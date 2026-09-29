<p align="center">
  <img src="GEVR-box-cover.png" alt="GoldenEye 007 VR - GEVR box art" width="480" />
</p>

# GEVR

**GoldenEye. Native. In VR. Bring your own ROM.**

> **Source note:** New GEVR **product code** is developed privately. This public repo stays the home for **player docs**, **Issues**, and **Beta zip Releases**. Grab playable builds from [Latest](https://github.com/no6969el/GEVR/releases/latest) (or **Update** in GevrRomStarter). Historical trees and older tags remain for reference; they are not the live workshop. Freeze tip: [`15449d0`](https://github.com/no6969el/GEVR/commit/15449d0eb55730f5cfc22a6cbcb7fceb40e5ebe3). See [`docs/SOURCE.md`](docs/SOURCE.md). Playable work ships as Beta zips; this tree is player-facing docs + historical reference.

> **vr450.2 (2026-09-28):** GitHub **Latest**. Keepers hard-coded in the binary: **cuff**, **FREEARM** ([#109](https://github.com/no6969el/GEVR/issues/109)), **VTXFIXREFS** ([#117](https://github.com/no6969el/GEVR/issues/117)), door snap, false doors, corpse pass, re-grab, mines, landmark, aim scale, embed eye. **Grab [vr450.2](https://github.com/no6969el/GEVR/releases/tag/vr450.2)** or **Update** in GevrRomStarter.

---
The N64 classic you can finally *stand inside* - not an emulator overlay, not a flat game with a headset stuck on. GEVR is a from-source PC port of *GoldenEye 007* built for real OpenXR VR. You supply a **USA GoldenEye ROM you legally own**; the starter prepares a local cache and **`Start-GEVR.bat`** launches through **GevrRomStarter** (not bare `goldeneye.exe`).

**Latest playable cut:** [**vr450.2**](https://github.com/no6969el/GEVR/releases/latest) - zip **`GEVR-Beta-vr450.2-win64.zip`**.

**Direct download:** [`GEVR-Beta-vr450.2-win64.zip`](https://github.com/no6969el/GEVR/releases/download/vr450.2/GEVR-Beta-vr450.2-win64.zip)

Older tags (**vr450** / **vr450.1** / **vr445.2** / earlier) stay for history. Grab [**vr450.2**](https://github.com/no6969el/GEVR/releases/tag/vr450.2).

If this brings you back, **Star** the repo and [**follow @no6969el**](https://github.com/no6969el) so you can catch the next drops. **Watch -> Releases** if you want a ping when we ship. Between cuts, we keep a [living status on Reddit](https://www.reddit.com/r/QuietWindows/comments/1whmk8l/gevr_living_status_goldeneye_in_native_openxr_vr/) - honest fan wear notes, not a second readme. For port help and GoldenEye fan chat, hop in [**Discord**](https://discord.gg/flat2vr) (BYO ROM - do not upload your ROM; setup details and logs only). Want to fund the next cuts? [Patreon](https://www.patreon.com/cw/GEVR) - the zip stays free.

[Latest zip](https://github.com/no6969el/GEVR/releases/latest) · [Direct zip](https://github.com/no6969el/GEVR/releases/download/vr450.2/GEVR-Beta-vr450.2-win64.zip) · [Report a bug](https://github.com/no6969el/GEVR/issues/new/choose) · [Discord](https://discord.gg/flat2vr) · [Controls](docs/CONTROLS.md) · [Credits](CREDITS.md) · [Other projects using GEVR](docs/OTHER-PROJECTS.md) · [Features](FEATURES.md) · [Support](https://www.patreon.com/cw/GEVR)

---

## Controller layout (vr450.2)

Quest / Meta Touch, Valve Index, and Oculus-style OpenXR binds (same actions):

| Input | What it does |
|---|---|
| **Left stick** | Walk |
| **Right stick** | Turn (Smooth or Snap — **VR Settings**, look right on the intro hub) |
| **Both thumbstick clicks** | Recenter playspace |
| **Trigger** | Fire (left fires left gun, right fires right when dual-wielding) |
| **Squeeze / grip** | **AIM / ADS** |
| **A** (right face button on Quest/Oculus Touch; Index **A**) | Next weapon |
| **X** (left Quest/Oculus) | Previous weapon |
| **B** | Reload |

**Short examples:** click both sticks to recenter · squeeze to ADS, then walk with the left stick · throw a prox mine, re-grab it, or stick it on a guard · tap **A** / left **X** to cycle guns, **B** to reload.

Classic squeeze = AIM. Fuller notes: [`docs/CONTROLS.md`](docs/CONTROLS.md).

---

## Streamer playtests

**Note:** This clip is from an **older public cut (~vr441)**. The game has moved on - grab **[Latest (vr450.2)](https://github.com/no6969el/GEVR/releases/latest)** for what you can play now. Picture, comfort, and bugs may not match the video.

[![GoldenEye VR Is Finally Here… And You Can Play It Now](https://img.youtube.com/vi/z4B0Ceqrf6I/maxresdefault.jpg)](https://www.youtube.com/watch?v=z4B0Ceqrf6I)

[Watch on YouTube](https://www.youtube.com/watch?v=z4B0Ceqrf6I) - streamer playtest.

---

## Play (vr450.2 - the one to grab)

1. Download **[GEVR-Beta-vr450.2-win64.zip](https://github.com/no6969el/GEVR/releases/download/vr450.2/GEVR-Beta-vr450.2-win64.zip)** from [Latest](https://github.com/no6969el/GEVR/releases/latest) / [tag vr450.2](https://github.com/no6969el/GEVR/releases/tag/vr450.2) (exe, `glew32.dll`, other runtime DLLs, ROM starter, launcher, notes). **No ROM inside the zip.**
2. Unzip anywhere.
3. Run **`Start-GEVR.bat`** - it starts **GevrRomStarter.exe**. The starter finds **`goldeneye.exe` in the same folder** and sets the game path for you.
4. Point at your **USA GoldenEye `.z64`** when asked. Images extract to `%LOCALAPPDATA%\GEVR\cache\<ROM-hash>\`. Each Beta tag bumps a **ship stamp** so the first launch after an update rebuilds that cache once from your ROM.
5. Put the headset on. Recenter with **both thumbstick clicks**.
6. On the intro hub, **look right** for **VR SETTINGS** and tune turn comfort. Enjoy.

**Please use the bat** - it runs the ROM starter we ship for this cut (not bare `goldeneye.exe`).

Default is **VR**. Flat / monitor is playable too (`Play-on-monitor.bat`) - same game, and it takes the fixes as we improve the VR cut.

No ROM in the download. You bring yours.

### New install vs returning after an update

- **New install:** first launch waits once while images prepare into `%LOCALAPPDATA%\GEVR\cache`, then you play. Saves start empty.
- **Returning after a Beta update:** keep the same USA `.z64`. The ship stamp forces **one** automatic re-prepare. **Saves and VR Settings prefs are kept** under `%LOCALAPPDATA%\GEVR`. Or open the starter and use **Update** when it offers a newer tag. You do not delete the cache folder for a normal update.
- **Picture still looks wrong:** the tag notes say delete `%LOCALAPPDATA%\GEVR` and run the bat again (that also drops saves). Prefer **`Clear-GEVR-cache.bat`** first (type **YES**) if you want to keep saves. See `RELEASE-NOTES.txt` in the zip.

---

## What is new in vr450.2

Wear-focused cut. Keepers are **hard-coded in the binary** — they stay on with a clean launch (no special boot flags).

- **Cuff / watch** — left-hand cuff stays with the controller through stage transitions
- **FREEARM ([#109](https://github.com/no6969el/GEVR/issues/109))** — two-handed NPC / weapon poses look better
- **VTXFIXREFS ([#117](https://github.com/no6969el/GEVR/issues/117))** — more stable Surface geometry
- **Door snap** — door-edge aim / hit more dependable around room boundaries
- **False doors** — quieter decoy / false door presentation
- **Corpse pass** — dead bodies jam doors less often
- **Re-grab** — thrown remote / prox mines can be picked back up
- **Mines** — stick to guards, follow them, stay visible while carried
- **Landmark / aim scale / embed eye** — aim and world marks stay readable in headset

### Next series

Levels and **gameplay stoppers**: Frigate door / aperture, mission progression and locks, save-slot coverage, remaining prop-on-prop / Dam-water problems.

Full zip notes: `RELEASE-NOTES.txt` in the zip / [tag](https://github.com/no6969el/GEVR/releases/tag/vr450.2).

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

**Half-speed / mushy VR?** Turn **SteamVR Motion Smoothing Off** (Settings → Video; also Applications → GEVR / `goldeneye.exe`) and **Virtual Desktop Space Warp Off**. MotSmooth / Space Warp halves the app rate; GEVR follows that rate, so the game feels half-speed. Not a GEVR toggle. Details: [`docs/BETA.md`](docs/BETA.md#half-speed--mushy-vr).

When you report a bug or crash, please include: **headset**, **OpenXR runtime**, **SteamVR on/off**, **HMD vs monitor**, whether you used **`Start-GEVR.bat`**, your **`gevr-*-boot.cmd`** filename from the zip folder, any log next to the zip or in the console, and any **`gevr-fault-*.txt`** beside the exe. Do **not** upload your ROM. [Open an Issue](https://github.com/no6969el/GEVR/issues/new/choose) or ask on [Discord](#discord-help--fan-chat).

---

## Discord (help + fan chat)

**[Join the GEVR Discord](https://discord.gg/flat2vr)** for:

- **Port help** - install, updates, ROM cache, comfort, crashes (tell us your headset and OpenXR runtime; **never upload your ROM**)
- **Fan chat** - missions, nostalgia, loadouts, and GoldenEye talk with people actually playing the Beta

GitHub Issues are still great for tracked bugs; Discord is often faster for "am I doing this right?" questions.

**Discord (help + fan chat):** [discord.gg/flat2vr](https://discord.gg/flat2vr) - port help and GoldenEye fan chat with other players. BYO ROM / do not upload your ROM (setup details and logs only).

---

## Known quirks (honest Beta)

We would rather tell you than surprise you. These are **vr450.2** today.

- **Half-speed / mushy VR:** turn **SteamVR Motion Smoothing Off** and **Virtual Desktop Space Warp Off** before blaming Hertz ([BETA.md](docs/BETA.md#half-speed--mushy-vr)).
- **Next series** is levels / gameplay stoppers (Frigate doors, mission locks, save slots, remaining prop / Dam-water issues) — not finished in this zip.
- **Melee / fist** is in (swing-based), but **not finely tuned yet** - be careful standing next to characters you are not supposed to harm ([issue #75](https://github.com/no6969el/GEVR/issues/75)).
- **Big explosions** (large objects, plane shells) can still hard-crash. If they do, grab `gevr-fault-*.txt` beside the exe before you relaunch.
- Alarm can keep ringing after a death or stage return.
- **Dam water** can look flat or murky.
- **Glass bullet holes** can still show in one eye.
- **HUD text** can sit too close or hard to read in depth.
- **Headset refresh:** follows your HMD rate now. High Hz is still Beta-test territory ([issue #49](https://github.com/no6969el/GEVR/issues/49)).
- Empty hand draws a **cube** (smaller; hides when that hand holds a weapon).
- Expect occasional **crashes** while we keep optimizing.

Still worth playing - absolutely. Facility, Dam, tanks that actually let you in, that first-person Bond feeling.

On a **flat / monitor** setup, the game is fully playable (`Play-on-monitor.bat`) and picks up the same fixes as we improve VR. Classic **local / split-screen multiplayer** is still there - couch chaos, same as you remember.

More tester notes: [BETA.md](docs/BETA.md) · [CONTROLS.md](docs/CONTROLS.md).

---

## Why this exists

GoldenEye is one of the most-wanted "I wish I could stand inside it" games on Earth. GEVR's north star:

- **Native / from-source** - full ownership of the game loop for proper VR
- **OpenXR** - Crystal, Quest via PC, SteamVR-class HMDs
- **Your ROM** - legal ownership stays with you
- **Feel first** - 6DOF, aiming, presence; then polish; then extras

More pitch and cover energy: [FEATURES.md](FEATURES.md).

---

## For press / curious readers

**One-liner:** Native from-source GoldenEye VR for PC OpenXR - bring your own ROM.

**Longer:** GEVR rebuilds GoldenEye on PC so VR can be done properly (stereo, 6DOF, controller aim), instead of stretching an emulator. Beta means playable and imperfect on purpose while we clear crashes and comfort. Local / split-screen multiplayer on a monitor is in this cut.

Credits: [CREDITS.md](CREDITS.md). Boundaries: [PRIOR-ART.md](PRIOR-ART.md), [LICENSE](LICENSE). Other product projects that reuse GEVR work (name, docs, tools, playbook): [docs/OTHER-PROJECTS.md](docs/OTHER-PROJECTS.md). We do not claim Nintendo's game data, Rare's assets, or third-party engines we did not write.

Attribution: **BarZ / [@no6969el](https://github.com/no6969el)**. Star and follow if you want the next cut.

---

## Docs (secondary)

Deep technical trail: [`docs/00-START-HERE.md`](docs/00-START-HERE.md)  
Controls: [`docs/CONTROLS.md`](docs/CONTROLS.md)  
Beta snapshot: [`docs/BETA.md`](docs/BETA.md) · [`docs/FEATURES-CURRENT.md`](docs/FEATURES-CURRENT.md)  
Other projects using GEVR: [`docs/OTHER-PROJECTS.md`](docs/OTHER-PROJECTS.md)  
Pack / smoke: [`packaging/README.md`](packaging/README.md) · ship boot allowlist: [`docs/ship-feature-checklist.md`](docs/ship-feature-checklist.md)

---

Jump in and enjoy finally being Bond in GoldenEye VR.
