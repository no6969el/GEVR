# Beta testing guide

GEVR’s public label is **Beta**. Expect crashes and unfinished corners - file them on Issues. The current public play zip is **[vr438](https://github.com/no6969el/GEVR/releases/tag/vr438)** (BYO-ROM, file-backed images).

**vr434 was pulled** on 2026-09-16 because that build linked ROM-derived image data into `goldeneye.exe` and could boot without a ROM. Do not use an old vr434 download - grab **vr438** instead.

## Before you start

- A **legal** USA GoldenEye ROM you already own (we do not supply one)
- Windows PC
- Optional: OpenXR headset. Flat monitor is fine for a quick look
- Download: [vr438 Release](https://github.com/no6969el/GEVR/releases/tag/vr438) or [all Releases](https://github.com/no6969el/GEVR/releases)

## VR runtime

**Verified:**
- Pimax Crystal Super + **SteamVR as OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR)
- Native **PimaxXR**
- **Quest 3 + Virtual Desktop (VDXR)**

Use `Start-GEVR.bat` from the zip (launches **GevrRomStarter**, not bare `goldeneye.exe`). Details: [CONTROLS.md](CONTROLS.md).

**Hz:** 72 / 80 / 90 should work; default is 90. Above 90 = still beta - report what you see.

## Install and run

1. Download and unzip **vr438**.
2. Run **`Start-GEVR.bat`** and point **GevrRomStarter** at your USA `.z64`.
3. The zip ships **`glew32.dll`** and the other runtime DLLs - keep them next to the exe when you unzip.
4. Play. VR is default; flat/desktop works too. If it crashes or looks wrong, [open an Issue](https://github.com/no6969el/GEVR/issues/new/choose).

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
- Multiplayer (roadmap later - LAN add-on first)

Jump in and enjoy finally being Bond in GoldenEye VR.
