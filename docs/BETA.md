> **vr456.1:** GitHub **Latest**. Grab [vr456.1](https://github.com/no6969el/GEVR/releases/tag/vr456.1) or use Update in GevrRomStarter.

# Beta testing guide

GEVR's public label is **Beta**. Expect crashes and unfinished corners. File them on Issues. We would rather hear from you than guess.

**Play this cut:** [**vr456.1**](https://github.com/no6969el/GEVR/releases/latest) (GitHub Latest). Zip: **`GEVR-Beta-vr456.1-win64.zip`**. The zip has no ROM and no HD texture pack. Install: [README](../README.md#install). Tag: [vr456.1](https://github.com/no6969el/GEVR/releases/tag/vr456.1).

Older tag **pages** stay for history. **Latest is vr456.1.** Do not download from [vr420](https://github.com/no6969el/GEVR/releases/tag/vr420) / [vr434](https://github.com/no6969el/GEVR/releases/tag/vr434) / [vr438](https://github.com/no6969el/GEVR/releases/tag/vr438) / [vr439](https://github.com/no6969el/GEVR/releases/tag/vr439) / [vr440](https://github.com/no6969el/GEVR/releases/tag/vr440) / [vr441](https://github.com/no6969el/GEVR/releases/tag/vr441).

- **vr434** was pulled. ROM images were baked into `goldeneye.exe`.
- **vr443** zip was pulled (HOLD) then superseded by vr443.1 (motion KEEP not baked in), then vr444.
- **vr441** / **vr440** tag pages stay. Their **zips were stripped** when later cuts shipped.
- **vr439** zip removed when vr440 shipped. Tag page stays for record.

Player door: [How to play](00-START-HERE.md). Install: [README](../README.md#install). Hands: [Controls](CONTROLS.md). Picture: [GEVR Settings](GEVR-SETTINGS.md). [HD textures](GEVR-SETTINGS.md#hd-textures). Pitch: [FEATURES.md](../FEATURES.md). How to report: [CONTRIBUTING.md](../CONTRIBUTING.md). License map: [LICENSE-MAP.md](../LICENSE-MAP.md).

An older playtest clip is on [YouTube](https://www.youtube.com/watch?v=z4B0Ceqrf6I). Picture and controls may not match vr456.1.

## Before you start

- A **legal** USA GoldenEye ROM you already own (we do not supply one)
- Windows PC
- Optional: OpenXR headset. No headset? Use the monitor bat.
- Download: [**GEVR-Beta-vr456.1-win64.zip**](https://github.com/no6969el/GEVR/releases/latest) — [README Install](../README.md#install)

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

1. Download and unzip **`GEVR-Beta-vr456.1-win64.zip`** from [Latest](https://github.com/no6969el/GEVR/releases/latest) / [vr456.1](https://github.com/no6969el/GEVR/releases/tag/vr456.1). The zip has no ROM and no HD texture pack.
2. Headset: `Start-GEVR.bat`. Monitor / no headset: `Play-on-monitor.bat`.
3. Point at your USA `.z64`.
4. First prepare waits once while images land in `%LOCALAPPDATA%\\GEVR\\cache`. Then play.
5. Recenter in VR with **both thumbstick clicks**.

## First run vs updating

- **New install:** run `Start-GEVR.bat` (headset) or `Play-on-monitor.bat` (no headset), pick your USA `.z64`, wait once, play.
- **After a Beta update:** keep the same `.z64`. The ship stamp forces one re-prepare. **Saves are kept.** You do not delete the cache for a normal update.
- **Troubleshooting only:** run **`Clear-GEVR-cache.bat`** from the vr456.1 zip (type **YES**) to wipe **`%LOCALAPPDATA%\GEVR\cache`** only (keeps saves). If the picture still looks wrong, delete `%LOCALAPPDATA%\GEVR` and run the bat again (that also drops saves).
- **Half-speed / mushy VR:** SteamVR **Motion Smoothing Off**; Virtual Desktop **Space Warp Off** — see [Half-speed / mushy VR?](#half-speed--mushy-vr) above.

## Beta wear notes

- **Gunfire fixed ([#84](https://github.com/no6969el/GEVR/issues/84)):** rifle guards use correct rifle fire tables/cadence (not pistol lean/single-shot from a 64-bit weapon-prop misread).
- **Janus meeting:** the crowd stops respawning after the meeting.
- **Throwables:** grenades, mines, plastique, and the covert modem show in your hand and leave from the grip. Remote, proximity, and timed mines draw in the hand like the grenade.
- **Black flicker ([#55](https://github.com/no6969el/GEVR/issues/55)):** quiet for now. Stuck mines (including Facility) use the same no-modem scrap hide as the covert modem, so people can play. Props still pass through other props; that overlap is the cause.
- **Always on:** ammo digits, the hip holster, weapon pictures, and chest reload stay on without boot knobs.
- **Ledge:** shooting over a ledge no longer deflects down.
- **Ammo:** digits sit on the grip and read from behind the gun. Flat mode keeps the corner count.
- **Weapon change:** **Left X** is the previous weapon on the left hand. **Right A** is the next weapon on the right hand.
- **Hand cubes:** hide while that hand holds a weapon; smaller when empty.
- **Frame rate:** follows the headset by default. Fixed 90 is still available in **GEVR Settings**.
- **GEVR Settings:** on **Mission Select**, next to **Select Mission**, **Multiplayer**, and **Cheat Options**. It is not named Options. **A** selects a row. Stick left / right changes the value. **Apply** saves and relaunches. Prefs save under `%LOCALAPPDATA%\GEVR`.
- **Watch:** **Y** opens it. **GAME OPTIONS** goes past ratio. The last line says scroll down for VR settings. A cuff grab detonates planted remotes. Otherwise the watch laser comes from the cuff. There is no detonator in the weapon cycle. The **left stick** moves the watch highlight. **Tab** still pauses on the keyboard.
- **Reload:** **B** reloads any gun. Upper chest plus grab reloads. A visible magazine reloads with a grip. Pistol, shotgun, sniper, and other guns with no visible magazine reload across the chest or with **B**. A handle grab swaps hands and does not reload. Guns do not reload on their own. See [CONTROLS.md](CONTROLS.md#reload).
- **HD textures:** beta. They can stutter, including on a fast card. PNG packs go in `hdtextures\GOLDENEYE` next to `goldeneye.exe`. `GOLDENEYE_HIRESTEXTURES.hts` is the wrong file. Steps: [HD textures](GEVR-SETTINGS.md#hd-textures).
- **Hip holster:** grip to hold, release to holster. A new gun goes to the hip and the old gun goes to inventory. Empty guns stay in the hand. Grenades, mines, and gadgets still switch away when used up.
- **Sniper:** a green dot stays on. Shots leave the eye along that dot. Right stick forward or back steps the zoom (30, 20, 15, 10, 7). Walking does not zoom. The right-hand sniper hides the red crosshair. The left-hand green aimer is not in this build.
- **Swing:** uses the held weapon’s damage. Shooting does not make the knife swing by itself.
- **Update button:** the starter checks GitHub Latest on open. Click **Update** to pull a newer zip. Saves, settings, and your `.z64` stay put.
- **Auto-aim** starts off.
- **B** also covers switches, plant, and activate. **Menu** also opens the pause watch.
- **Tank:** stand on the chassis and you auto-mount. Stick pitch aims the shells.
- **Empty hand** draws a cube.
- **GL** is single-shot / muzzle feel OK.
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
- Aim and shoot (auto-aim starts off); **left trigger** fires a left-hand gun on its own
- Dual-wield with two guns (each trigger fires its hand)
- Press **B** and confirm it reloads any gun. Upper chest plus grab reloads. A visible magazine reloads with a grip. Pistol, shotgun, sniper, and other guns with no visible magazine reload across the chest or with **B**. A handle grab swaps hands and does not reload
- **Right A** goes to the next weapon on the right hand. **Left X** goes to the previous weapon on the left hand
- Throw a grenade. Remote, proximity, and timed mines should draw in the hand the same way
- Open the watch with **Y**. Open **GAME OPTIONS** and scroll past ratio. The last line says scroll down for VR settings
- Climb a tank by standing on the chassis; pitch the turret with the stick
- Grenade launcher: one shot per trigger, no self-blast
- Rockets stay on the gun, with a flat crosshair
- Far guards / characters stay readable
- Empty hand shows the cube; armed hand hides it
- Die / continue / load another mission in the same process (should stay clean)
- Explosions and sparks (mass blow-ups can still crash - keep the fault file)
- Dam blue flicker is probably the convert modem (known - issue #70; labels got mixed); stuck modem scrap should be quieter; Dam water look
- One-eye glass bullet holes
- Facility halls / guards
- Local split-screen on a monitor if you have a friend on the couch
- Note any crash: what map, what action, fault file yes/no
- If you run high Hz: note headset rate and whether anything feels off

Jump in and enjoy finally being Bond in GoldenEye VR.

Stay tuned. Star the repo and [follow @no6969el](https://github.com/no6969el).
