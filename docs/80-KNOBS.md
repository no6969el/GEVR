# 80 — EVERY KNOB. The complete reference.

> ## **REBUILT 2026-08-25. IT HAD GONE 38 KNOBS STALE OUT OF 70 — MORE THAN HALF — WHILE STILL CALLING ITSELF COMPLETE.**
>
> **`48`: "a document's authority outlives its accuracy."** Everything below the
> `ROUTE B` heading was added on 2026-08-25 and covers the whole judder line and
> the whole 6DoF line. **The older sections are unaudited except where marked.**
>
> **THE CHECK IS TEN SECONDS AND IT SHOULD BE RUN EVERY TIME THIS FILE IS
> DOUBTED:**
> ```powershell
> Select-String -Path .\vr.ps1 -Pattern '^\s*\[(switch|double|int|string)\]\s*\$'
> ```

**2026-08-23. Generated from the source, not from memory** — the environment
variables actually read by `src/main`, `src/game` and `patches`, and every
`vr.ps1` parameter that sets them.

**Why this document exists:** this project has twice found a knob whose consumer
had been deleted (`32`'s `-Sign`, `24`'s `-ForceEye`), each returning a confident
false negative for a whole session. **A knob that is announced but not connected
is worse than no knob at all.** Anything listed here as CONNECTED was traced to a
reader in the source on this date.

**Run everything through `vr.ps1`.** It clears every `GE_VR_*` variable first,
which matters: environment variables persist for the life of a shell, and a
build silently inheriting a setting from three sessions ago has already cost one
wrong diagnosis.

---

## THE ONES YOU ACTUALLY NEED

```powershell
.\vr.ps1                                   # worn. SBS is the default (docs\65)
.\vr.ps1 -UnitsPerMetre 50                 # THE MEASURED WORLD SCALE (docs\77)
.\vr.ps1 -Flat                             # no headset. Both eyes in the window
.\vr.ps1 -NoXr                             # no VR at all. The path that must never break
.\build.ps1                                # build. Use this, not the raw cmake line
```

**Two things that are not knobs and will waste your session if you skip them:**

| | |
|---|---|
| **Press `F9` after putting the headset on** | Recentring fires at process start, when the headset is still on the desk. Everything about height and scale is wrong until you press it. O60 |
| **NEVER close a VR session with the X** | `taskkill /F /IM GoldenRecomp.exe`. The X bugchecks the machine — `75`, B3/B4 |

---

## WORLD AND SCALE

| `vr.ps1` | Env | Default | State | What it does |
|---|---|---|---|---|
| `-UnitsPerMetre <n>` | `GE_VR_UNITS_PER_METRE` | 100 | CONNECTED, **NOW A FALLBACK** | The master. **SUPERSEDED 2026-08-25 by the S1 split (`156`, `159`)** - it now only supplies the default for the two below. **Its old note ("measured worn at ~50") is VOID: 50 and 100 were answering different questions.** |
| `-Offset <n>` | `GE_VR_TEST_OFFSET` | 3.175 | CONNECTED | Per-eye lateral offset in units, **half** the eye separation. Superseded worn by the live headset IPD; still the lever under `-Flat` |
| `-ResScale <n>` | `GE_VR_RES_SCALE` | 1.0 | CONNECTED | Linear scale on the runtime's recommended eye size. **O22: smaller made it SLOWER, unexplained** |

## THE VIEWMODEL — the gun and the hand

| `vr.ps1` | Env | Default | State | What it does |
|---|---|---|---|---|
| `-ViewmodelScale <n>` | `GE_VR_VIEWMODEL_SCALE` | 1.0 | **CONNECTED, gates passed** | Resizes the gun **about its own root**. `78` |
| `-ViewmodelPush <n>` | `GE_VR_VIEWMODEL_PUSH` | 0.0 | **CONNECTED, gates passed** | Moves it away from the eye, in game units. −Z is away |
| `-HandAim` | `GE_VR_HAND_AIM` | off | **CONNECTED, NOT VALIDATED** | The gun follows the right controller. **Visual only** — the bullet still comes from the crosshair. `79` |
| `-HandRotOnly` | `GE_VR_HAND_POS=0` | pos on | CONNECTED | Rotation without position. Worn verdict: *"not a good way to play"* |
| `-HandAbsolute` | `GE_VR_HAND_ABSOLUTE` | **off** | **CONNECTED, NOT VALIDATED** | Absolute rotation against a neutral reference, so the game's turn-sway cannot reach the gun. **Right in principle; worn once it read "really far away"** |
| `-HandRotNoInvert` | `GE_VR_HAND_ROT_INVERT=0` | invert on | CONNECTED | Back to the first composition, which read inverted on every axis |
| `-HandAxisX/Y/Z <±1>` | `GE_VR_HAND_AXIS_*` | 1 | CONNECTED | Axis convention, applied by **conjugation** so it can only rotate, never mirror |

## HEAD TRACKING

| `vr.ps1` | Env | Default | State | What it does |
|---|---|---|---|---|
| `-NoHead` | `GE_VR_HEAD=0` | on | CONNECTED | Gamepad only, world head-locked |
| `-NoHeadTranslate` | `GE_VR_HEAD_TRANSLATE=0` | on | CONNECTED | Rotation only. **O2's gate 6 is still unjudged** |
| `-NoLiveFov` | `GE_VR_LIVE_FOV=0` | on | CONNECTED | The hardcoded Pimax tangent table instead of the runtime's |
| `-YawSign` `-PitchSign` `-RollSign` | `GE_VR_HEAD_*_SIGN` | 1 | CONNECTED | Rotation sense per axis. **Not used by the hand** — `79` correction 2 explains why they must not be |
| `-PosXSign` `-PosYSign` `-PosZSign` | `GE_VR_POS_*_SIGN` | 1 | CONNECTED | Position sense per axis. Used by the head **and** the hand's position |
| `-NoRecentre` | `GE_VR_RECENTRE=0` | on | CONNECTED | Keep 3f-4's raw local origin. A/B only |
| `-NoRecentreYaw` | `GE_VR_RECENTRE_YAW=0` | on | CONNECTED | Recentre position but not heading. **O20: re-run is blocked** |
| `-RecentreKey <n>` | `GE_VR_RECENTRE_KEY` | F9 | CONNECTED | SDL scancode for the recentre key |

## EYES, FRUSTUM AND PRESENT

| `vr.ps1` | Env | Default | State | What it does |
|---|---|---|---|---|
| — | `GE_VR_XR` | off | CONNECTED | OpenXR itself. `vr.ps1` sets it unless `-NoXr`/`-Flat` |
| `-Flat` | (frustum without XR) | off | CONNECTED | VR geometry, side by side, no headset. **Structurally blind to the eye present stage** — `64` |
| `-Sbs` / `-NoSbs` | `GE_VR_SBS` | **on** | CONNECTED | Side-by-side. **`-NoSbs` reproduces the B2 freeze on purpose** — `65` |
| `-SwapEyes` | `GE_VR_EYE` | 0 | CONNECTED | Which eye this build renders. The only live eye swap once head tracking is on |
| `-Sign <±1>` | `GE_VR_EYE_SIGN` | 1 | **CONSUMER DELETED** | `32`, `36`: the reader was removed by `30`. Kept as the record |
| `-ForceEye <n>` | `GE_VR_XR_FORCE_EYE` | −1 | **XR ONLY** | O24: `g_forceEye` lives only in `ge_vr_xr.cpp`, so it does nothing under `-Flat` |
| `-PresentEye <n>` | `GE_VR_PRESENT_EYE` | −1 | CONNECTED | Force both halves to one eye's target. `54` |
| `-SkipEye <n>` | `GE_VR_SKIP_EYE` | −1 | **`-Flat` ONLY** | **Returns a FALSE ANSWER under XR** (`64`) — it disables only the present-side eye render |
| — | `GE_VR_FIT_ASPECT` | 1 | CONNECTED | Monitor-preview aspect fit. Correctly off under XR |

## PATCH-SIDE, COMPILE TIME (`patches/ge_vr_bindtest.c`)

**These are `#define`s, not environment variables — changing one needs a rebuild.**

| | Default | What it does |
|---|---|---|
| `GE_VR_MODE` | `HOSTEYE` | Which half of the eye split the patch performs |
| `GE_VR_CULL_FOVY_DEG` / `_SCALE` | — | The culling frustum's widening. `26` |
| `GE_VR_MIN_ZNEAR_UNITS` / `MAX` | — | Near plane clamp. `14`, and `16` sharpened the reasoning |
| `GE_VR_TRACE_FOV` | 0 | FOV trace logging |
| `GE_VR_PREVIEW_FIT_ASPECT` | — | The preview fit, patch side |

## DIAGNOSTIC

| Env | Default | What it does |
|---|---|---|
| `GE_VR_LOG_VIEW` | off | `view FINAL` per frame. **O51: at 90 Hz this is 20k lines in two minutes of synchronous I/O on the present thread — an instrument that changes what it measures** |
| `GE_VR_XR_LEVEL` | 2 | 0 session only, 1 frame loop no layer, 2 full |
| `GE_VR_DRAIN_TIMEOUT_MS` | — | Present-thread drain timeout at shutdown. Related to O21 / B3 |

---

## THE RULE THIS DOCUMENT IS FOR

**Before trusting a knob, check it has a reader.** Twice now a knob has been
announced in the launcher, printed in the log, and read by nothing — and both
times it returned a confident negative result that sent a session down the wrong
path. `vr.ps1` printing a value is not evidence that anything consumes it.

**And before trusting a measurement, check the knob moved the number.** `77` is
here because a 2x change in eye separation was reported as "it looks the same"
by a human, while the log showed `eyeDelta` genuinely halving. **The knob worked
and the instrument was the person.**


---

# ►►►► ADDED 2026-08-25. EVERYTHING BELOW WAS MISSING. ◄◄◄◄

## ROUTE B — the 90 Hz sim. `129`, `131`, `132`, `147`

| Flag | Env | Default | State | What |
|---|---|---|---|---|
| `-ViRate <n>` | `GE_VR_VI_RATE` | **60** | **CONNECTED, WORN, THE JUDDER FIX** | The rate the runtime's VI thread ticks at. **90 is the build the owner called *"SO MUCH better, totally playable"*** (`147`). **NOT the default** - H-9, an open decision (`151`). Range 30-240 or it is ignored |
| `-FloatDelta` | `GE_VR_FLOAT_DELTA` | off | **CONNECTED, PARKED** | RB-03. `g_GlobalTimerDelta` carries the fractional frame length. **Makes Bond 1.5x too fast** - `145`: his walk is a per-FRAME convergence with no timestep. Deliberately a SECOND knob so RB-02 and RB-03 can be judged apart (`132` §1) |

## SCALE — split 2026-08-25. `156`, `159`

| Flag | Env | Default | State | What |
|---|---|---|---|---|
| `-WorldUnitsPerMetre <n>` | `GE_VR_WORLD_UNITS_PER_METRE` | follows `-UnitsPerMetre` | **CONNECTED, TUNING** | **THE EYES.** Stereo separation, therefore apparent size. **A PERCEPTION, not a measurement.** Wearer's answer is **~12-25 and still coming down** - `159`. **Halve, never nudge** |
| `-HandUnitsPerMetre <n>` | `GE_VR_HAND_UNITS_PER_METRE` | follows `-UnitsPerMetre` | **CONNECTED, PINNED AT 100** | **THE HAND.** **A MEASUREMENT: one game unit is one centimetre** (`16`, from Bond's 175-unit eye height). At 100 the hand travels 1:1 |

## THE SEAM — the gun follows the hand. `83`-`85`, `154`

| Flag | Env | Default | State | What |
|---|---|---|---|---|
| `-HandSeam` | `GE_VR_HAND_SEAM` | off | **CONNECTED, WORN** | The gun follows the hand, **rotation included**. **THE ONE TO USE** |
| `-SeamNoRot` | `GE_VR_SEAM_ROT=0` | rot on | **CONNECTED — AND IT DELETES THE ROTATION** | Writes IDENTITY over the whole rotation matrix (`:1109`). **It was in EVERY command in this project until 2026-08-25** (`154` §1). Position-only A/B; **not for normal play** |
| `-SeamTest` | `GE_VR_SEAM_TEST` | off | CONNECTED | `84`'s fixed-offset probe |
| `-HandPosX/Y/Z <±1>` | `GE_VR_HAND_POS_*` | 1 | CONNECTED | Hand position axis signs. **`-HandPosZ 1` is in the standing command** |
| `-GunOffX/Y/Z <n>` | `GE_VR_GUN_OFF_*` | **0** | **CONNECTED, WORN** | **THE GRIP OFFSET, and it had NEVER been switched on** - the gun pivoted about the model's own origin, which is the *"anchor on the front of the gun"* (`154` §2). PD's pistol default `(0,16,-4)` in cm. **Halve them whenever `-ViewmodelScale` halves** |
| `-GunOffFwd` | `GE_VR_GUN_OFF_FWD` | off | **CONNECTED, UNTESTED** | Applies the offset with PD's FORWARD rotation instead of today's transpose. **A knob because the convention could not be settled by reading** (`154` §3) |
| `-HandRotXDeg <n>` | `GE_VR_HAND_ROT_X_DEG` | 0 | **CONNECTED — FALSIFIED** | PD's post-rotation. **`90` did not work, `-90` was WORSE, 0 beat both** (`155` §2). Probably because our `R` is already head-relative. **Leave off** |
| `-HandAxisX/Y/Z <±1>` | `GE_VR_HAND_AXIS_*` | 1 | **CONNECTED, WORN, PROVEN** | **`-HandAxisX -1 -HandAxisZ -1` IS PD's `{w,-x,y,-z}` basis** (conjugation by `diag(sgn)`) **and it fixed the up/down inversion on the first launch** (`155` §1) |

## AIMING — `153`, `157`, `158`

| Flag | Env | Default | State | What |
|---|---|---|---|---|
| `-MuzzleOrigin` | `GE_VR_MUZZLE_ORIGIN` | off | **CONNECTED, WORN, WORKS** | **The bullet leaves the GUN, not the camera.** `gunfire.c:4871-4873` zeroed the origin - invisible and correct on a flat screen (`157`) |
| `-MuzzleExt <n>` | `GE_VR_MUZZLE_EXT` | 0 | CONNECTED | Slides that origin along the barrel, game units |
| `-MuzzleSignX/Y/Z <±1>` | `GE_VR_MUZZLE_SIGN_*` | 1 | CONNECTED | **View-space handedness is UNPROVEN. A wrong Z puts the muzzle BEHIND you** |
| `-AimFromHand` | `GE_VR_AIM_FROM_HAND` | off | **CONNECTED, UNTUNED** | **The hand drives the AIM** - writes `crosshair_x_pos` from the gun's pointing (`158`). **Before this, the seam was COSMETIC** (`157` §6.1) |
| `-AimGain <n>` | `GE_VR_AIM_GAIN` | 1.0 | CONNECTED | Ray slope to screen offset. **The main tuning knob** |
| `-AimSignX/Y <±1>` | `GE_VR_AIM_SIGN_*` | 1 | CONNECTED | If the aim goes the wrong way |
| `-AimFwdNeg <0/1>` | `GE_VR_AIM_FWD_NEG` | **1 — AND THAT IS A TRAP** | CONNECTED | **`0` IS THE WORKING VALUE.** At the default the forward component is negative, `state=REFUSED` fires every frame and the aim never runs. **Making 0 the default is OWED** |
| `-AimFwdAxis <0/1/2>` | `GE_VR_AIM_FWD_AXIS` | 2 | CONNECTED | Which axis is "into the screen". **The lateral-pair bug that made this knob useless was fixed in `158` §4** |
| `-AimBasis <0/1/2>` | `GE_VR_AIM_BASIS` | **2** | CONNECTED | 0/1 are the two guessed axes inside `R` - **both wrong** - kept for comparison. **2 is the ray derived from the raw poses** (`158` §5) |
| `-FreeAim` | `GE_VR_FREE_AIM` | off | **CONNECTED, INERT UNTIL A1c IS RIGHT** | Unclamps `crosshair_angle` (`gunfire.c:4699-4715`). **Its eight readers sort ONE-to-seven: only `gunDrawSight` wants the clamp** (`153` §8) |

## OBSOLETE — the interpolation era. `150` H-11

> **THESE PRE-DATE ROUTE B AND WOULD RE-ENABLE THE INTERPOLATION PATH IF
> COMBINED WITH `-ViRate`. DO NOT USE THEM.** `147`: `interpUsed=0` and nothing
> is manufactured any more.

| Flag | Env | Note |
|---|---|---|
| `-EyeInterp` | `GE_VR_EYE_INTERP` | Publishes interpolated eye passes. **Superseded by Route B** |
| `-EyeSetPhase` | `GE_VR_EYE_SETPHASE` | `116`'s phase fix. Implies `-EyeInterp` |
| `-EyeSampleTest` | `GE_VR_EYE_SAMPLE_TEST` | `110`'s O85 probe |
| `-EyePickLog` | `GE_VR_EYE_PICKLOG` | `113`'s `(set,pass)` trace |
| `-PosePerPass` | `GE_VR_POSE_PER_PASS` | `121`-`125`'s per-pass head pose |
| `-PoseLag <n>` | `GE_VR_POSE_LAG` | `94` T4. Submits a pose N ticks old |
| `-Timewarp` `-TimewarpYaw` `-TimewarpInvert` | `GE_VR_TIMEWARP*` | `97`/`98`. **The warp went the wrong way** |
