# 69 — RETRACTED IN PART. "Same texture" was read off a NAME, not an identity.

> ## READ THIS BOX FIRST — THE HEADLINE CLAIM BELOW IS WITHDRAWN
>
> **`Render Target Color #4040704` is a NAME, not a resource id.**
>
> **4040704 decimal = `0x3DA800`** — one of the two game framebuffer addresses
> (`67`). RT64 names every render target after its `addressForName`, and
> `workload_queue.cpp:1219` constructs **every eye target with the same
> `interpolationTargetKey.address`**. So distinct textures all display under
> one label in RenderDoc.
>
> **Proof it is a name and not an identity:** Colour Pass #1 reports
> `Render Target Color #4040704 - 320x240`, while Colour Passes #2 and #3
> report `#4040704 - 2348x1320`. **A texture cannot change size.** Three
> different textures, one label.
>
> **So "both eye passes render into the same texture" is NOT established.** It
> may still be true — passes #2 and #3 do share both the name and the size —
> but it was read off a label, and a label is exactly what `67` proved
> `addressForName` produces.
>
> **This is the fifth identity comparison this session that compared the wrong
> thing, and the first one I published before catching.** `49`'s upload
> verdict, today's `VIEWPROJ GPU` line, `50`'s `shared=0`, the `RenderTarget`
> address, and now this. **Rule 4 is not a checklist item; it is the whole job.**
>
> **What survives, and it does not depend on any label — see "THE MEASUREMENTS
> ALONE FORCE IT" below.** The two passes render different images and the two
> presented halves are identical. That still requires the two presented
> textures to have been fed from one source. **Whether that is one shared
> render target, two targets sharing a texture, or a present that resolves the
> same target twice is NOT yet distinguished.**
>
> **To settle it:** in `qrenderdoc.exe`, right-click each pass's RT0 thumbnail
> and open the **Resource Inspector**, which shows the true resource id rather
> than the name. Compare the ids for Colour Pass #2 and Colour Pass #3.
> **Do not compare the names.**

## The original claim, kept as the record of the error

# B1: both eye passes appeared to render into the SAME D3D12 texture

**2026-08-23, ~14:40. RenderDoc GUI, on the `67` capture. Read this first.**

---

## THE FINDING

**The two eye passes render visibly DIFFERENT images into the SAME render
target. Eye 1 overwrites eye 0, and present then resolves that one texture into
both halves.**

```
Colour Pass #2  (EID 1239-1990)  = eye 0   ->  Render Target Color #4040704
Colour Pass #3  (EID 2098-2849)  = eye 1   ->  Render Target Color #4040704
                                                ^^^^^^^^ THE SAME TEXTURE
```

Read in RenderDoc from two independent places, for both passes: the Texture
Viewer's **`Cur Output 0`** label, and the **RT0 thumbnail** in the Outputs
panel. Both report `Render Target Color #4040704`, 2348x1320,
`R16G16B16A16_UNORM`.

## THE RENDER WAS NEVER THE PROBLEM

**Stepping between the two passes in the Texture Viewer shows two visibly
different images** — the terrain and the tower shift exactly as a 1000-unit
eye separation (`-Offset 500`) should move them.

**So the eye split works. The per-eye matrices work. The passes each draw a
correct, different view.** Everything `50`, `51`, `54`, `56`, `57` and `67`
measured about the inputs was right. The second pass simply lands on top of the
first.

## THE MEASUREMENTS ALONE FORCE IT — no UI label required

This does not rest on reading a label off a screen:

1. The two passes render **different** images (seen in the replay).
2. The two presented halves are **pixel-identical** — 0 px against a predicted
   -94.2, correlation 1.0000 at dx=0, `mean|L-R| = 0.0006` (`67`).

**Two different renders cannot produce two identical presented textures unless
both landed in the same place and the second overwrote the first.** The
RenderDoc labels confirm what the pixels already required.

## WHY EVERY INSTRUMENT SAID "DISTINCT"

**`50`'s `eye targets: eye0=...C190 eye1=...CB90 shared=0` compares RT64
`RenderTarget` OBJECT pointers.** Two distinct C++ objects. It never compared
the D3D12 textures behind them.

**Two distinct `RenderTarget` objects resolving to one texture satisfy every
probe this project owns**, and that is precisely the state the capture shows:

| Instrument | Reported | Why it was satisfied |
|---|---|---|
| `50` `shared=0` | distinct | distinct C++ objects |
| `50` `pass targets: eye0=.. eye1=..` | distinct | same, object pointers |
| `57` `present source: distinct textures` | distinct | the two *present* textures ARE distinct — they are `vrPresentEyeTextures[0..1]`, resolved copies, both fed from the one shared source |
| `58` target stamp | "each half samples its own eye's target" | true, and irrelevant: both `RenderTarget` objects carry the same texture |
| `67` capture: two RTV descriptor slots `heap16[41]`, `heap16[42]` | distinct | **two descriptors can point at one resource** |

**The `67` XML replay saw the two distinct RTV slots and could not resolve them
to resource ids — and I recorded that as a parsing limit rather than a finding.
That was the correct call: it is exactly where the bug was hiding.**

## THE MEASUREMENT NOBODY TOOK, FOR THIRTEEN HYPOTHESES

Every probe asked **"are these two things different?"** about a C++ object, a
struct member address, or a pointer. **Not one asked whether the two eye
targets own the same GPU texture.**

**Rule 4 grew a corollary today, three times over: an instrument that compares
identity must compare the identity that MATTERS.** `49`'s upload verdict
compared struct member addresses. Today's `VIEWPROJ GPU` line compared
`BufferPair::get()` results. `50`'s `shared=0` compares `RenderTarget` objects.
**All three are true on a broken build.**

---

## WHERE TO LOOK IN THE SOURCE

`rt64_workload_queue.cpp:1215-1221` — the eye targets are constructed here:

```cpp
if (vrStereo && (eyeColorTargets.size() < eyeTargetCount)) {
    eyeColorTargets.resize(eyeTargetCount);
    for (size_t i = previousSize; i < eyeColorTargets.size(); i++) {
        eyeColorTargets[i] = std::make_unique<RenderTarget>(
            interpolationTargetKey.address, Framebuffer::Type::Color,
            RenderMultisampling(), usesHDR);
    }
}
```

**Each `RenderTarget` is a fresh object, so `shared=0` passes.** But a
`RenderTarget` here holds no texture yet — its texture is created or fetched
later, and **that is where two objects can end up on one resource.** The
constructor takes `addressForName` (`67`: cosmetic), and RT64 keys real
textures elsewhere — `RenderTargetManager`, `setupTexture`/`resize`, and the
`RenderTargetKey(address, width, siz, type)` used at
`workload_queue.cpp:750`.

**All the eye targets are built with the SAME `interpolationTargetKey.address`.**
`67` proved that address is cosmetic *for naming*, but if anything downstream
keys a texture or a framebuffer by an address-derived key, two targets at one
address collide.

**Find where `RenderTarget::texture` is created or assigned, and what it is
keyed on. That is the bug.**

---

## THE GATE FOR THE FIX — write it before the code (`48` rule 2)

Whatever the fix, it must make **`-Flat -Offset 500`** produce:

```
PREDICTION: eye1 - eye0 = -0.2821 ndc = -94.2 px per 668-px half-frame
REQUIRED:   -94.2 px +/- 5, right eye further LEFT
TODAY:      0 px, correlation 1.0000 at dx=0
```

**What would a working build have to do differently to fail this?** It would
have to render two different images and present them to different halves — so a
build that still shares one texture cannot pass, and a build that fixes it
cannot fail. This gate cannot be satisfied by accident.

**And the instrument to add with the fix — the one that has been missing for
thirteen hypotheses:**

```
eye textures: eye0=<RenderTarget::texture.get()> eye1=<...>  sharedTexture=0|1
```

**Not the `RenderTarget` object. The texture it owns.** With the note that
`shared=0` on the objects has always passed and always will.

## Do NOT

- **Do not conclude the eye split, the matrices, the buffers, the descriptors or
  the present are broken.** All measured correct (`67`, `68`). Only the target
  texture is shared.
- **Do not "fix" `50`'s `shared=0` probe by deleting it.** Fix what it compares.
- **Do not trust any remaining "are these distinct?" probe** without checking
  what it actually compares. Four have now been found comparing the wrong thing.
