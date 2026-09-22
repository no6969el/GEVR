# Feature snapshot (public) - 2026-09-21

> Player snapshot: [FEATURES.md](../FEATURES.md). Play [vr444](https://github.com/no6969el/GEVR/releases/latest) (GitHub Latest). This page is not a second Play guide.

High-level status of the playable wear. Current zip is **[`GEVR-Beta-vr444-win64.zip`](https://github.com/no6969el/GEVR/releases/latest)**. Play steps: [README Play](../README.md#play-vr444---the-one-to-grab). Download: [Latest](https://github.com/no6969el/GEVR/releases/latest) / [vr444](https://github.com/no6969el/GEVR/releases/tag/vr444).

## Working enough for Beta focus
- OpenXR VR present (true stereo path)
- Head look + locomotion keepers; physical walk/strafe moves you
- Controller gun aim; squeeze ADS mark on the gun ray (not stuck in face centre)
- Dual-wield fire from each hand and per-hand tracers
- Throwables appear in your hand and leave from the grip (grenades, mines, plastique, covert modem); grenades and mines resized to better match real hand dimensions
- Tap **A** = next weapon; left-controller **X** = previous
- Hand cue cube hides while that hand holds a weapon; smaller cube when empty / fists
- Thrown grenades follow the hand; rockets nose along the flight path
- Grenade launcher single-shot / muzzle feel OK (projectile-spawn experiment left off)
- Tank auto-mount and stick pitch for tank shells
- VR Settings on intro hub (look right); in-app Update in GevrRomStarter
- Game follows headset refresh rate (72 / 80 / 90 / 120 as reported)
- Stuck covert-modem scrap on the floor quieter (hand modem / screens stay)
- Die / continue reload no longer dumps you in junk space ([issue #38](https://github.com/no6969el/GEVR/issues/38) SETUPCOPY)
- Far guards more visible (007 far-vis)
- Hard-crash fault file `gevr-fault-*.txt` beside the exe
- Hit placement improved on recent wear
- Explosion / fire colour and bullet sparks much improved vs early September
- Flat desktop play still available (`Play-on-monitor.bat`)
- Local / split-screen multiplayer on a monitor

## Cooking / later (not shipped)
Soft list only (matches [vr444 RELEASE-NOTES](https://github.com/no6969el/GEVR/releases/tag/vr444)):
- Two-hand snap is still cooking
- Weapon wheel HUD is still cooking
- High Hz (over 90) is Beta-test territory - report if something feels off ([issue #49](https://github.com/no6969el/GEVR/issues/49))
- Ghost empty hand parked; cube is temporary
- Gun vanish below chest (GUNZ / HANDSOLID) left off until fixed
- Big explosion / plane shell can still hard-crash (fault file helps)

## Open / rough
- Crashes under investigation (report with the [issue forms](https://github.com/no6969el/GEVR/issues/new/choose))
- Mass explosions can still hard-crash (fault file now)
- Dam blue flicker still known ([issue #70](https://github.com/no6969el/GEVR/issues/70)); dish-on-glass depth still open
- Dam crates / water / one-eye glass holes
- Full colocated body + fancy hand mesh unfinished (cube now; ghost fingers later)

## Refused / not shipping as crutches
- FOV-match camera rewrite stays off unless a measured falsifier reopens it
- Boxy articulated hand mesh was rejected in the chair
- No ROM redistribution (do not upload ROM files)

## Headset / runtime (vr444)

Verified on this Beta (details in README Play):

- Pimax Crystal Super + **SteamVR OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR)
- Native **PimaxXR**
- **Quest 3 + Virtual Desktop (VDXR)**

When you report: headset, OpenXR runtime, SteamVR on/off, HMD vs monitor, Start-GEVR.bat yes/no (Play-on-monitor.bat if no headset). [CONTRIBUTING.md](../CONTRIBUTING.md).
