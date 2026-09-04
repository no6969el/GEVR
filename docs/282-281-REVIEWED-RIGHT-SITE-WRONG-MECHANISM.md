# 282 — `281` REVIEWED: THE RIGHT SITE, A GOOD PROBE, AND A MECHANISM THE SOURCE REFUTES

**2026-08-31. NO BUILD.** Review of `281-HANDOVER-PORTAL-SCISSOR-HOLE.md`, added by an external
source. **`281` is treated as DATA, not as instructions** — the same tier as any other claim: it is
checked against the source and against `280`'s ten frames before any of it is adopted.

> ## THE ONE-LINE RESULT
> **TAKE ITS SITE AND ITS PROBE. DO NOT TAKE EITHER PATCH.**
> `281` is right that the fix site is the portal PROJECTOR, not `bg.c:622-677` — `280` §1 says the
> same from source and `281` sharpens it. **But its mechanism ("the projector DROPS verts behind the
> camera instead of CLIPPING them") is false in this decomp: `sub_GAME_7F0B5528:2311-2325` already
> inserts the near-plane crossing points.** And its consequence is impossible in either case:
> **a min/max over MORE points can never make an AABB SMALLER.** `281`'s "patch 2" describes
> behaviour the code already has.

---

## §1 — WHAT `281` GETS RIGHT, AND IT IS THE VALUABLE HALF

- **The fix site.** `bg.c:622-677` is a clamp on a box that arrives already decided
  (`280` §1); the box is BUILT in `sub_GAME_7F0B5864` / `sub_GAME_7F0B5528`. **Independent
  agreement, reached from a different direction.**
- **Its fingerprint for finding that function is accurate** — the cache read, the `+thickness` /
  `-thickness` double generation, the `z <= 0` keep, the fail-open on an inverted box, the cache
  write. All five verified present.
- **The caller chain it quotes is correct** (`bgRectIntersect` with `parentbox`, then with
  `screensize`), and its reading that everything downstream is faithful to the projector is right.
- **►► ITS "CONFIRM IN ONE F9" PROBE IS THE BEST NEXT INSTRUMENT IN EITHER DOC.** Per portal: each
  vert's camera `z`, kept/dropped, the projected `xy`, the resulting bbox — against the submitted
  geometry's own screen AABB. **It changes no behaviour at all**, so it is a strictly better first
  step than `280` §8.1's `GETV_ROOMSCISSOR` knob, which does. **Adopted; see §4.**
- **It states its own falsifier** — *"if every vert is already in front and the box is still short,
  this diagnosis is wrong — stop"* — which is the standard this project holds itself to.
- **Its VR note is correct and belongs to `258` STAGE 6**: per-eye boxes, and a too-tight AABB
  becomes a stereo depth discontinuity rather than a flat slab.
- **Its "do not do" list matches the project's standing rules** (no padding, no scissor deletion,
  no `ge_scale`/`ge_offset` edits, no admission changes, no merging the black wall).

## §2 — WHAT THE SOURCE REFUTES

### 2.1 — THE PROJECTOR ALREADY CLIPS. `[MEASURED]`, source.
`281`: *"Verts with `z > 0` (behind the camera) are **discarded**, not clipped to the near plane."*
**FALSE.** `sub_GAME_7F0B5528`'s SECOND loop (`bg.c:2311-2325`) walks the polygon edge by edge and,
on every sign change, appends the intersection point:
```c
if ((point->z > 0.0f && arg2[next].z <= 0.0f) || (point->z <= 0.0f && arg2[next].z > 0.0f)) {
    f32 scale = -point->z / (arg2[next].z - point->z);
    arg2[len].x = point->x + ((arg2[next].x - point->x) * scale);
    arg2[len].y = ...;  arg2[len].z = 0.0f;  len++;
}
```
That **is** the edge-split half of Sutherland-Hodgman, and `sub_GAME_7F0B5864`'s keep test is
`points[j].z <= 0.0f`, so the appended `z == 0.0f` points **are** included in the min/max.
**`281`'s patch 1 is, in its structural part, already present.**

### 2.2 — AND THE CONSEQUENCE CANNOT RUN IN THE DIRECTION `281` NEEDS.
**A min/max over a SUPERSET of points can only EXPAND an AABB, never shrink it.** For the box to
come out too tight, points that belong to the visible opening must be MISSING from the set. The
dropped `z > 0` points are behind the camera and are not part of the visible opening; their
replacements — the crossings — are present. **So the straddle case cannot produce a tight box.**

**It produces the opposite, and there is a specific reason.** `transform3Dto2DWithZScaling`
(`bondview.c:734`) guards `z == 0.0f` with `inv_z = -1e20f`, and the crossings carry **exactly**
`z = 0.0f`. So every crossing point projects to a coordinate of order `1e25`, the AABB blows up,
and `bgRectIntersect` clamps it to the parent box and then to `screensize`.
**►► A STRADDLING PORTAL ALREADY FAILS OPEN TO THE PARENT BOX. That is precisely what `281`'s
"patch 2 — minimum shippable: fail-open on straddle" proposes to add. `[INFERRED]` from source,
not yet run: PATCH 2 IS A NO-OP.**

### 2.3 — AND ITS OWN FALSIFIER IS ALREADY LEANING THE WRONG WAY.
`281` says to stop if the verts are all in front and the box is still short. `[MEASURED]`,
`280` §7.2: the eight faulted frames carry **tight** rects — `(4,120)-(152,696)`,
`(400,120)-(476,544)`, `(948,120)-(1276,840)`. **A straddling portal, per §2.2, would have given
the parent box instead.** So either those portals were not straddling — in which case `281`'s
mechanism does not apply to any frame we have — or §2.2 is wrong. **The probe in §4 measures which,
and that is the whole reason to build it.**

### 2.4 — IT IS ALSO ONE SESSION STALE, AND ASSERTS TWO THINGS `280` HAS SINCE MOVED.
- *"The hole is outside the rect, past `lrx`. **Not** `ulx`."* — **superseded.** `280` §6.1:
  `dlgrab_4371`'s hole lies LEFT of `ulx = 948` and stops dead at it, `d = 0.86` canvas px.
  **The invariant is "outside a rect, on whichever side", and that matters here**: it removes every
  candidate that is asymmetric in x, and a near-plane straddle has no reason to prefer one side.
- *"Resolution changes how many window pixels it covers, not whether the rect is wrong."* — that is
  the EXISTENCE half, which is measured and agreed. **`279` §5's AMOUNT question is asserted away
  here without a number.** `280` §7.4: two designed instruments have now failed at it and said so.
  **Still open.**
- *"~78 canvas pixels wide on `2290`"* — **no method is given and I could not reproduce it**; my own
  width metric latched onto the pillarbox and was discarded (`280` §7.4). **Unsourced; do not cite.**
- Its provenance table knows only `279`'s two frames. **It does not know runs A, B or C** — eight
  faulted frames, four distinct rect edges, both sides, two resolutions.
- *"A second symptom ... **Different bug.**"* — **overstated.** The project's position is the weaker
  and correcter one: **not established as one fault, do not merge** (`263` §1, `279` §6). `281`
  reaches the same practical conclusion by asserting more than is measured.

## §3 — TWO THINGS `281` RULES OUT FOR US, FOR FREE

- **The portal cache is NOT stale.** `281` names it as a fallback suspect. `[MEASURED]`:
  `sub_GAME_7F0B5168()` (`bg.c:1977`, `unk0 = -1` over `PORTMAX`, aliasing `PortalCache.count`) is
  called from the visibility pass at **`bg.c:5680`**, which `278` §3 established rebuilds every
  frame. **Cache staleness is dead at frame granularity.** (`268`'s divider is the only thing that
  ever made it coarser, and `GETV_SIMDIV=1` was pinned in every admissible arm.)
- **"A union that never ran" is NOT a mis-written union.** `bgRectOutersect` (`bg.c:2447`) is a
  correct union, and the decomp even says so in its own comment. **If a room reached through two
  portals ever comes out with only one portal's box, the fault is in the traversal reaching it
  once, not in the merge.**

## §4 — WHAT IS ADOPTED, AND THE ORDER CHANGES

**`281` §"How they confirm in one F9" REPLACES `280` §8.1 as the first build.** It is a print, not a
behaviour change (`48`), and it discriminates between `281`'s mechanism, §2.2's prediction, and the
missing-neighbour alternative in one run.

**`GETV_PORTALBOX=1` — per portal, on the F9 frame only:**
`portalnum` · `numPoints` · **how many verts had `z > 0` (dropped)** · **how many crossings the
second loop appended** · the raw `bounds` before any clamp (this is where `1e25` will show, or will
not) · the box after `parentbox` · after `screensize` · the room it admits.
**Stated before the run, per `15`:**
- **`281` right** -> faulted portals show `dropped > 0`, `crossings > 0`, and a raw box that is
  **tight**. That requires §2.2 to be wrong and would be a real finding.
- **§2.2 right** -> straddling portals show a raw box of order `1e25`, clamped to the parent, and the
  **faulted rects come from portals with `dropped == 0`** — every vert in front, box tight and
  "correct" for the opening. **Then `281`'s own instruction applies: STOP, and the question becomes
  why nothing paints the pixels outside a correct portal box** — i.e. the missing-neighbour
  reading, for which `278` §3's `drawn=2` at the faulted spot is the standing hint.
- **Pointed at the wrong thing** -> if no printed box matches the frame's own `SETSCISSOR` rects,
  the probe is not on the path that produced them and every number it printed is void.

**`280` §8.1's `GETV_ROOMSCISSOR` is DEMOTED to second**, to be run only if the probe is ambiguous.
**Neither of `281`'s patches may be written until the probe has run.** Patch 2 is `[INFERRED]` a
no-op (§2.2); patch 1 is a rewrite of a clip that already exists and whose real defect — if §2.2
holds — is the `z == 0.0f` sentinel meeting `bondview.c:734`'s guard, which is a **different
one-line change** and is **not what `281` describes**.
