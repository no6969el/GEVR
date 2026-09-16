# GEVR release packaging (public repo)

Scripts and templates for **Beta ship zips** on the public `no6969el/GEVR` repo. Binaries are built on the owner SimRig from the private product tree; this folder holds the **pack layout**, **smoke gates**, and **player-facing launcher text** only.

## vr438 goal (BYO-ROM, file-backed images)

The shipped `goldeneye.exe` must **not** embed ROM-derived `images/combined.bin`. Images load from `%LOCALAPPDATA%\\GEVR\\cache\\<rom-sha256>\\` after the player supplies a **USA GoldenEye `.z64`**. The zip must **not** contain any ROM or EEPROM.

### Cache ship stamp (every public tag)

Each Beta tag bumps **`GEVR_SHIP_TAG`** in `gevr-vrNNN-boot.cmd` (for example `vr438`). **`Start-GEVR.bat`** calls that boot cmd first, then **GevrRomStarter**, which runs **`gevr_prepare.exe`** on Start.

After a successful prepare, the cache folder gets `ready` plus **`ship.txt`** (the current tag). If `ready` exists but `ship.txt` is missing or does not match `GEVR_SHIP_TAG`, prepare deletes `ready` and `combined.bin` and forces a full re-prepare from the same `.z64`. Same ROM hash is fine. Testers get **one** wait on first launch after a new zip; they do not wipe `%LOCALAPPDATA%\GEVR` unless troubleshooting.

Reference C sources: `packaging/rom-starter/gevr_cache_ship.*` and `gevr_prepare.c`. Product rebuild / merge steps: `packaging/RESULT/GoldenEyeVR-cache-ship-stamp-APPLY.md`. The stamp must live in **product** `gevr_prepare.exe` and the starter Start path - packing this repo's reference `.c` files is not enough until GoldenEyeVR is rebuilt.

**Do not** run `gh release create` or upload assets until the owner passes smoke on a clean machine.

## Owner workflow (SimRig)

1. Build file-backed VR binary (current KEEP + `-ImagesFileBacked`).
2. Drop ROM-starter tools into `packaging/rom-starter/` (see below).
3. Run `_pack-vr438.ps1`, then `_smoke-ship-zip.ps1` on the zip.
4. Test the zip on a PC that has **never** run GEVR and has **no** cache.
5. Only then tag `vr438` and publish the release (human step).

### One-liner build (product tree)

From PowerShell on SimRig, with `GoldenEyeVR` = your product root:

```powershell
cd $env:PRODUCT_ROOT\goldeneye-native\getv
.\build_windows.ps1 -Target all -Vr -ImagesFileBacked *> $env:PRODUCT_ROOT\build_vr438_filebacked.log
```

Optional harvest copy (matches historical stage B naming):

```powershell
.\packaging\_build-stage-b-images.ps1 -ProductRoot $env:PRODUCT_ROOT
```

### Pack + smoke

```powershell
$repo = "F:\Projects\GEVR\GEVR"   # this public docs repo clone
$build = "$env:PRODUCT_ROOT\goldeneye-native\getv\build-windows"
$combined = "$env:PRODUCT_ROOT\goldeneye-native\assets\images\combined\combined.bin"

& "$repo\packaging\_pack-vr438.ps1" -BuildDir $build -OutDir "$repo\packaging\out\vr438-staging"
& "$repo\packaging\_smoke-ship-zip.ps1" -StagingDir "$repo\packaging\out\vr438-staging" -CombinedBin $combined
& "$repo\packaging\_smoke-ship-zip.ps1" -ZipPath "$repo\packaging\out\GEVR-Beta-vr438-win64.zip" -CombinedBin $combined
```

Set `$env:PRODUCT_ROOT` to your `GoldenEyeVR` folder before running.

## `packaging/rom-starter/`

Place built tools here before packing (gitignored `*.exe`):

| File | Role |
|------|------|
| `GevrRomStarter.exe` | On Start: pick ROM, run `gevr_prepare.exe`, invalidate stale `ship.txt`, launch `goldeneye.exe` |
| `gevr_prepare.exe` | Extract/prepare into `%LOCALAPPDATA%\GEVR\cache\<rom-sha256>\`; write `ready` + `ship.txt` |
| `EXPECTED-ROM.txt` | SHA/size hints for USA `GoldenEye (U) [!].z64` (no ROM bytes in repo) |

Templates for player files live under `packaging/templates/`.

## Smoke gates (`_smoke-ship-zip.ps1`)

Fails the run if any of these are true:

- `goldeneye.exe` contains the first 64 bytes of local `combined.bin` (requires `-CombinedBin` on the build machine).
- `goldeneye.exe` does not contain the `[getv] images: file-backed` marker string.
- Zip or staging tree contains `.z64`, `.n64`, `.v64`, or `eeprom` payloads.
- Required DLLs missing: `glew32.dll`, `SDL2.dll`, `openxr_loader.dll`, `libwinpthread-1.dll`, `libgcc_s_seh-1.dll`, `libstdc++-6.dll`.
- `GevrRomStarter.exe` or `Start-GEVR.bat` missing.
- `Start-GEVR.bat` launches bare `goldeneye.exe` without going through `GevrRomStarter.exe`.
- `gevr-*-boot.cmd` missing `GEVR_SHIP_TAG` matching the pack `-Tag`.
- `RELEASE-NOTES.txt` missing ship stamp / cache rebuild documentation.

### Verify force-rebuild (owner)

After merging stamp logic in GoldenEyeVR, run `packaging/_verify-cache-stamp-smoke.ps1` or follow the manual steps in `packaging/RESULT/GoldenEyeVR-cache-ship-stamp-APPLY.md` (stale `ship.txt` + `ready` must not skip prepare).

## vr438 zip contents (canonical)

- `goldeneye.exe` (file-backed images build)
- Runtime DLLs from `build-windows` (including `glew32.dll`)
- `GevrRomStarter.exe`, `gevr_prepare.exe`, `EXPECTED-ROM.txt`
- `Start-GEVR.bat`, `RELEASE-NOTES.txt`
- No Nintendo ROM in the archive
