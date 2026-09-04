# GEVR — VR for GoldenEye 007, native from-source track

GEVR is the **native** VR track for GoldenEye 007: decompiled C built as a host
program, plus the VR layer, docs, and measurement tools. **Not** static
recompilation, **not** emulation. You supply your own ROM for assets.

## Related repositories

| Repo | Role |
|---|---|
| [no6969el/goldeneye-native](https://github.com/no6969el/goldeneye-native) | From-scratch native host + VR architecture / Phase 0 bind plan (MIT) |
| Playable native port (local / upstream TBD) | Bootable PC port the GETV stereo work attaches to — not redistributed here yet |
| [cblock85/GoldenEye64Recomp](https://github.com/cblock85/GoldenEye64Recomp) | **Separate / historical** recomp host (GPL-3.0). Early headset experiments used it; it is not the active GEVR track and is never vendored here |

## What this repo contains

| Path | What |
|---|---|
| `docs/` | Live record and task state — start at `docs/00-START-HERE.md` and `docs/00-STATE.md` |
| `xr/` | Standalone OpenXR probe / stereo validators |
| `tools/` | Offline stereo / screenshot measurement helpers |
| `historical/recomp/` | Early MIT patches that dropped into GoldenEye64Recomp only |

## Status (honest)

Active engineering is on the **native** eye-model / stereo instruments, documented
in `docs/`. Headset shipping is not claimed. Early recomp headset work is
historical context, not the product direction.

## Licence

MIT (`LICENSE`). No ROM or game assets. Recomp host stays external (GPL-3.0).
See `PRIOR-ART.md` for Perfect Dark VR credits.
