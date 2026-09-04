Read `repo\docs\00-STATE.md` — **§3 OWNER ACTION OUTSTANDING (the top FOUR entries, all new)**, and
**§3 OPEN item 0, which is the owner's own sentence and outranks everything else in the file**; then
**§4, which now retracts `297` §10 in its entirety**, then **§6 — six new traps, and four of them
are about how a crash is read**. Then **`297` §11 and §12 IN FULL** — §11 is the retraction and the
method that replaces it, §12 is a live pre-existing crash. Then **`RUN-SHEET-297` §5 onward**.

Same rules as always. Bridge reads are not free (`00-STATE` §6): `git log`, `git show` and
`git diff <path>` are safe; `git status` and `git add` are **NOT**, and **a bare `git diff` in the
decomp prints ~2,100 lines of CRLF churn, so always give it a path list** — and pass
`--ignore-cr-at-eol`, or every one of those files reports as wholly changed. The build, every run
and every commit are the owner's, on the main PC — **you write and validate OFFLINE, then supply
complete copy-paste command blocks (§7a). Quote a run-sheet block, never paraphrase it; take a
revert's file list from `git show --stat --name-status <sha>`. Both cost the owner a wasted build
cycle on 2026-09-02.**

---

## ►►►► WHERE `297` ACTUALLY STANDS. READ THIS BEFORE RANKING ANYTHING. ◄◄◄◄

**R0 IS GREEN.** `[MEASURED]` 2026-09-02: a full mono session — shooting characters, walking,
returning — with no crash, 39 MB of log. The R0 crash was **`chr.c:3305`, an `if (headSwitchVisible)`
written twice**; the `else` bound to the inner `if`, so an off-screen chr never cleared
`PROPFLAG_ONSCREEN` while its `field_20` joint list had already been nulled, and `chrTestHit` walked
NULL. Fixed, built, worn.

**`297` §10 IS RETRACTED IN FULL.** `objBuildRenderState + 199` was never the crash and that function
is not on the R0 stack at all. If you find yourself reasoning from it anywhere, stop and read §11.1.

**§5 (R1) AND §6 (R2) HAVE NEVER BEEN RUN. ARM 3 HAS NEVER RENDERED A FRAME.**

---

## ►►►►►►►► THE ONE QUESTION THIS SESSION EXISTS TO ANSWER ◄◄◄◄◄◄◄◄

**Are the characters and the props in BOTH eyes, and do they stay put?** Not a disparity number, not
a frame time. This is `00-STATE` §3 OPEN item 0, it is the owner's own sentence, it has been reported
after `292`, `293` and `295`, and **R2 is the first time in the project's history that the code
which is supposed to fix it will actually execute.**

`RUN-SHEET-297` §5 (R1, the negative arm — `REBUILD=0`, the broken picture on purpose) then §6 (R2,
`REBUILD=1`, the arm itself). **The sheet is complete and self-contained. Hand the owner the blocks
in order and do not rewrite them** — the last three sessions each rewrote the previous session's
sheet instead of running it, and `296` §11 defect 1 is what that costs.

**►► TWO THINGS THE SHEET DOES NOT YET SAY, AND BOTH MATTER:**

1. **DO NOT SHOOT A MINE in R1 or R2.** It crashes, it is **pre-existing**, and it is **not ARM 3's**
   — `297` §12, proven against `build-windows/goldeneye_PARENT.exe`. A mine crash mid-arm will look
   like ARM 3 failing and it is not.
2. **Leave `GETV_CHR_DEBUG=1` and `GETV_HIT_DEBUG=1` on.** They cost a little log volume and they
   are the instruments that named the R0 bug after three rounds of theory failed.

**IF R2 CRASHES, THE FIRST SUSPECT IS THE ARENA, NOT THE EYE LOOP.** `292` §1 doubled both pools so
two eyes could each allocate, and **until ARM 3 the second eye allocated nothing — the ×2 has never
been spent.** Overflow is silent. `GETV_GFXPOOL` is the lever. `297` §5's `rebuild] SUMMARY` /
`rebuild] GATE` census says which of three things happened: the driver did not run
(`eyes-rebuilt=0`), it ran and admitted nothing (`chr=0 obj=0 skipped=N`), or it ran and what it
built did not reach the screen (counts non-zero, picture unchanged). **Three different bugs, three
different next moves.**

---

## ►►►► HOW TO READ A CRASH IN THIS PROJECT. THIS IS NOT OPTIONAL ANY MORE. ◄◄◄◄

Three rounds and two impossible fixes were spent because the base was assumed instead of derived.

1. **`grep -n "EXCEPTION" <run log>` FIRST.** The port prints `===== EXCEPTION 0xc0000005 =====`,
   `fault addr:` and `FAULT PC:` and has done all along. `FAULT PC` is the leaf for free.
   **`fault addr` decides the shape of the fix** — small (< `0x10000`) is a NULL-plus-offset deref
   and wants a NULL guard; large and unaligned is a **WILD pointer** and a NULL guard is worthless.
2. **DERIVE the load base.** Every non-leaf frame is a RETURN address — the byte after a `call` —
   which is base-independent. `objdump -d --no-show-raw-insn goldeneye.exe > dis.txt` (under a
   second), collect every post-`call` address, and keep the only 64 KB-aligned base where **every**
   caller frame lands on one. **Exclude the leaf from the fit.** Cross-check against `FAULT PC`.
3. **A leaf landing mid-instruction means the base is wrong.** Nothing else.
4. **Never `objdump -d --start-address=<arbitrary>`** — it desyncs the decoder and invents
   instructions. Confirm against the linear dump.
5. **A correct base gives a call chain that reads as a sentence.** Huge symbol offsets and a chain
   that makes no structural sense are the tell that it does not.

---

## ►►►► AFTER R2 — THE TWO ITEMS THIS SESSION DELIBERATELY DID NOT START ◄◄◄◄

**Neither is ARM 3's, and neither should be touched until R2 has been read.**

**1. THE MINE CRASH — `297` §12.** `vtxstore.c:161` filters `type == 1` (**`PROP_TYPE_OBJ`**) and
then reads `PropRecord`'s tagged union as a **`ChrRecord *`**. `bondconstants.h:3930` —
`NUL=0, OBJ=1, DOOR=2, CHR=3`. An ObjectRecord read through `ChrRecord.model` (+`0x20` native) lands
on a float; `0xbdccc577` is ≈ `-0.1f`, which is the wild pointer in the fault address.
**TWO CANDIDATE CORRECTIONS AND THEY ARE NOT EQUIVALENT:** (1) the filter is wrong —
`type == PROP_TYPE_CHR`, keeping the cast; or (2) the cast is wrong — keep `PROP_TYPE_OBJ` and read
`var_s1->obj->model`, whose `Model *` is at a different offset. **Which matches the N64 original is
UNRESOLVED, and guessing trades a loud crash for a silent wrong-model bug.** The prior art in
`local-only/prior-art/perfect_dark_VR` is the obvious place to settle it. Marked in the source at
`vtxstore.c`, above `sub_GAME_7F09BAC4`.

**2. THE EXPLOSION TEXTURE — owner `[REPORTED]`, 2026-09-02, and it goes in §3 in their words
(`00-STATE` §7b2):** *"that texture shows weird, it doesn't show the proper explosion. On the normal
emulator version and on the TLb version it does show properly."* The owner also asks whether a
**different explosion texture can be substituted and used in the game.**
**►► DO NOT TREAT THIS AS AN ASSET PROBLEM UNTIL ONE THING IS CHECKED.** `sub_GAME_7F09BBBC`
(`vtxstore_tick`) — the function that crashes in item 1 — **merges duplicate vertex batches and
rewrites model references**, and `7a4e7bfd` records that `propobj.c:7750`, the rwdata-stride
**explosion** crash site, was in the same family of pointer-size errors. **Establish whether the
texture is wrong or merely being fed the wrong data first**; substituting the asset while the second
is true only hides it. `[getv] texbind model` and `[getv] gdltally` census lines are already in every
run log and are the cheap first read.

---

## THE STANDING RULES THIS SESSION ADDED, ALL IN `00-STATE` §6

- **A check for what was LOST cannot find what was DUPLICATED.** ARM 3's extraction was verified by
  a whole-file multiset diff against the parent; it reported one line lost, was declared clean, and
  **the bug was an added line sitting unread in the additions column.** Diff both directions. The
  build runs `-w`, so `-Wdangling-else` will never do it for you.
- **A type tag and its union member are one fact.** When a walker tests a raw integer instead of the
  `PROP_TYPE_*` name, check which union member the body then uses.
- **Save the `.map` beside every binary you keep.** `goldeneye_PARENT.map` / `goldeneye_ARM3.map`
  exist because a rebuild overwrites `goldeneye.map` and strands every earlier backtrace — and
  keeping `goldeneye_PARENT.exe` is what proved the mine crash pre-existing **without a rebuild**.
- **Quote run-sheet blocks; take file lists from `git`.** Two wasted owner cycles on 2026-09-02.
