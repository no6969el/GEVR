# 222 — TWO SMALL INSTRUMENTS: `noPose`, AND THE ASPECT THAT MAY BE THE "SKINNIER".

**2026-08-26. Tiers per `182`. BUILT, UNRUN. Both ride `221`'s build.**

---

## §1 — `noPose`: THE FRAMES NEITHER COUNTER COULD SEE

**`[READ]`, and `190` §3 flagged it as owed:** `aimed` and `refused` are BOTH
incremented **inside** the `geVrAimFwdHead()` branch. **So a frame where the
controller lost tracking is counted in NEITHER, and `aimed + refused` is not the
frame count.**

**A TRACKING DROPOUT WAS INVISIBLE IN THE ONE INSTRUMENT BUILT TO MEASURE THE
AIM** — and `189` §1 read a frozen `aimed` beside a climbing `refused` as *idle*,
when a long dropout would look almost identical. **That reading happened to be
right; nothing in the log made it so.**

```
[gevr] A1-VERIFY: ... CONE= coneOff= noPose= | maxNx= ...
```

**`noPose + aimed + refused` is now the whole frame count.** `noPose` large beside
a frozen `aimed` means **tracking was lost**, not that the wearer stood still.

**Patch-side, no new symbols.**

---

## §2 — THE ASPECT: "SKINNIER" IS NOT A SCALE WORD

**`[REPORTED]` the guard reads *"smaller and SKINNIER"* while the gun looks
LARGER. `213` §2.2 named the only horizontal-only term in the chain:**

```c
[READ] bondview.c:657
  c_scalex = (c_scaley * c_perspaspect * c_halfheight) / c_halfwidth
```

**and `167` established `c_scalex`/`c_scaley` are NEVER rebuilt from the headset
tangents.**

> **A SCALE ERROR MAKES THINGS SMALL IN BOTH AXES. AN ASPECT ERROR MAKES THEM
> NARROW.** Different faults, different cures — **and no number in this log has
> ever separated them.** `185` `A2`'s standard was *"a number, not an
> impression"*, and the scale question has been running on impressions since
> `159`.

```
[gevr] 6dof-game: ASPECT perspaspect=N halfw=N halfh=N | game x/y=N[x1000]
```

**Printed so the game's own x/y ratio can be compared against the RENDER's
half-tangents on the host line.** If they disagree, **that ratio IS the
skinniness.**

### AND `168` §5's GREP EARNED ITS KEEP AGAIN, IN SECONDS

**`getPlayer_c_perspaspect` is NOT in `externs.h`.** The first draft called it.
**It did not need to: `c_perspaspect`, `c_scalex` and `c_scaley` are all PLAYER
STRUCT FIELDS** (`structs.h:2615/2630/2635`), so the accessor was never the only
route. **`157` withdrew a whole slice for want of eight symbols; this cost one
grep.**

---

## §3 — WHAT IS OWED

1. **Both ride `221`'s build. Nothing extra to do.**
2. **READ `noPose` on the next aim log** — if it is large, previous `A1-VERIFY`
   readings were taken across dropouts and are weaker than they looked.
3. **READ `ASPECT` and compare `game x/y` against the render's.** If they differ,
   the scale hunt splits in two and **the aspect half is a separate, smaller
   problem** — one that `159`, `166` and `205` have all been fighting blind.

**NOTHING STAGED. THE COMMIT IS THE OWNER'S.**
