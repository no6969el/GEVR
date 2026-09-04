# 185 — THE EXECUTION PLAN. GROUPED, PRIORITISED, AND SPLITTABLE ACROSS SESSIONS.

**2026-08-26. Written to be handed to a session that was not here.**
**Tiers per `182`. Every commit is the owner's (`00-START-HERE`).**

> # ►►►► HOW TO USE THIS FILE ◄◄◄◄
>
> **SEVEN GROUPS. Each group is INTERNALLY ORDERED and can be taken whole by one
> session.** Groups `A`-`C` are the critical path; `D`-`G` are parallel or
> trailing. **Dependencies are stated per task and are the ONLY ordering that
> matters between groups.**
>
> **EVERY TASK HAS A GATE.** If the gate cannot be stated, the task is not ready
> to start. **`182`: an `[INFERRED]` claim may not be built on** - tasks resting
> on one carry a VERIFY step before their build step, and it is not optional.
>
> **DO NOT BATCH BEHAVIOUR CHANGES.** One build may carry many; one RUN changes
> ONE thing (`48` rule 5). Every behaviour change ships with its own off switch.

---

# GROUP A — THE AIM GEOMETRY. **CRITICAL PATH. NOTHING ELSE IN AIM IS JUDGEABLE UNTIL THIS IS DONE.**

**WHY FIRST:** `[REPORTED]` *"nothing is related to where you're pointing it"*,
and `184` §4 traced it to a real mechanism. **Every other aim task is measured
against a crosshair that is currently being flung off-frame** - so their results
would be noise.

### A1 — BOUND THE DIRECTION TO THE FRUSTUM CONE BEFORE PROJECTING
> ## ►►►► **DONE. VERIFIED, BUILT, WORN, PASSED.** `187` -> `188` -> `190`. ◄◄◄◄
> The VERIFY step below was run and CONFIRMED the band (`BAND=2846/8548`,
> `noFrus=0`). Built with `-NoAimCone`. **`G-A1` PASSED BOTH HALVES:**
> `[REPORTED]` *"the target followed my hand direction"*, and a LEVEL sweep rests
> at the MIDDLE of the right edge — **the axes saturate independently.**
- **THE FAULT** `[READ]` `ge_vr_aim.c:283` / `rt64_render_context.cpp:1483`:
  the refusal is `fwd[2] < -0.05f`, **~87 degrees, against a ~50 degree
  frustum.** Between them the divide returns finite, legal, enormous values.
  `162` P0-3(b) clamped the RESULT to +-2 NDC; `[MEASURED]` +-2 NDC on 320x220
  **is exactly `(480,340)`, and 290 of 1,313 samples sit on it.**
- **WHY THE EXISTING CLAMP IS NOT ENOUGH:** it collapses a 37-degree band of
  DIFFERENT gun directions onto ONE screen point. **That is the quadrant.**
- **DO:** clamp the DIRECTION into the frustum cone (per-axis tangent limits,
  from the live headset tangents `167` already establishes) **before** the
  divide. The projection then stays monotonic to the edge and beyond it pins
  smoothly rather than snapping.
- **KNOB:** `-NoAimCone` reverts to today exactly.
- **GATE `G-A1`:** sweep the gun slowly right. **The crosshair must move
  CONTINUOUSLY to the edge and STOP there** - no jump, no corner snap. Repeat
  diagonally: **the two axes must saturate INDEPENDENTLY**, not both to a corner.
- **`[INFERRED]` - VERIFY FIRST:** log `fwd[]` and the pre-clamp NDC for one run
  and confirm the 50-87 degree band is actually being entered. **Do not build on
  the inference alone.**

### A2 — THE TEN-PIXEL DROP
> ## ►►►► **CLOSED. IT WAS NEVER A FAULT.** `189` §2. ◄◄◄◄
> `[MEASURED]` `origin=(0,10)`: `c_screentop` is the `(240-220)/2` letterbox, and
> `[READ]` `bondview.c:724` puts the game's OWN projection centre at
> `c_screentop + c_halfheight`. **Rest at `(160,120)` IS dead centre.** The
> measurement was right and the baseline it was compared against was wrong.
> **AND THIS UNBLOCKS `B2` EARLY — the "constant 10 px masquerading as
> miss-HOLDS" confound below does not exist.**
- **`[MEASURED]`** rest position `(160,120)`; screen `320x220`, so centre is
  `(160,110)`. **Ten pixels low, constant, 377 samples.**
- **NOT PARALLAX** - a fixed offset does not shrink with distance. Do NOT let
  Group B absorb it.
- **DO:** a read. Candidates in order: `c_screentop` / `screenheight` halving in
  the NDC inversion (`ge_vr_aim.c:315`); the `220` vs `240` constant seen at
  `ge_vr_aim.c:650` (`getPlayer_c_screenheight() / 240.0f`); the HUD's own
  vertical origin.
- **GATE `G-A2`:** with the gun level and still, the rest crosshair sits at
  `(160,110)` in the log. **A number, not an impression.**
- **DEPENDS ON:** nothing. **Can be read in parallel with A1.**

### A3 — THE HUD SHIFT MAGNITUDE
> ## ►►►► **DONE. `G-A3` PASSES AT `-HudDepth 0.2`, WITH NO BUILD. `192` §1.** ◄◄◄◄
> **`[REPORTED]` *"0.2 is the one that actually worked."*** The cause was the HUD
> at INFINITY, not a wrong magnitude. **RECORD THE VALUE, DO NOT LEAVE IT A KNOB
> (`174`) — and note `0.2 m` is NEARER THAN THE GUN**, which is itself a finding
> `B1` is expected to supersede.
>
> ## ►►►► **AND THE `[INFERRED]` "32% TOO MUCH" BELOW IS RETRACTED. `191` §1.** ◄◄◄◄
> **`[MEASURED]` `0.1867` is EXACTLY `(tanR+tanL)/(tanR-tanL)` for the LIVE
> tangents `-1.4869, 1.0190`.** The `-0.1411` was computed from the
> `[gevr] tangents` line, which is `loggedFull` — **printed ONCE at startup,
> 29 log lines BEFORE the runtime delivered any live FOV.** That is the constant
> table, not the render. **THE SHIFT IS ALREADY DERIVED CORRECTLY; DO NOT DIAL
> IT.** The `[REPORTED]` separation stands and has another cause —
> **leading candidate: the HUD sits at INFINITY by construction and the wearer is
> verged much nearer. `-HudDepth` ALREADY EXISTS AND NEEDS NO BUILD.** `191` §3.
- **`[MEASURED]`** applied `eye0=0.1867 eye1=-0.1867`.
- **`[REPORTED]`, AND IT IS A MEASUREMENT:** *"the left eye's right side of the
  cross and the right eye's left side overlap perfectly"* - **the separation is
  EXACTLY ONE CROSSHAIR WIDTH.**
- **`[INFERRED]`** from this run's tangents (`eye0 -1.3760, 1.0358`) the
  cyclopean term is `(tanR+tanL)/(tanR-tanL) = -0.1411`, **not 0.1867 - about
  32% too much.**
- **DO:** derive it, do not dial it. **Then confirm against the wearer's overlap
  rather than against comfort** - `173` was fixed once by the wearer naming the
  DIRECTION of divergence, and that instrument still works.
- **GATE `G-A3`:** one fused crosshair, in the same world place with either eye
  closed. **The overlap test is the falsifier: the two crosses must no longer
  sit one width apart.**
- **DEPENDS ON:** **A1.** Cannot be judged while the crosshair leaves the frame.

---

# GROUP B — DEPTH. **THE OWNER'S OWN REQUIREMENT. BUILT ON A's FOUNDATION.**

> `[REPORTED]` *"the aimer does not know if I am aiming at someone forty feet
> away up six feet in the air or ten feet away to my left... there needs to be
> depth."* **A crosshair at a pixel is a RAY, and the crosshair and the bullet
> start from DIFFERENT places, so two non-parallel rays cross at exactly ONE
> distance.** Inside it you miss one way, outside the other.

### B1 — U-06 PARALLAX FROM THE LAST IMPACT DISTANCE
- **`[READ]`** `patches/structs.h:1795` - `item_related` is the last member of
  `struct hand`; `:2529` gives the patch `hands[2]`. **REACHABLE, NO NEW SYMBOLS.**
- **`[READ]`** `gunfire.c:1139` + `:1007` - it is the world point the shot
  terminates at. `gunfire.c:1130` - **the game ALREADY projects it with
  `camGetWorldToScreenMtxf()`.**
- **`[READ]` THE LIMIT:** every writer (`chr.c:3520`, `chrprop.c:1166`,
  `propobj.c:9514`) is an IMPACT site. **It updates only when a shot LANDS.**
- **TAKE PD's FUNCTION WHOLE** - `port/vr/vr_openxr.cpp:2397`,
  `vrComputeCrosshairParallax`, **25 lines, and its `100.0f` units-per-metre is
  already our scale.** Feed it `|item_related - player pos|`, default 50000
  (infinity, zero parallax) when stale - **PD's own fallback,
  `sight.c:1864` and `bondgun.c:8368`.**
- **KNOB:** `-NoParallax`.
- **GATE `G-B1`:** shoot a near wall, then a far one. **The crosshair's
  convergence must CHANGE between them** - and it should feel like it sits ON
  the surface rather than floating.
- **DEPENDS ON:** **A1 and A3.** Parallax modifies the per-eye shift A3 fixes.

### B2 — T7, THE DISTANCE TEST, RE-RUN IN STEREO
- **`[MEASURED]` PROBLEM:** T7 has NEVER been run with two eyes. `179`/`180`:
  every aim observation from 08-24 21:00 onward was monocular.
- **DO:** shoot a wall at arm's length, then the same spot across the room.
  **Miss SHRINKS -> parallax, B1 is the cure. Miss HOLDS -> a constant angular
  error and B1 fixes nothing.**
- **DEPENDS ON:** **A1, A2, A3.** With A2 outstanding a constant 10 px would
  masquerade as the "holds" answer.

### B3 — U-05, THE CONTINUOUS LASER DOT
- **STATUS: PROJECT, NOT A SLICE. `[READ]`** GoldenEye's trace lives inside
  `chraiDefaultWeaponFireHandler` (`chrprop.c:908-931`), which also applies
  damage and creates explosions, and **is not in `externs.h`.**
- **DO NOT START THIS BEFORE B1 IS WORN.** B1 may deliver most of the felt
  benefit at a fraction of the cost.

---

# GROUP C — COMFORT AND PRESENTATION. **INDEPENDENT OF A AND B. MAKES EVERY LATER TEST CHEAPER.**

### C1 — WORLD-LOCK THE VIRTUAL SCREEN
- **`[REPORTED]`** *"it stayed perfectly still and stuttered when you move your
  head. Very nauseating."*
- **`[READ]`** `175` builds each eye's ray from its frustum tangents and hits a
  plane at `-dist` **in VIEW space**, so the quad rides the head by construction.
- **DO:** express the plane against the **RECENTRED REFERENCE POSE** instead of
  the live one. Same shader, same constants - only the matrix changes.
- **ALSO:** recentre must RE-PLACE it, or the screen ends up behind the wearer
  with no way back.
- **KNOB:** `-ScreenLock 0` restores head-locked.
- **GATE `G-C1`:** turn your head. **The screen stays put.**

### C2 — TIMEWARP THE SCREEN PATH
- **`[READ]`** the flat frame arrives at the GAME's cadence, not 90 Hz, so a
  stationary quad has nothing to reproject and every submission repeats.
  **That is the stutter, and it is a SEPARATE cause from C1.**
- **`178` ALREADY MADE THE MACHINERY EXIST** - `ge_vr_timewarp_create()` now
  runs regardless of `GE_VR_TIMEWARP`. **Only the enable is missing for this path.**
- **DEPENDS ON:** C1. Head-locked, there is nothing to reproject.

### C3 — U-20, THE ROOM BEHIND THE SCREEN
- **OWNER WANTS IT.** `[READ]` PD `port/vr/vr_hub.cpp`: **two quads, twelve
  vertices** (`BuildFloorMesh` 6, `BuildSkyMesh` 6). Everything visible is
  procedural fragment shader - grid with distance fog, banded sky, one logo
  decal. **NO ART ASSETS.** The only work is GLSL -> HLSL.
- **`168`'s RULE CUTS THE OTHER WAY HERE:** the hub calls into NOTHING - no
  lasersight, no model parts, no game state.
- **SOURCE IS LOCAL:** `GoldenEyeVR\local-only\prior-art\perfect_dark_VR`.
- **DECISIONS TAKEN:** floor at the wearer's real floor (reuse `176`'s standing
  height); recentre re-places room AND screen together; **first pass is a
  NEUTRAL grid and horizon** - the GoldenEye skin (Dam sluice, Facility tiles,
  gun-barrel iris, Q-Branch) is the owner's art direction and is a later pass.
- **KNOB:** `-NoRoom`.
- **DEPENDS ON:** **C1.** Both need the same reference-pose matrix; doing them
  together writes it once.

---

# GROUP D — INSTRUMENTS AND HYGIENE. **CHEAP, AND EACH ONE HAS ALREADY COST A SESSION.**

### D1 — RENAME THE MISLEADING LOG LABEL
- **`[READ]`** `ge_vr_bindtest.c:889` prints `crosshair_angle` under the word
  **`BULLET`**. That line predates `172`/U-16 and now names the DRAWN SIGHT as
  though it were the shot. **IT COST AN HOUR THIS SESSION AND WILL COST THE NEXT
  READER THE SAME.**
- **DO:** print what the consumer actually used - the same selection as
  `ge_vr_aim.c:638` - and label the clamped one `SIGHT`.
- **HIGHEST VALUE PER LINE IN THIS DOCUMENT.**

### D2 — THREE MORE CLEAN X CLOSES
- **`[MEASURED]`** two clean closes, the second after a long in-level run at
  90 fps with stereo and `ds_option 4`. **`[ASSUMED]` in general: B3 failed five
  times historically but never on EVERY close.**
- **COSTS NOTHING** - just stop using `taskkill` and watch for
  `shutdown: complete, clean`.

### D3 — THE `ds_option` DECISION
- **`[MEASURED]` THIS SESSION: `ds_option 4` at 90 fps with `LATE 0/91`.**
  **`49`'s O22 did NOT reproduce.** `111` §4 measured `2` free; `4` had never
  been run by anyone.
- **OWED: the wearer's verdict on whether it LOOKS better**, then make it the
  default. `msaa_option` stays `"None"` (`43`), belt-and-braces since
  `rt64_render_context.cpp:195` forces it anyway.

### D4 — THE 15 fps SAMPLES
- **`[MEASURED]`, UNEXPLAINED:** 1,406 samples at `eye0=15` in the 08-26 flat
  run. **May be an artefact of the no-stereo state. Re-check now stereo is back**
  before treating it as a workstream.

---

# GROUP E — THE ORDERED TEST SCRIPT, RESUMED. **GATED ON GROUP A.**

**`MAIN-STATION-TASKS.md` `T4`-`T11` are all still owed AND ALL WERE VOIDED** -
`179`/`180`: no run since 08-24 21:00 had stereo, so nothing measured against T3
means anything.

| | test | note |
|---|---|---|
| **T3** | aim baseline | **RE-RUN after Group A.** Today's is the first stereo baseline but predates every A fix |
| **T4** | `-HeadAnchor 0` | should be WORSE - favours one eye |
| **T5** | `-NoAimFrustum` | **NEVER ISOLATED.** Should be worse; crosshair drifts as you aim UP |
| **T6** | `-NoClampSplit` | **`[READ]` `172` is CORRECT** (`184` §3a) - this now tests a working feature, not a suspect one |
| **T7** | distance test | **-> B2.** The one that decides |
| **T8** | `-AimTrimX/Y` | a MEASUREMENT, expected to be deleted |
| **T9** | `-SeamCompose 1` | hand still, head turning, gun must not re-aim. **Re-references `-HandAxis*`/`-GunOff*`** |
| **T10** | drop `-NoCrouch` | **the owner's own requirement.** Stand still ~90 frames to calibrate |
| **T11** | `-NoXr` | flat game unchanged |

---

# GROUP F — THE UNBLOCKED BACKLOG. **TAKE WHEN A GROUP ABOVE IS WAITING ON THE RIG.**

| | what | state |
|---|---|---|
| **U-18** | per-weapon muzzle from the model node | **`[MEASURED]` T2 PASSED** - two distinct `Switches[3]`, different `numSwitches`. **Second weapon still n=1: linger on it next run.** Kills `-MuzzleExt` + 3 sign knobs |
| **U-02** | host-side recoil | READY. **The ~60 PD profiles do NOT transfer; the CLASSES do** (`86` §7) |
| **U-03** | snap turn | READY. Most requested comfort option in any VR shooter |
| **U-07** | gesture reload | READY, **one caveat:** `lv.c:733` also requires `bond_interact_object()`, **whose meaning is UNREAD** |
| **U-08** | smoothed body yaw | READY. `161` P2-6 / `6D-04`, PD's constant to start from |
| **U-04** | settings file + in-game VR menu | **DELIBERATELY LAST** - P1-2 deletes most of the knobs it would expose |

---

# GROUP G — THE COMMIT. **OWNER ONLY, AND OVERDUE.**

**`[MEASURED]`: SIX SESSIONS. Neither repo has a remote of ours. All of this
work exists on one disk.**

```powershell
cd C:\Users\pdbar\Desktop\GoldenEye64Recomp
git status --ignore-submodules=all
cd C:\Users\pdbar\Desktop\GoldenEyeVR
.\commit-session.ps1 -Message "<message>"     # -Message is MANDATORY, docs\120
```

**SESSIONS NEVER STAGE, COMMIT, BRANCH OR MERGE.** They leave the tree described
and put the commands here.

---

# ►►►► HOW IT COMES TOGETHER ◄◄◄◄

**`A` MAKES THE AIM HONEST.** The gun's direction maps continuously and
monotonically to a screen point, the rest position is the true centre, and the
two eyes agree on where that point is. **Until all three, no aim measurement
means anything - which is the state the project has been in since 08-24.**

**`B` MAKES IT AWARE.** With `A` true, the remaining error is a DEPTH error, and
`T7` can finally distinguish parallax from a constant angular error - **because
`A2` removed the constant that would otherwise fake the "holds" answer.**

**`C` MAKES IT WEARABLE**, and it pays for itself: every `E` test is cheaper
when the menus are navigable, the screen is world-locked and nothing is
nauseating. **That was `175`'s original justification and it still holds.**

**`D` MAKES IT KNOWABLE.** `179`, `180` and `184` all cost time to instruments
that were silent, latched, or mislabelled. **`D1` alone repays its cost the
first time someone reads the log.**

**`E` IS THE PROOF.** Eleven runs, each changing one thing, against a build in
which `A`-`C` are true. **That is the first time the script will have measured
what it was written to measure.**

**`F` IS THE GAME**, and `G` is the only thing standing between six sessions of
work and a disk failure.

> ## THE ORDER, IN ONE LINE
> **`D1` (minutes) -> `A1`+`A2` (one build) -> `A3` -> `C1`+`C2`+`C3` (one build)
> -> `B1` -> `E` from `T3` -> `B2`/`T7` decides `B3` -> `F`.**
> **`G` AT ANY POINT, AND SOONER IS BETTER.**
