# 199 — `T9` FAILED TOO. STOP GUESSING COMPOSITIONS AND RECORD THE RAW POSES.

**2026-08-25. Tiers per `182`. The owner asked for this instrument by name.**

---

## §1 — `T9` IS `[REPORTED]` WORSE, AND THAT IS TWO OF EIGHT

> `[REPORTED]` with `-SeamCompose 1`: ***"if I look to the left, the gun just goes
> to the right... if I try to turn the gun sideways it cocks down and to the
> right... I can't point it up or down anymore... if I point it all the way up it
> flips upside down facing me, which I guess is the orientation, but THE PATH
> THAT IT TOOK IS THE OPPOSITE of what you would do to do that."***

**`173`'s `R = Rhead^T * Rhand` IS FALSIFIED IN THE HEADSET.** It was the better
of two candidates by derivation and it is wrong by measurement. **The legacy
`R = Rhead * Rhand^T` was already wrong (`198`).**

> ### ►► TWO WEAR TESTS, TWO CANDIDATES, AND THERE ARE EIGHT. ◄◄
> `Rhead` or `Rhead^T`, on the LEFT or the RIGHT, against `Rhand` or `Rhand^T`.
> **At one wear test per candidate this is six more sessions, each of which can
> only answer "no".** `48`'s rule was written for exactly this: **measure, do not
> reason** — and `158` §2 already solved this SHAPE of problem correctly by
> publishing every candidate and letting ONE run pick.

---

## §2 — ►►►► THE OWNER'S INSTRUMENT, AND IT IS THE RIGHT ONE ◄◄◄◄

> `[REPORTED]`: ***"Is there no way to create a tool since we have all the source
> code that will get every single variable that's happening? So you know my
> positioning, the way I'm facing, how I'm aiming, how high my arm is,
> everything. So you can just tune it all from me running around and doing
> things."***

**YES, AND IT IS TWELVE NUMBERS.**

```
[gevr] POSEREC hq=(x y z w) hp=(x y z)  gq=(x y z w) gp=(x y z)
```

**`hq`/`hp` — the HEAD pose. `gq`/`gp` — the GUN hand pose. RAW, exactly as
OpenXR delivered them, logged BEFORE this function transforms anything.**

**THAT LAST PART IS THE ENTIRE DESIGN.** Everything else the file computes —
`R`, `handPos`, the aim ray, the muzzle — **is derivable from those twelve
numbers offline.** A recorder that logged a DERIVED value could be wrong in the
same way the code is wrong and would confirm the bug rather than expose it.
**This one cannot: it records the inputs, and the correct composition is then
something to be SOLVED rather than guessed.**

**9 Hz, one line, the same cost as the `hand seam` line that has been there for
sessions. `-NoPoseRec` turns it off, and it is knob-gated from the first day
because `148` item 2 is a standing complaint about debug instrumentation that
shipped ungated.**

---

## §3 — ►► THE CALIBRATION SEQUENCE. ONE MOTION AT A TIME, PAUSE BETWEEN. ◄◄

**THE PAUSES ARE NOT POLITENESS — THEY ARE HOW THE LOG IS SEGMENTED.** A still
head between two motions is an unambiguous marker in the data; a continuous
flowing sequence is not separable afterwards.

| # | do this | what it isolates |
|---|---|---|
| **1** | **STAND STILL**, gun held forward, **5 seconds** | the rest pose, and the noise floor |
| **2** | **YAW** head left, pause, right, pause — **GUN HELD STILL** | head yaw vs a fixed hand |
| **3** | **ROLL** head left, pause, right, pause — gun still | head roll |
| **4** | **PITCH** head up, pause, down, pause — gun still | head pitch |
| **5** | **TWIST the wrist** CCW, pause, CW, pause — **HEAD STILL** | hand roll vs a fixed head |
| **6** | **WALK** forward, back, left, right, pausing at each end | translation |

**SAY EACH MARK OUT LOUD AS YOU START IT** so the order in the log is not in
doubt. **Nothing needs to be aimed at and nothing needs to be shot.**

> **WHY THIS ANSWERS IT IN ONE RUN:** steps 2-4 move the head with the hand
> FIXED, so any candidate composition that varies during them is falsified
> immediately — the gun's world orientation must not change when only the head
> moves. Step 5 moves the hand with the head FIXED, which must produce a pure
> roll in place. **The correct composition is the only one of the eight that
> satisfies both, and both are checkable offline, on a laptop, with no headset.**

---

## §4 — WHAT THIS DOES NOT DO, STATED PLAINLY

**IT FIXES NOTHING BY ITSELF.** It is a measurement, and the build it ships in
still has the wrong composition — **`-SeamCompose 1` should be DROPPED for the
recording run** so the log is taken against the state the rest of the docs
describe.

**AND IT DOES NOT SETTLE THE SCALE QUESTION** (`198` §3.2): *"they look like
they're my height but they're really small"*, *"my hand looks five feet off the
ground"*, *"if I look down I feel like my face is on the floor."* **`166` §3's
pre-registered finding has fired** — it still looks like a toy model at
`-WorldUnitsPerMetre 100` with `167`'s FOV fix confirmed running, and `166` §3
said in advance that **that would mean the FOV was not the whole story.**
`[MEASURED]` from this run's own log, the stereo at 100 is geometrically EXACT:
eye offset `3.175` units = **63.5 mm IPD**, Bond's eye at **175 units = 1.75 m**,
ratio `0.0363` against reality's `0.0635/1.75 = 0.0363`. **So `159`'s "the number
is TOO HIGH" cannot be the explanation and lowering it would only make Bond a
giant.** The remaining suspect is `[READ]` `fovy=106` in the log against the
headset's true vertical of `2*atan(0.9657) = 88 degrees` — **106 degrees of world
squeezed into an 88 degree display makes everything small, far, and low.**
**THAT IS THE NEXT READ AND IT IS A READ, NOT A LAUNCH.**

---

## §5 — WHAT IS OWED

1. **BUILD. RUN §3's SEQUENCE. SEND THE LOG.** Drop `-SeamCompose 1`.
2. **THE COMPOSITION IS THEN SOLVED OFFLINE**, from twelve numbers, with no
   headset time and no further guesses.
3. **THE FOV READ** (§4) — does the WORLD's projection use the headset tangents,
   or is it still built from `fovy=106`?
4. **THEN** `G-196`, `G-194`, `B1`, `U-18`.

**NOTHING STAGED. THE COMMIT IS THE OWNER'S**, both repos.
