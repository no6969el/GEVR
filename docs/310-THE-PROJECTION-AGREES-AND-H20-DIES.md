# `310` — **`H20` DIES, THE FLAT WALL IS WORN, AND THE UNDER-READ IS CORNERED IN ONE PLACE: THE SEPARATION THAT REACHES THE IMAGE IS `0.705` OF THE ONE REQUESTED**

> **PART ONE (§0-§6) IS OFFLINE AND CLOSED `H20`. PART TWO (§7-§10) IS `RUN-SHEET-310` §2 WORN ON
> THE MAIN PC, AND IT KILLED THE OTHER TWO CANDIDATES.** Read §0, then §7, §8 and §9.

**NOTHING BUILT, STAGED OR COMMITTED. Binary UNCHANGED.** One owner run (§7); everything else is a
source read on the bridge plus arithmetic, and every arithmetic line is
marked as arithmetic (`309` §7.1's rule, first application).

---

## §0 — WHAT THIS SESSION ESTABLISHED, IN ONE TABLE

| | |
|---|---|
| **1** | **`NEXT-SESSION-PROMPT-310`'S FIRST COMMAND WAS RUN AND `309`'s COMMIT IS IN.** `[MEASURED]` 2026-09-04 on the bridge: `goldeneye-native` HEAD **`5b741b3`** (`instr(309): stereo_disparity.py takes --patch FRAC`), `GoldenEyeVR` HEAD **`6180134`** (`docs(309): …`). The honest expectation in the prompt was a dirty tree; it is wrong, and this is the FIRST session in four whose opening sentence about git was pessimistic rather than optimistic |
| **2** | **BUT THE TREES ARE NOT CLEAN, AND WHAT IS DIRTY IS NOT THIS SESSION'S AND NOT `309`'s.** `[MEASURED]`: `-- repo/docs` reports **58 tracked files modified**, `182 insertions / 121 deletions`, and the change on every sampled one is the SAME: `C:\Users\<USER>\…` rewritten to `C:\Users\<USER>\…`. **It is a username scrub, it predates this session, and NOTHING IN THIS SESSION'S COMMIT MAY SWEEP IT UP.** §6 |
| **3** | **►►►►►►►► `H20` IS ANSWERED AND IT DIES. THE RENDERER'S HORIZONTAL FRUSTUM AND THE LOGGED TANGENTS ARE THE SAME FOUR FLOATS, WRITTEN BY ONE FUNCTION.** `geStereoBuildFrustumF()` (`stereo.c:255-311`) computes `tL/tR/tD/tU`, writes the projection matrix `fr.c:776` installs, **and stashes those same floats into the file statics `ge_st_tL…ge_st_tU` (`stereo.c:310`) that `geStereoPredict()` reads at `:487`.** There is no second projection and no path by which they can disagree |
| **4** | **►►►►►►►► AND THE 4:3 TERM IS NOT UNACCOUNTED FOR. IT IS `bondview2.c:8657`, STOCK RETAIL CODE.** `[ARITHMETIC, exact]`: `(320/180) * 0.75 * (16/9) = 2.370370` (the 16:9 branch of `set_cur_player_aspect`), halved once by `geStereoEyeAspect()` (`stereo.c:197`) to `1.185185`, times `tU = 0.577350` gives **`0.684267`** — the logged value, to six decimals. `0.75 * 16/9` **IS** the `4/3`. `309` §6.2's arithmetic was right and its word "unaccounted" was wrong; `00-STATE` §4 carries the retraction |
| **5** | **►►►►►►►► AND THE KILL IS STRONGER THAN THE COMPARISON ASKED FOR: AN ERROR IN `tR` CANNOT PRODUCE THE RATIO AT ALL, BECAUSE `tR` CANCELS.** `[ARITHMETIC]` The matrix maps world x to NDC through `mf[0][0] = 2/(tR-tL) = 1/tR`; the prediction divides by `tanw = tR-tL = 2*tR`. **The same `tR` appears in the drawn image and in the predicted number, so any factor wrong in it — `4/3`, `3/4`, or anything else — divides out of `measured/predicted` exactly.** The whole `H20` family is dead, not just the version that was checked |
| **6** | **THE PIXEL SCALE RE-CONFIRMS FROM A SECOND, INDEPENDENT DIRECTION.** `[ARITHMETIC]` from `gfx_pc.c:424-447` with `configWidescreen = 0`: `ge_scale() = min(2560/320, 1369/240) = 5.704167`, so the play area is `320 * 5.704167 = 1825.33` px — **byte-for-byte the `GE_STEREO_MANDATED_PLAYAREA_PX 1825.333f` constant at `stereo.c:450`** — and the eye is `160 * 5.704167 = 912.67` px. `309` §6.1 killed the eye-width candidate from the LOG; this kills it from the RENDERER |
| **7** | **THREE CANDIDATES WERE NAMED (§4) AND THE FLAT-WALL RUN KILLED TWO OF THEM THE SAME DAY.** §7-§8 |
| **8** | **►►►►►►►► `RUN-SHEET-310` §2 IS WORN. THE CORRELATOR IS ACCURATE TO ~2% AND THE UNDER-READ IS REAL.** `[MEASURED]` six admissible grabs on a flat wall over a **6.7-fold** depth range: ratios `0.6921`-`0.7184`, **mean `0.7051`, spread `0.026`** — and most of that spread is `dx` being an integer. **CANDIDATE `C` (a biased correlator) IS DEAD** and the instrument is exonerated. §7 |
| **9** | **►►►►►►►► AND CANDIDATE `B` (a short depth) DIED OFFLINE, FROM THAT RUN'S OWN LOG.** `[MEASURED]` 28 pairs of consecutive probe lines at unchanged facing: `-dD / (camera displacement along look)` = median **`1.0053`**, range `0.998`-`1.024`. **`D` tracks the camera one for one.** An additive offset is excluded separately, because it would make the ratio swing with depth and the ratio is FLAT. §8 |
| **10** | **►►►►►►►► SO `A` OWNS IT: THE SEPARATION THAT REACHES THE DRAWN IMAGE IS `~22.6` GAME UNITS, NOT `32`.** Every other link is now measured sound — frustum, 4:3, `tR`, pixel scale (three ways), depth, correlator. **STILL NOT FILED, STILL NOT PATCHED, COUNT STAYS AT FIVE.** §9 |
| **11** | **AND `0.750` / `0.6667` ARE DEAD A SECOND TIME, ON DATA THIS TIME.** `[ARITHMETIC]` they sit `0.045` and `0.038` from the mean while the whole spread is `0.026`. **`309` §6.2 could not separate them; this run excludes both** — independently of item 5's structural kill |
| **12** | **ONE DEFECT IN THIS SESSION'S OWN SHEET, AND IT IS FILED: `RUN-SHEET-310` §3 CARRIED NO ADMISSIBILITY GATE**, so grab `2917` (`predicted -503.85` px against a `[-500..+500]` search) was SCORED instead of REFUSED and its `0.449` was received as an outlier. **It is `H18`, it is `RUN-SHEET-307` §2.0's existing rule, and it cleared the confidence floor at `contrast 0.733` while being unmeasurable.** §7.2 |

---

## §1 — THE READ, END TO END. `[MEASURED, BRIDGE]` — FILE AND LINE FOR EVERY LINK

The question `PRIORITY-BOARD-309` §E item 0 asked was: *does the eye loop's own projection agree
with the tangents `geStereoPredict()` logs?* The chain, in the order the frame walks it:

1. **`lv.c:818-841` — the eye loop.** For each eye it calls `geStereoBeginEye()`, then
   `geStereoEyeViewport()`, which halves the player rectangle and **stashes `ge_st_eye_w/h/full_w`
   for the log** (`stereo.c:226-236`).
2. **`lv.c:868-877` — the eye's aspect.** `geStereoEyeAspect(ge_a, &ge_eye_a)` returns
   `full * 0.5f` (`stereo.c:197`) and the result goes to `set_cur_player_aspect()`, which is the
   ONE place that decides it — the comment at `lv.c:858` says so and `292` S2 is why.
3. **`fr.c:753-779` — the projection.** `guPerspectiveF()` runs first and unconditionally (it owns
   `g_viPerspNorm`); then `geStereoBuildFrustumF(g_viProjectionMatrixF, fovy*gePortFovScale(),
   g_ViBackData->aspect, znear, zfar)` **overwrites that same float matrix.**
4. **`fr.c:783-789`** — `guMtxF2L()` converts it and `gSPMatrix(… G_MTX_PROJECTION)` loads it.
   **That matrix, and no other, is what the RSP path draws the eye with.**
5. **`stereo.c:271-274`** — inside the builder: `tU = tan(fovy/2)`, `tD = -tU`,
   **`tR = tU * aspect_eye`**, `tL = -tR`, with `aspect_eye = aspect_full` because *"lv.c halved
   it once"* (`stereo.c:264-268`).
6. **`stereo.c:301-310`** — the matrix is written from those four tangents **and then
   `ge_st_tL = tL; ge_st_tR = tR; … ge_st_tvalid = 1;`**.
7. **`stereo.c:487`** — `geStereoPredict()` computes `tanw = ge_st_tR - ge_st_tL` **from those
   statics**, and refuses to print at all if `ge_st_tvalid` is 0 (`:481-488`).

**►►►► THEREFORE THE COMPARISON `H20` ASKED FOR IS AN IDENTITY, NOT A MEASUREMENT.** The renderer
and the prediction do not merely agree; they are the same four numbers, produced once per eye per
frame by one function and read by the other from that function's own statics. **`H20`'s "if they
DIFFER" branch does not exist in this source tree.**

### 1.1 — AND THE EYE TRANSLATION IS WHERE `255` §1 SAYS IT IS

`geStereoOffsetCameraPos()` (`stereo.c:333-423`) is called from **`bondview2.c:8958`, once, on
`cam_pos` only**, after `gePortCamInterp()`'s swap and before every matrix in that function is
built from `cam_pos`. **So the separation is in the VIEW, the frustum is symmetric under
`MODE=1`** (`stereo.c:284-295` shifts the tangents only under `MODE=2`, the `B1` falsifier),
**and the prediction's `-sep / (D * tanw)` is the right formula for what the code does.**

---

## §2 — THE 4:3 IS RETAIL, AND HERE IS WHERE IT COMES FROM

`bondview2.c:8655-8662`:

    if (get_screen_ratio() == SCREEN_RATIO_16_9)
        faspect = (viewportWidth / viewportHeight) * 0.75f * WIDESCREEN_ASPECT;
    else
        faspect = viewportWidth / viewportHeight;

with `WIDESCREEN_ASPECT = 16/9` (`fr.h:8`). `0.75 * 16/9 = 4/3` **exactly**, and that is the whole
of `309` §6.2's mystery factor.

`[MEASURED]` from `run_307_S3b_sep32.log`, 229 identical `eye viewport` lines, one distinct value:
**`160x180`, full width `320`, `L/R = -/+0.684267`, `D/U = -/+0.577350`, `tanw = 1.368534`.**

`[ARITHMETIC]`, and every step is a source line, not a guess:

| step | source | value |
|---|---|---:|
| the view's own rectangle | `320x180` (logged) | `1.777778` |
| the retail 16:9 conversion | `bondview2.c:8657`, `* 0.75 * 16/9` | `2.370370` |
| this eye's half | `stereo.c:197`, `* 0.5f` | `1.185185` |
| `tU` at `fovy = 60` | `stereo.c:271` | `0.577350` |
| **`tR = tU * aspect_eye`** | `stereo.c:273` | **`0.684267`** |

**It reproduces the logged tangent to six decimals with no free parameter.** Note that the eye's
`160/180 = 0.888889` and the `4/3` are not two separate facts: `0.5 * (320/180) * (4/3)` and
`(160/180) * (4/3)` are the same product written two ways, which is why `309` §6.2's exact hit
looked like a coincidence and was not.

### 2.1 — WHETHER THAT ASPECT IS *CORRECT* IS A DIFFERENT QUESTION, AND IT IS NOT THIS ONE

The 16:9 branch is stock code written for a `320x240`-shaped viewport; this build feeds it a
`320x180` one. **That may well distort the picture.** It cannot distort the *ratio* this board
cares about, for the reason in §0 item 5: `tR` divides out. **Do not file it, do not "fix" it, and
do not let it be measured by the disparity gate — it is a PICTURE question and the instrument for
it is a screenshot, not a correlator.**

---

## §3 — WHAT THIS SESSION IS ALLOWED TO CLAIM

- **`H20` IS CLOSED, NEGATIVE.** The renderer's horizontal frustum and the logged tangents are the
  same floats by construction. `[MEASURED]`
- **The 4:3 term is accounted for: `bondview2.c:8657`'s `0.75 * 16/9`.** `[ARITHMETIC, exact]`
- **No error in `tR` — of any size — can produce the `~0.69` ratio, because `tR` cancels between
  the drawn image and the prediction.** `[ARITHMETIC]`
- **The pixel scale `912.67` is confirmed a second time, from `gfx_pc.c` rather than from the log.**
  `[ARITHMETIC]`
- **`H19` IS UNCHANGED AND UNEXPLAINED.** The under-read is still a near-constant `~0.69`, and
  after this session there is one fewer place it can live. `[MEASURED]`, `309`
- **`V3` / `258` STAGE 6 DOES NOT CLOSE**, and it still must never close on `S3b_5400` (`309` §5.2).

**THIS IS A NEGATIVE RESULT AND IT IS THE THIRD SESSION IN A ROW WITH THAT SHAPE. IT COST THE
OWNER NOTHING** — no build, no run, no commit until §5.

---

## §4 — WHERE THE CONSTANT CAN STILL LIVE. **THREE CANDIDATES, NONE FILED, UNRANKED ON PURPOSE**

`measured / predicted = 0.692`-`0.697` on the mid-band, `0.634`-`0.814` over all twelve (`309`
§5.1). `predicted_px = -sep / (D * tanw) * 912.67`. §1 and §2 remove `tanw` and `912.67`. **What is
left is `sep`, `D`, and the correlator** — and `[ARITHMETIC]` the ratio implies exactly one of:

| # | candidate | what would have to be true | how it gets tested |
|---|---|---|---|
| **A** | **the applied separation is not `32`** | the view matrix moves the eye by `~22.2` game units, not `32` — `0.692 * 32` | offline read of the `MODE=1` path is DONE (§1.1) and shows `±sep/2` with a pose that is identity in-game; **the next step is an instrumented print of the actual `out->x/y/z` delta, not another read** |
| **B** | **the measured depth `D` is short by `~1.445x`** | `bgTestBulletHitBackground()` + `get_room_data_float1()` return a depth in units the separation is not in | a flat-wall grab where the true distance is knowable independently — **which is `RUN-SHEET-308` §2b** |
| **C** | **the correlator reads low by `~30%` on multi-depth scenes** | the whole-eye cross-correlation is biased toward the background on any frame that is not single-depth | **`RUN-SHEET-308` §2b measures exactly this, and it is the only one of the three that is measured by a run already on the board** |

**NO CANDIDATE IS FILED AND NO NUMBER IS TO BE "CORRECTED" INTO BAND.** `301` §0, the count is
five, and `309` is the case for the rule. **`B` and `C` are BOTH answered by the same five-minute
run, which is why §5's recommendation is that run and not another read.**

---

## §5 — WHAT NEEDS A PERSON

- **`RUN-SHEET-308` §2b — the flat-wall single-depth grab. `LOW`, ~5 minutes, NO BUILD.** It is now
  the only thing on the board that can move `H19`, and it discriminates candidate `C` from `B`.
  The block is `RUN-SHEET-310` §2b (this session's, filed rather than improvised — `308` §0's rule).
- **The commit** (§6), this session's own paths only.
- **`E3` (FC3/FC4) is CLOSED.** Do not re-ask.
- **DO NOT START GROUP `C` / `V7`** — `HIGH`, `PRIORITY-BOARD-310` §E item 9.

---

## §6 — THE COMMIT. **TWO REPOS. OWNER-RUN. AND THERE IS A TRAP IN THE DOCS TREE THIS TIME**

**►►►►►►►► `repo/docs` CARRIES 58 MODIFIED TRACKED FILES THAT ARE NOT THIS SESSION'S AND NOT
`309`'s.** `[MEASURED]`: `182 insertions / 121 deletions`, and every sampled hunk is
`C:\Users\<USER>\…` → `C:\Users\<USER>\…`. **A username scrub.** It may be entirely wanted — but it
is a SEPARATE change with a SEPARATE reason, and **`307` §5's sixteen strays are what an
undisciplined stage costs.** The block below therefore names **five paths and no wildcards**, and
`309`'s own two scratch files (`getv/tools/_patch309.py`, `getv/tools/ladder_driver.py`) stay out
of it. **`ladder_driver.py` is worth keeping if the ladder will be re-run — say so deliberately,
do not let a sweep decide it.**

The blocks are supplied in the assistant's message with this document, complete, per `00-STATE`
§7a. **`git add` is not bridge-safe; the assistant has staged nothing and will stage nothing.**

---

## §7 — `169` NEXT ID = `U-26`. **UNCHANGED — THIS SESSION FILED NO UNKNOWN.**

---

# ►►►►►►►► PART TWO — **`RUN-SHEET-310` §2 IS WORN. `B` AND `C` ARE BOTH DEAD AND `A` OWNS IT.**

**`[MEASURED]` 2026-09-04, MAIN PC, `run_310_S3d_flatwall.log` + `disp_310_S3d.txt`, seven grabs,
`ARM S3d grabs=7 preds=131 dls=7`.** Read back from the files on the bridge, not from a paste.

## §7 — THE FLAT-WALL LADDER, AND THE ERROR BAR NOTHING ON DISK HAD

| frame | `D` | `predicted px` | `dx` | **ratio** | integer quantization | admissible? |
|---|---:|---:|---:|---:|---:|---|
| `2917` | `42.32` | **`-503.85`** | `-226` | **`0.449`** | `±0.10%` | **NO — `\|pred\| > 500`** |
| `5114` | `75.84` | `-281.17` | `-202` | **`0.7184`** | `±0.18%` | yes |
| `5792` | `178.35` | `-119.57` | `-85` | **`0.7109`** | `±0.42%` | yes |
| `6371` | `273.70` | `-77.91` | `-55` | **`0.7059`** | `±0.64%` | yes |
| `6923` | `422.18` | `-50.51` | `-35` | **`0.6929`** | `±0.99%` | yes |
| `7380` | `459.06` | `-46.45` | `-33` | **`0.7104`** | `±1.08%` | yes |
| `7747` | `508.96` | `-41.90` | `-29` | **`0.6921`** | `±1.19%` | yes |

**SIX ADMISSIBLE GRABS: `0.6921` to `0.7184`, median `0.7081`, mean `0.7051`, TOTAL SPREAD
`0.026` (±1.9%) ACROSS A 6.7-FOLD RANGE OF DEPTH.** `[MEASURED]`

**►►►► AND THE ERROR BAR IS SMALLER THAN THE SPREAD, BECAUSE MOST OF THE SPREAD IS `dx` BEING AN
INTEGER.** `[ARITHMETIC]` at `dx = -29` a single pixel is `1.2%`; the two grabs with the largest
disparities and therefore the least quantization (`5114`, `5792`) read `0.7184` and `0.7109`.
**THE CORRELATOR IS GOOD TO ABOUT 2% RELATIVE, AND BETTER THAN THAT WHERE THE DISPARITY IS LARGE.
That is the number `RUN-SHEET-308` §2b existed to produce and nothing on disk had ever measured.**
`[MEASURED]` — every grab cleared the confidence floor with room to spare (`contrast` `0.478` to
`0.891`, floor `0.20`), which is `[PREDICTION] 1d` landing.

### 7.1 — **CANDIDATE `C` IS DEAD.**

`310` §4 candidate `C` was *"the whole-eye correlator reads low by ~30% on scenes that are not
single-depth."* **These scenes ARE single-depth, and it still reads `0.705`.** The pre-registered
table in `RUN-SHEET-310` §4 gave this outcome its meaning before the run: *"ratios cluster near
`0.69`, spread small → `C` DIES."* **`[MEASURED]`, and the instrument is exonerated: it is
accurate to ~2% and it is reporting a real 30% under-read.**

### 7.2 — ►►►►►►►► **AND `2917` IS NOT AN OUTLIER. IT IS INADMISSIBLE, AND IT IS A DEFECT IN THIS SESSION'S OWN SHEET.**

`[MEASURED]`: `predicted -503.85 px`, and the tool's own line reads
`searched [-500 .. +500] px`. **THE PREDICTION IS OUTSIDE THE RANGE THE CORRELATOR CAN EXPRESS, BY
4 px.** That is `H18` exactly — `00-STATE` §6, *"a prediction can be correct and unmeasurable, and
the instrument prints the number that says so before anything is correlated"* — and
**`RUN-SHEET-307` §2.0 already requires `|px| <= 500`.**

**`RUN-SHEET-310` §3 DID NOT CARRY THAT CHECK, SO THE GRAB WAS SCORED INSTEAD OF REFUSED, AND ITS
`0.449` WAS RECEIVED AS AN "OUTLIER — VERY CLOSE".** It is neither an outlier nor about being
close: **it is a number the instrument was never able to give.** `00-STATE` §4 carries it.

**AND THE PART THAT MATTERS BEYOND THIS GRAB: IT CLEARED THE CONFIDENCE FLOOR AT `contrast
0.733`** — higher than four of the six admissible grabs. **`308`'s floor was filed as the defence
against a confident wrong number, and here is a confident wrong number it does not catch.** It was
never designed to: the floor asks whether a peak is well-defined, and `H18`'s amplitude gate asks
whether the answer is *expressible*. **THE TWO ARE NOT SUBSTITUTES AND THE SHEET TREATED THEM AS
IF THEY WERE.** `H18`'s durable form — the tool refusing an out-of-range `--predicted-frac` itself
— is now the third session in a row where its absence cost something.

## §8 — **CANDIDATE `B` IS DEAD TOO, AND IT DIED OFFLINE, FROM THIS RUN'S OWN LOG**

`B` was *"the measured depth `D` is short by ~`1.42x`."* **The log answers it without a second run.**
`[MEASURED, BRIDGE]` over `run_310_S3d_flatwall.log`'s **131** probe lines carrying a measured `D`:
for every consecutive pair where the facing is unchanged (`look . look >= 0.9995`) and the camera
actually moved, compare the displacement projected onto the look vector against the change in `D`.

**28 usable pairs. `-dD / (displacement along look)` = median `1.0053`, range `0.998` to `1.024`.**

**`D` TRACKS THE CAMERA'S OWN TRANSLATION ONE FOR ONE, TO BETTER THAN 1%.** A `1.42x` scale error
is excluded by a factor of thirty.

**AND AN ADDITIVE OFFSET IS EXCLUDED BY A DIFFERENT ARGUMENT, WHICH IS WHY THE LADDER MATTERED:**
`[ARITHMETIC]` if `D_used = D_true - c`, the ratio would be `1 - c/D_true` and would **swing with
depth** — from `D = 76` to `D = 509` it could not stay inside `0.026`. **It is flat. There is no
offset and there is no scale.** `[MEASURED]`

### 8.1 — AND THE LAST COMMON-MODE SUSPECT DIED IN THE SAME PASS

Before blaming the view path, the pillarbox: if `stereo_disparity.py` split the raw `2560` px
screenshot in half, each half would carry an identical black bar, and a large zero-disparity
region pulls a correlation peak toward zero **multiplicatively** — which would look exactly like
this. **`[MEASURED]` it does not.** The tool auto-detects the play area from the non-black columns
(`stereo_disparity.py:59, 82`) and every one of the seven grabs prints
`play area x=[367..2192) width=1825 borders L=367 R=368` and `eye half 912 px`, identical.
**The bars are excluded, `half` is derived and not assumed, and `pred_px = pred_frac * half` uses
that same derived number** (`:296`). **The pixel mapping is sound for the third time, now from the
image itself.**

## §9 — ►►►►►►►► WHAT IS LEFT IS **`A`**, AND IT IS ONE SENTENCE

**EVERY OTHER LINK IN THE CHAIN IS NOW MEASURED SOUND:** the frustum (§1, identity), the 4:3 (§2,
retail), `tR` (§0 item 5, cancels), the pixel scale (§0 item 6 and §8.1, three ways), the depth
(§8, 1:1 over 28 pairs), the correlator (§7, ~2%).

**►►►► SO THE SEPARATION THAT REACHES THE DRAWN IMAGE IS `0.705` OF THE `32` THAT WAS ASKED FOR —
ABOUT `22.6` GAME UNITS — AND NOTHING ON THE BOARD KNOWS WHY.** `[MEASURED]`, and it is stated as
a measurement of the SYSTEM, not as a diagnosis of a LINE. **NO PATCH. THE COUNT OF WRONG FILED
FIXES STAYS AT FIVE.**

**AND THE TWO OLD CANDIDATE RATIOS ARE NOW DEAD A SECOND TIME, ON THE DATA RATHER THAN ON THE
ARGUMENT:** `[ARITHMETIC]` `0.750` is `0.045` from the mean and `0.6667` is `0.038` from it, while
the entire six-grab spread is `0.026`. **`309` §6.2 could not tell them apart; this run excludes
BOTH.** That agrees with §0 item 5's structural kill and was reached independently of it.

### 9.1 — WHAT `A` MEANS FOR `V3`, SAID PLAINLY

`[ARITHMETIC]` with a constant `0.705`, `V3`'s `±5 px` gate can only pass where
`0.295 * |predicted| <= 5`, i.e. **`|predicted| <= 17 px`** — which is why `S3b_5400` (predicted
`-11.04`) is the only frame that has ever passed it and why `309` §5.2 called that unfalsifiable.
**`V3` / `258` STAGE 6 CANNOT CLOSE UNTIL `A` IS FOUND. It is not a tuning problem and no venue
fixes it.**

## §10 — THE NEXT TWO STEPS, AND BOTH ARE `LOW`

Filed as blocks in **`RUN-SHEET-311`**, not cited (`308` §0):

1. **THE SEPARATION SWEEP — `LOW`, NO BUILD, ~5 MINUTES.** `A` says `measured = 0.705 x predicted`
   **for every `sep`**. Re-grab the same wall at `GETV_STEREO_OFFSET` `32 / 64 / 128`. **A constant
   ratio confirms a pure scale factor on the separation and rules out any additive or saturating
   term; a ratio that moves with `sep` is a different animal and outranks everything.** It also
   shrinks the quantization error by 2x and 4x, which sharpens the constant itself.
2. **THE `MODE=2` DISCRIMINATOR — `LOW`, NO BUILD, ~5 MINUTES.** `GETV_STEREO_MODE=2` puts the
   shift in the **PROJECTION** and never touches the view matrix (`stereo.c:284-295`), and it is
   tuned to agree with a real separation at `D = 1000`. **Grab at `D ~= 1000` under `MODE=2`: if it
   reads `1.00` the loss is in the VIEW path specifically, which is where `A` lives; if it also
   reads `0.705` the loss is common to both paths and something this session believes it has
   cleared is not clear.** A falsifier for `A`, not a fix for it.

**THE INSTRUMENTED PRINT of the actual applied `|eye_pos - centre_pos|` is the obvious third step
and it needs a BUILD, which makes it `MEDIUM`. Do the two `LOW` runs first — they may name the
factor without one.**
