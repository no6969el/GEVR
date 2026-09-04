# 56 — skip a pass. Does a target's content come from its own render?

**2026-08-23. Built. One knob, one launch.**

---

## The measurement that forced this

```
[gevr] eyeDelta: dx=-1000.000 dy=0.000 dz=0.000 units | worst rot term 0.000000
```

`.\vr.ps1 -Flat -Offset 500` — a **1000-unit eye separation, ten metres** — and:

```
mean|L-R| = 0.001    pixels differing by >2 levels: 0.01%
far/sky +0   mid +0   near +0   gun/HUD +0     correlation 1.000
```

**Ten metres apart and not one pixel of difference.**

This closes an entire class of question permanently. **Nothing about signs,
scales, magnitudes, IPD, units-per-metre or subtle disparity can be relevant to
B1 any more.** The per-eye parameter does not differentiate the rendered output
at any magnitude. `16`'s scale derivation, `25`'s eye sign, the "too far apart"
report from `32` — none of them can be the blocker, and none should be revisited
until two different images exist.

## What is now impossible to reconcile

Every one of these is measured, and together they should be contradictory:

| | Measured |
|---|---|
| Per-eye matrices | Distinct, mirrored, `m20 = ∓0.14106` — `49` |
| Eye separation reaching the transform | `dx=-1000` units, sustained |
| Override coverage | `drawn=23 overridden=23 covered=23`, identical masks — `54` |
| Transform buffers | Two distinct `dst` — `51` |
| Render targets | Two distinct, `shared=0` — `50` |
| Passes serialised | `execute(); wait();` per eye, line 852-855 |
| Present sources | Two distinct textures |
| **Rendered pixels** | **Identical at a 10-metre separation** |

**A pipeline where all of the above hold cannot produce one image — unless a
target's content does not come from its own pass.**

## The test

```powershell
.\vr.ps1 -Flat -SkipEye 0
.\vr.ps1 -Flat -SkipEye 1
```

Skips that eye's `threadRenderFrame` **entirely** — no draws, no RSP, no
uploads for that eye. The target is still published, so present still samples it.

| Result | Means |
|---|---|
| **The corresponding half goes black, stale, or garbage** | The target's content DOES come from its own pass. Then two passes with a 10 m separation produced identical pixels, and the fault is inside a single pass's use of the transforms |
| **The half looks completely normal** | **The target is being filled by something other than its pass** — a copy, a resolve, or an alias keyed on the shared framebuffer address. Both `eyeColorTargets` are constructed with the SAME `interpolationTargetKey.address`, and that is the first thing to suspect |
| Both halves go black | The skip is too aggressive and took the shared path down with it. Inconclusive, not negative |

**Every branch names the next slice.** The second is the one that would explain
every measurement above at once.

## Why this is the right shape of test

The last four slices each asked *"is this input correct?"* and the answer was
always yes. This asks **"does the output depend on the pass at all?"** — a
question no instrument in this project has ever put.

**Removing a thing and checking whether the result changes** is the one form of
evidence that survives a wrong mental model, and after four wrong predictions the
mental model is the thing most in doubt.

---

## Prediction, written before the launch

**The half will look completely normal**, i.e. the target is filled by something
other than its own pass.

Fifth prediction. The previous four were all wrong, and this one is written down
for the same reason: so it is scored rather than believed. **If it is wrong
again, the mental model needs rebuilding from the render target lifecycle up,
not patching further.**

---

# RESULT — the target DOES come from its own pass. Prediction wrong

`.\vr.ps1 -Flat -SkipEye 0`: **left half black, right half normal.**

**Fifth wrong prediction in a row.** The copy/alias theory is dead: skipping a
pass leaves its target empty, so each target's content is produced by its own
render pass and nothing else fills it.

| Doc | Prediction | Outcome |
|---|---|---|
| `50` | G1 will pass at ~113 px | Wrong |
| `51` | The shared framebuffer pair will matter | Wrong |
| `52` | The world will be in the shared pair | Wrong |
| `54` | Coverage will be incomplete | Wrong |
| `56` | The skipped half will look normal | **Wrong** |

Five targeted predictions, five misses, each costing one launch. **The mental
model of this pipeline is wrong at a level that guessing will not reach.**

## A lead chased and killed in the same pass

**Hypothesis:** interpolation. `displayFrames > 1`, and the RSP blends previous
and current vertex data by `prevFrameWeight`/`curFrameWeight`. If the previous
transforms were never eye-overridden, a prev-dominated frame would render
un-eyed geometry in both eyes — which fits every measurement.

**Killed by reading the source, not by argument about it**
(`rt64_projection_processor.cpp` 155-230):

```cpp
viewMatrix       = hlslpp::mul(viewMatrix, eye.viewOffset);
prevViewTransform = hlslpp::mul(prevViewTransform, eye.viewOffset);   // line 165
...
prevProjTransform = projMatrix;                                        // line 227
```

**Both the previous view AND the previous projection carry the eye override.**
The interpolated path is eye-aware. Recorded so nobody spends a session on it.

## The test that needs no build — and should have been obvious when the knob was written

```powershell
.\vr.ps1 -Flat -Offset 500 -SkipEye 1     # LEFT half  = eye 0's pass, ALONE
.\vr.ps1 -Flat -Offset 500 -SkipEye 0     # RIGHT half = eye 1's pass, ALONE
```

**Only one pass runs in each.** Neither can contaminate the other, so comparing
eye-0-alone against eye-1-alone is a clean comparison of the two passes'
output — at a 1000-unit separation, where any per-eye response would be
enormous.

| Result | Means | Next |
|---|---|---|
| **The two halves DIFFER** | The passes DO render different geometry. Something after the passes collapses them — and the skip result says it is not a target copy. The target lifecycle is next | Instrument what happens to a target between end-of-pass and present |
| **The two halves are IDENTICAL** | Both passes render the same geometry from demonstrably different matrices. The break is between the transform buffer and the vertices — **the RSP compute stage, the only untouched link** | Instrument the RSP: does the compute read the bound buffer, and does the raster read the compute's output |

**Cross-run confound applies** (`51` M1 was contaminated by a weapon-draw
animation). Mitigation: both runs from the level start, standing still, captured
the same way. If the correlation is poor the runs are not comparable and the
comparison is void rather than weak.

## Prediction

**The two halves will be identical**, pointing at the RSP stage.

Sixth prediction, after five wrong. **Written to be scored, and if it misses the
next action is not another guess — it is rebuilding the model of this pipeline
from the vertex path up, with GPU readback rather than pointer logging.**

---

# CORRECTION, 2026-08-23 — the BLACK half was over-read

**`58` measured it.** A black half under `-SkipEye` was read here as *"the other
eye's pass does not write this eye's target"*. **It means only that the target
was NEVER WRITTEN** — the `target stamp` instrument reports `-1` for it, and with
no pass to write it, it stayed black. The run says nothing about what the other
pass does to a target that HAS been written.

Everything built on that reading is void. What replaces it: **eye 0's target
holds eye 0's correct image when eye 1's pass is absent, and eye 1's image when
it is present** — so eye 1's pass writes a texture it does not own. `58`.
