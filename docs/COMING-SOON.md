# Coming soon / watch this space

**Play now:** [GEVR Beta vr438](https://github.com/no6969el/GEVR/releases/tag/vr438) - full zip (exe, `glew32.dll`, other runtime DLLs, `Start-GEVR.bat` launches **GevrRomStarter.exe**, notes). Bring your own USA GoldenEye `.z64`; images are file-backed from your ROM.

First launch prepares those images (can take a bit). A new Beta zip does that **once** automatically on first `Start-GEVR.bat` - you do not delete the cache folder yourself. Later launches with the same zip and same ROM are fast.

**vr434 is not live** - we pulled it on 2026-09-16 because that build linked image data into `goldeneye.exe` and could boot without a ROM. Do not use an old vr434 download.

**Star** the repo and **Watch → Releases** so the next cut shows up without you refreshing every day.

## VR that works on this cut

- **Pimax Crystal Super + SteamVR OpenXR** via [CustomHeadsetOpenVR](https://github.com/sboys3/CustomHeadsetOpenVR) (sboys3) - primary wear path
- **Native PimaxXR** - verified
- **Quest 3 + Virtual Desktop OpenXR** - verified

72 / 80 / **90** Hz should work (zip defaults to 90). Above 90 is still beta-test territory - please report Issues.

Full recipe + controls: [CONTROLS.md](CONTROLS.md). Attract sheet: [FEATURES.md](../FEATURES.md). Pack gates: [packaging/README.md](../packaging/README.md).

Also useful:
1. [README](../README.md) (play steps + roadmap)
2. [Credits](../CREDITS.md)
3. [Bug / crash forms](https://github.com/no6969el/GEVR/issues/new/choose)

Crashes are expected in Beta - please file [Issues](https://github.com/no6969el/GEVR/issues) with **headset + OpenXR runtime + SteamVR on/off + HMD vs monitor + Start-GEVR.bat yes/no**.
