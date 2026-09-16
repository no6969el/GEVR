# ROM starter binaries (not committed)

Git ignores `*.exe` here. Before running `_pack-vr438.ps1`, copy from the product tree build output:

- `GevrRomStarter.exe`
- `gevr_prepare.exe`

`EXPECTED-ROM.txt` ships in the zip and documents the USA `.z64` the player must provide.

These tools must **not** embed ROM data - only read the player-supplied file at runtime.
