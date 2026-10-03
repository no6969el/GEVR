<p align="center">
  <img src="GEVR-box-cover.png" alt="GoldenEye 007 VR - GEVR box art" width="520" />
</p>

# GEVR - stand inside GoldenEye

**Native VR. Bring your own ROM. Beta is live.**

Not an emulator overlay. Not a flat game with a 3D wrapper. GEVR rebuilds GoldenEye on PC for real OpenXR stereo, 6DOF, and controller aim so you can actually *be* in the Facility.

**Latest playable cut:** [**GEVR Beta vr452.4**](https://github.com/no6969el/GEVR/releases/latest) — public Beta (BYO-ROM). Zip: **`GEVR-Beta-vr452.4-win64.zip`**.

[Install](../README.md#install-vr4524) · [Controls](../README.md#controls-right-after-install) · [vr452.4 tag](https://github.com/no6969el/GEVR/releases/tag/vr452.4) · [Credits](CREDITS.md)

---

## vr452.4 — how to use what shipped

Full walkthrough with screenshot: [README — GEVR Settings](../README.md#gevr-settings-in-game-menu).

### GEVR Settings (in-game menu)

Intro hub — **look right** at **GEVR Settings**. **A** selects a row; stick **left / right** changes the value; **A** accepts. Highlight **Apply** (Save+Restart) and press **A** to save and restart.

**Visual mode:** **VR**, **XR**, or **flat** — each keeps its own saved settings.

| Row | Example |
|---|---|
| Supersample | 3 Sharp |
| Monitor | On |
| Full screen | Off |
| Window | 1280×960 |
| Filter | Bilinear |
| Frame rate | Headset |
| Game speed | Smooth 90 |
| HD textures | Off |
| Visual mode | VR |
| Beta | None yet |
| Reset defaults | No |
| Apply | Save+Restart |

**Monitor:** both eyes, left only, right only, or no desktop picture (VR/XR). Greyed out in flat. Saved with VR and XR profiles, not flat.

New features will keep being added here. **Beta** will hold test options later (**None yet** today).

### HD textures

**GEVR does not ship the pictures.** [GoldenEye-007-HD releases](https://github.com/GhostlyDark/GoldenEye-007-HD/releases) · [evilgames GE007 HD](https://evilgames.eu/texture-packs/ge007-hd.htm) — **GLideN64 PNG** zip (not `.hts`). Put **`GOLDENEYE`** inside **`hdtextures`** next to `goldeneye.exe`; HD textures **On** → **Apply** → **next boot**. Do not rename picture files.

| Feature | How |
|---|---|
| **Rockets** | Launcher stays on the gun; flat crosshair on the path. |

Install · controls video · binds: [README](../README.md).

---

## On the box / current features

What you can do in **vr452.4** today (player language):

- OpenXR VR — true stereo, stand inside the room
- Physical walk / strafe moves **you**; guns stay with your hands
- Controller gun aim; squeeze ADS on the gun ray; dual-wield fire
- While ADS: walk F/B on left stick; duck/stand on right stick
- Playspace / free move / hands follow ([#74](https://github.com/no6969el/GEVR/issues/74)); melee swing pose ([#75](https://github.com/no6969el/GEVR/issues/75)); Janus spawn ([#82](https://github.com/no6969el/GEVR/issues/82)); gun origin
- Grip-near-door open/close ([#90](https://github.com/no6969el/GEVR/issues/90)); Dam SKYWORLD sky ([#80](https://github.com/no6969el/GEVR/issues/80))
- Throwables in your hand leave from the grip; tap **A** / left **X** to cycle weapons
- Hand cue cube hides while that hand holds a weapon
- Tank auto-mount and stick pitch for shells
- **GEVR Settings** on the intro hub; in-app **Update** in GevrRomStarter
- BYO-ROM + file-backed images; recenter = both thumbstick clicks
- Local / split-screen on a monitor; flat via `Play-on-monitor.bat`

Fuller snapshot: [FEATURES-CURRENT.md](docs/FEATURES-CURRENT.md).

---

## The VR stuff that makes it feel like yours

**You are in the room**
Walk around your playspace and Bond walks with you. Turn your head - the world stays put. Recenter anytime with **both thumbstick clicks**.

**The gun is in your hand**
Point the controller to aim. Trigger fires. Squeeze to ADS - the mark sits on the gun ray, not glued to your face. While ADS, walk on the left stick and duck on the right. Dual-wield fires from each hand.

**Hands do Bond things**
Punch / melee with your hands. Touch to use (doors, interact) by reaching. Throwables show in your hand and leave from the grip.

**Tanks that let you in**
Stand on the chassis and you auto-mount. Stick pitch aims the shells.

**Cinema that stays in the world**
Menus and intro cinema sit on a screen in a small hub room. **GEVR Settings** glass is to your **right**.

**It looks like GoldenEye, in stereo**
True per-eye VR. File-backed images from *your* ROM (we never ship the cart). Optional HD textures from your own pack folder.

**Then you play the campaign**
Facility and friends, OpenXR on PC. HUD and on-screen text pulled in off the HMD rim so you can read it.

---

## What we tested

| Path | Notes |
|------|--------|
| **Pimax Crystal Super + SteamVR OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR) (sboys3) | Primary wear path |
| **Native PimaxXR** | Verified attach / play |
| **Meta Quest 3 + Virtual Desktop OpenXR (VDXR)** | Verified attach / play |

---

## Play

1. Grab **[`GEVR-Beta-vr452.4-win64.zip`](https://github.com/no6969el/GEVR/releases/latest)** (no ROM in the archive).
2. Follow [README Install](../README.md#install-vr4524).
3. [Controls](../README.md#controls-right-after-install) and [CONTROLS.md](docs/CONTROLS.md) for the full bind list.

Report bugs: [CONTRIBUTING.md](CONTRIBUTING.md). Do not upload your ROM.
