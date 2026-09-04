> **SUPERSEDED — read `00-START-HERE.md` first.**
>
> This was the state of play at step 3e, before OpenXR. It is kept because it is
> the clearest single record of how Phase 1 was built and why each half sits
> where it does. **It is not current**: the game now renders in the headset with
> head tracking, and slices 3f-1 through 3f-4 all postdate it.
>
> Do not take the "what works" list below as today's status.

# State of play — updated 2026-08-22 — PHASE 1 COMPLETE

## What works

`GoldenRecomp.exe` builds and runs on Windows. GoldenEye plays from the user's own
ROM, at 90 and 180 Hz, with a widened field of view driven by a VR hook.

Three things are now proven:

1. **The VR attachment model is sound.** Scaling the projection matrix inside
   `currentPlayerSetProjectionMatrix` visibly changes the world. Every later phase
   has somewhere to attach. See `03-phase0-result.md`.
2. **High framerate is achievable.** It was badly broken — geometry swimming,
   ghosting, flickering — and is now largely fixed. See `04-interpolation.md`.
3. **The whole pipeline rebuilds cleanly from a patch edit.** Edit patch → `make`
   → `N64Recomp patches.toml` → `cmake --build` produced a fresh exe end to end.
   The inner loop is written up in `07-rebuild-after-patch-edit.md`.

## Newest change — Phase 1 step 3, steps 3a to 3c (2026-08-22)

The eye split is built and the boundary has settled. Full record in `12` (design,
partly superseded), `17` (the redesign and its research), `18` (3c as built).

**Where each half lives now:**

| Concern | Owner |
|---|---|
| Culling frustum, 106 deg vertical | patch, via `RECOMP_PATCH viSetFovY` |
| Per-eye frustum and view offset | RT64 `ProjectionProcessor` |
| Two render targets | **DONE — step 3d**, measured |
| Both eyes on screen, side by side | **DONE — step 3e**, parallax confirmed |

`GE_VR_MODE_HOSTEYE` is the new default patch mode. The patch no longer builds an
eye frustum; RT64 does. `OFF`, `BINDTEST` and `STEREO` are kept as A/B partners.

**Passed on the monitor:** 3a (inert plumbing), 3b (a host-supplied view
transform reaches the geometry), 3c (the culling frustum moved to the engine's
own `viSetFovY`, and aim stayed correct at 106 degrees), the first host import,
and **3d — RT64 renders two eye images from one display list into two separate
render targets**, confirmed by pass counters rather than by eye:

```
[gevr] 60.0 fps | render passes: eye0=183 eye1=183 distinctTargets=183
```

`repo\docs\24` records why the frame-time gate this was originally specified
with would have failed a working build. Eye 1 is rendered and discarded; nothing
displays it yet. That is 3e.

Also measured: **about 3 render passes per displayed frame** from the
interpolation loop. At 90 Hz with two eyes that implies ~540 passes per second,
which is the budget Phase 2's OpenXR loop has to live inside.

Two bugs found and fixed along the way, both ours, both nearly invisible in flat
play:

- `GE_VR_MIN_ZNEAR_UNITS` was 10 units, culling whole characters at close range
  (`14`). Now 1.0, which is a pass-through.
- The drawn frustum was wider than the culled one, leaving an unrendered band at
  the screen edge (`14` addendum; mechanism in `17` addendum). 3c is the fix and
  that band is its headline gate.

Game units are now known: **1 unit is about 1 cm** (`16`), derived from the decomp
rather than guessed.

## Previous — Phase 1 step 1 (2026-08-22)

`patches/ge_vr_bindtest.c` is no longer only a bind test. It now builds a real
**per-eye asymmetric frustum**, in both the fixed-point `Mtx` and the float
`Mtxf`, with `GE_VR_MIN_ZNEAR_UNITS` enforced. Previous version kept as
`ge_vr_bindtest.c.bak` in the tree.

**Status: compiles, links, and is in the current `GoldenRecomp.exe`. It has never
been run.** Verifying it on the monitor is the next action — see
`05-going-forward.md` for what a correct picture looks like, and the closing
comment in the patch itself for what each wrong one means.

Three modes via `GE_VR_MODE`: `OFF` (counters only, the A/B control),
`BINDTEST` (the Phase 0 cot scale, kept as the cheapest proof the hook still
binds after an upstream merge), `STEREO` (default).

## Current visual state at high framerate

| Class | State |
|---|---|
| Rooms, level geometry | Stable, interpolated |
| Crates, props, scattered items | Stable, interpolated |
| Characters | Good. Vertex-interpolated |
| Bullets, effects, muzzle flash | Correct, stepped at native rate |
| Health / armour gauges | Correct, not interpolated (by design) |
| First-person gun and hands | Correct, stepped at native rate |
| Watch, front end | Untouched, stepped |

"Stepped" means it renders honestly at the game's native 30/25 Hz instead of being
guessed at. That is the deliberate fallback, not a defect.

## What is NOT done

- **No VR yet.** No stereo output, no OpenXR, no head tracking, no IPD. The
  per-eye frustum exists but only one eye is drawn, to a flat monitor.
- The two-render-target problem is untouched and undesigned. It is the real
  remaining piece of Phase 1.

## Files we own in the tree

- `patches/ge_vr_bindtest.c` — the VR projection hook (Phase 0 + Phase 1 step 1).
- `patches/interpolation.c` — six interpolation fixes, was `#if 0` upstream.
  Slice 6 (bullet impact id bands, 2026-08-22) is built but not yet run;
  pre-slice-6 version is `interpolation.c.bak2`.

Both are copied into `patches/` beside this doc, byte-identical to the tree.

## Third-party files we modified

All have backups beside them in the tree; all are captured as diffs in `diffs/`.

| File | Why | Backup |
|---|---|---|
| `lib/rt64/src/hle/rt64_game_frame.cpp` | Untagged world matrices → IGNORE, not AUTO | `.bak` |
| `tools_weaken_patched.py` | MSVC has no `__attribute__((weak))` | `.bak` |
| `lib/FindFreetype.cmake` | Upstream moved the lib path | `.bak` |
| `CMakeLists.txt` | GCC warning flags reaching MSVC | `.bak2` |
| `lib/N64ModernRuntime/ultramodern/CMakeLists.txt` | same | `.bak2` |
| `lib/N64ModernRuntime/librecomp/CMakeLists.txt` | same | `.bak2` |
| `RecompiledFuncs/funcs_*.c` (31 files) | weak → rename, see GOTCHA 9 | `.bakweak` |

`tools_weaken_patched.py` is included here in full rather than as a diff, because
its line endings were normalised and the diff is unreadable.

## Generated state that is NOT in git

These are rebuilt by the pipeline and must exist before `GoldenRecomp` will link:
`RecompiledFuncs/`, `RecompiledPatches/`, `rsp/aspMain.cpp`, `patches/patches.elf`,
`ge007.tlbfree.z64`, `N64Recomp.exe`, `RSPRecomp.exe`.

## The 29 renamed originals

`RecompiledFuncs` now defines these as `NAME__recomp_orig` so the strong
definition in `PatchesLib` wins the link (GOTCHA 9). Slice 6 added
`explosionCallRenderBulletImpactOnProp`:

```
__scMain applyRoomMatrixToDisplayList bgScissorCurrentPlayerView
bgUpdateCurrentPlayerScreenMinMax bondviewRenderGaugeBars bossMainloop
chrpropRender currentPlayerDrawFade currentPlayerSetProjectionMatrix
currentPlayerSetProjectionMatrixF explosionCallRenderBulletImpactOnProp
getPlayer_c_lodscalez getinstsize gunRenderCasings init
interface_menu00_legalscreen joyRumblePakInit modelSetDistanceDisabled
musicTrack1Play musicTrack2Play musicTrack3Play
renderGunbarrelEyeIntroSequence rmonCreateThread select_ramrom_to_play
skyRenderFull skyRenderTri strtol_recomp titleRenderFolderMenuBackgroundLines
zbufClearCurrentPlayer viSetFovY
```

Thirteen other `RECOMP_PATCH` names are deliberately NOT renamed — they sit inside
`#if 0` blocks upstream and never reach `patches.elf`, so renaming them would
delete their only definition. `tools_weaken_patched.py` filters these by
intersecting with what N64Recomp actually emitted. (Earlier drafts of this doc say
*fourteen*; that count predates the filter ever executing — the script had a
`NameError` that killed it before it ran. See `07` GOTCHA 3.)

Step 3c adds `viSetFovY`, bringing the count to **30**. If
`tools_weaken_patched.py` still reports 29 after 3c, the new patch never reached
`patches.elf` and nothing in 3c will work.

Adding code to an existing patch file does not change this list. Only adding a
new `RECOMP_PATCH` **name** does — and then the script must be re-run.
