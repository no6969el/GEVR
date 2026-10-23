GEVR Beta **vr457** - Windows.

Bring your own USA GoldenEye ROM. No ROM, HD pack or NVIDIA file is inside the zip.

Play: `Start-GEVR.bat` only.

Report issues: https://github.com/no6969el/GEVR/issues/new/choose

Linux flat alpha (separate): https://github.com/no6969el/GEVR/releases/tag/linux-alpha1

## Defaults for a fresh install

Hands and arms on. Weather Original (no falling weather). Enemy AI Classic (the original guards). Auto pickup on. Instant gesture reload (the physical magazine reload is off). Upscaler off. Change any of them in GEVR Settings; your saved choices always win.

## Highlights since vr456.9

- Passed in the headset on earlier test builds: VR eyes independent of the desktop window, VR render scale 50 to 150 percent, MSAA that sizes itself to your graphics memory, force-pull, pull a gun out of a guard's hand, door and wall button touch, hinged doors that push open, held items that follow your hand, no white flash between menus and a level.
- New, not yet tested in a headset: new hands and arms (on by default, with a closed watch band), pickup options (auto pickup, pull landing, stick click, two-gun swap), a scope magnifier, Enhanced and Dynamic weather with rain out to the far yard, optional Tactical enemy AI, the Train key guards leaving after the brakes, and GEVR Settings as pages.

## Known issues / in progress

- The plastique from All Weapons can keep exploding and follow you. Leave All Weapons off when you place plastique.
- Hands and arms: the thumb sits oddly on some guns; on the KF7 Soviet the left-side view draws the palm over the grip.
- Tactical and Tactical+ enemy AI are options, not the default, and have not passed a headset test.
- Multiplayer bots are not included.
- The physical magazine reload is off (still experimental).
- The first time HD textures appear in a level you may feel a short hitch.
- Windowed only (no Fullscreen toggle).

## Tester's notes

Windows build. Bring your own USA GoldenEye ROM. No ROM, HD texture pack, or NVIDIA file is inside the zip. Start with `Start-GEVR.bat`.

How to read the status tags below:

- **Passed in the headset** - tested in a headset on an earlier test build and it worked. This release as a whole has not had a full headset pass.
- **New** - built and checked on the bench, not yet tested in a headset. Please try these and report.

## What you get by default

A fresh install starts with: **Hands and arms ON**, **Weather Original** (the game as it was, no falling weather), **Enemy AI Classic** (the original guards), **Auto pickup ON**, **instant gesture reload** (the physical magazine reload is off), and the upscaler off. Change any of them in **GEVR Settings** (Mission Select, next to Select Mission) and press **Apply**. Your saved choices always win over these defaults.

## Known issues / in progress

- The plastique from All Weapons can keep exploding and follow you. Leave All Weapons off when you place plastique.
- Hands and arms: the thumb sits oddly on some guns (small, or not wrapped around the grip; on the shotguns it can point up). The four fingers are fine.
- KF7 Soviet: with the hands on, looking at the left side of the gun draws the inside of the palm over the grip; from the right side the gun shows and the hand does not.
- Tactical and Tactical+ enemy AI are options, not the default, and have not passed a headset test: some guards may ignore you or act strangely. Classic is the safe choice.
- Multiplayer bots are not included.
- The physical magazine reload (squeeze to pull the magazine out) is off; it is still experimental. The normal gesture or chest reload is unchanged.
- The Upscaler row under BETA does nothing in this zip: NVIDIA's own files are not included, so the game stays on plain OpenGL.
- The first time HD textures appear in a level you may feel a short hitch.
- Windowed only (no Fullscreen toggle).

## New since vr456.9 - try these

### Pickups (New)

- **Auto pickup.** With both hands empty, try walking over a gun on the floor; you should pick it up straight into your right hand. With a gun already in a hand, walk over another gun; it should go into your inventory. Walk over a second copy of a gun you already own; you should get the dual pair in your inventory. A third copy gives ammo only. Turn **AUTO PICKUP** off in GEVR Settings under HANDS AND GUNS and walk over a gun again; it should stay on the floor until you grab or pull it.
- **Force-pull landing.** Point a hand at a gun a few steps away, squeeze the grip and keep holding until it arrives; it should land in your hand and stay there when you let go. Squeeze, then let go while it is still flying; it should land in your inventory instead. With a gun already in one hand, try pulling another with the free hand; it should go to your inventory.
- **Stick click.** With a gun in your hand, try clicking a thumbstick; you should see the gun put away and find it in your inventory.
- **Two-gun swap.** Hold a gun in each hand, bring your hands together and squeeze both grips at nearly the same moment; the two guns should swap hands.

### Hands and arms (New, on by default)

- Look down at your hands. You should see one clean hand and sleeve per side, arms that follow your body, and a closed watch band around the left wrist with the watch case on top.
- Guns are drawn from your jacket (small guns) and over your shoulders (long guns). Try drawing a pistol with the opposite hand from the chest, and a rifle from over the shoulder; you should get the gun.
- To go back to the old hands and hip holsters, set **HANDS AND ARMS** to Off in GEVR Settings (HANDS AND GUNS page) or untick **New hands** in the launcher Options tab, then Apply or Start.

### Scopes (New)

- Pick up the sniper rifle (or use the Moonraker lens) and bring your eye toward the scope. You should see the scope picture grow as your eye gets close (full size beyond about 30 cm, up to two and a half times bigger at about 12 cm), so you no longer have to press the headset against it. The zoom level itself does not change.

### Weather (New: Enhanced and Dynamic)

- Open **GEVR Settings > WEATHER**. **Original** is the game as it was and is the default. **Enhanced** adds snow and rain on the levels that have it; **Dynamic** lets the weather change by itself over time. Set Enhanced, Apply, then load Dam. You should see rain falling around you and out across the yard, not only close to your head (the far layer reaches about 18 metres).
- Other rows on the page: intensity, weather type, ground effects (splashes, prints in snow, wet floors), lightning flashes, whether the weather hinders Tactical guards, and a seed for repeatable weather.
- The weather never changes the game's fog, draw distance or sky colour. If you see everything turn blue near your face, tell us.

### Enemy AI (New, optional)

- Leave **ENEMY AI** on Classic for the original guards. Tactical and Tactical+ make guards use cover, flank, call for help and fall back; they now fire first when they meet you close up and turn and fire if they run away from you. Their radio chirps, clicks and coughs are muted; spotted shouts and man-down yells still play. The AGGRESSION row sets how hard they push (Calm to Ruthless). See Known issues above.

### Train (New)

- Try the Train level: do the brakes objective. You should hear the brake sound and the two key guards should leave their posts instead of standing there for ever. The same fix applies to other levels where a guard waits for "objective N complete".

### GEVR Settings (New layout)

- GEVR Settings now has pages: GRAPHICS, VR, HANDS AND GUNS, WEATHER, ENEMY AI and BETA. Change a row with Left or Right, accept with A, then choose **APPLY** on the first page. The game restarts into your choice.

### Beta rows (off)

- **HD TEXTURE SET** (GEVR Settings > BETA): Off, GE007 HD, GEVR Curated, or Curated plus AI fills. It needs a folder of pictures on your own disk (the zip has none). With the folder in place, try loading a level; you should see the chosen pictures. Without the folder the game keeps HD off and says so in its log. Explosions and smoke should not look purple.
- **UPSCALER** (GEVR Settings > BETA): needs an RTX card and NVIDIA's own runtime files, which are not in this zip. Without them the row does nothing.

## Carried from earlier test builds

**Passed in the headset:**

- VR eyes no longer follow the desktop window. Try starting VR at different window sizes; you should see the same picture in each eye with no double edges.
- VR render scale, 50 to 150 percent (launcher Options tab, or the VR RENDER SCALE row in GEVR Settings). At 150 you should see a sharper picture at a distance; at 50 a faster, softer one. A very large headset at 150 is capped to what the runtime allows.
- Multisample anti-aliasing in VR sizes itself to your graphics memory (steps down 8x, 4x, 2x, off if it does not fit).
- Force-pull: point a hand at a gun, ammo, key or armour and squeeze the grip; it should fly to your hand. Pointing down at small items searches a little wider.
- Door and wall buttons press when you touch them; hinged doors push open with your palm.
- Held items follow your hand. Try the armour vest on the crate in Facility: grab it, lift it, set it back; it should land on top, not through.
- Menus and cinema fit one eye's picture, and moving between menus and a level no longer flashes white.
- Pull and disarm: try force-pulling a gun out of a guard's hand; you should hear a magnet sound and see the watch glow as it flies to you.

**Seen working, not re-checked on this build:** the left hand holds and uses everything the right can (not the taser), All Weapons also gives the gadgets, the throw marker shows on props and characters, and text sits symmetrically around the forward line.

## Not in this build

Live wrist watch panel, throwing any prop, multiplayer bots, DLSS frame generation and neural upscaling.

## Install and first boot

- Try `Start-GEVR.bat` after a fresh unzip; you should reach VR play without a fault. The first launch rebuilds the image cache once from your own ROM (the ship stamp is vr457).

## How to report

Open a GitHub issue: https://github.com/no6969el/GEVR/issues/new/choose and say what you changed, what you saw, and what you expected.
