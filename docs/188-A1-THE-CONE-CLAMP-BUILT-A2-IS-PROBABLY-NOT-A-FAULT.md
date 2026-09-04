# 188 — `A1` IS BUILT: THE DIRECTION IS BOUNDED TO THE FRUSTUM CONE. `A2` MAY NOT BE A FAULT AT ALL.

> **►► RUN AND PARTLY SUPERSEDED BY `189`. TWO CORRECTIONS, BOTH MINE: ◄◄**
> **1. §1 and §5's "`SAT=` must fall to zero" IS WRONG** — §2 re-pointed the
> counter block at the PRE-cone values, so `SAT`, like `BAND`, is a BEFORE-figure
> and cannot fall. **The log-side gate is `CONE == BAND` with `coneOff=0`.**
> `189` §3.
> **2. §3's `[INFERRED]` on `A2` IS CONFIRMED AND DISCHARGED** — `origin=(0,10)`.
> **`A2` was never a fault.** `189` §2.

**2026-08-25. Tiers per `182`. Every commit is the owner's.**
**BUILT AND UNRUN. Three behaviour-neutral instruments ride with it.**

---

## §0 — WHAT IS IN THE TREE

| | | |
|---|---|---|
| **`A1`** the frustum cone clamp | **BUILT, UNRUN.** Knob `-NoAimCone` | §1 |
| **`A1-VERIFY` kept, and re-pointed** | **BUILT.** It now measures PRE-cone geometry | §2 |
| **`A2`** the ten-pixel drop | **NOT FIXED — because it may not be broken.** One print settles it | §3 |
| **`begin_shutdown()` entry print** | **BUILT.** No behaviour change | §4 |

**FILES: `patches/ge_vr_aim.c`, `patches/ge_vr_bindtest.c`, `patches/misc_funcs.h`,
`patches/syms.ld`, `src/game/recomp_api.cpp`, `src/main/rt64_render_context.cpp`,
`vr.ps1`.**
**ONE NEW `RECOMP_PATCH`-REACHABLE SYMBOL — `recomp_ge_vr_aim_cone` at
`0x8F000160`. SO BUILD TWICE (`136`).** No header in the `115` cross-boundary set
changed; `rt64_render_context.cpp` is a `.cpp`, not a header.
**`168` §5's mandatory grep: ZERO new GAME symbols.** Everything touched is our
own patch-side global or an existing call site.

---

## §1 — ►►►► `A1`. THE CLAMP IS ON THE DIRECTION, NOT THE RESULT. ◄◄◄◄

`ge_vr_aim.c`, inside the `167` frustum block, **above** the `162` `+-2` clamp.

`rX`/`rY` are the aim ray on the `z = -1` plane — **tangents** — and the
frustum's own limits in those units are `cX +- hX` and `cY +- hY`, the live
headset values `167` already establishes. **The ray is bounded into that box
before `nx`/`ny` are formed.**

**WHY THIS IS NOT THE `162` CLAMP AGAIN.** `162` clamps the OUTPUT to `+-2` NDC,
so every direction past the edge produces the SAME point — `187` measured
`SAT=1424` frames doing exactly that, and `184` found 290 samples on the single
pixel `(480,340)`. **Bounding the input keeps the projection monotonic to the
edge and then pins smoothly.** The `162` clamp is left in place and simply stops
being reachable on this path (`|n| <= 1` by construction now) — **`00-START-HERE`,
DELETE NOTHING.**

**PER AXIS, NOT BY VECTOR LENGTH — AND THAT IS `G-A1`'s SECOND HALF.** A single
radial clamp would drag both axes to a corner together, **which would look like
the very fault this removes.** Sweep diagonally: X must be able to pin while Y is
still moving.

**NO ZERO GUARD, ON PURPOSE.** `hX`/`hY` are already proven `> 0.01f` by the
enclosing test and `-fwd[2] > 0.05f` by the refusal above, so both divides are
bounded. **A guard here would imply a case that cannot occur** — `48` rule 13
wants sentinels where a stale value is possible, not decoration.

**KNOB `-NoAimCone`** (`GE_VR_AIM_CONE=0`), **default ON.** The fault it removes
is `[MEASURED]`, not inferred, so the switch is the A/B arm rather than the
guard. Its env shape is copied from `GE_VR_CLAMP_SPLIT` deliberately — a knob
that reads its environment differently from its neighbours is `162`'s trap.

### `G-A1`, RESTATED SO IT CANNOT BE FITTED AFTER THE RUN
- **In the headset:** sweep slowly RIGHT. **The crosshair moves CONTINUOUSLY to
  the edge and STOPS.** No jump, no corner snap. Then diagonally: **the two axes
  saturate INDEPENDENTLY.**
- **In the log:** `CONE=` non-zero and tracking `BAND=`, and **`SAT=` at or near
  zero.** See §2 — the two together are the gate, not either alone.

---

## §2 — THE INSTRUMENT HAD TO MOVE, OR IT WOULD HAVE REPORTED SUCCESS EITHER WAY

**THIS IS THE ONE TRAP IN THE SLICE AND IT IS INVISIBLE.** `186` read `BAND` from
`nx`/`ny` at the `162` clamp, *"the only place both values exist unclamped."*
**`A1` now sits ABOVE that point.** Left alone, the counter would have read the
CURED value, printed `BAND=0` forever, and **destroyed the only before-figure
this project has for the fault** — while looking exactly like success.

**SO THE PRE-CONE PROJECTION IS RECORDED WHERE IT EXISTS** (`g_geVrAimRawNx/Ny`,
one line above the clamp, same two expressions including the vertical negation)
**and the counters read those.** `174`'s trim is deliberately excluded: it is a
measurement offset, and folding it in would let the trim change the band figure.

**AND THE FIX GETS ITS OWN COUNTER BESIDE THE FAULT'S:**

```
[gevr] A1-VERIFY: aimed= refused= | INSIDE= BAND= SAT= noFrus= | CONE= coneOff= | maxNx= maxNy= | ...
```

| reading | meaning |
|---|---|
| **`CONE` tracks `BAND`, `SAT` -> 0** | **`G-A1` PASSING IN THE LOG.** The clamp engages on the frames that need it |
| **`BAND` large, `CONE` 0** | **THE FIX IS INERT, NOT WORKING** — and without this counter it is indistinguishable from success |
| **`coneOff` non-zero** | `-NoAimCone` was passed. This run is the A/B arm |

**THE BEFORE-FIGURE TO BEAT, `187` §1:** `aimed=8548 refused=936 | INSIDE=5702
BAND=2846 SAT=1424 noFrus=0 | maxNx=15376 maxNy=20575`.

---

## §3 — ►► `A2`: `[INFERRED]` THAT THE TEN PIXELS ARE THE SCREEN ORIGIN. ◄◄

`185` `A2` records a `[MEASURED]` constant drop — rest at `(160,120)`, screen
`320x220`, so *"ten pixels low, constant, 377 samples"*. **`187` confirmed it
again across 318 fresh samples. The measurement is not in doubt. THE
SUBTRACTION IS.**

**`[READ]` `ge_vr_aim.c:552-553` then `:615-616`:** `crosshair_angle` is built as
`... + screen_height * 0.5f` and **then has `c_screentop` ADDED.** The NDC
inversion at `:389` **SUBTRACTS `c_screentop`** before dividing. **The two are
consistent, and the centre of the drawn rectangle is
`(screenleft + w/2, screentop + h/2)` — not `(w/2, h/2)`.**

**`[INFERRED]`: if `c_screentop` is 10 — `(240 - 220) / 2`, the letterbox — then
the ten pixels ARE the screen origin, the crosshair is exactly centred, and
`A2` IS NOT A FAULT.** The observed `(160,120)` fits that exactly, and
`screenleft = 0` fits the `x = 160` half of the same sample.

**`182` FORBIDS BUILDING ON THAT, SO NOTHING WAS BUILT. ONE PRINT SETTLES IT**,
on the existing `WIDE-frustum` line:

```
... screen=320x220 fovy=106 znear=2 origin=(L,T) centre-should-be=(X,Y)
```

- **`origin=(0,10)` and `centre-should-be=(160,120)`** -> **`A2` CLOSES AS "CORRECT
  ALL ALONG".** `185` `A2`'s gate asked for *"a number, not an impression"*, and
  **"not a fault" is a perfectly good answer to a gate.**
- **`origin=(0,0)`** -> the drop is real, and `185` `A2`'s remaining candidates are
  next: the `220` vs `240` constant at `ge_vr_aim.c:781`, and the HUD's own
  vertical origin.

> **AND THIS MATTERS BEYOND `A2`.** `185` `B2` says a constant 10 px would
> masquerade as T7's *"miss HOLDS"* answer. **If `A2` is not a fault, that
> confound does not exist and `B2` is unblocked by a read rather than a fix.**

---

## §4 — THE `begin_shutdown()` ENTRY PRINT. `187` §3.

**No behaviour change. `ge_vr::log`, on a path that runs once per process.**

`187` §3: the second X close bugchecked the machine and the log had **no
`shutdown:` line at all** — and that absence is **ambiguous between two very
different faults**: `begin_shutdown()` was never reached (`181` does not cover
this close path), or it was reached and died inside the drain or the teardown
(`181` is right about WHERE and wrong about WHAT). **Five sessions were spent in
the second territory while the answer was the first** — `181`'s own opening.

**THREE LINES, AND THE FIRST IS BEFORE THE LATCH ON PURPOSE:** printing after it
would go silent on a re-entry, and *"no line"* is precisely the reading being
disambiguated. **The latch's own decision is printed instead.**

```
[gevr-xr] shutdown: begin_shutdown ENTERED
[gevr-xr] shutdown: begin_shutdown re-entered, latched - returning
[gevr-xr] shutdown: drained, entering xr_shutdown        (or NOT drained ...)
```

**READ IT LIKE THIS ON THE NEXT CRASH:** no `ENTERED` -> nothing called it, go
back to who posts the quit. `ENTERED` and nothing after -> it died in
`ge_vr_drain_present_thread`, and `40`'s timeout branch is where to look.
`entering xr_shutdown` and nothing after -> the teardown itself, which is where
five sessions already looked and `181` says is correct.

**AND THE STANDING INSTRUCTION IS STILL `taskkill` (`187` §3).** These lines cost
nothing and will be there when a close is eventually spent deliberately —
**do not spend one to collect them.**

---

## §5 — WHAT IS OWED, IN ORDER

1. **BUILD TWICE** — one new `RECOMP_PATCH`-reachable symbol (`136`).
2. **ONE RUN, the standing command from `MAIN-STATION-TASKS.md`, unchanged**, with
   **`-NoCrouch`** (`00-START-HERE`: physical crouch moves the camera and would
   silently change what the aim test measures).
   **SWEEP SLOWLY — right, left, up, down, and DIAGONALLY — and dwell past the
   stop.** No shots needed; both instruments are populated by aiming alone.
3. **READ, IN THIS ORDER:** `noFrus` (can still void the run) -> `CONE` and `SAT`
   -> `origin=` for `A2` -> then judge `G-A1` in the headset.
4. **IF `G-A1` PASSES: `A3`** — the HUD shift magnitude, which `185` says cannot
   be judged until the crosshair stops leaving the frame. **That gate is now
   met.**
5. **IF `CONE` IS ZERO WITH `BAND` LARGE:** the clamp is not reaching those
   frames. Do not tune it — **find out why it did not run**, and `coneOff` says
   whether the knob is the reason.

**NOTHING IS STAGED. THE COMMIT IS THE OWNER'S**, `commit-session.ps1`, on
Windows, both repos.
