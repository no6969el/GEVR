# Controls (Beta)

How to move, aim, shoot, and use Bond’s watch in **[GEVR Beta vr454](https://github.com/no6969el/GEVR/releases/latest)**.

Install first: [README Install](../README.md#install). **Controls video:** [YouTube walkthrough](https://www.youtube.com/watch?v=Jst5srE6Iwc) (also on the [README](../README.md#vr-actions)). Download: [`GEVR-Beta-vr454-win64.zip`](https://github.com/no6969el/GEVR/releases/download/vr454/GEVR-Beta-vr454-win64.zip). The zip has no ROM and no HD texture pack. Tester notes: [BETA.md](BETA.md). What changed: [README vr454](../README.md#vr454) · [FEATURES.md](../FEATURES.md). How to report: [CONTRIBUTING.md](../CONTRIBUTING.md).

## Which bat

- **Headset:** `Start-GEVR.bat` — VR picture, recenter, stick-turn, then GevrRomStarter.
- **Monitor / no headset:** `Play-on-monitor.bat` — flat on the monitor, no stereo eyes. Also the path for **local split-screen**. You can also choose **Flat** under **GEVR Settings** and **Apply**. Apply saves and relaunches into that mode.

Use those bats from **`GEVR-Beta-vr454-win64.zip`**. Do not double-click `goldeneye.exe`.

## Default layout (OpenXR)

| Hand | Role |
|---|---|
| **Right controller** | Gun hand — fire, aim, **A** next weapon, **B** reload animation, turn stick |
| **Left controller** | Walk hand — move stick, **X** previous weapon, watch cuff on the arm |

**Meta Quest / Touch**, **Valve Index**, and other **Oculus-style OpenXR** profiles use the same actions. Only the printed names on the plastic differ.

Auto-Aim defaults **off** in this build.

---

## Meta Quest / Touch (stereo VR)

| Control | Action |
|---|---|
| **Right trigger** | Fire the gun in your **right** hand |
| **Left trigger** | Fire the gun in your **left** hand. A left-hand gun fires on its own. You do not need a second gun. |
| **Right grip (squeeze)** | **Aim** along the gun. The aim mark sits on the weapon, not glued to your face. |
| **Right grip at a door** | **Open or close** the door when you are in range |
| **Right grip on your left watch face** | **Cuff grab** — detonate planted remotes, or fire the watch laser. See [Bond’s watch](#bonds-watch--cuff). |
| **Grip a gun, then release** | **Hip holster.** Grip to hold. Release to put the gun on your hip. |
| **Left grip (squeeze)** | **Aim** when that hand holds a gun. Near a door or a pickup, same rules as the right grip for that hand. |
| **Left grip near a dropped weapon** | **Pick up** into **that** hand |
| **Left grip near your own stuck mine** | **Pick the mine back up** (remote mines and arming proximity mines you placed) |
| **Left grip on a two-handed gun’s fore-end** | **Two-hand support.** Hold the left controller along the barrel and squeeze. A rifle, shotgun, SMG, or grenade launcher in the right hand aims along both grips. Release to aim from the right wrist only. |
| **Left stick** | Walk and strafe |
| **Right stick** | Turn. **Smooth** or **Snap** is on the watch, under **GAME OPTIONS**, past ratio. |
| **Both stick clicks together** | **Recenter** the playspace. One stick alone does nothing. |
| **Right stick up or down while aiming** | Stand or crouch |
| **Left stick while aiming** | Walk forward and back |
| **Right A** | **Next weapon** on the **right** hand |
| **Left X** | **Previous weapon** on the **left** hand |
| **Right B** | **Reload animation** on a gun. B also plants and activates where GoldenEye uses that button. |
| **Chest swipe, or a grab on the magazine** | Refill with a **click** and no animation. See [Reload](#reload). |
| **Grab the handle** | **Swap hands.** This does not reload. |
| **Menu** (left controller) | Open the watch |
| **Y** | Open the watch |
| **Head / room-scale** | Look around. Walk your room to move in the mission. |
| **Swing the weapon in your hand** | Melee. The hit uses that weapon’s damage. Shooting does not swing the knife for you. |

**Dual-wield** is one gun in each hand. **Left trigger** fires the left gun. **Right trigger** fires the right gun. A single gun in the left hand still fires with the left trigger.

**Grenades, remote mines, proximity mines, and timed mines** draw in the hand the same way. The weapon picture, including the grenade and the mines, sits on the hand that is lifting it. **Trigger** throws or fires. After you plant a mine, use the grip to pick your own stuck mine back up when the game allows it.

A new gun goes to your hip, and the old gun goes to your inventory. An empty gun stays in your hand. Grenades, mines, and gadgets still switch away when you use them up.

You cannot put the same non-dual gun in both hands unless GoldenEye would allow that pair.

---

## Valve Index (stereo VR)

Same actions as Quest. Index names:

| Index control | Same as Quest | Action |
|---|---|---|
| **Right trigger** | Right trigger | Fire the right-hand gun |
| **Left trigger** | Left trigger | Fire the left-hand gun |
| **Right grip** | Right grip | Aim, door, cuff grab, hip holster |
| **Left grip** | Left grip | Aim the left gun, door, pickup, mine regrab, two-hand support |
| **Right thumbstick** | Right stick | Turn. With the sniper, forward or back steps the zoom. |
| **Left thumbstick** | Left stick | Walk |
| **Right A** | Right A | Next weapon on the right hand |
| **Right B** | Right B | Reload animation. Also plant and activate. |
| **Left X** | Left X | Previous weapon on the left hand |
| **Left Y** | Y | Open the watch |
| **System button** | Quest **Menu** | Open the watch |

---

## Bond’s watch & cuff

The left cuff is the watch. It stays on your left arm. Press **Y** to open it. The **Menu** button opens it too.

There is no detonator in the weapon cycle. **Left X** and **Right A** change guns. They do not select a detonator.

### GAME OPTIONS

Open **GAME OPTIONS** on the watch. The sheet goes past ratio. Scroll down with the **left stick**. The last line says to scroll down for VR settings. Turn speed, turn style, snap size, and the related rows sit below ratio.

### Cuff grab

Touch the left watch face with your right controller and squeeze.

- If you have planted remote mines, the cuff grab detonates them.
- If none are planted, the watch laser comes from the cuff.

### Watch magnet

1. On the pause watch, select **Watch Magnet Attract**. You keep your guns in hand.
2. Touch the left cuff with your right hand and squeeze.

That spends watch magnet ammo and runs one attract pulse. With no ammo you get an empty click. Select magnet again when you want another pulse.

**Watch Magnet Repel** is still chosen from the pause watch, the same way as retail GoldenEye. There is no separate cuff shortcut for repel.

---

## Weapons and holster

| Control | Action |
|---|---|
| **Right A** | **Next** weapon on the **right** hand |
| **Left X** | **Previous** weapon on the **left** hand |
| **Grip pickup** | Squeeze near a weapon on the ground to put it in **that** hand |
| **Grip, then release** | Grip to hold the gun. Release to holster it on your hip. |

A new gun goes to the hip. The old gun goes to your inventory. An empty gun stays in the hand. Grenades, mines, and gadgets still switch away when you use them up.

**Two-handed rifles, shotguns, SMGs, and the grenade launcher:** hold with the right hand, bring the left grip to the fore-end, and squeeze. Let go to aim from the right wrist only.

### Ammo and weapon pictures

Ammo digits sit on the grip. Read them from behind the gun. Flat mode on the monitor keeps the count in the corner.

The weapon picture sits on the lifting hand. That includes the grenade and the mines. Remote, proximity, and timed mines draw in the hand like the grenade.

### Swing

A swing uses the damage of the weapon you are holding. Shooting does not make the knife swing by itself.

### Bullet spread and rockets

Bullet spread stays around the controller aim. Rockets, the grenade launcher, and the watch laser are unchanged.

Rockets stay on the gun, with a flat crosshair.

### Sniper

A green dot stays on. The shot leaves your eye along that dot. Push the right stick forward or back to step the zoom through **30**, **20**, **15**, **10**, and **7**. Walking does not zoom. The right-hand sniper hides the red crosshair. The left-hand green aimer is not in this build.

---

## Reload

Guns do not reload on their own.

| What you do | What happens |
|---|---|
| **B** | Plays the **reload animation** |
| **Chest swipe**, or a **grab on the magazine** | Refills with a **click** and no animation |
| **Grab the handle** | **Swaps hands.** Does not reload. |

Pistols and guns with no magazine, including the shotgun, reload from the **chest**. Guns with the magazine on top or on the bottom, including the Uzi, reload from the **magazine**.

**B** also plants and activates where GoldenEye uses that button.

---

## Tank

- Walk onto the **tank chassis** to mount.
- **Right stick up or down** aims the cannon elevation.
- Get off the way GoldenEye already does. There is no separate enter button.

---

## Recenter

Press **both thumbstick clicks at the same time**.

Also works:

- **Xbox gamepad:** both stick clicks together
- **Keyboard:** `Home` while the game window has focus

After you recenter, turning your head while you stand still should not slide the world. Walking in your room moves you in the mission.

---

## GEVR Settings and the pause watch

| | **GEVR Settings** | **Pause watch** (in a mission) |
|---|---|---|
| Where | **Mission Select**, next to **Select Mission**, **Multiplayer**, and **Cheat Options**. The name is **GEVR Settings**. It is not named Options. | Press **Y** or **Menu** |
| How | **A** selects a row. Stick **left / right** changes the value. **Apply** saves and relaunches. | **Left stick** moves the highlight. Face buttons confirm. |
| **A** while you play | **Next weapon** on the right hand | — |
| **X** while you play | **Previous weapon** on the left hand | — |

Picture choices, including VR, XR, and Flat: [README vr454](../README.md#vr454) and [GEVR Settings](GEVR-SETTINGS.md).

---

## Keyboard and mouse (flat / monitor)

Use **`Play-on-monitor.bat`**, or choose **Flat** in GEVR Settings and Apply. Mouse look is on.

| Input | Action |
|---|---|
| **Mouse move** | Look / turn |
| **Left mouse button** | Fire |
| **Right mouse button** | Aim |
| **W A S D** | Walk |
| **Arrow keys** | Turn |
| **Space** or **Left Ctrl** | Fire |
| **Q** | Aim |
| **E** or **F** | Use / activate |
| **R** or **Enter** | Next weapon |
| **X** | Previous weapon |
| **Z / X** | Left / right shoulder |
| **C** or **Left Shift** | Crouch (hold) |
| **V** | Stand (hold) |
| **Tab** or **Numpad Enter** | Open the watch |
| **I J K L** | D-pad |
| **Home** | Recenter |
| **Esc** | Release the mouse cursor |

Flat mode keeps the ammo count in the corner.

---

## Getting VR working

GEVR uses **OpenXR**. Current zip: [README Install](../README.md#install) / [`GEVR-Beta-vr454-win64.zip`](https://github.com/no6969el/GEVR/releases/download/vr454/GEVR-Beta-vr454-win64.zip). Bring your own USA GoldenEye ROM. The zip does not include one.

**Verified:**

- **Pimax Crystal Super + SteamVR OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR) (sboys3). We do not maintain that driver. We do support this experience.
- **Native PimaxXR**
- **Quest 3 + Virtual Desktop OpenXR (VDXR)**

**Headset:** unzip **`GEVR-Beta-vr454-win64.zip`**, run **`Start-GEVR.bat`**, point at your USA `.z64`, put the headset on, and recenter with both stick clicks.

**No headset:** **`Play-on-monitor.bat`**, or **Flat** in GEVR Settings.

### If controls or VR feel dead

1. Launch with **`Start-GEVR.bat`** (headset) or **`Play-on-monitor.bat`** (flat). Do not use bare `goldeneye.exe`.
2. Recenter with **both** stick clicks.
3. Confirm Windows is handing GEVR the OpenXR runtime you think it is.
4. File an Issue with headset, OpenXR runtime, SteamVR on or off, headset or monitor, and whether you used **Start-GEVR.bat**. [CONTRIBUTING](../CONTRIBUTING.md).

Do not upload your ROM.
