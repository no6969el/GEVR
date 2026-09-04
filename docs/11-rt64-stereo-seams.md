# Phase 1 step 3 — the RT64 seams already exist

**2026-08-22. Research pass, no code written.** `05-going-forward.md` calls the
two-render-target problem "NOT STARTED, NOT DESIGNED ... the genuinely unsolved
piece of Phase 1". After reading RT64's render path in
`GoldenEye64Recomp\lib\rt64\src\`, that assessment is too pessimistic. **Every
mechanism stereo needs is already in RT64 and already exercised by an existing
feature.** The work is wiring, not invention.

This doc records what was found and where. It commits to no design; the
architecture choice is a separate decision.

---

## The three seams

### 1. Per-eye render target — `RenderTargetManager::setOverride()`

`render/rt64_render_target_manager.h` already carries an `overrideMap` beside
`targetMap`, and `RenderTarget &get(key, bool ignoreOverrides)` consults it.
`hle/rt64_workload_queue.cpp:352` sets an override and `:828` removes it.

The consequence: **the N64 framebuffer address does not have to map to one GPU
target.** The same game framebuffer can be rendered into two different
`RenderTarget`s by swapping the override between passes. That is precisely the
"two render targets" requirement, and it needs no new abstraction.

### 2. Per-eye view and projection — `ProjectionProcessor::processScene()`

`render/rt64_projection_processor.cpp` is the **single** place where the game's
matrices are rewritten before they reach the GPU. It already:

- copies `viewTransforms` / `projTransforms` into `modViewTransforms` /
  `modProjTransforms` (`:36-38`), and only the `mod*` copies are uploaded
  (`:152`) — so the game's own matrices are never disturbed;
- **wholesale replaces both matrices for perspective projections** when the
  debugger camera is on (`:91-95`):

  ```cpp
  if (workload.debuggerCamera.enabled && (proj.type == Projection::Type::Perspective) ...) {
      viewMatrix = workload.debuggerCamera.viewMatrix;
      projMatrix = workload.debuggerCamera.projMatrix;
  }
  ```

- already scales the projection for aspect ratio (`adjustProjectionMatrix`,
  `:11-16`) and already **lerps the view matrix between frames** via `RigidBody`
  for the interpolated-frame path (`:117-135`).

`DebuggerCamera` is a working, shipped precedent for "the host owns the camera
for a frame". A VR eye camera is the same override with different numbers.

Note it fires only for `Projection::Type::Perspective`. Orthographic scenes —
menus, the watch, the HUD — pass through untouched. That is the correct default
for Phase 1 and it is free.

### 3. Rendering one game frame N times — `WorkloadQueue::renderThreadLoop()`

The signature that matters (`hle/rt64_workload_queue.h`):

```cpp
void threadRenderFrame(GameFrame &curFrame, const GameFrame &prevFrame, ...,
    float curFrameWeight, float prevFrameWeight, float deltaTimeMs,
    RenderTargetKey overrideTargetKey, int32_t overrideTargetFbPairIndex,
    RenderTarget *overrideTarget, uint32_t overrideTargetModifier, ...);
```

`renderThreadLoop()` (`rt64_workload_queue.cpp:~1036`) already calls this in a
loop — `for (frame = 0; frame < displayFrames; frame++)` — rendering **one game
workload into several different override targets at a rate decoupled from the
game's logical tick**, recomputing `curFrameWeight` / `prevFrameWeight` per pass.
That is the interpolation path, and it is structurally the same loop stereo
needs. Per-eye rendering is an inner loop over two targets, not a new subsystem.

It also has frame-budget skip logic (`maxTimePerFrameMicro`) that already drops
passes when it runs late — behaviour that will need thought in VR, where dropping
one eye is worse than dropping both.

---

## What this changes about the plan

The docs assumed the eye split had to happen **in the game** — "a way to ask the
game to submit its display list twice" (`05`). RT64's structure says the split can
happen **after** the display list, host-side, on data RT64 has already parsed into
`DrawData`. The game submits once; RT64 draws twice.

Two consequences worth stating plainly, because they cut in opposite directions:

**In favour.** The game's 30/25 Hz tick stops governing head pose. RT64 already
re-renders a single workload multiple times at display rate; a head pose sampled
per pass rides that existing machinery. The interpolation work in `04` is not
merely a comfort prerequisite any more — it is the transport for head tracking.
It also costs the game nothing: no doubled MIPS-side work, no halved logic rate.

**Against, and this is the trap.** The game culls on the CPU against its own
`Mtxf` frustum in `viSetupCurrentPlayerView`. Geometry the game culled was never
put in the display list, so RT64 cannot draw it however it rewrites the matrices.
A host-side eye offset or head rotation that looks outside the game's submitted
frustum finds **nothing there** — the symptom is geometry popping in at the edges
when the head turns, worst at the outer edge of each eye where the Pimax's
53.99 deg outer FOV is widest.

That is the argument for the two halves belonging in different places:

| Concern | Where it belongs | Status |
|---|---|---|
| Cull against a frustum covering **both** eyes plus head-rotation margin | the MIPS patch, `ge_vr_bindtest.c` | already written; needs re-aiming from "one eye's frustum" to "superset frustum" |
| Exact per-eye view and projection | RT64 `ProjectionProcessor` | seam exists |
| Two targets | RT64 `RenderTargetManager` override | seam exists |
| Submit to the headset | new, replaces `VIRenderer` -> swapchain | `xr_stereo.cpp` is the validated consumer |

The already-built per-eye frustum maths is **not wasted** under this reading; its
job changes from "be the eye projection" to "be the culling superset", and the
same asymmetric-frustum code produces both.

`06`'s warning applies here too: a wider frustum pulls more geometry into view and
display list overflow becomes likelier, not less likely. Untested on Surface and
Streets.

---

## Prior art survey — 2026-08-22

Checked before designing anything, per the standing rule.

| Source | Verdict |
|---|---|
| `rt64/rt64` upstream | **No stereo, multiview or VR work**, in tree or in issues. Nothing to adopt, nothing to wait for. |
| `RaYRoD-TV/StarFox64-VR` | Closest analogue that exists: OpenXR on an N64 PC port, per-eye stereo, motion controllers, world-space HUD. **Source is not actually published** — the repo is a nine-line README pointing at a "Multiverse VR Hub" that ships no source either. Proof the shape of the thing works. Not a code input. |
| `ShinyWindow/Shipwright-VR`, `poregon/Shipwright-VR` | OpenVR on Ship of Harkinian. Different renderer entirely (libultraship / Fast3D, not RT64), and the author records that HUD and text do not line up. Low transferable value beyond confirming the HUD problem is real and belongs in Phase 3. |
| `Crementif/BotW-BetterVR` | Emulator-level VR (Cemu). Wrong layer for us. |
| Khronos `OpenXR-SDK` | Already in use and already validated on this rig (`09`, `10`). Keep. |

Conclusion: **there is no upstream stereo implementation to adopt.** The leverage
comes from RT64's own existing override mechanisms, not from a third party. Which
is the better outcome — it means no new dependency and no licence question.

---

## What is still genuinely unsolved

1. **Present path.** `PresentQueue` / `VIRenderer` render the final image to a
   `RenderSwapChain`. OpenXR wants two `XrSwapchain` images and an
   `XrCompositionLayerProjection`. This is new code, but `xr_stereo.cpp` has
   already done exactly it against this rig.
2. **Frame pacing interlock.** `xrWaitFrame` must gate the render loop, and the
   game's `waitForNextFrame2` pacing in `workbench_theboy.c` must not fight it.
   `05` predicted this would be fiddly. It still will be.
3. **The frame-skip budget** in `renderThreadLoop` assumes dropping a frame is
   acceptable. Dropping one eye is not.
4. **Game units per metre**, for the IPD offset. A provisional constant is fine;
   `room_data_float2` makes it per-level and that is Phase 4's problem.

Items 1 and 2 were always going to be Phase 2. Item 3 and 4 are new to the list.

---

## Rule that produced this doc

Read the host renderer before declaring the host renderer's problem unsolved.
`05` was written from the game's side of the boundary and reasoned about RT64 from
its outside. Two hours in `lib/rt64/src/` converted "not designed" into "three
existing seams and a present path".
