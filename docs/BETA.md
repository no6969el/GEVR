> **vr452.2:** GitHub **Latest**. Use **Update** in GevrRomStarter and stay on Latest so you have the features listed here. Saves stay.

# Beta testing guide

GEVR's public label is **Beta**. Expect crashes and unfinished corners. File them on Issues. We would rather hear from you than guess.

**Play this cut:** [**vr452.2**](https://github.com/no6969el/GEVR/releases/latest) (GitHub Latest). Zip: **`GEVR-Beta-vr452.2-win64.zip`**. Play steps: [README](../README.md#how-to-play). Tag: [vr452.2](https://github.com/no6969el/GEVR/releases/tag/vr452.2). Direct download: [GEVR-Beta-vr452.2-win64.zip](https://github.com/no6969el/GEVR/releases/download/vr452.2/GEVR-Beta-vr452.2-win64.zip).

Always stay on Latest via **Update** (or a fresh zip). Older tag pages stay for history - do not download them as if they were Latest.

Player door: [00-START-HERE.md](00-START-HERE.md). Play steps: [README](../README.md#how-to-play). Hands: [CONTROLS.md](CONTROLS.md). Pitch: [FEATURES.md](../FEATURES.md). How to report: [CONTRIBUTING.md](../CONTRIBUTING.md). License map: [LICENSE-MAP.md](../LICENSE-MAP.md).

## Before you start

- A **legal** USA GoldenEye ROM you already own (we do not supply one)
- Windows PC
- Optional: OpenXR headset. No headset? Use the monitor bat.
- Download: [**GEVR-Beta-vr452.2-win64.zip**](https://github.com/no6969el/GEVR/releases/download/vr452.2/GEVR-Beta-vr452.2-win64.zip) - or use **Update** - play steps in [README](../README.md#how-to-play)

## Launchers

- **Headset:** `Start-GEVR.bat` - **GevrRomStarter** finds `goldeneye.exe` next to itself and rewrites the game path for you.
- **Monitor / no headset:** `Play-on-monitor.bat` (VR off, no stereo eyes)

Use the bats. Do not double-click `goldeneye.exe`. Details: [CONTROLS.md](CONTROLS.md).

**Verified:** Pimax Crystal Super + SteamVR OpenXR via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR), native **PimaxXR**, **Quest 3 + Virtual Desktop OpenXR (VDXR)**.

**Hz:** The game follows your headset refresh (72 / 80 / 90 / 120 as reported). High Hz is still Beta-test territory - try it and report if something feels off.

### Half-speed / mushy VR?

Turn off runtime motion smoothing before blaming Hertz.

- **SteamVR:** Settings -> Video -> **Motion Smoothing = Off** (also check Applications -> GEVR / `goldeneye.exe`).
- **Virtual Desktop:** **Space Warp = Off**.

GEVR follows headset Hz and ties game speed to that rate - MotSmooth / Space Warp (SSW / ASW family) halves the app rate and the game will feel half-rate. This is not a GEVR toggle.

## Install and run

1. Download and unzip **`GEVR-Beta-vr452.2-win64.zip`** from [Latest](https://github.com/no6969el/GEVR/releases/latest) / [vr452.2](https://github.com/no6969el/GEVR/releases/tag/vr452.2) - or click **Update** in GevrRomStarter.
2. Headset: `Start-GEVR.bat`. Monitor / no headset: `Play-on-monitor.bat`.
3. Point at your USA `.z64`.
4. First prepare waits once while images land in `%LOCALAPPDATA%/GEVR/cache`. Then play.
5. Recenter in VR with **both thumbstick clicks**.

## First run vs updating

- **New install:** run `Start-GEVR.bat` (headset) or `Play-on-monitor.bat` (no headset), pick your USA `.z64`, wait once, play.
- **After a Beta update:** keep the same `.z64`. The ship stamp forces one re-prepare. **Saves are kept.** Or open GevrRomStarter and click **Update**. Always stay on Latest for the features below.
- **Troubleshooting only:** run **`Clear-GEVR-cache.bat`** from the zip (type **YES**) to wipe **`%LOCALAPPDATA%/GEVR/cache`** only (keeps saves). If the picture still looks wrong, delete `%LOCALAPPDATA%/GEVR` and run the bat again (that also drops saves).
- **Half-speed / mushy VR:** SteamVR **Motion Smoothing Off**; Virtual Desktop **Space Warp Off** - see above.

## vr452.2 wear notes

- **Update first** - stay on Latest so GEVR Settings, Visual modes, Apply, Reset, and HD toggle are in your folder.
- **GEVR Settings:** Mode Select -> GEVR Settings. Change picture / Visual / HD, then **Apply** (game restarts; settings stick). See [GEVR-SETTINGS.md](GEVR-SETTINGS.md).
- **Visual:** **VR** (full headset), **XR** (square outline), **Flat** (monitor). Apply to switch.
- **Reset defaults:** confirm Yes; restore follows pending Visual (VR-friendly or Flat-friendly).
- **HD textures:** optional; off by default; needs a pack on disk.
- **Cuff / watch:** left cuff on left; right hand over cuff + grab detonates remotes if mines are armed, else watch laser from the cuff; hip holster; right hand draws over the cuff; no three-arm watch pull-out; proximity alone does not fire.
- **Hand cycle:** left alone when you want; cycle per hand; grip pick; per-hip holster; hands respect each other's space.
- **Prop stick:** barrels, tanks, vehicles, crates, modems, and prop-on-prop; guards still stick as before.
- Throwables leave from your grip.
- Weapon cycle: tap **A** = next; left-controller **X** = previous. **B** reloads.
- Hand cubes hide while that hand holds a weapon.
- Frame rate can follow your headset or display from GEVR Settings.
- VR Settings glass: on the intro hub, **look right** (turn style / snap). Prefs save under `%LOCALAPPDATA%/GEVR`.
- Auto-Aim defaults OFF.
- Tank: stand on the chassis and you auto-mount. Stick pitch aims the shells.
- Hard crash: look beside `goldeneye.exe` for `gevr-fault-*.txt` and attach the first lines (no ROM).

## Next series (not this zip)

Levels and **gameplay stoppers** already reported. Scope / lens fill is still parked - not in this cut.

## How to report

[Open an Issue](https://github.com/no6969el/GEVR/issues/new/choose) with:

- Headset
- OpenXR runtime
- SteamVR on/off
- HMD vs monitor
- **`Start-GEVR.bat` yes/no** (if no headset, use **`Play-on-monitor.bat`** and pick No)
- Map / what you were doing
- A log from the zip folder or the console window, any **`gevr-fault-*.txt`**, or a short clip

Do **not** upload your ROM. Forms: [CONTRIBUTING.md](../CONTRIBUTING.md).

## What to test first

- Boot into VR; confirm **Update** / Latest is vr452.2
- GEVR Settings: change Visual or supersample, **Apply**, confirm it stuck after relaunch
- Cuff / watch: right over cuff + grab (detonate or laser); holster at hip; no three-arm look
- Hand cycle: empty left, per-hand cycle, grip pick, per-hip holster
- Prop stick on a barrel / crate / vehicle and on a guard
- Aim and shoot; squeeze ADS; dual-wield
- Throw a remote / prox mine - re-grab it
- Open / close doors near bodies
- Climb a tank by standing on the chassis
- Die / continue / load another mission in the same process
- Local split-screen on a monitor if you have a friend on the couch
- Note any crash: what map, what action, fault file yes/no

Jump in and enjoy finally being Bond in GoldenEye VR.

Stay tuned. Star the repo and [follow @no6969el](https://github.com/no6969el).
