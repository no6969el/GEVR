# 117 — R4. PERFECT DARK NEVER SOLVED OUR PROBLEM, BECAUSE IT NEVER HAD IT.

**2026-08-24. `114` §3.2's read 4, done. MIT, read at `67ea20c` — the same
commit `86` and `102` were read at. No machine needed, no GPU.**

> **THIS CHANGES THE STRATEGIC PICTURE AND IT DOES NOT CHANGE THE OWNER'S
> DECISION. Route B stays last resort until the owner says otherwise. What
> follows is evidence to re-decide WITH, not a decision.**

---

## §1 — WHAT THEIR VR FRAME LOOP ACTUALLY IS

**`port/src/pdmain.c:620-687`, `mainTick()`, in order:**

```c
vr_begin_frame_and_update_poses();   /* xrWaitFrame, xrBeginFrame, xrLocateViews, head pose */
lvTick();                            /* THE GAME SIMULATION. ONE TICK. */
lvTickPlayer();
gdl = lvRender(gdl);                 /* render */
vr_end_frame_and_submit();           /* xrEndFrame */
```

**And their own comment, `vr_openxr.cpp:2093`:**

> *"xrWaitFrame below is the ONLY thing pacing the game's tick."*

> ## **ONE SIM TICK, ONE RENDER, ONE XR FRAME, IN LOCKSTEP, PACED BY THE HEADSET.**
>
> **NO INTERPOLATOR. NO DUPLICATE SUBMISSIONS. ONE HEAD POSE PER RENDERED FRAME, LOCATED AT THAT FRAME'S OWN `predictedDisplayTime`.**

---

## §2 — SO THE ANSWER TO `114` §3.2's READ 4 IS: THEY DON'T

**R4 asked whether Perfect Dark does per-pass head poses, because if they had,
the answer would be sitting in a readable tree.**

**They do not, and they never needed to.** `vr_update_head_tracking(g_frameState.predictedDisplayTime)`
runs once per XR frame, and there is exactly one simulated, rendered frame per
XR frame. **There are no passes to pose.**

**P1 IS NOT COLLAPSED — BUT IT IS RE-FRAMED.** Per-pass posing is not the
architecture PD arrived at; **it is a workaround for an interpolator that exists
only because our sim cannot run at the display rate.** It remains the right move
*if we stay on the interpolator*, and `114` §3's slicing stands. It is no longer
"catching up to prior art."

---

## §3 — AND HERE IS WHY THEY COULD DO THAT AND WE CANNOT

**This is the finding. The two engines differ in exactly one structural way.**

### Perfect Dark — `src/game/lv.c:2233-2246`

```c
g_Vars.lvupdate240  = g_Vars.diffframe240;              /* elapsed time in 240ths, VARIABLE */
...
g_Vars.lvupdate60    = g_Vars.lvupdate240 + g_Vars.lvupdate240rem;
g_Vars.lvupdate240rem = g_Vars.lvupdate60 & 3;          /* <-- THE REMAINDER IS CARRIED */
g_Vars.lvupdate60  >>= 2;                                /* integer 60ths, for legacy constants */
g_Vars.lvupdate60f   = g_Vars.lvupdate240 * 0.25f;      /* <-- AND A FLOAT TIMESTEP */
```

| | |
|---|---|
| **Base unit** | **240ths of a second** — four times finer than the tick |
| **The remainder** | **`lvupdate240rem` CARRIES the leftover quarter-ticks.** Nothing is discarded |
| **Integer form** | `lvupdate60` — still a whole number of 60ths, so **every legacy "N sixtieths" duration constant works untouched** |
| **Float form** | `lvupdate60f`, `lvupdate60freal` — exposed to anything needing sub-tick precision |

### GoldenEye — `lib/ge/src/game/frametiming.c:46-53`

```c
void updateFrameCounters(s32 deltaFrames) {          /* INTEGER frames */
    currentFrameCounter += deltaFrames;              /* integer accumulation */
    speedgraphframes = deltaFrames;
}
```

**And `waitForNextFrame` busy-waits on
`(osGetCount() - base + 387937) / 775875` — an integer count of 1/60 units with
the fractional part DISCARDED. There is no remainder accumulator anywhere.**

> ## **PD CARRIES THE REMAINDER AND EXPOSES A FLOAT TIMESTEP. GOLDENEYE TRUNCATES AND EXPOSES ONLY INTEGERS.**
>
> **THAT IS THE WHOLE DIFFERENCE, AND IT IS THE ENTIRE REASON THEY GET NATIVE 90 Hz AND WE NEED AN INTERPOLATOR.**

**Note what this does NOT require: 240 does not divide evenly into 90 either**
(240/90 = 2.667). **The remainder accumulator is what makes a non-divisible rate
work** — you apply 2 or 3 units and carry the leftover. **`92`'s "90 is not 60
over an integer, therefore unreachable" is true of a truncating timebase and
false of an accumulating one.**

---

## §4 — WHAT THAT DOES TO ROUTE B's COST — `99` §4, `114` §5

**Two corrections, pulling in opposite directions. Both matter.**

### §4.1 — WORSE: THERE IS NO PRIOR ART TO COPY

**`114` §3.2 hoped PD's tree might contain the timebase work.** It does not —
**they never did any.** Their VR port let `xrWaitFrame` pace a tick that was
already variable. **Route B has a validated DESIGN in PD's source and NOT a
migration to copy.** `114`'s R4 optimism is corrected here.

### §4.2 — BETTER, AND THIS IS THE LARGER EFFECT

**`99` §4 named the main cost as "the hundreds of duration constants meaning
'N sixtieths of a second'".**

**PD shows those DO NOT NEED TO CHANGE.** `lvupdate60` remains an integer count
of 60ths and every constant expressed in 60ths keeps working. **The change is
confined to how that integer is DERIVED — an accumulator underneath it — not to
the hundreds of places that consume it.**

> **`99` §4's headline cost estimate appears to be an OVERESTIMATE, and `99`
> §4.1's fractional-tick variant is not a clever workaround — it is what the
> next game in the same engine family actually shipped.**

**THIS IS NOT A CLAIM THAT ROUTE B IS CHEAP.** It is a claim that its most-cited
cost may not be real. **`99` §4's other finding stands and is the part to
re-cost: 39 of 43 literal `g_ClockTimer` comparisons survive untouched and FOUR
do not, and those four are named.** That, plus an accumulator in
`updateFrameCounters`, may be closer to the true scope.

**IT IS A READ, NOT A COSTING. Nobody has tried it.**

---

## §5 — THE HONEST CAVEATS

1. **PD is not GoldenEye.** Same family, different decomp, and the aim feel
   argument in `92` still stands: `crosshair_x_pos` steps once per
   `g_ClockTimer`, so a finer tick changes weapon feel. **PD's `lvupdate60f`
   suggests the fix is to give the aim integrator the FLOAT timestep rather than
   a finer integer one — but that is a hypothesis from their structure, not
   something read in their aim code.**
2. **This says nothing about whether our RT64 interpolator could be removed.**
   PD renders with fast3d and their own pipeline. **Our 90 Hz presentation is
   entangled with RT64's interpolated workloads, and `64` proved that
   interpolator is load-bearing.**
3. **B3 and B4 are untouched by any of this** and are still the only two things
   `39` marks BLOCKING.

---

## §6 — WHAT I WOULD PUT IN FRONT OF THE OWNER

**The judder line has now spent `92` through `116` — fifteen documents — on
making a 60 Hz simulation look like 90 Hz. `116` may well close the duplicate
frame. The head-turn half (`114` §3) is the next several.**

**And the same engine, one game later, MIT, gets it for free by carrying a
remainder.**

> **THE QUESTION IS NOT "IS ROUTE B WORTH IT" IN THE ABSTRACT. IT IS: IS ONE
> ACCUMULATOR IN `updateFrameCounters` PLUS FOUR NAMED `g_ClockTimer`
> COMPARISONS CHEAPER THAN THE REMAINING INTERPOLATOR WORK — GIVEN THAT IT ALSO
> DELETES THE PER-PASS POSE PROBLEM, THE DUPLICATE FRAME PROBLEM, AND THE
> PACING PROBLEM AT ONCE?**

**That is a genuinely open question and it is the owner's to answer.** Route B
stays last resort until he says otherwise — **but it should now be re-decided on
this evidence rather than left parked on `92`'s "structurally unavailable",
which is true of the timebase we have and not of the one PD ships.**

### §6.1 — THE CHEAP NEXT READ IF HE WANTS IT COSTED

**No machine, no GPU, and it is the read `99` §4 never finished:**

1. **Every writer and reader of `currentFrameCounter` and `speedgraphframes`** —
   `99` counted `g_ClockTimer` comparisons and not these.
2. **Whether `jpD_800484CC`/`jpD_800484D0`** — the float shadows already in
   `frametiming.c`, currently under `#ifdef BUGFIX_R1` and mere casts of the
   integer — **are read anywhere.** If something already consumes a float
   timestep, the migration has a foothold.
3. **What `waitForNextFrame`'s busy-wait becomes** when the pacing comes from
   `xrWaitFrame` instead. **PD deleted this problem by not having it; ours is a
   spin loop on `osGetCount` and it is the thing that would have to yield.**
