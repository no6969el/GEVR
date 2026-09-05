> **Build-phase note (2026-09-05):** This doc is part of the *ideas trail*.
> The playable GETV VR workshop (gevr_*, working XR frame loop in the game
> process, drop-in patch series) is **not** published yet — see
> `docs/RELEASE-POLICY.md`. Use this to re-derive, not to clone a finished VR build.
# Replicating this tree from a clean clone

Assumes Windows x64. Toolchain versions that are known to work are in
`02-windows-build-notes.md`; **clang must be 18.1.8**, not 22.

```powershell
git clone --recurse-submodules https://github.com/cblock85/GoldenEye64Recomp.git
cd GoldenEye64Recomp

# Two submodules are declared or expected but never actually committed
git clone --depth 1 https://github.com/ubawurinna/freetype-windows-binaries.git lib/freetype-windows-binaries
git clone --depth 1 https://github.com/mupen64plus/mupen64plus-win32-deps.git lib/rt64/src/contrib/mupen64plus-win32-deps

# The decompilation headers the patches build against
git submodule update --init lib/ge
#   (if that fails: git clone --depth 1 https://github.com/n64decomp/007.git lib/ge)

# dxc Windows binaries â€” vendored copy has Linux/macOS only. Use dxc-bin HEAD.
git clone https://github.com/rt64/dxc-bin.git $env:TEMP\dxc-bin
Copy-Item $env:TEMP\dxc-bin\bin\x64\dxc.exe        lib\rt64\src\contrib\dxc\bin\x64\ -Force
Copy-Item $env:TEMP\dxc-bin\bin\x64\dxcompiler.dll lib\rt64\src\contrib\dxc\bin\x64\ -Force
Copy-Item $env:TEMP\dxc-bin\bin\x64\dxil.dll       lib\rt64\src\contrib\dxc\bin\x64\ -Force
Copy-Item $env:TEMP\dxc-bin\lib\x64\dxcompiler.lib lib\rt64\src\contrib\dxc\lib\x64\ -Force
```

Then apply everything in `diffs/` and copy `patches/*.c` into `patches/`, and drop
`tools_weaken_patched.py` over the upstream one.

```powershell
# Build the recompiler tools (note: N64RecompCLI, NOT N64Recomp â€” see GOTCHA 4)
cmake -S n64recomp-src -B n64recomp-src\build -DCMAKE_BUILD_TYPE=Release "-DCMAKE_POLICY_VERSION_MINIMUM=3.5"
cmake --build n64recomp-src\build --target N64RecompCLI --config Release
cmake --build n64recomp-src\build --target RSPRecomp   --config Release
Copy-Item n64recomp-src\build\Release\N64Recomp.exe .\N64Recomp.exe -Force
Copy-Item n64recomp-src\build\Release\RSPRecomp.exe .\RSPRecomp.exe -Force

# Place the ROM (converted retail NTSC-U) in the repo root as ge007.tlbfree.z64
#   sha1 e6e7bbcd4e16c8d83fbc86765aad9579a07d068c

.\RSPRecomp.exe aspMain.us.toml     # generates rsp/aspMain.cpp â€” GOTCHA 6
.\N64Recomp.exe us.toml             # expect: Function count: 3150
py tools_weaken_patched.py          # renames rather than weakens on Windows â€” GOTCHA 9

cmake -S . -B build "-DCMAKE_POLICY_VERSION_MINIMUM=3.5"
cmake --build build --target GoldenRecomp --config Release --parallel
```

## Running it

Assets are loaded by **relative path**, so the working directory must be the repo
root â€” MSBuild puts the exe in `build\Release\` which breaks that. Launch by path:

```powershell
cd C:\Users\<USER>\Desktop\GoldenEye64Recomp
.\build\Release\GoldenRecomp.exe
```

## Ordering trap

`tools_weaken_patched.py` filters its rename list against
`RecompiledPatches/patches.c` to skip the 14 `#if 0` patches. That file does not
exist on a first build. Run the script, build once (it may fail to link), then run
the script again and rebuild. Subsequent runs are fine.

## Verification checkpoints

If any of these disagree, stop and investigate before continuing:

| Step | Expected |
|---|---|
| `.\N64Recomp.exe us.toml` | `Function count: 3150` |
| `py tools_weaken_patched.py` | 24 renamed, 14 skipped as not emitted |
| `RecompiledFuncs` compile | No `C2143`/`C2082`/`C2091` â€” those mean weak symbols survived |
| `GoldenRecomp` link | No `LNK2001` on any renamed name |
| First run | Front end normal, levels visibly wider than stock GoldenEye |

## Toggles for bisecting

| Define | Effect when 0 |
|---|---|
| `GE_BT_ENABLED` | Phase 0 hook compiled in but image untouched (call counters still tick) |
| `GE_INTERP_ROOMS` | Room tagging off |
| `GE_INTERP_PROPS` | Prop/character tagging off |
| `GE_INTERP_HUD` | Gauge-bar tag off (body still replaced) |
| `GE_INTERP_VIEWMODEL_FENCE` | View-model fence off |
| `GE_UNTAGGED_WORLD_IS_IGNORE` | RT64 reverts to content-hash matching for untagged world matrices |
| `GE_FORCE_WEAK=1` (env) | `tools_weaken_patched.py` uses weak symbols even on Windows |
