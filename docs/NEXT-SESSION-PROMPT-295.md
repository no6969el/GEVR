# NEXT SESSION PROMPT — `295`

Read `repo\docs\00-STATE.md` (esp. §5 dead theories, §6 traps — **one is new and it is why `293`
wrote a blocker that does not exist** — and §7 the engine facts, **two of which are new and are the
whole of `294`**), then **`repo\docs\294-THE-VIEW-CANCELS-THE-MATRICES-ARE-THE-ARENA-AND-ALL-THREE-HAZARDS-ARE-ONE-PAIRING.md`
§4, §3.6 and §5**, then `293` §3a, §3b.5 and **§3c IN FULL**, then `RUN-SHEET-292.md` §5 for the S3
gate. Same rules as always. Reads from the bridge are not free (§6): `git log`, `git show` and
`git diff <path>` are safe; `git status` and `git add` are **NOT** — use `git --no-optional-locks`
if you must, and **a bare `git diff` in the decomp prints ~2,100 lines of CRLF churn, so always give
it a path list.** The build, every run and every commit are the owner's, main PC — **you write and
validate OFFLINE, then supply complete copy-paste command blocks (§7a).**

**`294` IS DOCS ONLY. NOTHING WAS BUILT OR RUN IN IT, AND S3 HAS STILL NEVER RUN.**

---

## ►►►► DO NOT REOPEN THESE. `294` CLOSED THEM FROM SOURCE. ◄◄◄◄

- **`293` §3b.3's tank-rect blocker is RETRACTED.** `propobj.c:6347` is a **round trip** —
  `V2W · (W2V · world)` — and `camGetWorldToScreenMtxf()` is the **bare lookat**, not a projection
  (`bondview.c:832`; the projection is a separate copy, `bondview2.c:9017-9044`). The eye offset
  enters and leaves on one line. **There is no 250-unit offset and no "last eye wins".** Do not
  re-derive it; §1 of `294` has the four line numbers.
- **`293` §3b.4's "second store that is not the arena" DOES NOT EXIST.** `modelFindNodeMtx` returns
  `&model->render_pos[index].pos` (`model.c:669-676`) — **the arena block itself.** Doubling the
  pools covers it. **`293` §3b.5's "Undecided" is empty.**
- **`objecthandler.c:430-662` is not a reader from outside the build** — `sub_GAME_7F06B29C`'s only
  callers are inside `chrTick` (`chr.c:3201/:3221/:3225`) plus `title.c`.
- **Do not re-read the 69 `camGetWorldToScreenMtxf`/`currentPlayerGetViewToWorldMtxf` call sites.**
  `294` §3.6 deliberately did not, and §5 says why: that is what the instrument in ARM 2 is for.

## ►►►► THE TWO INVARIANTS THAT CONSTRAIN EVERYTHING YOU WRITE ◄◄◄◄

1. **THE PAIRING (`294` §4).** The view pair (`field_10CC` = W2V, `viewtoworldmtxf` = V2W) and every
   `render_pos` block written under it are **one coordinate system with one owner.** Any read of
   either must happen while that eye is installed. Split-screen gets this free because
   `set_cur_player()` moves all three together; **an eye loop keeping `getPlayerCount()` at 1
   (`258` §1.5) gets none of it and must reproduce it by hand.**
2. **WHOLE-BUILD RE-RUN (`293` §3c.3).** In-place operators (`chr.c:3160-3161`,
   `bondviewTransformManyPosToViewMatrix`) are correct **exactly once per fresh allocation.** A
   partial re-run re-transforms. `292`'s fault 3 is what that looks like on screen.

**There is no "which eye wins" decision anywhere in `293` §3b. If you find yourself making one, stop
and re-read `294` §4.**

---

## THE THREE ARMS, IN THIS ORDER. THE FIRST TWO ARE CHEAP AND THEY DE-RISK THE THIRD.

### ARM 1 — THE VIEW-PAIR RESTORE. One line, cannot be wrong.

`lv.c:1042-1046` restores the rectangle, the aspect and the camera scales at the end of the eye
loop **but not the view matrix pair**, which only `viSetupCurrentPlayerView` writes. So once
`lvlRender` returns, `camGetWorldToScreenMtxf()` is the **last eye's** while every `render_pos` is
**eye 0's** — `[MEASURED]` from source, already true in the current build. Restore the pair the same
way the rectangle is restored. **It removes the whole class regardless of whether anything reads it
in that window.** `294` §3.6.

### ARM 2 — `GETV_STEREO_PAIRGUARD`. The instrument that answers §3.6 by measurement.

Stamp an eye index beside the pair when it is installed (`bondview.c:823`, `:856`) and into each
`dynAllocate`d `render_pos` block (`propobj.c:5991`, `chr.c:2889`); compare them on
`modelFindNodeMtx` and on entry to `projectileFindCollidingProp`; log and count mismatches. Inert
when the knob is off. **Shape only — `294` §5 is `[INFERRED]`, not costed, and you may find a better
place to hook it.**

**ITS FALSIFIER IS PART OF IT AND MUST BE RUN (rule `15`):** with stereo **OFF** it must report
**zero** mismatches, and against a deliberate late read it must report **non-zero**. A guard that
cannot fail on the boring frame is `279` §7 again. **Run it on the frame you expect to be boring.**

### ARM 3 — THE RENDER-ONLY PER-EYE PASS over `g_OnScreenPropList`. The real work.

Re-`dynAllocate` `render_pos`, rebuild the matrices, re-run `modelUpdateRelationsQuick`, re-derive
`zDepth`, **touch nothing else.** NOT a split of `objTick`/`chrTick` and NOT a second tick — both
are illegal (`293` §3a: the admission test selects between two *simulation* paths, and the lines
upstream mutate the portal table the room walk reads).

**Per eye / once per frame is settled in `293` §3b.5 as corrected by `294` §4 — read it, do not
re-derive it.** Two things it is easy to get wrong:

- **`chr.c:2893`'s `flinchcnt += g_ClockTimer` is behind NO guard** (`293` §3c.1). Run the build
  twice and every character recovers from being shot in **half the time**. **Hoist it out
  explicitly.** `293` §3b.1's *"every accumulator is already behind `isSimOwner`"* is true of
  `objTick` and **false of `chrTick`.**
- **Admission and `PROPFLAG_ONSCREEN` stay ONCE PER FRAME, and now for two reasons.** The second is
  new: `propobj.c:1399` gates the **precise per-node bullet hit test** on that flag — everything
  else falls through to a coarse bounding sphere. Run admission per eye and **a prop's hit fidelity
  depends on which eye ran last.** `294` §3.4.

---

## THE TRAPS THAT WILL COST YOU A BUILD IF YOU SKIP THEM

- **►► A LOCAL `extern` BESIDE A CALL SITE IS A HARD ERROR THAT SURVIVES `-w` AND SURFACES AS A LINK
  WALL NAMING SYMBOLS THAT ARE NOT MISSING. IT COST `292` A BUILD.** `build_windows.ps1:207`
  force-includes `src/ge_port_decls.h` into every game TU, so every engine prototype is already in
  scope. **Delete the local extern; do not correct it.** Offline `gcc -fsyntax-only` **does not
  catch it** unless it replicates the force-include — run `bash getv/tools/stereo_harness.sh`, which
  parses with `build_windows.ps1`'s own flag list. **Read the build's FIRST failure line, not the
  last error.** `00-STATE` §6.
- **►► IN `vendor/ge-decomp`, STAGE BY EXACT PATH. NEVER `git add -A`** — it sweeps ~2,100
  CRLF-dirty files into the commit, and **this has already happened once** (`7a4e7bfd`: a
  three-line fix carrying 736 files and 601,764 insertions). **`git diff --stat <path>` before
  committing, and check the number is the size of the change you made.** `288a`.
- **`COMMIT-NOW.cmd` does NOT cover `vendor/ge-decomp`** (`.gitignore:42`). A session whose whole
  change is in the decomp commits **nothing** if the owner only double-clicks it. Supply an explicit
  `-F` block.
- **Commit-message files go in the `GoldenEyeVR` ROOT, never beside the repo they describe.** `287`.
- **`gfx_pc.c` and `gfx_sdl2.c` are GITIGNORED AND REGENERATED.** Check `git ls-files` **before**
  editing anything under `getv/port/**`, and if you touch them, `tools/fetch-thirdparty.sh regen`
  then `verify` (**`15/15`**), **Git Bash, main PC, after the arms are worn** — a regen before the
  arms **deletes the instrument**. `287` §5, `271` §7.
- **For anything the owner will LOOK at or PLAY: `GETV_VSYNC=1`, `GETV_FPS=120`, `GETV_SIMHZ=query`.
  Every run sheet in this repo carries `GETV_VSYNC=0` and it is wrong for these runs.** `285`.
  **And put EVERY knob in EVERY block** — an omitted knob silently restores its default and reads
  as a regression. **`Remove-Item Env:GETV_*` before every run.**

## THE GATE

**S3 MUST NOT RUN UNTIL S2 IS CLEAN AT ZERO SEPARATION** (`RUN-SHEET-292` §5). S3 has never run.
**ARM 3 changes what S2 measures, so S2 is re-run before anyone talks about separation.**

## AND TREAT THIS PROMPT AS A HYPOTHESIS

**`293` §0 retracted the framing in `NEXT-SESSION-PROMPT-293`, and `294` retracted two sections of
`293`.** Twice now the confident paragraph at the top of a document has been the thing that was
wrong. **If a measurement disagrees with anything above, the measurement wins and this prompt gets
a retraction section, not a rescue.** `[INFERRED]` here: that ARM 1 and ARM 2 are cheap, and that
ARM 3's shape is right. **Neither is established. Nothing in `294` was built or run.**
