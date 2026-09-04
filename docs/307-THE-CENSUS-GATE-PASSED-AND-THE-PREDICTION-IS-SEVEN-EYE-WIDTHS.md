# `307` — `RUN-SHEET-306` IS WORN. THE SEPARATION GATE'S CENSUS PASSED FOR THE FIRST TIME EVER, AND ITS DISPARITY CANNOT BE MEASURED WHERE THE OWNER STOOD

**`[MEASURED]` 2026-09-04.** `RUN-SHEET-306` §1-§6 all run on the main PC, **and §7's two commits
are IN — `22e6b0a` (`GoldenEyeVR`, eight files) and `99d8a63` (`goldeneye-native`, the three-tool
ASCII fix, `5 insertions / 5 deletions`), both trees clean.** Binary unchanged:
`45756E5A…3F92`, 18,070,774 bytes. **One block failed to parse and it was the assistant's — §6.2
contained `<the number from the log>`, and `<` is a reserved operator in PowerShell. `296` §11 with
a new face: a PLACEHOLDER IS NOT A COMMAND.** `RUN-SHEET-307` §1 is the same read with the number
derived from the log by the block itself.

---

## §0 — THE ONE THING TO READ IF YOU READ NOTHING ELSE

| | |
|---|---|
| **1** | **`H7`'s PYTHON LEG IS CLOSED. THE ASCII FIX TOOK AND `305` REPRODUCES EXACTLY.** `order_sweep_306_repro.txt`: **`admission=52  equal=32  permuted=4  refused=168`** over 256 dumps, **zero tracebacks**. Same four permutations, same `span [29..36]`, and the only one among the fourteen `C1`+`V1` dumps is `dlgrab_C1_4676`. **`305` is quotable forward** |
| **2** | **►►►►►►►► GATE 6.1 PASSED ON `dlgrab_S3_5400` — THE FIRST TIME THE SEPARATION GATE'S PRECONDITION HAS EVER BEEN MET.** `viewport loads=2`; **`only in eye0 = 0`**; `MODEL_MTX 81/81`, `MODEL_VTX 49/49`, `MODEL_COL1 73/73`, no `DIVERGES` on any of the three; `eyes-rebuilt=1 chr=2 obj=2 skipped=0`. **Six sessions of "a disparity across a dead eye is a number about nothing" is over** |
| **3** | **►►►►►►►► AND THE DISPARITY STILL CANNOT BE SCORED, FOR A REASON NOBODY HAD LOOKED FOR: THE PREDICTION IS 7.7 EYE-WIDTHS.** At frame 5400 the log's own line reads **`PREDICTION: disparity = -7.696404 x eye_width (= -7024.25 px)`** on an eye half that is **912 px wide.** The correlator cannot represent a shift 7.7x wider than the image it searches. **All seven grabs are out of band: −1500, −1500, −1694, −7024, −7023, −6498, −6202 px** |
| **4** | **THE MEASURABLE WINDOW EXISTED AND IT PASSED 600 FRAMES BEFORE THE FIRST GRAB.** Frames **1380–1800**, `D` 644–1933, predicted **−172 to −517 px** — comfortably inside `--search 500`. **The venue instruction is what put the grabs outside it, and that instruction is `RUN-SHEET-299` §4's own: *"stand still, in a room, FACING A WALL"*** |
| **5** | **THE POLYGON DID NOT APPEAR IN EITHER `P1` OR `P2`, SO `304` §2a CANNOT DATE IT** — and the arms said something else instead, which is item §3 below |
| **6** | **`ZERO-REBUILD FRAMES` COUNTS FRAMES WITH NOTHING TO REBUILD.** `[MEASURED]`: 2,220 of them in this run, **contiguous, frames 1810–4029, every one with `zsnap=0`** — an empty on-screen prop list, because the owner was standing still facing a wall. `eyes-rebuilt=1` throughout. **The gate says this number "must be 0". It is benign here and the gate as written would have failed a healthy arm** |

---

## §1 — ►►►► THE AMPLITUDE PROBLEM, AND WHY IT IS A GATE AND NOT A MISTAKE

`GETV_STEREO_PROBE=60` printed 109 prediction blocks. Every one carries three fixed rungs and one
live one:

```
PREDICTION at D=    1000: disparity = -0.365354 x eye_width (= -333.45 px …)
PREDICTION at D=    4000: disparity = -0.091339 x eye_width (=  -83.36 px …)
PREDICTION at D=   16000: disparity = -0.022835 x eye_width (=  -20.84 px …)
MEASURED centre depth D=47.47 (room 7, engine ray test)
PREDICTION: disparity = -7.696404 x eye_width (= -7024.25 px …)
```

**The disparity goes as 1/D — that is the law the gate exists to test — so a NEAR wall produces an
ENORMOUS prediction.** `255` §4 chose `separation=500` as *"deliberately absurd"* so the mechanism
would be unmistakable, and `RUN-SHEET-299` §4 chose the venue as *"stand still, in a room, facing a
wall"* so the ray test would return a clean depth. **Each choice is right on its own and their
product is unmeasurable.** Per grab, from the prediction block immediately before it:

| grab | `D` | predicted disparity | in band (`\|px\| ≤ ~595`)? |
|---|---|---|---|
| `S3_2400` | 222.28 | **−1500.1 px** | no |
| `S3_2480` | 222.28 | **−1500.1 px** | no |
| `S3_3452` | 196.81 | **−1694.3 px** | no |
| `S3_5400` | 47.47 | **−7024.2 px** | no |
| `S3_5840` | 47.48 | **−7022.8 px** | no |
| `S3_6075` | 51.32 | **−6498.0 px** | no |
| `S3_6857` | 53.76 | **−6202.2 px** | no |

**THE BOUND IS NOT `--search`, IT IS THE IMAGE EDGE.** `301` §2's selftest C says it in the
instrument's own words: at 2560 wide with the play area `[367..2192)`, `--search 800` searches
`[-800..+595]`, *"the upper bound is set by the IMAGE EDGE, not by `--search`."* **A −7,024 px
prediction is not a hard measurement, it is a request the correlator cannot express.**

**►► SO THE ARM IS NOT WASTED AND IT IS NOT A `279` §7 NULL EITHER.** The instrument printed the
number that voids its own measurement **before any correlation was attempted**, on every one of 109
windows, and nobody had ever read that line as a gate. **THE NEW GATE, PRE-REGISTERED IN
`RUN-SHEET-307` §2: read the grabbed frame's own `PREDICTION: disparity = … px` line FIRST and
refuse to score anything whose magnitude exceeds the reachable range.** Same family as `303` §3.2 —
*a venue that maximises the counter can minimise the picture* — one level over: **a venue that
makes the mechanism loud can make it unmeasurable.**

### 1.1 — AND THERE IS A PRE-REGISTERED FALSIFIER SITTING IN THE FOLDER

**`stereo_disparity.py` on `dlgrab_S3_5400.bmp` MUST PEG AND THE `H1` ALARM MUST FIRE.** `H1` was
opened because that alarm had never fired; `301` §2 rebuilt `measure()` so it can; `306` §1 made
its line printable. **This is the first real frame in this project's history where it is REQUIRED
to fire.** If it stays silent on a −7,024 px prediction, `H1` is not closed after all.
`RUN-SHEET-307` §1.

---

## §2 — GATE 6.1: THE PRECONDITION IS MET, AND THAT IS THE RESULT THIS SESSION KEEPS

`[MEASURED]`, `dlgrab_S3_5400.txt`, `GETV_STEREO_OFFSET=500`:

```
=== dlgrab_S3_5400.txt ===  rows=19854  viewport loads=2
  gSPSegment BG_VTX(14)          7       15   +8   <-- DIVERGES
  gSPSegment MODEL_COL1(5)      73       73   +0
  gSPSegment MODEL_MTX(3)       81       81   +0
  gSPSegment MODEL_VTX(4)       49       49   +0
    only in eye0 = 0    only in eye1 = 8
```

and that frame's own rebuild line: **`eyes-rebuilt=1 chr=2 obj=2 view=0 skipped=0`, `zsnap=4`.**

**ALL FOUR CONDITIONS OF GATE 6.1 PASS.** `BG_VTX 7 vs 15` is not one of them and is not a
failure: **at a 500-unit separation the two eyes see different background geometry, which is the
point of the arm.** `only in eye1 = 8` is the same fact from the call side — **eye 1 calls eight
lists eye 0 does not, and the gate's test is `only in eye0 = 0`, which is what a strict subset
would break.**

**►► THIS IS THE SENTENCE THAT MOVES:** *"a disparity measured on an eye with no world in it is a
number about nothing"* has been the reason `S3` was deferred since `297`. **It is now measured
false on this frame.** The gate that remains is amplitude, and amplitude is a venue choice.

---

## §3 — `304` §2a: THE POLYGON DID NOT APPEAR IN EITHER ARM, AND `P2` MEASURED SOMETHING ELSE

**`P1` (`GETV_STEREO_REBUILD_VIEWER=1`), nine gameplay frames 1225–1391: ALL NINE CLEAN.**
Totals 0, 0, 0, 0, 0, 1, 0, 152, 1 px; **largest blob 15 px** at worst, against the corpus's clean
ceiling of 715 px and its smallest true hit of 1,967 px (`304` §1.3).

**`P2` (`GETV_STEREO_REBUILD_VIEWER=0`), nine gameplay frames 1218–1439: FOUR MEASURED, FIVE
REFUSED, AND THE FOUR ARE CATASTROPHIC.** 523,554 / 469,111 / 576,312 / 576,312 px.
**The five refusals are the instrument's own guard doing its job** — `dx +8 px`, and it refuses at
`|dx| >= 8` because *"this is not a `GETV_STEREO_OFFSET=0` run"* — which is `279` §7 written into
the tool.

**AND THE CENSUS SAYS WHAT THE FOUR ARE.** `dlgrab_P2_1369.txt`:

```
  gSPSegment MODEL_COL1(5)      19        0   -19   <-- DIVERGES
  gSPSegment MODEL_MTX(3)       38        0   -38   <-- DIVERGES
  gSPSegment MODEL_VTX(4)       16        0   -16   <-- DIVERGES
    only in eye0 = 18    only in eye1 = 0   <-- eye1 is a STRICT SUBSET
```

**That is the DEAD EYE, exactly `302`'s signature, reproduced with the fix off — and in GAMEPLAY,
not only in the level's opening.** `302` measured the viewer skip over ~541 opening frames; here at
frames 1309–1439 the second eye receives **nothing at all**, because the prop list in those frames
is short enough that the viewer is most of it.

**►►►► SO THE READING OF GATE §2a IS A ROW THAT IS NOT IN ITS TABLE, AND SAYING SO IS THE POINT.**
The table pairs "concentrated hit" against "concentrated hit". **What came back is `P1` NONE
against `P2` DEAD EYE.** Two conclusions, and only the first was asked for:

1. **`304` §2a CANNOT DATE THE POLYGON, BECAUSE THE POLYGON DID NOT APPEAR.** Eighteen gameplay
   grabs across two arms and not one carries it. **It is rarer than `C1`'s three-in-seven
   suggested**, and `C1_2336`, `V1_2732` and `C1_4676` remain the only three instances this
   project owns. **The dating question is still open and the archive still cannot answer it.**
2. **`303` §2's FIX IS NOW MEASURED IN GAMEPLAY AND NOT ONLY IN THE OPENING.** Nine frames clean
   with it on, four frames with a whole dead eye with it off, same walk, same level, same binary.
   **That is a stronger statement than GROUP `B`'s closure was, and it was free.**

### 3.1 — AND A CORRECTION TO THE METRIC THAT WAS SUPPOSED TO SEPARATE THEM

**`P2_1369` reads `blobs 1`, largest blob `576312` of `576312` total — 100% CONCENTRATION, which
is the POLYGON's signature by `304` §1.4's statistic.** Its bbox is `x[12..899] y[172..820]`:
**the entire unmasked eye.**

**SO CONCENTRATION DOES NOT SEPARATE THE TWO FAULTS AND `304` §1.4's 5%/8% DEAD-EYE FIGURES DO NOT
GENERALISE.** They were measured on `S2_1176` and `S3_1155`, two *opening* frames where eye 1 is
partly populated and the difference scatters. **A fully dead eye is one solid blob at 100%.**
**MAGNITUDE IS WHAT SEPARATES THEM:** the polygon is tens of thousands of pixels
(`C1_2336` 44,252 over 900 blobs at 38%; `V1_2732` and `C1_2336` 79–86% largest), a dead eye here
is **half a million.** `304` §1.3's rule applies to its own successor: **a calibration on the
frames you already understand is a hypothesis.**

---

## §4 — `ZERO-REBUILD FRAMES` COUNTS "NOTHING TO DO" AS "DID NOTHING"

`[MEASURED]` over all 7,636 summary lines of `run_306_S3_separation.log`:

- **cumulative `ZERO-REBUILD FRAMES` = 2,220 of 7,636**, and the gate's own words are *"it must be
  0 — or every non-zero one must be accounted for by `pass-never-ran`"*. **`pass-never-ran` is 0.**
- **All 2,220 are CONTIGUOUS, frames 1810–4029, and every one reads `zsnap=0`** — the on-screen
  prop list was **empty** — with `eyes-rebuilt=1` and `skipped=0` throughout.
- Outside that window, `zsnap` runs 1..10 and **not one frame is zero.**

**THE WINDOW IS EXPLAINED BY THE ARM ITSELF: the owner was standing still facing a wall, as
`RUN-SHEET-299` §4 instructs, with nothing on screen to rebuild.** Rebuilding nothing from an empty
list is correct behaviour, and three of the seven grabs (`2400`, `2480`, `3452`) were taken inside
it.

**►► SO THE COUNTER CANNOT DISTINGUISH "THE SECOND EYE GOT NOTHING" FROM "THERE WAS NOTHING TO
GIVE IT", AND THE GATE THAT READS IT WOULD HAVE FAILED A HEALTHY ARM.** This is `H2`'s own
instrument carrying an `H3`-shaped defect — **the number is right and the LINE invites the
misread** — and it is filed as `H17`, **a diagnosis and not a patch** (`301` §0, the count is
five). The shape a fix would take is a split: `zero-rebuild(zsnap>0)` beside
`zero-rebuild(zsnap==0)`, the way `N1` split the near line.

---

## §5 — WHAT DID NOT CHANGE

- **`305` stands in full and is now quotable forward** — §1's four gates and §2's reproduction
  passed on the main PC under `py`.
- **The polygon has no new explanation.** `305` §4's per-eye `MODEL_MTX` CONTENTS instrument is
  still the only level left, still undesigned, and `C1` is still aimed at `dlgrab_C1_2336`.
- **The binary is untouched. Nothing was staged, committed, branched or tagged by the assistant.**
- **The FC3/FC4 sentence is still owed** — `RUN-SHEET-306` §5, and it is still the only item on the
  board that costs nothing but a person.

---

## §6 — WHERE THE WORK GOES

1. **`RUN-SHEET-307` §1** — the corrected disparity read, with the fraction derived from the log by
   the block. **Its purpose is no longer to score `S3`: it is the pre-registered first firing of
   the `H1` peg alarm on a real frame.**
2. **`RUN-SHEET-307` §2 — `S3b` and `S3c`, the two arms that land in band**, and the amplitude gate
   that refuses anything out of it. **Two different `(separation, D)` pairs measuring the same law
   is the 1/D test taken with PIXELS instead of printed.**
3. **`RUN-SHEET-307` §3** — the main-PC confirmation of §3's `P1`/`P2` readings, **redirected to
   files, because console-only output is invisible to an offline assistant and this session read
   its eyediff numbers on the bridge.**
4. **`H17`** — the zero-rebuild split.
5. **The polygon's date is still open** and the archive still cannot settle it (`H14`).
