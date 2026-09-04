# 164 — THE SHOT LEAVES THE BARREL, NOT THE EYE. AND THE INSTRUMENT THAT REPORTS IT.

**2026-08-25. BUILT, WORN ONCE (partially — see §5). Written up retroactively at
session close; the code has referenced this number since it was built.**

> ## THE WEARER NAMED THE BUG EXACTLY
>
> ***"it seems like it's only hit points as if I was aiming in a 2D plane... it's
> not shooting in a straight line from the gun's exit hole."***
>
> **THAT IS A GEOMETRY ERROR, NOT TUNING, AND THE PHRASE IS DIAGNOSTIC.**

---

## 1. THE FAULT

`bullet_path_from_screen_center` ends by **unprojecting the crosshair pixel**,
which yields the ray **from the EYE** through that pixel. `157` (A1b) then
replaced the **origin** with the muzzle. So the shot became:

```
origin    = MUZZLE            (docs\157)
direction = EYE -> crosshair  (stock, never changed)
```

**A ray leaving the muzzle PARALLEL to the eye's ray is displaced from the true
barrel line by the eye-to-muzzle offset AT EVERY DISTANCE.** It never converges
on what the crosshair covers. **That is "aiming in a 2D plane pinned to the
screen", exactly.**

## 2. THE FIX

The direction now comes from the **barrel** — the same ray the aim is projected
from — so **origin and direction share one source.** That is the invariant `163`
§6 established for the muzzle, extended to the shot.

## 3. THE SPREAD IS PRESERVED WITH NO NEW CONSTANT

The weapon's inaccuracy is expressed in **pixels**. So: unproject the spread pixel
and the clean pixel, **normalise BOTH to the `z = -1` plane**, and difference
them. That yields the spread as a pure angular offset to add to the barrel ray.

**Both terms come from the game's own inverse projection, so there is no unit
conversion to get wrong and no scale accessor is needed.**

> **NORMALISING BOTH BEFORE DIFFERENCING IS THE PART THAT WOULD HAVE BEEN A BUG.**
> They are unit vectors with DIFFERENT z, so subtracting them directly folds a
> depth difference into the lateral offset.

## 4. THE INSTRUMENT — SO A SHOT CAN BE JUDGED WITHOUT A WEAR TEST

The owner asked for exactly this: *"so you can calculate yourself if a shot was
accurate or not."*

```
[gevr] 6dof: SHOT reported px=(156.4,120.5) ndc=(-0.022,0.005)
             muzzle=(1.5,-8.2,-50.2)u dir=(-0.011,0.011,-1.000)
```

**Impact is `muzzle + dir * t`.** Four numbers, and shot accuracy becomes
arithmetic on the log.

**AND IT REPAIRED AN INSTRUMENT THE PROJECTED PATH HAD BROKEN.**
`g_geVrAimDbgNdc` is written only by `aim_screen_ndc`, so once `163` made
`aim_fwd_head` the default the AIM line reported `ndc=(0,0)` forever — **a real
number replaced by a zero, which is the exact failure `86` wrote S0 to prevent.**
A refused frame and a zero frame look identical in a headset (`48`).

## 5. WHAT THE WORN RUN SHOWED

`px` was verified against `dir` on all 18 distinct shots and **they agree to about
0.01 NDC** — so the projection is self-consistent and **the barrel ray itself is
what is displaced.** That is what isolated `166` §4's seventeen degrees as a
SEPARATE fault, rather than a tuning residue of this one.

## 6. GATES

- **G-164-1** — the shot leaves along the barrel, not parallel to the eye ray.
- **G-164-2** — weapon spread is unchanged in feel; no new constant was
  introduced to achieve it.
- **G-164-3** — the SHOT line reports non-zero `muzzle` and `dir` whenever a shot
  is fired, and `n/a(no-shot-path-yet)` when none has been.

## 7. THE CONSEQUENCE, PRE-REGISTERED

**With the shot leaving the barrel, the crosshair and the impact point WILL
disagree at close range.** That is real gun geometry, **not a regression**, and it
is what `161` P1-6 / `169` U-06 exist to solve.
