# APPLY: cache ship stamp (GoldenEyeVR product tree)

Public packaging in `no6969el/GEVR` ships reference sources under `packaging/rom-starter/`.
Merge the following into **GoldenEyeVR** so BarZ testers never keep a stale `combined.bin` when
`ready` survived an older cut.

Stamp lives in **product** `gevr_prepare.exe` and the **GevrRomStarter** Start path.
`GEVR_SHIP_TAG` comes from boot (`Start-GEVR.bat` calls `gevr-vr439-boot.cmd` first;
`Play-on-monitor.bat` sets the same tag itself and stays flat).

Public pack must also ship `filelist.gevr-images.csv` next to `gevr_prepare.exe`.
That file is a slice-offset manifest (not ROM bytes). Live prepare looks for it
beside the exe (`--csv` override exists); missing manifest is **exit 3**.

## Problem

`%LOCALAPPDATA%\GEVR\cache\<sha>\ready` makes `gevr_prepare` skip re-extract ("READY already
prepared"). Same ROM hash, wrong textures after a new zip.

## Fix (summary)

1. Each ship tag sets `GEVR_SHIP_TAG=vrNNN` in `gevr-vrNNN-boot.cmd` (public template already does for vr439).
2. After a successful prepare, write `ship.txt` (one line: `vrNNN`) beside `ready`.
3. Before honoring `ready`, call `gevr_ship_stamp_invalidate_if_mismatch(cache_dir)` (shared helper).
4. Optional compile-time default: `-DGEVR_SHIP_TAG_DEFAULT=\"vr439\"` when building `gevr_prepare.exe`.

## Files to copy from public repo

Into `packaging/rom-starter/` (or your existing rom-starter path):

- `gevr_cache_ship.h`
- `gevr_cache_ship.c`
- Merge `gevr_prepare.c` logic into your existing `gevr_prepare.c` (do not replace wholesale if you already have extract code).

Link `gevr_cache_ship.c` into both `gevr_prepare.exe` and `GevrRomStarter.exe`.

## gevr_prepare.c (merge points)

At top of prepare, after resolving `cache_dir` from `GEVR_CACHE_DIR` or
`%LOCALAPPDATA%\GEVR\cache\<GEVR_ROM_SHA256>`:

```c
(void)gevr_ship_stamp_invalidate_if_mismatch(cache_dir);
if (gevr_cache_ready_exists(cache_dir)) {
    fprintf(stderr, "[gevr_prepare] READY already prepared (ship=%s)\n", gevr_ship_tag_expected());
    return 0;
}
```

After successful extract, before exit:

```c
gevr_write_ready_marker(cache_dir);  /* your existing ready write */
gevr_ship_stamp_write(cache_dir, gevr_ship_tag_expected());
```

Remove any path that writes `ready` without also writing `ship.txt`.

## GevrRomStarter.exe (Start path)

After computing `cache_dir` and **before** spawning `gevr_prepare` or `goldeneye.exe`:

```c
gevr_ship_stamp_invalidate_if_mismatch(cache_dir);
```

Ensure `Start-GEVR.bat` has already run `gevr-vr439-boot.cmd` so `GEVR_SHIP_TAG` is set in the
starter process environment (public `Start-GEVR.bat` calls boot cmd first).

Pass through to child:

- `GEVR_CACHE_DIR` (if you set it explicitly)
- `GEVR_ROM_SHA256`
- `GEVR_SHIP_TAG` (inherit from env)

## getv/port/src/port_assets.c (file-backed loader)

If the port checks `ready` without calling prepare, add the same invalidation once when resolving
the cache directory for `combined.bin`:

```c
gevr_ship_stamp_invalidate_if_mismatch(cache_dir);
```

If `port_assets.c` cannot link rom-starter objects, duplicate the small file I/O or expose
`gevr_ship_stamp_invalidate_if_mismatch` from a tiny static lib used by both port and tools.

## Build flags

```text
-DGEVR_SHIP_TAG_DEFAULT=\"vr439\"
```

Bump the string when cutting the next tag and update `packaging/templates/gevr-vrNNN-boot.cmd` in the
public repo (copy from the vr439 template, change tag).

## Owner smoke (force rebuild)

On a machine with an old cache:

1. Confirm `%LOCALAPPDATA%\GEVR\cache\<sha>\ready` exists and `ship.txt` says `vr438` or is missing.
2. Install vr439 zip; run `Start-GEVR.bat`.
3. Expect console: `ship stamp mismatch ... forcing re-prepare` (or no "READY already prepared" skip).
4. After prepare: `ship.txt` contains `vr439` and `ready` is fresh.

Automated helper (public repo): `packaging/_verify-cache-stamp-smoke.ps1`.

## Tester expectations (once stamped tools are in the zip)

- **First-ever install:** pick ROM, one prepare wait, play.
- **Same zip + same ROM later:** fast path when `ship.txt` matches `GEVR_SHIP_TAG`.
- **New zip / new tag:** one re-prepare on first `Start-GEVR.bat`. Testers do **not** delete `%LOCALAPPDATA%\GEVR` unless pictures look wrong.
- Headset: always launch via `Start-GEVR.bat` so boot sets `GEVR_SHIP_TAG` before the starter runs prepare.
- Monitor / no headset: `Play-on-monitor.bat` (flat; same stamp; no KEEP boot cmd).
- `filelist.gevr-images.csv` must be in the unzipped folder or prepare exits 3.
- Old GitHub tags (`vr438`, `vr434`, `vr420`) are history only. Their zips were removed. Do not upload a zip to those tags.
