# 154 — G3. THE ANCHOR ON THE FRONT OF THE GUN. THE OFFSET WAS NEVER TURNED ON.

**2026-08-25. The wearer, with seam rotation ENABLED for the first time since
`85`:** *"It lets me turn left and right. But there's like an anchor on the front
of the gun that holds it downwards when I move it, and the opposite direction if
I manipulate it. It's not completely free."*

---

## §1 — WHY ROTATION WAS OFF AT ALL, AND IT WAS OUR OWN LAUNCH FLAG

**`-SeamNoRot` sets `GE_VR_SEAM_ROT=0`, and `rt64_render_context.cpp:1109`
OVERWRITES THE ENTIRE ROTATION MATRIX WITH IDENTITY.** The gun got the hand's
position and a fixed orientation — up, down, left, right, no turning.

**It has been in every launch command in this project's standing instructions**,
including every one issued this session. `85` set it deliberately: the rotation
pre-multiplies `rotmtx` (`gunfire.c:548`), so it acts in the gun's own frame
about its own origin, and **a wrong rotation does not tilt the gun, it swings it
out of view.** `-SeamNoRot` isolated the good half. **The good half has been the
only half ever since, and nobody re-tested the other one.**

## §2 — THE ANCHOR: THE GUN IS PIVOTING ABOUT THE MODEL'S OWN ORIGIN

> ## **`ge_vr_gun_off_x/y/z` ALL DEFAULT TO `0.0f` (`:925-927`) AND NO LAUNCH HAS EVER SET THEM.**

**With a zero offset the gun rotates about wherever the model was authored
around.** If that is at or near the muzzle, rotating the controller swings the
BACK of the gun while the nose stays put — **an anchor on the front, inverting
when you rotate the other way. That is the reported symptom exactly.**

**THE GRIP OFFSET IS THE MECHANISM THAT FIXES THIS AND IT HAS NEVER BEEN ON.**

### PERFECT DARK'S VALUES — `102`, read at `67ea20c`, MIT, ATTRIBUTION OWED

`gCtrlPos + Ry180 * posrotmtx * off`. Default (pistols) **`(0, 16, -4)`**,
gun-model frame, X right, Y up, Z along the barrel. **The Y of 16 is the
dominant term: it lifts the pivot off the model origin to where a hand grips.**

**TWO TRAPS BEFORE COPYING ANY NUMBER:**

1. **UNITS. PD's are ~cm; ours are 50 per metre, so ONE GE UNIT IS 2 cm.**
   PD's `(0, 16, -4)` is about **`(0, 8, -2)`** for us. **Copying 16 straight
   across is double.**
2. **THE `Ry180` BASIS.** `102` measured X and Z negated relative to their
   original authoring — a tuned Falcon2's Z went `+7.3 -> -8.4`, sign flipped,
   magnitude kept. **Copy the placement or re-negate x and z; the numbers alone
   give a gun mirrored about the grip.**

## §3 — AND A CONVENTION MISMATCH FOUND WHILE COMPARING. IT IS A KNOB, NOT A FIX.

**Twelve lines apart in the same function:**

```c
handPos[i]  = (dx*Rhead[i][0]) + (dy*Rhead[i][1]) + (dz*Rhead[i][2]);  /* :1124 */
handPos[i] += (ox*R[0][i])     + (oy*R[1][i])     + (oz*R[2][i]);      /* :1131 */
```

**The hand position sums `M[i][j]`; the grip offset sums `M[j][i]` — the
transpose.** The second site at `:1355` has the same shape. **PD uses the
forward rotation.**

> ### **I DID NOT "FIX" IT, AND THE REASON IS THE POINT.**
> Whether the transpose is wrong depends on `ge_vr_quat_to_basis`'s convention
> AND on how `R` is composed — `R[i][j] = sum_k Rhead[i][k]*Rhand[j][k]`, i.e.
> `Rhead * Rhand^T`, with a comment citing `79` correction 2 saying that
> construction is deliberate. **I could not establish it by reading, and
> changing a matrix expression on an assumption is how five sessions were lost.**
> **`48`: measure the output. `86` §9: the wearer is the instrument.**

**SO IT IS `-GunOffFwd`, and ONE LAUNCH SETTLES IT.**

**IT IS LATENT UNTIL THE OFFSET IS NON-ZERO** — both forms add zero at
`GE_VR_GUN_OFF_* = 0`, so an unset build is an exact identity. `131`'s
discipline.

## §4 — AS BUILT. NOT COMPILED, NOT WORN.

| File | Change | Backup |
|---|---|---|
| `src/main/rt64_render_context.cpp` | `ge_vr_gun_off_fwd()`; both offset sites branch on it | `.bak154` |
| `vr.ps1` | `-GunOffFwd`, **and `GE_VR_GUN_OFF_FWD` added to the clear list** (`48` rule 6) | `.bak153` |

**`vr.ps1` parses clean** — checked with `[Parser]::ParseFile`, not by eye.
**No game-side patch, so no new `RECOMP_PATCH` name and no rename step.**

## §5 — THE GATES. Four launches, and the FIRST TWO NEED NO REBUILD AFTER THE FIRST.

**Drop `-SeamNoRot`. Keep `-HandSeam`.**

| Gate | Run | What it answers |
|---|---|---|
| **G-G3-1** | `-HandSeam` alone, no `-GunOff*` | **The baseline anchor.** Confirms §2: pivot at the model origin |
| **G-G3-2** | `-GunOffY 8 -GunOffZ -2` | **PD's default, scaled.** Does the pivot move to the grip? |
| **G-G3-3** | `-GunOffY 8 -GunOffZ -2 -GunOffFwd` | **§3's question.** Whichever of G-G3-2/3 tracks the hand cleanly names the convention |
| **G-G3-4** | the winner, with `-GunOffZ +2` | **The `Ry180` A/B.** If the gun looks mirrored about the grip, this is the sign trap in `102` |

> **WHAT WOULD MAKE THIS INSTRUMENT USELESS:** if the gun leaves view entirely at
> G-G3-1, the rotation itself is wrong and NO offset will rescue it — that is
> `85`'s original failure returning, and the answer is `102`'s basis (**G2 /
> 6D-08: `{w,-x,y,-z}` plus a 1.5708 rad X offset**), not this slice. **Say so
> and stop rather than sweeping offsets against a broken rotation.**
