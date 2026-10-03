# Controls (Beta)

How to move, aim, and reset your position in [GEVR Beta vr452.4](https://github.com/no6969el/GEVR/releases/latest).

Install first: [README Install](../README.md#install-vr4524). **Controls video:** [YouTube walkthrough](https://www.youtube.com/watch?v=Jst5srE6Iwc) (also on the [README](../README.md#controls-right-after-install)). Download: [`GEVR-Beta-vr452.4-win64.zip`](https://github.com/no6969el/GEVR/releases/download/vr452.4/GEVR-Beta-vr452.4-win64.zip). Tester notes: [BETA.md](BETA.md). Menu + features: [README](../README.md#vr4524-features-how-to-use-them) · [FEATURES.md](../FEATURES.md). How to report: [CONTRIBUTING.md](../CONTRIBUTING.md).

## Which bat

- **Headset:** `Start-GEVR.bat` — VR picture, recenter, stick-turn, then GevrRomStarter.
- **Monitor / no headset:** `Play-on-monitor.bat` — VR off, no stereo eyes. Also the path for **local split-screen**.

Use those bats from **`GEVR-Beta-vr452.4-win64.zip`**. Do not double-click `goldeneye.exe`. Bare exe can skip the ROM cache update and leave VR input off.

## Controller layout

Quest / Meta Touch, Valve Index, and Oculus-style OpenXR binds (same actions):

| Input | What it does |
|---|---|
| **Left stick** | Walk |
| **Right stick** | Turn (Smooth or Snap from **GEVR Settings**) |
| **Both thumbstick clicks** | Recenter playspace |
| **Trigger** | Fire (each hand fires its own gun when dual-wielding) |
| **Squeeze / grip** | AIM / ADS (aim mark on the gun ray, not stuck in face centre) |
| **Squeeze near a door** | Open / close |
| **B** (right face; Index **B**) | USE / reload |
| **A** (right face; Index **A**) | Next weapon |
| **X** (left Quest/Oculus) | Previous weapon |
| **Menu / system** | Pause in headset (**Tab** on keyboard / monitor) |
| **Head / 6DOF** | Look around; walk your room to move in Bond-world |

### Short examples

1. **Recenter** — press both sticks in at once (L3+R3). One stick alone does nothing.
2. **ADS walk** — squeeze to aim; left stick walks forward/back (no duck); right stick ducks / stands.
3. **Dual-wield fire** — second gun in the other hand; left trigger / right trigger each fire their gun.
4. **Door** — stand near the door and squeeze to open/close; squeeze in the clear to aim again.
5. **Weapon cycle** — **A** next, left **X** previous.
6. **Mine regrab** — throw a remote / prox mine, then pick it up again when you can.

Auto-Aim defaults **OFF** in this build.

## Reset position (recenter)

**Click both thumbsticks at the same time** (press both sticks in like L3+R3).

Also works:

- **Xbox pad:** L3 + R3 together
- **Keyboard:** `Home` while the game window has focus

After recenter, standing still and turning your head should not slide the world. Walking in your room should move you in Bond-world.

## Move and look

| Input | What it does |
|---|---|
| **Left stick** | Walk |
| **Right stick** | Turn (Smooth or Snap from GEVR Settings) |
| **Head / 6DOF** | Look around; move in the playspace to translate in-world |
| **Controllers** | Gun aim follows the controller |

## Fire and aim

| Input | What it does |
|---|---|
| **Trigger** | Fire (each hand fires its own gun when dual-wielding) |
| **B** | USE / reload |
| **A** | Next weapon |
| **X** (left controller) | Previous weapon |
| **Squeeze / grip** | ADS / aim mark on the gun ray |
| **Squeeze near a door** | Open / close |
| **While ADS + left stick** | Walk forward/back (no duck) |
| **While ADS + right stick** | Duck / stand |

**Rockets:** launcher stays on the gun; flat crosshair on the rocket path. Grenade launcher is single-shot / muzzle feel OK. Throwables (grenades, mines, plastique, covert modem) show in your hand and leave from the grip.

## Hands

- **Left cuff / arm** — the left watch cuff stays with the controller through stage transitions.
- **Empty hand / fists** draw a cube (smaller than older cuts).
- The cube **hides** while that hand holds a weapon.

## Tank

- Stand on the chassis and you **auto-mount**.
- **Right stick pitch** aims the shells.
- Climb by getting onto the tank (no separate touch-to-enter gesture).

## Reload, pause, and menus

- **B** reloads / USE (right-hand B on Quest-style layouts).
- **Menu / system button** opens pause and options in headset (not B, not Y). **Tab** still works on keyboard / monitor.
- In the **pause watch**, **left stick** moves the menu highlight in VR.
- Face-button confirm in menus is still partly wired. If a face button does nothing, file an Issue with your headset and bat.
- Die / continue should no longer dump you in junk space ([issue #38](https://github.com/no6969el/GEVR/issues/38)). If it still breaks, quit the exe, run the bat again, and report it.

## Cinema / menus / GEVR Settings

On the **intro hub**, you are in a small room with a **world-locked** cinema screen. **GEVR Settings** glass is to your **right** (see [screenshot](../images/gevr-settings-menu-vr452.4.png) on the README).

**In this menu only:** **A** selects a row; stick **left / right** changes the value; **A** accepts. **Apply** (Save+Restart) + **A** saves and restarts the game. (In gameplay, **A** is still **next weapon** — that is separate from this settings UI.)

**Visual mode** **VR** / **XR** / **flat** — each profile saves its own values under `%LOCALAPPDATA%\GEVR`.

| Row (vr452.4 defaults) | Example |
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

**Monitor:** both eyes, left eye only, right eye only, or no desktop picture — for VR/XR play. Greyed out in flat. Saved with VR and XR, not flat.

**HD textures:** [pack releases](https://github.com/GhostlyDark/GoldenEye-007-HD/releases) · [evilgames page](https://evilgames.eu/texture-packs/ge007-hd.htm). GEVR does not ship the pictures. GLideN64 **PNG** zip (not `.hts`); **`GOLDENEYE`** inside **`hdtextures`** next to `goldeneye.exe`; On → **Apply** → next boot. Do not rename picture files.

More rows will be added over time. **Beta** is for future test toggles (**None yet** today).

## Getting VR working

GEVR uses **OpenXR**. Current zip: [README Install](../README.md#install-vr4524) / [`GEVR-Beta-vr452.4-win64.zip`](https://github.com/no6969el/GEVR/releases/download/vr452.4/GEVR-Beta-vr452.4-win64.zip).

**Verified:**

- **Pimax Crystal Super + SteamVR OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR) (sboys3). We do not maintain that driver. We do support this experience.
- **Native PimaxXR**
- **Quest 3 + Virtual Desktop OpenXR (VDXR)**

**Headset recipe:** unzip **`GEVR-Beta-vr452.4-win64.zip`**, run **`Start-GEVR.bat`**, point at your USA `.z64`, put the headset on, recenter with both stick clicks.

**No headset:** **`Play-on-monitor.bat`** (flat 2D, no OpenXR).

### If controls or VR feel dead

1. Launch with **`Start-GEVR.bat`** (headset) or **`Play-on-monitor.bat`** (flat), not bare `goldeneye.exe`
2. Recenter with **both** stick clicks
3. Confirm Windows is handing GEVR the OpenXR runtime you think it is
4. File an Issue with **headset**, **OpenXR runtime**, **SteamVR on/off**, **HMD vs monitor**, and **Start-GEVR.bat yes/no**. [CONTRIBUTING](../CONTRIBUTING.md).

Do not upload your ROM.
