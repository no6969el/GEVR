# 68 — the descriptor chain resolved: correct end to end. B1 is in the compute shader's USE of the buffer.

**2026-08-23, ~14:40. No launches. The `67` capture, parsed further.**

---

## WHAT WAS RESOLVED

The full D3D12 descriptor chain for both eye passes, replayed from the capture:
`CreateShaderResourceView` -> `CopyDescriptorsSimple` -> `SetComputeRootDescriptorTable` -> `Dispatch`.

```
PASS A (eye 0)                          PASS B (eye 1)
4894 CREATE heap12[18] <- 82638 EYE0    5755 CREATE heap12[18] <- 85986 EYE1
4956 COPY   heap12[18] -> heap13[18]    5816 COPY   heap12[18] -> heap13[18]
4958 TABLE  root=1 heap13 base=3        5818 TABLE  root=1 heap13 base=3
         +15 = EYE0                              +15 = EYE1
4959 DISPATCH 117 groups                5819 DISPATCH 117 groups
      ExecuteCommandLists @ 5737              ExecuteCommandLists @ 6596
```

**Each dispatch's descriptor table, at slot +15, holds its OWN eye's buffer.**

**And the ordering is safe.** Both passes write the same shader-visible slot
`heap13[18]`, but pass A *executes* at 5737, before pass B overwrites it at
5816. No descriptor hazard.

## NO GRAPHICS DRAW EVER SEES A TRANSFORM BUFFER

All 23 `SetGraphicsRootDescriptorTable` calls were resolved the same way.
**Not one of their descriptor ranges contains either eye buffer.** Only the two
compute tables do.

```
3840 COMPUTE root=1 heap13 base=102  +15=EYE0
4958 COMPUTE root=1 heap13 base=3    +15=EYE0
5818 COMPUTE root=1 heap13 base=3    +15=EYE1
   (no GRAPHICS table, anywhere in the frame)
```

**So the per-eye transform buffer has exactly ONE consumer: the RSP compute
dispatch.** The 939 draws never read it. They consume the compute's *output*.

## `VertexProcessor` IS CORRECTLY EYE-AGNOSTIC

The second 117-group dispatch in each pass is `VertexProcessor`, which binds
`worldMats` / `invTWorldMats` / `prevWorldMats` and writes `worldPos`,
`worldNorm`, `worldVel`. **It never touches viewProj.** It is world-space input
for raytracing, and `51` was right not to give it an eye index. Not a suspect.

## THE SHARED OUTPUT BUFFER IS PROBABLY NOT IT EITHER

`workload.outputBuffers` (`screenPosBuffer`, `genTexCoordBuffer`,
`shadedColBuffer`, ...) is a single struct per workload, **shared by both eye
passes** — the last shared mutable state in the draw path, and the obvious
next thing to split after `50` split the targets and `51` split the transforms.

**The capture argues against it.** Pass A's whole command list — compute AND
draws — executes at 5737. Pass B's compute is recorded at 5819, after. The
draws that consume eye 0's positions have already run on the GPU before eye 1's
compute overwrites them.

**Do not build the `outputBuffers[2]` split on the strength of the pattern.**
It touches ~20 sites across three files and the ground truth says the ordering
already protects it. **If it is ever built, it must be because something
measured says so — not because the previous two fixes had that shape.**

---

## WHAT IS LEFT, AND IT IS NARROW

Everything below is now **verified correct by observation from outside the
codebase**, not by reading RT64:

| Stage | Verified |
|---|---|
| CPU per-eye matrices | correct, mirrored: +/-414.6 offset, -/+0.1411 skew (`67`) |
| Upload destination | two distinct GPU buffers, 82638 / 85986 (`67`) |
| Shader resource views | one per buffer, own barriers (`67`) |
| Descriptor heap slots | each eye's SRV in its own pass's slot (this doc) |
| Compute table binding | each dispatch binds its OWN eye at +15 (this doc) |
| Pass serialisation | separate `ExecuteCommandLists` (`67`) |
| Render targets | distinct, `shared=0` (`50`) |
| Present | each half samples its own eye's target (`58` stamp) |

**And the halves are pixel-identical: 0 px against a predicted -94.2,
correlation 1.0000 at dx=0.**

**Therefore: the compute dispatch reads the right matrices and produces output
that does not differ between eyes.** The fault is in how the shader USES the
buffer it correctly bound.

### The prime suspect, and how to test it

`RSPProcessor` binds **two** relevant buffers:

```cpp
processSet->setBuffer(processSet->srcViewProjIndices, ...viewProjIndicesBuffer...);
processSet->setBuffer(processSet->viewProjTransforms, eyeViewProj.get(), ...);
```

The shader transforms each vertex by `viewProjTransforms[ viewProjIndices[v] ]`.

**`viewProjIndicesBuffer` is NOT per-eye** — it is the same buffer for both
passes (confirmed: every non-viewProj upload destination is identical across
the two passes, `67`).

**That is correct only if the indices mean the same thing in both eyes' arrays.**
And there is a measured hint that they may not: **of the 26 matrices, exactly
one is identical between the eyes — matrix 0.** If the vertices that make up
the world index matrix 0, every vertex gets the same transform in both eyes and
the image is identical, while every instrument upstream reports two correct,
different buffers.

**The test, and it needs no launch:** the capture holds
`viewProjIndicesBuffer`'s contents. Find its upload (one of the
`CopyBufferRegion` destinations shared by both passes), pull the blob from
`gevr.zip` by the `Unmap` chunk's buffer id, and **read the indices**. If they
are all 0, or all point at matrices that happen to be identical, B1 is named.

**What it would say if it were looking at the wrong thing:** if the indices are
spread across 1..23 as `54`'s coverage probe claims, then the indices are fine,
the shader is reading different matrices per eye, and the fault is further
still — in the shader maths or in what consumes `screenPosBuffer`. That is a
different search, and it would also mean `54`'s probe is trustworthy, which is
worth knowing on its own.

**Do NOT trust `54`'s `idx coverage: drawn=23 overridden=23 covered=23` for
this.** It is from the same family of instruments as `49`'s upload verdict,
which turned out to be incapable of failing (`67`). **Read the bytes.**

---

## The method note, because it is the transferable part

Three instruments in this project have now been found incapable of failing:
`49`'s upload verdict, today's `VIEWPROJ GPU` line, and — pending — possibly
`54`'s coverage probe. All three were written by someone reasoning about the
code, and all three confirmed that reasoning.

**RenderDoc broke the pattern because it does not know what the code intended.**
Every fact in the table above came from the capture, not from RT64's source.

**When an instrument and a picture disagree, and twelve hypotheses have died,
stop instrumenting and go and look from outside.**

---

# THE INDICES, THE TARGETS AND THE PRESENT — all three checked, all three correct

**Continued, same capture, no launches.**

## `srcViewProjIndices` — my own hypothesis, falsified

Slot **+5** of the compute table is `srcViewProjIndices`, resource 82613,
`R16_UINT` — **the same buffer in both passes, and never re-uploaded during
them.** Its contents, read from the capture's blob (chunk 4825, blob 1355):

```
7473 indices, 25 distinct values, min 1 max 25
fraction pointing at matrix 0 : 0.00%
fraction in 1..25             : 100.00%
fraction out of range         : 0.00%
```

**The "everything indexes matrix 0" hypothesis is dead.** Matrix 0 is the only
one of the 26 that is identical between the eyes, and **nothing indexes it.**
Every vertex reads a matrix that genuinely differs per eye.

**And `54`'s coverage probe is vindicated** — `drawn=23 overridden=23` was
telling the truth. It was on the suspect list in this document's first half
purely by association with `49`'s vacuous verdict. **Association is not
evidence; the bytes were read.**

## The render targets — distinct, confirmed by ground truth

```
pass A (eye 0):  OMSetRenderTargets @4975 -> RTV heap16[41],  313 draws
pass B (eye 1):  OMSetRenderTargets @5836 -> RTV heap16[42],  313 draws
```

**Two different RTV slots.** `50` was right, and it is now confirmed from
outside RT64 rather than by `50`'s own `shared=0` probe.

## The present — two distinct textures, correct halves

```
6615 Viewport TopLeftX=0   Width=800   ->  GFX table -> resource 85982  -> DrawInstanced
6642 Viewport TopLeftX=800 Width=800   ->  GFX table -> resource 85987  -> DrawInstanced
```

**The left half samples one texture, the right half samples a different one.**
`58`'s target stamp was telling the truth as well.

---

# THE CONTRADICTION, STATED EXACTLY

Every stage is now verified correct **by observation from outside the
codebase**:

| Stage | Verified by |
|---|---|
| CPU matrices, mirrored +/-414.6 and -/+0.1411 | capture blobs |
| Two distinct GPU buffers | CopyBufferRegion destinations |
| One SRV per buffer, own barriers | CreateShaderResourceView |
| Correct descriptor heap slot per pass | CopyDescriptorsSimple replay |
| Each dispatch binds its OWN eye at +15 | SetComputeRootDescriptorTable replay |
| Indices reference 1..25, never the shared matrix 0 | buffer contents |
| Passes serialised | separate ExecuteCommandLists |
| Distinct render targets, 313 draws each | OMSetRenderTargets |
| Present samples two distinct textures, correct halves | GFX table + viewports |

**And the halves are pixel-identical: 0 px against a predicted -94.2,
correlation 1.0000 at dx=0, mean|L-R| = 0.0006.**

**One of these facts must be false, and the list is now short enough to check
each one individually.**

## THE ONE LINK NOT CLOSED

**Do the two presented textures (85982, 85987) correspond to the two render
targets the passes drew into (RTV heap16[41], heap16[42])?**

The RTV descriptors do not serialise with a `dst` PortableHandle in the same
form as SRVs, so the XML replay could not resolve `heap16[41]` and `heap16[42]`
to resource ids. **This is a limitation of the parsing, not a finding.**

**If they do not match, present is sampling textures that neither eye pass
rendered into — and B1 is named.** That would also explain why `58`'s stamp
reports correctly: the stamp is written on the `RenderTarget` object the pass
was handed, which is not necessarily the resource the present resolves and
samples.

### How to close it, in about thirty seconds

**Open `gevr_frame21238.rdc` in `qrenderdoc.exe`:**

1. Find the two `DrawInstanced` at the end of the frame (event ~6638 and ~6656).
2. For each, the **Texture Viewer** shows the bound SRV — note the resource.
3. Scroll back to the two `OMSetRenderTargets` (~4975 and ~5836) and note the
   resource each pass rendered into.
4. **Compare.** Four resource ids, one comparison.

The GUI resolves the RTV/SRV chain automatically. **This is the single step in
this investigation that genuinely wants a human at a screen**, and it is one
comparison.

**Also worth one glance while it is open:** select the two eye-pass draws and
look at the rendered output of each target in the Texture Viewer. **If the two
targets visibly differ, the render is fine and the fault is entirely in
present.** That is a picture, not a number, and it splits the remaining space
in half.

## A discrepancy noted, not yet meaningful

The two SRVs describe different element counts for the same 1664-byte upload:

```
eye 0: NumElements=48  StructureByteStride=64
eye 1: NumElements=36  StructureByteStride=64
```

26 matrices were uploaded to each and indices reach 25, so both reads are in
bounds and this is **not** a fault. It does show the two buffers were sized at
different moments. Recorded so nobody mistakes it for the bug, and so nobody
has to rediscover that it is not.
