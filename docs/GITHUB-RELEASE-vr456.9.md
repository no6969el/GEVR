GEVR Beta **vr456.9** - Windows Latest.

Bring your own USA GoldenEye ROM. No ROM or HD pack is inside the zip.

Play: `Start-GEVR.bat` only.

Report issues: https://github.com/no6969el/GEVR/issues/new/choose

Linux flat alpha (separate): https://github.com/no6969el/GEVR/releases/tag/linux-alpha1

## Known issues / in progress

- The first time HD textures appear in a level, you may feel a short hitch. An experimental prewarm path exists and stays off by default until it is proven.
- Multisample anti-aliasing in VR is new; try Default first if picture quality looks odd.
- Some Advanced graphics rows in the launcher are placeholders and do not change the game yet.
- HD texture packs are still beta: Apply HD, then restart play if a pack looks wrong.
- Windowed only (no Fullscreen toggle).

## Coming later (not broken)

Live wrist watch panel, physical magazine reload, and force-pull are planned follow-ups - not regressions.

## Highlights

- Dam speedboat: board, ride to the island, get off; boat about 1.75x retail size.
- Install isolation for cache / HD packs / prefs when you keep more than one install.
- Launcher Advanced MSAA and anisotropic filtering for this install.
- Cook-in-hand grenades; calmer backup-guard pacing on Facility and Dam.
- Throw-land marker and wheel, Archives and chase-guard fixes, scopes under MSAA, spare ammo reserves, launcher HD dropdown, Monitor Off blanking, corpse freeze, gun swap bounds.

## Tester's notes

### Coming later (not broken)

Live wrist watch panel, physical magazine reload, and force-pull are not ready yet. They are planned follow-ups, not regressions from older tags.

### Known issues / in progress

- The first time HD textures appear in a level, you may feel a short hitch. An experimental prewarm path exists and stays off by default until it is proven.
- Multisample anti-aliasing in VR is new; try Default first if picture quality looks odd.
- Some Advanced graphics rows in the launcher are placeholders and do not change the game yet.
- HD texture packs are still beta: Apply HD, then restart play if a pack looks wrong.
- Windowed only (no Fullscreen toggle).

### New this cut

- Dam speedboat: board at the north jetty, ride across to the island, get off, and check the boat looks about one-and-three-quarters retail size.
- Install isolation: cache, HD packs, and launcher prefs stay keyed to this install so side-by-side folders do not clobber each other.
- Launcher Advanced can set MSAA and anisotropic filtering for this install; Apply, then Start.
- Hold the trigger on a grenade: grip digits count down the fuse. Let go without throwing (or open the watch) and a live grenade drops at your feet.
- On Facility or Dam, noisy play that draws a backup should keep at most one live backup at a time (no endless stream).

### Launcher & settings

- Open RomStarter and browse for your ROM; detect and browse should work and the path should stick.
- Use RomStarter Update after installing a newer tag; expect a one-time cache wipe while ROM path, prefs, and HD settings are kept.
- Try the HD texture pack Simple or Advanced dropdown and Apply HD; the pack should merge into this install's hdtextures folder.
- Try launcher Options; theme and settings should save on relaunch.
- Try in-game GEVR Options; pages should load and monitor or output choice should persist after restart.
- Confirm there is no Fullscreen toggle (windowed only).
- Try Advanced MSAA or anisotropic filtering, Apply, then Start; the choice should apply for this install.

### Install & first boot

- The ship stamp is vr456.9. The first launch rebuilds the image cache once from your own ROM.
- Try Start-GEVR.bat after a fresh unzip; you should reach VR menu or play without a fault.
- Try first play after a cache wipe; let the one-time cache rebuild finish.
- Try starting after cache clear; prepare should finish before the game loads.
- Try Monitor Off with the headset on; the flat display should blank with no frozen logo.
- Try default HD play; avoid a hard render stall the first time HD textures appear (a short hitch is still possible - see Known issues).

### Dam boat

- Start Dam, go to the north jetty, and board the speedboat (use B or put a VR hand on the hull).
- Ride across the reservoir to the island and get off near the landing.
- Confirm the boat looks about 1.75x retail size (larger than stock, not double).

### Throwing & melee

- Try throwing at crates, screens, trucks, or guards; you should see one orange landing marker and no gun aimer on the throwable hand.
- Try the stick weapon wheel; guns, throwables, and other bands should stay separated; the watch laser should stay off the wheel.
- Try aiming a throw at a person, crate, or prop; you should see an orange marker on that target.
- Try moving while the throw marker is latched; you should see one fused marker in both eyes, not a double square.
- Try fist, knife, or unarmed; you should see no red or green gun aimer; guns should still show the aimer.
- Try the Dam wall modem vs a loose modem; you should not re-grip the installed wall unit; a loose modem should still be grabbable.

### Levels

- Try the Archives Natalia room; Natalia should react without a hard freeze.
- Try chase guard areas such as Caverns; guards should attack and move without getting permanently stuck.
- Try missing a place objective then going out of bounds; you should get another chance with a HUD line, not a permanent fail.
- Try Silo plastique placement when the mission allows regrab; you should be able to pick it up again.
- Try sim speed at your headset refresh rate; wall clock and in-game pacing should feel about one-to-one.
- Try Perf help for frame rate; help text should mention matching headset Hz.
- Try a heavy level compared with the previous Latest on the same ROM and HD settings; pacing should not feel worse.
- Try killing a guard; the corpse should freeze after the death animation.
- Try gun swap near map bounds in campaign; swap should stay guarded and clamped.
- Try legacy watch gadgets from the picker; gadgets should work without a live wrist panel.

### Scopes & ammo

- Try the sniper scope with MSAA Default; the picture should stay usable.
- Try the sniper scope with MSAA 8x; the picture should still be usable.
- Try the Moonraker lens on Default and 8x; the view should stay usable with the front grill off.
- Try All Guns ON; reserves should fill, empty mags should top up when idle, and chest or mag reload should work.
- Try throwables, watch gadgets, and the tank; behavior should match recent builds.
- Try gun reload by gesture or chest reload; reload should complete without a physical magazine prop ejecting.

### Text/HUD

- Try a long HUD message; the right eye should not clip text; the left eye should look fine.

### How to report

Open a GitHub issue: https://github.com/no6969el/GEVR/issues/new/choose
