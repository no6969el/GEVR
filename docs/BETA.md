# Beta testing guide

GEVR's public label is **Beta**. Expect crashes and unfinished corners. File them on Issues. We would rather hear from you than guess.

**Play this cut:** [**vr439**](https://github.com/no6969el/GEVR/releases/latest) (GitHub Latest). It is the only tag with a zip. Play steps: [README Play](../README.md#play).

Older tags [vr420](https://github.com/no6969el/GEVR/releases/tag/vr420) / [vr434](https://github.com/no6969el/GEVR/releases/tag/vr434) / [vr438](https://github.com/no6969el/GEVR/releases/tag/vr438) stay for history. Their zips were removed.

- **vr434** was pulled. ROM images were baked into `goldeneye.exe`.
- **vr438** was BYO-ROM, but VR boot was a stub. It looked like an old build.
- **vr439** restores the vr434 KEEP picture on BYO-ROM. Grab that.

Player door: [00-START-HERE.md](00-START-HERE.md). Play steps: [README Play](../README.md#play). Hands: [CONTROLS.md](CONTROLS.md). What is coming: [ROADMAP.md](ROADMAP.md). Pitch: [FEATURES.md](../FEATURES.md). How to report: [CONTRIBUTING.md](../CONTRIBUTING.md). License map: [LICENSE-MAP.md](../LICENSE-MAP.md).

## Before you start

- A **legal** USA GoldenEye ROM you already own (we do not supply one)
- Windows PC
- Optional: OpenXR headset. No headset? Use the monitor bat.
- Download: [Releases/latest](https://github.com/no6969el/GEVR/releases/latest) (**vr439**) - play steps in [README Play](../README.md#play)

## Launchers

- **Headset:** `Start-GEVR.bat` (KEEP: XR stereo source, SrcFbo, supersample 3, sky / playspace)
- **Monitor / no headset:** `Play-on-monitor.bat` (VR off, no stereo eyes)

Use the bats. Do not double-click `goldeneye.exe`. Details: [CONTROLS.md](CONTROLS.md).

**Verified:** Pimax Crystal Super + SteamVR OpenXR via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR), native **PimaxXR**, **Quest 3 + Virtual Desktop OpenXR**.

**Hz:** 72 / 80 / 90 should work. Headset default is 90. Over 90 is still beta-test territory. Report what you see.

## Install and run

1. Download and unzip **vr439**.
2. Headset: `Start-GEVR.bat`. Monitor / no headset: `Play-on-monitor.bat`.
3. Point at your USA `.z64`.
4. First prepare waits once while images land in `%LOCALAPPDATA%\GEVR\cache`. Then play.
5. Recenter in VR with **both thumbstick clicks**.

## First run vs updating

- **New install:** run `Start-GEVR.bat` (headset) or `Play-on-monitor.bat` (no headset), pick your USA `.z64`, wait once, play.
- **After a Beta update:** keep the same `.z64`. The ship stamp forces one re-prepare. You do not delete the cache for a normal update.
- **Troubleshooting only:** delete `%LOCALAPPDATA%\GEVR\cache` and run the bat again.

## How to report

[Open an Issue](https://github.com/no6969el/GEVR/issues/new/choose) with:

- Headset
- OpenXR runtime
- SteamVR on/off
- HMD vs monitor
- **`Start-GEVR.bat` yes/no** (if no headset, use **`Play-on-monitor.bat`** and pick No)

Map / action if it crashed. First install vs first launch after a new zip vs a later launch also helps.

Do **not** upload your ROM. We do not need it and we do not want it. Forms: [CONTRIBUTING.md](../CONTRIBUTING.md).

## What to test first

- Boot into VR and look around
- Aim and shoot
- Explosions and sparks
- Dam mid-range crates (known pop - still useful)
- Dam water look (known murky - still useful)
- One-eye glass bullet holes (known - still useful)
- Facility halls / guards
- Local split-screen on a monitor if you have a friend on the couch
- Note any crash: what map, what action

## What not to expect yet

- Store-polish stability
- Perfect body / hands
- LAN or online multiplayer (local split-screen works now; a LAN **add-on** is later; online is later than that)

Jump in and enjoy finally being Bond in GoldenEye VR.
