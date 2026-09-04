# 67 — RenderDoc: everything upstream of the shader is CORRECT. Measured from outside the codebase.

**2026-08-23, ~14:20. One `-Flat` capture, converted to XML and parsed. Read `65` and `66` first.**

---

## WHY THIS DOCUMENT IS DIFFERENT FROM THE OTHER TWELVE

Twelve hypotheses about B1 have been falsified. **Every instrument that
produced them asked the code what it intended to do**, using this project's own
reading of the source as the measuring stick. When that reading is the error,
the instrument inherits the error and confirms it.

**RenderDoc records what D3D12 was actually told.** None of it depends on
anyone's reading of RT64.

**And this session proved the point twice, on its own instruments:**

1. **`49`'s "upload verdict" is VACUOUS.** It compares `u.dstPair` — the
   addresses of `&drawBuffers.viewProjTransformsBuffer` and
   `&drawBuffers.viewProjTransformsBufferEye1`. **Two adjacent members of one
   struct, 0x30 apart. The comparison cannot fail on any build.** Its verdict
   "distinct data to DIFFERENT destination buffers — so the draws read a third
   buffer" has never meant anything, and it steered `57` and `58`.
2. **The replacement instrument written today was vacuous the same way**, and
   the user stopped it before it ran. `BufferPair::get()` returns
   `defaultBuffer.get()`; two separate BufferPair members always own separate
   RenderBuffers, so it printed "distinct GPU buffers — the binding is correct"
   on every line, which is what it would print on a working build and a broken
   one alike. **Rule 4, from the author of today's rule-4 corrections.**

**Gates were written for the outcomes and never for the measurement. The
question `48` actually requires is: can this instrument distinguish the cases
at all?**

---

## THE PREMISE WAS CHECKED THIS TIME

Before drawing anything from the capture, `-Flat -Offset 500` was measured on
the same build:

```
PREDICTION: eye1 - eye0 = -0.2821 ndc = -94.2 px per 668-px half-frame
MEASURED:   0 px.  cross-correlation at dx=0 = 1.0000.  mean|L-R| = 0.0006
```

**B1 reproduces fully in `-Flat -Offset 500`.** A 1000-unit eye separation
produces zero pixels of disparity. So the captured frame is a BROKEN frame, and
everything below describes the broken case.

**This check was nearly skipped.** Had it been, and had the capture looked
correct, the conclusion "the pipeline is fine" would have been drawn from a
frame nobody established was faulty.

---

## WHAT THE CAPTURE SHOWS — ground truth

`renderdoccmd capture` on `-Flat -Offset 500`, then `convert -c zip.xml`, parsed
here. The frame contains 45 `CopyBufferRegion`, 15 `Dispatch`, 11
`ExecuteCommandLists`, 939 `DrawIndexedInstanced`.

### The two eye passes are genuinely separate submissions

```
chunk 4940-4967   pass A : uploads, 2 dispatches   -> ExecuteCommandLists @ 5737
chunk 5800-5828   pass B : uploads, 2 dispatches   -> ExecuteCommandLists @ 6596
```

**`58` was right: the passes are fully serialised.** Two separate command list
executions. No GPU race between them is possible.

### The viewProj upload is the ONLY thing that differs, and it differs correctly

The 1664-byte upload (26 x 64-byte matrices) is the per-eye transform buffer.
Every other destination is shared; that one is not:

```
pass A:  82644  82607  [82638]  82640  82648  82650  80781  55180
pass B:  82644  82607  [85986]  82640  82648  82650  80781  55180
                        ^^^^^ different GPU resources
```

### Both buffers get their own SRV, barriers and upload

```
resource 82638 (eye 0): CreatePlacedResource, CreateShaderResourceView @4894,
                        ResourceBarrier @4937, CopyBufferRegion @4942, barrier @4950
resource 85986 (eye 1): CreatePlacedResource, CreateShaderResourceView @5755,
                        ResourceBarrier @5797, CopyBufferRegion @5802, barrier @5810
```

### AND THE BYTES ARE CORRECT

Extracted from the capture's own blobs — the mapped upload data, chunk 4925
(eye 0) and chunk 5748 (eye 1):

```
26 matrices; 25 differ.

matrix 1, row 2:  eye0  -0.1411   eye1  +0.1411      <- the frustum skew, mirrored
matrix 1, row 3:  eye0 414.6281   eye1 -414.6281     <- the +/-500 eye offset, exact
```

**The per-eye matrices are correct, correctly mirrored, and reached the GPU.**

---

## THE CONCLUSION, AND IT IS NOT A HYPOTHESIS

**In a frame measured to be pixel-identical between the halves, D3D12 was
given:**

- two distinct buffers,
- containing correctly different per-eye matrices,
- each with its own shader resource view,
- each uploaded with correct barriers,
- in two separately executed command lists,
- rendering into two distinct targets (`50`, `shared=0`),
- each target sampled by its own half at present (`58`'s target stamp, which
  fires under `-Sbs` and reports "each half samples the target ITS OWN eye
  wrote").

**Every stage from the CPU matrices to the presented texture is correct, and
the pixels are identical.**

**So the fault is at or after the point where the shader reads the buffer.**
The entire upstream half of the pipeline is now exonerated by observation
rather than by argument, which is more than twelve hypotheses achieved.

---

## THE NEXT QUERY, ON THE CAPTURE THAT IS ALREADY ON DISK

**No new launch is needed. The capture is kept at:**

```
GoldenEyeVR\ge-vr-shots\rdc\gevr_frame21238.rdc     (164 MB, the frame)
GoldenEyeVR\ge-vr-shots\rdc\gevr.zip.xml            (59 MB, the call stream)
GoldenEyeVR\ge-vr-shots\rdc\gevr.zip                (93 MB, the blobs)
```

**The one unresolved link: which descriptor the dispatch actually reads.**

An SRV is *created* for each buffer. It is then staged into a shader-visible
heap and referenced by a root descriptor table. The capture holds:

- 24 x `ID3D12Device::CopyDescriptorsSimple`
- 11 x `SetComputeRootDescriptorTable`
- 5 x `CreateDescriptorHeap`

**The question: does pass B's dispatch read a table slot holding eye 1's SRV,
or a stale slot still holding eye 0's?** Resolve
`SetComputeRootDescriptorTable` -> heap + offset -> the `CopyDescriptorsSimple`
that last wrote that offset -> the `CreateShaderResourceView` it came from ->
the resource id. If that resource is 82638 for BOTH dispatches, B1 is named.

**What it would say if it were looking at the wrong thing:** if the two
dispatches resolve to two different heap offsets that each hold the right SRV,
the descriptor path is correct too, and the fault is inside the compute shader
itself — its indexing into the buffer, or `srcViewProjIndices`. That is a
different search and a different document.

**Open the capture in `qrenderdoc.exe` for this.** The GUI resolves the
descriptor chain automatically and shows the bound resource per dispatch, which
is many hours of XML parsing done for free. **This is the one step in this
project that genuinely wants a human at the screen.**

---

## Housekeeping

- **RenderDoc 1.45 installed** via winget (`BaldurKarlsson.RenderDoc`). MIT, so
  under rule 12 it may influence anything, including `lib/rt64/`. Running a tool
  contaminates nothing regardless of licence; only reading its source would
  raise the question.
- **The capture recipe**, for repeating it:

```powershell
# set the -Flat env exactly as vr.ps1 does, then:
& "C:\Program Files\RenderDoc\renderdoccmd.exe" capture `
    -d C:\Users\<USER>\Desktop\GoldenEye64Recomp `
    -c <output-prefix> `
    C:\Users\<USER>\Desktop\GoldenEye64Recomp\build\Release\GoldenRecomp.exe
# F12 in a level to capture, then:
& "C:\Program Files\RenderDoc\renderdoccmd.exe" convert -f <x>.rdc -c zip.xml -o <x>.zip.xml
```

- **`-Flat` is the right harness for B1** and needs no headset. B1 reproduces
  there at full strength. `64`'s warning that `-Flat` is blind applies to the
  eye PRESENT stage, not to B1.

## The vacuous instruments must be fixed or deleted

**Both are still in the tree and both will mislead.** `49`'s upload verdict and
today's `VIEWPROJ GPU` line. Neither can fail. **A wrong doc costs more than a
bug (rule 10); an instrument that cannot fail costs more than both.**
