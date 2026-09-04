# 53 — do the two passes render different PIXELS? PLAN, NOT BUILT

**2026-08-23, after `51` was built and G1 still measured 0 px.**

**This is a bisection, not another candidate fix.** Three slices have now fixed
three real defects and moved the image by zero pixels. The next thing built
should *halve the remaining space*, not guess again.

---

## Why not the VR mirror

Asked directly, and worth answering in the record because `48` predicted this
exact temptation.

`47`'s mirror method is the right tool for **"are the images wrong, or is the
metadata submitted with them wrong?"** — a mirror shows the submitted IMAGE and
never the pose or FOV, which is what separated a render bug from a pose bug twice.

**That is not the open question.** `-Flat` already shows both submitted eye
images, side by side, at full fidelity, in a still frame, with no headset, no
recording, no camera shake and no compositor in the path. It is strictly more
evidence than a mirror recording of the same two images, and the answer it gives
is unambiguous: **the two images are identical to the pixel.** A mirror would
show the same two identical images, less precisely.

**`48` prediction 4 — "the mirror method will be applied to a problem that is not
an image problem" — scores as: tempted, correctly declined.** The mirror becomes
the right instrument again the moment `-Flat` shows two *different* images and
the headset still looks wrong. Not before.

---

## The one thing never measured

Every instrument this project has measures **inputs**: matrices, hashes, buffer
addresses, target pointers, pair indices. `49`, `50`, `51` and `52` between them
have eliminated:

- shared eye render targets (`shared=0`)
- the world drawn into a shared framebuffer pair (`52` census)
- one transform buffer for both eyes (two `dst`)
- non-serialised passes (`execute(); wait();` per eye, line 852-855)
- distinct, correctly mirrored per-eye matrices and frustums
- present sampling a single texture

**Nothing has ever looked at the OUTPUT of an eye pass.** The question
"do the two passes actually draw different pixels?" has been assumed to be
answered by the pixels at the *end* of the pipeline, which is the one place both
halves are known to agree.

## The test — per-eye clear colour. `10`'s tint test, aimed at a new question

Before each eye's pass, clear that eye's target to a **different colour**:
eye 0 faintly red, eye 1 faintly blue. Behind a `GE_VR_TINT` env knob, off by
default, and only under `vrStereo`.

Then `-Flat`, and read the two halves.

| Result | Means | Next |
|---|---|---|
| **Halves show DIFFERENT tints** | Two passes really do render into two targets, and present delivers both. The geometry drawn into them is identical — so the eye transform is not reaching the DRAWS, despite reaching the buffer | Instrument the draw path: which transform index each draw actually uses |
| **Halves show the SAME tint** | Whatever present delivers is not what the passes rendered. Something copies, resolves or aliases one target over the other AFTER the passes | Instrument the target lifecycle between end-of-pass and present |
| **No tint at all** | The clear is being overwritten by a full-screen draw, and the test is inconclusive rather than negative | Tint the eye's projection instead — e.g. scale eye 1's x by 1.5 and look for stretch |

**Every branch names a different next slice.** That is the property `51` lacked
and `52` had.

**What would make this test useless?** If the world pass clears or fully covers
the target itself, the tint never survives to be seen — hence the third row,
written before the run rather than discovered as a confusing result.

## Cost

Small: a clear colour, one env knob, one `-Flat` launch. All inside `lib/rt64/`,
MIT half. No headset.

---

## Prediction, written before the build

**The halves will show the same tint**, i.e. present does not deliver what the
passes rendered.

Stated as a prediction and not a finding, and scored next session either way.
**The last two predictions in this project were wrong** (`51` prediction 3, `52`'s
prediction), which is itself the reason this document has a predictions section
instead of a conclusion.
