# Step 3f — plan: the OpenXR present path

**2026-08-22.** Phase 1 is complete: RT64 renders two correct eye images into two
targets and both have been seen on a monitor with real parallax. 3f puts them in
the headset.

## Prior-art check

- **Upstream `rt64/rt64`**: no OpenXR, no stereo. Re-confirmed. Nothing to adopt.
- **`xr_stereo.cpp`, ours, 800 lines, already validated against this exact rig**
  (`10`): instance creation at `XR_API_VERSION_1_0`, D3D12 graphics binding,
  swapchain format enumeration, per-eye swapchains, the
  `xrWaitFrame`/`xrBeginFrame`/`xrLocateViews`/`xrEndFrame` loop, and the
  pose-to-view and tangents-to-projection helpers. **This is the input, and it is
  known-good rather than merely plausible.**

The remaining unknown was never OpenXR. It is whether an XR session can be
created on *RT64's* D3D12 device instead of one we made ourselves.

## The mechanism, confirmed by reading RT64

It can, and RT64 exposes exactly the handles required:

| Need | Source |
|---|---|
| `ID3D12Device*` for `XrGraphicsBindingD3D12KHR` | `D3D12Device::d3d` (`d3d12/rt64_d3d12.h:400`), an `ID3D12Device8*` |
| `ID3D12CommandQueue*` | `D3D12CommandQueue::d3d` (`:228`) |
| A per-frame callback at present time | `RenderHookDraw(RenderCommandList*, RenderFramebuffer*)`, already invoked in `PresentQueue::threadPresent` |
| Setup callback with the device | `RenderHookInit(RenderInterface*, RenderDevice*)` |

`SetRenderHooks()` is RT64's own supported extension point. It is not a hole we
are making.

## The architectural consequence, and it is a good one

**Almost all OpenXR code lives in the recomp host, not in RT64.**

The host registers a render hook; RT64 calls it once per present with a command
list already open on the present queue; the host runs the XR frame there. RT64's
side of 3f is then tiny and generic: publish the two eye targets so the hook can
reach them. Nothing OpenXR-shaped enters RT64 at all.

That matters beyond tidiness. Per `12` §7, RT64 changes are MIT and belong
upstream in `rt64/rt64`; the recomp host is GPL-adjacent and stays local. A
design that kept the XR session inside RT64 would put a large, vendor-specific,
unupstreamable lump in the half of the project meant to be contributed back. This
split falls along the licence boundary without being contrived to.

## Staging — four slices, four gates

The temptation is one big change. Resisted: "nothing appears in the headset" has
at least six independent causes, and separating them afterwards is far more
expensive than four builds.

### 3f-1 — session only, no rendering

Create the instance, system, and session on RT64's device via `RenderHookInit`.
Run the event loop. Render nothing.

**Gate:** `gevr.log` shows the session reaching `XR_SESSION_STATE_FOCUSED`, the
runtime name, and the per-eye recommended size. **The game on the monitor is
completely unchanged.** SteamVR shows the app as connected.

This isolates "can we create an XR session inside a running game on RT64's
device" — where the adapter LUID check from `09` lives — from everything visual.

### 3f-2 — submit solid colour

Create the two swapchains. Each frame: acquire, clear the image to a flat colour,
release, `xrEndFrame` with a projection layer. Do not touch the eye targets.

**Gate:** the headset shows a flat colour filling both eyes instead of the
SteamVR void. Left and right different colours, so a single-eye submission is
visible immediately.

This isolates the frame loop, swapchain lifecycle and layer submission from
anything to do with the game's images. It is also the first thing that can
deadlock the present thread, and it does so with nothing else in flight.

### 3f-3 — the game's eyes, and the tint test

Copy RT64's two eye targets into the acquired swapchain images. Same D3D12 queue
as RT64's present, so ordering is free and no cross-queue fence is needed.

**Gate: the tint test first, before any judgement of the picture.** Left eye
tinted red, right blue. `10` is unambiguous:

> A monoscopic image with correct perspective looks *exactly* like working
> stereo — it fuses, it looks like a room, it survives head movement.

Only after the tint passes: is there depth, and is it the right way round? **This
is where `GE_VR_EYE_SIGN` gets settled**, since `25` closed 3e with the sign
resting on argument rather than observation.

### 3f-4 — live pose and FOV

Replace the hardcoded Pimax tangents and the `GE_VR_TEST_OFFSET` constant with
per-frame values from `xrLocateViews`, feeding `VrConfiguration` through the
existing path. Head rotation reaches the game's culling frustum via the patch's
existing widening.

**Gate:** the world stays put when the head turns. IPD looks right rather than
exaggerated.

## Risks, in the order they are likely to bite

1. **Adapter mismatch.** OpenXR names the adapter by LUID; RT64 picks its own.
   Single-GPU rig, so they will agree — but `xr_probe.cpp` already contains the
   check and it should be carried over rather than reimplemented.
2. **Swapchain format.** RT64's targets are `R8G8B8A8_UNORM` or the HDR variant;
   the runtime offers a list. Pick a match, or the copy needs a conversion pass
   rather than `CopyResource`.
3. **Size mismatch.** RT64's eye targets are sized from the game's framebuffer
   and resolution scale, not the headset's 4140x3292 recommendation. Create the
   swapchains at RT64's size and let the runtime scale — `09` anticipated exactly
   this and called it "a knob, not a requirement".
4. **Frame pacing.** `xrWaitFrame` wants to own the cadence; the present thread
   currently has it. `12` §5 deferred this deliberately and it stays deferred:
   get a picture first, interlock in Phase 2 proper. Expect judder, and do not
   chase it in 3f.
5. **Session lifecycle against the game's own window.** Losing focus, alt-tab and
   exit all need handling, and a session that never reaches `FOCUSED` renders
   nothing while looking like a rendering bug. `10`'s lesson — anchor on
   `FOCUSED`, not on the first frame — applies directly.

## What must be ready before 3f-3

**The SteamVR floor calibration.** `10` records the head 2.4-3.2 m above the
floor plane. It sabotaged one stereo test already by collapsing apparent
disparity, and it will make every judgement in 3f-3 and 3f-4 unreliable. Not
needed for 3f-1 or 3f-2.

---

# 3f-1 implemented, 2026-08-22 — not yet built

## Correction to the gate above, found while writing it

The plan says 3f-1's gate is the session reaching `XR_SESSION_STATE_FOCUSED`.
**That is unreachable in 3f-1 and the gate as written would fail a correct
build.**

Session state advances in response to *frames being submitted*. Without
`xrWaitFrame`/`xrEndFrame` the runtime has no reason to move past
`SYNCHRONIZED`, and `10` said as much in passing — "frames begin rendering at
session state VISIBLE" — which is the same fact read from the other direction.

`FOCUSED` belongs to 3f-2, where frames start being submitted. **3f-1's gate is
`READY` followed by a successful `xrBeginSession`.**

That is the fourth gate this project has specified that a working build would
fail, after frame time in `24` and twice in `25`. The pattern is now unmistakable
enough to name: **the gate is being written from what success looks like at the
end of the step, not from what this slice actually changes.** Writing the gate
after the code, rather than before, would have caught every one of them — but
would also have made the gate a description of the implementation rather than an
independent check. The real fix is to ask, for each gate, "what would this build
have to do differently for this to fail?"

## Zero RT64 changes

3f-1 needs none. Everything required is already reachable from the host:

| Need | Path |
|---|---|
| `ID3D12Device8*` | `app->device` cast to `RT64::D3D12Device`, member `d3d` |
| `ID3D12CommandQueue*` | `app->presentQueue->ext.presentGraphicsWorker->commandQueue` cast to `RT64::D3D12CommandQueue`, member `d3d` |

`PresentQueue::ext` is already used by the host at
`rt64_render_context.cpp:358`, so this is an established path rather than a new
one. The render hooks are not needed yet either — `xr_tick()` is called from
`update_screen`, which the host already owns.

## Files

| File | Change |
|---|---|
| `src/main/ge_vr_xr.cpp` | **NEW.** Instance, system, adapter LUID check, session, event loop |
| `include/ge_vr_host.h` | `ge_vr::log`, `xr_tick`, `xr_session_running` |
| `src/main/rt64_render_context.cpp` | `ge_vr_log` becomes `ge_vr::log`; `xr_tick` called per frame |
| `CMakeLists.txt` | OpenXR loader include, lib, and a POST_BUILD copy of the DLL |
| `lib/openxr/` | the loader, copied from `GoldenEyeVR\workspace\lib\openxr` |

Both new sources are ours and are mirrored into the MIT repo at `repo\host\`.

Two things carried over deliberately rather than rewritten:

- **`XR_API_VERSION_1_0`, never `XR_CURRENT_API_VERSION`** (`09`). The 1.1
  headers' constant is rejected by SteamVR, and the loader reports it only as
  "chained CreateInstance call failed", naming neither the version nor the
  runtime.
- **The adapter LUID check.** The runtime names the adapter it requires; RT64
  picks its own. They will agree on a single-GPU rig, and a mismatch produces a
  session that creates cleanly and then renders nothing — cheap to check,
  expensive to discover.

## Failure is non-fatal by design

If anything in startup fails — SteamVR not running, headset asleep, no D3D12 —
it is logged once and XR stays off for the run. The game continues normally.
3f must not be able to stop the game from launching.

## Build

CMakeLists changed and a source file was added, so CMake re-configures itself
before compiling. The one-liner still covers it.

```powershell
$env:PATH = "C:\Program Files\LLVM\bin;C:\Program Files\CMake\bin;C:\Users\<USER>\AppData\Local\Microsoft\WinGet\Links;" + $env:PATH
cd C:\Users\<USER>\Desktop\GoldenEye64Recomp
cmake --build build --target GoldenRecomp --config Release --parallel
```

## Gate 3f-1

**Start SteamVR first**, and have the headset awake — asleep, the probe reported
it explicitly rather than printing garbage, and this does the same.

```powershell
build\Release\GoldenRecomp.exe
```

No VR environment variables needed; the session is independent of them.

| Check | Pass |
|---|---|
| The monitor | **Completely unchanged.** Nothing is rendered to the headset |
| `gevr.log` | runtime name, system name, recommended per-eye size |
| Adapter LUID | `match: yes` |
| Session | `session created on RT64's device and present queue` |
| State | reaches `READY`, then `xrBeginSession ok` |
| SteamVR | shows GoldenEyeVR as a connected application |

**Not expected:** anything past `SYNCHRONIZED`, and any image in the headset.
Both arrive in 3f-2.

---

# 3f-1 result, and the bug it surfaced

## 3f-1 passes

```
[gevr-xr] runtime: SteamVR/OpenXR 2.16.7
[gevr-xr] system: SteamVR/OpenXR : aapvr
[gevr-xr] recommended per eye: 4140x3292, 1 sample(s)
[gevr-xr] adapter LUID match: yes (runtime 00000000:0001D3AE, RT64 00000000:0001D3AE)
[gevr-xr] session created on RT64's device and present queue.
[gevr-xr] session state -> IDLE -> READY
[gevr-xr] xrBeginSession ok.
```

Every number matches `09`'s probe, taken a year of sessions earlier against a
standalone program. **An OpenXR session can be created on RT64's own D3D12
device and present queue**, which was the only real unknown in 3f.

Reported from play, and all correct for this slice: SteamVR shows the app
connected and sitting in the compositor's loading area, nothing renders to the
headset, the desktop view was needed, and the monitor image was mono because the
VR environment variables were cleared.

## The zoom bug — ours, and a state leak rather than an arithmetic one

Also reported: scope zoom worked, then stopped, then appeared on a weapon with no
scope.

`bondview.c:2631` reads the FOV back and compares it against the stock constant:

```c
fovy = viGetFovY();
if (fovy == 0 || fovy == 60.0f) fovy = 1;      /* not zoomed */
else fovy = ADJUST_ZOOM_FOV(60.0f) / fovy;     /* zoomed, by this factor */
```

`viSetFovY` now stores **106**. That equality never holds, so the game believes
it is permanently zoomed at about 0.57x. `propobj.c:932` reads it too.

**`18` required the widening to be multiplicative precisely so zoom would
survive, and the arithmetic is right.** What it missed is that the value is not
only consumed downstream — it is **read back and compared against a literal**.
Multiplicative arithmetic preserves *ratios*; it does not preserve *equality with
60*, and the game tests the latter.

That is the same shape as `21`: a change that is correct in its own terms leaks
into game logic that inspects its own state. Worth stating as a rule, because
this is twice now: **when a patch changes a value the game stores, check who
reads it back, not just who consumes it.**

Fixed by patching `viGetFovY` to divide the widening out, so the game's own view
of its FOV is unchanged while drawing and culling keep the wide value.
`viSetFovY(viGetFovY())` round-trips exactly. Safe in a getter — the warning at
the top of `ge_vr_bindtest.c` is about *mutating* in getters, which compounds
across many calls per frame; this stores nothing.

**New `RECOMP_PATCH` name, so the long build applies. Expect 31 renamed, not 30.**

# 3f-2 implemented — not yet built

Per-eye swapchains at the runtime's recommended 4140x3292, the
wait/begin/locate/acquire/release/end frame loop, and a flat colour per eye.

**Left red, right blue** — `10`'s tint convention, so a single-eye submission or
a swapped pair is obvious the moment the headset goes on instead of being
inferred from a picture.

Three decisions worth recording:

- **`LOCAL`, not `STAGE`.** STAGE is anchored to the play-area floor, and this
  rig's floor is 2.4-3.2 m out (`10`). LOCAL anchors where the headset was at
  session start, so a miscalibrated floor cannot move the world. It also means
  3f-2 and 3f-3 no longer wait on the room setup.
- **Our own command allocator and list, executed on RT64's queue.** Same queue
  gives ordering against RT64's own work for free.
  `ExecuteCommandLists` is free-threaded, so calling it from the game thread
  while the present thread uses the same queue is legal. The fence is for our
  *allocator*, which cannot be reset while the GPU still holds its commands.
- **Full recommended resolution for now.** `09` calls this "a knob, not a
  requirement" and expects the end state to render below it and let the runtime
  scale. Matching it here removes one variable from 3f-3.

## Gate 3f-2

Build the long way (new `RECOMP_PATCH` name), start SteamVR, wear the headset.

| Check | Pass |
|---|---|
| `tools_weaken_patched.py` | **31** renamed |
| Headset | **Left eye deep red, right eye deep blue**, filling the view |
| Session state | advances to `VISIBLE`, then `FOCUSED` |
| `gevr.log` | `first layer submitted`, swapchain format and image counts |
| Monitor | still playable, though pacing may be poor - see below |
| Zoom | scope zoom behaves normally again, and no zoom on unscoped weapons |

**Expect bad frame pacing.** `xrWaitFrame` blocks for the headset's cadence and
is being called from the game thread; the interlock is Phase 2's job and `12` §5
deferred it deliberately. Judder here is expected and not worth chasing.

**If both eyes are the same colour**, one eye's submission is failing. **If the
headset stays in the loading area**, the layer is being rejected — the log will
say whether `first layer submitted` was ever reached.
