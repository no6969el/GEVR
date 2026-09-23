# Handover — cloud session 2026-09-23

For the main GEVR project. This session was docs and digs on the public repo only. No APPLY, no compile, no zip, no workshop push.

Cloud environment: `ea097271-af85-11f1-bf4b-42ffb4d10ea7`. This machine can see `github.com/no6969el/GEVR` only. It cannot see the SimRig workshop (`F:\Projects\GEVR\GoldenEyeVR\goldeneye-native`).

## Draft PRs (do not merge blindly)

| PR | Branch | What it is |
|---|---|---|
| [#86](https://github.com/no6969el/GEVR/pull/86) | `cursor/log-temp-prop-flicker-2e68` | Front page and release-note templates. Black flicker is a **temporary** no-modem hide. Ammo picture marked in. |
| [#87](https://github.com/no6969el/GEVR/pull/87) | `cursor/open-dig-pack-2e68` | `docs/FOLLOWUP-DIGS-20260923.md`. Index of open tickets against public `goldeneye-native` RESULT pages and GitHub comments. |
| [#88](https://github.com/no6969el/GEVR/pull/88) | `cursor/public-source-port-dig-2e68` | `docs/DIG-PUBLIC-SOURCE-PORTS-20260909.md`. Public native ports, 2026-09-09 through 2026-09-23. Plus this handover. |

Historical GitHub release bodies were not republished. Templates only.

## Owner corrections this session

- In-app **Update**, intro-hub **turn speed**, and the **ammo picture** are done. If the ammo write-up is missing from the public dig, it is “file 10” on SimRig. Do not re-open the picture.
- **[#55](https://github.com/no6969el/GEVR/issues/55) black flicker** is a temporary play fix: the same no-modem hide as covert-modem scrap (`GETV_VR_MODEMDROP=3`). People can play. The cause the owner wants fixed is props passing through other props. The real goal is props that know other props exist and rest on each other. The public Facility mine dig (`MTXGUARD=2`, Facility chair PASS 2026-09-19) is a different conclusion. Do not globalize `MTXGUARD=2` onto Dam. Dam stays Facility/Bunker bats only.
- Prop-on-prop is **[#70](https://github.com/no6969el/GEVR/issues/70) EMBEDEYE**, and that chair **FAIL**ed 2026-09-21 (modem still through crates). Dig said embed, not pass-through. Second eye rebuilds the parent, not the child (`propobj.c:8567`). Knobs stay default off. TEXGUARD / SCRAPDROP stay failed. Do not re-sit them.
- **[#82](https://github.com/no6969el/GEVR/issues/82) Statue Janus:** the owner asked whether a dig is possible. From this cloud, no. Public `goldeneye-native` has no meet/scene code and no dig page. The dig belongs on the SimRig workshop. Do not mark #82 undiggable. Owner comment the same day: a fix is aimed at 445.2. LonnyEnds confirmed the bug on v444.
- **Water / sky.** Flat water already looks right. In VR, turning the sea on looks right and then **yaws with the head**. It needs to stay put. That is the SKYINF class of bug on the water fan, not a texture bug. SKYINF already pins cloudy sky and leaves the sea (issue [#80](https://github.com/no6969el/GEVR/issues/80): SKYPIN remeshes cloud only). On a monitor the only yaw is Bond’s, so the fan stays stuck to the deck. The headset adds a yaw the level does not use.

## Public from-source dig — what the main project can use

Window: 2026-09-09 to 2026-09-23. Class: native decomp ports. `n64decomp/007` last push 2026-08-17. Almost everything useful is `jkdansereau/goldeneye-pc-port`. Xbox recomp forks were set aside. Sightline, goldenpad, and GoldenEye 007 Plus moved and did not ship an engine fix to take. Nothing was copied.

**Do not take for the sea**

- D227 (`741dfe7`, 2026-09-12). Extra `* 32` on sky coords that are already S10.5. Fixes over-tiling and fast cloud scroll. It does not lock the sea to the world. Only look if clouds are still over-tiled or scrolling too fast.
- D245 (`4806799`, reopened the same day by `53c9a87`). Frigate water texture shift. Live play still swapped patterns as the view turned. A later probe (`7412a98`) is diagnostic only. Not a finished water fix, and not the VR stay-put.

**VR water read, when the workshop is up**

Build the water fan the way SKYINF builds the clouds: world yaw, both eyes sharing it, flat-screen appearance left as it is.

**Other checks, only if the symptom matches**

1. D233 `gfx_sp_tri1`: a vertex with `w < 0` drops the whole triangle (large wall or doorway becomes sky; props still draw). Read after the existing #79 admit path. #79 was dug as prop-admit / `CULL_BEHIND`, DoorScale ~0.75. Harvest `DIG-FRIGATE-INVIS-DOORS-20260921.md`.
2. D222: cull planes and guard fade built from nominal `fovy`, not the widened field. The VR-shaped question is which `fovy` feeds `currentPlayerSetCameraScale`. Do not port their `Video.FovScale` sliders.
3. D248: 8-byte scheduler offset sticks a 64-bit gfx client at 30 Hz while the VI clock stays at 60. Only if a client is hard-locked at half rate. This project’s sim is a 1/60 quantum on purpose. Do not treat D248 as the judder fix.
4. D255: `vtxstore_fix_refs` reads `Model*` through 4-byte `chrflags`. Crash on terminal destroy.
5. D312: `bgBuildRoomVtxBounds` counts a 16-vertex batch as 1 if `Gfx_le` packs `w0` their way. Shots pass through those walls. Take only if our display-list word matches.
6. Optional hygiene: D250 caches `getenv` on a hot path. Relevant if a `GETV_` read sits in a per-frame loop.

Smaller, symptom-gated only: black chrome if envmap UVs were stripped (D195), green CI8 water (D229), texpool 8-align (D217), IA16 gun palette swap (D228), MIPS64 PRNG shifts (D284), missing `return` silencing level music (D77).

## First five when BarZ is at the workshop

From the follow-up pack, still the order:

1. **#82** Janus — SimRig sheet. No public dig.
2. **#84** — rifle cadence shipped in vr445.1. Leftover is walk-vs-run after the spot (thet0x1n, 2026-09-23). Issue left open on purpose. Close paste, if wanted, is the harvest note `gevr-close-84-paste.md`. `gh` close from this cloud returned 403.
3. **#79** Frigate doors — dig landed, no fix. Chair / APPLY waiting on the owner.
4. **#75** — idle and intentional swings PASS with `GETV_VR_SWINGHIT=1`. Walking up still lands one free smack. Keep `HANDMELEE=1`. Do not revive `HANDSOLID`.
5. **#74** — public redigs still FAIL. Owner later called a chair perfect. Confirm which sit stuck before any ship. Do not restore `HEAD_TRANSLATE=1` as this fix.

## Leave alone

- **#56** watch-hand stretch. **#32 / #58** pause confirm. Owner said not to step on these.
- **LAN (#43 / #71).** Shelved. Do not build two-headset play.
- **TEXGUARD / SCRAPDROP** and **`GETV_VR_MONFRAME`.** Chair failed. Leave off.
- **Dam `MTXGUARD=2`.** Facility / Bunker bats only.
- **FRAMESEG / judder.** Parked. FRAMESEG is a timer, not a speed fix. The chair sit was never worn.
- Front page stays honest. Smoke and guardrails stay.
- Never push the workshop, a ROM, a built exe, or the prior-art folder to a public remote (`docs/RELEASE-POLICY.md`).

## Already in the zip (do not re-dig)

Testers are on **vr445.1**. Boot since vr444: `GETV_FPS` unset (follow the headset), `GETV_VSYNC=0`, `GETV_SUPERSAMPLE=3`, `GETV_VR_MODEMDROP=3`. SKYINF is listed as in vr445. No ASW.

## Private workshop on this cloud, when BarZ is home

Two gates, both required. This session’s `gh` token only lists public repos.

1. Grant the Cursor GitHub app access to the private GoldenEye repo.
2. Add that repo to cloud environment `ea097271-af85-11f1-bf4b-42ffb4d10ea7` (https://cursor.com/dashboard/cloud-agents/environments/e/ea097271-af85-11f1-bf4b-42ffb4d10ea7).

Until both are done, Janus, the water fan, `gfx_pc.c`, `stereo.c`, `gevr_xr.c`, and `port_input.c` cannot be read from here.
