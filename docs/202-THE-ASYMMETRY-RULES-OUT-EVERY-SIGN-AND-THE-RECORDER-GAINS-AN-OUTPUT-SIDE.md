# 202 — `G-201` PASSED. THE REMAINING FAULT IS ASYMMETRIC, WHICH RULES OUT EVERY SIGN AND MIRROR.

**2026-08-25. Tiers per `182`.**

---

## §1 — TWO PASSES, AND ONE OF THEM WAS MISTAKEN FOR A FAULT

> `[REPORTED]`: ***"When you turn your head, the gun does not move."***

**`G-201` PASSES. `163`'s second driver was the yaw.** The seam was already
measured clean (`200`: 0.14 deg over 83 head-only transitions) and the head was
re-aiming the model through `field_FFC` instead.

> `[REPORTED]`: ***"I was wondering if the crosshair affected the direction of the
> gun, it didn't."***

**THAT IS `201` WORKING, NOT A FAULT** — and it was reported as *"being weird"*,
which is fair, because **it is the first build in this project's history in which
the gun's orientation is independent of the crosshair.** `201` §2 predicted
exactly this and said the crosshair would keep moving on its own. **Recorded here
so it is not filed as a regression by a later session.**

> `[REPORTED]`: ***"my hand/gun and aimer going through geometry."***

**NOT A FRAME BUG. `169` U-23**, filed rather than chased: a viewmodel has no
collision, every shooter of the era draws it that way, and **it only reads as a
defect in VR because you can physically put your hand inside a wall.**

---

## §2 — ►►►► THE ASYMMETRY IS THE FINDING ◄◄◄◄

> `[REPORTED]`: ***"if I go to the right and just keep going to the right, it's
> fine. If I start going to the left, it starts lifting upwards... if I wanna go
> up to the top left, it almost looks like I'm aiming to the right with my left
> arm."***

**RIGHT SIDE CORRECT, LEFT SIDE WRONG, WITH YAW LEAKING INTO PITCH.**

> ### **NO SIGN AND NO MIRROR CAN PRODUCE THAT.**
> `-HandAxis*` applies `R[i][j] *= sgn[i]*sgn[j]`, a conjugation, and every such
> transform is **symmetric about the identity** — whatever it does turning right
> it does equally turning left. **`[MEASURED]` in the sweep, the wearer's wrist
> covered the FULL `-179.6` to `+179.7` degrees of yaw**, so the asymmetry is not
> a range artefact either. **THE SIGN SWEEP IS THEREFORE CLOSED WITHOUT RUNNING
> THE REMAINING COMBINATIONS** — a result, not a gap.

**AND ONE HONEST LIMIT, `[MEASURED]`:** pitch reached **`-83.0` degrees**, within
seven of straight down, and the yaw/pitch correlation over the sweep was
**`r = -0.34`**. **The wearer's own arm coupled yaw into pitch** — you cannot take
a right arm across to the left shoulder without rolling and pitching it. **So the
log cannot separate "the gun coupled the axes" from "the arm did", and this
document does not claim it can.**

---

## §3 — WHY `199`'s RECORDER CANNOT CLOSE THIS, AND WHAT IT NEEDS

**`199` §2 logs the INPUTS ONLY, deliberately** — *"a recorder that logs a DERIVED
value can be wrong in the same way the code is wrong"* — **and that discipline is
exactly what made `200`'s answer trustworthy at thirty to one.**

**IT IS ALSO WHY IT IS BLIND HERE.** The inputs say precisely what the hand did.
**They say nothing about what the game DREW**, and §2 has just established the
fault lives in how the game CONSUMES the matrix.

**`202` ADDS THE OTHER END OF THE SAME WIRE — `POSEOUT`:**

```
[gevr] POSEOUT rr=(x y z) rc=(x y z) root=(x y z) want=(x y z)
```

| term | why it is there |
|---|---|
| **`rr`** | `R`'s third ROW as a barrel axis |
| **`rc`** | `R`'s third COLUMN as a barrel axis. **`158` §2 established that BOTH are plausible** depending on whether `R` maps gun-local->head or head->gun, published both, and let one run pick. **The same ambiguity is live again in the solved frame and is settled the same way.** |
| **`root`** | `g_geVrLastRoot` — the placement **the game itself produced** this frame (`83`). **Without it there is no separating our contribution from the game's**, which is the confusion `85` spent a session inside. |
| **`want`** | what we hand it, for the pair |

**Rate-limited with `POSEREC` so the two lines stay adjacent and pair by
position rather than by timestamp.** Host-side, **ONE BUILD**, no new symbols.

---

## §4 — THE RUN, AND IT IS THE SAME SWEEP AGAIN

**Standing command, unchanged from `201` §4.** Then **repeat exactly the sweep
just described** — out in front, yaw all the way RIGHT, back to centre, all the
way LEFT, then up to the top-left where it inverts, plus a wrist roll each way.
**Say the marks out loud. The right-hand half is the CONTROL: it is reported
correct, so it is the reference the broken half is measured against.**

**Then `Copy-Item .\gevr.log .\gevr-keep-POSEOUT.log` and send it.**

---

## §5 — WHAT IS OWED

1. **BUILD ONCE. RUN §4's SWEEP. SEND THE LOG.**
2. **SOLVE THE CONSUMING FRAME OFFLINE** — row vs column first, then the
   remaining mapping, against the correct right-hand half.
3. **THEN THE POSE PASS** (`-GunOffY`/`-GunOffZ`/`-ViewmodelScale`), knob-only.
4. **THEN `G-194`, `B1`.** The FOV/scale read (`199` §4) is still owed and
   independent of all of this.

**NOTHING STAGED. THE COMMIT IS THE OWNER'S**, both repos.
