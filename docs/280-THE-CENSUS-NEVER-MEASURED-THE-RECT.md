# 280 — THE ADMISSION AND THE RECT ARE DIFFERENT NUMBERS. NEITHER FACT IS WRONG.

**2026-08-31. NO BUILD. NO LINE CHANGED.** Source read plus re-derivation of `279` §3's mapping.
This doc exists to discharge `279` §9's first owed item: **the reconciliation that `279` says must
be written before a line changes.** It proposes no fix.

> ## THE ONE-LINE RESULT
> **`[MEASURED]` from source: `278` §3's census and `279` §4's rect are computed from DIFFERENT
> GEOMETRY by DIFFERENT OPERATORS, and the census never prints a rect. "Admitted identically" and
> "clipped too narrow" are therefore not in contradiction — they are two statements about two
> different numbers, only one of which has ever been measured.**
> **The rect coordinates themselves have NEVER been compared between arms. That is the gap.**

---

## §1 — WHAT `bg.c:622-677` ACTUALLY BUILDS, AND WHAT IT OUTERSECTS AGAINST

`[MEASURED]`, source, `vendor/ge-decomp/src/game/bg.c`.

`sub_GAME_7F0B39BC(curroom, unk1, screensize, next)` — the function `279` names — is **not** where
a room's bbox is computed. It is the **accumulator**. It does exactly two things:

- **room already in the draw list** (`:636-646`): `bgRectOutersect(screensize, &list[i].bbox)`
  grows the incoming rect to the UNION with the one already stored, then writes the union back.
  **A room reached through two portals gets the union of both portals' rects.**
- **room not in the list** (`:657-678`): appends it and stores the incoming rect verbatim.

**The incoming `screensize` argument is NOT `g_CurrentPlayer->screensize` in the interesting
path.** `player.c:453-456` sets `g_CurrentPlayer->screensize` to a CONSTANT `(0,0)-(320,240)`
and **nothing in the tree ever writes it again** (one grep, whole `src/`, four writers, all in
`player.c`). It is the full 4:3 canvas, not the view. The rect that reaches `:622` from the live
traversal (`:4982-5016`, `:5153-5187`) is a **PORTAL-CHAIN rect**:

1. `sub_GAME_7F0B5864(portalnum, &bbox)` — projects the portal's own polygon (`sub_GAME_7F0B5528`
   transforms its points by `camGetWorldToScreenMtxf()` and clips them at `z = 0`), then takes the
   2D min/max of the on-screen points. Degenerate cases: **`onscreencount == 0` -> the rect is
   `(0,0)-(0,0)`**; an inverted rect -> **the whole of `screensize`**.
2. `bgRectIntersect(&screenbox, parentbox)` then `bgRectIntersect(&screenbox, &screensize)` — the
   chain is INTERSECTED down the portal path and finally clamped to the canvas.
3. What is stored is that chain product. `sub_GAME_7F0B3C8C` (`:868-873`, `:938-943`) hands it to
   `bgScissorCurrentPlayerViewF`, which truncates `min`, `ceil`s `max` (`:1919`), and
   `bgScissorCurrentPlayerView` (`:1945`) **clamps it to `viewleft..viewleft+viewx` and
   `viewtop..viewtop+viewy`** before `gDPSetScissor`. That clamp is where the `uly=120` in
   `279`'s two rects comes from — `[MEASURED]` both admissible arms log
   `VIEWPORT n64: vscale=(640,360) vtrans=(640,480) => implied 320x180`, i.e. `viewy=180`,
   `viewtop=30` = **canvas `120`**. The game was in its own letterboxed widescreen SCREEN mode in
   both. `279`'s "the top edge lands on the rect's `uly`" is that clamp, not a portal.

## §2 — WHAT `278` §3's CENSUS MEASURED, AND WHAT IT CANNOT SEE

`[MEASURED]`, source, `bg.c:5973-6006`. `GETV_CULLSTAT` prints, per frame:
room id, that room's vertex count, and **how many of the room's 3D bounding-box corners project in
front of the camera** (`bgProjectRoomCoordToScreen`, sign of `z`), aggregated into
`front/straddle/BEHIND` and the same split weighted by vertices.

**It never reads `dword_CODE_bss_8007FFA0[k].bbox`. Not one field of it. The rect is not in the
output.** The `[getv][order]` print (`:828-835`) prints `roomid/unk1/next/camz` — also no rect.

And the admission test itself, `bgIsRoomOnScreen` (`:2017`), is a **coarse 8-corner overlap test on
the room's 3D bbox**: it rejects only when **all eight** corners fail the SAME edge. It is
deliberately slack — a room half off-screen passes with one corner.

> **So: `278` §3 measured a slack boolean over ROOM BOUNDING BOXES. `279` §4 measured an edge of an
> INTERSECTED PORTAL-POLYGON CHAIN. Different inputs, different operator, different output — and
> the second was never printed in the arms that produced the first.**
> **NEITHER FACT IS WRONG. The contradiction was in reading the census as a statement about the
> rect.** `278` §3 remains a positive result about ADMISSION and about nothing else — which is
> exactly the scope `278` §7.1 already corrected itself to, and `00-STATE` §5 already records.

## §3 — AND WITH THE KNOB OFF THERE IS NO WINDOW TERM LEFT TO BLAME

`[MEASURED]`, source: **`configWidescreen` has exactly four use sites in the whole tree** —
`gfx_pc.c:3910` (viewport width substitution), `gfx_pc.c:4133` (the `k` stretch, full-width
scissors only), `lv.c:797` (`set_cur_player_aspect(gePortRealAspect())`, single-player only), and
its own definition at `port_support.c:203`. **With `GETV_WIDESCREEN=0` all three are dead**, and
the only window-derived quantities remaining are `ge_scale()` and `ge_offset_x/y()`, which are
applied to the scissor (`gfx_pc.c:4115-4118`) and to the viewport (`:3917-3920`) **by the same
expression**. Re-derived, per `279` §3's instruction — not re-litigated:
`ge_scale = min(2560/320, 1369/240) = 5.7042`, `/4` per 10.2 unit = **1.42604**;
`ge_offset_x = (2560 - 320*5.7042)/2 = **367.35**`. Both match `279` §3.

> **Consequence, and it is the sharp edge of this doc: with the knob OFF the entire fault is in
> GAME space, and game space has no window term in it. `279` §5's `[REPORTED]` "definitely not as
> much" at 4K therefore has NO available mechanism in the knob-off pipeline.** Either the reduction
> is not in the rects (different standing spot, a second contributor, or perception), or the
> four-site read above is wrong. **Both are testable and one is free.**

## §4 — THE MEASUREMENT THAT IS OWED, IN ORDER. NO BUILD IN STEPS 1-2.

**STEP 1 — THE UNCOVERED-CANVAS CENSUS. Offline, from dumps already on disk, no owner, no build.**
For one frame: take every `SETSCISSOR` in the dump, map each to canvas space, and compute the area
of the play area `(viewleft,viewtop)-(+viewx,+viewy)` that is inside **no** per-room rect. The
artifact is a region no room claimed; this counts it, in canvas px, resolution-free.
**Contract, stated before it runs (`15`, and `279` §7's demotion):**
- **RUN IT ON THE BORING FRAMES FIRST — `2849` and `4283`.** They are the negative controls
  (`279` §6). If a clean frame reports a large uncovered area, **the census is measuring the
  letterbox or the HUD and its verdict on `2290`/`2913` is void.** Print the uncovered rectangles,
  not just the total, so a failure is visible rather than plausible.
- Only then `2290` and `2913`. **Predicted:** `2290`'s uncovered region CONTAINS the slab at
  canvas `x >= 151.92`, `y` in `[119.9, ...]`. If it does not, `279` §4's match is a coincidence
  after all and this whole line closes.
- **ADMISSIBLE DUMPS ONLY**, re-verified this session by announcement, not timestamp:
  `V1` (`run_278_V1_widescreen_off.log`) -> `2290, 2849, 3582`;
  `R1` (`run_279_R1_4k_widescreen_off.log`) -> `2913, 4283`.
  `1573/1676/1693/1714` are announced by no log. The `00:2x` set is a 1280x960 session.

**STEP 2 — THE AMOUNT, WITH A NUMBER (`279` §5).** Step 1's uncovered area, in CANVAS px, for
`2290` (2560x1369) vs `2913` (3840x2160). **This is not yet a controlled A/B — the two frames are
different places in the level (`279` §5 says so), so a difference proves nothing on its own.**
What it can do is falsify: **if the two are of the same order, "resolution changes the amount" has
no support in game space and the `[REPORTED]` reduction must be sought elsewhere.**
**The controlled arm needs the owner and is STEP 3.**

**STEP 3 — THE ONE RUN THAT SETTLES BOTH ITEMS.** Same standing spot, same facing, `GETV_STAGE=29`,
`GETV_WIDESCREEN=0`, `GETV_SIMDIV=1`, artifact on screen, **F9 at 2560x1369 and again at
3840x2160** — two arms, two logs, one binary. **Prediction, stated in advance:** the per-room
scissor rects in the two dumps are the SAME CANVAS RECTS, because nothing in the knob-off path is
window-derived (§3). **If they differ, §3's four-site read is falsified and that is the finding.**

**STEP 4 — THE BLACK WALL, WHICH HAS NO DUMP AT ALL (`279` §6, `263` §1).** Not merged, not
inferred from, not measured against any of the above. **It needs its own F9, standing still, with
the black wall on screen.** Until then it is one `[REPORTED]` symptom with zero frames.

**ONLY AFTER STEP 1-3: the rect instrument.** The one-line-per-room print of
`dword_CODE_bss_8007FFA0[j].bbox` beside the existing `[getv][cull]` room line — the number the
census was always missing. **Proposed, not written. It is a build and the gate is `48`'s
one-behaviour-change; it is diagnostic-only and default-off.**

## §5 — WHAT THIS DOC DOES NOT DO
- **It proposes no fix.** `279` §9's condition is discharged by §2, not by a cause. **WHY a
  portal-chain rect would come out narrower than the geometry drawn under it is still unnamed**,
  and the two degenerate branches in `sub_GAME_7F0B5864` (`onscreencount == 0` -> a zero rect;
  inverted -> the whole canvas) are **noted, unmeasured, and must not be read as candidates.**
- It does not touch `GETV_WIDESCREEN`'s default. `00-STATE` §3 item 2's decision stands as written
  and is still an unmade one-line change.
- **STILL OWED AND STILL UNTOUCHED**, unchanged from `277` §9 / `279` §9: the two hoist sites
  driven; `277` §8's two free intro-skip audio falsifiers; the `MoveBond` executions-per-second
  counter; and `278` §6's hoist-1 read, still `[INFERRED]` source-only.

---

## §6 — RUN A, AND THE FINDING GENERALISES: IT IS NOT ALWAYS `lrx`

**`[MEASURED]`. `run_280_A1_2560_wsoff.log`, 2026-08-31 00:17, `277`'s binary (2026-08-30 20:05,
18,017,350 bytes). Streets 29, `GETV_WIDESCREEN=0`, `GETV_SIMDIV=1`, 60 Hz, window `2560x1369`
FROM LAUNCH (no maximise — V1 had to be maximised).**

**Self-verification, all four gates met:** `[getv] window: 2560x1369`; one `game_exit requested`
(`262` §5); **zero** `simulation held to` lines; and
`VIEWPORT n64: vscale=(640,360) vtrans=(640,480) | ours: x=367.333 y=171.125 w=1825.33 h=1026.75`.
**That `x=367.333` is the knob's positive gate** — with `GETV_WIDESCREEN=1` the offset collapses
toward 0. It also re-confirms `279` §3's mapping to three decimals without re-deriving it.

**Dumps, by announcement** (`grep -oh "dlgrab_[0-9]*\.txt"`), not timestamp:
`2655, 2762, 3197, 3209, 3283, 4371, 4453` — **seven, and they are three viewpoints, not seven.**
`[MEASURED]` `2655`/`2762` are byte-identical but for the frame number; `3197`/`3209`/`3283`
identical; `4371`/`4453` identical. **Standing still produced an identical display list, which is
what "standing still" was asked for and is worth having measured.**

### 6.1 — TWO MORE INSTANCES, AND ONE OF THEM IS ON `ulx`

| frame | hole's hard edge, canvas x | the frame's own rect | edge | `d` |
|---|---|---|---|---|
| `2290` (`279`, re-measured here) | **151.94** | `(4,120)-(152,696)` | `lrx` | **0.06** |
| `2913` (`279` §4) | 476.00 | `(400,120)-(476,544)` | `lrx` | 0.00 |
| **`3197` (A, new)** | **411.40**, contiguous run **523 rows** | `(4,120)-(412,840)`, 118 tris | **`lrx`** | **0.60** |
| **`4371` (A, new)** | **947.14** (slab's last pixel `1718`; rect's first is window `1719.2`) | `(948,120)-(1276,840)`, 182 tris | **`ulx`** | **0.86** |

**►► `279` §4's "both matches are on `lrx`, neither on `ulx`" IS SUPERSEDED, NOT CONTRADICTED.**
`4371`'s hole lies to the **LEFT of a rect's `ulx`** and stops dead at it. **The invariant is not
"the right edge" — it is "the hole is OUTSIDE a per-room rect and its hard edge is that rect's
boundary, on whichever side."** That removes every candidate cause that is asymmetric in x —
including anything shaped like `gfx_pc.c:4133`'s `k`, which only ever moves `x` and `width` from
the left, and which is dead at `GETV_WIDESCREEN=0` anyway (§3).

**DOES THE TEST DISCRIMINATE?** `[MEASURED]`, same rule as `279` §4: contiguous vertical
step-runs, then nearest rect edge. **`3197`: 7 distinct long edges, 3 match — and two of those
three are the pillarbox borders at canvas `-0.23` and `1279.53`, which are the VIEW edge and
match in EVERY frame including the clean ones. So one interior edge, and it matched at 0.60;
the other four interior edges are 90-148 canvas px away.** `2290`: same shape, one interior edge,
`d=0.06`. **`2849`, the clean control: 12 long edges, the only two matches are those same two
borders; the ten interior ones are 25-332 canvas px away.**
**`4371` is the weaker of the two new instances and is labelled so**: the step detector does NOT
find its slab edge — the boundary is dark-on-dark and below threshold — so its coordinate comes
from a colour-region measurement seeded by eye inside the slab (`c=(20,27,33)`, the same
see-through class as `2290`'s `rgb(16,24,32)`), 298 rows agreeing on the same last pixel.

### 6.2 — STEP 1's INSTRUMENT RAN, AND REFUSED ITSELF ON THE CONTROL FIRST

`repo\tools\dlgrab_scissor_census.py`. **Contract stated before the run, and the boring frames
(`2849`, `4283`) were run FIRST, per `279` §7.** It fired its own refusal on both:
**`FULLVIEW-GEOMETRY`: 3-4 spans carry 1,075-1,081 triangles under the FULL VIEW rect** (the sky
pass and the chr/props passes go through `bgScissorCurrentPlayerViewDefault`, `bg.c:906`), **so
the union of geometry-carrying rects is the whole view by construction and "uncovered area" is 0
in every frame — clean and faulted alike.**
**STEP 1 AS DESIGNED IS A NULL AND CANNOT SUPPORT OR REFUTE ANYTHING.** It is kept, because it
says so in its own output rather than printing a plausible 0. **`279` §5's amount question does
NOT have a free offline answer; it needs run B.**
What the tool IS good for, and what §6.1 used it for: the per-frame list of **sub-rects that carry
triangles**, with their triangle counts — the room-pass rectangles, separated from the pass-level
ones.

### 6.3 — UNCLASSIFIED, AND DELIBERATELY NOT MERGED
`2655` (the third viewpoint) shows **no interior rect-edge match at all** — its only long edges are
the two borders and one at `d=36`. By eye it carries **dark angular patches on a red brick wall**
which may be retail geometry (recesses) or may be the `[REPORTED]` black-wall symptom. **It is not
classified, not counted above, and not merged with anything.** `263` §1.

## §7 — RUNS B AND C. TEN FRAMES NOW. AND TWO THINGS DID NOT HAPPEN.

**`[MEASURED]` gates, both arms, `277`'s binary:** `run_280_A2_4k_wsoff.log` — `window: 3840x2160`,
one `game_exit requested`, zero `simulation held to`, **`ours: x=480 y=270 w=2880 h=1620`, which is
the value §4 STEP 3 predicted in advance, to the unit.** `run_280_C_blackwall.log` — `2560x1369`,
`x=367.333`, one exit record, zero `simulation held to`.
Dumps by announcement: **B -> `2209, 2221, 3178, 4213`; C -> `2186, 2259, 3478`.**

### 7.1 — THE CONTROLLED A/B DID NOT HAPPEN, AND MUST NOT BE CLAIMED
`[MEASURED]` B's frames carry **different rects and different triangle counts** from A's — B is a
different set of standing spots. **STEP 3's prediction (same spot, two resolutions, identical
canvas rects) is UNRUN, not met and not failed.** Anything below comparing 2560 with 4K is
confounded by position and is labelled so.

### 7.2 — THE TALLY: TEN FRAMES, AND THE EDGE IS ALWAYS A RECT'S
`[MEASURED]`, contiguous-step detector, then nearest rect x-edge, **borders and the `(4,...)`/
`(...,1276)` play-area inset excluded** — they are the view and match in every frame, clean ones
included:

| frame | window | interior long edges | matched | `d` (canvas px) | rect edge |
|---|---|---|---|---|---|
| `2290` | 2560 | 1 | 1 | 0.06 | `lrx` 152 |
| `2913` | 3840 | (279: 9 tested) | 1 | 0.00 | `lrx` 476 |
| `3197` | 2560 | 5 | 1 | 0.60 | `lrx` 412 |
| `4371` | 2560 | seeded | 1 | 0.86 | **`ulx` 948** |
| `2186` | 2560 | 1 | 1 | 0.67 | 316 |
| `2259` | 2560 | 1 | 1 | 0.67 | 316 |
| `3478` | 2560 | 1 | 1 | 0.70 | 248 |
| `3178` | 3840 | seeded (detector MISSED it: dark-on-dark, below threshold) | 1 | 0.00 | `lrx` 424 |
| `2849` | 2560 | 10 | **0** | 25-332 | — clean control |
| `2209` | 3840 | 1 | 0 | — | clean by eye |

**Eight faulted frames, eight matches, four different rect edges, both sides, two resolutions.
Two clean frames, zero matches.** `2655` and `4283` remain unclassified/clean.

### 7.3 — RUN C DID NOT CAPTURE THE BLACK WALL, AND THE NUMBER IS WHAT SAYS SO
I read `2259`'s central wall as darker than `2186`'s **by eye and was wrong.** `[MEASURED]` mean
RGB over the same canvas box `(420,240)-(780,520)`: `2186` luma **39.3**, `2259` **43.2**, `3478`
**38.4** — a 5% spread, and `2259` is the BRIGHTEST of the three. **There is no black wall in run
C.** All three C frames are the see-through class at one viewpoint.
**THE BLACK-WALL SYMPTOM STILL HAS NO DUMP. `279` §6 and `263` §1 stand unchanged.**

### 7.4 — AND THE AMOUNT STILL HAS NO NUMBER. SECOND INSTRUMENT, SECOND SELF-REPORTED FAILURE.
A hole-width metric (flat-colour run outward from the matched edge, in canvas px) **latched onto
the pillarbox black instead**: six unrelated 2560 frames returned `rows agreeing = 167` identically
and widths that are simply the distance to the letterbox. **Discarded.** `279` §5's amount question
is **still open and still has no admissible figure** — that is now two designed instruments (STEP 1
and this) that failed and said so, and the honest statement is that **AMOUNT NEEDS THE CONTROLLED
SAME-SPOT ARM (§7.1), not another offline metric.**

## §8 — "I THINK IT'S CULLING" — THE SESSION LEAD IS RIGHT, AND THE DOCS ARE MIS-SCOPED

`[REPORTED]`, and it outranks the analysis (`HANDOVER` §5). **It is also what §1 and §2 of this doc
say from source, and the standing docs are the thing that is wrong here:**

- **The rect IS the culling.** It is built by the portal-visibility traversal (`bg.c:4982-5016`,
  `:5153-5187`), stored by the visibility accumulator (`:622-677`), and emitted as that room's
  `SETSCISSOR`. There is no separate "clipping" subsystem — **portal visibility decides WHICH rooms
  AND HOW MUCH of each.**
- **`278` §3 exonerated only the first half.** Its census counts rooms and vertices and **never
  reads the rect** (§2). `00-STATE` §5's *"THE WIDESCREEN HOLES ARE NOT THE ROOM-VISIBILITY PASS"*
  is **too broad as written** and should read *"not the room ADMISSION half of it"*. `278` §7.1
  already flagged its own over-correction; this is the same error one step further on.
- **Ranking, per rule `16`:** the lead has now put culling ahead of the renderer twice.
  **`278` spent four arms inside the game and `279`/`280` have spent three sessions measuring an
  edge. Eight frames say the edge is a visibility rect's. Stop measuring it.**

### 8.1 — THE ONE BUILD THAT DECIDES IT. NOT A FIX. ONE BEHAVIOUR CHANGE, DEFAULT OFF.
**`GETV_ROOMSCISSOR=0` — force every per-room scissor to the full player view.** Two call sites,
both in `bg.c`: `:868-873` (primary pass) and `:938-943` (secondary/xlu pass), each currently
`bgScissorCurrentPlayerViewF(gdl, bbox.min.x, bbox.min.y, bbox.max.x, bbox.max.y)`; with the knob
set they call `bgScissorCurrentPlayerViewDefault(gdl)` instead. Diagnostic only, **off by default**,
prints its own banner when engaged (`17`, `133`, `268` §4: a knob not in the binary reads as a
clean null).
**WHAT IT DECIDES:**
- **Holes GONE** -> the rect is the whole cause, it is the visibility rect, and the question becomes
  *why is the chain product narrower than the geometry under it* — the two degenerate branches in
  `sub_GAME_7F0B5864` become admissible candidates at that point and not before.
- **Holes REMAIN** -> the rect is a bystander and eight `0.00-0.86 px` coincidences share an
  upstream cause with it. **That would be the more valuable outcome and it is the reason to run it.**
**WHAT ELSE IT WILL DO, STATED IN ADVANCE SO IT IS NOT READ AS A SECOND FAULT:** without per-room
scissors the painter's ordering (`sub_GAME_7F0B3C8C`'s buckets) has nothing containing it, so
**rooms will overdraw each other and the picture will be wrong in NEW ways.** That is expected.
The gate is the SLABS, not the picture. **It must never ship on.**
**ITS OWN FALSIFIER:** with the knob set, a fresh F9 dump must contain **no per-room sub-rect
carrying triangles** — `repo\tools\dlgrab_scissor_census.py` prints that list directly. If sub-rects
are still there, the knob did not take and the arm is a clean null.
