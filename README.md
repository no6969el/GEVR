<p align="center">
  <img src="GEVR-box-cover.png" alt="GoldenEye 007 VR - GEVR box art" width="480" />
</p>

# GEVR

**GoldenEye. Native. In VR. Bring your own ROM.**

The N64 classic you can finally *stand inside* - not an emulator overlay, not a flat game with a headset stuck on. GEVR is a from-source PC port of *GoldenEye 007* built for real OpenXR VR. You supply a **USA GoldenEye ROM you legally own**; the starter prepares a local cache and **`Start-GEVR.bat`** launches through **GevrRomStarter** (not bare `goldeneye.exe`).

**Latest public release:** [**GEVR Beta vr434**](https://github.com/no6969el/GEVR/releases/tag/vr434) was **pulled** on 2026-09-16 because that build still had ROM-derived image data linked into `goldeneye.exe`. Do not use an old vr434 download.

**Next cut:** **vr438** (file-backed images + ROM drop-in) is being packed and owner-tested before upload. **Watch → Releases** for the tag when it lands.

If this brings you back, **Star** the repo so you can catch the next drops.

[Releases](https://github.com/no6969el/GEVR/releases) · [Report a bug](https://github.com/no6969el/GEVR/issues/new/choose) · [Roadmap](docs/ROADMAP.md) · [Controls](docs/CONTROLS.md) · [Credits](CREDITS.md) · [Features](FEATURES.md)

---

## Play (when vr438 ships)

1. Download the **vr438 Release zip** (exe + DLLs + ROM starter + launcher + notes). **No ROM inside the zip.**
2. Unzip anywhere.
3. Run **`Start-GEVR.bat`** - it sets VR boot knobs and starts **GevrRomStarter.exe**.
4. Point at your **USA GoldenEye `.z64`** when asked. Images extract to `%LOCALAPPDATA%\GEVR_CACHE`.
5. Put the headset on. Recenter with **both thumbstick clicks**. Enjoy.

Default is **VR**. Flat / monitor works too if you just want a look.

Until vr438 is public, there is no supported all-in-one download on Releases. Fan builds from source are your own responsibility.

---

## What went wrong with vr434 (honest)

- The first vr434 zip could boot **without** you dropping a ROM because `combined.bin` was still embedded in `goldeneye.exe`.
- That release asset was removed; the tag page explains why.
- The replacement is **vr438**: file-backed images, ROM starter, and automated pack smoke gates under [`packaging/`](packaging/README.md).

---

## What we tested

These paths are what recent Betas were built and stared on:

| Path | Notes |
|------|--------|
| **Pimax Crystal Super + SteamVR OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR) (sboys3) | Primary wear path - we do not maintain that driver; we *do* support this experience |
| **Native PimaxXR** | Verified attach / play |
| **Meta Quest 3 + Virtual Desktop OpenXR** | Verified attach / play |

**Refresh rates:** 72 Hz, 80 Hz, and **90 Hz** should work. New zips default to **90**. Anything **over 90** (120 / 144 and friends) is still beta-test territory - try it, and [file an Issue](https://github.com/no6969el/GEVR/issues/new/choose) if something feels off.

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

GoldenEye is one of the most-wanted “I wish I could stand inside it” games on Earth. GEVR’s north star:

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
- “It boots, it shoots, it sometimes crashes” honesty

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

Credits: [CREDITS.md](CREDITS.md). Boundaries: [PRIOR-ART.md](PRIOR-ART.md), [LICENSE](LICENSE). We do not claim Nintendo’s game data, Rare’s assets, or third-party engines we did not write.

---

## Docs (secondary)

Deep technical trail: [`docs/00-START-HERE.md`](docs/00-START-HERE.md)  
Controls: [`docs/CONTROLS.md`](docs/CONTROLS.md)  
Beta snapshot: [`docs/BETA.md`](docs/BETA.md) · [`docs/FEATURES-CURRENT.md`](docs/FEATURES-CURRENT.md)  
Coming soon / release policy: [`docs/COMING-SOON.md`](docs/COMING-SOON.md) · [`docs/RELEASE-POLICY.md`](docs/RELEASE-POLICY.md)  
Pack / smoke (vr438): [`packaging/README.md`](packaging/README.md)

---

Jump in and enjoy finally being Bond in GoldenEye VR.
