<p align="center">
  <img src="GEVR-box-cover.png" alt="GoldenEye 007 VR - GEVR box art" width="520" />
</p>

# GEVR - stand inside GoldenEye

**Native VR. Bring your own USA ROM. Beta is live.**

Not an emulator overlay. Not a flat game with a 3D wrapper. GEVR rebuilds GoldenEye on PC for real OpenXR stereo, 6DOF, and controller aim so you can actually *be* in the Facility.

**Latest:** [**GEVR Beta vr454**](https://github.com/no6969el/GEVR/releases/latest). Zip: **`GEVR-Beta-vr454-win64.zip`**. The zip has no ROM and no HD texture pack.

[VR actions](README.md#vr-actions) · [vr454 how-to](README.md#vr454) · [Install](README.md#install) · [vr454 tag](https://github.com/no6969el/GEVR/releases/tag/vr454) · [Credits](CREDITS.md)

---

## How to use vr454

The full how-to, one feature at a time, is on the [front page](README.md#vr454). Short version:

**GEVR Settings** is on **Mission Select**, next to **Select Mission**, **Multiplayer**, and **Cheat Options**. It is not named Options. **A** selects a row. Stick left or right changes the value. **Apply** saves and relaunches.

**Visual mode** is **VR**, **XR** (smaller screen, black outline), or **Flat** on the monitor. Each mode keeps the settings saved for it.

**Frame rate** follows the headset. **Fixed 90** is still available. **Supersample** starts at 3. **Filter** starts on bilinear. **Point** is still available. The monitor picture can be **Both**, **Left**, **Right**, or **Off**. Off blanks the desktop mirror while you stay in the headset.

**Left X** is the previous weapon on the left hand. **Right A** is the next weapon on the right hand.

**Hip holster:** grip to hold, release to holster. A new gun goes to the hip and the old gun goes to inventory. An empty gun stays in the hand. Grenades, mines, and gadgets still switch away when used up.

**Reload:** **B** plays the reload animation. A chest swipe or a grab on the magazine refills with a click and no animation. Pistols and guns with no magazine, including the shotgun, reload from the chest. Mag-on-top and mag-on-bottom guns, including the Uzi, reload from the magazine. A handle grab swaps hands and does not reload. Guns do not reload on their own.

A left-hand gun fires on its own. Ammo digits sit on the grip and read from behind the gun. Flat mode keeps the corner count. Weapon pictures sit on the lifting hand, including the grenade and the mines. Remote, proximity, and timed mines draw in the hand like the grenade.

A swing uses the held weapon’s damage. Shooting does not make the knife swing by itself. Bullet spread stays around the controller aim. Rockets, the grenade launcher, and the watch laser are unchanged. Rockets stay on the gun, with a flat crosshair.

**Sniper:** a green dot stays on. Shots leave the eye along that dot. Push the right stick forward or back to step the zoom (30, 20, 15, 10, 7). Walking does not zoom. The right-hand sniper hides the red crosshair. The left-hand green aimer is not in this build.

**Watch:** **Y** opens it. **GAME OPTIONS** goes past ratio, and the last line says to scroll down for VR settings. A cuff grab detonates planted remotes. Otherwise the watch laser comes from the cuff. There is no detonator in the weapon cycle. Watch magnet attract is still the cuff grab after you select it on the watch. Repel stays on the watch.

After the **Janus meeting**, the crowd stops respawning.

### HD textures

GEVR does not ship the pictures. [GoldenEye-007-HD releases](https://github.com/GhostlyDark/GoldenEye-007-HD/releases) · [evilgames GE007 HD](https://evilgames.eu/texture-packs/ge007-hd.htm). Put the PNG pack in **`hdtextures\GOLDENEYE`**, next to `goldeneye.exe`. **`GOLDENEYE_HIRESTEXTURES.hts`** is the wrong file. Turn **HD textures** on, then **Apply**. The pack loads on the next boot.

Hands and binds: [CONTROLS.md](docs/CONTROLS.md).

---

## On the box

What you can do in **vr454**:

- OpenXR VR. True stereo. Stand inside the room.
- Walk your playspace. Turn your head and the world stays put. Recenter with **both thumbstick clicks**.
- Point the controller to aim. Squeeze to aim down the gun. The mark sits on the gun, not on your face.
- **Right trigger** fires the right-hand gun. **Left trigger** fires a left-hand gun on its own.
- **Left X** previous weapon on the left hand. **Right A** next weapon on the right hand.
- Grip to hold a gun. Release to holster it. **B** plays the reload animation. A chest swipe or a magazine grab refills with a click.
- While aiming, walk on the left stick. Duck or stand on the right stick. With the sniper, the right stick steps the zoom, and walking does not zoom.
- Press **Y** to open the watch. Scroll **GAME OPTIONS** past ratio for VR settings.
- Throwables show in the lifting hand, including the grenade and the mines.
- A swing uses the weapon you are holding.
- Rockets stay on the gun, with a flat crosshair.
- Ammo digits sit on the grip. Flat mode keeps the corner count.
- An empty hand shows a cube. The cube hides while that hand holds a weapon.
- Stand on a tank to mount it. The right stick pitches the shells.
- **GEVR Settings** on Mission Select. **Update** in GevrRomStarter.
- Bring your own USA ROM. Flat play with `Play-on-monitor.bat` or the Flat visual mode.
- After the Janus meeting, the crowd stops respawning.

---

## The VR stuff that makes it feel like yours

**You are in the room**
Walk around your playspace and Bond walks with you. Turn your head and the world stays put. Recenter anytime with **both thumbstick clicks**.

**The gun is in your hand**
Point the controller to aim. **Right trigger** fires the right-hand gun. **Left trigger** fires the left-hand gun whenever that hand holds one. Squeeze to aim. The mark sits on the gun. While you aim, walk on the left stick and duck on the right. With two guns, each trigger fires its hand.

**Hands do Bond things**
Swing the weapon you are holding. Reach a door and grip to open it. Press **B** for the reload animation, or swipe your chest or grab the magazine for a silent refill. Grenades and mines show in the lifting hand.

**Tanks that let you in**
Stand on the chassis and you mount. Stick pitch aims the shells.

**Menus sit in the world**
**GEVR Settings** is on Mission Select, next to Select Mission, Multiplayer, and Cheat Options. In a mission, **Y** opens the watch, and **GAME OPTIONS** carries VR settings below ratio.

**It looks like GoldenEye, in stereo**
True per-eye VR. Pictures come from your ROM. We never ship the cart. An optional PNG pack goes in `hdtextures\GOLDENEYE` next to the exe.

**Then you play the campaign**
Facility and the rest, in OpenXR on PC.

---

## What we tested

| Path | Notes |
|------|--------|
| **Pimax Crystal Super + SteamVR OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR) (sboys3) | Primary wear path |
| **Native PimaxXR** | Verified attach / play |
| **Meta Quest 3 + Virtual Desktop OpenXR (VDXR)** | Verified attach / play |

---

## Play

1. Grab **[`GEVR-Beta-vr454-win64.zip`](https://github.com/no6969el/GEVR/releases/latest)**. No ROM and no HD texture pack in the archive.
2. Follow [README Install](README.md#install).
3. [VR actions](README.md#vr-actions) and [CONTROLS.md](docs/CONTROLS.md) for the full bind list.

Report bugs: [CONTRIBUTING.md](CONTRIBUTING.md). Do not upload your ROM.
