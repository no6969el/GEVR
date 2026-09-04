# 83 — THE SEAM AND THE HOOK. Where the hand transform actually belongs.

**2026-08-23, ~17:45. The conclusion of the Perfect Dark read (`82`), written so
the next session starts by TYPING rather than by searching.**

**This is the single most useful thing this session produced about the hand, and
it is not code — it is knowing where the code goes.**

---

## THE SEAM — the engine's own hand override

```
GoldenEye  hand->field_92C   ==  Perfect Dark  hand->useposrot
GoldenEye  hand->field_8EC   ==  Perfect Dark  hand->posrotmtx
```

**Proven by struct alignment** (`82`), and confirmed by GoldenEye's own code:
`gun.c:609-611` sets `field_92C = 1` and writes a rotation and a position into
`field_8EC` for the debug keyframe path. **Perfect Dark's VR port writes exactly
this pair.**

**The reader, `gunfire.c:548`:**

```c
if (hand->field_92C != 0) {
    gunofs.x += hand->field_8EC.m[3][0];      /* ... y, z */
    matrix_4x4_multiply_homogeneous_in_place(&hand->field_8EC, &rotmtx);
    rotmtx.m[3][0] = rotmtx.m[3][1] = rotmtx.m[3][2] = 0.0f;
}
```

**Note the semantics, because they are not a replacement:**

- **Translation is ADDED to `gunofs`** — which already carries the sway, the
  per-item offsets and the recoil. So writing an absolute position needs the
  delta from what the game computed, not the position itself.
- **Rotation is MULTIPLIED into `rotmtx`** as the OUTER transform, so ours
  dominates but the sway is still underneath.
- **`gunfire.c:2704` clears `field_92C` EVERY TICK**, so it must be written
  every frame from something that runs inside the tick.

## THE HOOK — and this is the part that took the searching

**The write must happen after the clear (`gunfire.c:2704`, in
`gunTickHandState`) and before the read (`gunfire.c:548`, in the placement).**
Everything in that window is either enormous or conditional — except one
function:

```c
/* gun.c:1230 - TEN LINES, a leaf, called at gunfire.c:464 and :468,
 * inside the placement, BEFORE the read at :548, every frame, per hand. */
f32 gunSetHorizontalOffset(GUNHAND hand)
{
    if (hand == GUNRIGHT) return  get_ptr_item_statistics(get_item_in_hand_or_watch_menu(GUNRIGHT))->PosX;
    else                  return -get_ptr_item_statistics(get_item_in_hand_or_watch_menu(GUNLEFT ))->PosX;
}
```

**`RECOMP_PATCH` it, do the VR write, then return the original value.**

**Why not the others, so nobody re-walks this:**

| Candidate | Why not |
|---|---|
| `gunUpdateAndFire` (contains the read) | Hundreds of lines. `78` already rejected it |
| `gunTickHandState` (contains the clear) | `gunfire.c:2518-4215`, ~1700 lines |
| `used_to_load_1st_person_model_on_demand` | Right position in the frame, but its body needs `texInitPool`, `load_object_fill_header`, `get_ptr_item_text_call_line`, `D_80032464` — a symbol chase |
| `lvlGetControlsLockedFlag` | A one-liner, but called CONDITIONALLY inside branches. An unreliable hook is worse than none |
| `Gun_hand_without_item` | `gunfire.c:577` — **after** the read |
| Our current `bondviewTransformManyPosToViewMatrix` | RENDER time, after everything. Writing `field_92C` there is wiped by the next tick's clear before it is ever read |

## WHAT IS STILL OWED BEFORE IT COMPILES

**Bounded, and it is the only thing that stopped this being built on 2026-08-23:**

1. `patches/misc_funcs.h` or `externs.h` — declare `get_ptr_item_statistics` and
   `get_item_in_hand_or_watch_menu`.
2. **`WeaponStats` is not in `patches/structs.h` at all.** Copy the definition,
   or enough of its head to reach `PosX`, from `lib/ge/src/bondtypes.h`.
3. A host import returning the desired matrix. **The host already knows the
   game's own root translation** — our render-time patch reports it every frame
   (`docs\82`'s instrument) — so **the translation DELTA the additive reader
   needs is computable one frame stale**, which is imperceptible.

## AND THE ARCHITECTURE TO PUT THROUGH IT — `82` finding 2

**Do not rebuild the head-relative composition that failed all evening.** Build
the gun's orientation the way Perfect Dark does:

```
controller quaternion  x  body yaw  x  recentre quaternion   ->  GAME-WORLD axes
                                                              ->  applied through the live camera matrix
```

**Ours composed in the head's frame and then multiplied the game's root
rotation, so the engine's turn-sway rotated the gun underneath the hand** —
which is what the wearer reported, twice, before I listened.

**And carry the grip offset** (`82` finding 3): the gun model's origin is not
the grip. `-GunOffX/Y/Z` is built; the per-weapon table is not.

---

## THE MEASUREMENT THAT ENDED THE EVENING, KEPT BECAUSE IT WILL BE NEEDED AGAIN

```
game t0  = (10.9, -20.7, -33.4)     where the game puts the gun
ours     = (23.4,  -6.4, +28.9)     BEHIND the eye - the Z sign was inverted
after    = (14.4,  -7.8, -13.1)     in front, but only 13 units out
```

**Three things that instrument settled in one launch**, after four changes made
on reasoning alone:

1. **-Z is forward** (`gunfire.c:818` reads depth as `-m[3][2]`), and we had the
   sign backwards. **The viewmodel draws with the z-buffer OFF, so a gun behind
   the camera does not vanish — it renders anyway**, which is why it read as
   "really far away" rather than as missing.
2. **The game holds its gun 33 units out and 21 units below eye level.** Ours
   was 13 out and 8 below. **The near plane is around 10 units** (`14`, `16`),
   so at 13 units most of the model falls inside it and is clipped — a gun that
   VANISHES rather than one that is far.
3. **Those are the numbers to aim at.** Any hand placement that does not land
   near `(±11, −21, −33)` at rest is wrong before anyone puts the headset on.
