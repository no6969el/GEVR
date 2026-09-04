# RUN-SHEET-299 — THE A→B→A, THE EYE-DEATH FALSIFIER, AND R3/R4/R5 SPLICED IN FULL

**Written OFFLINE, 2026-09-03. NOTHING BUILT, NOTHING RUN, NO SOURCE FILE CHANGED.**
`HEAD` = `3de0db0` (GoldenEyeVR), `e380916` (goldeneye-native), `1f0f7aae` (vendor/ge-decomp);
all three trees clean under `git --no-optional-locks status`. **`goldeneye.exe` is
`2026-09-02 19:29`, 18,058,803 bytes — `297`'s ARM 3 fix3 build. EVERY BLOCK BELOW RUNS AGAINST
THAT BINARY. NOTHING HERE NEEDS A BUILD.**

**►►►► DEFECT 1 OF `RUN-SHEET-295` §11 IS HONOURED HERE: NOTHING ON THIS SHEET DELEGATES.**
`297` §8 said R4's block *"will be spliced in FULL rather than delegated once R2 passes"*. R2
passed, so §4 below is that splice. §5 is R5's, spliced for the same reason. **A block the owner
has to assemble from two documents is not a supplied command.**

---

## §0 — THE ORDER, AND WHY IT IS THIS ORDER

| § | arm | what it settles | build? |
|---|---|---|---|
| **§1** | **N1 → N2 → N3** | **`GETV_NEARCLAMP` A→B→A. The owner's #1 symptom, bug 2 of 2.** `298` §4.5 | no |
| **§2** | **E1** | **NEW. `299` §2: ARM 3 is green on one frame and DEAD on another in the same build.** | no |
| **§2b** | **E2** | **NEW. `299` §3: every saturated matrix in the set is in the dead eye. `GETV_STEREO_MTXGUARD=1`, observe only.** | no |
| §3 | R3 | pairguard with ARM 3 on. `RUN-SHEET-297` §7, quoted verbatim | no |
| §4 | R4 | **S3, the separation gate. SPLICED IN FULL.** `RUN-SHEET-297` §8 | no |
| §5 | R5a/b/c | ARM 3's cost. `P5`. **SPLICED IN FULL.** `RUN-SHEET-297` §9 | no |
| §6 | C2 | arm C's gate: *"the gun disappears on the floor."* Three arms, never exercised | no |

**§1 IS FIRST BECAUSE `NEXT-SESSION-PROMPT-299` SAYS SO AND IT IS THE CHEAPEST RUN IN THE QUEUE.**

**§2 IS SECOND, AND IT IS NEW THIS SESSION, BECAUSE §4's GATE CANNOT BE SCORED UNTIL IT RUNS.**
`299` §2 `[MEASURED]`: `dlgrab_1346` — **the only R2 grab with admissible provenance that has a
world in it** — shows ONE EYE WITH NO WORLD AT ALL, per-half texture energy **0.038 vs 4.685, a
123.7x ratio, WORSE than R1's 8.7x**, in a run whose banner reads `ARM 3 per-eye render rebuild ON`
and whose SUMMARY reads `eyes-rebuilt=1 enabled=1`. **R4 measures a disparity between two halves.
If one half can be dead on the grabbed frame, R4's number is a number about nothing** — which is
`297` §0's blank-frame trap in a new place, and `279` §7's rule for the fourth time.

---

## §1 — N1 → N2 → N3. **`GETV_NEARCLAMP` A → B → A. THE FIRST THING THIS SESSION RUNS.**

**Stage 29, mono, shipping culling, the SAME ALLEY arms B and D were grabbed in.**
One behaviour change between the arms and it is `GETV_NEARCLAMP` (`48`).

### 1.0 — READ THIS BEFORE THE FIRST BLOCK: THE KNOB HAS NO BANNER, AND THAT IS FINE

`00-STATE` §6's newest trap says **check the banner, never the `$env:` line.** `[MEASURED]`
offline, `299` §5: **`GETV_NEARCLAMP` HAS NO BANNER.** It has exactly one read site
(`gfx_pc.c:3743`, `getenv` latched into a function-static) and **it is not a key in
`ge_config.c` at all**, so — unlike `GETV_FILTERING` — the per-user cfg cannot shadow it and the
environment is its only source. **Its observable is the `[getv][far]` census, and the census is
STRICTER than a banner because it reports behaviour rather than resolution:**

| | `NEAR all_near` | `NEAR straddle` | `NEAR clamped` | reading |
|---|---|---|---|---|
| clamp **ON** | `a` | `s` | **`s + a`** | every straddling triangle clamped, plus every all-near one |
| clamp **OFF** | `a` | `s` | **`0`** | condition crossed, knob provably off |

**`[MEASURED]` on last session's own logs, and the identity holds to the unit:**
arm E `22635 + 50 = 22685` ✓ · arm D `23540 + 54 = 23594` ✓ · arm F `clamped = 0` with
`straddle = 18439` ✓. **If `clamped != straddle + all_near` in N1 or N3, the census accounting is
wrong and NOTHING on this sheet is scoreable — stop and say so.**

### 1.1 — N1. **ARM A. CLAMP ON (the shipping default, stated explicitly).**

Walk to the alley. Stand at the corner where the wall cut shows. **Do not move between grabs.**
**Press F9 three times, a second or so apart.** Then quit the game normally (`game_exit`).

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
$env:GETV_NEARCLAMP   = "1"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_299_N1_nearclamp_on_A.log 2>&1
Select-String -Path run_299_N1_nearclamp_on_A.log -Pattern 'GETV_FPS=panel'
Select-String -Path run_299_N1_nearclamp_on_A.log -Pattern 'GETV_SLOTFREE resolved|GETV_STAGE override'
Select-String -Path run_299_N1_nearclamp_on_A.log -Pattern 'roomscissor\]|proproomtest\]|getv\]\[stereo\]'
Select-String -Path run_299_N1_nearclamp_on_A.log -Pattern 'dlgrab_|getv\]\[shot\]'
Select-String -Path run_299_N1_nearclamp_on_A.log -Pattern 'EXCEPTION|game_exit requested'
Select-String -Path run_299_N1_nearclamp_on_A.log -Pattern '\[getv\]\[far\]' | Select-Object -Last 1
New-Item -ItemType Directory -Force -Path .\grabs_299_N1 | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_299_N1 -Force -ErrorAction SilentlyContinue
Get-ChildItem .\grabs_299_N1 | Select-Object Name, Length, LastWriteTime
```

### 1.2 — N2. **ARM B. CLAMP OFF. ONE BEHAVIOUR CHANGE.**

**Same alley, same corner, same three F9 presses.**

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
$env:GETV_NEARCLAMP   = "0"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_299_N2_nearclamp_off_B.log 2>&1
Select-String -Path run_299_N2_nearclamp_off_B.log -Pattern 'GETV_FPS=panel'
Select-String -Path run_299_N2_nearclamp_off_B.log -Pattern 'GETV_SLOTFREE resolved|GETV_STAGE override'
Select-String -Path run_299_N2_nearclamp_off_B.log -Pattern 'roomscissor\]|proproomtest\]|getv\]\[stereo\]'
Select-String -Path run_299_N2_nearclamp_off_B.log -Pattern 'dlgrab_|getv\]\[shot\]'
Select-String -Path run_299_N2_nearclamp_off_B.log -Pattern 'EXCEPTION|game_exit requested'
Select-String -Path run_299_N2_nearclamp_off_B.log -Pattern '\[getv\]\[far\]' | Select-Object -Last 1
New-Item -ItemType Directory -Force -Path .\grabs_299_N2 | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_299_N2 -Force -ErrorAction SilentlyContinue
Get-ChildItem .\grabs_299_N2 | Select-Object Name, Length, LastWriteTime
```

### 1.3 — N3. **ARM A AGAIN. THE RETURN LEG, AND IT IS THE WHOLE POINT.**

**Identical to N1 except the log and grab names.** A→B is a negative; **A→B→A is a cause.**

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
$env:GETV_NEARCLAMP   = "1"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_299_N3_nearclamp_on_A2.log 2>&1
Select-String -Path run_299_N3_nearclamp_on_A2.log -Pattern 'GETV_FPS=panel'
Select-String -Path run_299_N3_nearclamp_on_A2.log -Pattern 'GETV_SLOTFREE resolved|GETV_STAGE override'
Select-String -Path run_299_N3_nearclamp_on_A2.log -Pattern 'roomscissor\]|proproomtest\]|getv\]\[stereo\]'
Select-String -Path run_299_N3_nearclamp_on_A2.log -Pattern 'dlgrab_|getv\]\[shot\]'
Select-String -Path run_299_N3_nearclamp_on_A2.log -Pattern 'EXCEPTION|game_exit requested'
Select-String -Path run_299_N3_nearclamp_on_A2.log -Pattern '\[getv\]\[far\]' | Select-Object -Last 1
New-Item -ItemType Directory -Force -Path .\grabs_299_N3 | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_299_N3 -Force -ErrorAction SilentlyContinue
Get-ChildItem .\grabs_299_N3 | Select-Object Name, Length, LastWriteTime
```

### 1.4 — GATES, AND WHAT EACH FAILURE MEANS

**GATES COMMON TO ALL THREE ARMS — every one of these is in the block above:**

1. `Get-Item` reads **`2026-09-02 19:29`, `18058803`**. A different binary voids the set (`133`).
2. The loose-grab count printed before the run is **`0`**. If not, the `Move-Item` at the end will
   sweep another arm's dumps into this arm's folder (`298` §6).
3. `GETV_FPS=panel -> 180 Hz, QUERIED FROM SDL` present (`295` §11 defect 4).
4. `[getv][slot] GETV_SLOTFREE resolved to 1 (env=1)` and `GETV_STAGE override: booting stage 29`.
5. **NO `[getv][roomscissor]` line and NO `[getv][proproomtest]` line** — both banners fire only
   at `=0`, so their ABSENCE is the proof that culling is at shipping defaults. This is arm D's own
   verification and it is why the wall cut is in `00-STATE` §3 rather than in §6 (`298` §3).
6. **NO `[getv][stereo]` line.** These are mono arms (rule `48`).
7. **THREE `[getv][dlgrab] frame N ->` lines and THREE `[getv][shot]` lines.**
   **THIS IS THE GATE ARM F FAILED**, and it is the entire reason this sheet exists.
8. No `EXCEPTION`; ends `game_exit requested`.

**THE CENSUS GATE, from the last `[getv][far]` line of each arm:**

| arm | required | if it reads otherwise |
|---|---|---|
| N1 | `clamped = straddle + all_near`, `straddle` in the **thousands** | `clamped=0` means the knob took the wrong way round — the arms are swapped |
| N2 | **`clamped = 0`** AND `straddle` in the **thousands** | `straddle` small = the near plane was never crossed: **the arm is VOID, not a negative** (`279` §7, `298` §4.2) |
| N3 | `clamped = straddle + all_near`, `straddle` in the **thousands** | as N1 |

**THE ARTEFACT GATE — the owner's eyes, and this is the measurement (`HANDOVER` §5):**

| N1 | N2 | N3 | verdict |
|---|---|---|---|
| present | **absent** | **present** | **`[MEASURED]` CAUSE.** The near-plane clamp is bug 2 of 2. `298` §4 is upgraded from `[REPORTED]`+census. |
| present | present | present | `298` §8 falsifier 1 FIRED. **The clamp is not the mechanism and §4 is dead.** Say so and stop. |
| absent | absent | absent | **VOID.** The corner was not reached. Re-run; do not score it. |
| present | absent | **absent** | **VOID and interesting** — the artefact did not come back, so something other than the knob changed between arms. Do not call it either way. |

**►► `GETV_NEARCLAMP=0` IS NOT THE FIX AND MUST NOT SHIP** even if N2 is clean. Without the clamp
GL discards every triangle poking through the near plane; F's own census showed the price starting,
`all_near` **50 → 548**. Compare N1's and N2's `all_near` and **record the ratio** — it is free and
it is the cost of the wrong fix, measured. The right fix is `GL_DEPTH_CLAMP` in `gfx_opengl.c`
(`gfx_pc.c:3734` names it; `[MEASURED]` it is referenced in comments twice and implemented
nowhere), and **it is a build and it is not this sheet's.**

---

## §2 — E1. **THE EYE-DEATH FALSIFIER. NEW, AND IT OUTRANKS R3/R4/R5.**

**WHY THIS ARM EXISTS.** `299` §2, all offline, all reproducible from files already on disk:

- `dlgrab_2568` and `dlgrab_3056` (ARM 3 ON): both eyes carry the same world. Every DL counter
  equal, `only in eye0 = 0`, per-half energy **3.574 / 3.616**. **The picture confirms it — two
  soldiers, the street, the gun, in both halves.**
- `dlgrab_1192` and `dlgrab_1346` — **the ONLY two R2 grabs announced by the surviving
  `run_297_R2_rebuild_on.log`, same build, same knobs** — do not. `1346` has **one half with no
  world at all**: per-half energy **0.038 / 4.685 = 123.7x**, against R1's 8.7x. Its dead half's
  DL section carries a `MODELVIEW LOAD` at `seq=000273` with **every entry `±32768`** —
  `292` §5a's saturated-matrix signature, in an ARM 3 build.
- `1192`/`1346` have **no HUD and no viewmodel** (`texrect 0/0`, against `100/100` in `2451` and
  `2568`), so they are a DIFFERENT FRAME CLASS — cutscene or intro camera — and that class was
  never scored, because `298` §1.2 scored only the four grabs from the run whose log was destroyed.

**THE QUESTION THIS ARM ANSWERS, AND IT IS ONE OF THREE:** is the dead eye **(a)** alternating
frame to frame, **(b)** confined to the no-HUD frame class, or **(c)** an artefact of the one short
re-run? **`GETV_STEREO_REBUILD_REPORT=1` IS THE INSTRUMENT AND IT NEEDS NO BUILD.** `299` §4
`[MEASURED]` from source: `gePropsSnapshotTickZDepth()` resets the counters **on every tick**, so
the SUMMARY prints **the counters of ONE frame**, not of the window. **At `=600` it is a spot check;
at `=1` it is a census.** `298` §1.1's six rows are six spot checks.

**RUN IT LIKE THIS:** stage 29, ARM 3 on, zero separation. Walk into the alley, **stand still**,
and press **F9 six times as fast as you can**. Then walk on until a cutscene/no-HUD moment appears
if one does, press F9 three more times, and quit.

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
.\goldeneye.exe *> run_299_E1_percensus.log 2>&1
Select-String -Path run_299_E1_percensus.log -Pattern 'GETV_FPS=panel'
Select-String -Path run_299_E1_percensus.log -Pattern 'getv\]\[stereo\] ON|ARM 1 view-pair|ARM 3 per-eye|pools scaled'
Select-String -Path run_299_E1_percensus.log -Pattern 'dlgrab_|getv\]\[shot\]'
Select-String -Path run_299_E1_percensus.log -Pattern 'EXCEPTION|game_exit requested'
Select-String -Path run_299_E1_percensus.log -Pattern 'rebuild\] SUMMARY' | Measure-Object | Select-Object -ExpandProperty Count
Select-String -Path run_299_E1_percensus.log -Pattern 'rebuild\] SUMMARY' | Select-Object -First 5
Select-String -Path run_299_E1_percensus.log -Pattern 'rebuild\] SUMMARY' | Select-Object -Last 5
New-Item -ItemType Directory -Force -Path .\grabs_299_E1 | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_299_E1 -Force -ErrorAction SilentlyContinue
Get-ChildItem .\grabs_299_E1 | Select-Object Name, Length, LastWriteTime
```

**GATE E1 — and the counting is the point:**

1. All four ARM 3 banners present: `[getv][stereo] ON ... separation=0.000`, `ARM 1 view-pair
   restore ON`, `ARM 3 per-eye render rebuild ON`, `pools scaled x2 ... gfx=245760 vtx=81920`.
2. **The SUMMARY count is ~one per rendered frame** (thousands, not six). If it is six, `=1` did
   not take and the arm is void.
3. **Nine or more `[getv][dlgrab]` + `[getv][shot]` pairs.**
4. No `EXCEPTION`; ends `game_exit requested`.

**THEN, OFFLINE — no build, no run, and it is the whole verdict.** For every grab:

```
py F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\tools\dlgrab_eyecensus.py F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows\grabs_299_E1\dlgrab_<N>.txt
py F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\tools\stereo_disparity.py F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows\grabs_299_E1\dlgrab_<N>.bmp
```

**and for each grab pull its OWN frame's line out of the log:**

```powershell
Select-String -Path run_299_E1_percensus.log -Pattern 'rebuild\] SUMMARY' -Context 0,0 |
  Where-Object { $_.Line -match 'frames=(\d+)' -and [int]$Matches[1] -in @(<the grabbed frame numbers>) }
```

| what the six near-consecutive grabs show | reading |
|---|---|
| all six equal-eyed (`only in eye0 = 0`) | **(b) or (c).** The dead eye is not per-frame. Then chase the no-HUD class. |
| they **alternate** good / dead | **(a). ARM 3 rebuilds on some frames and not others**, and the owner's *"if I move any little bit, it goes down or goes away"* has a second candidate mechanism. **This would be the finding of the session.** |
| all six dead | ARM 3 is not working in this run at all, and `2568` is the outlier. Re-check the four banners before believing it. |

**►► STATED IN ADVANCE (rule `15`): IF THE SIX GRABS ARE ALL EQUAL-EYED AND EVERY SUMMARY LINE
READS `eyes-rebuilt=1` WITH `chr+obj` TRACKING `list`, THEN `299` §2 IS A FRAME-CLASS FINDING ONLY
AND `298`'s "ARM 3 IS GREEN" STANDS WITH A NAMED EXCEPTION** — not retracted, narrowed.

---

## §2b — E2. **THE SATURATED-MATRIX ARM. ONE BEHAVIOUR CHANGE FROM E1, AND IT HAS A PRE-REGISTERED NULL.**

**WHY.** `299` §3 `[MEASURED]`, counting MTX commands whose entries sit at ±32768 in each eye's own
DL section:

| dump | arm | MTX eye0 / eye1 | **SATURATED eye0 / eye1** |
|---|---|---|---|
| `2451` | R1 `REBUILD=0` | 204 / 94 | **0 / 0** |
| `2568` | R2 `REBUILD=1`, both eyes good | 223 / 223 | **0 / 0** |
| `1192` | R2 `REBUILD=1`, eye dead | 73 / 14 | **2 / 0** |
| `1346` | R2 `REBUILD=1`, eye dead | 73 / 14 | **5 / 0** |

**Every saturated matrix in the set is in EYE 0, and they appear ONLY in the two frames with the
dead eye.** `292`'s own comment calls this *"the green wedge across the left eye"* and eye 0 is the
left eye — so the mechanism `292` named is **present in the ARM 3 build**, in the frames that fail
and in none of the frames that pass.

**Same spot, same six F9 presses as E1. One knob different (`48`): `GETV_STEREO_MTXGUARD=1`.**
**MODE 1 OBSERVES AND CHANGES NOTHING THAT DRAWS.** Do **not** use mode 2 — `292` marks it a
falsifier that must never ship.

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
$env:GETV_STEREO_MTXGUARD       = "1"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_299_E2_mtxguard_observe.log 2>&1
Select-String -Path run_299_E2_mtxguard_observe.log -Pattern 'GETV_FPS=panel'
Select-String -Path run_299_E2_mtxguard_observe.log -Pattern 'mtxguard\]'
Select-String -Path run_299_E2_mtxguard_observe.log -Pattern 'dlgrab_|getv\]\[shot\]'
Select-String -Path run_299_E2_mtxguard_observe.log -Pattern 'EXCEPTION|game_exit requested'
New-Item -ItemType Directory -Force -Path .\grabs_299_E2 | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_299_E2 -Force -ErrorAction SilentlyContinue
Get-ChildItem .\grabs_299_E2 | Select-Object Name, Length, LastWriteTime
```

**GATE E2, and the null is the knob's own, printed by the knob itself:**

- The banner `[getv][mtxguard] GETV_STEREO_MTXGUARD=1 -- ... MODE 1 observes only` must appear. No
  banner, no arm.
- At exit: `[getv][mtxguard] arrays=N already-converted=M skipped=0`.
- **`already-converted > 0` → the double conversion is live in the ARM 3 build.** Then
  `bondviewTransformManyPosToViewMatrix`'s ownership question — `292`'s *"a design decision about
  who owns `render_pos` per eye"* — is what ARM 3 left unfinished, and that is the next build.
- **`already-converted = 0` → the knob's own printed sentence applies: *"the saturated matrix came
  from somewhere else and this diagnosis is WRONG -- do not keep it."*** Then §3's saturation count
  stands as an observation and its attribution to this function is dead. **Stated in advance.**

---

## §3 — R3. **THE PAIRING GUARD WITH ARM 3 ON.** `RUN-SHEET-297` §7, QUOTED VERBATIM.

> Same block as §6 with `$env:GETV_STEREO_PAIRGUARD = "600"`.

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
$env:GETV_STEREO_VIEWRESTORE    = "1"
$env:GETV_STEREO_PAIRGUARD      = "600"
$env:GETV_STEREO_REBUILD        = "1"
$env:GETV_STEREO_REBUILD_REPORT = "600"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_297_R3_guard_rebuild.log 2>&1
Select-String -Path run_297_R3_guard_rebuild.log -Pattern 'pairguard\] SUMMARY|pairguard\] MISMATCH|rebuild\] SUMMARY|game_exit requested'
```

**ADDED BY `299`, NOT PART OF THE QUOTED BLOCK — run these two afterwards** (`295` §11 defect 4:
no block on that sheet grepped the one knob resolved at runtime):

```powershell
Select-String -Path run_297_R3_guard_rebuild.log -Pattern 'GETV_FPS=panel'
Select-String -Path run_297_R3_guard_rebuild.log -Pattern 'EXCEPTION'
```

**GATE R3: `checks > 0` AND `mismatch = 0` in every window.**

> **►► AND READ THE NEXT SENTENCE BEFORE CELEBRATING IT.** With ARM 3 on, the arena's owner is the
> LAST eye by construction, so **this zero is not evidence that ARM 1 works — it is evidence that
> the fault can no longer occur.** That is why ARM 2 had to be worn on a build without ARM 3
> (`295` §5), and it is already done: `295` §10. **A non-zero `mismatch` here would be the
> interesting result** — it would mean something is reading a pair the rebuild did not reinstall,
> and that is a new class.

**►► `299` ADDS ONE MORE READING OF ITS ZERO.** `299` §4: `REBUILD_REPORT=600` prints one frame in
600. **If §2 shows the rebuild is intermittent, R3's zero is also consistent with "the guard
sampled a rebuilt frame."** Run §2 first and R3's zero means what the sheet says it means.

---

## §4 — R4. **S3, THE SEPARATION GATE. SPLICED IN FULL. THIS IS THE OWED BLOCK.**

**ONLY IF R2 PASSED — it has (`298` §0) — AND ONLY AFTER §2 HAS SAID THE GRABBED FRAME CAN BE
TRUSTED.** `RUN-SHEET-297` §8 delegated this to `RUN-SHEET-295` §10.2 "as written, adding two
lines and changing a third". **That delegation is `RUN-SHEET-295` §11 defect 1 and it ends here.**
The block below is §10.2's, with §8's three changes applied and a new log name, so nothing has to
be assembled from two documents.

**S3 HAS NEVER RUN.** Stand still, in a room, **FACING A WALL** — the engine's ray test does not
cross portals. If the log's prediction block says **CANNOT ANSWER**, move to face a wall and
re-run; **do not substitute an assumed depth.** **A re-run gets a new log name** (`298` §6).

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
$env:GETV_STEREO_OFFSET         = "500"
$env:GETV_STEREO_MODE           = "1"
$env:GETV_STEREO_PROBE          = "60"
$env:GETV_STEREO_VIEWRESTORE    = "1"
$env:GETV_STEREO_PAIRGUARD      = "0"
$env:GETV_STEREO_REBUILD        = "1"
$env:GETV_STEREO_REBUILD_REPORT = "1"
$env:GETV_DLGRAB_AT             = "5400"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_299_R4_S3_gate.log 2>&1
Select-String -Path run_299_R4_S3_gate.log -Pattern 'GETV_FPS=panel'
Select-String -Path run_299_R4_S3_gate.log -Pattern 'getv\]\[stereo\]|dlgrab_|getv\]\[shot\]'
Select-String -Path run_299_R4_S3_gate.log -Pattern 'props interpolated|simulation held to|ours: x=|game_exit requested'
Select-String -Path run_299_R4_S3_gate.log -Pattern 'EXCEPTION'
Select-String -Path run_299_R4_S3_gate.log -Pattern 'PREDICTION frame=|MEASURED centre depth|1/D LAW' | Select-Object -Last 12
New-Item -ItemType Directory -Force -Path .\grabs_299_R4 | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_299_R4 -Force -ErrorAction SilentlyContinue
Get-ChildItem .\grabs_299_R4 | Select-Object Name, Length, LastWriteTime
```

**THREE CHANGES FROM `RUN-SHEET-295` §10.2, ALL FROM `RUN-SHEET-297` §8, NAMED SO THEY CAN BE
CHECKED:** `GETV_STEREO_REBUILD=1` and `GETV_STEREO_REBUILD_REPORT` added (§8 says `600`; **`299`
raises it to `1` because §4 below shows `600` is a spot check**), and `GETV_DLGRAB_AT` **5400,
not 900** — frame 900 at `panel` on a 180 Hz display is ~5 s and is still the level-load fade,
which is how `295`'s S2 scored a PASS on a black frame (`297` §0).

### 4.1 — **THE NEW GATE FIRST, BECAUSE IT DECIDES WHETHER THE OLD ONE MEANS ANYTHING**

`RUN-SHEET-297` §8: *"the 1/D law is measured on a frame where the characters and props are present
in BOTH eyes. A disparity measured on an eye with no world in it is a number about nothing."*
**`299` §2 makes that a mechanical check, not a judgement:**

```
py F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\tools\dlgrab_eyecensus.py F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows\grabs_299_R4\dlgrab_5400.txt
```

**GATE 4.1 — ALL FOUR, on the grabbed frame's own dump:**

1. `viewport loads = 2`.
2. **`only in eye0 = 0`** — no `<-- eye1 is a STRICT SUBSET` line at all.
3. **`MODEL_MTX(3)`, `MODEL_VTX(4)` and `MODEL_COL1(5)` all NON-ZERO in BOTH eyes**, with no
   `<-- DIVERGES` marker. At `OFFSET=500` a small delta is expected and is not a failure; a **zero
   on one side is**.
4. That frame's own `rebuild] SUMMARY` line reads `eyes-rebuilt=1` with `chr+obj > 0`.

**IF 4.1 FAILS, STOP. Do not score 4.2, and do not re-run with a different `GETV_DLGRAB_AT` until
§2 has said which frames are safe to grab.** A disparity measured across a dead eye is exactly the
blank-frame trap `297` §0 caught, one level up.

### 4.2 — THE DISPARITY MEASUREMENT, AND SWEEP THE FREE PARAMETER

Take the predicted fraction from **the log's LAST `MEASURED centre depth` block BEFORE the grab**
(stand still and every block is the same; the block prints the camera position, so a moved camera
is visible).

```
py F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\tools\stereo_disparity.py F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows\grabs_299_R4\dlgrab_5400.bmp --predicted-frac <the number from the log>
```

**THEN RUN IT THREE MORE TIMES WITH `--search 200`, `--search 500` AND `--search 800`,** all with
the same `--predicted-frac`. **`00-STATE` §6, `298` §2.1: an answer that moves with the search
width IS the search width.** `[MEASURED]` last session: R1's `dx` read `+199 / +229 / -499 / -799`
across that sweep while R2's read `+1` at every width.

**►► AND THE SCRIPT'S OWN PEG DETECTOR CANNOT SAVE YOU.** `[MEASURED]`, `298` §2.1 and re-checked
offline this session: it tests `abs(dx) >= search` while `measure()`'s `lo`/`hi` clipping
(`stereo_disparity.py:90-91`) makes the reachable bound `search - 1`, **so it has never fired and
will not fire here.** The sweep is the detector. It is a live defect in the script and it is not
fixed on this sheet.

**GATE S3 — `RUN-SHEET-292` §5's, unchanged, and the log's numbers decide it, not the picture:**
`VERDICT PASS` (`|measured - predicted| <= 5 px` **and** the sign matches — the RIGHT eye's image
FURTHER LEFT); **the D=1000 and D=4000 predictions stand in a 4.000 ratio**, read off adjacent
lines; `props interpolated 0`, zero `simulation held to`, `ours: x=367.333`, `game_exit requested`.
**`RUN-SHEET-292` §5's failure table is unchanged and still tells you what each failure means —
read it BEFORE the run, not after** (`255` §4, `70`).

**►►►► THE SIGN CONVENTION IS SETTLED FROM SOURCE, NOT FROM THE PICTURE. `299` §3.**
An earlier draft of this sheet asked the owner which half was which eye. **It is documented, in two
lines, and the question is withdrawn:**

- **`stereo.c:233`** — `*out_left = full_left + ((ge_st_eye == 0) ? 0 : half)`.
  **Eye 0 is the LEFT half of the framebuffer; eye 1 is the RIGHT half.**
- **`stereo.c:387`** — `if (ge_st_eye == 0) { half = -half; /* eye 0 is the LEFT eye */ }`.
  **Eye 0 is the LEFT EYE**, offset −sep/2 along the camera's own right vector; eye 1 is the right
  eye, +sep/2.

**So: framebuffer LEFT = eye 0 = left eye = `dlgrab_eyecensus.py`'s `eye0` column, and the
`--scissors` pairing (eye0 at `x∈[0,640]`, eye1 at `[640,1280]`, +640 apart) is correct.**
The right eye's camera sits further right, so a fixed world point projects FURTHER LEFT in the right
half — which is exactly what `stereo_disparity.py` prints as a NEGATIVE `dx`. **GATE S3's sign test
reads as written and is scored normally.**

### 4.3 — S4, THE FALSIFIER. **`RUN-SHEET-295` §10.3, SPLICED. NOT REQUIRED BY `297` §8.**

**It is here because `RUN-SHEET-295` §10.3's own last sentence is a condition on S3's pass:**
*"If S4 is indistinguishable from S3 in every respect, S3's pass must be WITHDRAWN"* (`49`).
**Same spot as R4. Same wall.** One behaviour change from §4: `GETV_STEREO_MODE=2`.

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
$env:GETV_STEREO_OFFSET         = "500"
$env:GETV_STEREO_MODE           = "2"
$env:GETV_STEREO_PROBE          = "60"
$env:GETV_STEREO_VIEWRESTORE    = "1"
$env:GETV_STEREO_PAIRGUARD      = "0"
$env:GETV_STEREO_REBUILD        = "1"
$env:GETV_STEREO_REBUILD_REPORT = "1"
$env:GETV_DLGRAB_AT             = "5400"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_299_R4b_S4_falsifier.log 2>&1
Select-String -Path run_299_R4b_S4_falsifier.log -Pattern 'GETV_FPS=panel'
Select-String -Path run_299_R4b_S4_falsifier.log -Pattern 'getv\]\[stereo\]|dlgrab_|getv\]\[shot\]'
Select-String -Path run_299_R4b_S4_falsifier.log -Pattern 'props interpolated|simulation held to|ours: x=|game_exit requested'
Select-String -Path run_299_R4b_S4_falsifier.log -Pattern 'EXCEPTION'
New-Item -ItemType Directory -Force -Path .\grabs_299_R4b | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_299_R4b -Force -ErrorAction SilentlyContinue
Get-ChildItem .\grabs_299_R4b | Select-Object Name, Length, LastWriteTime
```

**Then run the script on THIS BMP with S3's OWN predicted fraction:**

```
py F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\tools\stereo_disparity.py F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows\grabs_299_R4b\dlgrab_5400.bmp --predicted-frac <S3's number>
```

**GATE S4 — `RUN-SHEET-292` §6's, unchanged:** the banner says
**`mode=2 (PROJECTION-ONLY -- B1 REPRODUCED ON PURPOSE, FALSIFIER ONLY, MUST NEVER SHIP ON)`**;
**there IS disparity on screen and it looks like working stereo — that is the point**; and
**the 1/D law is broken** — near the wall it may still pass the 5 px test and the far field will
not move with it. **The verdict for this arm is that the LAW failed, not that the pixels are
wrong.** **If S4 is indistinguishable from S3 in every respect, S3's pass must be WITHDRAWN** (`49`).

---

## §5 — R5a / R5b / R5c. **ARM 3's COST. `P5`. SPLICED IN FULL.**

`RUN-SHEET-297` §9 delegated this to `RUN-SHEET-295` §10.4 "three times, with the knob set to 0, 1
and the group removed". **Same defect 1. Here are the three blocks.** Cradle (STAGE 41), same spot
each time, against `272` §5.2's baseline: **CPU `0.890 ms` mean / `2.504 ms` worst, GPU `0.832 ms`,
against the `11.111 ms` period.** **Report a DELTA, never an absolute, and say which half moved.**
**Cut every window list at the `lvlStageLoad` line numbers — a tail is not a sample** (`273` §1).

**R5a — stereo ON, ARM 3 OFF. Stereo as it was.**

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
$env:GETV_STEREO_REBUILD        = "0"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_299_R5a_cost_rebuild_off.log 2>&1
Select-String -Path run_299_R5a_cost_rebuild_off.log -Pattern 'GETV_FPS=panel'
Select-String -Path run_299_R5a_cost_rebuild_off.log -Pattern 'budget|WORK|pools scaled|props interpolated|game_exit requested'
Select-String -Path run_299_R5a_cost_rebuild_off.log -Pattern 'EXCEPTION'
```

**R5b — stereo ON, ARM 3 ON. ONE behaviour change from R5a (`48`). THIS IS THE NUMBER.**

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
$env:GETV_STEREO_REBUILD        = "1"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_299_R5b_cost_rebuild_on.log 2>&1
Select-String -Path run_299_R5b_cost_rebuild_on.log -Pattern 'GETV_FPS=panel'
Select-String -Path run_299_R5b_cost_rebuild_on.log -Pattern 'budget|WORK|pools scaled|props interpolated|game_exit requested'
Select-String -Path run_299_R5b_cost_rebuild_on.log -Pattern 'EXCEPTION'
```

**R5c — the mono baseline. The whole stereo group removed.**

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
.\goldeneye.exe *> run_299_R5c_cost_mono.log 2>&1
Select-String -Path run_299_R5c_cost_mono.log -Pattern 'GETV_FPS=panel'
Select-String -Path run_299_R5c_cost_mono.log -Pattern 'budget|WORK|pools scaled|props interpolated|game_exit requested'
Select-String -Path run_299_R5c_cost_mono.log -Pattern 'EXCEPTION'
```

**GATE R5:** **`R5b − R5a` is ARM 3's own cost and it is the number this sheet owes.**
`R5a − R5c` is stereo's. **Neither has to be zero. Both have to be KNOWN.**
**No `[getv][stereo]` line may appear in R5c** — that is its one gate that can fail (`48`).

**►► THE GPU HALF IS DELIBERATELY NOT REPRODUCED.** `[MEASURED]` `GETV_FPS=0` **locks up on Cradle
within seconds, 3 of 3** (`273` §7.3), and `GETV_GPUTIME` refuses to report under a cap. **ARM 3 is
CPU-side and no GPU delta is predicted** — `[INFERRED]`, and that is exactly why it is not claimed.

---

## §6 — C2. **ARM C's GATE. THREE ARMS AND IT HAS NEVER ONCE BEEN EXERCISED.**

`298` §3: `GETV_PROPROOMTEST=0` fired its banner in arm C, **but no gun was dropped**, so
*"the gun disappears on the floor"* is untested and `bg.c:583`'s `getROOMID_isRendered(roomnum)` —
*"NEITHER `GETV_ROOMSCISSOR` NOR `GETV_PROPCULLBOX` TOUCHES IT"* — has now survived a THIRD arm
untested. **This block's whole content is the instruction to drop the gun.**

**RUN IT TWICE — the knob at `1` then at `0` — and in BOTH arms: drop a weapon on the floor, back
away until it disappears (or does not), walk in and out of the doorway, and press F9 at the exact
spot where it vanishes.** Below is the `=0` arm; **for the control arm change the two marked lines
and nothing else.**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
Get-ChildItem .\dlgrab_*.txt,.\dlgrab_*.bmp -ErrorAction SilentlyContinue | Measure-Object | Select-Object -ExpandProperty Count
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
$env:GETV_PROPROOMTEST = "0"          # <-- CONTROL ARM: "1"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_299_C2_proproomtest_off_gun.log 2>&1     # <-- CONTROL ARM: run_299_C2_proproomtest_on_gun.log
Select-String -Path run_299_C2_proproomtest_off_gun.log -Pattern 'GETV_FPS=panel'
Select-String -Path run_299_C2_proproomtest_off_gun.log -Pattern 'proproomtest\]|roomscissor\]|getv\]\[stereo\]'
Select-String -Path run_299_C2_proproomtest_off_gun.log -Pattern 'dlgrab_|getv\]\[shot\]'
Select-String -Path run_299_C2_proproomtest_off_gun.log -Pattern 'EXCEPTION|game_exit requested'
New-Item -ItemType Directory -Force -Path .\grabs_299_C2_off | Out-Null
Move-Item -Path .\dlgrab_*.txt,.\dlgrab_*.bmp -Destination .\grabs_299_C2_off -Force -ErrorAction SilentlyContinue
Get-ChildItem .\grabs_299_C2_off | Select-Object Name, Length, LastWriteTime
```

**GATE C2:** the `=0` arm MUST print `[getv][proproomtest] GETV_PROPROOMTEST=0 -- posIsOnScreen
NEUTRALISES ...` and the control arm MUST NOT. **The result is the owner's sentence: does the
dropped gun stay visible with the room test neutralised?**

- **Gun stays visible at `=0`, disappears at `=1`** → `getROOMID_isRendered` is the mechanism, after
  three arms of surviving untested.
- **Gun disappears in BOTH** → `298` §8 falsifier 3 fires: **`getROOMID_isRendered` is exonerated
  and the disappearing props are a FOURTH thing**, not bug 1 and not bug 2.

---

## §7 — WHAT THIS SHEET DELIBERATELY DOES NOT CONTAIN

- **`GL_DEPTH_CLAMP` in `gfx_opengl.c`.** The named fix for bug 2. **It is a build and it must not
  be written before §1 has run** (`298` §7, and `NEXT-SESSION-PROMPT-299`'s own instruction).
- **`configFiltering`'s missing `over` guard** (`ge_config.c:421/424/428`). One line, a build, and
  **independently re-verified offline this session**: `grep` for direct `config*` assignment in
  `ge_config.c` returns **exactly those three lines and nothing else**, so `298` §5's scope claim
  stands and every other knob on this sheet obeys environment-over-file precedence.
- **A fix for the rebuild census's cadence.** `GETV_STEREO_REBUILD_REPORT=1` makes it a census with
  no build, which is why §2 and §4 use `1`. Making `=600` accumulate over its window instead of
  printing one frame's snapshot is a build and is not owed yet.
- **`297` §12's mine crash** and its two non-equivalent corrections. `[REPORTED]` pre-existing,
  proven by `goldeneye_PARENT.exe`. **A NEW SESSION's work. DO NOT SHOOT A MINE in any arm above.**
- **The filtering question.** Still open. Until the source fix lands the only route is editing
  `filtering = point` in `%APPDATA%\Goldeneye-Native\Goldeneye-Native\goldeneye.cfg`
  (derive with `$env:APPDATA`, §0) and **the gate is the banner reading `filtering=0`.**
- **Any commit.** Every commit is the owner's (`00-STATE` §1.1).
