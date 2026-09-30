# Feature snapshot (public) - 2026-09-30

> Player snapshot: [FEATURES.md](../FEATURES.md). Play [vr451](https://github.com/no6969el/GEVR/releases/latest) (GitHub Latest). Stay on Latest via **Update**. This page is not a second Play guide.

High-level status of the playable wear. Current zip is [GEVR-Beta-vr451-win64.zip](https://github.com/no6969el/GEVR/releases/download/vr451/GEVR-Beta-vr451-win64.zip). Play steps: [README](../README.md#how-to-play). Download: [Latest](https://github.com/no6969el/GEVR/releases/latest) / [vr451](https://github.com/no6969el/GEVR/releases/tag/vr451).

## Working enough for Beta focus
- OpenXR VR present (true stereo path)
- Head look + locomotion; physical walk/strafe moves you
- Controller gun aim; squeeze ADS on the gun ray
- Dual-wield fire from each hand
- Throwables appear in your hand and leave from the grip
- Tap **A** = next weapon; left-controller **X** = previous; **B** = reload
- Hand cue cube hides while that hand holds a weapon
- **Cuff / watch** - left cuff; right over cuff + grab detonates if mines armed else watch laser; hip holster; draws over cuff; no three-arm watch pull-out; proximity alone does not fire
- **Hand cycle** - left alone; per-hand cycle; grip pick; per-hip holster; hands respect each other's space
- **Prop stick** - barrels / tanks / vehicles / crates / modems + prop-on-prop; guards still stick as before
- Mine **re-grab**
- Door-edge snap, quieter false doors, corpse pass so bodies jam doors less
- Free-aim arms, vertex fixes, and related comfort already in this pass
- Landmark / aim scale / embed eye for readable aim in headset
- Tank auto-mount and stick pitch for tank shells
- VR Settings on intro hub (look right); in-app **Update** in GevrRomStarter - stay on Latest
- Starter finds colocated goldeneye.exe and sets game path
- Game follows headset refresh rate (72 / 80 / 90 / 120 as reported)
- Flat desktop play (Play-on-monitor.bat); local / split-screen multiplayer on a monitor

## Open / rough (next series)
- Levels and **gameplay stoppers** already reported
- Scope / lens fill still parked - not claimed shipped
- Crashes under investigation (report with the [issue forms](https://github.com/no6969el/GEVR/issues/new/choose))
- Mass explosions can still hard-crash
- No ROM redistribution (do not upload ROM files)

## Headset / runtime (vr451)

Verified on this Beta (details in README):

- Pimax Crystal Super + **SteamVR OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR)
- Native **PimaxXR**
- **Quest 3 + Virtual Desktop (VDXR)**

When you report: headset, OpenXR runtime, SteamVR on/off, HMD vs monitor, Start-GEVR.bat yes/no (Play-on-monitor.bat if no headset). [CONTRIBUTING.md](../CONTRIBUTING.md).
