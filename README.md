<p align="center">
  <img src="GEVR-box-cover.png" alt="GoldenEye 007 VR - GEVR box art" width="480" />
</p>

# GEVR

**GoldenEye. Native. In VR. Bring your own ROM.**

The N64 classic you can finally *stand inside* - not an emulator overlay, not a flat game with a headset stuck on. GEVR is a from-source PC port of *GoldenEye 007* built for real OpenXR VR. You supply a **USA GoldenEye ROM you legally own**; the starter prepares a local cache and **`Start-GEVR.bat`** launches through **GevrRomStarter** (not bare `goldeneye.exe`).

**Latest playable cut:** [**GEVR Beta vr442**](https://github.com/no6969el/GEVR/releases/latest) - public Beta (BYO-ROM, file-backed images from your cart). Download it, unzip, play.

**vr441** and **vr440** stay on Releases for history. Grab **vr442** unless you are deliberately comparing older boots.

If this brings you back, **Star** the repo and [**follow @no6969el**](https://github.com/no6969el) so you can catch the next drops. **Watch -> Releases** if you want a ping when we ship. Between cuts, we keep a [living status on Reddit](https://www.reddit.com/r/QuietWindows/comments/1whmk8l/gevr_living_status_goldeneye_in_native_openxr_vr/) - honest fan wear notes, not a second readme. Want to fund the next cuts? [Patreon](https://www.patreon.com/cw/GEVR) - the zip stays free.

[Latest zip](https://github.com/no6969el/GEVR/releases/latest) · [Report a bug](https://github.com/no6969el/GEVR/issues/new/choose) · [Roadmap](docs/ROADMAP.md) · [Controls](docs/CONTROLS.md) · [Credits](CREDITS.md) · [Features](FEATURES.md) · [Support](https://www.patreon.com/cw/GEVR)

---

## Play (vr442 - the one to grab)

1. Download the **[Latest Release zip](https://github.com/no6969el/GEVR/releases/latest)** (exe, `glew32.dll`, other runtime DLLs, ROM starter, launcher, notes). **No ROM inside the zip.**
2. Unzip anywhere.
3. Run **`Start-GEVR.bat`** - it sets VR boot knobs and starts **GevrRomStarter.exe**.
4. Point at your **USA GoldenEye `.z64`** when asked. Images extract to `%LOCALAPPDATA%\\GEVR\\cache\\<ROM-hash>\\`. Each Beta tag bumps a **ship stamp** so the first launch after an update rebuilds that cache once from your ROM.
5. Put the headset on. Recenter with **both thumbstick clicks**. Enjoy.

**Please use the bat** - it locks in the good VR settings and runs the ROM starter we ship for this cut (not bare `goldeneye.exe`).

Default is **VR**. Flat / monitor works too if you just want a look (`Play-on-monitor.bat`).

No ROM in the download. You bring yours.

### New install vs returning after an update

- **New install:** first launch waits once while images prepare into `%LOCALAPPDATA%\\GEVR\\cache`, then you play. Saves start empty.
- **Returning after a Beta update:** keep the same USA `.z64`. The ship stamp forces **one** automatic re-prepare. **Saves are kept.** You do not delete the cache folder for a normal update.
- **Picture still looks wrong:** run **`Clear-GEVR-cache.bat`** from the zip (type **YES**) to wipe cache only. Optional last resort: delete `%LOCALAPPDATA%\\GEVR` (that also drops saves). See `RELEASE-NOTES.txt` in the zip.

---

## What is new in vr442

Internal cook **452**. Same honest Beta, more of the chair wear you asked for.

- **Tank auto-mount** when you are standing on the chassis. **Stick pitch** aims the shells (yaw already worked).
- **Grenade launcher** is single-shot again - no more double-spawn or blasting your own feet.
- **Rockets** point their nose along the flight path.
- **Die / continue / pad reload** no longer needs a full quit of `goldeneye.exe` ([issue #38](https://github.com/no6969el/GEVR/issues/38)).
- **Far characters** are easier to see (007 visibility boost).
- **Empty left hand** shows a temporary cube (MASK left) so you know where it is.
- **Hard-crash fault file** - if the exe dies hard, look for `gevr-fault-*.txt` beside it. That file helps us dig big-explosion crashes.

**Already in this zip** from recent cooks (still true on vr442):

- Dual-wield fire from each hand, not a right-hand mirror
- Per-hand tracers that stay on their own beam
- Thrown grenades follow the hand
- Magnum drum / ammo HUD polish
- Full chair boot from vr441 (bodies stay after kills, explosion / fire color, tuned aim / ADS)

Full player notes ship inside the zip as `RELEASE-NOTES.txt`.

---

## What's cooking (later update)

Soft list only. **Not** in the vr442 zip as finished work. Do not treat these as shipped.

- Two-hand support snap, and the cube hiding when your hands get near
- Hertz: boot is still **90-pinned**. Runtime refresh request is [issue #49](https://github.com/no6969el/GEVR/issues/49) for a later EXE
- Ghost hand is parked. Nicer hands after that
- Big object / plane-shell explosion hard crash can still happen (you now get the fault file)

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

**Older tag (history):** **vr434** was pulled because ROM-derived images were still linked into `goldeneye.exe`. The tag page stays; do not use an old vr434 download. **vr440** is still published if you want to compare the picture-only boot.

---

## What we tested

These paths are what this Beta was built and stared on:

| Path | Notes |
|------|--------|
| **Pimax Crystal Super + SteamVR OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR) (sboys3) | Primary wear path - we do not maintain that driver; we *do* support this experience |
| **Native PimaxXR** | Verified attach / play |
| **Meta Quest 3 + Virtual Desktop OpenXR (VDXR)** | Verified attach / play |
| **RTX 5060 laptop + Quest 3 + Virtual Desktop VDXR** | BarZ wear **vr441**, 2026-09-17; ran surprisingly well (one data point, not a minimum spec) |

**Refresh rates:** 72 Hz and 80 Hz should work. Default and wear recommendation is **90**. Anything **over 90** is still beta-test territory - try it, and [file an Issue](https://github.com/no6969el/GEVR/issues/new/choose) if something feels off. We do **not** call 120 / 144 signed off. The public boot is still **90-pinned**; asking the runtime for another rate is later ([issue #49](https://github.com/no6969el/GEVR/issues/49)).

When you report a bug or crash, please include: **headset**, **OpenXR runtime**, **SteamVR on/off**, **HMD vs monitor**, whether you used **`Start-GEVR.bat`**, your **`gevr-*-boot.cmd`** filename from the zip folder, any log next to the zip or in the console, and any **`gevr-fault-*.txt`** beside the exe. Do **not** upload your ROM. [Open an Issue](https://github.com/no6969el/GEVR/issues/new/choose).

---

## Known quirks (honest Beta)

We would rather tell you than surprise you. These are **vr442 today**.

- **Big explosions** (large objects, plane shells) can still hard-crash. If they do, grab `gevr-fault-*.txt` beside the exe before you relaunch.
- Alarm can keep ringing after a death or stage return.
- Mid-range **crates / props on Dam** can still pop in and out.
- **Dam water** can look flat or murky.
- **Glass bullet holes** can still show in one eye.
- **HUD text** can sit too close or hard to read in depth.
- **Headset refresh:** public boot stays 90-pinned. Some Virtual Desktop / runtime setups only enter VR at 90 Hz - [issue #49](https://github.com/no6969el/GEVR/issues/49).
- Empty left hand is a **cube** for now. Ghost fingers and nicer hands are later.
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

**Now - enjoy the Beta (vr442)**
- Solo VR campaign feel
- Tank climb + turret pitch, dual-wield fire, rockets that point where they fly
- Comfort, aim, and picture quality
- "It boots, it shoots, it sometimes crashes" honesty
- Local / split-screen multiplayer on a monitor

**Cooking**
- Two-hand support snap and cube hide-on-near
- Runtime Hertz request ([issue #49](https://github.com/no6969el/GEVR/issues/49))
- Ghost empty hand (parked); nicer mesh after that
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
