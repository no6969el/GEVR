Read `repo\docs\00-STATE.md` — the **currency line at the top** (it carries `309`'s full result;
`[MEASURED]`, and it was written from the repo and from `309`'s own pasted output, not from
memory), then **§4 RETRACTED — TWO new** (the `10-13%` figure, and `309`'s own pre-registered
`git diff --stat`), then **§6 TRAPS**. Then
**`309-THE-UNDER-READ-IS-THIRTY-PERCENT-NOT-THIRTEEN` §0, §5.1, §6.2 and §7** — §0 is one table,
§5.1 is the ladder's per-grab result, §6.2 is the live candidate, §7 is what was worn. Then
**`PRIORITY-BOARD-309`** — the current board (`308`'s is superseded and bannered); **`H20` is new
and it is §E item 0.**

Same rules as always. **You work OFFLINE. The build, every run and every commit are the owner's, on
the main PC. Supply complete copy-paste PowerShell blocks; quote a run-sheet block verbatim, never
paraphrase it. Never stage, commit, branch, merge or tag.** `git log`, `git show` and
`git diff <path>` are bridge-safe; `git status` needs `--no-optional-locks` **and a path list**.
**►►►► A PLACEHOLDER IS NOT A COMMAND: `<` is a RESERVED OPERATOR in PowerShell** (`00-STATE` §7a).
**►►►► INSTRUMENT OUTPUT IS ASCII (`H16`): the docs may carry arrows, the tools may not.**
**►►►► DO NOT EDIT A TRACKED SOURCE FILE WITH `Get-Content`/`-replace`/`Set-Content`** (`308` §1.1,
`00-STATE` §6). Hand the splice to `py` and do it in BYTES; `309`'s `_patch309.py` is the shape
with more than one anchor — every anchor must match exactly once or NOTHING is written.
**►►►► A HOLE'S FILED FIX IS A DIAGNOSIS, NOT A PATCH — the count of wrong filed fixes is five
(`301` §0). MEASURE BEFORE YOU PATCH.** `309` is the case FOR that rule: **its first act was to
re-derive the baseline from the file on disk, and the figure every document had been repeating for
two sessions turned out to be wrong.**

---

## ►►►► THE FIRST COMMAND, AND IT IS NOT OPTIONAL ◄◄◄◄

**`309` SUPPLIED A COMMIT BLOCK AND THE SESSION ENDED WITHOUT SEEING IT RUN.** Whether the docs
and the `--patch` edit are in is a claim about git, and `306` §0 is the standing rule.

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
git log --oneline -3
git --no-optional-locks status --porcelain -- getv/tools
Set-Location F:\Projects\GEVR\GoldenEyeVR
git log --oneline -3
git --no-optional-locks status --porcelain -- repo/docs
```

**`309` ENDED WITH ITS COMMIT BLOCK SUPPLIED AND UNRUN, SO THE HONEST EXPECTATION IS A DIRTY
TREE, NOT A CLEAN ONE.** Either state is fine; **which one it is, is the first thing this session
knows for a fact rather than assumes.**

- **If the trees are DIRTY:** `getv/tools/stereo_disparity.py` is modified (the `--patch` option)
  and `repo/docs` carries `00-STATE.md` modified plus `309`'s doc, `PRIORITY-BOARD-309`,
  `00-STATE.md.bak-309` and this file untracked. **The commit block is in
  `309-THE-UNDER-READ-IS-THIRTY-PERCENT-NOT-THIRTEEN` §8 and the two message files
  (`COMMIT-MESSAGE-2026-09-04d.txt`, `-native.txt`) are written and correct.** Offer it; the commit
  is the owner's.
- **If the trees are CLEAN:** the commit ran. Say the two HEADs out loud and move on.

Two scratch files, **`getv/tools/_patch309.py` and `getv/tools/ladder_driver.py`, are NOT part of
any commit** — `ladder_driver.py` is worth keeping if the ladder will be re-run, but say so
deliberately rather than letting a stage sweep it (`307` §5, 16 strays).
**`repo\docs\_to_delete\` holds two files an assistant misfiled and could not delete over the
bridge; delete that folder and keep it out of every commit.**

---

## ►►►► WHERE THINGS ACTUALLY STAND ◄◄◄◄

**`RUN-SHEET-308` §2a IS WORN AND ITS DIAGNOSIS IS FALSIFIED.** `stereo_disparity.py` takes
`--patch FRAC`; the ladder `1.00 / 0.50 / 0.25 / 0.10` ran all sixteen grabs at every rung under
`py`. **Mid-band median `measured/predicted`: `0.692`, `0.696`, `0.696`, `0.697`. A fifteen-fold
narrowing of the correlation band moves it by `0.005`. PATCH AVERAGING OVER DEPTH IS NOT THE
`S3b` UNDER-READ.** GATE 2a-i passed first: at `FRAC 1.00` all sixteen `dx` and `contrast` are
identical to `308`'s, four `S3c` refusals and nothing else, `--selftest A/B/C PASS` byte-identical.

**THE UNDER-READ IS A NEAR-CONSTANT RATIO, AND THE OLD NUMBER WAS WRONG.** Median proportional
error is **`30.76%`**, not `10-13%` (that was the corpus's two endpoints; `00-STATE` §4 retracts
it). The ratio is `0.652`-`0.799` over ten mid-band grabs. **The absolute error grows because the
ratio is constant — that is arithmetic, not a second finding.**

**AND THE LADDER ATE BOTH OUTLIERS.** `S3b_10177` goes `-458 -> -302` (`1.129 -> 0.750`) and
`S3b_5400` goes `-16 -> -7` (`1.449 -> 0.634`); at `FRAC 0.25` **all twelve grabs lie in
`0.634`-`0.814`**. The wide patch was not averaging depth on those two — it was matching something
outside the crosshair's neighbourhood.

### ►►►►►►►► `V3` DID NOT MOVE, AND ITS ONE PASS IS NOW KNOWN TO BE UNFALSIFIABLE ◄◄◄◄◄◄◄◄

**`S3b_5400` reads `-16`, `-10`, `-7`, `-7` across the four rungs and PASSES ±5 px at every one**,
because its prediction is `-11.04` px and any small number is within 5 px of it. **A GATE THAT
CANNOT BE FAILED IS NOT A GATE. `V3` / `258` STAGE 6 DOES NOT CLOSE AND MUST NEVER CLOSE ON THAT
FRAME.** Three sessions have now failed to move it.

---

## ►►►►►►►► THE FIRST JOB: `H20`. OFFLINE, NO RUN, NO BUILD. **EFFORT: `LOW`.** ◄◄◄◄◄◄◄◄

> **EFFORT IS THE OWNER'S TIME, NOT THE ASSISTANT'S** (`PRIORITY-BOARD-309` preamble).
> **`LOW`** = offline only, or one short run with no build and no new analysis — minutes.
> **`MEDIUM`** = a build, or a run plus real analysis — one sitting.
> **`HIGH`** = a design decision or work whose scope is not bounded, **and it must not be started
> at the end of a session.**
>
> **THIS SESSION'S RECOMMENDED SHAPE, IN ORDER:**
>
> | | job | effort | costs the owner |
> |---|---|---|---|
> | **1** | **`H20` — read the eye loop's projection, compare against the logged tangents** | **`LOW`** | **nothing.** A source read on the bridge; the assistant does it and reports |
> | **2** | file the answer (either way) and update `H20` on the board | **`LOW`** | one commit block |
> | **3** | **`RUN-SHEET-308` §2b — the flat-wall grab**, only if `H20` does not settle it | **`LOW`** | **one short run, ~5 minutes, no build.** Stand at a wall, `sep 32`, F9 x4-5 |
> | **4** | score §2b's grabs and read the correlator's error bar | **`LOW`** | one paste |
>
> **TOTAL: a `LOW` session that can close or kill `H20` and finally put an error bar on the
> instrument.** **DO NOT START GROUP `C` / `V7` (the per-eye contents instrument) IN THIS SESSION —
> it is `HIGH` and it is `PRIORITY-BOARD-309` §E item 9.** If `H20` turns out to need a BUILD to
> answer (it should not — it is a source read), that promotes it to `MEDIUM` and it is worth
> saying so before starting rather than discovering it half way.

**TWO CANDIDATES WERE ALREADY KILLED BY READING RATHER THAN RUNNING, AND BOTH COST ONE COMMAND:**
the log's implied eye width is `910.34`-`913.45` px over 898 lines and `stereo.c` fixes it at
`912.67`, so the tool's `half = 912` **agrees** — the pixel conversion is not the error; and
`frac * D` reads `-23.3760`-`-23.3840` over 687 prediction lines, so **the log's own 1/D law is
exact to four figures. WHATEVER IS WRONG IS A CONSTANT.**

**`H20` IS WHERE THAT CONSTANT MOST PLAUSIBLY LIVES.** `run_307_S3b_sep32.log` reports eye viewport
**`160x180`** n64 units (full width `320`), tangents **`L/R = -/+0.684267`**, **`D/U = -/+0.577350`**,
`tanw = 1.368534`, and `geStereoPredict()` (`vendor/ge-decomp/src/game/stereo.c:512`) computes
`frac = -sep / (D * tanw)`. **`0.577350 * (160/180) * (4/3) = 0.684267` EXACTLY: the horizontal
tangent is the vertical times the eye's aspect times an extra `4/3`.**

**THE STEP: read the eye loop's OWN projection — the matrices the renderer actually builds for each
eye — and compare its horizontal frustum against the tangents the prediction logs.** If they
DIFFER, the prediction has been wrong by that ratio all along and `V3` has been grading the game
against a bad number. If they AGREE, the candidate dies like the eye-width one and the constant is
somewhere else. **Either answer is worth more than another run.**

**►►►► AND IT DOES NOT CLOSE ON ARITHMETIC ALONE.** A dropped or added 4:3 predicts `0.750` or
`0.667`; **the measurement is `0.692`-`0.697` and is bracketed by both, ~4% from each.** The corpus
spread is `0.634`-`0.814`, so 4% is inside the noise. **Telling `0.667` from `0.750` needs the
correlator's own error bar, which nothing on disk measures — that is `RUN-SHEET-308` §2b.**

---

## ►►►► THE THINGS THAT NEED A PERSON ◄◄◄◄

- **`RUN-SHEET-308` §2b — `LOW`, about five minutes, no build. And it is now MORE necessary,
  not less.** Stand point-blank facing a FLAT,
  TEXTURED wall that fills the entire view (no floor, no ceiling, no long sightline),
  `GETV_STEREO_OFFSET=32`, F9 four or five times. **One depth across the whole eye is the only
  configuration on which the correlator's own error can be measured.** Do `H20` first — it may
  change what the run is for.
- **The commit**, this session's own paths only, explicit `git add --` path lists,
  `git commit -F`. **Do NOT use `COMMIT-NOW.cmd`** (`307` §5).
- **`E3` (FC3/FC4) is CLOSED.** Do not re-ask.

---

## ►►►► THE THING THIS SESSION SHOULD BE MOST CAREFUL ABOUT ◄◄◄◄

**`309` KILLED A DIAGNOSIS, TWO CANDIDATES AND ONE PUBLISHED FIGURE, AND MOVED `V3` ZERO DISTANCE.
THAT IS THE HONEST READING, AND IT IS THE SECOND SESSION IN A ROW WITH THAT SHAPE.** The
instrument is now honest AND better characterised; the measurement it exists to take still fails.

**THE TEMPTATION `H20` CREATES IS THE SIXTH WRONG FILED FIX.** A 4:3 factor is exactly the kind of
term that can be "corrected" until a number lands in band — and `309` measured that the two
candidate corrections **bracket** the data rather than matching it. **Read the renderer's
projection before touching the prediction, state what the corrected ratio WOULD be before you
apply anything, and if the answer still sits between `0.667` and `0.750`, say so and take §2b.**

**AND ONE PROCESS DEFECT FROM `309` ITSELF, §7.1: A PRE-REGISTERED GATE VALUE WAS AN ASSISTANT'S
HEAD ARITHMETIC PRESENTED IN A TABLE OF MEASURED ONES** (`git diff --stat` registered `25 / 5`,
landed `29 / 8`). The edit was still provably correct — the patched file is byte-identical
(`md5 316cb9c317f225a3d16482733ee20c79`) to the copy the whole ladder was dry-run against — **but a
gate list that mixes measured values with guessed ones teaches the reader to shrug at a miss.
LABEL A PREDICTION AS A PREDICTION.**

**`169` NEXT ID = `U-26`.**
