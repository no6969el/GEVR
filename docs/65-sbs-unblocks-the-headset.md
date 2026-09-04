# 65 — `-Sbs` unblocks the headset, B2 has a workaround, and B1 is the only blocker left

**2026-08-23, ~13:30-13:50. Six launches. Read `64` first — this continues it.**

---

## THE HEADLINE

**`.\vr.ps1 -Sbs` makes the headset work.** First working XR image since `36`.

**`-Sbs` sets `GE_VR_SBS=1`, which by design changes only the WINDOW.** It has
no business affecting the headset, and the fact that it does is the finding.

## THE 2x2, and it is not a single-launch result

Two variables, because the first attempt at this A/B changed both at once
(rule 5, caught after the fact):

| | watch the intro | skip the intro |
|---|---|---|
| **`-Sbs`** | **WORKS** | **WORKS** |
| **plain `.\vr.ps1`** | frozen at the first frame | black |

**`-Sbs` 2/2 working. Plain 2/2 broken. The intro is irrelevant in both
directions.** The intro-skip looked like a variable and is not one.

## MEASURED on the working build — B1 IS UNCHANGED

First disparity measurement ever taken on a live XR build:

```
PREDICTION: eye1 - eye0 = -0.3734 ndc = -124.7 px per 668-px half-frame
MEASURED:   0 px.   cross-correlation at dx=0 = 1.0000
            mean|L-R| = 0.001
```

**The two halves are pixel-identical.** `49`'s and `57`'s `-Flat` finding does
carry to XR: one image, both eyes.

Liveness at the same moment: **81.46% of pixels changed over 3 s**, mean 42.88,
max 245. Bright, correct, animating. B2 is absent in this configuration.

## WHY IT DOUBLES IN THE LENSES — and it is not a new bug

Reported worn: *"left side is distorted but shows and the right side shows as
well. because of the separation everything is duplicated."*

The SBS window's halves are **identical, 0 px apart**. The lenses show
duplication. That is `47`'s mirror table, second row:

| Mirror | Lenses | Means |
|---|---|---|
| **right** | **wrong** | **the images are right; the pose/FOV submitted with them is wrong** |

**Two identical images submitted with two different eye poses and FOVs cannot
fuse.** The brain is given zero disparity while the compositor applies opposite
per-eye warps, so everything doubles. **The doubling is what B1 looks like
through lenses**, and it is the same complaint as 3f-3's "the gun was visibly
two of them". It is not a separate fault and must not be given its own slice.

**Corollary: `00-START-HERE`'s "Also open: the viewmodel contradicts the docs"
section is explained.** The gun doubles because every object doubles, for this
reason. Close it.

## AND THE DISTORTION IS IN THE XR-ONLY PRESENT PASS

The window's two halves are identical, yet **one eye is distorted in the
headset.** So the distortion is introduced AFTER the eye render, in the XR-only
per-eye present pass — the same stage, and the same `25` failure mode, as the
menu's "zoomed in version of what's on the screen" (`64`).

Two faults, now separable:

| Fault | Where |
|---|---|
| One image in both eyes (B1) | at or before the eye render |
| One eye distorted / menus zoomed | the XR-only per-eye present pass |

## `-Sbs` IS A WORKAROUND, NOT A FIX — do not ship it as the answer

**Hypothesis, NOT established, and it must be read in source before anyone
believes it:** `GE_VR_SBS=1` makes the window path call `prepareEyeFromTarget`
on both eye targets, which calls `resolveTarget()` on each. Without it the
window path never touches the eye targets and only the eye block resolves them.
So `-Sbs` adds a second resolve, on the same present thread, in the same command
list, after the eye block wrote them.

**THAT HYPOTHESIS IS NOW WEAKENED AND PROBABLY WRONG — read the same session
it was written in.** `RenderTarget::resolveTarget` opens with:

```cpp
if (!resolvedTextureDirty || !usesResolve()) {
    return;
}
```

**MSAA is forced off under VR (`43`), so `usesResolve()` is false and
`resolveTarget` is a no-op.** The "second resolve" the hypothesis rests on does
not happen. Recorded rather than deleted, because the shape of the error matters:
a mechanism was proposed from a call site without reading the callee, which is
`58`'s lesson for the third time today.

**So what `-Sbs` actually changes is established, but WHY it fixes the headset
is NOT.** What is established, from `rt64_present_queue.cpp:502-610`:

- Without `-Sbs`, `sideBySide` is false, so `vrEyeZeroTarget` / `vrEyeOneTarget`
  are never even loaded, `eyeOneTarget` stays null, the whole SBS block is
  skipped, and the window draws `renderParams.texture` — the game's own target.
- With `-Sbs`, the window path additionally runs `prepareEyeFromTarget` and two
  `viRenderer->render()` calls sourced from the eye targets, with SHADER_READ
  barriers on each.

**The eye block runs BEFORE the window block in the same command list**, so the
window block cannot affect the headset in the same frame. Whatever the coupling
is, it is through state that persists across frames — `viRenderer`'s cached
descriptor sets, the eye targets' layouts, or the barriers. **None of that is
established and none of it should be written down as though it were.**

Supporting, from `64`: **`-ResScale 0.25` delayed the freeze from near-instant
to about eight seconds.** The freeze is load- and timing-dependent. That is a
race, and `-Sbs` is the shape of thing that hides one.

**Calling this a fix would be `49`'s "THE ROOT CAUSE" error for the third
time.** It is a workaround, it is genuinely useful, and the barrier is still
missing.

## What is now unblocked

**The headset is wearable again.** Everything gated behind "the headset shows
nothing" can proceed with `-Sbs` on the command line while the barrier is
found. That includes every stereo experiment, which has been impossible worn
since `36`.

## NEXT, in order

1. **Read the SBS block against the eye block in `rt64_present_queue.cpp`** and
   establish what `-Sbs` actually changes. Zero launches — `58`'s method, which
   has now killed hypotheses 8 and 12 for free.
2. **Confirm intermittency is not fooling us.** `-Sbs` is 2/2 and plain is 2/2,
   which is better than a single launch but is not many. Three more of each.
3. **Then B1, worn, with `-Sbs` on.** The `-Offset 500` and `-PresentEye`
   experiments from `57` and `58` have never been run in the headset, only in
   `-Flat`, and `64` established `-Flat` cannot reach the present stage.

**Do NOT** fix the unguarded `eyeZeroTarget` (measured not to fire), chase
brightness (explained in `64`), or give the doubling its own slice (it is B1).

## Corrections this document forces

1. **`-SkipEye` does not disable the eye split under XR** — `64`. It disables
   only the present-side eye render.
2. **`RenderTarget`'s address is `addressForName`, cosmetic** — hypothesis 12,
   falsified from source at zero cost, the second time this exact trap has been
   hit after `58`.
3. **The `-Sbs` entry in `00-START-HERE`'s environment-variable table** reads
   "both eyes side by side in the window", which is true and now dangerously
   incomplete. It also determines whether the headset works at all.
