Read `repo\docs\00-STATE.md` — the **currency line at the top** (it carries `308`'s full result and
`307`'s, because `307` never updated its own and that is filed in §4), then **§3 OWNER ACTION
OUTSTANDING — the top TWO entries**, then **§4 RETRACTED — THREE new** (the stale currency line,
`RUN-SHEET-308` §1.2's non-existent block, and the `0.123`/`0.122` slip), then **§6 TRAPS — TWO
new** (the PowerShell round-trip, and an improvised block that was never filed). Then
**`RUN-SHEET-308` §0** (one table) **and §2, which is the whole job.** Then
**`PRIORITY-BOARD-308`** — the current board (`307`'s is superseded and bannered); `H1` and `H18`
are CLOSED, **`H19` is NEW**, `V3` is still open and still the spine.

Same rules as always. **You work OFFLINE. The build, every run and every commit are the owner's, on
the main PC. Supply complete copy-paste PowerShell blocks; quote a run-sheet block verbatim, never
paraphrase it. Never stage, commit, branch, merge or tag.** `git log`, `git show` and
`git diff <path>` are bridge-safe; `git status` needs `--no-optional-locks` **and a path list**.
**►►►► A PLACEHOLDER IS NOT A COMMAND: `<` is a RESERVED OPERATOR in PowerShell** (`00-STATE` §7a,
`307` §0) — derive the value in the block, or mark the substitution and say so out loud.
**►►►► INSTRUMENT OUTPUT IS ASCII (`H16`): the docs may carry arrows, the tools may not.**
**►►►► AND A NEW ONE, `308` §1.1: DO NOT EDIT A TRACKED SOURCE FILE WITH
`Get-Content`/`-replace`/`Set-Content`.** `stereo_disparity.py` is LF-only UTF-8 with non-ASCII in
ten COMMENT lines; the round-trip rewrites 293 line endings and mangles all ten. **Hand the splice
to `py` and do it in BYTES** — `RUN-SHEET-308` §5.2 / `308` §5.2 is the shape, and it refuses
unless the anchor matches exactly once.
**►►►► A HOLE'S FILED FIX IS A DIAGNOSIS, NOT A PATCH — the count of wrong filed fixes is five
(`301` §0). MEASURE BEFORE YOU PATCH.**

---

## ►►►► THE FIRST COMMAND, AND IT IS NOT OPTIONAL ◄◄◄◄

**`308` SUPPLIED TWO COMMIT BLOCKS AND THE SESSION ENDED WITHOUT SEEING THEM RUN.** Whether
`b929c9b`-style commits exist for `308` is a claim about git, and **`306` §0 is the standing rule:
a claim that work is owed is a claim about the filesystem AND about git, and both are one command
away.** Three sessions in a row have opened with a sentence that was already false.

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
git log --oneline -3
git --no-optional-locks status --porcelain -- getv/tools
Set-Location F:\Projects\GEVR\GoldenEyeVR
git log --oneline -3
git --no-optional-locks status --porcelain -- repo/docs
```

**If `308`'s two commits are IN and both dirty sets are empty, say so and go to §2a.** If they are
not, the blocks are in `308` §7 and in the chat that produced this file; **the message files
`COMMIT-MESSAGE-2026-09-04c.txt` and `COMMIT-MESSAGE-2026-09-04c-native.txt` are written and
correct.** **Do NOT use `COMMIT-NOW.cmd`** — it stages the whole dirty tree and picks the newest
message file, which is how `307` swept 16 strays (`307` §5). Explicit `git add --` path lists and
`git commit -F`.

---

## ►►►► WHERE THINGS ACTUALLY STAND ◄◄◄◄

**`RUN-SHEET-308` §1 IS WORN IN FULL AND `H1` + `H18` CLOSE TOGETHER.** `stereo_disparity.py` now
prints `confidence  contrast <f>` and refuses any `dx` where
`contrast = (mad_zero - mad_best) / mad_zero < 0.20`, beside the existing absolute `mz - mb < 0.5`
(which stays, so the `B1` identical-halves case is still named separately). **`[MEASURED]` under
`py` on the main PC, the pre-registered falsifier on all 16 `307` grabs: `GATE dx: ALL 16
IDENTICAL` · `LOW CONFIDENCE refusals: 4` — `S3c_1620`, `S3c_5406`, `S3c_5462`, `S3c_7678`, all
four `S3c` and nothing else · `scored grabs: 12` · frame `5400` still `contrast 0.286`,
`|-16 - -11.04| = 4.96 px`, `VERDICT PASS` · `--selftest A/B/C PASS` byte-identical.** The floor
did not rescue a void frame and did not kill a real one, which is `301` §0's condition for filing.

**`H1` DID NOT CLOSE BY ITS PEG ALARM.** An out-of-band prediction is NECESSARY and NOT SUFFICIENT
— an interior spurious peak pre-empts the peg. The contrast floor is what catches that.

### ►►►►►►►► AND `V3` DID NOT MOVE. READ THIS BEFORE READING THE PASS. ◄◄◄◄◄◄◄◄

**AN HONEST INSTRUMENT IS NOT A PASS.** Eleven of twelve `S3b` grabs still miss ±5 px and the error
still grows with disparity magnitude — **~5 px at −11 px predicted, ~52 px at −406 px**, roughly
10-13% proportional. **AND THE ONE FRAME THAT PASSES IS THE WEAKEST EVIDENCE ON THE BOARD: `5400`
predicts −11.04 px, the SMALLEST of the twelve, and carries the LOWEST contrast of the twelve
(0.286 — nearest the new floor).** A pixel gate met at near-zero disparity says almost nothing about
a 1/D law. **Do not let `V3` be read as "one frame passes".** `258` STAGE 6 does not close.

---

## ►►►►►►►► THE JOB: `RUN-SHEET-308` §2a. OFFLINE, NO RUN, THE CORPUS IS ON DISK. ◄◄◄◄◄◄◄◄

**`H19` is the hole and `RUN-SHEET-308` §2a is the step.** The prediction uses the **centre-ray
depth** `D` (the engine's ray test at screen centre); the correlator averages a patch of the central
quarter — `stereo_disparity.py:86`, `xs = [half//4 .. 3*half//4]`. **Candidate diagnosis: the
matched texture sits at a depth different from the centre ray, so measured and predicted are two
different depths' disparities.**

**THE STEP:** add a `--patch FRAC` option (default the current 0.25-0.75 window) narrowing `xs` to a
band around the crosshair column, then re-score the strong `S3b` grabs at several widths.
**GATE 2a, stated before it runs:** if the proportional error **falls toward ±5 px as the patch
tightens**, the under-read is patch-averaging over depth and the fix is to correlate where the ray
test was taken. **If it does NOT move**, the under-read is elsewhere — projection scale, or the
log's own `D` — **and that is a real result that outranks everything else on the board**, and §2b
is required.

**IT IS AN INSTRUMENT CHANGE, SO IT IS A DIAGNOSIS AND NOT A PATCH** (`301` §0, count five), **and
it needs its own falsifier before anything is filed** — the shape that worked in §1: pre-register
what the numbers must do, run it on the frames you already understand INCLUDING the ones it should
be boring on (`279` §7), and re-score the whole 16 with `RUN-SHEET-308` §1.3/§1.4 so nothing else
moved. **`--patch` at its default must leave all 16 `dx` byte-identical, or the option is wired
wrong.** That is the cheapest first gate and it costs one re-run.

---

## ►►►► THE THINGS THAT NEED A PERSON ◄◄◄◄

- **Nothing, unless §2a is inconclusive** — then `RUN-SHEET-308` §2b is one short run: stand
  point-blank facing a FLAT textured wall that fills the whole view (no floor, no ceiling, no long
  line), `GETV_STEREO_OFFSET=32`, F9 four or five times.
- **`E3` (FC3/FC4) is CLOSED.** Do not re-ask.
- **And if `V3` ever closes, `V4` (`S4`, the mode-2 falsifier) runs in the SAME sitting** — a pass
  with no negative arm is a claim, not a result (`49`, board `V4`).

---

## ►►►► THE THING THIS SESSION SHOULD BE MOST CAREFUL ABOUT ◄◄◄◄

**`308` CLOSED TWO HOLES AND MOVED THE PROJECT ZERO DISTANCE TOWARD A HEADSET, AND THAT IS THE
HONEST READING.** The instrument is now trustworthy; the measurement it was built to take still
fails. **The temptation §2a creates is to tighten `--patch` until a number lands in band and file
that as `V3` closing.** A patch width chosen because it produces the answer you wanted is `304`
§1.3's rule with a new face — **a calibration on the frames you already understand is a hypothesis**
— and it would be the sixth wrong filed fix. **Pre-register the width and the gate before the
re-score, and if the error does not move, say so and take §2b.**

**`169` NEXT ID = `U-26`.**
