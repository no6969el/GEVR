# `299` — ARM 3 IS GREEN ON ONE FRAME AND DEAD ON ANOTHER, IN THE SAME BUILD

**OFFLINE ONLY. NOTHING BUILT, NOTHING RUN, NOTHING COMMITTED, NO SOURCE FILE CHANGED.**
`HEAD` `3de0db0` / `e380916` / `1f0f7aae`, all three trees clean under
`git --no-optional-locks status`. `goldeneye.exe` unchanged at `2026-09-02 19:29`, 18,058,803 bytes.
**Every number below was taken from files already on disk, with this project's own tools, and every
one of them is re-derivable by re-running the command that produced it.**

---

## §0 — THE HEADLINE

**`298` §0 says ARM 3 IS GREEN. `[MEASURED]` this session: it is green on `dlgrab_2568` and
`dlgrab_3056`, and it is DEAD on `dlgrab_1346` — same binary, same knobs, same level, same
session.** On `1346` **one eye contains no world at all**: per-half texture energy **0.038 against
4.685, a ratio of 123.7x, WORSE than R1's 8.7x**, in a run whose banner reads *ARM 3 per-eye render
rebuild ON* and whose census reads `eyes-rebuilt=1 enabled=1`.

**AND `1346` IS NOT A STRAY FILE. IT IS ONE OF THE ONLY TWO R2 GRABS WITH ADMISSIBLE PROVENANCE.**
`00-STATE` §6: a log's own `dlgrab` announcements are the only admissible provenance for a dump.
`run_297_R2_rebuild_on.log` announces **`1192` and `1346` — and nothing else.**
**The four grabs `298` §1.2 scored ARM 3 on are announced by no surviving log at all.**

**AND §3 NAMES A MECHANISM: EVERY SATURATED MATRIX IN THE SET SITS IN EYE 0, AND ONLY IN THE TWO
DEAD-EYE FRAMES** — `292`'s non-idempotent `bondviewTransformManyPosToViewMatrix`, alive in the ARM 3
build.

**THIS DOES NOT RETRACT ARM 3.** `2568`'s two halves are equal on every counter and the picture
confirms it — the street, two soldiers, the gun, in both eyes. **It narrows the claim, names a
frame class where it fails, and supplies the falsifier** (`RUN-SHEET-299` §2). *"ARM 3 puts the
characters and props in both eyes"* is true of the frames it was measured on and **has never been
measured across frames.**

---

## §1 — THE PROVENANCE, RECONSTRUCTED — AND `298` §6 WAS TOO PESSIMISTIC IN ONE HALF AND TOO
OPTIMISTIC IN THE OTHER

`298` §6 records that a re-run overwrote `run_297_R2_rebuild_on.log` and says *"the BMPs and §1.2's
measurements survive; their provenance cannot be re-derived."* `[MEASURED]`, from mtimes on the
bridge:

| artefact | mtime | what it can belong to |
|---|---|---|
| `run_297_R1_rebuild_off.log` | 20:21:31 | R1, closed |
| `dlgrab_2451`, `dlgrab_2754` | 20:21:26, 20:21:28 | **inside R1.** As documented |
| `dlgrab_2568`, `dlgrab_3056` | **20:22:03, 20:22:06** | **after R1's log closed and before the re-run. No other log covers 20:22.** |
| `run_297_R2_rebuild_on.log` (re-run) | 20:34:45 | the re-run |
| `dlgrab_1192`, `dlgrab_1346` | 20:34:42, 20:34:43 | **inside the re-run, and announced by it** |

**►► SO THE OPTIMISTIC HALF: `2568`/`3056`'s provenance CAN be bounded.** They were written in a
13-minute window in which the only process that existed was the original R2 run. That is weaker than
a log announcement and stronger than nothing, and it should be written down rather than left as
*"cannot be re-derived."*

**►► AND THE PESSIMISTIC HALF, WHICH NOBODY NOTICED: `298` §1.1's TABLE CITES SIX WINDOWS FROM A
FILE THAT CONTAINS TWO.** `[MEASURED]` `grep -c "rebuild] SUMMARY" run_297_R2_rebuild_on.log` = **2**:

```
SUMMARY frames=600  | list=11 | eyes-rebuilt=1 chr=2 obj=9 skipped=0 | enabled=1
SUMMARY frames=1200 | list=1  | eyes-rebuilt=1 chr=0 obj=0 skipped=1 | enabled=1
```

§1.1's rows for **1800, 2400, 3000 and 3600** are not in the file the table names. They were read
from the 14 MB log the re-run destroyed. **The finding stands; the citation does not.**
**A RE-RUN OF AN ARM GETS A NEW LOG NAME** — `298` §6 wrote that rule and this is what it cost.

---

## §2 — **THE MEASUREMENT. ONE EYE HAS NO WORLD, WITH ARM 3 ON.**

### 2.1 — The DL census: `dlgrab_eyecensus.py`, no build, no run

```
py getv\tools\dlgrab_eyecensus.py <dump>.txt
```

| dump | arm | `MODEL_MTX` e0/e1 | `MODEL_VTX` e0/e1 | `only in eye0` | verdict |
|---|---|---|---|---|---|
| `2451` | R1 `REBUILD=0` | 157 / **5** | 83 / **15** | **35** | eye1 a strict subset. As documented |
| `2568` | R2 `REBUILD=1` | **138 / 138** | **83 / 83** | **0** | **equal on every counter** |
| `1192` | R2 `REBUILD=1` | 38 / **0** | 16 / **0** | **18** | **eye1 emits NO models at all** |
| `1346` | R2 `REBUILD=1` | 38 / **0** | 16 / **0** | **18** | **the same, and it is `293`'s signature** |

**`1192` and `1346` are the pre-ARM-3 picture — `293` §2.1's one-way loss, `only-in-eye1 = 0` — in
a run with ARM 3 enabled.**

### 2.2 — Per-half texture energy, and the instrument is validated against `298`'s own numbers

Computed with **`stereo_disparity.py`'s own `read_bmp` / `play_area` / `frame_content`**, so the
definition is the one `298` §1.2 used. **Rule `15`: the instrument is validated by reproducing a
result it did not produce.**

| grab | this session L / R | `298` §1.2 L / R | agreement |
|---|---|---|---|
| `2451` | 0.411 / 3.588 | 0.415 / 3.578 | ≤ 0.01 |
| `2754` | 0.564 / 3.534 | 0.589 / 3.557 | ≤ 0.03 |
| `2568` | 3.574 / 3.616 | 3.631 / 3.647 | ≤ 0.06 |
| `3056` | 3.534 / 3.593 | 3.553 / 3.631 | ≤ 0.04 |
| **`1192`** | **2.015 / 2.112 — ratio 1.05** | *not scored* | new |
| **`1346`** | **0.038 / 4.685 — ratio 123.7x** | *not scored* | new |

**`1346`'s dead half scores 0.038, which is BELOW `stereo_disparity.py`'s own `CONTENT_MIN` of
0.15** — the floor at which the script refuses a frame as blank. **Half the frame is, by this
project's own threshold, not a drawn scene.**

### 2.3 — The pictures, and they are unambiguous

Three downscaled PNGs were written beside the dumps so this can be checked by eye without a run:
`build-windows\grabs_pre_298cull\_299_eyecheck_dlgrab_{2451,2568,1346}.png`. **They are this
session's only litter and they are named so they can be deleted.**

- **`2568`** — both halves show the alley, the two guards, the pistol, the ammo readout.
  **ARM 3 works, and `298` §1.2's conclusion is correct.**
- **`2451`** — one half is the correct street; the other is a flat dark-green wedge with the gun and
  HUD drawn over it. **`292` §5a's green wedge.**
- **`1346`** — one half is the correct alley; **the other is flat, empty and dark. No HUD, no gun,
  no world.**

### 2.4 — Two supporting facts about `1192`/`1346`, and one of them names a mechanism

1. **They are a different frame class.** `texrect` is **0 / 0** in both, against **100 / 100** in
   `2451` and `2568`: **no HUD and no viewmodel** — a cutscene or an intro camera, not gameplay.
   `298` §1.2 scored four gameplay grabs and no frame of this class exists in any scored set.
2. **`[MEASURED]` `dlgrab_1346` seq `000273`: `MTX params=0x02 MODELVIEW LOAD` with EVERY ENTRY
   `±32768`.** That is `292` §5a's saturated matrix — `bondviewTransformManyPosToViewMatrix` is an
   in-place `f32->s32` fixed-point conversion and is **not idempotent**, so running it twice pins
   every entry. **`[INFERRED]`, and it is the leading candidate for the wedge: the dead half is not
   missing its geometry, it is drawing it through a matrix that collapses it to one quad.**
   `GETV_STEREO_MTXGUARD` is the knob that observes it and `292` says **mode 2 is a falsifier, not a
   fix, and must not ship.**

---

## §3 — **RESOLVED FROM SOURCE: EYE 0 IS THE LEFT HALF AND THE LEFT EYE. AND ALL THE SATURATION IS IN IT.**

**An earlier draft of this document carried an `[UNRESOLVED]` about which framebuffer half is which
eye, and asked the owner for a picture. THAT WAS A READ I HAD NOT DONE. It is documented in two
lines and the question is withdrawn** — `00-START-HERE` rule `14`: don't ask the owner to read
something the source can print.

- **`stereo.c:233`** — `*out_left = (s16)(full_left + ((ge_st_eye == 0) ? 0 : half));`
  **eye 0 = the LEFT half of the framebuffer, eye 1 = the RIGHT half.**
- **`stereo.c:387`** — `half = ge_st_sep * 0.5f; if (ge_st_eye == 0) { half = -half; }` with the
  comment **`/* eye 0 is the LEFT eye */`** — eye 0 sits −sep/2 along the camera's own right vector.

**So `dlgrab_eyecensus.py`'s labels are correct, its `--scissors` pairing (eye0 `x∈[0,640]`, eye1
`[640,1280]`, +640 apart) is correct, `298` §1.2's `LEFT half (eye 0)` heading is correct, and GATE
S3's sign test — the RIGHT eye's image FURTHER LEFT, printed as a NEGATIVE `dx` — reads as written.**
Nothing is `[UNRESOLVED]` and `RUN-SHEET-299` §4.2 no longer asks the owner anything.

### 3.1 — WHAT WAS ACTUALLY BEHIND THE APPARENT PARADOX

The paradox was *"the half with MORE geometry is the half that looks wrong."* It dissolves the
moment the matrices are counted rather than the draws. `[MEASURED]`, MTX commands whose entries sit
at ±32768 (≥12 of 16), split at the per-eye viewport loads:

| dump | arm | MTX eye0 / eye1 | **SATURATED eye0 / eye1** |
|---|---|---|---|
| `2451` | R1 `REBUILD=0` | 204 / 94 | **0 / 0** |
| `2754` | R1 `REBUILD=0` | — | **0 / 0** |
| `2568` | R2, both eyes good | 223 / 223 | **0 / 0** |
| `3056` | R2, both eyes good | — | **0 / 0** |
| **`1192`** | **R2, eye dead** | 73 / 14 | **2 / 0** |
| **`1346`** | **R2, eye dead** | 73 / 14 | **5 / 0** |

**EVERY SATURATED MATRIX IN THE SET IS IN EYE 0, AND THEY OCCUR ONLY IN THE TWO DEAD-EYE FRAMES.**
`292`'s own comment on `bondviewTransformManyPosToViewMatrix` describes exactly this and calls it
*"the green wedge across the left eye"* — and eye 0 **is** the left eye. **The mechanism `292` named
is present in the ARM 3 build, in the frames that fail and in none of the frames that pass.**
`RUN-SHEET-299` §2b is the arm that tests it, with the knob's own pre-registered null.

### 3.2 — AND A LIMIT ON THE ENERGY INSTRUMENT, WHICH `298` §1.2 NAMED AND THIS SESSION HIT

`298` §1.2 says of per-half texture energy: *"its limit is that it measures how much is drawn, not
what."* **That limit is what made eye 0 look starved.** A half filled by ONE huge flat quad and a
half with nothing drawn in it both score near zero. `2451`'s eye 0 has **204 matrices and 3,144
triangles** and scores **0.411** — it is not empty, it is flat. **Do not read a low energy as
"missing geometry" without the DL census beside it**; the two instruments answer different
questions and this session needed both.

**`298` §1.2's CONCLUSION IS UNAFFECTED** — it rests on the ratio and on which figure moved, and
R2's per-eye figure equalling R1's good eye still says the starved half came up.

## §4 — **`GETV_STEREO_REBUILD_REPORT=600` IS A SPOT CHECK, NOT A CENSUS. `[MEASURED]` FROM SOURCE.**

`chrprop.c`: `gePropsSnapshotTickZDepth()` — called once per frame, from inside `lv.c`'s simulation
gate — **resets `ge_props_rb_chr`, `ge_props_rb_obj`, `ge_props_rb_skip` and `ge_props_rb_eyes` every
tick.** `gePropsRebuildReport()` prints them when `frames % cadence == 0`. **So the SUMMARY line
carries the counters of ONE frame — the frame it happened to land on — and says nothing about the
599 before it.**

**`298` §1.1 reads six such lines as *"the driver is not admitting a subset — it walks
`g_OnScreenPropList` and takes all of it."* Six spot checks cannot support that sentence**, and
§2 above is the counter-example: on the frames `1192`/`1346` the second eye emitted nothing, and the
nearest SUMMARY (`frames=1200`, `list=1 chr=0 obj=0 skipped=1`) reported a green-looking
`eyes-rebuilt=1`.

**THE INSTRUMENT IS ALREADY CAPABLE OF BEING RIGHT AND IT COSTS NOTHING: `GETV_STEREO_REBUILD_REPORT=1`
PRINTS EVERY FRAME.** `RUN-SHEET-299` §2 and §4 use `1`. A version of `=600` that accumulated
min/max over its window instead of printing one frame's snapshot would be one line and a build; it
is named, not written.

**THIS IS `288` §6's SHAPE — reading a counter without reading the loop it sits in — and `289` R2's
masked zero one level over. Sixth and seventh instances of `275` §1.**

---

## §5 — THREE SMALLER OFFLINE RESULTS, ALL FREE

1. **`GETV_NEARCLAMP` HAS NO BANNER AND CANNOT BE SHADOWED.** `[MEASURED]`: one read site only
   (`gfx_pc.c:3743`, `getenv` latched into a function-static) and **it is not a key in
   `ge_config.c`**, so the per-user cfg cannot beat it the way it beats `GETV_FILTERING`. Its
   observable is the `[getv][far]` census, and **the census is stricter than a banner because it
   reports behaviour rather than resolution.** The identity is exact on last session's own logs:
   `clamped = straddle + all_near` — E `22635+50=22685`, D `23540+54=23594`, F `0` with
   `straddle=18439`. **`RUN-SHEET-299` §1.0 makes that identity a gate.**
2. **`298` §5's SCOPE CLAIM IS INDEPENDENTLY RE-VERIFIED.** `grep` for direct `config*` assignment
   in `ge_config.c` returns **`:421`, `:424`, `:428` and nothing else**, all inside
   `key_filtering()`. **Every other `GETV_*` on every block of `RUN-SHEET-299` obeys
   environment-over-file precedence.** `configWidescreen` is untouched, so `GETV_WIDESCREEN=0` was
   honoured in R1's and R2's blocks.
3. **BOTH OFFLINE SELFTESTS PASS ON THE BRIDGE**, against the committed tree:
   `stereo_disparity.py --selftest` -> `injected shift -37, recovered -37, mad_best=0.00
   mad_zero=84.84 PASS`; `dlgrab_eyecensus.py --selftest` -> `SELFTEST PASS`, its subset detector
   firing on the synthetic negative. **This is the bridge's `python3`, not the main PC's** —
   `RUN-SHEET-295` §11's caveat applies unchanged.

---

## §6 — WHAT THIS SESSION DELIBERATELY DID NOT DO

**No build, no run, no commit, no source file changed.** The two one-line fixes `298` identified —
`GL_DEPTH_CLAMP` in `gfx_opengl.c` and `configFiltering`'s missing `over` guard — are **still not
written**, and `NEXT-SESSION-PROMPT-299` is explicit that neither is started before the
`GETV_NEARCLAMP` A→B→A. **`00-STATE` was not edited**: every finding here is a candidate for §3, §4
and §6 and none of it should land there until the owner has run `RUN-SHEET-299` §1 and §2, because
§2 is what decides whether §0's headline is a frame-class caveat or a retraction.

Also untouched: `297` §12's mine crash and its two non-equivalent corrections; the explosion
texture; the filtering question.

---

## §7 — FALSIFIERS, STATED BEFORE THEY RUN (rule `15`)

1. **`RUN-SHEET-299` §2's six near-consecutive grabs all come back equal-eyed.** Then the dead eye
   is not per-frame, §0 is a frame-class caveat on `298` and not a retraction, and the next question
   is what the no-HUD class does differently.
2. **They alternate good / dead.** Then ARM 3 rebuilds on some frames and not others, and the
   owner's *"if I move any little bit, it goes down or goes away"* acquires a second candidate
   mechanism that has nothing to do with the near-plane clamp. **That would outrank everything on
   the board.**
3. **All six come back dead.** Then `2568` is the outlier and something about the original R2 run
   was not reproduced — check the four ARM 3 banners before believing it.
4. **`RUN-SHEET-299` §2b's `GETV_STEREO_MTXGUARD=1` reports `already-converted=0`.** Then the knob's
   own printed sentence applies — *"the saturated matrix came from somewhere else and this diagnosis
   is WRONG"* — and §3.1's count stands as an observation with its attribution dead.
5. **N1/N2/N3 come back present / absent / present.** Then the near-plane clamp is `[MEASURED]`
   cause for bug 2 and `GL_DEPTH_CLAMP` becomes the next build.

---

## §8 — **THE RUNS. WORN BY THE OWNER 2026-09-03. `[MEASURED]`.**

Five arms, one binary (`2026-09-02 19:29`), no build. Every gate in `RUN-SHEET-299` §1.4 and §2
was checked from the logs on the bridge.

### 8.1 — **►►►►►►►► THE A→B→A PASSED. BUG 2 IS THE NEAR-PLANE DEPTH CLAMP, AND IT IS NOW `[MEASURED]` CAUSE. ◄◄◄◄◄◄◄◄**

`[REPORTED]` by the owner, in order, one line per arm:
**N1 *"yes it still does it in this run"* · N2 *"it does not do it in this run"* · N3 *"it did it in
this run."*** **PRESENT → ABSENT → PRESENT.** `RUN-SHEET-299` §1.4's first row.

**And the census says the knob took, in the only way this knob can be checked** (§5.1 — it has no
banner):

| arm | `NEAR all_near` | `NEAR straddle` | `NEAR clamped` | identity | artefact |
|---|---|---|---|---|---|
| **N1** clamp ON | 12 | 20,928 | **20,940** | `20928 + 12 = 20940` ✓ | **present** |
| **N2** clamp OFF | 150 | **8,666** | **0** | condition crossed 8,666 times, knob provably off | **absent** |
| **N3** clamp ON | 51 | 12,814 | **12,865** | `12814 + 51 = 12865` ✓ | **present** |

**N2 is not a masked zero** — `straddle` reads 8,666 (`289` R2's rule, `298` §4.2).
**Every other gate passed in all three arms:** exe `2026-09-02 19:29 / 18058803`;
`GETV_FPS=panel -> 180 Hz, QUERIED FROM SDL`; `GETV_SLOTFREE resolved to 1 (env=1)`;
`GETV_STAGE override: booting stage 29`; **zero `[getv][roomscissor]`, `[getv][proproomtest]` and
`[getv][stereo]` lines in all three** — shipping culling, mono, no silent default (`48`);
no `EXCEPTION`; all three end `game_exit requested`.

**AND ARM F's FAILURE WAS NOT REPEATED. GRABS EXIST THIS TIME: N1 four, N2 two, N3 three.**
`grabs_299_N1/`, `_N2/`, `_N3/`. The negative no longer rests on the owner's eyes alone.

**`298` §4 IS UPGRADED FROM `[REPORTED]` PLUS A CENSUS TO `[MEASURED]` CAUSE.**
`298` §8 falsifier 1 — *"A→B→A does NOT bring the artefact back"* — **did not fire.**
**THE NEXT BUILD IS `GL_DEPTH_CLAMP` IN `gfx_opengl.c`**, which `gfx_pc.c:3734` names as the exact
fix and which `[MEASURED]` is referenced in comments twice and implemented nowhere.

**►► A CAVEAT ON THE PICTURES, STATED RATHER THAN GLOSSED.** The N1 and N2 grabs are the same alley
and the same wall but **not the same camera position**, so they are corroboration and not a matched
A/B pair. **The measurement is the owner's report plus the census.** A future arm that wants a
pixel-level pair must not move between the two runs at all.

### 8.2 — **THE DEAD EYE IS NOT ALTERNATION. IT IS A BOUNDED, DETERMINISTIC FRAME CLASS.**

`299` §7 falsifier 1 **fired**: E1's fourteen grabs are **all equal-eyed**, `MODEL_MTX 39/39`,
`MODEL_VTX 17/17`, per-half energy ratio **1.0** on every one. **ARM 3 does not flicker.**

**But E2 caught the class, seven times, because its grabs started earlier in the level:**

| E2 grab | `MODEL_MTX` e0/e1 | `MODEL_VTX` e0/e1 | energy L / R | ratio |
|---|---|---|---|---|
| 744 | **38 / 0** | **16 / 0** | 3.617 / 3.676 | 1.0 |
| 769 | **38 / 0** | **16 / 0** | **0.049** / 4.467 | **90.9x** |
| 784 | **38 / 0** | **16 / 0** | 1.161 / 5.083 | 4.4x |
| 803 | **38 / 0** | **16 / 0** | **0.127** / 4.694 | **36.9x** |
| 822 | **38 / 0** | **16 / 0** | **0.046** / 4.596 | **99.1x** |
| 848 | **38 / 0** | **16 / 0** | 0.230 / 4.376 | 19.1x |
| 889 | **38 / 0** | **16 / 0** | 0.478 / 3.932 | 8.2x |
| 1556 / 1580 / 1612 | **39 / 39** | **17 / 17** | ~4.02 / ~4.07 | **1.0** |

**`1192`/`1346` were not a fluke of one short re-run. The class reproduces on demand.**

### 8.3 — **AND `REPORT=1` PAIRS EVERY GRAB WITH ITS OWN FRAME'S CENSUS. THE MECHANISM IS THE SKIP.**

| frames | `rebuild] SUMMARY` on that exact frame | eye 1 |
|---|---|---|
| 744, 769, 784, 803, 822, 848, 889 | `list=1 \| eyes-rebuilt=1 chr=0 obj=0 **skipped=1**` | **0 models** |
| 1556, 1580, 1612 | `list=1 \| eyes-rebuilt=1 **chr=1** obj=0 skipped=0` | **39 matrices** |

**SAME LIST SIZE. THE DIFFERENCE IS WHETHER THE ONE LISTED PROP WAS REBUILT OR SKIPPED.**
`chrprop.c`'s `gePropsRebuildRenderPass()` has **two** `ge_props_rb_skip++` sites and the census
cannot tell them apart:

1. `(prop->flags & (PROPFLAG_ENABLED|PROPFLAG_ONSCREEN)) != both` — **whose own comment says
   *"this cannot happen today."*** If this is the one firing, that comment is falsified.
2. the type `else` — *"explosion, smoke, viewer — item 4 above"*, a deliberate exclusion.

**ONE `printf` SEPARATES THEM AND IT IS THE NEXT BUILD AFTER `GL_DEPTH_CLAMP`.** Until it runs,
which branch fires is `[UNDETERMINED]` and **must not be asserted either way.**

**►► AND THE CLASS IS DETERMINISTIC. `[MEASURED]`: E1 and E2 report the SAME skip counts —
372 frames at `chr=0 obj=0 skipped=1` and 169 at `chr=1 obj=0 skipped=1` — in runs of 3,444 and
2,095 reported frames.** Identical counts across two different runs of different length is not
noise; it is a fixed opening segment of the level, ~541 frames ≈ 3 s at 180 Hz. **Every level starts
with it and it is the first thing the player sees.**

### 8.4 — **`292`'s DOUBLE CONVERSION IS ALIVE IN THE ARM 3 BUILD, AND THE KNOB'S OWN NULL DID NOT FIRE.**

`run_299_E2_mtxguard_observe.log`, at exit:

```
[getv][mtxguard] arrays=144716 already-converted=11902 skipped=0
```

**8.2% of every array reaching `bondviewTransformManyPosToViewMatrix` is already converted**, and
**every hit the knob printed is `eye=1`** — matching `292`'s original measurement exactly. The
knob's own pre-registered null — *"already-converted=0 means the saturated matrix came from
somewhere else and this diagnosis is WRONG"* — **did not fire**, so `299` §3.1's attribution stands.

**►► AND ONE THING NO DOCUMENT PREDICTED: MOST OF THE HITS ARE `NaN`, NOT FIXED POINT.**
`m[0][0]=nan` on seven of the eight printed entries, with `m[3][3]` values like
`-5.07e30` and `26388279066624.0`. The guard's test is `!(v==v) || |v|>20000` and **NaN is a
different fault from a re-read fixed-point word.** A NaN matrix is not "converted twice"; it is
arithmetic on uninitialised or freed arena memory. **`292`'s mechanism explains the saturation; it
does not explain a NaN, and nothing in the tree has looked at that.** `[MEASURED]`, unexplained,
and it belongs in the next session's ranking.

### 8.5 — HOUSEKEEPING: THE RE-RUN RULE BIT AGAIN, HARMLESSLY

The owner re-ran N2 to capture F9 grabs of the clean state, and it **overwrote
`run_299_N2_nearclamp_off_B.log`** — the rule `298` §6 wrote and `RUN-SHEET-299` §1.4 restated,
firing for the second session running. **No evidence was lost this time** (the surviving log is the
re-run, and it is the one with the grabs), but the file mtimes now read N1 `01:57:30`, N3 `01:59:00`,
N2 `01:59:36`, so **the arm order on disk is not the arm order that was run.** Recorded so nobody
later reads the timestamps as the sequence.

---

## §9 — **WHAT WAS WRITTEN AFTER THE RUNS. THREE SOURCE CHANGES, ONE NEW HARNESS, NOTHING BUILT.**

**The A→B→A earned the fix, so §8.1's `[MEASURED]` cause is now implemented.** Nothing here has
been compiled by a real compiler against real GL headers — **the bridge has no GL headers**
(`gcc: GL/gl.h: No such file or directory`), so **the GL path of `ge_depthclamp.c` is validated by
its harness and by inspection only, and the build is the gate.** Said out loud rather than assumed.

### 9.1 — `GL_DEPTH_CLAMP`, and it lives in a TRACKED file on purpose

| file | tracked? | change |
|---|---|---|
| **`getv/port/fast3d/ge_depthclamp.h`** | **NEW, ours, TRACKED** | the interface and the whole rationale |
| **`getv/port/fast3d/ge_depthclamp.c`** | **NEW, ours, TRACKED** | knob, support test, enable, verify, banner |
| `getv/port/fast3d/gfx_opengl.c` | gitignored, **regen** | `#include` + **one call** after `glDepthFunc` |
| `getv/port/fast3d/gfx_pc.c` | gitignored, **regen** | `#include` + **two `&& !ge_depth_clamp_active()`** |

**`268` LOST `GETV_DLGRAB` FOR TWO DAYS BECAUSE A KNOB LIVED ONLY IN A REGENERATED FILE.** So all
of the logic is in the two new tracked files and the two regenerated ones carry four lines of hook
between them. **The regen is therefore OWED before the native commit and its gate is `15/15`.**

**NO NEW ENTRY POINTS.** Depth clamping is a single enable token — `0x864F` in ARB, EXT, NV and
3.2 core alike — so this needs no GLEW symbol and no function pointer, only `glEnable()`, which is
core GL 1.0. **The include block is `gfx_opengl.c`'s, copied verbatim rather than invented**,
because that block is the only one in this tree proven to reach GL's headers on all four targets.

**THE KNOB IS OFF-ABLE, NOT ON-ABLE.** `299` §8.1 measured the per-vertex clamp as the defect, so
the fix ships enabled and **`GETV_DEPTHCLAMP=0` restores the pre-`299` behaviour exactly** — which
is what makes the A/B possible without a second build (rule `2`, rule `48`).

**BOTH PLANES STAND DOWN, NOT JUST THE NEAR ONE.** `GL_DEPTH_CLAMP` clamps after interpolation and
disables z clipping at **both** planes, so leaving the per-vertex FAR clamp running would
re-introduce the same gradient tilt at the far plane. `GETV_FARCLAMP` and `GETV_NEARCLAMP` both
remain reachable and both are now additionally gated on `!ge_depth_clamp_active()`.

**THE OBSERVABLE, AND IT IS DELIBERATELY THE SAME ZERO §8.1 USED:** with the extension active the
`[getv][far]` census must read **`clamped=0` on BOTH planes with `straddle` large.** That zero is
the banner's receipt, not a masked zero — and the banner says so in its own text so the next reader
does not have to remember.

**IT VERIFIES ITS OWN ENABLE.** `glEnable` then `glGetError()` **and** `glIsEnabled()`; a driver
that advertises the extension and then refuses is reported as unavailable by name rather than
assumed to have worked (rule `15`).

### 9.2 — `configFiltering`'s missing `over` guard. `298` §5's one-liner, written.

`ge_config.c:413`'s `key_filtering()` wrote the global unconditionally while `put(...)` on the next
line obeyed precedence — the two mechanisms its own comment says must never disagree, disagreeing.
A new `set_filtering(n, over)` gives the plain global the same precedence `put()` gives the
environment: **assign only when `over` is set or `getenv("GETV_FILTERING") == NULL`**, because
`GETV_FILTERING` is read by `port_support.c`'s constructor before `main()`. **`[MEASURED]` offline:
`grep` for direct `config*` assignment in `ge_config.c` now returns nothing.** The gate is a run
whose banner reads `filtering=0` with `GETV_FILTERING=0` set; it voided two owner cycles.

### 9.3 — The skip split. **§8.3's `[UNDETERMINED]` becomes answerable by one run.**

`chrprop.c` had **two** `ge_props_rb_skip++` sites and one counter, and §8.3 could not say which one
puts the dead eye on screen. Split into `flag=` and `type=`, both printed in the SUMMARY:

- **`type=`** — explosion, smoke or the viewer: the deliberate exclusion of item 4. Non-zero here is
  the design working as written.
- **`flag=`** — the prop lost `ENABLED|ONSCREEN` between the snapshot and the pass. **That site's
  own comment says *"this cannot happen today."* A non-zero `flag=` FALSIFIES that sentence** and
  means a per-eye admission has appeared from somewhere. The GATE line says so too.

26 insertions / 3 deletions, and **`-w` reads the same, so it is real code and not the CRLF ghost.**

### 9.4 — `getv/tools/depthclamp_harness.{c,sh}`. **NEW, tracked. `17 checks, 0 failed`.**

Compiles the REAL `ge_depthclamp.c` with `GE_DEPTHCLAMP_NO_GL` under `-Wall -Wextra -Werror` and
drives the two decisions that can be silently wrong on a machine nobody tested — **a wrong TRUE
enables an unsupported token and takes near-plane clipping with it; a wrong FALSE silently leaves
the artefact on screen.** It includes the negatives on purpose: `OpenGL ES 3.2` must NOT count as
core (ES has no core depth clamp at any version), `10.0` must not parse as `1.0`, a NULL extension
string (what 3.2 core returns) must not crash, and **`GL_ARB_depth_clamp_but_not_really` must read
FALSE — which a bare `strstr()` would get wrong.**

**WHAT IT CANNOT DO, STATED:** prove the owner's driver accepts `glEnable(GL_DEPTH_CLAMP)`, or that
the hook sits at the right point in `gfx_opengl_init()`. That is the build and the run.

### 9.5 — Offline gates re-worn after every edit

- `getv/tools/depthclamp_harness.sh` → **`17 checks, 0 failed` / `VERDICT PASS`**
- `getv/tools/stereo_harness.sh` → **`63 passed, 0 failed` / `VERDICT PASS`**, its nine-file
  syntax gate covering the edited `chrprop.c` with the build's own four flag groups
- `ge_config.c` → `gcc -fsyntax-only` with the port flag set: **clean**
- `ge_depthclamp.c` → clean under `-Wall -Wextra -Werror` on **both** inert paths
  (`GE_DEPTHCLAMP_NO_GL`, and `RAPI_GL` undefined)

**ALL OF IT UNDER THE BRIDGE's `gcc 11.4.0`, NOT THE MAIN PC's** — `RUN-SHEET-295` §11's caveat is
unchanged and §1 of any build block re-runs them there.

### 9.6 — **AND IT BUILT. `[MEASURED]` 2026-09-03 02:40.** `RUN-SHEET-300` §1-§3 WORN.

Regen first, then the build. `goldeneye.exe` **18,062,771 bytes** at `02:40` (was 18,058,803 at
`2026-09-02 19:29`); `windows port layer: 59 built, 0 failed` and **0 failed in every group**;
`goldeneye_300.map` saved beside the binary.

**THE ONE ASSUMPTION THE BRIDGE COULD NOT TEST IS SETTLED: the glob saw the new file.**
`build_windows.ps1:341` globs `port/fast3d`, and `goldeneye_300.map:5991` has
`ge_depthclamp.o` inside `libge.a` with **`0x360` bytes of `.text`** and all three symbols at real
addresses — `ge_gl_parse_version` `0x14011a487`, `ge_gl_has_extension` `0x14011a595`,
`ge_depth_clamp_init` `0x14011a5f4`. Its GL references resolve to **`glIsEnabled` and
`glGetError`** (`:1116`, `:1124`), so **the verify path is really linked and was not
dead-stripped** — which matters, because a `glEnable` whose result is never checked is exactly the
instrument-that-cannot-fail this project keeps retracting.

**BINARY STRING GATE — all six present** (`grep -a` on the exe, the `297` §3 method): the two
`[getv][depthclamp]` banners, the `GETV_DEPTHCLAMP=0` line, and the skip split's
`skipped=%d (flag=%d type=%d)` and `a non-zero flag= falsifies`.

**►► WHAT THIS DOES NOT ESTABLISH, AND IT IS THE WHOLE QUESTION: whether the driver accepts the
enable and whether the artefact goes away.** `RUN-SHEET-300` §4's D1/D2 is that gate and it has
**NOT RUN**. The banner is designed to say `UNAVAILABLE` by name if the enable is refused, so the
first line of D1's log answers it — but a string in a binary is not a run (`279` §7).
