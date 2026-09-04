# 267 — THE BUDGET INSTRUMENT MEASURED THE PACER, NOT THE WORK. `266` §3 IS RETRACTED.

**2026-08-29p. Two clean runs, both terminated, 25 and 20 reports.
`[MEASURED]` — and what they measured is the frame limiter.**

---

## §1 — THE RUNS ARE VALID. THE INSTRUMENT IS NOT.
`[MEASURED]` `run_budget_60.log` (25 reports) and `run_budget_90.log` (20 reports), both
carrying `game_exit requested`, gate confirmed in the exe before either was read.

| | mean | min | max | budget | OVER |
|---|---|---|---|---|---|
| `GETV_FPS=60` | **16.397** ms | 14.47 | 18.07 | 16.667 | 18-56% |
| `GETV_FPS=90`, vsync off | **10.931** ms | 9.27 | 12.57 | 11.111 | 33-48% |

> ## ►►►► **THE MEASURED "FRAME COST" CHANGED WHEN THE CAP CHANGED — 16.40 ms AT 60,
> ## 10.93 ms AT 90. WORK DOES NOT GET CHEAPER BECAUSE YOU ASKED FOR MORE FRAMES.** ◄◄◄◄
> **The figure tracks the PERIOD, not the load. That is `[MEASURED]`, from the owner's own
> two runs, and it is decisive on its own.**

**Corroborating:** in both runs the mean sits just BELOW the budget and the spread is tight
around it (±1.5 ms), which is the signature of a limiter holding a period — not of a
machine at its limit, which would push the mean ABOVE budget and the frame rate below the
cap. And **`min=0.150 ms`** appears in `r3` of both runs: a single frame that did not wait
at all.

## §2 — ►► THE MECHANISM, READ ◄◄
`[READ]` `gfx_pc.c:6258` — `gfx_end_frame()` calls `gfx_wapi->swap_buffers_end()`.
`[READ]` `gfx_sdl2.c:579` — that is `gfx_sdl_swap_buffers_end()`, which calls
`sync_framerate_with_timer()` (`gfx_sdl2.c:534`), **which calls `sys_sleep()` for the
remainder of the period.** And `gfx_sdl_swap_buffers_begin()` calls `SDL_GL_SwapWindow()`,
**which blocks on vblank when vsync is on.**

> **`266`'s bracket spans `gfx_start_frame` + `gfx_run` + `gfx_end_frame`. THE DELIBERATE
> SLEEP AND THE VBLANK WAIT ARE BOTH INSIDE IT.** The instrument was measuring the work
> plus however long the port then waited to avoid doing more.

## §3 — WHAT IS RETRACTED, AND IT IS MINE
| claimed | truth |
|---|---|
| **`266` §3: *"`OVER=` IS THE TERM THAT CAN FAIL. That is the whole of `P5`."*** | **FALSE.** `OVER=` counts frames whose PACED period ran long. It fails on limiter jitter, which happens ~40% of the time on a machine with headroom to spare. **It cannot distinguish a missed budget from a normal frame.** |
| **`266` §3: *"the whole CPU frame"* is what is being measured** | **Incomplete, and the incompleteness is the bug.** It is the whole *call*, which is work + sleep + vblank. |

**`266` §4's validation was sound and is NOT retracted** — the scripted clock proved the
arithmetic, the reset and both off-states. **It could not have caught this: a synthetic
clock has no pacer in it.** That is the limit of a bench test, recorded here so the next
instrument is validated against a run as well as a bench.

## §4 — WHAT IS ACTUALLY KNOWN NOW, AND IT IS NOT NOTHING
- `[MEASURED]` **The game sustains 90 Hz in gameplay.** Mean 10.93 ms against an 11.111 ms
  period, over 2,400 frames, with `min=9.27`. **It is holding the cap, not chasing it.**
- `[MEASURED]` **60 Hz likewise**, mean 16.40 against 16.667.
- **HEADROOM IS UNKNOWN.** Nothing here says how much of that period is work. `257` §6's
  pre-stereo baseline is **NOT** taken.

## §5 — THE FIX, AND WHAT IT COSTS
**Subtract the wait.** `sync_framerate_with_timer()` already computes `remain` and is the
only sleep on the path; bracket the actual sleep with `SDL_GetPerformanceCounter()`, export
the figure, and report three terms instead of one:

```
frame=10.950  work=6.104  wait=4.846 ms | budget=11.111 | WORK_OVER=0
```
**`WORK_OVER=` is then the term that can fail**, and `budget - work` is the headroom stereo
will be spent from.

**COSTS:** it touches `gfx_sdl2.c`, which is **GITIGNORED** — `tools/fetch-thirdparty.sh
regen` in the same commit. **And the vblank block still lives inside `work` when vsync is
on**, so the baseline run must keep `GETV_VSYNC=0`, or `work` will absorb the wait it was
built to exclude. **State that before the run, not after.**

## §6 — NOT CLAIMED
- **No headroom figure. No performance claim of any kind.**
- No claim about GPU-side cost; `GETV_GPUTIME` is untouched and was never part of this.
- No claim that the two runs are comparable to each other as WORK — they are two different
  periods, which is exactly the confound §1 names.
