# 166 — THE 2D CROSSHAIR CANNOT WORK IN STEREO. THE LASER IS THE INSTRUMENT AND THE FIX.

**2026-08-25. Worn evidence. `163` §1 IS PARTLY RETRACTED HERE.**

> ## THE OBSERVATION THAT SETTLES IT, FROM THE WEARER
>
> ***"the aim target was up the whole time and duplicated (two different
> locations on each eye)"***
>
> **A HUD ELEMENT DRAWN AT A FIXED PIXEL CANNOT BE CORRECT IN BOTH EYES, AND NO
> AMOUNT OF TUNING CHANGES THAT.**

---

## 1. WHY. THE FRUSTUMS ARE ASYMMETRIC, AND THE LOG SAYS SO

```
[gevr-xr] eye 0 live tangents: -1.4869 1.0190 0.9657 -0.9657
[gevr-xr] eye 1 live tangents: -1.0190 1.4869 0.9657 -0.9657
```

**Horizontally the two eyes are MIRRORED and NOT symmetric about their own
centre** (`-1.4869` vs `+1.0190`). The optical centre of each eye's frustum is
therefore **not** the centre of the image. A crosshair blitted at pixel
`(160,120)` maps to a **different world direction in each eye**, which is
exactly the doubling reported. **There is no single pixel that is right for
both eyes.** The crosshair is a 2D object in a problem that stopped being 2D at
slice S0.

## 2. ►►►► `163` §1 IS RETRACTED IN PART. THE FOV READ WAS OWED AFTER ALL. ◄◄◄◄

`163` §1 said the projection "carries the game's own FOV" and therefore
`159` §6's FOV read was "NO LONGER OWED FOR AIMING." **THAT IS WRONG, and this
run falsifies it.**

| quantity | value | source |
|---|---|---|
| game vertical half-tangent | **1.327** | `fovy=106`, and `c_scaley = 1.327/110 = 0.012064` matches the logged `12064` EXACTLY |
| headset vertical half-tangent | **0.9657** | live tangents, = **88°** |
| **ratio** | **1.374** | |

**The game's `c_scalex/c_scaley` are built from 106 degrees while the image is
PRESENTED at 88.** `transform3Dto2DCoords` is the game's true projection *for
the game's own frustum* — but that is no longer the frustum being displayed,
because `currentPlayerSetProjectionMatrix` rebuilds the real matrix from the
headset tangents (`geVrBuildProj`). **So the crosshair pixel is wrong by 1.374x,
growing with angle from centre** — the wearer's *"the more I go up, the more it
gets off."*

> **THE BULLET IS NOT AFFECTED.** The shot direction is a raw game-space ray and
> never touches `c_scale`. **Only the DRAWN crosshair is wrong.** These are two
> different faults and they were being read as one.

## 3. AND THE WORLD SCALE WAS COMPENSATING FOR THE FOV ALL ALONG

`159` drove `-WorldUnitsPerMetre` 50 -> 25 -> 12 chasing a *"toy model"*
perception. **At 12 u/m the geometry is absurd and the wearer finally named it:**

| | at 12 u/m | correct |
|---|---|---|
| Bond's eye (175 u) | **14.6 metres** | 1.75 m |
| a 20-unit gun | **1.7 metres** | 0.2 m |

***"the gun/arm is much bigger than it should be"*** — **that is arithmetic, not
perception.** The geometrically correct value is **100** (1 unit = 1 cm, `16`,
which is exactly where `-HandUnitsPerMetre 100` came from).

> **THE SCALE KNOB WAS BEING USED TO CANCEL THE FOV ERROR, AND IT BROKE THE
> GEOMETRY TO DO IT.** A world rendered 1.374x too small in angle looks like a
> toy; shrinking units per metre makes it big again while making everything
> else - hand travel, gun size, muzzle offset - wrong by the same factor.
> **FIX THE FOV, THEN PUT THE SCALE BACK TO 100.**

## 4. WHAT THE WEARER'S TWO-SHOT EXPERIMENT MEASURED

Deliberate: aim off-target until it hits, then move to where it *should* be and
fire. Same muzzle, both shots:

```
hit  (adjusted)      ndc=(-0.352, 0.024)  dir=(-0.555,-0.023,-0.832)   tan 0.667  33.7deg
"should have been"   ndc=(-0.158,-0.013)  dir=(-0.286, 0.027,-0.958)   tan 0.299  16.6deg
```

**17 degrees of yaw, at a fixed muzzle.** `px` was verified against `dir` on all
18 distinct shots and agrees to ~0.01 NDC, **so the projection is
self-consistent and the barrel ray itself is what is displaced.** The tangent
ratio is 2.23, **which is NOT the FOV's 1.374** — so the FOV error alone does not
explain it and **there is a second term still unidentified.** Recorded
explicitly rather than guessed at.

**THE LEADING CANDIDATE, UNPROVEN:** the wearer aims by looking at the DRAWN
GUN, and the drawn gun's orientation is the seam matrix `Rhead*Rhand^T` with the
`diag(sgn)` conjugation and the grip offsets — **which `158` §3 already proved is
NOT the barrel.** The bullet follows the raw pose; the picture follows a drawing
matrix. If those disagree, the wearer aims the picture and the bullet leaves
along something else.

## 5. ►►►► THE LASER IS BOTH THE INSTRUMENT AND THE FIX. ◄◄◄◄

**A world-space beam along the aim ray is correct in stereo by construction** —
it is a real 3D object, so both eyes agree with no per-eye correction, no
projection, and no FOV dependency. It also makes §4 answerable in one look:
**if the laser leaves the barrel and lands where the bullet lands, the ray is
right and the DRAWN GUN is the liar.**

**AND IT SUBSUMES P1-6.** `161` P1-6 already says PD aims at the laser dot's
real hit point rather than at `muzzle + dir*100000`. **With a laser we get the
hit point, and the crosshair problem stops mattering at all** — the aim
feedback becomes the dot, as it is in Perfect Dark.

### 5.1 THE MECHANISM EXISTS IN GOLDENEYE, AND IT IS WORLD-SPACE

`hand->weapon_beam` is a `BeamRecord`: `pos` (start, WORLD), `delta` (unit
direction), `unk1c` (length). Built by
`CapBeamLengthAndDecideIfRendered(beam, item, muzzleWorld, targetWorld)`
(`gunfire.c:1007`), which `gunCreateBeamForHand` (`:1112`) calls with
`hand->field_B58` and `hand->item_related`. `ITEM_LASER` is explicitly rendered
more often (`:1069`). **`gunfire.c:757` already transforms the muzzle to world
with `currentPlayerGetViewToWorldMtxf()`, which is the exact conversion our
camera-space muzzle and direction need.**

### 5.2 AND IT IS BLOCKED BY docs\115, WHICH HAS ALREADY COST THIS PROJECT A SLICE

**NONE of it crosses the patch boundary:**

| symbol | in `patches/` ? |
|---|---|
| `BeamRecord` | **NO** — not in `structs.h` |
| `CapBeamLengthAndDecideIfRendered` | **NO** |
| `gunCreateBeamForHand` | **NO** |
| `currentPlayerGetViewToWorldMtxf` | **NO** |
| `mtx4TransformVecInPlace` | **NO** |

**That is five unreachable symbols plus a struct layout to hand-match — the
same shape as the eight that made `157` WITHDRAW slice A1b before it compiled.**
`BeamRecord` also carries four fields whose meaning is unknown (`unk00`,
`unk20`, `unk24`, `unk28`) and one of them (`unk00 = -1`) is the "do not render"
flag, so a wrong layout produces an invisible laser and no error.

> **SO THE LASER IS ITS OWN SLICE. It is not a knob and it is not four lines,
> and pretending otherwise is how `157` lost an evening.**

## 6. WHAT IS ALREADY FIXED, AND WHAT THE CROSSHAIR IS STILL GOOD FOR

`165`'s `gunSetSightVisible` patch is CORRECT and stays: `gunsightmode=2` is
`GUNSIGHTREASON_NOTAIMING`, set from the aim button, which nobody presses in VR.
**But per §1 the crosshair must NOT be used as an aiming reference in stereo.**
It is now only good for one thing: **confirming that the aim chain is moving at
all.** The laser replaces it as the measuring instrument.

## 7. THE ORDER FROM HERE

1. **FOV** — make the game's `fovy` agree with the headset's tangents, or drive
   `c_scalex/c_scaley` from the tangents directly. **Then set world scale back to
   100 and re-judge the "toy model" perception, which should be GONE.**
2. **LASER** — its own slice, sized honestly at §5.2.
3. **THEN §4's 17 degrees**, which the laser makes a one-look question.

---

# 8. ►►►► HOW PERFECT DARK ACTUALLY DOES IT. READ AT `67ea20c`, MIT. ◄◄◄◄

## 8.1 THEY HAVE TWO MODES AND SWITCH BETWEEN THEM PER FRAME

`sight.c:1099` — **`if (!show_laser_dot[hand])`** falls back to a 2D screen
crosshair; otherwise the **3D laser dot IS the aim indicator.** They did not
choose one, they ship both and pick per frame.

## 8.2 THE AIM ITSELF IS A **WORLD POINT** PROJECTED BY THE GAME'S OWN CAMERA MATRIX

`bondgun.c:8367-8395`. This is the part that matters most to us:

```c
if (dotpos is UNCHANGED since last frame)  {      // stale -> no real hit
    sp94 = muzzlepos + vrdir * 100000.0f;         // far point along the ray
    show_laser_dot[h] = false;                    // fall back to the 2D sight
} else {
    sp94 = hand->dotpos;                          // THE ACTUAL RAYCAST HIT POINT
    show_laser_dot[h] = true;
}
mtx4TransformVecInPlace(camGetWorldToScreenMtxf(), &sp94);
cam0f0b4d04(&sp94, sp8c);
x = 2.0f * sp8c[0] / viGetViewWidth()  - 1.0f;
```

> **THEY NEVER PROJECT A DIRECTION WITH A SCALE CONSTANT. They build a POINT IN
> THE WORLD and push it through the matrix the game is actually drawing with.**
> That is why they have no `AIM_GAIN` and no FOV problem: the projection is the
> render's own, by construction.

**AND `159` §6 / §2 ABOVE IS EXACTLY THE DIFFERENCE.** Our
`transform3Dto2DCoords` uses `c_scalex/c_scaley`, which are derived from
`c_perspfovy = 106` — **a DIFFERENT projection from the one
`currentPlayerSetProjectionMatrix` rebuilds from the headset tangents.** PD's
single-matrix discipline makes that class of bug impossible.

**THE STALENESS TEST IS THE OTHER HALF AND WE HAVE NO EQUIVALENT:** comparing
`dotpos` against `old_dotposX/Y/Z` is how they know whether the raycast actually
hit something this frame. A dot that has not moved is a dot that was never
written, and they fall back rather than draw a lie. **That is `48`'s "an
instrument must be able to say I CANNOT ANSWER THIS", in shipped prior art.**

## 8.3 THEY ALSO PRE-LOAD BOTH INTEGRATORS — P1-3 CONFIRMED FROM SOURCE

```c
if (crossdamp < 1.0f) player->crosspossum[i] = x / (1.0f - crossdamp);
if (aimdamp   < 1.0f) player->crosssum2[i]   = x / (1.0f - aimdamp);
```

**Two pairs, two different damps, same `x`** — which is precisely what `163` §5
built and why the damp must not be shared. **INDEPENDENT CONFIRMATION.**

## 8.4 AND THEY CLAMP THE DRAWN CROSSHAIR ONLY

`bondgun.c:8419-8422` clamps `crosspos` to `[3, w-4]` **after** the sums are
loaded — the integrators keep the true aim. **That is P1-5, and `163` §10 already
noted GoldenEye ships half of it: `field_FFC` is unclamped in stock code.**

## 8.5 ►►►► WHY WE CANNOT SIMPLY COPY THE LASER: PD ALREADY HAD ONE. ◄◄◄◄

`lasersightSetBeam()` / `lasersightSetDot()` (`bondgun.c:10251-10258`) are
**Perfect Dark's OWN pre-existing laser-sight subsystem** — the Falcon 2 with
laser sight is a stock PD weapon. Their VR work only had to **re-point** it.

**GOLDENEYE HAS NO SUCH SUBSYSTEM.** §5.1's `BeamRecord` is a bullet-tracer
beam, not a sight, and §5.2's five unreachable symbols stand. **This is the
THIRD PD feature to fail transfer** after `155`'s post-rotation and `163` §7's
muzzle model part — **and the reason is the same every time: PD's VR build
inherits a richer base game.**

**BUT `VrlaserDotForALL` (`bondgun.c:10285`) IS WORTH RECORDING** — PD themselves
added a flag to give the laser dot to weapons that have no laser sight, because
it is that much better as an aiming reference. **The owner asking for "a laser
for testing (or an option)" is asking for the same flag PD found they needed.**

## 8.6 THE ORDER THIS CHANGES

**PD says the cheapest correct fix is NOT the laser — it is the PROJECTION.**
Project a **world point** through the **render's own matrix**, exactly as
`bondgun.c:8390` does. GoldenEye has both halves already:
`camGetWorldToScreenMtxf()` (used at `gunfire.c:1129`) and
`currentPlayerGetViewToWorldMtxf()` (used at `gunfire.c:757`).

**DO §7.1 (THE FOV) FIRST. It is small, it fixes the crosshair position, the
elevation drift AND the world-scale compensation in one change** — and PD's
design says the laser is the *nicety* on top, not the prerequisite.
