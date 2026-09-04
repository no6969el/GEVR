# 266 — THE CLOCK WAS NEVER THE PROBLEM. `257` §6.1 WAS READ OFF THE WRONG BRANCH.

**2026-08-29o. `P5` now has an instrument that can fail. `257` §6.1 is RETRACTED — mine.**

---

## §1 — ►►►► THE RETRACTION ◄◄◄◄

`257` §6.1 wrote: *"`port_render.c:143-156` times `gfx_start_frame`/`gfx_run`/`gfx_end_frame`
with **`SDL_GetTicks()` — millisecond resolution**... Requirement 4 is currently
unmeasurable."*

`[READ]` **those lines are inside `if (rendered < 5)`.** They are the BOOT-STALL BISECTOR —
*"it stalls after frame 1"* is not actionable, *"gfx_end_frame took 20 seconds"* is. **They
fire five times and never run again**, and a 1 ms quantum is correct for that job.

`[READ]` the steady-state branch already times with **`SDL_GetPerformanceCounter()`**
(`port_render.c`, the swap bracket) and with **`clock_gettime(CLOCK_MONOTONIC)`**
(`ge_now_ms()`, `gfx_pc.c:90`, nanosecond source, feeding `[prof]`).

> ## **THE CLOCK WAS NEVER THE PROBLEM. `257` §6.1 NAMED A REAL FILE, A REAL FUNCTION AND
> ## THE WRONG BRANCH, AND THEN COSTED A SESSION'S WORK AGAINST IT.**
> The same shape as `259` (`RB-04` was not in `MoveBond`) and `261` §2 (three config paths,
> not the live one): **a read that stopped one conditional too early.**

## §2 — WHAT WAS ACTUALLY MISSING, AND IT IS WORSE THAN RESOLUTION
1. **NOTHING TIMED THE WHOLE CPU FRAME.** `[READ]` `ge_prof.t_frame` brackets `gfx_run`
   ALONE (`gfx_pc.c:6038`). `gfx_start_frame` and `gfx_end_frame` — **the latter carrying
   the swap** — are outside it. **"Did this frame fit?" was not answerable from any counter
   in the tree.**
2. **`[prof]` PRINTS ONE FRAME IN SIXTY.** A budget question is about **the tail**, not a
   sample. `P5` wants an instrument that can FAIL; **a single sampled frame has nothing to
   fail against.**

## §3 — `GETV_BUDGET=<n>` — WHAT WAS BUILT
`port_render.c`, steady-state branch only. **Reports every `<n>` frames, default 120.
Unset or `0` = off.** Two `SDL_GetPerformanceCounter()` reads per frame, one printf per
report (`P4`). **Diagnostic only.**

```
[getv][budget] r7 n=120 | cpu frame mean=9.412 min=7.980 max=21.006 ms | budget=11.111 ms (90 fps) | OVER=4 (3.3%)
```
- **The whole call is bracketed** — `gfx_start_frame` + `gfx_run` + `gfx_end_frame`, swap included.
- **`OVER=` IS THE TERM THAT CAN FAIL.** That is the whole of `P5`.
- **The budget is DERIVED, never a literal** (`P1`, `P3`): `1000 / ge_pace_framerate`, the
  non-static runtime variable at `gfx_sdl2.c:106` that `GETV_FPS` writes. **There is no
  `11.1` anywhere in this file.**
- **THE FIRST FIVE FRAMES ARE EXCLUDED.** Frame 0's run stage alone is 159 ms; folding the
  loader in would produce a figure that describes asset loading.
- **`GETV_BUDGET_HZ=<hz>`** supplies a target by hand.

### ►► AND IT CAN SAY IT CANNOT ANSWER
**With the cap at 0 (`GETV_FPS=0`, uncapped) there is no target to miss.** It prints
`budget=none (uncapped...) | OVER=n/a` and **suppresses the count rather than inventing a
target.**

## §4 — ►► THE INSTRUMENT WAS VALIDATED BEFORE IT SHIPPED (`48` rule 15) ◄◄
`[MEASURED]` The timing block was compiled standalone against a **scripted clock** —
frequency 1 MHz, ten frames of known cost (5 × 8.000 ms, 5 × 14.000 ms):

| case | expected | printed |
|---|---|---|
| cap 60 (`budget 16.667`) | mean 11.000, min 8, max 14, **OVER=0** | exact |
| `GETV_BUDGET_HZ=90` | budget 11.111, **OVER=5 (50.0%)** | exact |
| `GETV_BUDGET_HZ=0` | **`budget=none`, `OVER=n/a`** | exact |
| gate unset, and `GETV_BUDGET=0` | **no output at all** | exact |

### AND THE TEST CAUGHT A REAL BUG, WHICH IS WHY IT WAS WORTH WRITING
The first cut printed **`budget=16.667 ms (59 fps)` for a 60 fps cap** — it re-derived the
rate from the millisecond figure and `(int)(1000.0/16.6667)` **TRUNCATED**.
> **THAT IS THE SAME TRUNCATING DIVIDE THAT MADE `92` DECLARE 90 Hz STRUCTURALLY
> UNAVAILABLE (`134`).** Cosmetic here — and it would still have been read as a pacing
> fault by the next person. **The Hz is now CARRIED, not re-derived.**

## §5 — NOT CLAIMED
- **No performance number.** Nothing has been run in the game. The instrument exists; the
  baseline does not.
- No claim about GPU-side cost — `GETV_GPUTIME` already owns that and is unchanged.
- No claim the boot-stall timer should change. **It is correct for its job and stays.**

## §6 — WHAT THIS UNBLOCKS
`257` §6's *"a baseline taken BEFORE stereo makes stereo's cost a delta against a known
number"* is now buildable. **One run at 60 and one at 90 gives it.** Stereo (`258`) is next
either way; this is what its cost will be measured against.
