# RUN-SHEET-302 — THE SKIP SPLIT'S OWN SPLIT

**WRITTEN OFFLINE 2026-09-03, AFTER `RUN-SHEET-301` WAS WORN IN FULL.** Nothing in it has been
run. The build, every run and every commit are the owner's.

## §0 — WHY THIS EXISTS, IN ONE TABLE

`301` §7 answered `299` §8.3 and immediately exposed the next layer of the same defect.

| `301` §7 read | what it settled | what it did NOT settle |
|---|---|---|
| `flag=0` on all **541** skipped frames | `chrprop.c:476`'s *"this cannot happen today"* is **NOT falsified**. There is no per-eye admission bug. **B1 is answered** | — |
| `type=1` on all 541 | the dead eye is the **deliberate `else` branch** | **WHICH type.** One counter stood for SIX, and they disagree about what the 372 frames MEAN |
| ZERO-REBUILD cumulative **372 of 1950**, `pass-never-ran 0`, SIMDIV=1 | a real finding, measured, not sampled | — |
| `bgLoad 'bg/bg_pete_all_p.seg'` at frame **1083**; dead block `1083–1454` (372) then `1455–1623` (169) | **372 + 169 = `299`'s "~541", confirmed to the frame.** The window starts exactly at the level's bg load | — |

**►►►► THE THREE READINGS THE `else` BRANCH CANNOT TELL APART, AND THEY ARE NOT VARIATIONS OF ONE
ANSWER:**

- **`viewer=`** — the viewmodel. `chrprop.c` item 4 says it is **already per-eye by its own path**
  (*"why the gun and the HUD survived"*). If this is the prop, **the 372 frames are BENIGN**,
  GROUP B2 is not a task at all, and `299` §8.3's pairing was a coincidence of sampling — GATE
  §7b's **third** row, `re-open it`, not its first.
- **`explosion=` / `smoke=`** — item 4's *"the next thing to extend if a run shows it matters"*
  fires. **GROUP B2 is real work and a design decision.**
- **`player=` / `nul=`** — ►► **NAMED BY NEITHER COMMENT AND EXCLUDED BY THE CODE ANYWAY.** Item 4
  and the `else` branch both say *"explosion, smoke or the viewer"*; the branch takes
  `PROP_TYPE_PLAYER` and `PROP_TYPE_NUL` as well, and anything past `PROP_TYPE_MAX`. **`PLAYER` is
  a live candidate for the single prop in a level's opening.** A comment that understates its own
  branch is the `H1`/`H3` shape exactly — a filed description read instead of the code.

**THE EDIT IS ALREADY WRITTEN AND GATED OFFLINE.** Three tracked files, no third-party, **no
regen**:

| file | repo | what changed |
|---|---|---|
| `src/game/ge_rebuild_window.h` | `vendor/ge-decomp` | six buckets + `tot_typ[]`; **`type` is now COMPUTED from them and is no longer a counter of its own** |
| `src/game/chrprop.c` | `vendor/ge-decomp` | `geSkipTypeBucket()`, the per-frame array, both print lines, and the GATE prose |
| `getv/tools/ge_rebuild_window_harness.c` | `goldeneye-native` | CASE 4 extended, **CASE 6 (the sum invariant) and CASE 7 (reset vs cumulative) are new** |

**►► `type` IS COMPUTED, NOT ACCUMULATED, AND THAT IS THE POINT.** A split that can disagree with
its own total is worse than no split. `geRebuildWindowFrame()` sums the buckets into `w->type`;
there is no second increment anywhere that could drift. CASE 6 is the falsifier (rule `15`).

---

## §1 — THE OFFLINE GATES, ON THE MAIN PC. **BEFORE ANYTHING ELSE.**

**All ten passed on the bridge 2026-09-03 with this edit in the tree.** Re-run them where the
build happens; a gate that passes on one machine and not the other is the finding.

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

**GATE §1 — ten `VERDICT PASS`. `RUN-SHEET-301` §1 states all ten in full and none of the other
eight changed; read it for those. The two this edit moves:**

1. **`ge_rebuild_window_harness` must report `30 checks, 0 failed`** — **`301` §1's gate line
   was `18`**, and this edit adds twelve: two in CASE 4, six in the new CASE 6 (the sum
   invariant) and four in the new CASE 7 (reset vs cumulative). **If it still says 18 the tree is
   stale and you are about to build the old census.** CASE 1 must still print **`six green spot
   checks, 363 failing frames`** — that line is `H2` stated as a number and it did not change.
2. **`stereo_harness`'s real-header gate must read `src/game/chrprop.c PASS 0 errors`.** That
   gate parses `chrprop.c` with `build_windows.ps1`'s **game** flags. It uses `-w`, so it catches
   errors and not warnings — the printf argument counts were checked separately offline
   (16 and 25, both exact) because `osSyncPrintf` carries no format attribute and **`-Wformat`
   cannot see these two calls at all.**

---

## §2 — THE BUILD. **AND READ THIS LINE BEFORE REACHING FOR THE REGEN.**

**►►►► THERE IS NO REGEN STEP IN `302`, AND THAT IS DELIBERATE, NOT AN OMISSION.** All three
edited files are TRACKED. **No file under the fifteen third-party ones was touched**, and
`tools/fetch-thirdparty.sh verify` already reads `15/15 files match pristine + patch` with this
edit in the tree. Running `regen` here would be harmless but it would also be the first time the
patch is regenerated over sources nobody changed — **verify, do not regen.**

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
& 'C:\Program Files\Git\bin\bash.exe' tools/fetch-thirdparty.sh verify 2>&1 | Select-Object -Last 2
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv
.\build_windows.ps1 *> ..\..\build_302_skipsplit.log
Get-Content ..\..\build_302_skipsplit.log | Select-Object -Last 12
```

**GATE §2 — `verify` reads `15/15`, then `windows binary: ... goldeneye.exe`.** `build_windows.ps1`
lives in `getv\`, **not** the repository root, and the binary lands in `getv\build-windows\`. A
`Set-Location` to the wrong one fails silently into whatever directory the prompt was in.

**IF §2 FAILS IT IS ALMOST CERTAINLY `chrprop.c`, AND READ THE FIRST ERROR, NOT THE LAST.** It is
the only game file this session edits and it gained two long `osSyncPrintf` calls.

### 2c — **RECORD THE BINARY'S IDENTITY. EVERY ARM BELOW GATES ON THIS FILE.**

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
"$((Get-FileHash .\goldeneye.exe -Algorithm SHA256).Hash) $((Get-Item .\goldeneye.exe).Length)" |
  Set-Content .\EXPECTED-EXE-302.txt
Get-Content .\EXPECTED-EXE-302.txt
```

**The `301` binary was `7058E950...D5B6 18067594`. A `302` binary that matches it is the `301`
binary and the edit did not take — that is a FAILURE, not a reassurance.**

---

## §3 — S3. **THE SPLIT, ON THE SAME FRAMES `301` §7 ALREADY MEASURED.**

**Identical environment to `RUN-SHEET-301` §7 except the arm name.** That is the point: `301`
S2's four population states are the control, and any state that moves means something other than
the census changed.

**Press F9 six times in the first five seconds, while the level is still opening.** `301` S2's
grabs landed at frames `1152–1268`, inside the dead block — repeat that.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
if (-not (Test-Path .\EXPECTED-EXE-302.txt)) { throw "EXPECTED-EXE-302.txt is missing -- run RUN-SHEET-302 section 2c after the build, before any arm." }
$want = (Get-Content .\EXPECTED-EXE-302.txt).Trim()
$got  = "$((Get-FileHash .\goldeneye.exe -Algorithm SHA256).Hash) $((Get-Item .\goldeneye.exe).Length)"
if ($want -ne $got) { throw "BINARY MISMATCH -- this is NOT the 302 build. want [$want] got [$got]" }
if (Test-Path .\run_302_S3_skipbuckets.log) { throw "run_302_S3_skipbuckets.log EXISTS -- rename it or pick a new name. A re-run would destroy the arm's provenance (H5)." }
Get-ChildItem .\dlgrab_*.txt,.\dlgrab_*.bmp -ErrorAction SilentlyContinue | Measure-Object | Select-Object -ExpandProperty Count
$env:GETV_ARM                   = "S3"
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
.\goldeneye.exe *> run_302_S3_skipbuckets.log 2>&1
Select-String -Path run_302_S3_skipbuckets.log -Pattern 'getv\]\[run\] ARM='
Select-String -Path run_302_S3_skipbuckets.log -Pattern 'GETV_STEREO_REBUILD_REPORT='
Select-String -Path run_302_S3_skipbuckets.log -Pattern 'dlgrab_|getv\]\[shot\]'
Select-String -Path run_302_S3_skipbuckets.log -Pattern 'rebuild\] WINDOW' | Select-Object -Last 3
Select-String -Path run_302_S3_skipbuckets.log -Pattern 'EXCEPTION|game_exit requested'
New-Item -ItemType Directory -Force -Path .\grabs_302_S3 | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_302_S3 -Force -ErrorAction SilentlyContinue
Get-ChildItem .\grabs_302_S3 | Select-Object Name, Length, LastWriteTime
```

**THE CHEAP READ, AFTER THE RUN — the four population states and the buckets, in two lines:**

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Select-String -Path run_302_S3_skipbuckets.log -Pattern 'SUMMARY frames=' -AllMatches |
  ForEach-Object { if ($_.Line -match 'chr=(\d+) obj=(\d+) skipped=(\d+) \(flag=(\d+) type=(\d+): nul=(\d+) viewer=(\d+) explosion=(\d+) smoke=(\d+) player=(\d+) other=(\d+)\)') { $Matches[0] } } |
  Group-Object | Sort-Object Count -Descending | Select-Object Count, Name
Select-String -Path run_302_S3_skipbuckets.log -Pattern 'rebuild\] WINDOW' | Select-Object -Last 1
```

### GATE §3a — **THE CONTROL. `301` S2's SHAPE MUST COME BACK.**

| frames | zsnap | chr | obj | skipped |
|---|---|---|---|---|
| pre-level | 11 | 2 | 9 | 0 |
| **the dead block (372 in `301`)** | 1 | **0** | **0** | **1** |
| **the 169** | 2 | 1 | 0 | **1** |
| gameplay | 1 | 1 | 0 | 0 |

**Counts will not match to the frame — F9 timing and how long you stand there are yours — but the
FOUR STATES and their order must.** A fifth state, or a dead block that has moved off the
`bgLoad`, means something other than the census changed and **nothing below is readable.**

### GATE §3b — **THE SUM. READ IT BEFORE THE BUCKETS.**

**`type=` must equal `nul + viewer + explosion + smoke + player + other` on every line.** It is
computed from them in `geRebuildWindowFrame()`, so a mismatch is not a miscount — it is a build
that does not contain this edit. **Check it once, on any line, then stop checking it.**

### ►►►► GATE §3c — **THE ANSWER. WHICH BUCKET IS NON-ZERO ON THE DEAD FRAMES.**

| the dead block reads | reading | where the work goes |
|---|---|---|
| **`viewer=`** | **The 372 frames are BENIGN.** Item 4 is right: the viewmodel is already per-eye, so the second eye was not owed a rebuild it did not get. **`299` §8.3's pairing was a coincidence of sampling** | **B2 IS NOT A TASK.** GATE §7b's third row fires — **re-open the dead eye somewhere else**, starting from `299` §8.2's grabs and NOT from this counter |
| **`explosion=` or `smoke=`** | Item 4's own *"the next thing to extend if a run shows it matters"* has fired | **B2 IS REAL.** A design decision: extend the rebuild to those types, or prove they cannot matter. **Not a patch** |
| **`player=`** | ►► **The branch excludes a type NEITHER comment names**, and it is the player's own prop in the level's opening. **The prose was wrong about what the code does** | **New. Rank it above B2** — and fix item 4's sentence in the same commit, because the next reader will believe it too |
| **`nul=`** | A list entry that should not be on the onscreen list at all | **Not a rebuild fault. It points at `chrai`'s list build**, not at this pass |
| **`other=`** | `PROP_TYPE_MAX` grew and this pass was not told | Fix the map in `geSkipTypeBucket()` first; nothing else is readable |
| **two or more non-zero** | The dead block is not one prop repeated. **Read the SUMMARY lines individually before concluding** — the WINDOW line sums a window and the split can hide a mixture the per-frame line would show | — |

**NOT WORTH DOING IF:** you read the WINDOW line's cumulative buckets and skip §3a. **A bucket
count from a run whose population states do not match `301` S2 is a number about a different
situation.**

---

## §4 — D3. **THE HALF OF `301` §5 THAT WAS NEVER READ.**

**`301` §5's verdict is in: D1 artefact GONE, D2 artefact PRESENT — `[REPORTED]`, the owner's
eyes. `gfx_pc.c:3733` was right and `299` §8.1 closes.** The census agreed on both arms and the
SCENE pair normalises to `341` vs `340` straddle per Mvtx, so the two arms stood in the same
place.

**WHAT WAS NEVER READ IS THE PRICE.** `GL_DEPTH_CLAMP` disables z clipping at **BOTH** planes, so
geometry that used to be clipped at the FAR plane now rasterises clamped to maximum depth.
`298` §4.4's `all_near` number was offered as that price and is **RETRACTED** (`00-STATE` §4) — it
measures where you stood, not what the clamp cost. **Nothing has replaced it, and the only
instrument for this one is the owner's eyes on a long sight line.**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
$want = (Get-Content .\EXPECTED-EXE-302.txt).Trim()
$got  = "$((Get-FileHash .\goldeneye.exe -Algorithm SHA256).Hash) $((Get-Item .\goldeneye.exe).Length)"
if ($want -ne $got) { throw "BINARY MISMATCH -- this is NOT the 302 build. want [$want] got [$got]" }
if (Test-Path .\run_302_D3_farfield.log) { throw "run_302_D3_farfield.log EXISTS -- rename it or pick a new name (H5)." }
$env:GETV_ARM         = "D3"
$env:GETV_SLOTFREE    = "1"
$env:GETV_VSYNC       = "1"
$env:GETV_FPS         = "panel"
$env:GETV_WIDESCREEN  = "0"
$env:GETV_ROOMSCISSOR = "1"
$env:GETV_WINDOW      = "2560x1369"
$env:GETV_STAGE       = "29"
$env:GETV_DIFFICULTY  = "0"
$env:GETV_DEPTHCLAMP  = "1"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_302_D3_farfield.log 2>&1
Select-String -Path run_302_D3_farfield.log -Pattern 'getv\]\[run\] ARM='
Select-String -Path run_302_D3_farfield.log -Pattern 'getv\]\[depthclamp\]'
Select-String -Path run_302_D3_farfield.log -Pattern '\[getv\]\[far\]' | Select-Object -Last 1
Select-String -Path run_302_D3_farfield.log -Pattern 'EXCEPTION|game_exit requested'
```

**WALK TO THE LONGEST SIGHT LINE THE LEVEL HAS AND LOOK DOWN IT.** Then say, in one sentence
each:

1. **Does anything appear in the distance that should not be there?** Geometry beyond the far
   plane now rasterises instead of being clipped — a wall behind a wall, a shape flickering at the
   horizon, a room bleeding through another.
2. **Does anything that used to be there stop being drawn?** That would be the opposite fault and
   it is not what the extension does — if you see it, say so anyway.
3. **Is the far field simply unchanged from what you remember?** **That is an acceptable and
   likely answer, and it is worth writing down as `[REPORTED]`** — the cost was asserted from GL
   semantics and has never been looked for.

**GATE §4 — the `[getv][far]` line's `beyond_far` count must be non-zero.** `301` D1 read
`beyond_far=319751 (0.7%)`. **If it is zero you were never pointed at anything past the far
plane, and "I saw nothing wrong" is `279` §7 — a null result from an instrument pointed at
nothing.** Walk further before answering.

---

## §5 — THE COMMITS. **TWO CODE REPOS AND THE DOCUMENTS. NO THIRD REPO STEP FOR THE PATCH.**

**Run §5 whenever it suits — the edit is gated offline and does not depend on the arms.**
Committing before the run means a failed arm is a `git diff` against a known tree rather than
against a guess.

### 5.1 — `vendor/ge-decomp`. **STAGE BY EXPLICIT PATH LIST, NEVER `git add -A`.**

A bare `git status` here prints **2,106 CRLF-dirty files** (`00-STATE` §6).

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\vendor\ge-decomp
git --no-optional-locks status --short -- src/game/chrprop.c src/game/ge_rebuild_window.h
git diff --ignore-cr-at-eol -- src/game/chrprop.c src/game/ge_rebuild_window.h | Select-Object -First 60
git add src/game/chrprop.c src/game/ge_rebuild_window.h
git commit -F ..\..\..\COMMIT-MESSAGE-2026-09-03c-decomp.txt
git log --oneline -1
```

### 5.2 — `goldeneye-native`. **THE HARNESS ONLY. NO PATCH REGEN.**

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
& 'C:\Program Files\Git\bin\bash.exe' tools/fetch-thirdparty.sh verify 2>&1 | Select-Object -Last 1
git --no-optional-locks status --short -- getv/
git add getv/tools/ge_rebuild_window_harness.c
git commit -F ..\COMMIT-MESSAGE-2026-09-03c-native.txt
git log --oneline -1
```

**GATE 5.2 — `verify` must read `15/15` BEFORE the commit.** If it does not, a third-party file
was touched after all and the patch is owed. **Nothing in `302` should have touched one.**

### 5.3 — `GoldenEyeVR`. The documents.

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR
git --no-optional-locks status --short -- repo/docs
git add repo/docs
git commit -F .\COMMIT-MESSAGE-2026-09-03c.txt
git log --oneline -1
```

### 5.4 — THE THREE-REPO CHECK, AFTER ALL THREE

```powershell
foreach ($p in @('F:\Projects\GEVR\GoldenEyeVR',
                 'F:\Projects\GEVR\GoldenEyeVR\goldeneye-native',
                 'F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\vendor\ge-decomp')) {
  Set-Location $p; Write-Host "==== $p"; git log --oneline -1
}
```

**No attribution trailers in any of these messages** — no `Co-Authored-By`, no session URL, no
tool footer.

---

## §6 — AFTER `302`

**`302` §3c decides where GROUP B goes and there is no point guessing which branch first.** Once
it reads:

- **GROUP C**, the `NaN` — `HIGH`, precondition none, and **untouched since `299` §8.4** wrote it
  down (`already-converted=11902` of `144716`, every hit `eye=1`, most `m[0][0]=nan`). It does not
  wait on `302` and it is the largest unexamined thing on the board.
- **`H4`'s banners** — `MEDIUM`, and `knob_banner_survey.py --used-in repo/docs` ranks the 324
  silent knobs. **Work down that list; do not sweep.** Expect at least one to be filed wrong.
- **GROUP D** — unblocked, `D1` is `LOW`.
- **`H9`** — `HIGH`, still held. Every visual verdict in `298`, `299`, `301` and now `302` §4 is
  `[REPORTED]`. **It needs a known-good reference frame the project does not have. Name it as
  accepted, or build it deliberately — but not at the end of a session.**
