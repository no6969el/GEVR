# GEVR Beta vr450.1

Point release after **vr450**. Same KEEP minus Contextual Grip — `#90` `GETV_VR_GRIPUSE` needs further testing (**not** in ship). Squeeze = **AIM** like pre-450. Testers: **Update** in GevrRomStarter or grab this zip.

**Release:** https://github.com/no6969el/GEVR/releases/tag/vr450.1 (Latest)  
**Zip:** `F:\Projects\GEVR\_publish-GEVR\packaging\out\GEVR-Beta-vr450.1-win64.zip`  
**Smoke:** **PASS** (staging + zip, 54 KEEP knobs; GRIPUSE forbidden/unset)  
**vr450 / vr445.2:** left intact — https://github.com/no6969el/GEVR/releases/tag/vr450 · https://github.com/no6969el/GEVR/releases/tag/vr445.2  
**Slot4 APPLY:** [`director-save-slot4-APPLY.md`](director-save-slot4-APPLY.md) (carry-forward from vr450)

## What’s new / changed

- **#90 GRIPUSE OFF:** `GETV_VR_GRIPUSE` unset in ship boot (C-default OFF). Squeeze = AIM; **A** = USE/reload. Code can stay in tree for dig testing. Needs further testing — **not** advertised ON.
- **Still on from vr450:** Frigate water RECT (`GETV_VR_SKYWATERRECT`) · Save slot 4 seed (`GETV_SEEDFOLDER4`, empty FOLDER4 → 007+24 cheats; folders 1–3 safe)

## Controller layout (also at top of README)

| Input | What it does |
|---|---|
| Left stick | Walk |
| Right stick | Turn |
| Both stick clicks | Recenter |
| Trigger | Fire |
| Squeeze / grip | AIM / ADS (classic) |
| A | USE / reload |

Quest / Index / Oculus Touch share these OpenXR actions.

## Already in (unchanged)

KEEP from [vr445.2](https://github.com/no6969el/GEVR/releases/tag/vr445.2): playspace (#74), melee (#75), Janus (#82), gun origin, walk/run + ANIMFRAMES (#84), Dam SKYWORLD, rifle cadence, temp MODEMDROP=3. Plus RECT (#80) + slot4 from vr450.

## HOLD / still open

- **#90 GRIPUSE** doors — further testing; not in 450.1
- Grip pickup / mines / modem
- Frigate FRIGMUTE / DOORROOM / aperture asym (#79)
- Prop-on-prop / Dam blue (#70)
- TEXGUARD / SCRAPDROP / EMBEDEYE

## Play

`Start-GEVR.bat` or `Play-on-monitor.bat`, USA `.z64`. Do not double-click `goldeneye.exe`.

Report bugs: https://github.com/no6969el/GEVR/issues/new/choose

Do not upload your ROM.
