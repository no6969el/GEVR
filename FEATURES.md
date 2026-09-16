<p align="center">
  <img src="GEVR-box-cover.png" alt="GoldenEye 007 VR - GEVR box art" width="520" />
</p>

# GEVR - stand inside GoldenEye

**Native VR. Bring your own ROM. Beta is live.**

Not an emulator overlay. Not a flat game with a 3D wrapper. GEVR rebuilds GoldenEye on PC for real OpenXR stereo, 6DOF, and controller aim so you can actually *be* in the Facility.

**Latest playable cut:** [**GEVR Beta vr438**](https://github.com/no6969el/GEVR/releases/tag/vr438) - public Beta (BYO-ROM, file-backed images from your cart).

[Play the Beta](https://github.com/no6969el/GEVR/releases/tag/vr438) | [Controls](docs/CONTROLS.md) | [Credits](CREDITS.md) | [Roadmap](docs/ROADMAP.md)

---

## The VR stuff that makes it feel like yours

**You are in the room**
Walk around your playspace and Bond walks with you. Turn your head - the world stays put. Recenter anytime with **both thumbstick clicks**. (This cut includes the playspace comfort pass so straying off your reset spot does not shear the gun and world when you look around.)

**The gun is in your hand**
Point the controller to aim. Trigger fires. Squeeze to ADS - the mark sits on the gun ray, not glued to your face. Casings leave the weapon. Haptics pulse when a round actually goes off.

**Hands do Bond things**
Punch / melee with your hands. Touch to use (doors, interact) by reaching instead of hunting a 2D prompt.

**Cinema that stays in the world**
Menus and intro cinema sit on a screen in a small hub room. Look left and right - the screen stays nailed in space; you are not wearing a billboard on your face.

**It looks like GoldenEye, in stereo**
True per-eye VR. Explosions and fire color. Intro gunbarrel drip. Title walk backdrop. File-backed images from *your* ROM (we never ship the cart).

**Then you play the campaign**
Facility and friends, OpenXR on PC. Mission Report / NEXT actually takes input after a stage clear. HUD and on-screen text pulled in off the HMD rim so you can read it.

---

## What we tested (vr438)

These paths are what this Beta was built and stared on:

| Path | Notes |
|------|--------|
| **Pimax Crystal Super + SteamVR OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR) (sboys3) | Primary wear path - we do not maintain that driver; we *do* support this experience |
| **Native PimaxXR** | Verified attach / play |
| **Meta Quest 3 + Virtual Desktop OpenXR** | Verified attach / play |

**Refresh rates:** 72 Hz, 80 Hz, and **90 Hz** should work. This zip defaults to **90**. Anything **over 90** (120 / 144 and friends) is still beta-test territory - try it, and [file an Issue](https://github.com/no6969el/GEVR/issues/new/choose) if something feels off.

When you report a bug or crash, please include: **headset**, **OpenXR runtime**, **SteamVR on/off**, **HMD vs monitor**, and whether you used **`Start-GEVR.bat`**.

---

## Honest Beta notes

- Crashes and rough edges are expected. That is why it is Beta.
- You bring a **USA GoldenEye `.z64` you own**. No ROM in the download. Run **`Start-GEVR.bat`** so **GevrRomStarter** can bind your ROM (not bare `goldeneye.exe`).
- **vr434 was pulled** on 2026-09-16 - that build linked image data into `goldeneye.exe` and could boot without a ROM. Use **[vr438](https://github.com/no6969el/GEVR/releases/tag/vr438)**.
- The zip includes **`glew32.dll`** and the other runtime DLLs Windows needs.
- **Dam crates** can still pop in and out; **Dam water** can look flat or murky; **glass bullet holes** can show in one eye in places.
- On a **flat / monitor** setup, classic **local split-screen multiplayer** is still there. The next multiplayer step we are aiming for is a **LAN / local-network add-on**; true online play is further out after that.
- Full colocated Bond body and a fancier hub room are later - see the [roadmap](docs/ROADMAP.md).

---

## Start

1. Grab the [vr438 Release zip](https://github.com/no6969el/GEVR/releases/tag/vr438) (no ROM in the archive).
2. Unzip. Run **`Start-GEVR.bat`** (**GevrRomStarter** - point at your USA `.z64`; the bat also locks in sharper VR with supersample 3 and the SrcFbo path, plus stereo / view-restore knobs that help eyes fuse).
3. Drop in your **USA `.z64`** when the starter asks.
4. Headset on. Recenter (both sticks). Enjoy.

[How to play / recenter](docs/CONTROLS.md) - [Report a bug](https://github.com/no6969el/GEVR/issues/new/choose) - [Who we credit](CREDITS.md)
