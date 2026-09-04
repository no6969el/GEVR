# 274 — THE REAL CLOCK CANNOT RUN AT NINETY. THE TIMEBASE IS SETTLED, AND NOT ON DETERMINISM.

**2026-08-30k. Docs run to `274`. NEXT DOC = `275`.**
**`258` STAGE 4's HIGH half — `SESSION-START` §4's named `P1`/`P9` determinism question.
THREE RUNS, NO BUILD. `run_clock_A_60.log`, `run_clock_B_90synth.log`,
`run_clock_C_90real.log`. No code was written and `bondview2.c` was not touched.**

> # ►►►► `GETV_REALCLOCK=1` UNDER A FRAME CAP RENDERS AT **60**, NOT 90. IT IS NOT A
> # TIMEBASE CHOICE FOR A 90 Hz PRESENT — IT IS A 60 Hz RUN WITH A BUSY SPIN IN IT. ◄◄◄◄
>
> **The determinism argument never had to be the deciding one. It is the second one.**

---

## §1 — THE VALIDITY PASS FIRST. `273` §1's RULE: AN ARM IS VOID UNTIL ITS BANNERS SAY OTHERWISE.

`[MEASURED]` all three logs are newer than `goldeneye.exe` (2026-08-30 14:42:53), all three
carry the terminating record `[getv] game_exit requested`, and every `[getv][clock]` line in
all three falls **after** the single `bm:lvlStageLoad` at line 97 — so the whole series is
in-stage and no window is an intro tail.

| gate | A (60, synth) | B (90, synth) | C (90, REAL) |
|---|---|---|---|
| `[getv] pace:` | `60 fps cap on, vsync=0` | `90 fps cap on, vsync=0` | `90 fps cap on, vsync=0` |
| `[getv] clock:` | synthetic | synthetic | **REAL host** |
| `simulation held to` | **0 lines** | **0 lines** | **0 lines** |
| `[simdiv] auto:` | **0 lines** | **0 lines** | **0 lines** |
| `props interpolated` | **0** | **0** | **0** |
| terminator | present | present | present |

**`273` §7.1's gate is met in all three: `GETV_SIMDIV=1` prints nothing, so the positive
evidence is `props interpolated 0` PLUS zero `simulation held to`, and both hold.** `268`'s
divider did not run in any arm. **B and C differ on exactly one banner** — the clock — which
is what makes them a pair.

**AND ARM B IS WHAT EXONERATES THE DISPLAY.** B held 90 fps on the same panel, same
`vsync=0`, same binary, minutes apart. **So C's 60 cannot be the monitor.** That was not the
reason B was in the sheet, and it is the reason it earned its place.

## §2 — THE MEASUREMENT

`[MEASURED]`, first window of each run discarded as boot transient:

| arm | windows | `fps` | `speedgraph` | `g_GlobalTimer` |
|---|---|---|---|---|
| **A — 60 Hz, synthetic (control)** | 29 | **59.7** (min 53, max 60) | **59.7/s** | 59.7/s |
| **B — 90 Hz, synthetic** | 25 | **90.0** (min 89, max 90) | **90.0/s** | 90.0/s |
| **C — 90 Hz, `GETV_REALCLOCK=1`** | 29 | **60.0** (min 60, max 60) | **60.0/s** | 60.0/s |

### 2.1 — `RB-04`, AS A NUMBER, FOR THE FIRST TIME
**Arm B: `speedgraph 90/s`.** The simulation consumes ninety 60 Hz video fields every real
second, so the world runs at **90/60 = 1.500x**. The owner's stopwatch on the fixed route said
**1.487** (`27.04s / 18.18s`). **A stopwatch, a `printf` written months earlier and an
instrument read today agree to under one per cent.** `259` §3 is CONFIRMED by run, not by
reading. Arm B also emits the upstream warning verbatim — *"the game will run at 90/60 =
1.50x speed"* — and arms A and C correctly do not.

### 2.2 — AND ARM C IS ARM A
**`fps 60.0`, `speedgraph 60.0/s`, `g_GlobalTimer 60.0/s`.** The real clock did exactly what
it promises — a field became a unit of real time, and game speed is correct — **and it
delivered that by throwing the 90 Hz away.** The three headline numbers in C are
indistinguishable from the 60 Hz control. **Asking this port for a real clock and 90 fps
returns a 60 fps game and no error.**

### 2.3 — AN ODDITY, `[MEASURED]`, NOT TO BE BUILT ON
**C's 29 windows are 60.0 with ZERO variance. A's dip to 53 and sit at 59.** The spin is a
harder pacer than `sys_sleep()`, which truncates to whole milliseconds (`port_support.c:47`).
**Recorded because it is real and because it is a trap**: C looks *steadier* than the control
on the one number a casual reader would check.

## §3 — THE MECHANISM. READ FROM SOURCE **BEFORE** THE RUN, WHICH IS WHY THE RUN COULD BE ONE LAUNCH.

`frametiming.c:322-343`:

```c
const u32 bias     = gePortRealClockOn() ? 0u : 387937u;
const s32 free_run = gePortRealClockOn() && gePortFrameCapOff();
do { nextFrameTime = ((osGetCount() - copy_of_osgetcount_value_1) + bias) / 775875;
     if (free_run) { copy1 += nextFrameTime * 775875u; break; }
} while (nextFrameTime < frameDelay);
```

**`gePortFrameCapOff()` (`port_os.c:221`) is true ONLY for `GETV_FPS=0` or `off`.** At
`GETV_FPS=90` it returns 0, so `free_run` is 0 and the remainder-carrying break is not taken.
With the real clock `bias` is 0, so the loop blocks until a whole real field —
**`775875 / 46,875,000 = 16.552 ms`** — has passed since the previous frame's reference.
**That is a 60.4 Hz ceiling, and the SDL pacer's 11.1 ms target never binds underneath it.**

> ### THE PRECONDITION WAS IN THE SOURCE ALL ALONG AND HAD NEVER BEEN READ AS ONE.
> `port_os.c:209`: *"With `GETV_REALCLOCK=1` **and `GETV_FPS=0`**, `waitForNextFrame()`
> becomes a genuine busy-spin on a core."* **The `GETV_FPS=0` is load-bearing.** Every doc that
> has cited `GETV_REALCLOCK` — `259` §3, `260` §4, `RUN-SHEET-260`, `HANDOVER` — quoted the
> knob without its run condition. **Same shape as `273` §8's `GETV_GPUTIME` needing
> `GETV_FPS=0`: the second instrument in two sessions whose working configuration is
> "uncapped", and in both cases the cap was silently answering instead.**

**And uncapped is not available to us.** `273` §7.3 `[MEASURED]` `GETV_FPS=0` locks up on
Cradle within seconds, 3 of 3 — and an uncapped present is not a VR frame path in any case.
**The real clock's only working configuration is one this project cannot ship.**

### 3.1 — THE SECOND COST: IT BLINDS `P5`. `[INFERRED]`, AND CHEAP TO SETTLE.
`waitForNextFrame()` is called from `boss.c:535`, **outside** `port_render.c`'s `GETV_BUDGET`
bracket (`gfx_start_frame`..`gfx_end_frame`). The 5.5 ms spin is therefore neither work nor
the pacer's measured sleep: the period grows by time no instrument sees, and `ge_pace_sleeps`
should fall to 0 — which `gfx_sdl2.c:130` names as the condition under which the work/wait
split says nothing. **This is `00-STATE` §6's bracket trap from the other side: not an
instrument containing the pacer, but a wait the instrument cannot see.**
**`[INFERRED]` — no arm set `GETV_BUDGET`. Adding `GETV_BUDGET=120` to arm C settles it for
the cost of one launch, and it is not worth a launch of its own.**

## §4 — THE DECISION

> ## **STAGE 4's TIMEBASE IS THE SYNTHETIC COUNTER, MADE RATE-AWARE. `GETV_REALCLOCK` IS
> ## REJECTED FOR THE PRESENT PATH AND STAYS REACHABLE AS THE KNOB IT IS (RULE `2`).**

Fields per rendered frame become **`60.0f / actualHz`** — `P1` verbatim, never a literal —
computed from the rate the program was **told**, not the rate it **achieved**:

- **Determinism is preserved**, and this is the whole of the `P1`/`P9` answer. `gfx_sdl2.c:89-93`
  forbids letting `speedgraphframes` *float under load*. **A term derived from the configured
  rate does not float**: every run at 90 Hz produces the identical field sequence whatever the
  machine is doing, so `271`/`272`/`273`'s figures stay comparable and gameplay frames stay
  reproducible. The warning is honoured, not overridden.
- **`258` §3.2's pin is where it must be — at the moment the timestep is written**, not
  retrofitted: `actualHz` **queried from the runtime by default, overridable by one term**
  (`GETV_SIMHZ=<n>` proposed; the name is the owner's). That is also §3.2's multiplayer
  clause — peers pinned to a common rate need the numerator *supplied*.
- **The port has already made this exact choice once, and kept determinism doing it.**
  `ge_config.c:388-391`: `framerate=30` sets **`GETV_TICKFIELDS=2`** — 30 updates x 2 fields =
  60 fields/s, game time correct, counter still synthetic. **90 Hz is the same mechanism with a
  non-integer factor (`0.667`).** `GETV_TICKFIELDS` is an `s32` and cannot express it; that
  limitation, not the timebase, is what is actually in the way.

**THE TRADE, STATED:** a machine that misses the rate goes into slow motion rather than
catching up. **That is what the synthetic clock already does at 60**, so it is not a
regression — and it is the correct trade for a project whose measurements must be comparable
across runs.

## §5 — WHAT THIS DOES **NOT** SETTLE, AND WHY IT IS A SEPARATE PIECE OF WORK

The timebase is settled. **The SHAPE of the fractional delta is not, and it is MEDIUM work —
the diff against the matching decomp.** Its cost input has changed:

- **`[MEASURED]` 44 divide-by-`g_GlobalTimerDelta` sites in 5 files, not 8.** `259` §4 inherited
  `132` §3's recomp-era count. `bondview2.c` 3, `front.c` 3, `gun.c` 12, `gunfire.c` 24,
  `propobj.c` 2. **34 sit under a `g_ClockTimer > 0` guard; 10 do not** — `front.c:8941-8943`,
  `gunfire.c:5994-5996`, `gunfire.c:6311-6313`, `propobj.c:2393`. **First cut, 25-line window;
  a guard further up would not be seen. It must be read properly before the change, not after.**
- **`g_ClockTimer` is an ITERATION COUNT, not only a scale.** 164 refs, **22 of them
  `for (i = 0; i < g_ClockTimer; i++)`**, and `lv.c:1152` advances `g_GlobalTimer` by it.
  **Neither may become non-integer** or every frame-counted timeout in the game moves.
- **Carrying the remainder into an `s32` makes a tick run with delta 0** (`0,1,1,0,1,1` at
  90 Hz). Retail only reached delta 0 while **paused or controls-locked** (`lv.c:1136-1142`).
  **That those 34 guards exist is evidence the state is reachable; that 10 sites lack one is
  the risk.**

**THREE SHAPES ANSWER IT, AND ONE OF THEM IS A TRAP:**
1. **Tick every frame, delta alternates 0/1.** No skipped ticks, so `268` cannot return. Costs
   the delta-0 review above.
2. **A FRACTIONAL DIVIDER** — tick only when a whole field has accumulated, delta always 1.
   No delta-0 at all. **AND IT REINTRODUCES `268`**: one frame in three becomes a skipped
   tick, and skipped ticks are exactly what the portal scissor could not survive. **Do not
   take this one without re-reading `268`.**
3. **Integer `g_ClockTimer` beside a genuinely fractional `g_GlobalTimerDelta`.** Smooth, no
   delta-0, but the two deltas then disagree — loops run 0 or 1 times while the delta says
   0.667. Arguably the right split (the port's own framing: 13 files scale by the delta, 122
   are frame-counted), and arguably a second source of truth. **Unread.**

**`259` §4's residual stands and is now testable:** the real clock hands the sim `0,1,1,...`
— correct on average, uneven per frame — which is **judder-shaped, not speed-shaped**, and is
what `96`'s *"it just feels not ninety hertz"* would look like. `[INFERRED]`, `182`.
**Shape 1 has the same residual by construction.** Arm C is the run that could have shown it
and did not, because arm C never reached 90.

## §6 — RETRACTION

| claimed | truth | killed by |
|---|---|---|
| *"`260` §4 / `RUN-SHEET-260`: `GETV_REALCLOCK=1` -> expect `speedgraph ~60/s` **while `fps` reads 90**"* | **FALSE — mine, and written into a run sheet as a prediction.** `[MEASURED]` `fps` reads **60.0** across 29 windows with the 90 fps cap requested and granted in the banner. The `speedgraph ~60/s` half was right for the wrong reason: it is 60/s because the RENDER fell to 60, not because a field became real time under a 90 Hz present. | this doc, §2 |

## §7 — THE TRAP THIS EARNS

> **►►►► A KNOB'S RUN CONDITION IS PART OF THE KNOB. `GETV_REALCLOCK` AND `GETV_GPUTIME` BOTH
> ONLY WORK WITH `GETV_FPS=0`, AND BOTH WERE CITED FOR TWO SESSIONS WITHOUT IT. ◄◄◄◄**
> Neither prints a refusal; `GETV_REALCLOCK` under a cap **silently substitutes a 60 Hz run**
> and its own banner still reads `REAL host timebase`, which is true and useless.
> **`273` §2 gave `GETV_GPUTIME` a `CONTAMINATED` gate for exactly this. `GETV_REALCLOCK` is
> owed the same one and does not have it** — rule `17`: a knob that falls back instead of
> failing is a silent-staleness bug that gets a gate.

## §8 — WHAT THIS DOES TO `258`

- **STAGE 4's HIGH half is CLOSED.** The timebase is decided and the decision is `[MEASURED]`,
  not reasoned. **`00-STATE` §3 item 4's "settle the determinism question first, as its own
  piece of work, before touching `bondview2.c`" is discharged.**
- **What remains of STAGE 4 is MEDIUM**: pick a shape from §5, read the 10 unguarded divide
  sites, write the pin, diff against the matching decomp, and re-run this same three-arm sheet
  as the `239` gate — **with `GETV_BUDGET=120` added, per §3.1.**
- **`239`'s gate is MET FOR THIS DECISION**: two rates, both valid, both instrumented, and the
  fault quantified at the second rate. **It is not yet met for the fix**, which does not exist.
- **STAGE 5 and STAGE 6 are unaffected.** Nothing here touches the pose spine or the eye loop.

## §9 — NOT CLAIMED
- **No code was written. No build happened. `bondview2.c` was not edited.**
- **The 44 divide sites' guard status is a 25-line-window first cut**, not a read.
- **§3.1 (that `GETV_REALCLOCK` blinds `GETV_BUDGET`) is `[INFERRED]` from source.** No arm
  set `GETV_BUDGET`.
- **No CPU or GPU figure was taken or re-taken.** `273` owns both, and no arm here set
  `GETV_GPUTIME` — which would have been void anyway, all three arms being capped.
- **The residual quantisation (`259` §4) is still unobserved.** Nothing has yet run the
  simulation at a correct speed with a 90 Hz present, because nothing yet can.
- **`GETV_SIMHZ` is a proposed name for an unwritten term.** It is in no binary.
