# 102 — WHAT PERFECT DARK ALREADY SOLVED. THE VALUES, NOT THE IDEAS.

**2026-08-24. Read at `Alex-LeTux/perfect_dark_VR`, branch `port`, commit
`67ea20c86986c6bc85687f26a27418b266af309c` (2026-08-19). MIT.**

**Why this document exists: `86` read their tree and copied their DESIGN. It did
not copy their NUMBERS.** So nine slices were specified that re-derive things
they had already measured, tuned and shipped. **The owner asked the right
question — *"if the game is the same, could we just use those variables so the
gun feels good and looks right off the bat"* — and the answer is yes for most of
it.**

**ATTRIBUTION IS OWED on anything derived from this**, in `PUBLISH-MANIFEST.md`
**and** in a source comment at the point of use. `00`'s licence table: MIT may
influence anywhere.

---

## §1 — THE CORRECTION THAT CHANGES SLICE A1 AND A2

> ### **`86` §3.8 IS WRONG. PERFECT DARK DOES *NOT* KEEP THE AIM CLAMP.**

`86` said PD *"keeps the clamp and answers the gap with a world-space laser
dot"*, and `90` built on that. **Read at source, they do something better and it
is exactly what the owner described wanting:**

```c
/* bondgun.c:8419-8422 — the DRAWN CROSSHAIR is clamped */
crosspos[0] clamped to [3, width-4], crosspos[1] to [3, height-4]

/* bondgun.c:8468-8472 — THE BULLET AIM IS DELIBERATELY NOT CLAMPED */
cam0f0b4c3c(crosspos2, &aimpos, 1000);   ->  bgunSetAimPos
```

**They clamp what you SEE and leave what you SHOOT free.** The per-hand HUD
crosshair is additionally forced to screen centre (`:8436-8437`) and the stale
accumulator bled off by `*= 0.9269697f` NTSC / `0.913f` PAL each tick
(`:8433-8434`).

**THIS IS THE "BREAK THE LOCK" THE OWNER ASKED FOR, AND PRIOR ART DOES IT.**
`76`'s three options and `86`'s "PD chose none of them" are both superseded.
Rule 10.

**The read A1 now owes** — and it is the whole slice in one question: **GoldenEye's
bullet reads `crosshair_angle`, which IS clamped (`90`, eight call sites). PD's
bullet reads `crosspos2`, which is not. Is GE's `field_FFC` path (unclamped,
already producing `field_A38/A3C/A40` via `transformAndNormalizeByLength2Dto3D`
+ `sub_GAME_7F067AB4`) the true counterpart of `crosspos2`?** If it is, **the
unclamped shot path exists in GoldenEye already** and `90`'s "there is no
unclamped shot path" is a statement about which path the STOCK code uses, not
about which paths exist.

## §2 — THE DAMPING INVERSION, CONFIRMED VERBATIM

`bondgun.c:8407-8412`:

```c
if (crossdamp < 1.0f) { player->crosspossum[0] = x[HAND_RIGHT] / (1.0f - crossdamp); ... }
if (aimdamp   < 1.0f) { player->crosssum2[0]  = x[HAND_RIGHT] / (1.0f - aimdamp);   ... }
```

**Both integrators, pre-loaded so the IIR's steady state IS the VR value.**
`87` finding 1 and `38`'s derivation are both confirmed by shipped code.
**Also: `bgunSwivelWithDamp`'s `if (aimdamp < crossdamp) aimdamp = crossdamp;` is
COMMENTED OUT FOR VR** (`:8497-8499`) — a stock coupling they had to remove.

**Pose to aim, `bgunSwivel` `bondgun.c:8347-8398`:** local `{0,0,-1}` through
`posrotmtx`, **then `vrdir.y = -vrdir.y`**, normalise, rotate by HMD quat, **then**
by stick-yaw quat — **order stated as load-bearing** — then world-to-screen and
NDC via `(2x/viewWidth)-1`.

## §3 — THE NUMBERS. COPY THESE.

### Per-weapon grip offsets — **`bondgun.c:6286-6320`, NOT `vr_input.cpp:6300`**

`86`'s citation was to a 1395-line file at line 6300 and cannot have been right.
**Default `(0, 16, -4)` CONFIRMED (`:6320`); rifles `(-4, 16, +8)` CONFIRMED
(`:6305`).** Game units ~ cm; gun-model frame, X right, Y up, Z along barrel.

| Class | offset | line |
|---|---|---|
| Dragon / SuperDragon / Devastator | `(-4, 16, +4)` | :6300, :6312 |
| **Rifles w/ foregrip** (RCP120, AR34, shotgun, sniper, Farsight) | `(-4, 16, +8)` | :6305 |
| Launchers (Callisto, RocketLauncher) | `(-8, 14, -4)` | :6308 |
| Reaper | `(+8, 12, -4)` | :6310 |
| Thrown / knife / crossbow | `(-2, 12, -12)` | :6318 |
| **default (pistols)** | **`(0, 16, -4)`** | :6320 |

**THE TRAP, and it is measured:** X and Z are **negated** relative to how they
were first authored, because the placement moved from `gCtrlPos + posrotmtx*off`
to `gCtrlPos + Ry180*posrotmtx*off` (`:6288-6294`, with proof: a tuned Falcon2's
total Z went `+7.3 -> -8.4`, sign flipped, magnitude kept). **Copy the Ry180
placement too, or re-negate x and z. Copying the numbers alone gets a gun
mirrored about the grip.**

Global trim on top: `VrGunOffX 2.35`, `VrGunOffY -13.02`, `VrGunOffZ -4.39`
(`:180-182`, applied `:6345-6347`). Per-weapon Z-roll radians at `:6325-6342`.

### Controller orientation — **CONFIRMED, and the offset is pi/2 not 1.0**

`vr_input.cpp:1219-1225`: `{ w, -x, y, -z }` — *"exactly conjugation by a 180 deg
Y rotation, a change of basis"* (`bondgun.c:11117-11119`).
`vr_input.cpp:1317-1327`: right-multiply by a **1.5708f** X rotation **after
smoothing**. **The comment beside it says "1.0 rad" and is WRONG. Trust the
value.** Applied to the raw quat too (`:1333-1337`) or the unsmoothed HUD
misorients relative to weapon and recoil.

**Per-frame order** (`:1176-1360`): publish raw play-space gesture quat -> pos
x100 (m->cm) -> mirror -> save pre-smoothing raw -> smooth -> **90 deg offset** ->
recoil -> velocities.

**HEAD USES A DIFFERENT CONVENTION** — `vr_openxr.cpp:1344-1348`:
`{-x*100, +y*100, -z*100}`. **X and Z negated, Y not.** Two conventions in one
codebase, deliberately.

### Smoothing, and it is nearly all OFF

| | value | where |
|---|---|---|
| `CTRL_SMOOTH_ALPHA_POS` | **1.00 = no smoothing** | vr_input.cpp:88 |
| `CTRL_SMOOTH_ALPHA_ROT_GRIP` | 0.10 | :89 |
| `CTRL_SMOOTH_ALPHA_ROT_IDLE` | 0.50 | :90 |
| `HMD_SMOOTH_ALPHA_POS` / `_ROT` | 0.05 / 0.05, **only while gripping a zoomable weapon** | vr_openxr.cpp:302-303 |

**Position is not smoothed at all.** Rotation smoothing is heavy only while
gripping — it is a scope-steadying feature, not a jitter fix.

### Height, crouch, ceiling

`VR_NOMINAL_HEAD_HEIGHT_CM 160` (vr_openxr.h:73) · `VrPlayerHeight 160` default,
**standing EYE height** (bondwalk.c:63) · slider clamp **130-200** (vr_settings.h:24)
· `VR_MAX_HEAD_CM 250` glitch swallow (bondwalk.c:69) · **90-sample MEDIAN**
calibration, `sHeightCalibOffset = VrPlayerHeight - median` (vr_openxr.cpp:282,
1286-1308).

**`unitsPerCm = vv_eyeheight / VrPlayerHeight`** in real-height mode — *1 real cm
= 1 game unit* (bondwalk.c:1824-1826).

**The ceiling probe, and the save/restore is load-bearing** (bondwalk.c:1876-1901):
compute a target, **write it into ALL THREE crouch-offset fields**, call
`bwalkCanMoveUpwards(0)`, **restore all three**, latch the last good height on
success. **`89` read 10 predicted this shape for our tree; this is it working.**

**CROUCH STATE FROM HEIGHT — and the bug they fixed is the one we would have
written** (`bondmove.c:2571-2578`): thresholds are fractions of the **configured
standing height**, `< /1.6 = SQUAT`, `< /1.3 = DUCK`. **A running max was the
original and it was wrong — a physical jump raised it and left you spuriously
ducking.** Speed penalties DUCK x0.5, SQUAT x0.35.

### Roomscale lean — `bondwalk.c:146-451`

`VR_HEAD_PROBE_RADIUS 12.0`, `YMAX +10`, `YMIN -10` — **a slab at eye level, not
a body cylinder, so waist-high rails pass under it.**
`VR_BODY_CATCHUP_MAX 10.0` · `VR_MAX_HEAD_STEP 25.0` (25 cm at 90 Hz = 22 m/s;
rejects spikes) · fade `VR_HEAD_FADE_START 2.0` -> `FULL 10.0`.

**THE TEST IS `GEOFLAG_BLOCK_SIGHT`, NOT SOLIDITY** (`:283-285`) — *"geometry you
can see through, your head goes through; geometry you cannot, it does not."*
**Invisible balcony barriers do not carry BLOCK_SIGHT, and testing solidity is
what broke leaning over rails.** `86` slice R1 said this; here is the reason.
**A second `cdTestLos05` along the lean** (`:288-290`) because a destination-only
test lets you step through a thin wall and pop out the far side.

**`delta.y = 0.0f`** — *"vertical is mapped absolutely by the eye height; it must
not move the body"* (`:366`). **Reset on dead / non-normal tick / duel /
non-walk, AND resync the last sample so the next live frame sees no jump**
(`:341-360`).

**THE FADE MUST BE DRAWN BEFORE THE HUD** (player.c:5388-5409) — HUD capture
regions redirect drawing, and a fade emitted after them **reached only one eye**,
"reliably in the campaign but not with a radar on screen." **That is a
stereo-specific bug they already paid for and we would have hit.**

### Turning, two-handed, throwing

`VR_JOY_TURN_SPEED (120/360/60)` · `VR_SNAP_ANGLE_DEG 45` · snap activate 0.9 /
deactivate 0.0001 · stick deadzone 0.1 (bondwalk.c:100-129).
`VR_2H_SEP_MIN 9.0` — **not comfort: controllers physically touching still read
~9 apart, measured** (bondgun.c:1060-1066). Throw release `> 0.5 m/s`,
`throwSpeed = magnitude * 10` (`:2747, :2767`).
**Recoil: a 5-field profile per weapon and ~60 entries** (vr_input.cpp:899-1088),
integrated at a **fixed `dt = 1/90`** with a TODO to use the real frame delta.

## §4 — THE TRAPS THEY ALREADY PAID FOR

1. **HAND INDEX IS INVERTED.** Game `HANDRIGHT=0, HANDLEFT=1`; OpenXR `0=left`.
   `ctrlIndex = 1 - handnum` (vr_input.cpp:1096-1101). **Our `61` bound
   controllers without this ever being written down.**
2. **ONE WRITER FOR THE HAND MATRIX.** `vrBuildGunRotation` must be the only
   writer of `posrotmtx`, because the recoil path rebuilds it every frame and
   *"would otherwise silently stomp the override exactly while firing"*
   (bondgun.c:1091-1094). **`48` rule 6 in someone else's codebase.**
3. **FRAME-GUARD ANY EASE.** The two-hand ease is guarded on `lvframe60` because
   while firing it is called twice per frame, *"which would make the grip engage
   twice as fast during a burst as at rest"* (`:1106-1108`).
4. **DO NOT COUNTER-ROTATE BY ABSOLUTE HEAD YAW.** *"A 360 spin unwound the
   elbows."* A smoothed follower yaw instead (`:186, :194-197`).
5. **A SEPARATE GESTURE FRAME.** Raw play-space quats with no mirror, no offset,
   no smoothing, no recoil, because *"swing gestures need one self-consistent
   basis"* (vr_openxr.h:57-61).
6. **A SEPARATE RECENTRE QUAT.** Anything already in play space must use
   `vr_recenter_rot_Q`, not the HMD quat, **or head yaw folds in twice**
   (vr_openxr.cpp:289-292). **`46` reached the same conclusion the hard way.**
7. **Mirroring a left hand: subtract the trim once, do not negate it** —
   *"negating o.x outright overshot by exactly 2x"* (bondgun.c:11131-11137).

## §5 — WHAT WE CANNOT TAKE

- **Weapon enum labels.** The offsets transfer as CLASSES — pistol, rifle-with-
  foregrip, launcher, thrown — not as a mapping. Same for the ~60 recoil profiles.
- **Character-height mode** — PD is multi-character (Joanna 159, Elvis 106).
  GoldenEye is Bond-only: drop the mode or hardcode.
- **Per-stage world scale** (85.0, or 42.5 on four stages) and the cutscene FOV
  formula. **The structure transfers; the numbers are PD stage geometry.** Ours
  is `77`'s measured ~50 u/m and `86` §3.9's one-knob-three-jobs problem, which
  slice S1 must still split.
- **Reload-snap and belt-grab zones** — indices into PD's model hierarchy
  (`VR_MAG_R_MTX_INDEX 38`) and Joanna's belt position.
- **Collision call signatures.** `cdCollectGeoForCylMove` / `cdExamCylMove02` /
  `cdTestLos05` have GE cognates, not twins. **The SEQUENCE transfers**: collect
  rooms -> disable own perimeter -> cylinder test -> LOS test -> re-enable.
- **Quest/GLES paths** and `vr_android_jni.cpp`.

## §6 — WHAT THIS DOES TO `86`'s SLICES

| Slice | Was | Now |
|---|---|---|
| **G2** rotation convention | A **sign sweep** the wearer judges | **A CHECK.** `{w,-x,y,-z}` + a 1.5708 rad X offset, applied after smoothing. One launch confirms or denies |
| **G3** grip offsets | A table to derive by wearing | **A TABLE TO VERIFY**, six classes, plus the Ry180 basis warning |
| **A1** bullet follows gun | Pre-load both integrators via a new patch | Unchanged in physics — **`x/(1-damp)` confirmed verbatim** — but §1 changes what "done" looks like |
| **A2** world aim dot | **Mandatory**, because `90` said no unclamped shot path exists | **Re-open.** PD leaves the SHOT unclamped and clamps only the drawn crosshair. **A2 may be a nicety, not the mechanism** |
| **H2** head height | Two writes, option B-i | Confirmed shape, **plus the crouch-state thresholds and the running-max bug already solved** |
| **R1** roomscale | Probe on sight-blocking geometry | Confirmed, **with radius 12, a +/-10 slab, a second LOS test, and the fade-before-HUD stereo bug** |

**Nothing here is built. `48` rule 1.** The next session picks slices with a
table of measured constants instead of a sweep plan.
