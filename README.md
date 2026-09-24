<p align="center">
  <img src="GEVR-box-cover.png" alt="GoldenEye 007 VR - GEVR box art" width="480" />
</p>

# GEVR

**GoldenEye. Native. In VR. Bring your own ROM.**

> **vr445.2 (2026-09-24):** GitHub **Latest**. KEEP stack default-on: **#74** playspace / free move / hands follow · **#75** melee swing pose · **#82** Janus spawn · **gun origin** · **#84** walk/run + **ANIMFRAMES** · Dam **SKYWORLD** · cadence from 445.1 · temp **MODEMDROP=3**. **Grab [vr445.2](https://github.com/no6969el/GEVR/releases/tag/vr445.2)** or **Update** in GevrRomStarter.
>
> *Footnote:* Decided to test some other features longer before pushing. WATERRECT / GRIPUSE / slot4 stay on [vr450](https://github.com/no6969el/GEVR/releases/tag/vr450) / [vr450.1](https://github.com/no6969el/GEVR/releases/tag/vr450.1) (pre-release), **not** Latest.

---
The N64 classic you can finally *stand inside* - not an emulator overlay, not a flat game with a headset stuck on. GEVR is a from-source PC port of *GoldenEye 007* built for real OpenXR VR. You supply a **USA GoldenEye ROM you legally own**; the starter prepares a local cache and **`Start-GEVR.bat`** launches through **GevrRomStarter** (not bare `goldeneye.exe`).

**Latest playable cut:** [**vr445.2**](https://github.com/no6969el/GEVR/releases/latest) - zip **`GEVR-Beta-vr445.2-win64.zip`**.

**vr450** / **vr450.1** stay published as **pre-release** (tags + zips kept). **vr445.1** / **vr445** / older tag pages stay for history. Older **zips are gone** where we pulled them. Grab [**vr445.2**](https://github.com/no6969el/GEVR/releases/tag/vr445.2).

If this brings you back, **Star** the repo and [**follow @no6969el**](https://github.com/no6969el) so you can catch the next drops. **Watch -> Releases** if you want a ping when we ship. Between cuts, we keep a [living status on Reddit](https://www.reddit.com/r/QuietWindows/comments/1whmk8l/gevr_living_status_goldeneye_in_native_openxr_vr/) - honest fan wear notes, not a second readme. For port help and GoldenEye fan chat, hop in [**Discord**](https://discord.gg/flat2vr) (BYO ROM - do not upload your ROM; setup details and logs only). Want to fund the next cuts? [Patreon](https://www.patreon.com/cw/GEVR) - the zip stays free.

[Latest zip](https://github.com/no6969el/GEVR/releases/latest) · [Report a bug](https://github.com/no6969el/GEVR/issues/new/choose) · [Discord](https://discord.gg/flat2vr) · [Roadmap](docs/ROADMAP.md) · [Controls](docs/CONTROLS.md) · [Credits](CREDITS.md) · [Other projects using GEVR](docs/OTHER-PROJECTS.md) · [Features](FEATURES.md) · [Support](https://www.patreon.com/cw/GEVR)

---

## Controller layout (vr445.2)

Quest / Meta Touch, Valve Index, and Oculus-style OpenXR binds (same actions):

| Input | What it does |
|---|---|
| **Left stick** | Walk |
| **Right stick** | Turn (Smooth or Snap — **VR Settings**, look right on the intro hub) |
| **Both thumbstick clicks** | Recenter playspace |
| **Trigger** | Fire (left fires left gun, right fires right when dual-wielding) |
| **Squeeze / grip** | **AIM / ADS** |
| **A** (right face button on Quest/Oculus Touch; Index **A**) | USE / reload (view-cone) |
| **X** (left Quest/Oculus) | Previous weapon (when weapon-cycle is armed) |
| **Head / room-scale** | Look around; physically walk to move in Bond-world |

Classic squeeze = AIM. Contextual Grip / GRIPUSE is **not** in Latest (further testing on the 450 line). Fuller notes: [`docs/CONTROLS.md`](docs/CONTROLS.md).

---

## Streamer playtests

**Note:** This clip is from an **older public cut (~vr441)**. The game has moved on - grab **[Latest (vr445.2)](https://github.com/no6969el/GEVR/releases/latest)** for what you can play now. Picture, comfort, and bugs may not match the video.

[![GoldenEye VR Is Finally Here… And You Can Play It Now](https://img.youtube.com/vi/z4B0Ceqrf6I/maxresdefault.jpg)](https://www.youtube.com/watch?v=z4B0Ceqrf6I)

[Watch on YouTube](https://www.youtube.com/watch?v=z4B0Ceqrf6I) - streamer playtest.

---

## Play (vr445.2 - the one to grab)

1. Download **[GEVR-Beta-vr445.2-win64.zip](https://github.com/no6969el/GEVR/releases/latest)** from [Latest](https://github.com/no6969el/GEVR/releases/latest) / [tag vr445.2](https://github.com/no6969el/GEVR/releases/tag/vr445.2) (exe, `glew32.dll`, other runtime DLLs, ROM starter, launcher, notes). **No ROM inside the zip.**
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

## What is new in vr445.2

Point release after **[vr445.1](https://github.com/no6969el/GEVR/releases/tag/vr445.1)**. Wear-PASS KEEP stack default-on:

- **[#74](https://github.com/no6969el/GEVR/issues/74)** playspace / free move / hands follow
- **[#75](https://github.com/no6969el/GEVR/issues/75)** melee swing pose
- **[#82](https://github.com/no6969el/GEVR/issues/82)** Janus spawn
- **Gun origin** — shots leave from the drawn gun
- **[#84](https://github.com/no6969el/GEVR/issues/84)** walk/run after spot + **ANIMFRAMES**
- Dam **SKYWORLD** tiled clouds (+ sky pin path)
- Rifle cadence retained from vr445.1
- Ship temp **`MODEMDROP=3`** (honest temp hide for covert modem scrap — not the [#70](https://github.com/no6969el/GEVR/issues/70) fix)

### Not in Latest (longer testing)

WATERRECT (#80), Contextual Grip / GRIPUSE (#90), and save slot 4 stay on **vr450** / **vr450.1** pre-release only — decided to test those longer before pushing to Latest.

### HOLD / still cooking

- Frigate **FRIGMUTE** / **DOORROOM** / aperture asym ([#79](https://github.com/no6969el/GEVR/issues/79))
- Prop-on-prop / Dam blue (#70) beyond the temp modem hide
- Grip **pickup** / mines / modems

---

## What is new in vr445.1

From the [vr445.1 RELEASE-NOTES](https://github.com/no6969el/GEVR/releases/tag/vr445.1). Point footnote on **vr445**. Still carry-forward under **vr445.2**.

### Gunfire fixed ([#84](https://github.com/no6969el/GEVR/issues/84))

On PC, rifle guards were using pistol lean / single-shot cadence because equipped weapon props were misread on 64-bit. They now use the correct rifle fire tables and cadence (auto/burst where intended).

### Known / in progress on this tag ([#82](https://github.com/no6969el/GEVR/issues/82) Statue Janus)

On **vr445.1**, Janus meet/scene was still open. **vr445.2** later KEEP’d Janus spawn — play Latest for that.

Everything else on this tag is still **vr445**.

## What is new in vr445

From the [vr445 RELEASE-NOTES](https://github.com/no6969el/GEVR/releases/tag/vr445). Small update on **vr444.1**. Still the base of **vr445.1** / **vr445.2**.

### 1) ADS walk + crouch

While aiming (grip): left stick walks forward/back (no duck); right stick down/up ducks/stands.

### 2) Dual-wield fire default ON

Left trigger fires the left gun, right fires the right.

### 3) Hertz follow hardened

The game detects your headset refresh (72 / 80 / 90 / 120...) and matches it. No manual FPS pin for normal play. Monitor stays live while VR runs.

### 4) Cloud stay-put (SKYINF)

On cloudy maps, sky holds in the world instead of dragging with the visor.

### 5) Mine / black flicker quieted (temporary)

Remote / prox / timed mines stuck on a wall or floor (**including Facility**) no longer black-flicker. Same temporary hide as the covert modem: drop the scrap (no modem) so the flash stops and people can play. Props still pass through other props, and that overlap is what starts the flicker. The real fix is props that know about each other and sit on each other ([issue #55](https://github.com/no6969el/GEVR/issues/55)).

### Still in from vr444 / vr444.1

- Stuck covert-modem scrap quieter; throwables in hand; **A** / left **X** weapon cycle; smarter hand cubes
- Physical walk/strafe moves **you**; guns stay with your hands
- **VR Settings** on the intro hub (**look right**); in-app **Update**
- Frigate hostage / corpse path keepers from vr444.1
- Open play space / picture KEEP / BYO-ROM / recenter both sticks

### Still open / cooking

- Frigate sea full-bleed / world-stable water
- Props still pass through other props. The no-modem scrap hide only keeps the black flicker quiet. Next: props collide and rest on each other ([issue #55](https://github.com/no6969el/GEVR/issues/55))
- Dam blue / dish-on-glass ([#70](https://github.com/no6969el/GEVR/issues/70)); weapon wheel; two-hand snap

Full notes: RELEASE-NOTES.txt in the zip / [tag](https://github.com/no6969el/GEVR/releases/tag/vr445).


## What's cooking (later update)

Soft list only. Matches the tag's **Still rough / coming soon**. Do not treat these as shipped.

- Frigate water RECT / WATERRECT ([#80](https://github.com/no6969el/GEVR/issues/80)) — longer testing; on vr450 / vr450.1 pre-release only
- Contextual Grip / GRIPUSE ([#90](https://github.com/no6969el/GEVR/issues/90)) — further testing
- Save slot 4 seed — longer testing
- Props that collide and rest on each other (black flicker is only quieted by the temporary no-modem hide, [issue #55](https://github.com/no6969el/GEVR/issues/55))
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

**Older tags (history only):** **vr434** was pulled (ROM images baked into `goldeneye.exe`). **vr445** / **vr443** / **vr442** / **vr441** / **vr440** tag pages stay; their **zips were stripped** where we pulled them. Do not hunt an old zip. Play [vr445.2](https://github.com/no6969el/GEVR/releases/latest).

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

We would rather tell you than surprise you. These are **vr445.2** today.

- **Frigate water / horizon** ([#80](https://github.com/no6969el/GEVR/issues/80)) — open on Latest; RECT only on vr450 / vr450.1 pre-release.
- **Black flicker** on stuck mines / Facility (same family as covert-modem scrap) is **quiet for now**. The no-modem hide lets people play. Props still go through other props; that overlap is the cause. Next is props that collide and rest on each other ([issue #55](https://github.com/no6969el/GEVR/issues/55)).
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

**Now - enjoy the Beta (vr445.2)**
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

Credits: [CREDITS.md](CREDITS.md). Boundaries: [PRIOR-ART.md](PRIOR-ART.md), [LICENSE](LICENSE). Other product projects that reuse GEVR work (name, docs, tools, playbook): [docs/OTHER-PROJECTS.md](docs/OTHER-PROJECTS.md). We do not claim Nintendo's game data, Rare's assets, or third-party engines we did not write.

Attribution: **BarZ / [@no6969el](https://github.com/no6969el)**. Star and follow if you want the next cut.

---

## Docs (secondary)

Deep technical trail: [`docs/00-START-HERE.md`](docs/00-START-HERE.md)  
Controls: [`docs/CONTROLS.md`](docs/CONTROLS.md)  
Beta snapshot: [`docs/BETA.md`](docs/BETA.md) · [`docs/FEATURES-CURRENT.md`](docs/FEATURES-CURRENT.md)  
Other projects using GEVR: [`docs/OTHER-PROJECTS.md`](docs/OTHER-PROJECTS.md)  
Coming soon / release policy: [`docs/COMING-SOON.md`](docs/COMING-SOON.md) · [`docs/RELEASE-POLICY.md`](docs/RELEASE-POLICY.md)  
Pack / smoke: [`packaging/README.md`](packaging/README.md) · ship boot allowlist: [`docs/ship-feature-checklist.md`](docs/ship-feature-checklist.md)

---

Jump in and enjoy finally being Bond in GoldenEye VR.
