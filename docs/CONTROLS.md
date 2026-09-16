# Controls (Beta)

How to move, aim, and **reset your position** in the current GEVR Beta.

Use **`Start-GEVR.bat`** from the Release zip. That bat turns on the VR input knobs this sheet describes, marks the current Beta tag, and runs the ROM starter. Running `goldeneye.exe` alone may skip prepare / cache updates and leave recenter / stick-turn off.

## Reset position (recenter)

When things feel offset, or after you move your playspace setup:

**Click both thumbsticks at the same time** (press both sticks in like L3+R3).

Also works:

- **Xbox pad:** L3 + R3 together
- **Keyboard:** `Home` while the game window has focus

One stick click alone does nothing. This is the same recenter the game uses when you enter gameplay from the cinema/menu (auto-recenter).

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

Face buttons (A/B style) are only partly wired in this Beta cut. Menu / folder navigation is more reliable with the stick and trigger path; if a face button does nothing, that is a known gap (held work), not you.

## Cinema / menus

While the flat cinema or frontend menus are up, you are in a small hub room looking at a **world-locked** screen: turn your head and the screen stays put in the room.

## Getting VR working (read this)

GEVR uses **OpenXR**. Which runtime Windows hands us matters a lot on this Beta.

### Works today (verified)

- **90 Hz only** on this Beta - set the headset and SteamVR to 90 Hz before you play.
- **Headset:** Pimax Crystal Super (Micro OLED)
- **Path:** **SteamVR as the OpenXR runtime**, with the Pimax presented as a SteamVR HMD
- This cut was verified on that path using [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR) (sboys3). We don't maintain that driver (it's their project), but that's the path this Beta was built and tested on.
- If your Crystal is on **native PimaxXR** instead, expect problems on this cut.

**Practical recipe:** SteamVR installed and running; Windows **default OpenXR runtime = SteamVR**; launch with **`Start-GEVR.bat`**; put the headset on; recenter with both stick clicks.

### Not working yet (we are fixing)

| Setup | What people see | Status |
|---|---|---|
| **Pimax native XR (PimaxXR)** | Often fails to attach as a proper HMD session | Open - attach dig |
| **Quest 3 + Virtual Desktop (VDXR)** | Often opens **flat on the monitor** instead of the headset (regression) | Open - attach dig |

Please still file Issues for those - they help the dig. Say **runtime name** and whether the picture was **HMD / monitor-only / black / crash**.

Native Quest (standalone APK) is a later port, not this PC zip.

### If controls or VR feel dead

1. Launch with **`Start-GEVR.bat`**, not bare `goldeneye.exe`
2. Confirm Windows OpenXR default is **SteamVR** (not PimaxXR / VDXR) while we sort those
3. Recenter with **both** stick clicks
4. File an Issue and fill the headset / runtime fields (no ROM uploads)
