---
cursor:
  subagentId: "bc-65ab2f40-71c9-5e11-bb80-dc6de62f4b5a"
---

# APPLY — Slot 4 = 007 + leftover cheats (vr450 rebake)

**Status:** **SHIPPED** into **[vr450](https://github.com/no6969el/GEVR/releases/tag/vr450)** (asset replaced in place; **vr445.2** untouched).  
**Dig:** [`director-save-slot4-007-cheats.md`](director-save-slot4-007-cheats.md) — Rank-1 **Y** (FOLDER4-only migrator).  
**Smoke:** **PASS** (staging + zip, 55 KEEP knobs) before upload.

## Product choices (BarZ open picks → APPLY defaults)

| Pick | Choice | Why |
|------|--------|-----|
| **Force-replace vs seed-if-empty** | **Seed-if-empty** | Dig Rank-1 + A gate. Empty FOLDER4 (no times, no cheat bits, no `flag_007`) gets 007+cheats. A used slot 4 is left alone. |
| **MP unlocks** | **SP slot4 only** | Same V2 setters as `GETV_UNLOCKALL` for **one** folder (Agent/Secret/00 times + 24 solo cheat bits + `flag_007|=1`). No extra MP unlock code. Dig note stands: Egypt-00 on folder 4 can still trip **any-folder** MP gates as a side effect of SP completion. |
| **Leftover cheats** | **24 solo unlock bits + 007** | Matches dig “solo unlock surface” + 007 mode. |
| **One-shot / stamp** | **Every boot, empty-check** | Idempotent: once seeded, folder is non-empty → no rewrite. No ship stamp file. |

## Mechanism (in-exe — not zip EEPROM)

- Hook in `fileValidateSaves()` after the diagnostic `GETV_UNLOCKALL` block (`file2.c`).
- `fileGetSaveForFoldernum(FOLDER4)` → V2 **direct** setters → **one** `fileWriteSave(save4)`.
- Gate: `GETV_SEEDFOLDER4` unset/empty/non-`0` = **ON** (ship default). Dig OFF: `=0`.
- Config key: `seed_folder4` / `seedfolder4` → `GETV_SEEDFOLDER4` (`ge_config.c`).
- **Never** arms `GETV_UNLOCKALL`. Boot template comments say so (`gevr-vr450-boot.cmd`).

## Slots 1–3 safety proof

1. **Code path:** migrator resolves **only** `FOLDER4` and writes that `save_data*`. No loop over `FOLDER1..3`. Full `GETV_UNLOCKALL` stays chair-only / off.
2. **Ship policy:** zip still contains **no** `eeprom.bin` (smoke gate). RomStarter Update still does not touch Roaming EEPROM; seed runs inside the new exe on next boot when FOLDER4 is empty.
3. **Binary receipt:** shipped `goldeneye.exe` contains `seedfolder4` / `SEEDFOLDER4` strings.

## KEEP (unchanged from prior vr450) + slot4

- vr445.2 stack + `GETV_VR_SKYWATERRECT=1` + `GETV_VR_GRIPUSE=1` (doors)
- **Plus** FOLDER4 seed (C-default ON)

## Must-not (honored)

- No Usetup* level edits
- TEXGUARD / SCRAPDROP / EMBEDEYE left alone
- No FRIG* default-on
- No grip pickup

## Build / pack

- Build: `-Vr -ImagesFileBacked` → `getv\build-windows\goldeneye.exe`
- Pack: `_pack-vr450.ps1` → `GEVR-Beta-vr450-win64.zip`
- Publish: `gh release upload vr450 … --clobber` + notes edit (same tag; no `vr450.1`)
