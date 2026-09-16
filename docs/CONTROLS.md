# Controls (Beta)

How to move, aim, and reset your position in [GEVR Beta vr439](https://github.com/no6969el/GEVR/releases/tag/vr439).

Play steps: [README](../README.md). Tester notes: [BETA.md](BETA.md). Pitch: [FEATURES.md](../FEATURES.md). What is next: [ROADMAP.md](ROADMAP.md).

## Which bat

- **Headset:** `Start-GEVR.bat` - KEEP VR picture (XR stereo source, SrcFbo, supersample 3, sky / playspace) plus recenter / stick-turn.
- **Monitor / no headset:** `Play-on-monitor.bat` - VR off, no stereo eyes. This is also the path for **local split-screen**.

Use those bats from the vr439 zip. Do not double-click `goldeneye.exe`. Bare exe can skip the ROM cache update and leave VR input off.

## Reset position (recenter)

When things feel offset, or after you move your playspace setup:

**Click both thumbsticks at the same time** (press both sticks in like L3+R3).

Also works:

- **Xbox pad:** L3 + R3 together
- **Keyboard:** `Home` while the game window has focus

One stick click alone does nothing. This is the same recenter the game uses when you enter gameplay from the cinema / menu.

After recenter, standing still and turning your head should not slide the world. Walking in your room should move you in Bond-world.

## Move and look

| Input | What it does |
|---|---|
| **Left stick** | Walk |
| **Right stick** | Turn |
| **Head / 6DOF** | Look around; move in the playspace to translate in-world |
| **Controllers** | Gun aim follows the controller |

## Fire and aim

| Input | What it does |
|---|---|
| **Trigger** | Fire |
| **Squeeze / grip** | ADS / aim mark on the gun ray (not stuck in face centre) |

Face buttons (A/B style) are only partly wired in this Beta cut. Menu / folder navigation is more reliable with the stick and trigger path. If a face button does nothing, that is a known gap, not you.

## Cinema / menus

While the flat cinema or frontend menus are up, you are in a small hub room looking at a **world-locked** screen. Turn your head and the screen stays put in the room.

## Getting VR working

GEVR uses **OpenXR**. Which runtime Windows hands us matters.

**Verified on vr439:**

- **Pimax Crystal Super + SteamVR OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR) (sboys3). We do not maintain that driver. We do support this experience.
- **Native PimaxXR**
- **Quest 3 + Virtual Desktop OpenXR**

**Hz:** 72 / 80 / **90** should work. The headset bat defaults to **90**. Over 90 is still beta-test territory. Try it and [file an Issue](https://github.com/no6969el/GEVR/issues/new/choose) if it feels off.

**Practical recipe:** unzip vr439, run **`Start-GEVR.bat`**, point at your USA `.z64`, put the headset on, recenter with both stick clicks.

Native Quest (standalone APK) is a later port, not this PC zip.

### If controls or VR feel dead

1. Launch with **`Start-GEVR.bat`** (headset) or **`Play-on-monitor.bat`** (flat), not bare `goldeneye.exe`
2. Recenter with **both** stick clicks
3. Confirm Windows is handing GEVR the OpenXR runtime you think it is
4. File an Issue with **headset**, **OpenXR runtime**, **SteamVR on/off**, **HMD vs monitor**, and **Start-GEVR.bat yes/no**

Do not upload your ROM.
