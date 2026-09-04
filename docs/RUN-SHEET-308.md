# `RUN-SHEET-308` — GIVE THE DISPARITY TOOL A CONFIDENCE GATE, THEN GO AFTER THE ±5 px PRECISION `V3` NEEDS

> **►►►►►►►► §1 IS WORN IN FULL, 2026-09-04, ON THE MAIN PC UNDER `py`. EVERY GATE PASSED AND
> `H1` + `H18` CLOSE TOGETHER.** The result, the five blocks as actually run, and the three
> documentation defects found on the way are in
> **`308-THE-CONFIDENCE-GATE-IS-MEASURED-BEFORE-IT-IS-PATCHED`** §5 and §6.
> **§2a IS THE NEXT ACTION AND IT IS OFFLINE.** Corrections applied to this sheet in place, below:
> §1.0's `S3c` maximum is **`0.122`**, not `0.123`; §1.1's replacement text carries the corrected
> number; and **§1.3 is NEW — it is the all-16 scoring block §1.2 cited and `307` never wrote down.**

> Written OFFLINE 2026-09-04, after `RUN-SHEET-307` §1 and §2 were worn on the main PC.
> **`RUN-SHEET-307` IS WORN IN FULL.** §1 fired the `H1` falsifier (the peg alarm stayed SILENT —
> an interior spurious peak, `H1` RE-OPENED), and §2 scored all 16 `S3b`/`S3c` grabs offline:
> **GATE 6.1 PASSES ON EVERY FRAME, both arms** (census era closed); **GATE S3 (±5 px) does NOT** —
> `S3b` sign-correct and 1/D-tracking but only 1/12 within ±5 px, `S3c` all wrong-sign with
> `mad_best`≈`mad_zero` (void, not a dead eye).
>
> **Same rules as always. You work OFFLINE. The build, every run and every commit are the owner's,
> on the main PC. Supply complete copy-paste PowerShell blocks; quote a block verbatim. Never stage,
> commit, branch, merge or tag.** `git log`, `git show` and `git diff <path>` are bridge-safe;
> `git status` needs `--no-optional-locks` **and a path list**. **A PLACEHOLDER IS NOT A COMMAND:**
> `<` is a RESERVED OPERATOR in PowerShell (`00-STATE` §7a, `307` §0). **Instrument OUTPUT is ASCII
> (`H16`); docs may have arrows, tools may not.** **A HOLE'S FILED FIX IS A DIAGNOSIS, NOT A PATCH —
> the count of wrong filed fixes is five (`301` §0). MEASURE BEFORE YOU PATCH.**

---

## §0 — WHAT `307` RETURNED, IN ONE TABLE

| | |
|---|---|
| §1 | **`H1` RE-OPENED.** The peg alarm stayed SILENT on all four searches of `dlgrab_S3_5400`; the correlator returned an interior spurious peak (`dx +351/+172 px`, wrong sign, moving with `--search`) on a −7,019 px prediction. An out-of-band prediction does NOT force a peg |
| §2 6.1 | **PASS on all 16 grabs, both arms.** `only in eye0 = 0 / only in eye1 = 0`, every `MODEL_*` equal both eyes. Census era closed |
| §2 S3 | **`S3b`** (sep 32): all 12 signs CORRECT, magnitudes track 1/D, STRONG correlation — but only frame `5400` within ±5 px (error grows with disparity magnitude). **`S3c`** (sep 500, long sightline): all four WRONG SIGN, `mad_best`≈`mad_zero`, VOID — census perfect, so not a dead eye |
| net | **The 1/D law is DIRECTIONALLY confirmed (S3b) but not to ±5 px. `V3`/`258` STAGE 6 does NOT close.** Two instruments are owed: a CONFIDENCE gate that rejects `S3c`-type noise, and a disparity read a multi-depth scene cannot fool |

**THIS SHEET IS ALL OFFLINE EXCEPT §2b, WHICH IS ONE OPTIONAL RUN.** The 16 `307` grabs on disk are
the whole test corpus for §1.

---

## §1 — THE CONFIDENCE GATE. **`H1`/`H18`. OFFLINE, AND ITS FALSIFIER IS ALREADY ON DISK.**

`stereo_disparity.py:272` already refuses when `mz - mb < 0.5` — an ABSOLUTE floor. **`307` §2
measured it too low:** `S3c` reads `mz - mb` of 2.1 and 1.1, clears 0.5, and is scored as a
WRONG-SIGN FAIL when it should read CANNOT ANSWER. **The fix is a RELATIVE floor on the fraction by
which the best shift beats the zero shift.**

### 1.0 — MEASURE BEFORE YOU PATCH. Re-derive the separation from the numbers already written.

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

**GATE 1.0 — PRE-REGISTERED FROM `307` §2:** `S3b`'s minimum `contrast` is **0.286** (frame `5400`,
the only ±5 px PASS) and `S3c`'s maximum is **0.122** (frame `1620`) — **`RUN-SHEET-308` as first written said `0.123`;
`(17.366 - 15.239) / 17.366 = 0.12249`, and `00-STATE` §4 carries the correction because the number
was about to be printed inside the instrument.** **A floor of `0.20` separates
them with 0.086 / 0.078 of margin. If this block does not reproduce that split, STOP — the
threshold is not real and must not be filed.**

### 1.1 — THE EDIT. **`getv/tools/stereo_disparity.py`, one place, ASCII only.**

Replace the block at **`stereo_disparity.py:269-276`** — currently:

```python
    print("mad_best    %.3f       mad_zero %.3f" % (mb, mz))
    if pred_frac is not None and pred_px is None:
        pred_px = pred_frac * half
    if mz - mb < 0.5:
        print("VERDICT: CANNOT ANSWER -- the two halves match no better shifted than "
              "unshifted. Either the halves are IDENTICAL (that is `B1`) or the patch has "
              "no texture to correlate. Look at the picture before believing any dx.")
        return 3
```

with:

```python
    print("mad_best    %.3f       mad_zero %.3f" % (mb, mz))
    contrast = (mz - mb) / mz if mz > 0 else 0.0
    print("confidence  contrast %.3f   (best shift beats zero shift by this fraction; "
          ">= 0.20 required to TRUST dx -- 307 s2: S3b real >= 0.286, S3c void <= 0.122)"
          % contrast)
    if pred_frac is not None and pred_px is None:
        pred_px = pred_frac * half
    if mz - mb < 0.5 or contrast < 0.20:
        why = ("IDENTICAL halves (B1) or no texture" if mz - mb < 0.5
               else "LOW CONFIDENCE -- no single global shift aligns the halves "
                    "(a multi-depth sightline, 307 S3c)")
        print("VERDICT: CANNOT ANSWER -- %s. The dx above is NOT a measurement. "
              "Look at the picture before believing any dx." % why)
        return 3
```

**It changes NO `dx`.** It adds one `confidence` line and turns the existing absolute floor into
`absolute OR relative`. The absolute `mz - mb < 0.5` stays so the `B1` identical-halves case is still
caught. **Do not add a second, separate check elsewhere (`H16`): this is the one gate.**

### 1.2 — SELFTEST, THEN RE-SCORE THE 16. **THE FALSIFIER.**

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
py ..\tools\stereo_disparity.py --selftest *> selftest_308.txt
Get-Content selftest_308.txt
```

**GATE 1.2a — `--selftest` must still read `selftest A/B/C` all passing.** The edit is in `main()`'s
output path, not in `selftest()`, so the selftest text is unchanged; if it differs, the wrong lines
were edited.

**►►►►►►►► AND THE SENTENCE THAT USED TO STAND HERE WAS FALSE: *"re-run `307` §2c's scoring block
unchanged (it writes `disp_307_S3_all.txt` and `census_307_S3_all.txt`)".* THAT BLOCK DOES NOT
EXIST.** `RUN-SHEET-307` §2c scores ONE grab per arm and carries `<frame>` / `<frac>` placeholders;
the all-16 block was improvised live in the `307` session and never filed. **IT IS §1.3 BELOW, and
it is proven: both `ARM ... grabs=N preds=N dls=N` headers and all 16 `predicted-frac` values
reproduce `307`'s exactly.** `00-STATE` §4 and §6.

Run **§1.3**, then score it with **§1.4**. **GATE 1.2b — THE PRE-REGISTERED FALSIFIER:**

- **All four `S3c` grabs must now read `VERDICT: CANNOT ANSWER -- LOW CONFIDENCE`.**
- **All twelve `S3b` grabs must still SCORE** (their `dx` byte-identical to `307` §2), and frame
  `5400` in particular must still read its `contrast 0.286` and still PASS.
- **If a real `S3b` frame flips to CANNOT ANSWER, or an `S3c` frame still scores, the threshold is
  wrong — do NOT file it, and record the miss in `00-STATE` §4.**

If 1.2b passes, **`H1` and `H18` close together**: the tool now refuses the two failure modes that
fooled it — an out-of-band prediction (the amplitude clip, already printed) and a no-real-match
correlation (this contrast floor).

### 1.3 — THE ALL-16 RE-SCORE BLOCK. **FILED HERE BECAUSE `307` NEVER FILED IT.**

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


### 1.4 — SCORE THE FALSIFIER MECHANICALLY

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

## §2 — THE PRECISION `V3` ACTUALLY NEEDS. **WHY `S3b` UNDER-READS, AND WHETHER A CLEAN TARGET CLOSES ±5 px.**

`S3b` is sign-correct and tracks 1/D, but the error grows with disparity magnitude — **~5 px at
−11 px predicted, ~52 px at −406 px**, roughly a 10-13% proportional error. The prediction uses the
**centre-ray depth** `D` (engine ray test at screen centre); the correlator averages a patch of the
central quarter (`stereo_disparity.py:86`, `xs = [half//4 .. 3*half//4]`). **Candidate diagnosis: the
matched texture sits at a depth different from the centre ray, so measured and predicted are two
different depths' disparities.** This is a DIAGNOSIS to test, not a patch to file.

### 2a — OFFLINE FIRST: does a tighter, ray-aligned patch shrink the error?

Add a `--patch FRAC` option (default the current 0.25-0.75 window) that narrows `xs` to a small band
around the crosshair column, and re-score the seven strong `S3b` grabs. **GATE 2a:** if the
proportional error falls toward ±5 px as the patch tightens, the under-read is patch-averaging over
depth and the fix is to correlate where the ray test was taken. If it does NOT move, the under-read
is elsewhere (projection scale, or the log's `D` itself) and §2b is required. **This touches only the
instrument and reuses the grabs on disk — no run.**

### 2b — ONE RUN, ONLY IF §2a IS INCONCLUSIVE: a single-depth target.

The whole-eye correlator assumes ONE depth. `S3b`'s near-wall frames approximate it; nothing on disk
IS it. **Stand point-blank facing a FLAT, TEXTURED wall that fills the entire view** (no floor, no
ceiling, no long line) at `GETV_STEREO_OFFSET=32`, and press F9 four or five times. One depth across
the whole eye means predicted and measured should agree tightly. **GATE 2b:** a single-depth grab
that passes ±5 px (with `contrast >= 0.20`) closes `V3`'s pixel gate on a controlled target; a
single-depth grab that still under-reads by ~10% is a real projection-scale result and outranks
everything else on the board. **This is the only person-cost step in this sheet, and it is deferred
behind §2a.**

---

## §3 — WHAT NEEDS A PERSON

- **Nothing, unless §2a is inconclusive** — then §2b is one short run at a flat wall (above).
- `E3` (FC3/FC4) is **CLOSED** as of `307`'s handover (`[REPORTED]`: they looked the same) — do not
  re-ask.

---

## §4 — THE COMMIT. **TWO REPOS THIS TIME (the tool edit + the docs). OWNER-RUN.**

`§1.1` edits `goldeneye-native/getv/tools/stereo_disparity.py` (tracked, no regen — it is not a
third-party file). The docs are the `GoldenEyeVR` repo. **Commit only this sheet's own paths; check
the dirty set first (`307` §5's `COMMIT-NOW.cmd` swept 16 strays because it stages the whole tree).**
Supplied complete when §1 and §2 are worn and their gates are known.

---

## §5 — AFTER `308`

- If `V3` closes at §2b: **`V4` (`S4`, the mode-2 falsifier) must run in the same sitting** — a pass
  with no negative arm is a claim, not a result (`49`, `PRIORITY-BOARD-307` `V4`). Then `V5`
  (`R5a/b/c`, ARM 3's cost with stereo ON), `V6` (a real IPD), and only then `V7`/GROUP `C` (the
  one-eye polygon) before extended headset time.
- If `V3` does not close: the §2b under-read is the next instrument question, and GROUP `X` (the XR
  layer, which does not exist) stays blocked behind it.

**`169` NEXT ID = `U-26`.**
