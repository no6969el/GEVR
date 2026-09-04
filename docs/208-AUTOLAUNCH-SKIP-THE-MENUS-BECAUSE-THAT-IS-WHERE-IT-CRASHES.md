# 208 — AUTOLAUNCH STRAIGHT INTO A STAGE. **BUILT, RUN, AND IT NEVER FIRED. INERT PENDING THE RIGHT HOOK.**

**2026-08-25. Tiers per `182`.**

> # ►►►► §5: THE HOOK WAS WRONG AND THE EVIDENCE WAS IN THE SAME FILE. ◄◄◄◄
> **`[MEASURED]` `wfnf=2`: `waitForNextFrame` ran TWICE in the whole session.**
> **`[REPORTED]` the run locked up on the title; no `AUTOLEVEL` line was ever
> printed.** **The mechanism in §2 is sound and UNTESTED; only the placement was
> wrong. THE CODE IS NOW INERT — nothing calls it — and `-AutoLevel` does
> nothing until the hook moves to `viSetFovY`.** See §5.

---

## §1 — WHY THIS AND NOT A FIX

`[REPORTED]`, and it reframed the whole problem: *"The only reason why I wanna
fix it is because it's stopping me from getting into the level, not because I
need to spend time in the menus."*

**`207` had just closed both quick routes:**
- **dynamic VI pacing — BLOCKED by `131`**, in a comment written for this exact
  case: the timing expressions are ABSOLUTE, so changing the divisor mid-run
  reinterprets every VI already counted;
- **a patch guard on the faulting function — BLOCKED by `168` §5's grep**:
  `process_02_position` and `modelAnimReadBitsAsU16Angle` are not reachable.

**So the crash stands. What changes is that it stops being a toll gate.**

> **THIS DOCUMENT CLAIMS NOTHING ABOUT THE CRASH.** `206`'s stack and `207`'s
> cadence finding are untouched and still owed. **A workaround recorded as a
> workaround is not a fix pretending to be one** — and the knob's own launch text
> says so out loud, so a later session cannot mistake it.

---

## §2 — HOW, AND IT NEEDED NO NEW GAME SYMBOLS

**`[READ]` `168` §5's mandatory grep: `g_StageNum` and `g_MainStageNum` are BOTH
in `patches/externs.h`.**

**`[READ]` `boss.c:647`:**

```c
g_StageNum = g_MainStageNum;
g_MainStageNum = LEVELID_NONE;
```

**and `bossSetLoadedStage()` is nothing but a write to `g_MainStageNum`.**
**`[READ]` `bossMainloop`'s loop is `while (g_MainStageNum < 0 || pendingGfx != 0)`**
(recorded in `ge_vr_route_b.c:416` while chasing something else entirely).
**`LEVELID_NONE` is `-1`, so a non-negative `g_MainStageNum` BREAKS THAT LOOP and
the game's own transition consumes it.**

**AND `waitForNextFrame` — already `RECOMP_PATCH`ed since `131` — IS CALLED FROM
INSIDE THAT LOOP.** So the whole feature is **one assignment from a function we
already own.** Zero new game symbols; `157`'s eight-symbol trap does not apply.

**THE SETTLE DELAY IS THE ONLY REAL RISK.** Queueing a stage into a half-built
pool would be **a crash of our own making stacked on the one being avoided**. So
it fires only once the title is ACTUALLY RUNNING (`g_StageNum == 90`,
`LEVELID_TITLE`) and then only after **120 further frames** — two seconds at 60,
1.3 at 90.

**ONE-SHOT, latched in a FILE-SCOPE global, not a `static`** (`136`: statics in
patch code are not emitted; `48` rule 13: a patch-code static cannot be assumed
zero). **The knob is range-checked HOST-SIDE** — a typo queueing stage 9999 would
be a crash we caused.

---

## §3 — USING IT

**`-AutoLevel 33` — the Dam.** `LEVELID_DAM = 33`, counted from
`LEVELID_STATUE = 22` in `bondconstants.h`. `0` or unset = off, and an unset
build is byte-identical (the latch closes on frame one without touching
anything).

```powershell
.\build.ps1
.\build.ps1
.\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
         -WorldUnitsPerMetre 25 -HandUnitsPerMetre 25 `
         -ViewmodelScale 0.5 -GunOffX 0 -GunOffY 0 -GunOffZ 0 `
         -AimFromHand -MuzzleOrigin -NoCrouch -HudDepth 0.2 `
         -AutoLevel 33
```

**BUILD TWICE — one new `RECOMP_PATCH`-reachable symbol** (`recomp_ge_vr_auto_level`,
`0x8F000168`), `136`.

**CONFIRM IN THE LOG:** `[gevr] AUTOLEVEL: stage queued from the title screen`.

> **IF IT HANGS ON THE TITLE, THE SETTLE DELAY IS TOO SHORT — SAY SO, DO NOT
> RETRY.** A second attempt would queue into the same half-built state. The fix
> is a larger `GEVR_AUTOLEVEL_SETTLE`, and it is one constant.

---

## §4 — WHAT THIS UNBLOCKS

**Every wear test from here stops paying the menu toll** — and the aim work has
been paying it all evening. **`-ViRate 90` is usable again**, which `207` §3c had
reduced to a per-session trade.

**STILL OWED, UNCHANGED:** `207` §3c's real fix (the timebase rebase) or §3c.3's
unasked question — **is there a LOADING flag the patch can already see, so
`chrTick` can be skipped while a load is in flight?** That is a grep, not a
build, and it is smaller than either route.

**AND THE POINT OF THE SESSION IS STILL `B1`** — `193` §2's 0.19-0.61 m muzzle.

---

## §5 — ►►►► THE FAILURE, AND THE HOOK THAT IS ACTUALLY RIGHT ◄◄◄◄

**`[MEASURED]`, the run:** no `[gevr] AUTOLEVEL` line, no crash, and
**`wfnf=2`** — `waitForNextFrame` was entered **twice in the entire session.**
`[REPORTED]`: *"I think it locked up."*

**`137` ALREADY ESTABLISHED THIS, AND IT IS WRITTEN 300 LINES ABOVE THE EDIT, IN
THE SAME FILE:**

> *"geVrTickInstrument was called ONCE, with `wfnf=2`. Both of those sit inside
> `bossMainloop`'s `while (g_MainStageNum < 0 || pendingGfx != 0)` loop... **the
> rendering is not going through the code path everything in RB-02 was built
> on**."*

**IN THE FRONT END THE GAME DOES NOT GO THROUGH `waitForNextFrame`.** I put the
front-end hook in the one function that does not run in the front end, **having
read past the finding while editing the file that records it.**

### THE HOOK THAT IS RIGHT: `viSetFovY`

**`[READ]` `set_world_camera`'s own comment: *"The patch calls this function
EVERY FRAME, unconditionally, from inside `viSetFovY`."***
**`[MEASURED]` the same run printed `world camera gate -> false` — so
`viSetFovY` DID run, and it ran in the FRONT END.** It is already
`RECOMP_PATCH`ed (`ge_vr_bindtest.c:619`), and `GE_VR_LIT`/`geVrPutS32` are local
to that file, so the log line comes free.

**THE MOVE IS: the same block, in `viSetFovY`, reading the same globals.** The
globals, the accessor `geVrAutoLevel()`, the host knob and the syms.ld entry are
all built and correct — **§2's mechanism is untested, not refuted.**

### STATUS: **INERT.** Nothing calls it. `-AutoLevel` does nothing.

**Deliberately left in rather than reverted** (`00-START-HERE`: DELETE NOTHING) —
**and the dead hook site keeps a comment saying why it was wrong, because
"put the front-end hook in `waitForNextFrame`" is an obvious idea that will occur
to somebody again.**

> **AND THE LOCK-UP IS NOT EXPLAINED BY THIS.** The queue never fired, so it
> cannot have caused a hang. **`[ASSUMED]`: it is the ordinary front-end fault
> (`206`/`207`) presenting as a hang rather than a crash this time.** Not
> established, and **not to be folded into `206`'s access violation without
> evidence** — a hang and an AV are different failures until something says
> otherwise.

**NOTHING STAGED. THE COMMIT IS THE OWNER'S.**
