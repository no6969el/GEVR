# ROM starter (sources + binaries)

## Sources (committed)

| File | Role |
|------|------|
| `gevr_cache_ship.h` / `gevr_cache_ship.c` | Ship stamp read/write and stale-cache invalidation |
| `gevr_prepare.c` | Reference prepare CLI; merge extract logic from GoldenEyeVR |

Copy into the **GoldenEyeVR** product tree and build. See `packaging/RESULT/GoldenEyeVR-cache-ship-stamp-APPLY.md`.

## Binaries (not committed)

Git ignores `*.exe` here. Before running `_pack-vr438.ps1`, copy from the product tree build output:

- `GevrRomStarter.exe`
- `gevr_prepare.exe`

`EXPECTED-ROM.txt` ships in the zip and documents the USA `.z64` the player must provide.

These tools must **not** embed ROM data - only read the player-supplied file at runtime.
