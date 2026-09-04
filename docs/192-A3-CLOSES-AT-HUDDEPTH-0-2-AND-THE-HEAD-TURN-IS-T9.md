# 192 — `G-A3` PASSES AT `-HudDepth 0.2`. AND THE HEAD-TURN REPORT IS `T9`, WHICH IS ALREADY BUILT.

**2026-08-25. Tiers per `182`. `[REPORTED]` is the wearer, verbatim.**

---

## §1 — `A3` CLOSES, AND IT CLOSED WITHOUT A BUILD

> `[REPORTED]`: ***"`-HudDepth 0.2` is the one that actually worked."***

**`191` §2's `[INFERRED]` IS CONFIRMED:** the residual doubling was **not** a wrong
canting magnitude (`191` §1 retracted that) — **it was the HUD sitting at INFINITY
while the wearer verges much nearer.** A finite depth fuses it. **No code was
written, and `185` `A3` closes as a DEFAULT CHANGE.**

**AND THE OWNER OVERRODE "HALVE, NEVER NUDGE" CORRECTLY.** `[REPORTED]`: *"even
though you said no to nudge, it only made sense because 0.5 was so close."*
**`159`'s rule is about not tuning below the noise floor — it is not a rule
against stopping when the answer is visibly bracketed.** The sweep did its job:
`2.0` and `1.0` were plainly wrong, `0.5` was plainly close, so the next step was
information rather than noise. **Recorded because the rule and the exception both
matter.**

### ►► BUT 0.2 m IS NEARER THAN THE GUN, AND THAT IS A FINDING IN ITSELF ◄◄

**`[READ]` the term:** `ndc += -(eyeX_m / depth) / halfW`. With this run's
`eyeX = 0.032 m` and `halfW = 1.253`, **`0.2 m` is an extra `0.128` NDC of
convergence — on the same scale as the `0.1867` canting term itself.**

| depth | extra NDC |
|---|---|
| 2.0 m | 0.013 |
| 0.5 m | 0.051 |
| **0.2 m** | **0.128** |

**A gun held at arm's length is about `0.5 m`. THE CROSSHAIR HAD TO BE PLACED
NEARER THAN THE GUN TO FUSE.** `[INFERRED]`, and NOT to be built on: either the
wearer is verging nearer than the barrel, or some convergence is still
unaccounted for upstream. **What settles it is `B1`, not another knob** — see §3.

> **AND THE STANDING RULE APPLIES: RECORD THE VALUE, DO NOT LEAVE IT AS A KNOB.**
> `174`'s `-AimTrim` is the cautionary tale, and `-AimGain` survived years that
> way (`163`). **`0.2` is a MEASUREMENT of the residual convergence, not a
> preference**, and `B1` is expected to replace it with a computed depth.

---

## §2 — ►►►► THE HEAD-TURN REPORT IS `T9`, AND `T9` HAS BEEN BUILT SINCE `173`. ◄◄◄◄

> `[REPORTED]`: ***"when I turn my head left and right and you try to aim the gun,
> it seems to kinda wanna maneuver the hand in a way."***

**THIS IS THE SAME OBSERVATION, FROM THE SAME WEARER, THAT `173` WAS WRITTEN
FROM** — `[REPORTED]` then: *"if I turn my head left and right, the gun will
change directions in my hand automatically."* **TWO INDEPENDENT REPORTS, MONTHS
OF DOCUMENTS APART, OF ONE SYMPTOM. `182`: a `[REPORTED]` observation that
contradicts a document is evidence against the document.**

**`[READ]`, `173` §3 / `185` `T9`:** the seam computes `R = Rhead * Rhand^T`; the
correct view-space orientation is **`R = Rhead^T * Rhand`** — **and the AIM path
has always used `Rhead^T`.** So the drawn gun and the aim ray have been on **two
different transforms for the entire project.** That is `166` §4's *"the drawn gun
is the liar"* hypothesis, and this report is its second confirmation.

**THE FIX IS BUILT, KNOB-GATED, AND HAS NEVER BEEN WORN: `-SeamCompose 1`.**

> **AND IT IS COSMETIC, WHICH IS WHY IT MATTERS MORE THAN IT SOUNDS.**
> `157` §6.1 established that **every reader of `field_8EC` in the game tree is a
> DRAWING site** — so the seam moves the gun's PICTURE and nothing else. **The
> shot is unaffected. But you AIM BY LOOKING AT THE GUN**, so a lying picture
> destroys trust in an aim that may already be correct. **It cannot be dismissed
> as "only cosmetic" for exactly that reason.**

**`185` PUT `T9` SECOND-TO-LAST ON PURPOSE, AND THAT REASON STILL STANDS:**
*"if it passes, `-HandAxis*` and `-GunOff*` were all tuned against a reference
that no longer exists."* **So it is a SEPARATE LAUNCH, never folded into an aim
run** — and if it passes, the grip constants are re-opened as a known consequence,
not as a surprise.

---

## §3 — THE THIRD REPORT: THE PERSPECTIVE AND THE GUN'S DEPTH. NOT YET DIAGNOSED.

> `[REPORTED]`: ***"the perspective is still off, which causes the gun to go
> beyond the distance of the aimer."***

**NOT CLOSED, AND NOT GUESSED AT HERE.** It is consistent with §1 — a crosshair
that fuses at `0.2 m` while the barrel extends past it **is** a gun reaching
beyond the aimer's depth — but "consistent with" is not a diagnosis, and this
project has spent sessions on exactly that move (`180`, `184` §3a).

**THE CANDIDATES, IN THE ORDER THEY SHOULD BE TAKEN, AND ALL ALREADY ON THE
SHEET:**
1. **`B1`, U-06 — THE PRINCIPLED CURE.** Drive the crosshair's convergence from
   the **last impact distance** rather than a fixed knob, PD's
   `vrComputeCrosshairParallax` (`185` `B1`, 25 lines, no new symbols). **If the
   crosshair sits at the TARGET's depth, "the gun goes beyond the aimer" cannot
   arise: the two are at the same distance by construction.** `[MEASURED]` §1's
   `0.2` becomes the fallback for "no impact yet", not the answer.
2. **`166` §3, UNRESOLVED SINCE IT WAS WRITTEN:** *"IF IT STILL LOOKS LIKE A TOY
   MODEL AT 100, THE FOV WAS NOT THE WHOLE STORY AND THAT IS THE FINDING."*
   `-WorldUnitsPerMetre` is at 100 and this report is the closest thing to an
   answer that has been given. **It wants the guard test** (`159`: a person is
   known by heart, and the guard is guaranteed to be your height), **not a
   viewmodel tweak.**
3. **`-ViewmodelScale` / `-GunOffZ`** — LAST, and only with a number in hand.
   **These are the knobs `159` warns are tuned against whatever else is wrong**,
   and `T9` (§2) may re-reference both.

---

## §4 — WHAT IS OWED, IN ORDER

1. **`T7`/`B2` — STILL THE PRIORITY, STILL NOT RUN.** `[REPORTED]` nothing yet
   about the wall test. **Same command, `-HudDepth 0.2`, nothing else changed.**
   Near wall then far wall: **miss SHRINKS -> parallax, `B1` is the cure; miss
   HOLDS -> a constant angular error.**
2. **`T9`, `-SeamCompose 1`, AS ITS OWN LAUNCH** (§2). Hand held still, head
   turning: **the gun must not re-aim.**
3. **`A3` DEFAULT:** make `GE_VR_HUD_DEPTH` default `0.2` in the next build, or
   deliberately leave it as a launch argument until `B1` lands. **Owner's call —
   it changes what "just run it" means** (`150` H-9 is the precedent).
4. **THEN `B1`** (§3), which is expected to supersede §1's constant.
5. **NEXT BUILD ALSO CARRIES:** `noPose` (`190` §3), `U-21`, `U-22`.

**NOTHING STAGED. THE COMMIT IS THE OWNER'S**, both repos.
