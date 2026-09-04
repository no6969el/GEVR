# 137 — THE NINETY MAY BE A FAST-FORWARD. `134` IS PROVISIONALLY RETRACTED.

**2026-08-24, late. A hypothesis with a cheap decisive test, written down before
the test rather than after.**

---

## §1 — THE FACT THAT WILL NOT GO AWAY

`136` found a real bug — `static` helpers in patch code are never emitted — and
fixing it made `geVrTickInstrument` appear in `RecompiledPatches/patches.c`.

**AND THE UNCONDITIONAL MARKER STILL PRINTED ZERO TIMES.**

**The entire chain is verified present in the emitted C:**

```
bossMainloop -> waitForNextFrame -> geVrTickInstrument -> recomp_puts
   YES              YES                   YES                 YES
```

`geVrTickInstrument` is emitted, calls `recomp_puts`, and is called twice from
`waitForNextFrame`, which is itself called from `bossMainloop`. **All four links
confirmed by reading the recompiler's own output.** And nothing prints.

> **THE REMAINING EXPLANATION IS THAT `waitForNextFrame` IS NOT EXECUTING AT
> RUNTIME.**

---

## §2 — AND IF IT IS NOT EXECUTING, THE 90 IS NOT WHAT WE THINK

**`updateFrameCounters` is called from `waitForNextFrame` and nowhere else on
this path.** If `waitForNextFrame` never runs:

- **`updateFrameCounters` never runs.**
- **`speedgraphframes` keeps its static initialiser — `frametiming.c:11`,
  `s32 speedgraphframes = 1;`**
- `lvlManageMpGame` does `g_ClockTimer = speedgraphframes` -> **1, every frame.**
- The loop iterates once per retrace, and retraces now arrive at **90 Hz**.

> ## **90 ITERATIONS x 1 TICK = 90 SIXTIETHS OF GAME TIME PER SECOND. THE WORLD RUNS AT 1.5x REAL SPEED.**

**THIS IS EXACTLY WHAT `129` §2 WARNED ABOUT** — *"raising it would tick the VI at
90 and make osGetCount run 1.5x faster, so the game would simply run at 1.5x
speed. That is a fast-forward, not a higher frame rate."* **We avoided that
mechanism and appear to have arrived at the same destination by another road:
not by scaling the counter, but by removing the gate that converted retraces into
ticks.**

### EVERY OBSERVATION FITS, INCLUDING THE ONES ALREADY BANKED

| Observation | Fast-forward predicts |
|---|---|
| fps 59.3 -> 88.7 | **YES** — the loop runs per retrace, unthrottled |
| marker never prints | **YES** — `waitForNextFrame` never runs |
| `timebase: delta=1 [1..1] clk=1 [1..1] gdelta x1000=1000` | **YES, AND IT WAS TELLING THE TRUTH** |
| audio "sounded normal" | **YES** — audio is 30 frames/s off the retrace divisor, independent of game ticks |
| pause "stopped dead" | **YES** — pause zeroes `g_ClockTimer` regardless |
| ***"I felt like I was running faster in the second run"*** | **YES. THE WEARER MEASURED IT FIRST.** |

### WHAT THIS RETRACTS

> **`134` §1: *"A mean of 87-89.5 is only reachable if the remainder accumulator
> is running."* THAT IS WRONG AND IS WITHDRAWN.** It is equally reachable by not
> gating the loop at all. **I treated one hypothesis as the only one, which is
> `48` rule 4 and the specific mistake `106` §2 accused `103`/`104`/`105` of.**

**And `134` §2 called the `timebase` line blind. It printed once, which is a real
defect — but its single sample may have been CORRECT all along**, and it was
dismissed because it disagreed with a number I had already decided to believe.

---

## §3 — TWO TESTS. NEITHER NEEDS THE INSTRUMENT TO WORK.

### TEST 1 — THE STOPWATCH. NO CODE, NO BUILD, DECISIVE.

**Time an in-game countdown against a real stopwatch, at `-ViRate 90`.**

> **60 in-game seconds in ~40 real seconds -> THE WORLD IS RUNNING AT 1.5x AND
> THIS DOCUMENT IS RIGHT.** 60 in ~60 -> the timebase is sound and the missing
> marker is a separate, smaller problem.

**This is the test `131` §5 listed as G-131-4 and nobody has run.** It does not
depend on a single line of instrumentation, and it should have been the first
gate rather than the fourth.

### TEST 2 — MARKER-A, ALREADY BUILT

`geVrViRate` now carries an unconditional marker. **`bossMainloop` calls it
directly** for `gEXSetRefreshRate` — a path independent of `waitForNextFrame`.

- **MARKER-A PRINTS** -> `recomp_puts` works from this file, and
  **`waitForNextFrame` is genuinely not executing.** §2 is the live hypothesis
  and the fix is to find out why.
- **MARKER-A DOES NOT PRINT** -> **nothing in this translation unit can print**,
  the fault is in emission or relocation rather than control flow, and §2 loses
  its main support — the fps would then need another explanation.

---

## §4 — AND A NEW BUG, REPORTED FROM THE SAME SESSION

**Mashing A through the boot menus crashes the game.** The owner: *"typically
that wouldn't be what someone does, but I don't think it should do that."* Agreed
— it is a real defect regardless of how it is provoked.

**THE FIRST QUESTION IS WHETHER IT IS OURS.** It must be tried at stock
(`.\vr.ps1 -NoXr`, no `-ViRate`). **Pre-existing -> it belongs with B3/B4 in
`39`. Only at 90 -> RB-02 caused it and it blocks the slice.**

**AND THERE IS A SPECIFIC SUSPECT IF IT IS OURS.** `patches/audio.c`'s
`musicTrack1Play` / `musicTrack2Play` contain:

```c
while (alCSPGetState(g_musicXTrack1SeqPlayer)) { yield_self_1ms(); }
```

**A spin waiting on the sequence player to stop.** Fast menu navigation starts
and stops music tracks as quickly as the player can press, and **RB-02 changed
the audio cadence** — `__scHandleRetrace` now notifies the audio client every
third retrace instead of every second (`130`). The audio frame rate is unchanged
at 30/s by design, **but the phase relationship between menu input and audio
frames is not**, and a spin-wait on another thread's state is exactly the shape
that turns a phase change into a hang or a crash.

**Speculative, and named so it can be tested rather than believed.** `130` §5
already flagged `musicFadeTick` as running 1.5x fast at 90 — the music path is
the part of RB-02 with the most behaviour riding on cadence.

---

## §5 — WHAT IS SOLID, AFTER ALL OF THIS

**The VI thread ticks at 90.** That is `129`'s edit and nothing here questions it.

**Everything downstream of it is now in doubt until Test 1 runs.** The honest
summary of this slice: **one real bug found (`136`), one real gap in the build
closed (`133`), one measured baseline banked (`133` §1), and a headline result
that may be a fast-forward wearing a frame rate's numbers.**

**The wearer said it first, in plain language, and it took a document to catch
up.** `95`, `98` and `124` are the same story. **When the person wearing it
reports a behaviour, that is data, and it outranks a log every time.**
