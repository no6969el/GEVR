# RUN SHEET 287 — finish the switch, and build the smoothness instrument

**2026-08-31.** One build, two knobs, both `#ifdef GE_PORT_NATIVE`, **both default OFF**, both
announcing themselves. With neither set the game does exactly what it did before, so every arm
doubles as its own control (`48`, one behaviour change).

> ## ►►►► THE VSYNC LINE. READ IT ONCE. ◄◄◄◄
> **Every run sheet before this one carries `GETV_VSYNC=0` and it is WRONG for every run that is
> not measuring the GPU (`285`).** This sheet says which of the two each block is, in its own
> heading. **A block that does not say is unfinished.**
>
> | purpose | VSYNC | FPS |
> |---|---|---|
> | **PLAY / LOOK AT ANYTHING** | `1` | `120` |
> | **GPU** (`GETV_GPUTIME`) | `0` | `0` |
> | **CPU** (`WORK_OVER=`) — `287` §A4, in no earlier doc | **`0`** | **`120`** |
>
> **`WORK_OVER` needs BOTH a cap and vsync off.** `port_render.c:1010` says so in its own source:
> *"WITH VSYNC ON, THE VBLANK BLOCK IN SDL_GL_SwapWindow IS STILL INSIDE `work`."* With no cap
> there is no budget and the pacer never sleeps. **So the CPU arm is a third recipe, and at
> `VSYNC=1` it self-declares void with `slept=0` — that is ARM 7B's prediction, not a failure.**

**A BLOCK THAT OMITS A KNOB SILENTLY RESTORES ITS DEFAULT** (`285` S1 lost `WIDESCREEN=0` and
`ROOMSCISSOR=0` this way and read it as a regression). **Every block below carries all seven.**

**GATE EVERY RUN ON ALL FIVE:** the `[getv][roomscissor]` banner (when the knob is set) ·
`ours: x=367.333` in the VIEWPORT line — **`x=0` means widescreen came back ON** ·
`simhz ... 0.500000 fields per frame` · **zero** `simulation held to` · terminating
`[getv] game_exit requested`.

---

## §0 — WHAT CHANGED IN THE SOURCE, AND WHY IT IS NOT WHAT `286` SAID

**`286` §1's list of four sites is wrong in both directions.** A grep of every consumer of
`dword_CODE_bss_8007FFA0[].bbox`:

| site | class | this build |
|---|---|---|
| `bg.c:1051` / `:1132` | SCISSOR | already switched, now carry a site index |
| `chr.c:3437` | SCISSOR | **switched** |
| `explosion.c:874` | SCISSOR | **switched** |
| **`explosion.c:1486` (SMOKE)** | SCISSOR | **switched — `286` MISSED THIS SITE** |
| `propobj.c:7570` | SCISSOR | **switched** |
| **`propobj.c:14007` (`posIsOnScreen`)** | **CULL — draw/don't-draw** | **its own knob, `GETV_PROPCULLBOX`** |
| **`chraction.c:10770` (`chrIsPosOffScreen`)** | **AI / SPAWN LOGIC** | **NEVER. Spirit test.** |
| ~~`chr.c:186`~~ | read-only debug counter | **not a site. `286` listed it; no edit.** |

**`chraction.c:10770` is why the knob is NOT inside `bgGet2dBboxByRoomId`.** One chokepoint there
would be tidier and would silently change what characters do.

**Two new knobs, one new counter set:**
- **`GETV_ROOMSCISSOR=0`** — unchanged name, now six sites. Its banner names all six, and
  **`[getv][roomscissor] sites: bg_pri=.. bg_sec=.. chr=.. expl=.. smoke=.. prop=..`** prints at
  exit. **A ZERO on `chr`/`expl`/`smoke`/`prop` in a level that draws them means that site never
  took** — which is the state `286` was in and could not see.
- **`GETV_PROPCULLBOX=0`** — the cull, not the clip. **A different symptom**: a too-tight rect
  here *removes* a prop rather than clipping it. Candidate mechanism for the **black-wall** class
  that still has no dump (`279` §6, `280` §7.3). **Do not merge it with the holes** (`263` §1).
- **`GETV_PACEHIST=<n>`** — `285` §3.3, below.

---

## §0a — ►►►► STOP. `gfx_sdl2.c` IS GITIGNORED AND REGENERATED, EXACTLY LIKE `gfx_pc.c`. ◄◄◄◄

**`[MEASURED]` this session, from `git ls-files` and `.gitignore:161`.** `GETV_PACEHIST` lives in
**`getv/port/fast3d/gfx_sdl2.c`**, which is **NOT TRACKED** — it is produced by
`tools/fetch-thirdparty.sh` from a pristine copy plus
`getv/patches/thirdparty/0001-getv-port-layer.patch` (the patch already carries a `gfx_sdl2.c`
hunk at line 7876). **`00-STATE` §6 names this trap for `gfx_pc.c` only. It applies here too, and
nobody had written that down.**

**Two consequences, both live right now:**
1. **`tools/fetch-thirdparty.sh verify` WILL NOW FAIL** — the file on disk no longer equals
   pristine + patch, because it carries an edit the patch does not. **That failure is correct and
   expected until step 2 is done.**
2. **A regen before that would DELETE the instrument**, and `271` §7 records exactly this class
   hiding behind two silent fallthroughs. **`268` was committed without a regen and `GETV_DLGRAB`
   was absent from a fresh clone for two days.**

**THE FIX IS ONE COMMAND, AND IT IS A MAIN-PC ACTION — GIT BASH, NOT THE BRIDGE, NOT MSYS2**
(the mount refuses to unlink; MSYS2's bash has no `git`). **Run it AFTER the build passes and the
arms are worn, so the patch captures the version that actually ran:**

```
"C:\Program Files\Git\bin\bash.exe" -lc "cd /f/Projects/GEVR/GoldenEyeVR/goldeneye-native && tools/fetch-thirdparty.sh regen && tools/fetch-thirdparty.sh verify"
```
**THE GATE IS `verify`: `15/15 files match pristine + patch`. A byte count is not the gate.**
The script now refuses an empty regen, refuses one under half the old size, and refuses a write it
could not make — but **`port_support.c` and the four decomp files are TRACKED and are not affected
by any of this.**

## §1 — BUILD, AND THE BINARY GATE

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
& getv\build_windows.ps1 -Target all *> build_287_sixsites_pacehist.log 2>&1
Select-String -Path build_287_sixsites_pacehist.log -Pattern 'error|Error|FAILED' | Select-Object -First 20
Get-Item F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows\goldeneye.exe |
    Select-Object FullName, LastWriteTime, Length
$exe = 'F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows\goldeneye.exe'
$txt = [Text.Encoding]::ASCII.GetString([IO.File]::ReadAllBytes($exe))
foreach ($k in 'GETV_ROOMSCISSOR','GETV_PROPCULLBOX','GETV_PACEHIST') {
    if ($txt.Contains($k)) { "$k IS IN THE BINARY" } else { "$k IS **NOT** IN THE BINARY -- STOP" }
}
foreach ($k in 'SIX SITES','pacehist','PANEL REPORTED BY SDL') {
    if ($txt.Contains($k)) { "marker '$k' present" } else { "marker '$k' MISSING -- STALE BUILD, STOP" }
}
```
**All six must say IS IN / present.** The timestamp must be newer than **`2026-08-31 01:07`**
(the `286` binary, 18,021,956 bytes). **`gfx_pc.c` is untouched, so no regen is needed.**

---

# ►►►► PART ONE — SMOOTHNESS. THIS OUTRANKS EVERYTHING ELSE. ◄◄◄◄

`285` §4: *a hole in a wall is a blemish; judder is the thing that makes people take the headset
off.* Run PART ONE first even if PART TWO looks more finished.

## §2 — WHAT `GETV_PACEHIST` IS, IN ONE PARAGRAPH

It stamps the clock the instant `SDL_GL_SwapWindow()` returns and records the **gap between
consecutive presented frames** — the whole distribution, not the mean. **`285` §3.3: a mean of
16.67 ms is identical for an even run and one alternating 8 and 25**, and the mean is the only
statistic this project has ever had. It bins each gap against the panel's own refresh period, so
`1x` reads *shown once* and `2x` reads *shown twice*. **It also prints the panel's refresh rate,
which nothing in this port has ever asked for** — a grep of `getv\port` for
`GetCurrentDisplayMode`/`refresh_rate` returns **zero hits**, so "the panel is 120 Hz" has been
`[REPORTED]` all along, and every `285` candidate is defined against it.

**It also scores `285` §1.1 without touching the pacer**, which `285` §3.4 requires: it
accumulates the sleep the pacer **asked** for beside the one `271` already **measures**, and
prints the difference. **A booking error near zero retracts §1.1.**

## §3 — THE PREDICTIONS, WRITTEN BEFORE THE RUNS (rule `15`)

| arm | expected |
|---|---|
| **4A** `VSYNC=1 FPS=120`, 120 Hz panel | **≥95% in the `1x` bin** |
| **4B** `VSYNC=1 FPS=60`, same panel | **≥95% in the `2x` bin.** *If this does not move, the stamp is in the wrong place and every other arm is void.* |
| **4C** `VSYNC=0 FPS=0` | **smeared, no mode.** The negative control |
| stamp accidentally before the swap | 4C reads intervals near **0 ms** |
| SDL will not report the panel | prints `UNKNOWN -- THE BINS ARE VOID` rather than a plausible number |

**AND THE FALSIFIER THAT COSTS NOTHING: if SDL reports 60 Hz, `GETV_FPS=120` with `vsync=1` is
asking for double the panel and `285` S1's "super smooth" needs re-reading before anything is
built on it.**

**Arm 4A runs in the FRONT-END MENU first** — the boring frame, and `285` §2's third question
(no world simulation there, so it separates presentation from simulation in one look). `279` §7:
a detector tuned on the positive frame passes its own contract until it meets the negative one.

## §4A — PLAY RECIPE. Front-end menu, then a level. **VSYNC=1 — this is a LOOK-AT-IT run.**

Sit in the **front-end menu** for ~60 s without pressing anything, then start a level and
**turn fast, repeatedly, the way the complaint describes.** Quit normally.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
$env:GETV_VSYNC       = "1"
$env:GETV_FPS         = "120"
$env:GETV_SIMHZ       = "query"
$env:GETV_SIMDIV      = "1"
$env:GETV_WIDESCREEN  = "0"
$env:GETV_ROOMSCISSOR = "0"
$env:GETV_WINDOW      = "2560x1369"
$env:GETV_PACEHIST    = "600"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_287_4A_pacehist_play120.log 2>&1
Select-String -Path run_287_4A_pacehist_play120.log -Pattern 'PANEL REPORTED BY SDL' | Select-Object -First 1
Select-String -Path run_287_4A_pacehist_play120.log -Pattern 'pacehist' | Select-Object -Last 12
Select-String -Path run_287_4A_pacehist_play120.log -Pattern 'roomscissor\]|ours: x=|fields per frame|simulation held to|game_exit requested'
```

## §4B — THE VALIDATION ARM. Same but `FPS=60`. **VSYNC=1 — a LOOK-AT-IT run.**

**This is the arm that proves the instrument, not the arm that answers the question.** Same
level, same kind of movement, ~60 s.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
$env:GETV_VSYNC       = "1"
$env:GETV_FPS         = "60"
$env:GETV_SIMHZ       = "query"
$env:GETV_SIMDIV      = "1"
$env:GETV_WIDESCREEN  = "0"
$env:GETV_ROOMSCISSOR = "0"
$env:GETV_WINDOW      = "2560x1369"
$env:GETV_PACEHIST    = "600"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_287_4B_pacehist_validate60.log 2>&1
Select-String -Path run_287_4B_pacehist_validate60.log -Pattern 'pacehist' | Select-Object -Last 12
Select-String -Path run_287_4B_pacehist_validate60.log -Pattern 'ours: x=|fields per frame|simulation held to|game_exit requested'
```

## §4C — THE NEGATIVE CONTROL. **VSYNC=0 + FPS=0 — this IS one of the two, and it is here to be UGLY.**

**Short run — `GETV_FPS=0` locks up on Cradle within seconds, 3 of 3** (`273` §7.3). Use the
front-end or Facility, ~30 s, then quit.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
$env:GETV_VSYNC       = "0"
$env:GETV_FPS         = "0"
$env:GETV_SIMHZ       = "query"
$env:GETV_SIMDIV      = "1"
$env:GETV_WIDESCREEN  = "0"
$env:GETV_ROOMSCISSOR = "0"
$env:GETV_WINDOW      = "2560x1369"
$env:GETV_PACEHIST    = "600"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_287_4C_pacehist_uncapped.log 2>&1
Select-String -Path run_287_4C_pacehist_uncapped.log -Pattern 'pacehist' | Select-Object -Last 12
Select-String -Path run_287_4C_pacehist_uncapped.log -Pattern 'game_exit requested'
```

## §4D — THE FREE ONE. **NO BUILD, NO KNOB, A STOPWATCH.** `285` §1.4.

**`287` §A2 answers `285` §1.4 from source and the answer is that the TURN is fine:** the yaw
integration carries the delta (`bondview2.c:7366`,
`vv_theta + speedtheta * g_GlobalTimerDelta * 3.5f`) and **every** ramp term in
`bondviewCurrentPlayerUpdateSpeedTheta` (`:4573-4630`) carries it too. **This is a source read,
not a measurement** — `275` §1's grep-for-a-guard and `277` §6.2's numbers-without-mechanism are
what happens when that distinction is skipped, so it gets a stopwatch:

**Full-deflection 360° spin, timed, `FPS=60` then `FPS=120`, `SIMHZ=query` both, same spot.**
- **Equal times → `285` §1.4 is retracted** and the smoothness question is entirely presentation.
- **120 spins ~2× faster → the source read is wrong**, §1.4 is alive, and it joins `RB-04`'s
  second half as a game-feel decision, not a bugfix.

**And the mouse-vs-pad question in `285` §2 needs no arm at all:** `port_input.c` accumulates
`ge_mouse_pend_x` **into the stick**, so the mouse reaches `moveData.analogTurn` and travels the
identical path. Mechanically they are the same thing.

---

# PART TWO — THE HOLES

## §5 — ARM 5: DID THE EXTENSION TAKE? **VSYNC=1 — a LOOK-AT-IT run.**

**Same spot as `283`/`284` arm A** (Streets, `GETV_STAGE=29`). **Stand still, artifact on screen,
F9 twice.** Quit normally.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
$env:GETV_VSYNC       = "1"
$env:GETV_FPS         = "120"
$env:GETV_SIMHZ       = "query"
$env:GETV_SIMDIV      = "1"
$env:GETV_WIDESCREEN  = "0"
$env:GETV_ROOMSCISSOR = "0"
$env:GETV_WINDOW      = "2560x1369"
$env:GETV_STAGE       = "29"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_287_5_sixsites_streets.log 2>&1
Select-String -Path run_287_5_sixsites_streets.log -Pattern 'roomscissor\] sites:'
Select-String -Path run_287_5_sixsites_streets.log -Pattern 'roomscissor\]|ours: x=|fields per frame|simulation held to|game_exit requested'
(Select-String -Path run_287_5_sixsites_streets.log -Pattern 'dlgrab_\d+\.txt' -AllMatches).Matches.Value | Sort-Object -Unique
```

**THE GATES, IN ORDER:**
1. **`sites:` must be non-zero on `chr`, `prop`** at minimum, and on `expl`/`smoke` if anything
   exploded. **A zero there means that site never took and the run says nothing about it.**
2. **The dump must no longer carry a sub-view rect.** `dlgrab_8040`, taken WITH the old switch on,
   still carried **`(832,120)-(1276,840)` with 613 triangles under it** — that is the falsifier.
   **Read the dump the last line above names, by its own announcement, not by timestamp**
   (`279` §2 — `278` mislabelled six files that way).
3. `[REPORTED]`: are the two surviving holes gone?

**EXPECTED AND NOT A SECOND FAULT:** with no per-room rectangle anywhere, rooms, characters and
props overdraw each other. **Judge the SLABS, not the picture. This must never ship on.**

## §6 — ARM 6: THE WEAR PASS. NEVER BEEN RUN. **VSYNC=1 — LOOK-AT-IT runs.**

`286` §3.2. **Transparency ordering is what the rectangle used to contain** (`sub_GAME_7F0B3C8C`'s
buckets). **Streets at four viewpoints is not a test of that.** Four separate runs — change only
`GETV_STAGE` and the log name:

| level | `GETV_STAGE` | what to look at |
|---|---|---|
| Facility | `34` | **the glass.** Ordering, double-draws, glass through walls |
| Dam | `33` | distance, water, the outdoor draw order |
| Cradle | `41` | the hardest level in the game (`272` §5.1) |
| front-end | **omit `GETV_STAGE`** | menus, folder art, the cast |

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
$env:GETV_VSYNC       = "1"
$env:GETV_FPS         = "120"
$env:GETV_SIMHZ       = "query"
$env:GETV_SIMDIV      = "1"
$env:GETV_WIDESCREEN  = "0"
$env:GETV_ROOMSCISSOR = "0"
$env:GETV_WINDOW      = "2560x1369"
$env:GETV_STAGE       = "34"          # 33 = Dam, 41 = Cradle; REMOVE this line for the front-end
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_287_6_wear_facility.log 2>&1
Select-String -Path run_287_6_wear_facility.log -Pattern 'roomscissor\] sites:'
Select-String -Path run_287_6_wear_facility.log -Pattern 'roomscissor\]|ours: x=|fields per frame|simulation held to|game_exit requested'
```

**`[REPORTED]` is the instrument here and it outranks the log** (`HANDOVER` §5).

## §7 — ARM 7: THE BLACK-WALL ARM. `GETV_PROPCULLBOX=0`. **VSYNC=1 — a LOOK-AT-IT run.**

**A DIFFERENT SYMPTOM, RUN SEPARATELY ON PURPOSE.** `279` §6 measured every slab in all five
admissible frames as the **see-through** class and said **not one frame shows the black-wall
symptom** — it has no dump at all. If a prop being culled entirely is behind it, this knob moves
it. **Run this only after ARM 5, and change nothing else.**

**Cost, stated in advance: props retail would cull get drawn. That is the price, not a fix.**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
$env:GETV_VSYNC        = "1"
$env:GETV_FPS          = "120"
$env:GETV_SIMHZ        = "query"
$env:GETV_SIMDIV       = "1"
$env:GETV_WIDESCREEN   = "0"
$env:GETV_ROOMSCISSOR  = "0"
$env:GETV_PROPCULLBOX  = "0"
$env:GETV_WINDOW       = "2560x1369"
$env:GETV_STAGE        = "29"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_287_7_propcullbox.log 2>&1
Select-String -Path run_287_7_propcullbox.log -Pattern 'propcullbox\]|roomscissor\] sites:'
Select-String -Path run_287_7_propcullbox.log -Pattern 'ours: x=|fields per frame|simulation held to|game_exit requested'
```

**If a black wall is on screen, F9 twice — `280` §7.3 has been owed that dump for four sessions.**

---

# PART THREE — THE COST

## §8 — ARM 8A: THE GPU. **VSYNC=0 + FPS=0. THIS IS THE GPU RECIPE — the ONE place it belongs.**

**Short run. `GETV_FPS=0` locks Cradle within seconds** (`273` §7.3): stand still, let it settle,
take the sample, quit. Facility (`34`) will run long; Cradle (`41`) will not.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
$env:GETV_VSYNC       = "0"
$env:GETV_FPS         = "0"
$env:GETV_SIMHZ       = "query"
$env:GETV_SIMDIV      = "1"
$env:GETV_WIDESCREEN  = "0"
$env:GETV_ROOMSCISSOR = "0"
$env:GETV_WINDOW      = "2560x1369"
$env:GETV_STAGE       = "41"
$env:GETV_GPUTIME     = "1"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_287_8A_gpu_cradle.log 2>&1
Select-String -Path run_287_8A_gpu_cradle.log -Pattern 'gputime|CONTAMINATED' | Select-Object -Last 15
Select-String -Path run_287_8A_gpu_cradle.log -Pattern 'ours: x=|simulation held to|game_exit requested'
```
**If it prints `CONTAMINATED`, the cap got back in — the figure is void** (`273` §2).
**Cut the window list at the `lvlStageLoad` line numbers; a tail is not a sample** (`273` §1).

## §8B — ARM 8B: THE CPU. **VSYNC=0 + FPS=120 — `287` §A4's third recipe.**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
$env:GETV_VSYNC       = "0"
$env:GETV_FPS         = "120"
$env:GETV_SIMHZ       = "query"
$env:GETV_SIMDIV      = "1"
$env:GETV_WIDESCREEN  = "0"
$env:GETV_ROOMSCISSOR = "0"
$env:GETV_WINDOW      = "2560x1369"
$env:GETV_STAGE       = "41"
$env:GETV_BUDGET      = "600"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_287_8B_cpu_cradle.log 2>&1
Select-String -Path run_287_8B_cpu_cradle.log -Pattern 'WORK_OVER=' | Select-Object -Last 10
Select-String -Path run_287_8B_cpu_cradle.log -Pattern 'ours: x=|simulation held to|game_exit requested'
```
**`slept=0` plus `PACER NEVER SLEPT` means the split is void** — expected only if the cap did not
take. **Run the same block once with `GETV_VSYNC="1"` to see it fail loudly; that is the check
that this is `271`'s instrument and not a plausible number.**

### THE BUDGET AT 120 Hz IS NOT 11.111 ms
`[MEASURED]` CPU `0.890` + GPU `0.832` = `1.722` ms, both on Cradle (`272` §5.2, `273` §5.1).
**Those were taken against a 90 Hz budget of `11.111` ms. At 120 Hz the budget is `8.333` ms**,
and **neither figure has ever been taken at 120 Hz.** `1.722 / 8.333` is a different headroom
claim from `1.722 / 11.111`; ARM 8A/8B are what make the 120 Hz version `[MEASURED]` instead of
carried forward.

---

## §9 — AND THEN THE THREE DEFAULTS (`286` §2), EACH THE SESSION LEAD'S CALL
1. **`configWidescreen`** (`port_support.c:203`, still `1`). Decided in doc as **OFF** (`00-STATE`
   §3), **never made, built or run.** Cost: pillarbox bars until `P3`.
2. **`GETV_ROOMSCISSOR`** default. **It is a FALSIFIER and its own banner says it must never ship
   on** — so this is not "flip it", it is "what is the real fix now that six sites are known".
   **Do not decide it before ARM 5 and ARM 6.**
3. **The vsync line in all four run sheets in `repo\docs`** (`260`, `276`, `282`, `283`). All
   carry `GETV_VSYNC=0` with no statement of which of the two they are.

## §10 — STILL OWED, CARRIED FORWARD HONESTLY
- The same-spot two-resolution amount arm (`279` §5) — **still no number.**
- Whether retail shows any of this (`283` §5.2). The clipping is decomp-matching code.
- All of `277` §9, **untouched through five sessions now**: the two hoist sites driven, the two
  intro-skip audio falsifiers, the `MoveBond` executions-per-second counter. Plus `278` §6's
  `[INFERRED]` hoist-1 read.
- `SETUP.md` §3.5 owes `229` §9's two CSV traps.
- **`GETV_REALCLOCK` is still owed a `CONTAMINATED` gate** (`274` §7, rule `17`).
