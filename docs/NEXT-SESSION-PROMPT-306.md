> # ►►►► SUPERSEDED 2026-09-04 BY `NEXT-SESSION-PROMPT-307`. KEPT IN FULL, RULE `2`. ◄◄◄◄
>
> **AND ONE SENTENCE IN IT IS FALSE AND WAS FALSE WHEN IT WAS WRITTEN:** *"`RUN-SHEET-304` IS NOW
> WORN IN FULL AND NOTHING IN `305` IS COMMITTED YET."* **`[MEASURED]` 2026-09-04 from `git log`:
> `689b009` (native) and `e58e1f1` (`GoldenEyeVR`) are IN and both trees are clean.** `306` §0.
> **`git log` is a bridge-safe read and it costs one command** (`00-STATE` §6).
>
> **AND `RUN-SHEET-304` §2a — carried here as *"still owed"* — had ALREADY BEEN RUN** at
> `2026-09-03T23:48:34Z` as `ARM=P1`, nine gameplay grabs, clean provenance, unread. `306` §2.

Read `repo\docs\00-STATE.md` — the **currency line at the top** (it is `304` §2 WORN, and it is
the whole handover), then **§3 OWNER ACTION OUTSTANDING — the top SIX entries are new**, then
**§4 RETRACTED — FOUR new, and the first of them narrows a sentence THREE documents leaned on**,
then **§6 TRAPS — FIVE new.** Then
**`305-THE-CENSUS-COMPARES-SETS-AND-BOTH-DL-EXPLANATIONS-ARE-NOW-DEAD` §0**, which is one table
and is the state of play, **and §2a, which is an arm nobody had read.** Then **`RUN-SHEET-305`
§1 and §2.** Then **`PRIORITY-BOARD-299`**, where **GROUP `C` has a new header and `C1` has been
RE-AIMED**, `H13` is struck through, and `H15` is new.

Same rules as always. **You work OFFLINE. The build, every run and every commit are the owner's,
on the main PC. Supply complete copy-paste PowerShell blocks; quote a run-sheet block verbatim,
never paraphrase it. Never stage, commit, branch, merge or tag.** Bridge reads are not free
(`00-STATE` §6): `git log`, `git show` and `git diff <path>` are safe; `git status` and `git add`
are **NOT** (use `git --no-optional-locks status`), and **a bare `git status` in the decomp prints
2,106 CRLF-dirty files — always give it a path list.** **►► AND `--ignore-cr-at-eol` IS A
`git diff` OPTION: `git status` REJECTS IT and the block stops there** (`[MEASURED]` 2026-09-03,
`RUN-SHEET-305` §5). Two rules, two commands.

---

## ►►►► WHERE THINGS ACTUALLY STAND ◄◄◄◄

**`RUN-SHEET-304` IS NOW WORN IN FULL AND NOTHING IN `305` IS COMMITTED YET.** `305` built no
binary, ran no game and staged nothing. Binary unchanged: **`45756E5A…3F92`, 18,070,774 bytes**.
`RUN-SHEET-305` §5 has the two commit blocks and `COMMIT-MESSAGE-2026-09-03h.txt` /
`-native.txt` are written in the `GoldenEyeVR` root.

### 1. THE CENSUS COMPARES **SETS**, AND THAT IS WHY `4676` READ PERFECT FOR THREE SESSIONS.

`dlgrab_eyecensus.py:96-97` is `set(a['calls']) - set(b['calls'])`. **A frame whose two eyes call
the same display lists in a DIFFERENT ORDER scores `only in eye0 = 0`, `only in eye1 = 0` and
reads PERFECT.** `dlgrab_C1_4676` is such a frame — **DL calls `[29..36]`, eight of them, a cyclic
rotation by three** — and `303` §5, `304` §0, `00-STATE`'s currency and `PRIORITY-BOARD-299`
GROUP `C` all quoted that census as the evidence. `getv/tools/dlgrab_dlorder.py` is the ordered
read; **`--selftest` 7 checks 0 failed and check `B` fails on any set-based implementation.**

### 2. THE REORDER IS REAL, DATED, AND IT DRAWS NOTHING — AND THAT SECOND HALF IS THE POINT.

Over **all 256 dumps**: 168 refused, 52 admission, 32 order-identical, **4 permuted**. Three carry
the identical signature on two binaries and two address spaces, and two of those three
(`dlgrab_2928`, `dlgrab_2957`) are announced by **exactly one log** — so **it predates `303` §2's
viewer fix, on admissible provenance, with no run.** **AND BOTH READ `total 0 px  blobs 0` UNDER
`stereo_eyediff.py` WHILE CARRYING IT IN FULL.** Zero, not "under threshold".

**IT WAS ONE KEYSTROKE FROM BEING FILED AS `4676`'s CAUSE. `279` §7 — pointing a NEW EXPLANATION
at the frames it should be boring on — is the only reason the count of wrong filed fixes is still
five and not six.**

### 3. ►►►► SO THE DISPLAY LIST IS EXHAUSTED, AND THE SEARCH SPACE IS FINALLY SMALL.

`C1_2336` and `V1_2732` — the two frames that carry the polygon — are **ORDER-IDENTICAL**, command
for command, every difference a `w1` segment rebase. Four levels are now excluded **by
measurement**: admission (`303` §5), the matrix conversion (`303` §4), the arena (`305` §1.2), the
order (`305` §1.5).

**EVERY ONE OF THOSE IS SOMETHING `GETV_DLGRAB` RECORDS, AND IT RECORDS `w0` AND `w1` — OPCODES
AND ADDRESSES. NOTHING IN THIS PROJECT HAS EVER READ A PER-EYE BUFFER'S *CONTENTS*.** Two eyes can
issue byte-identical commands naming per-eye matrix buffers whose **values** differ, and every
instrument on this board would call that frame perfect. **That is the description of `2336`.**

---

## ►►►►►►►► THE FIRST ACTION: `RUN-SHEET-305` §1. IT IS OFFLINE AND IT COSTS SECONDS. ◄◄◄◄◄◄◄◄

**Every number in `305` was measured on the BRIDGE's `python3 3.10.12`, not the main PC's `py`.**
That is `H7` exactly, and `H7` was opened because `292`'s link wall proved the two environments
disagree. §1 has four gates:

1. **`--selftest` reads `7 checks, 0 failed`.**
2. **Exactly ONE of the fourteen `C1`+`V1` dumps comes back `PERMUTATION`, and it is `4676`** —
   `span [29..36]`, `CYCLIC ROTATION of 8 calls by 3`. **`2336` and `2732` must read `ORDER
   IDENTICAL`.**
3. **`dlgrab_2928` and `dlgrab_2957` are `PERMUTATION` AND `total 0 px  blobs 0`.** This is the
   falsifier and it is pre-registered: **a non-zero pixel count on either retracts `305` §1.4 and
   puts the reorder back on the board.**
4. **The arena reads `MODEL_MTX fresh=3` / `MODEL_VTX fresh=0`, and the two `MOVEMEM` lines share
   ONLY `0386`/`0388`** — the lights. A match on `0380`, `0382` or `0384` means `305` §1.1's null
   is wrong.

**►► NOTHING IN `305` IS QUOTABLE FORWARD UNTIL THOSE PASS. Then §2, which bounds the falsifier
across the corpus and is also offline.**

---

## ►►►► THE ONE THING THAT NEEDS A PERSON: `RUN-SHEET-305` §4 ◄◄◄◄

**`RUN-SHEET-304` §3 WAS RUN AND ITS COUNTERS ARE NOW READ** (`305` §2a, per window, because the
cumulative line is `H12`-void). **The knob took at full strength in ALL 467 windows
(`clamped == straddle`) and the venue WAS the road — median 1,359 clamped/Mvtx against the cast
roll's 45,000 — so `303` §3.2's venue objection does NOT apply this time.** Per-window
`beyond_far` spans 0–21%, medians 3.81% (FC3) / 5.47% (FC4), and only 3% / 7% of windows land
inside §3's own 3.9–5.9% band, which is `H12` one level down.

**THE COUNTERS CANNOT DECIDE IT AND `303` §3 SAYS SO. ONE SENTENCE ABOUT EACH ARM, IN YOUR OWN
WORDS.** If the two looked the same again, **`RUN-SHEET-303` §0.1 is a `279` §7 null for the
SECOND time and should be CLOSED rather than re-run a third.**

---

## ►►►► THE THING THIS SESSION SHOULD BE MOST CAREFUL ABOUT ◄◄◄◄

**`305` DREW TWO RETRACTIONS OF ITS OWN AND WITHDREW A THIRD BEFORE FILING IT.** The withdrawn one
is the instructive one: every log pairs `[getv][dlgrab] frame N` with `[getv][shot] frame N+1`,
14 of 14, and read as two frames that voids *"SAME COMMANDS, DIFFERENT PICTURE"* everywhere it
appears. **It was drafted as this session's headline retraction.** Following the call —
`port_render.c:748-759` and `gfx_opengl.c:1495-1520` — shows the pair is the same frame by
construction and `fno` is a private counter. **A CONSISTENT offset is a label mismatch; a real
off-by-one is not consistent in all fourteen pairs.**

**`301` §0's rule, at its fifth instance and still holding: MEASURE BEFORE YOU FILE, ESPECIALLY
WHEN THE EVIDENCE IS GOOD.** The rotation was the most convincing thing this project has found in
three sessions and it draws nothing.

**AND THE SMALLER ONE, WHICH COST AN OWNER CYCLE: `304` §3 AND §4 WERE CARRIED AS "STILL OWED" IN
TWO DOCUMENTS WHILE THE LOGS AND GRABS WERE ALREADY ON DISK.** A run sheet's owed list is a claim
about the filesystem. **`ls grabs_*` and `ls run_*.log` before repeating an arm.**

---

## ►►►► AFTER §1 AND §2: WHERE THE WORK GOES ◄◄◄◄

- **THE NEXT INSTRUMENT — a per-eye read of `MODEL_MTX` CONTENTS, not addresses.** `305` §4. It
  is the only level left for the polygon and `305` deliberately does not design it: **`301` §0,
  and a hole's filed fix is a diagnosis, not a patch.**
- **`C1` IS RE-AIMED AT `dlgrab_C1_2336`, NOT `4676`.** `4676`'s extra defect is measured, dated
  and harmless, so it is the frame with the most NOISE in it, not the most signal. **`2336` is the
  polygon with nothing else in the frame.**
- **`RUN-SHEET-304` §2a** — date the **polygon** with a run. Still owed; `305` dated a different
  fault.
- **`H15`** — decide whether the order check belongs inside `dlgrab_eyecensus.py` or stays a
  sibling. `304` §1.2 is the precedent for editing an instrument; `H8` is the argument for two.
- **`H12`** — applied by hand in `305` §2a and still not in the code. **A windowed accumulator for
  `[getv][far]` would have made that section a `Select-String`.**
- **`H11`, `H14`, `C1a`** unchanged. **GROUP `D`** unblocked, `D1` `LOW`. **GROUP `E1`** has now
  survived four arms untested.

**`169` NEXT ID = `U-26`.**
