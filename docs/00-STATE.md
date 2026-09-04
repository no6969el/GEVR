# 00-STATE — READ THIS FIRST. NOTHING ELSE, UNTIL YOU NEED IT.

**Currency: 2026-09-04 (session `309` — **OFFLINE. NOTHING BUILT OR RUN IN-GAME.** Binary
UNCHANGED, `45756E5A…3F92`, 18,070,774 bytes. **►►►►►►►► `RUN-SHEET-308` §2a IS WORN AND ITS
DIAGNOSIS IS FALSIFIED.** `stereo_disparity.py` now takes `--patch FRAC`; the ladder
`1.00 / 0.50 / 0.25 / 0.10` ran all sixteen grabs at every rung under `py`, and the mid-band
median `measured/predicted` ratio reads **`0.692`, `0.696`, `0.696`, `0.697`** — **a fifteen-fold
narrowing of the correlation band moves it by `0.005`. PATCH AVERAGING OVER DEPTH IS NOT THE
`S3b` UNDER-READ.** GATE 2a-i passed first (all 16 `dx` and `contrast` identical to `308`'s at
`FRAC 1.00`, four `S3c` refusals and no others, `--selftest A/B/C PASS` byte-identical).
**►►►► AND THE FIGURE EVERY DOCUMENT SINCE `307` REPEATED IS WRONG: THE `S3b` ERROR IS NOT
"10-13% PROPORTIONAL". IT IS A MEDIAN OF `30.8%`** (mean `28.9%`, range `12.9%`-`44.9%`, ten of
twelve between `20.1%` and `34.8%`) — the old figure was the corpus's two ENDPOINTS. **And it is
not "the error grows with disparity magnitude": it is a NEARLY CONSTANT RATIO of ~`0.69`, so the
absolute error grows as arithmetic.** `[MEASURED]` under `py`, §4 carries the retraction.
**►►►► THE TIGHTER PATCH ATE BOTH OUTLIERS: `S3b_10177` `-458 -> -302` (`1.129 -> 0.750`) and
`S3b_5400` `-16 -> -7` (`1.449 -> 0.634`); at `FRAC 0.25` ALL TWELVE lie in `0.634`-`0.814`.**
**►►►►►►►► `V3`'s ONE PASS IS NOW KNOWN TO BE UNFALSIFIABLE: `5400` reads `-16, -10, -7, -7`
across the four rungs and PASSES ±5 px AT EVERY ONE, because its prediction is `-11.04`. A gate
that cannot be failed is not a gate. `V3` / `258` STAGE 6 DOES NOT CLOSE AND MUST NEVER CLOSE ON
THAT FRAME.** **►►►► TWO CANDIDATES WERE KILLED OFFLINE BY READING, NOT RUNNING: the log's
implied eye width is `910.34`-`913.45` px over 898 lines and `stereo.c` fixes it at `912.67`, so
the tool's `half = 912` AGREES — the pixel conversion is not the error; and `frac * D` reads
`-23.3760`-`-23.3840` over 687 prediction lines, so the log's own 1/D law is exact to four
figures. **WHATEVER IS WRONG IS A CONSTANT.** **►►►► THE LIVE CANDIDATE, `[HYPOTHESIS]` AND NOT
FILED: `stereo.c:512` uses `tanw = tR - tL = 1.368534`, and the logged tangents are NOT
consistent with the eye's own `160x180` aspect — `0.577350 * (160/180) * (4/3) = 0.684267`
EXACTLY. A 4:3 term is unaccounted for. Its two candidate ratios (`0.750`, `0.667`) BRACKET the
measured `0.692`-`0.697` and NEITHER MATCHES, so it is not identified — and whether the RENDERER
uses those logged tangents was NOT checked. THAT COMPARISON IS `310`'s FIRST JOB AND IT IS
OFFLINE.** **`RUN-SHEET-308` §2b (the flat-wall run) is now MORE necessary, not less: it is the
only thing that measures the correlator's own error bar, and without one `0.667` and `0.750`
cannot be told apart.** **READ `309-THE-UNDER-READ-IS-THIRTY-PERCENT-NOT-THIRTEEN` §0, §5.1, §6.2
AND §7, THEN `PRIORITY-BOARD-309`.** `169` NEXT ID = `U-26`.**

**PREVIOUS (session `308` — **OFFLINE. NOTHING BUILT, RUN IN-GAME, STAGED OR
COMMITTED.** Binary UNCHANGED, `45756E5A…3F92`, 18,070,774 bytes. **►►►►►►►► `RUN-SHEET-308` §1 IS
WORN IN FULL AND `H1` AND `H18` CLOSE TOGETHER.** `stereo_disparity.py` now prints a `confidence
contrast` line and refuses any `dx` whose best shift beats the zero shift by less than **0.20**.
`[MEASURED]` under `py` on the main PC, all five blocks in order: GATE 1.0 reproduces
(**`S3b` min `0.286`, `S3c` max `0.122`, gap `0.164`**, the four `S3c` the four lowest with no
interleaving); the edit lands **`10 insertions / 4 deletions`, `CRLF=0`**, one path, toplevel
verified; `--selftest` reads `A/B/C PASS` byte-identical **with no traceback under a redirected
`cp1252` stdout**; and **THE PRE-REGISTERED FALSIFIER PASSES ON ALL SIXTEEN GRABS — `GATE dx: ALL
16 IDENTICAL`, `LOW CONFIDENCE refusals: 4` (all four `S3c` and nothing else), `scored grabs: 12`,
frame `5400` still `contrast 0.286` / `VERDICT PASS`.** The floor did not rescue an `S3c` frame or
kill an `S3b` one, which is `301` §0's condition for filing. **►►►► AND `V3` STILL DOES NOT CLOSE,
WHICH IS THE HEADLINE: eleven of twelve `S3b` grabs still miss ±5 px, and the ONE that passes is
the frame with the SMALLEST predicted disparity (−11.04 px) and the LOWEST contrast of the twelve —
the weakest possible evidence for the 1/D law.** `RUN-SHEET-308` §2a is next and it is OFFLINE.
**►►►► THREE DOCUMENTATION DEFECTS WERE FOUND BEFORE ANYTHING WAS PATCHED AND ALL THREE ARE §4/§6
MATERIAL: (1) THIS LINE'S PREDECESSOR WAS STALE** — `NEXT-SESSION-PROMPT-308` opens by declaring the
currency line carries `307`'s full result, and `[MEASURED]` lines 1-45 contained no `S3b`, `S3c`,
`contrast` or `308` and still ended *"READ … `RUN-SHEET-307` §1"*; **(2) `RUN-SHEET-308` §1.2 CITED
A SCORING BLOCK THAT WAS NEVER WRITTEN DOWN** — `307` §2c writes ONE grab per arm with `<frame>` /
`<frac>` placeholders, and the all-16 block was improvised live in `307`; it is reconstructed and
PROVEN in `308` §1.3 / §5.4 (both `ARM` header counts reproduce exactly, all 16 `predicted-frac`
to six decimals); **(3) `RUN-SHEET-308` §1.0's `S3c` maximum read `0.123` and it is `0.122`** —
harmless to the threshold, and it was about to be printed inside the instrument. **►►►► AND ONE NEW
TRAP, §6: A POWERSHELL `Get-Content`/`-replace`/`Set-Content` ROUND-TRIP CANNOT EDIT A TRACKED
PYTHON FILE HERE** — `stereo_disparity.py` is LF-only UTF-8 with `►`/`§` in ten COMMENT lines, and
the round-trip would have produced 293 CRLF changes and ten mangled comments. The edit was applied
as a BYTE splice by `py`, refusing unless the anchor matched exactly once. **READ
`308-THE-CONFIDENCE-GATE-IS-MEASURED-BEFORE-IT-IS-PATCHED` §0 AND §6, THEN `RUN-SHEET-308` §2a.**
**THE CURRENT BOARD IS `PRIORITY-BOARD-308`.** `169` NEXT ID = `U-26`.**

**PREVIOUS (session `307` — **`RUN-SHEET-306` IS WORN IN FULL: §1, §2, §3, §4, §5 and
§6 all run on the main PC.** Binary UNCHANGED, `45756E5A…3F92`, 18,070,774 bytes; no build. **`RUN-SHEET-306` §7 IS ALSO WORN
— `22e6b0a` (`GoldenEyeVR`, eight files) and `99d8a63` (`goldeneye-native`, the three-tool ASCII
fix, `5 insertions / 5 deletions`) are IN and both trees are clean.** `[MEASURED]` from `git log`
before this line was written, which is the rule `306` itself filed twice. **►►►► `H7`'s PYTHON
LEG IS CLOSED AND `305` IS QUOTABLE FORWARD:** `order_sweep_306_repro.txt` reads
**`admission=52  equal=32  permuted=4  refused=168`** over 256 dumps with **zero tracebacks**, the
same four permutations at the same `span [29..36]`, and `dlgrab_C1_4676` still the only one among
the fourteen `C1`+`V1` dumps; `P1`'s nine read `equal=9`. **►►►►►►►► GATE 6.1 PASSED ON
`dlgrab_S3_5400` AND IT HAD NEVER PASSED BEFORE:** `viewport loads=2`, **`only in eye0 = 0`**,
`MODEL_MTX 81/81`, `MODEL_VTX 49/49`, `MODEL_COL1 73/73`, no `DIVERGES` on any of the three,
`eyes-rebuilt=1 chr=2 obj=2 skipped=0`. **Six sessions of *"a disparity measured on an eye with no
world in it is a number about nothing"* are over — that sentence is MEASURED FALSE on a real frame
at `GETV_STEREO_OFFSET=500`.** **►►►►►►►► AND THE DISPARITY IS UNMEASURABLE WHERE IT WAS TAKEN:
THE PREDICTION IS 7.7 EYE-WIDTHS.** The log's own line at frame 5400 reads **`PREDICTION: disparity
= -7.696404 x eye_width (= -7024.25 px)`** on an eye half **912 px** wide, and **all seven grabs are
out of band** (−1500, −1500, −1694, −7024, −7023, −6498, −6202 px). **Disparity goes as 1/D, so
`separation=500` — chosen "deliberately absurd" (`255` §4) — against `RUN-SHEET-299` §4's "stand
still, facing a wall" (`D≈47`) is a PRODUCT NEITHER DOCUMENT CONSIDERED. The measurable window
existed and passed 600 frames before the first grab: frames 1380–1800, `D` 644–1933, predicted −172
to −517 px.** The instrument printed the voiding number on all 109 windows and **nobody had ever
read that line as a gate** — `RUN-SHEET-307` §2.0 is that gate. **►►►► `304` §2a CANNOT DATE THE
POLYGON: IT DID NOT APPEAR IN EITHER ARM.** `P1` (fix ON) — **nine gameplay frames ALL CLEAN**,
worst blob 15 px; `P2` (fix OFF) — **four frames with a WHOLE DEAD EYE** (`MODEL_MTX 38/0`, `only in
eye0 = 18`, strict subset) and five refused by the tool's own `|dx| >= 8` guard. **Eighteen gameplay
grabs carry no polygon; `C1_2336`, `V1_2732` and `C1_4676` remain the only three instances. What the
arms DID measure is `303` §2's fix working in GAMEPLAY and not only in the opening.** **►► AND TWO
GATES WERE WRONG, NEITHER ABOUT THE GAME: `ZERO-REBUILD FRAMES` read 2,220 of 7,636 and every one is
BENIGN** — contiguous frames 1810–4029, **every one `zsnap=0`** (empty prop list, because the owner
stood still facing a wall), `eyes-rebuilt=1`, `skipped=0`, `pass-never-ran=0` — **so the counter
cannot tell "the second eye got nothing" from "there was nothing to give it" (`H17`)**; **and
CONCENTRATION DOES NOT SEPARATE THE TWO FAULTS** — `P2_1369` reads `blobs 1`, largest **576,312 of
576,312 = 100%**, the POLYGON's signature by `304` §1.4's statistic, with a bbox covering the ENTIRE
unmasked eye. **`304` §1.4's 5%/8% dead-eye figures were measured on two OPENING frames and do not
generalise; MAGNITUDE is what separates them.** **AND THE ONE BLOCK THAT FAILED WAS THE ASSISTANT'S
AND IT FAILED TO PARSE:** `--predicted-frac <the number from the log>` — **`<` is a RESERVED
OPERATOR in PowerShell**, `00-STATE` §7a, `296` §11. **►► `307`'s OWN COMMIT IS ALSO IN: `b929c9b`, and both trees are clean.** It was made with
`COMMIT-NOW.cmd`, **which stages the whole dirty tree and picks the NEWEST `COMMIT-MESSAGE` file**
— so it landed the six intended documents **plus sixteen stray `COMMIT-MESSAGE-*.txt` files from
`303`'s era**, 22 in total. Harmless, and it means **a run sheet's path list is advisory whenever
that tool is used** (`303` §5.0), **and rule `17`'s silent-staleness shape is live in the chooser.**
**►►►► AND THE CURRENT BOARD IS `PRIORITY-BOARD-307`** — `306`'s is superseded and `299`'s
before it. **THE BOARD IS RE-NUMBERED BY EVERY SESSION THAT CHANGES IT, SO ITS NUMBER IS THE DATE
STAMP**; `V1`/`V2` are done, `V3` is half answered, `H17` and `H18` are new. **READ
`307-THE-CENSUS-GATE-PASSED-AND-THE-PREDICTION-IS-SEVEN-EYE-WIDTHS` §0, THEN `RUN-SHEET-307` §1**,
which is offline and is the pre-registered FIRST FIRING of the `H1` peg alarm on a real frame.
`169` NEXT ID = `U-26`.**

**PREVIOUS (session `306` **OFFLINE — NOTHING BUILT, RUN, STAGED OR COMMITTED BY IT**.
Binary UNCHANGED and re-verified against `EXPECTED-EXE-303.txt` this session: `45756E5A…3F92`,
18,070,774 bytes. **►►►►►►►► THREE DOCUMENTS SAID WORK WAS OWED AND THE FILESYSTEM SAYS OTHERWISE.**
**(1) `RUN-SHEET-305` §5 IS WORN:** `689b009` (native) and `e58e1f1` (`GoldenEyeVR`) are committed
and both trees are clean on every named path — **`NEXT-SESSION-PROMPT-306` opens by declaring them
absent and that sentence was already false when it was written.** `git log` is a bridge-safe read
and costs one command. **(2) ►►►► `RUN-SHEET-305` §2 WAS RUN AND IT CRASHED:** `order_sweep_305.txt`,
23:45:07Z, ends in **`UnicodeEncodeError: 'charmap' codec` on `\u25ba` — `►` — raised at
`dlgrab_dlorder.py:93`, the `PERMUTATION` verdict line**, the instant the sweep reached
`dlgrab_2928`, the corpus's first permuted frame. It classified 42 of 265 dumps and printed no
summary, **so `RUN-SHEET-305` GATE §2a has no reading at all — not a pass, not a fail.** `H7` for
the PYTHON toolchain, which was never closed. **`--selftest`'s check `B` header is the same shape,
so GATE §1a is exposed too — and so is `stereo_disparity.py:261`, WHICH IS THE `H1` PEG ALARM: the
alarm `H1` was opened to make fire is a line that could not print.** **FIXED, NARROWLY: five print
sites, `►` → `>>`, no logic touched, in `dlgrab_dlorder.py` (2), `stereo_disparity.py` (1) and
`stereo_eyediff.py` (2, the module docstring `:419` prints). Selftests re-read `7 checks, 0 failed`
and `16 checks, 0 failed` ON THE BRIDGE, WHICH IS NOT THE GATE — `RUN-SHEET-306` §1 is, and it uses
a PLAIN `py` so the run tests the fix rather than masking it. The check count stayed at SEVEN on
purpose: a gate's expected TEXT is part of the gate.** **(3) ►►►►►►►► `RUN-SHEET-304` §2a's `P1`
ARM IS ON DISK, CLEAN, ADMISSIBLE AND UNREAD:** `run_304_P1_polygon_viewer_on.log`, **`ARM=P1
START=2026-09-03T23:48:34Z`**, nine grabs in `grabs_304_P1\`, **frames 1225–1391, which is
GAMEPLAY and is GATE §2a's own requirement**, exactly one log, nine `[getv][dlgrab]` announcements
against nine files, no `EXCEPTION`, `game_exit requested`. **Four documents carry §2a as "the only
part of `304` still owed". `stereo_eyediff.py` has never been pointed at it — `RUN-SHEET-306` §3 is
that read and it costs seconds. `P2` has NOT run.** **AND THE CORPUS IS 265 DUMPS, NOT 256** —
`grabs_304_P1`'s nine — so `RUN-SHEET-305` GATE §2a's pre-registered total would have refused;
`RUN-SHEET-306` §2 splits the sweep into a 256-dump REPRODUCTION and `P1`'s nine as NEW DATA.
**►►►► AND THE SHOT-LINE OFFSET IS NOW 23 OF 23 PAIRS** (`305` §2's fourteen plus `P1`'s nine),
which is a LABEL, not an off-by-one. **►►►►►►►► `PRIORITY-BOARD-299` IS SUPERSEDED BY
`PRIORITY-BOARD-306`**, which carries every open item forward and adds **GROUP `V` — the ordered
route from here to a headset** — and **GROUP `X` — the XR layer, which `[MEASURED]` 2026-09-04 DOES
NOT EXIST: no runtime call of any kind in the tree (`xrCreateSession`, `IVRSystem`,
`ovr_Initialize` all absent) and the word `OpenXR` appearing exactly TWICE, both in comments —
`posespine.c:10` and `stereo.c:324`, the latter already stating the pose basis in the OpenXR
convention. `258` STAGE 6 excludes the layer by name.** **`258` STAGE 6's OWN EXIT GATE — `S3`, the separation gate at
`GETV_STEREO_OFFSET=500` — HAS NEVER RUN IN SEVEN SESSIONS AND NEEDS NO HEADSET (`255` §4). Its
standing objection — a disparity across an empty eye is a number about nothing — LAPSED BY
MEASUREMENT WHEN `303` §2 FILLED EYE 1, so GATE 4.1's four conditions are satisfiable for the first
time. `RUN-SHEET-306` §6 splices it with six named changes.** **`306` FILED NO FIX FOR THE POLYGON
AND THE COUNT OF WRONG FILED FIXES IS STILL FIVE.** **READ
`306-THE-SWEEP-CRASHED-ON-AN-ARROW-AND-THE-POLYGON-RUN-WAS-ALREADY-ON-DISK` §0, THEN `RUN-SHEET-306`
§1.** **►►►►►►►► `307` §1 RAN 2026-09-04 AND THE FALSIFIER FIRED AGAINST ITS OWN PREDICTION: THE `H1` PEG ALARM STAYED SILENT ON ALL FOUR SEARCHES.** On `dlgrab_S3_5400` (`PREDICTED -7019.12 px` = `-7.696404 x 912`, the frac fed correctly) the correlator returned an INTERIOR peak -- `dx +351 px` at `--search 500/800`, `+172 px` at `--search 200`, so it MOVES with `--search` -- of the WRONG SIGN (positive; `mad_best 6.250` vs `mad_zero 12.311`) instead of pegging at the edge. **A -7,019 px request did NOT force a peg: a near, dark, high-texture wall (energy 0.884) offered a spurious in-band lock and the instrument took it. `H1` IS RE-OPENED -- its alarm is now MEASURED NOT to fire where it was required to** (`307` §1, §4, `H1`). **►►►►►►►► `307` §2 RAN TOO (all 16 grabs, offline, `py`): GATE 6.1 PASSES ON EVERY FRAME OF BOTH ARMS** -- `only in eye0 = 0 / only in eye1 = 0`, all `MODEL_*` equal both eyes -- **so the census era is decisively closed.** **GATE S3 (±5 px) DOES NOT PASS AS A PAIR.** `S3b` (sep 32): all 12 signs CORRECT and magnitudes track the 1/D prediction with STRONG correlation (`mad_best` well below `mad_zero`), but only frame `5400` lands within ±5 px -- error grows with disparity magnitude (~5 px at −11 px predicted, ~52 px at −406 px), a precision ceiling not a sign error. **`S3c` (sep 500, long sightline): all four WRONG SIGN (positive) with `mad_best`≈`mad_zero` (15/17, 28/29) -- NO real correlation, and the census on those frames is PERFECT, so NOT a dead eye: a long sightline has no single global disparity and the correlator locked onto noise.** **THE 1/D LAW IS DIRECTIONALLY CONFIRMED (S3b, correct sign across D=52→1932) BUT NOT TO ±5 px; `V3`/`258` STAGE 6 DOES NOT CLOSE.** **THE CONCRETE `H1`/`H18` FIX: the disparity tool needs a CONFIDENCE gate -- `mad_best` sufficiently below `mad_zero` -- which separates `S3b` (0.15–0.38, real) from `S3c` (0.88–0.96, void); the amplitude gate alone passed all 16 and let `S3c` through.** **►► `RUN-SHEET-308` IS DRAFTED (OFFLINE): §1 the confidence gate (a RELATIVE floor -- `stereo_disparity.py:272` already refuses at `mz-mb<0.5` but `S3c` clears it; `307` §2 pins the split at `contrast` 0.20, S3b>=0.286 vs S3c<=0.123) closes `H1`/`H18` with the 16 grabs as its falsifier; §2 is the ±5 px precision thread `V3` needs. `169` NEXT ID = `U-26`.** `169` NEXT ID = `U-26`.**

**PREVIOUS (session `304` §2 **WORN — `RUN-SHEET-304` IS NOW WORN IN FULL, AND §3
AND §4 TURN OUT TO HAVE BEEN RUN AT 22:17 UTC AND NEVER WRITTEN DOWN**. Binary UNCHANGED,
`45756E5A…3F92`, 18,070,774 bytes; **no build, no run, no commit by this session.**
**►►►► `dlgrab_eyecensus.py` COMPARES DL CALL TARGETS AS A *SET*** (`:96-97`,
`set(a['calls']) - set(b['calls'])`), **so a frame whose two eyes call the same lists in a
DIFFERENT ORDER scores `only in eye0 = 0`, `only in eye1 = 0` and reads PERFECT — and
`dlgrab_C1_4676` is exactly such a frame.** Four documents quote that census as evidence.
`getv/tools/dlgrab_dlorder.py` is the ordered comparison, **`--selftest` 7 checks 0 failed** with
a check that fails on any set-based implementation. **►►►► THE REORDER IS REAL, STRUCTURAL AND
PRE-`303`:** `[MEASURED]` over **all 256 dumps** — 168 refused (mono), 52 admission, 32
order-identical, **4 PERMUTED**, and three of the four are **DL calls `[29..36]`, eight calls, a
CYCLIC ROTATION BY THREE**, on two binaries and two unrelated address spaces
(`grabs_299_E1/dlgrab_2928`, `/dlgrab_2957`, `grabs_303_C1/dlgrab_C1_4676`; the fourth is
`dlgrab_7360`, the `VIEWRESTORE=0` falsifier, inadmissible). **`2928` and `2957` are announced by
EXACTLY ONE log, `run_299_E1_percensus.log`, stereo ON / offset 0 / ARM 1 ON / ARM 3 ON —
`279` §2 satisfied, and the reorder therefore PREDATES `303` §2's viewer fix, with no run
needed.** **►►►►►►►► AND IT IS NOT THE POLYGON AND NOT `4676`'s DIVERGENCE. `2928` and `2957`
carry the identical rotation and read `total 0 px  blobs 0` — ZERO, not "under threshold" — under
`stereo_eyediff.py`.** The reorder draws nothing. **AND `C1_2336` AND `V1_2732`, THE TWO FRAMES
THAT DO CARRY THE POLYGON, ARE ORDER-IDENTICAL**, command for command, every difference confined
to the `w1` segment rebase — like the five clean `C1` frames and the six clean `V1` frames.
**►►►► SO `4676` IS NOT `2336` AT AMPLITUDE AND IT IS NOT THE REORDER EITHER: BOTH REMAINING
DISPLAY-LIST EXPLANATIONS ARE NOW EXCLUDED BY MEASUREMENT, ON TOP OF `303`'s TWO.** Admission,
the matrix conversion, the arena and the order are all dead for the polygon — **and every one of
those is something the dump RECORDS. The dump records `w0` and `w1`: opcodes and ADDRESSES. It
has never recorded a buffer's CONTENTS, and nothing in this project has ever read a per-eye
matrix VALUE.** That is the next instrument and `305` §4 deliberately does not design it.
**►► `304` §2's READS 1 AND 2 ARE NULLS, AND EACH LEFT A STANDING FACT.** The two eyes never
share the viewport or either lookat buffer — the ONLY shared `MOVEMEM` addresses are
`0386`/`0388`, `G_MV_L0`/`G_MV_L1`, the LIGHTS, static and identical in every dump of every arm
including `V2` — and the five addresses are the same on clean frames as on polygon frames, so the
read cannot discriminate. **`MODEL_VTX fresh=0` in ALL FOURTEEN `C1`+`V1` dumps, clean and
polygon alike, beside `MODEL_MTX fresh=2`/`3`: THE SECOND EYE GETS ITS OWN MATRICES AND EYE
ZERO'S VERTICES.** A constant, not a finding. **►►►► `H13` CLOSES:** the constant SEVEN is
eye0's 9-command target clear (`SETZIMG`/`SETCIMG`/`SETFILLCOLOR`/`SETSCISSOR`/`FILLRECT` + syncs)
against eye1's 2-command `RDPFULLSYNC`/`ENDDL` — **9−2=7, identical in all 21 dumps of `C1`, `V1`
and `V2`**, benign, no code change. **►►►► AND `RUN-SHEET-304` §3 AND §4 ARE DONE:** the four
`dlgrab_D3_*` files are in `grabs_302_D3\`; `run_304_FC3_road_on.log` / `run_304_FC4_road_off.log`
ran at 22:17:46Z / 22:18:34Z with both banners taking. **Their counters are read for the first
time in `305` §2a, PER WINDOW because the cumulative line is `H12`-void: the knob took at full
strength in ALL 467 windows (`clamped == straddle`), the venue WAS the road (median 1,359
clamped/Mvtx against the cast roll's 45,000), per-window `beyond_far` spans 0–21% with medians
3.81% / 5.47%, and only 3% / 7% of windows land in `304` §3's own 3.9–5.9% gate band — `H12` one
level down.** **THE VERDICT IS THE OWNER'S EYES AND NO `[REPORTED]` IS ATTACHED TO EITHER ARM.
`RUN-SHEET-305` §4 asks for one sentence about each and asks for nothing else.**
**READ `305-THE-CENSUS-COMPARES-SETS-AND-BOTH-DL-EXPLANATIONS-ARE-NOW-DEAD` §0, THEN
`RUN-SHEET-305` §1.** `169` NEXT ID = `U-26`.**

**PREVIOUS (session `303` **WORN IN FULL — GATES, REGEN, BUILD, FOUR ARMS, A FIFTH
THAT WAS NOT IN THE SHEET, AND ALL THREE COMMITS**. Binary `goldeneye.exe` **18,070,774 bytes,
sha256 `45756E5A…3F92`**, 21:05; commits `94cdf01c` (decomp) / `c26c58d` (native) / `d393860`
(GoldenEyeVR). **►►►► GROUP `B` CLOSES: ADMITTING THE VIEWER FILLS THE SECOND EYE COMPLETELY.**
V1 reads eye0 `MODEL_MTX=38` against eye1 **`38`**, `MODEL_VTX` 16/16, `MODEL_COL1` 19/19, **`only
in eye0 = 0` AND `only in eye1 = 0` on every opening grab**, cumulative `viewer=0`, **ZERO-REBUILD
0 of 3015 and NOT ONE FRAME WITH `skipped>0` IN THE WHOLE RUN**; V2 reproduces `302` exactly
(38/0, `only in eye0 = 18`, `viewer=541`, 372 of 3044). `[REPORTED]`, the owner: *"Yes it does and
it loads better than before without all that texture in the left eye"* — and that texture is
**GONE**, not reduced, and it WAS `299` §8.2's symptom, not a second one. **►►►► THE FAR CLAMP
ARM IS A `279` §7 NULL AND `RUN-SHEET-303` §0.1 IS NOT SUPPORTED.** FC1 far `clamped=81,076` =
`straddle` exactly against FC2's `0`, near `clamped=0` in both (`301` §5 intact) — **the knob took
at full strength and the owner sees the same picture in both arms**: *"They both have blur in the
far distance, but not as bad as the other test. It was a good distance then the games natural
distance fog set in"*, **in the level, down the road**. The reason is `[MEASURED]`: **`[getv][far]`
is CUMULATIVE ACROSS TWO REGIMES THAT DIFFER 15x** — the road runs 1.2–5.9% `beyond_far` and the
cast roll 40–71% — so **`302` §4's `13.2%` is a blend of two scenes and is comparable to nothing**,
and **the far clamp fires 45,000/Mvtx in the cast roll, which is FLAT COLOUR, and 50–2,300/Mvtx on
the road, which is where the owner looks.** The venue maximised the counter and minimised the
picture. **►►►► AND `292`'s DOUBLE CONVERSION IS DEAD:** `C1`, `GETV_STEREO_MTXGUARD=1`, reads
**`arrays=366456 already-converted=0 skipped=0`** against `292`'s 88,520/183,808 and `299` E2's
11,902/144,716 on a comparable arm — upstream 2.5x larger, so `298` §4.2 makes it a result, not a
masked zero — **and the instrument printed its own pre-registered null: *"already-converted=0 means
the saturated matrix came from somewhere else and this diagnosis is WRONG -- do not keep it."*
GROUP `C`'s leading hypothesis is gone and `C1` must be rewritten before it is worked.** **►►►►
A NEW SYMPTOM, AND IT IS THE FIRST ONE THAT IS NOT AN ADMISSION FAULT: a flat slate polygon
occludes wall geometry in ONE eye** in `dlgrab_V1_2732`, `dlgrab_C1_2336` and `dlgrab_C1_4676`,
**in frames whose census reads `MODEL_MTX 39/39`, `MODEL_VTX 17/17`, `only in eye0 = 0` AND `only
in eye1 = 0`** — same commands, different picture, and the owner's *"bond bobs and it changes the
output"*. `4676` is the bigger event (44,252 differing px over 900 blobs, alignment `mad` 6.409
against every other frame's 3.4–4.1). **►►►► AND `H9` IS CLOSED BY A SENTENCE THAT WAS ALWAYS
TRUE: AT `GETV_STEREO_OFFSET=0` THE SECOND EYE **IS** THE KNOWN-GOOD FRAME** — same run, same rig,
same instant. `getv/tools/stereo_eyediff.py` is that differ, **selftest 11 checks 0 failed**, and
on `303`'s nine grabs it separates by a factor of ten: six clean frames 0–207 px against 2,196 /
4,544 / 5,947 px, **three hits and no false positives** — **CORRECTED BELOW, that was nine frames.**
**►►►► AND `304` §1 IS ALSO WORN, AND THE SWEEP FOUND A FALSE NEGATIVE IN `stereo_eyediff.py`
ITSELF.** It differenced LUMINANCE and scored `dlgrab_S2_1176` — **a frame with a WHOLE DEAD EYE**
— clean at 1,329 px, because a navy void and a brown building have nearly the same brightness;
`dlgrab_S3_1155` was a second miss. **FIXED: per-channel differencing, a selftest check that fails
on the `303` version, 16 checks 0 failed, and a 256-frame calibration replacing the nine-frame one
— clean tops out at 715 px, the smallest hit is 1,967, and NOTHING lands between.** The sweep read
**41 divergent / 40 clean / 175 refused**, and most of the divergence is the tool re-finding the
dead eye the project already knows — **V1 one divergent frame against V2's five, same alley, same
binary, which is `303` §2's fix appearing in a metric that knows nothing about props.**
**►►►► AND THE DATING QUESTION IS BLOCKED BY PROVENANCE, NOT BY THE INSTRUMENT: the only pre-`303`
frames carrying the polygon's signature are in `grabs_pre_298cull`, and THREE ARE ANNOUNCED BY NO
LOG, ONE BY FIVE, AND ONE BY A FALSIFIER ARM WHOSE GUARD IS SUPPOSED TO FIRE** (`279` §2, billed
for the first time). **The question is OPEN, not answered no, and it needs a RUN.**
**READ `304-THE-SWEEP-FOUND-A-FALSE-NEGATIVE-IN-ITS-OWN-INSTRUMENT` §0, THEN `RUN-SHEET-304` §2.**
`169` NEXT ID = `U-26`.**

**PREVIOUS (sessions `302` WORN + `303` WRITTEN. **BOTH `302` ARMS ANSWERED AND BOTH
MOVED WORK.** Binary `DF5CAB2A...1438 18068657`. **►►►► THE SKIPPED PROP IS THE VIEWER — cumulative
`viewer=541`, every other bucket ZERO, on a run whose four population states reproduced `301` S2 TO
THE FRAME — AND IT IS **NOT** BENIGN.** `dlgrab_eyecensus` on `grabs_302_S3` frames `1155/1243/1381`
reads **eye0 `MODEL_MTX=38 MODEL_VTX=16 MODEL_COL1=19` against eye1 `0/0/0`, `only in eye1 = 0`** —
a STRICT SUBSET, so a ONE-DIRECTIONAL LOSS. **`item 4`'s "the viewer is already per-eye" is
FALSIFIED**: `chrpropRender()` sends `PROP_TYPE_VIEWER` to `bondviewRenderProp()`
(`chrprop.c:884`), which forwards to `chrRenderProp()` when `chr` is non-NULL
(`bondview2.c:11666`), so it consumes exactly what `chrBuildRenderState()` produces. **`293` §2.1
measured the VIEWMODEL's allocation, a different object. GROUP `B1` IS FULLY ANSWERED AND `B2` IS
REAL, scope exactly one type.** **►►►► AND THE DEPTH-CLAMP FIX TOOK THE FAR PLANE DOWN WITH THE
NEAR ONE.** `302` §4 `[MEASURED]`: **`beyond_far=16534203` (13.2% of 125.5M vtx)** against `301`
D1's 0.7%, `all_far(hw-rejects)=0`, `clamped=0`; owner *"foggy after a certain distance and its
flickering"*, *"all the characters and cars etc are transparent and flickering"*, *"it is much less
view"*. **`299` §8.1 stood BOTH per-vertex clamps down on an argument measured at the NEAR plane
ONLY.** **►► AND THAT RUN WAS MONO** — `dlgrab_D3_33362.txt` has ONE viewport load and no
`[getv][stereo]` banner — **so *"both eyes layered over each other"* CANNOT be a stereo fault; it is
z-fighting, and the eye loop is not where to look.** `303` writes both fixes:
`GETV_STEREO_REBUILD_VIEWER` (default 1, banner, and **the balance is now
`chr+obj+view+skipped == zsnap`**) and the far clamp decoupled from `ge_depth_clamp_active()` with
**`GETV_FARCLAMP` given the banner it never had** — `H4` costing a cycle for the THIRD time. Ten of
ten gates PASS, **`regen` RUN and `verify` 15/15 — the regen IS owed this time, `gfx_pc.c` is
gitignored and `302` had no regen step.** **NOT BUILT, NOT RUN. READ `RUN-SHEET-303` §0 and §0.1,
THEN §1 ONWARD.** **►► THE BEST METHOD FIND IS THE OWNER'S: the character introduction video LOOPS,
shows the fault plainly, and is reached deterministically (start the level, die, let it restart).
A fixed camera on a repeating sequence removes the "were you standing in the same place" objection
that dogged `301` D1/D2 — `303` §4 uses it as the A/B venue and it is the best candidate the
project has for `H9`'s reference frame.** `169` NEXT ID = `U-26`.**

**PREVIOUS (sessions `301` + `302`, **`RUN-SHEET-301` WORN IN FULL — GATES, BUILD, 3c, FOUR ARMS AND THREE COMMITS.** Binary `goldeneye.exe` **18,067,594 bytes, sha256 `7058E950...D5B6`**, `EXPECTED-EXE-301.txt` matches; commits `2592170` (GoldenEyeVR) / `ad741f6` (native) / `ae4791b9` (decomp). **►►►► THE DEPTH-CLAMP FIX WORKS: D1 artefact GONE, D2 artefact PRESENT — `[REPORTED]`, the owner's eyes, and `299` §8.1 CLOSES.** The census agrees on both arms (D1 `straddle=15900 clamped=0`, far `clamped=0`; D2 `clamped=13930` = `straddle 13880 + all_near 50` exactly, far `clamped=33245`). **`GETV_FILTERING=0 -> filtering=0` — the precedence fix took and `H4`'s named offender is closed at the mechanism.** **►►►► AND THE SKIP SPLIT ANSWERED HALF OF `299` §8.3: `flag=0` ON ALL 541 SKIPPED FRAMES, `type=1` ON ALL OF THEM** — `chrprop.c:476`'s *"this cannot happen today"* is **NOT falsified**, there is no per-eye admission bug, and GROUP `B1` is answered. `S2` read **1950 frames in four clean population states** — `1-1082` zsnap=11 chr=2 obj=9, **`1083-1454` (372) chr=0 obj=0 skipped=1**, `1455-1623` (169) zsnap=2 chr=1 skipped=1, `1624-1950` gameplay — with **`bgLoad 'bg/bg_pete_all_p.seg'` firing at frame 1083, so the dead window starts EXACTLY at the level's bg load and `372 + 169` = `299`'s "~541" confirmed to the frame.** ZERO-REBUILD cumulative **372 of 1950 with `pass-never-ran 0`** on a `SIMDIV=1` run: measured, not sampled, and it is the number `298` §1.1 could not see. `chr+obj+skipped == zsnap` in all four states (`H3` verified on real data). **►►►► WHAT IT COULD NOT SAY IS WHICH TYPE, AND THE SIX DISAGREE: `viewer=` makes the 372 frames BENIGN (item 4: the viewmodel is already per-eye) and RETIRES `B2`; `explosion=`/`smoke=` make `B2` real; `player=` and `nul=` are excluded by the code and NAMED BY NEITHER COMMENT.** `302` splits the counter six ways in `ge_rebuild_window.h` + `chrprop.c` with `type` **COMPUTED** from the buckets, harness **30 checks 0 failed** (CASE 6 = the sum invariant, CASE 7 = reset vs cumulative), **ten of ten gates PASS, `verify` 15/15, NO REGEN OWED — all three edited files are tracked.** **NOT BUILT, NOT RUN.** **READ `RUN-SHEET-302` §0 (the whole thing is one table), THEN §1 ONWARD.** Still owed: **D1's FAR FIELD** (`GL_DEPTH_CLAMP` disables z clipping at BOTH planes and nobody has looked — `302` §4), GROUP C's `NaN` (`HIGH`, untouched), `H4`'s 324 banners, GROUP D, `H9`. `169` NEXT ID = `U-26`.**

**PREVIOUS (session `299`, OFFLINE + FIVE WORN ARMS. NOTHING BUILT, NOTHING COMMITTED, NO SOURCE FILE CHANGED. **THE A->B->A PASSED AND BUG 2 IS `[MEASURED]` CAUSE: the owner's *"you can see through the wall"* IS THE NEAR-PLANE DEPTH CLAMP (`gfx_pc.c:3752`).** N1 clamp ON *"yes it still does it"* / N2 clamp OFF *"it does not do it"* / N3 clamp ON *"it did it"*, with the census proving the knob took in all three (`20928+12=20940`, `clamped=0` against `straddle=8666`, `12814+51=12865`) and **grabs taken in every arm, which is the gate arm F failed.** **THE NEXT BUILD IS `GL_DEPTH_CLAMP` IN `gfx_opengl.c`** -- `gfx_pc.c:3734` names it and it is implemented nowhere. **SEPARATELY, AND IT NARROWS `298`'s HEADLINE: ARM 3 IS GREEN ON GAMEPLAY FRAMES AND DEAD ON THE LEVEL'S OPENING ~541 FRAMES.** `[MEASURED]` E2 grabs 744-889: `MODEL_MTX 38->0`, `MODEL_VTX 16->0`, per-half energy ratio up to **99x**, every one paired with its own frame's census reading `chr=0 obj=0 **skipped=1**` while the good frames read `chr=1 skipped=0` -- **same list size; the difference is whether the one listed prop was REBUILT or SKIPPED.** **IT IS NOT ALTERNATION** -- E1's fourteen grabs are all equal-eyed -- and **it is DETERMINISTIC**: E1 and E2 report identical skip counts (372 + 169) in runs of different length. **AND `292`'s DOUBLE CONVERSION IS ALIVE: `arrays=144716 already-converted=11902`, every hit `eye=1`, MOST OF THEM `NaN` -- which `292`'s mechanism does not explain and nothing has looked at.** **THE FIX IS WRITTEN, REGENERATED AND **BUILT** (2026-09-03 02:40, `goldeneye.exe` 18,062,771 bytes, `59` port-layer objects, 0 failed; `ge_depthclamp.o` in `libge.a` with all three symbols and its GL refs resolving to `glIsEnabled`/`glGetError`) **BUT NOT RUN**: `ge_depthclamp.{c,h}` NEW AND TRACKED, plus four lines of hook in `gfx_pc.c`/`gfx_opengl.c`, WHICH ARE REGENERATED -- SO THE REGEN IS OWED BEFORE THE BUILD AND BEFORE THE COMMIT (`268`). Also written: `configFiltering`'s `over` guard (`298` §5) and the rebuild census's `flag=`/`type=` skip split.** **COMMITTED 2026-09-03: `fe93821` (GoldenEyeVR) / `6f24ddc` (native, AND IT CARRIES THE REGENERATED PATCH) / `77f67e26` (decomp), `verify` `15/15` after.** **READ `299` §8 AND §9, THEN `RUN-SHEET-300` §4 ONWARD (§1-§3 ARE WORN AND COMMITTED), THEN `PRIORITY-BOARD-299`.** **WHETHER THE FIX WORKS IS ENTIRELY UNTESTED -- D1/D2 IS THAT GATE AND IT HAS NOT RUN.** R3, R4/S3 and R5 are still unrun. `169` NEXT ID = `U-26`.**
**PREVIOUS (session `297`, OFFLINE ONLY — NOTHING BUILT, NOTHING RUN, NOTHING COMMITTED. **ARM 3 IS WRITTEN: `GETV_STEREO_REBUILD`, DEFAULT OFF.** The second eye now walks `g_OnScreenPropList` and calls objTick's and chrTick's OWN render builds, extracted verbatim (`objBuildRenderState`, `chrBuildRenderState`) — **ESCAPING LOCALS: ZERO in both, `[MEASURED]`**, which is what made the cut legal. Three guards added in `chrTick`, which guards nothing of its own (`295` §3: TWO accumulators, not one), and NONE in `objTick`, which already guards all of its (`293` §3b.1). **AND A HAZARD NO EARLIER DOC NAMES: `prop->zDepth` IS NOT RENDER-ONLY** — `chr.c:4013`/`:4020`/`:4067`/`:4148` read it in the SHOT TEST — so it is snapshotted after the tick and restored after the eye loop (`297` §5). **ARM 2 IS WORN AND ITS QUESTION IS ANSWERED IN THE NULL: `mismatch == frames` exactly, every site `forced-read-after-lvlRender`, NO ENGINE READER IN 12,000 FRAMES (`295` §10).** `chrprop.c` AND `ge_port_decls.h` were both CRLF against an LF HEAD; both converted (`297` §6 — `295` §6 predicted the first and no document named the second). **►►►► R0 IS GREEN. THE CRASH WAS **NOT** `objBuildRenderState + 199` — THAT SYMBOL CAME FROM A LOAD BASE DERIVED BY ASSUMING THE ANSWER, AND `297` §10 IS RETRACTED IN FULL (`297` §11). THE REAL CAUSE WAS `chr.c:3305`, AN `if (headSwitchVisible)` WRITTEN **TWICE**: the `else` bound to the inner `if`, so an off-screen chr never cleared `PROPFLAG_ONSCREEN` while its `field_20` joint list had already been nulled, and `chrTestHit` walked NULL. **FIXED, BUILT AND WORN — a full session, no crash.** The instrument that named it (`GETV_HIT_DEBUG`'s `rej(off=0)`) had been in the tree unused. **AND `grep -n "EXCEPTION" <run log>` PRINTS `FAULT PC` AND `fault addr` — the port has always symbolised its own crashes and three rounds did not look.** SEPARATELY: **shooting a mine still crashes, it is PRE-EXISTING, and the saved parent binary proves it (`297` §12) — ARM 3 IS CLEARED OF IT.** Harness **63/63**, real-header gate on **NINE** files. **READ `297` §0, §3, §4, §5, THEN `RUN-SHEET-297`.** S3 has never run. `169` NEXT ID = `U-26`.**
**PREVIOUS (session `295`, 2026-09-02 — ARM 1 and ARM 2 written offline, then WORN by the owner: S1 `checks=8400 mismatch=0`, S2a `checks=250803 mismatch=600` (the falsifier FIRES), S2b `checks=213951 mismatch=0`. `295` §10 records it and §10.1 records the null answer.)**

**PREVIOUS (session `293`, 2026-09-01, OFFLINE ONLY — NOTHING BUILT, NOTHING RUN, NOTHING COMMITTED. **THE `1060 vs 622` DIVERGENCE IS ANSWERED AND THE QUESTION AS `292` FRAMED IT IS RETRACTED: THE ROOM SET IS IDENTICAL IN BOTH EYES — `gSPSegment(BG_VTX)` is EQUAL in ALL EIGHTEEN of `292`'s `dlgrab` dumps (2/2, 3/3, 9/9, 11/11, 15/15, 23/23) — and what collapses is the chr/prop MODEL pass (`MODEL_MTX 39->1`, `MODEL_VTX 17->0` in `dlgrab_5249`). Eye 1's DL-CALL set is a STRICT SUBSET of eye 0's in every dump (`only-in-eye1 = 0`): a ONE-WAY LOSS, not a divergence.** **THE CAUSE IS AN ENGINE FACT: `propsTick()` IS NOT A SIMULATION TICK** — `objTick`/`chrTick` run `posIsOnScreen`, set `PROPFLAG_ONSCREEN`, `dynAllocate` `model->render_pos` and fill it from `camGetWorldToScreenMtxf()`, and `292` gated ALL of it to eye 0. **`--arena` proves it: `MODEL_VTX` `fresh=0` in every dump — the second eye ALLOCATES NOTHING and replays eye 0's arena; its one fresh matrix per frame is the viewmodel. `292` §1 doubled BOTH pools so two eyes could each allocate, then gated away the only code that allocates.** Fault 3 is the SAME bug, not downstream of it. **`293` §3a: the obvious cut is ILLEGAL** (the admission test also selects between two SIMULATION paths). **READ `293` §0, §2.1 AND §3a.** S3 has never run. `169` NEXT ID = `U-26`.**
**PREVIOUS (session `292`, THE EYE LOOP IS BUILT AND RUN. S1 GREEN; **S2 CAUGHT THREE FAULTS AND ALL THREE WERE MINE** — see `292` §5a). **THE FINDING IS AN ENGINE FACT, NOT A STEREO ONE: `bondviewTransformManyPosToViewMatrix` IS NOT A TRANSFORM — it is an IN-PLACE f32->s32 fixed-point conversion, so it is NOT IDEMPOTENT, and running it twice saturates every matrix entry at +/-32768** (`[MEASURED]` `dlgrab_5249.txt` seq=002525: a character's shadow quad, every entry pinned — the green wedge). `GETV_STEREO_MTXGUARD=1` observe: `already-converted=88520/183808`, **every hit `eye=1`**; `=2` skip: `skipped=381767`, `[REPORTED]` *"both eyes showed better"*, both viewport lines print (`ours: x=367.333` AND `x=1280`). **MODE 2 IS A FALSIFIER, NOT A FIX — DO NOT SHIP IT.** Also fixed: the DL held a POINTER to a viewport slot both eyes shared (`67`/`70` again), and the eye aspect was halved in only one of the two places that describe the camera. **STILL OPEN AND IT IS THE REAL QUESTION: the two eyes admit DIFFERENT geometry — 1060 tri cmds / 1940 verts in eye 0 vs 622 / 1355 in eye 1, same frame, ZERO separation, byte-identical projections.** S3 has never run. `169` NEXT ID = `U-26`.**
**If this line is more than one session old, `HANDOVER`'s top banner is newer — read that, then fix this file.**

> **THIS FILE REPLACES READING `HANDOVER` + `00-START-HERE` TO ORIENT.**
> Those are 5,300 lines and nine stacked banners. This is the current truth with
> pointers. **It DELETES NOTHING — every doc stays exactly where it is.**
> **Read a numbered doc only when this file points you at one.**

---

## 0. ►►►► WHO "THE OWNER" IS: WHOEVER IS LEADING THIS SESSION ◄◄◄◄
**STANDING RULE, 2026-08-30, AT THE SESSION LEAD'S REQUEST.**
**"THE OWNER" IS A ROLE, NOT AN IDENTITY.** It means **whoever is driving the current
session** — the person who sent the prompt. **The same human runs this project under
DIFFERENT USERNAMES, ACCOUNTS AND MACHINES**, so:
- **Never key anything on a username, account name, email or machine name**, and never
  decide what to do based on who you think you are talking to. **The prompt is the
  authority; the account is not.** If a doc says "the owner", read "the session lead".
- **NEVER HARDCODE A USERNAME OR HOME DIRECTORY IN A COMMAND.** `C:\Users\<name>\...`
  breaks under a different login and is a silent failure. **Use `$env:USERPROFILE`,
  `$env:APPDATA`, `$HOME`** — and note the live config lives in
  `$env:APPDATA\Goldeneye-Native\Goldeneye-Native\goldeneye.cfg`, which is per-user and
  therefore **DIFFERENT FOR EACH LOGIN** (§6, config search order).
- **Project paths are stable and username-free** (`F:\Projects\GEVR\...`) — use them
  absolutely, per §7a. **It is only USER-SCOPED paths that must be derived.**
- **Continuity lives in THESE DOCS, not in a session or an account.** Do not assume a new
  session inherits anything a previous one knew. `00-STATE` is the handoff (§7b, §7c).

## 1. THE MISSION, AND THE FOUR THINGS THAT ARE NOT NEGOTIABLE

**Build GoldenEye 007 VR from SOURCE** — the native PC port (`goldeneye-native`,
from the 2026 100% decomp) + a VR layer. ROM for assets only. No recompiler.
**Currently: the flat game boots and plays. STEREO HAS NOT BEEN STARTED.**

1. **EVERY GIT COMMIT IS THE OWNER'S.** Never stage, commit, branch, merge, tag.
   Reading git state is fine. **`COMMIT-NOW.cmd`, main PC, not the bridge.**
2. **DELETE NOTHING.** Every knob stays reachable. Mark superseded; never remove.
3. **FIX IT IN THE SOURCE — and we may change anything, provided the game stays
   TRUE TO ITS SPIRIT.** Test: *would a 1997 player notice this as the game
   behaving differently, or only as the absence of a limit the console imposed?*
   Free = hardware budgets. Careful = anything the player feels (diff it against
   the decomp). Additive = the VR layer, inert when off. Ask first = game design.
   **Full table: `HANDOVER` §0.**
4. **`P1`-`P9` CONSTRAIN EVERY PLAN.** A plan not satisfying them is unfinished.
   `P1` sim rate `60.0f/actualHz`, never a literal, **pinnable** · `P2` four
   tangents per eye per frame, never a stored FOV angle · `P3` resolution is one
   runtime variable · `P4` pay structural cost once, never per-frame ·
   `P5` no performance claim without an instrument that can fail ·
   `P6` **the SIM owns the pose**, renderer only consumes · `P7` two hands + body
   are ONE articulated system · `P8` aim independent of facing/camera/locomotion ·
   `P9` sim authoritative for ballistics and position.
   **Full text: `00-START-HERE` "THE PERFORMANCE CONSTRAINTS" and "THE EMBODIMENT
   AND SIM-AUTHORITY CONSTRAINTS".**

## 2. THE RULES — 18 OF THEM, IN `00-START-HERE` "THE RULES"
**Do not restate them; read them once per session.** The six that get broken most:
- **`3` measure, do not describe.** Every correct conclusion came from a number.
- **`14` we have the source — change it.** Don't build a workaround around an
  editable constant; don't ask the owner to read a file the source can print.
- **`15` build the instrument when one can be built — and VALIDATE it. State what
  it would print if pointed at the wrong thing, BEFORE the run.** A counter that
  is never printed is not an instrument.
- **`16` a repeated owner report is a RANKING error, not noise.**
- **`17` (NEW, 2026-08-30) the session's COMMIT MESSAGE is part of its output — and any tool
  that falls back to "the newest" or "the last" instead of failing is a silent-staleness bug
  that gets a GATE.** Five surfaced in one session; every one reported success. `271` §7.
- **`18` (NEW, 2026-09-01) NO ATTRIBUTION TRAILERS IN COMMIT MESSAGES** — no `Co-Authored-By`, no
  session URL, no tool footer — **and a convention that arrives from the assistant's own DEFAULTS
  rather than from this project is a silent change that gets refused.** `294` added one unasked and
  it landed in `a6dce62`. **The trailer was TRIED AND ABANDONED here** — `[MEASURED]` 13 of 89
  commits carry one and all 13 are the repo's first two days; **60 consecutive commits carried none**
  before `294`. **And a convention check WITHOUT A STATED WINDOW is not a measurement**: `294` got
  `0` from the last 6 commits and `14` from all history and contradicted itself. Say the window, and
  look at WHERE the hits fall. Defaults are an untracked input to this repo.
> **`HANDOVER` §5: the owner's corrections have outranked the analysis EVERY TIME
> they conflicted. Treat a wear report as data that outranks a log.**

---

## 3. WHAT IS TRUE NOW

### WORKS
| | evidence |
|---|---|
| **THE REBUILD CENSUS CAN BE TRUSTED** (`H2`/`H3`) — **NEEDS THE `301` BUILD** | `301` §3. Window accumulators; read the `WINDOW` line and `ZERO-REBUILD FRAMES`, **not** `SUMMARY`. `GETV_STEREO_REBUILD_REPORT=1` no longer required |
| **`stereo_disparity.py`'s peg detector fires** (`H1`) — **offline, live now** | `301` §2. Tests `dx` against the bounds `measure()` really searched. `[MEASURED]` on `dlgrab_10393.bmp`: `--search 800` pegs at `-800` with `mad_best` FALLING to 4.441 |
| **51 of the 57 `getv/port/**` sources compile offline** (`H10`) | `301` §7a. `port_syntax_gate.sh`, using `build_windows.ps1`'s own `$portFlags`. The six exceptions are named with reasons in the script |
| **`fetch-thirdparty.sh regen` works over the bridge, and its patch no longer churns** | `301` §8. In-place-copy fallback when `mv` cannot unlink; `---`/`+++` timestamps normalised, so two regens over unchanged sources are byte-identical and `git diff` shows only real changes |
| **`ge_depthclamp.c`'s GL path compiles offline** (`H6`) | `301` §5. `depthclamp_glpath.sh`. **Parses ≠ verified** — `glstub/README.md` |
| Native port boots and plays from the owner's ROM | `229` |
| **Save/EEPROM persists** (`F2`) — was broken since bring-up | `262`; `MoveFileExA` replaced a POSIX `rename()` Windows refuses |
| **File-select folders** (`F1`) — two causes, both fixed | `260` fossil EEPROM in `%APPDATA%`; `262` `front.c:2452` passed `f32*` where `coord2d*` required |
| **Intro cast crash** — open four banners | `262`; slots leaked because `GETV_SLOTFREE=0` in the per-user cfg |
| Inventory crash, slow pickup, explosion crash, ammo re-pickup | `250` `GETV_CUFFIDX`, `251` `GETV_RWSTRIDE` |
| ~~Menu text, folder screen, purple explosion~~ **MENU TEXT IS SUPERSEDED — see OPEN, the `ge_offset_x()` item. Folder screen and purple explosion stand.** | `236`, `237`, `244`; broken for any non-4:3 window by `287` |
| **SPLIT-SCREEN RUNS — two views, two viewports, ONE display list, ONE swap** — stereo's mechanism, PROVEN BY A RUN | `270` §1; `258` §1 was only a source read until now |
| **`GETV_MENU=<n>` boots WITH SOUND, crosshair and ammo** — the fast-iteration route | `269`; `fileValidateSaves()` took neither call site on a title boot |
| 90 Hz is achievable — `59.3 -> 87.1 fps`, worn, "totally playable" | `134`, `147`. **The interpolator is DELETED and stays deleted.** |
| **`P5` HAS AN INSTRUMENT THAT CAN FAIL — `WORK_OVER=`** | `271`; the pacer's sleep is measured and subtracted. **`WORK_OVER=0` over 7,440 frames on Facility, and over ~9,960 MORE on CRADLE — the hardest level in the game** (`272` §5.1) |
| **THE PRE-STEREO CPU BASELINE IS TAKEN, AND RE-TAKEN SOMEWHERE HARD** (`258` STAGE 3.1) | **`272` §5.2 — 0.890 ms mean, 2.504 ms worst frame, CRADLE at 90 Hz.** `271` §2's 0.259 ms was Facility, and Facility is a VENT — §4 |
| **STAGE 41 (Cradle) DIRECT-BOOTS** | `272` §5.4. Only 9, 34 and 38 had ever been booted |
| **►► THE GPU TERM EXISTS. `[MEASURED]` 0.832 ms CRADLE, 0.334 ms FACILITY** — 1280x960, RTX 5090, **`GETV_FPS=0`** | **`273` §5.1.** First GPU figure the project has ever owned. Scene-sensitive, 2.5x |
| **THE PRESENT COSTS NOTHING — `[MEASURED]` `CPU present` 0.00 ms, max 0.05** | `273` §5.3; sleep-subtracted, cross-validated against the budget line in the same window |
| **`GETV_GPUTIME` NOW REFUSES A CAPPED RUN** instead of printing the period | `273` §2, rule `17`. `slept=N/120` + `CONTAMINATED` |
| **►► THE TIMEBASE DECISION IS SETTLED, BY RUN. `RB-04` HAS A NUMBER: `[MEASURED]` `speedgraph 90/s` at `GETV_FPS=90` = 1.500x, vs the owner's stopwatch 1.487** | **`274` §2.** Three arms, no build, all three valid on their own banners |
| **►► THE FRACTIONAL-DELTA SHAPE IS CHOSEN — SHAPE 3, integer `g_ClockTimer` beside a fractional `g_GlobalTimerDelta`** | **`275`.** Owner's call, on a full read of all 44 divide sites and all 24 iteration sites |
| **►►►► SHAPE 3 IS WRITTEN — `GETV_SIMHZ`, five files, default OFF. NOT BUILT, NOT RUN** | **`276`.** `frametiming.c` + the `lv.c` seam + `275` §4's two hoists, all inside `#ifdef GE_PORT_NATIVE` |
| **►►►► SHAPE 3 IS BUILT, RUN AND WORN. `239`'s GATE IS MET FOR THE DELTA TERM** | **`277`.** `[MEASURED]` 90 Hz: `fps 90`, `speedgraph 60/s`, `g_GlobalTimer 60/s`, `delta 0.6667`. Seven arms, one binary (`20:05:55`), no falsifier fired |
| **The term is INVISIBLE when unset — measured, not argued** | `277` §2 arm C: no banner, `simhz OFF`, full `speedgraph 90/s`. `48`'s one-behaviour-change holds |
| **BOTH REFUSALS FIRE AND NAME THEMSELVES** | `277` §2 arms D/D2 — the `GETV_REALCLOCK` interlock, and the pin honoured while declaring its own numbers void (rule `17`, `15`) |
| **THE WORLD RUNS AT RETAIL SPEED AT 90 Hz, WORN** | `277` §4. Owner, term on vs off: *"everything was moving faster except bond"* |
| **`275` §9's ONE OPEN CLASS IS CLOSED — the count of two hoists is EXACT** | `276` §4. A parser walked all 24 loop bodies; the only calls made from any of them are `sqrtf` and two `matrixmath.c` helpers, in a file with **zero** delta references |
| **►►►► THE POSE SPINE IS BUILT, RUN AND GREEN — `258` STAGE 5 DONE, `P6` ON THE LIVE PATH** | `291`. A2 `SUMMARY mode=1 frames=7180 stale=0 maxerr=0.000 VERDICT PASS` (pose written before the tick, read fresh at tick time); A3 `stale=6499 VERDICT PASS (detector fired)`; A1 inert. Five strings FOUND, `verify` 15/15, harness 10/10 |
| **►►►►►►►► ARM 3 IS GREEN. THE CHARACTERS AND THE PROPS ARE IN BOTH EYES AND NOTHING WARPS — `258` STAGE 5's REASON FOR EXISTING** | **`298` §0, §1.** R2 `[MEASURED]` 2026-09-02: `eyes-rebuilt=1`, `chr`+`obj` accounting for the WHOLE `g_OnScreenPropList` in every window (`11=2+9`, `3=2+1`, `7=5+2` x3), no `EXCEPTION`, `game_exit requested`. Per-eye texture energy **1.00 and 1.02** against R1's **8.6x and 6.0x** — and R2's per-eye figure EQUALS R1's good eye, so the starved eye came up rather than the good one coming down. **`292`'s doubled pools were spent for the first time and did not overflow.** **►► NARROWED 2026-09-03, `299` §8.2: TRUE OF GAMEPLAY FRAMES, FALSE OF THE LEVEL'S OPENING ~541 FRAMES**, where `[MEASURED]` `MODEL_MTX 38->0` and `MODEL_VTX 16->0` into eye 1, per-half energy ratio up to **99x**, on seven grabs in one arm. **NOT alternation** (E1's fourteen grabs are all equal-eyed) and **deterministic** (E1 and E2 report identical skip counts, 372 + 169, in runs of different length). Each dead frame's own census reads `chr=0 obj=0 skipped=1` against the good frames' `chr=1 skipped=0`. |

### OPEN — RANKED

0. **►►►►►►►►►► THE OWNER `[REPORTED]` IT 2026-09-02 AND IT GOES HERE IN THEIR WORDS (§7b2):
   *"AS JAMES BOND STANDS THERE AND BREATHES, YOU SEE THE WALL MOVE, EVEN GOES ABOVE THE GUNSHOT
   DECAL. WHENEVER YOU GET CLOSE TO AN EDGE OR SOMETHING IS ON THE CORNERS OF YOUR VISION, IT TENDS
   TO DISAPPEAR. YOU CAN SEE THE BUILDING SPLITS IN THE DISTANCE AS WELL."* AND, DECISIVELY:
   *"IF I MOVE ANY LITTLE BIT, IT GOES DOWN OR GOES AWAY. IT SEEMS TO BE IN SYNC WITH EXACTLY MY
   MOVEMENT."* ◄◄◄◄◄◄◄◄◄◄**

   **►► IT IS TWO BUGS AND ONE FALSIFIER SEPARATED THEM. `298` §3. DO NOT MERGE THEM AGAIN.**

   | symptom | shipping | `GETV_ROOMSCISSOR=0` | reading |
   |---|---|---|---|
   | the split down the distant facade | present | **GONE** | the per-room clip RECTANGLE |
   | the wall cut, geometry showing through | present | **STILL PRESENT** | **NOT the rectangle** |

   `bg.c:445-447` states both branches in advance and **one of each fired.** Arm D re-ran the same
   alley at shipping defaults — verified by the ABSENCE of both falsifier banners — and the second
   symptom reproduces, so it is not `ROOMSCISSOR=0`'s documented overdraw cost.

   **►►►► THE SECOND ONE HAS A NAMED MECHANISM AND A CENSUS BEHIND IT: THE NEAR-PLANE DEPTH CLAMP,
   `gfx_pc.c:3752`.** `[MEASURED]` `GETV_NEARCLAMP=0`: `NEAR straddle=18439 clamped=0` — **the
   condition was crossed eighteen thousand times with the clamp provably off and the artefact did
   not appear** (`[REPORTED]`). Not a masked zero (`289` R2's rule), because the upstream counter is
   large. The clamp moves `z` only, per-vertex, **before** interpolation, which tilts the depth
   gradient across every straddling triangle — recomputed from the camera every frame, which is the
   owner's *"in sync with exactly my movement"*, and vertex-level, which is why the scissor arm
   never touched it. **`gfx_pc.c:3733` names the fix itself: `GL_DEPTH_CLAMP` / `ARB_depth_clamp` /
   `EXT_depth_clamp`, "which is precisely the hardware behaviour" — and `[MEASURED]`, it appears in
   `gfx_pc.c` comments TWICE and IS NOT IMPLEMENTED ANYWHERE IN `gfx_opengl.c`.**
   **►► `GETV_NEARCLAMP=0` IS NOT THE FIX AND MUST NOT SHIP** — without it GL discards every
   triangle poking through the near plane; F's own census shows the price starting, `all_near`
   **50 -> 548**.
   **►► AND IT IS NOT `281`'s DEAD THEORY.** That was `sub_GAME_7F0B5528`, the portal-box projector
   in the GAME code, killed by `282` §2.1. This is the RENDERER's triangle submission. Named because
   the resemblance is close enough to mislead.
   **►►►►►►►► NO LONGER OWED. THE A -> B -> A RAN 2026-09-03 AND PASSED. THIS IS `[MEASURED]`
   CAUSE. `299` §8.1. ◄◄◄◄◄◄◄◄** `[REPORTED]` in order: N1 clamp ON *"yes it still does it in this
   run"*, N2 clamp OFF *"it does not do it in this run"*, N3 clamp ON *"it did it in this run"* --
   **PRESENT -> ABSENT -> PRESENT.** The census proves the knob took in every arm
   (`20928+12=20940` / `clamped=0` with `straddle=8666` / `12814+51=12865`), no falsifier banner
   fired in any of them, and **grabs were taken in all three -- the gate arm F failed.**
   **`298` §8 falsifier 1 did NOT fire. THE NEXT BUILD IS `GL_DEPTH_CLAMP` IN `gfx_opengl.c`.**

0. **►►►►►► `[REPORTED]` AND NEVER TESTED: *"the gun disappears on the floor."* THE ARM RAN AND ITS
   GATE DID NOT. ◄◄◄◄◄◄** `298` §3. `GETV_PROPROOMTEST=0` fired its banner in arm C, but no gun was
   dropped, so **`bg.c:583`'s `getROOMID_isRendered(roomnum)` — *"NEITHER `GETV_ROOMSCISSOR` NOR
   `GETV_PROPCULLBOX` TOUCHES IT. It has survived two arms without being tested once"* — has now
   survived a THIRD.** One short run answers it.

0. **►►►►►►►► THE OWNER HAS `[REPORTED]` THE SAME THING IN THREE SESSIONS AND IT IS STILL THE
   SYMPTOM THIS PROJECT EXISTS TO REMOVE: **THE PEOPLE, THE CHARACTERS AND THE PROPS ARE NOT IN
   THE RIGHT EYE AT ALL, AND WHAT DOES DRAW WARPS.** ◄◄◄◄◄◄◄◄**

   **THIS IS NOT A NEW ITEM AND THAT IS THE COMPLAINT.** `293` answered it in engine terms
   (`MODEL_MTX 39->1`, `MODEL_VTX fresh=0`, eye 1's DL-CALL set a strict subset of eye 0's in all
   eighteen dumps) and it has been carried since as *"the eye-1 model collapse, ARM 3's job"*. **A
   defect written only in the instrument's vocabulary reads as filed. This one is written in the
   owner's, at the top, until it is gone.**

   **THE TWO HALVES OF THE SYMPTOM, AND THEY ARE ONE MECHANISM (`293` §0, §2.1):**
   - **ABSENT.** `292` gated `propsTick()`/`objTick`/`chrTick` to eye 0. Those passes are the only
     code that `dynAllocate`s `render_pos` and builds the model matrices. Eye 1 allocates
     **nothing** and replays eye 0's arena, so most models never reach its display list.
   - **WARPING.** What *does* survive is transformed by `render_pos` filled from **eye 0's**
     `camGetWorldToScreenMtxf()` — a coordinate system that is not eye 1's. **The warp is not a
     second bug. It is the surviving remainder of the same one.**
   - The gun and HUD are the exception because the viewmodel is eye 1's one fresh allocation per
     frame — which is exactly what the S2 grabs of `295` §10.1 show and why they look the way
     they do.

   **THE REPAIR IS `293` §3a AND IT HAS NOT CHANGED:** a new **render-only** pass, per eye, over
   `g_OnScreenPropList` — re-`dynAllocate` `render_pos`, rebuild the matrices, re-run
   `modelUpdateRelationsQuick`, re-derive `zDepth`, **touch nothing else.** NOT a split of
   `objTick`/`chrTick`, NOT a second tick (`293` §7, both illegal). `295` §3's two-accumulator
   correction and §6's two traps are what it will need.

   **►► THE ONE STATED BLOCKER IS GONE. `[MEASURED]` 2026-09-02, and this is the entry's point.**
   `295` §5 held ARM 3 out of the build for exactly one reason — it rebuilds the arena under every
   eye, so ARM 2's guard could only ever report zero and the zero would mean nothing. **ARM 2 IS NOW
   WORN, GREEN, AND ITS FALSIFIER HAS FIRED**, from the owner's own three arms:

   | arm | window checks | window mismatch | reading |
   |---|---|---|---|
   | S1 `run_295_S1_guard_mono.log` (mono, guard ON) | 8400 | **0** | the boring frame, and checks > 0 so the zero is a result (`279` §7) |
   | S2a `run_295_S2a_restore_off.log` (`VIEWRESTORE=0`) | 250803 | **600** | **THE GUARD FIRES.** The instrument can be made to say FAIL |
   | S2b `run_295_S2b_restore_on.log` (`VIEWRESTORE=1`) | 213951 | **0** | ARM 1 removes the class |

   **►►►►►►►► THIS ENTRY IS ANSWERED. `[MEASURED]` 2026-09-02, `298` §0/§1 — R2 PUT THE
   CHARACTERS AND THE PROPS IN BOTH EYES, AND NOTHING WARPS. KEPT IN FULL PER RULE `2`; WHAT
   FOLLOWS IS THE HISTORY THAT LED TO IT. ◄◄◄◄◄◄◄◄**
   **►► AND THE ONE THING R2 DOES *NOT* PROVE, STATED SO NOBODY OVERSTATES IT: at
   `GETV_STEREO_OFFSET=0`, "each eye built its own world" and "eye 1 was handed a copy" are
   INDISTINGUISHABLE BY CONSTRUCTION.** R2 proves the world REACHES both halves. **`RUN-SHEET-297`
   §8 (R4 / S3, the separation gate) is what proves per-eye construction, it is now UNBLOCKED, and
   it is still UNRUN.**

   **►►►► ARM 3 IS NOW WRITTEN. `297`, OFFLINE, NOT BUILT AND NOT RUN. ◄◄◄◄**
   `GETV_STEREO_REBUILD`, default OFF. `objTick`'s build block (`propobj.c:6000-6378`) and
   `chrTick`'s (`chr.c:2855-3227`) are extracted VERBATIM into `objBuildRenderState` and
   `chrBuildRenderState` — **`[MEASURED]` ZERO escaping locals in both, which is what made the cut
   legal** — and `gePropsRebuildRenderPass()` in `chrprop.c` walks `g_OnScreenPropList` once per eye
   and calls them with the sim-owner flag 0. Admission, `PROPFLAG_ONSCREEN`, `chrobjWeaponTick`, the
   child walks and every accumulator stay ONCE PER FRAME. **THE OWNER'S NEXT ACTION IS
   `RUN-SHEET-297`, AND ITS GATE IS THE SENTENCE AT THE TOP OF THIS ENTRY — not a disparity
   number.** S3 (separation) is `RUN-SHEET-297` §8 and does not run until R2 passes: a disparity
   measured on an eye with no world in it is a number about nothing.


0. **►►►►►►►► THE OWNER `[REPORTED]` IT 2026-09-02, AND IT GOES HERE IN THEIR WORDS (§7b2):
   *"THAT TEXTURE SHOWS WEIRD, IT DOESN'T SHOW THE PROPER EXPLOSION. ON THE NORMAL EMULATOR VERSION
   AND ON THE TLb VERSION IT DOES SHOW PROPERLY."* ◄◄◄◄◄◄◄◄**

   The owner also asks a second, separable question: **can a DIFFERENT explosion texture be
   substituted and used in the game?** Likely yes — the port already tracks and binds textures by
   name (`[getv] texbind model`, `[getv] gdltally` are in every run log) — **but do not answer it
   first.**

   **►► DO NOT TREAT THIS AS AN ASSET PROBLEM UNTIL ONE THING IS CHECKED.** `sub_GAME_7F09BBBC`
   (`vtxstore_tick`) **merges duplicate vertex batches and rewrites model references**, it is the
   function that crashes when a mine is shot (`297` §12), and `7a4e7bfd` records that
   `propobj.c:7750` — the rwdata-stride **explosion** crash site — was in the same family of
   pointer-size errors. **Establish whether the texture is wrong or merely being fed the wrong
   data.** Substituting the asset while the second is true only hides it.

   **It renders correctly on the emulator and on TLb, from the same ROM. That is a strong
   [MEASURED]-adjacent falsifier: the asset is almost certainly fine and the port is almost
   certainly mis-feeding it.**

0. **►►►►►► SHOOTING A MINE CRASHES THE GAME, AND IT IS **PRE-EXISTING** — NOT ARM 3'S. `297` §12.
   ◄◄◄◄◄◄** `vtxstore.c:161` filters `type == 1` (**`PROP_TYPE_OBJ`**) then reads `PropRecord`'s
   tagged union as a **`ChrRecord *`**. **Proven pre-existing without a rebuild**, against the saved
   `build-windows/goldeneye_PARENT.exe`: same symbol+offset, same chain, and the **same fault
   address to the byte (`0xbdccc587`) at a different ASLR base** — which is itself the proof the
   garbage is deterministic data, not heap randomness. **A NULL guard is NOT the fix; the pointer is
   WILD.** **Two candidate corrections, not equivalent, deliberately not chosen** — see §12. The
   prior art in `local-only/prior-art/perfect_dark_VR` is the obvious place to settle it.

0. **►►►►►► `295` — ARM 1 AND ARM 2 ARE WRITTEN. **NOT BUILT, NOT RUN, NOT COMMITTED.**
   ARM 3 IS DELIBERATELY ABSENT AND THAT IS A FINDING. ◄◄◄◄◄◄**
   **READ `295` §0, §1, §3, §5, THEN `RUN-SHEET-295`.** ARM 1: the view pair is restored at the end
   of the eye loop, to **the arena's owner** — eye 0 today because `propsTick` is behind
   `geStereoIsFirstEye()`, the LAST eye once ARM 3 exists, and naming the owner is what makes the
   two compose. ARM 2: `GETV_STEREO_PAIRGUARD` compares the eye that ALLOCATED a block against the
   eye whose pair is installed, **from the arena watermark, with nothing stamped** (§7).
   **ARM 3 CANNOT SHARE A BUILD WITH ARM 2's FIRST WEARING** — it rebuilds the arena under every
   eye, so the guard would report zero by construction and the zero would mean nothing (`295` §5).
   **THE ORDER IS: S1 (stereo OFF, guard ON — the boring frame) → S2a (`VIEWRESTORE=0`, the guard
   MUST fire) → S2b (`VIEWRESTORE=1`, it must not) → `292`'s S2 re-run → S3.** Owed and unchanged:
   the eye-1 model collapse (`MODEL_MTX 39->1`) is ARM 3's, not ARM 1's.

0. **►►►►►► `293` — THE DIVERGENCE IS ANSWERED. IT IS NOT ROOMS, IT IS MODELS, AND IT IS THE PASS
   `292` GATED OFF. **OFFLINE ONLY — NOTHING BUILT, NOTHING RUN, NOTHING COMMITTED.** ◄◄◄◄◄◄**
   **READ `293` §0, §2.1 AND §3a.** From `292`'s own eighteen `dlgrab` dumps, with no run:
   rooms are admitted **identically** in both eyes (§5, now a dead theory); the chr/prop **model**
   pass collapses (`MODEL_MTX 39->1`, `MODEL_VTX 17->0`); eye 1's DL-CALL set is a **strict subset**
   of eye 0's in **every** dump. **The arena pointers close it: `MODEL_VTX fresh=0` — the second eye
   allocates NOTHING and replays eye 0's blocks; its single fresh matrix per frame is the
   viewmodel**, which is why the gun and HUD survive and the world does not.
   **`GETV_STEREO_MTXGUARD=2` was always the wrong place** — it cannot restore a matrix that was
   never built (§3), and fault 3 is the same bug seen on the models that still reach the alpha pass.
   **THE REPAIR SHAPE (§3a), AND IT IS NOT YET A PLAN:** a **new render-only pass, per eye, over
   `g_OnScreenPropList`** — re-`dynAllocate` `render_pos`, rebuild the matrices, re-run
   `modelUpdateRelationsQuick`, re-derive `zDepth`, **touch nothing else**. NOT a split of
   `objTick`/`chrTick` and NOT a second tick: both are illegal (§7, two new facts). **Stated cost:
   the second eye's prop admission stays eye 0's.** **THAT CLASSIFICATION IS NOW DONE FOR `objTick` (`293` §3b) AND IT FOUND TWO THINGS:**
   **(a) EVERY accumulator in the block is ALREADY behind `isSimOwner`** — the engine's own
   *"this pass owns the world"* bit (`propobj.c:4548`, `TRUE` always in single player), which is
   `geStereoIsFirstEye()` one level down; the build pass needs **no new guards** for the colour
   lerp (`:5985`), the iris-door SFX (`:6022`/`:6030`), the vehicle wheel (`:6179`) or the aircraft
   rotor (`:6253`). **`propobj.c:6190`'s second, apparently unguarded `wheelxrot +=` is INERT**
   (`var_f0_3` is 0 when `!isSimOwner`) — named because it reads like a bug and is not.
   **(b) ►►►► `293` §3b.3's "ONE BLOCKER" WAS NOT ONE. RETRACTED BY `294` §1. ◄◄◄◄**
   `sub_GAME_7F03F540` (`propobj.c:6347`) builds the tank's entry rect from `V2W · (W2V · world)` —
   **a ROUND TRIP, not a view-dependent write.** `camGetWorldToScreenMtxf()` is the **bare lookat**
   (no projection, no visibility scale) and `currentPlayerGetViewToWorldMtxf()` is its exact
   transpose-inverse, built five lines apart from the same three vectors (`bondview2.c:9005`,
   `:9010`). **The eye offset enters and leaves on one line. There is no 250-unit anything, there is
   no "last eye wins", and NOTHING IS OWED BEFORE THE BUILD PASS.** (`278` §5's mono "tank
   unenterable" is still a DIFFERENT question touching the same struct — do not merge, `263` §1.)
   **(c) ►►►► `293` §3b.4's "SECOND STORE THAT IS NOT THE ARENA" DOES NOT EXIST. RETRACTED BY `294`
   §2. ◄◄◄◄** `modelFindNodeMtx` returns **`&model->render_pos[index].pos`** (`model.c:669-676`) —
   **the `dynAllocate`d arena block itself**; only the INDEX comes from rodata. **Doubling the pools
   is EXACTLY what covers them**, and those matrices were already in the per-eye bucket. `293` §3b.4
   named `modelFindNodeMtx` and described its neighbour **`modelGetNodeRwData`** (`model.c:734`, 65
   lines away, one word different), whose only writes in this block are two idempotent `visible`
   flags. **§3b.5's "Undecided" is now EMPTY.**
   **AND `chrTick` IS NOW CLASSIFIED TOO (`293` §3c) AND IT DOES NOT MATCH `objTick`.**
   **`chr.c:2893` `g_CurModelChr->flinchcnt += g_ClockTimer` IS BEHIND NO GUARD AT ALL** — it sits
   inside the build block, so a body driven twice per frame makes **every character recover from
   being shot in HALF THE TIME**. That is mission point `3`'s test answered *yes*, and it is the one
   that would have shipped silently. **(a) above is true of `objTick` and FALSE of `chrTick` — do
   not generalise it.** The rest of `chrTick`'s build is **cleaner** than `objTick`'s: the joint
   list is rebuilt **from NULL** each pass (`chr.c:2914`, torn down at `:2846-2851`, finalised at
   `:3222-3223`) and both matrix lists come from a fresh `dynAllocate`, so once `flinchcnt` is
   hoisted out it re-runs cleanly. **AND THE INVARIANT (`293` §3c.3): THE BUILD MUST RE-RUN AS A
   WHOLE PER EYE — A PARTIAL RE-RUN RE-TRANSFORMS.** `chr.c:3160-3161` transforms `render_pos`
   IN PLACE and is correct exactly once per fresh allocation; `292`'s fault 3 is what a mismatched
   pairing looks like on screen.
   **►►►► AND `294` SUPPLIES THE OTHER HALF OF THE DESIGN CONSTRAINT: THE PAIRING INVARIANT. ◄◄◄◄**
   The view pair (`field_10CC` = W2V, `viewtoworldmtxf` = V2W) and every `render_pos` block written
   under it are **ONE coordinate system with ONE owner — any read of either must happen while that
   eye is installed.** Break it and §3b.3's round trip, the shot path and the arena all fail at once
   by the full separation. **The shot path is view-space END TO END** — `shotdata.viewOrigin` is
   literally `{0,0,0}` (`gunfire.c:6117`) and the hit tests read `render_pos` via `modelFindNodeMtx`
   — **and it is safe today ONLY because `propsTick()` and `chraiCheckUseHeldItems()` sit inside the
   SAME eye-0 gate** (`lv.c:908`, `:914`, `:932`). **AND `PROPFLAG_ONSCREEN` GATES HIT FIDELITY, NOT
   JUST DRAWING** (`propobj.c:1399`): onscreen props get a precise per-node line test, everything
   else a bounding sphere — **a second, independent reason to keep admission once per frame.**
   **ONE BOUNDED QUESTION IS LEFT (`294` §3.6): the eye loop restores the rectangle, the aspect and
   the camera scales but NOT the view pair (`lv.c:1042-1046`), so once `lvlRender` returns the pair
   is the LAST eye's while every `render_pos` is eye 0's.** Whether anything reads either in that
   window is **NOT established** — 69 call sites across 13 files, and `294` §5 proposes a stamped
   `GETV_STEREO_PAIRGUARD` to answer it by measurement instead of by reading them.
   **New this session:** `repo\docs\293-…md` and `goldeneye-native\getv\tools\dlgrab_eyecensus.py`
   (`--selftest` / `--scissors` / `--arena`, `SELFTEST PASS`) — **`293` IS COMMITTED** (`a86fc22`).
   **`294` (`repo\docs\294-…md`) IS NEW AND NOT COMMITTED**, and it is **OFFLINE ONLY — source
   reads, nothing built, nothing run, S3 still never run.**

0. **►►►►►► `292` — THE EYE LOOP IS BUILT AND RUN. S2 CAUGHT THREE FAULTS. `258` STAGE 6. ◄◄◄◄◄◄**
   **READ `292` §5a FIRST — it carries the three faults, the numbers and what is still open.**
   **THE REPAIR THAT HAS NOT BEEN MADE: who owns `model->render_pos` per eye.** `GETV_STEREO_MTXGUARD=2`
   suppresses the symptom and MUST NOT SHIP. **AND THE REAL QUESTION IS UPSTREAM OF IT: the two eyes
   admit different geometry (1060 vs 622 triangle commands at ZERO separation with identical
   projections), which is why a model reaches the alpha pass in one eye without the opaque pass that
   rebuilt its matrices.** S3 has never run — no separation has ever been applied.
   The loop is nested INSIDE `lvlRender`'s per-player body (`lv.c:785`), leaves `getPlayerCount()`
   at 1 (`258` §1.5), and emits **two viewport rectangles into ONE display list with ONE swap** —
   split-screen's own mechanism, so `gfx_run()` is never called twice and **nothing under
   `getv/port/` is touched: `verify` stays `15/15`, NO REGEN OWED.** The eye **translation** goes
   into `cam_pos` at `bondviewUpdateCameraMatrices` — the VIEW matrix (`255` §1) — and the
   projection is **replaced** at `viSetupCurrentPlayerView` by **four tangents per eye per frame**
   (`P2`), after `guPerspectiveF` and not instead of it, so `g_viPerspNorm` is untouched. The eye
   vector is read from `gePoseCurrent()` — `P6` on the live path, `291`'s spine consumed.
   **THREE READS CHANGED THE CODE AND NONE IS VISIBLE FROM THE EYE LOOP'S OWN LINES:** `propsTick()`
   sits INSIDE the per-player body (so the tick is gated to eye 0, short-circuit first);
   `viSetViewSize()` writes back into `g_CurrentPlayer->viewx` (so the rectangle is captured once
   before the loop, or the second eye gets a quarter); and **both memory pools are sized by player
   count** (§7 — the one that would have crashed). **OFFLINE `37/37`**, and the falsifier
   (`GETV_STEREO_MODE=2`) is tuned to be indistinguishable from the real thing at ONE depth and to
   fail only the `1/D` ratio — which is how `B1` survived from `43` to `71`.
   **`RUN-SHEET-292` is the build, the six-string binary gate, and five arms with every outcome
   written before the run: S1 off / S2 two eyes at ZERO offset (the *driven twice* counter-example
   search, and it runs FIRST) / S3 the gate / S4 the falsifier / S5 the cost against `272`.**
   **DO NOT PLAN PAST S3.**

0. **►►►►►► `290`/`291` — THE POSE SPINE. `258` STAGE 5. THE SIM OWNS THE POSE. **NOW BUILT,
   RUN AND GREEN (`291`)** — promoted to the WORKS row above; kept here for the mechanism. ◄◄◄◄◄◄**
   Head + both hands + a body proxy are game-side state (`posespine.h`/`.c`, new), written BEFORE
   the tick by `gePortPoseBeginFrame()` at the top of `lvlRender` and read by game code through
   `gePoseCurrent()` — `P6`/`P9`. All four joints present from the first line though only the head
   is driven (`P7`); static storage, cost paid once (`P4`); quaternion orientation carries no
   matrix-layout commitment (the row-vector/negated-yaw view compose is STAGE 6, §7). **NO
   HARDWARE**: identity, or a synthetic path under `GETV_POSE_SELFTEST`, as `port_input.c` fakes a
   pad. **THE INSTRUMENT, `GETV_POSETEST`, CAN FAIL (`P5`, rule `15`):** a known trajectory in, the
   same out, at the same sequence; the freshness reference is the probe's OWN call count, not the
   writer's, so a uniformly-shifted system cannot hide the off-by-one (`267`/`271`/`272` in a new
   place). Requires `GETV_SIMDIV=1`. Mode 2 self-falsifies. **Offline `10/10`**, incl. two
   independent proofs the freshness gate fires (external wrong-bracket + mode 2). **`RUN-SHEET-290`
   is the build, the five-string binary gate, and the three arms (A1 identity / A2 round-trip / A3
   self-falsify) with every outcome written before the run.** **`291` RAN ALL THREE ON A FRESH EXE (`00:06`, 18,039,699 bytes): A2 `VERDICT PASS stale=0 maxerr=0.000`, A3 `VERDICT PASS (detector fired)`, A1 inert. A2 IS GREEN — STAGE 6 IS UNBLOCKED (`258` STAGE 6, `NEXT-SESSION-PROMPT-292`).**

0. **►►►►►► `289` RAN FIVE ARMS. THE ROOM CANDIDATE IS DEAD AND THE SMOOTHNESS COMPLAINT IS NOT
   GRAPHICS — IT IS THE MOUSE. READ `289` FIRST. ◄◄◄◄◄◄**
   **`[MEASURED]` 2026-08-31, ONE binary (`18:47:30`, `18,036,265` bytes), fifteen strings, zero
   build errors. `verify` reads `15/15` before AND after the build.**

   **(1) `getROOMID_isRendered` IS ELIMINATED.** `GETV_PROPROOMTEST=0` was written as `287` wrote
   `GETV_PROPCULLBOX` — opt-in, inert unset, banner, applied at ONE call site and deliberately NOT
   inside `getROOMID_isRendered` (AI and spawn logic read it at eight other sites). **The knob TOOK
   and `[REPORTED]` the props STILL VANISH.** `RUN-SHEET-289` §6 outcome 4 fired. **DO NOT RE-RUN
   R2.** `288`'s standing candidate died to the falsifier written for it.

   **(2) `room` IS ON A DENOMINATOR IT CAN BE READ ON, AND THE REPORT CARRIES ITS OWN ARITHMETIC
   GATE.** `roomprop` (per prop, once), `nolist`, `view` and `calls` beside `288`'s per-ENTRY `room`
   and per-PLANE-HIT counters, three denominators on three lines. **`roomprop / box = 26.4x`** —
   `288`'s *"by how much is NOT MEASURED"* is measured. **The sum-check BALANCES on hardware under
   BOTH identities**, and it was shown to print `MISMATCH` offline first. **92.5% is what ANY
   broad-phase room cull reads and is NOT evidence** — written into the sheet before the run.

   **(3) ►► `dist=0` WAS A MASKED ZERO. THIS IS THE METHODOLOGICAL FINDING OF THE SESSION.**
   `dist` read 0 in `288` ARM 8, 8b and `289` R1 and **reads 17,124 in R2**, because it sits
   DOWNSTREAM of a test that rejects 92.5% of everything. **The verdict survives (it removes nothing
   in the shipping config); the reasoning does not.** **STANDING RULE: A ZERO DOWNSTREAM OF A TEST
   THAT REJECTS MOST OF ITS INPUT IS A MASKED ZERO, NOT AN EXONERATION.** `275` §1's shape, one
   level over.

   **(4) `GETV_SIMHZ` IS CLEARED — ON THE NUMBER AND ON THE WEAR.** S1 settled `jdp` **8.54%** vs S2
   **8.05%**, overlapping, term-OFF marginally lower — and `[REPORTED]` *"no waiting feel"* on BOTH.
   **S1 also reproduces `288` J1 to 0.25 points across two binaries**, so the statistic is stable
   run to run. **`RUN-SHEET-289` §7's first written outcome fired: the complaint had NO CANDIDATE
   LEFT.**

   **(5) ►►►► AND THEN THE SESSION LEAD RE-DIAGNOSED IT FROM S3. IT IS MOUSE-ONLY, IT IS THE SHAPE
   OF THE TURN, AND IT IS `258` STAGE 7 (AIM, `P8`) — NOT A RENDERING ITEM.** See the SMOOTHNESS
   entry below, rewritten. **`287` §2's *"mouse and pad are the SAME PATH so the question needs no
   arm"* is RETRACTED BY WEAR — a source read cancelled the arm that mattered, and it cost five
   sessions.**

   **(6) THE OFFLINE VALIDATION IS A COMMITTED FILE THIS TIME** —
   `getv/tools/cullwhy_harness.sh`, which extracts the real functions from `propobj.c` BY NAME so it
   can never test a stale copy. `288`'s harness lived only in its session and is gone.

0. **►►►► `288` RAN ALL SIX ARMS. TWO QUESTIONS CLOSED, ONE CANDIDATE PROMOTED. ◄◄◄◄**
   **`[MEASURED]` 2026-08-31, ONE binary (`17:09:32`, `18,035,038` bytes), ten strings, zero build errors.**

   **(1) `vsync=0` IS CLEARED AT THE JITTER RESOLUTION, AND THE CARRIER IS NOW `GETV_SIMHZ`.**
   J1 (`vsync=1`) settled `jdp` mean **8.29%** over 10 windows vs J2 (`vsync=0`) **7.70%** over 8,
   ranges 7.3-9.2 and 6.9-8.5 — **overlapping, with `vsync=0` marginally LOWER**, the opposite
   direction from the complaint. Every settled window `600/600` in `1x` in both. **`RUN-SHEET-288`
   §7's written outcome fired: the smoothness complaint is NOT in the presented-frame interval,
   even one level finer than `287` 4E could see. `GETV_SIMHZ` is the ONLY candidate left standing**
   (`287` already named it; `285` S1's *"super smooth"* ran with it, and most of this project did not).

   **(2) `GETV_FPS=panel` IS BUILT, RUN AND WORN.** `GETV_FPS=panel -> 120 Hz, QUERIED FROM SDL`,
   and the `pace:` banner then carries 120. **One env value correct on the 120 Hz desk and the
   180 Hz one.** `GETV_SIMHZ=query` chains off it for free. **Its sibling refusal fired for real in
   V2:** `simhz CONTAMINATED -- rate is 0 ... TERM STAYS OFF` at `GETV_FPS=0`. Rule `17`, unprompted.

   **(3) THE JITTER STATISTIC IS VALIDATED ON HARDWARE — AND BOTH ITS THRESHOLDS WERE WRONG, MINE.**
   `jdm > 20%` on the negative control is **MEASURED FALSE** (hardware 14.5%; the harness said 40.9%
   and is scatterier than the real uncapped loop). `jdp < 10%` was written per-window with **no boot
   exclusion** and V1's boot window read 32.8% — corroborated by nine hitches in the OLD bins, so the
   statistic is right and the contract was wrong. **What survives is the discrimination on the
   MATCHED metric: V1 settled `jdm` 2.9-4.7% vs V2 14.1-14.5%, a 3-5x separation.**
   **CORRECTED CONTRACT: a jitter threshold is scored on SETTLED windows. The boot window is
   REPORTED, NEVER SCORED.** `sd` vs `jd` also discriminated on hardware, not only in the harness.

   **(4) THE VANISHING PROPS: `dist` IS DEAD, THE BOX IS ELIMINATED, `room` IS THE CANDIDATE.**
   See the props item below, rewritten.

   **(5) `RUN-SHEET-288` HAS THREE DEFECTS OF ITS OWN AND `GETV_CULLWHY`'s REPORT HAS THREE MORE.**
   `288` §6 and §10. **The one that will bite next: GATE 2 (`ours: x=367.333`) MANDATES OPEN ITEM
   2's FAULT CELL — they are the same number — so every arm in that sheet has broken front-end menu
   text BY CONSTRUCTION.** It was `[REPORTED]` as a fresh regression this session because nothing
   said so. **Do not "fix" it by moving to `1825x1369`: that prints `ours: x=0`, which is also what
   `WIDESCREEN=1` prints, so gate 2 would silently stop discriminating** (rule `17`).

1. **►►►►►► SMOOTHNESS IS NOT A RENDERING ITEM. IT IS THE MOUSE, AND IT BELONGS TO `258` STAGE 7
   (AIM, `P8`). `289`. ◄◄◄◄◄◄**
   **`[REPORTED]` BY THE SESSION LEAD, UNPROMPTED, AFTER `289` S3 — and it re-diagnoses a
   five-session-old complaint:** *"this only happened to me with my mouse... it doesn't happen on
   the controller... it's the way bond walks/turns... it starts to turn almost like a car when the
   mouse is moved left or right when going forward. It's not a normal wasd type feel... I think
   this is not graphic related."*
   **FOUR FACTS, ALL NEW: (1) MOUSE-ONLY, the pad does not do it · (2) `289` S3 (cap 60) REPRODUCED
   it and is the only arm that did · (3) it IMPROVES with frame rate · (4) it is NOT judder, it is
   the SHAPE of the motion.**
   **►► FIVE SESSIONS OF PACING INSTRUMENTS CAME BACK CLEAN BECAUSE THE FAULT IS NOT IN THEM.**
   `287` 4A-4E, `288` V1/V2/J1/J2, `289` S1/S2/S3 — vsync, the frame cap, the pacer's sleep booking,
   the presented-frame distribution and the sim rate, **all cleared, three instruments built.**
   Rule `16`; `HANDOVER` §5.
   **►► `287` §2 CANCELLED THE ARM THAT WOULD HAVE FOUND IT, AND THAT IS A RETRACTION** (§4): mouse
   and pad share a **SINK** (`out->rx`), not a **PATH**.
   **►► `[MEASURED]` FROM SOURCE, READ NOT GREPPED, NO CAUSE NAMED AND NO FIX PROPOSED —
   `port_input.c:1013-1100`, `docs/MOUSE.md`.** Four properties the mouse path has and the pad does
   not: **M1** a PER-FRAME accumulator with no timestep (at most one full deflection emitted per
   frame, remainder carried) · **M2** a backlog cap expressed in FRAMES (`4 * 32767`), so **66.7 ms
   at 60 fps and 33.3 ms at 120** — matches fact 3 · **M3** a mouse-only deadzone **FLOOR**: any
   non-zero movement is lifted to 20% of full scale, and `MOUSE.md` says *"applied only to the
   mouse; a physical stick keeps its deadzone"* — **the pad has a 20% dead BAND, the mouse has a 20%
   FLOOR, and there is no small mouse turn** · **M4** `GE_MOUSE_COUNTS_FULL = 21`, so the map is
   **saturated nearly always** and M1's drain rate, not the gain, sets the turn.
   **IT MATCHES ALL FOUR REPORTED FACTS, WHICH IS EXACTLY WHY IT MUST BE MEASURED AND NOT
   BELIEVED** (`275` §1, `277` §6.2).
   **►► THE ARM IS FREE AND THE INSTRUMENT ALREADY EXISTS, UNRUN: `GETV_MOUSE_SELFTEST=<counts>`**
   (`port_input.c:961`) — synthetic constant mouse movement per frame, so degrees-per-count can be
   measured against a frame rate with no hand on the mouse. **`GETV_MOUSE_SENS` and
   `GETV_MOUSE_SELFTEST_Y` sit beside it.**
   **►► AND OPEN ITEM 9's CROSSHAIR AUTO-CENTRING IS A SECOND OWNER REPORT ABOUT MOUSE CONTROL,
   ALREADY FILED UNDER `P8`/STAGE 7.** Two reports in one subsystem is rule `16`'s ranking signal.
   **STAGE 7 may run BESIDE STAGE 6 (`258`), so this is not blocked by stereo and stereo is not
   blocked by it.**

   **THE PACING HISTORY BELOW IS ALL STILL TRUE AND IS WHY THE INSTRUMENTS EXIST — but it is no
   longer the ranked question. Rule `2`: nothing deleted.**
   **►► `vsync` CLEARED (`287` 4E, `288` J1/J2) · `GETV_SIMHZ` CLEARED ON THE NUMBER AND THE WEAR
   (`289` S1/S2). See item 0.**
   **`[MEASURED]` 2026-08-31, five arms, ONE binary (`02:24`, 18,026,915 bytes), no rebuild.**
   **THE PANEL IS 120 Hz — `PANEL REPORTED BY SDL: 120 Hz`, in a run log, for the FIRST TIME IN THIS
   PROJECT.** `285` §2's hole is closed and `285` S1's *"super smooth"* SURVIVES: `GETV_FPS=120` with
   `vsync=1` was asking for the panel, not double it. Every earlier "120 Hz" was `[REPORTED]`.
   **THE INSTRUMENT IS VALIDATED BY A MOVED MASS, NOT BY ARGUMENT — `287` §4B.** `FPS=60` on the same
   panel put **99.73% into the `2x` bin** (3,642 of 3,652) against a prediction of ≥95%, written first.
   A stamp in the wrong place cannot produce 8.333 ms locked to the panel at 120 and 16.667 at 60.
   **`GETV_PACEHIST` IS THE FIRST INSTRUMENT THIS PROJECT HAS THAT SEES BETWEEN FRAMES.**

   | arm | recipe | result |
   |---|---|---|
   | **4A** play | `VSYNC=1 FPS=120` | **99.90% `1x`** — 8,917 of 8,926 over 15 windows, mean 8.333 ms |
   | **4B** validate | `VSYNC=1 FPS=60` | **99.73% `2x`** — the mass moved on command |
   | **4C** negative control | `VSYNC=0 FPS=0` | **no mode** — 3,597 of 3,600 in `<0.5x`, mean 0.196-0.339 ms (~3-5k fps) |
   | **4D** free stopwatch | 360° spin, 60 vs 120 | **1.65 s vs 1.80 s — ratio 1.09, not 2.0** |

   **►► AT PLAY SETTINGS PRESENTATION IS CLEAN, INCLUDING THE FAST TURNING THE COMPLAINT IS ABOUT.**
   Three hitches in a two-minute session (`45.9`, `62.1`, `60.7` ms, each with its catch-up partner in
   `<0.5x`); every other window is a clean `600/600`. **The judder `285` reported is NOT in the
   presented-frame interval at `vsync=1`.**
   **►► `285` §1.1 IS REAL AND IS NOW `[MEASURED]`, NOT RETRACTED.** The pacer books the sleep it ASKED
   for: **error -0.29 ms per frame, consistent across all 15 windows of BOTH capped arms** (-120 to
   -175 ms per ~4.7 s). **It does not reach the screen — vsync absorbs it.** Two findings, NOT merged:
   the mis-booking is confirmed, its consequence at these settings is nil.
   **►► `285` §1.4 IS DEAD, BY STOPWATCH.** 4D: the failure mode was **2.0** and the reading was **1.09**,
   in the wrong direction, with the gap ~11x the hand-timing scatter. `287` §2's source read was right —
   `bondview2.c:7366` and all four branches of `bondviewCurrentPlayerUpdateSpeedTheta` carry the delta.
   **Recorded as NOT FRAME-RATE-PROPORTIONAL, not as "identical"** — 1.09 on two single hand readings is
   not a claim the rates match (`277` §6.1).
   **►►►► ARM 4E RAN, AND IT CAME OUT OPPOSITE TO THE PREDICTION. `285`'s DIAGNOSIS IS NOT SUPPORTED
   BY THE INSTRUMENT. ◄◄◄◄**
   `[MEASURED]` `VSYNC=0 FPS=120`, `SLOTFREE=1`, gates clean, **21,736 intervals over 37 windows — the
   longest run of the day: `1x` = 21,700 = 99.83%**, against 4A's 99.90% at `vsync=1`.
   **THE PREDICTION WAS "the mass leaves `1x` and smears, no clean mode." IT IS MEASURED FALSE — MINE,
   in the arm I wrote it for.** The falsifier written beside it fires instead: **"`vsync=0` was the
   judder" is NOT supported at this instrument's resolution, and `285`'s diagnosis needs re-reading
   before anything is built on it.**
   **A HINT THE BINS CANNOT HOLD, AND IT IS NOT A FINDING:** mean `p99-p50` 0.646 ms (4A) vs **0.707 ms**
   (4E); ragged windows (min<6.25 or max>10.4 ms) 3/14 = 21% vs **16/36 = 44%**. **The runs are not
   length- or activity-matched, so this is a direction to instrument, not a result.**
   **►►►► AND 4E EXPOSES THE INSTRUMENT'S OWN LIMIT — THIS IS THE REAL FINDING. ◄◄◄◄**
   **The `1x` bin is `[0.5,1.5)` of the panel period = 4.17 to 12.5 ms, THREE TIMES WIDE. A run
   alternating 6 and 10.5 ms scores 100% `1x` and would feel terrible.** `GETV_PACEHIST` catches
   **DROPPED AND DOUBLED FRAMES**; it does NOT catch **JITTER INSIDE A FRAME PERIOD**. **That is
   `285` §3.3's own critique — *a mean of 16.67 ms is identical for an even run and one alternating 8
   and 25* — ONE LEVEL FINER, now applying to the instrument built to answer it.** The turn complaint
   may live entirely in that blind spot.
   **WHAT `288` OWES: A JITTER STATISTIC, NOT A COARSER ONE.** The recorder already keeps a sample
   array (`ge_ph_keep`) and already prints p50/p90/p99/min/max — **so most of it is free.** Wanted: the
   spread reported per window as a first-class number (stddev, or a fine sub-bin histogram across
   `0.5x`-`1.5x`), so an even 8.33 and an alternating 6/10.5 stop reading identically. **`P5`: a figure
   that cannot fail is not an instrument.**
   **SCOPE LIMIT, RECORDED RATHER THAN GLOSSED: 4E IS NOT A REPLAY OF HISTORY.** It ran with
   `SIMHZ=query` and `SIMDIV=1`; the configuration actually played for most of this project had
   NEITHER. **4E isolates vsync with everything else correct. It does not tell us what the old runs
   felt like** — and it makes `GETV_SIMHZ`, not vsync, the untested carrier of `285` S1's
   *"super smooth."*
   **►► TWO DEFECTS IN `RUN-SHEET-287` ITSELF, FOUND BY RUNNING IT. Fix before it is used again:**
   **(a) §3's prediction table and the §1 gate `simhz ... 0.500000 fields per frame` carry a HIDDEN
   PANEL CONSTANT.** The bins are `panel ÷ cap` and the simhz line is `60 ÷ cap` — at `FPS=60` the
   CORRECT line is `1.000000`, and 4B printed it. **The session lead runs on a 180 Hz panel as well as a
   120 Hz one** (`287`), so on the 180 Hz desk 4B lands in `3x` and its stated prediction FAILS on a
   perfectly working instrument. **Restate both as ratios.**
   **(b) §3's row *"stamp accidentally before the swap -> 4C reads intervals near 0 ms"* CANNOT
   DISCRIMINATE.** With `VSYNC=0 FPS=0` the swap genuinely does not block, so near-zero intervals are the
   CORRECT reading. 4B outranks it. **Strike the row rather than honour it.**
   **►► AND THE AUTO-DETECT IS NOW CHEAP, `288` MATERIAL:** `gfx_sdl2.c:756` already queries
   `SDL_GetWindowDisplayIndex` + `SDL_GetCurrentDisplayMode`, so it already follows the window between
   monitors. It is gated on `GETV_PACEHIST>0`, LAZY (first present — far too late for the cap, parsed at
   `:457`), and consumed by nothing. **`wnd` is created at `:392`, 65 lines BEFORE the cap is resolved.**
   Hoist the query, give `GETV_FPS` a `panel` spelling, and **`GETV_SIMHZ=query` chains off
   `ge_pace_framerate` for free** (`frametiming.c:125`) — one env value covers both desks. **It MUST
   REFUSE, NOT FALL BACK, on an unknown rate (rule `17`), stay OPT-IN (`48`), and print the queried
   number every run.** Note `ge_config.c:355`'s `framerate=` key still rejects >60 with reasoning that
   `GETV_SIMHZ` has since made wrong.
   **►►►► `288` HAS WRITTEN WHAT 4E SAID WAS OWED, AND VALIDATED IT WITHOUT A BUILD. NOT BUILT,
   NOT RUN. ◄◄◄◄**
   **THE JITTER STATISTIC IS IN `gfx_sdl2.c`** — `sd` (stddev), **`jd` (mean `|dt[n]-dt[n-1]|`)** and a
   **10-bucket sub-histogram across the `1x` bin**, all three per window, all three inside the existing
   `GETV_PACEHIST` report. `jd` is the one that names the failure: an even run and a SLOW DRIFT both
   read ~0, an ALTERNATION reads high — and `sd` alone cannot tell those apart, which is why it does
   not ship alone.
   **`[MEASURED]` OFFLINE, BEFORE ANY BUILD — the real `ge_pacehist_record`/`_emit` extracted from
   `gfx_sdl2.c` and driven by five synthetic streams (`288`, harness in the session, gcc, clean under
   `-Wall -Wextra`).** The blind spot 4E exposed is now visible:

   | stream | old bins | `jdp` | sub-1x |
   |---|---|---|---|
   | even 8.333 ms | 100% `1x` | **0.0%** | one column |
   | **alternating 6.0 / 10.5 ms** | **100% `1x` — identical** | **54.0%** | **two columns, hole between** |
   | slow drift 8.0 -> 9.0 ms | 100% `1x` | **0.0%** (`sd`=0.288) | one column |
   | even 16.667 ms | 100% `2x` | 0.0% | — |
   | uncapped ~0.25 ms | 100% `<0.5x` | 1.2% / **`jdm` 40.9%** | — |

   **►► AND THE HARNESS FALSIFIED MY OWN PRE-RUN CONTRACT, WHICH IS WHY IT WAS BUILT.** The first
   draft predicted *"`jd` MUST BE LARGE on the uncapped control"*. It came back **0.103 ms** — tiny in
   ms, **40.9% of its own mean** — because at ~4,000 fps the intervals themselves are 0.25 ms.
   **A BARE-ms JITTER FIGURE CARRIES A HIDDEN CAP CONSTANT EXACTLY AS §4's DEFECT (a) CARRIES A HIDDEN
   PANEL CONSTANT.** Fixed the same way §4 fixes that one — **as ratios**: `jdp` (% of panel period)
   scores any arm that PRESENTS, `jdm` (% of window mean) scores an UNCAPPED arm. **Which one an arm is
   judged on is now part of the arm.** `P5`, and it fired on the author before it fired on a run.
   **AND `GETV_FPS=panel` IS WRITTEN — §3's cheap item, one binary with the above.** `ge_panel_hz_query()`
   hoisted above `gfx_sdl_init`'s cap parse, asked fresh so it follows the window between monitors.
   **It REFUSES on an unknown rate — prints why and exits, never falls back** (rule `17`); it is OPT-IN,
   so a numeric `GETV_FPS` is byte-for-byte the run it was before (`48`); and **`GETV_SIMHZ=query`
   chains off `ge_pace_framerate` for free** (`frametiming.c:126`), so ONE env value is correct on both
   the 120 Hz and the 180 Hz desk. `ge_config.c:355`'s `framerate=` key is UNTOUCHED — its >60 rejection
   is now reasoned wrongly, but changing a default is the session lead's call (`286` §2).
   **`tools/fetch-thirdparty.sh verify` NOW SAYS `DIFFERS getv/port/fast3d/gfx_sdl2.c`. THAT IS
   CORRECT AND EXPECTED** (§0a of `RUN-SHEET-287`) — the file is gitignored and regenerated, so the
   **regen is owed AFTER the arms are worn**, not before, or the instrument is deleted.
   **RUN SHEET: `RUN-SHEET-288.md`. The build gate now wants EIGHT strings.**

   **►►►► ARM 7 RAN AND THE ROOM RECTANGLE IS ELIMINATED. THE VANISHING PROPS ARE NOT THE BOX.
   `[MEASURED]` 2026-08-31 20:40. ◄◄◄◄**
   `run_288_7_propcullbox_off.log` — **the knob TOOK** (`[getv][propcullbox] GETV_PROPCULLBOX=0` is
   in the log, so this is not a clean null result), gates clean, all six sites non-zero.
   **`[REPORTED]` WITH THE BOX OFF THE PROPS STILL VANISH.** `RUN-SHEET-288` §8b's written outcome #2
   fired exactly as stated. **DO NOT RE-RUN ARM 7.**
   **TWO NEW `[REPORTED]` FACTS FROM THE SAME SESSION, AND THEY NARROW IT:**
   **(1) IT HAPPENS WHEN CLOSE TOO** — the prop just has to be further out toward the edge, and
   **further away, MORE of the screen makes it vanish.** **(2) IT IS SYMMETRIC — LEFT AND RIGHT:**
   *"on the left side it's the car, and on the right side the green bushes above the fence."*
   **FACT 1 BADLY DAMAGES THE `32000` RADIUS** — a hard distance cull cannot remove something you are
   standing beside — **but it is `[REPORTED]` against, not measured against, so it is NOT declared
   dead.** **FACT 2 POINTS AT THE LEFT/RIGHT PLANES**, which `bondview.c:986` builds from
   `c_halfwidth * c_scalex`, **symmetric by construction** — the shape reported.
   **A MECHANICAL READING THAT FITS FACT 1 AND IS NOT YET A FINDING:** the margin is
   `getinstsize(model)` = `BoundingVolumeRadius * scale` (`model.c:1184`), **a bounding sphere in
   WORLD units** — a fixed world radius subtends a smaller angle with distance, so the surviving
   screen band NARROWS as you back away. **It matches the report exactly, which is precisely why it
   must be measured and not believed** (`275` §1's grep-for-a-guard, `277` §6.2's
   numbers-without-mechanism).
   **AND THE CANDIDATE NEITHER ARM EVER TOUCHED:** `posIsOnScreen` opens with
   `getROOMID_isRendered(roomnum)`. **NEITHER `GETV_ROOMSCISSOR` NOR `GETV_PROPCULLBOX` TOUCHES THAT
   TEST**, so it has survived two arms untested — and *"while you are looking off in a different
   direction"* is what a view-driven room-visibility cull sounds like.
   **►►►►►► `GETV_CULLWHY` RAN. `dist` IS DEAD BY MEASUREMENT, THE PLANES ARE NOT INCRIMINATING,
   AND `getROOMID_isRendered` IS THE STANDING CANDIDATE. `[MEASURED]` 2026-08-31 17:31 / 17:36. ◄◄◄◄◄◄**
   **`twin-disagree=0` IN BOTH RUNS, so every per-plane number is live** (`271` §7, rule `17`).
   ```
   ARM 8   room=1134409 fog=12257 occl=2163 box=38996 dist=0 | drawn=36809
           planes: near=0     left=0      right=0      top=0     bottom=0
   ARM 8b  room=1727224 fog=12463 occl=2494 box=0     dist=0 | drawn=55595
           planes: near=7310  left=15289  right=38400  top=4978  bottom=9831
   ```
   **THE ACCOUNTING-BALANCE ARM PASSES: `box` dropped to 0 and the rejections REAPPEARED in the
   per-plane counts. They moved; they did not vanish. So ARM 8's reading stands.**
   **►► `dist=0` IN BOTH. THE `32000` RADIUS IS DEAD — and this time MEASURED, not `[REPORTED]`
   against.** `§8d` refused to declare it dead on a report; it is dead now. **And `§8e`'s written
   falsifier — *"`dist` LARGE means THE INSTRUMENT is wrong, not the report"* — DID NOT FIRE. The
   instrument and the owner's report AGREE**; `HANDOVER` §5 did not have to be invoked.
   **►► THE FIVE VIEW PLANES ARE MEASURED AND ARE NOT INCRIMINATING.** `left+right` = 70.8% of
   plane-hits, `top+bottom` 19.5%, `near` 9.6% — the reported shape, **and NOT advanced as a
   finding, because props sit on a GROUND PLANE and left/right dominance is what ANY level would
   produce** (`275` §1's shape). **`right/left = 2.51`, so `§8e`'s "roughly EQUAL" clause did not
   fire — and the counter CANNOT test symmetry either way**: the frustum is symmetric by
   construction and measured so (`c_screenleft=0.000`, byte-identical in both runs), so a
   cumulative counter reflects WHERE THE PLAYER LOOKED. **A defect in the stated outcome, mine.**
   **►►►► THE SITE, NAMED: `propobj.c:14087`, `getROOMID_isRendered(roomnum)`.** `§8e`'s written
   outcome *"`room` LARGE -> the cull neither knob touches, and the two arms were looking in the
   wrong place from the start"* **FIRED. NO FIX IS PROPOSED AND NONE MAY BE INFERRED.**
   **►► AND THE COUNTER CANNOT YET BE COMPARED TO THE OTHERS — A DEFECT IN THE INSTRUMENT'S OWN
   REPORT LINE.** `propobj.c:14081` is a **`while` loop over the prop's room list** and `:14085`
   increments `room` **once per UNRENDERED ENTRY**, continuing; every other counter is reached at
   most once per call, after the `break`. **So `room=1,134,409` is ENTRIES TRAVERSED, NOT PROPS.
   "29x bigger than `box`" is NOT a reading this report can support.** The per-prop outcomes DO
   balance (`36809+38996+12257+2163 = 90,225`). **`room` is very likely still the largest term. BY
   HOW MUCH IS NOT MEASURED, and putting it on the same denominator is the NEXT INSTRUMENT.**
   Two more report defects in `288` §6: **the plane counters MULTI-COUNT** (`:14130` sets every
   rejecting bit, so 75,808 is plane-hits, props are 38,400-75,808), and **with `PROPCULLBOX` at
   its shipping default the planes are UNREACHABLE** (`:14126`'s `else`), so ARM 8's five zeros are
   expected by construction and are not evidence. **That is why 8b was mandatory.**
   **►► THE FRUSTUM, RECORDED WITHOUT A THEORY:** half-angles **x=53.84 deg, y=30.00 deg**;
   `tan(53.84)/tan(30) = 2.370` vs geometric `160/90 = 1.778` — **a ratio of exactly `4/3`**
   (`tan y = 0.577350 = 1/sqrt(3)`, an exact 30 deg). **The cull is 4/3 WIDER horizontally than its
   own geometry implies, not narrower — so "two notions of view width pinching the edges" is NOT
   SUPPORTED. The 4/3 is real and unexplained.**
   **►► A NINTH CLEAN `dlgrab`, FROM A HABITUAL F9:** `dlgrab_10350.txt`, announced by
   `run_288_8b`'s own log (§6's provenance rule), carries **TWO scissors only** —
   `(0,0)-(1280,960)` x3 and `(0,120)-(1280,840)` x42, both FULL WIDTH, **zero sub-view rects** —
   and is **the first taken with `GETV_PROPCULLBOX=0`.**

   **THE ORIGINAL `288` ENTRY, KEPT BECAUSE RULE `2` DELETES NOTHING:**
   **►►►► SO `288` STOPPED ELIMINATING AND BUILT THE INSTRUMENT: `GETV_CULLWHY=1`. WRITTEN, NOT
   BUILT, NOT RUN. ◄◄◄◄** `posIsOnScreen` can say no in **six different ways** and two of them now
   have knobs that were not the mechanism. `GETV_CULLWHY` counts **all six** and prints them at exit
   beside `getv_roomscissor_report`: `room` · `fog` · `occl` · `box` · `view` **split per plane
   (near/left/right/top/bottom)** · `dist` · `drawn`, plus the cull frustum's **half-angles in
   degrees** to read against the VIEWPORT line. The per-plane split comes from a **READ-ONLY TWIN**
   of `camIsPosInScreen` in `bondview.c` that **decides nothing** — and **the twin carries its own
   drift gate, `twin-disagree`, which MUST BE ZERO or every per-plane number is VOID** (`271` §7,
   rule `17`). **`dist` coming back LARGE would contradict `[REPORTED]` fact 1, and in that case the
   INSTRUMENT is wrong, not the report** (`HANDOVER` §5). **No prediction is written for which one
   wins — that is the measurement.** `RUN-SHEET-288` §8e, with its own accounting-balance validation
   arm (`box` must drop to 0 with `PROPCULLBOX=0` and those rejects must REAPPEAR per-plane, not
   vanish). **Three changes now ride in `288`'s ONE binary.**

   **►►►► ARM 5 IS COMPLETE. BOTH GATES PASS, AND IT HANDED US A BIGGER SYMPTOM. `[MEASURED]`
   2026-08-31 20:28, `run_288_5_sixsites_streets.log` + eight dumps. ◄◄◄◄**
   **GATE 2, THE ONE THAT WAS OWED: EIGHT `dlgrab` DUMPS, ZERO SUB-VIEW RECTS.** Every dump carries
   exactly two scissors — `(0,0)-(1280,960)` and the letterbox band `(0,120)-(1280,840)`, **both full
   width**. `287`'s `dlgrab_8040` carried **seven** distinct rects including the falsifier
   `(832,120)-(1276,840)` with 613 triangles under it. **THE SUB-VIEW RECT IS GONE FROM EVERY DRAW.**
   **GATE 1 CONFIRMED A SECOND TIME, on a level that draws everything:** `expl=2801 smoke=8680` with
   every other site non-zero. Gates clean, and **`GETV_SLOTFREE resolved to 1 (env=1)` — the knob the
   run sheet's own block omits, added to this one, and the intro-cast crash did not happen.**
   **►►►► AND THE ARM PRODUCED A NEW `[REPORTED]` SYMPTOM THAT OUTRANKS WHAT IT WAS RUN FOR:
   PROPS VANISH IN THE CORNERS. ARM 7 IS NOW THE RANKED ARM. ◄◄◄◄**
   `[REPORTED]` unprompted, mid-arm: *"a car in the left hand corner... it is making objects in that
   distance on those corners disappear when it's in that side of the view while you are looking off in
   a different direction."* **THIS IS THE SYMPTOM `bg.c:545` PREDICTED IN WRITING BEFORE IT WAS SEEN**
   — *"a rectangle that is too tight there does not clip an object, it REMOVES it"* — and the knob for
   it, `GETV_PROPCULLBOX=0`, was written by `287` and **HAS NEVER BEEN RUN.**
   **`[MEASURED]` FROM SOURCE, MECHANISM NAMED, CAUSE NOT NAMED, NO FIX PROPOSED:** `propobj.c:14018`
   is the only consumer of the rectangle that decides whether a prop is drawn AT ALL, and
   `bondview.c:1139` builds its four planes from **the ROOM's projected rectangle, not the view
   frustum** — so a prop whose POSITION leaves that volume is removed WHOLE. **One obvious candidate is
   already dead on a source read: the prop is NOT tested as a bare point** — `chr.c:2750` and
   `propobj.c:5980` pass `getinstsize(model)` as a margin sphere. **Whether that sphere matches a car's
   extent is NOT established.** **AND A SECOND, SEPARATE CULL FIVE LINES BELOW MATCHES THE WORD
   "distance" IN THE REPORT:** `propobj.c:14035`'s hard `32000*32000` radius — a LITERAL and a console
   budget. **NOT the same mechanism; must not be merged** (`263` §1). **The session lead's proposal to
   widen past headset FOV is the right DIRECTION and the wrong KNOB for this run: it was 4:3
   pillarboxed, so no extra FOV is being rendered — the rectangle is narrower than the view ALREADY
   DRAWN.** Widening is `P2`/`P3` at stereo (derive from the RENDERED frustum, in stereo the UNION of
   both eyes, never a stored constant) — **a design note, not this arm. RUN THE FALSIFIER FIRST:
   `RUN-SHEET-288` §8b.**

   **►►►► ARM 5's FIRST GATE IS ALREADY ANSWERED — BY A LOG NOBODY READ FOR IT. `[MEASURED]`. ◄◄◄◄**
   `287` recorded `expl=0 smoke=0` in five arms and concluded, correctly, that this says nothing until a
   level that DRAWS explosions and smoke is run. **`run_287_M3_menu_offset0.log` is that run, and it was
   sitting in the build directory the whole time:**
   `sites: bg_pri=121858 bg_sec=121858 chr=38927 **expl=4514 smoke=16374** prop=333191`
   — on the same `02:24` binary, gates clean (`vsync=1`, cap 120, `simhz 0.500000`, `ours: x=0`, zero
   `simulation held to`, terminating `game_exit requested`). **ALL SIX SITES TOOK. The switch landed.**
   The zeros in 4A/4B/4D/4E were levels that drew no explosions and no smoke — the banner's own warning,
   firing correctly. **ARM 5 NOW OWES GATE 2 ONLY: the `dlgrab` dump must no longer carry the
   `(832,120)-(1276,840)` sub-view rect with 613 triangles under it.** No `287` log contains a single
   `dlgrab` line — **F9 was never pressed in that session** — so the dump arm is untouched and still owed.

   **THE HISTORY, STILL TRUE AND STILL THE REASON ALL OF THIS EXISTS:**
   1. **►►►► SMOOTHNESS. WORN, CONSTANT SINCE BRING-UP, AND IT WAS OUR RUN SHEETS. `285`. ◄◄◄◄**
   `[REPORTED]` *"when you turn real fast it feels like it's waiting... it's always been that way."*
   **`[MEASURED]` CAUSE: EVERY ARM THIS PROJECT EVER RAN SET `GETV_VSYNC=0`.** It came from `273`,
   which needed it for an uncapped GPU sample, and was copied into every run sheet since —
   including four written on 2026-08-31. `gfx_sdl2.c:413-421` says in its own comment that off
   *"is wrong for most people... the escape hatch for benchmarking."* **The session lead has been
   playing the benchmarking configuration for the entire project.**
   **THE FIX IS A SETTING, NOT A CHANGE: `GETV_VSYNC=1` + `GETV_FPS=<panel Hz>` + `GETV_SIMHZ=query`.**
   `[REPORTED]` on a 120 Hz panel: **"super smooth."** Banner `pace: 120 fps cap on, vsync=1` and
   `simhz ... 0.500000 fields per frame`. **`run_285_S1_vsync_on.log`, 2026-08-31.**
   **STILL OPEN UNDERNEATH IT, ALL `[INFERRED]`, NONE MEASURED — `285` §1:** the pacer books the
   sleep it ASKED for, not `ge_pace_wait_ms` which it measures two lines above (`gfx_sdl2.c:598`) ·
   the world advances one field per FRAME, so uneven intervals are uneven motion whatever the mean ·
   **the TURN may have no timestep, like `277` §4's walk — never checked, and the report is about
   turning.** **THE INSTRUMENT NOBODY HAS BUILT IS THE DISTRIBUTION OF PRESENTED-FRAME INTERVALS.
   A mean of 16.67 ms is identical for an even run and one alternating 8 and 25.**
   **AND NO RUN LOG IN THIS PROJECT RECORDS THE PANEL'S REFRESH RATE. It is 120 Hz.**
   **►►►► `287`: THE INSTRUMENT IS WRITTEN. `GETV_PACEHIST=<n>` — NOT BUILT, NOT RUN. ◄◄◄◄**
   The DISTRIBUTION of presented-frame intervals, stamped the instant `SDL_GL_SwapWindow()`
   returns (`gfx_sdl2.c`, swap_buffers_BEGIN — the pacer's sleep is in swap_buffers_END, and a
   stamp after it would be the same bracket error as `267` §1 / `271` §4 / `272` §3). Bins against
   the panel period, so `1x` reads *shown once*. **It also scores `285` §1.1 WITHOUT touching the
   pacer** — requested sleep beside `271`'s measured one; **near zero RETRACTS §1.1.**
   **AND IT WAS WORSE THAN `285` §2 SAID: NO CODE IN THIS PORT HAS EVER ASKED THE DISPLAY.**
   `[MEASURED]` a grep of `getv\port` for `GetCurrentDisplayMode`/`GetDesktopDisplayMode`/
   `refresh_rate` returns **ZERO hits**, so "120 Hz" is `[REPORTED]` and every candidate above is
   defined against it. `GETV_PACEHIST` now prints SDL's own answer. **IF SDL SAYS 60, `GETV_FPS=120`
   WITH `vsync=1` IS ASKING FOR DOUBLE THE PANEL AND S1's "SUPER SMOOTH" NEEDS RE-READING.**
   **►► AND `285` §1.4 IS A RETRACTION CANDIDATE ON A SOURCE READ — `287` §2.** The TURN **is**
   delta-scaled, unlike the walk: `bondview2.c:7366` (`vv_theta + speedtheta * g_GlobalTimerDelta
   * 3.5f`) and **every** term of all four branches of `bondviewCurrentPlayerUpdateSpeedTheta`
   (`:4573-4630`). **And mouse and pad are the SAME PATH** — `port_input.c` accumulates
   `ge_mouse_pend_x` into the stick — so `285` §2's mouse-vs-pad question needs no arm.
   **SOURCE READ ONLY. Its falsifier is free and unrun: a 360° spin timed at `FPS=60` vs `120`.**
   **RUN SHEET: `RUN-SHEET-287.md` PART ONE, arms 4A/4B/4C/4D. 4A IS THE FIRST RUN OF THE SESSION.**
1. **►►►► THE FRONT-END TEXT IS LAID OUT IN A DIFFERENT COORDINATE SPACE FROM THE FOLDER ART, AND THE
   VARIABLE IS `ge_offset_x()`. NEW, `[MEASURED]` 2026-08-31, `287`. ◄◄◄◄**
   **`[REPORTED]` by the session lead mid-session, unprompted: *"the text is not aligned properly on the
   menus."* `00-STATE` §3 listed "Menu text, folder screen" under WORKS (`236`/`237`/`244`). THAT ENTRY
   IS NOW WRONG FOR THIS CONFIGURATION.**
   **`[MEASURED]` off the screenshots, all four briefing pages and the difficulty screen identical:
   the folder ART — paper, crest, photo, tabs, the `OHMSS` title — is centred and correctly proportioned
   inside the pillarboxed 4:3 viewport. THE BODY TEXT IS NOT.** Viewport spans image px 920-2870; the
   paper spans 1110-2666 (9.7%-89.5% of the viewport); **the text runs from 10.8% out to ~100%,
   overflowing the paper on BOTH sides and hard-sliced on the left** — `Agent` loses its A, `MI6` reads
   `VII6`, `chemical` loses its c. **Two notions of view width inside ONE frame — the exact class §3's
   widescreen item says is in stereo's path.**
   **►► THE 2x2, AND ONE VARIABLE EXPLAINS ALL FOUR CELLS:**

   | | `1280x960` | `1825x1369` | `2560x1369` |
   |---|---|---|---|
   | **`WIDESCREEN=0`** | M1 **clean**, `offset_x=0` | **M3 clean, `ours: x=0`** | **4A/4B/4D FAULT, `x=367.333`** |
   | **`WIDESCREEN=1`** | not run | not run | M2 **clean**, `offset_x=0` by construction |

   **THE FAULT APPEARS IF AND ONLY IF `ge_offset_x()` (`gfx_pc.c:441`) IS NON-ZERO.** Both "clean"
   results are clean because they are the two ways of making the pillarbox margin vanish — not because
   widescreen or window size matter in themselves.
   **►► M3 IS THE SINGLE-VARIABLE ARM AND ITS PREDICTION WAS WRITTEN FIRST.** `1825x1369` vs `2560x1369`,
   both `WIDESCREEN=0`: `sx = 1825/320 = 5.703`, `sy = 1369/240 = 5.704` — **identical content scale,
   identical height, identical canvases, only the offset differs.** Predicted `ours: x=0` and aligned
   text; `[MEASURED]` `x=0` (and `x=-6.10352e-05` for the 440x330 canvas) and `[REPORTED]` *"text was
   aligned."*
   **►► AND IT KILLS THE SECOND CANDIDATE IN THE SAME ARM.** The 320x240 <-> 440x330 hi-res canvas switch
   (`gfx_pc.c:423`'s comment; both are exactly 4:3 so both yield the same offset but content scales of
   5.704 vs 4.148, a 1.375x displacement) **is present in the CLEAN run too, behaving identically.**
   Not the variable.
   **NO CAUSE IS NAMED AND NO FIX MAY BE INFERRED. `ge_offset_x()` is the VARIABLE, not the mechanism** —
   which draw path applies the offset and which does not is unread. **`P3`: this is a second, window-
   derived notion of view width, and `258` STAGE 6's per-eye frustum is the harder case of it.**
   **►► IT IS ALSO A COST OF THE `GETV_WIDESCREEN=0` DEFAULT THAT §3's WIDESCREEN ITEM DID NOT NAME.**
   That decision's cost table reads *"pillarbox bars on a desktop window"* and nothing else. **It is
   incomplete: at any non-4:3 window the front-end text is broken.** The decision is not reopened —
   the cost table is.
   **AND IT COST A WRONG ARM FIRST: M1/M2 MOVED BOTH KNOBS AT ONCE AND WERE A DIAGONAL, NOT A SQUARE.**
   Neither reproduced the reported cell, and two clean results were nearly read as "it went away."
   `275` §1's shape, sixth instance. **A 2x2 needs the cell the report came from in it.**
1. **Ourumov's SHIRT black + one Trevelyan's FACE black.** **THE COMBINER IS
   EXONERATED — `265`.** `GETV_CCPROBE` ran: ONE combiner across all 768 draws, the
   fault has the LEAST black inputs in the log (`texel=8b0000` red, `prim` white,
   `shade` grey), and **`CheadbrosnanboilerZ` draws a BLACK texel with a BLACK prim and
   renders CORRECTLY.** `263` §4 met its own falsification condition. **No cause is
   named. Next: key the same pointer bridge on the MODEL, not on `1x1` — `265` §6.**
2. **►►►► THE WIDESCREEN HOLES: THE PER-ROOM RECTANGLE IS THE CAUSE, AND `GETV_ROOMSCISSOR=0`
   REMOVES MOST OF THEM. `280`, `282`, `283`, `284`, `286`. ◄◄◄◄**
   **`[REPORTED]` arm A (`GETV_ROOMSCISSOR=0`, every room gets the full view): holes GONE.
   arm B (`GETV_PORTALOPEN=1`, `281`'s straddle patch): holes BACK. `284`.**
   **`[MEASURED]` TWO SURVIVE THE SWITCH, AND `286` NAMES WHY: the switch only changed the two ROOM
   draw calls (`bg.c:1051`, `:1132`). FOUR OTHER SITES FETCH THE SAME RECTANGLE AND CLIP TO IT
   THEMSELVES — `chr.c:186`, `chr.c:3437`, `explosion.c:874`, `propobj.c:7570`, all via
   `getPropCombinedRoomsBBox2D` -> `bgGet2dBboxByRoomId` -> the same `dword_CODE_bss_8007FFA0[].bbox`.**
   **`[MEASURED]` `dlgrab_8040`, taken WITH the switch on, still carries `(832,120)-(1276,840)` with
   613 triangles under it. THE SWITCH IS INCOMPLETE BY CONSTRUCTION.** `286` §1.
   **►►►► `287` §1: THE SWITCH IS SIX SITES, NOT FOUR, AND `286`'s LIST IS WRONG BOTH WAYS.
   WRITTEN, NOT BUILT, NOT RUN. ◄◄◄◄**
   **`explosion.c:1486` (SMOKE) is a fifth scissor site `286` MISSED** — same shape as `:874`.
   **`chr.c:186` IS NOT A SITE**: it is `ge_chr_dbg_vis_breakdown`, a read-only debug counter gated
   on `ge_chr_dbg_on()` that sets no scissor. **`propobj.c:14007` (`posIsOnScreen`) is a DIFFERENT
   CLASS — it CULLS, it does not clip**: a too-tight rect there REMOVES a prop, so it is a
   candidate mechanism for the **BLACK-WALL** symptom that still has no dump (`279` §6,
   `280` §7.3). It gets its own knob, **`GETV_PROPCULLBOX=0`**. **AND `chraction.c:10770`
   (`chrIsPosOffScreen`) reads `bgGet2dBboxByRoomId` DIRECTLY and is AI/SPAWN LOGIC — which is why
   THE KNOB MUST NOT LIVE IN `bgGet2dBboxByRoomId`.** A chokepoint there silently changes what
   characters DO. Six call-site edits, not one.
   **THE NEW FALSIFIER IS A COUNTER, NOT A DUMP:** `[getv][roomscissor] sites: bg_pri= bg_sec= chr=
   expl= smoke= prop=` at exit. **A ZERO on chr/expl/smoke/prop in a level that draws them means
   THAT SITE NEVER TOOK — the state `286` was in and could not see.** `RUN-SHEET-287.md` ARM 5.
   **THE WEAR PASS HAS STILL NEVER BEEN RUN** — Facility (glass), Dam, Cradle, front-end;
   `RUN-SHEET-287.md` ARM 6.
   **`281` IS CLOSED: both its patches are dead, killed by arm B, not by argument.** `284` §2.
   The historical trail, still true and still worth reading:
2. **►►►► THE WIDESCREEN HOLE'S EDGE IS A PORTAL SCISSOR'S `lrx`. NAMED TWICE. `279`. ◄◄◄◄**
   **`[MEASURED]` The artifact's hard vertical edge is the RIGHT edge of a per-room portal
   `SETSCISSOR` rect, in the game's own canvas space, to `0.00` native px — in TWO frames, TWO runs,
   TWO window resolutions, two different places in the level:**
   **`dlgrab_2290` (2560x1369, `GETV_WIDESCREEN=0`): edge at canvas x `151.92`, rect `(4,120)-(152,696)`;
   its top edge lands on that rect's `uly` too.**
   **`dlgrab_2913` (3840x2160, `GETV_WIDESCREEN=0`): edge at canvas x `476.00`, rect `(400,120)-(476,544)`.**
   **The hole lies OUTSIDE the rect in both. Both matches are on `lrx`, neither on `ulx`.**
   The rects are `bg.c:622-677` — each room's 2D bbox outersected against `screensize`, **game space,
   no window term in it.** In `2913` NINE interior edges were tested against the frame's own rects and
   **ONE matched, within 0.00 px; the other eight were 8-178 px away.** The test discriminates.
   **►► THE BUILD GATE IS OPEN — the rect is named. NO FIX IS PROPOSED AND NONE MAY BE INFERRED:**
   `278` §3 proved the room ADMISSION is byte-identical 4:3 vs 16:9, so "admitted correctly but
   clipped too narrow" is a contradiction that must be reconciled before a line changes.
   **THE MAPPING IS NOT AN ASSUMPTION**: `ge_scale`/`ge_offset_x` predicted the side bars, the game's
   own 120-row letterbox and the `(4,...)` play inset at BOTH resolutions before anything was
   concluded from them — 8 predictions, 8 met (`279` §3).
   **`GETV_WIDESCREEN` IS STILL A PORT KNOB, ON BY DEFAULT** (`port_support.c:203`);
   `ge_effective_native_width()` (`gfx_pc.c:423`) is still the LARGEST contributor and `278` §2's
   `1795.2` vs `1280` number stands. **This item is the SECOND contributor, and it survives the knob
   being off.**
   **`[REPORTED]` AT 4K IT IS REDUCED BUT NOT GONE** — *"only doing it on some of the edges and
   definitely not as much"* — while `[MEASURED]` `2913` still carries a `0.00`-px match.
   **AMOUNT IS RESOLUTION-SENSITIVE AND UNEXPLAINED. `279` §5. That is the next measurement.**
   **TWO SYMPTOMS, STILL TWO, AND NOW MEASURED APART** (`279` §6): every slab in all five admissible
   frames is the SEE-THROUGH class (flat sky/stale fill). **NOT ONE FRAME SHOWS THE BLACK-WALL
   symptom — it has NO DUMP AT ALL and needs its own F9, standing still.** `263` §1: do not merge.
   **►► STILL `P3` AND STILL IN STEREO'S PATH** — two notions of view width, one of which does not
   know about the window; `258` STAGE 6's off-centre per-eye frustum is a harder case of the same
   requirement.
   **►►►► THE DEFAULT IS DECIDED: `GETV_WIDESCREEN` GOES TO **OFF**. 2026-08-30p. ◄◄◄◄**
   **The session lead delegated the call** — *"I want whatever setting is going to allow us to render
   the best in VR. Other than that, I don't care how it's set."* **The honest answer is that NEITHER
   setting renders VR better: stereo does not go through this path at all** (`258` STAGE 6 computes a
   real per-eye off-centre frustum; this knob only stretches a 1280-wide canvas across a desktop
   window). **OFF is chosen for the path, not the picture:**
   - `ge_effective_native_width()` is a SECOND, window-derived notion of view width. Stereo brings the
     REAL one. **Two notions in one renderer is the bug class this whole item is made of** — the `k`
     stretch (`gfx_pc.c:4133`) applies to full-width scissors ONLY, so half the pipeline believes one
     width and half believes the other. **Default-on guarantees the fake one is still in the way when
     STAGE 6 lands. Default-off leaves it dormant, and `P3` DELETES it rather than reconciling it.**
   - **A knob that is ON by default and silently changes what the renderer fills cost `278` a whole
     session** (four wrong turns inside the game while the knob sat in the renderer), exactly as
     `268`'s silent `auto` cost `268`. Rule `17`'s family. **Default-off means the port behaves like
     retail until someone deliberately asks otherwise.**
   - **THE COST, NAMED:** pillarbox bars on a desktop window until `P3` is built. Accepted.
   **NOT YET DONE — THIS IS A DOC DECISION, NOT A CODE CHANGE.** The one-line flip is
   `port_support.c:203` (`unsigned int configWidescreen = 1;` -> `0`) plus its comment, and it has
   **NOT been made, built or run.** It is a candidate to fold into the first build of the `bg.c`
   work, so the two changes are worn together rather than in two separate arms.
   **`GETV_WIDESCREEN=0` REMAINS A DIAGNOSIS, NOT A FIX** — `279` proved the fault survives it.
2. **►► THE GPU IS MEASURED — BUT ONLY WITH THE CAP OFF. `273`. ◄◄**
   `[MEASURED]` **CRADLE 0.832 ms GPU draw, FACILITY 0.334 ms**, 1280x960, uncapped, `GETV_SIMDIV=1`.
   **The pre-stereo frame on the hardest level in the game is CPU 0.890 ms + GPU 0.832 ms against
   11.111 ms.** `273` §5.
   **`272` §7's repair WAS BUILT and its diagnosis was WRONG — `273` §4.** Moving `glEndQuery` ahead of
   the swap and the sleep changed the figure by nothing; the GPU **waits inside the query window**
   while the pacer sleeps, and the capped figure stayed 11.11 even at **320x240, one sixteenth of the
   pixels** (`273` §5.4). **The instrument now prints `CONTAMINATED` and withholds its verdict on any
   capped run** (`273` §2).
   **WHAT IS STILL OPEN:** no capped GPU figure exists, so "0.832 ms holds when the pacer sleeps" is
   an **assumption**, and every claim that stereo's doubled GPU work fits rests on it. `273` §6.
   **HOW TO MEASURE IT FROM NOW ON: `GETV_GPUTIME=1` WITH `GETV_FPS=0`.** `273` §8.
3. **STEREO — measured, scoped, NOT STARTED.** `258` is the route.
4. **►►►► `RB-04` IS TWO FAULTS. THE DELTA HALF IS FIXED; BOND'S WALK IS NOT. `277`. ◄◄◄◄**
   **`GETV_SIMHZ` IS BUILT, RUN AND WORN — `277`.** `[MEASURED]` at 90 Hz with the term on:
   `fps 90`, `speedgraph 60/s`, `g_GlobalTimer 60/s`, `simhz on delta 0.6667`, `props
   interpolated 0`, zero `simulation held to`. **The 44 delta-scaled sites — truck, tank,
   turret, thrown objects, casings, front-end cast — now run at retail speed at 90 Hz.**
   **►► WHAT IS STILL OPEN, AND IT IS NEW: BOND'S WALK IS NOT DELTA-SCALED AND IS UNTOUCHED.**
   `[MEASURED]` `277` §4, the Dam route: **60 Hz `20.94 s` vs 90 Hz `14.32 s` = `1.463`**, and
   the term changes it by nothing (`14.32` vs `14.24`). `145` §2's mechanism TRANSFERS to the
   native port: `bondview2.c:7237`/`:7411` advance an exponential approach once per FRAME with
   **no timestep** — shape 3 changes the DELTA, not the TICK COUNT.
   **►► SO AT 90 Hz THE WORLD IS NOW CORRECT AND BOND IS 1.46x FAST — AN INTERNAL MISMATCH THAT
   DID NOT EXIST WITH THE TERM OFF** (where both were ~1.5x and therefore consistent).
   **`[REPORTED]` the owner did NOT perceive it** — *"everything was fine"* — and reported 60 Hz
   as *"everything seemed in sync"*. **A measured, unperceived mismatch. `277` §5.**
   **THE FIX FOR THE SECOND HALF IS A GAME-DESIGN DECISION, NOT A BUGFIX** — a timestep inside
   `MoveBond`, 1,307 lines, **changes movement feel**; `118` §4 and rule 3's "ask first".
   **DO NOT START IT WITHOUT THE OWNER'S CALL.** `126`'s parked item, `277` §5.1.
   **THE MEASUREMENT THAT SCOPES IT IS STILL UNWRITTEN: `MoveBond` executions per second**
   (`145` §3, `277` §5.2). **Above 60 Hz still pin `GETV_SIMDIV=1`** and gate on `props
   interpolated 0` + zero `simulation held to` (`273` §7.1).
   **THE TWO HOIST SITES HAVE STILL NEVER BEEN DRIVEN** — tank turret (`bondview2.c:7330`) on
   Runway/Streets, grenade or rocket sliding to rest (`propobj.c:5065`). `277` §9.
   **►► `278` TRIED AND FAILED: four arms on Runway and Streets, THE TANK WAS NEVER ENTERED.**
   The entry chain is four gates and is written down in `278` §5; there is **no level whitelist**
   and detection is armed by being **BLOCKED by the tank**, not by standing on it
   (`bondview2.c:2540-2571`). **No free instrument prints any of it** — `GETV_VEHALL` covers
   VEHICHLE/AIRCRAFT only. `GETV_TANKWHY` is proposed, not built.
   **AND `278` §6 IS AN `[INFERRED]` RETRACTION CANDIDATE FOR HOIST 1 ITSELF**: `g_TankTurretTurn`
   is rebuilt each frame as `g_GlobalTimerDelta * turnspeed`, so retail's divide CANCELLED and the
   hoist may make the term 2/3, not fix it. **Source read only. Do not act on it unmeasured.**
   **STAGE 5 (the pose spine) still precedes STAGE 6 (stereo).**
5. **~~BLACK TRIANGLES AT 90 Hz~~ — SOLVED. `268`. NOT THE RENDERER.**
   `[MEASURED]` **`GETV_SIMDIV=auto` engages ITSELF at 90 Hz** (divider 3, sim held to 30 Hz,
   props drawn **interpolated**) and is a no-op at 60. No `[simdiv]` banner exists in ANY 60 Hz
   log; `props interpolated 0` at 60, `85000` at 90. **`GETV_SIMDIV=1` at 90 removes the
   artifacts** — owner: *"Yeah. That fixed it."*
   **The "triangles" were never triangles**: rooms clipped away by a portal scissor computed
   against state that only advances on ticks, so the sky shows through in hard-edged rectangles.
   Same cause as the ghost truck you can walk through, the see-through textures and the walls
   jumping. **This is OUT of stereo's path** — `258` is unaffected.
   **OWED: the DEFAULT. `auto` engaging silently above 60 Hz is what cost this. `268` §7.**
6. **`[REPORTED]` SAVES LOST.** Owner: *"the saves I had are gone from the other
   build."* Which build and which save path is **not established**. `260`: the live
   EEPROM is in `%APPDATA%`, NOT beside the binary. `local-only/save-backup.ps1`
   now snapshots it — **see `MAIN-STATION-TASKS.md`.**
7. Attract loop never reaches gameplay demos — `select_ramrom_to_play` and three
   siblings are `[getv] STUB:`. `263` §6.
6. Green line in the folder art (port-introduced, owner: "not in default game").
7. Folder 3 lost a save — `GETV_UNLOCKALL` writes 4 folders through a 5-slot
   rotation. Assistant-introduced fixture bug.
8. **`[REPORTED]` LATE GUN SOUND — STILL UNREPRODUCED. `269` §7.** A three-boot A/B on
   2026-08-30 could **not** reproduce it: a normal boot mashed through to Dam ran
   `rms` 3300-3600 throughout. **THE QUEUE-DEPTH THEORY IS DEAD — `269` §5.1**, `q=` and
   `n=` are identical in a healthy run and a totally silent one and the early-out never
   fires. **`512 -> 256` is NOT indicated and no fix may be proposed on current evidence.**
   Needs a long normal session with `GETV_AUDIO_DEBUG=60`; the `nz`/`rms` series dates it.
9. **`[REPORTED]` 4-PLAYER SPLIT-SCREEN: black flickering textures that overlay.** All four
   quadrants render and `support_fail=0`; **`GETV_SIMDIV=1` was pinned so `268` is NOT the
   cause**, and **no instrument separates the 4p run from the clean 2p run** — `270` §3.
   `[INFERRED]` candidate: `getPlayerCount()`-sized glass buffers (`258` §1.5). **NOT on
   stereo's path — stereo is two VIEWS, not two PLAYERS. STAGE 9.** `270` §4.
9. **`[REPORTED]` CROSSHAIR AUTO-CENTRES; aiming with the mouse fights it** — owner:
   *"it keeps putting you back."* **Not diagnosed, and NOT established as port-introduced
   rather than retail.** This is `P8` and belongs to `258` **STAGE 7**, not to a bugfix
   queue. `GETV_MOUSE_SENS`/`GETV_MOUSE`/`GETV_GUN_AIM` exist, unread. `269` §8.
9. **►► `[REPORTED]` SKIPPING THE INTRO KILLS THE AUDIO; LETTING IT LOAD IS PERFECT. `277` §8.**
   **The first NORMAL-BOOT reproduction of `269`'s silence** — until now it existed only under
   the `GETV_MENU` harness. `[INFERRED]`, not measured: `fileValidateSaves()` has two call sites
   and the non-title one is **`front.c:1461`, the last line of the LEGAL-SCREEN init** — and
   `00-STATE` §6 records that skipping any intro video goes straight to the menu. Zeroed
   `saves[]` -> `file2.c:1413-1414` applies `music_vol=0`/`sfx_vol=0`.
   **TWO FREE FALSIFIERS FIRST, NO BUILD:** no `lg:7-fileValidateSaves` boot mark on a skipped
   boot, **and the crosshair + ammo counter must be missing in that same session.** If the sound
   is off and the crosshair is there, the mechanism is something else — STOP.
   **"Prevent skipping" is NOT the fix** (nothing is a race; it fails the spirit test).
   **And do not touch `fileValidateSaves()` blind** — §3's folder-3 save loss lives inside it.
10. `SETUP.md` §3.5 owes `229` §9's two CSV traps.

### OWNER ACTION OUTSTANDING
- **►►►►►►►►►► THE NEXT ACTION IS `RUN-SHEET-308` §2a -- THE PATCH-TIGHTENING QUESTION. OFFLINE, NO RUN, AND IT REUSES THE 16 GRABS ALREADY ON DISK. ◄◄◄◄◄◄◄◄◄◄** `S3b` is sign-correct and tracks 1/D but under-reads by ~10-13%, growing with disparity magnitude. **The candidate diagnosis is that the correlator averages the central quarter (`stereo_disparity.py:86`, `xs = [half//4 .. 3*half//4]`) while the prediction uses the CENTRE-RAY depth, so measured and predicted are two different depths' disparities.** Add `--patch FRAC` (default the current window), narrow `xs` toward the crosshair column, re-score the strong `S3b` grabs. **GATE: if the proportional error falls toward ±5 px as the patch tightens, the under-read is patch-averaging; if it does not move, it is projection scale or the log's own `D`, and §2b (one flat-wall run) is required.** **`301` §0 -- A DIAGNOSIS, NOT A PATCH, AND THE COUNT IS FIVE.**
- **►►►►►►►►►► ~~`RUN-SHEET-308` §1, THE CONFIDENCE GATE~~ -- WORN IN FULL 2026-09-04 AND `H1` + `H18` CLOSE TOGETHER. THE FALSIFIER PASSED ON ALL 16 GRABS: `GATE dx: ALL 16 IDENTICAL`, four `LOW CONFIDENCE` refusals and all four are `S3c`, twelve still scored, `5400` still `contrast 0.286` / `VERDICT PASS`. `--selftest` unchanged, `10 insertions / 4 deletions`, `CRLF=0`. `308` §6. **`V3` DID NOT MOVE AND THAT IS THE POINT OF §2a.** ◄◄◄◄◄◄◄◄◄◄**
- **►►►►►►►►►► THE NEXT ACTION IS `RUN-SHEET-308` §1 -- THE CONFIDENCE GATE. OFFLINE, AND ITS FALSIFIER IS THE 16 `307` GRABS ALREADY ON DISK. ◄◄◄◄◄◄◄◄◄◄** `stereo_disparity.py` refuses at an ABSOLUTE `mz-mb<0.5` that `S3c` clears; the edit adds a RELATIVE `contrast >= 0.20` floor (`307` §2: S3b real >= 0.286, S3c void <= 0.123). **GATE: after the edit all four `S3c` read CANNOT ANSWER and all twelve `S3b` still score with unchanged `dx` -- else the threshold is wrong and is NOT filed (`301` §0, count five).** Then §2 is the ±5 px precision thread (`2a` offline patch tightening, `2b` one flat-wall run only if `2a` is inconclusive).**
- **►►►►►►►►►► ~~`RUN-SHEET-307` §2~~ -- RAN 2026-09-04, ALL 16 GRABS SCORED OFFLINE. GATE 6.1 PASSES ON EVERY FRAME (census era closed); GATE S3 (±5 px) DOES NOT: `S3b` sign-correct and 1/D-tracking but only 1/12 within ±5 px (precision ceiling), `S3c` all WRONG-SIGN with `mad_best`≈`mad_zero` (void, not a dead eye -- census perfect). `V3` DOES NOT CLOSE. NEXT: the `H1`/`H18` CONFIDENCE GATE (`mad_best` < ~0.6×`mad_zero`, which separates the two arms cleanly) and a disparity read a multi-depth scene cannot fool -- per-region, or a single-depth flat target. THE FC3/FC4 SENTENCE (`E3`) WAS THE LAST THING OWED THAT COST A PERSON -- NOW `[REPORTED]` AND CLOSED (next bullet). ◄◄◄◄◄◄◄◄◄◄**
- **►► `[REPORTED]` 2026-09-04, THE OWNER: *FC3 AND FC4 LOOKED THE SAME* -- the far-clamp A/B shows no visible difference. `RUN-SHEET-303` §0.1 IS A `279` §7 NULL FOR THE SECOND TIME AND CLOSES; `E3` IS DONE.** No prior `[REPORTED]` line carried it -- the owner believed it was filed and the docs did not hold it, the MIRROR of `305` §2a's trap. **`GETV_FARCLAMP` stays at its default `1`** (`303` §0.1: turning it off restores a state nobody has shown to be better).**
- **►►►►►►►►►► ~~THE NEXT ACTION IS `RUN-SHEET-307` §1~~ -- RAN 2026-09-04. THE FALSIFIER FIRED: the peg alarm STAYED SILENT on all four searches, returning an interior spurious peak (`dx +351/+172 px`, wrong sign, moving with `--search`) instead of pegging on a -7,019 px prediction. **`H1` IS RE-OPENED** (`307` §1, §4). THE NEXT ACTION IS NOW `RUN-SHEET-307` §2 -- `S3b` AND `S3c`, WHICH NEED THE OWNER IN-GAME. THE ORIGINAL ENTRY, KEPT BECAUSE RULE `2` DELETES NOTHING:**
- **►►►►►►►►►► THE NEXT ACTION IS `RUN-SHEET-307` §1 — OFFLINE, SECONDS, AND IT IS A FALSIFIER,
  NOT A MEASUREMENT. ◄◄◄◄◄◄◄◄◄◄** `stereo_disparity.py` on `dlgrab_S3_5400.bmp` **MUST PEG and the
  `H1` alarm MUST FIRE**: the frame's predicted disparity is −7.696404 eye-widths and the
  correlator cannot express it. **`H1` was opened because that alarm had never fired, `301` §2 made
  it able to, and `306` §1 made its line printable. This is the first real frame where it is
  required to fire — silence retracts `H1`'s closure.** The block derives `--predicted-frac` from
  the log so nothing has to be substituted.

- **►►►►►►►► THEN `RUN-SHEET-307` §2 — `S3b` AND `S3c`, THE TWO ARMS THAT LAND IN BAND. ◄◄◄◄◄◄◄◄**
  `S3b` is separation **32** at the near wall (predicted ≈ **−450 px**); `S3c` is separation **500**
  down a long sightline (predicted ≈ **−170 to −500 px**). **§2.0 is the AMPLITUDE GATE and it is
  scored before any pixel is read: the grabbed frame's own `PREDICTION: disparity = … px` must
  satisfy `|px| ≤ 500`.** **AND THE STAGING INSTRUCTION HAS CHANGED — for `S3c`, do NOT walk up to
  a wall; stand still down the LONGEST line in the room and press F9 four or five times.**
  **If both arms pass ±5 px, the 1/D law is MEASURED IN PIXELS across a 16x separation change and a
  40x depth change, which no arm has ever done, and `258` STAGE 6's gate is met on two independent
  points.**

- **►► `RUN-SHEET-306` §7 / `RUN-SHEET-307` §5's COMMITS ARE STILL UNMADE.** Three tools, five
  glyph sites, `5 insertions / 5 deletions` — **and that edit is what made `306` §1 and §2 run at
  all**, so it is now worn as well as written.

- **►►►►►►►►►► THE NEXT ACTION IS `RUN-SHEET-306` §1, THEN §2, THEN §3. ALL THREE ARE OFFLINE AND
  THE THIRD READS EVIDENCE THAT IS ALREADY ON DISK. ◄◄◄◄◄◄◄◄◄◄** §1 re-wears `305`'s numbers under
  the main PC's `py` **and tests `306`'s ASCII fix at the same time** — it uses a PLAIN `py` on
  purpose; §1e's `-X utf8` form is for diagnosis only and running it first measures nothing. §2 is
  the corpus sweep, **split into a 256-dump REPRODUCTION and `grabs_304_P1`'s nine as NEW DATA**,
  because the corpus grew. §3 points `stereo_eyediff.py` at `grabs_304_P1` for the first time.

- **►►►►►► `RUN-SHEET-304` §2a IS HALF DONE, NOT OWED IN FULL — `P1` RAN AT 23:48:34Z AND HAS
  NEVER BEEN READ. ◄◄◄◄◄◄** Nine gameplay grabs, one log, clean provenance, no `EXCEPTION`.
  **`P2` (`GETV_STEREO_REBUILD_VIEWER=0`) is the half that is genuinely owed** and it is
  `RUN-SHEET-306` §4. **GATE §2a needs both columns and only a CONCENTRATED hit in a GAMEPLAY
  frame counts** — top-three share beside largest blob (`305` §1.5): the polygon reads 79–86% /
  95–100%, the dead eye 5–8% / 14–23%.

- **►►►►►►►► `S3`, THE SEPARATION GATE, IS THE ONE ARM THAT DECIDES WHETHER `258` STAGE 6 CAN
  CLOSE — AND IT HAS NEVER RUN. `RUN-SHEET-306` §6. ◄◄◄◄◄◄◄◄** It needs **no headset** (`255` §4):
  desktop side-by-side at `GETV_STEREO_OFFSET=500`, halves cross-correlated, the prediction in the
  log BEFORE the screenshot. **The objection that held it back was correct and has lapsed:** a
  disparity measured across an empty eye is a number about nothing, and `303` §2 filled eye 1
  (`MODEL_MTX=38`, `MODEL_VTX 16/16`, `only in eye0 = 0`, `viewer=0`, ZERO-REBUILD 0 of 3015).
  **GATE 6.1 is scored FIRST and a failure there STOPS the read** — `295` §10.1 scored a PASS on a
  black frame and that is the same mistake one level up.

- **►► AND THE FC3/FC4 SENTENCE IS STILL OWED — IT IS THE ONLY THING ON THIS BOARD THAT COSTS
  NOTHING BUT A PERSON.** `RUN-SHEET-305` §4, carried unchanged as `RUN-SHEET-306` §5. **If the two
  arms looked the same again, `RUN-SHEET-303` §0.1 is a `279` §7 null for the SECOND time and
  should be CLOSED rather than re-run a third.**

- **►►►►►►►►►► THE NEXT ACTION IS `RUN-SHEET-305` §1 -- RE-WEAR `305`'s NUMBERS UNDER THE MAIN
  PC's `py`. IT IS OFFLINE, IT NEEDS NO BUILD AND IT COSTS SECONDS. ◄◄◄◄◄◄◄◄◄◄** Every figure in
  `305` was measured on the BRIDGE's `python3 3.10.12`, which is not this machine's `py` -- the
  exact gap `H7` exists for. **NOTHING IN `305` IS QUOTABLE FORWARD UNTIL §1's four gates pass.**
  Then **§2**, which bounds `305` §1.4's falsifier across the whole corpus, and **§4**, which is
  one sentence from the owner and the only thing this sheet asks a person for.

- **►►►►►► THE POLYGON IS STILL THE WORK, AND THE DISPLAY LIST IS NOW EXHAUSTED AS A PLACE TO
  LOOK. ◄◄◄◄◄◄** `305` §4. Four levels are excluded by measurement: admission (`303` §5), the
  matrix conversion (`303` §4), the arena (`305` §1.2), and the ORDER (`305` §1.5, `C1_2336` and
  `V1_2732` order-identical). **Every one of those is something `GETV_DLGRAB` RECORDS, and it
  records `w0`/`w1` -- opcodes and ADDRESSES. Nothing in this project has ever read a per-eye
  buffer's CONTENTS.** That is the next instrument. **`301` §0: it is not designed here and the
  count of filed fixes that were wrong is five.**

- **►►►► DO NOT READ `only in eye0 = 0` AS AN ORDER RESULT. THE CENSUS COMPARES SETS. ◄◄◄◄**
  `dlgrab_eyecensus.py:96-97`. `dlgrab_C1_4676` reads a perfect census AND carries an eight-call
  cyclic rotation by three. **`getv/tools/dlgrab_dlorder.py` is the ordered read and it must be
  run beside the census on any frame whose picture and census disagree.** `H15`.

- **►►►► THE REORDER IS DATED AND IT DRAWS NOTHING -- DO NOT SPEND A RUN ON IT. ◄◄◄◄** `305`
  §1.3/§1.4. It is on the `299` binary with clean provenance (`run_299_E1_percensus.log`, one log,
  `279` §2 satisfied), so it predates `303` §2 -- **and `dlgrab_2928` and `dlgrab_2957` read
  `total 0 px  blobs 0` under `stereo_eyediff.py` while carrying it in full.** ZERO, not "under
  threshold". **BOUND: those two frames are a different binary and a different scene from
  `4676`'s. `RUN-SHEET-305` §2 is what closes that edge and it is offline.**

- **►►►►►► `RUN-SHEET-304` §3 AND §4 ARE **DONE**, NOT OWED -- AND §3's ANSWER IS WAITING ON ONE
  SENTENCE. ◄◄◄◄◄◄** `305` §2a. The `dlgrab_D3_*` strays are in `grabs_302_D3\`;
  `run_304_FC3_road_on.log` and `run_304_FC4_road_off.log` ran at 22:17:46Z / 22:18:34Z with both
  banners taking and distinct `ARM=` lines. **Their counters are read for the first time in `305`
  §2a: the knob took at FULL STRENGTH in ALL 467 windows (`clamped == straddle`) and the venue
  WAS the road (median 1,359 clamped/Mvtx against the cast roll's 45,000) -- so `303` §3.2's venue
  objection does NOT apply this time.** But the counters cannot decide it and `303` §3 says so.
  **`RUN-SHEET-305` §4: one sentence about each arm. If they looked the same again,
  `RUN-SHEET-303` §0.1 is a `279` §7 null for the SECOND time and should be CLOSED, not re-run.**

- **►► AND `304` §2a -- DATE THE **POLYGON** WITH A RUN -- IS THE ONLY PART OF `304` STILL OWED.**
  `305` §1.3 dated the REORDER, which is a different fault and does not answer it.

- **►►►►►►►►►► THE NEXT ACTION IS `RUN-SHEET-304` §2 -- THE POLYGON, `dlgrab_C1_4676` FIRST, AND
  IT IS ALL OFFLINE. THEN §2a IF IT IS TO BE DATED. ◄◄◄◄◄◄◄◄◄◄** `RUN-SHEET-303` is worn in full
  and `RUN-SHEET-304` §1 and §5/§5a are worn: commits `94cdf01c` / `c26c58d` / `d393860`, then
  `f3c9a04` / `71ac3b3`, then `8946e54` / `f70fe81`. **All four repos clean.** **DO NOT RE-RUN
  §1** -- the sweep is done and `eyediff_sweep_304.txt` is its record. **§2 IS A DIAGNOSIS AND NOT
  A PATCH** (`301` §0, and the count is five). **§2a needs the game; §2, §4 and §5a do not.**

- **►►►►►► THE POLYGON IS THE ONLY SYMPTOM ON THE BOARD WITH A PICTURE, A DETECTOR AND NO
  EXPLANATION -- AND BOTH OBVIOUS CAUSES ARE EXCLUDED BY MEASUREMENT. ◄◄◄◄◄◄** Not an admission
  loss (`39/39`, `only in eye0 = 0`, `303` §5); not `292`'s double conversion
  (`already-converted=0` of 366,456, `303` §4). **`dlgrab_C1_4676` is 38% concentrated where
  `C1_2336` and `V1_2732` are 79-86%, so the FIRST question is whether it is the same fault at
  amplitude or a second one.** `304` §1.4.

- **►►►► THE POLYGON'S AGE IS UNKNOWN AND THE ARCHIVE CANNOT SETTLE IT -- `RUN-SHEET-304` §2a IS
  THE RUN THAT WOULD. ◄◄◄◄** `304` §2, `H14`. **P2's opening frames will diverge whatever happens**
  because the fix is off there, so **the gate is CONCENTRATION, not a hit count, and the grabs must
  be taken in GAMEPLAY.**

- **►►►►►►►►►► ~~THE NEXT ACTION IS `RUN-SHEET-304` §1~~ -- DONE 2026-09-03, AND IT FOUND A FALSE
  NEGATIVE IN THE INSTRUMENT ITSELF (`304` §1.2). THE ORIGINAL ENTRY, KEPT BECAUSE RULE `2` DELETES
  NOTHING:**
- **►►►►►►►►►► THE NEXT ACTION IS `RUN-SHEET-304` §1 -- WEAR `stereo_eyediff.py` ON THE MAIN PC,
  THEN SWEEP EVERY GRAB THIS PROJECT HAS. ◄◄◄◄◄◄◄◄◄◄** `RUN-SHEET-303` IS **WORN IN FULL** and
  its three commits are **IN** (`94cdf01c` / `c26c58d` / `d393860`, all three trees clean) -- do
  not re-run any of it, §5 included. §1 is OFFLINE, needs no build and costs seconds, and it
  re-reads `298`-`303`'s pictures with an instrument they did not have. **`H7`: the ten gates and
  the selftest were re-worn on the BRIDGE's `gcc 11.4.0` / `python3`, which is not the main PC's
  `py`.**

- **►►►►►► THE ONE-EYE POLYGON IS THE ONLY SYMPTOM ON THE BOARD WITH A PICTURE, A DETECTOR AND NO
  EXPLANATION. START WITH `dlgrab_C1_4676`. ◄◄◄◄◄◄** `303` §5. It is **NOT** an admission fault --
  the census on those frames is `39/39` with `only in eye0 = 0` -- and it is **NOT** `292`'s double
  conversion, which `C1` measured dead. **Do not inherit either explanation; both are excluded by
  measurement.** `4676` diverges BROADLY (900 blobs, `mad` 6.409) where the other two carry one
  polygon, so it is the frame with the most in it.

- **►►►► `RUN-SHEET-303` §0.1 IS UNANSWERED, NOT PROVEN AND NOT DISPROVEN. ◄◄◄◄** The far-clamp
  A/B could not discriminate because the venue was wrong, and **the fix for that is a per-window
  gate, not another pair of arms at the same place** -- `RUN-SHEET-304` §3. **`GETV_FARCLAMP`
  stays at its default `1`**: it is the RDP's own behaviour, it costs nothing measured, and
  turning it off restores a state nobody has shown to be better.

- **►► THE FOUR `dlgrab_D3_*` FILES IN `grabs_303_V1\` ARE `302` §4's AND MUST BE MOVED TO
  `grabs_302_D3\`.** `303` §7. Nothing is contaminated -- every census ran on `dlgrab_V1_*` -- but
  a folder named for one arm now contains another's, which is exactly `279` §2's failure with the
  labels swapped. **`GETV_ARM` names a run's OWN grabs and says nothing about the strays already
  sitting in `build-windows`.**

- **►►►►►►►►►► THE NEXT ACTION IS `RUN-SHEET-303` §1 -- THE TEN GATES, THEN §2 THE **REGEN**, WHICH
  IS OWED THIS TIME. ◄◄◄◄◄◄◄◄◄◄** `303`, written OFFLINE 2026-09-03. **`RUN-SHEET-302` IS WORN IN
  FULL** -- do not re-run any of it. **`302` HAD NO REGEN STEP AND `303` DOES: `gfx_pc.c` IS
  GITIGNORED and its change exists only in `getv/patches/thirdparty/0001-getv-port-layer.patch`.
  Do not carry `302`'s habit across.** The regen has already been run offline and `verify` reads
  `15/15`, so `verify` alone is the gate; run `regen` again only if it says `DIFFERS`. **`302`'s
  binary was `DF5CAB2A...1438 18068657` -- a `303` binary that matches it is the `302` binary.**

- **►►►►►► `303` §3 (V1/V2) DECIDES WHETHER GROUP B CLOSES, AND ITS GATE IS A PICTURE, NOT A
  COUNTER. ◄◄◄◄◄◄** `dlgrab_eyecensus` on V1's grabs must read **eye1 `MODEL_MTX=38`** against V2's
  `0`. **A partial admission -- eye1 non-zero but under 38 -- IS NOT A PASS**, and eye1 reading 38
  with the picture still wrong means `299` §8.2's symptom was never only about admission.
  **AND THE BALANCE INVARIANT CHANGED TO `chr+obj+view+skipped == zsnap`** -- a sheet quoting
  `chr+obj+skipped` is quoting the old one.

- **►►►► `303` §4 (FC1/FC2) IS THE FAR-CLAMP A/B, AND ITS VENUE IS THE INTRODUCTION LOOP. ◄◄◄◄**
  **FC1's far `clamped=0` would be a FAILURE** -- the only zero here that is a receipt is the NEAR
  one, which is `301` §5's fix still working and **must not regress in either arm.** `beyond_far`
  must be large in both or the loop was not reached and *"I saw nothing wrong"* is `279` §7.

- **►► `H4` HAS NOW COST THREE OWNER CYCLES** -- `GETV_FILTERING` two, `GETV_FARCLAMP` one --
  **and `MEDIUM` is arguably the wrong rank.** `GETV_FARCLAMP` was SILENT AND LOAD-BEARING at the
  same time, which is why `302` §4's far field went a whole run with no explanation in the log.
  **Re-rank `knob_banner_survey.py`'s 323 remaining by "does this knob change what is DRAWN",
  not by how often the docs mention it.**

- **►►►►►►►►►► ~~THE NEXT ACTION IS `RUN-SHEET-302` §1~~ -- DONE 2026-09-03, WORN IN FULL. THE
  ORIGINAL ENTRY, KEPT BECAUSE RULE `2` DELETES NOTHING:**
- **►►►►►►►►►► THE NEXT ACTION IS `RUN-SHEET-302` §1 -- THE TEN GATES, THEN §2 THE BUILD.
  ◄◄◄◄◄◄◄◄◄◄** `302`, written OFFLINE 2026-09-03. **`RUN-SHEET-301` IS WORN IN FULL AND EVERY
  GATE IT SET PASSED** -- do not re-run any of it. `302` edits THREE TRACKED FILES
  (`ge_rebuild_window.h`, `chrprop.c`, `ge_rebuild_window_harness.c`), **so there is NO REGEN
  STEP and that is deliberate, not an omission**: no third-party file was touched and `verify`
  already reads `15/15`. **§1's gate is `ge_rebuild_window_harness: 30 checks, 0 failed` -- `301` §1's
  gate line was `18` and this edit adds twelve; if it still says 18 the tree is stale and you are
  about to build the old census.** Then §2c writes
  `EXPECTED-EXE-302.txt`; **a `302` binary whose hash equals `301`'s `7058E950...D5B6` is the
  `301` binary and the edit did not take -- that is a FAILURE, not a reassurance.**

- **►►►►►► `302` §3c IS THE ONE READ THAT DECIDES WHERE GROUP B GOES, AND `B2` IS NOT YET A TASK.
  ◄◄◄◄◄◄** `301` §7 measured `type=1` on all 541 skipped frames but **one counter stood for six
  prop types.** If the dead block reads **`viewer=`** the 372 frames are **BENIGN** -- item 4 says
  the viewmodel is already per-eye -- **`B2` is retired and the dead eye must be RE-OPENED
  elsewhere** (`301` §7b's third row, not its first). If it reads `explosion=`/`smoke=`, `B2` is
  real design work. If it reads **`player=`** or `nul=`, the branch excludes a type **neither item
  4 nor the `else` branch's own comment names**, and the prose is wrong about what the code does.
  **`301`'s own rule applies to the board `301` wrote: a hole's filed fix is a diagnosis, not a
  patch. Do not inherit a guess about which.** **AND READ `302` §3a FIRST** -- a bucket count from
  a run whose four population states do not match `301` S2 is a number about a different
  situation.

- **►►►► `299` §8.1 IS CLOSED. THE DEPTH-CLAMP FIX WORKS -- D1 GONE, D2 PRESENT, `[REPORTED]`.
  ◄◄◄◄** What was never read is its PRICE: `GL_DEPTH_CLAMP` disables z clipping at **BOTH** planes
  and `298` §4.4's `all_near` number, which was offered as that price, is **RETRACTED** (§4) and
  measures where you stood. **`302` §4 is that read, and its gate is that `[getv][far]`'s
  `beyond_far` must be NON-ZERO** -- `301` D1 read `319751 (0.7%)`. A zero there makes *"I saw
  nothing wrong"* a `279` §7 null result from an instrument pointed at nothing.

- **►► A NOTE THE RUN SHEETS DID NOT CARRY: AN A/B's SCENE COUNTERS MUST BE NORMALISED BEFORE
  THEY ARE COMPARED.** `301` §5.3's GATE 3 says *"if D1 and D2 disagree by more than a little the
  A/B is void"* and compares raw totals. **D1 ran ~14% longer than D2** (`vtx` 46.6M vs 40.8M),
  so the raw pair is not comparable as written. Normalised, `straddle` is **341 vs 340 per Mvtx**
  -- the same place -- while `all_near` 143 vs 50 is a **93-triangle** difference on a counter at
  0.0003% of the frame. **Both counters increment at `gfx_pc.c:3769`, BEFORE the clamp branch, so
  they are genuinely knob-independent.** Not a void. **Every future A/B compares per-Mvtx.**

- **►►►►►►►► ARM 3 IS GREEN AND THE NEXT ACTION IS `RUN-SHEET-297` §7 (R3) THEN §8 (R4 / S3).
  `298` §0. ◄◄◄◄◄◄◄◄** R1 and R2 are worn: `[MEASURED]` R2 `eyes-rebuilt=1`, `chr`+`obj` accounting
  for the whole list, per-eye texture **1.00 / 1.02** against R1's **8.6x / 6.0x**, no crash.
  **R4 was gated on R2 passing and is now unblocked — `297` §8 says its block will be spliced in
  full rather than delegated, and that splice is owed.** R5 (cost) is untouched.

- **►►►►►►►►►► THE NEXT ACTION IS `RUN-SHEET-300` §4 -- D1/D2. THE BUILD IS DONE AND THE FIX IS
  ENTIRELY UNTESTED. `299` §9.6. ◄◄◄◄◄◄◄◄◄◄** `[MEASURED]` 2026-09-03 02:40: regen ran, build
  succeeded, `ge_depthclamp.o` linked with `0x360` bytes of `.text` and its GL references
  resolving to `glIsEnabled`/`glGetError`, all six new strings in the exe. **NONE OF THAT IS A
  RUN** (`279` §7). D1's FIRST LOG LINE answers the first question by name -- `GL_DEPTH_CLAMP ON`
  or `UNAVAILABLE (<why>)` -- and the census answers the second without anyone's eyes: **D1 must
  read `clamped=0` on BOTH planes with `straddle` in the thousands, and D2 must reproduce `299`
  N1's `clamped = straddle + all_near` exactly or the A/B is void.** **AND LOOK AT THE FAR FIELD
  IN D1:** the extension disables z clipping at both planes and `298` §4.4's `all_near` number is
  retracted, so that cost is the owner's eyes and nothing else.

- **~~THE FIRST STEP IS THE REGEN, NOT THE BUILD~~ -- DONE 2026-09-03. THE ORIGINAL ENTRY, KEPT
  BECAUSE RULE `2` DELETES NOTHING:**
- **►►►►►►►►►► THE NEXT ACTION IS `RUN-SHEET-300`, AND ITS FIRST STEP IS THE **REGEN**, NOT THE
  BUILD. `299` §9.1. ◄◄◄◄◄◄◄◄◄◄** `299` edited FOUR files under `getv/port/`: `ge_depthclamp.c`
  and `.h` are ours and tracked, but **`gfx_pc.c` and `gfx_opengl.c` are gitignored and reach a
  commit ONLY through `getv/patches/thirdparty/0001-getv-port-layer.patch`.** A build before the
  regen builds code that is in no commit. **The first `verify` is SUPPOSED to say `DIFFERS` on
  those two; the gate is the SECOND one reading `15/15`.** Then the build, then D1/D2
  (`GETV_DEPTHCLAMP` 1 vs 0, same alley as N1-N3), then the filtering arm, then the skip split,
  then three commits. **`ge_depthclamp.c` IS A NEW FILE IN A GLOBBED DIRECTORY and that glob is
  the one build-system assumption `299` could not test offline** -- an `undefined reference to
  'ge_depth_clamp_init'` means `build_windows.ps1:341` did not see it.

- **►►►►►►►► THE `GL_DEPTH_CLAMP` FIX IS WRITTEN AND BUILT. NOT RUN, NOT COMMITTED. `299` §9.
  ◄◄◄◄◄◄◄◄** The A->B->A passed: bug 2 is the near-plane depth clamp, `[MEASURED]` cause.
  `gfx_pc.c:3733` names `GL_DEPTH_CLAMP` / `ARB_depth_clamp` / `EXT_depth_clamp` as *"precisely the
  hardware behaviour"* and it is implemented **nowhere** in `gfx_opengl.c`. Enable it in the
  backend, then remove or gate the per-vertex clamp. **`GETV_NEARCLAMP=0` IS STILL NOT THE FIX AND
  MUST NOT SHIP** -- but see §4: the `all_near` number that was offered as its price does not
  measure it, and the reason it must not ship is the GL semantics, not that counter.

- **►►►►►► THE SKIP SPLIT IS WRITTEN TOO, AND IT ANSWERS `299` §8.3 IN ONE RUN. `299` §9.3.
  ◄◄◄◄◄◄** ARM 3's dead-eye frames are the ones where the single listed prop is SKIPPED, and
  `chrprop.c` had **two** `ge_props_rb_skip++` sites the census could not tell apart -- one of them
  carrying the comment *"this cannot happen today."* The SUMMARY now prints `flag=` and `type=`
  separately. **`type=` is a design gap (item 4's exclusion is too wide); `flag=` FALSIFIES that
  comment. Which one fires is still `[UNDETERMINED]` and must not be asserted until
  `RUN-SHEET-300` §6 runs.**

- **►►►►►► `configFiltering`'s `over` GUARD IS WRITTEN. `299` §9.2. ◄◄◄◄◄◄** `GETV_FILTERING` now
  obeys the precedence `ge_config.c` documents. **The gate is a run whose banner reads
  `filtering=0`** -- it read `filtering=2` in both `298` arms with the same environment set, and
  the blur question it was asked for is **still open.** `RUN-SHEET-300` §5.

- **~~BEFORE ANY OF THAT, THE CHEAPEST RUN IN THE QUEUE: A -> B -> A ON `GETV_NEARCLAMP`~~ -- DONE
  2026-09-03, PASSED. `299` §8.1. THE ORIGINAL ENTRY, KEPT BECAUSE RULE `2` DELETES NOTHING:**
- **►►►►►►►► BEFORE ANY OF THAT, THE CHEAPEST RUN IN THE QUEUE: A -> B -> A ON `GETV_NEARCLAMP`.
  `298` §4.5. ◄◄◄◄◄◄◄◄** Arm F (`GETV_NEARCLAMP=0`) came back clean with `NEAR straddle=18439
  clamped=0` — the condition present, the knob provably off — but **took no `dlgrab` grabs**, so the
  negative rests on the owner's eyes alone. **Same alley, clamp back to default, confirm the
  artefact RETURNS, and F9 both states.** Until it does, `298` §4 is `[REPORTED]` plus a census, not
  `[MEASURED]` cause.

- **►►►►►► TWO ONE-LINE FIXES ARE IDENTIFIED AND NEITHER IS WRITTEN. BOTH ARE BUILDS AND NEITHER
  BELONGS INSIDE AN ARM. ◄◄◄◄◄◄**
  1. **`GL_DEPTH_CLAMP` in the GL backend** — `gfx_pc.c:3734` names it as the exact fix and
     `[MEASURED]` it is referenced in comments twice and implemented nowhere in `gfx_opengl.c`.
     The per-vertex clamp is then removed or gated.
  2. **`configFiltering`'s missing `over` guard** — `ge_config.c:421/424/428`, `298` §5.

- **►►►►►► `GETV_FILTERING` CANNOT BE SET FROM THE ENVIRONMENT. TWO OWNER CYCLES WERE SPENT
  MEASURING THE DEFAULT. `298` §5. ◄◄◄◄◄◄** `key_filtering()` writes `configFiltering` DIRECTLY with
  no `over` guard while `put("GETV_POINT_FILTER", ..., over)` on the next line obeys precedence, so
  the per-user cfg beats the environment for this one key. **`[MEASURED]`: both
  `run_298_tex_filter0.log` and `run_298_tex_point.log` banner `filtering=2` with
  `GETV_FILTERING=0` set.** **Until the source fix lands, the only way to run that arm is to edit
  `filtering = point` in `%APPDATA%\Goldeneye-Native\Goldeneye-Native\goldeneye.cfg`, and the
  GATE IS THE BANNER READING `filtering=0`.** The question it was asked for — whether the near-wall
  blur is magnification or a wrong texture size — **is still open.**

- **►►►►►► A RE-RUN OF AN ARM GETS A NEW LOG NAME, AND EVERY ARM FILES ITS OWN GRABS. `298` §6.
  ◄◄◄◄◄◄** A re-run overwrote `run_297_R2_rebuild_on.log`; the BMPs survive but their provenance
  cannot be re-derived, and §6 makes a log's own `dlgrab` announcements the only admissible
  provenance. **`dlgrab_NNNN` is named by FRAME NUMBER, so two arms from the same spot silently
  overwrite each other.** Grabs are now filed per arm in `grabs_298_<ARM>/`, with everything
  earlier in `grabs_pre_298cull/`.

- **►►►►►►►► R0 IS GREEN. THE NEXT ACTION IS `RUN-SHEET-297` §5 (R1) AND §6 (R2) — AND R2 IS THE
  FIRST TIME ARM 3 WILL EVER HAVE RENDERED A FRAME. `297` §11.5. ◄◄◄◄◄◄◄◄** `[MEASURED]`
  2026-09-02: a full R0 session — shooting characters, walking, returning — with **no crash**,
  39 MB of log against the 2.2 MB truncated ones the bug produced. **DO NOT SHOOT A MINE during
  R1/R2: that crash is real, PRE-EXISTING and not ARM 3's (§12 below).**

- **►►►► `297` §10 IS RETRACTED IN FULL. THE R0 CRASH WAS NEVER IN `objBuildRenderState`. ◄◄◄◄**
  The cause was **`chr.c:3305` — `if (headSwitchVisible)` WRITTEN TWICE**, the first without
  braces, so the `else` bound to the inner `if` and the FALSE path skipped the whole statement
  including the else. An off-screen chr therefore kept a stale `PROPFLAG_ONSCREEN` while
  `chrTick:3299` had already torn `chr->field_20` down to NULL; `chrTestHit` passed its ONSCREEN
  guard on that and `sub_GAME_7F06C010` walked NULL with no NULL check. **Fixed, built, worn.**
  Nondeterministic by construction — it needs a chr to go off-screen while still a hit candidate.

- **►►►►►►►► SHOOTING A MINE CRASHES, IT IS PRE-EXISTING, AND THE PROOF IS A SAVED BINARY.
  `297` §12. ◄◄◄◄◄◄◄◄** `vtxstore.c:161` filters `type == 1` (**`PROP_TYPE_OBJ`**) and then reads
  `PropRecord`'s tagged union as a **`ChrRecord *`**; an ObjectRecord read through
  `ChrRecord.model` (+0x20 native) lands on a float. **`build-windows/goldeneye_PARENT.exe`, built
  before ARM 3 existed, crashes at the same symbol+offset with the same fault address to the byte
  (`0xbdccc587`) at a different ASLR base.** **A NULL GUARD IS NOT THE FIX — the pointer is WILD.**
  **TWO candidate corrections and they are NOT equivalent; this session deliberately did not
  choose.** Marked in the source, not fixed. **This is a NEW SESSION's work.**

- **►►►►►►►► `grep -n "EXCEPTION" <run log>` IS THE FIRST ACTION ON ANY CRASH. THE PORT HAS ALWAYS
  SYMBOLISED ITS OWN. ◄◄◄◄◄◄◄◄** It prints `===== EXCEPTION 0xc0000005 =====`, `fault addr:` and
  `FAULT PC:`. `FAULT PC` is the leaf for free and cross-checks any derived base; **`fault addr`
  decides the SHAPE of the fix** — small (< 0x10000) is NULL-plus-offset and wants a NULL guard,
  large and unaligned is a WILD pointer and a NULL guard is worthless. Three rounds did not grep
  for it (`297` §11.1).

- **►►►► A BACKTRACE OF BARE ADDRESSES IS FULLY RESOLVABLE — BUT **DERIVE** THE LOAD BASE, NEVER
  ASSUME IT. ◄◄◄◄** `297` §10 back-solved the base from the assumption that
  `objBuildRenderState` was the leaf; that is circular, it was **off by `0x20000`**, and it cost
  three rounds and two fixes that could never have worked. **Every non-leaf frame is a RETURN
  address — the byte after a `call` — which is base-independent and pins the base uniquely over
  ~9 frames.** Dump `.text` once, collect the post-`call` addresses, and keep the only 64 KB-aligned
  base where **every** caller frame lands on one; **exclude the leaf from the fit.** A leaf that
  lands **mid-instruction is proof the base is wrong** (`297` §11.1).

- **►►►►►►►► `RUN-SHEET-297` IS THE REST OF THE NEXT ACTION, AND ITS GATE IS THE OWNER'S OWN
  SENTENCE: *THE CHARACTERS AND THE PROPS, PRESENT AND STABLE IN BOTH EYES.* `297`. ◄◄◄◄◄◄◄◄**
  ARM 3 is written and **NOT BUILT**. Nine blocks, in order, and the order is load-bearing:
  **§1 (offline gates, main PC) → §2 (build) → §3 (GATE B1, twelve strings) → §4 R0 (MONO, the
  shipping path — the extraction touched `objTick` and `chrTick`, so flinch, colour lerp and door
  SFX are checked BEFORE anything stereo) → §5 R1 (`REBUILD=0`, THE NEGATIVE ARM, the broken
  picture on purpose) → §6 R2 (`REBUILD=1`, THE ARM) → §7 R3 (pairguard) → §8 R4 (S3, only if R2
  passed) → §9 R5 (cost).**
  **`GETV_DLGRAB_AT` IS `5400`, NOT `900`** — at `panel` on a 180 Hz display frame 900 is ~5 s and
  is still the level-load fade, which is how `295`'s S2 scored a PASS on a black frame.
  `stereo_disparity.py` now refuses such a frame **by a different sentence** than the `B1` refusal.

- **►►►► THE RULE R0's CRASH BOUGHT: WHEN AN EXTRACTION IS JUSTIFIED AS "A MOVE", EVERY LINE THAT
  IS NOT MOVED IS THE SUSPECT LIST, AND IT MUST BE SHORT ENOUGH TO WRITE DOWN.** `297` §10.3: it
  was four lines out of 379, nobody wrote them down, and the review effort went to the 379 that
  were provably identical. **"Equivalent" is `[INFERRED]` until a compiler or a run says otherwise.**

- **`RUN-SHEET-295` IS WORN. `[MEASURED]` 2026-09-02** — S1 `checks=8400 mismatch=0`, S2a
  `checks=250803 mismatch=600` (**the falsifier fires**), S2b `checks=213951 mismatch=0`, exe
  `2026-09-02 01:29`. **ARM 1 and ARM 2 are green** and `294` §3.6's question is answered in the
  **null** (`295` §10.1: `mismatch == frames` exactly, every site `forced-read-after-lvlRender`,
  **no engine reader in 12,000 frames**). **§10.1's S2 arm was scored on a BLACK frame and its PASS
  is void** (`297` §0); the owner's three F9 grabs are what showed it, and they are the reason ARM 3
  exists as this session's work. **Nothing on this sheet is owed any more.**

- **SUPERSEDED, KEPT FOR THE RECORD — `RUN-SHEET-295` HAD NEVER BEEN RUN AS OF `296`. ◄◄◄◄**
  `[MEASURED]` 2026-09-02, on the bridge: **no `build_295_pairguard.log`, no
  `run_295_S1_guard_mono.log`, no `run_295_S2a_restore_off.log`, no `run_295_S2b_restore_on.log`**
  anywhere in the tree, and `goldeneye.exe` is **`2026-09-01 02:10`** — `292d`'s build, three
  sessions old. **ARM 1 and ARM 2 are COMMITTED (`b712fa50`) AND UNBUILT.** `296` therefore wrote
  **no ARM 3** (`295` §5: ARM 3 in the same binary makes `GETV_STEREO_PAIRGUARD` incapable of
  reporting anything but zero) and instead **completed the sheet**: `RUN-SHEET-295` §10 now carries
  the S2/S3/S4/S5 blocks that §6/§7/§8 previously delegated to `RUN-SHEET-292`, and §11 records
  four defects in that delegation. **§1's two offline gates were re-worn and both PASS**
  (`61 passed, 0 failed`; `injected -37, recovered -37`) — **but under the bridge's `gcc 11.4.0`,
  not the main PC's, so §1 is still owed on the main PC before the build.**
  **THE ORDER IS: §1 → §2 → §3 (S1) → §4 (S2a) → §5 (S2b) → §10.1 → §10.2 → §10.3 → §10.4.**
- **►►►► `290`'s THREE COMMITS, IN ORDER. NO REGEN OWED (nothing under `getv/port/**`; `verify`
  `15/15` before and after). ◄◄◄◄**
  1. **`vendor/ge-decomp` — STAGE BY EXPLICIT PATH LIST, NEVER `git add -A`** (the worktree is
     CRLF-dirty for ~2,099 files). Stage `src/game/lv.c src/game/posespine.c src/game/posespine.h`;
     **`git diff --cached --stat` must read `318 insertions / 0 deletions, three files`**.
     Message: **`COMMIT-MESSAGE-2026-08-31h-decomp.txt`, in the `GoldenEyeVR` ROOT** (`287`).
  2. **`goldeneye-native`** — the harness only, `getv/tools/posespine_harness.sh` + `.c`.
     Message: `COMMIT-MESSAGE-2026-08-31h-native.txt`.
  3. **`GoldenEyeVR`** — `290`, `RUN-SHEET-290.md`, this file, `NEXT-SESSION-PROMPT-291.md`.
     Message: `COMMIT-MESSAGE-2026-08-31h.txt`. **`COMMIT-NOW.cmd` WILL NOT DO STEP 1** (§6).
- **►►►► `289`'s THREE COMMITS, IN ORDER, AND ONE OF THEM HAS A TRAP. ◄◄◄◄**
  **NO REGEN IS OWED** — `289` touched nothing under `getv/port/**` and `tools/fetch-thirdparty.sh
  verify` reads **`15/15`** both before and after its build. That is now a free standing gate.
  1. **`vendor/ge-decomp` — STAGE BY EXPLICIT PATH LIST, NEVER `git add -A`** (2,097 CRLF-dirty
     files sit there; `7a4e7bfd` is what happens when they get swept in). **`git diff --cached
     --stat` must read `168 insertions / 11 deletions, three files`** — `propobj.c`, `bg.c`, `bg.h`.
     Message: **`COMMIT-MESSAGE-2026-08-31g-decomp.txt`, in the `GoldenEyeVR` ROOT** (`287`: a
     message file beside the repo it describes is invisible to `commit-now.ps1`).
  2. **`goldeneye-native`** — the harness only, `getv/tools/cullwhy_harness.sh` + `.c`.
     Message: `COMMIT-MESSAGE-2026-08-31g-native.txt`.
  3. **`GoldenEyeVR`** — `289`, `RUN-SHEET-289.md`, this file, `NEXT-SESSION-PROMPT-290.md`.
     Message: `COMMIT-MESSAGE-2026-08-31g.txt`.
  **`COMMIT-NOW.cmd` WILL NOT DO STEP 1** — `vendor/` is gitignored by `goldeneye-native` and
  invisible to all three of its passes.
- **~~THE REGEN IS DUE~~ — DONE. `288`'s patch is committed as `30a85b8` and `verify` reads `15/15`;
  `vendor/ge-decomp` HEAD is `ad4105cf`, so the `GETV_SLOTFREE` banner is in HEAD. Both re-checked
  at the start of `289`. THE ORIGINAL ENTRY, KEPT BECAUSE RULE `2` DELETES NOTHING:**
- **►►►► THE REGEN IS NOW DUE. ALL SIX `288` ARMS ARE WORN. ◄◄◄◄** `tools/fetch-thirdparty.sh
  verify` still says `DIFFERS getv/port/fast3d/gfx_sdl2.c` (14 ok, 1 differs) — **correct and
  expected**, that file is gitignored and regenerated. **Until the regen runs, the jitter statistic
  and `GETV_FPS=panel` exist only on this machine's disk and are in NO COMMIT** (`268` lost
  `GETV_DLGRAB` for two days exactly this way). Gate: **`15/15 files match pristine + patch`** —
  a byte count is not the gate. **MAIN PC, GIT BASH.**
- **►►►► AND THE DECOMP HAS BEEN CARRYING UNCOMMITTED KNOBS FOR A DOZEN SESSIONS. `288` §8. ◄◄◄◄**
  `[MEASURED]` **seven `GETV_*` knobs are absent from `vendor/ge-decomp` HEAD entirely** —
  `GETV_SLOTTRACE`, `GETV_ANIMSLOTS`, `GETV_CCPROBE`, `GETV_FOLDERBOX`, `GETV_FOLDERTRACE`,
  `GETV_ALIGNPTR`, `GETV_MENU_NOVALIDATE` — and `GETV_SLOTFREE` / `GETV_UNLOCKALL` are partial.
  **THE ONE THAT MATTERS: `"[getv][slot] GETV_SLOTFREE resolved to %d (env=%s)"` IS ABSENT FROM
  HEAD, and it is gate 4 of every run block on a knob this file calls BLOCKING.** A fresh clone
  prints no banner, the gate reads as a clean null, and `287` 4C's `0xc0000005` returns unnamed.
  **`268`'s `GETV_DLGRAB`, same shape, sitting longer.** **AND `GETV_CCPROBE` IS THE INSTRUMENT
  BEHIND THIS FILE'S OWN "the combiner is EXONERATED" FINDING — it cannot be re-derived from a
  clone.** 468 insertions / 5 deletions; `-w` reads 467 / 4, **so it is real code, not the CRLF
  ghost.** Message written: `COMMIT-MESSAGE-2026-08-31f-decomp.txt`. **STAGE BY EXPLICIT PATH
  LIST, NEVER `git add -A`, and check `git diff --cached --stat` reads 468 before committing.**
  **`COMMIT-NOW.cmd` WILL NOT DO THIS** — `vendor/` is invisible to all three of its passes (§6).

- **►►►► BLOCKING, AND IT BIT THIS SESSION. Delete `GETV_SLOTFREE = 0` from `%APPDATA%\Goldeneye-Native\Goldeneye-Native\goldeneye.cfg`** (derive the path with `$env:APPDATA`, §0). **`[MEASURED]` `287`: `[getv][slot] GETV_SLOTFREE resolved to 0 (env=0)` in EVERY arm today — 4A, 4B and 4C — because every block opens with `Remove-Item Env:GETV_*`, which wipes the workaround, and the per-user cfg then wins on config search path 4 (`262` §2). 4C reached the intro cast and DIED THERE: `[getv][slotfail] NO SLOT: required=155 | slots=10 free=0` -> `EXCEPTION 0xc0000005, fault addr 0x28` loading `CnatalyaZ`. 4A/4B survived only because they never triggered the cast (`displaycast` count 0 vs 20).** **`262`'s fix IS NOT IN EFFECT ON THIS MACHINE.** Until the cfg line is gone, EVERY block must carry `$env:GETV_SLOTFREE="1"` after its `Remove-Item` line — the run sheet's own *a block that omits a knob silently restores its default* rule, firing for real.
- **COMMIT `266`-`267`.** `port_render.c` is TRACKED — no regen needed for those.
- **BACK UP THE EEPROM before every run**: `local-only\save-backup.ps1 -Backup`.
- **~~Run the regen before the native half~~ — DONE 2026-08-30, `15/15 match`. `271` §7.**
  Still standing as a RULE for every future native commit, just no longer outstanding.

---

## 4. ►►►► WHAT IS **FALSE** — RETRACTED STANDING FACTS ◄◄◄◄

**►►►►►►►► `309`: *"the `S3b` error is roughly a 10-13% proportional error"* IS RETRACTED.**
It appears in `RUN-SHEET-308` §2, `308` §6.2 and `NEXT-SESSION-PROMPT-309`, and it is **the two
ENDPOINTS of the corpus, not the corpus**. `[MEASURED]` under `py` over all twelve scored `S3b`
grabs: **median `30.76%`, mean `28.88%`, range `12.9%`-`44.9%`**, ten of twelve between `20.1%`
and `34.8%`. The two grabs that produced "10-13%" are the largest and smallest predictions in the
corpus and are **the only two that behave differently from the other ten** (`309` §1.1, §5.1).
**The companion claim *"the error grows with disparity magnitude"* is retracted with it: the
RATIO is near-constant at ~`0.69`, which makes the absolute error grow as arithmetic rather than
as a second finding.**

**►►►► `309`: THE `309` DOC'S OWN PRE-REGISTERED `git diff --stat` FIGURE WAS WRONG.** §3.3
registered **`25 insertions / 5 deletions`**; the edit landed **`29 insertions(+) / 8
deletions(-)`**. **The gate's SUBSTANCE passed** — one path (` M getv/tools/stereo_disparity.py`),
`CRLF=0`, `anchors=9`, `SYNTAX OK`, `--selftest A/B/C PASS` byte-identical — **and the file on
disk is byte-identical (`md5 316cb9c317f225a3d16482733ee20c79`) to the copy the ladder was dry-run
against, which is the check that actually matters.** The miss was an assistant's hand-count of how
`git` coalesces unchanged lines inside a replaced block, offered with the same weight as a
measured value. **A pre-registered number derived by arithmetic in the head is a PREDICTION, and
it is labelled as one or it is not registered.**

> **THIS SECTION EXISTS BECAUSE EVERY MAJOR ERROR ON 2026-08-29 CAME FROM
> BELIEVING A CONFIDENT CLAIM NOBODY HAD MARKED DEAD.** Add to it; never prune it.

**►►►►►►►► FALSE, AND IT IS THE SENTENCE `NEXT-SESSION-PROMPT-308` OPENS WITH: "the currency line at the top now carries `307`'s full result and points forward to `308`." `[MEASURED]` 2026-09-04, `308` §0. ◄◄◄◄◄◄◄◄**
**IT CARRIED `307`'s STARTING STATE.** Lines 1-45 of this file contained **no** occurrence of `S3b`, `S3c`, `contrast` or `308`, and the block still ended *"READ ... **`RUN-SHEET-307` §1**"* -- the action `307` had already run and falsified. **`307` updated §3 `OWNER ACTION` and §4 `RETRACTED` and did not update its own currency line**, so the one paragraph a session is told to read first was the one paragraph that was stale. **THIRD INSTANCE of `306` §0's shape -- a handover prompt's opening sentence false when written -- and the first where the false sentence is ABOUT THIS FILE.** The defence is the same one command: **read the currency line and grep it for this session's own markers before quoting it forward.**

**►►►►►►►► FALSE, AND IT WAS `RUN-SHEET-308` §1.2's: "re-run `307` §2c's scoring block unchanged (it writes `disp_307_S3_all.txt` and `census_307_S3_all.txt`)." `[MEASURED]` 2026-09-04, `308` §0/§1.3. ◄◄◄◄◄◄◄◄**
**THAT BLOCK DOES NOT EXIST IN ANY DOCUMENT.** `RUN-SHEET-307` §2c writes `disp_307_S3b.txt` / `disp_307_S3c.txt` for **ONE grab per arm** and carries `<frame>` / `<frac>` placeholders. `grep -rl disp_307_S3_all repo\docs\` returns only `RUN-SHEET-308` and `NEXT-SESSION-PROMPT-308` -- **the two documents that CITE it.** The all-16 block was improvised live in the `307` session, produced the file every later gate depends on, and was never filed. **A pre-registered falsifier whose corpus is on disk is worthless if the block that reads the corpus is not.** It is reconstructed and PROVEN in `308` §1.3 (both `ARM` header counts and all 16 `predicted-frac` values reproduce exactly) and filed complete as `RUN-SHEET-308` §1.3 / `308` §5.4. **Same family as `305` §2a one level over: a claim about the filesystem, unchecked.**

**►► ALSO WRONG IN THE LAST DIGIT, AND IT WAS ABOUT TO BE PRINTED INSIDE THE INSTRUMENT: `RUN-SHEET-308` §1.0's "`S3c`'s maximum is `0.123`".** `[MEASURED]` 2026-09-04: **`0.122`** -- `(17.366 - 15.239) / 17.366 = 0.12249`, frame `1620`. The threshold does not move and the margin is 0.078 either way. **The reason it is filed at all is that §1.1's replacement text carried the number into the tool's own `confidence` line**, where it would have been quoted forward as measured. **AND A SECOND-ORDER NOTE THAT IS NOT AN ERROR: §1.0's block re-derives `contrast` from the PRINTED 3-decimal `mad` values while the tool uses full precision, so the two disagree by ~0.001** -- `S3c_7678` re-derives `0.041` and the tool prints `0.042`. **Expected, harmless against a 0.08 margin, and worth knowing before someone calls it a fault.**

**►►►►►►►► FALSE, AND IT WAS `RUN-SHEET-307` §2b's CONSTRUCTION: "`S3c` lands in band by construction, so it is a measurable arm." `[MEASURED]` 2026-09-04, `307` §2. ◄◄◄◄◄◄◄◄**
**IN BAND BY AMPLITUDE IS NOT MEASURABLE.** All four `S3c` grabs passed §2.0's amplitude gate (predicted −172 to −386 px) and then read `mad_best`≈`mad_zero` (15.2/17.4, 28.2/29.2) with the WRONG SIGN, on frames whose census is PERFECT (`only in eye0/eye1 = 0`, all `MODEL_*` equal). **A long sightline at sep 500 has no single global disparity -- near geometry shifts hugely, far geometry barely -- so a whole-eye cross-correlation has nothing to lock and reports noise.** The amplitude gate bounds what the correlator can EXPRESS; it says nothing about whether a single answer EXISTS. **`H18` needs a sibling: a CONFIDENCE floor (`mad_best` sufficiently below `mad_zero`). `S3b`'s ratios are 0.15–0.38, `S3c`'s are 0.88–0.96 -- the arms separate cleanly on it.** Same family as `H8`: a summary number (`dx`) computed on data that does not support it.

**►►►►►►►► FALSE, AND IT WAS `RUN-SHEET-307` §1's PRE-REGISTERED PREDICTION: "on a -7,024 px prediction the correlator MUST PEG and the `H1` alarm MUST FIRE." `[MEASURED]` 2026-09-04, `307` §1. ◄◄◄◄◄◄◄◄**
**IT DID NEITHER.** All four searches on `dlgrab_S3_5400` returned an INTERIOR maximum -- `dx +351 px` at `--search 500/800`, `+172 px` at `--search 200`, so the answer MOVES with `--search` -- POSITIVE where the prediction is -7,019 px, `mad_best 6.250` against `mad_zero 12.311`, and **no `dx IS PEGGED` line on any run.** The unrepresentable prediction did not force a peg; a near, dark, high-texture wall (energy 0.884) offered a spurious in-band correlation and the instrument locked onto it. **The alarm's premise is therefore wrong: an out-of-band prediction is NECESSARY but NOT SUFFICIENT for the peg, because an interior false peak pre-empts it. `H1` is RE-OPENED, and `H18`'s amplitude gate is the only thing standing between this correlator and a confident wrong number.** The tool's own `sign IS WRONG -- eyes SWAPPED` note does not fit -- a swap explains the sign, not a 20x magnitude gap.

**►►►►►►►► NARROWED, AND IT IS A STAGING INSTRUCTION THREE SHEETS CARRIED: "stand still, in a room,
FACING A WALL" is the right venue for `S3`. `[MEASURED]` 2026-09-04, `307` §1. ◄◄◄◄◄◄◄◄**
**RIGHT ABOUT THE RAY TEST AND WRONG ABOUT THE AMPLITUDE.** Facing a near wall gives a clean
`MEASURED centre depth` — `D≈47` — and **disparity goes as 1/D**, so at `separation=500` the
prediction is **−7,024 px on a 912 px eye.** The reachable range is clipped by the IMAGE EDGE, not
by `--search` (`301` §2 selftest C: `--search 800` searches `[-800..+595]`), so the number is a
request the correlator cannot express. **The instruction survives for the ray test and is replaced
for the venue: the grabbed frame's own `PREDICTION: disparity = … px` must satisfy `|px| ≤ 500`,
and that is `RUN-SHEET-307` §2.0.** Same family as `303` §3.2 one level over: **a venue that makes
the mechanism LOUD can make it UNMEASURABLE.**

**►► ALSO FALSE, AND IT WAS `304` §1.4's: "the polygon CONCENTRATES and the dead eye SCATTERS —
79-86% against 5-8%."** `[MEASURED]` `307` §3.1: **`dlgrab_P2_1369` is a fully dead eye reading
`blobs 1`, largest `576312` of `576312` — 100% — with a bbox covering the ENTIRE unmasked eye.**
The 5%/8% figures came from `S2_1176` and `S3_1155`, two **opening** frames where eye 1 is partly
populated and the difference scatters. **A fully dead eye is one solid blob. MAGNITUDE separates
them — tens of thousands of pixels against half a million — and concentration alone does not.**
`304` §1.3's rule applied to its own successor: a calibration on the frames you already understand
is a hypothesis.


**►►►►►►►► FALSE, AND IT IS THE SENTENCE `NEXT-SESSION-PROMPT-306` OPENS WITH: "`RUN-SHEET-304` IS
NOW WORN IN FULL AND NOTHING IN `305` IS COMMITTED YET." `[MEASURED]` 2026-09-04 from `git log`,
`306` §0. ◄◄◄◄◄◄◄◄**
**BOTH HALVES ARE WRONG.** `689b009` (`goldeneye-native`, `dlgrab_dlorder.py`) and `e58e1f1`
(`GoldenEyeVR`, six documents) are committed, and `git --no-optional-locks status` on every named
path is empty — **`RUN-SHEET-305` §5 is WORN, not pending.** And `RUN-SHEET-304` is **not** worn in
full: **§2a's `P1` arm ran at `2026-09-03T23:48:34Z`** and its reading has never been taken, while
`P2` has not run at all. **`git log --oneline -3` is a bridge-safe read that answers the first half
in one command** (`00-STATE` §6). **THIRD AND FOURTH INSTANCE of `305` §2a's rule, and the rule now
covers git as well as the filesystem.**

**►► ALSO FALSE, AND IT WAS THIS FILE'S OWN AND `RUN-SHEET-305` GATE §2a's: "the corpus is 256
dumps."** `[MEASURED]` on disk 2026-09-04: **265** — `grabs_304_P1` added exactly nine at 23:48.
**The gate would have refused a sweep over a discrepancy that is fully explained by one folder**,
which is why `RUN-SHEET-306` §2 reproduces the 256 and scores the nine separately instead.

**►►►► AND A CLAIM ABOUT AN INSTRUMENT, NOT ABOUT THE GAME: "`305`'s numbers only need re-wearing
under `py` because the two Pythons might round differently." `[MEASURED]` 2026-09-04, `306` §1.**
**They do not disagree about arithmetic; they disagree about ENCODING, and the disagreement is
fatal rather than numerical.** `dlgrab_dlorder.py` died on `►` at the first `PERMUTATION` verdict
under a `cp1252` stdout and produced no summary line at all. **`H7` is not "the numbers might
differ" — it is "the run might not happen".**


**►►►►►►►► NARROWED, AND IT IS THE LOAD-BEARING SENTENCE OF THREE DOCUMENTS: "the census on
`dlgrab_C1_4676` is PERFECT -- `39/39`, `only in eye0 = 0` AND `only in eye1 = 0` -- so the
difference is downstream of admission." `[MEASURED]` 2026-09-03, `305` §1.3. ◄◄◄◄◄◄◄◄**
**TRUE OF THE SET AND FALSE OF THE ORDER.** `dlgrab_eyecensus.py:96-97` computes
`set(a['calls']) - set(b['calls'])`, so a frame whose two eyes call exactly the same display
lists in a DIFFERENT ORDER scores zero both ways. **`4676` is such a frame: DL calls `[29..36]`,
eight of them, a CYCLIC ROTATION BY THREE.** The census is not wrong -- it answers "was it
SUBMITTED", which is the question it was built for and the one that closed GROUP `B`. **Nothing
asked "was it submitted in the SAME PLACE", so nothing could see it.** `303` §5, `304` §0,
`PRIORITY-BOARD-299` GROUP `C` and this file's own currency line all quoted that census as
evidence. **The conclusion SURVIVES for `C1_2336` and `V1_2732`, which `dlgrab_dlorder.py` reads
ORDER-IDENTICAL -- it does NOT survive for `4676` on the census alone.**

**►► ALSO FALSE, AND IT WAS `RUN-SHEET-304` §2's OWN FRAMING: "`4676` is either the same fault at
amplitude or a second one."** `[MEASURED]` `305` §1.4/§1.5. **It is a frame that carries a
SECOND, SEPARATE defect -- and that defect is HARMLESS.** The two admissible frames carrying the
identical rotation, `dlgrab_2928` and `dlgrab_2957`, read **`total 0 px  blobs 0`** while
`C1_2336` and `V1_2732` carry a polygon with **no order difference at all**. **So the reorder
does not explain `4676`'s 109,920 pixels and the polygon does not need it. Neither branch of the
question as posed is the answer.**

**►► ALSO FALSE: "the four `dlgrab_D3_*` files are still sitting in `grabs_303_V1\`" and
"`304` §3 (FC3/FC4) is optional and still owed."** `[MEASURED]` on disk 2026-09-03, `305` §2a:
**§4 is done and §3 was RUN at 22:17:46Z / 22:18:34Z.** Both entries stood in §3 and in
`NEXT-SESSION-PROMPT-305` while the work was already on disk. **A run sheet's "owed" list is a
claim about the filesystem and it goes stale like any other measurement -- check `grabs_*` and
`run_*.log` before repeating one.**

**►► AND A CORRECTION TO A METRIC, NOT A FACT: `304` §1.4's LARGEST-BLOB CONCENTRATION
UNDERSTATES A MULTI-SLAB FAULT.** `4676` reads 38% by largest blob against `2336`'s 86%, which is
what sent `304` looking for "a second fault". **By TOP-THREE share the same frames read 73%
(`4676`), 100% (`2336`), 95% (`V1_2732`) against the dead-eye frames' 14% (`S2_1176`) and 23%
(`S3_1155`)** -- `4676` lands with the polygon group, not the dead-eye group, and the largest-blob
figure is the only reading that separated it. **The hint was right that `4676` is different and
wrong about how.**


**►►►►►►►► FALSE, AND IT WAS `303` §6's: "three hits, zero false positives" / "the separation is a
factor of ten". `[MEASURED]` 2026-09-03, `304` §1.2. ◄◄◄◄◄◄◄◄**
True of the NINE frames it was measured on and false of the corpus. `stereo_eyediff.py` shipped
differencing **LUMINANCE** -- correct in `stereo_disparity.py`, which is a CORRELATOR, and wrong in
a DIFFER -- so it scored `dlgrab_S2_1176` (`301` S2, provenance clean) **CLEAN at 1,329 px on a
frame with a WHOLE DEAD EYE**: eye0 a near-uniform dark NAVY void, eye1 the entire building, and
navy and brown at that brightness have nearly the same luminance. `dlgrab_S3_1155` -- the frame
`302` §3c names itself -- was the second miss. **Per channel the two read 4,845 px / 90,358 and
1,967 px / 23,515.** **THE RULE: A LUMINANCE METRIC CANNOT SEE A CHROMA-ONLY DIFFERENCE**, which is
`H8` one level over, and **a nine-frame calibration is a hypothesis, not a measurement.**

**►► ALSO NOT ESTABLISHED: "the corpus dates the polygon before the viewer fix."** Nothing dates
it. Five pre-`303` frames carry the signature and **not one is admissible**: `dlgrab_2893`,
`dlgrab_3393` and `dlgrab_5284` are announced by **no log at all**, `dlgrab_900` by **five**, and
`dlgrab_7360` by `run_295_S2a_restore_off.log` -- **the `VIEWRESTORE=0` arm, whose guard is
SUPPOSED to fire** (`298` §3). The two clean-provenance pre-`303` hits, `S2_1176` and `S3_1155`,
are dead-eye frames by concentration (5% and 8% of their differing pixels in the largest blob,
against a polygon's 79-86%). **OPEN, not answered no, and it needs a RUN.**

**►►►►►►►► FALSE ON THIS BINARY, AND IT WAS `299`'s: "`292`'s DOUBLE CONVERSION IS ALIVE --
`arrays=144716 already-converted=11902`, every hit `eye=1`, MOST OF THEM `NaN`." `[MEASURED]`
2026-09-03, `303` §4. ◄◄◄◄◄◄◄◄**
`C1` reads **`arrays=366456 already-converted=0 skipped=0`** with `GETV_STEREO_MTXGUARD=1` on an
arm whose banners match `299` E2's (stereo ON, VIEWRESTORE ON, REBUILD ON). **The upstream counter
is 2.5x E2's and nothing rejects upstream of the conversion, so this is a result and not a masked
zero** (`298` §4.2 applied forwards, `289` R2 satisfied rather than cited). The trend is
`292` 48.2% -> `299` 8.2% -> `303` **0.0%**. **`bondviewTransformManyPosToViewMatrix`'s own report
carries the verdict, written into the source before the run: *"already-converted=0 means the
saturated matrix came from somewhere else and this diagnosis is WRONG -- do not keep it."*
GROUP `C`'s leading hypothesis is retired, and because the guard's test catches out-of-range
floats generally, the `NaN` may have gone with it.** **BOUND: this establishes absence on this run
and this route. It is not a proof about every route, and it does not explain `303` §5's polygon --
nothing does yet.**

**►►►► ALSO NOT SUPPORTED, AND IT WAS `303`'s OWN: "the far per-vertex clamp is what makes the
distance foggy, flickering and transparent." `[MEASURED]` 2026-09-03, `303` §3.** FC1/FC2 put the
knob at full strength (far `clamped=81,076` = `straddle` exactly, against `0`) and **the owner sees
the same picture in both arms.** The claim is **UNANSWERED, not false** -- the A/B was run where
the knob is loud and the picture is blank. **`302` §4's `beyond_far=13.2%` is retired as a
comparable figure**: `[getv][far]` is cumulative and that run contains a 5% scene and a 67% scene,
so the headline is a weighted average of two places. **Any future far figure is quoted per window
or not at all.**

**►►►► AND `RUN-SHEET-303` §4's OWN VENUE ARGUMENT IS HALF FALSE -- MINE. "On a loop there is
nothing to normalise."** True of the OWNER'S EYES. **False of the COUNTERS**, which accumulate over
the whole run including the walk to the loop and the death, so two loop arms still differ by
however much gameplay each one carried in front of it (far `straddle` 1,790 vs 2,097 per Mvtx in
FC1/FC2, and nothing should be read into that gap).

**►► ALSO FALSE, AND IT IS `PRIORITY-BOARD-299` `H9`'s OWN FILED FIX: "a reference-frame differ
would need a known-good frame this project does not have."** **True of a MONO frame, false of a
STEREO one.** At `GETV_STEREO_OFFSET=0` the two halves must be identical apart from the viewmodel,
so **the second eye IS the known-good frame** -- same run, same rig, same instant, nothing to
normalise. `303` §6, `getv/tools/stereo_eyediff.py`. **Fourth instance of `301` §0's rule, with a
twist: the diagnosis was not wrong about the defect, it was wrong about the IMPOSSIBILITY.**

**►►►►►►►► FALSE, AND IT WAS `298`'s: "`all_near` 50 -> 548 IS THE PRICE OF `GETV_NEARCLAMP=0`
STARTING TO SHOW." `[MEASURED]` 2026-09-03, `299` §8.1. ◄◄◄◄◄◄◄◄**
**`ge_far.tri_all_near` AND `ge_far.tri_straddle_near` ARE INCREMENTED OUTSIDE `if (nc)`**
(`gfx_pc.c:3749-3750`), so they are **knob-independent by construction** and cannot show the
clamp's cost either way. The three `299` arms settle it: `all_near` reads **12 (clamp ON),
150 (OFF), 51 (ON)** -- the ON arms disagree with each other by 4x, because the counter measures
**how much geometry the player stood inside**, not what the knob did. **The conclusion survives on
the GL semantics** -- without the clamp GL discards every triangle crossing the near plane -- **but
the number offered as its evidence measures nothing, and `298` §4.4 must not be cited for it.**
**Reading a counter without reading the branch it sits outside of** -- `288` §6's shape, and mine
for repeating it into `RUN-SHEET-299` §1.4 before checking.

**►►►► ALSO FALSE: "`298` §1.1's SIX `SUMMARY` LINES SHOW THE DRIVER WALKS `g_OnScreenPropList` AND
TAKES ALL OF IT."** `[MEASURED]` `299` §4 and §8.3: the counters are reset **every tick**
(`gePropsSnapshotTickZDepth`), so at `GETV_STEREO_REBUILD_REPORT=600` each line is **one frame's
snapshot, not the window's** -- six spot checks, not a census. **At `=1` it is a census**, and the
census then shows **372 frames per run where the one listed prop is SKIPPED and the second eye gets
nothing.** The sentence was true of the six frames it landed on and false of the run.

**►► AND A SMALLER ONE IN THE SAME LINE: `list=` AND `chr`/`obj`/`skipped` ARE NOT CAPTURED AT THE
SAME MOMENT, SO "chr + obj vs list" IS NOT A BALANCING SUM.** `list` prints `g_OnScreenPropCount`
**at report time**; the others count the last tick's loop over `ge_props_zsnap_n`. `[MEASURED]`
`299` §8.3: **169 frames per run read `list=1` with `chr=1` AND `skipped=1`** -- two entries
processed against a list of one. **The sum balances only while the list is stable.**


**►►►►►►►► "THE WALL MOVING AND THE BUILDING SPLITS ARE ONE SYMPTOM" IS FALSE. THEY ARE TWO BUGS
WITH OPPOSITE FALSIFIER RESULTS. `[MEASURED]` 2026-09-02, `298` §3. ◄◄◄◄◄◄◄◄**
Carried as one complaint since `278`. `GETV_ROOMSCISSOR=0` **removes the facade split and leaves the
wall cut untouched**, and arm D reproduces the wall cut at shipping defaults with both falsifier
banners absent. `bg.c:445-447` states both branches in advance; one of each fired. **The per-room
clip rectangle is implicated for the FIRST symptom only, and every future arm must say which of the
two it is aimed at.**

**►►►► ALSO FALSE, AND IT WAS THIS SESSION'S OWN: "the wall movement is a collapsed painter's
order."** Proposed here because a draw-order failure would track the camera and ignore the scissor.
**`GETV_ORDER`'s own stated null is *"if every room lands in bucket 0 there is no ordering at all"*,
and `[MEASURED]` over all 16,412 frame dumps in `run_298_order_E.log` it does not fire**: spans run
`[0..1]` through `[0..7]`, and **all 216 `[0..0]` frames have `rooms=1`, which is trivially
ordered.** The ordering is intact. Pre-registered, measured false, dead.

**►► ALSO FALSE: "`GETV_FILTERING=0` in the environment selects nearest sampling."** It does not —
`ge_config.c`'s `key_filtering()` writes `configFiltering` directly with no `over` guard and the
per-user cfg wins (`298` §5). **Two runs were scored against a knob that never took**, and both
banner `filtering=2`. `GETV_POINT_FILTER` on the adjacent line DOES respect precedence, so the two
mechanisms can disagree — which `key_filtering`'s own comment says they must never do.

**►► ALSO FALSE: "the flat untextured slabs filling half of the arm-A frames are a missing-texture
defect."** `[MEASURED]` texture energy **0.029** in the slab against **4.467** for the street in the
same frame, and the same brick renders crisply where the wall recedes in the same crop. **It is the
camera pressed against a wall with the texture magnified past its last texel** — the fence and
railing story in its extreme form, third instance. Not a second fault.

**►►►►►►►► `297` §10 IS FALSE IN ITS ENTIRETY: THE R0 CRASH WAS **NOT** `objBuildRenderState + 199`,
AND THAT FUNCTION IS NOT ON THE R0 STACK AT ALL. `[MEASURED]` 2026-09-02, `297` §11. ◄◄◄◄◄◄◄◄**
The symbol came from a load base computed by **assuming `objBuildRenderState` was the faulting
function and back-solving from it** — circular, and stable enough to pass for a measurement: it
names a real function, the map bounds it, and `objdump -d` prints plausible lines. The real base
was **`0x20000` away**. Everything built on it is void:
- the `+ 199` resolution and the four source lines §10.1 attributes to it;
- the `gunCreateBeamForHand` / `explosionCreateBulletImpact` caller chain (§10.1) — **the real
  chain is `lvlRender -> chraiCheckUseHeldItems -> chraiCheckUseHeldItem ->
  chraiDefaultWeaponFireHandler -> chrTestHit -> sub_GAME_7F06C010`**;
- **the claim that re-deriving `obj`/`model` from `prop` caused a crash.** It did not. The
  parameters are still correct as a matter of the extraction being a MOVE, but
  `propobj.c`'s three `prop->obj` -> `obj` casts are **hardening, not a fix**: `[MEASURED]`, the
  pre-ARM-3 parent has `prop->obj` at all three sites and does not crash. **Do not cite them.**
- the second fix's report that it was *"confirmed in the binary, not inferred"* — the instruction
  bytes were read correctly and **attributed to the wrong function.**

**►► ALSO FALSE, AND IT WAS THIS SESSION'S OWN: a 32-bit `lea 0xd0(%rsp),%eax` pointer truncation
at `chrTestHit`'s call site.** It does not exist. `objdump -d --start-address=<arbitrary>`
**desyncs the x86 decoder and invents instructions**; the linear dump has `lea ...,%rax`. Confirm
every instruction against a linear disassembly before reporting it (`297` §11.1).

**►► ALSO FALSE: "`bondtypes.h` says `ChrRecord.model` is at `0x001C` but the code reads `0x20`, so
it is a wrong-field read."** Those comments are **N64 32-bit offsets, not the native layout.**
`chrTick` compiles `prop->chr->model` to the same `0x8` / `0x20`. **Confirm a suspected wrong-field
read against a known-good site before calling it a bug** (`297` §12).

**►► §6's "THERE IS A STALE `index.lock` IN THE DECOMP RIGHT NOW, DATED `2026-08-29 04:13`" IS NO
LONGER TRUE. `[MEASURED]` 2026-09-01, `292`, on the bridge:** all four repos
(`GoldenEyeVR`, `goldeneye-native`, `vendor/ge-decomp`, `GoldenEye64Recomp`) have **no
`index.lock` at all.** It went at some point between `276` and now — **by whom and when is not
established**, and nothing here claims it. **The §6 paragraph and `RUN-SHEET-276` STEP A0 both
still instruct a main-PC repair that has nothing left to repair.** The rest of that §6 entry — that
the bridge cannot delete such a lock, and that `git status`/`git add` from the bridge create them —
**stands and was honoured this session** (`git --no-optional-locks` throughout; re-checked after the
last read, all four clean).

**►► `293` §3b.3 AND §3b.4 ARE BOTH RETRACTED IN FULL BY `294`, AND BOTH WERE SOURCE READS THAT
MADE THE EYE LOOP LOOK HARDER THAN IT IS.** §3b.3's *"view-dependent write into world state"*,
*"the last eye wins"* and *"a 250-unit offset on the boarding test"* describe a **round trip whose
view cancels exactly** (`294` §1). §3b.4's *"a pointer into the MODEL's node rwdata"*, *"per MODEL,
not per eye"* and *"doubling the arena does not cover this"* describe **the arena itself** (`294`
§2). **Neither was measured; both read plausibly; both were wrong.** The surviving sentence from
the pair is one neither of them wrote — the **pairing invariant**, §7.

| claimed | truth | killed by |
|---|---|---|
| *"`293` §3b.3: the tank rect is a view-dependent write; last eye wins; 250 units at `OFFSET=500`"* | **FALSE.** `V2W · (W2V · world)` is a ROUND TRIP; the offset cancels on one line. | `294` §1 |
| *"`293` §3b.4: `modelFindNodeMtx` returns node rwdata, per MODEL not per eye; doubling the arena does not cover it"* | **FALSE on every clause.** It returns `&model->render_pos[index].pos` — the arena. Doubling it is exactly what covers it. | `294` §2 |
| *"`92`: 90 Hz is structurally unavailable"* | **FALSE.** A truncating divide and a hardcoded `60`. | `134` |
| *"`RB-04`: Bond's walk is an exponential approach with no timestep, inside `MoveBond`"* | **FALSE.** The walk IS delta-scaled (`bondview2.c:7845`). The delta is an **integer field count**; the port's own `printf` documents the 1.5x. | `259` |
| *"`GETV_SLOTFREE` is parked OFF"* then *"the park never took effect"* | **BOTH WRONG.** The park DID take effect — via config search path 4, the **per-user** `%APPDATA%` cfg. `261` §2 checked three paths, not the live one. | `262` §2 |
| *"`eeprom.bin` is exonerated; the folder fault survived a blank boot"* | **FALSE.** That boot loaded 512/512 bytes. The EEPROM lives in `%APPDATA%`, not beside the binary. | `260` §1 |
| *"The black faces are a total split across eleven characters"* | **FALSE — six of them were invented.** Two faults only: Ourumov's shirt, one Trevelyan's face. Inferred from two screenshots, stated as measured. | `263` §1 |
| *"`257` §7: BUILD ONCE, then runs 2 and 3"* | **FALSE.** Every queued `GETV_*` was already in the 04:36 binary. | `260` §3 |
| *"`237`: the folder fault is a stale `eeprom.bin`"* (retracted by `256`) | **UN-RETRACTED.** `256`'s retraction rested on the non-blank "blank" run. | `260` §1 |
| *"`263` §4: the 1x1 surfaces are black because their COMBINER INPUTS are black"* | **FALSE.** The fault's inputs are the least black in the log, and a BLACK texel with a BLACK prim renders CORRECTLY on `CheadbrosnanboilerZ`. | `265` §2 |
| *"`264` §4: `near=`/`last_delta=` count 1x1 uploads that missed the table"* | **FALSE — mine.** `ge_cctab_find()` runs on EVERY textured draw, so `near` is noise. `unkeyed=` is the correct counter. | `265` §5 |
| *"`257` §6.1: the frame is timed with `SDL_GetTicks()`, so `P5` is unmeasurable"* | **FALSE — mine.** Those lines are inside `if (rendered < 5)`, the boot-stall bisector. The steady state already used `SDL_GetPerformanceCounter()` and `CLOCK_MONOTONIC`. **A read that stopped one conditional too early** — same shape as `259` and `261` §2. | `266` §1 |
| *"`266` §3: `OVER=` is the term that can fail; that is the whole of `P5`"* | **FALSE — mine, same day.** The bracket contains the pacer's `sys_sleep()` and the vblank wait, so the figure tracks the PERIOD. **Proof: it changed when the cap changed.** | `267` §1 |
| *"`00-STATE` §3.5: the 90 Hz artifact is geometry, not a texture, and is in STEREO'S PATH"* | **FALSE.** Neither geometry nor the renderer — a simulation divider that turns itself on at 90 Hz. Says nothing about `lvlRender`'s per-view loop. | `268` §1 |
| *"the F9 hook belongs in `keyboard_on_key_down()`"* | **DEAD CODE — mine.** NOTHING in this port calls `gfx_wapi->set_keyboard_callbacks()`, so `kb_key_down` is always NULL. Cost a whole build-and-run cycle. Now read off the SDL event. | `268` §4 |
| *"`GETV_DLGRAB`: `0xB1` is `TRI2`"* | **WRONG NAME — mine.** `0xB1` is GE's `G_TRI4` (`model.c:7265`). The raw byte is authoritative; `gfx_pc.c:5675` handles it correctly. | `268` §4 |
| *"a single-frame capture can show this fault"* | **FALSE — mine, and the OWNER caught it**: *"the pictures don't show what I see."* A fault living between frames is not in any one frame. | `268` §4 |
| *"the late gun sound is the audio queue depth — `GE_QUEUE_TARGET` is 66.8 ms and `want.samples=512` adds 23.2 ms"* | **FALSE — mine.** `q=1114-1436` and `n=720` in BOTH the silent arm and the working arm; `port_audio.c:616`'s early-out never fires in any run. **Wrong sign too**: over-queueing makes audio LATE, and the fault was SILENCE. | `269` §5.1 |
| *"the `GETV_MENU` silence is the selected folder's save holding `music_vol=0`"* | **FALSE — mine, killed in ONE run by a falsifier written in advance.** Harness + a different folder was still silent; normal boot + the "bad" folder was fine. **Both came out opposite to the prediction.** | `269` §5.2 |
| *"`00-STATE` §3.5: `GETV_SIMDIV=auto` engages ITSELF at 90 Hz"* | **IMPRECISE — mine.** `frametiming.c:209`'s **UNSET-DEFAULT** branch is what engages, printing *"simulation held to"*; `auto` prints *"auto:"* and is a different branch. **"Refuse `auto` above 60" would NOT have prevented it.** | this session, from source |
| *"`267` §5 / `271`: headroom is `budget - work`"* | **FALSE — MINE, and it is `267` §1's error one level down.** The bracket holds Fast3D's replay and the swap, NOT the game tick or the display-list CONSTRUCTION. It overstated real idle by exactly the residual (0.231 ms at 60, 0.183 at 90). **`idle_mean` — the pacer's MEASURED sleep — replaces it.** | `271` §4 |
| *"`267`'s 60 and 90 runs are one experiment"* | **FALSE.** Read from their own banners: the 60 arm ran **vsync=1**, the 90 arm **vsync=0 AND the simulation held to 30 Hz** (they predate `268`), and neither pinned a stage. `267`'s conclusion survives; **a baseline rerunning that recipe would have understated the work.** | `271` §5 |
| *"`GETV_GPUTIME`'s GPU timeline / CPU in swap measure the GPU and the present"* | **FALSE — BOTH MEASURE THE FRAME CAP.** `11.11` at an `11.111` ms period, `16.67` at `16.667`, and **byte-identical in a VENT and on CRADLE** while CPU work differs 4.4x. The query and the swap bracket both contain the pacer's `sys_sleep` (`gfx_sdl2.c:111`). **Every verdict string it prints is void.** THIRD instrument with this same bracket error. | `272` §2-§4 |
| *"`271` §2: the pre-stereo baseline is 0.259 ms at both caps"* | **A VENT NUMBER, NOT A BASELINE — mine.** `GETV_STAGE=34` is `LEVELID_FACILITY`, which opens in a ventilation shaft; the pin was inherited without anyone asking what level it was. Cradle is **0.890 ms, 4.4x**. `271` §8 wrote this caveat itself. **THE OWNER CAUGHT IT FROM THE SCREEN:** *"I'm inside of a vent."* | `272` §4.2 |
| *"`PERFORMANCE.md`: the GPU timeline is ~6 ms and is indifferent to resolution"* | **UNUSABLE HERE.** Taken on a Surface Pro 3 / Intel HD 4400, so `[ASSUMED]` on this rig regardless — **and the instrument it came from is now known broken, so re-running it cannot transfer it either.** Nothing deleted; `272` supersedes that section until the repair lands. | `272` §4.1 |
| *"`272` §7: the GPU timer reads the period because `glEndQuery` sits after the pacer's sleep"* | **FALSE — MINE.** It was moved ahead of the swap AND the sleep and the figure did not move at all: 11.11 before, 11.11 after, both levels. The CPU issues the two markers **0.22 ms apart** while the GPU reports 11.11 ms between them — **the GPU waits INSIDE the window.** `ge_gpu_timer.c:179-189` named the mechanism in its own source and I read it twice without applying it. | `273` §4.1 |
| *"`272` §7: the repaired figure must be CAP-INVARIANT"* | **AN UNOBTAINABLE REQUIREMENT — MINE.** A capped run cannot yield a clean GPU figure whatever the bracket does. It was a correct FALSIFIER and a wrong specification: **the repair was a RUN CONDITION, not a bracket.** | `273` §4.2 |
| *"`272`'s four arms are a reproducible control"* | **FALSE.** They ran with `$env:GETV_SIMDIV` **inherited from a shell** and recorded nowhere; a clean env reset makes the 90 Hz arms engage `268`'s divider. `GETV_SIMDIV=1` prints NOTHING, so the gate is `props interpolated 0` + zero `simulation held to`. | `273` §7.1 |
| *"`GETV_SUPERSAMPLE` is a fill-rate knob on Windows"* | **INERT.** Both `getenv` sites are behind `TVOS_SUPERSAMPLE` / `GE_POSTFX`, neither defined here, while `ge_config.c:410` accepts it and puts it in the environment. **A clean null that would have read as a result.** `GETV_WINDOW=WxH` is the one that works. | `273` §7.2 |
| *"`-MessageFile`"* | **DOES NOT EXIST.** `commit-session.ps1` takes `-Message`. | `HANDOVER` |
| *"`ITEM ENTRY CORRUPT`"* | **FALSE ALARM on Windows.** Asserts `h>>32 == 1`; our pointers are `0x00007ff6…`, so it fires always. | `242` §3 |
| *"`fault addr: ffffffffffffffff` means `-1`"* | **FALSE.** Means NON-CANONICAL; #GP has no faulting address and Windows fills ones. | `249` |
| *"`260` §4 / `RUN-SHEET-260`: `GETV_REALCLOCK=1` -> `speedgraph ~60/s` **while `fps` reads 90**"* | **FALSE — mine, and it was written into a run sheet as a prediction.** `[MEASURED]` `fps` reads **60.0**, cap granted in the banner. The `~60/s` half was right for the wrong reason: the RENDER fell to 60. | `274` §6 |
| *"`274` §5: 34 of the 44 divide sites are guarded by `g_ClockTimer > 0`, 10 are NOT"* | **FALSE — a GREP, not a READ, and `274` §9 said so itself.** `[MEASURED]` **40 guarded, 4 not.** There are THREE guard spellings; the grep saw one. `gunfire.c:5992` and `:6309` guard with `>= (0 + 1)` — the source even carries `// Keep the 0 + 1 for matching` — and `propobj.c:5698` guards the DIVISOR with `> 0.0f`. **A grep for a guard is not a read for a guard.** | `275` §1 |
| *"`275` §7 / `RUN-SHEET-276` §0 prediction 4: the stopwatch on the `RB-04` walk reads `18.2 s`, not `27.0`"* | **INVERTED — MINE.** `145`'s table: RB-02 **27.04 s is the CORRECT** figure, RB-03 **18.18 s is the 1.5x-too-fast** one — a faster Bond finishes SOONER. `126`, `257` and `274` §2.1 all use them that way. The run sheet inherited it verbatim and it was handed to the owner a THIRD time in this session's arm-B block. | `277` §6.1 |
| *"the `RB-04` walking route measures the `GETV_SIMHZ` fix; term-on vs term-off should differ by 1.5x"* | **FALSE — MINE, AND UNMEASURABLE BY CONSTRUCTION.** `[MEASURED]` `14.32` vs `14.24` = **1.006**. The route is timed by Bond, Bond's walk has **no delta in it** (`145` §2), and both arms render 90 — so they were always going to come out equal. **`145` §1 and §2 said so and I quoted its NUMBERS without reading its MECHANISM** — the same shape as `275` §1's grep-for-a-guard, third instance in three sessions. **The right instrument was the owner's: watch the truck.** | `277` §6.2 |
| *"`126`/`145`: 29.48 / 27.04 / 18.18 are the `RB-04` baseline for this port"* | **NOT COMPARABLE IN ABSOLUTE TERMS.** Different build (recomp) and a route whose LEVEL was never recorded anywhere. **Only the RATIO transfers.** The route is now written down — Dam, `GETV_STAGE=33`, start to the barrels — with a this-binary baseline of **60 Hz `20.94 s` / 90 Hz `14.32 s`.** | `277` §7 |
| *"the widescreen holes are the portal clip box never learning about 16:9, so wide admits fewer rooms"* | **FALSE — MINE, AND MEASURED FALSE IN THE ARM I WROTE IT FOR.** It predicted FEWER rooms drawn at 16:9. `[MEASURED]` 200 stationary frames, same spot, artifact on screen: the `GETV_CULLSTAT` census is **byte-identical**. Correct scope: room ADMISSION is exonerated, the per-room clip RECTANGLE is not. I then over-corrected to a bare *"culling is exonerated"*, which is also wrong. | `278` §3, §7.1 |
| *"`282` §2.2: a straddling portal fails OPEN, so it cannot produce a too-tight box"* | **FALSE — MINE.** The crossings project through `bondview.c:734`'s `z==0 -> inv_z=-1e20` guard, so they expand only the side their SIGN points at. `[MEASURED]` **4,955 of 5,373 straddles (92.2%) kept at least one side finite**, and the existing inverted-box fail-open fired **0** times in 37,620 boxes. | `283` §2 |
| *"`283` §3: the LEFT slab is the straddle's fault"* | **FALSE — MINE, and I flagged it as unsafe before the build that killed it.** `GETV_PORTALOPEN=1` makes straddles fail open and the holes come back unchanged. The `0.07`-unit edge match stands as a measurement; the causal claim does not. | `284` §2 |
| *"`281`: the projector DROPS behind-camera verts instead of clipping them"* | **FALSE.** `sub_GAME_7F0B5528:2311-2325` appends the near-plane crossings; `cross=4` on the faulting portal proves the loop ran. Both of `281`'s patches are dead. | `282` §2.1, `284` §2 |
| *"`RUN-SHEET-283` §0: arm A will make the picture wrong in NEW ways — walls through walls"* | **NOT OBSERVED.** `[REPORTED]` *"much better"*, unqualified, and again on `285` S3. One level, one session — **not a clean bill, but the predicted cost did not appear where predicted.** | `284` §1 |
| *"the tank is entered by standing on top of it"* | **FALSE — MINE, and the OWNER said side-entry from memory and was right.** Detection lives in `bondviewTryMoveToStan`'s `block_20`, the **OBSTRUCTED** branch (`bondview2.c:2540-2571`) — you walk INTO it. I read `:2969`'s rect test without following the branch that arms it. **FOURTH instance in four sessions of the same shape** (`275` §1 grep-for-a-guard, `277` §6.2 numbers-without-mechanism). | `278` §7.2 |
| *"`dlgrab_2700` is a clean frame from this run"* | **THE WRONG ARTEFACT — MINE.** It is dated `2026-08-30 00:30` with a **1280x960** BMP: a windowed run from a PREVIOUS session. This session's dumps are 22:55-23:02 with **2560x1369** BMPs. **`dlgrab_*` accumulates across sessions in `build-windows` and is told apart only by timestamp and BMP byte count.** | `278` §7.3 |
| *"`286` §1: the switch's four remaining sites are `chr.c:186`, `chr.c:3437`, `explosion.c:874`, `propobj.c:7570`"* | **WRONG BOTH WAYS — MINE, and I wrote it.** `explosion.c:1486` (SMOKE) is a fifth scissor site and is absent. `chr.c:186` is `ge_chr_dbg_vis_breakdown`, a read-only debug counter that sets no scissor. And two more consumers exist that `286` never looked for: `propobj.c:14007` (a CULL, different symptom) and `chraction.c:10770` (AI/spawn logic, must never be switched). **A grep for the ONE helper, not for the RECTANGLE** — the same shape as `275` §1's grep-for-a-guard, fifth instance in five sessions. | `287` §1 |
| *"`285` §1.4: whether the LOOK/TURN rate has no timestep has never been checked"*, carried as a live candidate | **CANDIDATE RETRACTED, `[INFERRED]` — the TURN IS delta-scaled.** `bondview2.c:7366` integrates `speedtheta * g_GlobalTimerDelta * 3.5f`, and **every** term in all four branches of `bondviewCurrentPlayerUpdateSpeedTheta` (`:4573-4630`) carries the delta. **SOURCE READ, NOT A MEASUREMENT** — its free falsifier (a 360° spin timed at 60 vs 120) is unrun, and `bondviewApplyVertaTheta`/the pitch path are unread. Do not close it without the stopwatch. | `287` §2 |
| *"`285` §1.4, carried as `[INFERRED]` on a source read"* | **NOW `[MEASURED]` DEAD.** The free falsifier ran: 360° full-deflection spin, Dam, `SIMHZ=query` both arms, gates clean. **60 Hz `1.65 s` vs 120 Hz `1.80 s` = 1.09, and in the WRONG DIRECTION.** The failure mode was 2.0; the gap is ~11x the hand-timing scatter, so the test discriminates. Recorded as NOT frame-rate-proportional, **not** as "identical." | `287` 4D |
| *"`287` ARM 4E: `VSYNC=0` with a 120 cap will smear across the bins with no clean mode"* | **FALSE — MINE, MEASURED FALSE IN THE ARM I WROTE IT FOR.** `[MEASURED]` **99.83% in `1x`** over 21,736 intervals, against 4A's 99.90% at `vsync=1`. **"`vsync=0` was the judder" is NOT supported at this instrument's resolution.** And the arm exposed the instrument's own limit: **the `1x` bin is 4.17-12.5 ms, three times wide**, so it catches dropped and doubled frames but NOT jitter inside a frame period — `285` §3.3's critique one level finer. | `287` 4E |
| *"`RUN-SHEET-287` §3: 4A reads ≥95% `1x` and 4B ≥95% `2x`"* | **TRUE ON A 120 Hz PANEL ONLY — A HIDDEN CONSTANT.** The bins are `panel ÷ cap`; the §1 gate `simhz ... 0.500000` is `60 ÷ cap` and reads `1.000000` at `FPS=60`, which 4B printed. **The session lead also works on a 180 Hz panel**, where 4B lands in `3x` and a WORKING instrument fails its own stated prediction. | `287`, this session |
| *"`RUN-SHEET-287` §3: a stamp before the swap makes 4C read intervals near 0 ms"* | **CANNOT DISCRIMINATE — MINE, in the arm it was written for.** With `VSYNC=0 FPS=0` the swap does not block, so near-zero IS the correct reading. 4B settles it instead: a pre-swap stamp cannot produce 8.333 ms locked to the panel at 120 and 16.667 at 60. **Strike the row.** | `287` 4B/4C |
| *"the front-end menu text fault is `GETV_WIDESCREEN` or the window size"* | **BOTH WRONG — MINE, and the arms that "cleared" it were a DIAGONAL, not a 2x2.** M1 and M2 moved both knobs at once and neither ran the cell the report came from. **The variable is `ge_offset_x()`: fault iff non-zero**, confirmed by M3 at the same content scale. Two clean results were nearly read as "it went away." Sixth instance of `275` §1's shape. | `287` M3 |
| *"`RUN-SHEET-288` §3: `jdm > 20%` on the uncapped negative control"* | **FALSE — MINE, MEASURED FALSE IN THE ARM I WROTE IT FOR.** `[MEASURED]` **14.5%**. It was calibrated off the offline harness's uncapped stream (40.9%), and **the synthetic ~0.25 ms stream is SCATTERIER than the real uncapped loop**, which is remarkably even (`sd` 0.059, `jd` 0.032 ms). `§2` warned in advance the harness could not prove the pacer behaves like a synthetic stream. **The DISCRIMINATION survives on the matched metric — V1 settled `jdm` 2.9-4.7% vs V2 14.1-14.5%, 3-5x. The THRESHOLD does not.** Two findings, not merged. | `288` V2 |
| *"`RUN-SHEET-288` §3: `jdp < 10%`, per window, on V1"* | **INCOMPLETE — MINE. NO BOOT EXCLUSION.** V1's boot window read **32.8%**. It is not a failure of the statistic: that window carries **nine hitch intervals in the OLD bins**, an independent signal corroborating it. **Restated: a jitter threshold is scored on SETTLED windows; the boot window is REPORTED, NEVER SCORED.** | `288` V1 |
| *"`RUN-SHEET-288` §8e: `left` and `right` both large and ROUGHLY EQUAL = the symmetric signature"* | **DID NOT FIRE (`right/left = 2.51`) AND THE COUNTER CANNOT TEST IT EITHER WAY — MINE.** The frustum is symmetric by construction and measured so (`c_screenleft=0.000`, `c_halfwidth=160.000`, byte-identical in both runs). A counter accumulated while the player walks and turns reflects **where they looked**, not the shape of the frustum. **A defect in the stated outcome, not a finding about the planes.** | `288` ARM 8b |
| *"`GETV_CULLWHY`'s six counters are one accounting"* | **FALSE. `room` IS ON A DIFFERENT DENOMINATOR AND THE REPORT PRINTS THEM ON ONE LINE.** `propobj.c:14081` loops the prop's room list; `:14085` counts **once per UNRENDERED ENTRY** and continues, while every other counter is reached at most once per call after the `break`. **`room=1,134,409` is ENTRIES, NOT PROPS.** Also: the plane counters **multi-count** (`:14130`), and with `PROPCULLBOX` on the planes are **unreachable** (`:14126`'s `else`). **Reading a counter without reading the loop it sits in** — `275` §1 one level up. | `288` §6 |
| *"the 468 uncommitted decomp lines are undocumented work and CONTAMINATE the `288` binary"* | **FALSE — MINE, and I raised `274` §7's gate on it BEFORE reading the diffs.** They are this project's own `GETV_*` instrument history from `253`-`277`, carrying their own comments. **The binary is not contaminated by anything unknown and NO scope limit is owed on any arm.** The commit is still owed — for the OPPOSITE reason, see OWNER ACTION. | `288`, reading the diff |
| *"`Close GoldenEye VR.bat` being broken bugchecks the machine — fix it before the arms"* | **OVERSTATED — MINE, asserted before reading the script.** `close-gevr.ps1` targets **`GoldenRecomp.exe`**, the recomp build, not `goldeneye.exe`. Its own header says the 0x139s were GoldenRecomp in a VR session inside `nvwgf2umx.dll` and **never under `-NoXr`**; stereo has not been started in the native port. **Six arms closed cleanly today via `SDL_QUIT -> game_exit()`. It blocks nothing.** Copying it into `GoldenEyeVR\` would be WRONG — it would find no process and print "nothing to close" while the game ran on. | `288`, reading the script |
| *"`GETV_SLOTFREE = 0` in the per-user cfg is BLOCKING"* (carried from `287`) | **NOT ON THIS LOGIN.** `[MEASURED]` the `<USER>` login's `%APPDATA%` cfg contains **no SLOTFREE line at all**. **The standing rule is NOT retired** — §0: the cfg is per-user and the same human runs under different logins. `GETV_SLOTFREE=1` stays in every block; all six `288` arms printed `resolved to 1 (env=1)`. | `288` |
| *"`287` §2: mouse and pad are the SAME PATH, so `285` §2's mouse-vs-pad question needs no arm"* | **FALSE, AND IT COST FIVE SESSIONS.** `[REPORTED]` by the session lead: the fault is **mouse-only and the controller does not do it.** They share a **SINK** (`out->rx`), not a **PATH**: `port_input.c` gives the mouse a per-frame accumulator with no timestep, a backlog cap expressed in FRAMES, a 20% deadzone **FLOOR** applied to the mouse only, and a map that saturates at 21 counts — **the pad touches none of them.** **A SOURCE READ CANCELLED AN ARM, AND IT WAS THE ARM THAT MATTERED.** `275` §1's family, sixth instance. | `289` §6, the session lead |
| *"`dist=0`: the `32000` radius is DEAD BY MEASUREMENT"* (`288` ARM 8/8b, `289` R1) | **THE VERDICT SURVIVES, THE REASONING DOES NOT — MINE.** `[MEASURED]` `dist=17,124` in `289` R2. The radius sits DOWNSTREAM of the room test, which rejects **92.5%** of every call, so the far props never arrived. **It removes nothing in the shipping config and is not the mechanism — but it is NOT inert.** **STANDING RULE: a zero downstream of a test that rejects most of its input is a MASKED ZERO, not an exoneration.** `275` §1 one level over, and the same shape as `288` §6 reading `room` without reading its loop. | `289` R2 |
| *"`288` §5.2 / §8e: the five view planes are measured and not incriminating"* | **TRUE BUT NOT ABOUT THE SHIPPING PICTURE — MINE.** Every per-plane number came from ARM 8b, which ran `GETV_PROPCULLBOX=0`. **`[MEASURED]` in `289` R1 at the shipping default: `view=0` and all five planes `0`, because the plane path is UNREACHABLE when the box knob is on** (`288` §6 defect 3, now confirmed by a balancing sum-check). **In the picture the session lead actually looks at, the five view planes remove ZERO props.** | `289` R1 |
| *"`RUN-SHEET-289` §6 outcome 7: `box`, `view` and `drawn` will ALL RISE in R2"* | **PARTLY FALSE — MINE, in the arm I wrote it for.** `[MEASURED]` `box` 45,556 -> **42,409, essentially flat**, while `view` went 0 -> 436,784 and `drawn` 37,911 -> 255,863. The newly-arriving props have **no room bbox** (their rooms are not rendered), so they take the plain-view path rather than the box. **Right direction, wrong counter.** | `289` R2 |
| *"`RUN-SHEET-276`: the tank turret must not swing 1.5x faster at 90 Hz"* | **UNMEASURABLE AT THAT SITE.** The turret's real rotation is `g_TankTurretAngle += g_TankTurretTurn` at `bondview2.c:7236`, **outside every loop** and delta-scaled. The hoisted expression feeds `vv_theta` at `:7349` as a **camera lean**, `ftemp * 4.0f` — and the predicted defect is **2/3, not 3/2**, worth a few degrees. `[INFERRED]`, source read only. | `278` §6 |

## 5. DEAD THEORIES — DO NOT REOPEN WITHOUT NEW DATA
**THE TWO EYES DO NOT ADMIT DIFFERENT ROOMS, AND THE VIEWPORT RECTANGLE IS NOT READ BY ROOM
ADMISSION.** `[MEASURED]` `293` §1: `gSPSegment(SPSEGMENT_BG_VTX)` — written once per room by
`bgRenderRoomPrimary`/`Secondary` — is **EQUAL in both eyes in all eighteen `292` `dlgrab` dumps**,
across scenes from 2 to 23 rooms and across S2/S2b/S2c/S2d/S2e; `BG_DL` is 1/1 everywhere; and the
per-room `SETSCISSOR` lists pair one for one, 17 with 17. **`bgDetermineVisibleRooms`, the portal
traversal and `bgIsRoomOnScreen` are exonerated by measurement.** `278` §3's *"do not reopen room
ADMISSION"* held one question over. **`292` §5a's *"whatever makes a half-width viewport admit a
different room set is the next question"* is RETRACTED — it admits the same room set.** The
instrument is `getv/tools/dlgrab_eyecensus.py` and it has its own falsifier (`--selftest`).
**The black faces are NOT:** missing/unextracted assets (`0 MISSING`) · texture
bind misses (`miss=0`) · **degenerate 1x1 textures — those are RETAIL**, the ROM's
own `imagelist.u.csv` lists 1514/1604/1608/1917 as genuinely 12-byte images, and
`CheadbrosnanZ` binds 1608 seven times and renders perfectly · CI/TLUT
(`ci_decodes=0`). **`263` §5.**
**The 90 Hz artifact is NOT:** vsync (present at vsync 0 AND 1, absent at 60/vsync 0) ·
the display list (`GETV_DLCENSUS`, 48 blocks: **identical 34-opcode vocabulary at 60 and 90**,
nothing unique to either) · a census-visible proportion change (**two runs at the SAME rate
differ 25-56% on `TRI1`/`TEXRECT` — averaged proportions are NOISE at this repro and must not
be cited**). **`268` §5.**
**The `GETV_MENU` audio silence is NOT:** the SDL device · the queue accounting or the
synthetic clock · the buffer size · folder-specific (three folders, all silent). The mixer
RUNS and SAVES throughout and emits digital zero — `req=[m2,s110]`, the game asked for 110
sound effects. **It was a volume of zero applied at the source.** `269` §6.
**`GETV_GPUTIME=1` UNDER A FRAME CAP CANNOT ANSWER THE GPU QUESTION — AND IT NOW SAYS SO ITSELF.**
Nine arms, three caps, two levels, two resolutions: capped it prints the period every time,
**including at 320x240 with one sixteenth of the pixels.** **THE BRACKET IS NOT THE FAULT — that was
retracted in `273` §4.1 after the move was built and changed nothing.** The GPU waits inside the
query while the pacer sleeps. **RUN IT WITH `GETV_FPS=0` AND IT WORKS**: 0.832 ms Cradle vs 0.334 ms
Facility. A capped run now prints `CONTAMINATED` and withholds its verdict.
**`GETV_REALCLOCK` IS NOT THE 90 Hz ANSWER — AND ITS BANNER STILL SAYS `REAL host timebase`.**
Three arms, one build, all valid: 90 Hz synthetic ran `speedgraph 90/s` (the 1.500x), 90 Hz with
the real clock ran **60 fps**, and the 60 Hz control ran 60. **`waitForNextFrame` blocks a whole
real field unless `GETV_FPS=0`** (`frametiming.c:322-343`, `port_os.c:221`), so the knob
silently substitutes a 60 Hz run. **Do not reopen it as a present-path timebase without an
uncapped path that does not lock up.** `274` §3.
**THE FRACTIONAL DIVIDER (`274` §5's shape 2) IS NOT AN UNTRIED OPTION — IT IS `268`, THE SAME
LINES.** `frametiming.c:88-94` already accumulates skipped fields into `ge_sim_pending_fields` and
hands them over on the tick frame; *"tick only when a whole field has accumulated, delta always 1"*
is a verbatim description of `GETV_SIMDIV`. **It has been built, shipped, run at 90 Hz and rejected
by the owner** — *"Yeah. That fixed it"*, about turning it OFF. **Ruled out from source, not by
analogy. Do not re-propose it as a new shape.** `275` §3.
**THE WIDESCREEN HOLES ARE NOT THE ROOM-VISIBILITY PASS.** `[MEASURED]` W1 vs W2, 200 stationary
frames each, same spot and facing, the artifact on screen in the 16:9 arm: `curroom=9 drawn=2
rooms(front=1 straddle=1 BEHIND=0) vtx(total=609 front=244 straddle=365)` — **byte-identical**.
A widened view would admit MORE rooms. `bgDetermineVisibleRooms()` also rebuilds its clip box
every frame (`bg.c:5638`, `:6198`), so a stale box was never available either. **Do not reopen
room ADMISSION. The per-room clip RECTANGLE (`bg.c:622-677`) is a DIFFERENT question and is
still open.** `278` §3, §4.
**THE TANK BEING UNENTERABLE IS NOT THE DIFFICULTY MASK.** `prop.c:1898` does carry a
per-difficulty "Don't Load" mask and a `GETV_STAGE` boot silently runs AGENT (`lv.c:1979`) — but a
masked object is **not loaded at all**, and `[REPORTED]` the tank is visible on every difficulty.
**And it is not the button mapping**: the pad's own B works elsewhere in the same session. `278` §5.
**The cast crash was NOT:** slot COUNT (raised 10->32, crash did not move) or slot
CAPACITY (`maxcap=420` vs `required=155`). **It was a leak.** `262` §5.
**THE VANISHING PROPS ARE NOT:** the per-room rectangle (`288` ARM 7, and `box=0` in 8b with the
symptom still reproducing) · **the room-visibility test `getROOMID_isRendered` at `posIsOnScreen`'s
room gate** (`289` R2 — the knob TOOK and the props still vanished) · the `32000` radius, which
removes **zero** props in the shipping configuration across three runs. **AND THE FIVE VIEW PLANES
REMOVE ZERO PROPS IN THE SHIPPING CONFIGURATION** — they are unreachable with `GETV_PROPCULLBOX` on.
**WHAT IS LEFT IS `fog` (12,257) AND `occl` (2,241), NEITHER EVER TESTED — and the load-bearing
claim underneath all of it is `288`'s SOURCE READ that *"`posIsOnScreen` is the ONLY place that
decides a prop is not drawn"*, which is not a measurement.** **AND `fog=12,257` IS BYTE-IDENTICAL
ACROSS TWO SESSIONS AND TWO ROUTES** while every other counter moved, so a large part of these
cumulative counts is deterministic boot/load and the report has **no windowing at all**. **The next
instrument is WINDOWING, not another knob.** `289` §4.
**THE SMOOTHNESS COMPLAINT IS NOT IN THE PRESENTED-FRAME PATH AT ALL.** Not `vsync` (`287` 4E,
`288` J1/J2, two resolutions) · not the frame cap · not the pacer's sleep booking (`287` §4:
measured, and vsync absorbs it) · **not `GETV_SIMHZ` (`289` S1/S2 — cleared on the NUMBER, `jdp`
8.54% vs 8.05%, AND on the WEAR, *"no waiting feel"* on both)**. **Three instruments and five
sessions came back clean because the fault is MOUSE CONTROL, not rendering** — `289` §6, and it is
`258` STAGE 7. **Do not re-open any of them as the smoothness carrier.**
**The black surfaces are NOT the COLOUR COMBINER:** one combiner value across all 768
1x1 draws, non-black inputs on the fault, and a black-texel/black-prim draw that renders
correctly. **`265` §2. Do not reopen without a draw the probe did not see.**

## 6. TRAPS THAT COST A DAY
- **►►►►►►►► A POWERSHELL `Get-Content` / `-replace` / `Set-Content` ROUND-TRIP CANNOT EDIT A
  TRACKED SOURCE FILE HERE -- IT REWRITES EVERY LINE ENDING AND RE-ENCODES EVERY BYTE IT DOES NOT
  UNDERSTAND. `308` §1.1. ◄◄◄◄◄◄◄◄** `[MEASURED]`: `getv/tools/stereo_disparity.py` is **LF-only,
  UTF-8, no BOM**, and carries `►` and `§` in **ten COMMENT lines**. A round-trip would have
  produced **293 spurious CRLF changes and ten mangled comments** in the diff of a 4-line edit --
  on the very file whose printing correctness `306` spent a session fixing. **`H16` one level over:
  that rule is about what a TOOL writes; this is about what the SHELL writes to the tool.**
  **THE DEFENCE: hand the splice to `py` and do it in BYTES** -- anchor on the exact block, refuse
  unless it matches exactly once, refuse if the CRLF count would change, and score the edit with
  `git diff --stat` on ONE path. `308` §5.2 is the block; it read `10 insertions / 4 deletions`,
  `CRLF=0`, and refuses on a second run.
- **►►►►►► A BLOCK THAT WAS IMPROVISED LIVE AND PRODUCED A FILE LATER GATES DEPEND ON IS NOT
  FILED BY THE FILE EXISTING. `308` §0, §1.3. ◄◄◄◄◄◄** `RUN-SHEET-308` §1.2 sent the next session to
  *"`307` §2c's scoring block"* for the all-16 re-score. **`307` §2c scores ONE grab per arm and
  carries placeholders; the all-16 block lives only in a chat transcript.** The corpus was on disk,
  the falsifier was pre-registered, and **the instrument that reads them was not.** The
  reconstruction was provable only because the output file records its own `ARM ... grabs=N preds=N
  dls=N` headers. **THE RULE: if a block is written at the keyboard rather than in the sheet, it
  goes into the sheet before the session ends -- and a sheet that CITES a block by section number
  must be checked against that section, which costs one `grep`.**
- **►►►►►►►► A PREDICTION CAN BE CORRECT AND UNMEASURABLE, AND THE INSTRUMENT PRINTS THE NUMBER
  THAT SAYS SO BEFORE ANYTHING IS CORRELATED. `307` §1. ◄◄◄◄◄◄◄◄** `[MEASURED]`: `S3` predicted
  **−7,024 px** on a **912 px** eye at `D=47.47`, on all seven grabs and across all 109 probe
  windows. **Disparity goes as 1/D; `separation=500` was chosen absurd and the venue was chosen
  near, and nobody multiplied them.** The bound is the IMAGE EDGE, not `--search`. **READ THE
  GRABBED FRAME'S OWN `PREDICTION: disparity = … px` LINE FIRST AND REFUSE ANYTHING OUTSIDE THE
  REACHABLE RANGE.** `H18`.
- **►►►►►► A COUNTER THAT MEASURES "DID NOTHING" MUST BE ABLE TO SEE "HAD NOTHING TO DO". `307`
  §4. ◄◄◄◄◄◄** `ZERO-REBUILD FRAMES` read **2,220 of 7,636** on a healthy arm — contiguous frames
  1810–4029, **every one `zsnap=0`** because the owner stood still facing a wall with nothing on
  screen, `eyes-rebuilt=1` and `skipped=0` throughout. **The gate says "it must be 0" and
  `pass-never-ran` is 0, so the gate as written FAILS A HEALTHY ARM.** `H2`'s own instrument with
  an `H3` defect: the number is right and the LINE invites the misread. `H17`.
- **►►►► A PLACEHOLDER IS NOT A COMMAND, AND IN POWERSHELL IT IS A PARSE ERROR THAT STOPS THE
  BLOCK. `307` §0.** `--predicted-frac <the number from the log>` returned *"The '<' operator is
  reserved for future use."* **`<` is RESERVED.** `00-STATE` §7a says every command is supplied
  complete and `296` §11 says *"the same block with"* is not a command — **this is the same rule
  with angle brackets.** Derive the value inside the block, or mark the substitution and say out
  loud that it must be made before the block runs.
- **►►►►►►►► AN INSTRUMENT'S OUTPUT ENCODING IS PART OF ITS CONTRACT, AND ON WINDOWS IT CHANGES
  WITH REDIRECTION — SO THE TOOL DIES AT THE FINDING, BECAUSE THAT IS WHERE THE ARROWS ARE.
  `306` §1. ◄◄◄◄◄◄◄◄** `[MEASURED]`: `UnicodeEncodeError: 'charmap' codec` on `►` at
  `dlgrab_dlorder.py:93` — **the `PERMUTATION` verdict line** — on `dlgrab_2928`, the first permuted
  frame in the corpus; 42 of 265 dumps classified, no summary, **no reading at all.** The same
  two-character shape sits in `--selftest`'s check `B` header and in **`stereo_disparity.py:261`,
  which is the `H1` PEG ALARM — the alarm `H1` was opened to make fire is a line that could not
  print.** **THE RULE: instrument OUTPUT is ASCII. Docs may have arrows; tools may not.** And when
  fixing one, **do not add a check** — a gate's expected TEXT (`7 checks, 0 failed`) is part of the
  gate.
- **►►►►►► A CLAIM THAT WORK IS OWED IS A CLAIM ABOUT THE FILESYSTEM **AND ABOUT GIT**, AND BOTH
  ARE ONE COMMAND AWAY. `306` §0/§2.** `305` §2a caught `304` §3/§4 sitting on disk; `306` caught
  **`P1`** sitting on disk **and `305`'s two commits already in**, the second of which a prompt
  opened by denying. **`ls grabs_*`, `ls run_*.log`, `git log --oneline -3` — three bridge-safe
  reads, before any sentence that says something is still owed.**
- **►►►► AN OBJECTION THAT WAS CORRECT CAN LAPSE, AND NOTHING RE-RANKS IT AUTOMATICALLY. `306` §4,
  GROUP `V`.** *"A disparity measured on an eye with no world in it is a number about nothing"* was
  right for six sessions and is why `S3` kept being deferred. **`303` §2 filled eye 1 on
  2026-09-03 and nothing on the board moved.** `S3` is `258` STAGE 6's exit gate, it needs no
  headset, and it has now not run for seven sessions. **When a fix lands, re-read what it
  UNBLOCKED, not only what it closed.**
- **►►►►►►►► A SET COMPARISON CANNOT SEE A PERMUTATION, AND `only in eye0 = 0` IS A SET
  COMPARISON. `305` §1.3. ◄◄◄◄◄◄◄◄** `dlgrab_eyecensus.py:96-97` is
  `set(a['calls']) - set(b['calls'])`. **A frame whose two eyes call the same display lists in a
  different ORDER reads PERFECT**, and four documents quoted exactly such a frame as proof the
  fault was downstream. **Before believing a zero, read the OPERATOR that produced it, not just
  the number** -- `299` §8.1's shape moved from a brace to a set. `getv/tools/dlgrab_dlorder.py`
  is the ordered read; run it beside the census whenever a picture and a census disagree.
- **►►►►►► A DEFECT CAN BE REAL, STRUCTURAL, DATED AND STILL DRAW NOTHING -- AND THE FALSIFIER IS
  THE ONLY THING THAT SAYS SO. `305` §1.4. ◄◄◄◄◄◄** The eight-call rotation by three is on two
  binaries, two address spaces and the same ordinal span, it predates `303`, and it was one
  keystroke from being filed as `4676`'s cause. **`stereo_eyediff.py` on the two admissible frames
  that carry it reads `total 0 px  blobs 0`.** ZERO. **`279` §7 is not only for arms: point a
  NEW EXPLANATION at the frames it should be boring on before it is written down**, and the count
  of filed fixes that were wrong stays at five because of it.
- **►►►► TWO INDEPENDENT FRAME COUNTERS PRINT TWO DIFFERENT NUMBERS FOR ONE FRAME, AND ONLY ONE
  OF THEM IS THE GAME'S. `305` §2.** Every log pairs `[getv][dlgrab] frame N` with
  `[getv][shot] frame N+1`, 14 of 14. **The picture and the list ARE the same frame** --
  `port_render.c:748-759` sets the request inside that frame's render and `gfx_opengl.c:1495-1520`
  consumes it in that frame's `end_frame` -- and `fno` at `:1497` is a PRIVATE counter with a
  different origin. **This was drafted as a retraction of `303` §5's headline before the call was
  followed.** A CONSISTENT offset in every pair is a label mismatch; a real off-by-one is not
  consistent. **`RUN-SHEET-305` §3.**
- **►►►► LARGEST-BLOB CONCENTRATION PENALISES A FAULT THAT DRAWS MORE THAN ONE SLAB. `305` §1.5,
  `00-STATE` §4.** `4676` is 38% by largest blob and 73% by top three; the dead-eye frames are 5%
  and 14%. **The metric that separated `4676` from the polygon group is the only one that does.**
  Same family as `H8`: ask what a summary statistic throws away before ranking on it.
- **►► AND A RUN SHEET'S "STILL OWED" LIST IS A CLAIM ABOUT THE FILESYSTEM. `305` §2a.**
  `304` §3 and §4 were carried as outstanding in two documents while the logs, the grabs and the
  moved files were already on disk. **`ls grabs_*` and `ls run_*.log` before repeating an arm** --
  it costs one command and `304` §3 is an owner cycle.
- **►►►►►►►► A LUMINANCE METRIC CANNOT SEE A CHROMA-ONLY DIFFERENCE, AND A DEAD EYE CAN BE THE
  SAME BRIGHTNESS AS A LIVE ONE. `304` §1.2. ◄◄◄◄◄◄◄◄** `stereo_eyediff.py` differenced greyscale
  because `stereo_disparity.py` does, and a correlator is right to. **A DIFFER IS NOT A
  CORRELATOR.** `[MEASURED]`: a navy void against a brown building scored 1,329 px and passed as
  clean. **Before reusing a helper from a sibling instrument, ask what that instrument was
  MEASURING, not just what it READS.**
- **►►►► A CALIBRATION ON THE FRAMES YOU ALREADY UNDERSTAND IS A HYPOTHESIS. `304` §1.3.**
  Nine frames put the worst clean frame 171 px under the threshold and read as comfortable; 256
  frames put it 785 px under **and found two misses on the way.** `279` §7's rule for detectors --
  run it on the frame you expect to be BORING -- **and the corpus is where the boring frames are.**
- **►►►►►► `grabs_pre_298cull` IS 109 BMPs WITH NO ADMISSIBLE PROVENANCE, AND IT NOW BLOCKS A REAL
  QUESTION. `304` §2. ◄◄◄◄◄◄** `279` §2 has said since `278` that a log's own `dlgrab`
  announcements are the only admissible provenance for a dump. **This is the first time the rule
  has blocked a question rather than corrected a label:** the five pre-`303` frames carrying the
  one-eye polygon's signature are announced by no log (three), by five logs (one), and by a
  falsifier arm that is SUPPOSED to diverge (one). **`N2`'s `GETV_ARM` prevents future collisions
  and does nothing for the 109 files already there. When the archive cannot answer, take a RUN.**
- **►►►►►►►► A CUMULATIVE COUNTER OVER A RUN THAT CONTAINS TWO SCENES IS A WEIGHTED AVERAGE OF
  THEM, AND ITS PERCENTAGE IS COMPARABLE TO NOTHING. `303` §3.1. ◄◄◄◄◄◄◄◄**
  `[getv][far]` prints a running total. `[MEASURED]`: in every `302`/`303` far run the road reads
  **1.2-5.9% `beyond_far`** and the cast roll **40-71%**, a 15x step, so `302` §4's headline
  `13.2%` is neither figure. **Difference consecutive samples before quoting a rate**, and state
  which scene the window is in. Same family as `299` §4's reset-every-tick census one level up:
  ask what a number is accumulated OVER before believing it.
- **►►►►►► A VENUE THAT MAXIMISES THE COUNTER CAN MINIMISE THE PICTURE, AND THAT IS STILL `279`
  §7. `303` §3.2. ◄◄◄◄◄◄** The introduction loop was chosen because the fault "showed plainly"
  there and because a fixed camera removes the where-were-you-standing objection. It is **67%
  beyond-far AND FLAT COLOUR** -- two enormous unlit quads and the cast text -- so the far clamp
  fires 45,000/Mvtx into a picture with nothing in it to z-fight. **Before an A/B, ask BOTH
  questions: is the mechanism loud here, and is there anything here to SEE it in?** The owner was
  judging the road, where the same knob fires 20-40x less.
- **►►►► A GRAB FOLDER NAMED FOR AN ARM CAN CONTAIN ANOTHER ARM'S FILES, BECAUSE `GETV_ARM` NAMES
  THE RUN'S OWN GRABS AND NOT THE STRAYS ALREADY IN THE DIRECTORY. `303` §7.**
  `grabs_303_V1\` holds four `dlgrab_D3_*` files -- `302` §4's, left loose in `build-windows` and
  swept up by V1's closing `Move-Item`. **`N2` closed the collision case and not this one.** The
  defence is the glob: census `dlgrab_<ARM>_*`, never `dlgrab_*`, and count the folder before the
  run as every block already does.
- **►► A ZERO-SEPARATION STEREO RUN CARRIES ITS OWN CONTROL, AND FOR SIX SESSIONS NOBODY USED IT.**
  `303` §6. At `GETV_STEREO_OFFSET=0` the halves must be identical apart from the viewmodel, so any
  surviving difference IS a fault -- no reference frame, no normalisation, no memory of what the
  picture used to look like. **`getv/tools/stereo_eyediff.py`.** It cannot see flicker (`268` §4)
  and a pass is NOT "the picture is right": both eyes can be wrong together.
- **►► AND THE CENSUS AND THE PIXELS ANSWER DIFFERENT QUESTIONS -- `H8` ONE LEVEL OVER. `303` §5.**
  `dlgrab_eyecensus.py` reads `MODEL_MTX 39/39`, `only in eye0 = 0`, `only in eye1 = 0` on the
  exact frames where one eye draws a polygon the other does not. **The census counts what was
  SUBMITTED; it cannot see what was DRAWN.** A balanced census is not an exoneration of the frame.
- **►►►►►►►► A HOLE'S FILED FIX IS A DIAGNOSIS, NOT A PATCH. TWO OF SIX WERE WRONG. `301` §0.
  ◄◄◄◄◄◄◄◄** `PRIORITY-BOARD-299` `H1` said "clamp `hi`/`lo` to `±search`" — **that reads past the
  end of the row**, because `hi` is clipped by the IMAGE EDGE, not by `search`. `H3` said "print
  `ge_props_zsnap_n` beside `list=`" — **that prints `-1` on every frame**, because
  `gePropsRestoreTickZDepth()` nulls it at `lv.c:1135` and the report runs at `lv.c:1151`. Both
  took under a minute to catch **by reproducing the arithmetic and reading the call order instead
  of the declaration.** The `H3` shape is the worse one: the wrong fix replaces a misleading
  number with a CONSTANT, and there is nothing to notice. **Measure before you patch, even when
  the board already told you the answer — especially then.**
- **►► THE PORT BATCH AND THE GAME BATCH HAVE DIFFERENT INCLUDE SETS, AND USING THE WRONG ONE
  LOOKS LIKE A BROKEN FILE.** `301` §7a. `build_windows.ps1`'s `$portFlags` deliberately does NOT
  put the decomp's `include/` on the path — the decomp's `stdio`/`stdarg` shadows would beat the
  system headers, and the script says so at length. Compiling a port file with the GAME flags
  gives `unknown type name 'ptrdiff_t'`, which reads like the file is broken rather than like the
  flags are wrong. **`port_syntax_gate.sh` uses `$portFlags`; if that variable changes, the gate
  changes with it.**
- **►► A KNOB'S BANNER MAY BE ANOTHER KNOB'S BANNER. `301` §6.** `GETV_NEARCLAMP` looked bannered
  to a tree-wide grep: its name appears only inside `ge_depthclamp.c`'s message for
  `GETV_DEPTHCLAMP`, while its own read is in `gfx_pc.c`. **The generous version of the instrument
  agreed with the wrong answer.** `knob_banner_survey.py` requires the echo to be in the file that
  READS the knob. **82% of the 397 knobs are still silent.**
- **►► `mv` CANNOT REPLACE A FILE ON THE BRIDGE MOUNT — DELETES ARE REFUSED, WRITES ARE NOT.**
  `301` §8. `tools/fetch-thirdparty.sh regen` fails here with *"unable to remove target: Operation
  not permitted"* and **correctly refuses rather than reporting a write it did not make** (its own
  `271` guard). The script is right; do the regen on a local filesystem, or make the final replace
  an in-place copy so every one of its size guards and its `verify` still run. **`verify` is what
  returns `15/15`, and it is the thing to trust.**
- **►►►►►►►► A GIT-BASH PATH IN A POWERSHELL BLOCK FAILS **SILENTLY INTO THE WRONG REPO**.
  `299`, `RUN-SHEET-300` §7. ◄◄◄◄◄◄◄◄** `/f/Projects/...` is RELATIVE in PowerShell and resolves to
  `F:\f\Projects\...`, so `Set-Location` errors — **and every following line still runs, in
  whatever directory the prompt was already in, against whatever repo encloses it.** `[MEASURED]`
  2026-09-03: a decomp commit block ran against `goldeneye-native` and its closing
  `git log --oneline -1` printed **goldeneye-native's** HEAD, which is indistinguishable from the
  decomp commit having quietly not happened. Nothing was staged only because the pathspec and the
  message file were both wrong too. **EVERY COMMIT BLOCK NOW OPENS WITH
  `git rev-parse --show-toplevel`**, and a block that mixes the two shells says which line needs
  which shell. This project uses BOTH — `fetch-thirdparty.sh` needs git bash, everything else is
  PowerShell — so "which shell is this block" is never obvious from the block itself.
- **►►►►►►►► A COUNTER OUTSIDE THE `if` THAT THE KNOB CONTROLS CANNOT MEASURE THE KNOB.
  `299` §8.1. ◄◄◄◄◄◄◄◄** `ge_far.tri_all_near` sits **above** `if (nc)` in `gfx_pc.c`, so it counts
  the same whether the clamp runs or not. `298` read `50 -> 548` across two arms as the clamp's
  price; `299`'s three arms read **12 / 150 / 51** with the knob ON / OFF / ON. **Before quoting a
  counter as a knob's cost, find the brace it lives inside.** Same family as `288` §6's `room`.
- **►►►►►► A REPORT WHOSE COUNTERS ARE RESET EVERY TICK IS A SPOT CHECK, NOT A CENSUS -- AND ITS
  CADENCE IS THE DIFFERENCE. `299` §4, §8.3. ◄◄◄◄◄◄** `GETV_STEREO_REBUILD_REPORT=600` prints ONE
  frame in 600 and looks green on every one of them; **`=1` prints every frame and finds 372 frames
  per run where the second eye is rebuilt with nothing.** **The instrument was already capable of
  being right and the cadence was the whole defect.** Ask what a report's numbers are accumulated
  over before believing the interval it prints on.
- **►►►► TWO COUNTERS PRINTED ON ONE LINE ARE NOT NECESSARILY FROM THE SAME MOMENT. `299` §8.3.**
  `list=` is read when the line prints; `chr`/`obj`/`skipped` are from the last tick. 169 frames per
  run print `list=1 chr=1 skipped=1`. **A "balancing sum" across two capture times is not a sum.**
- **►►►► A RE-RUN TO GET THE GRABS STILL OVERWRITES THE LOG, AND KNOWING THE RULE DOES NOT STOP IT.
  `299` §8.5.** `298` §6 wrote the rule, `RUN-SHEET-299` §1.4 restated it, and the N2 arm was still
  re-run under its own name the next day. **Nothing was lost -- but the file mtimes now read
  N1, N3, N2, which is not the order the arms were run.** If a block's log name is fixed, the block
  itself should carry the new name; a rule in prose above the block is not enough.
- **►►►►►►►► A CONFIG FILE CAN BEAT THE ENVIRONMENT EVEN WHERE THE FILE'S OWN HEADER PROMISES IT
  CANNOT. CHECK THE BANNER, NOT THE `$env:` LINE. `298` §5. ◄◄◄◄◄◄◄◄** `ge_config.c` documents
  **CLI > environment > file > default** at `:15-19` and `:1067` and implements it through
  `put()` -> `setenv(..., over)`. **`key_filtering()` bypasses that and assigns the global
  directly**, so `GETV_FILTERING` is the one knob the file overrides. **A knob whose value is not
  echoed by a banner is a knob you have not set.** Same shape as `GETV_SLOTFREE` (`262` §2), and it
  cost two owner cycles today.
- **►►►► A ZERO IS ONLY A RESULT IF ITS UPSTREAM COUNTER IS LARGE — CHECK THE CONDITION, NOT JUST
  THE OUTCOME. `298` §4.2.** `GETV_NEARCLAMP=0` reported `clamped=0`; that means nothing on its own,
  because the same zero is produced by never crossing the near plane. **`straddle=18439` in the same
  census is what makes it an arm.** `289` R2's masked-zero rule, applied forwards for once instead
  of in a retraction.
- **►►►► A CORRELATOR'S ANSWER THAT MOVES WITH ITS OWN SEARCH WIDTH IS THE SEARCH WIDTH.
  `298` §2.1.** `stereo_disparity.py`'s `dx` read `+199 / +229 / -499 / -799` at `--search`
  `200 / 300 / 500 / 800` on the same frame while `mad_best` "improved" to 0.787 as the overlap
  vanished. **Its built-in peg detector tests `abs(dx) >= search` and NEVER FIRES, because
  `measure()`'s `lo`/`hi` clipping (`:90-91`) makes the reachable bound `search - 1`.** Sweep the
  free parameter; an answer that does not move is a measurement.
- **►►►► `dlgrab_NNNN` IS NAMED BY FRAME NUMBER, SO TWO ARMS RUN FROM THE SAME SPOT OVERWRITE EACH
  OTHER SILENTLY — AND A RE-RUN OVERWRITES ITS OWN LOG. `298` §6.** A re-run destroyed
  `run_297_R2_rebuild_on.log`, and this file makes a log's own `dlgrab` announcements the only
  admissible provenance for a dump. **Every arm ends by moving its grabs into `grabs_<session>_<ARM>/`,
  and a re-run of an arm gets a NEW log name.**
- **►►►► A FALSIFIER'S DOCUMENTED SIDE EFFECT IS NOT A NEW DEFECT — RE-SHOOT IT AT SHIPPING BEFORE
  FILING IT. `298` §3.** The wall cut was first grabbed under `GETV_ROOMSCISSOR=0`, whose own
  comment predicts *"walls through walls, rooms visible where they should not be."* **Arm D existed
  only to re-run that view at shipping defaults, verified by the ABSENCE of both banners**, and it
  is the only reason the symptom is in §3 rather than in this list as a misread.
- **►►►►►►►► A CHECK FOR WHAT WAS **LOST** CANNOT FIND WHAT WAS **DUPLICATED**. `297` §11.3. ◄◄◄◄◄◄◄◄**
  ARM 3's extraction was verified by a normalised, comment-stripped, whole-file multiset comparison
  against the parent commit. It reported **one** code line lost — the intended one — and the
  extraction was declared clean. **The bug was an ADDED line**: a second `if (headSwitchVisible)`
  at `chr.c:3305`, sitting in the additions column, unread. **Diff BOTH directions, and read added
  control-flow lines with the same suspicion as deleted ones.** The build runs `-w`, so
  `-Wdangling-else` and `-Wmisleading-indentation` will never do it for you.
- **►►►► `grep -n "EXCEPTION" <run log>` BEFORE ANYTHING ELSE ON A CRASH.** The port prints
  `===== EXCEPTION 0xc0000005 =====`, `fault addr:` and `FAULT PC:`. **Three sessions resolved
  backtraces by hand without ever grepping for it.** `fault addr` decides the shape of the fix:
  small is NULL-plus-offset, large and unaligned is a WILD pointer and **a NULL guard is
  worthless** (`297` §11.1, §12).
- **►►►► NEVER ASSUME A LOAD BASE — DERIVE IT FROM CALL-RETURN SITES.** Back-solving the base from
  an assumed leaf is circular and cost three rounds and two impossible fixes. Every non-leaf frame
  is the byte after a `call`; that constraint is base-independent and pins the base uniquely.
  **A leaf landing mid-instruction is proof the base is wrong**, not something exotic (`297` §11.1).
- **►►►► A TYPE TAG AND ITS UNION MEMBER MUST BE READ AS ONE FACT.** `vtxstore.c:161` filters
  `type == 1` (`PROP_TYPE_OBJ`) and reads `PropRecord`'s union as a `ChrRecord *`. It has crashed
  every build since long before ARM 3. **When a walker tests a raw integer instead of the
  `PROP_TYPE_*` name, check which member the body then uses** (`297` §12).
- **►►►► SAVE THE `.map` BESIDE EVERY BINARY YOU KEEP.** A rebuild overwrites `goldeneye.map` and
  strands every earlier backtrace. `build-windows/goldeneye_PARENT.map` and `goldeneye_ARM3.map`
  exist for this reason, next to `goldeneye_PARENT.exe` — **which is what proved the mine crash is
  pre-existing without a rebuild** (`297` §12).
- **►►►► A RUN-SHEET COMMAND BLOCK IS QUOTED, NEVER PARAPHRASED, AND A REVERT'S FILE LIST COMES
  FROM `git`.** Two wasted owner cycles on 2026-09-02: a §2 block rebuilt from `grep` hits dropped
  `Remove-Item Env:GETV_*` and named the wrong directory; and a revert list written from memory
  named three of ARM 3's **seven** files, so the un-reverted `lv.c` still called the reverted
  `chrprop.c` and the build died at LINK with four undefined references. **`sed -n` the whole fenced
  block; take file lists from `git show --stat --name-status <sha>`.**
- **►►►► `grep -c $'\r'` ANY `vendor/ge-decomp` FILE BEFORE YOU TOUCH IT. `297` §6. ◄◄◄◄**
  `HEAD` is LF and ~2,100 files in the working tree are CRLF, so **an honest 12-line change can
  arrive as a 1,056-line diff and be unreviewable.** `295` §6 predicted `chrprop.c` (4,502 of 4,502)
  because it needed that file. **`297` found `ge_port_decls.h` the same way — 523 of 535, and no
  document had named it, even though it is the FORCE-INCLUDED header every prototype goes in.**
  Both are converted. **The class is bigger than either instance: check the file, do not check the
  list of files someone else checked.** Convert in the same commit (`288a`'s precedent) and
  `git diff --stat <path>` before committing, every time.
- **►►►► A GATE WHOSE PASS CONDITION AND WHOSE "I CANNOT SEE ANYTHING" CONDITION PRINT THE SAME
  STRING IS NOT A GATE. `297` §0. ◄◄◄◄** `RUN-SHEET-295` §10.1 scores
  `CANNOT ANSWER — the two halves match no better shifted than unshifted` as the PASS for the
  zero-separation arm. **`[MEASURED]`: the mandated grab (`GETV_DLGRAB_AT=900`, ~5 s at `panel` on
  180 Hz) was a near-black level-load fade — texture energy 0.04 against 0.36-4.15 for every frame
  with a world in it — so the script refused for the WRONG REASON and the sheet read it as green.**
  `stereo_disparity.py` now measures content first and refuses a blank frame by name.
  **`279` §7, third instance: a null result from an instrument pointed at nothing is not a result.**
- **►► `Select-String -Encoding Byte` DOES NOT EXIST IN POWERSHELL 7.** It throws
  *"'Byte' is not a supported encoding name"*, and with `-ErrorAction SilentlyContinue` on the
  assignment **every probe then prints `MISSING` on a binary that contains all of them.** Read the
  bytes instead: `[System.IO.File]::ReadAllBytes()` + `[System.Text.Encoding]::Latin1` — Latin1 is
  the only decoder that maps all 256 byte values one-to-one. `RUN-SHEET-297` §3 has the block.
- **►► `stereo_disparity.py`'s `dx` PEGGED AT `±--search` IS THE CORRELATOR'S BOUNDARY, NOT A
  MEASUREMENT.** The match cost is not normalised for overlap width, so widening the search makes
  `mad_best` LOOK better while the overlap shrinks to nothing. **A pegged `dx` means the halves
  differ in CONTENT, not by a shift.** The script now says so on the line below `dx`.
- **►► THE HARNESS'S "BUILD'S OWN FLAGS" GATE MUST COPY ALL FOUR FLAG GROUPS, NOT JUST
  `$gameFlags`.** Dropping `$std` (`-std=gnu17`) makes GCC 15 default to gnu23, where
  `bondtypes.h:85`'s `typedef s32 bool;` is a hard error that poisons every file downstream;
  dropping `$permissive` leaves GCC 14+ default-errors that `-w` does **not** demote. It reported
  **7/7 FAIL on a tree the real build compiles clean.** Fixed; the gate now parses NINE files and
  is fatal on implicit declarations too.
- **►►►► A LOG'S OWN `dlgrab` ANNOUNCEMENTS ARE THE ONLY ADMISSIBLE PROVENANCE FOR A DUMP. ◄◄◄◄**
  `279` §2: **`278` §1 mislabelled SIX files as V1's on timestamp alone.** V1 produced THREE dumps
  (`2290/2849/3582`); `2356/2763/2915/3048/3667/3932/4292` are the widescreen-ON `D1` arm; and
  `1573/1676/1693/1714` are announced by **NO log at all**. Run
  **`grep -oh "dlgrab_[0-9]*\.txt" <log>` per arm, every time.** The BMP byte count narrows the
  window size; it does not name the arm. And the **all-black border says which arm it is**: `57 px`
  = 40 canvas rows = 4:3 play area stretched = widescreen ON; `171 px` = 120 rows = the game's own
  16:9 = V1. **Read the border before you read the picture.**
- **A DETECTOR TUNED ON THE POSITIVE FRAME PASSES ITS OWN CONTRACT UNTIL IT MEETS THE NEGATIVE
  ONE.** `279` §7: the edge finder's stated contract failed on the clean frame `2849`, and only
  because `2849` was actually run. **Rule `15` means running the instrument on a frame you expect
  to be BORING.**
- **`Z:` is a NAS.** Git refuses both repos until `safe.directory` is added.
  `COMMIT-NOW.cmd` pre-flights it. **`git status` TIMES OUT on the bridge.**
- **►►►► THERE IS A STALE `index.lock` IN THE DECOMP RIGHT NOW, DATED `2026-08-29 04:13`. ◄◄◄◄**
  `goldeneye-native\vendor\ge-decomp\.git\index.lock`, zero bytes, no git running. **The
  bridge cannot delete it** (the mount refuses to unlink — the same §6 behaviour that creates
  these), so it is a **main-PC** action and **any `git add` in the decomp fails until it goes.**
  Block: `RUN-SHEET-276.md` STEP A0. `[INFERRED]`, not established: a candidate for why the
  decomp's last commit is `2026-08-29` while work has landed there since.
- **►►►► `COMMIT-NOW.cmd` DOES **NOT** COVER `vendor\ge-decomp`. IT NEVER HAS. `276`. ◄◄◄◄**
  `[MEASURED]` from `commit-now.ps1` and `commit-session.ps1`: the script commits **three**
  repos — `GoldenEyeVR`, `GoldenEye64Recomp`, then `goldeneye-native` separately. `vendor/` is
  **gitignored by `goldeneye-native`** (`.gitignore:42`), so the decomp repo is invisible to all
  three passes. The `-decomp.txt` message files that exist were committed **by hand**. **A
  session whose whole change is in the decomp — like `276`'s clock — commits NOTHING if the
  owner only double-clicks `COMMIT-NOW.cmd`.** The block is in `RUN-SHEET-276.md` STEP A.
- **►►►► AND `git add -A` IN THE DECOMP WOULD SWEEP 2,106 CRLF-DIRTY FILES INTO YOUR COMMIT.**
  `[MEASURED]` 2026-08-30m: `HEAD` is LF throughout, the worktree has **2,106 files converted to
  CRLF** by something on the Windows side, and every one of them diffs as a whole file.
  **THIS HAS ALREADY HAPPENED ONCE AND IS IN THE HISTORY**: `7a4e7bfd`, whose subject is *"fix:
  three pointer-size errors the -w build never warned about"*, is **736 files and 601,764
  insertions.** A three-line bugfix carrying a line-ending sweep, under a message that mentions
  neither. **ALWAYS COMMIT THE DECOMP BY EXPLICIT PATH LIST, never `-A`**, until someone decides
  what to do about the churn. **Nothing has been deleted or normalised wholesale** — `276`
  touched five files and those five are LF, matching `HEAD`.
- **►►►► `git status` OVER THE CLAUDE BRIDGE LEAVES A STALE `index.lock` AND BREAKS THE
  OWNER'S NEXT COMMIT. `271`. ◄◄◄◄** The mount refuses to unlink, so git CREATES the lock,
  cannot remove it, and prints only a `warning:` while returning success. The next
  `COMMIT-NOW.cmd` then dies with *"Unable to create ... index.lock: File exists"*.
  **THE ASSISTANT MUST USE `git --no-optional-locks status` ON THE BRIDGE** — it takes no lock.
  `log`, `show` and `ls-files` are safe either way. **If a commit fails this way the lock is
  the assistant's litter, not a running git**: delete it and re-run.
- **►► A SECOND, STALE COPY OF THE WHOLE TREE EXISTS ON THE DESKTOP.**
  `$env:USERPROFILE\Desktop\GoldenEyeVR\goldeneye-native\getv\build-windows\goldeneye.exe`
  — **the path is IDENTICAL to the live one from `GoldenEyeVR\` down**, so an old shortcut
  or one wrong `Set-Location` runs a build months of knobs behind while every relative
  command still appears to work. `[REPORTED]` it is a temp backup from an app move.
  Its exe was renamed `.OLD-2026-08-29` on 2026-08-30. **THE LIVE TREE IS `F:\Projects\GEVR`.**
  **Always launch by ABSOLUTE path (§7a), and check the exe's timestamp before trusting a run** (`133`).
  `[INFERRED]` a candidate for §3 item 6's *"the other build"* — **not established**.
- **►►►► IF A MEASUREMENT EQUALS THE FRAME PERIOD, IT IS MEASURING THE PERIOD. CHECK EVERY
  BRACKET FOR THE PACER'S SLEEP. ◄◄◄◄** `267` §1, `271` §4 and `272` §3 are the SAME BUG in
  three different instruments. `gfx_end_frame` carries `swap_buffers_end ->
  sync_framerate_with_timer() -> sys_sleep()` (`gfx_sdl2.c:111`), so **anything that brackets
  `gfx_end_frame` has the frame cap inside it.** `ge_pace_wait_ms` (`gfx_sdl2.c:133`) is
  non-static precisely so it can be subtracted. **And the cheapest test is not another cap:
  CHANGE THE SCENE — a period-locked number cannot notice a harder level** (`272` §8).
- **►►►► A LOCAL `extern` THAT DISAGREES WITH A FORCE-INCLUDED REAL PROTOTYPE IS A HARD *ERROR*
  THAT SURVIVES `-w`, AND IT SURFACES AS A **LINK** FAILURE NAMING SYMBOLS THAT ARE NOT MISSING.
  `[MEASURED]` 2026-09-01, `292` — IT COST A BUILD. ◄◄◄◄**
  `build_windows.ps1:207` force-includes **`src/ge_port_decls.h` into every game translation
  unit**, so every engine prototype is already in scope and the house habit of writing
  `extern <type> geThing(void);` beside the call site is a **collision**, not a convenience.
  `stereo.c` declared `extern s32 bondviewGetCurrentPlayersRoom(void)`; the real one returns
  **`u8`** (`bondview.h:2822`). `build_windows.ps1:160`'s `-w` turns off warnings — **a
  conflicting type is not a warning.** The whole file failed to compile, and the build reported
  **eight `undefined reference to 'geStereo…'` link errors**, which read as *"the new file was
  never added to the build"* and are nothing of the kind. **The build's own message names the
  real cause on its FIRST line (`first failure in game (…): conflicting types`) and then buries
  it under the link wall — read the first failure, not the last error.**
  **AND OFFLINE `gcc -fsyntax-only` DOES NOT CATCH IT UNLESS IT REPLICATES THE FORCE-INCLUDE**:
  `292`'s first offline pass ran without `-include src/ge_port_decls.h` and reported 0 errors on
  every file. `stereo_harness.sh` now parses all five touched files **with `build_windows.ps1`'s
  own flag list**, and it is the reason that gate exists. **The fix is to DELETE the local extern,
  not to correct it** — the real header is already there.
  **A SECOND THING THE SAME PASS GOT WRONG:** `bondview2.c`'s *"12 pre-existing gcc errors"* were
  an artefact of the missing force-include too. With the build's flags it reports **0**.
- **►►►► `camGetWorldToScreenMtxf()` DOES NOT RETURN A WORLD-TO-SCREEN MATRIX. IT IS THE BARE
  LOOKAT, AND THE NAME COST `293` A FALSE BLOCKER. `[MEASURED]` 2026-09-01, `294` §1.3. ◄◄◄◄**
  It returns `g_CurrentPlayer->field_10CC` = `field_64` (`bondview.c:832`), built by
  `matrix_4x4_set_lookat` — **world->VIEW, rigid, no projection and no visibility scale.** The
  projection goes into `field_10E0` through a **separate copy** `spC4` (`bondview2.c:9017-9044`),
  and `bgGetLevelVisibilityScale()` is applied to **`spC4.m[0]` only** (`:9038`). **So it is exactly
  invertible, and `currentPlayerGetViewToWorldMtxf()` (`field_68`,
  `matrix_4x4_set_basis_and_position`, `bondview2.c:9010`) is its exact transpose-inverse — the two
  are built five lines apart from the same three normalised vectors and installed together by the
  only call site that writes either (`:9046-9047`).** **`293` §3b.3 read "WorldToScreen" as
  projection-carrying and therefore non-invertible, and wrote a blocker that does not exist.**
  **A round trip through this pair is an identity, not a view dependency.** Same family as
  `sub_GAME_7F03F540` and `bondviewTransformManyPosToViewMatrix` (§7): **in this codebase the
  NAME is not the contract — read the constructor.**
- **►►►► THE PORT LAYER HAS KNOBS A GAME-SIDE GREP CANNOT SEE. `278`. ◄◄◄◄**
  A sweep of every `GETV_*` across `getv\src` and `vendor\ge-decomp\src` returned 200-odd names
  and **did not contain `GETV_WIDESCREEN`** — it lives in `gfx_pc.c`, which is **gitignored and
  regenerated**. **Four wrong turns were spent inside the game while a default-ON knob sat in the
  renderer.** Grep `getv\port\**` as well, and `grep -a` the exe.
- **►►►► A `GETV_STAGE` DIRECT BOOT HAS TWO INVISIBLE INPUTS. `278`. ◄◄◄◄**
  It runs `fileValidateSaves()` **and** `fileSetCurrentFolder(FOLDER1)` (`boss.c:398-403`), so it
  **silently inherits folder 1's saved SCREEN and RATIO options** (`file2.c:1535-1541`) — and it
  **silently runs AGENT**, because the difficulty menu never ran (`lv.c:1979`, which says so in its
  own comment; `GETV_DIFFICULTY=<0..3>` overrides). **Both were uncontrolled in every `278` arm.**
  Note this is the OPPOSITE end of `277` §8: the TITLE path is the one that skips validation.
- **►►►► EVERY RUN SHEET IN THIS REPO CARRIES `GETV_VSYNC=0`, AND IT IS WRONG FOR EVERY RUN THAT IS
  NOT MEASURING THE GPU. ◄◄◄◄** `285`. It entered in `273` for a real reason and was copied forward
  ~40 times without being questioned. **It is the whole of the smoothness complaint.** For anything
  the owner will LOOK at or PLAY: `GETV_VSYNC=1`, `GETV_FPS=<panel Hz>` (**120 here**),
  `GETV_SIMHZ=query`. For GPU work only: `GETV_VSYNC=0` + `GETV_FPS=0` (`273` §8).
  **A run sheet that does not say which of the two it is, is not finished.**
- **►► AND A BLOCK THAT OMITS A KNOB SILENTLY RESTORES ITS DEFAULT.** `285` S1 dropped
  `GETV_WIDESCREEN=0` and `GETV_ROOMSCISSOR=0` while testing smoothness; the artifacts came back and
  read as a regression. **`ours: x=0` in the `VIEWPORT n64` line is the tell — widescreen is ON.**
  `x=367.333` at 2560x1369 / `x=480` at 3840x2160 means it is OFF. **Put every knob in every block.**
- **`dlgrab_*` FILES ACCUMULATE ACROSS SESSIONS** in `getv\build-windows`, and two sets from two
  days and two window sizes are told apart only by timestamp and BMP byte count
  (`54 + w*h*3`). **Identify the artefact before reading it.** `278` §7.3.
- **THE N64 `B` BUTTON IS `E` OR `F` ON THE KEYBOARD** (`port_input.c:1303`); A is `Enter`/`R`,
  Z-trigger `Z`, R `X`, Start `Tab`. On a pad it is the pad's own B.
- **`PowerShell $env: PERSISTS.** `Remove-Item Env:GETV_* -ErrorAction SilentlyContinue` **before every run.**
  **►► AND THE RESET CHANGES RESULTS: `272`'s controls silently depended on an INHERITED
  `$env:GETV_SIMDIV`.** `273` §7.1. **`GETV_SIMDIV=1` PRINTS NOTHING** (`frametiming.c:207`), so the
  only positive gate is **`props interpolated 0` plus zero `simulation held to` lines.** Put both in
  every timing block, or a 90 Hz arm silently runs `268`'s divider and its `WORK` is not comparable.
- **►► `GETV_SUPERSAMPLE` IS INERT ON WINDOWS** — both `getenv` sites sit behind `TVOS_SUPERSAMPLE`
  / `GE_POSTFX`, neither defined, while `ge_config.c:410` accepts the value and exports it.
  **A knob that is accepted, exported, and read by nobody.** Use **`GETV_WINDOW=WxH`**
  (`port_support.c:106`) for fill-rate work. `273` §7.2.
- **►►►► A KNOB'S RUN CONDITION IS PART OF THE KNOB. `GETV_REALCLOCK` **AND** `GETV_GPUTIME`
  BOTH ONLY WORK WITH `GETV_FPS=0`, AND BOTH WERE CITED FOR TWO SESSIONS WITHOUT IT. ◄◄◄◄**
  `GETV_REALCLOCK=1` under a cap renders at **60** and prints no refusal — its banner still reads
  `REAL host timebase`, which is true and useless. **`273` §2 gave `GETV_GPUTIME` a `CONTAMINATED`
  gate for exactly this; `GETV_REALCLOCK` is owed the same one and does not have it** (rule `17`).
  `274` §7. **And `GETV_CLOCKTRACE=1` is the instrument for all of it — already in the binary.**
- **`[MEASURED]` `GETV_FPS=0` LOCKS UP ON CRADLE within seconds, 3 of 3 attempts, standing still.**
  No exception, no terminator; frames just stop. Facility uncapped ran 43,800 frames. **It bounds how
  long an uncapped GPU sample can be.** Not investigated. `273` §7.3.
- **►► A TAIL IS NOT A SAMPLE.** `Select-Object -Last N` handed back the intro/cast windows of a run
  that had died and reloaded a stage — a plausible 0.22 ms from the wrong scene. **Always cut the
  window list at the `lvlStageLoad` line numbers.** `273` §1.
- **NEVER READ A LOG AS FINAL WITHOUT ITS TERMINATING RECORD** (`===== EXCEPTION`
  or `game_exit requested`). A log still being written reads as "no crash". `262` §5.
- **Check `gevr.log`/`run*.log` is NEWER than the exe** (`133`), and that the
  instrument you rely on is actually IN the binary (`grep -a` the exe).
- **►►►► A COMMIT-MESSAGE FILE ONLY COUNTS IF IT IS IN THE `GoldenEyeVR` ROOT. `287`. ◄◄◄◄**
  `[MEASURED]` 2026-08-31: `287` wrote `COMMIT-MESSAGE-2026-08-31b-native.txt` into
  `goldeneye-native\` and `...-decomp.txt` into `vendor\ge-decomp\` — **beside the repos they
  describe, which is the intuitive place and the wrong one.** `commit-now.ps1` globs the
  **GoldenEyeVR ROOT ONLY**, so it never saw them, fell back to the newest `*-native*` it could
  find — **`COMMIT-MESSAGE-2026-08-30m-native.txt`, which is `276`'s harness** — and would have
  committed `287`'s port work under a previous session's subject. **EVERY `-native` AND `-decomp`
  MESSAGE FILE IN THIS PROJECT'S HISTORY LIVES IN THE ROOT. Put them there.**
  **►► THE GUARD CAUGHT IT AND REFUSED**, naming the subject as already being HEAD. **That is rule
  `17`'s guard working as designed, on the exact failure mode rule `17` was written for** — and it
  is the first time it has fired on a real staleness rather than being reasoned about. **The guard
  is the reason this cost a message and not a mislabelled commit.**
  **THE `-F` ROUTE IS UNAFFECTED**: `git commit -F <path>` takes an explicit path and worked, which
  is why `287`'s three commits are correctly labelled. **It also committed the message file INTO
  the decomp and native repos** (six files in `2b57c497`, two in `05ce7b6`) — harmless, not the
  convention, and **not to be rewritten out of history** (rule `2`).
- **►►►► `gfx_sdl2.c` IS GITIGNORED AND REGENERATED **TOO**, AND `00-STATE` NAMED ONLY `gfx_pc.c`. `287` §5. ◄◄◄◄**
  `[MEASURED]` `.gitignore:161` + `git ls-files`. It is produced from a pristine copy plus
  `getv/patches/thirdparty/0001-getv-port-layer.patch`, which already carries a `gfx_sdl2.c` hunk
  at its line 7876. **`GETV_PACEHIST` lives in that file.** So: **`verify` FAILS until the patch is
  regenerated** (correct, expected), and **a regen run BEFORE the regeneration DELETES the
  instrument** — exactly `271` §7's `GETV_DLGRAB`, absent from a fresh clone for two days.
  **`tools/fetch-thirdparty.sh regen` then `verify`, GIT BASH, MAIN PC, AFTER the arms are worn.**
  **Assume any file under `getv/port/**` may be gitignored — CHECK `git ls-files` BEFORE editing it,
  not after.**
- **`gfx_pc.c` is GITIGNORED** — `tools/fetch-thirdparty.sh regen` in the SAME commit.
- **►► THE REGEN WAS TWO SESSIONS STALE AND IS NOW CURRENT — but read HOW it hid. `271` §7.**
  `268` was committed without one, so `GETV_DLGRAB` was absent from a fresh clone for two days.
  **It hid behind TWO silent fallthroughs, both now fatal in `tools/fetch-thirdparty.sh`:**
  an unchecked `mv` that printed *"wrote ... bytes"* after failing, and a missing `git` that
  fell through to a network fetch and blamed the network.
  **ON WINDOWS RUN REGEN FROM GIT BASH** (`C:\Program Files\Git\bin\bash.exe`) — **MSYS2's bash
  has no `git`** — and **it cannot complete over the bridge** (the mount refuses to unlink).
  **THE GATE IS `verify`: `15/15 files match pristine + patch`.** Byte count alone is not it.
- **`gfx_run()` is not re-entrant** (`gfx_pc.c:5817`) — but an eye loop at
  `lvlRender` never calls it twice. `258` §1.
- **DO NOT set `getPlayerCount()` to 2 for stereo** — 173 refs, 35 files, GAME
  LOGIC (dual-wield gating, glass-buffer sizing). `258` §1.5.
- **`build_windows.ps1:160` is `-w`** — every compiler diagnostic off. Four flags
  re-enabled found 56 pointer/int narrowings. `248` §4.
- **Config search order matters**: `$GETV_CONFIG` > CLI > beside the binary >
  **`%APPDATA%` per-user**. The last one is live and is NOT in the repo.
- **Repro for the cast roll:** touch nothing from boot. Skipping ANY intro video
  goes straight to the menu. `263` §6.

- **►►►► `ge-decomp` STORES LF IN HEAD AND 2,099 FILES SIT CRLF ON DISK, SO A WHOLE-FILE
  LINE-ENDING REWRITE HIDES INSIDE ANY DIFF THAT TOUCHES ONE OF THEM. `[MEASURED]` 2026-08-31,
  `288a`. ◄◄◄◄** `bondview.c` and `bondview.h` were two of those files, and an honest **88-line**
  change first read as **9,340 changed lines** — unreviewable, and it looks like the session
  rewrote the file. **`propobj.c` is LF on disk and diffed clean at `121 ++`, which is how the
  difference was noticed.** Converting **those two files only** to LF brought the commit to
  **209 insertions, 0 deletions, three files.**
  **THE RULE: IN `vendor/ge-decomp`, STAGE BY EXACT PATH. NEVER `git add -A` THERE** — it would
  sweep 2,097 unrelated line-ending flips into the commit. **Before committing a decomp file,
  run `git diff --stat <path>` and CHECK THE NUMBER IS THE SIZE OF THE CHANGE YOU MADE.**
  **The 2,097 others are a SEPARATE, PRE-EXISTING question and are NOT any one session's to
  "tidy".** Same family as §6's other silent-staleness traps and rule `17`: everything reports
  success while the artefact is wrong.
- **►►►► `chrprop.c` IS FULLY CRLF ON DISK AND `HEAD` IS LF — 4,502 OF 4,502 LINES — AND IT IS
  WHERE ARM 3's DRIVER GOES. `[MEASURED]` 2026-09-02, `295` §6. ◄◄◄◄**
  `288a`'s trap is sitting in the next session's path: `propsTick` (`:2538`),
  `chraiUpdateOnscreenPropCount` (`:219`) and `g_OnScreenPropList` (`:90`) are all in `chrprop.c`,
  so an honest 40-line change will first read as ~4,500. **Convert that one file to LF in the same
  commit, exactly as `288a` converted `bondview.c`/`bondview.h`.** `[MEASURED]` by
  `grep -c $'\r'` per file: `lv.c`, `stereo.c`, `stereo.h`, `bondview2.c`, `model.c`, `propobj.c`
  and `chr.c` are **all LF** and `295`'s six-file decomp change diffed at **499 insertions,
  2 deletions** — the size of the change that was made.
- **►►►► A `git status` FROM THE BRIDGE LEAVES A STALE `index.lock` THAT BLOCKS THE OWNER'S NEXT
  COMMIT. `[MEASURED]` 2026-08-31, `288a` — IT BROKE A COMMIT THE SAME SESSION. ◄◄◄◄**
  The mount refuses `unlink`, so git creates `.git/index.lock`, fails to remove it, and warns
  `unable to unlink '.git/index.lock': Operation not permitted` — **which reads like a warning and
  is actually damage.** Minutes later `COMMIT-NOW.cmd` died with
  `fatal: Unable to create '...index.lock': File exists. Another git process seems to be running`
  on **both** `goldeneye-native` and `vendor/ge-decomp`. **There was no other git process.**
  **READS FROM THE BRIDGE ARE NOT FREE. `git log`, `git show` and `git diff <path>` are safe;
  `git status` and `git add` are NOT** — plain `git diff`/`git status` refresh the index and take
  the lock. **Prefer reading the working tree directly** (`ls`, `cat`, a `find`) **over asking git
  what changed.**
  **THE REPAIR, AND IT IS A MAIN-PC ACTION:** confirm the lock is **0 bytes** (git died before
  writing; a non-empty lock means a real interrupted write and is NOT safe to delete), confirm no
  git is running, then `Remove-Item` it and re-commit. **Every commit, regen and build is a MAIN-PC
  action anyway** (§0a, rule `1`).

- **►►►► A RUN SHEET THAT SAYS "USE THE PREVIOUS SHEET'S BLOCK **VERBATIM**, ADDING THESE TWO
  LINES" HAS NOT SUPPLIED A COMMAND. `[MEASURED]` 2026-09-02, `296` §11. ◄◄◄◄**
  **DELEGATION IS NOT A BLOCK**, and §7a says so in as many words. Three sheets have now chained
  it — `292` §5/§6/§7 → `295` §6/§7/§8 → and it would have gone on — so **by the third link the
  owner is reading three documents to run one command.** Each link is individually reasonable and
  the chain is not. **And the delegated-to block silently loses whatever the NEW sheet's own blocks
  learned to carry:** `292`'s four arms carry **no `Get-Item .\goldeneye.exe` timestamp line**
  (`133`, and the stale second tree above), `292` §4 omits `GETV_STEREO_MODE`, and `295` §8 left
  `GETV_STEREO_VIEWRESTORE` to its default — which happened to be the wanted value, and **being
  right by accident is exactly the failure `285` names.** **REPRODUCE THE BLOCK, DO NOT POINT AT
  IT.** `RUN-SHEET-295` §10 is the repair.
- **►► AND `GETV_FPS=panel` RESOLVES AT RUNTIME, SO ITS BANNER BELONGS IN EVERY BLOCK'S GREP.**
  `gfx_sdl2.c:563` prints `GETV_FPS=panel -> N Hz`; `:553` REFUSES and `exit(1)`s if SDL will not
  answer, **so a refusal cannot pass silently** — but **a window that opened on the wrong monitor
  resolves to that monitor's rate with no other tell**, and every `285`-era number is defined
  against that rate. `296` §11 defect 4.

## 7. THE ENGINE FACTS THAT CHANGE DESIGNS
- **►►►► `prop->zDepth` IS NOT RENDER-ONLY, AND EVERY DOCUMENT BEFORE `297` SAID IT WAS. ◄◄◄◄**
  `293` §3a puts *"re-derive `zDepth`"* in the per-eye column. `[MEASURED]`, by grepping every
  reader: **`chr.c:4013`, `:4014`, `:4067` (nearest-candidate selection) and `:4020`, `:4148`
  (`maxdist` rejection) read it in the SHOT/HIT TEST**, and `objective_status.c:670` reads it too.
  Only `bgfog.c:691`/`:699` wants the per-eye value. **A naive per-eye re-derivation leaves the LAST
  eye's depth installed for the simulation — at `GETV_STEREO_OFFSET=500` a 250-unit error inside a
  hit test — and unlike `293` §3b.3's tank rect it does NOT cancel**, because `zDepth` is a raw
  view-space depth with no round trip through `V2W`. ARM 3 snapshots it after the tick and restores
  it after the eye loop (`297` §5).
  **THE GENERAL RULE: before moving a write into a per-eye pass, GREP ITS READERS. "Render-only" is
  a claim about the whole tree, not about the line.**
- **`lvlRender` (`lv.c:762`) ALREADY LOOPS OVER VIEWS** — per-view viewport, FOV,
  aspect, projection, one display list, one swap. **Split-screen is the shipped
  existence proof for stereo's mechanism.** `258` §1.
- **`viSetupCurrentPlayerView` (`fr.c:696`) is the seam AND the only place the
  projection is built.** `guPerspective` cannot express an off-centre frustum —
  a headset frustum must REPLACE it.
- **Row-vector vs column-vector:** `guPerspectiveF`/`guLookAtF` are row-vector,
  GL/OpenXR column-vector. **Engine yaw is the NEGATIVE** of the right-handed
  convention (`bondview2.c` rotates by `360 - vv_theta`).
- **The eye TRANSLATION lives in the VIEW matrix.** Projection-only is frustum
  shift, not separation — that is `B1`. `255` §1.
- **Local multiplayer is intact and LINKED**: `mpmenu.c`, MP text banks,
  split-screen viewport code, `_Static_assert(GE_PORT_MAX_PADS == 4)`, plus
  `ge_net*.c`/`ge_bot*.c` in the port layer. **Linked is not run.** `258` §2.
- **►►►► BOTH THE DISPLAY-LIST AND THE VERTEX POOL ARE SIZED BY `getPlayerCount()`, ONCE, AT
  LEVEL LOAD — AND AN EYE IS NOT A PLAYER. `292` §1. ◄◄◄◄** `dyn.c:40-41,90-96`:
  `g_GfxSizesByPlayerCount[] = {0x10000, 0x18000, 0x20000, 0x28000}` and an identical
  `g_VtxSizesByPlayerCount[]`, both indexed `[getPlayerCount() - 1]`. An eye loop that keeps the
  count at 1 (which `258` §1.5 requires) draws **two views out of the one-view pools**. `dyn.c`'s
  own comment records what running out costs and it is not a hypothetical: **the writer stops
  appending with no terminator and no error, and `gfx_run_dl` walks off the end into vertex data
  until a garbage `G_VTX` segfaults** — Jungle in first person already fills the scaled pool.
  **The VERTEX pool is the one that gets missed:** `dynAllocateMatrix()`/`dynAllocateLights()`
  both come from `g_GfxMemPos`, which starts inside `g_VtxBuffers`, and the existing
  `GETV_GFXPOOL` block scales only the `Gfx` side.
- **`viSetViewSize()`/`viSetViewPosition()` WRITE BACK INTO THE PLAYER STRUCT** via
  `currentPlayerSetScreenSize`/`Position` (`fr.c:880-900`, `player.c:559-568`) — and
  `lvlRender` passes `g_CurrentPlayer->viewx` straight back in, so anything that scales the
  rectangle inside the loop scales an already-scaled value on the next pass. They also call
  `currentPlayerSetCameraScale()`, so the culling scales and `posIsOnScreen`'s plane normals
  re-derive from the new rectangle for free — **but those normals are built from a SYMMETRIC
  half-angle and cannot express an off-centre frustum.** `292` §2.
- **`bgScissorCurrentPlayerView()` (`bg.c:2277`) CLAMPS EVERY ROOM'S CLIP RECTANGLE TO THE
  PLAYER'S rectangle**, not the video mode's — which is why a side-by-side split needs no
  renderer change at all. `292` §2.3.
- **`propsTick()` AND THE WHOLE SIM BLOCK SIT INSIDE `lvlRender`'s PER-PLAYER BODY**
  (`lv.c`, between `bgRoomVisibilityRelated()` and `bgLevelRender()`), and
  `gePortSimShouldTick()` is a pure flag read that cannot defend itself. **Anything that loops
  that body must gate the tick itself.** `292` §2.1.
- **►►►► `bondviewTransformManyPosToViewMatrix` IS NOT A TRANSFORM, AND IT IS NOT IDEMPOTENT.
  `292` §5a. ◄◄◄◄** Despite the name it applies no view matrix: it converts each `RenderPosView`
  from `f32` to 16.16 fixed point **IN PLACE, OVER THE SAME MEMORY** (`matrix_4x4_f32_to_s32`).
  Run it twice on one array and the second pass reads fixed-point words back as floats and
  **saturates every entry at +/-32768** — geometry stretched across the whole view.
  `model->render_pos` is per-FRAME arena state rebuilt on the OPAQUE pass; the conversion runs on
  the ALPHA pass (`chr.c:3538`, `withalpha != 0`). **One rebuild, one conversion — anything that
  runs the render body more than once per frame breaks that pairing.** `GETV_STEREO_MTXGUARD`.
- **`model->render_pos` POINTS INTO THE PER-FRAME ARENA** and is re-pointed at a fresh
  `dynAllocate` when a prop or chr is admitted (`propobj.c:5991`, `chr.c`). **After
  `dynSwapBuffers()` a model that is NOT re-admitted still holds last frame's pointer, into memory
  this frame is overwriting.** `292` §5a.
- **►►►► `propsTick()` IS NOT A SIMULATION TICK. IT IS ALSO THE PER-VIEW MODEL BUILD AND THE
  ON-SCREEN ADMISSION PASS. `293` §2. ◄◄◄◄** `objTick` (`propobj.c:4294`, at `:5980-5992`) runs
  **`posIsOnScreen`**, sets **`PROPFLAG_ONSCREEN`**, **`dynAllocate`s `model->render_pos`** and
  fills it from **`camGetWorldToScreenMtxf()` — the CURRENT VIEW MATRIX**; `chrTick` additionally
  tears down and rebuilds **`chr->field_20`, the joint list** (`chr.c:2846-2851`, `:3222-3223`).
  `chraiUpdateOnscreenPropCount()` then builds `g_OnScreenPropList` from those flags and
  `chrpropsRenderPass()` (`chrprop.c:500`) iterates **that list only**. **ANYTHING THAT RENDERS THE
  BODY MORE THAN ONCE PER FRAME MUST RUN THIS PER VIEW — and `258` STAGE 6 gated all of it to eye
  0, because there is ONE gate over two jobs.**
- **►► AND THE ADMISSION TEST ALSO SELECTS BETWEEN TWO *SIMULATION* PATHS, SO THE OBVIOUS CUT IS
  ILLEGAL. `293` §3a.** `var_v1_5` in `objTick` chooses branches that walk the prop's children
  through **different functions** (`sub_GAME_7F0442DC` / `sub_GAME_7F04424C`), each calling
  `chrobjWeaponTick`; `chrTick`'s other branch latches `shadecol = nextcol`. And the ~40 lines
  upstream of the test mutate the **portal table** (`doorActivatePortal`,
  `bgToggleDataPortalsContrlBytes1Bit1`, `propobj.c:5922-5967`) — the graph
  `bgRoomVisibilityRelated` walks. **Neither function may be run twice per frame.**
- **►► `dynAllocate` IS A BUMP ALLOCATOR WITH NO BOUNDS CHECK** (`dyn.c:155-186`), so the
  `gSPSegment` POINTER VALUES in a `dlgrab` are a direct read on **who allocated in which pass** —
  a value reused from an earlier pass means nothing was rebuilt. `293` §2.1; that is how the
  second eye was shown to allocate nothing.
- **►►►► THE VIEW PAIR AND THE ARENA ARE ONE COORDINATE SYSTEM WITH ONE OWNER. THIS IS THE WHOLE
  DESIGN CONSTRAINT ON A PER-EYE BUILD PASS, AND IT REPLACES THREE SEPARATE WORRIES. `294` §4. ◄◄◄◄**
  `g_CurrentPlayer->field_10CC` (W2V), `g_CurrentPlayer->viewtoworldmtxf` (V2W) and every
  `model->render_pos` block written under them belong to **whichever eye was installed when they
  were written**. **Any read of any of them must happen while that same eye is installed.** Round
  trips through the pair cancel (`propobj.c:6346`), rays transformed into it match
  (`propobj.c:1601`, `:1607`), matrices allocated under it are per-eye for free — **break the
  pairing and all three fail at once, by the full inter-eye separation.** Combined with `293`
  §3c.3's *"the build must re-run as a WHOLE per eye — a partial re-run re-transforms"*, that is the
  complete constraint. **There is NO "which eye wins" decision anywhere in `293` §3b.**
  **AND SPLIT-SCREEN IS THE EXISTENCE PROOF FOR THE PAIRING, NOT JUST FOR THE MECHANISM** (`258`
  §1): `set_cur_player()` moves the view pair, the arena and the shot ray together per player, so
  the discipline is automatic there — **and an eye loop that keeps `getPlayerCount()` at 1 (`258`
  §1.5) gets NONE of it for free and must reproduce it by hand.**
- **►►►► `PROPFLAG_ONSCREEN` DOES NOT ONLY DECIDE WHAT IS DRAWN. IT DECIDES WHETHER A BULLET GETS A
  PRECISE HIT TEST. `294` §3.4. ◄◄◄◄** `propobj.c:1399`: an ONSCREEN prop gets
  `projectileLineTestModel` — a precise per-node line test against `render_pos`; everything else
  falls through to the coarse `instsize` bounding sphere. **A GAMEPLAY consequence of a RENDERING
  flag**, and a second, independent reason the admission pass must stay **once per frame**
  (`293` §3b.5) — run it per eye and a prop's hit fidelity depends on which eye ran last.
  **The whole shot path is VIEW-SPACE END TO END**: `shotdata.viewOrigin` is literally `{0,0,0}`
  (`gunfire.c:6117`), the direction comes from `crosshair_angle`, and the hit tests read
  `render_pos` through `modelFindNodeMtx`. **So "where the bullet comes from" in this engine is THE
  CAMERA, not the gun — which is a real VR question and is NOT a `293` §3b question** (`263` §1).
- **►►►► THE ARENA WATERMARK NAMES THE OWNER OF EVERY BLOCK, SO NOTHING HAS TO BE STAMPED.
  `295` §2. ◄◄◄◄** `[MEASURED]` `dyn.c:155-190`: `dynAllocate`, `dynAllocateMatrix` and
  `dynAllocateLights` are the **same single bump pointer** `g_GfxMemPos`, which only ever
  increases within a frame and is reset only by `dynSwapBuffers()`. **So every allocation an eye
  makes lies in ONE CONTIGUOUS ADDRESS RANGE**, and recording `g_GfxMemPos` at each eye's first
  line classifies every arena pointer by eye — the hat matrices and joint lists as well as the two
  blocks `294` §5 named. **`294` §5's per-block stamp is superseded, and §5 invited exactly this.**
  A pointer in NO range is `outside`, **never a mismatch**: a stale last-frame pointer into the
  other half of the double buffer produces one, and so does anything allocated before the loop.
- **►►►► `chrTick`'s BUILD BLOCK HAS **TWO** UNGUARDED ACCUMULATORS. `293` §3c.1 NAMED ONE.
  `295` §3. ◄◄◄◄** `[MEASURED]` `chr.c:2893` `flinchcnt += g_ClockTimer` **and `chr.c:2910`
  `update_color_shading(&chr->shadecol, &chr->nextcol)`, behind no guard at all** —
  `dest += ((src - dest) + 7) >> 3` (`propobj.c:656-668`), an exponential-approach lerp, i.e. an
  accumulator, closing **23.4% of the gap per frame instead of 12.5%** if it runs twice. **It is
  the same call `293` §3b.1 lists as being behind `isSimOwner` in `objTick` (`:5985-5987`)** — so
  the asymmetry §3c.1 found is real and larger than it was written. **An ARM 3 that hoists only
  `flinchcnt` ships a double-rate colour lerp.**
- **►► `currentPlayerSetMatrix10CC`/`SetViewToWorldMtxf` ALSO SHADOW THE OUTGOING PAIR INTO
  `field_10E8`/`field_10EC`, AND IT IS READ.** `bondview.c:823-830`, `:856-859`;
  `chraction.c:6101` and `:6119` call `currentPlayerGetMatrix10EC()`. **In a stereo frame that
  "previous view" is already THIS frame's other eye**, not last frame — eye 1's setter pushes eye
  0's pointer in. `295` §1.2: named, **not fixed**, and it is why ARM 1's restore writes the two
  fields directly instead of calling the setters.
- **►► `chraiUpdateOnscreenPropCount()` DOES NOT ONLY COUNT — IT SORTS `g_OnScreenPropList` BY
  `zDepth`** (`chrprop.c:254-276`). `293` §3b.5 puts `zDepth` per eye and admission once per
  frame, and **the sort straddles the two.** Re-deriving `zDepth` per eye without re-sorting
  leaves the second eye drawing in the first eye's alpha order. **A decision ARM 3 owes out loud.**
  `295` §6.
- **The decomp `lib/ge` is MATCHING** — "did we change the feel" is a DIFF.

## 7a. ►►►► EVERY COMMAND THE OWNER RUNS IS SUPPLIED COMPLETE ◄◄◄◄
**STANDING RULE, 2026-08-30, AT THE OWNER'S REQUEST. FULL TEXT: `SESSION-START.md` §1b.**
**Never describe an action -- give the command, as ONE self-contained copy-paste block:**
**absolute paths** (never relative to a directory you assume is current) ·
**`Remove-Item Env:GETV_* -ErrorAction SilentlyContinue` as the FIRST LINE** of any block
that sets a `GETV_*` (**`$env:` persists and the owner runs several windows**) ·
**one block per action** · **every variable set explicitly, assume nothing survives** ·
**end with the block's own verification** (exe timestamp, the env actually set, the banner
that proves the knob took) -- **a knob that is not in the binary reads as a clean null
result** (`133`, `268` §4).
> **This is rule `14` pointed at the shell.** If the owner has to reconstruct any part of
> it, the command was not finished.

## 7b. STARTING A SESSION
> **►► TWO TRACKED, DIVERGENT COPIES OF `SESSION-START.md` EXIST. THE CANONICAL ONE IS
> `repo\docs\SESSION-START.md` (195 lines).** The 99-line copy at the repo ROOT is older
> (2026-08-29 vs 2026-08-30) and **does not carry §1b, §5's regen correction, or the reasoning
> table's current text.** §7b used to name the file with no path, and **this session oriented
> off the stale root copy** before noticing. Same shape as §6's second tree: identical name,
> older content, everything still appears to work. **Which copy survives is the owner's call —
> nothing has been deleted.** `271`.

**`repo\docs\SESSION-START.md`** — what the owner supplies, the standing prompt, and the
end-of-session checklist. **The owner supplies NOTHING but the prompt** unless
something changed by hand or a specific run log is meant.

## 7b2. ►►►► WHEN THE OWNER REPORTS SOMETHING THEY CAN SEE, IT GOES IN §3 IN THEIR WORDS ◄◄◄◄

**`297` §0, and it is a process finding worth more than that session's code.** The owner reported
*"the characters and props are not in the right eye at all, and it's warping"* after `292`, after
`293` and again after `295`. `293` diagnosed it correctly — and recorded it only as
`MODEL_MTX 39->1`, *"the eye-1 model collapse, ARM 3's job"*. **Every later sheet then referenced
that phrase instead of the symptom, and it shrank into a sub-clause of someone else's arm.** By
`RUN-SHEET-295` §10.1 the project was telling the owner to **expect** it and scoring the gate met
anyway.

- **A defect written only in the instrument's vocabulary reads as filed and stops being ranked.**
  The engine-term entry is the EXPLANATION. The owner's sentence is the ITEM.
- **It goes at the TOP of §3 OPEN and it stays there until it is gone.**
- **NO GATE EVER SAYS "EXPECT X TO STILL BE THERE" about something the owner has reported.** That
  converts an observation into an accepted background condition.
- **AND DO NOT PROPOSE THE NEXT ARM OVER IT.** A measurement taken on a broken frame is a number
  about nothing; say so and reorder.

## 7c. ►► ENDING ONE: THE ASSISTANT SAYS WHEN TO START A FRESH SESSION ◄◄
**STANDING RULE, 2026-08-30. FULL TEXT: `SESSION-START.md` §5.** The owner should never have
to guess whether the session has gone stale — **flag it unprompted, like the reasoning dial.**
**Never invent a context percentage; you cannot see one.** Call it from COUNTS AND SYMPTOMS
and say which: large artefacts read (**run logs are the usual trigger**) · **re-grepping for
something already found** · summarising where you used to quote exact lines.
**The four moments:** a finding documented AND committed (the cheapest seam) · the next task
is a different KIND of work, especially anything `SESSION-START` §4 marks **HIGH** ·
the fault has moved to a new subsystem · any symptom above.
**A POINTER IS NOT A HANDOFF** — do not suggest it until `00-STATE` and the numbered doc are
updated, and include the one-line prompt, the run-log names, what to do FIRST, and anything
owed that is not yet written down.
**AND THE COMMIT MESSAGE FILES ARE PART OF THAT — RULE `17`, added 2026-08-30.** One per repo
touched, dated today. **`COMMIT-NOW.cmd` substitutes the newest file it can find**, so a session
that writes none commits under the PREVIOUS session's message. It did that three times on
2026-08-30. **The script now refuses a subject that already matches HEAD; writing the file is
still the assistant's job, not the guard's.**

## 8. GOING DEEPER — WHERE TO LOOK, NOT WHAT TO READ
| you need | go to |
|---|---|
| the build route, stages 0-9 | **`258`** |
| the split-screen existence proof, and the 4-player fault | **`270`** |
| the combiner probe: gates, wiring, how it fails | **`264`**, and its result **`265`** |
| the frame budget instrument | **`266`**, why its first cut was wrong **`267`**, and the work/wait split that fixed it **`271`** |
| the pre-stereo CPU baseline, and why the GPU is now the open term | **`271`**, corrected and re-taken on Cradle by **`272`** |
| **why the GPU timer reads the frame cap, and the gated repair** | **`272`** |
| **the GPU's actual number, why it needs `GETV_FPS=0`, and the repair that missed** | **`273`** |
| **the timebase decision, why the real clock renders 60, and what STAGE 4 still owes** | **`274`** |
| **the guard audit, the shape decision, and the cast-camera NaN trap** | **`275`** |
| **the fix itself — `GETV_SIMHZ`, its refusals, and the harness that failed first** | **`276`**, and **`RUN-SHEET-276.md`** for the `239` gate |
| **the gate RUN, the wear result, and why `RB-04` is TWO faults** | **`277`** — and §7 for the `RB-04` route, recorded at last |
| **the widescreen holes, `GETV_WIDESCREEN`, and why the culling is exonerated** | **`278`** — and §5 for the tank entry chain, §6 for the hoist-1 retraction candidate |
| **the reconciliation: why "admitted identically" and "clipped too narrow" both hold** | **`280`** |
| **`281` reviewed — right site, wrong mechanism** | **`282`**, and the probe result **`283`** |
| **the arms that convicted the rectangle and closed `281`** | **`284`**, and **`RUN-SHEET-283`** |
| **the smoothness report, the vsync finding, and four candidates** | **`285`** |
| **the handover, the play settings, and what survives the switch** | **`286`** |
| **the six sites, the turn's delta, the panel nobody asked, and the third recipe** | **`287`** — and **`RUN-SHEET-287.md`** for every block |
| the 90 Hz artifact, and the divider that caused it | **`268`** |
| dumping one frame's whole display list (`F9`) + its BMP | **`268` §8** |
| why a `GETV_MENU` boot was silent, and the three symptoms it shared | **`269`** |
| **the room test killed, the masked zero, and the mouse re-diagnosis** | **`289`** — and **`RUN-SHEET-289.md`** for every block and every written-before-the-run outcome |
| **the pose spine — STAGE 5, the sim-owned pose and its can-fail instrument** | **`290`**, and **`RUN-SHEET-290.md`** |
| **STAGE 6 stereo — the eye loop, the four tangents, the pools, and the gate** | **`292`**, and **`RUN-SHEET-292.md`** |
| **the NEXT session: build + run `292`'s five arms, and STOP AT THE FIRST GATE** | **`NEXT-SESSION-PROMPT-293.md`**, and **`RUN-SHEET-292.md`** |
| what happened most recently | `HANDOVER` top banner |
| the rules, `P1`-`P9`, the spirit test | `00-START-HERE` |
| evidence tiers — `[MEASURED]`/`[REPORTED]`/`[INFERRED]`/`[ASSUMED]` | **`182` — MANDATORY** |
| session protocol, one-behaviour-change | `48` |
| grep `externs.h`/`structs.h` before costing anything | `168` §5 |
| the task board / IDs | `39`, `169` |
| commands the owner must run | `MAIN-STATION-TASKS.md` |
| **the regen, exactly — Git Bash, and the `verify` gate** | **`MAIN-STATION-TASKS.md`, top** |
| prior art + the licence split | `00-START-HERE` "Look for prior art", `PUBLISH-MANIFEST.md` |

> ## HOW TO KEEP THIS FILE HONEST
> **At the end of every session: update §3 (state), add any retraction to §4, add
> any killed theory to §5, and bump the currency line.** A numbered doc is still
> written for the session's findings — **this file is the INDEX, not a
> replacement.** If §4 ever gets shorter, something was quietly deleted.
