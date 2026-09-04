# 145 — A STOPWATCH BEAT EVERY INSTRUMENT, AND BOND'S WALK IS FRAME-RATE DEPENDENT BY CONSTRUCTION.

**2026-08-24, late.** The owner timed a run from the level start to the barrels,
three configurations, same route.

| Run | Config | Time |
|---|---|---|
| 1 | stock 60 | **29.48 s** *(hesitated when the truck came by)* |
| 2 | `-ViRate 90` (RB-02) | **27.04 s** |
| 3 | `-ViRate 90 -FloatDelta` (RB-03) | **18.18 s** |

> ## **27.04 / 18.18 = 1.487. THAT IS 90/60 TO WITHIN STOPWATCH ERROR.**
>
> **RB-03 MAKES BOND EXACTLY 1.5x TOO FAST. RB-02 DOES NOT** — run 1's extra
> 2.4 s is the truck hesitation the owner flagged, so stock and RB-02 agree.

**Three purpose-built instruments failed tonight and a stopwatch and a corridor
settled it in three runs.** `48` rule 9's real lesson, again.

---

## §1 — EVERY DIVIDE-BY-DELTA IN THE TREE IS RULED OUT

`144` §2 blamed the guarded divides. **All 44 `/ g_GlobalTimerDelta` sites in the
game were then listed.** Every one is tank movement, tank turret, thrown
objects, launch velocity, shell casings, truck angular velocity, or the
front-end cast animation.

> **NOT ONE OF THEM IS BOND'S WALKING SPEED. `144` §2 IS DEAD — THE THIRD
> MECHANISM I HAVE PROPOSED FOR THIS SYMPTOM AND THE THIRD ONE WRONG**
> (`132` §3, `144` §2, and `144` §4.2's `speedverta`).

**Not writing the fix when it was asked for was the right call**, and it was the
owner's own description — *"walking / running speed"* — that killed it.

---

## §2 — WHAT ACTUALLY MOVES BOND, AND WHY IT SCALES WITH FRAME RATE

`bondview2.c`, inside `MoveBond`:

```c
ftemp_26 = -swaytarget * theta_transform.f[2];      /* :7149 the TARGET      */
ftemp_11 =  swaytarget * theta_transform.f[0];
sp220    = ftemp_26 - swayoffset0;                  /* :7152 the ERROR       */
sp21C    = ftemp_11 - swayoffset2;
...
move_offset.f[0] += sp220;                          /* :7237 NO DELTA        */
move_offset.f[2] += sp21C;
...
swayoffset0 += sp240 * sp220;                       /* :7411 sp240 = the     */
swayoffset2 += sp240 * sp21C;                       /*   COLLISION RATIO     */
```

> ## **BOND'S WALK IS AN EXPONENTIAL APPROACH TOWARDS A TARGET, ADVANCED ONCE PER FRAME, WITH NO TIMESTEP ANYWHERE IN THE LOOP.**

`sp240` is not a time — it is the fraction of the attempted step that the
collision solver actually delivered. **So the convergence rate is measured in
FRAMES, not in seconds.** Run the loop 90 times a second instead of 60 and Bond
closes on his target 1.5x faster. **The 1.487 is not a bug in RB-03; it is this
loop meeting a higher frame rate.**

**AND IT IS THE ONLY UNSCALED DISPLACEMENT TERM IN THE ON-FOOT PATH.** Every
other contribution — the head-relative terms at `:7228`/`:7234`, the tank terms,
the debug-fast-bond term — carries `* g_GlobalTimerDelta` and sums correctly.

---

## §3 — THE ONE FACT STILL MISSING, AND IT IS WORTH NAMING HONESTLY

**If this loop simply runs per frame, RB-02 should be 1.5x too — and it is
not.** So `MoveBond` must be reached 60 times a second under RB-02 and 90 times
a second under RB-03, and **nothing found so far explains why.** There is no
`g_GlobalTimerDelta != 0` gate on the path; the only two in the tree are
`bondview2.c:7057` (EU-only) and `propobj.c:5594` (the truck).

**The measurement that would close it is one counter: `MoveBond` executions per
second, in each configuration.** `bondviewCalcUpdatePlayerCollision` is called
once per `MoveBond` and is 200 lines — patchable, but it is the collision core
and `142` is a fresh reminder of what happens when something load-bearing is
touched mid-investigation.

**IT IS NOT WRITTEN, AND THE REASON IS §4.**

---

## §4 — THE STRATEGIC READ: RB-02 IS THE DELIVERABLE. RB-03 PROBABLY IS NOT.

**RB-02 IS DONE, CORRECT AND MEASURED:**

- **89 fps**, ninety real frames a second, no interpolator manufacturing thirty.
- **Clock exact** — `per1000ms=60` across 138 samples.
- **Bond's speed correct** — 27.04 s against stock's 27-ish.
- **Audio correct, pause correct, stable, a mission plays.**
- **`dupSrc`'s 30/90 duplicate frame, the per-pass pose machinery and the
  interpolated-frame artefacts are all deleted** — `126`'s promise, delivered.

**RB-03 is a different proposition than `132` assumed.** Its purpose was smoother
sub-tick motion. But §2 shows the engine's own movement is **structurally
frame-rate dependent** — a per-frame convergence loop with no timestep — so a
finer delta does not make it smoother, it makes it *faster*. **Fixing that means
putting a timestep into `MoveBond`, a 1307-line function, and changing the feel
of Bond's movement in ways nobody asked for.** `118` §4's principle applies with
force: **leave the thing that decides feel alone.**

> ### **RECOMMENDATION: SHIP RB-02. LEAVE `-FloatDelta` OFF BY DEFAULT — IT ALREADY IS — AND TREAT RB-03 AS PARKED RATHER THAN OWED.**
>
> **The owner reached the same conclusion from the chair before any of this was
> read:** *"It's a fun way to play but not for VR."*

**WHAT REMAINS OPEN AND IS WORTH MORE THAN RB-03:** the world still animates in
60 discrete steps while rendering at 90. **Whether that is visible in a headset
is RB-07, and it is the question this whole route exists to answer.**
