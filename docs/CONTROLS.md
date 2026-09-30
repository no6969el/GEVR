# Controls (Beta)

How to move, aim, and reset your position in [GEVR Beta vr451](https://github.com/no6969el/GEVR/releases/latest).

Play steps: [README](../README.md#how-to-play). Download: [GEVR-Beta-vr451-win64.zip](https://github.com/no6969el/GEVR/releases/download/vr451/GEVR-Beta-vr451-win64.zip) ([Latest](https://github.com/no6969el/GEVR/releases/latest) / [vr451](https://github.com/no6969el/GEVR/releases/tag/vr451)). Prefer **Update** in GevrRomStarter so you stay on Latest. Tester notes: [BETA.md](BETA.md). Pitch: [FEATURES.md](../FEATURES.md). How to report: [CONTRIBUTING.md](../CONTRIBUTING.md).

## Which bat

- **Headset:** Start-GEVR.bat - starts **GevrRomStarter**, which looks for goldeneye.exe in the same folder and sets the game path for you.
- **Monitor / no headset:** Play-on-monitor.bat - VR off, no stereo eyes. This is also the path for **local split-screen**.

Use those bats from **GEVR-Beta-vr451-win64.zip**. Do not double-click goldeneye.exe. Bare exe can skip the ROM cache update and leave VR input off.

## Reset position (recenter)

**Click both thumbsticks at the same time** (press both sticks in like L3+R3).

Also works:

- **Xbox pad:** L3 + R3 together
- **Keyboard:** Home while the game window has focus

One stick click alone does nothing.

**Short example:** stand in your playspace, click both sticks, then walk forward with the left stick while looking around with your head.

## Move and look

| Input | What it does |
|---|---|
| **Left stick** | Walk |
| **Right stick** | Turn (Smooth or Snap from VR Settings) |
| **Head / 6DOF** | Look around; move in the playspace to translate in-world |
| **Controllers** | Gun aim follows the controller |

## Fire and aim

| Input | What it does |
|---|---|
| **Trigger** | Fire (each hand fires its own gun when dual-wielding) |
| **B** | Reload |
| **A** | Next weapon (that hand) |
| **X** (left controller) | Previous weapon (that hand) |
| **Squeeze / grip** | ADS / aim mark on the gun ray; also grab for holster, watch press, and pick-up |
| **While ADS + left stick** | Walk forward/back (no duck) |
| **While ADS + right stick** | Duck / stand |

**Short example:** squeeze to ADS, walk with the left stick, fire with the trigger. Tap **A** / left **X** to cycle weapons; **B** reloads.

Rockets point their nose along the flight path. Throwables (grenades, mines, plastique, covert modem) show in your hand and leave from the grip.

## Cuff / watch (vr451)

- **Left cuff** stays with your left controller through missions.
- **Watch press:** put your **right hand over the left cuff** and **grab** (squeeze rising edge). If remotes are planted / mines are armed, that **detonates** them (no detonator item needed). If nothing is planted, fires a **watch laser from the cuff**.
- **Holster:** bring a gun to your **hip** and grab to empty that hand; grab the hip again to take it back.
- Right hand **draws over** the cuff (not under it). No watch pull-out weapon - no three-arm look.
- **Proximity alone does not fire** - you need the grab over the cuff.

**Short example:** plant remotes, hover your right hand over the watch, grab once to detonate. Or with nothing planted, same gesture fires the watch laser.

## Hand cycle (vr451)

- Leave the **left hand alone** (empty) when you want.
- Cycle weapons **per hand** with **A** / left **X**.
- **Grip** near a thrown mine or stickable to pick it up.
- **Per-hip holster** - each side can stash / restore with grab at the hip.
- Hands **respect each other's space** - one hand's holster / cuff / pick does not steal the other.

**Short example:** holster the right gun at the right hip, keep cycling the left, then grab the hip again to redraw.

## Mines, prop stick, and re-grab (vr451)

- Thrown **remote / proximity** mines can be **picked back up** when the game allows it.
- **Prop stick:** mines and stickables stick to **barrels, tanks, vehicles, crates, modems**, and **onto other props**. Guards still take sticks as before.
- **Short example:** throw a prox mine at a crate or a guard, watch it stick, or re-grab a remote you just tossed if you change your mind.

## Doors and bodies

- Door-edge aim / hit snap is more dependable around room boundaries.
- False / decoy door presentation is quieter.
- Dead bodies are less likely to jam a door mid open/close.

## Tank

- Stand on the chassis and you **auto-mount**.
- **Right stick pitch** aims the shells. Yaw already worked.
- Climb by getting onto the tank.

## Reload, pause, and menus

- **B** reloads.
- **Menu / system button** opens pause and options in headset (not B, not Y). **Tab** still works on keyboard / monitor.
- In the **pause watch**, **left stick** moves the menu highlight in VR.

## Cinema / menus

While the flat cinema or frontend menus are up, you are in a small hub room looking at a **world-locked** screen.

**VR Settings** glass sits to your **right** on that hub. Right stick: **up/down** picks a row, **left/right** changes TURN SPEED, TURN STYLE (Smooth/Snap), and SNAP SIZE (gray on Smooth). Prefs save under %LOCALAPPDATA%/GEVR with your saves.

## Getting VR working

GEVR uses **OpenXR**. Current zip: [README](../README.md#how-to-play) / [GEVR-Beta-vr451-win64.zip](https://github.com/no6969el/GEVR/releases/download/vr451/GEVR-Beta-vr451-win64.zip).

**Verified:**

- **Pimax Crystal Super + SteamVR OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR) (sboys3). We do not maintain that driver. We do support this experience.
- **Native PimaxXR**
- **Quest 3 + Virtual Desktop OpenXR (VDXR)**

**Hz:** The game follows your headset refresh (72 / 80 / 90 / 120 as reported). High Hz is still Beta-test territory - try it and report if something feels off.

**Headset recipe:** unzip or **Update**, run **Start-GEVR.bat**, point at your USA .z64, put the headset on, recenter with both stick clicks.

**No headset:** **Play-on-monitor.bat** (flat 2D, no OpenXR).

### If controls or VR feel dead

1. Launch with **Start-GEVR.bat** (headset) or **Play-on-monitor.bat** (flat), not bare goldeneye.exe
2. Recenter with **both** stick clicks
3. Confirm Windows is handing GEVR the OpenXR runtime you think it is
4. File an Issue with **headset**, **OpenXR runtime**, **SteamVR on/off**, **HMD vs monitor**, and **Start-GEVR.bat yes/no** (Play-on-monitor.bat if no headset). [CONTRIBUTING](../CONTRIBUTING.md).

Do not upload your ROM.
