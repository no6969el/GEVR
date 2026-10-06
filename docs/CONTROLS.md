# Controls (Beta)

How to move, aim, shoot, and use Bond's watch in **[GEVR Beta vr456.7](https://github.com/no6969el/GEVR/releases/latest)**.

Install first: [README Install](../README.md#install). **Controls video:** [YouTube walkthrough](https://www.youtube.com/watch?v=Jst5srE6Iwc) (also on the [README](../README.md#vr-actions)). Download: [`GEVR-Beta-vr456.7-win64.zip`](https://github.com/no6969el/GEVR/releases/download/vr456.7/GEVR-Beta-vr456.7-win64.zip). The zip has no ROM and no HD texture pack. Tester notes: [BETA.md](BETA.md). Settings: [GEVR-SETTINGS.md](GEVR-SETTINGS.md). How to report: [CONTRIBUTING.md](../CONTRIBUTING.md).

## Which bat

- **Headset:** `Start-GEVR.bat`. VR picture, then GevrRomStarter.
- **Monitor / no headset:** `Play-on-monitor.bat`. Flat picture, no stereo eyes. Also the path for **local split-screen**.

Use those bats from **`GEVR-Beta-vr456.7-win64.zip`**. Do not double-click `goldeneye.exe`. A bare exe can skip the ROM cache update and leave VR input off.

You can also switch picture from **GEVR Settings**: set Visual mode to **VR**, **XR**, or **Flat**, then **Apply**. Apply saves and relaunches into that mode.

Ship stamp is **vr456.7**. First launch rebuilds the image cache once from your own USA GoldenEye ROM.

## Default layout (OpenXR)

GEVR uses the usual FPS layout:

| Hand | Role |
|---|---|
| **Right controller** | Gun hand: fire, aim, weapon **A** / **B**, comfort turn stick, weapon wheel click |
| **Left controller** | Walk hand: move stick, **X** next weapon, **Y** opens the watch, left watch cuff, watch picker, weapon wheel click |

**Meta Quest / Touch**, **Valve Index**, and other **Oculus-style OpenXR** profiles use the same actions. Only the names printed on the plastic differ.

Auto-aim starts **off**.

VR has **no walk bob**, **no landing dip**, and **no gun-hand sway**. Your view stays put when you walk and land. The gun in your hand does not add extra sway.

---

## Meta Quest / Touch (stereo VR)

| Control | Action |
|---|---|
| **Right trigger** | Fire the gun in your **right** hand |
| **Left trigger** | Fire the gun in your **left** hand. A left-hand gun fires on its own, not only when you dual-wield |
| **Right grip (squeeze)** | **Aim / ADS** on the gun ray (aim mark on the weapon, not glued to your face) |
| **Right grip at a door** | **Open / close** the door (same squeeze; no extra "use" reach when you are in range) |
| **Right grip on your left watch face** | **Watch press** (laser, detonator, or magnet depending on pause watch / watch picker) |
| **Right grip at your right hip** (gun hand low) | **Holster swap** (see [Weapons and holster](#weapons-and-holster)) |
| **Left grip (squeeze)** | **Aim / ADS** when that hand holds a gun; near a door or pickup, same rules as the right grip for that hand |
| **Left grip near a dropped weapon** | **Pick up** into **that** hand |
| **Left grip near your own stuck mine** | **Pick the mine back up** (remote mines and arming proximity mines you placed) |
| **Left grip on a two-handed gun's fore-end** | **Two-hand support**: hold the left controller along the barrel and squeeze |
| **Left stick** | Walk and strafe |
| **Right stick** | Turn in-game (**Smooth** or **Snap** from **GEVR Settings** / pause **VR SETTINGS**) |
| **One stick click** (left or right) | Open the **weapon wheel** for that hand (hold, hover, release to pick). Default is a **circle**. **NO WEAPON** sits at 12 o'clock. Centre follows the hover. Boxes are 2x dark grey. **STICK WHEEL** in GEVR Settings can switch to **Weapon Vert** (column); the next stick-click uses the new style |
| **Both stick clicks together** | **Recenter** playspace |
| **Right stick up / down while aiming** | Stand / crouch |
| **Left stick while aiming** | Walk forward and back (no accidental duck) |
| **Right A** | **Next weapon** on the **right** hand |
| **Left X** | **Next weapon** on the **left** hand |
| **Right B** | **USE**: doors and switches at range, plant/activate gadgets, throw cycle, and other retail **B** actions. **Gun reload** uses the [reload gesture](#reload-gesture-vr), not **B**. Tank shells still **auto-load** the next round after you fire |
| **Y** | **Opens the watch** |
| **Menu** (left controller) | Also opens the pause watch |
| **Head / room-scale** | Look around. Walk your room to move in the level |
| **Swing the held weapon** | Melee. The swing uses that weapon's damage. Shooting does not make the knife swing by itself |

**Dual-wield** is when you hold **two guns**. Put a second gun in the left hand with **Left X**, the wheel, or a pickup. Each trigger fires its own hand.

**Throwables** (grenades, timed mines, remote mines, proximity mines, plastique, covert modem): they appear in the hand. The trigger throws or fires. **B** plants and activates where GoldenEye already uses that button. Left-hand mines, bombcase, and plastique draw the right way around (no mirror). After you plant a mine, use the grip to pick your own stuck mine back up when the game allows it.

**Aimers:** red and green aim marks sit on the **shot's own first hit**, both eyes.

---

## Valve Index (stereo VR)

Same bindings as Quest. Index names:

| Index control | Same as Quest | Action |
|---|---|---|
| **Right trigger** | Right trigger | Fire the right gun |
| **Left trigger** | Left trigger | Fire the left-hand gun |
| **Right grip** | Right grip | Aim; door; watch press; hip holster swap |
| **Left grip** | Left grip | Aim (left gun); door; pickup; mine regrab; two-hand support |
| **Right thumbstick** | Right stick | Turn. On the sniper, forward or back steps the zoom |
| **Left thumbstick** | Left stick | Walk |
| **Thumbstick click** | Stick click | Weapon wheel for that hand |
| **Both thumbstick clicks** | Both stick clicks | Recenter |
| **Right A** | Right A | Next weapon on the right hand |
| **Right B** | Right B | USE / activate (not VR gun reload) |
| **Left X** | Left X | Next weapon on the left hand |
| **Left Y** | Y | Opens the watch |
| **System / menu button** | Quest **Menu** | Also opens the pause watch |

---

## Stick weapon wheel

1. **Click and hold** the left or right stick.
2. The wheel **freezes at the open pose**. Default style is a **circle**. **NO WEAPON** is at 12 o'clock. The centre follows your hover. Boxes are 2x dark grey (same palette as the watch picker).
3. Release to pick that slot.

**STICK WHEEL** in **GEVR Settings** / pause **VR SETTINGS**:

- **Weapon wheel** (circle, default)
- **Weapon Vert** (column)

Change the row, unpause, then the **next** stick-click uses the new style. No reboot.

Quick click with no hover still holsters / empties as the hip path allows.

---

## Bond's watch and cuff

The left cuff is the watch. It stays on your left arm. There is no detonator in the weapon cycle. You do **not** put a huge watch model into your gun hand.

### Watch picker (left cuff)

On the left cuff you get three squares with **pictures** and **labels**: **Laser / Magnet / Repel**. Yellow highlight is the middle square. Touch a square to set the cuff mode without digging the pause list first.

### Open the watch

Press **Y**. The **Menu** button also opens the pause watch (**Left Y** in the shipped VR profile).

Move the highlight with the **left stick**. Confirm with the face buttons, the same way the retail watch pages work.

From this menu you can pick **Watch Laser**, **Detonator**, **Watch Magnet Attract**, **Watch Magnet Repel**, and other stage items when you have them.

### GAME OPTIONS

Open **GAME OPTIONS** on the watch. The sheet goes past ratio. Scroll down with the **left stick**. The last line says **scroll down - vr settings below**. The VR rows (turn speed, turn style, snap size, **STICK WHEEL**) sit below ratio on that page.

**Watch Laser vs Detonator:**

- Choose **Watch Laser** to force **laser only** on cuff press (never detonate on that press).
- Choose **Detonator** for **auto**: cuff press **detonates your planted remote mines** if any are active; otherwise it fires the **watch laser** from the cuff.

If the stage does not give you a laser, a **Watch Laser** row can still appear in the watch list for solo play.

### Cuff press (laser / detonate / magnet)

When the watch is **not** animating open on screen:

1. Touch the **left watch face** with your **right controller grip** (gun hand).
2. **Squeeze** on a **new** press, not a squeeze you were already holding before you touched the watch.

Result depends on the watch picker / pause watch (laser, auto detonate/laser, or magnet).

### Watch Magnet (unlimited in VR)

1. Pick **Magnet** on the cuff picker, or **Watch Magnet Attract** in the pause watch (guns stay in hand).
2. Touch the **left watch cuff** with your **right hand** and **squeeze**.

In **VR**, **Magnet** is **unlimited**: no ammo spend, no DRY click. **Laser** and **Repel** stay on the picker and the pause list; they still use the normal watch item flow (not unlimited ammo).

---

## Weapons and holster

| Control | Action |
|---|---|
| **Stick click** | **Weapon wheel** for that hand (circle default; see above) |
| **Right A** | **Next** weapon on the **right** hand |
| **Left X** | **Next** weapon on the **left** hand |
| **Grip pickup** | Squeeze near a weapon on the ground to equip it to **that** hand |
| **Right hip + squeeze** | **Holster swap**: stash the right-hand gun, or draw the hip gun. Same-gun hip grip is a **real swap**, never a no-op. Left hand must be bare / cuff only for the classic hip toggle |

**All Guns / inventory copy:** weapon switch prefers a **free inventory copy** over stealing the holstered hip gun.

You cannot put the same non-dual gun in both hands unless the retail game would allow that pair.

**Two-handed rifles, shotguns, SMGs, and the grenade launcher:** hold with the right hand. Bring the left grip to the fore-end and squeeze to steady the aim. Let go to aim from the right wrist only.

Weapon pictures sit on the lifting hand, including the grenade and mines.

### Moonraker and sniper scopes

- **Moonraker:** small **circular scope lens** on the hexagonal rear cap, open ring in the middle. Look through that ring. Shoot through that ring. Dual Moonrakers give **two lenses**, one per hand. **No front grill screen.**
- **Sniper rifle:** still the one round plate with the green dot and zoom steps, on either hand. Hold a sniper in one hand and a Moonraker in the other and you get both: sniper plate plus Moonraker lens. Push the **right stick forward or back** to step sniper zoom: **30**, **20**, **15**, **10**, and **7**. Walking does not zoom.

### Rocket launcher

- A **loaded rocket stays on the launcher** while you look around. It is not glued to your head.
- **Flat / mouse aim:** the crosshair stays centred.

### Ammo

In VR, the ammo digits sit on the grip. You read them from behind the gun. Flat mode keeps the count in the corner.

---

## Reload gesture (VR)

Guns do **not** auto-reload except **tank shells** (retail empty-mag autoload after you fire). Reload other guns with the physical gesture for that weapon, not with **B**.

| Weapon type | Reload |
|---|---|
| **Magazine-fed** (mag on top, mag on bottom, **Uzi**, etc.) | Reload from the **magazine**: bring the mag through the reload motion |
| **Pistols** and guns **without** a magazine (**shotgun** included) | Reload at the **chest cross** gesture only |
| **Handle grab** (grab the gun handle to swap) | **Swaps hands**. Does **not** reload |

**B** still covers retail **USE**, plant, activate, and other **B** actions where GoldenEye maps them. It is not the VR gun-reload button.

---

## Snap-turn

In **GEVR Settings** / pause **VR SETTINGS**, turn style **Snap** uses **real degrees**: 15 / 22.5 / 30 / 45 / 60 / 90. The SETTINGS glass is click-to-edit (right stick click while the glass has focus), not a laser commit.

---

## Tank

- Walk onto the **tank chassis** to **auto-mount**.
- **Right stick up / down** aims the cannon elevation.
- Empty magazine **auto-loads** the next tank shell after you fire.
- Get off the way the retail game does. There is no separate enter button.

---

## Recenter

**Press both thumbstick clicks at the same time.** One stick click alone opens the weapon wheel, not recenter.

Also works:

- **Xbox gamepad:** both stick clicks together
- **Keyboard:** `Home` while the game window has focus

After you recenter, turning your head while you stand still should not slide the world. Walking in your room moves you in the level.

---

## GEVR Settings and the pause watch

**GEVR Settings** is on **Mission Select**, next to **Select Mission**, **Multiplayer**, and **Cheat Options**. It is not named Options. In VR you look at that glass on the intro hub.

| | **GEVR Settings** | **Pause watch** (in a mission) |
|---|---|---|
| Open | Mission Select, then **GEVR Settings** | **Y**, or the **Menu** button |
| Change a row | **A** selects the row. Stick **left / right** changes the value. **A** accepts | **Left stick** moves the highlight. Face buttons confirm |
| Save | **Apply** saves and relaunches into that mode | The watch sheet saves the retail way |
| **STICK WHEEL** | **Weapon wheel** (circle) or **Weapon Vert** (column) | Same row under **VR SETTINGS** (next stick-click applies) |
| **A** during play | **Next weapon** on the right hand | (settings closed) |
| **B** during play | **USE** / plant / activate (not VR gun reload) | (settings closed) |

Picture choices on that page:

- **Visual mode:** **VR**, **XR** (smaller screen, black outline), or **Flat** on the monitor.
- **Frame rate:** follows the headset by default. **Fixed 90** is still available.
- **Supersample** starts at **3**. **Filter** starts on **bilinear**. **Point** is still available.
- **Monitor:** **Both**, **Left**, **Right**, or **Off**. Off blanks the mirror while you stay in the headset.

Starting rows: [README](../README.md#vr4567) · [GEVR Settings](GEVR-SETTINGS.md).

---

## HD memo overlay

When **HD textures** are on, decoded HD pictures stay in memory so they stutter less (1 GB cap, still beta). Set `GETV_HD_MEMO_MB=0` in a boot profile to turn the memo overlay off. GEVR does **not** ship the HD pack; you add the community PNG pack yourself (see [README](../README.md#hd-textures)).

PNG texture packs go in `hdtextures\GOLDENEYE` next to `goldeneye.exe`. `GOLDENEYE_HIRESTEXTURES.hts` is the wrong file.

---

## XR catch-up and quit

Missed headset frames no longer slow the sim. When you quit, the game actually quits (no orphan window). One instance.

---

## Keyboard and mouse (flat / monitor)

Use **`Play-on-monitor.bat`**, or set Visual mode to **Flat** and Apply. Mouse look is on. The flat mouse-aim **crosshair stays centred**.

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
| **X** | Previous weapon (keyboard mapping; VR **Left X** is next weapon on the left hand) |
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

- **Gun reload (VR):** [reload gesture](#reload-gesture-vr). Magazine, chest cross, or handle grab. **No auto-reload** except **tank shells**.
- **B** is **USE** / plant / activate in VR. Not the VR gun-reload button.
- **Y** opens the watch. **Menu** does too. **Tab** opens pause on the keyboard.
- On the watch, the **left stick** moves the highlight. **GAME OPTIONS** goes past ratio. The last line says scroll down for VR settings.
- Die / continue should no longer dump you in junk space ([#38](https://github.com/no6969el/GEVR/issues/38)). If it still breaks, quit, run the bat again, and report it.

---

## Not in this zip

- thermal vision: out
- corpse freeze: out
- Gun Drop / Arm Bounds stay off (not default-on keepers)

---

## Getting VR working

GEVR uses **OpenXR**. Current zip: [README Install](../README.md#install) / [`GEVR-Beta-vr456.7-win64.zip`](https://github.com/no6969el/GEVR/releases/download/vr456.7/GEVR-Beta-vr456.7-win64.zip).

**Verified:**

- **Pimax Crystal Super + SteamVR OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR) (sboys3). We do not maintain that driver. We do support this experience.
- **Native PimaxXR**
- **Quest 3 + Virtual Desktop OpenXR (VDXR)**

**Headset:** unzip **`GEVR-Beta-vr456.7-win64.zip`**, run **`Start-GEVR.bat`**, point at your USA `.z64`, put the headset on, and recenter with both stick clicks.

**No headset:** **`Play-on-monitor.bat`**.

### If controls or VR feel dead

1. Launch with **`Start-GEVR.bat`** (headset) or **`Play-on-monitor.bat`** (flat), not bare `goldeneye.exe`.
2. Recenter with **both** stick clicks.
3. Confirm Windows is handing GEVR the OpenXR runtime you think it is.
4. File an Issue with **headset**, **OpenXR runtime**, **SteamVR on/off**, **headset vs monitor**, and whether you used **Start-GEVR.bat**. [CONTRIBUTING](../CONTRIBUTING.md).

Do not upload your ROM.
