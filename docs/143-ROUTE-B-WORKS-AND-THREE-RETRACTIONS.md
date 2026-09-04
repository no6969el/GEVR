# 143 — RB-02 IS CONFIRMED WORKING. AND THREE OF MY OWN CONCLUSIONS WERE WRONG.

**2026-08-24, 18:20. The measurement that should have been taken first.**

---

## §1 — THE NUMBERS

```
clock: ticks=20 in 333ms -> per1000ms=60 | clk=1 gd1000=1000 sgf=1 wfnf=1702
clock: ticks=20 in 333ms -> per1000ms=60 | clk=0 gd1000=0    sgf=0 wfnf=1732
clock: ticks=21 in 333ms -> per1000ms=63 | clk=1 gd1000=1000 sgf=1 wfnf=1672
```

**138 samples. `per1000ms=60`, flat, for the whole session. fps mean 89.0.**

> ## **THE GAME RUNS AT 90 FRAMES A SECOND AND ITS CLOCK ADVANCES AT EXACTLY 60 SIXTIETHS A SECOND.**
>
> **THAT IS ROUTE B. THAT IS THE ENTIRE POINT OF IT.** Ninety real frames, real
> time keeping real time, no interpolator manufacturing thirty of them.

**AND THE ACCUMULATOR IS VISIBLY WORKING.** `sgf` and `clk` read **1 on some
samples and 0 on others** — the `0, 1, 1` pattern `129` §4 predicted, sampled at
random moments. **G-135-1 passes.** `92`'s *"90 Hz is structurally unavailable"*
is answered in the only way that counts: measured, in a running game.

**`wfnf` climbs by ~30 every 333 ms — ninety calls a second.**

---

## §2 — RETRACTION 1: `137` IS DEAD. THERE IS NO FAST-FORWARD.

`137` argued the 90 fps was a 1.5× fast-forward — that `waitForNextFrame` never
ran, `speedgraphframes` stayed at 1, and the world was running fast.

> **`per1000ms=60` KILLS IT OUTRIGHT.** The clock is correct. **`137` §2 is
> withdrawn in full**, and with it the reading of the owner's *"I felt like I was
> running faster"* as evidence of a timebase fault.

**That report still needs an explanation and it is now more interesting, not
less:** the world at 90 fps with a correct clock **should** feel different, and
"faster" is a plausible way to describe motion that has stopped being delivered
in whole-tick steps. **It may have been RB-03 working.** That is now a question
for the `-FloatDelta` run rather than a symptom of a bug.

## §3 — RETRACTION 2: `bossMainloop` WAS RUNNING ALL ALONG

`139`-`142` concluded from `retrace=1` and `wfnf=2` that `bossMainloop`'s retrace
case was executing about once per session.

> **BOTH NUMBERS WERE FIRST-CALL SNAPSHOTS, AND I READ THEM AS TOTALS.**
> The BOOT line prints on the first call, when `wfnf` genuinely was 2. The probe
> prints on its first retrace, when `retrace` genuinely was 1. **The very first
> sample of a counter is 1. I built four documents on it.**

**`wfnf=1612` on the FIRST clock sample of this run** — the same counter, read at
a sensible moment, from a loop I had concluded was not turning.

**This is `48` rule 3 in its purest form** — a number compared against the wrong
baseline — and `111` §5's exact shape: *"reading their own stall as the success
signal."* Here it was reading a counter's birth as its death.

## §4 — RETRACTION 3: THE CRASH WAS MINE, AND THE FIX CONFIRMS IT

`142` reverted the de-static'ing of eleven helpers after the mission-start crash.
**This run, with them `static` again, is clean: 510 `6dof-game` lines against 1,
and a full session played.** **The speculative cleanup caused the crash**, and
`48` rule 5 — do not mix a refactor into a debugging build — is the lesson, cited
all evening by the person who then broke it.

---

## §5 — WHAT IS AND IS NOT ESTABLISHED

**ESTABLISHED, AND THIS IS THE PROJECT'S BIGGEST RESULT SINCE B1:**

- **RB-02 works.** 90 fps, clock at 60/s, `deltaFrames` alternating 0 and 1.
- **Audio is correct** (`130`'s divisor, confirmed by ear).
- **Pause stops the world dead** (`132` §2.2's re-asked test).
- **The build is stable** and a mission plays. The owner: *"works good."*

**NOT ESTABLISHED:**

> **RB-03 IS STILL UNTESTED.** This run had no `-FloatDelta`, and the log proves
> it: **`gd1000=1000` when `clk=1`, and `0` when `clk=0`** — the integer cast,
> exactly as designed when the knob is off. **`g_GlobalTimerDelta` is still
> whole-sixtieth steps, so motion inside the frames is not yet smooth.**

**Also open:** the menu-mash crash (`137` §4, deferred by the owner), and the
head-turn half, which needs RB-07 and a headset.

---

## §6 — NEXT, AND IT IS ONE LAUNCH

```powershell
.\vr.ps1 -NoXr -ViRate 90 -FloatDelta
```

**No rebuild.** The binary already contains RB-03; the knob is all that changes.

> **G-135-3, THE GATE: `gd1000=` must read ~667 STEADY** instead of alternating
> 1000/0. **And `per1000ms` MUST STAY AT 60** — if the float delta is right, the
> game's speed does not change, only the smoothness of the motion inside it.
>
> **`per1000ms` moving off 60 with `-FloatDelta` would be a real speed bug**, and
> it is the one thing that would make the owner's "running faster" a fault after
> all.

**And the subjective question, which is now the only one left for RB-03:** with
the clock provably correct at 60, **does the world look smoother than the run
just played?** That comparison is clean for the first time — same build, same
level, one knob.

---

## §7 — THE HONEST NOTE

**Four documents and six builds were spent between `134` and here, and the
finding at the end is that the code written in `131` and `132` was correct the
whole time.** Every failure in between was instrumentation: a gate that could not
fire, a helper that was never emitted, a print gate keyed on a garbage global, a
counter read at birth, and a refactor that should not have been in the build.

**The one measurement that settled it — the engine's own clock against a wall
clock — was available from the first minute and cost ten lines.** `48` rule 9's
real lesson is not "instrument more", it is **measure the output, not the
plumbing.**
