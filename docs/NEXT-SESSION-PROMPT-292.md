# NEXT SESSION PROMPT — `292` — **STAGE 6: STEREO. THE EYE LOOP AT `lvlRender`. VR WORK.**

**EFFORT LEVEL: HIGH.** `290` wrote the pose spine; `291` built it and RAN it — **A1 inert, A2
`VERDICT PASS stale=0 maxerr=0.000`, A3 `VERDICT PASS (detector fired)`.** `258` STAGE 5 is DONE and
`P6` holds on the live path (`291`, `00-STATE` WORKS row). **The pose is proven fresh; STAGE 6 may
now consume `gePoseCurrent()`.** This session is stereo, and NOTHING PAST ITS FIRST GATE.

---

## PASTE THIS

Read `repo\docs\00-STATE.md` (esp. §5 dead theories, §7 the engine facts), `repo\docs\258-...N-VIEWS.md` §1 and STAGE 6, `repo\docs\255.md` §1 and §4, and `repo\docs\291-THE-POSE-SPINE-IS-WORN-GREEN.md`. Same rules as always. Reads from the bridge are not free (§6): `git log`, `git show`, `git diff <path>` are safe; `git status` and `git add` are NOT. The build, every run and every commit are the owner's, main PC — you write and validate OFFLINE, then supply complete copy-paste command blocks (§7a).

**`290`/`291` ARE DONE — DO NOT RE-RUN THEM.** The pose spine is built, worn and green (`291`). Confirm on the bridge if you want (`git log`: `GoldenEyeVR` should have the `291` docs commit; `290`'s three commits `8a1adca`/`868776a`/`4014d36a` are in), but do not rebuild or re-run A1/A2/A3.

**STAGE 6 — STEREO. `P2`, `P3`. THE EYE LOOP AT `lvlRender`.** Nested INSIDE the per-player body (`lv.c:783-812`; NEVER `getPlayerCount()`, `258` §1.5 — 173 refs, 35 files, GAME LOGIC), taking its per-eye view from `gePoseCurrent()` and REPLACING the projection at `viSetupCurrentPlayerView` (`fr.c:696`, the single build site, already carrying a `GE_PORT_NATIVE` block) with **four tangents per eye, per frame** (`P2` — `guPerspective` cannot express an off-centre frustum; a stored aspect is `222` §2's 30% error). **The eye TRANSLATION goes in the VIEW matrix** (`255` §1 — projection-only is a frustum shift, not separation; that is `B1`). **READ `00-STATE` §7 BEFORE ANY MATRIX IS WRITTEN:** `guPerspectiveF`/`guLookAtF` are ROW-vector, GL/OpenXR column-vector; engine yaw is the NEGATIVE of the right-handed convention (`bondview2.c` rotates by `360 - vv_theta`). The decomp's `quaternion.c`/`.h` is there for the composition.

**THE GATE NEEDS NO HEADSET** (`255` §4): `GETV_STEREO=1 GETV_STEREO_OFFSET=500` (deliberately absurd; ~6 cm is tuned AFTER the mechanism is proven, never before — `239`), desktop side-by-side, halves cross-correlated, **`PREDICTION:` in pixels computed from THAT BUILD's own printed frustum and the offset, written to the log BEFORE the screenshot.** `REQUIRED: |measured - predicted| <= 5 px, sign matches (right eye's image further LEFT).` Zero disparity is `B1`; wrong sign is a swapped eye; wrong magnitude is a units error — three failures, three numbers. **Report the cost against `272`'s Cradle baseline: CPU 0.890 ms + GPU 0.832 ms (vs the 11.111 ms period).** The knob defaults OFF and stays reachable (`DELETE NOTHING`), one behaviour change per run (`48`).

**GITIGNORE / REGEN:** the matrix work is decomp-side (`fr.c`, `lv.c` under `vendor/ge-decomp/src` — commit BY EXPLICIT PATH LIST, never `-A`, §6 CRLF trap). If the side-by-side present forces a touch of `gfx_pc.c` or `gfx_sdl2.c` (both gitignored + regenerated, `287` §5), `tools/fetch-thirdparty.sh regen` then `verify` (`15/15`) is part of the SAME commit, Git Bash, main PC, AFTER the gate is worn — and CHECK `git ls-files` BEFORE editing any `getv/port/**` file.

**RUN-KNOB BASELINE for anything the owner LOOKS at** (§6): `GETV_SLOTFREE=1 GETV_VSYNC=1 GETV_FPS=panel GETV_SIMHZ=query GETV_WIDESCREEN=0 GETV_WINDOW=2560x1369`, panel queried (120 Hz one desk, 180 the other — never hardcode). `GETV_ROOMSCISSOR`: `1` (shipping) unless the arm is specifically looking at clipping. Gate 2 `ours: x=367.333` MANDATES the broken front-end menu text (OPEN item 2) — not a regression; `1825x1369` prints `ours: x=0` and silently breaks it (rule `17`). Every block: `Remove-Item Env:GETV_*` first line, all knobs explicit, absolute paths, banner verification.

**NOT in STAGE 6** (`258` STAGE 6): OpenXR, head tracking, hand aim, vignette, HUD quad, mirror, `gevr_xr.c`. **Aim is STAGE 7 (`P8`), a different session. Hands+body is STAGE 8.** **Do not plan STAGE 6 past its first gate (the no-headset side-by-side).**

**WHAT `292` MUST NOT DO.** Do not set `getPlayerCount()` to 2. Do not re-open the vanishing props (`getROOMID_isRendered` is DEAD, `289` R2), the mouse turn (`258` STAGE 7), or anything in `00-STATE` §5. Do not consume a renderer-side pose — read `gePoseCurrent()` (`P6`).

**STILL OWED (unchanged): all of `277` §9 · `278` §6's hoist-1 read · `279` §5's amount arm · `280` §7.3's black-wall dump · `274` §7's CONTAMINATED gate · `287` ARM 6 the wear pass, STILL NEVER RUN · `289` R2's missing `dlgrab`.**

Start by reading `00-STATE` §7 and `255` §1/§4, then design the per-eye view+projection at `fr.c:696` before writing a line. Do not plan past the first gate.
