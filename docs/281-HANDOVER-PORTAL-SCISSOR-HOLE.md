# 281 — Handover: the Streets hole is a portal scissor, and the fix is not at the scissor

**For the other session.** Self-contained. They do not need `277`–`279`.

---

## One line

The see-through slab is the neighbor room getting **admitted in 3D** and then **cut in 2D** by a portal screen-box that is too tight. The box is too tight because the portal projector **drops** verts behind the camera instead of **clipping** them. Do not patch `SETSCISSOR`. Patch the projector.

---

## The concept (if they do not have it)

GoldenEye does not have a modern visbuffer. A level is rooms connected by **portals** (doorway polygons).

Every frame:

1. **Vis / admission (3D).** “Can I see room B through this doorway?” Plane test + frustum. If yes, room B’s triangles go in the display list. This path is **correct**. Do not touch it.
2. **Scissor (2D).** “When I draw room B, only color the pixels inside this rectangle.” The rectangle is supposed to be the screen projection of the doorway. That way room B cannot paint over room A’s walls.

The hole is step 2 using a rectangle **smaller than the doorway as rasterized**.

Imagine a door. Room B is allowed to draw. The clip rect covers only the left two-thirds of the door. The right third never gets room B’s pixels. Whatever was already in the framebuffer shows through — sky/stale `rgb(16,24,32)`. That strip is axis-aligned because a scissor is an AABB, not because a wall is axis-aligned.

**Two tests, two shapes.** Admission uses the 3D portal. Scissor uses a 2D min/max of some projected points. They can disagree. They do.

```
screen:  [---- room A walls ----| DOOR |---- room A walls ----]
                                |      |
scissor:                        |<--->|      ← too short
                                |      |xxxx ← hole (stale/sky)
                                |  B   |
```

---

## What is already measured (do not re-open)

- Artifact edge = `SETSCISSOR` **`lrx`**, to **0.00 native pixels**, in two frames, two resolutions, two places.
  - `dlgrab_2290` (2560×1369): canvas x `151.92`, rect `(4,120)-(152,696)`
  - `dlgrab_2913` (3840×2160): canvas x `476.00`, rect `(400,120)-(476,544)`
- The hole is **outside** the rect, past `lrx`. Not `ulx`.
- `ulx=4` / `uly=120` are `screensize` clamps (play-area inset + the game’s own 16:9 letterbox). Those edges are innocent.
- Mapping `ulx/4 * ge_scale() + ge_offset_x()` is validated. Not a `gfx_pc.c` bug.
- ~78 canvas pixels wide on `2290`. Not off-by-one, not inclusive/exclusive `lrx`, not floor vs ceil.
- Widescreen-off. Existence is in **canvas space**. Resolution changes how many window pixels it covers, not whether the rect is wrong.
- A second symptom (black texture over a white wall) has **no dump**. Different bug. Do not merge.

---

## Where in code (wrong site vs right site)

**Wrong:** `bg.c` ~622–677, “outersect room 2D bbox with `screensize`,” then `gDPSetScissor`. That code **clamps a box that is already too tight**. Intersect/clamp cannot invent an `lrx` of 152. Widening here, deleting the scissor, or padding N pixels will either leak room B over room A or not fill a 78px gap.

**Right:** the function that **builds** the portal screen box. In the decomp it is `sub_GAME_7F0B5864` (often still under that name or `bgGetPortalScreenBbox` / similar). Find it by this fingerprint:

- reads `table_for_portals[portalnum]` cache
- generates portal points, **twice**, at `+thickness` and `-thickness` (`sub_GAME_7F0B5528`)
- loop: `if (points[j].z <= 0.0f) { project; expand min/max }`
- if no points kept → empty; if min>max → **full `screensize`** (fail-open)
- writes cache, returns count

Caller then does the correct thing:

```c
bgRectIntersect(&screenbox, parentbox);
bgRectIntersect(&screenbox, &g_CurrentPlayer->screensize);
```

So if the projector returns a tight box, everything downstream is faithfully tight. If the projector returns `screensize` on a straddle, the caller still intersects with the **parent** scissor — that is the safe conservative fallback.

---

## Why that loop is wrong

N64 camera looks down **−Z**. `z <= 0` means “in front.” Verts with `z > 0` (behind the camera) are **discarded**, not clipped to the near plane.

If every portal vert is in front, min/max of projections **is** a conservative AABB. Fine.

If the portal (or the ±thickness copy — this fires when you stand *close* to a doorway) **straddles** the camera plane: the AABB of the surviving verts is **not** a bound of the clipped opening. Near-plane clip edges can run to the screen border. Vis still admits room B. Draw scissors too small. Hole on whichever edge lost the dropped verts. Streets alleys put portals in your face, so this is the level that shows it.

The same function **already fail-opens to full `screensize`** when *all* verts are behind or the box is degenerate. It just does not fail-open for the **partial** case, which is the case you have.

---

## Solution

Two patches. Prefer 1. Ship 2 if they will not clip a polygon today. Do not do both blindly.

### 1. Correct: clip the portal polygon to the near plane, then AABB

In the projector, replace “drop `z > 0`” with Sutherland–Hodgman (or edge split) against `z = z_near` (`z_near` slightly less than 0, e.g. `-0.1` in camera space so the later divide is safe):

- For each edge of the portal polygon (and the ±thickness copy):
  - both in front → keep end
  - both behind → drop
  - crossing → keep the intersection point on `z = z_near`
- Project the clipped verts (all have `z <= z_near`)
- min/max as now
- empty after clip → reject portal (return 0)
- then let the caller intersect with parent / `screensize` as now
- **invalidate / don’t trust** `table_for_portals` cache until this is proven; the cache stores the bad box

This is the original intent of a portal scissor. Room B is allowed exactly the pixels of the opening, including when the camera is in the doorway.

### 2. Minimum shippable: fail-open on straddle

Same function, after the loop, before writing the cache:

```c
/* if any generated point was behind the camera AND at least one
   was in front, the AABB of the front points is not conservative */
if (straddling) {
    screenbox = g_CurrentPlayer->screensize; /* caller will intersect parent */
}
```

Effects:

- Hole goes away (scissor becomes parent box, which already covered the doorway).
- Room B may overdraw slightly around the doorframe. Z-buffer usually hides it; if you see a thin leak on the frame, you still want patch 1.
- Cheap. Matches a fallback the function already has. Safe on PC; original N64 avoided it for fill rate.

**Do not** pad by N pixels. **Do not** delete all `SETSCISSOR`. **Do not** “fix” `gfx_pc.c` scale/offset. **Do not** change admission. **Do not** merge the black-wall symptom into this.

---

## How they confirm in one F9 before/after

Stand still in a hole. Dump the matching `SETSCISSOR` and:

- portal id, each vert camera `z`, kept/dropped, projected `xy`
- `gSPVertex` screen AABB under that scissor

**Before:** some `z > 0` dropped, kept `max.x` == `lrx`, submitted verts extend past `lrx`.

**After (patch 1 or 2):** scissor `lrx` >= submitted verts `max.x`; hole gone.

If every vert is already in front and the box is still short, this diagnosis is wrong — stop and look at the portal cache / a union that never ran. Do not apply 1 or 2 in that world.

---

## VR note (since that is the destination)

Per-eye cameras mean **two** portal boxes per portal. A too-tight AABB that is a 78px slab on a 2D blit becomes a stereo depth-discontinuity (the hole is at different canvas x per eye). Patch 1 is the one that still works with two IPD-offset views. Patch 2 (fail-open) overdraws more per eye and will leak more in stereo. Do the clip.

---

## What they must not do

If they come back with any of the following, they did not read this:

- padded `lrx` by 1
- turned off scissors
- changed `ge_scale` / `ge_offset_x`
- patched `bg.c` ~622–677 (the clamp, not the projector)
- merged the black-wall-over-white-wall symptom into this bug
- changed vis / admission

---

## Provenance (from `279`)

| item | value |
|---|---|
| Edge identity | portal `SETSCISSOR` `lrx`, 0.00 native px |
| Frames | `dlgrab_2290` (2560×1369), `dlgrab_2913` (3840×2160) |
| Named clamp | `bg.c:622-677` (not the fix site) |
| Named projector | `sub_GAME_7F0B5864` (fix site) |
| Symptom class | see-through sky/stale slab only — not the black-wall symptom |
| Widescreen | `GETV_WIDESCREEN=0` |
| Mapping | `x = ulx/4 * ge_scale() + ge_offset_x()` — validated at two resolutions |
