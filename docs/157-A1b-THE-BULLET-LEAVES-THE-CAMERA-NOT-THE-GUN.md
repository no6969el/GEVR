# 157 — A1b. THE BULLETS COME OUT OF THE PLAYER'S FACE, AND IT IS THREE LINES.

**2026-08-25. The wearer, and it is the thing standing between him and actually
playing:** *"The bullets don't shoot from the gun. They shoot from the player. I
need that to shoot from the gun in order to actually take a break and test the
game for once."*

---

## §1 — THE FAULT

`gunfire.c:4871-4873`, inside `bullet_path_from_screen_center`:

```c
arg0->x = 0.0f;
arg0->y = 0.0f;
arg0->z = 0.0f;
```

> ## **`arg0` IS THE SHOT'S ORIGIN, AND ZERO IS THE CAMERA.**
> The callers name it themselves — `chrprop.c:931` passes
> `&shotdata.viewOrigin`. **Every bullet in the game leaves the player's eye.**

**ON A FLAT SCREEN THAT IS INVISIBLE AND CORRECT**: the camera *is* the player,
and a shot from the eye down the crosshair ray is exactly right. **In VR the gun
is a metre away from the eye and held in a hand, and the deception collapses.**

**THIS IS A DIFFERENT QUANTITY FROM A1.** `153`/A1 fixes where the shot **GOES**
(the clamp on `crosshair_angle`). **A1b fixes where it comes **FROM**.** They are
independent, they have separate knobs, and a failure of one must not be readable
as a failure of the other — `155` §3 is this session's own proof of that hazard.

## §2 — THE FIX

**`RECOMP_PATCH bullet_path_from_screen_center`**, stock line for line, with the
three zeroes replaced by the gun's muzzle **in the head's frame, in game units —
the space `arg0` already lives in.**

**The muzzle comes from the host, captured inside `hand_override` from the very
numbers the gun is DRAWN with**, so the origin and the model cannot drift apart.
`48` rule 8, one source of truth. `GE_VR_MUZZLE_EXT` then pushes it along the
gun's own forward axis (`R`'s third row) from the grip toward the barrel.

**ONE GATE, HOST-SIDE.** `muzzle_origin()` returns false when the feature is off,
when there is no hand pose, at `-NoXr`, or before the first controller sample —
**and the stock zeroes stand.** An earlier draft of the patch cached a second
opinion game-side and referenced a function that did not exist; **two sources of
truth for one boolean is what `116` was written about.** Removed.

## §3 — THE SIGNS ARE NOT ESTABLISHED, AND THAT IS SAID OUT LOUD

**The game's view-space handedness was never measured.** `GE_VR_MUZZLE_SIGN_X/Y/Z`
exist because **this project has been wrong about a sign five times** and because
a wrong sign here does something specific and recognisable:

> **A WRONG Z PUTS THE MUZZLE BEHIND THE PLAYER — "the bullets come from behind
> me."** That is the signature to look for, and it is a SIGN, not a failure of
> the slice.

## §4 — AS BUILT. NOT COMPILED, NOT WORN.

| File | Change |
|---|---|
| `patches/ge_vr_aim.c` | **2nd `RECOMP_PATCH`** — `bullet_path_from_screen_center` |
| `include/ge_vr_host.h` | `ge_vr::muzzle_origin(float*, int)` |
| `src/main/rt64_render_context.cpp` | captures hand position + gun forward in `hand_override`; the accessor and its env gate |
| `src/game/recomp_api.cpp` | `recomp_ge_vr_muzzle_origin` |
| `patches/syms.ld` | `0x8F000134` |
| `patches/misc_funcs.h` | `DECLARE_FUNC(s32, recomp_ge_vr_muzzle_origin, f32*, s32)` |
| `vr.ps1` | `-MuzzleOrigin -MuzzleExt -MuzzleSignX/Y/Z`, **all five in the clear list** |

**A SECOND NEW `RECOMP_PATCH` NAME** — `07`'s rename step, `133`'s `LNK2005`
self-heal, and **`CMakeLists.txt:150`'s standing "modifying patches requires two
builds to take". RUN `build.ps1` TWICE BEFORE CONCLUDING THE KNOB IS DEAD** —
`136` cost a whole session to exactly that.

## §5 — THE GATES

| Gate | Test |
|---|---|
| **G-A1b-1** | **Fire at a wall up close. The impact lines up with the BARREL, not the eye.** Today's build cannot pass this |
| **G-A1b-2** | **If shots seem to come from behind or beside you, sweep `-MuzzleSignZ -1`, then X, then Y.** §3 |
| **G-A1b-3** | **`-MuzzleExt 20`** should walk the origin visibly along the barrel. If nothing moves, the muzzle is not being applied at all |
| **G-A1b-4** | **Unset = identical to today.** The host gate returns false and the stock zeroes are written |
| **G-A1b-5** | **`-NoXr` is untouched** — no hand pose, so the gate is false by construction |

> **WHAT WOULD MAKE THIS INSTRUMENT USELESS: if the shot still leaves the eye
> with the knob ON and `-MuzzleExt 20` changes nothing, the patch never got
> emitted.** Check `patches.map` and `RecompiledPatches/patches.c` for
> `bullet_path_from_screen_center` before sweeping a single sign. `136`.


---

# §6 — TWO THINGS LEARNED AFTER THIS WAS WRITTEN. THE FIRST INVALIDATES `153` §3.

## §6.1 — THE SEAM IS COSMETIC. THE GAME'S AIM NEVER HEARS ABOUT THE HAND.

**The wearer, on the built slice:** *"No matter where I move the gun it doesn't
change unless I move my trigger or trigger head aim."*

**MEASURED, not inferred.** `hand_override`'s matrix lands in `hand->field_8EC`
(`ge_vr_bindtest.c:1248`), and **every reader of `field_8EC` in the game tree is
a DRAWING site** — `gunfire.c:550-553` adds its translation to `gunofs` and
multiplies its rotation into `rotmtx`. **Nothing in the aim path reads it.**

> ## **SO THE HAND MOVES THE GUN'S PICTURE AND NOTHING ELSE. `crosshair_x_pos` AND `gun_azimuth_angle` SEE ONLY THE STICK.**

**THIS INVALIDATES `153` §3's CONCLUSION.** That section proved both integrators
take the same `turn_x` and the damping cancels, and concluded **the clamp is the
only steady-state difference between gun and bullet.** The proof is correct and
**the premise is not: the HAND never feeds `turn_x`.** So A1's unclamping removed
a limit the hand cannot reach. **Necessary, and nowhere near sufficient.**

**WHAT IS ACTUALLY OWED IS `86`'s RECIPE STEPS 4-5, WHICH WERE NEVER BUILT:**

> **Write `crosshair_x_pos` / `crosshair_y_pos` — NEVER `crosshair_angle` — every
> frame, from the hand-derived screen point, with the pre-load
> `crosshair_x_pos = ndc / (1 - guncrossdamp)`** so the damped integrator settles
> ON the target instead of crawling toward it. `38` correction 2,
> `bondgun.c:8408`.

**`153` §8's reader sort STILL STANDS and is still needed** — it says which
readers want the true aim once the hand is driving it. **It was the right read of
the wrong half.**

## §6.2 — AUTO-AIM IS OFF, IN THE GAME'S OWN SETTINGS. RECORD IT.

**The owner disabled auto-aim from the in-game options, 2026-08-25.** `48`'s
floor item E: a setting changed outside the repo, and **the in-game menu is
exactly where this project has been bitten before** (`108` §4, `graphics.json`).

**TWO CONSEQUENCES, AND ONE IS GOOD NEWS:**

- **The latching the wearer reported is gone as a CONFOUND.** `bondview2.c:6047`
  gates on `currentPlayerGetXAutoAimEnabledRedirect()`; with it false the HONEY
  branch takes `speedtheta * 0.3f` instead of `autoaimx`.
- **AND `chrprop.c:2322`'s MANUAL branch is now the live hit test:**
  `passes_horizontal_check = screen_left_edge[0] <= crosshair_x && crosshair_x <= screen_right_edge[0]`
  — **it still reads the crosshair through `get_bullet_angle()`.** So once the
  hand drives `crosshair_x_pos`, **hit detection follows for free.** G-A1-6's
  worry about silently changing auto-aim is moot while it is off.
