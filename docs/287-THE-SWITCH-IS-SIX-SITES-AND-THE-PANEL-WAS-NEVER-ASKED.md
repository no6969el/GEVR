# 287 — THE SWITCH IS SIX SITES, NOT FOUR; THE TURN IS ALREADY DELTA-SCALED; AND NOTHING HAS EVER ASKED THE PANEL.

**2026-08-31. SOURCE READ + CODE WRITTEN. NOT BUILT, NOT RUN.** Same posture as `285` and `276`:
written before the build so nothing is lost if the session ends here.
**Run sheet: `RUN-SHEET-287.md`. Binary in play when this was written: `2026-08-31 01:07`,
18,021,956 bytes — the `286` binary.**

---

## §1 — `286` §1's SITE LIST IS WRONG IN BOTH DIRECTIONS. `[MEASURED]`, source.

`286` named four sites that fetch the per-room rectangle and clip to it. A grep of **every**
consumer of `dword_CODE_bss_8007FFA0[].bbox` — through `getPropCombinedRoomsBBox2D` **and**
through `bgGet2dBboxByRoomId` directly — returns nine, in four classes:

| site | function | class | `287` |
|---|---|---|---|
| `bg.c:1051` | room primary | SCISSOR | already switched; now carries a site index |
| `bg.c:1132` | room secondary/xlu | SCISSOR | already switched; now carries a site index |
| `chr.c:3437` | `chrRender` | SCISSOR | **switched** |
| `explosion.c:874` | explosion | SCISSOR | **switched** |
| **`explosion.c:1486`** | **smoke** | SCISSOR | **switched — NOT IN `286`'s LIST** |
| `propobj.c:7570` | prop/obj | SCISSOR | **switched** |
| **`propobj.c:14007`** | `posIsOnScreen` | **CULL** | **own knob, `GETV_PROPCULLBOX`** |
| **`chraction.c:10770`** | `chrIsPosOffScreen` | **AI / SPAWN LOGIC** | **NEVER SWITCHED** |
| ~~`chr.c:186`~~ | `ge_chr_dbg_vis_breakdown` | **read-only debug** | **not a site; no edit** |

**Three findings in that table:**

**1.1 — SMOKE WAS MISSED.** `explosion.c:1486` is textually the same shape as `:874` and does the
same thing to smoke. **A build following `286` §1 verbatim leaves smoke clipped, and would then
read the surviving artifact as "the extension took and holes still survive."**

**1.2 — `chr.c:186` IS NOT A CLIP SITE.** It is `ge_chr_dbg_vis_breakdown`, gated on
`ge_chr_dbg_on()`, which re-evaluates `posIsOnScreen`'s predicate chain to name which
sub-predicate rejected a chr. **It sets no scissor and clips nothing.** Switching it would edit a
diagnostic. `286` listed it as one of the four.

**1.3 — ►►►► THE CHOKEPOINT DESIGN IS FATAL, AND `chraction.c:10770` IS WHY. ◄◄◄◄**
The tidy move is one knob inside `bgGet2dBboxByRoomId` (`bg.c:928`) — one edit, every consumer.
**`chrIsPosOffScreen` (`chraction.c:10770`) reads it directly and is AI/SPAWN LOGIC**: chrs decide
behaviour on whether a position is off screen. A chokepoint knob **silently changes what
characters do**, which is rule `3`'s "careful — anything the player feels", diffed against the
decomp. **It must be six call-site edits. It is now six call-site edits.**

**1.4 — AND `propobj.c:14007` IS A DIFFERENT SYMPTOM, NOT A SIXTH CLIP.** `posIsOnScreen` feeds
the same rectangle to `camIsPosInScreenBox` and uses the answer to decide whether a prop is
**drawn at all**. A too-tight rectangle there **removes** an object rather than clipping it.
`279` §6 `[MEASURED]` that every slab in all five admissible frames is the **see-through** class
and that **not one frame shows the BLACK-WALL symptom**, which still has no dump at all
(`280` §7.3, owed for four sessions). **A vanished prop is a candidate mechanism for that second
symptom.** It gets `GETV_PROPCULLBOX=0`, its own banner, its own arm. **`263` §1: do not merge.**

**THE TAKE-COUNTERS ARE THE FALSIFIER FOR "DID THE EXTENSION TAKE".** Rule `15` — a counter that
is never printed is not an instrument — so `getv_roomscissor_report()` prints at `game_exit`:
`[getv][roomscissor] sites: bg_pri=.. bg_sec=.. chr=.. expl=.. smoke=.. prop=..`.
**A zero on `chr`/`expl`/`smoke`/`prop` in a level that draws them means that site never ran —
which is precisely the state `286` was in and could not see from any log.**

## §2 — `285` §1.4 IS ANSWERED FROM SOURCE. THE TURN IS DELTA-SCALED. `[INFERRED]`, source read.

The report is about turning, and `285` §1.4 asked whether the LOOK/TURN rate is in the same family
as `277` §4's walk — an approach advanced once per FRAME with no timestep. **It is not:**

- **`bondview2.c:7366`** — `stack_padding_9 = vv_theta + (speedtheta * g_GlobalTimerDelta * 3.5f)`.
  The yaw integration carries the delta.
- **`bondviewCurrentPlayerUpdateSpeedTheta` (`:4573-4630`)** — the turn-rate ramp. **Every** term
  in **all four** branches is `0.05f * g_GlobalTimerDelta * mult` or
  `0.0125f * g_GlobalTimerDelta * mult`. No exception.
- **`:6582`**, the natural-turn branch, assigns `speedtheta` from stick deflection with **no**
  delta — **correct**, because it is a *rate*; `:7366` multiplies it by the delta.

**AND `285` §2's MOUSE-VS-PAD QUESTION NEEDS NO ARM.** `port_input.c` accumulates
`ge_mouse_pend_x`/`_y` **into the stick**, so the mouse arrives as `moveData.analogTurn` and
travels the identical path. **Mechanically they are the same thing**, so `285` §1.4 could not
distinguish them either.

**►► THIS IS A RETRACTION CANDIDATE, NOT A RETRACTION.** `275` §1 (grep-for-a-guard),
`277` §6.2 (numbers without mechanism) and `278` §7.2 (branch not followed) are three sessions of
what happens when a source read is promoted to a measurement. **It gets a stopwatch, and it costs
no build: a full-deflection 360° spin at `FPS=60` vs `FPS=120`, `SIMHZ=query` both, same spot.**
Equal → `285` §1.4 is dead. 120 spinning ~2× faster → the read is wrong and §1.4 is alive.
**`bondviewApplyVertaTheta` and the pitch path have NOT been read.**

## §3 — ►►►► NOTHING IN THIS PORT HAS EVER ASKED THE DISPLAY WHAT IT IS. `[MEASURED]` ◄◄◄◄

`285` §2 said no run log records the panel's refresh rate. **It is worse than that: no CODE asks.**
A grep of `getv\port` for `GetCurrentDisplayMode`, `GetDesktopDisplayMode` and `refresh_rate`
returns **ZERO hits.** So **"the panel is 120 Hz" is `[REPORTED]`**, it is the input every `285`
candidate is defined against, and `GETV_FPS=<panel Hz>` — the whole of the smoothness fix — is set
against a number the binary has never seen.

**`GETV_PACEHIST` now prints SDL's own answer, once, at the first present.** It is two lines and it
is a standing fix, not an arm. **Its falsifier: if SDL reports 60, then `GETV_FPS=120` with
`vsync=1` is asking for double the panel and `285` S1's "super smooth" needs re-reading before
anything is built on it.**

## §4 — THE COST ARM NEEDS A THIRD RECIPE, AND IT IS IN NO DOC. `[MEASURED]`, source.

`285` and `286` §2 give two recipes: play (`VSYNC=1`, `FPS=<panel>`) and GPU (`VSYNC=0`, `FPS=0`).
**`WORK_OVER=` fits neither, and `port_render.c:1010` says so in its own source, in capitals,
written before the run:**

> **WITH VSYNC ON, THE VBLANK BLOCK IN `SDL_GL_SwapWindow` IS STILL INSIDE `work`. The baseline
> run must pin `GETV_VSYNC=0` or `work` absorbs the very wait this exists to exclude.**

And with **no cap** there is no budget and the pacer never sleeps, so the split is void by the
instrument's own `slept=0` warning. **The CPU term therefore needs a cap AND vsync off:**

| purpose | VSYNC | FPS |
|---|---|---|
| play / look at anything | `1` | `120` |
| GPU (`GETV_GPUTIME`) | `0` | `0` |
| **CPU (`WORK_OVER=`)** | **`0`** | **`120`** |

**PREDICTION, BEFORE THE RUN:** run `WORK_OVER` at `VSYNC=1 FPS=120` and it prints `slept=0` and
its own `<<< PACER NEVER SLEPT IN THIS WINDOW: work==frame, the split is void`. **It fails
LOUDLY.** That is the check that it is `271`'s instrument and not a plausible number.

**AND THE 90 Hz BUDGET IS NOT THE 120 Hz BUDGET.** `[MEASURED]` CPU `0.890` + GPU `0.832` =
`1.722` ms (`272` §5.2, `273` §5.1) were both taken against **`11.111` ms**. At 120 Hz the budget
is **`8.333` ms**, and **neither figure has ever been taken at 120 Hz.** Do not carry
`1.722 / 11.111` forward as if it were the 120 Hz headroom.

## §5 — ►► `gfx_sdl2.c` IS GITIGNORED AND REGENERATED, EXACTLY LIKE `gfx_pc.c`. `[MEASURED]`

**`.gitignore:161`, confirmed by `git ls-files`.** `GETV_PACEHIST` lives in
`getv/port/fast3d/gfx_sdl2.c`, which is produced by `tools/fetch-thirdparty.sh` from a pristine
copy plus `getv/patches/thirdparty/0001-getv-port-layer.patch` — the patch already carries a
`gfx_sdl2.c` hunk at its line 7876. **`00-STATE` §6 names this trap for `gfx_pc.c` ONLY. It
applies to `gfx_sdl2.c` too and nobody had written that down.**

- **`tools/fetch-thirdparty.sh verify` WILL FAIL until the patch is regenerated** — correct and
  expected, because the file on disk now carries an edit the patch does not.
- **A regen run BEFORE that regeneration would DELETE the instrument.** `271` §7: `268` was
  committed without a regen and `GETV_DLGRAB` was absent from a fresh clone for two days, hiding
  behind two silent fallthroughs. **Rule `17`'s family.**
- **The fix is `tools/fetch-thirdparty.sh regen` then `verify`, from GIT BASH on the main PC**
  (the bridge mount refuses to unlink; MSYS2's bash has no `git`). **Gate: `15/15 files match
  pristine + patch`. Run it AFTER the arms are worn**, so the patch captures what actually ran.
- `port_support.c` and the four decomp files are **TRACKED** and unaffected.

## §6 — WHAT THIS SESSION CHANGED IN THE SOURCE

| file | tracked? | change |
|---|---|---|
| `vendor/ge-decomp/src/game/bg.c` | yes | `getv_room_scissor` gains a `site` index + take-counters; `getv_roomscissor_report()`; **new** `getv_propcullbox()`; banner names six sites |
| `vendor/ge-decomp/src/game/bg.h` | yes | exports the four, under `#ifdef GE_PORT_NATIVE` |
| `vendor/ge-decomp/src/game/chr.c` | yes | `:3439` → `getv_room_scissor(..., 2)` |
| `vendor/ge-decomp/src/game/explosion.c` | yes | `:876` → site 3; **`:1488` → site 4 (smoke)** |
| `vendor/ge-decomp/src/game/propobj.c` | yes | `:7572` → site 5; `:14007` gated on `getv_propcullbox()` |
| `getv/port/src/port_support.c` | yes | `game_exit()` calls both reports before the terminating record |
| **`getv/port/fast3d/gfx_sdl2.c`** | **NO — §5** | **`GETV_PACEHIST`**: present-interval distribution, panel refresh, pacer booking error |

**Every knob defaults OFF and announces itself. `gfx_pc.c` is untouched — but see §5.**

**►► AND A SIXTH FINDING, FOUND BY THE COMMIT GUARD RATHER THAN BY ME. `[MEASURED]`**
This session wrote its `-native` message file into `goldeneye-native\` and its `-decomp` one into
`vendor\ge-decomp\` — **beside the repos they describe.** **`commit-now.ps1` globs the
`GoldenEyeVR` ROOT ONLY**, so it saw neither, fell back to the newest `*-native*` in the root —
**`COMMIT-MESSAGE-2026-08-30m-native.txt`, `276`'s harness** — and **the rule-`17` guard refused
it**, naming the subject as already being HEAD. **Every `-native` and `-decomp` message file in
this project's history is in the root; both are now copied there.**
**This is the guard's first real catch.** Rule `17` was added on 2026-08-30 after five
silent-staleness bugs surfaced in one session, every one of which reported success; **this one
reported failure and named why.** `00-STATE` §6 carries it.

**THE THREE COMMITS LANDED AND ARE CORRECTLY LABELLED**, because `git commit -F <path>` takes an
explicit path and bypasses the glob entirely:
| repo | commit | files |
|---|---|---|
| `GoldenEyeVR` | `5ab555b` | 6, **836 insertions** — the five docs + the message file |
| `vendor/ge-decomp` | `2b57c497` | 6, **186 insertions, 6 deletions** — **not** the 2,106-file CRLF sweep |
| `goldeneye-native` | `05ce7b6` | 2 — `port_support.c` + the message file |
| `GoldenEye64Recomp` | untouched | correct; nothing in it changed |
**The explicit path list held.** `00-STATE` §6's `7a4e7bfd` failure (601,764 insertions under a
three-line subject) did not recur.

## §7 — WHAT IS STILL OWED AFTER THIS
- Everything in `286` §4, unchanged except that §1.4 above gives the **black-wall dump** a
  candidate mechanism for the first time.
- The same-spot two-resolution amount arm (`279` §5) — **still no number.**
- All of `277` §9, **untouched through five sessions**: the two hoist sites driven, the two
  intro-skip audio falsifiers, the `MoveBond` executions-per-second counter, plus `278` §6's
  `[INFERRED]` hoist-1 read.
- **`GETV_REALCLOCK` is still owed its `CONTAMINATED` gate** (`274` §7, rule `17`).
- `SETUP.md` §3.5 owes `229` §9's two CSV traps.
- **`00-STATE` is NOT yet updated** — nothing here has been run. It gets its §3/§4/§5 edits and its
  currency bump after the arms, not before.
