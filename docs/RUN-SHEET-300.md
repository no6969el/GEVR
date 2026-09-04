# RUN-SHEET-300 — LAND `299`'s BUILD: `GL_DEPTH_CLAMP`, THE FILTERING FIX, THE SKIP SPLIT

**Written OFFLINE 2026-09-03 at the end of `299`. NOTHING BUILT.** Baseline before this sheet:
`HEAD` `3de0db0` / `e380916` / `1f0f7aae`, `goldeneye.exe` `2026-09-02 19:29` (18,058,803 bytes).

**►►►►►►►► §1, §2 AND §3 ARE WORN. `[MEASURED]` 2026-09-03 02:40. THE SESSION STOPPED THERE.
◄◄◄◄◄◄◄◄** The regen ran, the build succeeded, and the binary carries the change:
`goldeneye.exe` **18,062,771 bytes** at `02:40`, `windows port layer: 59 built, 0 failed`, 0 failed
in every group, `goldeneye_300.map` saved. **`ge_depthclamp.o` is in `libge.a` with `0x360` bytes
of `.text` and all three symbols at real addresses, and its GL references resolve to `glIsEnabled`
and `glGetError` — so the glob saw the new file and the verify path was not dead-stripped.** All
six new strings are in the exe. **`299` §9.6.**

**►► §4, §5 AND §6 ARE SUPERSEDED BY `RUN-SHEET-301` §5/§6/§7 (2026-09-03, `301`). They still
have not run, and they should not be run from here.** See the banner on each.

**►► §4, §5 AND §6 HAVE NOT RUN. THEY ARE THE NEXT SESSION'S FIRST ACTION.** Nothing below §3 has
been executed, and **a string in a binary is not a run** (`279` §7): whether the driver accepts
`glEnable(GL_DEPTH_CLAMP)` and whether the artefact goes away is entirely §4's question.

**THE ORDER IS LOAD-BEARING: §1 gates → §2 REGEN → §3 build → §4 the A/B → §5 filtering →
§6 the skip split → §7 commit.** §2 before §3 is not a style preference: **two of the four edited
port files are gitignored and regenerated, so a build that precedes the regen builds code that is
in no commit** (`268` lost `GETV_DLGRAB` for two days exactly this way).

---

## §1 — THE OFFLINE GATES, ON THE MAIN PC. **BEFORE ANYTHING ELSE.**

Worn on the bridge under `gcc 11.4.0`; the main PC has MSYS2/mingw and the harnesses invoke bare
`gcc`. Strong evidence, **different event** (`RUN-SHEET-295` §11).

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
bash getv/tools/depthclamp_harness.sh
bash getv/tools/stereo_harness.sh
py getv\tools\stereo_disparity.py --selftest
```

**GATE §1 — four things:**

1. **`depthclamp_harness: 17 checks, 0 failed` / `VERDICT PASS`.** New this session. It drives the
   two decisions in `ge_depthclamp.c` that can be silently wrong: the GL_VERSION core test and the
   GL_EXTENSIONS whole-word test. **Its negatives matter as much as its positives** — `OpenGL ES 3.2`
   must NOT count as core, and `GL_ARB_depth_clamp_but_not_really` must read FALSE.
2. **`63 passed, 0 failed` / `VERDICT PASS`** from `stereo_harness.sh`, whose nine-file real-header
   syntax gate now covers the edited `chrprop.c`.
3. **The three-arm pairing falsifier still reads `pairmono 0 / pairoff 2 / pairon 0`** — the middle
   arm must still fire. A harness whose falsifier has gone quiet is not a harness.
4. `stereo_disparity.py --selftest` recovers the injected `-37`.

---

## §2 — **THE REGEN. MAIN PC, GIT BASH. THIS IS THE STEP THAT GETS SKIPPED.**

`299` edited **four** files under `getv/port/`. Two are ours and tracked
(`ge_depthclamp.c`, `ge_depthclamp.h`); **two are gitignored and regenerated from pristine +
patch** (`gfx_pc.c`, `gfx_opengl.c`) and reach a commit **only** through
`getv/patches/thirdparty/0001-getv-port-layer.patch`.

```bash
cd /f/Projects/GEVR/GoldenEyeVR/goldeneye-native
tools/fetch-thirdparty.sh verify
tools/fetch-thirdparty.sh regen
tools/fetch-thirdparty.sh verify
git --no-optional-locks diff --stat -- getv/patches/thirdparty/0001-getv-port-layer.patch
```

**GATE §2 — and read them in this order:**

1. The **first** `verify` is expected to report **`DIFFERS`** on `gfx_pc.c` and `gfx_opengl.c`.
   **That is the point: it is the proof the edits are not yet in the patch.** If it reads `15/15`
   before the regen, the edits are not on disk and §3 will build the old code.
2. `regen` completes without `diff failed`.
3. The **second** `verify` reads **`fetch-thirdparty: 15/15 files match pristine + patch`.**
   **A byte count is not the gate. `15/15` is the gate.**
4. `git diff --stat` on the patch shows it **changed**. A zero-line diff means the regen wrote an
   empty patch — which has happened before (`fetch-thirdparty.sh:187`'s own comment records the
   truncate-before-subshell bug that destroyed it once).

---

## §3 — THE BUILD

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv
.\build_windows.ps1 *> F:\Projects\GEVR\GoldenEyeVR\build_300_depthclamp.log 2>&1
Select-String -Path F:\Projects\GEVR\GoldenEyeVR\build_300_depthclamp.log -Pattern 'first failure|conflicting types|error|Build succeeded|goldeneye.exe' | Select-Object -First 20
Get-Item F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
Copy-Item F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows\goldeneye.map F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows\goldeneye_300.map -Force
```

**►► READ THE FIRST FAILURE LINE, NOT THE LAST ERROR** (`00-STATE` §6). A conflicting declaration
survives `-w`, kills one object file, and buries itself under a wall of `undefined reference` that
reads like *"the new file was never added to the build"*.

**►► WORN. `[MEASURED]` 2026-09-03 02:40, all three gates met:** exe moved to `18,062,771 bytes`
(from `18,058,803` at `2026-09-02 19:29`); `ge_depthclamp.o` present in `libge.a` at
`goldeneye_300.map:5991`, so **the glob did see it**; `.map` saved. The build log reads
`167 / 234 / 40 / 59 / 2 built, 0 failed`.

**GATE §3 — three things:**

1. **The exe's `LastWriteTime` moves off `2026-09-02 19:29`.** If it does not, nothing was built.
2. **`ge_depthclamp.c` compiled at all.** It is a NEW file in `getv/port/fast3d/`, and
   `build_windows.ps1:341` globs that directory, so it should be picked up with no build-script
   edit. **If the link fails with `undefined reference to 'ge_depth_clamp_init'`, the glob did not
   see it** — that is the one build-system assumption `299` could not test offline.
3. **The `.map` is saved beside the binary** (`00-STATE` §6: a rebuild overwrites `goldeneye.map`
   and strands every earlier backtrace).

---

## §4 — D1 / D2. **THE A/B THAT SAYS WHETHER THE FIX WORKS.**

**►►►►►►►► SUPERSEDED BY `RUN-SHEET-301` §5, §6 AND §7. DO NOT RUN §4, §5 OR §6 FROM THIS
SHEET. ◄◄◄◄◄◄◄◄** They were written against the `02:40` binary, which `301`'s build replaces, and
they read counters that `301` proved were misreporting: the near counters shared one line with
knob-independent ones (`N1`), the rebuild census sampled one frame in n (`H2`), and `list=` did
not balance the sum (`H3`). `RUN-SHEET-301` carries the same three arms with the same intent,
re-gated: an automatic binary check, an `H5` overwrite guard, `GETV_ARM` set, and reads for the
lines that replaced the ones below. **This section is kept because it is the record of what was
planned on 2026-09-03, not because it is runnable.**


**Same alley, same corner as `299` N1-N3** — pressed against the brick wall, alley ahead, the red
wall and the jeep on the right (`grabs_298_D/dlgrab_7930.bmp` is that view). **Stand still, F9
three times, quit.** One behaviour change between the arms (`48`).

### 4.1 — D1. **The fix ON (shipping default).**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
Get-ChildItem .\dlgrab_*.txt,.\dlgrab_*.bmp -ErrorAction SilentlyContinue | Measure-Object | Select-Object -ExpandProperty Count
$env:GETV_SLOTFREE    = "1"
$env:GETV_VSYNC       = "1"
$env:GETV_FPS         = "panel"
$env:GETV_SIMHZ       = "query"
$env:GETV_SIMDIV      = "1"
$env:GETV_WIDESCREEN  = "0"
$env:GETV_ROOMSCISSOR = "1"
$env:GETV_WINDOW      = "2560x1369"
$env:GETV_STAGE       = "29"
$env:GETV_DIFFICULTY  = "0"
$env:GETV_DEPTHCLAMP  = "1"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_300_D1_depthclamp_on.log 2>&1
Select-String -Path run_300_D1_depthclamp_on.log -Pattern 'GETV_FPS=panel'
Select-String -Path run_300_D1_depthclamp_on.log -Pattern 'depthclamp\]'
Select-String -Path run_300_D1_depthclamp_on.log -Pattern 'GETV_SLOTFREE resolved|GETV_STAGE override'
Select-String -Path run_300_D1_depthclamp_on.log -Pattern 'roomscissor\]|proproomtest\]|getv\]\[stereo\]'
Select-String -Path run_300_D1_depthclamp_on.log -Pattern 'dlgrab_|getv\]\[shot\]'
Select-String -Path run_300_D1_depthclamp_on.log -Pattern 'EXCEPTION|game_exit requested'
Select-String -Path run_300_D1_depthclamp_on.log -Pattern '\[getv\]\[far\]' | Select-Object -Last 1
New-Item -ItemType Directory -Force -Path .\grabs_300_D1 | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_300_D1 -Force -ErrorAction SilentlyContinue
Get-ChildItem .\grabs_300_D1 | Select-Object Name, Length, LastWriteTime
```

### 4.2 — D2. **The fix OFF. This must reproduce `299` N1 exactly.**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
Get-ChildItem .\dlgrab_*.txt,.\dlgrab_*.bmp -ErrorAction SilentlyContinue | Measure-Object | Select-Object -ExpandProperty Count
$env:GETV_SLOTFREE    = "1"
$env:GETV_VSYNC       = "1"
$env:GETV_FPS         = "panel"
$env:GETV_SIMHZ       = "query"
$env:GETV_SIMDIV      = "1"
$env:GETV_WIDESCREEN  = "0"
$env:GETV_ROOMSCISSOR = "1"
$env:GETV_WINDOW      = "2560x1369"
$env:GETV_STAGE       = "29"
$env:GETV_DIFFICULTY  = "0"
$env:GETV_DEPTHCLAMP  = "0"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_300_D2_depthclamp_off.log 2>&1
Select-String -Path run_300_D2_depthclamp_off.log -Pattern 'GETV_FPS=panel'
Select-String -Path run_300_D2_depthclamp_off.log -Pattern 'depthclamp\]'
Select-String -Path run_300_D2_depthclamp_off.log -Pattern 'GETV_SLOTFREE resolved|GETV_STAGE override'
Select-String -Path run_300_D2_depthclamp_off.log -Pattern 'roomscissor\]|proproomtest\]|getv\]\[stereo\]'
Select-String -Path run_300_D2_depthclamp_off.log -Pattern 'dlgrab_|getv\]\[shot\]'
Select-String -Path run_300_D2_depthclamp_off.log -Pattern 'EXCEPTION|game_exit requested'
Select-String -Path run_300_D2_depthclamp_off.log -Pattern '\[getv\]\[far\]' | Select-Object -Last 1
New-Item -ItemType Directory -Force -Path .\grabs_300_D2 | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_300_D2 -Force -ErrorAction SilentlyContinue
Get-ChildItem .\grabs_300_D2 | Select-Object Name, Length, LastWriteTime
```

### 4.3 — GATES, AND EVERY OUTCOME MEANS SOMETHING DIFFERENT

**BANNER GATE FIRST — `GETV_DEPTHCLAMP` is the one knob here that has one, and `299` §5.1's rule is
that a knob whose value is not echoed by a banner is a knob you have not set:**

| arm | required `[getv][depthclamp]` line |
|---|---|
| D1 | **`GL_DEPTH_CLAMP ON (core 3.2+, GL_VERSION=4.6.0 NVIDIA ...)`** |
| D2 | **`GETV_DEPTHCLAMP=0 -- GL depth clamping NOT enabled`** |

**If D1 prints `UNAVAILABLE`, STOP.** The line names why in its own text. On an RTX 5090 reporting
`4.6.0` this cannot legitimately happen, so it means the version parse or the enable failed and
that is a code fault, not a driver one — **and `299`'s harness has 17 checks that say it should not.**

**CENSUS GATE — and this is where the fix proves itself without anyone's eyes:**

| arm | `NEAR straddle` | `NEAR clamped` | far `clamped` |
|---|---|---|---|
| **D1** | **thousands** | **0** | **0** |
| **D2** | thousands | `straddle + all_near` | non-zero |

**D1's double zero is the receipt of the banner, NOT a masked zero** — `straddle` in the thousands
is what makes it a result (`289` R2's rule). **D2's must match `299` N1's shape exactly**
(`clamped = straddle + all_near`); if it does not, `GETV_DEPTHCLAMP=0` is not restoring the old path
and the A/B is void.

**THE VERDICT IS THE OWNER'S EYES, ON THE SAME WALL:**

| D1 | D2 | reading |
|---|---|---|
| **artefact GONE** | **artefact PRESENT** | **THE FIX WORKS.** `gfx_pc.c:3733` was right and `299` §8.1 is closed |
| present | present | The extension is on and the artefact survives it. **`299` §7 falsifier 2 fires: the depth-gradient reading is wrong even though the knob moved** |
| GONE | GONE | **VOID** — D2 did not restore the old path. Check its banner and its census before reading anything into it |

**AND LOOK FOR WHAT THE FIX MIGHT COST.** `GL_DEPTH_CLAMP` disables z clipping at **both** planes,
so geometry that used to be clipped at the FAR plane now rasterises clamped to maximum depth.
`298` §4.4's `all_near` number is retracted (`00-STATE` §4) and **cannot** be used to measure this.
**Look at the far field in D1 and say whether anything appears that should not.**

---

## §5 — THE FILTERING ARM. **IT HAS NEVER TAKEN, AND IT VOIDED TWO OWNER CYCLES.**

**►►►►►►►► SUPERSEDED BY `RUN-SHEET-301` §5, §6 AND §7. DO NOT RUN §4, §5 OR §6 FROM THIS
SHEET. ◄◄◄◄◄◄◄◄** They were written against the `02:40` binary, which `301`'s build replaces, and
they read counters that `301` proved were misreporting: the near counters shared one line with
knob-independent ones (`N1`), the rebuild census sampled one frame in n (`H2`), and `list=` did
not balance the sum (`H3`). `RUN-SHEET-301` carries the same three arms with the same intent,
re-gated: an automatic binary check, an `H5` overwrite guard, `GETV_ARM` set, and reads for the
lines that replaced the ones below. **This section is kept because it is the record of what was
planned on 2026-09-03, not because it is runnable.**


`299` §9.2 fixed `key_filtering()`'s missing `over` guard, so `GETV_FILTERING` now obeys the
documented CLI > environment > file > default precedence. **The gate is the banner, and only the
banner** (`298` §5, `00-STATE` §6).

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
$env:GETV_SLOTFREE    = "1"
$env:GETV_VSYNC       = "1"
$env:GETV_FPS         = "panel"
$env:GETV_SIMHZ       = "query"
$env:GETV_SIMDIV      = "1"
$env:GETV_WIDESCREEN  = "0"
$env:GETV_ROOMSCISSOR = "1"
$env:GETV_WINDOW      = "2560x1369"
$env:GETV_STAGE       = "29"
$env:GETV_DIFFICULTY  = "0"
$env:GETV_FILTERING   = "0"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_300_F1_filtering_point.log 2>&1
Select-String -Path run_300_F1_filtering_point.log -Pattern 'getv\]\[config\] file'
Select-String -Path run_300_F1_filtering_point.log -Pattern 'GETV_FPS=panel|EXCEPTION|game_exit requested'
```

**GATE §5: the `[getv][config] file ...` line must end `filtering=0`.** It read `filtering=2` in
both `298` arms with the same environment set. **If it still reads `2`, the fix did not take and
nothing about the blur question may be concluded** — go back to `ge_config.c:413` rather than to
the picture. **The question it was asked for is still open:** is the near-wall blur magnification
of a low-resolution texture, or a wrong texture size? Walk to the railing and the brick.

---

## §6 — THE SKIP SPLIT. **ONE RUN, AND IT ANSWERS `299` §8.3's `[UNDETERMINED]`.**

**►►►►►►►► SUPERSEDED BY `RUN-SHEET-301` §5, §6 AND §7. DO NOT RUN §4, §5 OR §6 FROM THIS
SHEET. ◄◄◄◄◄◄◄◄** They were written against the `02:40` binary, which `301`'s build replaces, and
they read counters that `301` proved were misreporting: the near counters shared one line with
knob-independent ones (`N1`), the rebuild census sampled one frame in n (`H2`), and `list=` did
not balance the sum (`H3`). `RUN-SHEET-301` carries the same three arms with the same intent,
re-gated: an automatic binary check, an `H5` overwrite guard, `GETV_ARM` set, and reads for the
lines that replaced the ones below. **This section is kept because it is the record of what was
planned on 2026-09-03, not because it is runnable.**


Same block as `RUN-SHEET-299` §2 (E1) with **no knob change at all** — the split is unconditional
in the SUMMARY now. **Press F9 six times in the first five seconds, while the level is still
opening**, which is where `299` §8.2 found the dead eye.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
Get-ChildItem .\dlgrab_*.txt,.\dlgrab_*.bmp -ErrorAction SilentlyContinue | Measure-Object | Select-Object -ExpandProperty Count
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
$env:GETV_STEREO_OFFSET         = "0"
$env:GETV_STEREO_MODE           = "1"
$env:GETV_STEREO_VIEWRESTORE    = "1"
$env:GETV_STEREO_PAIRGUARD      = "0"
$env:GETV_STEREO_REBUILD        = "1"
$env:GETV_STEREO_REBUILD_REPORT = "1"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_300_S1_skipsplit.log 2>&1
Select-String -Path run_300_S1_skipsplit.log -Pattern 'GETV_FPS=panel'
Select-String -Path run_300_S1_skipsplit.log -Pattern 'ARM 3 per-eye|pools scaled'
Select-String -Path run_300_S1_skipsplit.log -Pattern 'dlgrab_|getv\]\[shot\]'
Select-String -Path run_300_S1_skipsplit.log -Pattern 'skipped=[1-9]' | Select-Object -First 10
Select-String -Path run_300_S1_skipsplit.log -Pattern 'EXCEPTION|game_exit requested'
New-Item -ItemType Directory -Force -Path .\grabs_300_S1 | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_300_S1 -Force -ErrorAction SilentlyContinue
Get-ChildItem .\grabs_300_S1 | Select-Object Name, Length, LastWriteTime
```

**GATE §6 — read the split on a frame that is ALSO a grab, so the census and the picture agree:**

| what `skipped=N (flag=A type=B)` reads on a dead-eye frame | reading |
|---|---|
| **`type=1 flag=0`** | The deliberate exclusion of `chrprop.c` item 4 — explosion, smoke or the viewer — **is too wide**, and the dead eye is a design gap, not a bug. GROUP B2 |
| **`flag=1 type=0`** | **The prop lost `ENABLED\|ONSCREEN` mid-frame, and that site's own comment says THIS CANNOT HAPPEN TODAY.** The comment is falsified and a per-eye admission has appeared from somewhere. **This is the more serious outcome** |
| both zero on every dead frame | The dead eye is not a skip at all and `299` §8.3's pairing was a coincidence of sampling. **Re-open it** |

---

## §7 — THE COMMITS. **THREE REPOS, IN THIS ORDER, AND THE FIRST HAS THE TRAP.**

**►►►►►►►► THESE ARE POWERSHELL BLOCKS WITH ABSOLUTE WINDOWS PATHS. `299` SHIPPED THEM IN
GIT-BASH FORM AND IT COST A CYCLE. ◄◄◄◄◄◄◄◄** In PowerShell `/f/Projects/...` is a RELATIVE path
and resolves to `F:\f\Projects\...`, so `Set-Location` fails — **and every following line then
runs in whatever directory the prompt was already in, against whatever repo encloses it.**
`[MEASURED]` 2026-09-03: the decomp block ran against `goldeneye-native`, `git add` reported
`pathspec did not match`, and the closing `git log` printed **goldeneye-native's** HEAD, which
reads exactly like the decomp's commit having silently not happened. Nothing was staged and
nothing was committed, but **the failure was only obvious because the message file was missing
too.** Hence gate 0 below.

**►► GATE 0, EVERY BLOCK: `git rev-parse --show-toplevel` PRINTS THE REPO BEFORE ANYTHING IS
STAGED.** A block that stages into the wrong repo is `287`'s diagonal-not-2x2 shape one level up:
each command succeeds and the set answers a different question than the one asked.

**Every commit is the owner's** (`00-STATE` §1.1). **`COMMIT-NOW.cmd` WILL NOT DO STEP 1** —
`vendor/` is gitignored by `goldeneye-native` and invisible to all three of its passes (`276`).
**No attribution trailers** (rule `18`).

### 7.1 — `vendor/ge-decomp`. **STAGE BY EXPLICIT PATH LIST, NEVER `git add -A`.**

2,106 CRLF-dirty files sit in that worktree; `7a4e7bfd` is what happens when they get swept in.

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\vendor\ge-decomp
git rev-parse --show-toplevel
git add src/game/chrprop.c
git --no-optional-locks diff --cached --stat
git commit -F F:\Projects\GEVR\GoldenEyeVR\COMMIT-MESSAGE-2026-09-03-decomp.txt
git --no-optional-locks log --oneline -1
```

**GATE 7.1 — two things, in this order:**

1. **`rev-parse` prints a path ending `vendor/ge-decomp`.** Anything else, stop.
2. **`diff --cached --stat` reads `1 file changed, 26 insertions(+), 3 deletions(-)`.** `-w` gives
   the same figures, so it is real code and not the CRLF ghost. Hundreds means `git add` took more
   than one file — `git reset` and start again.

### 7.2 — `goldeneye-native`. **THE PATCH IS PART OF THE COMMIT.**

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
git rev-parse --show-toplevel
git add getv/port/fast3d/ge_depthclamp.c getv/port/fast3d/ge_depthclamp.h
git add getv/tools/depthclamp_harness.c getv/tools/depthclamp_harness.sh
git add getv/port/src/ge_config.c
git add getv/patches/thirdparty/0001-getv-port-layer.patch
git --no-optional-locks diff --cached --stat
git commit -F F:\Projects\GEVR\GoldenEyeVR\COMMIT-MESSAGE-2026-09-03-native.txt
git --no-optional-locks log --oneline -1
```

**GATE 7.2 — SIX PATHS, AND THE PATCH IS THE ONE THAT MATTERS.** If
`getv/patches/thirdparty/0001-getv-port-layer.patch` is **not** in `--cached --stat`, §2's regen
did not run and `gfx_pc.c`'s and `gfx_opengl.c`'s four lines of hook are in no commit — the exact
shape of `268`. **Do not commit without it.** `[MEASURED]` before this sheet was written, the regen
had run and that patch stood at **130 insertions / 110 deletions**.

### 7.3 — `GoldenEyeVR`. The documents.

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR
git rev-parse --show-toplevel
git add repo/docs/00-STATE.md repo/docs/00-STATE.md.bak-298
git add repo/docs/299-ARM-3-IS-GREEN-ON-ONE-FRAME-AND-DEAD-ON-ANOTHER.md
git add repo/docs/RUN-SHEET-299.md repo/docs/RUN-SHEET-300.md
git add repo/docs/PRIORITY-BOARD-299.md repo/docs/NEXT-SESSION-PROMPT-300.md
git add COMMIT-MESSAGE-2026-09-03.txt COMMIT-MESSAGE-2026-09-03-native.txt COMMIT-MESSAGE-2026-09-03-decomp.txt
git --no-optional-locks diff --cached --stat
git commit -F F:\Projects\GEVR\GoldenEyeVR\COMMIT-MESSAGE-2026-09-03.txt
git --no-optional-locks log --oneline -1
```

**GATE 7.3: SEVEN document paths plus three message files, and nothing from `goldeneye-native/`.**
`build_300_depthclamp.log` is gitignored (`*.log`) and stays out, as every build log has.

### 7.4 — THE THREE-REPO CHECK, AFTER ALL THREE

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR;                                  git --no-optional-locks log --oneline -1
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native;                 git --no-optional-locks log --oneline -1
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\vendor\ge-decomp; git --no-optional-locks log --oneline -1
```

**and the last line needs GIT BASH, because it runs a shell script:**

```bash
cd /f/Projects/GEVR/GoldenEyeVR/goldeneye-native && tools/fetch-thirdparty.sh verify
```

**GATE 7.4: three NEW SHAs — none of them `3de0db0`, `e380916` or `1f0f7aae` — and `verify` still
reading `15/15`.** A regen before the commit and a `verify` after it are two different facts and
both are wanted.

### 7.5 — **LANDED. `[MEASURED]` 2026-09-03.**

| repo | SHA | contents, from `git show --stat --name-status` |
|---|---|---|
| `vendor/ge-decomp` | **`77f67e26`** | `M src/game/chrprop.c` — **one file, no CRLF sweep** |
| `goldeneye-native` | **`6f24ddc`** | `M getv/patches/thirdparty/0001-getv-port-layer.patch` · `A ge_depthclamp.c` · `A ge_depthclamp.h` · `M getv/port/src/ge_config.c` · `A depthclamp_harness.c` · `A depthclamp_harness.sh` |
| `GoldenEyeVR` | **`fe93821`** | three message files + seven doc paths, **nothing from `goldeneye-native/`** |

**GATE 7.2's ONE THAT MATTERS IS MET: the patch is in the native commit**, so `gfx_pc.c`'s and
`gfx_opengl.c`'s four lines of hook are committed and a fresh clone regenerates them. **`268`'s
shape did not recur.** `tools/fetch-thirdparty.sh verify` reads **`15/15 files match pristine +
patch`** after the commit, which with the regen before it is the two separate facts §7.4 wanted.

**THE BUILD IS COMMITTED AND THE FIX IS STILL UNTESTED.** §4's D1/D2 has not run.
