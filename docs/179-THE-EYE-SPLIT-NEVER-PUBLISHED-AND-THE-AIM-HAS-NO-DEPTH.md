# 179 — THE SCREEN WORKS, THE EYE SPLIT NEVER PUBLISHED ONCE, AND THE WEARER DESCRIBED U-06 FROM THE HEADSET

**2026-08-26. `178`'s hoist worked. The run it enabled found something bigger.**

> ## **`screen (docs\175 U-19): READY` — `178` IS CONFIRMED.**
>
> ## **AND `RT64 published both eye images` NEVER PRINTED. NOT ONCE, IN 405 POSECHECKS.**
>
> **Every single `posecheck` line in the session reads
> `dupSrc=n/a (no eye source published yet)` — including in-game.** The headset
> was never shown a stereo frame at any point in the run.

---

## §1 — THIS IS NOT `178`'s DOING, AND IT IS NOT THE SCREEN'S

`178` adds **one line that builds two PSOs.** It cannot reach
`vrPresentEyeTexture`. What it did was make the flat path VISIBLE: before it, a
session with no eye split showed red/blue and read as "menus not done yet".
**Now it shows a working flat screen, so a total absence of stereo looks like a
feature rather than a fault.**

> **`175` §4 predicted exactly this and chose wrong.** It kept the red/blue clear
> as a fallback *"so that 'flat mode' and 'no image at all' never become
> ambiguous"*. **The pair it needed to keep unambiguous was not those two. It was
> "no eye split THIS frame, normal" versus "no eye split ALL SESSION, broken" —
> and the screen makes those identical.**

## §2 — WHERE IT STOPS

`rt64_present_queue.cpp:607` gates publication on
`(wantWidth > 0) && (wantHeight > 0) && (eyeOneTarget != nullptr)`.

- **`wantWidth` is fine.** The host logged `requested RT64 eye targets at
  5306x4090`, and `:407` reads that same value back.
- **So the null is `eyeOneTarget`** — `:409`, from
  `sharedResources->vrEyeOneTarget`, with `vrEyeZeroTarget` beside it (`50`).

**Those two are published by the projection processor — the split DETECTOR —
and `rt64_projection_processor.cpp` is one of the seventeen files modified and
uncommitted in this tree.** `175` also touched `rt64_present_queue.cpp`,
`rt64_workload_queue.cpp`, `rt64_framebuffer_renderer.cpp` and
`rt64_vr_eye.h`. **`175` HAS NEVER BEEN WORN BEFORE TODAY.**

**THE FIRST QUESTION IS NOT "WHY IS THE SPLIT WRONG" BUT "IS IT MINE":**
`git stash` the RT64 half and run. Stereo back -> `175` broke it and the file
list above is the search space. Still flat -> it predates `175` and the
uncommitted tree is exonerated.

## §3 — ►►►► EVERY AIM OBSERVATION FROM THIS RUN IS VOID ◄◄◄◄

**The wearer judged the aim while the headset was being fed a flat, head-locked
image.** `T3`'s baseline, and every test measured against it, requires stereo.

**AND `-NoAimFrustum` (`T5`) IS THE SAME CLASS OF FAULT ONE LAYER UP** — an aim
projected through a frustum nobody is looking through. Here nobody was looking
through ANY frustum. **`111`'s rule: a run that looks fine is not a run that
passed, and a run that shows a picture is not a run that showed the right one.**

## §4 — WHAT THE WEARER FOUND ANYWAY, AND IT IS U-06

Verbatim: *"it seems like the aiming is attached to the crosshair, and the
crosshair is moving on a two d plane... it must be like some sort of box within
the view that it hits accurately, but then outside of that box, it changes the
trajectory."*

**THE LOG SAYS THE SAME THING IN THE PROJECT'S OWN VOCABULARY:**

```
BULLET crosshair_angle=(160,120)px CLAMPED | GUNPOINT field_FFC=(160,120)px unclamped
WIDE-frustum scalex=12064 scaley=12064 [x1e6] screen=320x220 fovy=106 znear=2
```

**`320x220` IS THE BOX. `(160,120)` IS ITS CENTRE. `CLAMPED` IS THE EDGE.**
That is `172`/U-16 — the clamp split — described from inside the headset by
someone who had not read the document. **`T6` now has an independent prediction
to be tested against.**

**AND THE DEPTH INTUITION IS CORRECT AND IS ALREADY ON THE SHEET:**

| the wearer said | the sheet already says |
|---|---|
| *"there needs to be depth"* | **U-06** — PD's `vrComputeCrosshairParallax`: the crosshair converges on the TARGET's distance instead of projecting from a fixed plane |
| *"it has to know if it's hitting an object or not"* | **U-05** — aim at the laser dot's REAL hit point, which is a world-space trace |

> ### **AND `177` ALREADY CLEARED THE BLOCKER BOTH OF THEM WERE COSTED AGAINST.**
> **`camGetWorldToScreenMtxf()` IS PATCH-REACHABLE — `patches/externs.h:63`.**
> `160` §2/B1 and `163` §1 both assumed it was not, and neither checked.
> **PD's exact idiom — world point in, pixels out — is available to us directly.**

**SO THE ANSWER TO "DOES PERFECT DARK HAVE SOMETHING WE CAN TAKE" IS YES, AND IT
IS ALREADY COSTED, AND ITS DEPENDENCY IS ALREADY DISSOLVED.**

**IT STILL WAITS ON `T7`.** Near wall then far wall: **miss SHRINKS -> U-06 is
the cure. Miss HOLDS -> a constant angular error and U-06 fixes nothing.** The
wearer's report is consistent with BOTH and cannot separate them — **that is
precisely why `T7` exists.**

## §5 — THE SCREEN IS HEAD-LOCKED, AND THAT IS THE OTHER HALF OF THE NAUSEA

*"when you try to move your head it stayed perfectly still and stuttered."*

**Stayed still relative to the WEARER = locked to the head.** `175` builds the
ray from each eye's frustum tangents and hits a plane at `-dist` **in VIEW
space**, so the rectangle rides the head exactly. **Stereo is correct and the
world-anchoring is absent** — and `175` §3's "genuine depth and correct parallax"
is true for the eyes and false for the neck.

**A screen that cannot be looked away from is a screen you cannot look away
from.** The fix is to place the quad against the RECENTRED reference pose rather
than the live one, so the head turns and the screen stays.

**AND THE STUTTER IS THE SAME MISSING PIECE:** the flat frame arrives at the
game's cadence, not the headset's 90 Hz, so a head-locked quad has nothing to
reproject and every submission repeats the last one. **`97`'s timewarp is
exactly this machinery, it is now CREATED (`178`), and it is still gated OFF.**
