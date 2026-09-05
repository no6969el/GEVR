# `330` -- **`xrWaitFrame` BLOCKS IN `goldeneye.exe`, TO `11.1111 ms`, AND `xrEndSession` RETURNED `XR_SUCCESS` FOR THE FIRST TIME IN THIS PROJECT**

---

## 0 -- ONE TABLE

| | |
|---|---|
| `1` | **`K-6` LANDS.** `vr329` with every `GETV_` knob unset and SteamVR closed: `[MEASURED]` `23,009` captured stdout lines, **`0`** `[getv][vr]`, **`0`** `[getv][xrkill]`, no report file, last frame `1081`. The gate is a gate and **`K-9`'s baseline is closed** |
| `2` | ►► **`K-3` LANDS, IN THE GAME PROCESS, AND IT IS THE SESSION.** `[MEASURED]` mean return-to-return interval **`11.1320 ms`** against a `predictedDisplayPeriod` of **`11.1111 ms` min AND max**, `270` frames scored. **`xrWaitFrame` BLOCKS WHERE THE GL CONTEXT, THE SDL PUMP AND THE SWAP BELONG TO SOMEONE ELSE. `D-X3` SURVIVES. IT IS NOT BUILT** ◄◄ |
| `3` | **AND IT LANDS ON BOTH BANDS.** `[ARITHMETIC]` the deviation is **`0.1881%`** -- inside the instrument's `10%` and inside `PLAN-329` section `5.2`'s `0.500%`. **THE BAND GAP `PLAN-330` PRE-REGISTERED DID NOT HAVE TO BE ADJUDICATED** |
| `4` | ►► **`xrEndSession -> XR_SUCCESS (0)`, CALLED FROM `STOPPING`.** `329` section `2` found that this project had never measured that call succeed. **IT HAS NOW, AND IT SUCCEEDED BECAUSE `329` CORRECTED THE TEARDOWN** ◄◄ |
| `5` | **`B1` DID NOT GO `NEITHER`. `B2` IS NOT MANDATED BY THIS RUN** -- the swapchain-free arm blocked, so the asymmetric reading never had to be used |
| `6` | **`K-3c` IS NEW: a `DESK` run went `VISIBLE` at frame `1` AND HELD IT FOR ALL `300` FRAMES.** `shouldRender` true **`270` of `270`**, with no layer ever submitted |
| `7` | **FORK `C2`'s FIRST EXERCISE HOLDS EXACTLY.** `[MEASURED]` the report file and the captured stdout carry the **same `38` lines**, byte for byte |
| `8` | **THE INTERLOCK IS NOT ARMED. NOTHING WAS FIXED. WRONG FILED FIXES STAY FIVE.** `H19` open, `U-28` reserved unfiled, `H24` unchanged |

---

## 1 -- **`K-3`, AND THE NUMBERS ARE OFF THE REPORT ON DISK**

`[MEASURED]` `repo\xr\getv_xrkill_report_330_DESK.txt` (`41` lines, `2,953` bytes), sidecar
`repo\xr\getv_xrkill_330_K3_DESK_conditions.txt`, `18:59:45`, `goldeneye.exe` md5
`70BF2580239CD6B7C402C063D89B976F` / `18,101,808` -- **`goldeneye.exe.vr329`, the binary `K-7`
scored.**

| | |
|---|---|
| interval ms | **mean `11.1320`** min `10.6435` max `14.6934` |
| interval ms | p50 `11.1120` p95 `11.1373` p99 `11.5787` |
| period ms | min `11.1111` max `11.1111` **spread `0.0000%`** => **`90.0001 Hz`** |
| `shouldRender` | **`270` of `270` true** |
| discarded | **`0`** of `300` reported `XR_FRAME_DISCARDED` |
| wall clock | **`3005.64 ms`** measured, `3000.00 ms` if every frame had cost exactly one period |

**THE VERDICT LINE, VERBATIM:**

    K-3 LANDS. mean interval 11.1320 ms is inside 10% of the runtime's own
        period (11.1111 .. 11.1111 ms). xrWaitFrame BLOCKS IN THE GAME PROCESS, where
        the GL context, the SDL pump and the swap belong to someone else.
        D-X3 SURVIVES. IT IS NOT BUILT.

### 1.1 -- **BOTH BANDS, BECAUSE `PLAN-330` SECTION `4.2` SAID BOTH WOULD BE REPORTED**

`[ARITHMETIC]` `(11.1320 - 11.1111) / 11.1111 = 0.18810%`. The instrument's band is `10%`
(inherited byte-identically from `ge_s3_score`); `PLAN-329` section `5.2`'s prose says `0.500%`.
**`0.1881%` IS INSIDE BOTH, SO THE SCORE IS THE SAME UNDER EITHER READING** and the gap between
the two was never load-bearing on this run. **NEITHER NUMBER WAS ADJUSTED AND THE INSTRUMENT WAS
NOT EDITED.**

### 1.2 -- **AND THE TWO INDEPENDENT READINGS AGREE TO THREE DECIMAL PLACES**

`[ARITHMETIC]` the excess wall clock is `3005.64 - 3000.00 = 5.64 ms` over `270` scored frames =
**`0.0209 ms` per frame**, and `mean - period = 11.1320 - 11.1111 =` **`0.0209 ms`**. `5.64 / 3000
= 0.188%`, against the mean's `0.1881%`. **A FLAT PER-FRAME COST, NOT STALLS HIDING IN A MEAN** --
the same shape `322` measured standalone, confirmed the same two ways.

**AND IT IS BIGGER IN THE GAME THAN IT WAS ON THE BENCH.** `[ARITHMETIC]` standalone slice 3
(`322`) ran `0.0077 ms` a frame over the period; `325` `0.0090 ms`; **this run `0.0209 ms`.** Same
order, same flatness, roughly `2.3` to `2.7` times the excess. **NO CAUSE IS OFFERED.** A process
that owns a GL context, an audio thread and a game loop is not a bench harness, and **which of
those it is was not measured.** `[MEASURED]` `p99 11.5787` and `max 14.6934` say one or two
intervals ran long; `325` saw `max 14.4042` on the bench with the same shape. **NOT FILED, NOT A
HOLE** (`301`).

---

## 2 -- ►► **THE FINDING `329` WENT LOOKING FOR, ANSWERED BY A RUN** ◄◄

`[MEASURED]`, from the report, in order:

    [getv][xrkill] xrRequestExitSession -> XR_SUCCESS (0)
    [getv][xrkill] state VISIBLE -> SYNCHRONIZED at frame 300
    [getv][xrkill] state SYNCHRONIZED -> STOPPING at frame 300
    [getv][xrkill] xrEndSession -> XR_SUCCESS (0)   (state at the call: STOPPING)

`329` section `2` read `gevr_xr_slice2.c:351-360`, found the result discarded and
`session ended.` printed regardless, and said **this project had never observed `xrEndSession`
succeed.** **IT HAS NOW.** The exit was requested, the runtime offered `STOPPING`, the call was
made **from** `STOPPING`, and the result is printed by name.

**AND THE CORRECTION IS WHAT MADE IT MEASURABLE.** `329` rewrote `geVrXrSessionStop()` to request
the exit, pump to `STOPPING` under a bounded budget and print the result with the state it was
called from -- **written before any of this ran, on the strength of reading the slices rather than
running them.** A session that had been ended straight out of `VISIBLE` would have returned
`XR_ERROR_SESSION_NOT_STOPPING` and this line would read differently.

---

## 3 -- **`K-3c`, AND IT IS A THIRD THING ABOUT `DESK` RUNS**

`[MEASURED]` `state READY -> SYNCHRONIZED at frame 1`, `SYNCHRONIZED -> VISIBLE at frame 1`, and
**no transition out of `VISIBLE` until frame `300`, when the exit was requested.** `shouldRender`
was true on **every** scored frame, `270` of `270`, **with no layer ever submitted.**

| run | condition | `VISIBLE` | `shouldRender` |
|---|---|---|---|
| `322` | desk | never | `0` of `570` |
| `324a` | desk | never | `0` of `570` |
| `324b` | worn | yes | -- |
| `325` | desk | frame `1` to frame `88` | `58` of `570`, **frame for frame** |
| ►► **`330`** ◄◄ | **desk** | **frame `1`, held to `300`** | **`270` of `270`** |

**WHAT THIS ADDS:** `325` established that desk does not prevent `VISIBLE`. **`330` ADDS THAT
DESK DOES NOT PREVENT HOLDING IT EITHER**, for the whole of a `3 s` window. **WHAT IT DOES NOT
ADD: A CAUSE.** This arm differs from all four priors on more than one axis at once -- it is in
the game process, the window is shown and foreground, and it has **no swapchain** -- **and this
run cannot separate them.** `324` retracted a causal claim for exactly this reason. **NOT FILED,
NOT A HOLE.**

**THE INSTRUMENT'S OWN LIMIT, KEPT:** *"It says the runtime expected frames it never got."*
`shouldRender` true with nothing submitted is not evidence about a rendering VR game loop, and
**a submit was not added in the same session to make it real** -- the instrument says so in its
own output and the standing rule says so twice over.

---

## 4 -- **THE FREEZE WAS `3.0 s`, NOT `13.3 s`, AND THE TWO POLL BUDGETS GOT THEIR FIRST MEASUREMENT**

`PLAN-330-CHAIR` section `2.5` put the unpumped window at **`3,333 ms` expected and up to
`13,333 ms`** -- `A2`'s loop plus a `5,000 ms` `READY` budget in front and a `5,000 ms` `STOPPING`
budget behind, all inside one `gePortRenderDisplayList()` call. `[MEASURED]`:

| segment | what it cost |
|---|---|
| `READY` poll | `UNKNOWN -> IDLE -> READY`, **`2` transitions, no sleep reported** -- `321`'s *"`READY` arrived before the first sleep"* holds in the game process too |
| the loop | **`3005.64 ms`** |
| `STOPPING` poll | both transitions **at frame `300`**, i.e. inside the pump, **not `5,000 ms`** |

►► **SO THE WORST CASE DID NOT MATERIALISE AND THE EXIT BUDGET HAS NOW BEEN MEASURED AT
APPROXIMATELY ZERO** -- a number nothing in this project had. **THE UNPUMPED WINDOW WAS UNDER THE
`~5 s` GHOSTING THRESHOLD `A2` WAS CHOSEN TO STAY UNDER**, which is `A2`'s rationale surviving a
run rather than an argument. ◄◄

**AND THE GAME CAME BACK.** `[MEASURED]` `k3_330_stdout.log`: `[getv][vr] session destroyed.`,
then `[getv] frame 121:` with normal per-frame instrumentation, and the log runs on to
**`[getv] frame 13861`** and ends `[getv] game_exit requested`. **`13,741` FRAMES RENDERED AFTER
THE LOOP.**

### 4.1 -- **THE MENU LOCKUP, RECORDED IN THE OWNER'S WORDS AND ATTRIBUTED TO NOTHING**

`[REPORTED]` sidecar, chair: *"Dam gameplay through level end (Bond jump-off sequence); lockup on
return to menu"*, `killed yes -- closed with X after menu lockup (process would not quit
normally)`.

**IT IS NOT ATTRIBUTED TO THE LOOP AND IT IS NOT FILED.** The loop completed at frame `120`, tore
down cleanly, and the game rendered nearly fourteen thousand frames afterwards through a whole
level. **AND IT HAS NO CONTROL:** `K-6` quit normally but **did not run the same Dam-to-menu exit
path**, so there is no baseline for that transition on either binary. **THAT IS A NAMED GAP, NOT A
HOLE** (`301`). Candidates -- a pre-existing menu-return fault, or a delayed consequence of an XR
session having existed in the process -- are **candidates, and neither was measured.**

---

## 5 -- **FORK `C2`'s FIRST EXERCISE, AND IT HOLDS EXACTLY**

`[MEASURED]` `330`, comparing `getv_xrkill_report_330_DESK.txt` against the `[getv][xrkill]` and
report lines of `k3_330_stdout.log`: **`38` non-blank lines, IDENTICAL.** Every line
`ge_xk_say()` wrote reached both sinks, which is the claim `329` made by reading and could not
test. **`RUN-SHEET-329` SECTION `2` SAID THE FIRST EXERCISE OF THE REPORT PATH WOULD BE `K-3`'s OWN
RUN. IT WAS, AND THE PATH WORKS.**

**AND THE REFUSAL PATHS WERE NEVER REACHED, SO THEY ARE STILL UNTESTED.**
`PLAN-330-CHAIR` section `2.2`'s three stdout-only refusals at the call site did not fire on this
run -- `geVrXrEnabled()`, `geVrXrInit()` and `geVrXrBeginSessionCurrent()` all returned `1`.
**THE CAPTURE THAT WOULD HAVE CAUGHT THEM WAS TAKEN ANYWAY, WHICH IS WHY THE `[getv][vr]` BLOCK IN
SECTION `6` EXISTS AT ALL.**

---

## 6 -- **WHAT THE CAPTURE PICKED UP THAT NOTHING ASKED FOR: THE SLICE-1 HANDSHAKE, IN THE GAME, FOR THE FIRST TIME**

`[MEASURED]` `k3_330_stdout.log` lines `427-437`, printed by `geVrXrInit()` in `goldeneye.exe`:

| | |
|---|---|
| runtime | `SteamVR/OpenXR  v2.16.7` |
| system | `SteamVR/OpenXR : aapvr` (vendor id `10462`) |
| extensions advertised | `41`, `XR_KHR_opengl_enable: yes` |
| view `0` / view `1` recommended | **`4140 x 3292`** each, max `8192 x 8192`, samples rec `1` max `1`, **rects identical across views** |
| GL | required min `4.3` max `4.6`; **context reports `4.6.0 NVIDIA 616.56`** |

**THESE ARE THE SAME NUMBERS THE STANDALONE SLICES READ**, now read **inside the game process, on
the game's own GL context** -- `X2`'s gates re-passing where it counts. **This is a corroboration,
not a new claim**, and it exists in the record only because fork `F2` captured stdout.

### 6.1 -- **AND THE CAPTURE ALSO SHOWS THE SECOND STALE BANNER. NEITHER IS PATCHED**

`[MEASURED]`, in this run's own output, `11` lines apart:

    [getv][vr] AND IT STOPS HERE. No xrBeginSession (that needs the event loop and a
    view-configuration commitment), no swapchain, no xrWaitFrame, no submit.
    ...
    [getv][xrkill] ARMED for frame 120. SESSION CREATE ONLY -- there is no xrWaitFrame
    in this build and this does not answer D-X3-KILL.

**AND THEN THE SAME RUN DID `xrBeginSession` AND `300` `xrWaitFrame` CALLS.** `PLAN-330-CHAIR`
section `2.1` named the second one before the run; **the first one -- slice 1's, in `gevr_xr.c` --
is found by this run and is the same class of thing.** **NEITHER IS FIXED IN THIS SESSION** (`301`,
and a rebuild would invalidate the md5 every result above is keyed to). **THEY ARE STALE STRINGS,
NOT STATEMENTS ABOUT THE BUILD**, and the next session that touches `gevr_xr.c` for any other
reason is the cheap place to correct them.

---

## 7 -- ►► **WHAT THIS SESSION DOES NOT CLAIM** ◄◄

1. **IT DOES NOT ARM THE INTERLOCK, AND A LANDED `K-3` IS NOT PERMISSION TO.** `[MEASURED]`
   `K-3d`, in the run's own output: `geVrXrPaceArm()` NOT called, `geVrXrPacingOwned()` NOT read,
   `sync_framerate_with_timer()` KEEPS THE CLOCK. **THE HANDOVER IS `I-3`/`D-X3` PROPER: its own
   plan, its own falsifier, its own green-light.**
2. **IT DOES NOT BUILD OR DESIGN `B2`, AND `B2` IS NOT MANDATED.** The `B1` mandate fires only on
   a non-blocking result. **The arm blocked.** Whether a swapchain changes the cadence is
   **untested and unclaimed** -- this run says nothing about it either way.
3. **IT DOES NOT EXPLAIN THE `DESK`/`VISIBLE` BEHAVIOUR** (section `3`), the larger per-frame
   excess (section `1.2`), or the menu lockup (section `4.1`). Three observations, no causes.
4. **IT DOES NOT TOUCH A PRODUCT FILE.** No edit, no rebuild, no new binary. `goldeneye.exe` was
   staged from `goldeneye.exe.vr329` for both runs and restored from `goldeneye.exe.plain329`
   afterwards: `[MEASURED]` `037EDBD61D293C1CA0419418927715D7` / `18,075,663`, and `.vr329`,
   `.plain329`, `.vr328`, `.plain328` untouched.
5. **NOTHING WAS FIXED BECAUSE SOMETHING WAS DIAGNOSED.** Two stale banners, the `10%`-vs-`0.500%`
   band, the CWD-relative `fopen`: **all named, none patched.** `H19` open. `U-28` reserved
   unfiled. `H24` unchanged. **WRONG FILED FIXES STAY FIVE.**

---

## 8 -- **ARTIFACTS** (gitignored logs OK)

| file | |
|---|---|
| `repo\xr\getv_xrkill_report_330_DESK.txt` | **`41` lines, `2,953` bytes.** The first `getv_xrkill_report.txt` this project has ever produced; the live copy is beside the binary in `getv\build-windows` and a later run will overwrite it |
| `repo\xr\getv_xrkill_330_K3_DESK_conditions.txt` | the sidecar that labels the run `DESK`. **Without it the run is unlabelled** (`325` section `2`) |
| `repo\xr\getv_xrkill_330_K6_conditions.txt` | `K-6`'s sidecar |
| `repo\xr\k3_330_stdout.log` | `76,268,410` bytes, `731,802` lines |
| `repo\xr\k6_330_stdout.log` | `2,667,826` bytes, `23,009` lines |

►► **BOTH LOGS ARE `UTF-16LE` WITH `CRLF`** -- PowerShell's `*>` redirection writes that, and
`Select-String` reads it back without complaint. **A UTF-8 TOOL READING THEM FINDS NOTHING AND
REPORTS `0` MATCHES**, which is indistinguishable from a clean run if nobody checks the encoding
first. Convert before grepping with anything else. ◄◄

**NOTHING STAGED, COMMITTED, BRANCHED, MERGED, TAGGED OR PUSHED BY THE RUNS.** The docs commit is
`RUN-SHEET-330` section `4`'s path list.

---

## 9 -- **WHAT IS NOW OWED, AND `330` DOES NOT PICK IT**

**`D-X3` SURVIVES AND IT IS NOT BUILT.** The next question is the handover -- `I-3`/`D-X3` proper,
arming `geVrXrPaceArm()` against a measured `predictedDisplayPeriod` -- **and `PLAN-329` section
`6` and `PLAN-330` section `6` both say it is a fresh session's `HIGH` with its own plan and its
own falsifier.** `00-STATE` section `7c` forbids starting it at the end of one.

**NO NEW FORK IS INVENTED HERE.** The three unexplained observations in section `7.3` are
observations; **whether any of them earns an arm is a decision, not a consequence.**

`169` NEXT ID = `U-28`. NEXT INSTRUMENT HOLE = `H25`.
