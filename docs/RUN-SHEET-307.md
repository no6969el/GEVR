# `RUN-SHEET-307` — FIRE THE `H1` ALARM ON A REAL FRAME, THEN TAKE THE SEPARATION GATE WHERE IT CAN BE MEASURED

**`RUN-SHEET-306` IS WORN IN FULL.** `307` is what follows from it. Binary unchanged:
`45756E5A…3F92`, **18,070,774 bytes** — every block below still gates on `EXPECTED-EXE-303.txt`.

**►►►► THE ONE BLOCK THAT FAILED WAS THE ASSISTANT'S AND IT FAILED TO PARSE, NOT TO RUN.**
`RUN-SHEET-306` §6.2 contained `--predicted-frac <the number from the log>`; **`<` is a reserved
operator in PowerShell** and the block stops on it: *"The '<' operator is reserved for future
use."* **`00-STATE` §7a says every command is supplied COMPLETE, and a placeholder is not a
command** — `296` §11 with a new face. **§1 below derives the number from the log itself.**

---

## §0 — WHAT `306` RETURNED, IN ONE TABLE

| | |
|---|---|
| §1, §2 | **PASS.** `admission=52  equal=32  permuted=4  refused=168` over 256 dumps, no traceback. **`305` reproduces exactly on the main PC and is quotable forward.** `P1`'s nine are `equal=9` |
| §3 | **`P1` — all nine gameplay frames CLEAN**, worst blob 15 px |
| §4 | **`P2` — four frames with a WHOLE DEAD EYE** (`MODEL_MTX 38/0`, strict subset), five refused by the tool's own `\|dx\| >= 8` guard. **Neither arm carries the polygon, so `304` §2a cannot date it** |
| §6.1 | **PASS — AND IT IS THE FIRST TIME.** `only in eye0 = 0`, `81/81`, `49/49`, `73/73`, `eyes-rebuilt=1 chr=2 obj=2` |
| §6.2 | **UNSCORABLE.** The log predicts **−7,024 px** on a **912 px** eye. All seven grabs out of band |

---

## §1 — THE CORRECTED DISPARITY READ. **ITS PURPOSE IS THE `H1` ALARM, NOT THE GATE. OFFLINE.**

**PRE-REGISTERED, BEFORE THE RUN:** `dlgrab_S3_5400.bmp` carries a predicted disparity of
**−7.696404 eye-widths**. **The correlator MUST PEG and the `H1` alarm MUST FIRE.** `H1` was opened
because that alarm had never fired; `301` §2 rebuilt `measure()` so that it can; `306` §1 made its
line printable. **This is the first real frame in this project's history where it is REQUIRED to
fire — and if it stays silent, `H1` is not closed.**

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
$log   = ".\run_306_S3_separation.log"
$lines = Get-Content $log
$grab  = ($lines | Select-String -Pattern '\[getv\]\[dlgrab\] frame 5400 ' | Select-Object -First 1).LineNumber
$frac  = ($lines[0..($grab-1)] | Select-String -Pattern 'PREDICTION: disparity = (-?[0-9.]+) x eye_width' | Select-Object -Last 1).Matches.Groups[1].Value
"grab line $grab   predicted-frac $frac"
py ..\tools\stereo_disparity.py .\grabs_306_S3\dlgrab_S3_5400.bmp --predicted-frac $frac *> disp_307_5400_default.txt
py ..\tools\stereo_disparity.py .\grabs_306_S3\dlgrab_S3_5400.bmp --predicted-frac $frac --search 200 *> disp_307_5400_s200.txt
py ..\tools\stereo_disparity.py .\grabs_306_S3\dlgrab_S3_5400.bmp --predicted-frac $frac --search 500 *> disp_307_5400_s500.txt
py ..\tools\stereo_disparity.py .\grabs_306_S3\dlgrab_S3_5400.bmp --predicted-frac $frac --search 800 *> disp_307_5400_s800.txt
Get-ChildItem disp_307_5400_*.txt | ForEach-Object { "=== $($_.Name) ==="; Get-Content $_.FullName }
```

**GATE §1 — `$frac` must print `-7.696404`, and all four runs must print
`>> dx IS PEGGED AT THE EDGE OF THE SEARCHED RANGE`.** The `dx` value is expected to MOVE with
`--search` and that is not a defect here — **it is `298` §2.1's signature of an answer that IS the
search width, and on this frame it is the correct answer.** **A silent run on any of the four
retracts `H1`'s closure.**

**►► THE OUTPUT IS REDIRECTED TO FILES ON PURPOSE.** `306` read its eyediff and census numbers on
the BRIDGE because `RUN-SHEET-306`'s reads printed to the console and the console does not reach an
offline assistant. **Every read in this sheet writes a file.**

---

## §2 — ►►►►►►►► `S3b` AND `S3c`: THE SEPARATION GATE WHERE IT CAN ACTUALLY BE MEASURED

**THE PHYSICS, IN ONE LINE: disparity goes as 1/D, so a NEAR wall makes the prediction ENORMOUS.**
`separation=500` was chosen *"deliberately absurd"* (`255` §4) and the venue was chosen as *"stand
still, facing a wall"* (`RUN-SHEET-299` §4). **Each is right alone; their product is 7.7 eye-widths
and cannot be correlated.** Two arms fix it from opposite ends, and **agreement between them is the
1/D law measured in PIXELS instead of printed** — which no arm has ever done.

### 2.0 — ►►►► THE AMPLITUDE GATE. **READ IT BEFORE SCORING ANY DISPARITY, IN EITHER ARM.**

**The grabbed frame's own `PREDICTION: disparity = … px` line must satisfy `|px| ≤ 500`.**
At 2560 wide with the play area `[367..2192)` the correlator's reachable range is clipped by the
IMAGE EDGE, not by `--search` — `301` §2's selftest C reads `[-800..+595]` for `--search 800`.
**A prediction outside that is a request the instrument cannot express, and scoring it produces a
peg, not a measurement.** This gate is new, it is `306`'s only real finding about the arm, and
**it costs one `Select-String`.**

### 2a — `S3b`. **SAME VENUE AS `306`, SEPARATION 32 INSTEAD OF 500.** Predicted ≈ **−450 px** at `D≈47`.

**Stand where you stood for `306` — still, facing the near wall.** One behaviour change from
`306` §6's block: `GETV_STEREO_OFFSET` **32**, and the log name and grab folder. Everything else is
byte-identical.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
if (-not (Test-Path .\EXPECTED-EXE-303.txt)) { throw "EXPECTED-EXE-303.txt is missing -- run RUN-SHEET-303 section 2c after the build, before any arm." }
$want = (Get-Content .\EXPECTED-EXE-303.txt).Trim()
$got  = "$((Get-FileHash .\goldeneye.exe -Algorithm SHA256).Hash) $((Get-Item .\goldeneye.exe).Length)"
if ($want -ne $got) { throw "BINARY MISMATCH -- this is NOT the 303 build. want [$want] got [$got]" }
if (Test-Path .\run_307_S3b_sep32.log) { throw "run_307_S3b_sep32.log EXISTS -- rename it or pick a new name (H5)." }
Get-ChildItem .\dlgrab_*.txt,.\dlgrab_*.bmp -ErrorAction SilentlyContinue | Measure-Object | Select-Object -ExpandProperty Count
$env:GETV_ARM                   = "S3b"
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
$env:GETV_DLGRAB_AT             = "5400"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_307_S3b_sep32.log 2>&1
Select-String -Path run_307_S3b_sep32.log -Pattern 'getv\]\[run\] ARM='
Select-String -Path run_307_S3b_sep32.log -Pattern 'separation=' | Select-Object -First 2
Select-String -Path run_307_S3b_sep32.log -Pattern 'dlgrab_|getv\]\[shot\]'
Select-String -Path run_307_S3b_sep32.log -Pattern 'props interpolated|simulation held to|ours: x=|game_exit requested|EXCEPTION'
New-Item -ItemType Directory -Force -Path .\grabs_307_S3b | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_307_S3b -Force -ErrorAction SilentlyContinue
Get-ChildItem .\grabs_307_S3b | Select-Object Name, Length
```

**PRESS F9 FOUR OR FIVE TIMES AT DIFFERENT DISTANCES — pressed against the wall, a pace back, mid
room, and down the longest line you can see — and STAND STILL for a second before each.** The
amplitude gate picks which grab is scorable; you do not have to judge it live.

### 2b — `S3c`. **SEPARATION 500, TAKEN DOWN A LONG SIGHTLINE.** Predicted ≈ **−170 to −500 px** at `D` 650–1900.

**`306` walked through the measurable window and grabbed outside it.** `[MEASURED]` in that log:
at frames **1620–1740** the camera stood essentially still at **`(-1316.3, 97.1, -2708.5)` looking
`(-0.02, -0.07, +0.997)`, room 7, `D = 1933`, predicted `-172.5 px`** — and at frames 1380–1560,
`D` 644–960, predicted −517 to −347 px. **That is the spot: the long line you were looking down
BEFORE you walked up to the wall.**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
if (-not (Test-Path .\EXPECTED-EXE-303.txt)) { throw "EXPECTED-EXE-303.txt is missing -- run RUN-SHEET-303 section 2c after the build, before any arm." }
$want = (Get-Content .\EXPECTED-EXE-303.txt).Trim()
$got  = "$((Get-FileHash .\goldeneye.exe -Algorithm SHA256).Hash) $((Get-Item .\goldeneye.exe).Length)"
if ($want -ne $got) { throw "BINARY MISMATCH -- this is NOT the 303 build. want [$want] got [$got]" }
if (Test-Path .\run_307_S3c_longsight.log) { throw "run_307_S3c_longsight.log EXISTS -- rename it or pick a new name (H5)." }
Get-ChildItem .\dlgrab_*.txt,.\dlgrab_*.bmp -ErrorAction SilentlyContinue | Measure-Object | Select-Object -ExpandProperty Count
$env:GETV_ARM                   = "S3c"
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
$env:GETV_STEREO_OFFSET         = "500"
$env:GETV_STEREO_MODE           = "1"
$env:GETV_STEREO_PROBE          = "60"
$env:GETV_STEREO_VIEWRESTORE    = "1"
$env:GETV_STEREO_PAIRGUARD      = "0"
$env:GETV_STEREO_REBUILD        = "1"
$env:GETV_STEREO_REBUILD_REPORT = "1"
$env:GETV_STEREO_REBUILD_VIEWER = "1"
$env:GETV_DLGRAB_AT             = "1620"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_307_S3c_longsight.log 2>&1
Select-String -Path run_307_S3c_longsight.log -Pattern 'getv\]\[run\] ARM='
Select-String -Path run_307_S3c_longsight.log -Pattern 'dlgrab_|getv\]\[shot\]'
Select-String -Path run_307_S3c_longsight.log -Pattern 'props interpolated|simulation held to|ours: x=|game_exit requested|EXCEPTION'
New-Item -ItemType Directory -Force -Path .\grabs_307_S3c | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_307_S3c -Force -ErrorAction SilentlyContinue
Get-ChildItem .\grabs_307_S3c | Select-Object Name, Length
```

**`GETV_DLGRAB_AT=1620` is a free extra sample at the frame `306` measured `D=1933` on — the walk
will not reproduce frame for frame, so it is a bonus and not the method. THE METHOD IS F9: stand
still looking down the LONGEST line in the room and press it four or five times, then walk a little
and do it again.** Do not walk up to a wall.

### 2c — THE AMPLITUDE TABLE, THEN THE DISPARITY. **BOTH ARMS, ONE BLOCK.**

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
foreach ($arm in @(@('S3b','run_307_S3b_sep32.log'), @('S3c','run_307_S3c_longsight.log'))) {
  $name = $arm[0]; $log = ".\$($arm[1])"
  if (-not (Test-Path $log)) { "MISSING $log -- skipped"; continue }
  $lines = Get-Content $log
  "=== $name ==="
  foreach ($g in (Get-ChildItem ".\grabs_307_$name\*.bmp")) {
    $fr = [regex]::Match($g.Name,'(\d+)\.bmp$').Groups[1].Value
    $ln = ($lines | Select-String -Pattern "\[getv\]\[dlgrab\] frame $fr " | Select-Object -First 1).LineNumber
    if (-not $ln) { "  $($g.Name)  NO DLGRAB LINE"; continue }
    $m = ($lines[0..($ln-1)] | Select-String -Pattern 'PREDICTION: disparity = (-?[0-9.]+) x eye_width \(= (-?[0-9.]+) px' | Select-Object -Last 1)
    $d = ($lines[0..($ln-1)] | Select-String -Pattern 'MEASURED centre depth D=([0-9.]+)' | Select-Object -Last 1)
    "  {0,-28} D={1,10}  frac={2,-14} px={3,10}" -f $g.Name, $d.Matches.Groups[1].Value, $m.Matches.Groups[1].Value, $m.Matches.Groups[2].Value
  }
}
```

**GATE §2c — THE AMPLITUDE GATE, AND IT IS SCORED BEFORE ANY PIXEL IS READ.** Take the grab whose
`px` column has the **smallest magnitude at or under 500** in each arm. **If an arm has none, that
arm is void as a disparity measurement and the venue is the reason — say so and do not score it.**
Then, for the chosen grab in each arm:

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
py ..\tools\dlgrab_eyecensus.py .\grabs_307_S3b\dlgrab_S3b_<frame>.txt --calls --arena *> census_307_S3b.txt
py ..\tools\stereo_disparity.py .\grabs_307_S3b\dlgrab_S3b_<frame>.bmp --predicted-frac <frac> --search 500 *> disp_307_S3b.txt
py ..\tools\dlgrab_eyecensus.py .\grabs_307_S3c\dlgrab_S3c_<frame>.txt --calls --arena *> census_307_S3c.txt
py ..\tools\stereo_disparity.py .\grabs_307_S3c\dlgrab_S3c_<frame>.bmp --predicted-frac <frac> --search 500 *> disp_307_S3c.txt
Get-ChildItem census_307_*.txt,disp_307_S3*.txt | ForEach-Object { "=== $($_.Name) ==="; Get-Content $_.FullName }
```

**►► THIS IS THE ONE BLOCK IN THIS SHEET THAT CARRIES PLACEHOLDERS, AND THEY ARE MARKED.** `<frame>`
and `<frac>` come from §2c's table. **Substitute them before running — PowerShell will refuse the
`<` and stop, which is `306`'s own error and is the reason this note exists.**

**GATE §2 — the same gate `RUN-SHEET-292` §5 wrote, now with an admissible prediction:**
`VERDICT PASS` (`|measured − predicted| ≤ 5 px`), **the sign matches — the RIGHT eye's image
FURTHER LEFT, which the tool prints as a NEGATIVE `dx`** (`299` §3, settled from `stereo.c:233`
and `:387`) — the census gate 6.1 passes on that frame (`only in eye0 = 0`, all three `MODEL_*`
non-zero both eyes), `props interpolated 0`, zero `simulation held to`, `ours: x=367.333`,
`game_exit requested`.

**►►►► AND THE READING THAT NEITHER ARM CAN GIVE ALONE: `S3b` measures the law at `sep=32, D≈47`
and `S3c` at `sep=500, D≈1900` — a factor of ~16 in separation against a factor of ~40 in depth.
If both land inside ±5 px of their own predictions, the 1/D law is MEASURED, not printed, and
`258` STAGE 6's gate is met on two independent points.** If one passes and the other pegs, the one
that pegged is a venue problem; **if one passes and the other MISSES by more than 5 px, that is a
real result about the projection and it outranks everything else on the board.**

---

## §3 — CONFIRM `306` §3 AND §4 ON THE MAIN PC, TO FILES. **OFFLINE, ~2 MINUTES.**

**`307` §3's `P1`/`P2` numbers were read on the BRIDGE** because `RUN-SHEET-306` §3/§4 printed to
the console. **`H7` is closed for these tools by `306` §2's exact reproduction, so this is a
confirmation and not a re-litigation — but it is cheap and it puts the numbers in a file.**

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
py ..\tools\stereo_eyediff.py (Get-ChildItem .\grabs_304_P1\*.bmp).FullName *> eyediff_307_P1.txt
py ..\tools\stereo_eyediff.py (Get-ChildItem .\grabs_304_P2\*.bmp).FullName *> eyediff_307_P2.txt
py ..\tools\dlgrab_eyecensus.py .\grabs_304_P2\dlgrab_P2_1369.txt --calls *> census_307_P2_1369.txt
py ..\tools\dlgrab_eyecensus.py .\grabs_306_S3\dlgrab_S3_5400.txt --calls --arena *> census_307_S3_5400.txt
Select-String -Path eyediff_307_P1.txt -Pattern 'total|VERDICT'
Select-String -Path eyediff_307_P2.txt -Pattern 'total|VERDICT|REFUSED'
Select-String -Path census_307_P2_1369.txt -Pattern 'MODEL_|only in eye'
Select-String -Path census_307_S3_5400.txt -Pattern 'viewport loads|MODEL_|only in eye'
```

**GATE §3 — the bridge's readings must reproduce:** `P1` nine frames, **worst blob 15 px, no
`ONE-EYE DIVERGENCE`**; `P2` **four `ONE-EYE DIVERGENCE` (523,554 / 469,111 / 576,312 / 576,312 px)
and five `REFUSED: |dx| >= 8`**; `P2_1369` **`MODEL_MTX 38 / 0`, `only in eye0 = 18`, STRICT
SUBSET**; `S3_5400` **`81/81`, `49/49`, `73/73`, `only in eye0 = 0`.** A disagreement anywhere here
re-opens `H7` for the Python toolchain and everything in `307` is withdrawn.

---

## §4 — **STILL OWED, STILL ONE SENTENCE: WHAT DID FC3 AND FC4 LOOK LIKE?**

Third sheet of asking, and nothing about it has changed. `run_304_FC3_road_on.log`
(`GETV_FARCLAMP=1`) against `run_304_FC4_road_off.log` (`GETV_FARCLAMP=0`), pictures in
`grabs_304_FC3\` and `grabs_304_FC4\`. **One sentence about each, in your own words. If they looked
the same again, `RUN-SHEET-303` §0.1 is a `279` §7 null for the SECOND time and CLOSES.**

---

## §5 — ~~THE COMMIT~~ **WORN 2026-09-04: `b929c9b`. DO NOT RE-RUN. THE BLOCK IS KEPT BELOW, RULE `2`.**

**►► `[MEASURED]` FROM `git log`: `b929c9b` (`GoldenEyeVR`) landed all six intended documents AND
SIXTEEN STRAY `COMMIT-MESSAGE-*.txt` FILES — 22 in total — because it was made with
`COMMIT-NOW.cmd`, which stages the whole dirty tree rather than a path list.** Nothing is wrong
with what landed; the strays are `303`-era message files that had been untracked for a day. **But
the staged set was NOT the sheet's set, and that is the distinction `303` §5.0 asks for: check the
dirty set BEFORE staging, because a tool that stages everything makes the sheet's path list
advisory.** **AND `COMMIT-NOW.cmd` PICKS "THE NEWEST `COMMIT-MESSAGE` FILE" — rule `17`'s
silent-staleness shape exactly.** It chose correctly here (`COMMIT-MESSAGE-2026-09-04b.txt`); it
will choose wrongly the first time a session writes a message file and the owner commits an older
piece of work. **Both trees are clean and nothing is owed.**

### 5 (ORIGINAL) — ONE REPO THIS TIME. `RUN-SHEET-306` §7 IS ALREADY WORN.

**►► `[MEASURED]` FROM `git log` BEFORE THIS SECTION WAS WRITTEN: `22e6b0a` (`GoldenEyeVR`, eight
files) and `99d8a63` (`goldeneye-native`, the three-tool ASCII fix, `5 insertions / 5 deletions`)
ARE IN, AND BOTH TREES ARE CLEAN.** **DO NOT RE-RUN `RUN-SHEET-306` §7.** `goldeneye-native` has
nothing dirty and gets no block here — **`307` changed no code at all.**

**This is the rule `306` filed twice, kept by the session that filed it:** a claim that a commit is
owed is a claim about git, and `git log --oneline -3` answers it.

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR
git rev-parse --show-toplevel
git --no-optional-locks log --oneline -2
git --no-optional-locks status --short -- repo/docs/00-STATE.md repo/docs/PRIORITY-BOARD-306.md repo/docs/PRIORITY-BOARD-307.md repo/docs/NEXT-SESSION-PROMPT-307.md repo/docs/RUN-SHEET-307.md repo/docs/307-THE-CENSUS-GATE-PASSED-AND-THE-PREDICTION-IS-SEVEN-EYE-WIDTHS.md
git diff --stat --ignore-cr-at-eol -- repo/docs/00-STATE.md repo/docs/PRIORITY-BOARD-306.md repo/docs/NEXT-SESSION-PROMPT-307.md
git add -- repo/docs/00-STATE.md repo/docs/PRIORITY-BOARD-306.md repo/docs/PRIORITY-BOARD-307.md repo/docs/NEXT-SESSION-PROMPT-307.md repo/docs/RUN-SHEET-307.md repo/docs/307-THE-CENSUS-GATE-PASSED-AND-THE-PREDICTION-IS-SEVEN-EYE-WIDTHS.md
git commit -F F:\Projects\GEVR\GoldenEyeVR\COMMIT-MESSAGE-2026-09-04b.txt
git log --oneline -1
```

**GATE §5 — the first line must end in `GoldenEyeVR`; `git log --oneline -2` must already show
`22e6b0a` and `e58e1f1`; and `diff --stat` must name EXACTLY THREE tracked files —
`00-STATE.md`, `PRIORITY-BOARD-306.md` and `NEXT-SESSION-PROMPT-307.md`.** The three new
documents — the `307` doc, `RUN-SHEET-307.md` and **`PRIORITY-BOARD-307.md`** — are untracked and
appear as `??`. **`PRIORITY-BOARD-306.md` shows as MODIFIED because it was reverted to its
committed text and given a SUPERSEDED banner: `306` wrote it offline before the sheet ran, and
`307`'s results belong in `307`'s board.** **`NEXT-SESSION-PROMPT-307.md` shows as MODIFIED because it was
rewritten when the sheet came back and before any session read it — its own first line says so.**
**A fourth tracked file means something was touched that this sheet does not know about — stop and
read it.**

---

## §6 — AFTER `307`

1. **`H17` (NEW)** — `ZERO-REBUILD FRAMES` counts frames with an empty prop list. **A diagnosis:
   split it into `zsnap>0` and `zsnap==0`, the way `N1` split the near line.** `307` §4.
2. **`H18` (NEW)** — **the disparity gate has no amplitude check.** §2.0 is that check written as a
   run-sheet step; **the durable form is the game refusing to print a `PREDICTION` it knows is
   unmeasurable, or the tool refusing a `--predicted-frac` outside its own reachable range.**
3. **The polygon is still undated and still unexplained.** Eighteen gameplay grabs across `P1` and
   `P2` and not one carries it. **`305` §4's per-eye `MODEL_MTX` CONTENTS instrument is still the
   only level left.**
4. **`V4`/`V5`** — `S4` the mode-2 falsifier, then `R5a/b/c`, ARM 3's cost against `272` §5.2's
   0.890 ms CRADLE baseline. **Both become live the moment §2 passes.**
5. **GROUP `X`** — the XR layer, unchanged and unstarted.
