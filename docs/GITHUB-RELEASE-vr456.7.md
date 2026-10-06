GEVR Beta vr456.7 is GitHub Latest. Wear it. Stand inside GoldenEye.

Hotfix: kills and aimed shots no longer drop you out of the game. Aim, fire, and finish the guard. Stay in the mission.

Bring your own USA GoldenEye ROM. This zip does not include a ROM or an HD texture pack.

vr456.6 stays up as the previous tag. This is a new Latest so Update can see it.

## How to play
- Download GEVR-Beta-vr456.7-win64.zip, unzip it, run Start-GEVR.bat. Do not double-click goldeneye.exe.
- Point GevrRomStarter at your USA GoldenEye .z64.
- Ship stamp is vr456.7. First launch rebuilds the image cache once from your own ROM. Saves stay.
- Put the headset on. Recenter with both stick clicks. Look right on the intro hub / Mission Select for GEVR Settings.
- Already on an older zip? Hit Update in GevrRomStarter, or grab this download.
- Report problems at https://github.com/no6969el/GEVR/issues/new/choose (do not upload your ROM).
- Full hands: docs/CONTROLS.md in this repo and inside the zip.

## How to play this cut
- Stick click opens the weapon wheel. Default is a circle. NO WEAPON sits at 12 o'clock. The centre follows your hover. Boxes are 2x dark grey. GEVR Settings STICK WHEEL can switch to Weapon Vert (a column). Change the row, unpause, then the next stick-click uses it. No reboot.
- Watch picker on the left cuff: three squares with pictures and labels (Laser / Magnet / Repel). Yellow highlight is the middle square. Magnet is unlimited in VR. Laser and Repel stay on the normal watch item flow.
- Holster swap: hip grip on the same gun is a real swap. Weapon switch prefers a free inventory copy over the hip gun.
- Left X is the next weapon on the left hand. Right A is the next weapon on the right hand.
- VR has no walk bob, no landing dip, no gun-hand sway.
- Tank shells auto-reload the next round after you fire (retail empty-mag autoload). Other guns reload with the magazine or chest-cross gesture. B is USE, not VR gun reload.
- Moonraker: small circular scope lens only. Look through the ring. Shoot through the ring. Dual Moonrakers give two lenses, one per hand. No big front grill screen. Sniper plate unchanged.
- Rocket launcher rockets stay locked to the launcher, not your head. Flat mouse-aim crosshair stays centred.
- Snap turn is real degrees (15 / 22.5 / 30 / 45 / 60 / 90).
- Red and green aimers sit on the shot's first hit.
- Left-hand throwables draw the right way around.
- HD memos keep decoded HD pictures in memory (GETV_HD_MEMO_MB=0 turns that off).
- XR catch-up: missed headset frames no longer slow the sim. Quitting actually quits.

Not in this zip: thermal vision, corpse freeze, Gun Drop / Arm Bounds default-on.

## Linux testers
A flat-only Linux alpha is up as its own prerelease, not Latest.

Download: https://github.com/no6969el/GEVR/releases/tag/linux-alpha1
Asset: GEVR-Linux-alpha1-flat-x86_64.tar.gz

This is monitor / Steam Deck. No VR, no headset, no OpenXR. Bring your own USA GoldenEye ROM. The archive has no ROM and no HD pack.

Unpack, then:
chmod +x goldeneye gevr_prepare run-gevr.sh
./run-gevr.sh /path/to/your-usa.z64

Needs SDL2, OpenGL 2.1, and glibc 2.34+ (Ubuntu 22.04, current SteamOS, and newer). Ubuntu 20.04 will not run it.

Known alpha limit: title menu backdrop is blank.

Windows Latest stays this vr456.7 zip. Update will not offer the Linux build.
