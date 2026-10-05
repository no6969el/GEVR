# GEVR - living status

Players: use the [README](../README.md#vr-actions) and [Controls](CONTROLS.md). This note is an old status log.

**Latest:** [vr454](https://github.com/no6969el/GEVR/releases/tag/vr454) — `GEVR-Beta-vr454-win64.zip`. You bring a USA GoldenEye ROM. The zip has no ROM and no HD texture pack.

**How to play:** unzip, point `Start-GEVR.bat` at your USA `.z64`, recenter with both thumbstick clicks.

**Buttons:** **Right A** is the next weapon on the right hand. **Left X** is the previous weapon on the left hand. **B** reloads any gun the normal way. **Y** opens the watch. The full list is on the [README](../README.md#vr454).

---
## Older status (kept for the record)

**Download (latest at the time of the notes below):** older than vr454. Do not treat the rest of this file as the current button list.

### What’s in Latest (KEEP, default-on at bake)
- [#74](https://github.com/no6969el/GEVR/issues/74) playspace / free move / hands follow
- [#75](https://github.com/no6969el/GEVR/issues/75) melee swing pose
- [#82](https://github.com/no6969el/GEVR/issues/82) Janus spawn
- Gun origin · [#84](https://github.com/no6969el/GEVR/issues/84) walk/run + ANIMFRAMES · Dam SKYWORLD · rifle cadence · temp MODEMDROP=3

### Still from earlier cuts
- ADS walk/crouch, dual-wield, Hertz follow, monitor in VR, mine flicker quiet (temp)
- BYO-ROM, file-backed images. No ROM in the zip
---
Keep shooting. File Issues. Watch GitHub.
---
## What's new since last edit
- **2026-09-24** - Docs warn: SteamVR Motion Smoothing / VD Space Warp Off (half-rate feel). Zip untouched.
- **2026-09-24** - **Latest = vr445.2.** Front docs sync. vr450 + vr450.1 stay pre-release (tags/zips kept).
- **2026-09-24** - vr450.1 / vr450 published then rolled off Latest.
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
- **Half-speed / mushy VR:** SteamVR **Motion Smoothing Off**; VD **Space Warp Off** (not a GEVR toggle; halves app rate)
- Dam mid-range crates/props can still pop in/out
- Glass bullet holes can still be one-eye in places
- Dam blue flicker (#70) — MODEMDROP=3 hides the covert-modem scrap
- Menu face-button confirm is still rough in places; watch highlight can miss an eye
- Ammo HUD picture can look stretched or fat in VR (render, not clip)
- Black flicker in VR (Facility gas tanks; Bunker after Surface) - not a shipped fix
- Big explosions can still hard-crash (fault file helps)
- Expect occasional crashes while we keep optimizing
- Still worth playing - that Bond-in-the-headset feeling
---
## Multiplayer
- **Flat / monitor:** classic local split-screen is in this cut
---
## How to report
GitHub Issues: https://github.com/no6969el/GEVR/issues/new/choose
Include: **headset**, **OpenXR runtime**, **SteamVR on/off**, **HMD vs monitor**, whether you used **`Start-GEVR.bat`**, and the **`gevr-*-boot.cmd`** filename in the unzip (fastest way to spot a stale zip). **Do not upload your ROM.**

**Discord (help + fan chat):** https://discord.gg/flat2vr — port help and GoldenEye fan chat with other players. BYO ROM / do not upload your ROM (setup details and logs only).
---
I'll keep **this post** updated instead of a new thread every drop. Star the repo / Watch Releases if you want a ping. Also at
https://www.patreon.com/cw/GEVR

Jump in and enjoy finally being Bond in GoldenEye VR.
