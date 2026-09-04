# 58 — hypothesis 8 is dead, read statically. And the contradiction it leaves

**2026-08-23, session start. PLAN — nothing built, nothing run.**

`57` ended by naming the eighth hypothesis of this project and the test for it:

> Both `eyeColorTargets` are built with the SAME `interpolationTargetKey.address`,
> and present's `resolveTarget()` / `getResolvedTexture()` may resolve against
> that shared address rather than the target's own contents.
> **Next action: log the resolve source and address key per eye at present time.**

That test was not needed. **The source answers it, for free, and the answer is
no.**

---

## F1 — the shared address does not exist. FALSIFIED BY SOURCE

Three facts, each a single line of `lib/rt64/`:

| Where | What it says |
|---|---|
| `rt64_render_target.h:38`, `.cpp:24, 91, 97, 115` | The constructor parameter is **`addressForName`**. Its only uses are `texture->setName("Render Target Color #" + std::to_string(addressForName))` and two siblings. **It is a debug label.** It is not a key, not a lookup, and nothing reads it back |
| `rt64_render_target.cpp:410` `resolveTarget()` | Resolves `this->texture` into `this->resolvedTexture`. No map, no address, no manager |
| `rt64_render_target.cpp:475` `getResolvedTexture()` | `return usesResolve() ? resolvedTexture.get() : texture.get();` — and with MSAA forced off (`43`) `usesResolve()` is **false**, so it returns **the target's own `texture`** |

And present's per-eye path (`rt64_present_queue.cpp:437-470`) picks
`eyeZeroTarget` / `eyeOneTarget` from the published pointers and runs each
through the one shared `prepareEyeFromTarget` lambda, which calls that same
per-target resolve.

**There is no address-keyed resolve anywhere in the present path.** Each half
samples the texture object owned by its own published `RenderTarget`.

`present source: eye0=..E090 eye1=..E4F0` showing two distinct textures was
therefore never evidence of a shared source, and `57`'s reading of it — *"two
distinct textures holding one image is precisely what a shared resolve source
looks like"* — is void. Two distinct textures holding one image means **one image
was written into both**, or **one of them was written twice**.

**Hypothesis 8 joins the other seven. It cost no launch, which is the point:
the question was answerable statically and was about to be answered with a
build.**

## F2 — the eye passes really are serialised. CONFIRMED BY SOURCE

`rt64_workload_queue.cpp:876-878`, at the end of `threadRenderFrame` — i.e. once
**per eye pass**, not per frame:

```cpp
ext.workloadGraphicsWorker->commandList->end();
framebufferRenderer->waitForUploaders();
ext.workloadGraphicsWorker->execute();
ext.workloadGraphicsWorker->wait();
```

So eye 0's GPU work has completed before eye 1's pass is recorded. **No upload
race, no staging race, no in-flight overwrite can put eye 1's data into eye 0's
draws.** This was asserted in `49` and is now read rather than believed.

---

## THE CONTRADICTION — and it is sharp

Four propositions, each independently established. **They cannot all be true.**

| | Claim | Source |
|---|---|---|
| P1 | The window's LEFT half samples `vrEyeZeroTarget`'s own texture | Source, F1 |
| P2 | `-SkipEye 0` (eye 0's pass skipped, eye 1's pass runs) → **left half BLACK** | Measured, `56`/`57` |
| P3 | Both passes → the two halves are **identical** (mean 0.001, 0.01% of pixels) and equal **eye 1's image** (mean 0.31, 4.1%) | Measured, `57` |
| P4 | Eye 0's pass run ALONE renders eye 0's correctly displaced view | Measured, `57` |

**P2 says eye 1's pass does not write eye 0's target** — if it did, the left half
would have shown eye 1's image instead of black.

**P3 says eye 0's target holds eye 1's image** when both passes run.

The only thing left that writes eye 0's target is **eye 0's own pass**. So:

> **When both passes run, eye 0's pass renders EYE 1's VIEW.**
> Run alone, the same pass renders eye 0's view (P4).

That is a different bug from anything this project has chased. Every slice so
far — `50` targets, `51` buffers, `52` the pair, `54` coverage, `56`, `57` —
asked *where the image goes*. **This asks what the first pass was told to draw,
and it depends on whether a second pass exists.**

### Where this could be wrong

Two ways, and both must be checked before building on it:

1. **P3's chain.** "Both halves carry eye 1's image" was measured as
   *halves identical* + *both-passes equals eye1-alone*. If the `eye1-alone`
   frame used in that comparison was compared full-frame while its own left half
   was black, the 0.31 mean could not have arisen — so the comparison was
   half-to-half and the chain holds. **Confirm which halves `57`'s numbers
   compared before this document is trusted.** `gevr_stereo.py` and the retained
   captures can say.
2. **P2's frame.** `-SkipEye` skips the pass but still publishes the target
   (`workload_queue.cpp:1315-1325`, deliberate). A black half is therefore the
   expected reading of *"nothing rendered here"* — but it is also what an
   unallocated or never-resized target looks like. Same picture, different cause.

---

## THE PLAN

Ordered so the free evidence comes first. **Nothing here changes what a frame
renders**; every item is read-only, which under `48`'s amended rule 5 means they
may be batched.

### Slice A — two launches, NO code

Both at `-Flat -Offset 500`, same start point, ammo checked, exactly as `57`.

| Run | Prediction if "eye 0's pass draws eye 1's view" | Prediction if present picks wrongly |
|---|---|---|
| `.\vr.ps1 -Flat -Offset 500 -PresentEye 0` | Both halves show **eye 1's image** (eye 0's target holds it) | Both halves show **eye 0's displaced view** |
| `.\vr.ps1 -Flat -Offset 500 -PresentEye 1` | Both halves show eye 1's image | Both halves show eye 1's image |

**`-PresentEye 0` is the discriminating one, and it has never been run.** It
separates "the target holds the wrong image" from "present reads the wrong
target" in a single launch with no build.

**If it is looking at the wrong thing:** `-PresentEye` is read in
`rt64_present_queue.cpp:445-449` via `getVrConfig().forcePresentEye`, on the
`-Flat` path — unlike `-ForceEye`, which is XR-only and was announced while dead
(`39` O24). **Before the run, confirm the log prints a line naming the forced
eye; if it does not, this is `32`'s dead knob again and the result is void, not
weak.**

### Slice B — the one value never printed, plus a write tag

`57`'s own stated fallback, and it is still the right instrument:

1. **`view FINAL: eye=N tx=%.3f ty=%.3f tz=%.3f`** — the view matrix's
   translation, logged in `threadRenderFrame` **after** everything has touched
   it, per pass, on change. Every projection log so far reports `projMatrix`
   terms; the eye offset lives in the **view** matrix and has never been read.
2. **A per-target write tag.** When a pass finishes, stamp the target it
   rendered into with `(eyeIndex, workloadId)`. Print both targets' stamps at
   present time: `target stamp: eye0 target written by eye=N wl=M | eye1 ...`.

**Gates, written before the code:**

| Gate | Passes only if | What a working build would do differently |
|---|---|---|
| B-G1 | `view FINAL` prints **two different tx** for the two passes, differing by the full eye separation | A build where pass 0 draws eye 1's view prints the **same tx twice** — this gate fails on exactly the bug it is aimed at |
| B-G2 | `target stamp` shows eye 0's target written by **eye 0**, eye 1's by **eye 1** | A build where something else writes it shows the other eye's index |
| B-G3 | Under `-SkipEye 0`, eye 0's target's stamp is **absent** | If it carries a stamp, something wrote it with no pass — which changes the whole question |

**What each would report if it were looking at the wrong thing:** both lines
carry the workload id and are logged on change rather than once (`52`'s menu
latch, O28), and a pass that never runs prints **no** line rather than a stale
one. **If `view FINAL` appears only once per frame, it is being logged outside
the eye loop and the run is void.**

### Slice C — only after A and B, and only if they agree

Name the mechanism, then plan the fix as its own numbered doc. **Not in this
one.**

---

## Not touched, and deliberately

- `graphics.json` — `rr_option: "Manual"` / 90 verified restored (`57`, O31).
  One behaviour change at a time; there is none in this plan.
- `-ResScale`, O21, O29 — unrelated, still open.

## The floor item still outstanding

**`48`'s floor item 1 — commit both repos — was not done all of the last
session**, and its own scoring says so. Nothing from 2026-08-23 late is
committed. That is the cheapest thing in this document.

---

# AMENDMENT — the build, agreed 2026-08-23. Slice A + Slice B batched

**Slice A cannot clear its own precondition without a build.** `-PresentEye` is
**live but silent**: `config.forcePresentEye` is parsed at
`rt64_render_context.cpp:1033` and consumed at `rt64_present_queue.cpp:448-449`
(XR) and `534-535` (the `-Flat` window path), but **nothing logs it** — unlike
`-SkipEye`, four lines below it in the same function, which prints
`docs\56 DIAGNOSTIC: SKIPPING eye N's render pass entirely.`

So a `-PresentEye 0` run would yield a picture with nothing in `gevr.log`
proving the setting reached present, and `48` rule 4 makes that **no** evidence.
The launcher printing it does not count — `32` and O24 were paid for exactly
that. Self-validation by running `-PresentEye 0` against `-PresentEye 1` and
looking for a difference does not rescue it either: under the current fault both
targets are believed to hold eye 1's image, so "identical" is the **expected**
result and discriminates nothing.

Since a build is required anyway, Slice B is batched into it. **Every edit below
is read-only** — no edit changes what a frame renders — which is what `48`'s
amended rule 5 permits.

## The edits

| # | File | Change |
|---|---|---|
| 1 | `src/main/rt64_render_context.cpp` (~1035) | Log `forcePresentEye` when it is `>= 0`, once, in the same shape as the `-SkipEye` line above it. **Clears Slice A's precondition** |
| 2 | `lib/rt64/src/hle/rt64_shared_queue_resources.h` | Per-eye slots for the final view translation, its transform index, a sequence counter, and the present-time target stamp |
| 3 | `lib/rt64/src/render/rt64_projection_processor.cpp` (~263) | After the eye composition and immediately before `viewProjMatrix = mul(viewMatrix, projMatrix)`, publish the view matrix's translation row per eye. **The one value never printed** |
| 4 | `lib/rt64/src/render/rt64_render_target.h` | `lastWriterEye` / `lastWriterWorkload` on `RenderTarget` |
| 5 | `lib/rt64/src/hle/rt64_workload_queue.cpp` | Stamp the eye's target with its eye index at the end of the pass that rendered it |
| 6 | `lib/rt64/src/hle/rt64_present_queue.cpp` | At present time, publish each picked target's stamp. **The deref stays inside RT64**; the host only logs |
| 7 | `src/main/rt64_render_context.cpp` | Print `view FINAL:` and `target stamp:` from the published slots, on change, with the workload id |

**Licence:** edits 2-6 are in `lib/rt64/` — the MIT, upstreamable half. They
derive from this project's own measurements and from no other project's source.
`55` closed prior art: StarFox64-VR's licence is UNCLEAR and was not read.

## Recorded while checking who reads what — NOT acted on

`rt64_rsp_processor.cpp:49-51` binds `viewProjTransformsBufferEye1` for eye 1 and
`viewProjTransformsBuffer` otherwise, so `51`'s consumer is correct **provided
`p.vrEyeIndex` is what it claims** — which `view FINAL` will show.

But **both eye passes still write into the SAME
`drawData.modViewProjTransforms` array** (`rt64_projection_processor.cpp:86-89,
263`) and the same `outputBuffers->screenPosBuffer`. `51` separated the upload
**destination**, not the **source**. Today only the per-pass
`execute(); wait();` (F2) keeps them apart. **This is the `51` shape one level
up, and it is a candidate for what Slice B measures — not a fix to build now.**

## Gates — restated for the batched build

Unchanged from B-G1..B-G3 above, plus:

| Gate | Passes only if |
|---|---|
| A-G0 | `gevr.log` prints the forced present eye when `-PresentEye` is given, and **prints nothing** when it is not. A line that appears either way is announcing a state it is not in — `32`'s shape again |

**What each instrument reports if it is looking at the wrong thing:** `view
FINAL` carries the eye index, the transform index and the workload id, and is
logged on change rather than once, so a menu cannot own the answer (`52` O28). A
pass that never runs publishes **nothing** rather than a stale value. **If
`view FINAL` appears once per frame instead of twice, it is outside the eye loop
and the run is VOID.**

---

# AS MEASURED — 2026-08-23 10:02. Build clean, both instruments fired,
# and `58`'s own derived statement is FALSE

Capture `gevr-58-baseline-100234`, `-Flat -Offset 500`, Runway, standing still.
1600x900 client area, 800-px halves.

## The instruments, verified before the picture was judged

```
render passes: eye0=90 eye1=90 distinctTargets=90     sustained, all three equal
pass targets:  eye0=0x...C4470 set=1 | eye1=0x...C5C70 set=1 | perspectiveInWorkload=21
idx coverage:  drawn=21 overridden=21 covered=21      all equal
eye targets:   eye0=...889C3930 eye1=...A9CC5A70 shared=0
fb census:     1 pairs, redirected pair = 0           the world IS the redirected pair
```

**A-G0, negative half: PASSES.** No forced-present-eye line appears when
`-PresentEye` is not given. The positive half is still unrun.

## The two new numbers

```
view FINAL eye0: tx= 391.551 ty=72.777 tz=-101.326  idx=21  publications=42
view FINAL eye1: tx=-608.449 ty=72.777 tz=-101.326  idx=21  publications=42
view FINAL verdict: dx=1000.000

target stamp: LEFT half's target written by eye=0 (wl=3)
            | RIGHT half's target written by eye=1 (wl=3)
target stamp verdict: each half samples the target ITS OWN eye wrote.
```

Sustained across every subsequent camera position — `idx` 21, 23, 24, `dx` never
anything but **1000.000**, and both eyes' publication counts equal at every
sample.

**B-G1: PASSES.** The two passes carry different views, differing by exactly the
1000-unit separation, read at the point the draws consume them.
**B-G2: PASSES.** Each half samples the target its own eye wrote.
**B-G3:** unrun (needs `-SkipEye`).

## And the picture is still ONE IMAGE

```
mean|L-R| at seam = 0.001      pixels differing by >2 levels: 0.01%
far/sky  dx=+0  corr 1.000        mid   dx=+0  corr 1.000
near     dx=+0  corr 1.000        gun   dx=+0  corr 1.000
```

## THE FINDING

**`58`'s derived statement — "eye 0's pass renders eye 1's view whenever eye 1's
pass also runs" — is FALSE.** Killed by the instrument written to test it, in one
launch. **Ninth hypothesis, ninth falsification.**

The value of it: the statement was derived from four propositions that could not
all be true, so one of them had to give. **P2 is the one that gives** — the
reading of `-SkipEye 0`'s BLACK half as *"eye 1's pass does not write eye 0's
target"* is what fails, and `58`'s own "where this could be wrong" section
flagged that a black half is also what a never-resized target looks like.

**What this pins down, and it is the tightest bound this project has had:**

| Stage | State |
|---|---|
| The game's view and projection | correct |
| The eye composition, `mul(viewMatrix, eye.viewOffset)` | **correct and DISTINCT — dx=1000.000, measured at the consumption point** |
| `viewProjMatrix = mul(viewMatrix, projMatrix)` | ← **the fault is at or after here** |
| The upload, per eye | distinct data, distinct destinations — `49`, `51` |
| The RSP compute's bind | per-eye, and the only consumer — read in source |
| Which target each pass wrote | **correct and distinct — STAMPED** |
| Which target each half samples | **correct — STAMPED at present** |
| The pixels | **IDENTICAL** |

**Correct distinct matrices in. Correct distinct targets out. One image.** The
fault is now bounded to the span between forming `viewProjMatrix` and the pixels
landing in the target — and nothing outside that span is still a suspect.

## The candidate this exposes — rule 6, and NOT yet acted on

`rt64_state.cpp:1080` uploads the game's **raw, un-offset**
`drawData.viewProjTransforms` into `workload.drawBuffers.viewProjTransformsBuffer`
— **the same `BufferPair` eye 0's projection processor uploads its modified
matrices into** (`rt64_projection_processor.cpp:313-314`). Eye 1 has
`viewProjTransformsBufferEye1` to itself; **eye 0 shares its buffer with the
game's own upload path.**

Two writers, one buffer, and only one of the two eyes is exposed to it. That is
`48` rule 6's shape — *check who else writes what you write* — which has now
appeared six times in this project.

**Stated as a candidate, not a finding.** It predicts eye 0 rendering the
**un-offset** view, and the halves are identical rather than one-offset-one-not,
so it does not fit on its own. **The discriminating measurement is below.**

## Next action — one launch, and it splits the remaining span

**`-Flat -Offset 0`, same spot, compared against this capture.**

| Result | Means |
|---|---|
| **Identical to the `-Offset 500` capture** | The eye offset does not reach the PIXELS at all, despite reaching the view matrix in full. The fault is in what the draws read — the buffer, not the eye assignment |
| **Different** | The offset does reach the pixels; both halves are then showing ONE eye's offset view, and the question is which eye and how it got into both |

`57` proposed this comparison and then reported a three-way result instead; the
`-Offset 0` vs `-Offset 500` both-passes pair does not appear to have been run.
It costs one launch and one return to the spot.

## Instrument defects found in this run — log them, do not chase them

- **`fb census` now reports `1 pairs`, not the `2 pairs` `49` built its root
  cause on.** Either the census was on a menu then (O28) or the pair count is
  workload-dependent. **`49`'s "2 framebuffer pairs but only pair 1 is
  redirected" is not reproducing.** New: **O34.**
- **The census verdict still ends "Look at the shared transform buffer"** — advice
  `51` has since acted on and closed. A verdict string that names a stale next
  action. New: **O35.**
- **`PREDICTION:` says "-94.2 px per 668-px half-frame" while the capture's half
  is 800 px**, and `00-START-HERE` states the pass criterion as -113 px ± 5.
  **Three numbers for one gate**, one of them scaled to a half-width this
  capture does not have. A gate judged against it would be wrong by ~15%.
  New: **O36 — and it must be fixed BEFORE the first non-zero disparity is
  measured**, or the first real stereo will be judged against the wrong number.
- **Reported from the screen during the run: occasional stray lines, two at a
  time, crossing the image.** Not measured, not reproduced, possibly the
  capture's own cursor artefact (`48`'s scoring records a mouse cursor being
  mistaken for a result once already). New: **O37, untriaged.**

---

# THE `-Offset 0` COMPARISON — and the instrument that nearly reported a browser

## First, the wrong turn, recorded before the result

`gevr-58-offset0-101523` measured **34.28% of pixels differing, dx=+160 at every
depth band**. Against a baseline of *"the halves are always identical"*, that is
the shape of a result — the first non-zero disparity this project has ever
measured — and it was one paragraph away from being reported as one.

**It was a screenshot of a WEB BROWSER.**

`tools_gevr_capture.ps1` finds the GoldenRecomp window by process, calls
`SetForegroundWindow` to raise it, **and discards the result.** Windows refuses
that call when the calling process is not itself foreground, so the script
captured whatever was on top **at the game's client coordinates** and printed
`CAPTURED 1600x900 (half-width 800)` exactly as it does on a good run.

**What caught it was the difference MAP, not the difference fraction.** `48`'s
scoring already ranks that third among the things that did the work, from the
night a 0.19% change turned out to be a mouse cursor. Same lesson, one day later,
with a much more convincing wrong number: **+160 px at every band, with
correlation 0.05-0.23.** The low correlation was the tell — real disparity
correlates, and a constant shift at all four depths is not parallax at all.

**The knob's log line was valid throughout** — the game was running and in-level;
only the PNG was of something else. **A run can be half-void.**

### Fixed, in the tool

`tools_gevr_capture.ps1` now reads `GetForegroundWindow()` after the raise and
**refuses to capture** if it is not the game, naming the reason. An instrument
that cannot confirm what it is looking at must say so rather than produce a
number — `48`, the rule `52`'s census earned.

**This is the fourth instrument caught lying in two days** — `fb eye` (O28),
`render passes:` under `-SkipEye` (O30), `-PresentEye`'s silence (`58`), and now
the capture script itself. **Every one of them reported success.**

## The valid comparison

`gevr-58-offset0-retry-101736`, foreground verified. The two runs landed at the
same camera position — baseline eye0 `tx=574.9` / eye1 `tx=-425.0`, midpoint
**74.95**; the `-Offset 0` run reads **74.9**, with `ty` and `tz` matching to
0.01. Directly comparable.

```
-Offset 0, halves:      mean|L-R| = 0.001    0.00% differ   dx=+0 all bands
   (CORRECT. At zero separation identical halves are the EXPECTED result)

-Offset 500  vs  -Offset 0, same spot:
   full frame           mean|diff| = 15.921   76.42% of pixels differ
   LEFT half            mean = 15.921         76.42%
   RIGHT half           mean = 15.921         76.42%
   far-band shift  LEFT(500) -> LEFT(0):   dx = 174   corr 0.313
   far-band shift RIGHT(500) -> RIGHT(0):  dx = 174   corr 0.313
```

## THE RESULT

**The eye offset DOES reach the pixels.** `-Offset 500` renders a visibly
displaced world; it is not being cancelled, ignored or averaged away.

**And both halves are displaced by exactly the same amount** — LEFT and RIGHT
move by an identical `dx=174` against the zero-offset run, to three decimal
places of mean difference. So:

> **Both halves show ONE eye's offset view.** The offset arrives in full; it
> arrives as the SAME eye's offset in both halves.

Which kills the first branch of the fork this run was designed to split: *"the
offset does not reach the pixels at all"* is **false**.

## Where that leaves the span

| Stage | State |
|---|---|
| Eye composition, per pass | **DISTINCT — dx=1000.000 measured at the consumption point** |
| `viewProjMatrix` formed | ← the fault is at or after here |
| CPU upload data, per eye | **DISTINCT hashes** — `49` |
| Upload destination, per eye | **DISTINCT** — `51`, O25 |
| RSP compute's bind | per-eye, and the **only** consumer of the buffer — source |
| **The pixels each pass produced** | **NEVER MEASURED. The gap.** |
| Which target each pass wrote | **CORRECT and distinct — stamped** |
| Which target each half samples | **CORRECT — stamped at present** |

Everything on both sides of "the pixels each pass produced" is measured correct
and distinct. **That one row is now the entire remaining search space**, and
`39` O26 has said "never measured" about it since `53`.

## Next action — and it fires B-G3

**`-SkipEye 1` then `-SkipEye 0`, same spot, this build.** `57` ran this pair on
the previous build and concluded both-passes equals eye1-alone; repeating it here
gets that answer with `view FINAL` and `target stamp` printing alongside, so the
identification is made on a build whose instruments have all been verified.

| Result | Means |
|---|---|
| both-passes == **eye1-alone** | Eye 1's pass produced the pixels in eye 0's target too. `57`'s conclusion reproduces on a verified build |
| both-passes == **eye0-alone** | The opposite, and `57`'s identification was wrong |
| both-passes == **neither** | `57`'s original "third image" reading returns, on a build where it can be trusted |

**B-G3 fires on the same runs:** under `-SkipEye`, the skipped eye's target must
stamp as `-1` (NEVER WRITTEN). If it stamps as an eye index, something wrote a
target with no pass, which changes the question again.

## More instrument defects

- **O39: `gevr_stereo.py` calls identical halves "the docs\49 failure"
  unconditionally.** At `-Offset 0` identical halves are the **correct** result.
  A verdict string that cannot be right in both directions.
- **O40: `tools_gevr_capture.ps1` discarded `SetForegroundWindow`'s result.**
  Fixed above. Recorded because the SHAPE is O21's, and that is now six.

---

# THE THREE-WAY, ON A BUILD WHOSE INSTRUMENTS ARE ALL VERIFIED

All `-Offset 500`, all this build, all the Runway start, foreground verified.

```
eye0-alone (-SkipEye 1):  LEFT mean=42.89   RIGHT mean=0.00  <- black
eye1-alone (-SkipEye 0):  LEFT mean= 0.00   RIGHT mean=43.37 <- black

both.LEFT       vs eye1-alone.RIGHT    mean=0.402   4.32% differ   <-- THE SAME IMAGE
both.RIGHT      vs eye1-alone.RIGHT    mean=0.401   4.31% differ
both.LEFT       vs eye0-alone.LEFT     mean=4.919  28.47% differ
eye0-alone.LEFT vs eye1-alone.RIGHT    mean=4.924  28.50% differ
```

**`57` reproduces exactly** — it measured 0.31/4.1%, 5.03/29.4% and 5.02/29.4% on
the previous build. **Both halves carry EYE 1's image**, now established on a
build where every instrument has been checked and two of them have demonstrated
that they can decline to answer.

## B-G3: PASSES, both directions

```
-SkipEye 1: target stamp: LEFT eye=0 (wl=2) | RIGHT eye=-1 (wl=0)   NEVER WRITTEN
            view FINAL: CANNOT ANSWER - eye0 publications=42 eye1=0
-SkipEye 0: target stamp: LEFT eye=-1 (wl=0) | RIGHT eye=1 (wl=3)   NEVER WRITTEN
            view FINAL: CANNOT ANSWER - eye0 publications=0 eye1=21
```

**The "I cannot answer" branch fired, in both directions, exactly where it
should.** That is the rule `52`'s census earned, working as designed — and it is
what makes the numbers above evidence rather than a picture.

## THE CONTRADICTION IS RESOLVED, AND P2 IS THE PROPOSITION THAT BROKE

`-SkipEye 0`'s black half was read in `56`/`57` as *"eye 1's pass does not write
eye 0's target"*. **It means nothing of the sort.** The stamp says eye 0's target
was **NEVER WRITTEN AT ALL** in that run — there was no eye 0 pass to write it,
so it stayed black. The run says nothing whatever about what eye 1's pass does to
a target that eye 0's pass HAS written.

**`58`'s own "where this could be wrong" section named this exact failure mode**
— *"a black half is also what an unallocated or never-resized target looks
like"* — and it is the one that broke. Writing the doubt down before the run is
what made this cheap.

## What is now established, and it is a mechanism, not a hypothesis

| | |
|---|---|
| Eye 0's pass receives the CORRECT, DISTINCT view | dx=1000.000, at the consumption point |
| Eye 0's pass renders into ITS OWN target | stamped eye=0 |
| Present samples that target's OWN texture | source, and distinct pointers |
| With eye 1's pass ABSENT, that target holds **eye 0's correct image** | `-SkipEye 1`, 28.47% from eye 1's |
| With eye 1's pass PRESENT, the same target holds **eye 1's image** | 4.32%, i.e. identical |

> **Eye 0's target is correct until eye 1's pass runs, and afterwards it holds
> eye 1's image. Something in eye 1's pass writes eye 0's texture — a texture
> that pass does not own and is not stamped as writing.**

Not a cancellation, not a resolve, not the view matrix, not present, not
interpolation, not the transform buffers, not the targets being shared. **A
write, by the second pass, into the first pass's texture.**

## The next slice — census the WRITES, not the passes

The stamp records only the pass's **override** target. A pass can touch other
targets through paths the stamp never sees, and two are already visible in
source:

- `rt64_workload_queue.cpp:751` and `:790` — `targetManager.get(otherColorTargetKey)`
  / `otherDepthTargetKey`, RT64's synchronisation between targets whose
  framebuffer regions overlap.
- `fbManager.recordOperations(...)` at the end of every pass — `:862`.

**The instrument: a write counter on `RenderTarget` itself**, bumped wherever the
target becomes a framebuffer attachment or a copy destination, tagged with the
eye index currently rendering. Printed per eye target at present time.

**Gate:** eye 0's target must show writes **only** while eye 0's pass is
recording. A write bearing eye 1's tag names the line. **What it reports if it is
looking at the wrong thing:** if eye 0's target shows zero writes in a run where
its half is not black, the counter is not on the path that fills it, and the run
is void rather than exonerating.

**Plan only. Not built.** `48`'s trigger for a plan-and-stop is met: this touches
shared RT64 code and it is the first edit in three that is not purely additive
logging.
