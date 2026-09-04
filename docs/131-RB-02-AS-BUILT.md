# 131 — RB-02, AS BUILT. THE SIM'S CLOCK IS NOW A KNOB.

**2026-08-24. Written, not compiled, not run.** `126` RB-02, revised by `129`
and extended by `130`. **Nine files. One knob: `-ViRate 90`.**

> ## **`.\vr.ps1 -NoXr -ViRate 90`**
> **No headset. No B3 reboot risk. No wearer time. Nothing else in this project
> has had that property** — `118`'s de-risker, and this is the slice it was for.

---

## §1 — WHAT WAS ACTUALLY CHANGED, AND WHY EACH ONE

**Four functional edits and five pieces of plumbing.**

| # | File | Change |
|---|---|---|
| **1** | `ultramodern/src/events.cpp` | **THE PRIMARY EDIT.** `vi_thread_func`'s two hardcoded `60`s (`:123`, `:139`) become `vi_hz`, read once from the new `ultramodern::get_vi_rate()`. **`counter_per_ms` is NOT touched** — `129` §2 |
| **2** | `patches/ge_vr_route_b.c` **(new)** | `waitForNextFrame`, **with the remainder accumulator**, replacing the truncating divide. Plus `__scHandleRetrace` with `130`'s audio divisor. Plus `geVrViRate()`, the game-side cache |
| **3** | `patches/workbench_theboy.c` | `gEXSetRefreshRate`'s **unguarded divide by `speedgraphframes`** — see §4, it is a correction to `127` |
| **4** | `patches/fps.c` | The dead `#if 0` `waitForNextFrame` **deleted**, not left disabled. Rule 8 |
| 5 | `ultramodern/include/ultramodern/ultramodern.hpp` | declares `get_vi_rate()` |
| 6 | `patches/syms.ld` | `recomp_ge_vr_vi_rate = 0x8F000128` |
| 7 | `patches/misc_funcs.h` | `DECLARE_FUNC(s32, recomp_ge_vr_vi_rate)` |
| 8 | `src/game/recomp_api.cpp` | the host side of that call |
| 9 | `vr.ps1` | `-ViRate`, the gates, and `GE_VR_VI_RATE` added to the clear list — rule 6 |

**`PUBLISH-MANIFEST.md` updated:** edit 1 is GPL-3.0 (`129` §5.1, rule 12).
**No RT64 file is touched by RB-02 at all**, which is the cleanest possible
answer to the boundary question.

---

## §2 — THE ACCUMULATOR, AND WHY IT IS FED MEASURED TIME

**The fault** (`frametiming.c:75-82`): `nextFrameTime = (elapsed + 387937) / 775875`
**discards the fraction**, and the `while (nextFrameTime < frameDelay)` loop then
busy-waits until a whole 1/60 has passed. At 90 Hz retraces 11.11 ms have
elapsed, which divides into **zero** whole sixtieths, **so the stock function
re-imposes 60 no matter what the VI thread does.**

**The replacement carries the remainder:**

```c
g_geVrTickAccum += elapsed;                       /* REAL counts, measured */
while (g_geVrTickAccum >= 775875 && ticks < 4) {
    g_geVrTickAccum -= 775875;
    ticks++;
}
updateFrameCounters(ticks);                       /* 0, 1, 1, 0, 1, 1, ... */
```

**It is fed MEASURED elapsed time, not an assumed period**, so it self-corrects
against jitter instead of drifting. `129` §4 predicted `0, 1, 1`; that is what
this produces, and `deltaFrames` averages exactly two thirds.

> **THE UNIT NEVER CHANGES.** `g_ClockTimer` stays an integer count of 60ths.
> **All 152 references and every "N sixtieths" duration constant keep working**
> — `117` §4.2, `118` §3, `126`. What changed is only how often that counter is
> ALLOWED to advance.

**AND THIS IS THE DIRECT ANSWER TO `92`.** *"90 is not 60 over an integer,
therefore unreachable"* **is true of a truncating timebase and false of an
accumulating one.** Perfect Dark's base unit does not divide into 90 either
(240/90 = 2.667) and they get there anyway, because `lvupdate240rem` carries the
remainder — `117`.

**The busy-wait is kept, at the target period rather than at 1/60.** In practice
it exits immediately: `bossMainloop`'s skip gate is a **half**-frame guard
(8.28 ms — `129` §3.1, correcting `128`) and has already let 11.11 ms pass before
`waitForNextFrame` is reached. **The retrace paces us; the spin is a floor, not
the pacer.** Removing it entirely is RB-06 and deliberately not in this slice.

**Two defences worth naming.** A stall (level load, window drag) is **capped at
four ticks and the backlog DISCARDED**, because banking it just fast-forwards
more slowly. And every piece of state is **self-sentinelling or magic-keyed,
never zero-initialised** — `100`'s statics trap, rule 13. `geVrViRate()`'s cache
needs no magic at all: any garbage is outside `[30, 240]` and re-reads.

---

## §3 — THE AUDIO DIVISOR, FROM `130`

`__scHandleRetrace`'s client gate `(sc->frameCount & 1) == 0` becomes
`(sc->frameCount % audioDivisor) == 0`, with `audioDivisor = rate / 30`.

**60 → 2, which is what `& 1` did. 90 → 3.** Both give **30 audio frames a
second**, and 30 x `g_FrameSize` 735 = **exactly 22050 samples/s**, the DAC rate.
**The audio path is cadence-identical to the shipping build** — same frame size,
same servo, same heap allocations, same sequence tempo.

**Why this function and not a cheaper one:** the gate lives here and nowhere
else. `osScAddClient` offers only "every retrace" or "every other" and **has no
divisor-of-three form at all**; patching `amMain` or `amHandleFrameMessage` means
dropping messages *downstream* of the decision instead of making the decision
correctly.

**Only the audio client is reached.** `init.c:246` registers the gfx client with
`next == NULL`, which satisfies the first disjunct and takes every retrace
regardless. `audi.c:427` registers audio with `next == 1`.

---

## §4 — A LIVE DIVIDE BY ZERO, AND IT CORRECTS `127`

`patches/workbench_theboy.c:659`:

```c
gEXSetRefreshRate(gdl++, 60 / speedgraphframes);
```

**`speedgraphframes` IS `updateFrameCounters`'s `deltaFrames`, which the
accumulator makes ZERO on one frame in three.**

> **`127` recorded the speed graph's divide as ALREADY ZERO-GUARDED. That is
> true of `speed_graph.c:257` — AND `127` AUDITED THE GAME TREE, NOT THE
> PATCHES. This one is in a patch, on the main render path, and it is
> unguarded.** Rule 10: recorded here rather than quietly fixed.

**The value was also wrong in a way that would have silently undone the whole
route.** `gEXSetRefreshRate` tells RT64 what rate the game produces frames at, so
it knows how many to manufacture. **Reporting 60 while the sim actually runs at
90 would have RT64 interpolate up to the panel all over again — the exact 30-in-90
fake frames Route B exists to delete.** It now reports the real rate, and the
interpolator has nothing left to do.

**`widescreen.c:11` has the identical line, is inside an `#if 0`, and is dead.**
Left alone, named here so nobody rediscovers it.

---

## §5 — THE GATES. THE FIRST FOUR NEED NO HEADSET.

```powershell
.\build.ps1
.\vr.ps1 -NoXr -ViRate 90
```

**`build.ps1` forces a full rebuild when a header changes (`115`), and this
touches `ultramodern.hpp`, `misc_funcs.h` and `syms.ld`. IF IT SAYS "SHORT
BUILD", STOP AND SAY SO.**

> **G-131-1 — THE GATE.** `sgf=` on the `[trace] retrace` line **must stop being
> flat 1.** At 90 it should read a mix of 0 and 1 averaging two thirds.
> **Still flat 1 → the accumulator is not running and nothing else in this run
> counts.** `119`'s T1-S0 line (`delta`, `clk`, `gdelta` with min/max) is the
> better instrument if it still prints: **`delta` must stop reading `[1..1]`.**

**G-131-2:** fps reads ~90, not 60.

**G-131-3 — AUDIO, and it is `130`'s whole point.** **LISTEN.** Correct pitch,
correct tempo, **no hashing and no crackle.** Wrong pitch or hashy audio means
the divisor and the VI rate disagree, and the first thing to check is that both
halves of the knob actually fired.

**G-131-4:** a level plays and **timers expire at the right WALL-CLOCK time** —
a stopwatch against an in-game countdown. Weapon fire rates unchanged. That is
RB-05 and it can batch here.

**G-131-5 — the identity check, and it is not optional.** A launch with **no**
`-ViRate` must be **indistinguishable** from before. Every path above is gated on
`rate != 60`.

> **AND "BEFORE" IS NOW MEASURED, NOT REMEMBERED.** Two unmodified `-NoXr`
> sessions were recorded at 17:08 and 17:09 on 2026-08-24 — see
> `TESTS-OWED-ON-RETURN.md`. **fps mean 59.2 / 59.3, max 61.6 / 61.1, over 140
> samples**, and `timebase: delta=1 [1..1] | clk=1 [1..1] | gdelta x1000=1000
> [1000..1000]` on both.
>
> **They were an accident** — the runs were made against a stale binary and read
> as a pass (`133`) — **and they are the most useful accident this slice could
> have had.** The two logs agree to a tenth, so the fps figure is stable enough
> that a real change will be unmistakable, and the identity gate no longer rests
> on anyone's memory of what 60 Hz looked like.

**G-131-6, WORN — RB-07.** The only gate no log can answer, and the only one
that costs a reboot.

---

## §6 — WHAT TO WATCH, AND WHAT NOT TO PRE-EDIT

**Watch, do not guard** — `126` RB-04's discipline is to fix what actually
breaks:

| | Where | At 90 |
|---|---|---|
| **`musicFadeTick()`** | `music.c:1351`, per retrace | **fades 1.5x faster.** The one a wearer would notice |
| **`viVsyncRelated()`** | `fr.c:239`, `g_ViShakeTimer` per retrace | screen shakes 1.5x shorter |
| **`demoMode`'s skip gate** | `workbench_theboy.c:636` | `MAIN_LOOP_TICK_INTERVAL * speedgraphframes * 2` — **multiplied, and with `speedgraphframes` now 0 or 1 this threshold changes shape.** `129` §3.1 named it as the one to watch and it still is |
| **`waitForNextFrame2`** | `fps.c`, **gunbarrel intro only** (`128`) | still divides by 1/60 and sets `frameDelay = speedgraphframes`, which can be 0 → the loop exits immediately → the intro free-runs at the retrace rate. Bounded, cosmetic, pre-gameplay |
| **`gunfire.c:202-205`** | RB-04's worked example | divides by `g_GlobalTimerDelta` **inside** `if (g_ClockTimer > 0)` — at 90 that skips a third of the frames that had real elapsed time. **Moves to the float in RB-03** |

**The 34 `g_ClockTimer > 0` guards already in the tree are why zero-tick frames
are safe at all** (`118`). The seven `for (i = 0; i < g_ClockTimer; i++)`
sub-step loops now run 0 or 1 times instead of always 1 — **correct behaviour,
not a regression.**

---

## §7 — WHAT THIS DOES NOT DO

**RB-03 is untouched.** `g_GlobalTimerDelta` is still `(f32) g_ClockTimer`, so it
is still integer 60ths — **217 references, 75 of them in `bondview2.c`, the
VIEW.** Until RB-03 lands, motion that integrates the float delta moves in
whole-sixtieth steps on a 90 Hz sim. **Expect it to look better than today and
not yet right.** That is the next task, not a failure of this one.

**And nothing here has been compiled.** Everything above is a read and a write.
`111` is what happens when a session believes its own numbers before the run —
and `113` is what happens when it believes them after.
