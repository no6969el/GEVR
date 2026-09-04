# 130 — RB-01c. YES, THE AUDIO IS PACED BY THE VI. AND THE FIX IS ONE DIVISOR.

**2026-08-24. A read. No machine, no headset, no build.** `126` RB-01c asked
whether the audio path is tied to the VI rate, because `129` found the VI rate
is the lever and `vi_thread_func`'s own comment says it is what lets the game
generate **audio and gfx** lists.

> ## **THE ANSWER IS YES — AND IT IS WORSE AND SIMPLER THAN EXPECTED. THE AUDIO
> ## FRAME IS DRIVEN BY THE RETRACE, DIVIDED BY TWO. AT 90 Hz THAT DIVISOR IS
> ## WRONG AND THE GAME PRODUCES ~1.47x MORE SAMPLES THAN THE DAC CONSUMES.**
>
> ## **AND 90 DIVIDES BY 3 EXACTLY AS 60 DIVIDES BY 2. `90/3 == 60/2 == 30`.
> ## CHANGE THE DIVISOR AND THE AUDIO CADENCE IS BIT-IDENTICAL TO TODAY.**

---

## 1. THE CHAIN, END TO END

Five links, all read this session:

1. **`ultramodern/src/events.cpp` `vi_thread_func`** — ticks at the hardcoded
   `60` (`129`) and sends `OS_SC_RETRACE_MSG` to `events_context.vi.mq` once per
   `vi.retrace_count` ticks.
2. **`sched.c:181`** — `osViSetEvent(&sc->interruptQ, VIDEO_MSG, numFields)`,
   and **`init.c:32` `#define NUM_FIELDS 1`**. So `retrace_count == 1`: **every
   VI tick becomes a `VIDEO_MSG`.** The VI rate IS the retrace rate, 1:1.
3. **`sched.c:312` `__scHandleRetrace`** — `sc->frameCount++`, then walks the
   client list:

   ```c
   for (client = sc->clientList; client != 0; client = client->next) {
       if ((*((s32*)client + 2) == 0) || ((sc->frameCount & 1) == 0)) {
           osSendMesg(client->msgQ, &sc->retraceMsg, OS_MESG_NOBLOCK);
       }
   }
   ```

   **`audi.c:427` registers the audio client with `next == 1`**, so the first
   disjunct is false and **the audio client is notified on EVERY OTHER RETRACE —
   30 times a second.**
4. **`audi.c` `amMain`** blocks on `frameMessageQueue` and calls
   `amHandleFrameMessage` per message.
5. **`amHandleFrameMessage` (`audi.c:517`)** decides how many samples to
   synthesise:

   ```c
   info->frameSamples = ((g_FrameSize - (osAiGetLength() >> 2)) + 16 + EXTRA_SAMPLES) & ~0xf;
   if (info->frameSamples < g_MinFrameSize) info->frameSamples = g_MinFrameSize;
   ```

## 2. THE ARITHMETIC, AND WHY IT IS EXACT TODAY

`audi.c:19,26,30,342`:

```
OUTPUT_RATE              0x5622 = 22050 Hz
MAYBE_FRAME_RATE         60
FRAMES_PER_FIELD_AS_POW2 1                    /* i.e. x2 */
g_FrameSize = ceil16(22050 * 2 / 60) = 735 -> 736 samples
g_MinFrameSize = g_FrameSize - 0x10
```

**30 audio frames a second x 735 samples = 22050 samples a second.** The audio
frame rate and the sample budget are two halves of one identity, and the
`osAiGetLength` term is only a small servo correcting VI jitter around it —
exactly what the function's own inherited comment says: *"audio is synchronised
off of the video interupt."*

## 3. WHAT BREAKS AT 90

Retraces 90/s -> `frameCount & 1` fires **45** audio frames a second.
`osAiGetLength` grows, so the servo drives `frameSamples` down — **and hits its
floor at `g_MinFrameSize` = 720.** It cannot go lower.

> **45 x 720 = 32,400 samples a second into a 22,050 Hz DAC. A PERMANENT 1.47x
> OVERPRODUCTION THAT THE GAME'S OWN THROTTLE CANNOT CORRECT, BECAUSE THE FLOOR
> IS BELOW IT BY CONSTRUCTION.**

**And the host does not absorb it silently.** `src/main/main.cpp:238`:

```c
uint32_t skip_factor = cur_queued_microseconds / 100000;
if (skip_factor != 0) { /* decimate by 1 << skip_factor */ }
```

Over 100 ms queued, the host **decimates the incoming stream by 2, 4, 8...** —
nearest-neighbour sample dropping with no filter. **So the symptom would not be
"latency drifts"; it would be aliased, hashy, intermittently pitch-broken
audio**, and the sequence players would run fast between decimations because
`alAudioFrame` advances the synth by the sample count it is handed.

**This is the kind of fault that gets blamed on the headset, the driver or the
build, and it would have cost a wear test. RB-01c earned itself.**

## 4. THE FIX — ONE DIVISOR, AND IT IS EXACT

**60/2 = 30. 90/3 = 30.** The audio frame rate does not have to change at all.

> ### **GATE THE AUDIO CLIENT ON `frameCount % 3 == 0` INSTEAD OF `frameCount & 1` WHEN THE VI RUNS AT 90.**

Then: 30 audio frames a second, `g_FrameSize` unchanged at 736, `g_MinFrameSize`
unchanged, `osAiGetLength` servo unchanged, sequence tempo unchanged, DAC rate
unchanged. **The audio path becomes cadence-identical to the shipping build.**

**Do NOT instead rescale `MAYBE_FRAME_RATE` to 90.** It "works" arithmetically
(45 x 490 = 22,050) but it moves `g_FrameSize`, `g_MinFrameSize`,
`g_MaxFrameSize`, the `EXTRA_SAMPLES` margin and every audio heap allocation
sized off `g_MaxFrameSize`, and it puts the synth on a 22.2 ms cadence it has
never run at. **The divisor change touches one comparison and nothing else.**

**WHERE:** `sched.c:334`, in `__scHandleRetrace`. It is game code, so it is a
`RECOMP_PATCH`, not a runtime edit — **no licence boundary here, unlike RB-02**
(`129`, rule 12).

**KNOB IT WITH RB-02.** The divisor is only correct at 90; at 60 it must stay 2.
One knob must set both the VI rate and this divisor, or the two disagree and the
audio breaks in the opposite direction (30 -> 20 audio frames a second).

## 5. AND THREE MORE PER-RETRACE TICKERS IN THE SAME FUNCTION — WATCH, DO NOT PRE-EDIT

`__scHandleRetrace` also calls, unconditionally, every retrace:

| Call | Unit | At 90 |
|---|---|---|
| **`musicFadeTick()`** (`music.c:1351`) | `g_musicXTrack1FadeRemainingFrames`, decremented per call | **fades complete 1.5x faster** — audible on level -> pause-watch transitions |
| **`viVsyncRelated()`** (`fr.c:239`) | `g_ViShakeTimer`, decremented per call | **screen shakes 1.5x shorter** |
| `joyPoll()` | none | polls 1.5x more often — harmless, arguably better |
| `speedgraphMarkerUpdate()`, `CheckDisplayErrorBufferEvery16Frames()` | debug | irrelevant |

**None of these is a blocker and none should be pre-edited** — `126`'s RB-04
discipline: fix what RB-02 actually breaks, when it breaks. **But `musicFadeTick`
is the one a wearer will notice, and it is now written down so nobody spends an
evening on it.**

## 6. ONE NEGATIVE, AND IT REMOVES A WORRY

**`vi_thread_func` sends the AI message on EVERY tick, outside the
`remaining_retraces == 0` gate** (`events.cpp:167`). That looked like a second,
ungated audio path.

**It is dead code for us: GoldenEye never calls `osSetEventMesg(OS_EVENT_AI, ...)`.**
`sched.c:178-180` registers SP, DP and PRENMI only. So
`events_context.ai.mq` stays `NULLPTR` and the send is skipped. **The retrace
path in §1 is the ONLY audio pacing in the build.**

## 7. WHAT THIS DOES TO RB-02

**It does not block it and it does not change the primary edit.** It adds one
line to it, and it is the reason RB-02 must be a single knob rather than a
runtime-side edit made in isolation:

> **RB-02's knob must set (a) the VI tick rate in `events.cpp` and (b) the audio
> client divisor in `sched.c` TOGETHER. Either one alone is a broken build.**

**Gate, and it needs no headset:** at `-NoXr` 90, audio plays at correct pitch
and tempo with no hashing, and the host never enters the `skip_factor` branch.
**A 30-second attract-mode listen answers it.**
