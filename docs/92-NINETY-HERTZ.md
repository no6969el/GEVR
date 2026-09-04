# 92 — CAN THIS RUN AT 90 Hz? THE SIMULATION QUANTUM SAYS NOT NATIVELY.

**2026-08-23. Priority raised by the owner: judder and comfort outrank feature
work, because a build that makes the wearer sick is not shippable however many
slices it has. This is a source read plus a measurement of a log ALREADY ON
DISK. No launches, no build, no headset.**

> # ►► THE SHORT ANSWER ◄◄
>
> **The game's simulation timestep is quantised to a WHOLE number of 1/60 s
> ticks. It can run at 60, 30, 20, 15 — and it cannot run at 90, on any
> hardware, because 90 is not 60 divided by an integer.**
>
> **This is not a performance limit and no amount of PC is going to move it.**
> It is `waitForNextFrame` (`frametiming.c:75`) waiting for an integer number
> of VI periods and then telling the whole game how many it waited
> (`speedgraphframes`), which every timer in the engine then integrates by.
>
> **So 90 Hz in the headset is 60 Hz of GAME through an interpolator, and the
> interpolator is not optional — `64` measured that turning it off froze the
> build harder.**
>
> ## AND THE MEASUREMENT SAYS THE SIM IS ALREADY HOLDING 60
>
> **From `gevr.log`, 149 one-second samples of a worn session, at zero cost:**
>
> | Game tick rate | Samples |
> |---|---|
> | **>= 59 (locked at 60)** | **142** |
> | 45-59 (dipping) | 5 |
> | 28-45 (near half) | **1** |
> | < 28 (level load / stall) | 1 |
>
> **Render: median 91 eye passes per second, min 3, max 93.**
>
> > **`73`'s hypothesis — "the VI clock halves to 30 in heavy scenes, so the
> > interpolation stretch triples exactly when the scene gets busy" — is REAL
> > but RARE.** One sample in 149 shows it, and it shows it exactly as `73`
> > predicted: **`30.8 fps` of game while `eye0=92` of render.**
> >
> > **One sample in 149 cannot be a judder that is felt continuously.** If the
> > judder is constant, `73` is not the cause, and `73` said so itself: *"if it
> > judders equally standing still, that is wrong."* **That falsifier has still
> > never been run, and it is now the cheapest question in the project.**

---

## 1. WHY 90 IS STRUCTURALLY UNAVAILABLE — THE SOURCE

```c
/* lib/ge/src/game/frametiming.c:75 — waitForNextFrame, the stock one */
do {
    nextFrameTime = ((osGetCount() - copy_of_osgetcount_value_1) + 387937) / 775875;
} while (nextFrameTime < frameDelay);

frameDelay = 1;
updateFrameCounters(nextFrameTime);      /* -> speedgraphframes = nextFrameTime */
```

**775875 COP0 counts is one 60 Hz VI period.** `nextFrameTime` is therefore
**how many whole 1/60 s periods the last frame took, rounded, minimum 1.**

**And `speedgraphframes` is the game's timestep.** It is not a statistic:

| Consumer | What it does |
|---|---|
| `lv.c:974` | **`g_ClockTimer = speedgraphframes`** |
| `gunfire.c:4692` | `for (i = 0; i < g_ClockTimer; i++)` — **the aim integrators step once per tick** |
| `bondview2.c:6181`, `:7991`, `:3036` | damage timers, watch timers, zoom |
| `mpmenu.c`, `chrobj*`, and dozens more | every countdown in the engine |
| **`workbench_theboy.c:659`** | **`gEXSetRefreshRate(gdl++, 60 / speedgraphframes)`** — tells RT64 the SOURCE rate for interpolation |

> **The engine has no concept of a fractional tick.** A frame is one 1/60 s
> quantum or two, never one and a half. **To make the game itself run at 90 you
> would have to change that quantum to 1/90 and then be right about every
> consumer of `speedgraphframes` in the tree.** Section 4 costs that honestly.

---

## 2. WHAT THE PC PORT ACTUALLY BOUGHT — because the expectation is reasonable

**The owner's expectation, in their words: *"I thought that was the whole point
of porting it to PC."*** It is worth answering that directly rather than
technically.

| The port bought | It did not buy |
|---|---|
| **Resolution** — 5838x4498 per eye instead of 320x240 | **A faster simulation.** The game's own tick is still a 1/60 s quantum, in the game's own code |
| **A stable 60** instead of the N64's frequent drops — the measurement above is the evidence | **A 90 Hz simulation.** Nothing in the recomp changes the quantum |
| **Interpolated frames** to fill the gap to 90 | **Motion that was never simulated.** An interpolated frame is a guess between two real ones |
| Head tracking, stereo, motion controllers | |

**A recompilation is the ORIGINAL GAME'S LOGIC, faithfully.** That fidelity is
what makes it GoldenEye and it is also what carries the 1/60 quantum in.

---

## 3. SO WHAT IS THE JUDDER? THREE CANDIDATES, RANKED, AND NONE IS CONFIRMED

**`48` rule 3: measure, do not describe. Nothing below is measured yet — these
are ranked candidates with a falsifier each, and the ranking is from the
measurement in the banner, which eliminates the previous favourite.**

### CANDIDATE 1 — THE 2:3 CADENCE. Structural, constant, and it fits "constant".

**60 simulated frames become 90 displayed frames: a ratio of 2:3.** Each
simulated frame is 16.67 ms; each displayed frame is 11.11 ms. **A sim frame
therefore covers one-and-a-half display frames, so the presentation alternates
between holding one display frame and holding two.**

> **This is the same structure as 3:2 pulldown — 24 fps film on a 60 Hz
> television — and it is the textbook cause of a regular, periodic judder.**
> **It would be felt CONSTANTLY, at a steady beat, worst on smooth continuous
> motion like turning, and it would not care whether the scene is busy.**
>
> **Interpolation is supposed to be the answer to exactly this.** RT64 is told
> the source rate (`gEXSetRefreshRate`, 60) and the target (`rr_manual_value`,
> 90) and asked to synthesise the difference. **So if this candidate is the
> cause, the real finding is that the interpolation is not doing its job — see
> candidate 2 — rather than that the ratio is wrong.**

**FALSIFIER, one launch, no code:** set `rr_manual_value` to **60** and run the
headset at a **60 Hz** mode if the runtime offers one. **A 1:1 ratio removes
this candidate entirely.** If the judder survives a true 1:1, it is not cadence.
*(60 Hz in a headset is its own comfort problem. This is a DIAGNOSTIC, not a
proposal.)*

### CANDIDATE 2 — PARTIAL INTERPOLATION. Some things interpolate, some do not.

**The interpolation layer has known, documented defects.** `04` shipped six
fixes to it. **`23` is still open: explosion effects STICK TO THE VIEW when
turning** — an object that is not being interpolated while the world is.

> **If the world interpolates to 90 and the gun, the HUD, or an effect steps at
> 60, the RELATIVE motion between them judders even though each is internally
> consistent.** **In a headset that is far more nauseating than a uniform
> judder**, because the eye locks onto the near object — **and the near object
> here is the gun, which is the thing the wearer is looking at.**
>
> **This candidate is strengthened by `23` being a KNOWN INSTANCE of exactly
> this fault, already reported, already open, and never connected to judder.**

**FALSIFIER, one launch, no code:** `-Flat`, stand still, and turn slowly.
**Film the screen and step through frames.** If the world's edges move smoothly
while the gun's edges move in steps, this is it, and it is measurable without a
headset at all — the `-Flat` method `49` gave us.

### CANDIDATE 3 — `73`'s VI-CLOCK HALVING. Real, measured, and RARE.

**Confirmed to happen — one sample in 149, at `30.8 fps` of game against
`eye0=92` of render.** When it happens the interpolation stretch doubles from
1.5x to 3x, which is a genuine and severe discontinuity.

> **But one sample in 149 seconds cannot be a constant judder.** **It is a
> plausible cause of an OCCASIONAL LURCH and a poor one for a continuous
> shimmer.** Keep it; do not lead with it.

**FALSIFIER — `73` wrote it and nobody has run it: *"if it judders equally
standing still, doing nothing, this is wrong."*** **This is the single cheapest
question in the project and it settles candidate 3 in about ten seconds of
wearing.**

---

## 4. THE THREE ROUTES TO 90, COSTED HONESTLY

| Route | What it is | Cost | Verdict |
|---|---|---|---|
| **A. Keep 60 sim + fix the interpolation** | Leave the quantum alone. Make every object interpolate, and never let the sim drop to 30 | **Bounded.** `23` is already open and is a worked instance; the sim is already holding 60 in the measurement | **START HERE.** It is the only route that does not touch the engine's timebase, and candidates 1 and 2 both resolve inside it |
| **B. Change the quantum to 1/90** | Rewrite `waitForNextFrame`'s period, and audit **every** consumer of `speedgraphframes` and `g_ClockTimer` | **Large and dangerous.** Dozens of consumers; the aim integrators LOOP on `g_ClockTimer`; weapon timers, animation blends and AI all scale by it. **`21`, `26`, `27`, `32` and `38` are all instances of this project changing a value the game reads back** | **NOT NOW.** It is the "real" fix and it is a project, not a slice. Revisit only if A fails |
| **C. Run the headset at 60** | Match display to sim, 1:1, no interpolation at all | **Trivial to test, poor to ship.** 60 Hz in a headset is its own comfort cost | **AS A DIAGNOSTIC ONLY** — it is candidate 1's falsifier |

> **Route A is also the only one that is compatible with the 6DoF work already
> planned.** Route B would invalidate the timing assumptions inside every slice
> in `86`, including the two integrators `87` and `90` spent a session pinning
> down — **`crosshair_x_pos` steps once per `g_ClockTimer`, so changing the
> quantum changes the aim feel of every weapon.**

---

## 5. WHAT `72` ALREADY RULED OUT, SO NOBODY RE-RUNS IT

**The XR submit loop is EXONERATED.** 516 samples, one over the 11.11 ms
budget, ~87% of every frame blocked in `xrWaitFrame`. **Blocking in
`xrWaitFrame` is CORRECT behaviour** — it is the compositor pacing the
application, not a stall.

**But `72`'s numbers are MEANS, and a mean cannot see a hitch.** `00`'s
instrument warning, fifteenth entry. **The submit loop is cleared of being
SLOW. It is not cleared of being IRREGULAR**, and no instrument in this tree
currently reports a maximum or a late count.

**`73` asked for `max` plus a late-count beside the mean. Two lines. Still not
built — and it is the instrument this whole question needs.** O54, O56.

---

## 6. THE ONE THING THAT WOULD SETTLE MOST OF THIS, AND A WEARER CAN DO IT

**`00`: the wearer is the best instrument in this project. Ask what it looks
like, not whether it works.** Three questions, one launch, no code:

1. **Stand perfectly still and look at a wall. Does it judder?**
   *Yes* -> candidate 1 or 2. *No* -> candidate 3, and `73` is back in front.
2. **Turn your head slowly with the world otherwise still. Is the WORLD smooth
   while the GUN steps, or do they judder together?**
   *Gun steps against a smooth world* -> **candidate 2, and `23` is the same
   bug.** *Together* -> candidate 1.
3. **Does it get worse when the scene gets busy, or is it constant?**
   *Constant* -> 1 or 2. *Worse when busy* -> 3.

> **These three answers separate all three candidates, and none of them needs a
> build.** **Every wrong conclusion in this project came from reasoning about an
> appearance; these are the appearance questions whose ANSWERS are diagnostic
> rather than descriptive** — which is the distinction `79` proved is worth
> asking for, when three faults were diagnosed from description alone.

---

## 7. WHAT THIS CHANGES IN THE PLAN

**Comfort outranks features. `86`'s slice order is unchanged but its
PRIORITY is now second.**

| | |
|---|---|
| **S0 still ships first** | It is written (`91`) and it costs one build. **And it is the frame where a pacing instrument belongs** — `73`'s max-and-late-count is two lines beside quantities S0 already prints |
| **NEW: O74, the pacing instrument** | `max` and a late-count beside `72`'s means. **Two lines. `73` asked for it and it has been outstanding since.** Do it WITH S0, not after — `48`'s amended rule 5: diagnostics may be batched, they cannot regress anything |
| **NEW: O75, the three wearer questions** | Section 6. **One launch, no code, settles the ranking** |
| **`23` is PROMOTED** | *"Explosion effects stick to the view when turning"* has sat as a cosmetic annoyance since Phase 1. **If candidate 2 is right it is the same bug as the judder, and it is the only worked instance of it in the tree** |
| **H1 and the rest of `86`** | **After the judder question has an answer.** A slice built into a build that makes the wearer sick cannot be evaluated by the wearer, and the wearer is this project's best instrument |

**Nothing here is built. `48` rule 1.**
