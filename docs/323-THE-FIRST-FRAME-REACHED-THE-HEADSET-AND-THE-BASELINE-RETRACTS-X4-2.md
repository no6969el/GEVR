# `323` -- **THE FIRST FRAME REACHED THE HEADSET. AND THE BASELINE RETRACTS `X4-2`'s CAUSE**

**2026-09-05. OFFLINE ASSISTANT. NOTHING BUILT, RUN, STAGED, COMMITTED, BRANCHED, MERGED OR
TAGGED BY THE ASSISTANT.** Two owner pastes on the main PC: one compile, one run.
**No PRODUCT source edited; `gevr_xr.c` md5 `2de74d753289fe82b2f07c863ea10c37` before and after,
gated in `RUN-SHEET-323` BLOCK 1 and printed by the owner.**

---

## section 0 -- **WHAT THIS SESSION DID, IN FIVE LINES**

1. **Confirmed the disk first.** `322`'s two commits were NOT in; landed them (`7a64bb2`,
   `24cdab3`), then found `00-STATE`'s currency line still said `321` while its body carried
   `322`'s findings -- **the `308` trap, one file deep** -- and fixed it at `088ab9e`.
2. **Wrote `PLAN-323-X4.md` FIRST and stopped.** The owner green-lit it, chose FORK `1A`, kept
   step `8` and kept `600` / `30`.
3. **Edited ONE TRACKED INSTRUMENT, `+10 / -0`:** a `GE_S3_NO_MAIN` guard around slice 3's
   `main`. **Not product. `ge_s3_armA` and `ge_s3_score` byte-identical.**
4. **Wrote `repo\xr\gevr_xr_slice4.c` (`929` lines) and `RUN-SHEET-323.md`** with nine gates
   pre-registered before the harness could run.
5. **The owner built it and ran it. `EXIT 0`. A FRAME REACHED THE HEADSET FOR THE FIRST TIME IN
   THIS PROJECT'S HISTORY -- AND THE RUN'S OWN BASELINE SHOWS THE SUBMIT IS NOT WHAT MADE THE
   SESSION VISIBLE.** Both halves of that sentence are section 1 and section 2.

---

## section 1 -- **THE PICTURE IS REAL, AND IT IS `X4-1`**

`[MEASURED]` `repo\xr\gevr_xr_slice4_report.txt`, `8495` bytes at **`19:40`**, from
`gevr_xr_slice4.exe` `307881` bytes at `19:40`. `SteamVR/OpenXR v2.16.7` / `aapvr`, `RTX 5090`,
GL `4.6.0 NVIDIA 616.56`, per-eye rect `4140 x 3292`. **`[smoke4] EXIT 0`.**

| | `[MEASURED]` |
|---|---|
| projection layers accepted by `xrEndFrame` | **`570` of `570` scored, `600` over the run** |
| `xrLocateViews` frames without valid pose+orientation | **`0` of `600`** |
| `glCheckFramebufferStatus` refusals | **`0`** |
| `xrWaitSwapchainImage` timeouts | **`0`**, worst wait **`2.2416 ms`** against a `100 ms` budget |
| `XR_FRAME_DISCARDED` | **`0` of `600`** |
| all five GL 3.0 framebuffer entry points | **resolved under their CORE names**, no `EXT` fallback needed |

**`X4-1` LANDS. `xrEndFrame` ACCEPTED A TWO-VIEW PROJECTION LAYER ON EVERY FRAME IT WAS OFFERED
ONE.** The acquire -> wait -> bind -> clear -> release -> submit path works end to end on this
runtime, at `4140 x 3292` per eye, in `GL_SRGB8_ALPHA8`.

**AND THE OWNER SAW IT.** `[REPORTED, OWNER PASTE]`: **"red on the left and blue in the right
eye"** -- eye `0` was cleared to deep red and eye `1` to deep blue, which is the mapping
`gevr_xr_slice4.c` writes. **The per-eye paths are genuinely separate and they are not
swapped.** This is an OBSERVATION, it was never a gate, the harness scored nothing about it,
and **it is not a stereo correctness claim** -- no correlator was involved and none is implied.

**FIVE SESSIONS OF PLUMBING ENDED HERE. `X2` AND `X3` WERE PLUMBING EXISTING; THIS IS A
PICTURE.**

---

## section 2 -- **AND NOW THE PART THAT MATTERS MORE: `X4-2`'s CAUSAL CLAIM IS RETRACTED**

**THE HARNESS PRINTED THIS, AND THE SECOND SENTENCE IS WRONG:**

> `X4-2 LANDS. The session reached VISIBLE, which it NEVER DID IN` `322` `(SYNCHRONIZED,`
> `frame 1, and never moved).` **`SUBMITTING LAYERS IS WHAT MOVED IT.`**

`[MEASURED]`, from the same report, lines `59`-`61` and `95`:

```
[getv][vr] X3 state READY -> SYNCHRONIZED at frame 1
[getv][vr] X3 state SYNCHRONIZED -> VISIBLE at frame 1
[getv][vr] X3 ARM A completed 600 frames, 2 state transitions during the loop.
[getv][vr] X4 completed 600 frames, 0 state transitions, 600 layers submitted.
```

**THE SESSION BECAME `VISIBLE` AT FRAME `1` OF ARM A -- IN THE `layerCount 0` BASELINE, BEFORE A
SINGLE LAYER EXISTED. THE `X4` LOOP MOVED THE SESSION STATE ZERO TIMES.**

**SO SUBMITTING IS NOT WHAT MADE IT VISIBLE, AND THE `X4-2` LINE IN THE REPORT MUST BE READ AS
A MEASUREMENT (`VISIBLE` was reached) WITH A FALSE ATTRIBUTION APPENDED (that the submit did
it). THE MEASUREMENT STANDS. THE CAUSE IS WITHDRAWN.**

### 2.1 -- **THE CONTROL DID ITS JOB BY FAILING TO REPRODUCE THE CONDITION**

The in-run ARM A baseline existed for exactly one reason: to be `322`'s run under `323`'s
conditions. **It did not reproduce `322`.**

| | `322` `19:11` | `323` `19:40` ARM A -- **SAME CODE, `ge_s3_armA` BYTE-IDENTICAL** |
|---|---|---|
| session states in the loop | `READY -> SYNCHRONIZED` at frame `1`, **`1` transition, never moved again** | `READY -> SYNCHRONIZED -> VISIBLE` at frame `1`, **`2` transitions** |
| `shouldRender` | **FALSE on all `570`** | **TRUE on all `570`** |
| `predictedDisplayPeriod` | `11.1111 ms`, spread `0.0000%` | `11.1111 ms`, spread `0.0000%` |
| mean interval | `11.1188 ms` | `11.1202 ms` |
| layers submitted | `0` | `0` |

**IDENTICAL CODE, IDENTICAL PERIOD, OPPOSITE `shouldRender`.** Something outside this source
tree differed between `19:11` and `19:40`, and **it is the thing that decides whether a session
goes `VISIBLE`, not the submit.**

**IF THE BASELINE HAD BEEN TAKEN FROM `322`'s NUMBERS INSTEAD OF RUN IN-PROCESS, THIS SESSION
WOULD HAVE FILED "SUBMITTING LAYERS MAKES THE SESSION VISIBLE" AS A FINDING AND IT WOULD HAVE
BEEN FALSE.** The in-run control is the only reason it is not being filed. **That is the whole
argument for running the baseline in the same process, and it paid for itself on its first use.**

### 2.2 -- **WHAT THE DIFFERENCE ACTUALLY WAS IS NOT KNOWN, AND IS NOT GUESSED HERE**

Candidates, **NONE OF THEM MEASURED AND NONE OF THEM ASSERTED**: which application SteamVR
considered the focused scene app at `19:11` versus `19:40`; whether the SteamVR dashboard or
another OpenXR client held the compositor; whether the headset was on the owner's head, awake
on a desk, or in proximity-sleep. **`322` and `323` were both remote runs and neither sheet
recorded any of this, which is itself the lesson.**

**THIS IS NOT FILED AND IT IS NOT A HOLE** (`301` section 0). It is `324`'s first question and
it has a cheap shape: **run the SAME binary twice under deliberately different headset/focus
conditions and see which one reproduces `322`.** No new code is needed -- `gevr_xr_slice4.exe`
already prints everything the question needs.

### 2.3 -- **AND `X4-3` INHERITS THE SAME CAUTION**

`X4-3` LANDS as a measurement: `shouldRender` true on `570` of `570` scored frames, above the
pre-registered `50%`. **But it was ALSO true on `570` of `570` baseline frames with no layer
submitted**, so the implied contrast with `322`'s `X3-3` is **not established by this run**.
`322`'s `X3-3` limit was lifted by whatever made the session `VISIBLE` -- **and that is not
known to be the eye loop.**

**WHAT `X4` DID ESTABLISH, AND IT IS NOT SMALL:** the submit path is correct and accepted, and
the cadence is now measured **in a session that was actually rendering** -- which is the thing
`322` explicitly could not speak for.

---

## section 3 -- **`X4-5`: SUBMITTING COST THE PERIOD NOTHING**

`[MEASURED]`, both halves of the same run, `570` scored each:

| | ARM A, `layerCount 0` | `X4`, `layerCount 1`, two `4140 x 3292` eyes |
|---|---|---|
| `predictedDisplayPeriod` | `11.1111` min AND max, spread `0.0000%` | **identical** |
| interval mean | `11.1202 ms` | **`11.1202 ms`** |
| interval `p50` / `p95` / `p99` | `11.1106` / `11.1334` / `11.1555` | `11.1121` / `11.2631` / `11.3771` |
| interval min / max | `10.8635` / **`14.5937`** | `10.2282` / `11.5727` |

**`X4-5` LANDS. THE MEANS AGREE TO FOUR DECIMAL PLACES.** Clearing two `4140 x 3292` eyes and
submitting a projection layer did not move the pacing at all.

**AND THE TAILS SWAPPED, WHICH NOTHING PREDICTED.** The `layerCount 0` half carries the run's
single worst frame (**`14.5937 ms`**, one period-and-a-third) while the half that actually
renders has a tighter maximum (`11.5727 ms`) and a fatter `p95`/`p99`. `[ARITHMETIC]` the
excess over the period is `11.1202 - 11.1111 = 0.0091 ms` per frame in BOTH halves.
**RECORDED, NOT EXPLAINED HERE.** A clear is not a game frame and this says nothing about what
Fast3D will cost.

---

## section 4 -- **WHAT IS STILL TRUE, AND WHAT IS NOW OWED**

- **`gevr_xr.c` UNCHANGED**, md5 `2de74d753289fe82b2f07c863ea10c37`. The game still compiles
  the inert stub: `GEVR_XR_HAVE_OPENXR` undefined, `build_windows.ps1` unedited,
  **loader still not vendored.** No product line was written this session.
- **`321` section 2.2's FORMAT DEBT IS PAID.** `PLAN-323-X4` section 2 wrote the reason for
  `GL_SRGB8_ALPHA8` **before** the run: Fast3D is 8-bit so `GL_RGBA16` would carry padding not
  precision; `~109 MB` against `~218 MB` of write traffic per frame; and it is what `X2` already
  creates, so `X4` moved one variable. **The runtime's `0x805B` ranking is declined WITH A
  REASON. STILL NOT `U-29`, and `X4` measured `0` discarded frames at that format.**
- **THE `D-X3` INTERLOCK IS STILL OWED AND IS UNCHANGED BY THIS RUN.**
  `[MEASURED]` `90.0001 Hz`; `[ARITHMETIC]` `90.0001 / 60 = 1.500002` against `274` section 2's
  `1.500x`. `PLAN-322-X3` section 6's shape stands. **NOT FILED, NOT A HOLE.**
- **`H19` OPEN AND UNPATCHED.** `[DISPOSAL] 9a` stands; `a = 1.060225` per eye is still printed
  by slice 1 as `[ARITHMETIC]` and is still an inference about a path the game does not take.
  **WRONG FILED FIXES STAY AT FIVE.**
- **`U-28` RESERVED AND UNFILED. `U-29` NOT INVENTED. `H24` still blinds every `WS=1` arm.**
  The `57`-file scrub is still nobody's.
- **NEWLY OWED, AND NOT FILED:** section 2.2's question -- **what makes this runtime take a
  session to `VISIBLE`** -- and the run-condition recording that would have answered it without
  a second run.

---

## section 5 -- **THE RULE THAT WAS TESTED AND HELD**

`RUN-SHEET-323` section 3.2 pre-registered: *if `X4-1` succeeds and `shouldRender` is still
false, that is a finding and it gets written, not fixed.* **The opposite happened -- everything
landed -- and the rule still did its work, because the thing that needed writing rather than
fixing turned out to be `X4-2`'s attribution.**

**NOTHING WAS RE-RUN TO TIDY THIS UP.** The report's `X4-2` line still says
`SUBMITTING LAYERS IS WHAT MOVED IT`; the code that prints it is unedited and the run is not
repeated to make the paste agree with this document. **The report is evidence and the
correction lives here** -- `319` and `321`'s `UTF-16LE` reports were left alone for the same
reason. **A sixth wrong filed fix was available this session and was declined.**

**`169` NEXT ID = `U-28`. NEXT INSTRUMENT HOLE = `H25`.**
