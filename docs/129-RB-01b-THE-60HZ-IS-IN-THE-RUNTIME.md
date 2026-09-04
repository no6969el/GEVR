# 129 — RB-01b. THE 60 Hz IS IN THE RUNTIME, HARDCODED, AND IT IS NOT IN THE GAME AT ALL.

**2026-08-24. `126`'s RB-01b, DONE. A read. It moves the primary edit out of the
game and into the runtime, and it corrects `128` in one place.**

---

## §1 — WHERE THE RETRACES COME FROM

**`lib/N64ModernRuntime/ultramodern/src/events.cpp`, `vi_thread_func()`:**

```cpp
auto next = ultramodern::get_start()
          + (total_vis * 1000000us) / (60 * ultramodern::get_speed_multiplier());   /* :123 */
...
uint64_t new_total_vis =
    (ultramodern::time_since_start() * (60 * ultramodern::get_speed_multiplier()) / 1000ms) + 1;  /* :139 */
...
osSendMesg(PASS_RDRAM events_context.vi.mq, events_context.vi.msg, OS_MESG_NOBLOCK);
```

> ## **THE VI THREAD TICKS AT A HARDCODED 60. THAT IS THE ORIGIN OF THE ENTIRE 60 Hz CADENCE, AND IT IS NOT IN THE GAME.**

**`bossMainloop` waits on those messages. `waitForNextFrame` divides real elapsed
time into 1/60ths. NEITHER CAN PRODUCE MORE THAN 60 TICKS A SECOND, BECAUSE ONLY
60 RETRACES ARRIVE.**

**Every previous costing of Route B — `92`, `99`, `118`, `127`, `128` — looked
only at the game. The clock is upstream of all of it.**

---

## §2 — `speed_multiplier` IS NOT THE LEVER

**`ultramodern/src/timer.cpp`:**

```cpp
constexpr uint32_t speed_multiplier = 1;                       /* :17 */
constexpr uint32_t counter_per_ms   = 46'875 * speed_multiplier; /* :19 */
```

**It is a compile-time constant, and it scales BOTH the VI rate AND the
`osGetCount` counter rate.** Raising it to 1.5 would tick the VI at 90 *and*
make `osGetCount` run 1.5x faster — **so the game would simply run at 1.5x
speed in real time.** That is a fast-forward, not a higher frame rate.

> **THE LEVER IS THE LITERAL `60` AT `events.cpp:123` AND `:139`, DECOUPLED FROM
> `counter_per_ms`.** Tick the VI at 90 and leave the counter at 46,875, and
> real time still measures correctly while three retraces arrive per two
> sixtieths.

---

## §3 — WHAT THEN HAPPENS, TRACED THROUGH

**With retraces at 90 Hz and `counter_per_ms` untouched:**

| Stage | Behaviour |
|---|---|
| **`osGetCount`** | **Unchanged.** `time_now()` is real elapsed time x 46,875/ms. It never knew about the VI rate |
| **`bossMainloop`'s skip gate** | `MAIN_LOOP_TICK_INTERVAL` = 387,937 counts = **8.28 ms**. Retraces would arrive 11.11 ms apart. **11.11 > 8.28, so the gate PASSES them.** |
| **`waitForNextFrame`** | `nextFrameTime = (elapsed + 387937) / 775875` — 775,875 counts = **16.55 ms**, i.e. 1/60. At 11.11 ms it yields **0**, and `while (nextFrameTime < frameDelay)` with `frameDelay == 1` **busy-waits until a whole 1/60 has passed** |

> ### **SO THE TRUNCATION IN `waitForNextFrame` IS WHAT WOULD RE-IMPOSE 60, AND IT IS EXACTLY WHAT RB-02'S ACCUMULATOR IS FOR. THE PIECES FIT.**

### §3.1 — AND IT CORRECTS `128`

**`128` §2.3 warned that `bossMainloop`'s skip gate would "re-impose 60 whatever
gate 2 does". THAT IS WRONG.** Its threshold is **half** a frame, not a whole
one — a guard against retraces arriving too close together, not a 60 Hz
quantiser. **At 90 Hz retraces it passes everything.**

**`128`'s edit (b) is therefore probably UNNECESSARY.** Rule 10. It should still
be *watched* on the first run, because `demoMode` has its own multiplied
threshold (`MAIN_LOOP_TICK_INTERVAL * speedgraphframes * 2`) and that one is not
half a frame.

---

## §4 — THE CORRECTED RB-02

| | Where | What |
|---|---|---|
| **1. THE CLOCK** | `ultramodern/src/events.cpp:123`, `:139` | **Tick the VI thread at the target rate instead of the literal 60. Do NOT touch `counter_per_ms`.** This is the primary edit and nobody had identified it |
| **2. THE TRUNCATION** | `patches/fps.c`, the `#if 0` `waitForNextFrame` | Carry the remainder so `deltaFrames` comes out 0, 1, 1 instead of busy-waiting for a whole 1/60. **The patch is already written against the right constants** |
| **3. THE FLOAT** | `lv.c:979` | `g_GlobalTimerDelta` fractional. RB-03, unchanged |
| **4. WATCH, DO NOT PRE-EDIT** | `bossMainloop`'s skip gate | Passes 90 Hz retraces by arithmetic (§3). **`demoMode`'s variant is the one to watch** |

---

## §5 — TWO THINGS TO BE CAREFUL ABOUT

### §5.1 — THE LICENCE. RULE 12.

**`N64ModernRuntime` is GPL-3.0.** `PUBLISH-MANIFEST.md`'s split puts the recomp
host (which already links it) on the GPL side and `lib/rt64/` on the MIT,
upstreamable side.

> **Editing `events.cpp` is fine for us and is NOT upstreamable to RT64.** It
> must not leak into the MIT half. **This is the first Route B edit that touches
> the licence boundary and it should be recorded in `PUBLISH-MANIFEST.md` when
> made.**

### §5.2 — THE VI THREAD IS `ThreadPriority::Critical`

Its own comment: *"This thread should be prioritized over every other thread in
the application, as it's what allows the game to generate new audio and gfx
lists."* **Raising its rate by 50% raises the wake rate of the
highest-priority thread in the process.** `105` §3 measured that we are not CPU
bound, so this is very likely free — **but it is the kind of change that is free
until it is not, and `109`'s `LATE` counter is already in place to see it.**

---

## §6 — WHAT THIS DID NOT ESTABLISH

**Whether the audio path is tied to the VI rate.** The comment above says the VI
thread is what lets the game generate **audio and gfx** lists. **If audio
buffering is sized or paced per VI, a 90 Hz VI could change audio timing.**

> **Filed as RB-01c. A read, no machine.** It is cheaper to ask now than to
> spend a wear test wondering why the music sounds wrong.
