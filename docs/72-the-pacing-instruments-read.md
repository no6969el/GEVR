# 72 — the pacing instruments, READ for the first time. O2 is not a submit-stage overrun.

**2026-08-23, later session. No code, no launch — this is a read of
`ge-vr-shots\gevr-FIX70-WORN-150514.log`, the worn session in which B1 was
confirmed fixed (`71`).**

`71` O2 said, of the two pacing instruments: *"Both instruments already exist
and print every second. Nobody has read them for pacing."* **They have now been
read. This is what they say, and it is not what O2 assumed.**

---

## THE MEASUREMENT

516 one-second samples from the worn session, `[gevr-xr] frame budget:`:

```
runtime display period   11.11 ms  (90.0 Hz)          <- the budget

our frame, per-second mean over 516 samples
    min       6.40 ms
    median   10.23 ms
    p90      10.30 ms
    max      18.80 ms
    samples over 11.11 ms:  1  of  516
```

The stage breakdown, `[gevr-xr] stage ms:`, is flat across the whole session:

```
waitFrame  ~8.9    locate  ~1.1    waitForGpu  0.00
record      0.01   execute  0.02   endFrame    0.25
```

**Roughly 8.9 of every 10.2 ms is spent BLOCKED inside `xrWaitFrame`, and our
own work — record, execute, endFrame — is about 0.3 ms.**

## WHAT THAT MEANS, USING THE CODE'S OWN DECISION TABLE

`ge_vr_xr.cpp:1090-1105` wrote the branches before the instrument ever ran, which
is exactly `48`'s rule. Its first branch:

> *`waitFrame` large -> the runtime is pacing us. We are EARLY, not slow, and 60
> is a cadence rather than a limit. Nothing to optimise; find the headset's real
> rate.*

**That is the branch the data selects, and it selects it unambiguously.** The
other three stages are at or near zero. `waitForGpu` is **0.00**, so the drain
`49` O23 worried about is not costing anything here either.

**So: the XR submit loop is not the judder.** It is idle, waiting for the
compositor, ~87% of every frame.

## AND THE HONEST LIMIT OF THIS INSTRUMENT — read this before quoting the above

**Every number it prints is a MEAN over ~90 frames.** `reportStages()` divides
accumulated totals by `g_stage.frames`.

**Judder is not a mean. Judder is outliers.** Ninety frames of which one takes
40 ms and eighty-nine take 9.8 ms average to 10.1 ms and this instrument reports
a healthy session. **A mean cannot see a hitch, and this is the fifteenth
instrument in this project that cannot fail in the way it is being asked to.**

**What is therefore established, and what is not:**

| | |
|---|---|
| **ESTABLISHED** | The loop is not *systematically* over budget. There is no sustained overrun, and no stage is chronically expensive |
| **NOT ESTABLISHED** | That no individual frame misses. The one 18.80 ms sample is a whole second whose MEAN was 18.80 ms, which is far worse than a spike and deserves finding |
| **NOT ADDRESSED AT ALL** | Whether the images themselves are stale or duplicated between submits, which judders identically while every timing number stays perfect |

## THE NEXT MEASUREMENT — one line, before any theory

**Add `max` and a late-frame count beside the mean:**

```
frame budget: period 11.11 | mean 10.23 | max N | late N/90
```

`StageTimes` already accumulates per frame; a `std::max` and a counter are two
lines in the same struct. **`48`'s amendment applies — this is a read-only
diagnostic and may be batched with anything else.**

**Write its wrong-thing branch first, as `48` now requires:** if `max` comes
back at ~11 ms and `late` at 0 while the headset visibly judders, **the timing
is not the fault and the images are** — which sends this at the 60/90 content
question below rather than at the loop.

## THE OTHER HALF, WHICH THIS DOES NOT TOUCH

`60` established the `60.0 fps` line is the emulated **N64 VI clock**, not the
PC framerate. In the same log, `render passes: eye0=90 eye1=90` — **the renderer
produces 90 eye images per second from a 60 Hz game**, via interpolation.

**So the 60->90 gap is being filled, and by interpolation.** That makes the
remaining judder candidates:

1. **Interpolation quality** — what the in-between images actually contain.
2. **The pose each submitted image carries** — a fresh pose on a stale image, or
   a stale pose on a fresh one, both judder.
3. **Per-frame spikes** the mean is hiding, per the section above.

**None of these is diagnosed here and none should be guessed at.** `12` §5's
deferred frame-pacing interlock is the standing debt behind all three.

---

## TWO OTHER THINGS THIS LOG SAYS, recorded so they are not lost

### `render passes` goes to `eye1=0` at the END of the session

```
461 samples   eye0=eye1=distinctTargets   (90 / 91 / 92)
 18 samples   0 / 0 / 0                   (the start - menu, before a level)
 23 samples   eye0=90.. eye1=0 distinct=0 (the END of the session)
```

**Consistent with the menu producing no stereo workloads**, which is what the
start of the log also shows — but it is stated here as an OBSERVATION, not a
diagnosis. It sits next to `45`/O45, "quit to menu goes black", and nobody has
checked whether they are the same thing.

### `EYETGT: *** DIVERGED ***`, sustained, on a session that worked

```
EYETGT: builtAt=0x003B5000 current=0x003DA800 *** DIVERGED *** | rebuilds=1
```

**`65` built this line as a whole hypothesis: `builtAt != current` was supposed
to be the fault.** It reads DIVERGED for essentially the entire worn session in
which **stereo demonstrably worked**, one rebuild having already happened.

**So either the divergence is benign after a rebuild, or the line is reporting a
stale `builtAt`.** Either way, **a red banner that prints on a healthy session
is worse than no banner** — it is the next thing to mislead somebody. Not fixed,
not diagnosed, recorded.
