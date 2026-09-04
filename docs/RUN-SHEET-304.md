# RUN-SHEET-304 — THE INSTRUMENT IS NEW, THE CORPUS IS OLD, AND THE SYMPTOM IS NOT AN ADMISSION FAULT

**WRITTEN OFFLINE 2026-09-03, AFTER `RUN-SHEET-303` WAS WORN IN FULL AND ITS THREE COMMITS
LANDED.** Nothing here has run. **`RUN-SHEET-303` IS DONE — §1, §2, §3, §4 AND §5. Do not re-run
any of it.**

Binary: `goldeneye.exe` **18,070,774 bytes, sha256 `45756E5A…3F92`**, `EXPECTED-EXE-303.txt`.
**§1 AND §2 NEED NO BUILD AND NO RUN AT ALL.** Only §3 launches the game, and it is optional.

## §0 — WHAT `303` SETTLED, IN ONE TABLE

| `303` read | verdict |
|---|---|
| §2 V1: eye1 `MODEL_MTX` **38**, `only in eye1 = 0`, **zero `skipped>0` frames in 3015** | **GROUP `B` CLOSES.** The viewer was the dead eye |
| §2 V2: 38/0, `only in eye0 = 18`, `viewer=541`, 372 of 3044 | reproduced `302` exactly — the A/B is not void |
| §3 FC1 far `clamped=81,076` = `straddle` exactly / FC2 `0`; near `clamped=0` both | **the knob took at full strength and the owner sees the same picture** |
| §3.1 `[getv][far]` per window: road **1.2–5.9%**, cast roll **40–71%** | **`302` §4's `13.2%` is a blend of two scenes and is comparable to nothing** |
| §4 `C1`: `arrays=366456 already-converted=0 skipped=0` | **`292`'s double conversion is DEAD.** GROUP `C`'s hypothesis with it |
| §5 one-eye polygon in `V1_2732`, `C1_2336`, `C1_4676`, census `39/39` `only in eye0 = 0` | **the first eye fault that is NOT an admission fault** |
| §6 `stereo_eyediff.py`, selftest **14 checks 0 failed** | **`H9` CLOSES.** The second eye is the reference frame |

**WHAT IS OWED: §1 (wear + sweep), then §2 (the polygon). §3 is the far clamp if it is still
wanted. §4 is one `Move-Item`. §5 is two commits.**

---

## §1 — WEAR `stereo_eyediff.py` ON THE MAIN PC, THEN SWEEP EVERY GRAB THIS PROJECT HAS

**OFFLINE. NO BUILD. NO GAME.** `H7` is why the wear is here at all: `303` ran the selftest under
the bridge's `python3`, and the main PC runs `py`. It costs seconds.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
py getv\tools\stereo_eyediff.py --selftest
```

**►►►► §1 IS WORN, 2026-09-03. `304-THE-SWEEP-FOUND-A-FALSE-NEGATIVE-IN-ITS-OWN-INSTRUMENT` IS
WHAT IT PRODUCED, AND THE GATES BELOW ARE KEPT AS WRITTEN (RULE `2`). WHAT ACTUALLY HAPPENED:
256 frames, 175 REFUSED as mono, 40 clean, 41 divergent — AND THE SWEEP FOUND A FALSE NEGATIVE IN
THE TOOL, WHICH NOW DIFFERENCES PER CHANNEL AND PASSES 16 CHECKS. THE SELFTEST GATE BELOW READS
`16`, NOT `14`.**

**GATE §1a — `stereo_eyediff selftest: 16 checks, 0 failed` and `VERDICT PASS`.** The checks that
matter are not the arithmetic ones: **`B` injects a 50×50 blob and fails if the alarm goes quiet**
(`H1` sat in this repo for months because its alarm could never fire), **`C` proves the two masks
actually mask**, and **`D2` proves a mono dump is REFUSED by name.**

Then the sweep. **`[MEASURED]` on the bridge: 21 grab folders, 238 BMPs, of which 88 carry two
`gSPViewport` loads and are readable; ~0.47 s per frame, so the whole corpus is under a minute.**

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
$bmps = Get-ChildItem -Path .\grabs_* -Recurse -Filter *.bmp | Sort-Object FullName
"$($bmps.Count) BMPs found"
py ..\tools\stereo_eyediff.py @($bmps.FullName) *> eyediff_sweep_304.txt
Select-String -Path eyediff_sweep_304.txt -Pattern 'ONE-EYE DIVERGENCE' -Context 6,0 |
  Select-Object -First 40
Select-String -Path eyediff_sweep_304.txt -Pattern '^================' | Select-Object -Last 1
(Select-String -Path eyediff_sweep_304.txt -Pattern 'REFUSED').Count
```

**GATE §1b — THE THREE KNOWN HITS MUST APPEAR**, or the tool did not survive the trip to the main
PC: `dlgrab_C1_2336` (2,196 px), `dlgrab_C1_4676` (4,544 px, 900 blobs), `dlgrab_V1_2732`
(5,947 px). **GATE §1c — every mono grab must print `REFUSED`, not a verdict.** `301` D1/D2,
`302` S3's D3 strays and all of `303` FC1/FC2 are mono; a number where a refusal belongs means the
dump beside the BMP was not read and every other number is suspect.

**►►►► WHAT THIS SWEEP IS ACTUALLY FOR, AND IT IS NOT THE THREE FRAMES WE ALREADY KNOW ABOUT.**
88 stereo frames were taken across `298`–`303` by an instrument that could not see this class of
fault. **Any hit in `298`, `299` or `301` dates the polygon to before the viewer fix and detaches
it from `303` entirely.** A sweep that finds hits ONLY in `303`'s own grabs is also an answer, and
a more uncomfortable one.

---

## §2 — THE POLYGON. **`dlgrab_C1_4676` FIRST, AND IT IS ALL OFFLINE.**

**DO NOT INHERIT AN EXPLANATION. BOTH OF THE OBVIOUS ONES ARE EXCLUDED BY MEASUREMENT:** it is not
an admission loss (`39/39`, `only in eye0 = 0`, `303` §5) and it is not `292`'s double conversion
(`already-converted=0` of 366,456, `303` §4). **`301` §0's rule is the whole of this section.**

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
py ..\tools\stereo_eyediff.py grabs_303_C1\dlgrab_C1_4676.bmp grabs_303_C1\dlgrab_C1_2336.bmp grabs_303_V1\dlgrab_V1_2732.bmp
py ..\tools\dlgrab_eyecensus.py grabs_303_C1\dlgrab_C1_4676.txt
py ..\tools\dlgrab_eyecensus.py grabs_303_C1\dlgrab_C1_4676.txt --calls --arena
py ..\tools\dlgrab_eyecensus.py grabs_303_C1\dlgrab_C1_2336.txt --calls --arena
```

**READ THESE THREE THINGS, IN THIS ORDER:**

1. **The `eye0` / `eye1` MOVEMEM line the census prints by itself** — the viewport load plus the
   per-eye view copies. **If the two eyes name the SAME view-matrix address, the second eye is
   drawing with the first eye's view**, and that is a different fault from anything on the board.
2. **`--arena`.** `293` measured `MODEL_VTX fresh=0` in every dump, back when the second eye
   allocated nothing. **With `303`'s rebuild admitting the viewer, `fresh` should no longer be
   zero** — and if it still is, the rebuild is producing state nobody consumes.
3. **`4676`'s `mad` of 6.409 against every other frame's 3.4–4.1.** That frame is diverging
   BROADLY — 900 blobs — where the other two carry one polygon. **Establish whether it is the same
   fault at greater amplitude or a second one**, and say which before proposing anything.

**GATE §2 — THIS SECTION PRODUCES A DIAGNOSIS OR IT PRODUCES NOTHING. It does not produce a
patch.** Four filed fixes in this project have been wrong (`H1`, `H3`, `298` §4.4, `302` §3c) and
every one was caught by following the call rather than re-reading the note.

---

## §2a — **DATE THE POLYGON WITH A RUN, BECAUSE THE ARCHIVE CANNOT.** `304` §2.

**THE QUESTION: does the one-eye polygon appear with `GETV_STEREO_REBUILD_VIEWER=0` as well?** If
it does, it is independent of `303`'s fix and always was. **The corpus cannot answer this** — the
only pre-`303` frames carrying the signature are announced by no log, by five logs, or by a
falsifier arm whose guard is supposed to fire (`279` §2, `298` §3).

**Both arms: the ALLEY where `303` §5's frames were taken — the gameplay stretch after the
opening, the same walk V1 and C1 made. Press F9 TEN TIMES, spread across the walk.** The polygon
moves with Bond's bob (`[REPORTED]`), so more grabs is the whole method; three frames in seven
caught it in `C1`.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
if (-not (Test-Path .\EXPECTED-EXE-303.txt)) { throw "EXPECTED-EXE-303.txt is missing -- run RUN-SHEET-303 section 2c after the build, before any arm." }
$want = (Get-Content .\EXPECTED-EXE-303.txt).Trim()
$got  = "$((Get-FileHash .\goldeneye.exe -Algorithm SHA256).Hash) $((Get-Item .\goldeneye.exe).Length)"
if ($want -ne $got) { throw "BINARY MISMATCH -- this is NOT the 303 build. want [$want] got [$got]" }
if (Test-Path .\run_304_P1_polygon_viewer_on.log) { throw "run_304_P1_polygon_viewer_on.log EXISTS -- rename it or pick a new name (H5)." }
Get-ChildItem .\dlgrab_*.txt,.\dlgrab_*.bmp -ErrorAction SilentlyContinue | Measure-Object | Select-Object -ExpandProperty Count
$env:GETV_ARM                    = "P1"
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
$env:GETV_STEREO_REBUILD_VIEWER  = "1"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_304_P1_polygon_viewer_on.log 2>&1
Select-String -Path run_304_P1_polygon_viewer_on.log -Pattern 'getv\]\[run\] ARM='
Select-String -Path run_304_P1_polygon_viewer_on.log -Pattern 'GETV_STEREO_REBUILD_VIEWER='
Select-String -Path run_304_P1_polygon_viewer_on.log -Pattern 'dlgrab_|getv\]\[shot\]'
Select-String -Path run_304_P1_polygon_viewer_on.log -Pattern 'EXCEPTION|game_exit requested'
New-Item -ItemType Directory -Force -Path .\grabs_304_P1 | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_304_P1 -Force -ErrorAction SilentlyContinue
Get-ChildItem .\grabs_304_P1 | Select-Object Name, Length
```

**P2 is the same block with the fix OFF, written out in full because *"the same block with"* is
not a command (`296` §11):**

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

Then the detector on both:

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
py ..\tools\stereo_eyediff.py (Get-ChildItem .\grabs_304_P1\*.bmp).FullName
py ..\tools\stereo_eyediff.py (Get-ChildItem .\grabs_304_P2\*.bmp).FullName
```

### GATE §2a — **READ `blobs` AND `total` BESIDE `largest`, OR THE TWO FAULTS WILL BE SCORED AS ONE.**

**P2 WILL SHOW DIVERGENCE IN ITS OPENING FRAMES WHATEVER HAPPENS** — the fix is off and the dead
eye is back — so a bare hit count settles nothing. **The polygon CONCENTRATES and the dead eye
SCATTERS** (`304` §1.4): `C1_2336` is 86% of its differing pixels in one blob and `V1_2732` 79%,
against `S2_1176`'s 5% and `S3_1155`'s 8%.

| P1 (fix ON) | P2 (fix OFF) | reading |
|---|---|---|
| a concentrated hit in a GAMEPLAY frame | a concentrated hit in a GAMEPLAY frame | **the polygon is independent of the viewer fix.** It predates `303` and the archive simply could not say so |
| a concentrated hit | none, over ten-plus grabs | **suspicious of the fix itself** — and that is a real possibility, not a slur: `303` §2 added a render path that did not run before |
| none in either, over twenty grabs | none | the polygon is rarer than `C1`'s 3-in-7 suggested, and **`C1_4676`'s broad divergence is the thing to chase instead** |

**GRAB IN GAMEPLAY, NOT IN THE OPENING.** The opening frames are where the dead eye lives in P2 and
they cannot separate the two faults.

---

## §3 — FC3 / FC4, **THE FAR CLAMP AT THE VENUE THE COMPLAINT CAME FROM.** Optional.

**ONLY RUN THIS IF THE FAR CLAMP IS STILL WANTED AS A QUESTION.** `303` §3 left it unanswered, not
false, and `GETV_FARCLAMP` stays at its default `1` either way.

**THE VENUE IS THE ROAD, NOT THE LOOP.** `[REPORTED]`: *"in the level looking down the road in the
distance. same level that had the car prop in the road."* **Do not die into the cast roll** — that
is where `303` §3 went wrong. Walk to the longest sight line, **stand still**, and press F9 four
times pointed down it.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
if (-not (Test-Path .\EXPECTED-EXE-303.txt)) { throw "EXPECTED-EXE-303.txt is missing -- run RUN-SHEET-303 section 2c after the build, before any arm." }
$want = (Get-Content .\EXPECTED-EXE-303.txt).Trim()
$got  = "$((Get-FileHash .\goldeneye.exe -Algorithm SHA256).Hash) $((Get-Item .\goldeneye.exe).Length)"
if ($want -ne $got) { throw "BINARY MISMATCH -- this is NOT the 303 build. want [$want] got [$got]" }
if (Test-Path .\run_304_FC3_road_on.log) { throw "run_304_FC3_road_on.log EXISTS -- rename it or pick a new name (H5)." }
Get-ChildItem .\dlgrab_*.txt,.\dlgrab_*.bmp -ErrorAction SilentlyContinue | Measure-Object | Select-Object -ExpandProperty Count
$env:GETV_ARM         = "FC3"
$env:GETV_SLOTFREE    = "1"
$env:GETV_VSYNC       = "1"
$env:GETV_FPS         = "panel"
$env:GETV_WIDESCREEN  = "0"
$env:GETV_ROOMSCISSOR = "1"
$env:GETV_WINDOW      = "2560x1369"
$env:GETV_STAGE       = "29"
$env:GETV_DIFFICULTY  = "0"
$env:GETV_DEPTHCLAMP  = "1"
$env:GETV_FARCLAMP    = "1"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_304_FC3_road_on.log 2>&1
Select-String -Path run_304_FC3_road_on.log -Pattern 'getv\]\[run\] ARM='
Select-String -Path run_304_FC3_road_on.log -Pattern 'GETV_FARCLAMP='
Select-String -Path run_304_FC3_road_on.log -Pattern 'getv\]\[depthclamp\]'
Select-String -Path run_304_FC3_road_on.log -Pattern '\[getv\]\[far\]'  | Select-Object -Last 1
Select-String -Path run_304_FC3_road_on.log -Pattern '\[getv\]\[near\]' | Select-Object -Last 1
Select-String -Path run_304_FC3_road_on.log -Pattern 'dlgrab_|getv\]\[shot\]'
Select-String -Path run_304_FC3_road_on.log -Pattern 'EXCEPTION|game_exit requested'
New-Item -ItemType Directory -Force -Path .\grabs_304_FC3 | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_304_FC3 -Force -ErrorAction SilentlyContinue
Get-ChildItem .\grabs_304_FC3 | Select-Object Name, Length
```

**FC4 is the same block with `$env:GETV_ARM = "FC4"`, `$env:GETV_FARCLAMP = "0"`, log
`run_304_FC4_road_off.log`, grabs into `grabs_304_FC4`.** It is written out in full below rather
than delegated, because *"the same block with"* is not a command (`296` §11).

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
if (-not (Test-Path .\EXPECTED-EXE-303.txt)) { throw "EXPECTED-EXE-303.txt is missing -- run RUN-SHEET-303 section 2c after the build, before any arm." }
$want = (Get-Content .\EXPECTED-EXE-303.txt).Trim()
$got  = "$((Get-FileHash .\goldeneye.exe -Algorithm SHA256).Hash) $((Get-Item .\goldeneye.exe).Length)"
if ($want -ne $got) { throw "BINARY MISMATCH -- this is NOT the 303 build. want [$want] got [$got]" }
if (Test-Path .\run_304_FC4_road_off.log) { throw "run_304_FC4_road_off.log EXISTS -- rename it or pick a new name (H5)." }
Get-ChildItem .\dlgrab_*.txt,.\dlgrab_*.bmp -ErrorAction SilentlyContinue | Measure-Object | Select-Object -ExpandProperty Count
$env:GETV_ARM         = "FC4"
$env:GETV_SLOTFREE    = "1"
$env:GETV_VSYNC       = "1"
$env:GETV_FPS         = "panel"
$env:GETV_WIDESCREEN  = "0"
$env:GETV_ROOMSCISSOR = "1"
$env:GETV_WINDOW      = "2560x1369"
$env:GETV_STAGE       = "29"
$env:GETV_DIFFICULTY  = "0"
$env:GETV_DEPTHCLAMP  = "1"
$env:GETV_FARCLAMP    = "0"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_304_FC4_road_off.log 2>&1
Select-String -Path run_304_FC4_road_off.log -Pattern 'getv\]\[run\] ARM='
Select-String -Path run_304_FC4_road_off.log -Pattern 'GETV_FARCLAMP='
Select-String -Path run_304_FC4_road_off.log -Pattern 'getv\]\[depthclamp\]'
Select-String -Path run_304_FC4_road_off.log -Pattern '\[getv\]\[far\]'  | Select-Object -Last 1
Select-String -Path run_304_FC4_road_off.log -Pattern '\[getv\]\[near\]' | Select-Object -Last 1
Select-String -Path run_304_FC4_road_off.log -Pattern 'dlgrab_|getv\]\[shot\]'
Select-String -Path run_304_FC4_road_off.log -Pattern 'EXCEPTION|game_exit requested'
New-Item -ItemType Directory -Force -Path .\grabs_304_FC4 | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_304_FC4 -Force -ErrorAction SilentlyContinue
Get-ChildItem .\grabs_304_FC4 | Select-Object Name, Length
```

### ►►►► GATE §3 — **THE VENUE GATE IS PER WINDOW, AND THE CUMULATIVE LINE IS NOT ADMISSIBLE.**

`[getv][far]` is a running total and these runs contain two scenes 15x apart (`303` §3.1), so the
last line is a weighted average of wherever you walked. **The gate is the per-window rate over the
frames you were looking down the road, and it must reach `302` D3's `3.9–5.9%`.** `303`'s arms
managed **1.2–2.3%** and that is why they could not answer. **A run that stays under 3% is a
`279` §7 null however clean the arms look, and it should be said so rather than scored.**

Then, and only then, the eyes: **FC3 clean and FC4 flickering** is the fix; **both the same** means
the far clamp is not what collapses it and `GETV_DEPTHCLAMP=0` on the same road is next; **both
clean** means FC4 did not restore the behaviour — check its `[getv][farclamp]` banner first.

---

## §4 — HOUSEKEEPING. ONE COMMAND, AND IT PREVENTS A `279` §2.

`grabs_303_V1\` contains four files that are `302` §4's, swept up by V1's closing `Move-Item`
because they were sitting loose in `build-windows` (`303` §7). **Nothing is contaminated** — every
census in `303` ran on `dlgrab_V1_*` — **but the folder is now mislabelled and that is exactly how
`278` §1 mislabelled six files on timestamp alone.**

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
New-Item -ItemType Directory -Force -Path .\grabs_302_D3 | Out-Null
Move-Item -Path .\grabs_303_V1\dlgrab_D3_*.txt,.\grabs_303_V1\dlgrab_D3_*.bmp -Destination .\grabs_302_D3 -Force
Get-ChildItem .\grabs_302_D3 | Select-Object Name, Length
Get-ChildItem .\grabs_303_V1 | Select-Object Name, Length
```

`grabs_303_V1` must end up holding **`dlgrab_V1_*` and nothing else**.

---

## §5 — ~~THE COMMITS.~~ **WORN 2026-09-03: `f3c9a04` (native) / `71ac3b3` (GoldenEyeVR).**

**►►►► §5 IS DONE AND MUST NOT BE RE-RUN. §5a BELOW IS THE FOLLOW-UP COMMIT** — `304` §1's
sweep was run after those two commits landed, and the false negative it found changed the tool
and four documents. **The `e` message files were restored from git after the fact so they still
describe the commits they produced (`git show -s --format=%B`); use the `f` files for §5a.**
ORIGINAL HEADER, KEPT BECAUSE RULE `2` DELETES NOTHING: THE COMMITS. TWO REPOS, AND NEITHER HAS A
TRAP THIS TIME.

`303`'s three commits are **already in** (`94cdf01c` / `c26c58d` / `d393860`) and all three trees
were clean afterwards. **This is only the new tool and the new documents. There is no decomp
change and no regen: `stereo_eyediff.py` is a host-side tool that is not compiled into the
binary.**

```powershell
# 5.0 -- THE STAGED SET MUST EQUAL THE DIRTY SET. Check BEFORE staging (`303` §5.0's lesson).
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
git --no-optional-locks status --short -- getv/
Set-Location F:\Projects\GEVR\GoldenEyeVR
git --no-optional-locks status --short -- repo/docs

# 5.1 -- native: the tool only
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
git rev-parse --show-toplevel
git add getv/tools/stereo_eyediff.py
git commit -F ..\COMMIT-MESSAGE-2026-09-03e-native.txt
git log --oneline -1

# 5.2 -- documents
Set-Location F:\Projects\GEVR\GoldenEyeVR
git rev-parse --show-toplevel
git add repo/docs
git commit -F .\COMMIT-MESSAGE-2026-09-03e.txt
git log --oneline -1
```

**Anything dirty in `getv/` that is not `getv/tools/stereo_eyediff.py` is something this sheet did
not expect — stop and read it before staging.** `repo/docs` will also carry `00-STATE.md.bak-303`
and `PRIORITY-BOARD-299.md.bak-303`, which follow the `.bak-288` / `.bak-294` / `.bak-298`
precedent already in the tree.

**No attribution trailers in either message.**

---

## §5a — THE FOLLOW-UP COMMIT. **THE COLOUR FIX AND `304`'s DOCUMENTS.**

Two repos again, no decomp change, no regen — `stereo_eyediff.py` is host-side and compiles into
nothing.

```powershell
# 5a.0 -- the staged set must equal the dirty set. Check BEFORE staging.
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
git --no-optional-locks status --short -- getv/
Set-Location F:\Projects\GEVR\GoldenEyeVR
git --no-optional-locks status --short -- repo/docs

# 5a.1 -- native: the tool's colour fix
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
git rev-parse --show-toplevel
py getv\tools\stereo_eyediff.py --selftest
git add getv/tools/stereo_eyediff.py
git commit -F ..\COMMIT-MESSAGE-2026-09-03f-native.txt
git log --oneline -1

# 5a.2 -- documents
Set-Location F:\Projects\GEVR\GoldenEyeVR
git rev-parse --show-toplevel
git add repo/docs
git commit -F .\COMMIT-MESSAGE-2026-09-03f.txt
git log --oneline -1
```

**GATE §5a — `16 checks, 0 failed` BEFORE the `git add`**, because the whole of this commit is
that the previous version of the file was wrong and the selftest is what proves the new one is
not. **Expected dirty set: `M getv/tools/stereo_eyediff.py` alone in native, and in `repo/docs`
`M 00-STATE.md`, `M 303-…md`, `M PRIORITY-BOARD-299.md`, `M RUN-SHEET-304.md` plus the untracked
`304-THE-SWEEP-FOUND-A-FALSE-NEGATIVE-IN-ITS-OWN-INSTRUMENT.md`.** Anything else is something this
sheet did not expect — read it before staging.

**No attribution trailers in either message.**

---

## §6 — AFTER `304`

- **GROUP `C` is the board's live work** and it now has a picture, a detector and no explanation.
- **`C1a`**: `C1`'s zero is one run and one route. Bound it before quoting it as general.
- **`H11` / `H12` / `H13`** are the three `LOW` holes `303` filed: the far line's mixed counters,
  the far census's cumulative blend, and the constant seven commands the second eye never gets.
- **GROUP `D`** is still unblocked and `D1` is still `LOW`.
- **GROUP `E1`**: `bg.c:583`'s `getROOMID_isRendered` has now survived four arms untested.
