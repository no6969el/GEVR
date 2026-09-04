# 189 — THE CONE ENGAGED ON EVERY BAND FRAME. `A2` IS CLOSED — IT WAS NEVER A FAULT. AND ONE GATE I WROTE WRONG.

**2026-08-25, the run after `188`'s build. Tiers per `182`.**
**`[MEASURED]` from `gevr.log` around :63689-:63994, three consecutive prints.**

```
[gevr] A1-VERIFY: aimed=7614 refused=1690 | INSIDE=5159 BAND=2455 SAT=1447 noFrus=0
       | CONE=2455 coneOff=0 | maxNx=15398 maxNy=20622
       | lastNdc=(1268,20427) lastFwd=(-431,-901,32) x1000
[gevr] 6dof-game: WIDE-frustum ... screen=320x220 fovy=106 znear=2
       origin=(0,10) centre-should-be=(160,120)
```

---

## §0 — WHAT THIS RUN SETTLES, AND WHAT IT DOES NOT

| | |
|---|---|
| **`A2`** | **CLOSED. NOT A FAULT.** `[MEASURED]` | §2 |
| **The cone clamp ENGAGES** | **`[MEASURED]`: on every band frame, `CONE=2455=BAND`** | §1 |
| **The cone clamp HELPS** | **NOT ESTABLISHED BY THIS LOG. `G-A1` is a WEAR observation** | §1 |
| **`noFrus=0`** | the run is evidence — `186` §3's lie-guard did not fire | |
| **`SAT` "must fall to zero"** | **THAT GATE WAS WRONG WHEN I WROTE IT** | §3 |

---

## §1 — ►► THE CLAMP RAN, ON EXACTLY THE FRAMES THAT NEEDED IT — AND THAT IS ENGAGEMENT, NOT EFFECT. ◄◄

**`[MEASURED]`: `CONE=2455`, `BAND=2455`, `coneOff=0`.** The clamp was active
(the knob was not passed) and it bound at least one axis on **every single frame
whose unbounded projection left the frustum.** `188` §2's failure mode —
*"`BAND` large with `CONE` 0 -> the fix is INERT, and without this counter it
would look identical to success"* — **is excluded.**

> ### AND NOW THE HONEST PART, BECAUSE THIS PROJECT HAS PROMOTED A CLAIM FOUR TIMES ALREADY (`182`).
>
> **`CONE == BAND` IS AN IDENTITY, NOT A RESULT.** `BAND` counts
> `|rawNx| > 1 || |rawNy| > 1`. The clamp fires exactly when `rX` or `rY` leaves
> `c +- h`, **which is the same predicate.** The two counters were always going to
> be equal whenever the code ran at all.
>
> **SO WHAT IT PROVES IS: THE CODE IS REACHED, THE KNOB IS ON, AND NO FRAME THAT
> NEEDED BOUNDING WAS MISSED.** That is worth having and it is all it is.
> **IT SAYS NOTHING ABOUT WHETHER AIMING IS BETTER.** `G-A1` — continuous travel
> to the edge, a clean stop, and the two axes saturating INDEPENDENTLY on a
> diagonal — **is a WEARER observation and the log cannot substitute for it.**
> `48`: wear it before you believe it.

**AND THE BAND IS UNCHANGED ON PURPOSE:** `BAND=2455` of `aimed=7614` (32%)
against `187`'s `2846` of `8548` (33%). **These are the PRE-cone figures**
(`188` §2), so they SHOULD hold — they are the before-figure, and a fall would
have meant the instrument had been moved behind the fix. It was not.

**THE TAIL OF THE RUN IS IDLE, NOT BROKEN.** Across the three prints `aimed`,
`INSIDE`, `BAND`, `SAT`, `CONE` and `maxN*` are all frozen while `refused` climbs
`1630 -> 1660 -> 1690`. **`lastFwd=(-431,-901,32)` says why: `fwd[2]` is `+0.032`
— the gun is pointing DOWN and slightly BACK**, which the `fwd[2] < -0.05f` test
refuses by design. **A frozen aim counter beside a climbing refusal counter is
the instrument working, not failing** — and `lastFwd` is recorded on BOTH sides of
the refusal precisely so this is readable rather than mysterious.

---

## §2 — ►►►► `A2` IS CLOSED. THE TEN PIXELS WERE THE SCREEN ORIGIN. ◄◄◄◄

**`[MEASURED]`: `origin=(0,10)`, `centre-should-be=(160,120)`.**
**`[MEASURED]`, same run: rest sits at `(160,120)`.**

**THE CROSSHAIR IS EXACTLY CENTRED AND HAS BEEN ALL ALONG.** `188` §3's
`[INFERRED]` is confirmed and discharged: `c_screentop` is `10`, the
`(240 - 220) / 2` letterbox, `crosshair_angle` adds it after the `h * 0.5f`, and
the aim inversion at `ge_vr_aim.c:389` subtracts it. **The two are consistent.**

> **AND THE GAME'S OWN SOURCE SAYS IT INDEPENDENTLY — `[READ]`
> `lib\ge\src\game\bondview.c:724`, `transform3Dto2DCoords` itself:**
> ```c
> out->y = (in->y * inv_z * c_recipscaley) + (c_screentop + c_halfheight);
> out->x = (c_screenleft + c_halfwidth) - (in->x * inv_z * c_recipscalex);
> ```
> **THE PROJECTION'S OWN CENTRE IS `c_screentop + c_halfheight`.** Not `h/2`.
> This is the decompiled game, not our patch, and it has said so since 1997.
> **The `origin=` print and the game's source agree, and they are independent** —
> which is the standard `182` asks for and `184` §3a is the record of skipping.

**`185` `A2`'s gate asked for "a number, not an impression". IT GOT ONE, AND THE
ANSWER IS THAT THERE WAS NOTHING TO FIX.** The `[MEASURED]` ten-pixel drop in
`185`/`187` was real as a measurement and **wrong as a subtraction**: it compared
an origin-included pixel against a naive `h/2`.

> **AND IT UNBLOCKS `185` `B2` WITHOUT A BUILD.** `B2` depended on `A2` because
> *"with A2 outstanding a constant 10 px would masquerade as the miss-HOLDS
> answer."* **There is no constant 10 px. THAT CONFOUND DOES NOT EXIST**, and
> `B2` now depends only on `A1` and `A3`.
>
> **THE GENERAL LESSON, AND IT IS THE THIRD TIME (`163` §7, `171` §2, this):**
> a number measured correctly and interpreted against the wrong reference is
> indistinguishable from a bug until someone prints the reference. **`185` `A2`
> listed three candidate CAUSES and none of them was "the measurement's baseline
> is wrong."** Print the frame before hunting inside it.

---

## §3 — ►► A GATE I WROTE THAT WAS WRONG, RECORDED SO IT IS NOT READ AS A FAILURE ◄◄

**`188` §1 and `vr.ps1`'s on-screen text both say `SAT=` must fall to zero.
`[MEASURED]` `SAT=1447`, essentially unchanged from `187`'s `1424`. THAT IS
CORRECT BEHAVIOUR AND MY GATE WAS WRONG.**

**WHY:** `SAT` originally counted the `162` `+-2` clamp actually firing, read from
`nx`/`ny`. **`188` §2 re-pointed the whole counter block at the PRE-cone values**
so `BAND` would survive the fix — **and `SAT` came along with it.** It now means
*"the raw projection WOULD have saturated"*, which is a property of the
un-clamped geometry and **cannot change when the geometry is bounded downstream.**

**SO THE CORRECT LOG-SIDE GATE FOR `A1` IS `CONE == BAND` WITH `coneOff=0`**
(§1), plus `noFrus=0`. **`SAT` is now a BEFORE-figure like `BAND`, not an after
one.** `vr.ps1`'s text and `188` §1/§5 are corrected to say so.

> **I would rather record this than quietly restate the gate.** `134` and `136`
> are the record of three purpose-built gates failing in a row, and the cost there
> was not the failures — it was that a wrong gate looked like a wrong result.

---

## §4 — WHAT IS OWED, IN ORDER

1. **THE WEARER'S ANSWER TO `G-A1`** — the only outstanding question about `A1`.
   Continuous travel to the edge? A clean stop, no corner snap? **Independent
   saturation on a diagonal sweep?** Nothing further should be built on `A1`
   until this is `[REPORTED]`.
2. **IF `G-A1` PASSES: `A3`**, the HUD shift magnitude — `185` says it *"cannot be
   judged while the crosshair leaves the frame"*, **and that condition is now
   met.** Derive the cyclopean term (`185` `A3`: `-0.1411` from this run's
   tangents, against the applied `0.1867`), do not dial it.
3. **`B2` IS UNBLOCKED EARLIER THAN PLANNED** (§2) — it now waits only on `A1`
   and `A3`.
4. **`A1-VERIFY` STAYS IN**, unchanged, with `SAT` and `BAND` understood as
   before-figures.

**NOTHING STAGED. THE COMMIT IS THE OWNER'S**, both repos.
