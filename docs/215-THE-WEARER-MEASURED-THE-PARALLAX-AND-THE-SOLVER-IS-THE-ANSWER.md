# 215 — THE WEARER MEASURED THE PARALLAX WITHOUT AN INSTRUMENT. AND `210` UNFUSED THE SIGHT.

**2026-08-26. Tiers per `182`. `[INFERRED]` carries its counter-example search
(`209` §4.3).**

---

## §1 — ►►►► THE MEASUREMENT, AND IT IS THE WHOLE ANSWER ◄◄◄◄

> `[REPORTED]`: ***"at, like, thirty game feet away, it's off that much. So WHERE
> THE GUN WAS HELD AND WHERE THAT RIGHT AIMER IS IS THE EXACT DISTANCE THAT IT'S
> OFF."***

**THE MISS EQUALS THE GUN-TO-CROSSHAIR SEPARATION. AT NINE METRES.**

**THAT IS THE SIGNATURE OF TWO PARALLEL RAYS, AND IT IS DEFINITIVE:**

- **the bullet** leaves the MUZZLE along the barrel (`164`);
- **the crosshair** is the same direction projected FROM THE EYE (`167`);
- **so the two rays are PARALLEL, offset by the muzzle-to-eye vector** — and two
  parallel rays are displaced by that vector **AT EVERY DISTANCE, FOREVER.**

**A CONSTANT LINEAR MISS, EQUAL TO THE MUZZLE OFFSET.** The wearer measured it by
eye, against the gun in his own hand, and named the offset exactly.

> ### AND IT RESOLVES `214` §3's CONTRADICTION.
> `214` §3 recorded two `[REPORTED]` claims that could not both be true: the miss
> shrinking with distance (`210`, `[MEASURED]` at contact range) and the miss
> worsening with distance (`214`). **THE ANSWER IS NEITHER: IT IS CONSTANT IN
> LINEAR TERMS.** Close up that is a huge ANGLE and shrinks as you back away
> (`210`'s reading); far away it is a large ABSOLUTE distance on the target and
> feels worse (`214`'s). **Both reports were honest and both described the same
> constant offset from different ends.**
>
> **COUNTER-EXAMPLE SEARCH (`182` §2):** a rival explanation is a constant ANGULAR
> error, which would give a miss GROWING linearly with distance — at 9 m the
> `4.38 deg` measured in `210` would be **69 cm**, not a gun's length. **Searched
> `193` §1's 55 shots for a distance-independent angular offset and found the
> `tan(dir)/ndc` ratio FLAT across eccentricity.** The angular explanation
> requires a residual nothing has measured; **the parallel-ray one predicts the
> wearer's exact words.**

---

## §2 — SO WHAT FIXES IT: `211`'s SOLVER, AND NOW IT IS CONFIRMED RATHER THAN PROPOSED

**Two parallel rays cannot be reconciled by tuning. They have to be made to
MEET**, and that is exactly what `211` §3 designed:

```
P     = muzzle + dir * zeroDistance   // a point ON the bullet's path
sight = project(P)                    // and THAT is the crosshair
```

**At the zero distance the crosshair and the shot coincide EXACTLY. Either side
they diverge by the muzzle offset over distance — bounded, computable, and
predictable in advance.** Today they never coincide at all.

**THE WEARER'S QUESTION WAS *"what can we map or build that will fix this?"* —
THE ANSWER IS THIS, IT IS ALREADY DESIGNED, AND U-18 (its prerequisite) IS
DONE.**

---

## §3 — AND `210` UNFUSED THE SIGHT. THAT ONE IS MINE.

> `[REPORTED]`: ***"the crosshairs are not syncing again. They're two separate in
> each eye."***

**`[READ]`, and it is a precedence bug I wrote this session:** `210`'s parallax
term **took priority over `-HudDepth`** whenever an impact distance existed. The
wearer had FUSED the crosshair at `-HudDepth 0.2` (`192`), worth **`~0.128` NDC**;
the parallax delivers **`~0.0145`**. **An order of magnitude less convergence,
substituted silently, without the wearer changing a flag.**

**`210` §2 PREDICTED THIS EXACT OUTCOME** — *"if it does not fuse, our depth term
and PD's differ by a large factor and THAT IS THE FINDING"* — **and I still let
the new, untested term win by default over a measured, worn, working one.**

**FIXED: an explicit `-HudDepth` is honoured FIRST. The parallax applies only
when none is set — which is what a fallback is.**

> **THE RULE THIS EARNS:** **a new term must not take precedence over a value the
> wearer has already tuned and confirmed.** `150` H-9 is the same lesson about
> defaults; this is it about precedence.

---

## §4 — TWO MORE, RECORDED AND NOT DIAGNOSED

**3.1 `[REPORTED]` *"shooting closer to the RIGHT EYE's bottom left quadrant."***
**That is `174`'s signature returning** — *"it seems to aim off the right eye"* —
and `174` fixed it by anchoring at the head centre. **`[INFERRED]`: with the
sight unfused (§3), "the right eye's crosshair" is a distinct object again, so
this may be §3's consequence rather than `174` regressing. WHAT WOULD SETTLE IT:
re-check after §3's fix, with the sight fused.** Do not touch `-HeadAnchor` first.

**3.2 `[REPORTED]` *"the longer gun shoots to the right and even shoots
downward."*** **`214` §1's fix — the barrel rotated by the transpose — was built
but NOT YET WORN when this was reported.** It predicts exactly a proportional,
off-axis error on the longer barrel. **Re-judge after the build; if it survives,
`214` §1 is wrong and the node's axis mapping is next.**

---

## §5 — WHAT IS OWED

1. **BUILD ONCE.** Carries `214` §1 (the barrel rotation) and §3 (the precedence).
2. **CONFIRM: the crosshair FUSES again at `-HudDepth 0.2`.** Nothing else is
   judgeable until it does.
3. **THEN `G-213`** — the longer weapon, §3.2.
4. **THEN `211`'s SOLVER.** §1 has now confirmed its premise from the headset.
5. **NOT NEEDED ANY MORE: `214` §4's distance measurement.** §1 answered it — the
   miss is CONSTANT IN LINEAR TERMS, and both prior reports were the same fact
   seen from two ranges.

**NOTHING STAGED. THE COMMIT IS THE OWNER'S.**
