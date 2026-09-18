# GEVR KEEP defaults inventory (vr441 ship-default-ON plan)

Source boot: `packaging/templates/gevr-vr441-boot.cmd` (headset path via
`Start-GEVR.bat`). Flat path: `packaging/templates/Play-on-monitor.bat`.

The public repo has **no `getv` source**. Every **C_DEFAULT** row below is the
code default at exe startup when the boot does not assign the knob; that default
is **UNKNOWN** here (classify from boot and comments only).

Pack smoke allowlist (39 knobs): `packaging/_smoke-ship-zip.ps1` (`$requiredBootKnobs`).
Human sit gates: `docs/ship-feature-checklist.md`.

Blank `set FOO=` wipe lines in section 0 are **not** listed in the KEEP arms
tables (dig clears only). They are summarized under **DIG_OFF (wipe)**.

---

## Classification key

| Class | Meaning |
|-------|---------|
| **KEEP_SHIP** | Non-empty boot assignment that arms a shipped VR / PLAY0 / picture KEEP path (incl. legacy `GE_VR_XR=1`). |
| **PLAYER_PREF** | Boot seeds PLAY0 tuning (input, buttons, distances, audio queue). Ship-default-ON may leave these env-only. |
| **DIG_OFF** | Explicit `=0` (or forbidden falsifier pin) so dig / chair instruments stay off. |
| **FLAT_FORCE** | Set only in `Play-on-monitor.bat` to disable headset KEEP. |
| **C_DEFAULT** | Wiped in section 0 and not reassigned; exe default **UNKNOWN**. |

---

## FLAT_FORCE (`Play-on-monitor.bat`)

| Knob | Value | Notes |
|------|-------|-------|
| `GEVR_SHIP_TAG` | `vr441` | Same cache stamp as headset zip. |
| `GE_VR_XR` | `0` | Smoke gate: flat path must clear legacy XR name. |
| `GETV_STEREO` | `0` | No stereo eyes on monitor. |
| `GETV_STEREO_MODE` | `0` | Flat stereo mode off. |
| `GETV_FPS` | `60` | Monitor cadence (headset boot uses `90`). |
| `GETV_AUDIO_CLOCK` | `device` | Same as headset boot; fixes flat audio desync ([#48](https://github.com/no6969el/GEVR/issues/48)). |
| `GETV_AUDIO_QUEUE_MS` | `33` | Same as headset boot ([#48](https://github.com/no6969el/GEVR/issues/48)). |

Headset KEEP knobs below are **not** run on the monitor bat unless the player
exports them in the shell.

---

## KEEP_SHIP and PLAYER_PREF (non-empty boot assigns)

### Stamp

| Knob | Value | Class |
|------|-------|-------|
| `GEVR_SHIP_TAG` | `vr441` | KEEP_SHIP |

### 2. Core VR + pacing

| Knob | Value | Class |
|------|-------|-------|
| `GETV_VR` | `1` | KEEP_SHIP |
| `GETV_FPS` | `90` | PLAYER_PREF |
| `GETV_SIMDIV` | `1` | KEEP_SHIP |
| `GETV_SIMHZ` | `query` | PLAYER_PREF |
| `GETV_BUDGET` | `120` | PLAYER_PREF |
| `GETV_XR_PLAY` | `1` | KEEP_SHIP |
| `GETV_XR_PLAY_AT` | `300` | PLAYER_PREF |
| `GETV_XR_PLAY_STEREO` | `1` | KEEP_SHIP |
| `GETV_XR_PLAY_SCREEN` | `2` | KEEP_SHIP |
| `GETV_STEREO` | `1` | KEEP_SHIP |
| `GETV_STEREO_SRC` | `xr` | KEEP_SHIP |
| `GETV_STEREO_REBUILD` | `1` | KEEP_SHIP |
| `GETV_STEREO_VIEWRESTORE` | `1` | KEEP_SHIP |
| `GETV_STEREO_HUDGATE` | `1` | KEEP_SHIP |
| `GETV_STEREO_AIMRECT` | `1` | KEEP_SHIP |
| `GETV_STEREO_GUNOFS` | `1` | KEEP_SHIP |
| `GETV_XR_UNITS_PER_M` | `100` | KEEP_SHIP |
| `GETV_XR_FOVSYM` | `1` | KEEP_SHIP |
| `GETV_XR_HEAD_TRANSLATE` | `1` | KEEP_SHIP |
| `GETV_XR_PLAY_AUTORECENTER` | `1` | KEEP_SHIP |
| `GETV_XR_PLAY_AUTOSCREEN` | `1` | KEEP_SHIP |
| `GETV_XR_PLAY_FOVSCALE_CINEMA` | `85` | PLAYER_PREF |
| `GETV_XR_PLAY_SRCRECT` | `full` | KEEP_SHIP |
| `GETV_XR_PLAY_EYERECT` | `1` | KEEP_SHIP |

### 3. Sharpness KEEP

| Knob | Value | Class | Notes |
|------|-------|-------|-------|
| `GETV_SUPERSAMPLE` | `3` | KEEP_SHIP | SS3; smoke required. |
| `GETV_XR_PLAY_SRCFBO` | `1` | KEEP_SHIP | Real SrcFbo name (not `GETV_SRCFBO`). |

### 4. Recenter + input

| Knob | Value | Class |
|------|-------|-------|
| `GETV_XR_ACTIONS` | `1` | KEEP_SHIP |
| `GETV_XR_HANDS` | `1` | KEEP_SHIP |
| `GETV_XR_INPUT` | `1` | KEEP_SHIP |
| `GETV_XR_RECENTER_CHORD` | `1` | KEEP_SHIP |
| `GETV_XR_RECENTER_YAWONLY` | `1` | KEEP_SHIP |
| `GETV_XR_FLOOR_INJECT` | `0` | DIG_OFF |
| `GETV_XR_FLOOR_M` | `-0.200` | KEEP_SHIP |
| `GETV_XR_TURN` | `1` | KEEP_SHIP |
| `GETV_XR_TURN_SCALE` | `60` | PLAYER_PREF |
| `GETV_XR_TURN_DEAD` | `20` | PLAYER_PREF |
| `GETV_XR_BUTTONS` | `1` | KEEP_SHIP |
| `GETV_XR_INPUT_TRIGGER` | `50` | PLAYER_PREF |
| `GETV_XR_INPUT_DEADZONE` | `20` | PLAYER_PREF |
| `GETV_XR_INPUT_EVERY` | `0` | DIG_OFF |
| `GETV_XR_HAPTICS` | `1` | KEEP_SHIP |
| `GETV_XR_BTN_B` | `use` | PLAYER_PREF |
| `GETV_XR_BTN_A` | `weapon` | PLAYER_PREF |
| `GETV_AUTOAIM` | `0` | DIG_OFF |

### 5. Aim / hands / gun / playspace

| Knob | Value | Class |
|------|-------|-------|
| `GETV_VR_HEADYAW` | `1` | KEEP_SHIP |
| `GETV_VR_HEADYAW_IPD` | `1` | KEEP_SHIP |
| `GETV_VR_HEADFRAME` | `2` | KEEP_SHIP |
| `GETV_VR_HANDYAW` | `2` | KEEP_SHIP |
| `GETV_VR_LEVELYAW` | `1` | KEEP_SHIP |
| `GETV_VR_GUNAIM` | `1` | KEEP_SHIP |
| `GETV_VR_GUNMOUNT` | `1` | KEEP_SHIP |
| `GETV_VR_GUNARM` | `1` | KEEP_SHIP |
| `GETV_VR_GUNPITCH` | `0` | DIG_OFF |
| `GETV_VR_GUNARM_TRACE` | `0` | DIG_OFF |
| `GETV_VR_PLAYSPACE` | `1` | KEEP_SHIP |
| `GETV_VR_TILTFIX` | `0` | DIG_OFF |
| `GETV_VR_BODY` | `0` | DIG_OFF |
| `GETV_VR_BODY_NOARMS` | `1` | KEEP_SHIP |
| `GETV_VR_HANDCUBES` | `1` | KEEP_SHIP |
| `GETV_VR_HANDCUBE_MM` | `60` | PLAYER_PREF |
| `GETV_VR_HANDCUBE_MASK` | `1` | KEEP_SHIP |
| `GETV_VR_CASINGS` | `1` | KEEP_SHIP |
| `GETV_VR_SIGHT2D` | `1` | KEEP_SHIP |
| `GETV_VR_SIGHTTRACE` | `0` | DIG_OFF |
| `GETV_VR_RETICLE` | `1` | KEEP_SHIP |
| `GETV_VR_RETICLE_M` | `5.00` | PLAYER_PREF |
| `GETV_VR_RETICLE_HAND` | `1` | KEEP_SHIP |
| `GETV_VR_TOUCHUSE` | `1` | KEEP_SHIP |
| `GETV_VR_TOUCHUSE_R` | `12` | PLAYER_PREF |
| `GETV_VR_TOUCHUSE_TRACE` | `0` | DIG_OFF |
| `GETV_VR_HANDMELEE` | `1` | KEEP_SHIP |
| `GETV_VR_HANDMELEE_R` | `8` | PLAYER_PREF |
| `GETV_VR_HANDMELEE_COOL` | `30` | PLAYER_PREF |
| `GETV_VR_HANDMELEE_TRACE` | `0` | DIG_OFF |

### 6. PLAY0 arm

| Knob | Value | Class | Notes |
|------|-------|-------|-------|
| `GETV_VR_VTXGUARD` | `64` | KEEP_SHIP | 64 KB poison guard; ships ON. |
| `GETV_VR_ADSSIGHT` | `1` | KEEP_SHIP | |
| `GETV_VR_HITSNAP` | `2` | KEEP_SHIP | |
| `GETV_VR_SIGHTPX` | `6` | KEEP_SHIP | |
| `GETV_VR_ADSCULL` | `1` | KEEP_SHIP | |

### 7. Rooms / cull / portals / audio

| Knob | Value | Class |
|------|-------|-------|
| `GETV_VR_DRAWALL` | `1` | KEEP_SHIP |
| `GETV_VR_CULLWIDE` | `3.0` | PLAYER_PREF |
| `GETV_VR_SCREENWIDE` | `3.0` | PLAYER_PREF |
| `GETV_VR_ROOMBUDGET` | `64` | PLAYER_PREF |
| `GETV_VR_LODDIST` | `0.25` | PLAYER_PREF |
| `GETV_ROOMSCISSOR` | `0` | DIG_OFF |
| `GETV_PORTALOPEN` | `1` | KEEP_SHIP |
| `GETV_PROPCULLBOX` | `0` | DIG_OFF |
| `GETV_PROPROOMTEST` | `0` | DIG_OFF |
| `GETV_VR_ROOMTEST` | `0` | DIG_OFF |
| `GETV_VR_PORTALWIDE` | `1` | KEEP_SHIP |
| `GETV_VR_PORTALDEPTH` | `24` | PLAYER_PREF |
| `GETV_VR_PORTALVISITS` | `64` | PLAYER_PREF |
| `GETV_VR_ROOMHEAP` | `4096` | PLAYER_PREF |
| `GETV_VR_ROOMLOADWHY` | `0` | DIG_OFF |
| `GETV_AUDIO_CLOCK` | `device` | PLAYER_PREF |
| `GETV_AUDIO_QUEUE_MS` | `33` | PLAYER_PREF |

### 8. Sky / eye isolation

| Knob | Value | Class |
|------|-------|-------|
| `GETV_VR_SKYMESH` | `1` | KEEP_SHIP |
| `GETV_VR_SKYSCISSOR` | `1` | KEEP_SHIP |
| `GETV_VR_SKYFILL` | `1` | KEEP_SHIP |
| `GETV_VR_SKYFILL2` | `0` | DIG_OFF |
| `GETV_VR_SKYFILL3` | `1` | KEEP_SHIP |

### 9. Corpses / texture / VFX (chair paths vr440 never armed)

| Knob | Value | Class | Notes |
|------|-------|-------|-------|
| `GETV_VR_CORPSEKEEP` | `1` | KEEP_SHIP | Bodies stay after kills. |
| `GETV_VR_CORPSEKEEP_MAX` | `48` | KEEP_SHIP | |
| `GETV_VR_CORPSEKEEP_CEIL` | `440` | KEEP_SHIP | |
| `GETV_VR_TEXINVAL` | `1` | KEEP_SHIP | Explosion / fire texture path. |
| `GETV_VR_TEXDLRETAG` | `1` | KEEP_SHIP | |
| `GETV_VR_WALLCENSUS` | `0` | DIG_OFF | Public boot must not arm census. |
| `GETV_VR_VFXTMEM` | `1` | KEEP_SHIP | |
| `GETV_VR_VFXSHIFT` | `1` | KEEP_SHIP | |
| `GETV_TILE1` | `1` | KEEP_SHIP | |
| `GETV_BASETILE` | `1` | KEEP_SHIP | |
| `GETV_TMEMMAP` | `0` | DIG_OFF | |
| `GETV_TEX16BE` | `1` | KEEP_SHIP | DECODE side; do not set `RGBA16BE`. |
| `GETV_RGBA16BE` | `0` | DIG_OFF | Pinned off (byte-order interlock). |
| `GETV_TEX32BE` | `1` | KEEP_SHIP | |

### Legacy gate name

| Knob | Value | Class | Notes |
|------|-------|-------|-------|
| `GE_VR_XR` | `1` | KEEP_SHIP | **No-op** in this binary; real arm is `GETV_VR`. Kept for flat gate (`GE_VR_XR=0`). |

---

## KEEP arms only (smoke-critical + picture / chair one-liners)

These are the assignments whose primary job is **ON** or a named KEEP value
(`xr`, `3`, `full`, corpse / tex / vfx stack). Count **73** rows (includes
`GEVR_SHIP_TAG`, `GE_VR_XR`, and numeric KEEP like `VTXGUARD=64`).

| Knob | Ship value |
|------|------------|
| `GEVR_SHIP_TAG` | `vr441` |
| `GETV_VR` | `1` |
| `GETV_SIMDIV` | `1` |
| `GETV_XR_PLAY` | `1` |
| `GETV_XR_PLAY_STEREO` | `1` |
| `GETV_XR_PLAY_SCREEN` | `2` |
| `GETV_STEREO` | `1` |
| `GETV_STEREO_SRC` | `xr` |
| `GETV_STEREO_REBUILD` | `1` |
| `GETV_STEREO_VIEWRESTORE` | `1` |
| `GETV_STEREO_HUDGATE` | `1` |
| `GETV_STEREO_AIMRECT` | `1` |
| `GETV_STEREO_GUNOFS` | `1` |
| `GETV_XR_UNITS_PER_M` | `100` |
| `GETV_XR_FOVSYM` | `1` |
| `GETV_XR_HEAD_TRANSLATE` | `1` |
| `GETV_XR_PLAY_AUTORECENTER` | `1` |
| `GETV_XR_PLAY_AUTOSCREEN` | `1` |
| `GETV_XR_PLAY_SRCRECT` | `full` |
| `GETV_XR_PLAY_EYERECT` | `1` |
| `GETV_SUPERSAMPLE` | `3` |
| `GETV_XR_PLAY_SRCFBO` | `1` |
| `GETV_XR_ACTIONS` | `1` |
| `GETV_XR_HANDS` | `1` |
| `GETV_XR_INPUT` | `1` |
| `GETV_XR_RECENTER_CHORD` | `1` |
| `GETV_XR_RECENTER_YAWONLY` | `1` |
| `GETV_XR_FLOOR_M` | `-0.200` |
| `GETV_XR_TURN` | `1` |
| `GETV_XR_BUTTONS` | `1` |
| `GETV_XR_HAPTICS` | `1` |
| `GETV_VR_HEADYAW` | `1` |
| `GETV_VR_HEADYAW_IPD` | `1` |
| `GETV_VR_HEADFRAME` | `2` |
| `GETV_VR_HANDYAW` | `2` |
| `GETV_VR_LEVELYAW` | `1` |
| `GETV_VR_GUNAIM` | `1` |
| `GETV_VR_GUNMOUNT` | `1` |
| `GETV_VR_GUNARM` | `1` |
| `GETV_VR_PLAYSPACE` | `1` |
| `GETV_VR_BODY_NOARMS` | `1` |
| `GETV_VR_HANDCUBES` | `1` |
| `GETV_VR_HANDCUBE_MASK` | `1` |
| `GETV_VR_CASINGS` | `1` |
| `GETV_VR_SIGHT2D` | `1` |
| `GETV_VR_RETICLE` | `1` |
| `GETV_VR_RETICLE_HAND` | `1` |
| `GETV_VR_TOUCHUSE` | `1` |
| `GETV_VR_HANDMELEE` | `1` |
| `GETV_VR_VTXGUARD` | `64` |
| `GETV_VR_ADSSIGHT` | `1` |
| `GETV_VR_HITSNAP` | `2` |
| `GETV_VR_SIGHTPX` | `6` |
| `GETV_VR_ADSCULL` | `1` |
| `GETV_VR_DRAWALL` | `1` |
| `GETV_PORTALOPEN` | `1` |
| `GETV_VR_PORTALWIDE` | `1` |
| `GETV_VR_SKYMESH` | `1` |
| `GETV_VR_SKYSCISSOR` | `1` |
| `GETV_VR_SKYFILL` | `1` |
| `GETV_VR_SKYFILL3` | `1` |
| `GETV_VR_CORPSEKEEP` | `1` |
| `GETV_VR_CORPSEKEEP_MAX` | `48` |
| `GETV_VR_CORPSEKEEP_CEIL` | `440` |
| `GETV_VR_TEXINVAL` | `1` |
| `GETV_VR_TEXDLRETAG` | `1` |
| `GETV_VR_VFXTMEM` | `1` |
| `GETV_VR_VFXSHIFT` | `1` |
| `GETV_TILE1` | `1` |
| `GETV_BASETILE` | `1` |
| `GETV_TEX16BE` | `1` |
| `GETV_TEX32BE` | `1` |
| `GE_VR_XR` | `1` |

All **39** `$requiredBootKnobs` entries appear in the tables above.

---

## DIG_OFF (explicit `=0` in boot)

| Knob | Value | Notes |
|------|-------|-------|
| `GETV_XR_FLOOR_INJECT` | `0` | |
| `GETV_XR_INPUT_EVERY` | `0` | |
| `GETV_AUTOAIM` | `0` | |
| `GETV_VR_GUNPITCH` | `0` | |
| `GETV_VR_GUNARM_TRACE` | `0` | |
| `GETV_VR_TILTFIX` | `0` | |
| `GETV_VR_BODY` | `0` | |
| `GETV_VR_SIGHTTRACE` | `0` | |
| `GETV_VR_TOUCHUSE_TRACE` | `0` | |
| `GETV_VR_HANDMELEE_TRACE` | `0` | |
| `GETV_ROOMSCISSOR` | `0` | |
| `GETV_PROPCULLBOX` | `0` | |
| `GETV_PROPROOMTEST` | `0` | |
| `GETV_VR_ROOMTEST` | `0` | |
| `GETV_VR_ROOMLOADWHY` | `0` | Smoke forbidden if non-zero. |
| `GETV_VR_SKYFILL2` | `0` | |
| `GETV_VR_WALLCENSUS` | `0` | Smoke forbidden if non-zero. |
| `GETV_TMEMMAP` | `0` | |
| `GETV_RGBA16BE` | `0` | Required off when `TEX16BE=1`. |

### DIG_OFF (wipe only, section 0)

Cleared to empty so a polluted shell cannot arm dig / falsifiers. **C_DEFAULT
UNKNOWN** after wipe unless the player sets them.

`GETV_XR_FOVMATCH`, `GETV_REALCLOCK`, `GETV_GUN_AIM`, `GETV_FULLSCREEN`,
`GETV_WINDOW`, `GETV_MSAA`, `GETV_FXAA`, `GETV_CRT`, `GETV_CRT_SCANLINE`,
`GETV_CRT_MASK`, `GETV_CRT_CURVE`, `GETV_CRT_VIGNETTE`, `GETV_XR_SHARPLOG`,
`GETV_FIREDUMP`, `GETV_VR_VISFAR`, `GETV_ROOMHOLD`, `GETV_CULLWHY`,
`GETV_STEREO_PROBE`, `GETV_ROOMTRACE`, `GETV_SKYTRACE`, `GETV_GRNDSKIPROOM`,
`GETV_GRNDNOP`, `GETV_GRNDPAT`, `GETV_PORTALBOX`, `GETV_MUSICFADE_HZ`,
`GETV_AUDIO_DEBUG`, `GETV_NO_AUDIO`, `GETV_NO_AUDIO_QUEUE`,
`GETV_VR_BODY_NOARMS_TRACE`, `GETV_XR_INPUT_FIREHAND`, `GETV_XR_INPUT_WALKHAND`,
`GETV_XR_TURN_HAND`, `GETV_XR_TURN_INVERT`, `GETV_XR_BUTTON_HAND`,
`GETV_XR_BTN_SQUEEZE`, `GETV_XR_BTN_SQUEEZE_PCT`, `GETV_CONTROLS`,
`GETV_DUALANALOG`, `GETV_CHR_DEBUG`, `GETV_FRONTTRACE`, `GETV_INPUT_DEBUG`,
`GETV_CINETRACE`, `GETV_STATE`, `GETV_STAGE`, `GETV_LOGFLUSH`,
`GETV_VR_WATERTILE`, `GETV_VR_OCCLSKIP`, `GETV_VR_FOGSKIP`, `GETV_VR_DISTSKIP`,
`GETV_VR_TEXTBAND_PAD`, `GETV_VR_TEXTBAND_X`, `GETV_VR_AMMOHUD_PAD`,
`GETV_VR_MSGSCALE`, `GETV_VR_BLOODINVAL`, `GETV_VR_TITLEBG`, `GETV_VR_HUB`.

Notable wipe: **`GETV_VR_MSGSCALE`** is intentionally **not** set in vr441 boot;
comments say chair KEEP used `50` in-binary and vr439/vr440 wrongly used dead
`GETV_MSGSCALE=434`. Post-wipe value is **C_DEFAULT UNKNOWN** (comment: 50).

Smoke **forbidden** if armed in boot: `GETV_XR_FOVMATCH`, `GETV_VR_WALLCENSUS`,
`GETV_VR_ROOMLOADWHY`, `GETV_FIREDUMP`, `GETV_STAGE`, `GETV_CHR_DEBUG`,
`GETV_INPUT_DEBUG`, `GETV_FRONTTRACE`, `GETV_CINETRACE`, `GETV_LOGFLUSH`,
`GETV_SKYTRACE`, `GETV_ROOMTRACE`, `GETV_CULLWHY`, `GETV_XR_SHARPLOG`.

Smoke **dead names** (do not assign): `GETV_SRCFBO`, `GETV_MSGSCALE`.

---

## Parked notes (not boot inventory)

- **Flat purple explosions** - headset TEXINVAL / byte-order KEEP is armed in
  vr441 boot; monitor path does not run that boot. Wrong-color explosions on
  flat remain a known gap; track as a **new issue** when filing (not closed by
  vr441 headset sit alone).
- **Flat audio desync** - `Play-on-monitor.bat` now seeds `GETV_AUDIO_CLOCK=device`
  and `GETV_AUDIO_QUEUE_MS=33` (same as vr441 headset boot). Re-run the monitor
  sit gate on the next zip cut; close [#48](https://github.com/no6969el/GEVR/issues/48)
  after wear confirms.

---

## Counts (vr441 boot)

| Bucket | Count |
|--------|------:|
| Non-empty `GETV_*` / `GE_*` / `GEVR_*` assigns | 117 |
| KEEP_SHIP (feature arms) | 73 |
| PLAYER_PREF (boot tuning) | 25 |
| DIG_OFF (explicit `=0`) | 19 |
| FLAT_FORCE (monitor bat only) | 7 |
| Wipe-only knobs (C_DEFAULT UNKNOWN) | 56 |

---

*Generated for ship-default-ON planning. Reconcile against private `getv` before
changing binary defaults.*
