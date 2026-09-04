# THE PROMPT FOR THE NEXT SESSION — copy the block below verbatim

**REWRITTEN 2026-08-31 at the end of the `287` RUN session.** The previous version of this
file is the prompt that STARTED that session and is kept below, unchanged, as history.
**`287` PART ONE IS NOW WORN — five arms, one binary, no rebuild.** `00-STATE` §7c: a pointer
is not a handover. This carries the prompt, what to do FIRST, the log names, and what is owed.

---

```
Read repo\docs\00-STATE.md and continue from section 3. Same rules as always.

THE BUILD IS DONE AND ITS GATE PASSES. Binary 2026-08-31 02:24, 18,026,915 bytes;
all six strings present. DO NOT REBUILD. RUN-SHEET-287 sections 1 and 4 are COMPLETE.
PART ONE IS WORN: 4A, 4B, 4C and 4D all ran, all gated clean, and their numbers are
already in 00-STATE section 3. DO NOT RE-RUN THEM.

THE PANEL IS 120 Hz. [MEASURED], from SDL, in a log -- not reported. But the session
lead ALSO WORKS ON A 180 Hz PANEL, so every bin prediction is panel/cap and every
simhz gate is 60/cap. THE FIRST LINE OF ANY PACEHIST LOG IS
`PANEL REPORTED BY SDL: <n> Hz` AND YOU READ IT BEFORE ANYTHING ELSE.

EVERY COMMAND BLOCK MUST CARRY ALL OF THESE, because a block that omits a knob
silently restores its default (285 S1 lost two this way and read it as a regression):
  GETV_SLOTFREE=1 GETV_VSYNC=1 GETV_FPS=120 GETV_SIMHZ=query GETV_SIMDIV=1
  GETV_WIDESCREEN=0 GETV_ROOMSCISSOR=0 GETV_WINDOW=2560x1369
GETV_SLOTFREE=1 IS NOT OPTIONAL until the cfg line is gone -- see below.
Three recipes, and every block must say which it is:
  PLAY / LOOK AT IT   VSYNC=1 FPS=120
  GPU (GETV_GPUTIME)  VSYNC=0 FPS=0     -- 273 section 8
  CPU (WORK_OVER=)    VSYNC=0 FPS=120   -- 287 section 4

DO THIS, IN THIS ORDER:
1. Re-confirm the six-string gate only (RUN-SHEET-287 section 1, the two foreach
   loops -- NOT the build line). A missing string means someone rebuilt; stop.
   THEN CONFIRM THE REGEN TOOK: tools/fetch-thirdparty.sh verify must say
   `15/15 files match pristine + patch`. If it does not, GETV_PACEHIST is not in
   the repo and the 287 session's own commit was the second instance of that bug.
2. ARM 4E ALREADY RAN. DO NOT RE-RUN IT. It came out OPPOSITE to the prediction:
   99.83% in the 1x bin at VSYNC=0 FPS=120, against 4A's 99.90% at vsync=1, over
   21,736 intervals. "VSYNC=0 WAS THE JUDDER" IS NOT SUPPORTED BY THE INSTRUMENT
   and 285's diagnosis is a re-read, not a settled fact. 00-STATE section 4 carries it.

   ►► THE REAL WORK IS THE ONE 4E EXPOSED: GETV_PACEHIST IS BLIND TO THE THING THE
   COMPLAINT IS PROBABLY MADE OF. The 1x bin is [0.5,1.5) of the panel period --
   4.17 to 12.5 ms, THREE TIMES WIDE. A run alternating 6 and 10.5 ms scores 100% 1x
   and would feel terrible. The instrument catches DROPPED AND DOUBLED FRAMES; it does
   NOT catch JITTER INSIDE A FRAME PERIOD. That is 285 section 3.3's own critique --
   a mean of 16.67 ms is identical for an even run and one alternating 8 and 25 --
   one level finer, now aimed at the instrument built to answer it.
   BUILD THE JITTER STATISTIC. Most of it is already there: ge_pacehist_record()
   keeps a sample array and already prints p50/p90/p99/min/max. Wanted is the SPREAD
   as a first-class per-window number -- a stddev, or a fine sub-bin histogram across
   0.5x-1.5x -- so an even 8.33 and an alternating 6/10.5 stop reading identically.
   P5: a figure that cannot fail is not an instrument. THIS IS A BUILD, and it is in
   gfx_sdl2.c, so 287 section 0a's regen trap applies again -- REGEN AFTER, NOT BEFORE.
   The hint it must resolve, from 4E vs 4A and NOT a finding (the runs are not length-
   or activity-matched): mean p99-p50 0.646 vs 0.707 ms, ragged windows 21% vs 44%.

   AND THE SCOPE LIMIT ON 4E, WHICH IS WHY 285 IS RE-READ RATHER THAN RETRACTED:
   4E ran with SIMHZ=query and SIMDIV=1. The configuration actually played for most
   of this project had NEITHER. 4E isolates vsync with everything else correct -- so
   GETV_SIMHZ, not vsync, is now the untested carrier of 285 S1's "super smooth."
3. ARM 5 -- did the six-site switch take? Streets, GETV_STAGE=29, stand still with
   the artifact on screen, F9 twice. READ THE `sites:` COUNTER LINE: a ZERO on
   chr/expl/smoke/prop in a level that draws them names the site that never ran.
   Three logs from 287 already show expl=0 smoke=0, which means NOTHING until a
   level that draws explosions and smoke is run. Then ARM 6 (the wear pass, NEVER
   RUN), ARM 7 (GETV_PROPCULLBOX, the black-wall arm), ARM 8A/8B (the cost).
Gate every run on all five: the roomscissor banner, `ours: x=367.333` in the
VIEWPORT line (x=0 means widescreen came back ON), the simhz line at 60/cap fields
per frame, zero `simulation held to`, and a terminating `game_exit requested`.

TWO DEFECTS IN RUN-SHEET-287 ITSELF, FOUND BY RUNNING IT. Fix them in 288 rather
than honouring them: section 3's bin predictions and the section 1 simhz gate carry
a hidden panel constant, and section 3's row "a pre-swap stamp reads near 0 ms in
4C" cannot discriminate in the uncapped arm it was written for -- 4B settles that
question instead. 00-STATE section 4 carries both.

OWNER ACTION, BLOCKING, AND IT CRASHED A RUN: GETV_SLOTFREE = 0 is still in
%APPDATA%\Goldeneye-Native\Goldeneye-Native\goldeneye.cfg. It resolved to 0 in
EVERY arm of 287 because every block opens with Remove-Item Env:GETV_*. 4C reached
the intro cast and died on it -- NO SLOT required=155 slots=10 free=0, then
0xc0000005 at fault addr 0x28. 262's fix IS NOT IN EFFECT ON THIS MACHINE.

NEW AND MEASURED, AND IT IS P3: the front-end TEXT is laid out in a different
coordinate space from the folder ART, and the variable is ge_offset_x(). The fault
appears IFF the pillarbox offset is non-zero -- four cells, and M3 isolates it at a
fixed content scale. NO CAUSE IS NAMED. Do not propose a fix; the next step is
reading which draw path applies the offset and which does not. It is also a cost of
the GETV_WIDESCREEN=0 default that 00-STATE's widescreen item never named.

CHEAP AND WORTH DOING, 288 MATERIAL: GETV_FPS=panel. gfx_sdl2.c:756 already queries
SDL for the panel and already follows the window between monitors; it is gated on
GETV_PACEHIST, lazy, and consumed by nothing. wnd exists at :392, sixty-five lines
before the cap is parsed at :457. Hoist it, and GETV_SIMHZ=query chains off
ge_pace_framerate for free -- one env value covers both the 120 and the 180 desk.
It MUST REFUSE rather than fall back on an unknown rate (rule 17), and stay opt-in.

DEAD, DO NOT REOPEN: both of 281's patches (284 s2). 282 s2.2's fail-open (283 s2).
283 s3's attribution of the left slab to the straddle (284 s2). The fractional
divider as a new shape -- it IS 268 (275 s3). 285 s1.4, the turn-has-no-timestep
candidate -- killed by 287's 4D stopwatch, 1.09 not 2.0. The 320x240 <-> 440x330
canvas switch as the menu-text cause -- present in the clean run too, 287 M3.

STILL OWED, SIX SESSIONS: all of 277 section 9, plus 278 section 6's INFERRED
hoist-1 read, 279 section 5's amount arm, 280 section 7.3's black-wall dump,
274 section 7's CONTAMINATED gate.

Start with step 1, then run ARM 4E and report the log. Do not plan -- the run sheet
is written.
```

---

# HISTORY — the prompt that STARTED the `287` run session, unchanged

# THE PROMPT FOR THE NEXT SESSION — copy the block below verbatim

**Written 2026-08-31 by the `287` session, which wrote code and ran nothing.**
**AMENDED later the same day: the build has since been run and its gate verified --
see the CORRECTED paragraph in the prompt block. Still zero measurements.**
`00-STATE` §7c: a pointer is not a handover. This carries the one-line prompt, what to do FIRST,
the log names, and what is owed.

---

```
Read repo\docs\00-STATE.md and continue from section 3. Same rules as always.

START FROM THIS BUILD AND THESE SETTINGS. Every command block must carry ALL of them,
because a block that omits a knob silently restores its default:
  GETV_VSYNC=1  GETV_FPS=120  GETV_SIMHZ=query  GETV_SIMDIV=1
  GETV_WIDESCREEN=0  GETV_ROOMSCISSOR=0  GETV_WINDOW=2560x1369
The panel is 120 Hz -- BUT NOTHING HAS EVER VERIFIED THAT, and 287 section 3 is why.
There are THREE recipes now, not two, and every block must say which it is:
  PLAY / LOOK AT IT   VSYNC=1 FPS=120
  GPU (GETV_GPUTIME)  VSYNC=0 FPS=0      -- 273 section 8
  CPU (WORK_OVER=)    VSYNC=0 FPS=120    -- 287 section 4, in no earlier doc
Gate every run on: the roomscissor banner, `ours: x=367.333` in the VIEWPORT line
(x=0 means widescreen came back ON), `simhz ... 0.500000 fields per frame`, zero
`simulation held to`, and a terminating `game_exit requested`.

CORRECTED 2026-08-31: THE BUILD IS DONE AND THE BINARY GATE PASSES. The text
below used to say "287 wrote code and ran nothing, the binary is still 286's."
The first half is still true -- NOTHING HAS BEEN MEASURED, there is not one
run_287_* log on disk. The second half is FALSE and was believed for a session.

  binary : 2026-08-31 02:24, 18,026,915 bytes   (286's was 01:07, 18,021,956)
  build  : build_287_sixsites_pacehist.log -- 165 game, 234 assets, 40 audio,
           58 port layer, 2 port c++, libge.a 24.8 MB / 498 members, 0 failed
  gate   : ALL SIX STRINGS PRESENT -- GETV_ROOMSCISSOR, GETV_PROPCULLBOX,
           GETV_PACEHIST, 'SIX SITES', 'pacehist', 'PANEL REPORTED BY SDL'
           plus the six-site counter labels bg_pri bg_sec expl smoke prop

So RUN-SHEET-287 section 1 IS COMPLETE. Do not rebuild. Three knobs are live in
this binary, all default OFF: GETV_ROOMSCISSOR at SIX sites with per-site take
counters, GETV_PROPCULLBOX, GETV_PACEHIST. RUN-SHEET-287.md has every block.

DO THIS FIRST, IN THIS ORDER:
1. Re-confirm the gate in ten seconds -- RUN-SHEET-287.md section 1's last two
   foreach loops only, NOT the build line above them. If a string is missing,
   somebody rebuilt since and the run is a clean null (133, 268 section 4).
2. ARM 4A -- GETV_PACEHIST=600 at the play settings. Front-end menu ~60 s, then a
   level, turning fast. THIS IS THE FIRST MEASUREMENT AND IT OUTRANKS THE HOLES (285
   section 4). The FIRST line to read is `PANEL REPORTED BY SDL: <n> Hz`. If it is not
   120, STOP and re-read 285 S1 before anything else.
3. ARM 4B is the VALIDATION arm, not the answer -- FPS=60 must move the mass to the 2x
   bin. If it does not, the stamp is in the wrong place and every other arm is void.
4. ARM 4C is the negative control. ARM 4D is free, needs no build: a 360-degree spin
   timed at FPS=60 vs FPS=120. Equal -> 285 section 1.4 is dead.
ONLY THEN PART TWO: ARM 5 (did the six-site switch take -- read the `sites:` counter
line, a ZERO names the site that never ran), ARM 6 (the wear pass, NEVER RUN: Facility
glass, Dam, Cradle, front-end), ARM 7 (GETV_PROPCULLBOX, the black-wall arm), ARM 8A/8B
(the cost).

DO NOT RUN tools/fetch-thirdparty.sh regen UNTIL THE ARMS ARE WORN. GETV_PACEHIST lives
in gfx_sdl2.c, which is GITIGNORED and regenerated -- 287 section 5. `verify` FAILING is
expected until the patch is regenerated; a regen BEFORE that DELETES the instrument,
which is exactly 271 section 7's GETV_DLGRAB. Git Bash, main PC, after.

DEAD, DO NOT REOPEN: both of 281's patches (284 section 2). 282 section 2.2's fail-open
(283 section 2). 283 section 3's attribution of the left slab to the straddle (284
section 2). The fractional divider as a new shape -- it IS 268 (275 section 3).

STILL OWED AND STILL UNTOUCHED, FIVE SESSIONS NOW: all of 277 section 9 -- the two hoist
sites driven, the two intro-skip audio falsifiers, the MoveBond executions-per-second
counter -- plus 278 section 6's INFERRED hoist-1 read. The same-spot two-resolution
amount arm (279 section 5), still no number. The black-wall dump (280 section 7.3) --
287 section 1 gives it a candidate mechanism for the first time. GETV_REALCLOCK's
CONTAMINATED gate (274 section 7). SETUP.md section 3.5 owes 229 section 9's two CSV traps.

Plan first if the plan is not obvious from the run sheet; otherwise run ARM 4A and
report the log.
```

---

## THE LOG NAMES THIS SESSION WILL PRODUCE
`build_287_sixsites_pacehist.log` · `run_287_4A_pacehist_play120.log` ·
`run_287_4B_pacehist_validate60.log` · `run_287_4C_pacehist_uncapped.log` ·
`run_287_5_sixsites_streets.log` · `run_287_6_wear_facility.log` (+ dam / cradle / frontend) ·
`run_287_7_propcullbox.log` · `run_287_8A_gpu_cradle.log` · `run_287_8B_cpu_cradle.log`

## WHAT IS NOT WRITTEN DOWN ANYWHERE ELSE
- **`00-STATE` is updated but its §3 entries for `285` and the holes say WRITTEN, NOT RUN.**
  The next session's first job after ARM 4A is to turn those into `[MEASURED]` or retract them.
- **`287` has no §-numbered findings from a run, because there was no run.** Its §1-§5 are all
  source reads. **Every one of them is a retraction candidate until an arm confirms it** — `275`
  §1, `277` §6.2 and `278` §7.2 are three sessions of what happens when that line is crossed.
- **The commit for this session covers three repos** and the decomp must go by **explicit path
  list, never `git add -A`** (`00-STATE` §6: 2,106 CRLF-dirty files, and `7a4e7bfd` in the history
  is a three-line bugfix carrying 601,764 insertions).
