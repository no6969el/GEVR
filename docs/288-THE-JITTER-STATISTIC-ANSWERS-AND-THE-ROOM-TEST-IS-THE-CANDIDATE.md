# 288 — THE JITTER STATISTIC ANSWERS, `vsync=0` IS CLEARED, AND THE VANISHING PROPS ARE THE ROOM TEST

**2026-08-31. BUILT, RUN AND WORN. SIX ARMS, ONE BINARY.**
**Binary: `2026-08-31 17:09:32`, `18,035,038` bytes.** Predecessor `287`'s was `18,026,915` at
`02:24`. Run sheet: `RUN-SHEET-288.md`. Predecessor doc: `287`.

**THE SESSION IN ONE LINE:** three written-but-unbuilt changes were built and all ten binary
strings took; the jitter statistic was validated on hardware and then **cleared `vsync=0` at its
own resolution**; and `GETV_CULLWHY` **killed the `32000` radius, eliminated the room rectangle,
and promoted `getROOMID_isRendered` to the standing candidate for the vanishing props.**
**FOUR OF THIS SESSION'S OWN PREDICTIONS CAME BACK FALSE AND ARE RECORDED AS SUCH.**

---

## §1 — THE BUILD AND THE TEN-STRING GATE. **PASS.**

`build_288_jitter_panel.log`, zero errors, zero failures: game 165 built, assets 234, audio 40,
port layer 58, port c++ 2, `libge.a` 24.8 MB / 498 members.

All ten strings present: `GETV_ROOMSCISSOR` · `GETV_PROPCULLBOX` · `GETV_PACEHIST` · `SIX SITES` ·
`pacehist` · `PANEL REPORTED BY SDL` · `jitter: sd=` · `GETV_FPS=panel REFUSED` · `GETV_CULLWHY` ·
`twin-disagree`. **A knob that is not in the binary reads as a clean null result** (`133`,
`268` §4); none of them did.

---

## §2 — `GETV_FPS=panel` IS BUILT, RUN AND WORN. `[MEASURED]`, FIRST RUN.

```
[getv] GETV_FPS=panel -> 120 Hz, QUERIED FROM SDL [MEASURED] for the display
[getv] pace: 120 fps cap on (GETV_FPS), vsync=1
```
**The gate is two-part and both halves passed in J1 and J2:** the query line names its source, and
the `pace:` banner then carries that same number as the cap. **`GETV_SIMHZ=query` chained off it
for free** — `simhz 0.500000 fields per frame`, the `60/cap` ratio. **One env value is now correct
on the 120 Hz desk and on the 180 Hz one.** `48` holds: a numeric `GETV_FPS` behaved exactly as
before in V1, V2, ARM 8 and ARM 8b.

**AND ITS REFUSAL FIRED FOR REAL, IN V2, ON A DIFFERENT KNOB.** `GETV_SIMHZ=query` with
`GETV_FPS=0`:
```
[getv][simhz] CONTAMINATED -- rate is 0. Queried from ge_pace_framerate with the cap OFF
(GETV_FPS=0) there is no rate to divide by, and 60/0 is not a number. TERM STAYS OFF.
```
**It declined to invent a rate rather than defining a whole run against a wrong one, which is
exactly `285`.** Rule `17`, working, unprompted.

---

## §3 — THE JITTER STATISTIC IS VALIDATED ON HARDWARE. **AND BOTH ITS THRESHOLDS WERE WRONG.**

### V1 — POSITIVE CONTROL, `VSYNC=1 FPS=60`. `[MEASURED]` 17:22:06.
Panel **120 Hz**. Bins land where predicted, `panel/cap` = `2x`: **591/600, 598/600, 284/284**.
Gates clean, including `simhz 1.000000` — the `60/cap` ratio at `FPS=60`, exactly as `287`
defect (a) said it must read.

| window | `sd` | `jd` | `jdp` | `jdm` | outside `2x` |
|---|---|---|---|---|---|
| 1 (boot) | 15.617 | 2.735 | **32.8%** | 15.5% | **9** |
| 2 | 2.674 | 0.781 | 9.4% | 4.7% | 2 |
| FINAL | 0.418 | 0.479 | 5.7% | 2.9% | 0 |

### V2 — NEGATIVE CONTROL, `VSYNC=0 FPS=0`. `[MEASURED]` 17:27:48, 130 windows.
**No mode, as predicted, overwhelmingly:** `<0.5x` = 599/600, 600/600, 171/171. Mean 0.219 ms
(~4,500 fps). Settled `jdm` = **14.1%** and **14.5%**.

### ►►►► DEFECT 1, MINE: `jdp < 10%` WAS WRITTEN PER-WINDOW WITH NO BOOT EXCLUSION. ◄◄◄◄
V1 window 1 misses it at 32.8%. **The arm is not voided, and the reason is a cross-check, not a
judgement call:** the failure the contract exists to catch is *a hard-locked run reporting jitter
that is not there.* Window 1 carries **nine hitch intervals in the OLD bins** — an independent
signal, in the same window, that the statistic did not produce. **The figure is CORROBORATED.**
**CORRECTED CONTRACT: a jitter threshold is scored on SETTLED windows — every window after the
one containing boot. The boot window is REPORTED, NEVER SCORED.**

### ►►►► DEFECT 2, MINE: `jdm > 20%` WAS CALIBRATED OFF THE HARNESS AND HARDWARE FALSIFIED IT. ◄◄◄◄
`§3` took `> 20%` from the offline harness's uncapped stream, which returned **40.9%**.
**Real hardware returns 14.5%.** The synthetic ~0.25 ms stream is SCATTERIER than the real
uncapped loop, which is remarkably even (`sd` 0.059, `jd` 0.032 ms). **`§2` said in advance the
harness could not prove the pacer behaves like a synthetic stream. This is that limit firing.**

**WHAT SURVIVES, ON THE MATCHED METRIC — and mixing `jdp` with `jdm` is the defect `§3` exists to
prevent:** V1 settled `jdm` = 2.9% / 4.7%. V2 settled `jdm` = 14.1% / 14.5%.
**THE STATISTIC SEPARATES CAPPED FROM UNCAPPED BY 3-5x.**
**So *"it reads calm on the negative control and is measuring nothing"* IS NOT SUPPORTED, and
*"20% was the right number"* IS MEASURED FALSE. Two findings, NOT merged** (`263` §1).

### AND `sd` vs `jd` DISCRIMINATED ON HARDWARE, NOT ONLY IN THE HARNESS
V1 window 1: `sd` ~5.7x `jd` — the signature of a few large outliers, **not** of an alternation.
J1/J2 boot windows: `sd` 1.1-2.8 while `jd` holds 0.57-0.85. **The outliers move `sd` and leave
`jd` alone. That is the whole reason `sd` does not ship alone**, and it is now observed for real.

---

## §4 — ►►►► J1/J2: `jdp` CAME BACK EQUAL. `vsync=0` IS CLEARED AT THIS RESOLUTION. ◄◄◄◄

`[MEASURED]` 17:42:15 and 17:43:26, `GETV_FPS=panel` both arms, gates clean both arms.
**EVERY SETTLED WINDOW IS `600/600` IN `1x` IN BOTH.** Locked to the panel at 120.

| | settled windows | `jdp` range | **`jdp` mean** |
|---|---|---|---|
| **J1** `vsync=1` | 10 | 7.3 - 9.2% | **8.29%** |
| **J2** `vsync=0` | 8 | 6.9 - 8.5% | **7.70%** |

**The ranges overlap almost entirely; the gap is 0.59 points against a within-run spread of ~2
points; and `vsync=0` is the SLIGHTLY LOWER one — the opposite direction from the complaint.**

**`§7`'s WRITTEN OUTCOME FIRES: the smoothness complaint is NOT in the presented-frame interval,
even at jitter resolution.** That closes what `287` 4E opened and what `288` was built to answer.
**THE CARRIER IS THE SIM — `GETV_SIMHZ`, which `287` ALREADY NAMED as the untested carrier of
`285` S1's *"super smooth."* IT IS NOW THE ONLY CANDIDATE LEFT STANDING.**

**`jdp` ~ `jdm` in every window** — trivially, because cap == panel, so the window mean IS the
panel period. A free internal consistency check, and it passes.

### TWO SCOPE LIMITS, RECORDED RATHER THAN GLOSSED
1. **NOT WINDOW-MATCHED, AND `§7` DEMANDED IT.** J1 = 13 windows, J2 = 10, 23% apart. **Little
   leverage here** — the statistic is per-window and stable within each run, and both have >= 8
   settled windows — **but ACTIVITY matching cannot be verified from a log at all.** Only the
   session lead knows. **Stated, not assumed.**
2. **ALL FOUR PACING ARMS RAN WITH `GETV_ROOMSCISSOR=0`, A RENDERING FALSIFIER** — rooms overdraw
   each other, so the GPU is doing MORE work than the shipping configuration. Consistent across
   V1/V2/J1/J2, so the comparison between them holds. **It is not a description of the shipping
   picture's pacing.** `[REPORTED]` mid-session as *"dropping side textures and blue walls"* —
   which is the knob's own banner text, not a regression.

---

## §5 — ►►►► ARM 8 + 8b: `dist` IS DEAD, THE BOX IS ELIMINATED, AND `room` IS THE CANDIDATE. ◄◄◄◄

`[MEASURED]` 17:31:17 (`run_288_8_cullwhy.log`) and 17:36:22 (`run_288_8b_cullwhy_boxoff.log`).
**`twin-disagree=0` IN BOTH — the per-plane numbers are LIVE** (`271` §7, rule `17`).
Gates clean in both; all six `roomscissor` sites non-zero in both.

```
ARM 8   room=1134409 fog=12257 occl=2163 box=38996 dist=0 | drawn=36809
        planes: near=0     left=0      right=0      top=0     bottom=0
ARM 8b  room=1727224 fog=12463 occl=2494 box=0     dist=0 | drawn=55595
        planes: near=7310  left=15289  right=38400  top=4978  bottom=9831
```

### THE ACCOUNTING-BALANCE ARM PASSES, SO ARM 8's READING STANDS
**`box` dropped to 0 and the rejections REAPPEARED in the per-plane counts. They moved; they did
not vanish.** `§8e`'s own validation arm, and it was not optional.

### 1. `dist=0`. **THE `32000` RADIUS IS DEAD, AND NOW BY MEASUREMENT.**
Zero in both runs, in runs that reproduced the symptom. `§8d` said `[REPORTED]` fact 1 *"badly
damages"* it but refused to declare it dead on a report. **It is dead now.**
**AND `§8e`'s WRITTEN FALSIFIER — *"`dist` LARGE contradicts the report and means THIS INSTRUMENT
is wrong, not the report"* — DID NOT FIRE. The instrument and the owner's report AGREE.**
`HANDOVER` §5 did not have to be invoked.

### 2. **THE FIVE VIEW PLANES ARE MEASURED AND ARE NOT INCRIMINATING.**
`left+right` = 53,689 = **70.8%** of plane-hits · `top+bottom` = 14,809 = **19.5%** · `near` =
7,310 = **9.6%**. That is the reported shape — **and it is NOT ADVANCED AS A FINDING**, because
props sit on a GROUND PLANE, distributed wide horizontally and thin vertically, so left/right
dominance is what **any** level would produce. A story that fits is `275` §1's grep-for-a-guard.

### 3. **THE SITE, NAMED: `propobj.c:14087`, `getROOMID_isRendered(roomnum)`.**
**`§8e`'s written outcome *"`room` LARGE -> the cull neither knob touches, and the two arms were
looking in the wrong place from the start"* FIRED.** `GETV_ROOMSCISSOR` and `GETV_PROPCULLBOX`
both leave this test alone; it survived two arms without being tested once — and *"while you are
looking off in a different direction"* is what a view-driven room-visibility cull sounds like.
**NO FIX IS PROPOSED AND NONE MAY BE INFERRED. THE SITE IS NAMED; THE MECHANISM IS NOT.**

### 4. THE FRUSTUM, RECORDED WITHOUT A THEORY ATTACHED
`c_halfwidth=160.000 c_scalex=0.008553 | c_halfheight=90.000 c_scaley=0.006415 |
c_screenleft=0.000` — **byte-identical in both runs.** Half-angles **x=53.84 deg, y=30.00 deg**.
`tan(53.84)/tan(30.00) = 2.370` against a geometric `160/90 = 1.778` — **a ratio of exactly
`4/3`.** `c_scaley` gives `tan y = 0.577350` = `1/sqrt(3)` to six places, an exact 30 deg.
**The cull is 4/3 WIDER horizontally than its own geometry implies. The instrument's note asks
whether it is NARROWER than what is drawn; it is WIDER, so "two notions of view width pinching
the edges" is NOT SUPPORTED by these numbers. The 4/3 is real and unexplained.**

### 5. A NINTH CLEAN DUMP, FROM A HABITUAL F9
`dlgrab_10350.txt`, **announced by `run_288_8b`'s own log**, so provenance is admissible
(`279` §2, `00-STATE` §6). **TWO distinct scissors only: `(0,0)-(1280,960)` x3 and
`(0,120)-(1280,840)` x42, BOTH FULL WIDTH. ZERO sub-view rects.** `287`'s `dlgrab_8040` carried
seven including the falsifier `(832,120)-(1276,840)`. **Ninth independent confirmation on top of
ARM 5's eight, and the first taken with `GETV_PROPCULLBOX=0`.**

---

## §6 — ►►►► THREE DEFECTS IN `GETV_CULLWHY`'s OWN REPORT, FOUND BY READING THE SOURCE IT COUNTS ◄◄◄◄

**These do not void the arm. They bound what it can be asked.** Rule `15`: an instrument that is
not read as carefully as the code is not an instrument.

1. **`room` IS ON A DIFFERENT DENOMINATOR FROM EVERY OTHER COUNTER, AND THE REPORT PRINTS ALL SIX
   ON ONE LINE AS IF THEY WERE COMMENSURABLE.** `propobj.c:14081` is a **`while` loop over the
   prop's room list** (up to 8 entries from `chraiGetPropRoomIds`). `:14085` increments `room`
   **once per UNRENDERED ENTRY** and continues; the function only `break`s on a rendered room.
   **So `room=1,134,409` is ENTRIES TRAVERSED, NOT PROPS REJECTED.** The per-prop outcomes do
   balance — `36809+38996+12257+2163 = 90,225` calls that reached a rendered room — **but `room`
   is not in that accounting. "29x bigger than `box`" IS NOT A READING THIS REPORT CAN SUPPORT.**
   `room` is very likely still the largest term. **BY HOW MUCH IS NOT MEASURED.**
2. **THE PLANE COUNTERS MULTI-COUNT.** `:14130` loops over five mask bits and increments **every**
   plane that rejects, so a prop outside two planes counts twice. **75,808 is PLANE-HITS, NOT
   PROPS**; props rejected by view lie between **38,400 and 75,808.**
3. **WITH `GETV_PROPCULLBOX` AT ITS SHIPPING DEFAULT THE PLANES ARE UNREACHABLE.** `:14126` sends
   a rejection to `box` whenever the knob is on and the bbox lookup succeeds; the per-plane
   counters are the **`else`** branch. **So ARM 8's `near=left=right=top=bottom=0` is EXPECTED BY
   CONSTRUCTION and is NOT evidence about the planes.** This is precisely why 8b was mandatory.

---

## §7 — WHAT `288` GOT WRONG. **FOUR PREDICTIONS AND TWO ASSERTIONS, ALL MINE.**

| claimed | truth | killed by |
|---|---|---|
| *"`jdm > 20%` on the uncapped negative control"* | **FALSE.** `[MEASURED]` 14.5%. Calibrated off the harness's 40.9%; the synthetic stream is scatterier than the real uncapped loop. **The discrimination survives on the matched metric (3-5x); the threshold does not.** | `288` V2 |
| *"`jdp < 10%`, per window"* | **INCOMPLETE — no boot exclusion.** V1 window 1 read 32.8% with nine hitches in the old bins corroborating it. **Restated: settled windows only.** | `288` V1 |
| *"`left` and `right` both large and ROUGHLY EQUAL = the symmetric signature"* | **DID NOT FIRE — `right/left = 2.51` — AND THE COUNTER CANNOT TEST IT EITHER WAY.** The frustum is symmetric by construction and measured so (`c_screenleft=0.000`, identical both runs); a cumulative counter over a run where the player walks and turns reflects WHERE THEY LOOKED, not the shape of the frustum. **A defect in the stated outcome, not a finding about the planes.** | `288` ARM 8b |
| *"the 468 uncommitted decomp lines are undocumented work and CONTAMINATE the 288 binary"* | **FALSE — MINE, and I raised `274` §7's gate on it before reading the diffs.** They are this project's own `GETV_*` instrument history from `253`-`277`, carrying their own comments. **The binary is not contaminated by anything unknown and no scope limit is owed on any arm.** The commit is still owed, for the OPPOSITE reason — see §8. | `288`, reading the diff |
| *"`Close GoldenEye VR.bat` being broken bugchecks the machine, fix it before the arms"* | **OVERSTATED — MINE, asserted before reading the script.** It targets **`GoldenRecomp.exe`**, the recomp build, not `goldeneye.exe`. Its own header says the 0x139s were GoldenRecomp in a VR session inside `nvwgf2umx.dll` and **never under `-NoXr`**. Stereo has not been started in the native port, and six arms closed cleanly today via `SDL_QUIT -> game_exit()`. **It blocks nothing.** | `288`, reading the script |
| *"`GETV_SLOTFREE = 0` in the per-user cfg is BLOCKING"* (carried from `287`) | **NOT ON THIS LOGIN.** `[MEASURED]` `%APPDATA%\Goldeneye-Native\Goldeneye-Native\goldeneye.cfg` on the `<USER>` login contains **no SLOTFREE line at all**. **The standing rule is NOT retired** — §0 says the cfg is per-user and the same human runs under different logins. `GETV_SLOTFREE=1` stays in every block; it cost nothing and all six arms printed `resolved to 1 (env=1)`. | `288` |

---

## §8 — ►►►► THE DECOMP HAS BEEN CARRYING UNCOMMITTED KNOBS FOR A DOZEN SESSIONS ◄◄◄◄

`[MEASURED]` before the arms ran. **Not new work — never committed**, because `COMMIT-NOW.cmd`
does not cover `vendor/ge-decomp` (`00-STATE` §6: `vendor/` is gitignored by `goldeneye-native`
and invisible to all three passes, so the `-decomp.txt` commits that exist were made BY HAND).

```
in HEAD / on disk
  5 / 8   GETV_SLOTFREE          2 / 4   GETV_UNLOCKALL
  0 / 2   GETV_SLOTTRACE         0 / 2   GETV_FOLDERBOX
  0 / 2   GETV_ANIMSLOTS         0 / 2   GETV_FOLDERTRACE
  0 / 2   GETV_CCPROBE           0 / 3   GETV_ALIGNPTR
                                 0 / 3   GETV_MENU_NOVALIDATE
```

**THE ONE THAT MATTERS: `"[getv][slot] GETV_SLOTFREE resolved to %d (env=%s)"` IS ABSENT FROM
HEAD.** That string is **gate 4 of every run block in `RUN-SHEET-288`**, on a knob `00-STATE`
calls BLOCKING. **A fresh clone builds a binary that prints no resolution banner, so the gate
reads as a clean null and `287` 4C's `0xc0000005` returns with nothing in the log to name it.**
**THIS IS `268`'s `GETV_DLGRAB`, SAME SHAPE, DIFFERENT KNOB, AND IT HAS BEEN SITTING LONGER.**

**AND `GETV_CCPROBE` IS THE INSTRUMENT BEHIND A STANDING FINDING** — `00-STATE` §3 records the
colour combiner as EXONERATED on `265`'s evidence. **The probe that produced it is in no commit.
The finding cannot be re-derived from a clone.**

**NOT a line-ending sweep:** 468 insertions / 5 deletions; the same diff with `-w` reads 467 / 4.
`00-STATE` §6's 2,097 CRLF-dirty files are a SEPARATE, PRE-EXISTING question and are untouched.
**Commit message written: `COMMIT-MESSAGE-2026-08-31f-decomp.txt`. Staged by explicit path list,
never `git add -A`.**

---

## §9 — STILL OWED, NOW EIGHT SESSIONS
All of `277` §9 (the two hoist sites, never driven) · `278` §6's INFERRED hoist-1 read ·
`279` §5's amount arm · `280` §7.3's black-wall dump · `274` §7's CONTAMINATED gate ·
**`287` ARM 6, the wear pass — STILL NEVER RUN.** **Carried forward honestly, not quietly.**

## §10 — AND THE `288` DEFECTS IN `RUN-SHEET-288` ITSELF, FOR WHOEVER USES IT NEXT
**(a) `§6`'s V2 block says *"same block as `§5` with these three lines changed"* and KEEPS
`GETV_SIMHZ=query`, which `GETV_FPS=0` MAKES IMPOSSIBLE.** So the positive and negative controls
differ in TWO things, not one. It does not void V2 — the statistic reads presented-frame
intervals and the sim rate is not in that path — **but it is a scope limit.**
**(b) GATE 3 IS INAPPLICABLE TO ANY UNCAPPED ARM.** `60 / cap` is undefined at `cap = 0`; the
correct reading is the `CONTAMINATED` refusal itself. Same family as `287` defect (a): a gate
carrying a hidden assumption.
**(c) GATE 2 MANDATES OPEN ITEM 2's FAULT CELL.** Gate 2 is `ours: x=367.333`; the front-end text
fault is `ge_offset_x() != 0`. **They are the same number — a run that passes gate 2 has broken
menu text BY CONSTRUCTION**, and `[REPORTED]` as a fresh regression this session because nothing
said so. **Do not "fix" it by moving to `1825x1369`: that prints `ours: x=0`, which is also what
`WIDESCREEN=1` prints, so gate 2 would silently stop discriminating** (rule `17`).
