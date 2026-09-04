# 273 — THE GPU HAS A NUMBER, AND IT CAN ONLY BE TAKEN WITH THE CAP OFF.

**2026-08-30j. `258` STAGE 3.1, the GPU half, CLOSED. TWO BUILDS, NINE RUNS.**
**`272` §7's repair was built exactly as designed. HALF of it worked and half of it was aimed
at the wrong thing — and the run that answered the question needed no build at all.**

**HEADLINE: `[MEASURED]` GPU draw is 0.832 ms on CRADLE and 0.334 ms on FACILITY, 1280x960,
RTX 5090 — the first GPU figure this project has ever owned. It is only obtainable with
`GETV_FPS=0`. With ANY cap on, the number is the frame period, and the instrument now REFUSES
to print a verdict rather than printing one.**

---

## §1 — THE RUNS, AND THREE OF THEM ARE PARTLY OR WHOLLY VOID. CHECKED FIRST.

| log | arm | verdict |
|---|---|---|
| `run_273_gpu2_cradle_90.log` | v2, Cradle 90 | **`GETV_SIMDIV` NOT PINNED — divider 3 engaged.** GPU figure valid for the gate; **`WORK` NOT comparable to `272`** |
| `run_273_gpu2_facility_90.log` | v2, Facility 90 | same divider fault; GPU figure valid for the gate |
| `run_273_gpu2_cradle_60.log` | v2, Cradle 60 | **CLEAN.** No divider at 60. `WORK` replicates `272` |
| `run_273_gpu2_cradle_90_nodraw.log` | v2, nodraw | clean; divider engaged, irrelevant with no draws |
| `run_273_h1_cradle_uncapped.log` | uncapped Cradle | **NO TERMINATING RECORD** — killed at a lock-up (§7.3). 18 windows are real |
| `run_273_h1_facility_uncapped.log` | uncapped Facility | **A SECOND `lvlStageLoad` AT LINE 375068 THEN `EXCEPTION 0xc0000005`.** The last 30 windows are the intro/cast sequence, **NOT Facility, and are VOID** — `272` §7's "pointed at a menu" failure, fired exactly as pre-registered. 330 windows before the reload are gameplay |
| `run_273_h2_cradle_320x240.log` | 320x240 @ 90 | **CLEAN.** `game_exit requested`, window banner `320x240`, `props interpolated 0` |
| `run_273_v3_cradle_90_capped.log` | v3 gate, capped | **CLEAN.** `game_exit requested` |
| `run_273_v3_cradle_uncapped.log` | v3 gate, uncapped | no terminator — the same lock-up, twice |

**THE VOID TAIL IS THE POINT OF §1.** PowerShell's `Select-Object -Last 4` handed the owner the
Facility intro-sequence windows — **0.20-0.23 ms, a plausible-looking number from the wrong
scene.** Only the line number of the second `lvlStageLoad` separated them. **A tail is not a
sample.**

## §2 — WHAT WAS BUILT. TWO BUILDS, ONE BEHAVIOUR CHANGE EACH.

**BUILD 1 (`v2`) — `272` §7 as designed.** `port_render.c`, `ge_gpu_timer.c/.h`. All TRACKED;
`gfx_sdl2.c` untouched, so **no regen is forced by this session's code.**
1. `geGpuTimerFrameEnd()` moved to **before** `gfx_end_frame()`, so `GL_TIME_ELAPSED` spans
   `gfx_start_frame`..last draw and excludes the swap and the pacer's `sys_sleep`.
2. `CPU in swap` -> `CPU present`, with `ge_pace_wait_ms` **sampled either side of
   `gfx_end_frame` and the DELTA subtracted.** Delta, not read-and-zero: the `GETV_BUDGET`
   consumer zeroes that accumulator and only when the knob is set, so read-and-zero would fight
   it when on and read a whole run's total when off.
3. Banner and field names versioned (`v2`, `GPU draw` / `CPU present` / `sleep`) so a log cannot
   be mistaken for `272`'s.

**BUILD 2 (`v3`) — THE CONTAMINATION GATE.** `ge_gpu_timer.c` only. When the pacer slept on any
frame in the window, the verdict string is replaced by
`CONTAMINATED -- the pacer slept, so GPU draw is the FRAME PERIOD and not GPU work. Re-run with
GETV_FPS=0.` The figures still print; **only the sentence a reader ACTS on is withheld.** The
line carries `slept=N/120` so the gate itself is auditable. **This is rule `17`: a tool that
falls back instead of failing is a silent-staleness bug, and this is the FOURTH instrument in
this family** (`267` §1, `271` §4, `272` §3, this).

## §3 — `272` §7's GATE, SCORED HONESTLY

| half | required | result |
|---|---|---|
| scene-SENSITIVE | Cradle >> Facility, same cap | **FAIL capped** (11.215 vs 11.131). **PASS uncapped** (0.832 vs 0.334, **2.5x**) |
| cap-INVARIANT | 60 and 90 agree | **FAIL** — 11.11 vs 16.67, unchanged from `272` |
| `GETV_NODRAW` -> ~0 | | **PASS** — 0.00, `WORK` 0.010 ms |

`[MEASURED]` capped `GPU draw`, mean of window means: **Cradle 90 = 11.215** (39/49 windows
within +-0.01 of 11.111) · **Facility 90 = 11.131** (31/36) · **Cradle 60 = 16.663** (46/51 within
+-0.01 of 16.667).

## §4 — ►► WHAT IS RETRACTED. BOTH ARE MINE, AND BOTH ARE FROM `272` §7. ◄◄

**4.1 — `272` §7 ITEM 1'S DIAGNOSIS IS WRONG. THE BRACKET WAS NOT THE FAULT.**
I said the query read the period because `glEndQuery` sat after the pacer's sleep. **It was moved
ahead of both the swap and the sleep and the figure DID NOT MOVE AT ALL** — 11.11 before,
11.11 after, to two decimals, in both levels.
**THE DECISIVE MEASUREMENT:** `[MEASURED]` the CPU issues `glBeginQuery` and `glEndQuery`
**0.22 ms apart** (`WORK mean=0.228`) while the GPU reports **11.11 ms between them**. The GPU is
therefore **waiting inside the query window**, and the wait is one frame period long.
**`ge_gpu_timer.c:179-189` NAMED THIS MECHANISM IN ITS OWN SOURCE** — *"If the GPU spends part of
that window waiting -- for a buffer to free, for the compositor, for work to arrive -- that
waiting is inside the number"* — **and it was read in `272` and again in this session without
being applied to the case in front of it.** `[INFERRED]` the wait is for the swap-chain back
buffer, whose release rate the pacer sets; **not established, and nothing is built on it.**

**4.2 — `272` §7'S "CAP-INVARIANT" GATE ASKED FOR SOMETHING UNOBTAINABLE.**
It required a capped run to yield a clean GPU figure. **A capped run cannot, whatever the bracket
does**, because the pacing wait is inside the draw window. The gate was a correct FALSIFIER — it
failed, loudly, and it was right to — but as a specification of the fix it was wrong. **The
repair was never a bracket move; it was a RUN CONDITION.**

## §5 — WHAT IS MEASURED, AND IT IS THE THING `258` STAGE 3.1 EXISTED FOR

**5.1 — `[MEASURED]` THE GPU TERM, UNCAPPED, 1280x960, `GETV_SIMDIV=1`, `props interpolated 0`:**

| scene | GPU draw mean | window range | worst frame seen | windows |
|---|---|---|---|---|
| **CRADLE (hardest)** | **0.832 ms** | 0.80-0.87 | 1.69 ms | 18 |
| **FACILITY (a vent)** | **0.334 ms** | 0.20-0.90 | 59.20 ms (one hitch, not chased) | 330 |

**2.5x between them. Scene-sensitive, sub-millisecond, `sleep 0.00` and `slept=0/120` in every
window.** Reproduced across two separate uncapped Cradle runs (0.83 and 0.832).

**5.2 — THE PRE-STEREO FRAME, BOTH TERMS, ON THE HARDEST LEVEL IN THE GAME:**
`[MEASURED]` **CPU 0.890 ms** (`272` §5.2) **+ GPU 0.832 ms, against an 11.111 ms period.**

**5.3 — `[MEASURED]` THE PRESENT COSTS NOTHING.** `CPU present 0.00 ms, max 0.02-0.05 ms`, in
every window of every arm, with the measured sleep subtracted. `272` §3 argued from source that
nobody is stalled in a swap; **this is the number.** Cross-validated against an independent
instrument in the same window: `sleep 10.53` beside the budget line's `wait mean=10.528`.

**5.4 — `[MEASURED]` THE CAPPED FIGURE IS INDIFFERENT TO SIXTEEN-FOLD LESS FILL.** Cradle at 90 Hz,
**320x240**: `GPU draw 11.11 ms`, identical to 1280x960. **A number that does not notice 1/16 of
the pixels is not measuring pixels.** This is the cheapest single proof in the whole session and
it needed no build.

**5.5 — `[MEASURED]` `271`/`272`'s CPU BASELINE REPLICATED ACROSS A REBUILD.** Cradle 60 Hz
`WORK` mean-of-means **0.614 ms** this session vs **0.625 ms** in `272`, 51 windows vs 42.

## §6 — NOT CLAIMED
- **NO CAPPED GPU FIGURE.** 0.832 ms was taken with the pacer never sleeping. Per-frame draw work
  *should* not depend on the present rate, but that is an ASSUMPTION and the capped case cannot
  currently check it. **Any claim that stereo's doubled GPU work fits in 11.111 ms rests on it.**
- **NOT CLAIMED that a second view costs exactly 2x** either term. Nobody has measured two views.
- **Facility's 59.20 ms worst frame is not investigated.** One hitch in 330 windows.
- **Cradle's uncapped sample is 18 windows (~2,160 frames)** against Facility's 330. It is
  consistent across two runs but it is not a long sample, and the run never terminated cleanly.
- **The `[INFERRED]` back-buffer mechanism in §4.1 is not established.** What IS established is
  that the wait exists, is inside the query, and disappears with the cap.

## §7 — THREE TRAPS, ALL FOUND THIS SESSION

**7.1 — ►► `272`'s FOUR CONTROL ARMS WERE NOT REPRODUCIBLE FROM THEIR OWN LOGS. ◄◄**
This session's blocks open with `Remove-Item Env:GETV_*` (§7a). **The 90 Hz arms then engaged
`GETV_SIMDIV`'s unset-default branch — `simulation held to 30Hz (divider 3)` — which `272`'s arms
do not show.** So `272` ran with `$env:GETV_SIMDIV` **inherited from a shell**, set in some earlier
window and recorded nowhere. **The env-reset rule is right; it exposed a hidden dependency.**
**AND THE OWNER NAMED IT FROM THE SCREEN BEFORE THE LOG WAS OPENED** — *"it's like there are
invalid graphics being pushed into different frames"*, *"the transparent texture issue"*. That is
`268`'s artifact exactly. **Rule `16` again.**
**`GETV_SIMDIV=1` PRINTS NOTHING** (`frametiming.c:207`, the explicit branch is silent). **The only
positive gate is `props interpolated 0` PLUS zero `simulation held to` lines — put both in every
block.** Consequence: this session's Cradle-90 `WORK` of 0.665 ms is **not** comparable to `272`'s
0.890 ms; the sim ran at 30 Hz.

**7.2 — ►► `GETV_SUPERSAMPLE` IS INERT IN THE WINDOWS BUILD. ◄◄** `[MEASURED]` from source: both
`getenv("GETV_SUPERSAMPLE")` sites (`gfx_opengl.c:1379`, `:1433`) are inside `#ifdef
TVOS_SUPERSAMPLE` and `#ifdef GE_POSTFX`, **neither defined here** — while `ge_config.c:410`
accepts `supersample=2` and puts it in the environment where nothing reads it. **It was one step
from being this session's fill-rate arm, and it would have returned a clean null read as a
result.** `GETV_WINDOW=WxH` (`port_support.c:106`) is live and is the fill-rate knob that works.

**7.3 — `[MEASURED]` UNCAPPED LOCKS UP ON CRADLE, REPRODUCIBLY.** `GETV_FPS=0` on stage 41 froze
within a few seconds in **three of three** attempts, standing still, twice on the v3 binary and
once on v2. No exception, no terminator — the process stops producing frames. **Facility uncapped
ran 43,800 frames before dying to `0xc0000005` after a death and a stage reload.** Not
investigated. **It bounds how long an uncapped GPU sample can be, which is why Cradle has 18
windows and Facility 330.**

## §8 — WHAT THIS COSTS THE NEXT SESSION, AND THE METHOD NOTE

**HOW TO MEASURE THE GPU FROM NOW ON:** `GETV_GPUTIME=1` **with `GETV_FPS=0`**, `GETV_SIMDIV=1`,
`GETV_VSYNC=0`, a pinned `GETV_STAGE`, and read only windows between `lvlStageLoad` events. **A
capped run now says CONTAMINATED and means it.**

**THE METHOD NOTE, AND IT IS `272` §8 EARNING ITS KEEP:** *when a measurement will not move, find
the axis it is pinned to and change THAT.* `272` changed the SCENE and proved the fault. `273`
changed the CAP and got the answer — **and the run that got it needed no build.** The build I
argued for first moved the bracket, which was the axis I had a theory about rather than the axis
the number was pinned to. **Two builds and nine runs; the two runs that answered it were the two
that changed a run condition instead of the code.**
