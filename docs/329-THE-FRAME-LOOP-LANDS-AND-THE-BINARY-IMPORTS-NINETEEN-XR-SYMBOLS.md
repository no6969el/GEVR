# `329` -- **THE FRAME LOOP IS IN THE BINARY. NINETEEN `xr*` IMPORTS, `xrWaitFrame` AMONG THEM. AND NOBODY HAS RUN IT**

---

## 0 -- ONE TABLE

| | |
|---|---|
| `1` | **`PLAN-329-FRAMELOOP` WAS WRITTEN, FORKED AND GREEN-LIT IN THIS SESSION.** Design first, three forks answered by the owner, then `602` lines typed. `00-STATE` section `7c` |
| `2` | **`S-7` LANDS.** `-Wall -Wextra -fsyntax-only` on `gevr_xr.c` with `-DGEVR_XR_HAVE_OPENXR`, after four new entry points: gcc exit `0`, log **`0` BYTES**. All three named candidates dead |
| `3` | **`S-8` LANDS.** `-Target port -Vr` and `-Target app -Vr` both exit `0`; `60 built, 0 failed`, `2 built, 0 failed`, `libge.a 24.9 MB, 502 members` |
| `4` | ►► **`K-7` LANDS, EXACTLY AS PRE-REGISTERED, AND IT IS THE SESSION.** `[MEASURED]` `objdump -p goldeneye.exe.vr329`: `openxr_loader.dll` named, **`19`** `xr*` import entries -- `328`'s twelve plus **`xrPollEvent`, `xrBeginSession`, `xrEndSession`, `xrRequestExitSession`, `xrWaitFrame`, `xrBeginFrame`, `xrEndFrame`**, each present **once**. **`xrWaitFrame` IS NOW IN goldeneye.exe** ◄◄ |
| `5` | **`K-8` LANDS.** The plain build links, **no log line names `openxr`**, seven DLLs, **`0`** `xr*` entries, and `xrWaitFrame`/`xrBeginFrame`/`xrEndFrame` are each `0` by name. The loop is gated |
| `6` | ►► **AND IT IS STILL NOT `K-3`. NO BINARY BUILT THIS SESSION HAS BEEN LAUNCHED.** `GETV_XR_KILL=1` has never executed. Whether `xrWaitFrame` BLOCKS in the game process is **exactly as open as it was in `322`** ◄◄ |
| `7` | **`K-6` IS PARKED** on the owner's call and was not taken. **`K-9` therefore has no baseline. THAT IS A NAMED DEPENDENCY, NOT A HOLE** |

---

## 1 -- **THE THREE FORKS, AND EACH ONE CHANGES WHAT A FUTURE RESULT MAY BE READ TO MEAN**

`PLAN-329-FRAMELOOP` section `4` put three questions to the owner before a line was typed. All
three were answered, and **the answers are in the source and in the instrument's own output**, not
only in a doc.

| fork | answer | what it costs, and what it buys |
|---|---|---|
| **`A2`** | **`N = 300`, warm-up `30`**, per-iteration body byte-identical to `ge_s3_armA` | `600` frames at the measured `11.1111 ms` is `6.7 s` inside **one** `gePortRenderDisplayList()` call, past the `~5 s` point at which Windows ghosts a top-level window that has not pumped. The standalone arm's window was **never shown** and never pumped `WM_` messages; the game's is shown, foreground, and owned by the thread the loop stands on. **A CONDITION THAT CHANGES AT SECOND `5` OF A `6.7 s` MEASUREMENT WOULD BE SCORED AS `xrWaitFrame`'s BEHAVIOUR.** `A2` buys `270` scored frames instead of `570` and spends nothing else |
| **`A3` REFUSED** | no `SDL_PumpEvents()` in the loop | `PLAN-326` section `5`: *"`ge_s3_armA`'s shape, unchanged, because a re-tuned arm is not a comparison."* **LENGTH IS A PARAMETER; THE BODY IS THE SHAPE.** The deviation is printed by the instrument itself so it cannot shrink into someone's memory |
| **`B1`** | **NO SWAPCHAINS** | All four prior `xrWaitFrame` measurements (`322`, `324` desk, `324` worn, `325`) had **two swapchains created and untouched**. This arm has none. **SO THE READING IS ASYMMETRIC, AND IT IS PRE-REGISTERED IN THE SOURCE:** a BLOCKING result is decisive and `D-X3` survives; **A NON-BLOCKING RESULT IS `K-3 NEITHER`, IT MANDATES `B2`, AND IT IS NOT A KILL** |
| **`C2`** | stdout **and** `getv_xrkill_report.txt` | `327` lost `K-2`'s `GETV_BUDGET`, `ge_pace_wait_ms` and `ge_pace_sleeps` to there being no visible console at the chair. A `3.3 s` freeze that produces nothing readable is worse than no instrument |

**`PLAN-322-X3` SECTION `6` ITEM `1` -- *"a non-blocking `xrWaitFrame` kills `D-X3` outright"* --
WAS WRITTEN ABOUT AN ARM THAT HAD SWAPCHAINS, AND IT DOES NOT TRANSFER TO ONE THAT DOES NOT.**
Writing that down **before** the arm was built is the only reason the cheap arm was safe to
propose, and the instrument prints it in its own verdict rather than leaving it in a plan.

---

## 2 -- ►► **THE FINDING NOBODY WENT LOOKING FOR: `xrEndSession` HAS NEVER BEEN MEASURED TO SUCCEED IN THIS PROJECT** ◄◄

`[MEASURED]` `329`, reading `repo\xr\gevr_xr_slice2.c:351-360`, `ge_s2_teardown()`:

    if (ge_s2_begun) {
        xrEndSession(ge_xr_session);
        ge_s2_begun = 0;
        printf("[getv][vr] session ended.\n");
    }

**THE RESULT IS DISCARDED AND THE LINE PRINTS ANYWAY.** `session ended.` at the foot of
`gevr_xr_slice2_report.txt`, `slice3`, `slice4` and `slice5` is a `printf`, **not a measurement**.
The spec makes `xrEndSession` legal only from `XR_SESSION_STATE_STOPPING`; a session still
`RUNNING`, `SYNCHRONIZED` or `VISIBLE` returns `XR_ERROR_SESSION_NOT_STOPPING`, **and every one of
those runs would have looked exactly like this.**

**AND `gevr_xr.c`'s OWN TEARDOWN WAS NOT EVEN THAT.** `geVrXrEndSession()` called
`xrDestroySession` and nothing else -- correct for slice 1, which never began a session, and
**wrong the moment `xrBeginSession` entered the file**: it would abandon a RUNNING session to the
runtime in a process that then keeps playing GoldenEye for another hour.

**THIS IS NOT FILED AND IT IS NOT A HOLE** (`301`; the wrong-fix count stays **FIVE**). It is a
gap in the standalone slices' evidence, found by reading them before writing against them.
`geVrXrSessionStop()` now **requests the exit, pumps to `STOPPING` under a bounded budget, and
prints `xrEndSession`'s result BY NAME together with the state it was called from** -- so the
first run of this instrument takes a measurement this project has never had, whichever way it
goes.

---

## 3 -- **WHAT WAS TYPED, AND IT IS THREE FILES AND `+602 / -0`**

| file | `+` | edit |
|---|---|---|
| `getv/port/src/gevr_xr.h` | `60` | four declarations -- `geVrXrSessionStart`, `geVrXrFrameLoop`, `geVrXrSessionStop`, `geVrXrFrameKill` -- and the block comment carrying `A2`, `B1` and section `2`'s finding |
| `getv/port/src/gevr_xr.c` | `532` | the four LIVE implementations inside the existing `GEVR_XR_LIVE` guard, four inert stubs, and `geVrXrEndSession()` gaining `if (ge_xr_begun) geVrXrSessionStop();` |
| `getv/port/src/port_render.c` | `10` | **one call**, `geVrXrFrameKill();`, inside `328`'s existing `else` branch after the `SESSION LIVE` line, plus its comment |

**`port_render.c` GAINED NO KNOB, NO INCLUDE, AND THE BLOCK DID NOT MOVE.** It is still before the
`GETV_BUDGET` bracket, which matters more now than it did in `328`: the loop freezes the thread
for seconds, and **the FOLLOWING frame's pacing and budget numbers are contaminated by that freeze
and ARE NOT A FINDING ABOUT `xrWaitFrame`.** That sentence is in the source, at the call site,
where a reader will hit it.

**THE PER-ITERATION BODY IS `ge_s3_armA`'s, MOVED NOT REWRITTEN** (`gevr_xr_slice3.c:150-204`):
non-sleeping pump, `xrWaitFrame` -> QPC -> `xrBeginFrame` with `XR_FRAME_DISCARDED` **counted and
never routed around** -> `xrEndFrame(layerCount 0, layers NULL)`. The scoring is `ge_s3_score`'s
distribution with `K-3`'s three-way verdict in place of `X3-1`'s.

**`build_windows.ps1`, `getv/patches` AND `gfx_sdl2.c` UNTOUCHED.** `328` measured the link line
already correct and `K-7` is the prediction that it stayed correct. It did.

**THE STANDING LINE HELD, AND IT WAS UNDER MORE PRESSURE THAN IN `328`.** This file now holds a
live `xrWaitFrame` and a measured `predictedDisplayPeriod` in one function -- **the interlock's two
inputs.** `[MEASURED]` `geVrXrPaceArm`, `geVrXrPacingOwned` and `sync_framerate` appear in the diff
**only inside comments and printed strings that say they are not called.** There is no call.
**THE HANDOVER IS NOT STARTED.**

---

## 4 -- **THE ARITHMETIC, AND IT CORROBORATES THE ONE FORK NOBODY ARGUED ABOUT**

| binary | md5 | length | vs its `328` twin |
|---|---|---|---|
| `goldeneye.exe.plain328` | `B449BAD55A9B25B8F0D26A6515422EDA` | `18,075,450` | -- |
| `goldeneye.exe.plain329` | `037EDBD61D293C1CA0419418927715D7` | `18,075,663` | **`+213`** |
| `goldeneye.exe.vr328` | `65ED4041C9C7818B921157BE5CC4727D` | `18,085,678` | -- |
| `goldeneye.exe.vr329` | `70BF2580239CD6B7C402C063D89B976F` | `18,101,808` | **`+16,130`** |

`[ARITHMETIC]` **A `+602`-LINE DIFF COST THE PLAIN BINARY `213` BYTES.** That is the owner's
"arrays inside `GEVR_XR_LIVE` only" answer, visible: the `12,000` bytes of loop arrays, the timing,
the pump, the scoring and the report are **all** behind the guard, and the plain build took four
inert stubs and one call. **AND THE SIZE STILL SCORES NOTHING** -- `328` section `2` ruled it
insufficient while it happened to point the right way, and `K-7` was scored on the import table
and on nothing else.

---

## 5 -- ►► **WHAT THIS SESSION DOES NOT CLAIM, AND THE LIST IS THE IMPORTANT PART** ◄◄

1. **IT DOES NOT ANSWER `D-X3-KILL`.** `K-7` and `K-8` are link facts read from `objdump`. **NO
   BINARY BUILT THIS SESSION HAS BEEN LAUNCHED**, with or without the knob, with or without a
   runtime. **`GETV_XR_KILL=1` HAS STILL NEVER EXECUTED**, and it is still unknown whether
   `xrCreateSession` succeeds on the game's own context -- which is the first thing the arm would
   find out.
2. **IT DOES NOT KNOW WHETHER THE SESSION EVER REACHES `READY` IN THE GAME PROCESS.**
   `geVrXrSessionStart()` has a `5 s` budget and a refusal written for exhausting it. Nothing has
   tested which way that goes.
3. **THE REPORT PATH IS VERIFIED BY READING, NOT BY A RUN.** FORK `C2`'s `fopen` is the first
   statement of `geVrXrFrameKill()`, before any `xr*` call, so every reach writes the file
   including a refusal. **BUT THE FUNCTION IS REACHED ONLY AFTER `GETV_VR=1`, `GETV_XR_KILL=1`,
   SteamVR up and the HMD awake -- AND ANY RUN THAT SATISFIES ALL OF THAT RUNS THE LOOP AND PRINTS
   A `K-3` VERDICT.** There is no smaller arm: the warm-up clamp keeps at least two scored frames
   on purpose. **A DESK RUN IS STILL THAT RUN.** `RUN-SHEET-329` section `2` states this rather
   than working around it.
4. **`K-6` IS PARKED** (owner, `329`) and **`K-9` has no baseline until it is taken.** A named
   dependency, not a hole.
5. **`B2` WAS NOT BUILT.** `[MEASURED]` `19` imports, not `23`; no swapchain name is in the table.
6. `H19` open. `U-28` reserved unfiled. `H24` still blinds every `WS=1` arm. **NOTHING NEW FILED.
   WRONG FILED FIXES STAY FIVE.**

---

## 6 -- **ARTIFACTS** (gitignored logs OK)

`repo\xr\syntax_329_gevr_xr.log` (`0` bytes), `build_329_vr.log`, `imports_329_vr.log`,
`build_329_plain.log`, `imports_329_plain.log`.
Binaries preserved: `goldeneye.exe.vr329`, `goldeneye.exe.plain329`; `goldeneye.exe` is the plain
binary again. `.vr328`, `.plain328`, `.vr326`, `.plain326` and `.pre326` untouched.

**NOTHING STAGED, COMMITTED, BRANCHED, MERGED, TAGGED OR PUSHED.**

`169` NEXT ID = `U-28`. NEXT INSTRUMENT HOLE = `H25`.
