# 169 — THE UPGRADE SHEET. A LIVING CATALOGUE. APPEND, DO NOT REWRITE.

**Opened 2026-08-25.**

> ## WHAT THIS FILE IS, AND WHAT IT IS NOT
>
> **`161` IS THE PLAN — the ordered board of what is being built NOW, with gates.**
> **THIS IS THE CATALOGUE — everything we have found that WOULD be an upgrade,
> whether or not anyone intends to build it yet.**
>
> An item lives here from the moment it is FOUND. It moves to `161` only when
> someone decides to build it. **Nothing is ever deleted from this file** — a
> rejected idea with its reason is worth more than a blank space, because it stops
> the next session re-finding it. `108` is why.

> ## ►►►► TEST STATUS, 2026-08-25. READ BEFORE BELIEVING A "BUILT". ◄◄◄◄
>
> **"BUILT" IN THIS FILE MEANS COMPILED-READY. IT DOES NOT MEAN WORN.**
>
> | | |
> |---|---|
> | **WORN AND PASSED** | **U-01** (`170`+`173` — the crosshair fuses) · **U-17** (`165` — the crosshair is drawn at all) |
> | **BUILT, NEVER WORN** | **U-16** (`172`) · **U-19** (`175`) · **U-09** (`176`) · `174` head anchor · `173` seam composition |
> | **IN A BINARY BUT NEVER ISOLATED** | `167` the FOV fix — worn as part of a whole, never A/B'd against `-NoAimFrustum` |
> | **INSTRUMENT BUILT, READ PENDING** | **U-18** (`171` — MUZZLENODE) |
>
> **THE ORDERED TEST SCRIPT IS `MAIN-STATION-TASKS.md`** — eleven runs from ONE
> build, each changing exactly one thing, sequenced so **no test can invalidate a
> test above it.** Do not test these ad hoc: **`T9` (seam composition) and `T10`
> (crouch) RE-REFERENCE everything else** and are deliberately last.

## HOW TO ADD AN ENTRY

Every entry carries these six fields, and **an entry without EVIDENCE and
BLOCKERS is not an entry, it is a wish:**

| field | meaning |
|---|---|
| **ID** | `U-nn`. Never reused, never renumbered. |
| **WHAT** | One sentence. What the player would notice. |
| **EVIDENCE** | File and line, ours or PD's. Where the claim comes from. |
| **COST** | KNOB / SLICE / PROJECT. See the scale below. |
| **BLOCKERS** | Named symbols, named unknowns, or "none identified". |
| **VERDICT** | DO NEXT / READY / NEEDS A READ / BLOCKED / DECIDED AGAINST |

**THE COST SCALE, calibrated on work already done:**

- **KNOB** — a launch flag or a constant. No rebuild, or a trivial one. *(e.g. the
  scale match in `166` §3.)*
- **SLICE** — one behaviour change, one build, one wear test. `48` rule 5.
  *(e.g. `163`, `167`.)*
- **PROJECT** — needs its own plan document and more than one build.
  *(e.g. the laser, `168` §4.1.)*

> ## ►►►► STANDING POLICY, OWNER'S DECISION 2026-08-25: DELETE NOTHING. ◄◄◄◄
>
> ***"I don't want to delete anything until we are done. We never know when we can
> make use of something, or maybe we do not fully understand the functionality."***
>
> **THIS OVERRIDES EVERY "SHOULD BE DELETED" IN THE DOCS**, including `163` §4 on
> the five dead aim knobs (`-AimGain`, `-AimSignX/Y`, `-AimFwdAxis`, `-AimFwdNeg`),
> `161` P1-2's "deleted, not defaulted", `174` §5 on the trim, and `163` §7 on
> `-MuzzleExt`. **Those knobs stay. Mark them SUPERSEDED and leave them reachable.**
>
> **AND THE PROJECT'S OWN HISTORY ARGUES FOR IT:** `171` §3 retracted a feature
> written off as absent; `162` §4 found a "trap" default that was correct under a
> basis nobody had re-read. **Twice this month a thing believed useless turned out
> to be misunderstood rather than dead.** A knob costs a branch; a deleted knob
> costs the next session the read that discovered it.
>
> **WHAT THIS DOES NOT LICENSE:** leaving a knob READ on a live path when a
> derived value is available. Supersede means "no longer consulted by the default
> path", not "still silently in the maths".

> ## ►►►► STANDING POLICY, OWNER'S DECISION 2026-08-25: THE OWNER MAKES EVERY GIT COMMIT. ◄◄◄◄
>
> ***"All git commits need to be performed by me when I am at my main PC."***
>
> **NO SESSION COMMITS, STAGES, BRANCHES, MERGES, RESETS OR TAGS. EVER.**
> Reading git state (`git status`, `git log`, `git diff`) is fine and useful.
> **Writing to the repository's history is the owner's, exclusively.**
>
> **AND THE BRIDGE ENFORCES IT ANYWAY, WHICH IS WHY THIS MUST BE WRITTEN DOWN
> RATHER THAN ASSUMED:** git cannot take `.git/index.lock` through the device
> mount, so a staging attempt fails with a permissions error that looks like a
> broken tool rather than a policy. **A future session that does not know the rule
> will read that error as something to work around.**
>
> **WHAT A SESSION DOES INSTEAD:** finish the work, leave the tree clean and
> described, and **put the exact commands in `MAIN-STATION-TASKS.md`** for the
> owner to run.

> ## ►►►► THE RULE THAT HAS COST THIS PROJECT TWO SLICES ◄◄◄◄
>
> **BEFORE COSTING ANYTHING THAT TOUCHES GAME CODE, GREP
> `patches/externs.h` AND `patches/structs.h` FOR EVERY SYMBOL IT NEEDS.**
> `157` withdrew a slice for want of eight symbols. `166` §5.2 stopped one before
> a line was written for want of five. **That grep is the cheapest step here.**

---

# OPEN ENTRIES

## U-01 — PER-EYE HUD SHIFT (fixes the doubled crosshair)
- **WHAT:** The crosshair and HUD stop appearing in two places at once.
- **EVIDENCE:** PD `vr_openxr.cpp:2386` and `:1989`. **Their canting term evaluates to `-0.1867` for our eye 0, which is EXACTLY the `m20=-0.18669` already in our own projection log.** `166` §1, `168` §2.1.
- **COST:** SLICE.
- **BLOCKERS:** none.
- **VERDICT:** ►► **BUILT AND WORN 2026-08-25. `170` + `173`. THE CROSSHAIR FUSES.** ◄◄ **AND IT TOOK THREE ATTEMPTS, TWO OF WHICH WERE MINE:** (1) `170` put the shift on the ORTHOGRAPHIC projection matrix — **but GoldenEye's HUD sprites are `Type::Rectangle`, a third projection type that carries NO MATRIX AT ALL** (`173` §2), so the edit was structurally incapable of moving the crosshair at any sign; (2) the sign was inverted, because **the matrix entry's sign is not the sign it produces in NDC** — the perspective divide flips it (`173` §1). **The wearer's "it's not merging" plus WHICH WAY they diverged named the sign before any algebra.** Now applied in the `Type::Rectangle` case in 10.2 fixed point, skipping full-width rects.
- **RESIDUAL:** it biases toward the right eye — **that is U-19 / `174`.** **THE CAUSE WAS ONE LINE:** `rt64_projection_processor.cpp:156` gates every per-eye adjustment on `Type::Perspective`, and **the HUD is ORTHOGRAPHIC** — so it has been excluded since stereo existed. Fixed at `[3][0]` (ortho has no perspective divide, so the canting becomes a constant in the translation row). **Term 1 has no free parameter.** Optional `-HudDepth` in metres; default 0 = infinity. **Gate G-170-2: the logged `eye0`/`eye1` MUST differ — equal means the shift never reached the projection, which looks identical in the headset to not having built it.**

## U-02 — HOST-SIDE WEAPON RECOIL
- **WHAT:** The gun kicks in your hand, per weapon class.
- **EVIDENCE:** PD `vr_input.cpp:908-1170`. Their own comment: *"100% on OpenXR side, no engine dependency."* Five floats per profile, spring-integrated, applied to the controller pose before the game sees it.
- **COST:** SLICE.
- **BLOCKERS:** none. Needs one call site on our fire path for `vrRecoilNotifyShotFired`.
- **VERDICT:** READY. **The ~60 PD profiles do NOT transfer; the CLASSES do.** `86` §7: no table until two GE weapons are measured to disagree.

## U-03 — SNAP TURN
- **WHAT:** Comfort option — turn in discrete steps instead of continuously.
- **EVIDENCE:** PD `bondwalk.c:105-113`. A boolean and a branch.
- **COST:** SLICE (small).
- **BLOCKERS:** none.
- **VERDICT:** READY. The most requested comfort option in any VR shooter.

## U-04 — SETTINGS FILE + IN-GAME VR MENU
- **WHAT:** Tune while wearing the headset instead of relaunching.
- **EVIDENCE:** PD `vr_settings.cpp` (`pd-vr.ini`, plain `Key=%.4f`) and `mainmenu.c` (checkboxes and stepped sliders). ~25 knobs.
- **COST:** PROJECT.
- **BLOCKERS:** our `enabled` flags are `static const`, latched on first call (`162` §6) — **hot reload needs those un-latched.** Recorded there before it bit anyone.
- **VERDICT:** READY, but **deliberately after P1-2**, which deletes most of the knobs it would expose. This is `161` P2-5.

## U-05 — THE LASER SIGHT / DOT AIMING
- **WHAT:** A visible beam and dot showing exactly where the shot goes; and aiming AT the dot's real hit point.
- **EVIDENCE:** PD `bondgun.c:8367-8395`, `:10251`. **PD did not build this — the Falcon 2's laser sight is stock Perfect Dark and their VR work only re-pointed it.**
- **COST:** PROJECT.
- **BLOCKERS:** **five symbols and a struct that do not cross the patch boundary** — `BeamRecord`, `CapBeamLengthAndDecideIfRendered`, `gunCreateBeamForHand`, `currentPlayerGetViewToWorldMtxf`, `mtx4TransformVecInPlace` — plus four `unk` fields, one of which (`unk00 = -1`) silently means "do not render". `166` §5.2.
- **VERDICT:** ►► **DOWNGRADED 2026-08-25 BY `177` §4 — THE STRUCT HALF IS SOLVED.** ◄◄ `BeamRecord` is **fully defined** at `src/bondtypes.h:2305` with offsets, and the patch-side slot exists at a verified offset (`ChrRecord_f180 field_A54` @ `0xA54`, anchored by `noise` @ `0xA80`). **If we fill a BeamRecord ourselves, `CapBeamLength...` and `gunCreateBeamForHand` are not needed — they construct a struct we would construct.** **REMAINING BLOCKER: the beam is WORLD space and `currentPlayerGetViewToWorldMtxf` is still unreachable.** Two unread routes in `177` §4. **PD added `VrlaserDotForALL` themselves** to give the dot to weapons with no laser sight, which is exactly what the owner asked for. Unlocks U-06.

## U-06 — CROSSHAIR PARALLAX BY TARGET DISTANCE
- **WHAT:** The crosshair stays true up close, not just at range.
- **EVIDENCE:** PD `vr_openxr.cpp:2396`, `vrComputeCrosshairParallax` — clamped to `+-0.02`, 1.75 m nominal.
- **COST:** SLICE.
- **BLOCKERS:** needs a target distance, i.e. the raycast hit. **Blocked on U-05.**
- **VERDICT:** BLOCKED. This is the principled cure for the close-range disagreement `163` §8 pre-registered.

## U-07 — MANUAL RELOADING BY GESTURE
- **WHAT:** Rack the weapon with a physical pull.
- **EVIDENCE:** PD `vr_input.cpp:832`, `vrUpdateReloadPull`. Relative motion of both controllers rotated into the right hand's local frame by the conjugate quaternion.
- **COST:** SLICE.
- **BLOCKERS:** ►► **RESOLVED BY `177` §3.** ◄◄ `bond_pressed_reload_activate()` is one line returning `g_CurrentPlayer->field_D0`, and **`field_D0` IS patch-reachable** (`structs.h:2005`) even though none of the three reload FUNCTIONS are. **So no function needs patching — write the field the game already polls.** `172` §7's rule in a new place.
- **VERDICT:** **READY**, with one caveat: `lv.c:733` also requires `&& bond_interact_object()`, **whose meaning is UNREAD.** If it gates on proximity to something usable, a gesture reload would work only sometimes — which would read as an unreliable gesture rather than a missing condition.

## U-08 — SMOOTHED BODY YAW AS A NAMED QUANTITY
- **WHAT:** A torso that follows the head instead of snapping to it.
- **EVIDENCE:** PD `bondgun.c:11003`, `VrBodyYaw += d * VrArmBodyFollow`, `VrArmBodyFollow = 0.02f`. **A follower, not the head yaw** — `102` §4's recorded trap (*"a 360 spin unwound the elbows"*).
- **COST:** SLICE.
- **BLOCKERS:** none.
- **VERDICT:** READY. **Already on the board as `161` P2-6 / `6D-04`;** this entry adds PD's actual constant to start from.

## U-09 — PHYSICAL HEIGHT MATCHING AND REAL CROUCH
- **WHAT:** Crouch by crouching; be a smaller target when you do.
- **EVIDENCE:** PD `bondwalk.c:1824`. Numbers already in `102`: 160 cm nominal, 130-200 slider, **90-sample MEDIAN** calibration, `VR_MAX_HEAD_CM 250` glitch swallow, crouch thresholds as **fractions of standing height** (`/1.6`, `/1.3`) because a running max left you spuriously ducking after a jump.
- **COST:** PROJECT.
- **BLOCKERS:** design decision, not code — Option A vs B. `86` recommends A first.
- **VERDICT:** ►► **DISCUSSED AND DESIGNED 2026-08-25. `176`. READY TO BUILD.** ◄◄ **The AI's "shoot lower at a crouched player" behaviour is ALREADY STOCK** (`chrprop.c:1413` picks `HIT_GENERAL`/`HIT_GENERALHALF` from `currentPlayerGetCrouchPos()`) **and has simply never been told**, because `crouchpos` only moves on a button press. **`86`'s Option B is BLOCKED — `eyeheight` is not patch-reachable — and is NOT NEEDED, because in VR the view lowers physically.** Owner's decisions: **suppress the engine's `ducking_height_offset`** (or you crouch twice), **keep the SQUAT speed penalty**, **calibrate standing height at level start** by 90-sample median.

## U-10 — ROOMSCALE LEAN
- **WHAT:** Lean around corners with your body.
- **EVIDENCE:** `102`. A 12-unit probe as a **slab** at eye level so waist-high rails pass under it; the test is **`GEOFLAG_BLOCK_SIGHT`, not solidity**; a second LOS test along the lean; `delta.y = 0`; 25-unit step rejection; **and the fade must be drawn BEFORE the HUD** — a stereo bug PD already paid for.
- **COST:** PROJECT.
- **BLOCKERS:** depends on U-09 option B.
- **VERDICT:** BLOCKED. `161` P2-4 / `6D-11`.

---

# ENTRIES DECIDED AGAINST — KEPT SO THEY ARE NOT RE-FOUND

## U-11 — IK ARM
- **DECIDED AGAINST**, `86` §7: *"a wrong arm is more distracting than none."*
- **BUT NOTE:** PD's `VrArmElbowTuck = 0.80f` (`bondgun.c:183`) is a much weaker thing than full IK. **Re-opening is allowed; drifting into it is not.**

## U-12 — TWO-HANDED AIM
- **DECIDED AGAINST**, `86` §7. **PD default it to TRUE** (`bondgun.c:1057`), so this is a real disagreement with prior art, not an oversight. **Re-open only after the one-handed aim chain is closed.**

## U-13 — GESTURE THROWING / SCOPE / VR HUB
- **DECIDED AGAINST**, `86` §7 and `37` trap 3. VR hub is `161` P3-3, *"Not now."*

---

# GOLDENEYE-NATIVE IDEAS — NOT FROM PD

*(This section exists so the sheet is not only a PD port list. `MODS-IDEAS.md`
is the older home for these; move anything here that acquires evidence.)*

## U-14 — PER-WEAPON MUZZLE FROM `MuzzleFlashExtension`
- **WHAT:** *(proposed)* Default `GE_VR_MUZZLE_EXT` to the weapon's own `MuzzleFlashExtension`.
- **VERDICT:** ►► **DECIDED AGAINST — FALSIFIED 2026-08-25. `171` §2.** ◄◄
- **WHY, SO IT IS NOT RE-PROPOSED:** `gunfire.c:754` passes it to `matrix_column_3_scalar_multiply`, which scales `matrix[8..11]` — **ROW 2, the Z BASIS ROW** (`matrixmath.c:408`). **It never touches `m[3][*]`, the position. It STRETCHES THE MUZZLE-FLASH SPRITE. It is a visual scale, not a distance, and it moves nothing.** `6D-02`'s measurement of `100` was right; the *interpretation* was wrong. **Wiring it in would have pushed the bullet origin ~1 m down the barrel and looked exactly like a bad grip offset** — which this project has already mis-attributed once (`163` §6). **The next reader will find `muzzleExt=100` in `6D-02` and reach for it exactly as I did. This entry is why they should not.**

## U-15 — THE GAME ALREADY COMPUTES A MUZZLE POINT
- **WHAT:** Stop estimating the muzzle; read the one the game builds.
- **EVIDENCE:** `gunfire.c:753-764` applies `flashext` to `gunmtx` and writes `hand->field_B58` (world, via `currentPlayerGetViewToWorldMtxf()`) and `hand->field_B64 = -flashmtx.m[3][2]`. **Pre-transform, `flashmtx.m[3][*]` is the muzzle in exactly the camera frame `bullet_path_from_screen_center`'s `arg0` wants.**
- **COST:** NEEDS A READ.
- **BLOCKERS:** it only runs when `flashdata != NULL`, so **it is not a per-frame source.** `currentPlayerGetViewToWorldMtxf` is also not patch-reachable (see U-05). **BUT `177` §2 solved the frame question — see U-18.**
- **VERDICT:** NEEDS A READ, **and SUPERSEDED IN PART by U-18**, which reaches the same muzzle at its SOURCE (the model node) rather than downstream of a matrix we cannot reach. `171` §5.

## U-16 — THE STOCK CLAMP SPLIT IS ALREADY HALF DONE
- **WHAT:** The crosshair pins at the screen edge while the shot keeps going.
- **EVIDENCE:** **`field_FFC` is NEVER clamped in stock GoldenEye** — only `crosshair_angle` is, and that is what the bullet reads. `163` §10. PD do the same split (`bondgun.c:8419` vs `:8468`).
- **COST:** SLICE.
- **BLOCKERS:** ~~none~~ **THAT WAS WRONG.** Moving the clamp into `gunDrawSight()` needs `crosshairimage` and `display_image_at_position`, **NEITHER of which is patch-reachable** — `115`'s hazard, which already cost `157` a slice. **This entry was costed from the game source without checking the boundary: the exact failure `168` §5 prescribes the cure for.**
- **VERDICT:** ►► **BUILT 2026-08-25, UNWORN. `172`.** ◄◄ **Routed around the blocker entirely:** we already patch the PRODUCER (`caclulate_gun_crosshair_position_rotation`) and the CONSUMER (`bullet_path_from_screen_center`), so the unclamped aim is published from one and read by the other — **and `crosshair_angle` is left exactly as stock, so the unreachable `gunDrawSight` keeps pinning the sight with no change at all. ZERO NEW SYMBOLS.**
- **THE LESSON, WORTH MORE THAN THE SLICE:** **a game function you cannot patch is not always a blocker. If you own the producer and the consumer, change what flows between them.** `157` withdrew a slice for want of eight symbols; this needed none, and **the difference was asking what the function READS rather than what it DOES.**

## U-17 — THE CROSSHAIR WAS NEVER DRAWN AT ALL
- **WHAT:** *(Already fixed, `165`. Kept as a catalogue entry because the mechanism generalises.)*
- **EVIDENCE:** `gunsightmode = 2` is `GUNSIGHTREASON_NOTAIMING`, set every tick from the **aim button** (`bondview2.c:5471`). Nobody presses it in VR, so the bit never cleared and the crosshair was hidden **for the entire project**.
- **VERDICT:** DONE. **THE GENERAL LESSON, WHICH IS THE REASON THIS STAYS:** GoldenEye has other button-gated states that VR will never enter. **Anything that "does not appear in VR" should be checked against a game-side gate BEFORE it is investigated as a rendering fault.**

---

## U-18 — THE MUZZLE NODE. `163` §7 WAS WRONG AND THE NODE EXISTS.
- **WHAT:** Every weapon's shot leaves from its own barrel, read from the gun model, with no tuning knob at all.
- **EVIDENCE:** `gunfire.c:633` — **`flashdata = (f32 *) mdlhdr->Switches[3]->Data;`** — then `gunfire.c:746` uses it as a `coord3d` position. **`Switches[3]->Data` IS the muzzle position in the gun model's own frame, per weapon: PD's `MODELPART_GUN_MUZZLEPOS` under a different name.** `171` §3.
- **COST:** SLICE, once the frame is established.
- **BLOCKERS:** ►► **CLEARED 2026-08-25 BY `177` §2.** ◄◄ `gunmtx` is NOT local — `gunfire.c:572` copies it to **`hand->gunmtx_camspace`**, the gun's matrix in CAMERA SPACE, exactly the frame `bullet_path_from_screen_center` wants. **And the patch-side slot is there at a verified offset:** sixteen consecutive `s32` placeholders `field_A98`..`field_AD4` = `0x40` bytes = one `Mtxf`, with **both sides anchored on `throw_item_pos_related` @ `0xad8`.** **A transcription, not reverse-engineering.** **All four symbols ARE patch-reachable** (`ModelNode`, `Switches`, `numSwitches`, `copy_of_body_obj_header` — four for four in `patches/structs.h`).
- **VERDICT:** **INSTRUMENT BUILT, READ PENDING.** A `MUZZLENODE` log line now prints `Switches[3]`, `numSwitches` and `flashExt` side by side. **The next run decides three things:** is the node present on every weapon; does it CHANGE between weapons (if a pistol and a rifle report the same vector it is not a per-weapon muzzle and this is over); and what is its magnitude, which establishes the model frame's scale. **If all three pass, `-MuzzleExt` and its three sign knobs are DELETED and per-weapon muzzles come free.**
- **AND IT SHARPENS `168`'s RULE:** `163` §7 searched for `MODELPART` and found zero, which was true and meant nothing. **Search for the MECHANISM, never for PD's identifier.**

## U-19 — THE FLAT GAME IMAGE IN VR, INSTEAD OF THE RED/BLUE FALLBACK
- **WHAT:** Menus, the front end, loading and cutscenes show the GAME on a virtual screen instead of a flat red/blue clear — so the headset never has to come off, and the VR controllers keep working. **The owner asked for this from his own testing loop: switching to the desktop view switches to desktop controls.**
- **EVIDENCE:** **NOT A BUG AND NOT A DIAGNOSTIC LEFT ON.** `ge_vr_xr.cpp:1632` says so outright: *"Null is a normal state, not a failure: the front end, menus, cutscenes and the opening frames all legitimately have no eye split. The caller falls back to the 3f-2 flat colour, which says 'no image' unambiguously instead of showing a stale one."* The clear is at `:2133`; the convention is `docs\10`'s (left red, right blue).
- **COST:** **SLICE** for the crude version (same flat image to both eyes, full FOV — usable, a bit overwhelming). **PROJECT** for the good one (a sized quad at ~2 m with the surround dimmed).
- **BLOCKERS:** **ONE, and it is small.** RT64 publishes only `vrPresentEyeTexture[2]`; **there is no shared slot for the flat present image.** Add one, publish the desktop present target into it, and blit in the `else` branch that currently clears.
- **WHAT ALREADY EXISTS:** the **entire blit pipeline** — `g_twRoot`, `g_twPso`, `g_twSrvHeap`, a fullscreen triangle with a texture SRV and **16 float constants** (the timewarp path). **Those constants are exactly the quad transform the good version needs**, so the gap between crude and good is much smaller than usual.
- **VERDICT:** ►► **BUILT 2026-08-25, UNWORN. `175`.** ◄◄ Done as a **real 3D rectangle**, not a blit: a fullscreen triangle reconstructs each eye's view ray from its OWN frustum tangents and intersects a plane at `-dist`. **The stereo is free** — the ray starts at that eye's offset from the head centre, so the screen has genuine depth and **needs none of the per-eye HUD machinery `173` fought over.** Source comes through `prepareEyeFromTarget`, the SAME path the eyes use, so there is no second route by which a frame can reach the headset. `-ScreenDist` / `-ScreenSize` in metres. **Red/blue REMAINS the fallback**, so "flat mode" and "no image at all" never become ambiguous.
- **NOT A PORT, AND THIS WAS CHECKED:** **PD's `vr_hub.cpp` is NOT this feature.** It is a decorative OpenGL environment — procedural floor grid, sky, logo decal — for their pause menu, and **it never displays the game image.** OpenGL against our D3D12 besides. The general "flat screen in VR" pattern is well-trodden (vorpX, REAL VR, UEVR) but all are **closed-source injectors wrapping other engines**, and upstream RT64 / Zelda64Recomp have no VR layer at all. **THIS ONE IS OURS TO WRITE.**

## U-20 — THE VR ROOM. PD'S HUB ENVIRONMENT, RE-SKINNED FOR GOLDENEYE
- **WHAT:** Instead of a flat screen floating in blackness, the menus and front end sit in a **room** — a floor, a horizon, a themed backdrop. **The owner wants this and intends to customise it to GoldenEye** (Dam sluice, Facility tiles, the gun-barrel iris, a Q-Branch workshop — the art direction is his).
- **EVIDENCE:** PD `port/vr/vr_hub.cpp`, 410 lines. `vr_hub_render(const float eyeViewProj[2][16])` — per-eye view-projection matrices in, room out.
- **AND IT IS FAR SMALLER THAN "410 LINES" SUGGESTS.** The geometry is **two quads, 12 vertices total**: `BuildFloorMesh()` is 6 verts of a ground plane, `BuildSkyMesh()` is 6 verts of an NDC fullscreen quad. **Everything you actually SEE is procedural fragment shader** — grid lines with distance fog on the floor, a banded gradient on the sky, plus one logo decal texture. **There are no art assets to port.**
- **COST:** SLICE for a first room (floor + horizon). PROJECT for a themed, polished one.
- **BLOCKERS:** **OpenGL vs D3D12.** PD's shaders are GLSL compiled at runtime (`CompileShader`/`LinkProgram`); ours is a D3D12 XR layer. **The GLSL must be rewritten as HLSL** — a translation, not a redesign, because the shaders are self-contained maths with no engine dependencies.
- ►► **DEPENDS ON U-19, AND THAT IS THE POINT.** ◄◄ U-19 puts a **textured quad with per-eye matrices** into the XR layer. **That is the same machinery this needs** — U-20 is then "draw two more quads behind it with different shaders". **Do U-19 first and this stops being a from-scratch feature.**
- **VERDICT:** **PLANNED — OWNER WANTS IT. AND U-19 IS NOW BUILT (`175`), SO THE DEPENDENCY IS CLEARED.** The textured quad with per-eye matrices exists in the XR layer; this becomes *"draw two more quads behind it with different shaders"* rather than a from-scratch feature. **NOTE FOR WHOEVER PICKS THIS UP: this is one of the few PD features where the DESIGN transfers almost completely** (`168`'s rule usually cuts the other way) — because the hub calls into nothing. No lasersight, no model parts, no game state. **Two quads and some maths.**

## U-21 — THE SIGHT PINS WITH ITS CENTRE ON THE FRAME EDGE, SO HALF THE CROSSHAIR HANGS OFF
- **WHAT:** At full deflection the crosshair rests with its CENTRE four pixels inside the frame, so the glyph is half outside it. `[REPORTED]` *"the target is partially off on whatever corner I left it at"*, and `[REPORTED]` partly clipped but still visible.
- **EVIDENCE `[READ]` + `[MEASURED]`:** the cone clamp bounds `nx` to `+-1` (`188`), `ge_vr_aim.c:552` maps that to `320` on a 320-wide screen — the edge exactly — and the stock `[3, w-4]` clamp at `:596` brings it to **`316`**. **`187`'s log printed it: `SIGHT crosshair_angle=(316,21)px CLAMPED`.**
- **NOT OURS AND NOT NEW.** `[3, w-4]` is stock GoldenEye, a 1997 margin sized for CRT overscan. **A VR frame edge has nothing beyond it.**
- **COST: SLICE. Small.** Widen the margin in OUR OWN copy of the clamp by roughly half a crosshair width.
- **BLOCKERS: NONE, and the reachable route is already established.** `172` proved `gunDrawSight` is NOT reachable (`crosshairimage` and `display_image_at_position` are absent from `externs.h`) — **but we do not need it: the clamp we would change is in our own patch.** ZERO new symbols.
- ►► **THE TRAP, AND IT IS THE WHOLE DESIGN NOTE:** do **NOT** inset `188`'s cone limit instead. **That would move the BULLET in with the sight and undo U-16** — the published `g_geVrTrueAimPx` is taken from `crosshair_angle` before the clamp but after `nx`. **Change the clamp, never the cone.**
- ►► **THE CONSTANT IS NOW KNOWN AND IT WAS NEVER A TUNING QUESTION — `213` §2.1.** `[READ]` `gunfire.c:6225`: `display_image_at_position(..., 0x20, 0x20, ...)` — **THE GLYPH IS 32x32 PIXELS.** The `[3, w-4]` clamp pins the sight's CENTRE at `316` on a 320-wide screen, **so exactly 16 px, half the glyph, hangs off.** The inset is **16**, measured, no run needed.
- **VERDICT:** **OPEN, cheap, not on the critical path — and now a ONE-CONSTANT change.** `190` §2, `213` §2.1.

## U-22 — A LOST CONTROLLER POSE SHOULD HOLD THE AIM, NOT GLIDE IT TO THE CENTRE
- **WHAT:** When tracking drops, the crosshair slides to screen centre and then re-attaches when the controller returns. `[REPORTED]` *"If my controller snaps out of camera view the target resets in the center before attaching back to controller when it comes back into the view."*
- **EVIDENCE `[READ]`:** `ge_vr_aim.c:324` — the aim block is behind `else if (geVrAimFwdHead(...))`, so no pose means the block never runs, and `:285-286` becomes `crosshair_x_pos * guncrossdamp + 0`: **an exponential decay to zero, which is centre.** `160` §2 recorded the same behaviour from a different cause.
- **WHY IT IS WORTH CHANGING:** **a lost pose means "I do not know where the gun is". Gliding to centre ASSERTS that the gun is level and forward.** `48`'s rule is that an instrument must be able to say *"I cannot answer this"* — the aim path can, and then the integrator answers anyway.
- **COST: SLICE.** Hold the last published aim while the pose is missing; knob-gated, and it needs a staleness limit so a controller left on the desk does not pin the sight forever.
- **BLOCKERS: NONE.** Our own patch state, zero new symbols.
- ►► **SEQUENCING, NOT A BLOCKER: DO NOT LAND THIS IN THE SAME RUN AS AN AIM CHANGE.** It changes what a wear test LOOKS like during a dropout, which is exactly how `48` rule 5 gets violated by accident.
- **AND CLOSE THE INSTRUMENT GAP FIRST (`190` §3):** `aimed` and `refused` are BOTH incremented inside the pose branch, **so a frame with no pose is counted in neither** and a dropout is invisible in `A1-VERIFY`. **One `noPose` counter, no behaviour change.**
- **VERDICT:** **OPEN. The counter first, the behaviour after.** `190` §3.

## U-23 — THE GUN AND THE HAND PASS THROUGH WALLS
- **WHAT:** `[REPORTED]` (`202`) *"my hand/gun and aimer going through geometry."* The viewmodel has no collision, so the barrel enters walls, crates and doorframes.
- **EVIDENCE:** normal for a viewmodel — GoldenEye draws the gun in camera space with no world test, and every flat-screen shooter of the era does the same. **In VR it reads much worse**, because you can physically put your hand into a wall and watch it happen.
- **COST:** SLICE for the cheap version (a short ray from the shoulder to the muzzle; on a hit, pull the gun back along its own axis to the contact point — "weapon pushback", the standard VR treatment). **PROJECT** for anything articulated.
- **BLOCKERS:** needs a world raycast reachable from the host or the patch. **NOT YET GREPPED — `168` §5's check is owed before this is costed.** GoldenEye's own trace lives inside `chraiDefaultWeaponFireHandler` (`chrprop.c:908-931`), which `185` `B3` already recorded as **not in `externs.h`** and entangled with damage and explosions.
- **AND IT IS NOT A FRAME BUG.** Recorded here so it is not re-diagnosed as one during the seam work: it was `[REPORTED]` in the same breath as a frame fault and is unrelated to it.
- **VERDICT:** **OPEN, cosmetic, not on the critical path.** `202`.

## U-24 — A CALIBRATION PHASE, SO THE GAME FITS THE PLAYER INSTEAD OF THE PLAYER FITTING THE GAME
- **WHAT:** Measure the WEARER once — standing eye height, comfortable ready position, full extension, floor — and DERIVE the offsets from it, instead of shipping PD's pistol constants and nudging them per person.
- **WHY, `[REPORTED]`:** *"if other people use this of different sizes, won't it be weird?"* And from the same session: *"the arm length is about one Bond hands length too far"*, *"the arm in the game is about 3 inches higher than my real life arm."* **Those are proportion mismatches being hand-corrected for one body.**
- **EVIDENCE IT IS TRACTABLE:** `[MEASURED]` the runtime space is HEAD-CENTRED (head `y=+0.016`, hand `y=-0.417`), so the hard version of this bug — stacking standing height onto Bond's eye height — **does not exist here.** `176`'s crouch already calibrates ("stand still for the first ~90 frames"), so **the pattern has precedent in this codebase.**
- **COST:** SLICE for eye height + ready position. **PROJECT** if it grows a menu, storage and re-run flow.
- **BLOCKERS: NONE KNOWN.** Host-side; the poses are already in hand.
- ►► **THE RULE IT MUST NOT BREAK (`205` §4): `-WorldUnitsPerMetre` and `-HandUnitsPerMetre` MUST MOVE TOGETHER.** Their ratio is an arm-length multiplier — measured at 2x when they were 50 and 100.
- **THE DOCUMENT IS `205`**, opened deliberately empty and standing. **Append there, not here.**
- **VERDICT:** **OPEN, owner-requested, not on the critical path today.**

---

# REFERENCE — THE LEVEL IDs, FOR ANY FUTURE MOD OR WARP

**`[READ]` `lib\ge\src\bondconstants.h`, `enum LEVELID`, expanded to values.**
**`g_StageNum` and `g_MainStageNum` are BOTH in `patches/externs.h`** (`208` §2),
so any of these can be queued from patch code with one assignment.
**The gaps are real** — the enum is sparse and the numbers are NOT mission order.

| id | name | | id | name | | id | name |
|---|---|---|---|---|---|---|---|
| -1 | `NONE` | | 33 | **`DAM`** | | 45 | `BASEMENT` |
| 0 | `DEFAULT` | | 34 | **`FACILITY`** | | 46 | `STACK` |
| 9 | `BUNKER1` | | 35 | **`RUNWAY`** | | 47 | `LUE` |
| 20 | `SILO` | | 36 | **`SURFACE`** | | 48 | `LIBRARY` |
| 22 | `STATUE` | | 37 | **`JUNGLE`** | | 49 | `RIT` |
| 23 | `CONTROL` | | 38 | **`TEMPLE`** | | 50 | `CAVES` |
| 24 | `ARCHIVES` | | 39 | **`CAVERNS`** | | 51 | `EAR` |
| 25 | `TRAIN` | | 40 | **`CITADEL`** | | 52 | `LEE` |
| 26 | `FRIGATE` | | 41 | **`CRADLE`** | | 53 | `LIP` |
| 27 | `BUNKER2` | | 42 | `SHO` | | 54 | `CUBA` |
| 28 | `AZTEC` | | 43 | `SURFACE2` | | 55 | `WAX` |
| 29 | `STREETS` | | 44 | `ELD` | | 56 | `PAM` |
| 30 | `DEPOT` | | | | | 57 | `MAX` |
| 31 | `COMPLEX` | | | | | **90** | **`TITLE`** |
| 32 | `EGYPT` | | | | | | |

**`33` IS THE DAM — the first mission, and the one to warp to for testing.**
**`90` IS THE TITLE SCREEN**, which is what `g_StageNum` reads while the front
end is running (`208` uses it as the "are we at the title yet" test).

> **AND A WARNING FOR WHOEVER USES THIS:** the enum's own comment says
> *"skyID since only used by Sky and does not reflect levelID, rather in past
> SkyID has been confused with Sky[Index]"*. **These values are what
> `g_StageNum` actually holds** — `bossGetStageNum()` returns it directly and
> `bondview2.c` compares it against `LEVELID_CUBA` — **but treat any OTHER table
> indexed by "level" as a separate question until checked.**

## U-25 — HEAD-RELATIVE LOCOMOTION, WITH A SMOOTHED TORSO YAW (and an OFF-HAND option)
- **WHAT:** Walking forward goes where the player is FACING instead of where the game camera happens to point. `[REPORTED]` owner's decision: **"Forward follows your head (offhand control should be an option in the future mod menu or option menu)."**
- **WHY IT IS NOT JUST COMFORT:** `[READ]` `194` — the game camera never receives the head rotation, so today "forward" is the body's stick-driven facing while the wearer looks elsewhere. **And `[REPORTED]` the owner plays in a SWIVEL CHAIR: "my direction may change and that messes up the shot."**
- **THE DESIGN IS PERFECT DARK'S AND IT SHIPPED — `218`.** `[READ]` `bondgun.c:10991`: an exponential chase of a smoothed torso yaw toward the head yaw, `VrArmBodyFollow = 0.02` per tick (~0.8 s at 60 Hz), with shortest-angle wrapping **"so a full 360 physical spin tracks correctly instead of unwinding"** and a hemisphere fix. **Glances do not steer you; sustained turns and chair spins do.**
- **EVIDENCE IT TRANSFERS:** pure quaternion maths, **no PD subsystem is called** — `168`'s rule satisfied outright. And PD hit our exact bug class: `bondgun.c:912` counter-rotates the arm anchor by *"the head yaw RELATIVE to the smoothed torso, so it is body-stable without coming unstuck when you physically turn."*
- **COST:** SLICE. **BLOCKERS: NONE** — `speedforwards` / `speedstrafe` / `speedsideways` are reachable at `structs.h:2110-2112`, and `MoveBond` is in `externs.h:131`.
- ►► **THE TRAP:** GoldenEye's stick is **turn + move, NOT a 2D vector** — `stick_x` turns and `stick_y` walks. So this is a DECOMPOSITION into forward+strafe, not a rotation of a movement vector.
- **AND PD's `0.02` IS A STARTING VALUE, NOT A LAW:** tuned at their tick rate and for the ARM, not for locomotion. **Knob from day one** (`155`: a PD constant that did not transfer).
- **OFF-HAND FORWARD:** owner wants it as an OPTION, for the settings menu `U-04` already plans.
- **VERDICT:** **OPEN, owner-requested, DESIGNED.** Measurement first (`218` §5): re-run `216`'s five groups on the `217` build and find out whether the aim residual rotates with PHYSICAL facing.

# APPEND BELOW THIS LINE. NEXT ID: **U-26**.
