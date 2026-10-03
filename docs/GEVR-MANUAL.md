# GEVR Player Manual

**GoldenEye 007 in VR. Native PC port. Bring your own ROM.**
For **GEVR Beta vr452.4** on Windows, 64-bit.

Controls video (watch this first if you like to learn by seeing): **https://www.youtube.com/watch?v=Jst5srE6Iwc**

---

## Contents

1. [Before you start](#1-before-you-start)
2. [Install and first launch](#2-install-and-first-launch)
3. [Which launcher to use](#3-which-launcher-to-use)
4. [Your two hands at a glance](#4-your-two-hands-at-a-glance)
5. [Moving and comfort](#5-moving-and-comfort)
6. [One squeeze, many jobs](#6-one-squeeze-many-jobs)
7. [Weapons](#7-weapons)
8. [Bond's watch](#8-bonds-watch)
9. [Valve Index button names](#9-valve-index-button-names)
10. [GEVR Settings](#10-gevr-settings)
11. [HD textures](#11-hd-textures)
12. [Playing on a monitor (flat)](#12-playing-on-a-monitor-flat)
13. [Updating GEVR](#13-updating-gevr)
14. [Troubleshooting](#14-troubleshooting)
15. [Reporting a problem](#15-reporting-a-problem)
16. [Quick reference card](#16-quick-reference-card)

---

## 1. Before you start

You need:

- A Windows 64-bit PC.
- A **USA GoldenEye 007 ROM (`.z64`) that you legally own**. GEVR does not include the game. There is no ROM in the download.
- For VR: a PC headset that runs **OpenXR**, with two motion controllers.
- For monitor play: nothing extra. A keyboard and mouse work.

Headset setups the team has checked:

| Headset and runtime | Notes |
|---|---|
| Pimax Crystal Super + SteamVR OpenXR, using [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR) by sboys3 | Main test setup. The GEVR team does not maintain that driver, but does support this setup. |
| Pimax with native PimaxXR | Checked. |
| Meta Quest 3 + Virtual Desktop OpenXR (VDXR) | Checked. |

Other OpenXR headsets may work. They have not been checked by the team.

---

## 2. Install and first launch

1. Unzip **`GEVR-Beta-vr452.4-win64.zip`** to any folder you like.
2. Double-click **`Start-GEVR.bat`**. It sets up VR and opens **GevrRomStarter**.
3. When GevrRomStarter asks, point it at your **USA GoldenEye `.z64`** file.
4. Wait. The first launch prepares the game's pictures from your ROM. This happens once. The prepared files go to `%LOCALAPPDATA%\GEVR\cache\`.
5. Put the headset on.
6. Press **both thumbstick clicks at the same time** to recenter. (See [Recenter](#recenter).)
7. You start in a small room called the **intro hub**. The game menus play on a screen in front of you. **Look to your right** to find the **GEVR Settings** panel. (See [GEVR Settings](#10-gevr-settings).)

Your saves start empty on a new install.

Auto-Aim is **off** by default in this build.

---

## 3. Which launcher to use

Always start GEVR from one of the two `.bat` files that came in the zip.

| File | Use it when |
|---|---|
| **`Start-GEVR.bat`** | You are playing in a headset. |
| **`Play-on-monitor.bat`** | You have no headset, or want to play on the desktop screen. VR is off. |

Do **not** double-click `goldeneye.exe` directly. Starting the exe on its own can skip the ROM update step and leave VR controls switched off.

---

## 4. Your two hands at a glance

GEVR uses the normal VR shooter layout:

| Hand | Main job |
|---|---|
| **Right controller** | Your **gun hand**. Fire, aim, **A** and **B** buttons, turning stick. |
| **Left controller** | Your **walk hand**. Walking stick, **X** button. Bond's **watch** is on your left wrist. |

Meta Quest (Touch), Valve Index and other Oculus-style OpenXR controllers all do the same things. Only the names printed on the buttons differ. Index names are in [section 9](#9-valve-index-button-names).

---

## 5. Moving and comfort

### Walk

Push the **left stick** to walk forward, back and sideways (strafe).

### Turn

Push the **right stick** left or right to turn Bond.

### Walk in your room

You can also physically walk around your play space. When you step in your room, Bond steps in the game. Turn your head to look around.

### Recenter

Press **both thumbstick clicks at the same time** (push the left stick and the right stick straight down together).

- One stick click on its own does nothing.
- On the keyboard, press **Home** while the game window is in front.
- On an Xbox gamepad, press both stick clicks together.

Recenter whenever your view is facing the wrong way or you feel offset from Bond. After a recenter, turning your head while standing still should not slide the world.

### Crouch and stand

While you are aiming (holding the grip on your gun hand, see [Aim](#aim-down-the-sights)):

- Push the **right stick up** to stand.
- Push the **right stick down** to crouch.

While you are aiming, the **left stick** still walks you forward and back without making you crouch by accident.

### Pause

Press the **Menu** button on the **left** controller. This opens Bond's watch (the pause menu). In the shipped VR setup, **Left Y** also pauses.

---

## 6. One squeeze, many jobs

The **grip** is the button under your middle finger. You squeeze it. In GEVR, the grip does different jobs depending on **where your hand is** when you squeeze.

| Where your hand is | What a grip squeeze does |
|---|---|
| Out in front, holding a gun | **Aim** down the sights |
| At a door you are standing next to | **Open or close** the door |
| Near a weapon lying on the ground | **Pick it up** into that hand |
| Near a mine you placed yourself (left hand) | **Pick the mine back up** |
| Right hand touching the **left watch face** | **Watch press** (laser, detonator or magnet) |
| Right hand low at your **right hip** | **Holster or draw** your right-hand gun |
| Left hand on the front of a long gun held in your right hand | **Two-hand hold** |

Each of these is explained below.

---

## 7. Weapons

### Fire (each hand has its own trigger)

- **Right trigger** fires the gun in your **right** hand.
- **Left trigger** fires the gun in your **left** hand when you are holding two guns.

Each trigger only fires its own hand's gun.

### Aim down the sights

Squeeze the **right grip** to aim the right-hand gun. The aim mark sits on the line of the gun, not stuck to your face. Let go to stop aiming.

When your left hand holds a gun, the **left grip** aims that gun the same way.

### Use, reload, activate (B)

Press **B** on the right controller. B is GoldenEye's single action button. It does all of these:

- Reload.
- Open doors and flip switches from a short distance.
- Plant and activate gadgets.
- Every other action the original game puts on B.

### Change weapons

Each hand has its own list of weapons.

- **A** on the right controller steps to the **next weapon in your right hand**.
- **X** on the left controller steps through the **weapons for your left hand**.

### Pick up a weapon from the ground

Put your hand near a weapon lying on the ground and **squeeze the grip** of that hand. The weapon goes into **that** hand.

### Hold two guns (dual-wield)

To hold a gun in each hand, put a second gun in your left hand. Either step through your left-hand weapons with **X**, or pick one up with the left grip.

Then **left trigger** fires the left gun and **right trigger** fires the right gun.

You cannot put the **same** gun in both hands unless the original game allows that pair.

### Hold a long gun with two hands

Rifles, shotguns, SMGs and the grenade launcher can be steadied with your second hand.

1. Hold the long gun in your **right** hand.
2. Keep your left hand empty.
3. Bring your **left controller** forward along the barrel, to the front of the gun (the fore-end).
4. **Squeeze the left grip** and hold it.
5. The gun now aims along the line between your two hands.
6. **Let go** of the left grip to go back to aiming with the right hand only.

The two-hand hold works with the long gun in your **right** hand, supported by your left.

### Holster and draw at your right hip

You can put your right-hand gun away on your hip and switch to Bond's fist, then draw it again.

1. Your **left hand must be empty** (just the watch cuff, no gun).
2. Lower your **right hand** to your **right hip**.
3. **Squeeze the right grip.** The gun goes to your hip and Bond's fist comes out.
4. To draw the gun again, lower your right hand to your right hip and **squeeze the right grip** again.

### Throw grenades and mines

Grenades, timed mines, remote mines, proximity mines, plastique, the covert modem and similar items appear in your hand.

- Press the **trigger** to throw or fire them.
- Press **B** to plant or activate where the original game uses B.

### Pick your mines back up

After you throw or plant a mine, you can take it back.

1. Reach your **left hand** to a mine you placed yourself.
2. **Squeeze the left grip.** The mine comes back to you.

This works for your own **remote mines** and for **proximity mines that are still arming**. It does **not** work on live grenades or on traps that are already armed.

### Doors

Walk up to a door and **squeeze the grip** to open or close it. You do not need to reach out and press a separate button when you are in range. **B** also opens doors and switches from a short distance.

---

## 8. Bond's watch

Bond's watch lives on your **left wrist** (the cuff). You use it two ways:

- The **pause watch**: the menu where you choose gadgets.
- The **cuff press**: touching the watch with your right hand to use the gadget you chose.

You never need to put a big watch model in your gun hand.

### Open the pause watch and choose a gadget

1. Press **Menu** on the left controller (or **Left Y**).
2. Move the highlight with the **left stick**.
3. Confirm with the face buttons, the same way as the original game's watch pages.

From the pause watch you can choose **Watch Laser**, **Detonator**, **Watch Magnet Attract**, **Watch Magnet Repel**, and other items the level gives you.

If a level does not give you a laser, a **Watch Laser** row can still appear in the watch list for solo play.

### Watch Laser or Detonator: which to choose

What the cuff press does depends on what you chose:

| You chose | Cuff press does |
|---|---|
| **Watch Laser** | Fires the **laser only**. It never sets off mines on that press. |
| **Detonator** | **Sets off your planted remote mines** if you have any out. If you have none, it fires the **laser**. |

Pick **Watch Laser** when you want to be sure you will not blow your mines by mistake. Pick **Detonator** when you want one press to do the right thing on its own.

### Do a cuff press (laser or detonator)

1. Make sure the watch is **not** opening on screen.
2. Touch your **left watch face** with your **right controller**.
3. **Squeeze the right grip** as a **new** squeeze.

A squeeze you were already holding before your hand reached the watch does not count. Let go, touch the watch, then squeeze.

### Watch Magnet Attract

The magnet pulls metal objects toward you, like the original game.

1. In the **pause watch**, select **Watch Magnet Attract**. You keep your guns in your hands.
2. Close the pause watch.
3. Touch your **left watch cuff** with your **right hand**.
4. **Squeeze the right grip**. This is the same gesture as the laser.

Each press uses **watch magnet ammo** and sends out **one** pull. If you have no magnet ammo, you hear an empty click.

To pull again later, select **Watch Magnet Attract** in the pause watch again, then do the cuff press again.

### Watch Magnet Repel

Repel is chosen from the **pause watch**, like the original game. Select **Watch Magnet Repel** there and use it the way the original game's watch items work. There is **no** cuff shortcut for repel.

---

## 9. Valve Index button names

Index controllers do the same things as Quest controllers. Use this table to match the names.

| Index control | Same as on Quest | What it does |
|---|---|---|
| Right trigger | Right trigger | Fire the right-hand gun |
| Left trigger | Left trigger | Fire the left-hand gun (two guns) |
| Right grip | Right grip | Aim; doors; watch press; hip holster |
| Left grip | Left grip | Aim the left gun; doors; pick up; mine regrab; two-hand hold |
| Right thumbstick | Right stick | Turn |
| Left thumbstick | Left stick | Walk |
| Right A | Right A | Next weapon (right hand) |
| Right B | Right B | Use / reload / activate |
| Left X (face button) | Left X | Weapon step (left hand) |
| Left Y | Left Y | Pause (in the shipped setup) |
| System / menu button | Quest Menu | Pause |

---

## 10. GEVR Settings

GEVR Settings is where you change picture, monitor and profile options. It is **not** the pause watch.

### Find it

On the **intro hub**, **look to your right**. You will see a glass panel called **GEVR Settings**, styled like GoldenEye's folder menus.

### Use it

1. Press **A** to enter the row you want to change.
2. Push the stick **left or right** to cycle that row's value.
3. Press **A** again to accept the value.
4. When you are done, highlight **Apply** and press **A**. GEVR **saves your choices and restarts** into them.

Changes do not take effect until you Apply.

Outside this menu, during play, **A** is "next weapon". It does not open settings.

### The rows you will use

| Row | Default | What it does |
|---|---|---|
| **Visual mode** | VR | Chooses **VR**, **XR** or **Flat**. Each has its own saved settings. |
| **Supersample** | 3 Sharp | Picture sharpness versus speed. |
| **Monitor output** | Both eyes | What the desktop screen shows while you play in VR or XR. |
| **Frame rate** | Headset | Follows your headset's refresh rate. |
| **HD textures** | Off | Turns on an HD texture pack you installed yourself. |
| **Beta** | None yet | Nothing to set yet. |
| **Reset defaults** | No | Puts the current Visual mode's settings back to default. |
| **Apply** | | Saves and restarts. |

The menu also has Full screen, Window, Filter and Game speed rows. Leave them as they are unless you have a reason to change them.

### Visual mode: VR, XR and Flat

| Mode | What you get |
|---|---|
| **VR** | Full headset VR. This is the default. |
| **XR** | The game shown inside a square outline with a black frame around it, in the headset. |
| **Flat** | A normal flat game on your monitor. |

Each mode keeps **its own saved settings**. To change the settings for a different mode, switch Visual mode to that mode first, change the rows, then Apply. GEVR restarts into that mode's profile.

### Supersample

| Value | What it means |
|---|---|
| **1 Fast** | Same number of pixels as the window. Softest picture, lightest on your PC. |
| **2 Clear** | Four times the pixels. A good middle setting. |
| **3 Sharp** | Nine times the pixels. Sharpest picture, heaviest on your PC. This is the default. |

If the game stutters in the headset, try **2 Clear** or **1 Fast**.

### Frame rate

The default is **Headset**. It follows your headset's own refresh rate. Leave it on Headset for headset play.

### Monitor output

This row only matters while you play in **VR** or **XR**. It picks what your desktop screen shows:

- **Both eyes**
- **Left eye only**
- **Right eye only**
- **No output** (nothing on the desktop; this can help performance)

Your choice is **saved** with the VR and XR profiles. The row is greyed out in Flat mode and has no effect there.

### Beta

The Beta row is where test options will go in future builds. Today it says **None yet**. There is nothing to set.

### Reset defaults

Set **Reset defaults** to **Yes** to put the current Visual mode back to its defaults. The menu asks "Are you sure?" first. Only the profile for the Visual mode you are on is reset.

### Where settings are kept

GEVR Settings and your saves are stored under `%LOCALAPPDATA%\GEVR`. They are kept when you update GEVR.

---

## 11. HD textures

HD textures are **off by default**. GEVR does **not** include an HD pack. You download one yourself.

1. Download the community **GLideN64 PNG** zip. Do **not** use the `.hts` file. Get it from either:
   - [GoldenEye-007-HD releases](https://github.com/GhostlyDark/GoldenEye-007-HD/releases)
   - [GE007 HD texture pack page](https://evilgames.eu/texture-packs/ge007-hd.htm)
2. Go to the folder where `goldeneye.exe` is (the folder you unzipped GEVR into).
3. Make a folder there called **`hdtextures`** if it is not already there.
4. Extract the pack so the **`GOLDENEYE`** folder sits inside **`hdtextures`**. Do not rename any of the picture files.
5. Start GEVR. In **GEVR Settings**, set **HD textures** to **On**.
6. Highlight **Apply** and press **A**. GEVR restarts with the HD textures.

The finished folder should look like this:

```
<your GEVR folder>\
    goldeneye.exe
    hdtextures\
        GOLDENEYE\
            (the pack's picture files)
```

If HD textures is On but no pack is installed, you see the normal N64 textures.

---

## 12. Playing on a monitor (flat)

Start **`Play-on-monitor.bat`**. VR is off and the game plays on your screen.

Mouse look is on by default.

| Key or button | What it does |
|---|---|
| Mouse move | Look and turn |
| Left mouse button | Fire |
| Right mouse button | Aim |
| W A S D | Walk |
| Arrow keys | Turn |
| Space or Left Ctrl | Fire |
| Q | Aim |
| E or F | Use / reload / activate |
| R or Enter | Next weapon |
| C or Left Shift | Crouch (hold) |
| V | Stand (hold) |
| Tab or Numpad Enter | Pause |
| I J K L | D-pad |
| Home | Recenter |
| Esc | Release the mouse cursor |

---

## 13. Updating GEVR

- Use **Update** in GevrRomStarter, or download the new zip and unzip it.
- Keep using the same USA `.z64`.
- The first launch after an update prepares the game pictures again, once. This is normal.
- Your **saves** and **GEVR Settings** are kept.

---

## 14. Troubleshooting

### Controls or VR feel dead

1. Make sure you started with **`Start-GEVR.bat`** (headset) or **`Play-on-monitor.bat`** (monitor), not `goldeneye.exe`.
2. Recenter with **both** stick clicks.
3. Check that Windows is using the OpenXR runtime you expect (SteamVR, PimaxXR, Virtual Desktop, and so on).

### The game feels half speed or mushy in the headset

- **SteamVR:** open Settings, then Video, and set **Motion Smoothing** to **Off**. Also check the per-application setting for GEVR / `goldeneye.exe`.
- **Virtual Desktop:** turn **Space Warp** **Off**.

### The picture looks wrong

1. Close GEVR.
2. Run **`Clear-GEVR-cache.bat`** and type **YES** when asked.
3. Start GEVR again with the bat. It prepares the pictures again from your ROM.

Only delete the whole `%LOCALAPPDATA%\GEVR` folder if that does not help. Deleting it also removes your saves and settings.

### The game crashed

Before you start the game again, look beside `goldeneye.exe` for a file named **`gevr-fault-*.txt`**. Keep a copy. It helps the team find the problem.

---

## 15. Reporting a problem

Report bugs on GitHub: **https://github.com/no6969el/GEVR/issues/new/choose**
Chat and help: **https://discord.gg/flat2vr**

Please include:

- Your headset.
- Your OpenXR runtime.
- Whether SteamVR was on or off.
- Whether you played in the headset or on the monitor.
- Whether you started with `Start-GEVR.bat`.
- The `gevr-*-boot.cmd` file name from your GEVR folder.
- Any log next to the zip or in the console window.
- Any `gevr-fault-*.txt` beside the exe.

**Never upload your ROM.**

---

## 16. Quick reference card

**Headset (Quest names; Index uses the same buttons, see section 9)**

| Do this | To |
|---|---|
| Left stick | Walk / strafe |
| Right stick | Turn |
| Both stick clicks together | Recenter |
| Hold grip + right stick up / down | Stand / crouch |
| Right trigger | Fire right-hand gun |
| Left trigger | Fire left-hand gun |
| Grip (gun in hand) | Aim |
| Grip at a door | Open / close |
| Grip near a ground weapon | Pick up into that hand |
| Left grip on your own mine | Take the mine back |
| Left grip on the front of a long gun (gun in right hand) | Two-hand hold |
| Right grip at right hip (left hand empty) | Holster / draw |
| Right B | Use / reload / activate |
| Right A | Next weapon, right hand |
| Left X | Weapon step, left hand |
| Menu or Left Y | Pause watch |
| Right hand on left watch + new grip squeeze | Cuff press: laser, detonator or magnet attract |

**Pause watch choices**

| Choose | Cuff press then does |
|---|---|
| Watch Laser | Laser only |
| Detonator | Sets off your remote mines, or laser if none are out |
| Watch Magnet Attract | One magnet pull (uses magnet ammo) |
| Watch Magnet Repel | Used from the pause watch; no cuff press |

**GEVR Settings (intro hub, look right)**

A enters a row. Stick left / right changes it. A accepts. Apply + A saves and restarts.

**Controls video:** https://www.youtube.com/watch?v=Jst5srE6Iwc
