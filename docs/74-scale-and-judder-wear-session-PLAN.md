# 74 — PLAN: one wear session, two no-code questions. Scale (O53) and judder (O58).

**2026-08-23, late session. Written before the runs, per `48` rule 2. Nothing
here is built, compiled or changed — every item is a launch flag that already
exists and a question answered by wearing it.**

**Read `71` O1 and `73` first. This is the execution sheet for both.**

---

# PART 1 — THE JUDDER FALSIFIER. Do this FIRST, at the default.

**Why first: it changes nothing.** Default `-UnitsPerMetre 100`, the exact
conditions the judder was reported in. Part 2 then changes one variable.

## The claim being tested (`73`, O58)

> The game's VI clock halves to **30** in a heavy scene while the renderer must
> still produce **90**. The interpolation stretch triples exactly when the scene
> gets busy.

**If that is the judder, the judder is SCENE-DEPENDENT.**

## The run — a scripted timeline, because the log has no timestamps

`gevr.log` prints one `fps` line per second and **nothing in it says what time it
is**, so the only way to align what you felt with what it recorded is to agree
the timeline in advance and stick to it.

```powershell
cd C:\Users\<USER>\Desktop\GoldenEye64Recomp
.\vr.ps1
```

| Phase | Duration | What to do | What to report |
|---|---|---|---|
| **A** | **~60 s** | Enter a level. **Stand still**, no enemies engaged, look slowly around a corridor or a wall | Does it judder? A word: none / slight / bad |
| **B** | **~60 s** | **Get into a real firefight.** Multiple guards, alarm if it comes | Same word |
| **C** | ~20 s | Stand still again somewhere quiet | Same word |

**Keep the phases in that order and roughly those lengths.** I map log sample
index to elapsed seconds and check whether the VI drops line up with B.

## THE GATES — written before the run

| Outcome | Verdict |
|---|---|
| **A quiet, B bad, C quiet** — and the log shows 30 fps only in B's window | **O58 CONFIRMED.** The interpolator's input rate is the judder, and the fix is a frame-pacing question, not an XR one |
| **A and B judder the same** | **O58 IS WRONG.** Kill it in `73` at source. `72`'s per-frame `max` + late-count becomes the next move |
| **B bad but the log shows NO drop to 30** | The judder is real and the VI clock is not it. **Also means `73`'s measurement does not generalise from `-NoXr` to worn** |
| **Nothing judders at all this session** | Say so. `71` O2 recorded judder once; a symptom that will not reproduce is a different problem from one that does |

**What would this test report if it were looking at the wrong thing?** If the
judder is in the *pose* rather than the *image* — a fresh pose on a stale frame —
it would judder in A and B equally and this test would call O58 wrong, which is
the correct call for the wrong reason. **So if A and B are equal, do not conclude
"not the interpolator"; conclude "not scene-dependent", which is weaker.**

---

# PART 2 — THE SCALE SWEEP. `16`'s open question, judgeable for the first time.

> **RUN AND CORRECTED, 2026-08-23. `75`.** The sweep's step size was wrong, not
> its axis. **100 vs 50 was reported as "it looks the same"** even though the
> live `eyeDelta` genuinely halved (-6.392 -> -3.196), which nearly closed this
> as a non-response. **`-UnitsPerMetre 400` then changed it unmissably** — world
> small, player tall, **gun small too**. So scale responds, `71`'s direction was
> backwards, the correction goes **DOWN**, and **the viewmodel moves with the
> knob**, which contradicts this document's own prediction below that it would
> not. **The two-fault split in O53 is no longer established.**
>
> **The lesson is `56`'s, again: use a step nobody could miss.** A 2x step in a
> direction the tester is unsure of reads as noise.

## FIRST, the thing `71` may have backwards — and the sweep settles it

`71` read the report as *"the world reads too LARGE, so sweep units/metre UP."*
**But what was actually said was:**

> *"The arm and gun size is very large **in comparison to the people and
> surroundings**."*

**That is the player reading large against the world, which is the opposite
framing, and it argues DOWN, not up.** Rather than resolve it by argument — this
project's most expensive habit — **the sweep goes in both directions and the
DIRECTION IS THE FINDING.**

## What `-UnitsPerMetre` does and does not touch

| | |
|---|---|
| **Higher u/m** | IPD in game units grows, and so does how far a physical step moves you. **The world reads SMALLER** |
| **Lower u/m** | The reverse. **The world reads LARGER** |
| **The viewmodel's ANGULAR size** | **Not touched at all.** The arm's projection is the game's own. What u/m changes is the *stereo distance* it converges at, so it can read nearer or further — but not wider |

**So judge the sweep on the WORLD ONLY.** A doorway, a guard's height, a
corridor ceiling. **Do not judge it on the arms** — that is the second, separate
fault in O53 and no u/m value can fix a ratio.

## The runs — four launches, one flag each

```powershell
.\vr.ps1                      # 100  - the baseline, "comically large"
.\vr.ps1 -UnitsPerMetre 150   # world smaller
.\vr.ps1 -UnitsPerMetre 200   # world smaller still
.\vr.ps1 -UnitsPerMetre 50    # world LARGER - the other direction
```

**Same level, same spot, every time.** Pick one with a doorway and a standing
guard near the start and go back to it.

## THE INSTRUMENT CHECK — do this on the FIRST launch or the whole sweep is void

**`vr.ps1` prints an expected half-IPD at startup, and `gevr.log` prints the
real one every second:**

```
[gevr] head: ... | eye sep 6.37 units          <- at 100 u/m
```

**Expected: `eye sep` ~= 0.0635 x u/m.**

| u/m | eye sep should read |
|---|---|
| 100 | ~6.4 |
| 150 | ~9.5 |
| 200 | ~12.7 |
| 50 | ~3.2 |

**If `eye sep` does not move when the flag moves, the knob is not connected and
every judgement in this sweep is void.** This project has found a knob with a
deleted consumer twice — `32`'s `-Sign` and `24`'s `-ForceEye`. **Check the
number before trusting the feeling.**

## THE RECORD — fill this in, all four rows, not just the winner

`MODS-IDEAS` needs the losers as much as the winner: Big James mode is defined
by the *distance* from the correct value, and if only the winner is written down
the mode has no setting.

| u/m | `eye sep` | Doorway | A guard's height | Corridor / ceiling | Verdict |
|---|---|---|---|---|---|
| 100 | | | | | |
| 150 | | | | | |
| 200 | | | | | |
| 50 | | | | | |

**And one line per row on the arms:** *did the arm cover more, less, or the same
fraction of your view?*

## THE GATES — written before the runs

| Outcome | Verdict |
|---|---|
| One value makes a doorway read like a doorway AND a guard read human | **That is `16`'s measurement.** It goes into `16` as the default, replacing the derivation, and 100 becomes Big James |
| The world reads right at some value but the arms are STILL huge | **O53's split is confirmed: two faults.** The viewmodel gets its own slice, and no more u/m work |
| **The arms change apparent SIZE across the sweep** | **Our model of what u/m drives is wrong.** Stop and re-read the projection path before touching anything — the prediction above says they must not |
| Nothing in 50..200 reads right | The scale fault is not in this knob. `16`'s derivation may be fine and something else is scaling the view |

---

# WHAT THIS SESSION WILL HAVE PRODUCED

- **O58 confirmed or killed**, by observation, in one level.
- **`16`'s three-year-old-shaped open question closed with a measurement**
  rather than a derivation, or proven to be in a different knob.
- **The Big James numbers**, recorded while they are cheap.
- **Zero lines of code**, so nothing here can regress anything.

## The instrument gap this plan had to work around — worth fixing later

**`gevr.log` has no timestamps.** Part 1 needs a scripted timeline purely because
a log line cannot say when it happened. **One `%.1f` of elapsed seconds at the
head of each periodic line** would make every future "it did X while I was doing
Y" answerable directly. Not built, not this session.
