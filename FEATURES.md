<p align="center">
  <img src="GEVR-box-cover.png" alt="GoldenEye 007 VR - GEVR box art" width="520" />
</p>

# GEVR - stand inside GoldenEye

**Native VR. Bring your own ROM. Beta is live.**

GEVR rebuilds GoldenEye on PC for real OpenXR stereo, so you can stand in the Facility. You bring a USA GoldenEye ROM you own. The zip has no ROM and no HD texture pack.

**Latest:** [**GEVR Beta vr456.4**](https://github.com/no6969el/GEVR/releases/latest). Zip: **`GEVR-Beta-vr456.4-win64.zip`**.

[Install](README.md#install) · [VR actions](README.md#vr-actions) · [vr456.4](https://github.com/no6969el/GEVR/releases/tag/vr456.4) · [Credits](CREDITS.md)

The how-to for this cut is on the [README](README.md#vr4564). Hands: [docs/CONTROLS.md](docs/CONTROLS.md). This page is the short pitch.

---

## What you do in vr456.4

**GEVR Settings** is on **Mission Select**, next to **Select Mission**, **Multiplayer**, and **Cheat Options**. It is not named Options. Change a row, then **Apply**. Apply saves and relaunches into that mode.

- **Visual mode:** **VR**, **XR** (smaller screen, black outline), or **Flat** on the monitor.
- **Frame rate** follows the headset. **Fixed 90** is still available.
- **Supersample** starts at 3. **Filter** starts on bilinear. **Point** is still available.
- **Monitor:** **Both**, **Left**, **Right**, or **Off**. Off blanks the mirror while you stay in the headset.
- **Stick weapon wheel:** stick click opens a circle (NO WEAPON at 12 o'clock). Centre follows the hover. Boxes are 2x dark grey. **STICK WHEEL** can set Weapon Vert.
- **Left X** is the next weapon on the left hand. **Right A** is the next weapon on the right hand.
- **Holster swap:** same-gun hip grip is a real swap. Weapon switch prefers a free inventory copy over the hip gun.
- **Watch picker:** pictures and labels on the left cuff (Laser / Magnet / Repel). Magnet is unlimited in VR. Laser and Repel stay on the normal watch item flow.
- **Moonraker:** small circular scope lens only. Look through the ring. Shoot through the ring. Dual Moonrakers give two lenses. No front grill screen.
- **Rockets** stay locked to the launcher, not your head. Flat mouse-aim crosshair stays centred.
- **Snap-turn** is real degrees. Red and green **aimers** sit on the shot's first hit.
- **Left-hand throwables** draw the right way around.
- **Tank** shells auto-load after you fire.
- **VR comfort:** no walk bob, no landing dip, no gun-hand sway.
- **HD memo** keeps decoded HD pictures in memory (`GETV_HD_MEMO_MB=0` turns it off).
- **XR catch-up:** missed headset frames no longer slow the sim. Quitting actually quits.
- Reload guns with the gesture (magazine or chest cross). **B** is USE, not VR gun reload.
- A left-hand gun fires on its own.
- Ammo digits sit on the grip and read from behind the gun. Flat mode keeps the corner count. Weapon pictures sit on the lifting hand.
- Remote, proximity, and timed mines draw in the hand like the grenade.
- A swing uses the held weapon's damage. Shooting does not make the knife swing by itself.
- Sniper: a green dot stays on. Right stick forward or back steps the zoom (30, 20, 15, 10, 7).
- **Y** opens the watch. **GAME OPTIONS** goes past ratio. Scroll down for VR settings.
- After the Janus meeting, the crowd stops respawning.

### HD textures

**GEVR does not ship the pictures.** [GoldenEye-007-HD releases](https://github.com/GhostlyDark/GoldenEye-007-HD/releases) · [evilgames GE007 HD](https://evilgames.eu/texture-packs/ge007-hd.htm): a **GLideN64 PNG** zip, not `.hts`. Put the pack in **`hdtextures\GOLDENEYE`** next to `goldeneye.exe`. `GOLDENEYE_HIRESTEXTURES.hts` is the wrong file. Turn HD textures **On**, then **Apply**. The pack loads on the next boot.

Full sentences and the button tables: [README](README.md#vr4564) · [CONTROLS.md](docs/CONTROLS.md).

---

## On the box

- OpenXR VR. You stand in the room.
- Walk your playspace and Bond moves with you. Recenter with **both thumbstick clicks**.
- Point the controller to aim. Squeeze to aim down the gun. The **right trigger** fires the right hand. The **left trigger** fires a left-hand gun on its own.
- Stick click opens the weapon wheel. Hip holster swap. Watch picker on the cuff.
- While you aim, walk on the left stick and crouch on the right stick.
- Grip a door to open or close it.
- Throwables leave from the hand.
- Stand on a tank to mount it. The stick pitches the cannon. Empty mag auto-loads the next shell.
- The in-app **Update** button in GevrRomStarter follows GitHub Latest.
- Local split-screen on a monitor. Flat play uses `Play-on-monitor.bat`, or Visual mode **Flat**.
- Not in this zip: 0085 thermal, 0086 corpse freeze, Gun Drop / Arm Bounds default-on.

---

## The VR stuff that makes it feel like yours

**You are in the room.** Walk your playspace and Bond walks with you. Turn your head and the world stays put. Recenter anytime with **both thumbstick clicks**. No walk bob, no landing dip, no extra gun-hand sway.

**The gun is in your hand.** Point the controller. **Right trigger** fires the right-hand gun. **Left trigger** fires the left-hand gun whenever that hand holds one. Squeeze to aim. The mark sits on the gun. With two guns, each trigger fires its own hand.

**Hands do Bond things.** A swing uses the weapon you are holding. Reload with the magazine or chest-cross gesture. Mines and grenades show in the hand. Stick click opens the wheel.

**Tanks that let you in.** Stand on the chassis and you mount. The stick pitches the shells. The next round auto-loads.

**Menus stay in the world.** **GEVR Settings** is on Mission Select, next to Select Mission, Multiplayer, and Cheat Options. In a mission, **Y** opens the watch, and **GAME OPTIONS** carries the VR rows below ratio.

**It looks like GoldenEye, in stereo.** The pictures come from your ROM. An optional PNG pack goes in `hdtextures\GOLDENEYE` next to the exe.

---

## What we tested

| Path | Notes |
|------|--------|
| **Pimax Crystal Super + SteamVR OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR) (sboys3) | Primary wear path |
| **Native PimaxXR** | Verified attach / play |
| **Meta Quest 3 + Virtual Desktop OpenXR (VDXR)** | Verified attach / play |

---

## Play

1. Grab **[`GEVR-Beta-vr456.4-win64.zip`](https://github.com/no6969el/GEVR/releases/latest)**. The archive has no ROM and no HD texture pack.
2. Follow [README Install](README.md#install).
3. [VR actions](README.md#vr-actions) and [CONTROLS.md](docs/CONTROLS.md) for the full bind list.

Report bugs: [CONTRIBUTING.md](CONTRIBUTING.md). Do not upload your ROM.
