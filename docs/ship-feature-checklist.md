# Ship feature checklist (public Beta boot)

Source of truth for the live KEEP + PLAY0 allowlist is `$requiredBootKnobs` in
[`packaging/_smoke-ship-zip.ps1`](../packaging/_smoke-ship-zip.ps1). Pack smoke fails if
`gevr-*-boot.cmd` in the zip does not assign every knob below to the exact value shown.

**vr441** ships the full allowlist in `gevr-vr441-boot.cmd`. **vr440** used the same
`goldeneye.exe` but a picture-only boot and failed this gate (23+ knobs missing).

Censuses stay **off** in public boots (`GETV_VR_WALLCENSUS=0`, `GETV_VR_ROOMLOADWHY=0`).
Pause / N64 A confirm is **not** claimed fixed; vr441 keeps the same `GETV_XR_BTN_A` /
`GETV_XR_BTN_B` map vr440 shipped.

## Sit gates (knobs assigned is not enough)

Pack smoke only proves the boot *writes* the env. A zip is not Latest until both
bats are *played* and the features fire. Headset KEEP passing does not clear the
monitor path. vr440 already taught that lesson.

Do this on the staged zip, not a chair launcher.

### `Start-GEVR.bat` (headset)

- Banner / boot cmd is the ship tag (`gevr-vr441-boot.cmd` or the current cut).
- Recenter: both sticks (or Home) resets the playspace.
- Trigger fires. Left stick walks. Right stick turns.
- Squeeze ADS mark sits on the gun ray.
- Touch-use: poke a door / console with either hand.
- Casings leave the gun. A kill stays on the floor (up to 48).
- Audio: first gunshot is on time and stays on time after a hitch.

### `Play-on-monitor.bat` (flat)

- Boots with no HMD session. No one-eye / OpenXR requirement.
- Audio is in sync from the first shot. [#48](https://github.com/no6969el/GEVR/issues/48)
- Keyboard / pad still work. Local split-screen still starts.

A FAIL on the monitor bat blocks Latest even if the headset sit was clean.

## Chair features vr440 never turned on

| Knob | Ship value | Notes |
|------|------------|--------|
| `GETV_VR_CORPSEKEEP` | `1` | Public boot required (off without boot) |
| `GETV_VR_CORPSEKEEP_MAX` | `48` | Public boot required |
| `GETV_VR_CORPSEKEEP_CEIL` | `440` | Public boot required |
| `GETV_VR_TEXINVAL` | `1` | Public boot required |
| `GETV_VR_TEXDLRETAG` | `1` | Public boot required |
| `GETV_VR_VFXTMEM` | `1` | Public boot required |
| `GETV_VR_VFXSHIFT` | `1` | Public boot required |
| `GETV_TEX16BE` | `1` | Public boot required (DECODE path; do not set `GETV_RGBA16BE=1`) |
| `GETV_RGBA16BE` | `0` | Public boot required (pinned off) |
| `GETV_TEX32BE` | `1` | Public boot required |

## PLAY0 arm

| Knob | Ship value | Notes |
|------|------------|--------|
| `GETV_VR_VTXGUARD` | `64` | Public boot required |
| `GETV_VR_ADSSIGHT` | `1` | Public boot required |
| `GETV_VR_HITSNAP` | `2` | Public boot required |
| `GETV_VR_SIGHTPX` | `6` | Public boot required |
| `GETV_VR_ADSCULL` | `1` | Public boot required |

## Aim / hands / gun / playspace

| Knob | Ship value | Notes |
|------|------------|--------|
| `GETV_VR_HEADYAW` | `1` | Public boot required |
| `GETV_VR_HEADFRAME` | `2` | Public boot required |
| `GETV_VR_HANDYAW` | `2` | Public boot required |
| `GETV_VR_LEVELYAW` | `1` | Public boot required |
| `GETV_VR_GUNAIM` | `1` | Public boot required |
| `GETV_VR_GUNMOUNT` | `1` | Public boot required |
| `GETV_VR_GUNARM` | `1` | Public boot required |
| `GETV_VR_PLAYSPACE` | `1` | Public boot required |
| `GETV_VR_BODY_NOARMS` | `1` | Public boot required |
| `GETV_XR_FLOOR_M` | `-0.200` | Public boot required |
| `GETV_VR_HANDCUBES` | `1` | Public boot required |
| `GETV_VR_RETICLE` | `1` | Public boot required |
| `GETV_VR_TOUCHUSE` | `1` | Public boot required |
| `GETV_VR_HANDMELEE` | `1` | Public boot required |
| `GETV_VR_CASINGS` | `1` | Public boot required |

## Picture KEEP

| Knob | Ship value | Notes |
|------|------------|--------|
| `GETV_SUPERSAMPLE` | `3` | Public boot required |
| `GETV_XR_PLAY_SRCFBO` | `1` | Public boot required (not the dead name `GETV_SRCFBO`) |
| `GETV_XR_PLAY_EYERECT` | `1` | Public boot required |
| `GETV_VR_SKYMESH` | `1` | Public boot required |
| `GETV_VR_SKYSCISSOR` | `1` | Public boot required |

## Core VR

| Knob | Ship value | Notes |
|------|------------|--------|
| `GETV_VR` | `1` | Public boot required (`geVrXrEnabled`; unset means off) |
| `GETV_FPS` | *(unset)* | Must stay unset in ship boot so pacing follows the HMD (#49). Do not pin `90` in public boots. |
| `GETV_STEREO_SRC` | `xr` | Public boot required |
| `GE_VR_XR` | `1` | Set in boot; **known no-op** in this binary (VR arm is `GETV_VR`). Kept for `Play-on-monitor.bat` gate compatibility. |

Also required in boot (not in the 39-knob table): `GEVR_SHIP_TAG=vr441` for the current cut.

## Forbidden in a public boot

These must not be assigned a non-empty, non-`0` value in `gevr-*-boot.cmd` (clears and `=0` are fine):

- `GETV_XR_FOVMATCH`
- `GETV_VR_WALLCENSUS`
- `GETV_VR_ROOMLOADWHY`
- `GETV_FIREDUMP`
- `GETV_STAGE`
- `GETV_CHR_DEBUG`
- `GETV_INPUT_DEBUG`
- `GETV_FRONTTRACE`
- `GETV_CINETRACE`
- `GETV_LOGFLUSH`
- `GETV_SKYTRACE`
- `GETV_ROOMTRACE`
- `GETV_CULLWHY`
- `GETV_XR_SHARPLOG`

## Dead knob names (fail smoke if present in boot)

Silent no-ops in `goldeneye.exe` - do not use in ship boots:

- `GETV_SRCFBO` (use `GETV_XR_PLAY_SRCFBO`)
- `GETV_MSGSCALE` (dead name; the live knob is `GETV_VR_MSGSCALE`, default 50)

## Pack smoke (owner)

Run [`packaging/_pack-vr441.ps1`](../packaging/_pack-vr441.ps1) without `-SkipSmoke`. Expect
`[smoke] PASS all gates` on staging and on the zip. See [`packaging/README.md`](../packaging/README.md).

Smoke PASS is necessary. Sit gates above are also necessary. Do not publish Latest on smoke alone.
