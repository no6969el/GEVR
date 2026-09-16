<p align="center">
  <img src="GEVR-box-cover.png" alt="GoldenEye 007 VR - GEVR box art" width="480" />
</p>

# GEVR

**GoldenEye. Native. In VR. Bring your own ROM.**

The N64 classic you can finally *stand inside*. Not an emulator overlay. Not a flat game with a headset stuck on. GEVR is a from-source PC port of *GoldenEye 007* for real OpenXR. You supply a **USA GoldenEye ROM you legally own**. We never ship the cart.

**Play this cut:** [**GEVR Beta vr439**](https://github.com/no6969el/GEVR/releases/tag/vr439) (`GEVR-Beta-vr439-win64.zip`). Same file via [Releases/latest](https://github.com/no6969el/GEVR/releases/latest). It is the only tag with a zip. Download it, unzip, play.

Star the repo if this brings you back. Watch -> Releases if you want a ping when the next cut ships.

[Releases](https://github.com/no6969el/GEVR/releases) · [Beta notes](docs/BETA.md) · [Controls](docs/CONTROLS.md) · [Roadmap](docs/ROADMAP.md) · [Features](FEATURES.md) · [Credits](CREDITS.md) · [Contributing](CONTRIBUTING.md)

---

## Play (vr439)

1. Download **`GEVR-Beta-vr439-win64.zip`** from the **[vr439](https://github.com/no6969el/GEVR/releases/tag/vr439)** page (or [latest](https://github.com/no6969el/GEVR/releases/latest)). **No ROM in the zip.**
2. Unzip anywhere. Leave the files together.
3. Pick a launcher:
   - **Headset:** `Start-GEVR.bat` (KEEP picture: XR stereo source, SrcFbo, SS3, skymesh / skyscissor, playspace, recenter chord, MSGSCALE 434).
   - **Monitor / no headset:** `Play-on-monitor.bat` (flat; `GE_VR_XR=0` / `GETV_STEREO=0`).
4. Point it at your **USA GoldenEye `.z64`** when asked.
5. In VR, recenter with **both thumbstick clicks**. Enjoy.

Please use those bats. They lock in the settings this cut was worn with. Do not double-click `goldeneye.exe`.

### New here

The first launch waits once while images prepare into `%LOCALAPPDATA%\GEVR\cache`. Then you play.

### Returning (older Beta)

Keep the same `.z64`. Each cut carries a **ship stamp**, so the first launch after an update rebuilds that cache once. You do not wipe anything by hand for a normal update.

Troubleshooting only: if the picture still looks wrong after that, delete `%LOCALAPPDATA%\GEVR\cache` and run the bat again.

---

## Older tags (history, not play)

[vr420](https://github.com/no6969el/GEVR/releases/tag/vr420), [vr434](https://github.com/no6969el/GEVR/releases/tag/vr434), and [vr438](https://github.com/no6969el/GEVR/releases/tag/vr438) stay up as history. Their zip assets were removed. Play **[vr439](https://github.com/no6969el/GEVR/releases/tag/vr439)**.

- **vr434** was pulled. ROM images were baked into `goldeneye.exe`.
- **vr438** had the ROM starter, but the VR boot was stripped. It looked like an old build. Do not use it.
- **vr439** restores the vr434 KEEP picture on BYO-ROM. That is why this is the cut.

---

## What we tested

These paths are what this Beta was built and worn on:

| Path | Notes |
|------|--------|
| **Pimax Crystal Super + SteamVR OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR) (sboys3) | Primary wear path. We do not maintain that driver. We do support this experience. |
| **Native PimaxXR** | Verified attach / play |
| **Meta Quest 3 + Virtual Desktop OpenXR** | Verified attach / play |

**Refresh rates:** 72 Hz, 80 Hz, and **90 Hz** should work. Headset default is **90**. Anything **over 90** (120 / 144 and friends) is still beta-test territory. Try it, and [file an Issue](https://github.com/no6969el/GEVR/issues/new/choose) if something feels off.

When you report a bug or crash, please include: **headset**, **OpenXR runtime**, **SteamVR on/off**, **HMD vs monitor**, and **which bat** (`Start-GEVR.bat` or `Play-on-monitor.bat`). Do not upload your ROM.

---

## Known quirks (honest Beta)

We would rather tell you than surprise you:

- Expect occasional **crashes**. That is why it is Beta.
- Mid-range **crates / props on Dam** can still pop in and out.
- **Dam water** can look murky.
- **Glass bullet holes** can still show in one eye in places.

Still worth playing. Facility at 6DOF is the whole point.

**Multiplayer:** local split-screen still works on a monitor. A **LAN / same-network add-on** is later. Online play is later than that. We are calling it an **add-on**, not a mod.

---

## Why this exists

GoldenEye is one of the most-wanted "I wish I could stand inside it" games on Earth. GEVR is a fan port for that feeling:

- **Native / from-source** so VR can be real stereo, not a stretch
- **OpenXR** so Crystal, Quest via PC, and SteamVR-class headsets can attach
- **Your ROM** so legal ownership stays with you
- **Feel first** - 6DOF, aiming, presence. Then polish. Then extras.

More of that pitch: [FEATURES.md](FEATURES.md). Who we thank: [CREDITS.md](CREDITS.md). Boundaries: [PRIOR-ART.md](PRIOR-ART.md), [LICENSE](LICENSE). We do not claim Nintendo's game data, Rare's assets, or third-party engines we did not write.

---

## Roadmap (honest, not a calendar)

**Now:** solo VR, monitor fallback, local split-screen on a couch.

**Next:** fewer crashes, those Dam / glass quirks, comfort for long sits.

**Later:** LAN add-on, then online, then extra modes once the base stays up.

Fuller list: [docs/ROADMAP.md](docs/ROADMAP.md).

---

## Player docs

- [Start here](docs/00-START-HERE.md) - short door for players and testers
- [Beta testing](docs/BETA.md)
- [Controls](docs/CONTROLS.md)
- [Roadmap](docs/ROADMAP.md)
- [Features](FEATURES.md)
- [Coming soon](docs/COMING-SOON.md)
- [Credits](CREDITS.md)
- [Contributing](CONTRIBUTING.md)
- [Pack / smoke (vr439)](packaging/README.md)

Play zip: [vr439](https://github.com/no6969el/GEVR/releases/tag/vr439) · [latest](https://github.com/no6969el/GEVR/releases/latest)

Jump in and enjoy finally being Bond in GoldenEye VR.
