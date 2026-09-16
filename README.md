<p align="center">
  <img src="GEVR-box-cover.png" alt="GoldenEye 007 VR - GEVR box art" width="480" />
</p>

# GEVR

**GoldenEye. Native. In VR. Bring your own ROM.**

The N64 classic you can finally *stand inside* - not an emulator overlay, not a flat game with a headset stuck on. GEVR is a from-source PC port of *GoldenEye 007* built for real OpenXR VR. Drop in a **USA GoldenEye ROM you legally own**, run `Start-GEVR.bat`, and go.

**Latest playable cut:** [**GEVR Beta vr434**](https://github.com/no6969el/GEVR/releases/tag/vr434) - sharper picture, better boot knobs, smaller popup text. Download it, unzip, play.

If this brings you back, **Star** the repo so you can catch the next drops. **Watch → Releases** if you want a ping when we ship.

[Releases](https://github.com/no6969el/GEVR/releases) · [Report a bug](https://github.com/no6969el/GEVR/issues/new/choose) · [Roadmap](docs/ROADMAP.md) · [Controls](docs/CONTROLS.md) · [Credits](CREDITS.md) · [Features](FEATURES.md)

---

## Play (vr434 - the one to grab)

1. Download the **[vr434 Release zip](https://github.com/no6969el/GEVR/releases/tag/vr434)** (full build - exe + deps + launcher + notes).
2. Unzip anywhere.
3. Put your **USA GoldenEye `.z64` ROM** where the starter asks (or drop it on the app).
4. Run **`Start-GEVR.bat`** (please use the bat - it locks in the good VR settings).
5. Put the headset on. Recenter with **both thumbstick clicks**. Enjoy.

**Already grabbed vr434 early?** The first upload was missing `glew32.dll`, so Windows may report: "The code execution cannot proceed because glew32.dll was not found." We replaced the zip on the release page (same tag, same URL) - please **re-download the [vr434 Release zip](https://github.com/no6969el/GEVR/releases/tag/vr434)** and unzip again.

Default is **VR**. Flat / monitor works too if you just want a look.

No ROM in the download. You bring yours.

---

## What is new in vr434

- **Sharper VR** - supersample 3 with the SrcFbo path we chaired and kept (the picture that made us say “wonderful”).
- **Boot that actually hands over** - `Start-GEVR.bat` sets FPS + stereo / view-restore so eyes fuse (fixes the old zip bat problem).
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

---

Jump in and enjoy finally being Bond in GoldenEye VR.
