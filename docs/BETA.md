# Beta testing guide

GEVR's public label is **Beta**. Expect crashes and unfinished corners. File them on Issues. We would rather hear from you than guess.

**Play this cut:** [**vr441**](https://github.com/no6969el/GEVR/releases/tag/vr441) (GitHub Latest). Download the release zip on that page. Play steps: [README](../README.md#play-vr441---the-one-to-grab).

Older tag **pages** stay for history. **Latest is vr441.** Do not download from [vr420](https://github.com/no6969el/GEVR/releases/tag/vr420) / [vr434](https://github.com/no6969el/GEVR/releases/tag/vr434) / [vr438](https://github.com/no6969el/GEVR/releases/tag/vr438) / [vr439](https://github.com/no6969el/GEVR/releases/tag/vr439).

- **vr434** was pulled. ROM images were baked into `goldeneye.exe`.
- **vr440** stays published (not Latest) - picture-only boot; see [README - What went wrong in vr440](../README.md#what-went-wrong-in-vr440).
- **vr439** zip removed when vr440 shipped. Tag page stays for record.

Player door: [00-START-HERE.md](00-START-HERE.md). Play steps: [README](../README.md#play-vr441---the-one-to-grab). Hands: [CONTROLS.md](CONTROLS.md). What is coming: [ROADMAP.md](ROADMAP.md). Pitch: [FEATURES.md](../FEATURES.md). How to report: [CONTRIBUTING.md](../CONTRIBUTING.md). License map: [LICENSE-MAP.md](../LICENSE-MAP.md).

## Before you start

- A **legal** USA GoldenEye ROM you already own (we do not supply one)
- Windows PC
- Optional: OpenXR headset. No headset? Use the monitor bat.
- Download: [vr441 release zip](https://github.com/no6969el/GEVR/releases/tag/vr441) (**vr441**) - play steps in [README](../README.md#play-vr441---the-one-to-grab)

## Launchers

- **Headset:** `Start-GEVR.bat` (KEEP: XR stereo source, SrcFbo, supersample 3, sky / playspace)
- **Monitor / no headset:** `Play-on-monitor.bat` (VR off, no stereo eyes)

Use the bats. Do not double-click `goldeneye.exe`. Details: [CONTROLS.md](CONTROLS.md).

**Verified:** Pimax Crystal Super + SteamVR OpenXR via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR), native **PimaxXR**, **Quest 3 + Virtual Desktop OpenXR**.

**Hz:** 72 / 80 / 90 should work. Headset default is 90. Over 90 is still beta-test territory. Report what you see.

## Install and run

1. Download and unzip **vr441** from the release page.
2. Headset: `Start-GEVR.bat`. Monitor / no headset: `Play-on-monitor.bat`.
3. Point at your USA `.z64`.
4. First prepare waits once while images land in `%LOCALAPPDATA%\GEVR\cache`. Then play.
5. Recenter in VR with **both thumbstick clicks**.

## First run vs updating

- **New install:** run `Start-GEVR.bat` (headset) or `Play-on-monitor.bat` (no headset), pick your USA `.z64`, wait once, play.
- **After a Beta update:** keep the same `.z64`. The ship stamp forces one re-prepare. **Saves are kept.** You do not delete the cache for a normal update.
- **Troubleshooting only:** run **`Clear-GEVR-cache.bat`** from the vr441 zip (type **YES**) to wipe **`%LOCALAPPDATA%\GEVR\cache`** only (keeps saves). You can delete that folder by hand instead. Optional: delete all **`%LOCALAPPDATA%\GEVR`** if you want cache **and** saves gone - not the default path. See `RELEASE-NOTES.txt` in the zip.

## vr441 wear notes

- **Auto-Aim defaults OFF** (`GETV_AUTOAIM` in the shipped exe).
- **Pause watch:** **left stick** moves the highlight in VR.
- **B/Y** opens pause in headset. **Tab** on keyboard / monitor still works.

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
- Aim and shoot (Auto-Aim should default OFF)
- Pause watch: move highlight with **left stick**
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
