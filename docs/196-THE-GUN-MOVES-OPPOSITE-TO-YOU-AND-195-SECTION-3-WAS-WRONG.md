# 196 — THE GUN MOVES OPPOSITE TO YOU. `195` §3 WAS WRONG, AND THE WEARER FALSIFIED IT IN ONE RUN.

**2026-08-25. Tiers per `182`. `[REPORTED]` is the wearer, verbatim.**

---

## §1 — THE REPORT, AND IT IS A CLEAN FALSIFICATION

> ***"No matter which version I run, if I go left or right or if I turn my head
> left or right or do anything, the gun does the opposite. If I go forward, the
> gun starts to come towards me. If I walk backwards, the gun goes forward."***

**`195` §3 STATED, IN BOLD: *"THE PICTURE WAS ALREADY CORRECT."* IT IS NOT, AND
THE ONLY REASON THAT CLAIM SURVIVED LONG ENOUGH TO BE BUILT ON IS THAT NOBODY HAD
WALKED WHILE WATCHING THE GUN.**

**AND `[REPORTED]` "no matter which version" IS ITSELF DIAGNOSTIC AND EXONERATES
THE NEW KNOB:** `195`'s term touched **only** `muzzle_origin`, the BULLET path.
**It could not have changed the picture in either arm** — so the inversion is
pre-existing, was always there, and `-NoRoomOrigin` is not implicated. **A report
that is identical across both arms of a knob is evidence about the knob as well
as about the fault.**

---

## §2 — THE GEOMETRY. IT IS THE SAME FAULT AS THE BULLET'S, IN THE PICTURE.

**`[READ]`, `rt64_render_context.cpp`:**

| | is at |
|---|---|
| **your eye** | `gameCamera + roomOffset` — the view matrix carries it (`194`) |
| **the drawn gun** | `gameCamera + (hand - head)` — `handPos`, head-relative, **no room term** |

**RELATIVE TO YOUR EYE, THE GUN THEREFORE SITS AT `-roomOffset`.** Walk forward:
the eye advances, the gun does not, **and the gun appears to come at you.** Walk
back and it recedes. **THE OPPOSITE OF YOU, ALWAYS, BY EXACTLY HOW FAR YOU
MOVED.** That is the report, term for term.

> **AND IT EXPLAINS THE HEAD-TURN HALF WITHOUT NEEDING A SECOND MECHANISM: THE
> EYES ORBIT THE NECK.** Turning your head is a small TRANSLATION of the eye, a
> few centimetres, so the same missing term shows up as the gun swinging the
> other way. **`[INFERRED]` — and it does NOT retire `T9`/`-SeamCompose 1`**
> (`192` §2), which is a ROTATION fault with its own independent evidence. **Both
> can be true, and `T9` is still owed as its own launch.**

**FOR THE GUN TO STAY IN YOUR HAND, `handPos` MUST BE `roomOffset + (hand - head)`.**

---

## §3 — ►► WHY `195` §3 REASONED ITSELF INTO THE WRONG PLACE ◄◄

**`195` §3 predicted that putting the term in the shared `handPos` would make the
viewmodel "slide across the room", and called that outcome a bug.** It cited
`154` §1 and `157` §6.1 — two real mis-diagnoses of the grip offset — as the
precedent.

**THE PRECEDENT WAS SOUND AND THE DIRECTION WAS BACKWARDS. THE SLIDE WAS ALREADY
HAPPENING, CAUSED BY THE TERM'S ABSENCE.** I reasoned about which consumer
*deserved* the term instead of asking where the quantity *belongs*, and the two
answers differ whenever one value feeds both the picture and the physics.

> **THE RULE THIS PRODUCES, AND IT IS NEW:** **when one published value feeds both
> what is DRAWN and what is SIMULATED, a correction belongs above the split or it
> will be right in one and wrong in the other.** `157` §6.1 is the same lesson
> from the other side — `field_8EC` had only drawing readers, so the hand moved
> the picture and nothing else for eighty documents.
>
> **AND THE COST WAS ONE RUN, NOT A SESSION**, because the wearer was given a gate
> that made him move (`G-194` needs stepping sideways) and he reported what he saw
> on the way. **A gate that puts the wearer in an unusual posture finds faults
> that no amount of standing still would.**

---

## §4 — THE CHANGE

**ONE TERM, ONE PLACE, ABOVE EVERY CONSUMER.**

```c
// in hand_override, after handPos is built and BEFORE anything reads it
handPos[i] += g_geVrHaveRoomPos ? g_geVrLastRoomPos[i] : 0.0f;
```

**AND IT IS REMOVED FROM `muzzle_origin`**, where `195` put it. **Leaving both
would DOUBLE-COUNT it — and the failure would have looked exactly like `195`
§2's "the sign is inverted" branch** (a miss of twice the displacement),
**sending the next session hunting a sign that was not wrong.** One term, one
place.

- **KNOB: `-NoRoomOrigin`, unchanged**, and it now reverts the picture too.
- **HOST-SIDE ONLY. ONE BUILD.** No new symbols, no `115` header, no game symbols.
- **`G-196`, AND IT NEEDS NO SHOOTING:** **hold the gun still and WALK — forward,
  back, left, right. THE GUN MUST STAY WITH YOUR HAND.** Then `-NoRoomOrigin`
  reproduces today's inversion on purpose.
- **THEN `G-194`** (`195` §2) for the bullet, which is now carried by the same term.

---

## §5 — THE OWNER'S ARCHITECTURAL QUESTION, ANSWERED HONESTLY

> `[REPORTED]`: ***"Don't we need to build a 3D floor space that lets me walk
> around in, and the arm should be staying attached to the camera area without
> moving? This is why I thought it would be better in the very beginning to add
> some sort of arm... we're still gonna need a left arm at some point."***

**THE DIAGNOSIS IS EXACTLY RIGHT AND THE REMEDY IS SMALLER THAN THE INSTINCT.**
*"The arm should stay attached to the camera area without moving"* **is precisely
§2's `roomOffset + (hand - head)`** — one addition, already written. **No floor
space and no arm model is required to get it, and neither would have delivered
it:** an IK arm hung off the same anchor would swing the wrong way just as the gun
does. **THE ANCHOR IS THE BUG, NOT THE ABSENCE OF AN ARM.**

**THE ARM ITSELF IS A REAL AND ALREADY-RECORDED WANT — `169` U-11, IK ARM** — and
it stays where it is on the sheet: **worth having, not on the critical path, and
strictly easier once the anchor is right.** The same is true of the left hand:
`hand_override` is already written for `hand` 0 and 1 and `structs.h` carries
`hands[2]`, so **the second hand is a wiring job, not a design job — once the
first one is correctly anchored.**

**AND THE "3D FLOOR SPACE" ALREADY HAS A HOME: `169` U-20 / `185` `C3`**, the room
behind the virtual screen, whose dependency `175` cleared. **That is a menu/hub
environment, not a play space** — GoldenEye's own levels are the play space, and
roomscale walking inside them is what `194`/`196` are making correct.

---

## §5b — THE PERFORMANCE REPORT: TWO DIFFERENT THINGS, AND ONE OF THEM IS REAL

> `[REPORTED]`: ***"the test here says eighty nine FPS, but the characters did that
> weird stutter thing... it actually felt like my GPU was struggling."***

**THOSE ARE TWO SEPARATE FAULTS AND THE WEARER HAS CORRECTLY NOTICED THAT THIS
ONE "WASN'T THE SAME".**

**1. THE CHARACTER STUTTER IS `RB-03`, AND IT IS NOT THE GPU.** `147` §2, the
owner's own deferral: **the frames and the view run at 90; THE WORLD ANIMATION
STILL ADVANCES IN 60 STEPS.** `145` showed it is not a small fix (a timestep
inside `MoveBond`, 1307 lines). **It shows on anything the world moves — the
truck before, characters now — and it is a KNOWN DEFERRED IMPROVEMENT, not a
regression.** High fps and stuttering characters is exactly its signature.

**2. THE "GPU STRUGGLING" FEELING IS SUPPORTED BY THE LOG. `[MEASURED]`, this
run: `LATE 93 of 3925 = 2.4%`, worst window `9/91`.**

| run | LATE |
|---|---|
| `109`, the old 60 Hz + interpolator build | **18%** |
| `147`, Route B worn and passed | **0/91 — ZERO** |
| **this run** | **2.4%, peaks at 10%** |

**IT IS NOWHERE NEAR THE OLD BUILD AND IT IS NO LONGER ZERO.** `146` §3 warned
the budget was sized for sixty frames and Route B asks for ninety real ones at
26 Mpx an eye; `147` came in under it with room to spare. **Something added since
has spent that room.**

**DO NOT GUESS WHICH — BISECT IT.**

> ### ►► AND MY OWN FIRST SUSPECT IS ALREADY ELIMINATED, BY A READ, BEFORE IT COST A RUN. ◄◄
> **I named `175`'s virtual screen, on the grounds that `178` "ungated it, so it
> now runs always". THAT IS A MISREADING OF `178` AND IT IS WRONG.**
>
> **`[READ]` `ge_vr_xr.cpp:2288-2290`: the screen draw sits inside the NO-EYE-PAIR
> BRANCH.** What `178` ungated was **PSO CREATION**, which had been trapped behind
> `GE_VR_TIMEWARP=0` — and even that is `if (!g_screenReady && !g_twTried)`, a
> no-op after frame one **including after a failed create, so there is no
> per-frame shader recompile either.**
>
> **SO DURING GAMEPLAY THERE IS AN EYE PAIR, THE BRANCH IS NOT TAKEN, AND THE
> SCREEN COSTS NOTHING.** It draws in menus, cutscenes and the front end — exactly
> where `175` §1 says a null eye split is *"a normal state, not a failure"*.
> **THE OWNER ASKED THE RIGHT QUESTION ("shouldn't it only run when it's a
> cutscene?") AND THE ANSWER IS THAT IT ALREADY DOES.**

**`185` `D4` already owns "the 15 fps samples"; this belongs with it.** With the
screen eliminated, **the honest first step is `118`'s de-risker — one `-NoXr` run
at `-ViRate 90`** — which separates "the GPU is short at 26 Mpx an eye" from
anything in the sim, **and costs no headset time and no B3 risk.**

> **THE PATTERN IS WORTH NAMING BECAUSE IT NEARLY REPEATED WITHIN ONE DOCUMENT:**
> §3 above is a retraction of a claim I reasoned my way into, and §5b's first
> draft was another one, aimed at the most recently-added feature. **The cure both
> times was a read that took two minutes.** `182` exists for this.

> **AND IT IS NOT URGENT ENOUGH TO DISPLACE THE AIM WORK.** 2.4% late is a
> comfort tax, not a blocker, and the aim chain is one gate from `B1`. **But it
> should be MEASURED before more is added on top**, because the next thing to
> land will otherwise be blamed for it.

---

## §6 — WHAT IS OWED

1. **BUILD ONCE. `G-196`** (§4) — walk, gun must stay in hand.
2. **`G-194`** (`195` §2) — the mark test, for the bullet.
3. **`T9` / `-SeamCompose 1`**, still its own launch, still owed (§2).
4. **`B1`**, judgeable once both gates pass.
5. **`U-18`**, **`noPose`**, **`U-21`**, **`U-22`** unchanged.

**NOTHING STAGED. THE COMMIT IS THE OWNER'S**, both repos.
