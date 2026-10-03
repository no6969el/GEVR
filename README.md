<p align="center">
  <img src="GEVR-box-cover.png" alt="GoldenEye 007 VR - GEVR box art" width="480" />
</p>

# GEVR

**GoldenEye. Native. In VR. Bring your own ROM.**

> **Play now:** GitHub **Latest** is **[vr452.4](https://github.com/no6969el/GEVR/releases/tag/vr452.4)** — zip [`GEVR-Beta-vr452.4-win64.zip`](https://github.com/no6969el/GEVR/releases/download/vr452.4/GEVR-Beta-vr452.4-win64.zip). Or hit **Update** in GevrRomStarter.

> This public repo is for **player docs**, **Issues**, and **Beta zip Releases**. New product code is developed privately. See [`docs/SOURCE.md`](docs/SOURCE.md).

---

The N64 classic you can finally *stand inside* — not an emulator overlay, not a flat game with a headset stuck on. GEVR is a from-source PC port of *GoldenEye 007* built for real OpenXR VR. You supply a **USA GoldenEye ROM you legally own**; the starter prepares a local cache and **`Start-GEVR.bat`** launches through **GevrRomStarter** (not bare `goldeneye.exe`).

| | |
|---|---|
| **Download** | [**GEVR-Beta-vr452.4-win64.zip**](https://github.com/no6969el/GEVR/releases/download/vr452.4/GEVR-Beta-vr452.4-win64.zip) |
| **Release page** | [vr452.4](https://github.com/no6969el/GEVR/releases/tag/vr452.4) |
| **Latest** | [Releases / Latest](https://github.com/no6969el/GEVR/releases/latest) |
| **Controls** | [docs/CONTROLS.md](docs/CONTROLS.md) |
| **Report a bug** | [New Issue](https://github.com/no6969el/GEVR/issues/new/choose) |
| **Discord** | [discord.gg/flat2vr](https://discord.gg/flat2vr) |
| **Features** | [FEATURES.md](FEATURES.md) |
| **Support** | [Patreon](https://www.patreon.com/cw/GEVR) |

Star the repo and [follow @no6969el](https://github.com/no6969el). **Watch → Releases** for ship pings.

---

## Install (vr452.4)

1. Download **[GEVR-Beta-vr452.4-win64.zip](https://github.com/no6969el/GEVR/releases/download/vr452.4/GEVR-Beta-vr452.4-win64.zip)** from [Latest](https://github.com/no6969el/GEVR/releases/latest) / [tag vr452.4](https://github.com/no6969el/GEVR/releases/tag/vr452.4). **No ROM inside the zip.**
2. Unzip anywhere.
3. Run **`Start-GEVR.bat`** — it sets VR boot knobs and starts **GevrRomStarter.exe**.
4. Point at your **USA GoldenEye `.z64`** when asked. Images extract to `%LOCALAPPDATA%\GEVR\cache\<ROM-hash>\`. Each Beta tag bumps a **ship stamp** so the first launch after an update rebuilds that cache once from your ROM.
5. Put the headset on. Recenter with **both thumbstick clicks**.
6. On the intro hub, **look right** for **GEVR Settings** and tune comfort. Enjoy.

**Please use the bat** — it locks in the good VR settings and runs the ROM starter we ship for this cut (not bare `goldeneye.exe`).

Default is **VR**. Flat / monitor: **`Play-on-monitor.bat`** — same game, no headset.

**New install:** first launch waits once while images prepare, then you play. Saves start empty.

**After an update:** keep the same USA `.z64`. The ship stamp forces **one** automatic re-prepare. **Saves and GEVR Settings are kept** under `%LOCALAPPDATA%\GEVR`. Or use **Update** in GevrRomStarter. For picture problems, try **`Clear-GEVR-cache.bat`** (type **YES**) before deleting the whole `%LOCALAPPDATA%\GEVR` folder.

---

## Controls (right after install)

**How to control GEVR in VR** — walkthrough on YouTube: **[watch here](https://www.youtube.com/watch?v=Jst5srE6Iwc)**

[![How to control GEVR in VR](https://img.youtube.com/vi/Jst5srE6Iwc/maxresdefault.jpg)](https://www.youtube.com/watch?v=Jst5srE6Iwc)

Quest / Meta Touch, Valve Index, and Oculus-style OpenXR binds (same actions):

| Input | What it does |
|---|---|
| **Left stick** | Walk |
| **Right stick** | Turn (Smooth or Snap — **GEVR Settings**, look right on the intro hub) |
| **Both thumbstick clicks** | Recenter playspace |
| **Trigger** | Fire (left fires left gun, right fires right when dual-wielding) |
| **Squeeze / grip** | **AIM / ADS** (aim mark on the gun ray) |
| **Squeeze near a door** | Open / close |
| **B** (right face; Index **B**) | USE / reload |
| **A** (right face; Index **A**) | Next weapon |
| **X** (left Quest/Oculus) | Previous weapon |
| **Menu / system** | Pause (headset). **Tab** on keyboard / monitor |
| **Head / room-scale** | Look around; physically walk to move in Bond-world |

**Quick examples:** (1) Recenter — both sticks in at once. (2) ADS walk — squeeze to aim, left stick walks, right stick ducks/stands. (3) Dual-wield — each trigger fires its hand. (4) Door — squeeze near the handle. (5) Pick mines back up when you can.

Full detail: [`docs/CONTROLS.md`](docs/CONTROLS.md).

---

## vr452.4 features (how to use them)

### HD textures

**GEVR does not ship the pack.** Download the community **GLideN64 PNG** zip (**not** the `.hts` file) from the [GoldenEye-007-HD releases](https://github.com/GhostlyDark/GoldenEye-007-HD/releases) or the [GE007 HD texture pack page](https://evilgames.eu/texture-packs/ge007-hd.htm). Extract it so the **`GOLDENEYE`** folders sit inside an **`hdtextures`** folder next to `goldeneye.exe`. Do not rename files. In **GEVR Settings**, turn **HD textures** on, **Apply**, then play on the **next boot**.

| Feature | How |
|---|---|
| **Settings that save** | **GEVR Settings** (intro hub, look right) — separate **VR**, **XR**, and **flat** profiles; **Apply** restarts into what you picked. |
| **Monitor output** | While in VR or XR, choose **both eyes**, **left**, **right**, or **off** for the desktop picture (saved per VR/XR profile). Greyed out in flat. |
| **Rockets** | Rocket launcher stays on the gun; flat crosshair on the rocket path. |

Older comfort and combat passes still in this line: playspace / hands ([#74](https://github.com/no6969el/GEVR/issues/74)), melee swing ([#75](https://github.com/no6969el/GEVR/issues/75)), Janus spawn ([#82](https://github.com/no6969el/GEVR/issues/82)), Dam sky / grip doors ([#80](https://github.com/no6969el/GEVR/issues/80), [#90](https://github.com/no6969el/GEVR/issues/90)), cuff / dual-wield / watch magnet, and more — see [FEATURES.md](FEATURES.md).

---

## What we tested

| Path | Notes |
|------|--------|
| **Pimax Crystal Super + SteamVR OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR) (sboys3) | Primary wear path — we do not maintain that driver; we *do* support this experience |
| **Native PimaxXR** | Verified attach / play |
| **Meta Quest 3 + Virtual Desktop OpenXR (VDXR)** | Verified attach / play |
| **RTX 5060 laptop + Quest 3 + Virtual Desktop VDXR** | BarZ wear **vr441**, 2026-09-17; one data point, not a minimum spec |

**Half-speed / mushy VR?** Turn **SteamVR Motion Smoothing Off** and **Virtual Desktop Space Warp Off**. Details: [`docs/BETA.md`](docs/BETA.md#half-speed--mushy-vr).

When you report a bug or crash, please include: **headset**, **OpenXR runtime**, **SteamVR on/off**, **HMD vs monitor**, whether you used **`Start-GEVR.bat`**, your **`gevr-*-boot.cmd`** filename from the zip folder, any log next to the zip or in the console, and any **`gevr-fault-*.txt`** beside the exe. Do **not** upload your ROM.

---

## Discord (help + fan chat)

**[Join the GEVR Discord](https://discord.gg/flat2vr)** for port help and GoldenEye fan chat. BYO ROM — do not upload your ROM (setup details and logs only). GitHub Issues stay great for tracked bugs.

---

## Known quirks (honest Beta)

- **Half-speed / mushy VR:** SteamVR **Motion Smoothing Off**; VD **Space Warp Off** ([BETA.md](docs/BETA.md#half-speed--mushy-vr)).
- **Frigate door / aperture** ([#79](https://github.com/no6969el/GEVR/issues/79)) and other level stoppers — ongoing focus.
- **Prop-on-prop / Dam blue** ([#70](https://github.com/no6969el/GEVR/issues/70)) and remaining Dam / Frigate water look issues.
- **Melee / fist** is in (swing-based) but not finely tuned ([#75](https://github.com/no6969el/GEVR/issues/75)).
- **Big explosions** can still hard-crash — grab `gevr-fault-*.txt` beside the exe before relaunch.
- Empty hand draws a **cube** (hides when that hand holds a weapon).
- Expect occasional **crashes** while we keep polishing.

More tester notes: [BETA.md](docs/BETA.md) · [CONTROLS.md](docs/CONTROLS.md).

---

## Why this exists

- **Native / from-source** — full ownership of the game loop for proper VR
- **OpenXR** — Crystal, Quest via PC, SteamVR-class HMDs
- **Your ROM** — legal ownership stays with you
- **Feel first** — 6DOF, aiming, presence; then polish; then extras

More pitch: [FEATURES.md](FEATURES.md). Credits: [CREDITS.md](CREDITS.md). Boundaries: [PRIOR-ART.md](PRIOR-ART.md), [LICENSE](LICENSE). Other projects using GEVR: [docs/OTHER-PROJECTS.md](docs/OTHER-PROJECTS.md).

---

## Docs (player)

- Start: [`docs/00-START-HERE.md`](docs/00-START-HERE.md)
- Controls: [`docs/CONTROLS.md`](docs/CONTROLS.md)
- Beta snapshot: [`docs/BETA.md`](docs/BETA.md) · [`docs/FEATURES-CURRENT.md`](docs/FEATURES-CURRENT.md)
- Other projects: [`docs/OTHER-PROJECTS.md`](docs/OTHER-PROJECTS.md)

Jump in and enjoy finally being Bond in GoldenEye VR.
