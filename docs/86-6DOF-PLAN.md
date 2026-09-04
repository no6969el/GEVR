# 86 — 6DoF: THE WHOLE PLAN, DERIVED FROM PERFECT DARK'S SOURCE

**2026-08-23, written after cloning and reading the Perfect Dark VR tree.
Plan only. Nothing here is built. `48` rule 1: plan, discuss, then execute.**

**This supersedes `82` as the record of what Perfect Dark does.** `82` read the
repository once and recorded three findings from it. **All three survive**, and
they were the tip of it. This document is written against the actual source with
file and line for every claim, so the next session starts by typing.

---

## 0. THE SOURCE, AND THE LICENCE

| | |
|---|---|
| Repository | `Alex-LeTux/perfect_dark_VR`, branch **`port`** |
| Commit read | **`67ea20c`** — *"Fixed a crash on standalone/Quest build…"* |
| Licence | **MIT**, `LICENSE`, *Copyright (c) 2022 Ryan Dwyer* |
| VR code | `port/vr/` — `vr_openxr.cpp`, `vr_input.cpp`, `vr_settings.cpp`, `vr_hub.cpp`, plus hooks through `src/game/bondgun.c`, `bondwalk.c`, `bondmove.c`, `bondhead.c`, `player.c`, `playerreset.c` |

**MIT means it may influence ANYWHERE, including `lib/rt64/` and `repo\` — the
upstreamable half.** `48`'s licence table, top row.

> ### ATTRIBUTION IS OWED AND IT IS NOT OPTIONAL
>
> **Every mechanism in this document is derived from that tree.** MIT requires
> the notice to travel. Before any of this ships:
>
> 1. **`PUBLISH-MANIFEST.md`** gains a prior-art section naming the repository,
>    the commit, and the licence.
> 2. **Every source file that implements one of these mechanisms carries a
>    comment naming the PD file and function it derives from.**
> 3. **`81` said this and it is repeated here because a plan is where it gets
>    forgotten.**

**`81`'s honest caveat — "the VR code is not yet in the public tree" — is now
FALSE and is corrected at source.** It is public, it is complete, and it is
about 180 KB of it. Rule 10.

---

## 1. WHAT "6DoF" MEANS IN THIS PROJECT, AND WHY IT IS ONE PLAN AND NOT SIX

Six degrees of freedom is not one feature. It is **two tracked rigid bodies —
the head and the hand — each with a position and an orientation, expressed in a
frame, at a scale.** This project has been building those pieces separately and
the pieces keep disagreeing about the frame.

| Aspect | GoldenEye today | Doc |
|---|---|---|
| Head **rotation** | Works, worn, confirmed | `36` |
| Head **position** | Works, worn — **but unclamped, unmapped to the body, and it puts your eye through ceilings** | `31`, `36` |
| **Scale** | Measured ~50 u/m by wearing it | `77` |
| **Recentre** | Works, but fires at process start — the wrong moment | O60 |
| Hand **position** | **Tracks, confirmed worn** through the engine's own seam | `85` |
| Hand **rotation** | **Deliberately identity.** A wrong one HIDES the gun | `85` |
| **Aim / the bullet** | Still from the crosshair. Nothing built | `38`, `76` |

**Perfect Dark answers all seven of those in one coherent scheme, and the reason
it is coherent is that every quantity is named with the frame it lives in.**
That is what this plan imports. Not their code — the injection mechanism is
different and a copied function would not attach (`82`) — **their frames.**

---

## 2. THE FRAMES. Read this table before writing a line.

**Nearly every hand and head fault this project has had was a frame error
wearing a different costume**: `79`'s "mirror, not a rotation", `84`'s
`gunofs`-space error, `85`'s inverted Z, `32`'s dead eye-sign knob. Perfect
Dark writes the frame into the variable name and the comment. We should too.

| PD quantity | Frame | Units | Built at |
|---|---|---|---|
| `gHeadPos` | **play space**, engine basis: OpenXR metres with **X and Z negated**, ×100 | game units (≈ cm) | `vr_openxr.cpp:1345` |
| `vr_HMD_rot_Q` | play space, **after** the recentre yaw | quaternion | `vr_openxr.cpp:1352` |
| `gRawHeadQ` | raw runtime, **before** the recentre | quaternion | `vr_openxr.cpp:1348` |
| `gVrHeadHeightCm` | **above the physical floor**, absolute | cm | `vr_openxr.cpp:1286` |
| `vr_recenter_rot_Q` | the recentre itself, yaw only | quaternion | `vr_openxr.cpp:1358` |
| `vr_joy_rot_Q` | the **body's** heading — stick turn, yaw only | quaternion | `bondwalk.c:141` |
| `gCtrlPos[2][3]` | **HEAD-RELATIVE.** Located against `viewSpace`, ×100 | game units | `vr_input.cpp:523`, `:1288` |
| `gCtrlQuat[2][4]` | head-relative, stored `{w,−x,y,−z}` — **a 180° Y basis change** — plus a 90° X offset | quaternion | `vr_input.cpp:1220`, `:1316` |
| `vr_ctrl_quat_play` / `vr_ctrl_velocity_play` | **play space, raw OpenXR, no mirror, no offset, no smoothing** — the gesture frame, kept separate on purpose | — | `vr_input.cpp:545`, `:1203` |

> **THE ONE THAT MATTERS MOST: `gCtrlPos` IS HEAD-RELATIVE.**
>
> They locate the controller against **`viewSpace`, not `playSpace`**
> (`vr_input.cpp:523`). So the controller position arrives already expressed in
> the same space the viewmodel is placed in, and the gun placement is a plain
> sum — no head cancellation, no camera matrix, nothing to get backwards.
>
> **`79` composed in the head's frame and then multiplied the game's root
> rotation. `85`'s seam adds to `gunofs`. Neither is head-relative-and-nothing-
> else.** This is the single structural difference between their placement and
> ours, and it is why theirs needs no per-axis sign sweep.
>
> **The gesture frame is kept as a SECOND copy on purpose** — the comment at
> `vr_input.h` says why: *"Gesture maths needs the rotation and the velocity to
> live in the same basis, and the mirror/offset/recoil that the weapon pose
> needs would break that."* **Two consumers, two frames, named. Not one frame
> argued over.**

---

## 3. WHAT PERFECT DARK DOES, MECHANISM BY MECHANISM

### 3.1 THE RECENTRE IS A YAW OFFSET, AND IT IS CALLED FROM THE GAME

```c
/* port/vr/vr_openxr.cpp:1257 */
extern "C" void vr_align_with_game_angle(float target_game_angle) {
    float current_physical_yaw = GetYawDegreesFromQuaternion(gRawHeadQ);
    g_yawOffsetDegrees = target_game_angle - current_physical_yaw;
    /* wrapped to ±180 */
}
```

Applied every frame to **both** halves of the head pose, which is the part that
cannot be got wrong once it is written this way:

```c
/* vr_openxr.cpp:1351-1353 */
XrQuaternionf offsetQ = YawToQuaternion(g_yawOffsetDegrees);
XrQuaternionf rawQ    = MultiplyQuaternions(offsetQ, gRawHeadQ);
XrVector3f    rawHead = RotateVectorY(rawPos, g_yawOffsetDegrees);
```

**Callers, and they are the point:** `player.c:1853` (align to the player's own
spawn angle), `player.c:3432` and `:4553` (a fixed `-120°`), **`bondwalk.c:529`
(align to `0`)**. It is not a key the user presses. **It is called by the game,
at the moments the game knows the player's heading**, and `playerreset.c:134`
re-runs the height calibration alongside it.

> **This is O60, answered.** Our recentre fires at process start with the
> headset on the desk. `F9` works and composes correctly — **the mechanism was
> never wrong, only the moment.** PD's answer is: fire it where the game already
> resets the player.
>
> **And note rule 8 holds here.** They did not synchronise the position recentre
> with the rotation recentre — **one yaw number drives both**, so they cannot
> disagree. `46` reached the same conclusion the hard way, twice.

### 3.2 HEAD HEIGHT IS ABSOLUTE, MEASURED FROM THE FLOOR

```c
/* vr_openxr.cpp:1286 */
if (gVrFloorRelativeSpace) { gVrHeadHeightCm = gHeadPos.y; return; }
/* else: median of 90 samples (~1 s), offset so the median reads VrPlayerHeight */
gVrHeadHeightCm = gHeadPos.y + sHeightCalibOffset;
```

- **A floor-relative reference space is preferred**, and under it the number is
  free. `gVrFloorRelativeSpace = (gPlaySpaceType != XR_REFERENCE_SPACE_TYPE_LOCAL)`
  — `vr_openxr.cpp:828`.
- **Under `LOCAL` they calibrate**: 90 samples, **median** (not mean — a mean is
  what `72` caught us using), offset against a user-declared standing eye
  height.
- **Recalibration is a named entry point** re-run at level start —
  `playerreset.c:134`.

**We use `LOCAL` deliberately** (`10` measured this rig's floor 2.4–3.2 m out),
so **the median calibration is the branch that applies to us**, and it is about
twenty lines.

### 3.3 THE HEAD'S HEIGHT DRIVES THE GAME'S EYE HEIGHT — NOT THE CAMERA MATRIX

**This is the largest architectural difference and the one the plan turns on.**

```c
/* src/game/bondwalk.c:1824-1836 */
float unitsPerCm = VrMatchCharacterHeight
                   ? (g_Vars.currentplayer->vv_eyeheight / VrPlayerHeight)
                   : VrSetWorldScale;
eyeheight = gVrHeadHeightCm * unitsPerCm;
if (eyeheight > VR_MAX_HEAD_CM * unitsPerCm) eyeheight = VR_MAX_HEAD_CM * unitsPerCm;
```

- **In real-height mode, one real centimetre is one game unit.** The comment
  says so outright: *"Joanna's eye sitting at 159 units for 1.59 m."* **That is
  100 units per metre.**
- `VR_MAX_HEAD_CM` is **250** (`bondwalk.c:69`) and its comment insists it is a
  **tracking-glitch clamp, not a height cap** — the ceiling test below is what
  actually stops you.
- **THE CEILING CHECK** — `bondwalk.c:1874-1900`. They write the candidate
  eyeheight into the player's three crouch-offset fields, ask
  **`bwalkCanMoveUpwards(0)`**, restore the fields, and keep the last known-good
  height if the answer is no.

> **This is `31`'s "head translation is unclamped — stand on a chair and the
> viewpoint goes through the ceiling", solved with the game's own collision
> query and about fifteen lines.**
>
> **And it is the thing our architecture currently cannot do.** We translate the
> camera **in RT64**, downstream of everything the game knows. The game does not
> know the player crouched, so nothing tests it against a ceiling, the AI does
> not see a crouched player, and the body does not move. **PD's head position is
> a GAME quantity. Ours is a RENDER quantity.** That is the choice §5 slice H2
> puts in front of the wearer.

### 3.4 PHYSICAL CROUCH IS REAL, AND SO IS A STICK-CLICK FALLBACK

```c
/* src/game/bondmove.c:2572 */
if (gVrHeadHeightCm < VrPlayerHeight / 1.6f || sVrEyeheightMode == VR_EYEHEIGHT_SQUAT) { ... }
else if (gVrHeadHeightCm < VrPlayerHeight / 1.3f || sVrEyeheightMode == VR_EYEHEIGHT_DUCK) { ... }
```

**Two routes to the same three states**, physically ducking or clicking the
thumbstick, tested by `||` so neither has priority. Same divisors — `/1.3` and
`/1.6` — used to *apply* the crouch at `bondwalk.c:1861-1873`. **One set of
numbers, two inputs.**

### 3.5 ROOMSCALE: THE HEAD MAY LEAVE THE BODY

`vr_player_pos`, `bondwalk.c:336`. The comment above it is the design:

> *"`prop->pos` is the BODY: the collision cylinder, what the AI shoots at, what
> owns the rooms. The camera is the HEAD. Physically leaning moves only the
> head; the body is dragged after it only once you have leaned far enough that
> you are plainly walking rather than leaning."*

| | |
|---|---|
| **Vertical is excluded from the walk delta** | `delta.y = 0.0f;` with the reason in the comment: *"vertical is mapped absolutely by the eye height; it must not move the body"* (`bondwalk.c:363`) |
| **Glitch rejection** | a frame step over `VR_MAX_HEAD_STEP` = **25 units** is dropped whole (`:210`, `:366`) |
| **Two offsets, not one** | `sVrHeadOffsetPlay` takes the motion **unconditionally** — *"it is a record of where your head is, and nothing in the game may overrule that"*. `sVrShownOffset` is what is actually rendered |
| **The head probe** | `vr_head_offset_is_clear` (`:252`): a 12-unit cylinder probe **plus** `cdTestLos05`, both testing **`GEOFLAG_BLOCK_SIGHT`** |
| **Why that flag** | *"Solid means you cannot see through it… The invisible barriers these levels put along balconies and rails do not carry it, because you can plainly see through them, and blocking the head on those is what stopped leaning over a rail from working."* |
| **Body drag is separate** | `vr_try_move_body` (`:298`), full cylinder, ordinary collision |
| **Reset on every non-walking mode** | dead, cutscene, riding, grabbing → both offsets zeroed and tracking continues, *"so the next live frame sees no jump"* |

**The two-probe detail is worth the whole section:** the cylinder test alone
catches the head **landing** inside a wall, and a wall thinner than a lean is
wide steps straight over it — so the line-of-sight test catches the **crossing**.
Their comment says exactly that at `bondwalk.c:284-289`.

### 3.6 TURNING IS A YAW-ONLY QUATERNION, ACCUMULATED

`joy_for_vr`, `bondwalk.c:108`. Snap **45°** with hysteresis (arm at |x| < 0.0001,
fire at |x| > 0.9), or continuous **120°/s**, into `vr_joyAccum`, then

```c
vr_joy_rot_Q = { 0, sin(a/2), 0, cos(a/2) };   /* bondwalk.c:141-144 */
```

**Yaw only, always.** It is then applied to the head offset (`:385`), the look
and up vectors (`:483`), the grab delta (`bondgrab.c:69`), the eyespy
(`bondeyespy.c:1152`) — **and the gun's aim direction** (`bondgun.c:8364`).
**One body-heading quantity, read by everything that needs to know which way the
body faces.** We have no such quantity.

### 3.7 THE GUN: HEAD-RELATIVE POSITION, PER-WEAPON GRIP OFFSET, WORLD-STABLE PLACEMENT

`vr_gun_pos_rot`, `bondgun.c:6279`. In order:

1. **A per-weapon grip offset table** (`:6300-6321`) — the delta from the
   tracked point to the **gun model's origin**, because the origin is not the
   grip. Eleven entries; the default is `(0, 16, −4)`; rifles are `(−4, 16, 8)`.
2. **A per-weapon Z-roll** (`:6325-6340`), non-zero for exactly three cases.
3. **A per-player trim** from the ini (`:6347`), defaults **`(2.35, −13.02,
   −4.39)`**. Their comment: applying the table *"preserves every per-weapon
   relationship the original author dialled in, so a single global trim serves
   all weapons and none of them need individual hand-tuning."*
4. **Orientation from `gCtrlQuat` through `vrBuildGunRotation`** (`:1094`) —
   and the reason that indirection exists is a rule-6 finding worth stealing:
   *"BOTH writers of `hand->posrotmtx` must go through here: `vr_gun_pos_rot`
   builds it normally, but `bgun0f09a6f8` rebuilds it from scratch every recoil
   frame, and would otherwise silently stomp the override exactly while
   firing."*
5. **`posoffset = gCtrlPos + off`**, written into `posrotmtx.m[3]`,
   `useposrot = true`, and copied to `posmtx` (`:6378-6386`).

**Then it is re-placed at RENDER**, `bondgun.c:11112-11146`, and their comment
is the most useful paragraph in the repository for us:

> *"`sp274` arrived here as `FovOffset + gCtrlPos + off`, where `FovOffset` and
> `off` are CONSTANT view-space vectors — so `camMtx` orbits them about the head
> and **the gun swims**. Re-place the offset properly instead: rotate it by
> `hand->posrotmtx` so it becomes a fixed vector in the CONTROLLER's frame that
> `camMtx` cancels the head out of; negate X/Z afterwards … strip the FOV nudge,
> a flat-viewmodel hack that is wrong for a physically tracked gun. Net:
> `gCtrlPos + Ry180 * Rctrl * off`, which **tracks 1:1 on all 6 DOF**."*

**And they measured it rather than argued it:** *"sweeping controller pitch
gives `pipe_pitch = 90 − true_pitch` (slope exactly −1), and the mis-placement
peaks at `2*|off|`."* **That is `47`'s method, in someone else's repository.**

### 3.8 THE AIM: THE GUN'S OWN FORWARD, PROJECTED TO SCREEN, INTO THE ENGINE'S OWN INPUTS

`bgunSwivel`, `bondgun.c:8308` — **the direct counterpart of GoldenEye's
`caclulate_gun_crosshair_position_rotation`.** The VR path replaces the stick's
`screenx/screeny` like this (`:8353-8394`):

```c
struct coord vrdir = {0.0f, 0.0f, -1.0f};          /* the gun's own forward */
mtx4RotateVecInPlace(hand->useposrot ? &hand->posrotmtx : &hand->posmtx, &vrdir);
vrdir.y = -vrdir.y;                                 /* the shot path's Y flip */
/* normalise, then into world: */
vr_rotate_vector_by_quaternion(&vrdir, &vr_HMD_rot_Q);
vr_rotate_vector_by_quaternion(&vrdir, &vr_joy_rot_Q);
/* a far point along it — or the laser dot's actual hit point if there is one: */
sp94 = hand->muzzlepos + vrdir * 100000.0f;
mtx4TransformVecInPlace(camGetWorldToScreenMtxf(), &sp94);
cam0f0b4d04(&sp94, sp8c);                           /* → screen pixels */
x[h] = 2*sp8c[0]/viGetViewWidth()  - 1.0f;          /* → NDC */
```

and then feeds the engine's own damped integrator by **pre-loading its sum**:

```c
/* bondgun.c:8408 */
player->crosspossum[0] = x[HAND_RIGHT] / (1.0f - crossdamp);
```

> ### THIS IS `38`'s INVERSION, CONFIRMED BY INDEPENDENT PRIOR ART
>
> `38` derived
> `crosshair_x_pos = (desired_pixel_x − W*0.5) / ((1 − guncrossdamp) * W*0.5)`
> **from reading GoldenEye's source alone.** PD writes
> `crosspossum = x_ndc / (1 − crossdamp)`, which is the same expression with the
> pixel→NDC step factored out. **Two decomps, same engine, same answer, arrived
> at independently. `38` correction 2 is now confirmed rather than believed.**

**And the honest half, which corrects `76`:**

| | |
|---|---|
| `crosspos` — the visible crosshair | **clamped** to `[3, W−4]`, `bondgun.c:8421-8424` |
| `crosspos2` — the aim position fed to `bgunSetAimPos` | **NOT clamped**, `bondgun.c:8473-8480` |

> **`76`'s design table offered three answers to "what happens past the clamp"
> and said none was chosen. Perfect Dark chose NONE OF THEM. They live with the
> clamp and put a LASER DOT in the world instead** — `show_laser_dot`
> (`bondgun.c:8386`), `bgunUpdateLasersight` (`:10209`), and a
> `VrlaserDotForALL` setting so it is not only the laser weapons.
>
> **That is O64, and O64 is therefore not decoration and not optional — it is
> the mechanism that makes the clamp survivable.** `39`'s O64 row already says
> so; this is prior art agreeing with it.

### 3.9 SCALE IS TWO SEPARATE QUANTITIES AND THEY KEEP THEM SEPARATE

| | |
|---|---|
| **`vr_world_scale`** | **85** by default, **42.5** on four large levels (`player.c:3556-3566`), and a FOV-derived expression during cutscenes (`player.c:2231`) |
| Where it goes | a **shader uniform**, `uWorldScale` — `gfx_opengl.cpp:638` — **and** the eye offset: `tx = localEyeX * vr_world_scale` (`vr_openxr.cpp:2378`) |
| **`VrSetWorldScale`** | the player's own multiplier, **clamped 0.50–1.50** (`vr_settings.h`) |
| **The IPD** | **measured from the runtime's two eye poses every frame**, sanity-clamped to 1–10 cm, defaulted to 64 mm (`vr_openxr.cpp:2367-2374`) |
| **Height scale** | a **third** number, `unitsPerCm`, §3.3 |

**Three scales with three jobs, never one knob.** Ours is one:
`GE_VR_UNITS_PER_METRE` drives the IPD **and** head translation, and `80` says
so. **`77` measured ~50 u/m by wearing it; PD's height mapping is 100 u/m
outright.** Those disagree by exactly the factor `77` says `16` was out by, and
**the two cannot be reconciled by argument — see G-S1.**

### 3.10 THE SETTINGS FILE

`pd-vr.ini`, `vr_settings.cpp`. Flat `key=value`, saved with **explanatory
comments written into the file**, e.g.

```
; Your standing EYE height in cm -- where your eyes are off the floor, which is
; what the headset reports, roughly 13 cm below the top of your head.
PlayerHeight=175.0
```

**That is O48**, planned in `61`, never built. The session that produced `85`
spent a dozen relaunches proving why it matters.

---

## 4. WHAT THIS CORRECTS IN OUR OWN DOCS — rule 10, at source

**A wrong doc that nobody flags costs more than a bug.** Six, and each names
where it must be fixed.

| Claim | Where | Now |
|---|---|---|
| *"The VR code is not yet in the public tree"* | `81` | **FALSE.** `port/vr/`, ~180 KB, commit `67ea20c` |
| *"Their gun is world-locked, not view-locked"* | `82` finding 2 | **Half right and the half that is wrong matters.** The controller is located against **`viewSpace`** (`vr_input.cpp:523`) — head-relative. What is world-locked is the **ORIENTATION at render**, by cancelling the head out through `camMtx` (`bondgun.c:11112`). Position is head-relative throughout |
| *"What happens past the aim clamp is a design choice, none chosen"* | `76`, `38` correction 3 | **PD chose none of the three.** They keep the clamp on the crosshair, leave `crosspos2` unclamped, and answer the gap with a **world laser dot**. O64 is the mechanism, not decoration |
| *"`38`'s inversion — the relation is exactly invertible"* | `38` | **CONFIRMED by independent prior art** (`bondgun.c:8408`). Promote from derived to corroborated |
| *"Head translation is unclamped… Phase 4's head-in-geometry fade"* | `00`, `31` | **A fade is not needed for the vertical half.** `bwalkCanMoveUpwards` answers it directly — `bondwalk.c:1889` |
| *"`-UnitsPerMetre` drives the IPD and head translation"* | `80` | **Not a correction — a warning.** PD needs THREE independent scales. One knob doing three jobs is why 100 vs 50 "looked the same" (`77`) |

---

## 5. THE PLAN — slices, in an order that pays each time

**Do not batch them.** `48` rule 5, one behaviour change at a time. Each slice
is independently wearable. **Gates are written here, before the code, and each
one answers: what would this build have to do differently for this to fail?**

### THE STANDING PRECONDITIONS — every slice runs under these

```powershell
.\vr.ps1 -UnitsPerMetre 50 -SeamNoRot -HandPosZ 1    # where 85 left it
taskkill /F /IM GoldenRecomp.exe                      # THE EXIT. Never the X — B3/B4
```

**PUT THE HEADSET ON, THEN PRESS `F9`.** O60. Three confounded launches already.

---

### SLICE 0 — THE INSTRUMENT, AND IT SHIPS FIRST

**Nothing in this plan is judgeable without one log line that prints every 6DoF
quantity with the frame it is in.** `52`'s census cost one launch instead of a
session because it stated what it would report if it were looking at the wrong
thing. This does the same.

```
[gevr] 6dof: head play=(x,y,z) heightCm=NN recentreYaw=NN.N bodyYaw=NN.N
             ctrlR viewrel=(x,y,z) quat=(w,x,y,z) | gun want=(x,y,z) game=(x,y,z)
             scale: u/m=NN ipd=N.NNm eyeSep=NN.Nu
```

| Gate | What would a working build have to do differently to fail? |
|---|---|
| **G0-1** | Every field is non-zero and moves when the corresponding physical thing moves. **A build where a quantity is not reaching the game prints a frozen number, which is the failure `32` and `80` were both written about** |
| **G0-2** | **The line states its frame.** `head play=` not `head=`. A build that prints an unlabelled vector passes nothing, because the reader cannot tell a frame error from a sign error |
| **G0-3** | Under `-NoXr` it does not print at all. **O59's shape — a VR instrument firing where VR is off** |

**Falsifier:** cover the headset's sensors. Every tracked field must freeze
together. If one keeps moving it is not reading tracking.

---

### SLICE H1 — THE RECENTRE MOVES TO WHERE THE GAME KNOWS THE ANSWER

**The smallest slice in the plan and it removes a confound from every slice
after it.** §3.1.

- Keep `F9`. **Add a call at level start**, our counterpart of
  `playerreset.c:134`, aligning the recentre yaw to the player's own spawn
  heading.
- **One yaw number drives both position and rotation** — rule 8. Do not add a
  second.

| Gate | What would a working build have to do differently to fail? |
|---|---|
| **G-H1-1** | **Start a level with the headset already on and DO NOT press `F9`. Height and heading are right immediately.** A build that recentres at process start cannot pass this — that is the whole defect |
| **G-H1-2** | Pressing `F9` afterwards changes **nothing measurable**. If it does, the level-start recentre used a different quantity from the key's |
| **G-H1-3** | `-NoXr` untouched |

**Falsifier, no code:** put the headset on the desk, start a level, then pick it
up. Under the fix the world must not have been captured from the desk.

---

### SLICE H2 — HEAD HEIGHT BECOMES A GAME QUANTITY

**The architectural slice, and the one to discuss before building.** §3.3.

Today our head translation is applied in RT64, downstream of the game. PD's
drives the player's own `eyeheight`. GoldenEye has the same composition —
`bondview2.c:9152` returns `eyeheight + field_88 + ducking_height_offset`, and
`bondview2.c:4564` writes `eyeheight` from `headpos.f[1]`.

**Two options, and this plan does not choose. The wearer does.**

| Option | Cost | What it buys |
|---|---|---|
| **A: keep it in RT64, add a ceiling clamp only** | small | Stops the through-the-ceiling case. **Crouching still does not make you a smaller target and the AI never knows** |
| **B: drive the game's `eyeheight`** | a patch on the eye-height path, plus §3.4's crouch states | Physical crouch is real. Ceiling, AI, cover and body height all follow from the game's own code, as PD's do |

**Recommendation: build A first**, because it is small and it removes a
known-bad behaviour; **then wear B against it.** `48` rule 5.

| Gate | What would a working build have to do differently to fail? |
|---|---|
| **G-H2-1** | **Stand on something and your eye stops at the ceiling instead of going through it.** Today's build goes through. Nothing else in the tree changes that |
| **G-H2-2** | The height it stops at **is the ceiling's**, measured in the log — not a fixed number. A constant cap would also pass a naive version of G-H2-1, which is why this row exists |
| **G-H2-3** (option B only) | **Physically crouch and a guard's shot passes overhead.** A render-only translation cannot pass this at all |
| **G-H2-4** | Sit down in a chair and the view does not sink through the floor. `-NoXr` untouched |

**Falsifier:** `-NoHeadTranslate`. With head translation off, every gate above
must fail. **A gate that still passes with the input removed is measuring
something else** — `56`'s method.

---

### SLICE H3 — THE BODY YAW BECOMES A NAMED QUANTITY

**PD has `vr_joy_rot_Q` and we have nothing.** §3.6. Without it there is no
answer to "which way is the body facing", and **slice A1 cannot be written**,
because the gun's world direction needs it.

- One yaw-only quaternion, accumulated from the turn input.
- **Every consumer reads it. Nobody re-derives it.** Rule 8.
- Snap turn and continuous turn are two ways of feeding the same accumulator,
  not two systems.

| Gate | What would a working build have to do differently to fail? |
|---|---|
| **G-H3-1** | Turn with the stick, then physically turn your head the other way. **The logged body yaw follows the stick only.** A build that derives body yaw from the head cannot pass |
| **G-H3-2** | Snap and continuous produce the **same** accumulated value for the same total rotation, within a degree |
| **G-H3-3** | It is **yaw only**. Look up and it does not change |

---

### SLICE R1 — ROOMSCALE LEAN, AND ONLY THEN THE BODY DRAG

§3.5. **Build the lean first and stop.** The body drag is a second slice.

- `delta.y = 0` **with the reason in the comment**, or somebody will "fix" it.
- The **25-unit** glitch reject.
- **Two offsets**: the physical one takes the motion unconditionally; the shown
  one is what renders.
- The probe tests **sight-blocking geometry**, not walls.

| Gate | What would a working build have to do differently to fail? |
|---|---|
| **G-R1-1** | **Lean over a rail and see down.** A build that tests the body cylinder is stopped by the rail — that is the exact failure the flag choice fixes |
| **G-R1-2** | **Lean into a solid wall and the view stops at its face.** A build with no probe goes inside |
| **G-R1-3** | Lean **through** a thin wall in one motion and it still stops. **This is the crossing-vs-landing case, and G-R1-2 passes while this fails** unless the line-of-sight test is there |
| **G-R1-4** | Physically crouch and the body does not slide. `delta.y = 0` is the only thing that gives that |
| **G-R1-5** | Die, or open a cutscene, and on return the head is back on the body with **no jump** |

---

### SLICE G1 — THE HAND POSE ARRIVES HEAD-RELATIVE

**`85` got the gun onto the hand through the engine's seam, and it works. This
slice does not replace that — it changes what is written INTO it.** §2, §3.7.

- Locate the controller against the **view space**, not the play space, so the
  head is already cancelled.
- **Publish the gesture-frame copy at the same time**, unsmoothed and
  unmirrored, so nothing later has to un-condition a conditioned pose.
- Keep `-SeamNoRot`. **Rotation is slice G2.**

| Gate | What would a working build have to do differently to fail? |
|---|---|
| **G-G1-1** | **Hold the controller still and turn your head. The gun does not move.** Head-relative-at-the-source is the only thing that gives that for free |
| **G-G1-2** | Move the controller with the head still: the gun tracks left, right **and depth**, as `85` already confirmed. **This is a regression gate, not a new one** |
| **G-G1-3** | **The hand at the side, low, and behind the shoulder.** `85`'s "when in front of me" was a deliberate qualifier and nobody has tested past it |
| **G-G1-4** | The logged view-relative position is **within a few units of a tape measure** from the headset to the controller. `85` proved feel is not enough |

---

### SLICE G2 — ROTATION, AS A CONVENTION SWEEP

**The position is known-good underneath it, which is why this order was worth
the launches** (`85`).

- **A wrong rotation HIDES the gun** — it pre-multiplies `rotmtx` and acts about
  the model's own origin (`85` fault 2). **Expect disappearance, not tilt.**
- Sweep `-HandAxisX/Y/Z` **one at a time**.
- **Route every write to the override matrix through one function**, PD's
  `vrBuildGunRotation` lesson (`bondgun.c:1091`) — **because a second writer
  during recoil will stomp it exactly while firing**, which is the worst
  possible time to find out. **This is rule 6, and PD hit it.**

| Gate | What would a working build have to do differently to fail? |
|---|---|
| **G-G2-1** | Roll the controller about the barrel and the gun rolls **the same way, the same amount**. A mirrored transform rolls the right amount the wrong way — `79` correction 2's exact fault |
| **G-G2-2** | **Fire a full magazine while rotating.** The gun does not snap back on any frame. A build with a second unrouted writer fails only here |
| **G-G2-3** | The gun stays **visible** through the whole sweep. Disappearance is the rotation failure mode, so an invisible gun is a FAIL, not a null result |

---

### SLICE G3 — THE GRIP OFFSET AND ITS TABLE

§3.7. `-GunOffX/Y/Z` is built. **The per-weapon table is not.**

- Trim first, in the **gun's own oriented frame**.
- **Then** measure two weapons that disagree, and only then add a table.
- **`83`'s numbers are the target**: the game holds its gun at `(±11, −21,
  −33)`, and the near plane is ~10 units — **a gun closer than that is CLIPPED,
  not far.**

| Gate | What would a working build have to do differently to fail? |
|---|---|
| **G-G3-1** | The trigger finger lands where your real one is, **on one weapon**. Measured against the log, not judged |
| **G-G3-2** | **Switch weapons. If the fit survives, no table is needed** — and that is a real possible outcome, not a failure |
| **G-G3-3** | Sweeping controller **pitch** moves the gun's own pitch 1:1. **PD measured slope −1 on a wrong frame and 2×|off| mis-placement** — that is the falsifier, and it costs one sweep |

---

### SLICE A1 — THE BULLET GOES WHERE THE GUN POINTS

**§3.8, and this is where PD's reading saves the most time.**

The GoldenEye counterpart is named and it is small:

| | |
|---|---|
| **`caclulate_gun_crosshair_position_rotation`** | `lib/ge/src/game/gunfire.c:4666`. **About 85 lines.** `RECOMP_PATCH`-able — which `78` could not say about `gunUpdateAndFire` |
| The clamp | `gunfire.c:4698-4715`, on `crosshair_angle` |
| **The unclamped aim** | `field_FFC`, `gunfire.c:4726-4731`, into `transformAndNormalizeByLength2Dto3D(..., 1000.0f)` then `sub_GAME_7F067AB4`. **This is `crosspos2` / `bgunSetAimPos`, exactly** |
| **The projection is closed-form invertible** | `transformAndNormalizeByLength2Dto3D`, `bondview.c:698`, is `x = ((px − c_screenleft) − c_halfwidth) * c_scalex`, `y = (c_halfheight − (py − c_screentop)) * c_scaley`, `z = −1`. **So a camera-space direction becomes a pixel with no matrix at all**: `px = c_screenleft + c_halfwidth + (d.x / −d.z) / c_scalex`, `py = c_screentop + c_halfheight − (d.y / −d.z) / c_scaley` |

**So we do not need PD's world→screen route.** They use
`camGetWorldToScreenMtxf` because they start from a world point; we can start
from the gun's direction in camera space and invert two lines of arithmetic.
**`camGetWorldToScreenMtxf` exists here too** (`bondview.c:824`) if the world
route turns out to be needed.

**The recipe:**

1. Gun forward `{0,0,−1}` through the same override matrix that placed it.
2. Into world via the head quaternion, then the body yaw (slice H3).
3. Back into camera space, invert `transformAndNormalizeByLength2Dto3D` → pixel.
4. **Write `crosshair_x_pos` / `crosshair_y_pos`, never `crosshair_angle`**, and
   **every frame** — `38` correction 2, confirmed by `bondgun.c:8408`.
5. Pre-load the integrator: `crosshair_x_pos = ndc / (1 − guncrossdamp)`.

| Gate | What would a working build have to do differently to fail? |
|---|---|
| **G-A1-1** | **Point off-centre and fire. The shot lands where the barrel points, not where the head looks.** Today's build cannot pass this at all |
| **G-A1-2** | **Switch weapons mid-burst.** Aim does not jump. `guncrossdamp` comes from `WeaponStats` and the game **rescales `crosshair_x_pos` underneath us** — a once-per-switch write fails only here |
| **G-A1-3** | **Point past the clamp and report what happens, in the same launch.** Not discovered later. The prediction: the crosshair pins and the gun keeps tracking, so gun and bullet visibly disagree |
| **G-A1-4** | `-NoXr` aims with the stick exactly as before. **The patch replaces a function both paths call** |

**Three reads still owed, and `76` listed them.** They are reads, not
experiments, and PD answers the shape of all three:

1. Which of `bondview2.c:6072` / `:6077` is aim mode — **confirmed, not
   assumed.** PD's callers are `bondmove.c:2391-2451`, five of them, and the
   split is auto-aim vs manual.
2. Whether `crosshair_x_pos` has readers besides
   `caclulate_gun_crosshair_position_rotation`.
3. Whether `getPlayer_c_screenwidth()` is affected by anything the patch does.
   **The patch widens the culling FOV and `viGetFovY` divides it back out**
   (`00`), so this one is live and matters.

---

### SLICE A2 — THE WORLD-SPACE AIM DOT (O64)

**Not decoration. §3.8.** With the clamp kept, the gun and the bullet disagree
past roughly ±30° off body centre, and **a dot on the fired ray is the only
honest way to show where the shot goes.** PD ships it for every weapon behind a
setting (`VrlaserDotForALL`), and their aim path already switches to *"the laser
dot's actual hit point"* when there is one (`bondgun.c:8367-8388`).

| Gate | What would a working build have to do differently to fail? |
|---|---|
| **G-A2-1** | The dot sits **on the surface the bullet hits**, at any range. A dot at fixed distance is a different feature and fails this |
| **G-A2-2** | **Point past the clamp: the dot stops moving with the hand.** That is the clamp made visible, and it is the point of the slice |
| **G-A2-3** | It is drawn once **per eye, at the right depth**. A HUD-space dot cannot fuse and B1 is what bought us the ability to notice |

---

### SLICE S1 — SPLIT THE SCALE KNOB

§3.9. **One knob currently does three jobs.**

| New knob | Drives | PD's counterpart |
|---|---|---|
| `-IpdScale` | the eye separation only | `vr_world_scale` at `vr_openxr.cpp:2378` |
| `-HeightUnitsPerCm` | head height → eye height | `unitsPerCm`, `bondwalk.c:1824` |
| `-MoveUnitsPerMetre` | how far a physical step carries you | the roomscale delta, `bondwalk.c:362` |

| Gate | What would a working build have to do differently to fail? |
|---|---|
| **G-S1-1** | **Change one and the other two logged quantities do not move.** Today's build moves all three — that is the defect |
| **G-S1-2** | **Use a step nobody could miss: 4×, not 2×.** `77`: a 2× change was reported as *"it looks the same"* while the log showed it genuinely halving |
| **G-S1-3** | Read `eye sep` from the log **before** judging anything. It is a number the program prints about the thing in question and it costs nothing |

> **AND THE OPEN QUESTION THIS SLICE FINALLY MAKES ANSWERABLE.** `77` measured
> ~**50** u/m worn. **PD's height mapping is 100 u/m outright** — one real cm,
> one game unit. **They cannot both be right about the same quantity, and they
> may not be about the same quantity at all**: ours drives IPD *and* height
> *and* movement at once. **Split them and measure each separately. Do not
> argue about which number is right.**

---

### SLICE C1 — `vr.json`, HOT-RELOADED (O48)

§3.10. Planned in `61`, never built. **The session that produced `85` spent a
dozen relaunches proving why it matters, and every slice above has a knob to
sweep.**

- Comments written **into** the file, as PD does.
- **Every value logs its SOURCE** — file, env override, or default. `61`'s
  design, and it is the answer to `80`'s standing worry about knobs with no
  reader.

| Gate | What would a working build have to do differently to fail? |
|---|---|
| **G-C1-1** | Edit the file **while worn** and the value changes without a relaunch. That is the whole feature |
| **G-C1-2** | An env override wins over the file **and says so in the log**. A build that silently prefers one fails the next diagnosis, not this test |
| **G-C1-3** | A missing or malformed file uses defaults and **names the fault**, rather than starting wrong and quietly |

---

## 6. THE ORDER, AND WHAT BLOCKS WHAT

```
S0  instrument ───────────────────────────────► everything
H1  recentre at level start ──────────────────► removes a confound from all of it
H3  body yaw as a named quantity ─────────────► A1 cannot be written without it
G1  head-relative hand pose ──────────► G2 ──► G3
H2  head height as a game quantity  (independent; discuss before building)
R1  roomscale lean            (independent; after H2 option B if that is chosen)
A1  bullet follows the gun ───────────────────► A2 aim dot
S1  split the scale knob      (independent; do it before any more scale sweeps)
C1  the settings file         (independent; every slice above gets cheaper after it)
```

**And B3/B4 — the machine bugcheck and the graceful exit — sit above all of
this.** `75`. Every slice here costs wear tests, and every wear test currently
risks a reboot.

---

## 7. WHAT THIS PLAN DELIBERATELY DOES NOT DO

- **No IK arm.** `76` settled it: a wrong arm is more distracting than no arm,
  and `hand_invisible[hand]` already exists to test both.
- **No two-handed aim, no gestures, no throwing.** PD has all three. They are
  built on top of a working single-hand pose and we do not have one yet.
- **No VR hub / quad-layer menu.** PD has one (`vr_hub.cpp`). It is O61 and it
  is parked.
- **No scope.** `37` trap 3. Its own phase, RT64-side.
- **No per-weapon table until two weapons are measured to disagree.**

---

## 8. THE READS OWED BEFORE ANY OF THIS IS BUILT

**All reads. None is an experiment. `76` said do them before, not during.**

1. **`caclulate_gun_crosshair_position_rotation`'s exact length and every symbol
   it calls**, against the `RECOMP_PATCH` rules in `07`. It looks patchable at
   ~85 lines; **"looks" is not the standard this project uses.**
2. Whether `crosshair_x_pos` has readers besides that function.
3. Whether `getPlayer_c_screenwidth()` is disturbed by the FOV widening.
4. **GoldenEye's counterpart of `bwalkCanMoveUpwards`** — the ceiling query H2
   needs, and whether it exists under another name.
5. **GoldenEye's counterpart of `GEOFLAG_BLOCK_SIGHT`** — R1's probe flag is the
   whole reason leaning over a rail works in PD.
6. **A new `RECOMP_PATCH` name needs the long build** (`07`, and 31 are already
   renamed). Count the new names in this plan **before** the first build, not
   after it fails silently.

---

## 9. THE RULES THIS PLAN IS WRITTEN UNDER

**Every one of them was paid for by this project, and Perfect Dark's source
independently obeys four of them.**

| | |
|---|---|
| **Rule 3 — measure, do not describe** | PD measured their frame error as *"slope exactly −1"* rather than describing a swimming gun |
| **Rule 6 — check who else writes what you write** | `vrBuildGunRotation` exists **only** because a second writer stomped the override during recoil |
| **Rule 8 — do not synchronise two things, remove the second** | One yaw offset drives both halves of their recentre |
| **Rule 11 — nothing is DONE until it is OBSERVED** | Every gate above names a wearer action |

**And the one this project earned last, which no amount of prior art replaces:**

> **THE WEARER IS THE BEST INSTRUMENT HERE. ASK WHAT IT LOOKS LIKE, NOT WHETHER
> IT WORKS — AND WHEN A HUMAN IS THE INSTRUMENT, USE A STEP NOBODY COULD MISS.**
