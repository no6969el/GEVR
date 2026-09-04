# 50 — B1: symmetric per-eye targets. PLAN, NOT BUILT

**2026-08-23, session following `49`.**

**This is a plan. Nothing in it has been written to source.** `48`'s rule: a doc
written and executed in the same breath is a changelog. Read it, argue with the
risks section, then say go.

**Prerequisite reading: `49`.** It has the root cause and the measurements that
close every question this plan does *not* re-open. Do not re-investigate
`viewOffset` symmetry, the per-eye frustums, the clip-w convention, the upload
path, or whether the render responds to the eye matrices. All five are numbers.

---

## What is actually wrong, in one paragraph

Eye 1 gets a scratch render target. **Eye 0 does not.** At `frame == 0` the
interpolation path only assigns `overrideTarget` when `usingMSAA || (frame > 0)`,
and under VR `usingMSAA` is forced false (`43`), so eye 0's `eyeTarget` is
`nullptr` and its pass composites into the *shared default* target for
`interpolationTargetKey.address`. Eye 1 then runs, and — for the one framebuffer
pair that is **not** redirected — draws over it. Present then samples
`renderParams.texture` (the shared target) for the left half and
`vrEyeOneTarget` for the right. Both end up showing eye 1's world.

**The asymmetry is the bug.** The fix is to remove it, not to add a workaround.

Source, as it stands:

| Thing | File | Line |
|---|---|---|
| `eyeColorTargets` sized `displayFrames` | `lib/rt64/src/hle/rt64_workload_queue.cpp` | 1091-1096 |
| `if (eye > 0)` — the special case | same | 1160-1167 |
| `distinctTargets` counted only for `eye > 0` | same | 1174-1176 |
| `vrEyeOneTarget` published, `frame == 0` only | same | 1182-1184 |
| `vrEyeOneTarget` cleared on reset | same | 45 |
| declaration | `rt64_workload_queue.h` | 98 |
| `vrEyeOneTarget` declared | `rt64_shared_queue_resources.h` | 134 |
| XR present path, eye loop (`if (eye == 1)` at 395) | `rt64_present_queue.cpp` | 392-441 |
| SBS present path, left half uses `renderParams.texture` | same | 483-489 |
| the preparation comment that records the blit bug | same | 491-505 |

---

## The gates — written before the code, as `48` requires

### G1 — the stereo gate. **This is the one that matters**

```powershell
.\vr.ps1 -Flat
```

Stand still. Screenshot. Split at the seam (minimise `mean|L-R|` over candidate
widths, per `49`). Cross-correlate the halves per depth band.

**Pass: distant content sits 113 px ± 5 apart, right eye further LEFT.**

The log prints its own prediction first, so this is a number against a number:

```
[gevr] PREDICTION: eye1 - eye0 = -0.2821 ndc = -94.2 px per 668-px half-frame
```
scaled to an 800-px half → **-113 px**.

**What would this build have to do differently for G1 to fail?** It would have to
put a different image in each half. **Today's build measures 0 px and 0.14% of
pixels differing** — it fails G1 right now, which is what makes G1 a gate and not
a formality. No headset required.

### G2 — the regression gate

```powershell
.\vr.ps1 -NoXr
```

Normal 60/90 fps game, unchanged, closes cleanly. **The path that must never
break.** Every edit below is inside a `vrStereo` branch precisely so this one
cannot move.

### G3 — the instrument gate. Run it BEFORE trusting G1

`49`'s own line, and `48`'s rule 4: **verify the instrument before trusting the
test.**

```
[gevr] fb eye0: ... overrideSet=1 overrideFbPairIndex=1 ...
[gevr] fb eye1: ... overrideSet=1 overrideFbPairIndex=1 ...
[gevr] render passes: eye0=N eye1=N distinctTargets=N
```

**All three of `eye0`, `eye1`, `distinctTargets` must match** — and see
Risk 3: `distinctTargets` **changes meaning** under this fix and must be
re-derived in the same commit, or it becomes a lying instrument that reports
success by construction.

New line to add, so eye 0's target is observable rather than inferred:

```
[gevr] eye targets: eye0=0x... eye1=0x... shared=0/1
```

**`shared=1` after the fix means the fix did not take.** That line answers the
question this whole document exists for, and costs nothing.

### G4 — the falsification. Do not skip it

**NOT `-ForceEye`. It is a dead knob under `-Flat` — see the correction below.**

```powershell
.\vr.ps1 -Flat -Offset 0      # no eye separation at all
.\vr.ps1 -Flat -Offset 1.6    # half separation
```

`GE_VR_TEST_OFFSET` is the eye displacement itself, and under `-Flat` there is no
head tracking to override it — `49` already exercised it (`-Offset 50` vs `0`
moved 81% of pixels), so it is a knob with a *demonstrated* live consumer.

**Pass: `-Offset 0` → ~0 px. `-Offset 1.6` → ~56 px, half of G1's 113.**

This is better than a binary collapse: it is a **sweep against a predicted
number**, so it falsifies "the measurement responds to anything at all" as well
as "the measurement responds to the eyes". If G1 shows 113 px and `-Offset 0`
*also* shows 113, the measurement is not measuring the eye pipeline and **G1's
pass is void**.

A gate with no falsification beside it is an impression with a number stapled
to it.

#### Correction to `00-START-HERE`: `-ForceEye` does nothing under `-Flat`

Found while verifying this plan, before writing any code. `00`'s "Do this first"
step 4 offers `-ForceEye 0` as *"falsification: one eye to BOTH. Depth MUST
collapse."*

`g_forceEye` is read and applied **only in `src/main/ge_vr_xr.cpp`** (declared
242, applied 712, parsed 1131). `vr.ps1` sets `GE_VR_XR` only when `-not $Flat`
(line 85). **Under `-Flat`, `ge_vr_xr.cpp` never runs, so `GE_VR_XR_FORCE_EYE` is
read by nobody.** `vr.ps1` still prints `FORCE EYE 0 - depth MUST collapse`
(line 132-133) — it announces a knob that is not connected.

**This is rule 6's exact shape** — the `-Sign` failure of `32` in a new place,
and it would have returned a confident false negative on the most important gate
in this plan. It is corrected at its source in `00` (`48` floor item 2), not only
here. `-ForceEye` remains valid **with the XR path live**, i.e. without `-Flat`.

---

## The change

Five edits. Four are one concern, all inside `vrStereo`; the fifth is the launcher warning that O24 earned. **One change at a time** (`48`):
this is one change, and the teardown fix (O21) is a *separate* commit — see
Ordering.

### 1. Size the vector for both eyes

`rt64_workload_queue.cpp` 1091-1096. `displayFrames` → `displayFrames * 2`,
indexed `[frame * 2 + eye]`. The comment above it ("One scratch target per
display pass for the second eye. Eye 0 keeps whatever target it would have used
anyway") is about to be false and must be rewritten in the same edit — `48`'s
rule: correct a falsified claim **at its source**.

### 2. Delete the `if (eye > 0)` special case

`rt64_workload_queue.cpp` 1160-1167. Both eyes take a scratch target:

```
eyeTarget   = eyeColorTargets[frame * 2 + eye].get();
eyeModifier = 0x1000 + (frame * 2 + eye);
```

The `0x1000` base still clears the interpolated targets' `1..N`, and the two eyes
can no longer collide on a `RenderFramebufferKey`.

**Guard: only when `vrStereo`.** With VR off, `eyeCount == 1`, nothing allocates,
and eye 0 must keep taking `overrideTarget` exactly as today — that is G2.

### 3. Publish both

`rt64_shared_queue_resources.h` 134: add `vrEyeZeroTarget` beside
`vrEyeOneTarget`, same atomic-pointer rationale (the owning vector is `resize()`d
on the render thread; publishing the vector itself would be a race on the vector).

`rt64_workload_queue.cpp` 1182-1184: publish at `frame == 0`, both eyes.

`rt64_workload_queue.cpp` 45: clear **both** in `reset()`. `29`'s rule — the
published pointer is dropped *before* anything that owns targets goes away, never
after. A second pointer with only one of them cleared is exactly the dangling
this rule was written for.

### 4. Present samples the published target for **each** half

`rt64_present_queue.cpp`, **both** paths — the XR eye loop (392, where the
preparation sits behind `if (eye == 1)` at 395) and the SBS path (483). Today eye 0 reads `renderParams.texture` in both. It must read
`vrEyeZeroTarget`, and it must go through the **same preparation** eye 1 gets:
`downsampleTarget` / `resolveTarget`, the target's own `resolutionScale`,
`format`, and `downsamplingScale`.

**Extract that preparation into one lambda and call it per eye.** The comment at
`rt64_present_queue.cpp` 491-505 records what happens when eye 1's texture was
swapped in without its preparation: the VI shader maps `videoResolution` onto
`textureResolution`, samples a small corner and magnifies it, and it reads as
"stereo is broken" rather than "the blit is wrong". **Two copies of that
preparation is that bug waiting to happen a second time, in the other eye.** One
copy, two calls.

**Fallback:** if `vrEyeZeroTarget` is null, fall back to `renderParams.texture`
as today. A null there is the pre-VR path, not an error.

### 5. Make `vr.ps1` refuse to lie about `-ForceEye`

`vr.ps1` 132-133 prints `FORCE EYE 0 - depth MUST collapse` even under `-Flat`,
where nothing reads the variable. Warn instead, exactly as it already does for
`-Sign`. Four lines. It is the same class of defect this plan is fixing —
something announcing a state it is not in — and leaving it in place after finding
it would be the `47` mistake with the ink still wet.

---

## Risks — the things that would make this fix wrong

Each has a check. `49`'s lesson was five plausible mechanisms falsified in one
session, every one from reasoning instead of measuring.

### Risk 1 — pair 0 is still shared, and this fix does not change that

The workload has **2 framebuffer pairs**; `setOverride()` still redirects **one**.
This fix does not redirect pair 0; it makes both eyes composite into their own
targets so that eye 1 redrawing shared pair 0 no longer destroys the image eye 0
still needs. `49` argues this holds because the passes are fully serialised by
`execute(); wait();` per eye.

**That is an argument, not a measurement — flag it as such.** It is the same
shape as `25`'s eye sign, which was settled by argument and was wrong.

**It holds if** pair 0 is an intermediate that pair 1's pass samples, and eye 0's
composite has already consumed it before eye 1 runs.
**It fails if** pair 0 carries content that lands in the *final* image directly.

**Check, and it is cheap:** G1 partially passing — disparity present but a region
of the frame identical in both halves — is this risk realised, and it names pair
0 as the culprit rather than leaving it to be guessed at. If that happens, the
next slice is redirecting **every** pair, not one.

### Risk 2 — memory

`eyeColorTargets` doubles. At Crystal Super resolution these are large. Log the
allocation count and size once, and watch for a `GetDeviceRemovedReason()` line
(`27`'s diagnostic) rather than discovering it as somebody else's crash.

### Risk 3 — `distinctTargets` becomes a lying instrument

It is currently incremented only when `eye > 0 && eyeTarget != overrideTarget`.
After this change eye 0 also has a distinct target, so the counter as written
either stops meaning what it says or reports success by construction. **Re-derive
it in the same commit** — count "eye 0's target != eye 1's target" — or G3 passes
on a build where nothing improved. `32`: a knob whose consumer was deleted
returned a confident false negative; this is that shape, pointed the other way.

### Risk 4 — CLOSED before the code. `-ForceEye` is not connected under `-Flat`

Raised as a risk, checked, and **confirmed real** — see G4's correction. `g_forceEye`
lives entirely in the XR host, which `-Flat` does not start. G4 now uses
`-Offset`, whose consumer `49` demonstrated live.

**Cost of finding it here rather than after the build: about four minutes.** Cost
of finding it after: a falsification gate that passes on any build whatsoever,
and a "the fix works" claim resting on it.

### Risk 5 — this is `47`'s lesson, restated

**Do not put the headset on to judge this.** `-Flat` and a cross-correlation, or
it did not happen. Wearing it is what produced the void conclusions in `47`.

---

## Ordering

1. **This fix, alone**, to G1/G2/G3/G4. It is the blocker, and it needs no
   headset.
2. **Then O21, the teardown fix, as its own commit** — `WaitForSingleObject`'s
   result returned, retried in 500 ms slices to ~10 s, and a deliberate **leak
   rather than release** if the GPU has not drained, with `GPU DID NOT DRAIN`
   logged. Never print `gpu idle` unless it is. Do this before any long session.
3. **Only then** anything that requires wearing the headset. O2, O8 and O20 are
   all marked "not judgeable until B1" on the board and stay that way until G1
   passes.

**Not in this slice, deliberately:** O22 (`-ResScale` slower), O7 (60 fps —
read `DISPLAY PERIOD` first), O17 (`STEREO IS OFF` false-positives in menus).
Each is a separate change, and `48`'s "one change at a time" was paid for by
three `graphics.json` settings moved at once.

---

## Licence

Every edit here is in `lib/rt64/` — the **MIT, upstreamable** half. Nothing in
this plan is derived from a GPL source, and nothing OpenXR-shaped enters RT64:
its side stays "render the two eyes into offscreen targets of this size and
publish them". `PUBLISH-MANIFEST.md` has the split.

**No prior art was consulted for this slice**, and `48`'s trigger says so
correctly: there is a concrete measured bug in front of us with a designed fix.
Prior art is for designing, not debugging.

---

## Found while building the instruments, before the game was launched

Two corrections, both to the *measurement*, both caught by testing the analysis
script against synthetic images with a known disparity before pointing it at a
real one. `48` rule 4, applied to my own tooling: **verify the instrument before
trusting the test.**

### `49`'s seam-finder only works on a BROKEN build

`49` finds the seam by minimising `mean|L-R|` over candidate half-widths, and it
worked — **because the two halves were the same image.** With real stereo the
halves differ everywhere by construction, and that minimum no longer marks the
seam.

Measured, on a synthetic pair with a known **-113 px** disparity: the search
picked **956 instead of 960**, and the 4 px error landed straight on the answer
as **-117 px** — inside no tolerance that matters, and wrong in a way that looks
like a real result.

**A method that only works while the bug is present cannot be used to verify the
bug is gone.** The seam now comes from the client width, which
`tools_gevr_capture.ps1` guarantees by capturing the client area rather than the
window. The search survives behind `--find-seam` as a cross-check for a suspect
capture, never as the default.

**This would have produced a wrong number on a correct build.** It is the same
shape as O24, found the same way — by testing the thing that does the measuring.

### The disparity sign, stated once and verified

`dx > 0` = right half's content further RIGHT. `dx < 0` = further LEFT.
**G1 expects negative.** Verified against a synthetic pair built the other way
round first, which is how the convention got pinned down rather than assumed —
`25` settled a sign by argument and was wrong for two sessions.

### The tooling, as built

| | |
|---|---|
| `GoldenEye64Recomp\tools_gevr_capture.ps1` | Captures the CLIENT AREA to PNG + a tagged copy of `gevr.log`, and prints the G3 lines. Run per shot; `gevr.log` is rewritten every launch |
| `GoldenEyeVR\repo\tools\gevr_stereo.py` | Seam split, per-band cross-correlation, reads `PREDICTION:` from the log and scales it to the shot's half-width. Prints PASS/FAIL |

Self-test, both directions, run before either touched a real frame:

```
synthetic, working build (-113 known):  far -113  mid -60  near -25  gun -8   G1: PASS
synthetic, broken build  (identical):   far   +0  ... "THE TWO HALVES ARE THE SAME IMAGE"  G1: FAIL
```

---

## Score this plan afterwards

Append below what this document got wrong. That appended section is worth more
than the plan above it — `49`'s wrong-turns section is the most valuable thing in
this project's record.

**One is already scored: Risk 4 paid for the whole risks section before a line of
code was written.** It was raised as "confirm where this is applied", checked in
four minutes, and turned out to be a disconnected knob sitting under the most
important gate here. That is the argument for writing gates before code, made
once more.

Remaining predictions, written before the code:

1. **G1 will pass and produce a number close to but not exactly 113 px.**
2. **Risk 1 (pair 0) is the most likely partial failure**, and it will show as a
   region of the frame identical in both halves rather than as a total failure.
3. **Risk 3 will be the one that is skipped**, because updating an instrument
   feels like bookkeeping next to fixing the bug.
4. Present's eye-0 path (edit 4) will take longer than edits 1-3 combined.

---

# AS BUILT, AND WHAT IT GOT WRONG

**2026-08-23. Built, compiled clean in 63.9s, gates run. G1 FAILED.**

## Gate results

| Gate | Result |
|---|---|
| G2 regression, `-NoXr` | **PASS** — confirmed by the user |
| G3 instrument | **PASS.** `eye targets: eye0=...29F0 eye1=...2360 shared=0`, `render passes: eye0=90 eye1=90 distinctTargets=90` sustained |
| G1 stereo, `-Flat` | **FAIL. 0 px disparity, 0.00% of pixels differing.** Predicted -112.8 px for the 800-px half |
| G4 falsification | Not run — G1 failed, so there is nothing to falsify |

The frame was a real level (the Runway tunnel, outdoor sightline, gun visible),
not a menu. `1600x900` client area, 800-px halves.

## What the fix DID achieve

**All of it worked, and none of it was enough.** Both eyes now hold genuinely
distinct targets (`shared=0`, sustained `distinctTargets=90`), both are
published, and present samples a different texture per half (`present source:
eye0=...F800 eye1=...00C0`). The docs\49 asymmetry is gone.

**The two distinct targets hold identical pixels.** The defect moved upstream of
where docs\49 was looking.

## The line that was in the log the whole time

```
[gevr] upload eye0: overrides=23 count=24 hash=923A97CFF2BA0584 dst=00000287CE4E0950
[gevr] upload eye1: overrides=23 count=24 hash=6EB1F9B11DE4B344 dst=00000287CE4E0950
[gevr] upload verdict: distinct data, same destination, serialised passes.
       The upload is being recorded but not consumed.
```

**Distinct hashes. Identical destination.** Both eyes upload their own
`modViewProjTransforms` into the same `workload.drawBuffers.viewProjTransformsBuffer`
(`rt64_projection_processor.cpp` 269). One buffer, one workload, two eye passes.

**docs\49 wrong turn 4 was this hypothesis.** It was written up, approved, and
falsified while implementing it, on the grounds that `threadRenderFrame` ends
`execute(); wait();` so no upload can *race*. That disproved a **race** and threw
out **shared destination** with it — they are not the same defect. A race is a
timing question; this is a question of what the draws read. `51` has it.

## Scoring this plan's predictions — three of four wrong

Written before the code, scored after. Kept verbatim because the pattern is the
point.

| # | Prediction | Outcome |
|---|---|---|
| 1 | "G1 will pass and produce a number close to but not exactly 113 px" | **WRONG.** G1 failed at 0 px. The fix was necessary and not sufficient |
| 2 | "Risk 1 (pair 0) is the most likely partial failure, showing as a region identical in both halves" | **WRONG in shape.** Total failure, not partial — and the shared pair may not be implicated at all |
| 3 | "Risk 3 will be the one that is skipped" | **WRONG.** `distinctTargets` was re-derived, and it is the reason G3 is trustworthy rather than true by construction |
| 4 | "Present's eye-0 path will take longer than edits 1-3 combined" | Roughly right |

**The honest summary: this plan correctly identified an asymmetry, fixed it, and
that asymmetry was not the whole bug.** docs\49 called it "THE ROOT CAUSE" on the
strength of one measurement; it was *a* root cause. The claim is corrected at its
source in `49` and `39`.

**What earned its place:** G3. Without `eye targets: shared=0` and the re-derived
`distinctTargets`, this failure would look identical to the one before it, and
the next session would have rebuilt the same fix.
