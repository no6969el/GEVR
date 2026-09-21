<p align="center">
  <img src="GEVR-box-cover.png" alt="GoldenEye 007 VR - GEVR box art" width="480" />
</p>

# GEVR

**GoldenEye. Native. In VR. Bring your own ROM.**

> **vr443.1 (2026-09-20):** Point fix. **vr443** shipped the comfort cut but the motion / playspace KEEP was **not on by default in the binary** (only chair batlines, which do not stick). Physical step/strafe could slide the world. We pulled that zip. **Grab [vr443.1](https://github.com/no6969el/GEVR/releases/tag/vr443.1)** or hit **Update** in GevrRomStarter.

---
The N64 classic you can finally *stand inside* - not an emulator overlay, not a flat game with a headset stuck on. GEVR is a from-source PC port of *GoldenEye 007* built for real OpenXR VR. You supply a **USA GoldenEye ROM you legally own**; the starter prepares a local cache and **`Start-GEVR.bat`** launches through **GevrRomStarter** (not bare `goldeneye.exe`).

**Latest playable cut:** [**vr443.1**](https://github.com/no6969el/GEVR/releases/latest) - zip **`GEVR-Beta-vr443.1-win64.zip`**. Point fix on vr443 (motion KEEP baked into the exe).

**vr443** / **vr442** / **vr441** / **vr440** tag pages stay for history. Their **zips are gone** (vr443 was HOLD). Grab [**vr443.1**](https://github.com/no6969el/GEVR/releases/tag/vr443.1).

If this brings you back, **Star** the repo and [**follow @no6969el**](https://github.com/no6969el) so you can catch the next drops. **Watch -> Releases** if you want a ping when we ship. Between cuts, we keep a [living status on Reddit](https://www.reddit.com/r/QuietWindows/comments/1whmk8l/gevr_living_status_goldeneye_in_native_openxr_vr/) - honest fan wear notes, not a second readme. Want to fund the next cuts? [Patreon](https://www.patreon.com/cw/GEVR) - the zip stays free.

[Latest zip](https://github.com/no6969el/GEVR/releases/latest) · [Report a bug](https://github.com/no6969el/GEVR/issues/new/choose) · [Roadmap](docs/ROADMAP.md) · [Controls](docs/CONTROLS.md) · [Credits](CREDITS.md) · [Features](FEATURES.md) · [Support](https://www.patreon.com/cw/GEVR)

---

## Streamer playtests

**Note:** This clip is from an **older public cut (~vr441)**. The game has moved on — grab **[Latest (vr443.1)](https://github.com/no6969el/GEVR/releases/latest)** for what you can play now. Picture, comfort, and bugs may not match the video.

[![GoldenEye VR Is Finally Here… And You Can Play It Now](https://img.youtube.com/vi/z4B0Ceqrf6I/maxresdefault.jpg)](https://www.youtube.com/watch?v=z4B0Ceqrf6I)

<p align="center">
  <iframe width="560" height="315" src="https://www.youtube.com/embed/z4B0Ceqrf6I" title="GoldenEye VR Is Finally Here… And You Can Play It Now (~vr441 footage)" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>
</p>

[Watch on YouTube](https://www.youtube.com/watch?v=z4B0Ceqrf6I) — streamer playtest / look-at-this energy, not a current build walkthrough.

---

## Play (vr443.1 - the one to grab)

1. Download **[GEVR-Beta-vr443.1-win64.zip](https://github.com/no6969el/GEVR/releases/latest)** from [Latest](https://github.com/no6969el/GEVR/releases/latest) / [tag vr443.1](https://github.com/no6969el/GEVR/releases/tag/vr443.1) (exe, `glew32.dll`, other runtime DLLs, ROM starter, launcher, notes). **No ROM inside the zip.**
2. Unzip anywhere.
3. Run **`Start-GEVR.bat`** - it sets VR boot knobs and starts **GevrRomStarter.exe**.
4. Point at your **USA GoldenEye `.z64`** when asked. Images extract to `%LOCALAPPDATA%\GEVR\\cache\\<ROM-hash>\\`. Each Beta tag bumps a **ship stamp** so the first launch after an update rebuilds that cache once from your ROM.
5. Put the headset on. Recenter with **both thumbstick clicks**.
6. On the intro hub, **look right** for **VR SETTINGS** and tune turn comfort. Enjoy.

**Please use the bat** - it locks in the good VR settings and runs the ROM starter we ship for this cut (not bare `goldeneye.exe`).

Default is **VR**. Flat / monitor works too if you just want a look (`Play-on-monitor.bat`).

No ROM in the download. You bring yours.

### New install vs returning after an update

- **New install:** first launch waits once while images prepare into `%LOCALAPPDATA%\GEVR\\cache`, then you play. Saves start empty.
- **Returning after a Beta update:** keep the same USA `.z64`. The ship stamp forces **one** automatic re-prepare. **Saves and VR Settings prefs are kept** under `%LOCALAPPDATA%\GEVR`. Or open the starter and use **Update** when it offers a newer tag. You do not delete the cache folder for a normal update.
- **Picture still looks wrong:** the tag notes say delete `%LOCALAPPDATA%\GEVR` and run the bat again (that also drops saves). Prefer **`Clear-GEVR-cache.bat`** first (type **YES**) if you want to keep saves. See `RELEASE-NOTES.txt` in the zip.

---

## What is new in vr443.1

From the [vr443.1 RELEASE-NOTES](https://github.com/no6969el/GEVR/releases/tag/vr443.1). Internal cook **453**.

### Why the point release

**vr443** said physical walk should move you (and guns should stick). Those KEEP features were **not on by default in the shipped binary** - only chair batlines, which do not stick for a normal download. Physical step/strafe could **slide the world left/right**. We pulled that zip (HOLD). **vr443.1** bakes those KEEP features **C-default ON** in the exe. New tag so **Update** notices.

### 1) In-app Update (start here)

Open **GevrRomStarter** and it **checks GitHub Latest** for you. If a newer cut is waiting, it says so.

Click **Update** once: downloads the win64 zip, unpacks into this folder, leaves saves / prefs / cache / your .z64 alone, then **launches Start-GEVR.bat** and closes. **One click to play.**

### 2) VR comfort / motion (fixed)

- Physical walk/strafe moves **you**, not the world (baked in)
- Guns stay with your hands when you lean/strafe (baked in)
- **VR Settings** glass on the intro / cinema hub (**look right**), world-locked, facing you
- **Right stick only**: up/down = row, left/right = change live
  - **TURN SPEED** / **TURN STYLE** (Smooth or Snap) / **SNAP SIZE** (25-150%, grayed on Smooth)
- Height row removed; Snap Size took that slot
- Prefs under %LOCALAPPDATA%\GEVR with your saves (survive zip Update and Clear-GEVR-cache.bat)

### 3) Dam sky (SKYPIN)

Look-up on Dam stays pinned. **On by default**.

### 4) Also in this cut

- Open play space / dual-wield fire / picture KEEP still on
- Recenter = both thumbstick clicks
- Public zip still has **no** cheat unlock dump
- One automatic cache rebuild after a new tag from your same ROM

### Worked this week, not public-on yet

- **Dam blue flicker / convert-modem flicker** ([#70](https://github.com/no6969el/GEVR/issues/70)) - **known, being worked on**
- #74 arms body - still cooking as a product story (playspace translate KEEP is on)
- Pause-menu VR Settings / laser select - parked

Full notes: RELEASE-NOTES.txt in the zip / [tag](https://github.com/no6969el/GEVR/releases/tag/vr443.1).


## What's cooking (later update)

Soft list only. Matches the tag's **Still rough / coming soon**. Do not treat these as shipped.

- Two-hand snap is still cooking (coming later)
- Higher Hertz requests are not signed off yet - stick to 72 / 80 / 90 for now ([issue #49](https://github.com/no6969el/GEVR/issues/49))
- Ghost hand is parked for this cut
- Empty left hand cube is temporary
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
- **Boot that actually hands over** - the bat sets FPS + stereo / view-restore so eyes fuse.
- **Movement feel** locked to the 90 Hz loco reference we preferred in the chair.

**Older tags (history only):** **vr434** was pulled (ROM images baked into `goldeneye.exe`). **vr442** / **vr441** / **vr440** tag pages stay; their **zips were stripped**. Do not hunt an old zip. Play [vr443.1](https://github.com/no6969el/GEVR/releases/latest).

---

## What we tested

These paths are what this Beta was built and stared on:

| Path | Notes |
|------|--------|
| **Pimax Crystal Super + SteamVR OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR) (sboys3) | Primary wear path - we do not maintain that driver; we *do* support this experience |
| **Native PimaxXR** | Verified attach / play |
| **Meta Quest 3 + Virtual Desktop OpenXR (VDXR)** | Verified attach / play |
| **RTX 5060 laptop + Quest 3 + Virtual Desktop VDXR** | BarZ wear **vr441**, 2026-09-17; ran surprisingly well (one data point, not a minimum spec) |

**Refresh rates:** 72 Hz and 80 Hz should work. **90 Hz** is recommended (default). Over 90 is still beta-test territory - try it, and [file an Issue](https://github.com/no6969el/GEVR/issues/new/choose) if something feels off. Higher Hertz requests are **not** signed off. Stick to 72 / 80 / 90 for now. We do **not** call 120 / 144 signed off ([issue #49](https://github.com/no6969el/GEVR/issues/49)).

When you report a bug or crash, please include: **headset**, **OpenXR runtime**, **SteamVR on/off**, **HMD vs monitor**, whether you used **`Start-GEVR.bat`**, your **`gevr-*-boot.cmd`** filename from the zip folder, any log next to the zip or in the console, and any **`gevr-fault-*.txt`** beside the exe. Do **not** upload your ROM. [Open an Issue](https://github.com/no6969el/GEVR/issues/new/choose).

---

## Known quirks (honest Beta)

We would rather tell you than surprise you. These are **vr443.1 today**.

- **Dam blue flicker** (end section) and **convert-modem flicker** - **known and being worked on** ([issue #70](https://github.com/no6969el/GEVR/issues/70)).
- **Melee / fist** is in (swing-based), but **not finely tuned yet** - be careful standing next to characters you are not supposed to harm ([issue #75](https://github.com/no6969el/GEVR/issues/75)).
- **Big explosions** (large objects, plane shells) can still hard-crash. If they do, grab `gevr-fault-*.txt` beside the exe before you relaunch.
- Alarm can keep ringing after a death or stage return.
- **Dam water** can look flat or murky.
- **Glass bullet holes** can still show in one eye.
- **HUD text** can sit too close or hard to read in depth.
- **Headset refresh:** public boot stays 90-pinned. Some Virtual Desktop / runtime setups only enter VR at 90 Hz - [issue #49](https://github.com/no6969el/GEVR/issues/49).
- Empty left hand is a **cube** for now (temporary stand-in). Ghost fingers are parked.
- **Gun vanish below chest** (GUNZ / HANDSOLID) is left off until it is fixed.
- Expect occasional **crashes** while we keep optimizing.
- We are **not** promising full-body Bond or fancy glove meshes yet.

Still worth playing - absolutely. Facility, Dam, tanks that actually let you in, that first-person Bond feeling.

On a **flat / monitor** setup, classic **local / split-screen multiplayer** is still there - couch chaos, same as you remember. Next social step is a **LAN / local-network multiplayer add-on** (not a mod). True online is further after that.

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

**Now - enjoy the Beta (vr443.1)**
- Solo VR campaign feel
- Tank climb + turret pitch, dual-wield fire, rockets that point where they fly
- Comfort, aim, and picture quality
- "It boots, it shoots, it sometimes crashes" honesty
- Local / split-screen multiplayer on a monitor

**Cooking**
- Two-hand snap (coming later)
- Higher Hertz request ([issue #49](https://github.com/no6969el/GEVR/issues/49))
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
