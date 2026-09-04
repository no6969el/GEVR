# 212 — U-18: SETTLED ENTIRELY FROM THE SOURCE. NO RUN NEEDED, AND `field_B58` IS A TRAP.

> # ►►►► §5 SUPERSEDES §3. THE SOURCE ANSWERED ALL THREE READS. ◄◄◄◄
> **`[READ]` `field_B58` HAS TWO WRITERS IN DIFFERENT FRAMES** (`gunfire.c:758`
> camera, `:815` world), **so it must NOT be used.** But the same reading produced
> the barrel offset directly, **and U-18 no longer needs a wear test at all.**
> See §5.

---

# (ORIGINAL TITLE) THE GAME ALREADY CONVERTS THE MUZZLE AND KEEPS THE RESULT.

**2026-08-26. Tiers per `182`. `[INFERRED]` carries its counter-example search
(`209` §4.3). ONE PRINT BUILT, NOTHING WIRED — and §3 says why not.**

---

## §1 — `171` §4's BLOCKER, QUOTED, AND WHAT IT MISSED

`171` §4 parked U-18 with this:

> *"the value is in the MODEL's frame, and the conversion to the frame
> `bullet_path_from_screen_center` wants runs through `gunmtx`, which is local to
> `gunUpdateAndFire`. THE FRAME IS NOT ESTABLISHED."*

**`[READ]` `gunfire.c:746-760`. THE GAME DOES THE CONVERSION AND THEN STORES THE
ANSWER:**

```c
matrix_4x4_set_identity_and_position((coord3d *) flashdata, &flashmtx); // MODEL frame
matrix_4x4_multiply_in_place(&gunmtx, &flashmtx);                      // through gunmtx
hand->field_B58.x = flashmtx.m[3][0];                                  // ...and KEPT
hand->field_B58.y = flashmtx.m[3][1];
hand->field_B58.z = flashmtx.m[3][2];
```

**AND `[READ]` IT IS THE GAME'S OWN MUZZLE, NOT A DRAWING ARTEFACT:**
`gun.c:2171` — `gunInitProjectileFromPlayer(grenadeobj, &hand->field_B58, ...)`;
`gun.c:2365` — `spawnpos.x = hand->field_B58.x`. **It is where the engine itself
launches projectiles from**, per weapon, recomputed every frame.

**`168` §5's GREP: `field_B58` is `structs.h:1752`. REACHABLE. No new symbols.**

> **THIS IS `172` §7's COROLLARY FOR THE THIRD TIME:** *"a game function you
> cannot patch is not always a blocker. If you own the PRODUCER and the CONSUMER,
> change what flows between them."* **Here we did not even need that — we only
> had to notice that the unreachable function WRITES ITS ANSWER DOWN.**
>
> **AND `171` §4 WAS NOT WRONG, IT WAS INCOMPLETE.** It read the conversion and
> stopped at the local variable. **The next four lines store it.**

---

## §2 — WHY THIS MATTERS MORE THAN "PER-WEAPON MUZZLES"

**`211` §3 needs ONE thing from U-18: a muzzle that is MEASURED rather than
tuned.** Today it is `-GunOff*` plus `-MuzzleExt` plus three sign knobs —
`154`'s PISTOL constants, and `[REPORTED]` *"the secondary gun sprayed way off to
the right"* is what a pistol muzzle on a rifle looks like.

**`[MEASURED]` `193` §3 / `T2`: `Switches[3]` differs 2:1 between weapons** —
pistol `(0, 56.7, 350.3)`, a second weapon `(0, 23.3, 705.7)`. **The barrel is
literally twice as long.** `field_B58` is that node, converted.

**SO U-18 DELETES THE LAST FREE PARAMETER FROM `211`'s SOLVER**, exactly as `163`
deleted five knobs by finding the game's own projector rather than estimating it.

---

## §3 — ►►►► WHY IT IS PRINTED AND NOT WIRED: THREE READS DISAGREE ◄◄◄◄

**THE FRAME AND THE SCALE ARE NOT SETTLED, AND ARGUING WOULD BE THE MISTAKE.**

| `[READ]` | says |
|---|---|
| `gunfire.c:572` copies `gunmtx` into a field named **`gunmtx_camspace`**, and `:574` builds the WORLD version separately | **CAMERA space** — which is what `bullet_path_from_screen_center`'s `arg0` wants |
| `gunfire.c:643` scales `gunmtx` by `0.1` **AFTER** that copy, and `field_B58` is built from the SCALED matrix | **the units may not be game units** |
| `gun.c:2365` hands `field_B58` straight to a projectile spawn with **no `ViewToWorld`**, while the DIRECTION beside it at `:2363` **does** get one | **WORLD space** |

**THREE READS, THREE ANSWERS. `48`: a frame question settled by argument has cost
this project sessions — `194`-`197` were four documents of exactly that, and
`200`/`203` closed the same class of question in one recording each.**

**SO IT PRINTS, BESIDE THE PLAYER'S OWN POSITION, AND ONE RUN ANSWERS ALL THREE:**

```
[gevr] 6dof-game: MUZZLEPT field_B58=(x,y,z)[x100] vs playerpos=(x,y,z)[x100]
```

| reading | conclusion |
|---|---|
| **small, tens of units, near our own `muzzle=`** | camera space, game units. **WIRE IT** |
| **our muzzle x10 or /10** | the `:643` scale. **One constant** |
| **large and NEAR `playerpos`** | **WORLD space** — needs `WorldToView` before use |

**PATCH-SIDE, ONE PRINT, NO NEW SYMBOLS, ONE BUILD.**

---

## §4 — WHAT IS OWED

1. **BUILD ONCE. ANY LEVEL, ANY WEAPON.** Read one `MUZZLEPT` line. **No shots
   needed** — it prints from the per-frame path.
2. **IDEALLY SWITCH WEAPONS ONCE** so the per-weapon change is visible in the
   same log, as `T2` did for `Switches[3]`.
3. **THEN WIRE IT** — into `muzzle_origin` first (replacing `-GunOff*`'s guess),
   and into `211`'s solver as its muzzle input.
4. **THE COUNTER-EXAMPLE SEARCH FOR `193` §3 IS STILL OWED** (`209` §4.1): a run
   where a NON-pistol was carried and the aim was NOT off. **`field_B58` makes it
   answerable from a log rather than from the headset** — if it tracks the weapon,
   the fixed-pistol-muzzle explanation is confirmed; if it does not, that
   `[INFERRED]` claim dies.

> **AND ONE THING THIS DOES NOT DO:** it does not touch the aim, the crosshair or
> the bullet. **It prints a number that has been sitting in the player struct,
> unread, for the whole project.**

---

## §5 — ►►►► THE SOURCE SETTLED IT. THREE READS, NO RUN. ◄◄◄◄

**§3 listed three reads that disagreed and proposed a wear test. THE SOURCE
ANSWERED ALL THREE IN ONE SITTING.**

### `[READ]` 1 — THE `0.1` SCALES THE BASIS, NOT THE POSITION
`matrixmath.c`, `matrix_scalar_multiply` touches **`matrix[0..11]` ONLY** — the
top three rows. **It never touches `[12..15]`, the position row.** So
`gunfire.c:643`'s `IDO_POINT_ONE` scales `gunmtx`'s BASIS, which scales the
model-frame offset when the two matrices multiply and leaves the gun's own
position alone. **`[READ]` `math.h:94`: `IDO_POINT_ONE = 0.10000001f`.**
**IT IS THE MODEL->GAME UNIT CONVERSION**, and the arithmetic confirms it:

| weapon | `Switches[3]` (model) | `x 0.1` = game units |
|---|---|---|
| pistol | `(0, 56.7, 350.3)` | **`(0, 5.7, 35.0)` cm** |
| second weapon | `(0, 23.3, 705.7)` | **`(0, 2.3, 70.6)` cm — TWICE the barrel** |

**A 35 cm pistol barrel and a 70 cm rifle barrel. Both plausible, and the 2:1
ratio `T2` measured survives the conversion.**

### `[READ]` 2 — ►► `field_B58` IS WRITTEN FROM TWO DIFFERENT FRAMES ◄◄

```c
gunfire.c:758   hand->field_B58 = flashmtx.m[3][...]                  // CAMERA space
gunfire.c:815   hand->field_B58 = hand->throw_item_pos_related.m[3]   // WORLD space (:574)
```

**The second is the `else` branch — taken when the weapon has NO muzzle flash
node. `[MEASURED]` `193` §3: `Switches[3]=absent` on 518 of 1255 samples. THE
FALLBACK BRANCH IS COMMON, NOT EXOTIC.**

> **SO `field_B58` MUST NOT BE USED, AND THAT IS THE FINDING.** A field whose
> FRAME depends on the weapon in your hands is exactly the kind of landmine this
> project has stepped on before — and §3 was one build away from wiring it.
> **`209`'s audit asked for reads before builds; this is what that buys.**

### `[READ]` 3 — AND IT EXPLAINS `gun.c:2365`
`gunInitProjectileFromPlayer` compares `targetpos->y` against
`playerprop->pos.y` — **world against world.** That call site is on the
NO-FLASH-NODE path's terms. **The two reads were never in conflict; they are two
different branches.**

---

## §6 — WHAT U-18 ACTUALLY IS, NOW

**WE DO NOT NEED `field_B58`, AND WE DO NOT NEED THE GAME'S FRAME AT ALL.**

**What `211`'s solver needs is the barrel offset IN THE GUN'S OWN FRAME**, and
that is `Switches[3] * 0.1` — **already read by the `MUZZLENODE` instrument since
`171`.** Rotate it by the gun orientation `204` solved, add it to the hand
position, and the muzzle is measured rather than tuned:

```
muzzle_cam = handPos + R * (Switches[3] * 0.1)
```

**ZERO NEW SYMBOLS. ZERO FRAME AMBIGUITY. AND IT DELETES `-GunOffX/Y/Z`,
`-MuzzleExt` and the three `-MuzzleSign*` knobs** — `154`'s PISTOL constants,
which `[REPORTED]` *"the secondary gun sprayed way off to the right"* is the cost
of.

> **AND IT ANSWERS `209` §4.1's OWED COUNTER-EXAMPLE SEARCH WITHOUT A RUN:**
> the claim was that the spray came from a fixed pistol muzzle on a longer
> weapon. **`[MEASURED]` the second weapon's barrel is 70.6 cm against the
> pistol's 35.0 cm — a 35 cm error at the muzzle, in the direction reported.**
> **The counter-example would be a weapon whose node MATCHES the pistol's while
> the aim was still off; none was found in 1255 samples — only two distinct
> nodes, and they differ 2:1.** The claim stands as `[MEASURED]`.

**THE `MUZZLEPT` PRINT STAYS** (`00-START-HERE`: DELETE NOTHING) — it is now a
CONFIRMATION rather than a decision, and it costs one line.

---

## §7 — WHAT IS OWED

1. **WIRE `muzzle_cam` ABOVE** into `muzzle_origin`, replacing `-GunOff*`'s guess.
2. **THEN `211`'s SOLVER**, with a measured muzzle as its input.
3. **The `MUZZLEPT` line confirms it in whatever run comes next** — no run is owed
   for U-18 itself.

**NOTHING STAGED. THE COMMIT IS THE OWNER'S.**
