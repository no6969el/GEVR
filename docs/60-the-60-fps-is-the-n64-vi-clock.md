# 60 — the "60 fps" is the N64's VI clock, not the framerate

**2026-08-23. Read from source, and it reframes O7 - which has been open, in one
form or another, for the life of this project.**

---

## The line everyone has been reading

```
[gevr] 60.0 fps | render passes: eye0=90 eye1=90 distinctTargets=90
```

**"60 fps" has been treated as a performance problem since Phase 2.** `00`, `39`
O7 and `49` all discuss why the game is not reaching 90.

## What that number actually counts

`ge_vr_report()` increments `frames` once per call and divides by wall-clock
elapsed. **Its only caller is `RT64Context::update_screen(vi_origin)`**
(`rt64_render_context.cpp:1686`).

`update_screen` is the **VI - the emulated N64's video interface update.** It
fires at the console's video rate, which for NTSC GoldenEye is **60 Hz.**

> **The counter labelled "fps" is measuring the emulated N64's video clock.**
> It cannot report the PC's presented framerate, has never reported it, and
> would read 60.0 on a machine presenting at 30 or at 240.

## The falsification, from data already collected

If it were presented frames it would move with load. **It does not move at all:**

| Run | Workload | Reported |
|---|---|---|
| `-NoXr` | one pass, no VR | **60.0** |
| `-Flat -Offset 500` | **two** full eye passes | **60.0** |
| `-Flat -SkipEye` | one pass | **60.0** |
| `-Flat -Offset 0` | two passes | **60.0** |

60.0 / 60.1 / 59.9, every line, across workloads that differ by a factor of two
in rendering cost. **A real present rate does not do that. A fixed emulated
clock does exactly that.**

## And the number beside it says the renderer IS at 90

`render passes: eye0=90 eye1=90` is counted where the passes are actually run
and reset once per second. **RT64 is running 90 render passes per eye per
second** — the interpolated rate, doing what `rr_manual_value: 90` asks.

## What this means, stated carefully

**It does NOT prove 90 frames reach the display.** It proves:

1. The "fps" line is not evidence of anything about display rate. **Every
   conclusion drawn from it is void** — including "the game runs at 60, not 90".
2. The renderer is producing 90 passes per eye per second.
3. **The gap between those two numbers has never been measured**, because the
   instrument that looked like it was measuring it was measuring the N64.

**This is rule 6 again — a value whose meaning nobody checked — and it is the
seventh instance.** It is also the most expensive one, because unlike a dead
knob it produced a plausible number that shaped the roadmap.

## The fix, and it is small

1. **Rename it.** `vi: 60.0 Hz` — it is a useful line, it just is not fps.
2. **Add a real present counter**, incremented in the draw hook, which runs per
   presented frame. Print both: `vi 60.0 Hz | present 90.0 Hz | passes 90`.
3. **Read `DISPLAY PERIOD`** in a headset session. `ge_vr_xr.cpp:745` prints the
   runtime's own `predictedDisplayPeriod` and it has never been read against a
   measured present rate.

**Gate:** with the real counter in, `-NoXr` on a 180 Hz monitor must NOT read
60.0. If it does, the counter is on the wrong path and the run is void.

## Corrections owed elsewhere

| Doc | Claim | Now |
|---|---|---|
| `39` O7 | "60 fps not 90" | **VOID as stated.** The 60 was the VI clock |
| `00` | "60 fps, closes cleanly" as the `-NoXr` verified row | The 60 there is the VI rate |
| `49` O22 | "8x fewer pixels ran 4x slower (60 to 16 fps)" | **The 60 is void; the 16 is not.** A VI clock falling to 16 means the EMULATOR was starved, which is a different and more serious reading than "the renderer got slower" |
