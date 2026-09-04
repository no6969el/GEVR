> **This prompt was drafted before `RUN-SHEET-306` came back and REWRITTEN when it did, on the same
> day and before any commit. It never pointed a session at worn work — which is the trap `306`
> filed twice — and the draft's only content that mattered, its reading order, survives below.**

Read `repo\docs\00-STATE.md` — the **currency line at the top** (it is `307`, and it is the whole
handover), then **§3 OWNER ACTION OUTSTANDING — the top THREE entries are new**, then **§4
RETRACTED — TWO new, and the first is a staging instruction three sheets carried**, then **§6
TRAPS — THREE new.** Then
**`307-THE-CENSUS-GATE-PASSED-AND-THE-PREDICTION-IS-SEVEN-EYE-WIDTHS` §0**, which is one table and
is the state of play, **and §1, which is the whole result.** Then **`RUN-SHEET-307` §1 and §2.**
Then **`PRIORITY-BOARD-307`** — **the current board; `306`'s and `299`'s are superseded, and the
number is re-stamped by every session that changes it** — where **GROUP `V` is the route to a
headset, `V1`/`V2` are done and `V3` has half-run.**

Same rules as always. **You work OFFLINE. The build, every run and every commit are the owner's,
on the main PC. Supply complete copy-paste PowerShell blocks; quote a run-sheet block verbatim,
never paraphrase it. Never stage, commit, branch, merge or tag.** `git log`, `git show` and
`git diff <path>` are bridge-safe; `git status` needs `--no-optional-locks` **and a path list**;
`--ignore-cr-at-eol` is a `git diff` option only. **►►►► AND A PLACEHOLDER IS NOT A COMMAND:
`--predicted-frac <the number from the log>` cost the owner a block, because `<` is a RESERVED
OPERATOR in PowerShell** — *"The '<' operator is reserved for future use."* **Derive the value in
the block, or mark the substitution and say out loud that it must be made first.** `00-STATE` §7a,
`296` §11.

---

## ►►►► WHERE THINGS ACTUALLY STAND ◄◄◄◄

**`RUN-SHEET-306` IS WORN IN FULL — §1, §2, §3, §4, §5 and §6 all run on the main PC, 2026-09-04.**
Binary unchanged: `45756E5A…3F92`, 18,070,774 bytes. **AND §7 IS WORN TOO: `22e6b0a`
(`GoldenEyeVR`) and `99d8a63` (`goldeneye-native`, the three-tool ASCII fix that made the sweep
run) are IN, both trees clean.** `RUN-SHEET-307` §5 commits only `307`'s own documents.
**`[MEASURED]` from `git log` before that sentence was written — the rule `306` filed twice, kept
by the session that filed it.**

### 1. `H7`'s PYTHON LEG IS CLOSED AND `305` IS QUOTABLE FORWARD.

`order_sweep_306_repro.txt`: **`admission=52  equal=32  permuted=4  refused=168`** over 256 dumps,
**zero tracebacks**, same four permutations at the same `span [29..36]`, and `dlgrab_C1_4676` still
the only one among the fourteen `C1`+`V1` dumps. `P1`'s nine read `equal=9`.

### 2. ►►►►►►►► GATE 6.1 PASSED, AND IT HAD NEVER PASSED BEFORE.

`dlgrab_S3_5400`: `viewport loads=2`, **`only in eye0 = 0`**, `MODEL_MTX 81/81`, `MODEL_VTX 49/49`,
`MODEL_COL1 73/73`, no `DIVERGES` on any of the three, `eyes-rebuilt=1 chr=2 obj=2 skipped=0`.
**Six sessions of *"a disparity measured on an eye with no world in it is a number about nothing"*
are over — that sentence is now measured FALSE on a real frame at `GETV_STEREO_OFFSET=500`.**

### 3. ►►►►►►►► AND THE DISPARITY IS UNMEASURABLE WHERE IT WAS TAKEN: THE PREDICTION IS 7.7 EYE-WIDTHS.

The log's own line at frame 5400: **`PREDICTION: disparity = -7.696404 x eye_width (= -7024.25
px)`** — on an eye half **912 px** wide. **All seven grabs are out of band** (−1500, −1500, −1694,
−7024, −7023, −6498, −6202 px). **Disparity goes as 1/D, so `separation=500` (chosen *"deliberately
absurd"*, `255` §4) against `RUN-SHEET-299` §4's *"stand still, facing a wall"* (`D≈47`) is a
product neither document considered.** **The measurable window existed and passed 600 frames before
the first grab: frames 1380–1800, `D` 644–1933, predicted −172 to −517 px.**

**THE INSTRUMENT PRINTED THE NUMBER THAT VOIDS ITS OWN MEASUREMENT, ON ALL 109 WINDOWS, AND NOBODY
HAD EVER READ THAT LINE AS A GATE.** `RUN-SHEET-307` §2.0 is that gate and it costs one
`Select-String`.

### 4. THE POLYGON DID NOT APPEAR IN EITHER `P1` OR `P2`.

**`P1` (fix ON): nine gameplay frames, ALL CLEAN**, worst blob 15 px. **`P2` (fix OFF): four frames
with a WHOLE DEAD EYE** — `MODEL_MTX 38/0`, `only in eye0 = 18`, strict subset — **and five refused
by the tool's own `|dx| >= 8` guard.** So **`304` §2a cannot date the polygon**, eighteen gameplay
grabs carry none of it, and the three `C1`/`V1` frames remain the only instances. **What the arms
DID measure is `303` §2's fix working in GAMEPLAY and not only in the opening, which is a stronger
statement than GROUP `B`'s closure and was free.**

---

## ►►►►►►►► THE FIRST ACTION: `RUN-SHEET-307` §1. IT IS OFFLINE AND IT IS A FALSIFIER. ◄◄◄◄◄◄◄◄

**`stereo_disparity.py` on `dlgrab_S3_5400.bmp` MUST PEG AND THE `H1` ALARM MUST FIRE.** `H1` was
opened because that alarm had never fired; `301` §2 rebuilt `measure()` so it can; `306` §1 made its
line printable after finding it was one of three that could not print at all. **This is the first
real frame in this project's history where the alarm is REQUIRED to fire, and if it stays silent
`H1` is not closed.** The block derives `--predicted-frac` from the log itself.

Then **§2 — `S3b` (separation 32 at the near wall, predicted ≈ −450 px) and `S3c` (separation 500
down a long sightline, predicted ≈ −170 to −500 px).** **Both arms land in band by construction,
and if both pass ±5 px the 1/D law is MEASURED IN PIXELS rather than printed — across a 16x
separation change and a 40x depth change. No arm has ever done that.**

---

## ►►►► THE THINGS THAT NEED A PERSON ◄◄◄◄

- **`RUN-SHEET-307` §2a/§2b — two runs, and the staging instruction has CHANGED.** For `S3c`:
  **do NOT walk up to a wall. Stand still looking down the LONGEST line in the room and press F9
  four or five times, then move and repeat.** The amplitude gate picks the scorable grab afterwards
  so nothing has to be judged live.
- **`RUN-SHEET-307` §4 — the FC3/FC4 sentence. Third sheet of asking.** One sentence about each
  arm, in your own words. **If they looked the same again, `RUN-SHEET-303` §0.1 is a `279` §7 null
  for the SECOND time and CLOSES.**

---

## ►►►► THE THING THIS SESSION SHOULD BE MOST CAREFUL ABOUT ◄◄◄◄

**TWO GATES WERE WRONG THIS TIME AND NEITHER WAS WRONG ABOUT THE GAME.**

**`ZERO-REBUILD FRAMES` READ 2,220 OF 7,636 AND EVERY ONE IS BENIGN.** `[MEASURED]`: contiguous,
frames 1810–4029, **every one `zsnap=0`** — an empty on-screen prop list, because the owner was
standing still facing a wall — with `eyes-rebuilt=1` and `skipped=0` throughout. **The gate's own
words are *"it must be 0"*, `pass-never-ran` is 0, and the arm is healthy.** The counter cannot tell
*"the second eye got nothing"* from *"there was nothing to give it"*. **`H17`, and it is a
DIAGNOSIS: the shape is a split, `zero-rebuild(zsnap>0)` beside `zero-rebuild(zsnap==0)`, the way
`N1` split the near line. `301` §0 — the count of wrong filed fixes is five.**

**AND CONCENTRATION DOES NOT SEPARATE THE TWO FAULTS.** `P2_1369` reads **`blobs 1`, largest
576,312 of 576,312 — 100%**, which is the POLYGON's signature by `304` §1.4's statistic, and its
bbox is the **entire unmasked eye**. **`304` §1.4's 5%/8% dead-eye figures were measured on two
OPENING frames and do not generalise; a fully dead eye is one solid blob.** **MAGNITUDE is what
separates them** — tens of thousands of pixels against half a million. `304` §1.3's rule, applied
to its own successor.

**`169` NEXT ID = `U-26`.**
