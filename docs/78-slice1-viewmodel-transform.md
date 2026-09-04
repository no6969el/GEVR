# 78 — SLICE 1 of `76`: the viewmodel's distance and size, as knobs.

**2026-08-23, ~17:00. Written before the code, per `48` rule 2.**

**Read `76` for why this is first and `77` for the evidence that it is a
separate fault from world scale.**

---

## THE CHOKE POINT, FOUND BY READING RATHER THAN GUESSING

The viewmodel's placement is built in **`gunfire.c` `gunUpdateAndFire()`**, and
`gunmtx` is copied into `hand->gunmtx_camspace` at **`gunfire.c:572`** — the name
is not a hint, it is the answer. **The matrices are in CAMERA space**, confirmed
three ways:

- `bondview.h:210` — `Mtxf gunmtx_camspace;`
- `gunfire.c:574` must multiply by `currentPlayerGetViewToWorldMtxf()` to get a
  world-space copy.
- `gunfire.c:818` — `hand->field_B64 = -hand->gunmtx_camspace.m[3][2];`
  **The camera looks down -Z, so pushing the gun away means DECREASING
  `m[3][2]`.**

The node matrices are emitted with **`G_MTX_LOAD`, not `G_MTX_MUL`**
(`model.c:4854`), so each one is a **complete, absolute modelview.** No camera
matrix is combined in later. That is what makes this tractable.

## WHERE THE CHANGE GOES, AND WHY NOT THE OBVIOUS PLACE

**The obvious place is `gunfire.c:643`**, the last touch of `gunmtx` before it
becomes the model root. **It is in `lib/ge/` — game code we cannot edit
directly.** Game-side changes go through `RECOMP_PATCH`, which replaces a
function **wholesale**, and `gunUpdateAndFire` is far too large to replace
safely.

**So the patch target is `bondviewTransformManyPosToViewMatrix`
(`bondview2.c:10662`) — twelve lines, and it is the LAST thing to touch the
matrices before the f32 -> s32 conversion.** The display list already holds
pointers to them by then; the values are read at execution, after conversion.
**Modifying them here changes what is drawn.**

**It is called for characters and casings too**, so it must identify the
viewmodel. It can, exactly and without heuristics:

```c
arg0 == ((Model *)&g_CurrentPlayer->hands[h].field_B68)->render_pos
```

**A pointer identity against the player's own hand models.** No name, no
address, no "is it probably the gun" — the thing `70`'s method note says to
insist on.

## THE TRANSFORM

Two knobs, and they do genuinely different things:

| Knob | What it does | Why not the other one |
|---|---|---|
| `GE_VR_VIEWMODEL_SCALE` | Scales the gun **about its own root**, so it gets bigger or smaller **where it is** | Scaling about the EYE would move and resize it together, leaving the angular size unchanged — which would look like nothing happened |
| `GE_VR_VIEWMODEL_PUSH` | Moves it away from the eye, in game units | This is the one that fixes the convergence. `36` measured the gun at **15-25 cm apparent**; the eyes cannot comfortably converge there |

**Scaling about the root, not about each node**, is the detail that matters:
every node matrix is absolute, so scaling each one in place would pull the slide,
hammer and muzzle apart. The root's translation is captured first and every
node is scaled about it.

```
root = render_pos[0].pos.m[3][*]          captured BEFORE anything changes
per node:  basis *= scale
           t = root + (t - root) * scale
           t.z -= push                    -Z is away, gunfire.c:818
```

**Defaults are `scale = 1.0`, `push = 0.0` — an exact identity**, so a build with
the knobs unset is byte-for-byte the current behaviour, and `-NoXr` cannot
change. That is the regression argument AND it is checkable by leaving them
unset.

## THE PLUMBING

Host -> patch, following the seam `22` already established:

| | |
|---|---|
| `include/ge_vr_host.h` | `float viewmodel_scale(); float viewmodel_push();` |
| `src/main/rt64_render_context.cpp` | reads `GE_VR_VIEWMODEL_SCALE` / `_PUSH` via the existing `ge_vr_env_float` |
| `src/game/recomp_api.cpp` | two exports returning float |
| `patches/syms.ld` | `0x8F000118`, `0x8F00011C` — next free after `recomp_ge_vr_set_world_camera` |
| `patches/misc_funcs.h` | two `DECLARE_FUNC`s |
| `patches/ge_vr_bindtest.c` | the `RECOMP_PATCH` |
| `vr.ps1` | `-ViewmodelScale`, `-ViewmodelPush` |

## THE GATES — written before the code

| # | Gate | What would a build that did nothing have to do to pass it? |
|---|---|---|
| G1 | With both knobs unset, **nothing changes anywhere** | Nothing. This is the regression gate and it must pass first |
| G2 | `-ViewmodelPush 60` visibly moves the gun away from the face | It cannot. The apparent distance is the whole change |
| G3 | `-ViewmodelScale 0.5` makes the gun smaller **without moving it** | A build scaling about the eye would move it too, and a build doing nothing would not change either |
| G4 | **The world's apparent scale is UNCHANGED by both** | If the world moves, the change landed in the wrong matrix and the pointer test is wrong |
| G5 | **The user can look at the world with BOTH EYES OPEN** | This is the wearer's own falsifier and it is the real one |
| G6 | The gun does not come apart | If nodes separate, the scale was applied per-node instead of about the root |
| G7 | `-NoXr` plays a level unchanged | The knobs are identity by default, but `73` exists because "unchanged by construction" is an argument |

## WHAT THIS SLICE DELIBERATELY DOES NOT DO

- **It does not track your hand.** That is slice 2, and keeping it separate means
  "is it the right size and distance" is answered before "does it follow me".
- **It does not touch aim or the bullet.** `gunmtx_camspace` and
  `throw_item_pos_related` are snapshotted at `gunfire.c:572-574`, long before
  this function runs, so **the aim direction, projectile spawn and muzzle-flash
  world position are untouched by construction.**
- **It does not hide the arm.** `77` and the read behind it found the honest hide
  point is `hand->field_87F`, not `hand_invisible` — which is a load-state
  counter with a misleading name. That is a knob for later.
