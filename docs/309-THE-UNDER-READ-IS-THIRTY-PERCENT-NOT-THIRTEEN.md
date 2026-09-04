# `309` — **THE `S3b` UNDER-READ IS ~30%, NOT 10-13%, AND IT IS A RATIO, NOT A GROWTH.** THE `--patch` LADDER IS PRE-REGISTERED BEFORE THE INSTRUMENT IS TOUCHED

**OFFLINE, 2026-09-04. NOTHING BUILT, RUN IN-GAME, STAGED OR COMMITTED BY THIS SESSION.**
Binary untouched, `45756E5A…3F92`, 18,070,774 bytes.

> **THE BRIDGE CAVEAT, FIRST, BECAUSE IT IS `H7`.** Every number in §1 below was derived on the
> **BRIDGE's `python3 3.10.12`** from `disp_308_S3_all.txt`. They are **`[MEASURED, BRIDGE]` and
> are NOT quotable forward** until §3.1 re-wears them under PowerShell on the main PC. They are
> here so the owner pastes one block instead of three.

---

## §0 — WHAT THIS SESSION HAS ESTABLISHED SO FAR, IN ONE TABLE

| | |
|---|---|
| **1** | **`NEXT-SESSION-PROMPT-309` §0'S FIRST COMMAND PASSES. `308` IS IN AND BOTH TREES ARE CLEAN.** `[MEASURED]` 2026-09-04: `goldeneye-native` HEAD **`cbc4fdf`**, `git --no-optional-locks status --porcelain -- getv/tools` **empty**; `GoldenEyeVR` HEAD **`162b2b4`**, `-- repo/docs` **empty**. Three sessions of opening on a false sentence is broken |
| **2** | **AND THE DOCS REPO CARRIES TWO COMMITS WITH A BYTE-IDENTICAL SUBJECT LINE.** `98796e5` (`308`'s docs) and `162b2b4` (`NEXT-SESSION-PROMPT-309.md` + `COMMIT-MESSAGE-2026-09-04c.txt`, 127 insertions). The handover prompt landed under `308`'s message instead of one of its own. **Cosmetic, and it is exactly how a later session quotes the wrong commit** |
| **3** | **►►►►►►►► THE FIGURE EVERY DOCUMENT SINCE `307` REPEATS IS WRONG. "roughly a 10-13% proportional error" (`RUN-SHEET-308` §2, `308` §6.2, `NEXT-SESSION-PROMPT-309`) IS THE TWO ENDPOINTS, NOT THE CORPUS.** `[MEASURED, BRIDGE]` over all twelve scored `S3b` grabs: **median `30.8%`, mean `28.9%`, range `12.9%` to `44.9%`.** Ten of the twelve sit between **20.1%** and **34.8%**. The two grabs that produced "10-13%" are the two EXTREMES of the corpus and are the only two that behave differently from the other ten (§1.2) |
| **4** | **►►►►►►►► AND IT IS NOT "THE ERROR GROWS WITH DISPARITY MAGNITUDE". IT IS A NEARLY CONSTANT RATIO.** `measured / predicted` over the ten mid-band grabs (`20 < abs(pred) < 300`) is **`0.652` to `0.799`, median `0.692`** — the correlator reads about **seven tenths** of what the log predicts, at every magnitude in the band. **ABSOLUTE error grows because the ratio is constant; that is arithmetic, not a second finding** |
| **5** | **TEN OF TWELVE UNDER-READ. THE TWO THAT OVER-READ ARE THE LARGEST AND THE SMALLEST PREDICTION IN THE CORPUS** — `-405.60` reads `-458` (ratio `1.129`) and `-11.04` reads `-16` (ratio `1.449`). **The `V3` "pass" is the second of those.** A 4.96 px miss on an 11 px prediction is a 45% error that fits inside a 5 px gate |
| **6** | **THE BOUNDS ARE NOT A CONFOUND YET, AND THEY WILL BE.** All sixteen grabs were scored at `searched [-500 .. +500]`, identical on every one. **`--patch` moves `px0`/`px1`, which feed `lo`/`hi` in `measure()` — §2.3** |
| **7** | **PRE-REGISTERED, NOT YET RUN: §2's ladder and gates.** Nothing has been edited. `stereo_disparity.py` is untouched at `cbc4fdf` |

---

## §1 — THE BASELINE, MEASURED BEFORE ANYTHING IS PATCHED. `[MEASURED, BRIDGE]`

### 1.1 — ALL TWELVE SCORED `S3b` GRABS, FROM `disp_308_S3_all.txt`

| `dx` | `PREDICTED` | `abs err` | `pct err` | **`ratio`** | dir | `contrast` |
|---:|---:|---:|---:|---:|:--|---:|
| `-123` | `-165.38` | `42.38` | `25.6%` | **`0.744`** | under | `0.853` |
| `-458` | `-405.60` | `52.40` | `12.9%` | **`1.129`** | **OVER** | `0.731` |
| `-70` | `-106.35` | `36.35` | `34.2%` | **`0.658`** | under | `0.573` |
| `-72` | `-106.08` | `34.08` | `32.1%` | **`0.679`** | under | `0.630` |
| `-69` | `-105.81` | `36.81` | `34.8%` | **`0.652`** | under | `0.385` |
| `-69` | `-91.67` | `22.67` | `24.7%` | **`0.753`** | under | `0.626` |
| `-69` | `-91.78` | `22.78` | `24.8%` | **`0.752`** | under | `0.403` |
| `-16` | `-11.04` | `4.96` | `44.9%` | **`1.449`** | **OVER** | `0.286` |
| `-37` | `-53.34` | `16.34` | `30.6%` | **`0.694`** | under | `0.624` |
| `-37` | `-53.54` | `16.54` | `30.9%` | **`0.691`** | under | `0.624` |
| `-37` | `-53.54` | `16.54` | `30.9%` | **`0.691`** | under | `0.619` |
| `-106` | `-132.63` | `26.63` | `20.1%` | **`0.799`** | under | `0.818` |

**`n=12` · median `pct err` `30.76%` · mean `28.88%` · `over=2` `under=10` · ratio median `0.719`
(all twelve) and `0.692` (the ten mid-band).**

### 1.2 — WHAT THAT SHAPE RULES IN, AND WHAT IT RULES OUT

**A CONSTANT RATIO IS A SCALE ERROR, NOT AN AVERAGING ERROR.** `RUN-SHEET-308` §2's candidate
diagnosis — *the matched texture sits at a depth different from the centre ray* — predicts an error
that **varies with what happens to be in the patch**, frame by frame. **The corpus does not show
that. It shows the same `0.65`-`0.80` factor on ten different frames at five different depths**,
including three frames (`-37`,`-37`,`-37`) that reproduce each other exactly. **A projection-scale
term, or a wrong constant in the log's own `PREDICTED`, fits this better than patch averaging does.**

**►►►► THAT IS A REASON TO RUN §2a, NOT A REASON TO SKIP IT.** It is a DIAGNOSIS from twelve frames
of one arm at one separation (`301` §0, count five), and §2a is the cheapest thing that can falsify
it: **if the ratio does not move as the patch tightens, patch averaging is dead and the scale term
is the live hypothesis.** The ladder is the falsifier for `RUN-SHEET-308` §2's diagnosis, and this
session is not permitted to file either one from the table above.

**AND THE TWO OVER-READERS ARE NOT NOISE ON THE SAME LAW.** Both extremes read HIGH while the whole
middle reads LOW. **Whatever §2a finds, `V3` must not be closed on `-11.04 -> -16`** — `308` §6.2
already said the pass is the weakest evidence on the board; §1.1 puts a number on it (`44.9%`).

---

## §2 — PRE-REGISTRATION. **FIXED BEFORE THE INSTRUMENT IS TOUCHED, `304` §1.3.**

### 2.1 — THE LADDER

`--patch FRAC` narrows `xs` to a band around the crosshair column. **`FRAC = 1.00` MUST REPRODUCE
THE CURRENT WINDOW EXACTLY** (`px0 = half//4`, `px1 = 3*half//4`). The ladder is
**`1.00`, `0.50`, `0.25`, `0.10`** — chosen now, and it does not change after the first number is
seen.

### 2.2 — THE GATES

- **GATE 2a-i, WIRING.** At `FRAC 1.00`: all sixteen `dx` **byte-identical** to `disp_308_S3_all.txt`,
  all sixteen `contrast` identical, four `LOW CONFIDENCE` refusals and no others, and
  `--selftest A/B/C PASS` byte-identical. **If any of that moves, the option is wired wrong and
  NOTHING is filed.**
- **GATE 2a-ii, THE QUESTION.** Over the ten mid-band grabs, the **median `ratio` (`0.692`) moves
  toward `1.000` monotonically as `FRAC` tightens** -> the under-read is patch averaging over depth
  and the fix is to correlate where the ray test was taken. **Flat, or non-monotonic, or noisier
  without a trend -> patch averaging is FALSIFIED**, the live hypothesis becomes projection scale or
  the log's own `D`, and `RUN-SHEET-308` §2b (the flat-wall run) is required.
- **THE TRAP THIS GATE IS BUILT AGAINST:** a `FRAC` chosen because it lands a number in band is
  `304` §1.3 with a new face and would be the **sixth** wrong filed fix. The ladder is fixed in
  §2.1 and the metric is the **median over ten grabs**, not any single frame.

### 2.3 — THE CONFOUNDS THAT MUST BE PRINTED ON EVERY ROW

1. **`px0`/`px1` FEED THE REACHABLE SHIFT BOUNDS.** `measure()` derives
   `hi = min(search, w - (Ra + px1) - 1)` and `lo = max(lo, -(Ra + px0))`. **Tightening the patch
   WIDENS the reachable range**, so a `--patch` row can change a peg verdict on a frame that is not
   otherwise different. All twelve are `[-500 .. +500]` today (§0 item 6); any row whose `lo`/`hi`
   differs from that is a **confound to declare, not a measurement**.
2. **FEWER SAMPLES MEANS `contrast` MOVES.** A grab that drops under the `0.20` floor at a tight
   `FRAC` is **`308`'s gate working**, not §2a failing. It is recorded as a refusal and excluded
   from that row's median, and the exclusion is stated.
3. **`xs` USES A STRIDE OF 3** (`stereo_disparity.py:86`). At `FRAC 0.10` the band is ~46 px wide,
   which is ~15 columns. **A median over fifteen columns is a different instrument from a median
   over 152**; if the ladder's last rung goes noisy, that is the reason and it is not evidence.

### 2.4 — THE EDIT VENUE, WHICH IS NOT NEGOTIABLE

`stereo_disparity.py` is **LF-only UTF-8, no BOM, with non-ASCII in ten COMMENT lines**. The edit is
a **BYTE splice under `py`** that refuses unless the anchor matches exactly once —
`308` §5.2's shape, quoted verbatim when it is written. **NOT** `Get-Content`/`-replace`/
`Set-Content`: that is `00-STATE` §6's new trap (293 line endings, ten mangled comments). Output
stays ASCII (`H16`).

---

## §3 — THE BLOCKS

### 3.1 — GATE 3.1: RE-WEAR §1.1 UNDER POWERSHELL ON THE MAIN PC. **NO EDIT, NO `py`, READ-ONLY.**

It re-derives the whole of §1.1 from `disp_308_S3_all.txt` with the tool untouched. **Read-only:
it opens one text file and writes nothing.**

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
$order = @(); $rows = @{}; $name = $null
Get-Content .\disp_308_S3_all.txt | ForEach-Object {
  if ($_ -match '^=== (S3[bc]) frame (\d+)') {
    $name = "$($Matches[1])_$($Matches[2])"
    $order += $name
    $rows[$name] = [pscustomobject]@{ grab=$name; dx=$null; pred=$null; contrast=$null; lo=$null; hi=$null; low=$false }
  }
  elseif ($name) {
    if     ($_ -match '^searched\s+\[(-?\d+) \.\. ([+-]?\d+)\]') { $rows[$name].lo = [int]$Matches[1]; $rows[$name].hi = [int]$Matches[2] }
    elseif ($_ -match '^dx\s+(-?\d+) px')                          { $rows[$name].dx = [int]$Matches[1] }
    elseif ($_ -match 'mad_best\s+([0-9.]+)\s+mad_zero\s+([0-9.]+)') {
      $mb = [double]$Matches[1]; $mz = [double]$Matches[2]
      $rows[$name].contrast = [math]::Round(($mz - $mb) / $mz, 3)
    }
    elseif ($_ -match '^PREDICTED\s+(-?[0-9.]+) px')                { $rows[$name].pred = [double]$Matches[1] }
    elseif ($_ -match 'CANNOT ANSWER')                              { $rows[$name].low = $true }
  }
}
$scored = @(foreach ($n in $order) {
  $r = $rows[$n]
  if ((-not $r.low) -and ($null -ne $r.dx) -and ($null -ne $r.pred)) {
    $err = [math]::Abs($r.dx - $r.pred)
    [pscustomobject]@{
      grab  = $r.grab
      dx    = $r.dx
      pred  = $r.pred
      err   = [math]::Round($err, 2)
      pct   = [math]::Round(100 * $err / [math]::Abs($r.pred), 1)
      ratio = [math]::Round($r.dx / $r.pred, 3)
      dir   = $(if ([math]::Abs($r.dx) -gt [math]::Abs($r.pred)) { 'OVER' } else { 'under' })
      contrast = $r.contrast
      lo    = $r.lo
      hi    = $r.hi
      pctx  = 100 * $err / [math]::Abs($r.pred)
      ratx  = $r.dx / $r.pred
    }
  }
})
$scored | Format-Table grab, dx, pred, err, pct, ratio, dir, contrast, lo, hi -AutoSize
function Med($a) { $s = @($a | Sort-Object); if ($s.Count % 2) { $s[[int](($s.Count - 1) / 2)] } else { ($s[$s.Count / 2 - 1] + $s[$s.Count / 2]) / 2 } }
$mid = @($scored | Where-Object { ([math]::Abs($_.pred) -gt 20) -and ([math]::Abs($_.pred) -lt 300) })
"n            = " + $scored.Count
"median pct   = " + [math]::Round((Med ($scored | ForEach-Object { $_.pctx })), 2)
"mean pct     = " + [math]::Round(($scored | Measure-Object pctx -Average).Average, 2)
"over         = " + @($scored | Where-Object { $_.dir -eq 'OVER'  }).Count
"under        = " + @($scored | Where-Object { $_.dir -eq 'under' }).Count
"mid-band n   = " + $mid.Count
"mid ratio md = " + [math]::Round((Med ($mid | ForEach-Object { $_.ratx })), 3)
"all ratio md = " + [math]::Round((Med ($scored | ForEach-Object { $_.ratx })), 3)
"refusals     = " + @($order | ForEach-Object { $rows[$_] } | Where-Object { $_.low }).Count
"bounds set   = " + ((@($scored | ForEach-Object { "$($_.lo)/$($_.hi)" }) | Sort-Object -Unique) -join '  ')
``` **GATE 3.1: `n=12`, median `pct err` `30.76`, `over=2`, `under=10`, mid-band ratio
median `0.692`, and every `lo`/`hi` `-500`/`+500`.** If the bridge and PowerShell disagree on any of
those, `H7` has bitten again and **§2 does not proceed** until the disagreement is named.

### 3.2 — GATE 3.1 IS WORN. `[MEASURED]` 2026-09-04, MAIN PC

**All nine pre-registered values reproduce under PowerShell**: `n=12`, `median pct 30.76`,
`mean pct 28.88`, `over 2`, `under 10`, `mid-band n 10`, `mid ratio md 0.692`,
`all ratio md 0.719`, `refusals 4`, one bounds entry. **§1.1 is `[MEASURED]` and quotable
forward; the `H7` caveat on it is discharged.** One cosmetic difference from the gate as
written: the bounds set prints `-500/500`, not `-500/+500` — `[int]` drops the `+`. That is
this document's wording, not a measurement.

### 3.3 — THE `--patch` EDIT. **BYTE-SPLICE VIA `py`, NINE ANCHORS, EACH MATCHING EXACTLY ONCE.**

The splice script is written to `getv\tools\_patch309.py` and the ladder driver to
`getv\tools\ladder_driver.py` (both **ASCII, LF, scratch, NOT part of any commit**). The
script refuses unless **every** anchor matches exactly once and refuses if the CRLF count would
move; nothing is written on refusal.

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\tools
py .\_patch309.py .\stereo_disparity.py
py -c "import ast,io; ast.parse(io.open(r'stereo_disparity.py',encoding='utf-8').read()); print('SYNTAX OK')"
py .\stereo_disparity.py --selftest
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
git rev-parse --show-toplevel
git --no-optional-locks status --porcelain -- getv/tools/stereo_disparity.py getv/tools/_patch309.py getv/tools/ladder_driver.py
git diff --stat -- getv/tools/stereo_disparity.py
```

**GATE 3.3** — `PATCHED ... CRLF=0 ... anchors=9`, `SYNTAX OK`, `selftest A/B/C PASS`
**byte-identical to `308` §5.3**, `git rev-parse` prints the `goldeneye-native` toplevel, and
`git diff --stat` reads **`1 file changed, 25 insertions(+), 5 deletions(-)`** on that one path.
Any other path in the diff, or any CRLF, means STOP.

### 3.4 — THE LADDER

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
py F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\tools\ladder_driver.py
```

It takes the grab list, the paths and every `predicted-frac` **from `disp_308_S3_all.txt` itself**
— `308` §0 item 3 is what a hand-typed table costs — runs all sixteen grabs at all four rungs,
writes `disp_309_ladder.txt`, and prints GATE 2a-i, the per-rung medians and the per-grab ratio
table. **Runtime is a few minutes; it is CPU only, no build, no game.**

---

## §5 — THE DRY RUN. **`[MEASURED, BRIDGE]`, ON A COPY. THE TRACKED FILE WAS NOT TOUCHED.**

**GATE 2a-i PASSES:** at `FRAC 1.00`, all sixteen `dx` and all sixteen `contrast` equal `308`'s,
four `LOW CONFIDENCE` refusals (the four `S3c`) and no others, band `[228..684)` / 152 columns,
bounds `[-500 .. +500]` on every grab, and `--selftest` **byte-identical** (`cmp` clean).

**►►►►►►►► GATE 2a-ii FAILS. THE RATIO DOES NOT MOVE.**

| `FRAC` | band | cols | mid-band `n` | **mid ratio median** | refused |
|---|---|---:|---:|---:|---|
| `1.00` | `[228..684)` | 152 | 10 | **`0.692`** | - |
| `0.50` | `[342..570)` | 76 | 9 | **`0.696`** | `S3b_12268` (`contrast 0.192`) |
| `0.25` | `[399..513)` | 38 | 10 | **`0.696`** | - |
| `0.10` | `[433..479)` | 16 | 10 | **`0.697`** | - |

**A fifteen-fold narrowing of the correlation band moves the median ratio by `0.005`.**
`RUN-SHEET-308` §2's candidate diagnosis — *the matched texture sits at a depth different from the
centre ray* — **is FALSIFIED. Patch averaging over depth is not the under-read.**

### 5.1 — AND THE TIGHTER PATCH DID SOMETHING ELSE: IT ATE BOTH OUTLIERS

| grab | `pred` | `1.00` | `0.50` | `0.25` | `0.10` |
|---|---:|---:|---:|---:|---:|
| `S3b_10069` | `-165.38` | `0.744` | `0.744` | `0.756` | `0.756` |
| **`S3b_10177`** | `-405.60` | **`1.129`** | `0.745` | `0.745` | **`0.750`** |
| `S3b_11926` | `-106.35` | `0.658` | `0.696` | `0.686` | `0.696` |
| `S3b_11990` | `-106.08` | `0.679` | `0.688` | `0.698` | `0.698` |
| `S3b_12268` | `-105.81` | `0.652` | `0.699`* | `0.690` | `0.690` |
| `S3b_12581` | `-91.67` | `0.753` | `0.753` | `0.753` | `0.753` |
| `S3b_12654` | `-91.78` | `0.752` | `0.752` | `0.752` | `0.752` |
| **`S3b_5400`** | `-11.04` | **`1.449`** | `0.906` | `0.634` | **`0.634`** |
| `S3b_9440` | `-53.34` | `0.694` | `0.694` | `0.694` | `0.694` |
| `S3b_9500` | `-53.54` | `0.691` | `0.691` | `0.691` | `0.691` |
| `S3b_9535` | `-53.54` | `0.691` | `0.672` | `0.691` | `0.691` |
| `S3b_9986` | `-132.63` | `0.799` | `0.807` | `0.814` | `0.814` |

`*` refused at that rung by the `0.20` floor and excluded from that median (§2.3 confound 2,
exactly as pre-registered).

**AT `FRAC 0.25` AND `0.10` ALL TWELVE GRABS LIE IN `0.634`-`0.814`.** The two grabs that
over-read at the wide patch — the largest prediction and the smallest — **collapse into the same
band as everyone else** (`10177`: `-458 -> -302`; `5400`: `-16 -> -7`). **The wide patch was not
averaging depth; on those two frames it was matching something outside the crosshair's
neighbourhood altogether.** The corpus is one constant factor, and the outliers were instrument
artefacts.

### 5.2 — WHAT THIS DOES TO `V3`'s ONE PASS

**`S3b_5400` reads `-16`, `-10`, `-7`, `-7` across the four rungs and PASSES `V3`'s ±5 px gate at
every one of them**, because the prediction is `-11.04` and any small number is within 5 px of it.
**A gate that cannot be failed is not a gate.** `308` §6.2 called this the weakest evidence on the
board; §1.1 measured it at `44.9%` error; §5.1 shows the underlying `dx` is not even stable.
**`V3` MUST NOT BE CLOSED ON THIS FRAME UNDER ANY `FRAC`.**

### 5.3 — THE LIVE HYPOTHESIS, AND IT IS NOT FILED

`main()` computes `pred_px = pred_frac * half` with `half = 912` (the play-area half). A constant
measured/predicted ratio of ~`0.69` says **`measured ~= pred_frac * 631`**. **A single wrong
constant — an eye width that is not half the play area, or a projection/FOV term the prediction
and the renderer do not share — reproduces every row of §5.1 with no per-frame freedom.**
**THIS IS A DIAGNOSIS AND THE COUNT OF WRONG FILED FIXES IS FIVE.** It is testable offline before
`RUN-SHEET-308` §2b costs a person anything: **find what eye width the run's own log used to write
`PREDICTION`, and compare it against `912`.** That is `310`'s first question.

### 5.4 — ONE DEFECT THE DRY RUN CAUGHT IN THIS SESSION'S OWN EDIT

The first draft derived the band arithmetically at every `FRAC`, including `1.00`
(`c +/- round((base1-base0)*patch/2)`). **`[MEASURED, BRIDGE]`: that does NOT reproduce the
historical window on every geometry** — at `half=66` it gives `[16..48)` where the tool has
`[16..49)`. **A ladder whose top rung is not the old instrument measures nothing.** The filed edit
takes an explicit `if patch >= 1.0: px0, px1 = base0, base1` branch, which is why GATE 2a-i can
be byte-identity rather than approximate.

---

## §6 — ►►►►►►►► THE LADDER IS WORN ON THE MAIN PC AND `RUN-SHEET-308` §2a's DIAGNOSIS IS DEAD

**`[MEASURED]` 2026-09-04, under `py`. EVERY CELL OF §5 AND §5.1 REPRODUCES EXACTLY** — the same
four medians (`0.692`, `0.696`, `0.696`, `0.697`), the same bands and column counts, the same
single refusal (`S3b_12268` at `0.50`, `contrast 0.192`), the same 48 per-grab ratios, the same
bounds `[-500 .. +500]` on every grab at every rung, and `GATE 2a-i mismatches = 0`. **`H7` is
satisfied for this read: the bridge and `py` agree on all of it, so §5 and §5.1 are `[MEASURED]`
and quotable forward.**

**GATE 2a-ii FAILS AND IT IS FILED AS A FALSIFICATION, NOT AS A FIX.** `RUN-SHEET-308` §2's
candidate diagnosis — *the matched texture sits at a depth different from the centre ray* — **is
FALSIFIED. Patch averaging over depth is not the `S3b` under-read.** `H19` keeps its hole; what it
loses is its first candidate.

### 6.1 — AND §5.3's CANDIDATE IS FALSIFIED TOO, BY ONE `grep`. `[MEASURED]`

**§5.3 guessed the log and the tool disagreed about the eye width. THEY DO NOT.** Over the 898
`x eye_width` lines in `run_307_S3b_sep32.log` the implied width is **`910.34` to `913.45` px**,
and `stereo.c` fixes it at `GE_STEREO_MANDATED_PLAYAREA_PX * 0.5f = 912.67`. **The tool's
`half = 912` is the same number.** The pixel conversion is not the error — **one grep closed a
candidate a whole run would have chased.**

**AND THE LOG'S OWN LAW IS EXACT.** `frac * D` reads **`-23.3760` to `-23.3840` over 687
prediction lines** at `separation=32` — the 1/D law holds in the PREDICTION to four significant
figures. Whatever is wrong is a CONSTANT, which is exactly what §1.2 said the corpus shape
implied.

### 6.2 — WHERE THE CONSTANT LIVES, AND IT IS ONE LINE OF `stereo.c`

`geStereoPredict()` (`vendor/ge-decomp/src/game/stereo.c:512`) computes

    frac = -ge_st_sep / (depths[i] * tanw)      with tanw = ge_st_tR - ge_st_tL

and the run logged **`tanw = 1.368534`**, `separation = 32.000 FULL (each eye +/- 16.000)`, eye
viewport **`160x180` n64 units (full width `320`)**, tangents **`L=-0.684267 R=+0.684267`**,
**`D=-0.577350 U=+0.577350`**.

**►►►► THE TANGENTS ARE NOT CONSISTENT WITH THE EYE'S OWN ASPECT, AND THE FACTOR IS EXACTLY 4/3.**
`[MEASURED]`, to six decimals: `0.577350 * (160/180) * (4/3) = 0.684267`. The horizontal tangent
is the vertical tangent times the eye's aspect **times an extra `4/3`**.

**A 4:3 factor dropped or added in the horizontal frustum moves the predicted disparity by exactly
that factor, and its two candidate ratios BRACKET the measurement:** `1 / (4/3) = 0.750` and
`(4/3) / 2 = 0.667` against a measured median of **`0.692`-`0.697`**. **NEITHER MATCHES. The
measurement sits between them, ~4% from `0.750` and ~4% from `0.667`.**

**THIS IS A DIAGNOSIS AND THE COUNT OF WRONG FILED FIXES IS FIVE.** It is not filed, and it must
not be "fixed" by picking whichever aspect term lands closest:
1. **A candidate that misses by 4% is not identified.** The corpus spread is `0.634`-`0.814`, so
   4% is inside the noise and the bracket does not discriminate.
2. **The correlator's own accuracy at these disparities is UNMEASURED** — that is precisely what
   `RUN-SHEET-308` §2b's flat single-depth wall was for, and §5.1 makes it MORE necessary, not
   less: an instrument whose error bar is unknown cannot separate `0.667` from `0.750`.
3. **Whether the RENDERER uses these logged tangents is not established by this session.** The
   prediction reads them; the eye loop's actual projection was not inspected. **If the two agree,
   the constant is elsewhere. That comparison is `310`'s first job and it is OFFLINE.**

### 6.3 — WHAT THIS SESSION IS ALLOWED TO CLAIM

- **`RUN-SHEET-308` §2a is WORN and its diagnosis is FALSIFIED.** `[MEASURED]`
- **The under-read is a near-constant factor of ~`0.69`, not a per-frame averaging error.**
  `[MEASURED]`, twelve grabs, four patch widths.
- **The eye-width conversion is NOT the error.** `[MEASURED]`
- **A 4:3 aspect term is UNACCOUNTED FOR in the logged frustum.** `[MEASURED]` — arithmetic, exact.
- **That term is NOT established as the cause.** `[HYPOTHESIS]` — and `V3` does not close on it.

---

## §7 — ►►►►►►►► WORN ON THE MAIN PC. **`[MEASURED]` 2026-09-04, UNDER `py`.**

| block | gate | `[MEASURED]` |
|---|---|---|
| **3.1** | re-wear §1.1 | **All nine values**: `n=12`, `median pct 30.76`, `mean 28.88`, `over 2`, `under 10`, `mid n 10`, `mid ratio md 0.692`, `all ratio md 0.719`, `refusals 4`, one bounds entry. **`H7` discharged for §1.1** |
| **3.3** | the splice | **`PATCHED 15974 -> 17411 bytes  CRLF=0  anchors=9`**, `SYNTAX OK`, **`selftest A/B/C PASS` byte-identical to `308` §5.3**, toplevel `F:/Projects/GEVR/GoldenEyeVR/goldeneye-native`, dirty set ` M getv/tools/stereo_disparity.py` + the two named scratch files and nothing else |
| **3.3** | the diff size | **`29 insertions(+), 8 deletions(-)` — the sheet registered `25 / 5`. §7.1** |
| **3.4** | the ladder | **EVERY CELL OF §5 AND §5.1 REPRODUCES**: four medians `0.692 / 0.696 / 0.696 / 0.697`, the same bands `[228..684) [342..570) [399..513) [433..479)` and counts `152 / 76 / 38 / 16`, the same single refusal (`S3b_12268` at `0.50`), all 48 per-grab ratios, `GATE 2a-i mismatches = 0`, bounds `[-500 .. +500]` everywhere |

**GATE 2a-ii FAILS ON THE MAIN PC AS IT DID ON THE BRIDGE. `RUN-SHEET-308` §2a IS WORN AND ITS
DIAGNOSIS IS FALSIFIED** (§6). §5 and §5.1 lose their `[MEASURED, BRIDGE]` caveat.

### 7.1 — THE ONE GATE VALUE THAT MISSED, AND IT WAS THE ASSISTANT'S

**§3.3 pre-registered `25 insertions / 5 deletions`. The truth is `29 / 8`.** The number was a
hand-count of how `git` coalesces unchanged lines inside a replaced block — **an arithmetic
prediction offered in a table of measured values, with no label saying so.**

**WHAT SAVES THE EDIT IS A DIFFERENT CHECK, AND IT IS BYTE-EXACT:** the patched
`stereo_disparity.py` on the main PC is **byte-identical to the copy the entire §5 dry run was
performed against** — `md5 316cb9c317f225a3d16482733ee20c79`, 17,411 bytes, both sides. **The
instrument that produced §7's ladder is provably the instrument that produced §5's.** The
substance of GATE 3.3 also passed in full: one path, `CRLF=0`, nine anchors, `SYNTAX OK`,
selftest byte-identical.

**THE RULE THIS FILES (§4 of `00-STATE`): A PRE-REGISTERED NUMBER DERIVED BY ARITHMETIC IN THE
HEAD IS A PREDICTION AND MUST BE LABELLED ONE.** A gate list that mixes measured values with
guessed ones teaches the reader to shrug at a miss, which is the opposite of what a gate is for.

---

## §4 — WHAT NEEDS A PERSON

- **NOTHING. §3.1, §3.3 and §3.4 are all worn (§7).** The next job, `310`'s first, is OFFLINE:
  read the eye loop's own projection and compare it against the tangents `geStereoPredict()` logs.
- **`RUN-SHEET-308` §2b is still deferred behind §2a** — one short run at a flat textured wall,
  `GETV_STEREO_OFFSET=32`, F9 four or five times. **§1.2 raises the odds it will be needed.**
- **`E3` (FC3/FC4) is CLOSED.** Do not re-ask.
- **The commit is the owner's**, this sheet's own paths only, explicit `git add --` path lists.
  **Do NOT use `COMMIT-NOW.cmd`** (`307` §5, 16 strays).

**`169` NEXT ID = `U-26`.**

---

## §8 — THE COMMIT. **TWO REPOS. OWNER-RUN. THIS SHEET'S OWN PATHS ONLY.**

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
git rev-parse --show-toplevel
git --no-optional-locks status --porcelain -- getv/tools
git add -- getv/tools/stereo_disparity.py
git commit -F F:\Projects\GEVR\GoldenEyeVR\COMMIT-MESSAGE-2026-09-04d-native.txt
git log --oneline -1
git --no-optional-locks status --porcelain -- getv/tools

Set-Location F:\Projects\GEVR\GoldenEyeVR
git rev-parse --show-toplevel
git --no-optional-locks status --porcelain -- repo/docs COMMIT-MESSAGE-2026-09-04d.txt COMMIT-MESSAGE-2026-09-04d-native.txt
git add -- repo/docs/00-STATE.md repo/docs/00-STATE.md.bak-309 "repo/docs/309-THE-UNDER-READ-IS-THIRTY-PERCENT-NOT-THIRTEEN.md" repo/docs/PRIORITY-BOARD-309.md repo/docs/NEXT-SESSION-PROMPT-310.md COMMIT-MESSAGE-2026-09-04d.txt COMMIT-MESSAGE-2026-09-04d-native.txt
git commit -F F:\Projects\GEVR\GoldenEyeVR\COMMIT-MESSAGE-2026-09-04d.txt
git log --oneline -1
git --no-optional-locks status --porcelain -- repo/docs
```

**NOT in either list, deliberately:** `getv/tools/_patch309.py` (scratch, spent) and
`getv/tools/ladder_driver.py` (keep it only as a deliberate decision — it re-runs the ladder).
**And `repo\docs\_to_delete\` must be deleted, not committed.**

**The docs message is deliberately distinct from `308`'s** — `98796e5` and `162b2b4` share a
subject line byte for byte (§0 item 2), and that is how a later session quotes the wrong commit.
