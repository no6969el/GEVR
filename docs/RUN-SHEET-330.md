# `RUN-SHEET-330` -- **`K-6` THEN `K-3`, AT THE CHAIR. EIGHT BLOCKS, AND THE FIRST TWO RUNS THIS PROJECT HAS TAKEN SINCE `325`**

**GREEN-LIT 2026-09-05 (owner):** `PLAN-330-CHAIR` with forks **`D1`** (`K-3` DESK, awake, not
worn), **`E1`** (fires at the default frame `120`, `GETV_XR_KILL_AT` not raised), **`F2`** (stdout
`*>` captured on **both** `K-6` and `K-3`, load-bearing per `PLAN-330-CHAIR` section `2.2`),
**`G1`** (`K-6` -> report -> `K-3` only if `K-6` lands; **any `[getv]` line with the knobs unset
falsifies `K-6` and `K-3` does not run**).

**ALSO LOCKED BY THE OWNER, AND THEY ARE NOT FORKS:**

1. **THE STALE `SESSION CREATE ONLY -- there is no xrWaitFrame in this build` STRING STAYS
   UNPATCHED** (`301`). The writeup reads it as stale, never as a statement about the binary.
2. **A GHOSTED OR "NOT RESPONDING" WINDOW DURING THE FREEZE IS A SIDECAR CONDITION, NOT PART OF
   THE `K-3` VERDICT, AND `N` IS NOT RETUNED AFTERWARDS.**
3. **BOTH BANDS ARE REPORTED** -- the instrument's `10%` verdict line **is the score**, the
   `PLAN-329` section `5.2` `0.500%` arithmetic is computed beside it, **and neither is adjusted
   after the numbers are seen.**
4. **`vr329` IS STAGED FOR THE RUNS AND `plain329` GOES BACK** (BLOCK `1`, BLOCK `7`).
5. **THE REPORT'S CWD IS `getv\build-windows`**, harvested to
   `repo\xr\getv_xrkill_report_330_DESK.txt`.
6. **`B1`: A NON-BLOCKING `xrWaitFrame` IS `K-3 NEITHER`, IT MANDATES `B2`, AND IT IS NOT A KILL.**

►► **BLOCKS ARE HANDED TO THE HELPER ONE AT A TIME AND NOTHING IS LAUNCHED AHEAD OF THE
HAND-OFF.** As of this line: **no block has been run, no game has been launched, SteamVR has not
been started, nothing is staged and nothing is committed.** ◄◄

## section 1 -- **WHAT IS ON DISK, MEASURED, AND WHY BLOCK `1` EXISTS**

`[MEASURED]` `330`, on the bridge:

| file | md5 | length |
|---|---|---|
| `goldeneye.exe` | `037EDBD61D293C1CA0419418927715D7` | `18,075,663` |
| `goldeneye.exe.plain329` | `037EDBD61D293C1CA0419418927715D7` | `18,075,663` |
| `goldeneye.exe.vr329` | `70BF2580239CD6B7C402C063D89B976F` | `18,101,808` |
| `openxr_loader.dll` | `E00CB2890D93D5E33D675BCA3113B1B0` | `2,669,568` |

**`goldeneye.exe` IS THE PLAIN BINARY AND BOTH RUNS NEED THE `-Vr` ONE**, so BLOCK `1` stages it
and BLOCK `7` puts the plain one back (`328`'s gate deviation, recorded in `00-STATE`, not
repeated by accident). **NO BLOCK IN THIS SHEET REBUILDS ANYTHING** -- a rebuild would change the
md5 this sheet names.

---

## BLOCK 0 -- **PRE-FLIGHT. NO GAME, NO SteamVR, NOTHING MOVES**

**ALREADY SATISFIED OFF THE DISK, `330`, BEFORE THE GREEN-LIGHT** -- the four md5s and lengths in
section `1`, `Subsystem 00000003 (Windows CUI)` on `goldeneye.exe.vr329`, and **no
`getv_xrkill_report.txt` anywhere in the tree** were all read on the bridge. **SO THIS BLOCK IS
NOT HANDED OVER AND BLOCK `1` GOES FIRST.** It is kept here as the re-take if the tree is touched
between now and the runs, or if BLOCK `1`'s md5 disagrees.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
$bw = 'F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows'
$xr = 'F:\Projects\GEVR\GoldenEyeVR\repo\xr'
$objdump = 'C:\msys64\mingw64\bin\objdump.exe'
foreach ($n in 'goldeneye.exe','goldeneye.exe.vr329','goldeneye.exe.plain329','openxr_loader.dll','SDL2.dll') {
  $p = Join-Path $bw $n
  if (Test-Path $p) {
    "{0,-24} {1}  {2}" -f $n, (Get-FileHash $p -Algorithm MD5).Hash, (Get-Item $p).Length
  } else {
    "{0,-24} MISSING" -f $n
  }
}
"---- PE subsystem of the binary that will be staged (MUST read 3) ----"
& $objdump -p (Join-Path $bw 'goldeneye.exe.vr329') | Select-String 'Subsystem'
"---- any stale report file, anywhere it could be (EXPECT NONE) ----"
foreach ($p in (Join-Path $bw 'getv_xrkill_report.txt'), (Join-Path $xr 'getv_xrkill_report.txt')) {
  if (Test-Path $p) { "STALE: $p  " + (Get-Item $p).LastWriteTime } else { "absent: $p" }
}
"---- end ----"
```

**`[PREDICTION] P-0`: the four md5s match section `1` exactly, `SDL2.dll` is present, the
subsystem reads `3`, and there is no `getv_xrkill_report.txt` anywhere.**
**FALSIFIED BY:** any md5 mismatch -- **then the tree is not what `329` left and the sheet stops
here**; a missing `openxr_loader.dll` beside the exe -- `RUN-SHEET-326` BLOCK `5` puts it there;
subsystem `2` -- **then `-GuiSubsystem` was used, the process has no stdout, fork `F2` is
impossible and `PLAN-330` section `2.3` is wrong**; or a stale report file -- **rename it before
anything runs, or `K-3`'s harvest will pick up somebody else's numbers.**

---

## BLOCK 1 -- **STAGE `vr329` AS `goldeneye.exe`. THIS IS THE ONLY THING THAT MOVES BEFORE A RUN**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
$bw = 'F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows'
Copy-Item (Join-Path $bw 'goldeneye.exe.vr329') (Join-Path $bw 'goldeneye.exe') -Force
"staged goldeneye.exe  " + (Get-FileHash (Join-Path $bw 'goldeneye.exe') -Algorithm MD5).Hash + "  " + (Get-Item (Join-Path $bw 'goldeneye.exe')).Length
"expected              70BF2580239CD6B7C402C063D89B976F  18101808"
```

**`[PREDICTION] P-1`: the two lines agree.**
**FALSIFIED BY:** any disagreement. **DO NOT LAUNCH ANYTHING IF THEY DISAGREE** -- every result
below is a claim about a binary identified by that md5.

---

## BLOCK 2 -- ►► **`K-6`. `-Vr` BINARY, ALL KNOBS UNSET, SteamVR CLOSED** ◄◄

**BEFORE PASTING: close SteamVR completely** (`vrmonitor`, `vrserver`, `vrcompositor` all gone).
This block **launches the game and does not return until the game exits.** Play far enough to be
sure several hundred frames have rendered -- **frame `120` is the number that matters and it must
be passed with room** -- then quit the game normally.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Get-Process vrmonitor,vrserver,vrcompositor -ErrorAction SilentlyContinue | Select-Object Name,Id
"---- the line above must be EMPTY. If it is not, close SteamVR and paste again. ----"
$bw  = 'F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows'
$log = 'F:\Projects\GEVR\GoldenEyeVR\repo\xr\k6_330_stdout.log'
Set-Location $bw
"launching goldeneye.exe with EVERY GETV_ KNOB UNSET. Play, then quit normally."
& .\goldeneye.exe *> $log
"game exited $LASTEXITCODE"
"log bytes " + (Get-Item $log).Length
```

**`[PREDICTION] K-6a`: the game boots, reaches gameplay and plays with normal controls, and the
log is non-empty.**
**FALSIFIED BY:** a boot that does not reach gameplay, a crash, a loader error dialog, **or a
`0`-byte log -- which under a subsystem-`3` binary means the capture itself failed and BLOCK `3`
cannot score anything.**

---

## BLOCK 3 -- **`K-6` SCORED, AND THE SIDECAR WRITTEN IN THE SAME PASTE**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
$bw  = 'F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows'
$xr  = 'F:\Projects\GEVR\GoldenEyeVR\repo\xr'
$log = Join-Path $xr 'k6_330_stdout.log'
"---- [getv][vr] lines (MUST BE 0) ----"
(Select-String -Path $log -Pattern '\[getv\]\[vr\]' | Measure-Object).Count
"---- [getv][xrkill] lines (MUST BE 0) ----"
(Select-String -Path $log -Pattern '\[getv\]\[xrkill\]' | Measure-Object).Count
"---- every [getv] line of any kind, so the absence is READ and not assumed ----"
Select-String -Path $log -Pattern '\[getv\]' | ForEach-Object { $_.Line.Trim() }
"---- report file with the knobs unset (MUST BE absent) ----"
if (Test-Path (Join-Path $bw 'getv_xrkill_report.txt')) { 'PRESENT -- K-6c FALSIFIED' } else { 'absent' }
"---- the sidecar. Edit the two quoted values on the next two lines FIRST if they are wrong. ----"
$cond  = 'DESK'
$notes = 'K-6 baseline: all GETV_ knobs unset, SteamVR closed, played to gameplay and quit normally.'
$side  = Join-Path $xr 'getv_xrkill_330_K6_conditions.txt'
$lines = @(
  'run           K-6 (PLAN-330-CHAIR section 3), 330',
  ('condition     ' + $cond),
  ('time_local    ' + (Get-Date -Format 'yyyy-MM-dd HH:mm:ss')),
  ('exe_md5       ' + (Get-FileHash (Join-Path $bw 'goldeneye.exe') -Algorithm MD5).Hash),
  ('exe_len       ' + (Get-Item (Join-Path $bw 'goldeneye.exe')).Length),
  'exe_label     goldeneye.exe.vr329 staged as goldeneye.exe',
  'knobs         ALL GETV_ UNSET',
  'steamvr       CLOSED (vrmonitor, vrserver, vrcompositor all absent at launch)',
  'headset       not required for this run',
  'stdout_log    repo\xr\k6_330_stdout.log',
  ('notes         ' + $notes)
)
Set-Content -Path $side -Value $lines -Encoding ASCII
"sidecar written: $side"
Get-Content $side
```

**`[PREDICTION] K-6b/K-6c`: both counts are `0`, the `[getv]` listing is empty, and no report file
exists.**
**FALSIFIED BY:** any `[getv][vr]` or `[getv][xrkill]` line with the knobs unset, or a report file
appearing. ►► **EITHER OF THOSE MEANS THE GATE IS NOT A GATE, `K-9` FALLS WITH IT, AND UNDER FORK
`G1` `K-3` DOES NOT RUN.** ◄◄ A `[getv]` line that is neither `vr` nor `xrkill` (budget, pacing,
census) is **not** a falsifier -- those knobs are unset too, so the listing is expected empty, but
an unrelated `[getv]` line is a note, not a failure.

---

## BLOCK 4 -- ►► **THE GATE. STOP HERE AND REPORT `K-6` BEFORE `K-3` IS LAUNCHED** ◄◄

**Paste BLOCK `3`'s output back and stop.** Under fork `G1`, `K-3` runs in the same sitting
**only if `K-6` landed on all three counts**. This is not ceremony: `K-3`'s reading is a claim
about a gated binary, and an ungated one would make the loop's own output unattributable.

**AND `K-6` IS A RESULT IN ITS OWN RIGHT.** It closes `K-9`'s named dependency, carried since
`328`, and it is the first time the `-Vr` binary has been observed doing anything at all.

---

## BLOCK 5 -- ►► **`K-3`. THE RUN THIS PROJECT HAS OWED SINCE `322`** ◄◄

**BEFORE PASTING:**

1. **SteamVR UP**, `vrmonitor` / `vrserver` / `vrcompositor` running, dashboard dismissed, **no
   other OpenXR client running** (no `gevr_xr_slice*` processes).
2. **HMD AWAKE.** Under fork `D1` it sits on the desk, awake, **not worn**. Without an awake
   system `xrGetSystem` returns `-35` and that is **a refusal, not a measurement**.
3. ►► **THE GAME WILL FREEZE.** `3.3 s` at best; up to `13.3 s` if both poll budgets are spent
   (`PLAN-330-CHAIR` section `2.5`). **The window may go white or say "not responding". THAT IS A
   CONDITION OF THE RUN, NOT A RESULT. DO NOT KILL THE PROCESS** -- and if it must be killed, the
   report file already holds every line written up to that moment, and **the kill goes in the
   sidecar.** ◄◄
4. **THE FIRST `[getv][xrkill]` LINE WILL SAY `SESSION CREATE ONLY -- there is no xrWaitFrame in
   this build`. THAT STRING IS STALE** (`PLAN-330-CHAIR` section `2.1`): it is `328`'s text left
   in `port_render.c`, `K-7` measured `xrWaitFrame` in this binary, and **it is not fixed in this
   session on purpose** (`301`).

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Get-Process vrmonitor,vrserver,vrcompositor -ErrorAction SilentlyContinue | Select-Object Name,Id
"---- the three lines above MUST be present. If they are not, start SteamVR and paste again. ----"
$bw  = 'F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows'
$log = 'F:\Projects\GEVR\GoldenEyeVR\repo\xr\k3_330_stdout.log'
$env:GETV_VR = '1'
$env:GETV_XR_KILL = '1'
"knobs set: GETV_VR=" + $env:GETV_VR + "  GETV_XR_KILL=" + $env:GETV_XR_KILL + "  GETV_XR_KILL_AT unset (default 120)"
Set-Location $bw
"launching. Reach gameplay and let it render. The freeze is the instrument. Quit normally after it returns."
& .\goldeneye.exe *> $log
"game exited $LASTEXITCODE"
"log bytes " + (Get-Item $log).Length
Remove-Item Env:GETV_VR,Env:GETV_XR_KILL -ErrorAction SilentlyContinue
```

**`[PREDICTION] K-3-REACH`: the log contains an `ARMED for frame 120` line, then
`SESSION LIVE IN THE GAME PROCESS`, then the `ARM A` banner, then a `K-3` verdict.**
**FALSIFIED BY:** a refusal line instead -- **which is a finding, not a failed run**, and
`PLAN-330-CHAIR` section `4.5` says how each one reads. **A refusal does NOT get a second run with
a raised budget** (`gevr_xr.c` says so in the refusal text itself: *"do NOT raise the budget and
re-run without writing it down first"*).

---

## BLOCK 6 -- **`K-3` HARVESTED, READ, AND LABELLED. THE FIRST `getv_xrkill_report.txt` IN THIS PROJECT**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
$bw   = 'F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows'
$xr   = 'F:\Projects\GEVR\GoldenEyeVR\repo\xr'
$log  = Join-Path $xr 'k3_330_stdout.log'
$live = Join-Path $bw 'getv_xrkill_report.txt'
$cond = 'DESK'
$dest = Join-Path $xr ('getv_xrkill_report_330_' + $cond + '.txt')
"---- did the report get written? ----"
if (Test-Path $live) {
  "PRESENT  " + (Get-Item $live).Length + " bytes  " + (Get-Item $live).LastWriteTime
  Copy-Item $live $dest -Force
  "harvested to $dest"
} else {
  "ABSENT -- read PLAN-330-CHAIR section 4.5 against the stdout log before concluding anything."
}
"---- EVERY [getv][xrkill] LINE FROM STDOUT, AND IT IS TO BE READ ----"
Select-String -Path $log -Pattern '\[getv\]\[xrkill\]' | ForEach-Object { $_.Line.Trim() }
"---- THE VERDICT BLOCK, VERBATIM, FROM THE REPORT ----"
if (Test-Path $dest) { Get-Content $dest }
"---- the sidecar. Edit the quoted values FIRST if they are wrong. ----"
$notes = 'K-3 first exercise of the report path. Window freeze observed: yes/no and roughly how long, plus what was on screen at the firing, go here.'
$side  = Join-Path $xr ('getv_xrkill_330_K3_' + $cond + '_conditions.txt')
$lines = @(
  'run           K-3 (PLAN-330-CHAIR section 4), 330',
  ('condition     ' + $cond),
  ('time_local    ' + (Get-Date -Format 'yyyy-MM-dd HH:mm:ss')),
  ('exe_md5       ' + (Get-FileHash (Join-Path $bw 'goldeneye.exe') -Algorithm MD5).Hash),
  ('exe_len       ' + (Get-Item (Join-Path $bw 'goldeneye.exe')).Length),
  'exe_label     goldeneye.exe.vr329 staged as goldeneye.exe',
  'knobs         GETV_VR=1  GETV_XR_KILL=1  GETV_XR_KILL_AT unset (default 120)',
  'forks         A2 N=300 warmup 30, B1 no swapchains, C2 stdout and report file',
  'steamvr       RUNNING (vrmonitor, vrserver, vrcompositor present at launch)',
  'headset       AWAKE, ON THE DESK, NOT WORN (fork D1)',
  'dashboard     DISMISSED',
  'other_openxr  NONE running at launch',
  'scene         what was on screen when the loop fired -- edit this line',
  'killed        no -- edit to yes plus when, if the process had to be killed',
  'stdout_log    repo\xr\k3_330_stdout.log',
  ('report        ' + $dest),
  ('notes         ' + $notes)
)
Set-Content -Path $side -Value $lines -Encoding ASCII
"sidecar written: $side"
Get-Content $side
```

**`[PREDICTION] K-3-REPORT`: `getv_xrkill_report.txt` exists in `build-windows`, it contains the
`ARM A` banner, the distribution, one of the three `K-3` verdicts, `K-3b`, `K-3c`, `K-3d`, the
`xrRequestExitSession ->` and `xrEndSession ->` lines, and the closing note that conditions are
not in the file.**
**FALSIFIED BY:** an absent file -- **section `4.5`, three readings, and the stdout log decides
which**; a file that stops mid-distribution -- **the process died or was killed, say which in the
sidecar**; or a report whose lines disagree with the stdout log, **which would falsify fork `C2`'s
both-sinks-or-neither claim and is a finding about the instrument.**

►► **AND THE SCORE IS THE INSTRUMENT'S OWN VERDICT LINE.** `PLAN-330-CHAIR` section `4.2`: the
binary's `LANDS` band is `10%`, inherited byte-identically from `ge_s3_score`; `PLAN-329` section
`5.2`'s prose says `0.500%`. **BOTH ARE REPORTED** -- the printed verdict, and the `0.500%`
arithmetic computed from the printed `mean`, `pmin` and `pmax`. **NEITHER NUMBER IS ADJUSTED AND
THE INSTRUMENT IS NOT EDITED.** ◄◄

---

## BLOCK 7 -- **RESTORE. THE PLAIN BINARY GOES BACK, AND IT IS VERIFIED**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
$bw = 'F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows'
Copy-Item (Join-Path $bw 'goldeneye.exe.plain329') (Join-Path $bw 'goldeneye.exe') -Force
"restored goldeneye.exe  " + (Get-FileHash (Join-Path $bw 'goldeneye.exe') -Algorithm MD5).Hash + "  " + (Get-Item (Join-Path $bw 'goldeneye.exe')).Length
"expected                037EDBD61D293C1CA0419418927715D7  18075663"
"---- and the preserved copies, untouched ----"
foreach ($n in 'goldeneye.exe.vr329','goldeneye.exe.plain329','goldeneye.exe.vr328','goldeneye.exe.plain328') {
  $p = Join-Path $bw $n
  if (Test-Path $p) { "{0,-26} {1}" -f $n, (Get-FileHash $p -Algorithm MD5).Hash }
}
```

**`[PREDICTION] P-7`: `goldeneye.exe` is `plain329` again and the four preserved copies are
unchanged.**
**FALSIFIED BY:** anything else. **`328` LEFT THE `-Vr` BINARY IN PLACE AND IT COST A GATE
DEVIATION**; this block is why it is not repeated.

---

## section 2 -- **WHAT THIS SHEET CANNOT SCORE, AND SAYS SO ITSELF**

1. **IT DOES NOT DECIDE `D-X3`.** A `K-3 LANDS` says `xrWaitFrame` blocks in the game process and
   **`D-X3` SURVIVES -- IT IS NOT BUILT.** A non-blocking result under `B1` is **`K-3 NEITHER`**,
   it **mandates `B2`**, and **it is not a kill**.
2. **IT DOES NOT BUILD OR DESIGN `B2`.** Four swapchain names in a future import table would mean
   something was built that was not green-lit. `B2` is a next session's plan.
3. **IT DOES NOT ARM THE INTERLOCK.** `geVrXrPaceArm()` is not called, `geVrXrPacingOwned()` is
   not read, `sync_framerate_with_timer()` keeps the clock. **A LANDED `K-3` IS NOT PERMISSION.**
4. **IT DOES NOT FIX THE THREE THINGS SECTION `2` OF THE PLAN FOUND** -- the stale `ARMED` string,
   the `10%`-vs-`0.500%` band, the CWD-relative `fopen`. **`301`. WRONG FILED FIXES STAY FIVE.**
5. **IT DOES NOT COMPARE PACING NUMBERS.** `K-2` never captured any; there is nothing to compare
   to. `H24` unchanged.
6. **THE FRAME AFTER THE FREEZE IS CONTAMINATED BY IT.** Any `GETV_BUDGET` or pacing number from
   the frame following the loop **is not a finding about `xrWaitFrame`** -- that sentence is in
   `port_render.c` at the call site, and it is repeated here because this is the sheet that
   creates the freeze.

## section 3 -- **THE ARTIFACTS THIS SHEET PRODUCES** (gitignored logs OK)

`repo\xr\k6_330_stdout.log`, `repo\xr\getv_xrkill_330_K6_conditions.txt`,
`repo\xr\k3_330_stdout.log`, `repo\xr\getv_xrkill_report_330_DESK.txt`,
`repo\xr\getv_xrkill_330_K3_DESK_conditions.txt`, and the working copy
`getv\build-windows\getv_xrkill_report.txt` which a later run will overwrite -- **which is why
BLOCK `6` harvests it under a labelled name.**

Binaries: `goldeneye.exe` is staged to `vr329` by BLOCK `1` and restored to `plain329` by BLOCK
`7`. **No preserved copy is written and nothing is rebuilt.**

## section 3a -- ►► **WHAT WAS ACTUALLY RUN, 2026-09-05 EVENING. BOTH RUNS LANDED** ◄◄

| block | outcome |
|---|---|
| `0` | **NOT HANDED OVER.** Its facts were read off the disk before the green-light; BLOCK `1`'s md5 was the re-take |
| `1` | **`P-1` LANDS.** `goldeneye.exe` = `70BF2580239CD6B7C402C063D89B976F` / `18,101,808` |
| `2` | **`K-6a` LANDS.** SteamVR closed, all knobs unset, `2,667,826` bytes captured, last frame `1081` |
| `3` | **`K-6b`/`K-6c` LAND.** `0` `[getv][vr]`, `0` `[getv][xrkill]`, no report file. Sidecar written `18:47:31` |
| `4` | the gate held: `K-6` reported, **`G1` unlocked `K-3`** |
| `5` | **`K-3-REACH` LANDS.** `ARMED for frame 120` -> `SESSION LIVE IN THE GAME PROCESS on frame 120` -> `ARM A: 300 frames` -> verdict. `76,268,410` bytes captured |
| `6` | **`K-3-REPORT` LANDS.** `41` lines, `2,953` bytes, harvested to `repo\xr\getv_xrkill_report_330_DESK.txt`. Sidecar written `18:59:45` |
| `7` | **`P-7` LANDS.** `goldeneye.exe` restored to `037EDBD61D293C1CA0419418927715D7` / `18,075,663`; `.vr329`, `.plain329`, `.vr328`, `.plain328` untouched |

**THREE DEVIATIONS FROM THIS SHEET AS WRITTEN, ALL RECORDED RATHER THAN SMOOTHED:**

1. **BLOCK `0` WAS SKIPPED** (above), by the sheet's own note.
2. **THE `K-3` PROCESS DID NOT QUIT NORMALLY.** `[REPORTED]` chair: Dam gameplay ran to level end,
   the menu locked up on return, the window was closed with `X`. **The sidecar says `killed yes`**
   -- which is the field that exists for this -- and **the loop had completed `13,741` frames
   earlier**, with `[getv] game_exit requested` as the log's last line. `330` section `4.1`.
3. **THE CAPTURED LOGS ARE `UTF-16LE`/`CRLF`**, which `Select-String` reads and a UTF-8 tool does
   not. **A `0` FROM THE WRONG TOOL WOULD LOOK EXACTLY LIKE A CLEAN `K-6`.** Named in `330`
   section `8`; the counts above were taken after converting.

**AND FORK `C2` WAS CROSS-CHECKED, WHICH THIS SHEET ASKED FOR:** `[MEASURED]` the report file and
the stdout capture carry the **same `38` non-blank lines**, byte for byte. **`C2` HOLDS.**

---

## section 4 -- **THE COMMIT. ONE REPO, PATH LIST ONLY, AND THE SCRUB IS NOT IN IT**

**`GoldenEyeVR` ONLY. `330` DID NOT TOUCH A PRODUCT FILE, SO `goldeneye-native` IS NOT COMMITTED
AND NOT VISITED.**

### BLOCK 8 -- the six docs

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR
git rev-parse --show-toplevel
"---- BEFORE: the unstaged ' M' count under repo/docs ----"
(git --no-optional-locks status --porcelain -- repo/docs | Select-String '^ M' | Measure-Object).Count
git add -- repo/docs/00-STATE.md repo/docs/00-STATE.md.bak-329 repo/docs/PLAN-330-CHAIR.md repo/docs/RUN-SHEET-330.md repo/docs/RUN-SHEET-329.md "repo/docs/330-XRWAITFRAME-BLOCKS-IN-THE-GAME-AND-XRENDSESSION-SUCCEEDS-AT-LAST.md"
"---- AFTER STAGING: staged lines (expect exactly six) ----"
git --no-optional-locks status --porcelain -- repo/docs | Select-String '^[AM] '
"---- AND THE SCRUB, WHICH MUST STILL BE ' M' ----"
(git --no-optional-locks status --porcelain -- repo/docs | Select-String '^ M' | Measure-Object).Count
git commit -F F:\Projects\GEVR\GoldenEyeVR\COMMIT-MESSAGE-2026-09-05v.txt
git log --oneline -1
```

**`[PREDICTION] C-330`: BEFORE `60`, AFTER `58`, with **six** staged lines -- two `M `
(`00-STATE.md`, `RUN-SHEET-329.md`) and four `A ` (the backup, the plan, this sheet, the session
doc).**
`[ARITHMETIC]` `59` were unstaged before this session touched anything; the `00-STATE` bump makes
it `60`; staging the two tracked files takes it to `58`. The four `A ` paths move `?? -> A ` and
**take nothing out of the unstaged column.**
**FALSIFIED BY:** a scrub file appearing as staged `M `, an after-count other than `58`, or a
staged line this list did not name.

**`RUN-SHEET-329.md` IS THE HYGIENE RIDE**, as agreed: its section `5` scrub arithmetic was
corrected on disk after `81ac07b`, and it goes in this path list rather than getting a commit of
its own. **THE OTHER THREE NON-SCRUB DIRTY FILES ARE NOT `330`'s AND ARE NOT LISTED:**
`309-THE-UNDER-READ-IS-THIRTY-PERCENT-NOT-THIRTEEN.md`, `MODS-EXTERNAL-DATABASE.md`,
`NEXT-SESSION-PROMPT-310.md`.

**THE COMMIT MESSAGE FILE IS `COMMIT-MESSAGE-2026-09-05v.txt`**, written this session at the
`GoldenEyeVR` root (rule `17`). It is an input to `-F`, not an artifact, and it is not committed.

---

## section 5 -- **THE STOPPING LINE**

**BEFORE ANY BLOCK: the four forks in `PLAN-330-CHAIR` section `8`.**
**AFTER BLOCK `3`: STOP, report `K-6`, and do not launch `K-3` if `K-6` was falsified.**
**AFTER BLOCK `7`: STOP.** No `B2`, no interlock, no product edit, no rebuild, no second `K-3`
with a different knob.
**AFTER BLOCK `8`: STOP.** The docs are committed and `D-X3` survives; **arming the handover is a
fresh session's `HIGH`** (`00-STATE` section `7c`, `330` section `9`).

`169` NEXT ID = `U-28`. NEXT INSTRUMENT HOLE = `H25`.
