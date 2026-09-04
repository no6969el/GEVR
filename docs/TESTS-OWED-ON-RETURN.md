# TESTS OWED WHEN YOU ARE BACK AT THE RIG

> # ►►►► 2026-08-26 — THIS FILE IS HISTORY. DO NOT WORK FROM IT. ◄◄◄◄
>
> ## **THE LIVE LIST IS `MAIN-STATION-TASKS.md`.** Everything still owed was
> ## audited out of here and moved there as `T12`, `T13`, B3/B4 and the commit.
>
> **AUDITED 2026-08-26 AGAINST THE CORPUS. WHAT CLOSED, AND WHERE:**
>
> | item | verdict |
> |---|---|
> | **TEST -1** RB-02 / RB-03 | **CLOSED** — `143` (Route B works), `144` |
> | **TEST 0** the timebase instrument | **CLOSED** — `119` ran; `143` |
> | **TEST 1** the phase fix / `dupSrc` | **CLOSED** — `147`, RB-07 passed WORN |
> | **TEST 2** the A/B control | **MOOT** — TEST 1 was not ambiguous |
> | **TEST 3** `ds_option 2` | **STILL OWED** -> `MAIN-STATION-TASKS.md` `T12` |
> | **TEST 4** `muzzleExt` | ►► **DEAD, NOT OWED.** It DID print — `6D-02` measured it `100` flat — and **`171` §2 falsified U-14**: `gunfire.c:754` scales the muzzle-flash SPRITE's Z basis row and never touches position. `169` U-14 exists so it is not re-proposed. **Do not run this.** ◄◄ |
> | **TEST 5** O97 intermittent LATE | **ALL BUT CLOSED** — `147` reads `LATE 0/91`, from `16/91`. Downgraded to a confirming read: `T13` |
> | **B3 / B4** | **STILL BLOCKING, AND WORSE** — B4 re-run 08-24 with `149` compiled in, the X **still** bugchecks, no `shutdown:` line at all. `149` is insufficient, not refuted |
> | **THE COMMIT** | **STILL OWED.** Neither repo has a remote of ours |
>
> **THE STANDING RULES AT THE TOP OF THIS FILE REMAIN TRUE** — headset on before
> launch, `taskkill` never the X, copy `gevr.log` after every run, and `build.ps1`
> must report the build it chose (`115`).


**Written 2026-08-24 as the owner went remote. Everything below needs the
machine; nothing below needs to be figured out first.**

**Ordered so the first launch is the most valuable one. If you only do ONE
thing, do TEST 1.**

---

## FIRST, EVERY TIME

```powershell
cd C:\Users\pdbar\Desktop\GoldenEye64Recomp
.\build.ps1
```

**`build.ps1` now tells you which build it chose.** Headers changed since the
last full build -> it builds ALL targets and says so. **If it says "short
build" after I have edited a header, something is wrong with the stamp — tell
me.** `115` is why this exists: a stale object file cost an hour and looked
like both a performance regression and a gameplay bug at once.

**And always:** headset on **before** F9. `taskkill /F /IM GoldenRecomp.exe`,
**never the X** (B3, costs a reboot). Copy `gevr.log` after every run — it is
rewritten on every launch.

---

> # ►►►► SUPERSEDED — 2026-08-24, END OF SESSION. THE LIST BELOW IS DONE. ◄◄◄◄
>
> **Route B was built, run and validated at `-NoXr` in this session.** RB-02
> works (`143`), RB-03 is parked (`145`). **Everything below is history except
> the standing rules at the top of this file.**
>
> > ## **THE ONE TEST NOW OWED IS RB-07 — THE HEADSET. `146` IS THE PLAN.**
> >
> > ```powershell
> > .\vr.ps1 -UnitsPerMetre 50 -SeamNoRot -HandPosZ 1 -ViRate 90
> > ```
> >
> > **DO NOT REBUILD FIRST** (`146` §1). **Pin `ds_option` and re-check
> > `graphics.json` after any menu visit** (`108` §4). **Close with
> > `taskkill /F /IM GoldenRecomp.exe` — never the X. B3 costs a reboot.**
> >
> > **READ THE LOG FIRST:** fps ~90 (`146` §3 — RB-02 buys 50% more real
> > rendering at 26 Mpx an eye), `dupSrc` ~0/90 (**30/90 in every prior build**),
> > `LATE`, and `per1000ms=60`. **Only then judge the head turn.**
>
> ---
>
> ### ►► 2026-08-24 17:09 — THE FIRST ATTEMPT RAN A STALE BINARY. `133`. ◄◄
>
> **Both launches happened and both were judged "working". Neither contained
> RB-02 or RB-03.** `GoldenRecomp.exe` was stamped **15:37**, `patches.elf` and
> `RecompiledPatches\patches.c` **14:09**, and the source edits **17:02-17:03**.
> **`build.ps1` was never run, or did not complete.**
>
> **AND THE LOG SAID SO, WHICH IS THE WHOLE POINT OF HAVING GATES:**
> `61.1 fps`, `timebase: delta=1 [1..1] | clk=1 [1..1] | gdelta x1000=1000`.
> **G-131-1 and G-132-1 both FAILED.** A knob that is not in the binary produces
> a perfectly normal-looking game — **`111`'s lesson exactly: a run that looks
> fine is not a run that passed.**
>
> **SO: BUILD FIRST, AND READ THE TWO LINES BELOW BEFORE JUDGING ANYTHING.**
>
> ### AND KEEP IT — IT IS A CLEAN BASELINE, AND G-131-5 NOW HAS NUMBERS
>
> **Two unmodified `-NoXr` sessions, recorded minutes before the change, on the
> machine as it stands.** Nothing in this project had that for the timebase.
>
> | | `gevr-0824-170823-run.log` | `gevr.log` (17:09) |
> |---|---|---|
> | fps samples | 64 | 76 |
> | **fps mean / max** | **59.2 / 61.6** | **59.3 / 61.1** |
> | fps min | 20.2 (first sample, load) | 17.0 (first sample, load) |
> | **`timebase`** | **`delta=1 [1..1] clk=1 [1..1] gdelta x1000=1000 [1000..1000]`** | identical |
>
> **THAT IS THE IDENTITY TARGET.** G-131-5 says an unset launch must be
> indistinguishable from today — **"today" is now these two rows**, not a memory.
> And the two logs agreeing to a tenth across 140 samples is itself worth
> having: **the fps figure is stable enough that a real change will be obvious.**
>
> **DO NOT DELETE THESE TWO LOGS.** `vr.ps1` archives on launch, so
> `gevr.log` will be overwritten by the next run; the 17:09 one is the copy at
> risk. **Rename it now if you want it kept beyond the next launch.**

---

## ►►►► TEST -1 — ROUTE B, RB-02. NO HEADSET. THIS ONE FIRST NOW. `131` ◄◄◄◄

```powershell
.\vr.ps1 -NoXr -ViRate 90
```

**The sim itself ticks at 90. Every frame is real; nothing is interpolated.**
This is what `118`'s de-risker was for — **no headset, no B3 reboot risk, no
wearer time.**

**`build.ps1` MUST report a FULL rebuild** — `ultramodern.hpp`, `misc_funcs.h`
and `syms.ld` all changed.

> **G-131-1, THE GATE: `sgf=` on the `[trace] retrace` line must STOP reading a
> flat 1.** At 90 it should be a mix of 0 and 1 averaging two thirds. **Flat 1
> means the accumulator is not running and nothing else in the run counts.**
> `119`'s `delta=1 [1..1]` line is the better instrument if it still prints.

**G-131-2:** fps ~90, not 60.
**G-131-3 — LISTEN.** `130`: correct pitch and tempo, **no hashing, no
crackle.** Wrong pitch = the audio divisor and the VI rate disagree.
**G-131-4:** a level plays; an in-game countdown matches a real stopwatch (RB-05).
**G-131-5:** a launch with **no** `-ViRate` must be indistinguishable from today.

**EXPECTED AND NOT A FAILURE** (`131` §6): music fades and screen shakes run
1.5x fast. **And motion will still STEP — that is RB-03 and it is the second
launch below, not a failure of this one.**

### THEN, OUT OF THE SAME BUILD — RB-03. `132`

```powershell
.\vr.ps1 -NoXr -ViRate 90 -FloatDelta
```

**`g_GlobalTimerDelta` stops being integer 60ths. This is the half that decides
whether Route B was worth doing** — 217 references, 75 in `bondview2.c`, the
VIEW.

**Run it SECOND, not instead.** If the gates above failed, nothing here means
anything.

> **G-132-1, THE GATE: `gdelta x1000` must read ~667 STEADY.**
> **`1000` = RB-03 is not running. Alternating 0/1000 = the knob fired but the
> value is still the integer.**

**G-132-2:** the level clock still keeps real time — stopwatch vs countdown.
**G-132-3: PAUSE IT.** Open the watch. **The world must stop DEAD.** `132` §2.2:
under RB-02, `g_ClockTimer == 0` no longer means paused, so the pause test had to
be re-asked directly. If the world creeps, that is what is wrong.
**G-132-4 — THE ONE THAT MATTERS: does the world look smooth now?** The first
gate in the whole Route B line that can answer *better* rather than *not broken*,
and the monitor can answer it for stick turn and world motion.
**G-132-5:** `-ViRate 90` without `-FloatDelta` still behaves as it did above.

**KNOWN, not a failure** (`132` §3): eight velocity divides go stale one frame in
three. Watch the gun's inertia and the tank turret. RB-04, and only if visible.

**STILL NOT ANSWERED BY EITHER LAUNCH: THE HEAD TURN.** That is RB-07 and it
needs the headset.

---

## TEST 0 — THE TIMEBASE INSTRUMENT. NO HEADSET. `119`

**It needs no VR, no Pimax, no B3 reboot risk — and it can invalidate `118`'s
whole Route B argument before a line of it is built.**

```powershell
cd C:\Users\pdbar\Desktop\GoldenEye64Recomp
.\build.ps1
.\vr.ps1 -NoXr
```

**Play ~20 s IN A LEVEL** (the numbers are only meaningful once the game is
ticking), then:

```powershell
taskkill /F /IM GoldenRecomp.exe
copy gevr.log gevr-keep-T0-timebase.log
Select-String -Path gevr-keep-T0-timebase.log -Pattern 'timebase:' | Select-Object -Last 8
```

**Expect:**

```
[gevr] timebase: delta=1 [1..1] | clk=1 [1..1] | gdelta x1000=1000 [1000..1000]
```

| Gate | Meaning |
|---|---|
| **G-119-1** | **All three FLAT, min == max.** **NOT flat -> the game already gets a variable delta and `118`'s model is WRONG** |
| **G-119-2** | **`gdelta == clk * 1000` always.** Not equal -> `g_GlobalTimerDelta` is not a plain cast and `118` §2 is wrong |
| **G-119-3** | **The line appears at all.** Nothing -> the patch print path is dead again (`100` fixed it once; rule 4 says verify, not assume) |

**`build.ps1` will say "HEADER CHANGED - building ALL targets" this time** —
`patches/externs.h` gained `g_GlobalTimerDelta`. **That is correct and expected;
`115` is why.**

---

## TEST 0 — THE TIMEBASE INSTRUMENT. NO HEADSET. NO VR. DO THIS ONE FIRST.

**`119` / T1-S0. It can invalidate all of `118` before a line of Route B is
built, and it costs one desktop launch with the Pimax still in its case.**

```powershell
.\vr.ps1 -NoXr
```

**Play ~30 s, then close it and read:**

```powershell
copy gevr.log gevr-keep-T0-timebase.log
Select-String -Path gevr-keep-T0-timebase.log -Pattern 'timebase:' | Select-Object -Last 6
```

**The line reads:**
`[gevr] timebase: delta=N [min..max] | clk=N [min..max] | gdelta x1000=N [min..max]`

| **G-119-1 — PREDICTION** | |
|---|---|
| `delta` | **1, flat. min == max** |
| `clk` | **1, flat. min == max** |
| `gdelta x1000` | **1000, flat. min == max** |

**IF THEY ARE NOT FLAT** — the game is already receiving a variable delta, and
**`118`'s model of a rigid 60 Hz tick is WRONG.** Everything in `118` §3 would
need re-deriving before any of it is built.

**IF `gdelta` IS EVER != `clk` x 1000** — `g_GlobalTimerDelta` is not simply a
cast of `g_ClockTimer`, and **`118` §2's two-line choke point is wrong.**

**IT IS NOT GATED ON VR** and prints on every launch, so **it also rides along
on Tests 1 and 2 for free** — you do not need a separate run if you would rather
batch it. It is listed first because it is the cheapest thing here and the only
one that can kill a whole planned workstream.

---

## TEST 1 — THE PHASE FIX. THE ONE THAT MATTERS. `116`

```powershell
.\vr.ps1 -UnitsPerMetre 50 -SeamNoRot -HandPosZ 1 -EyeSetPhase -EyePickLog
```

**~30 s, and STICK-TURN several times while wearing it.**

```powershell
taskkill /F /IM GoldenRecomp.exe
copy gevr.log gevr-keep-T1-setphase.log
Select-String -Path gevr-keep-T1-setphase.log -Pattern 'pick trace|posecheck:|render passes:|stage MAX ms:' | Select-Object -Last 8
```

| Gate | Expect |
|---|---|
| **G-116-1** | **`dupSrc` ~0/90**, down from 30/90. **THE GATE** |
| **G-116-2** | fps 60, submits 90 |
| **G-116-3** | The trace stops repeating — no two identical entries in a row |
| **G-116-4** | **DOES THE STICK TURN LOOK SMOOTH?** The only gate a log cannot answer |

**ALSO WATCH FOR THE CHARACTER MISPLACEMENT** of `105`/`115`. If `dupSrc` falls
but characters go wrong, the fix is reading the wrong slot and that is a
different failure wearing a success's numbers — `116` §4.

**If G-116-1 and G-116-4 both pass, the duplicate-frame judder is CLOSED** after
fifteen documents, and the head-turn half becomes the whole remaining problem.

---

## TEST 2 — THE A/B, IF TEST 1 IS AMBIGUOUS

```powershell
.\vr.ps1 -UnitsPerMetre 50 -SeamNoRot -HandPosZ 1 -EyeInterp -EyePickLog
taskkill /F /IM GoldenRecomp.exe
copy gevr.log gevr-keep-T2-oldphase.log
```

**Same build, old path.** `dupSrc` should read ~30/90 and the trace should show
`1:0:xxxx 1:0:xxxx 0:1:yyyy`. **This is the control, and it costs one launch.**

---

## TEST 3 — `ds_option 2` AS THE DEFAULT. FREE WIN, ALREADY MEASURED. `111` §4

**Already confirmed: 60 fps, 90 eye passes, LATE 12% (BETTER than baseline's
17%), and it kills the distant shimmer (`108` §3).**

**What is owed is only the decision and one confirming run.** If you want the
curve: try `ds_option 4` and read the fps line. **If 4 is SLOWER than 2, that is
`49`'s O22 reproducing on demand, which nobody has ever pinned down** — that
would be worth more than the AA result itself.

```powershell
$g = "$env:LOCALAPPDATA\GoldenRecomp\graphics.json"
(Get-Content $g -Raw) -replace '"ds_option"\s*:\s*\d+', '"ds_option": 4' | Set-Content $g
```

**`msaa_option` stays `"None"`. Not negotiable — `43`.** And the in-game
graphics menu rewrites this file, so re-check after any menu visit.

---

## TEST 4 — `muzzleExt`. ONE IN-LEVEL LAUNCH. OUTSTANDING SINCE `91`

**The last unread S0 falsifier. `A40` came back `-1000` and confirmed;
`muzzleExt` has never printed** — its line is the only one of five that emits
empty, and the only one touching `get_ptr_item_statistics`. **`100` says move
that read to its own line, LAST.**

**It batches with any in-level launch above. It does not need its own run.**

| | |
|---|---|
| **PREDICTION** | `muzzleExt > 0` |
| **If it fails** | `88` §5.1's aim-axis reasoning inverts and **slices G2 and A1 both change shape** |

---

## TEST 5 — THE INTERMITTENT LATE FRAMES. O97, NO HEADSET NEEDED

**`109` found ~1 frame in 6 missing the 11.11 ms deadline on the build you
actually play — and INTERMITTENTLY: other samples in the same run read
`LATE 0/60`.** Something periodic costs a deadline several times a second and
nobody knows what.

**Just run any build for 60+ seconds and keep the log.** The `stage MAX ms:`
line already reports it; it needs a longer window, not new code.

---

## NOT A TEST, BUT IT IS OWED — COMMIT BOTH REPOS

**Now failed five sessions.** Today added **eight source files** and **ten
documents**.

```powershell
cd C:\Users\pdbar\Desktop\GoldenEye64Recomp
Get-ChildItem .git -Recurse -Filter *.lock | Remove-Item -Force
cd C:\Users\pdbar\Desktop\GoldenEyeVR
Get-ChildItem .git -Recurse -Filter *.lock | Remove-Item -Force
.\commit-session.ps1 -Message (Get-Content C:\Users\pdbar\Desktop\GoldenEyeVR\COMMIT-MESSAGE-2026-08-24.txt -Raw)
```

**`-Message` IS NOW MANDATORY — `120` §1.** The old script staged a hardcoded
file list from the `86`-`96` era and committed under a hardcoded message; three
existing commits already carry the identical subject line. **A ready-to-use
message for today's work is written out at
`GoldenEyeVR\COMMIT-MESSAGE-2026-08-24.txt`** — the command above reads it
straight in. Add `-DryRun` to stage and list without committing.

**It clears locks itself and refuses to run while a `git` process is live**, so
the two `Get-ChildItem ... *.lock` lines above are now belt-and-braces rather
than required.

**On Windows, not through the bridge** — `48`, and `115` is a reminder of what
stale state costs. **`git status` on `GoldenEye64Recomp` times out because it
recurses submodules; use `--ignore-submodules=all` if you need it.**

**Neither repo has a remote of ours. Five sessions of work exist on one disk.**

---

## AND THE TWO THAT ARE STILL MARKED BLOCKING AND STILL UNTOUCHED

**B3** — the machine bugchecks when a VR session closes, `0x139` arg1=3, five
times, never under `-NoXr`. **Costs a reboot per test.**
**B4** — a tester will close with the X, and the force-kill is a workaround for
people who know about it, not a shippable exit.

**`39` has had both marked BLOCKING since `75`. Nothing this week touched
either, and that is a decision being made by default rather than deliberately.**
