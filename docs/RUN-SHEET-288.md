# RUN SHEET 288 — the jitter statistic, `GETV_FPS=panel`, and the arms `287` still owes

**Written 2026-08-31, after `287` PART ONE completed and ARM 4E came back opposite its prediction.**
**Predecessor: `RUN-SHEET-287.md`. Its §4A-§4E ARE WORN AND MUST NOT BE RE-RUN** — except `4B` and
`4C`, which are re-run here for a NEW reason, stated in §3.

---

## §0 — WHAT CHANGED IN THE SOURCE, AND WHY

**Two changes, ONE binary, both in `getv/port/fast3d/gfx_sdl2.c`, both inert unless asked for.**

**1. THE JITTER STATISTIC — `288`'s reason for existing.** `287` ARM 4E scored **99.83% `1x` over
21,736 intervals at `vsync=0`**, against 4A's 99.90% at `vsync=1`, and **falsified its own written
prediction.** The real finding was the one underneath: **the `1x` bin is `[0.5,1.5)` of the panel
period = 4.17 to 12.5 ms, THREE TIMES WIDE.** A run alternating 6 and 10.5 ms scores **100% `1x`** and
would feel terrible. `GETV_PACEHIST` catches DROPPED and DOUBLED frames; it is BLIND to jitter inside
a frame period — **`285` §3.3's own critique, one level finer, now aimed at the instrument built to
answer it.** The turn complaint may live entirely in that blind spot.

Added inside the existing report, per window, no new knob:
- **`sd`** — standard deviation of the interval, ms. How spread out.
- **`jd`** — **mean `|dt[n]-dt[n-1]|`**, ms. **The one that names the failure.** Even run ~0. Slow
  drift ~0 (correctly — nobody feels a drift). **Alternation: large.** `sd` cannot separate the last
  two; `jd` can, which is why `sd` does not ship alone.
- **`jdp` / `jdm`** — `jd` as a % of the **panel period** and of the **window mean**. See §3.
- **a 10-bucket sub-histogram across `0.5x`-`1.5x`**, so the SHAPE is visible: one column = even,
  **two columns with a hole = alternating.** A number can be argued with; a hole cannot.

**2. `GETV_FPS=panel`** — `00-STATE` §3's cheap item. `287` built the SDL query and left it gated on
`GETV_PACEHIST`, LAZY (first present, 65+ lines after the cap is resolved) and **consumed by nothing.**
`ge_panel_hz_query()` is now hoisted above the cap parse in `gfx_sdl_init`, asked fresh so it
**follows the window between monitors** — the session lead runs a 120 Hz panel **and a 180 Hz one**,
and one env value has to be right on both desks. **`GETV_SIMHZ=query` chains off `ge_pace_framerate`
for free** (`frametiming.c:126`). **IT REFUSES ON AN UNKNOWN RATE AND EXITS — it does not fall back**
(rule `17`): a cap silently left at 60 on an unknown panel does not fail, it produces a whole session
of numbers defined against the wrong rate, **which is exactly `285`.** OPT-IN (`48`): a numeric
`GETV_FPS` behaves byte-for-byte as before, so every log in `92`-`287` stays readable as written.

**`ge_config.c:355`'s `framerate=` key is UNTOUCHED.** Its >60 rejection is now reasoned wrongly —
`GETV_SIMHZ` decoupled the thing that reasoning is about — but **changing a default is the session
lead's call** (`286` §2), and rule `2` says nothing is deleted. Flagged, not changed.

## §0a — ►►►► THE REGEN IS OWED, AND IT IS OWED *AFTER* THE ARMS, NOT BEFORE. ◄◄◄◄

`gfx_sdl2.c` is **GITIGNORED AND REGENERATED** from pristine + `0001-getv-port-layer.patch`
(`RUN-SHEET-287` §0a — the trap `00-STATE` §6 names for `gfx_pc.c` only). Two live consequences:

1. **`tools/fetch-thirdparty.sh verify` ALREADY SAYS `DIFFERS getv/port/fast3d/gfx_sdl2.c`.**
   **`[MEASURED]` 2026-08-31, after these edits. THAT FAILURE IS CORRECT AND EXPECTED** until step 2.
2. **A REGEN BEFORE THE BUILD WOULD DELETE BOTH CHANGES.** `268` was committed without a regen and
   `GETV_DLGRAB` was absent from a fresh clone for two days.

**RUN THIS ONLY AFTER THE ARMS ARE WORN, so the patch captures the version that actually ran.**
**MAIN PC, GIT BASH — not the bridge, not MSYS2:**
```
"C:\Program Files\Git\bin\bash.exe" -lc "cd /f/Projects/GEVR/GoldenEyeVR/goldeneye-native && tools/fetch-thirdparty.sh regen && tools/fetch-thirdparty.sh verify"
```
**THE GATE IS `verify`: `15/15 files match pristine + patch`. A byte count is not the gate.**

---

## §1 — BUILD, AND THE BINARY GATE. **TEN STRINGS NOW, NOT SIX.**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
& getv\build_windows.ps1 -Target all *> build_288_jitter_panel.log 2>&1
Select-String -Path build_288_jitter_panel.log -Pattern 'error|Error|FAILED' | Select-Object -First 20
Get-Item F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows\goldeneye.exe |
    Select-Object FullName, LastWriteTime, Length
$exe = 'F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows\goldeneye.exe'
$txt = [Text.Encoding]::ASCII.GetString([IO.File]::ReadAllBytes($exe))
foreach ($k in 'GETV_ROOMSCISSOR','GETV_PROPCULLBOX','GETV_PACEHIST') {
    if ($txt.Contains($k)) { "$k IS IN THE BINARY" } else { "$k IS **NOT** IN THE BINARY -- STOP" }
}
foreach ($k in 'SIX SITES','pacehist','PANEL REPORTED BY SDL','jitter: sd=','GETV_FPS=panel REFUSED','GETV_CULLWHY','twin-disagree') {
    if ($txt.Contains($k)) { "marker '$k' present" } else { "marker '$k' MISSING -- STALE BUILD, STOP" }
}
```
**All TEN must say IS IN / present.** The four new ones are `jitter: sd=`,
`GETV_FPS=panel REFUSED`, `GETV_CULLWHY` and `twin-disagree` — **a knob that is not in the binary reads as a clean null result**
(`133`, `268` §4). Timestamp must be newer than **`2026-08-31 02:24`** (the `287` binary,
18,026,915 bytes).

---

# ►►►► PART ONE — VALIDATE THE NEW STATISTIC BEFORE BELIEVING ANY ARM OF IT ◄◄◄◄

## §2 — IT IS ALREADY VALIDATED OFFLINE. READ THIS BEFORE RUNNING ANYTHING.

**`[MEASURED]` `288`, no build:** the real `ge_pacehist_record` / `ge_pacehist_emit` were extracted
from `gfx_sdl2.c`, compiled with SDL stubbed, and driven by five synthetic streams whose answers are
known by construction. Clean under `gcc -Wall -Wextra`.

| stream | old bins | `sd` | `jd` | `jdp` | sub-1x |
|---|---|---|---|---|---|
| even `8.333` | 100% `1x` | 0.000 | 0.000 | **0.0%** | one column |
| **alternating `6.0`/`10.5`** | **100% `1x`** | 2.250 | **4.500** | **54.0%** | **two columns + hole** |
| slow drift `8.0`->`9.0` | 100% `1x` | 0.288 | **0.002** | **0.0%** | one column |
| even `16.667` | 100% `2x` | 0.000 | 0.000 | 0.0% | — |
| uncapped ~`0.25` | 100% `<0.5x` | 0.088 | 0.103 | 1.2% / **`jdm` 40.9%** | — |

**Row 2 is the whole point: the old bins CANNOT TELL ROW 1 FROM ROW 2. `jdp` reads 0.0% and 54.0%.**
**Row 3 is why `sd` does not ship alone: `sd` = 0.288 on a drift nobody feels, `jd` = 0.002.**

**THIS DOES NOT REPLACE THE ON-HARDWARE VALIDATION IN §3.** A harness proves the arithmetic; it
cannot prove the stamp is in the right place or that the real pacer behaves like a synthetic stream.
`279` §7: *a detector tuned on the positive frame passes its own contract until it meets the
negative one.*

## §3 — THE PREDICTIONS, WRITTEN BEFORE THE RUNS (rule `15`, `P5`)

**►► READ THE FIRST LINE OF THE LOG BEFORE ANYTHING ELSE: `PANEL REPORTED BY SDL: <n> Hz`.**
**Every prediction below is a RATIO of it, never a bare number** — `287` §4 defect (a) was a hidden
panel constant, and the session lead runs a 180 Hz desk as well as a 120 Hz one.

**►► AND `jd` IS JUDGED AS A RATIO TOO, WHICH IS A DEFECT `288` FOUND IN ITSELF.** The first draft of
this sheet predicted *"`jd` must be large on the uncapped control"*. **The offline harness returned
0.103 ms — tiny in ms, 40.9% of its own mean — and falsified it.** A bare-ms threshold hides a CAP
constant the way the old bin table hid a PANEL constant. So:
- **an arm that PRESENTS on the panel is judged on `jdp`** (% of panel period);
- **an UNCAPPED arm is judged on `jdm`** (% of window mean), because there is no panel cadence there
  for a fraction of a period to mean anything.
**Saying which one an arm is scored on is part of the arm.**

| arm | recipe | prediction, WRITTEN FIRST | what a failure means |
|---|---|---|---|
| **V1** | `VSYNC=1 FPS=60` | bins `panel/60`; **`jdp` < 10%** | a hard-locked run reporting big jitter means **THE STATISTIC IS WRONG AND EVERY ARM BELOW IS VOID** |
| **V2** | `VSYNC=0 FPS=0` | no mode, `<0.5x`; **`jdm` > 20%** | a jitter figure that reads calm on the negative control is measuring nothing |
| **J1** | `VSYNC=1 FPS=panel` | bins `1x`; `jdp` — **NO NUMBER PREDICTED** | this is the measurement, not a gate |
| **J2** | `VSYNC=0 FPS=panel` | bins `1x`; `jdp` — **NO NUMBER PREDICTED** | this is the measurement, not a gate |

**V1 AND V2 ARE `287`'s 4B AND 4C RE-RUN FOR A NEW REASON, AND THAT IS NOT A RE-RUN OF A WORN ARM.**
Their pacing answers are already in `00-STATE` §3 and are not re-litigated. **They are here as the
positive and negative control FOR A STATISTIC THAT DID NOT EXIST WHEN THEY RAN.**

**►► J1 vs J2 IS THE OPEN QUESTION, AND I WILL NOT WRITE A NUMBER FOR IT.** `287` recorded a HINT the
bins could not hold — ragged windows **21% (4A) vs 44% (4E)**, `p99-p50` **0.646 vs 0.707 ms** — and
recorded it **as a direction to instrument, not a result**, because the runs were not length- or
activity-matched. **`jd` is the number that hint was reaching for. MATCH THE RUNS THIS TIME: same
spot, same activity, same window count.**
**IF `jdp` COMES BACK EQUAL, `vsync=0` IS CLEARED AT THIS RESOLUTION TOO**, the complaint is not in
the presented interval at all, and the carrier is the SIM — **`GETV_SIMHZ`, which `287` already named
as the untested carrier of `285` S1's "super smooth".** **THAT IS A REAL OUTCOME, NOT A FAILED RUN.**

---

## §4 — THE FIVE GATES, ON EVERY RUN IN THIS SHEET

1. the `roomscissor` banner;
2. **`ours: x=367.333`** in the VIEWPORT line — **`x=0` means `GETV_WIDESCREEN` came back ON**;
3. the `simhz` line at **`60 / cap` fields per frame** — a RATIO, not `0.500000`;
4. **zero** `simulation held to`;
5. a terminating **`game_exit requested`**.

**AND `GETV_SLOTFREE=1` IS IN EVERY BLOCK AND IS NOT OPTIONAL.** `GETV_SLOTFREE = 0` is still in
`%APPDATA%\Goldeneye-Native\Goldeneye-Native\goldeneye.cfg`; every block opens with
`Remove-Item Env:GETV_*`, which wipes the workaround, and the per-user cfg then wins on config
search path 4. **`287` 4C reached the intro cast and DIED: `NO SLOT: required=155 slots=10 free=0`
-> `0xc0000005` at fault addr `0x28`.** `RUN-SHEET-287` §5's own block omits this knob. **Until the
cfg line is gone, a block without it is a block that can crash.**

---

## §5 — V1. THE POSITIVE CONTROL. **VSYNC=1 FPS=60 — a LOOK-AT-IT run.**

Front-end menu or a boring spot. **If this arm fails, STOP — nothing below it means anything.**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
$env:GETV_SLOTFREE    = "1"
$env:GETV_VSYNC       = "1"
$env:GETV_FPS         = "60"
$env:GETV_SIMHZ       = "query"
$env:GETV_SIMDIV      = "1"
$env:GETV_WIDESCREEN  = "0"
$env:GETV_ROOMSCISSOR = "0"
$env:GETV_WINDOW      = "2560x1369"
$env:GETV_PACEHIST    = "600"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_288_V1_jitter_control_cap60.log 2>&1
Select-String -Path run_288_V1_jitter_control_cap60.log -Pattern 'PANEL REPORTED BY SDL'
Select-String -Path run_288_V1_jitter_control_cap60.log -Pattern 'pacehist\] .*jitter:|pacehist\] .*sub-1x|pacehist\] .*bins:'
Select-String -Path run_288_V1_jitter_control_cap60.log -Pattern 'roomscissor\]|ours: x=|fields per frame|slot\] GETV_SLOTFREE|simulation held to|game_exit requested'
```

## §6 — V2. THE NEGATIVE CONTROL. **VSYNC=0 FPS=0 — this is the GPU recipe and it is here to be UGLY.**

Same block as §5 with these three lines changed, everything else identical:
```powershell
$env:GETV_VSYNC       = "0"
$env:GETV_FPS         = "0"
```
```powershell
.\goldeneye.exe *> run_288_V2_jitter_negative_uncapped.log 2>&1
```
**Judged on `jdm`, NOT `jdp`, NOT bare ms.** **DO NOT reach the intro cast without `SLOTFREE=1`.**

## §7 — J1 and J2. THE MEASUREMENT. **`FPS=panel` — and this is also `GETV_FPS=panel`'s first run.**

**J1 = `VSYNC=1`, J2 = `VSYNC=0`. Same spot, same activity, SAME NUMBER OF WINDOWS.** Match them or
the comparison is `287`'s unmatched hint again with a better statistic on top.

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
$env:GETV_ROOMSCISSOR = "0"
$env:GETV_WINDOW      = "2560x1369"
$env:GETV_PACEHIST    = "600"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_288_J1_jitter_vsync1_panel.log 2>&1
Select-String -Path run_288_J1_jitter_vsync1_panel.log -Pattern 'GETV_FPS=panel|PANEL REPORTED BY SDL|pace: '
Select-String -Path run_288_J1_jitter_vsync1_panel.log -Pattern 'pacehist\] .*jitter:|pacehist\] .*sub-1x|pacehist\] .*bins:'
Select-String -Path run_288_J1_jitter_vsync1_panel.log -Pattern 'roomscissor\]|ours: x=|fields per frame|slot\] GETV_SLOTFREE|simulation held to|game_exit requested'
```
**THE `GETV_FPS=panel` GATE, AND IT IS SEPARATE FROM THE JITTER GATE:** the log must carry
**`GETV_FPS=panel -> <n> Hz, QUERIED FROM SDL`** and the `pace:` banner must then show that same
`<n>` as the cap. **If SDL will not say, the run REFUSES AND EXITS with `GETV_FPS=panel REFUSED` —
that is the knob working, not the knob failing.**

Then J2, same block, `$env:GETV_VSYNC = "0"`, log `run_288_J2_jitter_vsync0_panel.log`.

---

# PART TWO — WHAT `287` STILL OWES, UNCHANGED

## §8 — ARM 5: ►►►► COMPLETE. BOTH GATES PASS. `[MEASURED]` 2026-08-31 20:28. ◄◄◄◄

**RUN, WORN, AND CLOSED — `run_288_5_sixsites_streets.log`, eight `dlgrab` dumps.**
- **GATE 1, the sites, INDEPENDENTLY CONFIRMED** on a level that draws everything:
  `sites: bg_pri=170894 bg_sec=170894 chr=54173 **expl=2801 smoke=8680** prop=125117`.
  With `run_287_M3`'s `expl=4514 smoke=16374`, that is **two separate runs on two levels**.
- **GATE 2, THE DUMP, PASSES DECISIVELY.** **Eight dumps, ZERO sub-view rects.** Every one carries
  exactly two scissors: `(0,0)-(1280,960)` and the letterbox band `(0,120)-(1280,840)`, both FULL
  WIDTH. **`287`'s `dlgrab_8040` carried SEVEN distinct rects including the falsifier
  `(832,120)-(1276,840)`.** The sub-view rect is gone from every draw in every dump.
- **GATES: `SLOTFREE resolved to 1 (env=1)` — no crash, the added knob did its job** ·
  `ours: x=367.333` · `pace: 120 fps cap on, vsync=1` · `simhz 0.500000` · zero
  `simulation held to` · terminating `game_exit requested`.

**►►►► AND THE ARM PRODUCED A NEW `[REPORTED]` SYMPTOM THAT OUTRANKS WHAT IT WAS RUN FOR. ◄◄◄◄**
See §8a. Rule `16`: an owner report is a RANKING error, not noise.

## §8a — ►►►► ARM 7 IS NOW THE RANKED ARM: PROPS VANISH IN THE CORNERS. ◄◄◄◄

**`[REPORTED]` by the session lead, 2026-08-31, unprompted, while taking the ARM 5 dumps:**
*"a bunch of F9 shots of the textures disappearing... it was a car in the left hand corner of the
screen. It appears that it is making objects in that distance on those corners disappear when it's
in that side of the view while you are looking off in a different direction."*

**THIS IS THE SYMPTOM `bg.c:545` PREDICTED IN WRITING, BEFORE IT WAS SEEN:** *"A rectangle that is
too tight there does not clip an object, it REMOVES it."* **`287` wrote the knob for it and it has
NEVER BEEN RUN.**

**`[MEASURED]` FROM SOURCE — the mechanism is named, THE CAUSE IS NOT, and no fix is proposed:**
- `propobj.c:14018` is the **ONLY** consumer of the rectangle that decides whether a prop is drawn
  AT ALL. It calls `camIsPosInScreenBox(pos, margin, &bbox)` where `bbox` is
  `getPropCombinedRoomsBBox2D` — **THE ROOM'S PROJECTED RECTANGLE, NOT THE VIEW FRUSTUM.**
- `bondview.c:1139` builds its four planes from `box->min.x` / `box->max.x` through
  `c_screenleft`, `c_halfwidth`, `c_scalex`. **So the cull volume is the ROOM's rect. A prop whose
  POSITION leaves that volume is removed WHOLE, however much of it is still on screen** — which is
  exactly "a car in the corner, while looking off in a different direction."
- **ONE CANDIDATE IS ALREADY DEAD ON A SOURCE READ, AND IT IS THE OBVIOUS ONE:** the prop is NOT
  tested as a bare point. `chr.c:2750` and `propobj.c:5980` pass **`getinstsize(model)`** as
  `margin`, and `camIsPosInScreenBox` documents that as *"a slack in world units applied as a
  sphere around the point."* **Whether that sphere matches a car's real extent is NOT ESTABLISHED
  and is not claimed here.**
- **A SECOND, SEPARATE CULL SITS FIVE LINES BELOW AND MATCHES THE WORD "DISTANCE" IN THE REPORT:**
  `propobj.c:14035`, `xdiff^2+ydiff^2+zdiff^2 > 32000*32000` -> `result = FALSE`. **A HARD RADIUS,
  A LITERAL, AND A CONSOLE BUDGET** — mission rule `3`'s *"free = hardware budgets"* class.
  **IT IS NOT THE SAME MECHANISM AS THE BOX AND MUST NOT BE MERGED WITH IT** (`263` §1). ARM 7
  does not touch it; if props still vanish with the box off, **this is the next arm.**

**ON THE SESSION LEAD'S PROPOSAL — *"increase whatever that is to go further than the FOV a person
can see in a headset"* — THE DIRECTION IS RIGHT AND THE KNOB IS NOT, and the reason matters:**
this run was **4:3 pillarboxed** (`GETV_WIDESCREEN=0`, `ours: x=367.333`), so there is no extra FOV
being rendered yet for a wider cull to reveal. **The rectangle is narrower than the view that is
ALREADY being drawn.** Widening it is `P2`/`P3` when stereo arrives — the cull must be derived from
the RENDERED frustum, and in stereo from the UNION OF BOTH EYES plus headroom, **never from a stored
constant** — but that is a design note, **not this arm.** **ARM 7 answers "is it the box?" in one
run, and it already exists. Run the falsifier before designing anything.**

## §8b — ARM 7, THE BLOCK. `GETV_PROPCULLBOX=0`. **VSYNC=1 — a LOOK-AT-IT run.**

**Go to the SAME SPOT that produced the vanishing car, look the SAME way, and F9 there.** The
before-dumps already exist (`dlgrab_29855`/`30166`/`30209`/`31663`/`31870`, 20:25-20:28).

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getvuild-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
$env:GETV_SLOTFREE     = "1"
$env:GETV_VSYNC        = "1"
$env:GETV_FPS          = "120"
$env:GETV_SIMHZ        = "query"
$env:GETV_SIMDIV       = "1"
$env:GETV_WIDESCREEN   = "0"
$env:GETV_ROOMSCISSOR  = "0"
$env:GETV_WINDOW       = "2560x1369"
$env:GETV_STAGE        = "29"
$env:GETV_PROPCULLBOX  = "0"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_288_7_propcullbox_off.log 2>&1
Select-String -Path run_288_7_propcullbox_off.log -Pattern 'propcullbox\]'
Select-String -Path run_288_7_propcullbox_off.log -Pattern 'roomscissor\] sites:'
Select-String -Path run_288_7_propcullbox_off.log -Pattern 'roomscissor\]|ours: x=|fields per frame|slot\] GETV_SLOTFREE|simulation held to|game_exit requested'
(Select-String -Path run_288_7_propcullbox_off.log -Pattern 'dlgrab_\d+\.txt' -AllMatches).Matches.Value | Sort-Object -Unique
```

**THE GATE THAT SAYS THE KNOB TOOK:** the log must carry
`[getv][propcullbox] GETV_PROPCULLBOX=0 -- posIsOnScreen ignores the per-room rectangle`.
**Without that line the run is a clean null result and says nothing** (`133`, `268` §4).

**WHAT EACH OUTCOME MEANS, WRITTEN BEFORE THE RUN (rule `15`):**
- **THE CAR STAYS** -> **the room rectangle IS the mechanism.** The vanishing is a CULL, confirmed,
  and the fix is a design question about what volume the test should use — `P2`/`P3`, and it must be
  answered for stereo, not patched for flat.
- **THE CAR STILL VANISHES** -> **the box is NOT the mechanism** and the `32000` radius or the
  `getinstsize` margin is. **That is a real result. Do not re-run ARM 7 hoping; go to the radius.**
- **EXPECTED AND NOT A SECOND FAULT:** props retail would have culled are now drawn, and the frame
  costs more. **A COST, NOT A FIX. FALSIFIER ONLY. THIS MUST NEVER SHIP ON.**

## §8d — ►►►► ARM 7 RAN. THE BOX IS NOT THE MECHANISM. OUTCOME #2 FIRED. ◄◄◄◄

**`[MEASURED]` 2026-08-31 20:40, `run_288_7_propcullbox_off.log`, two dumps.** The knob TOOK —
`[getv][propcullbox] GETV_PROPCULLBOX=0 -- posIsOnScreen ignores the per-room rectangle` is in the
log, so this is **not a clean null result** (`133`, `268` §4). Gates clean: `ours: x=367.333`,
`simhz 0.500000`, zero `simulation held to`, terminating `game_exit requested`, all six sites
non-zero.

**`[REPORTED]` WITH THE KNOB OFF, THE PROPS STILL VANISH.** §8b's outcome #2, written before the
run: *"the box is NOT the mechanism... That is a real result. Do not re-run ARM 7 hoping."*
**THE ROOM RECTANGLE IS ELIMINATED. It is not the cull that is doing this.**

**AND THE SESSION LEAD ADDED TWO FACTS THAT NARROW IT FURTHER, BOTH `[REPORTED]`:**
1. **IT HAPPENS WHEN YOU ARE CLOSE TOO** — the object simply has to be further out toward the
   edge. **Further away, MORE of the screen makes it vanish.**
2. **IT IS SYMMETRIC: LEFT AND RIGHT.** *"On the left side it's the car, and on the right side the
   green bushes above the fence."* Both edges, same run, same F9 takes.

**WHAT THOSE TWO FACTS DO TO THE CANDIDATE LIST — AND NO CAUSE IS NAMED:**
- **THE `32000` RADIUS IS BADLY DAMAGED BY FACT 1.** A hard distance cull cannot remove something
  you are standing next to. **NOT declared dead — it is `[REPORTED]` against, not measured
  against, and `§8a` ranked it on the word "distance" in the earlier report.** §9 counts it.
- **FACT 2 POINTS AT THE LEFT AND RIGHT PLANES**, which `bondview.c:986` builds from
  `c_halfwidth * c_scalex` — **symmetric by construction**, which is exactly the shape reported.
- **FACT 1's DISTANCE BEHAVIOUR HAS A MECHANICAL READING AND IT IS NOT YET A FINDING:** the margin
  passed is `getinstsize(model)` = `BoundingVolumeRadius * scale` (`model.c:1184`) — **a bounding
  sphere in WORLD units.** A fixed world radius subtends a SMALLER ANGLE the further away it is,
  so the screen band in which a prop survives NARROWS with distance. **That matches "further away
  there is more space where it'll disappear" exactly — which is why it must be MEASURED, not
  believed. A story that fits is `275` §1's grep-for-a-guard all over again.**
- **AND THE CANDIDATE NEITHER ARM EVER TOUCHED:** `posIsOnScreen` opens with
  `getROOMID_isRendered(roomnum)`. **`GETV_ROOMSCISSOR` and `GETV_PROPCULLBOX` BOTH LEAVE THAT
  TEST ALONE**, so it has survived two arms without being tested once — and *"while you are
  looking off in a different direction"* is what a view-driven room-visibility cull sounds like.

**STOP ELIMINATING. THE NEXT ARM MEASURES WHICH TEST SAYS NO.**

## §8e — ►►►► ARM 8: `GETV_CULLWHY=1`. THE INSTRUMENT, NOT ANOTHER ELIMINATION. ◄◄◄◄

**WRITTEN, NOT BUILT, NOT RUN — it rides in `288`'s ONE binary with the jitter statistic and
`GETV_FPS=panel`.** Rule `15`: two arms have now been spent narrowing by elimination; that is what
building the instrument is for.

**WHAT IT IS.** `posIsOnScreen` is the only place that decides a prop is not drawn, and **it can
say no in six different ways.** `GETV_CULLWHY=1` counts all six and prints them at exit
(`port_support.c`, beside `getv_roomscissor_report`):
`room` · `fog` · `occl` · `box` · `view` **broken out per plane — near / left / right / top /
bottom** · `dist` (the `32000` radius) · and `drawn`.
The per-plane split comes from a **READ-ONLY TWIN** of `camIsPosInScreen` in `bondview.c` that
returns a bitmask instead of stopping at the first rejecting plane. **It decides nothing.**
It also prints `c_halfwidth`/`c_scalex` and **the cull frustum's half-angles in degrees**, to be
read against the VIEWPORT line in the same log.

**►► THE TWIN IS A LIABILITY AND IT CARRIES ITS OWN GATE** (`271` §7, rule `17`): if
`camIsPosInScreen` is ever edited and the mirror is not, it will report confidently about a test
that no longer exists. So the caller checks the mask against what `camIsPosInScreen` actually
returned and counts **`twin-disagree`**. **`twin-disagree` MUST BE ZERO. Non-zero VOIDS every
per-plane number in the report.**

**WHAT IT PRINTS IF POINTED AT THE WRONG THING (rule `15`, `P5`, WRITTEN BEFORE THE RUN):**
- **ALL COUNTS ZERO** in a level that visibly drops props -> **the counters are not on the path
  that removes them and the search is in the WRONG FUNCTION.** That is a result, not a null.
- **`dist` LARGE** -> it **contradicts** `[REPORTED]` fact 1, *"it happens when you're close."*
  **THE INSTRUMENT IS WRONG UNTIL SHOWN OTHERWISE, NOT THE REPORT** — `HANDOVER` §5, the owner's
  correction has outranked the analysis every time they conflicted.
- **`left` AND `right` BOTH LARGE AND ROUGHLY EQUAL** -> the symmetric signature that was reported.
- **`room` LARGE** -> the cull neither knob touches, and the two arms were looking in the wrong
  place from the start.
**NO PREDICTION IS WRITTEN FOR WHICH ONE WINS. That is the measurement.**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
$env:GETV_SLOTFREE     = "1"
$env:GETV_VSYNC        = "1"
$env:GETV_FPS          = "120"
$env:GETV_SIMHZ        = "query"
$env:GETV_SIMDIV       = "1"
$env:GETV_WIDESCREEN   = "0"
$env:GETV_ROOMSCISSOR  = "0"
$env:GETV_WINDOW       = "2560x1369"
$env:GETV_STAGE        = "29"
$env:GETV_CULLWHY      = "1"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_288_8_cullwhy.log 2>&1
Select-String -Path run_288_8_cullwhy.log -Pattern 'cullwhy\]'
Select-String -Path run_288_8_cullwhy.log -Pattern 'VIEWPORT n64' | Select-Object -First 3
Select-String -Path run_288_8_cullwhy.log -Pattern 'roomscissor\]|ours: x=|fields per frame|slot\] GETV_SLOTFREE|simulation held to|game_exit requested'
```
**GO TO THE SAME SPOT AND MAKE THE CAR AND THE BUSHES VANISH ON PURPOSE, then quit normally** —
the counters are cumulative over the run, so a run that never reproduces the symptom measures
nothing. **`GETV_PROPCULLBOX` IS DELIBERATELY LEFT AT ITS DEFAULT (ON)** so the `box` counter is
live and the reading describes the SHIPPING configuration, not ARM 7's.

**AND A SECOND PASS, `GETV_CULLWHY=1` PLUS `GETV_PROPCULLBOX=0`**, log
`run_288_8b_cullwhy_boxoff.log`: **`box` must drop to 0 and those rejects must reappear in the
per-plane counts.** If they vanish instead of moving, the accounting does not balance and the
instrument is wrong. **That is ARM 8's own validation arm and it is not optional.**

## §8c — ARM 5, THE ORIGINAL TEXT, KEPT BECAUSE RULE `2` DELETES NOTHING

**DO NOT re-litigate the `sites:` counters.** `run_287_M3_menu_offset0.log` carries
`expl=4514 smoke=16374` with every other site non-zero, on the `02:24` binary, gates clean.
**ALL SIX SITES TOOK** (`00-STATE` §3). What is owed is the DUMP: Streets, `GETV_STAGE=29`, stand
still with the artifact on screen, **F9 twice** — **no `287` log contains a single `dlgrab` line, so
F9 was never pressed.** The dump **must no longer carry the `(832,120)-(1276,840)` sub-view rect with
613 triangles under it**; that rect is the falsifier. **Read the dump by its own announcement, not by
timestamp** (`279` §2 — `278` mislabelled six files that way). Block: `RUN-SHEET-287` §5,
**plus `$env:GETV_SLOTFREE = "1"`**, log renamed to `run_288_5_sixsites_streets.log`.

## §9 — THEN, IN ORDER, AND ALL UNCHANGED FROM `287`
**ARM 6** the wear pass (`RUN-SHEET-287` §6) — **NEVER RUN** · **ARM 7** `GETV_PROPCULLBOX`, the
black-wall arm (§7) · **ARM 8A** the GPU, `VSYNC=0 FPS=0` (§8) · **ARM 8B** the CPU,
`VSYNC=0 FPS=120` (§8B). **Every one of those blocks needs `$env:GETV_SLOTFREE = "1"` added.**

## §10 — STILL OWED, NOW SEVEN SESSIONS
All of `277` §9 · `278` §6's INFERRED hoist-1 read · `279` §5's amount arm · `280` §7.3's black-wall
dump · `274` §7's CONTAMINATED gate. **Carried forward honestly, not quietly.**

## §11 — AND THE `287` DEFECTS, FIXED HERE RATHER THAN HONOURED
**(a)** the hidden panel constant in the bin predictions and the `simhz` gate — **restated as ratios
in §3 and §4.** **(b)** the row *"a pre-swap stamp reads near 0 ms in 4C"* — **STRUCK**, it cannot
discriminate in an uncapped arm where near-zero is the correct reading; **4B settles that question
and does it in §5.** Both are recorded in `00-STATE` §4.
