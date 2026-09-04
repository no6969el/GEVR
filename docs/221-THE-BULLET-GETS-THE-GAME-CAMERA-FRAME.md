# 221 — THE BULLET GETS THE GAME CAMERA'S FRAME. THREE CANDIDATES, ONE RUN PICKS.

**2026-08-26. Tiers per `182`. BUILT, UNRUN.**

---

## §1 — WHAT IT DOES

**`[MEASURED]` `220`: we pass `R_head^-1 * gun_world`, and the game applies its
OWN camera->world matrix. The head term CANCELS any rotation the head and hand
share — so turning the body 176 degrees moved the bullet 17.**

**WHAT IS WANTED:** `dir` such that `ViewToWorld * dir` is the gun's true world
forward. So `dir = ViewToWorld^-1 * fwdPlay`.

**AND `ViewToWorld` IS RECOVERABLE FROM TWO MATRICES THE GAME KEEPS:**

```
[READ] gunfire.c:574   throw_item_pos_related = ViewToWorld * gunmtx_camspace
       therefore       ViewToWorld            = throw * gunmtx_camspace^-1
```

**Both reachable** — `217` named `gunmtx_camspace` in `structs.h` at the offset
it always occupied. **NO UNREACHABLE SYMBOL, no new game function.**

**AND `gunmtx_camspace` CARRIES NO SCALE TO UNDO:** `[READ]` it is copied at
`gunfire.c:572`, BEFORE the `0.1` basis scale at `:643`. **A rotation, so the
inverse is the transpose.**

---

## §2 — ►► THE COMPOSITION ORDER IS NOT GUESSED. THREE CANDIDATES SHIP. ◄◄

**THIS PROJECT HAS LOST FOUR BUILDS TO GUESSING A MATRIX CONVENTION** — `200`,
`203`, `214` and `217`. **So both orders are computed and `-BulletFrame` picks:**

| `-BulletFrame` | form |
|---|---|
| **0** | the head-relative ray — **today, and `220`'s measured fault** |
| **1** | `R = throw_rot * camspace_rot^T` — **DEFAULT** |
| **2** | `R = camspace_rot^T * throw_rot` |

**`48` / `158` §2: publish every candidate and let ONE run decide.** That is what
closed `200` and `203`; every build that guessed instead had to be corrected by
the next measurement.

**AND THE CROSSHAIR IS DELIBERATELY UNTOUCHED.** `220` §3: it is drawn on a
screen seen through the head, so **head-relative is CORRECT for it.** The host
now publishes both frames from one call — `[0..2]` head-relative for the sight,
`[3..5]` raw play space for the bullet. **Same symbol, wider payload, so no new
address and `136`'s double build does not apply to it.**

**ONE NEW SYMBOL** (`recomp_ge_vr_bullet_frame`, `0x8F000180`) **-> BUILD TWICE.**

---

## §3 — `G-220`, AND IT IS THE THING THAT HAS NEVER HAPPENED

> ## **TURN YOUR BODY. YOUR AIM MUST TURN WITH YOU.**

**`[MEASURED]` baseline to beat: 176 degrees of physical rotation moved the
bullet 17 degrees.**

- **wrong in a MIRRORED or rotated way -> `-BulletFrame 2`.** That is the
  composition order, not a failure, and it costs a launch rather than a build.
- **turning still does nothing -> `-BulletFrame 0` is today's behaviour**, and
  the recovery of `ViewToWorld` is wrong rather than its application.
- **`219`'s `IMPACTNEW` pairing is in this build**, so the gun-vs-bullet table is
  computable from the same run without a second pass.

---

## §4 — WHAT IS OWED

1. **BUILD TWICE. `G-220`.** Nine shots as `219` §4: three forward, three
   up-right, three after physically turning 180.
2. **IF IT PASSES: the crosshair slice** — `220` §4's three owner decisions.
3. **IF IT FAILS: `-BulletFrame 2`, then `0`.** Three launches, no rebuild.

**NOTHING STAGED. THE COMMIT IS THE OWNER'S.**
