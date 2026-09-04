# `308` — THE CONFIDENCE GATE, MEASURED BEFORE IT IS PATCHED. **AND `RUN-SHEET-308` §1.2 CITES A BLOCK THAT DOES NOT EXIST**

**OFFLINE, 2026-09-04. NOTHING BUILT, RUN IN-GAME, STAGED OR COMMITTED BY THIS SESSION.**
Binary untouched. Both trees clean on every path this sheet names, `[MEASURED]` from
`git --no-optional-locks status` with a path list: `GoldenEyeVR` HEAD `bed52d7`,
`goldeneye-native` HEAD `99d8a63`, and `getv/tools/stereo_disparity.py` last touched by `99d8a63`
(`306`'s ASCII fix).

> **THE BRIDGE CAVEAT, FIRST, BECAUSE IT IS `H7`.** Everything in §1.0 and §1.3 below was measured
> on the **BRIDGE's `python3 3.10.12`**, not on the main PC's `py`. `306` §1 is why that distinction
> exists at all — the two Pythons did not disagree about arithmetic, they disagreed about ENCODING,
> and the disagreement was fatal. **These numbers are `[MEASURED, BRIDGE]` and are NOT quotable
> forward until §1.0 and §1.2 are re-worn under `py` on the main PC.** They are here because a
> pre-registered falsifier that has already been dry-run costs the owner one paste instead of three.

---

## §0 — WHAT THIS SESSION HAS ESTABLISHED SO FAR, IN ONE TABLE

| | |
|---|---|
| **1** | **GATE 1.0 REPRODUCES.** `S3b` minimum `contrast` **0.286** (frame `5400`), `S3c` maximum **0.122** (frame `1620`). A floor of **0.20** separates them with **0.086 / 0.078** of margin. `[MEASURED, BRIDGE]` from `disp_307_S3_all.txt` |
| **2** | **►►►► AND THE SHEET'S OWN FIGURE IS OFF BY ONE IN THE LAST DIGIT: `RUN-SHEET-308` §1.0 SAYS `S3c` MAX IS `0.123`. IT IS `0.122`** — `(17.366 - 15.239) / 17.366 = 0.12249`. The threshold does not move; **the number is going into the instrument's own printed line, so it is worth being right** |
| **3** | **►►►►►►►► `RUN-SHEET-308` §1.2 SAYS "re-run `307` §2c's scoring block unchanged (it writes `disp_307_S3_all.txt` and `census_307_S3_all.txt`)". THAT BLOCK DOES NOT EXIST.** `RUN-SHEET-307` §2c writes `disp_307_S3b.txt` / `disp_307_S3c.txt` for **ONE grab per arm** and carries `<frame>` / `<frac>` placeholders. **The all-16 block was improvised live in the `307` session and was never written down.** `[MEASURED]`: `grep -rl disp_307_S3_all` over `repo\docs\` returns only `RUN-SHEET-308` and `NEXT-SESSION-PROMPT-308` — the two documents that CITE it. **§1.3 below reconstructs it and proves the reconstruction** |
| **4** | **►►►► AND `00-STATE`'s CURRENCY LINE IS STALE. `NEXT-SESSION-PROMPT-308` OPENS BY SAYING IT "now carries `307`'s full result and points forward to `308`". IT DOES NOT.** `[MEASURED]`: lines 1-45 of `00-STATE.md` contain **no** occurrence of `S3b`, `S3c`, `contrast` or `308`; the block still ends *"READ ... **`RUN-SHEET-307` §1**"*, which is `307`'s STARTING state. §3 `OWNER ACTION` and §4 `RETRACTED` **were** updated. **This is `306` §0's shape for the third time: a prompt's opening sentence was already false when it was written** |
| **5** | **THE EDIT'S TARGET IS VERIFIED BYTE-EXACT.** `stereo_disparity.py:269-276` matches `RUN-SHEET-308` §1.1's "currently" quote exactly, once, in the whole file. The file is **LF-only, UTF-8, no BOM**, and its only non-ASCII bytes are in COMMENTS (ten lines) — **`H16` is about OUTPUT and is not in danger here, but a PowerShell rewrite of the file is** (§1.1) |
| **6** | **►►►►►►►► GATE 1.2b PASSES IN DRY RUN, ALL 16, EXACTLY AS PRE-REGISTERED.** `[MEASURED, BRIDGE]` on a patched COPY in scratch (the tracked file was not touched): all four `S3c` read `CANNOT ANSWER -- LOW CONFIDENCE` (`rc=3`); all twelve `S3b` still score; **all 16 `dx` byte-identical to `307`'s**; frame `5400` still reads `contrast 0.286` and `VERDICT PASS`. `--selftest` still reads `A/B/C PASS` |

| **7** | **►►►►►►►► AND IT IS WORN. EVERY GATE PASSED ON THE MAIN PC UNDER `py`, 2026-09-04 — §6 BELOW. `H1` AND `H18` CLOSE TOGETHER** |

**ITEM 6 WAS A DRY RUN ON THE WRONG PYTHON, ON A COPY, AND IT IS NOT WHAT CLOSED ANYTHING.**
**§6 IS.** The dry run's only value was that the owner pasted five blocks instead of ten.

---

## §1 — THE CONFIDENCE GATE

### 1.0 — THE SPLIT, RE-DERIVED. **`[MEASURED, BRIDGE]`, AND IT REPRODUCES.**

Sorted by `contrast = (mad_zero - mad_best) / mad_zero`:

| grab | dx | predicted | mad_best | mad_zero | contrast | mz-mb | verdict |
|---|---|---|---|---|---|---|---|
| `S3c_5406` | +107 | -385.96 | 28.166 | 29.242 | **0.037** | 1.076 | FAIL (wrong sign) |
| `S3c_5462` | +107 | -385.96 | 28.185 | 29.264 | **0.037** | 1.079 | FAIL (wrong sign) |
| `S3c_7678` | +106 | -385.96 | 27.887 | 29.094 | **0.041** | 1.207 | FAIL (wrong sign) |
| `S3c_1620` | +230 | -172.35 | 15.239 | 17.366 | **0.122** | 2.127 | FAIL (wrong sign) |
| `S3b_5400` | -16 | -11.04 | 7.566 | 10.593 | **0.286** | 3.027 | **PASS** |
| `S3b_12268` | -69 | -105.81 | 4.524 | 7.358 | 0.385 | 2.834 | FAIL |
| `S3b_12654` | -69 | -91.78 | 8.837 | 14.812 | 0.403 | 5.975 | FAIL |
| `S3b_11926` | -70 | -106.35 | 2.366 | 5.540 | 0.573 | 3.174 | FAIL |
| `S3b_9535` | -37 | -53.54 | 4.352 | 11.417 | 0.619 | 7.065 | FAIL |
| `S3b_9440` | -37 | -53.34 | 4.274 | 11.373 | 0.624 | 7.099 | FAIL |
| `S3b_9500` | -37 | -53.54 | 4.305 | 11.438 | 0.624 | 7.133 | FAIL |
| `S3b_12581` | -69 | -91.67 | 4.924 | 13.168 | 0.626 | 8.244 | FAIL |
| `S3b_11990` | -72 | -106.08 | 1.944 | 5.253 | 0.630 | 3.309 | FAIL |
| `S3b_10177` | -458 | -405.60 | 3.602 | 13.380 | 0.731 | 9.778 | FAIL |
| `S3b_9986` | -106 | -132.63 | 2.352 | 12.920 | 0.818 | 10.568 | FAIL |
| `S3b_10069` | -123 | -165.38 | 1.898 | 12.897 | 0.853 | 10.999 | FAIL |

**`S3b` min 0.286 · `S3c` max 0.122 · gap 0.164 · floor 0.20 sits 0.086 under the lowest real
frame and 0.078 over the highest void one.** GATE 1.0 as `RUN-SHEET-308` wrote it: **PASSES.**

**►► ONE THING THE SHEET'S BLOCK CANNOT SEE, AND IT EXPLAINS A LAST-DIGIT DISAGREEMENT.** §1.0's
block re-derives `contrast` from the **printed, 3-decimal** `mad_best` / `mad_zero`. The tool
computes it from the full-precision floats. `[MEASURED, BRIDGE]`: `S3c_7678` re-derives to `0.041`
and the patched tool prints `0.042`. **Differences of ~0.001 against a margin of 0.08 change
nothing — but the two numbers WILL differ in the last digit and that is not a fault.**

### 1.1 — THE EDIT, AND **THE ONE TRAP IN APPLYING IT**

The target is verified: `stereo_disparity.py:269-276`, **exactly once in the file**, byte-identical
to the sheet's quote. **One correction to the sheet's replacement text: `0.123` becomes `0.122`
(§0 item 2).** Otherwise the edit is `RUN-SHEET-308` §1.1's, unchanged.

**►►►► THE TRAP: DO NOT APPLY THIS WITH `Get-Content` / `-replace` / `Set-Content`.**
`stereo_disparity.py` is **LF-only, UTF-8, no BOM**, and carries `►` and `§` in ten comment lines.
A PowerShell round-trip rewrites every line ending to CRLF and re-encodes those bytes under
`cp1252` — **293 spurious line changes and ten mangled comments in the diff, on a file whose whole
point this session is that it prints correctly on the owner's machine.** That is `H16`'s family
one level over: the `306` fix was about what a tool WRITES; this is about what a shell writes to
the tool. **The block below hands the splice to `py` and does it in BYTES, so the encoding and the
line endings cannot move.** It refuses unless the anchor matches exactly once.

### 1.2 — WHAT THE FALSIFIER WILL SAY. **PRE-REGISTERED, AND DRY-RUN ON THE BRIDGE.**

| | pre-registered by `RUN-SHEET-308` §1.2b | `[MEASURED, BRIDGE]` dry run |
|---|---|---|
| four `S3c` read `CANNOT ANSWER -- LOW CONFIDENCE` | required | **4 / 4**, `rc=3`, no `PREDICTED` line printed |
| twelve `S3b` still SCORE | required | **12 / 12** |
| all `dx` unchanged from `307` | required | **16 / 16 identical** |
| `5400` still `contrast 0.286`, still `PASS` | required | **yes**, `|-16 - -11.04| = 4.96 px` |
| `--selftest` text unchanged | GATE 1.2a | **`A/B/C PASS`**, unchanged |

**IF THE OWNER'S `py` DISAGREES WITH ANY ROW OF THAT TABLE, THE FLOOR IS NOT FILED AND THE MISS
GOES IN `00-STATE` §4** — `301` §0, and the count of wrong filed fixes stays at five.

### 1.3 — THE MISSING BLOCK, RECONSTRUCTED AND PROVEN

`disp_307_S3_all.txt` records enough to rebuild the block that made it: a `START` stamp, one
`ARM <name> grabs=N preds=N dls=N` header per arm, then `=== <arm> frame <N>   predicted-frac <F> ===`
before each grab's tool output, then `DONE`. The `predicted-frac` rule is `307` §2c's own — **the
LAST `PREDICTION: disparity =` line at or before that frame's `[getv][dlgrab] frame N ` line.**

**PROOF THAT THE RECONSTRUCTION IS THE ORIGINAL** — `[MEASURED, BRIDGE]`, re-derived from
`run_307_S3b_sep32.log` and `run_307_S3c_longsight.log`:

- **`ARM S3b grabs=12 preds=211 dls=12`** and **`ARM S3c grabs=4 preds=29 dls=4`** — both header
  lines reproduce **exactly**.
- **All 16 `predicted-frac` values reproduce exactly**, to all six decimals.

**It is `§1.3`'s block below, and it writes `disp_308_S3_all.txt` in the same format so the two
files diff directly.**

---

## §2 — THE PLAN. **NUMBERED, AND IT STOPS AT THE FIRST GATE THAT CAN FAIL.**

1. **Re-wear GATE 1.0 under `py`** — `RUN-SHEET-308` §1.0's block, quoted verbatim, unchanged.
   Expect `S3b min 0.286`, `S3c max 0.122`. **If the split does not reproduce, STOP** — the
   threshold is not real and nothing is patched.
2. **Apply the edit** with §1.1's byte-splice block. It refuses unless the anchor matches once, and
   it verifies itself: syntax check, CRLF count, and `git diff --stat` on the one path.
3. **GATE 1.2a — `--selftest`.** Must still read `selftest A/B/C ... PASS`.
4. **GATE 1.2b — re-score all 16** with §1.3's reconstructed block, then the comparison block.
   **PASS = 4 `LOW CONFIDENCE` (all `S3c`), 12 scoring, 16 `dx` identical, `5400` still `PASS`.**
   **If a real `S3b` frame flips, or an `S3c` frame still scores: the floor is wrong, it is NOT
   filed, and the miss goes in `00-STATE` §4.**
5. **If 1.2b passes: `H1` and `H18` close together**, and this doc plus `00-STATE` §3/§4/§6 and
   `PRIORITY-BOARD-308` are written before anything else is started.
6. **Then `RUN-SHEET-308` §2a** — the `--patch FRAC` option and a re-score of the strong `S3b`
   grabs, to find out whether the ~10-13% under-read is patch-averaging over depth. **Offline, no
   run.** It is a NEW instrument option and therefore a diagnosis, not a patch (`301` §0).
7. **§2b — the flat-wall single-depth run — ONLY if §2a is inconclusive.** It is the only
   person-cost step on the sheet and it stays deferred behind step 6.
8. **The commit is the owner's**, two repos (`goldeneye-native` for the tool, `GoldenEyeVR` for the
   docs), path lists only, after the gates are known. `307` §5's `COMMIT-NOW.cmd` stages the whole
   dirty tree and swept 16 strays — **check the dirty set first.**

**THE THREE DOCUMENTATION DEFECTS IN §0 (items 2, 3, 4) ARE FIXED IN THE SAME PASS AS STEP 5**, in
`RUN-SHEET-308` §1.0/§1.1, in a new `RUN-SHEET-308` §1.3, and in `00-STATE`'s currency line.

---

## §3 — WHAT NEEDS A PERSON

- **Nothing in §1.** Every block is offline and the whole corpus is on disk.
- **Nothing in §2a.** It re-scores the same grabs.
- **§2b only, and only if §2a is inconclusive** — stand point-blank facing a FLAT textured wall
  that fills the entire view, `GETV_STEREO_OFFSET=32`, F9 four or five times.
- `E3` (FC3/FC4) is **CLOSED** — do not re-ask.

## §4 — REASONING EFFORT

**MEDIUM for all of `308`.** `SESSION-START` §4: `HIGH` is for long-consequence decisions where
being wrong means REWORK rather than a re-run, and it is explicitly **NOT debugging**. §1 is a
reproduction, a one-place edit that changes no `dx`, and a pre-registered falsifier whose corpus is
already on disk — **its failure mode is caught by its own gate, not by depth of thought.** §2a is
instrument design, which is the project's core loop and `SESSION-START` §4's own example of
`MEDIUM`. **Nothing on this sheet is a `HIGH` item. The next one that will be is GROUP `X` — the
XR layer — and it is blocked behind `V3`.**

**`169` NEXT ID = `U-26`.**

---

## §5 — THE BLOCKS, COMPLETE. **RUN THEM IN ORDER AND STOP AT THE FIRST GATE THAT FAILS.**

**No block below contains a placeholder.** `<` never appears as a command argument (`307` §0).

### 5.1 — GATE 1.0 UNDER `py`. **`RUN-SHEET-308` §1.0, QUOTED VERBATIM.**

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
$rows = @()
$name = $null
Get-Content .\disp_307_S3_all.txt | ForEach-Object {
  if ($_ -match '=== (S3[bc]) frame (\d+)') { $name = "$($Matches[1])_$($Matches[2])" }
  elseif ($_ -match 'mad_best\s+([0-9.]+)\s+mad_zero\s+([0-9.]+)') {
    $mb = [double]$Matches[1]; $mz = [double]$Matches[2]
    $rows += [pscustomobject]@{ grab=$name; mad_best=$mb; mad_zero=$mz; contrast=[math]::Round(($mz-$mb)/$mz,3) }
  }
}
$rows | Sort-Object contrast | Format-Table -AutoSize
"S3b min contrast: " + ($rows | Where-Object grab -like 'S3b*' | Measure-Object contrast -Minimum).Minimum
"S3c max contrast: " + ($rows | Where-Object grab -like 'S3c*' | Measure-Object contrast -Maximum).Maximum
```

**GATE 5.1 — `S3b` min `0.286`, `S3c` max `0.122`.** (`RUN-SHEET-308` §1.0 says `0.123`; it is
`0.122` — §0 item 2. The split is what the gate is, not the last digit.) **If the split does not
reproduce, STOP AND PATCH NOTHING.**

### 5.2 — THE EDIT. **BYTE-SPLICE VIA `py`, SO ENCODING AND LINE ENDINGS CANNOT MOVE.**

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\tools
$patch = @'
import sys
TARGET = sys.argv[1]
OLD = [
'    print("mad_best    %.3f       mad_zero %.3f" % (mb, mz))',
'    if pred_frac is not None and pred_px is None:',
'        pred_px = pred_frac * half',
'    if mz - mb < 0.5:',
'        print("VERDICT: CANNOT ANSWER -- the two halves match no better shifted than "',
'              "unshifted. Either the halves are IDENTICAL (that is `B1`) or the patch has "',
'              "no texture to correlate. Look at the picture before believing any dx.")',
'        return 3',
]
NEW = [
'    print("mad_best    %.3f       mad_zero %.3f" % (mb, mz))',
'    contrast = (mz - mb) / mz if mz > 0 else 0.0',
'    print("confidence  contrast %.3f   (best shift beats zero shift by this fraction; "',
'          ">= 0.20 required to TRUST dx -- 307 s2: S3b real >= 0.286, S3c void <= 0.122)"',
'          % contrast)',
'    if pred_frac is not None and pred_px is None:',
'        pred_px = pred_frac * half',
'    if mz - mb < 0.5 or contrast < 0.20:',
'        why = ("IDENTICAL halves (B1) or no texture" if mz - mb < 0.5',
'               else "LOW CONFIDENCE -- no single global shift aligns the halves "',
'                    "(a multi-depth sightline, 307 S3c)")',
'        print("VERDICT: CANNOT ANSWER -- %s. The dx above is NOT a measurement. "',
'              "Look at the picture before believing any dx." % why)',
'        return 3',
]
old = ("\n".join(OLD) + "\n").encode("utf-8")
new = ("\n".join(NEW) + "\n").encode("utf-8")
data = open(TARGET, "rb").read()
n = data.count(old)
if n != 1:
    print("REFUSED: anchor block found %d times, expected exactly 1. NOTHING WRITTEN." % n)
    sys.exit(2)
out = data.replace(old, new)
if data.count(b"\r\n") != out.count(b"\r\n"):
    print("REFUSED: line endings would change. NOTHING WRITTEN.")
    sys.exit(2)
open(TARGET, "wb").write(out)
print("PATCHED %s   %d -> %d bytes   CRLF=%d   (must be CRLF=0)" % (TARGET, len(data), len(out), out.count(b"\r\n")))
'@
Set-Content -Path F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\tools\_patch308.py -Value $patch -Encoding ascii
py F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\tools\_patch308.py F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\tools\stereo_disparity.py
py -c "import ast,io; ast.parse(io.open(r'F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\tools\stereo_disparity.py',encoding='utf-8').read()); print('SYNTAX OK')"
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
git rev-parse --show-toplevel
git --no-optional-locks status --porcelain -- getv/tools/stereo_disparity.py getv/tools/_patch308.py
git diff --stat -- getv/tools/stereo_disparity.py
git diff -- getv/tools/stereo_disparity.py
```

**GATE 5.2 — `PATCHED ... CRLF=0`, `SYNTAX OK`, `git rev-parse` prints the `goldeneye-native`
toplevel (`299` / `RUN-SHEET-300` §7), and `git diff --stat` reads `1 file changed, 10 insertions(+),
4 deletions(-)` on that ONE path.** Any other file in the diff, or any CRLF, means STOP.
**`_patch308.py` is scratch and is NOT part of the commit** — delete it or leave it untracked, but
do not let `COMMIT-NOW.cmd` sweep it (`307` §5).

### 5.3 — GATE 1.2a: `--selftest`

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
py ..\tools\stereo_disparity.py --selftest *> selftest_308.txt
Get-Content selftest_308.txt
```

**GATE 5.3 — three lines, `selftest A`, `selftest B`, `selftest C`, each ending `PASS`, text
unchanged from before the edit.** The edit is in `main()`'s output path and `selftest()` does not
go through it; **if the text moved, the wrong lines were edited.**

### 5.4 — GATE 1.2b: RE-SCORE ALL 16. **THE BLOCK `RUN-SHEET-308` §1.2 CITES AND `307` NEVER WROTE DOWN.**

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
"START $((Get-Date).ToString('o')) cwd=$($PWD.Path)" | Set-Content -Encoding ascii .\disp_308_S3_all.txt
foreach ($arm in @(@('S3b','run_307_S3b_sep32.log'), @('S3c','run_307_S3c_longsight.log'))) {
  $name = $arm[0]; $log = ".\$($arm[1])"
  if (-not (Test-Path $log)) { "MISSING $log -- ARM SKIPPED" | Add-Content .\disp_308_S3_all.txt; continue }
  $lines = Get-Content $log
  $bmps  = @(Get-ChildItem ".\grabs_307_$name\*.bmp" | Sort-Object Name)
  $preds = @($lines | Select-String -Pattern 'PREDICTION: disparity =').Count
  $dls   = @($lines | Select-String -Pattern '\[getv\]\[dlgrab\] frame \d+ ').Count
  "ARM $name grabs=$($bmps.Count) preds=$preds dls=$dls" | Add-Content .\disp_308_S3_all.txt
  foreach ($g in $bmps) {
    $fr = [regex]::Match($g.Name,'(\d+)\.bmp$').Groups[1].Value
    $ln = ($lines | Select-String -Pattern "\[getv\]\[dlgrab\] frame $fr " | Select-Object -First 1).LineNumber
    if (-not $ln) { "=== $name frame $fr   NO DLGRAB LINE ===" | Add-Content .\disp_308_S3_all.txt; continue }
    $m = ($lines[0..($ln-1)] | Select-String -Pattern 'PREDICTION: disparity = (-?[0-9.]+) x eye_width' | Select-Object -Last 1)
    $frac = $m.Matches.Groups[1].Value
    "=== $name frame $fr   predicted-frac $frac ===" | Add-Content .\disp_308_S3_all.txt
    py ..\tools\stereo_disparity.py $g.FullName --predicted-frac $frac --search 500 *>&1 | Add-Content .\disp_308_S3_all.txt
  }
}
"DONE $((Get-Date).ToString('o'))" | Add-Content .\disp_308_S3_all.txt
Select-String -Path .\disp_308_S3_all.txt -Pattern '^ARM |^=== |^dx |^confidence |^VERDICT'
```

**GATE 5.4a — the two `ARM` header lines must read `ARM S3b grabs=12 preds=211 dls=12` and
`ARM S3c grabs=4 preds=29 dls=4`.** Those are `307`'s own counts and they are how this
reconstruction proves it is the original block (§1.3). **A different count means a different
corpus, and the comparison in 5.5 is void.**

### 5.5 — THE FALSIFIER, SCORED MECHANICALLY

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
function Get-DxMap([string]$p) {
  $h = @{}; $n = $null
  foreach ($l in (Get-Content $p)) {
    if ($l -match '^=== (S3[bc]) frame (\d+)') { $n = "$($Matches[1])_$($Matches[2])" }
    elseif ($l -match '^dx\s+([+-]\d+) px' -and $n) { $h[$n] = [int]$Matches[1] }
  }
  return $h
}
$a = Get-DxMap .\disp_307_S3_all.txt
$b = Get-DxMap .\disp_308_S3_all.txt
"grabs: 307=$($a.Count)  308=$($b.Count)   (both must be 16)"
$bad = @($a.Keys | Where-Object { $a[$_] -ne $b[$_] })
if ($bad.Count -eq 0) { "GATE dx: ALL 16 IDENTICAL" } else { "GATE dx: MISMATCH -- " + ($bad -join ', ') }
$low = @(Select-String -Path .\disp_308_S3_all.txt -Pattern 'CANNOT ANSWER -- LOW CONFIDENCE')
"LOW CONFIDENCE refusals: $($low.Count)   (must be 4)"
$scored = @(Select-String -Path .\disp_308_S3_all.txt -Pattern '^VERDICT (PASS|FAIL)')
"scored grabs: $($scored.Count)   (must be 12)"
"--- which grabs were refused (all four must be S3c) ---"
$n = $null
foreach ($l in (Get-Content .\disp_308_S3_all.txt)) {
  if ($l -match '^=== (S3[bc]) frame (\d+)') { $n = "$($Matches[1])_$($Matches[2])" }
  elseif ($l -match 'CANNOT ANSWER -- LOW CONFIDENCE') { "  refused: $n" }
}
"--- frame 5400 must still read contrast 0.286 and VERDICT PASS ---"
Select-String -Path .\disp_308_S3_all.txt -Pattern 'S3b frame 5400' -Context 0,12
```

**GATE 5.5 — ALL FIVE LINES, OR THE FLOOR IS NOT FILED:**
`grabs 16 / 16` · `GATE dx: ALL 16 IDENTICAL` · `LOW CONFIDENCE refusals: 4` and **all four
`S3c`** · `scored grabs: 12` · **`5400` still `contrast 0.286` and `VERDICT PASS`.**
**If an `S3b` frame is refused, or an `S3c` frame still scores, the threshold is wrong: revert the
edit, do NOT file it, and the miss goes in `00-STATE` §4** (`301` §0, the count is five).

---

## §6 — ►►►►►►►► WORN. **`[MEASURED]` 2026-09-04 ON THE MAIN PC, UNDER `py`. `H1` AND `H18` CLOSE.**

**All five blocks of §5 ran in order. Every gate passed. No falsifier fired.**

| block | gate | `[MEASURED]` |
|---|---|---|
| **5.1** | GATE 1.0 — the split reproduces under `py` | **`S3b min contrast: 0.286` · `S3c max contrast: 0.122`.** Four `S3c` are the four lowest rows, no interleaving, gap **0.164**. **`H7` satisfied for this read: the bridge and `py` agree to all three decimals** |
| **5.2** | the edit applies without moving a byte it should not | **`15612 -> 15974 bytes   CRLF=0`**, `SYNTAX OK`, `git rev-parse --show-toplevel` = `F:/Projects/GEVR/GoldenEyeVR/goldeneye-native`, **`1 file changed, 10 insertions(+), 4 deletions(-)`** on the one path. Working tree: ` M getv/tools/stereo_disparity.py` + `?? getv/tools/_patch308.py` (scratch) and nothing else |
| **5.3** | GATE 1.2a — `--selftest` text unchanged | **`selftest A/B/C` all `PASS`, byte-identical**, and **no traceback under a redirected `cp1252` stdout** — which is `H16`'s exact failure venue, exercised on the patched file for the first time |
| **5.4** | GATE 5.4a — the reconstructed block is the original | **`ARM S3b grabs=12 preds=211 dls=12`** and **`ARM S3c grabs=4 preds=29 dls=4`**, both exact. **`disp_308_S3_all.txt` is written and diffs directly against `307`'s** |
| **5.5** | GATE 1.2b — **THE PRE-REGISTERED FALSIFIER** | **`grabs: 307=16  308=16` · `GATE dx: ALL 16 IDENTICAL` · `LOW CONFIDENCE refusals: 4` — `S3c_1620`, `S3c_5406`, `S3c_5462`, `S3c_7678`, ALL FOUR `S3c` AND NOTHING ELSE · `scored grabs: 12` · frame `5400` still `contrast 0.286`, `|-16 - -11.04| = 4.96 px`, `VERDICT PASS`** |

### 6.1 — WHAT CLOSED, AND WHAT IT COST

**`H1` CLOSES.** It was re-opened by `307` §1 because the peg alarm stayed silent on a −7,019 px
prediction while the correlator returned a confident interior spurious peak. **The alarm's premise
was never the fix — the amplitude clip is necessary and not sufficient.** The relative `contrast`
floor is the sibling `307` §2 said it needed, and it catches exactly the case the peg detector
cannot see: a frame that offers a strong-looking in-band maximum which is not a disparity.

**`H18` CLOSES WITH IT.** Its two failure modes are now both refused by the instrument itself — an
out-of-band prediction (the amplitude gate, already printed on every window) and a no-real-match
correlation (this floor). **A `dx` that survives both is a number the tool is willing to stand
behind, and it says so in a line of its own.**

**THE COST: ONE LINE OF OUTPUT AND NO CHANGE TO ANY `dx`.** All sixteen `dx` values are identical
to `307`'s. **The gate did not rescue an `S3c` frame and did not kill an `S3b` one** — `301` §0's
condition for filing, met by measurement rather than by the number looking reasonable.

### 6.2 — WHAT DID **NOT** CLOSE, AND IT IS THE HEADLINE

**`V3` / `258` STAGE 6 IS STILL OPEN AND THIS SESSION DID NOT MOVE IT.** The confidence gate makes
the instrument honest; it does not make `S3b` precise. **Eleven of twelve `S3b` grabs still miss
±5 px**, the error still grows with disparity magnitude (~5 px at −11 px predicted, ~52 px at
−406 px), and **the one frame that passes, `5400`, is also the frame with the SMALLEST predicted
disparity and the LOWEST contrast of the twelve (0.286 — it sits closest to the new floor).** That
is worth saying out loud rather than reading as a pass: **the only grab meeting `V3`'s pixel gate
is the one where the prediction is nearly zero, so it is the weakest possible evidence for the 1/D
law.** `RUN-SHEET-308` §2a is the next question and it is offline.
