# Features (current Beta)

> Player snapshot: [FEATURES.md](../FEATURES.md). Play [vr454](https://github.com/no6969el/GEVR/releases/latest) (GitHub Latest). How to do each part: [README vr454](../README.md#vr454).

Current zip: **[`GEVR-Beta-vr454-win64.zip`](https://github.com/no6969el/GEVR/releases/download/vr454/GEVR-Beta-vr454-win64.zip)**. The zip has no ROM and no HD texture pack. Tag: [vr454](https://github.com/no6969el/GEVR/releases/tag/vr454).

## vr454

- **Visual modes** — VR, XR (smaller screen, black outline), or Flat on the monitor. Change the row in **GEVR Settings** and **Apply**. Apply saves and relaunches into that mode.
- **Frame rate** — follows the headset. Fixed 90 is still available.
- **Supersample** starts at 3. **Filter** starts on bilinear. Point is still available.
- **Monitor picture** — Both, Left, Right, or Off. Off blanks the desktop mirror while you stay in the headset.
- **Weapons** — Left X is the previous weapon on the left hand. Right A is the next weapon on the right hand.
- **Hip holster** — grip to hold, release to holster. A new gun goes to the hip and the old gun goes to inventory. Empty guns stay in the hand. Grenades, mines, and gadgets still switch away when used up.
- **Reload** — B plays the reload animation. A chest swipe or a magazine grab refills with a click and no animation. Pistols and guns with no magazine, including the shotgun, reload from the chest. Mag-on-top and mag-on-bottom guns, including the Uzi, reload from the magazine.
- **Handle grab** swaps hands and does not reload. Guns do not reload on their own.
- **Left-hand gun** fires on its own.
- **Ammo digits** sit on the grip and read from behind the gun. Flat mode keeps the corner count.
- **Weapon pictures** sit on the lifting hand, including the grenade and the mines.
- **Mines** — remote, proximity, and timed mines draw in the hand like the grenade.
- **Swing** uses the held weapon’s damage. Shooting does not make the knife swing by itself.
- **Bullet spread** stays around the controller aim. Rockets, the grenade launcher, and the watch laser are unchanged.
- **Rockets** stay on the gun, with a flat crosshair.
- **Sniper** — a green dot stays on. Shots leave the eye along that dot. Right stick forward or back steps the zoom (30, 20, 15, 10, 7). Walking does not zoom. The right-hand sniper hides the red crosshair. The left-hand green aimer is not in this build.
- **Watch** — Y opens it. GAME OPTIONS goes past ratio, and the last line says to scroll down for VR settings. A cuff grab detonates planted remotes. Otherwise the watch laser comes from the cuff. There is no detonator in the weapon cycle.
- **Janus meeting** — the crowd stops respawning after the meeting.
- **GEVR Settings** is on Mission Select, next to Select Mission, Multiplayer, and Cheat Options. It is not named Options.
- **HD textures** — PNG pack in `hdtextures\GOLDENEYE` next to `goldeneye.exe`. `GOLDENEYE_HIRESTEXTURES.hts` is the wrong file. GEVR does not ship the pack. [Pack releases](https://github.com/GhostlyDark/GoldenEye-007-HD/releases) / [evilgames page](https://evilgames.eu/texture-packs/ge007-hd.htm).

## Still in this line

- OpenXR stereo, 6DOF, controller aim, aim on the gun, per-hand triggers
- Playspace and recenter (both stick clicks), grip doors, tank mount
- Bring your own USA ROM. Saves stay under `%LOCALAPPDATA%\GEVR`.
- Watch magnet attract from the cuff after you select it on the pause watch. Repel stays on the watch.

## Headset / runtime

Pimax (SteamVR OpenXR + CustomHeadsetOpenVR), native PimaxXR, Quest 3 + VDXR — see [README](../README.md#what-we-tested).

Controls: [CONTROLS.md](CONTROLS.md). Beta quirks: [BETA.md](BETA.md).
