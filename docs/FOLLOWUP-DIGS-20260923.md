# Follow-up pack — open and pending (2026-09-23)

Information only. No APPLY, no zip, no chair sit. Read while BarZ is out.

Sources: GitHub issues on `no6969el/GEVR`, and public `no6969el/goldeneye-native` (last push **2026-09-20**). Workshop C after that date is not on the public remote. Harvest files named below live on SimRig under `F:\Projects\GEVR\_side-mission-staging\harvest\` unless a path is given.

## When you get back

1. **[#82 Statue Janus](https://github.com/no6969el/GEVR/issues/82)** — still open. LonnyEnds confirmed it on v444 (2026-09-23). Your reply the same day: a fix is in the works for **445.2**. There is **no public dig write-up** for the meet/scene. Next step is the SimRig sheet, not another cloud dig.
2. **[#84 gunfire](https://github.com/no6969el/GEVR/issues/84)** — rifle **animation / cadence shipped** in vr445.1 (you and thet0x1n agree the firing set is right). thet0x1n (2026-09-23): enemies **still walk instead of run** after they spot you. Walk/run is the leftover. Issue left open on purpose.
3. **[#79 Frigate doors](https://github.com/no6969el/GEVR/issues/79)** — dig landed, no fix. Door **mesh** is dropped on the shared prop admit / room-pass draw. Collision, bullet hits, and open still work. Frigate makes it obvious: all single-player doors are `CULL_BEHIND`, DoorScale ~0.75. Same class as older Letter N residue. Seen on vr443.1; not caused by the #78 hostage fix. Harvest: `DIG-FRIGATE-INVIS-DOORS-20260921.md`. Chair / APPLY waiting on you.
4. **[#75 melee swing](https://github.com/no6969el/GEVR/issues/75)** — idle stand next to a guard **PASS** with `GETV_VR_SWINGHIT=1`. Intentional swings **PASS**. Walking up still lands **one free smack**. Overnight note (2026-09-20) called the next cut APPLY-READY: recentre-relative joint speed counts a step as a swing. Keep `HANDMELEE=1`. Do not revive `HANDSOLID`.
5. **[#74 guns in the playspace](https://github.com/no6969el/GEVR/issues/74)** — public redigs still record **chair FAIL** (HandWorld-only, then HandPoseRel/HeadPosRel: walk amplifies, lean sends guns and cube at the floor). You later called a chair perfect and a baseline sheet was written. Before any ship, confirm that later sit is the one that stuck. Do not restore `HEAD_TRANSLATE=1` as this fix.

## Digs already on file (public `goldeneye-native` `getv/patches/`)

Each of these is DIG ONLY. None of them landed C on the public tree. “Not APPLY READY” means the write-up says do not ship from that page.

| Ticket | Write-up | What it concluded | Next |
|---|---|---|---|
| [#29](https://github.com/no6969el/GEVR/issues/29) crates pop | `dam-crates-pop-dig/RESULT.md` | Not far-guard VISFAR. Dam fog admit + fade. Chair keep already: `PROPFOGALPHA=0` + `OCCLSKIP=1`. Leftover is fog colour, not another skip. | Sit the fog-colour leftover, or leave it. |
| [#30](https://github.com/no6969el/GEVR/issues/30) Dam water | `dam-water-dig/RESULT.md` | Dam `IsWater=0`. Lake is sky fill + room mesh. `WATERTILE` stays default OFF. Not #72 blue flash. | Chair `GETV_VR_WATERTILE=1` only if you want world-space tiles. |
| [#31](https://github.com/no6969el/GEVR/issues/31) glass holes one eye | `glass-bullet-holes-dig/RESULT.md` | Glass holes draw in xlu from `render_pos` that was already converted in place. `IMPACTEYE` is census only. | One Facility sit: wall vs glass, then IMPACTEYE counts, then `HITSNAP=0`. |
| [#33](https://github.com/no6969el/GEVR/issues/33) HUD depth | `hud-depth-dig/RESULT.md` | HUD is still 2D texrects. `HUDGATE` pins infinity. `HUD_DEPTH_PX` is a bad ship knob. | Chair `GETV_VR_HUD_DEPTH_M` at 2.0, then 1.0, then 0.5. Do not ship 0.2. |
| [#34](https://github.com/no6969el/GEVR/issues/34) ammo picture | `ammo-hud-picture-dig/RESULT.md` | Fat stamp = dest X aspect. Specks = RGBA32 line treated as 16-bit. Picture before any gun-side move. | You said this is **done**. Public dig is still “not applied” as of Sep 20. Attach file 10 when you have it. Do not re-open. |
| [#35](https://github.com/no6969el/GEVR/issues/35) ADS grip | `ads-grip-dig/RESULT.md` | Honey aim steals the stick, so walk-while-ADS dies. One squeeze env cannot split hands. | Needs workshop `port_input.c`. Not a bat-only fix. |
| [#36](https://github.com/no6969el/GEVR/issues/36) no-HMD stereo | `no-hmd-stereo-fallback-dig/RESULT.md` | Keep `Play-on-monitor.bat`. Do not ship in-exe stereo without an HMD. SBS MODE=1 is measure-only. | Parked. |
| [#39](https://github.com/no6969el/GEVR/issues/39) huge gun / cross-eye | `viewmodel-guneye-dig/RESULT.md` | Both eyes share one gun matrix. Units-per-metre is the wrong knob. | `GETV_VR_GUNEYE` was written default OFF for vr444 and **not chaired**. Sit B0 then PLAY0 before any zip. |
| [#42](https://github.com/no6969el/GEVR/issues/42) cinema vs VR picker | `cinema-boot-picker-dig/RESULT.md` | Cinema already exists. No in-HMD picker. | Smallest sit is existing `PLAY_SCREEN` / `AUTOSCREEN`, not a new menu. |
| [#45](https://github.com/no6969el/GEVR/issues/45) floor height | issue comment only | Recenter resets heading, not runtime floor Y. | Sketch `GETV_XR_PLAYSPACE_OFF` + `PLAYSPACE_Y_M`, default OFF. Harvest: `OVERNIGHT-DIG-45-20260920.md`. |
| [#46](https://github.com/no6969el/GEVR/issues/46) HMD vs window size | `hmd-res-split-dig/RESULT.md` | One FBO is sized from the desktop window, then SS3. | `GETV_XR_HMDSCALE` unset = 1.0. Chair scale 1, then 1.5. Not in the zip. |
| [#49](https://github.com/no6969el/GEVR/issues/49) Hertz | `hertz-49-dig/RESULT.md` | 72/80 failed because boot pinned `GETV_FPS=90` and the pace interlock refused. | **Shipped later:** vr444+ leaves `GETV_FPS` unset. Issue still open. Do not re-pin 90. |
| [#55](https://github.com/no6969el/GEVR/issues/55) black flicker | `facility-mines-flicker-dig/RESULT.md` | Facility mine-throw black is the same in-place matrix convert as Bunker. Chair **PASS** `MTXGUARD=2` on Facility (2026-09-19). Do not put `=2` on Dam. | You later called the **playing** fix the temporary **no-modem** hide (same family as covert-modem scrap), because props pass through other props. That cause is **not** what this dig concluded. Real prop-on-prop work is [#70](https://github.com/no6969el/GEVR/issues/70) EMBEDEYE below. |
| [#59](https://github.com/no6969el/GEVR/issues/59) vision shake | `vision-jitter-dig/RESULT.md` | Quest 2 + Steam Link is not a chaired path. 90 pin into a 72 Hz compositor steps the picture. ASW makes it worse. | Setup first. If it still fails on VDXR, the leftover is the SDL pacer beside `xrWaitFrame`. |
| [#60](https://github.com/no6969el/GEVR/issues/60) slowdown | `issue-60-slowdown-dig/RESULT.md` | Four stacked causes, not one shader. Setup (Steam Link / Hz / desktop present) before code. | Tester checklist is in that folder. Ties to #46 and #59. |
| [#70](https://github.com/no6969el/GEVR/issues/70) modem / prop stick | several `dam-modem-*` + `texture-spray-guard-dig/RESULT.md` | TEXGUARD/SCRAPDROP **chair FAIL**. EMBEDEYE **chair FAIL** (2026-09-21): you still saw the modem through crates/props. Dig said it embeds, not passes through; the second eye rebuilds the parent and not the child (`propobj.c:8567`). | Stays default OFF. Harvest: `RESULT-70-OPUS-EXTRA-EMBEDEYE-RANK1-20260920.md`, `APPLY-70-EMBEDEYE-20260921.md`, `CHAIR-70-EMBEDEYE1-FAIL-20260921.md`. Ship hide is `GETV_VR_MODEMDROP=3`. |
| [#72](https://github.com/no6969el/GEVR/issues/72) Dam blue | `dam-bridge-blue-flash-dig/RESULT.md` | Blue is Dam sky fill `RGB(16,48,96)`, not the modem. | Closed on the tracker. `SKYMESH=0` was the chair keep named here. Later SKYINF is a different sky job. |
| [#73](https://github.com/no6969el/GEVR/issues/73) flat aim snap | `flat-aim-snap-dig/RESULT.md` | Aim button enters Honey. Stick at rest decays the sight to center. Monitor bat does not clear VR aim knobs. | Bat pins or a look-ahead A/B. Not shipped from this page. |
| Two-hand snap | `twohand-snap-dig/RESULT.md` | Hide left cube when it is near the right gun. Snap is a second layer, default OFF. | Still cooking. Do not snap in dual-wield. |

## Filed, no public RESULT.md

| Ticket | What the issue already says | Gap |
|---|---|---|
| [#80](https://github.com/no6969el/GEVR/issues/80) Frigate water | Sky-seam class. Rank 1: described water/ground corners vs the drawn XR frustum. `SKYPIN` remeshes cloud only. Not Dam #30. | No comment, no public write-up. Separator chair still parked. |
| [#81](https://github.com/no6969el/GEVR/issues/81) hitch | Present drops under prop/modem load while Task Manager looks flat. Opt digs “landed”; measure then APPLY. `GETV_VSYNC=0` is already in vr444+ boot. | No harvest filename on the issue. FRAMESEG sit is still the measurement, and it was never worn. |
| [#61](https://github.com/no6969el/GEVR/issues/61) Reverb G2 | WMR Portal on Windows 10. | No dig. Needs the reporter’s runtime, not a code guess. |
| [#50](https://github.com/no6969el/GEVR/issues/50) Linux | Asked. Read was: a port is very hard. | Reply was drafted and not posted. |
| [#43](https://github.com/no6969el/GEVR/issues/43) / [#71](https://github.com/no6969el/GEVR/issues/71) LAN | You shelved two-headset play. Sidecar shape is right; not two-HMD ready. | Do not build. |

## Leave alone

- **[#56](https://github.com/no6969el/GEVR/issues/56) watch-hand stretch** and **[#32](https://github.com/no6969el/GEVR/issues/32) / [#58](https://github.com/no6969el/GEVR/issues/58) pause confirm.** You said not to step on these. Latest public state: hinge SLOT chairs are diagnostic only; do not ship a SLOT value. Pause A still toggles twice per stereo frame (`GETV_WATCHHL` / once-gate). No new dig this session.
- **[#57](https://github.com/no6969el/GEVR/issues/57) arm watch panel.** Dig ranks a farther billboard first (`GETV_WATCHFAR`, default OFF). Not started.
- **TEXGUARD / SCRAPDROP.** Chair failed. Do not re-sit.
- **`GETV_VR_MONFRAME`.** Chair reject. Leave off.
- **Dam `MTXGUARD=2`.** Facility/Bunker bats only.

## Already in the zip (do not re-dig)

- In-app **Update** and intro-hub **turn speed** ([#76](https://github.com/no6969el/GEVR/issues/76)) are on the vr445 front page.
- **`GETV_FPS` unset** and **`GETV_VSYNC=0`** from vr444 onward.
- **`GETV_VR_MODEMDROP=3`** quiets stuck-mine / covert-modem scrap. Temporary.
- Cloudy **SKYINF** is listed as in vr445. Wear pass before treating every map as signed off. No public SKYINF dig page.

## What this session could not open

`goldeneye-native` on GitHub does not contain the workshop bodies (`gfx_pc.c`, `stereo.c`, `gevr_xr.c`, `port_input.c`). Janus, Frigate door C, EMBEDEYE, MODEMDROP, SKYINF, FRAMESEG, and the #84 weapon-prop fix are on SimRig, not in that remote. This pack is the index. The next APPLY still starts from the harvest file named on the row.
