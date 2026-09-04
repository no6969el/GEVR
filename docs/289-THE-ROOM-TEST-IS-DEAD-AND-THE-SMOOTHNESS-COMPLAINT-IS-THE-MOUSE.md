# 289 — THE ROOM TEST IS DEAD, `dist=0` WAS A MASKED ZERO, AND THE SMOOTHNESS COMPLAINT IS THE MOUSE

**2026-08-31. BUILT, RUN AND WORN. FIVE ARMS, ONE BINARY.**
**Binary: `2026-08-31 18:47:30`, `18,036,265` bytes.** Predecessor `288`'s was `18,035,038` at
`17:09:32`. Run sheet: `RUN-SHEET-289.md`. Predecessor doc: `288`.

**THE SESSION IN ONE LINE:** two instruments were written, validated offline against a harness that
is a FILE this time, and built; the first put `room` on a denominator it could be read on and the
second **killed `288`'s standing candidate in one arm**; and then **the session lead re-diagnosed the
five-session-old smoothness complaint from the arm that was supposed to close it — it is
MOUSE-ONLY, it is the SHAPE OF THE TURN, and it is not graphics.**
**THREE OF THIS SESSION'S OWN WRITTEN OUTCOMES FIRED AND ONE STANDING SOURCE READ IS RETRACTED.**

---

## §1 — THE BUILD AND THE FIFTEEN-STRING GATE. **PASS.**

`build_289_roomtest.log`, zero errors, zero failures: game 165 built, assets 234, audio 40, port
layer 58, port c++ 2. Binary **1,227 bytes larger** than `288`'s — the size of two banners and four
printf lines.

All fifteen strings present, read off the binary independently of the build shell:
`GETV_ROOMSCISSOR` · `GETV_PROPCULLBOX` · `GETV_PACEHIST` · `GETV_CULLWHY` · **`GETV_PROPROOMTEST`** ·
`SIX SITES` · `pacehist` · `PANEL REPORTED BY SDL` · `jitter: sd=` · `GETV_FPS=panel REFUSED` ·
`twin-disagree` · **`proproomtest`** · **`PER PROP (one per posIsOnScreen call)`** · **`sum-check:`** ·
**`PER ENTRY (NOT a prop count`**.

**AND THE TWO PRECONDITIONS `288` LEFT WERE CHECKED BEFORE ANYTHING WAS EDITED, AND BOTH HELD:**
`tools/fetch-thirdparty.sh verify` = **`15/15 files match pristine + patch`** with the patch
committed as `30a85b8`; `vendor/ge-decomp` HEAD = **`ad4105cf`**, so `288` §8's 468 insertions and
the `GETV_SLOTFREE` resolution banner are in HEAD. **`verify` was re-run AFTER the build and still
reads `15/15`** — nothing in `289` touches `getv/port/**`, and that is now a free standing gate.

---

## §2 — THE OFFLINE VALIDATION IS A FILE THIS TIME

`getv/tools/cullwhy_harness.sh` + `cullwhy_harness.c`. It extracts the real `getv_cullwhy_report()`
and `posIsOnScreen()` from `propobj.c` **by name, brace-matched**, so it can never test a stale copy;
stubs every predicate; and drives them with nine synthetic worlds. Clean under `gcc -Wall -Wextra`.

**`[MEASURED]` before any build: nine cases x two arms, 0 failures.** The sum-check balances in all
eighteen; the knob moves a prop whose whole room list is unrendered from `roomprop` into the rest of
the pipeline; and **`room` and `roomprop` read identically in both arms**, which is the arm-invariance
the read-only pre-pass exists for. **A negative control double-counts one bucket on purpose and the
report is seen to print `MISMATCH`** (`279` §7).

**`288`'s pacehist harness lived only in the session and is gone.** This one is committed, for the
same reason `00-STATE` §3 gives about `GETV_CCPROBE`: an instrument behind a standing finding that
cannot be re-derived is a finding that cannot be re-derived.

---

## §3 — R1: THE DENOMINATOR IS FIXED AND THE SUM-CHECK BALANCES ON HARDWARE

`[MEASURED]` 18:50, `run_289_R1_cullwhy_denominators.log`. Gates clean throughout: panel 120 queried
from SDL, `simhz 0.500000` (= `60/120`), `ours: x=367.333`, `SLOTFREE resolved to 1 (env=1)`, six
sites non-zero, zero `simulation held to`, `props interpolated 0`, terminating record,
`twin-disagree=0`.

```
PER PROP   calls=1301498 | nolist=0 roomprop=1203533 fog=12257 occl=2241
                            box=45556 view=0 dist=0 drawn=37911
sum-check  ... = 1301498 vs calls=1301498 -- BALANCES
PER ENTRY  room-entries=1327916
PER PLANE  near=0 left=0 right=0 top=0 bottom=0 | plane-hits=0 vs view=0 props
```

**`room` IS COMPARABLE NOW: `roomprop / box = 26.4x`.** `288` §6 said *"very likely still the largest
term. BY HOW MUCH IS NOT MEASURED."* It is measured. **`288`'s unsupported "29x" was in the right
neighbourhood for the wrong reason**, and `room-entries / roomprop = 1.103` says why the two
denominators were never far apart: a prop the room test removes has barely more than one unrendered
entry in its list.

**►► AND THE BIG NUMBER IS NOT EVIDENCE, WHICH WAS WRITTEN INTO THE SHEET BEFORE THE RUN.**
92.5% of calls rejected by the room test is what **any** broad-phase room cull reads, because at any
instant most of a level's props are in rooms that are not drawn. **All R1 establishes is that
`roomprop` is not zero, so §6 outcome 2 did not fire and R2 is a live test. R1 cannot convict and
does not.**

`view=0` and all five planes `0` are **expected by construction** — with `GETV_PROPCULLBOX` on, the
plane path is unreachable (`288` §6 defect 3), and **the sum-check balancing WITH `view=0` is the
positive confirmation that it is unreachable rather than broken.**

**A TENTH CLEAN `dlgrab`, ANNOUNCED BY THIS LOG** (`279` §2): `dlgrab_7675.txt`, taken with the prop
visibly vanished, BMP `10,513,974` = `54 + 2560*1369*3`. **Two distinct scissors, both FULL WIDTH,
zero sub-view rects.** With ARM 5's eight and `288`'s ninth that is ten. **The vanishing prop is not
a scissor.**

---

## §4 — ►►►► R2: THE PROPS STILL VANISH. `288`'s STANDING CANDIDATE IS ELIMINATED. ◄◄◄◄

`[MEASURED]` 18:53, `run_289_R2_proproomtest_off.log`. **THE KNOB TOOK** — the `proproomtest` banner
is in the log, so this is **not a clean null result** (`133`, `268` §4). Gates clean.

```
R1 (roomtest ON )  calls=1301498 | roomprop=1203533 fog=12257  occl=2241  box=45556 view=0      dist=0     drawn=37911
R2 (roomtest OFF)  calls=1385191 | roomprop=1285030 fog=544303 occl=88708 box=42409 view=436784 dist=17124 drawn=255863
```

**`[REPORTED]` BY THE SESSION LEAD WITH THE ROOM TEST NEUTRALISED: *"still able to."***
**`RUN-SHEET-289` §6's outcome 4, written before the run, FIRED:** *"the room test is ELIMINATED.
That is a real result and it is exactly how ARM 7 ended. DO NOT RE-RUN R2 HOPING."*

**`getROOMID_isRendered` AT `posIsOnScreen`'s ROOM GATE IS NOT THE MECHANISM.** `288` promoted it and
`289` killed it **with the falsifier written for it**, not by argument.

**THE LIMIT, STATED RATHER THAN GLOSSED:** a prop rejected by the room test **and also** by a
downstream test would still vanish with the gate neutralised. R2 cannot separate that from *"the
room test never touched it."* Same limit ARM 7 carried. **Eliminated as the mechanism; not proved
innocent.**

### 4.1 THE INSTRUMENT VALIDATED ITSELF TWICE
**The sum-check BALANCES under BOTH identities** — with `roomprop` in (1,301,498) and out
(1,385,191). **The OFF identity balancing is the positive proof that `roomprop` is a shadow count
and not a double-count**, which the offline harness could assert but not demonstrate on real data.
**And the arm-invariance held on hardware: `roomprop` is 92.5% of calls in R1 and 92.8% in R2**,
0.3 points apart across two separately-walked runs.

### 4.2 ►►►► `dist=0` WAS A **MASKED ZERO**. THIS IS THE METHODOLOGICAL FINDING OF THE SESSION. ◄◄◄◄
**`dist` has read 0 three times — `288` ARM 8, ARM 8b and `289` R1 — and `00-STATE` records the
`32000` radius as DEAD BY MEASUREMENT. `[MEASURED]` IN R2 IT READS `17,124`.**

The radius sits **downstream** of the room test. With the room gate rejecting 92.5% of everything,
the far props never arrived. **The zero was not the test being inert; it was an earlier test getting
there first.**

- **SURVIVES:** in the shipping configuration, across three runs that reproduced the symptom, the
  radius removed **zero** props. **It is not the mechanism. That verdict is untouched.**
- **DOES NOT SURVIVE:** any reading of *"`dist=0`, therefore the test is inert."*
- **THE GENERAL RULE, AND IT IS NEW: A ZERO IN A TEST THAT SITS DOWNSTREAM OF A TEST REJECTING 92.5%
  OF EVERYTHING IS A MASKED ZERO, NOT AN EXONERATION.** It is `275` §1's grep-for-a-guard in a new
  costume — **the counter read without reading the ORDER it sits in**, exactly as `288` §6 read
  `room` without reading the LOOP it sits in. **Same shape, one level over, same session.**

### 4.3 THE SHIPPING CONFIGURATION HAS ALMOST NOTHING LEFT THAT CAN REMOVE A PROP

| test | R1, shipping | status |
|---|---|---|
| `room` | 1,203,533 | **ELIMINATED by R2** |
| `box` | 45,556 | **ELIMINATED by ARM 7**, and `box=0` in 8b with the symptom present |
| `dist` | 0 | removes nothing in the shipping config, three runs |
| `view` / five planes | **0** | **UNREACHABLE with `PROPCULLBOX` on** |
| `fog` | **12,257** | **not eliminated, never tested** |
| `occl` | **2,241** | **not eliminated, never tested** |

**►► SO IN THE PICTURE THE SESSION LEAD IS ACTUALLY LOOKING AT, THE FIVE VIEW PLANES REMOVE ZERO
PROPS.** Everything `288` measured about left/right/top/bottom came from 8b, which had
`PROPCULLBOX=0`. **That path is not taken in the shipping configuration.**

**►► AND THE LOAD-BEARING CLAIM IS NOW A SOURCE READ.** `288` wrote *"`posIsOnScreen` is the ONLY
place that decides a prop is not drawn."* **That is not a measurement.** §6 outcome 8 anticipated the
shape and did not fire as written, because the counters are plainly on **a** path. **It may still be
the wrong one. NO CAUSE IS NAMED AND NO FIX IS PROPOSED.**

### 4.4 `fog` IS THE STRANGEST NUMBER IN EITHER LOG
**`fog=12,257` in R1 is byte-identical to `288` ARM 8's `fog=12257`** — two sessions, two routes,
while `occl`, `box`, `drawn` and the entries count all moved. In R2 it is **544,303**. `[MEASURED]`,
and **no explanation is offered.** What it bounds: **a large part of these cumulative counts is
deterministic** — boot, load, front-end — and **the report has no windowing at all**, so it cannot
separate the deterministic part from the part the player caused. **That is `288` §4's boot-window
lesson one level over, and it is the next instrument, not a finding.**

### 4.5 OWED AND NOT DELIVERED
**No `dlgrab` line appears in `run_289_R2`.** F9 did not land, so there is no dump of the prop
vanishing **with the room test off** to set beside `dlgrab_7675`. **Recorded as owed.**

---

## §5 — S1/S2: `GETV_SIMHZ` IS CLEARED, ON THE NUMBER **AND** ON THE WEAR

`[MEASURED]` 18:58 and 19:02. Gates clean on both; **S2's inverted gate passed — zero
`fields per frame` lines and no `simhz` banner anywhere**, so the term really was off.

| | settled windows | `jdp` range | **`jdp` mean** |
|---|---|---|---|
| `288` **J1** (`vsync=1 FPS=panel SIMHZ=query`) | 10 | 7.3 - 9.2% | **8.29%** |
| **S1** — same recipe, new binary, new session | 12 | 7.1 - 9.9% | **8.54%** |
| **S2** — `SIMHZ` unset, world at **2x** | 12 | 7.2 - 9.1% | **8.05%** |

**S1 REPRODUCES J1 TO 0.25 POINTS ACROSS TWO BINARIES AND TWO SESSIONS** — nobody asked for that,
and it means a difference between S1 and S2 is a difference in the arm and not in the day.
**S1 vs S2: the ranges overlap almost entirely, the gap is 0.49 points against a within-run spread
of ~2, and the term-OFF arm is the SLIGHTLY LOWER one** — the same shape, size and direction as
J1/J2's 8.29 vs 7.70. Every settled window `600/600` in `1x` in both.

**AND `[REPORTED]` ON BOTH ARMS: *"no waiting feel."*** **`RUN-SHEET-289` §7's first written outcome
fired, and it is the uncomfortable one:** *"`jdp` equal -> `GETV_SIMHZ` is cleared and the complaint
has NO CANDIDATE LEFT."* It is cleared on the number **and** on the wear.

**BOOT IS IDENTIFIED BY TWO INDEPENDENT SIGNALS THAT AGREE:** `sd` collapses from 1.3-2.9 to ~0.48
and the OLD bins stop carrying hitches, **at the same window in both runs.** `288`'s corrected
contract applied without having to be re-learned.

**A READING NOBODY HAS TAKEN, RECORDED WITHOUT A THEORY:** in **every settled window of both arms**
`jd` is LARGER than `sd` — ratio ~**1.4**, against `2/sqrt(pi)` = 1.128 for independent noise and
2.0 for a clean two-level alternation. The boot windows are the opposite (`sd` 3-5x `jd`, the
outlier signature). **It is present with and without the term, so it is not the term.** **Not a
finding. No theory. A direction to instrument.**

---

## §6 — ►►►►►► AND THEN S3 ANSWERED A DIFFERENT QUESTION. THE COMPLAINT IS THE MOUSE. ◄◄◄◄◄◄

`[MEASURED]` 19:06, `run_289_S3_simhz_off_cap60.log`. Gates clean; bins land in `2x` = `panel/cap` =
`120/60`, as they must. **S3 HAS NO SETTLED WINDOWS AND IS NOT SCORED** — ~1,400 intervals, and both
full windows carry hitches. `jdp` 10.6% and 12.8% are **REPORTED, NEVER SCORED.** A short run has no
settled region; that is a property of the run.

**`[REPORTED]` BY THE SESSION LEAD, UNPROMPTED, AFTER S3:**
> *"this only happened to me with my mouse... it doesn't happen on the controller. I tested the other
> ones from before that I reported didn't do it and it's so smooth that it helped me realize that
> it's the way bond walks/turns. It is weird when you are running on the 60hz but it smooths out on
> the higher speed settings... it's the way the walk is when you go straight and then it starts to
> turn almost like a car when the mouse is moved left or right when going forward. It's not a normal
> wasd type feel... I think this is not graphic related."*

**FOUR FACTS, ALL NEW:**
1. **MOUSE-ONLY. THE CONTROLLER DOES NOT DO IT.**
2. **S3 REPRODUCED IT** — cap 60, the only arm today that did.
3. **IT IMPROVES WITH FRAME RATE.**
4. **IT IS NOT JUDDER — IT IS THE SHAPE OF THE MOTION**, arcing *"like a car"* out of a straight run.

**`285`'s COMPLAINT HAS BEEN CHASED FOR FIVE SESSIONS THROUGH vsync, THE FRAME CAP, THE PACER'S
SLEEP BOOKING, THE PRESENTED-FRAME DISTRIBUTION AND THE SIM RATE** — `287` 4A-4E, `288` V1/V2/J1/J2,
`289` S1/S2/S3, **three instruments and one binary each.** Every one came back clean or came back
equal. **THEY CAME BACK CLEAN BECAUSE THE FAULT IS NOT IN ANY OF THEM.** Rule `16`, and `HANDOVER`
§5: the owner's correction outranks the analysis.

### 6.1 ►► THE SOURCE READ THAT CANCELLED THE RIGHT ARM — A RETRACTION
`287` §2: *"mouse and pad are the SAME PATH — `port_input.c` accumulates `ge_mouse_pend_x` into the
stick — so `285` §2's mouse-vs-pad question needs no arm."*
**CONTRADICTED BY WEAR.** They share a **SINK** (`out->rx`), not a **PATH**. **A source read
cancelled an arm, and it was the arm that mattered.** `275` §1's family, **sixth instance — and this
one cost five sessions.**

### 6.2 WHAT THE SOURCE SAYS. `[MEASURED]`, READ NOT GREPPED. **NO CAUSE IS NAMED.**
`goldeneye-native/getv/port/src/port_input.c:1013-1100`, `goldeneye-native/docs/MOUSE.md`.
Four properties the mouse path has that the pad path does not:

- **M1 — THE MOUSE PATH IS A PER-FRAME ACCUMULATOR WITH NO TIMESTEP.** At most `32767`, one full
  deflection, is emitted **per frame**; the remainder is carried (`:1055-1063`). **The same class as
  `277` §4's un-timestepped walk, in the PORT LAYER instead of the game.**
- **M2 — THE BACKLOG CAP IS EXPRESSED IN FRAMES**, `4 * 32767` (`:1050-1053`), so its duration is
  **66.7 ms at 60 fps and 33.3 ms at 120.** **Matches fact 3**: the same hand movement is held twice
  as long at 60.
- **M3 — THE DEADZONE REMAP GIVES THE MOUSE A 20% FLOOR.** Any non-zero movement is lifted to at
  least `6553` (`:1077-1090`). `MOUSE.md`: *"Applied only to the mouse; a physical stick keeps its
  deadzone."* **The pad has a 20% dead BAND; the mouse has a 20% FLOOR — same constant, opposite
  behaviour. There is no small mouse turn.** **Matches fact 4**: a step at zero is what an arc-onset
  feels like.
- **M4 — THE MAP IS SATURATED NEARLY ALWAYS.** `GE_MOUSE_COUNTS_FULL = 21` (`:942`): **21 counts is
  full deflection**, and a real sweep is hundreds. So **M1's drain rate, not the gain, sets the
  turn.** `MOUSE.md` records *"one frame of full stick is 3.54 degrees"* — **a per-FRAME constant.**
- **M5 — THE PAD GOES THROUGH NONE OF M1-M4. Matches fact 1.**

**THIS MATCHES ALL FOUR REPORTED FACTS, WHICH IS PRECISELY WHY IT MUST BE MEASURED AND NOT
BELIEVED** — `275` §1's story that fits, `277` §6.2's numbers without a mechanism. **NO FIX IS
PROPOSED AND NONE MAY BE INFERRED.**

### 6.3 ►► THE INSTRUMENT ALREADY EXISTS, HAS NEVER BEEN RUN, AND IS FREE
**`GETV_MOUSE_SELFTEST=<counts>`** (`port_input.c:961`, `:972`) — its own comment: *"pretend the
mouse moves this many counts right every frame... the only way to put a number on it without a hand
on the mouse."* **It was written for this exact question and has never been run against a frame
rate.** `GETV_MOUSE_SELFTEST_Y` and `GETV_MOUSE_SENS` sit beside it. **No build. `290`'s first arm.**

### 6.4 RULE `16` FIRES A SECOND TIME
`00-STATE` OPEN item 9 already carries *"`[REPORTED]` CROSSHAIR AUTO-CENTRES; aiming with the mouse
fights it — it keeps putting you back"*, filed under `P8`/STAGE 7 and never diagnosed. **That is a
SECOND owner report about mouse control, sitting unranked while five sessions went into the
renderer.** **`285` §2 asked the mouse-vs-pad question in the first place and `287` §2 cancelled it.**

---

## §7 — WHAT `289` GOT WRONG, AND WHAT IT INHERITED WRONG

| claimed | truth | killed by |
|---|---|---|
| *"the `32000` radius is DEAD BY MEASUREMENT"* (`00-STATE`, `288`) | **THE VERDICT SURVIVES, THE REASONING DOES NOT.** `dist` reads 17,124 in R2. The three zeros are **MASKED** by a test upstream that rejects 92.5% of everything. It removes nothing in the shipping config; it is not inert. | `289` R2 |
| *"`287` §2: mouse and pad are the SAME PATH, so `285` §2's mouse-vs-pad question needs no arm"* | **FALSE, BY WEAR.** Same sink, different path: an accumulator, a per-frame drain, a frame-expressed cap and a mouse-only deadzone floor, none of which the pad touches. **A source read cancelled the arm that mattered.** | `289` §6, the session lead |
| *"`RUN-SHEET-289` §7: S3 controls S2's 2x world producing a FALSE POSITIVE"* | **THE ROLE CHANGED UNDER IT — MINE.** S2 came back negative, so that job was done before S3 ran; its live risk was 2x **MASKING** a hesitation. Demoted mid-sheet and stated, not quietly dropped. **And it then reproduced the symptom for an unrelated reason — the mouse.** | `289` §7c |
| *"`RUN-SHEET-289` §6 outcome 7: `box` will RISE in R2 along with `view` and `drawn`"* | **`box` DID NOT RISE — 45,556 -> 42,409, essentially flat**, while `view` went 0 -> 436,784. The newly-arriving props have **no room bbox** (their rooms are not rendered), so they take the plain-view path instead. **The prediction's direction was right for the wrong counter.** | `289` R2 |
| *"`288` §6: `room=1,134,409` is very likely still the largest term, by how much is not measured"* | **CORRECT, AND NOW MEASURED: 26.4x `box` on the per-prop denominator.** Recorded because it is the rare case of a `288` caveat surviving intact. | `289` R1 |

---

## §8 — STILL OWED, NOW NINE SESSIONS
All of `277` §9 (the two hoist sites, never driven) · `278` §6's INFERRED hoist-1 read ·
`279` §5's amount arm · `280` §7.3's black-wall dump · `274` §7's `CONTAMINATED` gate ·
**`287` ARM 6, the wear pass — STILL NEVER RUN** · **and new: `289` R2's missing `dlgrab`.**
**Carried forward honestly, not quietly.**

## §9 — THE COMMITS THIS SESSION OWES, IN ORDER
1. `vendor/ge-decomp` — **BY EXPLICIT PATH LIST, NEVER `git add -A`.**
   `git diff --cached --stat` must read **168 insertions / 11 deletions, three files**.
   Message: `COMMIT-MESSAGE-2026-08-31g-decomp.txt`, **in the `GoldenEyeVR` ROOT.**
2. `goldeneye-native` — the harness only. `COMMIT-MESSAGE-2026-08-31g-native.txt`.
3. `GoldenEyeVR` — this doc, the run sheet, `00-STATE`, the `290` prompt.
   `COMMIT-MESSAGE-2026-08-31g.txt`.

**No regen is owed: nothing under `getv/port/**` was touched and `verify` reads `15/15` after the
build.** **`COMMIT-NOW.cmd` will not do step 1** — `vendor/` is invisible to all three of its passes.
