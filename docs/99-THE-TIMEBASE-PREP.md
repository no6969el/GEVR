# 99 — GOING AFTER THE TIMEBASE. THE PREP FOR THE NEXT SESSION.

**2026-08-24. Written at the owner's direction after `98`. Read `92` for why 90
is unavailable today, `98` for why the warp was rejected. Nothing here is built.
`48` rule 1.**

---

## §1 — THE DECISION, AND IT IS THE OWNER'S TO MAKE

> ***"It does look better, but I'm not wanting to go in the 'fix' direction. I
> don't even use these features in other VR because I notice them. I want a pure
> smooth experience, not an emulator type feel. I know the game's timing is
> causing this issue and I want it gone."***

**The timewarp WORKED and is being retired anyway. That is a legitimate
engineering decision and it should not be relitigated by a later session:** a
reprojected frame is a guess, the wearer can see guesses, and shipping a guess
to hide a timebase problem leaves the timebase problem in the build forever.

**`-Timewarp` and `-TimewarpInvert` stay in the tree as DIAGNOSTICS.** They are
the sharpest instrument we have for "how much angular error is there between
render and display", and `98` §4's motionless test is the only thing in the
project that can read a pose convention without the wearer turning his head.
**Not the ship path. Not deleted.**

---

## §2 — THE DIAGNOSIS, STATED PLAINLY, BECAUSE THE FIX FOLLOWS FROM IT

**The head-turn judder is not caused by the game simulating at 60. It is caused
by THE VIEW BEING SAMPLED AT 60.**

Those sound like the same sentence and they are not, and the difference is the
whole of §3:

| | Rate | Smooth? |
|---|---|---|
| The world's animation and AI | 60 (the quantum) | **Yes, and nobody has complained about it** |
| Frames presented to the headset | ~90 (RT64 interpolates) | — |
| **The HEAD POSE baked into the eye images** | **60** — `renders=60` in every `posecheck` line we have | **NO. This is the complaint** |

**A stick turn is a world rotation, so RT64's interpolator smooths it. A head
turn enters at eye-render time and the interpolator never sees it.** That is the
stick-vs-head asymmetry, measured, and it is the one fact that has survived every
description since `95`.

> **So the target is not "make the game run at 90". The target is "make the VIEW
> update at 90".** The game running at 90 is ONE WAY to achieve that, and `§4`
> costs it. **It is not the only way and it is not the cheapest.**

---

## §3 — ROUTE D: RENDER 90 REAL FRAMES OF A 60 Hz WORLD. **COST THIS FIRST.**

**Nobody has costed this and it is the route that matches what the owner asked
for.** It is **not** reprojection and it is not interpolation:

> Every presented frame is a **real render**, of real geometry, from the **head
> pose located at that moment**. The world's animation state is the 60 Hz one and
> is reused across pairs of frames. **Nothing is warped, blended or guessed.**

**Head motion becomes genuinely 90 Hz.** Turning your head resamples the actual
scene, because that is what a render is. **World animation stays 60** — a
character's arm advances every other frame — **and that is the same 60 the wearer
already tolerates today and has never complained about.**

**This is how most VR ports of fixed-timestep games ship.** It is the difference
between "the picture is a guess" and "the picture is a render of slightly old
world state", and only the second one survives a wearer who notices reprojection.

### The reads owed before a line of code — `86` §8's rule, do them before, not during

| # | Read | Why it decides the route |
|---|---|---|
| **R1** | **Where does RT64 decide to interpolate rather than re-render, and can the VR eye path opt out?** `renders=60` vs `submits=90` is the measurement; find the code that produces it | **If the eye path can simply be asked to render per presented frame, Route D is a knob, not a project** |
| **R2** | **What does a re-render cost at 5838x4498 per eye?** `49` O22 is unexplained and points the wrong way: 8x fewer pixels ran **4x slower**. **Until O22 is understood, no GPU cost estimate here is trustworthy** | Route D's whole risk is GPU budget. **This is the read that can kill it** |
| **R3** | **Does the game's render path assume one render per sim tick?** Anything that mutates state during draw — particle advance, `23`'s explosion effects — breaks or double-steps when drawn twice per tick | `23` is a known worked instance and is already open |
| **R4** | **`gEXSetRefreshRate(gdl++, 60 / speedgraphframes)`** (`workbench_theboy.c:659`) tells RT64 the SOURCE rate. What does RT64 do with it, and what happens if the source rate and the render rate stop agreeing? | This is `48` rule 6 — a value the other side reads back — and this project has been bitten by that shape **five times**: `21`, `26`, `27`, `32`, `38` |

**R2 is the gate. If a re-render at full eye resolution cannot hold 90, Route D
is dead and §4 is the remaining answer.** Do R2 before R1.

---

## §4 — ROUTE B: CHANGE THE QUANTUM. **RE-COSTED FROM THE TREE, AND `92` WAS TOO PESSIMISTIC**

**`92` §4 called this "large and dangerous — dozens of consumers". Counted, on
2026-08-24, in `lib/ge/src`:**

| | Count |
|---|---|
| `speedgraphframes` references | **24, across 8 files** |
| `g_ClockTimer` references | **152, across 21 files** |
| Of those, comparisons against a **literal** | **43** |
| **Of those 43, comparisons against ZERO** (`> 0`, `== 0`, `<= 0`, `!= 0`, `< 0`) | **39 — semantically INVARIANT under a quantum change.** They ask "did any time pass", and that question survives |
| **Comparisons against a NON-ZERO literal — the ones that actually change meaning** | **FOUR.** `explosion.c:696`, `explosion.c:1297` (`< 15`), `glass.c:227` (`< 15`), `gunfire.c:1465` (`< 3`) |

**Four sites, all named. That is not "dozens" and `92` §4 is corrected here.**
Rule 10.

**BUT THE REAL COST IS NOT THOSE SITES AND `92` MISSED IT TOO.** The danger is
not the comparisons against `g_ClockTimer` — it is **every duration constant in
the engine that means "N sixtieths of a second"**. Timers accumulate
`g_ClockTimer` and compare against literals. Redefine the tick as 1/90 and every
one of those durations runs **1.5x fast**: reload times, door timings, alarm
countdowns, the watch, invulnerability windows. **Those constants are not
greppable by symbol and there are hundreds of them.**

### §4.1 — THE VARIANT THAT AVOIDS ALL OF THAT, AND IT IS THE ONE TO EVALUATE

> **Do not change what a tick MEANS. Allow a FRACTIONAL one.**

Keep the tick as 1/60 s. Let `g_ClockTimer` carry **0.667** when a frame took
1/90 s. **Every duration constant in the tree keeps its meaning** — 60 ticks is
still one second — and the sim simply advances in smaller steps.

**What that costs, and it is a real list, not a shrug:**

| | |
|---|---|
| **`g_ClockTimer` is `s32`** | `bondtypes.h`. Making it `f32` touches all 152 references. Most are multipliers and are fine as floats; **the integer ones must be found deliberately, not by compiler silence** |
| **THE AIM INTEGRATORS LOOP ON IT** | `gunfire.c:4692`, `for (i = 0; i < g_ClockTimer; i++)`. **A fractional count cannot drive a loop.** It becomes a damped step with a `dt` — **and that changes the aim feel of every weapon, which is exactly what `92` warned about and what `87` and `90` spent a session pinning down** |
| **The four non-zero literals** | `< 15` and `< 3` above. Each needs reading in context |
| **Accumulator types** | `zoomintime` is already `f32` (`bondview2.c:3036`). **`damageshowtime`, `watch_time_0`, `g_gameOverFlag` and `chevron_glow_timer` are NOT yet checked** — an `s32 += 0.667f` truncates to zero and the timer **never advances**. A dead countdown is a silent, plausible-looking bug |

**Route B — even the fractional variant — still changes aim feel and still
invalidates the timing assumptions in every `86` slice. It remains the last
resort. But it is now a costed last resort with four named sites and a specific
type audit, instead of a warning.**

---

## §5 — THE ORDER FOR THE NEXT SESSION

> 1. **R2 — what does a full-resolution eye re-render cost, and what is O22?**
>    No launch needed to start; `49` O22 is a standing unexplained result and it
>    is the single number Route D lives or dies on.
> 2. **R1, R4 — how RT64 chooses interpolate-vs-render, and what it does with the
>    source rate it is told.**
> 3. **THEN discuss. Do not build.** Route D is a knob or a project depending
>    entirely on R1, and nobody knows which yet.
> 4. **Route B only if R2 kills Route D.**

**Gates for whatever gets built, written now — `48` rule 2:**

| | |
|---|---|
| **G-99-1** | **Worn: turn the head fast. The doubling is gone, not reduced.** The owner has already rejected "better"; the bar is a clean image |
| **G-99-2** | **`posecheck` `renders` rises to ~90 and `reused` falls to ~0.** The measurement that defines the fix, and it is already in the tree and already printing |
| **G-99-3** | **Stick turn no worse, and world animation no worse.** Route D reuses world state across frame pairs — if that is visible, it has traded one artefact for another |
| **G-99-4** | **`-NoXr` untouched; `-Flat` still measures -113 px +/-5.** B1 cost weeks |
| **G-99-5** | **No weapon's aim feel changes.** Route B's tripwire. Under Route D it must be free — **if aim feel changes under Route D, something is stepping the sim that should not be, and R3 was answered wrong** |

## §6 — WHAT IS STILL OWED FROM BEFORE, UNCHANGED

**The game half of S0 has never printed a line** — every `6dof-game:` field,
including the `muzzleExt` and `A40` falsifiers, is still unread because that
launch never reached a level. **One launch that enters a mission with a gun in
hand closes it, and it batches free with any wear test above.** `97` §5.
