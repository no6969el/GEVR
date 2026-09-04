# `305` — THE CENSUS COMPARES SETS, THERE IS A REORDER IT COULD NEVER SEE, AND IT IS NOT THE POLYGON

**`RUN-SHEET-304` §2 IS WORN, 2026-09-03.** Offline, no build, no game, no commit.
Binary untouched: `45756E5A…3F92`, 18,070,774 bytes.

**Everything below was measured on the BRIDGE's `python3 3.10.12`, not the main PC's `py` — `H7`.
`RUN-SHEET-305` §1 re-wears every number under `py` before any of it is quoted forward.**

---

## §0 — THE ONE THING TO READ IF YOU READ NOTHING ELSE

**§2's THREE READS CAME BACK NULL, NULL, AND AN ANSWER — AND THE ANSWER CLOSES THE DISPLAY LIST
AS A PLACE TO LOOK AT ALL.**

| | |
|---|---|
| **1** | **`dlgrab_eyecensus.py` COMPARES DL CALL TARGETS AS A **SET*** (`:96-97`, `set(a['calls']) - set(b['calls'])`). A frame whose two eyes call the same lists in a **different order** scores `only in eye0 = 0`, `only in eye1 = 0` and reads PERFECT. **Four documents quote `dlgrab_C1_4676`'s census as evidence, and `4676` is exactly such a frame** |
| **2** | **THE REORDER IS REAL, IT IS STRUCTURAL, AND IT PREDATES `303`.** `[MEASURED]` over all **256 dumps**: 4 permutations, 168 refused (mono), 52 admission differences, 32 order-identical. Three of the four are **DL calls 29–36, eight calls, a CYCLIC ROTATION BY THREE** — on two different binaries and two different address spaces |
| **3** | **AND IT IS NOT THE POLYGON, AND NOT `4676`'s DIVERGENCE EITHER.** The two admissible pre-`303` frames that carry the identical rotation — `dlgrab_2928` and `dlgrab_2957`, announced by exactly one log — are **0 differing pixels, 0 blobs** under `stereo_eyediff.py`. **The reorder produces no picture.** `2336` and `V1_2732`, which DO carry a polygon, are **order-identical** |

**SO BOTH DISPLAY-LIST EXPLANATIONS ARE NOW EXCLUDED BY MEASUREMENT, ON TOP OF THE TWO `303`
EXCLUDED.** The polygon is not an admission loss (`303` §5), not `292`'s double conversion
(`303` §4), not an arena divergence (§1.2 below), and not a draw-order divergence (§1.4).
**Everything the dump records is now eliminated, and the dump records ADDRESSES, never CONTENTS.
That is the next instrument and §4 names it.**

**THE COUNT OF FILED FIXES THAT WERE WRONG IS STILL FIVE. This section was one keystroke from
making it six** — the rotation is the most convincing thing this project has found in three
sessions, and the falsifier says it draws nothing.

---

## §1 — `RUN-SHEET-304` §2, READ BY READ

### 1.1 — READ 1, the per-eye `MOVEMEM` line: **NULL, and the question it was asked is answered NO**

The sheet asks: *"if the two eyes name the SAME view-matrix address, the second eye is drawing
with the first eye's view."* `[MEASURED]` on `dlgrab_C1_4676`, and identically on all six other
`C1` dumps and all seven `V1` dumps:

```
eye0 MOVEMEM  0380:605DBEA8  0386:5F23BC08  0388:5F23BC00  0384:605DBFF8  0382:605DC008
eye1 MOVEMEM  0380:605DC758  0386:5F23BC08  0388:5F23BC00  0384:605DC8A8  0382:605DC8B8
```

The index bytes are `gbi.h:1270-1274`: **`0x80` `G_MV_VIEWPORT`, `0x82` `G_MV_LOOKATY`, `0x84`
`G_MV_LOOKATX`, `0x86` `G_MV_L0`, `0x88` `G_MV_L1`.** So the three per-eye view quantities —
viewport, both lookat vectors — are **distinct buffers in every dump**, and the only two shared
addresses are **the two LIGHTS**, which are static (`5F23BC00/08` is in the image, not in the
arena) and are byte-identical in every dump of every arm, `V2` included, where eye1 gets nothing.

**►► AND IT IS A NULL IN THE STRONG SENSE: the same five addresses appear on the CLEAN frames
and on the polygon frames.** A read that does not move between the frames that differ cannot be
what makes them differ. `279` §7 applied to a read rather than to an arm.

### 1.2 — READ 2, `--arena`: **`MODEL_VTX fresh=0` IS STILL ZERO — AND IT IS A CONSTANT, NOT A FINDING**

The sheet says: *"with `303`'s rebuild admitting the viewer, `fresh` should no longer be zero —
and if it still is, the rebuild is producing state nobody consumes."* `[MEASURED]`:

```
MODEL_MTX(3) eye1  distinct=3   reused-from-eye0=0   fresh=3   above-eye0-high-water=3
MODEL_VTX(4) eye1  distinct=17  reused-from-eye0=17  fresh=0   above-eye0-high-water=0
   -> EYE 1 ALLOCATED NOTHING. It is replaying eye 0's arena.
```

**`fresh=0` on the MODEL_VTX segment in EVERY ONE of the fourteen `C1`+`V1` dumps** — clean
frames and polygon frames alike, and `V1`'s six opening frames read `16/16 fresh=0` the same way.
**MODEL_MTX is the segment the rebuild touches (`fresh=2` in `V1`'s opening, `fresh=3` in the
gameplay frames, always above eye0's high water); MODEL_VTX it never touches.**

**►►►► SO THE STANDING FACT IS: THE SECOND EYE GETS ITS OWN MATRICES AND EYE ZERO'S VERTICES.**
That is a real and previously unwritten statement about what ARM 3 rebuilds. **It is NOT an
explanation of anything in `303` §5**, because it is the same on the frames with no divergence at
all. `293`'s `fresh=0` was measured when eye1 allocated *nothing*; this `fresh=0` sits beside
`MODEL_MTX fresh=3`, which is a different situation with the same number — **`299` §4's shape,
one segment over.**

### 1.3 — ►►►► READ 3, AND THE FIRST HALF OF THE ANSWER: **THE CENSUS COMPARES SETS**

`dlgrab_eyecensus.py:96-97`:

```python
only0 = set(a['calls']) - set(b['calls'])
only1 = set(b['calls']) - set(a['calls'])
```

**A SET DIFFERENCE.** It answers *was this display list submitted to both eyes*, which is the
question it was built for and the question that closed GROUP `B`. **It cannot answer *was it
submitted in the same place*, and nothing else ever asked.**

`getv/tools/dlgrab_dlorder.py` (new, `--selftest` **7 checks 0 failed**, check `B` is a pure
reorder that a set comparison scores clean) reads the **ordered** sequence. `[MEASURED]` over
every dump this project has — **256 files, 24 `grabs_*` folders**:

| verdict | count |
|---|---|
| `refused` — one `gSPViewport` load, a mono dump | **168** |
| `admission` — the sets differ; the census's question, handed back to it | **52** |
| `equal` — same calls, same order | **32** |
| **`permuted` — same calls, DIFFERENT ORDER** | **4** |

**AND THE FOUR ARE ONE SIGNATURE.** Three of them are **DL calls `[29..36]`, eight calls, a
cyclic rotation by three**, across two binaries and two unrelated address spaces:

| dump | arm | span | shape |
|---|---|---|---|
| `grabs_299_E1/dlgrab_2928` | `299` E1 | `[29..36]` | 8 calls, **rotation by 3** |
| `grabs_299_E1/dlgrab_2957` | `299` E1 | `[29..36]` | 8 calls, **rotation by 3** |
| `grabs_303_C1/dlgrab_C1_4676` | `303` C1 | `[29..36]` | 8 calls, **rotation by 3** |
| `grabs_pre_298cull/dlgrab_7360` | — | `[14..23]` | 10 calls, two groups swapped, **not a rotation** |

`dlgrab_7360` is `run_295_S2a_restore_off.log`'s — the `VIEWRESTORE=0` falsifier, **whose guard
is supposed to fire** (`298` §3, `304` §2). It is inadmissible and it is listed for completeness
only.

**►► THE OTHER THREE ARE ADMISSIBLE.** `dlgrab_2928` and `dlgrab_2957` are announced by **exactly
one log**, `run_299_E1_percensus.log`, whose banners read stereo ON, `separation=0.000`, `mode=1`,
ARM 1 ON, **ARM 3 `GETV_STEREO_REBUILD=1`** — the same shape as `C1`. `279` §2 satisfied.

**SO THE REORDER PREDATES `303` §2's VIEWER FIX, ON ADMISSIBLE FRAMES, WITHOUT A RUN.** That is
a dating answer `304` §2 could not get for the polygon, and it is one the archive CAN give,
because the reorder leaves a signature in the dump where the polygon leaves none.

### 1.4 — ►►►►►►►► AND THE SECOND HALF, WHICH IS THE FALSIFIER: **THE REORDER DRAWS NOTHING**

Before this was written down as `4676`'s cause it was pointed at the frames it should be boring
on — **which is the whole of `279` §7 and the whole of what `304` §1.3 cost.**

`stereo_eyediff.py`, per channel, on the two admissible frames that carry the identical rotation:

| frame | carries the rotation | largest blob | total differing px | blobs |
|---|---|---|---|---|
| `dlgrab_2928` | **yes, `[29..36]` by 3** | **0 px** | **0** | **0** |
| `dlgrab_2957` | **yes, `[29..36]` by 3** | **0 px** | **0** | **0** |

**ZERO DIFFERING PIXELS. NOT "under the threshold" — ZERO.** The two eyes are identical to the
last pixel on both frames, and both carry the reorder in full.

**►►►► THEREFORE THE ROTATION OF THOSE EIGHT CALLS DOES NOT CHANGE THE PICTURE, AND IT IS NOT
WHAT DRAWS `4676`'s 109,920 DIFFERING PIXELS.** A reorder is invisible wherever the geometry is
opaque and z-buffered, which is what these eight evidently are.

**BOUND, AND IT IS THE ONLY THING KEEPING THIS FROM BEING AIRTIGHT:** the falsifying frames are
on the `299` binary in a different scene from `4676`'s. The rotation is the same ordinal span,
the same length and the same shift, which is why they are comparable at all — but *"the same
reorder is harmless HERE"* is not *"a reorder is harmless everywhere"*. **`RUN-SHEET-305` §2 is
the arm that closes it and it costs nothing.**

### 1.5 — AND THE OTHER TWO POLYGON FRAMES ARE ORDER-IDENTICAL

`dlgrab_C1_2336` and `dlgrab_V1_2732` — the two frames that carry `303` §5's polygon — verdict
**ORDER IDENTICAL**, exactly like the five clean `C1` frames and the six clean `V1` frames.
Segment-by-segment, every one of their per-prop command blocks matches its opposite number
**command for command, with every difference confined to the `w1` address word** (the per-eye
segment rebase).

**SO READ 3's QUESTION — same fault at amplitude, or a second one — IS ANSWERED, AND THE ANSWER
IS NEITHER OF THE TWO OFFERED.**

| | |
|---|---|
| `2336` / `V1_2732` | **display list identical in content AND order.** The polygon is downstream of everything the dump records |
| `4676` | **display list carries a permutation** — but the same permutation on two admissible frames draws **0 px**, so it does not account for `4676` either |

**`4676` IS NOT `2336` AT AMPLITUDE. IT IS A FRAME THAT CARRIES A SECOND, SEPARATE, HARMLESS
DEFECT ON TOP OF WHATEVER `2336` HAS.** Its `38%` largest-blob concentration was the hint that
sent this section looking, and the hint was right that `4676` is different — **and wrong about
what is different, because the thing that is different does not draw.**

### 1.6 — `H13` CLOSES: THE CONSTANT SEVEN IS THE SECOND EYE'S CLEAR

`303` §7 recorded `cmds` reading `6587 / 6580` in every grab of every stereo run, *"too small to
be `303` §5's polygon, too consistent to be noise, and no document explains it."*

`[MEASURED]` on **all 21 dumps of `grabs_303_C1`, `grabs_303_V1` and `grabs_303_V2`** — every one
identical:

```
eye0 tail (9 cmds)  SETZIMG RDPPIPESYNC SETOTHERMODE_L SETCIMG SETOTHERMODE_H
                    SETFILLCOLOR SETSCISSOR FILLRECT RDPPIPESYNC
eye1 tail (2 cmds)  RDPFULLSYNC ENDDL
```

**9 − 2 = 7.** The first eye's half ends by clearing the colour and depth targets for the second;
the second eye's half ends the display list. **Benign, explained, and constant by construction —
it is the same in `V2`, where eye1 is dead.** `H13` closes with no code change.

---

## §2 — ►►►► THE PROVENANCE SCARE THAT WAS NOT ONE, AND IT IS RECORDED BECAUSE IT NEARLY BECAME A RETRACTION

Every log pairs a dump with a picture one number apart, 14 of 14:

```
[getv][dlgrab] frame 4676 -> dlgrab_C1_4676.txt
[getv][shot]   frame 4677 -> dlgrab_C1_4676.bmp
```

Read as two frame numbers, that voids the sentence *"SAME COMMANDS, DIFFERENT PICTURE"* in `303`
§5, `304` §0, `00-STATE`'s currency line and `PRIORITY-BOARD-299` GROUP `C` — because it would
mean no picture has ever been compared with its own frame's commands. **It was drafted as this
session's first retraction.**

**IT IS NOT ONE.** `port_render.c:748-759` sets `ge_shot_request` at the end of the dump, inside
the frame's own render, and `gfx_opengl.c:1495-1520` consumes it in **that frame's**
`gfx_opengl_end_frame()`. The picture and the list are the same frame by construction, as
`port_render.c`'s own comment says and as `93` paid for. **`fno` in `gfx_opengl.c:1497` is a
PRIVATE counter incremented at every `end_frame` from a different origin, and it reads exactly
one higher — consistently, in all fourteen pairs, which is what a fixed offset looks like and is
not what a real off-by-one would look like.**

**THE TRAP IS THE LOG, NOT THE CAPTURE: two independent frame counters print two different
numbers for one frame, and only one of them is the game's.** `RUN-SHEET-305` §3 is a one-line
banner change that makes the shot line print the dump's number; it is a diagnosis of a label, and
it is the smallest thing on this board.

---

## §2a — ►►►►►►►► `RUN-SHEET-304` §3 AND §4 HAVE BOTH BEEN RUN, AND NOBODY WROTE IT DOWN

`NEXT-SESSION-PROMPT-305` and `00-STATE` §3 both list §3 as *optional and owed* and §4 as *one
`Move-Item` still outstanding*. **Both are stale.** `[MEASURED]` on disk, 2026-09-03:

- **§4 IS DONE.** The four `dlgrab_D3_*` files are in `grabs_302_D3\` and `grabs_303_V1\` no
  longer holds any. `303` §7 closes.
- **§3 IS RUN.** `run_304_FC3_road_on.log` (`ARM=FC3 START=2026-09-03T22:17:46Z`,
  `GETV_FARCLAMP=1`) and `run_304_FC4_road_off.log` (`ARM=FC4 START=2026-09-03T22:18:34Z`,
  `GETV_FARCLAMP=0`), with `grabs_304_FC3\` and `grabs_304_FC4\` beside them. **Both banners
  took. `H5`'s ARM line is present and distinct in each.**

**AND ITS COUNTERS HAVE NEVER BEEN READ. THEY ARE READ HERE, PER WINDOW, BECAUSE THE CUMULATIVE
LINE IS `H12`-VOID.** The `[getv][far]` line is a running total (`303` §3.1), so the 468 / 374
samples are differenced consecutively and the rate is quoted per print interval:

| | FC3 `FARCLAMP=1` | FC4 `FARCLAMP=0` |
|---|---|---|
| samples | 468 | 374 |
| **cumulative final `beyond_far`** | 2,065,665 of 32,840,932 = **6.3%** | 1,915,135 of 28,725,001 = **6.7%** |
| **per-window `beyond_far`** | min 0.00 · **median 3.81** · mean 5.56 · max 21.13 | min 0.00 · **median 5.47** · mean 5.98 · max 21.13 |
| windows inside `302` D3's 3.9–5.9% band | **14 of 467 (3%)** | **27 of 373 (7%)** |
| windows under 3.0% | 206 | 150 |
| `clamped == straddle` | **467 of 467 windows** | n/a, `clamped=0` throughout |
| **`clamped` per Mvtx** | min 0 · **median 1,359** · max 8,505 | 0 |

**►► THE VENUE GATE IS HALF MET AND THE READING IS THE OPPOSITE OF `303`'s.** `303` §3.1
established the two regimes: **45,000 clamped/Mvtx in the cast roll**, which is flat colour, and
**50–2,300/Mvtx on the road**, which is where the owner judges. **FC3's median is 1,359/Mvtx —
squarely the ROAD regime.** The knob also took at full strength in **every window** (`clamped ==
straddle`, 467 of 467), which is `303` FC1's receipt reproduced per window rather than once.

**►► BUT THE GATE AS WRITTEN IS NOT MET, AND SAYING SO IS THE POINT.** `RUN-SHEET-304` §3's gate
was *"per window at `302` D3's 3.9–5.9%"*, and **only 3% (FC3) and 7% (FC4) of windows land in
that band.** The run is not uniformly under 3% either — it spans 0% to 21%. **It is `H12` one
level down: even the per-window distribution is bimodal, so a median is a summary of two places
and the band was the wrong shape of gate.** The last 40 windows of both arms read median 0.00%,
so both runs ended somewhere with no far geometry in them at all.

**AND THE ARM'S REAL GATE IS A PICTURE, AND NO `[REPORTED]` IS ATTACHED TO EITHER RUN.**
`303` §3 is explicit that the counters cannot discriminate and the owner's eyes are the verdict.
**§3's STATUS IS: RUN DONE, KNOB PROVEN TO TAKE, VENUE PROVEN TO BE THE ROAD, VERDICT PENDING ON
ONE SENTENCE FROM THE OWNER.** `RUN-SHEET-305` §4 asks for it and asks for nothing else.

**►► AND THE DISCIPLINE NOTE: THE COUNTERS ABOVE DO NOT COMPARE THE TWO ARMS AND MUST NOT BE
READ AS DOING SO.** FC3 carried 32.8 Mvtx and FC4 28.7 Mvtx over different walks, which is
exactly `303` §4's retraction — *"on a loop there is nothing to normalise" is true of the eyes
and false of the counters.* Each column describes its own run.

---

## §3 — WHAT DID NOT CHANGE

- **`303` §2, §3, §4, §5 and §6 all stand.** GROUP `B`'s closure, the far-clamp null,
  `already-converted=0`, the polygon itself and `H9` are untouched.
- **`304` §1 stands.** The per-channel fix, the 256-frame calibration and the sweep are what made
  §1.4's falsifier possible at all.
- **The binary is untouched and nothing was built, run or committed.** `dlgrab_dlorder.py` is
  host-side and compiles into nothing.
- **`304` §2's dating question about the POLYGON is still open.** §1.3 dates the REORDER. They
  are different faults and §2a is still the run for the polygon.

---

## §4 — ►►►► WHERE THE WORK GOES, AND THE SEARCH SPACE JUST GOT SMALL

**EVERY LEVEL THE DUMP CAN SEE IS NOW EXCLUDED FOR THE POLYGON:**

| level | instrument | verdict |
|---|---|---|
| admission — was it submitted | `dlgrab_eyecensus.py` | `39/39`, `only in eye0 = 0` — **excluded**, `303` §5 |
| the matrix conversion | `GETV_STEREO_MTXGUARD` | `already-converted=0` of 366,456 — **excluded**, `303` §4 |
| the arena — who allocated what | `--arena` | identical on clean and polygon frames — **excluded**, §1.2 |
| the order — where it was submitted | `dlgrab_dlorder.py` | order-identical on both polygon frames — **excluded**, §1.5 |

**►►►►►►►► WHAT IS LEFT IS THE ONE THING NO INSTRUMENT IN THIS PROJECT HAS EVER READ: THE
CONTENTS OF THE BUFFERS THE COMMANDS POINT AT.** `GETV_DLGRAB` records `w0` and `w1` — opcodes
and **addresses**. Two eyes can issue byte-identical commands naming per-eye matrix buffers whose
**values** differ, and every instrument on this board would call that frame perfect. **That is
exactly the description of `2336` and `V1_2732`.**

1. **`RUN-SHEET-305` §1 — re-wear §1's numbers under the main PC's `py`.** `H7`. Seconds, no
   build. **Nothing in this document is quotable forward until it passes.**
2. **`RUN-SHEET-305` §2 — bound §1.4's falsifier**, by running `dlgrab_dlorder.py` and
   `stereo_eyediff.py` as a pair over the whole corpus and asking whether ANY `permuted` frame is
   also a pixel hit. Offline, no build. **If one is, §1.4's null is bounded to the two frames it
   was measured on and the reorder goes back on the board.**
3. **`RUN-SHEET-304` §2a — date the POLYGON with a run.** Unchanged and still owed. §1.3 dated
   the reorder and says nothing about the polygon.
4. **The next instrument: a per-eye read of `MODEL_MTX` CONTENTS**, not addresses. `[STATED]` as
   the next thing to build, not designed here — **`301` §0, and the count is five.**
5. **`304` §3 and §4 are DONE, not owed** — §2a. §3 needs **one sentence from the owner** about
   what the two arms looked like, and it needs nothing else. **`RUN-SHEET-305` §4.**

---

## §5 — FILES

| file | repo | change |
|---|---|---|
| `getv/tools/dlgrab_dlorder.py` | `goldeneye-native` | **NEW.** Ordered DL-call comparison. `--selftest` 7 checks 0 failed; check `B` fails on any set-based implementation |
| `repo/docs/305-…md` | `GoldenEyeVR` | this document |
| `repo/docs/RUN-SHEET-305.md` | `GoldenEyeVR` | §1 the `py` re-wear, §2 the falsifier's bound, §3 the shot-line label, §4 the FC3/FC4 question |
| `repo/docs/00-STATE.md` | `GoldenEyeVR` | currency, §3, §4, §6 |
| `repo/docs/PRIORITY-BOARD-299.md` | `GoldenEyeVR` | `C1` rewritten, `H13` closed, `H15` added |

**NOTHING WAS BUILT, RUN, STAGED, COMMITTED, BRANCHED OR TAGGED.**
