<p align="center">
  <img src="GEVR-box-cover.png" alt="GoldenEye 007 VR - GEVR box art" width="480" />
</p>

# GEVR

**GoldenEye. Native. In VR. Bring your own ROM.**

The N64 classic you can stand inside. GEVR is a from-source PC port of *GoldenEye 007* for real OpenXR VR. You bring a **USA GoldenEye ROM you own**. The zip has **no ROM** and **no HD texture pack**.

> **Latest:** **[vr454](https://github.com/no6969el/GEVR/releases/tag/vr454)** — [`GEVR-Beta-vr454-win64.zip`](https://github.com/no6969el/GEVR/releases/download/vr454/GEVR-Beta-vr454-win64.zip). Or hit **Update** in GevrRomStarter. Full binds: [docs/CONTROLS.md](docs/CONTROLS.md).

---

## VR actions

**Right hand is the gun hand. Left hand walks, and the watch cuff stays on that arm.** Quest, Index, and other Oculus-style OpenXR controllers use the same actions. Index names are in [`docs/CONTROLS.md`](docs/CONTROLS.md).

**How to control GEVR in VR** — walkthrough on YouTube: **[watch here](https://www.youtube.com/watch?v=Jst5srE6Iwc)**

[![How to control GEVR in VR](https://img.youtube.com/vi/Jst5srE6Iwc/maxresdefault.jpg)](https://www.youtube.com/watch?v=Jst5srE6Iwc)

### Move

| Control | What it does |
|---|---|
| **Left stick** | Walk and strafe |
| **Right stick** | Turn. **Smooth** or **Snap** is set in **GEVR Settings** |
| **Both thumbstick clicks** | Recenter the playspace |
| **Head / room-scale** | Look around. Walk your room to move in the level |
| **Left stick while aiming** | Walk forward and back |
| **Right stick up or down while aiming** | Stand or crouch |

### Fight

| Control | What it does |
|---|---|
| **Right trigger** | Fire the gun in your **right** hand |
| **Left trigger** | Fire the gun in your **left** hand. It fires on its own, even when you are not dual-wielding |
| **Grip** | Aim down the gun |
| **Grip near a door** | Open or close it |
| **Right A** | Next weapon on the **right** hand |
| **Left X** | Previous weapon on the **left** hand |
| **Right B** | Reload button. Reloads any gun the normal way. Also switches, plant, and activate |
| **Upper chest + grab** | Optional. Reloads any gun |
| **Grip on a visible magazine** | Reloads that gun |
| **Grab the handle** | Swaps hands. Does not reload |
| **Grip, then release** | Grip holds the gun. Release holsters it at the hip |
| **Left grip on the fore-end** | Two-hand hold for a rifle, shotgun, or SMG in the right hand |
| **Grip near a gun on the ground** | Pick it up into that hand |
| **Grip on your own stuck mine** | Pick a remote mine, or an arming proximity mine, back up |
| **Swing** | Uses the damage of the weapon in that hand |

A lone gun in the left hand still fires with the left trigger. Dual-wield is only when you hold two guns. Grenades, mines, and gadgets show in the hand. The trigger throws or fires them.

### Watch

| Control | What it does |
|---|---|
| **Y** | Opens the watch |
| **Menu** | Also opens the pause watch |
| **GAME OPTIONS** | Go past ratio. The last line says scroll down for VR settings |
| **Cuff grab** | Detonates planted remotes. If none are planted, the watch laser comes from the cuff |

There is no detonator in the weapon cycle. The full bind list is in [`docs/CONTROLS.md`](docs/CONTROLS.md).

---

## vr454

### Visual modes

You can play in **VR**, in **XR**, or **Flat** on the monitor. XR is a smaller screen with a black outline. Open **GEVR Settings**, change the Visual mode row, and choose **Apply**. Apply saves and relaunches into that mode.

### Frame rate

Frame rate follows the headset by default. Fixed 90 is still available on that row.

### Supersample and filter

Supersample starts at 3. The texture filter starts on bilinear. Point is still available.

### Monitor picture

Choose **Both**, **Left**, **Right**, or **Off**. Off blanks the mirror on the monitor while you stay in the headset.

### Where GEVR Settings lives

On **Mission Select**, **GEVR Settings** sits next to **Select Mission**, **Multiplayer**, and **Cheat Options**. It is not named Options.

**A** selects a row. The stick **left** or **right** changes the value. **A** accepts. Highlight **Apply** and press **A** to save and relaunch.

| Row | Starts at |
|---|---|
| Supersample | 3 |
| Monitor | Both |
| Full screen | Off |
| Window | 1280×960 |
| Filter | Bilinear |
| Frame rate | Headset |
| Game speed | Smooth 90 |
| HD textures | Off |
| Visual mode | VR |
| Beta | None yet |
| Reset defaults | No |
| Apply | Save and relaunch |

Each mode keeps its own saved settings. Switch Visual mode when you want to edit a different one. The monitor row is for VR and XR. It is greyed out in Flat.

### Weapon change

**Left X** is the previous weapon on the left hand. **Right A** is the next weapon on the right hand.

### Hip holster

Grip to hold the gun. Release to holster it. A new gun goes to the hip, and the old gun goes to inventory. An empty gun stays in the hand. Grenades, mines, and gadgets still switch away when they are used up.

### Reload

You do not have to reload by hand. Press **B**, the reload button, and any gun reloads the normal way.

You can also hold any gun to your upper chest and press the grab button to reload it. On a gun with a visible magazine, grab that magazine with the grip button to reload it.

Pistols, the shotgun, the sniper, and other guns with no visible magazine reload across the chest, or with **B**.

Grabbing the handle swaps hands and does not reload. Guns do not reload on their own.

### Left hand

A gun in the left hand fires on its own with the left trigger.

### Ammo and weapon pictures

Ammo digits sit on the grip and read from behind the gun. Flat mode keeps the corner count. Weapon pictures sit on the lifting hand, including the grenade and mines.

### Mines

Remote, proximity, and timed mines draw in the hand like the grenade.

### Swing

A swing uses the damage of the weapon you are holding. Shooting does not make the knife swing by itself.

### Bullets and rockets

Bullet spread stays around the controller aim. Rockets, the grenade launcher, and the watch laser are unchanged. Rockets stay on the gun, with a flat crosshair.

### Sniper

A green dot stays on. Shots leave the eye along that dot. Push the right stick forward or back to step the zoom through 30, 20, 15, 10, and 7. Walking does not zoom. The right-hand sniper hides the red crosshair. The left-hand green aimer is not in this build.

### Watch

Press **Y** to open the watch. On the **GAME OPTIONS** sheet, go past ratio. The last line says scroll down for VR settings. A cuff grab detonates planted remotes. If none are planted, the watch laser comes from the cuff. There is no detonator in the weapon cycle.

### Janus meeting

The crowd stops respawning after the meeting.

### HD textures

The zip does not include a texture pack. If `hdtextures` only has `GOLDENEYE_HIRESTEXTURES.hts`, that is the wrong file. An `.hts` file there does nothing.

1. Download a GLideN64 **PNG** zip, not the `.hts` file. [GoldenEye-007-HD releases](https://github.com/GhostlyDark/GoldenEye-007-HD/releases) or the [GE007 HD texture pack page](https://evilgames.eu/texture-packs/ge007-hd.htm).
2. Put the pictures in `hdtextures\GOLDENEYE`, next to `goldeneye.exe`. Do not rename the picture files.
3. Turn **HD textures** **On**.
4. Choose **Apply**.
5. The pack loads on the next boot.

Playspace movement, grip doors, the tank, and recenter are still in. Details: [FEATURES.md](FEATURES.md).

---

## Install

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

1. Download **[GEVR-Beta-vr454-win64.zip](https://github.com/no6969el/GEVR/releases/download/vr454/GEVR-Beta-vr454-win64.zip)** from [Latest](https://github.com/no6969el/GEVR/releases/latest) / [vr454](https://github.com/no6969el/GEVR/releases/tag/vr454). The zip has no ROM and no HD texture pack.
2. Unzip anywhere.
3. Run **`Start-GEVR.bat`**. It starts **GevrRomStarter.exe**.
4. Point at your **USA GoldenEye `.z64`** when asked. Images extract to `%LOCALAPPDATA%\GEVR\cache\<ROM-hash>\`. The first launch after an update rebuilds that cache once from your ROM.
5. Put the headset on. Recenter with **both thumbstick clicks**.
6. On **Mission Select**, open **GEVR Settings** (next to Select Mission, Multiplayer, and Cheat Options) and tune the picture.

Use the bat. Do not start bare `goldeneye.exe`.

The game starts in **VR**. For a monitor with no headset, run **`Play-on-monitor.bat`**. You can also set Visual mode to **Flat** and Apply.

**New install:** the first launch waits once while images prepare. Saves start empty.

**After an update:** keep the same USA `.z64`. Saves and GEVR Settings stay under `%LOCALAPPDATA%\GEVR`. Or use **Update** in GevrRomStarter. If the picture is wrong, try **`Clear-GEVR-cache.bat`** (type **YES**) before you delete the whole `%LOCALAPPDATA%\GEVR` folder.

---

## Older playtest (video)

This clip is from an older public cut. Picture and controls may not match **vr454**.

[![GoldenEye VR streamer playtest](https://img.youtube.com/vi/z4B0Ceqrf6I/maxresdefault.jpg)](https://www.youtube.com/watch?v=z4B0Ceqrf6I)

[Watch on YouTube](https://www.youtube.com/watch?v=z4B0Ceqrf6I)

---

## What we tested

| Path | Notes |
|------|--------|
| **Pimax Crystal Super + SteamVR OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR) (sboys3) | Primary wear path — we do not maintain that driver; we *do* support this experience |
| **Native PimaxXR** | Verified attach / play |
| **Meta Quest 3 + Virtual Desktop OpenXR (VDXR)** | Verified attach / play |
| **RTX 5060 laptop + Quest 3 + Virtual Desktop VDXR** | One data point, not a minimum spec |

**Half-speed or mushy VR?** Turn **SteamVR Motion Smoothing Off** and **Virtual Desktop Space Warp Off**. Details: [`docs/BETA.md`](docs/BETA.md#half-speed--mushy-vr).

When you report a bug or crash, include: **headset**, **OpenXR runtime**, **SteamVR on/off**, **HMD vs monitor**, whether you used **`Start-GEVR.bat`**, your **`gevr-*-boot.cmd`** filename from the zip folder, any log next to the zip or in the console, and any **`gevr-fault-*.txt`** beside the exe. Do **not** upload your ROM.

---

## Discord (help + fan chat)

**[Join the GEVR Discord](https://discord.gg/flat2vr)** for port help and GoldenEye fan chat. Bring your own ROM. Do not upload it. GitHub Issues stay the place for tracked bugs.

---

## Known quirks (honest Beta)

- **Half-speed or mushy VR:** SteamVR **Motion Smoothing Off**; Virtual Desktop **Space Warp Off** ([BETA.md](docs/BETA.md#half-speed--mushy-vr)).
- **Big explosions** can still hard-crash. Grab `gevr-fault-*.txt` beside the exe before you relaunch.
- An empty hand shows Bond's fist. The old hand cube is off.
- Expect occasional **crashes** while we keep polishing.

More tester notes: [BETA.md](docs/BETA.md) · [CONTROLS.md](docs/CONTROLS.md).

---

## Why this exists

- **Native / from-source** — the game loop is ours, so VR can be real
- **OpenXR** — Crystal, Quest via PC, SteamVR-class headsets
- **Your ROM** — you keep the cart you own
- **Feel first** — stand in the room, aim with your hands, then polish

More pitch: [FEATURES.md](FEATURES.md). Credits: [CREDITS.md](CREDITS.md). Boundaries: [PRIOR-ART.md](PRIOR-ART.md), [LICENSE](LICENSE). Other projects using GEVR: [docs/OTHER-PROJECTS.md](docs/OTHER-PROJECTS.md).

---

## Docs (player)

- Start: [`docs/00-START-HERE.md`](docs/00-START-HERE.md)
- Controls: [`docs/CONTROLS.md`](docs/CONTROLS.md)
- Settings: [`docs/GEVR-SETTINGS.md`](docs/GEVR-SETTINGS.md)
- Beta snapshot: [`docs/BETA.md`](docs/BETA.md) · [`docs/FEATURES-CURRENT.md`](docs/FEATURES-CURRENT.md)
- Other projects: [`docs/OTHER-PROJECTS.md`](docs/OTHER-PROJECTS.md)

Jump in and enjoy finally being Bond in GoldenEye VR.
