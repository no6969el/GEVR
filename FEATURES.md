<p align="center">
  <img src="GEVR-box-cover.png" alt="GoldenEye 007 VR - GEVR box art" width="520" />
</p>

# GEVR - stand inside GoldenEye

**Native VR. Bring your own ROM. Beta is live.**

Not an emulator overlay. Not a flat game with a 3D wrapper. GEVR rebuilds GoldenEye on PC for real OpenXR stereo, 6DOF, and controller aim so you can actually *be* in the Facility.

**Latest playable cut:** [**GEVR Beta vr450.2**](https://github.com/no6969el/GEVR/releases/latest) - public Beta (BYO-ROM, file-backed images from your cart). Zip: **`GEVR-Beta-vr450.2-win64.zip`**.

[Play the Beta](https://github.com/no6969el/GEVR/releases/latest) | [Direct zip](https://github.com/no6969el/GEVR/releases/download/vr450.2/GEVR-Beta-vr450.2-win64.zip) | [vr450.2 tag](https://github.com/no6969el/GEVR/releases/tag/vr450.2) | [Controls](docs/CONTROLS.md) | [Credits](CREDITS.md)

---

## On the box / Current features

What you can do in **vr450.2** today (player language):

- OpenXR VR present - true stereo, stand inside the room
- Physical walk / strafe moves **you**; guns stay with your hands
- Controller gun aim; squeeze ADS on the gun ray; dual-wield fire (default ON)
- While ADS: walk F/B on left stick; duck/stand on right stick
- **Keepers hard-coded** in the binary — cuff, FREEARM, door/corpse, mines, re-grab, landmark, aim scale, and related comfort stay on with a clean launch
- **Cuff / watch** stays with the left controller through stage changes
- **FREEARM ([#109](https://github.com/no6969el/GEVR/issues/109))** — two-handed NPC / weapon poses look better
- **Surface geometry ([#117](https://github.com/no6969el/GEVR/issues/117))** — more stable vertex references
- Door-edge snap, quieter false doors, corpse pass (bodies jam doors less)
- Mine **re-grab**; mines stick to / follow guards and stay visible while carried
- Landmark / aim scale / embed eye for readable aim in headset
- Throwables in your hand leave from the grip
- Tap **A** = next weapon; left-controller **X** = previous; **B** = reload
- Hand cue cube hides while that hand holds a weapon
- Tank auto-mount and stick pitch for shells; rockets nose along the flight path
- VR Settings on the intro hub (**look right**): turn speed / style / snap size
- In-app **Update** in GevrRomStarter (checks GitHub Latest); starter finds colocated `goldeneye.exe` and sets game path
- BYO-ROM + file-backed images; recenter = both thumbstick clicks
- Local / split-screen multiplayer on a monitor
- Flat / monitor play is a real path (`Play-on-monitor.bat`)

Fuller snapshot: [FEATURES-CURRENT.md](docs/FEATURES-CURRENT.md).

---

## The VR stuff that makes it feel like yours

**You are in the room**
Walk around your playspace and Bond walks with you. Turn your head - the world stays put. Recenter anytime with **both thumbstick clicks**.

**The gun is in your hand**
Point the controller to aim. Trigger fires. Squeeze to ADS - the mark sits on the gun ray, not glued to your face. While ADS, walk on the left stick and duck on the right. Dual-wield fires from each hand. Tap **A** / left **X** to cycle weapons; **B** reloads.

**Hands do Bond things**
Punch / melee with your hands. Throwables show in your hand and leave from the grip. Mines can be re-grabbed; they can stick to guards. Empty hand draws a smaller cube (hides while that hand holds a weapon). Cuff / watch stays on the left controller.

**Tanks that let you in**
Stand on the chassis and you auto-mount. Stick pitch aims the shells.

**Cinema that stays in the world**
Menus and intro cinema sit on a screen in a small hub room. Look left and right - the screen stays nailed in space.

**It looks like GoldenEye, in stereo**
True per-eye VR. File-backed images from *your* ROM (we never ship the cart).

**Then you play the campaign**
Facility and friends, OpenXR on PC. Die / continue / pad reload works in the same process. HUD and on-screen text pulled in off the HMD rim so you can read it.

---

## What we tested (vr450.2)

| Path | Notes |
|------|--------|
| **Pimax Crystal Super + SteamVR OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR) (sboys3) | Primary wear path - we do not maintain that driver; we *do* support this experience |
| **Native PimaxXR** | Verified attach / play |
| **Meta Quest 3 + Virtual Desktop OpenXR (VDXR)** | Verified attach / play |
| **RTX 5060 laptop + Quest 3 + Virtual Desktop VDXR** | BarZ wear **vr441**, 2026-09-17; one data point, not a minimum spec |

**Refresh rates:** The game follows your headset refresh (72 / 80 / 90 / 120 as reported). High Hz is still Beta-test territory.

When you report a bug or crash, please include: **headset**, **OpenXR runtime**, **SteamVR on/off**, **HMD vs monitor**, whether you used **`Start-GEVR.bat`**, and your **`gevr-*-boot.cmd`** filename. If it hard-crashed, attach the first lines of **`gevr-fault-*.txt`** beside the exe.

---

## Honest Beta notes

- Crashes and rough edges are expected. That is why it is Beta.
- You bring a **USA GoldenEye `.z64` you own**. No ROM in the download. Run **`Start-GEVR.bat`** so **GevrRomStarter** can bind your ROM (not bare `goldeneye.exe`).
- **New install** waits once while cache prepares. **After an update**, keep the same `.z64`; the ship stamp rebuilds cache once. Saves stay.
- Use **[vr450.2 Latest](https://github.com/no6969el/GEVR/releases/latest)** (`GEVR-Beta-vr450.2-win64.zip`).
- **Next series:** levels and gameplay stoppers (Frigate doors, mission locks, save slots, remaining prop / Dam-water issues).
- On a **flat / monitor** setup, classic **local split-screen multiplayer** is still there.

---

## Start

1. Grab **[`GEVR-Beta-vr450.2-win64.zip`](https://github.com/no6969el/GEVR/releases/download/vr450.2/GEVR-Beta-vr450.2-win64.zip)** from [Latest](https://github.com/no6969el/GEVR/releases/latest) / [vr450.2](https://github.com/no6969el/GEVR/releases/tag/vr450.2) (no ROM in the archive).
2. Unzip. Run **`Start-GEVR.bat`** (**GevrRomStarter** finds `goldeneye.exe` next to itself and sets the game path — point at your USA `.z64`).
3. Drop in your **USA `.z64`** when the starter asks.
4. Headset on. Recenter (both sticks). Enjoy.

[How to play / recenter](docs/CONTROLS.md) - [Report a bug](https://github.com/no6969el/GEVR/issues/new/choose) - [Who we credit](CREDITS.md)

Stay tuned. Star the repo and [follow @no6969el](https://github.com/no6969el).
