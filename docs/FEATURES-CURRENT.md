# Features (current Beta)

> Player snapshot: [FEATURES.md](../FEATURES.md). Play [vr457](https://github.com/no6969el/GEVR/releases/latest) (GitHub Latest). Install: [README](../README.md#install). How to use this cut: [README vr457](../README.md#vr457). Hands: [CONTROLS.md](CONTROLS.md).

Current zip: **[`GEVR-Beta-vr457-win64.zip`](https://github.com/no6969el/GEVR/releases/download/vr457/GEVR-Beta-vr457-win64.zip)**. Tag: [vr457](https://github.com/no6969el/GEVR/releases/tag/vr457). The zip has no ROM and no HD texture pack.

## vr457

**How to read the tags.** **Passed** means tested in a headset on an earlier test build. **New** means built and checked on the bench, not yet tested in a headset. This release as a whole has not had a full headset pass.

**Fresh-install defaults:** hands and arms on, weather Original (no falling weather), enemy AI Classic (the original guards), auto pickup on, instant gesture reload (the physical magazine reload is off), squad chatter muted, scope magnifier on, pull and disarm on, upscaler off. Change any of them in **GEVR Settings** and press **Apply**; your saved choices always win.

### New in vr457 (not yet tested in a headset)

- **Hands and arms** (on by default): new hands and sleeves, arms that follow your body, and a closed watch band on the left wrist with the watch case on top. Small guns are drawn from the jacket, long guns from over the shoulders. Grenades and mines keep the old hold for now. **HANDS AND ARMS** Off gives the old hands and hip holsters back.
- **Pickup options:**
  - **AUTO PICKUP** (on by default, HANDS AND GUNS page): walk over a gun to collect it. Both hands empty: it goes into your right hand. A gun already in a hand: the new gun goes to your inventory. A second copy of a gun you own gives the dual pair in your inventory; a third copy gives ammo only. Off leaves the gun on the floor until you grab or pull it.
  - **Force-pull landing:** hold the grip until the gun arrives and it lands in your hand and stays there. Let go while it is still flying and it lands in your inventory. With a gun already in one hand, pulling another with the free hand sends it to your inventory.
  - **Stick click** with a gun in your hand puts the gun away into your inventory.
  - **Two-gun swap:** a gun in each hand, hands together, squeeze both grips at nearly the same moment, and the guns swap hands.
- **Scope magnifier:** the sniper scope and the Moonraker lens grow as your eye comes close (full size beyond about 30 cm, up to two and a half times bigger at about 12 cm). The zoom level itself does not change.
- **Weather:** **Off**, **Original** (default, the game as it was), **Enhanced** (snow and rain on the levels that have it, now also out to about 18 metres) and **Dynamic** (the weather changes by itself). Rows for intensity, weather type, ground effects, lightning flashes, whether weather hinders Tactical guards, and a seed. It never changes fog, draw distance or sky colour.
- **Enemy AI:** **Classic** (default, the original guards), **Tactical** and **Tactical+** (cover, flanking, calling for help, falling back; they fire first when they meet you close up). **AGGRESSION** runs from Calm to Ruthless. Squad radio chatter is muted; spotted shouts and man-down yells still play.
- **Train and objective scripts:** the two key guards leave their posts after the brakes objective. The same fix applies to other levels where a guard waits for "objective N complete".
- **GEVR Settings pages:** GRAPHICS, VR, HANDS AND GUNS, WEATHER, ENEMY AI and BETA. The launcher Options tab has the render scale slider, a New hands checkbox, and the Enemy AI picker with an aggression slider.

### Passed in a headset on earlier test builds

- VR eyes independent of the desktop window and Supersample. **VR render scale** 50 to 150 percent. MSAA in VR sizes itself to your graphics memory.
- **Force-pull** of a gun, ammo, key or armour. **Pull and disarm:** force-pull a gun out of a guard's hand (a magnet sound and the watch glows).
- Door and wall buttons press when touched; hinged doors push open with the palm. Held items follow your hand and drop onto whatever is below.
- Menus and cinema fit one eye's picture, and there is no white flash between menus and a level.

### Known issues in vr457

- The plastique from All Weapons can keep exploding and follow you. Leave All Weapons off when you place plastique.
- Hands and arms: the thumb sits oddly on some guns (small, or not wrapped around the grip; on the shotguns it can point up). On the KF7 Soviet the left-side view draws the palm over the grip.
- Tactical and Tactical+ enemy AI are options, not the default, and have not passed a headset test. Classic is the safe choice.
- Multiplayer bots are not included. The physical magazine reload is off (still experimental). The first time HD textures appear in a level you may feel a short hitch. Windowed only (no Fullscreen toggle).

### Beta rows (off)

- **HD TEXTURE SET** (GEVR Settings > BETA): Off, GE007 HD, GEVR Curated, or Curated plus AI fills. It needs a folder of pictures on your own disk; the zip has none.
- **UPSCALER** (GEVR Settings > BETA): needs an RTX card and NVIDIA's own runtime files, which are not in this zip. Without them the row does nothing.

### Carried from earlier cuts

- **Corpse freeze:** a defeated guard's body freezes after the death animation (in since vr456.9).
- **Visual mode:** VR, XR (smaller screen, black outline), or Flat on the monitor. Change the row in **GEVR Settings** and **Apply**. Apply saves and relaunches into that mode.
- **Frame rate:** follows the headset by default. Fixed 90 is still available.
- **VR render scale** sets the headset picture size, 50 to 150 percent (Flat keeps **Supersample**). **Filter** starts on bilinear. Point is still available.
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
- **Reload:** gesture reload (instant by default; the physical magazine reload is off) or chest cross. B is USE, not VR gun reload. Handle grab swaps hands and does not reload.
- **Left hand:** a left-hand gun fires on its own.
- **Ammo:** digits sit on the grip and read from behind the gun. Flat mode keeps the corner count. Weapon pictures sit on the lifting hand.
- **Mines:** remote, proximity, and timed mines draw in the hand like the grenade.
- **Swing:** uses the held weapon's damage. Shooting does not make the knife swing by itself.
- **Sniper:** green dot stays on. Right stick forward or back steps the zoom (30, 20, 15, 10, 7).
- **Watch:** Y opens it. GAME OPTIONS goes past ratio. Scroll down for VR settings.
- **Janus meeting:** the crowd stops respawning after the meeting.
- **HD textures:** PNG pack in `hdtextures\GOLDENEYE` next to `goldeneye.exe`. `GOLDENEYE_HIRESTEXTURES.hts` is the wrong file. GEVR does not ship the pack.

Not in this build: live wrist watch panel, throwing any prop, multiplayer bots, DLSS frame generation and neural upscaling.

## Still in this cut

- OpenXR stereo, room-scale walk, recenter on both stick clicks, grip to open doors
- Aim along the gun, tank mount, bring your own USA ROM
- GevrRomStarter **Update** follows GitHub Latest

## Headset / runtime

Pimax (SteamVR OpenXR + CustomHeadsetOpenVR), native PimaxXR, Quest 3 + Virtual Desktop. See [README](../README.md#what-we-tested).

Controls: [CONTROLS.md](CONTROLS.md). Beta notes: [BETA.md](BETA.md).
