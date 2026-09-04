Read `repo\docs\00-STATE.md` — the **currency line at the top** (it is `302` + `303` and it is the
whole handover), then **§3 OWNER ACTION OUTSTANDING — the top FOUR entries are new**, then **§4
RETRACTED**, then **§6 TRAPS**. Then **`RUN-SHEET-303` §0 and §0.1 — between them they are the
entire session in two tables and three measured numbers.** Then **§1 onward.** Then
**`PRIORITY-BOARD-299`**, where the work goes after the arms.

Same rules as always. **You work OFFLINE. The build, every run and every commit are the owner's,
on the main PC. Supply complete copy-paste PowerShell blocks; quote a run-sheet block verbatim,
never paraphrase it. Never stage, commit, branch, merge or tag.** Bridge reads are not free
(`00-STATE` §6): `git log`, `git show` and `git diff <path>` are safe; `git status` and `git add`
are **NOT** (use `git --no-optional-locks status`), and **a bare `git status` in the decomp prints
2,106 CRLF-dirty files — always give it a path list** and pass `--ignore-cr-at-eol`.

---

## ►►►► WHERE THINGS ACTUALLY STAND ◄◄◄◄

**`301` AND `302` ARE BOTH WORN IN FULL. `303` IS WRITTEN, GATED, AND NOT BUILT.** Ten of ten
offline gates pass, `regen` has been run and `verify` reads `15/15`. The binary in
`getv\build-windows\` is **`302`'s** — `DF5CAB2A...1438`, `18,068,657` bytes — and **it does not
contain any of `303`'s work.**

**TWO THINGS ARE NOW MEASURED THAT WERE PREVIOUSLY ASSERTED, AND BOTH REVERSE SOMETHING WRITTEN
DOWN AS SETTLED.**

### 1. The near depth-clamp fix WORKS, and it took the far plane down with it.

`301` §5, `[REPORTED]`, the owner's eyes: **D1 artefact GONE, D2 artefact PRESENT.** `299` §8.1
CLOSES. But `299` §8.1 stood **BOTH** of `gfx_pc.c`'s per-vertex clamps down on an argument
measured at the **NEAR** plane only, and `302` §4 measured what that cost at the far one:
**`beyond_far=16534203` — 13.2% of 125.5M vertices**, against `301` D1's 0.7%, with
`all_far(hw-rejects)=0` and `clamped=0`. Owner: *"foggy after a certain distance and its
flickering"*, *"all the characters and cars etc are transparent and flickering"*, *"it is much
less view"*.

**►►►► AND THAT RUN WAS MONO. DO NOT GO BACK TO THE EYE LOOP FOR IT.** The owner's words were
*"almost like both eyes from before are now layered over each other"*, but `dlgrab_D3_33362.txt`
has **ONE** viewport load and the log carries no `[getv][stereo]` banner at all. **There is no
second eye in that run to layer.** It is z-fighting: past the far plane geometry is neither
rejected nor pulled to `z==w`, so every fragment lands on the same maximum depth.

### 2. The prop the second eye loses is the VIEWER, and it is NOT benign.

`302` §3: cumulative **`viewer=541`**, every other bucket zero, on a run whose four population
states reproduced `301` S2 **to the frame**. `302` §3c's own table then said `viewer=` meant
BENIGN, on `item 4`'s authority — **and the disproof was already on disk when that row was
written.** `dlgrab_eyecensus` on `grabs_302_S3` frames `1155`/`1243`/`1381`:

```
gSPSegment MODEL_MTX(3)   eye0 38   eye1 0     <-- DIVERGES
gSPSegment MODEL_VTX(4)   eye0 16   eye1 0     <-- DIVERGES
DL CALL targets           eye0 21   eye1 3      only in eye1 = 0
```

`only in eye1 = 0` makes it a **one-directional loss**, not a divergence. **`item 4`'s "the viewer
is already per-eye" is FALSIFIED**: `chrpropRender()` sends `PROP_TYPE_VIEWER` to
`bondviewRenderProp()` (`chrprop.c:884`), which is four lines and forwards to `chrRenderProp()`
when `chr` is non-NULL (`bondview2.c:11666`). **A viewer prop with a chr renders exactly like a
chr.** `293` §2.1 measured the **VIEWMODEL's** allocation — a different object. **GROUP `B1` is
fully answered and `B2` is REAL, with a scope of exactly one type.**

---

## ►►►►►►►► THE FIRST ACTION: `RUN-SHEET-303`, FROM §1. ◄◄◄◄◄◄◄◄

§1 the ten gates → §2 **THE REGEN, WHICH IS OWED THIS TIME** → §2c the binary identity → §3 the
V1/V2 viewer A/B → §4 the FC1/FC2 far-clamp A/B → §5 the commits (which may be run first).

**►► §2 IS WHERE THIS SESSION'S FIRST TRAP IS, AND IT IS THE OPPOSITE OF LAST SESSION'S.** `302`
had **no** regen step and said so in bold. **`303` DOES: `gfx_pc.c` is GITIGNORED and its change
exists only in `getv/patches/thirdparty/0001-getv-port-layer.patch`.** Do not carry `302`'s habit
across. The regen has already been run offline, so `verify` reading `15/15` is the gate; run
`regen` again only if it says `DIFFERS`.

**IF THE OWNER HAS ALREADY RUN SOME OF IT, ASK WHICH GATES PRINTED WHAT BEFORE ASSUMING ANYTHING.**

---

## ►►►► WHAT IS DIFFERENT IN THE LOG, AND WHY OLD NUMBERS ARE NOT COMPARABLE ◄◄◄◄

| line | what changed |
|---|---|
| `[getv][stereo][rebuild] SUMMARY ... chr=N obj=N view=N skipped=...` | **`view=` IS NEW AND IT JOINED THE BALANCE.** `chr+obj+view+skipped == zsnap`, never `chr+obj+skipped` |
| `WINDOW ... rebuilt(chr+obj+view)` | `view` counts as rebuilt, or every frame the fix repairs still reads ZERO-REBUILD |
| `[getv][stereo][rebuild] GETV_STEREO_REBUILD_VIEWER=<n>` | new knob, default `1` |
| `[getv][farclamp] GETV_FARCLAMP=<n>` | **new banner on a PRE-EXISTING knob that was silent and load-bearing at the same time** |
| `[getv][depthclamp] ... ONLY THE **NEAR** ... STANDS DOWN` | it used to say BOTH stand down. **That sentence was false and a false banner is what this project hunts** |

---

## ►►►► THE THING THIS SESSION SHOULD BE MOST CAREFUL ABOUT ◄◄◄◄

**A FILED FIX IS A DIAGNOSIS, NOT A PATCH — AND THE COUNT IS NOW FOUR.** `H1`, `H3`, `298` §4.4,
and **`302` §3c's own "viewer = benign" row, written one section after `301` stated the rule.**
Every one of them was caught the same way and it was never by re-reading the note: **follow the
call.** `bondviewRenderProp` is four lines and nobody had opened it in three sessions.

**AND `H4` HAS NOW COST THREE OWNER CYCLES** — `GETV_FILTERING` two, `GETV_FARCLAMP` one. A knob
that is **silent AND load-bearing** is the shape that bites; `302` §4's far field went a whole run
with no explanation in the log for exactly that reason. **When ranking the ~323 remaining silent
knobs, rank by "does this knob change what is DRAWN", not by how often the docs mention it.**

---

## ►►►► THE BEST METHOD FIND IS THE OWNER'S, AND IT IS WORTH MORE THAN EITHER FIX ◄◄◄◄

**The character introduction video LOOPS**, shows the far-field fault plainly, and is reached
deterministically: start the level, die, let it restart. **A fixed camera on a repeating sequence
removes the "were you standing in the same place" objection that dogged `301` D1/D2** — where the
SCENE counters were only comparable once normalised per-Mvtx (`straddle` 341 vs 340; D1 ran 14%
longer). `303` §4 uses it as the A/B venue.

**►► AND IT IS THE BEST CANDIDATE THE PROJECT HAS FOR `H9`'s REFERENCE FRAME**, which has been
open since `299` for want of exactly this: a known-good picture that does not depend on where
anyone stood. **Consider naming it as such deliberately — but not at the end of a session.**

---

## ►►►► AFTER THE ARMS: WHERE THE WORK GOES ◄◄◄◄

- **`303` §3c closes or re-opens GROUP B**, and `B3` is mostly done by V1's own grabs. **A partial
  admission — eye1 non-zero but under 38 — is NOT a pass.**
- **GROUP C**, the `NaN`. `HIGH`, precondition none, **untouched since `299` §8.4** and now the
  largest unexamined thing on the board.
- **`H4`'s banners**, re-ranked as above.
- **GROUP D** unblocked, `D1` is `LOW`. **`H9`** — see the loop, above.

---

## ►►►► HOUSEKEEPING THAT WILL BITE IF IGNORED ◄◄◄◄

- **`302` §5's COMMITS WERE NEVER RUN, so the tree carries `302` AND `303` together.** The
  `COMMIT-MESSAGE-2026-09-03c-*.txt` files are **SUPERSEDED** and each `-d-` message carries its
  `-c-` text verbatim at the end. **Use the `d` files only.**
- **`RUN-SHEET-303` §5's add lists were WRONG ONCE and are now gated by §5.0.** They were written
  for `303`'s three files and not widened when `302` merged in, so they dropped
  `src/game/ge_rebuild_window.h` and `getv/tools/ge_rebuild_window_harness.c`. **Check the staged
  set against the dirty set before staging anything.**
- **`gfx_pc.c` IS GITIGNORED and cannot be staged.** The patch is the only record. `verify` `15/15`
  is the proof, and it must read that BEFORE the `git add`.
- **PowerShell 7.** `Select-String -Encoding Byte` does not exist and throws; scan a binary with
  `[System.Text.Encoding]::Latin1.GetString([System.IO.File]::ReadAllBytes($exe))`.
- **`build_windows.ps1` lives in `getv\`, not the repository root**, and the binary lands in
  `getv\build-windows\`.
- **`EXPECTED-EXE-303.txt`** is written by §2c and every arm throws on a mismatch. **`302`'s binary
  was `DF5CAB2A...1438 18068657` — a `303` binary that matches it is the `302` binary and the edit
  did not take.**
