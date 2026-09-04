# Step 3c — plan, and a redesign

**2026-08-22. Research and plan only, no code.** `12-phase1-step3-design.md` §2
said 3c should widen the game's culling by rewriting the float `Mtxf` frustum
and then "verify `bgUpdateCurrentPlayerScreenMinMax` and
`bgScissorCurrentPlayerView`; do not assume the one change is sufficient".

**That plan was aimed at the wrong lever.** The game's culling frustum is not
derived from the projection matrix at all.

## Prior-art check that found it

`05` records the standing rule: check what already exists before designing.

**Perfect Dark shares GoldenEye's engine**, and `perfect-dark-pc-port/perfect_dark`
(MIT, Ryan Dwyer's decompilation) is a complete PC port with working widescreen
and FOV options — the same problem 3c has to solve, already solved once in the
same codebase. It does not touch projection matrices. It calls
`viSetFovAspectAndSize(fovy, aspect, width, height)`, the engine's own FOV entry
point, and lets everything downstream re-derive.

That prompted the obvious question: does GoldenEye have the equivalent? It does.

**Nothing is copied from the Perfect Dark port.** It was used as a signpost. The
code below is GoldenEye's own, from `lib/ge` (`n64decomp/007`), already a build
dependency.

## The chain that matters

```
viSetFovY(fovy)                                       fr.c:902
  -> g_ViBackData->fovy = fovy
  -> currentPlayerSetPerspective(znear, fovy, aspect) bondview.c:641
       -> c_perspfovy, c_perspaspect
  -> currentPlayerSetCameraScale()                    bondview.c:649
       -> c_scaley = sin(fovy/2) / (cos(fovy/2) * c_halfheight)
       -> c_scalex = c_scaley * aspect * c_halfheight / c_halfwidth
```

and, separately, once per frame inside `viSetupCurrentPlayerView`:

```
guPerspectiveF(g_viProjectionMatrixF, &g_viPerspNorm,
               g_ViBackData->fovy, g_ViBackData->aspect, ...)   fr.c:709
```

`c_scalex` and `c_scaley` are what build the **culling frustum's slope planes**,
at `bondview.c:1157-1206` — four tests turning a screen bounding box into view
slopes. That is the room and portal visibility test.

So:

| | Derived from |
|---|---|
| What gets **drawn** | `g_ViBackData->fovy` via `guPerspectiveF` |
| What gets **culled** | `c_perspfovy` via `c_scalex` / `c_scaley` |

**One variable feeds both — but only if the change goes through `viSetFovY`.**

`ge_vr_bindtest.c` rewrites the matrix *after* `guPerspectiveF` has run. The
drawn frustum widens; `c_perspfovy` never hears about it; culling keeps using the
stock 60 degrees. The two disagree, and the disagreement is visible exactly where
the drawn frustum exceeds the culled one — **the outermost sliver of the image.**

That is the blue band in `14`. Diagnosed, with a mechanism, from source.

## What this retires

`12` §10 called room and portal culling "the single biggest risk in this design",
with the failure mode "widening the frustum will not produce the missing geometry
and step 3c's gate will fail with no obvious fix".

The risk was real and it has already produced its symptom. **The fix is obvious
after all**, and it is the engine's own supported path. Risk retired, not by
argument but by finding the lever.

## The redesign

3c no longer hand-builds a superset matrix. It patches the FOV setter:

```c
RECOMP_PATCH void viSetFovY(f32 fovy) { /* widen, then original behaviour */ }
```

Every downstream quantity — projection matrix, `c_perspfovy`, `c_scalex`,
`c_scaley`, portal culling, screen extents, LOD scaling — re-derives from the
widened value automatically, because that is what the engine already does. The
patch stops fighting the engine and starts using it.

Three things this must respect:

1. **`viSetFovY` is called every frame.** `bondview2.c:7883` and eight sites in
   `front.c` call `viSetFovY(FOV_Y_F)`, and a comment at `bondview2.c:7879`
   confirms `lvlRender` re-sets it per frame. Setting FOV once would be
   overwritten immediately. Patching the setter is therefore not merely
   convenient, it is the only stable place.
2. **The front end calls it too**, from `front.c`. The existing `geVrInLevel()`
   gate applies, same as everywhere else.
3. **Zoom uses it.** `bondview2.c:3069` calls `viSetFovY(zoominfovy)` for scope
   zoom. Widening must be multiplicative on whatever is passed, never a constant
   assignment, or zoom breaks.

`c_lodscalez` also derives from `c_scaley`, so LOD distances shift with FOV.
That is arguably correct — a wider view showing more geometry wants more
aggressive LOD — but it is a behaviour change to watch for rather than assume.

## What moves where, finally

| Concern | Owner after 3c |
|---|---|
| Culling frustum, ~108 deg + margin | patch, via `viSetFovY` |
| Per-eye exact frustum | RT64 `ProjectionProcessor`, `overrideFrustum` on |
| Per-eye view offset | RT64, already working (`15`) |
| Matrix rewriting in `currentPlayerSetProjectionMatrix` | **removed** |

The hand-built asymmetric frustum in the patch is retired. Its maths does not
move to RT64 — RT64 already has it, written in 3b and currently switched off.
That is the cleanest outcome available: the two halves stop overlapping and each
lives where it can see what it needs.

## Gate 3c

1. **Control run unchanged** with the widening factor at 1.0.
2. **No blue background band at any screen edge** while strafing along a wall,
   in the tunnel spot from `14`. This is the headline test.
3. **No geometry popping in at the edges** when turning.
4. Frame time watched on a dense level — Surface or Streets, not the Facility.
   `05` predicts display list overflow becomes likelier, and this step makes the
   culled volume genuinely larger for the first time.

## Open question worth stating before writing it

`viSetFovY` takes a *vertical* FOV and derives horizontal from `aspect`. The
headset's frustum is asymmetric per eye and its union is not expressible as one
symmetric fovy/aspect pair. The cull superset does not need to match the eye
frustums exactly — it only needs to *contain* them — so a symmetric superset that
is slightly too generous is correct and costs only some over-submission. Worth
saying out loud so the mismatch is not later mistaken for a bug.

---

# Addendum — the mechanism, corrected while implementing

Written before reading `patches/widescreen.c`. Two corrections, one of which
changes the diagnosis above.

## Correction 1 — the portal screen box was already widened upstream

This doc reasoned that `bgUpdateCurrentPlayerScreenMinMax` computes the room and
portal culling bounds from viewport dimensions alone, so widening the projection
would leave portal culling behind.

**That path is already handled.** `widescreen.c:137` carries a
`RECOMP_PATCH bgUpdateCurrentPlayerScreenMinMax` — theboy181's widescreen work,
upstream in cblock85's fork — whose non-demo branch sets
`screenxminf = viGetViewLeft() + 320 * -4` and
`screenxmaxf = viGetViewLeft() + viGetViewWidth() + 320 * 4`. The screen box is
blown out by +/-1280, which makes the portal test effectively unbounded
horizontally.

So room and portal visibility is **not** the source of the blue band, and the
first-listed candidate in `14`'s addendum is wrong.

## Correction 2 — the actual consumer is the camera frustum normals

> **Superseded by `19-blue-band.md`.** This correction identifies the right
> consumer of `c_perspfovy` and the draw/cull disagreement it describes was real
> — 46 degrees of it — but that disagreement is **not** what produces the blue
> band. Gate 3c settled it in the negative, as the honesty note at the end of
> this section said it would.

`currentPlayerSetCameraScale()` (`bondview.c:649`) does more than set
`c_scalex` / `c_scaley`. Its last eight lines build the **camera frustum plane
normals**:

```c
fVar2 = c_halfheight * c_scaley;
fVar4 = 1.0f / sqrtf(fVar2 * fVar2 + 1.0f);
c_cameratopnorm  = { 0, fVar4, fVar2 * fVar4 };

fVar5 = -c_halfwidth * c_scalex;
fVar4 = 1.0f / sqrtf(fVar5 * fVar5 + 1.0f);
c_cameraleftnorm = { -fVar4, 0, -fVar5 * fVar4 };
```

These are normalised view-space plane normals for the **real** screen half-width
and half-height — not the blown-out box `widescreen.c` supplies to the portal
test. They come straight from `c_scalex` / `c_scaley`, hence from
`c_perspfovy`, hence from the stock 60 degrees.

**That is the mismatch.** The projection draws a ~100 degree view while these
planes describe a 60 degree cone, and geometry outside the cone is never
submitted. The unrendered sliver sits exactly where the drawn frustum exceeds the
culled one.

The conclusion of this doc is unchanged and now rests on a better-identified
consumer: route the change through `viSetFovY` so `currentPlayerSetCameraScale`
recomputes these normals wide, and drawing and culling agree at the source.

## Honesty note

The decomp's `getPlayer_c_cameratopnorm` / `..._leftnorm` accessors have no
callers within the decompiled sources, so the consumers of these normals were not
traced to a specific culling call site. The derivation chain from `c_perspfovy`
to the normals is certain; the last hop, from the normals to a cull decision, is
inferred from their construction rather than read. Gate 3c's blue-band test is
what settles it.
