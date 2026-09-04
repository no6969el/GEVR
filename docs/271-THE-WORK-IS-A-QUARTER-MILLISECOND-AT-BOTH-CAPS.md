# 271 — STAGE 2 IS BUILT AND STAGE 3.1 IS TAKEN. THE WORK IS 0.259 ms AT BOTH CAPS.

**2026-08-30. `258` STAGE 2 (the instrument) and STAGE 3.1 (the pre-stereo baseline).**
**Two runs: `run_271_work_60.log`, `run_271_work_90.log`. One build, diagnostics only.**

---

## §1 — THE RUNS ARE VALID. CHECKED BEFORE ANY NUMBER WAS READ.
- `goldeneye.exe` 03:02, **newer than the edited sources**; `goldeneye.map` names `ge_pace_wait_ms`.
- Logs 03:03 and 03:04, **both newer than the exe** (`133`).
- **Both terminate with `game_exit requested`.** Neither was read while still being written (`262` §5).
- **Both arms `vsync=0`** — `[getv] pace: N fps cap on (GETV_FPS), vsync=0`.
- **The divider never engaged in either arm**: zero `simulation held to` lines, `props interpolated 0`.
  `268`'s fault is not in this measurement.
- **It is GAMEPLAY, not a menu** (`52`): `GETV_STAGE override: booting stage 34`,
  `bm:set_solo_and_ptr_briefing`, `bm:lvlStageLoad`, and **34,985 scissor changes** in the 60 Hz log.
- **`slept=120` on EVERY window of BOTH runs.** The instrument's own void condition never fired.

## §2 — ►►►► THE MEASUREMENT ◄◄◄◄
`GETV_BUDGET=120 GETV_VSYNC=0 GETV_SIMDIV=1 GETV_STAGE=34`, stationary then a short route.

| | 60 Hz, 3,240 frames | 90 Hz, 4,200 frames |
|---|---|---|
| period | 16.667 ms | 11.111 ms |
| cpu frame (the `267` figure) | 16.436 | 10.928 |
| **WORK — Fast3D replay + swap** | **0.259 ms** | **0.259 ms** |
| WORK worst window max (excl. r1 loader tail) | 0.904 | 1.294 |
| **idle — the pacer's MEASURED sleep** | **16.177** | **10.670** |
| `outside` = period − frame, DERIVED | 0.231 | 0.183 |
| **`WORK_OVER`** | **0 of 3,240** | **0 of 4,200** |

**`[MEASURED]` THE WORK IS THE SAME AT BOTH CAPS TO THREE DECIMAL PLACES.**
**The pacer slept on every one of 7,440 frames. The game never once failed to fit its period.**

## §3 — THE FALSIFIER WAS WRITTEN BEFORE THE RUN AND IT DID NOT FIRE
Stated in advance: *"`work` must be approximately INVARIANT across the cap while `wait` absorbs
the difference. If `work` moves with the cap the way `frame` did in `267`, the fix failed."*
`work` moved by **0.000 ms**; `wait` moved by **5.507 ms**, which is the whole of the period change.
**`266` §3's `OVER=` failed on limiter jitter — 21-39% of frames at 60 Hz, and it meant nothing.
`WORK_OVER` is 0 across both runs and it now means something.** `P5` has an instrument that can fail.

## §4 — ►► WHAT IS RETRACTED, AND IT IS MINE ◄◄
**`headroom_mean = budget − work`, which I built this session and `267` §5 proposed. IT IS
`267` §1'S OWN ERROR ONE LEVEL DOWN.** The bracket holds Fast3D's replay and the swap; it does
**not** hold the game tick or the display-list CONSTRUCTION, which run before
`gePortRenderDisplayList()` is ever called. So `budget − work` assumes everything outside the
bracket is free, and it overstated the real idle **by exactly the residual, in both arms**
(0.231 ms at 60, 0.183 at 90). **Fixed in source: `idle_mean` is the pacer's own MEASURED sleep
and is the only headroom figure here that was observed rather than assumed.** `outside` is
printed beside it and is marked `[derived]` — the pacer assumes its sleep landed exactly
(`frame_time = now + remain`) while `SDL_Delay` truncates down. **Do not build on `outside`.**
**The logs above were produced by the binary BEFORE this correction and still print
`headroom_mean=`. Read `idle` from `wait mean=`, which is the same measured number.**

## §5 — `267`'s TWO ARMS WERE NOT ONE EXPERIMENT, AND NOBODY HAD DIFFED THEM
Read from the two old logs' own banners this session. **No run, no build.**

| | `run_budget_60.log` | `run_budget_90.log` |
|---|---|---|
| vsync | **1** | 0 |
| simulation | full rate | **held to 30 Hz, divider 3** |
| stage | not pinned, not recorded | not pinned, not recorded |

**`267`'s conclusion survives** — the figure tracked the period in both arms. But **`267`'s 90 Hz
numbers were taken with the simulation at one third rate**, because those runs predate `268`.
**A baseline taken by rerunning that recipe would have understated the work stereo must fit
beside.** This is `268`'s method note again: the two arms already existed on disk.

## §6 — WHAT THIS SAYS ABOUT STEREO, AND THE NEW RANKING ITEM
`[MEASURED]` **the CPU is not the constraint.** Fast3D replay + swap is a quarter of a
millisecond against an 11.111 ms period, and `258` §1's eye loop replays the list per view —
so the CPU cost of a second view is of that order, not of the period's.
**`[INFERRED]`, AND IT IS THE POINT: THE GPU IS UNMEASURED.** `GETV_GPUTIME=1` exists,
is untouched, and was off in both runs (`267` §6 said so and it is still true). **Stereo doubles
GPU work, and nothing here has measured GPU work at all.** `P5` is answered for the CPU term and
**wide open for the GPU term.** That is a run, not a build: same binary, `GETV_GPUTIME=1`.

## §7 — ►►►► THE THIRDPARTY PATCH IS STALE, AND THE TOOL REPORTED SUCCESS ◄◄◄◄
`[MEASURED]`, found while preparing this commit. The tracked patch that carries every change to
the fifteen GITIGNORED third-party sources is **415,083 bytes, dated 2026-08-28 21:46**. A regen
run against the current tree produces **433,892 bytes.**
**18,809 bytes of committed work exist only in gitignored files.** Specifically:

| symbol | in `gfx_sdl2.c` | in the tracked patch |
|---|---|---|
| `dlgrab` / `DLGRAB` (`268` §8, F9) | present | **ABSENT** |
| `ge_pace_wait_ms` / `ge_pace_sleeps` (this doc) | present | **ABSENT** |
| `ge_pace_framerate` | 7 | 6 |

`gfx_pc.c` and `gfx_opengl.c` also report `DIFFERS`. **`268` was committed without a regen, so a
fresh clone of the native repo TODAY does not have `GETV_DLGRAB` at all** — the instrument `268`
built, documented and pointed the next session at.

**AND THE TOOL SAID IT HAD WRITTEN THE FILE.** `cmd_regen` ran `mv -f` without checking it:
on a mount that refuses to unlink the target the move failed, and the next line still printed
`fetch-thirdparty: wrote ... (433892 bytes, was 415083)`. `cmd_verify` then reported `DIFFERS`
on three files — **the signal existed, but it arrived after a false success line.** That is the
same shape as the truncation bug already commented in that function, and it is exactly how a
change to a gitignored source gets lost.

**FIXED IN SOURCE (rule `14`, `tools/fetch-thirdparty.sh`, TRACKED):** a failed `mv` is now
fatal, and the written size is confirmed against the expected size rather than `mv`'s status
alone. **Validated against the failure that exposed it** — it now dies with the byte counts and
says to run regen on a local filesystem. `bash -n` clean.
**A SECOND SILENT FALLTHROUGH, SAME RUN.** The first attempt on the main PC used MSYS2's bash,
**which ships without `git`** — so every probe in `resolve_repo()` failed, control fell through to
a NETWORK fetch, and it died with `(network?)` while `vendor/sm64ex-cache.git` sat there holding
the pinned SHA. **The cache was always sufficient; no network was ever needed.**
**FIXED IN SOURCE:** `resolve_repo()` now checks for `git` first and names Git Bash. Verified by
running it on a PATH with no `git` — the new message fires ahead of the old one.

### ►►►► RESOLVED, SAME SESSION. `[MEASURED]` ◄◄◄◄
Regen run from **Git Bash** on the main PC: **433,892 bytes — exactly the figure predicted from
the bridge** — `dlgrab` 5 hits, `ge_pace_wait_ms` 3 hits, and
**`fetch-thirdparty: 15/15 files match pristine + patch`, zero `DIFFERS`.**
**The patch now reconstructs the whole third-party tree, `GETV_DLGRAB` included. A fresh clone
gets F9 back.**

## §8 — NOT CLAIMED
- **No GPU figure of any kind.** Not measured, not inferred from how the runs looked.
- **No claim that 0.259 ms holds in a heavier scene.** One level (stage 34), stationary plus a
  short route. A crowded firefight is not sampled and the worst window max (1.294 ms at 90) is
  the tail this run actually saw, not the game's worst.
- No claim about `outside` beyond an order of magnitude — see §4.
- No claim that the arms are comparable as GAME CONTENT: at 90 Hz the synthetic clock still runs
  the game 1.5x (`RB-04`, STAGE 4), so equal frame counts are not equal play.
- Nothing here touches `265` §6's shirt probe, and nothing here was built for it.
- **No claim that anything PREVENTS the next stale patch** — two silent fallthroughs were fixed,
  but nothing yet makes a commit refuse to proceed on a stale patch. `commit-now.ps1:193` still
  only WARNS. That is a candidate, not a decision, and it is the owner's call.
