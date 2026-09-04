# 174 — THE AIM WAS ANCHORED AT THE LEFT EYE.

**2026-08-25. BUILT, UNWORN. The residual `173` §3 left behind.**

> ## THE WEARER, AFTER THE CROSSHAIR FINALLY FUSED
>
> ***"I'm much closer now in my vision, and it seems to aim off the right eye."***
>
> **A RAY ANCHORED AT ONE EYE IS EXACTLY WHAT THAT READS LIKE: correct from one
> eye, offset from the other, and never correct from the middle.**

---

## 1. THE FINDING

`HeadView::position[2][3]` and `orientation[2][4]` are **PER EYE**
(`ge_vr_host.h:71` — *"Per eye, from xrLocateViews"*).

**So `head.position[0]` is the LEFT EYE, not the head centre.** And it is what
every one of these was measured from:

- the hand's position relative to the head (`rt64_render_context.cpp`, both sites)
- therefore the muzzle
- therefore the whole aim ray

**MEANWHILE `167`'s aim frustum and `170`/`173`'s HUD shift are both CYCLOPEAN**,
computed as the average of the two eyes.

> ## **THE GEOMETRY WAS ANCHORED AT ONE EYE WHILE THE PICTURE WAS CENTRED BETWEEN
> ## BOTH.** A constant lateral bias of **HALF THE IPD** — about **32 mm**, which
> at 100 units/metre is **~3.2 game units**.

## 2. THE FIX

`ge_vr_head_origin()` returns the **midpoint of the two eye positions**.
`GE_VR_HEAD_ANCHOR 0` restores the left-eye anchor for comparison; default is the
centre.

**ORIENTATION IS LEFT ALONE, DELIBERATELY.** `head.orientation[0]` is also the
left eye's, but on this headset the panel cant is expressed in the **FRUSTUM**
(the mirrored asymmetric tangents, `166` §1) rather than in the pose, so the two
eye orientations are effectively parallel and the error is a **translation, not a
rotation.** **If `-SeamCompose 1` (`173` §4) changes that reading, this is the
next thing to re-examine.**

## 3. THE RESIDUAL, AND THE WEARER DREW IT

The shot lands in the crosshair's **top-right quadrant, on the circle, close to
the vertical arm** — a drawing was supplied and it is unambiguous:

**≈ 6-7 px UP and ≈ 1 px RIGHT** in the game's 320x220 frame, i.e. **~0.06 NDC,
predominantly VERTICAL.**

**A LATERAL half-IPD anchor error does not explain a VERTICAL offset.** So §2 is
necessary and **not sufficient**, and this document does not claim otherwise.

## 4. ►►►► THE TEST THAT DISCRIMINATES, AND IT COSTS ONE WALL ◄◄◄◄

Two candidates remain and **they behave OPPOSITELY with distance:**

| cause | signature |
|---|---|
| **MUZZLE PARALLAX** — the crosshair projects the barrel direction from the HEAD, the bullet leaves from the MUZZLE. Two parallel rays, separated by `(muzzle - head)`. | **The miss SHRINKS with distance** and vanishes at range |
| **A CONSTANT ANGULAR ERROR** in the ray | **The miss STAYS THE SAME SIZE** at every distance |

**SHOOT A WALL AT ARM'S LENGTH, THEN THE SAME SPOT FROM ACROSS THE ROOM.**

**If it shrinks, it is parallax and `169` U-06 is the principled cure** (PD's
`vrComputeCrosshairParallax`, `166` §8). **If it holds, it is angular and the
ray itself is still wrong.**

## 5. THE TRIM IS A MEASUREMENT INSTRUMENT, NOT A KNOB

`-AimTrimX` / `-AimTrimY`, in NDC, default 0.

**Dial until the shot sits ON the crosshair, then REPORT THE VALUE.** That
converts *"it is a bit off"* into a number to three decimals, from which the
physical quantity can be worked out.

> **IT IS EXPECTED TO BE DELETED.** `163` deleted five knobs by finding the
> projection. **This one exists to FIND the next cause, not to live alongside
> one** — and recording that intent here is what stops it quietly becoming
> permanent, which is how `-AimGain` survived as long as it did.

## 6. GATES

- **G-174-1** — the aim no longer favours one eye. Close each eye in turn: the
  crosshair should be equally right (or equally wrong) from both.
- **G-174-2** — `-HeadAnchor 0` reproduces the one-eye bias, from the same build.
- **G-174-3** — **the distance test in §4 is ANSWERED**, either way. That answer
  is worth more than the fix in §2.
