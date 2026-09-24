# GEVR - living status
**Last updated:** 2026-09-24
**One-liner:** From-source *GoldenEye 007* on PC for real OpenXR VR. Bring your own USA ROM. Stand inside it.
**Download (latest):** https://github.com/no6969el/GEVR/releases/latest → **[vr445.2](https://github.com/no6969el/GEVR/releases/tag/vr445.2)**
**Repo / README:** https://github.com/no6969el/GEVR — controller layout sits **near the top** of the README (after Latest blurb, before Streamer playtests).
**How to play:** unzip → drop in your USA `.z64` → run `Start-GEVR.bat` → recenter with both thumbstick clicks

> **Footnote:** Decided to test some other features longer before pushing — WATERRECT (#80), GRIPUSE (#90), and save slot 4 stay on the **vr450** / **vr450.1** pre-release tags, **not** Latest.

---
## Controller layout (vr445.2)

Quest / Index / Oculus Touch (same OpenXR actions):

| Input | What it does |
|---|---|
| **Left stick** | Walk |
| **Right stick** | Turn (Smooth / Snap in VR Settings) |
| **Both stick clicks** | Recenter |
| **Trigger** | Fire (each hand its own gun when dual-wielding) |
| **Squeeze / grip** | **AIM / ADS** |
| **A** (right face, Quest/Oculus; Index A) | USE / reload (view-cone) |
| **X** (left, Quest/Oculus) | Previous weapon (where WEAPAX is on) |
| **Head / 6DOF** | Look; walk your room to move in-world |

---
## Current cut
**vr445.2** — GitHub **Latest**. Hit **Update** in GevrRomStarter or grab `GEVR-Beta-vr445.2-win64.zip`.

**vr450** / **vr450.1** stay published as **pre-release** (tags + zips kept). They are **not** Latest.

### What’s in Latest (KEEP, default-on at bake)
- [#74](https://github.com/no6969el/GEVR/issues/74) playspace / free move / hands follow
- [#75](https://github.com/no6969el/GEVR/issues/75) melee swing pose
- [#82](https://github.com/no6969el/GEVR/issues/82) Janus spawn
- Gun origin · [#84](https://github.com/no6969el/GEVR/issues/84) walk/run + ANIMFRAMES · Dam SKYWORLD · rifle cadence · temp MODEMDROP=3

### Not in Latest (on vr450 / vr450.1 pre-release only)
- [#80](https://github.com/no6969el/GEVR/issues/80) Frigate water RECT (`GETV_VR_SKYWATERRECT`) — wear PASS on 450 line; **issue reopened** until it ships in a Latest cut again
- Save slot 4 007+cheats seed
- [#90](https://github.com/no6969el/GEVR/issues/90) Contextual Grip / GRIPUSE — further testing; was pulled from 450.1

### Still open / cooking
- Frigate door / aperture asym ([#79](https://github.com/no6969el/GEVR/issues/79))
- Dam blue / dish-on-glass ([#70](https://github.com/no6969el/GEVR/issues/70))
- Grip pickup / mines / modem · two-hand snap · weapon wheel HUD
- High Hz polish ([#49](https://github.com/no6969el/GEVR/issues/49)) · black flicker ([#55](https://github.com/no6969el/GEVR/issues/55)) · ammo HUD picture ([#34](https://github.com/no6969el/GEVR/issues/34))

### Still from earlier cuts
- ADS walk/crouch, dual-wield, Hertz follow, monitor in VR, mine flicker quiet (temp)
- BYO-ROM, file-backed images. No ROM in the zip
---
## What's coming (after this zip)
No promise on the next tag. Play **vr445.2**. **Watch** the GitHub repo (Watch -> Releases). Star it if you want the next Bond drop without hunting.

Keep shooting. File Issues. Watch GitHub.
---
## What's new since last edit
- **2026-09-24** - **Latest = vr445.2.** Front docs sync. Footnote: longer testing before pushing WATERRECT / GRIPUSE / slot4. vr450 + vr450.1 demoted to pre-release (tags/zips kept). [#80](https://github.com/no6969el/GEVR/issues/80) reopened.
- **2026-09-24** - vr450.1 / vr450 published then rolled off Latest (GRIPUSE off in 450.1; RECT + slot4 on that line).
- **2026-09-23** - **vr445.2** shipped KEEP stack (#74/#75/#82/gun origin/#84 walk-run+ANIMFRAMES/SKYWORLD).
- **2026-09-23** - **vr445.1** gunfire #84 cadence.
- **2026-09-22** - **vr445** (ADS crouch/walk, dualfire ON, Hertz follow, monitor live, SKYINF, mine flicker incl. Facility).
- **2026-09-16** - **vr441** then superseded; **vr440** picture KEEP / BYO-ROM era; **vr434** pulled (ROM images baked into `goldeneye.exe`).
- **2026-09-15** - vr420 first public Beta zip
---
## Tested on
- Pimax Crystal Super + SteamVR OpenXR via CustomHeadsetOpenVR (primary)
- Native PimaxXR
- Meta Quest 3 + Virtual Desktop OpenXR (VDXR)
- **Laptop check:** RTX 5060 laptop + Quest 3 + Virtual Desktop VDXR ran well (2026-09-17). One data point, not a minimum spec.
- **Hz:** game follows headset refresh (72 / 80 / 90 / 120 as reported). High Hz still Beta-test territory (#49).
---
## Known quirks (honest)
- Frigate water / horizon (#80) — **open again** on Latest (fix only on 450/450.1 pre-release)
- Frigate door / aperture SFX / asym still open (#79)
- Grip pickup / mines / modem **not** in this cut
- Dam mid-range crates/props can still pop in/out
- Dam water can look flat/murky
- Glass bullet holes can still be one-eye in places
- Dam blue flicker / dish-on-glass (#70) — MODEMDROP=3 is a temp hide, not the fix
- Menu face-button confirm is still rough in places; watch highlight can miss an eye
- Ammo HUD picture can look stretched or fat in VR (render, not clip)
- Black flicker in VR (Facility gas tanks; Bunker after Surface) - not a shipped fix
- Big explosions can still hard-crash (fault file helps)
- Expect occasional crashes while we keep optimizing
- Still worth playing - that Bond-in-the-headset feeling
---
## Multiplayer
- **Now (flat / monitor):** classic local split-screen still there
- **Later:** LAN / local-network add-on, then true online (not the next zip)
---
## How to report
GitHub Issues: https://github.com/no6969el/GEVR/issues/new/choose
Include: **headset**, **OpenXR runtime**, **SteamVR on/off**, **HMD vs monitor**, whether you used **`Start-GEVR.bat`**, and the **`gevr-*-boot.cmd`** filename in the unzip (fastest way to spot a stale zip). **Do not upload your ROM.**

**Discord (help + fan chat):** https://discord.gg/flat2vr — port help and GoldenEye fan chat with other players. BYO ROM / do not upload your ROM (setup details and logs only).
---
## Roadmap (loose)
- Ship WATERRECT (#80) into a future Latest when ready; #90 GRIPUSE when further testing clears; #79 Frigate asym
- #70 prop-on-prop (not MODEMDROP)
- Fewer freezes / softer landings
- Clearer first-run (ROM drop-in, saves that survive updates)
- Dam crates / water / glass
- More HUD / comfort polish
- Then the multiplayer path above, later
I'll keep **this post** updated instead of a new thread every drop. Star the repo / Watch Releases if you want the next ping. Also at
https://www.patreon.com/cw/GEVR

Jump in and enjoy finally being Bond in GoldenEye VR.
