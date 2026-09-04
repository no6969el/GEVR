# 194 — THE ROOMSCALE READ. YOUR BODY MOVES THE VIEW AND DOES NOT MOVE THE BULLET.

**2026-08-25. `193` §4's read, done before any more aim work, as that document
required. Tiers per `182`. NO RUN, NO BUILD — this is four `[READ]`s.**

---

## §1 — THE QUESTION, RESTATED PRECISELY

`[REPORTED]`: *"if I am on the side off center in VR it shoots off to the side."*
**A dependence on head POSITION, which nothing in `193` §1-§3 accounted for.**
`193` §4 named the read: **does the roomscale head TRANSLATION reach the game's
shooting frame, or only the rendered view?**

---

## §2 — ►►►► THE ANSWER: THE VIEW GETS IT. THE BULLET DOES NOT. ◄◄◄◄

**`[READ] 1 — THE VIEW GETS THE TRANSLATION.** `ge_vr_head_transform`,
`rt64_render_context.cpp`: after the orientation basis is built,

```c
const float tx = view.position[eye][0] * env.worldUnitsPerMetre * env.posSignX;   // ...y, z
m[3][0] = -(tx*m[0][0] + ty*m[1][0] + tz*m[2][0]);                               // ...[3][1], [3][2]
```

**The head's real position, in game units, is written into the eye view matrix.**
Its own comment: *"This single number carries BOTH the head translation and the
eye separation."* **Step sideways and the rendered image is drawn from where you
actually are.**

**`[READ] 2 — THE BULLET'S ORIGIN IS HEAD-RELATIVE, AND DELIBERATELY SO.**
`rt64_render_context.cpp:1853`:

```c
const float dx = (input.aimPosition[1][0] - headOrigin[0]) * ge_vr_hand_pos_sign_x();  // ...y, z
handPos[i] = ((dx*Rhead[i][0]) + (dy*Rhead[i][1]) + (dz*Rhead[i][2])) * env.handUnitsPerMetre;
```

**`hand MINUS head`.** `muzzle_origin` then returns exactly that (`:1694`). **So
the muzzle offset is measured from your head and is INVARIANT to where you stand
— which is correct for what it was built to do** (`157`: put the shot at the gun
rather than the eye).

**`[READ] 3 — AND THE GAME APPLIES IT FROM A CAMERA THAT NEVER MOVED.** Stock
`bullet_path_from_screen_center` writes `arg0 = (0,0,0)`: the origin is an offset
**in the game's own camera frame**, and our slice replaces those three zeroes with
the head-relative hand position. **Nothing in that path adds the roomscale
displacement, because `[READ] 4` says it was never available there:**
`ge_vr_head_transform`'s result is composed onto the game's view matrix **at
render time** — `rt64_projection_processor.cpp:159`, quoted in our own crouch
comment. **It is a post-hoc adjustment to the picture. The engine's camera
position never learns about it.**

### SO THE TWO HALVES ARE ANCHORED IN DIFFERENT PLACES

| | anchored at |
|---|---|
| **what you SEE** | your real head, displaced by however far you have stepped |
| **where the bullet STARTS** | the game's camera + `(hand - head)` — **undisplaced** |

**YOUR ROOMSCALE DISPLACEMENT IS A PURE ERROR TERM IN THE BULLET'S ORIGIN, EQUAL
TO EXACTLY HOW FAR YOU HAVE STEPPED.** Stand in the centre and it is zero — *"the
center shots remain ok"*. Step half a metre to the side and the shot leaves from
half a metre away from where you are looking. **`[INFERRED]`, and it is the only
mechanism found that is switched on by MOVING YOUR BODY rather than by pointing
the gun.**

> **AND IT COMPOUNDS `193` §2 RATHER THAN REPLACING IT.** That measured a muzzle
> that already sits **0.19-0.61 m** from the eye. **This adds however far you have
> walked, in whatever direction, on top.** Two origin errors, one of which the
> wearer controls with his feet — which is why the fault has looked so
> inconsistent from inside the headset.

---

## §3 — THE FIX IS SMALL, AND IT IS THE SAME INVARIANT `25` ALREADY WROTE DOWN

**`25`'s rule: POSITION AND FRUSTUM MUST COME FROM ONE SOURCE.** `174` applied it
to the eye-versus-cyclopean anchor. **This is the same rule again, one level up:
the ray and the picture must be anchored at the same point.**

**THE CHANGE IS ONE ADDITION.** `muzzle_origin` returns the hand relative to the
HEAD; it should return the hand relative to **the point the game thinks the camera
is** — which is the head MINUS the roomscale displacement:

```
origin = (hand - head)            <- today
       + (head - gameCamera)      <- the missing term
```

**AND THE MISSING TERM IS ALREADY COMPUTED, TO THE UNIT.** It is the same
`view.position * worldUnitsPerMetre`, rotated into the head frame, that
`ge_vr_head_transform` writes into `m[3][*]`. **Taking it from that expression
rather than recomputing it is the whole point** — `25`'s failure was two sources
disagreeing, and a second derivation here would reintroduce exactly that.

- **KNOB:** `-NoRoomOrigin` reverts to today.
- **GATE `G-194`: ►► THE VERSION BELOW IS WRONG. USE `195` §2. ◄◄**
  ~~*stand centred, put a shot on a mark; step half a metre to the side WITHOUT
  MOVING THE GUN'S DIRECTION and fire again; the two impacts must agree.*~~
  **A fixed direction fired from an origin translated half a metre LANDS half a
  metre away — that is correct, and this gate would have failed a working fix.**
  **The correct test keeps the MARK fixed and RE-AIMS from off-centre: it must
  still hit, and `-NoRoomOrigin` must miss by roughly your displacement.**
  `195` §2.
- **BLOCKERS: NONE.** Host-side only, no new patch symbols, no game function
  touched. **`168` §5's grep has nothing to fail on.**

> ►► **AND IT MUST LAND BEFORE `B1`, NOT AFTER.** `B1` converges the crosshair
> onto the last impact DISTANCE. **If the bullet's origin is displaced by an
> amount that changes whenever the wearer shifts his weight, `B1` would be
> converging against a moving reference and its gate could not be judged.**
> That is `A1`-before-`A3` again, and the reason is identical.

---

## §4 — WHAT IS OWED, IN ORDER

1. **THIS SLICE** (§3). Host-side, one addition, one knob, `G-194` above.
2. **`B1` / U-06 — THE PARALLAX** (`193` §2). Now second, and judgeable once §3
   lands.
3. **`U-18` — THE PER-WEAPON MUZZLE** (`193` §3). `T2` passed; the MODEL-frame
   conversion `171` §4 named is the remaining work.
4. **`T9` / `-SeamCompose 1`**, its own launch (`192` §2).
5. **`noPose`** (`190` §3), **`U-21`**, **`U-22`** ride whichever build comes next.

> **THE THREE ORIGIN FAULTS, IN ONE LINE, BECAUSE THEY WERE FOUND SEPARATELY AND
> ARE ONE STORY:** the bullet leaves from **the wrong place relative to your head**
> (`193` §2, B1), **from the wrong place for the weapon in your hand** (`193` §3,
> U-18), **and from the wrong place in the room** (this document). **The DIRECTION
> was never the problem** — `193` §1 measured that across 55 shots.

**NOTHING STAGED. THE COMMIT IS THE OWNER'S**, both repos.
