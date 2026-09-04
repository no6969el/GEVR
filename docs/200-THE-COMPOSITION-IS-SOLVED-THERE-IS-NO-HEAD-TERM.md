# 200 — SOLVED FROM 744 RECORDED POSES: THERE SHOULD BE NO HEAD TERM AT ALL. `R = Rhand`.

**2026-08-25. Tiers per `182`. `[MEASURED]` from `199`'s pose recorder, first run.**
**NO HEADSET TIME WAS USED TO REACH THIS. It was solved on a laptop.**

---

## §1 — ►►►► THE MEASUREMENT ◄◄◄◄

**744 `POSEREC` samples. 83 transitions in which the HEAD MOVED (>1.5 deg) AND
THE HAND DID NOT (<0.4 deg).** In those windows the gun's world orientation must
not change — that is `T9`'s gate, expressed as arithmetic instead of an
impression. **All eight candidates, drift per head-only step:**

| composition | drift |
|---|---|
| **`Rhand`** — no head term | **0.14 deg** |
| `Rhand^T` | 0.14 |
| `Rhead * Rhand^T` — **THE LEGACY DEFAULT** | 4.35 |
| `Rhead^T * Rhand` — **`173`, and `T9`** | 4.40 |
| `Rhead * Rhand` | 4.27 |
| `Rhead^T * Rhand^T` | 4.18 |
| `Rhand * Rhead^T` | 4.39 |
| `Rhand^T * Rhead` | 4.41 |

**THE HEAD ITSELF MOVED 4.34 DEG PER STEP IN THOSE WINDOWS.**

> ### **EVERY FORM CONTAINING A HEAD TERM DRIFTS BY EXACTLY THE HEAD'S OWN MOTION.**
> **That is not a tuning error and not a sign — it is the head rotation being
> applied TWICE.** `194` established that the head pose reaches the eye view
> matrix and is composed onto the game's view matrix at render time. **So
> anything drawn in the game's camera space is rotated by the head FOR FREE, and
> a head term in `R` spends a rotation that was already spent.**
>
> **`173` AND THE LEGACY FORM ARE TWO DIFFERENT WRONG WAYS TO DO THE SAME
> DOUBLE-APPLICATION.** That is why swapping between them changed the symptom and
> never removed it, across two wear tests.

**`Rhand` VS `Rhand^T` NEEDS NO RUN EITHER.** The AIM path takes its forward as
`-Rhand` column 2 (`158` §5), and `193` §1 **measured that aim as correct across
55 shots.** `Rhand^T` points elsewhere. **Taking `Rhand` makes the drawn gun and
the aim ray the same object at last** — which is exactly what `166` §4's *"the
drawn gun is the liar"* was reaching for.

---

## §2 — THE POSITION TAKES THE SAME ANSWER, AND IT COLLAPSES `194` AND `197`

**The argument is identical and it is the same measurement:** the view matrix
already carries the head's pose, so a head term in the position is a second
application too.

**AND THE TWO PREVIOUS DOCUMENTS WERE CONVERGING ON THIS WITHOUT SEEING IT:**

```
docs\194:  origin = (hand - head) + (head - gameCamera)
           and (head - gameCamera) IS the head's play-space position
           so the sum is exactly:  hand      <- the RAW play-space hand position
```

**`197`'s transpose was the right correction to the wrong expression. `194`'s
room term was a correct term added to a value that should never have been
head-relative.** Under the solved frame the position is simply the hand's
play-space position, scaled.

> **THE ROOM TERM IS NOT DROPPED — IT IS SUBSUMED**, and it must therefore NOT be
> added again. **Adding it twice would make the gun run away at DOUBLE the
> wearer's walking speed**, and `196` already recorded that a double-counted term
> reads as a working fix with an inverted sign, which is the most expensive way
> for this to fail.

---

## §3 — WHAT SHIPPED

**`GE_VR_SEAM_FRAME` — `2` = `Rhand` + raw play-space position (**NEW DEFAULT**),
`1` = `173`'s form, `0` = legacy.** `-SeamFrame 0|1|2`. `-SeamCompose 1` still
selects `1`, so nothing already written stops working.

**HOST-SIDE ONLY. ONE BUILD.** No new symbols, no `115` header, no game symbols.

### `G-200` — NO SHOOTING
1. **Hold the gun still and turn / tilt your head. THE GUN MUST NOT RE-AIM.**
2. **Twist your wrist. It must roll IN PLACE, not sweep the `199` letter-C arc.**
3. **Walk. It must come with you** — and **not at double speed** (§2).

> **AND THE EXPECTED COMPLICATION, STATED BEFORE THE RUN SO IT IS NOT MISREAD AS
> A FAILURE:** `-HandAxisX -1 -HandAxisZ -1` (`155`) and `-GunOffY 8 -GunOffZ -2`
> (`154`) were **all tuned against the legacy frame**, and `185` `T9` warned that
> a pass here re-references them. **JUDGE THE MOTION FIRST AND THE POSE SECOND.**
> A gun that now tracks correctly but sits at a wrong ANGLE or OFFSET is those
> knobs, **not this frame**, and re-tuning them is a separate, cheap, knob-only
> job that must not be started until the motion is confirmed.

---

## §4 — WHAT THIS SAYS ABOUT THE METHOD, AND IT IS THE POINT

**TWO WEAR TESTS WERE SPENT ON TWO OF EIGHT CANDIDATES, ONE AT A TIME, AND BOTH
COULD ONLY ANSWER "NO".** The recorder cost one build and one calibration run and
**answered all eight at once, offline, with a margin of thirty to one.**

> **THE OWNER ASKED FOR THE INSTRUMENT** (*"is there no way to create a tool...
> that will get every single variable that's happening"*), **and it was the right
> call at the right moment.** `48`'s *"measure, do not reason"* and `158` §2's
> *"BOTH are published and one run picks"* both said so; **the project had the
> rule and did not apply it here until asked.**
>
> **AND THE RECORDER LOGS ONLY RAW INPUTS.** Had it logged a DERIVED value it
> would have been wrong in the same way the code was wrong and would have
> confirmed the bug. `199` §2.

---

## §5 — WHAT IS OWED

1. **BUILD. `G-200`** (§3). Motion first, pose second.
2. **IF THE MOTION IS RIGHT: re-check `-HandAxis*` and `-GunOff*`** against the
   new frame. Knob-only, no build.
3. **THEN `G-196` / `G-194`** — both are now carried by §2's single term.
4. **THE FOV / SCALE READ** (`199` §4) — `fovy=106` against the headset's 88.
5. **THEN `B1`, `U-18`.** `noPose`, `U-21`, `U-22` on any build.

**NOTHING STAGED. THE COMMIT IS THE OWNER'S**, both repos.
