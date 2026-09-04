# RUN-SHEET-303 — TWO FIXES, AND BOTH CAME OUT OF `302`'s OWN NUMBERS

**WRITTEN OFFLINE 2026-09-03, AFTER `RUN-SHEET-302` WAS WORN IN FULL.** Nothing here has run.

## §0 — WHAT `302` SETTLED, IN ONE TABLE

| `302` read | verdict |
|---|---|
| §3a control: `1-1082` / **`1083-1454` (372)** / `1455-1623` (169) | **reproduced `301` S2 TO THE FRAME.** The census change did not move the scene |
| §3b sum | `type` == its buckets on every line |
| **§3c: cumulative `viewer=541`, every other bucket ZERO** | **The skipped prop is the VIEWER, on all 541 frames** |
| §4: `beyond_far=16534203` (**13.2%** of 125.5M vtx), `all_far(hw-rejects)=0`, `clamped=0` | **The far field is a measured catastrophe** |
| owner, §4: *"foggy after a certain distance and flickering"*, *"characters and cars are transparent and flickering"*, *"much less view"* | `[REPORTED]` |

**►►►► AND THE `302` §3c TABLE SAID `viewer=` MEANT "BENIGN". IT IS NOT, AND THE THING THAT
DISPROVED IT WAS ALREADY ON DISK.** `dlgrab_eyecensus.py` on the dead frames themselves
(`grabs_302_S3`, frames `1155`, `1243`, `1381`) reads:

```
  gSPSegment MODEL_COL1(5)   eye0 19    eye1 0    <-- DIVERGES
  gSPSegment MODEL_MTX(3)    eye0 38    eye1 0    <-- DIVERGES
  gSPSegment MODEL_VTX(4)    eye0 16    eye1 0    <-- DIVERGES
  DL CALL targets            eye0 21    eye1 3     only in eye1 = 0  <-- STRICT SUBSET
```

**The second eye is not receiving 38 model matrices it plainly needs. `only in eye1 = 0` makes it
a ONE-DIRECTIONAL LOSS, not a divergence.** `item 4`'s *"the viewer is already per-eye"* is
**FALSIFIED**, and so is the row of `302` §3c that rested on it. **That row was mine and it was
wrong — written from `item 4`'s prose instead of from the render path.** The rule it broke is the
project's own (`301` §0), and this is the fourth time: `H1`, `H3`, `302` §3c.

**THE CALL NOBODY FOLLOWED, AND IT IS FOUR LINES.** `chrpropRender()` sends `PROP_TYPE_VIEWER` to
`bondviewRenderProp()` (`chrprop.c:884`), and that function (`bondview2.c:11666`) is:

```c
Gfx *bondviewRenderProp(PropRecord *arg0, Gfx *arg1, s32 arg2)
{
    if (arg0->chr != NULL) { arg1 = chrRenderProp(arg0, arg1, arg2); }
    return arg1;
}
```

**A viewer prop with a chr RENDERS EXACTLY LIKE A CHR**, so it consumes exactly the per-eye state
`chrBuildRenderState()` produces. `293` §2.1's *"the second eye's ONE fresh allocation per frame"*
measured the **VIEWMODEL's** allocation — a different object — and `item 4` attached that reading
to the wrong thing. The rest of `chrprop.c` already pairs the two types at `:1364`, `:1405`,
`:1612` and `:1645`. **The rebuild pass was the only place that did not.**

---

## §0.1 — THE SECOND FIX, AND `302` §4's NUMBER IS THE WHOLE ARGUMENT

`299` §8.1 stood **BOTH** of `gfx_pc.c`'s per-vertex clamps down when `GL_DEPTH_CLAMP` is active,
on one argument: that doing them as well would re-introduce the gradient tilt the extension exists
to remove. **THAT ARGUMENT WAS MEASURED ON THE NEAR PLANE ONLY** — N1/N2/N3, one alley, one wall —
**AND APPLIED TO BOTH.**

| plane | stand down? | evidence |
|---|---|---|
| **near** | **YES — correct** | `301` §5: D1 artefact **GONE**, D2 **PRESENT**. `299` §8.1 closes |
| **far** | **NO — and this is the bug** | `302` §4: `beyond_far` **13.2%** vs `301` D1's 0.7%, `all_far(hw-rejects)=0`, `clamped=0` |

**THE MECHANISM.** With clipping disabled at the far plane, geometry past it is neither rejected
nor pulled to `z==w`. **Every fragment of it is clamped by GL to the SAME maximum depth, so it all
z-fights** — with itself and with whatever is legitimately at the far plane. That is *"foggy and
flickering"*, *"transparent"*, and *"much less view"*, exactly.

**►►►► AND IT IS NOT A STEREO FAULT, WHICH THE OWNER'S OWN WORDS INVITE YOU TO THINK.** *"It's
almost like both eyes from before are now layered over each other."* **`302` §4 WAS A MONO RUN** —
`dlgrab_D3_33362.txt` has **ONE** viewport load, and the log carries no `[getv][stereo]` banner at
all. **There is no second eye in that run to layer.** The doubling is z-fighting. Do not go back
to the eye loop for it.

The per-vertex far clamp moves `z` **before** interpolation, which is what keeps those 16.5M
vertices ordered against each other instead of collapsed onto one plane. **It does not fight
`GL_DEPTH_CLAMP`; it feeds it.**

### WHAT IS WRITTEN, AND IT IS GATED

| file | repo | change |
|---|---|---|
| `src/game/chrprop.c` | `vendor/ge-decomp` | `GETV_STEREO_REBUILD_VIEWER` (default `1`) + banner; VIEWER-with-chr → `chrBuildRenderState()`; **`view=` joins the balance** |
| `getv/port/fast3d/gfx_pc.c` | ►► **GITIGNORED** | the far branch drops `&& !ge_depth_clamp_active()`; **`GETV_FARCLAMP` gains a banner** |
| `getv/port/fast3d/ge_depthclamp.c` | `goldeneye-native` | its banner said BOTH clamps stand down. **That is now a lie and lies in banners are what this project hunts** |

**►► THE BALANCE INVARIANT CHANGED: `chr+obj+view+skipped == zsnap`.** A sheet quoting
`chr+obj+skipped` is quoting the old one. **`302` §3b's gate must be re-read with `view` in it.**

**Ten of ten gates PASS offline, `regen` run, `verify` `15/15`.**

---

## §1 — THE OFFLINE GATES, ON THE MAIN PC. **BEFORE ANYTHING ELSE.**

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

**GATE §1 — ten `VERDICT PASS`.** `RUN-SHEET-301` §1 states all ten in full. The two this session
moves:

1. **`stereo_harness`: `src/game/chrprop.c PASS 0 errors` and `63 passed, 0 failed`.** The viewer
   admission lives there and the real-header gate is the only thing that parses it offline.
2. **`port_syntax_gate: 51 ok, 0 failed, 6 not covered`.** `gfx_pc.c` and `ge_depthclamp.c` are
   both in it. **A stub pass is PARSES AND TYPE-CHECKS, never "verified"** — the build is still
   the authority for these two.

---

## §2 — **THE REGEN. IT IS OWED THIS TIME AND IT IS THE STEP THAT GETS SKIPPED.**

**►►►► `gfx_pc.c` IS GITIGNORED. `302` HAD NO REGEN STEP AND THIS ONE DOES — DO NOT CARRY THE
HABIT ACROSS.** Its change exists ONLY in `getv/patches/thirdparty/0001-getv-port-layer.patch`. A
build before the regen builds code that is in no commit.

**The regen has already been run offline and `verify` reads `15/15`, so `verify` alone is the gate
here.** Run `regen` again only if `verify` says `DIFFERS`.

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
& 'C:\Program Files\Git\bin\bash.exe' tools/fetch-thirdparty.sh verify 2>&1 | Select-Object -Last 3
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv
.\build_windows.ps1 *> ..\..\build_303_twofixes.log
Get-Content ..\..\build_303_twofixes.log | Select-Object -Last 12
```

### 2c — **RECORD THE BINARY'S IDENTITY.**

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
"$((Get-FileHash .\goldeneye.exe -Algorithm SHA256).Hash) $((Get-Item .\goldeneye.exe).Length)" |
  Set-Content .\EXPECTED-EXE-303.txt
Get-Content .\EXPECTED-EXE-303.txt
```

**`302`'s binary was `DF5CAB2A...1438 18068657`. A match means the edit did not take.**

---

## §3 — V1 / V2. **DOES ADMITTING THE VIEWER FILL THE SECOND EYE?**

**Same environment as `302` §3, one behaviour change between the arms.** Press F9 six times in the
first five seconds, in the opening, exactly as before — `302`'s grabs landed at `1155-1381` and
that block is deterministic.

### 3.1 — V1. **The fix ON (shipping default).**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
$want = (Get-Content .\EXPECTED-EXE-303.txt).Trim()
$got  = "$((Get-FileHash .\goldeneye.exe -Algorithm SHA256).Hash) $((Get-Item .\goldeneye.exe).Length)"
if ($want -ne $got) { throw "BINARY MISMATCH -- this is NOT the 303 build. want [$want] got [$got]" }
if (Test-Path .\run_303_V1_viewer_on.log) { throw "run_303_V1_viewer_on.log EXISTS -- rename it or pick a new name (H5)." }
Get-ChildItem .\dlgrab_*.txt,.\dlgrab_*.bmp -ErrorAction SilentlyContinue | Measure-Object | Select-Object -ExpandProperty Count
$env:GETV_ARM                    = "V1"
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
.\goldeneye.exe *> run_303_V1_viewer_on.log 2>&1
Select-String -Path run_303_V1_viewer_on.log -Pattern 'getv\]\[run\] ARM='
Select-String -Path run_303_V1_viewer_on.log -Pattern 'GETV_STEREO_REBUILD_VIEWER='
Select-String -Path run_303_V1_viewer_on.log -Pattern 'dlgrab_|getv\]\[shot\]'
Select-String -Path run_303_V1_viewer_on.log -Pattern 'rebuild\] WINDOW' | Select-Object -Last 1
Select-String -Path run_303_V1_viewer_on.log -Pattern 'EXCEPTION|game_exit requested'
New-Item -ItemType Directory -Force -Path .\grabs_303_V1 | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_303_V1 -Force -ErrorAction SilentlyContinue
Get-ChildItem .\grabs_303_V1 | Select-Object Name, Length
```

### 3.2 — V2. **The fix OFF. This must reproduce `302` §3 exactly.**

Same block with `$env:GETV_ARM = "V2"`, `$env:GETV_STEREO_REBUILD_VIEWER = "0"`, log
`run_303_V2_viewer_off.log`, grabs into `grabs_303_V2`.

### GATE §3a — **THE BANNER, AND IT IS THE FIRST THING.**

`[getv][stereo][rebuild] GETV_STEREO_REBUILD_VIEWER=1` in V1 and `=0` in V2. **A knob whose value
is not echoed is a knob you have not set.**

### GATE §3b — **THE CENSUS, AND THE BALANCE HAS CHANGED.**

| arm | dead block reads | `viewer=` bucket |
|---|---|---|
| **V1** | **`chr=0 obj=0 view=1 skipped=0`** | **`0`** |
| **V2** | `chr=0 obj=0 view=0 skipped=1` | `1` |

**`chr+obj+view+skipped` must equal `zsnap=` in BOTH.** And **`ZERO-REBUILD FRAMES` cumulative
must fall by 541 in V1** — `302` read `630 of 2664` on a longer run; the 372+169 must leave it.
**A V1 that still reports 372 zero-rebuild frames means `view` did not reach the accumulator.**

### ►►►► GATE §3c — **THE PICTURE, AND IT IS THE ONLY GATE THAT MATTERS.**

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
py ..\..\getv\tools\dlgrab_eyecensus.py grabs_303_V1\dlgrab_V1_*.txt
py ..\..\getv\tools\dlgrab_eyecensus.py grabs_303_V2\dlgrab_V2_*.txt
```

| arm | `MODEL_MTX` | reading |
|---|---|---|
| **V1** | **eye0 38, eye1 38** | **THE FIX WORKS.** The second eye receives the viewer's models |
| **V2** | eye0 38, eye1 **0**, `only in eye1 = 0` | must reproduce `302` exactly, or the A/B is void |
| V1 reads eye1 **non-zero but < 38** | a PARTIAL admission | **Do not call that a pass.** Something in the chr path is still eye-0-only |
| V1 reads eye1 **38 and the picture is still wrong** | the models arrive and something else eats them | **`299` §8.2's symptom was never only about admission.** Re-open with the grabs, not the census |

**AND LOOK AT THE OPENING WITH YOUR EYES.** The census can only say the commands are there.

---

## §4 — FC1 / FC2. **THE FAR CLAMP, ON THE ONE SCENE THAT REPEATS ITSELF.**

**►►►► THE VENUE IS THE OWNER'S OWN FIND AND IT IS BETTER THAN ANY ALLEY.** `302` §4 ended in the
**character introduction video, which LOOPS** — a fixed camera, a fixed sequence, the same frames
every time. **That removes the one thing that made `301` D1/D2 arguable**: the SCENE counters
could not be compared because the two arms were not standing in the same place (`301` D1 ran 14%
longer; `straddle` only agreed once normalised per Mvtx). **On a loop there is nothing to
normalise.** Reach it the way it was reached: start the level, die, let it restart into the
introduction loop. **Then F9 four times, spread across one full cycle of the loop.**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
$want = (Get-Content .\EXPECTED-EXE-303.txt).Trim()
$got  = "$((Get-FileHash .\goldeneye.exe -Algorithm SHA256).Hash) $((Get-Item .\goldeneye.exe).Length)"
if ($want -ne $got) { throw "BINARY MISMATCH -- this is NOT the 303 build. want [$want] got [$got]" }
if (Test-Path .\run_303_FC1_farclamp_on.log) { throw "run_303_FC1_farclamp_on.log EXISTS -- rename it or pick a new name (H5)." }
Get-ChildItem .\dlgrab_*.txt,.\dlgrab_*.bmp -ErrorAction SilentlyContinue | Measure-Object | Select-Object -ExpandProperty Count
$env:GETV_ARM         = "FC1"
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
.\goldeneye.exe *> run_303_FC1_farclamp_on.log 2>&1
Select-String -Path run_303_FC1_farclamp_on.log -Pattern 'getv\]\[run\] ARM='
Select-String -Path run_303_FC1_farclamp_on.log -Pattern 'getv\]\[depthclamp\]'
Select-String -Path run_303_FC1_farclamp_on.log -Pattern 'GETV_FARCLAMP='
Select-String -Path run_303_FC1_farclamp_on.log -Pattern 'GETV_NEARCLAMP='
Select-String -Path run_303_FC1_farclamp_on.log -Pattern '\[getv\]\[far\]'  | Select-Object -Last 1
Select-String -Path run_303_FC1_farclamp_on.log -Pattern '\[getv\]\[near\]' | Select-Object -Last 1
Select-String -Path run_303_FC1_farclamp_on.log -Pattern 'dlgrab_|getv\]\[shot\]'
Select-String -Path run_303_FC1_farclamp_on.log -Pattern 'EXCEPTION|game_exit requested'
New-Item -ItemType Directory -Force -Path .\grabs_303_FC1 | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_303_FC1 -Force -ErrorAction SilentlyContinue
Get-ChildItem .\grabs_303_FC1 | Select-Object Name, Length
```

Same block with `$env:GETV_ARM = "FC2"`, `$env:GETV_FARCLAMP = "0"`, log
`run_303_FC2_farclamp_off.log`, grabs into `grabs_303_FC2`. **FC2 is `302` §4's behaviour and must
reproduce the flicker.**

### GATE §4a — **THE BANNERS, AND ONE OF THEM WAS REWRITTEN BECAUSE IT WAS FALSE.**

- `[getv][farclamp] GETV_FARCLAMP=1` / `=0`. **NEW. This knob was silent and load-bearing at the
  same time, which is why `302` §4 went a whole run without an explanation.** That is `H4` costing
  a cycle for the third time.
- `[getv][depthclamp] GL_DEPTH_CLAMP ON ... ONLY THE **NEAR** PER-VERTEX CLAMP STANDS DOWN`. **If
  this still reads "PER-VERTEX clamps STAND DOWN" you are running the `302` binary.**

### GATE §4b — **THE CENSUS. THREE NUMBERS AND THEY DISAGREE BY ARM.**

| | `[getv][near] clamped` | `[getv][far] clamped` | `beyond_far` |
|---|---|---|---|
| **FC1** | **`0`** | **NON-ZERO, and near `straddle`'s order of magnitude** | large — that is the point of the venue |
| **FC2** | `0` | `0` | large |

**FC1's far `clamped=0` WOULD BE A FAILURE**, and the only one of these zeros that is a receipt is
the NEAR one — it is `301` §5's fix still working, and it must not regress. **If near `clamped`
goes non-zero in either arm, the near fix has been undone and nothing else here is readable.**

**GATE §4c — `beyond_far` MUST BE LARGE IN BOTH.** `302` read `13.2%`. **A small `beyond_far`
means the loop was not reached and *"I saw nothing wrong"* is a `279` §7 null result** — an
instrument pointed at nothing.

### ►►►► GATE §4d — THE VERDICT, AND IT IS YOUR EYES ON THE SAME LOOP

| FC1 | FC2 | reading |
|---|---|---|
| **clean distance** | **flickering / transparent** | **THE FIX WORKS.** `299` §8.1's stand-down was too wide by exactly one plane |
| flickering | flickering | the far clamp is not what collapses it. **`GETV_DEPTHCLAMP=0` should then be tried on the SAME loop before anything else** |
| clean | clean | **VOID** — FC2 did not restore `302`'s behaviour. Check its `[getv][farclamp]` banner first |

---

## §5 — THE COMMITS. **THREE REPOS, AND THE FIRST TWO BOTH HAVE A TRAP.**

**►►►► READ THIS BEFORE THE FIRST `git add`: THESE COMMITS CARRY `302`'s WORK AS WELL.**
`RUN-SHEET-302` §5 was written to be runnable at any time and **it was never run**, so `302`'s
arms were worn against a tree that is still uncommitted. `303` edits the same files.
**The two sessions can no longer be split into two commits without unpicking interleaved hunks —
and the two commits that produced would be ones neither of which was ever built or run.**
`COMMIT-MESSAGE-2026-09-03c-*.txt` are **SUPERSEDED**; each `-d-` message now carries its `-c-`
text verbatim at the end. **Use the `d` files and only the `d` files.**

Run whenever it suits; both edits are gated offline.

```powershell
# 5.1 -- decomp. EXPLICIT PATH LIST. A bare `git status` here prints 2,106 CRLF-dirty files.
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\vendor\ge-decomp
git --no-optional-locks status --short -- src/game/chrprop.c
git diff --ignore-cr-at-eol -- src/game/chrprop.c | Select-Object -First 60
git add src/game/chrprop.c src/game/ge_rebuild_window.h   # ge_rebuild_window.h is `302`'s -- see the banner above
git commit -F ..\..\..\COMMIT-MESSAGE-2026-09-03d-decomp.txt
git log --oneline -1

# 5.2 -- native. THE PATCH IS PART OF THE COMMIT. `verify` 15/15 BEFORE the add.
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
& 'C:\Program Files\Git\bin\bash.exe' tools/fetch-thirdparty.sh verify 2>&1 | Select-Object -Last 1
git --no-optional-locks status --short -- getv/
git add getv/patches/thirdparty/0001-getv-port-layer.patch getv/port/fast3d/ge_depthclamp.c getv/tools/ge_rebuild_window_harness.c
git commit -F ..\COMMIT-MESSAGE-2026-09-03d-native.txt
git log --oneline -1

# 5.3 -- documents
Set-Location F:\Projects\GEVR\GoldenEyeVR
git --no-optional-locks status --short -- repo/docs
git add repo/docs
git commit -F .\COMMIT-MESSAGE-2026-09-03d.txt
git log --oneline -1
```

**GATE 5.2 — `verify` must read `15/15` BEFORE the `git add`.** `gfx_pc.c` itself is gitignored and
**cannot** be staged; the patch is the only record of it. **If you stage `getv/` without the patch,
the far-clamp fix is in the binary and in no commit.**

**►►►► GATE 5.0 — THE STAGED SET MUST EQUAL THE DIRTY SET, IN BOTH CODE REPOS. THIS SHEET'S ADD
LISTS WERE WRONG ONCE ALREADY.** They were written for `303`'s three files and not widened when
`302`'s commits turned out never to have been run, so they silently dropped
`src/game/ge_rebuild_window.h` and `getv/tools/ge_rebuild_window_harness.c` — **two files that were
BUILT INTO and MEASURED BY `302`.** A hand-written path list is a thing that goes stale; check it
against the tree rather than trusting it:

```powershell
# decomp -- MUST print exactly: chrprop.c, ge_rebuild_window.h
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\vendor\ge-decomp
git --no-optional-locks status --short -- src/game/chrprop.c src/game/ge_rebuild_window.h
# native -- MUST print exactly: the patch, ge_depthclamp.c, ge_rebuild_window_harness.c
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
git --no-optional-locks status --short -- getv/
```

**Anything dirty that is not in the add list below is a file this sheet forgot.** Run this BEFORE
5.1, not after. (The decomp needs the explicit two-path list — a bare `git status` there prints
2,106 CRLF-dirty files.)

**No attribution trailers in any of these messages.**

---

## §6 — AFTER `303`

- **GROUP B closes or re-opens on §3c**, and `B3` (re-measure with grabs inside the opening) is
  already most of the way done by V1's own grabs.
- **`H4` HAS NOW COST THREE CYCLES** (`GETV_FILTERING` two, `GETV_FARCLAMP` one). `MEDIUM` is
  arguably wrong. `knob_banner_survey.py --used-in repo/docs` ranks the remaining 323; **the ones
  that gate a BEHAVIOUR, not the ones mentioned most, are the ones that bite.** Consider re-ranking
  the survey by "does this knob change what is drawn".
- **GROUP C**, the `NaN` — `HIGH`, precondition none, **still untouched since `299` §8.4.** It is
  now the largest unexamined thing on the board.
- **GROUP D** unblocked, `D1` `LOW`. **`H9` still held**, and every visual verdict in `298`-`303`
  is `[REPORTED]`. **The introduction loop found in `302` is the best candidate for the known-good
  reference frame `H9` needs** — it is deterministic, it is always available, and it does not
  depend on where anyone stood.
