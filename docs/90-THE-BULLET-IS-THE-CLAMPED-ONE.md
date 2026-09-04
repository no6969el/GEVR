# 90 — THE BULLET COMES FROM THE CLAMPED QUANTITY. `87` AND `86` BOTH HAD IT BACKWARDS.

**2026-08-23, found while costing the A1 routes for a build decision. One read,
no launches. It inverts the central mapping of `86` §3.8 and of `87` finding 1,
and it changes which slice is optional.**

> # ►► `crosshair_angle` IS THE BULLET. `field_FFC` IS THE GUN MODEL'S POINTING. ◄◄
>
> ```c
> /* gunfire.c:4846 — and the decomp's own comment names it */
> /* "This function computes the angle the player's bullets are fired at" */
> void bullet_path_from_screen_center(coord3d *arg0, coord3d *result, enum GUNHAND arg2)
> {
>     ...
>     crosspos.x = g_CurrentPlayer->crosshair_angle.f[0] + randfactor * scaledspread * ...;
>     crosspos.y = g_CurrentPlayer->crosshair_angle.f[1] + randfactor * scaledspread * ...;
>     transformAndNormalizeByLength2Dto3D(&crosspos, result, 1.0f);
> }
> ```
>
> **Eight call sites**, across every firing path: `chrprop.c:931`, `:1423`,
> `gun.c:1775`, `:1862`, `:1961`, `:2143`, `:2362`, `gunfire.c:230`.
>
> **And `field_A38/A3C/A40` — what `field_FFC` feeds through
> `sub_GAME_7F067AB4` — has exactly FIVE readers, and not one of them fires
> anything:** `gunfire.c:568` (the gun's align), `:782` and `:803` (the muzzle
> flash's orientation), `:3287` and `:3299` (a draw/animation term).

---

## WHAT WAS WRONG, AND WHERE

| Claim | Where | Now |
|---|---|---|
| *"`field_FFC` … **This is `crosspos2` / `bgunSetAimPos`, exactly**"* | **`86` §3.8** table | **FALSE.** `field_FFC` never reaches a bullet. It orients the **gun model** and the **muzzle flash** |
| *"`gun_azimuth_angle` drives the **BULLET**"* | **`87`** finding 1, and its §1 code block | **FALSE, and it was mine.** `gun_azimuth_angle` → `field_FFC` → the gun's **pointing**. **`crosshair_x_pos` → `crosshair_angle` → the bullet** |
| *"the aim position fed to `bgunSetAimPos` is **NOT clamped**"* mapped onto ours | `86` §3.8, from PD | **The mapping does not carry.** PD's unclamped `crosspos2` is their **shot**. **Our unclamped `field_FFC` is our gun's POINTING, and our shot is the CLAMPED `crosshair_angle`** |
| *"pre-load **both** integrators, each with its own damping constant"* | **`87`** §1 | **STILL CORRECT, and now for a better reason** — but the roles swap: `crosshair_x_pos` for the **bullet**, `gun_azimuth_angle` for where the **gun model points** |

**`87`'s two-integrator finding survives intact. Only the labels on the two
outputs were swapped, and swapping them changes what the clamp means.**

---

## WHY THIS MATTERS MORE THAN A LABEL SWAP

### 1. THE BULLET IS CLAMPED. THERE IS NO UNCLAMPED SHOT PATH.

`crosshair_angle` is clamped to `[3, W-4] x [3, H-4]` at `gunfire.c:4699-4715`,
**before** `bullet_path_from_screen_center` ever reads it.

> **So in GoldenEye you cannot shoot outside the screen. Not "the crosshair
> pins while the bullet keeps going" — the bullet pins too.**
>
> **`86` §3.8 predicted, as gate G-A1-3, that past the clamp *"the crosshair
> pins and the gun keeps tracking, so gun and bullet visibly disagree."*
> The prediction is right and the reason is now known**: the gun keeps tracking
> because `field_FFC` is unclamped, and the bullet stops because
> `crosshair_angle` is not. **G-A1-3 is confirmed from source before it is run.**

### 2. SLICE A2 IS NOT OPTIONAL. IT IS THE ONLY HONEST INDICATOR.

**`86` already said O64 *"is the mechanism, not decoration"*, from PD's
example. This is a second, independent, stronger reason:** with the shot hard-
clamped to the screen and the gun model free to point anywhere, **the gun
becomes an actively misleading indicator past the clamp** — it points where you
aimed while the bullet goes somewhere else. **A world-space dot on the fired ray
is the only thing that tells the truth.**

**And gate G-A2-2 gets sharper:** *"point past the clamp and the dot stops
moving with the hand"* — **the dot must pin with the BULLET, not with the gun.**

### 3. THE PRACTICAL AIM LIMIT IS THE SCREEN, NOT THE HEADSET

**Whatever the FOV, the shot cannot leave `crosshair_angle`'s clamped
rectangle**, and that rectangle is in the **106-degree culling frustum**
(`87` read 3). **So the aim envelope and the eye's visible field are two
different rectangles**, and how they relate has never been measured. **A read
is not enough for this one — it is an S0 line and then a wear test.**

---

## WHAT THIS DOES NOT CHANGE

- **`88` §5 stands.** `gunfire.c:568` still aims the gun model at
  `field_A38/A3C/A40`, and that is still the coupling that makes the gun follow
  a written aim. **It just means the gun model follows `field_FFC` while the
  bullet follows `crosshair_angle`, so A1 must write BOTH or they diverge on
  purpose.**
- **`88` §5.1's barrel-axis conclusion stands** — but see the caveat below.
- **`87` reads 3, 4, 5, 6 stand.** Untouched.
- **`86`'s choice of function stands.** `caclulate_gun_crosshair_position_rotation`
  owns both integrators, so it remains the right place to write both.

### ONE CAVEAT ON `88` §5.1, RECORDED RATHER THAN SMOOTHED OVER

`88` §5.1 argued the aim point sits at **z ≈ −1000**, from
`transformAndNormalizeByLength2Dto3D`'s `out->z = -1.0f * norm`. **But
`initBondDATA.c:114` and `unk_092E50.c:138` initialise `field_A40` to
`+1000.0f`** — the opposite sign.

**The runtime value overwrites the initialiser every frame, so the runtime sign
is the one that governs — but the two disagree and `88` did not know it.**
**`88` §5.1's conclusion is therefore CORROBORATED but not PROVEN**, and the
`MuzzleFlashExtension` falsifier it named is now doing real work rather than
being a formality. **Slice 0 prints both `MuzzleFlashExtension` and
`field_A40`.** Rule 3: do not promote an impression, including a tidy one.

---

## THE CORRECTED PICTURE, IN ONE TABLE

| Quantity | Integrator | Damping | Clamped? | Drives |
|---|---|---|---|---|
| `crosshair_x_pos` → `crosshair_angle` | `gunfire.c:4692` | `guncrossdamp` (`CrosshairSpeed`) | **YES**, `:4699-4715` | **THE BULLET** (`bullet_path_from_screen_center`, 8 sites) **and the HUD crosshair** (`gunDrawSight`, `:6214`) |
| `gun_azimuth_angle` → `field_FFC` → `field_A38/A3C/A40` | `gunfire.c:4722` | `gunaimdamp` (`AimLockSpeed`) | **NO** | **The gun model's pointing** (`:568`), **the muzzle flash** (`:782`, `:803`), **and the viewmodel's screen sway** (`:512-520`) |

**A1 writes both, or the gun and the shot disagree by construction.**

**Nothing is built. `48` rule 1.**
