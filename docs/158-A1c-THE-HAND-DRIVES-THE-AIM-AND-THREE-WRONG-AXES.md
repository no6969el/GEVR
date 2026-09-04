# 158 — A1c. THE HAND NOW DRIVES THE AIM. AND THREE GUESSES AT AN AXIS, ALL WRONG.

**2026-08-25. The slice that makes VR aiming real, the slice that makes the
bullet leave the barrel, and a methodological failure of mine that an instrument
caught in one run instead of four.**

---

## §1 — THE FINDING THAT REFRAMED EVERYTHING: THE SEAM IS COSMETIC

**Full detail in `157` §6.1.** `hand_override`'s matrix lands in
`hand->field_8EC`, and **every reader of `field_8EC` in the game tree is a
DRAWING site** (`gunfire.c:550-553`).

> ## **SO FROM `83` UNTIL TODAY, MOVING THE HAND MOVED THE GUN'S PICTURE AND NOTHING ELSE. `crosshair_x_pos` SAW THE STICK AND ONLY THE STICK.**

**The wearer said it plainly:** *"No matter where I move the gun it doesn't change
unless I move my trigger."*

**AND IT INVALIDATES `153` §3.** That section proved both integrators take the
same `turn_x` and the damping cancels, concluding the clamp was the only
difference between gun and bullet. **The proof was right; the premise was not —
the hand never fed `turn_x`.** A1's unclamping removed a limit the hand could
never reach.

## §2 — A1c: WRITE THE GUN'S POINTING INTO `crosshair_x_pos`

**`86`'s recipe steps 4-5, never built until now.** In the patched
`caclulate_gun_crosshair_position_rotation`, after the stock integrator loop:

```c
if (geVrAimFromHand(&g_geVrAimNdc[0])) {
    f32 denom = 1.0f - guncrossdamp;
    if (denom > 0.0001f) {
        g_CurrentPlayer->crosshair_x_pos = g_geVrAimNdc[0] / denom;
        g_CurrentPlayer->crosshair_y_pos = g_geVrAimNdc[1] / denom;
    }
}
```

**THE PRE-LOAD IS THE POINT.** `crosshair_angle = crosshair_x_pos * (1-damp) * w/2 + w/2`,
so holding `ndc / (1-damp)` places the crosshair **AT** the target rather than
crawling toward it. **Writing `crosshair_angle` directly is the mistake `38`
correction 2 names** — the next tick overwrites it from the integrator.

**It REPLACES the stick rather than adding to it** (two drivers on one integrator
is `116`'s fault), and **the host REFUSES when there is no hand pose**, leaving
the stick in charge on that frame.

## §3 — THREE GUESSES AT THE BARREL AXIS, ALL WRONG, AND THE INSTRUMENT THAT CAUGHT IT

**I picked `R`'s third ROW as the gun's forward axis. Then its third COLUMN. Then
made the axis a knob.** The knob could not have worked either — **`-AimFwdAxis`
selected the forward component but the lateral pair was ALWAYS `(fx, fy)`, so
axis 1 divided Y by Y.** A bug in the escape hatch.

**WHAT SETTLED IT WAS ONE LOG LINE, BUILT BEFORE THE RUN:**

```
AIM(docs158) state=REFUSED(fwd too small - WRONG AXIS/SIGN) fwd=-0.303 ndc=(0.000,0.000)
AIM row3=(-0.450,-0.840,0.304) col3=(-0.592,0.747,0.304)
```

> ### **`REFUSED` ON EVERY SAMPLE. THE AIM WRITE HAD NEVER RUN ONCE.**
> And `row3`'s dominant term is **Y at -0.84**, not Z. **That vector is mostly
> VERTICAL. It is not a barrel and never was.**

**AND THE GAME-SIDE LINE AGREED FROM THE OTHER SIDE:**
`crosshair_angle=(160,120)px` — **dead centre of a 320x240 screen, unmoving.**
With the write refused and no stick input, both integrators decay to centre and
every shot flies straight out along the view axis.

> **`48`'s rule that an instrument must be able to say "I CANNOT ANSWER THIS"
> paid for itself here.** A refused frame and a zero-valued frame are identical
> in the headset. **Without `state=REFUSED` this would have been four launches of
> sign-sweeping against a quantity that was never a barrel.**

## §4 — WHY `R` WAS THE WRONG PLACE TO LOOK AT ALL

**`R` IS A DRAWING MATRIX.** `R = Rhead * Rhand^T` (`79` correction 2) with a
`diag(sgn)` conjugation baked in for the seam (`155`). **It is tuned to place a
model, not to carry geometry.** Three guesses inside it were three guesses too
many.

## §5 — THE DERIVATION, WHICH IS NOT A GUESS

`ge_vr_quat_to_basis` is a **standard column-vector basis**: `w[i] = sum_j m[i][j]*l[j]`,
local -> world. So:

```
gun forward in WORLD = Rhand * (0,0,-1) = -(third COLUMN of Rhand)
gun forward in HEAD  = Rhead^T * that
forward component    = -v[2]            (OpenXR head frame looks down -Z)
ndc = ( v[0] / -v[2], v[1] / -v[2] ) * gain
```

**Computed where `Rhead` and `Rhand` are already in scope, published as
`g_geVrAimFwdHead`, and it is now the DEFAULT** (`-AimBasis 2`). The two R-based
paths stay reachable at `-AimBasis 0` / `1` for comparison. **The lateral-pair
bug in §3 is fixed.**

**THE GATE, WRITTEN BEFORE THE RUN:** the log prints `fwdHead=(x,y,z)`, and
**`z` must go NEGATIVE when the gun points forward.** If it does not, the head
frame is not what OpenXR says it is and that is a bigger finding than this slice.

## §6 — A1b: THE ORIGIN. WITHDRAWN ONCE, THEN BUILT.

**`gunfire.c:4871-4873` sets the shot's origin to `(0,0,0)` — the CAMERA.**
Invisible and correct on a flat screen; in VR the gun is a metre from the eye.

**THE FIRST ATTEMPT WAS WITHDRAWN BEFORE IT COMPILED** — reproducing
`bullet_path_from_screen_center` needs eight symbols patch code cannot reach,
plus the `WeaponStats` layout.

**THE SECOND ATTEMPT DECLARES ONLY WHAT IT NEEDS**, following the partial-struct
pattern `100` established for S0. **`Inaccuracy`'s offset was MEASURED, not
guessed:** `WeaponStats`' fields were walked in order out of `gun.h` and it lands
at **byte 48**. `geVrInaccuracyOf()` **refuses a value outside [0,100]** and
falls back to perfect accuracy — **a wrong offset would otherwise present as
bizarre weapon spread that nobody would attribute to a struct layout** (`115`).

> **WORN, AND IT WORKS:** *"Bullets come out of the gun."* **The wearer's earlier
> report was the exact half-fixed signature:** *"the bullet may still be coming
> out from the camera, but the place it comes out is now wherever I have the
> gun"* — direction from the eye, origin at the barrel.

**ONE LANDMINE LOGGED:** the PAL/NTSC branch was replaced with the literal
`240.0f`. **Correct for this `-DVERSION_US -DREFRESH_NTSC` build and WRONG for a
PAL one.**

## §7 — STATE

| | |
|---|---|
| **A1** unclamp (`153`) | Built. **Cannot help until the hand drives the aim** |
| **A1b** origin (`157`) | **BUILT AND WORKING — bullets leave the barrel** |
| **A1c** direction (`158`) | **Built; REFUSED on every frame so far. §5 is the fix, unrun** |

**THE NEXT RUN IS THE WHOLE QUESTION:** does `state=` read `APPLIED`, and does
the crosshair follow the hand? **Then, and only then, `-AimGain` and the signs.**
