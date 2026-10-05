<p align="center">
  <img src="GEVR-box-cover.png" alt="GoldenEye 007 VR - GEVR box art" width="480" />
</p>

# GEVR

**GoldenEye. Native. In VR. Bring your own USA ROM.**

> **Latest:** **[vr454](https://github.com/no6969el/GEVR/releases/tag/vr454)** — zip [`GEVR-Beta-vr454-win64.zip`](https://github.com/no6969el/GEVR/releases/download/vr454/GEVR-Beta-vr454-win64.zip). The zip has no ROM and no HD texture pack. You bring a USA GoldenEye ROM you own. Or hit **Update** in GevrRomStarter.

The N64 classic you can stand inside. GEVR is a from-source PC port of *GoldenEye 007* for OpenXR. This public repo is for player docs, Issues, and Beta zip releases. New product code is developed privately. See [`docs/SOURCE.md`](docs/SOURCE.md).

| | |
|---|---|
| **Download** | [**GEVR-Beta-vr454-win64.zip**](https://github.com/no6969el/GEVR/releases/download/vr454/GEVR-Beta-vr454-win64.zip) |
| **Release page** | [vr454](https://github.com/no6969el/GEVR/releases/tag/vr454) |
| **Latest** | [Releases / Latest](https://github.com/no6969el/GEVR/releases/latest) |
| **Controls** | [docs/CONTROLS.md](docs/CONTROLS.md) |
| **Report a bug** | [New Issue](https://github.com/no6969el/GEVR/issues/new/choose) |
| **Discord** | [discord.gg/flat2vr](https://discord.gg/flat2vr) |
| **Features** | [FEATURES.md](FEATURES.md) |
| **Support** | [Patreon](https://www.patreon.com/cw/GEVR) |

Star the repo and [follow @no6969el](https://github.com/no6969el). **Watch → Releases** for ship pings.

---

## VR actions

**How to control GEVR in VR** — walkthrough on YouTube: **[watch here](https://www.youtube.com/watch?v=Jst5srE6Iwc)**

[![How to control GEVR in VR](https://img.youtube.com/vi/Jst5srE6Iwc/maxresdefault.jpg)](https://www.youtube.com/watch?v=Jst5srE6Iwc)

**Right hand is the gun. Left hand walks, and the watch stays on that cuff.** Meta Quest / Touch, Valve Index, and Oculus-style OpenXR use the same actions. Index names are in [`docs/CONTROLS.md`](docs/CONTROLS.md).

### Move

| Control | What it does |
|---|---|
| **Left stick** | Walk and strafe |
| **Right stick** | Turn. **Smooth** or **Snap** is on the watch, under **GAME OPTIONS**, past ratio. |
| **Both thumbstick clicks** | Recenter the playspace (`Home` on the keyboard) |
| **Head / room-scale** | Look around. Walk your room to move in the mission. |
| **Right stick up or down while aiming** | Stand or crouch |
| **Left stick while aiming** | Walk forward and back |

With the sniper out, the right stick steps the zoom. Walking does not zoom. See [Sniper](#sniper) below.

### Fight

| Control | What it does |
|---|---|
| **Right trigger** | Fire the gun in your right hand |
| **Left trigger** | Fire the gun in your left hand. It fires on its own. You do not need a second gun. |
| **Grip** | Aim down the gun. Near a door, the same grip opens or closes it. |
| **Grip, then release** | Hold the gun while you grip. Release to put it on your hip. |
| **Right B** | Play the reload animation. B also plants and activates where GoldenEye uses that button. |
| **Chest swipe, or a grab on the magazine** | Refill with a click and no animation |
| **Grab the handle** | Swap the gun to the other hand. This does not reload. |
| **Right A** | Next weapon on the right hand |
| **Left X** | Previous weapon on the left hand |
| **Left grip on the fore-end** | Two-hand hold for a rifle, shotgun, or SMG in the right hand |
| **Grip near a gun on the ground** | Pick it up into that hand |
| **Grip on your own stuck mine** | Pick a remote mine, or an arming proximity mine, back up |
| **Trigger** | Throw a grenade, or fire a launcher |

Guns do not reload on their own. An empty gun stays in your hand. Grenades, mines, and gadgets still switch away when you use them up. A new gun goes to your hip, and the old gun goes to your inventory.

**Dual-wield** means one gun in each hand. Each trigger fires that hand.

### Watch

| Control | What it does |
|---|---|
| **Y** | Open the watch |
| **Menu** (Quest left; Index system) | Also opens the watch |
| **GAME OPTIONS** | Go past ratio. The last line says to scroll down for VR settings. |
| **Cuff grab** | Detonate planted remotes. If none are planted, the watch laser comes from the cuff. |

There is no detonator in the weapon cycle. Full tables: [`docs/CONTROLS.md`](docs/CONTROLS.md).

---

## vr454

What to do in this Latest cut.

### Visual modes

You can play in **VR**, in **XR**, or **Flat** on the monitor. XR is a smaller screen with a black outline. On Mission Select, open **GEVR Settings**, change the Visual mode row, and choose **Apply**. Apply saves and relaunches into that mode. VR, XR, and Flat each keep the settings saved for that mode.

### Frame rate

Frame rate follows the headset unless you change it. **Fixed 90** is still on that row if you want it.

### Supersample and filter

Supersample starts at **3**. The texture filter starts on **bilinear**. **Point** is still available.

### Monitor picture

The monitor picture can be **Both**, **Left**, **Right**, or **Off**. **Off** blanks the mirror on the desktop while you stay in the headset.

### Weapon change

**Left X** is the previous weapon on the left hand. **Right A** is the next weapon on the right hand.

### Hip holster

Grip a gun to hold it. Release the grip to put it on your hip. A new gun goes to the hip, and the old gun goes to your inventory. An empty gun stays in your hand. Grenades, mines, and gadgets still switch away when you use them up.

### Reload

Press **B** to play the reload animation. A swipe at your chest, or a grab on the magazine, refills the gun with a click and no animation. Pistols and guns with no magazine, including the shotgun, reload from the chest. Guns with the magazine on top or on the bottom, including the Uzi, reload from the magazine.

### Handle grab

A grab on the handle swaps the gun into the other hand. That grab does not reload. Guns do not reload on their own.

### Left hand

A gun in your left hand fires on its own with the left trigger.

### Ammo digits

Ammo digits sit on the grip. Read them from behind the gun. Flat mode on the monitor still shows the count in the corner.

### Weapon pictures

The weapon picture sits on the hand that is lifting the gun. That includes the grenade and the mines.

### Mines in the hand

Remote mines, proximity mines, and timed mines draw in your hand the same way the grenade does.

### Swing

When you swing, the hit uses the damage of the weapon you are holding. Shooting does not make the knife swing by itself.

### Bullet spread

Bullet spread stays around where the controller is aiming. Rockets, the grenade launcher, and the watch laser are unchanged.

### Rockets

Rockets stay on the gun. The crosshair on that shot is flat.

### Sniper

A green dot stays on. The shot leaves your eye along that dot. Push the right stick forward or back to step the zoom through **30**, **20**, **15**, **10**, and **7**. Walking does not zoom. With the sniper in your right hand, the red crosshair stays hidden. The left-hand green aimer is not in this build.

### Watch

Press **Y** to open the watch. On the **GAME OPTIONS** sheet, go past ratio. The last line says to scroll down for VR settings. Grab the cuff to detonate planted remotes. If none are planted, the watch laser comes from the cuff. There is no detonator in the weapon cycle.

### Janus meeting

After the Janus meeting, the crowd stops respawning.

### Where GEVR Settings lives

**GEVR Settings** is on **Mission Select**, next to **Select Mission**, **Multiplayer**, and **Cheat Options**. The name is **GEVR Settings**. It is not named Options.

Older comfort and combat that is still in this line: playspace and hands ([#74](https://github.com/no6969el/GEVR/issues/74)), grip doors and the Dam sky ([#80](https://github.com/no6969el/GEVR/issues/80), [#90](https://github.com/no6969el/GEVR/issues/90)), and the watch magnet. See [FEATURES.md](FEATURES.md) and [`docs/CONTROLS.md`](docs/CONTROLS.md).

---

## Install

1. Download **[GEVR-Beta-vr454-win64.zip](https://github.com/no6969el/GEVR/releases/download/vr454/GEVR-Beta-vr454-win64.zip)** from [Latest](https://github.com/no6969el/GEVR/releases/latest) / [vr454](https://github.com/no6969el/GEVR/releases/tag/vr454). The zip has no ROM and no HD texture pack.
2. Unzip anywhere.
3. Run **`Start-GEVR.bat`**. It starts **GevrRomStarter.exe**. Please use the bat. Do not double-click `goldeneye.exe`.
4. Point at your **USA GoldenEye `.z64`** when asked. Pictures are prepared under `%LOCALAPPDATA%\GEVR\cache\<ROM-hash>\`.
5. Put the headset on. Recenter with **both thumbstick clicks**.
6. On **Mission Select**, open **GEVR Settings** (next to Select Mission, Multiplayer, and Cheat Options) and set the picture. **Apply** saves and relaunches.

**Flat on the monitor:** choose **Flat** in GEVR Settings and Apply, or run **`Play-on-monitor.bat`**. Same game, no headset.

**New install:** the first launch waits once while pictures prepare. Saves start empty.

**After an update:** keep the same USA `.z64`. The first launch prepares the pictures once. Saves and GEVR Settings stay under `%LOCALAPPDATA%\GEVR`. You can also use **Update** in GevrRomStarter. If the picture is wrong, run **`Clear-GEVR-cache.bat`** and type **YES** before you delete the whole `%LOCALAPPDATA%\GEVR` folder.

### HD textures

GEVR does not ship the pictures. Put a PNG pack in **`hdtextures\GOLDENEYE`**, next to `goldeneye.exe`. **`GOLDENEYE_HIRESTEXTURES.hts`** is the wrong file. An `.hts` file in `hdtextures` does nothing.

1. Download the PNG zip, not the `.hts` file — [GoldenEye-007-HD releases](https://github.com/GhostlyDark/GoldenEye-007-HD/releases) or the [GE007 HD texture pack page](https://evilgames.eu/texture-packs/ge007-hd.htm).
2. Extract it so the pictures land in **`hdtextures\GOLDENEYE`**, next to `goldeneye.exe`.
3. In **GEVR Settings**, turn **HD textures** **On**.
4. Choose **Apply**. The pack loads on the next boot.

---

## Older playtest (video)

This clip is from an older public cut (around vr441). The picture and the controls may not match **vr454**.

[![GoldenEye VR streamer playtest (~vr441 era)](https://img.youtube.com/vi/z4B0Ceqrf6I/maxresdefault.jpg)](https://www.youtube.com/watch?v=z4B0Ceqrf6I)

[Watch on YouTube](https://www.youtube.com/watch?v=z4B0Ceqrf6I)

---

## What we tested

| Path | Notes |
|------|--------|
| **Pimax Crystal Super + SteamVR OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR) (sboys3) | Primary wear path. We do not maintain that driver. We do support this experience. |
| **Native PimaxXR** | Verified attach / play |
| **Meta Quest 3 + Virtual Desktop OpenXR (VDXR)** | Verified attach / play |
| **RTX 5060 laptop + Quest 3 + Virtual Desktop VDXR** | vr441, 2026-09-17. One data point, not a minimum spec. |

**Half-speed or mushy VR?** Turn **SteamVR Motion Smoothing** off and **Virtual Desktop Space Warp** off. Details: [`docs/BETA.md`](docs/BETA.md#half-speed--mushy-vr).

When you report a bug or crash, include: headset, OpenXR runtime, SteamVR on or off, headset or monitor, whether you used **`Start-GEVR.bat`**, your **`gevr-*-boot.cmd`** filename from the zip folder, any log next to the zip or in the console, and any **`gevr-fault-*.txt`** beside the exe. Do not upload your ROM.

---

## Discord (help + fan chat)

**[Join the GEVR Discord](https://discord.gg/flat2vr)** for port help and GoldenEye fan chat. Bring your own ROM. Do not upload it. Setup notes and logs are enough. GitHub Issues are the place for tracked bugs.

---

## Known quirks (honest Beta)

- **Half-speed or mushy VR:** SteamVR **Motion Smoothing** off, and Virtual Desktop **Space Warp** off ([BETA.md](docs/BETA.md#half-speed--mushy-vr)).
- **Frigate door / aperture** ([#79](https://github.com/no6969el/GEVR/issues/79)) and other level stoppers are still an open focus.
- **Prop-on-prop / Dam blue** ([#70](https://github.com/no6969el/GEVR/issues/70)) and some Dam and Frigate water looks are still open.
- A swing uses the damage of the weapon in your hand. Shooting does not swing the knife for you.
- **Big explosions** can still hard-crash. Grab `gevr-fault-*.txt` beside the exe before you relaunch.
- An empty hand draws a **cube**. The cube hides when that hand holds a weapon.
- Expect occasional **crashes** while we keep polishing.

More tester notes: [BETA.md](docs/BETA.md) · [CONTROLS.md](docs/CONTROLS.md).

---

## Why this exists

- **Native, from source** — the game loop is ours, so VR can be real
- **OpenXR** — Crystal, Quest via PC, SteamVR-class headsets
- **Your ROM** — legal ownership stays with you
- **Feel first** — 6DOF, aiming, presence, then polish, then extras

More pitch: [FEATURES.md](FEATURES.md). Credits: [CREDITS.md](CREDITS.md). Boundaries: [PRIOR-ART.md](PRIOR-ART.md), [LICENSE](LICENSE). Other projects using GEVR: [docs/OTHER-PROJECTS.md](docs/OTHER-PROJECTS.md).

---

## Docs (player)

- Start: [`docs/00-START-HERE.md`](docs/00-START-HERE.md)
- Controls: [`docs/CONTROLS.md`](docs/CONTROLS.md)
- Settings: [`docs/GEVR-SETTINGS.md`](docs/GEVR-SETTINGS.md)
- Beta snapshot: [`docs/BETA.md`](docs/BETA.md) · [`docs/FEATURES-CURRENT.md`](docs/FEATURES-CURRENT.md)
- Other projects: [`docs/OTHER-PROJECTS.md`](docs/OTHER-PROJECTS.md)

Jump in. Be Bond.
