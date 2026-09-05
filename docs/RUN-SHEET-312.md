# `RUN-SHEET-312` — **IS THE `0.705` THE WINDOW GEOMETRY?** ONE KNOB, TWO SHORT RUNS, NO BUILD

> **STATE ON ENTRY (`311` §3):** `RUN-SHEET-311` §2 and §3 are both worn. **The ratio does NOT move
> with separation** (medians `0.6907` / `0.7036` / `0.6960` at `sep` `32` / `64` / `128`, a 4-fold
> range) — so it is a pure scale, `2b` lands and `2d` does not fire. **AND `MODE=2` READ `0.7075`,
> NOT `1.00`** — seven grabs, `dx = -60` on every one. `MODE=2` never touches the view matrix
> (`stereo.c:355-357` returns 0), so **the loss is COMMON TO BOTH PATHS and `A` — "the applied
> separation is short" — IS RETRACTED AS THE LOCATION.** `00-STATE` §4.
>
> **NOTHING HERE PATCHES ANYTHING.** The count of wrong filed fixes is five. This sheet moves ONE
> knob that neither the frustum nor the separation touches, and reads the ratio.

---

## §0 — THE ADMISSIBILITY GATE, AND **IT IS NOT `912` ANY MORE**

**►►►► `RUN-SHEET-311` §1's SCORER HARD-CODES `$frac * 912.0`, AND THIS SHEET CHANGES THE WINDOW,
WHICH CHANGES THE HALF.** `[ARITHMETIC]` from `gfx_pc.c:424-447` with `configWidescreen=0`:
`ge_scale() = min(W/320, H/240)`, the play area is `320 * ge_scale` px and the eye half is
`160 * ge_scale`.

| `GETV_WINDOW` | `W/320` | `H/240` | `ge_scale` | play area px | **eye half px** |
|---|---:|---:|---:|---:|---:|
| `2560x1369` (`311`'s, the control) | `8.000` | `5.7042` | `5.7042` | `1825.33` | **`912.67`** |
| **`1600x1369`** | `5.000` | `5.7042` | `5.0000` | `1600.00` | **`800.00`** |
| **`2560x800`** | `8.000` | `3.3333` | `3.3333` | `1066.67` | **`533.33`** |

**THE TOOL DERIVES ITS OWN HALF FROM THE IMAGE (`stereo_disparity.py:59, 82`) AND IS UNAFFECTED —
only the PowerShell gate figure moves.**

**►►►►►►►► AND ONE MORE THING MOVES, AND IT IS IN THE LOG RATHER THAN IN THE TOOL: THE GAME'S OWN
`= +/-N px at the mandated 2560x1369 geometry` LINE WILL BE WRONG ON BOTH ARMS.**
`GE_STEREO_MANDATED_PLAYAREA_PX` is the constant `1825.333f` at `stereo.c:450` and
`geStereoPredict()` multiplies by half of it **unconditionally** — it does not know the window
changed. `[ARITHMETIC]` on arm 1 that line will over-state by `912.67/800 = 1.141x` and on arm 2 by
`912.67/533.33 = 1.712x`. **The line is labelled a convenience and it is; the FRACTION
(`disparity = +/-0.NNNNNN x eye_width`) is what every gate uses and it is correct on every arm.**
**READ THE FRACTION, AND READ THE TOOL'S OWN `eye half` LINE. DO NOT QUOTE THE LOG'S px FIGURE ON
EITHER ARM OF THIS SHEET.** `239`: a knob validated at one geometry is not a setting — and this is
the first sheet that leaves that geometry. §1's scorer therefore takes the half as a parameter.
**A GRAB IS ADMISSIBLE ONLY IF `|predicted px| <= 450`**, on that arm's own half
(`RUN-SHEET-307` §2.0, `RUN-SHEET-311` §0, `310` §7.2).

---

## §1 — THE SCORER, WITH THE HALF AS AN ARGUMENT. **USE THIS ONE, NOT `RUN-SHEET-311` §1**

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
function Score-Arm2([string]$arm, [string]$log, [string]$grabs, [string]$out, [double]$half) {
  "START $((Get-Date).ToString('o')) arm=$arm log=$log half=$half" | Set-Content -Encoding ascii $out
  if (-not (Test-Path $log)) { "MISSING $log -- ARM SKIPPED" | Add-Content $out; return }
  $lines = Get-Content $log
  $bmps  = @(Get-ChildItem "$grabs\*.bmp" -ErrorAction SilentlyContinue | Sort-Object Name)
  $preds = @($lines | Select-String -Pattern 'PREDICTION: disparity =').Count
  $dls   = @($lines | Select-String -Pattern '\[getv\]\[dlgrab\] frame \d+ ').Count
  $tan   = ($lines | Select-String -Pattern 'tanR-tanL=([0-9.]+)' | Select-Object -First 1)
  "ARM $arm grabs=$($bmps.Count) preds=$preds dls=$dls half=$half tanw=$(if ($tan) { $tan.Matches.Groups[1].Value } else { 'NONE' })" | Add-Content $out
  foreach ($g in $bmps) {
    $fr = [regex]::Match($g.Name,'(\d+)\.bmp$').Groups[1].Value
    $ln = ($lines | Select-String -Pattern "\[getv\]\[dlgrab\] frame $fr " | Select-Object -First 1).LineNumber
    if (-not $ln) { "=== $arm frame $fr   NO DLGRAB LINE -- INADMISSIBLE (279 s2) ===" | Add-Content $out; continue }
    $m = ($lines[0..($ln-1)] | Select-String -Pattern 'PREDICTION: disparity = (-?[0-9.]+) x eye_width' | Select-Object -Last 1)
    $d = ($lines[0..($ln-1)] | Select-String -Pattern 'MEASURED centre depth D=([0-9.]+)' | Select-Object -Last 1)
    if (-not $m) { "=== $arm frame $fr   NO PREDICTION LINE BEFORE THIS GRAB -- INADMISSIBLE ===" | Add-Content $out; continue }
    $frac = [double]$m.Matches.Groups[1].Value
    $dep  = if ($d) { $d.Matches.Groups[1].Value } else { "NONE" }
    $px   = $frac * $half
    if ([Math]::Abs($px) -gt 450) {
      "=== $arm frame $fr   D $dep   predicted $([Math]::Round($px,2)) px   INADMISSIBLE -- |px| > 450 (H18, RUN-SHEET-307 s2.0). NOT SCORED, NOT AN OUTLIER. ===" | Add-Content $out
      continue
    }
    "=== $arm frame $fr   predicted-frac $frac   D $dep   predicted $([Math]::Round($px,2)) px ===" | Add-Content $out
    py ..\tools\stereo_disparity.py $g.FullName --predicted-frac $frac --search 500 *>&1 | Add-Content $out
  }
  "DONE $((Get-Date).ToString('o'))" | Add-Content $out
  Select-String -Path $out -Pattern '^ARM |^=== |^play area |^eye half |^dx |^confidence |^PREDICTED |^VERDICT|CANNOT ANSWER'
}
```

**The `$m` null guard `RUN-SHEET-311` §1 did not have is in this one** (`311` §2 flagged it before the
run; it did not fire, and it costs one line to make sure it never does). **The `tanw` and the
tool's own `play area` / `eye half` lines are now echoed, because this sheet's whole subject is
whether those two agree.**

---

## §2 — **THE WINDOW SWEEP. THE PRIMARY TEST.** `LOW`, no build, ~5 minutes

**THE QUESTION: does the `0.705` track the WINDOW GEOMETRY, or is it a constant?**

**`311` §3 NARROWED IT TO A HORIZONTAL MAPPING, NOT A SEPARATION.** `[ARITHMETIC]` under
`MODE=2` the shift is `s = -(sep*0.5)/1000` in TANGENT units and the measured NDC fraction is
`s/tR`, while the prediction is `-sep/(D*2tR)` — **`tR` cancels on BOTH sides**, so at `D = 1000`
the ratio is `1.000` for any frustum. **It read `0.7075`.** What is left in that expression is the
step the prediction does NOT own: **NDC fraction -> PIXELS.** The tool multiplies by a half it
DERIVES from the image (`912`); the renderer multiplies by whatever it actually uses. `310` §8.1
and §0 item 6 confirmed that the play area IS `1825` px wide and each half IS `912` px — **they
never measured what NDC `+/-1` spans inside that half, and that is the gap.**

**AND COMBINING THE TWO ARMS RETIRES `A` ARITHMETICALLY:** `[ARITHMETIC]` `MODE=1`'s ratio is
`(sep_applied / sep_requested) * (half_true / 912)` and `MODE=2`'s is `(half_true / 912)` alone.
`0.7022 / 0.7075 = 0.992`. **THE SEPARATION IS APPLIED IN FULL, TO BETTER THAN 1%.**

**THIS SHEET MOVES THE ONE KNOB THAT CHANGES THE PIXEL GEOMETRY AND NOTHING ELSE.**
`GETV_WINDOW` does not touch `fovy`, the N64 `320x180` view, `tanw`, or the separation.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
if (-not (Test-Path .\EXPECTED-EXE-303.txt)) { throw "EXPECTED-EXE-303.txt is missing -- run RUN-SHEET-303 section 2c after the build, before any arm." }
$want = (Get-Content .\EXPECTED-EXE-303.txt).Trim()
$got  = "$((Get-FileHash .\goldeneye.exe -Algorithm SHA256).Hash) $((Get-Item .\goldeneye.exe).Length)"
if ($want -ne $got) { throw "BINARY MISMATCH -- this is NOT the 303 build. want [$want] got [$got]" }
foreach ($w in @("w1600","w2560h800")) {
  $log = ".\run_312_$w.log"
  if (Test-Path $log) { throw "$log EXISTS -- rename it or pick a new name (H5)." }
}
$env:GETV_SLOTFREE              = "1"
$env:GETV_VSYNC                 = "1"
$env:GETV_FPS                   = "panel"
$env:GETV_SIMHZ                 = "query"
$env:GETV_SIMDIV                = "1"
$env:GETV_WIDESCREEN            = "0"
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

**`sep 64` for both arms, because `311` §2 measured it as the best-quantized of the three
(spread `0.0133` over six grabs against `0.0305` and `0.0485`).** Same flat wall as `310` §7 and
`311` §2; **same walk, `D` from about `200` out to about `550`, four or five grabs.**

**ARM 1 OF 2 — the WIDTH becomes the limiting axis:**

```powershell
$env:GETV_ARM = "w1600"; $env:GETV_WINDOW = "1600x1369"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_312_w1600.log 2>&1
New-Item -ItemType Directory -Force -Path .\grabs_312_w1600 | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_312_w1600 -Force -ErrorAction SilentlyContinue
Select-String -Path run_312_w1600.log -Pattern 'separation=' | Select-Object -First 1
Select-String -Path run_312_w1600.log -Pattern 'tanR-tanL=' | Select-Object -First 1
Get-ChildItem .\grabs_312_w1600 | Measure-Object | Select-Object -ExpandProperty Count
```

**ARM 2 OF 2 — the height is squeezed instead, same width as the control:**

```powershell
$env:GETV_ARM = "w2560h800"; $env:GETV_WINDOW = "2560x800"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_312_w2560h800.log 2>&1
New-Item -ItemType Directory -Force -Path .\grabs_312_w2560h800 | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_312_w2560h800 -Force -ErrorAction SilentlyContinue
Select-String -Path run_312_w2560h800.log -Pattern 'separation=' | Select-Object -First 1
Select-String -Path run_312_w2560h800.log -Pattern 'tanR-tanL=' | Select-Object -First 1
Get-ChildItem .\grabs_312_w2560h800 | Measure-Object | Select-Object -ExpandProperty Count
```

**SCORE BOTH — and the half is different for each, which is the whole point of §0:**

```powershell
Score-Arm2 "w1600"     ".\run_312_w1600.log"     ".\grabs_312_w1600"     ".\disp_312_w1600.txt"     800.00
Score-Arm2 "w2560h800" ".\run_312_w2560h800.log" ".\grabs_312_w2560h800" ".\disp_312_w2560h800.txt" 533.33
```

### 2.1 — PRE-REGISTERED. **`[PREDICTION]`, AND LABELLED AS ONE** (`309` §7.1)

| | `[PREDICTION]` | what it means |
|---|---|---|
| **2a** | every arm's log reads `separation=64.000 FULL` and `mode=1`, and **`tanR-tanL=1.368534` UNCHANGED on both arms** | `tanw` comes from `fovy` and the N64 `320x180` view, not from the window. **If `tanw` moves with `GETV_WINDOW`, stop — that is a bigger finding than this sheet** |
| **2b** | the tool's own `play area` line reads **`1600`** on arm 1 and **`1066`** on arm 2, and `eye half` reads **`800`** and **`533`** | the derived half is the measurement `311` never varied |
| **2c** | **THE TWO ARMS SEPARATE THREE ANSWERS, AND THEY DISAGREE IN OPPOSITE DIRECTIONS.** See the table below | that is why there are two arms and not one |
| **2d** | **IF THE RATIO STAYS `~0.70` ON BOTH ARMS** | the factor is geometry-INDEPENDENT and baked in somewhere `GETV_WINDOW` cannot reach. **Both candidates die, and they die cheaply** |
| **2e** | anything else — a ratio that moves but onto neither column | a partial dependence: **file it as a new hole, do NOT curve-fit it** |

**THE TWO CANDIDATE SCALES, PRE-REGISTERED PER ARM.** `[HYPOTHESIS]` **NEITHER IS FILED and neither
names a line** — they are two arithmetically distinct ways the horizontal scale could be picked,
written down in advance so the run can kill at least one:

| arm | `ge_scale` = `min(W/320, H/240)` | **`C1`: an EYE-width scale**, `min((W/2)/320, H/240) / ge_scale` | **`C2`: a WIDTH-derived scale**, `ge_scale / (W/320)` |
|---|---:|---:|---:|
| control `2560x1369` (`311` §2 `sep64`, **measured `0.7036`**) | `5.7042` | **`0.7012`** | **`0.7130`** |
| **arm 1 `1600x1369`** | `5.0000` | **`0.5000`** | **`1.0000`** |
| **arm 2 `2560x800`** | `3.3333` | **`1.0000`** | **`0.4167`** |

**BOTH CANDIDATES FIT THE CONTROL INSIDE `310` §7's 2% ERROR BAR — AND THEY PREDICT OPPOSITE
RESULTS ON BOTH ARMS.** `C1` says arm 1 halves and arm 2 goes clean; `C2` says the reverse. **Two
short runs decide between three outcomes, and one of the three is "neither".**

**THE MEASUREMENT TO REPORT: two medians and their spreads, each against its own arm's
`[PREDICTION]` — plus the control, `311` §2's `sep64` median `0.7036` at `2560x1369`.**

---

## §2b — **THE `MODE=2` DEPTH-CONSTANCY CHECK. IT IS OWED, AND IT IS IN A SHEET THIS TIME**

**►►►► THIS IS `311` §7.2's DEFECT REPAIRED, NOT A NEW IDEA.** The check was described in CHAT
during `311` and never written into `RUN-SHEET-311` §3, so all seven `mode2` grabs landed at
`D = 1005.73` and **it did not happen** (`308` §0, `00-STATE` §4). **It is written here so that it
exists.** `LOW`, no build, ~3 minutes, and it runs AFTER §2's two arms, at the CONTROL geometry.

**THE QUESTION, AND IT IS A DIFFERENT ONE FROM §2's.** `[ARITHMETIC]` under `MODE=2` the frustum
shift is `s = -(sep * 0.5) / GE_STEREO_B1_DEPTH` in TANGENT units (`stereo.c:284-295`,
`GE_STEREO_B1_DEPTH 1000.0f`) — **it does not contain `D` at all.** So the drawn disparity is a
CONSTANT in pixels, at every depth, and `geStereoPredict()`'s own `1/D` prediction is NOT: the
predicted fraction falls as the owner walks back while the measured `dx` must not move.

> **`[PREDICTION] 2b-i` — `dx` IS CONSTANT ACROSS ALL GRABS, to within +/-2 px**, while `D` moves
> over at least a 3-fold range. **That is the `B1` signature and nothing else has it.**
> **`[PREDICTION] 2b-ii` — the RATIO therefore is NOT constant**: it reads `~0.7075` only where
> `D ~= 1000`, and it scales as `D / 1000` elsewhere. **DO NOT SCORE THIS ARM ON THE RATIO AND DO
> NOT ADD IT TO ANY `MODE=1` POOL.** `311` §5's `0.7075` is the `D ~= 1000` figure and it is the
> only depth at which the two are comparable.
> **`[PREDICTION] 2b-iii` — IF `dx` MOVES WITH `D` ON THIS ARM, `MODE=2` IS NOT DOING WHAT
> `stereo.c:284-295` SAYS**, and that is a bigger finding than either sheet: it would mean `311`
> §5's seven identical grabs were identical because the owner stood still, not because the mode is
> depth-free, and `311` §6.1's retraction of `A` — which divides the two arms — would need re-deriving.

**SAME FLAT WALL, SAME WALK, `D` FROM ABOUT `250` OUT TO ABOUT `1000`, FIVE GRABS SPREAD OVER IT —
NOT FIVE GRABS AT ONE SPOT. THAT IS THE ENTIRE POINT OF THIS ARM.**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
if (-not (Test-Path .\EXPECTED-EXE-303.txt)) { throw "EXPECTED-EXE-303.txt is missing -- run RUN-SHEET-303 section 2c after the build, before any arm." }
$want = (Get-Content .\EXPECTED-EXE-303.txt).Trim()
$got  = "$((Get-FileHash .\goldeneye.exe -Algorithm SHA256).Hash) $((Get-Item .\goldeneye.exe).Length)"
if ($want -ne $got) { throw "BINARY MISMATCH -- this is NOT the 303 build. want [$want] got [$got]" }
if (Test-Path .\run_312_mode2depth.log) { throw "run_312_mode2depth.log EXISTS -- rename it or pick a new name (H5)." }
$env:GETV_SLOTFREE              = "1"
$env:GETV_VSYNC                 = "1"
$env:GETV_FPS                   = "panel"
$env:GETV_SIMHZ                 = "query"
$env:GETV_SIMDIV                = "1"
$env:GETV_WIDESCREEN            = "0"
$env:GETV_ROOMSCISSOR           = "1"
$env:GETV_STAGE                 = "29"
$env:GETV_DIFFICULTY            = "0"
$env:GETV_STEREO                = "1"
$env:GETV_STEREO_MODE           = "2"
$env:GETV_STEREO_OFFSET         = "128"
$env:GETV_STEREO_PROBE          = "60"
$env:GETV_STEREO_VIEWRESTORE    = "1"
$env:GETV_STEREO_PAIRGUARD      = "0"
$env:GETV_STEREO_REBUILD        = "1"
$env:GETV_STEREO_REBUILD_REPORT = "1"
$env:GETV_STEREO_REBUILD_VIEWER = "1"
$env:GETV_ARM                   = "mode2depth"
$env:GETV_WINDOW                = "2560x1369"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_312_mode2depth.log 2>&1
New-Item -ItemType Directory -Force -Path .\grabs_312_mode2depth | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_312_mode2depth -Force -ErrorAction SilentlyContinue
Select-String -Path run_312_mode2depth.log -Pattern 'mode=2' | Select-Object -First 1
Select-String -Path run_312_mode2depth.log -Pattern 'tanR-tanL=' | Select-Object -First 1
Get-ChildItem .\grabs_312_mode2depth | Measure-Object | Select-Object -ExpandProperty Count
```

**SCORE IT WITH §1's `Score-Arm2`, AT THE CONTROL HALF — and read `dx` against `D`, NOT the ratio:**

```powershell
Score-Arm2 "mode2depth" ".\run_312_mode2depth.log" ".\grabs_312_mode2depth" ".\disp_312_mode2depth.txt" 912.67
Select-String -Path .\disp_312_mode2depth.txt -Pattern '^=== |^dx '
```

**GATE `2b-0`, AND IT IS CHECKED BEFORE ANY OF THE ABOVE IS READ:** the log must read
`mode=2 (PROJECTION-ONLY -- B1 REPRODUCED ON PURPOSE)`, the horizontal tangents must both be
shifted by exactly `(128 * 0.5) / 1000 = 0.064000`, and **`tanR-tanL` must be UNCHANGED at
`1.368534`** (`311` §5). If the mode did not take, the arm answers nothing.

**AND THE `D` SPREAD IS ITSELF A GATE:** `[MEASURED]` `311` §3 delivered `max(D) - min(D) = 0.00`.
**If this arm's `D` values do not span at least a factor of 2, THE CHECK HAS NOT HAPPENED AGAIN and
it must be said so out loud rather than scored.**

---

## §3 — WHAT NEEDS A PERSON

- **§2's two arms.** `LOW`, ~5 minutes, no build. **Same wall, same walk as `311` §2.**
- **§2b, the `MODE=2` depth-constancy check.** `LOW`, ~3 minutes, no build, AFTER §2. **It has been
  owed since `311` and it did not happen because it was in a transcript instead of a sheet
  (`311` §7.2, `308` §0). It is in §2b now.**
- **§5's `H18` splice**, and **only after the runs** — it edits a tool the runs depend on.
- **The commit** for whatever these produce, this session's own paths only, explicit `git add --`
  path lists, `git commit -F`. **Do NOT use `COMMIT-NOW.cmd`** (`307` §5).
- **The username scrub across 57 tracked files under `repo/docs` is STILL not this session's.**
  Leave it alone; do not sweep it into a commit.
- **`E3` (FC3/FC4) is CLOSED.** Do not re-ask.

## §4 — AND THE STANDING ONE

**`V3` / `258` STAGE 6 STILL CANNOT CLOSE** (`310` §9.1). `311` did not move it and neither does
this sheet. **What `311` changed is WHERE the `0.705` can live, not whether it is there.**
---

## §5 — **`H18`'s DURABLE FORM. THE TOOL REFUSES AN UNREACHABLE PREDICTION ITSELF.** `LOW`, no build

**►►►► RUN THIS ONLY AFTER §2 AND §2b HAVE BEEN SCORED.** It edits `stereo_disparity.py`, which is
the instrument those arms are read with; editing it first would put a changed tool under a measured
result for no reason.

**WHY IT IS OWED.** `H18` has been a line in a PowerShell gate since `307` §2.0 and **three
sessions have paid for it having no durable form** (`00-STATE` §4). `RUN-SHEET-310` §3 carried no
gate at all, so `S3d_2917` — **predicted `-503.85` px against the tool's own printed
`searched [-500..+500]`** — was scored rather than refused, and **it cleared the confidence floor
at `contrast 0.733`, higher than four of the six admissible grabs.** `308`'s floor asks whether a
peak is WELL DEFINED; `H18` asks whether the answer is **EXPRESSIBLE**. They are not substitutes
and the floor never could catch it.

**AND THIS SHEET IS THE REASON IT CANNOT STAY IN THE SHELL.** §0 changes the half three ways
(`912.67` / `800.00` / `533.33`). **A hard-coded `450` in a scorer is a constant validated at ONE
geometry** (`239`), and §1 already had to take the half as an argument. **The tool derives its own
half and its own searched range from the image, so the refusal belongs in the tool, and it is
bounded by `lo`/`hi` — the range REALLY searched, which the image edge sets — not by `--search` and
not by a number typed in a sheet.**

**►►►► THE SPLICE IS DONE IN BYTES BY `py`, NOT BY `Get-Content`/`-replace`/`Set-Content`**
(`308` §1.1, `00-STATE` §6): that file is **LF-only, UTF-8, no BOM** and carries `>` arrows and `§`
in ten comment lines, and a shell round-trip would produce ~293 spurious CRLF changes and ten
mangled comments in the diff of a small edit. **The block below anchors on the exact two lines,
refuses unless they match EXACTLY ONCE, refuses if the CRLF count would change, and refuses on a
second run.**

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\tools
@'
import io, sys
P = "stereo_disparity.py"
d = open(P, "rb").read()
if d.count(b"\r\n") != 0:
    print("REFUSED: file already contains CRLF; this is not the file this splice was written for.")
    sys.exit(2)
if b"H18: THE PREDICTION IS NOT REACHABLE" in d:
    print("REFUSED: the splice is already in. Nothing done.")
    sys.exit(3)
anchor = b"    if pred_frac is not None and pred_px is None:\n        pred_px = pred_frac * half\n"
n = d.count(anchor)
if n != 1:
    print("REFUSED: anchor matched %d times, expected exactly 1. Nothing written." % n)
    sys.exit(4)
add = (
b"    # H18, DURABLE FORM (312). A PREDICTION THE CORRELATOR CANNOT EXPRESS IS NOT A RESULT\n"
b"    # AND IT IS NOT AN OUTLIER -- IT IS INADMISSIBLE, AND THE TOOL SAYS SO ITSELF. Three\n"
b"    # sessions paid for this living only in a run sheet: RUN-SHEET-310 s3 carried no gate, so\n"
b"    # S3d_2917 was scored at a predicted -503.85 px against a searched [-500..+500] -- and it\n"
b"    # cleared the 308 confidence floor at contrast 0.733 while doing it. The floor asks whether\n"
b"    # a peak is WELL DEFINED; this asks whether the answer is EXPRESSIBLE, and they are not\n"
b"    # substitutes. The bound is the range REALLY searched (lo/hi, set by the image edge and\n"
b"    # printed above), NOT --search and NOT a constant in a shell: a sheet that moves the window\n"
b"    # moves the half (RUN-SHEET-312 s0: 912.67 / 800.00 / 533.33) and a typed 450 goes stale.\n"
b"    if pred_px is not None and (pred_px < lo or pred_px > hi):\n"
b"        print(\"CANNOT ANSWER: H18: THE PREDICTION IS NOT REACHABLE -- predicted %+.2f px \"\n"
b"              \"lies outside the range this correlator actually searched, [%+d..%+d]. This \"\n"
b"              \"grab is INADMISSIBLE: it is not an outlier, and it must not be scored, \"\n"
b"              \"quoted or pooled. Stand further from the wall, or lower the separation.\"\n"
b"              % (pred_px, lo, hi))\n"
b"        return 7\n"
)
out = d.replace(anchor, anchor + add)
if out.count(b"\r\n") != 0:
    print("REFUSED: the edit would introduce CRLF. Nothing written.")
    sys.exit(5)
open(P, "wb").write(out)
print("WROTE %s: %d -> %d bytes, CRLF=%d" % (P, len(d), len(out), out.count(b"\r\n")))
'@ | Set-Content -Encoding ascii .\_splice312.py
py .\_splice312.py
py .\stereo_disparity.py --selftest
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
git --no-optional-locks diff --stat -- getv/tools/stereo_disparity.py
git --no-optional-locks diff -- getv/tools/stereo_disparity.py
```

**THE EXPECTED READING, AND ALL THREE PARTS OF IT ARE THE GATE:**

- **`WROTE stereo_disparity.py: 17411 -> 18722 bytes, CRLF=0`** — `[MEASURED, BRIDGE]` `312`, the
  splice dry-run on a scratch COPY before it was written into this sheet. **Any other byte count
  means the file is not the one this anchor was cut against.**
- **`--selftest` still prints `selftest A: ... PASS`, `selftest B: ... peg detector FIRED  PASS`,
  `selftest C: ... PASS` — THREE checks, unchanged.** `306` §1's rule: **a gate's expected TEXT is
  part of the gate, so this splice adds NO selftest check.** The refusal it installs is on the
  prediction path, which `--selftest` does not travel. `[MEASURED, BRIDGE]` all three still PASS on
  the spliced copy, and the three lines are byte-identical to the unspliced tool's.
- `git diff --stat` reads **`1 file changed, 16 insertions(+)`** and **`0 deletions`**, on ONE path.
  **Any CRLF churn or any second file in that stat means the splice was not done in bytes — revert
  and stop.**

**►►►► `_splice312.py` IS A SCRATCH FILE AND IT IS NOT PART OF ANY COMMIT** — `goldeneye-native`
already carries two untracked scratch files from `309` (`_patch309.py`, `ladder_driver.py`) and
`307` §5's sixteen strays are why that matters. **The commit's path list is
`getv/tools/stereo_disparity.py` and nothing else.**

**AND WHAT THIS DOES NOT DO:** it does not change any number this project has measured. **Every
admissible grab in `310`, `311` and `312` has `|predicted px|` well inside `lo`/`hi`, so the
refusal is silent on all of them** — it fires only where a sheet would otherwise have to catch it,
and `RUN-SHEET-310` §3 is the proof that a sheet sometimes does not.
