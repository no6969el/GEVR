# 118 — ROUTE B, COSTED FROM THE TREE. IT IS A SLICE, NOT A PROJECT.

**2026-08-24. `117` §6.1's read, done. No machine, no GPU.**
**`92` and `99` both over-costed this, and `117` §4.2 guessed why. Here are the
numbers.**

> **A COSTING, NOT A DECISION. Route B is the owner's call and it stays last
> resort until he moves it. But it should be moved or parked on THIS, not on
> `92`'s "structurally unavailable", which describes the timebase we have and
> not the one that is reachable.**

---

## §1 — THE ARCHITECTURE IS ALREADY 90% OF PERFECT DARK's

**`117` §3 found PD carries a remainder and exposes a float timestep, and said
GoldenEye does neither. HALF OF THAT IS WRONG. We already have the float.**

| | Perfect Dark | GoldenEye | |
|---|---|---|---|
| **Integer tick, 60ths** | `lvupdate60` | **`g_ClockTimer`** | **EXISTS.** 152 refs. **Written in FIVE places, all in `lv.c`** — three are `= 0` (paused/locked), one is `= 1`, and **exactly one is the per-frame delta** |
| **Float tick, 60ths** | `lvupdate60f` | **`g_GlobalTimerDelta`** | **EXISTS. 217 refs — MORE than the integer.** Derived one line below the integer, `lv.c:979`: `g_GlobalTimerDelta = (f32) g_ClockTimer;` |
| **Remainder accumulator** | `lvupdate240rem` | **— MISSING** | **THE ONLY GAP** |
| **Zero-tick frames** | supported | **SUPPORTED. 34 `g_ClockTimer > 0`-style guards already in the tree** | The engine already expects frames where nothing ticks |

**And `bondview2.c` — the VIEW code, which `99` §2 names as the actual target
(*"the judder is THE VIEW being sampled at 60"*) — is the heaviest consumer of
the FLOAT delta: 75 of the 217.**

> ## **THE ENGINE IS ALREADY PREDOMINANTLY FLOAT-TIMESTEP. NOBODY IN THIS PROJECT HAD LOOKED.**

---

## §2 — THE CHOKE POINT IS TWO LINES

```c
/* game/lv.c:974-979 */
g_ClockTimer       = speedgraphframes;        /* integer 60ths */
g_GlobalTimerDelta = (f32) g_ClockTimer;      /* the float, currently just a CAST */
```

**And `speedgraphframes` comes from one place —
`frametiming.c:46-53`, `updateFrameCounters(s32 deltaFrames)` — fed by:**

```c
/* frametiming.c:75-89 */
nextFrameTime = ((osGetCount() - base) + 387937) / 775875;   /* <- INTEGER DIVIDE.
                                                                THE REMAINDER IS DISCARDED. */
```

> ## **THAT ONE INTEGER DIVISION IS THE WHOLE OF `92`'s "90 Hz IS STRUCTURALLY UNAVAILABLE".**

**`currentFrameCounter` is contained entirely in `frametiming.c/h` — 8
references, nothing outside the file. It does not spread.**

---

## §3 — THE CHANGE

**Three edits. That is the honest core of it.**

1. **Carry the remainder** in `waitForNextFrame` / `updateFrameCounters`, so the
   elapsed time is accumulated at fine resolution and `deltaFrames` comes out as
   0, 1, 1, 0, 1... averaging 2/3 at 90 Hz instead of being truncated.
2. **`g_GlobalTimerDelta` becomes the FRACTIONAL delta** instead of a cast of
   the integer. At 90 Hz it reads a steady ~0.667 every frame.
3. **Audit the 34 integer guards** for anything CONTINUOUS hiding behind them.

**AND THE UNIT NEVER CHANGES.** `g_ClockTimer` stays an integer count of 60ths.
**All 152 references keep working. Every "N sixtieths" duration constant keeps
working.** The sub-step loops (`for (i = 0; i < g_ClockTimer; i++)`, seven of
them) run 0 or 1 times instead of always 1 — **which is the correct behaviour,
not a regression.**

**That is `99` §4's headline cost — "the hundreds of duration constants" —
evaporating, exactly as `117` §4.2 predicted from PD's structure.**

### §3.1 — WHAT IT BUYS, STATED PLAINLY

**At 90 Hz: everything DISCRETE ticks at its natural 60, and everything
CONTINUOUS — camera, view, velocity, sway — moves at 90.**

**Which is `99` §2's target exactly:** *"the judder is not the game simulating at
60, it is THE VIEW being sampled at 60."* **The view is float-driven, 75 sites in
`bondview2.c`.**

---

## §4 — THE RISKS, NAMED

| Risk | Assessment |
|---|---|
| **The 34 integer guards** | **THE REAL AUDIT, and it is bounded at 34 sites.** The danger is code using an INTEGER guard to gate a CONTINUOUS quantity. **A worked example already exists: `gunfire.c:202-205` divides by `g_GlobalTimerDelta` INSIDE `if (g_ClockTimer > 0)`.** At 90 Hz that skips a third of the frames that had real elapsed time. Those move to the float |
| **44 divisions by `g_GlobalTimerDelta`** | **Lower risk than today, not higher.** A fractional delta is small-but-nonzero more often than an integer one is nonzero |
| **AIM FEEL — `92`'s main objection** | **DEFUSED, AND IT BECOMES A CHOICE.** `crosshair_x_pos` steps per `g_ClockTimer`. **Leave it integer and the weapon feel is bit-identical to today.** Move it to the float only if smooth aim is wanted. **`92` treated this as a forced consequence; it is not** |
| **Unknown unknowns** | **Real.** It is a decompilation and something will assume `deltaFrames >= 1`. **Bounded by §5's gate, which costs no headset** |
| **`waitForNextFrame` is a BUSY-WAIT** spin on `osGetCount` | **A separate, real piece of work.** Under VR the pacing should come from `xrWaitFrame`, which is what PD does (`117` §1). **Not required for slice 1** |

---

## §5 — AND THE DE-RISKER THAT CHANGES EVERYTHING

> ## **THIS CAN BE VALIDATED ENTIRELY ON THE MONITOR. NO HEADSET. NO VR. NO GPU CONTENTION.**

**`.\vr.ps1 -NoXr` already presents at 90** — `rr_option: "Manual"`,
`rr_manual_value: 90` — and `106` §7 established that path shows the same frames
and looks correct.

**So the whole timebase change is testable with `-NoXr` on the desktop:** does
the game still play correctly, do timers still expire at the right wall-clock
moment, does the view move more smoothly. **Every VR-specific risk — B3's
bugchecks, the reboot cost, the headset, the wearer's time — is OFF the critical
path for the entire first slice.**

**Nothing else in this project has had that property. It is the cheapest large
change available.**

---

## §6 — THE VERDICT

**`92` said 90 Hz was structurally unavailable and no amount of PC would move
it. That is TRUE of a truncating timebase.** `99` costed the migration at
hundreds of duration constants. **`117` showed PD ships the accumulating version
of the same engine. This read shows we already have both halves of PD's design
and are missing only the accumulator.**

> ### **RECOMMENDATION: THIS IS A SLICE, NOT A PROJECT. IT IS WORTH BUILDING, AND IT IS SMALLER THAN THE PER-PASS HEAD POSE WORK IT WOULD REPLACE.**

**Because it does not just fix the head turn. It deletes, at once:**

- the duplicate frame (`93`, `112`, `116`) — there are no duplicates if every frame is real
- the per-pass head pose problem (`114` §3) — one pose per frame, like PD
- the pose/image mismatch (`93`) — the image is rendered from the pose it is submitted with
- the interpolator's partial-interpolation artefacts (`23`, `92` candidate 2)
- and `109`'s pacing question changes shape entirely

**AGAINST: it is the deepest change this project has attempted, into
decompiled code, and `48` rule 1 says plan and discuss before executing.**

---

## §7 — SLICE 1, IF THE OWNER SAYS GO

**Gates before code, `86`'s discipline.**

| | |
|---|---|
| **T1-S0** | **An instrument first.** Log `deltaFrames`, `g_ClockTimer` and `g_GlobalTimerDelta` once a second, with min/max — **on the CURRENT build.** We have never seen these numbers. **G: at `-NoXr` 90, `deltaFrames` should read a steady 1 and `g_GlobalTimerDelta` a steady 1.0. If it does not, the model in this document is wrong before a line is changed** |
| **T1-S1** | **The accumulator, knob-gated** (`GE_VR_TIMEBASE=1`). Unset = today, exactly | **G: at 90, `g_ClockTimer` averages 2/3 and `g_GlobalTimerDelta` reads ~0.667 steady. `-NoXr`, no headset** |
| **T1-S2** | **The 34-guard audit**, driven by what S1 actually breaks rather than by reading all 34 first | **G: a level plays correctly at `-NoXr` 90. Timers expire at the right wall-clock time** |
| **T1-S3** | **Only then, VR.** | **G: the wearer. `95`** |

**T1-S0 costs almost nothing and can invalidate the whole document. It ships
first.**
