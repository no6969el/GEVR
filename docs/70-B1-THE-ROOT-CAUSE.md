# 70 — B1, THE ROOT CAUSE. One descriptor slot, two draws, one command list.

**2026-08-23, ~14:45. RenderDoc, `-Flat -Offset 500`. This supersedes `69`.**

---

## THE BUG

**Both halves of the side-by-side present bind the SAME descriptor heap slot,
in the SAME command list, and D3D12 reads descriptor heaps at EXECUTION time —
not at record time.**

```
Colour Pass #4  (EID 2907-2927)  -  ONE command list, ONE ExecuteCommandLists at 2929

2919   RSSetViewports({   0, 0, 800, 900 })          <- LEFT half
       SetGraphicsRootDescriptorTable(1, { Descriptor Heap 13, 201 })
       DrawInstanced(3, 1)

2927   RSSetViewports({ 800, 0, 800, 900 })          <- RIGHT half
       SetGraphicsRootDescriptorTable(1, { Descriptor Heap 13, 201 })
       DrawInstanced(3, 1)
                                            ^^^ THE SAME SLOT
```

RT64 writes eye 0's SRV into `heap13[201]`, records the left draw, **overwrites
`heap13[201]` with eye 1's SRV**, and records the right draw. Both commands are
then executed together.

**At execution the GPU reads slot 201 twice and finds eye 1's SRV both times.
Both halves sample eye 1's texture.**

This is a textbook D3D12 descriptor-reuse-within-a-command-list hazard.

## IT EXPLAINS EVERY OBSERVATION, INCLUDING ALL THIRTEEN FALSIFIED HYPOTHESES

| Observation | Explained |
|---|---|
| **"Both halves carry EYE 1's image"** (`57`) | eye 1 writes the descriptor last |
| **Each pass ALONE is correct** (`56`) | one draw, one descriptor write, nothing overwrites it |
| **0 px disparity at ANY `-Offset`** (`49`, `57`, `67`) | the same texture is sampled twice |
| **Every "distinct" probe passes** (`50`, `51`, `54`, `58`, `67`) | the buffers, SRVs and targets genuinely ARE distinct — the *descriptor slot* is not |
| **`58`'s target stamp says each half samples its own eye's target** | true at record time, and the stamp cannot see the overwrite |
| **`-PresentEye 0/1` changes nothing** (`64`) | both halves already show one eye |
| **The two eye passes render VISIBLY DIFFERENT images** (RenderDoc, this session) | the render was never the problem |

**The render, the matrices, the buffers, the descriptors, the targets and the
present logic are all correct.** Only the descriptor *slot* is reused.

## SEEN, NOT INFERRED

- Colour Pass #2 (eye 0) and Colour Pass #3 (eye 1) show **different images** in
  the replay — the geometry shifts as a 1000-unit separation should.
- The final swapchain shows **both halves carrying eye 1's image** (the rock
  spire), with eye 0's view nowhere on screen.
- Stepping to draw 2919 alone shows the left half drawn and the right black —
  and the left half's input is **eye 1's** content.

## WHERE IT IS

`lib/rt64/src/hle/rt64_present_queue.cpp`, the side-by-side block:

```cpp
VIRenderer::RenderParams leftParams = renderParams;
prepareEyeFromTarget(leftParams, leftPick);
...
viRenderer->render(leftParams);          // writes viRenderer's descriptor set, records draw

VIRenderer::RenderParams eyeParams = renderParams;
prepareEyeFromTarget(eyeParams, rightPick);
...
viRenderer->render(eyeParams);           // OVERWRITES the same descriptor set, records draw
```

**`viRenderer` is one object with one descriptor set.** Each `render()` call
rewrites it and records a draw into the same open command list. The second write
wins for both draws.

**The XR eye block at `present_queue.cpp:456-480` has the SAME shape** — two
`viRenderer->render(eyeParams)` calls in one command list — so it is the same
bug on the headset path, and fixing only the SBS path would leave the headset
broken while the window looked fixed.

## THE FIX — the shape, not the code (`48` rule 1: plan, discuss, then execute)

**The two eye draws need two different descriptor slots.** Options, in the order
they should be considered:

1. **Per-eye descriptor sets in `VIRenderer`** — the direct fix. Two descriptor
   set objects, one per eye, so the two draws bind two slots.
2. **Execute between the two draws** — correct but costs a submission per eye
   per frame, and the workload path already pays that.
3. **A descriptor ring** — most invasive, least justified.

**Prefer 1.** It is local to `VIRenderer`, it is what the workload path already
does implicitly by executing between eye passes, and it changes nothing when VR
is off (one eye, one set, one draw).

## THE GATE — written before the code

```
.\vr.ps1 -Flat -Offset 500

PREDICTION: eye1 - eye0 = -0.2821 ndc = -94.2 px per 668-px half-frame
REQUIRED:   -94.2 px +/- 5, right eye further LEFT
TODAY:      0 px, correlation 1.0000 at dx=0, mean|L-R| = 0.0006
```

**What would a working build have to do differently to fail this?** It would
have to sample two different textures into two halves. A build that still
shares one descriptor slot cannot pass; a build that fixes it cannot fail.

**Then, worn:** `.\vr.ps1` (SBS is the default now, `65`) and confirm depth is
real and the doubling is gone — because the doubling IS B1 (`65`).

## THE INSTRUMENT TO ADD WITH THE FIX

Every probe this project built asked *"are these two things different?"* about
an object, a pointer or a struct member. **None asked what the GPU would read.**

**Add, per present:** the descriptor table slot each half binds.

```
present halves: left slot=N right slot=M  sameSlot=0|1
```

**`sameSlot=1` is the bug.** And note in the code why the obvious probes
(`shared=0`, `distinct textures`, `distinct buffers`) all pass while it is true.

---

## THE METHOD NOTE — the transferable part of this whole investigation

**Thirteen hypotheses died. Five instruments were found incapable of failing:**

| Instrument | Compared | Why it could not fail |
|---|---|---|
| `49` upload verdict | `&dstPair` | two adjacent struct members |
| today's `VIEWPROJ GPU` | `BufferPair::get()` | separate members own separate buffers |
| `50` `shared=0` | `RenderTarget*` | separate objects |
| `RenderTarget` address | `addressForName` | cosmetic (`67`) |
| `69`'s "same texture" | the render target **NAME** | RT64 names every target by address, so distinct textures share a label |

**Every one compared an identity that was distinct by construction, while the
identity that mattered — the descriptor slot the GPU reads — was never
compared by anything.**

**RenderDoc broke it because it does not know what the code intended.** It
records what D3D12 was told, and it showed two draws binding one slot in three
seconds of looking.

**The rule this earns:** when an instrument and a picture disagree, and the
hypotheses keep dying, **stop instrumenting and go and look from outside.**
