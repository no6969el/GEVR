# Beta testing guide

GEVR's public label is **Beta**. Expect crashes and unfinished corners. File them on Issues. We would rather hear from you than guess.

**Play this cut:** [**vr442**](https://github.com/no6969el/GEVR/releases/latest) (GitHub Latest). Download the release zip on that page. Play steps: [README](../README.md#play-vr442---the-one-to-grab).

Older tag **pages** stay for history. **Latest is vr442.** Do not download from [vr420](https://github.com/no6969el/GEVR/releases/tag/vr420) / [vr434](https://github.com/no6969el/GEVR/releases/tag/vr434) / [vr438](https://github.com/no6969el/GEVR/releases/tag/vr438) / [vr439](https://github.com/no6969el/GEVR/releases/tag/vr439).

- **vr434** was pulled. ROM images were baked into `goldeneye.exe`.
- **vr440** stays published (not Latest) - picture-only boot; see [README](../README.md#what-vr441--vr438-already-taught-us-still-true).
- **vr441** stays published (not Latest) - full chair boot, before the vr442 wear pack.
- **vr439** zip removed when vr440 shipped. Tag page stays for record.

Player door: [00-START-HERE.md](00-START-HERE.md). Play steps: [README](../README.md#play-vr442---the-one-to-grab). Hands: [CONTROLS.md](CONTROLS.md). What is coming: [ROADMAP.md](ROADMAP.md) and [COMING-SOON.md](COMING-SOON.md). Pitch: [FEATURES.md](../FEATURES.md). How to report: [CONTRIBUTING.md](../CONTRIBUTING.md). License map: [LICENSE-MAP.md](../LICENSE-MAP.md).

## Before you start

- A **legal** USA GoldenEye ROM you already own (we do not supply one)
- Windows PC
- Optional: OpenXR headset. No headset? Use the monitor bat.
- Download: [Latest release zip](https://github.com/no6969el/GEVR/releases/latest) (**vr442**) - play steps in [README](../README.md#play-vr442---the-one-to-grab)

## Launchers

- **Headset:** `Start-GEVR.bat` (KEEP: XR stereo source, SrcFbo, supersample 3, sky / playspace)
- **Monitor / no headset:** `Play-on-monitor.bat` (VR off, no stereo eyes)

Use the bats. Do not double-click `goldeneye.exe`. Details: [CONTROLS.md](CONTROLS.md).

**Verified:** Pimax Crystal Super + SteamVR OpenXR via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR), native **PimaxXR**, **Quest 3 + Virtual Desktop OpenXR (VDXR)**.

**Hz:** 72 / 80 should work. Default and wear recommendation is **90**. Over 90 is still beta-test territory. Report what you see. We do not call 120 / 144 signed off. The public boot is still **90-pinned**; runtime Hertz request is later ([issue #49](https://github.com/no6969el/GEVR/issues/49)).

## Install and run

1. Download and unzip **vr442** from the [Latest release](https://github.com/no6969el/GEVR/releases/latest).
2. Headset: `Start-GEVR.bat`. Monitor / no headset: `Play-on-monitor.bat`.
3. Point at your USA `.z64`.
4. First prepare waits once while images land in `%LOCALAPPDATA%\\GEVR\\cache`. Then play.
5. Recenter in VR with **both thumbstick clicks**.

## First run vs updating

- **New install:** run `Start-GEVR.bat` (headset) or `Play-on-monitor.bat` (no headset), pick your USA `.z64`, wait once, play.
- **After a Beta update:** keep the same `.z64`. The ship stamp forces one re-prepare. **Saves are kept.** You do not delete the cache for a normal update.
- **Troubleshooting only:** run **`Clear-GEVR-cache.bat`** from the vr442 zip (type **YES**) to wipe **`%LOCALAPPDATA%\\GEVR\\cache`** only (keeps saves). You can delete that folder by hand instead. Optional: delete all **`%LOCALAPPDATA%\\GEVR`** if you want cache **and** saves gone - not the default path. See `RELEASE-NOTES.txt` in the zip.

## vr442 wear notes

- **Auto-Aim defaults OFF** (`GETV_AUTOAIM` in the shipped exe).
- **Pause watch:** **left stick** moves the highlight in VR.
- **B** reloads. Pause is the **Menu / system button** in headset. **Tab** on keyboard / monitor still works.
- **Tank:** stand on the chassis and you auto-mount. Stick pitch aims the shells.
- **Empty left hand** is a temporary cube (MASK left). Ghost fingers are later.
- **Hard crash:** look beside `goldeneye.exe` for `gevr-fault-*.txt` and attach the first lines (no ROM).

## How to report

[Open an Issue](https://github.com/no6969el/GEVR/issues/new/choose) with:

- Headset
- OpenXR runtime
- SteamVR on/off
- HMD vs monitor
- **`Start-GEVR.bat` yes/no** (if no headset, use **`Play-on-monitor.bat`** and pick No)
- Map / what you were doing
- A log from the zip folder or the console window, any **`gevr-fault-*.txt`**, or a short clip

Do **not** upload your ROM. We do not need it and we do not want it. Forms: [CONTRIBUTING.md](../CONTRIBUTING.md).

Die / continue / pad reload was fixed in vr442 ([issue #38](https://github.com/no6969el/GEVR/issues/38)). If the world still goes glitchy after a death or mission return, fully quit and relaunch, then file a new Issue with the five fields above.

## What to test first

- Boot into VR and look around
- Aim and shoot (Auto-Aim should default OFF)
- Dual-wield if you pick up a second gun (each hand should fire on its own)
- Pause watch: move highlight with **left stick**
- Climb a tank by standing on the chassis; pitch the turret with the stick
- Grenade launcher: one shot per trigger, no self-blast
- Rockets: nose along the flight path
- Far guards / characters stay readable
- Empty left hand shows the cube
- Die / continue / load another mission in the same process (should stay clean)
- Explosions and sparks (mass blow-ups can still crash - keep the fault file)
- Dam mid-range crates and Dam water look
- One-eye glass bullet holes
- Facility halls / guards
- Local split-screen on a monitor if you have a friend on the couch
- Note any crash: what map, what action, fault file yes/no

## What not to expect yet

- Store-polish stability
- Two-hand support snap or the cube hiding when hands get near
- Runtime Hertz auto-request (boot stays 90-pinned)
- Perfect body / hands (ghost fingers are parked; cube is the interim)
- LAN or online multiplayer (local split-screen works now; a LAN **add-on** is later; online is later than that)

Jump in and enjoy finally being Bond in GoldenEye VR.

Stay tuned. Star the repo and [follow @no6969el](https://github.com/no6969el).
