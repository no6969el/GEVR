<p align="center">
  <img src="GEVR-box-cover.png" alt="GoldenEye 007 VR - GEVR box art" width="520" />
</p>

# GEVR - stand inside GoldenEye

**Native VR. Bring your own ROM. Beta is live.**

Not an emulator overlay. Not a flat game with a 3D wrapper. GEVR rebuilds GoldenEye on PC for real OpenXR stereo, 6DOF, and controller aim so you can actually *be* in the Facility.

**Play this cut:** [**GEVR Beta vr439**](https://github.com/no6969el/GEVR/releases/tag/vr439) (GitHub Latest). Only this tag has a zip.

[README](README.md) | [Beta notes](docs/BETA.md) | [Controls](docs/CONTROLS.md) | [Roadmap](docs/ROADMAP.md) | [Credits](CREDITS.md)

---

## The VR stuff that makes it feel like yours

**You are in the room**
Walk around your playspace and Bond walks with you. Turn your head - the world stays put. Recenter anytime with **both thumbstick clicks**.

**The gun is in your hand**
Point the controller to aim. Trigger fires. Squeeze to ADS - the mark sits on the gun ray, not glued to your face. Casings leave the weapon. Haptics pulse when a round actually goes off.

**Hands do Bond things**
Punch / melee with your hands. Touch to use (doors, interact) by reaching instead of hunting a 2D prompt.

**Cinema that stays in the world**
Menus and intro cinema sit on a screen in a small hub room. Look left and right - the screen stays nailed in space. You are not wearing a billboard on your face.

**It looks like GoldenEye, in stereo**
True per-eye VR. Explosions and fire color. Intro gunbarrel drip. Title walk backdrop. Images come from *your* ROM. We never ship the cart.

**Then you play the campaign**
Facility and friends, OpenXR on PC. Mission Report / NEXT actually takes input after a stage clear. HUD and on-screen text pulled in off the HMD rim so you can read it.

---

## What we tested (vr439)

These paths are what this Beta was built and worn on:

| Path | Notes |
|------|--------|
| **Pimax Crystal Super + SteamVR OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR) (sboys3) | Primary wear path. We do not maintain that driver. We do support this experience. |
| **Native PimaxXR** | Verified attach / play |
| **Meta Quest 3 + Virtual Desktop OpenXR** | Verified attach / play |

**Refresh rates:** 72 Hz, 80 Hz, and **90 Hz** should work. Headset default is **90**. Anything **over 90** (120 / 144 and friends) is still beta-test territory. Try it, and [file an Issue](https://github.com/no6969el/GEVR/issues/new/choose) if something feels off.

When you report a bug or crash, please include: **headset**, **OpenXR runtime**, **SteamVR on/off**, **HMD vs monitor**, and whether you used **`Start-GEVR.bat`**. Do not upload your ROM.

---

## Honest Beta notes

- Crashes and rough edges are expected. That is why it is Beta.
- You bring a **USA GoldenEye `.z64` you own**. No ROM in the download.
- **Headset:** `Start-GEVR.bat` (KEEP picture: XR stereo source, SrcFbo, supersample 3, sky / playspace). **Monitor / no headset:** `Play-on-monitor.bat`.
- First launch prepares images once into `%LOCALAPPDATA%\GEVR\cache`. A new zip rebuilds that cache once via a ship stamp. Troubleshooting only: delete that cache folder.
- **vr438** was BYO-ROM with a stub VR boot. It looked like an old build. Use [vr439](https://github.com/no6969el/GEVR/releases/tag/vr439).
- **vr434** was pulled. ROM images were baked into `goldeneye.exe`.
- **Dam crates** can still pop in. **Dam water** can look murky. **Glass bullet holes** can show in one eye.
- **Local split-screen multiplayer** still works on a monitor. A **LAN / same-network add-on** is later. Online is later than that.
- Full colocated Bond body and a fancier hub room are later. See the [roadmap](docs/ROADMAP.md).

---

## Start

1. Grab the [vr439 zip](https://github.com/no6969el/GEVR/releases/tag/vr439). No ROM in the archive.
2. Unzip. **Headset:** `Start-GEVR.bat`. **Monitor / no headset:** `Play-on-monitor.bat`.
3. Point at your **USA `.z64`**. First prepare can take a bit. Later launches with the same zip are fast.
4. Headset on. Recenter (both sticks). Enjoy.

[How to play / recenter](docs/CONTROLS.md) - [Beta testing](docs/BETA.md) - [Report a bug](https://github.com/no6969el/GEVR/issues/new/choose) - [Who we credit](CREDITS.md)
