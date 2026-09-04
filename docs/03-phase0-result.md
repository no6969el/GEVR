# Phase 0 result — the hook reaches the world projection

**2026-08-22. PASS.** First successful run of `GoldenRecomp.exe` on Windows with
`patches/ge_vr_bindtest.c` compiled in.

## What was tested

The bind test replaces both projection setters and scales `[0][0]` and `[1][1]` —
`cot(fovy/2)/aspect` and `cot(fovy/2)` — by a constant. Nothing else in the matrix
depends on fovy, so near, far, the W row and perspNorm stay provably intact. The
only two images it can produce are "wider" and "identical", which are exactly the
two Phase 0 needs to tell apart.

Run at `GE_BT_COT_SCALE = 0.3f` (~125–145° vertical, unmistakable) rather than the
default `0.625f` (~85°), so the result could not be a trick of memory.

## Result

**The world visibly widened.** VR-PLAN §2's attachment model is sound:
`currentPlayerSetProjectionMatrix` / `...MatrixF` do govern the projection that
reaches the RSP. Every later phase has somewhere to attach.

## The unasked question it also answered

**The menus widened too.** At 0.3 the file-select options were covered by an
overlay stretched past its scissor box.

Cause, confirmed by scanning all 60 `RecompiledFuncs` translation units: both
setters have exactly **one** caller, `viSetupCurrentPlayerView`. The front end is
drawn through the same player view as the world. There is no narrower hook to
move to.

So the world/UI separation has to come from **game state**, not from a different
hook site. `ge_vr_bindtest.c` now gates on
`g_StageNum != LEVELID_NONE && g_StageNum != LEVELID_TITLE` (values from
`patches/structs.h`: -1 and 90), which leaves the front end alone.

This is a good outcome for VR, not a bad one — a single chokepoint governs the
entire world projection, which is precisely what a stereo pair needs.

Not covered by the gate: the in-level pause menu and watch, which run with a
level loaded. Deliberately left distorted, since Phase 3 re-renders those as
world-space panels and gating them now would be work thrown away.

## Blocker found for later phases: frame interpolation is unimplemented

Above the native 30/25 Hz, objects and characters slide around as the camera
moves.

RT64 interpolates between game frames using matrix-group tags that the port must
attach to each thing it draws — saying *this* interpolates, *this* is UI and must
not. cblock85's fork defines the whole macro family in `patches/patches.h`
(`gEXMatrixGroupDecomposed`, `gEXMatrixGroupInterpolateOnlyTiles`, and a dozen
more) and has **zero call sites** across all ten patch files. `interpolation.c`,
the file whose entire job this is, is wrapped in `#if 0` around a single function.

Consequence: nothing is tagged, so above native framerate RT64 has no idea what
should move smoothly.

This is a hard blocker for VR specifically — VR needs high framerate far more
than flat gaming does, and 30 Hz is not shippable in a headset. It is also
substantial work (the Zelda 64 recomp team spent a long time on it). Tracked
here as a Phase 1.5 item; not on the critical path to proving stereo.

## State of the tree at this point

- `GE_BT_COT_SCALE` back to `0.625f`, stage gate added.
- 24 recompiled originals renamed `NAME__recomp_orig` (see windows-build-notes
  GOTCHA 9); the 14 `#if 0` patches left under their original names.
- `GoldenRecomp.exe` builds and runs; assets resolve only when CWD is the repo
  root, so launch as `.\build\Release\GoldenRecomp.exe` from there.
