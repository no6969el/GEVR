<p align="center">
  <img src="GEVR-box-cover.png" alt="GoldenEye 007 VR - GEVR box art" width="480" />
</p>

# GEVR

**GoldenEye. Native. In VR. Bring your own ROM.**

The N64 classic you can finally *stand inside* - not an emulator overlay, not a flat game with a headset stuck on. GEVR is a from-source PC port of *GoldenEye 007* built for real OpenXR VR. You bring a **USA GoldenEye ROM you legally own**, run **`Start-GEVR.bat`**, wait once while it prepares, and go.

**Latest playable cut:** [**GEVR Beta vr438**](https://github.com/no6969el/GEVR/releases/tag/vr438) - public Beta (BYO-ROM, file-backed images from your cart). Download it, unzip, play.

**vr434 was pulled** on 2026-09-16 because that build still had ROM-derived image data linked into `goldeneye.exe` and could boot without you dropping a ROM. Do not use an old vr434 download.

If this brings you back, **Star** the repo so you can catch the next drops. **Watch → Releases** if you want a ping when we ship.

[Releases](https://github.com/no6969el/GEVR/releases) · [Report a bug](https://github.com/no6969el/GEVR/issues/new/choose) · [Roadmap](docs/ROADMAP.md) · [Controls](docs/CONTROLS.md) · [Credits](CREDITS.md) · [Features](FEATURES.md)

---

## Play

1. Download the **[vr438 Release zip](https://github.com/no6969el/GEVR/releases/tag/vr438)**. **No ROM inside the zip.**
2. Unzip anywhere.
3. **Headset:** run **`Start-GEVR.bat`**. **Monitor / no headset:** run **`Play-on-monitor.bat`**.
4. Point it at your **USA `.z64`**.
5. Recenter with **both thumbstick clicks**.

### First time

The first launch waits once while images prepare into `%LOCALAPPDATA%\GEVR\cache`, then you play.

### Updating from an older Beta

Keep the same `.z64`. Each cut carries a **ship stamp**, so the first launch after an update rebuilds that cache once automatically. You do not need to delete the cache folder by hand.

If the picture still looks wrong: delete `%LOCALAPPDATA%\GEVR` and run the bat again.

**Headset:** `Start-GEVR.bat`. **Monitor / no headset:** `Play-on-monitor.bat` (flat 2D, no OpenXR).

No ROM in the download. You bring yours.

---

## What went wrong with vr434 (honest)

- The first vr434 zip could boot **without** you dropping a ROM because `combined.bin` was still embedded in `goldeneye.exe`.
- That release asset was removed; the tag page explains why.
- The replacement is **vr438**: file-backed images, ROM starter, and automated pack smoke gates under [`packaging/`](packaging/README.md).

---

## What is new in vr438

- **BYO-ROM enforced** - `Start-GEVR.bat` launches **GevrRomStarter**; you must supply a USA GoldenEye `.z64` you own.
- **File-backed images** - in-game textures and UI art come from your ROM on disk; the zip does not ship Nintendo cart data.
- **Cache rebuilds itself on a new tag** - first launch after you update waits once; you do not wipe `%LOCALAPPDATA%\GEVR` by hand.
- **Full runtime in the zip** - includes `glew32.dll` and the other Windows DLLs the build needs.
- **Sharper VR** (carried forward) - supersample 3 with the SrcFbo path we chaired and kept.
- **Boot that actually hands over** - the bat sets FPS + stereo / view-restore so eyes fuse.
- **Movement feel** locked to the 90 Hz loco reference we preferred in the chair.
- **Smaller popup / instruction text** so the big lines are easier to read in the headset.
- Same playspace / aiming keepers from earlier Beta.

Full player notes ship inside the zip as `RELEASE-NOTES.txt`.

---

## What we tested

These paths are what this Beta was built and stared on:

| Path | Notes |
|------|--------|
| **Pimax Crystal Super + SteamVR OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR) (sboys3) | Primary wear path - we do not maintain that driver; we *do* support this experience |
| **Native PimaxXR** | Verified attach / play |
| **Meta Quest 3 + Virtual Desktop OpenXR** | Verified attach / play |

**Refresh rates:** 72 Hz, 80 Hz, and **90 Hz** should work. This zip defaults to **90**. Anything **over 90** (120 / 144 and friends) is still beta-test territory - try it, and [file an Issue](https://github.com/no6969el/GEVR/issues/new/choose) if something feels off.

When you report a bug or crash, please include: **headset**, **OpenXR runtime**, **SteamVR on/off**, **HMD vs monitor**, and whether you used **`Start-GEVR.bat`**.

---

## Known quirks (honest Beta)

We would rather tell you than surprise you:

- Mid-range **crates / props on Dam** can still pop in and out - measured hard; not fixed in this zip yet.
- **Dam water** can look flat or murky - researched; not locked on for this cut.
- **Glass bullet holes** can still show in one eye in places.
- Expect occasional **crashes** while we keep optimizing.

Still worth playing - absolutely. Especially if you miss levels like Facility and want to get brushed up for when we eventually ship the multiplayer add-on. Dam, Facility, that first-person Bond feeling: we are shipping updates as fast as we can.

On a **flat / monitor** setup, classic **local multiplayer** is still there - split-screen couch chaos, same as you remember. The next multiplayer step we are aiming for is a **LAN / local-network add-on**; true online play is further out after that.

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

**Now - enjoy the Beta**
- Solo VR campaign feel
- Comfort, aim, and picture quality
- "It boots, it shoots, it sometimes crashes" honesty

**Next**
- Fewer freezes and softer landings
- Clearer first-run (ROM drop-in, saves that survive updates)
- More visual / HUD comfort for long sits
- Those Dam crates / water / glass quirks above

**Later - the fun extras**
- **Multiplayer add-on** - first goal is **LAN / same-network** play; full online is further after that (calling it early so you know where this is pointed)
- More levels / modes once the base stays stable
- Optional quality knobs without breaking the classic feel

Fuller list: [`docs/ROADMAP.md`](docs/ROADMAP.md). Star + Watch if you want multiplayer and Beta drops without refreshing every day.

---

## For press / curious readers

**One-liner:** Native from-source GoldenEye VR for PC OpenXR - bring your own ROM.

**Longer:** GEVR rebuilds GoldenEye on PC so VR can be done properly (stereo, 6DOF, controller aim), instead of stretching an emulator. Beta means playable and imperfect on purpose while we clear crashes and comfort. Multiplayer and bigger social features sit on the roadmap after the solo VR base is something we are proud to hand strangers.

Credits: [CREDITS.md](CREDITS.md). Boundaries: [PRIOR-ART.md](PRIOR-ART.md), [LICENSE](LICENSE). We do not claim Nintendo's game data, Rare's assets, or third-party engines we did not write.

---

## Docs (secondary)

Deep technical trail: [`docs/00-START-HERE.md`](docs/00-START-HERE.md)  
Controls: [`docs/CONTROLS.md`](docs/CONTROLS.md)  
Beta snapshot: [`docs/BETA.md`](docs/BETA.md) · [`docs/FEATURES-CURRENT.md`](docs/FEATURES-CURRENT.md)  
Coming soon / release policy: [`docs/COMING-SOON.md`](docs/COMING-SOON.md) · [`docs/RELEASE-POLICY.md`](docs/RELEASE-POLICY.md)  
Pack / smoke (vr438): [`packaging/README.md`](packaging/README.md)

---

Jump in and enjoy finally being Bond in GoldenEye VR.
