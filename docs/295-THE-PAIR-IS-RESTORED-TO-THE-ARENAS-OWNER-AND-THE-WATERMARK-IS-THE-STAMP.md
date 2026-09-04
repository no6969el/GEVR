# 295 — THE PAIR IS RESTORED TO **THE ARENA'S OWNER**, THE **WATERMARK** IS THE STAMP, AND `293` §3c.1 UNDERCOUNTED BY ONE

**Currency: 2026-09-02. ARM 1 AND ARM 2 ARE WRITTEN AND VALIDATED OFFLINE. NOTHING WAS BUILT,
NOTHING WAS RUN, NOTHING WAS COMMITTED. ARM 3 WAS NOT WRITTEN — AND §5 IS WHY THAT IS A
FINDING AND NOT A SHORTFALL. S3 HAS STILL NEVER RUN.**

---

## §0 — THE HEADLINE

1. **ARM 1 IS WRITTEN.** `lv.c` now restores the view pair at the end of the eye loop, the same
   way it already restores the rectangle, the aspect and the camera scales. **It does not restore
   "eye 0's" pair. It restores THE ARENA'S OWNER's pair** — §1 — which is eye 0 today and would
   become the last eye the moment ARM 3 exists. Naming the owner instead of the index is the whole
   reason ARM 1 and ARM 3 compose instead of fighting.
2. **ARM 2 IS WRITTEN, AND IT DOES NOT STAMP ANYTHING.** `294` §5 asked for an eye index written
   beside the view pair and into every `dynAllocate`d `render_pos` block, and said the shape was
   `[INFERRED]` and that a better hook might exist. **It does: the ARENA WATERMARK.** `dynAllocate`
   is one bump pointer that only increases within a frame (`dyn.c:155-190`), so each eye's
   allocations are one **contiguous address range** and a pointer names its own eye. **Nothing is
   stamped, nothing grows, and `propobj.c:5991` and `chr.c:2889` are not touched at all** — §2.
3. **►► `293` §3c.1 UNDERCOUNTED. `chrTick`'s BUILD BLOCK HAS *TWO* UNGUARDED ACCUMULATORS, NOT
   ONE.** `[MEASURED]` `chr.c:2910`: `update_color_shading(&chr->shadecol, &chr->nextcol)` sits
   inside the same `headSwitchVisible` block as `flinchcnt`, behind **no guard at all** — and it is
   the *identical call* `293` §3b.1 lists as being behind `isSimOwner` in `objTick` (`:5985-5987`).
   **Anyone who hoists only `flinchcnt` ships a double-rate colour lerp.** §3.
4. **►► AND ARM 3 MUST NOT BE IN THE SAME BUILD AS ARM 2'S FIRST WEARING.** ARM 3 rebuilds the
   arena under every eye, so the pair and the arena agree everywhere and **`GETV_STEREO_PAIRGUARD`
   can only ever report zero.** The instrument that is supposed to measure the fault would be
   measuring a build in which the fault cannot exist. §5.
5. **THE OFFLINE HARNESS IS GREEN AT `61/61`**, up from `37/37`, including a **real-header syntax
   gate on all seven touched files with `build_windows.ps1`'s own flag list** and a three-arm
   pairing falsifier whose middle arm **must fail on purpose**. §4.

---

## §1 — ARM 1. **AND THE RESTORE TARGET IS NOT A FREE CHOICE.**

`294` §3.6 `[MEASURED]`: `lv.c:1042-1046` restores the rectangle, the aspect and the camera scales
and **not** the view pair, which only `viSetupCurrentPlayerView` → `bondview2.c:9046-9047` ever
writes. So when `lvlRender` returns, `camGetWorldToScreenMtxf()` is the **last eye's** while every
`model->render_pos` is the **build eye's**.

**The question `294` did not have to ask, and ARM 1 does: whose pair goes back?**

- There is **no mono pair** in a stereo frame. Neither eye is the un-offset camera, so "restore
  what was there before the loop" has no referent — the pre-loop pair is *last frame's*.
- `294` §4 answers it without a preference: **the pair and the arena are one coordinate system with
  one owner.** So the pair to leave installed is the one belonging to **the eye that owns the
  arena** — the eye under which the model build last ran.
- **Today that is eye 0**, because `propsTick()` sits behind `geStereoIsFirstEye()` (`lv.c:908`).
- **After ARM 3 it would be the LAST eye**, and the restore correctly becomes a no-op.

`lv.c` therefore calls `geStereoNoteArenaBuild()` immediately before `propsTick()` and asks
`geStereoArenaViewPair()` after the loop. **Had ARM 1 hard-coded eye 0, ARM 3 would silently
re-introduce the mismatch it was written to remove.**

### 1.1 — TWO POINTER WRITES, NOT A COPY

`field_64` / `field_68` are `dynAllocateMatrix()` blocks (`bondview2.c:8978-8981`) and the arena is
never reused within a frame (`dyn.c:155-190`), so **eye 0's pair is still intact and still eye
0's** when the loop closes. The restore is two pointer writes. **Nothing is copied, so nothing can
be re-transformed** — `293` §3c.3's in-place hazard is not reachable from here.

### 1.2 — AND IT DELIBERATELY DOES **NOT** GO THROUGH THE SETTERS

`currentPlayerSetMatrix10CC` / `currentPlayerSetViewToWorldMtxf` (`bondview.c:823-830`, `:856-859`)
also push the outgoing value into `field_10E8` / `field_10EC` — **the PREVIOUS-view pair, and it is
read**: `chraction.c:6101` and `:6119` call
`matrix_4x4_multiply_homogeneous_in_place(currentPlayerGetMatrix10EC(), …)`. A restore is not a new
view; routing it through the setters would leave `chraction` reading *"eye 1 of this frame"* as the
previous view. **ARM 1 writes the two fields directly and touches nothing else.**

> `[MEASURED]`, and **NOT FIXED HERE**: in a stereo frame that shadow is *already* wrong — eye 1's
> setter call pushes **eye 0 of the same frame** into it, so `chraction`'s "previous view" is
> 250 units away rather than one frame old. **That is a separate defect with a separate owner and
> it is written down, not folded in** (`263` §1).

### 1.3 — WHAT IT DOES WHEN NO BUILD RAN

If `gePortSimShouldTick()` was false for the whole frame, no eye owns the arena — the blocks are
last frame's (`00-STATE` §7). **The helper returns 0 and nothing is written.** Re-installing a pair
there would be an assertion, not a restore. In the mandated configuration this cannot happen
(`GETV_SIMHZ=query` ticks every frame, `277`); under `GETV_SIMDIV>1` it can.

---

## §2 — ARM 2. **THE WATERMARK IS THE STAMP, AND IT IS STRICTLY BETTER THAN `294` §5's.**

`294` §5 proposed one `s32` beside the view pair and one inside every `dynAllocate`d `render_pos`
block, hooked at `propobj.c:5991` and `chr.c:2889`. **That shape was `[INFERRED]` and said so.**

`[MEASURED]` `dyn.c:155-190`: `dynAllocate`, `dynAllocateMatrix` and `dynAllocateLights` are the
**same single bump pointer**, `g_GfxMemPos`, which only ever increases within a frame and is reset
only by `dynSwapBuffers()`. That is the same property `293` §2.1 used to prove the second eye
allocated nothing. **Therefore every allocation an eye makes lies in ONE CONTIGUOUS ADDRESS
RANGE**, and recording `g_GfxMemPos` at each eye's first line names the owner of every block for
free.

| | `294` §5's stamp | the watermark |
|---|---|---|
| files touched in the hot path | `propobj.c`, `chr.c` | **none** |
| memory | +1 `s32` per block | **0** |
| coverage | the two named blocks | **every arena block** — hat matrices (`chr.c:3033`), joint lists, the camera matrices themselves |
| cost per allocation | a store | **0** |
| cost per check | a load | two pointer compares |

**A pointer in NO range is reported as `outside`, never as a mismatch.** Two honest things produce
one: a block allocated before the loop opened, and a **stale pointer from last frame into the other
half of the double buffer** (`00-STATE` §7 — a model that is not re-admitted keeps last frame's
pointer). Calling either a mismatch would make the guard fire for a reason that has nothing to do
with eyes, which is `279` §7 in the other direction.

### 2.1 — THE TWO READ SITES, AND WHY THEY ARE DIFFERENT SHAPES

- **`model.c:669-683`, `modelFindNodeMtx`** — the hand-out point for the arena block. Every
  per-node matrix the shot path, the joint list and the renderer read comes through here, so the
  check has a **pointer** and compares *that block's* eye against the installed pair's.
- **`propobj.c:1562-1613`, `projectileFindCollidingProp`** — transforms the shot ray **into** the
  pair (`:1601`, `:1607`) and then walks `render_pos`. There is no single block to name, so it
  compares **the arena's owner as a whole** against the installed pair. This is the assertion of
  `294` §3.2's source read rather than a repetition of it.

### 2.2 — THE COUNTERS ARE WINDOWED, AND `checks=` IS PART OF THE GATE

`289` §4: *"a cumulative count with no windowing"* cannot say whether anything moved, so the
SUMMARY prints **both** a per-window and a cumulative triple. And it prints `checks=` beside
`mismatch=` because **a zero mismatch out of zero checks is `279` §7, not a result.** The run
sheet gates on `checks > 0` **and** `mismatch == 0`, never on `mismatch` alone.

---

## §3 — **A CORRECTION TO `293` §3c.1: THERE ARE TWO UNGUARDED ACCUMULATORS, NOT ONE.**

`293` §3c.1 is titled *"THE UNGUARDED ACCUMULATOR"*, singular, and names `chr.c:2893`'s
`flinchcnt += g_ClockTimer`. `[MEASURED]`, from a sweep of every `+=`, `-=`, `++`, `--` and every
`update_color_shading` call in `chr.c:2853-3240`:

```c
chr.c:2891   if (g_CurModelChr->flinchcnt >= 0)
chr.c:2893       g_CurModelChr->flinchcnt += g_ClockTimer;      /* named by 293 §3c.1 */
...
chr.c:2910   update_color_shading(&chr->shadecol, &chr->nextcol);   /* NOT named. NO guard. */
```

`update_color_shading` (`propobj.c:656-668`) is
`dest += ((src - dest) + 7) >> 3` — **an exponential-approach lerp, i.e. an accumulator.** Run it
twice per frame and each channel closes `1 - (7/8)² = 23.4%` of the gap instead of `12.5%` —
**very nearly double rate.**

**And it is the same call `293` §3b.1 lists in its own table as being behind `isSimOwner` in
`objTick` (`:5985-5987`).** So the asymmetry `293` §3c.1 discovered is real and *larger* than it
was written: `objTick` guards this call, `chrTick` does not.

**Consequence for ARM 3: the hoist list is TWO lines, not one.** The complete unguarded set in
`chrTick`'s build block is `chr.c:2893` and `chr.c:2910`, plus the debug nudges at `:3071-3101`
that `293` §3c.1 already named as developer-only.

**Everything else in `293` §3c stands.** §3c.2's *"the joint list is rebuilt from NULL every
pass"*, §3c.3's in-place invariant and §3b's `objTick` table are unchanged by this.

---

## §4 — WHAT WAS VALIDATED, AND WHAT THAT DOES NOT MEAN

`getv/tools/stereo_harness.sh` — **`61 passed, 0 failed`, `VERDICT PASS`** (was `37/37`).

- **THE REAL-HEADER SYNTAX GATE NOW COVERS SEVEN FILES**, parsed with `build_windows.ps1`'s own
  flag list **including `-include src/ge_port_decls.h`**: `stereo.c`, `lv.c`, `fr.c`,
  `bondview2.c`, `dyn.c`, and newly **`model.c`** and **`propobj.c`**. `0 errors` on every one.
  This gate exists because `292`'s local `extern` was a hard error that survived `-w` and surfaced
  as a link wall (`00-STATE` §6).
- **AND THE NEW CALL SITES ADD NO LOCAL `extern` AT ALL.** `bondview2.c`, `model.c` and
  `propobj.c` `#include "stereo.h"`, and **`bondview2.c`'s existing local extern for
  `geStereoOffsetCameraPos` was DELETED, not corrected** — which is what §6 says the fix is.
- **`g_GfxMemPos` IS NOT DECLARED IN `stereo.c`.** `ge_port_decls.h` force-includes `game/dyn.h`,
  which declares it (`dyn.h:23`); the harness supplies it in its stub header exactly as it already
  supplies the three engine functions `geStereoPredict()` calls.
- **THE PAIRING FALSIFIER IS THREE ARMS AND THE MIDDLE ONE MUST FAIL:**

| arm | knobs | required |
|---|---|---|
| `pairmono` | stereo OFF, `PAIRGUARD=1` | `checks=3` `mismatch=0` — **the boring frame** (`279` §7) |
| `pairoff` | stereo ON, `VIEWRESTORE=0` | `checks=3` **`mismatch>0`** — the guard MUST fire |
| `pairon` | stereo ON, `VIEWRESTORE=1` | `checks=3` `mismatch=0` — ARM 1 removes the class |

  All three pass. **The mono arm is run FIRST and on purpose**: an instrument that has only ever
  been pointed at the positive frame is `279` §7.

**WHAT THE HARNESS CANNOT DO** (the same honesty as `258` STAGE 6's): it drives a **fake** arena
and a **fake** eye loop. It cannot prove that any real reader of the pair exists in the window
after `lvlRender` returns — `294` §3.6 is explicit that this is unestablished and that reading 69
call sites is not how to establish it. **`GETV_STEREO_PAIRGUARD_FORCE=1` is the arm that makes the
guard fire regardless of whether a real reader is found, and it is in the run sheet.**

---

## §5 — **WHY ARM 3 IS NOT IN THIS BUILD, AND IT IS A FINDING**

The prompt ordered the arms *"first two are cheap and they de-risk the third"*. There is a sharper
reason than cost, and it is an argument from ARM 2's own logic:

> **ARM 3 REBUILDS `render_pos` UNDER EVERY EYE. The pair and the arena would then agree in every
> window — inside eye 1's render, and after the loop. `GETV_STEREO_PAIRGUARD` COULD ONLY EVER
> REPORT ZERO, AND THAT ZERO WOULD MEAN NOTHING.**

Shipping ARM 3 in the same build as ARM 2's first wearing destroys the only measurement that can
say whether `294` §3.6's mismatch has a real reader. **The observe-only arm must be worn on a build
where the fault can still exist.** Same shape as `279` §7 and rule `15`: measure the fault before
removing it, or the removal is untestable.

The same argument is why **`GETV_STEREO_VIEWRESTORE` defaults ON but has an off-switch**: ARM 2's
positive arm is `VIEWRESTORE=0`, not a hand-built stale read.

**ARM 3 IS THEREFORE THE NEXT SESSION'S WHOLE JOB, AND `296` CARRIES IT.** What this session
established that it will need is in §3 (two accumulators, not one) and §6 (the CRLF trap that is
waiting for it).

---

## §6 — TWO TRAPS FOUND WHILE WRITING, BOTH `[MEASURED]`, BOTH FOR `296`

- **►► `chrprop.c` IS FULLY CRLF ON DISK AND `HEAD` IS LF — 4,502 of 4,502 lines.** ARM 3's driver
  belongs in `chrprop.c` (`propsTick` is at `:2538`, `chraiUpdateOnscreenPropCount` at `:219`,
  `g_OnScreenPropList` at `:90`), so **`288a`'s trap is waiting for it**: an honest 40-line change
  will first read as ~4,500. `[MEASURED]` this session, with `grep -c $'\r'` per file: `lv.c`,
  `stereo.c`, `stereo.h`, `bondview2.c`, `model.c`, `propobj.c` and `chr.c` are **all LF** and
  diffed clean; `chrprop.c` is the odd one out. **Convert that one file to LF in the same commit,
  the way `288a` converted `bondview.c`/`bondview.h`, or the diff is unreviewable.**
- **►► `chraiUpdateOnscreenPropCount()` DOES NOT ONLY COUNT — IT SORTS `g_OnScreenPropList` BY
  `zDepth` (`chrprop.c:254-276`).** `293` §3b.5 puts `zDepth` in the per-eye column and admission
  in the once-per-frame column, and **the sort straddles them**: it is derived from a per-eye
  quantity but lives in a once-per-frame function. Re-deriving `zDepth` per eye without re-sorting
  leaves eye 1 drawing in eye 0's alpha order. **It is a decision `296` has to make out loud; this
  session did not make it.**

---

## §7 — WHAT THIS RETRACTS

- **`293` §3c.1's *"THE UNGUARDED ACCUMULATOR"*, singular, and its claim that `flinchcnt` is the
  one.** There are **two** — §3. The section's argument, its conclusion and its consequence for
  ARM 3 all stand; the **count** was wrong.
- **`294` §5's stamp, as a shape.** Not retracted as an idea — it would work — but **superseded by
  the watermark**, which §5 itself invited ("you may find a better place to hook it"). §2.
- **Nothing else.** `294` §1, §2, §3, §3.4, §3.5, §3.6 and §4 stand unchanged. `293` §1, §2, §2.1,
  §3, §3a, §3b and §3c.2/§3c.3 stand. `292`'s faults 1 and 2 stand. The pool sizing stands.

## §8 — NOT CLAIMED

- **NOTHING WAS BUILT AND NOTHING WAS RUN.** No claim that this compiles under MSVC/clang — the
  gate is `gcc -fsyntax-only` with the build's flags, which is a **parse**, not a build. **S3 has
  still never run** and `RUN-SHEET-292` §5's gate is untouched.
- **THAT ANYTHING READS THE PAIR IN `294` §3.6's WINDOW IS STILL NOT ESTABLISHED.** ARM 2 is the
  instrument for it, and it has not been pointed at the game.
- **THE COST OF THE `modelFindNodeMtx` CHECK IS NOT MEASURED.** It is one call and one branch per
  node lookup with the knob off, on a path that already walks a node tree — **`[INFERRED]`
  negligible, and `P5` says that is not a claim.** The S5 cost arm is in the run sheet for it.
- **ARM 3 IS NOT WRITTEN, NOT DESIGNED LINE BY LINE, AND NOT COSTED.** §5 says why it is not here;
  it does not say it is easy.
- **§1.2's SHADOW DEFECT (`field_10E8`/`field_10EC` holding this frame's other eye) IS NAMED, NOT
  FIXED AND NOT MEASURED.** No run has shown it matters.

## §9 — STILL OWED, CARRIED FORWARD

All of `294` §8 unchanged — `277` §9 · `278` §6 · `279` §5 · `280` §7.3 · `274` §7's `CONTAMINATED`
gate · **`287` ARM 6 the wear pass, STILL NEVER RUN** · `289` R2's missing `dlgrab` ·
`GETV_ROOMSCISSOR=0` as a default · `293` §5's `GETV_CHR_DEBUG` per-eye tagging.
**`294`'s two newly-owed items are DISCHARGED by this session** (the view-pair restore is written;
the §3.6 instrument is written) **— but neither has been RUN, so neither is closed.**
**Newly owed by this doc:** the `zDepth` re-sort decision (§6) · `chrprop.c`'s line endings (§6) ·
§1.2's previous-view shadow.

---

## §10 — **ARM 2 IS WORN, AND `294` §3.6's QUESTION IS ANSWERED IN THE NULL. `[ADDED 2026-09-02, SESSION `297`.]`**

`NEXT-SESSION-PROMPT-297` requires this section to exist before ARM 3 is started, and it requires
the answer to be read off an arithmetic discriminator rather than off a vibe. Both are done here.

**THE SHEET WAS RUN.** `[MEASURED]` from the owner's own logs in
`goldeneye-native\getv\build-windows\`, against `goldeneye.exe 2026-09-02 01:29`:

| arm | log | window checks | window mismatch | reading |
|---|---|---|---|---|
| S1 mono, guard ON | `run_295_S1_guard_mono.log` | 8400 | **0** | the boring frame. `checks > 0`, so the zero is a result and not `279` §7 |
| S2a `VIEWRESTORE=0` | `run_295_S2a_restore_off.log` | 250803 | **600** | **THE GUARD FIRES.** An instrument that can be made to say FAIL |
| S2b `VIEWRESTORE=1` | `run_295_S2b_restore_on.log` | 213951 | **0** | ARM 1 removes the class |

**ARM 1 AND ARM 2 ARE BOTH GREEN, AND ARM 2 HAS ITS FALSIFIER.** That is `295` §1 and §2 worn,
and it is what unblocks ARM 3 (§5's one stated reason for holding it back is now spent).

### §10.1 — AND THE ANSWER IS THE NULL ONE. **NO ENGINE READER WAS FOUND.**

The prompt's discriminator: the forced late read guarantees **exactly one mismatch per frame**, so a
cumulative `mismatch` at or near the frame count means only the forced read fired, and well above it
means real engine readers.

```
S2a cumulative: checks=1939916 mismatch=12000 outside=36200   frames=12000
```

**`mismatch == frames`, exactly.** And every `MISMATCH` line the run printed names the same site:

```
8 x  MISMATCH at forced-read-after-lvlRender
```

**`modelFindNodeMtx` does not appear. `projectileFindCollidingProp` does not appear. Nothing
appears but the probe the harness fires itself.**

**SO: over 12,000 frames of Dam, NOTHING IN THE ENGINE READ THE STALE VIEW PAIR IN `294` §3.6's
WINDOW.** `294` §3.6 asked whether a real reader exists. `[MEASURED]`: **not one that this level,
this route and 12,000 frames could produce.**

### §10.2 — WHAT THAT DOES AND DOES NOT RETRACT

- **ARM 1 STILL STANDS, AND IT IS NOT WEAKENED BY THIS.** It removes a class in which one
  coordinate system has two owners. A window with no measured reader is a window with no measured
  reader — it is not a proof that none exists, and the cost of closing it is two pointer writes
  after the loop. `294` §4's invariant is unchanged.
- **WHAT IS RETRACTED IS THE URGENCY, NOT THE MECHANISM.** Anywhere `294` or `295` reads as
  *"there is a reader and it is corrupting frames"*, that is now **`[INFERRED]` and unsupported.**
  The honest statement is: the mismatch is real, ARM 2 proved it can be detected, and no consumer
  of it has been found.
- **AND THIS IS EXACTLY WHY ARM 2 HAD TO BE WORN FIRST.** Had ARM 3 shipped in the same binary,
  the guard would have read `mismatch=0` and that zero would have been read as *"ARM 1 fixed it"*
  when it actually means *"the fault can no longer occur"*. `295` §5's argument was right and the
  run is what shows it was right.

**►► IT ALSO MEANS ARM 1 IS NOT THE FIX FOR ANYTHING THE OWNER CAN SEE.** The characters and props
missing from the second eye were never this class. That is ARM 3, and `297` is it.
