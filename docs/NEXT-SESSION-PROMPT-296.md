Read `repo\docs\00-STATE.md` (esp. §6 traps — **one is new and it is sitting directly in your
path** — and §7 the engine facts, **four of which are new and three of them are `295`**), then
**`repo\docs\295-THE-PAIR-IS-RESTORED-TO-THE-ARENAS-OWNER-AND-THE-WATERMARK-IS-THE-STAMP.md`
§3, §5 and §6 IN FULL**, then `293` §3a, §3b.5 and **§3c IN FULL as corrected by `295` §3**, then
`RUN-SHEET-295.md` §0 and §9. Same rules as always. Reads from the bridge are not free
(`00-STATE` §6): `git log`, `git show` and `git diff <path>` are safe; `git status` and `git add`
are **NOT** — use `git --no-optional-locks` if you must, and **a bare `git diff` in the decomp
prints ~2,100 lines of CRLF churn, so always give it a path list.** The build, every run and every
commit are the owner's, main PC — **you write and validate OFFLINE, then supply complete
copy-paste command blocks (§7a).**

**`295` IS DOCS + CODE, OFFLINE ONLY. NOTHING WAS BUILT OR RUN IN IT, AND S3 HAS STILL NEVER RUN.**

---

## ►►►► FIRST: FIND OUT WHETHER `RUN-SHEET-295` HAS BEEN RUN. IT CHANGES YOUR JOB. ◄◄◄◄

`RUN-SHEET-295` is ARM 1 + ARM 2. Ask, or look for `run_295_S1_guard_mono.log`,
`run_295_S2a_restore_off.log` and `run_295_S2b_restore_on.log` in
`goldeneye-native\getv\build-windows\`.

- **NOT RUN:** the sheet is the session. Do not write ARM 3 on top of an unworn instrument.
- **RUN:** read S2a's `MISMATCH` site names first. **If `modelFindNodeMtx` or
  `projectileFindCollidingProp` appear there, `294` §3.6 is answered in the AFFIRMATIVE and a real
  reader exists.** If only `forced-read-after-lvlRender` appears, the answer is the null one — and
  it is still an answer, and ARM 1 still stands on its own. **Write the retraction or the
  confirmation into `295` before starting ARM 3.**

## ►►►► DO NOT REOPEN THESE. `294` AND `295` CLOSED THEM FROM SOURCE. ◄◄◄◄

- **`293` §3b.3's tank-rect blocker is RETRACTED** (`294` §1) and **`293` §3b.4's "second store"
  DOES NOT EXIST** (`294` §2). There is **no "which eye wins" decision anywhere in `293` §3b**.
- **Do not re-derive the restore target.** `295` §1: it is the **arena's owner**, not eye 0, and
  the code already asks `geStereoNoteArenaBuild()` for it. Under ARM 3 the owner becomes the last
  eye and `geStereoArenaViewPair()` correctly returns 0. **That is by design; do not "fix" it.**
- **Do not re-propose stamping an eye index into `render_pos`.** `294` §5's shape is superseded by
  the arena watermark and `295` §2 says why with `dyn.c` line numbers. **`propobj.c:5991` and
  `chr.c:2889` are untouched and should stay that way.**
- **Do not re-read the 69 `camGetWorldToScreenMtxf`/`currentPlayerGetViewToWorldMtxf` call sites.**
  ARM 2 is the instrument for that question and it is built.

## ►►►► THE THREE INVARIANTS THAT CONSTRAIN EVERYTHING YOU WRITE ◄◄◄◄

1. **THE PAIRING (`294` §4).** The view pair and every `render_pos` block written under it are one
   coordinate system with one owner. Any read of either must happen while that eye is installed.
2. **WHOLE-BUILD RE-RUN (`293` §3c.3).** In-place operators (`chr.c:3160-3161`,
   `bondviewTransformManyPosToViewMatrix`) are correct **exactly once per fresh allocation.** A
   partial re-run re-transforms. `292`'s fault 3 is what that looks like on screen.
3. **ADMISSION AND `PROPFLAG_ONSCREEN` STAY ONCE PER FRAME, FOR TWO REASONS** — `293` §3a (the
   test also selects between two *simulation* paths, and the lines upstream mutate the portal
   table) and `294` §3.4 (`propobj.c:1399` gates the **precise per-node bullet hit test** on that
   flag, so per-eye admission makes a prop's hit fidelity depend on which eye ran last).

---

## THE JOB: **ARM 3 — THE RENDER-ONLY PER-EYE PASS over `g_OnScreenPropList`.**

Re-`dynAllocate` `render_pos`, rebuild the matrices from `camGetWorldToScreenMtxf()`, re-run
`modelUpdateRelationsQuick`, re-derive `zDepth`, **touch nothing else.** NOT a split of
`objTick`/`chrTick` into two ticks and NOT a second tick — both are illegal (invariant 3).

**Per eye / once per frame is settled in `293` §3b.5 as corrected by `294` §4. Read it; do not
re-derive it.** Four things that will cost you a build:

- **►► THERE ARE TWO UNGUARDED ACCUMULATORS IN `chrTick`, NOT ONE. `295` §3.** `chr.c:2893`
  `flinchcnt += g_ClockTimer` **and `chr.c:2910` `update_color_shading(&chr->shadecol,
  &chr->nextcol)`** — the second is the same call `293` §3b.1 lists as GUARDED in `objTick`.
  **Hoist BOTH explicitly.** `293` §3c.1 names only the first and its title says "THE" accumulator.
- **►► `chrprop.c` IS 4,502 OF 4,502 LINES CRLF WHILE `HEAD` IS LF, AND YOUR DRIVER GOES IN IT**
  (`propsTick` `:2538`, `chraiUpdateOnscreenPropCount` `:219`, `g_OnScreenPropList` `:90`).
  **Convert that one file to LF in the same commit** the way `288a` did `bondview.c`/`bondview.h`,
  or a 40-line change reads as 4,500. **`git diff --stat <path>` before committing, every time.**
- **►► `chraiUpdateOnscreenPropCount()` ALSO SORTS THE LIST BY `zDepth` (`chrprop.c:254-276`).**
  `zDepth` is per-eye; the sort is in a once-per-frame function. **Decide out loud whether the
  second eye re-sorts, and write the limitation down if it does not.** `295` §6.
- **►► THE EXTRACTION, NOT A FLAG.** `chrTick` is ~2,800 lines of AI, animation and physics before
  `after_position_update` (`chr.c:2839`); a "build-only" flag threaded through it would have to
  guard all of it. **The cut is at `chr.c:2853`'s `if (headSwitchVisible)` block and
  `propobj.c:5983`'s `if (var_v1_5 != 0)` block** — extract each into a function called both in
  place and from the per-eye driver. **Do the escaping-locals analysis before writing a line, and
  say how many there are.**

**AND ARM 3 GETS ITS OWN KNOB, DEFAULT OFF.** `GETV_STEREO_REBUILD`. One behaviour change (`48`),
and it is the only way one binary can serve both the ARM 2 arms (which need the fault to exist)
and the ARM 3 arms (which remove it). **`295` §5.**

## THE GATE

**S3 MUST NOT RUN UNTIL S2 IS CLEAN AT ZERO SEPARATION** (`RUN-SHEET-292` §5, `RUN-SHEET-295` §6).
S3 has never run. **ARM 3 changes what S2 measures, so S2 is re-run before anyone talks about
separation** — and with `GETV_STEREO_REBUILD` on, **`GETV_STEREO_PAIRGUARD` must report
`mismatch=0` with `checks>0` in every window, which is ARM 3's own gate for free.**

## AND TREAT THIS PROMPT AS A HYPOTHESIS

**`293` §0 retracted `NEXT-SESSION-PROMPT-293`'s framing, `294` retracted two sections of `293`,
and `295` retracted a count in `293` §3c.1 and a shape in `294` §5.** Three sessions running, the
confident paragraph at the top of a document has been the thing that was wrong. **If a measurement
disagrees with anything above, the measurement wins and this prompt gets a retraction section, not
a rescue.** `[INFERRED]` here: that the extraction is the right cut, and that its cost is
affordable. **Neither is established. Nothing in `295` was built or run.**
