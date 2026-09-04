# Step 3e — plan: show both eyes, side by side

**2026-08-22.** 3d proved RT64 renders two eye images into two targets. Eye 1 is
discarded. 3e puts it on screen.

**This is the last gate that needs no headset**, and it catches nearly everything
3f would: whether the two images actually differ, whether they differ in the
right direction, and whether they fuse.

## Prior-art check

Nothing external applies — this is a debug view inside one renderer's present
path. Upstream RT64 has no stereo present, re-confirmed.

The relevant internal precedent is `xr_stereo.cpp`, already validated on this rig
(`10`). It is the *consumer* for 3f, not for 3e, but it settles a question 3e
must not get wrong: **the tint test is the only check that cannot be faked by
correct perspective.** `10` is emphatic, having been misled once by a monoscopic
image that fused, looked like a room, and survived head movement. Side-by-side on
a monitor is not that check — it shows two images and lets you compare them
directly, which is strictly better here because both are visible at once.

## Design

Four small pieces.

**1. `VIRenderer::RenderParams` gains viewport and scissor overrides.**
`VIRenderer::render` currently computes them itself from the swap chain via
`getViewportAndScissor`. Optional overrides, used only when non-null, leave every
existing caller byte-identical.

**2. `SharedQueueResources` gains `std::atomic<RenderTarget*> vrEyeOneTarget`.**
The render thread publishes the eye-1 target it just finished; the present thread
reads the pointer.

*Why a bare atomic pointer and not the vector.* `eyeColorTargets` lives on the
workload queue and is grown with `resize()`. Reading that vector from the present
thread while the render thread resizes it is a data race on the vector itself,
even though the `RenderTarget` objects do not move. One atomic pointer sidesteps
it entirely. Cleared on `reset()` so it cannot dangle.

**3. `VrConfiguration` gains `sideBySide`,** driven by `GE_VR_SBS=1`. Off by
default, so the normal present path is untouched.

**4. `PresentQueue::threadPresent` renders twice when enabled** — eye 0 into the
left half of the window, eye 1 into the right.

Each eye is squeezed into half the window width, so both are horizontally
compressed 2:1. That is what side-by-side always looks like and it does not
impede the comparison; the alternative, letterboxing each eye to preserve aspect,
wastes half the screen on black.

## What the frame skew means

Eye 1 is published once per game frame and read by the present thread whenever it
next presents. With interpolation running ~3 passes per displayed frame, the
right half may be up to one game frame older than the left.

**This is invisible for the comparison being made** — parallax between the eyes
is a spatial offset, not a temporal one, and a frame of lag does not create or
destroy it. It matters for 3f and not here. Stated so it is not later mistaken
for a stereo defect.

## Gate 3e

```powershell
$env:GE_VR_FRUSTUM="1" ; $env:GE_VR_SBS="1"
build\Release\GoldenRecomp.exe
```

| Check | Pass |
|---|---|
| `GE_VR_SBS=""` | Single image, exactly as 3d. The default path must be untouched |
| `GE_VR_SBS="1"` | Two images, side by side, both live and both animating |
| **The two images differ** | Left and right show visibly different viewpoints |
| **They differ the right way** | Near objects — the gun — shift more between halves than distant walls. That is parallax; a constant shift everywhere is not |
| Cross-eye fusion | Crossing your eyes to overlap the halves gives depth |
| `gevr.log` | Still `eye1 == eye0 == distinctTargets` |

**The parallax check is the one with teeth.** Two images that differ by a uniform
shift would mean the eye offset reached the view matrix but the per-eye
projection did not, or vice versa — and that fails while looking like success.
The gun is the instrument, as it was in 3b: it sits 30-40 cm from the eye and
moves far more than a wall ten metres out.

## After

3f — replace the present path with `xr_stereo.cpp`'s validated OpenXR submission.
Run `xr_stereo.exe tint` first to confirm the rig, per `10`.

---

# Implemented, 2026-08-22 — not yet built

| File | Change |
|---|---|
| `render/rt64_vi_renderer.h/.cpp` | optional `viewportOverride` / `scissorOverride` on `RenderParams` |
| `hle/rt64_shared_queue_resources.h` | `std::atomic<RenderTarget *> vrEyeOneTarget` |
| `hle/rt64_workload_queue.cpp` | publishes eye 1's target on pass 0; clears it on `reset()` |
| `render/rt64_vr_eye.h` | `VrConfiguration::sideBySide` |
| `hle/rt64_present_queue.cpp` | the two-viewport present |
| `src/main/rt64_render_context.cpp` | `GE_VR_SBS`, and the `GE_VR_EYE` fix below |

## A real bug found by writing 3e, which 3d's gate could not see

3b set both eye slots to the selected eye:

```c
config.eyes[1 - env.eye] = config.eyes[env.eye];   // "one eye per build for now"
```

Correct while only one eye was ever rendered. **Once 3d started rendering both,
it silently made eye 1 a duplicate of eye 0** — two render targets holding the
same image.

**3d's gate passed anyway, and was right to.** It counted *targets*, not
*content*: `eye1 == eye0` and `distinctTargets == eye1` were all true and all
meaningful. Two passes really did run into two distinct targets. Nothing about
that measurement was wrong; it simply did not measure the thing this bug broke.

Side-by-side would have rendered two identical halves, which reads as "stereo is
broken" and would have sent the search into the eye loop, the render targets, or
the projection processor — none of which had anything wrong with them.

`GE_VR_EYE` now **swaps** the two parameter sets instead of collapsing them. The
single-image path still presents slot 0, so `GE_VR_EYE` keeps its old meaning
there, while the two slots stay genuinely different.

**The lesson is about the gate, not the bug.** 3d's counters were a large
improvement on frame time and still had a blind spot exactly one layer up:
they proved the plumbing carried two things without proving the two things
differed. Every proxy has a boundary; the useful question is what a passing
measurement still permits.

## Note on the diff capture

The `.bak3a` baselines for `rt64_vi_renderer.*` and `rt64_present_queue.cpp` were
created *after* those files had been edited, which produced empty diffs. Caught
and repaired by inverting the known edits. `git diff` against the fork would be
the robust answer, but git on the mounted filesystem times out, so the hand-kept
baselines stay — with the ordering trap now recorded.

## Build and gate

```powershell
$env:PATH = "C:\Program Files\LLVM\bin;C:\Program Files\CMake\bin;C:\Users\<USER>\AppData\Local\Microsoft\WinGet\Links;" + $env:PATH
cd C:\Users\<USER>\Desktop\GoldenEye64Recomp
cmake --build build --target GoldenRecomp --config Release --parallel

$env:GE_VR_FRUSTUM="1" ; $env:GE_VR_SBS="1" ; $env:GE_VR_EYE=""
build\Release\GoldenRecomp.exe
```

Antialiasing still has to be off. `gevr.log` should open with
`frustum=1 ... sbs=1 (enabled=1)`.

The checks are in the gate table above. The one with teeth: **the gun should
shift between the halves far more than a distant wall.** Equal shift everywhere
is not parallax and means only one of the two per-eye transforms is landing.

## First run — the blit was wrong, not the render

Both halves drew, both were live, and both animated. But the right half showed a
**hugely magnified crop of roughly the top-left of the scene** — in one shot the
rocks and sky from the upper left, in another the railing and awning from a
building at the left edge, in a third an unrecognisable close-up of a pillar.

That reads instantly as "stereo is broken". It was not. The eye images were fine;
the code putting eye 1 on screen was not.

**Cause.** The first attempt treated eye 1 as "the same present with a different
texture" and only substituted the texture and its dimensions. The main path does
considerably more before it draws:

```cpp
renderParams.resolutionScale  = colorTarget->resolutionScale;
renderParams.downsamplingScale = 1;
if (colorTarget->downsampleMultiplier > 1) {
    colorTarget->downsampleTarget(...);        // <- produces the texture
    ... width / downsampleMultiplier ...
} else {
    colorTarget->resolveTarget(...);           // <- produces the texture
    ... width ...
}
```

Eye 1 got none of it: no `resolveTarget`, no downsample branch, and it inherited
the *main* target's `resolutionScale` and `downsamplingScale` while carrying its
own raw dimensions.

The VI shader maps `videoResolution` (the source region, computed from
resolutionScale and downsamplingScale) onto `textureResolution`. Give it a
mismatched pair and it samples a small corner of the texture and stretches it
across the viewport — a magnified crop anchored at the top-left, which is exactly
what appeared.

**Fix:** run eye 1 through the identical preparation, deriving every parameter
from the eye target rather than borrowing from the main one.

**Worth noting as a pattern.** This is the third time in this step's vicinity that
a failure has *looked* like broken stereo while being something one layer away —
after the collapsed eye config, and the frame-time gate that could not see the
work at all. The visible symptom of "the two eye images are wrong" is nearly
uninformative about which stage produced it, because every stage from the eye
matrices to the final blit fails the same way on screen.

## Second run — the blit is fixed, and the gate was under-specified

Both halves now show the same scene at the same zoom, both live, differing
subtly. The presentation bug is closed.

**But the parallax check could not have passed as instructed**, and that is a
fault in the instruction rather than in the build.

The run was `GE_VR_FRUSTUM=1` with **`GE_VR_TEST_OFFSET` unset**, so
`config.enabled` was true via the frustum alone and `viewOffset` stayed identity
for *both* eyes. The two eyes therefore shared a camera position and differed
only in their asymmetric frustums.

**Two frustums from one point produce a shift, not parallax.** Every object moves
by the same angular amount regardless of distance, because nothing about the
viewpoint changed. The gate asked for "the gun shifts more than the canyon walls",
which that configuration cannot produce no matter how correct the code is.

This is the same class of error as the frame-time gate in `24` and the
target-counting gate in this doc: **a check that a working build fails.** Three
times now, and the common thread is asserting the gate before the configuration
it depends on was pinned down. The gate table above should have named the
environment variables it assumed.

### The corrected parallax test

`16` gives 1 unit as about 1 cm, so the true half-IPD is 3.175 units. That is
honest but nearly invisible on a monitor — the same reason `15` used an
exaggerated value for 3b.

```powershell
$env:GE_VR_FRUSTUM="1" ; $env:GE_VR_SBS="1" ; $env:GE_VR_TEST_OFFSET="20"
```

20 units per eye is 40 cm of separation — absurd as an IPD, ideal for making
parallax unmistakable. Then the check has teeth: **the gun should shift between
the halves far more than the canyon walls**, because it sits 30-40 cm from the
eye while they are tens of metres away.

Follow it with `3.175` to see what the real thing looks like. Expect it to be
subtle, and expect the gun to still be the clearest indicator.

## Third run — parallax confirmed, and a sign error found

At `GE_VR_TEST_OFFSET=20` the canyon shot settles it:

| Feature | Distance | Shift between halves |
|---|---|---|
| Yellow kerb, bottom left | ~1 m | large, roughly 9% of the half width |
| Guard figure down the road | tens of m | none detectable |
| Distant peaks through the gap | far | none detectable |

**Near objects move, far objects do not. That is parallax, and 3e's gate passes.**
Two eye images, genuinely different, differing by depth-dependent displacement.

### The sign was backwards

The same measurement gives the direction, and it was wrong.

In the right-hand half, the near kerb is shifted **right**. A camera moved right
makes near objects shift *left*; a camera moved right by 40 cm cannot make them
shift right. So the half carrying the **right eye's frustum** had its camera
displaced **left**.

The code says the same thing independently. The composition is `p * V * E`, so
`E` acts in view space: `[3][0] = +d` adds `d` to every view-space x, sliding the
world right, which is the camera moving **left**. The original assignment gave
eye 1 `+offset`, so eye 1's camera went left while its tangents were the right
eye's.

**Position and frustum disagreeing is not cosmetic.** In a headset it inverts
depth — the world turns inside out, near reads as far — and it presents as
discomfort and eye strain rather than as an obviously broken picture, which is
the expensive kind of bug to carry into 3f.

Fixed: eye 0 now takes `+offset`, eye 1 `-offset`. `GE_VR_EYE_SIGN=-1` flips it
without a rebuild, because this is exactly the reasoning that is easy to get
backwards twice.

### Why the viewmodel does not move, and why that is expected

The gun sits at the same place in both halves at every offset. It is drawn in the
player's own space and rides the camera, so an eye displacement does not
separate it from the viewpoint.

**In a headset that is wrong** — a weapon a hand's length away should carry the
strongest parallax in the scene, and one pinned to the cyclopean viewpoint will
read as flat and painted-on. It is a Phase 3 item, alongside the decoupled aim
work, and is recorded here rather than fixed because the viewmodel's whole
treatment changes there anyway.

Note the irony: `15` made the gun the instrument for detecting a moving camera in
3b, and here the same gun is the one thing that does *not* move. Both are correct
— in 3b the whole camera moved, so the gun moved with it; here only the eye
offsets differ, and the gun rides the camera rather than the eye.

## Fourth run — sign flipped, and a note on the test value

Confirmed different after the sign fix. The wearer's observation was the useful
one: **"you can tell when going into doors you are on the side that would clip."**

That is the 20-unit test value, not a defect. 20 units per eye is 40 cm of
separation — a head two-thirds of a metre wide. In a doorway that puts an eye
through the frame, and near geometry lands between the eye and the scene. It was
chosen to make parallax unmissable on a monitor and it succeeded; it is absurd as
an IPD and its side effects are absurd to match.

At the real half-IPD of 3.175 units (`16`) the separation is 6.35 cm and the
effect should vanish entirely.

**The sign is not yet settled by observation.** The images differ, and the change
is consistent with the fix, but neither of us can reliably read displacement
direction off a screenshot of a dark corridor — and reading it off the wrong
feature is how the error got in. Two things point the same way (the kerb
measurement in run three, and the `p * V * E` derivation), which is enough to
proceed and not enough to close.

**The tint test in the headset closes it.** `10` is unambiguous that this is the
one check that cannot be faked, and it applies here in a form nothing on a
monitor can match: with left tinted red and right blue, a wearer knows
immediately which eye is which, and whether the world has depth or is inverted.
Carry `GE_VR_EYE_SIGN` into 3f for exactly that moment.

## 3e is complete

Two eye images, rendered from one display list into two targets, presented
together, differing by depth-dependent parallax in the intended direction.

**Phase 1 is done.** What remains is Phase 2: the OpenXR frame loop and present
path, where `xr_stereo.cpp` is already validated against this rig.
