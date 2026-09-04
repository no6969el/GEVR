# `304` — THE SWEEP FOUND A FALSE NEGATIVE IN ITS OWN INSTRUMENT, AND THE CORPUS CANNOT DATE THE POLYGON

**`RUN-SHEET-304` §1 IS WORN, 2026-09-03.** Offline, no build, no game. §2, §3, §4 and §5 are not.

Binary unchanged: `45756E5A…3F92`, 18,070,774 bytes. **`stereo_eyediff.py` was edited by this
session and the edit is a correction, not a feature** — §1.2.

---

## §0 — THE ONE THING TO READ IF YOU READ NOTHING ELSE

**§1 WAS WRITTEN TO ASK ONE QUESTION — DOES THE ONE-EYE POLYGON PREDATE THE VIEWER FIX? — AND IT
CAME BACK WITH TWO ANSWERS, NEITHER OF THEM THE ONE IT ASKED FOR.**

| | |
|---|---|
| **1** | **THE INSTRUMENT HAD A FALSE NEGATIVE AND THE SWEEP FOUND IT.** It differenced LUMINANCE, so it called `dlgrab_S2_1176` — a frame with a **whole dead eye** — CLEAN at 1,329 px. A navy void and a brown building have nearly the same brightness. **Fixed: the difference is now per channel, and the same frame reads 4,845 px over 813 blobs** |
| **2** | **THE CORPUS CANNOT DATE THE POLYGON, AND THE REASON IS PROVENANCE, NOT THE INSTRUMENT.** The only pre-`303` frames carrying its signature are in `grabs_pre_298cull`, and **three of them are announced by NO log, one by FIVE, and one by a falsifier arm whose whole purpose was to make the eyes diverge.** `279` §2, quantified |

**AND THE DATING QUESTION IS STILL OPEN.** It is not answered "no". It is not answered at all.

---

## §1 — THE SWEEP

### 1.1 — What it ran on

`[MEASURED]`: **21 grab folders, 256 BMPs.** After the mono refusal, **81 frames are readable** —
175 are `REFUSED` by name because their dump carries one `gSPViewport` load. **GATE §1c held:
every mono grab printed a refusal and not a number.** ~0.26 s per frame, 1 m 06 s for the corpus.

### 1.2 — ►►►► THE FALSE NEGATIVE, AND IT WAS MINE

The first cut differenced the **greyscale** rows it inherited from `stereo_disparity.py`. That is
correct in a CORRELATOR, which wants luminance. **It is wrong in a DIFFER.**

`[MEASURED]` `dlgrab_S2_1176` — `301` S2, provenance clean, announced by
`run_301_S2_skipsplit.log`, and **it is a dead-eye frame**: eye0 is a near-uniform dark NAVY void
with a sliver of building, eye1 has the whole building.

| metric | greyscale (as shipped in `303`) | per channel (now) |
|---|---|---|
| largest blob | **1,329 px — scored CLEAN** | **4,845 px — HIT** |
| total differing px | 15,475 | **90,358** |
| blobs | 445 | 813 |

**The instrument missed a whole missing eye**, and it did so on the exact fault class the project
has been chasing since `292`. `dlgrab_S3_1155` (`302` §3c's own named frame) was the second false
negative and it is now a hit at 1,967 px.

**This is `H8`'s shape one level over** — a luminance figure could not tell "nothing drawn" from
"one huge flat quad" either — and it is the fifth time a metric has agreed with the answer it was
tuned on. **`--selftest` now carries check `F`: an injected patch whose RGB averages to exactly its
background's luminance must still be detected. That check fails on the `303` version of this
file.** 16 checks, 0 failed.

### 1.3 — The calibration this replaces, and it was nine frames

| | `303` §6, nine frames, greyscale | `304`, 256 frames, per channel |
|---|---|---|
| worst clean | 1,329 px (171 px under the line) | **715 px** |
| smallest hit | 2,196 px | **1,967 px** |
| gap either side of `--max-blob 1500` | **171 / 696** | **785 / 467, and NO frame lands between** |

**`303` §6's "a factor of ten, three hits, no false positives" was true of the nine frames it was
measured on and false of the corpus.** A nine-frame calibration is a hypothesis.

### 1.4 — What the sweep actually found

**41 divergent, 40 clean, 175 refused.**

| folder | divergent | clean |
|---|---|---|
| `grabs_pre_298cull` | 22 | 7 |
| `grabs_299_E1` | 0 | 14 |
| `grabs_299_E2` | 4 | 4 |
| `grabs_301_S2` | 4 | 2 |
| `grabs_302_S3` | 3 | 1 |
| `grabs_303_V1` | 1 | 6 |
| `grabs_303_V2` | **5** | 1 |
| `grabs_303_C1` | 2 | 5 |

**MOST OF THAT IS THE TOOL RE-FINDING THE FAULT THE PROJECT ALREADY KNOWS.** V2's five are the
opening frames where the fix is OFF and eye1 gets nothing; `pre_298cull`'s 22 are `292`/`293`-era
frames from before ARM 3 existed. **That is validation, not news** — and V1's ONE divergent frame
against V2's FIVE, in the same alley on the same binary, is `303` §2's fix showing up in a metric
that knows nothing about props.

**►► AND `blobs` AND `total` SAY WHICH FAULT IT IS, WHICH `303` DID NOT NOTICE.** A single polygon
CONCENTRATES; a dead or diverging eye SCATTERS:

| frame | largest / total | blobs | concentration |
|---|---|---|---|
| `dlgrab_C1_2336` | 3,331 / 3,874 | **2** | **86%** — one polygon |
| `dlgrab_V1_2732` | 23,086 / 29,387 | 53 | **79%** — one polygon |
| `dlgrab_C1_4676` | 41,570 / 109,920 | 760 | 38% — **broader, and it was always the odd one** |
| `dlgrab_S2_1176` | 4,845 / 90,358 | 813 | **5%** — a dead eye |
| `dlgrab_S3_1155` | 1,967 / 23,515 | 453 | **8%** — a dead eye |

**The ratio is a hint to take to the dump. It is not a classifier and the tool does not pretend to
be one.**

---

## §2 — ►►►► THE DATING QUESTION IS BLOCKED BY PROVENANCE, AND IT IS `279` §2 WITH A COST

Five pre-`303` frames carry the localised signature. **NOT ONE OF THEM IS ADMISSIBLE.**

| frame | announced by | admissible? |
|---|---|---|
| `dlgrab_2893` | **no log at all** | **NO** |
| `dlgrab_3393` | **no log at all** | **NO** |
| `dlgrab_5284` | **no log at all** | **NO** |
| `dlgrab_900` | **FIVE logs** — `292` S2, S2b, S2c, `295` S2, `dlgrab2_90` | **NO.** Named by frame number and overwritten repeatedly; which run wrote the file on disk is undetermined |
| `dlgrab_7360` | `run_295_S2a_restore_off.log` | **NO.** That is the `VIEWRESTORE=0` arm, whose guard is SUPPOSED to fire (`stereo_harness`: *"THE GUARD MUST FIRE"*). **A falsifier's documented side effect is not a defect** (`298` §3) |

And the two pre-`303` frames with clean provenance that DID come back divergent — `S2_1176` and
`S3_1155` — **are dead-eye frames by their concentration (5% and 8%) and by `302` §3c naming
`1155` itself.** They are the known fault, not the polygon.

**SO: NO ADMISSIBLE FRAME BEFORE `303` SHOWS THE POLYGON, AND NO ADMISSIBLE FRAME BEFORE `303`
RULES IT OUT.** `grabs_pre_298cull` is 109 BMPs and it is the only place the answer might live.

**►► THIS IS WHAT `279` §2 COSTS WHEN IT IS FINALLY BILLED.** That entry has said since `278` that
*"a log's own `dlgrab` announcements are the only admissible provenance for a dump"*. This is the
first time the rule has blocked a question rather than corrected a label. **`N2`'s `GETV_ARM`
prevents future collisions and does nothing for the 109 files already there.**

**THE DATING QUESTION NOW NEEDS A RUN, NOT THE ARCHIVE** — `RUN-SHEET-304` §2a: the same alley, the
fix ON and OFF, ten-plus grabs each, `GETV_ARM`-named, then this sweep. If the polygon appears with
`GETV_STEREO_REBUILD_VIEWER=0` as well, it is independent of `303`'s fix and always was.

---

## §3 — WHAT DID NOT CHANGE

- **`303` §2, §3, §4 and §5 all stand.** Nothing in this sweep touches GROUP `B`'s closure, the
  far-clamp null, `already-converted=0`, or the three `303` hits — all three are still hits, with
  larger numbers under the per-channel metric.
- **`303` §6's claim that `H9` is closed stands.** The instrument works; its first metric was
  wrong and the corpus found it, which is what a corpus is for.
- **The binary is untouched.** `stereo_eyediff.py` is host-side and compiles into nothing.

---

## §4 — FILES

| file | repo | change |
|---|---|---|
| `getv/tools/stereo_eyediff.py` | `goldeneye-native` | **per-channel differencing**, selftest check `F`, calibration replaced with the 256-frame sweep. **16 checks, 0 failed** |
| `repo/docs/304-…md` | `GoldenEyeVR` | this document |
| `repo/docs/303-…md` | `GoldenEyeVR` | §6 gains a dated correction pointing here |
| `repo/docs/00-STATE.md` | `GoldenEyeVR` | currency, §4, §6 |
| `repo/docs/PRIORITY-BOARD-299.md` | `GoldenEyeVR` | `H9`'s calibration corrected, `H14` added |

---

## §5 — WHERE THE WORK GOES

1. **`RUN-SHEET-304` §2 — the polygon, `dlgrab_C1_4676` first.** Unchanged, and now better aimed:
   `4676` is 38% concentrated where `2336` and `V1_2732` are 79–86%, so **it is either the same
   fault at amplitude or a second one, and that is the first thing to settle.**
2. **`RUN-SHEET-304` §2a — date the polygon with a RUN**, because the archive cannot.
3. **`304` §3 and §4** — FC3/FC4 at the road, and the `Move-Item` — both still owed.
4. **`H14`** — 109 BMPs with no admissible provenance. Nobody's to tidy, and now known to block a
   real question.
