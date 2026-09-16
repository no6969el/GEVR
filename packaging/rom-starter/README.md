# ROM starter (sources + binaries)

## Runtime flow

Always launch via a zip bat, not bare `goldeneye.exe`.

- **Headset:** `Start-GEVR.bat` calls `gevr-vr439-boot.cmd` (sets `GEVR_SHIP_TAG=vr439` and VR KEEP knobs), then **`GevrRomStarter.exe`**.
- **Monitor / no headset:** `Play-on-monitor.bat` sets `GEVR_SHIP_TAG=vr439` itself, turns XR/stereo off, then **`GevrRomStarter.exe`**. It does not call the KEEP boot cmd.

On Start, GevrRomStarter:

1. Lets the player pick a USA GoldenEye `.z64` they own.
2. Runs **`gevr_prepare.exe`** into `%LOCALAPPDATA%\GEVR\cache\<rom-sha256>\`.
3. After a successful prepare, that folder holds `ready` plus **`ship.txt`** (one line: the current tag).
4. If `ready` exists but `ship.txt` is missing or does not match `GEVR_SHIP_TAG`, prepare deletes `ready` and `combined.bin` and re-slices from the same `.z64`.
5. Then launches `goldeneye.exe`.

Returning testers who unzip a new Beta get **one** prepare wait on first launch. They do not delete the cache folder by hand (once stamped tools are in the zip).

These tools must **not** embed ROM data - only read the player-supplied file at runtime. Do not put a `.z64` in this folder or in the zip.

Product merge steps: [`packaging/RESULT/GoldenEyeVR-cache-ship-stamp-APPLY.md`](../RESULT/GoldenEyeVR-cache-ship-stamp-APPLY.md).

## Sources (committed)

| File | Role |
|------|------|
| `gevr_cache_ship.h` / `gevr_cache_ship.c` | Ship stamp read/write and stale-cache invalidation |
| `gevr_prepare.c` | Reference prepare CLI; merge extract logic from GoldenEyeVR |

Copy into the **GoldenEyeVR** product tree and build. See the APPLY note above.

## Binaries (not committed)

Git ignores `*.exe` here. Before running `_pack-vr439.ps1`, copy from the product tree build output:

- `GevrRomStarter.exe` (must call prepare on Start, then launch the game)
- `gevr_prepare.exe` (must honor `GEVR_SHIP_TAG` / `ship.txt`)

`EXPECTED-ROM.txt` ships in the zip and documents the USA `.z64` the player must provide.
