# Building GoldenEye64Recomp on Windows — undocumented gotchas

Upstream supports macOS/Linux only. The Windows paths in CMake are intact (inherited from
goldenrecomp) but untested, so these all had to be found the hard way. Rig: `simrig`,
Windows x64, NVIDIA. Repo at `C:\Users\pdbar\Desktop\GoldenEye64Recomp`.

**Status 2026-08-22: configure succeeds; recompiler, patch assembly and RT64 all build.
Nine Windows-only breakages found and fixed. Awaiting the `GoldenRecomp` link.**

## Toolchain (verified working)

| Tool | Version | Note |
|---|---|---|
| VS Build Tools 2022 | 17.14.39 / MSVC 19.44 | `Microsoft.VisualStudio.Workload.VCTools` |
| clang | **18.1.8** | MIPS backend present; verified compiling with the real flags |
| ld.lld / llvm-objcopy | 18.1.8 | |
| CMake | 4.4.2 | needs policy flag, see below |
| make | 4.4.1 | |
| Python | 3.13.3 / 3.12.10 | **use `py`**, `python` is hijacked by the Store alias |
| git | 2.55.0 | |

### clang 22 does NOT work

`winget install LLVM.LLVM` gives 22.1.8, which fails on the patches Makefile flags:

```
Unknown command line argument '-mips-ssection-threshold=0'
Unknown command line argument '-mgpopt'
```

Pin to 18.1.8: `winget install LLVM.LLVM --version 18.1.8`. Uninstall 22 first or the
installer exits with code 2. Winget does NOT add LLVM to PATH — add
`C:\Program Files\LLVM\bin` manually.

Verify with: `clang --print-targets` (want `mips`), then

```
clang -target mips -mips2 -mabi=32 -G0 -mno-abicalls -mno-odd-spreg -c t.c -o t.o
```

## GOTCHA 1 — CMake 4 rejects this project

Many CMakeLists declare pre-3.5 minimums (`n64recomp-src` itself, `fmt`, `tomlplusplus`,
`lunasvg` at 3.3). CMake 4 hard-errors. Add to EVERY configure:

```
"-DCMAKE_POLICY_VERSION_MINIMUM=3.5"
```

**Quote it.** Unquoted, PowerShell splits on the dot and CMake receives `3`:
`Invalid CMAKE_POLICY_VERSION_MINIMUM value "3"`.

## GOTCHA 2 — freetype-windows-binaries is declared but never committed

`.gitmodules` declares `lib/freetype-windows-binaries`, but `git ls-files -s lib/` shows only
ONE real gitlink: `lib/ge`. Everything else (rt64, RmlUi, lunasvg, sse2neon, N64ModernRuntime)
is committed directly. freetype-windows-binaries is neither — so
`git submodule update --init lib/freetype-windows-binaries` fails with
"pathspec did not match any file(s) known to git".

Fix — clone it directly:

```
git clone --depth 1 https://github.com/ubawurinna/freetype-windows-binaries.git lib/freetype-windows-binaries
```

## GOTCHA 3 — FindFreetype.cmake points at a path upstream deleted

`lib/FindFreetype.cmake` (only loaded on Windows, via CMakeLists:33 adding `lib/` to
CMAKE_MODULE_PATH) hardcodes `release static/vs2015-2022/win64/freetype.lib`.
Current upstream layout is `release static/vs2026/{x64,x86,arm64}/`. Patched on the rig;
original kept as `FindFreetype.cmake.bak`.

Configure now passes. **Still unproven at link time:** that lib is built with the VS2026
toolset and we link with VS2022 (v144). Fallback if the linker objects — switch
`FREETYPE_LIBRARIES` to `release dll/x64/freetype.lib` and copy `freetype.dll` beside the exe.

## GOTCHA 4 — target `N64Recomp` is a LIBRARY, not the executable

`n64recomp-src/CMakeLists.txt`: `add_library(N64Recomp)` at :86, `add_executable(N64RecompCLI)`
at :123 with `set_target_properties(N64RecompCLI PROPERTIES OUTPUT_NAME N64Recomp)` at :135.

With Ninja on Linux, `ninja N64Recomp` resolves to the output *file* and builds the exe — which
is why `build_linux.sh` works. With MSBuild, `--target N64Recomp` builds the library and you
get `N64Recomp.lib` and no exe. **On Windows build `--target N64RecompCLI`**; the output is
still named `N64Recomp.exe`.

Generator-dependent target resolution — expect the same trap for any other target that script names.

## GOTCHA 5 — vendored dxc has no Windows binaries

`lib/rt64/src/contrib/dxc/` ships only `dxc-linux`, `dxc-macos`, `.so` and `.dylib`. Configure
fails with:

```
CMake Error: File .../dxc/bin/x64/dxcompiler.dll does not exist.
CMake Error: File .../dxc/bin/x64/dxil.dll does not exist.
```

In upstream RT64, `src/contrib/dxc` is a **submodule** of `https://github.com/rt64/dxc-bin`.
cblock85 vendored RT64 as plain directories and the Windows half didn't come along.

Version matters. Their vendored `inc/dxcapi.h` is sha256 `f8487a55…`, which matches dxc-bin
commits `0cffb90` (v1.8.2407) through HEAD `7810655` — NOT the `cc15e71` (v1.8.2403.2) that
upstream RT64 pins. So use **dxc-bin HEAD**, whose headers match. (Their Linux binaries are
custom rebuilds and don't match any dxc-bin commit — irrelevant, since headers determine ABI.)

```
git clone https://github.com/rt64/dxc-bin.git $env:TEMP\dxc-bin
Copy-Item $env:TEMP\dxc-bin\bin\x64\dxc.exe        lib\rt64\src\contrib\dxc\bin\x64\ -Force
Copy-Item $env:TEMP\dxc-bin\bin\x64\dxcompiler.dll lib\rt64\src\contrib\dxc\bin\x64\ -Force
Copy-Item $env:TEMP\dxc-bin\bin\x64\dxil.dll       lib\rt64\src\contrib\dxc\bin\x64\ -Force
Copy-Item $env:TEMP\dxc-bin\lib\x64\dxcompiler.lib lib\rt64\src\contrib\dxc\lib\x64\ -Force
```

## GOTCHA 6 — rsp/aspMain.cpp is generated, and the standard build path never generates it

`rsp/` contains only `.gitignore`. `CMakeLists.txt:453` requires `rsp/aspMain.cpp`
unconditionally, but `build_linux.sh` only runs `RSPRecomp` in its `--clean` branch. Upstream
doesn't notice because their working trees already have the file from an earlier clean build.

```
cmake --build n64recomp-src\build --target RSPRecomp --config Release
Copy-Item n64recomp-src\build\Release\RSPRecomp.exe .\RSPRecomp.exe -Force
.\RSPRecomp.exe aspMain.us.toml
```

Reads a 3.5 KB RSP microcode slice at ROM offset `0x22C80` and writes `rsp/aspMain.cpp`.

## GOTCHA 7 — GCC warning flags are passed unconditionally to MSVC

`CMakeLists.txt`, `lib/N64ModernRuntime/ultramodern/CMakeLists.txt` and
`lib/N64ModernRuntime/librecomp/CMakeLists.txt` add `-Wno-unused-variable` and friends with no
compiler guard. MSVC parses `-W...` as `/W...`:

```
cl : Command line error D8021: invalid numeric argument '/Wno-unused-variable'
```

Fix — wrap each in a generator expression (6 replacements across the 3 files, backups `.bak2`):

```
$<$<NOT:$<BOOL:${MSVC}>>:-Wno-unused-variable>
```

**Do this with Python, not `sed`.** These files are CRLF; a naive `sed` pattern that ends at
the flag silently matches nothing and reports success.

## GOTCHA 8 — `mupen64plus-win32-deps` (SDL) is not vendored either

RT64's Windows build fails with `Cannot open include file: 'SDL.h'`. Same cause as GOTCHA 5 —
a submodule that didn't survive being flattened into plain directories.

```
git clone --depth 1 https://github.com/mupen64plus/mupen64plus-win32-deps.git lib/rt64/src/contrib/mupen64plus-win32-deps
```

Ships SDL2 2.26.3 with `include/` and `lib/x64`. **Watch for a version skew:** RT64 links
2.26.3 while the top-level FetchContent copies 2.30.3's DLL beside the exe. If SDL misbehaves
at runtime, that's the first thing to check.

## GOTCHA 9 — `__attribute__((weak))` does not exist in MSVC (blocked the whole build)

`tools_weaken_patched.py` marks the recompiled originals of every `RECOMP_PATCH`'d function
weak so the strong definition in `PatchesLib` wins at link time. Its own docstring scopes this
to "GNU ld, lld, and Apple ld64" — MSVC is not on that list, and it doesn't parse the
attribute at all. The result is hundreds of errors in `RecompiledFuncs`, all of the same shape:

```
funcs_36.c(3981,27): error C2143: syntax error: missing ')' before '('
funcs_36.c(3981,40): error C2082: redefinition of formal parameter 'currentPlayerSetProjectionMatrixF'
funcs_36.c(3981,13): error C2091: function returns function
funcs_36.c(3981,...): error C2065: 'ctx': undeclared identifier
```

This affects all **38** weakened functions — upstream's own 36 as well as our 2 — so it is a
fundamental upstream Windows incompatibility, not something the VR bind test introduced.

**Fix — rename instead of weaken.** If the recompiled original is renamed, there is only one
definition of the symbol left in the link (the strong one in `PatchesLib`), so every call site
resolves to the patch. That is exactly what `RECOMP_PATCH` is supposed to mean; weak symbols
were only ever one way to get there.

```
RECOMP_FUNC __attribute__((weak)) void NAME(uint8_t* rdram, recomp_context* ctx)
→ RECOMP_FUNC void NAME__recomp_orig(uint8_t* rdram, recomp_context* ctx)
```

`tools_weaken_patched.py` now does this automatically on Windows (`os.name == "nt"`), keeping
the weak path everywhere else; set `GE_FORCE_WEAK=1` to override. Backup: `.py.bak`. The 38
already-generated sites were rewritten in place, each file backed up as `.c.bakweak`.

The renamed originals stay in the binary, unreferenced — harmless, and useful later if a patch
ever wants to call through to vanilla behaviour.

## Files placed on the rig

- `ge007.tlbfree.z64` (repo root) — sha1 `e6e7bbcd4e16c8d83fbc86765aad9579a07d068c`, converted
  in the cloud from the user's own ROM; means xdelta3 is NOT needed on Windows.
- `patches/ge_vr_bindtest.c` — the Phase 0 bind test.

## Checkpoints hit on the rig (all matched the cloud run exactly)

- `.\N64Recomp.exe us.toml` → **`Function count: 3150`**, same three `[Info]` lines.
- `py tools_weaken_patched.py` → **`weakened 38 patched functions across 31 files`** +
  `applied cosf fallthrough fix in RecompiledFuncs\funcs_20.c`.
- Verified on disk: `funcs_36.c` and `funcs_59.c` carried the two projection setters;
  `camGetWorldToScreenMtxf` and `currentPlayerGetProjectionMatrixF` did not.
- `PatchesBin` — the bind test compiled to MIPS with clang 18 and linked into `patches.elf`;
  N64Recomp regenerated 347 patch functions from it.

## Full Windows build order

```
git clone --recurse-submodules https://github.com/cblock85/GoldenEye64Recomp.git
git clone --depth 1 https://github.com/ubawurinna/freetype-windows-binaries.git lib/freetype-windows-binaries
git clone --depth 1 https://github.com/mupen64plus/mupen64plus-win32-deps.git lib/rt64/src/contrib/mupen64plus-win32-deps
# patch lib/FindFreetype.cmake     (GOTCHA 3)
# copy dxc Windows binaries        (GOTCHA 5)
# guard the -Wno-* flags for MSVC  (GOTCHA 7)
# place ge007.tlbfree.z64 in repo root, ge_vr_bindtest.c in patches/
cmake -S n64recomp-src -B n64recomp-src\build -DCMAKE_BUILD_TYPE=Release "-DCMAKE_POLICY_VERSION_MINIMUM=3.5"
cmake --build n64recomp-src\build --target N64RecompCLI --config Release
cmake --build n64recomp-src\build --target RSPRecomp   --config Release
Copy-Item n64recomp-src\build\Release\N64Recomp.exe .\N64Recomp.exe -Force
Copy-Item n64recomp-src\build\Release\RSPRecomp.exe .\RSPRecomp.exe -Force
.\RSPRecomp.exe aspMain.us.toml
.\N64Recomp.exe us.toml
py tools_weaken_patched.py          # renames rather than weakens on Windows (GOTCHA 9)
cmake -S . -B build "-DCMAKE_POLICY_VERSION_MINIMUM=3.5"
cmake --build build --target GoldenRecomp --config Release --parallel
```

## Still-unproven risks

1. freetype VS2026 lib vs VS2022 link (GOTCHA 3).
2. SDL2 2.26.3 (RT64) vs 2.30.3 (the DLL copied beside the exe) — GOTCHA 8.
3. CMake runs `./N64Recomp patches.toml` with a Unix-style path — may not resolve on Windows.
   Workaround: run `.\N64Recomp.exe patches.toml` by hand.
