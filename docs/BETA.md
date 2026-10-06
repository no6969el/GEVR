> **vr456.7:** GitHub **Latest**. Grab [vr456.7](https://github.com/no6969el/GEVR/releases/tag/vr456.7) or use Update in GevrRomStarter.

# Beta testing guide

GEVR's public label is **Beta**. Expect crashes and unfinished corners. File them on Issues. We would rather hear from you than guess.

**Play this cut:** [**vr456.7**](https://github.com/no6969el/GEVR/releases/latest) (GitHub Latest). Zip: **`GEVR-Beta-vr456.7-win64.zip`**. The zip has no ROM and no HD texture pack. Install: [README](../README.md#install). Tag: [vr456.7](https://github.com/no6969el/GEVR/releases/tag/vr456.7). Hands: [CONTROLS.md](CONTROLS.md).

Older tag **pages** stay for history. **Latest is vr456.7.** Do not download from [vr420](https://github.com/no6969el/GEVR/releases/tag/vr420) / [vr434](https://github.com/no6969el/GEVR/releases/tag/vr434) / [vr438](https://github.com/no6969el/GEVR/releases/tag/vr438) / [vr439](https://github.com/no6969el/GEVR/releases/tag/vr439) / [vr440](https://github.com/no6969el/GEVR/releases/tag/vr440) / [vr441](https://github.com/no6969el/GEVR/releases/tag/vr441).

- **vr434** was pulled. ROM images were baked into `goldeneye.exe`.
- **vr443** zip was pulled (HOLD) then superseded by vr443.1 (motion KEEP not baked in), then vr444.
- **vr441** / **vr440** tag pages stay. Their **zips were stripped** when later cuts shipped.
- **vr439** zip removed when vr440 shipped. Tag page stays for record.

Player door: [00-START-HERE.md](00-START-HERE.md). Install: [README](../README.md#install). Hands: [CONTROLS.md](CONTROLS.md). Pitch: [FEATURES.md](../FEATURES.md). How to report: [CONTRIBUTING.md](../CONTRIBUTING.md). License map: [LICENSE-MAP.md](../LICENSE-MAP.md).

Linux testers: flat alpha is a separate prerelease. [linux-alpha1](https://github.com/no6969el/GEVR/releases/tag/linux-alpha1). Windows Latest stays this vr456.7 zip.

## Before you start

- A **legal** USA GoldenEye ROM you already own (we do not supply one)
- Windows PC
- Optional: OpenXR headset. No headset? Use the monitor bat.
- Download: [**GEVR-Beta-vr456.7-win64.zip**](https://github.com/no6969el/GEVR/releases/latest). [README Install](../README.md#install)

## Launchers

- **Headset:** `Start-GEVR.bat` (KEEP: XR stereo source, SrcFbo, supersample 3, sky / playspace)
- **Monitor / no headset:** `Play-on-monitor.bat` (VR off, no stereo eyes)

Use the bats. Do not double-click `goldeneye.exe`. Details: [CONTROLS.md](CONTROLS.md).

**Verified:** Pimax Crystal Super + SteamVR OpenXR via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR), native **PimaxXR**, **Quest 3 + Virtual Desktop OpenXR (VDXR)**.

**Frame rate:** the game follows your headset by default. Fixed 90 is still available in **GEVR Settings**. High refresh is still Beta-test territory. Try it and report if something feels off.

### Half-speed / mushy VR?

Turn off runtime motion smoothing before blaming Hertz.

- **SteamVR:** Settings → Video → **Motion Smoothing = Off** (also check Applications → GEVR / `goldeneye.exe`).
- **Virtual Desktop:** **Space Warp = Off**.

SteamVR Motion Smoothing and Virtual Desktop Space Warp can make the game feel half-speed. Turn those off in the runtime; this is not a GEVR menu toggle.

## Install and run

1. Download and unzip **`GEVR-Beta-vr456.7-win64.zip`** from [Latest](https://github.com/no6969el/GEVR/releases/latest) / [vr456.7](https://github.com/no6969el/GEVR/releases/tag/vr456.7). The zip has no ROM and no HD texture pack.
2. Headset: `Start-GEVR.bat`. Monitor / no headset: `Play-on-monitor.bat`.
3. Point at your USA `.z64`.
4. First prepare waits once while images land in `%LOCALAPPDATA%\GEVR\cache`. Then play.
5. Recenter in VR with **both thumbstick clicks**.

## First run vs updating

- **New install:** run `Start-GEVR.bat` (headset) or `Play-on-monitor.bat` (no headset), pick your USA `.z64`, wait once, play.
- **After a Beta update:** keep the same `.z64`. The ship stamp forces one re-prepare. **Saves are kept.** You do not delete the cache for a normal update.
- **Troubleshooting only:** run **`Clear-GEVR-cache.bat`** from the vr456.7 zip (type **YES**) to wipe **`%LOCALAPPDATA%\GEVR\cache`** only (keeps saves). If the picture still looks wrong, delete `%LOCALAPPDATA%\GEVR` and run the bat again (that also drops saves).
- **Half-speed / mushy VR:** SteamVR **Motion Smoothing Off**; Virtual Desktop **Space Warp Off**. See [Half-speed / mushy VR?](#half-speed--mushy-vr) above.

## Beta wear notes

- **Gunfire fixed ([#84](https://github.com/no6969el/GEVR/issues/84)):** rifle guards use correct rifle fire tables/cadence (not pistol lean/single-shot from a 64-bit weapon-prop misread).
- **Janus meeting:** the crowd stops respawning after the meeting.
- **Throwables:** grenades, mines, plastique, and the covert modem show in your hand and leave from the grip. Remote, proximity, and timed mines draw in the hand like the grenade. Left-hand throwables are not mirrored.
- **Black flicker ([#55](https://github.com/no6969el/GEVR/issues/55)):** quiet for now. Stuck mines (including Facility) use the same no-modem scrap hide as the covert modem, so people can play. Props still pass through other props; that overlap is the cause.
- **Ammo:** digits sit on the grip and read from behind the gun. Flat mode keeps the corner count.
- **Weapon change:** **Right A** is the next weapon on the right hand. **Left X** is the next weapon on the left hand. Stick click opens the weapon wheel (circle default; **STICK WHEEL** can set Weapon Vert). Centre follows the hover. Boxes are 2x dark grey.
- **Holster swap:** same-gun hip grip is a real swap. Weapon switch prefers a free inventory copy over the hip gun.
- **Watch picker:** pictures and labels on the left cuff (Laser / Magnet / Repel). Magnet is unlimited in VR.
- **Moonraker:** small circular scope lens only. Look through the ring. Shoot through the ring. Dual Moonrakers give two lenses. No front grill screen.
- **Rockets:** stay locked to the launcher, not your head. Flat mouse-aim crosshair stays centred.
- **Aimers:** red and green on the shot's first hit.
- **VR comfort:** no walk bob, landing dip, or gun-hand sway.
- **HD memo:** decoded HD pictures stay in memory. `GETV_HD_MEMO_MB=0` turns it off.
- **XR catch-up / quit:** missed headset frames no longer slow the sim. Quitting actually quits.
- **Hand cubes:** hide while that hand holds a weapon; smaller when empty.
- **Frame rate:** follows the headset by default. Fixed 90 is still available in **GEVR Settings**.
- **GEVR Settings:** on **Mission Select**, next to **Select Mission**, **Multiplayer**, and **Cheat Options**. It is not named Options. **A** selects a row. Stick left / right changes the value. **Apply** saves and relaunches. Prefs save under `%LOCALAPPDATA%\GEVR`.
- **Watch:** **Y** opens it. **GAME OPTIONS** goes past ratio. The last line says scroll down for VR settings. Cuff press follows the picker / pause watch. There is no detonator in the weapon cycle. The **left stick** moves the watch highlight. **Tab** still pauses on the keyboard.
- **Reload:** magazine or chest-cross gesture. **B** is USE, not VR gun reload. Tank shells auto-load. A handle grab swaps hands and does not reload. See [CONTROLS.md](CONTROLS.md#reload-gesture-vr).
- **Sniper:** a green dot stays on. Shots leave the eye along that dot. Right stick forward or back steps the zoom (30, 20, 15, 10, 7). Walking does not zoom.
- **Swing:** uses the held weapon's damage. Shooting does not make the knife swing by itself.
- **Update button:** the starter checks GitHub Latest on open. Click **Update** to pull a newer zip. Saves, settings, and your `.z64` stay put.
- **Auto-aim** starts off.
- **B** covers switches, plant, and activate. **Menu** also opens the pause watch.
- **Tank:** stand on the chassis and you auto-mount. Stick pitch aims the shells. Empty mag auto-loads the next shell.
- **Empty hand** draws a cube.
- **GL** is single-shot / muzzle feel OK.
- **Not in this zip:** thermal vision, corpse freeze, Gun Drop / Arm Bounds default-on.
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

- Boot into VR and look around (no walk bob, no landing dip, no extra gun-hand sway)
- Aim and shoot (auto-aim starts off); **left trigger** fires a left-hand gun on its own
- Dual-wield with two guns (each trigger fires its hand)
- Reload with the magazine or chest-cross gesture. Confirm **B** is USE, not gun reload. Tank shells should auto-load. A handle grab should swap hands and not reload
- **Right A** goes to the next weapon on the right hand. **Left X** goes to the next weapon on the left hand
- Stick click opens the circular weapon wheel. Try **STICK WHEEL** Weapon Vert
- Hip holster swap on the same gun. All Guns should prefer a free inventory copy
- Watch picker pictures and labels (Laser / Magnet / Repel). Magnet unlimited in VR
- Moonraker: small circular lens only, shots through the ring, two lenses if dual-wielded
- Throw a grenade. Remote, proximity, and timed mines should draw in the hand the same way. Left-hand throwables should not be mirrored
- Open the watch with **Y**. Open **GAME OPTIONS** and scroll past ratio. The last line says scroll down for VR settings
- Climb a tank by standing on the chassis; pitch the turret with the stick; fire and watch the next shell auto-load
- Grenade launcher: one shot per trigger, no self-blast
- Rockets stay on the launcher, with a flat crosshair
- Red and green aimers on the shot's first hit
- Far guards / characters stay readable
- Empty hand shows the cube; armed hand hides it
- Die / continue / load another mission in the same process (should stay clean)
- Explosions and sparks (mass blow-ups can still crash; keep the fault file)
- Dam blue flicker is probably the convert modem (known; issue #70; labels got mixed); stuck modem scrap should be quieter; Dam water look
- One-eye glass bullet holes
- Facility halls / guards
- Local split-screen on a monitor if you have a friend on the couch
- Note any crash: what map, what action, fault file yes/no
- If you run high Hz: note headset rate and whether anything feels off
- Quit: the game should actually quit

Jump in and enjoy finally being Bond in GoldenEye VR.

Stay tuned. Star the repo and [follow @no6969el](https://github.com/no6969el).
