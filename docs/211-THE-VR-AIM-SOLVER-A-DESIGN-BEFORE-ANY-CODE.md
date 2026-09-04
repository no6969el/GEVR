# 211 — THE VR AIM SOLVER. A DESIGN, WRITTEN BEFORE ANY CODE.

**2026-08-26. Tiers per `182`. `[INFERRED]` claims carry their counter-example
search (`209` §4.3). NOTHING IS BUILT. This document exists to be argued with.**

**Owner's decision, verbatim:** *"if you had a choice to keep troubleshooting this
way or just rebuild the code to match Perfect Dark... what about the idea of maybe
just creating the parts that are missing... We're trying to get this done. I don't
care if it takes longer."*

---

## §1 — THE THREE ROUTES, AND WHY THIS ONE

| route | verdict |
|---|---|
| **Rebuild to match PD's architecture** | **RULED OUT.** `168`'s rule, learned three times: the constants and designs transfer, THE SUBSYSTEMS DO NOT. PD edit `bgunSwivel` from INSIDE the engine where `camGetWorldToScreenMtxf()` is in scope; we compute in RT64 where it is not. `155`, `163` §7 and `166` §8.5 all died calling into PD features GoldenEye lacks — and `210` §3 records the same trap arriving again from outside |
| **More term-by-term troubleshooting** | **RULED OUT IN THIS SHAPE.** Not because it fails — `200` and `203` each solved a question in ONE recording — but because **five knobs now move the same crosshair** (`-HudDepth`, the per-eye shift, the parallax, `-AimTrim*`, `-GunOff*`), each tuned against a different broken assumption, and they fight |
| **BUILD THE MISSING PART AS ONE COHERENT PIECE** | **CHOSEN** |

> **WHY IT IS TRACTABLE NOW AND WAS NOT YESTERDAY: THE TWO GENUINE UNKNOWNS ARE
> CLOSED.** `204` solved the frame — `[MEASURED]`, 744 poses — so controller space
> maps to game space with no free parameters. `193` §1 measured the projection
> innocent across 55 shots. **WHAT REMAINS IS ARITHMETIC OVER MEASURED INPUTS.**

---

## §2 — THE FAULT, STATED ONCE, PROPERLY

**THE CROSSHAIR IS DRAWN WHERE THE EYE RAY GOES. THE BULLET LEAVES FROM THE
MUZZLE.** `[MEASURED]` `210`: the muzzle sits at **`(-3.0, -8.1, -9.7)` cm** from
the camera — **8 cm BELOW the eye.** Two parallel rays from origins 8 cm apart
**never meet**, so the crosshair is wrong at every distance except one.

**`[MEASURED]` at contact range**, the wearer's miss-then-hit pair:
**4.38 degrees** (yaw `+3.84`, pitch `-2.23`). Against the offset's own subtense:

| offset | at 1.0 m | at 1.5 m | at 43 m |
|---|---|---|---|
| lateral 3.1 cm | 1.8 deg | 1.2 deg | 0.04 deg |
| **vertical 8.1 cm** | **4.6 deg** | **3.1 deg** | 0.11 deg |

**SAME ORDER AS THE MEASURED MISS, AND THE VERTICAL TERM DOMINATES.**

> **COUNTER-EXAMPLE SEARCH (`182` §3, `209` §4.3):** the rival explanation is a
> constant ANGULAR error in the ray, which would NOT shrink with distance.
> **Searched: `193` §1's 55 shots for a distance-independent angular offset. The
> `tan(dir)/ndc` ratio was FLAT across eccentricity (X 1.183 near centre vs 1.317
> off, inside the 0.23 spread the game's own randomness produces), so no constant
> angular error was found.** And the miss is `[REPORTED]` large at contact range
> and was not reported at corridor range. **The origin explanation survives; the
> angular one does not.** `T7` in the headset can still overturn this.

**AND `210` FOUND THE PARALLAX PATCH CANNOT CURE IT, FOR THREE MEASURED
REASONS:** the distance fed in was stale (`626 m` while the guard was at arm's
length); PD's `1.75 m` floor zeroes the correction at contact range; and **the
correction is horizontal-only while the dominant offset is VERTICAL.**

---

## §3 — THE DESIGN

> ## **ONE RULE: THE CROSSHAIR IS DRAWN WHERE THE BULLET GOES. NOT WHERE THE EYE LOOKS.**

**INPUTS — all `[MEASURED]` or `[READ]`, none tuned:**

| input | source |
|---|---|
| muzzle position, camera frame | `U-18`'s per-weapon node — `Switches[3]`, `[MEASURED]` 2:1 between weapons (`T2`) |
| barrel direction | the raw pose, `204`'s solved frame |
| render frustum tangents | `167`, live from the headset |
| screen rect and origin | `[MEASURED]` `320x220`, `origin=(0,10)` |
| **the ZERO distance** | **one constant. See below** |

**THE COMPUTATION, IN THREE LINES:**

```
P     = muzzle + dir * zeroDistance      // a point on the BULLET's path
ndc   = project(P)                       // the render frustum, docs\167
sight = ndc -> pixels                    // and this IS the crosshair
```

**The bullet is unchanged** — it leaves the muzzle along `dir` (`164`), which
`193` §1 measured correct. **So the crosshair and the shot agree EXACTLY at the
zero distance and diverge either side of it by the muzzle offset over distance —
a bounded, computable quantity instead of a mystery.**

**AND THE CONVERGENCE FALLS OUT OF THE SAME POINT.** `P` has a depth; the per-eye
shift derives from it. **`-HudDepth` and `210`'s parallax term are both
SUBSUMED** — one number, one place, `48` rule 8.

### ►► THE ZERO DISTANCE IS THE ONE HONEST CHOICE IN THIS DESIGN ◄◄

**A distance is UNAVOIDABLE and this document will not pretend otherwise:** two
non-parallel screen mappings cannot be reconciled without one. The candidates:

| source | status |
|---|---|
| a live trace to what you are aiming at | **BLOCKED.** `185` `B3`: GoldenEye's trace lives inside `chraiDefaultWeaponFireHandler`, entangled with damage and explosions, **not in `externs.h`** |
| the last impact (`item_related`) | **REAL BUT STALE** — `[MEASURED]` `626 m` while the target was at arm's length |
| **A CHOSEN ZERO, like a rifle's** | **CHOSEN.** The error is zero at that range and bounded and KNOWN everywhere else |

**`-AimZero`, default `[ASSUMED]` 5 m, and what would settle it is one wear
session sweeping it.** At a 5 m zero the residual from an 8 cm offset is **+8 cm
at 1 m and -8 cm at infinity** — under half a degree beyond 10 m, and at contact
range it replaces a `4.4 degree` miss with a hand's width. **The last impact can
REFINE the zero later; it must not BE the zero.**

---

## §4 — WHAT IT DELETES, AND THAT IS THE POINT

**`A2`'s ten pixels · the parallax term · the vertical 8 cm · `-HudDepth 0.2`'s
`[MEASURED]` six-times-PD discrepancy (`210` §2) · `-AimTrim*`, which `174` said
in advance "IS EXPECTED TO BE DELETED" · and the per-weapon muzzle question.**
**Five knobs and four open questions collapse into one computation with ONE free
parameter.** `163` deleted five knobs the same way, by finding the game's own
projector instead of estimating it.

**Every knob stays as an off switch** (`00-START-HERE`: DELETE NOTHING).

---

## §5 — GATES

- **`G-211-1` THE ZERO.** At the zero distance the crosshair and the impact
  coincide. **A number, not an impression** — `SHOTREC` gives both.
- **`G-211-2` THE LADDER.** At 1 m and at 40 m the miss is **bounded and in the
  PREDICTED direction and magnitude**. Predicted before the run, from the muzzle
  offset and the zero. **A miss that does NOT match the prediction falsifies §2.**
- **`G-211-3` FUSION.** One crosshair, without `-HudDepth`.
- **`G-211-4` NO REGRESSION** on `204`'s seam: head turns do not re-aim, wrist
  rolls in place, walking is stable.

---

## §6 — THE RISK, AND THE ORDER

**THE RISK IS REAL AND IS THE OPPOSITE OF THIS PROJECT'S USUAL DISCIPLINE: one
change that touches everything, so if it is wrong it is wrong everywhere at
once.** Mitigations: **`-NoAimSolver` reverts to today entirely**, and the first
run is a straight A/B.

**THE ORDER:**
1. **`U-18` FIRST — the per-weapon muzzle.** `T2` PASSED; the node is `[MEASURED]`
   and reachable. **It removes the last tuned input**, exactly as `163` removed
   five by finding the projector. **Its own counter-example search is still owed**
   (`209` §4.1).
2. **THEN THE SOLVER**, ~150 lines, host-side plus one publish, **no new game
   symbols.**
3. **THEN the gates**, in `G-211-1` order.

**AND THE SCALE IS A SEPARATE PROBLEM.** `[REPORTED]` the guard reads *"smaller
and skinnier"* and the gun larger. **"Skinny" is an ASPECT word, not a scale
word** — it belongs with `205`'s calibration and the FOV, **not folded into this**.

**NOTHING STAGED. THE COMMIT IS THE OWNER'S.**
