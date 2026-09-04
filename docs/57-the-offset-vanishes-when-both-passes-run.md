# 57 — the offset VANISHES when both passes run

**2026-08-23, ~01:50. The sharpest measurement this project has produced.**

---

## The three frames

All at `-Offset 500` (a 1000-unit eye separation), all at the Runway start,
all at ammo `7|93` — **same game state, so the runs are comparable.**

| Frame | What it shows |
|---|---|
| `-SkipEye 1` → eye 0's pass ALONE | World seen from far off to the side, floating over the canyon. **Massively displaced** |
| `-SkipEye 0` → eye 1's pass ALONE | Same, displaced the other way. **Massively displaced** |
| **Both passes** | **The runway, close and normally framed — as if the offset were ZERO** |

Measured, downsampled halves:

```
both.LEFT vs eye0-alone     mean|diff|=11.44   51.4% of pixels differ
both.LEFT vs eye1-alone     mean|diff|= 9.68   41.2% of pixels differ
eye0-alone vs eye1-alone    mean|diff|= 5.02   29.4% of pixels differ
```

## The finding

**The both-passes image is not eye 0's render and not eye 1's render.** It
differs from each single-eye frame *more* than the two single-eye frames differ
from each other.

**Each pass, run alone, applies its eye offset in full. Run together, the offset
effectively disappears** — the picture reverts to something close to an
un-offset view, in *both* halves.

This is not "one eye's image in both halves", which is what `49`, `50`, `51` and
`56` were all built around. **It is a third image that neither pass produces on
its own.** `56` named this outcome in advance as the branch meaning *"the model
of this pipeline is wrong in a way I cannot yet name."* It is that branch.

## Why every previous slice failed

Every fix so far targeted *separation* — separate targets (`50`), separate
transform buffers (`51`), the right framebuffer pair (`52`), coverage (`54`).
**All of them were correct, all of them are still in, and none could have
worked**, because the two passes are not competing for a resource. Something is
**combining** them.

And it explains the one thing that never made sense: a 1000-unit separation
producing zero disparity. **The average of −500 and +500 is 0.**

## The hypothesis for tomorrow — and its test

**Frame interpolation blends across the eye passes.**

`ProjectionProcessor::processScene` interpolates the view against the *previous
frame's* matching workload:

```cpp
viewMatrix        = rigidBody->lerp(p.curFrameWeight,  *prevViewMatrix, curViewTransform, true);
prevViewTransform = rigidBody->lerp(p.prevFrameWeight, *prevViewMatrix, curViewTransform, true);
projMatrix        = lerpMatrix(adjustedPrevProj, curProjTransform, p.curFrameWeight);
```

`GameFrameMap` maps the current workload to a previous one. **With two eye passes
per frame, the pass that ran most recently is the OTHER EYE's** — so the lerp may
be blending eye 0's view against eye 1's, converging both to the midpoint. Run
one eye alone and every "previous" pass is the same eye, so nothing cancels.

**This fits every measurement**: the vanishing offset, the identical halves, the
full displacement when alone, and the irrelevance of targets and buffers.

**Stated as a hypothesis, not a finding. Six predictions in this project have now
been wrong.**

### The test — no code

Interpolation is what supplies the previous-frame data. Turn it off:

`%LOCALAPPDATA%\GoldenRecomp\graphics.json` → `rr_option: "Original"`
(currently `"Manual"` / `rr_manual_value: 90`).

That should give `displayFrames == 1` and no previous-frame interpolation.

| Result | Means |
|---|---|
| **Stereo appears** — the halves differ, disparity near the predicted value | The interpolation path is the mechanism. The slice is to make the frame map eye-aware, or to exclude the eye offset from the lerp |
| **Halves still identical** | The hypothesis is dead and the cancellation is elsewhere. Next: log the final `viewMatrix` per pass AFTER the lerp, which is the one value never printed |

**One change at a time** (`48` rule 5, paid for by three `graphics.json` settings
moved at once): change **only** `rr_option`, and put it back afterwards.
`graphics.json.bak-preVR` exists. The in-game menu rewrites this file, so
re-check it after any menu visit.

## Also true, and unrelated to the above

**Six kernel bugchecks in ten hours**, all `0x139 (0x3)` — LIST_ENTRY corruption:

```
8/22 3:03 PM · 6:58 PM · 8:15 PM · 8:41 PM · 11:48 PM · 8/23 1:24 AM
```

Identical signature every time. Consistent with `49`'s finding that this rig's
BIOS lost its memory settings and needed a DIMM pulled — i.e. memory/EXPO
instability, not this project. **`-Flat` never sets `GE_VR_XR`, so the O21
teardown defect cannot be the mechanism** (the `49` wrong-turn-5 argument, still
valid). Recommendation: JEDEC memory speeds, then re-test.

**A real gap this exposed:** the `[gevr-crash]` unhandled-exception filter and
every `shutdown:` line are gated behind `GE_VR_XR`. **`-Flat` became the primary
test harness in `49` and inherited none of the crash diagnostics.** Worth fixing
before the next long session.

## Instruments added tonight

| Line | Answers |
|---|---|
| `eye targets: eye0=.. eye1=.. shared=` | Are the two eyes' targets distinct? |
| `idx coverage: drawn/overridden/covered` + masks | Does the override land on indices the draws use? |
| `fb census: N pairs, redirected pair = N` + per-pair perspective/ortho counts | Where is the world, and is it redirected? |
| `pass targets: eye0=.. set=N \| eye1=.. set=N \| perspectiveInWorkload=N` | What did each pass render into, in the WORLD workload — re-logged on change, so a menu cannot own the answer |
| `-SkipEye 0\|1` | Run one pass alone. **The knob that produced this document** |
| `-PresentEye 0\|1` | Force both halves to one eye's target |
| `tools_gevr_capture.ps1`, `tools/gevr_stereo.py` | Client-area capture + tagged log; seam split, per-band correlation, self-tested both directions |

## Known instrument defects, not yet fixed

- **`render passes: eye0=N eye1=N` over-reports under `-SkipEye`** — the counter
  increments before the skip. The `SKIPPING eye N` line is the true one.
- **The `fb eye` probe still one-shots on the first workload (a MENU)** — O28.
  `pass targets:` supersedes it; the old line should be deleted or given the same
  change-detection, not left to mislead.

---

# INTERPOLATION HYPOTHESIS — DEAD. Measured, 01:47

`graphics.json` `rr_option: "Manual"` → `"Original"`, one key, backed up to
`graphics.json.bak-pre57`. Relaunched `-Flat -Offset 500`.

**Interpolation is genuinely off:**

```
[gevr] 60.0 fps | render passes: eye0=60 eye1=60 distinctTargets=60
```

60 passes per second instead of 90 — `displayFrames == 1`, no interpolated
frames generated.

**Result:**

```
mean|L-R| = 0.001    pixels differing >2 levels: 0.01%
far band best shift: 0 px, correlation 1.000
```

**Still identical. Seventh wrong prediction.**

## What this eliminates, and it is more than it looks

With `rr_option: "Original"`, `requiresFrameMatching` is false, so
`curFrame.match()` is never called, `workloadMap.mapped` is false, and
`processScene`'s entire interpolation branch is skipped — `prevViewTransform`
and `prevProjTransform` fall through to lines 137-138 instead.

**So the cancellation is not the lerp, not the frame map, not the previous-frame
data, and not interpolation in any form.** That whole subsystem is out.

`57`'s stated fallback applies: **log the final `viewMatrix` per pass AFTER
everything has touched it.** It is the one value this project has never printed —
every projection log so far reports `projMatrix` terms, never the view matrix
that carries the eye offset.

## The sharper question, being measured now

The claim "the offset vanishes" rests on the both-pass image *looking*
un-offset. **That is an appearance, and rule 3 says measure it.**

`-Flat -Offset 0` against `-Flat -Offset 500`, identical settings otherwise:

| Result | Means |
|---|---|
| **Identical** | The eye offset does **nothing** when both passes run — a far stronger and more useful statement than "the halves match" |
| **Different** | The offset does reach the render with both passes running; it is applied *equally* to both eyes rather than oppositely. A completely different bug — a sign or indexing fault, not a cancellation |

**These two point at different code and different fixes.** Worth the last launch
of the night.

---

# THE ANSWER — both halves are EYE 1's IMAGE. And this doc's title is wrong

**01:55. Measured, three-way, all at `-Offset 500`.**

```
both-passes  vs  eye1-alone     mean|diff| = 0.31    4.1% differ   <-- THE SAME IMAGE
both-passes  vs  eye0-alone     mean|diff| = 5.03   29.4% differ
eye0-alone   vs  eye1-alone     mean|diff| = 5.02   29.4% differ
```

The 4.1% residual is interpolation-on vs interpolation-off between the two
captures, not a geometric difference.

**When both passes run, BOTH halves carry eye 1's image.**

## Correcting this document at its source

**The title and the "offset vanishes" finding above are WRONG.** They were read
off the *appearance* of one frame — the both-pass `-Offset 500` capture looked
close-framed and un-displaced, so it was called un-offset.

**That is rule 3, violated by the author of this document, two hours after
writing it down.** The offset was never cancelling. It applies in full — it is
just **eye 1's offset, in both eyes.**

Kept rather than deleted, per rule 10. The lesson is not that a hypothesis was
wrong; it is that **an impression was promoted to a finding without a number**,
in a document whose first section warns against exactly that.

## What this means, and the one mechanism that survives

Every measurement now fits a single story:

| Measurement | Explained by |
|---|---|
| Both halves identical at any offset | Both hold eye 1's image |
| `-Offset 500` both-pass = eye1-alone | Eye 1's pass output is what present shows, twice |
| Eye 0 alone renders correctly displaced | With no eye 1 pass, nothing replaces it |
| `-SkipEye 0` → left half BLACK | Eye 0's target has no content of its own to resolve |
| Distinct targets, buffers, matrices, coverage, serialisation | All true, all irrelevant |

**The surviving mechanism: the resolve at PRESENT time.**

Present calls `resolveTarget()` / `getResolvedTexture()` (or
`downsampleTarget()`) on each eye's `RenderTarget`. **Both `eyeColorTargets` are
constructed with the SAME `interpolationTargetKey.address`.** If the resolve
draws from framebuffer storage keyed by that address rather than from the
target's own contents, both eyes resolve to whatever was written last — eye 1 —
and an unrendered target resolves to nothing, which is the black half.

**This is the only remaining explanation consistent with all five results.
It is a hypothesis, not a finding — the eighth in this project, and the previous
seven were wrong.**

### The test, first thing next session

Log, per eye, at present time: the target pointer, its resolved-texture pointer,
**and the address key it resolves against.** If the two eyes resolve against the
same address, that is the bug, and the fix is to give each eye's target its own
identity — a distinct address key, or a copy taken at end-of-pass rather than a
resolve at present-time.

`present source: eye0=..E090 eye1=..E4F0` already shows two distinct *textures* —
so the resolve produces two textures with the same contents. **Two distinct
textures holding one image is precisely what a shared resolve source looks
like.** That line has been in the log since `49` and was read as evidence the
present path was fine.

## Settings to restore

`graphics.json` `rr_option` is currently **`"Original"`** for this test. **It
must go back to `"Manual"` with `rr_manual_value: 90`.** Backup at
`graphics.json.bak-pre57`.

---

# CORRECTION, 2026-08-23 session start — the hypothesis above is FALSIFIED

**Read `58`.** The mechanism this document ends on — *"present's resolve is keyed
on the shared framebuffer address"* — **does not exist in the source.**

- `RenderTarget`'s address parameter is named `addressForName` and its only uses
  are `texture->setName(...)`. It is a debug label; nothing reads it back.
- `resolveTarget()` resolves `this->texture` into `this->resolvedTexture`. No
  map, no address.
- `getResolvedTexture()` returns `this->resolvedTexture` or, with MSAA off,
  `this->texture`. **Each half samples its own target's own texture.**

So the reading of `present source:` given above — *"two distinct textures holding
one image is precisely what a shared resolve source looks like"* — is **void**.
Two distinct textures holding one image means one image was **written** into
both, or one was written twice.

**Eighth hypothesis, eighth falsification — and this one cost no launch**,
because the question was answerable by reading `lib/rt64/` rather than by
building. The test named above ("log the resolve source and address key per eye")
should NOT be built.

`58` carries what replaces it: with the resolve exonerated and the eye passes
confirmed serialised in source, `-SkipEye 0`'s black half and the both-pass
result cannot both be true unless **eye 0's pass renders eye 1's view whenever
eye 1's pass also runs.**

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
