<p align="center">
  <img src="GEVR-box-cover.png" alt="GoldenEye 007 VR - GEVR box art" width="480" />
</p>

# GEVR

**GoldenEye. Native. In VR. Bring your own ROM.**

The N64 classic you can finally *stand inside* - not an emulator overlay, not a flat game with a headset stuck on. GEVR is a from-source PC port of *GoldenEye 007* built for real OpenXR VR. You supply a **USA GoldenEye ROM you legally own**; the starter prepares a local cache and **`Start-GEVR.bat`** launches through **GevrRomStarter** (not bare `goldeneye.exe`).

**Latest playable cut:** [**GEVR Beta vr441**](https://github.com/no6969el/GEVR/releases/tag/vr441) - public Beta (BYO-ROM, file-backed images from your cart). Download it, unzip, play.

**vr440** is still on Releases for comparison, but it is **not** Latest - same `goldeneye.exe` as vr441, picture-only boot. Grab **vr441** unless you are deliberately comparing boots (see **What went wrong in vr440** below).

If this brings you back, **Star** the repo so you can catch the next drops. **Watch -> Releases** if you want a ping when we ship. Play **vr441** until then. Between cuts, we keep a [living status on Reddit](https://www.reddit.com/r/QuietWindows/comments/1whmk8l/gevr_living_status_goldeneye_in_native_openxr_vr/) - honest fan wear notes, not a second readme. Want to fund the next cuts? [Patreon](https://www.patreon.com/cw/GEVR) - the zip stays free.

[Releases](https://github.com/no6969el/GEVR/releases) · [Report a bug](https://github.com/no6969el/GEVR/issues/new/choose) · [Roadmap](docs/ROADMAP.md) · [Controls](docs/CONTROLS.md) · [Credits](CREDITS.md) · [Features](FEATURES.md) · [Support](https://www.patreon.com/cw/GEVR)

---

## Play (vr441 - the one to grab)

1. Download the **[vr441 Release zip](https://github.com/no6969el/GEVR/releases/tag/vr441)** (exe, `glew32.dll`, other runtime DLLs, ROM starter, launcher, notes). **No ROM inside the zip.**
2. Unzip anywhere.
3. Run **`Start-GEVR.bat`** - it sets VR boot knobs and starts **GevrRomStarter.exe**.
4. Point at your **USA GoldenEye `.z64`** when asked. Images extract to `%LOCALAPPDATA%\\GEVR\\cache\\<ROM-hash>\\`. Each Beta tag bumps a **ship stamp** so the first launch after an update rebuilds that cache once from your ROM.
5. Put the headset on. Recenter with **both thumbstick clicks**. Enjoy.

**Please use the bat** - it locks in the good VR settings and runs the ROM starter we ship for this cut (not bare `goldeneye.exe`).

Default is **VR**. Flat / monitor works too if you just want a look.

No ROM in the download. You bring yours.

---

## What went wrong in vr440

- **vr440** shipped the same `goldeneye.exe` as **vr441**, but **`Start-GEVR.bat`** only ran the **picture KEEP** boot - the visual stack we chaired (stereo, SrcFbo sharpness, supersample, sky / playspace).
- The **chair features** were already in the binary; the public boot **never turned them on**. Bodies could vanish after kills, explosion textures could look wrong, and aim / the gun arm were not on the tuned **PLAY0** path we wear in the chair.
- **vr441** is that same binary with the **full PLAY0 KEEP boot** in `gevr-vr441-boot.cmd`. The **vr440** tag stays published so you can compare - it is not Latest.

**Older tag (history):** **vr434** was pulled because ROM-derived images were still linked into `goldeneye.exe` and that zip could boot without your ROM. The tag page stays; do not use an old vr434 download.

---

## What is new in vr441

- **Full chair boot** - same `goldeneye.exe` as vr440, but `Start-GEVR.bat` now runs `gevr-vr441-boot.cmd`, which turns on bodies-stay, explosion/fire byte-order fixes, and the tuned aim / ADS path. Those code paths existed in the binary from vr438 onward; **vr440 never armed them in the public boot** (picture KEEP only).
- **vr440** is still on Releases for comparison but is not Latest.

---

## What's coming (stay on vr441)

No new zip yet. Keep playing **vr441**. When the next wear-passed cut lands, it will be a GitHub Release. **Watch** this repo (Watch -> Releases) so you get pinged. Star it if you want the next Bond drop without hunting.

**In the chair right now** (working on, not in your unzip):
- **Watch finger + pause menu** - so the watch and pause actually work in VR: confirm, highlight in both eyes, that stretched finger when you pull the watch. This is the current EXE project. Several open Issues live here.
- **Ammo HUD picture** - ammo icons can look stretched or fat in the headset. That is **render** distortion, not clip or overlap (placement already moved). Picture first. Not wear-passed, so not shipped.

**Known, looking at** (not promising it in the next drop):
- **Black flicker** in VR at Facility gas tanks and Bunker after Surface ([issue #55](https://github.com/no6969el/GEVR/issues/55)). Dig exists. Not chaired. File more sits if you hit it.

Keep shooting. Watch GitHub. We will tell you when Latest moves.

---

## What vr438 introduced (still true)

- **BYO-ROM enforced** - `Start-GEVR.bat` → **GevrRomStarter**; you must supply a USA GoldenEye `.z64` you own.
- **File-backed images** - in-game textures and UI art come from your ROM on disk; the zip does not ship Nintendo cart data.
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
| **RTX 5060 laptop + Quest 3 + Virtual Desktop VDXR** | BarZ wear **vr441**, 2026-09-17; ran surprisingly well (one data point, not a minimum spec) |

**Refresh rates:** 72 Hz, 80 Hz, and **90 Hz** should work. This zip defaults to **90**. Anything **over 90** (120 / 144 and friends) is still beta-test territory - try it, and [file an Issue](https://github.com/no6969el/GEVR/issues/new/choose) if something feels off.

When you report a bug or crash, please include: **headset**, **OpenXR runtime**, **SteamVR on/off**, **HMD vs monitor**, whether you used **`Start-GEVR.bat`**, your **`gevr-*-boot.cmd`** filename from the zip folder, and any log next to the zip or in the console. Do **not** upload your ROM. [Open an Issue](https://github.com/no6969el/GEVR/issues/new/choose).

---

## Known quirks (honest Beta)

We would rather tell you than surprise you:

- Mid-range **crates / props on Dam** can still pop in and out - measured hard; not fixed in this zip yet.
- **Dam water** can look flat or murky - researched; not locked on for this cut.
- **Glass bullet holes** can still show in one eye in places.
- **Pause / watch** confirm is still rough; watch highlight can miss an eye; watch finger can stretch when you pull it (in the chair now - see What's coming).
- **Ammo HUD picture** can look stretched or fat in VR (render, not clip - in the chair, not wear-passed).
- **Black flicker** in VR (Facility gas tanks; Bunker after Surface) - looking at it, not a shipped fix. [Issue #55](https://github.com/no6969el/GEVR/issues/55).
- Expect occasional **crashes** while we keep optimizing.
- After you **finish a level**, sit on the **character / folder screen**, then load again, you can spawn in junk space (glitchy / empty). **Quit the game fully and run `Start-GEVR.bat` again** - loading another mission in the same process often stays broken. Please [file an Issue](https://github.com/no6969el/GEVR/issues/new/choose) with headset, runtime, map, and a log or short clip if you have one. No ROM files.

Still worth playing - absolutely. Facility, Dam, that first-person Bond feeling. Stay on **vr441**, Watch GitHub, and we will ping you when Latest moves.

On a **flat / monitor** setup, classic **local multiplayer** is still there - split-screen couch chaos, same as you remember. LAN / same-network is later, not the next zip. True online is further after that.

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

**Next (in the chair, not in the zip)**
- Watch finger + pause menu (usable watch / confirm in VR)
- Ammo HUD picture (render first; not wear-passed)

**Also on the board**
- Fewer freezes and softer landings
- Clearer first-run (ROM drop-in, saves that survive updates)
- Those Dam crates / water / glass quirks above

**Later - the fun extras**
- **Multiplayer add-on** - LAN / same-network first, full online further after that (not the next zip)
- More levels / modes once the base stays stable
- Optional quality knobs without breaking the classic feel

Fuller list: [`docs/ROADMAP.md`](docs/ROADMAP.md). Star + **Watch -> Releases** if you want the next zip without refreshing every day.

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
Pack / smoke: [`packaging/README.md`](packaging/README.md) · ship boot allowlist: [`docs/ship-feature-checklist.md`](docs/ship-feature-checklist.md)

---

Jump in and enjoy finally being Bond in GoldenEye VR.
