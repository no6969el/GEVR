# `325` -- **THE INTERLOCK REFUSES `90` AGAINST `60`. AND A DESK RUN REACHED `VISIBLE`, WHICH `324` SAID IT WOULD NOT**

**2026-09-05.** Owner green-light mid-session: FORK 1 = `B`, FORK 2 = `A`, interlock and refuse
path first, stop at the smallest build that can score `I-1`. **One compile and one run, both the
owner's, on the main PC.** `[MEASURED]` `repo\xr\gevr_xr_slice5_report.txt`, `16:17`, **`EXIT 0`**,
conditions sidecar `gevr_xr_slice5_conditions.txt` -- **`DESK`**, SteamVR up, dashboard dismissed,
no other OpenXR client. Harness md5 `9D70A45F980C5EE2A55260AA1DD8F37F`.

---

## 0 -- ONE TABLE

| | |
|---|---|
| `1` | **`I-1` LANDS, BOTH HALVES.** `PART 1` `T1` and the live `I-1b` both printed `CONTAMINATED` at `90.0001 Hz` against `ge_pace_framerate 60`, named both numbers, and **REFUSED THE HANDOVER** |
| `2` | **`I-2` LANDS, BOTH HALVES.** `90.0001` against a pinned `90` AGREES at `0.0001%`, inside the pre-registered `0.500%` band |
| `3` | **`I-1c` LANDS.** Armed with `60` then re-armed with `90`, the latch read `0` then `0` and printed once. **A REFUSAL IS FINAL FOR THE PROCESS** |
| `4` | **`I-1d` LANDS.** `geVrXrSessionLive()` `1` and `geVrXrPacingOwned()` `0` **at the same instant** -- the refuse path, with a live session |
| `5` | **`I-4` LANDS.** `90.0001 / 60 = 1.500002` against `274`'s MEASURED `1.500x`, inside the pre-registered `0.010` |
| `6` | **`PART 1` PASSED `6` OF `6`** with no runtime involved, including both edges of the band (`0.4%` AGREE, `0.6%` REFUSE) |
| `7` | **THE X2 GATES AND `X3-1`, `X3-2`, `X3-4` ALL RE-PASSED** from the tracked files. `0` of `600` `XR_FRAME_DISCARDED` |
| `8` | ►► **AND A DESK RUN REACHED `VISIBLE`. `324`'s `V-desk` DID NOT REPRODUCE A THIRD TIME.** See section `2` ◄◄ |
| `9` | **`I-3` AND `D-X3-KILL` ARE UNSCORED AND OWED, IN-GAME.** No handover exists. `port_render.c` is untouched. Wrong filed fixes stay **FIVE** |

---

## 1 -- **WHAT WAS BUILT, AND WHAT WAS DELIBERATELY NOT**

**PRODUCT, AND IT IS THE FIRST PRODUCT EDIT IN MANY SESSIONS:** `gevr_xr.h` `+57 / -0`,
`gevr_xr.c` `+104 / -0`. Three functions -- `geVrXrPaceInterlock()` (pure), `geVrXrPaceArm()`
(the latch), `geVrXrPacingOwned()` (FORK 2 = `A`'s caller-side gate). **`gevr_xr.c` NO LONGER
READS `2DE74D75...`; the gate `319`-`324` all printed is retired on the owner's green-light and
`RUN-SHEET-325` section 1.1 says so in its own words.**

**THEY SIT OUTSIDE THE `GEVR_XR_LIVE` GUARD ON PURPOSE.** The decision is two numbers and no
handles, so it compiles in every build including the inert game build, and `PART 1` scores it
with SteamVR not even required. **The game binary gains three functions it never calls, so THE
BEHAVIOUR IS UNCHANGED AND THE BYTES ARE NOT** -- stated rather than glossed, and byte-identity
must not be claimed for that file again until it is re-measured.

**INSTRUMENT:** `repo\xr\gevr_xr_slice5.c`, `423` lines, `?? ` and gitignored `.exe`/report.
`ge_s3_armA` and `ge_s3_score` byte-identical to `323`/`324` -- ARM A is present for ONE reason,
to produce a MEASURED period to feed the interlock, and it was not re-tuned.

**NOT BUILT, AND ALL OF IT STILL OWED:** no `port_render.c` line, no `build_windows.ps1` edit,
no FORK 1 = `B` existence check, no `GEVR_XR_HAVE_OPENXR` for the game, no patch edit, no
`gfx_sdl2.c`, **no handover of any kind. NOTHING IN THIS RUN PACED ANYTHING.** No `H19`, no
`SHAPE A`/`B`, no `U-28` filed, no `GX-0`.

### 1.1 -- **THE PART 1 DISCLOSURE, KEPT WHERE IT CAN BE READ**

`RUN-SHEET-325` section 1.3: **the six `PART 1` cases were exercised on a scratch copy of the
three pure functions in the bridge VM before the sheet was handed over** -- not the Windows
build, not the harness, nothing under `F:\`, nothing on the main PC. **SO `PART 1` ON WINDOWS IS
A REPRODUCTION AND IS NOT WRITTEN UP AS A FIRST MEASUREMENT.** `PART 2` was genuinely unseen.

**THAT DESK CHECK EARNED ITS KEEP BY FAILING.** The first `I-1c` check read `1` then `1` and
looked like a broken latch. **THE BUG WAS IN THE CHECK:** both `geVrXrPaceArm()` calls sat in one
`printf` argument list, where C leaves evaluation order unspecified, and gcc ran the agreeable one
first. `gevr_xr_slice5.c` uses two statements and now carries a comment saying why.

---

## 2 -- ►► **THE FINDING NOBODY ASKED FOR: A `DESK` RUN WENT `VISIBLE`** ◄◄

`[MEASURED]` `gevr_xr_slice5_report.txt`, ARM A, on a run whose sidecar says **`DESK`**:

```
[getv][vr] X3 state READY -> SYNCHRONIZED at frame 1
[getv][vr] X3 state SYNCHRONIZED -> VISIBLE at frame 1
[getv][vr] X3 state VISIBLE -> SYNCHRONIZED at frame 88
shouldRender  58 of 570 frames true
```

**AGAINST THE TWO DESK RUNS BEFORE IT:** `322` `19:11` -- `READY -> SYNCHRONIZED` and never
moved, `shouldRender` `0` of `570`. `324a` DESK -- the same, `0` of `570`. **`324` section 0 row
`1` says `V-desk LANDS`. IT DID NOT LAND A THIRD TIME.**

**AND THE ARITHMETIC TIES THE TWO NUMBERS TOGETHER EXACTLY.** The warm-up is `30` frames and
`VISIBLE` ended at frame `88`. `[ARITHMETIC]` `88 - 30 = 58`, and `shouldRender` was true on
**exactly `58`** scored frames. **ON THIS RUN `shouldRender` WAS TRUE IF AND ONLY IF THE SESSION
WAS `VISIBLE`, frame for frame.** That relationship is new and it is the cleanest thing in the
report.

**WHAT SURVIVES OF `324`:** worn has reached `VISIBLE` on both occasions it was tried. **WHAT
DOES NOT:** *desk locks `322`-like behaviour*. **DESK IS NOT SUFFICIENT TO PREVENT `VISIBLE`,
and the outside-tree factor `324` named is therefore NOT THE WHOLE FACTOR.**

**WHAT IS NOT CLAIMED HERE.** No cause is offered. A headset that had just been handled, a
proximity sensor, a compositor focus that lapses after roughly a second -- `[ARITHMETIC]`
`88` frames is `0.978 s` -- are all CANDIDATES and none was measured. **`324` retracted a causal
claim for exactly this reason and a third desk run is not a theory.** **NOT FILED, NOT A HOLE**
(`301` section 0). **WRONG FILED FIXES STAY AT FIVE.**

**THE STANDING LABEL RULE NEEDS THE OTHER HALF:** `00-STATE` said to label XR timing taken while
`VISIBLE` as worn-condition unless desk-controlled. **`VISIBLE` NOW HAPPENS ON A DESK TOO, SO
`VISIBLE` NO LONGER IMPLIES WORN.** Label by the sidecar, not by the session state.

### 2.1 -- **AND IT COST THE INTERLOCK'S RESULT NOTHING, WHICH IS ITSELF A DATUM**

`[MEASURED]` period `11.1111 ms` **min AND max, spread `0.0000%`, `90.0001 Hz`** -- the fourth
run in a row to print that number, now across `322` desk, `324a` desk, `324b` worn and a desk run
that spent `88` frames `VISIBLE`. **THE PERIOD IS INDIFFERENT TO ALL OF IT.** `X3-1` landed again
(mean interval `11.1201 ms`; `min 10.9870`, `max 14.4042`, `p50 11.1121`, `p95 11.1393`,
`p99 11.1576`), `X3-2` landed again, `0` of `600` discarded, wall clock `6338.47 ms` against
`6333.33 ms` of ideal periods. **Every number the interlock consumes was stable while the thing
`324` was about was not.**

---

## 3 -- **WHAT THE INTERLOCK ACTUALLY PRINTED, ONCE, VERBATIM**

`[MEASURED]`, the live `I-1b` line:

```
[getv][vr][pace] CONTAMINATED -- xrWaitFrame paces at 90.0001 Hz (period 11.1111 ms) and
ge_pace_framerate claims 60 Hz. That is 1.500002x. gePortSimHzResolve() has already cached the
60 on the first game frame (frametiming.c:126,233) and cannot be told otherwise. HANDOVER
REFUSED: sync_framerate_with_timer() KEEPS THE CLOCK and the game paces as it does today. Pin
GETV_FPS=90 to agree, or accept the desktop pacer. Band is 0.500% (PLAN-325-DX3 section 4).
                 AND THIS IS `274`'s FAULT BY THE NUMBERS -- 1.500002x against the 1.500x world
`274` MEASURED, through the door `277` never had to close.
```

**THE `274` CLAUSE IS CONDITIONAL AND THAT IS DELIBERATE.** `T6` refused a `1.006x` disagreement
and did NOT print it: **the interlock guards DISAGREEMENT, and `274` is the precedent for one
particular disagreement, named only when the numbers are that one.** A refusal dressed in a
fault it does not have is how a report starts lying to its own reader.

---

## 4 -- **WHAT THIS DOES NOT CLAIM**

- **NOT that `D-X3` works.** No handover exists. `sync_framerate_with_timer()` still owns the
  clock in every binary, unchanged.
- **NOT that a refusal costs the game nothing** -- that is `I-3`, it needs the GAME binary and a
  `GETV_BUDGET` comparison, and **THERE IS NO GAME IN THIS BINARY. OWED.**
- **NOT that `xrWaitFrame` blocks in the game.** `D-X3-KILL` is untouched. Four runs of evidence
  come from a STANDALONE SLICE with its own window and event pump; **in the game the context, the
  SDL pump and the swap belong to someone else, and `324` -- and now section `2` -- are this
  project's own proof that environment decides outcomes on a byte-identical binary. OWED,
  IN-GAME, AND IT NEEDS THE LOADER FIRST.**
- **NOT a stereo, pixel or comfort claim.** Nothing was drawn and nothing was submitted.
- **NOT `H19` fixed.** Not `U-28` filed. **WRONG FILED FIXES STAY FIVE.**

---

## 5 -- **ARTIFACTS** (gitignored reports OK)

- `repo/xr/gevr_xr_slice5_report.txt` + `gevr_xr_slice5_conditions.txt` (`DESK`, `16:17`)
- `repo/docs/PLAN-325-DX3.md` (section `9` records the green-light and what it superseded)
- `repo/docs/RUN-SHEET-325.md` (section `1.1` retires the md5 gate; section `1.3` is the
  `PART 1` disclosure)

`169` NEXT ID = `U-28`. NEXT INSTRUMENT HOLE = `H25`.
