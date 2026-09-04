# NEXT SESSION PROMPT — `290` — **STAGE 5, THE POSE SPINE. THIS IS VR WORK, NOT BUG WORK.**

**EFFORT LEVEL: HIGH.** New source in an area this project has never written in, one build, and
arms that need **no headset**. Not a diagnosis session.

**WHY THIS AND NOT MORE TROUBLESHOOTING — SAID PLAINLY, BECAUSE IT IS THE SESSION LEAD'S
CORRECTION AND IT IS RIGHT.** `289` was booked HIGH and spent on diagnosis: it killed `288`'s
standing candidate, found a masked zero, and re-diagnosed a five-session-old complaint. **All true,
none of it stereo.** The mission is *build GoldenEye 007 VR from source*, and **STEREO HAS NOT BEEN
STARTED.** `258` is the route; stages 0-4 are done and worn (`271`/`272`/`273` the budget and
baseline, `277` the clock). **STAGE 5 IS NEXT ON THAT ROUTE AND IT IS THE ONE THING THAT MAKES
STEREO CHEAP INSTEAD OF EXPENSIVE.** Everything else is parked below, with what it owes written
down.

---

## PASTE THIS

Read `repo\docs\00-STATE.md` and `repo\docs\258-THE-ROUTE-THE-ENGINE-ALREADY-RENDERS-N-VIEWS.md` §1 and STAGE 5, then write `RUN-SHEET-290.md` and execute it. Same rules as always. See the "Operation not permitted" warning in §6 — reads from the bridge are not free; `git log`, `git show` and `git diff <path>` are safe, `git status` and `git add` are NOT.

**THE TASK IS `258` STAGE 5 — THE POSE SPINE — AND NOTHING ELSE.** Head, both hands and a body proxy become **game-side state, written BEFORE the tick and readable by game code**. That is `P6`: THE SIM OWNS THE POSE, the renderer only consumes it. **NO HARDWARE IS REQUIRED TO BUILD OR TO PROVE IT** — feed it identity, then a synthetic path, exactly the way `port_input.c` already fakes a pad with `GETV_MOUSE_SELFTEST`.

**WHY IT COMES BEFORE STEREO, AND THIS IS `258`'s LOAD-BEARING ORDERING CLAIM:** stereo needs a per-eye **view**, and **the eye TRANSLATION lives in the VIEW matrix** (`255` §1 — projection-only is a frustum shift, NOT separation). **Build stereo first and it consumes a renderer-side pose; then `P6` arrives and the whole eye path is reworked.** That is the *"hack it now, fix it later"* the standing clause forbids. **Built in this order, `P6` costs nothing extra and STAGE 6 consumes it.** `194` is the receipt: one missing term, four faults.

**WHAT `290` MUST NOT DO.** No OpenXR, no `gevr_xr.c`, no head tracking, no hand aim, no vignette, no HUD quad, no mirror — `258` STAGE 5 lists those as NOT in this stage and STAGE 6 as a separate build. **Do not set `getPlayerCount()` to 2** (`258` §1.5: 173 refs, 35 files, and it is GAME LOGIC — dual-wield gating and glass-buffer sizing). **Do not put the eye loop in this session.** **And do not re-open the vanishing props or the mouse turn — both are parked below with their next arms already named.**

**THE CONSTRAINTS THAT DECIDE THE SHAPE, AND A PLAN THAT DOES NOT SATISFY THEM IS UNFINISHED:** `P6` the SIM owns the pose · `P4` pay the structural cost ONCE, never per-frame · `P9` the sim is authoritative for position · `P7` two hands and body are ONE articulated system, so the spine must be able to hold all three from the start even if only the head is driven · `P3` resolution is one runtime variable · `P1` never a literal rate.

**IT NEEDS AN INSTRUMENT THAT CAN FAIL, AND IT NEEDS IT BEFORE THE BUILD (rule `15`, `P5`).** A pose that is written and never read is invisible; a pose read at the wrong point in the frame is `267`/`271`/`272`'s bracket error in a new place. **State what it prints if pointed at the wrong thing BEFORE the run.** The synthetic path is the falsifier: a known trajectory in, the same trajectory out, **and a deliberate off-by-one-tick that the instrument must catch.** Opt-in, inert when unset, a banner that says it took, and it must never ship on.

**READ THE SEAM BEFORE WRITING ANYTHING.** `lvlRender` (`vendor/ge-decomp/src/game/lv.c:762-796`) already loops over views with per-view viewport, FOV, aspect and projection; `viSetupCurrentPlayerView` (`fr.c:696`) is the SINGLE projection build site and already carries a `GE_PORT_NATIVE` block. **Row-vector vs column-vector and the negative-yaw trap are in `00-STATE` §7 — read them before any matrix is written.**

**EVERY COMMAND BLOCK CARRIES ALL OF THESE, because a block that omits a knob silently restores its default:**
`GETV_SLOTFREE=1 GETV_VSYNC=1 GETV_FPS=panel GETV_SIMHZ=query GETV_SIMDIV=1 GETV_WIDESCREEN=0 GETV_ROOMSCISSOR=0 GETV_WINDOW=2560x1369`
**`GETV_ROOMSCISSOR=0` is a FALSIFIER, not a setting — if `290` is not looking at room clipping, consider `1` and say which you chose and why.** `GETV_FPS=panel` queried 120 Hz from SDL on both `289` J-arms; the session lead also runs a 180 Hz desk, so never hardcode a rate. **Gate 2 is `ours: x=367.333` and it MANDATES the broken front-end menu text — that is OPEN item 2, by construction, not a regression, and moving to `1825x1369` would print `ours: x=0` and silently break the gate** (rule `17`).

**CHECK BEFORE YOU START:** `tools/fetch-thirdparty.sh verify` must read `15/15` (it did after `289`'s build, and `289` touched nothing under `getv/port/**`), and **`289`'s THREE COMMITS must be in** — `vendor/ge-decomp` staged BY EXPLICIT PATH LIST at `168 insertions / 11 deletions across three files`, `goldeneye-native` for the harness, and `GoldenEyeVR` for the docs. **If the decomp is uncommitted, say so first.**

**A STANDING LESSON `289` ADDED, AND IT APPLIES TO EVERY COUNTER THIS PROJECT WILL EVER READ: A ZERO IN A TEST THAT SITS DOWNSTREAM OF A TEST REJECTING MOST OF ITS INPUT IS A MASKED ZERO, NOT AN EXONERATION.** `dist` read 0 three times and reads 17,124 the moment the test above it is neutralised. **Read the ORDER a counter sits in, not just the counter.**

**DEAD, DO NOT REOPEN:** `getROOMID_isRendered` as the vanishing-prop mechanism (`289` R2) · the per-room rectangle (ARM 7, `box=0` in 8b) · `vsync` as the smoothness carrier (`287` 4E, `288` J1/J2) · **`GETV_SIMHZ` as the smoothness carrier (`289` S1/S2, cleared on the NUMBER and on the WEAR)** · ARM 4E, ARM 5, ARM 7, R2 · everything in §5 of `00-STATE`.

**STILL OWED, NOW TEN SESSIONS:** all of `277` §9 · `278` §6's INFERRED hoist-1 read · `279` §5's amount arm · `280` §7.3's black-wall dump · `274` §7's CONTAMINATED gate · `287` ARM 6, the wear pass, STILL NEVER RUN · `289` R2's missing `dlgrab`.

Start by reading `00-STATE` and `258`. Do not plan past the first instrument.

---

## THE TWO PARKED ITEMS, WITH THEIR NEXT ARMS ALREADY NAMED

**PARKED IS NOT DROPPED.** Both have a next step that is written down and free, so neither needs a
session of its own to be resumed.

### 1. THE MOUSE TURN SHAPE — **IT IS `258` STAGE 7 (AIM, `P8`), NOT A BUG QUEUE ITEM**
`289` §6: `[REPORTED]` MOUSE-ONLY, not the controller; reproduced at cap 60 and better at higher
rates; **it is the SHAPE of the motion**, arcing *"almost like a car"* out of a straight run, not
judder. **Five sessions of pacing instruments came back clean because the fault is not in them.**
`289` §6.2 reads four `[MEASURED]` properties the mouse path has and the pad does not — a per-frame
accumulator with no timestep, a cap expressed in FRAMES, a mouse-only 20% deadzone FLOOR, and a map
that saturates at 21 counts. **No cause is named and no fix is proposed.**
**THE ARM IS FREE AND THE INSTRUMENT ALREADY EXISTS, UNRUN: `GETV_MOUSE_SELFTEST=<counts>`**
(`port_input.c:961`) — synthetic constant mouse movement per frame, so degrees-turned-per-count can
be measured against a frame rate **with no hand on the mouse.** **And `00-STATE` OPEN item 9's
crosshair auto-centring is a SECOND owner report about mouse control, already filed under `P8`.**
**Rule `16` says two reports in the same subsystem is a ranking signal — and STAGE 7 is where it is
ranked. It may run beside STAGE 6 (`258` STAGE 7), so it is not blocked by anything here.**

### 2. THE VANISHING PROPS — **FOUR OF SIX TESTS ELIMINATED, TWO NEVER TESTED**
`289` §4.3: `room` eliminated, `box` eliminated, `dist` removes nothing in the shipping config, and
**the five view planes are UNREACHABLE with `PROPCULLBOX` on, so they remove zero props in the
picture actually being looked at.** What is left is **`fog` (12,257) and `occl` (2,241)**, neither
ever tested — and **the load-bearing claim is now `288`'s source read that *"`posIsOnScreen` is the
ONLY place that decides a prop is not drawn"*, which is not a measurement.**
**AND `fog=12,257` IS BYTE-IDENTICAL ACROSS TWO SESSIONS AND TWO ROUTES** while every other counter
moved — **so a large part of these cumulative counts is deterministic boot/load, and the report has
no windowing at all.** **The next instrument is windowing, not another knob.**
**This item does touch stereo eventually** (`288` §8a: the cull volume must be derived from the
RENDERED frustum, in stereo the UNION of both eyes, never a stored constant — `P2`/`P3`) — **but it
is a flat-game rendering bug today and it is not blocking STAGE 5.**

---

## WHY HIGH EFFORT

- **A new subsystem, not an edit.** The pose spine is game-side state with an ownership rule
  (`P6`) attached; where it is written relative to the tick is the whole design.
- **It must be provable without hardware**, which means a synthetic driver and an instrument with a
  written failure mode — the same discipline `287` used for `GETV_PACEHIST` and `289` for the
  cullwhy harness.
- **One binary, a string gate, and a commit in three repos**, with the decomp's explicit-path trap
  on one of them.
- **It is the ordering decision the whole VR build rests on.** Get it wrong and STAGE 6 is rework.
