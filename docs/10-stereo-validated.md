# Stereo validated in the headset — 2026-08-22

**The per-eye projection maths in `patches/ge_vr_bindtest.c` is correct, confirmed
in real stereo on real hardware.** This is the result that unblocks Phase 1.

Source: `xrprobe/xr_stereo.cpp`. Session log: `xrprobe/stereo_session_log.txt`.

## What was run

A standalone D3D12 + OpenXR program that renders a wireframe test world to both
eyes and submits an `XrCompositionLayerProjection`. It touches nothing in the
recomp tree and cannot affect `GoldenRecomp.exe`.

Critically, it builds its projection **the same way `geVrBuildProj()` does**:

```
sx = 2 / (tanRight - tanLeft)                    -> [0][0]
sy = 2 / (tanUp    - tanDown)                    -> [1][1]
ox = (tanRight + tanLeft) / (tanRight - tanLeft) -> [2][0]   ROW 2
oy = (tanUp    + tanDown) / (tanUp    - tanDown) -> [2][1]
```

row-vector layout, shader declared `row_major` with `mul(pos, M)`, driven by live
`xrLocateViews` tangents. Only the depth row differs (D3D clips to [0,1], the N64
does not) — and the depth row is not what step 1 changes.

## The result

| Check | Outcome |
|---|---|
| Left eye tinted red, right blue | **Confirmed by wearer** — per-eye rendering is real |
| Depth perception | **Confirmed** — "I can definitely tell depth" |
| Fusion | Clean |
| Per-eye FOV | Correctly mirrored: L `-53.99/+46.01`, R `-46.01/+53.99` |
| Per-eye pose separation | 63 mm, matching measured IPD |

The tint test is the one that matters and it is worth keeping in the toolbox. A
monoscopic image with correct perspective looks *exactly* like working stereo —
it fuses, it looks like a room, it survives head movement. Parallax judgement
alone could not settle it: the first attempt drew "the cubes did not shift" from
the wearer, which was a true observation of a working stereo scene whose objects
happened to be far away. **A full-screen per-eye colour cannot be faked by correct
perspective.** Use it first, not last.

## What this proves, and what it does not

Proven:

- OpenXR instance, system, D3D12 graphics binding on the runtime's chosen
  adapter, per-eye swapchain creation at 4140 x 3292, per-eye rendering,
  composition layer submission, and pose-driven view matrices all work on this rig.
- The asymmetric frustum formula and its row-2 skew placement are correct in
  stereo. A transposed skew would shear; a per-eye offset that failed to reach the
  view matrix would give correct tint but flat depth. Neither happened.

NOT proven, and still the real work:

- **Nothing about RT64.** The remaining Phase 1 question is unchanged: how to get
  the game to produce two eye images. This program is the *consumer* for those
  images, and it is now known-good — which converts Phase 2's frame loop from
  "unwritten" to "written and validated, awaiting a producer".

## GOTCHA — the rig's floor calibration is wrong, and it is not cosmetic

SteamVR reports the head **2.4 to 3.2 m above the floor plane**, while horizontal
position sits within 3 cm of the STAGE origin and is stable to centimetres. That
is a fixed calibration offset, not tracking drift.

It actively sabotaged this test: every object sat 2.3 m+ away, disparity collapsed
to roughly 1.6 degrees against 9 degrees for the wearer's controllers, and the
first stereo read came back as "the cubes did not shift". It also inverted the
apparent size ordering of the depth cubes, since a viewer 2 m above a row of
receding objects sees the far ones subtend the larger angle.

**Fix the SteamVR room setup before further VR work.** Phase 4 is entirely about
scale, seated recentre and comfort, and GoldenEye's world units already vary per
level (`room_data_float2`). Calibrating game scale against a floor that is over a
metre out would bake the error in permanently.

## Two process lessons worth keeping

**Anchor on FOCUSED, not on the first frame.** The scene was first pinned to the
head position on frame 0. Frames begin rendering at session state VISIBLE, which
occurs while the headset is still in the wearer's hand — it anchored at y=2.42
while the wearer settled at y=3.19, putting the whole scene 0.8 m below eye level.
`XR_SESSION_STATE_FOCUSED` is the state that means "worn and receiving input".

**Log head position every second.** Two wrong explanations were produced and
discarded in this session purely because the telemetry contradicted them — first
"the wearer is standing back from the origin" (they were 3 cm from it), then the
anchor timing. Subjective reports from inside a headset are necessary but not
sufficient; the numbers arbitrate. The logging is now permanent in `xr_stereo.cpp`.

## Running it

```
cd C:\Users\<USER>\Desktop\ge-vr-xrprobe
xr_stereo.exe          # normal
xr_stereo.exe tint     # left eye red, right eye blue — the stereo proof
```

Build line is in the file header. Needs `openxr_loader.dll` beside the exe, and
`shell32.lib` / `user32.lib` on the link line as well as the obvious ones.

## Where this code belongs

`xrprobe/` is host-agnostic and has no dependency on the recomp tree. It belongs
in **`goldeneye-native`** (the MIT repo) alongside `phase0/`, not in
`GoldenEye64Recomp`. Move it when that repo is restored from the bundle — see
`08-where-everything-comes-from.md`.
