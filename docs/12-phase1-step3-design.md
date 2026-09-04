# Phase 1 step 3 — design: the hybrid eye split

**2026-08-22. Design only, no code written.** Decision taken with the user:
**hybrid**. The game owns a culling frustum that is a *superset* of both eyes;
RT64 owns the exact per-eye view and projection and the two render targets; a new
present path submits to OpenXR.

Read `11-rt64-stereo-seams.md` first — it establishes that the RT64 mechanisms
this design uses already exist and are already exercised by shipped features.

---

## 1. Why hybrid, in one paragraph

Pure host-side rendering is tempting because RT64 already re-renders one game
workload several times per tick at display rate, which would decouple head pose
from the game's 30 Hz logic entirely. It fails on one point: **the game culls on
the CPU, so geometry it discarded is not in the display list and RT64 cannot draw
it however the matrices are rewritten.** Pure game-side rendering avoids that but
doubles MIPS work, halves the logic rate, and re-couples head pose to 30 Hz. The
split falls along the boundary each side can actually see:

| Concern | Owner | Why there |
|---|---|---|
| What geometry exists at all | the patch (MIPS) | only the game can decide not to cull it |
| Where each eye is, exactly | RT64 `ProjectionProcessor` | only the host knows the live head pose |
| Two images | RT64 `RenderTargetManager` override | the seam already exists |
| Getting them to the headset | new `XrPresenter` | `xr_stereo.cpp` already proved the consumer |

The game ends up submitting a slightly-too-wide monoscopic display list, once,
and never learning that anything stereoscopic happened to it.

## 2. What changes about the existing patch

> **SUPERSEDED 2026-08-22 by `17-step3c-plan.md` and `18-step3c.md`.** This
> section says the patch should widen the cull by rewriting the `Mtxf` frustum,
> and warns to check `bgUpdateCurrentPlayerScreenMinMax` and
> `bgScissorCurrentPlayerView` afterwards. Both are aimed at the wrong lever:
> the game's culling frustum derives from `c_perspfovy` via
> `currentPlayerSetCameraScale()`, not from the projection matrix. The
> implemented design patches `viSetFovY` instead, which is the engine's own
> entry point and updates drawing and culling together. The FOV numbers and the
> head-turn-margin reasoning below still stand; the mechanism does not.


`ge_vr_bindtest.c` keeps all its maths and changes its *purpose*. It currently
builds one eye's asymmetric frustum. It should instead build the **union** of both
eyes plus a head-motion margin:

```
cullTanLeft  = -max(|tanLeft_L|,  |tanLeft_R|)  extended by margin
cullTanRight = +max(|tanRight_L|, |tanRight_R|) extended by margin
```

With the measured Pimax numbers (`09`) the union is the outer tangent on each
side: +/-1.3760, i.e. +/-53.99 deg — roughly 108 deg horizontal against the
100 deg a single eye sees. Vertical is unchanged at +/-45.5 deg, since the panels
are parallel and there is no vertical disparity.

**The margin is not optional and it is the part most likely to be got wrong.**
The display list is built once per game tick (30 Hz) and consumed by up to three
render passes per eye at 90 Hz. Between the tick that built it and the last pass
that draws it, the head can turn. At a brisk 200 deg/s that is ~6.7 deg of yaw per
tick, and that pass is drawing geometry the game culled 6.7 deg ago. Budget a
tunable `GE_VR_CULL_MARGIN_DEG`, start at 15, and treat "edges pop when I turn my
head fast" as the signal to raise it.

**Two matrices, two different jobs, and only one still matters visually:**

- The float `Mtxf` is what the game culls with. **This is the one that must
  become the superset.** It also feeds GoldenEye's per-room screen extent logic —
  `bgUpdateCurrentPlayerScreenMinMax` and `bgScissorCurrentPlayerView`, both
  already in the renamed-patch list and therefore already reachable. If those keep
  using a narrow frustum, room culling will quietly undo the widened `Mtxf`.
  Verify them; do not assume one change is sufficient.
- The fixed-point `Mtx` becomes visually irrelevant, because RT64 replaces the
  projection derived from it. Set it to the **centre** (cyclopean) frustum anyway.
  That gives a defined fallback: if the RT64 override is off or fails, the game
  renders a sane wide monoscopic picture rather than a broken one.

`GE_VR_MIN_ZNEAR_UNITS` enforcement stays exactly as it is.

**Known cost, already predicted.** `05` warns that a wider frustum pulls more
geometry into view and makes display list overflow likelier — each tag costs 2 Gfx
slots, props 4, and Surface and Streets were never tested. This design makes the
frustum wider still. Overflow moves from "possible" to "expected on dense levels"
and needs its own instrumentation, or it will be diagnosed as something else.

## 3. RT64 side — the per-eye override

### 3.1 Where it attaches, and why NOT where the debugger camera attaches

The obvious move is to copy the `DebuggerCamera` block in
`ProjectionProcessor::processScene` (`rt64_projection_processor.cpp:91`). **That
would be wrong**, and the reason is worth stating because the mistake looks like
success at first.

The debugger-camera branch sits *before* the aspect-ratio adjustment and *before*
the `RigidBody` interpolation, and the interpolation block is explicitly guarded
with `!workload.debuggerCamera.enabled` — the debugger camera deliberately
**disables** frame interpolation. For VR we want the exact opposite: the game's
view matrix must still be interpolated between ticks, because that smooth camera
motion is the entire reason the interpolation work in `04` exists. Attaching in
the debugger slot would silently switch it off and reintroduce 30 Hz judder in a
headset — a comfort failure, not a cosmetic one.

Composition order:

```
1. viewMatrix = game's view for this projection        (existing)
2. viewMatrix = rigidBody->lerp(...)                   (existing — KEEP)
3. viewMatrix = eyeOffset * headDelta * viewMatrix     (NEW — after the lerp)
4. projMatrix = the eye's asymmetric frustum           (NEW — outright replace)
5. viewProjMatrix = mul(viewMatrix, projMatrix)        (existing)
```

> **AMENDED by `15-step3b.md`.** The eye projection is supplied as four
> *tangents*, not as a finished matrix, and only the four frustum-shape terms are
> rewritten — the depth row is left as the game wrote it. Handing RT64 a complete
> projection would mean choosing a depth convention, and the game's is not D3D's.

Step 4 **replaces** rather than adjusts. The headset's frustum is fixed per eye,
so neither `adjustProjectionMatrix(projRatioScale)` nor the projection lerp should
touch it — and `aspectRatioScale` should be forced to 1.0 in VR, since ultrawide
stretch is meaningless when the runtime defines the frustum.

Step 3 pre-multiplies. `headDelta` is the head pose change since the tick that
built the display list; `eyeOffset` is the IPD translation. Both are in game
units, which is where `gameUnitsPerMetre` enters — see §6.

### 3.2 The struct, and where it lives

`DebuggerCamera` lives on the `Workload`. The eye override must **not**, because
it varies per render pass while the workload is shared between passes. It belongs
on `ProjectionProcessor::ProcessParams`, already constructed fresh per call to
`threadRenderFrame`:

```cpp
struct VrEyeOverride {
    bool     enabled  = false;
    uint32_t eyeIndex = 0;        // 0 left, 1 right
    interop::float4x4 eyeView;    // eyeOffset * headDelta, in game units
    interop::float4x4 eyeProj;    // asymmetric frustum, D3D [0,1] depth
    bool     inLevel  = false;    // mirrors geVrInLevel(); gates menus out
};
```

Gate on `proj.type == Projection::Type::Perspective`, as the debugger camera
already does. Orthographic scenes — menus, the watch, the HUD — then pass through
untouched, which is the correct Phase 1 behaviour and costs nothing. `inLevel`
mirrors the patch's existing `geVrInLevel()` gate so the title and front end stay
flat; `05` already found that `viSetupCurrentPlayerView` is shared between world
and front end, and this is that same problem surfacing on the host side.

One wiring detail that will otherwise cost an hour: `threadRenderFrame` only runs
the projection processor when `processProjections` is true, currently
`aspectRatioAdjustment || prevFrame.matched || curFrame.isDebuggerCameraEnabled()`.
**Add the VR flag to that condition**, or the override is silently skipped on
frames with no interpolation match — which is the first frame of every scene, i.e.
exactly the frames looked at while debugging.

### 3.3 Two render targets

`RenderTargetManager::setOverride()` already lets one N64 framebuffer address
render into a caller-supplied `RenderTarget`, and `threadRenderFrame` already
takes `overrideTargetKey` / `overrideTarget` / `overrideTargetModifier` for
exactly this. The interpolation path in `renderThreadLoop` allocates a
`std::vector<std::unique_ptr<RenderTarget>> interpolatedTargets` and cycles
through them. **Allocate `eyeTargets[2]` the same way, with distinct
`overrideTargetModifier` values so the `RenderFramebufferKey` differs per eye.**

The pass loop becomes an eye loop nested inside the existing frame loop; each pass
calls `threadRenderFrame` with that eye's target and that eye's `VrEyeOverride`.

**The depth target is shared between eyes, and this design accepts that.** Only
the colour key is overridden; `depthTarget` still comes from
`targetManager.get(fbKey.depthTargetKey)`. That is safe here for a checkable
reason rather than a hopeful one: the interpolation path **already** renders one
workload into several different colour targets against a single depth target and
is known to work, and GoldenEye clears its z-buffer from the display list every
frame — `zbufClearCurrentPlayer` is in the renamed-patch list, so the clear is
replayed in every pass. **Verify rather than trust**; the failure mode is the
second eye's geometry being rejected against the first eye's depth, which looks
like sparse missing geometry in one eye only.

### 3.4 The frame-skip budget must treat an eye pair as atomic

`renderThreadLoop` drops passes when it runs late, comparing elapsed time against
`maxTimePerFrameMicro`. Correct for interpolated frames, where dropping one costs
smoothness. **In VR, dropping one eye of a pair is far worse than dropping both** —
it presents a stale image to one eye, which is a fusion failure and immediately
nauseating. Move the skip check to pair granularity: decide before eye 0, never
between eye 0 and eye 1.

## 4. Present path

`PresentQueue` / `VIRenderer` currently render the final image into a
`RenderSwapChain`. OpenXR wants two `XrSwapchain` images and one
`XrCompositionLayerProjection`. This is the genuinely new code, but the risk is
low: `xr_stereo.cpp` has already done precisely this against this rig, and D3D12
is already the default graphics API on Windows
(`src/main/rt64_render_context.cpp:269`), matching the binding the probe validated.

Carry forward unchanged from `09` and `10`:

- request `XR_API_VERSION_1_0`, never `XR_CURRENT_API_VERSION`;
- check the runtime's requested adapter LUID against RT64's device;
- anchor on `XR_SESSION_STATE_FOCUSED`, not the first rendered frame;
- log head position once a second, permanently.

## 5. Frame pacing — deliberately deferred

`xrWaitFrame` wants to own the render cadence; the game's `waitForNextFrame2` and
`InitFrameRateControl` in `workbench_theboy.c` currently do. `05` predicted this
would be fiddly and it will be. **Step 3 does not solve it.** Get two correct eye
images presented first, on whatever cadence, then interlock in Phase 2. Attempting
both at once means every judder has two possible causes.

## 6. Game units per metre

The IPD offset is a translation in game units, so it needs a scale. Use a single
tunable constant for now. `room_data_float2` makes the true value per-level and
Phase 4 owns that; a wrong constant here shows up as the world feeling giant or
tiny, which is obvious, harmless, and off the critical path.

**But the rig's floor calibration must be fixed before this is tuned by eye.**
`10` records the head sitting 2.4-3.2 m above the floor plane while horizontal
position is accurate to 3 cm. Calibrating game scale against a floor over a metre
out bakes the error in permanently, and it already sabotaged one stereo test.

## 7. A licence finding — checked, and acted on

`lib/rt64/LICENSE` reads **"MIT License, Copyright (c) 2024 RT64 Contributors"**.

`PUBLISH-MANIFEST.md` used to put every file in `thirdparty-diffs\` in the
do-not-publish bucket, reasoning that "a diff against GPL-licensed source is a
derivative work of that source". Sound for the recomp host, which links GPL-3.0
`N64ModernRuntime`. **It does not apply to RT64**, a separately licensed MIT
project that merely happens to be vendored into that tree. The test is which
project's source the diff derives from, not which repo the file sat in.

Checked 2026-08-22 before acting:

- vendored `lib/rt64/LICENSE` is the MIT text;
- upstream `rt64/rt64`'s `LICENSE` is the same MIT text — cblock85's flattened
  copy did not alter it;
- no file under `lib/rt64/src/hle/` or `lib/rt64/src/render/` carries any notice
  beyond that LICENSE. The only additional notices in RT64's tree are under
  `src/contrib/` — `D3D12MemoryAllocator`, `dxc`, `im3d` — which we do not
  modify. **Repeat this check before ever touching `src/contrib/`.**

Acted on the same day. `local-only\thirdparty-diffs\` is now split:

| Folder | Derives from | Publishable |
|---|---|---|
| `rt64\` | `rt64/rt64`, MIT | yes — as a fork of or PR against `rt64/rt64` |
| `recomp-host\` | `cblock85/GoldenEye64Recomp` + GPL-3.0 `N64ModernRuntime` | no — stays local |

`PUBLISH-MANIFEST.md` and `local-only\thirdparty-diffs\README.md` both record
the split with its evidence.

**This matters for the work below**, because most of the new code in this design
lands inside RT64 and is therefore publishable upstream, where it is actually
useful. `VENDORING.md` §1 rule 3 is untouched — the split applies that rule's
first clause rather than making an exception to it.

**Still a reading of licence files by the people working on the project, not
legal advice.** It is recorded with its evidence so it can be re-checked rather
than re-argued from memory.

## 8. Build order, with a test gate at every step

Each step is small enough that a failure has one plausible cause. **No step
proceeds until its gate passes.**

| Step | Change | Gate — what a pass looks like |
|---|---|---|
| **3a** | Add `VrEyeOverride`, thread it through `ProcessParams` and `threadRenderFrame`, wire the `processProjections` condition. **Disabled by default.** | Game runs on the monitor and is **pixel-identical** to today. A visible change here means the plumbing is not inert and something is wrong before any VR logic exists. |
| **3b** | Enable the override with hardcoded constants: left-eye offset, left-eye frustum. Still one target, still the monitor. | The view shifts sideways by roughly the IPD and the frustum is visibly asymmetric. **Straight edges stay straight** — shear means the row-2 skew got transposed, the failure `10` warns about. Flip to the right eye and it moves the other way by the same amount. |
| **3c** | Widen the patch's cull frustum (§2) and re-verify 3b. | No new geometry pops at the edges when turning in-game. Watch for display list overflow on a dense level — Surface or Streets, not the Facility. |
| **3d** | Allocate `eyeTargets[2]`, render both eyes per pass. Present **left only** to the window. | Picture identical to 3b, but frame time roughly doubles. That doubling **is** the proof both passes ran; without it, eye 1 is being skipped silently. |
| **3e** | Debug present: both eye targets side by side in the window. | Two visibly different images; cross-eye fusion gives real depth. **This is the last gate that does not need the headset**, and it catches almost everything the headset would. |
| **3f** | Replace the present path with the OpenXR submission from `xr_stereo.cpp`. | In the headset. Run the **tint test first** — left eye red, right eye blue — before judging anything by parallax. `10` is emphatic about this, and it was learned the expensive way. |

## 9. What is needed from the user, and when

Nothing until 3a is written. Then, in order:

1. **Gates 3a-3e — at the rig, on the monitor, no headset.** For each: launch
   `build\Release\GoldenRecomp.exe` **from the repo root** (never by
   double-click — `07`), load a level, and report against the gate description
   above. A photo or capture beats a description for 3b and 3e.
2. **Before 3f — fix the SteamVR floor calibration.** Re-run room setup, then run
   `xr_stereo.exe` and report the logged head height. It should read roughly real
   eye height, not 2.4-3.2 m.
3. **Gate 3f — in the headset.** `xr_stereo.exe tint` first to confirm the rig is
   still good, then the game. Report the tint result before any impression of
   depth or scale.
4. **Not blocking, but still the only copy** — push the `goldeneye-native`
   bundle. The device bridge has no network, so this one cannot be automated from
   here; the four commands are in `PUBLISH-MANIFEST.md`.

## 10. What could still make this design wrong

Stated plainly, because none of it is settled:

- ~~**Room and portal culling may dominate the frustum.**~~ **RETIRED
  2026-08-22.** It produced its symptom — the blue edge band in `14` — before any
  of 3c was written, and the fix turned out to be the engine's own FOV setter.
  See `17` and its addendum. Original text follows.
- **Room and portal culling may dominate the frustum.** If GoldenEye's visibility
  is driven more by room adjacency than by the projection matrix, widening the
  frustum will not produce the missing geometry and gate 3c fails with no obvious
  fix. This is the single biggest risk in the design.
- **Shared depth may not survive two eyes.** §3.3 gives reasons to expect it will
  and a specific symptom if it does not.
- **The eye passes may not fit the frame budget.** Doubling render passes on top
  of interpolation's existing multiplier could exceed 90 Hz on dense levels. RT64
  upscales, so per-eye resolution is a knob (`09`) — tunable rather than fatal.
