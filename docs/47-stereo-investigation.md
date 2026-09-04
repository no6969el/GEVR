# 47 — the stereo investigation

> # ⚠ READ `49` FIRST. THIS DOCUMENT'S IMAGE FINDINGS ARE VOID.
>
> Every measurement below was taken on a build where **both eyes rendered the
> same image** — 0.14% of pixels differ across the seam, 0 px disparity at every
> depth. Two identical images cannot produce a geometric disparity, so:
>
> - **"44 px in the WRONG DIRECTION" is void.** There was no signal.
> - **"The residual is not explained" is void.** There was nothing to residualise.
> - **"`-SwapEyes` moves the fault to the other eye" needs a new explanation.**
> - **"One rendered image is wrong and the eyes are not symmetric" is the wrong
>   shape** — there was only ever one rendered image.
>
> The narrowest hypothesis this document ended on — log `viewOffset` for both
> eyes — was carried out and came back **clean**: a pure IPD translation, worst
> rotation term `0.000000`.
>
> **The METHOD in this document is still the best thing in the project**, and
> `49`'s `-Flat` + `PREDICTION:` gate is its direct descendant. Read it for the
> method. Do not trust its numbers.


**2026-08-23, end of session.** The eyes still do not fuse. This document is the
handover for that problem specifically: every measurement taken, every cause
eliminated, every wrong turn and why it was wrong, and where the next session
should start.

**Read this before touching the eye pipeline. It will save a day.**

---

## The single most important result

```
.\vr.ps1              -> the RIGHT eye is wrong
.\vr.ps1 -SwapEyes    -> the LEFT eye is wrong
```

**The fault moved with the content, not with the panel.**

That one observation eliminates an entire class of causes and nobody had run it
until the last hour of the session. It means:

| Eliminated | Because |
|---|---|
| Swapped eyes | Swapping makes it symmetric, not correct. It is not a swap |
| A bad swapchain, panel, or copy path | Those are fixed to a slot. The fault is not |
| Anything in the OpenXR submit for one eye | Same reasoning |

**What remains: one of the two RENDERED IMAGES is itself wrong, and the two eyes
are not being treated symmetrically somewhere in the render path.** The fault is
upstream of the swap point in `ge_vr_update_config`, which means RT64's per-eye
rendering or the `VrEyeParams` fed to it.

**Start there.** Not at the pose, not at the compositor, not at the runtime.

---

## The measurement method — use it, it is the only thing that worked

Every conclusion below came from measuring the Pimax mirror recording. Every
wrong conclusion this session came from reasoning about symptoms.

1. Record the Pimax mirror ("Pimax Mirror - Both") while playing.
2. Extract frames: `ffmpeg -i rec.mp4 -vf "select='eq(n\,60)'" -vsync 0 f%02d.jpg`
3. Split the frame in half and cross-correlate the two halves for the (dx, dy)
   that best aligns them.

**The mirror shows the submitted IMAGE and never the metadata.** That property is
what separated a render bug from a pose bug twice, and it is why "the mirror
looks fine but the lenses do not" is a *diagnosis*, not a complaint:

- Mirror wrong, lenses wrong -> the images are wrong.
- **Mirror right, lenses wrong -> the images are right and the POSE/FOV we submit
  alongside them is wrong.**

That distinction is worth more than any reasoning in this document.

## What the measurements say

Frame from the 21:51 recording, mirror half-width 668 px:

| Quantity | Value | Meaning |
|---|---|---|
| Vertical disparity | **0 px** | The eyes are perfectly aligned vertically. Rules out a whole family of fusion failures |
| Panel cant | **0.097 deg** | Parallel. `docs\09`'s assumption survives the runtime change. **Not the cause** |
| Frustum aspect vs target | 1.2974 vs 1.2979 | No stretch |
| `eye sep` | **6.32 units at 100 u/m = 63.2 mm** | The separation is correct against a measured 63.5 mm IPD |
| Horizontal disparity, distant content | **44 px further RIGHT in the right eye** | **WRONG SIGN** |

The predicted value, from the live tangents:

```
eye 0 tangents  -1.4869  1.0190     -> "straight ahead" lands at 396 px
eye 1 tangents  -1.0190  1.4869     -> "straight ahead" lands at 272 px
=> distant content should sit 125 px further LEFT in the right eye
```

Observed **+44** where **-125** was predicted. The sign is inverted, and **sign is
what prevents fusion** — eyes can converge and physically cannot diverge.
Magnitude only sets how much depth is perceived.

**The residual is not explained.** A pure swap predicts +125; the measurement is
+44. So there are plausibly *two* effects, and only one has been identified. The
next session should not assume a single fault.

---

## Confirmed working — do not re-investigate

| | Evidence |
|---|---|
| Both eyes render, into distinct targets | `eye0=90 eye1=90 distinctTargets=90`, sustained |
| Eye separation | 6.32 units at 100 u/m, vs 63.5 mm measured |
| Head tracking, world holds still | Worn and confirmed, `36` |
| Recentre | origin captured, corrected `y` near zero, crouch negative |
| Hip-fire aim decoupled from head | Worn, `36`. Aim mode is NOT — `36` correction |
| Vertical eye alignment | 0 px, measured |
| Panel cant | 0.097 deg, measured |
| Clean shutdown | All four lines, first time ever, `40`/`42` |
| Firing path reads `crosshair_angle` | `38`, code read, no aim-mode branch |

---

## The wrong turns, and why each was wrong

Kept in full. The pattern in them is worth more than the individual mistakes.

### 1. `GE_VR_EYE_SIGN` — a knob with no consumer

`30` removed the quantity it flipped and nobody removed the knob. `00-START-HERE`
step 4 told the reader to test the eye sign with it. It would have returned a
confident **false negative**. Caught by reading the source, not by running it.

### 2. MSAA — a documented rule that a menu can undo

`00-START-HERE` has said "MSAA must stay off" since Phase 1. The in-game graphics
menu **rewrites** `graphics.json`, and `config.cpp:28` makes `MSAA2X` the default
it writes. So opening the graphics menu silently destroyed stereo, and the file
left on disk looked like a deliberate choice.

**The right eye was not skewed. It was never rendered.** Two hypotheses were
tested against an eye that did not exist. `43` forces MSAA off under VR, because
a rule a menu can undo is not a rule.

### 3. The OpenXR runtime changed underneath the project

Every measurement up to `36` was made against **SteamVR/OpenXR 2.16.7**. The rig
is now on **Pimax OpenXR 0.1.0**, Crystal Super, **5838x4498** per eye rather
than 4140x3292. The line naming the runtime had been printed since `27` and
nobody read it, because nobody expected it to vary.

That single fact explained the "unexplained" FOV change and the origin mystery —
SteamVR's zero pose was the broken thing, vindicating the original `README` over
`00-START-HERE`.

**Check the runtime line and the resolution at the top of every session.**

### 4. The recentre, wrong twice, in opposite directions

This is the instructive one.

- **3f-5** recentred inside the *renderer*, leaving `ge_vr_xr.cpp` submitting the
  RAW pose as the projection layer's. Rendered from one viewpoint, described as
  another.
- **`45`** "fixed" it by submitting the *recentred* pose — **worse**.
  `XrCompositionLayerProjectionView::pose` is defined to be **in the layer's
  space**, and the layer's space was still raw `LOCAL`. That is not an
  inconsistency, it is a false statement about where the head was, and the
  compositor acted on it: view far right and sideways, one eye black.
- **`46`** stopped transforming poses at all and offset the reference space
  instead (`poseInReferenceSpace`), so the recentre is a property of the space
  everything already shares.

**The rule earned: when two things must agree, do not synchronise them. Remove
the second one.**

### 5. Three hypotheses tested against a broken instrument

`-NoRecentreYaw`, `-ForceEye 0` and `-NoHeadTranslate` were all run while MSAA
was on and the second eye was not rendering. **Those results are void** and were
briefly treated as evidence. `-ForceEye 0` and `-NoHeadTranslate` were re-run
after the fix and remain valid; `-NoRecentreYaw` has still not been validly
re-run.

---

## The honest summary of how this session went

Every correct conclusion came from a number the program printed or a measurement
taken from the mirror. **Every incorrect one came from reasoning about a
symptom** — and there were four, in a row, each plausible.

The project's own method already says this: *"when a crash cannot be reproduced
under a debugger, make the program describe its own failure rather than inferring
harder."* The generalisation this session paid for is that it applies to
**appearance**, not only to crashes. "The right eye looks skewed" is not data.
"Distant content is 44 px to the right when it should be 125 px to the left" is.

A second, sharper rule: **before testing a hypothesis, verify the instrument.**
One log line — `render passes: eye0=N eye1=N distinctTargets=N` — would have
invalidated three test results before they were acted on. It was in the log the
whole time.

---

## Recommendations, in the order I would take them

### 1. Find the asymmetry in the per-eye render path

The `-SwapEyes` result says one rendered image is wrong and the two eyes are not
symmetric somewhere. Candidates, cheapest first:

- **`VrEyeParams` as actually consumed by RT64.** Log every field of both eyes
  once per session and compare them term by term. The tangents are already
  logged and look correctly mirrored; **`viewOffset` is not logged at all.**
  Print all 16 floats of each eye's matrix. If eye 1's differs from eye 0's by
  anything other than the sign of the x translation, that is the bug.
- **`ProjectionProcessor`** in RT64 — how `overrideFrustum` builds the matrix
  from the tangents. An asymmetric frustum has an off-centre principal point;
  a symmetrised or wrongly-signed one produces exactly the measured error.
- **`fitAspectToGame`** is false, but confirm RT64 honours that per eye.

### 2. Make the mirror measurement a routine gate

It is the only diagnostic that has produced correct answers. It should be a
documented step, not a thing invented under pressure. Expected values are
computable from the live tangents, as above — so it is a **gate**, with a
predicted number, not an impression.

### 3. Re-run `-NoRecentreYaw` validly

Never tested with both eyes rendering.

### 4. Then, and only then, the deferred work

`39` has the full board. Nothing on it is judgeable through eyes that cannot
fuse, which is why fusion is the only blocker.

### 5. Do not chase these

- **Panel cant** — measured 0.097 deg.
- **Vertical alignment** — measured 0 px.
- **Eye separation** — measured correct.
- **The eye sign** — the knob's consumer was deleted; there was never anything
  there.
- **The intro stutter** — predates all VR work, clears on entering a level.

---

## Where the session ended

The build is committed and clean. The last change is `46`. The last observation
is the `-SwapEyes` symmetry, which is recorded here and nowhere else in code.

**The next person should start by logging `viewOffset` for both eyes and reading
the two matrices side by side.** That is a twenty-minute job and it tests the
narrowest remaining hypothesis directly.
