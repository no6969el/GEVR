# 205 — THE CALIBRATION PHASE. A STANDING DOCUMENT, OPENED DELIBERATELY EMPTY.

**Opened 2026-08-25 at the owner's request:** *"I think we need some sort of
calibration phase because if other people use this of different sizes, won't it
be weird? We should make a document that states that so we can come back to it
and fill it with information."*

> ## **THIS IS A STANDING FILE LIKE `169`. APPEND TO IT; DO NOT REWRITE IT.**
> **It is opened BEFORE the work so that findings land somewhere on the day they
> are made** — `108` is the record of what happens when a session ends without a
> home for what it learned. **Sections marked `[TO FILL]` are deliberate.**

---

## §1 — THE PROBLEM, IN ONE LINE

**GoldenEye's proportions are fixed by 1997 art. The player's are not.**
Bond's eye height, arm length and grip position are constants in the ROM; the
wearer's are whatever the wearer is. **Nothing in this project currently maps one
onto the other.**

**`[REPORTED]`, and it is what opened this file:** *"the arm length is about one
Bond hands length too far"*, *"the arm in the game is about 3 inches higher than
my real life arm."* **Those are proportion mismatches being corrected by hand,
one knob at a time, for one person.**

---

## §2 — WHAT WE HAVE TODAY, AND WHAT IT IS NOT

**`[MEASURED]` from `199`'s recorder: head `y = +0.016 m`, hand `y = -0.417 m`.**
**The runtime hands us a HEAD-CENTRED space, not a floor-based one** — so we are
NOT accidentally stacking the wearer's standing height onto Bond's eye height,
and the relative geometry (hand 42 cm below head) is preserved correctly.
**That is worth recording because it eliminates the most common version of this
bug before anyone goes looking for it.**

**WHAT EXISTS:**
- `200`: position = the raw play-space hand, scaled. **Correct, and proportion-blind.**
- `-WorldUnitsPerMetre` / `-HandUnitsPerMetre` (`156`): a global scale. **And they
  must MOVE TOGETHER — `205` §4.**
- `-GunOffX/Y/Z` (`154`): PD's PISTOL grip constants. **Someone else's hand.**
- `176`'s crouch calibration: *"stand still for the first ~90 frames."*
  **THE ONLY CALIBRATION IN THE PROJECT, and it is for one feature.**

**WHAT DOES NOT EXIST:** any measurement of the WEARER. No height, no reach, no
comfortable ready position. **Every number above is a constant chosen by someone
else and then nudged.**

---

## §3 — WHAT A CALIBRATION PHASE WOULD CAPTURE `[TO FILL]`

A first sketch, to be argued with rather than implemented as written:

| quantity | how | what it would fix |
|---|---|---|
| **standing eye height** | stand naturally, hold still | maps the wearer's eye onto Bond's, instead of assuming |
| **comfortable ready position** | hold the gun where it feels natural | **replaces `154`'s PISTOL grip constants with THIS wearer's** |
| **full extension** | arm out straight | the *"one Bond hand too far"* error, derived rather than dialled |
| **floor** | point at the floor, or take it from STAGE space | crouch, and any future leaning |

**THE OUTPUT IS NOT A KNOB. IT IS A SET OF DERIVED OFFSETS**, and the standing
command should get SHORTER when this lands, not longer — `204` is the precedent:
five terms went from launch arguments into defaults once they were understood.

---

## §4 — THE ONE RULE ALREADY LEARNED, AND IT WAS LEARNED THE HARD WAY

> **`-WorldUnitsPerMetre` AND `-HandUnitsPerMetre` MUST BE EQUAL.**
>
> `156` split them because one is a MEASUREMENT and one is a PERCEPTION, which
> was right. **But the ratio between them is an ARM-LENGTH MULTIPLIER that nobody
> intended.** `[REPORTED]` at world 50 / hand 100: *"when I move my arm one way
> or another it seems to orbit a larger area than my body"* — **exactly 2x, and
> for exactly that reason.**
>
> **A calibration phase must set them together or the wearer's arm stops being
> the wearer's arm.**

---

## §5 — OPEN QUESTIONS `[TO FILL]`

1. **Does Bond's arm length even exist as a number?** `171` found the MUZZLE node
   in the model (`Switches[3]`); **is there an equivalent for the grip or the
   shoulder?** A read, not a launch, and `168` §5's grep comes first.
2. **What happens to a player much shorter or taller than Bond?** Scale the world
   to them, or move the camera? **These give different answers and the difference
   is the whole design.**
3. **Where is calibration stored?** Per-machine, or per-profile.
4. **How is it re-run?** A menu item, a launch flag, or automatic on first start.
5. **Does U-11 (the IK arm) depend on this, or the other way round?**
   `196` §5: *"the anchor is the bug, not the absence of an arm"* — **and an arm
   built on uncalibrated proportions would be wrong for everyone but one person.**

---

## §6 — STATUS

**OPEN. NOTHING BUILT.** `169` **U-24** points here.
**NOT ON THE CRITICAL PATH TODAY** — the owner's stated focus is the world's
perspective (`206`) and then `B1`. **This file exists so the finding is not lost
when it is finally picked up.**
