# 51 — one buffer, two eyes. PLAN, NOT BUILT

**2026-08-23, following `50`.**

**This is a plan. Nothing in it has been written to source.** Read it, then say
go — or run M1 first, which needs no code at all.

**Read `50`'s "AS BUILT" section before this.** `50` removed the eye-target
asymmetry and G1 still measured **0 px**. That fix was necessary; it was not
sufficient. Do not rebuild it.

---

## The defect

```
[gevr] upload eye0: ... hash=923A97CFF2BA0584 dst=00000287CE4E0950
[gevr] upload eye1: ... hash=6EB1F9B11DE4B344 dst=00000287CE4E0950
```

**Distinct data. One destination.** Both eye passes upload their own
`modViewProjTransforms` into the same
`workload.drawBuffers.viewProjTransformsBuffer` —
`rt64_projection_processor.cpp` 269, one `BufferPair` per **workload**
(`rt64_workload.h` 156), bound at `rt64_rsp_processor.cpp` 44.

The two eyes are not just sharing a destination on the GPU. They share the
**CPU-side source array too**: `ProjectionProcessor::process()` writes
`drawData.modViewProjTransforms` in place, per eye, into the one `DrawData` the
workload owns.

**Rule 8 applies exactly**: *when two things must agree, do not synchronise them
— remove the second one.* There should not be one buffer that two eyes take
turns owning.

## What `49` got right, and where it went wrong

`49`'s **wrong turn 4** was "a shared `viewProjTransformsBuffer` race". It was
written up, approved by the user, and falsified while implementing it, because
`threadRenderFrame` ends `execute(); wait();` — so no upload can race another.

**That reasoning is correct and it disproves the wrong claim.** "Race" and
"shared destination" are different defects: a race is about *timing*, this is
about *what the draws read*. Killing the first took the second down with it, and
the evidence — two hashes, one `dst` — was printed in the same log that was used
to rule it out.

**This is the third time in this project a knob or a buffer was cleared of
suspicion by an argument about mechanism rather than a measurement** (`25`'s eye
sign, `32`'s dead knob, now this). The response is M1, below: measure before
building, even though the fix looks obvious.

---

## M1 — the measurement that costs nothing. Run this FIRST

**No code. Current build. Two launches.**

```powershell
.\vr.ps1 -Flat
.\vr.ps1 -Flat -SwapEyes
```

`-SwapEyes` (`GE_VR_EYE=1`) swaps the two parameter sets wholesale, pose and
frustum together, so the pass that runs **last** carries the other eye's
frustum.

| Outcome | Means | Next |
|---|---|---|
| The single image **shifts by ~113 px** between the two runs | **Last writer wins.** The draws read whatever was uploaded most recently, so both eyes render the last eye's frustum | The fix below is right |
| The image **does not change at all** | The eye parameters are not reaching the draws by this route at all | The fix below is **wrong**, and the question moves to the descriptor set / RSP transform cache — a different slice |

**Both halves stay identical in either case.** M1 is not asking whether stereo
works; it is asking **which eye's image we are looking at twice.** That is the
question that decides the next slice, and no amount of reading the code settles
it — `49` spent a session proving that.

`47` observed *"`-SwapEyes` moves the fault to the other eye"* and `49` marked it
**"needs a new explanation"**. M1 is that explanation, made into a measurement.

---

## The fix, if M1 says last-writer-wins

**Give each eye its own transform storage, end to end.** Not a synchronisation,
not an ordering fix — a second buffer, so there is nothing to take turns over.

1. `rt64_workload.h` 156: `viewProjTransformsBuffer` becomes a per-eye pair,
   `viewProjTransformsBuffer[2]`, or a second `BufferPair` beside it. Under VR
   off, index 0 is the only one ever touched and the path does not change.
2. `rt64_projection_processor.cpp` 269: upload into
   `drawBuffers.viewProjTransformsBuffer[p.vrEye.eyeIndex]`.
3. The **CPU-side** array: `drawData.modViewProjTransforms` is written per eye
   into shared storage. Either give it a per-eye copy, or establish by
   measurement that it is fully consumed by the upload before the next eye
   writes it — **and if the second, say so in the doc rather than assuming it.**
   That assumption is what this whole document is about.
4. `rt64_rsp_processor.cpp` 44: bind the eye's buffer, not the workload's.

**Licence:** every file is in `lib/rt64/` — the MIT, upstreamable half. Nothing
OpenXR-shaped enters RT64.

## The gates — written before the code

**G1 is unchanged and still the one that matters**: `-Flat`, stand still,
capture, cross-correlate → **-113 px ± 5 in the far band, right eye further
LEFT**, against the log's `PREDICTION:` line. Tooling exists and is self-tested
in both directions (`50`).

**G2** — `-NoXr` unchanged. The path that must never break.

**G3** — the instrument, before the test: `eye targets: ... shared=0`,
`render passes: eyeN=N ... distinctTargets=N` all matching, **and a new
`upload eyeN: ... dst=` that differs between the eyes.** That last one is the
line this slice exists to change; if it still reads one address, nothing was
fixed and G1's result is meaningless either way.

**G4** — `-Flat -Offset 0` → disparity collapses to ~0; `-Flat -Offset 1.6` →
~56 px, half. **Not `-ForceEye`** — dead under `-Flat`, `39` O24.

**What would this build have to do differently for G1 to fail?** It would have to
put a different frustum's output in each half. Today's build, with `50` already
in it, measures 0.

---

## Risks

### Risk 1 — memory and lifetime

A second `BufferPair` per workload, doubled. Smaller than `50`'s target
doubling. Watch for `GetDeviceRemovedReason()` (`27`).

### Risk 2 — the CPU-side array may be the real sharing

Point 3 above. If `modViewProjTransforms` is the thing being overwritten before
it is consumed, duplicating only the GPU buffer moves the defect without fixing
it, and G1 would still measure 0 — **which is at least an honest failure**, since
G3's `dst` line would show two addresses while the image stayed one. That
combination is diagnostic, not confusing, and it is why G3 gets the new line.

### Risk 3 — the shared framebuffer pair is still there

`fb verdict` still reports 2 pairs with pair 1 redirected. `50` Risk 1 was never
resolved, only deprioritised, and it may yet be a second defect behind this one.
**Expect the possibility of another layer.** Two have been found so far.

### Risk 4 — this looks obvious, and so did the last one

`50` was also designed, gated, and confident. It was right about a real
asymmetry and wrong that it was the whole bug. **M1 exists so this slice does not
repeat that**, and the honest position until M1 runs is: *we have a strong
candidate and one measurement that would falsify it.*

---

## Predictions, written before the code

1. **M1 will show the image shifting**, i.e. last-writer-wins.
2. **The CPU-side array (Risk 2) will need duplicating too**, and doing only the
   GPU buffer will not be enough.
3. **`50` Risk 3's shared framebuffer pair will turn out to matter**, as a third
   layer, after this one.
4. G1 will still not pass on the first build of this slice.

---

# M1 RESULT — LAST WRITER WINS. Measured, 2026-08-23

**Run at the Runway start, same position both runs, no code changes.**

## The numbers

| Region | dx (A→B) | corr |
|---|---|---|
| tunnel mouth / distant cliffs | **+116 px** | 0.929 |
| far band (top quarter) | **+129 px** | 0.952 |
| near / gun bands | contaminated — see below | 0.17-0.44 |

**Predicted, if last-writer-wins: +113 px, rightward.** The displayed image's
`m20` goes from `+0.14106` (plain, eye 1's frustum) to `-0.14106` (swapped, eye 1
now carrying eye 0's), i.e. ndc.x from `-0.1411` to `+0.1411` = `+0.2821` ndc =
**+113 px rightward** on an 800-px half.

**Measured +116 to +129 px rightward, on well-correlated distant geometry.**

## The verdict — CORRECTED. M1 proves less than this doc first claimed

**The image changed. M1's other branch predicted 0 px.** The eye parameters DO
reach the draws, and the displayed image follows whichever eye pass ran **last**.

> **CORRECTION, made before building anything — `48` floor item 2.**
>
> This section first read *"`51`'s fix is aimed at the right defect."* **That
> does not follow, and it is the same error `49` made twice.**
>
> **Two mechanisms predict M1's result identically:**
>
> **(a) the shared `viewProjTransformsBuffer`** — one buffer, two eyes, last
> upload wins. `51`'s fix.
>
> **(b) the shared framebuffer pair 0** — `50` Risk 1, never resolved. If the
> **world** is drawn into the non-redirected pair, both passes draw it into one
> target and each eye's scratch target only ever receives a copy of it. The last
> pass's frustum wins, and `-SwapEyes` changes the image, exactly as measured.
>
> **M1 cannot tell (a) from (b), and the fix for one is a no-op for the other.**
> Building `51` on M1 alone would have been a coin flip dressed as a conclusion.
>
> `52` is the census that discriminates them. **Run it before building this.**

The log agrees, per run:

```
M1a plain:  proj EYE 0 m20=-0.14106   EYE 1 m20=+0.14106
M1b swap:   proj EYE 0 m20=+0.14106   EYE 1 m20=-0.14106   <-- exactly swapped
both runs:  upload eye0 ... dst=X     upload eye1 ... dst=X (same address)
```

## What this settles beyond the fix

**`47`'s "`-SwapEyes` moves the fault to the other eye"** — which `49` marked
**"needs a new explanation"** — now has one, and it is not about eyes being
swapped. `-SwapEyes` changes *which frustum the last pass carries*, and the last
pass owns the only buffer. The observation was real; the interpretation was not.

## Honesty about the margin

**+116/+129 measured against +113 predicted is not a clean hit**, and the doc
should not pretend it is. Two known contaminants, both visible in the frames:

1. **Game state differed between runs.** Both are the level start, but the
   weapon-draw animation was at a different point — B has the gun raised and the
   HUD up, A does not. That is why the near and gun/HUD bands correlate at 0.17
   to 0.44 and their numbers should be ignored.
2. **The HUD could not serve as the control it was meant to be**, for the same
   reason: 91% of its pixels differ between runs because it is mid-animation,
   not because anything moved.

**The binary M1 asked is answered well past any margin** — 116-129 is not 0 — but
**the exact magnitude is not confirmed to ±5 and must not be quoted as though it
were.** G1 after the fix is the measurement that has to hit 113 ± 5, from a
single frame with both halves in it, where no cross-run confound exists at all.

**Better M1 protocol if it is ever repeated:** pause the game, or capture after
the draw animation settles. A cross-run comparison inherits every difference
between the runs, which is exactly why `-Flat`'s single frame is the better
instrument and why G1 is the real gate.

---

# AS BUILT — G3 passes, G1 STILL 0 px

**2026-08-23. Built, linked, measured.**

## Gate results

| Gate | Result |
|---|---|
| G3 — `upload eyeN: dst=` differs | **PASS.** `eye0 dst=...E740`, `eye1 dst=...E770`. Two buffers. The edit took |
| G3 — targets, passes | **PASS.** `shared=0`, `eye0=92 eye1=92 distinctTargets=92` |
| G1 — stereo | **FAIL. 0 px.** Predicted -112.8 |
| G2 — `-NoXr` | Not re-run; every edit is behind `vrEye.enabled` / `vrEyeIndex == 1` |

## The 0.19% was a mouse cursor

The halves differed by 0.19% of pixels where the previous build differed by
0.00%, and for about a minute that looked like a signal. **It is the Windows
mouse pointer, caught inside one half of the client area by the screen capture.**
The difference map is 1388 pixels in an arrow shape at the top-left and nothing
anywhere else.

**Recorded because it was nearly believed.** A 0.19% change in the right
direction, on the build that was meant to fix it, is exactly the kind of number
that gets reported as "partial progress". The difference *map* killed it in
seconds where the difference *fraction* would have carried the session. **When a
number moves, look at where.**

## Scoring this plan's predictions

| # | Prediction | Outcome |
|---|---|---|
| 1 | M1 will show the image shifting | **RIGHT** — but M1 proved less than claimed; see the correction above |
| 2 | The CPU-side array will need duplicating too | **Not reached.** The GPU buffers are now distinct and nothing changed, so this is no longer the obvious next step |
| 3 | `50` Risk 3's shared framebuffer pair will matter | **WRONG.** `52` measured the world INTO the redirected pair |
| 4 | G1 will not pass on the first build of this slice | **RIGHT** |

## What is now eliminated, by measurement

**This is the value of the last three slices, and it is real even though none of
them fixed anything.**

| | Status |
|---|---|
| Eye render targets shared | **Eliminated** — `shared=0`, `50` |
| The world drawn into a shared framebuffer pair | **Eliminated** — `52` census |
| One transform buffer for both eyes | **Eliminated** — two `dst`, `51` |
| Per-eye matrices distinct and correct | Eliminated as a cause since `49` |
| Per-eye frustums, `viewOffset`, clip-w | Eliminated since `49` |
| Present sampling one texture | Eliminated — `present source` distinct |
| **Eye passes not serialised** | **Eliminated by reading**: `threadRenderFrame` ends `commandList->end(); waitForUploaders(); execute(); wait();` at line 852-855, per eye. `49` was right about this |

**Everything between the matrices and the presented pixels has now been checked
except one thing: whether the two eye passes actually RENDER different pixels.**
That has never been measured. Every instrument in this project measures inputs,
pointers and addresses — none of them looks at the output of a pass.

**That is the next slice, and it is a bisection rather than another candidate
fix.** `53`.
