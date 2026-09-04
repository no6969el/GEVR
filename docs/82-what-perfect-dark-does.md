# 82 — WHAT PERFECT DARK'S VR PORT ACTUALLY DOES. Read before writing any more hand code.

**2026-08-23, ~17:30. The repository was cloned and read.** `81` established the
licence (**MIT**, Ryan Dwyer's decomp copyright) and said the VR code might not
be public. **It is.** `port/vr/` — `vr_openxr.cpp`, `vr_input.cpp`,
`vr_settings.cpp`, `vr_hub.cpp` — plus hooks all through `src/game/bondgun.c`,
`bondview.c`, `bondmove.c`, `bondwalk.c`.

**MIT means it may influence ANYWHERE, including `lib/rt64/` and `repo\`.
Attribution travels with anything derived from it** — `PUBLISH-MANIFEST.md` and
the source comment, both.

---

# FINDING 1 — THE ENGINE HAS A NATIVE HAND OVERRIDE, AND WE HAVE IT TOO

**Perfect Dark's VR code does not do matrix surgery on rendered node matrices.
It writes two engine-native fields:**

```c
vrBuildGunRotation(handnum, hand, qf, &hand->posrotmtx);
hand->posrotmtx.m[3][0..2] = hand->posoffset;
hand->useposrot = true;
```

**Those fields exist in GOLDENEYE, under placeholder names.** Proven by aligning
the two `struct hand` definitions backwards from `blendpos[4]`, which is where
both decomps agree on names:

| Perfect Dark (`src/include/types.h`) | GoldenEye (`patches/structs.h`) |
|---|---|
| `Mtxf posrotmtx` (0x6ac, 64 bytes) | **`Mtxf field_8EC`** |
| `bool useposrot` (0x6ec) | **`s32 field_92C`** |
| `damppos`,`damplook`,`dampup`,`damppossum`,`damplooksum`,`dampupsum` — 18 floats | **`field_930` .. `field_974` — 18 fields** |
| `blendpos[4]`, `blendlook[4]`, `blendup[4]`, `curblendpos`, `dampt`, `blendscale`, `blendscale1`, `sideflag` | **identical, same order** |

**The alignment is exact, and GoldenEye's own code already uses the pair the same
way:** `gun.c:609-611` sets `field_92C = 1` and writes a rotation and a position
into `field_8EC` for the debug keyframe path.

**The reader is `gunfire.c:548`:**

```c
if (hand->field_92C != 0) {
    gunofs.x += hand->field_8EC.m[3][0];      /* ... y, z */
    matrix_4x4_multiply_homogeneous_in_place(&hand->field_8EC, &rotmtx);
    rotmtx.m[3][0] = rotmtx.m[3][1] = rotmtx.m[3][2] = 0.0f;
}
```

## What that changes for us, and the catch that stops it being a free win

**It is the SANCTIONED seam** — upstream of the render, inside the placement the
game itself uses — and it is where `76` slice 2 should have gone if we had known.

**Two things stop it being a drop-in:**

1. **GoldenEye composes it ADDITIVELY.** It *adds* the translation to `gunofs`
   and *multiplies* the rotation into `rotmtx`, which already carries the sway.
   **So writing it does not by itself remove the turn-sway** the wearer
   identified. Perfect Dark could replace the placement outright because they
   can edit the game source; **we cannot** — `RECOMP_PATCH` replaces whole
   functions, and `gunUpdateAndFire` is far too large to replace safely (`78`).
2. **`gunfire.c:2704` clears `field_92C` every tick**, so it must be written
   every frame, from something that runs inside the tick.

**Neither is fatal, and both are known now instead of being discovered worn.**

# FINDING 2 — THEIR GUN IS WORLD-LOCKED, NOT VIEW-LOCKED

```c
// Controller basis in GAME-world axes (per hand), produced by vr_gun_pos_rot and
// consumed at render time by bgun0f0a5550 to world-lock the gun ORIENTATION via
// the live camera matrix.
struct coord gVrGunRight[2], gVrGunUp[2], gVrGunFwd[2];
```

**The controller quaternion is composed with the BODY YAW and the RECENTRE
quaternion** (`vr_joy_rot_Q`, `vr_recenter_rot_Q`) into game-world axes, and the
orientation is applied at render through the live camera matrix.

**That is the architecture `79` was missing.** Ours composed in the head's frame
and then multiplied the game's own root rotation, so the engine's turn-sway
rotated the gun underneath the hand — which is exactly what the wearer reported:
*"in this game when you turn left or right it makes the gun turn in the direction
you are turning... I think it's still attached to other parts."*

# FINDING 3 — THE GUN MODEL'S ORIGIN IS NOT THE GRIP

**This is almost certainly `79`'s "really far away".**

```c
switch (weaponnum) {
  case WEAPON_RCP120: case WEAPON_AR34: case WEAPON_SHOTGUN:
      off.x = -4.0f; off.y = 16.0f; off.z = 8.0f;  break;
  case WEAPON_CALLISTO: case WEAPON_ROCKETLAUNCHER:
      off.x = -8.0f; off.y = 14.0f; off.z = -4.0f; break;
  default:
      off.x = 0.0f;  off.y = 16.0f; off.z = -4.0f; break;
}
off.x += VrGunOffX;   /* per-player trim, from their ini */
```

**A per-weapon offset from the tracked controller point to the gun model's
origin, in game units, plus a global per-player trim** — and their own comment
records that the values were re-derived when the frame they are applied in
changed, "so a single global trim serves all weapons and none of them need
individual hand-tuning."

**We put the model's ORIGIN on the hand.** If GoldenEye's gun models are
authored like Perfect Dark's, the visible weapon hangs some 16 units off that
point, which reads as the gun floating away from the hand.

**BUILT THIS SESSION: `-GunOffX/Y/Z`**, applied **in the gun's own oriented
frame** the way theirs is, not in view space. No per-weapon table yet — the trim
first, then a table if weapons disagree.

# ALSO WORTH KNOWING, NOT ACTED ON

| | |
|---|---|
| **Per-weapon Z-roll corrections** | A small `zRollAngle` per weapon class. Ours will need the same |
| **Their settings live in an ini** (`pd-vr.ini`) | Tuning WHILE WORN instead of relaunching per value. That is **O48**, planned in `61` and never built, and this session spent a dozen relaunches proving why it matters |
| **A VR "hub"** — a flat grid environment for the pause menu | The same shape as the quad-layer idea in `MODS-IDEAS`, and the honest answer to our zoomed menus |
| **Gesture support** — throw history, grip/fist detection, two-handed hold, knife | Far beyond us. Evidence the seam they chose is strong enough to build on |

---

## THE HONEST COMPARISON

**They can edit the game source. We can only replace whole functions.** That is
the whole difference, and it is why our transform lives at the last matrix touch
before the f32 -> s32 conversion (`78`) instead of in the placement itself.

**What transfers regardless of that:** the world-locked orientation, the grip
offset, the per-weapon table, the ini, and the knowledge that `field_92C` /
`field_8EC` is the seam the engine itself sanctions.

**What does not transfer:** their code, verbatim, into ours — not for licence
reasons, MIT allows it with attribution, but because the injection mechanism is
different and a copied function would not attach.
