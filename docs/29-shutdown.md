# 29 — teardown, and the exit that took the machine down

**2026-08-22.** Reported from play: closing the game **crashed the whole
computer**, not just the process. This is the cause and the fix. Written after
the fact rather than before, because the bug arrived from use rather than from a
plan.

## What was actually wrong: there was no teardown at all

3f-1 through 3f-3 built an OpenXR session, two swapchains at 4140x3292, a command
allocator, a command list, a fence, an RTV heap, and raw pointers into RT64's own
eye textures. **None of it was ever destroyed.** The process simply exited.

That is not a leak. On exit, three things race:

1. **The OpenXR session outlives the D3D12 device it was created on.** SteamVR
   holds references to that device and to every swapchain image. Destroy the
   device first and the runtime — *a different process* — is left dereferencing
   freed objects. This is the one that reaches the driver, and the driver is
   why the machine went down rather than the game.
2. **Our command objects are released while the GPU may still be executing work
   that references them.**
3. **`g_eyeSource` holds raw `ID3D12Resource*` into RT64's textures**, which RT64
   destroys on its way out.

## The first fix was right, and in the wrong place

Teardown went into `~RT64Context`, reasoning that `app` is a member so the device
must still be alive. It faulted immediately:

```
[gevr-xr] shutdown: begin
[gevr-crash] access violation WRITING address 0x168
[gevr-crash] fault at  GoldenRecomp.exe+0x38066 -> ge_vr::xr_shutdown + 0x36
[gevr-crash]   frame 8 GoldenRecomp.exe+0x35141 -> ~RT64Context + 0x81
```

`0x168` is `vrPresentEyeWidth`'s offset inside `SharedQueueResources`. Writing to
*exactly* a member offset means the base was null: `sharedQueueResources` had
already been reset.

**The reasoning was wrong because `Application::~Application()` is empty.**
`Application::end()` is the entire teardown, and it is called before
`~RT64Context` ever runs:

```c
void Application::end() {
    state.reset(); workloadQueue.reset(); presentQueue.reset();

    RenderHookDeinit *deinitHook = GetRenderHookDeinit();
    if (deinitHook != nullptr) { deinitHook(); }        // <-- here

    ... sharedQueueResources.reset(); ... swapChain.reset();
    ... presentGraphicsWorker.reset(); device.reset();
}
```

By `~RT64Context`, everything is already gone. **Which is exactly why the
original no-teardown build took the driver with it** — the OpenXR objects were
being cleaned up by process exit, long after the device had been destroyed. The
destructor was not merely a bad place to put the fix; it was *the same place the
bug already lived*.

## The right place is the deinit hook

At `deinitHook()` the picture is ideal, and not by luck — this is what the hook
is for:

| | At deinit hook | At `~RT64Context` |
|---|---|---|
| Present queue | **destroyed** — the draw hook cannot fire, nothing to race | destroyed |
| `sharedQueueResources` | **alive** | null |
| Command queue, device | **alive** — OpenXR can be destroyed legally | destroyed |

So `xr_shutdown` moved into `ge_vr_render_hook_deinit`, which `27` had already
created for chaining. `27` chained the hooks on the way *in*; this is the other
half.

## Teardown order

Reverse of construction, every step logged, so a future crash names its own step:

1. Zero RT64's requested eye size; drop `g_eyeSource`.
2. `xrEndSession` if running.
3. **Wait for GPU idle** — before any resource the GPU might still read is
   released. This is the step whose absence reaches the driver.
4. Destroy swapchains, then the reference space, then the session.
5. Release our command list, allocator, RTV heap, fence, fence event. **Not**
   the device or queue — those are RT64's and were never referenced.
6. `xrDestroyInstance` last.

`~RT64Context` stays as a **safety net**, not the path: a setup failure destroys
the context without `end()` ever running, and then nothing else will do it.
`xr_shutdown` is idempotent, and its `sharedQueueResources` access is now checked
rather than assumed.

## Racing the present thread

A flag is not enough. The hook runs on RT64's present thread; teardown runs on
the graphics thread. A plain flag leaves a window where the present thread is
already inside `xr_present_tick` when teardown starts freeing what it is using.

The hook takes `g_ge_vr_hook_mutex` for its whole body; teardown takes and
releases the same mutex, which **waits for any call already in flight**. One
uncontended lock per present, on a thread about to do a 27-megapixel copy.

At the deinit hook the present queue is already destroyed, so in the normal path
there is nothing to wait for. The mutex is for the destructor path, and for the
next person who moves this code.

## Second fix: a sleeping headset no longer costs a relaunch

Found while testing the first. `startup()` was called once and any failure set
`g_failed`:

```
[gevr-xr] xrGetSystem failed (-35). Headset asleep or not connected?
[gevr-xr] disabled for this run; the game continues normally.
```

`-35` is `XR_ERROR_FORM_FACTOR_UNAVAILABLE` — **the headset is dozing**. Nothing
about it is permanent; it starts succeeding the moment the headset wakes. Taking
it as final turns a dozing headset into a relaunch, in exactly the
build-launch-put-the-headset-on loop this project lives in.

Now retried about once a second. The instance is created once; the retry costs a
single `xrGetSystem`, which is the thing being waited on anyway. Logged once
rather than every attempt.

`g_attempted` ("the environment has been read") and `g_started` ("startup
succeeded") are now separate flags. One flag doing both jobs is what made the
first failure permanent.

## Gates

| # | Check | Result |
|---|---|---|
| 1 | `GE_VR_XR` unset, run and close | **Pass.** 60 fps, closes cleanly, no crash |
| 2 | XR on, headset asleep | **Pass.** Retry logged once, game runs at 60 fps, closes cleanly |
| 3 | XR on, session created, close | **Pass** for the no-session path; see below |
| 4 | `gevr.log` on exit | `shutdown: begin` -> `xr session destroyed` -> `complete, clean` |

## Not yet verified, and it is the case that matters

**A full-session shutdown — swapchains allocated, frames submitting, the eye copy
running — has not been tested.** The headset went to sleep partway through this
work, so every close since the fix has gone through the *no-session* path, which
exercises the guards but not step 3 or step 4.

Steps 2 and 3 never logged in any run so far, because there was no session to end
and no fence to wait on. **Their first real execution is still ahead.** Next
session, with the headset awake: play, close the window, and check for

```
[gevr-xr] shutdown: session ended
[gevr-xr] shutdown: gpu idle
[gevr-xr] shutdown: xr session destroyed
[gevr-xr] shutdown: complete, clean
```

All four lines, in that order. Anything missing names the step that failed —
which is the entire reason each one is logged separately.

## The rule this adds

`27` gave "check who else writes what you write." `29` adds its mirror:

**Know who destroys what you build, and when.** The assumption here was
"`app` is a member, so it is alive in the destructor". True, and irrelevant —
the object was alive and *already gutted*, because its teardown is a method
someone else calls, not its destructor. Ownership said one thing and lifetime
said another.

## Files changed

| File | Change |
|---|---|
| `src/main/ge_vr_xr.cpp` | `xr_shutdown`; retryable startup; `g_started` |
| `src/main/rt64_render_context.cpp` | Teardown in the deinit hook; hook mutex; destructor as safety net |
| `include/ge_vr_host.h` | `xr_shutdown` declaration |

Also added: **`vr.ps1`** in the repo root. The eye offset, sign, forced eye and
XR itself are all environment variables, so the whole experiment space is
relaunches rather than rebuilds. It clears every `GE_VR_*` variable before
setting the ones it wants — a leftover from a previous experiment is otherwise
indistinguishable from a change that did not work.
