# Step 3d — plan: two render targets

**2026-08-22. Plan only.** The last unsolved piece of Phase 1, and the one `05`
called "NOT STARTED, NOT DESIGNED ... the genuinely unsolved piece".

## Prior-art check

- **Upstream `rt64/rt64`: still nothing.** No stereo, multiview or VR work in
  tree or in issues, re-confirmed this session. Nothing to adopt and nothing to
  wait for.
- **`RaYRoD-TV/StarFox64-VR`**: publishes no source. Unchanged from `11`.
- **Perfect Dark PC port**: paid off enormously for 3c, but has nothing here — it
  is a Fast3D-lineage renderer with no equivalent of RT64's render-target
  manager.

**The prior art that matters is inside RT64 already**, and it is better than
anything external: `renderThreadLoop` renders one game workload into several
different override targets at display rate, every frame, today. Stereo is that
loop with one more dimension.

## The shape of the change

`renderThreadLoop`'s existing pass loop:

```
for (frame = 0; frame < displayFrames; frame++) {
    overrideTarget = (usingMSAA || frame > 0) ? interpolatedTargets[i++] : nullptr;
    threadRenderFrame(..., overrideTarget, overrideModifier, ..., vrEye);
}
```

Note `frame == 0` normally passes `nullptr` — it renders into the game's real
framebuffer target. Only the extra interpolated frames need scratch targets.

**That asymmetry is the design.** Eye 0 keeps the existing path byte for byte;
eye 1 becomes one additional override render into a scratch target:

```
for (frame = 0; ...) {
    for (eye = 0; eye < eyeCount; eye++) {          // eyeCount is 1 when VR is off
        overrideTarget = (eye == 1) ? eyeTargets[...] : existing_choice;
        threadRenderFrame(..., VrEyeOverride::fromConfig(vrConfig, eye));
    }
}
```

With VR off, `eyeCount == 1` and the loop is textually the old one. **No
behaviour change is possible in the mono path**, which is what makes the first
gate meaningful.

## What 3d deliberately does NOT do

**It does not touch the present path.** Eye 1 is rendered and discarded.

That sounds wasteful and is the point: it isolates "can RT64 produce two eye
images from one display list" from "can we display them", and those have
completely different failure modes. The evidence that eye 1 ran is frame time,
not pixels — see the gate.

Side-by-side display is 3e. OpenXR submission is 3f.

## Risks, most likely first

**1. `threadRenderFrame` has side effects beyond drawing.** It calls
`fbManager.recordOperations`, `framebufferRenderer->advanceFrame`, and can copy
targets back to RDRAM. Running it twice per frame could double-apply those.

*Why this is survivable:* the interpolation path **already** calls it up to three
times per workload and has done since before this project started. Those side
effects are already tolerated N times per frame. Stereo adds a dimension to a
loop that is already N-deep, rather than making a once-per-frame call twice.

**2. Shared depth.** Only the colour key is overridden; `depthTarget` still comes
from `targetManager.get(fbKey.depthTargetKey)`, so both eyes share one depth
buffer. Same reasoning as `12` §3.3: the interpolation path already shares depth
across several colour targets, and GoldenEye clears z from the display list every
frame via `zbufClearCurrentPlayer`, which is replayed in every pass. **Verify,
do not trust.** The failure looks like sparse missing geometry in one eye only.

**3. Frame budget.** `renderThreadLoop` drops passes when late, comparing against
`maxTimePerFrameMicro`. Dropping one eye of a pair is far worse than dropping
both — a stale image in one eye is a fusion failure. The skip decision must move
to pair granularity: decide before eye 0, never between eye 0 and eye 1.

**4. Target memory.** Per-eye scratch targets at the recommended per-eye size are
not free. 3d allocates one extra target per interpolated frame, not two.

## Gate 3d

```powershell
$env:GE_VR_FRUSTUM="1" ; $env:GE_VR_EYE="0"
build\Release\GoldenRecomp.exe
```

| Check | Pass |
|---|---|
| VR off (`GE_VR_FRUSTUM=""`) | **Pixel-identical to today**, and frame time unchanged. The mono path must be untouched. |
| VR on, picture | Identical to 3c's left-eye view. Eye 1 is not displayed. |
| VR on, **frame time** | **Roughly doubles.** This is the only evidence eye 1 rendered at all. |
| One eye only missing geometry | Would mean risk 2 — shared depth — is real |

**The frame-time check is the gate.** Without it, a build where eye 1 is silently
skipped looks exactly like success: the picture is correct either way, because
the picture is eye 0. Anyone judging this by eye passes a broken build.

Read it however you normally do; a clear before/after on the same spot in the same
level is enough. A halving of frame rate is the expected, correct result and is
not a performance regression to fix — it is two eyes being drawn at a resolution
chosen for one.

## After

- **3e** — present both targets side by side in the window. Last gate that needs
  no headset, and it catches nearly everything 3f would.
- **3f** — replace the present path with `xr_stereo.cpp`'s validated OpenXR
  submission. Fix the SteamVR floor calibration first (`10`).

---

# Implemented, 2026-08-22 — not yet built

Two files, both RT64, both MIT and therefore publishable upstream.

| File | Change |
|---|---|
| `hle/rt64_workload_queue.h` | `eyeColorTargets` — scratch colour targets for eye 1, one per display pass |
| `hle/rt64_workload_queue.cpp` | `vrStereo` / `eyeCount`, lazy target allocation, and the eye loop inside the frame loop |

## Two conditions added that the plan did not have

Both found while writing it, and both share a failure mode worth naming: **each
would produce a build that renders one eye twice, doubling the frame time and
therefore passing gate 3d while being wrong.** The gate is frame time precisely
because pixels cannot see eye 1 — which also means frame time cannot distinguish
"two eyes" from "one eye twice". These close that off at the source instead.

**1. `!interpolationTargetKey.isEmpty()`.** The override mechanism matches on a
colour framebuffer key. With no key, `setOverride` has nothing to match, and eye
1 renders into the same target as eye 0. Stereo needs an identifiable colour
framebuffer for exactly the reason interpolation does.

**2. `!usingMSAA`.** `threadRenderFrame` honours an override target only when
MSAA is off — `if ((overrideTarget != nullptr) && !usingMSAA)`. With MSAA on the
override is ignored entirely and eye 1 lands on top of eye 0.

So **stereo currently requires MSAA off**. That is a real limitation, not a
temporary hack: the override path in RT64 genuinely does not support it, and
making it do so is its own piece of work. Worth knowing before anyone tests with
antialiasing on and concludes stereo is broken.

## The eye loop's placement

Inside the frame loop, **after** the skip test. That makes an eye pair atomic for
free: the skip decision is taken before eye 0 and cannot fire between the eyes.
Risk 3 in the plan is closed by placement rather than by extra logic.

`uploadExtras` is forced false on eye 1 — it is a per-frame upload that eye 1
consumes rather than repeats.

Eye 1's `overrideModifier` is `0x1000 + frame`, far above the interpolated
targets' `1..N`, so `RenderFramebufferKey`s cannot collide.

## Build

RT64 only. No patch change, so the one-liner.

```powershell
$env:PATH = "C:\Program Files\LLVM\bin;C:\Program Files\CMake\bin;C:\Users\pdbar\AppData\Local\Microsoft\WinGet\Links;" + $env:PATH
cd C:\Users\pdbar\Desktop\GoldenEye64Recomp
cmake --build build --target GoldenRecomp --config Release --parallel
```

**Turn MSAA off in the game's graphics options before testing**, or `vrStereo`
is false and nothing happens.

## Gate

```powershell
# 1 - mono control
$env:GE_VR_FRUSTUM="" ; build\Release\GoldenRecomp.exe

# 2 - stereo
$env:GE_VR_FRUSTUM="1" ; $env:GE_VR_EYE="0" ; build\Release\GoldenRecomp.exe
```

| Check | Pass |
|---|---|
| Run 1 | Pixel-identical to 3c, frame time unchanged |
| Run 2, picture | Same left-eye view as 3c. Eye 1 is rendered and discarded |
| Run 2, **frame time** | **Roughly halved frame rate.** The only evidence eye 1 ran |
| Either run | No geometry missing from the visible eye — would indicate the shared depth target (risk 2) |

A halved frame rate is the correct result, not a regression: two eyes at a
resolution chosen for one.

---

## Result — 3d passes, 2026-08-22

Measured, not eyeballed. `gevr.log`, one line per second.

**Control** (`GE_VR_FRUSTUM=""`, `enabled=0`):

```
[gevr] 60.0 fps | render passes: eye0=183 eye1=0 distinctTargets=0
```

**Stereo** (`GE_VR_FRUSTUM="1"`, `GE_VR_EYE="0"`, `enabled=1`):

```
[gevr] 60.0 fps | render passes: eye0=183 eye1=183 distinctTargets=183
```

Across 40 sampled seconds: `eye1 == eye0` on every line, and
`distinctTargets == eye1` on **every** line, zero mismatches.

**RT64 produces two eye images from one display list, into two separate render
targets. Phase 1's remaining unsolved piece is solved.**

## The gate this doc originally specified would have FAILED this build

The plan above says: *"VR on, frame time — roughly doubles. This is the only
evidence eye 1 rendered at all."*

**Frame rate did not move. 60.0 fps in both runs.** An RTX 5090 rendering N64-era
geometry has enough headroom to absorb a second full render pass without
registering. Judged by the stated gate, a correct build looks broken.

That the gate was replaced before anyone ran it was luck dressed as judgement —
it was replaced because the user could not read a frame rate, not because the
gate was wrong. It happened to be wrong as well.

**The general fault: frame time is a proxy, and this one was doubly bad.** It
could not distinguish "two eyes" from "one eye twice" (which is why the
`distinctTargets` counter exists), *and* it could not detect the work at all on
fast hardware. Counting the thing itself is not merely more precise here — it is
the difference between a pass and a false negative.

## Incidental measurement worth keeping

**~183 render passes per second against 60 presented frames — about 3 per
displayed frame.** That is the interpolation multi-pass loop, measured rather
than inferred, and it is the machinery the eye loop hangs off. It also sets the
scale for Phase 2: at 90 Hz with two eyes the same structure implies roughly 540
passes per second, which is the number the OpenXR frame loop will have to live
inside.

## What this does not yet do

Eye 1 is rendered and discarded. Nothing displays it. That is 3e.
