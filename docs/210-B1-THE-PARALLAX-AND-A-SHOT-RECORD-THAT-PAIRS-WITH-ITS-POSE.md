# 210 — `B1`/U-06: THE CROSSHAIR CONVERGES AT THE LAST IMPACT. AND THE SHOT RECORD FINALLY PAIRS WITH ITS POSE.

**2026-08-26. Tiers per `182`. `[INFERRED]` claims carry their counter-example
search — `209` §4.3, first document under the new rule. BUILT, UNRUN.**

---

## §1 — WHAT IT FIXES, AND IT IS `[MEASURED]`

**`193` §2, 55 logged shots: the bullet leaves a point `0.19`-`0.61 m` from the
eye, wandering ~0.4 m laterally, while the crosshair is drawn FROM the eye.**
**Two rays with the same direction and different origins never meet** — they
agree at exactly one distance and diverge either side of it. `185` `B1`: *"inside
it you miss one way, outside the other."*

**`193` §1 already excluded the alternative:** the crosshair and the bullet agree
with the render frustum to within half a per cent, flat across eccentricity.
**The direction is right. Only the origins differ.**

---

## §2 — THE IMPLEMENTATION, AND THE THREE THINGS TAKEN FROM PD

**`[READ]` PD's `vrComputeCrosshairParallax`, `port/vr/vr_openxr.cpp:2397`, 25
lines. Structurally it is the SAME expression as our existing `-HudDepth` term**
(`ge_vr_hud_offset_ndc`) — `(halfIpd / distance) / tanHalfWidth`. **`168`'s rule
holds: the DESIGN transferred, and there was no subsystem to call into.**

**PD have three things we did not, and all three are kept:**

| | why |
|---|---|
| **a 1.75 m FLOOR** | closer than that the term runs away, and a wall you are standing against must not swing the sight |
| **NOMINAL-RELATIVE** | the correction is the DIFFERENCE from the floor, not the absolute convergence — so "no impact yet" and "an impact at the floor distance" agree instead of jumping |
| **a `+-0.02` NDC CLAMP** | |

### ►► AND KEEPING THE CLAMP IS A TEST, NOT A COPIED CONSTANT ◄◄

**`[REPORTED]` the wearer fused the crosshair at `-HudDepth 0.2`. `[MEASURED]`
this file's own term computes that as `~0.128` NDC — SIX TIMES PD's maximum
correction.** `192` §1 already flagged that `0.2 m` is **nearer than the gun** and
tiered it as needing `B1` to resolve.

**IF THE PARALLAX ALONE FUSES THE SIGHT, that discrepancy WAS the missing depth.
IF IT DOES NOT, our depth term and PD's differ by a large factor and THAT IS THE
FINDING — do not widen the clamp to chase it.**

**`168` §5's GREP, RUN FIRST: `item_related` is a `coord3d` at `structs.h:1795`
and `struct player` carries `pos` at `:1879`. BOTH REACHABLE. `sqrtf` is already
used in this file.** One new patch->host symbol (`recomp_ge_vr_impact_dist`,
`0x8F00016C`) — **so BUILD TWICE** (`136`).

**THE DISTANCE IS PUBLISHED PER FRAME from the crosshair update**, not per shot:
the crosshair must converge continuously, and `caclulate_gun_crosshair_position_rotation`
is the per-frame path. **A zero distance means "nothing has landed yet" and the
host falls back to the fixed `-HudDepth`** rather than inventing one (`48`).

---

## §3 — THE SHOT RECORD, AND IT CAME FROM THE OWNER'S SUGGESTION

**`[REPORTED]` the owner brought a suggestion recommending a per-shot telemetry
harness logging the head pose, controller pose, muzzle world position, aim ray
and the engine's raycast input SIDE BY SIDE.**

**MOST OF IT WE ALREADY HAD** — `199`'s `POSEREC`, `202`'s `POSEOUT` and `164`'s
`SHOT` line — **but it named a real gap: `SHOT` is printed ONCE PER SECOND from
the summary block, and the poses are logged at 9 Hz. NEITHER IS SYNCHRONISED TO
THE SHOT**, so a shot cannot be paired with the pose that produced it.

**`SHOTREC` is emitted INSIDE `aim_report`, in the fire path**, so every value is
from the same instant by construction rather than by timestamp matching:

```
[gevr] SHOTREC px=() ndc=() muzzle=()u dir=() hq=() hp=() gq=() gp=() impact=u
```

**HOST-SIDE, NO NEW SYMBOLS** — `head_view()` and `controller_input()` are
already in scope there. **And `199` §2's rule still holds: the poses are the RAW
runtime ones, so the record cannot be wrong in the same way the code is wrong.**

> **WHERE THE SUGGESTION WAS WRONG, AND IT IS WORTH RECORDING:** it named
> `bondgun.c`, `weapon.c`, `bullet.c`, `game_0147a0.c`, `bgun.c` and the functions
> `bulletCreate`, `fireBullet`, `bgunSwivel`. **`[READ]`: FIVE OF THE SIX FILES DO
> NOT EXIST in `lib\ge\src\game`, and ALL THREE FUNCTIONS RETURN ZERO HITS.**
> They are Perfect Dark's names. **That is exactly `168`'s rule — search for the
> mechanism, never for PD's identifier — which `163` §7 learned by concluding
> GoldenEye had no muzzle node.** It also described the camera-centric trajectory
> as the live fault; **`157` and `164` closed that, and `193` §1 measured it
> closed.**

---

## §4 — `G-210`, AND THE PROTOCOL COMES FROM THE SUGGESTION TOO

**TWO RUNS, ONE BUILD. The known-angle discipline is the suggestion's, and it is
better than what this project has been doing for shots.**

**RUN 1 — BASELINE, `-NoParallax`.** **RUN 2 — the same, without it.**

In each, fire **three shots at known angles: STRAIGHT AHEAD, 45 DEGREES UP, and
90 DEGREES RIGHT** — and separately, **a NEAR wall and a FAR wall.**

- **`G-210` PASSES** if the miss shrinks toward zero at BOTH distances in run 2,
  instead of being right at one distance and wrong at the other.
- **`[ASSUMED]`, AND IT IS THE ONLY ASSUMPTION HERE:** that one landed shot is
  enough to converge. **The FIRST shot of any run uses the fallback** because
  `item_related` has not been written yet — **by design (`185` `B1`), and it must
  not be read as a failure.**

**COUNTER-EXAMPLE SEARCH (`182` §3, and `209` §4.3 now requires it):** the claim
that the ORIGIN offset explains the miss would be falsified by a run in which the
miss holds its ANGULAR size across distance. **`193` §1's 55 shots were searched
for exactly that: the `tan(dir)/ndc` ratio was FLAT across eccentricity
(X 1.183 near centre vs 1.317 off, against a 0.23 spread from the game's own
random spread), so no constant angular error was found.** **`T7` in the headset
remains the check that could still produce one.**

---

## §5 — WHAT IS OWED

1. **BUILD TWICE. RUN 1 (`-NoParallax`), RUN 2 (default).** Three known angles
   plus near/far wall in each. **Send the log** — `SHOTREC` makes it solvable
   offline.
2. **THEN `U-18`**, the per-weapon muzzle (`T2` PASSED, `193` §3) — **and its own
   counter-example search is still owed** (`209` §4.1).
3. **THE SCALE at 25** (`205` §4: both numbers together, judged against a guard).
4. **THE COMMIT — twenty-five documents overdue, both repos.**

**NOTHING STAGED. THE COMMIT IS THE OWNER'S.**
