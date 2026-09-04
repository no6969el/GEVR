> **►►►►►►►► SUPERSEDED 2026-09-03 BY `NEXT-SESSION-PROMPT-306`. KEPT IN PLACE BECAUSE RULE `2`
> DELETES NOTHING. ◄◄◄◄◄◄◄◄**
>
> The session this launched **wore `RUN-SHEET-304` §2**, and two of the statements below are now
> **FALSE** and must not be carried forward:
>
> * *"`304` §3 — FC3/FC4 at the road, optional"* and *"`304` §4 — one `Move-Item`"* — **BOTH WERE
>   ALREADY RUN** at 22:17:46Z / 22:18:34Z, and the `dlgrab_D3_*` strays were already moved. Their
>   counters are read for the first time in `305` §2a. **A run sheet's "still owed" list is a
>   claim about the filesystem; `ls grabs_*` before repeating an arm.**
> * *"in frames whose census reads `MODEL_MTX 39/39` … `only in eye0 = 0` AND `only in eye1 = 0`"*
>   offered as proof the fault is downstream — **true of the SET and false of the ORDER.**
>   `dlgrab_eyecensus.py:96-97` is a set difference and `dlgrab_C1_4676` carries an eight-call
>   cyclic rotation by three. **The claim survives for `C1_2336` and `V1_2732`; it does not
>   survive for `4676` on the census alone.** `305` §1.3, `00-STATE` §4.
>
> Everything else below stood up, including its warning about numbers read without their context
> — which is what caught both of the above.

Read `repo\docs\00-STATE.md` — the **currency line at the top** (it is `303` WORN + `304` §1
WORN, and it is the whole handover), then **§3 OWNER ACTION OUTSTANDING — the top THREE entries
are new**, then **§4 RETRACTED — SIX new entries and FOUR of them are this project's own claims
from the last two sessions**, then **§6 TRAPS — EIGHT new.** Then
**`304-THE-SWEEP-FOUND-A-FALSE-NEGATIVE-IN-ITS-OWN-INSTRUMENT` §0**, which is two paragraphs and
is the state of play. Then **`303-THE-VIEWER-WAS-THE-DEAD-EYE-AND-THE-SECOND-EYE-IS-THE-REFERENCE-FRAME`
§0 and §5** — §5 is the symptom this session is about. Then **`RUN-SHEET-304` §2 and §2a.** Then
**`PRIORITY-BOARD-299`**, where GROUP `B` and `H9` are struck through, **GROUP `C` has been
rewritten from the top**, and `H11`–`H14` are new.

Same rules as always. **You work OFFLINE. The build, every run and every commit are the owner's,
on the main PC. Supply complete copy-paste PowerShell blocks; quote a run-sheet block verbatim,
never paraphrase it. Never stage, commit, branch, merge or tag.** Bridge reads are not free
(`00-STATE` §6): `git log`, `git show` and `git diff <path>` are safe; `git status` and `git add`
are **NOT** (use `git --no-optional-locks status`), and **a bare `git status` in the decomp prints
2,106 CRLF-dirty files — always give it a path list** and pass `--ignore-cr-at-eol`.

---

## ►►►► WHERE THINGS ACTUALLY STAND ◄◄◄◄

**EVERYTHING IS COMMITTED AND ALL FOUR REPOS ARE CLEAN.** `RUN-SHEET-303` worn in full
(`94cdf01c` decomp / `c26c58d` native / `d393860` docs), then `RUN-SHEET-304` §5 (`f3c9a04` /
`71ac3b3`) and §5a (`8946e54` / `f70fe81`). Binary **`45756E5A…3F92`, 18,070,774 bytes**, with
`EXPECTED-EXE-303.txt` beside it and `goldeneye_303.map` saved. **`RUN-SHEET-304` §1 IS WORN. §2,
§2a, §3 and §4 ARE NOT.**

### 1. GROUP `B` IS CLOSED AND THE VIEWER FIX IS SHIPPING.

`303` §2: V1 reads eye1 `MODEL_MTX` **38** against V2's `0`, `only in eye0 = 0` AND
`only in eye1 = 0` on every opening grab, cumulative `viewer=0`, **not one frame with
`skipped>0` in 3,015.** `[REPORTED]`, the owner: *"it loads better than before without all that
texture in the left eye"* — **gone, not reduced**, and it was `299` §8.2's symptom rather than a
new one. **Do not reopen this group for the polygon below.**

### 2. TWO ARMS ANSWERED NOTHING, AND BOTH SAID WHY. NEITHER IS A FAILURE.

- **The far clamp** (`303` §3): FC1 far `clamped=81,076` = `straddle` exactly against FC2's `0`,
  and the owner sees the same picture in both. **`[getv][far]` is CUMULATIVE across two scenes
  that differ 15x** — the road runs 1.2–5.9% `beyond_far`, the cast roll 40–71% — **so `302` §4's
  `13.2%` is a blend and is comparable to nothing**, and the knob fires 45,000/Mvtx in the cast
  roll, which is two unlit quads and the cast text, against 50–2,300/Mvtx on the road, which is
  where the owner was judging. **`RUN-SHEET-303` §0.1's causal claim is UNANSWERED, not false.**
  `GETV_FARCLAMP` stays at its default `1`.
- **`292`'s double conversion** (`303` §4): `arrays=366456 already-converted=0 skipped=0`, upstream
  2.5x `299` E2's, and **the instrument printed its own pre-registered null.** **GROUP `C`'s
  leading hypothesis is dead.**

### 3. ►►►► THE LIVE SYMPTOM, AND IT IS A CLASS THIS PROJECT HAS NEVER SEEN.

**A flat slate polygon occludes wall geometry in ONE eye** — `dlgrab_V1_2732`, `dlgrab_C1_2336`,
`dlgrab_C1_4676` — **in frames whose census reads `MODEL_MTX 39/39`, `MODEL_VTX 17/17`,
`only in eye0 = 0` AND `only in eye1 = 0`.** Same commands, different picture. `[REPORTED]`:
*"bond bobs and it changes the output."*

**Every eye fault since `292` has been an ADMISSION fault. This one is not, and both obvious
causes are excluded by measurement.** Nothing on record names its mechanism, and **nothing in
`305` should name it without following the call.**

### 4. AND THE INSTRUMENT BUILT TO SEE IT HAD A FALSE NEGATIVE, WHICH THE SWEEP CAUGHT.

`304` §1.2: `stereo_eyediff.py` differenced **LUMINANCE** — right in `stereo_disparity.py`, which
is a CORRELATOR, wrong in a DIFFER — and scored `dlgrab_S2_1176`, **a frame with a whole dead
eye**, CLEAN at 1,329 px, because a navy void and a brown building have nearly the same
brightness. **Fixed per channel; `--selftest` carries a check that FAILS on the committed
`303` version; calibration is now 256 frames — clean tops out at 715 px, the smallest hit is
1,967, and nothing lands between.**

---

## ►►►►►►►► THE FIRST ACTION: `RUN-SHEET-304` §2. IT IS OFFLINE AND IT NEEDS NO BUILD. ◄◄◄◄◄◄◄◄

§2 opens `dlgrab_C1_4676` with `stereo_eyediff.py` and `dlgrab_eyecensus.py --calls --arena`, and
its three reads are ordered for a reason:

1. **the per-eye `MOVEMEM` line** — if both eyes name the SAME view-matrix address, the second eye
   is drawing with the first eye's view, and that is not on the board at all;
2. **`--arena`** — `293` measured `MODEL_VTX fresh=0` when the second eye allocated nothing;
   **with `303`'s rebuild admitting the viewer it should no longer be zero**, and if it still is,
   the rebuild is producing state nobody consumes;
3. **`4676`'s concentration: 38%, against `2336`'s 86% and `V1_2732`'s 79%** — settle whether it
   is the same fault at amplitude or a second one, **and say which before proposing anything.**

**►► `RUN-SHEET-304` §2's GATE IS THAT IT PRODUCES A DIAGNOSIS OR IT PRODUCES NOTHING.**

---

## ►►►► THE THING THIS SESSION SHOULD BE MOST CAREFUL ABOUT ◄◄◄◄

**A FILED FIX IS A DIAGNOSIS, NOT A PATCH — THE COUNT IS FIVE** (`H1`, `H3`, `298` §4.4, `302`
§3c, `H9`) — **AND THE LAST TWO SESSIONS ADDED FOUR RETRACTIONS OF THEIR OWN CLAIMS**: the far
clamp's causal claim, `RUN-SHEET-303` §4's *"on a loop there is nothing to normalise"* (true of
the eyes, false of the counters), `303` §6's nine-frame calibration, and *"the corpus dates the
polygon"*.

**THE COMMON SHAPE IS NOT CARELESSNESS. IT IS A NUMBER READ WITHOUT ITS CONTEXT** — a counter
outside the branch, a rate over two scenes, a metric measured on the frames that were already
understood. **Before quoting any figure in `305`, say what it is accumulated over and what would
make it move.**

**AND ONE MORE, WHICH `304` §2 BILLED FOR THE FIRST TIME:** `grabs_pre_298cull` is 109 BMPs with
**no admissible provenance** — three of the interesting frames announced by no log, one by five,
one by a falsifier arm whose guard is supposed to fire. **`279` §2 stopped being a labelling rule
and became a blocker.** When the archive cannot answer, take a run: that is `§2a`.

---

## ►►►► AFTER §2: WHERE THE WORK GOES ◄◄◄◄

- **`304` §2a — date the polygon with a RUN.** Ten-plus grabs per arm, **in GAMEPLAY**, gated on
  **concentration, not a hit count** — P2's opening frames will diverge whatever happens, because
  the fix is off there.
- **`304` §3 — FC3/FC4 at the road**, optional, **gated per window at `302` D3's 3.9–5.9%**. A run
  that stays under 3% is another `279` §7 null however clean the arms look.
- **`304` §4 — one `Move-Item`**: four `dlgrab_D3_*` files are still sitting in `grabs_303_V1\`.
- **`C1a`** — `already-converted=0` is one run and one route. **Bound it before quoting it as
  general.**
- **`H11` / `H12` / `H13` / `H14`** — the far line's mixed counters; the far census's cumulative
  blend; **the constant SEVEN commands the second eye never gets** (`cmds` 6587/6580 in every grab
  of every stereo run, and no document explains it); and `pre_298cull`'s provenance.
- **GROUP `D`** unblocked, `D1` `LOW`. **GROUP `E1`** has now survived four arms untested.

**`169` NEXT ID = `U-26`.**
