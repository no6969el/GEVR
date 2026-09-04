# RUN SHEET — `260`. THE CLOCK AND THE FREE READS.

**Every path, script name and environment variable below was grepped out of the
tree on 2026-08-29h before this sheet was written.** `GETV_ALIGNPTR` is at
`front.c:8525`, `GETV_REALCLOCK` at `port_os.c:214`, `GETV_PADS`/`GETV_PAD_SYNTH`
at `port_input.c:423`/`436`, `GETV_FPS`/`GETV_VSYNC` at `gfx_sdl2.c:374`/`396`,
`GETV_CLOCKTRACE` at `frametiming.c`, `GETV_MOVETRACE` at `bondview2.c:7882`.
**Nothing here is copied forward from a previous banner.**

## THE TWO RULES FOR THIS SHEET
1. **`Remove-Item Env:GETV_* -ErrorAction SilentlyContinue` BEFORE EVERY RUN.**
   PowerShell `$env:` persists for the life of the window. Three variables
   accumulated silently once already.
2. **RUNS 1-4 NEED NO BUILD. DO NOT BUILD UNTIL STEP B.** The current
   `goldeneye.exe` is from 2026-08-29 04:36 and answers all four.

---

# STEP A — COMMIT. FIRST. BEFORE ANYTHING ELSE.

**At the main PC, not the bridge.** Double-click, in `Z:\Desktop\GoldenEyeVR`:

```
COMMIT-NOW.cmd
```

It dry-runs, lists every staged file, asks y/N, commits both repos, then offers
`goldeneye-native` separately. **Nothing is pushed.**

**IF IT SAYS `fatal: detected dubious ownership`** — `Z:` is a NAS and git
refuses it. The script pre-flights this and offers to add the exceptions; say
yes. **Read the output ABOVE the closing paragraph: it has ended on a reassuring
summary with two failures scrolled off above it before.**

**New this session and untracked:** `repo\docs\258-*.md`, `repo\docs\259-*.md`,
`repo\docs\RUN-SHEET-260.md`, `repo\docs\00-START-HERE.md` (P6-P9),
`repo\docs\HANDOVER.md`.

---

# THE NO-BUILD RUNS. FOUR LAUNCHES, CURRENT EXE.

```powershell
cd Z:\Desktop\GoldenEyeVR\goldeneye-native\getv\build-windows
```

---

## ► RUN 1 — THE CLOCK. **THIS IS THE ONE THAT MATTERS.** (`259`)

**Question: is `RB-04` just the synthetic clock?** `259` says the walk is already
delta-scaled and the 1.487x is the default clock counting every rendered frame as
one 60 Hz field. **`GETV_REALCLOCK=1` is the switch that already exists.**

### 1a — the control, at 60. Establish the stopwatch baseline again.
```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
cd Z:\Desktop\GoldenEyeVR\goldeneye-native\getv\build-windows
$env:GETV_CLOCKTRACE = "1"
$env:GETV_FPS        = "60"
.\goldeneye.exe *> run_clock_60.log 2>&1
```

### 1b — 90 Hz, synthetic clock. **THE BROKEN CASE. Expect ~1.5x too fast.**
```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
$env:GETV_CLOCKTRACE = "1"
$env:GETV_FPS        = "90"
$env:GETV_VSYNC      = "0"
.\goldeneye.exe *> run_clock_90_synth.log 2>&1
```

### 1c — 90 Hz, REAL clock. **THE CANDIDATE FIX.**
```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
$env:GETV_CLOCKTRACE = "1"
$env:GETV_REALCLOCK  = "1"
$env:GETV_FPS        = "90"
$env:GETV_VSYNC      = "0"
.\goldeneye.exe *> run_clock_90_real.log 2>&1
```

### WHAT TO DO IN ALL THREE
**Walk your `RB-02`/`RB-03` fixed route and time it with the stopwatch.**
Same start point, same end point, same weapon, no shooting. **Write the three
times down.** Baseline for comparison: stock `29.48s`, RB-02 `27.04s`,
RB-03 `18.18s`.

### ►►► VERIFY THE INSTRUMENT FIRST — RULE 4 ◄◄◄
**Before believing any of the three, check the log has these lines:**
- `[getv] pace: 90 fps cap on (GETV_FPS), vsync=0` — **if it says 60, your
  display capped it and RUNS 1b/1c ARE VOID.**
- `[getv] clock: ... timebase (GETV_REALCLOCK=...)` — must read synthetic in 1b
  and real in 1c. **If 1b and 1c print the same thing, the switch did not take
  and both are VOID.**
- In 1b only, expect the upstream warning: *"the game will run at 90/60 = 1.50x
  speed."*

### THE PREDICTIONS, WRITTEN BEFORE THE RUN (`70`'s shape)
- **1b ≈ 18-20s** — the 1.5x, matching RB-03.
- **1c ≈ 27-30s** — correct speed, matching RB-02 and stock.
- **If 1c comes back CORRECT ON SPEED but feels uneven / not-ninety, that is
  `259` §4's quantisation and it is the expected residual, not a failure.**
- **If 1c is also ~18s, `259` §3 is WRONG.** Say so; it is one grep to redo.

---

## ► RUN 2 — SPLIT-SCREEN. THE MULTI-VIEW EXISTENCE PROOF. (`258` §1)

**Question: does this port render two views, two projections, one swap?** If yes,
the stereo mechanism is proven before a line is written.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
$env:GETV_PADS = "2"
.\goldeneye.exe *> run_2p.log 2>&1
```

**Go to the multiplayer menu, start any 2-player match on any arena, and look at
both halves.** Second pad optional — `GETV_PADS=2` forces port 1 to report
connected so the menu will let you start.

**REPORT:** do both halves draw? Is either half black, duplicated, or showing the
other player's view? Does the split line sit correctly? **A duplicated half is
`B1`'s shape and would be the single most useful thing this run could find.**

---

## ► RUN 3 — FOUR PADS. (`258` §2)

**Question: are the four N64 ports independently addressable?** This decides
whether local play is 2 or 4.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
$env:GETV_PADS      = "4"
$env:GETV_PAD_SYNTH = "1"
.\goldeneye.exe *> run_4pad.log 2>&1
```

Start a 4-player match, let it run ~20 seconds, quit. **The synthetic pads give
each port a different phase, so four players should move DIFFERENTLY.**
**FOUR IDENTICAL PLAYERS MEANS THE PLUMBING RUNS BUT THE PORTS ARE NOT
INDEPENDENT** — that is the failure this test exists to catch.

---

## ► RUN 4 — THE SAVE SPLIT. (`257` §7 step 1, still owed)

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
$env:GETV_SAVE_DEBUG = "1"
.\goldeneye.exe *> run_save.log 2>&1
```

Boot, go to the folder screen, back out, quit normally with **X** (X is the clean
exit in this port; `taskkill` would lose the 64 KB stdout buffer).
**Reads but no writes → `F2` is real and `file2.c` declines to write.
Neither → it never runs at all.**

---

# STEP B — BUILD ONCE. ONLY AFTER RUNS 1-4.

```powershell
cd Z:\Desktop\GoldenEyeVR\goldeneye-native
& getv\build_windows.ps1 -Target all *> build.log 2>&1
```

## ► RUN 5 — `GETV_ALIGNPTR=0` (the folder fault, `front.c:8525`)
```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
cd getv\build-windows
$env:GETV_ALIGNPTR = "0"
.\goldeneye.exe *> run_alignptr.log 2>&1
```
**All four folders selectable → `253`'s widening is the cause. Still two → it is
excluded, for the cost of one launch.**

## ► RUN 6 — `GETV_RECTPROBE=1` (the intro scanline wipe)
```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
$env:GETV_RECTPROBE = "1"
.\goldeneye.exe *> run_rectprobe.log 2>&1
```
Blank EEPROM, watch the gunbarrel through. **Read the `BLANK` lines only.**

---

# WHAT TO SEND BACK

The logs land in `goldeneye-native\getv\build-windows\`. **I can read them
directly off the share — just tell me which runs you did.** Plus, in your own
words:

1. **The three stopwatch times from Run 1**, and whether 1c *felt* like ninety.
2. **Run 2:** both halves drawing, or not.
3. **Run 3:** four players moving differently, or identically.
4. Anything that crashed, and at what point.

**If a run contradicts a prediction above, that is the run that was worth doing.
Say so plainly — `HANDOVER` §5: your corrections have outranked my analysis every
time they conflicted.**
