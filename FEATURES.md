<p align="center">
 <img src="GEVR-box-cover.png" alt="GoldenEye 007 VR - GEVR box art" width="520" />
</p>

# GEVR - stand inside GoldenEye

**Native VR. Bring your own ROM. Beta is live.**

GEVR rebuilds GoldenEye on PC for real OpenXR stereo, so you can stand in the Facility. You bring a USA GoldenEye ROM you own. The zip has no ROM and no HD texture pack.

**Latest:** [**GEVR Beta vr457**](https://github.com/no6969el/GEVR/releases/latest). Zip: **`GEVR-Beta-vr457-win64.zip`**.

[Install](README.md#install) · [VR actions](README.md#vr-actions) · [vr457](https://github.com/no6969el/GEVR/releases/tag/vr457) · [Credits](CREDITS.md)

The how-to for this cut is on the [README](README.md#vr457). Hands: [docs/CONTROLS.md](docs/CONTROLS.md). This page is the short pitch.

---

## What you do in vr457

**GEVR Settings** is on **Mission Select**, next to **Select Mission**, **Multiplayer**, and **Cheat Options**. It is not named Options. Change a row, then **Apply**. Apply saves and relaunches into that mode. GEVR Settings is now a set of pages: **GRAPHICS**, **VR**, **HANDS AND GUNS**, **WEATHER**, **ENEMY AI** and **BETA**.

**How to read the tags.** **Passed** means tested in a headset on an earlier test build. **New** means built and checked on the bench, not yet tested in a headset. This release as a whole has not had a full headset pass.

**Fresh-install defaults:** hands and arms on, weather Original (no falling weather), enemy AI Classic (the original guards), auto pickup on, instant gesture reload (the physical magazine reload is off), squad chatter muted, scope magnifier on, pull and disarm on, upscaler off. Your saved choices always win.

### New in vr457 (not yet tested in a headset)

- **Hands and arms** (on by default): new hands and sleeves, arms that follow your body, a closed watch band on the left wrist. Small guns are drawn from the jacket and long guns from over the shoulders. Grenades and mines keep the old hold for now. **HANDS AND ARMS** Off brings back the old hands and hip holsters.
- **Pickup options:** **AUTO PICKUP** (on by default) collects a gun when you walk over it: into your right hand if both hands are empty, otherwise into your inventory. Force-pull: hold the grip until it arrives and the gun stays in your hand; let go while it is flying and it lands in your inventory. A stick click with a gun in your hand puts it in your inventory. With a gun in each hand, bring your hands together and squeeze both grips to swap them.
- **Scope magnifier:** the sniper scope and the Moonraker lens grow as your eye comes close, so you do not have to press the headset against them.
- **Weather:** **Off**, **Original** (default, the game as it was), **Enhanced** (snow and rain on the levels that have it, also out across the yard) and **Dynamic** (the weather changes by itself). It never changes fog, draw distance or sky colour.
- **Enemy AI:** **Classic** is the default (the original guards). **Tactical** and **Tactical+** are optional: cover, flanking, calling for help and falling back, with an aggression setting. Squad radio chatter is muted.
- **Train:** the key guards leave their posts after the brakes objective. The same fix covers other levels where a guard waits for "objective N complete".

### Passed in a headset on earlier test builds

- VR eyes independent of the desktop window, VR render scale 50 to 150 percent, and MSAA that sizes itself to your graphics memory.
- **Force-pull** of a gun, ammo, key or armour, and **pull and disarm** a gun out of a guard's hand.
- Door and wall buttons press when touched, hinged doors push open with your palm, held items follow your hand, and there is no white flash between menus and a level.

### Known issues in vr457

- The plastique from All Weapons can keep exploding and follow you. Leave All Weapons off when you place plastique.
- Hands and arms: the thumb sits oddly on some guns; on the KF7 Soviet the left-side view draws the palm over the grip.
- Tactical and Tactical+ enemy AI have not passed a headset test. Classic is the safe choice.
- Multiplayer bots are not included. The physical magazine reload is off (still experimental). The first time HD textures appear in a level you may feel a short hitch. Windowed only.

### Carried from earlier cuts

- **Visual mode:** **VR**, **XR** (smaller screen, black outline), or **Flat** on the monitor.
- **Frame rate** follows the headset. **Fixed 90** is still available.
- **VR render scale** sets the headset picture size, 50 to 150 percent (Flat keeps **Supersample**). **Filter** starts on bilinear. **Point** is still available.
- **Monitor:** **Both**, **Left**, **Right**, or **Off**. Off blanks the mirror while you stay in the headset.
- **Stick weapon wheel:** stick click opens a circle (NO WEAPON at 12 o'clock). Centre follows the hover. Boxes are 2x dark grey. **STICK WHEEL** can set Weapon Vert.
- **Left X** is the next weapon on the left hand. **Right A** is the next weapon on the right hand.
- **Holster swap:** same-gun hip grip is a real swap. Weapon switch prefers a free inventory copy over the hip gun.
- **Watch picker:** pictures and labels on the left cuff (Laser / Magnet / Repel). Magnet is unlimited in VR. Laser and Repel stay on the normal watch item flow.
- **Moonraker:** small circular scope lens only. Look through the ring. Shoot through the ring. Dual Moonrakers give two lenses. No front grill screen.
- **Rockets** stay locked to the launcher, not your head. Flat mouse-aim crosshair stays centred.
- **Snap-turn** is real degrees. Red and green **aimers** sit on the shot's first hit.
- **Left-hand throwables** draw the right way around.
- **Tank** shells auto-load after you fire.
- **VR comfort:** no walk bob, no landing dip, no gun-hand sway.
- **HD load:** textures come in without hitching the headset. Levels feel smooth when pictures arrive.
- **Monitor Off** blanks the mirror cleanly. Your saved Monitor Output row still decides on or off.
- **HD memo** keeps decoded HD pictures in memory (`GETV_HD_MEMO_MB=0` turns it off).
- **XR catch-up:** missed headset frames no longer slow the sim. Quitting actually quits.
- Reload guns with the gesture (magazine or chest cross). Instant gesture reload is the default; the physical magazine reload is off (still experimental). **B** is USE, not VR gun reload.
- A left-hand gun fires on its own.
- Ammo digits sit on the grip and read from behind the gun. Flat mode keeps the corner count. Weapon pictures sit on the lifting hand.
- Remote, proximity, and timed mines draw in the hand like the grenade.
- A swing uses the held weapon's damage. Shooting does not make the knife swing by itself.
- Sniper: a green dot stays on. Right stick forward or back steps the zoom (30, 20, 15, 10, 7).
- **Y** opens the watch. **GAME OPTIONS** goes past ratio. Scroll down for VR settings.
- After the Janus meeting, the crowd stops respawning.

### HD textures

**GEVR does not ship the pictures.** [GoldenEye-007-HD releases](https://github.com/GhostlyDark/GoldenEye-007-HD/releases) · [evilgames GE007 HD](https://evilgames.eu/texture-packs/ge007-hd.htm): a **GLideN64 PNG** zip, not `.hts`. Put the pack in **`hdtextures\GOLDENEYE`** next to `goldeneye.exe`. `GOLDENEYE_HIRESTEXTURES.hts` is the wrong file. Turn HD textures **On**, then **Apply**. The pack loads on the next boot.

Full sentences and the button tables: [README](README.md#vr457) · [CONTROLS.md](docs/CONTROLS.md).

---

## On the box

- OpenXR VR. You stand in the room.
- Walk your playspace and Bond moves with you. Recenter with **both thumbstick clicks**.
- Point the controller to aim. Squeeze to aim down the gun. The **right trigger** fires the right hand. The **left trigger** fires a left-hand gun on its own.
- Stick click opens the weapon wheel. Hip holster swap. Watch picker on the cuff.
- While you aim, walk on the left stick and crouch on the right stick.
- Grip a door to open or close it.
- Throwables leave from the hand.
- Stand on a tank to mount it. The stick pitches the cannon. Empty mag auto-loads the next shell.
- The in-app **Update** button in GevrRomStarter follows GitHub Latest.
- Local split-screen on a monitor. Flat play uses `Play-on-monitor.bat`, or Visual mode **Flat**.
- Not in this build: live wrist watch panel, throwing any prop, multiplayer bots, DLSS frame generation and neural upscaling.

---

## The VR stuff that makes it feel like yours

**You are in the room.** Walk your playspace and Bond walks with you. Turn your head and the world stays put. Recenter anytime with **both thumbstick clicks**. No walk bob, no landing dip, no extra gun-hand sway.

**The gun is in your hand.** Point the controller. **Right trigger** fires the right-hand gun. **Left trigger** fires the left-hand gun whenever that hand holds one. Squeeze to aim. The mark sits on the gun. With two guns, each trigger fires its own hand.

**Hands do Bond things.** A swing uses the weapon you are holding. Reload with the magazine or chest-cross gesture. Mines and grenades show in the hand. Stick click opens the wheel.

**Tanks that let you in.** Stand on the chassis and you mount. The stick pitches the shells. The next round auto-loads.

**Menus stay in the world.** **GEVR Settings** is on Mission Select, next to Select Mission, Multiplayer, and Cheat Options. In a mission, **Y** opens the watch, and **GAME OPTIONS** carries the VR rows below ratio.

**It looks like GoldenEye, in stereo.** The pictures come from your ROM. An optional PNG pack goes in `hdtextures\GOLDENEYE` next to the exe.

---

## What we tested

| Path | Notes |
|------|--------|
| **Pimax Crystal Super + SteamVR OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR) (sboys3) | Primary wear path |
| **Native PimaxXR** | Verified attach / play |
| **Meta Quest 3 + Virtual Desktop OpenXR (VDXR)** | Verified attach / play |

---

## Play

1. Grab **[`GEVR-Beta-vr457-win64.zip`](https://github.com/no6969el/GEVR/releases/latest)**. The archive has no ROM and no HD texture pack.
2. Follow [README Install](README.md#install).
3. [VR actions](README.md#vr-actions) and [CONTROLS.md](docs/CONTROLS.md) for the full bind list.

Report bugs: [CONTRIBUTING.md](CONTRIBUTING.md). Do not upload your ROM.
