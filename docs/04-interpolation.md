# Frame interpolation — diagnosis, fixes, and what remains

**2026-08-22. Solved for practical purposes.** Rooms, props and characters
interpolate correctly at 90 and 180 Hz. Effects, HUD and the first-person view
model render correctly at native rate. Six fixes, described below in the order
they were found — the order matters, because three of them fixed problems an
earlier one created.

## Root cause

RT64 interpolates between the game's native 30/25 Hz frames and must know which
matrix this frame corresponds to which matrix last frame. Ports say so by tagging
matrices with a stable id via the `gEXMatrixGroup*` commands.

cblock85's fork defines the whole macro family in `patches/patches.h` — inherited
from an earlier Zelda/MM-lineage port — and called **none of it**. Zero call sites
across ten patch files. `interpolation.c` was `#if 0` around one function.

Untagged, `TransformGroup::matrixId` defaults to `G_EX_ID_AUTO`
(`rt64_transform_group.h:13`), which puts RT64 on the content-matching path:
`GameFrame::hashFromCall` (`rt64_game_frame.cpp:740`) pairs draw calls between
frames on `XXH3(colorCombiner, otherMode, geometryMode, triangleCount,
matrixIdHash)`. In GoldenEye a great many draw calls agree on all four, so the
hash collides between unrelated objects and RT64 interpolates one toward another.

## What was fixed, in order, and what each taught us

### Slice 1 — rooms. `applyRoomMatrixToDisplayList`, id = `roomID + 1`
Eight call sites: room geometry (`bg.c` x2), explosions, smoke, scorch marks,
bullet impacts, glass. Rooms were the most violent case because
`setupRoomTransformationMatrix` builds each matrix relative to the player —
`m[3][n] = room_pos[n] * scale - g_CurrentPlayer->current_model_pos[n]` — so every
room matrix changes every frame and a mismatch lerps between rooms metres apart.
**Result: rooms and level geometry became rock stable.**

### Slice 2 — props. `chrpropRender`, id from `PropRecord*`
The single dispatch every prop type passes through (`chrprop.c:427`). Also fixed a
problem slice 1 *created*: `gEXMatrixGroup` with `G_EX_NOPUSH` replaces the current
group and persists, and bg.c's order is
`chrpropsRenderPass(0)` / `bgRenderRoomPrimary` / `chrpropsRenderPass(2)`, so every
prop drawn after a room's geometry inherited that room's id.
**Result: crates and scattered items became stable.**

Two follow-on corrections, both real bugs:
- `withalpha` folded into the id. One prop is drawn more than once per frame
  (passes 0/1/2, opaque and alpha separately); two draws claiming one identity is
  the same mismatch we were removing.
- A **closing** `gEXMatrixGroupNoInterpolation` on the way out. `chrpropRender` is
  the only site where this is possible — it contains its own draw, whereas
  `applyRoomMatrixToDisplayList` returns before its caller emits geometry.
  **Result: large improvement across bullets, gun and HUD.**

### Slice 2b — characters need vertices, and must NOT get transform components
GoldenEye skins characters on the CPU. `chrRenderProp` (`chr.c:2871`) emits **no
`gSPMatrix` at all**; `modelRenderNodeDl` (`model.c:4249`) uploads already
transformed vertices via `gSPSegment(SPSEGMENT_MODEL_VTX, ...)`.

Consequences, learned the hard way:
1. `vert` must be `G_EX_COMPONENT_INTERPOLATE`, or a smoothly interpolated
   transform wraps vertices still stepping at 30 Hz — worst exactly when animation
   is fastest, i.e. a character being shot.
2. `pos/rot/scale/skew/persp` must all be **SKIP**. A character's group has no
   matrix of its own, so those components refer to whatever matrix was last
   loaded, which several props share while each claims a distinct id. Setting them
   made characters *worse*.

Characters therefore get SKIP on every transform component, INTERPOLATE on vert
and tile. Rigid props keep the full `DecomposedVerts` tag.
**Result: characters went from very glitchy to much better.**

### Slice 3 — HUD. `bondviewRenderGaugeBars`, `gEXMatrixGroupNoInterpolation`
Its geometry is rebuilt every frame by `buildGaugeBarDL`, the worst case for
content matching. A HUD element in a fixed ortho projection should not interpolate
at all. Body copied verbatim from the decomp; only the tag added.

### Slice 4 — renderer-side default for untagged world matrices
Effects kept flickering: muzzle flash (`sub_GAME_7F061E18`, 284 lines), tracers,
glass shards, blood, scorch marks. Short-lived geometry is the worst case for
content matching — a flash that exists for one or two frames has no previous-frame
partner, so RT64 drops it on in-between frames, which reads as **flicker** rather
than ghosting.

Tagging each meant transcribing five more game functions including a 284-line one.
Instead, `rt64_game_frame.cpp` now treats an untagged **world** group as
`G_EX_ID_IGNORE` (draw as-is at native rate) rather than `G_EX_ID_AUTO`, behind
`GE_UNTAGGED_WORLD_IS_IGNORE` (default 1, set 0 to revert):

- `buildCallHashMap` — an AUTO world group no longer opts into transform matching.
- `buildTransformIdMap` — AUTO world groups go to `ignoredIdVector`.

**Critically, only the world path is touched.** The view/projection group is
handled separately at `rt64_game_frame.cpp:458-468` and still keys on
`G_EX_ID_AUTO`, so camera interpolation is unaffected. A naive flip of the
`TransformGroup::matrixId` default would have hit both and cost the smooth camera.

This converts the remaining work from an open-ended transcription job into a
**whitelist**: untagged is safe-but-stepped, and we tag things deliberately when
smoothness is worth it.

### Slice 5 — a fence in front of the first-person view model
Symptom: the gun's slide ghosted as it cocked back, and the hand chop left a faint
duplicate hand above the arm. A **ghost, not a flicker** — so the view model was
still being interpolated, which after slice 4 means something handed it a real id.

It inherited one. Slice 1 tags room geometry and never closes the group, because
`applyRoomMatrixToDisplayList` returns before its caller emits the geometry — there
is no "after" to close in. So everything drawn once the world pass finishes, gun
and hands included, still claimed the last room's identity, and RT64 paired the
hand's vertex buffer with whatever else carried that id.

`gunRenderCasings` (15 lines) runs immediately before `gunRenderFirstPersonGunModels`
on the same Gfx pointer (`bondview2.c:8953-8954`), so it now emits a closing
`gEXMatrixGroupNoInterpolation`. The view model itself is 112 lines and leans on
struct fields absent from `patches/structs.h`.

`CasingRecord` is redeclared inside `interpolation.c` (VERSION_US branch of
`gun.h:242`, 160 bytes) because the patch headers lack it. **If shell casings ever
misbehave, suspect that layout first.**

**Result: ghosting gone from the gun and hands.**

### Slice 6 — bullet impacts get their own id band (2026-08-22, built, not yet run)

The cheap win that had been sitting on the list. It turned out to need one idea
the earlier slices did not have, so it is worth reading before the next one.

`explosionRenderBulletImpactOnProp` (`explosion.c:2201`, ~95 lines) batches by
room: when the room changes it calls `applyRoomMatrixToDisplayList`, then emits
`gSPVertex` + `gSP2Triangles` per impact. So every bullet hole in room R is drawn
under id `R + 1` — **the same id as R's own walls**, and the same id the scorch
buffer (`:1888`), prop explosions (`:886`) and smoke (`:1499`) hand out. Four
unrelated kinds of geometry claiming one identity is exactly the collision slice 1
existed to remove, reintroduced one level down.

**Batching by room is not the bug and was left alone.** Every impact in a room
shares one matrix, so one group per room is the right shape — the same shape that
made room walls stable. What was wrong was the namespace.

So `applyRoomMatrixToDisplayList` now emits `roomID + 1 + g_geRoomIdBias`, a
global set by a caller and cleared on the way out. Bands are `0x10000` apart;
room walls keep bias 0, so **slice 1's output is bit-for-bit unchanged** and
nothing that currently works can regress. `explosionCallRenderBulletImpactOnProp`
(`explosion.c:2299`, four lines, the `arg1 == NULL` world entry point from
`bg.c:678`) sets `GE_IDBAND_BULLET_IMPACT`, calls through, clears it, and — because
this wrapper **contains its own draw** — closes its own group on the way out.

That fence is worth more than it looks: `bg.c:677-678` runs the scorch buffer
immediately before the impacts, so the fence catches the scorch pass's leak too,
for free. Slice 4 does not help here — it demotes untagged **AUTO** world groups
to IGNORE, and a leaked room id is a real id, not AUTO.

**Every band setter must clear the bias on the way out.** A leaked bias silently
moves room walls into someone else's band, and the symptom looks like slice 1
regressing rather than like slice 6 misbehaving.

**Expected result:** bullet holes stop sliding across walls and stop dragging room
geometry toward them. If they instead start **flickering**, the pass is failing to
pair at all — set `GE_INTERP_BULLET_IMPACTS` to 0 to revert to inheriting the
room's id.

## The general lesson, for whoever picks this up

The vocabulary matters and it is diagnostic:

- **Swimming / sliding** — RT64 matched the wrong pair and interpolated between
  them. Fix: give the thing a stable id.
- **Ghost / duplicate** — same, but the mismatched partner is far away, or the
  thing inherited an id it does not own. Fix: stable id, or fence the leak.
- **Flicker** — RT64 could not pair it at all and dropped it on in-between frames.
  Typical of short-lived geometry. Fix: `G_EX_ID_IGNORE`.

And the structural rule that caused four separate bugs now: **`gEXMatrixGroup` with
`G_EX_NOPUSH` replaces the current group and persists until the next group
command.** Any tag leaks forward onto everything drawn after it. Only a function
that contains its own draw can close its own group.

Slice 6 adds a second rule worth carrying: **a shared tagging helper is a shared
namespace.** `applyRoomMatrixToDisplayList` serves eight callers, so "give it a
stable id" is not enough — the id has to be stable *and* unique to the kind of
thing being drawn. The bias band is the cheap way to get that without touching
the helper's callers.

## Remaining, in priority order

1. **First-person weapon, properly tagged.** Currently stepped. It is always on
   screen, so it is the highest-value remaining target. Needs per-hand ids and
   vertex interpolation inside `gunRenderFirstPersonGunModels` (112 lines,
   `gunfire.c:1489`) — the only remaining item worth a big transcription.
2. **Scorch marks.** `explosionRenderScorchBuffer` is 48 lines and still shares
   the room's band. Now a small job: give it `GE_IDBAND_SCORCH` the same way
   slice 6 did, either by patching the 48-line function or by finding a wrapper.
   Bullet impacts (the 4-line win) are **done** — slice 6.
3. **Glass shards** (43 lines), **flying particles** (41), **blood** (10). Each
   reaches `applyRoomMatrixToDisplayList` and so wants its own band.
4. **Muzzle flash / tracers** (`sub_GAME_7F061E18`, 284 lines). Probably fine
   stepped — a 1-2 frame flash gains little from interpolation. Low priority
   precisely because the function is huge and the payoff is small.
5. **The watch.** Deliberately deferred: Phase 3 re-renders it as a world-space
   panel for VR, so flat-mode polish there is likely throwaway work.

## Display list budget — the standing risk

Each tag costs **two** Gfx slots. `G_EX_COMMAND2` writes at `_cmd+0` and `_cmd+1`
and evaluates its `cmd` argument twice on purpose — that is what the bare
`(void)(cmd);` line is for — so the `gdl++` idiom advances by two. Props now cost
four (open + close). Slice 6 adds two more per frame, once, for the closing fence.

GoldenEye's display list buffers are fixed size. If a crowded level drops or
garbles geometry, suspect overflow before suspecting the tagging. Mitigation if it
happens: close the group once per pass rather than once per prop.

## Why this matters for VR

Flat play tolerates 30 Hz. A headset does not. This was on the critical path to a
comfortable build, and it is now in good enough shape that Phases 1-2 (stereo,
OpenXR) can proceed without it blocking.
