# `317` — **`V3` PASSES SIX OF SIX AND `V4` DID NOT FIRE — AND THE `GATE 4b` I WROTE COULD NOT PRINT, ON ANY ARM**

**2026-09-05.** OFFLINE ASSISTANT. **NOTHING BUILT, STAGED, BRANCHED, MERGED OR TAGGED BY THE
ASSISTANT. TWO ARMS AND FOUR SCORINGS RUN BY THE OWNER ON THE MAIN PC; EVERYTHING ELSE READ BACK
OFF THE BRIDGE RATHER THAN TAKEN ON A PASTE.** Binary UNCHANGED — both arms ran behind the common
preamble's `EXPECTED-EXE-303.txt` check and neither threw.
**NOTHING IS PATCHED IN THE PRODUCT AND NOTHING IN THE INSTRUMENT. THE COUNT OF WRONG FILED FIXES
STAYS AT FIVE.** `316`'s docs are committed at **`0e11b9d`**.

---

## §0 — WHAT THIS SESSION ESTABLISHED, IN ONE TABLE

| | |
|---|---|
| **1** | **`[PREDICTION] 6a` HALF LANDED AND THE OTHER HALF WAS UNPRINTABLE.** The scorer replayed `313` §2.2's six `dx` **exactly** — `-129, -95, -67, -50, -39, -34`, `PASS FAIL PASS PASS PASS PASS`. **Its `seam-check` and `GATE 4b` clauses never printed, on any arm, because the regex I wrote cannot match the line the tool emits.** §3, and it is the assistant's own |
| **2** | **►►►►►►►► `V3` PASSES SIX OF SIX AT `1600x1200`.** `[MEASURED]` `v3_4x3`, `MODE=1`, sep `64`, `a = 1.0000`: ratios `0.996 / 0.946 / 0.982 / 0.989 / 0.981 / 0.981`, **median `0.981`**, every one `VERDICT PASS`. `313` §2.2 read five of six on the same window. **`[PREDICTION] 6e` LANDS** |
| **3** | **`[PREDICTION] 6c` LANDS AND IT IS READ OFF THE LOG.** `v3_4x3`'s own `PREDICTION at D=` lines are `-0.046765` at `1000` and `-0.011691` at `4000` — **ratio `4.0001`, not `1.000`.** The separation is real, not projection-only |
| **4** | **►►►►►►►► `GATE 6.1` FAILED ON ITS OWN COUNTER AND PASSED ON THE INSTRUMENT BUILT TO ANSWER IT.** `[MEASURED, BRIDGE]` all six grabbed frames read `rebuilt(chr+obj+view) min=0 max=0`. **`dlgrab_eyecensus.py` on the same six `.txt` dumps reads `viewport loads=2`, `tri 622/622` (`878/878` on two), `vtx 96/96`, `mtx 32/32`, `MODEL_MTX 1/1`, `only in eye0 = 0  only in eye1 = 0` — SIX OF SIX.** That is `H17` exactly: **a counter that measures "did nothing" cannot see "had nothing to do"** |
| **5** | **►►►► `V4` RAN AND DID NOT FIRE, WHICH IS THE ANSWER IT WAS ASKED FOR.** `[MEASURED]` `v4_4x3`, `MODE=2`, sep `128`: **all seven grabs read `dx = -74` or `-75`** while the run's own `PREDICTION at D=1000` is `-0.093531 x eye_width` = **`-74.83` px at a half of `800`**. The arm visited `D` from `397` to `2277`. **The disparity did not track depth and it sat on the tuned `D=1000` value. `B1` confirmed; `[PREDICTION] 6f` LANDS at `0.989`** |
| **6** | **AND ITS SEVEN `VERDICT FAIL` LINES ARE `H22`, NOT A RESULT.** `[MEASURED]` `preds=10` in a `25 MB` log; **all seven grabs were scored against ONE prediction line at `D=1822.64`**, so the scorer's `-41.05 px` is a stale pairing. `312` §3 measured this on both previous `MODE=2` arms. **`[DISPOSAL] 6f-iii` refuses them by name: no ratio-against-prediction is admissible on this arm** |
| **7** | **►►►► THE `H25` CANDIDATE IS NOW A MEASURED ONE-PIXEL BIAS IN `dx`.** `[MEASURED]` on `v4_4x3` six grabs read `play area x=[0..1599)` -> half `799` -> `dx -74`, and the one grab reading `x=[0..1600)` -> half `800` -> `dx -75`. **A one-pixel play-area difference moved `dx` by exactly one pixel, seven times.** It is the instrument, not the picture |
| **8** | **`314` §2.2 IS CONFIRMED A THIRD TIME, ON DATA THAT DID NOT EXIST WHEN IT WAS WRITTEN.** `[MEASURED]` `v3_4x3`'s worst grab (`0.946`) is its largest depth drift (`6.4%`); the frame gaps `53, 53, 33, 5, 14, 16` **order nothing** — the two `53`s bracket the best and the worst |
| **9** | **`X1-0` DID NOT RUN.** No `xr_ext_probe.exe`, no `xr_ext_probe_report.txt`. **The binding is still unmeasured** |
| **10** | **SO LANE 1 CLOSES AT `1600x1200` AND NOWHERE ELSE.** `[DISPOSAL] 6g`, pre-registered and now owed in full: **it passes at a `4:3` window where `a = 1.0000` by accident of the window. IT DOES NOT PASS AT THE MANDATED `2560x1369`** |

---

## §1 — **`V3`, AND IT IS THE CLEANEST ARM THIS PROJECT HAS RUN**

`[MEASURED]` `run_316_v3_4x3.log` / `disp_316_v3_4x3.txt`. `GETV_WIDESCREEN=0`, `1600x1200`,
`MODE=1`, sep `64`, `tanR-tanL=1.368534`, `ours: x=0 w=800 fb=1600x1200`.

| frame | `D` | predicted px | `dx` | ratio | depth drift | frame gap | gate |
|---:|---:|---:|---:|---:|---:|---:|---|
| `3353` | `313.09` | `-119.50` | **`-119`** | **`0.996`** | `0.6%` | `53` | **PASS** |
| `3653` | `471.95` | `-79.27` | `-75` | `0.946` | **`6.4%`** | `53` | **PASS** |
| `3873` | `565.09` | `-66.21` | `-65` | `0.982` | `2.0%` | `33` | **PASS** |
| `4085` | `672.74` | `-55.61` | `-55` | `0.989` | `1.1%` | `5` | **PASS** |
| `4274` | `764.65` | `-48.93` | `-48` | `0.981` | `2.0%` | `14` | **PASS** |
| `4456` | `895.05` | `-41.80` | `-41` | `0.981` | `2.0%` | `16` | **PASS** |

**MEDIAN `0.981`. SIX OF SIX `VERDICT PASS`, `|measured - predicted| <= 5 px` WITH THE SIGN
MATCHING, AT PREDICTIONS FROM `-119.50` DOWN TO `-41.80` px.** `contrast` runs `0.844` down to
`0.513`, all well over the `0.20` floor. **`309` §5.2's warning does not apply: this gate CAN fail
here — `3653` misses by `4.27` px and the arm spans a factor of three in predicted disparity.**

**►►►► AND IT SITS EXACTLY WHERE THE STANDING CONTROL SAID IT WOULD.** The `2560x1369` control
reads `0.704` at `a = 0.7130`, which is `0.987` once divided by `a`. Here `a = 1.0000` and the
median is `0.981`. **Two windows, two `a`, one number to within `0.6%`.** `H19` is `(4/3)/(W/H)`
and nothing else, for the third independent time.

**AND `314` §2.2 GETS ITS THIRD CONFIRMATION FREE.** The one grab that misses the median is the one
grab with a large depth drift; **the frame gaps order nothing.** `[NOTE, AND IT CUTS BOTH WAYS]`
the default `--max-depth-drift 0.05` **would have refused `3653`** — a grab that passed its own
`+/-5 px` gate, which is `314` §2.2's argument for `0.15` — **and `3653` is also this arm's worst
ratio, which is an argument the other way.** One arm is not a decision; the default stays deferred.

---

## §2 — **`V4`, THE NEGATIVE ARM. IT DID NOT FIRE, AND ITS SEVEN `FAIL`s ARE `H22`**

`[MEASURED]` `run_316_v4_4x3.log` / `disp_316_v4_4x3.txt`. `MODE=2`, sep `128`, same window, same
sitting. **`MODE=2` TOOK:** `tangents L=-0.620267 R=0.748267`, asymmetric, **shifted together**, with
`tanR-tanL=1.368534` unchanged — `stereo.c:284-295`, and it is the off-centre term
`RUN-SHEET-315` §1 says `MODE=2` already drives.

| | |
|---|---|
| the run's own `PREDICTION at D=1000` | **`-0.093531 x eye_width`**, which at a half of `800` is **`-74.83` px** |
| measured `dx`, seven grabs | **`-74` on six, `-75` on one** |
| ratio against the `D=1000` value | **`0.989` / `1.002`** |
| depths the run visited | `397.39` ... `2276.93`, ten distinct prints |
| `contrast` | `0.553` ... `0.855` |

**►►►►►►►► THE DISPARITY DID NOT TRACK DEPTH.** Seven grabs, seven positions, one number to within
a pixel, on an arm whose own centre depth ranged over a factor of `5.7`. **That is `B1`:
`MODE=2` puts the shift in the PROJECTION and returns `0` from `geStereoOffsetCameraPos()`
(`stereo.c:355-357`), so its disparity is a constant — and `stereo.c:22` tunes that constant to the
disparity a real separation would produce at `GE_STEREO_B1_DEPTH = 1000`. It landed on it.**

**►►►► `[DISPOSAL] 6f-i` DID NOT FIRE, SO `V3`'s PASS IS NOT WITHDRAWN.** `49` and `299` §4.3 are
satisfied: `V3` passed on the view path, `V4` behaved as the projection-only path must, and the two
disagree in exactly the way `311` §3 pre-registered.

**AND THE SEVEN `VERDICT FAIL` LINES MUST NOT BE QUOTED AS A RESULT.** `[MEASURED]` `preds=10` in a
`25 MB` log: the `PREDICTION` print stops on a `MODE=2` arm and **all seven grabs were scored
against one line at `D=1822.64`**, giving a stale `-41.05 px`. `312` §3 measured the same thing on
`run_311_mode2.log` (`41,502`-`150,254` lines stale) and `run_312_mode2depth.log` (`58,637`).
**`[DISPOSAL] 6f-iii` refuses them: no ratio-against-prediction is admissible on this arm.** The
admissible reading is the depth-independence above, which needs no pairing at all.

### 2.1 — ►►►► **AND THE `-74` / `-75` SPLIT IS THE INSTRUMENT, MEASURED**

`[MEASURED]` six grabs read `play area x=[0..1599)  width=1599  borders L=0 R=1` and one reads
`x=[0..1600)  width=1600  borders L=0 R=0`, on the same arm, same window, same backend rectangle
(`ours: x=0 w=800`). **Half `799` gives `dx -74`; half `800` gives `dx -75`.**

**A ONE-PIXEL PLAY-AREA DIFFERENCE MOVED `dx` BY EXACTLY ONE PIXEL, SEVEN TIMES.** `316` §0 item 3
filed this as a candidate off `311_mode2`'s `2191`/`2192` and `312_w2560h800`'s `746`/`747`, where
the half never moved and nothing could be seen. **Here the half moves and the answer moves with
it.** The backend's rectangle is a per-arm constant; the detector's is a per-picture estimate.
**This is what `RUN-SHEET-316` §3's log-fed seam removes, and it is now the second measured reason
to want it — but it is still not filed and still not spliced.**

---

## §3 — ►►►►►►►► **THE RETRACTION, AND IT IS MINE, MADE THE SAME DAY IT WAS WRITTEN** ◄◄◄◄◄◄◄◄

**`RUN-SHEET-316` §1.1's `GATE 4b` CANNOT PRINT. IT DID NOT PRINT ON ANY OF THE FOUR SCORINGS.**

`[MEASURED, BRIDGE]` `grep -c 'seam-check'` and `grep -c 'GATE 4b'` return **`0` and `0`** on
`disp_316_replay_w1600x1200.txt`, `disp_316_replay_wsONb.txt`, `disp_316_v3_4x3.txt` **and**
`disp_316_v4_4x3.txt`.

**THE CAUSE IS ONE CHARACTER OF WHITESPACE.** The block matches

```
'play area x=\[(\d+)\.\.(\d+)\)  width=(\d+)'
```

and `stereo_disparity.py:270` prints

```
play area   x=[0..1600)  width=1600  borders L=0 R=0
```

— **three spaces after `area`, not one.** `$pa` is `$null` on every grab, so the `if ($pa)` body —
the `seam-check` line **and** the `GATE 4b FAILED` banner — is skipped entirely.

**►►►►►►►► AND THE COST IS THE WORST KIND: IT IS A REGRESSION DRESSED AS AN IMPROVEMENT.**
On `replay_wsONb`, seven grabs whose seam is `367.333` px from the real one printed
`eye half 1280`, `searched [-500 .. +319]`, `dx -420` / `-486` / ..., one
`CANNOT ANSWER -- LOW CONFIDENCE` and the rest `VERDICT FAIL` — **with no banner at all.**
**`RUN-SHEET-314` §5.2's typed `1825` would have bannered all seven.** I replaced a gate that was
wrong at every window but one with a gate that is silent at every window.

- **This is `H1` and `H17`'s family and the project already has the sentence for it:
  `309` §5.2 — A GATE THAT CANNOT BE FAILED IS NOT A GATE.** `307` §4 filed `H17` for a counter
  whose alarm could not distinguish a healthy arm; this is one step worse, because the alarm could
  not be reached at all.
- **`[PREDICTION] 6a` IS THEREFORE ONLY HALF LANDED.** Its `dx` clause reproduced `313` §2.2
  exactly. Its other two clauses — *"no `GATE 4b FAILED` on any of the six"* and *"`delta_left 0`
  and `delta_width 0` on all six"* — were **UNPRINTABLE, NOT PASSED.** A replay control that
  cannot exercise the branch it is controlling is not a control for that branch.
- **AND THE RULE, WHICH IS NEW AND IS THIS SESSION'S TO PAY FOR: A GATE'S CONTROL MUST MAKE IT
  FIRE, NOT ONLY MAKE IT QUIET.** `316` pre-registered `6b` to banner seven times on `wsONb` and
  then read `6a`'s silence as a pass without checking that `6b` had produced its banners. **The
  negative arm existed and was not read.** That is `49` pointed at an instrument instead of at a
  measurement.

**►►►► WHAT THE DEFECT DOES *NOT* DO, AND IT IS CHECKED RATHER THAN ASSUMED.** `[MEASURED,
BRIDGE]` on `v3_4x3` and `v4_4x3` the backend printed `ours: x=0 w=800`, so the true expectation is
`1600`, and the tool read `1600` or `1599` on every grab. **A working `GATE 4b` would have passed
all thirteen.** §1's and §2's numbers stand; what was lost is the assurance, not the result.

**THE FIX IS `RUN-SHEET-317` §1 AND ITS CONTROL IS THAT IT MUST BANNER SEVEN TIMES ON
`grabs_315_wsONb` BEFORE IT IS USED ON ANYTHING ELSE.**

---

## §4 — **`GATE 6.1`, AND THE RIGHT INSTRUMENT ANSWERED IT**

`RUN-SHEET-315` §2.1 point 1: *"GATE 6.1 FIRST, AND STOP IF IT FAILS. Both eyes non-zero on each
grabbed frame."* **On its stated counter, `v3_4x3` FAILS: all six grabbed frames read
`rebuilt(chr+obj+view) min=0 max=0`, cumulative `2684 of 4836`, `pass-never-ran 0`.**

**`H17` IS EXACTLY THIS AND `307` §4 MEASURED IT ON A HEALTHY ARM:** `2,220 of 7,636` contiguous
zero-rebuild frames because the owner stood still facing a wall with nothing on screen. **The
counter counts rebuilt PROPS. A wall is not a prop.**

**SO IT WAS ANSWERED WITH THE INSTRUMENT BUILT FOR THE QUESTION, OFFLINE, ON THE `.txt` DUMPS THAT
WERE ALREADY BESIDE THE PICTURES.** `[MEASURED, BRIDGE]` `dlgrab_eyecensus.py`, all six frames:

| frame | viewport loads | tri | vtx | mtx | `MODEL_MTX` | only in eye0 / eye1 |
|---:|---:|---:|---:|---:|---:|---|
| `3353` | `2` | `622 / 622` | `96 / 96` | `32 / 32` | `1 / 1` | `0 / 0` |
| `3653` | `2` | `622 / 622` | `96 / 96` | `32 / 32` | `1 / 1` | `0 / 0` |
| `3873` | `2` | `622 / 622` | `96 / 96` | `32 / 32` | `1 / 1` | `0 / 0` |
| `4085` | `2` | `622 / 622` | `96 / 96` | `32 / 32` | `1 / 1` | `0 / 0` |
| `4274` | `2` | `878 / 878` | `211 / 211` | `39 / 39` | `1 / 1` | `0 / 0` |
| `4456` | `2` | `878 / 878` | `211 / 211` | `39 / 39` | `1 / 1` | `0 / 0` |

**TWO VIEWPORTS, TWO EYES, IDENTICAL AND NON-ZERO, WITH NO DL CALL TARGET IN ONE EYE AND NOT THE
OTHER, ON EVERY GRABBED FRAME.** `GATE 6.1`'s SUBSTANCE is met. **`v4_4x3` needs no such rescue —
its grabbed frames read `min=2/3`, non-zero on the counter itself.**

**►►►► AND THIS IS OWED BACK TO `H17` AS A MEASUREMENT, NOT AS A WORKAROUND.** The census is the
discriminator the rebuild counter lacks, it is already written, and it runs offline on files the
arms already produce. **`RUN-SHEET-317` §2 proposes making it `GATE 6.1`'s instrument rather than
its second opinion. It is a PROPOSAL. Nothing is filed.**

---

## §5 — **WHERE LANE 1 ACTUALLY STANDS**

**`RUN-SHEET-315` §0's stop condition is met: `V3` reads `PASS` with `4c` clean, `V4` ran in the
same sitting, and `4b` — the one gate that could not print — is checked by hand against the
backend's own rectangle and would have passed all thirteen. LANE 1 CLOSES.**

**►►►►►►►► AND `[DISPOSAL] 6g` IS OWED IN FULL, IN ITS OWN WORDS:**

> **It passes at `1600x1200`, a `4:3` window where `a = 1.0000` by accident of the window.
> IT DOES NOT PASS AT THE MANDATED `2560x1369`. `H19` stays open, unpatched,
> `a = (4/3)/(W/H)`, and DOCUMENTED rather than hunted.** That sentence is the difference
> between a gate and a claim.

**WHAT IS STILL TRUE AND WAS NOT TOUCHED:**

- **`[PREDICTION] 4a` IS STILL NEITHER ESTABLISHED NOR FALSIFIED.** `[ARITHMETIC]` `a = 1.000000`
  at `WS=1` is still unchecked, because `H24` still blinds every `WS=1` arm.
- **`H24` IS UNFIXED AND `RUN-SHEET-316` §3 IS STILL A CONTRACT, NOT A TASK.**
- **`H25` IS STILL NOT FILED**, and it now has a measured consequence (§2.1) rather than only a
  wobble. **`314` §2.2's rule still applies: check that the quantity a refusal refuses on ORDERS
  the error, on grabs already held. That has not been done.**
- **`X1-0` IS STILL OWED.** One compile, one run.

---

## §6 — WHAT NEEDS A PERSON

- **`RUN-SHEET-317` §1 — the `GATE 4b` fix, and its control is that it must FIRE.** `LOW`, offline.
  **Nothing else in this document is trusted until it has bannered seven times on `wsONb`.**
- **`RUN-SHEET-317` §3 — `X1-0`, unchanged and still owed.** `LOW`, one compile, one run.
- **`X1` — `HIGH`, a fresh session's opening question.** `PRIORITY-BOARD-313` §GROUP X's
  precondition — `V3` passed — **is now satisfied at `1600x1200` and only there.** Whether that
  satisfies it is the owner's call and it belongs in `00-STATE` §3 in the owner's words.
- **`RUN-SHEET-317` §2 — the census as `GATE 6.1`'s instrument.** A PROPOSAL. `MEDIUM`.
- **`--max-depth-drift`'s default** — §1 is evidence on BOTH sides. **Still deferred.**
- **`U-27`**, **`GX-0`**, **lane 3** — unchanged. **`E3` is CLOSED.**

**`169` NEXT ID = `U-28`. NEXT INSTRUMENT HOLE = `H25`.**
