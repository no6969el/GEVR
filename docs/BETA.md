> **vr454:** GitHub **Latest**. Grab [vr454](https://github.com/no6969el/GEVR/releases/tag/vr454) or use Update in GevrRomStarter. The zip has no ROM and no HD texture pack.

# Beta testing guide

GEVR's public label is **Beta**. Expect crashes and unfinished corners. File them on Issues. We would rather hear from you than guess.

**Play this cut:** [**vr454**](https://github.com/no6969el/GEVR/releases/latest) (GitHub Latest). Zip: **`GEVR-Beta-vr454-win64.zip`**. Install: [README](../README.md#install). Tag: [vr454](https://github.com/no6969el/GEVR/releases/tag/vr454). Bring a USA GoldenEye ROM you own.

Older tag **pages** stay for history. **Latest is vr454.** Do not download from [vr420](https://github.com/no6969el/GEVR/releases/tag/vr420) / [vr434](https://github.com/no6969el/GEVR/releases/tag/vr434) / [vr438](https://github.com/no6969el/GEVR/releases/tag/vr438) / [vr439](https://github.com/no6969el/GEVR/releases/tag/vr439) / [vr440](https://github.com/no6969el/GEVR/releases/tag/vr440) / [vr441](https://github.com/no6969el/GEVR/releases/tag/vr441).

- **vr434** was pulled. ROM images were baked into `goldeneye.exe`.
- **vr443** zip was pulled (HOLD) then superseded by vr443.1 (motion KEEP not baked in), then vr444.
- **vr441** / **vr440** tag pages stay. Their **zips were stripped** when later cuts shipped.
- **vr439** zip removed when vr440 shipped. Tag page stays for record.

Player door: [00-START-HERE.md](00-START-HERE.md). Install: [README](../README.md#install). Hands: [CONTROLS.md](CONTROLS.md). Pitch: [FEATURES.md](../FEATURES.md). How to report: [CONTRIBUTING.md](../CONTRIBUTING.md). License map: [LICENSE-MAP.md](../LICENSE-MAP.md).

## Before you start

- A **legal** USA GoldenEye ROM you already own (we do not supply one)
- Windows PC
- Optional: OpenXR headset. No headset? Use the monitor bat.
- Download: [**GEVR-Beta-vr454-win64.zip**](https://github.com/no6969el/GEVR/releases/latest) — [README Install](../README.md#install). No ROM and no HD texture pack inside.

## Launchers

- **Headset:** `Start-GEVR.bat` (VR picture, supersample 3, sky / playspace)
- **Monitor / no headset:** `Play-on-monitor.bat` (VR off, no stereo eyes)

Use the bats. Do not double-click `goldeneye.exe`. Details: [CONTROLS.md](CONTROLS.md).

**Verified:** Pimax Crystal Super + SteamVR OpenXR via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR), native **PimaxXR**, **Quest 3 + Virtual Desktop OpenXR (VDXR)**.

**Hz:** The game follows your headset refresh (72 / 80 / 90 / 120 as reported). High Hz is still Beta-test territory - try it and report if something feels off. We do not call every high-Hz path signed off yet ([issue #49](https://github.com/no6969el/GEVR/issues/49)).

### Half-speed / mushy VR?

Turn off runtime motion smoothing before blaming Hertz.

- **SteamVR:** Settings → Video → **Motion Smoothing = Off** (also check Applications → GEVR / `goldeneye.exe`).
- **Virtual Desktop:** **Space Warp = Off**.

SteamVR Motion Smoothing and Virtual Desktop Space Warp can make the game feel half-speed. Turn those off in the runtime; this is not a GEVR menu toggle.

## Install and run

1. Download and unzip **`GEVR-Beta-vr454-win64.zip`** from [Latest](https://github.com/no6969el/GEVR/releases/latest) / [vr454](https://github.com/no6969el/GEVR/releases/tag/vr454).
2. Headset: `Start-GEVR.bat`. Monitor / no headset: `Play-on-monitor.bat`.
3. Point at your USA `.z64`.
4. First prepare waits once while images land in `%LOCALAPPDATA%\\GEVR\\cache`. Then play.
5. Recenter in VR with **both thumbstick clicks**.

## First run vs updating

- **New install:** run `Start-GEVR.bat` (headset) or `Play-on-monitor.bat` (no headset), pick your USA `.z64`, wait once, play.
- **After a Beta update:** keep the same `.z64`. The ship stamp forces one re-prepare. **Saves are kept.** You do not delete the cache for a normal update.
- **Troubleshooting only:** run **`Clear-GEVR-cache.bat`** from the vr454 zip (type **YES**) to wipe **`%LOCALAPPDATA%\GEVR\cache`** only (keeps saves). If the picture still looks wrong, delete `%LOCALAPPDATA%\GEVR` and run the bat again (that also drops saves).
- **Half-speed / mushy VR:** SteamVR **Motion Smoothing Off**; Virtual Desktop **Space Warp Off** — see [Half-speed / mushy VR?](#half-speed--mushy-vr) above.

## Beta wear notes

- **Gunfire ([#84](https://github.com/no6969el/GEVR/issues/84)):** rifle guards use rifle fire.
- **Janus meeting ([#82](https://github.com/no6969el/GEVR/issues/82)):** after the meeting, the crowd stops respawning.
- **Throwables:** the grenade, remote mines, proximity mines, and timed mines draw in the hand. The weapon picture sits on the lifting hand. Plastique and the covert modem still show in the hand.
- **Black flicker ([#55](https://github.com/no6969el/GEVR/issues/55)):** quiet for now. Stuck mines (including Facility) stay hidden the same way as covert-modem scrap, so people can play. Props can still pass through other props.
- **Ammo:** digits sit on the grip and read from behind the gun. Flat mode keeps the count in the corner.
- **Weapon change:** **Right A** is the next weapon on the right hand. **Left X** is the previous weapon on the left hand.
- **Hip holster:** grip to hold, release to holster. A new gun goes to the hip and the old gun goes to inventory. Empty guns stay in the hand. Grenades, mines, and gadgets still switch away when used up.
- **Hand cubes:** hide while that hand holds a weapon. An empty hand still draws a cube.
- **Frame rate:** follows the headset. Fixed 90 is still available.
- **GEVR Settings:** on **Mission Select**, next to Select Mission, Multiplayer, and Cheat Options. It is not named Options. **Apply** saves and relaunches. Prefs stay under `%LOCALAPPDATA%\GEVR`.
- **Watch:** **Y** opens it. **GAME OPTIONS** goes past ratio. The last line says to scroll down for VR settings. A cuff grab detonates planted remotes. Otherwise the watch laser comes from the cuff. There is no detonator in the weapon cycle.
- **Reload:** **B** plays the reload animation. A chest swipe or a magazine grab refills with a click and no animation. Pistols and guns with no magazine, including the shotgun, reload from the chest. Mag-on-top and mag-on-bottom guns, including the Uzi, reload from the magazine. A handle grab swaps hands and does not reload. Guns do not reload on their own. See [CONTROLS.md](CONTROLS.md#reload).
- **Update button:** the starter checks GitHub Latest when it opens. Click **Update** to pull a newer zip. Saves, settings, and your `.z64` stay put.
- **Auto-Aim** defaults off.
- **Pause watch:** the **left stick** moves the highlight.
- **B** plays the reload animation, and it still plants and activates where GoldenEye uses that button. **Tab** on the keyboard still opens the watch.
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
- Aim and shoot (Auto-Aim should default OFF); **left trigger** fires a left-hand gun on its own
- Dual-wield with two guns (each trigger fires its hand)
- Reload: **B** plays the animation. A chest swipe or a magazine grab refills with a click. A handle grab swaps hands and does not reload.
- **Right A** is the next weapon on the right hand. **Left X** is the previous weapon on the left hand.
- Grip a gun to hold it. Release to holster it. An empty gun stays in the hand.
- Throw a grenade or a mine. Remote, proximity, and timed mines should draw in the hand like the grenade.
- Sniper: the green dot stays on. Right stick forward or back steps 30, 20, 15, 10, 7. Walking does not zoom. The right-hand sniper hides the red crosshair.
- Press **Y** to open the watch. Scroll **GAME OPTIONS** past ratio. The last line says to scroll down for VR settings. A cuff grab detonates planted remotes, otherwise the laser comes from the cuff.
- Climb a tank by standing on the chassis; pitch the turret with the stick
- Grenade launcher: one shot per trigger, no self-blast
- Rockets stay on the gun, with a flat crosshair. Spread on normal guns stays around the controller aim.
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
