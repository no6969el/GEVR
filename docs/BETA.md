> **vr450.2 (2026-09-28):** GitHub **Latest**. Keeper stack hard-coded in the binary (cuff, FREEARM, door/corpse, mines, re-grab, landmark, aim scale, and related comfort). Grab [vr450.2](https://github.com/no6969el/GEVR/releases/tag/vr450.2) or use **Update**.

# Beta testing guide

GEVR's public label is **Beta**. Expect crashes and unfinished corners. File them on Issues. We would rather hear from you than guess.

**Play this cut:** [**vr450.2**](https://github.com/no6969el/GEVR/releases/latest) (GitHub Latest). Zip: **`GEVR-Beta-vr450.2-win64.zip`**. Play steps: [README](../README.md#play-vr4502---the-one-to-grab). Tag: [vr450.2](https://github.com/no6969el/GEVR/releases/tag/vr450.2). Direct download: [GEVR-Beta-vr450.2-win64.zip](https://github.com/no6969el/GEVR/releases/download/vr450.2/GEVR-Beta-vr450.2-win64.zip).

Older tag **pages** stay for history. **Latest is vr450.2.** Do not download from [vr420](https://github.com/no6969el/GEVR/releases/tag/vr420) / [vr434](https://github.com/no6969el/GEVR/releases/tag/vr434) / [vr438](https://github.com/no6969el/GEVR/releases/tag/vr438) / [vr439](https://github.com/no6969el/GEVR/releases/tag/vr439) / [vr440](https://github.com/no6969el/GEVR/releases/tag/vr440) / [vr441](https://github.com/no6969el/GEVR/releases/tag/vr441) / [vr445.2](https://github.com/no6969el/GEVR/releases/tag/vr445.2) as if they were Latest.

- **vr434** was pulled. ROM images were baked into `goldeneye.exe`.
- **vr443** zip was pulled (HOLD) then superseded by later cuts.
- Older tag pages stay. Their **zips were stripped** when later cuts shipped.

Player door: [00-START-HERE.md](00-START-HERE.md). Play steps: [README](../README.md#play-vr4502---the-one-to-grab). Hands: [CONTROLS.md](CONTROLS.md). Pitch: [FEATURES.md](../FEATURES.md). How to report: [CONTRIBUTING.md](../CONTRIBUTING.md). License map: [LICENSE-MAP.md](../LICENSE-MAP.md).

## Before you start

- A **legal** USA GoldenEye ROM you already own (we do not supply one)
- Windows PC
- Optional: OpenXR headset. No headset? Use the monitor bat.
- Download: [**GEVR-Beta-vr450.2-win64.zip**](https://github.com/no6969el/GEVR/releases/download/vr450.2/GEVR-Beta-vr450.2-win64.zip) — play steps in [README](../README.md#play-vr4502---the-one-to-grab)

## Launchers

- **Headset:** `Start-GEVR.bat` — **GevrRomStarter** finds `goldeneye.exe` next to itself and rewrites the game path for you.
- **Monitor / no headset:** `Play-on-monitor.bat` (VR off, no stereo eyes)

Use the bats. Do not double-click `goldeneye.exe`. Details: [CONTROLS.md](CONTROLS.md).

**Verified:** Pimax Crystal Super + SteamVR OpenXR via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR), native **PimaxXR**, **Quest 3 + Virtual Desktop OpenXR (VDXR)**.

**Hz:** The game follows your headset refresh (72 / 80 / 90 / 120 as reported). High Hz is still Beta-test territory — try it and report if something feels off. We do not call every high-Hz path signed off yet ([issue #49](https://github.com/no6969el/GEVR/issues/49)).

### Half-speed / mushy VR?

Turn off runtime motion smoothing before blaming Hertz.

- **SteamVR:** Settings → Video → **Motion Smoothing = Off** (also check Applications → GEVR / `goldeneye.exe`).
- **Virtual Desktop:** **Space Warp = Off**.

GEVR follows headset Hz and ties game speed to that rate — MotSmooth / Space Warp (SSW / ASW family) halves the app rate and the game will feel half-rate. This is not a GEVR toggle.

## Install and run

1. Download and unzip **`GEVR-Beta-vr450.2-win64.zip`** from [Latest](https://github.com/no6969el/GEVR/releases/latest) / [vr450.2](https://github.com/no6969el/GEVR/releases/tag/vr450.2).
2. Headset: `Start-GEVR.bat`. Monitor / no headset: `Play-on-monitor.bat`.
3. Point at your USA `.z64`.
4. First prepare waits once while images land in `%LOCALAPPDATA%\GEVR\cache`. Then play.
5. Recenter in VR with **both thumbstick clicks**.

## First run vs updating

- **New install:** run `Start-GEVR.bat` (headset) or `Play-on-monitor.bat` (no headset), pick your USA `.z64`, wait once, play.
- **After a Beta update:** keep the same `.z64`. The ship stamp forces one re-prepare. **Saves are kept.** You do not delete the cache for a normal update. Or open GevrRomStarter and click **Update**.
- **Troubleshooting only:** run **`Clear-GEVR-cache.bat`** from the zip (type **YES**) to wipe **`%LOCALAPPDATA%\GEVR\cache`** only (keeps saves). If the picture still looks wrong, delete `%LOCALAPPDATA%\GEVR` and run the bat again (that also drops saves).
- **Half-speed / mushy VR:** SteamVR **Motion Smoothing Off**; Virtual Desktop **Space Warp Off** — see [Half-speed / mushy VR?](#half-speed--mushy-vr) above.

## vr450.2 wear notes

- **Keepers hard-coded:** cuff, FREEARM, door/corpse, mines, re-grab, melee, landmark, aim scale, and related comfort stay on with a clean launch — no special boot flags.
- **Cuff / watch:** left-hand cuff presentation is more reliable through stage transitions.
- **FREEARM ([#109](https://github.com/no6969el/GEVR/issues/109)):** two-handed NPC / weapon poses look better (left hand stays on the gun more often).
- **Surface geometry ([#117](https://github.com/no6969el/GEVR/issues/117)):** vertex-reference fixes for more stable Surface renders.
- **Door snap / false doors / corpse pass:** door-edge aim is more dependable; false doors quieter; bodies less likely to jam a door.
- **Re-grab + mines:** thrown remote / prox mines can be picked back up; mines can stick to guards, follow them, and stay visible while carried.
- **Landmark / aim scale / embed eye:** aim and world landmarks stay more readable in headset.
- **Throwables:** grenades / mines / plastique / covert modem show in your hand and leave from the grip.
- **Weapon cycle:** tap **A** = next; left-controller **X** = previous. **B** reloads.
- **Hand cubes:** hide while that hand holds a weapon; smaller when empty / fists.
- **Refresh:** follows your headset rate.
- **VR Settings:** on the intro hub, **look right**. Prefs save under `%LOCALAPPDATA%\GEVR`.
- **Update button:** starter checks GitHub Latest on open.
- **Auto-Aim defaults OFF**.
- **Tank:** stand on the chassis and you auto-mount. Stick pitch aims the shells.
- **Hard crash:** look beside `goldeneye.exe` for `gevr-fault-*.txt` and attach the first lines (no ROM).

## Next series (not this zip)

Levels and **gameplay stoppers**: Frigate door / aperture behavior, mission progression and lock issues, save-slot coverage, remaining prop-on-prop / Dam-water problems.

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

- Boot into VR and look around; check cuff / watch on the left controller
- Aim and shoot (Auto-Aim should default OFF); squeeze ADS
- Dual-wield if you pick up a second gun
- Cycle weapons with **A** / left **X**; reload with **B**
- Throw a remote / prox mine — re-grab it; stick one on a guard and watch it ride
- Open / close doors near bodies (should not jam as often)
- Pause watch: move highlight with **left stick**
- Climb a tank by standing on the chassis
- Facility halls / guards; note FREEARM two-hand poses
- Surface sits after destroying props ([#117](https://github.com/no6969el/GEVR/issues/117))
- Die / continue / load another mission in the same process
- Local split-screen on a monitor if you have a friend on the couch
- Note any crash: what map, what action, fault file yes/no

Jump in and enjoy finally being Bond in GoldenEye VR.

Stay tuned. Star the repo and [follow @no6969el](https://github.com/no6969el).
