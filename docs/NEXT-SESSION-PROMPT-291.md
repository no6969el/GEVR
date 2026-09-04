# NEXT SESSION PROMPT — `291` — **RUN THE POSE SPINE, THEN STAGE 6 (STEREO). VR WORK.**

**EFFORT LEVEL: HIGH.** `290` WROTE and OFFLINE-VALIDATED the pose spine (`258` STAGE 5) but did
NOT build or run it — rule `1`, the build is the owner's, main PC. `291`'s first job is to make
`290` real: build it, gate the binary, and RUN its three arms (A1 identity / A2 round-trip / A3
self-falsify). **If A2 reads `VERDICT PASS` and A3 reads `VERDICT PASS (detector fired)`, the pose
is proven fresh on the live path and STAGE 6 may consume it.** Only then, STEREO.

**WHY STEREO IS UNBLOCKED THE MOMENT `290` IS WORN:** `258`'s load-bearing ordering claim is that a
sim-owned pose must exist BEFORE the eye loop, or the eye path is built against a renderer-side pose
and reworked (`194`: one missing term, four faults). `290` gives STAGE 6 `gePoseCurrent()` to read.

---

## PASTE THIS

Read `repo\docs\00-STATE.md` and `repo\docs\258-THE-ROUTE-THE-ENGINE-ALREADY-RENDERS-N-VIEWS.md` §1 and STAGE 6, and `repo\docs\RUN-SHEET-290.md` §0-§7. Same rules as always. Reads from the bridge are not free (§6): `git log`, `git show`, `git diff <path>` are safe; `git status` and `git add` are NOT.

**FIRST, MAKE `290` REAL — IT IS WRITTEN AND OFFLINE-VALIDATED, NOT BUILT, NOT RUN.**
1. **Confirm `290`'s three commits are in** (`git log`): `vendor/ge-decomp` = the pose spine, staged BY EXPLICIT PATH LIST at `318 insertions / 0 deletions / 3 files` (`lv.c 12+`, `posespine.c 237+`, `posespine.h 69+`); `goldeneye-native` = the harness; `GoldenEyeVR` = the docs. **If the decomp is uncommitted, say so first.** No regen is owed — `290` touched nothing under `getv/port/**`, so `tools/fetch-thirdparty.sh verify` must read `15/15` before AND after.
2. **Re-run the offline falsifier before trusting anything:** `getv/tools/posespine_harness.sh` must read `10 passed, 0 failed` (`-Wall -Wextra -Werror` clean). It compiles the REAL `posespine.c`, so it can never test a stale copy.
3. **Build (main PC), gate the five strings in the exe** (`RUN-SHEET-290.md` §1), then **run A1/A2/A3** exactly as `§4`/`§5`/`§6` write them. **Every command block carries all knobs, absolute paths, `Remove-Item Env:GETV_*` first line, banner verification.** `GETV_SIMDIV=1` is the pose instrument's run condition (§3) — gate on `props interpolated 0` + zero `simulation held to` or the report is VOID.

**EVERY COMMAND BLOCK CARRIES ALL OF THESE, because a block that omits a knob silently restores its default:**
`GETV_SLOTFREE=1 GETV_VSYNC=1 GETV_FPS=panel GETV_SIMHZ=query GETV_SIMDIV=1 GETV_WIDESCREEN=0 GETV_ROOMSCISSOR=1 GETV_WINDOW=2560x1369`
**`290` chose `GETV_ROOMSCISSOR=1` (shipping default) because the pose test reads the LOG, not the picture, and 291 stays with that unless it is looking at clipping.** Gate 2 is `ours: x=367.333` and MANDATES the broken front-end menu text — OPEN item 2, by construction, not a regression; moving to `1825x1369` prints `ours: x=0` and silently breaks the gate (rule `17`). `GETV_FPS=panel` queries the panel (120 Hz on one desk, 180 on another — never hardcode a rate).

**IF A2 FAILS:** read `RUN-SHEET-290.md` §7 — a `lag=1 STALE` in A2 means the `gePortPoseBeginFrame()` seam in `lv.c` is bracketed after the tick (the `267`/`271`/`272` error in a new place). Fix the seam, NOT the instrument. A large `err` with `lag=0` means the pose is written and never read — the accessor or the static state. **Do not build STAGE 6 on a pose spine whose A2 is not green.**

**THEN STAGE 6 — STEREO. `P2`, `P3`. THE EYE LOOP AT `lvlRender`.** Nested INSIDE the per-player body (never `getPlayerCount()`, `258` §1.5), taking its per-eye view from `gePoseCurrent()` and REPLACING the projection at `viSetupCurrentPlayerView` (`fr.c:696`, the single build site, already carrying a `GE_PORT_NATIVE` block) with **four tangents per eye, per frame** (`P2` — `guPerspective` cannot express an off-centre frustum). **The eye TRANSLATION goes in the VIEW matrix** (`255` §1); row-vector vs column-vector and the negative-yaw trap are in `00-STATE` §7 — read them before any matrix is written. The decomp's `quaternion.c`/`.h` is there for the composition. **THE GATE NEEDS NO HEADSET** (`255` §4): desktop side-by-side, `GETV_STEREO_OFFSET=500` (deliberately absurd; ~6 cm tuned after the mechanism is proven), halves cross-correlated, `PREDICTION:` in pixels written to the log BEFORE the screenshot. Report the cost against `272`'s Cradle baseline (CPU 0.890 ms + GPU 0.832 ms vs 11.111 ms). **NOT in STAGE 6:** OpenXR, head tracking, hand aim, vignette, HUD quad, mirror, `gevr_xr.c`.

**WHAT `291` MUST NOT DO.** Do not set `getPlayerCount()` to 2. Do not re-open the vanishing props (`getROOMID_isRendered` is DEAD, `289` R2) or the mouse turn (it is `258` STAGE 7, not rendering). Do not reopen anything in `00-STATE` §5.

**STILL OWED (unchanged): all of `277` §9 · `278` §6's hoist-1 read · `279` §5's amount arm · `280` §7.3's black-wall dump · `274` §7's CONTAMINATED gate · `287` ARM 6 the wear pass, STILL NEVER RUN · `289` R2's missing `dlgrab`.**

Start by confirming `290` is committed and its harness is green. Do not plan STAGE 6 past its first gate (the no-headset side-by-side).
