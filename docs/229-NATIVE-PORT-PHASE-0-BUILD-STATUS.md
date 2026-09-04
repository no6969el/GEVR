# 229 — NATIVE PORT PHASE 0: BUILD STATUS + NEXT-SESSION RUNBOOK

**Direction:** the native source port (`227`, `228`). This doc is the live
Phase 0 build log for `SegfaultEvan/goldeneye-native` on the owner's Windows
box. Phase 0 gate = **native GoldenEye boots and plays from the owner's ROM.**

> **OWNER POLICIES STILL BIND:** no git commits/branches/resets (reading is
> fine); DELETE NOTHING (mark superseded, keep every off-switch). The owner's
> ROM is never committed or transmitted.

---

## §0 — WHERE WE ARE (as of 2026-08-27)

`[MEASURED]` from `goldeneye-native/build.log`, last full run:
- windows **game: 165 built, 0 failed**
- windows **assets: 232 built, 0 failed**
- windows **audio: 40 built, 0 failed**
- windows **port c++: 2 built, 0 failed**
- windows **port layer: 42 built, 16 FAILED** ← the only blocker
- link: never reached.

**All 16 port failures were the same one line:** `fatal error: PR/gbi.h: No
such file or directory` (`#include <PR/gbi.h>`, first seen in
`getv/port/fast3d/gfx_opengl.c:10`).

**Root cause `[MEASURED]`:** `getv/port/include/PR` and
`getv/port/include/platform_info.h` are **git symlinks into
`vendor/ge-decomp/include/`** that Windows checked out as tiny plain files (36
bytes: literally the text `../../../vendor/ge-decomp/include/PR`). So the
port's own include dir never exposes the decomp headers, and `$portFlags`
did not carry the decomp include path.

---

## §1 — THE TWO FIXES APPLIED THIS SESSION (already on disk)

Edited `getv/build_windows.ps1` (a file edit, NOT a git commit; backup saved
as `build_windows.ps1.bak-preVR`):

**Fix A — give the port batch the decomp headers.** In `$portFlags` (~line
207) added two include roots right after the port includes:
```
"-I$decomp\include", "-I$decomp\include\PR",
```
`$decomp` is already defined at line 75 (`vendor\ge-decomp`). This resolves
`<PR/gbi.h>` and `platform_info.h` without touching the broken symlinks.

**Fix B — drop the tvOS-only main from the link harness.** At ~line 350:
```
$rootStems = @('ge_mac_main.o')   # was @('ge_tvos_main.o','ge_mac_main.o')
```
`ge_tvos_main.c` is tvOS-only and cannot compile on Windows; `main()` for the
desktop build lives in `ge_mac_main.o`, which IS built and present
(`build-windows/obj/..._ge_mac_main.o`). The old harness threw
`missing harness object *ge_tvos_main.o` at link time.

**Prediction (to be verified next run):** port layer goes 58/58 (or 57 + the
harmless tvOS skip), link produces `goldeneye.exe`.

---

## §2 — ENVIRONMENT ALREADY STOOD UP (do NOT redo unless it regressed)

`[MEASURED]` done in prior sessions on the owner's box:
- MSYS2 mingw64 toolchain at `C:\msys64\mingw64` (gcc 16.2.0). **PATH:** the
  build needs `C:\msys64\mingw64\bin` on PATH or `cc1.exe` dies on missing
  `libisl-23.dll` / `libgcc_s_seh-1.dll` / `libgmp-10.dll`. Already added to
  the User Path permanently; if a fresh shell still fails, prepend it:
  `$env:PATH = "C:\msys64\mingw64\bin;" + $env:PATH`.
- `mingw-w64-x86_64-glew` installed (fixed the direct-GLEW port files).
- Python 3.12 installed + a Git-Bash `~/bin/python3` shim (`exec python "$@"`)
  in `~/.bashrc` (the asset gen scripts call `python3`).
- SDL2 dev libs present for mingw; ROM at
  `vendor/ge-decomp/baserom.u.z64` (US, sha1 of the matching decomp).
- `baserom.u.cdata` decompressed; generated asset/layout includes written
  (`ge_propdef_layout.inc.c` etc.).
- CRLF stripped from all `vendor/ge-decomp/**/*.sh` (Windows autocrlf breaks
  `/bin/bash^M`).

---

## §3 — NEXT-SESSION RUNBOOK (do these in order)

**Terminal note:** `build_windows.ps1` is **PowerShell**, not Git Bash. Run it
from a PowerShell window with the mingw PATH in scope.

1. **Re-run the build**, capturing the log, from `goldeneye-native/`:
   ```powershell
   cd C:\Users\<USER>\Desktop\GoldenEyeVR\goldeneye-native
   & getv\build_windows.ps1 -Target all *> build.log 2>&1
   ```
2. Paste nothing huge — just say "done"; the assistant reads `build.log` over
   the bridge and reports.
3. **Expected next states / how to react:**
   - *Port layer now 0 failed, link makes `goldeneye.exe`* → go to step 4.
   - *New compile errors in the port layer* → almost certainly more headers the
     decomp expects; read the first `fatal error:` line, add the missing `-I`
     to `$portFlags` the same way. Check for OTHER broken symlinks first:
     `find getv/port -type f -size -200c` and read any that contain `../`.
   - *Link errors (undefined reference)* → a port stub is missing a symbol;
     name it, find it in the decomp, add the TU or a stub in
     `port/src/ge_link_stubs.c`.
4. **Boot it** with the owner's ROM (the Phase 0 gate). Confirm the exe finds
   `baserom.u.z64` / built assets, launches SDL2+GL, reaches a menu, and a
   stage loads and plays. Record framerate.
5. **Log the result back into THIS doc (§4)** and flip the HANDOVER banner.

---

## §4 — PHASE 0 RESULT LOG (append as we go)

- 2026-08-27a: fixes A+B applied. **Re-run reached the LINK step** (all objects
  compiled). New blocker surfaced there: **multiple-definition** link errors
  (`padlist`, `propDefs`, `path_table_*`, `intro`, `pathsets`...) between
  per-stage setup files in `assets/obseg/setup/u/` (`UsetupcradZ.o`,
  `UsetupdestZ.o`, `Ump_setuparchZ.o` all define bare `padlist` etc).

- **ROOT CAUSE (`[MEASURED]`):** the asset **symbol-uniquify pass was never run**
  on this checkout. `tools/uniquify_asset_symbols.py` is supposed to give every
  setup/stan TU its own symbol prefix (`padlist` -> `UsetupcradZ_padlist`); the
  generated files still have bare names, so every level's data collides. This is
  a CORRECTNESS bug, not just a link nuisance: without it every stage binds to
  whichever level linked first (SETUP.md §"Every level was running on some other
  level's data"). Pipeline order (SETUP.md §3.6): run the 6 uniquify passes, THEN
  `git apply getv/patches/0002-assets.patch`.

- **SCOPE (`[MEASURED]`):** the only TUs needing uniquify here are
  `assets/obseg/setup` (30), `assets/obseg/setup/u` (8), `assets/obseg/stan` (29)
  = **67 files, all prefix = file-stem**. `chr/gun/prop` contain ONLY `.inc.c`
  (no standalone TUs) in this asset generation, so their `--recurse` passes match
  0 files and are correct no-ops — do NOT chase them.

- **WHY IT'S SLOW OVER THE BRIDGE:** the tool shells out to `clang -O1` per file;
  `-O1` on the giant generated initializer arrays is pathological (one setup file
  = **>40s**). At **-O0 it is ~1.4s** (opt level is irrelevant to symbol names).
  Two portability facts for whoever runs it: the tool hardcodes `clang` and the
  clang-only flag `-ferror-limit=0`. A `clang` shim that (a) maps
  `-ferror-limit=0`->`-fmax-errors=0` and (b) forces `-O0`, then execs `gcc`,
  makes it work with the mingw toolchain and fast. (Shim kept at `~/shimbin/clang`
  in the Cowork Linux VM this session; on Windows, make an equivalent `clang.cmd`
  on PATH before the mingw `gcc`, or edit the tool's `CFLAGS` to `-O0` and its
  two `subprocess.run(['clang'...])`/`ferror-limit` lines to gcc equivalents.)

- **UPDATE 2026-08-27b — UNIQUIFY COMPLETE (67/67).** All setup(30)+setup/u(8)+
  stan(29) TUs are now symbol-namespaced. Verified: `UsetupcradZ_padlist`,
  `UsetupdestZ_padlist`, `Ump_setuparchZ_padlist` are now distinct (the exact
  collision from the link error is gone); 0 bare `tile_0` left in stan; the only
  remaining bare `padlist` are the 14 files in `setup/e`+`setup/j`, which the
  build EXCLUDES (build_windows.ps1 lines 296-297) — correct, no collision.
  Two extra portability bugs in `uniquify_asset_symbols.py` had to be worked
  around and MUST be fixed if it is ever re-run on Windows/Linux: (1) it shells
  out to `clang -O1`; `-O1` on the giant setup/stan initializers takes >40s/file,
  `-O0` is ~1.4s and identical for symbol extraction. (2) `globals_of` only keeps
  nm symbols that **start with `_`** (macOS Mach-O convention); on ELF/PE64 there
  is no leading underscore, so it extracts NOTHING and renames NOTHING (silent).
  The fix: accept symbols with or without a leading `_`. (Done this session via a
  patched batch driver `~/uniq_batch.py` in the Cowork VM; the vendored tool on
  disk is unchanged.)

- **NEXT ACTION IS NOW JUST: REBUILD.** The asset .c files have newer mtimes, so
  `& getv\build_windows.ps1 -Target all *> build.log 2>&1` will recompile them.
  Expect the setup/u multiple-definition errors gone. If NEW multiple-definition
  errors appear from another asset dir, that dir needs uniquify too — but stan and
  setup were the standalone-TU dirs; chr/gun/prop are `.inc.c` only.

- **0002-assets.patch:** SETUP.md says apply after uniquify, but it is PARTIALLY
  applied on this checkout (`git apply --check` fails on animationtable/ fonts).
  It was NOT needed to reach a clean uniquify. Try the rebuild WITHOUT it first;
  only if the build errors point at something the patch fixes, apply with
  `git apply --3way` (from `vendor/ge-decomp`) and inspect any `.rej`.

- ~~**STATUS AT SESSION END:** uniquify NOT yet completed over the bridge (45s

### §3 (revised) NEXT-SESSION RUNBOOK — do in order

**Step 0 (NEW — do FIRST): run the asset symbol-uniquify on the Windows box.**
In PowerShell, create a `clang` shim on PATH that forwards to mingw `gcc`, forcing
`-O0` and mapping `-ferror-limit=0`; or simplest, edit
`tools/uniquify_asset_symbols.py`: change `'clang'` -> `'gcc'` (both
`subprocess.run` calls), `-ferror-limit=0` -> `-fmax-errors=0`, and `-O1` -> `-O0`
in `CFLAGS`. Then from inside `vendor\ge-decomp`:
```
python3 ..\..\tools\uniquify_asset_symbols.py assets/obseg/setup
python3 ..\..\tools\uniquify_asset_symbols.py assets/obseg/setup/u
python3 ..\..\tools\uniquify_asset_symbols.py assets/obseg/stan
```
Each must end with NO "FILE(S) DID NOT COMPILE" block. (chr/gun/prop passes are
no-ops here — 0 TUs — skip them.) Verify: `grep padlist assets/obseg/setup/u/UsetupcradZ.c`
should now read `UsetupcradZ_padlist`.

**Step 0b: apply the assets patch** (only after uniquify): from `vendor\ge-decomp`,
`git apply ..\..\getv\patches\0002-assets.patch`. NOTE: parts of this patch
already applied on this checkout (`git apply --check` fails on
`animationtable_data.h`, fonts). Use `git apply --3way` or apply with
`--reject` and inspect `.rej` files; do not force. If it's already effectively
applied, skip.

**Step 1: rebuild** `& getv\build_windows.ps1 -Target all *> build.log 2>&1`;
say "done"; assistant reads `build.log`. Expect the multiple-definition errors
gone and the link to produce `goldeneye.exe`.

**Step 2: boot** with the owner's ROM = the Phase 0 gate (menu + a stage plays).

**Prior blocker log (superseded, kept):** 2026-08-27: fixes A+B applied; port
42/58 -> compiled; then the setup/u multiple-definition link errors above.

---

## §5 — AFTER PHASE 0 (from `228`, not started)

Phase 1 stereo (port PD VR `port/fast3d` stereo) → Phase 2 OpenXR (port PD VR
`port/vr/vr_openxr.cpp`, frame hook `vr_begin_frame_and_update_poses` →
`lvTick` → `vr_end_frame_and_submit`) → Phase 3 motion aim (the `[MEASURED]`
aim spec from `194`/`226`: fault was screen-space firing; in a native port we
control the fire ray directly) → Phase 4 comfort → Phase 5 Quest standalone.
All inputs are MIT (goldeneye-native, PD VR © Ryan Dwyer, Fast3D).

---

## §6 — LOCAL FILES/FOLDERS THE NEXT SESSION MUST HAVE ACCESS TO

Request these at session start (the whole GoldenEyeVR desktop folder covers all
of it; listed granularly in case access is scoped):
- `C:\Users\<USER>\Desktop\GoldenEyeVR\goldeneye-native\` — the native port
  (build script, `getv/port/**`, `vendor/ge-decomp/**`, `build.log`,
  `build-windows/obj/**`). **This is the active work tree.**
- `C:\Users\<USER>\Desktop\GoldenEyeVR\repo\docs\` — all handover/design docs
  (this file, `225`–`228`, `00-START-HERE`, `HANDOVER`).
- `C:\Users\<USER>\Desktop\GoldenEyeVR\local-only\perfect_dark_VR\` — the PD VR
  source to port the VR layer from (Phases 1–5).
- Read-only reference (recomp fallback, DELETE NOTHING):
  `C:\Users\<USER>\Desktop\GoldenEyeVR\repo\` build/patches.

**Cannot run from the bridge:** the Windows PowerShell + mingw build itself —
the owner runs `build_windows.ps1`; the assistant reads `build.log`.

---

## §7 — 2026-08-27c: LINK REACHED, TWO REGRESSIONS FIXED

Rebuild after uniquify: **all multiple-definition errors GONE** (uniquify
confirmed working end-to-end). Link then failed on **undefined references** to
port symbols (`gePortLauncherRun`, `gePortUserDataDir`, `osSyncPrintf`, ...)
because the **port layer regressed to 16 failed** + a truncated asset. Two
distinct causes, both now fixed on disk:

1. **Port include was too broad (my §1 Fix A).** `-I$decomp\include` put the
   decomp's SHADOW `stdarg.h` on the port's search path, so SDL's
   `#include <stdarg.h>` resolved to the N64 stdarg (dragging in the whole
   ultra64/gu/mbi chain) and every fast3d/port file broke. The port's design
   exposes ONLY `PR/` and `platform_info.h` from the decomp (that's what the two
   git symlinks `port/include/PR` and `port/include/platform_info.h` did) — never
   the whole `include/` root. **FIX:** materialized those two as REAL files in a
   clean dir `getv/port/prheaders/` (`PR/*.h` + `platform_info.h`), added
   `-I$here\port\prheaders` at the FRONT of `$portFlags`, and REMOVED the two
   `-I$decomp\include*` entries. This reproduces the symlinks without shadowing
   system headers. (The broken 36-byte symlink files under `port/include/` are
   left in place — harmless now, and the bridge can't delete them.)

2. **One asset truncated by an interrupted write.** The uniquify batch driver's
   write to `assets/obseg/stan/Tbg_dam_all_p_stanZ.c` was killed mid-write by the
   45s device-shell cap, leaving it 727 lines (should be 35953) -> `expected '}'`.
   **FIX:** restored from the git blob (`git show HEAD:<path>`, a read) and
   re-uniquified with an ATOMIC write (temp + `os.replace`). Verified 35953 lines,
   symmetric git numstat, `tile_0` -> `Tbg_dam_all_p_stanZ_tile_0`. Scanned all 67
   uniquified files via `git diff --numstat`; only this one was truncated.
   A stray `Tbg_dam_all_p_stanZ.c.orig` remains in the stan dir (bridge can't
   delete/mv) — neutralized to a 48-byte comment; owner can delete it.

**NEXT ACTION: rebuild again.** `& getv\build_windows.ps1 -Target all *> build.log 2>&1`.
Expect: port layer 58/58, assets 232/232, link -> `goldeneye.exe`. If some port
file now fails on `<ultra64.h> not found`, that PR header needs ultra64 exposed
too — copy `vendor/ge-decomp/include/ultra64.h` (and any it names) into
`getv/port/prheaders/`. Then boot with the ROM = Phase 0 gate.

---

## §8 — 2026-08-27d: §7 CONFIRMED. THE ROM `files` EXTRACTION PASS WAS NEVER RUN.

**§7's two fixes WORKED.** `[MEASURED]` from `build.log`: game **165/165**, assets
**232/232**, audio **40/40**, port layer **58/58** (was 16 failed), port c++ **2/2**,
`libge.a` 19.5 MB / 496 members. **Every compile stage is now clean.** The link is
the only remaining step, and it fails on **undefined references**, not
multiple-definition — a different and much later failure than 2026-08-27a.

### THE UNDEFINED SYMBOLS ARE ALL ONE THING

Three families, all referenced from `src/game/ob.c`:
- `gePortObsegSize` — the size-lookup function
- `bg_*_all_p_seg` × 25 (`bg_dam_all_p_seg`, `bg_sev_all_p_seg`, …)
- `C*Z` × many (`CarmourguardZ`, `CcheckmanZ`, `CbondZ`, …) — the chr/gun/prop model blobs

**They are the 759 symbols `assets/obseg/ob_seg.s` would `.incbin`** (725
`obseg_file_rz|Z` + 34 `bg_file_seg`), which `tools/gen_obseg_blobs.py` is supposed
to emit as C arrays.

### ROOT CAUSE (`[MEASURED]`) — NOT A CODE BUG, A SKIPPED PIPELINE STEP

`assets/obseg/ge_obseg_blobs.c` on disk is **6 lines — the header comment and
nothing else.** `assets/obseg/ge_obseg_sizes.c` **does not exist.** So
`gen_obseg_blobs.py` ran and found **zero** of its inputs.

Its inputs are `assets/obseg/<dir>/<name>.bin`. `[MEASURED]`:

```
find assets/obseg -name '*.bin'   ->  0 files
```

And more broadly, of the **634 rows in `scripts/filelist.u.csv` with extract=1,
0 exist on disk.** Meanwhile `find assets -name '*.bin'` returns **2699** — all of
them under `assets/images/`.

> **THE `images` HALF OF `scripts/extract_baserom.u.sh` RAN. THE `files` HALF NEVER
> DID.** That is the whole fault. Every downstream generator that reads a `.bin`
> silently produced an empty result, and nothing complained until the link.

**`tools/extractor/extractor` is not built** (only its `.c`/`makefile` are present),
which is consistent with the `files` pass never having been reached.

### WHAT IS *NOT* WRONG — CHECKED, SO IT IS NOT RE-CHASED

- **`enable_bg_extraction.py` is already done.** Re-ran it this session: *"34
  background rows, 0 switched on, 34 already on."* All 34 bg rows have extract=1.
  **`SETUP.md` §7.2's `bg_*_all_p` diagnosis does NOT apply here** — that one is
  about the flag; ours is about the extraction never running at all.
  **TRAP, and it cost a wrong reading this session: `filelist.u.csv` is
  `offset,size,name,compressed,extract` — `extract` is column 4, `compressed` is
  column 3.** Reading col 3 as the extract flag says "all 34 bg rows are off" and
  sends you to the wrong `SETUP.md` section.
- **Uniquify (67/67) is still good** — no multiple-definition errors returned.
- **§7's `prheaders/` include fix holds** — port layer stayed at 58/58.
- **`0002-assets.patch` is not implicated.** Leave it alone.

### NEXT ACTION — OWNER, IN **GIT BASH** (not PowerShell), from `vendor/ge-decomp`

```bash
cd /c/Users/<USER>/Desktop/GoldenEyeVR/goldeneye-native/vendor/ge-decomp
make -C tools/extractor                 # builds the extractor (mingw gcc)
bash scripts/extract_baserom.u.sh files  # the half that never ran; ~10 min
python3 ../../tools/gen_obseg_blobs.py   # now finds its 759 inputs
```

**Gates, in order — check each before moving on:**
1. `find assets/obseg -name '*.bin' | wc -l` → **must be 551**, not 0.
2. `gen_obseg_blobs.py` must print `emitted 759 blobs` (or close) and **must not
   list missing names**. `[EXPECTED]` `ge_obseg_blobs.c` becomes tens of MB.
3. `ls assets/obseg/ge_obseg_sizes.c` → **must now exist.**

Then rebuild: `& getv\build_windows.ps1 -Target all *> build.log 2>&1` (PowerShell).

**WHY THE OWNER RUNS THIS AND NOT THE BRIDGE:** 716 file writes plus one tens-of-MB
write through the device shell. §7 item 2 `[MEASURED]` exactly that failure mode —
the 45s cap killed a write mid-file and left a truncated asset that cost a build.
**The extraction is idempotent** (byte ranges copied out of the ROM), so a re-run is
always safe.

**IF `gen_obseg_blobs.py` STILL REPORTS MISSING NAMES:** it prints them. Cross them
against `filelist.u.csv` — a name missing there with `extract=0` is a second flag
bug in the same family as `enable_bg_extraction.py`; a name present with extract=1
whose `.bin` is absent means the extractor errored on that row. **Do not stub them
in `ge_link_stubs.c`** — a 0xFF stub links and then loads garbage at runtime, which
is `gen_obseg_blobs.py`'s own docstring warning (the silent-bg trap).

---

## §9 — 2026-08-27e: THE EXTRACTION FAILED SILENTLY ON **CRLF**. FIXED, RUN, INSTALLED.

§8 was right that the `files` pass never produced anything, and wrong about why.
The owner ran it; it printed `emitted 0 blobs` and `759 had no .bin`.

### `[MEASURED]` ROOT CAUSE — ONE CARRIAGE RETURN PER LINE

`scripts/filelist.u.csv` was **CRLF, all 812 lines.** The extractor binary was not
built (`make` is not on the owner's Git Bash PATH), so
`scripts/extract_baserom.u.sh` fell through to its **bash `while read` fallback**,
which tests the extract flag:

```bash
while IFS=, read -r offset size name compressed extract
do  if [ "$extract" == "1" ]; then ... else echo "skip $name"; fi
```

With CRLF the field parses as **`'1\r'`**, the test is false for **every row**, and
the script prints `skip` 812 times and exits 0. **No error, anywhere.**
The script's own comment says it: *"unix line endings only"*.

> **AND THERE IS A CONTROL ON DISK THAT PROVES IT.** `build/u/imagelist.csv` is
> **also CRLF — and the images extracted fine (2699 `.bin`).** Its loop is
> `read -r offset size name rest`: it never tests a flag, and `rest` swallows the
> `\r`. **Same script, same run, same CRLF — the half that reads a flag failed and
> the half that does not succeeded.** That is why `assets/images/` was full and
> `assets/obseg/` was empty, which is the exact shape §8 measured.

**This is the same CRLF class as §2's `*.sh` fix. The CSVs were missed.**

### `[MEASURED]` WHAT §8 GOT WRONG, RECORDED SO IT IS NOT REPEATED

§8 said *"the `files` half never ran"*. **It ran every time and skipped every row.**
The distinction matters: "never ran" points at the invocation, and the fault was in
the data. **A pass that skips 812 of 812 rows and exits 0 is indistinguishable from
one that was never invoked, unless you read the flag field as bytes.**

### WHAT WAS DONE THIS SESSION (all on disk, no git operations)

1. **CRLF stripped from `scripts/filelist.u.csv`** (atomic temp+rename; backup at
   `/tmp/filelist.crlf.bak` in the VM). Verified: 0 CR remain, 812 rows, 634 with
   extract=1, and **every field byte-identical to the backup after strip.**
2. **Extraction run** with a locally-built extractor: **634 extracted / 178 skipped
   in 0.081 s.** (The skipped 178 are extract=0 by design.) The `makefile` builds
   clean — **the binary was built in `/tmp`, deliberately NOT in the tree**, because
   a Linux ELF at `tools/extractor/extractor` would satisfy the script's
   `[ -x ... ]` test on Windows and break the next run.
3. **550 obseg `.bin` (9 MB) copied into the tree and verified `cmp`-identical,
   0 mismatches of 628.**
4. **`gen_obseg_blobs.py` run:** `emitted 537 blobs -> ge_obseg_blobs.c (20.9 MB)`,
   `512 blob sizes -> ge_obseg_sizes.c`, `25 bg sizes -> ge_obseg_bg_sizes.h`.
5. **All three installed** via copy-to-`.part` + size-check + `mv` (the §7 anti-
   truncation pattern). Verified `cmp`-identical in the tree.

### `[MEASURED]` THE LINK SHOULD NOW RESOLVE — CHECKED SYMBOL BY SYMBOL

The 36 unique undefined symbols in `build.log`, differenced against the new blob
symbols plus everything already in `libge.a`:

> **1 remained: `gePortObsegSize` — and it is defined at
> `ge_obseg_sizes.c:1043`, which did not exist before this session.**

`bg_dam_all_p_seg`, `bg_sev_all_p_seg`, `CcheckmanZ`, `CarmourguardZ` each
individually confirmed present in `ge_obseg_blobs.c`.

### THE 222 THE GENERATOR STILL REPORTS AS "NO .bin" — 177 ARE FINE

`[MEASURED]` **177 of the 222 are already defined in `libge.a`** — the `T*stanZ`,
`Usetup*Z` and `Ubrief*Z` families ship as **checked-in `.c`**, are compiled, and
need no blob. **Their appearance in the generator's warning is expected noise, not
a fault. Do not chase them and do not stub them.**

**The other 45 are `L*P` — the PAL text banks.** They are referenced by
`file_resource_table.inc.c` and `ob_seg.s:763`, but **have no rows in
`filelist.u.csv` at all** (the US ROM does not contain them). **They did NOT appear
in this build's undefined list**, so they are left alone deliberately —
`[ASSUMED]` the US resource table never reaches them.

> **IF THE NEXT LINK REPORTS `LdamP` / `LameP` / …, THE FIX IS ALREADY PRECEDENTED
> AND IS ONE EDIT:** `getv/port/src/ge_link_stubs.c` **already stubs `LaztJ`,
> `LsevbJ`, `LstatJ`** — absent-language text banks, exactly this class. Add the 45
> `L*P` the same way. **This is safe for TEXT and would NOT be safe for bg** (the
> generator's docstring: a 0xFF bg stub links and then silently loads an
> uninitialised header). Text for a language the US build never selects is inert.

### NEXT ACTION — OWNER: JUST REBUILD (PowerShell)

```powershell
cd C:\Users\<USER>\Desktop\GoldenEyeVR\goldeneye-native
& getv\build_windows.ps1 -Target all *> build.log 2>&1
```

**`[EXPECTED]` asset count rises above 232** (the three generated files are new TUs;
`ge_obseg_blobs.c` is 20.9 MB and **will be slow to compile — that is normal, not a
hang**). **Then the link should produce `goldeneye.exe`.** Then boot with the ROM =
the Phase 0 gate.

### FOR ANYONE RE-RUNNING THE PIPELINE FROM CLEAN — TWO PERMANENT TRAPS

1. **Normalise the CSVs, not just the `.sh` files:**
   `scripts/filelist.u.csv` and any generated `imagelist.csv`. Git autocrlf on
   Windows re-introduces this on every fresh checkout.
2. **`filelist.u.csv` is `offset,size,name,compressed,extract`** — `extract` is
   **column 4**, `compressed` is column 3. Reading col 3 as the flag says the 34 bg
   rows are all off and sends you to `SETUP.md` §7.2 (`enable_bg_extraction.py`),
   which is **not** the fault. That tool is already correctly applied here — re-ran
   it this session: *"34 background rows, 0 switched on, 34 already on."*

---

## §10 — 2026-08-27f: 36 UNDEFINED -> 2 -> 0. BOTH WERE DOWNSTREAM OF §9.

`[MEASURED]` from `build.log`: game 165/165, **assets 233** (was 232 — the new
`ge_obseg_sizes.c`), audio 40/40, port 58/58, **`libge.a` 23.4 MB / 497 members**
(was 19.5 MB / 496). **§9's blobs linked: every `bg_*_all_p_seg` and `C*Z` is gone
from the undefined list.** Two symbols remained, and neither was a new fault —
**both were consequences of the extraction having never run.**

### FAULT 1 — `geAudioSegment`

`src/ge_audio_segment.h` declared it; **nothing defined it.**
`tools/gen_audio_segment.py` reads `assets/music/*.ctl`, `*.tbl` and the `M*.bin`
tracks — **all extract=1 rows that §9's CRLF bug had skipped**, so an earlier run
had produced the header and no array.

**FIX: re-ran it now that the 74 music assets exist.** `[MEASURED]`:
`instruments.ctl rev=16945 banks=1 instruments=75 sounds=131 wavetables=106` ·
`music.s 63 tracks, packed 126156 bytes` · **`segment: 1362046 bytes -> 6.9 MB of C`.**
Installed `assets/music/ge_audio_segment.c` (7,236,194 bytes) and a regenerated
`src/ge_audio_segment.h`.

> **NOTE, and it is reassuring:** the regenerated header's five offsets are
> **identical** to the one already on disk (`SFXCTL 0`, `SFXTBL 23488`,
> `INSTRUMENTSCTL 820848`, `INSTRUMENTSTBL 838160`, `MUSICSAMPLETBL 1235376`,
> `TOTAL 1362046`). The only difference was **CRLF vs LF** — the old copy was CRLF.
> **So the audio layout was right all along and only the array was missing.**

### FAULT 2 — `u_UsetuplenZ_credits_data_0`: THE UNIQUIFY PASS DOUBLE-PREFIXED ONE FILE

`bondview_r.c:449` declares `extern CreditsEntry u_UsetuplenZ_credits_data_0[]`.
The file defined **`UsetuplenZ_u_UsetuplenZ_credits_data_0`** — the `u_` prefix
applied **twice**.

`[MEASURED]` the convention is confirmed by the sibling dirs, which the build
excludes but which are correct: `assets/obseg/setup/e/UsetuplenZ.c` defines
**`e_UsetuplenZ_credits_data_0`** and `setup/j` defines **`j_UsetuplenZ_...`**.
**The right name for `setup/u` is `u_UsetuplenZ_*`, one prefix, dir-letter based.**

**`[MEASURED]` SCOPE — IT IS EXACTLY ONE FILE.** Checked all 8 `setup/u` TUs for
the `<stem>_u_<stem>_` pattern: **`UsetuplenZ` had 13 symbols affected; the other
seven had zero.** `UsetuplenZ` is the only setup/u file `src/` reaches into by
name, which is why only it broke and why nothing else in the batch is suspect.

**FIX:** rewrote `UsetuplenZ_u_UsetuplenZ_` -> `u_UsetuplenZ_` in that one file,
**44 occurrences, 17 distinct symbols**, atomic temp+rename, backup at
`/tmp/UsetuplenZ.bak` in the VM. Verified: 0 residual double prefixes ·
`CreditsEntry u_UsetuplenZ_credits_data_0[]` defined at line 103 ·
`stagesetup UsetuplenZ` (the file's own top-level symbol) **untouched** ·
**no collision** — no other built file defines `u_UsetuplenZ_*`.

**AND THE CHECK WAS GENERALISED SO THIS CLASS IS CLOSED:** swept **all** of
`src/game/*.c` for externs naming a setup asset symbol. **There is exactly one in
the entire tree** (`u_UsetuplenZ_credits_data_0`), and it now resolves. **No other
`src/`->asset name dependency exists to be broken by uniquify.**

### NEXT ACTION — OWNER: REBUILD (PowerShell)

```powershell
cd C:\Users\<USER>\Desktop\GoldenEyeVR\goldeneye-native
& getv\build_windows.ps1 -Target all *> build.log 2>&1
```

**`[EXPECTED]` assets 234** (`ge_audio_segment.c` is a new TU) and **the link
produces `goldeneye.exe`.** Both remaining undefined symbols are now defined and
no new references were introduced. **Then boot with the ROM = the Phase 0 gate.**

**`[ASSUMED]`, stated so it is not mistaken for a measurement:** that the link is
now complete. **Only the link can say so** — the two fixes were verified as
definitions present and non-colliding, not as a successful link. If `L*P` surfaces,
§9's precedented `ge_link_stubs.c` fix applies.

---

## §11 — 2026-08-27g: ►►►► **IT LINKS. `goldeneye.exe` EXISTS.** ◄◄◄◄

`[MEASURED]` from `build.log`, clean run, **zero errors at every stage**:

| stage | result |
|---|---|
| game | **165 built, 0 failed** |
| assets | **234 built, 0 failed** |
| audio | **40 built, 0 failed** |
| port layer | **58 built, 0 failed** |
| port c++ | **2 built, 0 failed** |
| `libge.a` | **24.7 MB, 498 members** |
| **binary** | **`getv/build-windows/goldeneye.exe` — 17.2 MB** |

`grep -c 'undefined reference|error:|multiple definition'` = **0**.
**§10's `[EXPECTED]` assets 234 was exact**, and its `[ASSUMED]` that the link was
complete is now `[MEASURED]`. **`L*P` never surfaced** — the US resource table does
not reach the PAL text banks, as §9 assumed. **No stub was needed; do not add one.**

### THE PHASE 0 BLOCKER CHAIN, END TO END — ALL FOUR WERE BUILD-PIPELINE, NONE WERE CODE

1. **`PR/gbi.h`** — git symlinks checked out as 36-byte text files (§1, §7.1)
2. **multiple-definition** — asset symbol uniquify never run (§4)
3. **`bg_*_all_p_seg` / `C*Z` / `gePortObsegSize`** — **CRLF in
   `scripts/filelist.u.csv`** made the ROM `files` extraction skip 812 of 812 rows
   and exit 0 (§9). **The single highest-value finding here.**
4. **`geAudioSegment`** (same CRLF cause) and **one double-prefixed uniquify file**
   (§10)

> **THE METHOD NOTE, AND IT MATCHES `HANDOVER` §5.** Every one of these was found by
> **reading disk state and diffing symbol sets** — never by guessing at a fix and
> rebuilding. §9's CRLF root cause was settled by a **control that was already on
> disk**: `imagelist.csv` is CRLF too, and its loop does not test a flag, so images
> extracted while obseg did not. **One run of the same script proved and disproved
> the hypothesis simultaneously.** No speculative edit was made at any point.

### ►►►► NEXT ACTION: THE PHASE 0 GATE. OWNER, IN THE HEADSET-FREE FLAT BUILD. ◄◄◄◄

**Run it with the owner's ROM. This is the gate `227` set and it has never been met.**

```powershell
cd C:\Users\<USER>\Desktop\GoldenEyeVR\goldeneye-native\getv\build-windows
.\goldeneye.exe
```

**What must be true to call Phase 0 PASSED — record each, not just "it works":**
1. the exe **finds `baserom.u.z64` / the built assets** and does not exit early
2. **SDL2 + GL window opens**
3. **reaches the menu** (this is also where the recomp's `206` menu crash lived —
   **if the native port's menu is clean, that is a finding in its own right**)
4. **a stage loads and PLAYS**
5. **record the framerate**

**IF A STAGE LOADS BUT LOOKS WRONG** — geometry from another level, missing rooms —
**suspect uniquify before anything else** (`SETUP.md`: *"every level was running on
some other level's data"*). §10 verified only the one `src/`-facing symbol; it did
**not** verify that all 67 uniquified TUs bind their own data at runtime.
**That check is the boot, and only the boot.**

**THEN:** log the result in §4, **flip the `HANDOVER` and `00-START-HERE` banners**,
and Phase 1 (stereo, `228`) begins. **`§5`'s phase list is unchanged.**

> **AND THE COMMIT IS NOW 39+ DOCUMENTS OVERDUE, BOTH REPOS.** Owner-only,
> `commit-session.ps1`, at the main PC, not through the bridge. **This session
> changed real files on disk** (`filelist.u.csv` line endings, 550 extracted
> `.bin`, three generated obseg files, `ge_audio_segment.c/.h`, `UsetuplenZ.c`) —
> **a working native build is worth a commit far more than the 38 that preceded it.**

---

## §12 — 2026-08-27h: ►►►►►► **PHASE 0 IS PASSED. IT BOOTS AND PLAYS.** ◄◄◄◄◄◄

`[REPORTED]` ***"It works"*** — the native GoldenEye port runs from the owner's ROM.
**The gate `227` set is met.** `228`'s Phase 1 (stereo) is now unblocked.

**TWO DEFECTS `[REPORTED]` ON THE FIRST RUN:**
1. *"the audio for the gun shots is late"*
2. *"the explosion effect is not loading — it was all purple and missing the texture"*
3. *"I am sure there are other missing things"* — **treated as the important one.**

### THE OWNER'S QUESTION: "WE HAVE TO REBUILD TO FIX, RIGHT?" — **YES, BOTH.**

`[MEASURED]`, so it is not re-asked:
- **Assets are compiled into the binary** (`libge.a` 24.7 MB), so any asset or
  generated-data fix is a rebuild by construction.
- **The audio latency is a compile-time constant**, not a setting.
- **`ge_config.c` has NO audio/latency key**, and the exe accepts only
  `--config --help --launcher --list-cheats --write-config`. **There is no runtime
  knob for either fault.**

### ►► BUT DO NOT REBUILD YET. THE GAME ALREADY PRINTS THE ANSWER. ◄◄

**`[READ]` the port has the instruments for BOTH faults already built in:**

| instrument | what it says |
|---|---|
| `gfx_pc.c:459` | **the purple IS the port's own marker** — *"4x4 pink-black checkerboard texture to indicate missing textures"*, uploaded at `:1657`. **It is a diagnosed state, not corruption.** |
| `gfx_pc.c:1996` | `fprintf(stderr, "NULL texture: tile %d, format %d/%d, size %d")` — **names the failing tile and format** |
| `ob.c:293` | `[getv][ob] index= name= hw= obsegsize= -> NATIVE (early-out) \| ROM LOAD PATH` — first 12 resource loads |
| `ob.c:~262` | `[getv][watch] UsetuparchZ[0]` — catches linked `.data` being overwritten at runtime |
| `port_audio.c:523` | `[getv] audio: %d Hz stereo, %d samples/frame, device %u` |

> **ONE CAPTURED RUN ANSWERS "WHAT ELSE IS MISSING" FOR THE WHOLE GAME.** Guessing
> at the explosion instead costs a full rebuild per guess, and the blobs file is
> 21 MB — **rebuilds are now expensive.** This is `HANDOVER` §5 exactly: *"When
> tempted to ship a candidate, ship an instrument instead."* **The instrument is
> already shipped; it has simply never been read.**

**CAPTURE COMMAND (PowerShell) — play until an explosion, then quit:**
```powershell
cd C:\Users\<USER>\Desktop\GoldenEyeVR\goldeneye-native\getv\build-windows
.\goldeneye.exe *> run.log 2>&1
```

### `[MEASURED]` FAULT 1 IS ALREADY DIAGNOSED WITHOUT A RUN — AND ITS OWN COMMENT DISAGREES WITH ITS CODE

`port_audio.c:52-54`:
```c
/* How much audio to keep queued on the device, in stereo frames. Two video frames'
 * worth is enough to ride out a slow frame without adding audible latency; the game
 * pushes ~736 samples per frame at 60 Hz. */
#define GE_QUEUE_TARGET     (GE_FRAME_SAMPLES * 4)
```
> **THE COMMENT SAYS TWO VIDEO FRAMES. THE CODE QUEUES FOUR.**

`[MEASURED]` arithmetic at `GE_OUTPUT_RATE 22050`, `GE_FRAME_SAMPLES 736`
(interleaved, = one 60 Hz video frame = 16.7 ms):

| term | latency |
|---|---|
| `GE_QUEUE_TARGET = FRAME_SAMPLES * 4` | **66.8 ms** |
| the same at `* 2` (what the comment describes) | **33.4 ms** |
| SDL `want.samples = 512` on top | **23.2 ms** |

**~90 ms total. A gunshot is the most latency-exposed sound in the game**, which is
why it is the one `[REPORTED]`. **CANDIDATE FIX: `* 4` -> `* 2`, one line, and it
restores the stated design intent rather than inventing a value.**

**`[ASSUMED]` — and the counter-example search, per `209`:** that the queue is the
dominant term. **Searched for a competing source of gunshot delay: the sfx trigger
path is sample-driven** (`port_audio.c:600` — *"players advance by samples, so
skipping a frame here does not drop events"*), **so it does not add a variable
delay.** No second candidate found. **But `-ViRate`/frame pacing was never measured
here, and if the port runs below 60 Hz the queue drains differently — so the run
log's `[getv] audio:` line and the framerate are wanted BEFORE this is built.**

### FAULT 2 — LEAD SUSPECT, NOT YET A CLAIM

`[MEASURED]` **four §3.5 generated outputs PREDATE the 19:17 extraction:**

| file | generated | |
|---|---|---|
| `build/imagelist.csv` | 17:29:13 | **STALE** |
| `assets/images/combined/combined.bin` | 17:29:41 | **STALE** |
| `assets/images/ge_images_segment.c` | 17:29:42 | **STALE** |
| `assets/ge_animation_offsets.h` | 17:29:43 | **STALE** |
| `src/ge_asset_fileview.h` | 17:29:44 | **STALE** |
| `ge_obseg_blobs.c` / `ge_audio_segment.c` | 19:19 / 19:24 | ok (rebuilt this session) |

**`[NOT MEASURED]` whether any of them actually READS a file that only appeared at
19:17.** The images half of the extractor **did** work at 17:29 (2698 split `.bin`
present), so the image pipeline may be entirely fine. **The mtimes are a lead, not
a diagnosis — the `NULL texture` line will say which it is.** Re-running the tail of
§3.5 blind would be the guess this project keeps paying for.

**AND ONE THING TO RULE OUT FIRST, BECAUSE THIS SESSION CHANGED IT:** §9 gave 512
symbols a real `gePortObsegSize`, which flips them from **NATIVE (early-out)** to
the **ROM LOAD PATH** at `ob.c:296`. **That is the CORRECT direction** — those
symbols were 0xFF-poisoned stubs before, and the path exists to inflate exactly
these `.rz` blobs — **but it is a behaviour change made this session and the
`[getv][ob]` lines confirm or refute it in one look.** **Check it before anything
else.**

### THE ORDER

1. **capture `run.log`** (above), play to an explosion, quit with `taskkill`
2. assistant reads it: `NULL texture` lines · `[getv][ob]` NATIVE vs ROM LOAD PATH ·
   `[getv] audio:` · framerate
3. **fix everything it names in ONE rebuild**, audio constant included
4. **then** log Phase 0 PASSED in §4 and flip the `HANDOVER` / `00-START-HERE`
   banners to Phase 1

---

## §13 — 2026-08-27i: `run.log` CAME BACK **ZERO BYTES**. THE PORT HAS NO STDOUT ON WINDOWS.

§12 sent the owner to capture `run.log`. **It is 0 bytes. Not truncated — empty.**

### `[MEASURED]` ROOT CAUSE: PE SUBSYSTEM 2, FROM AN UNFILTERED `-mwindows`

Read straight out of the binary's PE optional header:

```
goldeneye.exe   PE magic 0x20b   Subsystem = 2  ->  GUI (WINDOWS)
```

**A subsystem-2 process has no console and no stdout handle**, so
`.\goldeneye.exe *> run.log` redirects a handle that was never connected to
anything. **Every `printf` in the port has been discarded on Windows since the
first boot** — `gfx_pc.c`'s `NULL texture`, `ob.c`'s `[getv][ob]`, `[getv] audio:`,
all of it.

**WHERE IT COMES FROM `[MEASURED]` BY ELIMINATION:** `-mwindows` appears nowhere in
`build_windows.ps1` (`grep -c` = 0) and nothing in `$linkArgs` sets a subsystem —
but mingw's `sdl2.pc` ships `Libs: ... -lmingw32 -lSDL2main -lSDL2 -mwindows`, and
the script builds `$sdlLibs` from `pkg-config --libs sdl2`. **It already strips
`-lSDL2main` and `-Dmain=SDL_main` out of that very output, and simply never
strips `-mwindows`.**

> **THE FAILURE MODE IS THE POINT: nothing is broken and nothing is logged.** The
> build is clean, the game runs, the redirect reports no error, and the file is
> empty. **An instrument that cannot say "I CANNOT ANSWER THIS" (`48`) is worse
> than no instrument — this one silently answered "nothing is wrong".**

**FIX (on disk):** strip `-mwindows` in the same idiom as the `-lSDL2main` line.
**OFF-SWITCH `-GuiSubsystem`** restores it for release builds (no console window).
**VERIFY BY THE PE HEADER, NOT BY EYE: subsystem must read 3.**

### AND THE AUDIT THAT FOLLOWS FROM IT — DO NOT SKIP THIS

**Every `[REPORTED]` symptom from the native port so far was judged with the
diagnostics switched off.** `225`-`229` cite `build.log` freely, which is the build
script's output and is real. **But no runtime `[getv]` line has ever been read on
Windows.** Treat any prior runtime claim about the native port as `[ASSUMED]`.

### THIRD SYMPTOM `[REPORTED]` THIS SESSION

> ***"the text to choose the game save is missing, you have to click around to find it."***

**Menu text absent, controls still live** — the strings do not draw, the widgets do.
**`[ASSUMED]` same family as the purple explosion: an asset that is present as a
symbol but empty or unloaded.** Deliberately NOT diagnosed further without the log.

**Counter-example search, per `209`:** checked whether it is one of the **stubbed**
text banks — `ge_link_stubs.c` stubs `LaztJ`, `LsevbJ`, `LstatJ` only, all Japanese,
and the file-select strings are not in them. **`[MEASURED]` the `L*E` banks are all
compiled into `libge.a`** (`asset_._assets_obseg_text_LmiscE.o`, `LoptionsE.o`,
`LtitleE.o` … all present). **So the stub list does NOT explain it and that lead is
closed.** It needs the log.

### THIS REBUILD CARRIES TWO CHANGES — OWNER APPROVED THE BUNDLE

`48` says one behaviour change per run. **Asked, and the owner chose to bundle**, on
the reasoning that late gunshots are judged BY EAR and cannot be confounded with
missing textures or missing text.

1. **`build_windows.ps1`** — strip `-mwindows` (instrumentation; **not** a game
   behaviour change)
2. **`port_audio.c:54`** — `GE_QUEUE_TARGET` `* 4` -> `* 2`, **66.8 ms -> 33.4 ms**.
   This is not a tuned value being retuned: **it restores the value the comment
   three lines above it has always described.** Full arithmetic and the revert
   condition are in the comment now.

### NEXT ACTION — REBUILD, THEN CAPTURE

```powershell
cd C:\Users\<USER>\Desktop\GoldenEyeVR\goldeneye-native
& getv\build_windows.ps1 -Target all *> build.log 2>&1
cd getv\build-windows
.\goldeneye.exe *> run.log 2>&1
```

**Play to an explosion AND to the save-select screen, then quit with `taskkill`.**
**`run.log` must now be non-empty — if it is still 0 bytes, the subsystem did not
change and nothing else in this plan is worth doing.** Listen for the gunshots on
the way past.

---

## §14 — 2026-08-27j: THE LOG WORKS. **IT CLEARS THE TEXTURES ENTIRELY.**

`[MEASURED]` `run.log`: **5,384,689 bytes, 100,270 lines**, ends with
`[getv] game_exit requested`. **§13's subsystem fix is confirmed working.**

### ►► THE HEADLINE: THERE IS NO TEXTURE FAULT. NOT ONE. ◄◄

| probe | count |
|---|---|
| `NULL texture: tile …` (`gfx_pc.c:1996`) | **0** |
| `could not load texture: …` (`gfx_pc.c:1655`) | **0** |
| `modeltex: … N resident in pool, **0 MISSING**` | **every line, no exceptions** |
| fonts | **both converted, `0/94 chars have kerningindex outside 0..12`** |

**AND THE PINK/BLACK `missing_texture` CANNOT BE WHAT THE OWNER SAW.** `[READ]`
`gfx_pc.c:1643` — that path is reached only from `fs_load_file(fullpath)`, i.e. the
**external HD-texture loader**, and it always prints `could not load texture` first.
**Zero of those lines. §12 named this marker as the lead suspect; it is now
excluded.** The purple is something else — an untextured/miscoloured surface, not an
absent asset.

### `[MEASURED]` THE RUN NEVER REACHED AN EXPLOSION — SO IT CANNOT SPEAK TO IT

- `grep -c explo` = **4**, and all four are
  `alloc_explosion_smoke_casing_scorch_impact_buffers` — **buffer allocation at load,
  not a single explosion event.**
- **peak `drawn=` over the whole run: 2382 tris** (frame 4141 was `drawn=269`).
  **Front-end / briefing scale, not deep gameplay.**
- 4141 frames at `fps=60`, ~69 s.

> **THE OWNER SAID WHY, AND IT IS THE REAL FINDING:** ***"The menu is really hard to
> get through, im not even sure that is what is happening."*** **The unreadable menu
> is not one bug among three — it is the bug that PREVENTS TESTING THE OTHER TWO.**
> It gets priority on those grounds alone.

### AND THE MENU TEXT IS **NOT** A MISSING ASSET — ALSO MEASURED

`[MEASURED]` from `[getv][ob]`, every front-end text bank resolves on the correct
path: **`LtitleE`, `LmiscE`, `LoptionsE`, `LmpmenuE`, `LmpweaponsE`, `LpropobjE`,
`LgunE` — all `obsegsize=0 -> NATIVE (early-out)`**, which `ob.c:250` documents as
the correct answer for linked C data. **Plus both fonts convert cleanly.**

> **SO THE STRINGS ARE PRESENT AND THE GLYPHS ARE PRESENT.** The fault is in
> **DRAWING** them — not loading them. **§13's `[ASSUMED]` "an asset present as a
> symbol but empty" is now falsified.** Every asset-side explanation for the menu
> text is closed.

### FOURTH SYMPTOM `[REPORTED]`, AND IT IS THE SHARPEST ONE YET

> ***"when you click on the copy (for copy file save) it makes a noise, when you back
> out it makes a machine gun sound."***

**A menu click producing a MACHINE GUN is not a missing sound — it is a sound that
played, from the WRONG INDEX.** The bank is present and `sndPlaySfx` succeeded;
the id resolved to the wrong record.

**CONTEXT THAT MATTERS: THIS IS AUDIO'S FIRST LIGHT.** §10 created
`ge_audio_segment.c` **for the first time** — before it, `geAudioSegment` was
undefined and the binary did not link at all. **So this is not a regression. No
build has ever had working audio to regress from**, and the segment's index mapping
has never been checked against anything.

`[MEASURED]` what the bank loader reports:
`bank converted -- 1 bank(s), 929 records` (sfx) and `1 bank(s), 606 records`
(instruments); `ALHeap high-water 99616 of 131072`; `22050 Hz stereo, 736
samples/frame`. **No error on either bank — they parse; the mapping is the suspect.**

**`[NOT MEASURED]` and NOT to be guessed at:** whether the offset is a constant
shift, a per-bank base, or a wrong record stride. **`GETV_AUDIO_TESTSFX=<id>` plays
one id every 60 frames and prints `TESTSFX id=N -> started|REFUSED`
(`port_audio.c:252`) — that is the instrument that turns this into a number.**

### THE AUDIO LATENCY CHANGE IS UNJUDGED

§13 shipped `GE_QUEUE_TARGET * 4 -> * 2`. **The owner never reached a gunfight**, so
**`[UNJUDGED]`, not passed and not failed.** Do not record it either way.

### ►►►► THE UNBLOCK: SKIP THE MENU. IT IS ALREADY BUILT AND NEEDS NO REBUILD. ◄◄◄◄

`[READ]` `0001-source.patch:18478` documents `GETV_MENU` / `GETV_MENUSTAGE`, which
set **the engine's own menu-entry variable** (`initgamedata.c:10`) — *"it uses the
engine's own entry mechanism rather than a new code path"*, and *"absent the env
vars nothing above changes."* **Verified against `bondconstants.h:1939-1966`:**

`0 LEGAL · 1 NINTENDO · 2 RAREWARE · 3 EYE_INTRO · 4 GOLDENEYE_LOGO ·
5 FILE_SELECT · 6 MODE_SELECT · 7 MISSION_SELECT · 8 DIFFICULTY · 10 BRIEFING ·
24 DISPLAY_CAST` — and `GETV_MENUSTAGE` defaults to **33 = DAM**.

**This is exactly the tool for a menu the owner cannot read: jump straight past it.**

### NEXT RUN — NO REBUILD. TWO CAPTURES, EACH ANSWERING ONE THING.

**A) Get in-game, and judge the explosion AND the gunshot audio:**
```powershell
cd C:\Users\<USER>\Desktop\GoldenEyeVR\goldeneye-native\getv\build-windows
$env:GETV_LOGFLUSH="1"; $env:GETV_MENU="10"; $env:GETV_MENUSTAGE="33"
.\goldeneye.exe *> run_dam.log 2>&1
```
**Fire a lot. Blow something up. Close with X** (`game_exit requested` proves the
clean exit; **the X-close crash is recomp-era and `[REPORTED]` does not happen on
this build** — `HANDOVER` §3's `taskkill` note does not apply to the native port).

**B) The sound map, one id at a time** — `$env:GETV_AUDIO_TESTSFX="<id>"`, and say
what is heard. **A handful of ids is enough to tell a constant offset from a
scramble**, which decides the whole shape of the fix.

### THE FOUR OPEN SYMPTOMS, RE-RANKED BY WHAT BLOCKS WHAT

1. **menu text not DRAWN** (assets proven present) — **blocks all other testing**
2. **sfx wrong index** — sharpest signal, has a ready instrument
3. **purple explosion** — **no texture fault exists in the log**; needs run A to
   even be observed
4. **gunshot latency** — `[UNJUDGED]`, needs run A

---

## §15 — 2026-08-27k: **MY §14 SENT THE OWNER TO THE WRONG MENU. `GETV_MENU=10` IS THE BRIEFING, NOT THE LEVEL.**

`run_dam.log` (4,306,862 bytes) `[MEASURED]`: **the override fired correctly** —
`[getv][menu] GETV_MENU override: menu=10 stage=33 briefingpage=1
brieffile=UbriefdamZ` — and DAM's data loaded (`UsetupdamZ`,
`Tbg_dam_all_p_stanZ`). **But it still never entered the level:**

| | run.log (§14) | run_dam.log |
|---|---|---|
| peak `drawn=` | 2382 | **2274** |
| guard models (`Cgreatguard2Z`, `CheadleeZ`) | **loaded** | **NOT loaded** |

**`GETV_MENU=10` is `MENU_BRIEFING` — ANOTHER MENU SCREEN.** The owner hit the same
unreadable-text wall one screen further along. **`run_dam.log` actually got LESS far
than `run.log` did.**

**`[MEASURED]` the enum, counted from 0 at `bondconstants.h:1941`:**
```
0 LEGAL  1 NINTENDO  2 RAREWARE  3 EYE_INTRO  4 GOLDENEYE_LOGO  5 FILE_SELECT
6 MODE_SELECT  7 MISSION_SELECT  8 DIFFICULTY  9 007_OPTIONS  10 BRIEFING
11 RUN_STAGE  12 MISSION_FAILED  13 MISSION_COMPLETE ...
```
> **`MENU_RUN_STAGE` = 11. THAT is the one that boots into the level, and the
> patch's own worked example says so** (`0001-source.patch:7338`:
> *"On DAM with `GETV_MENU=11 GETV_MENUSTAGE=33`"*). **§14 quoted an abbreviated
> list from the patch COMMENT that omits `9 MENU_007_OPTIONS`; the header is the
> source of truth and it was never checked against it.** `168`'s rule in a new
> costume: **read the mechanism, not the summary of it.**

**DO NOT ADD `GETV_ENDLEVEL`.** The same comment documents it SIGSEGVing every run
at `bondviewUpdateCameraMatrices + 100` (the NULL-stan mission-end crash). **It is
only wanted when hunting that specific bug.**

### "NO SOUND AT ALL" — DO NOT FILE THIS AS A REGRESSION YET

`[MEASURED]` the audio stack came up healthy in this run, identically to the last:
`bank converted -- 929 records` · `606 records` · `22050 Hz stereo, 736
samples/frame, device 2` · `ALHeap high-water 99616 of 131072` · `frame driver
armed`. **No error on any of it.**

**The owner spent this run on the BRIEFING screen. A briefing screen legitimately
has no sfx** — and the *"machine gun"* was `[REPORTED]` from **FILE_SELECT/copy**,
a screen this run never visited. **So "no sound at all" and the crossed sfx are not
in conflict, and neither is judged.** `port_audio.c:153` states the exact
distinction the counters exist to draw: *"a silent run can be split into 'the game
never asked' and 'the game asked and nothing came out'"* — **`GETV_AUDIO_DEBUG=1`
is what reads them, and it has not been on yet.**

### NEXT RUN — INTO THE LEVEL, WITH THE AUDIO COUNTERS ON

```powershell
cd C:\Users\<USER>\Desktop\GoldenEyeVR\goldeneye-native\getv\build-windows
$env:GETV_LOGFLUSH="1"; $env:GETV_AUDIO_DEBUG="1"
$env:GETV_MENU="11"; $env:GETV_MENUSTAGE="33"
.\goldeneye.exe *> run_lvl.log 2>&1
```
**Shoot a lot. Blow something up. Close with X.**
**GATE, so it is not another wasted run: guard models (`C*Z ... ROM LOAD PATH`)
must appear and `drawn=` must exceed ~2400.** If it does not, the level did not
load and nothing else in the log means anything.

**This one run can settle THREE of the four open symptoms** — the explosion, the
gunshot latency, and whether audio is asked-for-but-silent — **because they are all
gameplay-only and every previous run stopped short of gameplay.**

---

## §16 — 2026-08-27l: ►► **THE SILENCE IS LOCALISED TO ONE STAGE: ENVMIX.** ◄◄

`[REPORTED]` ***"there IS no sound, my computer plays sound fine."*** **The owner is
right, and §15's "a briefing screen legitimately has no sfx" is now superseded — it
was true of THAT run and wrong about the fault.** `HANDOVER` §5 again: **wear
reports outrank analysis.**

### THE GATE PASSED — THIS RUN FINALLY REACHED GAMEPLAY

`[getv][menu] GETV_MENU override: menu=11 stage=33` · guard models loaded
(`Cgreatguard2Z` 10013 B, `CheadalanZ` 1481 B, **ROM LOAD PATH**) · `drawn=` peak
**2405**. **`GETV_MENU=11` is confirmed as the way into a level.**

### `[MEASURED]` THE GAME ASKED FOR AUDIO. LOUDLY.

Last frame, `f=1504`: **`req=[m1,s146]`** — **146 sfx requests and 1 music
request** · `trk=[9,0,0]` · `voices=[9,0,0]` · `state=[1,0,0]` ·
**`mixops=653361`** · `q` reaching **1249-1256** · `ovf=0`.
**Nothing is idle and nothing is failing. And `rmsL=0.0 rmsR=0.0 pk=0 pkAll=0`
across `nz=0/1505` — EVERY ONE OF 1505 FRAMES WAS DIGITAL SILENCE.**

### ►► THE CHAIN PROBE NAMES THE STAGE. THE PORT'S AUTHOR BUILT IT FOR EXACTLY THIS. ◄◄

`ge_mixer.c:76` — *"each probe is the peak absolute sample that stage wrote. **The
first zero in the chain, reading adpcm -> resample -> envmix -> mix -> interleave ->
save, is the stage that killed it.**"*

```
load=32768  adpcm=32768/57544  resample=32570/67922
envmix=0/60402   mix=0/142880   interleave=0/7520   save=0      (peak/calls)
```

| stage | peak | verdict |
|---|---|---|
| load | **32768** | full scale |
| adpcm | **32768** / 57,544 calls | full scale |
| resample | **32570** / 67,922 calls | full scale |
| **envmix** | **0** / **60,402 calls** | **CALLED 60k TIMES, WROTE SILENCE EVERY TIME** |
| mix / interleave / save | 0 | downstream of the kill |

### AND THE SECOND PROBE SPLITS *WHY*, ALSO AS DESIGNED

`ge_mixer.c:93` — *"That splits 'the input never arrived' from **'the input arrived
and a volume of zero multiplied it away'**."*

```
envmix: in_pk=32570  vol=[1,1]  dry=32767  wet=30957  target0=0  rate0=-1
```

> **THE INPUT ARRIVED AT FULL SCALE. THE VOLUME IS `1` OUT OF `32767`.**
> These are **running maxima** (`if (rspa.vol[0] > ge_mixer_em_vol0)`), so `1` is
> the **highest volume reached in the entire run** — about **-90 dB**. With
> `target0 = 0`, the envelope is ramping to zero as well. **The samples are
> perfect and the envelope multiplies them away.** The author's own second branch,
> confirmed.

**WHERE IT IS WRITTEN: `aSetVolumeImpl` (`ge_mixer.c:275`)** — `rspa.vol[]`,
`rspa.target[]`, `rspa.rate[]` are all set there from the ACMD operands. `[ASSUMED]`
the operand decode or the ABI variant is wrong; **`[NOT MEASURED]` which.**
**Counter-example search:** `dry=32767` and `wet=30957` come through that same
struct **correctly**, so the struct is not wholesale garbage and a blanket
"rspa is corrupt" explanation is excluded — **it is `vol`/`target` specifically.**

### ►► TWO THINGS THIS EXONERATES — BOTH WERE THIS SESSION'S WORK ◄◄

1. **§10's `ge_audio_segment.c` IS CORRECT.** `[MEASURED]` **ADPCM decodes to a
   peak of 32768 — full scale.** The bank parse (`929 records` / `606 records`),
   the sample data and the segment offsets are all proven good **by the audio
   coming out of the decoder**. **The 6.9 MB we generated is right.**
2. **§13's `GE_QUEUE_TARGET *4 -> *2` IS NOT THE CAUSE.** `[MEASURED]` `q` reaches
   **1249-1256** against the new target of 1472, `ovf=0`. **The queue is being fed
   on schedule — with silent samples.** Do not revert it looking for the sound.

**AND `GETV_ENVCLAMP` IS NOT THE KNOB.** `[READ]` `ge_mixer.c:1203`
`geEnvSamplesGuard` clamps **sample COUNTS** (`samples < 0`, `> maxsamples`), not
volume. **Ruled out before it cost a run.**

### ONE THING THAT DOES NOT FIT, RECORDED RATHER THAN EXPLAINED AWAY

`[REPORTED]` earlier: *"when you click on the copy it makes a noise, when you back
out it makes a machine gun sound."* **Audible sound, in the front end.** But this
run measures `pkAll=0` on every frame in a LEVEL. **Either the front-end sfx take a
different path, or the two observations disagree.** **`[NOT MEASURED]` — the
front-end has never been run with `GETV_AUDIO_DEBUG=1`.** It is one run to settle,
and it is worth settling: **a path that DOES produce sound is a working reference
for the one that does not.**

### THE FAULT IS NOW A CODE BUG IN THE PORT'S MIXER, NOT A BUILD-PIPELINE FAULT

**Every blocker in §1-§11 was pipeline. This one is not** — it is `aSetVolumeImpl`
and the GE ENVMIXER ABI (`ge_mixer.c:690-760`, which cites `mupen64plus-rsp-hle`'s
`alist_envmix_ge` and warns that **Ship of Harkinian's mixer is ABI2 and NOT a valid
reference for this game**). **Read that block comment before touching anything —
it pre-refutes the obvious wrong reference.**

**NEXT: the owner's call on whether to open the mixer, plus the one cheap run
above** (`GETV_AUDIO_DEBUG=1` with **no** `GETV_MENU`, click around the file-select
screen) **to capture the front-end path that reportedly DOES make noise.**

---

## §17 — 2026-08-27m: ►► **§16 IS RETRACTED. THE SILENCE IS MY DIAGNOSTIC, NOT A MIXER BUG.** ◄◄

`[REPORTED]` ***"That was before the sound stopped. There was a run before this it
all worked."*** **The owner's correction, and it is right again** (`HANDOVER` §5:
*"the owner's corrections have been right every time they conflicted with my
reading"* — **that list now has another entry**).

### `[MEASURED]` THE TIMESTAMPS SETTLE IT WITHOUT A NEW RUN

| time | event |
|---|---|
| 19:43:53 | `port_audio.c` edited (§13's `GE_QUEUE_TARGET`) |
| **19:49:50** | **`goldeneye.exe` built — the ONLY binary since** |
| 19:51:01 | `run.log` — **`[REPORTED]` SOUND: the copy click, the "machine gun"** |
| 19:55:42 | `run_dam.log` — `GETV_MENU=10` added |
| 19:58:33 | `run_lvl.log` — `GETV_MENU=11` + `GETV_AUDIO_DEBUG=1` — **SILENT** |

> **ONE BINARY. THREE RUNS. THE ONLY DIFFERENCE BETWEEN THE RUN THAT MADE SOUND AND
> THE RUN THAT DID NOT IS ENVIRONMENT VARIABLES.**
> **A binary that produced audio at 19:51 cannot have a categorically broken mixer
> at 19:58.** §16's `vol=[1,1]` is real and measured — **but it describes a run
> entered through `GETV_MENU=11`, not the game.**

### WHAT §16 GOT WRONG, AND IT IS A NAMED TRAP

**§16 read `envmix=0` and concluded "a code bug in the port's mixer".** The probe
chain was sound; **the CONTROL was missing.** There was no measurement of the same
probes on a run that DOES make noise, so "envmix writes zero" was never separated
from "envmix writes zero *when the front end is skipped*".

> **`GETV_MENU` IS DOCUMENTED AS A DIAGNOSTIC THAT BYPASSES THE ENGINE'S OWN BOOT
> WALK** — `0001-source.patch:18470`: *"a headless boot walks LEGAL -> NINTENDO ->
> RAREWARE -> EYE -> GOLDENEYE_LOGO -> DISPLAY_CAST -> attract demo"*. The override
> jumps that entire sequence and calls `set_selected_difficulty()` /
> `set_solo_and_ptr_briefing()` by hand. **`[ASSUMED]` the front-end walk also
> initialises sequence/voice volume state that `MENU_RUN_STAGE` alone never sets —
> which is exactly `vol=[1,1]`, `target0=0`: voices allocated, envelope never
> configured.**
> **I INTRODUCED THE SHORTCUT IN §14/§15 AND THEN MEASURED ITS SIDE EFFECT AS IF IT
> WERE THE GAME.**

**`48` again, in a new costume: the instrument changed the thing it measured.**
The rule has always been *"one behaviour change per run"* — **an env var that
re-routes the boot path IS a behaviour change**, and three of them were added at
once alongside the audio probe.

### THE DISCRIMINATOR — 60 SECONDS, NO REBUILD, AND IT DECIDES EVERYTHING

```powershell
cd C:\Users\<USER>\Desktop\GoldenEyeVR\goldeneye-native\getv\build-windows
Remove-Item Env:GETV_MENU, Env:GETV_MENUSTAGE -ErrorAction SilentlyContinue
$env:GETV_LOGFLUSH="1"; $env:GETV_AUDIO_DEBUG="1"
.\goldeneye.exe *> run_front.log 2>&1
```
**`Remove-Item Env:` MATTERS: `$env:` vars PERSIST for the life of the PowerShell
window.** Every run since 19:51 inherited the previous run's settings, which is how
three variables accumulated without anyone choosing them together. **Open a fresh
window if in any doubt.**

**Click around the file-select / copy screen — the place the "machine gun" was
heard. Then close with X.**

| outcome | meaning |
|---|---|
| **`pkAll` > 0** | **the mixer is FINE.** §16 is fully retracted, `GETV_MENU=11` skips audio init, and the real bug list is the menu text + the explosion |
| **`pkAll` = 0** with sound audible | the probe is lying — instrument bug, not an audio bug |
| **`pkAll` = 0** and silent | **NOW §16's mixer analysis applies**, and it applies to the real boot path |

**NO MIXER WORK UNTIL THIS RUN EXISTS.** §16's `aSetVolumeImpl` lead is preserved
and still good **if and only if** the third row is what happens — and opening the
GE ENVMIXER ABI on the strength of a self-inflicted confound would be the most
expensive mistake available right now.

### WHAT SURVIVES §16 REGARDLESS

**Both exonerations hold, because both were measured on the mechanism and not on the
boot path:** the **§10 audio segment is correct** (ADPCM decodes to full-scale
32768 — the sample data is good however the game was entered), and **§13's
`GE_QUEUE_TARGET` is not the cause** (`q` reaching 1249-1256, `ovf=0`).

---

## §19 — 2026-08-27o: **§17 CONFIRMED. SOUND IS BACK. AND THE BINARY IS PROVEN GENUINE.**

`[REPORTED]` ***"sound is back but its really delayed and off."***

`[MEASURED]` `run_front.log` (7,092,856 B), no `GETV_MENU`, **same binary**:
```
rmsL=3074.1 rmsR=3077.8  pk=9828  nz=4190/4321  pkAll=32768
```
**Peak 32768, non-silent on 4190 of 4321 frames** — against §16's `pkAll=0` on
`0/1505`. **`GETV_MENU=11` WAS THE CONFOUND. §16 IS DEAD: `envmix` and
`aSetVolumeImpl` are fine and must not be touched.**

### ►► THE OWNER ASKED FOR PROOF THE EXE IS OURS. FOUR WAYS. ◄◄

**A fair question to ask after a retraction.** Recorded so it never has to be taken
on trust again:

**1. Exactly ONE `goldeneye.exe` exists on the disk.** `find` returns a single
path — **no stale copy can be run by accident.**

**2. PE subsystem = 3.** It was **2** when §13 measured it, and 3 is reachable
*only* through the `-mwindows` strip added to `build_windows.ps1`. **Every
non-empty `run*.log` re-proves it: a subsystem-2 build physically cannot write
one.**

**3. Build order is strictly correct:**
```
19:43:53  port_audio.c     (the GE_QUEUE_TARGET edit)
19:49:46  ...port_audio.o  (rebuilt AFTER the edit)
19:49:50  goldeneye.exe    (linked AFTER the object)
```

**4. AND THIS ONE IS CONCLUSIVE, BECAUSE IT READS THE CONSTANT'S EFFECT OUT OF THE
RUNNING PROCESS:**

| | queue ceiling |
|---|---|
| `GE_QUEUE_TARGET = FRAME_SAMPLES * 2` (ours) | **1472** |
| `* 4` (the old value) | 2944 |

**max `q=` observed — `run_lvl.log` 1466 · `run_front.log` 1469.**
> **Both sit just under 1472 and neither ever exceeds it.** Under the old `*4` the
> queue would climb toward 2944. **The new constant is not merely compiled in, it
> is observably governing the running binary. A timestamp can be coincidence; a
> ceiling cannot.**

### `[MEASURED]` THE LATENCY IS HALVED, NOT GONE — AND IT IS NOW TWO TERMS

| term | value |
|---|---|
| queue, sitting at `q≈1213-1221` | **~27.5 ms** |
| SDL device buffer, `want.samples = 512` | **23.2 ms** |
| **total** | **~51 ms** (was ~90) |

**`[MEASURED]` `ovf=0` and `fps=60`** — the queue never starves and the game is not
late, **so what remains is buffer depth, not performance.**

**`[READ]` the second term has never been touched:** `port_audio.c:521`
`want.samples = 512`, opened with `SDL_OpenAudioDevice(..., 0)` —
**`allowed_changes = 0`, so SDL grants exactly 512 and `have` cannot differ.**
`256` would halve it to 11.6 ms.
**`[NOT MEASURED]`: neither term's underrun floor. Lower them ONE AT A TIME —
`ovf` already counts the failure and is already in the log.**

### "AND OFF" IS A SECOND, SEPARATE FAULT — DO NOT FOLD IT INTO THE LATENCY

`[REPORTED]` *"delayed **and off**"*, with the earlier *"back out ... makes a
machine gun sound"*. **A wrong sound is not a late sound.** Latency is buffer
depth; a menu click producing a machine gun is **an index landing on the wrong
record**, and no buffer tuning touches it.
**`[UNDIAGNOSED]`. The instrument is `GETV_AUDIO_TESTSFX=<id>`
(`port_audio.c:252`) — plays one id on repeat, prints
`TESTSFX id=N -> started|REFUSED`. A handful of ids separates a constant offset
from a scramble, and that shape decides the fix. STILL NEVER RUN.**

### THE STANDING LIST

1. **menu text not drawn** — assets proven present (§14); **blocks normal play**
2. **sfx wrong index** ("off") — instrument ready, never run
3. **latency ~51 ms** — halved; two reducible terms, one run each
4. **purple explosion** — never yet seen in an instrumented run that reached
   gameplay legitimately
5. **`GETV_MENU=11` skips audio init** — `[MEASURED]`. **A property of the
   diagnostic, not a game bug. Never judge audio through it again.**

---

## §20 — THE PLAN. SESSION CLOSE 2026-08-27.

### ►►►►►► ITEM 0: **COMMIT. BEFORE ANYTHING ELSE. OWNER-ONLY.** ◄◄◄◄◄◄

**40+ documents overdue, and this session changed more real files than any before
it.** A working native build is the most valuable thing this project has produced
and **it exists only as untracked working-tree state.**

```powershell
.\commit-session.ps1     # at the main PC, NOT through the bridge (148 item 11)
```

**What changed on disk this session — all of it uncommitted:**

| file | change | § |
|---|---|---|
| `vendor/ge-decomp/scripts/filelist.u.csv` | **CRLF -> LF** (the root cause of everything) | §9 |
| `vendor/ge-decomp/assets/obseg/**/*.bin` | **550 files extracted from the ROM** | §9 |
| `assets/obseg/ge_obseg_blobs.c` | generated, **20.9 MB** | §9 |
| `assets/obseg/ge_obseg_sizes.c`, `ge_obseg_bg_sizes.h` | generated | §9 |
| `assets/music/ge_audio_segment.c` + `src/ge_audio_segment.h` | generated, **6.9 MB** | §10 |
| `assets/obseg/setup/u/UsetuplenZ.c` | double-prefix fix, 44 occurrences | §10 |
| `getv/build_windows.ps1` | `-mwindows` strip + `-GuiSubsystem` switch | §13 |
| `getv/port/src/port_audio.c` | `GE_QUEUE_TARGET *4 -> *2` | §13 |

**`.gitignore` note:** several generated files say *"do not commit"* in their own
headers and may be ignored. **That is fine and intended — but then
`SETUP.md` §3.5 IS the build artifact, and §9's two traps must be in it or a fresh
clone reproduces this entire session.** See item 5.

### THE ORDER, AND WHY IT IS THIS ORDER

#### 1. **THE MENU TEXT.** It blocks everything else.
**`[MEASURED]` the assets are NOT the problem** (§14): every front-end bank
(`LtitleE`, `LmiscE`, `LoptionsE`, `LmpmenuE`) loads `NATIVE (early-out)`, both
fonts convert with `0/94` bad glyphs, and there is **not one texture fault in
100,270 lines.** **The strings and the glyphs are present. They are not being
DRAWN.**
**So this is a RENDER-side question and the next step is a read, not a run:** find
the front-end text draw call and ask what makes it a no-op — a clip/scissor
rejection, a colour or alpha of zero, or a position off-screen. `[getv] SCISSOR
n64: (0,40)-(1280,920) => 320x230` appears in the logs and **is the first thing to
check against where the text is placed.**
**WHY FIRST: the owner cannot navigate his own game.** Every other symptom is
reached through this menu, and `GETV_MENU` is not a substitute — **§16/§17 proved
that skipping the front end silently changes behaviour and produces false
findings.**

#### 2. **THE WRONG SOUNDS.** Cheapest open item; the instrument already exists.
```powershell
$env:GETV_AUDIO_DEBUG="1"; $env:GETV_AUDIO_TESTSFX="<id>"   # no GETV_MENU
```
Prints `TESTSFX id=N -> started|REFUSED`. **Try a handful of ids and say what is
heard. A constant offset and a scramble need completely different fixes, and this
tells them apart in one sitting.** **`[UNDIAGNOSED]`, never run.**

#### 3. **THE LATENCY.** ~51 ms, two terms, both reducible, **one change per run**.
`[MEASURED]` queue ~27.5 ms + SDL `want.samples=512` ~23.2 ms; `ovf=0`, `fps=60`.
**Take `want.samples` to 256 first** (`port_audio.c:521`) — **it has never been
touched, while the queue term already moved once.** **`ovf` in the log is the
failure signal; if it leaves 0, the value was too low.**

#### 4. **THE PURPLE EXPLOSION.** Still never observed in a legitimate instrumented run.
**`[MEASURED]` it is NOT a missing texture** — 0 `NULL texture`, 0 `could not load
texture`, every `modeltex` line `0 MISSING`, and the pink/black marker is
unreachable without a `could not load texture` line first (§14). **Suspect an
untextured or miscoloured surface, i.e. a combiner/blend path, not an absent
asset.** **Needs item 1 first** so it can be reached without `GETV_MENU`.

#### 5. **FOLD §9's TWO TRAPS INTO `SETUP.md` §3.5.** Cheap, and it is the
difference between a reproducible port and a one-off.
- **normalise the CSVs, not just the `.sh` files** — git autocrlf on Windows
  re-breaks `filelist.u.csv` on every fresh clone
- **`filelist.u.csv` is `offset,size,name,compressed,extract`** — `extract` is
  **column 4**; reading column 3 sends you to the wrong `SETUP.md` section
- and `uniquify_asset_symbols.py`'s two portability bugs (§4: `clang -O1`,
  and `globals_of` requiring a leading `_`) are **still unfixed in the vendored
  tool** — they were worked around, not repaired

#### 6. **THEN PHASE 1 — STEREO** (`228` §5). Unchanged and unblocked.

### THE METHOD LESSON OF THIS SESSION, AND IT COST TWO RETRACTIONS

> **EVERY BLOCKER IN §1-§11 WAS A BUILD-PIPELINE FAULT, NOT A CODE FAULT.** Symlinks
> checked out as text · uniquify never run · **CRLF making the ROM extraction skip
> 812 of 812 rows and exit 0** · a double-applied prefix. **Not one line of game
> logic was wrong.**

> **AND THE TWO WRONG TURNS WERE BOTH MINE, BOTH THE SAME SHAPE: I TRUSTED A
> SUMMARY OVER THE MECHANISM.** §15 read the MENU enum out of a code COMMENT that
> omitted `9 MENU_007_OPTIONS` instead of out of `bondconstants.h` — off by one,
> one wasted run. §16 read `envmix=0` and blamed the mixer **without a control**,
> when the zero was produced by `GETV_MENU=11`, a shortcut **I had introduced one
> section earlier.** `168`'s rule in new costumes.
> **`48` needs restating for env vars: AN ENVIRONMENT VARIABLE THAT RE-ROUTES THE
> BOOT PATH IS A BEHAVIOUR CHANGE.** Three accumulated silently because PowerShell
> `$env:` persists for the life of the window. **`Remove-Item Env:GETV_*` between
> runs, or use a fresh window.**

> **AND THE OWNER WAS RIGHT BOTH TIMES HE CONTRADICTED ME** — *"That doesnt happen
> on this build"* (the X-close crash is recomp-era) and *"There was a run before
> this it all worked"* (which killed §16). **`HANDOVER` §5's rule holds without
> exception across this session.**
