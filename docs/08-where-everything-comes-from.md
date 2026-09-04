# Where everything comes from

Every input this project needs, and how to obtain it. Nothing here is optional
unless marked so.

## 1. The two repositories

This project spans **two** repos. Confusing them has already cost one documentation
error, so be precise.

| | `GoldenEye64Recomp` | `goldeneye-native` |
|---|---|---|
| Source | `github.com/cblock85/GoldenEye64Recomp` | `github.com/no6969el/goldeneye-native` |
| On disk | `C:\Users\pdbar\Desktop\GoldenEye64Recomp` | **not on the rig** — see §2 |
| Licence | mixed; links GPL-3.0 `N64ModernRuntime` | MIT |
| Role | the thing that builds and runs | the design/spec repo + host-agnostic harness |
| Holds | `patches/ge_vr_bindtest.c`, `patches/interpolation.c` | `VR-PLAN.md`, `PRIOR-ART.md`, `VENDORING.md`, `phase0/`, `include/ge_vr/`, `src/ge_vr_bridge.cpp` |

**The recomp host is GPL-3.0 and stays external. Never vendor it into the MIT
repo.** That constraint is the reason the two repos exist.

`geVrBuildProjectionF` and the original `GE_VR_MIN_ZNEAR_UNITS` live in
**goldeneye-native**, not the recomp tree. `ge_vr_bindtest.c` on the rig defines
its own copy of the constant deliberately — patch space cannot see the host repo.

## 2. Recovering goldeneye-native — DONE, kept as the record

> **RESOLVED 2026-08-22, verified live against GitHub.** This section's urgency
> is spent and later handoffs kept repeating it. `git ls-remote origin main` and
> the local `main` are both `0aa0ddb` — **the work is pushed.** It is also
> committed inside the recomp repo as the bundle named below.
>
> The recovery procedure is kept because it is correct and because the bundle is
> still a good backup. **But it is no longer urgent, and it is no longer the only
> copy.** Do not spend a session rescuing it.

The Phase 0 harness, the VR-PLAN §6 rewrite and the PRIOR-ART licence audit were
written into a **cloud container that is destroyed when the session ends**. They
were written there and, at the time this was first written, existed only as:

```
ge-vr-handoff/goldeneye-native/goldeneye-native.bundle       (self-contained git repo)
ge-vr-handoff/goldeneye-native/goldeneye-native-phase0.patch (same, as a readable patch)
```

The bundle contains full history through commit `0aa0ddb`, one commit ahead of
upstream `fcfb5b6`. To restore:

```powershell
git clone goldeneye-native.bundle goldeneye-native
cd goldeneye-native
git remote set-url origin https://github.com/no6969el/goldeneye-native.git
git log --oneline -2      # expect 0aa0ddb on top of fcfb5b6
git push origin main      # already done - main is 0aa0ddb on the remote
```

Or, against an existing clone: `git am goldeneye-native-phase0.patch`.

**1,116 insertions across 14 files.** Contents: `phase0/` bind-test harness (C89,
host-agnostic, selftest 9/9), `phase0/adapters/ge64recomp/ge_vr_bindtest.c` (the
ancestor of the rig's patch), `GE_VR_MIN_ZNEAR_UNITS` in `include/ge_vr/ge_vr.h`,
its enforcement in `src/ge_vr_bridge.cpp`, a corrected comment in
`tools/room_render.cpp`, and the VR-PLAN/PRIOR-ART rewrites.

## 3. Third-party source that is declared but NOT committed

`cblock85` flattened several RT64 submodules into plain directories and the
Windows halves did not come along. `git clone --recurse-submodules` will not get
these; fetch them by hand.

| What | Where from | Why needed |
|---|---|---|
| `lib/freetype-windows-binaries` | `github.com/ubawurinna/freetype-windows-binaries` | declared in `.gitmodules`, never a real gitlink (GOTCHA 2) |
| `lib/rt64/src/contrib/mupen64plus-win32-deps` | `github.com/mupen64plus/mupen64plus-win32-deps` | RT64 needs `SDL.h` (GOTCHA 8) |
| dxc Windows binaries | `github.com/rt64/dxc-bin` — **HEAD**, not RT64's pinned `cc15e71` | vendored dxc is Linux/macOS only (GOTCHA 5). Header sha256 `f8487a55…` matches v1.8.2407+ |
| `lib/ge` | `github.com/n64decomp/007` | decomp headers the patches compile against. This one IS a real gitlink |

Real submodules that clone normally: `N64ModernRuntime` (kholdfuzion), `RmlUi`
(mikke89), `lunasvg` (sammycage), `sse2neon` (DLTcollab), `rt64` (rt64).

## 4. Toolchain

Exact versions in `02-windows-build-notes.md`. The one that bites:

```powershell
winget install LLVM.LLVM --version 18.1.8   # NOT 22 — no MIPS flags (see notes)
winget install Kitware.CMake
winget install --id Microsoft.VisualStudio.2022.BuildTools --override "--add Microsoft.VisualStudio.Workload.VCTools"
# make: via MSYS2, Chocolatey, or GnuWin32
```

**PATH:** winget does not add LLVM to PATH, and an automated shell does not
inherit whatever your interactive session has. `make` missing from PATH reports as
`no such file or directory`, which reads like a missing source file and is not.
See `07-rebuild-after-patch-edit.md`.

## 5. The ROM

Supplied by the user; **never committed, never transmitted**.

- Input: their own retail **NTSC-U** GoldenEye 007 cartridge dump.
- Working file: `ge007.tlbfree.z64` in the repo root,
  sha1 `e6e7bbcd4e16c8d83fbc86765aad9579a07d068c`, 12,653,664 bytes.
- Conversion: `vanilla_to_tlbfree.xdelta` / `.gep1`, both already in the repo root.
  The converted file is already on the rig, so **xdelta3 is not needed on Windows**.
- The launcher's ROM picker also converts automatically if given a vanilla dump.

## 6. Fetched at configure time — needs network

`gamecontrollerdb.txt`, pinned to commit `b1e4090b3d4266e55feb0793efa35792e05faf66`
of `gabomdq/SDL_GameControllerDB`, downloaded by `CMakeLists.txt:162`. SDL2 arrives
via FetchContent (2.30.3), while RT64 links the vendored 2.26.3 — a known latent
skew, first suspect for odd input or audio behaviour.

## 7. Generated, not stored — must exist before GoldenRecomp links

`RecompiledFuncs/`, `RecompiledPatches/`, `rsp/aspMain.cpp`, `patches/patches.elf`,
`patches/patches.bin`, `N64Recomp.exe`, `RSPRecomp.exe`.
Regeneration order is in `06-replicate.md`, including the run-the-script-twice
ordering trap.

## 8. Reverting anything

Every third-party edit has a backup beside it and a diff in `diffs/`:
`.bak` = original, `.bak2` = pre-MSVC-flag-guard, `.bakweak` = pre-rename
(31 files under `RecompiledFuncs/`). `patches/ge_vr_bindtest.c.bak` is the Phase 0
cot-scale version, though `-DGE_VR_MODE=GE_VR_MODE_BINDTEST` reaches that path
without swapping files.

Two more from 2026-08-22, both in `patches/`:
`interpolation.c.bak` is the original upstream `#if 0` stub (384 bytes — it is not
a backup of our work, do not restore it expecting the five slices back);
`interpolation.c.bak2` is the pre-slice-6 version, the real revert target.
Slice 6 also reverts in place with `-DGE_INTERP_BULLET_IMPACTS=0`.

## 9. Not obtainable — deliberately

Per `VENDORING.md` §1 rule 3, nothing under a proprietary notice is vendored
regardless of the containing LICENSE. This ruled out libultra's `perspective.c`
and `mtxutil.c` (SGI notice); the fixed-point matrix code is reimplemented from
`PR/gbi.h`'s documented layout instead. Do not "fix" this by copying libultra.

## 10. Two bugs found in the build tooling itself, 2026-08-22

Both were latent and both now fixed in this folder's copies. Flagged here because
they present as broken *inputs* rather than as broken code.

- **`tools_weaken_patched.py` used `WEAK_SUPPORTED` sixteen lines before defining
  it.** Every run on Windows died with `NameError` before touching a file, so the
  `#if 0` filtering block it guards had never actually executed. Fixed by hoisting
  the definition above its first use. The filter now runs and reports 13 skipped
  names.
- **Bare `make` in `patches/` links with `ld`, not `ld.lld`.** `LD` is a GNU make
  built-in variable, so the Makefile's `LD ?= ld.lld` never takes effect. CMake's
  `PatchesBin` target passes `LD=` in the environment and is therefore fine; a
  hand-run `make` is not. Always `make CC=clang LD=ld.lld`. The failure is
  `CreateProcess(NULL, ld ...) failed` — which reads like a linker crash and is a
  missing binary.
