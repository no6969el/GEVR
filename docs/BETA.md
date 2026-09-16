# Beta testing guide

GEVR’s public label is **Beta**. Expect crashes and unfinished corners - file them on Issues.

**vr434 was pulled** (ROM images were linked into `goldeneye.exe`). The next supported zip is **vr438** (BYO-ROM, file-backed images) after owner smoke - watch [Releases](https://github.com/no6969el/GEVR/releases).

## Before you start

- A **legal** USA GoldenEye ROM you already own (we do not supply one)
- Windows PC
- Optional: OpenXR headset. Flat monitor is fine for a quick look
- Download: [Releases](https://github.com/no6969el/GEVR/releases)

## VR runtime

**Verified:**
- Pimax Crystal Super + **SteamVR as OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR)
- Native **PimaxXR**
- **Quest 3 + Virtual Desktop (VDXR)**

Use `Start-GEVR.bat` from the zip. Details: [CONTROLS.md](CONTROLS.md).

**Hz:** 72 / 80 / 90 should work; default is 90. Above 90 = still beta - report what you see.

## Install and run

1. Download and unzip the current **Release zip** when available (starts with **vr438**).
2. Run **`Start-GEVR.bat`** (launches **GevrRomStarter**, not bare `goldeneye.exe`). Point at your **USA `.z64`** when asked.
3. VR is default; flat/desktop works too.
4. Play. If it crashes or looks wrong, [open an Issue](https://github.com/no6969el/GEVR/issues/new/choose).

## What to test first

- Boot into VR and look around (comfort / tracking)
- Aim and shoot
- Explosions and sparks
- Dam mid-range crates (known pop - still useful reports)
- Dam water look (known flat/murky - still useful)
- Facility halls / guards
- Note any crash: what map, what action

## What not to expect yet

- Store-polish stability
- Perfect body / hands
- Multiplayer (roadmap later)

Jump in and enjoy finally being Bond in GoldenEye VR.
