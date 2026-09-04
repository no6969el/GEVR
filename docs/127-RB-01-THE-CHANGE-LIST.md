# 127 — RB-01. THE DEFINITIVE CHANGE LIST.

**2026-08-24. `126`'s RB-01, DONE. A read of the whole timebase surface. No
machine, no build, no headset.**

> ## **THE LIST IS TWO FILES AND ABOUT A DOZEN LINES. IT IS SMALLER THAN `118` ESTIMATED AND FAR SMALLER THAN `99` DID.**

---

## §1 — `currentFrameCounter` AND ITS DERIVED COUNTERS: CONTAINED, AND MOSTLY DEAD

**All 8 references to `currentFrameCounter` are in `frametiming.c` and
`frametiming.h`. It does not leave the file.**

**And the four counters derived from it are worse than contained — they are
UNREAD:**

| | Refs | Read anywhere else? |
|---|---|---|
| `halfFrameCounter` | 4 in `frametiming.c`, 1 extern in `.h` | **NO** |
| `isFrameCounterOdd` | 2 + extern | **NO** |
| `lastFrameCounter` | 2 + extern | **NO** |
| `halfMinusPreviousCounter` | 2 + extern | **NO** |

**Every one is `extern`-declared in the header and consumed by nothing in the
tree.** That is `32`'s shape — quantities announcing an interface nobody uses.

> **CONSEQUENCE FOR RB-02: they can be left exactly as they are.** They are
> computed from `currentFrameCounter` and read by nobody, so whatever the
> accumulator does to the counter cannot break a consumer that does not exist.
> **Do not "fix" them and do not delete them** — deleting is a change with no
> benefit, and `42` is what happens when you build for a caller that is not
> there.

---

## §2 — `frameDelay` IS NOT IN THE NTSC PATH

`frameDelay` escapes `frametiming.c` exactly once, into `boss.c`:

```c
/* boss.c:60, PAL */    #define MAIN_LOOP_TICK_INTERVAL frameDelay * (CYCLES_PER_FRAME - 6450U) - ...
/* boss.c:68, NTSC */   #define MAIN_LOOP_TICK_INTERVAL (INTERVAL_INTER_MATH - 2688U)   // 387,937
```

**On NTSC — which is what we run — `MAIN_LOOP_TICK_INTERVAL` is a CONSTANT and
does not reference `frameDelay` at all.** Its one consumer is `boss.c:472`,
`if (mainTickElapsed < MAIN_LOOP_TICK_INTERVAL)`.

> **CONSEQUENCE: RB-02 does not have to reason about `frameDelay` on our build.
> IT MUST NOT ASSUME THAT FOR PAL.** If this ever ships PAL, `frameDelay`
> multiplies the main loop's own tick interval and the accumulator interacts
> with it. **Named here rather than guarded — rule 13.**

---

## §3 — `speedgraphframes`: 24 REFERENCES, SORTED BY WHAT THEY DO

### §3.1 — THE CHOKE POINT. ONE LINE.

```c
/* lv.c:974 */  g_ClockTimer = speedgraphframes;
/* lv.c:979 */  g_GlobalTimerDelta = (f32) g_ClockTimer;
```

**Everything else downstream of the timebase flows through these two lines.**

### §3.2 — TIME ACCUMULATORS. NO CHANGE NEEDED, AND SEVERAL IMPROVE.

| Site | |
|---|---|
| `bondview2.c:3036` | `zoomintime += (f32) speedgraphframes` — **already casts to float** |
| `bondview2.c:3044` | `zoomintime += speedgraphframes * watch_transition_time` |
| `bondview2.c:6181` | `damageshowtime += speedgraphframes` |
| `bondview2.c:7991` | `watch_time_0 += speedgraphframes` |
| `mpmenu.c:589` | `g_gameOverFlag -= speedgraphframes` |
| `mpmenu.c:611`, `:612` | menu timers `+=` |
| `options.c:1502` | `D_80040B14 += (D_80040B1C * speedgraphframes * M_TAU_F) / 360.0f` — float math |

**These add elapsed 60ths to a timer. With an accumulator producing 0, 1, 1, 0,
1 they still sum correctly over time** — that is the whole point of carrying the
remainder. **No edits.** The float ones would read *better* from a fractional
delta, which is RB-03's territory, not RB-02's.

### §3.3 — THE ON-SCREEN SPEED GRAPH. ALREADY ZERO-SAFE.

`speed_graph.c` accumulates and maxes it (`:210`, `:212-214`, `:308`), and
divides by it at `:257`:

```c
sprintf(buffer, "%2d hz", ((speedgraphframes == 0) ? 0 : (VICLOCK / speedgraphframes)));
```

> **THE DIVIDE IS ALREADY GUARDED AGAINST ZERO.** The one place in the tree that
> divides by the frame delta already expects it to be zero sometimes. **That is
> a strong signal that zero-tick frames were always an anticipated state** — and
> it matches the 34 `g_ClockTimer > 0` guards `118` §1 counted.

**`g_speedGraphCountAccumulator` is this display's counter and NOT a timebase
accumulator.** Ruled out in `119`; repeated here because the name invites the
mistake twice.

### §3.4 — THE ONE COMPATIBILITY FLAG

```c
/* ramromreplay.c:251 */  ramrom_blkbuf_2->speedframes = speedgraphframes;
```

**The frame delta is RECORDED INTO REPLAY DATA.** A replay captured before RB-02
and played back after — or vice versa — carries a different cadence.

> **NOT A BLOCKER, AND NOT SOMETHING TO GUARD.** Nobody in this project uses
> ramrom replays and the VR build is not a competitive-replay target.
> **Written down so that if replay desync ever appears, this is the first place
> to look instead of the twentieth.** Rule 13.

---

## §4 — THE `g_ClockTimer` CONSUMERS THAT ARE NOT `> 0` TESTS

**`99` §4 said 39 of 43 literal comparisons are against zero and four are not.
Here are the four, plus the seven loops, and NONE of them breaks:**

| Site | What | Survives? |
|---|---|---|
| `explosion.c:696`, `:1297` | `lvupdate = (g_ClockTimer < 15) ? (f32) g_ClockTimer : 15.0f` | **Yes** — a clamp on a still-integer count |
| `glass.c:227` | `if (g_ClockTimer < 15)` | **Yes** — same |
| `gunfire.c:1465` | `if (g_ClockTimer < 3)` | **Yes** — a threshold on 60ths |
| 7 x `for (i = 0; i < g_ClockTimer; i++)` — `bondview2.c` x5, `propobj.c` x2 | sub-step loops | **Yes** — they run 0 or 1 times instead of always 1, **which is the correct behaviour, not a regression** |

**Because THE UNIT NEVER CHANGES.** `g_ClockTimer` remains an integer count of
60ths; only the way that integer is DERIVED changes.

---

## §5 — THE ANSWER: THE EDIT LIST FOR RB-02 AND RB-03

**CHANGE — two files:**

1. **`frametiming.c`, `waitForNextFrame` / `updateFrameCounters`** — carry the
   remainder instead of truncating
   `((osGetCount() - base) + 387937) / 775875`. **RB-02.**
2. **`lv.c:979`** — `g_GlobalTimerDelta` becomes the fractional delta rather
   than `(f32) g_ClockTimer`. **RB-03.**

**AUDIT, DRIVEN BY BREAKAGE — RB-04:** the 34 `g_ClockTimer > 0` guards, for
CONTINUOUS quantities hiding behind an INTEGER gate. **The worked example is
`gunfire.c:202-205`, which divides by `g_GlobalTimerDelta` inside
`if (g_ClockTimer > 0)`.**

**DO NOT CHANGE:** the derived counters (§1), the time accumulators (§3.2), the
speed graph (§3.3), the four comparisons and seven loops (§4).

**WATCH, DO NOT GUARD:** `frameDelay` on PAL (§2), replay cadence (§3.4).

---

## §6 — WHAT THIS READ DID NOT ESTABLISH

**It did not run anything.** Every claim here is from the tree.

**It did not check the RECOMP side.** `frametiming.c` is game code reached
through the recompiler; whether `waitForNextFrame`'s busy-wait on `osGetCount`
behaves the same under recompilation as on hardware **is RB-06's question and
has not been asked.** If the recomp already replaces or short-circuits that
loop, RB-02's edit may land in a function that no longer paces anything.

> **THAT IS THE FIRST THING RB-02 SHOULD CHECK, BEFORE WRITING THE ACCUMULATOR.**
