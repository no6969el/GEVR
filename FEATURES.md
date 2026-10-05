<p align="center">
  <img src="GEVR-box-cover.png" alt="GoldenEye 007 VR - GEVR box art" width="520" />
</p>

# GEVR - stand inside GoldenEye

**Native VR. Bring your own ROM. Beta is live.**

GEVR rebuilds GoldenEye on PC for real OpenXR stereo, so you can stand in the Facility. You bring a USA GoldenEye ROM you own. The zip has no ROM and no HD texture pack.

**Latest:** [**GEVR Beta vr456.1**](https://github.com/no6969el/GEVR/releases/latest). Zip: **`GEVR-Beta-vr456.1-win64.zip`**.

[Install](README.md#install) · [How to play](docs/00-START-HERE.md) · [Controls](docs/CONTROLS.md) · [vr456.1](https://github.com/no6969el/GEVR/releases/tag/vr456.1) · [Credits](CREDITS.md)

How to play is on [Start here](docs/00-START-HERE.md). Buttons are on [Controls](docs/CONTROLS.md). This page is the short pitch.

---

## What you do in vr456.1

**GEVR Settings** is on **Mission Select**, next to **Select Mission**, **Multiplayer**, and **Cheat Options**. It is not named Options. Change a row, then **Apply**. Apply saves and relaunches into that mode.

- **Visual mode:** **VR**, **XR** (smaller screen, black outline), or **Flat** on the monitor.
- **Frame rate** follows the headset. **Fixed 90** is still available.
- **Supersample** starts at 3. **Filter** starts on bilinear. **Point** is still available.
- **Monitor:** **Both**, **Left**, **Right**, or **Off**. Off blanks the mirror while you stay in the headset.
- Ammo digits, the hip holster, weapon pictures, and chest reload stay on without boot knobs. Shooting over a ledge no longer deflects down.
- **Left X** is the previous weapon on the left hand. **Right A** is the next weapon on the right hand.
- Grip holds a gun. Release holsters it. A new gun goes to the hip, and the old gun goes to inventory. Empty guns stay in the hand. Grenades, mines, and gadgets still switch away when used up.
- **B** reloads any gun. Upper chest plus grab reloads. A visible magazine reloads with a grip. Pistol, shotgun, sniper, and other guns with no visible magazine reload across the chest or with **B**. A handle grab swaps hands and does not reload. Guns do not reload on their own.
- A left-hand gun fires on its own.
- Ammo digits sit on the grip and read from behind the gun. Flat mode keeps the corner count. Weapon pictures sit on the lifting hand, including the grenade and mines.
- Remote, proximity, and timed mines draw in the hand like the grenade.
- A swing uses the held weapon’s damage. Shooting does not make the knife swing by itself.
- Bullet spread stays around the controller aim. Rockets, the grenade launcher, and the watch laser are unchanged. Rockets stay on the gun, with a flat crosshair.
- Sniper: a green dot stays on. Shots leave the eye along that dot. Push the right stick forward or back to step the zoom (30, 20, 15, 10, 7). Walking does not zoom. The right-hand sniper hides the red crosshair. The left-hand green aimer is not in this build.
- **Y** opens the watch. **GAME OPTIONS** goes past ratio. The last line says scroll down for VR settings. A cuff grab detonates planted remotes. Otherwise the watch laser comes from the cuff. There is no detonator in the weapon cycle.
- After the Janus meeting, the crowd stops respawning.

### HD textures

HD textures are beta. They can stutter, including on a fast card. [GoldenEye-007-HD releases](https://github.com/GhostlyDark/GoldenEye-007-HD/releases) · [evilgames GE007 HD](https://evilgames.eu/texture-packs/ge007-hd.htm). Put the PNG pack in **`hdtextures\GOLDENEYE`** next to `goldeneye.exe`. `GOLDENEYE_HIRESTEXTURES.hts` is the wrong file. Turn HD textures **On**, then **Apply**. The pack loads on the next boot. Steps: [HD textures](docs/GEVR-SETTINGS.md#hd-textures).

Full sentences and the button tables: [How to play](docs/00-START-HERE.md) · [CONTROLS.md](docs/CONTROLS.md).

---

## On the box

- OpenXR VR. You stand in the room.
- Walk your playspace and Bond moves with you. Recenter with **both thumbstick clicks**.
- Point the controller to aim. Squeeze to aim down the gun. The **right trigger** fires the right hand. The **left trigger** fires a left-hand gun on its own.
- While you aim, walk on the left stick and crouch on the right stick.
- Grip a door to open or close it.
- Throwables leave from the hand.
- Stand on a tank to mount it. The stick pitches the cannon.
- The in-app **Update** button in GevrRomStarter follows GitHub Latest.
- Local split-screen on a monitor. Flat play uses `Play-on-monitor.bat`, or Visual mode **Flat**.

---

## The VR stuff that makes it feel like yours

**You are in the room.** Walk your playspace and Bond walks with you. Turn your head and the world stays put. Recenter anytime with **both thumbstick clicks**.

**The gun is in your hand.** Point the controller. **Right trigger** fires the right-hand gun. **Left trigger** fires the left-hand gun whenever that hand holds one. Squeeze to aim. The mark sits on the gun. With two guns, each trigger fires its own hand.

**Hands do Bond things.** A swing uses the weapon you are holding. B reloads any gun. Upper chest plus grab reloads. A visible magazine reloads with a grip. Mines and grenades show in the hand.

**Tanks that let you in.** Stand on the chassis and you mount. The stick pitches the shells.

**Menus stay in the world.** **GEVR Settings** is on Mission Select, next to Select Mission, Multiplayer, and Cheat Options. In a mission, **Y** opens the watch, and **GAME OPTIONS** carries the VR rows below ratio.

**It looks like GoldenEye, in stereo.** The pictures come from your ROM. HD textures are beta and can stutter, including on a fast card. A PNG pack goes in `hdtextures\GOLDENEYE` next to the exe.

---

## What we tested

| Path | Notes |
|------|--------|
| **Pimax Crystal Super + SteamVR OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR) (sboys3) | Primary wear path |
| **Native PimaxXR** | Verified attach / play |
| **Meta Quest 3 + Virtual Desktop OpenXR (VDXR)** | Verified attach / play |

---

## Play

1. Grab **[`GEVR-Beta-vr456.1-win64.zip`](https://github.com/no6969el/GEVR/releases/latest)**. The archive has no ROM and no HD texture pack.
2. Follow [README Install](README.md#install).
3. Use [How to play](docs/00-START-HERE.md) and [CONTROLS.md](docs/CONTROLS.md) for the binds.

Report bugs: [CONTRIBUTING.md](CONTRIBUTING.md). Do not upload your ROM.
