> # ►►►► WORN IN FULL 2026-09-04. RESULT IN `310` §7-§9. ◄◄◄◄
> **Seven grabs, six admissible: ratios `0.6921`-`0.7184`, mean `0.7051`, spread `0.026` over a
> 6.7-fold depth range. CANDIDATE `C` IS DEAD and the correlator is accurate to ~2%.**
> **►►►► AND §3 BELOW CARRIED A DEFECT: NO ADMISSIBILITY GATE.** Grab `2917` (`predicted -503.85`
> px against a `[-500..+500]` search) was scored instead of refused, and it cleared the confidence
> floor at `contrast 0.733` while being unmeasurable. **`RUN-SHEET-307` §2.0's `|px| <= 500` rule
> already existed and this sheet did not carry it forward.** `00-STATE` §4. **`RUN-SHEET-311` §1
> carries the gate.**

# `RUN-SHEET-310` — **THE FLAT-WALL SINGLE-DEPTH GRAB.** THE ONLY THING THAT PUTS AN ERROR BAR ON THE CORRELATOR

> **`RUN-SHEET-308` §2b, FILED AS A COMPLETE BLOCK RATHER THAN CITED.** `308` §0 is the rule: a
> block that is improvised at the keyboard and produces a file later gates depend on is NOT filed
> by the file existing. §2b has been carried as prose in three documents and has never had a block.
>
> **PRE-REQUISITE: `310` §1-§3.** `H20` is closed negative — the renderer's frustum and the logged
> tangents are the same floats — so this run is no longer a tie-breaker between `0.667` and
> `0.750`. **It is now the primary instrument for `H19`**, and it discriminates `310` §4's
> candidate `C` (the correlator is biased on multi-depth scenes) from candidate `B` (the measured
> depth is short).

---

## §0 — WHAT THIS RUN IS FOR, AND WHAT IT IS NOT FOR

**FOR:** one scene with ONE depth across the entire eye, so `measured` and `predicted` can be
compared with no averaging argument available to either side.

**NOT FOR:** closing `V3`. **`V3` DOES NOT CLOSE ON A SINGLE FRAME AND IT NEVER CLOSES ON
`S3b_5400`** (`309` §5.2 — that frame passes ±5 px at every patch width because its prediction is
`-11.04` px, and a gate that cannot be failed is not a gate).

---

## §1 — PRE-REGISTERED, BEFORE THE RUN. **THESE ARE PREDICTIONS AND THEY ARE LABELLED AS SUCH**

`309` §7.1's rule, first application: every number below is arithmetic in advance, **not** a
measurement, and a miss on any of them is a finding rather than a failure.

| | `[PREDICTION]` | if it misses |
|---|---|---|
| **1a** | the log's `eye viewport` line reads **`160x180`, full width `320`, `tanw = 1.368534`**, identical to `run_307_S3b_sep32.log`'s 229 lines | the venue changed the viewport — say so before scoring anything |
| **1b** | `MEASURED centre depth D` lands in **`40`-`200`** at a wall you are standing against | the ray test is answering about something other than the wall |
| **1c** | `predicted px = -32 / (D * 1.368534) * 912.67 = -21341 / D` — so **`D = 60` predicts `-356` px, `D = 100` predicts `-213` px** | arithmetic error; re-derive before believing the run |
| **1d** | **`contrast >= 0.20` on every grab.** A flat textured wall is the best case the correlator will ever see | if a FLAT wall cannot clear the confidence floor, the floor is wrong and `H18` re-opens |
| **1e** | **THE MEASUREMENT: `measured / predicted`.** `~1.00` says the correlator is sound and `310` §4 candidate **`C` DIES** — the `0.69` belongs to `sep` or `D`. `~0.69` again says the correlator is NOT the problem either way and **`B`/`A` own it**. Anything else is new | — |

**THE SPREAD ACROSS THE FOUR OR FIVE GRABS IS THE ERROR BAR, AND IT IS THE POINT OF THE RUN.**
Report it as a range, never as a single number.

---

## §2 — THE RUN. **ONE SITTING, ~5 MINUTES, NO BUILD**

**VENUE: stand point-blank facing a FLAT, TEXTURED wall that FILLS THE ENTIRE VIEW.** No floor in
frame, no ceiling, no doorway, no long sightline. **Then take a half-pace back and grab again**, and
repeat — four or five grabs total, **STAND STILL for a second before each F9**. Varying the
distance is what makes the `1/D` law readable across the set; keeping the wall filling the frame is
what makes each grab single-depth.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
if (-not (Test-Path .\EXPECTED-EXE-303.txt)) { throw "EXPECTED-EXE-303.txt is missing -- run RUN-SHEET-303 section 2c after the build, before any arm." }
$want = (Get-Content .\EXPECTED-EXE-303.txt).Trim()
$got  = "$((Get-FileHash .\goldeneye.exe -Algorithm SHA256).Hash) $((Get-Item .\goldeneye.exe).Length)"
if ($want -ne $got) { throw "BINARY MISMATCH -- this is NOT the 303 build. want [$want] got [$got]" }
if (Test-Path .\run_310_S3d_flatwall.log) { throw "run_310_S3d_flatwall.log EXISTS -- rename it or pick a new name (H5)." }
Get-ChildItem .\dlgrab_*.txt,.\dlgrab_*.bmp -ErrorAction SilentlyContinue | Measure-Object | Select-Object -ExpandProperty Count
$env:GETV_ARM                   = "S3d"
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
$env:GETV_STEREO_OFFSET         = "32"
$env:GETV_STEREO_MODE           = "1"
$env:GETV_STEREO_PROBE          = "60"
$env:GETV_STEREO_VIEWRESTORE    = "1"
$env:GETV_STEREO_PAIRGUARD      = "0"
$env:GETV_STEREO_REBUILD        = "1"
$env:GETV_STEREO_REBUILD_REPORT = "1"
$env:GETV_STEREO_REBUILD_VIEWER = "1"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_310_S3d_flatwall.log 2>&1
Select-String -Path run_310_S3d_flatwall.log -Pattern 'getv\]\[run\] ARM='
Select-String -Path run_310_S3d_flatwall.log -Pattern 'separation=' | Select-Object -First 2
Select-String -Path run_310_S3d_flatwall.log -Pattern 'eye viewport' | Select-Object -First 1
Select-String -Path run_310_S3d_flatwall.log -Pattern 'dlgrab_|getv\]\[shot\]'
Select-String -Path run_310_S3d_flatwall.log -Pattern 'props interpolated|simulation held to|ours: x=|game_exit requested|EXCEPTION'
New-Item -ItemType Directory -Force -Path .\grabs_310_S3d | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_310_S3d -Force -ErrorAction SilentlyContinue
Get-ChildItem .\grabs_310_S3d | Select-Object Name, Length
```

**`GETV_DLGRAB_AT` IS DELIBERATELY NOT SET** — `307` §2a pinned frame `5400` because it wanted one
known frame; this run wants whichever frames the owner chooses at the wall, and F9 is the trigger.

---

## §3 — SCORE IT. **THE SAME SHAPE AS `RUN-SHEET-308` §1.3, ONE ARM**

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
"START $((Get-Date).ToString('o')) cwd=$($PWD.Path)" | Set-Content -Encoding ascii .\disp_310_S3d.txt
$log   = ".\run_310_S3d_flatwall.log"
$lines = Get-Content $log
$bmps  = @(Get-ChildItem .\grabs_310_S3d\*.bmp | Sort-Object Name)
$preds = @($lines | Select-String -Pattern 'PREDICTION: disparity =').Count
$dls   = @($lines | Select-String -Pattern '\[getv\]\[dlgrab\] frame \d+ ').Count
"ARM S3d grabs=$($bmps.Count) preds=$preds dls=$dls" | Add-Content .\disp_310_S3d.txt
foreach ($g in $bmps) {
  $fr = [regex]::Match($g.Name,'(\d+)\.bmp$').Groups[1].Value
  $ln = ($lines | Select-String -Pattern "\[getv\]\[dlgrab\] frame $fr " | Select-Object -First 1).LineNumber
  if (-not $ln) { "=== S3d frame $fr   NO DLGRAB LINE ===" | Add-Content .\disp_310_S3d.txt; continue }
  $m = ($lines[0..($ln-1)] | Select-String -Pattern 'PREDICTION: disparity = (-?[0-9.]+) x eye_width' | Select-Object -Last 1)
  $d = ($lines[0..($ln-1)] | Select-String -Pattern 'MEASURED centre depth D=([0-9.]+)' | Select-Object -Last 1)
  $frac = $m.Matches.Groups[1].Value
  $dep  = if ($d) { $d.Matches.Groups[1].Value } else { "NONE" }
  "=== S3d frame $fr   predicted-frac $frac   D $dep ===" | Add-Content .\disp_310_S3d.txt
  py ..\tools\stereo_disparity.py $g.FullName --predicted-frac $frac --search 500 *>&1 | Add-Content .\disp_310_S3d.txt
}
"DONE $((Get-Date).ToString('o'))" | Add-Content .\disp_310_S3d.txt
Select-String -Path .\disp_310_S3d.txt -Pattern '^ARM |^=== |^dx |^confidence |^VERDICT|CANNOT ANSWER'
```

**GATE 3a — the header must read `ARM S3d grabs=N preds=M dls=N` with `grabs = dls` and both equal
the number of times F9 was pressed.** A mismatch means a grab has no announcement and is
inadmissible (`279` §2).

**GATE 3b — every grab must print `contrast >= 0.20`.** A refusal on a flat textured wall is
`[PREDICTION] 1d` missing, and it is a bigger finding than the ratio.

**THEN PASTE `disp_310_S3d.txt`'s summary lines.** The ratio per grab is
`measured_px / predicted_px`, and **the SPREAD of those ratios is the correlator's error bar** —
the number nothing on disk has ever measured.

---

## §4 — WHAT EACH OUTCOME MEANS. **PRE-REGISTERED, SO NOTHING CAN BE READ INTO IT AFTER THE FACT**

| result | reading | what moves |
|---|---|---|
| ratios cluster near **`1.00`**, spread small | the correlator is sound on single-depth scenes; the `~0.69` is an artefact of multi-depth frames | **`310` §4 candidate `C` LIVES and `H19` becomes an instrument-venue problem.** `V3` needs a venue rule, not a fix |
| ratios cluster near **`0.69`**, spread small | the under-read survives the cleanest possible target | **`C` DIES. `A` (the applied separation) and `B` (the measured depth) own it, and the next step is an instrumented print, not a read** |
| spread is **wide** (say worse than ±10%) | the correlator's own error bar is comparable to the effect | **`V3`'s ±5 px gate is not achievable with this instrument at all, and that is a `00-STATE` §4 entry about the GATE, not about the game** |
| any grab **refused** on contrast | `[PREDICTION] 1d` missed | `H18` re-opens; the floor was calibrated on frames that were not the best case |

**NO PATCH IS AUTHORISED BY THIS SHEET.** `301` §0 — the count of wrong filed fixes is five, and
`309` and `310` are both cases for the rule.
