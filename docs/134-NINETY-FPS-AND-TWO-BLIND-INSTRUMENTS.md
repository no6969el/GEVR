# 134 — IT RUNS AT NINETY. AND BOTH OF THE GATES I NAMED ARE BLIND.

**2026-08-24, 17:27 and 17:29. The first two runs of a binary that actually
contains RB-02 and RB-03** (`GoldenRecomp.exe` 17:23:47, after the source at
17:02 and `patches.elf` at 17:13 — checked, because `133` happened).

---

## §1 — THE HEADLINE, AND IT IS NOT A SMALL ONE

| | baseline (`133` §1) | **`-ViRate 90`** | **`+ -FloatDelta`** |
|---|---|---|---|
| fps samples | 140 across two runs | 129 | 123 |
| **fps mean** | **59.2 / 59.3** | **87.1** | **89.5** |
| fps max | 61.6 / 61.1 | **91.6** | **91.6** |
| fps min | 20.2 / 17.0 (load) | 45.0 | 49.2 |

> ## **THE SIM COMPLETES ~90 FRAMES A SECOND. IT HAS RUN AT 60 FOR THIS PROJECT'S ENTIRE LIFE.**

**And the owner, unprompted, on the second run: *"wow runs so good"*.**

**G-131-2 PASSES, and it passes in a way that cannot be an artefact.** If
`waitForNextFrame` were still truncating and busy-waiting for a whole 1/60, the
loop would cap at ~60 no matter what the VI thread did — that is `129` §3's whole
point. **A mean of 87-89.5 is only reachable if the remainder accumulator is
running.** The fps counter is an independent instrument that predates all of this
and it is measuring the thing Route B set out to change.

**`92` IS ANSWERED.** *"90 Hz is structurally unavailable... not a performance
limit; no amount of PC moves it."* **It was a truncating divide and a hardcoded
`60` in a file nobody had opened.**

---

## §2 — AND NOW THE PART THAT IS NOT A CELEBRATION

**Both gates I named in `131` and `132` returned the pre-change values:**

```
timebase: delta=1 [1..1] | clk=1 [1..1] | gdelta x1000=1000 [1000..1000]
```

**Identical on both runs, and identical to the baseline.** Taken at face value
that says RB-02 is not running and RB-03 is not running — **while the fps counter
says otherwise, emphatically.**

**THE FPS COUNTER IS RIGHT AND THE TIMEBASE LINE IS BLIND. HERE IS WHY:**

| | Measured |
|---|---|
| `timebase:` lines in a 50,974-line log | **ONE**, at **line 13** |
| `timebase:` lines in a 48,156-line log | **ONE**, at **line 27** |
| `[trace] retrace#... sgf=` lines | **ZERO in both runs** |

> ### **IT PRINTS ONCE, IN THE FIRST MOMENTS OF BOOT, AND NEVER AGAIN. IT IS A SINGLE SAMPLE TAKEN BEFORE THERE IS A LEVEL, AND IT IS BLIND TO EVERYTHING AFTERWARDS.**

**`126` RB-00 KNEW AND WROTE IT OFF:** *"The line prints once rather than per 90
frames — `100`'s statics trap again, not worth chasing unless it obstructs."*

> **IT NOW OBSTRUCTS. It is the only gate for RB-03 and it cannot see RB-03.**

**And `sgf=` is worse than blind — it does not exist.** The `[trace] retrace`
line lives inside `bossMainloop`'s `while (g_MainStageNum < 0 || pendingGfx)`
pre-level loop, so it prints while the game is loading and **not once during
gameplay.** `131` §5 named it as THE gate. **It could never have answered.**

**THIS IS THE FOURTH INSTRUMENT IN THIS PROJECT WHOSE NAME PROMISED MORE THAN IT
MEASURED** — `reused` (`111`), `dupSrc` knob-off (`113`), `interpUsed` (`116`),
now `timebase` and `sgf`. **`48` rule 4, and I wrote two of these gates myself
three documents ago without checking that the instrument could fire.**

---

## §3 — SO WHAT IS ACTUALLY ESTABLISHED, AND WHAT IS NOT

**ESTABLISHED:**
- **RB-02 works.** 59.3 -> 87.1 mean, by an independent counter, and no other
  mechanism can produce it.
- The build contains both slices, verified by timestamp (`133`).
- It is stable enough to play and the owner likes it.

**NOT ESTABLISHED, AND NOBODY SHOULD SAY OTHERWISE YET:**

> ### **RB-03 IS COMPLETELY UNMEASURED. Its only gate is the blind line above.**
>
> **87.1 -> 89.5 is NOT evidence for it.** RB-03 does not change the frame rate —
> it changes the *smoothness of motion within* frames. The 2.4 fps difference is
> two different play sessions and is exactly the kind of number `111` §5 warns
> against reading. **`-FloatDelta` may be doing nothing at all and these logs
> could not tell the difference.**

### §3.1 — THE THREE WEARER ANSWERS, AND THE THIRD ONE CHANGES THINGS

**G-131-3, AUDIO: PASS.** *"Sounded normal."* **`130`'s divisor is doing its
job** — 90/3 = 30 audio frames a second, the identity held, and the hashy
decimation `130` predicted did not happen. That whole read paid for itself.

**G-132-3, PAUSE: PASS.** *"World stopped dead."* **`132` §2.2's re-asked pause
test is correct** — `g_ControlsLockedFlag` / `checkGamePaused()` rather than
inferring from `g_ClockTimer == 0`, which no longer means paused.

**G-132-4: NOT SMOOTHNESS. SOMETHING ELSE, AND IT NEEDS CHASING.**

> ### ***"I FELT LIKE I WAS RUNNING FASTER IN THE SECOND RUN."***

**That is a SPEED report, not a smoothness report, and the two runs differed only
by `-FloatDelta`.** Both were already at ~90 fps, so this is not the 60 -> 90
change being felt.

**IT CUTS BOTH WAYS AND BOTH MATTER:**

1. **It is the FIRST evidence that `-FloatDelta` does anything at all.** §3 above
   said RB-03 was completely unmeasured; **this is a behavioural difference, and
   it is the only one we have.**
2. **If Bond actually moves faster, that is a CORRECTNESS BUG and it outranks
   smoothness entirely.** A Route B that runs the game at the wrong speed is not
   a Route B.

**THE ARITHMETIC SAYS IT SHOULD NOT HAPPEN, WHICH IS WHY IT NEEDS MEASURING
RATHER THAN ARGUING.** Both configurations deliver 60 sixtieths of elapsed time
per second — knob off, `(f32) g_ClockTimer` reads `0, 1, 1` and sums to 60; knob
on, `0.667` ninety times sums to 60. And the movement integrators are the
unguarded kind that sum correctly: `bondview2.c:5576`
`speedforwards += unadjustedTargetSpeed * g_GlobalTimerDelta`.

**SO THERE ARE THREE LIVE EXPLANATIONS AND NO BASIS YET TO PICK ONE:**

- **Smoother motion reads as faster.** Continuous movement at 90 Hz genuinely
  feels quicker than the same movement delivered in whole-tick steps.
- **A real speed change** down a path not yet found — a per-frame damping or
  approach term that is NOT scaled by the delta, where 90 frames a second applies
  it 1.5x as often as 60 did.
- **`48` RULE 3.** A subjective comparison across two separate play sessions, and
  **this project has broken rule 3 repeatedly, including by its own author**
  (`124`'s withdrawn latency conclusion).

**THE MEASUREMENT THAT SETTLES IT IS CHEAP AND NEEDS NO CODE:** a stopwatch
against a fixed traverse — same corridor, same route — knob on and knob off, and
G-132-2's in-game countdown against real time in both. **If the traverse times
match, it is perception; if they differ, it is a bug and it is the next thing
fixed.**
- **The head-turn half is untouched and still needs RB-07 and a headset.**

---

## §4 — WHAT IS OWED, IN ORDER

**1. FIX THE TIMEBASE INSTRUMENT. It is now the blocker, not a nicety.**
`100`'s statics trap: the once-per-90-frames counter is a `static` in
`RECOMP_PATCH` code that cannot be assumed zero, and rule 13's magic-sentinel fix
was applied to its min/max but evidently not to the print gate. **It must print
periodically DURING GAMEPLAY, not once at boot.** Until it does, RB-03 has no
gate and RB-04 has no way to be judged either.

**2. A `-FloatDelta` A/B THAT CAN ACTUALLY FAIL.** Once the line prints in-level,
`gdelta x1000` must read **~667 steady** with the knob and **1000** without it.
**That is a ten-second test and it is the whole of RB-03's evidence.**

**3. THEN the wearer questions** — audio, pause, and whether the world looks
smooth — which no log will ever answer.

**DO NOT MARK RB-03 DONE.** `126` keeps it IN PROGRESS. **RB-02 may be marked
DONE on the fps evidence**, with the note that its named gate was void and the
fps counter carried it.
