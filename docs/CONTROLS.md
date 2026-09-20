# Controls (Beta)

How to move, aim, and reset your position in [GEVR Beta vr442](https://github.com/no6969el/GEVR/releases/latest).

Play steps: [README Play](../README.md#play-vr442---the-one-to-grab). Download: [Latest zip](https://github.com/no6969el/GEVR/releases/latest). Tester notes: [BETA.md](BETA.md). Pitch: [FEATURES.md](../FEATURES.md). What is next: [ROADMAP.md](ROADMAP.md). How to report: [CONTRIBUTING.md](../CONTRIBUTING.md).

## Which bat

- **Headset:** `Start-GEVR.bat` - KEEP VR picture (XR stereo source, SrcFbo, supersample 3, sky / playspace) plus recenter / stick-turn.
- **Monitor / no headset:** `Play-on-monitor.bat` - VR off, no stereo eyes. This is also the path for **local split-screen**.

Use those bats from the vr442 zip. Do not double-click `goldeneye.exe`. Bare exe can skip the ROM cache update and leave VR input off.

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
| **Trigger** | Fire (each hand fires its own gun when dual-wielding) |
| **B** | Reload |
| **A** | Cycle weapon |
| **Squeeze / grip** | ADS / aim mark on the gun ray (not stuck in face centre) |

**vr442:** Auto-Aim defaults **OFF** in this build. Dual-wield fire and per-hand tracers are in this zip. Two-hand support snap (and hiding the cube when hands get near) is **not** shipped yet.

Thrown grenades follow the hand. Rockets point their nose along the flight path. Grenade launcher is single-shot.

## Hands (vr442)

- **Empty left hand** shows a temporary cube (MASK left) so you can see where it is.
- Ghost fingers are parked. Nicer hands come later. See [COMING-SOON.md](COMING-SOON.md).

## Tank (vr442)

- Stand on the chassis and you **auto-mount**.
- **Right stick pitch** aims the shells. Yaw already worked.
- Touch-to-enter as a separate gesture is not the ship path. Climb by getting onto the tank.

## Reload, pause, and menus (vr442)

- **B** reloads (right-hand B on Quest-style layouts).
- **Menu / system button** opens pause and options in headset (not B, not Y). **Tab** still works on keyboard / monitor.
- In the **pause watch**, **left stick** moves the menu highlight in VR.
- Face-button confirm in menus is still partly wired. If a face button does nothing, that may still be a known gap - file an Issue with your headset and bat.
- Die / continue / pad reload should work in the same process now ([issue #38](https://github.com/no6969el/GEVR/issues/38)). If it still breaks, quit the exe, run the bat again, and report it.

## Cinema / menus

While the flat cinema or frontend menus are up, you are in a small hub room looking at a **world-locked** screen. Turn your head and the screen stays put in the room.

## Getting VR working

GEVR uses **OpenXR**. Which runtime Windows hands us matters. Current zip: [README Play](../README.md#play-vr442---the-one-to-grab) / [Latest release](https://github.com/no6969el/GEVR/releases/latest).

**Verified on vr442:**

- **Pimax Crystal Super + SteamVR OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR) (sboys3). We do not maintain that driver. We do support this experience.
- **Native PimaxXR**
- **Quest 3 + Virtual Desktop OpenXR (VDXR)**

**Hz:** 72 / 80 should work. Default and wear recommendation is **90**. The headset bat is still **90-pinned**. Over 90 is still beta-test territory. Try it and [file an Issue](https://github.com/no6969el/GEVR/issues/new/choose) if it feels off. We do not call 120 / 144 signed off. Runtime Hertz request is later ([issue #49](https://github.com/no6969el/GEVR/issues/49)).

**Headset recipe:** unzip vr442, run **`Start-GEVR.bat`**, point at your USA `.z64`, put the headset on, recenter with both stick clicks.

**No headset:** **`Play-on-monitor.bat`** (flat 2D, no OpenXR).

Native Quest (standalone APK) is a later port, not this PC zip.

### If controls or VR feel dead

1. Launch with **`Start-GEVR.bat`** (headset) or **`Play-on-monitor.bat`** (flat), not bare `goldeneye.exe`
2. Recenter with **both** stick clicks
3. Confirm Windows is handing GEVR the OpenXR runtime you think it is
4. File an Issue with **headset**, **OpenXR runtime**, **SteamVR on/off**, **HMD vs monitor**, and **Start-GEVR.bat yes/no** (Play-on-monitor.bat if no headset). [CONTRIBUTING](../CONTRIBUTING.md).

Do not upload your ROM.
