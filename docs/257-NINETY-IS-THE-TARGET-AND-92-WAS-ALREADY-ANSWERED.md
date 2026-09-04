# 257 — NINETY IS THE TARGET. `92` WAS ALREADY ANSWERED, AND I BUILT ON IT ANYWAY.

**2026-08-29. Docs run to `257`. NEXT DOC = `258`.**

**No code was written for this document.** `228` §2's rule stands: **gates before
code.** Everything below is read from source, read from the corpus, or named as
unknown.

> # ►►►►►► **THE OWNER HAS ENTERED FOUR STANDING REQUIREMENTS. ONE OF THEM
> # REOPENS A DECISION I HAD JUST GOT WRONG IN THE OPPOSITE DIRECTION.** ◄◄◄◄◄◄
>
> **`[REPORTED]`, and this is the source of every constraint in §5:**
>
> 1. **90 Hz in the headset.**
> 2. **Adjustable field of view — different headsets, different FOV.**
> 3. **Adjustable resolution — different headsets, different panels.**
> 4. **"Incredibly optimized and run very smoothly ... every choice that we make
>    for this foundation builds on this so that we don't have to hack later on."**
>
> **These are not feature requests. They are constraints on the foundation, and
> they are entered into `00-START-HERE` as `P1`–`P5` by this document.**

---

## §1 — ►► MY RETRACTION, AND IT IS THE WHOLE REASON THIS DOCUMENT EXISTS ◄◄

I offered the owner two routes to 90 Hz and characterised them like this:

> *"**90 Hz present, 60 Hz sim + interpolation** — `92` `[MEASURED]` this already
> worked in the recomp, and `64` measured that turning the interpolator off froze
> the build harder. **The first is proven and cheap.**"*

**Every load-bearing part of that is wrong, and the corpus already said so.**

### 1.1 — `92` WAS ANSWERED FIVE DAYS BEFORE I CITED IT

`[MEASURED]` `134` §1:

| | baseline | **`-ViRate 90`** | **`+ -FloatDelta`** |
|---|---|---|---|
| fps mean | **59.2 / 59.3** | **87.1** | **89.5** |
| fps max | 61.6 / 61.1 | **91.6** | **91.6** |
| samples | 140 | 129 | 123 |

> **`134`, verbatim: *"`92`'s '90 Hz is structurally unavailable... not a
> performance limit; no amount of PC moves it' — it was a truncating divide and a
> hardcoded `60` in a file nobody had opened."***

**`92` has been superseded since 2026-08-24.** I quoted its headline as a live
finding. **`92` is marked SUPERSEDED BY `134` in the index by this document.**

### 1.2 — THE INTERPOLATOR WAS NOT THE PROVEN ROUTE. ITS DELETION WAS.

`[REPORTED]` `147`, worn 2026-08-24 19:00, RB-07:

> ***"I am so happy to say it's SO MUCH better. It's totally playable and
> enjoyable."***

`[MEASURED]` the same run: `fps mean 82.7 / max 90.0`, `interpUsed=0`,
`eye0=eye1=distinctTargets=90`, **`LATE 0/91 (ZERO per cent)`**.

And `126` RB-07 states the comparison outright:

> **"pacing is BETTER at ninety real frames than it was at sixty plus an
> interpolator (`109` measured 18% late)."**

`131` §1 states the mechanism as the feature: *"The sim itself ticks at 90. Every
frame is real; nothing is interpolated."*

### 1.3 — AND `64`'s "FROZE IT HARDER" IS A DIFFERENT MECHANISM

`64`/`57` measured **RT64's `rr_option: "Original"`** — asking the *renderer* to
stop interpolating while the sim still ran at 60, which leaves 60 real frames to
fill 90 present slots and manufactures repeats instead. **Route B removed the
need for the interpolator by making the sim produce 90 real frames.**

**Those are opposite operations and I treated them as the same one.** That is the
entire error, and it is `182`'s pattern — **the fifth instance in this project of
promoting an unverified reading to an established one** (`160`, `163`, `171` §3,
`180`, now this).

> ## **THE OWNER CAUGHT IT FROM MEMORY, AGAIN.** *"If the 90hz sim is possible
> and the better route ... maybe its possible that the cons are no longer the
> same?"* — against a document of mine that had just called the other route
> proven. **`180` records him doing exactly this once before.** `HANDOVER` §5
> holds: **wear reports and owner recollection outrank my reading.**

### 1.4 — HIS OBJECTION WAS ON THE RECORD THE WHOLE TIME

He asked whether it was noted. It is, three times:

- `96`: *"it's pointless building all this extra stuff if you're just gonna get
  sick when you're playing it."*
- `96`, logged as a **fault separate from the judder**, with an explicit warning
  that fixing the judder would not fix it: *"when I turn with the controller it
  doesn't judder, but it just feels **not ninety hertz**."*
- `180`: *"I was able to run virate 90 in VR and the characters DID NOT stutter."*

**The record was complete. The failure was that I did not read it before
answering.** `168` §5 exists for this and I did not apply it to the corpus.

---

## §2 — SO WHAT IS ACTUALLY ESTABLISHED ABOUT 90 Hz SIM

`[MEASURED]`, all from the recomp era, all worn:

| claim | evidence |
|---|---|
| the sim can tick at 90 | `134` — 59.3 → 87.1 fps mean, 129 samples |
| it is preferred by the wearer | `147` — *"SO MUCH better"* |
| pacing improves, not degrades | `126` RB-07 — `LATE 0/91` vs `109`'s 18% late |
| stereo survives it | `180`'s retraction — `-ViRate 90`, `interpUsed=0`, **both eyes** |
| the delta consumers are safe | `132` §3 — see below |

### 2.1 — THE DELTA CONSUMERS ARE NOT THE RISK. THEY WERE COUNTED.

`[MEASURED]` `132` §3 / RB-03b: **216 references to `g_GlobalTimerDelta`, eight
inside a `g_ClockTimer > 0` guard, and ALL EIGHT ARE DIVIDES — not one is an
integrator.** The other 208 are unguarded accumulations that sum correctly from a
fractional delta by construction. **`bondview2.c` is 73 of 75 unguarded.**

The eight are characterised as a **mild** fault: *"stale velocity for 11 ms on one
frame in three, not motion at two-thirds speed."*

> **This supersedes how I presented `224`'s `bondhead.c:284` counter-example.**
> `224` was right that a divide site exists; `132` had already **enumerated** them
> and found the class bounded and small. **I cited the counter-example without the
> census that scoped it.**

---

## §3 — ►► THE ONE REAL CON: `RB-04`. AND IT IS ONE FUNCTION, NOT A CLASS. ◄◄

`[MEASURED]` by the owner, stopwatch on a fixed route (`145`, `126` RB-04):

| build | fixed-route time |
|---|---|
| stock | 29.48 s (truck hesitation) |
| **RB-02** — the clock alone | **27.04 s — CORRECT** |
| **RB-03** — + the float delta | **18.18 s** |

**`27.04 / 18.18 = 1.487 = 90/60`. Bond walks exactly 1.5× too fast.**

`[READ]`, and the mechanism is named: **`bondview2.c:7152 / :7237 / :7411` —
Bond's walk is an exponential approach to a target, advanced once per FRAME, with
no timestep in the loop** (`sp240` is a collision ratio, not a time). More frames
per second → faster convergence → faster Bond.

**And the obvious suspect was excluded first:** all 44 `/ g_GlobalTimerDelta`
sites in the tree were listed and **none is Bond's walk** — they are tank, thrown
objects, casings, truck and front end. `144` §2 died there, *"the third wrong
mechanism for this symptom."*

### 3.1 — WHY IT WAS PARKED, AND WHAT ACTUALLY CHANGED

It was parked for one stated reason: fixing it means **putting a timestep inside
`MoveBond` — 1307 lines — and changing movement feel**, and `118` §4 says leave
the thing that decides feel alone. **Through a patch layer against a recompiled
binary, that is an unacceptable trade and RB-02 shipped without it.**

> **THE CON THAT CHANGED IS THIS ONE, AND ONLY THIS ONE.** The clock stopped being
> the problem at `134`. **`MoveBond` is the problem, and `MoveBond` is what the
> source port makes tractable:** the file is ours to edit directly, the change is
> reviewable as source rather than as a patch, and **the matching decomp is ground
> truth for what the original convergence curve was** — so "did we change the
> feel" becomes a diff and an A/B, not an opinion.

### 3.2 — WHAT I HAVE NOT DONE, AND IT MUST BE DONE BEFORE ANY COSTING

> **`[ASSUMED]` — I have NOT opened `MoveBond` in the native tree.** Every line
> number in §3 is **recomp-era, from `126` and `145`**, against
> `vendor/ge-decomp`. **`168` §5 is explicit: grep the tree for every symbol
> BEFORE costing anything, and `157` withdrew a whole slice for want of eight
> symbols.**
>
> **COUNTER-EXAMPLE SEARCH: not run.** The native tree's `bondview2.c` may differ
> in line numbering, in structure, or in whether `MoveBond` is even the same
> function after the port's edits. **No estimate of RB-04's cost may be made until
> §7 step 4 has been run.** This paragraph exists so the next session does not
> inherit my line numbers as though they were read.

---

## §4 — ►► THE CORRECTION: RATE-AGNOSTIC, NOT NINETY ◄◄

**The owner accepted 90 Hz sim as the target. The correction is to not build it
for 90.**

RB-02's recomp shape replaced a hardcoded `60` with a target rate. **Doing the
same thing again in the source port trades one literal for another, and
requirement 2 and 3 above make that a foundation defect:** a wearer on a 72 Hz
Quest or a 120 Hz Index is then a second port, not a config line.

| want | term |
|---|---|
| sim rate | **`60.0f / actualHz`, computed per frame from the runtime** |
| the `MoveBond` fix | **a timestep in the loop — rate-agnostic, not a 90 Hz constant** |
| game speed / slow-mo | **the same term, multiplied. One knob** (`224` §2) |

> **`239`'s rule is the argument: a knob validated at ONE value is not a setting.**
> A `MoveBond` timestep tested only at 90 is a 90 Hz hack that happens to be
> spelled as a variable. **It must be read at two rates before it is believed.**

**This costs nothing extra.** The timestep has to go into the loop either way; the
only question is whether the numerator is a literal or a query.

---

## §5 — THE STANDING PERFORMANCE CONSTRAINTS

**Entered into `00-START-HERE` by this document as `P1`–`P5`. They constrain every
later plan; they are not a section of this one.**

**P1. SIM RATE AND PRESENT RATE ARE SEPARATE TERMS, AND NEITHER IS A LITERAL.**
`ge_timing_probe.c` already states the property to preserve — *"game time is
counted in video fields, so a correct clock gives 60 a second whatever the
renderer is doing."* **Keep that separation even once the sim runs at 90.**

**P2. NEVER STORE AN FOV ANGLE. STORE FOUR TANGENTS PER EYE, PER FRAME.**
`guPerspective` cannot express an off-centre frustum, so the projection is being
replaced regardless (`255` §1). **`222` §2 `[MEASURED]` the aspect error at 30%**
— game x/y `1.000` against render `1.297` — **which is the exact fault class a
stored aspect assumption produces.** Requirement 2 and correctness are the same
code path; a symmetric-FOV build is rewritten for headset #2.

**P3. RESOLUTION IS ONE VARIABLE, SOURCED FROM THE RUNTIME.** `[READ]` the seam
exists: `ge_config.c:270` parses `WIDTHxHEIGHT`, and `ge_display_api.c:12` records
that the dimension *"is only ever assigned on `gfx_current_dimensions`, never on
`gfx_output_dimensions`."* **Preserve that. One assignment site, no constants.**

**P4. PAY STRUCTURAL COST ONCE; NEVER PAY PER-FRAME COST FOR CONVENIENCE.**
This is what decides `255` §3's A vs B on the cost axis — see §6.

**P5. NO PERFORMANCE CLAIM WITHOUT AN INSTRUMENT THAT CAN FAIL.** `49`, and §6.

---

## §6 — WHAT `P4` DOES TO THE A/B CHOICE, AND WHAT IT DOES NOT

`256` §2.2 declined to recommend A or B **on correctness** — neither delivers eye
separation, because separation lives in the view. **That is unchanged and this
document does not overturn it.**

What the owner's requirement adds is a **cost** axis, and on cost they are not
close:

- **A (game-side re-render)** doubles all game-side render work **every frame,
  forever**, and `255` §3 marks the survival of `fr.c`'s per-frame state under a
  double drive as **not established**.
- **B (renderer-side replay)** runs game logic once. Its costs — splitting
  `gfx_run` (`255` §2's second trap), and working inside the gitignored
  `gfx_pc.c` — are **one-time structural costs.**

> **`P4` therefore favours B. It does NOT decide B**, because `256` §5's **row 3**
> is still the read that says whether B can carry the eye translation at all. If it
> cannot, B alone is `B1` and the question reopens. **Cost favours B; feasibility
> is one run away and that run is already built.**

### 6.1 — AND THERE IS NO FRAME BUDGET TO SPEND

`[READ]` `port_render.c:143-156` times `gfx_start_frame` / `gfx_run` /
`gfx_end_frame` with **`SDL_GetTicks()` — millisecond resolution.** The budget at
90 Hz is **11.1 ms**. A 1 ms quantum is ~9% error per stage, and the timings are
emitted through a per-frame `printf` + `fflush` **that costs more than the thing
it measures.**

`[READ]` `gfx_sdl2.c:403,540` already uses **`SDL_GetPerformanceCounter()`** for
pacing. **The high-resolution clock is in the tree and is not on this path.**

> **`49`'s test, applied: a millisecond timer prints the same thing on a build
> that hits 11.1 ms and on one that misses it by 8%. It is not an instrument for
> this question.**
>
> **Requirement 4 is currently unmeasurable, and stereo's cost can only be
> reported as an impression.** A baseline taken **before** stereo makes stereo's
> cost a delta against a known number. **Nothing depends on it and it is the
> cheapest item in §7.**

---

## §7 — ►► THE NEXT SESSION. IN THIS ORDER. ◄◄

**Steps 1–3 are already built and staged by `256` §5. Steps 4–6 are new and step 4
needs no build at all.**

### **0. COMMIT.** `247`–`257`, the fixes, both handover docs.
**At the main PC, not through the bridge** (`48`, `148` item 11).

> ## **DOUBLE-CLICK `COMMIT-NOW.cmd` IN `Z:\Desktop\GoldenEyeVR`.**
> It picks the newest message file, dry-runs, shows every staged file, asks y/N,
> commits **both** repos, then offers `goldeneye-native` separately. Nothing is
> pushed. **Written by `257` — see §7.1 for why it had to be.**

By hand, if needed:
```powershell
cd Z:\Desktop\GoldenEyeVR
.\commit-session.ps1 -Message (Get-Content .\COMMIT-MESSAGE-2026-08-29d.txt -Raw)
```
**`getv/port/fast3d/gfx_pc.c` IS GITIGNORED** (`233` §6.1).
**`tools/fetch-thirdparty.sh regen` is part of the commit** — it regenerates
`getv/patches/thirdparty/0001-getv-port-layer.patch`, the tracked artifact.
**Without it a fresh clone loses every probe from `256`.**

### **1. RUN 1 — `GETV_SAVE_DEBUG=1`. NO BUILD. DO IT FIRST.**
```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
cd Z:\Desktop\GoldenEyeVR\goldeneye-native\getv\build-windows
$env:GETV_SAVE_DEBUG = "1"
.\goldeneye.exe *> run_save.log 2>&1
```
**Reads but no writes → `file2.c` runs and declines to write. Neither → it never
runs.** Separates `F1` from `F2` in one launch (`256` §3.1).

### **2. BUILD ONCE.**
```powershell
cd Z:\Desktop\GoldenEyeVR\goldeneye-native
& getv\build_windows.ps1 -Target all *> build.log 2>&1
```

### **3. RUNS 2 AND 3, AND THE ROW-3 READ.**
- **Run 2 — `GETV_ALIGNPTR=0`, nothing else.** Four folders selectable → `253`'s
  widening is the cause and `254` shipped a regression. Still two → excluded, at
  the cost of one launch.
- **Run 3 — `GETV_RECTPROBE=1`**, blank EEPROM, watch the gunbarrel through. Read
  the `BLANK` lines only.
- **`GETV_MTXTRACE` with `GETV_PROBE_AFTER=3000` — READ ROW 3 WHOLE.** `256` §2.1
  flagged the `V·P` fit as `[ASSUMED]` Z-only because **an X translation is
  invisible in `m22/m32/m23/m33`, and an eye offset IS an X translation.**
  **This is the read that decides A vs B on feasibility.** §6 has already decided
  it on cost.

### **4. FREE DESK WORK — NO BUILD, NO LAUNCH. `RB-04` IN THE NATIVE TREE.**
**§3.2 is the reason this is a step and not an estimate.**
```
grep -n 'MoveBond' vendor/ge-decomp/src/bondview2.c
grep -rn '/ *g_GlobalTimerDelta' vendor/ge-decomp/src/
grep -rn 'g_GlobalTimerDelta' vendor/ge-decomp/src/ | wc -l
```
Confirm in the **native** tree: the three convergence sites, the 44 divide sites,
the 216 references. **Then, and only then, cost the timestep.**
**Deliverable: a doc that either confirms `126`'s reading or corrects it.**

### **5. THE FRAME-BUDGET INSTRUMENT.** §6.1.
`SDL_GetPerformanceCounter()` on `port_render.c`'s three stages; accumulate and
emit **once per N frames**, not per frame; gate it on `GETV_PROBE_AFTER` so it can
be pointed at gameplay (`256` §1's lesson, and it is the second instance).
**Gate, per rule 2: what does it print on a build that misses the budget?**
If min/max/mean over a window do not separate 11.1 ms from 12.0 ms, it is not the
instrument.

### **6. THE BASELINE CAPTURE. BEFORE ANY STEREO CODE.**
One run, gameplay, current build. **The number that every later change is a delta
against.** `239`: take it at more than one resolution, or it is not a baseline for
requirement 3.

---

## §7.1 — ►► THE COMMIT PROCEDURE WAS WRONG IN THE HANDOVER, AND THE REPO
## LAYOUT WAS WRONG IN `00-START-HERE`. BOTH FIXED HERE. ◄◄

**`[READ]` `commit-session.ps1:37-42`. Its only parameters are `-Message`
(mandatory string) and `-DryRun`.**

> **THE `2026-08-29c` BANNER SAID `.\commit-session.ps1 -MessageFile
> .\COMMIT-MESSAGE-....txt`. `-MessageFile` DOES NOT EXIST. That call fails.**
> **It was copied forward into the `29d` banner before anyone opened the
> script** — a fourth-hand instruction that had never been executed as written.

**`[MEASURED]` on the bridge, and it corrects the old "two repositories"
section, which named the wrong two:**

| | verified |
|---|---|
| `GoldenEyeVR\repo\` | **NO `.git`.** A plain subfolder. **All docs commit with `GoldenEyeVR`** |
| `GoldenEyeVR` | **IS** the repo. No remote. Local only |
| `GoldenEyeVR\goldeneye-native\` | **its own repo** (`SegfaultEvan/goldeneye-native`, `main`), **gitignored by the parent at `.gitignore:46`** — `commit-session.ps1` does **not** touch it |
| `GoldenEye64Recomp` | the second repo. origin is cblock85's, not the owner's |

### 7.1.0 — AND THE HARDCODED DRIVE LETTER WOULD HAVE COMMITTED NOTHING

`[REPORTED]` the owner, on reading the corrected command: *"right now its
Z:\Desktop for both folders."*

`[READ]` `commit-session.ps1` had **both repo paths hardcoded to
`C:\Users\<USER>\Desktop\...`**. Its own loop prints `NOT FOUND` and `continue`s
on a missing path — **so on the `Z:` form it would have reported cleanly and
committed NOTHING, in both repos, with a zero exit.** `49`'s shape in a script
rather than an instrument: **a failure that prints something reasonable.**

> **The first `commit-now.ps1` I wrote was worse — it hard-guarded on
> `Test-Path 'C:\Users\<USER>\Desktop\GoldenEyeVR'` and would have refused to run
> outright.** I wrote a location check into a wrapper whose entire purpose was
> removing a procedural trap, and put a second one in.

**BOTH SCRIPTS NOW RESOLVE FROM `$PSScriptRoot`:** `GoldenEyeVR` is the script's
own directory, `GoldenEye64Recomp` is its sibling, with the two known desktops
as a named fallback. **`commit-now.ps1` tests for `.git` and for Windows —
properties that matter — never for a drive letter.**

**Both path forms reach the same folders and older documents use the `C:` form.
They are not wrong; they are not to be copied into new scripts.**

**The old section named `GoldenEye64Recomp` and `goldeneye-native` as "the two
repositories" and pointed `goldeneye-native` at `no6969el` in `local-only\`.**
That is a third, historical checkout. **The two the commit script actually
commits are `GoldenEyeVR` and `GoldenEye64Recomp`.**

### 7.1.3 — ►► `Z:` IS A NAS, AND GIT REFUSES BOTH REPOS UNTIL TOLD OTHERWISE ◄◄

`[REPORTED]` the first real run of the corrected command, both repos:

```
fatal: detected dubious ownership in repository at
  '//NAS/Double 6TB/User folder Data/Desktop/GoldenEyeVR'
  git add FAILED
```

**`Z:\Desktop` is a MAPPED NETWORK DRIVE to `\\NAS\Double 6TB\User folder
Data\Desktop`.** Git resolves the mapping to the UNC path, finds an owner that
is not the local Windows user, and refuses — **git's CVE-2022-24765 mitigation,
working as designed.** `git add` fails, so **nothing is staged and nothing is
committed, in either repo.**

**THE ONE-TIME FIX, and it is per-repo:**

```powershell
git config --global --add safe.directory '%(prefix)///NAS/Double 6TB/User folder Data/Desktop/GoldenEyeVR'
git config --global --add safe.directory '%(prefix)///NAS/Double 6TB/User folder Data/Desktop/GoldenEye64Recomp'
```

`goldeneye-native` will need the same when it is first committed, and
`GoldenEye64Recomp`'s `lib/ge` submodule may too. **`commit-now.ps1` now
pre-flights all three**: it runs `git rev-parse --is-inside-work-tree` in each,
derives the `%(prefix)/` form from `(Get-PSDrive Z).DisplayRoot`, prints the
exact commands and offers to add them. **Adding them is a change to the global
git config, so it asks — it never does it silently.**

> **`git config --global --add safe.directory '*'` also works and is tempting
> with a submodule in play. It disables the check everywhere, for every
> repository on the machine, forever. Prefer the three explicit entries.**

### 7.1.4 — THE SCRIPT REPORTED THE FAILURE HONESTLY AND STILL READ AS SUCCESS

**Worth keeping, because the error handling was not the problem.**
`commit-session.ps1` checked `$LASTEXITCODE`, printed `git add FAILED`, and
`continue`d — correct behaviour. **But it then printed its normal closing
paragraph** (*"Both repos are LOCAL ONLY..."*), so the run **ends on a
reassuring block of text with the two failures scrolled off above it.**

> **`49` again, and this is its third appearance in one session: a failure that
> terminates in the same shape as a success.** The fix is not louder text — it
> is the pre-flight, which refuses to reach the failure at all.

### 7.1.1 — AND `git status` TIMES OUT ON THE BRIDGE

`[MEASURED]` twice on 2026-08-29, both at the 120 s cap, in both repos. The
script's own comment gives the cause: recursing `GoldenEye64Recomp`'s `lib/ge`
submodule exceeds the bridge's 45-second limit. **`--ignore-submodules=all`, or
read git state at the main PC. It is not a hang.**

### 7.1.2 — `COMMIT-NOW.cmd`, AND WHY A WRAPPER RATHER THAN A CORRECTED LINE

`[REPORTED]` the owner: *"So I can just right click that and run it each time.
It does both."* **Right-click → Run with PowerShell does not work on
`commit-session.ps1`:** `-Message` is mandatory, so Explorer opens an
interactive `Message:` prompt, and a multi-line commit body cannot be pasted
into it. **The instruction was not merely mistyped; the shape of it was wrong.**

**`COMMIT-NOW.cmd` + `commit-now.ps1` are on disk.** Double-click the `.cmd`.
It refuses to run anywhere but the main PC (`48`), finds the newest
`COMMIT-MESSAGE-*.txt`, **dry-runs and prints every file it would stage**, asks
`y/N`, commits both repos, then offers `goldeneye-native` separately if that
repo is dirty and a `-native` message exists — with a reminder that
`fetch-thirdparty.sh regen` must precede it. **Nothing is ever pushed.**

> **`P5`'s shape applied to a procedure rather than a measurement: an
> instruction nobody has executed as written is not a procedure.** Three
> sessions carried `-MessageFile` forward. **The wrapper removes the failure
> mode instead of documenting it more loudly.**

---

## §8 — WHAT IS NOT CLAIMED

- **No architecture recommendation.** §6 moves the **cost** axis to B and leaves
  the **feasibility** axis exactly where `256` §2.2 left it: on row 3.
- **`[ASSUMED]` every `RB-04` line number in §3.** Recomp-era, unverified against
  the native tree. **§7 step 4 exists because of this and no cost may precede it.**
- **No claim that the `MoveBond` fix is cheap.** `118` §4's caution about touching
  movement feel is undiminished; what changed is that it is now a **design
  decision with a ground truth to diff against**, not a structural block.
- **No claim that 90 Hz sim in the NATIVE port will reproduce `134`'s numbers.**
  `134` measured the recomp, on RT64. **The native port has never been run above
  60 and has no frame-budget instrument** (§6.1). The mechanism is proven; the
  numbers are not transferable.
- **`[INFERRED]` that `P2`'s tangent form fixes `222` §2's 30% aspect.** They are
  the same fault class; that they are the same fault is not measured.
- **Nothing in §7 has been run.**
