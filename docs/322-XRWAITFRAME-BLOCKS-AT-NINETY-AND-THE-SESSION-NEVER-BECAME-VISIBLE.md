# `322` -- **`xrWaitFrame` BLOCKS, TO `11.1111 ms`, AND THE SESSION NEVER GOT PAST `SYNCHRONIZED`**

**2026-09-05. OFFLINE ASSISTANT. NOTHING BUILT, RUN, STAGED, COMMITTED, BRANCHED, MERGED OR
TAGGED BY THE ASSISTANT.** Two owner pastes on the main PC: one compile, one run.
**No PRODUCT source edited; `gevr_xr.c` md5 `2de74d753289fe82b2f07c863ea10c37` before and
after, gated in the build block and printed by the owner.**

---

## section 0 -- **WHAT THIS SESSION DID, IN FIVE LINES**

1. **Confirmed the disk before writing anything.** `9e69356` / `7a096e5`, `repo/docs` exactly
   `57` ` M`, `repo/xr` clean. **`321` owed nothing** -- `NEXT-SESSION-PROMPT-322`'s commit
   block was dead on arrival by its own instruction.
2. **Wrote the plan FIRST and stopped** (`PLAN-322-X3.md`), including the falsifier and two
   forks. **The owner green-lit it, chose FORK 1 option `A`, and CUT ARM B.**
3. **Edited ONE TRACKED INSTRUMENT, `+9 / -0`:** a `GE_S2_NO_MAIN` guard around slice 2's
   `main`. **Not product. Not one of the four `X2` gates.**
4. **Wrote `repo\xr\gevr_xr_slice3.c` (`454` lines) and `RUN-SHEET-322.md`** with five
   predictions pre-registered before the harness could run.
5. **The owner built it and ran it. `EXIT 0`. `X3-1`, `X3-2` and `X3-4` land; `X3-3` is
   recorded and it is the limit on everything else here.** `X4` is not started.

---

## section 1 -- **`X3-1` LANDS, AND IT IS THE ONLY THING THAT COULD HAVE KILLED `D-X3`**

`[MEASURED]` `repo\xr\gevr_xr_slice3_report.txt`, `5283` bytes at **`19:11`**, from
`gevr_xr_slice3.exe` `290716` bytes at `19:05`. `SteamVR/OpenXR v2.16.7` / `aapvr`,
`RTX 5090`, GL `4.6.0 NVIDIA 616.56`. **`[smoke3] EXIT 0`.**

**`600` frames of `xrWaitFrame -> xrBeginFrame -> xrEndFrame(layerCount 0)`. `570` scored
after a `30`-frame warm-up.**

| | `[MEASURED]` |
|---|---|
| interval between `xrWaitFrame` returns | **mean `11.1188 ms`**, min `10.7108`, max `11.5028` |
| the same, as a distribution | **`p50 11.1119`, `p95 11.1386`, `p99 11.3367`** |
| `predictedDisplayPeriod` | **`11.1111 ms`, min AND max, spread `0.0000%`** -> **`90.0001 Hz`** |
| wall clock | `6337.70 ms` measured against `6333.33 ms` at exactly one period per frame |
| `XR_FRAME_DISCARDED` | **`0` of `600`** |

**`xrWaitFrame` BLOCKS, AND IT BLOCKS TO THE PERIOD IT ADVERTISES.** The falsifier was written
to catch the opposite -- a call that returns at once, exit `7`, `D-X3` dead -- and **it did not
fire.** `PRIORITY-BOARD-320` section C's `X3` is answerable and the answer is yes.

**AND THE FOUR `X2` GATES RE-PASSED FROM THE GUARDED FILE, IDENTICALLY:** eight formats in the
same order, two swapchains at `4140 x 3292`, three images each, GL names **`1 2 3`** and
**`4 5 6`**, `UNKNOWN -> IDLE -> READY` in **`0 ms`** of the `5000 ms` budget. **The regression
check was there to prove the guard disturbed nothing, and it proved it by running rather than
by asserting.**

---

## section 2 -- **THE FOUR THINGS THE RUN SAID THAT NOTHING PREDICTED**

### 2.1 -- **THE SESSION WENT `SYNCHRONIZED` AT FRAME `1` AND NEVER MOVED AGAIN**

`[MEASURED]` **`X3 state READY -> SYNCHRONIZED at frame 1`, one transition in `600` frames.**
Never `VISIBLE`, never `FOCUSED` -- **which is exactly right for an app that submits no
layers**, and it is the mechanism behind `X3-3`.

**SO THE HEADLINE NUMBER IS: SteamVR PACED A `SYNCHRONIZED` SESSION AT THE FULL PANEL RATE.**
It did not throttle a session that was giving it nothing. **That is more than the falsifier
asked for and it is still less than a rendering loop** -- section 3.

### 2.2 -- **THE PERIOD IS NOT "ABOUT `90`". IT IS A LITERAL CONSTANT**

`[MEASURED]` `predictedDisplayPeriod` min and max are **the same number**, `11.1111 ms`,
spread **`0.0000%`** across `570` frames. **`X3-2` LANDS and `gePortSimHzResolve()`'s one-shot
read is safe ON THIS RUN.**

**DO NOT PROMOTE THAT INTO A GUARANTEE.** `XR_EXT_view_configuration_views_change` is
advertised by this runtime (`gevr_xr.h`), the owner can move a SteamVR slider, and a headset
can change mode. **What is measured is that it did not move for `6.3` seconds in one state.**

### 2.3 -- **THE LOOP RUNS `0.0077 ms` A FRAME SLOWER THAN THE PERIOD, AND THE COST IS FLAT**

`[ARITHMETIC]` from the table: `11.1188 - 11.1111 = 0.0077 ms` per frame, and independently
`(6337.70 - 6333.33) / 570 = 0.00767 ms` per frame. **The two agree, so the excess is a
CONSTANT PER-FRAME COST and not a handful of stalls hiding in a mean** -- which is the whole
reason `285` section 3.3 made this project report distributions. `p95` is `+0.0275 ms` over the
period; only `p99` (`+0.2256`) and `max` (`+0.3917`) stretch, and `min` at `-0.4003` is the
catch-up after one of them.

`[ARITHMETIC]` `0.0693%` slow, which is **`2.5` seconds per hour** if nothing ever corrects it.
**Nothing here says whether the runtime corrects it; the harness does not run long enough to
say and it must not be assumed either way.**

### 2.4 -- **AND IT IS FINER THAN THE PACER IT WOULD REPLACE CAN EXPRESS**

`[ARITHMETIC, SOURCE]` `sync_framerate_with_timer()` sleeps through `sys_sleep()`, which is
`SDL_Delay((Uint32)(us / 1000.0))` (`port_support.c:47`) -- **it TRUNCATES to whole
milliseconds**, then books `frame_time = now + remain` from the UNtruncated figure.
**Its granularity is `1 ms` against a period of `11.1111 ms`: `9%`.** `xrWaitFrame`'s measured
`p95` sits `0.0275 ms` off the period: **`0.25%`.**

**THIS IS A COMPARISON OF GRANULARITY AGAINST MEASURED SPREAD AND NOT A LIKE-FOR-LIKE ARM.**
The honest comparison already has an instrument -- `287`'s `ge_pace_req_ms` beside
`ge_pace_wait_ms`, and `GETV_PACEHIST` -- **and it has never been run at `90 Hz` for this
purpose.** `285` section 1.1's booking error is the name this project already gave it.
**NOT RUN TODAY, NOT FILED, and it is a cheap arm somebody should want before `D-X3` is built.**

---

## section 3 -- **`X3-3`, AND IT IS THE LIMIT ON EVERYTHING ABOVE**

`[MEASURED]` **`shouldRender` was FALSE on all `570` scored frames.**

**SO THE CADENCE IS NOT EVIDENCE ABOUT A RENDERING GAME LOOP.** It establishes that
`xrWaitFrame` blocks, that it blocks to `11.1111 ms`, and that it does so in a `SYNCHRONIZED`
session that submits nothing. **A loop that acquires, draws two `4140 x 3292` eyes and submits
a projection layer is a different load and this run says nothing about it.**

**THE INTERPRETATION WAS PRE-REGISTERED IN `RUN-SHEET-322` SECTION 3 BEFORE THE OUTPUT EXISTED,
AND IT IS BEING HONOURED RATHER THAN RE-READ.** No submit was added to make it real, and the
frame count was not raised and re-run. **That is the rule `RUN-SHEET-321` section 3 wrote for
the poll budget, pointed at this loop.**

---

## section 4 -- **`X3-4` LANDS, AND THE COLLISION IS `274`'s NUMBER TO FIVE DECIMAL PLACES**

`[MEASURED]` the runtime presents at **`90.0001 Hz`**. `[ARITHMETIC]` `GE_FRAMERATE_DEFAULT` is
**`60`** (`gfx_sdl2.c:99`), and `gePortSimHzResolve()` on the `query` branch sets
`rate = ge_pace_framerate` **once, then caches** (`frametiming.c`).

**`90.0001 / 60 = 1.500002`. `274` section 2 measured the world running `1.500x` too fast at
`GETV_FPS=90` against the owner's stopwatch at `1.487`.** So a `D-X3` that lets `xrWaitFrame`
take the clock while `ge_pace_framerate` keeps its default **reproduces `274`'s fault exactly,
through a door `277` never had to close** -- because until today the pacer's period and the
sim's divisor were the same variable and could not disagree.

**THE INTERLOCK IN `PLAN-322-X3` SECTION 6 IS NOW OWED, AND IT IS `277` ARM `D2`'s SHAPE, NOT A
NEW INVENTION:** on the frame the session goes live, compare `predictedDisplayPeriod` against
`ge_pace_framerate`, and **on a disagreement print `CONTAMINATED`, name both numbers, and refuse
the term** -- as `gePortSimHzResolve()` already refuses a pin that disagrees with the pacer and
as `GETV_REALCLOCK=1` already refuses to be scaled twice.

**THIS IS NOT FILED AND IS NOT A HOLE** (`301` section 0). It is a design consequence, written
down, owed by whoever builds `D-X3`. **`169` NEXT ID = `U-28`. NEXT INSTRUMENT HOLE = `H25`.**

---

## section 5 -- **WHAT `X3` DOES NOT ENTITLE ANYONE TO CLAIM**

- **NOT that a frame has been rendered.** `layerCount` was `0` on every one of the `600`
  frames. Nothing was acquired, nothing bound, nothing drawn, nothing submitted.
  **THE HEADSET STILL SHOWS NOTHING AND THE REPORT NEVER SAYS IT DOES.**
- **NOT that the pacing handover is built.** `D-X3` is designed and measured-for, not written.
  `sync_framerate_with_timer()` is untouched, `port_render.c` is untouched, `frametiming.c` is
  untouched.
- **NOT that `a = 1.060225` is a measurement.** `[DISPOSAL] 9a` stands, `gfx_current_dimensions`
  is still the SDL window at `gfx_pc.c:6062`. **`H19` OPEN AND UNPATCHED. WRONG FILED FIXES
  STAY AT FIVE.**
- **NOT that the game build is closer to linking OpenXR.** `GEVR_XR_HAVE_OPENXR` is still
  undefined for the game, `build_windows.ps1` is unedited, **THE LOADER IS STILL NOT VENDORED**,
  and the game still compiles the inert stub.
- **NOT that the format question is answered.** `321` section 2.2's debt is still owed **BY THE
  EYE LOOP**: slice 3 inherited `GL_SRGB8_ALPHA8` and never rendered into it, so the choice was
  not load-bearing here and paying the debt from a timing harness would have been paying it
  with the wrong reason. **STILL NOT `U-29`.**
- **`U-28` STILL RESERVED AND UNFILED.**
- **`H24` still blinds every `WS=1` arm.** The 57-file username scrub is still nobody's.

---

## section 6 -- **WHAT `322` LEAVES ON DISK**

| file | state | owed? |
|---|---|---|
| `repo/docs/PLAN-322-X3.md` | `??` | **YES** -- it carries the pre-registration and both forks |
| `repo/docs/RUN-SHEET-322.md` | `??` | **YES** -- the sheet AND the result |
| `repo/docs/322-...md` (this file) | `??` | **YES** |
| `repo/docs/NEXT-SESSION-PROMPT-323.md` | `??` | **YES** |
| `repo/docs/00-STATE.md` | ` M` (deliberate) | **YES** -- currency + section 3 |
| `repo/xr/gevr_xr_slice2.c` | ` M` `+9/-0` | **YES** -- the `GE_S2_NO_MAIN` guard |
| `repo/xr/gevr_xr_slice3.c` | `??` | **YES** -- the instrument the write-up is about |
| `repo/xr/gevr_xr_slice3.exe`, `..._report.txt` | ignored | **NO** -- `repo\.gitignore` |

**`-- repo/docs` WILL READ `58` ` M` AND `4` `??` BEFORE THE COMMIT:** the 57-file scrub **plus
`00-STATE.md`, which `322` edited deliberately.** **The 57 must still read ` M`, unstaged,
after any add.**

**TWO COMMITS, SPLIT ON `321` section 4.1's ARGUMENT:** the docs, then the instrument. A reader
who bisects should be able to take the write-up without the harness or the harness without the
write-up. **The blocks are in `NEXT-SESSION-PROMPT-323` section 2, they are path-list adds, and
each names its own `-F` message file so `COMMIT-NOW.cmd`'s newest-file substitution is never
relied on** (rule `17`).

### 6.1 -- **A HYGIENE FACT, PAID FORWARD FROM `321` section 6.2**

**`| Out-File -Encoding utf8` WORKED AND `Select-String` MATCHED.** `[MEASURED, BRIDGE]`
`gevr_xr_slice3_report.txt` is **UTF-8 with a BOM, CRLF**, `5283` bytes for ~`5.2` KB of text --
readable straight through the bridge, unlike `319`'s and `321`'s `UTF-16LE`.
**THOSE TWO ARE STILL NOT RE-RUN.** The change belonged in the new block and that is where it
went.

---

## section 7 -- **THE STOPPING LINE, AND IT IS `7c`**

**`X4` IS NOT STARTED.** The eye loop -- acquire, bind, draw, submit a projection layer -- is a
`HIGH`, it is the thing `X3-3` says this run cannot speak for, and `00-STATE` section 7c says a
`HIGH` is not opened at the end of a session.

**NEXT: `322`'s TWO COMMITS, THEN A FRESH SESSION.** The board's next question is one of two and
the owner picks: **`X4`, the eye loop** (which also pays the format debt and calls in the loader
vendoring the moment it needs the game build), or **the cheap `287`/`GETV_PACEHIST` arm at
`90 Hz`** that would make section 2.4's comparison like-for-like before `D-X3` is written.
