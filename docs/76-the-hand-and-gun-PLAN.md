# 76 — PLAN: the hand and the gun in VR. Four slices, in an order that pays each time.

**2026-08-23, ~16:30. Written before any code, per `48` rule 2 and this
project's standing rule: plan, discuss, then execute.**

**Read `38` first — it corrects `37` in three places and it is the substance
behind everything here.** `36` (hip fire already decoupled from the head) and
`61` (controllers bound, aim poses arriving) are the prerequisites, and both are
already confirmed worn.

---

## WHAT THE WEAR SESSION OF 2026-08-23 ADDS TO THIS

**The viewmodel is now the loudest problem in the headset, measured by the only
instrument that matters — a person wearing it:**

> *"It's the gun and the size of the hand and the size of the gun that makes me
> feel like I'm bigger than I am. If I block that out of my vision, I feel like
> I'm the right height."*
>
> *"It's making this hard, because I have to close one eye to not see it — and
> then it removes depth."*

**Two things that follow, and they change the order of work:**

1. **The world scale is settled enough.** With correct recentring the player is
   the same height as the guards at every value tried, and the world reads right
   around **50 u/m** (25 and 35 close, 100 too small). **`16`'s question is
   answered well enough to stop sweeping.**
2. **The gun is oversized at 25, 35, 50 AND 100, and only shrank at 400 when the
   whole world shrank.** An object whose apparent size does not hold its
   proportion to the world across a 16x sweep **is not a world-scale problem.**
   This is `71` O1's second fault, now established by observation.

**And `36` already measured why:** the viewmodel sits at roughly **15-25 cm
apparent** (O8). A gun 20 cm from your face is enormous no matter what the world
does, and no `-UnitsPerMetre` value can move it.

---

## THE DESIGN QUESTION, ANSWERED HONESTLY

**"Can we add a physical moving VR arm, or stick with what we have?"**

**Stick with what we have, and re-parent it.** The reasons are concrete:

| | |
|---|---|
| **The game's models are the right models** | Every weapon, its animations, muzzle flash, shell ejection, reload and weapon-switch already exist and are keyed to the game's own state. Rebuilding that to hold a new asset means reimplementing all of it |
| **We do not need new assets** | Nothing here requires modelling or rigging |
| **The transform is one matrix** | The viewmodel is placed by a matrix per hand. **Replacing the root transform keeps the animation** — the sway, recoil and reload become a local offset on top of the hand pose instead of something to fight |
| **The game already has a hide switch** | `hand_invisible[hand]` and `lock_hand_model[hand]` exist in `gun.c`. **If the fused arm reads wrong when the gun is held by a tracked hand, the arm can be hidden without touching rendering** |

**A full IK arm — shoulder, elbow, wrist from one tracked point — is a real
project on its own and it is the thing most likely to look worse than nothing.**
Most VR shooters show **gun only, no arm**, precisely because a wrong arm is more
distracting than an absent one. **We already have the switch to test that in
either direction, so it becomes a knob rather than a decision.**

---

## THE CONSTRAINT NOBODY CAN DESIGN AROUND — read this before choosing anything

**`38` correction 3: the gun's aim is HARD CLAMPED to the game's viewport.**

```c
if (crosshair_angle.f[0] < 3.0f)          crosshair_angle.f[0] = 3.0f;
else if (screen_width - 4.0f < ...)       crosshair_angle.f[0] = screen_width - 4.0f;
```

**Past roughly the original FOV's half-angle — on the order of +/-30 degrees off
body centre — the aim pixel simply stops moving.** You can point your hand
further. The bullet will not go there.

**So "point anywhere and shoot there" is not available**, and pretending
otherwise produces the worst possible feel: a gun that follows your hand until it
silently doesn't. **What happens at the limit is a design choice that must be
made deliberately.** Three options, none chosen:

| Option | Feels like | Cost |
|---|---|---|
| **Gun lags at the clamp** | The gun stops following your hand at the edge | Free. Honest, but reads as the weapon fighting you |
| **Body auto-turns to follow** | You push the aim into the edge and the body rotates to keep up | Small. **Closest to natural**, and it is how many VR shooters handle snap-free turning. Risk: unrequested camera motion is a comfort hazard |
| **Indicate the limit** | A visual cue at the edge of the aim cone | Small. Honest and teachable, but adds VR-only UI |

**Recommendation: gun lags at the clamp for slice 3, then try body auto-turn as a
knob in slice 4.** Ship the honest one first, so the tuning question is answered
by wearing rather than by argument.

---

# THE SLICES

Each one is independently wearable and independently valuable. **Do not batch
them** — `48` rule 5: one behaviour change at a time.

## SLICE 1 — PUSH THE VIEWMODEL OUT AND SIZE IT. No tracking yet.

**The smallest change that fixes the thing that is actively hurting.**

Give the viewmodel's placement a distance and a scale, both knob-driven:

```
GE_VR_VIEWMODEL_DISTANCE   where the gun sits, in game units
GE_VR_VIEWMODEL_SCALE      its size
```

**Gates, written first:**

| Gate | What would a working build have to do differently to fail? |
|---|---|
| The gun reads as held at arm's length, not at your nose | A build that leaves the transform alone cannot pass; the apparent distance is the whole change |
| **You can look at the world with BOTH eyes open** | This is the user's own falsifier and it is the real one |
| The world's apparent scale is UNCHANGED | If the world moves too, the change landed in the wrong matrix |
| `-NoXr` is untouched | The viewmodel is drawn on every path. **Gate it on VR being enabled** |

**Risk, and it is the one to watch:** the viewmodel may be positioned in a space
where "distance" is not what it looks like. **Read where the matrix is built
before changing it** — `gun.c` `hands[handnum]`, and the draw path in
`bondview2.c`.

## SLICE 2 — THE GUN FOLLOWS THE HAND, VISUALLY ONLY

Drive the viewmodel's root transform from the right controller's `aim` pose,
which `61` already logs every frame and **nothing consumes**.

**Shots still come from the crosshair.** They will not agree with the gun yet,
and that is deliberate: **it isolates "does the gun track my hand and feel like
mine" from "does the bullet go there."** Two questions, two slices, two wear
tests.

**Gates:** point the controller left, the gun goes left. **Hold the controller
still and move your head — the gun must NOT move with the head.** `36` proved
the head half of that already.

## SLICE 3 — THE BULLET FOLLOWS THE HAND

**`38` has already done the hard reading.** The recipe:

```
crosshair_x_pos = (desired_pixel_x - W*0.5) / ((1 - guncrossdamp) * W*0.5)
```

- **Write the INPUTS, never `crosshair_angle`** — it is recomputed every frame
  (`38` correction 2, `21`'s rule for the fifth time).
- **Write them EVERY frame** — the game rescales `crosshair_x_pos` on weapon
  switch, because `guncrossdamp` comes from `WeaponStats`.
- **Project the same hand pose used in slice 2** into the game's screen space, so
  the visible gun and the bullet cannot disagree by construction.

**Gate:** fire while pointing off-centre; the shot lands where the barrel points,
not where the head looks. **And the clamp behaviour from the section above is
observed and reported rather than discovered later.**

## SLICE 4 — THE KNOBS THAT DECIDE WHETHER IT FEELS LIKE YOURS

`37` trap 2, and it is not cosmetic: **auto-aim fights a tracked hand.** The gun
points where you put it and the game quietly moves the shot elsewhere.

- `currentPlayerSetXAutoAimEnabled` — already a runtime setter. **Knob, default
  decided by a wear test, not by argument.**
- `gunaimdamp` — damping tuned for a thumbstick reads as lag on a hand.
- The clamp behaviour, from the table above.

**`61`'s O12 amendment already flagged this:** there is currently no crosshair in
VR at all, so auto-aim may be doing the job the missing crosshair would. **Turn
it off and the answer may get worse before it gets better.**

---

## WHAT IS NOT IN THIS PLAN, DELIBERATELY

- **The scope** (`37` trap 3). Its own phase, RT64-side, after all of this.
- **Aim mode.** `36` left it head-locked by choice. In VR it has no role at all.
- **Two-handed weapons and the left hand.** One hand working beats two hands half-working.

## THE OPEN READS `38` LISTED AND NOBODY HAS DONE

**These block slice 3 and none of them is an experiment — they are all reads:**

1. Which of `bondview2.c:6072` / `:6077` is aim mode, **confirmed rather than assumed.**
2. Whether `crosshair_x_pos` has readers besides `caclulate_gun_crosshair_position_rotation`.
3. Whether `getPlayer_c_screenwidth()` is affected by anything the patch does.

**Do these before slice 3 is written, not during it.**
