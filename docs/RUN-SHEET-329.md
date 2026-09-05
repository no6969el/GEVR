# `RUN-SHEET-329` -- **THE FRAME LOOP IS TYPED. FOUR PASTES, AND THE FALSIFIER IS `objdump -p` AGAIN**

**GREEN-LIT 2026-09-05 (owner):** `PLAN-329-FRAMELOOP` with forks **`A2`** (`N=300`, warm-up `30`,
per-iteration body byte-identical to `ge_s3_armA`, deviation printed), **`B1`** (no swapchains;
a non-blocking `xrWaitFrame` is `K-3 NEITHER`, **NOT** a kill), **`C2`** (stdout **and**
`getv_xrkill_report.txt`), `geVrXrEndSession()` corrected to end a begun session, four entry
points in `gevr_xr.h`/`.c`, **one** added call in `port_render.c`, loop arrays inside
`GEVR_XR_LIVE` only.

## section 1 -- **WHAT IS ON DISK, AND IT IS THREE FILES**

`[MEASURED]` `git --no-optional-locks status --porcelain -- getv/port/src` in
`goldeneye-native` returns **exactly three lines**, all ` M`, **`+602 / -0`**:

| file | `+` | what changed |
|---|---|---|
| `getv/port/src/gevr_xr.h` | `60` | four declarations -- `geVrXrSessionStart`, `geVrXrFrameLoop`, `geVrXrSessionStop`, `geVrXrFrameKill` -- and the `D-X3-KILL` block comment that carries `A2`, `B1` and the `xrEndSession` finding |
| `getv/port/src/gevr_xr.c` | `532` | the four LIVE implementations inside the existing `GEVR_XR_LIVE` guard, their four inert stubs, and `geVrXrEndSession()` gaining the `if (ge_xr_begun) geVrXrSessionStop();` branch |
| `getv/port/src/port_render.c` | `10` | **one call**, `geVrXrFrameKill();`, inside the existing `328` `else` branch after the `SESSION LIVE` line, plus its comment. **No new knob, no new include, block not moved, still BEFORE the `GETV_BUDGET` bracket** |

**`build_windows.ps1` IS NOT TOUCHED. `getv/patches` IS NOT TOUCHED. `gfx_sdl2.c` IS NOT
TOUCHED.** Nothing is staged, committed, branched, tagged or pushed by this sheet.

**THE STANDING LINE HELD.** `[MEASURED]` `geVrXrPacingOwned`, `geVrXrPaceArm` and
`sync_framerate` appear in the diff **only inside comments and printed strings that say they are
NOT called**. There is no call to any of them.

**AND THE INERT HALF IS ALREADY READ.** `[MEASURED]` `329`, on the bridge: `gcc -Wall -Wextra
-fsyntax-only` over `gevr_xr.c` **without** `-DGEVR_XR_HAVE_OPENXR` -- **exit `0`, no output**.
That reads the stubs and the pacing block. **IT DOES NOT READ THE LIVE BRANCH**, which needs
`<windows.h>`, and that is BLOCK 1's whole job.

---

## BLOCK 1 -- **THE `-Wall -Wextra` SYNTAX-ONLY READ OF `gevr_xr.c`. NO OBJECT, NO LINK**

Same flag set as `RUN-SHEET-328` BLOCK 1, log name changed.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
$mingw = 'C:\msys64\mingw64'
$gcc   = Join-Path $mingw 'bin\gcc.exe'
$here  = 'F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv'
$log   = 'F:\Projects\GEVR\GoldenEyeVR\repo\xr\syntax_329_gevr_xr.log'
$flags = @(
  "-I$here\port\prheaders", "-I$here\port", "-I$here\port\include",
  "-I$here\port\fast3d", "-I$here\port\src", "-I$mingw\include\SDL2",
  '-include', "$here\port\include\ge_win_compat.h",
  '-DTARGET_N64','-DGE_PORT_NATIVE','-D_LANGUAGE_C=1','-DRAPI_GL','-DWAPI_SDL2',
  '-DGE_PLATFORM_DESKTOP','-DGEVR_XR_HAVE_OPENXR',
  '-std=gnu17','-mno-ms-bitfields','-O1','-Wall','-Wextra','-fsyntax-only'
)
& $gcc @flags "$here\port\src\gevr_xr.c" *> $log
"gcc exit $LASTEXITCODE"
"log bytes $((Get-Item $log).Length)"
"---- EVERY LINE OF IT, AND IT IS TO BE READ ----"
Get-Content $log
"---- end ----"
```

**`[PREDICTION] S-7`: exit `0` and the log is `0` BYTES.** `328`'s `S-5` set that bar and it is
not softened for a bigger edit.
**FALSIFIED BY:** any diagnostic. The named candidates this time are the `double` conversions in
`ge_xk_say`'s variadic path under `-Wextra`, `XrSessionState` compared against `XR_SESSION_STATE_*`
in a `switch` with a `default`, and `QueryPerformanceFrequency`/`Sleep` needing the `<windows.h>`
already at `gevr_xr.c:34`. **A WARNING IS A RESULT AND IS WRITTEN UP, NOT FIXED ON SIGHT**
(`301`).

---

## BLOCK 2 -- **THE `-Vr` BUILD, AND THE COPY THAT PRESERVES IT.** `ONLY IF BLOCK 1 SHOWED NO ERROR`

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
$bw  = 'F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows'
$dll = 'F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\port\lib\openxr\openxr_loader.dll'
$log = 'F:\Projects\GEVR\GoldenEyeVR\repo\xr\build_329_vr.log'
if (-not (Test-Path $dll)) { throw "loader missing at $dll -- RUN-SHEET-326 BLOCK 5 puts it there" }
"loader md5 $((Get-FileHash $dll -Algorithm MD5).Hash)"
powershell -NoProfile -File F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build_windows.ps1 -Target port -Vr *> $log
"port exit $LASTEXITCODE"
powershell -NoProfile -File F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build_windows.ps1 -Target app -Vr *>> $log
"app  exit $LASTEXITCODE"
Get-Content $log -Tail 12
Copy-Item (Join-Path $bw 'goldeneye.exe') (Join-Path $bw 'goldeneye.exe.vr329') -Force
"vr329  $((Get-FileHash (Join-Path $bw 'goldeneye.exe.vr329') -Algorithm MD5).Hash)  $((Get-Item (Join-Path $bw 'goldeneye.exe.vr329')).Length)"
```

**`[PREDICTION] S-8`: both exits `0`, `port layer` reports `0 failed`, the app links, and no
`failed` / `error` / `warning` / `undefined` anywhere in the log.**
**FALSIFIED BY:** any of them. The two files that changed are `gevr_xr.c` and `port_render.c`; an
undefined `xr*` at link would mean the loader is no longer last on the line, which `328` measured
it to be.

---

## BLOCK 3 -- ►► **`K-7`. THE ONLY THING THAT COUNTS: SEVEN NEW NAMES IN THE IMPORT TABLE** ◄◄

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
$objdump = 'C:\msys64\mingw64\bin\objdump.exe'
$bw  = 'F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows'
$log = 'F:\Projects\GEVR\GoldenEyeVR\repo\xr\imports_329_vr.log'
& $objdump -p (Join-Path $bw 'goldeneye.exe.vr329') *> $log
"objdump exit $LASTEXITCODE"
"---- EVERY IMPORTED DLL ----"
Select-String -Path $log -Pattern 'DLL Name' | ForEach-Object { $_.Line.Trim() }
"---- openxr_loader named? ----"
(Select-String -Path $log -Pattern 'openxr_loader' | Measure-Object).Count
"---- xr* IMPORT ENTRIES: COUNT, THEN ALL OF THEM ----"
(Select-String -Path $log -Pattern 'xr[A-Z][A-Za-z]' | Measure-Object).Count
Select-String -Path $log -Pattern 'xr[A-Z][A-Za-z]' | ForEach-Object { $_.Line.Trim() }
"---- THE SEVEN THIS SESSION ADDED, ONE LINE EACH ----"
foreach ($n in 'xrPollEvent','xrBeginSession','xrEndSession','xrRequestExitSession','xrWaitFrame','xrBeginFrame','xrEndFrame') {
  "$n : $((Select-String -Path $log -Pattern $n | Measure-Object).Count)"
}
"---- end ----"
```

**`[PREDICTION] K-7`: `openxr_loader.dll` IS NAMED AND THE `xr*` ENTRY COUNT IS `19` -- `328`'s
TWELVE PLUS `xrPollEvent`, `xrBeginSession`, `xrEndSession`, `xrRequestExitSession`,
`xrWaitFrame`, `xrBeginFrame` AND `xrEndFrame`, EACH PRESENT EXACTLY ONCE.**
**FALSIFIED BY:** any of `xrWaitFrame`, `xrBeginFrame` or `xrEndFrame` absent -- **then the loop
is not in the binary and nothing about it may be claimed.** A count other than `19` with all seven
present is a finding to write up, **not a number to adjust the prediction to.**
`[MEASURED]` `329`: all seven are static exports of the vendored loader (`objdump -p
repo\xr\openxr_loader.dll`: `xrBeginFrame [3]`, `xrBeginSession [4]`, `xrEndFrame [18]`,
`xrEndSession [19]`, `xrPollEvent [45]`, `xrRequestExitSession [47]`, `xrWaitFrame [54]`), so a
direct call becomes an import entry and this prediction is mechanical, not hopeful.

**`23` WOULD BE `B2` AND `B2` IS NOT THIS SESSION.** Four swapchain names in this table mean
something was built that was not green-lit.

---

## BLOCK 4 -- ►► **`K-8`. THE PLAIN CONTROL, RE-TAKEN, NOT INHERITED** ◄◄

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
$objdump = 'C:\msys64\mingw64\bin\objdump.exe'
$bw  = 'F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows'
$log = 'F:\Projects\GEVR\GoldenEyeVR\repo\xr\build_329_plain.log'
$imp = 'F:\Projects\GEVR\GoldenEyeVR\repo\xr\imports_329_plain.log'
powershell -NoProfile -File F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build_windows.ps1 -Target port *> $log
"port exit $LASTEXITCODE"
powershell -NoProfile -File F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build_windows.ps1 -Target app *>> $log
"app  exit $LASTEXITCODE"
"---- any line naming openxr (MUST BE NONE) ----"
Select-String -Path $log -Pattern 'openxr' | ForEach-Object { $_.Line }
"---- end of that list ----"
Copy-Item (Join-Path $bw 'goldeneye.exe') (Join-Path $bw 'goldeneye.exe.plain329') -Force
"plain329  $((Get-FileHash (Join-Path $bw 'goldeneye.exe.plain329') -Algorithm MD5).Hash)  $((Get-Item (Join-Path $bw 'goldeneye.exe.plain329')).Length)"
& $objdump -p (Join-Path $bw 'goldeneye.exe.plain329') *> $imp
"---- plain: EVERY IMPORTED DLL ----"
Select-String -Path $imp -Pattern 'DLL Name' | ForEach-Object { $_.Line.Trim() }
"---- plain: xr* ENTRY COUNT (MUST BE 0) ----"
(Select-String -Path $imp -Pattern 'xr[A-Z][A-Za-z]' | Measure-Object).Count
"---- and the three frame calls, by name (MUST ALL BE 0) ----"
foreach ($n in 'xrWaitFrame','xrBeginFrame','xrEndFrame') {
  "$n : $((Select-String -Path $imp -Pattern $n | Measure-Object).Count)"
}
"---- end ----"
```

**`[PREDICTION] K-8`: the plain build compiles and links, no log line names `openxr`, the plain
binary has the same seven DLLs and an `xr*` entry count of `0`.**
**FALSIFIED BY:** any `xr*` import in the plain binary, any `openxr` line in a plain build log, or
a compile failure -- **any of which means the loop is not gated and it comes back out.**
**`K-5` IS NOT INHERITED HERE:** the edit is `532` lines against `328`'s handful, and inheriting a
gate across a rewrite is how one gets missed.

---

## section 2 -- ►► **THE REPORT PATH, AND WHY THIS SHEET DOES NOT EXERCISE IT** ◄◄

FORK `C2` opens `getv_xrkill_report.txt` as the **first statement of `geVrXrFrameKill()`**, before
`geVrXrSessionStart()` and before any `xr*` call, so **every reach of that function writes the
file, including one that refuses.** That is verified by reading the code, and it is the strongest
claim available without a run.

**IT CANNOT BE EXERCISED IN-GAME WITHOUT TAKING THE INSTRUMENT'S RUN, AND THAT IS STATED RATHER
THAN WORKED AROUND.** `geVrXrFrameKill()` is reached only after `geVrXrEnabled()`, `geVrXrInit()`
and `geVrXrBeginSessionCurrent()` have all returned `1` -- which needs `GETV_VR=1`,
`GETV_XR_KILL=1`, SteamVR up and the HMD awake. **A RUN THAT SATISFIES ALL OF THAT RUNS THE LOOP
AND PRINTS A `K-3` VERDICT.** There is no smaller arm: `GETV_XR_KILL_N` cannot be lowered far
enough to suppress the verdict, because the loop clamps the warm-up to leave at least two scored
frames on purpose (a distribution of one is not a distribution).

**SO THE FIRST EXERCISE OF THE REPORT PATH IS `K-3`'s OWN RUN**, it needs the conditions sidecar
(`325` section `2`: **`VISIBLE` NO LONGER IMPLIES WORN**) and its own green-light, and **A DESK
RUN IS STILL THAT RUN** -- desk does not make it a smoke test. **THAT IS THE OWNER'S CALL AND IT
IS NOT TAKEN BY THIS SHEET.**

## section 3 -- **WHAT THIS SHEET CANNOT SCORE, AND SAYS SO ITSELF**

**IT DOES NOT ANSWER `D-X3-KILL`.** `K-7` and `K-8` are link facts read from `objdump`. **NO
BINARY BUILT BY THIS SHEET IS LAUNCHED.** `GETV_XR_KILL=1` has still never executed and it is
still unknown whether `xrCreateSession` succeeds on the game's own context.

**`K-6` IS PARKED** (owner, `329`) and is not taken here. **`K-9`** -- with `GETV_XR_KILL` unset
the `-Vr` binary is `K-6`'s baseline -- **has no baseline until `K-6` is taken. That is a named
dependency, not a hole.**

## section 5 -- **THE COMMIT. TWO REPOS. OWNER-RUN. PATH LISTS ONLY, AND THE SCRUB IS NOT IN THEM**

**RUN THESE ONLY AFTER BLOCKS 1-4 HAVE ALL LANDED.** Two commits, product first. **NEITHER BLOCK
CONTAINS `git add -A` AND NEITHER NAMES `repo/docs` AS A DIRECTORY.**

### BLOCK 5 -- `goldeneye-native`, the three product files

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
git rev-parse --show-toplevel
"---- BEFORE ----"
git --no-optional-locks status --porcelain -- getv/port/src getv/port/include getv/build_windows.ps1
git add -- getv/port/src/gevr_xr.c getv/port/src/gevr_xr.h getv/port/src/port_render.c
"---- AFTER STAGING (expect exactly three, all 'M ') ----"
git --no-optional-locks status --porcelain -- getv/port/src getv/port/include getv/build_windows.ps1
git commit -F F:\Projects\GEVR\GoldenEyeVR\COMMIT-MESSAGE-2026-09-05u-native.txt
git log --oneline -1
```

### BLOCK 6 -- `GoldenEyeVR`, the four docs and the backup

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR
git rev-parse --show-toplevel
"---- BEFORE: the scrub, counted ----"
(git --no-optional-locks status --porcelain -- repo/docs | Select-String '^ M' | Measure-Object).Count
git add -- repo/docs/00-STATE.md repo/docs/00-STATE.md.bak-328 repo/docs/PLAN-329-FRAMELOOP.md repo/docs/RUN-SHEET-329.md "repo/docs/329-THE-FRAME-LOOP-LANDS-AND-THE-BINARY-IMPORTS-NINETEEN-XR-SYMBOLS.md"
"---- AFTER STAGING: staged lines (expect exactly five) ----"
git --no-optional-locks status --porcelain -- repo/docs | Select-String '^[AM] '
"---- AND THE SCRUB, WHICH MUST STILL BE ' M' AND MUST NOT HAVE MOVED ----"
(git --no-optional-locks status --porcelain -- repo/docs | Select-String '^ M' | Measure-Object).Count
git commit -F F:\Projects\GEVR\GoldenEyeVR\COMMIT-MESSAGE-2026-09-05u.txt
git log --oneline -1
```

**EXPECTED BEFORE: `59` unstaged ` M` under `repo/docs`. EXPECTED AFTER: `58` unstaged ` M` and
`5` staged** -- one `M ` (`00-STATE.md`) and four `A ` (the backup, the plan, this sheet, the
session doc).

**AND THIS SHEET SAID `54` BEFORE THE COMMIT WAS RUN, WHICH WAS WRONG, AND IT IS CORRECTED HERE
RATHER THAN QUIETLY** (`326` set this precedent for a plan's own arithmetic). `[MEASURED]` `329`:
the count went `59` -> `58`. **ONLY `00-STATE.md` WAS EVER IN THE ` M` SET.** The other four paths
were `??`, so they move `?? -> A ` and take nothing out of the unstaged column. Five staged lines
do not mean five fewer unstaged ones, and the number that matters -- **the scrub did not move, and
nothing staged as `M ` that should have stayed ` M`** -- was read correctly by both blocks.

**►► AND ONE OF THOSE `59` IS NOT THE SCRUB AND IS NOT THIS SESSION'S.** `[MEASURED]` `329`:
`repo/docs/MODS-EXTERNAL-DATABASE.md` gained `+6 / -1` at `22:01` **while this session was
running** -- rows `XB360-07` .. `XB360-11` from the Rare interview, plus a changelog line and a
NEXT-ROW-ID bump. **NOT THIS SESSION'S WORK, NOT IN EITHER PATH LIST, AND NOT TOUCHED.** It is
named here so it is not mistaken for scrub later.
`repo/docs/309-...md` and `repo/docs/NEXT-SESSION-PROMPT-310.md` also carry non-scrub edits, and
both predate this session.

**THE COMMIT MESSAGE FILES ARE NOT COMMITTED**, matching every prior session: `[MEASURED]`
`COMMIT-MESSAGE-2026-09-05t.txt` and its `-native` twin are untracked and un-ignored at the
`GoldenEyeVR` root. They are inputs to `-F`, not artifacts.

---

## section 4 -- **THE STOPPING LINE**

After BLOCK 4: report `S-7`, `S-8`, `K-7` and `K-8`, and **STOP**. Nothing staged. No game run,
no `K-3`, no `K-6`, no `B2`.

`169` NEXT ID = `U-28`. NEXT INSTRUMENT HOLE = `H25`.
