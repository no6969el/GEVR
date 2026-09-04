# RUN SHEET 289 — the per-prop denominator, the room falsifier, and the last smoothness candidate

**Written 2026-08-31, after `288` ran all six of its arms.** Predecessor: `RUN-SHEET-288.md`.
**`288`'s V1/V2/J1/J2 AND ARM 5/7/8/8b ARE WORN AND MUST NOT BE RE-RUN** — except `GETV_CULLWHY`
at the shipping default, which is re-run here **for a number that did not exist when it ran**
(§4, and it is the same justification `288` §3 gave for re-running `287`'s 4B/4C).

**ONE BINARY, like `288`. The `17:09:32` / `18,035,038` binary is good and nothing is owed against
it — but it does not contain either instrument below, so the arms in PART ONE need a build.**
**PART TWO (smoothness) needs NO build and is valid on either binary; the log's own timestamp
names which one ran it.**

---

## §0 — THE TWO PRECONDITIONS `288` LEFT, CHECKED FIRST. **BOTH HOLD.**

`[MEASURED]` 2026-08-31, before anything was edited:

1. **THE REGEN RAN AND `verify` IS CLEAN.** `tools/fetch-thirdparty.sh verify` →
   **`15/15 files match pristine + patch`**, `gfx_sdl2.c` now `ok`. The patch
   (`getv/patches/thirdparty/0001-getv-port-layer.patch`, 455,444 bytes) carries
   `PANEL REPORTED BY SDL`, `jitter: sd=`, `GETV_FPS=panel REFUSED` and `ge_panel_hz_query`,
   and it is **committed** — `30a85b8`, `193 ++ / 30 --` on that one file. **The jitter statistic
   and `GETV_FPS=panel` are no longer only on this machine's disk.**
2. **THE DECOMP IS COMMITTED.** `vendor/ge-decomp` `HEAD` = **`ad4105cf`**, subject *"288 decomp:
   commit the GETV_* knobs that have been running for a dozen sessions and are in NO commit"*.
   `288` §8's 468 insertions are in. **`"[getv][slot] GETV_SLOTFREE resolved to"` is in HEAD**, so
   gate 4 of every block below is a real gate on a fresh clone.

**NEITHER HAS COME UNDONE. Nothing is owed against them, and this sheet does not re-litigate them.**

---

## §0a — WHAT CHANGED IN THE SOURCE, AND WHY. **TWO CHANGES, ONE BINARY, BOTH INERT UNLESS ASKED.**

Both are in `vendor/ge-decomp`, both inside `#ifdef GE_PORT_NATIVE`:
`src/game/propobj.c` (+128 / −11), `src/game/bg.c` (+48), `src/game/bg.h` (+3).
**168 insertions, 11 deletions, three files — and `git diff -w --stat` reads THE SAME**, so this is
real code and not `00-STATE` §6's CRLF ghost. All three files are LF on disk, matching `HEAD`.

### 1. `room` IS PUT ON THE SAME DENOMINATOR AS EVERYTHING ELSE — `288` §6 defect 1

`288` printed `room=1134409` on one line with `fog`, `occl`, `box`, `dist` and `drawn` **as if the
six were one accounting, and they are not.** `propobj.c`'s room loop increments `room` **once per
UNRENDERED ENTRY** in a list of up to 8 and continues; every other counter is reached at most once
per call, after the `break`. **So `room` is ENTRIES TRAVERSED, and `"29x bigger than box"` was never
a reading that report could support.**

**`getv_cw_room` IS NOT REMOVED AND ITS MEANING IS NOT CHANGED (rule `2`).** Four counters are added
**beside** it, and the report prints three separate denominators on three separate lines:

| counter | what it counts | denominator |
|---|---|---|
| **`calls`** | every `posIsOnScreen` call | — it IS the denominator |
| **`roomprop`** | a prop whose **ENTIRE** room list is unrendered — **counted ONCE** | per prop |
| **`nolist`** | `chraiGetPropRoomIds` returned an **empty** list. Its own bucket: the room test never runs on it and no room knob can change it (`chr.c:131`'s `g_geChrDbgVbRooms` tracks the same case) | per prop |
| **`view`** | props rejected on the plain-view path, **counted ONCE** | per prop |
| `room` (`288`'s) | **unrendered ENTRIES traversed**, unchanged | **per entry — NOT comparable** |
| `plane[5]` (`288`'s) | **plane-HITS, multi-counted** — every rejecting bit is set, so a prop outside two planes counts twice | **per plane-hit — NOT comparable** |

**AND THE REPORT NOW CARRIES ITS OWN ARITHMETIC GATE** (rule `15`: a figure that cannot fail is not
an instrument). It prints `sum-check: ... BALANCES` or **`MISMATCH — THE PER-PROP LINE IS VOID`**:

- **roomtest ON:** `nolist + roomprop + fog + occl + box + view + dist + drawn == calls`
- **roomtest OFF:** `nolist + fog + occl + box + view + dist + drawn == calls`, and **`roomprop` is a
  SHADOW COUNT — props the room test WOULD have removed and did not.** That shadow count is the
  single most important number in ARM R2.

**THE COUNTING MOVED INTO A READ-ONLY PRE-PASS at the top of `posIsOnScreen`, and the reason is the
arm:** with the falsifier on, the loop breaks on the first entry, so an in-loop counter would
**silently change its own meaning between the arm and its control** — `275` §1's family. In the
pre-pass, `room` and `roomprop` read **identically in both arms** (proved in §2).
`getROOMID_isRendered` is a bare array read (`bg.c:3196`) with no side effects, so walking the list
twice decides nothing.

### 2. `GETV_PROPROOMTEST=0` — THE FALSIFIER FOR THE STANDING CANDIDATE

`288` named the site: **`propobj.c`, `getROOMID_isRendered(roomnum)` at the room gate of
`posIsOnScreen`.** Neither `GETV_ROOMSCISSOR` nor `GETV_PROPCULLBOX` touches it; it has survived two
arms without being tested once. **IT IS A CANDIDATE. IT IS NOT ESTABLISHED, AND THIS KNOB DOES NOT
ESTABLISH IT — IT ONLY LETS THE ARM FAIL.**

- **Written the same way `287` wrote `GETV_PROPCULLBOX`:** OPT-IN, **inert when unset** (`on = 1`
  unless the value is exactly `0`), a **banner that says it took**, `FALSIFIER ONLY, MUST NEVER
  SHIP ON` in the banner text itself. A run that does not set it is the shipping code byte for
  byte — `48`'s one behaviour change.
- **OFF = `posIsOnScreen` enters its body on the prop's FIRST room without asking whether that room
  is being rendered.** Nothing else in the function changes. If the room list is **empty** the loop
  is never entered and the knob does nothing — **it cannot manufacture a prop out of nothing**, which
  is why `nolist` is its own bucket.
- **►► IT IS APPLIED AT ONE CALL SITE AND DELIBERATELY NOT INSIDE `getROOMID_isRendered()`.** That
  function is also read by `chraction.c:2972`/`:9875`/`:10768`, `chrai.c:1903`, `chrprop.c:564`/`:596`,
  `explosion.c:1907`/`:2326` and `chr.c:179` — **AI, SPAWN, and scorch/impact logic.** A chokepoint
  there would silently change **what characters DO** while claiming to be a rendering falsifier.
  **This is exactly why `GETV_ROOMSCISSOR` does not live in `bgGet2dBboxByRoomId`** (`287` §1), and
  it is the rule that keeps a diagnostic from becoming a game-logic edit.
- **EXPECTED SIDE EFFECT, A COST AND NOT A FIX:** props in rooms the renderer is not drawing are
  submitted — props through walls, props in closed-off rooms, more work per frame.

**NO FIX IS PROPOSED AND NONE MAY BE INFERRED.** The site is named; the mechanism — *why* a room the
player can see into is marked not-rendered — is **unread**, and this sheet does not read it.

---

## §0b — THE REGEN AND THE COMMITS, IN ORDER, AND ONLY AFTER THE ARMS

**Nothing here touches `getv/port/**`, so `tools/fetch-thirdparty.sh verify` MUST STILL SAY
`15/15` after this build.** If it says `DIFFERS` on anything, something was edited that this sheet
did not intend and **the build is not the one described here.** That is a new gate and it is free.

**COMMIT ORDER, AFTER THE ARMS ARE WORN (`00-STATE` §6, and every one of these is a MAIN-PC action):**
1. `vendor/ge-decomp` — **BY EXPLICIT PATH LIST, NEVER `git add -A`** (2,097 CRLF-dirty files sit
   there and `7a4e7bfd` is what happens when they get swept in). `git diff --cached --stat` must read
   **168 insertions / 11 deletions across three files** before committing.
   Message: `COMMIT-MESSAGE-2026-08-31g-decomp.txt`, **in the `GoldenEyeVR` ROOT** (`287`: a message
   file beside the repo it describes is invisible to `commit-now.ps1`).
2. `goldeneye-native` — the harness only (`getv/tools/cullwhy_harness.sh`, `cullwhy_harness.c`).
   Message: `COMMIT-MESSAGE-2026-08-31g-native.txt`.
3. `GoldenEyeVR` — this sheet and the `289` doc. Message: `COMMIT-MESSAGE-2026-08-31g.txt`.

**`COMMIT-NOW.cmd` WILL NOT DO STEP 1** — `vendor/` is gitignored by `goldeneye-native` and invisible
to all three of its passes.

---

## §1 — BUILD, AND THE BINARY GATE. **FIFTEEN STRINGS.**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
& getv\build_windows.ps1 -Target all *> build_289_roomtest.log 2>&1
Select-String -Path build_289_roomtest.log -Pattern 'error|Error|FAILED' | Select-Object -First 20
Get-Item F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows\goldeneye.exe |
    Select-Object FullName, LastWriteTime, Length
$exe = 'F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows\goldeneye.exe'
$txt = [Text.Encoding]::ASCII.GetString([IO.File]::ReadAllBytes($exe))
foreach ($k in 'GETV_ROOMSCISSOR','GETV_PROPCULLBOX','GETV_PACEHIST','GETV_CULLWHY','GETV_PROPROOMTEST') {
    if ($txt.Contains($k)) { "$k IS IN THE BINARY" } else { "$k IS **NOT** IN THE BINARY -- STOP" }
}
foreach ($k in 'SIX SITES','pacehist','PANEL REPORTED BY SDL','jitter: sd=','GETV_FPS=panel REFUSED','twin-disagree','proproomtest','PER PROP (one per posIsOnScreen call)','sum-check:','PER ENTRY (NOT a prop count') {
    if ($txt.Contains($k)) { "marker '$k' present" } else { "marker '$k' MISSING -- STALE BUILD, STOP" }
}
```
**All FIFTEEN must say IS IN / present. The five that are new to `289` are `GETV_PROPROOMTEST`,
`proproomtest`, `PER PROP (one per posIsOnScreen call)`, `sum-check:` and `PER ENTRY (NOT a prop
count`.** **A knob that is not in the binary reads as a clean null result** (`133`, `268` §4).
**Timestamp must be newer than `2026-08-31 17:09:32`** (the `288` binary, 18,035,038 bytes).

**AND THE FREE ONE, SAME SHELL, AFTER THE BUILD:**
```
"C:\Program Files\Git\bin\bash.exe" -lc "cd /f/Projects/GEVR/GoldenEyeVR/goldeneye-native && tools/fetch-thirdparty.sh verify"
```
**It must still read `15/15 files match pristine + patch`.** Nothing in `289` touches `getv/port/**`;
a `DIFFERS` here means something was edited that this sheet did not intend.

---

## §2 — IT IS ALREADY VALIDATED OFFLINE. **AND THE VALIDATION IS RE-RUNNABLE, WHICH `288`'s WAS NOT.**

`getv/tools/cullwhy_harness.sh` **extracts the real `getv_cullwhy_report()` and `posIsOnScreen()`
out of `propobj.c` BY NAME, brace-matched** — so it can never test a stale copy — stubs every
predicate, and drives them with nine synthetic worlds whose answers are known by construction.
Clean under `gcc -Wall -Wextra`. **`288`'s pacehist harness lived only in the session and is gone;
this one is a file, for the same reason `00-STATE` §3 gives about `GETV_CCPROBE`.**

`[MEASURED]` offline, **before any build**, nine cases x two arms, **0 failures**:

| case | roomtest **ON** | roomtest **OFF** | `room` entries | `roomprop` |
|---|---|---|---|---|
| empty room list | `nolist` | `nolist` | 0 | 0 |
| **no room rendered (3 entries)** | **`roomprop`** | **`fog`** | **3 — SAME** | **1 — SAME** |
| 2nd room rendered | `drawn` | `drawn` | 1 — SAME | 0 — SAME |
| fog / occl / box / view / dist / drawn | each its own bucket | unchanged | 0 | 0 |

**ROW 2 IS THE WHOLE POINT AND IT IS TWO CLAIMS AT ONCE.** The knob moves that prop from `roomprop`
to the rest of the pipeline — **that is the falsifier's mechanism, demonstrated before the build** —
**while `room` and `roomprop` read IDENTICALLY in both arms**, which is the arm-invariance the
pre-pass exists for. `calls` is 1 in every case and the sum-check **BALANCES** in all eighteen.

**AND THE GATE IS SHOWN TO FAIL.** A negative control double-counts one bucket on purpose and the
report prints
`sum-check: ... = 10 vs calls=9 -- MISMATCH -- A CALL IS BEING COUNTED TWICE OR NOT AT ALL.`
**`279` §7: a detector tuned on the positive frame passes its own contract until it meets the
negative one.**

**WHAT THE HARNESS CANNOT DO, STATED PLAINLY:** it proves the arithmetic and the arm-invariance. **It
cannot prove the counters sit on the path the game actually takes, and it cannot prove the knob
changes the picture.** That is the run — **and `288` §3 is the reason this caveat is not decoration:
its harness returned `jdm` 40.9% and hardware returned 14.5%.**

---

## §3 — THE FIVE GATES, ON EVERY RUN IN THIS SHEET

1. the `roomscissor` banner (and `sites:` all six non-zero at exit);
2. **`ours: x=367.333`** in the VIEWPORT line — **`x=0` means `GETV_WIDESCREEN` came back ON**;
3. the `simhz` line at **`60 / cap` fields per frame** — a RATIO, never `0.500000`
   **(and in ARM S2 the correct reading is `simhz OFF` / no banner — see §7)**;
4. **zero** `simulation held to`;
5. a terminating **`game_exit requested`**.

**PLUS `[getv][slot] GETV_SLOTFREE resolved to 1 (env=1)`.** `GETV_SLOTFREE=1` is in every block and
is not optional: every block opens with `Remove-Item Env:GETV_*`, the per-user cfg then wins on
config search path 4, and `287` 4C died at the intro cast with `NO SLOT: required=155 free=0` ->
`0xc0000005`. `288` measured no SLOTFREE line in the `pdbar` cfg — **the rule is not retired**
(`00-STATE` §0: the cfg is per-user and the same human runs under different logins).

### THREE THINGS THAT WILL LOOK LIKE REGRESSIONS IN EVERY ARM AND ARE NOT

- **THE FRONT-END MENU TEXT IS MISALIGNED.** Gate 2 is `ours: x=367.333`; the fault condition is
  `ge_offset_x() != 0`. **They are the same number, so a run that PASSES gate 2 has broken menu text
  BY CONSTRUCTION.** `00-STATE` OPEN item 2. **Do not "fix" it by moving to `1825x1369`: that prints
  `ours: x=0`, which is also what `WIDESCREEN=1` prints, so gate 2 would silently stop
  discriminating** (rule `17`).
- **`GETV_ROOMSCISSOR=0` MAKES ROOMS OVERDRAW EACH OTHER.** Dropping side textures and blue walls
  are **the knob's own banner text**, not an old build. **Judge the slabs, not the picture.**
- **In ARM R2, props appear through walls and in rooms you cannot see into.** That is
  `GETV_PROPROOMTEST=0` working. **A COST, NOT A FAULT.**

---

# ►►►► PART ONE — THE VANISHING PROPS ◄◄◄◄

**Both arms: Streets, `GETV_STAGE=29`. GO TO THE SAME SPOT THAT PRODUCED THE VANISHING CAR AND THE
GREEN BUSHES, LOOK THE SAME WAY, AND MAKE THEM VANISH ON PURPOSE, then quit normally.** The counters
are cumulative over the run, so **a run that never reproduces the symptom measures nothing.**
**MATCH THE TWO RUNS: same spot, same route, comparable length.** Activity matching cannot be
verified from a log at all — only the session lead knows (`288` §4 scope limit 1). **Stated, not
assumed.**

## §4 — ARM R1. THE SHIPPING DEFAULT, WITH THE DENOMINATORS FIXED.

**This is not a re-run of a worn arm.** `288` ARM 8's answers about `dist`, `box` and the planes are
in `00-STATE` and are not re-litigated. **R1 exists for `roomprop`, `nolist`, `view`, `calls` and the
sum-check — five numbers that did not exist when ARM 8 ran** — and it is R2's control.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
$env:GETV_SLOTFREE     = "1"
$env:GETV_VSYNC        = "1"
$env:GETV_FPS          = "panel"
$env:GETV_SIMHZ        = "query"
$env:GETV_SIMDIV       = "1"
$env:GETV_WIDESCREEN   = "0"
$env:GETV_ROOMSCISSOR  = "0"
$env:GETV_WINDOW       = "2560x1369"
$env:GETV_STAGE        = "29"
$env:GETV_CULLWHY      = "1"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_289_R1_cullwhy_denominators.log 2>&1
Select-String -Path run_289_R1_cullwhy_denominators.log -Pattern 'cullwhy\]'
Select-String -Path run_289_R1_cullwhy_denominators.log -Pattern 'GETV_FPS=panel|PANEL REPORTED BY SDL|pace: '
Select-String -Path run_289_R1_cullwhy_denominators.log -Pattern 'roomscissor\] sites:|ours: x=|fields per frame|slot\] GETV_SLOTFREE|simulation held to|game_exit requested'
(Select-String -Path run_289_R1_cullwhy_denominators.log -Pattern 'dlgrab_\d+\.txt' -AllMatches).Matches.Value | Sort-Object -Unique
```
**`GETV_PROPROOMTEST` IS DELIBERATELY ABSENT** so the reading describes the shipping configuration.
**`GETV_PROPCULLBOX` IS DELIBERATELY ABSENT TOO**, so `box` is live and R1 is comparable with
`288` ARM 8 — **one knob, and only one, moves between R1 and R2.**

## §4a — ►►►► R1 RAN. THE DENOMINATOR IS FIXED, THE SUM-CHECK BALANCES, AND `roomprop` IS 92.5%. ◄◄◄◄

**`[MEASURED]` 2026-08-31 18:50, `run_289_R1_cullwhy_denominators.log`, binary `18:47:30` /
18,036,265 bytes.** Gates clean: `GETV_FPS=panel -> 120 Hz, QUERIED FROM SDL`, `pace: 120 fps cap
on, vsync=1`, `simhz 0.500000` (= `60/120`), `ours: x=367.333`, `SLOTFREE resolved to 1 (env=1)`,
all six `roomscissor` sites non-zero, **zero** `simulation held to`, `props interpolated 0`,
terminating `game_exit requested`. `twin-disagree=0`.

```
PER PROP   calls=1301498 | nolist=0 roomprop=1203533 fog=12257 occl=2241
                            box=45556 view=0 dist=0 drawn=37911
sum-check  nolist+roomprop+fog+occl+box+view+dist+drawn = 1301498 vs calls=1301498 -- BALANCES
PER ENTRY  room-entries=1327916
PER PLANE  near=0 left=0 right=0 top=0 bottom=0 | plane-hits=0 vs view=0 props
```

**THE SUM-CHECK BALANCES ON HARDWARE, EXACTLY, FIRST RUN.** The gate that was shown to print
`MISMATCH` offline (§2) prints `BALANCES` here. **Every call is accounted for exactly once**, so the
per-prop line is readable — which is the whole of job 1.

**►► `room` IS NOW COMPARABLE, AND THE COMPARISON IS `roomprop / box = 26.4x`.** `288` §6 said
*"`room` is very likely still the largest term. BY HOW MUCH IS NOT MEASURED."* It is measured now:
**1,203,533 props against 45,556 — and `288`'s unsupported "29x" was in the right neighbourhood for
the wrong reason.** The entries figure moved too (`1,134,409` → `1,327,916`), which is what a
different run length does to a cumulative counter.

**►► AND `room-entries / roomprop = 1.103`.** A prop the room test removes has, on average, barely
more than ONE unrendered entry in its list — so the two denominators were never going to differ by
an order of magnitude, and the reason `288` could not be read was not that the gap was large but
that **nobody knew what the gap was.**

### ►►►► THE NUMBER IS BIG AND THE NUMBER IS NOT EVIDENCE. READ THIS BEFORE R2. ◄◄◄◄
**92.5% of every `posIsOnScreen` call is rejected by the room test — and that is what ANY broad-phase
room-visibility cull would read**, because at any instant the overwhelming majority of a level's
props are in rooms that are not being drawn at all. **`roomprop` being the largest term is EXPECTED
BY CONSTRUCTION and says NOTHING about the car in the corner.** This is `275` §1's shape — a story
that fits — and it is written down here so that a big number in R1 cannot be read as a result.
**What R1 establishes is only this: `roomprop` is NOT ZERO, so §6 outcome 2 did not fire and R2 is a
live test.** R1 cannot convict and does not.

### THREE MORE READINGS, TWO EXPECTED AND ONE NOT

1. **`view=0` and all five planes `0` — EXPECTED BY CONSTRUCTION, NOT EVIDENCE.** With
   `GETV_PROPCULLBOX` at its shipping default the plane path is unreachable (`288` §6 defect 3,
   restated in §9(c) of this sheet before the run). The new `view` counter sits in the same `else`
   branch and reads zero for the same reason. **The sum-check balancing WITH `view=0` is the
   positive confirmation that it is unreachable rather than broken.**
2. **`dist=0`, A THIRD TIME.** `288` ARM 8 and 8b, now R1. The `32000` radius stays dead.
3. **►► `fog=12257` IS BYTE-IDENTICAL TO `288` ARM 8's `fog=12257`, AND EVERY OTHER COUNTER MOVED**
   (`occl` 2163→2241, `box` 38996→45556, `drawn` 36809→37911, entries 1134409→1327916). **Two runs,
   two sessions, two different routes, and a five-digit exact match. `[MEASURED]`, AND NO
   EXPLANATION IS OFFERED.** What it bounds: **a substantial part of these cumulative counts is
   DETERMINISTIC — boot, load, the front-end — and is not driven by where the player looked.** The
   report has no windowing, so it cannot separate them. **That is the same class as `288` §4's boot
   window, and it is a limit on what R1-vs-R2 can be asked, not a fault in either.**

**A TENTH CLEAN `dlgrab`, ANNOUNCED BY THIS LOG (`279` §2 provenance):** `dlgrab_7675.txt`, taken by
F9 **with the prop visibly vanished**, BMP 10,513,974 bytes = `54 + 2560*1369*3`, so it is this run's.
**TWO distinct scissors only — `(0,120)-(1280,840)` x43 and `(0,0)-(1280,960)` x3, BOTH FULL WIDTH,
ZERO sub-view rects.** With ARM 5's eight and `288`'s ninth that is ten. **The vanishing prop is not
a scissor.**

## §5 — ARM R2. THE FALSIFIER. **`GETV_PROPROOMTEST=0`, EVERYTHING ELSE IDENTICAL TO R1.**

Same block as §4 with **one line added** and the log renamed:
```powershell
$env:GETV_PROPROOMTEST = "0"
```
```powershell
.\goldeneye.exe *> run_289_R2_proproomtest_off.log 2>&1
Select-String -Path run_289_R2_proproomtest_off.log -Pattern 'proproomtest\]'
Select-String -Path run_289_R2_proproomtest_off.log -Pattern 'cullwhy\]'
Select-String -Path run_289_R2_proproomtest_off.log -Pattern 'roomscissor\] sites:|ours: x=|fields per frame|slot\] GETV_SLOTFREE|simulation held to|game_exit requested'
```

**THE GATE THAT SAYS THE KNOB TOOK:** the log must carry
`[getv][proproomtest] GETV_PROPROOMTEST=0 -- posIsOnScreen NEUTRALISES getROOMID_isRendered`.
**Without that line the run is a clean null result and says nothing** (`133`, `268` §4).

## §6 — WHAT EACH OUTCOME MEANS, WRITTEN BEFORE THE RUN (rule `15`, `P5`)

**READ THESE IN ORDER. THE FIRST THREE ARE ABOUT THE INSTRUMENT AND THEY OUTRANK THE ARM.**

1. **`sum-check` SAYS `MISMATCH` in either run** -> **the per-prop line is VOID.** A call is counted
   twice or not at all. Fix it and re-run; read nothing else off that log.
2. **`roomprop = 0` IN R1** -> **the room test never removes a whole prop in this run.** Then R2 can
   change nothing by construction, **and BOTH arms are void as a test of the candidate.** That is a
   RESULT, not a null: `getROOMID_isRendered` is not on the path that removes these props, the
   standing candidate falls without R2 having to say anything, and the search moves. **It also
   means the `288` reading was entries in lists that always contained a rendered room.**
3. **`nolist` LARGE** -> a large fraction of props reach `posIsOnScreen` with **no rooms at all**, a
   case no room knob can touch and one this sheet has not thought about. **Stop and read
   `chraiGetPropRoomIds` before interpreting anything.**
4. **PROPS STILL VANISH IN R2, banner present, `roomprop` non-zero in R1** -> **the room test is
   ELIMINATED.** Three of the six tests are now dead by measurement. **That is a real result and it
   is exactly how ARM 7 ended. DO NOT RE-RUN R2 HOPING** (`288` §8b outcome #2). The next arm goes
   to what is left: the `getinstsize(model)` margin sphere (`model.c:1184`) and the `4/3` the
   frustum report has been printing unexplained since `288` §5.4.
5. **PROPS STOP VANISHING IN R2, banner present, `roomprop` non-zero in R1** -> **the site is
   CONVICTED as the place the prop is removed.** `propobj.c`'s room gate. **THAT IS ALL IT MEANS.
   NO FIX IS PROPOSED AND NONE MAY BE INFERRED** — *why* a room the player can see into is marked
   not-rendered is a different question in a different file, and widening anything is `P2`/`P3` at
   stereo, never a stored constant (`288` §8a).
6. **PROPS STOP VANISHING IN R2 BUT `roomprop = 0` IN R1** -> **CONTRADICTION.** The knob changed
   the picture without changing any counted rejection. Either the counter is wrong or the knob has
   a second effect nobody wrote down. **STOP AND READ. Do not record a conviction.**
7. **`box`, `view`, `drawn` ALL RISE IN R2 vs R1** -> **EXPECTED BY CONSTRUCTION AND NOT EVIDENCE.**
   Neutralising the room gate sends props that used to stop there on into the remaining tests.
   **The number to compare across the two arms is `roomprop`, which is arm-invariant by design**
   (§2) — and if `roomprop` swings wildly between R1 and R2, **the runs were not activity-matched**
   and the comparison is `287`'s unmatched hint all over again.
8. **ALL COUNTS ZERO** in a level that visibly drops props -> the counters are not on the path that
   removes them and **the search is in the wrong function.** `288` wrote this and it did not fire;
   it is carried forward unchanged.

**NO PREDICTION IS WRITTEN FOR WHICH OF 4 AND 5 WINS. THAT IS THE MEASUREMENT.**

---

## §6a — ►►►► R2 RAN. THE PROPS STILL VANISH. THE ROOM TEST IS ELIMINATED. ◄◄◄◄

**`[MEASURED]` 2026-08-31 18:53, `run_289_R2_proproomtest_off.log`, same binary.** **THE KNOB TOOK** —
`[getv][proproomtest] GETV_PROPROOMTEST=0 -- posIsOnScreen NEUTRALISES getROOMID_isRendered` is in
the log, so **this is not a clean null result** (`133`, `268` §4). Gates clean: panel 120 queried,
`simhz 0.500000`, `ours: x=367.333`, `SLOTFREE resolved to 1 (env=1)`, six sites non-zero, zero
`simulation held to`, `props interpolated 0`, terminating `game_exit requested`, `twin-disagree=0`.

**`[REPORTED]` BY THE SESSION LEAD, WITH THE ROOM TEST NEUTRALISED: *"still able to."* THE PROPS
STILL VANISH.** **§6 outcome 4, written before the run, FIRED:** *"the room test is ELIMINATED. That
is a real result and it is exactly how ARM 7 ended. DO NOT RE-RUN R2 HOPING."*

```
R1 (roomtest ON )  calls=1301498 | nolist=0 roomprop=1203533 fog=12257  occl=2241  box=45556 view=0      dist=0     drawn=37911
R2 (roomtest OFF)  calls=1385191 | nolist=0 roomprop=1285030 fog=544303 occl=88708 box=42409 view=436784 dist=17124 drawn=255863
```

**`getROOMID_isRendered` AT `posIsOnScreen`'s ROOM GATE IS NOT THE MECHANISM. `288`'s STANDING
CANDIDATE IS DEAD, AND IT WAS KILLED BY THE FALSIFIER WRITTEN FOR IT, NOT BY ARGUMENT.**

**THE ONE THING THIS ARM DOES NOT EXCLUDE, STATED RATHER THAN GLOSSED:** a prop rejected by the room
test **and also** by a downstream test would still vanish with the room gate neutralised. **R2
cannot separate that from "the room test never touched it."** It is the same limit ARM 7 carried and
it is not new — but it is the reason the verdict is *eliminated as the mechanism*, not *proved
innocent*.

### 1. ►►►► THE INSTRUMENT VALIDATED ITSELF TWICE, AND THE SHADOW COUNT WORKS ◄◄◄◄
**The sum-check BALANCES under BOTH identities** — `1,301,498` with `roomprop` IN, `1,385,191` with
`roomprop` OUT. **The OFF identity balancing is the positive proof that `roomprop` really is a
shadow count in that arm** and not a double-count, which is the one thing the offline harness could
assert but not demonstrate on real data.

**AND THE ARM-INVARIANCE CLAIM HOLDS ON HARDWARE: `roomprop` is 92.5% of calls in R1 and 92.8% in
R2** — 0.3 points apart across two separately-walked runs. **That is what §0a's read-only pre-pass
was built for**, and it is what makes the two arms comparable at all.

### 2. ►►►► `dist=0` WAS A **MASKED ZERO**, AND THAT IS THE METHODOLOGICAL FINDING OF THIS ARM ◄◄◄◄
**`dist` has read 0 three times — `288` ARM 8, ARM 8b, and R1 — and `00-STATE` records the `32000`
radius as DEAD BY MEASUREMENT. `[MEASURED]` IN R2 IT READS `17,124`.**

The radius test sits **downstream** of the room test: it is only reached by a prop that has already
passed room, fog, occl and the box. **With the room gate rejecting 92.5% of everything, the far
props never arrived — so the zero was not the test being inert, it was an earlier test getting
there first.**

**WHAT SURVIVES AND WHAT DOES NOT:**
- **SURVIVES:** in the SHIPPING configuration, across three runs that reproduced the symptom, the
  radius removed **zero** props. It is not the mechanism. **That verdict is untouched.**
- **DOES NOT:** any reading of *"`dist=0` therefore the test is inert / dead / could never matter."*
  **It fires 17,124 times the moment something upstream stops shadowing it.**
- **THE GENERAL RULE, AND IT IS NEW:** **a zero in a test that sits downstream of a test rejecting
  92.5% of everything is a MASKED ZERO, not an exoneration.** It is `275` §1's grep-for-a-guard in
  a new costume — **the counter was read without reading the ORDER it sits in**, exactly as `288`
  §6 read `room` without reading the loop it sits in. **Same session, same shape, one level over.**

### 3. THE SHIPPING CONFIGURATION NOW HAS ALMOST NOTHING LEFT THAT CAN REMOVE A PROP
Read R1's line again with the eliminations applied. Of the six ways `posIsOnScreen` can say no:

| test | R1, shipping | status |
|---|---|---|
| `room` | 1,203,533 | **ELIMINATED by R2** (`[REPORTED]` wear, this arm) |
| `box` | 45,556 | **ELIMINATED by ARM 7** (`[REPORTED]` wear) and `box=0` in 8b with the symptom present |
| `dist` | 0 | removes nothing in the shipping config (three runs) |
| `view` / the five planes | **0** | **UNREACHABLE with `PROPCULLBOX` on** — `288` §6 defect 3, now confirmed by a balancing sum-check |
| `fog` | **12,257** | **not eliminated, never tested** |
| `occl` | **2,241** | **not eliminated, never tested** |

**►► SO IN THE SHIPPING CONFIGURATION THE FIVE VIEW PLANES REMOVE ZERO PROPS.** Everything `288`
measured about left/right/top/bottom came from 8b, which had `PROPCULLBOX=0`. **In the picture the
session lead is actually looking at, that path is not taken.**

**►► AND THAT LEAVES TWO SMALL COUNTERS AND ONE BIG ASSUMPTION.** `288` wrote *"`posIsOnScreen` is
the ONLY place that decides a prop is not drawn."* **That is a source read, not a measurement, and
it is now the load-bearing claim.** §6 outcome 8 anticipated the shape — *"the counters are not on
the path that removes them and the search is in the WRONG FUNCTION"* — and it did not fire as
written, because the counters are plainly on **a** path. **It may still be the wrong one.**
**NO CAUSE IS NAMED AND NO FIX IS PROPOSED.**

### 4. `fog` IS THE STRANGEST NUMBER IN EITHER LOG AND IT IS NOT EXPLAINED
`fog=12,257` in R1 is **byte-identical** to `288` ARM 8's `fog=12257` — two sessions, two routes,
while every other counter moved. In R2 it is **544,303**. **`[MEASURED]`, twice, and no explanation
is offered.** Combined with §4a's note, it says a large part of these cumulative counts is
**deterministic** — boot, load, front-end — and the report **has no windowing at all**, so it cannot
separate the deterministic part from the part the player caused. **That is `288` §4's boot-window
lesson one level over, and it is the next instrument, not a finding.**

### 5. WHAT WAS OWED AND DID NOT ARRIVE
**No `dlgrab` line appears in `run_289_R2`.** F9 did not land in this arm, so there is no dump of the
prop vanishing **with the room test off** to set beside `dlgrab_7675`. **Recorded as owed, not
glossed** (`279` §2: a log's own announcements are the only admissible provenance, and this log
announces none).

---

# PART TWO — SMOOTHNESS. THE LAST CANDIDATE, AND IT NEEDS NO BUILD.

## §7 — S1 / S2 / S3. **`GETV_SIMHZ` ON vs OFF — AND THE CONFOUND IS NAMED FIRST.**

`288` J1/J2 came back **equal** — settled `jdp` 8.29% (`vsync=1`) vs 7.70% (`vsync=0`), overlapping
ranges, `vsync=0` marginally **lower**. **`vsync` is cleared at the presented-frame resolution, at
two resolutions now (`287` 4E and `288` J1/J2), and `GETV_SIMHZ` is the only candidate left
standing.** `285` S1's *"super smooth"* ran **with** it; most of this project ran **without** it, and
that comparison has never been run as an arm.

### ►►►► READ THIS BEFORE DESIGNING ANYTHING ON THE RESULT: THE ARM HAS A CONFOUND AND IT IS STRUCTURAL ◄◄◄◄

**`GETV_SIMHZ` does not only change how the sim is quantised — it changes HOW FAST THE WORLD RUNS.**
With the term off at a 120 Hz cap the world advances **one whole field per frame**, so it runs at
`cap/60` = **2x**. `277` §4 measured that class of thing and the session lead wore it: *"everything
was moving faster except bond."* **So S2 is not a single-variable arm against S1, and pretending
otherwise would be `287` M1/M2's diagonal again.** Hence S3.

**AND THE 2x2 HAS ONLY THREE CELLS, WHICH IS ITSELF WORTH RECORDING:** at `FPS=60` the term computes
`60/60` = **1.000 fields per frame**, which is what the untermed code does anyway — **at a 60 Hz cap
`GETV_SIMHZ` is a no-op and the two cells are the same run by construction.** `288` V1 printed
`simhz 1.000000` and is the evidence.

| arm | recipe | world speed | what it isolates |
|---|---|---|---|
| **S1** | `VSYNC=1 FPS=panel SIMHZ=query` | **retail** | `285` S1's *"super smooth"* configuration |
| **S2** | `VSYNC=1 FPS=panel` **SIMHZ unset** | **`panel/60` — 2x on the 120 Hz desk** | what most of this project actually ran |
| **S3** | `VSYNC=1 FPS=60` **SIMHZ unset** | **retail** | the term's absence **without** the speed change |

**S3 IS THE CELL THAT MAKES THIS AN EXPERIMENT INSTEAD OF A DEMONSTRATION.** If S2 feels wrong and
S3 does not, the difference is the **2x world**, not the sim quantisation.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
$env:GETV_SLOTFREE     = "1"
$env:GETV_VSYNC        = "1"
$env:GETV_FPS          = "panel"
$env:GETV_SIMHZ        = "query"
$env:GETV_SIMDIV       = "1"
$env:GETV_WIDESCREEN   = "0"
$env:GETV_ROOMSCISSOR  = "0"
$env:GETV_WINDOW       = "2560x1369"
$env:GETV_PACEHIST     = "600"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_289_S1_simhz_on.log 2>&1
Select-String -Path run_289_S1_simhz_on.log -Pattern 'PANEL REPORTED BY SDL|GETV_FPS=panel|pace: '
Select-String -Path run_289_S1_simhz_on.log -Pattern 'pacehist\] .*jitter:|pacehist\] .*sub-1x|pacehist\] .*bins:'
Select-String -Path run_289_S1_simhz_on.log -Pattern 'roomscissor\]|ours: x=|fields per frame|simhz|slot\] GETV_SLOTFREE|simulation held to|game_exit requested'
```

**S2 — the same block with ONE line REMOVED (`$env:GETV_SIMHZ`), log
`run_289_S2_simhz_off.log`.** Because a block that omits a knob restores its default, **this is the
one place in this sheet where omitting is the point, and the gate is inverted: gate 3 must show
`simhz OFF` or no `simhz` banner at all.** If a `fields per frame` line appears, `$env:` persisted
from the previous window (`00-STATE` §6) and **the run is void.**

**S3 — the S2 block with `$env:GETV_FPS = "60"`, log `run_289_S3_simhz_off_cap60.log`.**
**`GETV_FPS=60` is deliberate and is NOT the `panel` spelling**: S3's whole purpose is the retail
world speed, and on the 180 Hz desk `panel` would give 3x.

### HOW THE THREE ARE SCORED — AND `jdp` IS NOT THE ANSWER TO THE COMPLAINT

- **THE NUMBER:** settled-window `jdp`, **S1 vs S2 vs S3, against EACH OTHER.** **No absolute
  threshold.** `288` wrote `jdp < 10%` and `jdm > 20%` and hardware falsified both — 14.5% against
  the harness's 40.9%, and V1's own boot window read 32.8%. **A jitter threshold is scored on
  SETTLED windows; the boot window is REPORTED, NEVER SCORED.**
- **Read `PANEL REPORTED BY SDL: <n> Hz` on the first line of every log before anything else.** Every
  bin prediction is `panel/cap` and every simhz gate is `60/cap`. **Ratios, never bare numbers.**
  S3 lands in `2x` on a 120 Hz panel and `3x` on the 180 Hz one, **and both are correct.**
- **THE WEAR QUESTION, ASKED PRECISELY:** not *"which is smoother"* — S2's world is 2x and will feel
  different for reasons that have nothing to do with pacing. The question is
  **"does the turn show the WAITING symptom `285` reported — and in which of the three?"**

### WHAT EACH OUTCOME MEANS, WRITTEN BEFORE THE RUN

- **`jdp` EQUAL ACROSS ALL THREE** -> **`GETV_SIMHZ` is cleared at the presented-frame resolution
  too, and the complaint has NO CANDIDATE LEFT.** That is a real and uncomfortable result: it means
  the symptom lives where `GETV_PACEHIST` cannot see — **the phase between the sim step and the
  present**, which no instrument in this project measures. **The next instrument is that phase, not
  a finer bin.**
- **S2 SHOWS THE WAITING SYMPTOM AND S3 DOES NOT** -> the carrier is the **2x world**, not the
  term's quantisation, and `285` S1's *"super smooth"* was **retail speed**, not smoothness.
- **S2 AND S3 BOTH SHOW IT, S1 DOES NOT** -> the carrier **is** `GETV_SIMHZ`'s fractional delta, with
  the speed confound controlled by S3. **This is the only cell that would support the standing
  reading, and it needs S3 to mean anything.**
- **THE SESSION LEAD REPORTS S2 AS "FASTER" RATHER THAN "JUDDERY"** -> **that is an answer, not a
  failed run.** It says the historical configuration was wrong in a way that has already been fixed,
  and the *"it feels like it's waiting"* report is still unexplained.

---

## §7a — S1 RAN. **IT REPRODUCES `288` J1 ACROSS TWO BINARIES, AND `jd > sd` IN EVERY SETTLED WINDOW.**

**`[MEASURED]` 2026-08-31 18:58, `run_289_S1_simhz_on.log`, binary `18:47:30`.** Gates clean:
`GETV_FPS=panel -> 120 Hz, QUERIED FROM SDL`, `pace: 120 fps cap on, vsync=1`,
`PANEL REPORTED BY SDL: 120 Hz`, `simhz 0.500000` (= `60/120`), `ours: x=367.333`,
`SLOTFREE resolved to 1 (env=1)`, zero `simulation held to`, terminating `game_exit requested`.
17 windows.

**`[REPORTED]` BY THE SESSION LEAD: *"no waiting feel on that run."*** This is `285` S1's recipe and
it behaves as `285` S1 did.

**BOOT IS WINDOWS 1-4 AND TWO INDEPENDENT SIGNALS AGREE ON WHERE IT ENDS** — `sd` collapses from
1.3-2.8 to ~0.48-0.57 at window 5, and the OLD bins stop carrying hitches at exactly the same
window (`<0.5x` and `5x+` pairs in 1-4; **`600/600` in `1x` in every one of 5-16**). **Window 4 is
the worst window in the run at `jdp` 10.5% and it is REPORTED, NEVER SCORED** — `288` V1's lesson,
applied without having to be re-learned.

| | settled windows | `jdp` range | **`jdp` mean** |
|---|---|---|---|
| `288` **J1** (`vsync=1 FPS=panel SIMHZ=query`) | 10 | 7.3 - 9.2% | **8.29%** |
| **S1** (same recipe, new binary, new session) | **12** (w5-w16) | 7.1 - 9.9% | **8.54%** |

**S1 REPRODUCES J1 TO 0.25 POINTS ACROSS TWO BINARIES AND TWO SESSIONS.** Nobody asked for that and
it is worth more than it cost: **the statistic is stable run to run**, so a difference between S1
and S2 will be a difference in the arm and not in the day.

### ►► AND A READING NOBODY HAS TAKEN BEFORE, RECORDED WITHOUT A THEORY
**In every settled window `jd` is LARGER than `sd`** — 0.588-0.824 against 0.478-0.568. That is the
opposite of the boot windows, where `sd` is 3-5x `jd` (the outlier signature `288` §3 identified).
**For independent noise `jd/sd` is `2/sqrt(pi)` = 1.128; for a clean two-level alternation it is
2.0. The settled windows read ~1.4.** `[MEASURED]`. **NO CONCLUSION IS DRAWN AND NONE MAY BE
INFERRED FROM ONE ARM** — there is no comparison yet, `288` J1/J2 were never read this way, and
`jd/sd` is not a statistic this project has validated. **It is a direction to instrument, exactly
as `287` recorded its ragged-window hint.**

## §7b — ►►►► S2 RAN. `jdp` CAME BACK EQUAL **AND SO DID THE WEAR**. `GETV_SIMHZ` IS CLEARED. ◄◄◄◄

**`[MEASURED]` 2026-08-31 19:02, `run_289_S2_simhz_off.log`, same binary, same recipe minus one line.**
**THE INVERTED GATE PASSES: ZERO `fields per frame` lines and no `simhz` banner anywhere in the log**,
so the term really was off and `$env:` did not survive from the S1 window. All other gates clean:
panel 120 queried, `pace: 120 fps cap on, vsync=1`, `ours: x=367.333`,
`SLOTFREE resolved to 1 (env=1)`, zero `simulation held to`, terminating `game_exit requested`.
16 windows; boot is 1-3 by the same two-signal test as S1.

| | settled windows | `jdp` range | **`jdp` mean** |
|---|---|---|---|
| **S1** `SIMHZ=query` | 12 (w5-w16) | 7.1 - 9.9% | **8.54%** |
| **S2** `SIMHZ` unset, world at **2x** | 12 (w4-w15) | 7.2 - 9.1% | **8.05%** |

**THE RANGES OVERLAP ALMOST ENTIRELY; the gap is 0.49 points against a within-run spread of ~2
points; and the term-OFF arm is the SLIGHTLY LOWER one — the opposite direction from the
complaint.** **That is the same shape, the same size and the same direction as `288` J1/J2's 8.29 vs
7.70.** Every settled window is `600/600` in `1x` in both.

**AND THE WEAR ANSWER CAME BACK THE SAME WAY. `[REPORTED]` BY THE SESSION LEAD ON BOTH ARMS:
*"no waiting feel."*** S1 was `285` S1's recipe; **S2 is the configuration most of this project
actually ran**, at 2x world speed, and it does not show the symptom either.

### ►►►► §7's FIRST WRITTEN OUTCOME FIRES, AND IT IS THE UNCOMFORTABLE ONE ◄◄◄◄
*"`jdp` EQUAL -> `GETV_SIMHZ` is cleared at the presented-frame resolution too, and the complaint has
NO CANDIDATE LEFT."* **It is cleared on the NUMBER and on the WEAR, which is stronger than the
outcome asked for.** `287` 4E cleared `vsync` on the number, `288` J1/J2 cleared it again one
resolution finer, and **`GETV_SIMHZ` was the only candidate `288` left standing. It is now gone.**

**►► AND THE `jd > sd` STRUCTURE IS PRESENT IN BOTH ARMS, ~1.4 IN EVERY SETTLED WINDOW OF BOTH.**
**So it is not the term.** It is a property of this pacer at `vsync=1`, and `288` J1/J2 were never
read this way. **Still not a finding. Still no theory.**

### WHAT THIS DOES **NOT** SAY, AND IT IS THE IMPORTANT PART
**THE SYMPTOM DID NOT REPRODUCE IN EITHER ARM.** A comparison between two runs that both feel fine
cannot clear a knob of causing a symptom neither one shows — **it can only say the knob does not
CAUSE it, not that the symptom is gone.** `285`'s report is *"it's always been that way"*, made
against runs that differed from these in **more than `GETV_SIMHZ`**.

**TWO CONFIGURATION DIFFERENCES BETWEEN "ALWAYS BEEN THAT WAY" AND TODAY REMAIN UNTESTED ON WEAR,
AND BOTH ARE FREE:**
1. **`GETV_VSYNC=0`.** `287` 4E and `288` J1/J2 cleared it **on the number** — but **nobody has
   asked the eye since `285`.** If the waiting feel returns at `vsync=0` while `jdp` stays equal,
   that is not a contradiction: **it means the symptom lives where `GETV_PACEHIST` cannot see, and
   the instrument's blind spot is the finding.**
2. **`GETV_SIMDIV` UNSET.** Every block in this session pins it to `1`. `268` `[MEASURED]` that the
   unset-default branch engages above 60 Hz and **holds the simulation**, printing
   `simulation held to` — and *"the world advances on fewer ticks than frames"* is what *"it feels
   like it's waiting"* sounds like. **The gate is free and unambiguous: the banner either appears or
   it does not.** **`[INFERRED]` ONLY — this is a source-and-history read, not a measurement, and
   `275` §1's shape is exactly this kind of story that fits.**

**S3 IS STILL WORTH RUNNING AND ITS ROLE HAS CHANGED.** It was written to stop S2's 2x world from
producing a FALSE POSITIVE. S2 came back negative, so that job is done — **but the 2x could equally
have MASKED a hesitation, and S3 is the only cell that runs the term off at retail speed.** Demoted
from load-bearing to a control against masking. **Stated, not quietly dropped.**

## §7c — ►►►►►► S3 RAN AND THE SESSION LEAD RE-DIAGNOSED THE COMPLAINT. IT IS NOT GRAPHICS. ◄◄◄◄◄◄

**`[MEASURED]` 2026-08-31 19:06, `run_289_S3_simhz_off_cap60.log`.** Gates clean: `pace: 60 fps cap
on, vsync=1`, no `simhz` banner (correct — the term is off), `ours: x=367.333`,
`SLOTFREE resolved to 1 (env=1)`, zero `simulation held to`, terminating record.
**Bins land in `2x` = `panel/cap` = `120/60`, as they must.**

**►► S3 HAS NO SETTLED WINDOWS AND CANNOT BE SCORED.** The run is ~1,400 intervals — two full
windows and a partial, and **both full windows carry hitches** (`<0.5x` + `5x+` pairs). `jdp` 10.6%
and 12.8% are **REPORTED, NEVER SCORED** — `288` V1's corrected contract, applied to my own arm.
**A short run has no settled region; that is a property of the run, not of the configuration.**

### ►►►►►► AND THEN THE ARM ANSWERED A DIFFERENT QUESTION THAN THE ONE IT ASKED ◄◄◄◄◄◄

**`[REPORTED]` BY THE SESSION LEAD, UNPROMPTED, AFTER S3:**
> *"this only happened to me with my mouse. So, yes, with the mouse, this last test did that weird
> thing. It doesn't happen on the controller. I tested the other ones from before that I reported
> didn't do it and it's so smooth that it helped me realize that it's the way bond walks/turns. It
> is weird when you are running on the 60hz but it smooths out on the higher speed settings and you
> realize it's the way the walk is when you go straight and then it starts to turn almost like a car
> when the mouse is moved left or right when going forward. It's not a normal wasd type feel. So the
> weirdness might be in how the mouse controls work with the controls. I think this is not graphic
> related."*

**FOUR FACTS IN THAT REPORT, AND EVERY ONE OF THEM IS NEW:**
1. **IT IS MOUSE-ONLY. THE CONTROLLER DOES NOT DO IT.**
2. **S3 REPRODUCED IT** — cap 60, and it is the only arm today that did.
3. **IT GETS BETTER AT HIGHER FRAME RATES**, which S1 and S2 are.
4. **IT IS NOT JUDDER. It is the SHAPE OF THE MOTION** — going forward and then arcing *"almost
   like a car"* rather than a WASD turn.

**RULE `16`: A REPEATED OWNER REPORT IS A RANKING ERROR, NOT NOISE — AND `HANDOVER` §5: THE OWNER'S
CORRECTION HAS OUTRANKED THE ANALYSIS EVERY TIME THEY CONFLICTED.** `285`'s *"when you turn real
fast it feels like it's waiting"* has been chased for five sessions through **vsync, the frame cap,
the pacer's sleep booking, the presented-frame distribution and the sim rate** — `287` 4A-4E,
`288` V1/V2/J1/J2, `289` S1/S2/S3 — **and every one of those came back clean or came back equal.**
**They came back clean because the fault is not in any of them.**

### ►► `287` §2 CANCELLED THE ARM THAT WOULD HAVE FOUND THIS, AND IT IS A RETRACTION
`287` §2 wrote: *"mouse and pad are the SAME PATH — `port_input.c` accumulates `ge_mouse_pend_x`
into the stick — so `285` §2's mouse-vs-pad question needs no arm."*
**THAT IS NOW CONTRADICTED BY WEAR.** They share a **SINK**, not a **PATH**: `out->rx` is the same
field, and everything upstream of it is different. **A source read cancelled an arm, and the arm was
the one that mattered.** Same family as `275` §1's grep-for-a-guard — **sixth instance, and this one
cost five sessions of instrument-building.**

### ►► WHAT THE SOURCE SAYS. `[MEASURED]`, READ NOT GREPPED, AND **NO CAUSE IS NAMED**
`goldeneye-native/getv/port/src/port_input.c:1013-1100` and `goldeneye-native/docs/MOUSE.md`. Four properties the mouse path
has and the pad path does not:

| # | `[MEASURED]` from source | why it matches the report |
|---|---|---|
| **M1** | The mouse→stick path is a **PER-FRAME ACCUMULATOR WITH NO TIMESTEP**: at most `32767` — one full deflection — is emitted **per frame** and the remainder is carried (`:1055-1063`) | a per-frame quantity, the same class as `277` §4's walk, in the **port layer** instead of the game |
| **M2** | The backlog cap is **expressed in FRAMES** — `4 * 32767` (`:1050-1053`) — so its duration is **66.7 ms at 60 fps and 33.3 ms at 120** | **fact 3**: the same hand movement is held twice as long at 60 Hz |
| **M3** | The deadzone remap lifts **ANY** non-zero movement to at least `6553` = **20% of full scale** (`:1077-1090`). `MOUSE.md`: *"Applied only to the mouse; a physical stick keeps its deadzone"* | **fact 4**: there is **no small mouse turn**. The pad has a 20% dead BAND; the mouse has a 20% **FLOOR**. Same constant, opposite behaviour, and a step at zero is what an arc-onset feels like |
| **M4** | `GE_MOUSE_COUNTS_FULL = 21` (`:942`) — **21 counts is full deflection**, and `MOUSE.md` records *"one frame of full stick is 3.54 degrees"* | a real sweep is hundreds of counts, so the map is **SATURATED nearly always** and it is M1's drain rate, not the gain, that sets the turn |
| **M5** | The **pad goes through none of M1-M4** | **fact 1**: mouse-only |

**THAT IS A MECHANISM-SHAPED SET OF FACTS AND IT IS NOT A FINDING.** It matches all four reported
facts, which is **precisely why it must be measured and not believed** — `275` §1's story that fits,
`277` §6.2's numbers without a mechanism. **NO FIX IS PROPOSED AND NONE MAY BE INFERRED.**

### ►► AND THE INSTRUMENT FOR IT ALREADY EXISTS, UNUSED, AND IS FREE
**`GETV_MOUSE_SELFTEST=<counts>`** (`port_input.c:961`, `:972`) — *"pretend the mouse moves this many
counts right every frame... the only way to put a number on it without a hand on the mouse."*
**It was written for exactly this question and has never been run against a frame rate.**
`GETV_MOUSE_SELFTEST_Y` and `GETV_MOUSE_SENS` are beside it. **No build. That is `290`'s first arm.**

**AND RULE `16` FIRES A SECOND TIME:** `00-STATE` OPEN item 9 already carries
*"`[REPORTED]` CROSSHAIR AUTO-CENTRES; aiming with the mouse fights it — it keeps putting you
back"*, filed under `P8`/STAGE 7 and never diagnosed. **That is a SECOND owner report about mouse
control, sitting unranked while five sessions went into the renderer.**

## §8 — STILL OWED, NOW NINE SESSIONS
All of `277` §9 (the two hoist sites, never driven) · `278` §6's INFERRED hoist-1 read ·
`279` §5's amount arm · `280` §7.3's black-wall dump · `274` §7's `CONTAMINATED` gate ·
**`287` ARM 6, the wear pass — STILL NEVER RUN.** **Carried forward honestly, not quietly.**

## §9 — THE `288` DEFECTS, FIXED HERE RATHER THAN HONOURED
**(a) `288` §6 defect 1** — `room` on one line with the per-prop counters — **fixed in the source**
(§0a.1: three denominators, three lines, and a sum-check that can say MISMATCH).
**(b) `288` §6 defect 2** — the plane counters multi-count — **now printed on the line itself**, with
`view` beside it as the per-prop number.
**(c) `288` §6 defect 3** — with `PROPCULLBOX` on, the planes are unreachable — **unchanged and still
true**; R1 keeps `PROPCULLBOX` at its default deliberately, so **R1's five plane zeros are expected
by construction and are not evidence**, exactly as ARM 8's were.
**(d) `288` §10(a)** — V2 changed two things at once — **honoured, not repeated**: S2 changes exactly
one line against S1, and S3 exists because S2's second variable could not be removed.
**(e) `288` §10(c)** — gate 2 mandates the menu-text fault cell — **not fixed, and deliberately so.**
It is stated in §3 as a known cost of a discriminating gate. **Moving to `1825x1369` would print
`ours: x=0` and silently break the gate** (rule `17`).
