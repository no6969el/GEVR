# `PLAN-329-FRAMELOOP` -- **THE FRAME LOOP `D-X3-KILL` HAS NEVER HAD, ITS FALSIFIER, AND THE THREE THINGS THE DESIGN HAD TO FIND BEFORE IT COULD PROPOSE ONE**

**`329` IS DESIGN ONLY.** No product edit, no `gevr_xr.c`, no `port_render.c`, no build script,
nothing staged. `00-STATE` section `7c`: plan first, falsifier named, then stop.
**`K-6` (chair, knobs unset) IS PARKED AND IS NOT THIS `HIGH`. `K-3` -- THE TIMED IN-GAME RUN --
IS NOT THIS SESSION AND IS NOT GREEN-LIT BY ANYTHING BELOW.**

---

## 0 -- ONE TABLE (`[MEASURED]` off the disk this session, source and one export table, nothing built)

| | |
|---|---|
| `1` | **THE GATES MATCH THE PROMPT.** `goldeneye-native` `HEAD` **`fdf7c7d`**; `GoldenEyeVR` `HEAD` **`73b8a97`**; `-- repo/docs` **`57`** entries, **all ` M`, `0` staged**; `-- getv/port/src`, `-- getv/port/include`, `-- getv/build_windows.ps1` **all clean**; `00-STATE` currency **`328`** |
| `2` | **THE CALL SITE IS WHERE `328` LEFT IT.** `port_render.c:886-921`, before the `GETV_BUDGET` bracket, `static int xrkill = -1, xrkill_at = 120, xrkill_fired = 0`, and the success branch runs `geVrXrEnabled` -> `geVrXrInit` -> `geVrXrBeginSessionCurrent` -> print -> `geVrXrEndSession` -> `geVrXrShutdown`. **IT DOES NOT NEED REDESIGNING. IT NEEDS ONE LINE** |
| `3` | **THE LIVE BRANCH STILL STOPS AT `xrCreateSession`** (`gevr_xr.c:390`), and `:404-405` says so in its own output. `xrBeginSession`, `xrWaitFrame`, `xrBeginFrame`, `xrEndFrame`, `xrPollEvent`, `xrEndSession` and `xrRequestExitSession` appear in this tree **only** in `repo\xr\gevr_xr_slice2.c` / `slice3.c` (standalone, untracked by the game build) and in printed strings |
| `4` | **`QueryPerformanceCounter` COSTS NO NEW HEADER.** `gevr_xr.c:34` already includes `<windows.h>` inside `GEVR_XR_LIVE`. `ge_s3_now_ms()` transplants as written |
| `5` | ►► **EVERY ONE OF THE SEVEN IS A STATIC EXPORT OF THE VENDORED LOADER.** `[MEASURED]` `objdump -p repo\xr\openxr_loader.dll`: `xrBeginFrame [3]`, `xrBeginSession [4]`, `xrEndFrame [18]`, `xrEndSession [19]`, `xrPollEvent [45]`, `xrRequestExitSession [47]`, `xrWaitFrame [54]`. **A DIRECT CALL TO ANY OF THEM BECOMES AN IMPORT ENTRY, SO SECTION `5`'s FALSIFIER IS MECHANICALLY SOUND AND NOT A HOPE** ◄◄ |
| `6` | **AND SO ARE THE FOUR SWAPCHAIN CALLS, IF SECTION `4`'s FORK GOES THAT WAY:** `xrCreateSwapchain [11]`, `xrDestroySwapchain [17]`, `xrEnumerateSwapchainFormats [25]`, `xrEnumerateSwapchainImages [26]` |
| `7` | **THE ARM TO COPY IS `ge_s3_armA`** (`repo\xr\gevr_xr_slice3.c:134-210`): `GE_S3_FRAMES 600`, `GE_S3_WARMUP 30`, a NON-SLEEPING `ge_s3_pump`, `xrWaitFrame` -> `t_ret = QPC` -> `xrBeginFrame` (counting `XR_FRAME_DISCARDED` as the success code it is) -> `xrEndFrame` with `layerCount 0` and `layers NULL` |
| `8` | **THE REPORT TO COPY IS `ge_s3_score`** (`:215+`): mean / min / max / p50 / p95 / p99 of the return-to-return interval, `predictedDisplayPeriod` min-median-max and spread, `shouldRender` count, discarded count |
| `9` | **AND `port_render.c` ALREADY WRITES FILES FROM THIS THREAD.** `GETV_DLGRAB` `fopen`s a bare relative name (`:700-705`), so a report file beside the binary has precedent in this file and needs no new path machinery |

---

## 1 -- **WHAT IS BEING ASKED FOR, IN ONE SENTENCE, AND WHAT IT IS NOT**

**`D-X3-KILL`:** does `xrWaitFrame` BLOCK when it is called from inside `goldeneye.exe`, where the
GL context, the SDL pump and the swap belong to someone else? (`PLAN-326` section `1`.)

Four runs -- `322`, `324` desk, `324` worn, `325` -- say it blocks at `11.1111 ms` / `90.0001 Hz`
with a spread of `0.0000%`. **ALL FOUR WERE TAKEN IN A STANDALONE SLICE WITH ITS OWN NEVER-SHOWN
WINDOW AND ITS OWN EVENT PUMP**, and `324` is this project's own proof that environment decides
outcomes on a byte-identical binary.

**THIS PLAN DESIGNS THE CODE THAT MAKES THAT QUESTION ASKABLE IN THE GAME PROCESS. IT DOES NOT ASK
IT.** The asking is `K-3`, it is a run at the chair with a conditions sidecar, and it has its own
green-light (section `6`).

---

## 2 -- ►► **THREE BLOCKERS THE DESIGN HAD TO FIND FIRST, AND THE FIRST ONE IS A HOLE IN WHAT THIS PROJECT ALREADY BELIEVES** ◄◄

### 2.1 -- **`xrEndSession` HAS NEVER BEEN MEASURED TO SUCCEED IN THIS PROJECT**

`[MEASURED]` `gevr_xr_slice2.c:351-360`, `ge_s2_teardown()`:

    if (ge_s2_begun) {
        xrEndSession(ge_xr_session);
        ge_s2_begun = 0;
        printf("[getv][vr] session ended.\n");
    }

**THE RESULT IS DISCARDED AND THE LINE PRINTS ANYWAY.** `session ended.` at the foot of
`gevr_xr_slice5_report.txt` is a `printf`, **not a measurement**, and every slice-2/3/4/5 report
in `repo\xr\` carries it on the same terms. The spec makes `xrEndSession` legal only from
`XR_SESSION_STATE_STOPPING`; a session still `RUNNING`, `SYNCHRONIZED` or `VISIBLE` returns
`XR_ERROR_SESSION_NOT_STOPPING` and **that is exactly what these runs would have looked like.**

**AND `gevr_xr.c`'s OWN TEARDOWN IS NOT EVEN THAT.** `geVrXrEndSession()` (`:433`) calls
`xrDestroySession` and nothing else, because slice 1 never began a session and had nothing to end.
**THE MOMENT `xrBeginSession` LANDS IN THIS FILE, THAT FUNCTION IS WRONG** -- it would abandon a
running session to the runtime, in a process that then keeps playing GoldenEye for another hour.

**THIS IS NOT FILED AND IT IS NOT A HOLE** (`301`; the wrong-fix count stays **FIVE**). It is a
gap in the standalone slices' evidence, found by reading them, and the design below closes it by
**reading and printing the result by name** rather than by assuming either answer.

### 2.2 -- **THE LOOP BLOCKS THE THREAD THAT OWNS THE GAME'S WINDOW, AND THE STANDALONE ARM'S WINDOW WAS NEVER SHOWN**

`ge_s3_armA` at `600` frames and `11.1111 ms` is **`6.7 SECONDS`** inside one call to
`gePortRenderDisplayList()`. In the smoke that costs nothing: the window is created
`WS_OVERLAPPEDWINDOW` and **never `ShowWindow`n**, and the loop pumps `xrPollEvent` only -- no
`WM_` messages, on a window nobody can see.

**IN THE GAME THAT WINDOW IS SHOWN, IS FOREGROUND, AND ITS MESSAGE PUMP IS THE THREAD THE LOOP IS
STANDING ON.** Windows ghosts a top-level window that has not pumped for about `5 s` and DWM
substitutes a "(Not Responding)" copy; a ghosted, possibly de-foregrounded window is a **CHANGE OF
CONDITIONS INSIDE THE MEASUREMENT WINDOW**, and `325` already measured this runtime moving
`VISIBLE -> SYNCHRONIZED` mid-loop on a desk run. **A CONDITION THAT CHANGES AT SECOND `5` OF A
`6.7 s` MEASUREMENT WOULD BE SCORED AS `xrWaitFrame`'s BEHAVIOUR.**

**SO THE LOOP LENGTH IS A NUMBER THAT MUST BE CHOSEN BEFORE THE RUN, NOT AFTER IT.** Section `4`
forks it.

**AND ONE CONSEQUENCE IS NAMED HERE SO IT CANNOT BE MISREAD LATER:** the game's own pacer sees a
multi-second frame. Whatever `sync_framerate_with_timer()` and the sim do on the frame *after* the
loop -- a catch-up burst, a spike in `ge_pace_wait_ms` -- **IS NOT A FINDING ABOUT `xrWaitFrame`**
and is not to be reported as one. The loop sits before the `GETV_BUDGET` bracket, so no budget
line is charged, and the next frame's line is the one to distrust.

### 2.3 -- **THE FOUR MEASUREMENTS ALL HAD TWO SWAPCHAINS. THE PROPOSED LOOP HAS NONE**

`[MEASURED]` `gevr_xr_slice3.c:29-32`: arm A creates no images, acquires nothing, submits nothing
-- **but slice 2's `xrCreateSwapchain` ran first, and the swapchains existed for the whole of every
run.** Slice 3's own words are "created and destroyed and never touched in between".

**"NOT TOUCHED" IS NOT "NOT PRESENT."** Nothing in this project has measured whether this runtime
offers a blocking `xrWaitFrame`, or `shouldRender`, or `VISIBLE` at all, to a session that has
never created one. That is the one axis on which the cheap in-game arm would differ from all four
prior runs, and it decides how a NON-blocking result may be read (section `5.2`).

---

## 3 -- **WHAT IS PROPOSED: FOUR ENTRY POINTS IN `gevr_xr.*` AND ONE LINE IN `port_render.c`**

**THE SPLIT IS `328`'s, RESTATED:** `port_render.c` gains **ONE CALL**, `gevr_xr.c` owns every
`xr*` call, every handle, every `<windows.h>` reference and the whole report. The knob shape is
`gevr_xr.c`'s existing `getenv` idiom (`geVrXrEnabled`, `:93-105`).

| new entry point | what it does | new `xr*` calls |
|---|---|---|
| `int geVrXrSessionStart(void)` | bounded `xrPollEvent` pump to `XR_SESSION_STATE_READY` (slice 2's `GE_S2_POLL_TRIES 200` x `GE_S2_POLL_SLEEP 25` = `5 s`), then `xrBeginSession(PRIMARY_STEREO)`. Refuses by name on budget exhaustion, on `LOSS_PENDING`/`EXITING`, and on a failed begin | `xrPollEvent`, `xrBeginSession` |
| `int geVrXrFrameLoop(int frames, int warmup)` | **`ge_s3_armA` AND `ge_s3_score`, TRANSPLANTED, PER-ITERATION BODY UNCHANGED**: non-sleeping pump, `xrWaitFrame` -> QPC -> `xrBeginFrame` (`XR_FRAME_DISCARDED` counted, never routed around) -> `xrEndFrame(layerCount 0, layers NULL)`. Prints the same distribution | `xrWaitFrame`, `xrBeginFrame`, `xrEndFrame` |
| `void geVrXrSessionStop(void)` | `xrRequestExitSession`, pump until `STOPPING` under the same bounded budget, **then `xrEndSession` WITH ITS RESULT READ AND PRINTED BY NAME** (section `2.1`), then fall through to the existing destroy | `xrRequestExitSession`, `xrEndSession` |
| `int geVrXrFrameKill(void)` | the one call `port_render.c` makes: `SessionStart` -> `FrameLoop(N, W)` -> `SessionStop`, each refusal printed, `N`/`W` from `GETV_XR_KILL_N` / `GETV_XR_KILL_WARMUP` with the section `4` defaults | none of its own |

**AND `geVrXrEndSession()` IS CORRECTED RATHER THAN LEFT TO BE WRONG** (section `2.1`): it calls
`geVrXrSessionStop()` first when a session was begun, then destroys. **`328`'s BLOCK IS
BEHAVIOURALLY UNCHANGED BY THAT** -- it never begins a session, so the new branch is not taken.

**THE `port_render.c` EDIT, IN FULL:** one call to `geVrXrFrameKill()` inside the existing
`else` branch of the `328` block, after the `SESSION LIVE IN THE GAME PROCESS` line and before the
existing `geVrXrEndSession()`. **NO NEW KNOB IN THAT FILE, NO NEW INCLUDE, NO MOVE OF THE BLOCK,
AND IT STAYS BEFORE THE `GETV_BUDGET` BRACKET.**

**THE STATIC COST, STATED RATHER THAN GLOSSED:** three arrays of `GE_XR_KILL_MAX_FRAMES` (`600`)
-- two `double`, one `int` -- is **`12,000` bytes of BSS in both builds**, because they are sized
at compile time. If that is not wanted in the plain binary they go inside `GEVR_XR_LIVE`; the
inert half then needs no state at all. **THAT IS A ONE-LINE CHOICE AND IT IS THE OWNER'S.**

---

## 4 -- **THE FORKS. THREE, AND EACH ONE CHANGES WHAT A RESULT MAY BE READ TO MEAN**

### FORK `A` -- **THE LOOP LENGTH** (section `2.2`)

| | `N` / warm-up | wall clock at `11.1111 ms` | window ghosting | scored frames |
|---|---|---|---|---|
| `A1` | `600` / `30` -- arm A's exact numbers | **`6.7 s`** | **CROSSES THE `~5 s` THRESHOLD** | `570` |
| ►► `A2` ◄◄ | **`300` / `30`** | **`3.3 s`** | under it | `270` |
| `A3` | `600` / `30` **plus `SDL_PumpEvents()` in the loop** | `6.7 s` | avoided | `570` |

**PROPOSED: `A2`.** `A3` is refused on the plan's own rule: `PLAN-326` section `5` says
*"`ge_s3_armA`'s shape, unchanged, because a re-tuned arm is not a comparison"*, and **a call added
inside the loop body is a change of shape.** `A1` is arm A's shape *and* arm A's sample count, and
it buys `300` extra frames of a distribution that has read `0.0000%` spread four times running at
the price of taking the measurement across a condition change. **LENGTH IS A PARAMETER; THE BODY
IS THE SHAPE. `A2` KEEPS THE SHAPE AND SPENDS THE PARAMETER** -- and it says so in the report, so
the deviation is on the page rather than in someone's memory.

### FORK `B` -- **SWAPCHAINS** (section `2.3`)

| | shape | new `xr*` calls | comparable to `322`/`324`/`325` |
|---|---|---|---|
| ►► `B1` ◄◄ | **NO SWAPCHAIN.** `xrBeginSession` then the loop | `7` | **on every axis but this one** |
| `B2` | slice 2's `X2-1`/`X2-2` transplanted too: format enumeration, two swapchains, image enumeration | `11`, plus a GL format choice in the game build | yes |

**PROPOSED: `B1`, WITH ITS ASYMMETRY PRE-REGISTERED AND NOT PAPERED OVER.** A **BLOCKING** result
under `B1` is decisive and costs nothing more: `xrWaitFrame` blocks in the game process, `D-X3`
survives, and the swapchain question never has to be paid for. A **NON-BLOCKING** result under
`B1` is **NOT** decisive -- it is either `D-X3` dead or the swapchain being load-bearing, and
those are not separable by that run. **SO A NON-BLOCKING `B1` SCORES `K-3 NEITHER` AND MANDATES
`B2` BEFORE `D-X3` IS DECLARED DEAD** (section `5.2`). `PLAN-322-X3` section `6` item `1` --
*"a non-blocking `xrWaitFrame` kills `D-X3` outright"* -- was written about an arm that had
swapchains, and it does not transfer to one that does not. **WRITING THAT DOWN NOW IS THE WHOLE
REASON THE CHEAP ARM IS SAFE TO PROPOSE.**

### FORK `C` -- **WHERE THE NUMBERS LAND** (section `0` item `9`)

`[MEASURED]` `327`: there was **no visible console at the chair**, and `GETV_BUDGET`,
`ge_pace_wait_ms` and `ge_pace_sleeps` were lost to it for `K-2`. **THE ENTIRE OUTPUT OF THIS
INSTRUMENT IS `printf`.**

| | |
|---|---|
| `C1` | stdout only, and the run sheet redirects. **One forgotten redirect and a `3.3 s` freeze produces nothing** |
| ►► `C2` ◄◄ | **stdout AND a report file**, `getv_xrkill_report.txt`, `fopen`ed beside the binary in `GETV_DLGRAB`'s idiom (`port_render.c:705`) -- written from `gevr_xr.c`, not from `port_render.c` |

**PROPOSED: `C2`.** The measurement survives the chair.

---

## 5 -- **THE FALSIFIERS. THE LINK FACT IS THIS DESIGN'S; THE TIMING IS NOT**

### 5.1 -- **WHAT AN IMPLEMENTATION SESSION SCORES, AND IT IS `objdump` AGAIN**

| | prediction | falsified by |
|---|---|---|
| **`S-7`** | `-Wall -Wextra -fsyntax-only` on `gevr_xr.c` with `-DGEVR_XR_HAVE_OPENXR` after the four entry points: gcc exit `0`, **log `0` bytes** | any diagnostic. `328`'s `S-5` set this bar at `0` bytes and it is not softened |
| **`S-8`** | `-Target port -Vr` and `-Target app -Vr` both exit `0`, no `failed`/`error`/`warning`/`undefined` in the log | any of them |
| ►► **`K-7`** ◄◄ | **`objdump -p goldeneye.exe.vr329` NAMES `openxr_loader.dll` AND LISTS `19` `xr*` IMPORTS: `328`'s TWELVE PLUS `xrPollEvent`, `xrBeginSession`, `xrEndSession`, `xrRequestExitSession`, `xrWaitFrame`, `xrBeginFrame`, `xrEndFrame`** (`23` under `B2`) | **any of `xrWaitFrame`, `xrBeginFrame`, `xrEndFrame` absent.** Then the loop is not in the binary and nothing about it may be claimed -- `327` section `2.1`'s lesson, taken a second time rather than assumed away |
| **`K-8`** | the plain build compiles and links, **no log line names `openxr`**, seven DLLs, **`0`** `xr*` imports | any `xr*` import in the plain binary, or a plain build that fails. **`K-5` IS RE-TAKEN, NOT INHERITED** -- the new code is several times the size of `328`'s and inheriting a gate across a rewrite is how one gets missed |
| **`K-9`** | with `GETV_XR_KILL` unset, the `-Vr` binary boots and plays with **no `[getv][vr]` and no `[getv][xrkill]` output** | any such line with the knob unset. **AND `K-9` HAS NO BASELINE UNTIL `K-6` IS TAKEN** -- `K-6` is parked, that dependency is named here, **and it is a dependency, not a hole** |

**SIZE SCORES NOTHING, AGAIN.** `328` section `2` ruled it insufficient while it happened to point
the right way, and it stays insufficient.

### 5.2 -- **`K-3`, AND IT IS NOT THIS SESSION'S AND NOT THIS SESSION'S TO GREEN-LIGHT**

Pre-registered here so it cannot be written after the numbers are seen. **THE RUN THAT SCORES IT
NEEDS ITS OWN GREEN-LIGHT, ITS OWN RUN SHEET AND A CONDITIONS SIDECAR** (`325` section `2`:
**`VISIBLE` NO LONGER IMPLIES WORN** -- label the run by the sidecar, never by the session state).

| | reads | means |
|---|---|---|
| **`K-3` LANDS** | mean return-to-return interval within `0.500%` of the run's own `predictedDisplayPeriod` | **`xrWaitFrame` BLOCKS IN THE GAME TOO. `D-X3` SURVIVES. IT IS NOT BUILT** |
| **`K-3` FALSIFIED** | interval far below the period, or `xrWaitFrame` returns immediately | **UNDER `B2` ONLY: `D-X3` IS DEAD ON THE SPOT** and that is the cheapest outcome available. **UNDER `B1` THIS READS AS `K-3 NEITHER`** and mandates `B2` (fork `B`) |
| **`K-3` NEITHER** | blocks, but not to the advertised period; or `B1` returned non-blocking | a finding, unranked, `D-X3` stays open with a named next arm |

**AND TWO CONDITIONS ARE PART OF THE PREDICTION, NOT FOOTNOTES:** the run needs `GETV_VR=1` **and**
`GETV_XR_KILL=1` **and** SteamVR up with the HMD awake -- `xrGetSystem` returns `-35` otherwise and
that is a **REFUSAL, NOT A MEASUREMENT** (`gevr_xr.c:234`). And the sidecar records worn/desk,
because `325` measured a desk run reaching `VISIBLE` for `88` frames.

---

## 6 -- **THE STANDING LINE, UNCHANGED, AND IT IS LOAD-BEARING TWICE OVER NOW**

`GETV_XR_KILL` **NEVER** reads `geVrXrPacingOwned()`. It **NEVER** touches
`sync_framerate_with_timer()`. **NO HANDOVER, NOT THIS SESSION AND NOT THE ONE THAT WRITES THE
CODE.**

**AND THE TEMPTATION IS BIGGER NOW THAN IT WAS IN `328`, WHICH IS WHY IT IS RESTATED.** This
design puts a live `xrWaitFrame` and a measured `predictedDisplayPeriod` in the same function --
the two inputs `geVrXrPaceArm()` takes. **THE INTERLOCK IS NOT ARMED BY THIS LOOP.** Arming it is
`I-3`/`D-X3` proper, it is gated on `K-3` having an answer, and a diff that contains
`geVrXrPaceArm` has broken this line.

---

## 7 -- **WHAT THIS PLAN WILL NOT DO, WHATEVER THE ANSWER**

No `H19`, no `U-28` filed, no `SHAPE A`/`B`, no `GX-0`, no desk-`VISIBLE` cause, no graphics, no
extras. **NO `K-6` -- IT IS PARKED.** No re-do of `K-4`/`K-5`. No handover, no `geVrXrPacingOwned`,
no `sync_framerate`. No `gfx_sdl2.c`, no `getv/patches`, no `build_windows.ps1` edit -- `328`
proved the link line is already right and **`K-7` is a prediction that it stays right**. No eye
loop, no swapchain images touched, no `glBindFramebuffer`, no submit, no layer.
**Nothing staged, committed, branched, merged, tagged or pushed.**

---

## 8 -- **THE STOPPING LINE, AND IT IS HERE**

**THE OWNER ANSWERS FOUR THINGS AND NOTHING IS TYPED UNTIL THEN:**

1. **FORK `A` -- loop length.** Proposed **`A2`**: `300` frames, warm-up `30`, per-iteration body
   byte-identical to `ge_s3_armA`, deviation printed in the report.
2. **FORK `B` -- swapchains.** Proposed **`B1`** (none), **with the non-blocking case
   pre-registered as `K-3 NEITHER` rather than as a kill.**
3. **FORK `C` -- output.** Proposed **`C2`**: stdout and `getv_xrkill_report.txt`.
4. **MAY `geVrXrEndSession()` BE CORRECTED** to end a begun session before destroying it, and may
   the four new entry points land in `gevr_xr.h`/`gevr_xr.c` with **one** added call in
   `port_render.c`? (Section `3`. And: arrays inside `GEVR_XR_LIVE`, or in both builds?)

**`K-3` IS NOT ON THIS LIST.** It is a run, it is at the chair, it needs a sidecar and a sheet, and
it is a later session's green-light.

`169` NEXT ID = `U-28`. NEXT INSTRUMENT HOLE = `H25`.
