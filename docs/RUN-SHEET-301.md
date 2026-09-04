# RUN-SHEET-301 — THE INSTRUMENT BUILD

**Written OFFLINE 2026-09-03. NOTHING BUILT.** Baseline: `goldeneye.exe` **18,062,771 bytes at
02:40** (`299` §9.6). This sheet replaces that binary.

**READ `301` §7 BEFORE STARTING.** `RUN-SHEET-300` §4/§5/§6 have not run and were written
against the `02:40` binary; this build replaces it. That is a decision, and it is yours.

**THE ORDER IS LOAD-BEARING: §1 gates → §2 REGEN → §3 build → §4 the smoke read.**
**§2 BEFORE §3 IS NOT A STYLE PREFERENCE.** `gfx_pc.c` is gitignored, so a build that precedes
the regen builds code that is in no commit (`268` lost `GETV_DLGRAB` for two days exactly this
way). The regen has already been run and verified `15/15` offline this session — §2 re-runs it
on the main PC because that is where the build happens.

---

## §1 — THE OFFLINE GATES, ON THE MAIN PC. **BEFORE ANYTHING ELSE.**

All nine were worn on the bridge under `gcc 11.4.0`. The main PC has MSYS2/mingw and the
harnesses invoke bare `gcc` — strong evidence, **different event** (`RUN-SHEET-295` §11).

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
bash getv/tools/depthclamp_harness.sh
bash getv/tools/depthclamp_glpath.sh
bash getv/tools/ge_rebuild_window_harness.sh
bash getv/tools/port_syntax_gate.sh
bash getv/tools/stereo_harness.sh
bash getv/tools/cullwhy_harness.sh
bash getv/tools/posespine_harness.sh
gcc -std=c99 -Wall -Wextra -Werror -o ge_arm_tag_harness.exe getv/tools/ge_arm_tag_harness.c
.\ge_arm_tag_harness.exe
py getv\tools\stereo_disparity.py --selftest
py getv\tools\knob_banner_survey.py --selftest
```

**GATE §1 — TEN things, and the four new ones are the point:**

1. `depthclamp_harness: 17 checks, 0 failed` / `VERDICT PASS`.
2. **`depthclamp_glpath: VERDICT PASS`. NEW.** The GL path of `ge_depthclamp.c` compiles offline
   for the first time. **A pass is not a verification** — see `glstub/README.md`.
3. **`ge_rebuild_window_harness: 18 checks, 0 failed`. NEW.** CASE 1 must print
   **`six green spot checks, 363 failing frames`** — that line is `H2` stated as a number, and if
   it ever reads differently the accumulator has changed meaning.
4. **`port_syntax_gate: 51 ok, 0 failed, 6 not covered` / `VERDICT PASS`. NEW, and it is `H10`.**
   Until `301` the port layer compiled **nowhere but this PC** — `stereo_harness.sh`'s real-header
   gate covers DECOMP files only, so an edit to `port_render.c` or the gitignored `gfx_pc.c` was
   checked by nothing until the build. **The six skipped files are named with reasons in the
   script and are still build-only.** If a file that used to pass now FAILS, that is the gate
   working; do not add to the exclude list to silence it.
5. `63 passed, 0 failed` from `stereo_harness.sh`, whose nine-file real-header syntax gate covers
   the edited `chrprop.c`. **This is the gate most likely to catch a mistake in this session's
   `chrprop.c` work.**
6. **The three-arm pairing falsifier still reads `pairmono 0 / pairoff 2 / pairon 0`.** The middle
   arm must still fire. A harness whose falsifier has gone quiet is not a harness.
7. `cullwhy_harness` and 8. `posespine_harness` both `VERDICT PASS` — untouched this session, so
   they are the regression check.
9. **`ge_arm_tag_harness: 11 checks, 0 failed`. NEW.** Includes `../../etc/passwd` and a pasted
   `F:\Projects\...`; both must come back with no `/`, `\`, `:` or `.` surviving.
10. `stereo_disparity.py --selftest` — **three cases now, and B must read `peg detector FIRED`.**
   A silent B is `H1` reopening.

---

## §2 — **THE REGEN. MAIN PC, GIT BASH. THIS IS THE STEP THAT GETS SKIPPED.**

```bash
cd /f/Projects/GEVR/GoldenEyeVR/goldeneye-native
tools/fetch-thirdparty.sh regen
```

**GATE §2:** `fetch-thirdparty: 15/15 files match pristine + patch`.

**The patch is ALREADY at 459,478 bytes (was 457,069) and already verified 15/15 offline.** So
this run should report a size change of **zero or near-zero**. **A large shrink here means the
main PC's working tree does not have this session's `gfx_pc.c` edits** — stop and reconcile
rather than committing the shrink; the script will refuse a shrink past half on its own.

---

## §3 — THE BUILD

**The block is `RUN-SHEET-300` §3's, quoted, with only the log name changed.** `build_windows.ps1`
lives in `getv\`, not the repository root, and the binary lands in `getv\build-windows\` — a
`Set-Location` to the wrong one of those fails silently into whatever directory the prompt was
already in (`00-STATE` §6's first trap).

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv
.\build_windows.ps1 *> F:\Projects\GEVR\GoldenEyeVR\build_301_instruments.log 2>&1
Select-String -Path F:\Projects\GEVR\GoldenEyeVR\build_301_instruments.log -Pattern 'first failure|conflicting types|error|Build succeeded|goldeneye.exe' | Select-Object -First 20
Select-String -Path F:\Projects\GEVR\GoldenEyeVR\build_301_instruments.log -Pattern 'port layer:|failed'
Get-Item F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
Copy-Item F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows\goldeneye.map F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows\goldeneye_301.map -Force
```

**GATE §3:** `windows port layer: 59 built, 0 failed`, 0 failed in every group, and
**`goldeneye.exe` with a `LastWriteTime` later than `02:40` and a `Length` different from
`18,062,771`.** Do not memorise either number — §3c below records them for you.

**►► THIS BUILD IS WHERE `port_render.c` AND `gfx_pc.c` ARE FINALLY CHECKED.** `301` §1's
`port_syntax_gate.sh` now type-checks both offline (`H10`), which is new — but the stub headers
are not the real SDL/GL, so **this compile is still the authority.** A failure here in either
file is this session's most likely mistake; read the first error rather than the last.

Then confirm the new strings are actually in the binary. **`Select-String -Encoding Byte` is NOT
used here and must not be: it does not exist in PowerShell 7, it throws *"'Byte' is not a
supported encoding name"*, and with `-ErrorAction SilentlyContinue` anywhere near it every probe
prints MISSING on a binary that contains all of them** (`00-STATE` §6). This is
`RUN-SHEET-283` §1's block, with `Latin1` rather than `ASCII` because it is the only decoder that
maps all 256 byte values one-to-one.

```powershell
$exe = 'F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows\goldeneye.exe'
$txt = [System.Text.Encoding]::Latin1.GetString([System.IO.File]::ReadAllBytes($exe))
foreach ($k in '[getv][run] ARM=','[getv][near] SCENE','[getv][arm] GETV_ARM=',
               'GETV_STEREO_REBUILD_REPORT=','ZERO-REBUILD FRAMES','GETV_NEARCLAMP=') {
    if ($txt.Contains($k)) { "$k  IS IN THE BINARY" } else { "$k  IS **NOT** IN THE BINARY -- STOP" }
}
```

**GATE §3b: all six must say IS IN.** A string in a binary is not a run (`279` §7) — but a string
**missing** means that file was not rebuilt, and that is worth one command.

### 3c — **RECORD THE BINARY'S IDENTITY. EVERY ARM BELOW GATES ON THIS FILE.**

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
"$((Get-FileHash .\goldeneye.exe -Algorithm SHA256).Hash) $((Get-Item .\goldeneye.exe).Length)" |
  Set-Content .\EXPECTED-EXE-301.txt
Get-Content .\EXPECTED-EXE-301.txt
```

**Why this replaces the old `18,062,771 bytes / 02:40` gate.** `RUN-SHEET-300`'s arms opened with
an informational `Get-Item` and a constant in the prose above them — **so the check was the
reader's memory, and the constant went stale the moment anything was rebuilt.** `133`'s rule
("every block's `Get-Item .\goldeneye.exe` line stays the first gate") is now enforced by the
machine: each arm recomputes the hash and **throws** on a mismatch. **It needs no hand-edited
number and it stays correct across every future build — re-run this one block after each build
and the arms below need no editing at all.**

**GATE §3c:** the file exists and holds one line — a 64-character hash and a byte count.

---

## §4 — THE SMOKE READ. ONE SHORT RUN, NO ANALYSIS.

**This is not an arm and no verdict comes out of it.** It confirms the five new lines say anything
at all, before any real measurement is taken through them. **A level is loaded on purpose** — at
the menu the rebuild census has nothing to count and a zero there would mean nothing.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
if (-not (Test-Path .\EXPECTED-EXE-301.txt)) { throw "EXPECTED-EXE-301.txt is missing -- run RUN-SHEET-301 section 3c after the build, before any arm." }
$want = (Get-Content .\EXPECTED-EXE-301.txt).Trim()
$got  = "$((Get-FileHash .\goldeneye.exe -Algorithm SHA256).Hash) $((Get-Item .\goldeneye.exe).Length)"
if ($want -ne $got) { throw "BINARY MISMATCH -- this is NOT the 301 build. want [$want] got [$got]" }
if (Test-Path .\run_301_S1_smoke.log) { throw "run_301_S1_smoke.log EXISTS -- rename it or pick a new name. A re-run would destroy the arm's provenance (H5)." }
$env:GETV_ARM                   = "S1"
$env:GETV_SLOTFREE              = "1"
$env:GETV_FPS                   = "panel"
$env:GETV_WIDESCREEN            = "0"
$env:GETV_WINDOW                = "2560x1369"
$env:GETV_STAGE                 = "29"
$env:GETV_DIFFICULTY            = "0"
$env:GETV_STEREO                = "1"
$env:GETV_STEREO_REBUILD        = "1"
$env:GETV_STEREO_REBUILD_REPORT = "600"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_301_S1_smoke.log 2>&1
Select-String -Path run_301_S1_smoke.log -Pattern 'getv\]\[run\] ARM='
Select-String -Path run_301_S1_smoke.log -Pattern 'getv\]\[arm\] GETV_ARM='
Select-String -Path run_301_S1_smoke.log -Pattern 'GETV_STEREO_REBUILD_REPORT='
Select-String -Path run_301_S1_smoke.log -Pattern 'GETV_NEARCLAMP='
Select-String -Path run_301_S1_smoke.log -Pattern 'GETV_FILTERING=.*filtering='
Select-String -Path run_301_S1_smoke.log -Pattern 'getv\]\[near\] SCENE' | Select-Object -Last 1
Select-String -Path run_301_S1_smoke.log -Pattern 'rebuild\] WINDOW'      | Select-Object -Last 2
Select-String -Path run_301_S1_smoke.log -Pattern 'EXCEPTION|game_exit requested'
```

**Walk a few steps, look at a wall, and quit.** Thirty seconds is plenty.

**GATE §4 — six reads, and the sixth is the one that has never existed:**

1. **`[getv][run] ARM=S1 START=<utc>`.** `H5` is live. **If it reads `ARM=(UNSET)` the environment
   did not reach the process — stop.** That is the `GETV_FILTERING` failure shape exactly, and
   nothing measured after it would mean anything.
2. `[getv][arm] GETV_ARM=S1`, and any grab written is named `dlgrab_S1_<frame>.*` — **not**
   `dlgrab_<frame>.*`. That is `N2`.
3. `[getv][stereo][rebuild] GETV_STEREO_REBUILD_REPORT=600`. The knob echoes its own name now.
4. `[getv][nearclamp] GETV_NEARCLAMP=1`. `H4`'s named offender, which had no banner at all.
5. `[getv][config] ... GETV_FILTERING=(unset) -> filtering=<n>`. **Env value and effective value,
   side by side.** If they ever disagree, the config file won.
6. **►► `[getv][stereo][rebuild] WINDOW over the last 600 frames ... ZERO-REBUILD FRAMES <a> of
   600 (cumulative <b> of <n>)`.** This line has never existed. **`<b>` is the quantity `298` §1.1
   could not see** — six samples read zero while the run had 372.

**NOT WORTH DOING IF:** you are tempted to score anything on `<b>` here. This is a title-screen-
to-corridor stroll, not a controlled arm; **§7 is where that number is pointed at something.**
The only failure that matters at this stage is a line that does not appear at all.

---

## §5 — D1 / D2. **THE A/B THAT SAYS WHETHER THE DEPTH-CLAMP FIX WORKS.**

**Supersedes `RUN-SHEET-300` §4, which was written against the `02:40` binary.** Same alley, same
corner as `299` N1-N3 — pressed against the brick wall, alley ahead, the red wall and the jeep on
the right (`grabs_298_D/dlgrab_7930.bmp` is that view). **Stand still, F9 three times, quit.** One
behaviour change between the arms (`48`).

**THREE THINGS ARE NEW SINCE `300` WROTE THIS ARM, AND ALL THREE ARE GATES:** the binary check is
now automatic (`§3` wrote `EXPECTED-EXE-301.txt`), the log cannot be silently overwritten (`H5`),
and the near counters are split into SCENE and CLAMP ACTION on a new `[getv][near]` line (`N1`) —
**which is the whole reason `298` §4.4 misread this arm.**

### 5.1 — D1. **The fix ON (shipping default).**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
if (-not (Test-Path .\EXPECTED-EXE-301.txt)) { throw "EXPECTED-EXE-301.txt is missing -- run RUN-SHEET-301 section 3c after the build, before any arm." }
$want = (Get-Content .\EXPECTED-EXE-301.txt).Trim()
$got  = "$((Get-FileHash .\goldeneye.exe -Algorithm SHA256).Hash) $((Get-Item .\goldeneye.exe).Length)"
if ($want -ne $got) { throw "BINARY MISMATCH -- this is NOT the 301 build. want [$want] got [$got]" }
if (Test-Path .\run_301_D1_depthclamp_on.log) { throw "run_301_D1_depthclamp_on.log EXISTS -- rename it or pick a new name. A re-run would destroy the arm's provenance (H5)." }
Get-ChildItem .\dlgrab_*.txt,.\dlgrab_*.bmp -ErrorAction SilentlyContinue | Measure-Object | Select-Object -ExpandProperty Count
$env:GETV_ARM         = "D1"
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
.\goldeneye.exe *> run_301_D1_depthclamp_on.log 2>&1
Select-String -Path run_301_D1_depthclamp_on.log -Pattern 'getv\]\[run\] ARM='
Select-String -Path run_301_D1_depthclamp_on.log -Pattern 'GETV_FPS=panel'
Select-String -Path run_301_D1_depthclamp_on.log -Pattern 'depthclamp\]'
Select-String -Path run_301_D1_depthclamp_on.log -Pattern 'GETV_NEARCLAMP='
Select-String -Path run_301_D1_depthclamp_on.log -Pattern 'GETV_SLOTFREE resolved|GETV_STAGE override'
Select-String -Path run_301_D1_depthclamp_on.log -Pattern 'roomscissor\]|proproomtest\]|getv\]\[stereo\]'
Select-String -Path run_301_D1_depthclamp_on.log -Pattern 'dlgrab_|getv\]\[shot\]'
Select-String -Path run_301_D1_depthclamp_on.log -Pattern 'EXCEPTION|game_exit requested'
Select-String -Path run_301_D1_depthclamp_on.log -Pattern '\[getv\]\[far\]'  | Select-Object -Last 1
Select-String -Path run_301_D1_depthclamp_on.log -Pattern '\[getv\]\[near\]' | Select-Object -Last 1
New-Item -ItemType Directory -Force -Path .\grabs_301_D1 | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_301_D1 -Force -ErrorAction SilentlyContinue
Get-ChildItem .\grabs_301_D1 | Select-Object Name, Length, LastWriteTime
```

### 5.2 — D2. **The fix OFF. This must reproduce `299` N1 exactly.**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
if (-not (Test-Path .\EXPECTED-EXE-301.txt)) { throw "EXPECTED-EXE-301.txt is missing -- run RUN-SHEET-301 section 3c after the build, before any arm." }
$want = (Get-Content .\EXPECTED-EXE-301.txt).Trim()
$got  = "$((Get-FileHash .\goldeneye.exe -Algorithm SHA256).Hash) $((Get-Item .\goldeneye.exe).Length)"
if ($want -ne $got) { throw "BINARY MISMATCH -- this is NOT the 301 build. want [$want] got [$got]" }
if (Test-Path .\run_301_D2_depthclamp_off.log) { throw "run_301_D2_depthclamp_off.log EXISTS -- rename it or pick a new name. A re-run would destroy the arm's provenance (H5)." }
Get-ChildItem .\dlgrab_*.txt,.\dlgrab_*.bmp -ErrorAction SilentlyContinue | Measure-Object | Select-Object -ExpandProperty Count
$env:GETV_ARM         = "D2"
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
.\goldeneye.exe *> run_301_D2_depthclamp_off.log 2>&1
Select-String -Path run_301_D2_depthclamp_off.log -Pattern 'getv\]\[run\] ARM='
Select-String -Path run_301_D2_depthclamp_off.log -Pattern 'GETV_FPS=panel'
Select-String -Path run_301_D2_depthclamp_off.log -Pattern 'depthclamp\]'
Select-String -Path run_301_D2_depthclamp_off.log -Pattern 'GETV_NEARCLAMP='
Select-String -Path run_301_D2_depthclamp_off.log -Pattern 'GETV_SLOTFREE resolved|GETV_STAGE override'
Select-String -Path run_301_D2_depthclamp_off.log -Pattern 'roomscissor\]|proproomtest\]|getv\]\[stereo\]'
Select-String -Path run_301_D2_depthclamp_off.log -Pattern 'dlgrab_|getv\]\[shot\]'
Select-String -Path run_301_D2_depthclamp_off.log -Pattern 'EXCEPTION|game_exit requested'
Select-String -Path run_301_D2_depthclamp_off.log -Pattern '\[getv\]\[far\]'  | Select-Object -Last 1
Select-String -Path run_301_D2_depthclamp_off.log -Pattern '\[getv\]\[near\]' | Select-Object -Last 1
New-Item -ItemType Directory -Force -Path .\grabs_301_D2 | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_301_D2 -Force -ErrorAction SilentlyContinue
Get-ChildItem .\grabs_301_D2 | Select-Object Name, Length, LastWriteTime
```

### 5.3 — GATES, AND EVERY OUTCOME MEANS SOMETHING DIFFERENT

**GATE 0 — PROVENANCE, AND IT IS NEW.** Both logs must open with `[getv][run] ARM=D1` and
`ARM=D2` respectively, and the grabs must be named `dlgrab_D1_*` / `dlgrab_D2_*`. **If either
reads `ARM=(UNSET)` the environment did not reach the process — stop, because that is the
`GETV_FILTERING` failure shape and everything downstream would be measuring the wrong thing.**

**BANNER GATE — a knob whose value is not echoed is a knob you have not set (`299` §5.1):**

| arm | required `[getv][depthclamp]` line | required `[getv][nearclamp]` line |
|---|---|---|
| D1 | **`GL_DEPTH_CLAMP ON (core 3.2+, GL_VERSION=4.6.0 NVIDIA ...)`** | `GETV_NEARCLAMP=1` |
| D2 | **`GETV_DEPTHCLAMP=0 -- GL depth clamping NOT enabled`** | `GETV_NEARCLAMP=1` |

`GETV_NEARCLAMP` had **no banner at all** until `301`; `299` had to infer it from the census.
**Both arms must read `=1`** — if either reads `0` the near clamp is disabled and D2 is not the
old path, so the A/B is void before the census is even read.

**CENSUS GATE — AND THE LINE IT IS READ FROM HAS CHANGED. READ `[getv][near]`, NOT `[getv][far]`.**

The near counters used to share `[getv][far]`'s line, mixing counters that answer to the knob
with counters that do not. They now print as:

```
[getv][near] SCENE (knob-independent, ...): all_near(hw-DRAWS)=N straddle=N || CLAMP ACTION (knob-dependent, ...): clamped=N
```

| arm | SCENE `straddle` | CLAMP ACTION `clamped` | far `clamped` |
|---|---|---|---|
| **D1** | **thousands** | **0** | **0** |
| **D2** | thousands | `straddle + all_near` | non-zero |

**D1's double zero is the receipt of the banner, NOT a masked zero** — `straddle` in the thousands
is what makes it a result (`289` R2's rule). **D2's must match `299` N1's shape exactly**
(`clamped = straddle + all_near`); if it does not, `GETV_DEPTHCLAMP=0` is not restoring the old
path and the A/B is void.

**►►►► GATE 3 IS ENTIRELY NEW AND ONLY THE `N1` SPLIT MAKES IT POSSIBLE. COMPARE THE SCENE PAIR
ACROSS THE TWO ARMS.** `all_near` and `straddle` are incremented outside the knob's branch, so
**they describe where you were standing, not what the clamp did.** If D1 and D2 disagree on them
by more than a little, **you did not stand in the same place and the A/B is void** — whatever the
`clamped` numbers say. **This is the check whose absence produced `298` §4.4's retracted reading
of `all_near 50 -> 548` as "the clamp's price": it was the player facing a nearer wall, and the
same number would have moved with the clamp compiled out.**

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

## §6 — THE FILTERING ARM. **IT HAS NEVER TAKEN, AND IT VOIDED TWO OWNER CYCLES.**

**Supersedes `RUN-SHEET-300` §5.** `299` §9.2 fixed `key_filtering()`'s missing `over` guard so
`GETV_FILTERING` obeys CLI > environment > file > default. **The gate is the banner, and only the
banner** (`298` §5, `00-STATE` §6) — **and the banner itself changed in `301`.**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
if (-not (Test-Path .\EXPECTED-EXE-301.txt)) { throw "EXPECTED-EXE-301.txt is missing -- run RUN-SHEET-301 section 3c after the build, before any arm." }
$want = (Get-Content .\EXPECTED-EXE-301.txt).Trim()
$got  = "$((Get-FileHash .\goldeneye.exe -Algorithm SHA256).Hash) $((Get-Item .\goldeneye.exe).Length)"
if ($want -ne $got) { throw "BINARY MISMATCH -- this is NOT the 301 build. want [$want] got [$got]" }
if (Test-Path .\run_301_F1_filtering_point.log) { throw "run_301_F1_filtering_point.log EXISTS -- rename it or pick a new name. A re-run would destroy the arm's provenance (H5)." }
$env:GETV_ARM         = "F1"
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
.\goldeneye.exe *> run_301_F1_filtering_point.log 2>&1
Select-String -Path run_301_F1_filtering_point.log -Pattern 'getv\]\[run\] ARM='
Select-String -Path run_301_F1_filtering_point.log -Pattern 'getv\]\[config\]'
Select-String -Path run_301_F1_filtering_point.log -Pattern 'GETV_FPS=panel|EXCEPTION|game_exit requested'
```

**GATE §6 — the `[getv][config]` line now prints BOTH halves, and that is the point:**

```
GETV_FILTERING=0 -> filtering=0
```

**The left side is what the environment said. The right side is what took effect.** It read
`filtering=2` in both `298` arms with `GETV_FILTERING=0` set — and **nobody could grep for it,
because the log never said `GETV_FILTERING` at all.** That is `H4` in one line, and it is why the
full knob name is now printed.

- **`GETV_FILTERING=0 -> filtering=0`** — the fix took. Proceed.
- **`GETV_FILTERING=0 -> filtering=2`** — **the config file won.** The precedence fix did not
  take; go back to `ge_config.c:413`, **not** to the picture.
- **`GETV_FILTERING=(unset) -> ...`** — the environment did not reach the process. Not a
  filtering result at all.

**The question it was asked for is still open:** is the near-wall blur magnification of a
low-resolution texture, or a wrong texture size? Walk to the railing and the brick.

---

## §7 — THE SKIP SPLIT. **ONE RUN, AND IT ANSWERS `299` §8.3's `[UNDETERMINED]`.**

**Supersedes `RUN-SHEET-300` §6, and it now carries the `H2` window census as well.**
**Press F9 six times in the first five seconds, while the level is still opening** — that is where
`299` §8.2 found the dead eye.

`GETV_STEREO_REBUILD_REPORT=1` is kept, but **for a different reason than `300` gave.** It is no
longer needed to avoid missing frames — `H2`'s window accumulators cover every frame at any
cadence. It is kept so the SUMMARY line lands on the *same* frames as the grabs, which is what
makes the split readable against a picture.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
if (-not (Test-Path .\EXPECTED-EXE-301.txt)) { throw "EXPECTED-EXE-301.txt is missing -- run RUN-SHEET-301 section 3c after the build, before any arm." }
$want = (Get-Content .\EXPECTED-EXE-301.txt).Trim()
$got  = "$((Get-FileHash .\goldeneye.exe -Algorithm SHA256).Hash) $((Get-Item .\goldeneye.exe).Length)"
if ($want -ne $got) { throw "BINARY MISMATCH -- this is NOT the 301 build. want [$want] got [$got]" }
if (Test-Path .\run_301_S2_skipsplit.log) { throw "run_301_S2_skipsplit.log EXISTS -- rename it or pick a new name. A re-run would destroy the arm's provenance (H5)." }
Get-ChildItem .\dlgrab_*.txt,.\dlgrab_*.bmp -ErrorAction SilentlyContinue | Measure-Object | Select-Object -ExpandProperty Count
$env:GETV_ARM                   = "S2"
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
.\goldeneye.exe *> run_301_S2_skipsplit.log 2>&1
Select-String -Path run_301_S2_skipsplit.log -Pattern 'getv\]\[run\] ARM='
Select-String -Path run_301_S2_skipsplit.log -Pattern 'GETV_STEREO_REBUILD_REPORT='
Select-String -Path run_301_S2_skipsplit.log -Pattern 'GETV_FPS=panel'
Select-String -Path run_301_S2_skipsplit.log -Pattern 'ARM 3 per-eye|pools scaled'
Select-String -Path run_301_S2_skipsplit.log -Pattern 'dlgrab_|getv\]\[shot\]'
Select-String -Path run_301_S2_skipsplit.log -Pattern 'skipped=[1-9]' | Select-Object -First 10
Select-String -Path run_301_S2_skipsplit.log -Pattern 'rebuild\] WINDOW' | Select-Object -Last 3
Select-String -Path run_301_S2_skipsplit.log -Pattern 'EXCEPTION|game_exit requested'
New-Item -ItemType Directory -Force -Path .\grabs_301_S2 | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_301_S2 -Force -ErrorAction SilentlyContinue
Get-ChildItem .\grabs_301_S2 | Select-Object Name, Length, LastWriteTime
```

**GATE §7a — READ THE `WINDOW` LINE FIRST. IT HAS NEVER EXISTED BEFORE AND IT SCORES ARM 3.**

```
[getv][stereo][rebuild] WINDOW over the last N frames ...: rebuilt(chr+obj) min=A max=B |
ZERO-REBUILD FRAMES C of N (cumulative D of M) | of those, pass-never-ran E (cumulative F) | ...
```

- **`ZERO-REBUILD FRAMES` cumulative `D` is the number `298` §1.1 could not see.** Six spot checks
  said zero; the run had 372. **`D` must be 0, or every one of them must be accounted for by
  `pass-never-ran`** (which is legitimate only on a `GETV_SIMDIV` run — and this arm sets
  `SIMDIV=1`, so **`pass-never-ran` should be 0 here and any `D > 0` is a real finding**).
- **`min=0` with `max` in the tens is the dead eye, stated as a number rather than inferred from
  a picture.** That is `299` §8.2 measured instead of sampled.

**GATE §7b — the split, on a frame that is ALSO a grab, so census and picture agree:**

| what `skipped=N (flag=A type=B)` reads on a dead-eye frame | reading |
|---|---|
| **`type=1 flag=0`** | The deliberate exclusion of `chrprop.c` item 4 — explosion, smoke or the viewer — **is too wide**, and the dead eye is a design gap, not a bug. GROUP B2 |
| **`flag=1 type=0`** | **The prop lost `ENABLED\|ONSCREEN` mid-frame, and that site's own comment says THIS CANNOT HAPPEN TODAY.** The comment is falsified and a per-eye admission has appeared from somewhere. **This is the more serious outcome** |
| both zero on every dead frame | The dead eye is not a skip at all and `299` §8.3's pairing was a coincidence of sampling. **Re-open it** |

**GATE §7c — `chr+obj+skipped` must equal `zsnap=`, NOT `list=`.** They are printed side by side
and labelled. `169` frames per run in `298` read `list=1 chr=1 skipped=1` and the sum was called
broken; it was only two numbers taken at two different moments (`H3`).

---

## §8 — THE COMMITS. **THREE REPOS, IN THIS ORDER, AND THE FIRST HAS THE TRAP.**

**►►►►►►►► THESE ARE POWERSHELL BLOCKS WITH ABSOLUTE WINDOWS PATHS. `299` SHIPPED THEM IN
GIT-BASH FORM AND IT COST A CYCLE. ◄◄◄◄◄◄◄◄** In PowerShell `/f/Projects/...` is RELATIVE and
resolves to `F:\f\Projects\...`, so `Set-Location` fails — **and every following line then runs in
whatever directory the prompt was already in, against whatever repo encloses it.**

**►► GATE 0, EVERY BLOCK: `git rev-parse --show-toplevel` PRINTS THE REPO BEFORE ANYTHING IS
STAGED.**

**Every commit is the owner's** (`00-STATE` §1.1). **`COMMIT-NOW.cmd` WILL NOT DO STEP 8.1** —
`vendor/` is gitignored by `goldeneye-native` and invisible to all three of its passes (`276`).
**No attribution trailers** (rule `18`). The message files are already written and carry a `b`
suffix because `2026-09-03` was used by `300` — **a re-used message filename is `H5` in a
different costume.**

### 8.1 — `vendor/ge-decomp`. **STAGE BY EXPLICIT PATH LIST, NEVER `git add -A`.**

2,106 CRLF-dirty files sit in that worktree; `7a4e7bfd` is what happens when they get swept in.

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\vendor\ge-decomp
git rev-parse --show-toplevel
git add src/game/chrprop.c src/game/ge_rebuild_window.h
git --no-optional-locks diff --cached --stat
git commit -F F:\Projects\GEVR\GoldenEyeVR\COMMIT-MESSAGE-2026-09-03b-decomp.txt
git --no-optional-locks log --oneline -1
```

**GATE 8.1 — three things, in this order:**

1. **`rev-parse` prints a path ending `vendor/ge-decomp`.** Anything else, stop.
2. **`diff --cached --stat` reads TWO files: `chrprop.c` at `90 insertions(+), 4 deletions(-)`,
   and `ge_rebuild_window.h` as a new file of `75` lines.** `-w` gives the same figures for
   `chrprop.c`, so it is real code and not the CRLF ghost. **Hundreds of files means `git add`
   took more than the two — `git reset` and start again.**
3. **`ge_rebuild_window.h` MUST be in the list.** `chrprop.c` `#include`s it and calls
   `geRebuildWindowFrame()`. **Committing one without the other leaves the tree unbuildable at
   that commit.**

### 8.2 — `goldeneye-native`. **THE PATCH IS PART OF THE COMMIT.**

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
git rev-parse --show-toplevel
git add getv/port/src/ge_config.c getv/port/src/port_render.c getv/port/src/ge_arm_tag.h
git add getv/tools/stereo_disparity.py getv/tools/knob_banner_survey.py
git add getv/tools/ge_rebuild_window_harness.c getv/tools/ge_rebuild_window_harness.sh
git add getv/tools/ge_arm_tag_harness.c getv/tools/port_syntax_gate.sh getv/tools/depthclamp_glpath.sh
git add getv/tools/glstub
git add tools/fetch-thirdparty.sh
git add getv/patches/thirdparty/0001-getv-port-layer.patch
git --no-optional-locks diff --cached --stat
git commit -F F:\Projects\GEVR\GoldenEyeVR\COMMIT-MESSAGE-2026-09-03b-native.txt
git --no-optional-locks log --oneline -1
```

**GATE 8.2 — SEVENTEEN files, and the patch is the one that matters.** `[MEASURED]` before this
sheet was written:

| file | changed |
|---|---|
| **`getv/patches/thirdparty/0001-getv-port-layer.patch`** | **143** |
| `getv/tools/stereo_disparity.py` | 83 |
| `getv/port/src/port_render.c` | 63 |
| `tools/fetch-thirdparty.sh` | 52 |
| `getv/port/src/ge_config.c` | 50 |
| 12 new files | `knob_banner_survey.py` 228, `port_syntax_gate.sh` 120, `ge_rebuild_window_harness.c` 99, `ge_arm_tag_harness.c` 67, `depthclamp_glpath.sh` 40, `ge_arm_tag.h` 37, `ge_rebuild_window_harness.sh` 36, and five under `glstub/` |

**►► IF `0001-getv-port-layer.patch` IS NOT IN `--cached --stat`, STOP.** `gfx_pc.c`'s
`[getv][near]` split and the `GETV_NEARCLAMP` banner are in **no commit** without it — that file
is gitignored and the patch is its only record. **This is the exact shape of `268`.**

**A note worth having in six months:** the patch shows `143` changed lines here, but `301` also
normalised the `---`/`+++` timestamps out of it. **From this commit onward a regen that changes
nothing produces a byte-identical patch** — so any later churn in that file is a real change and
worth reading rather than skipping.

### 8.3 — `GoldenEyeVR`. The documents.

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR
git rev-parse --show-toplevel
git add repo/docs/00-STATE.md repo/docs/PRIORITY-BOARD-299.md
git add repo/docs/RUN-SHEET-300.md repo/docs/RUN-SHEET-301.md
git add repo/docs/301-THE-INSTRUMENTS-WERE-THE-BUG.md
git add repo/docs/NEXT-SESSION-PROMPT-302.md
git add COMMIT-MESSAGE-2026-09-03b.txt COMMIT-MESSAGE-2026-09-03b-native.txt COMMIT-MESSAGE-2026-09-03b-decomp.txt
git --no-optional-locks diff --cached --stat
git commit -F F:\Projects\GEVR\GoldenEyeVR\COMMIT-MESSAGE-2026-09-03b.txt
git --no-optional-locks log --oneline -1
```

**GATE 8.3: SIX document paths plus three message files, and NOTHING from `goldeneye-native/`.**
`00-STATE.md` +32, `PRIORITY-BOARD-299.md` +58/−12, `RUN-SHEET-300.md` +33, three new files.
Build and run logs are gitignored (`*.log`) and stay out, as every one has.

### 8.4 — THE THREE-REPO CHECK, AFTER ALL THREE

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR;                                  git --no-optional-locks log --oneline -1
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native;                 git --no-optional-locks log --oneline -1
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\vendor\ge-decomp; git --no-optional-locks log --oneline -1
```

**and the last line needs GIT BASH, because it runs a shell script:**

```bash
cd /f/Projects/GEVR/GoldenEyeVR/goldeneye-native && tools/fetch-thirdparty.sh verify
```

**GATE 8.4: three DIFFERENT hashes, each newer than the `299` set (`fe93821` / `6f24ddc` /
`77f67e26`), and `15/15 files match pristine + patch`.** **Three identical hashes means every
block ran in the same repo** — the trap at the top of this section, and it prints as success.

### 8.5 — **WHEN TO RUN THIS SECTION**

**These commits are of OFFLINE work and do not depend on the build.** They can be run before §1
or after §7, and **there is an argument for before: it puts the patch in a commit while you are
still looking at it**, and `268` lost two days to a gitignored change that was never committed.
Committing first changes nothing in §1–§7.
