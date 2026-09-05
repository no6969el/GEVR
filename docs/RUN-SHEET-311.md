# `RUN-SHEET-311` — **IS THE `0.705` A PURE SCALE ON THE SEPARATION?** TWO `LOW` RUNS, NO BUILD

> **►►►►►►►► WORN 2026-09-04, BOTH SECTIONS, ON THE MAIN PC. SUPERSEDED BY `RUN-SHEET-312`.**
> **§2 ANSWERED `2b`:** medians `0.6907` / `0.7036` / `0.6960` at `sep` `32` / `64` / `128` —
> **a pure scale, flat over a 4-fold range.** `2d` did not fire. **`[PREDICTION] 2c` FAILED** and
> `00-STATE` §4 carries it (`sep128` spread `0.0485` against `sep64`'s `0.0133`).
> **§3 ANSWERED WITH THE SECOND BRANCH: `MODE=2` READ `0.7075`, NOT `1.00`** — seven grabs,
> `dx = -60` on every one. **The loss is common to both paths and candidate `A` is RETRACTED:
> the separation is applied in full to better than 1%** (`311` §6, `00-STATE` §4).
> **§0's `450` gate fired for real** — `sep128` frame `2462`, predicted `-476` px, refused.
> **DO NOT RE-RUN THIS SHEET.** `RUN-SHEET-312` §1 carries the scorer with the half as an argument,
> which this sheet's hard-coded `912` cannot do.

> **STATE ON ENTRY (`310` §9):** every link in the disparity chain is measured sound except one.
> The frustum is the prediction's own (§1), the 4:3 is retail (§2), `tR` cancels (§0 item 5), the
> pixel scale is confirmed three ways (§0 item 6, §8.1), the depth tracks the camera 1:1 over 28
> pairs (§8), and the correlator is good to ~2% (§7). **What is left is that the separation
> reaching the drawn image is `~0.705` of the one requested — `~22.6` game units instead of `32`.**
>
> **NOTHING HERE PATCHES ANYTHING.** `301` §0 — the count of wrong filed fixes is five, and both
> `309` and `310` are cases for the rule. **These two runs NARROW the candidate; they do not name
> a line, and no line is to be edited on their evidence alone.**

---

## §0 — THE ADMISSIBILITY GATE, WHICH `RUN-SHEET-310` §3 SHOULD HAVE CARRIED AND DID NOT

**`310` §7.2:** grab `2917` predicted `-503.85` px against a `searched [-500 .. +500]` window, was
**scored instead of refused**, and **cleared the confidence floor at `contrast 0.733`.** The
confidence floor asks whether a peak is well-defined; **`H18`'s amplitude gate asks whether the
answer is expressible, and they are not substitutes.**

**►►►► RULE FOR EVERY BLOCK IN THIS SHEET: A GRAB IS ADMISSIBLE ONLY IF `|predicted px| <= 450`.**
`RUN-SHEET-307` §2.0 says `<= 500`; **`450` leaves margin so a grab does not become inadmissible
because the owner stood 4 px too close.** §1's scorer refuses the rest mechanically, out loud, and
excludes them from every median — **it does not call them outliers.**

---

## §1 — THE SCORER, WITH THE GATE IN IT. **USE THIS ONE, NOT `RUN-SHEET-310` §3**

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
function Score-Arm([string]$arm, [string]$log, [string]$grabs, [string]$out) {
  "START $((Get-Date).ToString('o')) arm=$arm log=$log" | Set-Content -Encoding ascii $out
  if (-not (Test-Path $log)) { "MISSING $log -- ARM SKIPPED" | Add-Content $out; return }
  $lines = Get-Content $log
  $bmps  = @(Get-ChildItem "$grabs\*.bmp" -ErrorAction SilentlyContinue | Sort-Object Name)
  $preds = @($lines | Select-String -Pattern 'PREDICTION: disparity =').Count
  $dls   = @($lines | Select-String -Pattern '\[getv\]\[dlgrab\] frame \d+ ').Count
  "ARM $arm grabs=$($bmps.Count) preds=$preds dls=$dls" | Add-Content $out
  foreach ($g in $bmps) {
    $fr = [regex]::Match($g.Name,'(\d+)\.bmp$').Groups[1].Value
    $ln = ($lines | Select-String -Pattern "\[getv\]\[dlgrab\] frame $fr " | Select-Object -First 1).LineNumber
    if (-not $ln) { "=== $arm frame $fr   NO DLGRAB LINE -- INADMISSIBLE (279 s2) ===" | Add-Content $out; continue }
    $m = ($lines[0..($ln-1)] | Select-String -Pattern 'PREDICTION: disparity = (-?[0-9.]+) x eye_width' | Select-Object -Last 1)
    $d = ($lines[0..($ln-1)] | Select-String -Pattern 'MEASURED centre depth D=([0-9.]+)' | Select-Object -Last 1)
    $frac = [double]$m.Matches.Groups[1].Value
    $dep  = if ($d) { $d.Matches.Groups[1].Value } else { "NONE" }
    $px   = $frac * 912.0
    if ([Math]::Abs($px) -gt 450) {
      "=== $arm frame $fr   D $dep   predicted $([Math]::Round($px,2)) px   INADMISSIBLE -- |px| > 450 (H18, RUN-SHEET-307 s2.0). NOT SCORED, NOT AN OUTLIER. ===" | Add-Content $out
      continue
    }
    "=== $arm frame $fr   predicted-frac $frac   D $dep   predicted $([Math]::Round($px,2)) px ===" | Add-Content $out
    py ..\tools\stereo_disparity.py $g.FullName --predicted-frac $frac --search 500 *>&1 | Add-Content $out
  }
  "DONE $((Get-Date).ToString('o'))" | Add-Content $out
  Select-String -Path $out -Pattern '^ARM |^=== |^dx |^confidence |^VERDICT|CANNOT ANSWER'
}
```

**Paste that function once per PowerShell window; §2 and §3 call it.**

---

## §2 — **THE SEPARATION SWEEP. THE PRIMARY TEST.** `LOW`, no build, ~5 minutes

**THE QUESTION: is `0.705` a pure scale factor on the separation, or does it move with `sep`?**
`A` as stated predicts **the same ratio at every separation.** Anything else — an additive term, a
clamp, a saturation — shows up here and outranks everything on the board.

**VENUE: the same flat wall as `310` §7, and stand at `D` between roughly `150` and `450`.**
`[ARITHMETIC]` at `D = 180` the predictions are `-120 / -239 / -479` px for `sep` `32 / 64 / 128`,
so **the largest separation is the one that can go inadmissible — at `sep 128` stand no closer than
`D ~= 190`** (`21341 * 4 / 450`). Three short runs, **four or five F9 grabs each, at the SAME
spots**, so the three arms are comparable grab for grab.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
if (-not (Test-Path .\EXPECTED-EXE-303.txt)) { throw "EXPECTED-EXE-303.txt is missing -- run RUN-SHEET-303 section 2c after the build, before any arm." }
$want = (Get-Content .\EXPECTED-EXE-303.txt).Trim()
$got  = "$((Get-FileHash .\goldeneye.exe -Algorithm SHA256).Hash) $((Get-Item .\goldeneye.exe).Length)"
if ($want -ne $got) { throw "BINARY MISMATCH -- this is NOT the 303 build. want [$want] got [$got]" }
foreach ($sep in @(32,64,128)) {
  $log = ".\run_311_sep$sep.log"
  if (Test-Path $log) { throw "$log EXISTS -- rename it or pick a new name (H5)." }
}
$env:GETV_SLOTFREE              = "1"
$env:GETV_VSYNC                 = "1"
$env:GETV_FPS                   = "panel"
$env:GETV_SIMHZ                 = "query"
$env:GETV_SIMDIV                = "1"
$env:GETV_WIDESCREEN            = "0"
$env:GETV_ROOMSCISSOR           = "1"
$env:GETV_WINDOW                = "2560x1369"
$env:GETV_STAGE                 = "29"
$env:GETV_DIFFICULTY            = "0"
$env:GETV_STEREO                = "1"
$env:GETV_STEREO_MODE           = "1"
$env:GETV_STEREO_PROBE          = "60"
$env:GETV_STEREO_VIEWRESTORE    = "1"
$env:GETV_STEREO_PAIRGUARD      = "0"
$env:GETV_STEREO_REBUILD        = "1"
$env:GETV_STEREO_REBUILD_REPORT = "1"
$env:GETV_STEREO_REBUILD_VIEWER = "1"
```

**THEN, ONCE PER SEPARATION — run the game, grab, quit, and repeat with the next number.**
The three blocks are identical except for the two values, and they are written out in full rather
than as "the same block with" (`296` §11, `00-STATE` §7a):

```powershell
$env:GETV_ARM = "sep32";  $env:GETV_STEREO_OFFSET = "32"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_311_sep32.log 2>&1
New-Item -ItemType Directory -Force -Path .\grabs_311_sep32 | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_311_sep32 -Force -ErrorAction SilentlyContinue
Select-String -Path run_311_sep32.log -Pattern 'separation=' | Select-Object -First 1
Get-ChildItem .\grabs_311_sep32 | Measure-Object | Select-Object -ExpandProperty Count
```

```powershell
$env:GETV_ARM = "sep64";  $env:GETV_STEREO_OFFSET = "64"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_311_sep64.log 2>&1
New-Item -ItemType Directory -Force -Path .\grabs_311_sep64 | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_311_sep64 -Force -ErrorAction SilentlyContinue
Select-String -Path run_311_sep64.log -Pattern 'separation=' | Select-Object -First 1
Get-ChildItem .\grabs_311_sep64 | Measure-Object | Select-Object -ExpandProperty Count
```

```powershell
$env:GETV_ARM = "sep128"; $env:GETV_STEREO_OFFSET = "128"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_311_sep128.log 2>&1
New-Item -ItemType Directory -Force -Path .\grabs_311_sep128 | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_311_sep128 -Force -ErrorAction SilentlyContinue
Select-String -Path run_311_sep128.log -Pattern 'separation=' | Select-Object -First 1
Get-ChildItem .\grabs_311_sep128 | Measure-Object | Select-Object -ExpandProperty Count
```

**SCORE ALL THREE:**

```powershell
Score-Arm "sep32"  ".\run_311_sep32.log"  ".\grabs_311_sep32"  ".\disp_311_sep32.txt"
Score-Arm "sep64"  ".\run_311_sep64.log"  ".\grabs_311_sep64"  ".\disp_311_sep64.txt"
Score-Arm "sep128" ".\run_311_sep128.log" ".\grabs_311_sep128" ".\disp_311_sep128.txt"
```

### 2.1 — PRE-REGISTERED. **`[PREDICTION]`, AND LABELLED AS ONE** (`309` §7.1)

| | `[PREDICTION]` | what it means |
|---|---|---|
| **2a** | the log's `separation=` line reads **`32.000` / `64.000` / `128.000` FULL** on the three arms | if a knob does not take, nothing else in the arm means anything |
| **2b** | **the ratio is the SAME on all three arms, `0.70 +/- 0.03`** | `A` as stated: a pure scale on the separation |
| **2c** | the `sep 128` ratios are the TIGHTEST, because quantization is 4x smaller there | it also gives the best single estimate of the constant |
| **2d** | **IF THE RATIO MOVES WITH `sep`** — say `0.705 / 0.85 / 0.92` — then it is **NOT a scale factor**: something adds or clamps, and **that outranks every other item on the board** | a new hole, filed as one |

**THE MEASUREMENT TO REPORT: three medians and their spreads, and the ratio-of-ratios between
arms.** Not a single number.

---

## §3 — **THE `MODE=2` DISCRIMINATOR.** `LOW`, no build, ~5 minutes. **A FALSIFIER, NOT A FIX**

`GETV_STEREO_MODE=2` puts the shift in the **PROJECTION** (`stereo.c:284-295`) and **returns 0 from
`geStereoOffsetCameraPos()` without touching the view matrix** (`stereo.c:355-357`). It is tuned so
that at `GE_STEREO_B1_DEPTH = 1000` it produces exactly the disparity a real separation would
(`stereo.c:22`).

**►►►► THEREFORE, AND THIS IS THE WHOLE POINT: AT `D ~= 1000`, `MODE=2` AND `MODE=1` SHOULD AGREE
WITH THE SAME PREDICTION — AND THEY TRAVEL BY DIFFERENT PATHS.**

- **`MODE=2` reads `~1.00` →** the projection path delivers the full separation and **the loss is
  in the VIEW path specifically. `A` is confirmed as a view-path defect** and the instrumented
  print is worth its build.
- **`MODE=2` also reads `~0.705` →** the loss is **common to both paths**, and something `310`
  believes it cleared is not clear. **That is the more important answer and it would reopen §8.1.**

**VENUE: `D` near `1000` — a long sightline, NOT the flat wall.** `[ARITHMETIC]` at `sep 32`,
`D = 1000` predicts `-21.3` px, which is small and heavily quantized, **so use `sep 128`:
`-85.4` px at `D = 1000`, comfortably inside the gate.**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
$want = (Get-Content .\EXPECTED-EXE-303.txt).Trim()
$got  = "$((Get-FileHash .\goldeneye.exe -Algorithm SHA256).Hash) $((Get-Item .\goldeneye.exe).Length)"
if ($want -ne $got) { throw "BINARY MISMATCH -- this is NOT the 303 build. want [$want] got [$got]" }
if (Test-Path .\run_311_mode2.log) { throw "run_311_mode2.log EXISTS -- rename it or pick a new name (H5)." }
$env:GETV_ARM                   = "mode2"
$env:GETV_SLOTFREE              = "1"
$env:GETV_VSYNC                 = "1"
$env:GETV_FPS                   = "panel"
$env:GETV_SIMHZ                 = "query"
$env:GETV_SIMDIV                = "1"
$env:GETV_WIDESCREEN            = "0"
$env:GETV_ROOMSCISSOR           = "1"
$env:GETV_WINDOW                = "2560x1369"
$env:GETV_STAGE                 = "29"
$env:GETV_DIFFICULTY            = "0"
$env:GETV_STEREO                = "1"
$env:GETV_STEREO_OFFSET         = "128"
$env:GETV_STEREO_MODE           = "2"
$env:GETV_STEREO_PROBE          = "60"
$env:GETV_STEREO_VIEWRESTORE    = "1"
$env:GETV_STEREO_PAIRGUARD      = "0"
$env:GETV_STEREO_REBUILD        = "1"
$env:GETV_STEREO_REBUILD_REPORT = "1"
$env:GETV_STEREO_REBUILD_VIEWER = "1"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_311_mode2.log 2>&1
Select-String -Path run_311_mode2.log -Pattern 'mode=2'  | Select-Object -First 1
Select-String -Path run_311_mode2.log -Pattern 'separation=' | Select-Object -First 1
New-Item -ItemType Directory -Force -Path .\grabs_311_mode2 | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_311_mode2 -Force -ErrorAction SilentlyContinue
Score-Arm "mode2" ".\run_311_mode2.log" ".\grabs_311_mode2" ".\disp_311_mode2.txt"
```

**GRAB DOWN THE LONGEST SIGHTLINE YOU HAVE, four or five times, and read each grab's own
`MEASURED centre depth D` — the ones near `1000` are the scorable ones.** Grabs far from `1000`
are **expected** to disagree under `MODE=2` (that is what `B1` IS) and must not be read as a
result: **only `D` within roughly `800`-`1300` is admissible for this arm**, on top of §0's gate.

---

## §4 — WHAT NEEDS A PERSON

- **§2, then §3.** Both `LOW`, both ~5 minutes, neither needs a build. **§2 first — it is the one
  that can name the constant.**
- **The commit** for whatever these produce, this session's own paths only, explicit `git add --`
  path lists, `git commit -F`. **Do NOT use `COMMIT-NOW.cmd`** (`307` §5).
- **`E3` (FC3/FC4) is CLOSED.** Do not re-ask.
- **DO NOT START GROUP `C` / `V7`** — `HIGH`, `PRIORITY-BOARD-310` §E item 9.

## §5 — AND THE STANDING ONE

**`V3` / `258` STAGE 6 CANNOT CLOSE UNTIL THE `0.705` IS FOUND** (`310` §9.1: with a constant
`0.705` the `±5 px` gate can only pass where `|predicted| <= 17 px`). **It does not close on
`S3b_5400` under any circumstances** (`309` §5.2). **Nothing in this sheet closes it either, and
no sheet should be written that claims to until `A` has a name.**
