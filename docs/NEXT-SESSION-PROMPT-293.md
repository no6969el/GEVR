# NEXT SESSION PROMPT — `293`

Read `repo\docs\00-STATE.md` (esp. §5 dead theories, §6 traps, §7 the engine facts — **two of them
are new and they are the whole of `292`**), then **`repo\docs\292-THE-EYE-LOOP-IS-WRITTEN-AND-BOTH-POOLS-ARE-SIZED-FOR-ONE-VIEW.md`
§5a IN FULL**, then `repo\docs\RUN-SHEET-292.md` §8, and `255` §1/§4. Same rules as always. Reads
from the bridge are not free (§6): `git log`, `git show`, `git diff <path>` are safe; `git status`
and `git add` are **NOT**, and **a bare `git diff` in the decomp prints 2,101 lines of CRLF churn —
always give it a path list.** The build, every run and every commit are the owner's, main PC — you
write and validate OFFLINE, then supply complete copy-paste command blocks (§7a).

**`292` IS BUILT AND RUN. DO NOT RE-RUN S1/S2 AND DO NOT REDESIGN THE EYE MODEL.** S1 (knob off) is
green and the shipping path is untouched. S2 caught three faults and all three are fixed and
committed. The offline harness reads **`47/47`** — including a real-header gate that parses all five
touched files with `build_windows.ps1`'s own flags — and `verify` reads **`15/15`**; nothing under
`getv/port/` needs regenerating. Confirm on the bridge if you want
(`bash getv/tools/stereo_harness.sh`, `bash tools/fetch-thirdparty.sh verify`, `git log`).

---

## ►►►► THE FIRST JOB, AND IT IS NOT THE GUARD ◄◄◄◄

**`[MEASURED]`, one frame, ZERO separation, byte-identical projection matrices in both eyes:**

```
eye 0 pass:  1060 triangle commands, 1940 vertices
eye 1 pass:   622 triangle commands, 1355 vertices
```

**THE TWO EYES ADMIT DIFFERENT GEOMETRY.** The cameras are identical, the matrices are identical,
the scissors are correct halves, the pools do not overflow (`unresolved=0`). The only thing that
differs is the **viewport rectangle**, and something in room admission or the portal traversal reads
it. **Find out what. That is `293`.**

**Everything else in `292` §5a is downstream of this.** Fault 3 — the saturated matrix — happens
*because* a model reaches the alpha pass in one eye without the opaque pass that rebuilt its
matrices. Fix the divergence and fault 3 may not need a repair at all. **Do not start from the
guard.**

**`GETV_STEREO_MTXGUARD=2` SUPPRESSES A SYMPTOM AND MUST NOT SHIP.** It is a falsifier. It proved
the diagnosis (`already-converted=88520/183808`, every hit `eye=1`; then `skipped=381767` and
`[REPORTED]` *"both eyes showed better"*) and its job is done. **The repair it stands in for — who
owns `model->render_pos` per eye — is a DESIGN DECISION THAT HAS NOT BEEN MADE. Do not make it by
accident.**

**AND `258`'s ROUTE RESTS ON AN ASSUMPTION THAT IS NOW FALSE.** `258` §1 nests the eye loop in
`lvlRender`'s body because split-screen already drives that body N times. `292` §6's `[INFERRED]`
that the body survives being driven twice is **RETRACTED**: it does not, because
`bondviewTransformManyPosToViewMatrix` is an **in-place `f32`->`s32` fixed-point conversion**, not a
transform, and `model->render_pos` is per-frame arena state (`00-STATE` §7, both new). **Whether
that is repairable inside `258`'s shape, or whether the shape has to change, is the question `293`
should be able to answer by the end. It is not answered now and must not be assumed either way.**

---

## STILL OPEN FROM `292`, NOT YET LOOKED AT

- **`dlgrab_3917.bmp` and `dlgrab_5595.bmp`** — the artifacts remaining after `MTXGUARD=2`. **Both
  are ANNOUNCED BY `run_292_S2e_guard_skip.log`, so provenance is clean** (§6, `279` §2). Nobody has
  analysed them. Their paired `.txt` dumps are the instrument, not the picture.
- **The HUD is drawn per eye in FULL-SCREEN coordinates** — the ammo lands in both halves, the clock
  straddles the seam. **Expected and out of scope** (the HUD quad is not in STAGE 6). Do not fix it.
- **S3 HAS NEVER RUN. NO SEPARATION HAS EVER BEEN APPLIED.** The gate in `RUN-SHEET-292` §5 is
  untouched, and its outcomes were written before any of this. **Do not run S3 until S2 is clean at
  zero separation** — a gate measured on a build that still diverges is not a gate.

## THE GATE, WHEN YOU GET THERE (`RUN-SHEET-292` §5, unchanged)

`GETV_STEREO=1 GETV_STEREO_OFFSET=500 GETV_STEREO_PROBE=60`. **`|measured - predicted| <= 5 px`, the
sign matches (the RIGHT eye's image FURTHER LEFT), AND the log's own 1/D ratio reads `4.000`.**
Zero disparity is `B1`; wrong sign is a swapped eye; wrong magnitude is a units error; **right
magnitude with a `1.000` ratio is a projection-only build, which is the failure that looks most like
success.** S4 (`GETV_STEREO_MODE=2`) is `B1` built on purpose, tuned to be indistinguishable at one
depth — **if S4 is indistinguishable from S3 in every respect, S3's pass must be withdrawn** (`49`).
**Do not tune the separation.** 500 is deliberately absurd; ~6 cm comes after the mechanism is
proven (`239`).

## RUN-KNOB BASELINE for anything the owner LOOKS at (§6)

`GETV_SLOTFREE=1 GETV_VSYNC=1 GETV_FPS=panel GETV_SIMHZ=query GETV_WIDESCREEN=0
GETV_WINDOW=2560x1369`, panel queried (120 Hz one desk, 180 the other — **never hardcode**).
`GETV_ROOMSCISSOR=1` (shipping) **unless the arm is specifically looking at clipping**. Gate 2
`ours: x=367.333` **MANDATES** the broken front-end menu text (OPEN item 2) — not a regression.
**Under stereo BOTH viewport lines print**: `ours: x=367.333` and `ours: x=1280`, `w=912.667` each.
Every block: `Remove-Item Env:GETV_*` first line, all knobs explicit, absolute paths, banner
verification. **And read the build's FIRST failure line, not the last error** (§6, the
force-include trap — it cost a build in `292`).

## DO NOT

Set `getPlayerCount()` to 2 · re-open the vanishing props (`getROOMID_isRendered` is DEAD, `289` R2),
the mouse turn (`258` STAGE 7), or anything in `00-STATE` §5 · consume a renderer-side pose · ship
`GETV_STEREO_MTXGUARD=2` · **plan past the first gate.**
**NOT IN `293`:** OpenXR, head tracking, hand aim, vignette, HUD quad, mirror, `gevr_xr.c`. **Aim is
STAGE 7 (`P8`). Hands+body is STAGE 8.**

## STILL OWED (unchanged — `292` opened none of these and closed none)

All of `277` §9 · `278` §6's hoist-1 read · `279` §5's amount arm · `280` §7.3's black-wall dump ·
`274` §7's CONTAMINATED gate · `287` ARM 6 the wear pass, **STILL NEVER RUN** · `289` R2's missing
`dlgrab`. **And one the owner raised in `292` and it is still unanswered: `GETV_ROOMSCISSOR=0` was
never made the default because `287` ARM 6 — the four-level wear pass that would justify it — has
never been run.**
