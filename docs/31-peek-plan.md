# 31 — plan: peek. A raised viewpoint, and deliberately not a jump

**2026-08-22.** Asked for during a VR session, and **explicitly off the VR
critical path.** Nothing here is required by any Phase 2 or Phase 3 slice, and
nothing here should be allowed to delay 3f-4's first wearing.

## What this is, and the honesty requirement

GoldenEye has no jump. This does not add one.

**Peek raises where Bond looks from. It does not move Bond.** You can see over a
crate; you cannot get on top of it, cannot clear a railing, cannot reach a ledge,
and cannot escape any part of any level. Your collision, your footing and your
hitbox are exactly where they were.

The user asked for that stated plainly rather than left to be discovered, and it
belongs in three places, not one:

1. **The binding's readable name** — `"Peek (not a jump)"`, since that string is
   what the config menu renders.
2. **A line of copy in the controls page**, next to the binding row.
3. **This document**, first paragraph.

A feature that reads as "jump" in a menu and then refuses to clear a knee-high
crate is worse than no feature. The name is doing real work.

## Why the game makes this cheap, and a real jump expensive

Read from the decomp rather than assumed.

**There is no vertical velocity anywhere in the player.** The `vv_*` fields are
view *angles* — `vv_theta`, `vv_verta`, and their sines and cosines. The speed
fields are `speedforwards`, `speedsideways`, `speedstrafe`, `speedboost`: all
horizontal. There is no gravity term, no airborne flag, no vertical integration.

Bond is not a physics body. He is placed on floor tiles and the tile supplies his
height.

**But a vertical offset system already exists, and it works.** Crouch:

| Field | Role |
|---|---|
| `crouchpos`, `autocrouchpos` | `CROUCH_STAND` / `CROUCH_HALF` / `CROUCH_SQUAT` |
| `ducking_height_offset` | the live offset, smoothly interpolated (`bondview2.c:6770`) |
| `standheight` | the stationary ground reference (`bondhead.c:289`) |
| `eyeheight` | recomputed per frame in `bondviewUpdatePlayerCollisionPositionFields` |

So the game already animates a vertical eye offset every time you crouch. **Peek
is that machinery, driven the other way.** That is the whole reason it is a small
slice and a real jump is not.

A real jump would need vertical velocity, gravity, an airborne state, floor
collision reworked so the player is not re-seated on a tile every frame, and
landing against arbitrary geometry. The last is the expensive one: the levels
were authored knowing the player can never leave the ground, so the first thing a
working jump finds is the places you can escape the map. **Not proposed.**

## The insertion point — one decision, and it is the whole design

Two candidates, and they differ in a way the player will feel.

**A. View only — `bondhead.c`.** The camera height is built there:

```c
headpos.f[1] = ((bondheadmatrices[0].m[3][1] - standheight) * headamplitude) + standheight;
```

Add the peek offset to that result. The eye rises; collision, hitbox and footing
are untouched.

**B. The height stack — `bondviewUpdatePlayerCollisionPositionFields`.**

```c
phi_f0 = eyeheight + ((field_88 + ducking_height_offset) * player_perspective_height);
... field_488.collision_position.f[1] = field_70 + phi_f0;
```

This feeds **collision position**, and it is read by chr AI and by line-of-sight
checks (`bondview2.c:9571`, `9625`, `chraction.c:5854`).

**Take A.** B would raise where guards think your head is, which changes who can
see and shoot you — a stealth-relevant change smuggled in behind a camera
feature. A peek that gets you shot from across the room is not what was asked
for, and worse, the cause would be invisible.

**Consequence, and it must be in the release notes:** peeking over a crate lets
*you* see, and does not let guards see you any differently. That is a small
gameplay advantage. It is the honest reading of "view only" and it is preferable
to the alternative, but it should be stated rather than discovered.

## The button, end to end

The input system is x-macro driven and the menu rows are declared by enum name,
so a new binding is four small edits and no new machinery.

| # | File | Change |
|---|---|---|
| 1 | `include/recomp_input.h` | New group `DEFINE_GE_EXTRA_INPUTS()`, with `DEFINE_INPUT(PEEK, 0, "Peek (not a jump)")`, folded into `DEFINE_ALL_INPUTS()` |
| 2 | `src/game/config.cpp` | Default mapping, plus save/load, alongside `TOGGLE_MENU` |
| 3 | `assets/config_menu/controls.rml` | A binding row, `data-for="cur_binding, i : inputs.PEEK"`, and the "not a jump" line |
| 4 | `src/game/input.cpp` (or the host tick) | Poll with `recomp::get_input_digital` |

**The bit field must be 0.** The N64 button inputs carry a controller bit and are
merged into the controller state the game reads; `TOGGLE_MENU` and friends use
`0` because they are host-only. Peek is host-only in exactly the same way — it
must not appear as a phantom N64 button press, or it will fire whatever the game
already binds to that bit.

Default binding: **unbound.** An off-by-default option cannot surprise anyone,
and the user asked for this as an option rather than a change to the game.

## Host to patch

The patch runs as MIPS; the button is read by the host. `22` established the
mechanism and `21` established the gate pattern, so this is an existing road:

```
patches/syms.ld       recomp_ge_peek_amount = 0x8F000118;   # next free
patches/misc_funcs.h  DECLARE_FUNC(s32, recomp_ge_peek_amount, void);
src/game/recomp_api.cpp   returns the current peek offset
```

`0x8F000114` is `recomp_ge_vr_set_world_camera`; `0x118` is the next slot.

**Return `s32` in game units, not `f32`.** The existing import is `void(s32)`, so
integer returns across this boundary are proven and float returns are not. A peek
is a whole number of centimetres; there is nothing to gain by being the first
call to test float return conventions here.

**A new `RECOMP_PATCH` name means the long build** with
`tools_weaken_patched.py`, and the renamed count goes **31 to 32** (`07`).

## Ramp, so it reads as a movement rather than a teleport

Instant is wrong and the game already shows why: crouch interpolates. Match it.

- Hold to rise over ~0.15 s to the full offset, release to fall back over ~0.2 s.
- Full offset **40 units**, about 40 cm (`16`), roughly standing on your toes and
  craning. Enough to clear a crate, not enough to look over a wall.
- Both numbers behind environment variables for the first build —
  `GE_PEEK_UNITS`, `GE_PEEK_RISE_MS` — for the same reason `GE_VR_EYE_SIGN` has
  one: a feel value settled by argument is a value that gets re-argued.

**Interaction with crouch:** peek while crouched should return you toward
standing, not add 40 units on top of a crouch. Simplest correct rule: the peek
offset is applied **after** `ducking_height_offset` and the sum is clamped to the
standing height plus the peek limit.

## VR: peek already exists, and it is called jumping

**Asked during this session: what happens if the player physically jumps in VR?**

Traced through 3f-4 rather than guessed. Each eye's transform is built from
`views[eye].pose` — the headset's real position in `LOCAL` space, in metres —
converted by `GE_VR_UNITS_PER_METRE` and applied as the view-space transform `E`,
*after* the game's own camera.

So a real jump of 0.4 m raises the viewpoint by about 40 game units. **That is
the peek button, to within a couple of centimetres, and it already works.**

More to the point, it works *the same way peek is designed to work* — view only.
The game is never told. Bond's collision, footing, hitbox and what the guards
think they can see are all untouched, because head translation never reaches
them. Physical crouching gets you the same thing downward: you can duck to look
under a desk without the game believing you crouched.

This is the strongest argument for design A above. **The VR path already made the
view-only choice**, and it made it structurally rather than by decision — `E`
acts after `V` and there is no route from there back into collision. A peek that
took route B would behave differently from physically standing up, in the same
build, on the same button-press. Two mechanisms for one action, disagreeing.

### It is unclamped, and that is a real problem

Nothing limits head translation. Stand on a chair and your viewpoint goes through
the ceiling. Crouch to the floor and it goes through it, and you see the world
from underneath through the near plane.

That is the **head-in-geometry** problem `14` describes and Phase 4 owns, reached
by a new route — and jumping reaches it faster than walking into a wall does. It
is not a peek bug and must not be fixed here, but this document is where it was
first noticed from this direction, so: **Phase 4's fade needs to consider
vertical position, not only walls.**

### A physical jump is a scale ruler

Useful accident. The head translation is the only quantity in the build with a
**known real-world size** — you know roughly how high you can jump and how far
you can crouch.

So: crouch until your view reaches a known object's height, or jump beside
something whose in-game height is known, and compare. That is an independent
check on `GE_VR_UNITS_PER_METRE` that does not depend on stereo, on the eye sign,
or on judging depth — all of which are still unsettled. **Worth trying during the
3f-4 sweep in `00-START-HERE`.**

### So the button is a flat-screen feature

In a headset, peek should default **off**. Moving someone's viewpoint without
their body moving is precisely the discomfort 3f-4 was written to remove, and
here the physical version is available, free, and comes with correct vestibular
cues — which is exactly why a real jump feels fine and a button-driven rise may
not.

**Gate it on that rather than assuming:** with the headset on, does the button
feel wrong next to physically standing up? If it does, default it off under XR.

## Staging

### 31a — the binding, doing nothing

Add the input, the default, the menu row and the "not a jump" copy. **Poll it and
log it. Change no game behaviour.**

**Gate:** the row appears in the controls menu, binds to a chosen button,
survives a restart, and `gevr.log` shows it pressed and released. **The game plays
identically.**

Worth its own build because it is the half that touches the config file and the
UI — the half that can break something a person relies on, and the half that has
nothing to do with the game's code.

### 31b — the offset

The host import, the patch, the ramp.

| # | Check | Pass |
|---|---|---|
| 1 | Hold the button standing | View rises ~40 units over ~0.15 s, smoothly |
| 2 | Release | Falls back, no snap |
| 3 | Stand at a crate | You can see over it |
| 4 | Walk into a wall while peeking | **You do not clip through, and you do not get anywhere new** |
| 5 | Peek while crouched | Rises toward standing, does not overshoot |
| 6 | Guards | React exactly as before. Nothing about being seen changes |
| 7 | Unbound | Game is byte-for-byte the game |

**Gate 6 is the one that justifies choosing A over B**, and it is the one that is
tempting to skip because nothing visibly happens.

## Risks

1. **The name.** Someone will read "Peek" as "jump" anyway. Hence the readable
   name carrying the disclaimer, not just the docs.
2. **Menu regressions.** Editing `controls.rml` and the config save format risks
   a bad binding file. Keep 31a separate and check a restart.
3. **Interpolation ownership.** `ducking_height_offset` is driven by existing
   crouch code every frame. Peek must be a **separate term**, not a write into
   that field, or the crouch logic will fight it — the same shape as `21` and
   `26`: do not write into state someone else owns.
4. **Head bob.** `headamplitude` scales the walk bob around `standheight`. Adding
   peek after that is correct; adding it before would make the bob grow with the
   peek.

## Explicitly not in scope

Jumping. Climbing. Mantling. Ledges. Any change to collision, hitboxes, AI
perception, or level traversal. **If any of those become desirable, they are a
different document and a much larger one.**
