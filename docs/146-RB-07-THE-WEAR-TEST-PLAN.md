# 146 — RB-07. THE WEAR TEST. THE ONLY GATE THAT MATTERS, AND IT COSTS A REBOOT.

**2026-08-24. The plan, written before the headset goes on, because B3 makes
every VR session expensive and `74`'s lesson is that an unplanned wear test
wastes one.**

---

## §1 — DO NOT REBUILD FIRST

**Run RB-07 on the exact binary that has been validated at `-NoXr`.** It is
carrying debug instrumentation — the clock probe, the retrace probes, the boot
lines — and the temptation is to strip them first.

> **DO NOT.** They cost roughly one log line a second and some float arithmetic
> per frame. **`142` is four hours old: a "tidy-up" landed in a debugging build
> and cost a run and a crash.** The binary that is known-good at `-NoXr` is the
> one that goes in the headset. Rule 5, applied before the mistake this time.

---

## §2 — THE COMMANDS

**Headset on and tracking BEFORE launch.**

```powershell
.\vr.ps1 -UnitsPerMetre 50 -SeamNoRot -HandPosZ 1 -ViRate 90
```

**CLOSE WITH `taskkill /F /IM GoldenRecomp.exe`. NEVER THE X — that is B4, and
B3 bugchecks the machine on VR session close and costs a reboot** (`39`, `75`).

**PIN `ds_option` FIRST.** `111` recommends `2` as the default and measured it
free; **the in-game menu rewrites `graphics.json`, so re-check it after any menu
visit** (`108` §4). And `rr_option` must still be `"Manual"` / `rr_manual_value`
90.

---

## §3 — THE PREDICTION THAT MATTERS, AND IT IS A COST

> ## **RB-02 DELETES THE INTERPOLATOR AND REPLACES IT WITH 50% MORE REAL RENDERING.**

Before: RT64 rendered **60** real frames and manufactured 30.
Now: the game submits **90** real frames and `interpUsed=0`.

**The `-NoXr` logs already show it — `eye0=90`, `interpUsed=0`.** On a monitor
that is free. **In the headset each eye is 5838x4498 — 26 Mpx — and `109`
measured the old 60 fps build at a 10.27 ms mean against an 11.11 ms budget,
with `LATE 16/91 (18%)`.**

> **THAT HEADROOM WAS SIZED FOR SIXTY REAL FRAMES. RB-02 ASKS FOR NINETY.**
> **If the GPU cannot hold it, fps falls below 90 and the compositor starts
> repeating frames — which is the doubling this whole project has been chasing,
> arriving by a new route.**

**SO THE FIRST THING TO READ IS NOT THE FEELING, IT IS `fps` AND `LATE`.**
If fps is not ~90, nothing worn afterwards is judgeable and the answer is
`ds_option 1`, or `-ResScale 0.7`, before anything else is concluded.

---

## §4 — THE GATES, IN THE ORDER TO READ THEM

**FROM THE LOG, BEFORE JUDGING ANYTHING WORN:**

**G-146-1: `fps` ~90 and `submits` ~90.** Below that, see §3 and re-run smaller.
**G-146-2: `interpUsed=0` and `dupSrc` ~0/90.** **This is the structural prize.**
`dupSrc` has read **30/90 through every build in this project's history** —
stride fix, phase fix, per-pass read, 90 Hz host refresh, display-time
prediction, previous pose. **If it reads ~0 now, the duplicate frame is dead and
Route B did what fifteen documents could not.**
**G-146-3: `LATE`** (`109`). At 90 Hz the budget is 11.11 ms.
**G-146-4: `per1000ms=60`** on the clock line — the timebase must still be right
with XR on, not only at `-NoXr`.

**WORN, AND ONLY IF THE ABOVE PASS:**

> ### **G-146-5 — THE HEAD TURN. `124`'s TARGET, RESTATED BY THE OWNER AND NOT TO BE LOST:**
> *"The judder happens when I turn my HEAD. The stick turn is just
> semi-satisfactory. I tried to make that clear a few times so we wouldn't just
> fall back to fixing the head turn and then settle for the 60 feeling of the
> world."*

**G-146-6: the stick turn and world motion.** `92`'s *"feels not ninety hertz"*
— that complaint was about a 60 Hz sim shown at 90. **The sim is now 90.**

**G-146-7: the doubling on distant characters and mountain edges** (`108` §2),
which was diagnosed as the duplicate frame. **If G-146-2 passes and this
persists, the duplicate frame was never its cause.**

---

## §5 — WHAT AN HONEST RESULT LOOKS LIKE

**`126` claimed RB-02 would delete, at once:** the duplicate frame, the
interpolated-frame artefacts, the per-pass head pose problem and the pose/image
mismatch. **The first two are structural and the `-NoXr` logs already support
them.** The head-pose ones are not automatic — `117` §1 re-framed per-pass posing
as a workaround for an interpolator that no longer exists, but **one pose per
rendered frame at 90 Hz is still one pose per 11.11 ms, and whether that is
enough for a head turn is exactly what has never been measured.**

> **SO THE HONEST PREDICTION, ON THE RECORD BEFORE THE RUN: the stick-turn and
> world-motion half should be clearly better. THE HEAD-TURN HALF MAY NOT BE
> FIXED AT ALL.** `125` built the entire view path correctly and the artifact
> survived it — *"it feels better... so much tighter now... but it's still
> absolutely happening."*

**If the head turn is still wrong at a true 90 Hz sim with no interpolation and
no duplicate frames, then every remaining explanation in this project is
exhausted and the cause is upstream of everything we have touched** — the
runtime's compositor, the Pimax layer, or the panel itself. **That would be a
genuinely new place to look, and reaching it would be worth the reboot on its
own.**
