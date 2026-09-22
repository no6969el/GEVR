> **vr444 (2026-09-21):** Major glitch cut - stuck covert-modem scrap quieted, plus hands / throwables / weapon cycle / follow headset Hz. Built on vr443.1. Grab [vr444](https://github.com/no6969el/GEVR/releases/tag/vr444) or use Update.

# Beta testing guide

GEVR's public label is **Beta**. Expect crashes and unfinished corners. File them on Issues. We would rather hear from you than guess.

**Play this cut:** [**vr444**](https://github.com/no6969el/GEVR/releases/latest) (GitHub Latest). Zip: **`GEVR-Beta-vr444-win64.zip`**. Play steps: [README](../README.md#play-vr444---the-one-to-grab). Tag: [vr444](https://github.com/no6969el/GEVR/releases/tag/vr444).

Older tag **pages** stay for history. **Latest is vr444.** Do not download from [vr420](https://github.com/no6969el/GEVR/releases/tag/vr420) / [vr434](https://github.com/no6969el/GEVR/releases/tag/vr434) / [vr438](https://github.com/no6969el/GEVR/releases/tag/vr438) / [vr439](https://github.com/no6969el/GEVR/releases/tag/vr439) / [vr440](https://github.com/no6969el/GEVR/releases/tag/vr440) / [vr441](https://github.com/no6969el/GEVR/releases/tag/vr441).

- **vr434** was pulled. ROM images were baked into `goldeneye.exe`.
- **vr443** zip was pulled (HOLD) then superseded by vr443.1 (motion KEEP not baked in), then vr444.
- **vr441** / **vr440** tag pages stay. Their **zips were stripped** when later cuts shipped.
- **vr439** zip removed when vr440 shipped. Tag page stays for record.

Player door: [00-START-HERE.md](00-START-HERE.md). Play steps: [README](../README.md#play-vr444---the-one-to-grab). Hands: [CONTROLS.md](CONTROLS.md). What is coming: [ROADMAP.md](ROADMAP.md) and [COMING-SOON.md](COMING-SOON.md). Pitch: [FEATURES.md](../FEATURES.md). How to report: [CONTRIBUTING.md](../CONTRIBUTING.md). License map: [LICENSE-MAP.md](../LICENSE-MAP.md).

## Before you start

- A **legal** USA GoldenEye ROM you already own (we do not supply one)
- Windows PC
- Optional: OpenXR headset. No headset? Use the monitor bat.
- Download: [**GEVR-Beta-vr444-win64.zip**](https://github.com/no6969el/GEVR/releases/latest) - play steps in [README](../README.md#play-vr444---the-one-to-grab)

## Launchers

- **Headset:** `Start-GEVR.bat` (KEEP: XR stereo source, SrcFbo, supersample 3, sky / playspace)
- **Monitor / no headset:** `Play-on-monitor.bat` (VR off, no stereo eyes)

Use the bats. Do not double-click `goldeneye.exe`. Details: [CONTROLS.md](CONTROLS.md).

**Verified:** Pimax Crystal Super + SteamVR OpenXR via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR), native **PimaxXR**, **Quest 3 + Virtual Desktop OpenXR (VDXR)**.

**Hz:** The game follows your headset refresh (72 / 80 / 90 / 120 as reported). High Hz is still Beta-test territory - try it and report if something feels off. We do not call every high-Hz path signed off yet ([issue #49](https://github.com/no6969el/GEVR/issues/49)).

## Install and run

1. Download and unzip **`GEVR-Beta-vr444-win64.zip`** from [Latest](https://github.com/no6969el/GEVR/releases/latest) / [vr444](https://github.com/no6969el/GEVR/releases/tag/vr444).
2. Headset: `Start-GEVR.bat`. Monitor / no headset: `Play-on-monitor.bat`.
3. Point at your USA `.z64`.
4. First prepare waits once while images land in `%LOCALAPPDATA%\\GEVR\\cache`. Then play.
5. Recenter in VR with **both thumbstick clicks**.

## First run vs updating

- **New install:** run `Start-GEVR.bat` (headset) or `Play-on-monitor.bat` (no headset), pick your USA `.z64`, wait once, play.
- **After a Beta update:** keep the same `.z64`. The ship stamp forces one re-prepare. **Saves are kept.** You do not delete the cache for a normal update.
- **Troubleshooting only:** run **`Clear-GEVR-cache.bat`** from the vr444 zip (type **YES**) to wipe **`%LOCALAPPDATA%\\GEVR\\cache`** only (keeps saves). The tag notes say: if the picture still looks wrong, delete `%LOCALAPPDATA%\\GEVR` and run the bat again (that also drops saves).

## vr444 wear notes

- **Throwables:** grenades / mines / plastique / covert modem show in your hand and leave from the grip.
- **Weapon cycle:** tap **A** = next; left-controller **X** = previous. (Weapon wheel HUD still cooking.)
- **Hand cubes:** hide while that hand holds a weapon; smaller when empty / fists.
- **Refresh:** follows your headset rate (not pinned to 90).
- **VR Settings:** on the intro hub, **look right**. Right stick U/D = row, L/R = change (TURN SPEED / STYLE / SNAP SIZE). Prefs save under `%LOCALAPPDATA%\GEVR`.
- **Update button:** starter checks GitHub Latest on open. Click **Update** to pull a newer zip (saves / prefs / your `.z64` left alone).
- **Auto-Aim defaults OFF** (`GETV_AUTOAIM` in the shipped exe).
- **Pause watch:** **left stick** moves the highlight in VR.
- **B** reloads. Pause is the **Menu / system button** in headset. **Tab** on keyboard / monitor still works.
- **Tank:** stand on the chassis and you auto-mount. Stick pitch aims the shells.
- **Empty hand** draws a cube for now (temporary stand-in). Ghost hand is parked.
- **GL** is single-shot / muzzle feel OK. Projectile-spawn experiment is left off.
- **Gun vanish below chest** (GUNZ / HANDSOLID) is left off until fixed.
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

Die / continue / pad reload was fixed in earlier cuts ([issue #38](https://github.com/no6969el/GEVR/issues/38)). If the world still goes glitchy after a death or mission return, fully quit and relaunch, then file a new Issue with the five fields above.

## What to test first

- Boot into VR and look around
- Aim and shoot (Auto-Aim should default OFF)
- Dual-wield if you pick up a second gun (each hand should fire on its own)
- Cycle weapons with **A** / left **X**
- Throw a grenade / mine / plastique / modem - should show in hand and leave from the grip
- Pause watch: move highlight with **left stick**
- Climb a tank by standing on the chassis; pitch the turret with the stick
- Grenade launcher: one shot per trigger, no self-blast
- Rockets: nose along the flight path
- Far guards / characters stay readable
- Empty hand shows the cube; armed hand hides it
- Die / continue / load another mission in the same process (should stay clean)
- Explosions and sparks (mass blow-ups can still crash - keep the fault file)
- Dam blue flicker (known - issue #70); stuck modem scrap should be quieter; Dam water look
- One-eye glass bullet holes
- Facility halls / guards
- Local split-screen on a monitor if you have a friend on the couch
- Note any crash: what map, what action, fault file yes/no
- If you run high Hz: note headset rate and whether anything feels off

## What not to expect yet

- Store-polish stability
- Two-hand snap (still cooking)
- Weapon wheel HUD (still cooking)
- Signed-off high Hz polish (follow-headset is in; report quirks)
- Gun vanish below chest (GUNZ / HANDSOLID)
- Perfect body / hands (ghost fingers are parked; cube is the interim)
- LAN or online multiplayer (local split-screen works now; a LAN **add-on** is later; online is later than that)

Jump in and enjoy finally being Bond in GoldenEye VR.

Stay tuned. Star the repo and [follow @no6969el](https://github.com/no6969el).
