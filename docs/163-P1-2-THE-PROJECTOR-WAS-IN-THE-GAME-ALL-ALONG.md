# 163 — P1-2 / B1. THE PROJECTOR WAS IN THE GAME ALL ALONG, AND THE TWO FRAMES ALREADY MATCH.

**2026-08-25. P1-1 and P1-2 and P1-3 are BUILT IN ONE SLICE. P1-4(a) fixed.
P1-4(b) is FALSIFIED for GoldenEye. UNBUILT, UNWORN.**

> ## THE FINDING, IN ONE SENTENCE
>
> **`160` §2/B1 says PD can project because `camGetWorldToScreenMtxf()` is in
> scope and we cannot because it is not — but GoldenEye's projector NEEDS NO
> MATRIX ARGUMENT, is already called from `gunfire.c:4818`, and its camera frame
> is OpenXR's head frame EXACTLY. There was nothing to estimate and nothing to
> convert.**

---

## 1. P1-1 — THE PROJECTOR. THE DELIVERABLE PARAGRAPH.

**`transform3Dto2DCoords(coord3d *in, coord2d *out)` — `bondview.c:722`, declared
`bondview.h:2825`.**

```c
inv_z  = 1.0f / in->z;
out->y = (in->y * inv_z * c_recipscaley) + (c_screentop  + c_halfheight);
out->x = (c_screenleft + c_halfwidth)  - (in->x * inv_z * c_recipscalex);
```

**ARGUMENT FRAME: the camera/view frame, in game units. NOT world.**
**RETURNS: PIXELS,** already including `c_screenleft` / `c_screentop`.

**IT TAKES NO CAMERA MATRIX.** Everything it needs is live state on
`g_CurrentPlayer` — `c_recipscalex/y`, `c_halfwidth/halfheight`,
`c_screenleft/top`. **REACHABLE FROM PATCH CODE: yes, unambiguously —
`gunfire.c:4818` already calls it, and so do `chrprop.c` (7 sites) and
`front.c` (2).**

**AND IT CARRIES THE GAME'S OWN FOV.** `currentPlayerSetCameraScale`
(`bondview.c:649`) sets `c_scaley = tan(fovy/2) / c_halfheight`, so
`c_recipscaley = c_halfheight / tan(fovy/2)`. **The projection is therefore
correct at every FOV INCLUDING under the widescreen hack. `159` §6's FOV read is
NO LONGER OWED FOR AIMING** (it may still matter for stereo).

## 2. ►►►► THE FRAMES ALREADY MATCH. THIS IS THE PART THAT DELETES THE KNOBS. ◄◄◄◄

Invert `transformAndNormalizeByLength2Dto3D` (`bondview.c:698`), which is
`transform3Dto2DCoords`'s exact inverse:

```
y = (c_halfheight - (in->y - c_screentop)) * c_scaley
x = ((in->x - c_screenleft) - c_halfwidth) * c_scalex
z = -1
```

A point to the RIGHT of screen centre gives `x > 0`. A point ABOVE centre gives
`y > 0`. Forward is `z = -1`.

> ## **GOLDENEYE'S CAMERA FRAME IS `+x` RIGHT, `+y` UP, `-z` FORWARD.**
> ## **THAT IS OPENXR'S HEAD FRAME, AXIS FOR AXIS.**

`g_geVrAimFwdHead` (`rt64_render_context.cpp:1333`) is already in it.
**THE RAY CROSSES THE BOUNDARY UNMODIFIED. THERE IS NO SIGN TO GUESS** — and
`48` records that this project has been wrong about a sign **five times.**

## 3. WHAT WAS ACTUALLY WRONG WITH A1c

`aim_screen_ndc` computes `lateral / forward * GE_VR_AIM_GAIN` — **a perspective
divide with the projection matrix replaced by ONE SCALAR.** That is why A1c is
"mis-aimed, UNTUNED": **there is nothing to tune it TO.** A gain that is right at
screen centre is wrong at the edge; a gain right at one FOV is wrong at another.
**It is not a tuning problem, it is a missing projection.**

## 4. THE SLICE AS BUILT

**HOST** — `ge_vr::aim_fwd_head(float *out3, int hand)`, new. Publishes the UNIT
forward ray in the head frame and **stops there**. No projection, no knobs.
`GE_VR_AIM_BASIS` still selects the source so the old bases stay comparable.
New export `recomp_ge_vr_aim_fwd_head` @ `0x8F00013C`,
`recomp_ge_vr_aim_estimate` @ `0x8F000140`.

**PATCH** — `ge_vr_aim.c`, inside `caclulate_gun_crosshair_position_rotation`:

1. `ray = fwd * 1000` (any positive length; the divide cancels it).
2. **REFUSE if `fwd.z >= -0.05`.** `transform3Dto2DCoords` divides by `in->z`
   with **NO zero guard** — its sibling `transform3DtoDWithZScaling` has one,
   this one does not. Edge-on or behind, the stick keeps the frame (`48`).
3. `transform3Dto2DCoords(&ray, &px)` → pixels.
4. Pixels → the integrator pre-load. `c_halfwidth` **IS** `c_screenwidth * 0.5f`
   (`bondview.c:629`), so the two functions share a centre and the inversion is
   exact:
   `nx = (px.x - c_screenleft - w/2) / (w/2)`, then `crosshair_x_pos = nx / (1 - guncrossdamp)`.
5. `±2` clamp carried over from `162` P0-3(b).

**WHAT DIES: `GE_VR_AIM_GAIN`, `GE_VR_AIM_SIGN_X`, `GE_VR_AIM_SIGN_Y`,
`GE_VR_AIM_FWD_AXIS`, `GE_VR_AIM_FWD_NEG`. Five knobs. ZERO free parameters
remain.** They are left DEFINED but UNREAD on this path, behind
`-AimEstimate`, **so both paths can be compared out of ONE build** — `48` rule 5
is one behaviour change per build, and an A/B needing two builds is how this
project spent three confounded launches. **`161` asks for them deleted; that is a
separate commit once this is worn.**

## 5. P1-3 / B2 IS IN THE SAME SLICE, AND THE ORDERING IS A TRAP

`gun_azimuth_angle` / `gun_azimuth_turning` build `field_FFC`, which is what the
**GUN MODEL** points along (`→ transformAndNormalizeByLength2Dto3D →
sub_GAME_7F067AB4 → hands[].field_A38/A3C/A40`). Until now that pair saw the
STICK and only the stick.

> **THE TRAP, AND IT WAS WRITTEN WRONG FIRST: the natural place to write the pair
> is next to the crosshair pre-load — but that point is ABOVE the `gun_azimuth`
> integrator loop, which would overwrite it the SAME FRAME.** The result would be
> a crosshair that tracks the hand and a gun that does not — **and that reads
> exactly like "the gun lags", which would have been mis-diagnosed as smoothing.**
> The value is stashed and applied AFTER the loop.

**AND IT TAKES A DIFFERENT DAMP.** This pair scales by `gunaimdamp`, the
crosshair by `guncrossdamp`. Using the wrong one puts the gun and the crosshair a
constant factor apart.

## 6. P1-4(a) — THE LIVE BUG, FIXED

`muzzle_origin` extended along `g_geVrLastGunFwd` — **basis 0, R's third row,
ALREADY FALSIFIED by `158` §3** — while the aim used basis 2. **It read as working
only because `GE_VR_MUZZLE_EXT` defaults to 0: at ext 0 the term vanishes and the
axis is never exercised.** The first `-MuzzleExt 20` run would have walked the
origin SIDEWAYS and been blamed on the grip offset. **`GE_VR_AIM_BASIS` now
selects for BOTH, so they cannot drift apart again.**

## 7. ►►►► RETRACTED 2026-08-25 BY `171` §3 — THE NODE EXISTS. ◄◄◄◄

> **THIS SECTION'S CONCLUSION IS WRONG. `gunfire.c:633` reads
> `mdlhdr->Switches[3]->Data` as the per-weapon muzzle position in the gun
> model's frame — PD's `MODELPART_GUN_MUZZLEPOS` under a different name, and all
> four symbols it needs ARE patch-reachable.**
>
> **THE ERROR WAS THE SEARCH, NOT THE READING: grepping `MODELPART` looked for
> PERFECT DARK'S IDENTIFIER rather than for the MECHANISM.** Zero occurrences was
> true and meant nothing. **See `171` §3 and `169` U-18.** The section is left
> below unaltered because `108`.

## 7 (AS WRITTEN, NOW RETRACTED). P1-4(b) IS FALSIFIED. GOLDENEYE HAS NO MUZZLE MODEL PART.

`161` P1-4(b) says to search `structs.h`/`externs.h` for `MUZZLE` and expect PD's
`MODELPART_GUN_MUZZLEPOS`. **Searched the whole game tree:**

- **`MODELPART` — ZERO occurrences anywhere.**
- **`MUZZLE` — exactly ONE datum: `f32 MuzzleFlashExtension`, `gun.h:18`,**
  consumed at **exactly one site, `gunfire.c:739`.**

**PD's per-weapon muzzle node DOES NOT TRANSFER. `-MuzzleExt` CANNOT be deleted.**
This is the **second** PD constant to fail transfer after `155`'s 1.5708 rad.

**BUT PER-WEAPON MUZZLES ARE STILL FREE, BY A DIFFERENT ROUTE — AND THIS IS THE
NEXT CHEAP WIN:** `MuzzleFlashExtension` **is** the per-weapon barrel length the
game already ships, and `6D-02` already measured it at **`100`, flat across 97
samples**. It sits at **offset 0** of the `GeVrWeaponStatsAim` struct
`ge_vr_aim.c` already declares. **So `GE_VR_MUZZLE_EXT` should DEFAULT to the
weapon's own `MuzzleFlashExtension` instead of 0.** Deliberately NOT in this
build — `48` rule 5.

**AND THE GAME ALREADY COMPUTES A MUZZLE POINT.** `gunfire.c:753-764` applies
`flashext` to `gunmtx` and writes `hand->field_B58` (world, via
`currentPlayerGetViewToWorldMtxf()`) and `hand->field_B64 = -flashmtx.m[3][2]`.
**Pre-transform, `flashmtx.m[3][*]` is the muzzle in exactly the camera frame
`bullet_path_from_screen_center`'s `arg0` wants.** It only runs when
`flashdata != NULL`, so it is not a per-frame source — **but it is the game's own
answer to "where is the muzzle" and it should be read before anything is
estimated again.** Recorded for P1-6 / `6D-06`.

## 8. GATES, PRE-REGISTERED

- **G-163-1** — `-NoXr` with `-AimFromHand` UNSET: identical to today. By
  construction (the host gate returns at the guard), but it is the discipline.
- **G-163-2** — point the gun at a wall corner. **The crosshair lands ON the
  corner at 1 m AND at 20 m.** Far-only agreement is the **muzzle-parallax**
  signature (P1-6), **NOT a projection failure** — do not tune it away.
- **G-163-3** — **no knob is touched to achieve G-163-2.** If one is needed, the
  frames do not match after all and §2 is wrong.
- **G-163-4 (P1-3)** — the **DRAWN GUN** sweeps with the crosshair. Today it
  cannot, by construction.
- **G-163-5** — `-AimEstimate` reproduces the old behaviour out of the same
  build, so the two paths are comparable without a second launch.

## 9. TWO BUILD ERRORS, RECORDED BECAUSE BOTH WERE AVOIDABLE

**(1) `transform3Dto2DCoords` was UNDECLARED in patch code.** P1-1 confirmed it is
declared in `bondview.h` and called from `gunfire.c:4818` — **but `bondview.h` is
not reachable through `patches.h`.** "Callable from game code" and "callable from
patch code" are different questions and P1-1's deliverable conflated them.
Declared in `ge_vr_aim.c` the same way that file already declares
`get_ptr_item_statistics` and friends, **prototype copied verbatim** — a
mismatched one would not fail to link, it would misread the arguments (`115`).

**(2) A comment terminator left mid-block.** Removing the mis-ordered P1-3 write
took the code but left its closing `*/`, so five lines of prose parsed as C
(`undeclared identifier 'AND'`). **Check `/*` and `*/` counts match after any
edit that deletes code out of a commented block.**

## 10. AND THE LOG COMMAND IN THIS PROJECT'S DOCS HAS NEVER WORKED

`161` P0-2, `HANDOVER.md` and `00-START-HERE.md` all recorded:

```powershell
Select-String .\gevr.log "AIM"      # WRONG - never worked
```

`Select-String`'s first positional parameter is **`-Pattern`, not `-Path`**, so
this passes `.\gevr.log` as a regex and fails on the `\g` escape. Corrected in
all three files to:

```powershell
Select-String -Path .\gevr.log -Pattern "AIM" | Select-Object -Last 6
```

## 11. STILL UNBUILT AND UNWORN

**None of this has been compiled.** `162` §4's correction is the reason to read
the AIM line before believing anything: **`state=` must now say `APPLIED`.**
