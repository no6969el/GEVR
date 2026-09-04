Read `repo\docs\00-STATE.md` — the **currency line at the top** (it now carries `307`'s full result
and points forward to `308`), then **§3 OWNER ACTION OUTSTANDING — the top TWO entries are new**
(the `RUN-SHEET-308` §1 next-action, and the `E3` closure), then **§4 RETRACTED — THREE new** (the
`H1` peg-alarm prediction, the polygon-concentration metric, and `S3c`'s "in band means
measurable"), then **§6 TRAPS**. Then **`RUN-SHEET-308` §0** (one table — the state of play) **and
§1, which is the whole first job.** Then **`PRIORITY-BOARD-307`** — still the current board (`307`
did not supersede it; `V1`/`V2` done, `V3` half-answered and open, `E3` CLOSED, `H1` RE-OPENED,
`H17`/`H18` open).

Same rules as always. **You work OFFLINE. The build, every run and every commit are the owner's, on
the main PC. Supply complete copy-paste PowerShell blocks; quote a run-sheet block verbatim, never
paraphrase it. Never stage, commit, branch, merge or tag.** `git log`, `git show` and
`git diff <path>` are bridge-safe; `git status` needs `--no-optional-locks` **and a path list**.
**►►►► A PLACEHOLDER IS NOT A COMMAND: `<` is a RESERVED OPERATOR in PowerShell** (`00-STATE` §7a,
`307` §0) — derive the value in the block, or mark the substitution and say so out loud.
**►►►► INSTRUMENT OUTPUT IS ASCII (`H16`): the docs may carry arrows, the tools may not.**
**►►►► A HOLE'S FILED FIX IS A DIAGNOSIS, NOT A PATCH — the count of wrong filed fixes is five
(`301` §0). MEASURE BEFORE YOU PATCH.**

---

## ►►►► WHERE THINGS ACTUALLY STAND ◄◄◄◄

**`RUN-SHEET-307` IS WORN IN FULL.** §1 fired the `H1` falsifier and it fired against us: on
`dlgrab_S3_5400` (predicted −7,019 px) **the peg alarm STAYED SILENT on all four searches** and the
correlator returned an interior spurious peak (`dx +351/+172 px`, WRONG sign, moving with
`--search`). **An out-of-band prediction does NOT force a peg — a textured frame gives the correlator
an interior escape hatch. `H1` IS RE-OPENED.**

**§2 SCORED ALL 16 `S3b`/`S3c` GRABS OFFLINE, AND THE VENUE RE-AIM WORKED — EVERY GRAB IN BAND.**

### 1. GATE 6.1 PASSES ON ALL 16 FRAMES, BOTH ARMS. THE CENSUS ERA IS CLOSED.

`only in eye0 = 0`, `only in eye1 = 0`, every `MODEL_*` equal in both eyes, on every grab. **Whatever
`S3c` is, it is NOT a dead eye.**

### 2. `S3b` IS REAL STEREO, JUST NOT ±5 px-PRECISE.

All 12 grabs sign-correct, magnitudes tracking the 1/D prediction, STRONG correlation (`mad_best`
well below `mad_zero`). **Only frame `5400` lands within ±5 px** — the error grows with disparity
magnitude (~5 px at −11 px, ~52 px at −406 px), an instrument-precision ceiling. **`RUN-SHEET-308`
§2 is that thread.**

### 3. `S3c` IS VOID, NOT A FAILURE — AND IT HANDS US THE `H1`/`H18` FIX.

All four `S3c` grabs read WRONG SIGN with `mad_best`≈`mad_zero` (15/17, 28/29): NO real correlation,
because a long sightline at sep 500 has no single global disparity. **The disparity tool already
refuses on an ABSOLUTE floor (`mz-mb<0.5`) that `S3c` clears; the fix is a RELATIVE `contrast`
floor**, and `307` §2 pins it: `S3b` real ≥ 0.286, `S3c` void ≤ 0.123, so 0.20 separates them with
margin. **`V3`/`258` STAGE 6 DOES NOT CLOSE: the 1/D law is DIRECTIONALLY confirmed, not confirmed
to ±5 px.**

---

## ►►►►►►►► THE FIRST ACTION: `RUN-SHEET-308` §1. OFFLINE, AND ITS FALSIFIER IS ON DISK. ◄◄◄◄◄◄◄◄

**§1.0 reproduces the `contrast` split from the numbers already in `disp_307_S3_all.txt` — measure
before you patch.** Then **§1.1 is the one edit** to `stereo_disparity.py` (a relative floor, ASCII,
changes no `dx`), and **§1.2 re-scores the 16 grabs as the pre-registered falsifier: all four `S3c`
must read CANNOT ANSWER and all twelve `S3b` must still score with unchanged `dx`, or the threshold
is wrong and is NOT filed.** If it passes, **`H1` and `H18` close together.**

Then **§2 — the ±5 px precision `V3` needs.** `2a` is offline (tighten the correlation patch toward
the crosshair, re-score the strong `S3b` grabs); `2b` is one flat-wall single-depth run **only if
`2a` is inconclusive** — the sheet's only person-cost step.

---

## ►►►► THE THINGS THAT NEED A PERSON ◄◄◄◄

- **Nothing, unless `RUN-SHEET-308` §2a is inconclusive** — then §2b is one short run: stand
  point-blank facing a FLAT textured wall that fills the whole view, sep 32, F9 four or five times.
- **`E3` (FC3/FC4) is CLOSED** (`[REPORTED]` 2026-09-04: they looked the same). Do not re-ask.

---

## ►►►► THE THING THIS SESSION SHOULD BE MOST CAREFUL ABOUT ◄◄◄◄

**THE CONFIDENCE THRESHOLD IS A CALIBRATION ON THE FRAMES YOU ALREADY UNDERSTAND (`304` §1.3), SO
IT IS A HYPOTHESIS UNTIL §1.2's FALSIFIER RUNS.** 0.20 is pre-registered from exactly two arms; the
gate is the 16 grabs separating cleanly, not the number looking reasonable. **And it is a DIAGNOSIS,
not a patch (`301` §0): it must not silently rescue an `S3c` frame or silently kill an `S3b` one.
If either happens, the floor is wrong — record the miss in `00-STATE` §4 and do not file it.**

**`169` NEXT ID = `U-26`.**
