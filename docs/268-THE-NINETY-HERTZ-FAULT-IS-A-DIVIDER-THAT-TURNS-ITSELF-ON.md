# 268 — THE 90 Hz FAULT IS A SIMULATION DIVIDER THAT TURNS ITSELF ON. IT IS NOT THE RENDERER.

**2026-08-30. `[MEASURED]` from the owner's own logs, and `[MEASURED]` by the fix:
`GETV_SIMDIV=1` at 90 Hz and the artifacts are gone. Owner: *"Yeah. That fixed it."***

---

## §1 — ►►►► THE FINDING ◄◄◄◄

**At 90 Hz this port silently stops running the simulation every frame. At 60 Hz it does not.**

`run_dlgrab2_90.log`:
```
[getv][simdiv] 90Hz present, simulation held to 30Hz (divider 3). GETV_SIMDIV overrides.
[getv][simdiv] simulation runs 1 frame in 3; rendering every frame. EXPERIMENTAL
[getv][interp] props interpolated 85000 (yaw 25016), skipped 0
```
Every 60 Hz run — `run_dlc_60_a`, `run_dlc_60_b`, `run_tri_60_novsync`, `run_budget_60`:
```
[getv][interp] props interpolated 0 (yaw 0), skipped 0
```
**and NO `[simdiv]` banner at all.**

`GETV_SIMDIV=auto` (`frametiming.c:116`) derives the divider from the present rate so the
simulation lands on `GE_SIM_TARGET_HZ = 30`. At 60 that is a divider of 1 — a no-op. **At 90
it is 3.** Nobody selected it for those runs; asking for 90 Hz selects it.
**The code's own comment calls it `EXPERIMENTAL`.**

## §2 — WHY THAT PRODUCES THE REPORTED SYMPTOMS
- **`[REPORTED]` the ghost truck** — *"a ghost ahead of it that I can walk through, and it's
  transparent and I can't walk through it."* The sim ticks one frame in three; the other two
  draw props **interpolated** between tick states (`lv.c:825`, `gePortPropHistoryTick()`).
  Collision is at the tick position, the drawn copy is between. **A drawn object that is not
  where the game thinks it is.** One copy blocks you, the other does not.
- **`[REPORTED]` the "black triangles"** — `[INFERRED]` mechanism, consistent but not
  separately proven: they are not triangles. GoldenEye clips each room to its portal's screen
  rectangle (`bg.c:1971`, `bgScissorCurrentPlayerView`), and the visibility pass caches the
  portal bounds per portal (`bg.c:2246`) and resets that cache once per pass
  (`bg.c:5680`, `bgDetermineVisibleRooms`). Culling runs every frame (`lv.c:815`,
  deliberately outside the tick gate); the state it culls against only advances on ticks.
  **Where a room is clipped away you see the sky, with hard vertical and horizontal edges —
  which is exactly what the owner's screenshots show.**
- **`[REPORTED]` "the wall behind me glitching forward"** — the same, one frame later.

## §3 — THE PROOF, AND WHAT WOULD HAVE FALSIFIED IT
`[MEASURED]` One launch, no build: `GETV_FPS=90 GETV_VSYNC=0 GETV_SIMDIV=1`.
**Written before the run:** the ghost goes, the rectangular holes go; the 1.5x speed stays
because that is `RB-04` and a different fault; **if the artifacts survived, simdiv was
exonerated and §1 was wrong.** They did not survive. Owner: *"Yeah. That fixed it."*

## §4 — ►► WHAT IS RETRACTED, AND ALL FIVE ARE MINE ◄◄
| claimed | truth |
|---|---|
| **`00-STATE` §3.5 / this session: the 90 Hz artifact is "geometry, not a texture" and is "in stereo's path"** | **FALSE.** It is neither geometry nor the renderer. It is the simulation cadence, and it says nothing about `lvlRender`'s per-view loop. |
| **`[REPORTED]`-driven framing that this was a TEXTURE fault** (see-through truck, textures not landing) | **The symptom list was right and my reading of it was wrong.** Every item is one cause: draw state that does not match sim state. |
| **The F9 hook in `keyboard_on_key_down()` (`port_support.c:409`)** | **DEAD CODE. Nothing in this port ever calls `gfx_wapi->set_keyboard_callbacks()`, so `kb_key_down` is always NULL.** One full build-and-run cycle produced zero data. The hook now lives at the SDL event (`gfx_sdl2.c:444`), beside the F11 handler that demonstrably works. |
| **`GETV_DLGRAB`'s opcode table calls `0xB1` "TRI2"** | **WRONG NAME.** `0xB1` is GoldenEye's `G_TRI4` extension (`model.c:7265`). The dump says the raw byte is authoritative for exactly this reason; `gfx_pc.c:5675` handles it correctly. |
| **A single-frame grab can show this fault** | **FALSE, and the owner said so first**: *"I'm looking at the pictures you're reading and they don't show what I see."* A capture of one frame cannot contain a fault that lives in the difference between frames. |

## §5 — DEAD THEORIES, DO NOT REOPEN WITHOUT NEW DATA
- **NOT vsync.** Artifact present at 90/vsync=0 and 90/vsync=1, absent at 60/vsync=0. `§1` here.
- **NOT the display list.** `GETV_DLCENSUS` over 48 report blocks: **identical opcode
  vocabulary at 60 and 90 — 34 opcodes, nothing unique to either.** The game emits the same
  kind of list at both rates.
- **NOT a census-visible proportion change.** Two runs at the SAME rate differ by 25-56% on
  `TRI1`/`TEXRECT`. **Averaged proportions are noise at this repro and must not be cited.**
  The 60-vs-60 control arm is what established that, and it is why it existed.

## §6 — WHAT IS NOT CLAIMED
- **The portal-culling mechanism in §2 is `[INFERRED]`.** `GETV_SIMDIV=1` kills the whole
  class at once, so this run does not separate the culling path from the interpolation path.
  A probe on `bgDetermineVisibleRooms` would, and has not been built.
- **No claim that `SIMDIV=auto` is wrong to exist.** It attacks a real problem
  (`frametiming.c:116`: 122 of 135 game files do per-frame work tuned for 20-30 fps hardware).
  **The fault is that it engages ITSELF at 90 Hz, unasked, while marked EXPERIMENTAL.**
- **`RB-04` is untouched.** 90 Hz with the synthetic clock still runs 1.5x fast.
- No claim about the black shirt / Trevelyan face. Nothing here touches those.

## §7 — WHAT THIS OWES NEXT (the decision is the owner's)
1. **The default.** `auto` engaging silently at 90 is what cost this. Options, none taken:
   pin `SIMDIV=1` unless asked; keep `auto` but refuse it above 60; or keep it and fix §2.
2. **If `auto` is to be kept, the fix is in the mismatch, not the divider**: collision must
   read the interpolated transform, or culling must run against the same state it draws.
3. **The audio item is re-ranked.** `[REPORTED]` the late gun sound is present at 60 as well,
   so the pacer is exonerated for it — `port_audio.c:520`'s `want.samples = 512` (23.2 ms by
   the port's own comment at `:63`) is untried and is one line. It was ranked 8. That was a
   ranking error under rule `16`.

## §8 — THE INSTRUMENTS BUILT THIS SESSION (all keep working, all off by default)
- **`GETV_DLCENSUS=<n>` / `GETV_DLCENSUS_AFTER=<f>`** (`port_render.c`, tracked) — per-frame
  display-list census: command count, call/branch/depth structure, full opcode histogram.
  Answered §5's vocabulary question and reported its own noise floor.
- **`GETV_DLGRAB`** (`port_render.c` + `gfx_sdl2.c`, the latter GITIGNORED — **`regen`**) —
  **F9 grabs one frame's entire display list** to `dlgrab_<frame>.txt`: every command with
  raw `w0/w1`, every vertex, every matrix as floats, TRI4 expanded as the RSP expands it, and
  a SUMMARY that says whether the dump is complete. **Pairs a BMP of the same frame by
  construction** (`gfx_opengl.c`, GITIGNORED — **`regen`**), which is `93`'s requirement.
  `GETV_DLGRAB_AT=<f>` and `GETV_DLGRAB_EVERY=<n>`/`GETV_DLGRAB_MAX=<n>` are keyboard-free
  triggers, added because the first key path was silently unreachable (§4).

> ## THE METHOD NOTE, BECAUSE IT IS THE REAL LESSON
> **The owner reframed this and the reframe is what solved it.** *"Why are we taking
> screenshots and tracking logs when we have the source? Ask where it stops agreeing."* The
> answer came from a 60-vs-90 A/B of the port's own startup banners — **four grep-able lines
> in logs that had been sitting on disk** — not from any instrument built that day.
> **THE TWO ARMS ALREADY EXISTED. NOBODY HAD DIFFED THEM.**
