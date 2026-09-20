# Coming soon / watch this space

**Play now:** [GEVR Beta vr442](https://github.com/no6969el/GEVR/releases/latest) (GitHub Latest). Full zip, two bats, no ROM. You bring a USA GoldenEye `.z64`. Play steps: [README Play](../README.md#play-vr442---the-one-to-grab).

**Star** the repo and [**follow @no6969el**](https://github.com/no6969el). **Watch -> Releases** so the next zip shows up without you refreshing every day.

- **vr441** stays published (full chair boot; not Latest).
- **vr440** stays published for comparison. Same era exe family, picture-only boot. Not Latest.
- **vr434** was pulled (baked ROM images).
- **vr438** was BYO-ROM with a stub VR boot. Do not use.
- **vr439** zip removed when vr440 shipped. Tag page stays.

## On this cut (vr442)

- Headset: `Start-GEVR.bat`. Monitor / no headset: `Play-on-monitor.bat`.
- Auto-Aim defaults OFF. Pause watch: left stick moves the highlight in VR. **B** reloads. Pause is the Menu / system button (Tab on keyboard / monitor).
- **Pimax Crystal Super + SteamVR OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR), **native PimaxXR**, **Quest 3 + Virtual Desktop OpenXR (VDXR)**.
- 72 / 80 should work. Default / recommended is **90**. Over 90 is still beta-test territory - please report issues. We do not call 120 / 144 signed off.
- Tank auto-mount on the chassis + stick pitch for shells.
- Grenade launcher single-shot. Rockets nose along the flight path.
- Die / continue / pad reload fixed ([issue #38](https://github.com/no6969el/GEVR/issues/38)).
- Far character visibility boost. Empty left hand is a temporary cube.
- Hard-crash writes `gevr-fault-*.txt` beside the exe.
- Dual-wield fire, per-hand tracers, thrown grenades, Magnum / ammo polish - already in this zip from recent cooks.
- Local / split-screen multiplayer works on a monitor.

## Cooking for a later update

Soft list only. Do **not** treat these as shipped on vr442.

- Two-hand support snap, and the cube hiding when your hands get near
- Hertz: still 90-pinned in boot. Runtime request is [issue #49](https://github.com/no6969el/GEVR/issues/49) for a later EXE
- Ghost empty hand (parked). Nicer hands after that
- Big object / plane-shell explosion hard crash can still happen (fault file now)

## Later (separate track)

- **LAN / local-network multiplayer add-on** (not a mod). Local split-screen already exists.
- True online after that
- Nicer hand mesh after the ghost hand lands
- Full-body Bond is later - ghost hand first

See [ROADMAP.md](ROADMAP.md) for the honest list. Pitch: [FEATURES.md](../FEATURES.md). Hands: [CONTROLS.md](CONTROLS.md). Tester notes: [BETA.md](BETA.md).
