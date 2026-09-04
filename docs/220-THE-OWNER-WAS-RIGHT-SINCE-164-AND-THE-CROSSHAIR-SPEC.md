# 220 — THE OWNER'S "2D PLANE" MODEL WAS RIGHT, AND HE SAID IT IN `164`. PLUS THE CROSSHAIR SPEC.

**2026-08-26. Tiers per `182`. A correction of my own framing, three owner
decisions, and a build plan.**

---

## §1 — HE CORRECTED ME AND HE WAS RIGHT

**`219` §2 claimed the near-zero error in group 3 meant the aim was correct when
the wearer's body aligned with his character. `[REPORTED]` he pushed back:**

> ***"When I turn around, it's the wrong way. So when I shoot straight, it turns
> it around and shoots perfectly straight BEHIND me, the way that I originally
> should have been facing, BECAUSE THE CAMERA NEVER TURNED."***

**`[MEASURED]`, from the raw CONTROLLER quaternion in `SHOTREC` — which is his
physical hand, not the game's belief about it:**

| group | controller yaw | head yaw | bullet yaw |
|---|---|---|---|
| 1 forward | `+14` | `+13` | `-89` |
| 2 up-right | `+87` | `+24` | `-33` |
| 3 turned around | `-162` | `-163` | `-72` |

**HE ROTATED HIS BODY 176 DEGREES AND THE BULLET MOVED 17.** And group 2 is the
completing half: **his HAND moved 73 degrees while his HEAD moved 11, and the
bullet moved 55.**

> **SO THE BULLET FOLLOWS THE HAND *RELATIVE TO THE HEAD*, AND NOTHING ELSE.**
> ```
> dir          = R_head^-1 * gun_world      <- shared head+hand rotation CANCELS
> bullet_world = R_gameCamera * dir         <- and the game camera never turns
> ```
> **Turn your whole body: the relative term is unchanged, nothing happens.
> Move your hand relative to your head: it changes, the bullet moves.**

**AND MY ERROR WAS SPECIFIC: `219`'s table compared the bullet against `gunfwd`,
which is the GAME'S BELIEF about the gun — head-relative in exactly the same
way.** The 1.2 degrees proved the game was SELF-CONSISTENT, not correct.
**I read self-consistency as correctness** — the same mistake `184` §3a recorded
when a log label said `BULLET` and meant `SIGHT`.

---

## §2 — AND THE MODEL HAS BEEN IN THE CORPUS SINCE `164`

`[REPORTED]`, this session:

> ***"the aimer is fixed to a 2D plane at a fixed distance in front of me...
> whenever I move the gun, it's moving the crosshair along that fixed plane. The
> gun doesn't really matter. It's which field does that crosshair fall into
> compared to the direction I'm angling my gun, and THAT'S the angle at which the
> bullet shoots out."***

**`164` RECORDED THE SAME MODEL FROM THE SAME PERSON, IN ITS OWN WORDS:**
*"it seems like it's only hit points as if I was aiming in a 2D plane... it's not
shooting in a straight line from the gun's exit hole."*

**AND THE FUNCTION IS LITERALLY CALLED `bullet_path_from_screen_center`.** Stock
GoldenEye unprojects the crosshair's SCREEN POSITION into a ray from the eye —
a fixed plane at a fixed distance, exactly as described.

> **THE TWO DESCRIPTIONS ARE ONE FACT.** A direction expressed relative to the
> head, planted on a camera frame that never turns, **behaves** precisely like a
> crosshair sliding around a plane pinned in front of Bond. **His version
> explains the feel; §1's explains the arithmetic. HIS IS THE MORE USEFUL ONE
> FOR DECIDING WHAT THE FIX MUST ACHIEVE** — and it was available for fifty-six
> documents.

---

## §3 — ►► THE FIX IS ONE VALUE, NOT TWO. I GOT THAT WRONG TOO. ◄◄

**I told him both the bullet AND the crosshair needed correcting. THEY DO NOT.**

- **THE CROSSHAIR IS DRAWN ON THE SCREEN, AND THE SCREEN IS RENDERED THROUGH THE
  HEAD'S VIEW MATRIX.** Computing its position head-relative is **CORRECT**, and
  `167` already does it against the render's own tangents.
- **THE BULLET NEEDS THE GAME CAMERA'S FRAME**, because `chrprop.c:952` rotates
  it with `currentPlayerGetViewToWorldMtxf()`.

**THEY GENUINELY NEED DIFFERENT FRAMES — WHICH IS EXACTLY WHY THEY AGREE TODAY
WHILE BOTH ARE DETACHED FROM HIS HAND.** Both are head-relative; only the
crosshair is right to be. **Fix the bullet alone and they will agree BECAUSE BOTH
ARE RIGHT**, instead of because both are wrong.

**THE CHANGE:**

```
ViewToWorld = throw_item_pos_related * gunmtx_camspace^-1     // both reachable
dir         = ViewToWorld^T * gun_forward_world               // instead of R_head^-1 * ...
```

**Both matrices are maintained by the game every frame** (`gunfire.c:572`, `:574`)
and `217` named `gunmtx_camspace` in `structs.h` at the offset it always
occupied. **NO UNREACHABLE SYMBOL. The game's own camera matrix, recovered from
two things it keeps itself.**

---

## §4 — THE CROSSHAIR SPEC, OWNER'S DECISIONS

> `[REPORTED]`: ***"When you move your gun away from your vision of the screen,
> the crosshair should disappear."***
> ***"The crosshair is so close. I would prefer that it just goes on the target
> that you're aiming at."***
> ***"and is smaller, much smaller."***

| # | decision | status |
|---|---|---|
| **1** | **NO EDGE PINNING — the crosshair DISAPPEARS off-screen** | reverses stock's `[3, w-4]` clamp and supersedes `169` U-21, whose 16 px inset is no longer wanted |
| **2** | **IT SITS ON THE TARGET** — at the aimed depth, not a fixed plane | this is `B1`/U-06 and `211`'s `P = muzzle + dir * distance`, and **the distance now has a real source: `219`'s `IMPACTNEW`** |
| **3** | **MUCH SMALLER** | `[MEASURED]` `213` §2.1: the glyph is **32x32** (`gunfire.c:6225`) |

**ON (3), THE ROUTE MATTERS:** `172` established `gunDrawSight` is NOT patchable
(`crosshairimage` and `display_image_at_position` are absent from `externs.h`).
**BUT `173`'s per-eye HUD shift ALREADY REACHES THE CROSSHAIR'S RECT** in RT64's
`rt64_framebuffer_renderer.cpp`, in `Type::Rectangle`. **Scaling it there is
reachable — and the 32x32 size is the discriminator that tells the crosshair from
the rest of the HUD**, which must NOT shrink with it.
**`[ASSUMED]` that 32x32 is unique to the sight; what would settle it is one log
of every rect size the HUD submits.**

---

## §5 — WHAT IS OWED

1. **BUILD §3's ONE CHANGE.** Knob `-NoViewToWorld`.
   **GATE `G-220`: TURN YOUR BODY. THE AIM MUST TURN WITH YOU** — the one thing
   that has never happened.
2. **THEN §4's crosshair**, as its own slice: disappear, depth, size.
3. **`211`'s SOLVER IS SUPERSEDED IN PART** — it assumed the direction was
   already correct and only the origin was wrong. **`219`/`220` show the
   direction is wrong too.** Its parallax half survives and belongs with §4.2.

**NOTHING STAGED. THE COMMIT IS THE OWNER'S.**
