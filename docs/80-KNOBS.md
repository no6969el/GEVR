# Dig knobs (public)

Ship builds are already tuned for VR. Most env knobs below are dig-only.

## Timing / refresh

Timing is tuned for VR (follows headset refresh for normal play). Dig knobs that pin FPS or alter simulation cadence exist for emergency / dig use only — details of the timing recalculation are not published here.

- `GETV_FPS` — optional pin (normally unset = follow HMD).
- `GETV_SIMHZ` — dig; leave ship default.
- Emergency pin helper: `GEVR-Quest-Pin90.bat` (behavior only).

## Other dig knobs

Non-timing dig knobs remain internal. Prefer Latest ship zip + in-app Update.

See also: `docs/BETA.md`, `README.md`.
