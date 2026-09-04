# `303` — THE VIEWER WAS THE DEAD EYE, AND THE SECOND EYE IS THE REFERENCE FRAME

**WRITTEN OFFLINE 2026-09-03. `RUN-SHEET-303` IS WORN IN FULL — ten gates, the regen, the build,
V1/V2, FC1/FC2 and all three commits — plus one arm this sheet did not contain (`C1`).**

Binary: `goldeneye.exe` **18,070,774 bytes**, sha256 `45756E5A…3F92`, built 2026-09-03 21:05,
`EXPECTED-EXE-303.txt` written and matched by every arm. `302`'s was `DF5CAB2A…1438 18068657`;
**the two differ by 2,117 bytes and no arm ran against the wrong one.**

**THREE THINGS CAME OUT OF THIS SESSION AND ONLY ONE OF THEM IS THE FIX IT WAS WRITTEN FOR.**

---

## §0 — THE ONE THING TO READ IF YOU READ NOTHING ELSE

**THE SESSION'S TWO FIXES CAME OUT OPPOSITE WAYS, AND THE ARM THAT ANSWERED NOTHING TAUGHT THE
MOST.**

| | verdict |
|---|---|
| **§2 the viewer admission** | **WORKS, TOTALLY.** eye1 `MODEL_MTX` 38/38, `only in eye1 = 0`, **zero skipped frames in the whole run**, and the owner's eyes agree. GROUP `B` CLOSES |
| **§3 the far clamp** | **NO VERDICT.** The A/B could not discriminate, and the reason is measured, not guessed: **the knob is loud only where the picture is blank** |
| **§4 the `NaN`** | **`292`'s DOUBLE CONVERSION IS DEAD** — `already-converted=0` of `366,456`. GROUP `C`'s leading hypothesis is gone and the instrument said so itself, in a line written before the run |

**AND A FOURTH THING NOBODY ASKED FOR: `H9` IS ANSWERABLE AND WAS ALL ALONG.** §6. It has been
open since `299` on the sentence *"a reference-frame differ would need a known-good frame this
project does not have."* **That is true of a MONO frame and false of a STEREO one:** at
`GETV_STEREO_OFFSET=0` the second eye IS the known-good frame — same run, same rig, same instant,
nothing to normalise. **`getv/tools/stereo_eyediff.py` is that differ, it is written and its
selftest passes, and it found the session's new symptom three times in nine frames with no false
positives.**

---

## §1 — WHAT WAS WORN, IN ORDER

| step | result |
|---|---|
| §1 ten offline gates | **ten `VERDICT PASS`**, re-worn on the bridge as well (`H7`): `depthclamp` 17/0, `glpath` PASS, `ge_rebuild_window` **30 checks 0 failed**, `port_syntax_gate` **51 ok 0 failed 6 not covered**, `stereo_harness` **63 passed 0 failed** with `src/game/chrprop.c PASS 0 errors`, `cullwhy` 0 failures, `posespine` 10/0, `ge_arm_tag` 11/0, `stereo_disparity --selftest` A/B/C PASS, `knob_banner_survey --selftest` 5/0 |
| §2 `verify` + build | `15/15`; `game 167 / assets 234 / audio 40 / port layer 59 / port c++ 2`, **0 failed anywhere**, `libge.a` 24.9 MB / 501 members |
| §2c binary identity | `45756E5A…3F92 18070774` — **not** `302`'s, so the edit took |
| §3 V1 / V2 | **both worn**, `game_exit requested`, no `EXCEPTION` |
| §4 FC1 / FC2 | **both worn**, same |
| §5 three commits | `94cdf01c` (decomp) / `c26c58d` (native) / `d393860` (GoldenEyeVR), **run before the arms**, all three trees clean after |
| `C1` (not in the sheet) | `GETV_STEREO_MTXGUARD=1`, observe only |

**►► EVERY NEW INSTRUMENT WAS CONFIRMED PRESENT IN THE BINARY BEFORE ANY ARM RAN** (`133`,
`grep -aF` on the exe): `GETV_STEREO_REBUILD_VIEWER`, `[getv][farclamp]`, `GETV_FARCLAMP=`,
`[getv][run] ARM=`, `rebuilt(chr+obj+view)`, `[getv][near]`, `[getv][far]`. The depth-clamp
banner reads `ONLY THE **NEAR** PER-VERTEX CLAMP STANDS DOWN`, so no arm could have been the
`302` exe under a `303` name.

---

## §2 — GROUP `B` CLOSES. THE VIEWER WAS THE DEAD EYE AND ADMITTING IT FILLS THE SECOND ONE.

**GATE §3a** — `[getv][stereo][rebuild] GETV_STEREO_REBUILD_VIEWER=1` in V1, `=0` in V2.

**GATE §3b — `[MEASURED]`, and it is `RUN-SHEET-303` §3b's predicted table to the frame:**

| | V1 (fix ON) | V2 (fix OFF) |
|---|---|---|
| the dead block `1083-1454` | **`chr=0 obj=0 view=1 skipped=0` ×372** | `chr=0 obj=0 view=0 skipped=1` ×372 |
| the second state | `chr=1 obj=0 view=1 skipped=0` ×169 | `chr=1 obj=0 view=0 skipped=1` ×169 |
| cumulative `viewer=` | **`0`** | **`541`** |
| ZERO-REBUILD cumulative | **`0` of 3015** | `372` of 3044 |
| frames with any `skipped>0` | **ZERO in the entire run** | 541 |

`372 + 169 = 541` on both sides — `301` S2's four population states, reproduced again, and the
whole of `299`'s "~541" accounted for. **`view` reached the accumulator**, which was §3b's stated
failure mode.

**►►►► GATE §3c — THE PICTURE, AND IT IS THE FULL 38, NOT A PARTIAL ADMISSION.**

| grab | V1 `MODEL_MTX` | V2 `MODEL_MTX` |
|---|---|---|
| 1158 / 1191 | **38 / 38** | 38 / **0**, `only in eye0 = 18` |
| 1195 / 1253 | **38 / 38** | 38 / **0**, `only in eye0 = 18` |
| 1235 / 1300 | **38 / 38** | 38 / **0**, `only in eye0 = 18` |
| 1271 / 1354 | **38 / 38** | 38 / **0**, `only in eye0 = 18` |
| 1308 / 1404 | **38 / 38** | 38 / **0**, `only in eye0 = 18` |
| 1345 / 1459 | **38 / 38** | **76 / 38**, `only in eye0 = 18` |
| gameplay 2732 / 2867 | 39 / 39 | 39 / 39 |

`MODEL_VTX` 16/16 and `MODEL_COL1` 19/19 in V1 as well, and **`only in eye0 = 0` AND
`only in eye1 = 0` on every V1 frame** — so it is not the matrices alone. V2 reproduces `302` §3
exactly, so the A/B is not void.

**`[REPORTED]`, the owner, on V1's opening:** *"Yes it does and it loads better than before
without all that texture in the left eye."* Asked whether that was gone or merely reduced:
**gone.** That texture WAS the documented symptom (`299` §8.2), not a second one.

**`item 4`'s *"the viewer is already per-eye"* is falsified in the picture as well as in the
call.** `chrpropRender()` → `bondviewRenderProp()` (`chrprop.c:884`) → `chrRenderProp()` when
`chr` is non-NULL (`bondview2.c:11666`): four lines, and three sessions did not open them.

---

## §3 — THE FAR CLAMP: **NO VERDICT, AND THE VENUE IS WHY.** `303` §0.1 IS NOT SUPPORTED.

**GATE §4a** — `[getv][farclamp] GETV_FARCLAMP=1` / `=0`, and
`[getv][depthclamp] GL_DEPTH_CLAMP ON (core 3.2+, GL_VERSION=4.6.0 NVIDIA 616.56)`.

**GATE §4b — the knob took, at full strength:**

| | near `clamped` | far `clamped` | far `straddle` | `beyond_far` (whole run) |
|---|---|---|---|---|
| **FC1** | **`0`** ✔ the receipt | **`81,076`** | `81,076` | 2,152,718 (4.8% of 45.3M) |
| **FC2** | **`0`** ✔ | **`0`** | `105,129` | 2,281,006 (4.5% of 50.1M) |

FC1's far `clamped` equals its `straddle` **exactly**, with `all_far(hw-rejects)=0`. Near
`clamped=0` in both, so `301` §5's near fix has **not** regressed.

**`[REPORTED]`, the owner, on both arms:** *"They both have blur in the far distance, but not as
bad as the other test. It was a good distance then the games natural distance fog set in."* Asked
where: ***"in the level looking down the road in the distance. same level that had the car prop in
the road."***

### 3.1 — ►►►► THE CENSUS IS CUMULATIVE ACROSS TWO REGIMES THAT DIFFER BY 15x, AND THE HEADLINE % IS A BLEND OF THEM

`[getv][far]` prints a running total, so differencing consecutive samples gives the per-window
rate. **Every one of these three runs has two completely different scenes in it:**

| | the level / the road | the cast roll (the "introduction loop") |
|---|---|---|
| **D3** (`302` §4, clamp down) | 3.9 – 5.9% `beyond_far` | **45% → 67%**, straddle **44k**/Mvtx |
| **FC1** (clamp ON) | 1.2 – 1.6% | **56 → 71%**, straddle 45k/Mvtx, **clamped 45k/Mvtx** |
| **FC2** (clamp OFF) | 1.5 – 2.3% | **40 → 67%**, straddle 50k/Mvtx, **clamped 0** |

**So `302` §4's `beyond_far=16534203 (13.2%)` is not a property of a scene. It is a weighted
average of a 5% scene and a 67% scene**, and it is not comparable to any other run's 13.2%.

### 3.2 — AND THE VENUE THE PROJECT CHOSE MAXIMISES THE COUNTER AND MINIMISES THE PICTURE

The FC grabs were opened. **All of them are the cast roll** — *"Also Featuring / General Arkady
Ourumov"*, *"Starring / 007 James Bond"*, and `302`'s own `dlgrab_D3_33362` is *"Ex KGB Agent /
Valentin Zukovsky"*. Each frame is **two enormous flat-shaded quads meeting on a diagonal** with
the cast text over them. Borders 366 px each side = `x=367.333`, so widescreen was OFF as set
(`285`).

**That is why nothing could be seen.** The cast roll is 67% beyond-far — which is why it looked
like the right venue — **and it is flat colour, so there is nothing in it to z-fight visibly.**
Meanwhile the place the owner was actually judging, the road, is where the clamp fires
**20–40x less**: 50–2,300 clamps per Mvtx against the cast roll's 45,000.

**►►►► THE ARM IS A `279` §7 NULL: AN INSTRUMENT POINTED AT NOTHING.** `RUN-SHEET-303` §0.1's
claim — that the far clamp is the cause of *"foggy… flickering… transparent… much less view"* —
**is NOT SUPPORTED by this A/B and must not be written up as supported.** It is not disproved
either. It is unanswered.

**AND THE CORRECTION TO `303`'s OWN VENUE ARGUMENT:** *"On a loop there is nothing to normalise"*
is true of the OWNER'S EYES and false of the COUNTERS, because the counters are cumulative over
the whole run including the walk and the death. `RUN-SHEET-304` §2 gates on the per-window rate
instead.

---

## §4 — `C1`: **`292`'s DOUBLE CONVERSION IS DEAD, AND THE INSTRUMENT SAID SO IN A LINE WRITTEN BEFORE THE RUN**

Not in `RUN-SHEET-303`. Added because §5's symptom needed GROUP `C`'s hypothesis tested, and
`GETV_STEREO_MTXGUARD=1` is observe-only, needs no build, and was already in the binary.

```
[getv][mtxguard] arrays=366456 already-converted=0 skipped=0
[getv][mtxguard] already-converted=0 means the saturated matrix came from somewhere else
                 and this diagnosis is WRONG -- do not keep it.
```

**That third line is the instrument's own pre-registered null** (`bondview2.c`, rule `15`, `49`),
and it fired.

| run | binary | arrays | already-converted |
|---|---|---|---|
| `292` S2d | pre-ARM-3 | 183,808 | **88,520 (48.2%)** |
| `299` E2 | `02:40` | 144,716 | **11,902 (8.2%)** |
| **`303` C1** | **`21:05`** | **366,456** | **0 (0.0%)** |

`299` E2's banners were checked: **stereo ON, VIEWRESTORE ON, REBUILD ON** — the same shape as
`C1`, so the arms are comparable in kind.

**THIS ZERO IS A RESULT, NOT A MASKED ZERO.** Its upstream counter is **2.5x E2's**, and nothing
rejects upstream of the conversion — `298` §4.2's rule applied forwards, and `289` R2's
masked-zero rule satisfied rather than cited. **The honest bound: this establishes absence on
this run and this route, not a proof about every route.**

**WHAT IT KILLS.** GROUP `C`'s leading hypothesis. `299` §8.4's *"`292`'s double conversion is
ALIVE… most of them `NaN`"* does not hold on the `303` binary, and since the guard's test catches
out-of-range floats generally, **the `NaN` may have gone with it.** `C1` on the board must be
rewritten around what is left, not around the conversion.

---

## §5 — THE NEW SYMPTOM: **A ONE-EYE POLYGON, IN FRAMES WHOSE CENSUS IS PERFECTLY BALANCED**

`[REPORTED]`, the owner, unprompted: *"There are other small texture flickers that come up… It
normally would have been confused for the original issue, but apparently its different"*, and
later, *"bond bobs and it changes the output"*.

It is in the grabs. **`dlgrab_V1_2732`, `dlgrab_C1_2336` and `dlgrab_C1_4676`** each carry **a
flat, untextured slate-blue polygon with a soft vertical gradient, occluding wall geometry, in ONE
eye only.**

**►►►► AND THE CENSUS ON THOSE VERY FRAMES IS PERFECT:**

```
gSPSegment MODEL_MTX(3)   eye0 39   eye1 39   +0
gSPSegment MODEL_VTX(4)   eye0 17   eye1 17   +0
DL CALL targets           eye0 46   eye1 46    only in eye0 = 0   only in eye1 = 0
```

**SAME COMMANDS, DIFFERENT PICTURE.** Every eye fault this project has chased since `292` has been
an ADMISSION fault — one eye not being told about geometry. **This is the first one that is not**,
and no instrument the project had could see it: the census counts what was submitted, and the
owner cannot be pointed at 3,000 frames. The bob moving it is consistent with a transform rather
than an admission.

**`dlgrab_C1_4676` IS A BIGGER EVENT THAN THE OTHER TWO AND SHOULD BE OPENED FIRST:** 44,252
differing pixels across **900 blobs** against `V1_2732`'s 11,205 across 53, and its half-alignment
`mad` reads **6.409** where every other frame in the session reads 3.4–4.1. In its crop the wall
geometry itself differs between the eyes, not only the polygon.

**WHAT IT IS NOT:** it is not the double conversion (§4), and it is not an admission loss (the
census above). **Nothing in this session names its cause and nothing here should be read as
naming it.**

---

## §6 — ►►►► `H9` IS CLOSED, AND THE FILED FIX WAS WRONG IN THE SAME WAY `H1` AND `H3` WERE

`PRIORITY-BOARD-299` `H9`: *"No instrument answers 'is the picture right' without the owner's
eyes… A reference-frame differ would need a known-good frame this project does not have."*

**THE SECOND SENTENCE IS TRUE OF A MONO FRAME AND FALSE OF A STEREO ONE.**

> At `GETV_STEREO_OFFSET=0` the two eye halves MUST be identical apart from the viewmodel.

So the known-good frame is **in the same picture**: same run, same rig, same instant, nothing to
normalise and nothing to remember. **Fourth instance of `301` §0's rule — a hole's filed fix is a
diagnosis, not a patch — and this time the diagnosis was not wrong about the defect, it was wrong
about the impossibility.**

**`getv/tools/stereo_eyediff.py`.** Stdlib only, like `stereo_disparity.py`, whose BMP reader,
pillarbox detection and dx sign convention it reuses so the two tools cannot disagree about where
the seam is.

| | |
|---|---|
| what it does | aligns the halves at the measured `dx`, masks the per-eye regions, thresholds, labels 4-connected blobs, prints every number and a verdict |
| masks, **declared not tuned** | bottom `0.60*h` — the viewmodel is legitimately per-eye (`293` §2.1, `[MEASURED]` its blob sits at y[908..1149]) and the HUD timer is drawn into one half; `12` edge px each side of the half — the boundary itself |
| refusal | `|dx| >= 8` → **REFUSED**, because with a real separation the halves are SUPPOSED to differ and every number would be noise |
| `--selftest` | **11 checks, 0 failed.** Injects a 50×50 blob and **fails if the alarm goes quiet** (`H1`); asserts a blob in the viewmodel band and one inside the edge margin are NOT reported, so the masks are a mask and not a claim; recovers a −3 px separation with `stereo_disparity`'s sign |

**`[MEASURED]` on `303`'s nine grabs — its own output, and the separation is a factor of ten:**

| | largest blob | total differing px |
|---|---|---|
| six clean frames | 0, 0, 1, 1, 0, **207** | 0 – 207 |
| `C1_2336` | **2,196** | 2,336 |
| `V1_2732` | **5,947** | 11,205 |
| `C1_4676` | **4,544** (900 blobs) | **44,252** |

**Three hits, zero false positives, on data that was already on disk before the tool existed.**

**►►►►►►►► CORRECTED 2026-09-03 BY `304` §1. THAT SENTENCE WAS TRUE OF NINE FRAMES AND FALSE OF
THE CORPUS. ◄◄◄◄◄◄◄◄** The sweep it recommended found a **FALSE NEGATIVE IN THIS TOOL**: it
differenced LUMINANCE, inherited from `stereo_disparity.py` where a correlator correctly wants it,
and so scored `dlgrab_S2_1176` — **a frame with a whole dead eye** — CLEAN at 1,329 px, because a
navy void and a brown building have nearly the same brightness. `dlgrab_S3_1155` was a second
miss. **The difference is now PER CHANNEL, `--selftest` carries a check that fails on the version
committed above, and the calibration is 256 frames rather than nine: clean tops out at 715 px and
the smallest hit is 1,967 px, with nothing in between.** `304` §1.2. **The three hits below are
still hits, with larger numbers.** The table's figures are the greyscale ones and are kept as
written (rule `2`).

**WHAT IT CANNOT DO, AND THE DOCSTRING SAYS ALL OF IT OUT LOUD:** it cannot see flicker — a fault
between frames is in no single frame (`268` §4, and the OWNER is who caught that); it is only
valid at zero separation; **a pass is not "the picture is right"**, because both eyes can be wrong
together; and it is `dlgrab_eyecensus.py`'s other half, never its replacement (`H8`) — the census
says whether the commands ARRIVED, this says whether they DREW the same thing.

---

## §7 — THREE LOOSE ENDS, ALL SMALL, ALL RECORDED SO THEY ARE NOT REDISCOVERED

- **`cmds` READS `6587 / 6580` IN EVERY GRAB OF ALL THREE RUNS — A CONSTANT SEVEN COMMANDS THE
  SECOND EYE NEVER GETS.** V1, V2 and C1, opening frames and gameplay frames alike, `-7` every
  time. Too small to be §5's polygon, too consistent to be noise, **and nothing in any document
  explains it.** `LOW`.
- **`[getv][far]` STILL PRINTS KNOB-DEPENDENT `clamped` ON ONE LINE WITH KNOB-INDEPENDENT
  `beyond_far` / `straddle` / `behind_eye`.** `N1` was closed for `[getv][near]` only — it grew
  the SCENE / CLAMP ACTION split and the far line did not. `LOW`, and §3.1 is what it costs.
- **`grabs_303_V1` CONTAINS FOUR FILES THAT ARE NOT V1's.** `dlgrab_D3_33362/33557/33730/33919.*`
  were `302` §4's, left loose in `build-windows`, and V1's `Move-Item` swept them in. **Nothing is
  contaminated** — every census here ran on `dlgrab_V1_*` — but they must go to `grabs_302_D3\`
  before someone reads them as V1's (`279` §2). **This is `N2`'s workaround failing in the
  direction `N2` did not cover: `GETV_ARM` names a run's OWN grabs and says nothing about the
  strays already in the folder.**

---

## §8 — FILES

| file | repo | change |
|---|---|---|
| `getv/tools/stereo_eyediff.py` | `goldeneye-native` | **NEW.** `H9`. 11 selftest checks, 0 failed |
| `repo/docs/303-…md` | `GoldenEyeVR` | this document |
| `repo/docs/00-STATE.md` | `GoldenEyeVR` | currency, §3, §4 retraction, §6 traps |
| `repo/docs/PRIORITY-BOARD-299.md` | `GoldenEyeVR` | `B` closed, `C` rewritten, `H9` closed, two new holes |
| `repo/docs/RUN-SHEET-304.md` | `GoldenEyeVR` | **NEW** |
| `repo/docs/NEXT-SESSION-PROMPT-304.md` | `GoldenEyeVR` | **NEW** |

**No source file changed after the build.** The binary in `getv\build-windows\` is the one every
arm above ran against, and `stereo_eyediff.py` is a host-side tool that is not compiled into it.

---

## §9 — WHERE THE WORK GOES

1. **`RUN-SHEET-304` §1 — wear `stereo_eyediff.py` on the main PC** (`H7`: the bridge's
   `gcc 11.4.0` / `python3` is not the main PC's `py`), then **sweep every grab this project has**.
   It is offline, it costs nothing, and it re-reads `298`–`302`'s pictures with an instrument they
   did not have.
2. **`304` §2 — the polygon.** `C1_4676` first. It is the only symptom on the board with a picture,
   a detector and no explanation.
3. **`304` §3 — FC3/FC4 at the road**, if the far clamp is still wanted, gated on the per-window
   rate rather than the blended cumulative one.
4. **GROUP `C` needs rewriting before it is worked**, not after: its hypothesis died in §4.
