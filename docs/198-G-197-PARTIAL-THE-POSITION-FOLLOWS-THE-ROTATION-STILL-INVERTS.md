# 198 — `G-197` IS A PARTIAL PASS. THE POSITION FOLLOWS YOU NOW. THE ROTATION STILL INVERTS, AND THAT IS `T9`.

**2026-08-25. Tiers per `182`. `[REPORTED]` verbatim, first wear of `197`.**

---

## §1 — WHAT IMPROVED, IN THE WEARER'S OWN WORDS

> ***"If I hold the gun in front of me and I tilt my head to the left, the gun in
> hand will tilt to the right BUT COME TO THE LEFT WITH ME."***

**TWO THINGS IN ONE SENTENCE, AND THEY ARE THE TWO HALVES `197` SPLIT:**

| | before `197` | now |
|---|---|---|
| **POSITION under head ROLL** | *"tilt to the right, the gun shoots off to the left"* | **"COMES TO THE LEFT WITH ME" — IT FOLLOWS** |
| **ORIENTATION under head ROLL** | inverted | **"the gun will TILT TO THE RIGHT" — STILL INVERTED** |

**`197`'s transpose is CONFIRMED for the roll axis of the position**, by the same
wearer who reported the fault. **AND THE ORIENTATION WAS NEVER IN `197`'s
SCOPE** — `197` §3 said so explicitly: *"It fixes where the gun IS, not where it
points."*

---

## §2 — ►►►► WHAT IS LEFT IS `T9`, AND `T9` IS BUILT AND HAS NEVER BEEN WORN. ◄◄◄◄

**EVERY REMAINING SYMPTOM IS AN ORIENTATION SYMPTOM:**

> ***"If I turn right, the gun goes off the screen to the left. If I go to the
> left, the gun goes to the far right. Instead of staying straight, IT'S TURNING
> AND GOING IN THAT DIRECTION."***

**Note the wearer's own words: *"it's TURNING and going in that direction."* The
displacement he sees is the far end of a gun that is being ROTATED about a pivot,
not a gun being translated.** A metre-long lever rotated by the head's yaw sweeps
its muzzle off-screen while its grip barely moves.

> ***"If I twist my hand counterclockwise... it goes ALL THE WAY TO THE GROUND
> BEFORE IT FLIPS OVER. It's like it's flipping on a big letter C."***

**THAT IS THE CLEANEST ROTATION EVIDENCE IN THE REPORT.** A roll applied in the
correct frame spins the gun IN PLACE. **A roll composed in the wrong frame sweeps
it along an ARC — the wearer drew a letter C with his description.** And
`[REPORTED]` *"harder to do it clockwise"* is what an asymmetric composition
does: the two directions are not mirror images once the frames disagree.

### AND `173` ALREADY WROTE THE FIX FOR THIS AND NEVER TESTED IT

`173` §3 / `185` `T9`: the seam computes **`R = Rhead * Rhand^T`**; the correct
view-space orientation is **`R = Rhead^T * Rhand`** — **the same handedness
`197` just fixed in the position, in the variable next to it.**

**`-SeamCompose 1`. BUILT, KNOB-GATED, NEVER WORN, NO BUILD REQUIRED.**

**IT IS NOW THE HIGHEST-VALUE LAUNCH ARGUMENT AVAILABLE** — it is the only
untested thing that addresses the only remaining class of symptom, it costs one
flag, and `197` has just given independent evidence that its diagnosis of the
handedness was right.

---

## §3 — TWO RESIDUALS, RECORDED AND NOT EXPLAINED

**1. `[REPORTED]` walking the line: *"the gun slowly kinda moves up a little bit,
but not too much... it's on some sort of warp."*** **SMALL, and much smaller than
the pre-`197` *"goes down to the floor."*** It may be the yaw half of the same
orientation fault (a rotated lever arm changes height as it sweeps), or a
residual in the translation. **DO NOT DECIDE THAT UNTIL `T9` HAS BEEN WORN** — if
the orientation is wrong, everything hanging off it inherits the error, and
`185` `T9` warned that a pass there re-references `-HandAxis*` and `-GunOff*`.

**2. `[REPORTED]` *"this perspective makes my hand look like five feet off the
ground"*** and, separately, *"they look like they're my height but they're really
small... if I look down I feel like my face is on the floor."*
**THAT IS THE SCALE QUESTION AND IT HAS A PRE-REGISTERED FINDING — see `199`.**
Not this document, and not fixable by a hand transform.

---

## §4 — WHAT IS OWED

1. **`T9` — `-SeamCompose 1`, ITS OWN LAUNCH, NO BUILD.** Gate: hand held STILL,
   head turning — **the gun must not re-aim.** Then tilt: it must roll IN PLACE,
   not on an arc.
2. **EXPECTED CONSEQUENCE, NOT A SURPRISE** (`185` `T9`): if it passes,
   `-HandAxisX -1 -HandAxisZ -1` and `-GunOffY 8 -GunOffZ -2` were all tuned
   against a composition that no longer exists. **Re-check them AFTER, never
   during.**
3. **THEN re-judge §3.1's residual**, `G-196`, and `G-194`.
4. **THE SCALE / FOV READ — `199`.**

**NOTHING STAGED. THE COMMIT IS THE OWNER'S**, both repos.
