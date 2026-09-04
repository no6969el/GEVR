# 201 — THE AXIS SIGNS WERE THE ROLL. THE REMAINING YAW IS A SECOND DRIVER: `163`'s `gun_azimuth` WRITE.

**2026-08-25. Tiers per `182`. Two knob-only results and one small build.**

---

## §1 — `G-200` IS TWO-THIRDS PASSED, AND ONE PART OF IT IS NEW GROUND

> `[REPORTED]`: ***"When I walked forward and backwards... everything looked like
> it was stable, meaning that it didn't move or adjust position."***

**THE POSITION IS SOLVED.** `200` §2's raw play-space hand position holds under
walking — **the first time in this project that the gun has stayed put while the
wearer moved.** `194`, `195`, `196` and `197` were four attempts at this and the
answer turned out to be that the whole head term should never have been there.

> `[REPORTED]` after dropping the legacy axis signs: ***"now it turns in the right
> direction when I turn my wrist."***

**`-HandAxisX 1 -HandAxisZ 1` FIXED THE ROLL, AND THE PREDICTION WAS MADE BEFORE
THE RUN.** `155` measured `-1 -1` against the LEGACY composition; `185` `T9`
warned a frame change would re-reference them; `200` §3 said a wrong ANGLE after
a correct MOTION would be those knobs and not the frame. **`diag(-1, 1, -1)`
mirrors X and Z and leaves Y alone — which inverts ROLL and YAW and spares PITCH,
exactly the two axes reported and exactly the one not.**

**RECORD THE NEW DEFAULTS: `-HandAxisX 1 -HandAxisZ 1`.** The `-1`s are `155`'s
measurement against a frame that no longer exists, and `169` U-xx style deletion
is not owed — but the standing command must stop carrying them.

---

## §2 — ►►►► THE YAW SURVIVES, AND IT IS A SECOND DRIVER, NOT THE SEAM ◄◄◄◄

> `[REPORTED]`: ***"when I turn my head left and right, it still changes the
> direction of the gun massively."***

**THE SEAM IS NOT DOING THIS. `[MEASURED]` `200` §1: `R = Rhand` drifts 0.14 deg
across 83 head-only transitions.** A matrix that provably does not move cannot be
what is moving the gun.

**`[READ]` THE GUN MODEL HAS TWO DRIVERS, AND `163` DOCUMENTED THE SECOND ONE
WHEN IT ADDED IT:**

```
gun_azimuth_angle/_turning  ->  field_FFC
                            ->  transformAndNormalizeByLength2Dto3D
                            ->  7F067AB4  ->  hands[].field_A38/A3C/A40
```

**AND THE TERM IT IS WRITTEN FROM IS HEAD-RELATIVE.** `g_geVrAimNx` comes from
`g_geVrAimFwdHead = Rhead^T * fwdWorld`, so **it changes when the head turns even
though the hand has not moved.**

> **THAT IS CORRECT FOR A CROSSHAIR AND WRONG FOR A GUN.** A gun held at a fixed
> world direction genuinely DOES appear at a different place in your view when
> you look away — so the screen-space crosshair must move. **The gun's own
> ORIENTATION must not.** One number was driving both.

**AND `163` WAS RIGHT WHEN IT WROTE IT.** At that time the seam was cosmetic and
wrong (`157` §6.1), so `field_FFC` was the ONLY route by which the model could
follow the hand at all. **`200` removed the reason. The write outlived it.**

---

## §3 — WHAT SHIPPED

**`geVrGunAzimuthActive()` gates the write. `GE_VR_GUN_AZIMUTH` DEFAULT 0.
`-GunAzimuth` restores `163`'s behaviour** for the legacy frames, which still
need it.

**NOTHING ELSE MOVES, AND BOTH HALVES OF THAT ARE `[READ]`:**
- **the CROSSHAIR is untouched** — built from `crosshair_x_pos`, the FIRST
  integrator, still written above;
- **the BULLET is untouched** — `164` takes the barrel ray directly and **has
  never read `field_FFC`.**

**ONE NEW `RECOMP_PATCH`-REACHABLE SYMBOL (`recomp_ge_vr_gun_azimuth`,
`0x8F000164`) SO BUILD TWICE (`136`).** No `115` header. `168` §5's grep: zero
game symbols.

### `G-201` — NO SHOOTING
**Hold the gun STILL and turn your head left and right. THE GUN MUST NOT
RE-AIM.** Then confirm the two that already passed have not regressed: **wrist
twist rolls the right way, walking stays stable.**

> **AND ONE THING TO WATCH THAT IS NOT A FAULT:** the CROSSHAIR will still move
> across the screen when you turn your head with the gun held still. **That is
> correct** (§2) and it is the first time it will be visibly true.

---

## §4 — THE STANDING COMMAND, UPDATED

```powershell
.\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
         -WorldUnitsPerMetre 100 -HandUnitsPerMetre 100 `
         -ViewmodelScale 0.5 -GunOffY 8 -GunOffZ -2 `
         -HandAxisX 1 -HandAxisZ 1 `
         -AimFromHand -MuzzleOrigin -NoCrouch -HudDepth 0.2
```

**`-HandAxisX 1 -HandAxisZ 1` IS THE CHANGE** (§1). **`-GunOffY 8 -GunOffZ -2`
are `154`'s PISTOL values and are still tuned against the old frame** — they are
a POSE offset, not a motion term, so they are judged after `G-201`, not during.

---

## §5 — WHAT IS OWED

1. **BUILD TWICE. `G-201`** (§3).
2. **THEN THE POSE PASS:** `-GunOffY` / `-GunOffZ` / `-ViewmodelScale` against the
   solved frame. **Knob-only, no build.**
3. **THEN `G-194`** (the mark test) and `B1`.
4. **THE FOV / SCALE READ** (`199` §4) — `fovy=106` against the headset's 88.
5. `U-18`, `noPose`, `U-21`, `U-22`.

**NOTHING STAGED. THE COMMIT IS THE OWNER'S**, both repos.
