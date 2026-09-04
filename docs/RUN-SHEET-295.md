# RUN SHEET `295` — ARM 1 (THE VIEW-PAIR RESTORE) AND ARM 2 (`GETV_STEREO_PAIRGUARD`)

**EVERY BUILD, EVERY RUN AND EVERY COMMIT IS THE OWNER'S, ON THE MAIN PC** (rule `1`, `00-STATE`
§7a). The assistant wrote and validated this offline. **ARM 3 IS NOT IN THIS BUILD AND MUST NOT BE
— `295` §5: it would make `GETV_STEREO_PAIRGUARD` incapable of reporting anything but zero.**

**READ FIRST:** `295` §5 (why the order is what it is) and `00-STATE` §6 (the two knob traps
below). Every block sets **every** knob, because an omitted knob silently restores its default and
reads as a regression (`285`). Every block begins with the `Remove-Item` line, because
`$env:` persists across windows (`00-STATE` §6).

**`GETV_VSYNC=1`, `GETV_FPS=panel`, `GETV_SIMHZ=query` throughout** — these are runs the owner
LOOKS at. `285`: every previous sheet's `GETV_VSYNC=0` is wrong for that and it is the whole of the
smoothness complaint. Only the S5 cost arm flips them.

---

## §0 — PRECONDITIONS

- **`00-STATE` §6's stale `index.lock` in `vendor\ge-decomp\.git\` — if it is still there, it is a
  MAIN-PC delete and every `git add` in the decomp fails until it goes.** Block: `RUN-SHEET-276`
  STEP A0.
- **NOTHING UNDER `getv/port/**` WAS TOUCHED**, so **no regen is owed** and
  `tools/fetch-thirdparty.sh verify` should still be `15/15` for free. `[MEASURED]` this session
  with `git ls-files`: the two files added to the harness are tracked, not gitignored.
- **THE LIVE TREE IS `F:\Projects\GEVR`.** There is a stale second copy on the Desktop with an
  identical path from `GoldenEyeVR\` down (`00-STATE` §6). Launch by absolute path; check the exe's
  timestamp in every block.

---

## §1 — THE OFFLINE HARNESS. **RE-RUN IT BEFORE THE BUILD. `61/61`.**

```
bash F:/Projects/GEVR/GoldenEyeVR/goldeneye-native/getv/tools/stereo_harness.sh
```

**GATE H1: `61 passed, 0 failed` / `VERDICT PASS`.** Four things in it are the point:

1. **The real-header syntax gate, now SEVEN files** — `stereo.c`, `lv.c`, `fr.c`, `bondview2.c`,
   `dyn.c`, **`model.c`**, **`propobj.c`** — parsed with `build_windows.ps1`'s own flag list
   including `-include src/ge_port_decls.h`. **`0 errors` on every line.** This gate is why `292`'s
   link wall cannot happen twice (`00-STATE` §6).
2. `mono, stereo OFF    PASS  checks=3 mismatch=0` — **the boring frame** (`279` §7).
3. `stereo ON, VIEWRESTORE=0    PASS  checks=3 mismatch=2` — **the guard fires on purpose.**
4. `stereo ON, VIEWRESTORE=1    PASS  checks=3 mismatch=0` — ARM 1 removes the class.

**If arm 3 passes while arm 2 shows `mismatch=0`, STOP: the guard cannot fire and nothing else it
prints may be cited.**

And the measuring script's own falsifier, unchanged:
```
py F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\tools\stereo_disparity.py --selftest
```
**GATE: `injected shift -37, recovered -37 … PASS`.**

---

## §2 — BUILD, AND THE BINARY GATE. **NINE STRINGS.** MAIN PC.

Nothing was added to the build files. `stereo.c` was already globbed; the four other decomp files
were already in the build.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv
.\build_windows.ps1 *> F:\Projects\GEVR\GoldenEyeVR\build_295_pairguard.log 2>&1
Select-String -Path F:\Projects\GEVR\GoldenEyeVR\build_295_pairguard.log -Pattern 'first failure|conflicting types|error|Build succeeded|goldeneye.exe' | Select-Object -First 20
Get-Item F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
```

**►► READ THE FIRST FAILURE LINE, NOT THE LAST ERROR.** `00-STATE` §6: a conflicting declaration
is a hard error that survives `-w`, kills one object file, and then buries itself under a wall of
`undefined reference` that reads like *"the new file was never added to the build"*. The
`Select-Object -First 20` above is deliberate.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
$strings = '[getv][stereo] ON','ARM 1 view-pair restore','pairguard] ON','pairguard] SUMMARY','pairguard] MISMATCH','forced-read-after-lvlRender','PREDICTION frame=','1/D LAW','pools scaled x'
# Select-String -Encoding Byte was removed in PowerShell 7 (`295`): it throws
# "'Byte' is not a supported encoding name", and with -ErrorAction SilentlyContinue on the
# assignment every probe then reports MISSING on a binary that may well contain all nine.
# A NULL RESULT PRODUCED BY A CMDLET THAT NEVER RAN IS NOT A NULL RESULT. Read the bytes.
$bytes = [System.IO.File]::ReadAllBytes((Resolve-Path .\goldeneye.exe))
$blob  = [System.Text.Encoding]::Latin1.GetString($bytes)
foreach ($s in $strings) {
  "{0,-32} {1}" -f $s, ($(if ($blob.Contains($s)) {'FOUND'} else {'MISSING'}))
}
Remove-Variable blob, bytes
```
**GATE B1: all NINE read FOUND.** A knob that is not in the binary reads as a clean null result
(`133`, `268` §4).

Then, **Git Bash, main PC**: `tools/fetch-thirdparty.sh verify` → **`15/15 files match pristine +
patch`.** No regen is owed (§0). **Do NOT run `regen` — a regen before the arms are worn deletes
instruments** (`287` §5, `271` §7).

---

## §3 — ARM S1. **IDENTITY: STEREO OFF, GUARD ON. THE BORING FRAME.** Streets, stand still.

**This arm runs FIRST and it is the one that matters most** (`279` §7). With stereo off there is
one eye, it owns everything, and the guard must report **checks > 0 with mismatch 0**. A guard that
reports `mismatch=0` out of `checks=0` has proved nothing.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
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
$env:GETV_STEREO_PAIRGUARD      = "600"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_295_S1_guard_mono.log 2>&1
Select-String -Path run_295_S1_guard_mono.log -Pattern 'pairguard\]'
Select-String -Path run_295_S1_guard_mono.log -Pattern 'getv\]\[stereo\] ON|ARM 1 view-pair restore'
Select-String -Path run_295_S1_guard_mono.log -Pattern 'props interpolated|simulation held to|ours: x=|game_exit requested'
```

**GATE S1, stated before the run:**
- The **second** `Select-String` returns **NOTHING** — the stereo banners are stereo's, and stereo
  is off. The guard is deliberately independent of `GETV_STEREO`.
- Every `pairguard] SUMMARY` line reads **`stereo=0 eyes=1`**, **`checks=` a large number**, and
  **`mismatch=0`**. **`outside=` may be non-zero and that is CORRECT** — stale blocks from last
  frame and blocks allocated before the loop both land there (`295` §2).
- **Zero `pairguard] MISMATCH` lines.**
- `props interpolated 0`, zero `simulation held to`, `ours: x=367.333`, `game_exit requested`.

**IF `checks=0`: STOP.** The guard is not being reached and no later arm may be cited.
**IF `mismatch>0` HERE:** the watermark classification is wrong, not the engine. Read the first
`MISMATCH` line's `arena block eye=` — `-1` means the pair was never recorded.

---

## §4 — ARM S2a. **THE FALSIFIER. `VIEWRESTORE=0`, AND THE GUARD MUST FIRE.**

Two eyes, **zero separation** (the identity arm — the halves must still be identical), ARM 1
**disabled**, and one deliberate late read per frame. **This is the arm that answers `294` §3.6.**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
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
$env:GETV_STEREO_PROBE          = "0"
$env:GETV_STEREO_VIEWRESTORE    = "0"
$env:GETV_STEREO_PAIRGUARD      = "600"
$env:GETV_STEREO_PAIRGUARD_FORCE= "1"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_295_S2a_restore_off.log 2>&1
Select-String -Path run_295_S2a_restore_off.log -Pattern 'pairguard\]'
Select-String -Path run_295_S2a_restore_off.log -Pattern 'ARM 1 view-pair restore|pools scaled x'
Select-String -Path run_295_S2a_restore_off.log -Pattern 'props interpolated|simulation held to|ours: x=|game_exit requested'
```

**GATE S2a, stated before the run:**
- `ARM 1 view-pair restore OFF` in the banner, and `pools scaled x2`.
- Every SUMMARY reads **`stereo=1 eyes=2 viewrestore=0 force=1`**, **`checks>0`** and
  **`mismatch>0`**. **THE FORCED READ ALONE GUARANTEES ONE MISMATCH PER FRAME**, so
  `mismatch >= frames/600 × 600`; a `mismatch` at or near the frame count means only the forced
  read fired, and a `mismatch` **well above** it means **real engine readers exist in that window**
  — which is `294` §3.6 answered in the affirmative. **Write down which of the two it is.**
- The first eight `MISMATCH` lines name their site. **`modelFindNodeMtx` or
  `projectileFindCollidingProp` appearing there is the finding**; only
  `forced-read-after-lvlRender` appearing is the null answer, and the null answer is still an
  answer.
- `ours: x=367.333`, `props interpolated 0`, zero `simulation held to`, `game_exit requested`.

**IF `mismatch=0` HERE, THE INSTRUMENT IS BROKEN AND EVERY OTHER ARM IS VOID.** The forced read
cannot legitimately match: the pair is eye 1's and the arena is eye 0's, by construction.

---

## §5 — ARM S2b. **ARM 1 ON. THE SAME RUN, ONE KNOB DIFFERENT.**

**Identical to §4 except `GETV_STEREO_VIEWRESTORE=1`.** One behaviour change (`48`).

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
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
$env:GETV_STEREO_PROBE          = "0"
$env:GETV_STEREO_VIEWRESTORE    = "1"
$env:GETV_STEREO_PAIRGUARD      = "600"
$env:GETV_STEREO_PAIRGUARD_FORCE= "1"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_295_S2b_restore_on.log 2>&1
Select-String -Path run_295_S2b_restore_on.log -Pattern 'pairguard\]'
Select-String -Path run_295_S2b_restore_on.log -Pattern 'ARM 1 view-pair restore|pools scaled x'
Select-String -Path run_295_S2b_restore_on.log -Pattern 'props interpolated|simulation held to|ours: x=|game_exit requested'
```

**GATE S2b:** `ARM 1 view-pair restore ON`; every SUMMARY **`viewrestore=1`**, **`checks>0`**,
**`mismatch=0`**, **zero `MISMATCH` lines**. `arena_eye=0 pair_eye=0` on the trailing SUMMARY.

**S2a with mismatches and S2b with none, from the same binary and one knob apart, is the whole
finding.** Either half alone proves nothing (`279` §7).

---

## §6 — ARM S2. **`292`'s S2 RE-RUN. THE IDENTITY ARM, WITH THE RESTORE ON.**

> **►► THE BLOCK BELOW IS A DELEGATION, NOT A BLOCK. USE §10.1, WHICH IS THE SPLICE ALREADY MADE.**
> `296` `[MEASURED]`: `292` §4's block carries no exe-timestamp line and omits `GETV_STEREO_MODE`.
> **The GATE in this section is unchanged and still governs.**

**ARM 1 changes what happens after `lvlRender` returns, so `292`'s S2 is re-run before anyone
talks about separation** — the gate in `RUN-SHEET-292` §5 has not moved. Use **`RUN-SHEET-292` §4
verbatim**, with these two lines added to its block:

```powershell
$env:GETV_STEREO_VIEWRESTORE    = "1"
$env:GETV_STEREO_PAIRGUARD      = "0"
```

**GATE S2: `292` §4's own gates, unchanged, plus — worn, not measured — no new artefact anywhere
on screen.** The guard is off here so the arm measures the game, not the instrument.

**►► `292`'s three faults were all real and all mine. Expect the eye-1 model collapse (`293` §1)
to STILL BE THERE: ARM 1 does not fix it and was never claimed to. `MODEL_MTX 39->1` is ARM 3's
job.** If S2 is otherwise as `292` left it, the gate is met.

---

## §7 — ARM S3. **THE GATE. ONLY AFTER S2 IS CLEAN AT ZERO SEPARATION.**

> **►► USE §10.2 (S3) AND §10.3 (S4). Same reason as §6. The GATES here are unchanged.**

**S3 HAS NEVER RUN.** Use **`RUN-SHEET-292` §5 VERBATIM**, adding:

```powershell
$env:GETV_STEREO_VIEWRESTORE    = "1"
$env:GETV_STEREO_PAIRGUARD      = "0"
```

and then **`RUN-SHEET-292` §6 (S4, the projection-only falsifier) with the same two lines.**
Nothing in `295` changes S3's gate, its prediction block or its failure table.

---

## §8 — ARM S5. **THE COST. `P5`, AND IT IS OWED BY THE `modelFindNodeMtx` CHECK.**

> **►► USE §10.4. It also sets `GETV_STEREO_VIEWRESTORE=1` explicitly, which this section leaves to
> the default — right by accident is the failure `285` names (`296` §11, defect 3).**

`295` §8: the per-node check is `[INFERRED]` negligible and `P5` says that is not a claim. Use
**`RUN-SHEET-292` §7 verbatim** (Cradle, against `272` §5.2's `0.890 ms` mean / `2.504 ms` worst),
adding `$env:GETV_STEREO_PAIRGUARD = "0"` — **the shipping configuration is the one that has to be
free.** Then repeat with `GETV_STEREO_PAIRGUARD=600` and record both; the difference is the
instrument's own cost and it does not have to be zero, it has to be **known**.

---

## §9 — WHAT THIS SHEET DELIBERATELY DOES NOT CONTAIN

- **ARM 3.** `295` §5 — it would make S2a incapable of firing.
- **A separation tuned to a real IPD.** `239`: tuned after the mechanism is proven, never before.
- **Any `dlgrab`.** `293` answered the divergence from `292`'s eighteen existing dumps without a
  run; the next one that is owed is ARM 3's, not this session's.

---

## §10 — **COMPLETE BLOCKS FOR §6, §7 AND §8. `[ADDED 2026-09-02, SESSION `296`.]`**

**§6, §7 and §8 above say "use `RUN-SHEET-292` §4/§5/§6/§7 **verbatim**, adding these two lines".
THAT IS NOT A COMPLETE BLOCK AND `00-STATE` §7a SAYS SO** — *"never describe an action, give the
command, as ONE self-contained copy-paste block"*. The owner would have to open a second sheet,
find the right block, and splice two lines into it correctly four times. **The blocks below are
those splices already made.** They supersede §6/§7/§8's instructions; the **gates** in §6/§7/§8
and in `RUN-SHEET-292` §4/§5/§6/§7 are unchanged and still govern.

**FOUR THINGS WERE WRONG WITH THE SPLICE AS WRITTEN, AND ALL FOUR ARE FIXED BELOW** (§11 records
them):

1. **`RUN-SHEET-292`'s blocks carry NO `Get-Item .\goldeneye.exe` line.** Every block in
   `RUN-SHEET-295` §2-§5 carries one. `133` and `00-STATE` §6's stale-Desktop-tree trap are exactly
   this, and the risk is **higher** after a fresh build than it was in `292`, when the exe under
   test was the only one anybody had. **Added to all four.**
2. **`292` §4's S2 block omits `GETV_STEREO_MODE`** — `285`: an omitted knob silently restores its
   default and reads as a regression. **Added, `=1`, explicitly.**
3. **§8 adds `GETV_STEREO_PAIRGUARD=0` to the cost arms but NOT `GETV_STEREO_VIEWRESTORE`.** ARM 1
   defaults **ON** (`stereo.c:32`, `ge_st_restore = 1`), so S5 would measure the shipping
   configuration *by accident*. That happens to be the configuration §8 wants — **and being right
   by default is what `285` is about.** **Set explicitly, `=1`.**
4. **No block greps the `GETV_FPS=panel` resolution banner.** `panel` is the only knob in these
   blocks whose value is **resolved at runtime**: `gfx_sdl2.c:563` prints
   `GETV_FPS=panel -> N Hz`, and `:553` REFUSES and `exit(1)`s if SDL will not answer. The refusal
   cannot pass silently — **but which N it resolved to is part of the run record**, and a window
   that opened on the wrong monitor resolves to that monitor's rate with no other tell. **Added to
   every block's `Select-String`.**

**RUN THESE IN ORDER, AND ONLY AFTER §1-§5 HAVE BEEN WORN AND PASSED.**

---

### §10.1 — ARM S2. `292` §4's gates, `295` §6's knobs. **The identity arm, restore ON.**

Stand still from the moment the level loads. Do not fire, do not break glass.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
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
$env:GETV_STEREO_PROBE          = "60"
$env:GETV_STEREO_VIEWRESTORE    = "1"
$env:GETV_STEREO_PAIRGUARD      = "0"
$env:GETV_DLGRAB_AT             = "900"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_295_S2_zero.log 2>&1
Select-String -Path run_295_S2_zero.log -Pattern 'GETV_FPS=panel'
Select-String -Path run_295_S2_zero.log -Pattern 'getv\]\[stereo\]|dlgrab_'
Select-String -Path run_295_S2_zero.log -Pattern 'props interpolated|simulation held to|ours: x=|game_exit requested'
```

**Then, identifying the BMP by the log's OWN `dlgrab_` announcement and never by timestamp**
(`00-STATE` §6, `279` §2):

```
py F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\tools\stereo_disparity.py F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows\dlgrab_<N>.bmp
```

**GATE: `RUN-SHEET-292` §4's five gates, unchanged** — banner `separation=0.000 … mode=1`,
`pools scaled x2` with both byte counts; no crash and `game_exit requested`;
`props interpolated 0` and zero `simulation held to`; the script prints
**`CANNOT ANSWER — the two halves match no better shifted than unshifted`** (**that refusal is the
pass**); and **watch the screen for double-rate motion** in tracers, sparks, glass and smoke.
**PLUS §6's:** `GETV_FPS=panel -> 120 Hz`, `ours: x=367.333`, and **no new artefact on screen.**

**►► EXPECT THE EYE-1 MODEL COLLAPSE (`293` §1) TO STILL BE THERE. `MODEL_MTX 39->1` IS ARM 3's
JOB AND ARM 1 NEVER CLAIMED IT.** If S2 is otherwise as `292` left it, the gate is met.

---

### §10.2 — ARM S3. **THE GATE. IT HAS NEVER RUN.**

**ONLY IF §10.1 PASSED.** Stand still, in a room, **FACING A WALL** — the engine's ray test does
not cross portals. If the log's prediction block says **CANNOT ANSWER**, move to face a wall and
re-run; **do not substitute an assumed depth.**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
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
$env:GETV_DLGRAB_AT             = "900"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_295_S3_gate.log 2>&1
Select-String -Path run_295_S3_gate.log -Pattern 'GETV_FPS=panel'
Select-String -Path run_295_S3_gate.log -Pattern 'getv\]\[stereo\]|dlgrab_'
Select-String -Path run_295_S3_gate.log -Pattern 'props interpolated|simulation held to|ours: x=|game_exit requested'
```

**Then measure, with the predicted fraction copied from the log's LAST `MEASURED centre depth`
block BEFORE the grab** (stand still and every block is the same; the block prints the camera
position, so a moved camera is visible):

```
py F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\tools\stereo_disparity.py F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows\dlgrab_<N>.bmp --predicted-frac <the number from the log>
```

**GATE S3 — `RUN-SHEET-292` §5's, unchanged, and the log's numbers decide it, not the picture:**
`VERDICT PASS` (`|measured - predicted| <= 5 px` **and** the sign matches — the RIGHT eye's image
FURTHER LEFT); **the D=1000 and D=4000 predictions stand in a 4.000 ratio**, read off adjacent
lines; `props interpolated 0`, zero `simulation held to`, `ours: x=367.333`, `game_exit requested`.
**`RUN-SHEET-292` §5's failure table is unchanged and still tells you what each failure means —
read it BEFORE the run, not after** (`255` §4, `70`).

---

### §10.3 — ARM S4. **THE FALSIFIER. THE GATE MUST FAIL, AND FAIL IN ONE SPECIFIC WAY.**

**Same spot as S3. Same wall.** One behaviour change from §10.2: `GETV_STEREO_MODE=2`.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
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
$env:GETV_STEREO_MODE           = "2"
$env:GETV_STEREO_PROBE          = "60"
$env:GETV_STEREO_VIEWRESTORE    = "1"
$env:GETV_STEREO_PAIRGUARD      = "0"
$env:GETV_DLGRAB_AT             = "900"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_295_S4_b1.log 2>&1
Select-String -Path run_295_S4_b1.log -Pattern 'GETV_FPS=panel'
Select-String -Path run_295_S4_b1.log -Pattern 'getv\]\[stereo\]|dlgrab_'
Select-String -Path run_295_S4_b1.log -Pattern 'props interpolated|simulation held to|ours: x=|game_exit requested'
```

**Then run the script on THIS BMP with S3's OWN predicted fraction:**

```
py F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\tools\stereo_disparity.py F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows\dlgrab_<N>.bmp --predicted-frac <S3's number>
```

**GATE S4 — `RUN-SHEET-292` §6's, unchanged:** the banner says
**`mode=2 (PROJECTION-ONLY -- B1 REPRODUCED ON PURPOSE, FALSIFIER ONLY, MUST NEVER SHIP ON)`**;
**there IS disparity on screen and it looks like working stereo — that is the point**; and
**the 1/D law is broken** — near the wall it may still pass the 5 px test and the far field will
not move with it. **The verdict for this arm is that the LAW failed, not that the pixels are
wrong.** **If S4 is indistinguishable from S3 in every respect, S3's pass must be WITHDRAWN**
(`49`).

---

### §10.4 — ARM S5. **THE COST. THREE RUNS, ONE BEHAVIOUR CHANGE BETWEEN EACH.**

Against `272` §5.2's Cradle baseline: **CPU `0.890 ms` mean / `2.504 ms` worst, GPU `0.832 ms`,
against the `11.111 ms` period.** Same level, same spot. **Report a DELTA, never an absolute, and
say which half moved.**

**S5a — CPU, stereo ON, the SHIPPING configuration (guard off, ARM 1 on):**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
$env:GETV_SLOTFREE              = "1"
$env:GETV_VSYNC                 = "1"
$env:GETV_FPS                   = "panel"
$env:GETV_SIMHZ                 = "query"
$env:GETV_SIMDIV                = "1"
$env:GETV_WIDESCREEN            = "0"
$env:GETV_ROOMSCISSOR           = "1"
$env:GETV_WINDOW                = "2560x1369"
$env:GETV_STAGE                 = "41"
$env:GETV_DIFFICULTY            = "0"
$env:GETV_BUDGET                = "120"
$env:GETV_STEREO                = "1"
$env:GETV_STEREO_OFFSET         = "500"
$env:GETV_STEREO_MODE           = "1"
$env:GETV_STEREO_VIEWRESTORE    = "1"
$env:GETV_STEREO_PAIRGUARD      = "0"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_295_S5a_cost_stereo.log 2>&1
Select-String -Path run_295_S5a_cost_stereo.log -Pattern 'GETV_FPS=panel'
Select-String -Path run_295_S5a_cost_stereo.log -Pattern 'budget|WORK|pools scaled|props interpolated|game_exit requested'
```

**S5b — CPU, stereo OFF. The mono baseline. One behaviour change (`48`):**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
$env:GETV_SLOTFREE              = "1"
$env:GETV_VSYNC                 = "1"
$env:GETV_FPS                   = "panel"
$env:GETV_SIMHZ                 = "query"
$env:GETV_SIMDIV                = "1"
$env:GETV_WIDESCREEN            = "0"
$env:GETV_ROOMSCISSOR           = "1"
$env:GETV_WINDOW                = "2560x1369"
$env:GETV_STAGE                 = "41"
$env:GETV_DIFFICULTY            = "0"
$env:GETV_BUDGET                = "120"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_295_S5b_cost_mono.log 2>&1
Select-String -Path run_295_S5b_cost_mono.log -Pattern 'GETV_FPS=panel'
Select-String -Path run_295_S5b_cost_mono.log -Pattern 'budget|WORK|pools scaled|props interpolated|game_exit requested'
```

**S5c — THE INSTRUMENT'S OWN COST. S5a with the guard ON, and nothing else changed:**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
$env:GETV_SLOTFREE              = "1"
$env:GETV_VSYNC                 = "1"
$env:GETV_FPS                   = "panel"
$env:GETV_SIMHZ                 = "query"
$env:GETV_SIMDIV                = "1"
$env:GETV_WIDESCREEN            = "0"
$env:GETV_ROOMSCISSOR           = "1"
$env:GETV_WINDOW                = "2560x1369"
$env:GETV_STAGE                 = "41"
$env:GETV_DIFFICULTY            = "0"
$env:GETV_BUDGET                = "120"
$env:GETV_STEREO                = "1"
$env:GETV_STEREO_OFFSET         = "500"
$env:GETV_STEREO_MODE           = "1"
$env:GETV_STEREO_VIEWRESTORE    = "1"
$env:GETV_STEREO_PAIRGUARD      = "600"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_295_S5c_cost_guard.log 2>&1
Select-String -Path run_295_S5c_cost_guard.log -Pattern 'GETV_FPS=panel'
Select-String -Path run_295_S5c_cost_guard.log -Pattern 'budget|WORK|pools scaled|props interpolated|game_exit requested'
```

**GATE S5:** `S5a - S5b` is **stereo's** cost and it is the one the project owes an answer on.
`S5c - S5a` is **the guard's own** cost; it does not have to be zero, it has to be **KNOWN**
(§8). **Cut every window list at the `lvlStageLoad` line numbers — a tail is not a sample**
(`273` §1).

**►► THE GPU HALF (`292` §7's S5c, `GETV_GPUTIME=1` + `GETV_FPS=0` + `GETV_VSYNC=0`) IS NOT
REPRODUCED HERE ON PURPOSE.** `[MEASURED]` `GETV_FPS=0` **locks up on Cradle within seconds, 3 of
3** (`273` §7.3), and `GETV_GPUTIME` refuses to report under a cap (`273`, `274` §7). **Run
`RUN-SHEET-292` §7's S5c block unchanged if the GPU half is wanted, and expect the lockup;** a
`CONTAMINATED` line means the run was capped and its verdict is withheld, which is the gate
working. **ARM 1 and ARM 2 are CPU-side and no GPU delta is predicted** — `[INFERRED]`, and that
is exactly why it is not claimed.

---

## §11 — **CORRECTIONS TO THIS SHEET, FOUND ON THE BRIDGE. `[MEASURED]` 2026-09-02, `296`.**

**THIS SHEET HAD NOT BEEN RUN WHEN `296` OPENED.** `[MEASURED]`: no `run_295_S1_guard_mono.log`,
no `run_295_S2a_restore_off.log`, no `run_295_S2b_restore_on.log` and no `build_295_pairguard.log`
anywhere in the tree, and `goldeneye.exe` is **`2026-09-01 02:10`** — `292d`'s build, three
sessions old. **`NEXT-SESSION-PROMPT-296`'s own branch therefore applies: the sheet is the session,
and ARM 3 was NOT written.** `295` §5's argument holds and is now load-bearing: ARM 3 in this
binary would make `GETV_STEREO_PAIRGUARD` incapable of reporting anything but zero.

**§1's TWO OFFLINE GATES WERE RE-WORN AND BOTH PASS**, on the bridge, against the committed tree
at `b712fa50`:

- `stereo_harness.sh` → **`61 passed, 0 failed` / `VERDICT PASS`**, with the three-arm pairing
  falsifier reading exactly as §1 states it must: `pairmono checks=3 mismatch=0`,
  **`pairoff checks=3 mismatch=2`** and `pairon checks=3 mismatch=0`. **The middle arm fires.**
- `stereo_disparity.py --selftest` → **`injected shift -37, recovered -37, mad_best=0.00
  mad_zero=84.84 PASS`**.

**►► CAVEAT, AND IT IS THE REASON §1 STILL STANDS: THIS RAN UNDER THE BRIDGE'S `gcc 11.4.0`
(Ubuntu), NOT THE MAIN PC'S.** The harness invokes bare `gcc` (`stereo_harness.sh:35,84,105`), so
on the main PC it is MSYS2/mingw's. The seven-file `-fsyntax-only` gate reporting `0 errors` under
a *different* compiler is strong evidence and **is not the same event** as §1's. **RE-RUN §1 ON THE
MAIN PC BEFORE THE BUILD ANYWAY.** It costs seconds and `292`'s link wall is what it is for.

**GATE B1's NINE STRINGS WERE CHECKED AGAINST SOURCE AND ALL NINE ARE PRESENT** — `[MEASURED]`,
`grep -rF` over `vendor/ge-decomp/src` and `getv/src` with the harness excluded: `[getv][stereo] ON`,
`ARM 1 view-pair restore`, `pairguard] ON`, `pairguard] SUMMARY`, `pairguard] MISMATCH`,
`forced-read-after-lvlRender`, `PREDICTION frame=`, `1/D LAW`, `pools scaled x`. **Every `GETV_*`
this sheet sets also exists in source**: `GETV_STEREO`, `_OFFSET`, `_MODE`, `_PROBE`, `_MTXGUARD`,
`_VIEWRESTORE`, `_PAIRGUARD`, `_PAIRGUARD_FORCE`, `GETV_GFXPOOL`. **So GATE B1's list is sound and
a MISSING there would be a build failure, not a typo in the sheet.**

**THE FOUR DEFECTS §10 FIXES**, restated as the general rule each one is an instance of:

| # | defect | the rule it breaks |
|---|---|---|
| 1 | §6/§7/§8 delegate to another sheet "verbatim + two lines" | **`00-STATE` §7a.** A block the owner has to assemble from two documents is not a supplied command. **DELEGATION IS NOT A BLOCK.** |
| 2 | `292`'s blocks carry no `Get-Item .\goldeneye.exe` line | `133`, `00-STATE` §6's stale second tree. **Worse after a fresh build than before one.** |
| 3 | `292` §4's S2 omits `GETV_STEREO_MODE`; §8 omits `GETV_STEREO_VIEWRESTORE` | **`285`.** An omitted knob silently restores its default. §8's default happens to be the wanted value — **being right by accident is the failure `285` names.** |
| 4 | no block greps `GETV_FPS=panel`'s resolution banner | **`00-STATE` §7a**: end with the verification that proves the knob took. `panel` is the one knob here resolved at RUNTIME (`gfx_sdl2.c:563`). A refusal `exit(1)`s (`:553`) and cannot pass silently — **but a window opened on the wrong monitor resolves to that monitor's rate with no other tell.** |

**►► DEFECT 1 IS THE ONE WORTH CARRYING FORWARD, AND IT IS NEW TO `00-STATE` §6.** Three sheets
now (`292` §5/§6/§7 → `295` §6/§7/§8 → here) have chained "use the previous sheet verbatim,
adding". **Each link is individually reasonable and the chain is not: by the third one the owner is
reading three documents to run one command.** A sheet that references another sheet's block must
**reproduce it**, not point at it.

**WHAT `296` DID NOT DO, AND IT IS DELIBERATE:** no ARM 3, no `GETV_STEREO_REBUILD`, no
`chrTick`/`objTick` extraction, no escaping-locals analysis, no `chrprop.c` LF conversion, and no
decision on `chraiUpdateOnscreenPropCount()`'s `zDepth` sort (`295` §6). **All of it waits on this
sheet being worn.** `295` §3's two-accumulator correction and §6's two traps are unchanged and are
still what ARM 3 will need. **`NEXT-SESSION-PROMPT-296` is unretracted — its `[INFERRED]` claims
about the extraction were never tested, because the branch it opens with sent this session
somewhere else.**
