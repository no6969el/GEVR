<p align="center">
  <img src="GEVR-box-cover.png" alt="GoldenEye 007 VR - GEVR box art" width="520" />
</p>

# GEVR - stand inside GoldenEye

**Native VR. Bring your own ROM. Beta is live.**

Not an emulator overlay. Not a flat game with a 3D wrapper. GEVR rebuilds GoldenEye on PC for real OpenXR stereo, 6DOF, and controller aim so you can actually *be* in the Facility.

**Latest playable cut:** [**GEVR Beta vr450.1**](https://github.com/no6969el/GEVR/releases/latest) - public Beta (BYO-ROM, file-backed images from your cart). Zip: **`GEVR-Beta-vr450.1-win64.zip`**.

[Play the Beta](https://github.com/no6969el/GEVR/releases/latest) | [vr450.1 tag](https://github.com/no6969el/GEVR/releases/tag/vr450.1) | [Controls](docs/CONTROLS.md) | [Credits](CREDITS.md) | [Roadmap](docs/ROADMAP.md) | [Coming soon](docs/COMING-SOON.md)

---

## On the box / Current features

What you can do in **vr450.1** today (player language):

- OpenXR VR present - true stereo, stand inside the room
- Physical walk / strafe moves **you**; guns stay with your hands
- Controller gun aim; squeeze ADS on the gun ray; dual-wield fire (default ON)
- While ADS: walk F/B on left stick; duck/stand on right stick
- **Gunfire fixed** ([#84](https://github.com/no6969el/GEVR/issues/84)): rifle guards use correct rifle fire tables/cadence (not pistol lean/single-shot)
- **Black flicker quieted (temporary)** when remote/prox/timed mines stick (including Facility), same no-modem scrap hide as the covert modem. Props still pass through each other; they should collide and rest ([#55](https://github.com/no6969el/GEVR/issues/55))
- Ammo counter picture in VR is in
- Throwables in your hand leave from the grip; grenades and mines resized to better match real hand dimensions
- Tap **A** = next weapon; left-controller **X** = previous (weapon wheel still cooking)
- Hand cue cube hides while that hand holds a weapon; smaller cube when empty / fists
- Cloudy sky stay-put (SKYINF); game follows headset Hz; monitor stays live in VR
- Tank auto-mount and stick pitch for shells; rockets nose along the flight path
- VR Settings on the intro hub (**look right**): turn speed / style / snap size
- In-app **Update** in GevrRomStarter (checks GitHub Latest)
- BYO-ROM + file-backed images; recenter = both thumbstick clicks
- Local / split-screen multiplayer on a monitor
- Flat / monitor play is a real path (`Play-on-monitor.bat`)
- **Known / in progress:** Statue Janus meet/scene ([#82](https://github.com/no6969el/GEVR/issues/82)) — not fixed in this cut

Fuller snapshot: [FEATURES-CURRENT.md](docs/FEATURES-CURRENT.md).

---

## The VR stuff that makes it feel like yours

**You are in the room**
Walk around your playspace and Bond walks with you. Turn your head - the world stays put. Recenter anytime with **both thumbstick clicks**. (This cut includes the playspace comfort pass so straying off your reset spot does not shear the gun and world when you look around.)

**The gun is in your hand**
Point the controller to aim. Trigger fires. Squeeze to ADS - the mark sits on the gun ray, not glued to your face. While ADS, walk on the left stick and duck on the right. Dual-wield fires from each hand. Casings leave the weapon. Haptics pulse when a round actually goes off. Tap **A** / left **X** to cycle weapons.

**Hands do Bond things**
Punch / melee with your hands. Touch to use (doors, interact) by reaching instead of hunting a 2D prompt. Throwables show in your hand and leave from the grip. Empty hand draws a smaller cube for now (hides while that hand holds a weapon). Ghost hand is parked.

**Tanks that let you in**
Stand on the chassis and you auto-mount. Stick pitch aims the shells.

**Cinema that stays in the world**
Menus and intro cinema sit on a screen in a small hub room. Look left and right - the screen stays nailed in space; you are not wearing a billboard on your face.

**It looks like GoldenEye, in stereo**
True per-eye VR. Explosions and fire use the chaired color / byte-order path; bodies can stay after kills (up to 48). Far characters stay readable. Intro gunbarrel drip. Title walk backdrop. File-backed images from *your* ROM (we never ship the cart).

**Then you play the campaign**
Facility and friends, OpenXR on PC. Die / continue / pad reload works in the same process. Mission Report / NEXT actually takes input after a stage clear. HUD and on-screen text pulled in off the HMD rim so you can read it.

---

## What we tested (vr450.1)

These paths are what this Beta was built and stared on:

| Path | Notes |
|------|--------|
| **Pimax Crystal Super + SteamVR OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR) (sboys3) | Primary wear path - we do not maintain that driver; we *do* support this experience |
| **Native PimaxXR** | Verified attach / play |
| **Meta Quest 3 + Virtual Desktop OpenXR (VDXR)** | Verified attach / play |
| **RTX 5060 laptop + Quest 3 + Virtual Desktop VDXR** | BarZ wear **vr441**, 2026-09-17; ran surprisingly well (one data point, not a minimum spec) |

**Refresh rates:** The game follows your headset refresh (72 / 80 / 90 / 120 as reported). High Hz is still Beta-test territory - try it and report if something feels off. We do not call every high-Hz path signed off yet.

When you report a bug or crash, please include: **headset**, **OpenXR runtime**, **SteamVR on/off**, **HMD vs monitor**, whether you used **`Start-GEVR.bat`**, and your **`gevr-*-boot.cmd`** filename. If it hard-crashed, attach the first lines of **`gevr-fault-*.txt`** beside the exe.

---

## Honest Beta notes

- Crashes and rough edges are expected. That is why it is Beta.
- You bring a **USA GoldenEye `.z64` you own**. No ROM in the download. Run **`Start-GEVR.bat`** so **GevrRomStarter** can bind your ROM (not bare `goldeneye.exe`).
- **New install** waits once while cache prepares. **After an update**, keep the same `.z64`; the ship stamp rebuilds cache once. Saves stay.
- Use **[vr450.1 Latest](https://github.com/no6969el/GEVR/releases/latest)** (`GEVR-Beta-vr450.1-win64.zip`). Older tag pages stay; their **zips were stripped** where we pulled them.
- The zip includes **`glew32.dll`** and the other runtime DLLs Windows needs.
- **Dam crates** can still pop in and out; **Dam / Frigate water** can still look wrong (world-stable sea still open); **glass bullet holes** can show in one eye in places.
- Big explosions can still hard-crash. The fault file is new; the crash is not fully gone.
- Two-hand snap and weapon wheel HUD are **not** in this zip. See [COMING-SOON.md](docs/COMING-SOON.md).
- On a **flat / monitor** setup, classic **local split-screen multiplayer** is still there.

---

## Start

1. Grab **[`GEVR-Beta-vr450.1-win64.zip`](https://github.com/no6969el/GEVR/releases/latest)** from [Latest](https://github.com/no6969el/GEVR/releases/latest) / [vr450.1](https://github.com/no6969el/GEVR/releases/tag/vr450.1) (no ROM in the archive).
2. Unzip. Run **`Start-GEVR.bat`** (**GevrRomStarter** - point at your USA `.z64`).
3. Drop in your **USA `.z64`** when the starter asks.
4. Headset on. Recenter (both sticks). Enjoy.

[How to play / recenter](docs/CONTROLS.md) - [Report a bug](https://github.com/no6969el/GEVR/issues/new/choose) - [Who we credit](CREDITS.md)

Stay tuned. Star the repo and [follow @no6969el](https://github.com/no6969el).
