# 148 — SUPERSEDED BY `161` ON 2026-08-25. READ `161`, THEN `160`.

> **THIS FILE IS HISTORY. `161` IS THE STANDING BOARD.** The `6D-xx` labels below
> are stable and are carried forward into `161` by name; what changed is the
> ORDER and the evidence, after the full Perfect Dark scan in `160`. **The
> per-task state recorded here is still accurate as of 2026-08-25 and `161`
> summarises it — do not re-derive it from this file.**

---

# 148 — THE 6DoF PLAN. LABELLED TASKS, PRIORITY ORDER.

**2026-08-24, end of session. THE STANDING PLAN, replacing `126` as the file
every session starts from.** `126` is Route B and Route B is closed (`147`).

> **HOW TO USE THIS FILE — same discipline as `126`, which worked.**
> **1.** Take the first task that is not DONE.
> **2.** If you finish it, mark it DONE here with what it found.
> **3.** If you cannot finish it, mark it IN PROGRESS or BLOCKED **and write what
> you learned.** `108` exists because a session ended without writing up and the
> next one wrote a document that contradicted it.
> **4.** Labels are stable. Refer to them by label (`6D-05`), never by position.

---

## WHY NOW — THE GATE THAT BLOCKED THIS SINCE `96` IS LIFTED

`96`, the owner: *"It's pointless building all this extra stuff if you're just
going to get sick when you're playing it."* **`86`'s nine slices have been parked
ever since.**

**2026-08-24, worn, at a true 90 Hz sim (`147`):** *"SO MUCH better... totally
playable and enjoyable."* **And then, explicitly:**

> ***"I shook my head fast, slow, went in circles. IT DOESN'T DO IT. It's pretty
> damn good."***

> ## **THE HEAD-TURN ARTIFACT IS GONE. `124`'s TARGET — the one the owner insisted must not be lost — IS CLOSED.**
>
> That question ran from `92` through `147`. **`146` §5 predicted the stick half
> would improve and the head half might not. The prediction was wrong and the
> result is better than predicted.**

**THE ONE RESIDUAL, MEASURED BY THE WEARER AND DELIBERATELY DEFERRED:**
*"Since I'm moving so fluidly I can notice the sixty hertz in the world on the
truck, but only when you're running at full speed and you turn and pass it by.
It's not major... the game shows me it's not worth it."*

**That is RB-03 exactly** — the world animating in 60 steps while rendering at 90
— **and `145` showed it is not a small fix.** Owner decision: **back burner.**
`126` RB-03 stays PARKED. **It is a known future improvement, not a defect.**

---

## THE STANDING PRECONDITIONS — every task below runs under these

- **PUT THE HEADSET ON, THEN LAUNCH.** O60. Three confounded launches already.
- **CLOSE WITH `taskkill /F /IM GoldenRecomp.exe`. NEVER THE X.** B3 bugchecks
  the machine on VR session close and costs a reboot; B4 is a tester using the X.
- **ONE BEHAVIOUR CHANGE PER BUILD.** `48` rule 5 — **and `142` is this session's
  fresh proof**: a tidy-up mixed into a debugging build caused a crash and cost a
  run.
- **`build.ps1` must report a FULL rebuild after any header change** (`115`), and
  it now self-heals the `LNK2005` weaken step (`133`) and fails on the static
  helper trap (`136`).
- **The wearer is the best instrument here** (`86` §9). Ask what it LOOKS like,
  not whether it works.
- **AUTO-AIM IS OFF** — set in the in-game options by the owner 2026-08-25 (`157` §6.2). **A setting outside the repo; note it before comparing any run against an older one.**
- **THE SEAM IS COSMETIC** (`157` §6.1): `field_8EC` has only DRAWING readers, so moving the hand **cannot** change where a shot goes until something writes `crosshair_x_pos`.

---

## THE TASKS

| Label | Task | State |
|---|---|---|
| **6D-00** | **B3 / B4 — THE BUGCHECK ON VR CLOSE, AND THE GRACEFUL EXIT.** `39`, `75`. The machine bugchecks (`0x139`) when a VR session closes; a tester will close with the X | **NOT STARTED — AND IT IS NOW FIRST.** `39` has had it BLOCKING since `75`, and **every session including this one chose the judder over it by default rather than deliberately.** `86` §6: *"B3/B4 sit above all of this — every slice costs wear tests and every wear test risks a reboot."* **The judder is closed. B3 has no competition left, and every task below is cheaper once it is fixed.** **IN PROGRESS — `149`: O21 IS BUILT, NOT COMPILED, NOT WORN.** `waitForGpu()` ignored **three** results — `Signal`'s, `SetEventOnCompletion`'s and `WaitForSingleObject`'s — so a `WAIT_TIMEOUT` printed **`gpu idle`** and went straight on to destroy the swapchains, allocator, list and fence **underneath a running GPU**. That is hazard 2 in `xr_shutdown`'s own header. It now returns `bool` and a failure takes `40`'s proven deliberate-leak branch. **THE FIRST RUN IS A DIAGNOSTIC EITHER WAY:** `gpu idle (confirmed)` -> the wait always succeeded and B3 is something else; `ABANDONED - the GPU could not be confirmed idle` -> **that was it.** **THE TEST IS B4: close a VR session with the X, on purpose.** Costs a reboot if it still bugchecks, and is now worth one. **UPDATE `151`: COMPILED AND VERIFIED IN THE BINARY (`133`) - all three of `149`'s strings are in GoldenRecomp.exe. TWO CRASHES SPENT, NEITHER ANSWERED B4: no `shutdown:` line in either log, so the teardown was never reached and B3 IS UNTESTED, NOT REFUTED. NEXT IS THE `-NoXr` BISECT BEFORE ANY MORE HEADSET TIME - `48`/`63`, `151` §4.** |
| **6D-01** | **S0, THE 6DoF INSTRUMENT — CONFIRM IT IN A LEVEL.** `86` §5: *"nothing in this plan is judgeable without one log line that prints every 6DoF quantity in a named frame"* | **G0-1 AND G0-2 PASS, 2026-08-25, from `gevr-logs\gevr-0824-195259-tw0-88fps.log` - NO LAUNCH NEEDED, the evidence was already on disk. G0-3 STILL OWED.** **G0-2 PASSES:** the line reads `6dof: head play=(x,y,z)u`, naming its frame explicitly. **G0-1 PASSES FOR THE HEAD:** across 46 samples `head play` moves from `(-0.0,0.0,-0.0)u heightAboveOrigin=0.000m` (headset stationary) to `(19.4,18.0,38.7)u heightAboveOrigin=0.419m` - non-zero and tracking the physical thing. `ipd=0.0639m` and `scale u/m=50.0` also live. **G0-3 (silent under `-NoXr`) NEEDS ONE MONITOR LAUNCH - no headset, no reboot risk.** **AND IT SURFACED A BLOCKER THAT IS NOW ITS OWN TASK - SEE 6D-14.** Originally: **BUILT, PARTIALLY OBSERVED.** Written `91`; its silence diagnosed and fixed in `100` (`recomp_puts`, hand-rolled formatter, no varargs, no statics) and confirmed emitting 14 samples. **G0-1 not fully checked: every field non-zero AND moving when the physical thing moves. G0-2: the line must state its FRAME (`head play=`, not `head=`). G0-3: silent under `-NoXr`.** One in-level launch closes it |
| **6D-02** | **`muzzleExt` — THE LAST UNREAD FALSIFIER.** `90`'s five, four confirmed | **DONE 2026-08-25. THE FIFTH FALSIFIER IS READ AND IT CONFIRMS THE PREDICTION.** `muzzleExt=100` across **97 samples, flat**, against `100`'s `PREDICT >0` - and it is no longer the line that emits empty, so `100`'s move-it-to-its-own-line remedy was not needed. `A40` also confirmed NEGATIVE and LIVE, ranging -865 to -1000 across the run rather than the frozen `-1000`. **`90`'s five falsifiers are now five for five.** Read off `gevr-logs\gevr-0824-195259-tw0-88fps.log`; no launch was spent. Was:**NOT STARTED — BATCHES WITH ANY IN-LEVEL LAUNCH.** `100`: its line is the only one that emits empty and the only one touching `get_ptr_item_statistics`. **Move that read to its own line, last.** `A40 = -1000` CONFIRMED, `crosshair_angle` and `field_FFC` both read (160,120) = screen centre |
| **6D-03** | **H1 — THE RECENTRE MOVES TO LEVEL START.** `86` §5. Today it fires at process start, which is the wrong moment (O60) | **NOT STARTED. THE SMALLEST SLICE IN THE PLAN AND IT REMOVES A CONFOUND FROM EVERY OTHER ONE.** G-H1-1: start a level with the headset on and **do not press F9** — height and heading right immediately. G-H1-2: F9 afterwards changes nothing measurable. G-H1-3: `-NoXr` untouched. **No-code falsifier: headset on the desk, start a level, then pick it up** |
| **6D-04** | **H3 — THE BODY YAW BECOMES A NAMED QUANTITY.** `86` §5 | **NOT STARTED — AND `153` §2 REMOVES IT FROM A1's CRITICAL PATH.** `86` §6's *"A1 cannot be written without it"* is true of `86`'s camera->WORLD->camera recipe and not of the problem: **the gun and the camera share the same body yaw, so it CANCELS on the round trip** - and `86` names the shortcut itself one paragraph earlier. **`field_FFC` is already the gun's pointing as an unclamped SCREEN POINT, so there is nothing for body yaw to do.** **STILL WORTH BUILDING** for G1/G2/G3 and any true world-space work, and `86`'s rule 8 stands - every consumer reads it, nobody re-derives it. **It is simply no longer in front of the headline feature.** |
| **6D-05** | **A1 — THE BULLET GOES WHERE THE GUN POINTS.** The headline feature | **NOT STARTED — READY TO BUILD, AND BETTER RESEARCHED THAN ANY SLICE IN THIS PROJECT.** Entry point found by the wearer (`101`): holding aim selects KISSY -> `sub_GAME_7F067FBC`, **a nine-line wrapper around the exact function `86` chose, already fetching both per-weapon dampings.** **The ARM is already unclamped (`field_FFC`); ONLY THE BULLET IS LOCKED** (`90`). **`102` §1: PD clamps the DRAWN CROSSHAIR and leaves the BULLET AIM UNCLAMPED — prior art ships the break-the-lock.** **A1-R3 CLOSED by the owner:** losing look-ahead in aim mode is fine, *"you're in the shooting position now."* Design: `101` §6. **UNBLOCKED 2026-08-25 - `153` IS THE PLAN.** No longer waiting on 6D-04 (`153` §2), does not need the OpenXR controller path (`153` §6), and **`153` §4 resolves `101` §6.4's timebase collision in our favour: the accumulator still emits sixty ticks a second, so the aim integrator gets sixty iterations and the feel is preserved.** **G-A1-4 IS `-NoXr` AND RUNS FIRST - no headset, no reboot risk.** **READS 1 AND 2 CLOSED, AND THE GATING EIGHT-READER READ IS DONE - `153` §8.** `crosshair_x_pos` has NO readers outside `gunfire.c`; the function is 69 lines and patchable. **THE EIGHT READERS SORT ONE-TO-SEVEN: only `gunDrawSight()` wants the clamp; the shot path, the aim ray AND the auto-aim test all want the TRUE AIM** - and `chrprop.c:2322` compares the crosshair against UNCLAMPED projected target bounds, so the clamped value is the bug there, not the fix. **THE CHANGE: keep `crosshair_angle` unclamped, move the `[3,w-4]` clamp into `gunDrawSight()`, KNOB-GATED so an unset build is an exact identity.** That is `102` §1's PD split confirmed in our own tree. **READ 3 CLOSED: TWO new `RECOMP_PATCH` names were needed and the slice was cut to ONE** (`153` §9.1 - `__recomp_orig` is not callable as plain C from patch code, so `gunDrawSight` becomes slice A1b). **WRITTEN 2026-08-25, NOT COMPILED, NOT RUN - `153` §9.** Six files, one behaviour change, knob `-FreeAim`, off by default; `vr.ps1` parses clean and the knob IS in the clear list (`48` rule 6, nearly missed). **`CMakeLists.txt:150` warns that modifying patches needs TWO builds to take, and this is a brand-new patch name - run `build.ps1` twice before concluding the knob is dead (`136`).** **GATE ORDER: `-NoXr` KNOB OFF first, then `-NoXr -FreeAim`, THEN the headset.** |
| **6D-05c** | **A1c — THE HAND DRIVES THE AIM. `crosshair_x_pos` written from the gun's pointing** | **BUILT 2026-08-25, REFUSED ON EVERY FRAME SO FAR — `158`.** **THE FINDING THAT REFRAMED THE WHOLE SLICE: THE SEAM IS COSMETIC** (`157` §6.1) — `field_8EC` has only DRAWING readers, so from `83` until now moving the hand moved the gun's PICTURE and nothing else, and `crosshair_x_pos` saw only the stick. **This writes the gun's pointing into the bullet's integrator with the `ndc/(1-damp)` pre-load** (`86` steps 4-5, `38` correction 2 — never write `crosshair_angle`). **THREE GUESSES AT THE BARREL AXIS INSIDE `R` WERE ALL WRONG and one log line caught it: `state=REFUSED fwd=-0.303`, `row3=(-0.45,-0.84,0.30)` — dominated by Y, not a barrel.** `R` is a DRAWING matrix (`Rhead*Rhand^T` + `diag(sgn)`), the wrong place for geometry. **§5 derives the ray from the RAW poses instead and is now the default; UNRUN.** Gate: `fwdHead` z must go NEGATIVE when the gun points forward. |
| **6D-05b** | **A1b — THE BULLET'S ORIGIN. Shots leave the CAMERA, not the gun** | **NEW AND BUILT 2026-08-25, NOT RUN — `157`.** Raised by the wearer as the thing blocking actual play: *"the bullets don't shoot from the gun, they shoot from the player."* **`gunfire.c:4871-4873` sets the shot's origin to `(0,0,0)` — the CAMERA** — and the callers name it (`chrprop.c:931` passes `&shotdata.viewOrigin`). **Invisible and CORRECT on a flat screen; it collapses in VR.** A 2nd `RECOMP_PATCH` on `bullet_path_from_screen_center` writes the muzzle in the head's frame instead, sourced from the same numbers the gun is drawn with. **SEPARATE QUANTITY FROM A1 — A1 is where the shot GOES, A1b is where it comes FROM, separate knobs on purpose (`155` §3).** **DONE AND WORN 2026-08-25: *"bullets come out of the gun."*** First attempt was WITHDRAWN before compiling (eight unreachable symbols + the `WeaponStats` layout); the second declares only what it needs via `100`'s partial-struct pattern, with **`Inaccuracy`'s offset MEASURED at byte 48 by walking `gun.h`, and a [0,100] guard so a wrong offset fails SAFE as perfect accuracy rather than as bizarre spread** (`115`). **LANDMINE LOGGED: the PAL branch is hardcoded `240.0f` — right for this US/NTSC build, wrong for PAL.** Gates: `157` §5. |
| **6D-06** | **A2 — THE WORLD-SPACE AIM DOT (O64)** | **NOT STARTED — AND `102` SAYS IT MAY NOT BE MANDATORY.** Re-cost after A1 |
| **6D-07** | **G1 — THE HAND POSE ARRIVES HEAD-RELATIVE** | **NOT STARTED.** Note the seam already works position-first (`83`-`85`) and `-HandSeam` / `-SeamNoRot` exist |
| **6D-08** | **G2 — ROTATION CONVENTION** | **DONE 2026-08-25 - `155`. THE CHECK PASSED ON THE FIRST LAUNCH AND NO SWEEP WAS EVER RUN.** `-HandAxisX -1 -HandAxisZ -1` IS the `{w,-x,y,-z}` conjugation (our `sgn[i]*sgn[j]` is conjugation by `diag(sgn)`); worn, **the up/down inversion went away and `-HandAxisY -1` was not needed.** **BUT PD's 1.5708 rad X POST-ROTATION IS FALSIFIED FOR US: `-HandRotXDeg 90` did not work and `-90` was WORSE; 0 beats both** - probably because our `R` is already head-relative (`Rhead*Rhand^T`) where PD's quat is play-space. **First PD constant that did NOT transfer, and it transferred by half - `155` §3.** Knob kept, default 0, skipped at 0. Was: **NOT STARTED — AND `102` DOWNGRADES IT FROM A SWEEP TO A CHECK.** PD's basis is confirmed verbatim: **`{w,-x,y,-z}` plus a 1.5708 rad X offset** (their own comment says "1.0 rad" and is **wrong**) |
| **6D-09** | **G3 — THE GRIP OFFSET AND ITS TABLE** | **IN PROGRESS 2026-08-25 - `154`.** **THE REPORTED "anchor on the front of the gun" IS EXPLAINED: `ge_vr_gun_off_x/y/z` ALL DEFAULT TO 0 AND NO LAUNCH HAS EVER SET THEM**, so the gun pivots about the model's own origin. **AND `-SeamNoRot`, in every standing command in this project, was DELETING THE ROTATION ENTIRELY** (`:1109` writes identity) - dropping it gives left/right turning for the first time since `85`. **A convention mismatch was also found and deliberately NOT 'fixed': the grip offset sums `M[j][i]` where the hand position sums `M[i][j]`. Which is right could not be settled by reading, so it is `-GunOffFwd` and the wearer settles it** (`154` §3). **Four gates, `154` §5. Latent until `-GunOff*` is non-zero, so an unset build is an exact identity.** Was: **NOT STARTED — AND `102` TURNS IT INTO A TABLE TO VERIFY.** `(0,16,-4)` default, `(-4,16,+8)` rifles — **in `bondgun.c:6286-6320`, not `vr_input.cpp`, and in an Ry180 basis, so copying the numbers alone MIRRORS THE GUN about the grip** |
| **6D-10** | **H2 — HEAD HEIGHT BECOMES A GAME QUANTITY.** The architectural one | **NOT STARTED — AND IT NEEDS A DECISION BEFORE A BUILD.** **Option A:** keep it in RT64, add a ceiling clamp only — small, but crouching still does not make you a smaller target and the AI never knows. **Option B:** drive the game's `eyeheight` — physical crouch is real, ceiling/AI/cover follow, as PD's do. **`86` recommends A first.** `89` READ 10: `bondviewUpdatePlayerCollisionPositionFields` (`bondview2.c:4557`) is **95 lines and patchable**, and takes `headpos.f[1]` as input. **READ 9: `autocrouchpos` will NOT fight a written-in head height** |
| **6D-11** | **R1 — ROOMSCALE LEAN, THEN BODY DRAG** | **NOT STARTED.** After 6D-10 if option B is chosen. **`86` §3.5 has PD's whole design:** two offsets not one, vertical excluded from the walk delta, 25-unit glitch rejection, a 12-unit cylinder probe plus `cdTestLos05` both testing **`GEOFLAG_BLOCK_SIGHT`** — *"blocking the head on invisible barriers is what stopped leaning over a rail from working"* |
| **6D-12** | **S1 — SPLIT THE SCALE KNOB** | **BUILT 2026-08-25, NOT RUN — `156`.** `GE_VR_WORLD_UNITS_PER_METRE` (the eyes / world size) and `GE_VR_HAND_UNITS_PER_METRE` (the hand / arm reach) are now separate; both default to `-UnitsPerMetre` so an unset build is an exact identity. **S0's line was corrected in the SAME build** - it read `ONE-KNOB-THREE-JOBS` and would otherwise have reported a quantity that no longer exists (`48` rule 4). **IT SETTLED `77` vs `16` WITHIN ONE SESSION - `159`.** They were never in conflict: **HAND = 100 is a MEASUREMENT** (one game unit is one centimetre, from Bond's 175-unit eye height) and is now PINNED; **WORLD is a PERCEPTION** and the wearer's answer is **nowhere near 50 or 100 - it is around 12-25 and still coming down.** *"Toy model level... characters much smaller than me size wise BUT SAME HEIGHT"* at 100 is the HYPERSTEREO signature: heights are geometry and invariant, only apparent size is stereo. **Halve, never nudge - finer than a factor of two is below the noise floor in a headset.** Height stays with 6D-10. Gates: `156` §3. Was: **NOT STARTED — DO IT BEFORE ANY MORE SCALE SWEEPS.** `86` §3.9: PD keep **three** separate numbers — world scale, a per-frame measured IPD (clamped 1-10 cm, default 64 mm), and `unitsPerCm` for height |
| **6D-14** | **THE CONTROLLERS ARE NOT BINDING. `ctrlR` IS `n/a` AND `handValid=0`.** | **NEW 2026-08-25, AND IT BLOCKS THE HEADLINE FEATURE.** `gevr.log`: *"xr input: bound profile = NONE BOUND - no controllers detected, or none matched a suggested profile"* - with **four profiles suggested ok** (index, vive, touch, simple). S0 agrees from the other side: **`ctrlR viewrel=n/a quat=n/a (valid=1 focused=1 handValid=0)` on all 46 samples.** The session ran `-SeamNoRot -HandPosZ 1`, so **hand flags were being passed with no hand input at all.** **6D-05 (A1), 6D-07, 6D-08 and 6D-09 ALL NEED THIS FIRST.** **CHEAPEST EXPLANATION FIRST, AND IT COSTS NOTHING: were the controllers awake? Pimax Crystal Super - check whether its controllers present as Index or as a Pimax-native profile we never suggest.** |
| **6D-13** | **C1 — `vr.json`, HOT-RELOADED (O48)** | **NOT STARTED — every slice above gets cheaper after it** |

---

## WHAT IS ALREADY BUILT AND NOT FULLY CONNECTED

**The owner is right that there are things built and left dangling. Here they
are, so nobody rebuilds them:**

| | Where | State |
|---|---|---|
| **S0, the 6DoF instrument** | `91`, fixed in `100` | Built and emitting. **6D-01 finishes it** |
| **The seam — the gun follows the hand** | `83`, `84`, `85` | **Works, position first.** `-HandSeam`, `-SeamNoRot`, `-HandPosZ` |
| **The viewmodel transform** | `78`, `79` | Slices 1 and 2 of `76` done. `-ViewmodelScale`, `-ViewmodelPush` |
| **Scale, measured** | `77` | ~50 units/metre, worn. `-UnitsPerMetre 50` is the standing flag |
| **The recentre** | O60 | Works — **but fires at process start. That is 6D-03** |
| **All eleven reads `86` §8 owed** | `87`, `88`, `89` | **DONE**, with `90`'s label correction folded in |
| **Perfect Dark's actual constants** | `102` | **Read at `67ea20c`, MIT, ATTRIBUTION OWED.** Grip offsets, quaternion basis, smoothing alphas, probe geometry, crouch thresholds, and seven traps they already paid for |
| **Route B's debug instrumentation** | `ge_vr_route_b.c` | **In the shipping build right now.** Clock probe, retrace probes, boot lines. Cheap, but see SUGGESTIONS |

---

## WHAT MUST NOT BE FORGOTTEN

**`86` §7 — WHAT THIS PLAN DELIBERATELY DOES NOT DO.** No IK arm (`76`: a wrong
arm is more distracting than none). No two-handed aim, gestures or throwing. No
VR hub (O61). No scope (`37` trap 3). **No per-weapon table until two weapons are
measured to disagree.**

**THE LABELS ON THE TWO INTEGRATORS WERE SWAPPED ONCE AND CORRECTED** — `90`.
**`crosshair_x_pos` drives the BULLET; `gun_azimuth_angle` drives the GUN MODEL'S
POINTING.** The two-integrator finding survives; its output labels did not.

**PERFECT DARK IS THE REFERENCE, NOT A SOURCE TO COPY.** MIT, may influence
anywhere, **attribution owed in the published repo.**

---

## THE ORDER, AND WHAT BLOCKS WHAT

```
6D-00  B3/B4 ─────────────────────────────► makes every wear test below cheap
6D-01  S0 confirmed ─────────────────────► everything is judged through it
6D-03  H1 recentre at level start ───────► removes a confound from all of it
6D-04  H3 body yaw ───────────────────────► 6D-05 A1 ──► 6D-06 A2
6D-07  G1 hand pose ──► 6D-08 G2 ──► 6D-09 G3
6D-10  H2 head height   (independent; DISCUSS before building)
6D-11  R1 roomscale     (after 6D-10 option B, if chosen)
6D-12  S1 scale split   (independent; before any more scale sweeps)
6D-13  C1 settings file (independent; everything above gets cheaper after it)
6D-02  muzzleExt        (batches with any in-level launch)
```
