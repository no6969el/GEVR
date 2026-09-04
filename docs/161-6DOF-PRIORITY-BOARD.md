# 161 — THE 6DoF PRIORITY BOARD. TAKE THE TOP UNCHECKED BOX.

**2026-08-25. THIS REPLACES `148` AS THE FILE EVERY SESSION STARTS FROM.**

> # ►►►► UPDATED 2026-08-25 LATE. P0 IS CLOSED AND P1-1..P1-4 ARE BUILT. ◄◄◄◄
>
> **READ `162` (P0 — and TWO ITEMS ON THIS BOARD WERE WRONG) THEN `163` (P1-2,
> and the projector was in the game all along).**
>
> **THREE BOARD CORRECTIONS, ALL EVIDENCED:**
> **(1) P0-1's premise is false — the controllers DID bind, as Oculus Touch.**
> **(2) P0-3(a) would have BROKEN the aim — its evidence was from the old basis.**
> **(3) P1-4(b) is impossible — GoldenEye has no muzzle model part.**
>
> **THE NEXT THING IS A BUILD AND ONE WORN RUN. `163` §8 has the gates.**
>
> # ►►►► UPDATED AGAIN 2026-08-25 CLOSE. FOUR MORE SLICES, NONE WORN. ◄◄◄◄
>
> **`167`** the FOV (the aim projected through a frustum nobody looks through) —
> **`170`** U-01 (the HUD was never given an eye) — **`171`** the muzzle-node
> instrument — **`172`** U-16 (the clamp split, P1-5).
>
> **AND `169` IS NOW THE STANDING UPGRADE SHEET.** This board is the PLAN; `169`
> is the CATALOGUE. **Append to `169`, never rewrite it. Next ID `U-19`.**
>
> **TWO RETRACTIONS, BOTH MINE, BOTH CAUGHT BEFORE THEY COST A BUILD:**
> **(1) P1-4(b) below is WRONG — GoldenEye HAS a muzzle node** (`171` §3).
> **(2) `163` §1's "the FOV read is no longer owed" is WRONG** (`166` §2).
>
> **AND ONE PROPOSAL FALSIFIED BEFORE BUILDING:** `169` U-14 —
> **`MuzzleFlashExtension` is a flash-SPRITE stretch, not a barrel length**
> (`matrixmath.c:408` scales row 2, never the position). `171` §2.
>
> **THE RULE THAT CAUGHT ALL THREE: grep `patches/externs.h` and
> `patches/structs.h` for every symbol BEFORE costing anything — and search for
> the MECHANISM, never for Perfect Dark's identifier.**
>
> # ►►►► 2026-08-25 EVENING. THE CROSSHAIR FUSES. `173`, `174`. ◄◄◄◄
>
> **U-01 IS WORN AND WORKING** — *"much closer now in my vision"* — after two of my
> own misses: the shift went to the ORTHOGRAPHIC matrix when GoldenEye's HUD is
> **`Type::Rectangle`, which has no matrix at all**, and the sign was inverted
> because **the perspective divide flips the matrix entry's sign**. `173`.
>
> **AND THE WEARER FOUND THE SEAM BUG:** *"turn my head and the gun changes
> direction in my hand."* The seam is `R = Rhead * Rhand^T`; correct is
> `R = Rhead^T * Rhand` — **and the AIM has always used `Rhead^T`. The aim and the
> picture have been on different transforms the whole time.** That is P1-4/`166`
> §4's "the drawn gun is the liar", confirmed. **`-SeamCompose 1`, UNTESTED.**
>
> **P1-6 IS NOW THE LIVE QUESTION, AND ONE WALL DECIDES IT:** the shot lands ~6 px
> UP of the crosshair. **Miss shrinks with distance -> muzzle parallax (P1-6 /
> U-06). Miss holds -> a constant angular error.** They behave OPPOSITELY.
`148`'s labels (`6D-xx`) are stable and still referenced here; what changed is the
ORDER and the evidence, after the full Perfect Dark scan in `160`.

> ## HOW TO USE THIS FILE. THE DISCIPLINE IS THE POINT.
>
> 1. **Take the first unchecked box.** Do not skip ahead; the order encodes what
>    blocks what.
> 2. **When you finish it, TICK IT — `- [x]` — and write the one-line result
>    and the doc number on the same line.** A tick with no evidence is worse
>    than no tick.
> 3. **If you cannot finish it, leave the box unticked and write `IN PROGRESS`
>    or `BLOCKED` plus WHAT YOU LEARNED.** `108` exists because a session ended
>    without writing up and the next one contradicted it.
> 4. **Labels never move.** Refer to a task as `P1-2`, never as "the second one".
> 5. **One behaviour change per build** (`48` rule 5). **`build.ps1` twice after
>    any new `RECOMP_PATCH` name** (`136`, `CMakeLists.txt:150`).

**THE OWNER'S MISSION, IN HIS WORDS:** *"getting this hand tracking right and the
bullet leaving the gun"* — and *"aimed/shot freely... something is locking the
movement."*

> ## **THE ANSWER TO "SOMETHING IS LOCKING THE MOVEMENT" — IT IS NOT ONE LOCK, IT IS THREE, AND NONE OF THEM NEEDS A REWRITE OF THE MOVEMENT CODE.**
>
> 1. **The controllers are not binding at all** (`6D-14`) — `handValid=0` on all
>    46 samples. **A hand that never arrives cannot move anything.**
> 2. **The aim write is REFUSED every frame** (`158`) — so both integrators decay
>    to screen centre and every shot leaves along the view axis. **That is the
>    "shoots where I look" report, exactly.**
> 3. **The `[3, w-4]` clamp** (`153`) — real, already unclamped behind `-FreeAim`,
>    and **the smallest of the three.** It only bites once 1 and 2 are fixed.

---

## THE STANDING PRECONDITIONS — every task below runs under these

- **PUT THE HEADSET ON, THEN LAUNCH.** O60. Three confounded launches already.
- **CLOSE WITH `taskkill /F /IM GoldenRecomp.exe`. NEVER THE X** (`6D-00`).
- **AUTO-AIM IS OFF** in the in-game options, set 2026-08-25 (`157` §6.2).
- **The wearer is the best instrument.** Ask what it LOOKS like, not whether it
  works. **A guard is the scale reference** (`159` §5).
- **Perfect Dark source is LOCAL:**
  `local-only\prior-art\perfect_dark_VR` @ `67ea20c`, MIT. **Do not re-clone.**
  **Attribution owed in `PUBLISH-MANIFEST.md` and at the point of use.**

---

# P0 — BEFORE ANY MORE HEADSET TIME. CHEAP, AND EVERYTHING ABOVE IT IS BLOCKED.

- [x] **P0-1 — CORRECTED BY `162` §3, NOT AS WRITTEN. THE CONTROLLERS DID BIND.**
      `gevr.log` 2026-08-25 02:13: `bound profile =
      /interaction_profiles/oculus/touch_controller` — **NOT `NONE BOUND`** — with
      live per-sample `ctrlR viewrel=/quat=` data. **The Pimax Crystal Super
      presents as OCULUS TOUCH**, which was this task's own second hypothesis,
      answered from the disk with no launch. **`handValid=` does not appear in
      this log at all**, so that reading came from an earlier build. **THIS WAS
      NOT THE BLOCKER.** What remains is a one-line confirmation in the new
      build, folded into G-163-2. `162`.

      *(original text, superseded:)* **THE CONTROLLERS ARE NOT BINDING.** `gevr.log`: *"bound profile = NONE BOUND"* with four
      profiles suggested ok; S0 agrees from the other side with
      `ctrlR ... handValid=0` on every sample. **CHEAPEST EXPLANATION FIRST AND
      IT COSTS NOTHING: were the controllers awake and in the guardian?** Then:
      **does the Pimax Crystal Super present its controllers as
      `/interaction_profiles/valve/index_controller`, or as something we never
      suggest?** Dump the runtime's reported profile path per hand.
      **GATE: one `-NoXr`-free launch where `handValid=1`. Nothing below P1 is
      judgeable until this reads 1.**

- [x] **P0-2 — DONE, `162`. THE ANSWER IS A THIRD STATE: `NEVER-CALLED` on all
      117 samples — the knob was OFF, so `-AimFromHand` was never passed and
      A1c HAS NEVER RUN.** `fwdHead` z is negative on 97 of 98 non-zero samples
      (to `-0.995`), so `158` §5's pre-registered gate PASSES on free data.
      **"Still mis-aimed, UNTUNED" was judged on a build where the aim path
      never executed** — which is why P1-2 was gone to directly.

      *(original text:)* READ THE LAST AIM LOG BEFORE BUILDING ANYTHING.
      `Select-String -Path .\gevr.log -Pattern "AIM"`. **`state=` must say `APPLIED`.** If it
      still says `REFUSED`, `158` §5's derived ray did not land and that is the
      finding, not a tuning problem. **Also read `fwdHead=` — `z` must go
      NEGATIVE when the gun points forward** (`158` §5's pre-registered gate).

- [x] **P0-3 — (b) APPLIED. (a) REFUSED WITH CAUSE — `162` §4. THE BOARD WAS
      WRONG.** `-AimFwdNeg 0` cleared the refusal **under BASIS 0** (`158` §3);
      `158` §5 then made basis 2 the default and inverted the sign convention,
      and this board carried the old advice forward. Under basis 2 the log shows
      `fwdHead.z < 0` on 97/98 samples, so `fwd = -z` is POSITIVE and **`1.0` IS
      THE CORRECT DEFAULT.** Defaulting it to 0 would have refused every frame —
      re-creating the exact fault P0-2 diagnosed. **Left at 1.0, reasoning in the
      code.** (b) NDC clamped to `±2`.

      *(original text:)* THE TWO GUARDS OWED IN CODE.
      (a) **make `GE_VR_AIM_FWD_NEG` default `0`** — `-AimFwdNeg 0` is what
      cleared the refusal and the shipped default is a trap;
      (b) **clamp the returned NDC to about `[-2, 2]`** — a near-zero forward
      divisor threw `ndc=(-8.5,-17.9)` and flung the crosshair off screen, which
      is the "shooting the ground" report. `rt64_render_context.cpp:1158,1174`.
      **GATE: `-NoXr` unset build is character-for-character identical.**

- [ ] **P0-4 — `6D-00` / B3+B4. THE BUGCHECK ON VR CLOSE.** `149`'s fix is
      COMPILED and VERIFIED IN THE BINARY (`151`) and **has never been reached**
      — no `shutdown:` line in either crash log. **`151` §4: the `-NoXr` bisect
      runs BEFORE any more headset time.** Costs a reboot if B4 still
      bugchecks. **Kept at P0 because every wear test below risks one — but the
      `taskkill` workaround is known and works, so this may be deferred by owner
      decision without blocking P1.**

---

# P1 — THE AIM CHAIN. THE HEADLINE FEATURE. `160` IS THE EVIDENCE FOR ALL OF IT.

- [x] **P1-1 — DONE, `163` §1.** `transform3Dto2DCoords`, `bondview.c:722`,
      declared `bondview.h:2825`. **Takes NO camera matrix** — it runs off live
      `g_CurrentPlayer` scales. **Argument frame: CAMERA/VIEW, game units.
      Returns PIXELS.** **Reachable from patch code: YES** — `gunfire.c:4818`
      already calls it. **And `c_recipscaley = c_halfheight/tan(fovy/2)`, the
      game's OWN fov, so `159` §6's FOV read is NO LONGER OWED FOR AIMING.**

      *(original text:)* FIND GOLDENEYE'S 3D-to-2D PROJECTOR.
      **PD's whole aim is `mtx4TransformVecInPlace(camGetWorldToScreenMtxf(), p)`
      then `cam0f0b4d04(p, screen)`** (`bondgun.c:8391-8397`). Our counterpart is
      named but unread: **`transform3Dto2DCoords`**, cited in `153` §8 as what
      `chrprop.c:2322` uses to project target bounds. **Confirm its signature,
      confirm it is reachable from patch code, confirm what frame it consumes.**
      **DELIVERABLE: one paragraph in a new doc naming the function, its
      argument frame, and whether patch code can call it.** `160` §2/B1.

- [x] **P1-2 — BUILT (UNCOMPILED, UNWORN), `163`. AND THE PLAN CHANGED: NO
      WORLD-FRAME PUBLISH IS NEEDED.** `163` §2 — **inverting
      `transformAndNormalizeByLength2Dto3D` shows GoldenEye's camera frame is
      `+x` right, `+y` up, `-z` forward: OPENXR'S HEAD FRAME, AXIS FOR AXIS.**
      So the host publishes the raw ray (`aim_fwd_head`) and the patch projects
      it with the game's own function. **No world transform, no sign to guess.**
      Five knobs dead. Old path kept behind `-AimEstimate` for a one-build A/B.

      *(original text:)* PROJECT THE RAY INSTEAD OF ESTIMATING IT.
      Today `ge_vr::aim_screen_ndc` does `lateral/forward * GE_VR_AIM_GAIN` —
      **a perspective divide with the projection matrix replaced by one scalar,
      which is why A1c is "mis-aimed, UNTUNED": there is nothing to tune it to.**
      **THE CHANGE:** the host stops returning NDC and instead publishes **the
      gun's forward direction and the muzzle position in the game's world
      frame**; the patch builds `muzzle + fwd * 100000`, calls P1-1's projector,
      and converts pixels to NDC with `2*x/width - 1`.
      **WHAT IT BUYS: zero free parameters. `-AimGain`, `-AimSignX`, `-AimSignY`,
      `-AimFwdAxis`, `-AimFwdNeg`, `-AimBasis` all become dead and should be
      deleted, not defaulted.** Correct at every FOV, including under the
      widescreen hack `159` §6 flags as unmeasured.
      **GATES:** (1) `-NoXr` identical with the knob off; (2) point the gun at a
      wall corner and the crosshair lands ON the corner at 1 m and at 20 m —
      **the far-only agreement is the B4 signature, not a failure**; (3) no knob
      is touched to achieve it.

- [x] **P1-3 — BUILT (UNCOMPILED, UNWORN), same build as P1-2. `163` §5.**
      **AND THERE IS AN ORDERING TRAP, HIT AND FIXED:** the natural write site is
      beside the crosshair pre-load, but that is ABOVE the `gun_azimuth`
      integrator loop, which overwrites it the SAME FRAME. **The result would be
      a crosshair that tracks and a gun that does not — which reads exactly like
      "the gun lags" and would have been mis-diagnosed as smoothing.** Stashed
      and applied after the loop, scaled by `gunaimdamp` NOT `guncrossdamp`.

      *(original text:)* DRIVE BOTH INTEGRATORS.
      `ge_vr_aim.c` writes `crosshair_x_pos`/`_y_pos` and **nothing else**;
      `gun_azimuth_angle`/`gun_azimuth_turning` are still driven by the stick's
      `turn_x`, and `field_FFC` — the gun's pointing and the input to
      `sub_GAME_7F067AB4` — comes off them. **PD pre-loads `crosspossum` AND
      `crosssum2` from the same `x`, two lines apart** (`bondgun.c:8407-8412`).
      **Add the `ndc / (1 - gunaimdamp)` write for the second pair.**
      **GATE: the drawn gun and the crosshair track together when the hand
      sweeps. Today they cannot, by construction.**

- [x] **P1-4(a) FIXED. (b) IS FALSIFIED — `163` §6/§7.**
      **(a)** `muzzle_origin` now reads the same `GE_VR_AIM_BASIS` source as the
      aim, so the two cannot drift apart again.
      **(b) ►►►► RETRACTED 2026-08-25 BY `171` §3. THE NODE EXISTS. ◄◄◄◄**
      `gunfire.c:633` reads **`mdlhdr->Switches[3]->Data`** — the per-weapon
      muzzle position in the gun model's own frame, **PD's
      `MODELPART_GUN_MUZZLEPOS` under a different name** — and **all four symbols
      it needs ARE patch-reachable** (`ModelNode`, `Switches`, `numSwitches`,
      `copy_of_body_obj_header`). **THE ERROR WAS THE SEARCH:** grepping
      `MODELPART` looked for PERFECT DARK'S IDENTIFIER, not for the MECHANISM.
      **Instrument built (`171`); the read happens on the next run — see `169`
      U-18.** *(original text, now retracted:)*
      **GOLDENEYE HAS NO MUZZLE MODEL PART. `MODELPART` has ZERO occurrences
      in the whole game tree; `MUZZLE` has exactly one datum —
      `f32 MuzzleFlashExtension`, `gun.h:18`, used at one site,
      `gunfire.c:739`. PD'S NODE DOES NOT TRANSFER and `-MuzzleExt` CANNOT be
      deleted.** Second PD constant to fail transfer after `155`.
      **THE CHEAP WIN THAT REPLACES IT (next build, `48` rule 5): default
      `GE_VR_MUZZLE_EXT` to the weapon's own `MuzzleFlashExtension`** — offset 0
      of the struct `ge_vr_aim.c` already declares, and `6D-02` already measured
      it at 100. **Per-weapon muzzles, by a different route.**
      **AND `gunfire.c:753-764` already computes a muzzle point** into
      `hand->field_B58` / `field_B64` — read it before estimating again (P1-6).

      *(original text:)* B3. THE MUZZLE.
      **`aim_screen_ndc` defaults to `GE_VR_AIM_BASIS 2` (the derived ray) while
      `muzzle_origin` still uses `g_geVrLastGunFwd` — basis 0, R's third row,
      which `158` §3 ALREADY FALSIFIED** (`row3=(-0.45,-0.84,0.30)`, dominated by
      Y). **It reads as working only because `GE_VR_MUZZLE_EXT` defaults to 0.**
      (a) point `muzzle_origin` at the same forward the aim uses;
      (b) **then look for the real answer:** PD reads the muzzle out of the model
      — `modelGetPart(modeldef, MODELPART_GUN_MUZZLEPOS)`, with
      `MODELPART_GUN_HOLDPOS` for thrown items and `posmtx` as the last resort
      (`bondgun.c:11507-11576`). **Search our `structs.h`/`externs.h` for
      `MUZZLE`; `6D-02`'s `muzzleExt=100` across 97 flat samples says the game
      already knows where its muzzle is.** If the node exists, **`-MuzzleExt`
      and its three sign knobs are deleted, and per-weapon muzzles are free.**
      **GATE: `157` G-A1b-3 — `-MuzzleExt 20` must walk the origin ALONG THE
      BARREL, not sideways.**

- [x] **P1-2b — THE FOV. `167`. BUILT, UNWORN.** The aim projected with
      `c_scalex/c_scaley` (from `c_perspfovy=106`) while the frame is DRAWN from
      the headset tangents (~88). **Vertical gap 1.374, horizontal 1.540 — TWO
      RATIOS, which is why it read as two bugs** ("worse going up" AND "off in a
      different way at the sides"). Now divided by the RENDER's own cyclopean
      tangents, measured live. **`163` §1's "the FOV read is no longer owed" is
      RETRACTED — see `166` §2.** Zero new constants. **The BULLET was never
      affected** (raw game-space ray); this moves the CROSSHAIR onto the barrel.

- [x] **P1-CROSSHAIR — `165`/`166`. THE CROSSHAIR WAS NEVER DRAWN, AND A 2D ONE
      CANNOT WORK IN STEREO.** `gunsightmode=2` is `GUNSIGHTREASON_NOTAIMING`,
      set from the AIM BUTTON nobody presses in VR — hidden for the whole
      project. Patched at `gunSetSightVisible`. **BUT the wearer then saw it
      DOUBLED, one place per eye:** the frustums are mirrored and asymmetric
      (`-1.4869/+1.0190`), so **no single pixel is correct for both eyes.** The
      crosshair is now only good for confirming the chain moves. **`166`.**

- [x] **P1-5 — B5. THE CLAMP SPLIT. BUILT (UNCOMPILED, UNWORN), `172`.**
      **AND THIS BOARD'S OWN PRESCRIPTION WAS BLOCKED:** moving the clamp into
      `gunDrawSight()` needs `crosshairimage` and `display_image_at_position`,
      **neither patch-reachable** (`115`'s hazard, which cost `157` a slice).
      **ROUTED AROUND IT ENTIRELY:** we already patch the PRODUCER
      (`caclulate_gun_crosshair_position_rotation`) and the CONSUMER
      (`bullet_path_from_screen_center`), so the unclamped aim is published from
      one and read by the other — and **`crosshair_angle` is left exactly as
      stock, so the unreachable `gunDrawSight` keeps pinning the sight with no
      change at all. ZERO NEW SYMBOLS.**
      **GATE G-172-1: BOTH HALVES or it is not the split** — the crosshair STOPS
      at the edge AND the shot keeps tracking the gun.

      *(original text:)* **STILL UNBUILT — AND NOTE `163`'s READ:**
      the stock split is ALREADY HALF PD's. `field_FFC` (the GUN model) is
      **never clamped** in stock code; only `crosshair_angle` is, and that is
      what the BULLET reads (`bullet_path_from_screen_center`). So the move is
      still to push the `[3, w-4]` clamp into `gunDrawSight()` — but the
      "prior art ships the break-the-lock" framing understates it: **GoldenEye
      already ships half of it.**
      Our `-FreeAim` unclamps `crosshair_angle`, which **both the draw and the
      shot read**, so the HUD crosshair walks off screen — deliberate as a
      proof, wrong as a shipping state. **PD clamps `crosspos` (drawn) and leaves
      `crosspos2` (bullet) free** (`bondgun.c:8419-8422` vs `:8468-8472`).
      **Move the `[3, w-4]` clamp into `gunDrawSight()`** — a second
      `RECOMP_PATCH`, 25 lines with four `#ifdef` branches.
      **GATE: crosshair pins at the screen edge; the shot keeps going.**

- [ ] **P1-6 — B4 / `6D-06`. AIM AT THE LASER DOT'S REAL HIT POINT.
      RE-COSTED BY `166` §5.2/§8.5, AND IT IS BIGGER THAN THIS ENTRY SAYS.**
      **PD DID NOT BUILD A LASER — THEY ALREADY HAD ONE.** `lasersightSetBeam`/
      `lasersightSetDot` are stock Perfect Dark (the Falcon 2's laser sight);
      their VR work only RE-POINTED it. **GoldenEye has no such subsystem**, and
      the nearest thing (`BeamRecord`, a bullet tracer) needs **five symbols and
      a struct that do not cross the patch boundary** — the same shape as the
      eight that made `157` withdraw a slice. **THIRD PD feature to fail
      transfer** after `155` and `163` §7. **Its own slice. Not four lines.**
      **WORTH RECORDING: PD added `VrlaserDotForALL` themselves** — a flag giving
      the dot to weapons with no laser sight, which is exactly what the owner
      asked for. **And PD's STALENESS TEST is the half we have no equivalent
      for:** `dotpos` unchanged since last frame means the raycast never wrote,
      so they fall back instead of drawing a lie (`48`, in shipped prior art).
      When `hand->dotpos` is fresh, **PD aims at the actual raycast HIT POINT
      instead of `muzzle + dir*100000`** (`bondgun.c:8365-8388`), with a
      `+-100000` sanity guard (`:16459`) and a staleness test that hides the dot
      when the value has not changed. **This is the exact cure for muzzle
      parallax up close, and it is why their crosshair sits ON the dot.**
      **`102` said A2 "may be a nicety". IT IS NOT — it is prior art's aiming
      INPUT, not its decoration.** Re-costed here as the cheap half of `6D-06`.
      **GATE: walk to a wall. The crosshair stays on the spot the barrel points
      at, at arm's length.**

---

# P2 — THE 6DoF FRAME AROUND THE AIM. Each is independent of the others.

- [ ] **P2-1 — `6D-03` / H1. THE RECENTRE MOVES TO LEVEL START.** The smallest
      slice in the plan and **it removes a confound from every task above.**
      Today it fires at process start with the headset on the desk (O60).
      **GATES: `154`-style — start a level wearing it and do NOT press F9;
      height and heading right immediately. F9 afterwards changes nothing.
      `-NoXr` untouched.**

- [ ] **P2-2 — `6D-12` / S1. FINISH THE WORLD-SCALE SWEEP.** `-HandUnitsPerMetre
      100` is **PINNED, a measurement.** `-WorldUnitsPerMetre` is a PERCEPTION
      and the direction is DOWN: 50 -> 100 (worse) -> 25 ("better") -> **12
      pending.** **HALVE, NEVER NUDGE.** Then `-ViewmodelScale` for the
      gun-to-guard ratio, **with the grip offsets halved alongside it**
      (`159` §4). **STAND NEXT TO A GUARD — he is guaranteed your height.**
      **IF IT BOTTOMS OUT AT 12 IT IS NOT STEREO** and `159` §6's FOV read is
      owed: S0 says `fovy=106` while the headset's tangents give ~88, and it is
      **not established that `widescreen.c` does not re-apply after our
      override.** That is a READ.

- [ ] **P2-3 — `6D-10` / H2. HEAD HEIGHT BECOMES A GAME QUANTITY. DISCUSS BEFORE
      BUILDING.** **Option A** (RT64 + ceiling clamp only) — small; crouching
      still does not make you a smaller target and the AI never knows.
      **Option B** (drive `eyeheight`) — physical crouch is real; ceiling, AI and
      cover follow, as PD's do. `86` recommends A first.
      **PD's numbers are measured and in `102`:** nominal 160 cm eye height,
      slider 130-200, a **90-sample MEDIAN** calibration, `VR_MAX_HEAD_CM 250`
      glitch swallow, and **crouch thresholds as FRACTIONS of the configured
      standing height (`/1.6` squat, `/1.3` duck) — because a running max was
      the original and a physical jump left you spuriously ducking.**
      `89` READ 10: `bondviewUpdatePlayerCollisionPositionFields` is 95 lines and
      patchable; READ 9: `autocrouchpos` will not fight a written height.

- [ ] **P2-4 — `6D-11` / R1. ROOMSCALE LEAN.** Only after P2-3 option B.
      **PD's whole design is in `102`:** a 12-unit probe as a **slab** at eye
      level (`YMAX +10`, `YMIN -10`) so waist-high rails pass under it; **the
      test is `GEOFLAG_BLOCK_SIGHT`, NOT solidity** — *"geometry you can see
      through, your head goes through"*; a **second LOS test along the lean** so
      you cannot pop through a thin wall; `delta.y = 0` because vertical is
      mapped absolutely by eye height; a 25-unit step rejection; and
      **THE FADE MUST BE DRAWN BEFORE THE HUD** — a stereo-specific bug they
      already paid for, where a fade emitted after the HUD capture regions
      reached only one eye.

- [ ] **P2-5 — `6D-13` / C1. `vr.json`, HOT-RELOADED (O48).** PD tune while
      worn, from `pd-vr.ini`. **Every task above gets cheaper after this, and
      this project has already spent dozens of relaunches proving it.**
      Deliberately below P1 only because P1-2 deletes most of the knobs.

- [ ] **P2-6 — `6D-04` / H3. THE BODY YAW AS A NAMED QUANTITY.** **Not on A1's
      critical path** (`153` §2 — the gun and camera share it, so it cancels).
      Still worth building for G1/G2/G3 and any true world-space work, and
      `86` rule 8 stands: every consumer reads it, nobody re-derives it.
      **PD's trap, already paid for: do NOT counter-rotate by absolute head yaw
      — "a 360 spin unwound the elbows." Use a smoothed follower yaw** (`102` §4).

---

# P3 — AFTER THE ABOVE. RECORDED SO IT IS NOT RE-INVENTED.

- [ ] **P3-1 — HOST-SIDE RECOIL.** `vr_input.cpp:897-1160`, and its own comment
      says **"100% on OpenXR side, no engine dependency"**: a five-field spring
      profile per weapon, integrated at a fixed `dt = 1/90` (with their own TODO
      to use the real delta), applied to the controller pose before the game sees
      it. **Our host owns the same pose, so this is close to a drop-in.**
      **The ~60 per-weapon profiles do NOT transfer — the CLASSES do.**

- [ ] **P3-2 — PER-WEAPON GRIP OFFSET TABLE.** `102` §3 has six classes.
      **`86` §7 still stands: no table until two weapons are MEASURED to
      disagree.** P1-4(b) may make it unnecessary entirely.

- [ ] **P3-3 — THE VR HUB / menu environment.** PD ship one (`vr_hub.cpp`).
      O61, `MODS-IDEAS`. **Not now.**

**DELIBERATELY NOT DOING** (`86` §7, unchanged): no IK arm — *a wrong arm is more
distracting than none*; no two-handed aim; no gestures or throwing; no scope
(`37` trap 3).

---

## THE ORDER, AND WHAT BLOCKS WHAT

```
P0-1  controllers bind ──────────────► NOTHING BELOW IS JUDGEABLE WITHOUT IT
P0-2  read the log ──────────────────► free, and decides whether P1-2 is urgent
P0-3  the two guards ────────────────► one build, no headset
P0-4  B3/B4 bugcheck ────────────────► makes every wear test below cheap

P1-1 read the projector ─► P1-2 PROJECT THE RAY ─┬─► P1-4 muzzle
                                                 ├─► P1-5 clamp split
                           P1-3 both integrators ┘   └─► P1-6 aim at the dot

P2-1 recentre   (independent, removes a confound from all of the above)
P2-2 scale      (independent)
P2-3 head height (DISCUSS) ─► P2-4 roomscale
P2-5 vr.json    (independent)
P2-6 body yaw   (independent)
```

---

## STATE CARRIED FORWARD FROM `148` — NOTHING BELOW NEEDS REBUILDING

| | Where | State |
|---|---|---|
| **S0, the 6DoF instrument** | `91`, `100` | Built and emitting. **G0-1/G0-2 pass; G0-3 owed** (one monitor launch) |
| **`6D-02` muzzleExt** | `90`, `148` | **DONE** — `100` flat across 97 samples; five falsifiers five for five |
| **`6D-08` / G2 rotation basis** | `155` | **DONE** — `-HandAxisX -1 -HandAxisZ -1`, first launch. **PD's 1.5708 post-rotation FALSIFIED** |
| **`6D-09` / G3 grip offset** | `154` | **IN PROGRESS** — `-GunOffY 8 -GunOffZ -2` fixed the pivot. `-GunOffFwd` convention still for the wearer to settle |
| **A1 unclamp** | `153` | Built behind `-FreeAim`. **Inert until P1-2** |
| **A1b origin** | `157` | **WORN AND WORKING** — *"bullets come out of the gun"* — **but see P1-4** |
| **A1c direction** | `158` | Built, **REFUSED on every frame so far**. P0-2 then P1-2 |
| **Route B / the judder** | `147` | **CLOSED.** RB-03 (world at 60 steps) parked by owner decision |
| **PD constants** | `102`, `160` | Read at `67ea20c`. **Source now local and permanent** |

**THE STANDING COMMAND, until P1-2 deletes half of it:**

```powershell
.\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
         -WorldUnitsPerMetre 12 -HandUnitsPerMetre 100 `
         -ViewmodelScale 0.5 -GunOffY 8 -GunOffZ -2 `
         -HandAxisX -1 -HandAxisZ -1 `
         -AimFromHand -AimFwdNeg 0 -MuzzleOrigin
```

**CLOSE WITH `taskkill /F /IM GoldenRecomp.exe`.**
