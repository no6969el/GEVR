# Feature snapshot (public) - 2026-09-20

> Player snapshot: [FEATURES.md](../FEATURES.md). Play [vr442](https://github.com/no6969el/GEVR/releases/latest) (GitHub Latest). This page is not a second Play guide.

High-level status of the playable wear. Current zip is **vr442**. Play steps: [README Play](../README.md#play-vr442---the-one-to-grab). Download: [Latest release](https://github.com/no6969el/GEVR/releases/latest).

## Working enough for Beta focus
- OpenXR VR present (true stereo path)
- Head look + locomotion keepers
- Controller gun aim; squeeze ADS mark on the gun ray (not stuck in face centre)
- Dual-wield fire from each hand and per-hand tracers
- Thrown grenades follow the hand; rockets nose along the flight path
- Grenade launcher single-shot
- Tank auto-mount on chassis + stick pitch for shells
- Die / continue / pad reload in the same process ([issue #38](https://github.com/no6969el/GEVR/issues/38))
- Far character visibility boost
- Empty left hand temporary cube (MASK left)
- Hard-crash fault file `gevr-fault-*.txt` beside the exe
- Hit placement improved on recent wear
- Explosion / fire colour and bullet sparks much improved vs early September
- Flat desktop play still available (`Play-on-monitor.bat`)
- Local / split-screen multiplayer on a monitor

## Cooking / later (not shipped)
Soft list only:
- Two-hand support snap and cube hide-on-near
- Runtime Hertz request ([issue #49](https://github.com/no6969el/GEVR/issues/49)); boot stays 90-pinned
- Ghost empty hand (parked); nicer hands after that
- Big object / plane-shell explosion hard crash can still happen

## Open / rough
- Crashes under investigation (report with the [issue forms](https://github.com/no6969el/GEVR/issues/new/choose))
- Mass explosions can still hard-crash (fault file now)
- Dam crates / water / one-eye glass holes
- Full colocated body + fancy hand mesh unfinished (cube now; ghost fingers later)

## Refused / not shipping as crutches
- FOV-match camera rewrite stays off unless a measured falsifier reopens it
- Boxy articulated hand mesh was rejected in the chair
- No ROM redistribution (do not upload ROM files)

## Headset / runtime (vr442)

Verified on this Beta (details in README Play):

- Pimax Crystal Super + **SteamVR OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR)
- Native **PimaxXR**
- **Quest 3 + Virtual Desktop (VDXR)**

When you report: headset, OpenXR runtime, SteamVR on/off, HMD vs monitor, Start-GEVR.bat yes/no (Play-on-monitor.bat if no headset). [CONTRIBUTING.md](../CONTRIBUTING.md).
