# 40 — the exit crash: the teardown is intact, and the RUNTIME CHANGED

**2026-08-23.** Reported: closing the game takes the whole PC down. A second
session diagnosed it as *"we never tear anything down — the XR session,
swapchains and instance are never destroyed, our D3D12 objects are never
released, and the render hook stays installed."*

**Every one of those specifics is false in this tree.** Acting on that diagnosis
would have replaced working, hard-won teardown with new code, and *that* would
have been the regression. What follows is what the source and the log actually
say.

---

## 1. The teardown exists, in full

`ge_vr_xr.cpp:907`, `ge_vr::xr_shutdown`, in reverse order of construction, every
step logged:

| Claim | Reality |
|---|---|
| "XR session never destroyed" | `xrEndSession` :936, `xrDestroySession` :964 |
| "Swapchains never destroyed" | `xrDestroySwapchain` :952, per eye |
| "Instance never destroyed" | `xrDestroyInstance` :984, last, deliberately |
| "D3D12 objects never released" | :972-976 — cmdList, allocator, rtvHeap, fence, `CloseHandle` |
| "Render hook stays installed" | `SetRenderHooks(prev...)` restores the chain, `rt64_render_context.cpp:569` |

It also does the thing the diagnosis said was missing and then some:
**`waitForGpu()` before releasing anything** (:944), guarded on queue and fence
still being alive; `g_appSpace` destroyed before the session; `sharedQueueResources`
null-**checked** rather than assumed, because the first version faulted there;
and `static bool done` making the whole function idempotent across both entry
paths.

**The present-thread race is handled too.** `g_ge_vr_shutting_down` is set first,
then `g_ge_vr_hook_mutex` is taken purely to drain — and the draw hook holds that
same mutex for the whole of `xr_present_tick`, so teardown cannot begin while a
frame is in flight. That is `29`'s work and it is all still there.

**Nothing in 3f-5 touched any of it.** 3f-5 changed `HeadView`, added a recentre
preprocess, an SDL key and launcher flags. `git log -p` on the teardown path is
unchanged since `29`.

## 2. The log says teardown was never REACHED

`ge_vr::log` calls `fflush` on **every line** (`rt64_render_context.cpp:650`), so
the log is not a buffering artefact.

The crashing run ends mid-frame on an ordinary fps line. **`shutdown: begin` — the
very first line of `xr_shutdown`, printed before anything dangerous happens — is
absent.** So the function was never entered. The failure is upstream of teardown,
not inside it.

## 3. The actual news: we are on a different OpenXR runtime

```
[gevr-xr] runtime: Pimax OpenXR 0.1.0          <- the crashing run
[gevr-xr] runtime: SteamVR/OpenXR 2.16.7       <- every previous session
```

**Every measurement, every doc and every conclusion in this project up to `36`
was made against SteamVR/OpenXR.** The runtime underneath us changed between
sessions and nothing announced it except this line.

That single fact explains three open items at once:

- **O9, the FOV that changed for no reason.** `-1.4869 / 1.0190 / 0.9657` this
  run against `09`'s measured `-1.3760 / 1.0358 / 1.0176`. Not a headset setting,
  not drift: **a different runtime reporting different numbers.** Closed.
- **The origin mystery from `33` and `36`.** SteamVR gave 4.55 m, then 1.16 m.
  Pimax OpenXR gives `y = -0.001 m` — a sane `LOCAL`. **SteamVR's zero pose was
  the broken thing**, exactly as the original `README` said before
  `00-START-HERE` argued it down.
- **The exit crash.** `Pimax OpenXR **0.1.0**` is a version-zero runtime. A
  whole-machine fault on exit is far more likely there than in teardown that has
  been reviewed, ordered, mutex-drained and idempotent since `29` — and which the
  log proves never ran.

**This is `07` GOTCHA 4 in a new costume.** That gotcha says check the log's
timestamp against the binary before concluding anything from it. The general form
is bigger: **check that the environment which produced your evidence is the
environment you think it is.** A changed runtime invalidates comparisons across
sessions in both directions, and every A/B run today has one foot in each.

---

## What to do, in order

### First: settle it with no code at all

Set the active OpenXR runtime back to **SteamVR** and close a live session.

| Result | Meaning |
|---|---|
| Exit is clean | The crash is the Pimax runtime. Not our bug. Pick a runtime and pin it |
| Exit still crashes | Ours, in a path the log has never reached. Then instrument, do not guess |

**Do this before any code changes.** It costs one relaunch and it decides whether
there is a bug to fix.

### Then, regardless of the answer, one real hardening

There is a genuine hazard in the current design, and it is *not* the one that was
reported.

`ge_vr_render_hook_draw` holds `g_ge_vr_hook_mutex` for the entire
`xr_present_tick`, and that tick contains **`xrWaitFrame`, which blocks**. If a
runtime fails to return from it while the session is going away, teardown waits
on that mutex **forever**. The process hangs; a forced kill with GPU work still
outstanding is precisely the driver-level fault that takes a machine down — and
it would produce exactly what we see: **no `shutdown: begin`, ever.**

That is consistent with the observation without requiring the teardown to be
wrong, and it is worth fixing whichever runtime is at fault:

- `try_lock` with a bounded wait in the deinit path, then proceed and log that
  the drain timed out, rather than blocking indefinitely;
- and a log line on entry to the deinit hook, **before** the mutex, so the next
  occurrence distinguishes "never called" from "called and blocked". Right now
  those two look identical, and they have completely different causes.

**Not built. Not scheduled ahead of the runtime A/B**, because if SteamVR exits
cleanly this is hardening rather than a fix, and its priority changes.

### Minor, noted not fixed

`ge_vr::log` uses a function-local `static FILE *` with no mutex and is called
from both the game thread and the present thread. Interleaved lines are cosmetic;
the unsynchronised lazy `fopen` is a genuine if narrow race.

---

## The rule this earns

Two sessions have now spent effort on this: one proposing to rewrite code that
already existed, one reading the code first and finding the runtime had moved.

**Verify the claim against the source before acting on it, however confident the
claim sounds — and check what changed in the environment before assuming what
changed in the code.** The log line naming the runtime has been printed since
`27` and nobody read it, because nobody expected it to vary.

`gevr.log`'s runtime line should be checked at the top of every session, beside
the binary's timestamp.
