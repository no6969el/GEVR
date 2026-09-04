# 87 — THE SIX READS `86` §8 OWED, DONE

**2026-08-23, after `86`. All reads, no experiments, no launches, no headset,
no build. `86` §8 said do them before, not during. This is that.**

> # ►► CORRECTED BY `88` AND `90`. READ BOTH. ◄◄
>
> **`90` FALSIFIES FINDING 1'S LABELS AND THEY WERE MINE.**
> **`crosshair_x_pos` drives the BULLET** (`bullet_path_from_screen_center`,
> `gunfire.c:4846`, eight call sites, and the decomp's own comment says so).
> **`gun_azimuth_angle` drives the GUN MODEL'S POINTING**, not the shot —
> `field_A38/A3C/A40`'s five readers are the align, the muzzle flash, and a
> draw term. **The two-integrator finding SURVIVES; the labels on its two
> outputs were swapped.** And it matters: **the bullet is the CLAMPED
> quantity, so there is no unclamped shot path in GoldenEye and slice A2 is
> the only honest indicator past the clamp.** `90`.
>
> **`88` did read 7 and it falsifies finding 2 below.** The `field_FFC` overlap
> is real, but calling it a **COLLISION** was wrong: `gunfire.c:568` orients the
> gun on the axis through the gun position and the aim point, **by design, in
> stock code**. It is not two features fighting over one variable — **it is the
> coupling slice A1 was going to have to build, already present.** `88` §5.
>
> **`88` also closed `86` §5 A1's owed read 1 (`:6077` is aim mode, and the
> split is CONTROLLER CONFIG, not auto-aim vs manual), and read 8
> (`sub_GAME_7F0680D4` has NO callers — dead in the shipped game).**
>
> # ►► THREE OF THE SIX CAME BACK DIFFERENT FROM WHAT `86` ASSUMED. ◄◄
>
> | | |
> |---|---|
> | **THE AIM IS TWO INTEGRATORS, NOT ONE** | `86` §3.8 maps our `field_FFC` onto PD's `crosspos2`. **It is not the same quantity.** PD derives `crosspos2` from the SAME sum as the crosshair. **Ours has a SECOND, independently damped integrator** — `gun_azimuth_angle`/`gun_azimuth_turning` under `gunaimdamp`. **Writing `crosshair_x_pos` alone moves the crosshair and NOT the bullet.** `86` slice A1 recipe step 4 is incomplete as written |
> | **`field_FFC` ALSO MOVES THE GUN MODEL** | `gunfire.c:512-520`. The aim quantity is read back to build `gunofs`. **That is the engine's own turn-sway `79` fought and `85` worked around** — and it means A1 and the hand slices write to the same place. Rule 6, and nobody had checked |
> | **THE FOV PATCH *DOES* DISTURB THE PROJECTION** | Not `c_screenwidth` — **`c_scalex` and `c_scaley`**, by 106/60 = **1.7667**, every frame, under `geVrWorldCamera()` only. `viGetFovY` divides the widening out for the GAME's readback; **it does not divide it out of the camera scale.** Read 3 was live and the answer is yes |
>
> **And two came back BETTER than `86` hoped:**
>
> 4. **The ceiling query EXISTS**, is already called with the player's own eye
>    height, and the game **already auto-crouches** you under low geometry —
>    `autocrouchpos`. H2 option B has an existing consumer.
> 5. **The function A1 must patch is 69 lines, not ~85**, and
>    `crosshair_x_pos`/`crosshair_y_pos` have **no readers outside it at all**.

---

## READ 1 — `caclulate_gun_crosshair_position_rotation`, MEASURED

| | |
|---|---|
| Location | `lib/ge/src/game/gunfire.c:4666`, body `4667`–`4734` |
| **Length** | **69 lines**, brace to brace. `86` §8 said *"about 85 lines"* and flagged its own *"looks is not the standard this project uses"*. **Corrected: 69** |
| Callers | **two, both local.** `sub_GAME_7F067F58` (`:4752`, aim-lock path) and `sub_GAME_7F067FBC` (`:4775`, normal path) |
| Calls out to | `getPlayer_c_screenwidth`, `getPlayer_c_screenheight`, `getPlayer_c_screenleft`, `getPlayer_c_screentop`, `transformAndNormalizeByLength2Dto3D`, `sub_GAME_7F067AB4` — **six, all leaf-ish, none of them a patch target** |
| Globals touched | `g_CurrentPlayer`, `g_ClockTimer` |
| Control flow | two `if` blocks, two `for i < g_ClockTimer` loops, four clamp branches. **No switch, no recursion, no varargs, no float-return trampoline** |

**Verdict: `RECOMP_PATCH`-able, and cleanly.** It is a self-contained leaf with
six named callees and two named callers. `78` could not say this about
`gunUpdateAndFire`; it can be said here, from the source, at zero cost.

**It is a NEW name and therefore needs the long build** — read 6.

### AND THE THING THAT MATTERS MORE THAN THE LENGTH

**The function runs TWO independent damped integrators, not one.**

```c
/* the CROSSHAIR, damped by guncrossdamp  (gunfire.c:4692-4697) */
crosshair_x_pos   = crosshair_x_pos * guncrossdamp + turn_x;      /* x g_ClockTimer */
crosshair_angle.f[0] = crosshair_x_pos * (1-guncrossdamp) * W*0.5 + W*0.5;
    /* then CLAMPED to [3, W-4]  (4699-4715), then += c_screenleft */

/* the AIM, damped by gunaimdamp  (gunfire.c:4722-4727) */
gun_azimuth_angle = gun_azimuth_angle * gunaimdamp + turn_x;      /* x g_ClockTimer */
field_FFC.x       = gun_azimuth_angle * (1-gunaimdamp) * W*0.5 + W*0.5;
    /* NOT clamped, then += c_screenleft */
transformAndNormalizeByLength2Dto3D(&field_FFC, &coords, 1000.0f);
sub_GAME_7F067AB4(&coords);      /* -> hands[].field_A38/A3C/A40 : THE SHOT */
```

**Both are fed the same `turn_x`/`turn_y`. Both are integrated separately, with
different damping constants, from different weapon stats** (`CrosshairSpeed` vs
`AimLockSpeed`, `:4765-4766`).

> **THIS FALSIFIES `86` §3.8's MAPPING.** PD's `crosspos` and `crosspos2` are
> two *readings* of one sum. **Ours are two sums.** So `86`'s recipe step 4 —
> *"write `crosshair_x_pos` / `crosshair_y_pos`, never `crosshair_angle`"* —
> **steers the visible crosshair and leaves the bullet exactly where it was.**
>
> **A1 must pre-load BOTH integrators, each with its own damping constant:**
>
> ```
> crosshair_x_pos   = ndc_x / (1 - guncrossdamp)     /* the crosshair */
> gun_azimuth_angle = ndc_x / (1 - gunaimdamp)       /* the bullet    */
> ```
>
> **`38`'s inversion is still right — it just has to be applied twice.** And
> `86`'s corroboration of it from `bondgun.c:8408` still stands: the expression
> is the same, there are simply two places to put it.
>
> **A gate follows from this and it must go into A1:** *fire without moving the
> hand and confirm the crosshair and the impact point agree.* A build that
> pre-loads only one integrator passes every "the gun aims where I point" gate
> **by eye** and fails this one. Rule 2.

---

## READ 2 — WHO ELSE READS `crosshair_x_pos`, AND THE ONE NOBODY EXPECTED

**Every reference in `lib/ge/src`, `src`, `patches`, `include`:**

| Symbol | Readers outside the function | Writers outside it |
|---|---|---|
| `crosshair_x_pos` / `crosshair_y_pos` | **NONE** | `initBondDATA.c:287-288`, `player.c:379-380` — **zero-init only** |
| `gun_azimuth_angle` / `gun_azimuth_turning` | **NONE** | `initBondDATA.c:292-293`, `player.c:384-385` — zero-init only |
| **`crosshair_angle`** | **MANY** — `get_bullet_angle` (`:4783`), the two firing/spread paths (`:4839`, `:4865`, `:5185`, `:5211`), **the HUD** `gunDrawSight` (`:6214`) | **`sub_GAME_7F06802C` (`:4794`) and `sub_GAME_7F0680D4` (`:4818`)** |
| **`field_FFC`** | **`gunfire.c:512-520` — THE GUN MODEL'S OWN SCREEN OFFSET** | the same two functions (`:4795`, `:4820`) |

**Read 2's stated question is answered cleanly: `crosshair_x_pos` has no other
reader.** Writing it is safe. So is `gun_azimuth_angle`.

### BUT THE SEARCH TURNED UP TWO THINGS `86` DID NOT ASK ABOUT

**1. `field_FFC` IS THE VIEWMODEL SWAY.**

```c
/* gunfire.c:512 */
gunofs.x += (((field_FFC.x - c_screenleft) - W*0.5f) * itemstats->PlayZ) / (W*0.5f);
/* :514-521 — same for y, via PlayY above centre and PlayX below it */
```

> **The aim position and the gun's on-screen position are THE SAME QUANTITY in
> GoldenEye.** Perfect Dark keeps them apart (`gCtrlPos` places the gun,
> `crosspos2` aims it). **We cannot, without breaking one of them.**
>
> **This is `79`'s third wearer-diagnosed fault — *"it's still attached to other
> parts"* — named at source.** It is not a leftover sway to be suppressed; it is
> `field_FFC` arriving through `gunofs`, and `85` reached the same place from
> the other direction by hooking `gunofs`.
>
> **So A1 and G1/G2/G3 collide.** Whichever ships second must know the other
> writes here. **This is rule 6 and it is exactly the shape PD hit with
> `vrBuildGunRotation`** (`86` §3.7 item 4 / slice G2's third bullet) — except
> ours is worse, because theirs was two writers of one matrix and ours is two
> *features* wanting one variable to mean two different things.
>
> **The cheap answer, and it should be tested before anything clever:**
> `itemstats->PlayX/PlayY/PlayZ` are per-weapon multipliers on this term. **If
> they can be zeroed under VR, `field_FFC` stops moving the model and is free to
> mean aim only.** That is a read, not a build — and it is the first thing the
> A1 session should look at. **It is not yet done; it is the seventh read.**

**2. There are two OTHER writers of both quantities**, and they matter for
G-A1-2 (the "switch weapons mid-burst" gate):

- **`sub_GAME_7F06802C`** (`:4788`) recentres both to screen centre and re-fires
  `sub_GAME_7F067AB4`. **A hard reset to the middle.**
- **`sub_GAME_7F0680D4`** (`:4806`) sets aim from a **3D direction** — it builds
  a rotation matrix, takes its Z column ×1000, projects with
  `transform3Dto2DCoords`, and writes both. **That is A1's whole job, already
  written, in the engine.**

> **`sub_GAME_7F0680D4` is a world-direction-to-aim path that already exists.**
> A1 may not need to invert `transformAndNormalizeByLength2Dto3D` at all — it
> may only need to hand this function a direction. **It also writes
> `crosshair_angle` directly, bypassing the clamp**, which is a different
> answer to `86` §3.8's clamp question from either PD's or `76`'s.
> **Callers unknown — an eighth read, and a cheap one.**

---

## READ 3 — DOES THE FOV WIDENING DISTURB THE PROJECTION? **YES, AND NOT WHERE `86` LOOKED**

`86` §8 read 3 asks about `getPlayer_c_screenwidth()`. **That was the wrong
field to worry about, and the right worry underneath it.**

| Quantity | Set by | Disturbed by the patch? |
|---|---|---|
| `c_screenwidth`, `c_screenheight`, `c_screenleft`, `c_screentop`, `c_halfwidth`, `c_halfheight` | `currentPlayerSetScreenSize` / `SetScreenPosition` (`bondview.c:624-638`) | **NO.** No patch touches either function |
| **`c_scalex`, `c_scaley`, `c_recipscalex`, `c_recipscaley`** | `currentPlayerSetCameraScale` (`bondview.c:649`), **from `c_perspfovy`** | **YES** |

**The chain, from the patch:**

```c
/* patches/ge_vr_bindtest.c:493 — RECOMP_PATCH viSetFovY */
if (geVrWorldCamera()) { fovy *= GE_VR_CULL_FOVY_SCALE; }   /* 106/60 = 1.76667 */
...
currentPlayerSetPerspective(znear, g_ViBackData->fovy, aspect);   /* c_perspfovy = WIDENED */
currentPlayerSetCameraScale();                                     /* c_scale* from WIDENED */
```

```c
/* bondview.c:656-657 */
c_scaley = sinf(fovy/2) / (cosf(fovy/2) * c_halfheight);
c_scalex = (c_scaley * c_perspaspect * c_halfheight) / c_halfwidth;
```

**`viGetFovY` divides `GE_VR_CULL_FOVY_SCALE` back out** (`ge_vr_bindtest.c:566`)
**— for the GAME's readback only.** `c_scalex` and `c_scaley` keep the widened
value. That is deliberate and correct: culling and drawing want the wide
frustum. **But `transformAndNormalizeByLength2Dto3D` — the exact function A1
must invert — is built on `c_scalex`/`c_scaley`:**

```c
/* bondview.c:698 — and 86 §8's stated inverse is CONFIRMED exactly right */
y = (c_halfheight - (in->y - c_screentop)) * c_scaley;
x = ((in->x - c_screenleft) - c_halfwidth)  * c_scalex;
z = -1.0f;
```

### WHAT THIS MEANS FOR A1

1. **Self-consistency is preserved.** Invert the same `c_scalex` the forward
   transform used and the round trip is exact, whatever the FOV. **A1's
   arithmetic is safe.**
2. **But the pixel it produces is a pixel in the 106° CULLING frustum**, not in
   the eye's own frustum. **The crosshair drawn at that pixel by `gunDrawSight`
   (`:6214`) will not sit on the world point the eye sees**, because the eye is
   rendered through `VrEyeParams`, not through `c_perspfovy`. **The disagreement
   is the ratio of the two frustums and it is not small.**
3. **The gate follows:** *point at a marked world feature and confirm the drawn
   crosshair lands on it, per eye.* **This is the second-strongest argument for
   slice A2's world-space dot** — a HUD crosshair computed in the culling
   frustum is wrong by construction in a headset, and `86` §3.8's laser-dot
   finding now has a second, independent reason behind it.
4. **The gate is gated by `geVrWorldCamera()`** — `geVrInLevel() && !demoMode &&
   (CAMERAMODE_FP || CAMERAMODE_MP)` (`ge_vr_bindtest.c:449`). **Menus, demos
   and cutscenes use the unwidened scale.** Anything A1 measures must state
   which side of that gate it was on. `52`'s lesson: an instrument that latches
   on a menu reports a different frustum and says nothing about it.

**Also noted while there:** `znear` is clamped **down** to 2.0 under the same
gate (`:534`), so the near plane in VR is 2 units, not the level's. **That
strengthens `86` slice G3's `83` note** — the near plane is **2**, not ~10, so
a gun closer than 10 units is *not* clipped. **`83`'s "~10 units" is stale under
the VR gate. Rule 10, and it makes G3's trim range wider than `86` assumed.**

---

## READ 4 — `bwalkCanMoveUpwards`' COUNTERPART: **IT EXISTS, AND SO DOES AN AUTO-CROUCH**

There is no function of that name. **There is something better: the query it
would be built on is already called, with the player's own eye height.**

```c
/* bondview2.c:4418 — the player's ceiling test, as shipped */
stanTestLocusEdgeAboveY(
    &stan, collision_position.x, collision_position.z, collision_radius,
    bondviewGetPlayerDuckingHeightRelated(g_CurrentPlayer) + sp64) >= 0
```

and `bondviewGetPlayerDuckingHeightRelated` is `bondview2.c:9152` — **the exact
composition `86` §5 H2 quotes:**

```c
return player->eyeheight + player->field_88 + player->ducking_height_offset;
```

| The pieces | |
|---|---|
| **`stanTestLocusEdgeAboveY(tile, x, z, radius, yThreshold)`** | `stan.c:2574`. **Takes an arbitrary Y and answers whether geometry sits above it.** This IS the ceiling query. It is already called on the player, twice |
| `stanTestVolume` | `stan.c:1929`, annotated in-tree as *"Perfect Dark cdTestVolume"* — **the volume test, with explicit `ymin`/`ymax` arguments** |
| `stanTestLineUnobstructed` | `stan.c:1565` — **the LOS test**, `(tile, x, z, dest_x, dest_z, cdtypes, height, ...)` |
| `eyeheight` is written from the head | `bondview2.c:4564`: `eyeheight = headpos.f[1] * player_perspective_height + 7.0f` |
| Crouch is three states | `0`, `-60`, `FULL_CROUCH_OFFSET = -100` (`bondview2.c:6756-6768`), animated by `chrobjApplySpeed`. **Structurally identical to PD's three** (`86` §3.4) |

### AND THE FINDING THAT CHANGES H2's COST

```c
/* bondview2.c:2123-2126 */
if (stanGetLocusField0(&sp3C) != 0) {
    g_CurrentPlayer->autocrouchpos = CROUCH_SQUAT;
}
```

> **GoldenEye ALREADY auto-crouches the player under low geometry.** There is an
> `autocrouchpos` field, it is driven by the stan locus, and the movement path
> at `:2139-2143` already refuses a move whose head clearance
> (`collision_position.y + 175.0f`) is blocked.
>
> **So H2 option B is not "add a ceiling system". It is "write our head height
> into a field the game already tests, and let the existing auto-crouch fire."**
> `86` §5 H2 estimated *"a patch on the eye-height path, plus §3.4's crouch
> states"*. **The crouch states exist. The ceiling test exists. The auto-crouch
> exists.** The remaining work is the eye-height write itself.
>
> **This shifts the A-vs-B recommendation and the wearer should be told so
> before choosing.** `86` recommended A first because B was large. **B is
> smaller than it looked.** It is still the architectural change and still needs
> discussing — but not on the grounds `86` gave.

**Not established, and it is the ninth read:** whether `autocrouchpos` has a
consumer that would fight a written-in head height. Rule 6, and it is the exact
shape that has bitten this project five times.

---

## READ 5 — `GEOFLAG_BLOCK_SIGHT`' COUNTERPART: **NO SUCH FLAG. A DIFFERENT MECHANISM.**

`grep GEOFLAG` across `lib/ge/src` returns **one line**, and it is a comment:

```c
/* bondconstants.h:249 */
CDTYPE_AIOPAQUE = 0x0100,   // exclude objects with OBJFLAG_AISEETHROUGH
```

**GoldenEye has no per-surface sight flag.** What it has instead is a
**`cdtypes` bitmask passed per query** — `CDTYPE_OBJS`, `DOORS`, `PLAYERS`,
`CHRS`, `PATHBLOCKER`, `BG`, `AIOPAQUE`, and eight door variants
(`bondconstants.h:239-257`). **The caller chooses what counts as an obstruction,
per call.**

| PD | Ours |
|---|---|
| One flag on the geometry, `GEOFLAG_BLOCK_SIGHT`, read by both probes | **A mask chosen by the caller.** `bondview2.c:2128` passes `0` or `OBJS\|DOORS\|PLAYERS\|CHRS\|PATHBLOCKER` — **note `CDTYPE_BG` is NOT in the player's move mask**; `chr.c:1252` passes `0x1f`; `bondview2.c:681` passes `0x13` |

> **This is better for R1, not worse, and the reason is `86` §3.5's own
> argument.** PD chose `GEOFLAG_BLOCK_SIGHT` **because they needed a way to
> exclude the invisible balcony barriers that the body collides with but the eye
> sees through.** Ours is a per-call mask, so **R1's head probe simply passes a
> different `cdtypes` than the body probe does** — which is the same intent,
> reached without needing the flag to exist.
>
> **`CDTYPE_PATHBLOCKER` is the one to look at first** — its comment is *"glass
> and scenery with `OBJFLAG_PATHBLOCKER`"*, which is precisely the
> see-through-but-solid class PD's flag was invented to exclude. **A head probe
> that omits `PATHBLOCKER` and keeps `BG` is the candidate**, and it costs one
> wear test to check against G-R1-1 (lean over a rail) and G-R1-2 (lean into a
> wall).
>
> **Both of R1's probes exist**: `stanTestVolume` (the cylinder/volume, with
> ymin/ymax) and `stanTestLineUnobstructed` (the crossing). **`86` §3.5's
> two-probe requirement — landing AND crossing — is buildable from what is
> already in the tree.**

---

## READ 6 — THE PATCH-NAME COUNT, AND A STALE NUMBER

| | |
|---|---|
| `RECOMP_PATCH` sites in `patches/*.c` | **46** — **CORRECTED by `91`; this doc first said 48** |
| **Unique names** | **45** — **CORRECTED by `91`; this doc first said 47.** One name appears twice (`select_ramrom_to_play`), under opposing `#if` |
| Why it was wrong | **The regex matched COMMENT PROSE**, including sentences about `RECOMP_PATCH` naming. **An instrument counting itself.** `48` rule 4
| **What `00` and `07` say** | *"Currently **31** renamed"* |

> **`00`'s and `07`'s 31 is STALE by 16.** Rule 10 — it is corrected in `00` by
> this document. It is not merely cosmetic: `07` GOTCHA 4's whole point is that
> a new *name* needs the long build with `tools_weaken_patched.py`, and a
> session reading "31" while the tree holds 47 has no way to tell whether its
> own new name registered.

**Distribution:** `widescreen.c` 13, `workbench_theboy.c` 11,
`ge_vr_bindtest.c` 8, `interpolation.c` 5, `audio.c` 3, `fps.c` 3, `skybox.c` 3,
`boot.c` 2.

### NEW NAMES `86` NEEDS — COUNTED BEFORE THE FIRST BUILD, AS §8 ITEM 6 ASKED

| Slice | New `RECOMP_PATCH` name | Long build? |
|---|---|---|
| **A1** | `caclulate_gun_crosshair_position_rotation` — **confirmed not already patched** | **YES** |
| **H2 option B** | the eye-height write. Candidate: the function containing `bondview2.c:4564`, or `bondviewGetPlayerDuckingHeightRelated` (`:9152`) — **not yet named, tenth read** | **YES** |
| **H2 option A** | none — RT64-side | no |
| S0, H1, H3, R1, G1, G2, G3, A2, S1, C1 | none identified — host and RT64 side, or `85`'s existing seam | no |

**So: one long build for A1, and a second if H2 option B is chosen.** Plan them;
do not discover them.

---

## WHAT THIS DOCUMENT CHANGES IN `86` AND `00` — RULE 10, LISTED

| Claim | Where | Now |
|---|---|---|
| *"about 85 lines"* | `86` §8 read 1, §3.8 table | **69 lines**, `gunfire.c:4667-4734` |
| *"`field_FFC` … This is `crosspos2` / `bgunSetAimPos`, exactly"* | `86` §3.8 table | **NOT exactly.** `field_FFC` comes from a **second integrator** under `gunaimdamp`, and it **also drives the gun model** (`gunfire.c:512`) |
| *"write `crosshair_x_pos` / `crosshair_y_pos`"* | `86` §5 A1 recipe step 4-5 | **Incomplete. Both integrators must be pre-loaded**, each with its own damping constant |
| *"whether `getPlayer_c_screenwidth()` is disturbed"* | `86` §8 read 3 | **It is not. `c_scalex`/`c_scaley` ARE**, by 1.7667, under `geVrWorldCamera()` |
| *"GoldenEye's counterpart of `bwalkCanMoveUpwards`… whether it exists under another name"* | `86` §8 read 4 | **`stanTestLocusEdgeAboveY` (`stan.c:2574`), already called on the player, and an `autocrouchpos` already fires. H2 option B is smaller than `86` costed it** |
| *"GoldenEye's counterpart of `GEOFLAG_BLOCK_SIGHT`"* | `86` §8 read 5 | **Does not exist. `cdtypes` is per-call**, which serves the same purpose. `CDTYPE_PATHBLOCKER` is the candidate to exclude |
| *"Currently 31 renamed"* | `00`, `07` | **45 unique names, 46 sites** — corrected again by `91`; this doc's own first answer of 47/48 counted comment prose |
| *"the near plane is ~10 units — a gun closer than that is CLIPPED"* | `83`, quoted in `86` §5 G3 | **Under the VR gate `znear` is clamped to 2.0** (`ge_vr_bindtest.c:534`). **G3's usable trim range is wider than `86` assumed** |

---

## THE READS THIS ONE OPENED — four, all cheap, all still reads

**`86` §8 owed six. Doing them owed four more.** None needs a launch.

7. **Can `itemstats->PlayX/PlayY/PlayZ` be zeroed under VR**, so `field_FFC`
   stops moving the gun model and is free to mean aim only? `gunfire.c:512-521`.
   **This is the one that decides whether A1 and G1-G3 can coexist.**
8. **Who calls `sub_GAME_7F0680D4`** (`gunfire.c:4806`)? It is a
   world-direction-to-aim path that already exists and already bypasses the
   clamp. **A1 may be a caller, not a patch.**
9. **Does `autocrouchpos` have a consumer that would fight a written-in head
   height?** Rule 6, fifth time.
10. **Name the function that owns `bondview2.c:4564`**, so H2 option B's patch
    name is counted before the build rather than after it fails silently.

---

## WHAT DID NOT CHANGE

**`86` §8's stated inverse of `transformAndNormalizeByLength2Dto3D` is exactly
right**, checked against `bondview.c:698-706` line by line:

```
px = c_screenleft + c_halfwidth  + (d.x / -d.z) / c_scalex
py = c_screentop  + c_halfheight - (d.y / -d.z) / c_scaley
```

**And `86`'s central claim survives**: `caclulate_gun_crosshair_position_rotation`
is the right function, it is patchable, and the aim path runs through it. **The
plan's target was correctly chosen. Its recipe needs one more line.**

---

## THE ORDER THIS SUGGESTS, WHICH IS `86` §6 WITH ONE EDIT

```
S0  instrument ──────────────────────────────► everything          UNCHANGED
H1  recentre at level start ─────────────────► removes a confound   UNCHANGED
reads 7 & 8  (field_FFC ownership, and sub_GAME_7F0680D4's callers)
             ────────────────────────────────► A1 AND G3 both      NEW, and free
H3  body yaw ────────────────────────────────► A1                   UNCHANGED
G1  head-relative hand pose ──► G2 ──► G3                           UNCHANGED
H2  head height  (cheaper than 86 said — re-discuss A vs B before building)
R1  roomscale lean  (cdtypes mask, not a flag)
A1  bullet follows the gun — TWO integrators ─► A2
S1, C1  independent
```

**Nothing here is built. `48` rule 1 still holds: plan, discuss, then execute.**
