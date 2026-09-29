# GEVR Beta vr450.2

Wear-focused VR beta update. Bring your own USA GoldenEye ROM; no ROM is included.

**Release:** https://github.com/no6969el/GEVR/releases/tag/vr450.2 (Latest)  
**Zip:** [`GEVR-Beta-vr450.2-win64.zip`](https://github.com/no6969el/GEVR/releases/download/vr450.2/GEVR-Beta-vr450.2-win64.zip)

## What is new (outcomes)

- **Keepers hard-coded in the binary** (cuff, FREEARM, corpse/door behavior, mines, re-grab, melee, landmark, aim scale, and related comfort). They stay on with a clean launch — no special boot flags.
- **Cuff / watch** — left-hand cuff stays with the controller through stage transitions.
- **FREEARM ([#109](https://github.com/no6969el/GEVR/issues/109))** — two-handed NPC / weapon interactions look better.
- **VTXFIXREFS ([#117](https://github.com/no6969el/GEVR/issues/117))** — Surface rendering gets more stable geometry.
- **Door snap / false doors / corpse pass** — door-edge aim more dependable; false doors quieter; bodies jam doors less.
- **Re-grab + mines** — thrown remote / prox mines can be picked back up; mines stick to guards, follow them, and stay visible while carried.
- **Landmark / aim scale / embed eye** — aim presentation stays readable in headset.

## Controller layout (players)

| Input | What it does |
|---|---|
| Left stick | Walk |
| Right stick | Turn (Smooth or Snap — VR Settings) |
| Both stick clicks | Recenter |
| Trigger | Fire |
| Squeeze / grip | AIM / ADS |
| A | Next weapon |
| X (left) | Previous weapon |
| B | Reload |

Quest / Index / Oculus Touch share these OpenXR actions. Fuller notes: [`docs/CONTROLS.md`](../../docs/CONTROLS.md).

## Next

Levels and gameplay stoppers: Frigate door / aperture, mission progression and locks, save-slot coverage, remaining prop-on-prop / Dam-water problems.

## Play

`Start-GEVR.bat` — **GevrRomStarter** finds `goldeneye.exe` in the same folder and sets the game path. USA `.z64`. Do not double-click `goldeneye.exe`.

Report bugs: https://github.com/no6969el/GEVR/issues/new/choose

Do not upload your ROM.
