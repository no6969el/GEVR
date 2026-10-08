# GEVR Player Manual

**GoldenEye VR on PC**

This manual ships with the download. It is the directions for the VR controls that work in the current public Beta (vr452.4).

A short video of the same controls is on YouTube: [How to control GEVR in VR](https://www.youtube.com/watch?v=Jst5srE6Iwc). Use the video as a quick look. The steps below are the full directions.

Bring a USA *GoldenEye 007* ROM you already own (a `.z64` file). The zip does not contain a ROM.

---

## Contents

1. [Start the game](#1-start-the-game)
2. [Hands](#2-hands)
3. [Valve Index names](#3-valve-index-names)
4. [Move, look, and recenter](#4-move-look-and-recenter)
5. [Fire, aim, and use](#5-fire-aim-and-use)
6. [Two hands on a long gun](#6-two-hands-on-a-long-gun)
7. [Hip holster](#7-hip-holster)
8. [Throwables and mines](#8-throwables-and-mines)
9. [Bond’s watch](#9-bonds-watch)
10. [Tank](#10-tank)
11. [GEVR Settings](#11-gevr-settings)
12. [HD textures](#12-hd-textures)
13. [Keyboard and mouse](#13-keyboard-and-mouse)
14. [If VR feels half speed](#14-if-vr-feels-half-speed)
15. [Help](#15-help)

---

## 1. Start the game

1. Unzip the download anywhere on the PC.
2. For a headset, run **`Start-GEVR.bat`**.
3. For a monitor, or for local split-screen, run **`Play-on-monitor.bat`**.
4. When the starter asks, point it at your USA `.z64`.
5. The first launch builds the picture cache from that ROM. Wait until it finishes.
6. Put the headset on. Recenter by pressing **both thumbstick clicks at the same time**.
7. On the intro hub, **look right**. The glass panel there is **GEVR Settings**.

`Start-GEVR.bat` sets the VR options and opens GevrRomStarter. Start from that bat for headset play. Starting from `goldeneye.exe` alone can skip the ROM cache update and leave VR input off.

A new install prepares the pictures once, then you play. Saves start empty.

After an update, keep the same USA `.z64`. Saves and GEVR Settings stay in `%LOCALAPPDATA%\GEVR`. You can also choose **Update** inside GevrRomStarter. If the picture is wrong, run **`Clear-GEVR-cache.bat`** from the zip folder and type **YES**. That clears the picture cache and keeps your saves.

Auto-aim is off.

---

## 2. Hands

| Hand | Job |
|---|---|
| **Right controller** | Gun hand. Fire, aim, **A** / **B**, and the turn stick. |
| **Left controller** | Walk hand. The watch cuff stays on this arm. **X** steps this hand’s weapon. |

Meta Quest / Touch, Valve Index, and other Oculus-style OpenXR controllers share these actions. The words printed on the plastic change. Index names are in the next section.

An empty hand shows a small cube. The cube hides while that hand holds a weapon.

Head look and room-scale walking move you in the mission. The gun stays with the hand that holds it.

---

## 3. Valve Index names

Index uses the same actions as Quest. Read the left column when the controllers are Index controllers.

| Index control | Quest name | Action |
|---|---|---|
| **Right trigger** | Right trigger | Fire the gun in the right hand |
| **Left trigger** | Left trigger | Fire the gun in the left hand |
| **Right grip (A button grip)** | Right grip | Aim, door, watch press, hip holster |
| **Left grip** | Left grip | Aim a left-hand gun, door, mine regrab, two-hand support on a long gun |
| **Right thumbstick** | Right stick | Turn |
| **Left thumbstick** | Left stick | Walk |
| **Right A** | Right A | Next weapon |
| **Right B** | Right B | Use, reload, plant, activate |
| **Left X** (face button) | Left X | Previous weapon |
| **Left Y** | Left Y | Pause |
| **System / menu button** | Menu | Pause |

The **grip** is the squeeze of the handle. On the right Index controller that squeeze is the **A button grip**. The **A** face button is a different control: it steps to the next weapon. **B** is use and reload.

The left Index controller may not print X and Y on the plastic. In GEVR those face buttons are still **Left X** (previous weapon) and **Left Y** (pause). The system button pauses as well.

Press both thumbstick clicks together to recenter.

---

## 4. Move, look, and recenter

| Control | What you do |
|---|---|
| **Left stick** | Walk and strafe |
| **Right stick** | Turn. Smooth or Snap is chosen in **GEVR Settings**. |
| **Head** | Look around |
| **Room-scale** | Walk in your room to move in the mission |
| **Both thumbstick clicks** | Recenter the playspace |
| **Right stick up / down while aiming** | Stand or crouch |
| **Left stick while aiming** | Walk forward and back |

Recenter details:

- Press **both** thumbstick clicks at the same time (L3 + R3 together).
- On an Xbox pad, press both stick clicks together.
- On the keyboard, press **Home** while the game window has focus.

After a recenter, turning your head while you stand still should leave the world in place. Walking in the room moves you in the mission.

While the grip is held for aim, the right stick stands you up or crouches you. The left stick still walks. Walking backward on that stick keeps you at your current height.

Swing an empty hand, or a melee weapon, to strike.

---

## 5. Fire, aim, and use

### Per-hand fire

- **Right trigger** fires the gun in the **right** hand.
- **Left trigger** fires the gun in the **left** hand.

Each hand keeps its own weapon. In dual-wield, put a second gun in the left hand by stepping that hand’s list, then fire each gun with its own trigger.

- **Right A** steps the **right-hand** weapon to the next one.
- **Left X** steps the **left-hand** weapon to the previous one.

You can hold the same gun in both hands only when the original game would allow that pair.

The rocket launcher stays on the gun. A flat crosshair sits on the rocket’s path.

### Aim

Squeeze the **grip** on the hand that holds the gun. That is aim / ADS. The aim mark sits on the gun’s ray, out along the weapon.

### Doors

Squeeze the grip when that hand is at a door and you are close enough. The same squeeze opens or closes the door.

**Right B** still uses doors and switches at range, reloads, plants, and activates. **B** is the action button, the same as in the original game. Use, reload, and activate share that one press.

### Throw on the trigger

Grenades, mines, plastique, and the covert modem appear in the hand. The **trigger** throws or fires. **B** plants, activates, or reloads where the original game does.

---

## 6. Two hands on a long gun

Use this on a **rifle, shotgun, submachine gun, or grenade launcher** held in the **right** hand.

1. Keep the gun in the right hand.
2. Bring the **left** controller to the fore-end, along the barrel.
3. Squeeze the **left grip**.

While that squeeze is held, the gun aims along the line between the two grips. Release the left grip to aim from the right wrist only.

---

## 7. Hip holster

1. Drop the **right** hand to the **right hip** (gun hand low).
2. Squeeze the **right grip**.
3. Keep the **left** hand empty. The cuff may stay on that arm.

The squeeze stashes the right-hand gun at the hip and brings out Bond’s fist. Squeeze at the hip again to draw the stashed gun.

---

## 8. Throwables and mines

Grenades, timed mines, remote mines, proximity mines, plastique, and the covert modem show in the hand. They leave from the grip when you pull the trigger. **B** plants or activates where the original game uses B.

### Take your own mine back

After you throw or plant a mine:

1. Put the **left** controller near **your own** mine that is stuck in the world.
2. Squeeze the **left grip**.

This picks the mine back up. It works for **remote mines** and for **proximity mines you placed that are still arming**. Leave live grenades and armed traps where they are.

---

## 9. Bond’s watch

The **left cuff is the watch**. It stays on the left arm. Hands stay visible while you use the laser, the detonator, or the magnet.

### Open the pause watch

1. Press **Menu** on the left controller. On Index, press the **system / menu button**. **Left Y** also pauses in the shipped profile.
2. Move the highlight with the **left stick**.
3. Confirm a gadget or a mode with the face buttons, the same way the original watch pages work.

From this menu, choose **Watch Laser**, **Detonator**, **Watch Magnet Attract**, **Watch Magnet Repel**, or another item the mission gave you.

On the keyboard, **Tab** or **Numpad Enter** pauses.

### Watch Laser and Detonator

Pick one of these in the pause watch **before** you press the cuff. The cuff press then follows that choice.

**Watch Laser.** A cuff press fires the **laser only**.

**Detonator.** A cuff press **detonates your planted remote mines** when any are active. When none are active, that same press fires the **watch laser** from the cuff.

If the mission does not give you a laser, a **Watch Laser** row can still appear in the list during solo play.

### Cuff press

Do this in the mission, while the watch is closed (the watch is not opening on screen).

1. Touch the **left watch face** with the **right** hand.
2. Squeeze the **right grip**.
3. Make it a **new** squeeze. A squeeze you were already holding when the hand arrived on the watch does not count.

The result is whatever you selected: laser only, detonate-or-laser, or magnet attract (below).

### Watch Magnet Attract

1. Open the pause watch and select **Watch Magnet Attract**. Your guns stay in your hands. Your hands stay visible.
2. Close the watch and return to the mission.
3. Touch the **left watch cuff** with the **right** hand and **squeeze**. This is the same gesture as the watch laser.

That spends watch-magnet ammo and runs **one attract pulse**. The pulse pulls metal the way the original magnet does. With no ammo, the cuff gives an empty click.

When you want another pulse, open the pause watch and select **Watch Magnet Attract** again.

### Watch Magnet Repel

**Watch Magnet Repel** is the normal watch item. Open the pause watch, choose **Watch Magnet Repel**, and use it from that menu the way the original game does.

---

## 10. Tank

1. Walk onto the tank chassis. You mount on your own.
2. Move the **right stick up or down** to pitch the cannon.
3. Get off by leaving the tank the way you do in the original game.

---

## 11. GEVR Settings

GEVR Settings is the glass panel on your **right** on the intro hub. Picture, monitor, and profile options live here. The pause watch is a different menu, used inside a mission.

In a mission, **A** is next weapon. On this hub menu, **A** edits rows.

### Change a row

1. Move **up or down** until the row you want is highlighted.
2. Press **A** to enter that row.
3. Move the stick **left or right** to cycle the value.
4. Press **A** to accept the value.

The edit is stored when you Apply.

### Apply

1. Highlight **Apply** (Save+Restart).
2. Press **A**.

The game saves and restarts. That restart is how picture size, filter, HD textures, and Visual mode take effect.

### Visual mode

**Visual mode** is **VR**, **XR**, or **Flat**. Each mode keeps **its own saved settings**. To edit a different profile, switch Visual mode, change the rows, then Apply.

| Mode | Use it for |
|---|---|
| **VR** | Everyday headset play. Full VR. |
| **XR** | Headset play with a clean square outline, a framed picture. |
| **Flat** | Desk or couch on a monitor. No headset. |

After you pick a mode, highlight **Apply** and press **A**, then wait for the relaunch.

To return to full VR later, set Visual mode to **VR** and Apply.

### Rows in this Beta

The sheet below is the starting example. Your sheet changes after you edit it.

| Row | Starting example |
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

**Supersample.** Starts at **3 Sharp**. Enter the row, cycle left or right, accept with A, then Apply. This is the sharpness of the VR picture.

**Frame rate.** The default is **Headset**. Leave **Headset** selected for headset play so the game follows the headset. Frame rate and Game speed are two different rows. Game speed starts at **Smooth 90** on this sheet. On flat / monitor play, frame rate can follow the monitor, and game speed can be **Original 60** or **Smooth 90**.

**Monitor.** While Visual mode is **VR** or **XR**, this row is the desktop picture. Cycle it through:

- **Both** — both eyes
- **Left** — left eye
- **Right** — right eye
- **Off** — no desktop picture

Press A to accept, then Apply. The choice is **saved** with the **VR** profile and the **XR** profile. It is not part of the flat profile. In **Flat**, the Monitor row is greyed out. The starting example on the VR sheet reads **On** until you change it.

**Full screen, Window, and Filter.** Full screen starts **Off**. The window starts at **1280×960**. Filter starts at **Bilinear**. Change them with the same A / left-right / A steps, then Apply.

**Beta.** The row reads **None yet**. This Beta has no test options on that row.

**Reset defaults.** Highlight **Reset defaults**, confirm **Yes**, and read the “are you sure” prompt. The restore follows the Visual mode you are in:

- **Flat** restores flat defaults (monitor rate, full screen, classic speed).
- Any other Visual mode restores VR defaults (supersample 3, frame rate follows the headset, bilinear, HD textures off, Visual mode VR).

Highlight **Apply** and press **A** when you want that restore to relaunch now.

---

## 12. HD textures

**HD textures** starts **Off**. The game is meant to be played that way until you add a pack. GEVR does not ship the pictures.

To turn them on:

1. Download the community **GLideN64 PNG** zip. Use the PNG zip, not the `.hts` file.
   - [GoldenEye-007-HD releases](https://github.com/GhostlyDark/GoldenEye-007-HD/releases)
   - [GE007 HD texture pack page](https://evilgames.eu/texture-packs/ge007-hd.htm)
2. Extract it so the **`GOLDENEYE`** folder sits inside a folder named **`hdtextures`**.
3. Put **`hdtextures`** beside `goldeneye.exe` (the same folder as the game).
4. Leave the picture file names as they are.
5. In **GEVR Settings**, enter **HD textures** and set it to **On**.
6. Press **A** to accept, then highlight **Apply** and press **A**.
7. Play on the **next boot**, after that restart.

---

## 13. Keyboard and mouse

Run **`Play-on-monitor.bat`**. Mouse look is on. `GETV_MOUSE=0` turns mouse look off.

| Input | Action |
|---|---|
| **Mouse move** | Look / turn |
| **Left mouse button** | Fire |
| **Right mouse button** | Aim |
| **W A S D** | Walk |
| **Arrow keys** | Turn (same job as the right stick) |
| **Space** or **Left Ctrl** | Fire |
| **Q** | Aim |
| **E** or **F** | Use, reload, activate (**B**) |
| **R** or **Enter** | Next weapon |
| **X** | Previous weapon when `GETV_BIND_WEAPON_PREV` is in use (left-controller **X** in VR) |
| **Z / X** | Left / right shoulder (original C buttons) |
| **C** or **Left Shift** | Crouch (hold) |
| **V** | Stand (hold) |
| **Tab** or **Numpad Enter** | Pause |
| **I J K L** | D-pad |
| **Home** | Recenter |
| **Esc** | Release the mouse cursor |

---

## 14. If VR feels half speed

Turn off the runtime’s motion smoothing. These switches are in the headset software, not in GEVR Settings.

- **SteamVR:** Settings → Video → **Motion Smoothing** off. Also check Applications for GEVR / `goldeneye.exe`.
- **Virtual Desktop:** **Space Warp** off.

---

## 15. Help

- Controls video: [How to control GEVR in VR](https://www.youtube.com/watch?v=Jst5srE6Iwc)
- The same binds, in short form: [docs/CONTROLS.md](../CONTROLS.md)
- Discord: [discord.gg/flat2vr](https://discord.gg/flat2vr)
- Bug report: [New Issue](https://github.com/no6969el/GEVR/issues/new/choose)

When you report a problem, include the headset, the OpenXR runtime, whether SteamVR was on, whether you were in the headset or on the monitor, and whether you used `Start-GEVR.bat`. If the game closes hard, copy the first lines of any `gevr-fault-*.txt` beside `goldeneye.exe`. Leave the ROM on your PC.
