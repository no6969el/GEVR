# 160 — THE FULL PERFECT DARK SCAN. WHY IT IS NOT COPY-PASTE, AND THE FIVE THINGS THAT ARE.

**2026-08-25. Source is now LOCAL and stays local:**
`C:\Users\pdbar\Desktop\GoldenEyeVR\local-only\prior-art\perfect_dark_VR`
**branch `port`, commit `67ea20c86986c6bc85687f26a27418b266af309c` (2026-08-19),
MIT.** Same commit `102` was read at, so every line number in `102` still
resolves. **It was NOT on disk before today** — `102` and `82` were written from
a clone that no longer exists. **Never re-clone to read it: it is checked out.**

**ATTRIBUTION IS OWED** on anything derived from this, in `PUBLISH-MANIFEST.md`
**and** at the point of use. `00`'s licence table: MIT may influence anywhere.

> **THE OWNER'S QUESTION, VERBATIM:** *"Perfect dark should work the same as
> goldeneye so I am unsure why this isn't just copy paste to get it to work."*
>
> ## THE ANSWER IS ONE SENTENCE, AND IT IS NOT ABOUT THE GAMES.
>
> **They edit `bgunSwivel` from inside the game, where `camGetWorldToScreenMtxf()`
> is in scope. We compute our aim in `rt64_render_context.cpp`, where it is
> not — so we did not project a ray, we ESTIMATED one with a gain knob.**
> Everything below follows from that single difference.

---

## §1 — WHAT PERFECT DARK ACTUALLY DOES, READ AT SOURCE

`bondgun.c:8306-8489`, `bgunSwivel`. **The four arguments `screenx, screeny,
crossdamp, aimdamp` are seeded into `x[]`/`y[]` at `:8322-8325` and then
OVERWRITTEN for any hand that is in use.** The stock stick-driven swivel survives
only when the hand is unavailable. **That is the whole "break the lock":
they did not unclamp the stick path, they REPLACED it.**

The replacement, in order (`:8347-8489`):

```c
struct coord vrdir = {0,0,-1};
mtx4RotateVecInPlace(hand->useposrot ? &hand->posrotmtx : &hand->posmtx, &vrdir);
vrdir.y = -vrdir.y;                       /* then normalise */
vr_rotate_vector_by_quaternion(&vrdir, &vr_HMD_rot_Q);
vr_rotate_vector_by_quaternion(&vrdir, &vr_joy_rot_Q);   /* ORDER IS LOAD-BEARING */

sp94 = hand->muzzlepos + vrdir * 100000.0f;              /* .y uses MINUS */
        /* ...or hand->dotpos, when the laser has a real hit */

mtx4TransformVecInPlace(camGetWorldToScreenMtxf(), &sp94);   /* <<<< THE POINT */
cam0f0b4d04(&sp94, sp8c);
x = 2*sp8c[0]/viGetViewWidth()  - 1;
y = 2*sp8c[1]/viGetViewHeight() - 1;
```

**A WORLD POINT, PROJECTED BY THE GAME'S OWN CAMERA MATRIX, CONVERTED TO NDC.
NO GAIN. NO SIGN KNOBS. NO FOV ASSUMPTION. NO TUNING AT ALL.**

Then, and only then, the integrator pre-loads and the writes:

```c
player->crosspossum[0..1] = x / (1 - crossdamp);   /* BOTH sums */
player->crosssum2[0..1]   = x / (1 - aimdamp);     /* BOTH sums */
player->crosspos[0..1]  = ndc -> pixels;  CLAMPED to [3, w-4]   /* DRAWN */
player->crosspos2[0..1] = ndc -> pixels;  NOT CLAMPED           /* THE BULLET */
cam0f0b4c3c(player->crosspos2, &aimpos, 1000);  bgunSetAimPos(&aimpos);
```

---

## §2 — THE FIVE THINGS TO BORROW, RANKED BY WHAT THEY BUY

### **B1 — PROJECT THE RAY THROUGH THE GAME'S CAMERA MATRIX. THIS IS THE WHOLE FIX.**

**What we do today** (`rt64_render_context.cpp:1128-1177`, `ge_vr::aim_screen_ndc`):

```c
out2[0] = (comp[ilat0] / fwd) * GE_VR_AIM_GAIN * GE_VR_AIM_SIGN_X;
out2[1] = (comp[ilat1] / fwd) * GE_VR_AIM_GAIN * GE_VR_AIM_SIGN_Y;
```

**That is a perspective divide with the projection matrix replaced by one
scalar.** It is why `A1c` is *"still mis-aimed, UNTUNED"*: there is nothing to
tune it to. **`GE_VR_AIM_GAIN` is standing in for `1/tan(fov/2)`, and it cannot
be right on both axes at once** — GE scales X by `screen_width` and Y by
`screen_height`, so a non-square aspect needs two different gains. **One knob for
two axes is a defect, not a tuning problem.**

> **PD's version has ZERO free parameters and is exact at every distance and
> every FOV, including under the widescreen hack that `159` §6 flags as
> unmeasured. It also makes the whole `-AimGain` / `-AimSignX` / `-AimSignY` /
> `-AimFwdAxis` / `-AimFwdNeg` / `-AimBasis` sweep DISAPPEAR.**

**HOW TO GET IT ON OUR SIDE.** GoldenEye's counterpart of
`camGetWorldToScreenMtxf()` must be reached from patch code, not from
`rt64_render_context.cpp`. **Two candidates already in our tree:**

- `transformAndNormalizeByLength2Dto3D` + `sub_GAME_7F067AB4` — already called at
  the bottom of our patched `caclulate_gun_crosshair_position_rotation`. That is
  the 2D->3D direction; **we need its inverse, the 3D->2D.**
- **`transform3Dto2DCoords`** — named in `153` §8 as what `chrprop.c:2322` uses to
  project target bounds. **That is almost certainly GE's `cam0f0b4d04` and it is
  the function this slice needs.** A read, not a launch.

**The shape of the fix:** the host stops returning NDC and starts returning
**the gun's forward direction and the muzzle position, in the game's world
frame**; the patch builds `muzzle + fwd*100000`, calls GE's 3D->2D, and divides
by screen width/height. **The projection stays where the projection lives.**

### **B2 — WRITE BOTH INTEGRATORS. WE ONLY WRITE ONE.**

`ge_vr_aim.c` writes `crosshair_x_pos` / `crosshair_y_pos` and **nothing else.**
`gun_azimuth_angle` / `gun_azimuth_turning` are still driven by `turn_x` from
the stick, and `field_FFC` — the gun model's pointing, and the input to
`sub_GAME_7F067AB4` — is derived from them.

> **PD PRE-LOADS `crosspossum` AND `crosssum2` FROM THE SAME `x`, TWO LINES
> APART.** We pre-load one. **So even when A1c starts applying, the gun's
> pointing and the bullet will disagree by construction**, and that will read as
> exactly the fault the owner is chasing.

**This is a four-line change in a function we already own, and it costs nothing.**
It should land in the same build as B1, because a half-driven pair is not a
state worth wearing.

### **B3 — THE MUZZLE COMES OUT OF THE GUN MODEL, NOT OUT OF A KNOB.**

`bondgun.c:11507-11530`:

```c
node = modelGetPart(modeldef, MODELPART_GUN_MUZZLEPOS);
sp6c = modelFindNodeMtxIndex(node, 0);
hand->muzzlepos = mtx[sp6c].m[3][0..2];     /* and mtx4Copy -> hand->muzzlemat */
```

**The gun models carry a NAMED MUZZLE NODE and PD simply reads it.** Grenades and
mines fall back to `MODELPART_GUN_HOLDPOS`; anything with no node falls back to
`hand->posmtx`'s translation. **Three tiers, no tuning, correct per weapon for
free — and it is `86`'s "no per-weapon table until two weapons disagree" solved
without a table at all.**

**Ours** (`muzzle_origin`, `:1188-1205`) is `hand position + R's third row *
GE_VR_MUZZLE_EXT`, three sign knobs on top. **And `158` §3 ALREADY PROVED R's
third row is not the barrel** — `row3=(-0.45,-0.84,0.30)`, dominated by Y.

> ## **THAT IS A LIVE BUG AND IT IS IN A SLICE MARKED DONE.**
> **`aim_screen_ndc` defaults to `GE_VR_AIM_BASIS 2` (`g_geVrAimFwdHead`, the
> derived ray) while `muzzle_origin` still uses `g_geVrLastGunFwd` (basis 0, the
> falsified third row).** The two halves of the shot use two different forwards.
> A1b reads as working only because `GE_VR_MUZZLE_EXT` defaults to `0`, so the
> wrong axis is multiplied by nothing. **The moment anyone sets `-MuzzleExt` it
> pushes the origin sideways.** `157` G-A1b-3 would have caught it.

**THE READ THIS OWES:** does GoldenEye's model format carry a muzzle part
constant? Search our `structs.h` / `externs.h` for `MUZZLE`, and `90`'s
`muzzleExt=100` — **read across 97 samples in `6D-02` — is a strong hint that the
game already knows where its muzzle is.**

### **B4 — AIM AT THE LASER DOT'S REAL HIT POINT WHEN THERE IS ONE.**

`bondgun.c:8365-8388`. When `hand->dotpos` is fresh (it is written by
`bgun0f0a94d0` from an actual world-space raycast hit, with a `+-100000` sanity
guard at `:16459`), **PD aims at the HIT POINT rather than at `muzzle + dir *
100000`.** When the dot is stale — the value has not changed since last frame —
they fall back to the far point and hide the dot.

> **THIS IS THE EXACT ANSWER TO MUZZLE PARALLAX**, and it is why their crosshair
> sits ON the laser dot instead of near it. The far-point approximation is only
> correct at infinity; up close, a barrel held a foot to the right of the eye
> projects to a visibly different pixel than the thing it is touching.

**It is also `6D-06` / A2, and it turns out to be the cheap half of it**: the
world-space dot is prior art's *aiming input*, not just its decoration.

### **B5 — THE CLAMP SPLIT, CONFIRMED AGAIN AND STILL OWED.**

`102` §1 was right and this scan confirms it verbatim: **`crosspos` clamped,
`crosspos2` not.** Our A1 gate unclamps `crosshair_angle`, which is read by BOTH
the draw and the shot, so an unclamped build lets the HUD crosshair walk off
screen. **`153` §8's plan — keep `crosshair_angle` true, move the `[3, w-4]`
clamp into `gunDrawSight()` — is exactly PD's split and it is still unbuilt.**

---

## §3 — WHAT ELSE THE SCAN FOUND IN OUR OWN CODE

| | Where | What |
|---|---|---|
| **One gain, two axes** | `rt64_render_context.cpp:1170` | `GE_VR_AIM_GAIN` scales X and Y identically. GE scales X by `screen_width` and Y by `screen_height`. **Cannot be correct on both.** Moot once B1 lands; **a real defect until then** |
| **Two different forwards** | `:1141` vs `:1202` | aim uses basis 2, muzzle uses basis 0. §2/B3 |
| **No NDC clamp** | `:1174-1175` | `fwd < 0.05` refuses, but a divisor just above it still throws `ndc=(-8.5,-17.9)` — the recorded "shooting the ground". **Clamp NDC to about `[-2, 2]`** |
| **`AIM_FWD_NEG` defaults to 1** | `:1158` | `-AimFwdNeg 0` is what cleared the refusal. **The default is a trap as shipped** — `00`'s own words |
| **`crosshair_angle` write is above the clamp gate** | `ge_vr_aim.c` | Correct as written. Noted so nobody "tidies" it |

---

## §4 — WHAT TRANSFERS AS A NUMBER, AND WHAT HAS ALREADY FAILED

**`102` §3 is the constants table and it is unchanged by this scan** — grip
offsets and their Ry180 trap, the `{w,-x,y,-z}` basis, the smoothing alphas
(position is NOT smoothed at all), the probe geometry, the crouch fractions, the
`x/(1-damp)` pre-load. **Do not re-derive any of it.**

**THE SCOREBOARD ON PD CONSTANTS SO FAR, AND IT IS THE HONEST ONE:**

| Constant | Result here |
|---|---|
| `{w,-x,y,-z}` basis | **TRANSFERRED** — `-HandAxisX -1 -HandAxisZ -1`, first launch (`155`) |
| Pistol grip offset `(0,16,-4)` | **TRANSFERRED** — `-GunOffY 8 -GunOffZ -2` at half scale (`154`) |
| `x/(1-damp)` pre-load | **TRANSFERRED** — confirmed verbatim in both trees |
| 1.5708 rad X post-rotation | **FALSIFIED** — `-HandRotXDeg 90` failed, `-90` worse, 0 beat both (`155`) |
| World scale (85.0 / 42.5) | **DOES NOT APPLY** — PD stage geometry. Ours is `159`'s 12-25 |

> **Two constants out of the same slice, one right and one wrong. Judge each on
> its own gate.** `155` §3, and it is the rule for everything in `102`.

**NEWLY CONFIRMED AS PORTABLE, HOST-SIDE, NO ENGINE DEPENDENCY:**
**the recoil model** (`vr_input.cpp:897-1160`) — its own comment says *"100% on
OpenXR side, no engine dependency"*. A five-field spring profile per weapon,
integrated at a fixed `dt = 1/90`, applied to the controller pose before it
reaches the game. **That is a drop-in for our host, because our host owns the
same pose.** Not a priority; recorded so it is not re-invented.

**WHAT STILL CANNOT COME ACROSS:** weapon enum labels and the ~60 recoil profiles
(classes transfer, mappings do not); character-height mode (PD is multi-character,
GE is Bond-only); reload-snap and belt-grab model indices; `cd*` call signatures
(**the SEQUENCE transfers, the signatures do not**); Quest/GLES.

---

## §5 — SO, IN ONE LINE EACH

1. **B1 makes the aim correct instead of tuned.** Everything else is smaller.
2. **B2 is four lines and stops the gun and the bullet disagreeing.**
3. **B3 fixes a live axis bug and deletes `-MuzzleExt`.**
4. **B4 makes the crosshair sit on what the barrel touches.**
5. **B5 keeps the HUD honest while the shot goes free.**

**THE PRIORITISED, CHECKABLE TASK LIST IS `161`. START THERE.**
