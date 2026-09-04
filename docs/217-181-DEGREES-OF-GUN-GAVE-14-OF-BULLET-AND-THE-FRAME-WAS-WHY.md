# 217 — 181 DEGREES OF GUN GAVE 14 DEGREES OF BULLET. THE DIRECTION WAS IN THE WRONG FRAME, AND THE GAME HAD THE RIGHT ONE ALL ALONG.

**2026-08-26. Tiers per `182`. `[MEASURED]` from `216`'s recorder, first run.
BUILT, UNRUN.**

---

## §1 — THE MEASUREMENT

**14 shots, five groups, `SHOTWORLD`:**

| | |
|---|---|
| **the GUN's world yaw** | `+37.9` -> `+88.5` -> `-143.4` — **181 DEGREES** |
| **the BULLET's world yaw** | `-135` to `-149` — **14 DEGREES** |
| every impact | within **0.5 m** of one spot, at a near-constant **1.8-2.0 m** from the gun |

**THE BULLET DID NOT FOLLOW THE GUN.** It landed in essentially one place
regardless of aim. **And group 5's apparent agreement was a coincidence:** the
wearer turned the gun to `-143`, which is where the bullets were already going.

> **THIS IS `184`'s ORIGINAL COMPLAINT, UNFIXED.** *"nothing is related to where
> you're pointing it... it's only focusing on the general quadrant."* **`A1`
> fixed that for the CROSSHAIR** (`190`: *"the target followed my hand
> direction"*). **The BULLET was never fixed, and nothing measured it until now**
> — every instrument before `216` was in CAMERA space, and the question is about
> direction in WORLD space.

---

## §2 — ►►►► THE CAUSE, AND THE GAME IS NOT AT FAULT ◄◄◄◄

**`[READ]` `chrprop.c:947-952`, the hitscan path:**

```c
bullet_path_from_screen_center(&shotdata.viewOrigin, &shotdata.viewDir, hand);
shotdata.dir = shotdata.viewDir;
mtx4RotateVecInPlace(currentPlayerGetViewToWorldMtxf(), &shotdata.dir);   // -> WORLD
dest = shotdata.dir * 65535 + shotdata.gunpos;
```

**THE GAME HANDLES IT CORRECTLY — IF `arg1` IS IN THE GAME CAMERA'S FRAME.**

**`[READ]` OURS IS IN THE HEADSET'S.** `ge_vr_aim.c` builds the direction from
`geVrAimFwdHead = Rhead^T * fwdWorld` (`158` §5) — the controller's forward **in
the head's frame.**

**AND `[READ]` `194` ESTABLISHED THE GAME CAMERA NEVER RECEIVES THE HEAD
ROTATION:** the head pose reaches the eye VIEW matrix and is composed onto the
game's view matrix **at render time only.**

> ### **SO THE TWO FRAMES COINCIDE ONLY WHEN THE HEAD IS AT NEUTRAL.**
> That is exactly why forward was roughly right and off-axis was wild, and why
> `[REPORTED]` *"I shot upwards to the right, and it shot to the LEFT of the
> gun."*
>
> **IT IS `194`'s FAULT FOR THE THIRD TIME** — after the bullet's ORIGIN (`194`)
> and the drawn gun's ORIENTATION (`200`). **Each time, a value computed in the
> headset's frame was handed to something that expected the game's.**

**COUNTER-EXAMPLE SEARCH (`182` §2, `209` §4.3):** the rival explanation is that
the direction never reaches the game at all — a stale or ignored vector. **That
predicts ZERO correlation between gun and bullet; `[MEASURED]` there is a weak
one (50 deg of gun gave 9 deg of bullet), and the impacts drift with elevation.
A wholly ignored vector cannot do that.** A frame mismatch can, and does.

---

## §3 — THE FIX NEEDS NO CONVERSION AND NO NEW GAME SYMBOLS

**THE GAME ALREADY BUILDS THE GUN'S MATRIX IN ITS OWN CAMERA FRAME, EVERY
FRAME** — `gunfire.c:570-572`, `hand->gunmtx_camspace` — **and it already carries
our seam, because `field_8EC` pre-multiplies `rotmtx` at `:548` BEFORE `gunmtx`
is copied from it** (`83`).

**`[READ]` `bondview.h:210`: it is the `Mtxf` immediately before
`throw_item_pos_related` (`0xad8`), so it begins at `0xa98` — and `structs.h` had
EXACTLY SIXTEEN loose `s32 field_A98..field_AD4` there, 64 bytes, the size of one
`Mtxf`.** **IT HAS BEEN IN OUR STRUCT, UNNAMED, FOR THE WHOLE PROJECT.**

**Named, not moved: every other field keeps its offset.** `115`'s header rule
applies — **this is a `structs.h` change, so the build is a FULL one.**

**ROW OR COLUMN IS NOT ASSUMED.** `158` §2 left that open for the SEAM and `203`
settled it there, **but this is a different matrix.** Both forms are computed and
**`-BulletDirCol` picks** — `48`: publish both, let one run decide.

**KNOB `-NoBulletDir` reverts. TWO NEW SYMBOLS -> BUILD TWICE (`136`).**

---

## §4 — `G-217`

**POINT THE GUN ANYWHERE AND SHOOT. THE BULLET MUST FOLLOW THE GUN.**

- **If it is MIRRORED or 90 degrees out -> `-BulletDirCol`.** That is the
  row/column question, not a failure.
- **If it still lands in one spot -> the frame theory is wrong** and `216`'s
  recorder should be re-run to say so, with the same five groups.

**AND `216`'s RECORDER STAYS IN.** After the fix it becomes the regression check:
**the gun's world yaw and the bullet's world yaw should track each other**, and
the residual between them is then the parallax `215` measured — **which is the
NEXT problem and a much smaller one.**

---

## §5 — WHAT IS OWED

1. **BUILD TWICE (full rebuild — `structs.h` changed). `G-217`.**
2. **THEN RE-RUN `216`'s FIVE GROUPS** and read the gun-vs-bullet yaw table
   again. **That is the pass/fail, and it is arithmetic, not an impression.**
3. **THEN `211`'s SOLVER** for the remaining parallax — **and only then, because
   a solver built on top of a bullet that ignores the gun would be measuring
   nothing.**
4. **`210`'s IMPACT DISTANCE IS WRONG AND MUST BE REFITTED** (`216` §1):
   it was computed against `g_CurrentPlayer->pos`, which `[MEASURED]` sits **48 m
   from the gun** — it is NOT the player's world position (`gun.c` uses
   `getCurrentPlayerProp()->pos`). **The right origin is the gun's own world
   position, which `216` now logs.** That is where the 626 m and 2.5 km readings
   came from.

**NOTHING STAGED. THE COMMIT IS THE OWNER'S.**
