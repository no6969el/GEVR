# Feature snapshot (public) - 2026-09-28

> Player snapshot: [FEATURES.md](../FEATURES.md). Play [vr450.2](https://github.com/no6969el/GEVR/releases/latest) (GitHub Latest). This page is not a second Play guide.

High-level status of the playable wear. Current zip is **[`GEVR-Beta-vr450.2-win64.zip`](https://github.com/no6969el/GEVR/releases/download/vr450.2/GEVR-Beta-vr450.2-win64.zip)**. Play steps: [README Play](../README.md#play-vr4502---the-one-to-grab). Download: [Latest](https://github.com/no6969el/GEVR/releases/latest) / [vr450.2](https://github.com/no6969el/GEVR/releases/tag/vr450.2).

## Working enough for Beta focus
- OpenXR VR present (true stereo path)
- Head look + locomotion keepers; physical walk/strafe moves you
- Controller gun aim; squeeze ADS mark on the gun ray (not stuck in face centre)
- Dual-wield fire from each hand and per-hand tracers
- Throwables appear in your hand and leave from the grip (grenades, mines, plastique, covert modem)
- Tap **A** = next weapon; left-controller **X** = previous; **B** = reload
- Hand cue cube hides while that hand holds a weapon; smaller cube when empty / fists
- **Cuff / watch** stays with the left controller through stage changes
- **FREEARM ([#109](https://github.com/no6969el/GEVR/issues/109)):** two-handed NPC / weapon poses
- **VTXFIXREFS ([#117](https://github.com/no6969el/GEVR/issues/117)):** more stable Surface geometry
- Door-edge snap, quieter false doors, corpse pass so bodies jam doors less
- Mine **re-grab**; mines stick to / follow guards and stay visible while carried
- Landmark / aim scale / embed eye comfort for readable aim in headset
- Keepers hard-coded in the binary — clean launch keeps them on
- Tank auto-mount and stick pitch for tank shells
- VR Settings on intro hub (look right); in-app Update in GevrRomStarter
- Starter finds colocated `goldeneye.exe` and sets game path
- Game follows headset refresh rate (72 / 80 / 90 / 120 as reported)
- Die / continue reload no longer dumps you in junk space ([issue #38](https://github.com/no6969el/GEVR/issues/38))
- Flat desktop play (`Play-on-monitor.bat`); local / split-screen multiplayer on a monitor

## Open / rough (next series)
- Levels and **gameplay stoppers** (Frigate door / aperture, mission locks, save-slot coverage)
- Remaining prop-on-prop / Dam-water problems
- Crashes under investigation (report with the [issue forms](https://github.com/no6969el/GEVR/issues/new/choose))
- Mass explosions can still hard-crash
- No ROM redistribution (do not upload ROM files)

## Headset / runtime (vr450.2)

Verified on this Beta (details in README Play):

- Pimax Crystal Super + **SteamVR OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR)
- Native **PimaxXR**
- **Quest 3 + Virtual Desktop (VDXR)**

When you report: headset, OpenXR runtime, SteamVR on/off, HMD vs monitor, Start-GEVR.bat yes/no (Play-on-monitor.bat if no headset). [CONTRIBUTING.md](../CONTRIBUTING.md).
