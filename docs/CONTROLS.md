# Controls (Beta)

How to move, aim, shoot, and use Bond’s watch in **[GEVR Beta vr453](https://github.com/no6969el/GEVR/releases/latest)**.

Install first: [README Install](../README.md#install-vr453). **Controls video:** [YouTube walkthrough](https://www.youtube.com/watch?v=Jst5srE6Iwc) (also on the [README](../README.md#controls-right-after-install)). Download: [`GEVR-Beta-vr453-win64.zip`](https://github.com/no6969el/GEVR/releases/download/vr453/GEVR-Beta-vr453-win64.zip). Tester notes: [BETA.md](BETA.md). Menu + features: [README](../README.md#vr453-features-how-to-use-them) · [FEATURES.md](../FEATURES.md). How to report: [CONTRIBUTING.md](../CONTRIBUTING.md).

## Which bat

- **Headset:** `Start-GEVR.bat` — VR picture, recenter, stick-turn, then GevrRomStarter.
- **Monitor / no headset:** `Play-on-monitor.bat` — VR off, no stereo eyes. Also the path for **local split-screen**.

Use those bats from **`GEVR-Beta-vr453-win64.zip`**. Do not double-click `goldeneye.exe`. Bare exe can skip the ROM cache update and leave VR input off.

## Default layout (OpenXR)

GEVR assumes the usual FPS layout unless you change bindings in a boot profile:

| Hand | Role |
|---|---|
| **Right controller** | Gun hand — fire, aim, weapon **A** / **B**, comfort turn stick |
| **Left controller** | Walk hand — move stick, **X** previous weapon, left watch cuff on the arm |

**Meta Quest / Touch**, **Valve Index**, and other **Oculus-style OpenXR** profiles use the same actions; only the printed names on the plastic differ (see tables below).

Auto-Aim defaults **OFF** in this build.

---

## Meta Quest / Touch (stereo VR)

| Control | Action |
|---|---|
| **Right trigger** | Fire the gun in your **right** hand |
| **Left trigger** | Fire the gun in your **left** hand (any time that hand holds a gun — not only dual-wield) |
| **Right grip (squeeze)** | **Aim / ADS** — insight aim on the gun ray (aim mark on the weapon, not glued to your face) |
| **Right grip at a door** | **Open / close** the door (same squeeze; no separate “use” reach when you are in range) |
| **Right grip on your left watch face** | **Watch press** — see [Bond’s watch & cuff](#bonds-watch--cuff) (laser, detonator, or magnet attract depending on what you selected in the pause watch) |
| **Right grip at your right hip** (gun hand low) | **Holster / draw** — stash the right-hand gun to your hip and bring out Bond’s fist, or pull the stashed gun back (left hand must be bare / cuff only) |
| **Left grip (squeeze)** | **Aim / ADS** when that hand holds a gun; near a door or pickup, same rules as the right grip for that hand |
| **Left grip near a dropped weapon** | **Pick up** into **that** hand (per-hand inventory) |
| **Left grip near your own stuck mine** | **Pick the mine back up** (remote mines and arming proximity mines you placed; not live grenades or armed traps) |
| **Left grip on a two-handed gun’s fore-end** | **Two-hand support** — hold the left controller along the barrel and squeeze; the right-hand rifle/shotgun/SMG aims along the line between both grips (release to return to one-hand aim) |
| **Left stick** | Walk and strafe |
| **Right stick** | Turn in-game (**Smooth** or **Snap** from **GEVR Settings** on the intro hub) |
| **Both stick clicks together** | **Recenter** playspace (one stick alone does nothing) |
| **Right stick up / down while aiming** | Stand / crouch (one-hand duck with the gun hand) |
| **Left stick while aiming** | Walk forward and back without the old “walk backward = accidental crouch” chord |
| **Right A** | **Next weapon** (right-hand inventory step) |
| **Left X** | **Previous weapon** (left-hand inventory step) |
| **Right B** | **USE** — doors and switches at range, plant/activate gadgets, throw cycle, and other retail **B** actions (**gun reload** uses the [reload gesture](#reload-gesture-vr), not **B**) |
| **Menu** (left controller) | **Pause** — Bond’s watch menu in VR |
| **Left Y** (optional) | Also mapped to **pause** in the shipped VR boot profile |
| **Head / room-scale** | Look around; physically walk to move in Bond-world |
| **Swing an empty hand or melee weapon** | Melee (swing-based; still being tuned) |

**Dual-wield** is only when you hold **two guns** — put a second gun in the left hand (weapon cycle or pickup). **Left trigger** fires the left gun; **right trigger** fires the right gun. A **single** gun in the left hand still fires with **left trigger** on its own. Each hand keeps its own weapon line.

**Throwables** (grenades, timed mines, remote/proximity mines, plastique, covert modem, etc.): they appear in the hand; **trigger** throws or fires; **B** still handles use/plant/reload where retail does. After you throw or plant a mine, use **grip regrab** (above) to recover your own stuck mines when the game allows it.

---

## Valve Index (stereo VR)

Same bindings as Quest; Index names:

| Index control | Same as Quest | Action |
|---|---|---|
| **Right trigger** | Right trigger | Fire right gun |
| **Left trigger** | Left trigger | Fire left-hand gun |
| **Right grip (A button grip)** | Right grip | Aim / ADS; door; watch press; hip holster |
| **Left grip** | Left grip | Aim (left gun); door; pickup; mine regrab; two-hand support |
| **Right thumbstick** | Right stick | Turn |
| **Left thumbstick** | Left stick | Walk |
| **Right A** | Right A | Next weapon |
| **Right B** | Right B | USE / activate (reload = gesture) |
| **Left X** (face button) | Left X | Previous weapon |
| **Left Y** | Left Y | Pause (in shipped profile) |
| **System / menu button** | Quest **Menu** | Pause |

---

## Bond’s watch & cuff

The **left cuff is the watch** — it stays on your left arm in VR. You do **not** equip a huge watch model into your gun hand for laser or detonator (hands stay visible).

### Pause watch (inventory)

1. Press **Menu** (or **Left Y** in the default VR profile).
2. Move the highlight with the **left stick**.
3. Confirm gadgets and modes with the face buttons (same as retail watch pages).

From this menu you can pick **Watch Laser**, **Detonator**, **Watch Magnet Attract**, **Watch Magnet Repel**, and other stage items when you have them.

### GAME OPTIONS (ratio and VR settings)

Open **GAME OPTIONS** on the pause watch. The list continues **past ratio**. **Scroll down** with the **left stick** — the retail sheet’s last line reads exactly: **scroll down - vr settings below**. VR comfort rows (turn speed, turn style, snap size, and related options) sit **below** ratio on that page.

**Watch Laser vs Detonator (mode):**

- Choose **Watch Laser** in the pause watch to force **laser only** on cuff press (never detonate on that press).
- Choose **Detonator** for **auto** behaviour: cuff press **detonates your planted remote mines** if any are active; otherwise it fires the **watch laser** from the cuff.

If the stage does not give you a laser, a **Watch Laser** row can still appear in the watch list for solo play.

### Cuff press (laser / detonate)

When the watch is **not** animating open on screen:

1. Touch the **left watch face** with your **right controller grip** (gun hand).
2. **Squeeze** (grip) on a **new** press — not a squeeze you were already holding before you touched the watch.

Result depends on what you selected in the pause watch (laser-only, auto detonate/laser, or magnet — below).

### Watch magnet attract

1. In the **pause watch**, select **Watch Magnet Attract** (you keep your guns in hand; hands stay visible).
2. Touch the **left watch cuff** with your **right hand** and **squeeze** — same gesture as the watch laser.

That spends **watch magnet ammo** and runs one **attract** pulse (pulls metal like retail). With no ammo you get an empty click. Select magnet again after use when you need another pulse.

**Watch Magnet Repel** is still chosen from the **pause watch** like retail GoldenEye (repel uses the normal watch item flow; there is no separate cuff shortcut for repel).

---

## Weapons & holster (per-hand)

With per-hand inventory (default in the shipped VR profile):

| Control | Action |
|---|---|
| **Right A** | Cycle **right-hand** weapon forward |
| **Left X** | Cycle **left-hand** weapon forward |
| **Grip pickup** | Squeeze near a weapon on the ground to equip it to **that** hand |
| **Right hip + squeeze** | Toggle **holster** — gun to hip / fist out, or draw stashed gun (see table above) |

You cannot put the **same** non-dual gun in both hands unless retail would allow that pair.

**Two-handed rifles / shotguns / SMGs / grenade launcher:** hold with the **right** hand; bring the **left** grip to the fore-end and **squeeze** to stabilize aim (support hold). Let go to aim from the right wrist only.

---

## Reload gesture (VR)

Guns do **not** auto-reload. Reload in VR with the physical gesture for that weapon — not with **B**.

| Weapon type | Reload |
|---|---|
| **Magazine-fed** (mag on top, mag on bottom, **Uzi**, etc.) | Reload from the **magazine** — bring the mag through the reload motion |
| **Pistols** and guns **without** a magazine (**shotgun** included) | Reload at the **chest cross** gesture only |
| **Handle grab** (grab the gun handle to swap) | **Swaps hands** — does **not** reload |

**B** still covers retail **USE**, plant, activate, and other **B** actions where GoldenEye maps them; it is not the VR gun-reload button.

---

## Tank

- Walk onto the **tank chassis** to **auto-mount**.
- **Right stick up / down** (pitch) aims the cannon elevation.
- Dismount by leaving the tank like retail (no separate “enter” button beyond getting on).

---

## Recenter

**Press both thumbstick clicks at the same time** (L3 + R3 together).

Also works:

- **Xbox gamepad:** L3 + R3 together
- **Keyboard:** `Home` while the game window has focus

After recenter, turning your head while standing still should not slide the world. Walking in your room moves you in Bond-world.

---

## GEVR Settings (intro hub) vs pause watch

| | **GEVR Settings** (intro hub, glass on your right) | **Pause watch** (in mission) |
|---|---|---|
| Open | Look at **GEVR Settings** on the hub; interact in VR | **Menu** / **Left Y** |
| Navigate | **A** selects a row; stick **left/right** changes value; **Apply** saves and restarts | **Left stick** moves highlight; face buttons confirm |
| **A** in gameplay | **Next weapon** (not the settings UI) | — |

Default rows and screenshot: [README](../README.md#vr453-features-how-to-use-them).

---

## Keyboard & mouse (flat / monitor)

Use **`Play-on-monitor.bat`**. Mouse look is on by default (`GETV_MOUSE=0` turns it off).

| Input | Action |
|---|---|
| **Mouse move** | Look / turn |
| **Left mouse button** | Fire |
| **Right mouse button** | Aim / ADS |
| **W A S D** | Walk |
| **Arrow keys** | Turn (mapped like the right stick) |
| **Space** or **Left Ctrl** | Fire |
| **Q** | Aim |
| **E** or **F** | USE / reload / activate (**B** on the virtual pad) |
| **R** or **Enter** | Next weapon |
| **X** (pad right shoulder key mapping) | Previous weapon when bound (`GETV_BIND_WEAPON_PREV`) |
| **Z / X** | Left / right shoulder (C-buttons retail mapping) |
| **C** or **Left Shift** | Crouch (hold) |
| **V** | Stand (hold) |
| **Tab** or **Numpad Enter** | Pause / start |
| **I J K L** | D-pad |
| **Home** | Recenter (VR chord equivalent when using a headset) |
| **Esc** | Release mouse cursor |

Weapon **previous** on keyboard follows `GETV_BIND_WEAPON_PREV` (shipped VR profile uses **X** on the virtual pad = left-controller **X** in VR).

---

## Reload, pause, and menus

- **Gun reload (VR):** [reload gesture](#reload-gesture-vr) — magazine, chest cross, or handle grab; **no auto-reload**.
- **B** (right hand in VR) is the retail **USE** / **activate** button — doors, gadgets, plant, and other **B** actions; **not** VR gun reload.
- **Menu** opens pause in headset; **Tab** on keyboard.
- In the **pause watch**, **left stick** moves the menu highlight in VR; **GAME OPTIONS** continues past **ratio** — scroll down for VR settings (**scroll down - vr settings below**).
- Die / continue should no longer dump you in junk space ([#38](https://github.com/no6969el/GEVR/issues/38)). If it still breaks, quit, run the bat again, and report it.

---

## Getting VR working

GEVR uses **OpenXR**. Current zip: [README Install](../README.md#install-vr453) / [`GEVR-Beta-vr453-win64.zip`](https://github.com/no6969el/GEVR/releases/download/vr453/GEVR-Beta-vr453-win64.zip).

**Verified:**

- **Pimax Crystal Super + SteamVR OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR) (sboys3). We do not maintain that driver. We do support this experience.
- **Native PimaxXR**
- **Quest 3 + Virtual Desktop OpenXR (VDXR)**

**Headset recipe:** unzip **`GEVR-Beta-vr453-win64.zip`**, run **`Start-GEVR.bat`**, point at your USA `.z64`, put the headset on, recenter with both stick clicks.

**No headset:** **`Play-on-monitor.bat`** (flat 2D, no OpenXR).

### If controls or VR feel dead

1. Launch with **`Start-GEVR.bat`** (headset) or **`Play-on-monitor.bat`** (flat), not bare `goldeneye.exe`
2. Recenter with **both** stick clicks
3. Confirm Windows is handing GEVR the OpenXR runtime you think it is
4. File an Issue with **headset**, **OpenXR runtime**, **SteamVR on/off**, **HMD vs monitor**, and **Start-GEVR.bat yes/no**. [CONTRIBUTING](../CONTRIBUTING.md).

Do not upload your ROM.
