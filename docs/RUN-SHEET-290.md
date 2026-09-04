# RUN SHEET 290 — THE POSE SPINE. `258` STAGE 5. `P6`, `P7`, `P9`. THE FOUNDATION, BEFORE STEREO.

**2026-08-31, session `290`. FIRST VR-WORK SESSION. Not bug work.** Head, both hands and a body
proxy become **game-side state, written BEFORE the tick and readable by game code** — `P6`: THE
SIM OWNS THE POSE, the renderer only consumes it (STAGE 6). **NO HARDWARE builds it or proves it:**
feed it identity, then a synthetic path, exactly as `port_input.c` fakes a pad with
`GETV_MOUSE_SELFTEST`.

**WRITTEN AND VALIDATED OFFLINE — NOT BUILT, NOT RUN.** Rule `1`: every commit and every build is
the owner's, on the main PC. This sheet stops at the first instrument (`258` STAGE 5's own
instruction) and does **not** design the eye loop, hand paths, body-follow or calibration — those
are STAGE 6/7/8 and are not opened here.

**WHY THE POSE COMES BEFORE STEREO, AND THIS IS `258`'s LOAD-BEARING ORDERING CLAIM:** stereo needs
a per-eye **view**, and the eye TRANSLATION lives in the **view matrix** (`255` §1 — projection-only
is a frustum shift, not separation). Build stereo first and it consumes a renderer-side pose; then
`P6` arrives and the whole eye path is reworked — the *"hack now, fix later"* the standing clause
forbids. Built in this order, `P6` costs nothing extra and STAGE 6 consumes it. `194` is the
receipt: one missing term, four faults.

---

## §0 — THE TWO PRECONDITIONS FROM `289`, CHECKED FIRST. **BOTH HOLD.**

1. **`289`'s THREE COMMITS ARE IN.** `[MEASURED]` on the bridge with safe reads only (`git log`,
   `git show --stat` — never `git status`/`git add`, §6):
   - `GoldenEyeVR` HEAD = `080de08` *"289 docs …"*
   - `goldeneye-native` HEAD = `cf24dfd` *"289 native: a RE-RUNNABLE offline harness …"*
   - `vendor/ge-decomp` HEAD = `a163fbb2` *"289 decomp: put `room` on the same denominator …"*,
     and `git show --stat a163fbb2` reads **168 insertions / 11 deletions across three files**
     (`bg.c 48+`, `bg.h 3+`, `propobj.c 128+`) — the exact shape `00-STATE` names. **The decomp is
     NOT uncommitted.**
2. **`tools/fetch-thirdparty.sh verify` READS `15/15`.** `15/15 files match pristine + patch`, run
   on the bridge before any 290 change. **`290` touches nothing under `getv/port/**`, so this is a
   FREE STANDING GATE and no regen is owed** (see §0b).

---

## §0a — WHAT CHANGED IN THE SOURCE, AND WHY. **THREE FILES OF NEW CODE, ONE lv.c SEAM, ALL INERT UNLESS ASKED.**

**The whole system is `#ifdef GE_PORT_NATIVE` and OPT-IN. With no `GETV_*` set it is one identity
struct and two O(1) calls per frame that publish it — no banner, no check, byte-for-byte the game
`289` shipped (`48`'s one-behaviour-change, `2`'s every-knob-stays-reachable).**

### 1. `vendor/ge-decomp/src/game/posespine.h` + `posespine.c` — THE SPINE (new files)
- `GePoseSpine` = **four joints — head, left hand, right hand, body proxy — present from the first
  line even though STAGE 5 drives only the head** (`P7`: two hands and a body are ONE articulated
  system, so the structure must be able to hold all three from the start). Each joint is a `vec3d`
  position + a quaternion orientation (`{0,0,0,1}` identity). A `driven_mask` records which joints
  were actually driven; an undriven joint is identity, never stale garbage.
- **`gePortPoseBeginFrame()`** samples the source (identity, or a synthetic path), stamps the frame
  sequence, and publishes into **static** storage — **structural cost paid ONCE** (`P4`); the only
  per-frame work is one sample and one stamp.
- **`gePoseCurrent()`** returns a `const GePoseSpine *` — **readable by game code, const because
  consumers read the pose, they do not write it** (`P6`/`P9`: the sim owns it).
- **CONVENTION DEFERRED ON PURPOSE.** Orientation is a quaternion, which carries **no matrix-layout
  commitment**. Composing the per-eye VIEW matrix in the engine's **row-vector** convention, with
  engine yaw the **NEGATIVE** of the right-handed one (`00-STATE` §7), is STAGE 6's job. There is a
  matching `quaternion.c`/`.h` already in the decomp for when that stage needs it.

### 2. `vendor/ge-decomp/src/game/lv.c` — THE TWO SEAM CALLS (`+12` lines, `0` deletions)
- **`gePortPoseBeginFrame()` at the TOP of `lvlRender()`**, ahead of the per-player loop and of
  `propsTick()` — so the pose is **written before the tick** and the tick, and any game reader, sees
  **this** frame's pose, not last frame's.
- **`gePortPoseProbeAtTick()` inside the `gePortSimShouldTick()` block, immediately before
  `propsTick()`** — the exact point a game reader touches the pose. This is the instrument's read
  site; inert unless `GETV_POSETEST` is set.
- **The eye loop is NOT here** (STAGE 6). `getPlayerCount()` is **NOT** touched (`258` §1.5: 173
  refs, 35 files, GAME LOGIC — dual-wield gating and glass-buffer sizing). `viSetupCurrentPlayerView`
  (`fr.c:696`, the single projection build site) is **NOT** touched.

### 3. `goldeneye-native/getv/tools/posespine_harness.sh` + `.c` — THE OFFLINE FALSIFIER (new files)
- Compiles the **REAL, UNMODIFIED `posespine.c`** against minimal `f32/s32/u32/vec3d` stubs under
  `-Wall -Wextra -Werror` and drives it. **It IS the file that ships — never a stale copy** (`289`'s
  standing rule). §2 below is its output.

**LINE-ENDINGS AND THE COMMIT SHAPE, CHECKED ON THE BRIDGE (§6's CRLF trap is LIVE):** `git diff
--numstat` shows the decomp worktree is CRLF-dirty for ~2,099 unrelated files. **`lv.c` reads
`12  0` and is LF (`grep -cU $'\r'` = 0); `posespine.c`/`.h` are new and LF.** So the decomp commit
is **STAGE BY EXPLICIT PATH LIST ONLY, NEVER `git add -A`** (§6, `7a4e7bfd` is what a sweep does).

---

## §0b — THE COMMITS, IN ORDER, AND ONLY AFTER THE ARMS ARE WORN. MAIN PC.

**NO REGEN IS OWED** — `290` touched nothing under `getv/port/**`; `verify` reads `15/15` before AND
after the build (re-check it after, it is a free gate). `COMMIT-NOW.cmd` will **not** do step 1 —
`vendor/` is gitignored by `goldeneye-native` and invisible to all three of its passes (§6).

1. **`vendor/ge-decomp` — EXPLICIT PATH LIST, NEVER `-A`.** Stage exactly
   `src/game/lv.c src/game/posespine.c src/game/posespine.h`. **`git diff --cached --stat` must read
   `318 insertions, 0 deletions, 3 files`** (`lv.c 12+`, `posespine.c 237+`, `posespine.h 69+`).
   Message: **`COMMIT-MESSAGE-2026-08-31h-decomp.txt`, in the `GoldenEyeVR` ROOT** (`287`: a message
   file beside the repo it describes is invisible to `commit-now.ps1`).
2. **`goldeneye-native`** — the harness only: `getv/tools/posespine_harness.sh` +
   `getv/tools/posespine_harness.c`. Message: `COMMIT-MESSAGE-2026-08-31h-native.txt`.
3. **`GoldenEyeVR`** — `290`, `RUN-SHEET-290.md`, `00-STATE.md`, `NEXT-SESSION-PROMPT-291.md`.
   Message: `COMMIT-MESSAGE-2026-08-31h.txt`.

**If a `git status`/`git diff` was ever run over the bridge and left a 0-byte `index.lock`, it is
the assistant's litter — confirm 0 bytes, no git running, `Remove-Item` it, re-commit (§6).**

---

## §1 — BUILD, AND THE BINARY GATE. **FIVE STRINGS.** MAIN PC, `build_windows.ps1`.

`posespine.c` lands under `src/game/`, which `build_windows.ps1:298` globs recursively for `*.c`
and does not match its skip regex — **it is picked up with no build-file edit.** `GE_PORT_NATIVE`
is defined for the decomp compile (`build_windows.ps1:210`).

**After the build, gate the binary — a knob not in the exe reads as a clean null (`133`, `268` §4):**
```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
$strings = 'posetest] ON','[getv][pose] GETV_POSE_SELFTEST','posetest] seq=','SUMMARY mode=','VERDICT'
foreach ($s in $strings) {
  $hit = (Select-String -Path .\goldeneye.exe -Pattern ([regex]::Escape($s)) -AllMatches -Encoding Byte -ErrorAction SilentlyContinue)
  "{0,-40} {1}" -f $s, ($(if ($hit) {'FOUND'} else {'MISSING'}))
}
```
**All five must read FOUND. Then re-run `tools/fetch-thirdparty.sh verify` (Git Bash) — still `15/15`.**

---

## §2 — IT IS ALREADY VALIDATED OFFLINE, AND THE VALIDATION IS RE-RUNNABLE. **10/10, `-Wall -Wextra -Werror` CLEAN.**

`getv/tools/posespine_harness.sh` compiles the real `posespine.c` and drives five scenarios whose
answers are known by construction. **Run on the bridge, 2026-08-31, all passed:**

| scenario | env | expected, written first | result |
|---|---|---|---|
| 1 inert | none | **no `[getv][posetest]` output at all** — never ships on | PASS |
| 2 drive only | `GETV_POSE_SELFTEST=10` | selftest banner, path driven, **no VERDICT** | PASS |
| 3 round-trip | `GETV_POSETEST=1`, correct order | `lag=0 err=0.000 OK`, **VERDICT PASS, stale=0** | PASS |
| 4 bracket error | `GETV_POSETEST=1`, **probe before begin-frame** | `lag=1 STALE`, **VERDICT FAIL** | PASS |
| 5 self-falsify | `GETV_POSETEST=2`, correct order | one-tick-late pose, all-stale, **VERDICT PASS (detector fired)** | PASS |

**Scenarios 4 and 5 are the point: an instrument that cannot be made to say FAIL is not an
instrument** (`P5`, rule `15`). Scenario 4 reproduces `267`/`271`/`272`'s bracket error from OUTSIDE
the module (the harness calls the probe before the writer); scenario 5 is the module's own
`GETV_POSETEST=2` self-falsify. **Two independent proofs that the freshness gate fires.**

**WHAT THE HARNESS CANNOT DO (same honesty as `288` §2's pacehist harness): prove the two hooks sit
at the right points in `lvlRender` on the live path. THAT IS THE RUN.**

---

## §3 — THE GATES ON EVERY RUN IN THIS SHEET

**The pose instrument's run condition is part of the knob (§6): it REQUIRES `GETV_SIMDIV=1`.** Under
a divider, begin-frame runs every frame while the probe runs only on tick frames, the two counters
diverge, and `lag` is meaningless. **The block pins it; gate on `props interpolated 0` + zero
`simulation held to` lines (`273` §7.1) or the pose report is VOID.**

Every run also gates on: `GETV_FPS=panel` → `PANEL REPORTED BY SDL: <n> Hz` and a `pace:` line
carrying that number (queried, never hardcoded — `P1`; `289` read 120 Hz, the lead also runs 180);
`[getv][slot] GETV_SLOTFREE resolved to 1 (env=1)`; a terminating `game_exit requested`.

**GATE 2 IS `ours: x=367.333`** in the `VIEWPORT n64` line, at `2560x1369` with `WIDESCREEN=0`. **It
MANDATES the broken front-end menu text — that is OPEN item 2, BY CONSTRUCTION, not a regression**
(`288` §6). **Do NOT move to `1825x1369`: that prints `ours: x=0`, which is also what `WIDESCREEN=1`
prints, so the gate would silently stop discriminating** (rule `17`).

### WHAT WILL LOOK LIKE A REGRESSION AND IS NOT
- **Broken/overflowing front-end menu text** — Gate 2 above, mandated. OPEN item 2.
- **`GETV_ROOMSCISSOR=1` in these blocks, not `0`.** Recent sheets ran `0` (the widescreen-holes
  diagnostic override). **`290` chooses `1` — the SHIPPING DEFAULT — and says so, per the standing
  falsifier note: 290 does not touch culling or clipping, and the pose test reads from the LOG, not
  the picture, so the shipping default is the honest state to measure against.** With `WIDESCREEN=0`
  the game renders 4:3 pillarboxed, so the widescreen holes are largely moot anyway. If any prop
  vanishing or wall hole appears, **it is OPEN item 0/2, not 290's** — do not re-open it (it is DEAD
  to re-run per §5 of `00-STATE`).
- Pillarbox bars — the `WIDESCREEN=0` default's accepted cost.

---

# ►►►► THE ONLY ARMS THIS SESSION — THE FIRST INSTRUMENT, AND NOTHING PAST IT ◄◄◄◄

**Any level boots it; the pose spine is frame-based, not level-based.** `GETV_STAGE=29` is a fast,
known-good boot (§6: a `GETV_STAGE` boot silently runs AGENT and inherits folder-1 options — fine
here, the pose test is indifferent to level and difficulty).

## §4 — ARM A1. **IDENTITY. THE SYSTEM IS INVISIBLE WHEN UNDRIVEN.**

Prove the spine is inert and the game is unchanged with the pose system present but no knob set.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
$env:GETV_SLOTFREE     = "1"
$env:GETV_VSYNC        = "1"
$env:GETV_FPS          = "panel"
$env:GETV_SIMHZ        = "query"
$env:GETV_SIMDIV       = "1"
$env:GETV_WIDESCREEN   = "0"
$env:GETV_ROOMSCISSOR  = "1"
$env:GETV_WINDOW       = "2560x1369"
$env:GETV_STAGE        = "29"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_290_A1_identity.log 2>&1
Select-String -Path run_290_A1_identity.log -Pattern 'posetest\]|GETV_POSE_SELFTEST'
Select-String -Path run_290_A1_identity.log -Pattern 'PANEL REPORTED BY SDL|pace: |slot\] GETV_SLOTFREE|props interpolated|simulation held to|ours: x=|game_exit requested'
```
**GATE A1: the FIRST `Select-String` returns NOTHING** — no pose banner, no check, the instrument
never armed. The second returns the standard gates, `props interpolated 0`, `ours: x=367.333`.

## §5 — ARM A2. **THE SYNTHETIC PATH ROUND-TRIPS AND IS FRESH. THIS IS THE INSTRUMENT.**

`GETV_POSETEST=1`: a known head trajectory (`x = seq·10`, `y = seq·5`, `z = seq·2.5` engine units)
is written at begin-frame and must come back out unchanged, at the same sequence, when the probe
reads it at tick time. Stand or play for a few seconds so frames accumulate.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
$env:GETV_SLOTFREE     = "1"
$env:GETV_VSYNC        = "1"
$env:GETV_FPS          = "panel"
$env:GETV_SIMHZ        = "query"
$env:GETV_SIMDIV       = "1"
$env:GETV_WIDESCREEN   = "0"
$env:GETV_ROOMSCISSOR  = "1"
$env:GETV_WINDOW       = "2560x1369"
$env:GETV_STAGE        = "29"
$env:GETV_POSETEST     = "1"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_290_A2_posetest1.log 2>&1
Select-String -Path run_290_A2_posetest1.log -Pattern 'posetest\] ON|posetest\] seq=|SUMMARY mode=1|VERDICT'
Select-String -Path run_290_A2_posetest1.log -Pattern 'props interpolated|simulation held to|game_exit requested'
```
**GATE A2: `SUMMARY mode=1 … VERDICT PASS`, `stale=0`, `maxerr=0.000`**, and every per-frame line
reads `lag=0 err=0.000 OK`. `props interpolated 0`. **This is the proof that the pose is written
before the tick and read correctly at tick time — `P6` on the live path.**

## §6 — ARM A3. **THE INSTRUMENT IS SHOWN TO FAIL ON HARDWARE.**

`GETV_POSETEST=2`: begin-frame deliberately publishes a **one-tick-late** pose (the exact bracket
error). The freshness gate must catch it every frame.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
$env:GETV_SLOTFREE     = "1"
$env:GETV_VSYNC        = "1"
$env:GETV_FPS          = "panel"
$env:GETV_SIMHZ        = "query"
$env:GETV_SIMDIV       = "1"
$env:GETV_WIDESCREEN   = "0"
$env:GETV_ROOMSCISSOR  = "1"
$env:GETV_WINDOW       = "2560x1369"
$env:GETV_STAGE        = "29"
$env:GETV_POSETEST     = "2"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_290_A3_posetest2_selffalsify.log 2>&1
Select-String -Path run_290_A3_posetest2_selffalsify.log -Pattern 'posetest\] ON mode=2|lag=1|SUMMARY mode=2|VERDICT'
```
**GATE A3: `lag=1 … STALE/MISMATCH` on every printed frame, `SUMMARY mode=2 … stale=frames …
VERDICT PASS (mode 2 must be all-stale: the detector fired)`.** A pass here means the detector CAN
fire; A2's pass then means it did NOT fire when it should not. **Both are needed.**

---

## §7 — WHAT EACH OUTCOME MEANS, WRITTEN BEFORE THE RUN (rule `15`, `P5`)

**These are stated now so the run cannot be rationalised afterwards.**

- **A2 `VERDICT PASS` (expected):** the pose is written before the tick and read intact at tick time.
  `P6` holds on the live path; STAGE 6 may consume `gePoseCurrent()`.
- **A2 prints `lag=1 … STALE` / `VERDICT FAIL`:** the `gePortPoseBeginFrame()` call is bracketed
  **after** the tick, or the probe reads before the write — the real bug this instrument exists to
  catch, `267`/`271`/`272` in a new place. **Fix the seam in `lv.c`, do not touch the instrument.**
- **A2 prints large `err` with `lag=0` (read stays 0 while `expect` grows):** the pose is written
  and never reaches the reader — the accessor or the static state is wrong. **A pose written and
  never read is invisible; the instrument made it visible.**
- **A3 `VERDICT FAIL` (i.e. it did NOT go all-stale):** the freshness stamp is not independent of the
  writer — a uniformly phase-shifted system would then read self-consistent and the whole instrument
  is worthless. **This is why the probe counts its OWN calls, not the writer's sequence.** If A3
  fails, the instrument is not trustworthy and A2's pass means nothing.
- **A1 prints ANY `posetest]` line:** the system is not opt-in and would ship on. **Blocker.**
- **`props interpolated` non-zero in any arm:** `GETV_SIMDIV` did not resolve to 1; the pose report
  is VOID (§3). Re-run with the divider pinned.

---

## §8 — WHERE STAGE 6 PICKS THIS UP (NOT THIS SESSION — DO NOT BUILD IT)

Recorded so the ordering claim is not lost, **and explicitly out of scope for 290**: STAGE 6 nests
an eye loop **inside** the per-player body of `lvlRender` (never `getPlayerCount()`, §1.5), takes the
per-eye view from `gePoseCurrent()`, and **replaces** the projection at `viSetupCurrentPlayerView`
(`fr.c:696`) with four tangents per eye (`P2`). The eye TRANSLATION goes in the VIEW matrix, built
in the engine's **row-vector** convention with engine yaw **negated** (`00-STATE` §7); the decomp's
`quaternion.c` is there for it. **STAGE 5's job was to make the pose exist and be provably fresh
before any of that. It does.**

## §9 — STILL OWED, CARRIED FORWARD (unchanged by 290)

All of `277` §9 · `278` §6's INFERRED hoist-1 read · `279` §5's amount arm · `280` §7.3's black-wall
dump · `274` §7's CONTAMINATED gate · `287` ARM 6, the wear pass, STILL NEVER RUN · `289` R2's
missing `dlgrab`. **290 opened none of these and closed none of them.**

## §10 — DEAD, DO NOT REOPEN (from `00-STATE` §5, restated so 290 does not trip them)

`getROOMID_isRendered` as the vanishing-prop mechanism · the per-room rectangle · `vsync` / the
frame cap / the pacer's sleep / `GETV_SIMHZ` as the smoothness carrier (it is the MOUSE, `258`
STAGE 7) · everything in `00-STATE` §5. **The vanishing props and the mouse turn are parked with
their next arms already named; 290 does not touch either.**
