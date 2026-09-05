# `RUN-SHEET-313` — **KILL THE ASPECT TERM OR CONFIRM IT.** THREE SHORT ARMS, NO BUILD

> **STATE ON ENTRY (`312` §2):** `RUN-SHEET-312` §2 is worn. **The ratio TRACKS THE WINDOW** —
> medians `1.0987` at `1600x1369` and `0.3813` at `2560x800` against the control's `0.7036` at
> `2560x1369`. **`C1` is dead in direction; `C2` is right in direction and off by `+9.9%`/`-8.3%`.**
> **`[MEASURED, BRIDGE]` `gfx_pc.c:2362` multiplies every 3D vertex's `x` by
> `(4/3) / (W/H)` at `gfx_pc.c:2476`**, which is `0.7130` at the mandated geometry; dividing each
> arm by its own `a` gives `0.987` / `0.963` / `0.915`, and the depth-free `MODE=2` arm gives
> **`0.986`**.
>
> **NOTHING IS PATCHED. The count of wrong filed fixes is five, and four of them looked this good.
> THIS SHEET EXISTS TO KILL THE DIAGNOSIS, NOT TO DRESS IT.**

---

## §0 — THE GATE, AND THE HALF MOVES AGAIN

`[ARITHMETIC]` `gfx_pc.c:424-447`, `configWidescreen=0`: `ge_scale() = min(W/320, H/240)`, play
area `320 * ge_scale` px, eye half `160 * ge_scale`. **`312` §2.1 confirmed this three ways** — the
tool's detected play area, the letterbox/pillarbox measured off the BMP, and the backend's own
`[getv] VIEWPORT n64 ... ours: w=` line, which read `912.667` / `800` / `533.333`.

| arm | `GETV_WIDESCREEN` | window | `ge_scale` | **eye half px** | **`a = (4/3)/(W/H)`** |
|---|---|---|---:|---:|---:|
| control (`311` §2 `sep64`) | `0` | `2560x1369` | `5.7042` | `912.67` | `0.7130` |
| **arm 1** | **`1`** | `2560x1369` | **see §2.1** | **read it off the log** | **identity by design** |
| **arm 2** | `0` | `1600x1200` | `5.0000` | **`800.00`** | **`1.0000`** |
| **arm 3** | `0` | `1280x684` | `2.8500` | **`456.00`** | **`0.7130`** |

**►►►► ARM 1's HALF IS NOT PREDICTED HERE AND THAT IS DELIBERATE.** `GETV_WIDESCREEN=1` changes
`ge_effective_native_width()`, so it changes `ge_scale()`, the play area, the pillarbox AND the
aspect expression together. **READ THE HALF OFF THAT ARM'S OWN `[getv] VIEWPORT n64` LINE AND OFF
THE TOOL'S `eye half`, AND CHECK THE TWO AGREE BEFORE SCORING IT.** Guessing it is how a sheet
scores a number it cannot express (`310` §3, `H18`).

**DO NOT QUOTE THE LOG'S `= +/-N px at the mandated 2560x1369 geometry` FIGURE ON ANY ARM OF THIS
SHEET.** `GE_STEREO_MANDATED_PLAYAREA_PX` is the constant `1825.333f` (`stereo.c:450`) and
`geStereoPredict()` multiplies by it unconditionally. **The FRACTION is what every gate uses.**

**A GRAB IS ADMISSIBLE ONLY IF `|predicted px| <= 450`** on that arm's own half
(`RUN-SHEET-307` §2.0, `RUN-SHEET-311` §0, `310` §7.2).

---

## §1 — THE SCORER. **`RUN-SHEET-312` §1's `Score-Arm2`, PLUS AN `H22` STALENESS COLUMN**

**►►►► `312` §3 FOUND THAT THE SCORER PAIRS A GRAB WITH THE LAST PREDICTION BEFORE IT AND CANNOT
SEE HOW OLD THAT IS** — on both `MODE=2` arms ever run, every grab in the run was scored against
ONE line, up to 150,254 log lines stale. **This scorer prints the gap. It does not yet refuse on
it, because the durable refusal belongs in the tool (`H22`) and this sheet does not build.**

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
function Score-Arm3([string]$arm, [string]$log, [string]$grabs, [string]$out, [double]$half) {
  "START $((Get-Date).ToString('o')) arm=$arm log=$log half=$half" | Set-Content -Encoding ascii $out
  if (-not (Test-Path $log)) { "MISSING $log -- ARM SKIPPED" | Add-Content $out; return }
  $lines = Get-Content $log
  $bmps  = @(Get-ChildItem "$grabs\*.bmp" -ErrorAction SilentlyContinue | Sort-Object Name)
  $preds = @($lines | Select-String -Pattern 'PREDICTION: disparity =').Count
  $dls   = @($lines | Select-String -Pattern '\[getv\]\[dlgrab\] frame \d+ ').Count
  $tan   = ($lines | Select-String -Pattern 'tanR-tanL=([0-9.]+)' | Select-Object -First 1)
  $vp    = ($lines | Select-String -Pattern 'VIEWPORT n64:.*ours: x=\S+ y=\S+ w=(\S+)' | Select-Object -First 1)
  "ARM $arm grabs=$($bmps.Count) preds=$preds dls=$dls half=$half tanw=$(if ($tan) { $tan.Matches.Groups[1].Value } else { 'NONE' }) backend_eye_w=$(if ($vp) { $vp.Matches.Groups[1].Value } else { 'NONE' })" | Add-Content $out
  foreach ($g in $bmps) {
    $fr = [regex]::Match($g.Name,'(\d+)\.bmp$').Groups[1].Value
    $ln = ($lines | Select-String -Pattern "\[getv\]\[dlgrab\] frame $fr " | Select-Object -First 1).LineNumber
    if (-not $ln) { "=== $arm frame $fr   NO DLGRAB LINE -- INADMISSIBLE (279 s2) ===" | Add-Content $out; continue }
    $m = ($lines[0..($ln-1)] | Select-String -Pattern 'PREDICTION: disparity = (-?[0-9.]+) x eye_width' | Select-Object -Last 1)
    $d = ($lines[0..($ln-1)] | Select-String -Pattern 'MEASURED centre depth D=([0-9.]+)' | Select-Object -Last 1)
    if (-not $m) { "=== $arm frame $fr   NO PREDICTION LINE BEFORE THIS GRAB -- INADMISSIBLE ===" | Add-Content $out; continue }
    $frac = [double]$m.Matches.Groups[1].Value
    $dep  = if ($d) { $d.Matches.Groups[1].Value } else { "NONE" }
    $gap  = $ln - $m.LineNumber
    $px   = $frac * $half
    if ([Math]::Abs($px) -gt 450) {
      "=== $arm frame $fr   D $dep   predicted $([Math]::Round($px,2)) px   INADMISSIBLE -- |px| > 450 (H18, RUN-SHEET-307 s2.0). NOT SCORED, NOT AN OUTLIER. ===" | Add-Content $out
      continue
    }
    $flag = if ($gap -gt 3000) { "  >>>> H22 WARNING: THE PREDICTION IS $gap LOG LINES OLD. TREAT THIS GRAB AS UNPAIRED (312 s3)." } else { "" }
    "=== $arm frame $fr   predicted-frac $frac   D $dep   predicted $([Math]::Round($px,2)) px   pred-gap $gap lines$flag ===" | Add-Content $out
    py ..\tools\stereo_disparity.py $g.FullName --predicted-frac $frac --search 500 *>&1 | Add-Content $out
  }
  "DONE $((Get-Date).ToString('o'))" | Add-Content $out
  Select-String -Path $out -Pattern '^ARM |^=== |^play area |^eye half |^dx |^confidence |^PREDICTED |^VERDICT|CANNOT ANSWER'
}
```

---

## §2 — **THE THREE ARMS.** `LOW`, no build, ~8 minutes

**THE QUESTION: is the under-read `a = (4/3) / (W/H)`, applied at `gfx_pc.c:2476`?**

**THE COMMON PREAMBLE — paste once, then each arm below it:**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
if (-not (Test-Path .\EXPECTED-EXE-303.txt)) { throw "EXPECTED-EXE-303.txt is missing -- run RUN-SHEET-303 section 2c after the build, before any arm." }
$want = (Get-Content .\EXPECTED-EXE-303.txt).Trim()
$got  = "$((Get-FileHash .\goldeneye.exe -Algorithm SHA256).Hash) $((Get-Item .\goldeneye.exe).Length)"
if ($want -ne $got) { throw "BINARY MISMATCH -- this is NOT the 303 build. want [$want] got [$got]" }
foreach ($w in @("wide1","w1600x1200","w1280x684")) {
  $log = ".\run_313_$w.log"
  if (Test-Path $log) { throw "$log EXISTS -- rename it or pick a new name (H5)." }
}
$env:GETV_SLOTFREE              = "1"
$env:GETV_VSYNC                 = "1"
$env:GETV_FPS                   = "panel"
$env:GETV_SIMHZ                 = "query"
$env:GETV_SIMDIV                = "1"
$env:GETV_ROOMSCISSOR           = "1"
$env:GETV_STAGE                 = "29"
$env:GETV_DIFFICULTY            = "0"
$env:GETV_STEREO                = "1"
$env:GETV_STEREO_MODE           = "1"
$env:GETV_STEREO_OFFSET         = "64"
$env:GETV_STEREO_PROBE          = "60"
$env:GETV_STEREO_VIEWRESTORE    = "1"
$env:GETV_STEREO_PAIRGUARD      = "0"
$env:GETV_STEREO_REBUILD        = "1"
$env:GETV_STEREO_REBUILD_REPORT = "1"
$env:GETV_STEREO_REBUILD_VIEWER = "1"
```

**►►►► AND THE WALK IS PART OF THE INSTRUMENT NOW, BECAUSE OF `H22`: STOP MOVING, COUNT TO TWO,
THEN TAKE THE GRAB.** `312` §2.3 measured the cost of walking through a grab — the two grabs whose
`D` was drifting fastest are the two worst points on their arms. **Same flat wall as `310` §7,
`D` from about `200` out to about `550`, four or five grabs, STATIONARY at each one.**

**ARM 1 OF 3 — the knob that makes the expression the identity, by its own comment
(`gfx_pc.c:410-423`):**

```powershell
$env:GETV_WIDESCREEN = "1"; $env:GETV_ARM = "wide1"; $env:GETV_WINDOW = "2560x1369"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_313_wide1.log 2>&1
New-Item -ItemType Directory -Force -Path .\grabs_313_wide1 | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_313_wide1 -Force -ErrorAction SilentlyContinue
Select-String -Path run_313_wide1.log -Pattern 'separation=' | Select-Object -First 1
Select-String -Path run_313_wide1.log -Pattern 'tanR-tanL=' | Select-Object -First 1
Select-String -Path run_313_wide1.log -Pattern 'VIEWPORT n64' | Select-Object -First 2
Get-ChildItem .\grabs_313_wide1 | Measure-Object | Select-Object -ExpandProperty Count
```

**ARM 2 OF 3 — a `4:3` window, widescreen OFF: `a` is `1.0000` exactly:**

```powershell
$env:GETV_WIDESCREEN = "0"; $env:GETV_ARM = "w1600x1200"; $env:GETV_WINDOW = "1600x1200"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_313_w1600x1200.log 2>&1
New-Item -ItemType Directory -Force -Path .\grabs_313_w1600x1200 | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_313_w1600x1200 -Force -ErrorAction SilentlyContinue
Select-String -Path run_313_w1600x1200.log -Pattern 'separation=' | Select-Object -First 1
Select-String -Path run_313_w1600x1200.log -Pattern 'tanR-tanL=' | Select-Object -First 1
Select-String -Path run_313_w1600x1200.log -Pattern 'VIEWPORT n64' | Select-Object -First 2
Get-ChildItem .\grabs_313_w1600x1200 | Measure-Object | Select-Object -ExpandProperty Count
```

**ARM 3 OF 3 — the CONTROL'S ASPECT at half the pixels: `a` is unchanged, so nothing may move:**

```powershell
$env:GETV_WIDESCREEN = "0"; $env:GETV_ARM = "w1280x684"; $env:GETV_WINDOW = "1280x684"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_313_w1280x684.log 2>&1
New-Item -ItemType Directory -Force -Path .\grabs_313_w1280x684 | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_313_w1280x684 -Force -ErrorAction SilentlyContinue
Select-String -Path run_313_w1280x684.log -Pattern 'separation=' | Select-Object -First 1
Select-String -Path run_313_w1280x684.log -Pattern 'tanR-tanL=' | Select-Object -First 1
Select-String -Path run_313_w1280x684.log -Pattern 'VIEWPORT n64' | Select-Object -First 2
Get-ChildItem .\grabs_313_w1280x684 | Measure-Object | Select-Object -ExpandProperty Count
```

**SCORE ALL THREE — arm 1's half is READ, not assumed. Run its `Select-String` above first, take
the `w=` figure from `[getv] VIEWPORT n64`, and put THAT number in the marked slot. `<` IS A
RESERVED OPERATOR IN POWERSHELL** (`00-STATE` §7a) — **the line below carries a real number that
must be replaced with the measured one before it runs:**

```powershell
Score-Arm3 "wide1"      ".\run_313_wide1.log"      ".\grabs_313_wide1"      ".\disp_313_wide1.txt"      1280.00
Score-Arm3 "w1600x1200" ".\run_313_w1600x1200.log" ".\grabs_313_w1600x1200" ".\disp_313_w1600x1200.txt"  800.00
Score-Arm3 "w1280x684"  ".\run_313_w1280x684.log"  ".\grabs_313_w1280x684"  ".\disp_313_w1280x684.txt"   456.00
```

**►►►► THE `1280.00` ON THE FIRST LINE IS A PLACEHOLDER WITH A PLAUSIBLE VALUE IN IT — it is what
a uniform-fill `GETV_WIDESCREEN=1` gives at `2560` wide — AND IT MUST BE REPLACED WITH THE `w=`
FIGURE THAT ARM ACTUALLY PRINTS.** If the two differ, the printed one wins and the difference is
itself worth writing down. The tool derives its own half from the image and is unaffected either
way; **only the `450` admissibility figure and nothing else depends on this number.**

### 2.1 — PRE-REGISTERED. **`[PREDICTION]`, AND LABELLED AS ONE** (`309` §7.1)

| | `[PREDICTION]` | what it means |
|---|---|---|
| **3a** | every arm reads `separation=64.000 FULL`, `mode=1`, and **`tanR-tanL = 1.368534` UNCHANGED**, arm 1 included | `tanw` comes from `fovy` and the N64 `320x180` view. **If `GETV_WIDESCREEN=1` moves `tanw`, arm 1 is confounded and only arms 2 and 3 answer** |
| **3b** | **ARM 2 READS `~1.00`** | `a = 1.0000` at `4:3`. **This is the single cleanest test of the whole diagnosis: same knobs, same code path, one number changed, and the under-read must VANISH** |
| **3c** | **ARM 3 READS `~0.70`, i.e. IT DOES NOT MOVE FROM THE CONTROL** | `a` is unchanged at `0.7130`. **If the ratio moves when the aspect does not, the factor is not the aspect and `312` §2.2 is wrong** |
| **3d** | **ARM 1 READS `~1.00`** | `gfx_pc.c:410-423` says the expression becomes the identity. **If arm 1 stays at `~0.70`, the knob does not reach this path and the diagnosis is wrong or incomplete** |
| **3e** | **IF `3b` AND `3c` BOTH LAND, `H19` IS LOCATED AND CLOSABLE** — and the fix is a DESIGN decision (a knob, or the prediction learning the term), **not this sheet's** | `MEASURE BEFORE YOU PATCH` has been paid for; **the patch is still a separate, argued step** |
| **3f** | **ANY OTHER PATTERN** | write it down as measured, do NOT curve-fit a fourth candidate, and say which of `3b`/`3c`/`3d` failed |

**THE MEASUREMENT TO REPORT: three medians and their spreads, each against its own arm's
`[PREDICTION]`, plus the control (`311` §2's `sep64` median `0.7036` at `2560x1369`), plus each
arm's `pred-gap` column so `H22` cannot hide inside the answer.**

---

## §3 — WHAT NEEDS A PERSON

- **§2's three arms.** `LOW`, ~8 minutes, no build. **Same wall, stationary at each grab.**
- **`RUN-SHEET-312` §5's `H18` splice**, if it has still not been run. `LOW`, offline.
- **The commit**, this session's own paths only, explicit `git add --` path lists, `git commit -F`.
  **Do NOT use `COMMIT-NOW.cmd`** (`307` §5).
- **The 57-file username scrub under `repo/docs` is STILL not this session's.** Leave it alone.
- **`E3` (FC3/FC4) is CLOSED.** Do not re-ask.

## §4 — AND THE STANDING ONE

**`V3` / `258` STAGE 6 STILL CANNOT CLOSE** (`310` §9.1). **But for the first time it has a named
route: if `3b` lands, the `+/-5 px` gate is passable either by a knob or by teaching
`geStereoPredict()` the aspect term.** `312` §7. **It is not closed by predicting that.**
