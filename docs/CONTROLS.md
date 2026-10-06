# Controls (Beta)

How to move, aim, shoot, and use Bond's watch in **[GEVR Beta vr456.3](https://github.com/no6969el/GEVR/releases/latest)**.

Install first: [README Install](../README.md#install). **Controls video:** [YouTube walkthrough](https://www.youtube.com/watch?v=Jst5srE6Iwc) (also on the [README](../README.md#vr-actions)). Download: [`GEVR-Beta-vr456.3-win64.zip`](https://github.com/no6969el/GEVR/releases/download/vr456.3/GEVR-Beta-vr456.3-win64.zip). The zip has no ROM and no HD texture pack. Tester notes: [BETA.md](BETA.md). What vr456.3 adds: [README](../README.md#vr4563) · [FEATURES.md](../FEATURES.md). How to report: [CONTRIBUTING.md](../CONTRIBUTING.md).

## Which bat

- **Headset:** `Start-GEVR.bat` (VR picture, then GevrRomStarter).
- **Monitor / no headset:** `Play-on-monitor.bat` (flat picture, no stereo eyes). Also the path for **local split-screen**.

Use those bats from **`GEVR-Beta-vr456.3-win64.zip`**. Do not double-click `goldeneye.exe`. A bare exe can skip the ROM cache update and leave VR input off.

You can also switch picture from **GEVR Settings**: set Visual mode to **VR**, **XR**, or **Flat**, then **Apply**. Apply saves and relaunches into that mode.

## Default layout (OpenXR)

GEVR uses the usual FPS layout:

| Hand | Role |
|---|---|
| **Right controller** | Gun hand. Fire, aim, **A** next weapon, **B** reload button, comfort turn stick, stick click for the weapon wheel |
| **Left controller** | Walk hand. Move stick, **X** next weapon, **Y** opens the watch, cuff on the arm |

**Meta Quest / Touch**, **Valve Index**, and other **Oculus-style OpenXR** profiles use the same actions. Only the names printed on the plastic differ.

Auto-aim starts **off**.

---

## Meta Quest / Touch (stereo VR)

| Control | Action |
|---|---|
| **Right trigger** | Fire the gun in your **right** hand |
| **Left trigger** | Fire the gun in your **left** hand. A left-hand gun fires on its own, not only when you dual-wield |
| **Right grip (squeeze)** | **Aim** along the gun. The aimer sits on the first thing the shot hits |
| **Right grip at a door** | **Open / close** the door when you are in range |
| **Right grip on your left watch cuff** | **Cuff grab.** Detonates planted remotes. If none are planted, the watch laser comes from the cuff |
| **Grip, then release** | **Hip holster.** Grip holds the gun, release holsters it. Same-gun hip grip swaps sides |
| **Left grip (squeeze)** | **Aim** when that hand holds a gun. Near a door or a pickup, same rules as the right grip for that hand |
| **Left grip near a dropped weapon** | **Pick up** into **that** hand |
| **Left grip near your own stuck mine** | **Pick the mine back up** (remote mines and arming proximity mines you placed) |
| **Left grip on a two-handed gun's fore-end** | **Two-hand support.** Hold the left controller along the barrel and squeeze. The right-hand rifle, shotgun, or SMG aims along the line between both grips. Release to go back to one-hand aim |
| **Left stick** | Walk and strafe |
| **Right stick** | Turn in-game (**Smooth** or **Snap** from pause **VR Settings**) |
| **Stick click** | **Weapon wheel** (circle default). Pause **VR Settings** row **STICK WHEEL** can set **Weapon Vert** instead |
| **Both stick clicks together** | **Recenter** the playspace |
| **Right stick up / down while aiming** | Stand / crouch |
| **Left stick while aiming** | Walk forward and back |
| **Right A** | **Next weapon** on the **right** hand |
| **Left X** | **Next weapon** on the **left** hand. Prefers a free inventory copy over the hip gun |
| **Right B** | **Reload button.** Reloads any gun the normal way. You do not have to use a gesture. Also doors, switches, plant, and activate |
| **Y** | **Opens the watch** |
| **Menu** (left controller) | Also opens the pause watch |
| **Head / room-scale** | Look around. Walk your room to move in the level |
| **Swing the held weapon** | Melee. The swing uses that weapon's damage. Shooting does not make the knife swing by itself |

**Dual-wield** is only when you hold **two guns**. Put a second gun in the left hand with **Left X**, **Right A**, a hip swap, or a pickup. Each trigger fires its own hand.

**Throwables** (grenades, timed mines, remote mines, proximity mines, plastique, covert modem): they appear in the hand. The trigger throws or fires. **B** plants and activates where GoldenEye already uses that button. Remote, proximity, and timed mines draw in the hand like the grenade. After you plant a mine, use the grip to pick your own stuck mine back up when the game allows it. Left-hand throwables sit the same way as the right. Bomb case and plastique included.

---

## Valve Index (stereo VR)

Same bindings as Quest. Index names:

| Index control | Same as Quest | Action |
|---|---|---|
| **Right trigger** | Right trigger | Fire the right gun |
| **Left trigger** | Left trigger | Fire the left-hand gun |
| **Right grip** | Right grip | Aim; door; cuff grab; hold the gun |
| **Left grip** | Left grip | Aim (left gun); door; pickup; mine regrab; two-hand support |
| **Right thumbstick** | Right stick | Turn. On the sniper, forward or back steps the zoom |
| **Left thumbstick** | Left stick | Walk |
| **Stick click** | Stick click | Weapon wheel (or Weapon Vert) |
| **Right A** | Right A | Next weapon on the right hand |
| **Right B** | Right B | Reload button for any gun; also use / activate |
| **Left X** | Left X | Next weapon on the left hand |
| **Left Y** | Y | Opens the watch |
| **System / menu button** | Quest **Menu** | Also opens the pause watch |

---

## Bond's watch and cuff

The left cuff is the watch. It stays on your left arm. There is no detonator in the weapon cycle.

### Open the watch

Press **Y**. The **Menu** button also opens the pause watch.

Move the highlight with the **left stick**. Confirm with the face buttons, the same way the retail watch pages work.

### GAME OPTIONS

Open **GAME OPTIONS** on the watch. The sheet goes past ratio. Scroll down with the **left stick**. The last line says scroll down for VR settings. The VR rows sit below ratio on that page. That is where **snap-turn** and **STICK WHEEL** live.

### Cuff grab

Touch the left cuff with your right hand and grip.

- If you have planted remote mines, the cuff grab detonates them.
- If you do not, the watch laser comes from the cuff.

### Cuff picker

Look at the cuff. The picker names are **Laser**, **Magnet**, and **Repel**. It does not crash. It does not run dry. Magnet pulls, Laser cuts, Repel shoves, as often as you want.

---

## Weapons and holster

| Control | Action |
|---|---|
| **Stick click** | **Weapon wheel** (circle default). **STICK WHEEL** in pause VR Settings can set **Weapon Vert** |
| **Right A** | **Next** weapon on the **right** hand |
| **Left X** | **Next** weapon on the **left** hand |
| **Grip pickup** | Squeeze near a weapon on the ground to equip it to **that** hand |
| **Grip, then release** | Grip **holds** the gun. Release **holsters** it at the hip. Same-gun hip grip **swaps** |

Drop the same gun onto a hip that already has one and they swap sides. With All Guns on, cycle to a gun that is on your hip and the empty hand gets a second copy. The holster keeps its own. The cycle would rather hand you a gun from inventory than steal the one on your hip.

A new gun goes to the hip, and the old gun goes to inventory. An empty gun stays in the hand. Grenades, mines, and gadgets still switch away when they are used up.

You cannot put the same non-dual gun in both hands unless the retail game would allow that pair.

**Two-handed rifles, shotguns, SMGs, and the grenade launcher:** hold with the right hand. Bring the left grip to the fore-end and squeeze to steady the aim. Let go to aim from the right wrist only.

Weapon pictures sit on the lifting hand, including the grenade and mines.

### Weapon wheel

Click the stick. A big dark-grey circle of guns opens at your hand. The picture in the middle is the one you are hovering, not the last gun you used. Let go to pick it.

Want the old up-and-down list? Pause, open **VR Settings**, find **STICK WHEEL**, set **Weapon Vert**. Switch back to **Weapon wheel** the same way. No restart. The next stick click uses the style you picked.

### Ammo

In VR, the ammo digits sit on the grip. You read them from behind the gun. Flat mode keeps the count in the corner.

---

## Reload

You do not have to reload by hand. Press **B**, the reload button, and any gun reloads the normal way.

You can also hold any gun to your upper chest and press the grab button to reload it. On a gun with a visible magazine, grab that magazine with the grip button to reload it.

Pistols, the shotgun, the sniper, and other guns with no visible magazine reload across the chest, or with **B**.

Grabbing the handle swaps hands and does not reload. Handheld guns do not reload on their own. **Tanks** auto-reload the next round after you fire.

**B** still covers switches, plant, and activate where GoldenEye uses that button.

---

## Sniper and Moonraker

The red and green aimer sits on the first thing the shot hits. The hole is under the dot, not beside your head. Left-handed sniper works the same as the right.

Push the **right stick forward or back** to step the zoom. The steps are **30**, **20**, **15**, **10**, and **7**. Walking does not zoom.

**Moonraker:** small circular scope lens only. No big front grill screen. Dual-wield two Moonrakers and you get two lenses, one on each gun. Look through the ring. That is where the shot goes. Left-handed Moonraker works the same as the right.

---

## Aim

Point the controller. Bullet spread stays around that aim. The aimer sits on the first hit.

Rockets stay locked to the launcher, not your head.

A swing uses the damage of the weapon you are holding. Firing does not swing the knife for you.

You stay planted. Sprinting does not bounce your view. No walk bob, no landing dip, no gun-hand sway.

---

## Tank

- Walk onto the **tank chassis** to mount.
- **Right stick up / down** aims the cannon elevation.
- Climb in and shoot. The tank tops itself up.
- Get off the way the retail game does. There is no separate enter button.

---

## Recenter

**Press both thumbstick clicks at the same time.**

A single stick click is the weapon wheel, not recenter.

Also works:

- **Xbox gamepad:** both stick clicks together
- **Keyboard:** `Home` while the game window has focus

After you recenter, turning your head while you stand still should not slide the world. Walking in your room moves you in the level.

---

## GEVR Settings and the pause watch

**GEVR Settings** is on **Mission Select**, next to **Select Mission**, **Multiplayer**, and **Cheat Options**. It is not named Options. Look right on the intro hub too.

| | **GEVR Settings** | **Pause watch** (in a mission) |
|---|---|---|
| Open | Mission Select, then **GEVR Settings** | **Y**, or the **Menu** button |
| Change a row | **A** selects the row. Stick **left / right** changes the value. **A** accepts | **Left stick** moves the highlight. Face buttons confirm |
| Save | **Apply** saves and relaunches into that mode | The watch sheet saves the retail way |
| **A** during play | **Next weapon** on the right hand | (pause watch) |
| **B** during play | Reload button for any gun, plus use / activate | (pause watch) |

Picture choices on that page:

- **Visual mode:** **VR**, **XR** (smaller screen, black outline), or **Flat** on the monitor.
- **Frame rate:** follows the headset by default. **Fixed 90** is still available.
- **Supersample** starts at **3**. **Filter** starts on **bilinear**. **Point** is still available.
- **Monitor:** **Both**, **Left**, **Right**, or **Off**. Off blanks the mirror while you stay in the headset.

Pause **VR Settings** (watch, below ratio):

- **Snap-turn** on or off, plus the angle.
- **STICK WHEEL:** **Weapon wheel** or **Weapon Vert**.

Starting rows and the rest of the how-to: [README](../README.md#vr4563) · [GEVR Settings](GEVR-SETTINGS.md).

---

## Keyboard and mouse (flat / monitor)

Use **`Play-on-monitor.bat`**, or set Visual mode to **Flat** and Apply. Mouse look is on.

| Input | Action |
|---|---|
| **Mouse move** | Look / turn |
| **Left mouse button** | Fire |
| **Right mouse button** | Aim |
| **W A S D** | Walk |
| **Arrow keys** | Turn (same job as the right stick) |
| **Space** or **Left Ctrl** | Fire |
| **Q** | Aim |
| **E** or **F** | Use / activate |
| **R** or **Enter** | Next weapon |
| **X** | Previous weapon |
| **Z / X** | Left / right shoulder (the retail C-buttons) |
| **C** or **Left Shift** | Crouch (hold) |
| **V** | Stand (hold) |
| **Tab** or **Numpad Enter** | Pause / start |
| **I J K L** | D-pad |
| **Home** | Recenter |
| **Esc** | Release the mouse cursor |

Flat mode keeps the ammo count in the corner.

---

## Reload, pause, and menus

- **B** is the reload button. It reloads any gun the normal way. You do not have to use a gesture.
- Hold any gun to your upper chest and press the grab button to reload it.
- On a gun with a visible magazine, grab that magazine with the grip button to reload it.
- Pistols, the shotgun, the sniper, and other guns with no visible magazine reload across the chest, or with **B**.
- Grabbing the handle swaps hands and does not reload.
- Handheld guns do not reload on their own. Tanks do.
- **Y** opens the watch. **Menu** does too. **Tab** opens pause on the keyboard.
- On the watch, the **left stick** moves the highlight. **GAME OPTIONS** goes past ratio. The last line says scroll down for VR settings.

---

## Getting VR working

GEVR uses **OpenXR**. Current zip: [README Install](../README.md#install) / [`GEVR-Beta-vr456.3-win64.zip`](https://github.com/no6969el/GEVR/releases/download/vr456.3/GEVR-Beta-vr456.3-win64.zip).

**Verified:**

- **Pimax Crystal Super + SteamVR OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR) (sboys3). We do not maintain that driver. We do support this experience.
- **Native PimaxXR**
- **Quest 3 + Virtual Desktop OpenXR (VDXR)**

**Headset:** unzip **`GEVR-Beta-vr456.3-win64.zip`**, run **`Start-GEVR.bat`**, point at your USA `.z64`, put the headset on, and recenter with both stick clicks.

**No headset:** **`Play-on-monitor.bat`**.

PNG texture packs go in `hdtextures\GOLDENEYE` next to `goldeneye.exe`. `GOLDENEYE_HIRESTEXTURES.hts` is the wrong file.

### If controls or VR feel dead

1. Launch with **`Start-GEVR.bat`** (headset) or **`Play-on-monitor.bat`** (flat), not bare `goldeneye.exe`.
2. Recenter with **both** stick clicks.
3. Confirm Windows is handing GEVR the OpenXR runtime you think it is.
4. File an Issue with **headset**, **OpenXR runtime**, **SteamVR on/off**, **headset vs monitor**, and whether you used **Start-GEVR.bat**. [CONTRIBUTING](../CONTRIBUTING.md).

Do not upload your ROM.
