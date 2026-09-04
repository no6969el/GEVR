# `RUN-SHEET-306` — READ WHAT IS ALREADY ON DISK, THEN THE ARM THAT PROVES STEREO SEPARATES

**`306` IS OFFLINE. NO BUILD, NO RUN, NO COMMIT BY THE ASSISTANT.** Binary untouched and
`[MEASURED]` on disk this session: `45756E5ADB5F…E7223F92`, **18,070,774 bytes**, 21:05:38Z — it
equals `EXPECTED-EXE-303.txt` byte for byte, so every block below passes its own binary gate.

**►►►► THE FIRST THING TO KNOW: `RUN-SHEET-305` §5 IS WORN AND `RUN-SHEET-305` §2 WAS ALREADY
TRIED. ◄◄◄◄** Commits `689b009` (native) / `e58e1f1` (`GoldenEyeVR`) are IN and both trees are
clean on the six named paths — **`NEXT-SESSION-PROMPT-306`'s *"nothing in `305` is committed yet"*
is stale.** And `order_sweep_305.txt` exists, dated 23:45:07Z: **the sweep ran and CRASHED**, on
`dlgrab_2928`, the first `PERMUTATION` it reached. `306` §1.

---

## §0 — WHAT `306` FOUND, IN ONE TABLE. **ALL OF IT OFF THE FILESYSTEM, NONE OF IT FROM A RUN.**

| | |
|---|---|
| **1** | **`RUN-SHEET-305` §2 DIED AT THE FINDING IT WAS WRITTEN TO BOUND.** `py` 3.13 raised `UnicodeEncodeError: 'charmap' codec` on `\u25ba` (`►`) at `dlgrab_dlorder.py:93` — the `PERMUTATION` verdict line — the moment the sweep reached `dlgrab_2928`. **The instrument prints a character the redirected stdout cannot encode.** `H7`, billed a second time, and this time it cost the owner a command |
| **2** | **THE SELFTEST GATE IS EXPOSED THE SAME WAY.** `--selftest` prints check `B`'s header — `"B. ►► THE CHECK THAT FAILS ON A SET COMPARISON"` — **before** it prints `7 checks, 0 failed`. **GATE §1a of `RUN-SHEET-305` cannot pass on a cp1252 stdout either** |
| **3** | **AND `stereo_disparity.py`'s PEG ALARM IS ONE OF THE THREE `►` PRINT SITES** (`:261`). **`H1` was opened because that alarm had never fired. The first time it fires, it would have crashed the tool** |
| **4** | **FIXED OFFLINE, AND IT IS THE ONLY EDIT `306` MAKES:** every printable path of `dlgrab_dlorder.py`, `stereo_disparity.py` and `stereo_eyediff.py` is now **ASCII**. Five sites, `►` → `>>`, no logic touched. Selftests re-read **`7 checks, 0 failed`** and **`16 checks, 0 failed`** on the bridge — **and the bridge is not the gate; §1 is** |
| **5** | **►►►► `RUN-SHEET-304` §2a's `P1` ARM HAS BEEN RUN AND NOBODY HAS READ IT.** `run_304_P1_polygon_viewer_on.log`, `ARM=P1 START=2026-09-03T23:48:34Z`, **nine grabs in `grabs_304_P1\`**, provenance admissible — exactly one log, nine `[getv][dlgrab] frame` announcements against nine files on disk, `GETV_ARM` banner present, **no `EXCEPTION`, `game_exit requested`**. Frames **1225–1391**, past the ~541 opening, so **GATE §2a's "GRAB IN GAMEPLAY" is satisfied.** **`P2` has NOT run and the detector has NOT been run on `P1`** |
| **6** | **THE CORPUS IS 265 DUMPS, NOT 256.** `grabs_304_P1` added exactly nine at 23:48. `RUN-SHEET-305` GATE §2a pre-registers a total of 256 and would refuse — **reconciled here, and §2 below is re-shaped so reproduction and new data are scored separately** |

---

## §1 — RE-WEAR `305` UNDER THE MAIN PC's `py`. **`H7`. SECONDS. AND IT NOW TESTS THE FIX TOO.**

**NOTHING IN `305` IS QUOTABLE FORWARD UNTIL THIS PASSES** — that sentence is `RUN-SHEET-305`'s
and it still stands, because `305` §2's attempt did not get past the second folder.

**ONE CHANGE FROM `RUN-SHEET-305` §1, AND IT IS DELIBERATELY THE ONLY ONE:** the tools are now
ASCII, so these blocks are run with a **plain `py`, exactly as `305` wrote them**. If §1a still
raises `UnicodeEncodeError`, the ASCII fix is not what was wrong and the fallback is in §1e —
**do not run the fallback first, because then nothing is measured.**

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\tools
py .\dlgrab_dlorder.py --selftest
```

**GATE §1a — the last line must read `7 checks, 0 failed`, and check `B`'s header must print as
`B. >> THE CHECK THAT FAILS ON A SET COMPARISON`.** Check `B` is a pure reorder that a set-based
comparison scores clean; **if `B` passes on an implementation that uses `set()`, the check is not
doing its job and this file is worthless.** A `UnicodeEncodeError` here means `306`'s fix did not
take — go to §1e.

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
py ..\tools\dlgrab_dlorder.py (Get-ChildItem .\grabs_303_C1\*.txt).FullName (Get-ChildItem .\grabs_303_V1\*.txt).FullName
```

**GATE §1b — exactly ONE frame must come back `PERMUTATION` and it must be `dlgrab_C1_4676`,
reading `same 46 targets, 8 positions differ, span [29..36]` and `CYCLIC ROTATION of 8 calls by
3`. The other thirteen must read `ORDER IDENTICAL`, `dlgrab_C1_2336` and `dlgrab_V1_2732`
INCLUDED.** A second permutation here means the bridge and the main PC disagree and `305` §1.5 is
withdrawn.

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
py ..\tools\dlgrab_dlorder.py (Get-ChildItem .\grabs_299_E1\dlgrab_2928.txt,.\grabs_299_E1\dlgrab_2957.txt).FullName
py ..\tools\stereo_eyediff.py (Get-ChildItem .\grabs_299_E1\dlgrab_2928.bmp,.\grabs_299_E1\dlgrab_2957.bmp).FullName
```

**GATE §1c — THIS IS THE FALSIFIER AND IT IS THE WHOLE OF `305` §1.4.** Both frames must come
back **`PERMUTATION`** from the first command and **`total 0 px   blobs 0`** from the second.
**A non-zero pixel count on either frame puts the reorder back on the board as a candidate cause,
and `305` §1.4 is retracted.** `279` §7: this is the instrument pointed at the frames it is
expected to be boring on, and the expectation is pre-registered here.

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
py ..\tools\dlgrab_eyecensus.py .\grabs_303_C1\dlgrab_C1_4676.txt --calls --arena
```

**GATE §1d — the `ARENA` block must read `MODEL_MTX(3) eye1 … fresh=3` and `MODEL_VTX(4) eye1 …
reused-from-eye0=17 fresh=0`, and the two `MOVEMEM` lines must share ONLY `0386` and `0388`
(`G_MV_L0` / `G_MV_L1`, the lights).** If `0380`, `0382` or `0384` match between the eyes, `305`
§1.1's null is wrong and the second eye is drawing with the first eye's view after all.

### 1e — **THE FALLBACK, AND ONLY IF A GATE ABOVE RAISES `UnicodeEncodeError`.**

```powershell
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$env:PYTHONIOENCODING = "utf-8"
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\tools
py -X utf8 .\dlgrab_dlorder.py --selftest
```

**If this passes where §1a failed, the fault is the console encoding and not the tool** — say so
in the wear report, because it changes which of the two fixes the project keeps.

---

## §2 — THE CORPUS SWEEP, RE-SHAPED. **OFFLINE, ~2 MINUTES. `305` §2's QUESTION, UNCHANGED.**

**THE QUESTION, PRE-REGISTERED AND UNCHANGED FROM `RUN-SHEET-305` §2: is there ANY dump that
`dlgrab_dlorder.py` calls `permuted` AND `stereo_eyediff.py` calls a pixel hit?**

**WHY IT IS SPLIT IN TWO:** `305` measured 256 dumps; the folder now holds **265**, because
`grabs_304_P1` arrived at 23:48 with nine. **A total that does not match is supposed to stop the
read** (`305` GATE §2a) **and here the discrepancy is fully accounted for — one folder, nine
files — so it is reconciled rather than obeyed.** Reproduction and new data are scored apart.

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
$dumps = Get-ChildItem .\grabs_*\*.txt -Exclude 'dlgrab_P1_*' | Where-Object { $_.DirectoryName -notlike '*grabs_304_P1*' } | Select-Object -ExpandProperty FullName
$dumps.Count
py ..\tools\dlgrab_dlorder.py $dumps *> order_sweep_306_repro.txt
Select-String -Path order_sweep_306_repro.txt -Pattern '^================'
Select-String -Path order_sweep_306_repro.txt -Pattern 'UnicodeEncodeError|Traceback'
```

**GATE §2a — `$dumps.Count` must print `256`, the summary must read
`admission=52  equal=32  permuted=4  refused=168`, and the `Traceback` search must find
NOTHING.** Any other total means a folder changed again since `306` counted it; any other split
means the bridge and the main PC disagree and **`305` is withdrawn in full, not in part.**

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
py ..\tools\dlgrab_dlorder.py (Get-ChildItem .\grabs_304_P1\*.txt).FullName *> order_sweep_306_P1.txt
Select-String -Path order_sweep_306_P1.txt -Pattern '^================'
Select-String -Path order_sweep_306_P1.txt -Pattern 'PERMUTATION' -Context 2,0
```

**GATE §2b — nine dumps, and this is NEW DATA WITH NO PRE-REGISTERED ANSWER.** What is
pre-registered is the reading: **a `PERMUTATION` here whose frame is ALSO a pixel hit in §3 is the
first counter-example to `305` §1.4 and puts the reorder back on the board.** `equal=9` says the
`299`-era rotation does not reproduce on the `303` binary in this scene, which is a bound, not a
retraction.

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
py ..\tools\stereo_eyediff.py .\grabs_299_E1\dlgrab_2928.bmp .\grabs_299_E1\dlgrab_2957.bmp .\grabs_303_C1\dlgrab_C1_4676.bmp .\grabs_pre_298cull\dlgrab_7360.bmp
```

**GATE §2c — THE READING, AND BOTH OUTCOMES ARE WRITTEN DOWN BEFORE THE RUN:**

| result | reading |
|---|---|
| `2928` and `2957` at **0 px**, `4676` a hit | **`305` §1.4 STANDS.** The reorder is real, dated to `299`, and draws nothing; `4676`'s pixels are something else and the display list is exhausted as a place to look |
| **either of `2928` / `2957` a hit** | **`305` §1.4 IS RETRACTED.** The reorder becomes a live candidate again and `305` §4's ordering of the work is wrong |
| `4676` **clean** | the frame that started all of this is not divergent under `py` and the whole of `303` §5's third frame is in question |

`dlgrab_7360` is the `VIEWRESTORE=0` falsifier arm (`298` §3) and is **inadmissible either way** —
it is in the list so that its number is on the record, not so that it can be read.

---

## §3 — ►►►► READ THE `P1` ARM. IT HAS BEEN SITTING ON DISK SINCE 23:48 AND IT IS THE POLYGON's
DATE. **OFFLINE, SECONDS.** ◄◄◄◄

`RUN-SHEET-304` §2a asked *"does the one-eye polygon appear with `GETV_STEREO_REBUILD_VIEWER=0` as
well?"* and its `P1` half is **run, clean and admissible** (§0 row 5). **Nothing about it has ever
been read.** Two documents and a prompt still carry it as owed. **`ls grabs_*` before repeating an
arm — third instance.**

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Select-String -Path run_304_P1_polygon_viewer_on.log -Pattern 'getv\]\[run\] ARM='
Select-String -Path run_304_P1_polygon_viewer_on.log -Pattern 'GETV_STEREO_REBUILD_VIEWER='
py ..\tools\stereo_eyediff.py (Get-ChildItem .\grabs_304_P1\*.bmp).FullName
```

**GATE §3 — `RUN-SHEET-304` GATE §2a's metric, and `305` §1.5's correction to it: READ `blobs` AND
`total` BESIDE `largest`, AND READ THE TOP-THREE SHARE, NOT THE LARGEST BLOB ALONE.** The polygon
**CONCENTRATES** (`C1_2336` 86% largest / 100% top-three, `V1_2732` 79% / 95%); the dead eye
**SCATTERS** (`S2_1176` 5% / 14%, `S3_1155` 8% / 23%). **A concentrated hit in any of the nine
gameplay frames is the polygon, present with the viewer fix ON, in a run whose provenance is
clean.** Then, and only on a frame that hits:

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
py ..\tools\dlgrab_eyecensus.py .\grabs_304_P1\dlgrab_P1_<the frame that hit>.txt --calls --arena
py ..\tools\dlgrab_dlorder.py .\grabs_304_P1\dlgrab_P1_<the frame that hit>.txt
```

**IF THAT FRAME READS A BALANCED CENSUS AND `ORDER IDENTICAL`, IT IS A THIRD INSTANCE OF `2336`**
— same commands, same order, different picture — **and `305` §4's per-eye CONTENTS instrument is
the only level left, on three frames now instead of two.**

---

## §4 — `P2`, THE OTHER HALF OF `304` §2a. **NEEDS THE GAME. ~10 MINUTES. RUN IT AFTER §3.**

**QUOTED VERBATIM FROM `RUN-SHEET-304` §2a — it is written out in full there because *"the same
block with"* is not a command (`296` §11), and it is written out in full here for the same
reason.** Same alley, same walk, **F9 ten times spread across the gameplay stretch**, fix OFF.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
if (-not (Test-Path .\EXPECTED-EXE-303.txt)) { throw "EXPECTED-EXE-303.txt is missing -- run RUN-SHEET-303 section 2c after the build, before any arm." }
$want = (Get-Content .\EXPECTED-EXE-303.txt).Trim()
$got  = "$((Get-FileHash .\goldeneye.exe -Algorithm SHA256).Hash) $((Get-Item .\goldeneye.exe).Length)"
if ($want -ne $got) { throw "BINARY MISMATCH -- this is NOT the 303 build. want [$want] got [$got]" }
if (Test-Path .\run_304_P2_polygon_viewer_off.log) { throw "run_304_P2_polygon_viewer_off.log EXISTS -- rename it or pick a new name (H5)." }
Get-ChildItem .\dlgrab_*.txt,.\dlgrab_*.bmp -ErrorAction SilentlyContinue | Measure-Object | Select-Object -ExpandProperty Count
$env:GETV_ARM                    = "P2"
$env:GETV_SLOTFREE               = "1"
$env:GETV_VSYNC                  = "1"
$env:GETV_FPS                    = "panel"
$env:GETV_SIMHZ                  = "query"
$env:GETV_SIMDIV                 = "1"
$env:GETV_WIDESCREEN             = "0"
$env:GETV_ROOMSCISSOR            = "1"
$env:GETV_WINDOW                 = "2560x1369"
$env:GETV_STAGE                  = "29"
$env:GETV_DIFFICULTY             = "0"
$env:GETV_STEREO                 = "1"
$env:GETV_STEREO_OFFSET          = "0"
$env:GETV_STEREO_MODE            = "1"
$env:GETV_STEREO_VIEWRESTORE     = "1"
$env:GETV_STEREO_PAIRGUARD       = "0"
$env:GETV_STEREO_REBUILD         = "1"
$env:GETV_STEREO_REBUILD_REPORT  = "1"
$env:GETV_STEREO_REBUILD_VIEWER  = "0"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_304_P2_polygon_viewer_off.log 2>&1
Select-String -Path run_304_P2_polygon_viewer_off.log -Pattern 'getv\]\[run\] ARM='
Select-String -Path run_304_P2_polygon_viewer_off.log -Pattern 'GETV_STEREO_REBUILD_VIEWER='
Select-String -Path run_304_P2_polygon_viewer_off.log -Pattern 'dlgrab_|getv\]\[shot\]'
Select-String -Path run_304_P2_polygon_viewer_off.log -Pattern 'EXCEPTION|game_exit requested'
New-Item -ItemType Directory -Force -Path .\grabs_304_P2 | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_304_P2 -Force -ErrorAction SilentlyContinue
Get-ChildItem .\grabs_304_P2 | Select-Object Name, Length
```

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
py ..\tools\stereo_eyediff.py (Get-ChildItem .\grabs_304_P2\*.bmp).FullName
```

**GATE §4 — `RUN-SHEET-304` GATE §2a's TABLE, UNCHANGED, WITH §3's `P1` READING IN THE LEFT
COLUMN. `P2` WILL SHOW DIVERGENCE IN ITS OPENING FRAMES WHATEVER HAPPENS** — the fix is off and
the dead eye is back — **so a bare hit count settles nothing and only a CONCENTRATED hit in a
GAMEPLAY frame counts.**

| `P1` (fix ON) | `P2` (fix OFF) | reading |
|---|---|---|
| a concentrated hit in a GAMEPLAY frame | a concentrated hit in a GAMEPLAY frame | **the polygon is independent of the viewer fix.** It predates `303` and the archive simply could not say so |
| a concentrated hit | none, over ten-plus grabs | **suspicious of the fix itself** — and that is a real possibility, not a slur: `303` §2 added a render path that did not run before |
| none in either, over twenty grabs | none | the polygon is rarer than `C1`'s 3-in-7 suggested, and **`C1_4676`'s broad divergence is the thing to chase instead** |

---

## §5 — **STILL OWED, STILL ONE SENTENCE: WHAT DID FC3 AND FC4 LOOK LIKE?** `RUN-SHEET-305` §4.

Nothing needs re-running and nothing has changed about this ask since `305` wrote it. The knob
took at full strength in **all 467 windows** (`clamped == straddle`), the venue was **the road**
(median **1,359** clamped/Mvtx against the cast roll's 45,000), and the counters still cannot
decide it — **`303` §3 says so in its own words.**

- `run_304_FC3_road_on.log` — `GETV_FARCLAMP=1`, the shipping default
- `run_304_FC4_road_off.log` — `GETV_FARCLAMP=0`

**One sentence about each, in your own words**, the way `303` §3's was recorded. **If the two arms
looked the same again, `RUN-SHEET-303` §0.1 is a `279` §7 null for the SECOND time and it should be
CLOSED rather than re-run a third time.** The pictures are in `grabs_304_FC3\` and `grabs_304_FC4\`.

---

## §6 — ►►►►►►►► THE ARM THAT PROVES THE EYES SEPARATE. `S3`. **IT HAS NEVER RUN, AND IT IS
STAGE 6's EXIT GATE.** ◄◄◄◄◄◄◄◄

**`258` STAGE 6's gate needs no headset** (`255` §4): desktop side-by-side at
`GETV_STEREO_OFFSET=500`, the halves cross-correlated, **the prediction written to the log BEFORE
the screenshot.** `PRIORITY-BOARD-299` `D2` has carried it as **NEVER RUN** since `297`.

**WHY IT IS ADMISSIBLE NOW AND WAS NOT BEFORE, AND THIS IS THE PART TO READ.** The standing
objection was that *a disparity measured on an eye with no world in it is a number about nothing*,
and for six sessions that objection was correct: eye 1 was empty. **`303` §2 closed that** — V1
reads eye1 `MODEL_MTX=38`, `MODEL_VTX 16/16`, `only in eye0 = 0` on every opening grab, cumulative
`viewer=0`, ZERO-REBUILD 0 of 3015 — **so GATE 4.1's four conditions are met by measurement for
the first time in this project's life.** The objection has lapsed; it was not overruled.

**SPLICED FROM `RUN-SHEET-299` §4, WITH SIX CHANGES, EVERY ONE NAMED SO IT CAN BE CHECKED:**
(1) new log name `run_306_S3_separation.log` (`H5` — a re-run gets a new name); (2) `GETV_ARM=S3`
added (`N2`/`301`, so the grabs are `dlgrab_S3_5400.*`); (3) the `EXPECTED-EXE-303.txt` binary gate
added (`301` §3c) with `299`'s bare `Get-Item` line kept beside it; (4) the `H5` log-exists guard
added; (5) `GETV_STEREO_REBUILD_VIEWER=1` stated explicitly — the knob did not exist when `299` was
written and `303` made it the default; (6) the grabs land in `.\grabs_306_S3`. **Nothing else is
changed from `299` §4.**

**STAND STILL, IN A ROOM, FACING A WALL — the engine's ray test does not cross portals. If the
log's prediction block says `CANNOT ANSWER`, move to face a wall and re-run; do not substitute an
assumed depth.**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
if (-not (Test-Path .\EXPECTED-EXE-303.txt)) { throw "EXPECTED-EXE-303.txt is missing -- run RUN-SHEET-303 section 2c after the build, before any arm." }
$want = (Get-Content .\EXPECTED-EXE-303.txt).Trim()
$got  = "$((Get-FileHash .\goldeneye.exe -Algorithm SHA256).Hash) $((Get-Item .\goldeneye.exe).Length)"
if ($want -ne $got) { throw "BINARY MISMATCH -- this is NOT the 303 build. want [$want] got [$got]" }
if (Test-Path .\run_306_S3_separation.log) { throw "run_306_S3_separation.log EXISTS -- rename it or pick a new name (H5)." }
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
Get-ChildItem .\dlgrab_*.txt,.\dlgrab_*.bmp -ErrorAction SilentlyContinue | Measure-Object | Select-Object -ExpandProperty Count
$env:GETV_ARM                   = "S3"
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
$env:GETV_DLGRAB_AT             = "5400"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_306_S3_separation.log 2>&1
Select-String -Path run_306_S3_separation.log -Pattern 'GETV_FPS=panel'
Select-String -Path run_306_S3_separation.log -Pattern 'getv\]\[stereo\]|dlgrab_|getv\]\[shot\]'
Select-String -Path run_306_S3_separation.log -Pattern 'props interpolated|simulation held to|ours: x=|game_exit requested'
Select-String -Path run_306_S3_separation.log -Pattern 'EXCEPTION'
Select-String -Path run_306_S3_separation.log -Pattern 'PREDICTION frame=|MEASURED centre depth|1/D LAW' | Select-Object -Last 12
New-Item -ItemType Directory -Force -Path .\grabs_306_S3 | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_306_S3 -Force -ErrorAction SilentlyContinue
Get-ChildItem .\grabs_306_S3 | Select-Object Name, Length, LastWriteTime
```

### 6.1 — **THE CENSUS GATE FIRST, BECAUSE IT DECIDES WHETHER THE DISPARITY MEANS ANYTHING.**
**`RUN-SHEET-299` §4.1, unchanged except for the ARM-tagged filename.**

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
py ..\tools\dlgrab_eyecensus.py .\grabs_306_S3\dlgrab_S3_5400.txt --calls --arena
```

**GATE 6.1 — ALL FOUR, on the grabbed frame's own dump:**

1. `viewport loads = 2`.
2. **`only in eye0 = 0`** — no `<-- eye1 is a STRICT SUBSET` line at all.
3. **`MODEL_MTX(3)`, `MODEL_VTX(4)` and `MODEL_COL1(5)` all NON-ZERO in BOTH eyes**, with no
   `<-- DIVERGES` marker. At `OFFSET=500` a small delta is expected and is not a failure; a **zero
   on one side is**.
4. That frame's own `rebuild] SUMMARY` line reads `eyes-rebuilt=1` with `chr+obj > 0`.

**IF 6.1 FAILS, STOP. Do not score 6.2.** A disparity measured across a dead eye is exactly the
blank-frame trap `297` §0 caught, one level up — and `295` §10.1's PASS on a black frame is this
project's own instance of it.

### 6.2 — THE DISPARITY, AND SWEEP THE FREE PARAMETER. **`RUN-SHEET-299` §4.2.**

Take the predicted fraction from **the log's LAST `MEASURED centre depth` block BEFORE the grab**
(stand still and every block is the same; the block prints the camera position, so a moved camera
is visible).

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
py ..\tools\stereo_disparity.py .\grabs_306_S3\dlgrab_S3_5400.bmp --predicted-frac <the number from the log>
py ..\tools\stereo_disparity.py .\grabs_306_S3\dlgrab_S3_5400.bmp --predicted-frac <the same number> --search 200
py ..\tools\stereo_disparity.py .\grabs_306_S3\dlgrab_S3_5400.bmp --predicted-frac <the same number> --search 500
py ..\tools\stereo_disparity.py .\grabs_306_S3\dlgrab_S3_5400.bmp --predicted-frac <the same number> --search 800
```

**`00-STATE` §6, `298` §2.1: an answer that moves with the search width IS the search width.**
`[MEASURED]` in `298`: R1's `dx` read `+199 / +229 / -499 / -799` across that sweep while R2's read
`+1` at every width. **►► AND THE PEG DETECTOR IS NO LONGER BLIND — `H1` closed in `301`, and
`306` made its alarm line printable.** If it fires, the sweep is not the only detector any more.

**GATE S3 — `RUN-SHEET-292` §5's, unchanged, and the log's numbers decide it, not the picture:**
`VERDICT PASS` (`|measured - predicted| <= 5 px` **and** the sign matches — the RIGHT eye's image
FURTHER LEFT); **the D=1000 and D=4000 predictions stand in a 4.000 ratio**, read off adjacent
lines; `props interpolated 0`, zero `simulation held to`, `ours: x=367.333`, `game_exit requested`.

**THE SIGN CONVENTION IS SETTLED FROM SOURCE (`299` §3) AND THE QUESTION IS NOT ASKED AGAIN:**
`stereo.c:233` puts **eye 0 in the LEFT half of the framebuffer**; `stereo.c:387` puts **eye 0 at
−sep/2**, so eye 0 is the **left eye**. The right eye's camera sits further right, so a fixed world
point projects FURTHER LEFT in the right half — **which `stereo_disparity.py` prints as a NEGATIVE
`dx`.**

---

## §7 — THE COMMITS. **TWO REPOS. NOTHING IS STAGED BY THIS SHEET UNTIL YOU RUN IT.**

**►► TWO RULES, TWO COMMANDS, AND `305` §5 PAID FOR THIS ONE ALREADY:** `--ignore-cr-at-eol` is a
`git diff` option and **`git status` rejects it**; a bare `git status` in the decomp prints 2,106
CRLF-dirty files, so **every `status` gets an explicit path list.** **EVERY BLOCK OPENS WITH
`git rev-parse --show-toplevel`** — `299` / `RUN-SHEET-300` §7: a git-bash path in a PowerShell
block fails SILENTLY INTO THE WRONG REPO. Read that line before anything else the block prints.

### 7a — `goldeneye-native`: the ASCII fix to three instruments

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
git rev-parse --show-toplevel
git --no-optional-locks status --short -- getv/tools/dlgrab_dlorder.py getv/tools/stereo_disparity.py getv/tools/stereo_eyediff.py
git diff --stat --ignore-cr-at-eol -- getv/tools/dlgrab_dlorder.py getv/tools/stereo_disparity.py getv/tools/stereo_eyediff.py
git add -- getv/tools/dlgrab_dlorder.py getv/tools/stereo_disparity.py getv/tools/stereo_eyediff.py
git commit -F F:\Projects\GEVR\GoldenEyeVR\COMMIT-MESSAGE-2026-09-04-native.txt
git log --oneline -1
```

**GATE §7a — the first line must end in `goldeneye-native`, `diff --stat` must name EXACTLY THREE
files, and the insertion/deletion counts must be `5 +` / `5 -`.** A larger diff means something
other than the five glyph sites changed and **the commit must not be made until it is read.**

### 7b — `GoldenEyeVR`: the documents

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR
git rev-parse --show-toplevel
git --no-optional-locks status --short -- repo/docs/00-STATE.md repo/docs/00-STATE.md.bak-306 repo/docs/PRIORITY-BOARD-299.md repo/docs/PRIORITY-BOARD-306.md repo/docs/RUN-SHEET-306.md repo/docs/306-THE-SWEEP-CRASHED-ON-AN-ARROW-AND-THE-POLYGON-RUN-WAS-ALREADY-ON-DISK.md repo/docs/NEXT-SESSION-PROMPT-306.md repo/docs/NEXT-SESSION-PROMPT-307.md
git diff --stat --ignore-cr-at-eol -- repo/docs/00-STATE.md repo/docs/PRIORITY-BOARD-299.md repo/docs/NEXT-SESSION-PROMPT-306.md
git add -- repo/docs/00-STATE.md repo/docs/00-STATE.md.bak-306 repo/docs/PRIORITY-BOARD-299.md repo/docs/PRIORITY-BOARD-306.md repo/docs/RUN-SHEET-306.md repo/docs/306-THE-SWEEP-CRASHED-ON-AN-ARROW-AND-THE-POLYGON-RUN-WAS-ALREADY-ON-DISK.md repo/docs/NEXT-SESSION-PROMPT-306.md repo/docs/NEXT-SESSION-PROMPT-307.md
git commit -F F:\Projects\GEVR\GoldenEyeVR\COMMIT-MESSAGE-2026-09-04.txt
git log --oneline -1
```

**GATE §7b — the first line must end in `GoldenEyeVR`, and `diff --stat` must name EXACTLY THREE
files: `00-STATE.md`, `PRIORITY-BOARD-299.md` and `NEXT-SESSION-PROMPT-306.md`** (the last two are
rule `2` SUPERSEDED banners, not rewrites). **The four NEW files — the three documents and
`00-STATE.md.bak-306`, which is this session's snapshot of `00-STATE` before the edit (the
`.bak-288` / `.bak-294` / `.bak-298` / `.bak-303` convention) — are untracked and appear only in
`status --short` as `??`.** A fourth file in `diff --stat` means this session touched something
it does not know about — **stop and read it.**

---

## §8 — AFTER `306`

1. **`305` §4's per-eye `MODEL_MTX` CONTENTS instrument.** Still the only level left for the
   polygon, and still deliberately not designed here — **`301` §0, and the count of filed fixes
   that were wrong is five.**
2. **`S3`'s result decides whether STAGE 6 can close.** If it passes, `D3` (S4, the mode-2
   falsifier) is what stops the pass being withdrawn later (`49`), and `D4` (R5a/b/c) is the
   frame budget with stereo on — **`P5`, against `272` §5.2's 0.890 ms CRADLE baseline.**
3. **The XR layer does not exist yet and nothing above creates it.** `258` STAGE 6 says so in its
   own words: *"NOT in this stage: OpenXR, head tracking, hand aim, vignette, HUD quad, mirror,
   `gevr_xr.c`."* **`PRIORITY-BOARD-306` GROUP `X` is where that work is ranked for the first
   time.**
4. **`H15`** — whether the order check belongs inside `dlgrab_eyecensus.py`. Unchanged.
5. **`H16` (NEW)** — an instrument that prints outside ASCII is an instrument that can die on the
   owner's machine and not on the bridge. `306` §0.
