# 88 — READ 7, AND THE THREE READS IT CLOSED ON THE WAY

**2026-08-23, after `87`. `87` opened four reads and said read 7 was the one
that decides whether A1 and the hand slices can coexist. This is read 7 —
and doing it answered reads 8 and 9's shape, plus `86` §5 A1's first owed read.
No launches, no build, no headset.**

> # ►► AMENDED BY `90`. §5 STANDS; THE LABELS DO NOT. ◄◄
>
> **`90` establishes that `field_FFC`/`field_A38` drive the GUN MODEL'S
> POINTING and the muzzle flash — NOT the bullet. The bullet comes from the
> clamped `crosshair_angle`.** §5's mechanism is unaffected: `gunfire.c:568`
> still aims the gun at `field_A38`. **But "the gun points where the bullet
> goes" is too strong — the gun points where `field_FFC` says, the bullet goes
> where `crosshair_angle` says, and A1 must write BOTH or they diverge by
> construction.** **And §5.1's z ≈ −1000 argument is corroborated but NOT
> proven** — `initBondDATA.c:114` initialises `field_A40` to **+1000**, the
> opposite sign. `90`.
>
> # ►► THE ANSWER TO READ 7 IS "DO NOT SUPPRESS IT". ◄◄
>
> **`87` asked whether `itemstats->PlayX/PlayY/PlayZ` can be zeroed under VR so
> `field_FFC` stops moving the gun model. They CAN be — they have exactly three
> readers and all three are in that one block. But they SHOULD NOT BE, and the
> reason is a line neither `86` nor `87` had read:**
>
> ```c
> /* gunfire.c:568, inside gunUpdateAndFire */
> matrix_4x4_align(&tmpmtx, 0.0f, gunofs.x - hand->field_A38,
>                                 gunofs.y - hand->field_A3C,
>                                 gunofs.z - hand->field_A40);
> ```
>
> **`field_A38/A3C/A40` is the AIM POINT** — it is what `sub_GAME_7F067AB4`
> writes from `field_FFC` (`87` read 1). **So the engine already orients the gun
> along the vector from the aim point to the gun's position.**
>
> ## THE GUN ALREADY POINTS AT WHERE THE BULLET GOES. BY DESIGN. IN STOCK CODE.
>
> **`87` called the `field_FFC` overlap a collision between A1 and G1-G3 —
> "two features wanting one variable to mean two different things". That was
> wrong, and it is corrected here at source. Rule 10.** It is not a collision.
> **It is the coupling slice A1 was going to have to build, already present and
> already pointing the right way**: write the aim point and the gun model
> follows it, without a rotation write, without a sign sweep, without `86`
> slice G2's convention hunt for this part of the problem.
>
> **`85`'s `-SeamNoRot` was not a workaround for a missing rotation. It was
> the wearer refusing to fight a rotation the engine was already computing.**

---

## 1. READ 7, LITERALLY: THE MULTIPLIERS AND THEIR READERS

**Every reference to `PlayX`, `PlayY`, `PlayZ` in `lib/ge/src`, `src`, `patches`:**

| Where | What |
|---|---|
| `gun.h:38`, `:44`, `:49` | the three declarations |
| **`gunfire.c:512`** | `gunofs.x += ((field_FFC.x - c_screenleft - W*0.5) * itemstats->**PlayZ**) / (W*0.5)` |
| **`gunfire.c:516`** | `gunofs.y -= (... ) * itemstats->**PlayY** / (H*0.5)` — **above screen centre** |
| **`gunfire.c:520`** | `gunofs.y -= (... ) * itemstats->**PlayX** / (H*0.5)` — **below screen centre** |

**Three readers. All three in one nine-line block. Nothing else in either
repository touches them.** Suppression is mechanically trivial.

### THE HEADER COMMENTS DO NOT MATCH THE USE, AND SOMEBODY WILL TRUST THEM

```c
/* gun.h:36-49 */
f32 PlayX;   /* "The amount of play the guns are given when you move forward/back." */
f32 PlayY;   /* "...when you move side to side." */
f32 PlayZ;   /* "...when you move up or down." */
```

**But `PlayZ` multiplies the HORIZONTAL term and `PlayX`/`PlayY` both multiply
the VERTICAL one**, split by whether the aim point is above or below screen
centre. **The names and the doc comments are a decomp artefact and they are
wrong about which axis is which.** Anyone tuning these by name will tune the
wrong one. Noted here rather than edited — the tree is a decomp and renaming is
`no6969el/goldeneye-native`'s business, not ours.

**Also: the field name is literally "play", as in slack.** The stock game uses
this to let the gun drift toward the crosshair. **That is not a bug to be
suppressed; it is the flat game's version of exactly what VR wants.**

---

## 2. THE TRAP THAT WOULD HAVE COST A SESSION: THE STATS STRUCT IS NOT CONST

```c
/* gun.c:708 */
WeaponStats *get_ptr_item_statistics(ITEM_IDS item) {
    if (gitem_structs[item].has_no_model == 0) return gitem_structs[item].item_weapon_stats;
    return &default_weaponstats;
}
```

**It returns a pointer INTO a shared, mutable, per-item-type table. And the
table is written at runtime:**

```c
/* gun.c:735 */
void copy_item_in_hand_to_main_list(coord3d *pos) {
    stats->PosX = pos->x;  stats->PosY = pos->y;  stats->PosZ = pos->z;
}
```

> **So "zero `PlayX/Y/Z` under VR" — the obvious implementation — would be a
> PERMANENT MUTATION OF GAME DATA, shared by every holder of that weapon,
> surviving until the table is reloaded.** Rule 7: know who destroys what you
> build, and when. **Here the answer is "nobody, and that is the problem."**
>
> Any suppression must happen **at the read site**, never in the table.
> **Recorded so the next session does not discover it by playing.**

---

## 3. AND THE READ SITE IS NOT PATCHABLE ANYWAY

| | |
|---|---|
| The block at `:512-521` lives in | **`gunUpdateAndFire`**, `gunfire.c:315-980` |
| **Length** | **666 lines** |
| `78`'s verdict | **not `RECOMP_PATCH`-able** — and `83`'s seam search says the same, calling it *"larger"* than `gunTickHandState`'s ~1700 |

**Confirmed independently here. `78` and `83` were right and this is a third
measurement agreeing with them.**

**So even if suppression were wanted, there is no patch that reaches it.** The
only way in is the one `83` already found — and that turns out to be the
opening.

---

## 4. THE OPENING: OUR OWN SEAM HOOK ALREADY RUNS 48 LINES UPSTREAM

`85`'s seam is `RECOMP_PATCH gunSetHorizontalOffset` (`ge_vr_bindtest.c:860`),
chosen by `83` because it is the only patchable leaf between
`gunTickHandState`'s clear of `field_92C` and the placement's read of it.

**It is called from `gunfire.c:464 — inside `gunUpdateAndFire`, in the same
frame, 48 lines BEFORE the `field_FFC` read at `:512`.**

```
gunfire.c:464   gunSetHorizontalOffset(handnum)      <- OUR PATCH ALREADY RUNS HERE
gunfire.c:512   gunofs.x += f(field_FFC.x) * PlayZ   <- reads a player global
gunfire.c:548   gunofs += field_8EC translation      <- 85's seam lands here
gunfire.c:568   matrix_4x4_align(gunofs - field_A38) <- THE GUN IS AIMED
```

> **`field_FFC` is `g_CurrentPlayer->field_FFC` — a player global, not a local.
> A write from the seam hook at `:464` is visible at `:512` in the same frame.**
>
> **So slice A1 does not need a new `RECOMP_PATCH` name at all, and `87` read 6's
> "one long build for A1" may be wrong.** The aim write can land in the leaf
> that is already patched, already runs every frame, already runs per hand, and
> already runs in the right window.
>
> **This is not a recommendation yet — it is a read.** Writing `field_FFC` from
> the seam skips `caclulate_gun_crosshair_position_rotation`'s integrator
> entirely rather than pre-loading it, which changes what `38`'s inversion is
> for. **Both routes are now open and they should be discussed before either is
> built.** `48` rule 1.
>
> | Route | Cost | Risk |
> |---|---|---|
> | **Patch `caclulate_gun_crosshair_position_rotation`** (`86` A1 as planned, plus `87`'s two-integrator correction) | a **new** patch name, long build | none known; it is the function that owns the quantity |
> | **Write `field_FFC` and `field_A38/A3C/A40` from the existing seam hook** | **no new name, no long build** | the integrator still runs at `:6072`/`:6077` and will fight the write unless it is also pre-loaded or gated. **Order within the frame is established (§6) but the interaction is not** |

---

## 5. WHAT THE COUPLING MEANS FOR SLICES G2, A1 AND A2

**`matrix_4x4_align(&tmpmtx, 0, gunofs - aimpoint)` at `:568`, then
`matrix_4x4_multiply_homogeneous_in_place(&tmpmtx, &rotmtx)`.**

| Slice | `86` said | Now |
|---|---|---|
| **G2, rotation** | *"a convention sweep, one axis at a time; a wrong rotation HIDES the gun"* | **Still true for the seam's own rotation — but the gun's AIM-axis orientation does not need sweeping at all. It falls out of the aim point.** G2's sweep is for roll about the barrel and the grip's basis, not for where the barrel points |
| **A1, the bullet** | *"the bullet goes where the gun points"* | **Inverted, and this is the better direction.** In this engine **the gun points where the bullet goes.** Write the aim and both follow. `86`'s framing has the causality backwards for GoldenEye |
| **A2, the aim dot** | *"the only honest way to show where the shot goes"* | **Unchanged, and now cheaper to justify** — but note the gun model itself becomes a second indicator, since it visibly points along the fired ray |
| **`85`'s `-SeamNoRot`** | *"rotation is deliberately off because a wrong one HIDES the gun"* | **The right default for a reason nobody had yet named**: the seam's rotation multiplies into the same `rotmtx` that `:568`'s align writes, so a seam rotation and the engine's aim-align compose. **`85` was right by observation before it was right by source.** Rule 3, and the wearer got there first again |

### 5.1 `matrix_4x4_align`, READ TO THE BOTTOM — because §5 rests on it

`matrix_4x4_align` (`matrixmath.c:798`) is two lines: `RadToDeg(angle)`, then
**`guAlignF`** — the stock N64 SDK routine, `libultra/gu/align.c:27`. Its body:

```c
guNormalize(&x, &y, &z);
...
mf[2][0] = -x;   mf[2][1] = -y;   mf[2][2] = -z;
```

**Row 2 of the matrix is `-dir`.** In this engine's row-vector convention that
row is the image of the local **+Z** basis vector, so **local +Z maps to `-dir`
and local −Z maps to `+dir`**, with `angle` rolling about that axis.

**With `dir = gunofs - aimpoint`:** `sub_GAME_7F067AB4` writes the aim point
from `transformAndNormalizeByLength2Dto3D(..., 1000.0f)`, whose `z` is
`-norm` — **so the aim point sits at z ≈ -1000**, a long way in front of the
camera in a −Z-forward view space, while `gunofs.z` is a few tens. **`dir`
therefore has a large positive z.**

> **WHAT IS ESTABLISHED: the gun's orientation is built on the axis through the
> gun position and the aim point. That is §5's claim and it holds.**
>
> **WHAT IS NOT ESTABLISHED: which end of that axis is the muzzle.** That
> depends on the viewmodel's own forward convention, which this read did not
> touch. **The stock game visibly points its guns at the crosshair, so the
> composition evidently resolves correctly — but that is observation, not
> source, and rule 3 says not to promote it.** Anyone building on §5 must
> establish the model convention first; it is a read, not an experiment, and
> it is owed.
>
> **Recorded this way on purpose.** `57`'s title is wrong because an impression
> was promoted to a finding two hours after rule 3 was written down. **This is
> the same shape and it is being refused.**

**The falsifier, and it costs one launch inside a slice already planned:**
**sweep the stick horizontally with `-SeamNoRot` and watch whether the gun model
yaws.** If it does, `:568` is live and everything above holds. If it does not,
this whole section is wrong and something between `:512` and `:568` is
suppressing it. **A gate that a working build would fail if this were false.**

---

## 6. THE THREE READS THIS CLOSED ON THE WAY

### `86` §5 A1 owed read 1 — **WHICH OF `bondview2.c:6072` / `:6077` IS AIM MODE**

**ANSWERED FROM SOURCE. `:6077` is aim mode.** And the split is **not** what
`86` assumed:

```c
/* bondview2.c:6036-6042 — the branch is on CONTROLLER CONFIG, not on aim mode */
if (moveData.canSwivelGun)      g_CurrentPlayer->controldef = CONTROLLER_CONFIG_HONEY;
else if (moveData.canManualAim) g_CurrentPlayer->controldef = CONTROLLER_CONFIG_KISSY;

if (controldef == CONTROLLER_CONFIG_HONEY) {          /* HIP FIRE */
    ... auto-aim nested inside ...
    sub_GAME_7F067F58(sp70, ..., MAX_AIMLOCK_SPEED_DEFAULT);      /* :6072 */
} else if (controldef == CONTROLLER_CONFIG_KISSY) {   /* AIM MODE */
    sub_GAME_7F067FBC(stickX * 0.65f / 80.0f, stickY * 0.65f / 80.0f);  /* :6077 */
}
```

| | |
|---|---|
| **`:6072`, `CONTROLLER_CONFIG_HONEY`** | **hip fire.** `canSwivelGun`. Speed-derived turn, **auto-aim nested inside it** as a conditional override of the y term |
| **`:6077`, `CONTROLLER_CONFIG_KISSY`** | **AIM MODE.** `canManualAim`. **Raw control stick**, scaled 0.65/80 |

> **`86` §5 A1 predicted the split would be "auto-aim vs manual", by analogy
> with PD's five callers. It is CONTROLLER CONFIG, with auto-aim nested one
> level in.** Corrected at source. Rule 10.
>
> **This matches `36` exactly** — *"hip-fire aim vs head: decoupled, confirmed
> worn. Aim mode is not."* **Now we know why: they are two different call sites
> with two different input scalings, and only one of them was ever addressed.**
> Both call the same function, so **a patch there covers both**, which is
> `86` gate G-A1-4's whole basis and it survives.

### `87` READ 8 — **`sub_GAME_7F0680D4` HAS NO CALLERS**

`grep` across `lib/ge/src`: **the definition at `gunfire.c:4806` and nothing
else.** It is **dead code in the shipped game.**

**It is still the most interesting function in the file for us** — it takes a
3D direction, builds a rotation, projects its Z column ×1000 through
`transform3Dto2DCoords`, writes **both** `crosshair_angle` and `field_FFC`, and
calls `sub_GAME_7F067AB4`. **That is slice A1's entire job, already written,
and it bypasses the clamp.**

> **But "dead in the shipped game" means "never executed on real hardware",
> which means it is UNTESTED ENGINE CODE, not a proven path.** `64` killed four
> theories that were reasonable on paper. **If A1 calls it, that is a slice with
> its own gate, not a shortcut.** Recorded as a candidate, not a plan.

### `87` READ 9 — **`autocrouchpos`: NOT YET CLOSED, BUT NARROWED**

Not fully read. **`87` read 9 stands open** and it should be finished before
H2 option B is chosen, not during. Named again here so it is not lost.

---

## 7. WHAT THIS CHANGES — RULE 10, LISTED

| Claim | Where | Now |
|---|---|---|
| *"`field_FFC` also moves the gun model … A1 and G1-G3 collide"* | **`87`**, finding 2 | **The overlap is real; calling it a COLLISION was wrong.** `gunfire.c:568` aims the gun at the aim point by design. **It is the coupling A1 wanted** |
| *"the bullet goes where the gun points"* | `86` §5 slice A1's title | **Backwards for this engine. The gun points where the bullet goes** — `gunfire.c:568` |
| *"one long build for A1"* | **`87`** read 6 | **Possibly none.** The already-patched seam leaf runs 48 lines upstream of the read, in the same frame, and `field_FFC` is a player global |
| *"which of `:6072` / `:6077` is aim mode"* | `86` §5 A1, owed read 1 | **`:6077` is aim mode. And the split is CONTROLLER CONFIG, not auto-aim vs manual** |
| *"`sub_GAME_7F0680D4` … A1 may be a caller, not a patch"* | **`87`** read 8 | **It has NO callers. Dead in the shipped game — a candidate, and an untested one** |
| `PlayX/PlayY/PlayZ` doc comments | `gun.h:36-49` | **Wrong about which axis each drives.** `PlayZ` is horizontal; `PlayX`/`PlayY` are vertical, split above/below centre |
| *"`-SeamNoRot` … rotation is deliberately off"* | `85` | **Right, and now explained**: the seam's rotation composes with `:568`'s aim-align into the same `rotmtx` |

---

## 8. THE READS STILL OWED

**Two from `87` survive, one is new, and none is an experiment.**

9. **Does `autocrouchpos` have a consumer that would fight a written-in head
   height?** `87` read 9, still open. **Before H2 option B is chosen.**
10. **Name the function owning `bondview2.c:4564`**, for H2 option B's patch
    name. `87` read 10, still open.
11. **CLOSED BEFORE THIS DOCUMENT SHIPPED — see §5.1.** The load-bearing claim
    was checked rather than left owed. **The axis is confirmed; the nose
    direction is not, and §5.1 says so plainly.**

---

## 9. WHAT DID NOT CHANGE

**`87`'s two-integrator finding stands and is the most important thing either
document found.** Nothing here softens it: `crosshair_x_pos` drives the
crosshair, `gun_azimuth_angle` drives the bullet, they are damped differently,
and **both must be pre-loaded** whichever route A1 takes.

**And `86`'s slice order stands.** S0 first, H1 second. **Nothing in this
document is built, and `48` rule 1 still holds: plan, discuss, then execute.**
