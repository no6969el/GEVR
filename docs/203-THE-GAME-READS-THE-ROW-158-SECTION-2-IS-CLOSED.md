# 203 — THE GAME READS `R`'s THIRD **ROW**. `158` §2'S OPEN QUESTION IS CLOSED BY ONE RUN.

**2026-08-25. Tiers per `182`. `[MEASURED]` from 734 paired `POSEREC`/`POSEOUT`
samples. NO HEADSET TIME WAS SPENT REACHING IT.**

---

## §1 — THE MEASUREMENT

**`202` logged `R`'s third ROW and third COLUMN beside the raw controller pose.**
Against the controller's true forward vector:

| | mean angular error |
|---|---|
| **COLUMN** | **0.00 deg** |
| **ROW** | **54.60 deg** |

**The COLUMN is the controller's forward BY CONSTRUCTION** (`200` made
`R = Rhand`, and the conjugation is identity now that the axis signs are `1`).
**And the drawn gun does not behave like the column. It behaves like the row.**

**BUCKETED BY TRUE YAW — AND THIS IS THE WEARER'S REPORT, IN NUMBERS:**

| true yaw | true pitch | **ROW** yaw / pitch | COLUMN yaw / pitch |
|---|---|---|---|
| **-80** | +37.5 | **-6.8 / -51.8** | -75.8 / +37.5 |
| **-60** | +22.7 | +27.6 / -31.3 | -58.5 / +22.7 |
| **-40** | +17.3 | +28.1 / -22.8 | -40.6 / +17.3 |
| **0** | +10.4 | -4.5 / -8.1 | +3.5 / +10.4 |
| **+40** | +11.6 | **-40.0 / -6.0** | +39.1 / +11.6 |
| **+100** | +6.9 | **-100.5 / +12.5** | +100.3 / +6.9 |

**YAW MIRRORED THROUGHOUT** — `[REPORTED]` *"when I aim the gun to the top right,
it points to the top left."*
**AND PITCH DIVERGING ONLY ON THE LEFT**, by up to **89 degrees** at true yaw
`-80`, while the right-hand half stays within a few — `[REPORTED]` *"if I go to
the right it's fine... if I start going to the left it starts lifting
upwards."*

> ### ►► AND THIS IS WHY `202` §2 WAS RIGHT THAT NO SIGN COULD DO IT ◄◄
> **It is not a reflection. It is the INVERSE ROTATION**, which differs from its
> own mirror by more and more as you turn away from the identity — **symmetric at
> the centre, wildly asymmetric at the extremes.** `202` closed the sign sweep on
> the grounds that a conjugation cannot produce an asymmetry; **the asymmetry's
> actual shape confirms that reasoning rather than merely being consistent with
> it.**

---

## §2 — `158` §2, QUOTED, AND CLOSED

> *"R's third ROW and third COLUMN are both plausible barrel axes and which one is
> correct depends on whether R maps gun-local->head or head->gun. That could not
> be settled by reading (`R = Rhead * Rhand^T`, `79`), so BOTH are published and
> one run picks. `48`: measure, do not reason."*

**IT WAS PUBLISHED IN `158`, IT SAT OPEN THROUGH FORTY-FIVE DOCUMENTS, AND ONE
RUN PICKED.** The game treats what we hand it as the transpose of what we mean.

**THE FIX: transpose `R` on the way out.** Its ROW becomes our COLUMN, and the
whole orientation comes right with it — **roll included, because the transpose of
the inverse is the rotation itself.**

**`-NoSeamT` reverts. HOST-SIDE, ONE BUILD, no new symbols, no `115` header.**

---

## §3 — `G-203`

1. **Aim top-RIGHT. It must point top-RIGHT.**
2. **Sweep LEFT. No lift, no inversion at the top-left.**
3. **NO REGRESSION on the three already passed:** wrist roll correct (`201`),
   head turns do not re-aim (`G-201`), walking stable (`G-200`).

> **AND IF IT IS RIGHT, THE POSE KNOBS ARE NEXT AND THEY ARE KNOB-ONLY:**
> `-GunOffY 8 -GunOffZ -2` are `154`'s PISTOL values measured against the legacy
> frame, and `-ViewmodelScale 0.5` with them. **Judge those only after the motion
> is confirmed** (`185` `T9`, and it has been right every time so far).

---

## §4 — THE METHOD, FOR THE RECORD

**`200` solved the composition from the INPUT side. `203` solved the consuming
frame from the OUTPUT side. Both from the same recorder, both offline, both
after the headset had already said "no" to hand-picked candidates.**

> **THE TWO HALVES WERE NEEDED FOR DIFFERENT REASONS, AND `202` §3 SAID SO BEFORE
> THIS RUN:** inputs alone proved the composition because the fault was in what we
> COMPUTED; they were blind to this one because the fault was in what the game
> CONSUMED. **A recorder that logs only inputs is trustworthy and incomplete. The
> pair is what closed it.**

---

## §5 — WHAT IS OWED

1. **BUILD ONCE. `G-203`** (§3).
2. **THE POSE PASS** — `-GunOffY` / `-GunOffZ` / `-ViewmodelScale`. Knob-only.
3. **`G-194`** (the mark test), then **`B1`/U-06** — the parallax, which is the
   next thing that changes what SHOOTING feels like (`193` §2).
4. **STILL OPEN AND INDEPENDENT:** the FOV/scale read (`199` §4), the 2.4% late
   frames (`196` §5b), B3's X close, **and the commit — both repos.**

**NOTHING STAGED. THE COMMIT IS THE OWNER'S.**
