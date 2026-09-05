# `311` — **THE SEPARATION IS APPLIED IN FULL. THE PIXELS ARE NOT.**

**2026-09-04. OFFLINE ASSISTANT. NOTHING BUILT, STAGED, BRANCHED OR TAGGED BY THE ASSISTANT.**
Binary UNCHANGED and verified on the bridge against `EXPECTED-EXE-303.txt`:
`45756E5ADB5F…E7223F92`, `18,070,774` bytes. **Four arms were run by the owner on the main PC.**

---

## §0 — WHAT THIS SESSION ESTABLISHED, IN ONE TABLE

| | |
|---|---|
| **1** | **`310`'s COMMIT IS IN AND THE FIRST COMMAND WAS RUN.** `[MEASURED, BRIDGE]` `GoldenEyeVR` HEAD **`c0188a0`**, `goldeneye-native` HEAD **`5b741b3`**. **The username scrub is still there and still not this session's: 57 tracked files under `repo/docs`, untouched.** `c0188a0` swept `00-STATE.md`'s own scrub hunk in with `310`'s edit, exactly as `310` §0 item 2 said it would have to; the other 57 are left alone |
| **2** | **`310` §8's KILL OF CANDIDATE `B` RESTED ON AN IDENTITY, AND IT IS RETRACTED — `B` STAYS DEAD ON `310` §8's OTHER ARGUMENT.** `00-STATE` §4, committed as `9cabee8` before the runs. The statistic reproduces exactly (28 pairs, median `1.0053`); **the camera enters `dmeas` only through `- from . look` (`stereo.c:529-534`), so `-dD/displacement = 1` is FORCED for any `s`.** `D + (camera . look)` is constant to `2.6e-4`. **The flatness over depth is what kills `B`, and it now has a number: a wrong scale needs `c = -22.4` at `D = 75.84`, which would read `0.956` at `D = 508.96` — a spread of `0.251` against a measured `0.026`** |
| **3** | **`RUN-SHEET-311` §1's SCORER WAS DRY-RUN OFFLINE BEFORE THE OWNER TOUCHED IT.** `[MEASURED, BRIDGE]` against `310`'s corpus it reproduces `310` §7's table exactly — `grabs=7 preds=131 dls=7`, all seven predicted px to two decimals — and its `450` gate refuses `S3d_2917` and nothing else. **The gate then fired for real in a live arm** (§4) |
| **4** | **►►►►►►►► `RUN-SHEET-311` §2 IS WORN AND `[PREDICTION] 2b` LANDS: THE RATIO DOES NOT MOVE WITH THE SEPARATION.** `[MEASURED]` medians **`0.6907` / `0.7036` / `0.6960`** at `sep` `32` / `64` / `128`. Ratio-of-ratios `1.019`, `0.989`, `1.008`. **A 4-fold separation range moves it by less than the error bar. `2d` DOES NOT FIRE: nothing adds, clamps or saturates.** §4 |
| **5** | **►►►►►►►► `RUN-SHEET-311` §3 IS WORN AND IT FIRED THE SECOND BRANCH — THE ONE `310` §10 CALLED "THE MORE IMPORTANT ANSWER". `MODE=2` READ `0.7075`, NOT `1.00`.** `[MEASURED]` seven grabs, **`dx = -60` on every one**, `D = 1005.73`, predicted `-84.81`. `MODE=2` returns 0 from `geStereoOffsetCameraPos()` and **never touches the view matrix** (`stereo.c:355-357`). **THE UNDER-READ SURVIVES A PATH THAT APPLIES NO SEPARATION AT ALL.** §5 |
| **6** | **►►►►►►►► SO `A` IS RETRACTED AS THE LOCATION, AND THE RETRACTION IS ARITHMETIC RATHER THAN A JUDGEMENT.** `[ARITHMETIC]` `MODE=1`'s ratio is `(sep_applied/sep_requested) * (half_true/912)`; `MODE=2`'s is `(half_true/912)` alone. **`0.7022 / 0.7075 = 0.992`. THE SEPARATION IS APPLIED IN FULL, TO BETTER THAN 1%.** `00-STATE` §4. §6 |
| **7** | **WHAT IS LEFT IS THE STEP THE PREDICTION DOES NOT OWN: NDC FRACTION -> PIXELS.** `[ARITHMETIC]` under `MODE=2` the shift is `s = -(sep*0.5)/1000` in TANGENT units, the measured NDC fraction is `s/tR` and the prediction is `-sep/(D*2tR)` — **`tR` cancels on BOTH sides, so at `D = 1000` the ratio is `1.000` for any frustum, right or wrong.** `310` §0 item 5 holds and holds here too. **`310` §8.1 and §0 item 6 proved the play area IS `1825` px and each half IS `912` px. They never measured what NDC `+/-1` SPANS inside that half.** §6 |
| **8** | **`[PREDICTION] 2c` FAILED AND IT IS REPORTED AS A FAILURE, NOT SMOOTHED.** It said the `sep128` ratios would be the TIGHTEST because quantization is 4x smaller there. `[MEASURED]` `sep128` spread **`0.0485`** against `sep64`'s **`0.0133`** — **the widest, with the best quantization.** §7 |
| **9** | **AND THE REASON IS A RESIDUAL THIS SESSION CAN SEE AND CANNOT SEPARATE: THE RATIO DRIFTS DOWN WITH DEPTH BY ~2.5%.** `[MEASURED]` pooled over all 15 `MODE=1` grabs, `D < 400` median **`0.7097`** against `D >= 400` median **`0.6924`**. It fits `0.670 + 11.0/D` and it fits `|dx|` about as well, **and the two are confounded within an arm.** `310` §7's "flat" was six grabs on one arm. §7 |
| **10** | **NOTHING IS FILED AND NOTHING IS PATCHED. THE COUNT OF WRONG FILED FIXES STAYS AT FIVE.** `A` is retracted as a location, not replaced by another one |
| **11** | **ONE PROCESS DEFECT, AND IT IS THE ASSISTANT'S OWN, `308` §0 EXACTLY:** the depth-constancy check for `MODE=2` was given to the owner **in chat and never written into the sheet**, so it did not happen — all seven `mode2` grabs are at one spot, `D` identical to two decimals. §7.2 |

---

## §1 — THE ENTRY STATE, MEASURED BEFORE ANY SENTENCE WAS WRITTEN ABOUT IT

`306` §0 is the standing rule: a claim that work is owed is a claim about git. `[MEASURED, BRIDGE]`
2026-09-04, before anything else:

- `GoldenEyeVR` HEAD **`c0188a0`** — `docs(310b)`. **`310`'s commit is IN. Nothing was owed.**
- `goldeneye-native` HEAD **`5b741b3`**, with `309`'s two untracked scratch files
  (`getv/tools/_patch309.py`, `getv/tools/ladder_driver.py`) and nothing else.
- `-- repo/docs` reports **57** modified tracked files, all username scrub.
  **`310` measured 58; `00-STATE.md` is the one that left the list**, because it carried `310`'s
  own edit and could not be separated from its scrub hunk without staging hunks. **The arithmetic
  agrees with `310` §0 item 2 exactly, and the other 57 were not touched by this session either.**

**This is the FIFTH session in a row whose opening claim about git had to be checked rather than
assumed, and the second in a row where checking it was cheap and correct.**

---

## §2 — WHAT WAS DONE OFFLINE BEFORE THE OWNER RAN ANYTHING

`279` §7's rule, applied to a run sheet rather than to an arm: **the most expensive thing this
project does is run an arm that could not have answered anything.** Three bridge-safe reads:

1. **THE BINARY.** `[MEASURED, BRIDGE]` `goldeneye.exe` sha256 `45756E5A…E7223F92`, `18,070,774`
   bytes — **matches `EXPECTED-EXE-303.txt` byte for byte**, so §2's and §3's guards would pass
   rather than throw.
2. **THE NAMES.** No `run_311_*`, `grabs_311_*` or `disp_311_*` existed. The `H5` guards would pass.
3. **THE SCORER.** `[MEASURED, BRIDGE]` §1's selection logic was re-implemented offline and run
   against `310`'s corpus. **It reproduces `310` §7's table exactly** — `ARM S3d grabs=7 preds=131
   dls=7`, and every predicted px to two decimals — **and its `|px| <= 450` gate refuses
   `S3d_2917` (`-503.85`) and nothing else.** The tail `Select-String` anchors were checked against
   the real line starts in `disp_310_S3d.txt`.

**ONE HAZARD WAS FLAGGED BEFORE THE RUN AND DID NOT FIRE:** §1 guards `$d` but not `$m`, so a grab
landing before the first `PREDICTION` line would have thrown mid-arm. It did not happen.
**`RUN-SHEET-312` §1 carries the guard**, because a hazard named in a transcript and not written
into a sheet is `308` §0 (see §7.2, where the same rule caught this session out).

---

## §3 — `310` §8's ARGUMENT, RETRACTED OFFLINE AND COMMITTED BEFORE THE RUNS

Committed as **`9cabee8`**, `docs(311a)`. `00-STATE` §4 carries it in full. In short:

**THE STATISTIC REPRODUCES EXACTLY** — same filters, **28 pairs, median `1.0053`, range
`0.998`-`1.024`**. **THE INFERENCE DOES NOT.** `geStereoPredict()` builds the depth as
`dmeas = (hit.hitpos / s - from) . look` (`stereo.c:529-534`), and **the camera enters only through
`- from . look`.** Moving along `look` does not move the ray, so `hitpos` is unchanged and
`d(dmeas)/d(camera along look) = -1` **for every value of `s`, including a wrong one.**
`[MEASURED, BRIDGE]` on those same 28 pairs, `D + (camera . look)` is constant to **`2.6e-4`
median, `7.4e-4` max.** **A `1.42x` scale error would have passed that test untouched.**

**`B` IS STILL DEAD, ON `310` §8's SECOND ARGUMENT, WHICH NOW HAS A NUMBER.** `[ARITHMETIC]` a
wrong scale gives `D_used = D_true + c` with `c` constant along one sightline. Producing `0.705` at
`D = 75.84` needs `c = -22.4`; that same `c` reads `0.956` at `D = 508.96`. **The ladder would have
to show a spread of `0.251` and it shows `0.026`.**

**THE RULE: DIFFERENTIATE THE EXPRESSION BEFORE QUOTING A RATIO AS EVIDENCE.** Same family as
`305` §1.3 — read the OPERATOR that produced the zero — one level up: **read the DERIVATIVE that
produced the one.**

---

## §4 — `RUN-SHEET-311` §2 IS WORN. **THE RATIO DOES NOT MOVE WITH THE SEPARATION**

**GATE `2a` PASSES ON ALL THREE ARMS.** `[MEASURED]` the logs read `separation=32.000` /
`64.000` / `128.000 game units FULL`, `mode=1 (translation in the VIEW matrix)`, and
`tanR-tanL=1.368534` **identical on all three** — the knob takes, and the frustum does not move
with it.

| arm | grabs | admissible | **median** | mean | min | max | **spread** |
|---|---:|---:|---:|---:|---:|---:|---:|
| `sep32` | 5 | 5 | **`0.6907`** | `0.6888` | `0.6723` | `0.7028` | `0.0305` |
| `sep64` | 6 | 6 | **`0.7036`** | `0.7060` | `0.7017` | `0.7149` | **`0.0133`** |
| `sep128` | 5 | **4** | **`0.6960`** | `0.6924` | `0.6646` | `0.7131` | `0.0485` |

**RATIO-OF-RATIOS BETWEEN ARMS, WHICH IS THE MEASUREMENT §2 EXISTED TO PRODUCE:**
`sep64/sep32` = **`1.0188`**, `sep128/sep64` = **`0.9891`**, `sep128/sep32` = **`1.0077`**.

**►►►► `[PREDICTION] 2b` LANDS: THE RATIO IS THE SAME AT EVERY SEPARATION, TO WITHIN THE ERROR BAR,
ACROSS A 4-FOLD RANGE. `2d` DOES NOT FIRE — IT IS A PURE SCALE. NOTHING ADDS, CLAMPS OR
SATURATES.**

### 4.1 — AND THE GATE `RUN-SHEET-310` §3 DID NOT HAVE FIRED FOR REAL

`[MEASURED]` `sep128` frame `2462`, `D = 179.20`, predicted **`-476.00` px**:

```
=== sep128 frame 2462   D 179.20   predicted -476 px   INADMISSIBLE -- |px| > 450
    (H18, RUN-SHEET-307 s2.0). NOT SCORED, NOT AN OUTLIER. ===
```

**It was refused, out loud, and excluded from the median.** `310` §7.2's defect is the one thing on
this board that has now been fixed rather than argued about, and it cost one `grep` and five lines
of PowerShell. **`RUN-SHEET-311` §2's own arithmetic predicted this grab** — the sheet said "at
`sep 128` stand no closer than `D ~= 190`", the owner stood at `179`, and **the sheet's number and
the tool's refusal agree to a pixel.**

---

## §5 — `RUN-SHEET-311` §3 IS WORN. **`MODE=2` READ `0.7075`, AND THAT IS THE ANSWER THAT MATTERS**

**GATE `2a` PASSES, AND THE FRUSTUM PROVES THE MODE TOOK.** `[MEASURED]` the log reads
`mode=2 (PROJECTION-ONLY -- B1 REPRODUCED ON PURPOSE)` and the tangents are **asymmetric**:

```
tangents L=-0.620267 R=0.748267 D=-0.577350 U=0.577350, tanR-tanL=1.368534
```

**Both horizontal tangents are shifted by exactly `+0.064000`, which is `(128 * 0.5) / 1000`**
(`stereo.c:284-295`, `GE_STEREO_B1_DEPTH 1000.0f`), **and `tanR-tanL` is UNCHANGED at `1.368534`.**
The frustum slid sideways without changing width, which is what `MODE=2` is.

| frame | `D` | predicted px | `dx` | **ratio** | contrast |
|---|---:|---:|---:|---:|---:|
| `3525` | `1005.73` | `-84.81` | `-60` | **`0.7075`** | `0.820` |
| `3854` | `1005.73` | `-84.81` | `-60` | **`0.7075`** | `0.810` |
| `4163` | `1005.73` | `-84.81` | `-60` | **`0.7075`** | `0.801` |
| `4456` | `1005.73` | `-84.81` | `-60` | **`0.7075`** | `0.786` |
| `4716` | `1005.73` | `-84.81` | `-60` | **`0.7075`** | `0.772` |
| `4962` | `1005.73` | `-84.81` | `-60` | **`0.7075`** | `0.784` |
| `5205` | `1005.73` | `-84.81` | `-60` | **`0.7075`** | `0.751` |

**SEVEN GRABS, `dx = -60` ON EVERY ONE, ZERO SPREAD.** `RUN-SHEET-311` §3's pre-registered reading:

> **`MODE=2` reads `~1.00`** -> the loss is in the VIEW path, `A` confirmed.
> **`MODE=2` also reads `~0.705`** -> the loss is **common to both paths**, and something `310`
> believes it cleared is not clear. **That is the more important answer and it would reopen §8.1.**

**►►►►►►►► IT READ `0.7075`. THE SECOND BRANCH FIRED.**

`MODE=2` **returns 0 from `geStereoOffsetCameraPos()` before it computes anything**
(`stereo.c:355-357`) — the view matrix is never displaced, `bondview2.c:8958` never swaps the
camera, and the two eyes are drawn from **the same point in the world.** The under-read is there
anyway, to within `0.5%` of the value the real separation gives.

---

## §6 — ►►►►►►►► **`A` IS RETRACTED, AND WHAT IS LEFT IS ONE STEP THE PREDICTION DOES NOT OWN**

### 6.1 — THE RETRACTION, IN ARITHMETIC

`[ARITHMETIC]` write the two arms out with the same unknowns in them:

```
  MODE=1 ratio  =  (sep_applied / sep_requested)  x  (half_true / half_derived)
  MODE=2 ratio  =                                    (half_true / half_derived)
```

`MODE=2` carries no separation term at all, because no separation is applied. Dividing:

```
  sep_applied / sep_requested  =  0.7022 / 0.7075  =  0.992
```

**►►►►►►►► THE SEPARATION THAT REACHES THE DRAWN IMAGE IS THE `32` THAT WAS ASKED FOR, TO BETTER
THAN 1%. `310` §9's ONE SENTENCE — "the separation that reaches the drawn image is `~22.6` game
units, not the `32` requested" — IS FALSE, AND `00-STATE` §4 CARRIES IT.**

**`310` was right not to file it.** It was stated as a measurement of the SYSTEM and explicitly not
as a diagnosis of a line, and `310` §9 said out loud that the source read disagreed with it
(`stereo.c:333-423` offsets by exactly `+/-sep/2` along a unit right vector, `bondview2.c:8958`
swaps the camera and nothing else, `posespine.c:76` is identity). **The source was right and the
sentence was wrong, and the count of wrong FILED fixes stays at five because nobody filed it.**

### 6.2 — WHY `tR` STILL CANCELS, EVEN HERE

`[ARITHMETIC]` under `MODE=2` the frustum shift is `s = -(sep * 0.5) / 1000` **in tangent units**.
With `mf[0][0] = 1/tR` and `mf[2][0] = s/tR`, a point at view-space `(x, z)` lands at
`x_ndc = (1/tR)(x/(-z) - s)`, so the two eyes separate by `2s/tR` in NDC, which is `s/tR` **as a
fraction of the eye's width.** The prediction is `-sep/(D * 2tR)`. At `D = 1000` those are the same
number for **any** `tR`. **`310` §0 item 5's kill of the whole `H20` family holds, and it holds on
this arm too: no error in any tangent can produce this ratio.**

### 6.3 — SO THE `0.705` LIVES IN NDC -> PIXELS, AND THAT STEP HAS NEVER BEEN MEASURED

The prediction is expressed as a **fraction of the eye's width** precisely so it needs no window
scaling (`stereo.c:434-441`). The tool then multiplies by a half it **derives from the image**:
`play area x=[367..2192) width=1825 borders L=367 R=368`, `eye half 912 px`, on every grab of every
arm of both sessions. **`310` §8.1 and §0 item 6 confirmed, three ways, that the play area IS
`1825` px wide and each half IS `912` px.**

**►►►►►►►► NONE OF THE THREE MEASURED WHAT NDC `+/-1` SPANS INSIDE THAT HALF.** A picture can fill
`912` px and still respond to a frustum shift as though it were `645`. **THAT IS THE GAP, IT IS
WHERE THE `0.705` NOW LIVES, AND IT IS NOT FILED AS A LINE OF CODE.**

### 6.4 — AND THE FIRST HALF OF THAT STEP WAS READ OFFLINE THE SAME DAY, AND IT IS SOUND

`[MEASURED, BRIDGE]` `311b`, prompted by an outside read-only code review that named the viewport
as the object nobody had looked at. **The N64-side NDC -> pixel chain is correct on paper and
correct in the log:**

- `geStereoEyeViewport()` (`stereo.c`) sets the eye rectangle to `half = full_x / 2`, offsets eye
  1 by `half`, and leaves the height alone.
- **`[MEASURED]` the log agrees, on all 425 probe prints across all four `311` arms, with no
  variation at all: `eye viewport 160x180 n64 units (full width 320)`.**
- `viSetupCurrentPlayerView()` (`fr.c:696-705`) builds the RSP viewport as
  `vscale[0] = viewx * 2`, `vtrans[0] = viewx * 2 + viewleft * 4` — **the standard N64 quarter-pixel
  convention, and with `viewx = 160` it is the correct half.**
- `160 * ge_scale (5.704167) = 912.67` px, which is the `912` the tool derives from the image and
  the `1825` play area it detects. **THE TWO AGREE.**

**SO THE `0.705` IS NOT IN THE EYE RECTANGLE, NOT IN `vscale[0]`, AND NOT IN THE N64-UNIT
ARITHMETIC.** That is an elimination, not a finding, and it cost one source read and one `grep`.
**What is NOT read yet is what the PC backend does with that viewport** — `gfx_pc.c`'s scaling of a
viewport that is not the full `320`, which is the only remaining link between `vscale[0] = 320` and
a pixel on the owner's screen. **`RUN-SHEET-312` §2 is the cheaper question and it comes first:
if the ratio tracks `GETV_WINDOW`, the answer is in that backend; if it does not, it is not.**

### 6.5 — AND ONE THING THAT DID NOT FIRE, WHICH IS WORTH SAYING OUT LOUD

`fr.c:731-740` takes a **per-eye copy of the `Vp` from the frame arena** — the `292` S2 fix, because
the display list holds a POINTER and two eyes writing one slot means both halves get the last eye's
rectangle. **The copy is guarded `if (ge_copy != NULL)` and the failure path silently falls back to
the shared slot with no banner and no counter.** `[MEASURED]` it did not fire in any `311` arm — a
fallback would put both halves in one rectangle and every grab shows two well-formed images with a
seam at `x=1279` — **but a fix whose failure mode is invisible is a hole, and it is filed as `H21`
on `PRIORITY-BOARD-311` §D.**

`H19` is **narrowed, not closed**, and its statement changes:

> **`H19` (RESTATED, `311`): the drawn image's horizontal response to the projection is `~0.705`
> of what the logged frustum and the derived `912` px half imply. It is a PURE SCALE — flat over a
> 4-fold separation range — and it is present on a path that never touches the view matrix.**

---

## §7 — WHAT THIS SESSION GOT WRONG, AND IT IS TWO THINGS

### 7.1 — `[PREDICTION] 2c` FAILED, AND THERE IS A RESIDUAL UNDERNEATH IT

`RUN-SHEET-311` §2.1 `2c` said: *"the `sep 128` ratios are the TIGHTEST, because quantization is 4x
smaller there."* `[MEASURED]` `sep128` spread **`0.0485`**, `sep64` **`0.0133`**, `sep32`
**`0.0305`**. **The arm with the best quantization has the WIDEST spread. The prediction is
falsified and it is written down as falsified.**

**AND THE REASON IS VISIBLE IN THE POOLED DATA:** `[MEASURED]` over all 15 admissible `MODE=1`
grabs, sorted by depth, **`D < 400` median `0.7097` against `D >= 400` median `0.6924`** — a
**~2.5% downward drift with depth**, larger than quantization on the two big-separation arms.
It fits `ratio = 0.670 + 11.0/D`; **it also fits `|dx|` about as well (`+0.00012` per px), and
within a single arm `D` and `|dx|` are inversely related, so THIS RUN CANNOT SEPARATE THEM.**

**`310` §7's "flat, spread `0.026`" was six grabs on ONE separation.** Three arms show structure
the one arm could not. **This does not touch the headline** — `0.705` against `1.000` is a 30%
effect and the residual is 2.5% — **but the correlator's ~2% error bar is now the same size as an
unexplained trend, and it must not be quoted as though the trend were noise.**

**`RUN-SHEET-312` gets a lever on this for free:** it changes the derived half at a fixed venue, so
the same `D` produces a different `dx`. **Neither this session nor `310` had that.**

### 7.2 — AND THE ASSISTANT WALKED INTO `308` §0

`RUN-SHEET-311` §3 asked for grabs at `D ~= 1000`. **The owner did exactly that, and the arm is
sound.** The assistant then added, IN CHAT and not in the sheet, that the grabs should be spread
over depth — because under `MODE=2` the disparity is a CONSTANT and its independence from `D` is
the `B1` signature, which would have checked that `MODE=2` is behaving at all.

**`[MEASURED]` all seven `mode2` grabs are at `D = 1005.73`, identical to two decimals: the owner
stood still. THE CHECK DID NOT HAPPEN, AND IT DID NOT HAPPEN BECAUSE IT WAS NEVER IN THE SHEET.**

That is `308` §0 verbatim — *"if a block is written at the keyboard rather than in the sheet, it
goes into the sheet before the session ends"* — **and this is the first time the rule has caught
the assistant rather than a citation.** What the seven grabs DID give is a repeatability check
nothing on disk had: **`dx = -60` seven times with contrast falling `0.820` -> `0.751`, zero
spread.** That is worth having. It is not the check that was described.

**THE `MODE=2` DEPTH-CONSTANCY CHECK IS STILL OWED. It is `LOW` and it is in `RUN-SHEET-312`'s
successor, not in a transcript.**

---

## §8 — WHAT NEEDS A PERSON

- **`RUN-SHEET-312` §2 — the window sweep.** `LOW`, ~5 minutes, no build, two short arms.
  **`GETV_WINDOW` changes the pixel geometry and touches nothing else** — not `fovy`, not the N64
  `320x180` view, not `tanw`, not the separation. **Two candidate scales that fit the control
  equally well predict OPPOSITE results on the two arms, and "neither" is the third outcome.**
- **The commit**, this session's own paths only, explicit `git add --` path lists, `git commit -F`.
  **Do NOT use `COMMIT-NOW.cmd`** (`307` §5). **And leave the 57-file username scrub alone.**
- **`E3` (FC3/FC4) is CLOSED.** Do not re-ask.
- **DO NOT START GROUP `C` / `V7`** — `HIGH`, `PRIORITY-BOARD-311` §E item 9.

## §9 — THE STANDING ONE

**`V3` / `258` STAGE 6 STILL CANNOT CLOSE** (`310` §9.1: a constant `0.705` lets the `+/-5` px gate
pass only where `|predicted| <= 17` px, which is exactly and only `S3b_5400`, the frame `309` §5.2
ruled unfalsifiable). **`311` did not move it. What `311` changed is WHERE the `0.705` can live,
and it moved it off the separation entirely.**

**`169` NEXT ID = `U-26`. UNCHANGED — THIS SESSION FILED NO UNKNOWN.**
