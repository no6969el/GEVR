Read `repo\docs\00-STATE.md` (§3 **OWNER ACTION OUTSTANDING, the TOP entry** — it is the whole of
the next action — plus §6 traps, **two are new**, and §7 the engine facts), then
**`RUN-SHEET-295.md` §10 and §11 IN FULL**, then `295` §3, §5 and §6, then `293` §3a, §3b.5 and
**§3c as corrected by `295` §3**. Same rules as always. Reads from the bridge are not free
(`00-STATE` §6): `git log`, `git show` and `git diff <path>` are safe; `git status` and `git add`
are **NOT** — and **a bare `git diff` in the decomp prints ~2,100 lines of CRLF churn, so always
give it a path list.** The build, every run and every commit are the owner's, main PC — **you
write and validate OFFLINE, then supply complete copy-paste command blocks (§7a).**

**`295` IS DOCS + CODE, OFFLINE ONLY. `296` IS DOCS ONLY. NOTHING HAS BEEN BUILT SINCE `292d`
(`goldeneye.exe`, `2026-09-01 02:10`), AND S3 HAS STILL NEVER RUN.**

---

## ►►►► FIRST, AND IT IS THE SAME BRANCH `296` FACED: HAS `RUN-SHEET-295` BEEN RUN? ◄◄◄◄

**`296` MEASURED THAT IT HAD NOT, AND DID NOT WRITE ARM 3.** Check again before assuming
anything — look in `goldeneye-native\getv\build-windows\` for `run_295_S1_guard_mono.log`,
`run_295_S2a_restore_off.log`, `run_295_S2b_restore_on.log`, and in the `GoldenEyeVR` root for
`build_295_pairguard.log`. **And check `goldeneye.exe`'s timestamp — if it still reads
`2026-09-01 02:10`, nothing has been built.**

- **STILL NOT RUN:** **the sheet is still the session.** It is now complete (`296` finished
  §6/§7/§8 into §10), so there is nothing left to write for it — **say so plainly, hand the owner
  the ordered block list, and do not start ARM 3.** `295` §5: ARM 3 in this binary makes
  `GETV_STEREO_PAIRGUARD` incapable of reporting anything but zero.
- **RUN:** **read S2a's `MISMATCH` site names FIRST.** If **`modelFindNodeMtx`** or
  **`projectileFindCollidingProp`** appear there, `294` §3.6 is answered in the **AFFIRMATIVE** and
  a real reader exists. If only **`forced-read-after-lvlRender`** appears, the answer is the null
  one — **and it is still an answer, and ARM 1 still stands on its own.** The discriminator is
  arithmetic, not vibes: the forced read guarantees **one mismatch per frame**, so a `mismatch` at
  or near the frame count means only the forced read fired, and **well above it means real engine
  readers.** **Write the retraction or the confirmation into `295` BEFORE starting ARM 3.**

**THE ORDER, ONCE: §1 → §2 → §3 (S1) → §4 (S2a) → §5 (S2b) → §10.1 (S2) → §10.2 (S3) → §10.3 (S4)
→ §10.4 (S5).** §1's two offline gates were re-worn by `296` and both PASS — **but under the
bridge's `gcc 11.4.0`, not the main PC's, so §1 is still owed there** (`296` §11).

## ►►►► DO NOT REOPEN THESE. `294`, `295` AND `296` CLOSED THEM. ◄◄◄◄

- **`293` §3b.3's tank-rect blocker is RETRACTED** (`294` §1) and **`293` §3b.4's "second store"
  DOES NOT EXIST** (`294` §2). There is **no "which eye wins" decision anywhere in `293` §3b**.
- **Do not re-derive the restore target.** `295` §1: it is the **arena's owner**, not eye 0. Under
  ARM 3 the owner becomes the last eye and `geStereoArenaViewPair()` correctly returns 0. **By
  design; do not "fix" it.**
- **Do not re-propose stamping an eye index into `render_pos`.** `294` §5 is superseded by the
  arena watermark (`295` §2). **`propobj.c:5991` and `chr.c:2889` are untouched and stay that way.**
- **Do not re-read the 69 `camGetWorldToScreenMtxf`/`currentPlayerGetViewToWorldMtxf` call sites.**
  ARM 2 is the instrument for that question and it is built.
- **Do not re-check GATE B1's nine strings or the sheet's knob names.** `296` §11 `[MEASURED]` all
  nine present in source, and every `GETV_*` the sheet sets. **A `MISSING` there is a build
  failure, not a typo.**
- **Do not "improve" `RUN-SHEET-295` §10's blocks.** They are the splice already made and the
  reason they exist is `296` §11 defect 1.

## ►►►► THE THREE INVARIANTS THAT CONSTRAIN EVERYTHING ARM 3 WRITES ◄◄◄◄

1. **THE PAIRING (`294` §4).** The view pair and every `render_pos` block written under it are one
   coordinate system with one owner. **Any read of either must happen while that eye is installed.**
2. **WHOLE-BUILD RE-RUN (`293` §3c.3).** In-place operators (`chr.c:3160-3161`,
   `bondviewTransformManyPosToViewMatrix`) are correct **exactly once per fresh allocation.** A
   partial re-run re-transforms. `292`'s fault 3 is what that looks like on screen.
3. **ADMISSION AND `PROPFLAG_ONSCREEN` STAY ONCE PER FRAME, FOR TWO REASONS** — `293` §3a (the test
   also selects between two *simulation* paths, and the lines upstream mutate the portal table) and
   `294` §3.4 (`propobj.c:1399` gates the **precise per-node bullet hit test** on that flag, so
   per-eye admission makes a prop's hit fidelity depend on which eye ran last).

---

## THE JOB, WHEN AND ONLY WHEN THE SHEET IS WORN: **ARM 3 — THE RENDER-ONLY PER-EYE PASS over
`g_OnScreenPropList`.**

Re-`dynAllocate` `render_pos`, rebuild the matrices from `camGetWorldToScreenMtxf()`, re-run
`modelUpdateRelationsQuick`, re-derive `zDepth`, **touch nothing else.** NOT a split of
`objTick`/`chrTick` into two ticks and NOT a second tick — both are illegal (invariant 3).

**Per eye / once per frame is settled in `293` §3b.5 as corrected by `294` §4. Read it; do not
re-derive it.** Four things that will cost a build:

- **►► TWO UNGUARDED ACCUMULATORS IN `chrTick`, NOT ONE. `295` §3.** `chr.c:2893`
  `flinchcnt += g_ClockTimer` **and `chr.c:2910` `update_color_shading(&chr->shadecol,
  &chr->nextcol)`** — the second is the same call `293` §3b.1 lists as GUARDED in `objTick`.
  **Hoist BOTH explicitly.**
- **►► `chrprop.c` IS 4,502 OF 4,502 LINES CRLF WHILE `HEAD` IS LF, AND THE DRIVER GOES IN IT**
  (`propsTick` `:2538`, `chraiUpdateOnscreenPropCount` `:219`, `g_OnScreenPropList` `:90`).
  **Convert that one file to LF in the same commit** the way `288a` did `bondview.c`/`bondview.h`.
  **`git diff --stat <path>` before committing, every time.**
- **►► `chraiUpdateOnscreenPropCount()` ALSO SORTS BY `zDepth` (`chrprop.c:254-276`).** `zDepth` is
  per-eye; the sort is once per frame. **Decide out loud whether the second eye re-sorts, and write
  the limitation down if it does not.** `295` §6.
- **►► THE EXTRACTION, NOT A FLAG.** `chrTick` is ~2,800 lines of AI, animation and physics before
  `after_position_update` (`chr.c:2839`). **The cut is `chr.c:2853`'s `if (headSwitchVisible)`
  block and `propobj.c:5983`'s `if (var_v1_5 != 0)` block** — extract each into a function called
  both in place and from the per-eye driver. **Do the escaping-locals analysis before writing a
  line, and say how many there are.**

**AND ARM 3 GETS ITS OWN KNOB, DEFAULT OFF: `GETV_STEREO_REBUILD`.** One behaviour change (`48`),
and the only way one binary serves both the ARM 2 arms (which need the fault) and the ARM 3 arms
(which remove it). `295` §5.

## THE GATE

**S3 MUST NOT RUN UNTIL S2 IS CLEAN AT ZERO SEPARATION** (`RUN-SHEET-292` §5, `RUN-SHEET-295`
§10.1). **ARM 3 changes what S2 measures, so S2 is re-run before anyone talks about separation** —
and with `GETV_STEREO_REBUILD` on, **`GETV_STEREO_PAIRGUARD` must report `mismatch=0` with
`checks>0` in every window, which is ARM 3's own gate for free.**

## AND TREAT THIS PROMPT AS A HYPOTHESIS

**`293` §0 retracted `NEXT-SESSION-PROMPT-293`'s framing; `294` retracted two sections of `293`;
`295` retracted a count in `293` §3c.1 and a shape in `294` §5; and `296` found that
`NEXT-SESSION-PROMPT-296`'s entire stated job was not the job, because its own first instruction
said so.** Four sessions running, the confident paragraph at the top of a document has been the
thing that was wrong. **If a measurement disagrees with anything above, the measurement wins and
this prompt gets a retraction section, not a rescue.**

**`[INFERRED]` here, carried forward from `296` UNTESTED:** that the `chr.c:2853` /
`propobj.c:5983` extraction is the right cut, and that its cost is affordable. **Neither is
established. Nothing since `292d` has been built or run.**
