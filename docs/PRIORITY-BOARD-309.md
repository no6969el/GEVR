# PRIORITY BOARD — `309`. **LAST UPDATED 2026-09-04, AFTER `RUN-SHEET-308` §2a WAS WORN.**

> **CURRENT BOARD. Supersedes `PRIORITY-BOARD-308`, `PRIORITY-BOARD-307` (which `307` itself never
> re-numbered), `PRIORITY-BOARD-306` and `PRIORITY-BOARD-299`.**
>
> **►►►►►►►► WHAT CHANGED FROM `308`: `RUN-SHEET-308` §2a IS WORN AND ITS DIAGNOSIS IS
> FALSIFIED. `H19` SURVIVES, NARROWED — the under-read is a near-constant ratio of ~`0.69`, not a
> per-frame patch-averaging error, and its `10-13%` framing is RETRACTED (`00-STATE` §4). `V3`
> did not move for the second session running, and its one "pass" is now known to be
> UNFALSIFIABLE. The instrument gained `--patch FRAC`. `H20` IS NEW: the logged frustum carries an
> unaccounted 4:3 term.**
>
> **►►►►►►►► WHAT CHANGED FROM `307`: `H1` AND `H18` ARE CLOSED (`RUN-SHEET-308` §1, worn) — the
> disparity tool now refuses a `dx` it cannot stand behind. `V3` DID NOT MOVE and is still the
> spine. `H19` IS NEW (the ±5 px under-read, promoted out of `V3`'s own row because it is an
> INSTRUMENT question and `V3` is a RESULT). Two documentation defects from `307`'s handover are
> filed in `00-STATE` §4 and are not board items.**
>
> **►► THE NUMBER IS THE DATE STAMP: EVERY SESSION THAT CHANGES THIS BOARD RE-NUMBERS IT AND
> BANNERS THE ONE IT REPLACES.** Seven sessions of in-place strikethrough is what made `299`
> unreadable, and numbering the edit is cheaper than reading through it.

**HOW TO USE THIS.** Each group is a **session's worth of work** and they are ordered, but they are
**not a chain**: a session can take any group whose PRECONDITION is met without touching the others.
Every item says its effort, its precondition, and **what would make it not worth doing** — because
the most expensive thing this project does is run an arm that could not have answered anything
(`279` §7, and it has now happened five times).

**EFFORT IS THE OWNER'S TIME, NOT THE ASSISTANT'S:**

- **`LOW`** — offline only, **or** one short run with **no build** and no new analysis. Minutes.
- **`MEDIUM`** — a build, **or** a run plus real analysis. One sitting.
- **`HIGH`** — a design decision, a wear session, or work whose scope is not yet bounded.
  **A `HIGH` item should not be started at the end of a session.**

**WHY THIS BOARD IS RE-NUMBERED.** `PRIORITY-BOARD-299` was written at the end of `299` and has
been edited in place through `303`, `304` and `305`. **Seven sessions of strikethrough is no longer
readable as a plan**, and the owner asked for a board that says where the project stands and how it
reaches a headset. `299`'s board is kept in full, superseded, because rule `2` deletes nothing.

---

# §A — WHERE THE PROJECT ACTUALLY STANDS, 2026-09-04

**BINARY:** `goldeneye.exe` **18,070,774 bytes**, sha256 `45756E5ADB5F…E7223F92`, built 21:05:38Z
2026-09-03, verified against `EXPECTED-EXE-303.txt` on 2026-09-04. **Commits `94cdf01c` /
`c26c58d` / `d393860`, then `f3c9a04` / `71ac3b3`, then `8946e54` / `f70fe81`, then `689b009` /
`e58e1f1`. All trees clean.**

**SEVEN SESSIONS OF SCORE, `299` → `306`:**

| | `299` | `306` |
|---|---|---|
| owner-visible stereo defects on the board | **2** — the dead eye in every level's opening, and the warped/absent props | **1** — the one-eye polygon |
| groups closed | 0 of 6 | **2 of 6** (`A` landed, `B` closed by measurement AND by the owner's eyes) |
| measurement holes closed | 0 of 10 | **11 of 18** — and the two newest were opened by an arm that ran, not by reading |
| explanations for the polygon excluded **by measurement** | — | **4** — admission, the matrix conversion, the arena, the draw order |
| filed fixes that turned out to be wrong | 5 | **5** — and `305` came one keystroke from six |
| **`258` STAGE 6's exit gate (`S3`, separation)** | **never run** | **RUN, RE-AIMED AND SCORED ON 16 GRABS. GATE 6.1 PASSES ON EVERY ONE, BOTH ARMS — the census era is closed. GATE S3 (±5 px) DOES NOT: 1 of 12 `S3b` grabs is in band, and it is the frame with the SMALLEST predicted disparity.** `S3c` is VOID, not failed, and the tool now says so itself |
| measurement holes closed | 0 of 10 | **13 of 19** — `H1` and `H18` closed together by `RUN-SHEET-308` §1; `H19` is new |

**THE HONEST READING OF THAT TABLE.** The correctness work has gone well: the second eye is full,
the depth clamp is fixed, the double conversion is dead, the instruments can be trusted. **What has
not moved in seven sessions is the thing that would tell us stereo actually WORKS** — `S3` — and
the reason it did not move was legitimate until `303` §2 and is not legitimate now. **GROUP `V`
exists to stop that drifting for an eighth session.**

---

# §B — THE ROUTE TO A HEADSET, BECAUSE IT HAS NEVER BEEN WRITTEN DOWN

## GROUP V — **FROM HERE TO VR TESTING.** Precondition: none. **THE SPINE OF THE NEXT THREE SESSIONS.**

**READ THIS FIRST, BECAUSE IT IS THE PART PEOPLE GET WRONG.** *"VR testing"* is two different
things and only one of them is close:

- **STEREO PROVEN ON A DESKTOP** — `258` STAGE 6's own gate, and **it needs no headset at all**
  (`255` §4). Side-by-side at `GETV_STEREO_OFFSET=500`, the halves cross-correlated, the prediction
  written to the log **before** the screenshot. **This is `V3` and it is one run away.**
- **THE GAME IN A HEADSET** — needs an **XR layer that does not exist**: `[MEASURED]` 2026-09-04,
  **there is no runtime call of any kind in the tree — no `xrCreateSession`, no `IVRSystem`, no
  `ovr_Initialize` — and the word `OpenXR` appears exactly TWICE, both in comments**:
  `posespine.c:10` (*"No OpenXR"*, describing how the spine is fed synthetically) and
  `stereo.c:324`, **which already states the pose basis in the OpenXR convention** — +X right,
  +Y up, −Z forward. **That second one is a head start and it is the only one.** `258`
  STAGE 6 excludes it by name: *"NOT in this stage: OpenXR, head tracking, hand aim, vignette, HUD
  quad, mirror, `gevr_xr.c`."* **That is GROUP `X` and it is a build, not a run.**

**AND THE PROJECT ALREADY HAS HEADSET EXPERIENCE — ON THE OTHER LINE.** `161-6DOF-PRIORITY-BOARD`
is the **recomp** line (`GoldenRecomp.exe`), where 6DoF, the aim chain and the hand basis were worn
in a headset. **Its results are prior art for STAGES 7-8 of the native line and its tasks do not
run against this binary.** Nothing there needs re-deriving; nothing there is a substitute for `V3`.

| # | task | effort | gate, and what makes it not worth doing |
|---|---|---|---|
| **V1** | **Read the `P1` arm that is already on disk.** `RUN-SHEET-306` §3 | **LOW**, offline | `stereo_eyediff.py` over `grabs_304_P1\`'s nine gameplay frames. **The gate is CONCENTRATION, not a hit count** (`304` GATE §2a, corrected by `305` §1.5 to read top-three share beside largest blob). **Not worth doing only if it has already been read — and check `ls`, because three documents were wrong about that** |
| **V2** | **`P2`, the same walk with `GETV_STEREO_REBUILD_VIEWER=0`.** `RUN-SHEET-306` §4 | **LOW**, one run | Dates the polygon against `303`'s fix. **`P2`'s opening frames diverge whatever happens** — only a concentrated hit in a GAMEPLAY frame counts |
| **V3** | **►►►►►►►► `S3`, THE SEPARATION GATE. STILL THE SPINE, AND `308` DID NOT MOVE IT. GATE 6.1 PASSES ON ALL 16 GRABS BOTH ARMS (census era closed); GATE S3 (±5 px) DOES NOT — 1 of 12 `S3b` in band. THE CONFIDENCE GATE IS NOW IN (`H1`/`H18` closed) SO THE TOOL NO LONGER RETURNS A CONFIDENT WRONG NUMBER — BUT AN HONEST INSTRUMENT IS NOT A PASS.** ►► **AND THE ONE PASSING FRAME IS THE WEAKEST EVIDENCE ON THE BOARD: `5400` predicts **−11.04 px**, the smallest of the twelve, and carries the LOWEST contrast (0.286). A gate met at near-zero disparity says almost nothing about a 1/D law.** **NEXT IS `RUN-SHEET-308` §2a — the `--patch FRAC` question — then §2b, one flat-wall run, only if §2a is inconclusive** | **MEDIUM**, one run at most | GATE 6.1 (census: both eyes non-zero on the grabbed frame) **then** GATE S3 (`VERDICT PASS`, `\|measured − predicted\| ≤ 5 px`, sign matches, D=1000 and D=4000 in a 4.000 ratio, and **the answer does not move with `--search`**). **NOT WORTH DOING IF 6.1 FAILS — stop there.** A disparity across a dead eye is `295` §10.1's black-frame PASS repeated |
| **V4** | **`S4`, the mode-2 falsifier.** `RUN-SHEET-299` §4.3 | **MEDIUM** | Not required by `297` §8, **but `S3`'s pass cannot be withdrawn without it** (`49`). Run it in the same sitting as `V3` or the pass is a claim with no negative arm |
| **V5** | **`R5a/b/c` — ARM 3's cost with stereo ON.** `RUN-SHEET-299` §5 | **MEDIUM** | `P5`: **no performance claim without an instrument that can fail.** The comparison is against `272` §5.2's pre-stereo baseline — **0.890 ms mean, 2.504 ms worst, CRADLE at 90 Hz** — and `WORK_OVER=` is the instrument. **`R5b − R5a` does not have to be zero; it has to be KNOWN** |
| **V6** | **Set a real IPD.** `GETV_STEREO_OFFSET` from 500 to ~6 cm in the engine's units, then re-measure | **LOW** after `V3` | `255` §4: **500 is deliberately absurd so the mechanism is unmistakable; the human number is tuned after the mechanism is proven.** Doing this before `V3` hides a broken mechanism inside a plausible picture |
| **V7** | **The one-eye polygon — GROUP `C`.** Fix before extended headset time, not before `V3` | **HIGH** | A one-eye polygon on a monitor is an artefact; **in a headset it is binocular rivalry, which is a comfort problem, not a cosmetic one.** It does not block `V3` and it does block wearing the thing for an hour |
| **V8** | **GROUP `X` — the XR layer** | **HIGH** | Below. **Nothing in `V1`-`V7` creates it and no amount of stereo correctness substitutes for it** |

**NOT WORTH DOING IF:** you are tempted to skip `V3` because the picture "looks stereo". **The
whole method of this project is that a picture is not a measurement** — `295` scored a PASS on a
black frame, and `303` §6 exists because nothing could answer *is the picture right* without the
owner's eyes.

## GROUP X — **THE XR LAYER. IT DOES NOT EXIST YET.** Precondition: `V3` passed. **HIGH.**

**NOTHING HERE IS DESIGNED ON THIS BOARD** — `301` §0, and a hole's filed fix is a diagnosis, not a
patch. These are the questions a design session has to answer, in the order the answers depend on
each other. **Every one of them is additive and must be inert when the layer is off** (rule `3`,
the VR layer is the "additive" column).

| # | question | note |
|---|---|---|
| **X1** | **Which runtime surface, and where does the session live?** `gevr_xr.c` is named by `258` STAGE 6 and does not exist | The recomp line already ships against a runtime; **`161`'s standing preconditions are the operational prior art** (headset on before launch, and so on) |
| **X2** | **The projection must come from the runtime, per eye, per frame.** `P2`: four tangents per eye per frame, **never a stored FOV angle** | Already the shape STAGE 6 built to — `guPerspective` cannot express an off-centre frustum, and `222` §2's `[MEASURED]` 30% error is what a stored aspect costs |
| **X3** | **The head pose feeds the STAGE 5 spine, not the renderer.** `P6`: the SIM owns the pose | **The spine is BUILT AND GREEN** — `291`, A2 `stale=0 maxerr=0.000`, A3's detector fired. This is the item that is already paid for |
| **X4** | **Presentation.** Today stereo is ONE framebuffer split in halves (`stereo.c:233`); a runtime wants swapchain images per eye plus a mirror window | The split is proven (`270` §1: two views, two viewports, one display list, one swap). **What changes is where the halves go, not that there are two** |
| **X5** | **Frame timing.** The runtime owns the cadence and predicts display time | `P1`'s clock work is **done and worn** — `277`: `GETV_SIMHZ`, fractional delta, retail world speed at 90 Hz, owner-confirmed |
| **X6** | **The first headset run's gate is INSTRUMENTS, not impressions** | Census both eyes non-zero, `stereo_eyediff` on a grabbed frame, `WORK_OVER=0` at the panel rate. **Ask the wearer what it LOOKS like** (`161`, `159` §5) — and score the arm on the log |

**NOT WORTH DOING IF:** `V3` has not passed. **An XR layer over an unproven eye path is `194`'s
shape again — one missing term, four faults — and it is exactly the "hack later" the owner's
standing clause forbids.**

---

# §C — THE CORRECTNESS GROUPS, CARRIED FORWARD

## ~~GROUP A~~ — **CLOSED.** `299` §9.6, `301`, `302`, `303`. A1-A5 all done; the binary landed and all three repos are committed.

## ~~GROUP B~~ — **CLOSED 2026-09-03, `303` §2.** The dead eye in every level's opening was the VIEWER prop. `GETV_STEREO_REBUILD_VIEWER`, default `1`, in `94cdf01c`. `[REPORTED]`, the owner: *"Yes it does and it loads better than before without all that texture in the left eye"* — **gone, not reduced.** **Do not reopen this group for the polygon: that fault is in frames whose census is `39/39` with `only in eye0 = 0`, and this group was entirely about admission.**

## GROUP C — **THE ONE-EYE POLYGON.** Precondition: none. **HIGH. THE OWNER-VISIBLE DEFECT, AND IT STAYS AT THE TOP OF THIS SECTION UNTIL IT IS GONE.**

**THE SYMPTOM IN THE OWNER'S WORDS:** *"bond bobs and it changes the output"* — a flat slate polygon
occludes wall geometry **in ONE eye**, in `dlgrab_C1_2336`, `dlgrab_V1_2732` and `dlgrab_C1_4676`.

**FOUR LEVELS ARE EXCLUDED BY MEASUREMENT AND EVERY ONE OF THEM IS SOMETHING THE DUMP RECORDS:**

| level | instrument | verdict |
|---|---|---|
| admission — was it submitted | `dlgrab_eyecensus.py` | `39/39`, `only in eye0 = 0` — **excluded**, `303` §5 |
| the matrix conversion | `GETV_STEREO_MTXGUARD` | `already-converted=0` of 366,456 — **excluded**, `303` §4 |
| the arena — who allocated what | `--arena` | identical on clean and polygon frames — **excluded**, `305` §1.2 |
| the order — where it was submitted | `dlgrab_dlorder.py` | order-identical on both polygon frames — **excluded**, `305` §1.5 |

**►►►►►►►► WHAT IS LEFT IS THE ONE THING NO INSTRUMENT HERE HAS EVER READ: THE CONTENTS OF THE
BUFFERS THE COMMANDS POINT AT.** `GETV_DLGRAB` records `w0`/`w1` — opcodes and **addresses**. Two
eyes can issue byte-identical commands naming per-eye matrix buffers whose **values** differ, and
every instrument on this board would call that frame perfect.

| # | task | effort | note |
|---|---|---|---|
| **C1** | **Build the per-eye `MODEL_MTX` CONTENTS read.** `305` §4 | **HIGH** | **Start at `dlgrab_C1_2336`, not `4676`** — `4676` carries a second, measured, dated, HARMLESS defect (the eight-call cyclic rotation by three) and is therefore the frame with the most NOISE, not the most signal. **`301` §0: this is a diagnosis, not a patch, and the count of wrong filed fixes is five** |
| **C1a** | Re-run `GETV_STEREO_MTXGUARD=1` on a route reaching more of the level | **LOW** | `303` §4's zero is **one run and one route** and the board must not read it as a proof about every route |
| **C2** | Decide who owns `render_pos` per eye | **HIGH** | `292` called it a design decision and deferred it; ARM 3 answered half |
| **C3** | **Date the polygon — `V1` + `V2` above.** `304` §2a | **LOW** | **`P1` IS ALREADY RUN AND UNREAD.** `306` §2 |

## GROUP D — **FOLDED INTO GROUP `V`.** `D1` (R3 pairguard) is the one item NOT promoted: with ARM 3 on, its zero means the fault cannot occur, so it is **LOW value, not LOW effort well spent.** `D2`→`V3`, `D3`→`V4`, `D4`→`V5`.

## GROUP E — **`[REPORTED]` AND STILL UNTESTED.** Precondition: none. **MEDIUM.**

| # | task | effort | note |
|---|---|---|---|
| E1 | Arm C's gate: *"the gun disappears on the floor"* (`RUN-SHEET-299` §6) | **LOW** | `bg.c:583`'s `getROOMID_isRendered` has now **survived FIVE arms untested** |
| E1b | The explosion texture | **LOW** to characterise | **Nobody has written down the symptom.** Until someone does it cannot be ranked at all |
| E2 | Bug 1 — the split down the distant facade | HIGH | `GETV_ROOMSCISSOR=0` removes it, but that knob **is not a fix** |
| ~~**E3**~~ **CLOSED 2026-09-04** | **The far clamp: FC3/FC4's verdict** -- `[REPORTED]`, the owner: they *looked the same*. | **FREE** | **`RUN-SHEET-303` §0.1 is a `279` §7 null for the SECOND time and CLOSES.** No prior `[REPORTED]` line carried it, so it was owed until now |

## GROUP F — **PRE-EXISTING CRASHES.** Precondition: none. **HIGH.**

| # | task | effort | note |
|---|---|---|---|
| F1 | The mine crash: `vtxstore.c:161` reads a tagged union as the wrong member | HIGH | `297` §12. **Two candidate corrections and they are NOT equivalent. A NULL guard is worthless — the pointer is WILD.** Proven pre-existing on `goldeneye_PARENT.exe` |

---

# §D — HOLES. **13 OF 20 CLOSED** — `H19` survives `RUN-SHEET-308` §2a, NARROWED; `H20` is new.

**CLOSED:** `H1` `H2` `H3` `H5` `H6` `H7` `H9` `H10` `H13` `H18` `N1` `N2` — the account is `301` §1,
`303` §6, `305` §1.6, `308` §6. **`H7` was closed once and re-opened by `306` §1: it is closed for the C
toolchain and it was NEVER closed for the Python one.**

**►►►►►►►► `H1` AND `H18` — CLOSED 2026-09-04, `RUN-SHEET-308` §1, AND THE FIX IS ONE RELATIVE
FLOOR.** `stereo_disparity.py` prints `confidence  contrast <f>` and refuses any `dx` where
`contrast = (mad_zero - mad_best) / mad_zero < 0.20`, alongside the existing absolute `mz - mb <
0.5` (`B1`). **`[MEASURED]` on the 16 `307` grabs under `py`: four `S3c` refused as `LOW
CONFIDENCE` and nothing else, twelve `S3b` still scored, ALL SIXTEEN `dx` IDENTICAL, `5400` still
`contrast 0.286` / `VERDICT PASS`.** The floor was pre-registered from exactly two arms
(`S3b` >= 0.286, `S3c` <= 0.122) and the falsifier is what filed it -- **it did not rescue a void
frame or kill a real one, which is `301` §0's condition.** `H1`'s peg alarm is NOT the mechanism
that closed it: an out-of-band prediction is necessary and not sufficient, and the interior
spurious peak is what the contrast floor catches.

| # | hole | effort | fix |
|---|---|---|---|
| ~~**H1**~~ **CLOSED 2026-09-04** | **THE PEG ALARM DOES NOT FIRE ON AN OUT-OF-BAND PREDICTION WHEN THE FRAME OFFERS A SPURIOUS IN-BAND PEAK** | **LOW-MED** -- needs a confidence floor, not just an edge test | `[MEASURED]` `307` §1: `dlgrab_S3_5400`, predicted -7,019 px, all four searches returned an INTERIOR `dx` (+351 at `--search 500/800`, +172 at 200, MOVING with search), `mad_best 6.250`/`mad_zero 12.311`, **NO peg line.** `301` §2 rebuilt `measure()` to peg at the edge; a near textured wall gives it an interior escape hatch, so it reports a confident WRONG number instead of pegging. **Couples to `H18`:** refuse a `--predicted-frac` outside the reachable range BEFORE correlating, and/or require the winning `mad` to clear a floor against `mad_zero`. `stereo_disparity.py:261`. **CONFIRMED `307` §2: the mad-ratio floor separates real from void -- `S3b` reads 0.15–0.38, `S3c` (wrong sign) reads 0.88–0.96.** |
| **H4** | **A knob with no banner cannot be checked.** Surveyed; the banner work is open | **MEDIUM** | `knob_banner_survey.py`. **397 knobs, 35 tier A, 35 tier B, 327 silent — 82%.** Work from the script's doc-mention ranking. **Convention: every banner prints the FULL knob name and an `=`** |
| **H8** | Per-half texture energy cannot tell "nothing drawn" from "one huge flat quad" | **LOW** (a rule) | Always read it beside `dlgrab_eyecensus.py`. Neither is sufficient alone |
| **H11** | `[getv][far]` prints knob-dependent `clamped` on one line with knob-independent `beyond_far`/`straddle` | **LOW** | `N1` split the NEAR line and **the far line never got it.** `303` §3 is what that cost |
| **H12** | `[getv][far]` is CUMULATIVE over runs containing two scenes 15x apart | **LOW** | **Applied BY HAND in `305` §2a and still not in the code. A windowed accumulator would have made that section a `Select-String`** |
| **H14** | `grabs_pre_298cull` is 109 BMPs with no admissible provenance, and it blocks a question | **MEDIUM** | `304` §2. **Either reconstruct provenance from the surviving logs, or declare the folder unusable in one line so nobody mines it again** |
| **H15** | `dlgrab_eyecensus.py` compares DL call targets as a **SET**, so a pure reorder reads PERFECT | **LOW** — closed by a sibling tool; the open part is whether it belongs inside the census | `305` §1.3. **`304` §1.2 is the precedent for editing an instrument; `H8` is the argument for keeping two.** `RUN-SHEET-305` §6 |
| **►► H16 (NEW, `306`)** | **AN INSTRUMENT THAT PRINTS OUTSIDE ASCII CAN DIE ON THE OWNER'S MACHINE AND NOT ON THE BRIDGE — AND IT DIES AT THE FINDING, BECAUSE THAT IS WHERE THE EMPHASIS ARROWS ARE** | **LOW** — the five sites are fixed; the RULE is the open part | `[MEASURED]` `order_sweep_305.txt` 23:45:07Z: `UnicodeEncodeError: 'charmap' codec` on `►` at `dlgrab_dlorder.py:93`, **the `PERMUTATION` verdict line**, on the first permuted frame in the corpus. `--selftest`'s check `B` header and **`stereo_disparity.py`'s `H1` peg alarm** are the same shape: **the alarm `H1` was opened to make fire is a line that could not print.** ►► **THE RULE: instrument OUTPUT is ASCII. The docs can have arrows; the tools cannot.** A gate's expected TEXT is part of the gate, so the check count stayed at 7 |
| **►► H17 (NEW, `307`)** | **`ZERO-REBUILD FRAMES` COUNTS A FRAME WITH AN EMPTY PROP LIST AS A FRAME WHERE THE SECOND EYE GOT NOTHING** | **LOW** — the split; **a DIAGNOSIS, not a patch** | `[MEASURED]` `run_306_S3_separation.log`: **2,220 of 7,636**, contiguous frames 1810–4029, **every one `zsnap=0`** (the owner stood still facing a wall with nothing on screen), `eyes-rebuilt=1`, `skipped=0`, `pass-never-ran=0` — **and the gate's own words are "it must be 0", so as written it FAILS A HEALTHY ARM.** `H2`'s instrument with an `H3` defect. **The shape: `zero-rebuild(zsnap>0)` beside `zero-rebuild(zsnap==0)`, the way `N1` split the near line. `301` §0 — the count is five** |
| **►► H19 (`308`, NARROWED BY `309`)** | **`S3b` READS A NEAR-CONSTANT ~`0.69` OF THE PREDICTED DISPARITY AND NOTHING ON THE BOARD KNOWS WHY** | **LOW** offline; **MEDIUM** with the §2b run | `[MEASURED]` `309` §1.1/§5.1/§7 under `py`: median proportional error **`30.76%`** (not `10-13%` — RETRACTED, `00-STATE` §4), and the `measured/predicted` RATIO is **`0.652`-`0.799` over ten mid-band grabs, median `0.692`**. **THE `--patch` LADDER FALSIFIES `RUN-SHEET-308` §2a's DIAGNOSIS: `1.00 / 0.50 / 0.25 / 0.10` give `0.692 / 0.696 / 0.696 / 0.697` — a fifteen-fold narrowing moves it by `0.005`.** Patch averaging over depth is NOT the cause. **What the ladder DID do is eat both outliers** (`10177` `1.129 -> 0.750`, `5400` `1.449 -> 0.634`); at `FRAC 0.25` all twelve lie in `0.634`-`0.814`. **Two candidates killed offline by reading: the eye-width conversion (log `910.34`-`913.45`, `stereo.c` `912.67`, tool `912` — they AGREE) and the log's 1/D law (`frac*D` = `-23.376`-`-23.384` over 687 lines — exact). WHATEVER IS WRONG IS A CONSTANT — see `H20`** |
| **►►►► H20 (NEW, `309`)** | **THE LOGGED FRUSTUM CARRIES A 4:3 TERM THE EYE'S OWN ASPECT DOES NOT ACCOUNT FOR, AND NOBODY HAS CHECKED WHETHER THE RENDERER AGREES WITH IT** | **LOW** — it is a source read, OFFLINE | `[MEASURED]` `309` §6.2 from `run_307_S3b_sep32.log`: eye viewport **`160x180`** n64 units (full width `320`), tangents **`L/R = ∓0.684267`**, **`D/U = ∓0.577350`**, `tanw = 1.368534`. **`0.577350 * (160/180) * (4/3) = 0.684267` EXACTLY** — the horizontal tangent is the vertical times the eye aspect times an extra `4/3`. `geStereoPredict()` (`vendor/ge-decomp/src/game/stereo.c:512`) computes `frac = -sep / (D * tanw)` from it. **A dropped or added 4:3 gives ratios `0.750` or `0.667`; the measurement is `0.692`-`0.697` and BRACKETED BY BOTH, so this is `[HYPOTHESIS]`, NOT a fix (`301` §0 — the count is five).** **THE STEP: read the eye loop's OWN projection and compare it against these logged tangents. If they agree, the constant is elsewhere.** Deciding `0.667` from `0.750` needs the correlator's error bar, which is what `RUN-SHEET-308` §2b measures |
| ~~**H18**~~ **CLOSED** | **THE DISPARITY GATE HAS NO AMPLITUDE CHECK — A PREDICTION CAN BE CORRECT AND UNMEASURABLE** | **LOW** as a run-sheet step (`RUN-SHEET-307` §2.0); **MEDIUM** as the durable form | `[MEASURED]` `307` §1: **−7,024 px predicted on a 912 px eye**, on all seven `S3` grabs and all 109 probe windows, because disparity goes as **1/D** and `separation=500` met `D≈47`. The bound is the **IMAGE EDGE**, not `--search` (`301` §2 selftest C). **The durable form is the game refusing to print a `PREDICTION` it knows is unreachable, or `stereo_disparity.py` refusing a `--predicted-frac` outside its own range** — the same shape as its existing `\|dx\| >= 8` refusal |

---

# §E — WHAT THE NEXT SESSION SHOULD TAKE

**UPDATED 2026-09-04 — `RUN-SHEET-308` §2a IS WORN AND ITS DIAGNOSIS IS FALSIFIED.** `309`.

0. **►►►►►►►► `H20` — READ THE EYE LOOP'S OWN PROJECTION AND COMPARE IT AGAINST THE TANGENTS
   `geStereoPredict()` LOGS. OFFLINE, NO RUN, NO BUILD.** It is the cheapest remaining question and
   it is decisive in one direction: **if the renderer's horizontal frustum differs from the logged
   `tanw = 1.368534`, the prediction has been wrong by that ratio the whole time and `V3` has been
   grading the game against a bad number; if they agree, the constant is somewhere else and the
   candidate dies the way the eye-width one did** (`309` §6.1 — one `grep` closed it).
0a. **`RUN-SHEET-308` §2b — the flat-wall single-depth run. NOW MORE NECESSARY, NOT LESS.** It is
   the only step that measures **the correlator's own error bar**, and without one `0.667` and
   `0.750` cannot be told apart (`309` §6.2). Stand point-blank facing a FLAT textured wall filling
   the whole view, `GETV_STEREO_OFFSET=32`, F9 four or five times. **The only person-cost step.**
0b. **AND IF `V3` EVER CLOSES, `V4` (`S4`, the mode-2 falsifier) RUNS IN THE SAME SITTING** — a
   pass with no negative arm is a claim, not a result (`49`).

**►►►► AND A STANDING RULE FOR WHOEVER TAKES `V3`: IT DOES NOT CLOSE ON `S3b_5400`.** That frame
reads `-16, -10, -7, -7` across the four patch rungs and **passes ±5 px at every one**, because its
prediction is `-11.04` px. **A gate that cannot be failed is not a gate** (`309` §5.2).

1. ~~`RUN-SHEET-306` §1 and §2~~ — **PASSED.** `305` is quotable forward; `H7`'s Python leg closed.
2. ~~§3 — `V1`/`P1`~~ — **DONE.** Nine gameplay frames clean; `P2` showed a whole dead eye. The
   polygon appeared in neither, so `304` §2a cannot date it.
3. ~~§6 — `V3`, `S3`~~ — **GATE 6.1 PASSED; the ±5 px gate has NOT, for three sessions.**
4. ~~`RUN-SHEET-307` §1~~ — ran; the alarm did not fire; `H1` re-opened, then **CLOSED by `308` §1.**
5. ~~`RUN-SHEET-307` §2~~ — ran; `S3b` real but imprecise, `S3c` void.
6. ~~`E3`, the FC3/FC4 sentence~~ — **CLOSED 2026-09-04.** Do not re-ask.
7. ~~`RUN-SHEET-308` §1 — the confidence gate~~ — **WORN. `H1` and `H18` closed together.**
8. ~~`RUN-SHEET-308` §2a — the `--patch` ladder~~ — **WORN 2026-09-04. GATE 2a-ii FAILED: the
   ratio does not move. The diagnosis is FALSIFIED and `H19` is narrowed, not closed.**
9. **`V7`/GROUP `C`** — the per-eye contents instrument, when a session has room for a `HIGH`.

**`169` NEXT ID = `U-26`.**
