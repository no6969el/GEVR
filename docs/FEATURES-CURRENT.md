# Features (current Beta)

> Player snapshot: [FEATURES.md](../FEATURES.md). Play [vr456.5](https://github.com/no6969el/GEVR/releases/latest) (GitHub Latest). Install: [README](../README.md#install). How to use this cut: [README vr456.5](../README.md#vr4565). Hands: [CONTROLS.md](CONTROLS.md).

Current zip: **[`GEVR-Beta-vr456.5-win64.zip`](https://github.com/no6969el/GEVR/releases/download/vr456.5/GEVR-Beta-vr456.5-win64.zip)**. Tag: [vr456.5](https://github.com/no6969el/GEVR/releases/tag/vr456.5). The zip has no ROM and no HD texture pack.

## vr456.5

- **Visual mode:** VR, XR (smaller screen, black outline), or Flat on the monitor. Change the row in **GEVR Settings** and **Apply**. Apply saves and relaunches into that mode.
- **Frame rate:** follows the headset by default. Fixed 90 is still available.
- **Supersample** starts at 3. **Filter** starts on bilinear. Point is still available.
- **Monitor:** Both, Left, Right, or Off. Off blanks the mirror while you stay in the headset.
- **GEVR Settings:** on Mission Select, next to Select Mission, Multiplayer, and Cheat Options. It is not named Options.
- **Stick weapon wheel:** stick click opens a circle (NO WEAPON at 12 o'clock). Centre follows the hover. Boxes are 2x dark grey. **STICK WHEEL** can set Weapon Vert.
- **Weapons:** Left X is the next weapon on the left hand. Right A is the next weapon on the right hand.
- **Holster swap:** same-gun hip grip is a real swap. Weapon switch prefers a free inventory copy over the hip gun.
- **Watch picker:** pictures and labels on the left cuff (Laser / Magnet / Repel). Magnet is unlimited in VR. Laser and Repel use the normal watch item flow.
- **Moonraker:** small circular scope lens only. Look through the ring. Shoot through the ring. Dual Moonrakers give two lenses. No front grill screen.
- **Rockets:** stay locked to the launcher, not your head. Flat mouse-aim crosshair stays centred.
- **Snap-turn:** real degrees (15 / 22.5 / 30 / 45 / 60 / 90) plus click-to-edit SETTINGS glass.
- **Aimers:** red and green on the shot's first hit.
- **Left-hand throwables:** no mirror.
- **HD memo:** decoded HD pictures stay in memory. `GETV_HD_MEMO_MB=0` turns it off.
- **Tank autoload:** shells keep retail empty-mag autoload.
- **VR comfort:** no walk bob, landing dip, or gun-hand sway.
- **XR catch-up / quit:** missed headset frames no longer slow the sim. Quitting actually quits.
- **Reload:** magazine or chest-cross gesture. B is USE, not VR gun reload. Handle grab swaps hands and does not reload.
- **Left hand:** a left-hand gun fires on its own.
- **Ammo:** digits sit on the grip and read from behind the gun. Flat mode keeps the corner count. Weapon pictures sit on the lifting hand.
- **Mines:** remote, proximity, and timed mines draw in the hand like the grenade.
- **Swing:** uses the held weapon's damage. Shooting does not make the knife swing by itself.
- **Sniper:** green dot stays on. Right stick forward or back steps the zoom (30, 20, 15, 10, 7).
- **Watch:** Y opens it. GAME OPTIONS goes past ratio. Scroll down for VR settings.
- **Janus meeting:** the crowd stops respawning after the meeting.
- **HD textures:** PNG pack in `hdtextures\GOLDENEYE` next to `goldeneye.exe`. `GOLDENEYE_HIRESTEXTURES.hts` is the wrong file. GEVR does not ship the pack.

Not in this zip: 0085 thermal, 0086 corpse freeze, Gun Drop / Arm Bounds default-on.

## Still in this cut

- OpenXR stereo, room-scale walk, recenter on both stick clicks, grip to open doors
- Aim along the gun, tank mount, bring your own USA ROM
- GevrRomStarter **Update** follows GitHub Latest

## Headset / runtime

Pimax (SteamVR OpenXR + CustomHeadsetOpenVR), native PimaxXR, Quest 3 + Virtual Desktop. See [README](../README.md#what-we-tested).

Controls: [CONTROLS.md](CONTROLS.md). Beta notes: [BETA.md](BETA.md).
