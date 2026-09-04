# 276 — SHAPE 3 IS WRITTEN. THE PRICE WAS THE TWO SITES `275` PRICED, AND ONE THE HARNESS FOUND.

**2026-08-30m. Docs run to `276`. NEXT DOC = `277`.**
**`258` STAGE 4's FIX. CODE WAS WRITTEN. NOTHING WAS BUILT AND NOTHING WAS RUN** — the
bridge is a Linux VM with no mingw toolchain and no Windows binary. **Every claim below is
`[MEASURED]` from source or from a standalone harness that ran; NOTHING is `[MEASURED]` from
the game.** The run sheet, the prediction and the falsifier are `RUN-SHEET-276.md`, written
before the build, per `15`.

> # ►►►► THE TERM EXISTS: `GETV_SIMHZ`. DEFAULT OFF, QUERIED OR PINNED, AND IT REFUSES. ◄◄◄◄
> # AND THE FIRST CUT OF IT WAS WRONG IN A WAY ONLY AN INSTRUMENT COULD HAVE CAUGHT:
> # **AN `f32` CARRY LOSES 0.1 OF A FIELD EVERY SECOND AT 72 AND 144 Hz.** §3.

---

## §1 — WHAT WAS WRITTEN. FIVE FILES, AND THE SEAM IS ONE LINE.

`275` §5 chose SHAPE 3: an INTEGER `g_ClockTimer` beside a genuinely fractional
`g_GlobalTimerDelta`. Retail collapses them — `lv.c:1151` is literally
`g_GlobalTimerDelta = (f32) g_ClockTimer;` — and that cast is exact only while a rendered
frame is worth exactly one video field, which is what stops being true above 60 Hz (`274` §2,
the 1.500x).

| file | what changed | lines |
|---|---|---|
| `frametiming.c` | `GETV_SIMHZ`: the gate, the rate source, the carry, the banner, the three refusals, the accessors; the fractional twin of `ge_sim_pending_fields`; `[getv][clock]` now prints the term and the delta | +198 |
| `lv.c` | the seam. `g_ClockTimer` integer, `g_GlobalTimerDelta` fractional, new `g_GlobalTimerFieldDelta`; whole retail block kept verbatim under `#else` | +87 |
| `lv.h` | `extern f32 g_GlobalTimerFieldDelta` | +5 |
| `bondview2.c:7330` | HOIST 1 — the tank turret | +12 |
| `propobj.c:5065` | HOIST 2 — projectile ground friction | +11 |

**EVERY EDIT IS INSIDE `#ifdef GE_PORT_NATIVE`.** The N64 path keeps the retail lines
verbatim and gains no data and no store, so the matching build is untouched — which is what
makes `258` STAGE 4's *"did we change the feel"* answerable as a diff rather than an opinion.

### 1.1 — THE THREE TERMS, AND WHAT EACH IS FOR

| | at 90 Hz | per real second | who reads it |
|---|---|---|---|
| `g_ClockTimer` | `0,1,1` | **60** | 122 frame-counted files; 24 iteration sites; `g_GlobalTimer += g_ClockTimer` |
| `g_GlobalTimerDelta` | **`0.667` EVERY frame** | 60 | the 13 delta-scaled files — animation, recoil, sway, camera |
| **`g_GlobalTimerFieldDelta`** (new) | `1.0` | — | **exactly two sites**, `275` §4's — the delta for ONE WHOLE FIELD, for use inside a `g_ClockTimer` loop |

**`g_GlobalTimerFieldDelta` IS `g_GlobalTimerDelta` WHENEVER THE KNOB IS OFF**, on every
version including EU's `* 1.2f`. That is not an argument, it is the construction: both are
assigned from the same local in the same block.

### 1.2 — PAUSE IS NOT A SPECIAL CASE, AND THAT IS WHY THE FOUR UNGUARDED SITES NEED NO WORK
`lv.c` forces `g_ClockTimer = 0` when controls are locked or the game is paused. The delta
must go to zero with it or the world moves through the pause, so a `simFrozen` flag carries
that branch into the new assignment. **That is the ONLY path on which SHAPE 3 produces a zero
divisor — which is exactly retail behaviour**, and it is precisely why `275` §2's four
unguarded sites (`front.c:8941-8943`, `propobj.c:2393`) are left alone. **The cast-camera NaN
trap is not armed by this change.** Shape 1 would have armed it at p=1/3 per cast.

## §2 — `258` §3.2 IS HONOURED, NOT RETROFITTED

> *"THE SIM STEP MUST BE A VALUE THE PROGRAM CAN BE TOLD, NOT ONLY A VALUE IT COMPUTES...
> It is a rewrite if it is added afterwards."*

```
GETV_SIMHZ=query   (or auto)   rate QUERIED from ge_pace_framerate (gfx_sdl2.c:106)
GETV_SIMHZ=<n>                 rate PINNED — supplied, not measured, so it cannot float
                               under load and 271/272/273 stay comparable
unset, or =0                   OFF. Retail arithmetic. 48's one behaviour change.
```
`P3`'s shape holds for free: **one runtime variable, one banner, one place to pin.**
The numerator is `#define GE_SIMHZ_AUTHORED_HZ 60` and is never a literal at a use site (`P1`).

### 2.1 — IT REFUSES RATHER THAN SUBSTITUTES. RULE `17`, AND `274` §7's OWED GATE IS PAID.
| condition | what it prints | term |
|---|---|---|
| `GETV_REALCLOCK=1` also set | `CONTAMINATED` — a field is already real time; scaling it again counts the same seconds twice | **OFF** |
| queried with the cap OFF (`GETV_FPS=0`) | `CONTAMINATED` — 60/0 is not a number | **OFF** |
| rate outside 1..1000 | `CONTAMINATED` | **OFF** |
| pinned `!=` `ge_pace_framerate` | `CONTAMINATED` — **the pin is HONOURED**, that is what a pin is for, but every timing number from the run is VOID | **ON** |

**`GETV_REALCLOCK` was owed a gate by `274` §7 and still does not have one of its own. It now
has one from the other side**: the two knobs together are refused, loudly, by name.

## §3 — ►► THE HARNESS FAILED, AND THAT IS THE POINT OF WRITING ONE. `getv/tools/simhz_harness.c`.

`15` says build the instrument and state what it would print if pointed at the wrong thing,
**before** the run. The accumulator was lifted out of `frametiming.c` into a standalone C
program and run at 60, 72, 90, 120, 144 and 165 Hz, ten seconds each and one hour at 90.

**THE FIRST CUT CARRIED THE FRACTION IN AN `f32` AND FAILED:**

```
144 Hz x 10s:  g_ClockTimer fields per real second   got 59.90000   want 60.00000   FAIL
 72 Hz x 10s:  g_ClockTimer fields per real second   got 59.90000   want 60.00000   FAIL
```

`60/72` and `60/144` are not representable in binary. The residual accumulates: **599 fields
where 600 were owed — a 0.17% slow clock at every rate whose ratio is not a clean binary
fraction.** No play session would notice it and no timing run could have explained it.
**90 and 120 Hz PASSED, so a harness that only tested the target rate would have shipped it.**

**THE FIX: THE CLOCK CARRY IS INTEGER.** Count in 60ths of a field —
`carry += 60 * deltaFrames; whole = carry / rate; carry -= whole * rate` — which is exact at
every rate by construction. The **delta** stays `f32` and is fine, because it is a constant
that is read, never accumulated.

**RE-RUN, ALL PASS:**

| rate | `g_ClockTimer` fields/s | delta summed/s | delta ever 0 | longest `g_ClockTimer==0` run |
|---|---|---|---|---|
| 60 | 60.000 | 60.000 | no | 0 |
| 72 | 60.000 | 60.000 | no | 1 |
| 90 | 60.000 | 60.000 | no | 1 |
| 120 | 60.000 | 60.000 | no | 1 |
| 144 | 60.000 | 60.000 | no | 2 |
| 165 | 60.000 | 60.000 | no | 2 |
| 90, one hour (324,000 frames) | 60.000 | 60.000 | no | 1 |

**"delta ever 0: no" is the column that separates SHAPE 3 from SHAPE 1**, and the harness would
print `1` there if this were shape 1. **`60.0f/60` is EXACTLY `1.0f`**, checked, so the term
switched ON at 60 Hz is bit-identical to the term OFF.

## §4 — `275` §9's ONE OPEN CLASS IS NOW CLOSED. THE COUNT OF TWO IS EXACT.

`275` §9 flagged the one way its count of two could be low: *"a delta reference reached through
a FUNCTION CALL made inside a `g_ClockTimer` loop. That class is unread."*

**IT IS READ NOW.** A parser walked every `for`/`while` whose condition names `g_ClockTimer`,
matched its body's braces, and listed both the delta references and every call in it.

- **`[MEASURED]` 24 iteration sites — exactly the count `275` §1 reported.**
- **`[MEASURED]` exactly 2 carry a delta reference: `bondview2.c:7328`, `propobj.c:5057`.**
  The two `275` §4 named, and no others.
- **`[MEASURED]` the ONLY functions called from any of the 24 loop bodies are `sqrtf`,
  `matrix_4x4_multiply_homogeneous_in_place` and its `_eu` twin.** `matrixmath.c`, which
  defines both, contains **zero** references to `g_GlobalTimerDelta`.

## §5 — WHAT IS NOT CLAIMED. READ THIS BEFORE CITING ANYTHING ABOVE.

- **NO BUILD. NO RUN. NO LOG. NO GAME BEHAVIOUR IS MEASURED HERE.** The bridge is a Linux VM
  with no mingw toolchain; `build_windows.ps1` is a main-PC action (`RUN-SHEET-276.md` STEP B).
- **`239`'s GATE IS NOT MET.** It is met for the timebase (`274`) and the shape (`275`). A fix
  that has never run at two rates is not a setting.
- **The harness is the ACCUMULATOR, not the game.** It proves the arithmetic carries without
  drift and that the delta is never zero. It proves nothing about animation, recoil, AI
  stepping or anything else that reads either term.
- **`g_GlobalTimerFieldDelta`'s two sites are TESTED BY READING, not by playing.** Nobody has
  driven the tank or slid a grenade at 90 Hz. Both are enumerated in `RUN-SHEET-276.md` as
  named things to look at.
- **The syntax check is `gcc -fsyntax-only` with hand-rolled include paths, not the real
  build.** `[MEASURED]`: the diagnostic count for each of the four `.c` files is **identical
  to the same file at `HEAD`** — 0, 0, 12, 394 — so the edits add no new diagnostic. **The
  12 and the 394 are artefacts of the ad-hoc invocation and exist at `HEAD` too.** A clean
  compile is STEP B and has not happened.
- **`GETV_SIMHZ` is now IN THE SOURCE and is still IN NO BINARY.** `133`, `268` §4: until the
  banner is in a log, a knob that is not in the binary reads as a clean null result.
- **Nothing here touches STAGE 5 (the pose spine) or STAGE 6 (stereo), and the order stands.**

## §6 — ►► A COMMIT TRAP FOUND WHILE PREPARING THIS ONE. IT IS NOT ABOUT THE CLOCK.

`[MEASURED]` from `commit-now.ps1` and `commit-session.ps1`, read this session:

1. **`COMMIT-NOW.cmd` COMMITS THREE REPOS AND `vendor/ge-decomp` IS NOT ONE OF THEM.**
   `GoldenEyeVR`, `GoldenEye64Recomp`, then `goldeneye-native` — and `vendor/` is gitignored by
   `goldeneye-native` (`.gitignore:42`), so the decomp is invisible to every pass. The
   `-decomp.txt` message files in the tree were committed by hand. **`276`'s entire change is in
   the decomp**, so double-clicking `COMMIT-NOW.cmd` and stopping there would commit the docs,
   the harness, and none of the fix. This is rule `17`'s shape exactly: a tool that reports
   success while doing less than the name implies.
2. **AND `git add -A` THERE IS WORSE THAN USELESS.** `[MEASURED]` `HEAD` is LF throughout; the
   worktree has **2,106 files converted to CRLF**, each diffing as a whole file. **The history
   already contains one of these sweeps**: `7a4e7bfd`, subject *"fix: three pointer-size errors
   the -w build never warned about"*, is **736 files and 601,764 insertions.**
3. **DISCLOSED, BECAUSE IT IS A SILENT CHANGE:** the five files `276` edited were rewritten
   through a text-mode read/write and are now **LF, matching `HEAD`** — which is why their
   diffs are 311 lines and not five whole files. If they were CRLF before, that normalisation
   is mine and it is confined to those five. **Nothing else was touched and nothing was
   normalised wholesale.**

**THE REMEDY IS AN EXPLICIT PATH LIST, IN `RUN-SHEET-276.md` STEP A.** The churn itself is a
decision for the owner and is NOT actioned here.

## §7 — WHAT THIS DOES TO `00-STATE`

- **§3 item 4 moves from "the fix is not written" to "written, not built, not run."**
- **§4 gains nothing** — no standing claim was retracted this session. `275` §9's open class was
  CLOSED, not overturned (§4 above).
- **§5 gains nothing.** Shapes 1 and 2 were already dead in `275`; they are now dead in code.
- **The currency line goes to `2026-08-30m`, docs to `276`.**
