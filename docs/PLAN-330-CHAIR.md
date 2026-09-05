# `PLAN-330-CHAIR` -- **`K-6` UNPARKED, THEN `K-3`. AND FIVE THINGS READ OFF THE SOURCE BEFORE ANYBODY RUNS ANYTHING**

**NOT GREEN-LIT. NOTHING IN THIS PLAN OR IN `RUN-SHEET-330` HAS BEEN RUN.** No game has been
launched, SteamVR has not been started, no product file has been edited, nothing has been staged.
`330` is a planning session and this document plus `RUN-SHEET-330` are the whole of its output.

---

## 0 -- **ONE TABLE**

| | |
|---|---|
| `1` | **`329` PUT `xrWaitFrame` IN `goldeneye.exe` AND NOBODY HAS RUN IT.** `K-7` (`19` `xr*` imports) and `K-8` (`0` on plain) are `objdump` facts. `GETV_XR_KILL=1` has still never executed |
| `2` | **THIS PLAN COVERS TWO RUNS AT THE CHAIR: `K-6` FIRST, THEN `K-3`.** `K-6` is cheap, it is owed since `328`, and it is `K-9`'s missing baseline |
| `3` | ►► **AND FIVE THINGS WERE READ OUT OF THE SOURCE BEFORE EITHER RUN WAS SCHEDULED (section `2`). TWO OF THEM CHANGE WHAT THE RUN SHEET HAS TO DO** ◄◄ |
| `4` | **NONE OF THE FIVE IS PATCHED HERE.** `301`: a diagnosis is not a licence to edit. **WRONG FILED FIXES STAY FIVE.** `H19` open, `U-28` reserved unfiled, `H24` unchanged |
| `5` | **FOUR FORKS GO TO THE OWNER (section `5`) AND NOTHING RUNS UNTIL THEY ARE ANSWERED** |

---

## 1 -- **WHERE THE STATE ACTUALLY IS, READ OFF THE DISK RATHER THAN OFF `00-STATE`**

`[MEASURED]` `330`, on the bridge, `getv\build-windows`:

| file | md5 | length |
|---|---|---|
| `goldeneye.exe` **(what would launch today)** | `037EDBD61D293C1CA0419418927715D7` | `18,075,663` |
| `goldeneye.exe.plain329` **(same bytes)** | `037EDBD61D293C1CA0419418927715D7` | `18,075,663` |
| `goldeneye.exe.vr329` **(the binary both runs need)** | `70BF2580239CD6B7C402C063D89B976F` | `18,101,808` |
| `openxr_loader.dll` beside them | `E00CB2890D93D5E33D675BCA3113B1B0` | `2,669,568` |

►► **SO NEITHER RUN CAN START WITHOUT A STAGING COPY.** `goldeneye.exe` holds the **plain** binary,
which is correct as `329` left it, and **every chair run in this project runs `goldeneye.exe`** --
Windows will not launch `goldeneye.exe.vr329` by that name. `RUN-SHEET-330` BLOCK `1` copies
`vr329` over `goldeneye.exe` and prints the md5, and **BLOCK `7` copies `plain329` back**. `328`
left the `-Vr` binary sitting as `goldeneye.exe` and `RUN-SHEET-328` BLOCK `4` had to put a plain
one back; that is recorded in `00-STATE` as a gate deviation and it is not repeated by accident. ◄◄

**`getv_xrkill_report.txt` DOES NOT EXIST ANYWHERE IN THE TREE.** `[MEASURED]` `330`: not in
`build-windows`, not in `repo\xr`. Every artifact in `repo\xr` is a standalone slice's. **The
first one that ever exists will be `K-3`'s**, which is what `RUN-SHEET-329` section `2` said, and
it is restated here because it also makes "the file is not there" a **readable result** rather
than an accident (section `2.2`).

---

## 2 -- ►► **FIVE THINGS READ OFF THE SOURCE BEFORE THE RUN. NONE OF THEM IS FIXED HERE** ◄◄

### 2.1 -- **THE FIRST `[getv][xrkill]` LINE THE RUN PRINTS CONTRADICTS THE BINARY IT IS PRINTED BY**

`[MEASURED]` `port_render.c:894-896`, unchanged by `329`:

    printf("[getv][xrkill] ARMED for frame %d. SESSION CREATE ONLY -- there is no "
           "xrWaitFrame in this build and this does not answer D-X3-KILL.\n", xrkill_at);

**THAT SENTENCE WAS TRUE OF `328` AND IS FALSE OF `329`.** `xrWaitFrame` is in the build --
`K-7` measured it in the import table -- and this run is precisely the one that answers
`D-X3-KILL`. **IT IS THE FIRST THING THE OWNER WILL SEE ON THE `K-3` RUN.**

**IT IS NOT PATCHED IN THIS SESSION.** `301` is the reason and the reason has a count on it. A
stale printed string is a `LOW` edit that costs a rebuild, a re-link, `K-7`/`K-8` re-taken and a
new binary md5 -- **and the run that is owed is the run that has been owed since `322`.** It is
named here, it is named again in `RUN-SHEET-330` BLOCK `5`, and **the writeup reads it as stale,
not as a statement about the build.**

### 2.2 -- ►► **THE THREE REFUSALS AT THE CALL SITE PRINT TO STDOUT AND TO NOTHING ELSE** ◄◄

FORK `C2` opens `getv_xrkill_report.txt` as the first statement of `geVrXrFrameKill()`, and
`RUN-SHEET-329` section `2` is exactly right about that function: **every reach of it writes the
file, refusal included.** **BUT THE GATE IN FRONT OF IT IS NOT IN IT.** `[MEASURED]`
`port_render.c:901-911`, three `printf` calls that never touch `ge_xk_say`:

    if (!geVrXrEnabled())              printf("[getv][xrkill] geVrXrEnabled()=0 ...")
    else if (!geVrXrInit())            printf("[getv][xrkill] geVrXrInit REFUSED: %s ...")
    else if (!geVrXrBeginSessionCurrent()) printf("[getv][xrkill] geVrXrBeginSessionCurrent REFUSED: %s ...")

**ON ANY OF THOSE THREE PATHS `geVrXrFrameKill()` IS NEVER CALLED, THE `fopen` NEVER HAPPENS, AND
NOTHING REACHES THE DISK AT ALL.** So "there is no `getv_xrkill_report.txt` after the run" is
**three different outcomes wearing one face**: the loop refused before it started; the game never
reached frame `120`; or the process died. Without a capture they cannot be told apart, and the
`5 s` `xrGetSystem` refusal that `326` spent a session diagnosing is one of them.

►► **THEREFORE THE STDOUT CAPTURE IS PART OF THE INSTRUMENT AND NOT A CONVENIENCE, AND THAT IS
FORK `F`.** ◄◄ **AND `K-6` HAS NO REPORT FILE AT ALL BY CONSTRUCTION** -- knobs unset means
`geVrXrFrameKill()` is never reached -- **so stdout is `K-6`'s ONLY evidence.** An unparked `K-6`
that is not captured is an unparked `K-6` that cannot be scored, which is how it came to be parked.

### 2.3 -- **AND THE BINARY IS NOT AVAILABLE TO BLAME FOR THAT.** `[MEASURED]` `330`, offline

`objdump -p goldeneye.exe.vr329` reads **`Subsystem 00000003 (Windows CUI)`**. `plain329` reads
the same. `build_windows.ps1:174-184` strips SDL's `-mwindows` **on purpose** and says why in the
script: with it, the process has no console and no stdout handle and
`.\goldeneye.exe *> run.log` **produces an empty file**; without it, subsystem `3`, and the
redirect works.

**SO `327`'s LOST `K-2` NUMBERS WERE A CAPTURE THAT NOBODY WROTE, NOT A CONSOLE THAT DOES NOT
EXIST.** `H24` is about `WS=1` blinding and is **not** touched by this; nothing new is filed.

### 2.4 -- **THE REPORT LANDS IN THE PROCESS'S CURRENT DIRECTORY, WHATEVER THE LINE SAYS**

`[MEASURED]` `gevr_xr.c:922`: `fopen("getv_xrkill_report.txt", "w")` -- a bare relative name, in
`GETV_DLGRAB`'s idiom (`port_render.c:705`), **which is the CWD of the process and not the
directory of the executable.** `gevr_xr.c:947` then prints *"report written to
getv_xrkill_report.txt beside the binary"*, **and that sentence is true only when the launch set
the location.** `RUN-SHEET-330` sets it, in both run blocks, and BLOCK `6` looks in the CWD it set
rather than trusting the line.

### 2.5 -- ►► **THE FREEZE IS NOT `3.3 s`. `A2` BOUGHT THE LOOP, AND THE LOOP WAS NEVER THE WHOLE FREEZE** ◄◄

`[ARITHMETIC]` `330`, from three constants in one file:

| segment | source | budget |
|---|---|---|
| `geVrXrSessionStart()` polling for `READY` | `GE_XR_KILL_POLL_TRIES 200` x `GE_XR_KILL_POLL_SLEEP 25` | **up to `5,000 ms`** |
| `geVrXrFrameLoop()` -- `A2` | `300` x measured `11.1111 ms` | **`3,333 ms`** |
| `geVrXrSessionStop()` pumping to `STOPPING` | the same `200` x `25` | **up to `5,000 ms`** |
| | | **worst case `13,333 ms`** |

**ALL THREE HAPPEN INSIDE ONE `gePortRenderDisplayList()` CALL, ON THE THREAD THAT OWNS A SHOWN,
FOREGROUND WINDOW, WITH NO `WM_` PUMP** (`A3` was refused, and correctly: the body is the shape).
`A2` reduced `600` frames to `300` to keep the measurement under the `~5 s` at which Windows
ghosts an unpumping top-level window -- **and it did that for the middle row only.**

**WHAT PRIOR ART SAYS ABOUT THE FIRST ROW:** `321` -- *"`READY` arrived before the first sleep"*.
The front budget is **expected** to cost approximately nothing. **WHAT ANYTHING SAYS ABOUT THE
THIRD ROW: NOTHING.** `xrRequestExitSession` -> `STOPPING` has never been measured in this
project; section `2` of `329` is the finding that `xrEndSession` has never even been observed to
succeed. **THE EXIT BUDGET IS AN UNKNOWN THAT CAN COST FIVE SECONDS.**

**PRE-REGISTERED, BEFORE THE RUN, SO IT CANNOT BE DECIDED AFTERWARDS:**

1. **A GHOSTED, WHITE OR "NOT RESPONDING" WINDOW DURING THE FREEZE IS A CONDITION OF THE RUN AND
   IS NOT `xrWaitFrame`'s BEHAVIOUR.** It goes in the sidecar as an observation. It does **not**
   enter the `K-3` verdict, and it does **not** license raising or lowering `GETV_XR_KILL_N`
   afterwards -- that would be re-tuning an arm after seeing it (`326` section `5`).
2. **THE REPORT IS FLUSHED LINE BY LINE.** `[MEASURED]` `gevr_xr.c`: `ge_xk_say()` calls
   `fflush(ge_xk_rep)` after **every** line. **A KILLED PROCESS STILL LEAVES EVERY LINE UP TO THE
   KILL ON DISK.** So if the window has to be killed, the partial file is evidence -- **and the
   kill is recorded in the sidecar, because a truncated report that nobody labelled would read as
   a crash.**
3. **DO NOT KILL BEFORE THE `xrEndSession ->` LINE IF IT CAN BE HELPED.** That line is the
   measurement `329` section `2` went looking for and this project has never taken.

---

## 3 -- **`K-6`, UNPARKED. WHAT IT SCORES, WHAT STAYS PARKED, AND WHY IT KEPT SLIPPING**

**THE RUN.** `goldeneye.exe` = `vr329`. **ALL `GETV_*` UNSET** (`Remove-Item Env:GETV_*`, which is
the standing first line of every block in this project). **SteamVR CLOSED.** Boot, reach gameplay,
play for long enough to pass frame `120` several times over, quit normally. **Stdout captured to a
file** (section `2.2`; fork `F`).

### 3.1 -- **SCORED**

| | `[PREDICTION]` `K-6` | falsified by |
|---|---|---|
| **`a`** | the `-Vr` binary **boots and reaches gameplay** with normal controls, indistinguishable from `K-2`'s baseline | a boot that does not reach gameplay, a crash, a loader error dialog |
| **`b`** | the captured stdout contains **`0`** lines matching `[getv][vr]` **and `0`** matching `[getv][xrkill]` | **any** such line with the knobs unset -- **then the gate is not a gate and `K-9` is falsified with it** |
| **`c`** | the run produces **no `getv_xrkill_report.txt`** anywhere | a report file appearing with the knobs unset |

**`K-6` IS `K-9`'s BASELINE AND TAKING IT CLOSES THE NAMED DEPENDENCY** carried since `328`
(`00-STATE`, `PLAN-329` section `5.1`). `K-9` -- *"with `GETV_XR_KILL` unset the `-Vr` binary boots
and plays with no `[getv][vr]` and no `[getv][xrkill]` output"* -- **is scored by `b` and `c`
together, on this run, and by nothing else.**

### 3.2 -- **PARKED, AND EACH ONE IS NAMED RATHER THAN QUIETLY DROPPED**

1. **THE PACING COMPARISON.** `GETV_BUDGET`, `ge_pace_wait_ms` and `ge_pace_sleeps` are **not**
   read on this run. `K-2` never captured them either (`00-STATE`, `327`), **so there is nothing
   to compare against, and manufacturing a baseline now would be a new arm inside a run that is
   supposed to be a control.** If the owner wants that comparison it is its own arm, its own
   sheet, and it is cheap now that section `2.3` says the capture works.
2. **SMOOTHNESS, FRAME RATE AND FEEL.** No instrument, and an impression is not a measurement
   (`182`). Not scored, not recorded as evidence, allowed in the sidecar `notes` as an
   observation.
3. **ANYTHING ABOUT `xrWaitFrame`.** The knobs are unset; nothing XR runs. `K-6` says the gate
   holds, and it says nothing whatever about the loop.

### 3.3 -- **WHY IT WAS PARKED TWICE, AND IT IS NOT A DISCIPLINE PROBLEM**

`K-6`'s whole content is **the absence of output**, and until section `2.3` was read nobody had
established that this binary can produce a readable stdout at the chair at all. **AN ABSENCE THAT
CANNOT BE CAPTURED IS NOT AN OBSERVATION.** With the capture, `K-6` is a five-minute run whose
result is a `grep` count, and it is worth taking before `K-3` for one more reason: **it exercises
the staging, the launch line, the capture and the harvest on a run where nothing can freeze the
window.** If the capture is broken, it is discovered on the cheap run.

---

## 4 -- **`K-3`. THE READING IS ASYMMETRIC AND IT WAS WRITTEN BEFORE THE FIRST NUMBER**

### 4.1 -- **THE CONDITIONS ARE PART OF THE PREDICTION**

`GETV_VR=1` **and** `GETV_XR_KILL=1` **and SteamVR up with the HMD awake.** `[MEASURED]`
`gevr_xr.c:234`: without a runtime and a system, `xrGetSystem` returns `-35` and that is a
**REFUSAL, NOT A MEASUREMENT**. `[MEASURED]` `port_render.c:891`: the knob is read as
`*e == '1'` exactly -- **`GETV_XR_KILL=true` DOES NOTHING.** `[MEASURED]` `port_render.c:887`:
the block fires **once**, on the first rendered frame at or past `GETV_XR_KILL_AT`, default
**`120`** (fork `E`).

### 4.2 -- **THE VERDICT IS THE INSTRUMENT'S OWN LINE, AND ALL THREE ARE ALREADY IN THE BINARY**

| the line it prints | what it means | what it does NOT mean |
|---|---|---|
| **`K-3 LANDS.`** | mean interval inside the runtime's own period band. **`xrWaitFrame` BLOCKS IN THE GAME PROCESS. `D-X3` SURVIVES -- IT IS NOT BUILT** | that the interlock may be armed. It may not (`K-3d`, and section `6`) |
| **`K-3 NEITHER -- AND THIS IS NOT A KILL`** | `xrWaitFrame` returned without blocking **in an arm with no swapchain** (`B1`). **`B2` IS MANDATED BEFORE `D-X3` IS DECLARED DEAD** | **a kill.** `PLAN-322-X3` section `6` item `1` was written about an arm that had two swapchains and does not transfer. **Do not raise the frame count, do not add a submit, do not report it as a kill** |
| **`K-3 NEITHER.`** (blocks, wrong period) | the gap between the block and the advertised period is the finding | a kill, a landing, or a rounding error |

►► **AND ONE THING IS PRE-REGISTERED HERE BECAUSE IT WOULD OTHERWISE BE DECIDED AFTER THE
NUMBERS.** `[MEASURED]` `gevr_xr.c:818`: the `LANDS` test in the binary is
`mean >= 0.90 * pmin && mean <= 1.10 * pmax` -- **a `10%` band**, inherited **byte-identical** from
`ge_s3_score` (`gevr_xr_slice3.c:272`), which is exactly what `A2`/"the body is the shape"
required. **`PLAN-329` SECTION `5.2`'s PROSE SAYS `0.500%`.** Both readings are taken: **the
instrument's own verdict line is the score**, and **the `0.500%` arithmetic is computed beside it
in the writeup from the printed `mean`, `pmin` and `pmax`.** A run that lands the `10%` band and
misses `0.500%` is **`K-3 LANDS (WIDE BAND)`** and is written that way -- neither number is
adjusted, and the instrument is not edited to match a plan (`301`). Prior art says the gap is
unlikely to bite: `[ARITHMETIC]` `325`'s mean `11.1201 ms` against period `11.1111 ms` is
**`0.081%`**, inside both. ◄◄

### 4.3 -- **THE SECONDARY READINGS, WHICH ARE PRINTED WHETHER OR NOT ANYBODY WANTS THEM**

- **`K-3b`** -- `predictedDisplayPeriod` spread across the run. Under `1%` it says a one-shot read
  is safe **on this run**; over `1%` it is a finding about `gePortSimHzResolve()`'s one-shot cache.
- **`K-3c`** -- `shouldRender` true count. **`325` measured a DESK run `VISIBLE` for `88` frames
  and `shouldRender` true on exactly `58` scored frames, frame for frame**, so a mixed count is
  expected shape, not a surprise. **`VISIBLE` NO LONGER IMPLIES WORN. THE SIDECAR LABELS THE RUN.**
- **`K-3d`** -- the runtime's rate, followed by the standing line in the instrument's own voice.
- **AND THE `xrEndSession ->` LINE**, which is `329` section `2`'s whole point and is the first
  time this project reads that result by name.

### 4.4 -- **WHERE THE FIRST REAL `getv_xrkill_report.txt` IS EXPECTED, NAMED**

**AT THE CHAIR** -- the main PC is the only machine in this project that runs the game; the bridge
takes no game runs. **THE FILE IS WRITTEN INTO THE PROCESS CWD, WHICH `RUN-SHEET-330` SETS TO
`F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows`** (section `2.4`), beside
`goldeneye.exe` and `openxr_loader.dll`. **HEADSET CONDITION: `DESK` under the proposed fork `D1`**
-- awake, on the desk, not worn -- **and the sidecar, not the session state, is what labels it.**

BLOCK `6` harvests it to `repo\xr\getv_xrkill_report_330_DESK.txt` (or `..._WORN.txt` under `D2`)
so that the working copy in `build-windows` can be overwritten by a later run without losing this
one -- **`324` had to keep two slice-4 reports apart by name for exactly this reason.**

### 4.5 -- **WHAT A MISSING REPORT FILE MEANS, AND IT IS THREE THINGS (section `2.2`)**

| stdout capture says | reading |
|---|---|
| an `ARMED for frame 120` line and then one of the three `REFUSED` / `geVrXrEnabled()=0` lines | **the gate refused before the loop.** The refusal text names which. **A FINDING, NOT A FAILED RUN** |
| an `ARMED` line and nothing after it | **the game never reached frame `120` while rendering**, or the process died. Sidecar says which |
| no `[getv][xrkill]` line at all | **the knob did not take** -- `GETV_XR_KILL` unset, not `1`, or the wrong binary is staged. Check the md5 BLOCK `1` printed |

---

## 5 -- **THE FORKS. FOUR, AND NOTHING RUNS UNTIL THEY ARE ANSWERED**

| fork | options | proposed, and what it costs |
|---|---|---|
| **`D` -- `K-3`'s HEADSET CONDITION** | **`D1` DESK** (awake, on the desk, not worn) / `D2` WORN | ►► **`D1`** ◄◄ The primary reading -- does `xrWaitFrame` block, and to what period -- was **identical across all four prior runs**, `322` desk, `324a` desk, `324b` worn and `325` desk: `11.1111 ms` min AND max, spread `0.0000%`, four times. **DESK COSTS THE PRIMARY READING NOTHING.** What it costs is `K-3c`: desk reached `VISIBLE` once in three tries (`325`), so `shouldRender` may be `0`, mixed, or all -- **and `K-3c`'s text already handles all three.** `D2` buys a likelier `VISIBLE` and costs the owner wearing a headset through a freeze of up to `13 s` (section `2.5`) |
| **`E` -- WHERE THE LOOP FIRES** | **`E1` default `120`** / `E2` a raised `GETV_XR_KILL_AT` to land inside gameplay | ►► **`E1`** ◄◄ **No knob is touched, which is the point.** Frame `120` is roughly `2 s` into rendering, wherever the game is then; **the sidecar records what was on screen.** `E2` is a parameter change to a pre-registered arm and it buys nothing the question needs -- `xrWaitFrame` does not know what the game is drawing. **If the owner wants an in-gameplay firing it is a second run, not an edit to this one** |
| **`F` -- STDOUT CAPTURE** | `F1` none (as `327`) / **`F2` `*>` to a named log, both runs** | ►► **`F2`, AND SECTION `2.2` MAKES IT LOAD-BEARING RATHER THAN NICE** ◄◄ `K-6` has **no** report file by construction and stdout is its only evidence; `K-3`'s three refusal paths write **nothing** to disk. `[MEASURED]` subsystem `3` (section `2.3`) says the redirect works. Cost: the console output is not visible live during the run -- **the report file is, and BLOCK `6` prints the verdict** |
| **`G` -- ORDER AND THE ABORT RULE** | **`G1` `K-6`, report, then `K-3` in the same sitting only if `K-6` landed** / `G2` both back to back / `G3` `K-6` only, `K-3` next session | ►► **`G1`** ◄◄ `K-6` is minutes and it validates staging, launch, capture and harvest on a run that cannot freeze the window. **If `K-6` is falsified -- any `[getv]` line with the knobs unset -- `K-3` DOES NOT RUN**, because the gate would be the finding and a loop run on an ungated binary would not be readable |

**`K-3` IS NOT ON A FORK LIST AS A YES/NO.** It is the run this project has owed since `322`, it
needs the sidecar and the conditions above, and **the green-light for it is the owner's, on this
plan, before `RUN-SHEET-330` is opened.**

---

## 6 -- **THE STANDING LINE, AND `K-3` IS WHERE IT IS MOST TEMPTING TO CROSS**

`GETV_XR_KILL` **NEVER** reads `geVrXrPacingOwned()`. It **NEVER** touches
`sync_framerate_with_timer()`. **NO HANDOVER -- NOT IN THIS SESSION AND NOT IN THE ONE THAT READS
THE RESULT.**

**AND A LANDED `K-3` IS EXACTLY THE MOMENT THE LINE GETS CROSSED BY ACCIDENT.** A `K-3 LANDS`
verdict puts a live `xrWaitFrame` and a measured `predictedDisplayPeriod` in the same run --
`geVrXrPaceArm()`'s two inputs -- and the next obvious move looks like arming it. **IT IS NOT THE
NEXT MOVE.** Arming is `I-3`/`D-X3` proper: its own plan, its own falsifier, its own green-light,
gated on `K-3` having an answer **and on that answer being written down first.** `K-3d` says so in
the instrument's own output so it cannot be forgotten between the run and the writeup.

---

## 7 -- **WHAT THIS PLAN WILL NOT DO, WHATEVER EITHER RUN SAYS**

**NO PRODUCT EDIT OF ANY KIND** -- and that includes the stale `ARMED` string (`2.1`), the `10%`
band (`4.2`), and the CWD-relative `fopen` (`2.4`). **A DIAGNOSIS IS NOT A LICENCE (`301`; wrong
filed fixes stay FIVE).** No `B2`, and **`B2` is not invented in this session even if `K-3` reads
`NEITHER`** -- the instrument prints the mandate and the mandate is a next session's plan.
No `H19`. No `U-28` filed. No `SHAPE A`/`B`, no `GX-0`, no desk-`VISIBLE` cause, no graphics, no
extras. No re-do of `K-7`/`K-8`. No handover, no `geVrXrPaceArm`, no `geVrXrPacingOwned`, no
`sync_framerate`. No `gfx_sdl2.c`, no `getv/patches`, no `build_windows.ps1`. No rebuild --
**a rebuild would change the binary the run sheet names by md5.**
**Nothing staged, committed, branched, merged, tagged or pushed by this plan.**

---

## 8 -- **THE STOPPING LINE, AND IT IS HERE**

**THE OWNER ANSWERS FOUR FORKS AND GREEN-LIGHTS `K-6` AND `K-3`. NOTHING IS LAUNCHED UNTIL THEN.**

1. **FORK `D`** -- `K-3` desk or worn. Proposed **`D1` DESK**.
2. **FORK `E`** -- fire at the default frame `120`, or raise `GETV_XR_KILL_AT`. Proposed **`E1`**.
3. **FORK `F`** -- stdout capture on both runs. Proposed **`F2`**, and section `2.2` is why.
4. **FORK `G`** -- `K-6` first with the abort rule, then `K-3`. Proposed **`G1`**.

**AND ONE THING THAT IS NOT A FORK, STATED SO IT IS NOT A SURPRISE AT THE CHAIR:** the `K-3` run
freezes the game window for **`3.3 s` at best and up to `13.3 s`** (section `2.5`), the window may
ghost, and **the report file is complete line by line as it goes.**

`169` NEXT ID = `U-28`. NEXT INSTRUMENT HOLE = `H25`.
