# 173 — THE HUD SHIFT REACHED THE WRONG PATH, THE SIGN WAS BACKWARDS, AND THE SEAM COMPOSITION IS WRONG.

**2026-08-25. Three findings, two fixes worn, one knob awaiting a test.**

> ## THE SESSION'S SHAPE, AND IT IS THE INSTRUMENT'S DOING
>
> `170` shipped the HUD shift and the wearer reported it **still split**. The
> instrument said `eye0=0.1867 eye1=-0.1867` — **computed, published, and
> differing** — which proved in one line that the value was correct and was **not
> reaching the pixels.** Without that line this would have been a sign hunt.

---

## 1. THE SIGN WAS BACKWARDS, AND THE FAILURE'S DIRECTION NAMED IT

`170` copied `projMatrix[2][0]` across unchanged. **The matrix entry's sign is
not the sign it produces in NDC.** Expand the row-vector projection with
`m23 = -1` (measured — the log prints `m23=-1.00000`), so `clip.w = -z`:

```
clip.x = x*(2/w) + z*(tanR+tanL)/w
x_ndc  = clip.x / (-z) = 2X/w - (tanR+tanL)/w        [ X = x/(-z) ]
```

**Check at the edges:** `X = tanLeft` gives `-1`, `X = tanRight` gives `+1`.
**So the constant term is NEGATIVE** — the perspective divide inverts the entry
before it reaches NDC.

> **AND THE WEARER'S DESCRIPTION WAS DIAGNOSTIC, NOT ANECDOTAL:**
> ***"its two objects one in each eye but its not merging in my eyes"*** — with
> the two crosshairs **DIVERGING**, left eye's to the left, right eye's to the
> right.
>
> **CONVERGENT would be a finite depth. PARALLEL is infinity. DIVERGENT is
> BEHIND infinity, which the eyes physically cannot fuse.** The direction of the
> failure named the sign before any algebra was done.

`GE_VR_HUD_SIGN` exists only so a wearer can refuse the derivation in one launch.

## 2. ►►►► AND IT STILL WAS NOT ENOUGH: THE HUD IS NOT ORTHOGRAPHIC. ◄◄◄◄

With the sign fixed the wearer reported **no change**. The instrument again said
the value was right. So the offset was reaching `VrEyeParams` and **not reaching
the crosshair.**

**`Projection::Type` has FIVE members, not two** (`rt64_projection.h:14`):

```
None, Perspective, Orthographic, Rectangle, Triangle
```

**GOLDENEYE'S HUD SPRITES ARE `Type::Rectangle`.** And rects carry **NO
PROJECTION MATRIX AT ALL** — `rt64_framebuffer_renderer.cpp` sends them straight
to `convertViewportRect()` as screen-space coordinates.

> **SO `170`'s EDIT TO `projMatrix[3][0]` WAS STRUCTURALLY INCAPABLE OF MOVING
> THE CROSSHAIR, AT ANY SIGN OR MAGNITUDE.** `170` §3's derivation of `[3][0]`
> was correct **for orthographic geometry that the HUD never was.**

**THE LESSON, AND IT IS THE SAME ONE AS `171` §3 IN A NEW COSTUME:** the fix was
placed by reasoning about what the HUD *ought* to be rather than by finding where
its pixels are actually produced. **`166` §1's diagnosis was right and `170`'s
implementation aimed at the wrong stage of the pipeline.**

## 3. THE FIX, WHERE THE HUD ACTUALLY BECOMES PIXELS

`FramebufferRenderer::DrawParams` gains `hudShiftPixels`, filled per eye in
`rt64_workload_queue.cpp` (where `vrEye` is already a parameter) and applied in
the `Type::Rectangle` case.

**TWO THINGS THAT WOULD HAVE BEEN WRONG:**

**FIXED POINT, NOT PIXELS.** `FixedRect` is `int32_t` and **10.2** —
`left()` is `(v + 3) >> 2` (`rt64_common.cpp:93`), so **one pixel is four units.**
Adding a float pixel count straight in lands at **a quarter** of the intended
shift, and truncates. **That is the dangerous class of error: it would have read
as "the sign is right but the magnitude is off" and invited tuning.**

**NOT APPLIED TO FULL-WIDTH RECTS.** `coversScissorWidth` is computed two lines
above and identifies the framebuffer blit, fades and letterboxing. **Shifting
those would slide the whole IMAGE sideways per eye** — far worse than the bug
being fixed. HUD sprites are exactly the complement of that test.

**WORN RESULT:** *"much closer now in my vision"*. The crosshair fuses.
**Residual: it biases toward the right eye — that is `174`.**

## 4. ►►►► THE SEAM COMPOSITION IS WRONG, AND THE WEARER FOUND IT ◄◄◄◄

***"if I turn my head left and right, the gun will change directions in my hand
automatically. And I think that's messing things up."***

`rt64_render_context.cpp` computed:

```c
R[i][j] = SUM_k Rhead[i][k] * Rhand[j][k]      //  R = Rhead * Rhand^T
```

**That is not "the hand expressed in the head's frame".** It is a different
composition, and it responds to HEAD rotation with a stationary hand — **turning
the head re-aims the drawn gun.**

**THE CORRECT VIEW-SPACE ORIENTATION IS `R = Rhead^T * Rhand`.**

> ## **AND THE AIM PATH HAS ALWAYS USED `Rhead^T`.**
> `g_geVrAimFwdHead` is built as `Rhead^T * fwdWorld`. **SO THE AIM AND THE
> PICTURE HAVE BEEN USING TWO DIFFERENT TRANSFORMS THE ENTIRE TIME.**

**That is exactly `166` §4's "the drawn gun is the liar" hypothesis, and the
head-turn report is the independent confirmation it was waiting for.** `158` §3
already proved `R` is a DRAWING matrix and not geometry; **this says why.**

**KNOB-GATED, DEFAULT LEGACY, DELIBERATELY.** `-HandAxisX`/`-HandAxisZ` (`155`)
and `-GunOffY`/`-GunOffZ` (`154`) were all tuned **against the old
composition**. Flipping the default would invalidate three measured results at
once and make the next run unreadable. **`-SeamCompose 1` settles it in one
launch.** `48` rule 5.

## 5. GATES — `-SeamCompose 1` IS UNTESTED

- **G-173-1** — the crosshair fuses into one object. **PASSED** (§3).
- **G-173-2** — **UNTESTED. Hold the hand STILL and turn the head. The gun must
  NOT re-aim.** If it stops, §4 is confirmed and `166` §4's 17 degrees has its
  cause.
- **G-173-3** — if `-SeamCompose 1` is right, **expect `-HandAxis*` and
  `-GunOff*` to need re-checking.** That is a good problem, not a regression.
