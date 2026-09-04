# 291 — THE POSE SPINE IS WORN GREEN. `258` STAGE 5 IS DONE, `P6` HOLDS ON THE LIVE PATH.

**2026-09-01, session `291`. FIRST VR-WORK RESULT.** `290` wrote and offline-validated the pose
spine; `291` built it on the main PC and ran its three arms. **All green.** The sim owns the pose,
it is written before the tick, and it is read back fresh at tick time — `P6`/`P9` on the live path,
not in a harness. STAGE 6 (stereo) may now consume `gePoseCurrent()`.

**Rule `1`: the build and the run are the owner's, main PC. The bridge confirmed the commits, re-ran
the offline falsifier (`10/10`) and `verify` (`15/15`), and read the run logs.** No code changed this
session — this is a RESULT, not a patch. The only edit is docs (`00-STATE` currency + WORKS row +
this file + `NEXT-SESSION-PROMPT-292`).

---

## §1 — THE PRECONDITIONS, RE-CONFIRMED ON THE BRIDGE (safe reads only)

- **`290`'s three commits are in.** `GoldenEyeVR` `8a1adca`, `goldeneye-native` `868776a`,
  `vendor/ge-decomp` `4014d36a`. `git show --stat 4014d36a` = **`318 insertions, 0 deletions, 3
  files`** (`lv.c 12+`, `posespine.c 237+`, `posespine.h 69+`) — the exact shape `00-STATE` names.
  The two hooks are on disk: `gePortPoseBeginFrame()` at `lv.c:760` (top of `lvlRender`),
  `gePortPoseProbeAtTick()` at `lv.c:844` (immediately before `propsTick()`).
- **Offline falsifier `10/10`**, `-Wall -Wextra -Werror` clean, compiling the REAL `posespine.c`.
  Scenarios 4 (wrong bracket) and 5 (mode 2) both make it say FAIL — it is an instrument.
- **`verify` `15/15`.** `290` touched nothing under `getv/port/**`; free standing gate, no regen owed.

## §2 — THE THREE ARMS. `[MEASURED]`, ONE FRESH EXE (`00:06`, 18,039,699 BYTES).

Binary gate: all five strings FOUND (`posetest] ON`, `[getv][pose] GETV_POSE_SELFTEST`,
`posetest] seq=`, `SUMMARY mode=`, `VERDICT`). Every arm ran the full knob set with `GETV_SIMDIV=1`
holding (`props interpolated 0`, zero `simulation held to`), panel queried at 120 Hz, clean
`game_exit requested`. Gate 2 `ours: x=367.333` present in all three (OPEN item 2, mandated).

| arm | log | result |
|---|---|---|
| **A1 identity** | `run_290_A1_identity.log` | **INERT** — zero `[getv][posetest]` lines, `props interpolated 0`, `ours: x=367.333`, clean exit. Opt-in confirmed; ships off. |
| **A2 round-trip** | `run_290_A2_posetest1.log` | **`SUMMARY mode=1 frames=7180 stale=0 maxerr=0.000 — VERDICT PASS`.** Every sampled frame `lag=0 err=0.000 OK`; `read.x == expect.x` exactly (e.g. `seq=7140 read.x=71400.000 expect.x=71400.000`). **The pose is written before the tick and read intact at tick time — `P6` on the live path.** |
| **A3 self-falsify** | `run_290_A3_posetest2_selffalsify.log` | **`SUMMARY mode=2 frames=6499 stale=6499 — VERDICT PASS (detector fired)`.** `lag=1` on every one of the sampled frames, `err` = exactly one step (`read.x=64790 expect.x=64800`). **The freshness gate CAN fire.** |

**Why all three matter, not just A2:** A1 proves silence when off, A3 proves the detector is not
blind, so A2 — sitting between them — proves the pose actually round-tripped fresh, and not that a
dead check rubber-stamped it. An instrument that cannot be made to say FAIL is not an instrument
(`P5`, rule `15`); A1 and A3 rule that out around A2.

**A2 needed no repair** — §7's failure branch (`lag=1 STALE` = seam bracketed after the tick;
large `err lag=0` = written-but-never-read) did not fire. The seam at `lv.c:760`/`:844` is correct.

## §3 — WHAT THIS UNBLOCKS, AND WHAT IT DOES NOT

**Unblocks STAGE 6 (stereo).** `258`'s load-bearing ordering claim holds: a sim-owned pose exists
BEFORE the eye loop, so STAGE 6 nests an eye loop in `lvlRender`'s per-player body, takes its per-eye
view from `gePoseCurrent()`, and replaces the projection at `viSetupCurrentPlayerView` (`fr.c:696`).
Confirmed read-only this session: the per-player body (`lv.c:783-812`) carries
`DL = viSetupCurrentPlayerView(DL)` and an existing `GE_PORT_NATIVE` block beside it — the seam is real.

**Does NOT touch:** `getPlayerCount()` (still 1, `258` §1.5), the vanishing props, the mouse turn,
or anything in `00-STATE` §5. None reopened.

## §4 — STILL OWED, CARRIED FORWARD (unchanged by 291)

All of `277` §9 · `278` §6's INFERRED hoist-1 read · `279` §5's amount arm · `280` §7.3's black-wall
dump · `274` §7's CONTAMINATED gate · `287` ARM 6 the wear pass, STILL NEVER RUN · `289` R2's missing
`dlgrab`. **291 opened none of these and closed none of them.**
