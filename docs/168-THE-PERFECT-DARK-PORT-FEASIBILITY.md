# 168 — PORTING PERFECT DARK'S VR LAYER. WHAT TRANSFERS, WHAT DOES NOT, AND WHY.

**2026-08-25. Read at `local-only\prior-art\perfect_dark_VR` @ `67ea20c`, MIT.
ATTRIBUTION OWED in `PUBLISH-MANIFEST.md` and at every point of use.**

> ## THE RULE THIS PROJECT HAS NOW LEARNED THREE TIMES
>
> **THE CONSTANTS AND THE DESIGNS TRANSFER. THE SUBSYSTEMS DO NOT.**
>
> | what | outcome |
> |---|---|
> | `{w,-x,y,-z}` hand basis (`155`) | **TRANSFERRED — worked first launch** |
> | Both-integrator pre-load (`163` §5) | **TRANSFERRED — confirmed from their source** |
> | Clamp the drawn sight only (`166` §8.4) | **TRANSFERRED — GE already ships half** |
> | "Project a world point through the render's own matrix" (`167`) | **TRANSFERRED** |
> | 1.5708 rad X post-rotation (`155`) | **FAILED** |
> | `MODELPART_GUN_MUZZLEPOS` (`163` §7) | ~~FAILED~~ **TRANSFERS — `171` §3. `163` searched for PD's NAME, not the mechanism; GE's is `Switches[3]->Data`** |
> | `lasersightSetBeam/Dot` (`166` §8.5) | **FAILED — PD already HAD a laser sight** |
>
> **THE PATTERN IS NOT LUCK. PD'S VR LAYER IS THIN AND VERY PORTABLE; WHAT IT
> SITS ON IS A RICHER BASE GAME.** Every real failure was a call INTO a PD feature
> GoldenEye does not have. **So the question for any candidate is never "is the
> VR code portable" — it is "what does this VR code CALL INTO".**
>
> **AND THE SECOND HALF OF THE RULE, ADDED BY `171` §3 AFTER ONE FALSE NEGATIVE:
> SEARCH FOR THE MECHANISM, NEVER FOR PERFECT DARK'S IDENTIFIER.** `163` §7
> grepped `MODELPART`, found zero, and wrote off a feature GoldenEye has. **A
> name-based search can only ever prove PD's name is absent.**

---

# 1. THE SHAPE OF THEIR VR LAYER

`port/vr/`, **5,543 lines total**:

| file | lines | what |
|---|---|---|
| `vr_openxr.cpp` | 2586 | session, frustum, per-eye HUD, submit |
| `vr_input.cpp` | 1395 | bindings, recoil, reload pull, haptics |
| `vr_runtime_launcher.h` | 454 | runtime selection |
| `vr_hub.cpp` | 410 | the VR menu environment |
| `vr_settings.cpp/.h` | 170 | `pd-vr.ini` persistence, ~25 knobs |

**AND THE KNOBS ARE EXPOSED AS AN IN-GAME MENU** (`mainmenu.c`), not a config
file only. **That is our P2-5 (`6D-13`/C1) and it is worth copying as a
PATTERN** — every tuning task in `161` gets cheaper the moment tuning stops
costing a relaunch, and this project has spent dozens proving it.

---

# 2. TIER A — PORT THESE. LITTLE OR NOTHING BLOCKS THEM.

## 2.1 ►► THE PER-EYE HUD SHIFT. THE DOUBLED CROSSHAIR FIX. ◄◄

**THE SINGLE HIGHEST-VALUE ITEM ON THIS PAGE**, because `166` §1 proved a 2D
crosshair cannot work in stereo and this is how PD make it work anyway.

`vr_openxr.cpp:2386`:

```c
parallaxOffset = localEyeX * (VrStereoCrosshair * fovTan.tanHalfWidth);
cantingOffset  = vr_get_horizontal_fov_offset_ratio(eye);
*out_tx_HUD    = parallaxOffset + cantingOffset;
```

and `vr_openxr.cpp:1989`:

```c
return (tanRight + tanLeft) / (tanRight - tanLeft);   // optical centre offset, [-1,1]
```

**FOR OUR EYE 0 THAT EVALUATES TO -0.1867 — WHICH IS EXACTLY THE `m20=-0.18669`
ALREADY PRINTED IN OUR OWN PROJECTION LOG.** Our 3D scene is canted correctly;
**the HUD is not shifted at all.** That is the doubling, and the correction is
already computed in our own code for the other path.

**`VrStereoCrosshair` (default 0.70) is the HUD's stereo DEPTH**, exposed as a
menu slider. **It has no GoldenEye dependency whatsoever** — it is arithmetic on
tangents we already have.

**BLOCKERS: none identified.** Needs the RT64 HUD pass to accept a per-eye
horizontal offset. **VERDICT: DO THIS FIRST.**

## 2.2 ►► HOST-SIDE WEAPON RECOIL ◄◄

`vr_input.cpp:908-1170`. Their own comment: **"100% on OpenXR side, no engine
dependency."**

```c
struct WeaponRecoilProfile {
    float kickPitch, kickYaw, kickPush, springStiff, springDamp;
};
```

Five floats, a spring integrated at fixed `dt` (with their own TODO to use the
real delta), applied to the controller pose **before the game sees it**
(`RecoilApplyToControllerPose`). **Our host owns the same pose, so this is close
to drop-in.**

**THE ~60 PER-WEAPON PROFILES DO NOT TRANSFER — THE CLASSES DO.** Pistol, magnum,
SMG, LMG each have a recognisable shape. **`86` §7 still applies: no table until
two GoldenEye weapons are MEASURED to disagree.**

**BLOCKERS: none.** `vrRecoilNotifyShotFired(handnum)` needs one call site on our
fire path. **VERDICT: PORT, AS ITS OWN SLICE. This is `161` P3-1 and it is
cheaper than its position suggests.**

## 2.3 ►► SNAP TURN ◄◄

`bondwalk.c:105-113`. A boolean plus a branch on the turn stick. **Pure comfort
feature, no PD dependency.** Ours would sit wherever `-ViRate`-era turning lives.
**VERDICT: PORT. Cheap, and it is the single most requested VR comfort option in
any shooter.**

## 2.4 ►► THE SETTINGS FILE AND MENU PATTERN ◄◄

`vr_settings.cpp` writes `pd-vr.ini` as plain `Key=%.4f` lines; `mainmenu.c`
exposes each as a checkbox or a stepped slider with min/step constants.
**This IS `161` P2-5 / `6D-13` / C1, and PD prove the shape.**
**VERDICT: PORT THE PATTERN, not the file.** Deliberately below P1-2 in `161`
only because P1-2 deletes most of the knobs it would expose.

---

# 3. TIER B — PORT THE DESIGN, WRITE OUR OWN CODE.

## 3.1 THE SMOOTHED BODY YAW — AND IT IS ALREADY OUR `6D-04`

`bondgun.c:11003`: **`VrBodyYaw += d * VrArmBodyFollow;`** with
`VrArmBodyFollow = 0.02f`. **A follower, not the head yaw** — which is exactly
`102` §4's recorded trap (*"a 360 spin unwound the elbows"*) and exactly what
`161` P2-6 already specifies. **The constant 0.02 is a real number to start from.**

## 3.2 ELBOW TUCK / ARM POSING

`bondgun.c:183`, `VrArmElbowTuck = 0.80f`. **NOTE: `86` §7 says DELIBERATELY NOT
DOING an IK arm** — *"a wrong arm is more distracting than none."* PD's tuck is a
much weaker thing than full IK and may be worth revisiting, **but that is a
decision to re-open explicitly, not to drift into.**

## 3.3 TWO-HANDED AIM

`bondgun.c:1057`, `VrTwoHandAim = true` by default in PD — aim along the line
between both controllers for two-handed weapons. **`86` §7 lists two-handed aim as
DELIBERATELY NOT DOING.** **Recorded, not recommended.** Re-open only after the
one-handed aim chain is closed.

## 3.4 MANUAL RELOADING BY GESTURE

`vr_input.cpp:832`, `vrUpdateReloadPull`. Relative motion of the two controllers,
rotated into the RIGHT hand's local frame by the conjugate quaternion, accumulated
on three local axes. **Host-side and elegant.** **BLOCKER: needs a GoldenEye
reload entry point to drive**, which is a read we have not done.

## 3.5 CROSSHAIR PARALLAX BY TARGET DISTANCE

`vr_openxr.cpp:2396`, `vrComputeCrosshairParallax(distanceGameUnits)`. Corrects
the crosshair for how far the target is, clamped to `+-0.02`, with a 1.75 m
nominal. **This is the principled version of the muzzle-parallax problem `163` §8
warned would appear at close range.** **BLOCKER: needs a distance, which means
the raycast hit — see §4.1.**

---

# 4. TIER C — BLOCKED, WITH THE BLOCKER NAMED.

## 4.1 THE LASER SIGHT / DOT AIMING (`161` P1-6)

**PD DID NOT BUILD A LASER. THEY ALREADY HAD ONE** — the Falcon 2's laser sight
is stock Perfect Dark. Their VR work only re-pointed it
(`lasersightSetBeam`/`lasersightSetDot`, `bondgun.c:10251`).

**GOLDENEYE HAS NO SUCH SUBSYSTEM.** Nearest is `BeamRecord`, a bullet TRACER,
and `166` §5.2 lists the blocker precisely: **five symbols and a struct that do
not cross the patch boundary**, plus four `unk` fields one of which silently
means "do not render".

**WORTH RECORDING: PD ADDED `VrlaserDotForALL` THEMSELVES** — a flag giving the
dot to weapons with no laser sight, **because it is that much better as an aiming
reference.** The owner asking for *"a laser for testing (or an option)"* is asking
for the flag PD found they needed.

**AND THEIR STALENESS TEST IS THE HALF WE HAVE NO EQUIVALENT FOR:** `dotpos`
unchanged since last frame means the raycast never wrote, so they fall back to
`muzzlepos + vrdir*100000` rather than draw a lie (`bondgun.c:8367`). **That is
`48`'s "an instrument must be able to say I CANNOT ANSWER THIS", in shipped prior
art.**

## 4.2 THE VR HUB / MENU ENVIRONMENT

`vr_hub.cpp`, 410 lines. **`161` P3-3 already says "Not now."** Unchanged.

## 4.3 PHYSICAL HEIGHT MATCHING

`bondwalk.c:1824`, `VrMatchCharacterHeight` switches `unitsPerCm` between the
player's real height and the character's. **This is `161` P2-3 / `6D-10` H2 and it
is explicitly marked DISCUSS BEFORE BUILDING.** PD's measured numbers are already
in `102`: 160 cm nominal, 130-200 slider, a **90-sample MEDIAN** calibration,
`VR_MAX_HEAD_CM 250` glitch swallow, and **crouch thresholds as FRACTIONS of the
configured standing height** (`/1.6` squat, `/1.3` duck) because a running max
left you spuriously ducking after a jump.

---

# 5. THE HONEST ANSWER TO "CAN WE PORT THE WHOLE THING"

**Not as a lift-and-shift, and the reason is structural rather than legal.** The
MIT licence permits it; the base game does not match. **But the enumeration above
is the whole of it** — there is no hidden fourth tier, and Tier A alone is four
features with no identified blockers, one of which (§2.1) fixes a defect the
wearer has already reported.

**THE ORDER THIS IMPLIES:**

1. **§2.1 per-eye HUD shift** — fixes the doubled crosshair. Nothing blocks it.
2. **Finish `161`'s aim chain** — `167` is built and unworn; `166` §4's 17 degrees
   is still open and is not a PD problem.
3. **§2.2 recoil, §2.3 snap turn** — independent, cheap, high felt value.
4. **§2.4 the settings menu** — after P1-2 deletes the knobs it would expose.
5. **§4.1 the laser** — its own slice, honestly sized, and it unlocks §3.5.

**AND ONE RULE FOR EVERY ITEM ABOVE, FROM THREE FAILURES:** before costing a PD
feature, **grep our `patches/externs.h` and `patches/structs.h` for every symbol
it touches.** `157` withdrew a slice for want of eight; `166` §5.2 stopped one
before it was written for want of five. **That grep is the cheapest step in this
document.**
