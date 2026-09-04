> # ►►►► SUPERSEDED 2026-09-04 BY `PRIORITY-BOARD-306`. KEPT IN FULL, RULE `2`. ◄◄◄◄
>
> **This board was written at the end of `299` and edited in place through `303`, `304` and `305`.
> `PRIORITY-BOARD-306` is the current one** — it carries every open item forward, adds **GROUP `V`
> (the ordered route from here to a headset)**, **GROUP `X` (the XR layer, which does not exist
> yet)** and **`H16`**, and it records the score from `299` to `306` in one table.
> **Nothing below is deleted and nothing below is current.**

# PRIORITY BOARD — WRITTEN 2026-09-03, END OF `299`

**HOW TO USE THIS.** Each group below is a **session's worth of work** and they are ordered, but
they are **not a chain**: a session can take any group whose PRECONDITION is met without touching
the others. Every item says its effort, its precondition, and **what would make it not worth
doing** — because the most expensive thing this project does is run an arm that could not have
answered anything (`279` §7, and it has now happened four times).

**EFFORT IS THE OWNER'S TIME, NOT THE ASSISTANT'S, AND THE TIERS ARE DEFINED SO THEY ARE NOT
VIBES:**

- **`LOW`** — offline only, **or** one short run with **no build** and no new analysis. Minutes.
  The gate is a line in a log.
- **`MEDIUM`** — a build, **or** a run plus real analysis (a census to reconcile, a script to
  sweep, two arms to compare). One sitting.
- **`HIGH`** — a design decision, a wear session, or work whose scope is not yet bounded. **A
  `HIGH` item should not be started at the end of a session.**

**`LOW` DOES NOT MEAN UNIMPORTANT.** `H1` is one character and it is why every disparity
measurement this project has taken needed a manual sweep to be trustworthy.

---

## GROUP A — **LAND `299`'s BUILD.** Precondition: none. **PARTLY DONE.**

**►► A1 AND A5 ARE DONE, 2026-09-03.** The gates, the regen and the build were worn
(`goldeneye.exe` 18,062,771 bytes at 02:40, `59` port-layer objects, 0 failed, `ge_depthclamp.o`
linked with all three symbols) and all three repos are committed — `fe93821` / `6f24ddc` /
`77f67e26`, with `verify` `15/15` after. **A2, A3 and A4 have NOT run and the fix is entirely
untested.**

| # | task | effort | note |
|---|---|---|---|
| ~~A1~~ | ~~gates, regen, build~~ | — | **DONE.** `299` §9.6. Do not re-run |
| ~~**A2**~~ **DONE 2026-09-03, `301` §5 — AND THE FIX WORKS** | ~~D1/D2, `GETV_DEPTHCLAMP` 1 vs 0~~ **`[REPORTED]` D1 artefact GONE, D2 artefact PRESENT — row 1 of §5.3. `299` §8.1 CLOSES.** Census agrees: D1 `straddle=15900 clamped=0`/far `clamped=0`; D2 `clamped=13930` = `straddle+all_near` exactly | ~~MEDIUM~~ | **THE FAR FIELD WAS NEVER READ — `302` §4.** And GATE 3 must be normalised: D1 ran 14% longer, `straddle` 341 vs 340 per Mvtx = same place |
| ~~**A3**~~ **DONE 2026-09-03, `301` §6** | ~~the filtering arm~~ **`GETV_FILTERING=0 -> filtering=0`. The precedence fix took; `H4`'s named offender is closed at the mechanism** | ~~LOW~~ | **The blur question it was asked for is still OPEN and still MEDIUM:** magnification of a low-res texture, or a wrong texture size? |
| ~~**A4**~~ **DONE 2026-09-03, `301` §7 — HALF ANSWERED, AND IT SPAWNED `A5`** | ~~read `flag=`/`type=`~~ **`flag=0` on ALL 541 skipped frames, `type=1` on all of them.** `chrprop.c:476`'s comment is NOT falsified. Dead block `1083-1454` (372) starts EXACTLY at `bgLoad`; `372+169` = `299`'s ~541 to the frame | ~~LOW~~ | **`type` stood for SIX prop types and they disagree.** GROUP B is unblocked but `B1` is only half answered |
| ~~**A5**~~ **DONE 2026-09-03, `302` §3 — `viewer=541`, EVERY OTHER BUCKET ZERO** | ~~read WHICH of the six skip buckets fires.~~ **And the "benign" reading is DEAD: eye0 `MODEL_MTX=38` vs eye1 `0`, strict subset. `B2` IS REAL, scope one type. `303` §3 is the A/B** | ~~LOW~~ | **►► A6 IS THE NEXT THING: `303` §4, the far clamp.** `302` §4 measured `beyond_far` **13.2%** and the owner's distance is flickering — ORIGINAL ROW: **`RUN-SHEET-302` §3: read WHICH of the six skip buckets fires on the dead block.** The split is WRITTEN and gated offline (30 checks, 0 failed); `302` §2 is the build | **LOW to read, and it is the NEXT THING** | **One run. `viewer=` RETIRES `B2` and re-opens the dead eye elsewhere; `explosion=`/`smoke=` makes `B2` real; `player=`/`nul=` means the prose is wrong about what the branch does.** `B1`/`B2` are NOT actionable until this reads |
| ~~A5~~ | ~~commit all three repos~~ | — | **DONE.** `RUN-SHEET-300` §7.5 |

**►► GROUP A NOW REQUIRES `RUN-SHEET-301`'s BUILD FIRST (owner's decision, 2026-09-03).** A2/A3/A4
read the very counters `301` repaired; running them on the `02:40` binary would take verdicts
through instruments now known to misreport, which is what `298` did. **The binary gate is no
longer a constant in prose** — `301` §3c records the hash and every arm throws on a mismatch, so
this group needs no re-editing after any future build.

**NOT WORTH DOING IF:** you are tempted to re-run `RUN-SHEET-300` §1-§3. They are worn and committed; re-running
the build only moves the exe's timestamp and invalidates the `299` §9.6 figures every later doc
cites.

## ~~GROUP B — **THE DEAD EYE IN THE LEVEL'S OPENING.**~~ **►►►► CLOSED 2026-09-03, `303` §2. THE WHOLE GROUP. ◄◄◄◄**

**`[MEASURED]` V1: eye1 `MODEL_MTX` **38** against V2's `0`, `MODEL_VTX` 16/16, `MODEL_COL1` 19/19, `only in eye0 = 0` AND `only in eye1 = 0` on every opening grab, cumulative `viewer=0`, ZERO-REBUILD **0 of 3015**, and NOT ONE FRAME WITH `skipped>0` IN THE ENTIRE RUN.** `[REPORTED]`, the owner: *"Yes it does and it loads better than before without all that texture in the left eye"* — **gone, not reduced.** V2 reproduced `302` exactly, so the A/B is not void. **The fix is `GETV_STEREO_REBUILD_VIEWER`, default `1`, committed in `94cdf01c`.**

**►► DO NOT REOPEN THIS GROUP FOR `303` §5's ONE-EYE POLYGON.** That fault is in frames whose census is `39/39` with `only in eye0 = 0` — **it is not an admission loss and this group was entirely about admission.** It belongs to GROUP `C`'s rewrite, below. ORIGINAL HEADER, KEPT BECAUSE RULE `2` DELETES NOTHING: Precondition ~~A4~~ ~~A5~~ BOTH DONE. **HIGH.**

`299` §8.2/§8.3: for ~541 deterministic frames at the start of every level the second eye receives
no models. **This is the first thing a player sees, every level, and it is the symptom this project
exists to remove.**

| # | task | effort | note |
|---|---|---|---|
| ~~B1~~ **DONE, `303` §2** | ~~Decide what to do about the skipped prop once A4 says which branch fires~~ **HALF DONE: it is the `type=` branch, `flag=0` on all 541 frames, so no source comment is falsified. The rest waits on A5** | HIGH | **`301` §7.** The remaining half is WHICH type — and one of the six (`viewer=`) means B2 should not exist |
| ~~B2~~ **DONE, `303` §2 — IT WAS REAL AND ITS SCOPE WAS EXACTLY ONE TYPE.** `bondviewRenderProp()` (`bondview2.c:11666`) forwards a viewer with a chr to `chrRenderProp()`, so it consumes exactly what `chrBuildRenderState()` produces | ~~If `type=`: extend the rebuild to the excluded types, or prove they cannot matter~~ | ~~HIGH~~ | **►► NOT YET A TASK — A5 may RETIRE IT.** And item 4 names three types; **the `else` branch excludes FIVE plus a default** (`PROP_TYPE_PLAYER`, `PROP_TYPE_NUL`). **A design decision, not a patch** |
| ~~B3~~ **DONE by V1's own grabs, `303` §2** | ~~Re-measure with `REBUILD_REPORT=1` and grabs INSIDE the opening frames~~ | ~~MEDIUM~~ | `299` §8.2's method, now that it is known where to point it |

**NOT WORTH DOING IF:** ~~A4 has not run~~ **A5 has not run.** `301` settled `flag=` vs `type=`; it did
NOT settle which of the six types, **and one of them retires `B2` entirely. Do not inherit a guess
about which — that is the same error one level down.**

---

## GROUP C — **REWRITTEN 2026-09-03: THE ONE-EYE POLYGON, AND THE `NaN` HYPOTHESIS IS DEAD.** Precondition: none. **HIGH.**

**►►►►►►►► READ THIS FIRST, 2026-09-03, `305`. THE DISPLAY LIST IS NOW EXHAUSTED AS A PLACE TO LOOK FOR THE POLYGON.** Four levels are excluded BY MEASUREMENT: admission (`303` §5), the matrix conversion (`303` §4), the arena (`305` §1.2 -- `MODEL_VTX fresh=0` on ALL FOURTEEN dumps, clean and polygon alike, so it is a constant and not a finding), and the ORDER (`305` §1.5 -- `dlgrab_dlorder.py` reads `C1_2336` and `V1_2732` ORDER-IDENTICAL). **Every one of those is something `GETV_DLGRAB` RECORDS, and it records `w0`/`w1`: opcodes and ADDRESSES. Nothing in this project has ever read a per-eye buffer's CONTENTS, and two eyes can issue byte-identical commands naming per-eye matrix buffers whose VALUES differ. That is the next instrument; `305` §4 deliberately does not design it (`301` §0, the count is five).**

**►►►► AND `4676` IS NOT `2336` AT AMPLITUDE. IT CARRIES A SECOND, SEPARATE, HARMLESS DEFECT.** `305` §1.3/§1.4: an eight-call CYCLIC ROTATION BY THREE at DL span `[29..36]`, which `dlgrab_eyecensus.py` cannot see because it compares call targets as a **SET** (`:96-97`). The rotation is real, structural (same span on two binaries and two address spaces) and **PRE-`303`** -- `dlgrab_2928` and `dlgrab_2957`, announced by exactly one log, `279` §2 satisfied. **AND IT DRAWS NOTHING: both read `total 0 px  blobs 0`.** Do not spend a run on it. `RUN-SHEET-305` §2 bounds that null.

**►►►► READ THIS BEFORE THE TABLE. `303` §4 KILLED THIS GROUP'S LEADING HYPOTHESIS AND `303` §5 GAVE IT A NEW SYMPTOM WITH A PICTURE.**

`C1` (`GETV_STEREO_MTXGUARD=1`) reads **`arrays=366456 already-converted=0 skipped=0`** against `292`'s 88,520/183,808 and `299` E2's 11,902/144,716 on a comparable arm — **upstream 2.5x larger, so it is a result, not a masked zero** — and the instrument printed its own pre-registered null: *"already-converted=0 means the saturated matrix came from somewhere else and this diagnosis is WRONG -- do not keep it."* **`292`'s double conversion is dead on the `303` binary and the `NaN` may have gone with it.**

**AND THE LIVE SYMPTOM IS NOW A PICTURE, NOT A COUNTER:** a flat slate polygon occludes wall geometry **in ONE eye** in `dlgrab_V1_2732`, `dlgrab_C1_2336` and `dlgrab_C1_4676`, in frames whose census reads `MODEL_MTX 39/39`, `MODEL_VTX 17/17`, **`only in eye0 = 0` AND `only in eye1 = 0`**. **Same commands, different picture — the first eye fault this project has that is NOT an admission fault.** `[REPORTED]`: *"bond bobs and it changes the output."*

ORIGINAL HEADER, KEPT BECAUSE RULE `2` DELETES NOTHING: **GROUP C — THE `NaN` NOBODY HAS LOOKED AT.**

`299` §8.4: `already-converted=11902` of `144716`, **every hit `eye=1`, and most of them `m[0][0]=nan`**
with `m[3][3]` values like `-5.07e30`.

| # | task | effort | note |
|---|---|---|---|
| C1 | ~~Establish where the `NaN` comes from~~ ~~**RESTATED: establish what draws `303` §5's one-eye polygon.** Start at `dlgrab_C1_4676`~~ **RE-AIMED 2026-09-03, `305`: `4676` IS THE WRONG FRAME TO START AT -- its extra defect is measured, dated and harmless. Start at `dlgrab_C1_2336`, which is the polygon with NOTHING else in the frame (order-identical, content-identical, every difference a `w1` rebase), and build the per-eye CONTENTS read that `305` §4 names.** | HIGH | **BOTH INHERITED EXPLANATIONS ARE EXCLUDED BY MEASUREMENT: not the double conversion (`303` §4), not an admission loss (the census on those frames).** `4676` diverges BROADLY — 900 blobs, 44,252 px, alignment `mad` 6.409 against every other frame's 3.4–4.1 — where the other two carry one polygon. **Do not inherit a guess; that is the error one level down** |
| C1a | Re-run `GETV_STEREO_MTXGUARD=1` on a route that reaches more of the level, to bound `303` §4's absence | **LOW** | `C1`'s zero is established on ONE run and ONE route. **It is not a proof about every route** and the board must not read it as one |
| C2 | Decide who owns `render_pos` per eye | HIGH | `292` called this *"a design decision"* and deferred it. ARM 3 answered half of it |

**NOT WORTH DOING IF:** you are tempted to treat C1 as part of `292`. **It is not** — `292`'s knob
observes both and the documents have only ever discussed one.

---

## GROUP D — **THE STEREO GATES THAT HAVE NEVER RUN.** Precondition: A1 — **MET 2026-09-03.** **MEDIUM** (D1 is LOW).

Still owed from `297`, and every block is spliced in full in `RUN-SHEET-299`.

| # | task | effort | note |
|---|---|---|---|
| D1 | R3, pairguard with ARM 3 on (`RUN-SHEET-299` §3) | **LOW** | **Read its warning before celebrating its zero** — with ARM 3 on, a zero means the fault cannot occur |
| D2 | **R4 / S3, the separation gate (`RUN-SHEET-299` §4). NEVER RUN.** | **MEDIUM** | **Its 4.1 gate must pass first: `only in eye0 = 0` on the grabbed frame.** `DLGRAB_AT=5400` is past the dead window |
| D3 | S4, the mode-2 falsifier (`RUN-SHEET-299` §4.3) | **MEDIUM** | Not required by `297` §8, but **S3's pass cannot be withdrawn without it** (`49`) |
| D4 | R5a/b/c, ARM 3's cost (`RUN-SHEET-299` §5) | **MEDIUM** | `P5`. `R5b − R5a` does not have to be zero; it has to be KNOWN |

**NOT WORTH DOING IF:** run before A1 — **which is now done, so this group is unblocked.** The one
thing that would still spoil it is running these against a binary that is not the `02:40` one, so
every block's `Get-Item .\goldeneye.exe` line stays the first gate (`133`).

---

## GROUP E — **`[REPORTED]` AND STILL UNTESTED.** Precondition: none. **MEDIUM.**

| # | task | effort | note |
|---|---|---|---|
| E1 | Arm C's gate: *"the gun disappears on the floor"* (`RUN-SHEET-299` §6) | **LOW** | `bg.c:583`'s `getROOMID_isRendered` has **survived three arms untested** |
| E1b | The explosion texture. `298` §7 lists it as untouched and no document says what is wrong with it | **LOW** to characterise | **Nobody has written down the symptom.** Until someone does, it cannot be ranked at all |
| E2 | Bug 1 — the split down the distant facade | HIGH | `GETV_ROOMSCISSOR=0` removes it, but that knob **is not a fix** and its own comment predicts the cost. **A real fix has to widen the rectangles correctly** |

---

## GROUP F — **PRE-EXISTING CRASHES.** Precondition: none. **HIGH.**

| # | task | effort | note |
|---|---|---|---|
| F1 | The mine crash: `vtxstore.c:161` reads a tagged union as the wrong member | HIGH | `297` §12. **Two candidate corrections and they are NOT equivalent. A NULL guard is worthless — the pointer is WILD.** Proven pre-existing by `goldeneye_PARENT.exe` |

---

# HOLES — DEFICIENCIES IN HOW WE MEASURE, NOT IN THE GAME

**►► `301`, 2026-09-03, CLOSED EVERY `LOW` AND `MEDIUM` HOLE ON THIS BOARD: H1, H2, H3, H5, H6,
the H4 SURVEY, and both of `299`'s two unfiled candidates. H4's banner work and H9 remain open;
H7 and H8 were already settled. No build, no run — every one of these was worn offline, and
nine harnesses pass (six existing, three new).** `301` §1 is the account. **The next session
inherits a rebuild census it can trust, which is what GROUP B was waiting on.**

**TWO OF THESE FIXES WERE NOT WHAT THE BOARD SAID THEY WERE.** H1's filed fix ("clamp `hi`/`lo`
to `±search`") reads past the end of the row, and H3's ("print `ge_props_zsnap_n` beside
`list=`") would have printed `-1` on every frame. Both were caught by measuring before patching.
**A hole's diagnosis is not its fix, and this board should be read as the former.**

**These are why arms get scored wrong. Each one has already cost at least one cycle.**

| # | hole | effort | fix |
|---|---|---|---|
| ~~H1~~ | ~~**`stereo_disparity.py`'s peg detector has NEVER fired and cannot.**~~ **CLOSED 2026-09-03, `301`** | **LOW** | `measure()` now RETURNS the bounds it searched and the caller tests `dx` against those. **The filed fix would not have worked:** `hi` is clipped by the IMAGE EDGE, not by `search` (2560/search-800 -> `[-800,+595]`), so `lo`/`hi` cannot be clamped to `±search` without reading past the row. Demonstrated on a real `298` grab; `--selftest` now fails if the alarm goes quiet |
| ~~H2~~ | ~~**`GETV_STEREO_REBUILD_REPORT=<n>` prints ONE FRAME IN n.**~~ **CLOSED 2026-09-03, `301`** | **MEDIUM** | Window accumulators (min/max, `ZERO-REBUILD FRAMES`, `pass-never-ran`) fold in on EVERY frame, BEFORE the cadence gate, so the cadence is now a PRINT rate and never a measurement rate. **Read the new `WINDOW` line, not `SUMMARY`.** `=1` is no longer required. Arithmetic in `ge_rebuild_window.h`, driven offline by `ge_rebuild_window_harness.sh` (18 checks) against the exact `298` shape |
| ~~H3~~ | ~~**`list=` and `chr`/`obj`/`skipped` are captured at different moments.**~~ **CLOSED 2026-09-03, `301`** | **MEDIUM** | The pass's loop bound is captured DURING the pass and printed as `zsnap=`; `chr+obj+skipped` sums to that, never to `list=`, and both are labelled in the line. **The filed fix would have printed `-1` forever:** `gePropsRestoreTickZDepth()` nulls `ge_props_zsnap_n` at `lv.c:1135` and the report runs at `lv.c:1151`, after it |
| **H4** | **A knob with no banner cannot be checked.** **SURVEYED 2026-09-03, `301`; the banner work is still open** | ~~LOW to survey~~ **MEDIUM to fix** | **`getv/tools/knob_banner_survey.py` is the survey, and it is a SCRIPT so it cannot go stale.** `[MEASURED]`: **397 knobs read, 35 tier A (a `NAME=` echo in the reading file), 35 tier B, 327 tier C (silent) — 82%.** Banners added this session for the three that cost the most: `GETV_NEARCLAMP` (28 doc mentions, the named offender), `GETV_STEREO_REBUILD_REPORT` (18), `GETV_FILTERING` (16, now printing env AND effective side by side). **The remaining 324 are ranked by doc mentions in the script's output — work from that list.** ►► **THE CONVENTION IS NOW: every banner prints the FULL knob name and an `=`.** `filtering=2` could not be grepped for by anyone who set `GETV_FILTERING`, and that is exactly how two cycles were voided |
| ~~H5~~ | ~~**A re-run under the same log name destroys the arm's provenance.**~~ **CLOSED 2026-09-03, `301`** | **MEDIUM** | Two halves. **PREVENTION is one line at the top of each run-sheet block** — `if (Test-Path .\run_300_D1.log) { throw "..." }` — because the log is made by PowerShell's `*>` redirection, which the game never sees and cannot refuse. **DETECTION is in the game:** a new `[getv][run] ARM=<n> START=<utc>` line identifies the arm INSIDE the log, so two logs bearing the same ARM are a proven collision and a log that does not match its block is the wrong file. The identity no longer lives in prose above the block |
| ~~H6~~ | ~~**The bridge has no GL headers**, so `ge_depthclamp.c`'s GL path cannot be compiled offline~~ **CLOSED 2026-09-03, `301` — DECISION: VENDOR THE STUB** | **LOW** | `getv/tools/glstub/` + `depthclamp_glpath.sh` syntax-check the GL path with `-DRAPI_GL -DWAPI_SDL2 -Werror`. **Falsified before being believed:** an undeclared GL call and a wrong-arity call were both injected and both were caught. **A pass means the path PARSES, not that it is VERIFIED** — a stub agrees with whatever it was written to agree with; `glstub/README.md` says so at length and the real compile is still the gate |
| H7 | ~~**§1's offline gates have only ever been re-worn under the bridge's `gcc 11.4.0`**~~ **CLOSED 2026-09-03** — `RUN-SHEET-300` §1 ran both harnesses on the main PC before the build | **LOW** | It costs seconds. **`292`'s link wall is what it is for** |
| H8 | **Per-half texture energy cannot tell "nothing drawn" from "one huge flat quad"** — it made eye 0 look starved in `299` when it had 204 matrices | **LOW** (a rule, now recorded) — **RE-AFFIRMED `301`, no code change; it is a rule, not a defect** | Always read it beside `dlgrab_eyecensus.py`. **Neither instrument is sufficient alone** |
| ~~H9~~ | ~~**No instrument answers "is the picture right" without the owner's eyes.**~~ **CLOSED 2026-09-03, `303` §6 — AND THE FILED FIX WAS WRONG ABOUT THE IMPOSSIBILITY, NOT ABOUT THE DEFECT** | **HIGH** | *"a reference-frame differ would need a known-good frame this project does not have"* is **true of a MONO frame and false of a STEREO one**: at `GETV_STEREO_OFFSET=0` the two halves must be identical apart from the viewmodel, so **the second eye IS the known-good frame** — same run, same rig, same instant, nothing to normalise. `getv/tools/stereo_eyediff.py`, **selftest 16 checks 0 failed**, masks declared not tuned, refuses at `\|dx\| >= 8`. **CALIBRATION CORRECTED 2026-09-03 BY `304` §1: the nine-frame figure was a hypothesis and the tool had a FALSE NEGATIVE in it — it differenced LUMINANCE and scored `dlgrab_S2_1176`, a frame with a WHOLE DEAD EYE, clean at 1,329 px. Per channel, over the 256-frame corpus: clean tops out at 715 px, the smallest hit is 1,967, NOTHING lands between, and `--selftest` is 16 checks 0 failed with a check that fails on the `303` version. ORIGINAL, KEPT BECAUSE RULE `2` DELETES NOTHING: `[MEASURED]` on `303`'s nine grabs: six clean 0–207 px against 2,196 / 4,544 / 5,947 — three hits, no false positives.** **IT CANNOT SEE FLICKER** (`268` §4) and **a pass is NOT "the picture is right"** — both eyes can be wrong together |
| H11 | **`[getv][far]` prints knob-dependent `clamped` on one line with knob-independent `beyond_far`/`straddle`/`behind_eye`** | **LOW** | `N1` grew the SCENE / CLAMP ACTION split for `[getv][near]` **and the far line did not get it**. `303` §3 is what that cost |
| H12 | **`[getv][far]` is CUMULATIVE over runs that contain two scenes 15x apart, so its percentage is comparable to nothing** | **LOW** | `303` §3.1: the road runs 1.2–5.9% `beyond_far`, the cast roll 40–71%, and `302` §4's `13.2%` is neither. **A windowed accumulator, exactly what `H2` did for the rebuild census** |
| ~~H13~~ | ~~**`cmds` reads `6587 / 6580` in every grab of every stereo run — a constant SEVEN commands the second eye never gets**~~ **CLOSED 2026-09-03, `305` §1.6 — BENIGN, EXPLAINED, NO CODE CHANGE** | **LOW** | `[MEASURED]` on **all 21 dumps of `grabs_303_C1`, `grabs_303_V1` and `grabs_303_V2`**, every one identical: eye0's half ends with a **9-command target clear** — `SETZIMG RDPPIPESYNC SETOTHERMODE_L SETCIMG SETOTHERMODE_H SETFILLCOLOR SETSCISSOR FILLRECT RDPPIPESYNC` — and eye1's ends with **2**, `RDPFULLSYNC ENDDL`. **9 − 2 = 7.** The first eye clears the colour and depth targets for the second; the second closes the list. **Constant by construction and the same in `V2`, where eye1 is dead.** ORIGINAL, KEPT BECAUSE RULE `2` DELETES NOTHING: `303` §7, *"too small to be `303` §5's polygon, too consistent to be noise, and no document explains it"* |
| H14 | **`grabs_pre_298cull` is 109 BMPs with NO ADMISSIBLE PROVENANCE, and it now BLOCKS a question rather than mislabelling one** | **MEDIUM** | `304` §2. The five pre-`303` frames carrying `303` §5's signature are announced by **no log** (`2893`, `3393`, `5284`), by **five logs** (`900`), and by **a falsifier arm whose guard is supposed to fire** (`7360`, `run_295_S2a_restore_off.log`, `298` §3). **`279` §2 billed for the first time.** `N2`'s `GETV_ARM` prevents future collisions and does nothing for the files already there. **Either reconstruct provenance from the logs that survive, or accept the folder as unusable and say so in one line so nobody mines it again** |
| H15 | **`dlgrab_eyecensus.py` compares DL call targets as a SET, so a pure REORDER scores `only in eye0 = 0` and reads PERFECT** | **LOW** — closed by a sibling tool, and whether it belongs INSIDE the census is the open part | `305` §1.3. `:96-97` is `set(a['calls']) - set(b['calls'])`. `[MEASURED]` over all **256 dumps**: 168 refused (mono), 52 admission, 32 order-identical, **4 permuted** — and `dlgrab_C1_4676`, whose census four documents quote as evidence, is one of them. **`getv/tools/dlgrab_dlorder.py` is the ordered read, `--selftest` 7 checks 0 failed, and check `B` is a pure reorder that fails on any set-based implementation.** ►► **THE OPEN DECISION: fold the order check into the census, or keep two instruments.** `304` §1.2 is the precedent for editing an instrument in place; **`H8` is the argument for keeping them separate — neither is sufficient alone and a combined verdict hides which half fired.** `RUN-SHEET-305` §6 |
| ~~H10~~ | ~~**The port layer has no offline syntax gate.**~~ **CLOSED 2026-09-03, `301` — 51 of 57 files** | **MEDIUM** | `getv/tools/port_syntax_gate.sh`, using `build_windows.ps1`'s OWN `$portFlags` (the port batch's include set is NOT the game batch's — reproducing the game flags is what made this look impossible). **`port_render.c` and `gfx_pc.c` are now checked offline.** Falsified with an injected arity error and an undeclared identifier. **The six uncovered files are NAMED WITH REASONS in the script** — four need SDL enum/struct layouts a stub cannot state correctly, two need the full GL 2.x/3.x surface; a NEW port file is covered by DEFAULT and fails loudly |

---

# `299`'s TWO UNFILED CANDIDATES — **BOTH CLOSED 2026-09-03, `301`**

Recorded here because they were flagged as additions at the end of `299` and never made it onto
the board proper.

| # | hole | effort | what was done |
|---|---|---|---|
| ~~N1~~ | ~~**`[getv][far]` prints knob-dependent and knob-independent counters on one line.**~~ **CLOSED** | **LOW** | `all_near`/`straddle` are incremented at `gfx_pc.c:3755-3756` OUTSIDE `if (nc)`; only `clamped` is inside. They now print as two labelled groups on a new `[getv][near]` line — **SCENE (knob-independent)** against **CLAMP ACTION (knob-dependent)** — with the instruction to A/B them separately. **`298` §4.4 read `all_near 50 -> 548` as the clamp's price; it was the player facing a nearer wall, and the same number would have moved with the clamp compiled out.** Same family as H3: the counters were right and the LINE invited the misread |
| ~~N2~~ | ~~**`dlgrab_NNNN` is named by frame number**, so two arms from the same spot overwrite each other silently~~ **CLOSED** | **LOW** | New `GETV_ARM=<name>`: grabs become `dlgrab_D1_5400.*` and two arms at the same `GETV_DLGRAB_AT` can no longer collide. **Unset, the name is byte-for-byte what it has always been**, so `298`'s grabs on disk and every existing analysis script keep working. The sanitiser is driven offline by `ge_arm_tag_harness.c` (11 checks) including `../../etc/passwd` and a pasted `F:\Projects\...` — **this string comes out of a run sheet, and a run sheet is mostly paths.** The `298` per-arm-folder workaround still works and is now belt-and-braces rather than the only defence |

**►► `GETV_ARM` SHOULD BE SET IN EVERY RUN-SHEET BLOCK FROM `301` ONWARD.** It names the grabs
AND it is what the new `[getv][run]` provenance line reports, so it closes N2 and H5 together.
The game warns on every run where it is unset.