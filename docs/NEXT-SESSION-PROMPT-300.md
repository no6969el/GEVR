Read `repo\docs\00-STATE.md` — **§3 OWNER ACTION OUTSTANDING (the top THREE entries, all new)**,
**§3 OPEN item 0, which is now ANSWERED and says so**, then **§4, which retracts THREE things and
two of them are `298`'s own instruments**, then **§6 — four new traps, and three of them are about
a counter that was read outside the branch it belongs to.** Then **`299` §8 and §9 IN FULL** — §8
is the five worn arms, §9 is the code that was written afterwards and NOT BUILT. Then
**`RUN-SHEET-300` §1 → §7 in order.** Then **`PRIORITY-BOARD-299`**, which is where the work goes
after this build lands.

Same rules as always. Bridge reads are not free (`00-STATE` §6): `git log`, `git show` and
`git diff <path>` are safe; `git status` and `git add` are **NOT** (use
`git --no-optional-locks status`), and **a bare `git status` in the decomp prints 2,106 CRLF-dirty
files — it did this session — so always give it a path list** and pass `--ignore-cr-at-eol`.
The build, every run and every commit are the owner's, on the main PC — **you write and validate
OFFLINE, then supply complete copy-paste command blocks (§7a). Quote a run-sheet block, never
paraphrase it.**

---

## ►►►► WHERE THINGS ACTUALLY STAND ◄◄◄◄

**THE OWNER'S #1 SYMPTOM IS SOLVED AND THE FIX IS WRITTEN BUT NOT BUILT.** `[MEASURED]` 2026-09-03:
the A→B→A passed — clamp ON the artefact is present, clamp OFF it is absent with `straddle=8666`,
clamp ON it returns — and **grabs exist in all three arms**, which is the gate arm F failed.
`gfx_pc.c:3733` named the fix and `299` §9 implements it: `ge_depthclamp.{c,h}`, new and tracked,
plus four lines of hook in two regenerated files.

**NOTHING IS BUILT. THE BRIDGE HAS NO GL HEADERS**, so the GL path of `ge_depthclamp.c` has never
been through a compiler — the harness covers the two decisions that can be silently wrong, and the
build is the gate. `HEAD` is `3de0db0` / `e380916` / `1f0f7aae` and `goldeneye.exe` is still
`2026-09-02 19:29`.

---

## ►►►►►►►► THE FIRST ACTION: `RUN-SHEET-300` §4. THE BUILD IS ALREADY DONE. ◄◄◄◄◄◄◄◄

**`299` STOPPED AFTER THE BUILD. §1, §2 AND §3 ARE WORN AND DO NOT NEED RE-RUNNING.**
`[MEASURED]` 2026-09-03 02:40: the regen ran (the patch is modified and carries the four lines of
hook), the build succeeded (`59` port-layer objects, **0 failed in every group**), `goldeneye.exe`
is **18,062,771 bytes** at `02:40`, and `goldeneye_300.map` is saved beside it.
**`ge_depthclamp.o` is in `libge.a` with `0x360` bytes of `.text`, all three symbols at real
addresses, and its GL references resolving to `glIsEnabled` and `glGetError`** — so the glob saw
the new file and the verify path was not dead-stripped. All six new strings are in the binary.

**►►►► AND NONE OF THAT IS A RUN.** Whether the driver accepts `glEnable(GL_DEPTH_CLAMP)`, and
whether the owner's *"you can see through the wall to the jeep"* actually goes away, is **§4's
question and only §4's**. `279` §7: a string in a binary is not a result.

**START WITH D1. ITS FIRST LOG LINE ANSWERS THE FIRST QUESTION** — the banner is written to say
`GL_DEPTH_CLAMP ON (core 3.2+, GL_VERSION=...)` or `UNAVAILABLE (<why>)` by name. On an RTX 5090
reporting `4.6.0`, `UNAVAILABLE` cannot legitimately happen, so it would mean the version parse or
the enable failed — **a code fault, not a driver one, and the harness has 17 checks that say it
should not.**

**THEN THE CENSUS, WHICH PROVES THE FIX WITHOUT ANYONE'S EYES:** D1 must read **`clamped=0` on
BOTH planes with `straddle` in the thousands** — that double zero is the banner's receipt, not a
masked zero — and **D2 must reproduce `299` N1's shape exactly** (`clamped = straddle + all_near`).
If D2 does not, `GETV_DEPTHCLAMP=0` is not restoring the old path and the A/B is void.

**AND LOOK AT THE FAR FIELD IN D1.** `GL_DEPTH_CLAMP` disables z clipping at **both** planes, so
geometry once clipped at the far plane now rasterises clamped to maximum depth. **`298` §4.4's
`all_near` number is retracted (`00-STATE` §4) and cannot be used to measure this** — it is the
owner's eyes, and it is the one cost this change could carry.

---

## ►►►► THE COMMITS ARE DONE. NOTHING IS OWED THERE. ◄◄◄◄

`[MEASURED]` 2026-09-03, all three landed and checked with `git show --stat --name-status`:

| repo | SHA | contents |
|---|---|---|
| `vendor/ge-decomp` | **`77f67e26`** | `M src/game/chrprop.c` — one file, **no CRLF sweep** |
| `goldeneye-native` | **`6f24ddc`** | six paths, **including `getv/patches/thirdparty/0001-getv-port-layer.patch`** |
| `GoldenEyeVR` | **`fe93821`** | three message files + seven docs, nothing from `goldeneye-native/` |

**THE GATE THAT MATTERED IS MET: the regenerated patch is in the native commit**, so `gfx_pc.c`'s
and `gfx_opengl.c`'s four lines of hook are committed and a fresh clone regenerates them —
**`268`'s shape did not recur.** `tools/fetch-thirdparty.sh verify` reads **`15/15`** after the
commit, which together with the regen before it is the two separate facts `RUN-SHEET-300` §7.4
wanted. **Do not re-commit and do not re-run §1-§3.**

---

## ►►►► ARM 3 IS NARROWER THAN `298` SAID, AND IT IS NOT RETRACTED ◄◄◄◄

**True of gameplay frames. False of the level's opening ~541 frames**, where `[MEASURED]`
`MODEL_MTX 38→0`, `MODEL_VTX 16→0` into eye 1 on seven grabs, per-half texture energy ratio up to
**99x**. **It is NOT alternation** — fourteen grabs in the other arm are all equal-eyed — and **it
is deterministic**: two runs of different length report identical skip counts, 372 and 169.

**THE DEAD EYE IS A SKIPPED PROP.** Each dead frame's own census reads `chr=0 obj=0 skipped=1`
against the good frames' `chr=1 skipped=0` **at the same list size**. `299` split the one skip
counter into `flag=` and `type=` and **deliberately did not assert which fires** — one run
(`RUN-SHEET-300` §6) answers it, and the two answers mean opposite things:
**`type=` is a design gap; `flag=` falsifies a comment in the source that says it cannot happen.**

---

## ►►►► WHAT `299` MEASURED AND COULD NOT EXPLAIN ◄◄◄◄

**`arrays=144716 already-converted=11902`, every hit `eye=1`, and MOST OF THEM `NaN`** —
`m[0][0]=nan`, `m[3][3]=-5.07e30`. `292`'s non-idempotent `bondviewTransformManyPosToViewMatrix`
explains **saturation**; it does not explain a **NaN**, which is arithmetic on uninitialised or
freed arena memory. **The knob's own pre-registered null did not fire, so the attribution stands
for the saturation half and the NaN half is unowned.** `PRIORITY-BOARD-299` GROUP C.

---

## ►►►► THREE RETRACTIONS, AND TWO OF THEM ARE `298`'s OWN INSTRUMENTS ◄◄◄◄

1. **`298` §4.4's `all_near 50 → 548`** as the price of `GETV_NEARCLAMP=0`. That counter is
   incremented **outside** `if (nc)` and is knob-independent; `299`'s arms read **12 / 150 / 51**
   with the clamp ON / OFF / ON. **The "must not ship" conclusion survives on GL semantics; the
   number offered as its evidence measures nothing.**
2. **`298` §1.1's six `SUMMARY` lines as a census.** The counters reset every tick, so at
   `REPORT=600` each line is **one frame's snapshot**. Six spot checks looked green while 372
   frames per run were failing. **`=1` is the census. Always run `=1`.**
3. **"chr + obj vs list is a balancing sum."** The two are captured at different moments — 169
   frames per run read `list=1` with `chr=1` **and** `skipped=1`.

**AND ONE THING THIS SESSION GOT WRONG AND FIXED ITSELF:** it asked the owner which framebuffer
half was which eye. **`stereo.c:233` and `stereo.c:387` answer it — eye 0 is the LEFT half AND the
LEFT eye — and the question was withdrawn.** Rule `14`: do not ask the owner to read something the
source can print.

---

## ►►►► OWED, IN THE ORDER `RUN-SHEET-300` PUTS THEM ◄◄◄◄

- **~~§1 gates · §2 REGEN · §3 build~~ — ALL THREE WORN 2026-09-03 02:40. Do not re-run them.**
- **§4** D1/D2, `GETV_DEPTHCLAMP` 1 vs 0, same alley. **D1's `clamped=0` on both planes is the
  banner's receipt, not a masked zero. D2 must reproduce `299` N1 exactly or the A/B is void.**
  **And look at the far field in D1** — the extension disables z clipping at both planes.
- **§5** the filtering arm, finally runnable. **Gate is the banner reading `filtering=0`.**
- **§6** the skip split. One run.
- **§7** the commits, three repos, decomp first and by explicit path list.

**STILL UNRUN AND NOT THIS SHEET'S:** `RUN-SHEET-299` §3 (R3), §4 (R4/S3, **never run**), §4.3 (S4),
§5 (R5 cost), §6 (arm C's gun gate). All are spliced in full there. `297` §12's mine crash is a
new session's work and **DO NOT SHOOT A MINE in any arm.**

## RUN LOGS `299` PRODUCED

`run_299_N1_nearclamp_on_A.log` · `run_299_N2_nearclamp_off_B.log` (**a re-run overwrote the
original — no evidence lost, but the mtimes read N1, N3, N2, which is not the order they were
run**) · `run_299_N3_nearclamp_on_A2.log` · `run_299_E1_percensus.log` ·
`run_299_E2_mtxguard_observe.log`. Grabs in `grabs_299_N1/`, `_N2/`, `_N3/`, `_E1/`, `_E2/`.
