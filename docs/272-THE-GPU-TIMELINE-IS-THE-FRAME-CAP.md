# 272 — THE "GPU TIMELINE" IS THE FRAME CAP. THE GPU IS STILL UNMEASURED.

**2026-08-30i. `258` STAGE 3.1, the GPU half. FOUR RUNS, NO BUILD, NO CODE.**
**`run_272_gpu_90.log`, `run_272_gpu_90_nodraw.log`, `run_272_gpu_cradle_90.log`,
`run_272_gpu_cradle_60.log`. Same 03:02 binary that produced `271`.**

**HEADLINE: `[getv][gputime]`'s two numbers BOTH measure the frame cap. Every verdict it
has ever printed is void. `00-STATE` §3 ranking item 2 does not move — and it is now known
to be BROKEN, not merely unrun.**

**AND THE OWNER CAUGHT THE THING THAT MADE IT PROVABLE: every performance number this
project owns was taken inside a ventilation shaft.**

---

## §1 — THE RUNS ARE VALID. CHECKED BEFORE ANY NUMBER WAS READ.
- `goldeneye.exe` 03:02; all four logs 13:17-13:27, **newer than the exe** (`133`).
- **All four terminate with `game_exit requested`.** None read while still being written (`262` §5).
- All four `pace: N fps cap on (GETV_FPS), vsync=0`; **zero `simulation held to` lines** in any
  arm, so `268`'s divider is not in this measurement.
- **It is GAMEPLAY, not a menu** (`52`): `GETV_STAGE override` and `bm:lvlStageLoad` in each.
- `[getv][gputime] on:` present in all four — **the knob took** (`133`, `268` §4).
- `n=120` per window in every arm except the first (116) — no sample gap to hide behind.
- `GL_RENDERER=NVIDIA GeForce RTX 5090`, `GL_VERSION=4.6.0 NVIDIA 616.56`, window 1280x960.

## §2 — ►►►► THE MEASUREMENT, AND IT CLOSES ON TWO INDEPENDENT AXES ◄◄◄◄

| arm | stage | cap | **GPU timeline** | period | CPU in swap | CPU `WORK` |
|---|---|---|---|---|---|---|
| A | 34 Facility (a VENT) | 90 | **11.11 ms** | 11.111 | 10.7-10.8 | 0.203 ms |
| B | 34, `GETV_NODRAW=1` | 90 | **0.00 ms** | 11.111 | 10.9 | 0.008 ms |
| E | **41 Cradle** | 90 | **11.11 ms** | 11.111 | 9.66-9.93 | **0.890 ms** |
| F | **41 Cradle** | 60 | **16.67 ms** | 16.667 | 15.2-16.1 | 0.625 ms |

**`[MEASURED]` THE FIGURE IS THE PERIOD, ON TWO AXES THAT CANNOT BOTH BE COINCIDENCE:**

**2.1 — CAP-SENSITIVE.** `11.11 -> 16.67` when the cap changed, same scene, same binary.
**The spread is not merely close, it is degenerate:** of Cradle's 41 windows at 90 Hz,
**40 fall within ±0.01 ms of 11.111**; of 42 windows at 60 Hz, **41 fall within ±0.01 ms of
16.667.** (The single outlier at each end is the teardown window — see §6.)

**2.2 — SCENE-BLIND, AND THIS IS THE ONE THAT KILLS IT.** A ventilation shaft and the level
whose framerate the N64 could not hold produce **the byte-identical figure at the same cap** —
**while the CPU work between them differs by 4.4x.** No measurement of GPU work can be
indifferent to that.

**2.3 — THE SCENE CHANGE IS CONFIRMED INDEPENDENTLY, IN A SECOND TERM.** `CPU in swap` falls
from 10.7-10.8 ms (Facility) to 9.66-9.93 ms (Cradle) at the same cap: **heavier CPU work
leaves less frame to sleep through.** The two instruments agree that Cradle is harder. Only
the GPU line does not notice.

## §3 — WHY, FROM SOURCE. NOT INFERRED.
**The GPU query bracket and the swap bracket BOTH contain the pacer's sleep.**
- **`gfx_sdl2.c:111`, the port's own comment:** *"gfx_end_frame carries swap_buffers_end ->
  sync_framerate_with_timer() -> sys_sleep()."*
- **`port_render.c:923-934`:** `geGpuTimerRecordSwap` brackets `gfx_end_frame()`, and
  `geGpuTimerFrameEnd()` — the `glEndQuery` — is called **after** it.
- **AND THE LOGS PROVE IT WITHOUT INFERENCE.** Arm A window `r1`: the budget instrument reports
  `wait mean=10.762 ms` and the GPU timer reports `CPU in swap 10.76 ms` — **the same number,
  to two decimals, in the same window.**

**So `CPU in swap` is the FRAME CAP, not a present block. Nobody has ever been stalled in a
swap.** `ge_gpu_timer.h` warned about exactly this in its own header — *"time the GPU spends
waiting inside that window is included"* — **and I read that warning and ran anyway.**

## §4 — ►► WHAT IS RETRACTED, AND BOTH ARE MINE ◄◄

**4.1 — `[getv][gputime]`'s "GPU timeline" AND "CPU in swap" MEASURE THE FRAME CAP.**
Both are void, and so is every verdict string derived from them — `neither dominates`,
`STALLED IN SWAP (GPU idle)`. **This is `267` §1 and `271` §4 for the THIRD time, in a THIRD
instrument, and it is the identical error each time: a bracket that contains the pacer's
sleep produces a figure that tracks the period.** `271` §4 fixed it in `WORK` and I did not
go looking for the same shape next door.
**Consequence for `docs/PERFORMANCE.md`:** its GPU section rests on this instrument. Its
figures were taken on a Surface Pro 3 / Intel HD 4400 and are `[ASSUMED]` here regardless —
**but the instrument they came from is now known broken, so they cannot be transferred by
re-running it either.** Nothing in that document is deleted; this doc supersedes its GPU
section until the instrument is repaired.

**4.2 — `271` §2's "0.259 ms at both caps" IS A VENT NUMBER, NOT A BASELINE.**
`[MEASURED]` Facility 0.203 ms -> **Cradle 0.890 ms**, mean of window means, same cap, same
binary. **4.4x.** `271` §8 wrote this caveat itself — *"No claim that 0.259 ms holds in a
heavier scene"* — and the next session inherited the `GETV_STAGE=34` pin without ever asking
what level 34 was. **It is `LEVELID_FACILITY` (`bondconstants.h:1752`, counting from
`LEVELID_STATUE = 22`), and Facility opens in the ventilation shaft.**
**THE OWNER FOUND THIS FROM THE SCREEN, NOT FROM A LOG:** *"Are we trying to track performance
because you loaded me in one of the easiest levels? I'm inside of a vent."* **Rule `16`, and
`HANDOVER` §5's standing observation again — the wear report outranked the analysis.**
**And the owner supplied the level: `[REPORTED]` Cradle is the hardest, from the owner's own
research. It is also the strongest possible form of the test — there is no scene left to
escalate to.**

## §5 — WHAT SURVIVES, AND IT IS NOT NOTHING
**5.1 — `[MEASURED]` THE CPU TERM SURVIVES THE HARDEST LEVEL IN THE GAME.**
**`WORK_OVER = 0 in EVERY ONE of 83 windows — ~9,960 frames — across both Cradle arms, and
the pacer slept on every frame of both.** Worst single-frame `WORK` seen: 2.504 ms at 90 Hz,
2.081 ms at 60, against periods of 11.111 and 16.667. **The game never once failed to fit its
period on Cradle.** `P5`'s CPU term survives the scene change with room to spare.

**5.2 — THE HONEST PRE-STEREO CPU BASELINE IS NOW:** `[MEASURED]` **0.890 ms mean, 2.504 ms
worst frame, Cradle, 90 Hz, 1280x960**, against an 11.111 ms period, with measured idle
9.8 ms. **`258` STAGE 3.1 is re-taken and this figure replaces `271` §2's for all purposes
except describing Facility.**

**5.3 — `GETV_NODRAW` STILL BISECTS.** CPU `WORK` collapses 0.203 -> **0.008 ms** with
`gfx_run` skipped. The display-list replay cost is isolated and consistent with `271`.
**The falsifier I wrote for arm B fired exactly as predicted — and predicting it correctly
did not make arm A's magnitude readable. I got the right answer to the wrong question.**

**5.4 — STAGE 41 DIRECT-BOOTS.** Only stages 9, 34 and 38 had ever been booted in this port.
Cradle now has too. Small, but it is one less unknown for the next scene-heavy run.

## §6 — NOT CLAIMED
- **NO GPU FIGURE OF ANY KIND, STILL.** Four runs and the GPU remains entirely unmeasured.
  Nothing here says whether stereo's doubled GPU work fits in 11.111 ms.
- **NOT CLAIMED that `WORK` scales with the cap.** Cradle reads 0.890 at 90 and 0.625 at 60,
  which is *not* the invariance `271` §3 found on Facility — **but at 90 Hz the synthetic clock
  runs the game 1.5x (`RB-04`) and the owner flew a different route in each arm.** Different
  content, not a measured difference. **UNRESOLVED, and it does NOT retract `271` §3.**
- **The 90 Hz teardown window** (`f4920`, `GPU timeline 12.02 ms, max 129.87`) is the quit path
  and was not investigated. One window of 41. Do not build on it.
- `[MEASURED]` **`draining pre-existing GL error 0x0502` (`GL_INVALID_OPERATION`) fires at timer
  init in every arm** — `PERFORMANCE.md`'s known unfixed frame-0 error **reproducing on the
  RTX 5090**, not only on the Intel HD 4400 it was found on. **Correctness, not performance.
  Not chased, and it is not a candidate for a per-frame cost** (`PERFORMANCE.md` already killed
  that hypothesis and recorded it as killed).
- No claim about Cradle's *worst* case: the owner swept the valley, but a firefight was not
  sampled and 2.504 ms is the tail these runs saw, not the game's.

## §7 — ►►►► THE REPAIR. PLANNED, GATED, AND DELIBERATELY NOT BUILT ◄◄◄◄
**Rule 1: this is a plan and it stops. NOTHING IN §7 HAS BEEN WRITTEN.**

**ONE behaviour change, diagnostics only, no game behaviour touched.** The pacer already
publishes its measured sleep as a non-static global (`ge_pace_wait_ms`, `gfx_sdl2.c:133`)
**precisely so it can be subtracted — that is how `271` fixed `WORK`.** The same move applies
twice:
1. **`glEndQuery` moves to before the pacer sleeps**, so the GL_TIME_ELAPSED window covers the
   frame's draw work instead of the cap.
2. **`CPU in swap` becomes `gfx_end_frame` MINUS the measured sleep** — the `271` subtraction,
   already validated in-tree.

### THE GATE, WRITTEN BEFORE THE CODE. IT IS THE PRECISE INVERSE OF §2.
> **The repaired figure must be SCENE-SENSITIVE — Cradle ≫ Facility at the same cap — AND
> CAP-INVARIANT — 60 and 90 agreeing within noise, the way `WORK` did in `271` §3.
> If it stays identical across levels, or still moves with the cap, THE FIX FAILED AND I SAY
> SO.** `GETV_NODRAW=1` must still take it to ~0.00.

**Both halves are required.** Cap-invariance alone would pass on a number stuck at zero;
scene-sensitivity alone would pass on a number that is really the CPU's. **§2 is the negative
control and it already exists on disk** — the repaired instrument re-run on these same two
Cradle arms either separates them or it does not.

### WHAT IT WOULD PRINT IF POINTED AT THE WRONG THING
- **Knob absent from the build** -> no `[getv][gputime] on:` banner. A clean null, not a fast
  GPU (`133`, `268` §4). Every block must grep for the banner.
- **Driver refuses** -> `no ARB_timer_query`. The answer is *I cannot answer this*, not a zero.
- **Pointed at a menu** (`52`) -> few draws, small figure, meaningless. Gate on `lvlStageLoad`.
- **Driver running far ahead** -> `n` well below 120. Do not read the mean if it is.

## §8 — METHOD NOTE, AND IT IS THE REUSABLE PART
**The decisive test was not mine and it was not an instrument. It was the owner looking at the
screen and asking what level he was standing in.**
**A number locked to the frame period CANNOT respond to scene complexity** — so changing the
level tested the bracket without touching the cap, on an axis the instrument's author never
considered. It was cheaper than the 60 Hz arm, arrived first, and would have closed the
question on its own.
**`56`'s move again — change one thing and see what fails to change.** Three sessions running,
the fault has been a bracket, and three times the tell was a figure that tracked something it
should have been independent of. **The general form: when a measurement will not move, find
the axis it is pinned to, and change THAT.**
