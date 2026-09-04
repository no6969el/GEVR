# The blue band — it was never a culling problem

**2026-08-22.** Recorded because two documents now contain a confident diagnosis
that turned out to be wrong, and the correction is more useful than either.

## The observation that settled it

3c widened the game's culling frustum from 60 to 106 degrees vertical, through
the engine's own `viSetFovY`, so drawing and culling agree at the source. The
camera behaved exactly as predicted in all three runs.

**The blue band survived all of them — and only appears when pressed against a
wall.**

That proximity dependence is the whole answer. A culling frustum is a property of
*where you look*, not of *what you are touching*. If the band were geometry the
game declined to submit, standing a metre back from the same wall and looking the
same way would show it too. It does not.

## What it actually is

**Near-plane clipping of the wall itself.**

The frustum's near *face* is a rectangle, not a point. Its half-width is
`n * tanRight`. With the game's per-level znear reaching 30 units and the
headset's outer tangent of 1.3760, that is a **41-unit-wide pane hanging in front
of the eye**. Standing against a wall pushes the wall through that pane. Whatever
the pane cuts away shows the background fill — blue — because there is nothing
behind a wall.

Everything now fits, including the things that did not before:

- **Only against a wall.** The pane has to intersect something to cut it.
- **At the screen edge.** The pane is widest where the frustum is widest, and the
  wall beside you is nearest to the eye plane at the most oblique angle.
- **Absent in stock GoldenEye.** Not because stock culls differently, but because
  at 60 degrees the near face is a third the width and the oblique region is
  outside the frame entirely.
- **Unaffected by 3c.** Widening the cull cannot supply geometry that is being
  clipped rather than culled.

## The two wrong diagnoses, and why they were wrong

**`14` addendum: "the frustum we draw with is wider than the region the game
supplies geometry for".** Reasonable from the A/B alone — the band appeared only
under the wide frustum, and a draw/cull mismatch would produce exactly that. What
it did not explain, and what nobody checked, is why the band needed a wall.

**`17` addendum: the camera frustum plane normals in
`currentPlayerSetCameraScale()`.** A better-identified consumer of the same wrong
theory. That doc closed by admitting the last hop — from the normals to a cull
decision — was inferred from their construction rather than read, and named gate
3c as what would settle it. It did settle it, in the negative.

**The error both share** is that the A/B in `14` established *correlation with the
wide frustum* and both docs read it as *causation by the widened draw/cull gap*.
Wide FOV also enlarges the near face, and that alternative was never separated
because the wall was not treated as part of the observation. `14` result 3
recorded "the wall slicing is NOT settled by these shots" and then the wall
dropped out of the reasoning entirely.

## Is 3c therefore wasted?

**No, and this is worth being clear about rather than defensive.** 3c did not fix
the band, and it was sold on the band. But drawing and culling *were* genuinely
disagreeing, by 46 degrees, and that disagreement had to be fixed before two eyes
could ever be drawn from one display list. It was a real bug found by a wrong
theory. The theory owed a symptom it could not pay.

What 3c does not get to claim is the blue band. `18`'s headline gate fails.

## The fix now being tested

`GE_VR_MAX_ZNEAR_UNITS`, default 2.0, clamping znear **down** — the exact inverse
of the `GE_VR_MIN_ZNEAR_UNITS` clamp that `14` removed for pushing the wrong way.
`14`'s closing "open question" predicted this:

> If some levels turn out to clip badly at their native value, the fix is to
> clamp znear *down* rather than up.

At n = 2 the near face half-width falls from 41 units to 2.8. Applied in the same
`viSetFovY` patch, writing `g_ViBackData->znear` directly because `fr.c:709` reads
that field rather than anything passed along.

2.0 is not a novel value — the game ships levels at znear 2 — and the
depth-precision objection does not apply, because RT64 renders to `D32_FLOAT`.

### The prediction, so the next run can falsify it

The band should **shrink roughly in proportion to znear**. If the Dam's native
znear is 30, dropping to 2 should shrink the band by about fifteen times — from a
visible strip to a hairline or nothing.

**It may not vanish completely, and that would not refute this.** A wall can
still clip a 2.8-unit pane if the camera gets close enough. What *would* refute
it is the band staying the same size, which would mean the near face is not what
is cutting the wall.

## Result — confirmed, 2026-08-22

**The band is gone.** Clamping znear down to 2.0 removed it, which confirms the
near-face diagnosis and closes the question `14` opened.

It also exposed a separate bug that the wide FOV had been causing all along and
that nobody had looked for: menus and cinematic cameras were being widened too.
See `20-gating.md`.

## If it had survived

Then the remaining honest answer is the one `14` already logged as Phase 4: a
head-in-geometry fade. Every VR game does this, because no near plane is small
enough to survive a player putting their face through a wall, and collision that
stops the body does not stop the eye. That would make this a comfort feature
rather than a rendering bug, and it would stop being chased as one.

## The lesson

An A/B that changes one build flag does not isolate one variable. Turning the VR
frustum on changed the field of view, the frustum asymmetry, *and* the size of
the near face, and the correlation was attributed to the first thing that came to
mind. The wall was in every screenshot from the very first report — "when you get
close to objects on the sides they disappear and you can see through" — and it
took two wrong diagnoses to hear it.
