# The near-plane clipping bug — diagnosed 2026-08-22

**Reported symptom, present since before step 3a:**

- characters disappear entirely when you get close to them;
- objects at the **sides** disappear when you get close, and you can see through
  them to the geometry behind.

**Cause: `GE_VR_MIN_ZNEAR_UNITS` was 10.0f.** The patch clamped the game's
per-level znear up to 10 game units. Everything nearer than that was clipped.

This is our bug, introduced with Phase 1 step 1. It is not stock GoldenEye and it
is not step 3a, which is host-side and inert.

## Why the original reasoning failed

The constant shipped with this justification, in `ge_vr_bindtest.c` itself:

> Clamping up costs no field of view (n cancels out of the x/y scale) and no
> visible near clipping: 10 units is well inside the player's own collision
> radius.

The field-of-view half is correct — `n` genuinely does cancel out of `[0][0]` and
`[1][1]`. Both other halves are wrong.

**"Well inside the collision radius" is the wrong invariant.** The collision
radius stops *the player* walking into geometry. It does not stop a character
walking into the player, and it does not apply at all to props brushed past on
either side. Those are exactly the two cases reported.

**The side asymmetry is the tell, and it confirms the diagnosis rather than
merely being consistent with it.** A near *plane* is perpendicular to the view
axis. An object off to the side at the same radial distance from the eye has a
smaller z than one straight ahead, so it crosses the near plane **sooner**. Any
diagnosis that predicted a uniform distance cutoff would predict objects
vanishing at the same range in every direction, which is not what happens. Only a
near plane produces "the ones at the edges go first".

**Whole characters vanishing, rather than being sliced, points at the second
victim.** The patch writes the clamped frustum into both the fixed-point `Mtx`
and the float `Mtxf`. `Mtxf` is what the game culls with on the CPU, so a raised
near plane does not merely clip triangles — it culls whole objects before they
are ever submitted. That is why a character pops out of existence instead of
being cut in half.

**The depth-precision argument does not apply to this renderer.** It is an
argument about the N64's 16-bit z encoding. RT64 does not reproduce it: render
targets use `D32_FLOAT` (`lib/rt64/src/render/rt64_render_target.cpp:513`). At
n = 2 there is precision to spare, and the shimmer the clamp was defending
against is not a threat from this direction.

## Why it matters more than it looks

A large near plane is the wrong direction for VR specifically. In a headset the
player can lean in and put their face against a wall or a character, which is a
thing people do within about ten seconds of putting a headset on. The old value
pushed the near plane exactly the wrong way for the thing being built, while
being nearly invisible in flat play — which is why it survived this long.

## The change

`GE_VR_MIN_ZNEAR_UNITS` is now `1.0f` and wrapped in `#ifndef`, so it can be
swept from the build line without editing the file:

```
#ifndef GE_VR_MIN_ZNEAR_UNITS
#define GE_VR_MIN_ZNEAR_UNITS 1.0f
#endif
```

At 1.0 the clamp never fires — the game's own per-level value (2..30) always
wins — so the projection passes through with the game's native near plane. The
clamp is kept rather than deleted because it is the right shape of control; only
its value was wrong.

Backup: `patches/ge_vr_bindtest.c.bak3znear`.

## What the test distinguishes

One build, one run, unambiguous either way:

- **Clipping gone** — it was our clamp. Confirmed and fixed.
- **Clipping unchanged** — that level's native znear is already at or above 1.0
  in a way that matters, i.e. this is stock GoldenEye behaviour on that level and
  never was ours. The per-level range goes up to 30, so some levels will clip
  natively and no patch value can help.

Test on the **same level and the same spot** as the original observation. The
znear is per-level, so comparing across levels proves nothing.

## Open question this leaves

The game's native znear is per-level and unknown to us at runtime; we only see it
via `srcA`/`srcB` in `geVrBuildProj`. If some levels turn out to clip badly at
their native value, the fix is to clamp znear *down* rather than up — the
opposite of what the constant was doing — and that has real depth-precision
consequences worth measuring rather than assuming. Not needed yet. Raised here so
it is not rediscovered.

## Lesson worth keeping

The failing claim was a comment asserting an invariant ("well inside the
collision radius") that was never tested and could not be tested from the flat
monitor it was written against. It sat in the source looking like a reason. When
a constant is justified by a claim about player behaviour, the claim is a
hypothesis, and it should say so.

---

# Addendum — the A/B against stock, 2026-08-22

Built with `GE_VR_MODE_OFF` and re-shot the same two locations. Restored to
`GE_VR_MODE_STEREO` afterwards.

## Result 1 — the znear fix is confirmed

Characters now come "a good distance closer" before vanishing. That was the
prediction and it held. `GE_VR_MIN_ZNEAR_UNITS = 1.0f` stays.

## Result 2 — the blue void band at the screen edge is OURS

> **The mechanism below is WRONG. Corrected in `19-blue-band.md`, 2026-08-22.**
> The band is ours, which this section gets right. It is *near-plane clipping of
> the wall you are pressed against*, not a draw/cull mismatch — the frustum's
> near face is a rectangle of half-width `n * tanRight`, up to 41 units wide at
> the game's largest znear, and a wall pushed through it shows the background
> fill. Step 3c widened the culling frustum and the band survived unchanged. The
> tell that was missed: it only ever appears against a wall, and culling does not
> care what you are touching. Original text follows.

In the Dam tunnel, the wide-frustum build shows a narrow full-height blue strip
at the extreme left edge, roughly 2% of the screen width, with the near wall
ending against it at a hard vertical line. **In the stock build the strip is
absent** and the wall runs continuously to the edge of the frame.

Blue is not geometry. It is the level's background fill — the same colour as the
Dam's water — showing where nothing was drawn at all.

That makes this **the first confirmed instance of the mismatch predicted in
`12-phase1-step3-design.md` §10**: the frustum we draw with is wider than the
region the game supplies geometry for, so the outermost sliver of the image has
nothing in it. It is not a near-plane problem and it is unrelated to the znear
constant.

Two candidate mechanisms, neither yet established:

- **Room and portal visibility.** `bgUpdateCurrentPlayerScreenMinMax`
  (`lib/ge/src/game/bg.c:4615`) computes `g_CurrentPlayer->screensize` purely
  from viewport dimensions — `viGetX`, `viGetViewLeft`, `viGetViewWidth` — and
  never consults the projection. `bgDetermineVisibleRooms` then culls rooms by
  projecting portals into that fixed screen box. Widening the projection changes
  where portals land in screen space without changing the box they are tested
  against.
- **Scissor.** `bgScissorCurrentPlayerView` is already patched upstream in
  `patches/widescreen.c`, using RT64's extended GBI `gEXSetScissor` with
  `G_EX_ORIGIN_LEFT` / `G_EX_ORIGIN_RIGHT` anchoring. If that anchoring does not
  account for the widened frustum, a sliver at the edge falls outside the
  scissor.

The narrowness of the band — a sliver rather than a missing room — leans towards
scissor. The mechanism is not being chased now, because **step 3c exists to fix
exactly this class of problem** and the band gives it a concrete acceptance test.

## Result 3 — the wall slicing is NOT settled by these shots

Inconclusive, and worth saying so rather than reading the pictures optimistically.
The two dam shots were taken from different positions (ammo 4|79 versus 3|86, and
the pillar edge falls at a visibly different screen fraction), as were the two
tunnel shots (4|79 versus 7|72). The vertical boundary at the pillar is
consistent with the pillar's own edge in both builds, not necessarily with a
clip.

Nothing here needs a re-shoot. The question is subsumed: a wide-FOV near plane
against a wall you are pressed into is a comfort problem in VR regardless of
whether stock GoldenEye also has it, and the standard answer is to fade the view
as the head enters geometry rather than to move the near plane. That is Phase 4
work and is now recorded as such.

## Consequences

1. `GE_VR_MIN_ZNEAR_UNITS = 1.0f` — keep. Confirmed fix.
2. The blue edge band is folded into **gate 3c**, whose pass criteria gain: *no
   blue background band at any screen edge while strafing along a wall.*
3. Near-plane-versus-head-in-wall is a Phase 4 comfort item (view fade), not a
   projection item. Logged, not scheduled.
4. `12` §10 called room and portal culling "the single biggest risk in this
   design". It has now produced its first visible symptom before a single line of
   3c was written, which is the cheap end of finding out.
