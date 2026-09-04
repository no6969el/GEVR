# MAIN STATION — THE ORDERED TEST SCRIPT

---

## ►►►► THE REGEN, AND IT IS PART OF EVERY NATIVE COMMIT. `271` §7. ◄◄◄◄
**`gfx_sdl2.c`, `gfx_pc.c` and `gfx_opengl.c` are GITIGNORED.** They reach git ONLY through
`getv/patches/thirdparty/0001-getv-port-layer.patch`. **A native commit without a regen ships a
tree that a fresh clone cannot rebuild** — that is how `GETV_DLGRAB` was missing for two days.

**RUN IT FROM GIT BASH. NOT MSYS2's BASH — MSYS2 SHIPS WITHOUT `git`,** so every cache probe
fails, the script falls through to a network fetch and blames the network. **And it CANNOT run
over the Claude bridge**: that mount refuses to unlink the target, so the `mv` fails.
**No network is needed** — `vendor/sm64ex-cache.git` holds the pinned SHA.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
$cands = @("C:\Program Files\Git\bin\bash.exe",
           "C:\Program Files (x86)\Git\bin\bash.exe",
           "$env:LOCALAPPDATA\Programs\Git\bin\bash.exe")
$bash = $cands | Where-Object { Test-Path $_ } | Select-Object -First 1
if (-not $bash) { "Git Bash not found. Report the output of: (Get-Command git).Source" ; return }
"using: $bash"
& $bash -c "cd /f/Projects/GEVR/GoldenEyeVR/goldeneye-native && tools/fetch-thirdparty.sh regen"
& $bash -c "cd /f/Projects/GEVR/GoldenEyeVR/goldeneye-native && tools/fetch-thirdparty.sh verify"
$p = "F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\patches\thirdparty\0001-getv-port-layer.patch"
Get-Item $p | Select-Object LastWriteTime,Length
```

### THE GATE IS `verify`, NOT THE BYTE COUNT
**`fetch-thirdparty: 15/15 files match pristine + patch`, and zero `DIFFERS`.** A byte count
only says the file changed; `verify` says the patch actually RECONSTRUCTS the tree.
**Then grep the patch for whatever you added this session** (e.g. `dlgrab`, `ge_pace_wait_ms`) —
a symbol you changed that is absent from the patch is a change a fresh clone will not have.

**BOTH WAYS THIS USED TO FAIL SILENTLY ARE NOW FATAL** (`271` §7): an unchecked `mv` that
printed *"wrote ... bytes"* after failing, and a missing `git` that blamed the network.
**`commit-now.ps1:193` still only WARNS about the regen — it does not refuse.** Running it is
still on the human.

---

> # ►►►► 2026-08-26 — `T3`-`T11` ARE ALL VOID. RE-RUN THEM. ◄◄◄◄
>
> **`179`/`180`: NO RUN BETWEEN 08-24 21:00 AND 08-26 HAD STEREO AT ALL** —
> `eye1=0` in every sample of every run. **Anything measured in that window was
> judged through a monocular image, including `T10` and `T13`.**
>
> ## **AND `T3` IS GATED ON GROUP `A` OF `185`.**
> `184` §4: the aim divide is unbounded between ~50 and ~87 degrees and `162`'s
> +-2 NDC clamp collapses that whole band onto one screen point. **A baseline
> taken against a crosshair that is being flung off-frame is not a baseline.**
>
> **`185` IS THE PLAN. `T1` and `T2` ARE DONE:**
> **`T1`** the virtual screen — **PASSED** once `178` ungated it (it was built
> inside `ge_vr_timewarp_create()`, which only runs under a knob that is off by
> default). **`T2`** the muzzle node — **PASSED**, two distinct `Switches[3]`
> values with different `numSwitches`. **U-18 proceeds.**
>
> **STANDING COMMAND UNCHANGED, and `-ViRate 90` IS SAFE** — `[MEASURED]`
> 2026-08-26: `90.0 fps · interpUsed=0 · stereo in 75 of 99 samples`. `180`'s
> claim that Route B killed stereo is RETRACTED.
>
> **NEW GATE ON EVERY RUN:** the launch now prints the PREVIOUS run's verdict,
> and the log must say **`layout OK: SharedQueueResources ... on both sides`**
> (`183`) and **`VRGATE/s: ... -> stereo=N | OK`** (`180` §4). **If VRGATE names
> a false term, STOP — that is the answer, no inference needed.**
>
> **CLOSE WITH THE X** — `181` made it safe, and three more clean closes are
> owed (`185` `D2`).


> # ►►►►►► `G-220`: TURN YOUR BODY, YOUR AIM MUST TURN. BUILD TWICE. `221`. ◄◄◄◄◄◄
>
> **`[MEASURED]` `220`: 176 degrees of physical rotation moved the bullet 17.**
> We pass `R_head^-1 * gun_world`; the head term CANCELS the very turn you made,
> and the game's camera never rotates. **THE CROSSHAIR IS RIGHT TO BE
> HEAD-RELATIVE; THE BULLET IS NOT.**
>
> **FIX: `dir = ViewToWorld^-1 * fwdPlay`, with `ViewToWorld` recovered as
> `throw_item_pos_related * gunmtx_camspace^-1`** — both reachable, no new game
> symbol. **THE COMPOSITION ORDER IS NOT GUESSED: three candidates ship and one
> run picks** (`48` / `158` §2 — the method that closed `200` and `203`).
>
> ```powershell
> .\build.ps1
> .\build.ps1
> .\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
>          -WorldUnitsPerMetre 25 -HandUnitsPerMetre 25 `
>          -ViewmodelScale 0.5 -GunOffX 0 -GunOffY 0 -GunOffZ 0 `
>          -AimFromHand -MuzzleOrigin -NoCrouch -HudDepth 0.2
> ```
>
> ## NINE SHOTS, ~2 s APART so `IMPACTNEW` lands between them:
> **three FORWARD · three UP AND RIGHT · PHYSICALLY TURN 180, then three FORWARD.**
>
> ## READING IT
> **Mirrored or rotated wrong -> `-BulletFrame 2`** (the other composition order,
> a launch not a build). **Turning still does nothing -> `-BulletFrame 0`** is
> today's behaviour, and the recovery is wrong rather than its application.
>
> ## THEN: **the crosshair slice** — `220` §4: disappear off-screen, sit ON the
> target, much smaller. **THE FULL CHECKLIST IS IN `HANDOVER.md`.**

> # ►►►► HISTORY — `217` DID NOTHING; FIX THE INSTRUMENT. `219`. ◄◄◄◄
>
> **`[MEASURED]` `-NoBulletDir` and the default give THE SAME TABLE.** `217` is
> falsified as a sufficient cause. **It stays in (DELETE NOTHING) and costs
> nothing.**
>
> **AND THE LIMIT IS NOW MY INSTRUMENT:** the impact logged with a shot is the
> PREVIOUS shot's, which has muddied `216`, `217` and `218`. **Fixed — the impact
> point is published every frame and the host logs `IMPACTNEW` the moment it
> changes, so pairing is by ADJACENCY.**
> **SAME SYMBOL, WIDER PAYLOAD -> ONE BUILD, not two.**
>
> ```powershell
> .\build.ps1
> .\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
>          -WorldUnitsPerMetre 25 -HandUnitsPerMetre 25 `
>          -ViewmodelScale 0.5 -GunOffX 0 -GunOffY 0 -GunOffZ 0 `
>          -AimFromHand -MuzzleOrigin -NoCrouch -HudDepth 0.2
> ```
>
> ## NINE SHOTS. PAUSE ~2 SECONDS BETWEEN EACH.
> **1.** three FORWARD, level · **2.** three UP AND RIGHT ·
> **3.** PHYSICALLY TURN 180 (chair and all), then three FORWARD.
> **No walking, no wall-hunting.** The pause is what keeps `IMPACTNEW` between
> shots rather than beside one.
>
> ## THEN `Copy-Item .\gevr.log .\gevr-keep-IMPACTNEW.log` and send it.
> **Every shot will then have ITS OWN impact** — and if the gun-vs-bullet
> relation is a fixed rotation, that rotation IS the fault.

> # ►►►► HISTORY — THE BULLET IGNORED THE GUN. `217`. ◄◄◄◄
>
> **`[MEASURED]` 14 shots: the GUN's world yaw swept `181 DEGREES`; the BULLET's
> moved `14`. Every impact landed within half a metre of ONE SPOT.**
> **THAT IS `184`'s ORIGINAL COMPLAINT, NEVER FIXED FOR THE BULLET** — `A1` fixed
> it for the CROSSHAIR only, and nothing measured the bullet until `216`.
>
> **CAUSE `[READ]`: we hand the game a direction in the HEADSET's frame; the game
> rotates it by its OWN camera matrix (`chrprop.c:952`), and the game camera
> never receives the head rotation (`194`). The two coincide ONLY at neutral.**
> **`194`'s fault for the THIRD time** — after the bullet's origin and the drawn
> gun's orientation.
>
> **FIX: take the direction from `hand->gunmtx_camspace` — THE GAME'S OWN GUN
> MATRIX IN ITS OWN FRAME, which already carries our seam.** `[READ]` it sat
> UNNAMED in `structs.h` as 16 loose `s32`s at `0xa98`, for the whole project.
> **`structs.h` CHANGED -> FULL REBUILD, and TWO new symbols -> BUILD TWICE.**
>
> ```powershell
> .uild.ps1
> .uild.ps1
> .r.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
>          -WorldUnitsPerMetre 25 -HandUnitsPerMetre 25 `
>          -ViewmodelScale 0.5 -GunOffX 0 -GunOffY 0 -GunOffZ 0 `
>          -AimFromHand -MuzzleOrigin -NoCrouch -HudDepth 0.2
> ```
>
> ## `G-217`: **POINT THE GUN ANYWHERE AND SHOOT. THE BULLET MUST FOLLOW IT.**
> **MIRRORED or 90 deg out -> `-BulletDirCol`** (row vs column, `158` §2's
> ambiguity on a new matrix — not a failure).
> **Still one spot -> the frame theory is wrong; re-run `216`'s five groups.**
>
> ## THEN re-run the five groups anyway — the gun-vs-bullet yaw table IS the
> pass/fail, and it is arithmetic rather than an impression.
>
> **`[REPORTED]` *"I shot upwards to the right, and it shot to the LEFT of the
> gun."* `215`'s parallel-ray offset CANNOT do that — a constant offset is the
> same displacement whichever way you face. **THERE ARE TWO FAULTS**, and nothing
> logged so far can separate them: every instrument is in CAMERA space and the
> question is about direction in WORLD space.
>
> **`SHOTWORLD` fixes that — gun world position, gun world forward, the impact
> point and the player, ALL IN ONE FRAME.** No camera matrix needed (and
> `currentPlayerGetViewToWorldMtxf` is not reachable anyway).
> **ONE NEW SYMBOL -> BUILD TWICE (`136`).**
>
> ```powershell
> .\build.ps1
> .\build.ps1
> .\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
>          -WorldUnitsPerMetre 25 -HandUnitsPerMetre 25 `
>          -ViewmodelScale 0.5 -GunOffX 0 -GunOffY 0 -GunOffZ 0 `
>          -AimFromHand -MuzzleOrigin -NoCrouch -HudDepth 0.2
> ```
>
> ## THE FIVE GROUPS — **THREE SHOTS EACH, SAY EACH GROUP OUT LOUD:**
> **1.** FORWARD, level, wall ~5 m · **2.** FORWARD, level, ~15 m ·
> **3.** UP 45 deg · **4.** UP AND RIGHT · **5.** TURN AROUND 180, repeat 1.
>
> **THREE SHOTS PER GROUP IS NOT PADDING:** the impact logged with a shot is the
> PREVIOUS shot's (`216` §3), so three shots give two usable pairs.
>
> ## THEN: `Copy-Item .\gevr.log .\gevr-keep-SHOTWORLD.log` and send it.
> **`211`'s SOLVER comes AFTER this** — one built for the forward case alone
> would leave the direction-dependent term untouched.

> # ►►►► HISTORY — BUILD ONCE; THE SIGHT MUST FUSE. `215`. ◄◄◄◄
>
> **`[REPORTED]` the crosshair unfused — and that is a PRECEDENCE BUG from `210`:
> its parallax term overrode `-HudDepth 0.2` with a value an ORDER OF MAGNITUDE
> smaller. FIXED: an explicit `-HudDepth` now wins.**
>
> **AND `[REPORTED]` THE WEARER MEASURED THE PARALLAX BY EYE:** *"where the gun
> was held and where that right aimer is IS THE EXACT DISTANCE THAT IT'S OFF"* at
> ~9 m. **THE MISS EQUALS THE MUZZLE-TO-EYE OFFSET — two PARALLEL rays, displaced
> by that vector at EVERY distance.** `214` §3's contradiction is resolved: the
> miss is CONSTANT IN LINEAR TERMS, which reads as shrinking up close and
> worsening far away. **`211`'s SOLVER is the fix and its premise is now
> confirmed from the headset.**
>
> ```powershell
> .\build.ps1
> .\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
>          -WorldUnitsPerMetre 25 -HandUnitsPerMetre 25 `
>          -ViewmodelScale 0.5 -GunOffX 0 -GunOffY 0 -GunOffZ 0 `
>          -AimFromHand -MuzzleOrigin -NoCrouch -HudDepth 0.2
> ```
>
> ## 1. **THE CROSSHAIR MUST FUSE.** Nothing else is judgeable until it does.
> ## 2. `G-213`: the longer weapon — `214` §1's fix was built but NOT WORN when
> the *"shoots right and downward"* report was made. **Re-judge it now.**
> ## 3. **THEN `211`'s SOLVER.**
> ## NO LONGER NEEDED: `214`'s distance measurement — §1 answered it.

> # ►►►► HISTORY — ONE-LINE FIX, `G-213` AGAIN. `214`. ◄◄◄◄
>
> **`[REPORTED]` *"the larger gun went further to the right"* — an error that
> scales with BARREL LENGTH is a ROTATION error, not an offset one.**
> `[READ]` `g_geVrLastR` is published AFTER `203`'s transpose, so it holds the
> matrix the GAME consumes. **`213` rotated the barrel by the INVERSE.**
> **FIXED: columns instead of rows. ONE BUILD — the symbol is already in.**
>
> ```powershell
> .\build.ps1
> .\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
>          -WorldUnitsPerMetre 25 -HandUnitsPerMetre 25 `
>          -ViewmodelScale 0.5 -GunOffX 0 -GunOffY 0 -GunOffZ 0 `
>          -AimFromHand -MuzzleOrigin -NoCrouch -HudDepth 0.2
> ```
>
> ## 1. `G-213`: swap to a LONGER weapon. **The PROPORTIONAL error must be gone.**
> ## 2. ►► THEN THE DISTANCE MEASUREMENT — IT DECIDES THE NEXT BUILD. ◄◄
> **Shoot the SAME target from CLOSE, then from FAR.** `[REPORTED]` this run says
> the miss gets WORSE with distance; `[MEASURED]` `210` said the origin offset
> SHRINKS with distance. **BOTH CANNOT BE RIGHT.** `SHOTREC` settles it — and it
> must be measured AFTER this build, because `214` §1 changes the muzzle.
>
> ## NOT DIAGNOSED, NOT GUESSED AT: the STICK turn re-aiming the gun (`214` §2.1
> — read `gunfire.c:548` first) and the gun looking LARGER (`214` §2.2 — that is
> the SCALE question, with the guard reading smaller at the same time).

> # ►►►► HISTORY — U-18 WIRED; BUILD TWICE, `G-213`. `213`. ◄◄◄◄
>
> **The muzzle is now the game's OWN per-weapon barrel:
> `handPos + R * (Switches[3] * 0.1)`.** `[MEASURED]` pistol **35.0 cm**, second
> weapon **70.6 cm**. **`212` settled every term FROM SOURCE — no wear test.**
> **NOT `field_B58`: `[READ]` two writers, two frames** (`gunfire.c:758` camera,
> `:815` world), **and the world branch fired on 518 of 1255 samples.**
> **ONE NEW SYMBOL -> BUILD TWICE (`136`). `-NoMuzzleNode` reverts.**
>
> ```powershell
> .\build.ps1
> .\build.ps1
> .\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
>          -WorldUnitsPerMetre 25 -HandUnitsPerMetre 25 `
>          -ViewmodelScale 0.5 -GunOffX 0 -GunOffY 0 -GunOffZ 0 `
>          -AimFromHand -MuzzleOrigin -NoCrouch -HudDepth 0.2
> ```
> ## ►► `-GunOff*` MUST STAY AT 0. ◄◄ They were `154`'s PISTOL constants
> CARRYING the barrel; with the real one wired, **a barrel counted twice is worse
> than not at all.**
>
> ## `G-213`: **swap to a LONGER weapon. The shot must stay on the crosshair.**
> `[REPORTED]` before this: *"the secondary gun sprayed way off to the right."*
>
> ## THEN: **`211`'s SOLVER** — U-18 was its prerequisite and is now done.

> # ►►►► HISTORY — U-18: BUILD ONCE, READ ONE LINE. `212`. ◄◄◄◄
>
> **`171` §4 parked U-18 because the muzzle is in the MODEL's frame. `[READ]`
> `gunfire.c:746-760`: THE GAME DOES THE CONVERSION AND STORES IT IN
> `hand->field_B58` — and `gun.c:2171`/`:2365` use it as the PROJECTILE SPAWN
> POINT.** `structs.h:1752`, reachable, no new symbols.
>
> **BUT THREE READS DISAGREE ON ITS FRAME AND SCALE (`212` §3), so it PRINTS
> rather than wires.** One line answers all three.
>
> ```powershell
> .\build.ps1
> .\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
>          -WorldUnitsPerMetre 25 -HandUnitsPerMetre 25 `
>          -ViewmodelScale 0.5 -GunOffX 0 -GunOffY 0 -GunOffZ 0 `
>          -AimFromHand -MuzzleOrigin -NoCrouch -HudDepth 0.2
> ```
> **NO SHOTS NEEDED.** Get into a level, **switch weapons once**, close.
> ```powershell
> Select-String -Path .\gevr.log -Pattern "MUZZLEPT|MUZZLENODE" | Select-Object -Last 6
> ```
> **SMALL and near our own `muzzle=` -> camera space, WIRE IT.
> Ours x10 or /10 -> the `:643` scale, one constant.
> LARGE and near `playerpos` -> WORLD, needs `WorldToView` first.**
>
> ## THEN: wire it into `muzzle_origin` and into `211`'s solver.

> # ►►►► HISTORY — STOP; DO NOT RUN `B1`'s SECOND ARM. `211`. ◄◄◄◄
>
> **RUN 1 ANSWERED IT AND RUN 2 WOULD SHOW NOTHING.** `[MEASURED]` `210`: the
> parallax term delivers `~0.0145` NDC, its distance was STALE (`626 m` while the
> guard was at arm's length), PD's `1.75 m` floor zeroes it at contact range,
> **and it corrects HORIZONTALLY while the measured fault is VERTICAL** (muzzle
> 8 cm below the eye; miss-then-hit `4.38 deg`).
>
> ## **THE NEW PLAN IS `211`: draw the crosshair where the BULLET goes.**
> **NO WEAR TEST IS OWED RIGHT NOW.** The next work is code:
> **1. `U-18`** — the per-weapon muzzle (`T2` PASSED). Removes the last tuned input.
> **2. THE SOLVER** — ~150 lines, host-side, no new game symbols, `-NoAimSolver`.
> **3. `G-211-1..4`**, in that order.
>
> ## STILL OPEN AND UNCHANGED: the SCALE (`205`, and *"skinnier"* is an ASPECT
> word — chase it separately), the menu crash (`206`/`207`), `-AutoLevel` inert
> (`208`), **and THE COMMIT — twenty-six documents overdue.**

> # ►►►► HISTORY — `B1` BUILT; TWO RUNS. `210`. ◄◄◄◄
>
> **The crosshair now converges at the LAST IMPACT DISTANCE** (`193` §2's
> 0.19-0.61 m origin offset). **PD's design, with their 1.75 m floor,
> nominal-relative baseline and +-0.02 clamp all KEPT** — and the clamp is a TEST:
> `-HudDepth 0.2` computes as `~0.128` NDC, **six times PD's maximum.**
> **AND `SHOTREC` now logs the head + controller pose AT FIRE TIME**, so a shot
> finally pairs with the pose that produced it.
> **ONE NEW SYMBOL -> BUILD TWICE (`136`). `-AutoLevel` still does nothing.**
>
> ```powershell
> .\build.ps1
> .\build.ps1
> ```
> **RUN 1 — BASELINE:** the standing command **plus `-NoParallax`**.
> **RUN 2 — the same, without it.**
> ```powershell
> .\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
>          -WorldUnitsPerMetre 25 -HandUnitsPerMetre 25 `
>          -ViewmodelScale 0.5 -GunOffX 0 -GunOffY 0 -GunOffZ 0 `
>          -AimFromHand -MuzzleOrigin -NoCrouch -HudDepth 0.2
> ```
>
> ## IN EACH RUN: **three shots at KNOWN ANGLES — straight ahead, 45 up,
> ## 90 right — and a NEAR wall then a FAR wall.**
> **`G-210`: the miss must shrink toward zero at BOTH distances in run 2.**
> **THE FIRST SHOT OF ANY RUN USES THE FALLBACK** — `item_related` has not been
> written yet. **By design (`185` B1). Not a failure.**
> **Then `Copy-Item .\gevr.log .\gevr-keep-B1.log` and send it.**
>
> ## ALSO IN THE LEVEL: **the SCALE at 25**, both numbers together, judged
> against a **GUARD** (`159`, `205` §4).

> # ►►►► HISTORY — REBUILD, THEN SCALE, THEN `B1`. `208` INERT. ◄◄◄◄
>
> **`-AutoLevel` DOES NOTHING** — wrong hook, `[MEASURED]` `wfnf=2` (`208` §5).
> **Do not pass it. Do not spend a run on it.** The move is to `viSetFovY` and it
> is one block of code, not a redesign.
>
> ```powershell
> .\build.ps1
> .\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
>          -WorldUnitsPerMetre 25 -HandUnitsPerMetre 25 `
>          -ViewmodelScale 0.5 -GunOffX 0 -GunOffY 0 -GunOffZ 0 `
>          -AimFromHand -MuzzleOrigin -NoCrouch -HudDepth 0.2
> ```
> **Menus crash sometimes — if it bites, relaunch. `-ViRate 60` avoids it at the
> cost of the judder fix (`207`).**
>
> ## IN THE LEVEL, TWO THINGS, IN ORDER:
> **1. THE SCALE at 25.** Both numbers equal (`205` §4). **Judge against a GUARD**
> — a person is known by heart, a doorway is a guess (`159`).
> **2. THEN `B1`** — the parallax. `193` §2's 0.19-0.61 m muzzle. **The one that
> changes where bullets land.**

> # ►►►► HISTORY — AUTOLAUNCH BUILT (INERT). `208`. ◄◄◄◄
>
> **The menu crash is NOT fixed** (`206` has its stack, `207` has the cadence
> finding and found both quick fixes blocked). **`-AutoLevel 33` queues the Dam
> from the title screen so it stops standing between you and a wear test.**
> **One new `RECOMP_PATCH` symbol -> BUILD TWICE (`136`).**
>
> ```powershell
> .\build.ps1
> .\build.ps1
> .\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
>          -WorldUnitsPerMetre 25 -HandUnitsPerMetre 25 `
>          -ViewmodelScale 0.5 -GunOffX 0 -GunOffY 0 -GunOffZ 0 `
>          -AimFromHand -MuzzleOrigin -NoCrouch -HudDepth 0.2 `
>          -AutoLevel 33
> ```
> **CONFIRM: `[gevr] AUTOLEVEL: stage queued from the title screen` in the log.**
> **IF IT HANGS ON THE TITLE the settle delay is too short — SAY SO, DO NOT
> RETRY.** One constant, `GEVR_AUTOLEVEL_SETTLE`.
>
> ## IN THE LEVEL, TWO THINGS, IN THIS ORDER:
> **1. THE SCALE** — 25 u/m, both numbers equal. **Judge against a GUARD.**
> **2. THEN `B1`** — the parallax. `193` §2's 0.19-0.61 m muzzle.

> # ►►►► HISTORY — THE SEAM IS SOLVED AND LOCKED IN. `204`. ◄◄◄◄
>
> **All five terms are HOST DEFAULTS now — an unset launch is the correct one.**
> **`-HandAxisX/-HandAxisZ` are OFF the standing command: they are `-1` by
> default because the MODEL's barrel is `+Z` (`MUZZLENODE Switches[3]`).**
> **BUILD ONCE to pick up the new defaults.**
>
> ```powershell
> .\build.ps1
> .\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
>          -WorldUnitsPerMetre 100 -HandUnitsPerMetre 100 `
>          -ViewmodelScale 0.5 -GunOffY 8 -GunOffZ -2 `
>          -AimFromHand -MuzzleOrigin -NoCrouch -HudDepth 0.2
> ```
> **Confirm once that the unset launch matches what was just worn** — the defaults
> moved, and `133`'s rule is to verify the thing you are about to build on.
>
> ## THEN, IN ORDER:
> **1. THE POSE KNOBS** — `-GunOffY` / `-GunOffZ` / `-ViewmodelScale`. Knob-only,
> no builds, and **judgeable for the first time** now the motion is right.
> **2. `B1`/U-06 THE PARALLAX** — `193` §2's 0.19-0.61 m muzzle. **The next thing
> that changes SHOOTING.** 25 lines from PD, no new symbols.
> **3. `G-194`** the mark test · **4. `U-18`** the per-weapon muzzle (`T2` passed).
>
> ## STILL OPEN, INDEPENDENT: the FOV/scale read (`199` §4), the 2.4% late frames,
> B3's X close, **and THE COMMIT — both repos, nineteen documents overdue.**

> # ►►►► HISTORY — THE GAME READS THE ROW; `G-203`. `203`. ◄◄◄◄
>
> **`[MEASURED]` 734 paired samples: COLUMN `0.00` deg from the true controller
> forward, ROW `54.60`. The drawn gun follows the ROW — mirrored in yaw, and
> diverging in pitch by up to 89 deg ON THE LEFT ONLY. That is the wearer's
> report as arithmetic, and it is the INVERSE ROTATION, not a mirror.**
> **`158` §2's forty-five-document-old open question is CLOSED.**
>
> ## BUILD ONCE (host-side, no new symbols), then the standing command:
> ```powershell
> .\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
>          -WorldUnitsPerMetre 100 -HandUnitsPerMetre 100 `
>          -ViewmodelScale 0.5 -GunOffY 8 -GunOffZ -2 `
>          -HandAxisX 1 -HandAxisZ 1 `
>          -AimFromHand -MuzzleOrigin -NoCrouch -HudDepth 0.2
> ```
>
> ## `G-203` — **aim top-RIGHT: it points top-RIGHT. Sweep LEFT: no lift.**
> **AND NO REGRESSION ON THE THREE ALREADY PASSED:** wrist roll correct, head
> turns do not re-aim, walking stable. **`-NoSeamT` is the before.**
>
> ## THEN THE POSE PASS — `-GunOffY` / `-GunOffZ` / `-ViewmodelScale`, knob-only,
> and only after the motion is confirmed (`185` `T9`).
> ## THEN `G-194`, then **`B1`/U-06 — the next thing that changes SHOOTING.**

> # ►►►► HISTORY — `G-201` PASSED; SWEEP AND SEND THE LOG. `202`. ◄◄◄◄
>
> **`[REPORTED]` *"when you turn your head, the gun does not move."* THE HEAD NO
> LONGER RE-AIMS THE GUN.** And *"the crosshair didn't affect the direction of the
> gun"* is `201` WORKING, not a fault — first build where they are independent.
>
> **THE REMAINING FAULT IS ASYMMETRIC** (right side fine, left side lifts) **and
> NO SIGN OR MIRROR CAN DO THAT — they are symmetric by construction. THE SIGN
> SWEEP IS CLOSED; do not run the remaining combinations.**
>
> ## BUILD ONCE (host-side, no new symbols), then the standing command:
> ```powershell
> .\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
>          -WorldUnitsPerMetre 100 -HandUnitsPerMetre 100 `
>          -ViewmodelScale 0.5 -GunOffY 8 -GunOffZ -2 `
>          -HandAxisX 1 -HandAxisZ 1 `
>          -AimFromHand -MuzzleOrigin -NoCrouch -HudDepth 0.2
> ```
>
> ## THE SWEEP — **repeat exactly what was just described, saying each mark:**
> gun out front · yaw ALL THE WAY RIGHT · back to centre · ALL THE WAY LEFT ·
> up to the TOP-LEFT where it inverts · wrist roll each way.
> **THE RIGHT-HAND HALF IS THE CONTROL** — it is correct, so it is the reference.
>
> ## THEN: `Copy-Item .\gevr.log .\gevr-keep-POSEOUT.log` and send it.
> The new `POSEOUT` line carries `R`'s third ROW and COLUMN (`158` §2's live
> ambiguity) and the game's OWN placement, so the consuming frame is solved
> offline — the way `200` was.

> # ►►►► HISTORY — BUILD TWICE, `G-201`, THE SECOND DRIVER. `201`. ◄◄◄◄
>
> **`G-200` PASSED TWO OF THREE: walking is STABLE (`[REPORTED]` *"it didn't move
> or adjust position"*), and dropping the legacy axis signs fixed the ROLL.**
> **NEW DEFAULTS: `-HandAxisX 1 -HandAxisZ 1`** — `155`'s `-1 -1` were measured
> against a frame that no longer exists.
>
> **THE REMAINING YAW IS NOT THE SEAM** (`[MEASURED]` 0.14 deg drift) **— it is
> `163`'s `gun_azimuth` write, which feeds `field_FFC` and turns the gun MODEL a
> second time, from a HEAD-RELATIVE term.** Now gated, DEFAULT OFF.
> **ONE NEW SYMBOL -> BUILD TWICE (`136`).**
>
> ```powershell
> .\build.ps1
> .\build.ps1
> .\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
>          -WorldUnitsPerMetre 100 -HandUnitsPerMetre 100 `
>          -ViewmodelScale 0.5 -GunOffY 8 -GunOffZ -2 `
>          -HandAxisX 1 -HandAxisZ 1 `
>          -AimFromHand -MuzzleOrigin -NoCrouch -HudDepth 0.2
> ```
>
> ## `G-201` — **hold the gun STILL, turn your head. IT MUST NOT RE-AIM.**
> Confirm no regression: **wrist rolls correctly, walking stays stable.**
> **THE CROSSHAIR WILL STILL MOVE ACROSS THE SCREEN — that is CORRECT** (`201` §2)
> and it is the first build in which it is visibly true.
>
> ## THEN the POSE pass (`-GunOffY`/`-GunOffZ`/`-ViewmodelScale`), knob-only.

> # ►►►► HISTORY — SOLVED FROM THE RECORDING; `G-200`. `200`. ◄◄◄◄
>
> **`[MEASURED]` 744 poses / 83 head-only transitions: `Rhand` drifts 0.14 deg;
> EVERY form with a head term drifts 4.18-4.41 against the head's own 4.34.
> THE HEAD ROTATION WAS BEING APPLIED TWICE.** `-SeamFrame 2` is the new default
> (`1` = `173`, `0` = legacy). **The position takes the same answer: raw
> play-space hand. `194`'s room term is SUBSUMED, not added twice.**
>
> ## BUILD ONCE, then the standing command — **no new flags**:
> ```powershell
> .\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
>          -WorldUnitsPerMetre 100 -HandUnitsPerMetre 100 `
>          -ViewmodelScale 0.5 -GunOffY 8 -GunOffZ -2 `
>          -HandAxisX -1 -HandAxisZ -1 `
>          -AimFromHand -MuzzleOrigin -NoCrouch -HudDepth 0.2
> ```
>
> ## `G-200` — **NO SHOOTING.**
> **1.** Head turns and tilts, gun still: **THE GUN MUST NOT RE-AIM.**
> **2.** Wrist twist: **rolls IN PLACE, no letter-C arc.**
> **3.** Walk: **comes with you — and NOT at double speed** (that would be the
> room term counted twice).
>
> ## **JUDGE MOTION FIRST, POSE SECOND.** `-HandAxis*` / `-GunOff*` were tuned
> against the legacy frame (`185` `T9`); a wrong ANGLE or OFFSET now is those
> knobs, not the frame, and re-tuning them is knob-only and comes AFTER.

> # ►►►► HISTORY — `T9` FAILED; RECORD THE POSES. `199`. ◄◄◄◄
>
> **Both compositions are falsified in the headset. EIGHT candidates exist; two
> have cost a wear test each. STOP GUESSING — RECORD.**
>
> ## BUILD ONCE (host-side), then run WITHOUT `-SeamCompose`:
> ```powershell
> .\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
>          -WorldUnitsPerMetre 100 -HandUnitsPerMetre 100 `
>          -ViewmodelScale 0.5 -GunOffY 8 -GunOffZ -2 `
>          -HandAxisX -1 -HandAxisZ -1 `
>          -AimFromHand -MuzzleOrigin -NoCrouch -HudDepth 0.2
> ```
>
> ## THE SEQUENCE — ONE MOTION AT A TIME, **PAUSE BETWEEN**, say each out loud:
> **1** stand still 5 s · **2** YAW head L/R (gun still) · **3** ROLL head L/R ·
> **4** PITCH head up/down · **5** TWIST wrist CCW/CW (head still) · **6** WALK
> forward/back/left/right. **Nothing to aim. Nothing to shoot.**
>
> ## THEN: `Copy-Item .\gevr.log .\gevr-keep-POSEREC.log` and send it.
> **The composition is solved offline from twelve numbers — no headset, no
> further guesses.**

> # ►►►► HISTORY — `G-197` PARTIAL. `T9` NEXT. `198`. ◄◄◄◄
>
> **`[REPORTED]` *"I tilt my head to the left, the gun will tilt to the right BUT
> COME TO THE LEFT WITH ME."* THE POSITION FOLLOWS NOW; THE ORIENTATION STILL
> INVERTS.** `197` only ever claimed the position (`197` §3).
>
> **EVERY REMAINING SYMPTOM IS ROTATIONAL** — *"it's TURNING and going in that
> direction"*, and twisting the hand sweeps the gun *"on a big letter C"* instead
> of rolling in place. **`173` wrote the fix and never wore it.**
>
> ## RUN — the standing command PLUS ONE FLAG. Nothing else changes.
> ```powershell
> .\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
>          -WorldUnitsPerMetre 100 -HandUnitsPerMetre 100 `
>          -ViewmodelScale 0.5 -GunOffY 8 -GunOffZ -2 `
>          -HandAxisX -1 -HandAxisZ -1 `
>          -AimFromHand -MuzzleOrigin -NoCrouch -HudDepth 0.2 `
>          -SeamCompose 1
> ```
> **`T9`: hand held STILL, head turning — THE GUN MUST NOT RE-AIM. Then tilt — it
> must roll IN PLACE, not sweep an arc.**
>
> ## **EXPECTED IF IT PASSES:** `-HandAxis*` and `-GunOff*` were tuned against the
> OLD composition and will need re-checking. **AFTER, never during** (`185` `T9`).

> # ►►►► HISTORY — `G-197` FIRST, THE POSITION TRANSPOSE. `197`. ◄◄◄◄
>
> **`[READ]` the hand POSITION used `Rhead` while the aim ray uses `Rhead^T`, ten
> lines apart in `hand_override`. `ge_vr_quat_to_basis` maps LOCAL->WORLD, so the
> position needed the transpose and never had it.** Invisible facing forward;
> **it is every head-turn report this project has ever had** (`173`, `192`, `197`).
> **`194`'s room term takes the same transpose and the same knob.**
>
> ## `G-197` — **NO SHOOTING.**
> **Turn your head and body: THE GUN MUST STAY IN FRONT OF YOU. Tilt your head: it
> must stay put. Walk: it must come with you, not sink or veer.**
> **`-NoHandPosT` reproduces the inversion on purpose.**
>
> ## THEN `G-196` (walk, gun stays in hand), THEN `G-194` (the mark test).
> ## `T9` / `-SeamCompose 1` IS STILL SEPARATE — it is the ROTATION half.
>
> ## NOTE: `vr.ps1`'s stereo verdict describes the **PREVIOUS** run, not the one
> you are about to judge. `197` §4.

> # ►►►► HISTORY — THE TERM MOVED. `G-196`, THEN `G-194`. `196`. ◄◄◄◄
>
> **`[REPORTED]` the gun moves OPPOSITE to the wearer, in BOTH arms — `195` §3's
> "the picture was already correct" is RETRACTED.** The room term now lives in
> `handPos` (above every consumer) and is REMOVED from `muzzle_origin`.
> **ONE BUILD. Host-side only.**
>
> ## `G-196` — **NO SHOOTING. Hold the gun still and WALK: forward, back, left,
> ## right. THE GUN MUST STAY WITH YOUR HAND.** `-NoRoomOrigin` reproduces the
> inversion on purpose. **This gate comes FIRST — `G-194` cannot be judged while
> the gun is sliding.**
>
> ## THEN `G-194` (`195` §2), then `T9` (`-SeamCompose 1`, its own launch).
>
> ## ►► AND A PERFORMANCE NUMBER TO CARRY FORWARD: `[MEASURED]` `LATE 2.4%`
> (93 of 3925), against `147`'s **0/91** and the old build's **18%**.
> **The character stutter is `RB-03` (world at 60 steps) and is NOT the GPU.**
> **The 2.4% is real and new. `185` `D4` owns it — BISECT, do not guess.** `196` §5b.
> **AND THE VIRTUAL SCREEN IS ALREADY ELIMINATED BY A READ:** `[READ]`
> `ge_vr_xr.cpp:2288` — the draw is inside the NO-EYE-PAIR branch, so it runs in
> menus and cutscenes and **costs nothing in gameplay.** `178` ungated PSO
> CREATION, not the draw. **FIRST STEP IS `-NoXr -ViRate 90`** (`118`'s
> de-risker): no headset time, no B3 risk.

> # ►►►► HISTORY — `194`'s ROOM ORIGIN BUILT. `195`. ◄◄◄◄
>
> ## BUILD — **ONCE IS ENOUGH.** Host-side only; no new `RECOMP_PATCH` symbols
> (`136` does not apply), no `115` header, zero game symbols.
> ```powershell
> cd C:\Users\pdbar\Desktop\GoldenEye64Recomp
> .\build.ps1
> ```
>
> ## RUN — the standing command, unchanged. Then the same command `-NoRoomOrigin`.
> ```powershell
> .\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
>          -WorldUnitsPerMetre 100 -HandUnitsPerMetre 100 `
>          -ViewmodelScale 0.5 -GunOffY 8 -GunOffZ -2 `
>          -HandAxisX -1 -HandAxisZ -1 `
>          -AimFromHand -MuzzleOrigin -NoCrouch -HudDepth 0.2
> ```
>
> ## `G-194` (CORRECTED — `195` §2; the `194` §3 wording was geometrically wrong)
> **HIT A MARK FROM THE CENTRE. THEN STEP AS FAR SIDEWAYS AS YOU CAN, RE-AIM AT
> THE SAME MARK, AND FIRE. IT MUST STILL HIT.**
> **`-NoRoomOrigin` is the before: from off-centre it should MISS, by roughly how
> far you stepped.** **JUDGE THE DIFFERENCE BETWEEN THE ARMS** — a residual miss
> present in BOTH is the muzzle parallax (`193` §2) and belongs to `B1`.
> **Sign check: a miss of TWICE your displacement means the term is inverted.**
> **AND THE DRAWN GUN MUST NOT MOVE — a viewmodel that slides is a BUG** (`195` §3).
>
> ## THEN `B1`/U-06 — and NOT before `G-194` passes.

> # ►►►► HISTORY — NEXT BUILD IS `194`'s ROOM ORIGIN, BEFORE `B1`. ◄◄◄◄
>
> **`193` §4's read is done (`194`): the roomscale head translation reaches the
> RENDERED VIEW and never reaches the game's shooting frame, while the muzzle
> origin is `hand - head`. SO HOW FAR YOU HAVE STEPPED IS A PURE ERROR IN THE
> BULLET'S ORIGIN.**
>
> ## THE BUILD — host-side, one addition, one knob, ZERO new symbols
> `origin = (hand - head) + (head - gameCamera)`, second term taken from
> `ge_vr_head_transform`'s `m[3][*]`, NOT re-derived (`25`). Knob `-NoRoomOrigin`.
>
> ## **`G-194`, AND IT NEEDS NO INSTRUMENT:** put a shot on a mark from the centre
> of your space. **Step half a metre sideways WITHOUT CHANGING WHERE THE GUN
> POINTS. Fire again. The two impacts must agree** — today the gap should be about
> how far you stepped.
>
> ## THEN, IN ORDER: **`B1`/U-06 parallax** (`193` §2) · **`U-18` per-weapon muzzle**
> (`193` §3, `T2` PASSED) · **`T9` `-SeamCompose 1`** (its own launch) ·
> **`noPose`/`U-21`/`U-22`** on whichever build is next.
>
> ## STILL `taskkill`, NOT THE X. COPY THE LOG ASIDE FIRST.

> # ►►►► HISTORY — `T7` ANSWERED FROM THE LOG. `T2` PASSED. `193`. ◄◄◄◄
>
> **DO NOT RE-RUN `T7` TO GET THE ANSWER — 55 logged shots already carry it.**
> **`[MEASURED]` the crosshair and the bullet agree with the render frustum
> (X 1.248 vs 1.253, Y 0.953 vs 0.966, flat with eccentricity) — the projection is
> INNOCENT.** **`[MEASURED]` the bullet's ORIGIN sits 0.19-0.61 m from the eye and
> wanders ~0.4 m laterally — that is the MISS-SHRINKS branch.**
>
> ## **NEXT IS A BUILD, AND IT IS `185` `B1` / U-06.**
> PD's `vrComputeCrosshairParallax`, fed from `item_related`, fallback 50000.
> **`189` §2 and `192` already cleared its blockers.**
>
> ## **`T2` PASSED — mark it.** `Switches[3]` = `(0,56.7,350.3)` pistol vs
> `(0,23.3,705.7)` on a second weapon. **`U-18` proceeds.**
>
> ## STILL OWED AS RUNS: **`T9` (`-SeamCompose 1`, its own launch)** and, before
> any further aim work, **the `193` §4 READ** — does roomscale head translation
> reach the game's camera frame or only the rendered view?
>
> ## STILL `taskkill`, NOT THE X. COPY THE LOG ASIDE FIRST.

> # ►►►► HISTORY — `G-A3` PASSED AT `-HudDepth 0.2`. `192`. ◄◄◄◄
>
> **`-HudDepth 0.2` IS NOW PART OF THE STANDING COMMAND** until `B1` replaces it.
>
> ## STEP 1 — `T7`, THE DISTANCE TEST. **NOTHING CHANGES BUT THE WALL.**
> ```powershell
> .\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
>          -WorldUnitsPerMetre 100 -HandUnitsPerMetre 100 `
>          -ViewmodelScale 0.5 -GunOffY 8 -GunOffZ -2 `
>          -HandAxisX -1 -HandAxisZ -1 `
>          -AimFromHand -MuzzleOrigin -NoCrouch -HudDepth 0.2
> ```
> **Wall at ARM'S LENGTH, then the SAME SPOT across the room. Miss SHRINKS ->
> muzzle parallax, `B1` is the cure. Miss HOLDS -> a constant angular error.**
>
> ## STEP 2 — `T9`, ITS OWN LAUNCH. **ADD `-SeamCompose 1`, CHANGE NOTHING ELSE.**
> **Hand held STILL, head turning left and right: THE GUN MUST NOT RE-AIM.**
> `[REPORTED]` twice now (`173`, `192` §2). **If it passes, `-HandAxis*` and
> `-GunOff*` were tuned against a reference that no longer exists — expected, not
> a surprise.**
>
> ## COPY THE LOG ASIDE BEFORE EACH CLOSE. STILL `taskkill`, NOT THE X.

> # ►►►► HISTORY — NO-BUILD SESSION: `-HudDepth`, THEN `T7`. `191`. ◄◄◄◄
>
> **`A3` NEEDS NO CODE — its premise is retracted (`191` §1): `0.1867` is already
> exactly `(tanR+tanL)/(tanR-tanL)` for the LIVE tangents.**
>
> ## STEP 1 — `G-A3`, THREE LAUNCHES, ONE ARGUMENT CHANGING
> ```powershell
> .\vr.ps1 <standing command> -NoCrouch -HudDepth 2.0
> .\vr.ps1 <standing command> -NoCrouch -HudDepth 1.0
> .\vr.ps1 <standing command> -NoCrouch -HudDepth 0.5
> ```
> **HALVE, NEVER NUDGE (`159`). GATE: ONE FUSED CROSSHAIR, in the same world place
> with either eye closed.** If one fuses, **REPORT THE VALUE** — it becomes a
> default, not a knob (`174`).
>
> ## STEP 2 — `T7`/`B2`, SAME SESSION, ON WHATEVER DEPTH FUSED
> **Shoot a wall at ARM'S LENGTH, then the SAME SPOT from across the room.**
> **Miss SHRINKS -> muzzle parallax, `B1` is the cure. Miss HOLDS -> a constant
> angular error in the ray.** Drop `-NoCrouch` only for `T10`, never here.
>
> **`noPose`, `U-21`, `U-22` ALL WAIT FOR THE NEXT BUILD.** This session is worth
> more with nothing compiled.
>
> ## STILL `taskkill`, NOT THE X. `187` §3.

> # ►►►► HISTORY — `G-A1` PASSED. `190`. ◄◄◄◄
>
> **`[REPORTED]` *"the target followed my hand direction"*, and on a LEVEL sweep it
> rests at the MIDDLE of the right edge — independent axes. BOTH HALVES PASS.**
> **`A1` IS DONE. `A2` IS CLOSED (`189`). `A3` AND `B2` ARE BOTH UNBLOCKED.**
>
> ## THE NEXT BUILD IS `185` `A3` — derive the cyclopean HUD shift, do not dial it.
> **Ride the `noPose` counter with it** (`190` §3): `aimed` and `refused` are both
> incremented inside the pose branch, **so a tracking dropout is counted in
> neither and is invisible in `A1-VERIFY`.** One counter, no behaviour change.
>
> ## NOT ON THE CRITICAL PATH, BOTH RECORDED IN `169`:
> **`U-21`** the sight pins with its centre ON the frame edge (the stock
> `[3, w-4]` clamp; fix OUR clamp, **never the cone**).
> **`U-22`** hold the aim on a lost pose instead of gliding to centre — **and do
> not land it in the same run as an aim change** (`48` rule 5).
>
> ## STILL `taskkill`, NOT THE X. `187` §3.

> # ►►►► HISTORY — THE RUN HAPPENED. THE LOG SIDE PASSED. `189`. ◄◄◄◄
>
> **`CONE=2455 = BAND=2455`, `coneOff=0`, `noFrus=0` — the clamp engaged on every
> frame that needed it.** **`origin=(0,10)` — `A2` IS CLOSED, NOT A FAULT.**
>
> ## **DO NOT RE-RUN THE LOG READ. THE OPEN QUESTION IS WHAT IT LOOKED LIKE:**
> **sweep slowly right — CONTINUOUS travel to the edge, then a clean STOP, no
> corner snap; and on a DIAGONAL sweep the two axes saturating INDEPENDENTLY.**
>
> ## **CORRECTION TO THE BLOCK BELOW: `SAT=` DOES NOT FALL.** It is a
> BEFORE-figure now, like `BAND` (`188` §2 re-pointed both at the pre-cone
> values). **The log-side gate is `CONE == BAND` with `coneOff=0`.** `189` §3.
>
> ## **AND `A3` IS UNBLOCKED IF `G-A1` PASSES.** `B2` is unblocked already.

> # ►►►► HISTORY — NEXT RUN IS `G-A1`. `A1` IS BUILT AND UNRUN. `188`. ◄◄◄◄
>
> ## BUILD — **TWICE.** One new `RECOMP_PATCH` symbol (`136`). No `115` header.
> ```powershell
> cd C:\Users\pdbar\Desktop\GoldenEye64Recomp
> .\build.ps1
> .\build.ps1
> ```
>
> ## RUN — the standing command below, unchanged, **PLUS `-NoCrouch`.**
> **SWEEP SLOWLY: right, left, up, down, and DIAGONALLY — dwelling past the point
> where the crosshair stops.** **NO SHOTS NEEDED.** Both instruments are populated
> by aiming alone.
>
> ## READ THE LOG
> ```powershell
> Select-String -Path .\gevr.log -Pattern "A1-VERIFY|WIDE-frustum|BULLET aim=" | Select-Object -Last 8
> ```
> - **`noFrus` LARGE -> STOP, the run is not evidence** (unchanged, `186` §3).
> - **`CONE=` non-zero and tracking `BAND=`, `SAT=` at zero -> `G-A1` PASSING.**
> - **`BAND` large with `CONE=0` -> THE FIX IS INERT**, not working. Do not tune
>   it; find out why it did not run. `coneOff=` says if the knob is the reason.
> - **`BAND=` is the PRE-cone geometry on purpose** (`188` §2) — it is the
>   before-figure, and it should NOT fall. `2846` of `8548` is the baseline.
> - **`origin=(0,10)` on the `WIDE-frustum` line -> `A2` CLOSES as correct all
>   along.** `origin=(0,0)` -> the ten-pixel drop is real; `188` §3 has the next
>   two candidates.
>
> ## IN THE HEADSET — `G-A1`
> **Sweep slowly RIGHT: the crosshair moves CONTINUOUSLY to the edge and STOPS.
> No jump, no corner snap. Then DIAGONALLY: the two axes must saturate
> INDEPENDENTLY.** If it passes, **`A3` is unblocked** (`185`).
>
> ## STILL `taskkill`, NOT THE X. `187` §3.

> # ►►►► HISTORY — `A1-VERIFY` HAS BEEN RUN. IT PASSED. `187`. ◄◄◄◄
>
> **`[MEASURED]` `gevr-keep-A1VERIFY-crash.log`:
> `aimed=8548 refused=936 | INSIDE=5702 BAND=2846 SAT=1424 noFrus=0 |
> maxNx=15376 maxNy=20575`.**
> **`noFrus=0` -> the run is evidence. `BAND` 33% of aimed -> `184` §4 CONFIRMED.**
> **`D1` also PASSED: 99 of 318 `BULLET`/`SIGHT` samples differ, only while
> clamped.** **`A2` confirmed in the same lines: rest `(160,120)` vs centre
> `(160,110)`.**
>
> ## **NEXT IS NOT A RUN. IT IS A BUILD: `185` `A1` + `A2`, plus a
> `begin_shutdown()` entry print.** Then `G-A1` / `G-A2`, then `A3`, then `T3`.
>
> ## ►► AND EVERY "CLOSE WITH THE X" INSTRUCTION IN THIS FILE IS SUSPENDED. ◄◄
> **`[REPORTED]` the X bugchecked the PC again; `[MEASURED]` no `shutdown:` line
> in the log. `181` is INSUFFICIENT, not refuted.** **Use
> `taskkill /F /IM GoldenRecomp.exe`, and COPY `gevr.log` ASIDE BEFORE CLOSING.**
> `187` §3.

> # ►►►► HISTORY — NEXT RUN IS `A1-VERIFY`, AND IT COMES BEFORE `T3`. `186`. ◄◄◄◄
>
> **`185` `D1` IS DONE** — `ge_vr_bindtest.c` now prints the BULLET's own
> selection under `BULLET` and the clamped field under `SIGHT`, with `src=`
> saying which. **`184` §3a's trap is closed.**
>
> **AND `185` `A1`'s VERIFY STEP IS BUILT AND UNRUN.** `182` forbids building on
> `184` §4's `[INFERRED]` band, so **`A1` ITSELF IS DELIBERATELY NOT WRITTEN**
> until this run says whether the band is entered.
>
> ## BUILD — ONCE IS ENOUGH THIS TIME
> ```powershell
> cd C:\Users\pdbar\Desktop\GoldenEye64Recomp
> .\build.ps1
> ```
> **TWO `.c` FILES, NO HEADER CHANGED — `115` does not apply and a PARTIAL build
> is legitimate here.** No new `RECOMP_PATCH` symbols either, so `136` is clear.
>
> ## RUN — THE STANDING COMMAND BELOW, UNCHANGED. NO FLAG ADDED OR REMOVED.
>
> **THEN SWEEP THE GUN WIDE: right, left, up, down, and deliberately PAST the
> point where the crosshair stops moving — AND DWELL THERE, a few seconds each
> way.** The band is only entered if you aim into it, and **the print is once per
> 90 frames, so a fast sweep can pass THROUGH the band between two samples and
> score nothing.** Slow and held beats wide and quick.
>
> **NO SHOTS ARE NEEDED ON THIS RUN.** Both instruments sit in
> `caclulate_gun_crosshair_position_rotation`, the PER-FRAME crosshair update, and
> `g_geVrTrueAimPx` is published in that same path — **they are fully populated by
> AIMING alone.** Firing now costs nothing and proves nothing. **`B1` is the run
> where shots ARE the measurement**, because `item_related` only updates when a
> round LANDS (`185` B1).
>
> **AND `BULLET` vs `SIGHT` ONLY DIVERGE WHILE THE SIGHT IS CLAMPED** — at or past
> the screen edge. **On-screen the two read EQUAL and that is CORRECT**, not a
> fault. So the same dwell-past-the-stop that fills `BAND` is also what proves
> `D1`.
>
> ## READ THE LOG — `noFrus` FIRST, IT CAN VOID THE RUN
> ```powershell
> Select-String -Path .\gevr.log -Pattern "A1-VERIFY|BULLET aim=" | Select-Object -Last 8
> ```
> - **`noFrus` LARGE -> STOP. THE RUN IS NOT EVIDENCE** (`186` §3): the `167`
>   frustum path was refused, `nx`/`ny` are in the game's 106 degree unit, and
>   `|n| == 1` is not the frustum edge.
> - **`BAND` LARGE against `aimed` -> `184` §4 CONFIRMED, build `A1`.**
> - **`BAND` AT OR NEAR ZERO -> FALSIFIED, DO NOT BUILD `A1`** — that is a
>   finding, not a failed session.
> - **`SAT`** is the `162` +-2 clamp firing; `184` measured 290 of 1,313.
> - **`BULLET aim=` and `SIGHT crosshair_angle=`** should DIFFER while
>   `src=TRUEAIM`. Equal with `src=TRUEAIM` would mean U-16 is publishing the
>   clamped value and is its own finding.
>
> **All `A1-VERIFY` numbers are CUMULATIVE and `x1000`.** Report the LAST line.

---

**Rewritten 2026-08-25 as a SEQUENCE. Work top to bottom.**
Working dir for every command: `C:\Users\pdbar\Desktop\GoldenEye64Recomp`

> ## HOW THIS FILE WORKS, AND WHY THE ORDER IS NOT ARBITRARY
>
> **ONE BUILD, THEN ELEVEN RUNS. Each run changes EXACTLY ONE THING.**
>
> The order is chosen so that **no test can invalidate a test above it.**
> Independent systems come first (they cannot be confounded), the aim chain is
> tested from its foundation outward, and the two changes that RE-REFERENCE
> everything else — `T9` seam composition and `T10` crouch — come last.
>
> **Write the result beside each test before moving on.** `108` is why: a session
> ended without writing up and the next one contradicted it.

---

## BUILD FIRST — ONCE

```powershell
cd C:\Users\pdbar\Desktop\GoldenEye64Recomp
.\build.ps1
.\build.ps1
```

**TWICE.** Two new `RECOMP_PATCH`-reachable symbols this round
(`recomp_ge_vr_crouch_state`, `recomp_ge_vr_duck_offset`) — `136`.
**Four headers changed, so it MUST report a FULL REBUILD** (`115`). If it says
partial, run it again.

**Everything below comes out of that one binary.** No rebuilds between tests.

---

## THE STANDING COMMAND

Every test is this line plus or minus ONE flag. **Copy it once; the tests below
name only what changes.**

```powershell
.\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
         -WorldUnitsPerMetre 100 -HandUnitsPerMetre 100 `
         -ViewmodelScale 0.5 -GunOffY 8 -GunOffZ -2 `
         -HandAxisX -1 -HandAxisZ -1 `
         -AimFromHand -MuzzleOrigin -NoCrouch
```

> ### ►► NOTE `-NoCrouch` ON THE STANDING COMMAND. IT IS DELIBERATE. ◄◄
> **Physical crouch is ON by default and it MOVES THE CAMERA.** If it fires while
> you are judging aim — because you leaned to look at something — it silently
> changes the thing you are measuring. **Crouch is disabled for every aim test and
> enabled alone in `T10`.**

**Close every run with:**
```powershell
taskkill /F /IM GoldenRecomp.exe
```

---

# PHASE 1 — INDEPENDENT SYSTEMS. Nothing here can confound anything else.

## T1 — THE VIRTUAL SCREEN `175` / U-19 · **UNTESTED**

**Standing command, unchanged.** Look at the **menus and front end** before
loading anything.

| gate | what to see |
|---|---|
| **G-175-1** | menus show **the game**, in a rectangle at a comfortable distance — not a wall, not a red/blue tint |
| **G-175-2** | ►► **it has DEPTH.** Close one eye, then the other — the screen should shift against the background like a real object at 2.5 m ◄◄ |
| **G-175-4** | the log says `screen (docs\175 U-19): READY` |

```powershell
Select-String -Path .\gevr.log -Pattern "screen \(docs" | Select-Object -Last 2
```

**Adjust if you want:** `-ScreenDist 2.5` (metres away), `-ScreenSize 2.6` (width
in metres; height follows the image's aspect).

**IF IT SAYS `UNAVAILABLE`** the shader failed to build and you will still get
red/blue. That is the designed fallback, not a crash — tell me and continue.

**RESULT:** ................................................................

---

## T2 — THE MUZZLE NODE READ `171` / U-18 · **READ ONLY, NO JUDGEMENT**

**Standing command.** Get into a level, **then switch from a pistol to a rifle**
(or any two different weapons) and close.

```powershell
Select-String -Path .\gevr.log -Pattern "MUZZLENODE" | Select-Object -Last 6
```

**The only question: does `Switches[3]=(x,y,z)` CHANGE between the two weapons?**

- **CHANGES** → per-weapon muzzles are free; `-MuzzleExt` and its three sign knobs
  become unnecessary. U-18 proceeds.
- **IDENTICAL** → it is not a per-weapon muzzle and U-18 is dead. Equally useful.
- **`Switches[3]=absent`** → the node is not present on that weapon at all.

**RESULT: ►► PASSED, 2026-08-25 (`193` §3). IT IS PER-WEAPON. ◄◄**
`[MEASURED]`, one run: pistol `(0, 56.7, 350.3)` on **696** samples;
a second weapon `(0, 23.3, 705.7)` on **40** — **the muzzle is TWICE as far down
the barrel.** `absent` on 518 (no gun model that frame). One further reading,
`(-257.15, 1.29, 0)` with `numSwitches=7`, appeared **ONCE and is evidence of
nothing.**
**`U-18` PROCEEDS.** And it explains `[REPORTED]` *"the secondary gun... sprayed
way off to the right"*: our origin is a FIXED `-GunOffY/-GunOffZ`, `154`'s PISTOL
value.

---

# PHASE 2 — THE AIM CHAIN. Foundation outward. Do NOT reorder.

> **WHY THIS ORDER:** `T3` establishes what "normal" looks like. `T4` is the
> ray's ORIGIN, `T5` its PROJECTION, `T6` its CLAMP — origin before projection
> before clamp, because each later one is measured against the earlier being
> right. `T7` is the diagnostic that decides the next slice, and it needs `T3`-`T6`
> settled to mean anything.

## T3 — AIM BASELINE · establishes the reference

**Standing command, unchanged.** No flag changes. This run is the reference every
test below is compared against.

Note down, roughly:
- Is the crosshair **one object**? (should be — `170`/`173` already passed)
- Where does the shot land relative to the crosshair? *(last measured: ~6 px up,
  ~1 px right — see `images/2026-08-25-crosshair-impact-sketch.png`)*
- Does the aim favour one eye?

```powershell
Select-String -Path .\gevr.log -Pattern "HUD shift|state=|SHOT reported" | Select-Object -Last 10
```

**`state=` must say `APPLIED`. `HUD shift` eye0 and eye1 MUST differ.**

**RESULT:** ................................................................

---

## T4 — THE HEAD ANCHOR `174` · **UNTESTED** · add `-HeadAnchor 0`

```powershell
.\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
         -WorldUnitsPerMetre 100 -HandUnitsPerMetre 100 `
         -ViewmodelScale 0.5 -GunOffY 8 -GunOffZ -2 `
         -HandAxisX -1 -HandAxisZ -1 `
         -AimFromHand -MuzzleOrigin -NoCrouch -HeadAnchor 0
```

**`-HeadAnchor 0` REVERTS to the old left-eye anchor.** So this run should be
**WORSE** than `T3`.

**G-174-1: close each eye in turn.** In `T3` the aim should be equally right (or
equally wrong) from both. **Here it should favour ONE eye** — that is the bug
`174` fixed, reproduced on purpose.

**IF T3 AND THIS RUN FEEL IDENTICAL**, the anchor change did nothing and that is
the finding.

**RESULT:** ................................................................

---

## T5 — THE FOV FIX `167` · **NEVER ISOLATED** · add `-NoAimFrustum`

```powershell
.\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
         -WorldUnitsPerMetre 100 -HandUnitsPerMetre 100 `
         -ViewmodelScale 0.5 -GunOffY 8 -GunOffZ -2 `
         -HandAxisX -1 -HandAxisZ -1 `
         -AimFromHand -MuzzleOrigin -NoCrouch -NoAimFrustum
```

**Reverts to the game's own `c_scale` (fovy 106) instead of the headset's real
tangents.** Expect it to be **WORSE**.

**The specific claim: the crosshair should drift OFF the barrel as you aim UP**,
and be off differently at the sides. In `T3` it should sit on the barrel at every
elevation.

> **`-NoAimFrustum` IS NOT `-AimEstimate`.** The latter reverts the whole
> projected aim to the old gain path and answers a different question. Do not
> substitute one for the other.

**RESULT:** ................................................................

---

## T6 — THE CLAMP SPLIT `172` / U-16 · **UNTESTED** · add `-NoClampSplit`

**First, on the standing command (split ON), aim PAST THE SCREEN EDGE:**

| gate | what to see |
|---|---|
| **G-172-1** | ►► **BOTH halves, or it is not the split** — the crosshair STOPS at the screen edge **AND** the shot keeps tracking the gun ◄◄ |

**Then add `-NoClampSplit` and repeat:**

```powershell
.\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
         -WorldUnitsPerMetre 100 -HandUnitsPerMetre 100 `
         -ViewmodelScale 0.5 -GunOffY 8 -GunOffZ -2 `
         -HandAxisX -1 -HandAxisZ -1 `
         -AimFromHand -MuzzleOrigin -NoCrouch -NoClampSplit
```

**The bullet should now be caught by the clamp too** — aim past the edge and the
shot stops following the gun.

**RESULT:** ................................................................

---

## T7 — ►►►► THE DISTANCE TEST. THE MOST VALUABLE RUN IN THIS FILE. ◄◄◄◄

**Standing command, unchanged.** Nothing new to enable.

**Shoot a wall at ARM'S LENGTH. Then the same spot from ACROSS THE ROOM.**

| what you see | what it means | what I build next |
|---|---|---|
| **the miss SHRINKS with distance** | **muzzle parallax** — the crosshair projects from your head, the bullet leaves the muzzle | **U-06** — PD's `vrComputeCrosshairParallax`. A known, principled cure |
| **the miss STAYS THE SAME SIZE** | **a constant angular error** in the ray itself | I chase it in the ray — an entirely different problem |

> **THESE TWO BEHAVE OPPOSITELY, SO ONE WALL ANSWERS IT.** Everything after this
> depends on which it is. **If you only have time for one test in this file,
> make it this one.**

**RESULT: ►► ANSWERED FROM THE LOG WITHOUT THE WALL, 2026-08-25 (`193`). ◄◄**
**`[MEASURED]`, 55 distinct logged shots: the crosshair and the bullet AGREE.**
`tan(dir)/ndc` medians **X 1.248 / Y 0.953** against the render half-tangents
**1.253 / 0.966**, and **flat across eccentricity** — so it is NOT a constant
angular error and **the projection is innocent.**
**`[MEASURED]` the same shots put the bullet's ORIGIN 0.19-0.61 m from the eye,
wandering ~0.4 m laterally.** Two rays, same direction, different origins.
**THAT IS THE "MISS SHRINKS" BRANCH, AND `B1`/U-06 IS THE NAMED CURE.**
**The wall test is NOT void — it would confirm this in the headset — but it is no
longer the thing that decides what to build.**

---

## T8 — OPTIONAL: MEASURE THE RESIDUAL · `-AimTrimY` / `-AimTrimX`

Only if you would rather hand me a number than do `T7`.

```powershell
.\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
         -WorldUnitsPerMetre 100 -HandUnitsPerMetre 100 `
         -ViewmodelScale 0.5 -GunOffY 8 -GunOffZ -2 `
         -HandAxisX -1 -HandAxisZ -1 `
         -AimFromHand -MuzzleOrigin -NoCrouch `
         -AimTrimY -0.06
```

Dial `-AimTrimY` (try −0.04 to −0.08; negative moves the aim DOWN) and
`-AimTrimX` until the shot sits ON the crosshair. **Then write both numbers
down.** That is a MEASUREMENT, not a fix — the value tells me which physical
quantity it is.

**RESULT:  AimTrimX = ..........   AimTrimY = ..........**

---

# PHASE 3 — THE TWO THAT RE-REFERENCE EVERYTHING. LAST, AND ALONE.

## T9 — THE SEAM COMPOSITION `173` · **UNTESTED** · add `-SeamCompose 1`

```powershell
.\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
         -WorldUnitsPerMetre 100 -HandUnitsPerMetre 100 `
         -ViewmodelScale 0.5 -GunOffY 8 -GunOffZ -2 `
         -HandAxisX -1 -HandAxisZ -1 `
         -AimFromHand -MuzzleOrigin -NoCrouch -SeamCompose 1
```

> ### THE TEST, AND IT NEEDS NO SHOOTING
> **HOLD YOUR HAND COMPLETELY STILL AND TURN YOUR HEAD.**
> **G-173-2: the gun must NOT re-aim.**

You reported it does today. The seam computes `R = Rhead · Rhandᵀ`; the correct
view-space orientation is `R = Rheadᵀ · Rhand` — **and the aim path has always
used `Rheadᵀ`.** If this stops the drift, `166` §4's 17° has its cause.

> ### ►►►► WHY THIS IS SECOND-TO-LAST ◄◄◄◄
> **`-HandAxisX`, `-HandAxisZ`, `-GunOffY` and `-GunOffZ` were ALL tuned against
> the OLD composition** (`154`, `155`). **If this test passes, those four numbers
> are measured against a reference that no longer exists and will need
> re-checking.** Anything tested after this, under this flag, is being judged on
> an untuned grip. **That is why every aim test above runs WITHOUT it.**

**RESULT:** ................................................................

---

## T10 — PHYSICAL CROUCH `176` / U-09 · **UNTESTED** · drop `-NoCrouch`

```powershell
.\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
         -WorldUnitsPerMetre 100 -HandUnitsPerMetre 100 `
         -ViewmodelScale 0.5 -GunOffY 8 -GunOffZ -2 `
         -HandAxisX -1 -HandAxisZ -1 `
         -AimFromHand -MuzzleOrigin
```

**`-NoCrouch` is GONE — that is the only change from `T3`.**

> ### ►► STAND STILL FOR THE FIRST ~90 FRAMES OF THE LEVEL. ◄◄
> **That is the calibration — a 90-sample median of your standing head height.**
> If you start crouched or leaning, the reference is wrong and everything reads
> too tall. Confirm it happened:

```powershell
Select-String -Path .\gevr.log -Pattern "CROUCH calibrated" | Select-Object -Last 1
```

| gate | what to see |
|---|---|
| **G-176-1** | ►► **THE REQUIREMENT. Let a guard SEE you, then physically crouch. HIS SHOTS MUST GO LOWER.** ◄◄ |
| **G-176-3** | **NO DOUBLE CROUCH.** The view drops by exactly as much as your head did, and no more |
| **G-176-4** | movement slows while squatting, and recovers when you stand |
| **G-176-2** | in the log, `crouchpos=` and `vrCrouch=` **AGREE** once calibrated |

```powershell
Select-String -Path .\gevr.log -Pattern "crouchpos=" | Select-Object -Last 4
```

**IF `crouchpos` AND `vrCrouch` DISAGREE, the write is not landing** — and that
looks identical in the headset to the feature not existing.

**`-CrouchHeight 1.6`** sets your standing EYE height in metres if the default
thresholds feel wrong. **`-NoCrouch`** turns it off entirely.

**RESULT:** ................................................................

---

## T11 — REGRESSION CHECK · `-NoXr`

```powershell
.\vr.ps1 -NoXr
```

**The flat game must behave exactly as stock** — button crouch normal, aim normal,
crosshair normal. **Every VR path above is gated and must be inert here.**
If anything differs, a gate leaked.

**RESULT:** ................................................................

---

# PHASE 4 — ALSO OWED AT THE RIG, AND NOT IN THE ELEVEN

**Added 2026-08-26 after auditing `TESTS-OWED-ON-RETURN.md` against the corpus.
That file is mostly HISTORY — most of what it lists is closed. These are the
items that survived the audit. THEY DO NOT OUTRANK `T1`-`T11`.**

## T12 — `ds_option 2` AS THE DEFAULT · **A DECISION, NOT AN EXPERIMENT**

**Already measured free** — `111` §4: 60 fps, 90 eye passes, `LATE` 17% -> **12%,
BETTER than baseline**, and it kills the distant shimmer (`108` §3). `113` and
`114` §213 both list it as an outstanding free win.

**What is owed is the DECISION and one confirming run.** It rides along on any
run above.

```powershell
$g = "$env:LOCALAPPDATA\GoldenRecomp\graphics.json"
(Get-Content $g -Raw) -replace '"ds_option"\s*:\s*\d+', '"ds_option": 2' | Set-Content $g
```

**`msaa_option` STAYS `"None"`. Not negotiable — `43`.** The in-game graphics
menu REWRITES this file, so re-check after any menu visit (`108` §4).

**Optional curve:** try `4`. **If 4 is SLOWER than 2, that is `49`'s O22
reproducing on demand, which nobody has ever pinned down** — worth more than the
AA result itself.

**RESULT:** ................................................................

---

## T13 — CONFIRM O97 IS CLOSED · **ONE READ, NO EXTRA RUN**

`109` found ~1 frame in 6 missing the 11.11 ms deadline, intermittently, and
nobody explained it. **`147` then recorded `LATE 0/91` at ninety, down from
`16/91 (18%)`.** Route B appears to have dissolved it.

**So this is no longer a workstream — it is a confirmation.** Any run above,
60+ seconds, then:

```powershell
Select-String -Path .\gevr.log -Pattern "stage MAX ms:" | Select-Object -Last 4
```

**`LATE` at or near 0/N -> O97 CLOSES.** Anything like 1-in-6 returning means
`147`'s run was the lucky one and it was never about pacing.

**RESULT:** ................................................................

---

## ►►►► B3 AND B4 — STILL BLOCKING, AND WORSE THAN THE OLD FILE SAYS ◄◄◄◄

**NOT A TEST YOU RUN. A DECISION THAT HAS BEEN MADE BY DEFAULT FOR FIVE
SESSIONS**, and `39` has had both marked BLOCKING since `75`.

**B4 WAS RE-RUN ON PURPOSE, 2026-08-24, WITH `149`'s FIX COMPILED IN, AND THE X
STILL BUGCHECKS THE MACHINE.** `147`: **there is no `shutdown:` line in the log
at all** — the log simply stops mid-gameplay at `90.0 fps | LATE 0/91`. On the X
path **`xr_shutdown` NEVER RUNS**, which is `42`'s exact recorded signature.

> **`149` IS NOT REFUTED. IT IS INSUFFICIENT.** The fix has to move EARLIER — to
> `begin_shutdown()` at the SDL_QUIT moment, `42`'s territory.

**B3 costs a reboot per occurrence, so it is not something to poke at casually
mid-test-script.** It belongs to a session that starts with it, not one that
ends up in it.

---

## THE COMMIT — OWED, AND NOW SIX SESSIONS DEEP

**Neither repo has a remote of ours. All of this work exists on one disk.**

```powershell
cd C:\Users\pdbar\Desktop\GoldenEye64Recomp
git status --ignore-submodules=all
cd C:\Users\pdbar\Desktop\GoldenEyeVR
.\commit-session.ps1 -Message "<your message>"
```

**`-Message` IS MANDATORY — `120` §1.** The old script committed under a
hardcoded subject and three commits already share it. **`-DryRun` stages and
lists without committing.** On Windows, not through the bridge — `48`.

**`git status` on `GoldenEye64Recomp` times out because it recurses submodules;
use `--ignore-submodules=all`.**

**AND IT IS YOURS. Sessions never stage, commit, branch or merge.**

---

# THE OFF-SWITCH TABLE — everything, from one build

| flag | what it reverts | tested in |
|---|---|---|
| `-NoHudShift` | per-eye HUD shift → crosshair doubles again | *(already passed)* |
| `-HudSign -1` | flips the HUD shift if the derivation is wrong | *(spare)* |
| `-HeadAnchor 0` | head-centre anchor → left-eye anchor | **T4** |
| `-NoAimFrustum` | the FOV fix → game `c_scale` | **T5** |
| `-NoClampSplit` | the clamp split → bullet caught by the edge clamp | **T6** |
| `-AimTrimX/Y` | measurement trim, NDC | **T8** |
| `-SeamCompose 1` | **turns ON** the corrected seam composition | **T9** |
| `-NoCrouch` | physical crouch off | **T10** |
| `-ScreenDist` / `-ScreenSize` | move / resize the virtual screen (metres) | **T1** |
| `-AimEstimate` | whole projected aim → old gain path | *(different question)* |
| `-FreeAim` | `153`'s blunt unclamp — superseded by `-NoClampSplit` | *(historic)* |

---

# STANDING PRECONDITIONS — every run

- **HEADSET ON, THEN LAUNCH.** Three confounded runs already (`O60`).
- **WAKE THE CONTROLLERS and hold them in view before launching.** One run had
  `handValid=0` on 91 of 99 samples with the good ones only in the last ten frames.
- **AUTO-AIM IS OFF** in the in-game options (`157` §6.2). Confirm before comparing.
- **CLOSE WITH `taskkill /F /IM GoldenRecomp.exe`. NEVER THE X** — `6D-00`/B3 still
  bugchecks and `149`'s fix is in code the X path never reaches.

# THE ONE-LINE LOG READ, AFTER EVERY RUN

```powershell
Select-String -Path .\gevr.log -Pattern "screen \(docs|CROUCH calibrated|HUD shift|MUZZLENODE|state=|SHOT reported|crouchpos=" | Select-Object -Last 16
```

# GIT — OWNER ONLY

**Standing policy: every commit is yours.** Sessions never stage, commit, branch
or merge. There is uncommitted work in the tree from today; `git status` before
you start, so a failed test can be reverted cleanly.
