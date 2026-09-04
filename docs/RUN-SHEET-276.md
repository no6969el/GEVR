# RUN SHEET — `276`. THE `239` GATE ON SHAPE 3.

**WRITTEN BEFORE THE BUILD, PER `15`. THE PREDICTION AND THE FALSIFIER ARE IN §0 AND THEY ARE
NOT TO BE EDITED AFTER A RUN.**
**Every path and variable below was grepped out of the tree on 2026-08-30m:** `GETV_SIMHZ` at
`frametiming.c` (new this session), `GETV_CLOCKTRACE` / `GETV_SIMDIV` / `GETV_TICKFIELDS` at
`frametiming.c`, `GETV_FPS` / `GETV_VSYNC` at `gfx_sdl2.c:402`/`421`, `GETV_BUDGET` at
`port_render.c:752`, `GETV_REALCLOCK` at `port_os.c:214`, `GETV_STAGE` in `ge_config.c`.
**THE LIVE TREE IS `F:\Projects\GEVR`** — `00-STATE` §6, the second stale copy on the Desktop.

---

## §0 — THE PREDICTION, AND THE FALSIFIER. READ THIS FIRST.

**PREDICTION** (`275` §7, restated unchanged):

1. **`speedgraph` reads `60/s` at BOTH 60 Hz and 90 Hz.** Today it reads 60 and **90**
   (`274` §2).
2. **`fps` still reads `90.0` in the 90 Hz arm.** The render rate must NOT fall — that is what
   separates this from `GETV_REALCLOCK`, which delivered correct game speed by throwing the
   90 Hz away (`274` §2.2).
3. **`g_GlobalTimer` reads `60/s` in both arms.**
4. **The owner's stopwatch on the `RB-04` walk reads about `18.2 s`, not `27.0`.**
5. **`[getv][clock]` prints `simhz on delta 0.6667` in the 90 Hz arm and `simhz on delta
   1.0000` at 60.**

**FALSIFIERS — any one of these voids the run and everything derived from it:**

- **`speedgraph` still reads `90/s` at 90 Hz → THE TERM IS NOT IN THE BINARY** and every other
  number in that log is void. Check the exe timestamp and `grep -a GETV_SIMHZ goldeneye.exe`.
- **No `[getv][simhz] SHAPE 3 ON` banner in the log → the knob did not take.** A knob that is
  not in the binary reads as a clean null result (`133`, `268` §4).
- **Any `CONTAMINATED` line → read it and stop.** The term names its own contamination.
- **`fps` falls to 60 in arm B → this is `274` §2.2 all over again** and shape 3 has bought
  nothing.
- **Any `simulation held to` line, or `props interpolated` non-zero → `268`'s divider is
  running and the arm is not comparable** (`273` §7.1). `GETV_SIMDIV=1` PRINTS NOTHING, so
  these two are the only positive gate.

---

## STEP A — COMMIT FIRST. MAIN PC, NOT THE BRIDGE. **TWO ACTIONS, NOT ONE.**

> ### ►►►► `COMMIT-NOW.cmd` DOES NOT COMMIT `vendor\ge-decomp`, AND THIS SESSION'S WHOLE FIX LIVES THERE. ◄◄◄◄
> `[MEASURED]` from `commit-now.ps1`: it commits `GoldenEyeVR`, `GoldenEye64Recomp`, then
> `goldeneye-native` — and `vendor/` is gitignored by `goldeneye-native` (`.gitignore:42`).
> **Double-clicking the script and stopping there commits the docs and the harness and NONE of
> the clock.** `276` §6.

**Three message files are written and dated today** (rule `17`): `-2026-08-30m.txt` (docs),
`-m-native.txt`, `-m-decomp.txt`. **`275` and `COMMIT-MESSAGE-2026-08-30e.txt` are still
untracked from the previous session and ride along in A1.**

### A1 — the docs repo + the recomp + `goldeneye-native`. The script, as normal.

```
F:\Projects\GEVR\GoldenEyeVR\COMMIT-NOW.cmd
```

`GoldenEye64Recomp` is **clean** this session — expect *"nothing to commit"* there and do not
read it as a failure. `goldeneye-native`'s only change is the new
`getv\tools\simhz_harness.c`. **No file this session touches `gfx_pc.c`, `gfx_sdl2.c` or
`gfx_opengl.c`, so nothing NEW is hidden from git — but the regen is a standing rule for every
native commit** (`271` §7), from **Git Bash** (`C:\Program Files\Git\bin\bash.exe`; MSYS2's
bash has no `git`), **not over the bridge**, and **the gate is `verify` reporting `15/15 files
match pristine + patch`** — byte count is not the gate. `MAIN-STATION-TASKS.md`, top.

### A0 — ►►►► CLEAR THE STALE LOCK FIRST, OR A2 FAILS. RUN THIS BEFORE ANYTHING ELSE. ◄◄◄◄

`[MEASURED]` this session: **`goldeneye-native\vendor\ge-decomp\.git\index.lock` exists and
is dated `2026-08-29 04:13`.** It is zero bytes and no git is running. **The bridge cannot
delete it** — the mount refuses to unlink, which is `00-STATE` §6's documented behaviour — so
this is a main-PC action. **Any `git add` in the decomp dies with *"Unable to create ...
index.lock: File exists"* until it is gone.**

`[INFERRED]`, **not established**: this lock is a candidate for why the decomp's last commit is
`2026-08-29` despite work landing there since. Do not build on that.

```powershell
$lock = 'F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\vendor\ge-decomp\.git\index.lock'
Get-Process git -ErrorAction SilentlyContinue | Format-Table Id, StartTime -AutoSize
if (Test-Path $lock) { Get-Item $lock | Select-Object FullName, Length, LastWriteTime; Remove-Item $lock -Force }
if (Test-Path $lock) { "LOCK STILL PRESENT -- A GIT IS RUNNING, DO NOT PROCEED" } else { "lock clear" }
```

**THE BLOCK'S OWN VERIFICATION IS THE LAST LINE.** If `Get-Process git` listed anything, stop —
a running git owns that lock and deleting it corrupts the operation (`commit-session.ps1` makes
the same check for the same reason).

### A2 — ►► THE DECOMP. BY HAND, AND **BY EXPLICIT PATH LIST**.

**DO NOT RUN `git add -A` IN THIS REPO.** `[MEASURED]` `HEAD` is LF throughout and the worktree
has **2,106 files converted to CRLF**, each of which diffs as a whole file. **The history
already contains one such sweep** — `7a4e7bfd`, subject *"fix: three pointer-size errors the -w
build never warned about"*, is **736 files and 601,764 insertions**. `-A` here would bury a
five-file clock change inside a two-thousand-file line-ending commit.

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\vendor\ge-decomp
git add -- src/game/frametiming.c src/game/lv.c src/game/lv.h src/game/bondview2.c src/game/propobj.c
git diff --cached --stat
git commit -F F:\Projects\GEVR\GoldenEyeVR\COMMIT-MESSAGE-2026-08-30m-decomp.txt
git log -1 --format='%h  %ad  %s' --date=short
git status --short -- src/game/frametiming.c src/game/lv.c src/game/lv.h src/game/bondview2.c src/game/propobj.c
```

**THE BLOCK'S OWN VERIFICATION IS THE LAST THREE LINES.** `git diff --cached --stat` must show
**exactly five files and about 311 insertions** — if it shows hundreds of files or hundreds of
thousands of lines, **abort with `git reset` and say so**, the path list did not hold. The
closing `status` must print **nothing**, meaning all five went in.

**THE 2,106-FILE CRLF CHURN IS NOT ACTIONED HERE AND IS THE OWNER'S CALL.** It is recorded in
`00-STATE` §6 and `276` §6. Nothing has been deleted or normalised wholesale.

---

## STEP B — BUILD ONCE. ONE BLOCK, COMPLETE.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
& getv\build_windows.ps1 -Target all *> build_276_simhz.log 2>&1
Select-String -Path build_276_simhz.log -Pattern 'error|Error|FAILED' | Select-Object -First 20
Get-Item F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows\goldeneye.exe |
    Select-Object FullName, LastWriteTime, Length
$exe = 'F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows\goldeneye.exe'
$txt = [Text.Encoding]::ASCII.GetString([IO.File]::ReadAllBytes($exe))
if ($txt.Contains('GETV_SIMHZ')) { "GETV_SIMHZ IS IN THE BINARY" }
else { "GETV_SIMHZ IS **NOT** IN THE BINARY -- STOP, EVERY ARM BELOW IS A CLEAN NULL" }
```

**THE BLOCK'S OWN VERIFICATION IS THE LAST TWO LINES.** The timestamp must be newer than the
log of any run you compare against (`133`), and the string must be present, or every arm below
is a clean null result.

---

## THE THREE ARMS. `274`'s SHEET, WITH `GETV_BUDGET=120` ADDED PER `274` §3.1.

**`GETV_SIMDIV=1` IS PINNED IN EVERY ARM** and its gate is `props interpolated 0` plus zero
`simulation held to` lines (`273` §7.1). **`GETV_STAGE=34` is FACILITY and FACILITY IS A VENT**
(`272` §4.2) — fine for a clock arm, which is what these are, and NOT to be quoted as a
performance figure.

### ► ARM A — 60 Hz, the control. **MUST BE INDISTINGUISHABLE FROM TODAY.**
```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
$env:GETV_CLOCKTRACE = "1"
$env:GETV_SIMDIV     = "1"
$env:GETV_BUDGET     = "120"
$env:GETV_FPS        = "60"
$env:GETV_VSYNC      = "0"
$env:GETV_STAGE      = "34"
$env:GETV_SIMHZ      = "query"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_276_A_60_simhz.log 2>&1
```

### ► ARM B — 90 Hz, the term ON, QUERIED. **THIS IS THE ARM THE GATE TURNS ON.**
```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
$env:GETV_CLOCKTRACE = "1"
$env:GETV_SIMDIV     = "1"
$env:GETV_BUDGET     = "120"
$env:GETV_FPS        = "90"
$env:GETV_VSYNC      = "0"
$env:GETV_STAGE      = "34"
$env:GETV_SIMHZ      = "query"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_276_B_90_simhz.log 2>&1
```
**WALK THE `RB-04` ROUTE AND STOPWATCH IT.** `18.18 s` is the retail figure; `27.04 s` is what
90 Hz did before this change (`259` §3, `274` §2.1).

### ► ARM C — 90 Hz, the term OFF. **THE REGRESSION CONTROL: this must reproduce `274` arm B.**
```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
$env:GETV_CLOCKTRACE = "1"
$env:GETV_SIMDIV     = "1"
$env:GETV_BUDGET     = "120"
$env:GETV_FPS        = "90"
$env:GETV_VSYNC      = "0"
$env:GETV_STAGE      = "34"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_276_C_90_off.log 2>&1
```
**ARM C MUST STILL READ `speedgraph 90/s`.** If it does not, the term is not gated and `48`'s
one-behaviour-change is broken — which would be a worse finding than the fix failing.

### ► ARM D — THE REFUSAL. NO GAMEPLAY NEEDED; READ THE FIRST TWENTY LINES AND QUIT.
```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
$env:GETV_CLOCKTRACE = "1"
$env:GETV_SIMDIV     = "1"
$env:GETV_FPS        = "90"
$env:GETV_VSYNC      = "0"
$env:GETV_STAGE      = "34"
$env:GETV_SIMHZ      = "60"
$env:GETV_REALCLOCK  = "1"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_276_D_refuse.log 2>&1
```
**EXPECT `[getv][simhz] CONTAMINATED` naming `GETV_REALCLOCK`, and the term OFF.** An
instrument that cannot be made to refuse has not been validated (`15`, rule `17`).
**Without `GETV_REALCLOCK` this same arm would instead refuse on the pin: `60` pinned against
`ge_pace_framerate` 90.** Run it both ways if you want both refusals in one log pair.

---

## READING THE LOGS — AND THE TWO TRAPS THAT HAVE COST A DAY EACH

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
foreach ($f in 'run_276_A_60_simhz.log','run_276_B_90_simhz.log','run_276_C_90_off.log','run_276_D_refuse.log') {
    "==== $f"
    Select-String -Path $f -Pattern 'simhz|pace:|simdiv|simulation held to|props interpolated|CONTAMINATED' |
        Select-Object -First 12 | ForEach-Object { $_.Line }
    "---- clock windows (first discarded as boot transient):"
    (Select-String -Path $f -Pattern '\[getv\]\[clock\]').Line | Select-Object -Skip 1
}
```

- **A TAIL IS NOT A SAMPLE** (`273` §1). Cut the window list at the `lvlStageLoad` line
  numbers; `Select-Object -Last N` has handed back the intro/cast windows of a run that had
  died and reloaded.
- **NEVER READ A LOG AS FINAL WITHOUT ITS TERMINATING RECORD** — `===== EXCEPTION` or
  `game_exit requested` (`262` §5).

---

## THE TWO HOIST SITES — LOOK AT THEM, THEY ARE NOT COVERED BY ANY NUMBER ABOVE

`275` §4 / `276` §1. Neither is exercised by standing in a vent, and neither has ever been
driven at 90 Hz.

1. **THE TANK (`bondview2.c:7330`).** Runway or Streets. **The turret must not swing 1.5x
   faster at 90 Hz than at 60.** That is the exact failure the hoist prevents, and it is the
   one that would be visible.
2. **A THROWN GRENADE OR A SPENT ROCKET SLIDING ON THE FLOOR (`propobj.c:5065`).** It must
   come to rest over the same distance at both rates, not slide half again as far.

**If either misbehaves, the hoist is the suspect and `g_GlobalTimerFieldDelta` is the term to
print.** Do not go looking in the renderer.

---

## OWED BACK TO THE DOCS WHEN THE RUN LANDS

- `276` §5 says the `239` gate is NOT met. **The run is what meets it, or fails it.**
- `00-STATE` §3 item 4, and its currency line.
- **If a prediction in §0 comes out wrong, `00-STATE` §4 gains a row.** That section exists
  because every major error on 2026-08-29 came from believing a confident claim nobody had
  marked dead.
