<p align="center">
  <img src="GEVR-box-cover.png" alt="GoldenEye 007 VR - GEVR box art" width="480" />
</p>

# GEVR

**GoldenEye. Native. In VR. Bring your own ROM.**

> **vr444 (2026-09-21):** Major glitch cut - stuck covert-modem scrap quieted, throwables in hand, weapon cycle, follow headset Hz. Built on **vr443.1** motion KEEP. **Grab [vr444](https://github.com/no6969el/GEVR/releases/tag/vr444)** or hit **Update** in GevrRomStarter.

---
The N64 classic you can finally *stand inside* - not an emulator overlay, not a flat game with a headset stuck on. GEVR is a from-source PC port of *GoldenEye 007* built for real OpenXR VR. You supply a **USA GoldenEye ROM you legally own**; the starter prepares a local cache and **`Start-GEVR.bat`** launches through **GevrRomStarter** (not bare `goldeneye.exe`).

**Latest playable cut:** [**vr444**](https://github.com/no6969el/GEVR/releases/latest) - zip **`GEVR-Beta-vr444-win64.zip`**. Major glitch cut (modem scrap) plus hands / throwables / A-X cycle / follow headset Hz.

**vr443.1** / **vr443** / **vr442** / **vr441** / **vr440** tag pages stay for history. Older **zips are gone** where we pulled them (vr443 was HOLD). Grab [**vr444**](https://github.com/no6969el/GEVR/releases/tag/vr444).

If this brings you back, **Star** the repo and [**follow @no6969el**](https://github.com/no6969el) so you can catch the next drops. **Watch -> Releases** if you want a ping when we ship. Between cuts, we keep a [living status on Reddit](https://www.reddit.com/r/QuietWindows/comments/1whmk8l/gevr_living_status_goldeneye_in_native_openxr_vr/) - honest fan wear notes, not a second readme. For port help and GoldenEye fan chat, hop in [**Discord**](https://discord.gg/flat2vr) (BYO ROM - do not upload your ROM; setup details and logs only). Want to fund the next cuts? [Patreon](https://www.patreon.com/cw/GEVR) - the zip stays free.

[Latest zip](https://github.com/no6969el/GEVR/releases/latest) · [Report a bug](https://github.com/no6969el/GEVR/issues/new/choose) · [Discord](https://discord.gg/flat2vr) · [Roadmap](docs/ROADMAP.md) · [Controls](docs/CONTROLS.md) · [Credits](CREDITS.md) · [Features](FEATURES.md) · [Support](https://www.patreon.com/cw/GEVR)

---

## Streamer playtests

**Note:** This clip is from an **older public cut (~vr441)**. The game has moved on - grab **[Latest (vr444)](https://github.com/no6969el/GEVR/releases/latest)** for what you can play now. Picture, comfort, and bugs may not match the video.

[![GoldenEye VR Is Finally Here… And You Can Play It Now](https://img.youtube.com/vi/z4B0Ceqrf6I/maxresdefault.jpg)](https://www.youtube.com/watch?v=z4B0Ceqrf6I)

[Watch on YouTube](https://www.youtube.com/watch?v=z4B0Ceqrf6I) - streamer playtest.

---

## Play (vr444 - the one to grab)

1. Download **[GEVR-Beta-vr444-win64.zip](https://github.com/no6969el/GEVR/releases/latest)** from [Latest](https://github.com/no6969el/GEVR/releases/latest) / [tag vr444](https://github.com/no6969el/GEVR/releases/tag/vr444) (exe, `glew32.dll`, other runtime DLLs, ROM starter, launcher, notes). **No ROM inside the zip.**
2. Unzip anywhere.
3. Run **`Start-GEVR.bat`** - it sets VR boot knobs and starts **GevrRomStarter.exe**.
4. Point at your **USA GoldenEye `.z64`** when asked. Images extract to `%LOCALAPPDATA%\GEVR\\cache\\<ROM-hash>\\`. Each Beta tag bumps a **ship stamp** so the first launch after an update rebuilds that cache once from your ROM.
5. Put the headset on. Recenter with **both thumbstick clicks**.
6. On the intro hub, **look right** for **VR SETTINGS** and tune turn comfort. Enjoy.

**Please use the bat** - it locks in the good VR settings and runs the ROM starter we ship for this cut (not bare `goldeneye.exe`).

Default is **VR**. Flat / monitor is absolutely playable too (`Play-on-monitor.bat`) - same game, and it takes the fixes as we improve the VR cut. Flat-screen settings and borderless fullscreen are on the want list ([COMING-SOON](docs/COMING-SOON.md)).

No ROM in the download. You bring yours.

### New install vs returning after an update

- **New install:** first launch waits once while images prepare into `%LOCALAPPDATA%\GEVR\\cache`, then you play. Saves start empty.
- **Returning after a Beta update:** keep the same USA `.z64`. The ship stamp forces **one** automatic re-prepare. **Saves and VR Settings prefs are kept** under `%LOCALAPPDATA%\GEVR`. Or open the starter and use **Update** when it offers a newer tag. You do not delete the cache folder for a normal update.
- **Picture still looks wrong:** the tag notes say delete `%LOCALAPPDATA%\GEVR` and run the bat again (that also drops saves). Prefer **`Clear-GEVR-cache.bat`** first (type **YES**) if you want to keep saves. See `RELEASE-NOTES.txt` in the zip.

---

## What is new in vr444

From the [vr444 RELEASE-NOTES](https://github.com/no6969el/GEVR/releases/tag/vr444). Major glitch cut on top of **vr443.1** (motion KEEP already fixed).

### 1) Quiet stuck modem scrap (the big one)

Stuck covert-modem scrap / flicker on the floor is hidden. The hand modem and screens stay on. Dam blue flicker is probably the same convert-modem story (we mixed the labels under [#70](https://github.com/no6969el/GEVR/issues/70)); dish-on-glass depth is still open.

### 2) Throwables in your hand

Grenades, mines, plastique, and the covert modem show in your hand and leave from the grip. Grenades and mines were resized to better reflect their actual dimensions in your hand.

### 3) Smarter hand cubes

The hand cue cube hides while that hand holds a weapon. Empty hand / fists bring the cube back. Cube is smaller than before.

### 4) Weapon cycle on the face buttons

Tap **A** = next weapon. Tap left-controller **X** = previous weapon. (Weapon wheel HUD still not shipped.)

### 5) Follow your headset refresh

The game follows your headset refresh rate (72 / 80 / 90 / 120 as your runtime reports) instead of pinning 90. Still Beta - if something feels off at high Hz, [report it](https://github.com/no6969el/GEVR/issues/new/choose).

### Still in from vr443.1

- Physical walk/strafe moves **you**, not the world
- Guns stay with your hands when you lean/strafe
- **VR Settings** glass on the intro / cinema hub (**look right**): TURN SPEED / STYLE / SNAP SIZE
- Dam sky look-up pinned (on by default)
- In-app **Update** in GevrRomStarter
- Open play space / dual-wield / picture KEEP / BYO-ROM / recenter both sticks

### Worked this week, not public-on yet

- **Dam blue / convert-modem** ([#70](https://github.com/no6969el/GEVR/issues/70)) - Dam blue is probably the convert modem, not a separate bug; floor scrap quieter above; dish-on-glass depth still open
- #74 arms body - still cooking as a product story
- Pause-menu VR Settings / laser select - parked
- Weapon wheel HUD - cooking

Full notes: RELEASE-NOTES.txt in the zip / [tag](https://github.com/no6969el/GEVR/releases/tag/vr444).


## What's cooking (later update)

Soft list only. Matches the tag's **Still rough / coming soon**. Do not treat these as shipped.

- Two-hand snap is still cooking (coming later)
- Weapon wheel HUD is still cooking
- High Hz (over 90) is Beta-test territory - try it and report if something feels off ([issue #49](https://github.com/no6969el/GEVR/issues/49))
- Ghost hand is parked for this cut
- Empty-hand cube is temporary (smaller now; hides when armed)
- Gun vanish below chest (GUNZ / HANDSOLID) left off until fixed
- Big explosion / plane shell can still hard-crash (the fault file helps)

Stay tuned. **Star** this repo and [**follow @no6969el**](https://github.com/no6969el). **Watch -> Releases** for the next zip.

---

## What vr441 / vr438 already taught us (still true)

- **vr441** turned on the full chair boot after **vr440** shipped picture KEEP only. Those keepers are still on.
- **BYO-ROM enforced** - `Start-GEVR.bat` -> **GevrRomStarter**; you must supply a USA GoldenEye `.z64` you own.
- **File-backed images** - in-game textures and UI art come from your ROM on disk; the zip does not ship Nintendo cart data.
- **Full runtime in the zip** - includes `glew32.dll` and the other Windows DLLs the build needs.
- **Sharper VR** - supersample 3 with the SrcFbo path we chaired and kept.
- **Boot that actually hands over** - the bat sets stereo / view-restore so eyes fuse; refresh follows the headset.
- **Movement feel** locked to the loco reference we preferred in the chair.

**Older tags (history only):** **vr434** was pulled (ROM images baked into `goldeneye.exe`). **vr443** / **vr442** / **vr441** / **vr440** tag pages stay; their **zips were stripped** where we pulled them. Do not hunt an old zip. Play [vr444](https://github.com/no6969el/GEVR/releases/latest).

---

## What we tested

These paths are what this Beta was built and stared on:

| Path | Notes |
|------|--------|
| **Pimax Crystal Super + SteamVR OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR) (sboys3) | Primary wear path - we do not maintain that driver; we *do* support this experience |
| **Native PimaxXR** | Verified attach / play |
| **Meta Quest 3 + Virtual Desktop OpenXR (VDXR)** | Verified attach / play |
| **RTX 5060 laptop + Quest 3 + Virtual Desktop VDXR** | BarZ wear **vr441**, 2026-09-17; ran surprisingly well (one data point, not a minimum spec) |

**Refresh rates:** The game follows your headset refresh (72 / 80 / 90 / 120 as reported). Still Beta - if something feels off at high Hz, [file an Issue](https://github.com/no6969el/GEVR/issues/new/choose). We do **not** call every high-Hz path signed off yet ([issue #49](https://github.com/no6969el/GEVR/issues/49)).

When you report a bug or crash, please include: **headset**, **OpenXR runtime**, **SteamVR on/off**, **HMD vs monitor**, whether you used **`Start-GEVR.bat`**, your **`gevr-*-boot.cmd`** filename from the zip folder, any log next to the zip or in the console, and any **`gevr-fault-*.txt`** beside the exe. Do **not** upload your ROM. [Open an Issue](https://github.com/no6969el/GEVR/issues/new/choose).

**Discord (help + fan chat):** [discord.gg/flat2vr](https://discord.gg/flat2vr) - port help and GoldenEye fan chat with other players. BYO ROM / do not upload your ROM (setup details and logs only).

---

## Known quirks (honest Beta)

We would rather tell you than surprise you. These are **vr444 today**.

- **Dam blue flicker** (end section) - probably the **convert modem**, not a separate mystery ([issue #70](https://github.com/no6969el/GEVR/issues/70)). Stuck covert-modem scrap on the floor is quieter this cut; dish-on-glass depth is still open.
- **Melee / fist** is in (swing-based), but **not finely tuned yet** - be careful standing next to characters you are not supposed to harm ([issue #75](https://github.com/no6969el/GEVR/issues/75)).
- **Big explosions** (large objects, plane shells) can still hard-crash. If they do, grab `gevr-fault-*.txt` beside the exe before you relaunch.
- Alarm can keep ringing after a death or stage return.
- **Dam water** can look flat or murky.
- **Glass bullet holes** can still show in one eye.
- **HUD text** can sit too close or hard to read in depth.
- **Headset refresh:** follows your HMD rate now. High Hz is still Beta-test territory ([issue #49](https://github.com/no6969el/GEVR/issues/49)).
- Empty hand is a **cube** for now (smaller; hides when that hand holds a weapon). Ghost fingers are parked.
- **Gun vanish below chest** (GUNZ / HANDSOLID) is left off until it is fixed.
- Expect occasional **crashes** while we keep optimizing.
- We are **not** promising full-body Bond or fancy glove meshes yet.

Still worth playing - absolutely. Facility, Dam, tanks that actually let you in, that first-person Bond feeling.

On a **flat / monitor** setup, the game is fully playable (`Play-on-monitor.bat`) and picks up the same fixes as we improve VR. Classic **local / split-screen multiplayer** is still there - couch chaos, same as you remember. Flat-screen settings and borderless fullscreen are planned ([COMING-SOON](docs/COMING-SOON.md)). Next social step is a **LAN / local-network multiplayer add-on** (not a mod). True online is further after that.

More tester notes: [BETA.md](docs/BETA.md) · [COMING-SOON.md](docs/COMING-SOON.md) · [CONTROLS.md](docs/CONTROLS.md).

---

## Why this exists

GoldenEye is one of the most-wanted "I wish I could stand inside it" games on Earth. GEVR's north star:

- **Native / from-source** - full ownership of the game loop for proper VR
- **OpenXR** - Crystal, Quest via PC, SteamVR-class HMDs
- **Your ROM** - legal ownership stays with you
- **Feel first** - 6DOF, aiming, presence; then polish; then extras

More pitch and cover energy: [FEATURES.md](FEATURES.md).

---

## Roadmap (honest, not a calendar promise)

**Now - enjoy the Beta (vr444)**
- Solo VR campaign feel
- Throwables in hand, A / X weapon cycle, smarter hand cubes
- Tank climb + turret pitch, dual-wield fire, rockets that point where they fly
- Comfort, aim, and picture quality
- "It boots, it shoots, it sometimes crashes" honesty
- Local / split-screen multiplayer on a monitor

**Cooking**
- Flat-screen settings and borderless fullscreen (monitor path)
- Two-hand snap (coming later)
- Weapon wheel HUD
- High Hz polish ([issue #49](https://github.com/no6969el/GEVR/issues/49))
- Ghost empty hand (parked); nicer mesh after that
- Gun vanish below chest (GUNZ / HANDSOLID)
- Softer landings when the big explosions go loud

**Later**
- **LAN / local-network multiplayer add-on** (not a mod; not this polish pack)
- True online after that
- Full-body Bond later
- Dam water / glass / HUD-depth polish

Fuller list: [`docs/ROADMAP.md`](docs/ROADMAP.md). Star + [follow @no6969el](https://github.com/no6969el) + **Watch -> Releases** if you want the next zip without refreshing every day.

---

## For press / curious readers

**One-liner:** Native from-source GoldenEye VR for PC OpenXR - bring your own ROM.

**Longer:** GEVR rebuilds GoldenEye on PC so VR can be done properly (stereo, 6DOF, controller aim), instead of stretching an emulator. Beta means playable and imperfect on purpose while we clear crashes and comfort. Multiplayer and bigger social features sit on the roadmap after the solo VR base is something we are proud to hand strangers.

Credits: [CREDITS.md](CREDITS.md). Boundaries: [PRIOR-ART.md](PRIOR-ART.md), [LICENSE](LICENSE). We do not claim Nintendo's game data, Rare's assets, or third-party engines we did not write.

Attribution: **BarZ / [@no6969el](https://github.com/no6969el)**. Star and follow if you want the next cut.

---

## Docs (secondary)

Deep technical trail: [`docs/00-START-HERE.md`](docs/00-START-HERE.md)  
Controls: [`docs/CONTROLS.md`](docs/CONTROLS.md)  
Beta snapshot: [`docs/BETA.md`](docs/BETA.md) · [`docs/FEATURES-CURRENT.md`](docs/FEATURES-CURRENT.md)  
Coming soon / release policy: [`docs/COMING-SOON.md`](docs/COMING-SOON.md) · [`docs/RELEASE-POLICY.md`](docs/RELEASE-POLICY.md)  
Pack / smoke: [`packaging/README.md`](packaging/README.md) · ship boot allowlist: [`docs/ship-feature-checklist.md`](docs/ship-feature-checklist.md)

---

Jump in and enjoy finally being Bond in GoldenEye VR.
