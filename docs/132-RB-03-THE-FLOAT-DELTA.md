# 132 — RB-03. THE FLOAT DELTA, AND RB-04 MEASURED INSTEAD OF FEARED.

**2026-08-24. Written, not compiled, not run.** `126` RB-03, built on top of
`131`'s RB-02 **and separately knobbed from it on purpose.**

> ## **`.\vr.ps1 -NoXr -ViRate 90 -FloatDelta`**
>
> **RB-02 MADE THE FRAMES REAL. THIS IS WHAT MAKES THE MOTION IN THEM SMOOTH,
> AND IT IS THE HALF THAT DECIDES WHETHER ROUTE B WAS WORTH DOING.**

---

## §1 — THE OWNER'S CALL, AND WHY IT WAS RIGHT AND ALSO HALF WRONG

*"I won't see the benefits of anything if I test, so I think we should just
continue on."*

**Right about the BENEFIT.** `131` §7 said it plainly: with `g_GlobalTimerDelta`
still integer, motion moves in whole-sixtieth steps on a 90 Hz sim. **A wear test
of RB-02 alone could only have answered "is it broken", never "is it better."**

**Wrong about the BUILD, and this is the part worth keeping.** G-131-1, -3 and
-5 are **correctness** gates, not benefit gates: does the accumulator run, is the
audio right, is the unset build unchanged. **Those are the foundation RB-03 now
sits on**, and `107` is the standing lesson about building three documents on an
unverified one.

> **SO THE ANSWER IS: SKIP THE SEPARATE TRIP, NOT THE GATES.** One build, two
> launches. `-ViRate 90` reads RB-02's correctness gates; add `-FloatDelta` and
> read RB-03's. **Fusing the two knobs would mean a failure could not say which
> half caused it** — `106` §2's criticism of this project, and `110` was built
> precisely to stop changing two things at once.

---

## §2 — THE CHANGE

**`lv.c:979`, inside `lvlManageMpGame`, is the whole of RB-03:**

```c
g_GlobalTimerDelta = (f32) g_ClockTimer;      /* INTEGER 60ths -> 0, 1, 1 at 90 */
```

**217 references — more than the integer's 152 — and `bondview2.c`, THE VIEW, is
75 of them.**

It becomes the frame's **real** length in sixtieths: `0.667` at 90 Hz, computed
in `waitForNextFrame` where the true elapsed count already exists, and **fed
measured time so it self-corrects rather than assuming a period.**

### §2.1 — AND IT IS ONE LINE, NOT A 500-LINE PATCH

`lvlManageMpGame` is ~500 lines and duplicating it into a `RECOMP_PATCH` would be
a large surface for one assignment.

> **ITS ONLY CALLER IS `bossMainloop` (`boss.c:519`), AND `bossMainloop` IS
> ALREADY PATCHED** in `workbench_theboy.c`. So `geVrApplyFloatDelta()` runs
> immediately after `lvlManageMpGame` returns and overwrites the one value,
> before anything downstream reads it. **Change the value in one place rather
> than fork five hundred lines to reach it.**

### §2.2 — THE PAUSE SEMANTICS NEEDED CARE, AND THIS IS THE SUBTLE BIT

`lvlManageMpGame` zeroes `g_ClockTimer` when the controls are locked or the game
is paused, and the delta follows it to zero.

> **UNDER RB-02, `g_ClockTimer == 0` NO LONGER MEANS PAUSED.** It also means "no
> whole tick accrued this frame", which happens on **one frame in three while
> play is perfectly normal.** The two are indistinguishable from the counter.

**So the pause test is re-asked directly** — `g_ControlsLockedFlag` and
`checkGamePaused()` — rather than inferred. **Getting this wrong would leave the
world creeping while the watch is open**, and it would have looked like a physics
bug rather than a timebase one. **G-132-3 exists only to check it.**

---

## §3 — RB-04 WAS MEASURED, AND IT COLLAPSES

`126` RB-04 named the trap and gave one worked example (`gunfire.c:202-205`).
**Nobody had counted it.** Counted now, across the whole game tree:

> ## **216 `g_GlobalTimerDelta` REFERENCES. EIGHT SIT INSIDE A `g_ClockTimer > 0` GUARD. ALL EIGHT ARE DIVIDES.**

| Where | What |
|---|---|
| `bondview2.c:2885` | `speedverta /= delta + delta` |
| `bondview2.c:6709` | tank turret turn speed |
| `gun.c:2335-2337` | player velocity from position delta |
| `gunfire.c:203-205` | player velocity from position delta — **`126`'s example** |

**NOT ONE OF THEM IS AN INTEGRATOR.** Every one of the other 208 references is an
unguarded accumulation of the form `x += k * delta`, and **those sum correctly
from a fractional delta by construction.** `bondview2.c` — the view, the thing
this whole project is about — is **73 of 75 unguarded.**

> ### **SO RB-03 LANDS SAFELY ON ITS OWN, AND RB-04 SHRINKS FROM "AUDIT 34 GUARDS" TO "EIGHT NAMED DIVIDES."**
>
> **And the eight are a MILD fault, not a wrong rate:** they compute a rate from
> a displacement and will simply not refresh on the one frame in three where no
> whole tick accrued. **Stale velocity for 11 ms, not motion at two-thirds
> speed.** That is a real thing to watch for in the gun's inertia and the tank
> turret, and it is not a reason to hold RB-03.

**This is the third time in Route B that a cost survived from `92`/`99` into
three later documents without anyone counting it** — `118` did it to the duration
constants, `130` did it to the audio, this does it to the guards. **The counting
keeps being cheaper than the worrying.**

---

## §4 — WHAT IS DELIBERATELY UNTOUCHED

**`g_ClockTimer` STAYS INTEGER.** All 152 references and every "N sixtieths"
duration constant keep working, and `g_GlobalTimer += g_ClockTimer` still sums
whole sixtieths, **so the level clock keeps real wall-clock time.** That is
G-132-2 and it is a stopwatch test.

**`126` RB-08's aim-feel decision is untouched and remains a CHOICE.** Nothing
here moves `crosshair_x_pos` off the integer, so **weapon feel is bit-identical
to today** — `118` §4, and `92` was wrong to treat it as a forced consequence.

**RB-04 is not done.** The eight divides above are named, not moved.

---

## §5 — THE GATES

```powershell
.\build.ps1
.\vr.ps1 -NoXr -ViRate 90                 # RB-02 alone - 131 section 5
.\vr.ps1 -NoXr -ViRate 90 -FloatDelta     # then RB-03
```

**Run them in that order out of the one build.** If `131`'s gates fail, RB-03's
results mean nothing and the fix is upstream of here.

> **G-132-1 — THE GATE.** `119`'s `gdelta x1000` must read **~667 STEADY** at 90.
> **`1000` means RB-03 is not running.** **Alternating 0/1000 means the knob
> fired but the value is still the integer** — the insertion is in the wrong
> place or `lvlManageMpGame` is not the last writer.

**G-132-2:** the level clock still keeps real time — stopwatch against an
in-game countdown. `g_ClockTimer` stayed integer precisely so this holds.

**G-132-3 — PAUSE IT.** Open the watch. **The world must stop dead.** If it
creeps, §2.2's pause test is wrong and that is the first thing to fix.

**G-132-4 — THE ONE THAT MATTERS.** Does the world look smooth now? This is the
first gate in the entire Route B line that can answer *better* rather than
*not broken*, and **`-NoXr` on the monitor can answer it** — stick turn and world
motion, at least. **Head turn still needs RB-07 and a headset.**

**G-132-5:** `-ViRate 90` without `-FloatDelta` must still behave exactly as it
did in the first launch, and an unset launch must still be indistinguishable
from today.

---

## §6 — WHAT TO EXPECT, HONESTLY

**The stick-turn and world-motion half should improve here.** Sixty real frames
became ninety real frames (`131`), and now the motion inside them is continuous
rather than stepped.

**The head-turn half is NOT addressed by RB-03 and never was.** `124`'s target,
restated by the owner and not to be lost again: *"The judder happens when I turn
my HEAD."* **RB-02 and RB-03 delete the duplicate frame, the interpolated-frame
artefacts and the per-pass pose machinery** (`126`) — which is `125`'s entire
remaining scaffolding — **but the head pose path is judged in the headset, at
RB-07, and nowhere else.**

**And nothing here has been compiled.** `111` is what happens when a session
believes its numbers before the run; `113` is what happens when it believes them
after.
