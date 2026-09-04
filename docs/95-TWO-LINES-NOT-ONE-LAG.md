# 95 — "IT BECOMES TWO LINES": THE SYMPTOM IS OSCILLATION, NOT LAG. AND STICK-TURN IS CLEAN.

**2026-08-23, from the wearer's second description.**

> ### FIRST, A CORRECTION OF SCOPE, AT THE WEARER'S OWN INSISTENCE
>
> ***"Just an example of the visual, though. Let's not get caught up on that."***
>
> **He is right and this document was drifting.** The mountain edge, the two
> lines and the plucked-rubber-band ringing were an ILLUSTRATION of what bad
> looks like, not a measurement of it. **`94` §6 exists because a description
> that flattered a theory got promoted to a finding within the hour, and
> building a mechanism out of a metaphor is the same mistake wearing better
> clothes.**
>
> **ONE thing in the report is structural and survives dropping every image:**
>
> > **STICK TURN IS CLEAN. HEAD TURN IS NOT. At comparable angular speeds.**
>
> **Both rotate the world across the retina; only one is bad. That localises the
> fault to the HEAD POSE PATH and it does not depend on any adjective.**
> Everything else below is context, and §4 is explicitly downgraded.

**Nothing is concluded here. `94`'s discipline still applies.**

---

## 1. THE REPORT — KEPT FOR THE RECORD, NOT LEANED ON

**In the wearer's own terms:**

| | |
|---|---|
| **Stick turn** | *"It doesn't judder, but it just feels not ninety hertz."* **CLEAN, but not good** |
| **Head turn, fast** | *"A line on the corner of a mountain edge will turn into TWO LINES as I turn my head"* — and *"like a rubber band when you stretch it and hit it, it goes back and forth, a reverberating vibration"* |
| **Head turn, slow** | *"The line IS bouncing, but not as far apart, so you don't see it. It kinda just beats"* |

> ### ONE THING WORTH KEEPING FROM THE VISUAL, STATED WEAKLY
>
> **`93` predicted LAG — one image in the wrong place, catching up.** What was
> described sounds more like an ALTERNATION between two states than a steady
> displacement. **If that holds, `93`'s predicted APPEARANCE was wrong even if
> its mechanism is right**, since a reused image at a fresh pose alternating
> with a fresh image at a fresh pose is a two-state alternation, not a lag.
>
> **Recorded as a caveat on `93`, not as evidence for anything.** The wearer has
> asked not to build on the visual and that instruction is respected.

---

## 2. THE MOST DIAGNOSTIC THING IN THE REPORT — AND IT WAS UNPROMPTED

**Stick turn is clean. Head turn is not. At comparable angular speeds.**

**Both rotate the world across the wearer's retina. Only one of them is bad.**
**So the fault is not in "the world moving" — it is specific to the HEAD POSE
PATH.**

| | Stick turn | Head turn |
|---|---|---|
| What rotates the view | the GAME's camera, baked into the rendered image | the HEAD POSE, applied by RT64 from `VrConfiguration` |
| Rate that quantity updates | 60 (the sim), interpolated by RT64 to ~90 | **60 — the GAME thread builds the config** |
| Pose submitted to the compositor | **constant** (the head is still) | **~90, from each present tick's `xrLocateViews`** |
| **Mismatch between image content and declared pose** | **NONE — the head is not moving** | **PRESENT, and proportional to head speed** |
| **Reported** | **clean** | **doubling, scaling with speed** |

> **The asymmetry is exactly what `93`'s mechanism predicts, and the wearer
> produced it without being asked to look for it.** That is independent
> evidence rather than a restatement of the first description — **which is the
> distinction `94` §6 was written about.**
>
> **It also sharpens `94` T4's prediction into something much harder to fake:**
>
> > **`-PoseLag 4` should make HEAD turns dramatically worse and do NOTHING
> > AT ALL to stick turns.** A knob that worsens both is not touching this
> > mechanism; a knob that worsens neither kills it.

---

## 3. THE ONE THAT MUST BE RULED OUT FIRST, AND IT COSTS TWO SECONDS

**"It becomes two lines" is ALSO the exact signature of B1** — `47`'s mirror
table, and `65`: *"two identical images submitted with two different eye poses
cannot fuse, so everything doubles."*

**B1 is fixed and measured at -117 px. But a residual stereo fault that only
appears DURING MOTION would not have shown up in a static screenshot
measurement, and every B1 measurement in this project was static.**

> # ►► CLOSE ONE EYE WHILE TURNING YOUR HEAD FAST. ◄◄
>
> | With one eye closed | Means |
> |---|---|
> | **The doubling VANISHES** | **It is STEREO** — the two eyes are showing different moments, or different poses, during motion. **A live B1-shaped fault that static measurement cannot see** |
> | **The doubling REMAINS** | **It is TEMPORAL** — one eye alone is alternating between two positions. `93`'s mechanism, or the 2:3 cadence, or both |
>
> **Two seconds, no build, and it splits the entire problem in half.** **Do this
> before anything else.**

**And its companion, also free:**

> **Turn your head fast, then STOP DEAD mid-turn while staring at the edge.**
>
> - **Doubling vanishes the instant you stop** -> the fault is driven by
>   MOTION. Temporal or pose.
> - **A static double remains** -> it is a STEREO geometry fault and it is
>   present at rest, merely invisible until an edge is moving.

---

## 4. THE "REVERBERATION" — DOWNGRADED, AND ONE USEFUL NEGATIVE FROM IT

**Checked, and it is worth recording as a NEGATIVE:** there is **no smoothing,
filtering, prediction or damping applied to the head pose anywhere in our
code** — `grep` across `ge_vr_xr.cpp` and `rt64_render_context.cpp` returns
nothing but the crash filter and `predictedDisplayPeriod`.

**So the "plucked rubber band" ringing is NOT an overshooting filter of ours.**

**No mechanism is inferred from the ringing.** The wearer has said not to build
on the visual, and this document does not. **The negative above is the only
thing kept from it, and a negative is worth keeping**: it means nobody needs to
go looking for a filter we do not have.

### AND THE WEARER'S OWN INTUITION POINTS AT THE REAL GAP

> ***"It's probably, like, trying to fix the issue as I'm moving by. I don't
> know."***
>
> **That is a description of REPROJECTION** — the compositor warping a frame to
> correct for head motion after the app rendered it. **And whether the Pimax
> runtime does that, and with what, is the single biggest unchecked thing in
> this whole investigation.** `94` §2 flagged it as the item that could make
> `93` wrong while every fact in `93` stays true.
>
> **If the runtime IS reprojecting, then feeding it a pose that says "no
> correction needed" is worse than useless — it is correction being actively
> aimed at the wrong target while the wearer moves.** **That is the wearer's
> sentence, in the pipeline's terms, and it is a better articulation of the
> concern than `93` managed.**
>
> **NEW: O79 — establish what Pimax OpenXR 0.1.0 actually does.** Does it
> reproject? Does it predict? Is there a setting? **This is a READ and a
> settings check, not an experiment, and it should happen before any fix.**

> **The runtime may still apply its own prediction.** **Pimax OpenXR 0.1.0's
> reprojection and prediction behaviour is STILL UNCHECKED** — `94` §2 flagged
> this as the thing that could make `93` wrong while every fact in it stays
> true, and it remains open.

---

## 5. THE SECOND FAULT, WHICH IS SEPARATE AND SHOULD NOT BE CONFLATED

> ***"When I turn with the controller it doesn't judder, but it just feels not
> ninety hertz."***

**That is `92`, and it is a different problem from the doubling.** The sim runs
at 60 (measured: 142 of 149 samples) and RT64 interpolates to ~90. **An
interpolated frame is a guess between two real ones, and 60 into 90 is a 2:3
cadence** — so "smooth but not native" is the honest expected result of the
current architecture.

**Do not let fixing the head-turn fault be judged by whether stick-turn starts
feeling native. It will not, and that is `92`'s quantum problem, not this one.**

---

## 6. WHAT CHANGES IN THE TEST PLAN

**`94`'s four tests all stand. Two free discriminators go IN FRONT of them.**

| | Test | Cost |
|---|---|---|
| **D1** | **Close one eye while turning fast.** Doubling gone = STEREO. Doubling remains = TEMPORAL | **2 seconds** |
| **D2** | **Stop dead mid-turn.** Double vanishes = motion-driven. Double persists = static stereo geometry | **2 seconds** |
| **T1** | The mirror recording — `47`'s method | 10 min, no build |
| **T4** | `-PoseLag 4`, **now with the sharper prediction: worse on HEAD turns ONLY, nothing on stick turns** | 3 launches |
| **T2/T3** | The `posecheck` numbers | free, same launches |

**D1 and D2 come first because they can invalidate T1 and T4's whole framing.
If the doubling is STEREO, `93` is looking at the wrong half of the pipeline
entirely** — and two seconds of the wearer's time is the cheapest thing in this
project.

---

## 7. HONESTLY, WHERE THIS LEAVES `93`

| | |
|---|---|
| **Strengthened** | The stick-vs-head asymmetry is exactly what the mechanism predicts, and it arrived unprompted |
| **Corrected** | **`93` predicted LAG and the symptom is DOUBLING.** The mechanism can produce doubling, but `93` did not say so and would not have predicted "two lines" |
| **Still untested** | Every one of `94`'s tests. **And D1 could still hand the whole thing to a stereo fault** |
| **Still unchecked** | **Whether the Pimax runtime reprojects at all** |

**`93` remains candidate 4. It is now the leading candidate on independent
evidence rather than on a description that flattered it — but "leading
candidate" is not "cause", and `49` killed five plausible mechanisms in one
session.**

**Nothing is built. `48` rule 1.**
