# Features (current Beta)

> Player snapshot: [FEATURES.md](../FEATURES.md). Play [vr456.1](https://github.com/no6969el/GEVR/releases/tag/vr456.1) (GitHub Latest). Install: [README](../README.md#install). How to play: [Start here](00-START-HERE.md).

Current zip: **[`GEVR-Beta-vr456.1-win64.zip`](https://github.com/no6969el/GEVR/releases/download/vr456.1/GEVR-Beta-vr456.1-win64.zip)**. Tag: [vr456.1](https://github.com/no6969el/GEVR/releases/tag/vr456.1). The zip has no ROM and no HD texture pack.

## vr456.1

- **Visual mode** — VR, XR (smaller screen, black outline), or Flat on the monitor. Change the row in **GEVR Settings** and **Apply**. Apply saves and relaunches into that mode.
- **Frame rate** — follows the headset by default. Fixed 90 is still available.
- **Supersample** starts at 3. **Filter** starts on bilinear. Point is still available.
- **Monitor** — Both, Left, Right, or Off. Off blanks the mirror while you stay in the headset.
- **GEVR Settings** — on Mission Select, next to Select Mission, Multiplayer, and Cheat Options. It is not named Options.
- **Always on** — ammo digits, the hip holster, weapon pictures, and chest reload stay on without boot knobs.
- **Ledge** — shooting over a ledge no longer deflects down.
- **Weapons** — Left X is the previous weapon on the left hand. Right A is the next weapon on the right hand.
- **Hip holster** — grip to hold, release to holster. A new gun goes to the hip and the old gun goes to inventory. Empty guns stay in the hand. Grenades, mines, and gadgets still switch away when used up.
- **Reload** — B reloads any gun. Upper chest plus grab reloads. A visible magazine reloads with a grip. Pistol, shotgun, sniper, and other guns with no visible magazine reload across the chest or with B. A handle grab swaps hands and does not reload. Guns do not reload on their own.
- **Left hand** — a left-hand gun fires on its own.
- **Ammo** — digits sit on the grip and read from behind the gun. Flat mode keeps the corner count. Weapon pictures sit on the lifting hand, including the grenade and mines.
- **Mines** — remote, proximity, and timed mines draw in the hand like the grenade.
- **Swing** — uses the held weapon’s damage. Shooting does not make the knife swing by itself.
- **Spread** — stays around the controller aim. Rockets, the grenade launcher, and the watch laser are unchanged.
- **Rockets** — stay on the gun, with a flat crosshair.
- **Sniper** — a green dot stays on. Shots leave the eye along that dot. Right stick forward or back steps the zoom (30, 20, 15, 10, 7). Walking does not zoom. The right-hand sniper hides the red crosshair. The left-hand green aimer is not in this build.
- **Watch** — Y opens it. GAME OPTIONS goes past ratio. The last line says scroll down for VR settings. A cuff grab detonates planted remotes, otherwise the watch laser comes from the cuff. There is no detonator in the weapon cycle.
- **Janus meeting** — the crowd stops respawning after the meeting.
- **HD textures** — beta. They can stutter, including on a fast card. PNG packs go in `hdtextures\GOLDENEYE` next to `goldeneye.exe`. `GOLDENEYE_HIRESTEXTURES.hts` is the wrong file. The zip has no pack. Steps: [HD textures](GEVR-SETTINGS.md#hd-textures).

## Still in this cut

- OpenXR stereo, room-scale walk, recenter on both stick clicks, grip to open doors
- Aim along the gun, tank mount, bring your own USA ROM
- GevrRomStarter **Update** follows GitHub Latest

## Headset / runtime

Pimax (SteamVR OpenXR + CustomHeadsetOpenVR), native PimaxXR, Quest 3 + Virtual Desktop — see [FEATURES](../FEATURES.md#what-we-tested).

Controls: [CONTROLS.md](CONTROLS.md). Beta notes: [BETA.md](BETA.md).
