<p align="center">
  <img src="GEVR-box-cover.png" alt="GoldenEye 007 VR - GEVR box art" width="480" />
</p>

# GEVR

**GoldenEye in VR. Bring your own ROM.**

Latest build: **[vr452.3](https://github.com/no6969el/GEVR/releases/latest)**  
Direct zip: [`GEVR-Beta-vr452.3-win64.zip`](https://github.com/no6969el/GEVR/releases/download/vr452.3/GEVR-Beta-vr452.3-win64.zip)

[Discord](https://discord.gg/flat2vr) · [Report a bug](https://github.com/no6969el/GEVR/issues/new/choose) · [Credits](CREDITS.md)

---

## Stay on Latest

GEVR has an in-app **Update** in **GevrRomStarter**. Use it when a newer build is out (saves stay). Always stay on Latest so you have the features listed below.

---

## How to play

1. Download **[`GEVR-Beta-vr452.3-win64.zip`](https://github.com/no6969el/GEVR/releases/download/vr452.3/GEVR-Beta-vr452.3-win64.zip)** (no ROM inside) - or click **Update** if you already play.
2. Unzip anywhere.
3. Double-click **`Start-GEVR.bat`** - it opens **GevrRomStarter**, which finds `goldeneye.exe` in the same folder.
4. Point it at a **USA GoldenEye `.z64` you own**.
5. Put the headset on. Click **both thumbsticks** to recenter.
6. On **Mode Select**, open **GEVR Settings** to tune picture, Visual mode (VR / XR / Flat), and optional HD textures - then **Apply** so the game restarts with your choices saved.

Tip: if VR feels half-speed, turn **SteamVR Motion Smoothing** and **Virtual Desktop Space Warp** **Off**.

Flat screen: set Visual to **Flat** in GEVR Settings and **Apply**, or use **`Play-on-monitor.bat`**. Same game; split-screen multiplayer works on a monitor.

---

## What's new in vr452.2

- **GEVR Settings** - from Mode Select: sharpen the picture, pick launch style, optional HD, then **Apply**.
- **Visual modes** - full **VR**, square-outline **XR**, or **Flat** on your monitor.
- **Apply & restart** - save once; the game comes back in the mode you picked. Supersample and friends stick across that relaunch.
- **Reset defaults** - one confirm restores a solid VR or Flat starting point.
- **Optional HD textures** - sharper walls and props when you install a pack (off by default).

How-to: [`docs/GEVR-SETTINGS.md`](docs/GEVR-SETTINGS.md).

---

## Controls

| Input | What it does |
|---|---|
| **Left stick** | Walk |
| **Right stick** | Turn (smooth or snap - set in VR Settings) |
| **Both stick clicks** | Recenter |
| **Trigger** | Fire (each hand fires its own gun when dual-wielding) |
| **Squeeze / grip** | Aim down sights; also grab for holster / watch press / pick-up |
| **A** (right) | Next weapon (that hand) |
| **X** (left) | Previous weapon (that hand) |
| **B** | Reload |

**Short examples:** click both sticks to recenter · squeeze to ADS, then walk · right hand over left cuff + grab to detonate or fire the watch laser · gun to hip + grab to holster · grip near a thrown mine to pick it back up.

More detail: [`docs/CONTROLS.md`](docs/CONTROLS.md).

---

## What you can do now (vr452.2)

- **Stand inside GoldenEye** - real OpenXR stereo; walk your playspace and Bond moves with you.
- **Aim with your hands** - point the controller, squeeze to ADS, fire with the trigger.
- **Dual-wield** - hold a gun in each hand; each trigger fires that hand.
- **Cuff / watch** - left cuff stays on your left. Put your **right hand over the cuff** and **grab**: detonates planted remotes if mines are armed; otherwise fires a **watch laser** from the cuff. Holster at the hip with grab. Right hand draws over the cuff (not under). No three-arm watch pull-out. Proximity alone does not fire.
- **Hand cycle** - leave the left hand empty when you want; cycle weapons per hand; grip to pick things up; holster at each hip; hands respect each other's space.
- **Prop stick** - mines and stickables stick to barrels, tanks, vehicles, crates, modems, and onto other props. Guards still take sticks as before.
- **Mines** - throw, stick, and **pick them back up** (re-grab).
- **Throwables** leave from your grip, not from mid-air.
- **Doors & bodies** - cleaner door-edge aim, quieter false doors, corpses jam doors less.
- **Readable aim** - scaled aimer / landmarks / eye marks that stay clear in headset.
- **Tanks** - stand on the chassis to mount; aim shells with the stick.
- **Your settings, your way** - GEVR Settings for picture, Visual VR / XR / Flat, Apply that sticks, Reset defaults, optional HD.

---

## Coming next

Next fix series: **levels and gameplay stoppers** already reported. Scope / lens fill is still parked - not in this cut.

---

## Links

[Latest zip](https://github.com/no6969el/GEVR/releases/latest) · [Discord](https://discord.gg/flat2vr) · [Features](FEATURES.md) · [GEVR Settings](docs/GEVR-SETTINGS.md) · [Patreon](https://www.patreon.com/cw/GEVR)

Star the repo and [follow @no6969el](https://github.com/no6969el) for the next drop.
