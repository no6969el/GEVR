# RUN SHEET 292 — STEREO. `258` STAGE 6, `P2`/`P3`. THE EYE LOOP AT `lvlRender`.

**2026-09-01, session `292`. WRITTEN AND VALIDATED OFFLINE — NOT BUILT, NOT RUN.** Rule `1`:
every build, every run and every commit is the owner's, on the main PC. The design and the four
source reads behind it are in **`292`**; this sheet is the commands.

**THIS SHEET STOPS AT THE FIRST GATE — the no-headset side-by-side — on purpose (`258` STAGE 6).**
No OpenXR, no head tracking, no aim, no HUD quad, no mirror.

---

## §0 — PRECONDITIONS. **ALL THREE CHECKED ON THE BRIDGE THIS SESSION, SAFE READS ONLY.**

1. **`290`'s three commits and `291`'s docs commit are in.** `git log`: `GoldenEyeVR` `7c58574`,
   `goldeneye-native` `868776a`, `vendor/ge-decomp` `4014d36a`. **`290`/`291` were NOT re-run.**
2. **`tools/fetch-thirdparty.sh verify` reads `15/15 files match pristine + patch`**, run on the
   bridge before any `292` change.
3. **`git ls-files` says `getv/port/fast3d/gfx_pc.c` and `getv/port/fast3d/gfx_sdl2.c` are both
   GITIGNORED — and `292` TOUCHES NEITHER.** The side-by-side is two viewport rectangles inside the
   one N64 framebuffer, exactly as split-screen already does it, so the renderer never learns there
   are two eyes. **NO REGEN IS OWED. `verify` stays a free standing gate** (`287` §5).

**LINE ENDINGS, AND §6's CRLF TRAP IS LIVE.** `fr.c` and `dyn.c` were sitting **CRLF** on disk
while `HEAD` is LF — two of the 2,099. **Both were converted to LF before editing, and `git diff
--stat` immediately after the conversion and before any edit printed NOTHING**, which proves the
conversion added zero lines to the commit. `lv.c` and `bondview2.c` were already LF.
**STAGE BY EXPLICIT PATH LIST, NEVER `git add -A`** (§6; `7a4e7bfd` is what a sweep does).

---

## §0a — WHAT CHANGED. **TWO NEW FILES, FOUR SEAMS. ALL INERT UNLESS ASKED.**

| file | change |
|---|---|
| `src/game/stereo.h` **NEW** | 103 lines — the interface and every knob |
| `src/game/stereo.c` **NEW** | 453 lines — eye count, per-eye viewport, four-tangent frustum, the eye translation, the PREDICTION printer |
| `src/game/lv.c` | the eye loop nested in the per-player body; the sim-tick gate; `geStereoPredict()` |
| `src/fr.c` | the four-tangent projection, **after** `guPerspectiveF` — `g_viPerspNorm` untouched |
| `src/game/bondview2.c` | the eye **translation**, into `cam_pos`, after the `GETV_INTERP` swap |
| `src/game/dyn.c` | **both** pools scaled by the eye count — `292` §1 |

**`git diff --cached --stat` for the decomp must read `707 insertions, 1 deletion, 6 files`**
(`fr.c 24+`, `bondview2.c 24+`, `dyn.c 39+`, `lv.c 65+/1-`, `stereo.c 453+`, `stereo.h 103+`).
**If the number is bigger than that, a line-ending sweep got in — stop and read §6.**

### THE KNOBS, ALL NEW, ALL DEFAULT OFF

| knob | meaning |
|---|---|
| `GETV_STEREO=1` | two eyes, side-by-side, one framebuffer, one swap. **Default 0.** |
| `GETV_STEREO_OFFSET=<f>` | **FULL** eye separation in game units; each eye is displaced ± OFFSET/2. Default `0.0`. |
| `GETV_STEREO_MODE=1\|2` | `1` (default) translation in the **view** matrix. `2` projection-only — **`B1` on purpose. FALSIFIER ONLY, MUST NEVER SHIP ON.** |
| `GETV_STEREO_PROBE=<n>` | print the PREDICTION block every n rendered frames. `0` = off. |

---

## §1 — THE OFFLINE HARNESS. **RE-RUN IT BEFORE THE BUILD. 37/37.**

Already run on the bridge, `-Wall -Wextra -Werror` clean, compiling the **real** `stereo.c`.
Re-runnable anywhere with `gcc` (Git Bash on the main PC works):

```
bash F:/Projects/GEVR/GoldenEyeVR/goldeneye-native/getv/tools/stereo_harness.sh
```
**GATE: `42 passed, 0 failed` / `VERDICT PASS`.** It opens with the **real-header syntax gate** —
all five touched files parsed with `build_windows.ps1`'s own flag list, `0 errors` each. **That
gate exists because its absence cost the first build** (`00-STATE` §6, the force-include trap).
Then the three that matter:
`four tangents == guPerspectiveF` at `max|delta| = 1.192e-07`; `separation goes as 1/D — ratio
4.000`; and, in the `b1` scenario, `MODE=2 is INDISTINGUISHABLE from the real thing at ONE depth`
followed by `ratio 1.000, the detector FIRES`.

And the measuring script carries its own falsifier:
```
py F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\tools\stereo_disparity.py --selftest
```
**GATE: `injected shift -37, recovered -37 … PASS`.**

---

## §2 — BUILD, AND THE BINARY GATE. **SIX STRINGS.** MAIN PC.

`stereo.c` lands under `src/game/`, which `build_windows.ps1:298` globs recursively for `*.c` and
does not match its skip regex — **picked up with no build-file edit**, exactly as `posespine.c`
was. `GE_PORT_NATIVE` is defined for the decomp compile (`build_windows.ps1:210`).

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv
.\build_windows.ps1 *> F:\Projects\GEVR\GoldenEyeVR\build_292_stereo.log 2>&1
Select-String -Path F:\Projects\GEVR\GoldenEyeVR\build_292_stereo.log -Pattern 'error|warning: .*stereo|Build succeeded|goldeneye.exe' | Select-Object -Last 20
Get-Item F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
```

**A knob that is not in the binary reads as a clean null result (`133`, `268` §4):**
```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
$strings = '[getv][stereo] ON','PREDICTION frame=','1/D LAW','MEASURED centre depth','pools scaled x','B1 REPRODUCED ON PURPOSE'
foreach ($s in $strings) {
  $hit = (Select-String -Path .\goldeneye.exe -Pattern ([regex]::Escape($s)) -AllMatches -Encoding Byte -ErrorAction SilentlyContinue)
  "{0,-32} {1}" -f $s, ($(if ($hit) {'FOUND'} else {'MISSING'}))
}
```
**All six must read FOUND.** Then, in **Git Bash**, `tools/fetch-thirdparty.sh verify` — **still
`15/15`**, and it is free: `292` touched nothing under `getv/port/`.

---

## §3 — ARM S1. **IDENTITY: THE KNOB IS OFF AND NOTHING HAPPENED.** Streets, stand still.

The shipping path. **Zero `[getv][stereo]` lines of any kind.**

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
$env:GETV_DIFFICULTY   = "0"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_292_S1_off.log 2>&1
Select-String -Path run_292_S1_off.log -Pattern 'getv\]\[stereo\]'
Select-String -Path run_292_S1_off.log -Pattern 'PANEL REPORTED BY SDL|pace: |slot\] GETV_SLOTFREE|props interpolated|simulation held to|ours: x=|game_exit requested'
```
**GATE S1: the FIRST `Select-String` returns NOTHING.** The second returns the standard gates,
`props interpolated 0`, zero `simulation held to`, and **`ours: x=367.333`** — which mandates the
broken front-end menu text (OPEN item 2) and is **not** a regression (rule `17`).

---

## §4 — ARM S2. **TWO EYES, ZERO SEPARATION. THE COUNTER-EXAMPLE SEARCH, AND IT RUNS FIRST.**

`GETV_STEREO=1` with the offset left at `0.0`: the body renders **twice** with **identical**
views. **This arm asks one question and it is not about stereo:** does the render body survive
being driven twice in one frame? (`292` §6 — `glassRenderShards`, `bullet_sparks_render_all`,
`explosionRenderFlyingParticles` and `weaponRenderTracers` sit outside the sim gate and have not
been read for state.) **Separating *driven twice* from *driven with two views* before the offset
is ever applied is the whole point of running this one first** (`56`, run in reverse).

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
$env:GETV_DIFFICULTY   = "0"
$env:GETV_STEREO       = "1"
$env:GETV_STEREO_OFFSET= "0"
$env:GETV_STEREO_PROBE = "60"
$env:GETV_DLGRAB_AT    = "900"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_292_S2_zero.log 2>&1
Select-String -Path run_292_S2_zero.log -Pattern 'getv\]\[stereo\]|dlgrab_'
Select-String -Path run_292_S2_zero.log -Pattern 'props interpolated|simulation held to|ours: x=|game_exit requested'
```
**Stand still from the moment the level loads. Do not fire, do not break glass.**

**GATE S2 — four things, and each can fail on its own:**
1. **The banner reads `separation=0.000 … [GETV_STEREO_OFFSET unset -> 0.0, the IDENTITY arm]`
   … `mode=1`** and **`pools scaled x2`** with both byte counts printed.
2. **It does not crash, and the log ends `game_exit requested`.** A truncated display list
   segfaults *silently* (`292` §1) — **a crash here is the pool, not the eye loop.** If it
   crashes, that is the finding; report the pool numbers from the banner and stop.
3. **`props interpolated 0`, zero `simulation held to`** — the sim did **not** tick twice.
4. **The two halves are pixel-identical.** Identify the BMP by the log's **own** `dlgrab_`
   announcement, never by timestamp (§6, `279` §2):
   ```
   py F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\tools\stereo_disparity.py F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows\dlgrab_<N>.bmp
   ```
   **It must print `CANNOT ANSWER — the two halves match no better shifted than unshifted`.**
   **THAT REFUSAL IS THE PASS FOR THIS ARM.** At zero separation there is nothing to find, and an
   instrument that reported `dx = 0` instead would be reporting a number it cannot have.
5. **WATCH THE SCREEN FOR DOUBLE-RATE MOTION** — tracers, sparks, glass, smoke. Two identical
   halves with particles running at twice the rate is `292` §6's `[INFERRED]` failing, and it is
   a *different* fault from anything stereo.

---

## §5 — ARM S3. **THE GATE. `GETV_STEREO_OFFSET=500`, DELIBERATELY ABSURD.**

**Stand still, in a room, FACING A WALL** — the engine's ray test does not cross portals, so the
prediction needs the wall to be in the player's own room. If the block says **CANNOT ANSWER**,
move to face a wall and re-run; **do not substitute an assumed depth.**

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
$env:GETV_DIFFICULTY   = "0"
$env:GETV_STEREO       = "1"
$env:GETV_STEREO_OFFSET= "500"
$env:GETV_STEREO_MODE  = "1"
$env:GETV_STEREO_PROBE = "60"
$env:GETV_DLGRAB_AT    = "900"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_292_S3_gate.log 2>&1
Select-String -Path run_292_S3_gate.log -Pattern 'getv\]\[stereo\]|dlgrab_'
Select-String -Path run_292_S3_gate.log -Pattern 'props interpolated|simulation held to|ours: x=|game_exit requested'
```

**Then measure, with the predicted fraction copied from the log's LAST `MEASURED centre depth`
block before the grab** (stand still and every block is the same; the block prints the camera
position so a moved camera is visible):

```
py F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\tools\stereo_disparity.py F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows\dlgrab_<N>.bmp --predicted-frac <the number from the log>
```

**GATE S3 — and the log's own numbers decide it, not the picture:**
- **`VERDICT PASS`** from the script: **`|measured - predicted| <= 5 px` AND the sign matches —
  the RIGHT eye's image FURTHER LEFT.**
- **AND the log's 1/D block: the D=1000 and D=4000 predictions must stand in a 4.000 ratio.**
  Read them off; they are printed on adjacent lines.
- **`props interpolated 0`, zero `simulation held to`, `ours: x=367.333`, `game_exit requested`.**

**WHAT EACH FAILURE MEANS, WRITTEN BEFORE THE RUN** (`255` §4, `70`):
| result | meaning |
|---|---|
| `CANNOT ANSWER`, halves identical | **`B1`.** Two views were requested and one image was drawn. Read `bondview2.c`'s seam first — is `geStereoOffsetCameraPos` returning 1? |
| sign is wrong | the eyes are swapped: `geStereoEyeViewport` puts eye 0 on the left, `geStereoOffsetCameraPos` puts eye 0 at `-half`. One of the two disagrees. |
| magnitude wrong by a constant factor | a units error. The separation is in **game units** and the printed prediction is a **fraction of the eye width** — check the script found the right play area, printed on its second line. |
| magnitude right, but the log's ratio is not 4.000 | **the translation did not reach the view matrix.** That is `B1` wearing the right clothes — and it is exactly what S4 produces on purpose. |

---

## §6 — ARM S4. **THE FALSIFIER. THE GATE MUST FAIL, AND FAIL IN ONE SPECIFIC WAY.**

`GETV_STEREO_MODE=2` puts the separation in the **projection** and leaves the view matrix alone —
`B1`, built on purpose, and tuned so that at D = 1000 it produces **exactly** the disparity the
real thing produces. **It is the arm that proves S3's pass was not a rubber stamp** (`290` A3's
shape; an instrument that cannot be made to say FAIL is not an instrument).

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
$env:GETV_DIFFICULTY   = "0"
$env:GETV_STEREO       = "1"
$env:GETV_STEREO_OFFSET= "500"
$env:GETV_STEREO_MODE  = "2"
$env:GETV_STEREO_PROBE = "60"
$env:GETV_DLGRAB_AT    = "900"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_292_S4_b1.log 2>&1
Select-String -Path run_292_S4_b1.log -Pattern 'getv\]\[stereo\]|dlgrab_'
```
**Same spot as S3. Same wall.**

**GATE S4:**
1. The banner says **`mode=2 (PROJECTION-ONLY -- B1 REPRODUCED ON PURPOSE, FALSIFIER ONLY, MUST
   NEVER SHIP ON)`**.
2. **There IS disparity on screen** — the halves are not identical, and to the eye it looks like
   working stereo. **That is the point.**
3. **AND IT IS THE SAME AT EVERY DEPTH.** Run the script on this BMP with **S3's own predicted
   fraction**: near the wall it may still pass the 5 px test, and the far field will not move
   with it. **The verdict for this arm is that the 1/D law is broken, not that the pixels are
   wrong.**

**If S4 is indistinguishable from S3 in every respect, the gate is not measuring what it claims
and S3's pass must be withdrawn** (`49`: an instrument that prints the same thing on a working
and a broken build is not an instrument).

---

## §7 — ARM S5. **THE COST, AGAINST `272`'s CRADLE BASELINE.**

`272`: **CPU 0.890 ms + GPU 0.832 ms against the 11.111 ms period.** Same level, same spot.

**S5a — the CPU half, under the normal cap:**
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
$env:GETV_STAGE        = "41"
$env:GETV_DIFFICULTY   = "0"
$env:GETV_BUDGET       = "120"
$env:GETV_STEREO       = "1"
$env:GETV_STEREO_OFFSET= "500"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_292_S5a_cost_stereo.log 2>&1
Select-String -Path run_292_S5a_cost_stereo.log -Pattern 'budget|WORK|pools scaled|props interpolated|game_exit requested'
```
**Then the SAME block with `$env:GETV_STEREO` removed entirely, to `run_292_S5b_cost_mono.log`.**
Two runs, one behaviour change between them (`48`). **Cut both window lists at the `lvlStageLoad`
line numbers — a tail is not a sample (`273` §1).**

**S5c — the GPU half. `GETV_GPUTIME` ONLY WORKS WITH `GETV_FPS=0`** (`273`, `274` §7), and
**`[MEASURED]` `GETV_FPS=0` LOCKS UP ON CRADLE within seconds, 3 of 3** (`273` §7.3). **So take a
SHORT sample and expect the lockup**; if the log prints `CONTAMINATED` the run was capped and its
verdict is withheld, which is the gate working.
```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
$env:GETV_SLOTFREE     = "1"
$env:GETV_VSYNC        = "0"
$env:GETV_FPS          = "0"
$env:GETV_SIMHZ        = "query"
$env:GETV_SIMDIV       = "1"
$env:GETV_WIDESCREEN   = "0"
$env:GETV_ROOMSCISSOR  = "1"
$env:GETV_WINDOW       = "2560x1369"
$env:GETV_STAGE        = "41"
$env:GETV_DIFFICULTY   = "0"
$env:GETV_GPUTIME      = "1"
$env:GETV_STEREO       = "1"
$env:GETV_STEREO_OFFSET= "500"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_292_S5c_gpu_stereo.log 2>&1
Select-String -Path run_292_S5c_gpu_stereo.log -Pattern 'gputime|CONTAMINATED|ms'
```
**REPORT THE COST AS A DELTA AGAINST `272`, NOT AS AN ABSOLUTE**, and say which half moved.
**No claim is made here about what the number will be.**

---

## §8 — THE COMMITS, IN ORDER, AND ONLY AFTER THE ARMS ARE WORN. MAIN PC.

**NO REGEN IS OWED** — nothing under `getv/port/`; `verify` reads `15/15` before **and** after
the build (re-check after; it is free). **`COMMIT-NOW.cmd` will NOT do step 1** — `vendor/` is
gitignored by `goldeneye-native` and invisible to all three of its passes (§6).

**►► S1, S2, S2b, S2d and S2e HAVE RUN — `292` §5a carries the results. The blocks below are the
FOLLOW-UP commit for the three fixes and the guard. S3 has NOT run.**

**►► THE FIRST THREE COMMITS ARE ALREADY IN** — `vendor/ge-decomp` `25ef9791`,
`goldeneye-native` `8af5d72`, `GoldenEyeVR` `317f183`, made before the build. **Nothing is
rewritten** (rule `2`); the link fix is a FOLLOW-UP commit, and these are its paths:

1. **`vendor/ge-decomp` — EXPLICIT PATH LIST, NEVER `-A`** (a bare `git diff` there prints
   2,101 lines of CRLF churn — §6). Stage exactly
   `src/fr.c src/game/lv.c src/game/stereo.c src/game/stereo.h src/game/bondview2.c`.
   **`git diff --cached --stat` must read `231 insertions, 13 deletions, 5 files`.**
   Message: **`COMMIT-MESSAGE-2026-09-01d-decomp.txt`, in the `GoldenEyeVR` ROOT** (`287`: a
   message file beside the repo it describes is invisible to `commit-now.ps1`).
2. **`goldeneye-native`** — `getv/tools/stereo_harness.c`, `getv/tools/stereo_harness.sh`,
   `getv/port/src/port_support.c` (the guard's exit hook; `git ls-files` says TRACKED, and
   `verify` still reads `15/15`, so **no regen is owed**).
   **`60 insertions, 7 deletions, 3 files`.** Message: `COMMIT-MESSAGE-2026-09-01d-native.txt`.
3. **`GoldenEyeVR`** — `00-STATE.md`, `292-…md`, `RUN-SHEET-292.md`, `NEXT-SESSION-PROMPT-293.md`.
   Message: `COMMIT-MESSAGE-2026-09-01d.txt`.

**If a `git status`/`git diff` was ever run over the bridge and left a 0-byte `index.lock`, it is
the assistant's litter — confirm 0 bytes, confirm no git is running, `Remove-Item` it, re-commit**
(§6).

---

## §9 — WHAT THIS SHEET DELIBERATELY DOES NOT CONTAIN

**No OpenXR, no runtime, no session, no swapchain, no compositor. No head tracking — the offset is
a constant. No hand aim (STAGE 7, `P8`). No vignette, HUD quad or desktop mirror. No
`gevr_xr.c`.** And **no tuning of the separation:** `500` is deliberately absurd; ~6 cm is tuned
**after** the mechanism is proven, never before (`239`, `255` §4).

**Nothing past the first gate is planned. That is the instruction and it is also the right call:
S2 can still say the render body does not survive two passes, and S3 can still say `B1`.**
