# 214 — THE BARREL WAS ROTATED BY THE WRONG MATRIX, AND "THE LARGER GUN WENT FURTHER RIGHT" IS THE PROOF.

**2026-08-26. Tiers per `182`. One-line fix, plus two reports NOT yet diagnosed.**

---

## §1 — THE REPORT THAT DIAGNOSED IT

> `[REPORTED]`: ***"The aim was off to the right, the larger gun went further to
> the right."***

**THAT IS A ROTATION ERROR AND NOT AN OFFSET ERROR, AND THE DISTINCTION IS THE
WHOLE DIAGNOSIS.** A wrong CONSTANT would move a 35 cm barrel and a 70 cm barrel
by **the same amount**. **An error that scales with the offset's LENGTH is the
offset being rotated by the wrong matrix.**

**`[READ]`, and it is mine:** `g_geVrLastR` is published at the END of
`hand_override` — **AFTER `203`'s transpose at `:2130`.** So it holds **the matrix
the GAME consumes**, not the gun's true orientation. `213` rotated the barrel by
it, applying the **inverse** rotation.

**THE FIX IS COLUMNS INSTEAD OF ROWS** — transposing back recovers the true
orientation:

```c
bi = nx*R[0][i] + ny*R[1][i] + nz*R[2][i];   // was R[i][0], R[i][1], R[i][2]
```

> **`203` ESTABLISHED THE GAME WANTS THE TRANSPOSE. THE BARREL IS A VECTOR IN THE
> GUN'S OWN FRAME AND WANTS THE ORIGINAL.** Both are true at once, and storing
> only one of them is what made the mistake available. **The variable's name does
> not say which it holds** — that is the lesson, and it is the same shape as
> `184` §3a, where a LOG LABEL said `BULLET` and meant `SIGHT`.

**HOST-SIDE, ONE LINE, NO NEW SYMBOLS. ONE BUILD** (the symbol from `213` is
already in the binary).

---

## §2 — TWO REPORTS FROM THE SAME RUN, NOT DIAGNOSED, NOT GUESSED AT

### 2.1 THE CONTROLLER TURN RE-AIMS THE GUN

> `[REPORTED]`: ***"when I turn with the controller it messes with the gun, it
> turns it similar to how the head did before."***

**THIS IS NOT `201`'s FAULT RETURNING** — that was the head, it was `[MEASURED]`
fixed, and `[REPORTED]` confirmed *"when you turn your head, the gun does not
move."* **This is the STICK turn**, which yaws the GAME's camera rather than the
headset.

**AND THE EXPECTED BEHAVIOUR IS NOT OBVIOUS, SO IT IS WRITTEN DOWN BEFORE ANY
FIX:** stick-turning rotates the player's virtual body. **The gun SHOULD rotate
with the body — keeping its relationship to the wearer's real hand — and should
NOT rotate relative to that hand.** `[REPORTED]` says it does the second.

**`[ASSUMED]`, and what would settle it:** `R` is expressed in the game's CAMERA
space, and the camera yaws with the stick — so a constant `R` should already
follow the body. **If it does not, something else applies the game's yaw to the
gun a second time** — `gunfire.c:548` pre-multiplies `rotmtx`, and that is the
first place to read. **NOT to be fixed by trying a matrix: `199`/`200`/`203` all
cost less than the guesses that preceded them.**

### 2.2 THE GUN LOOKS LARGER

> `[REPORTED]`: ***"the guns seemed larger than normal."***

**`-ViewmodelScale` is the gun-to-world ratio ALONE** (`159`) — but the world
scale moved to 25 u/m this session and **`[REPORTED]` the guard reads *"smaller
and skinnier"* at the same time.** **A gun that looks bigger while the characters
look smaller is the SCALE question, not the aim** — and `213` §2.2 already named
a suspect for the "skinny" half: `bondview.c:657` derives `c_scalex` from the
game's own aspect, and `167` established those scales are never rebuilt from the
headset tangents.

---

## §3 — AND ONE THING THAT IS WORKING, SAID PLAINLY

**`[REPORTED]` the aim gets worse AT A DISTANCE AND AT THE EDGES.**

**AT THE EDGES is `211` §2's known geometry** — the crosshair is the eye ray, the
bullet leaves the muzzle, and the disagreement grows off-axis. **THE SOLVER IS
THE FIX AND IT IS THE NEXT BUILD.**

**AT A DISTANCE, HOWEVER, CONTRADICTS THE ORIGIN EXPLANATION** — a fixed origin
offset shrinks with distance (`193` §2, `[MEASURED]`). **A miss that GROWS with
distance is an ANGULAR error.**

> **SO `T7`'s TWO BRANCHES ARE BOTH `[REPORTED]` NOW, AND THEY CANNOT BOTH BE
> RIGHT.** `210`'s contact-range measurement supported the origin; this run
> reports the opposite at range. **The counter-example search `182` §2 demands is
> therefore OWED and OUTSTANDING**, and `SHOTREC` can settle it from one run:
> **two shots at the SAME target from two distances, and the angular residual
> compared.** **Do not build for either branch until that is measured** — and note
> that `214` §1's fix changes the muzzle, so **the measurement must be taken
> AFTER this build, not before.**

---

## §4 — WHAT IS OWED

1. **BUILD ONCE. `G-213` again** — swap to a longer weapon. **The proportional
   error must be gone.**
2. **THE DISTANCE MEASUREMENT** (§3): same target, two distances, `SHOTREC`.
3. **THE `gunfire.c:548` READ** (§2.1) — before any matrix is tried.
4. **THEN `211`'s SOLVER.**
5. **The scale** (§2.2) stays separate, with `213` §2.2's `c_perspaspect` print.

**NOTHING STAGED. THE COMMIT IS THE OWNER'S.**
