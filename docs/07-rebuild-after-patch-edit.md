> **Build-phase note (2026-09-05):** This doc is part of the *ideas trail*.
> The playable GETV VR workshop (gevr_*, working XR frame loop in the game
> process, drop-in patch series) is **not** published yet — see
> `docs/RELEASE-POLICY.md`. Use this to re-derive, not to clone a finished VR build.
# Rebuilding after editing a file in `patches/` â€” verified 2026-08-22

The full build order in `02-windows-build-notes.md` is for a cold start. This is
the inner loop: you changed a `.c` in `patches/` and want a new exe. Verified
working end to end on `simrig`.

## The one-liner

```powershell
$env:PATH = "C:\Program Files\LLVM\bin;C:\Program Files\CMake\bin;C:\Users\<USER>\AppData\Local\Microsoft\WinGet\Links;" + $env:PATH
cd C:\Users\<USER>\Desktop\GoldenEye64Recomp
cmake --build build --target GoldenRecomp --config Release --parallel
```

That is all. CMake's `PatchesBin` target runs `make` in `patches/`, the
`patches.elf` byproduct triggers `./N64Recomp patches.toml`, and the regenerated
`RecompiledPatches/` feeds the link. Roughly a minute when only the patch changed.

## GOTCHA 1 â€” the PATH line is not optional

`clang`, `cmake` and `make` are all installed but **none of them are on the PATH
that a tool-driven or long-lived shell inherits.** LLVM and CMake were added to
PATH manually after that environment was captured, and `make` lives in
`%LOCALAPPDATA%\Microsoft\WinGet\Links`, which winget adds to the *user* PATH.

Symptom: `The term 'cmake' is not recognized`, or a build that dies with

```
no such file or directory
error MSB8066: Custom build for '...\PatchesBin.rule' exited with code 1
```

That "no such file or directory" is `make` missing, not a missing source file.
It is the single most misleading error in this build and it costs half an hour if
you read it literally. A freshly opened interactive terminal usually has the right
PATH; anything automated usually does not. Just set it explicitly.

## GOTCHA 2 â€” bare `make` links with the wrong linker

If you run `make` in `patches/` by hand rather than through CMake, it links with
`ld`, not `ld.lld`, and fails:

```
process_begin: CreateProcess(NULL, ld audio.o boot.o ... -o patches.elf, ...) failed.
make (e=2): The system cannot find the file specified.
```

Reads like a linker crash. It is a missing binary. **`LD` is a GNU make built-in
variable**, preset to `ld`, so the Makefile's `LD ?= ld.lld` never takes effect â€”
`?=` only assigns when the variable is unset, and make has already set it. CMake's
`PatchesBin` passes `LD=` through `cmake -E env`, which overrides the built-in, so
the CMake path is fine and only the hand-run path breaks.

Always: `make CC=clang LD=ld.lld`.

## GOTCHA 3 â€” `tools_weaken_patched.py` had never actually run its filter

Fixed 2026-08-22; the corrected copy is in this folder. The script used
`WEAK_SUPPORTED` sixteen lines before defining it, so every run on Windows died
with `NameError: name 'WEAK_SUPPORTED' is not defined` â€” before touching a single
file. The `#if 0` filtering block that flag guards had therefore never executed,
and the rename state on disk came from an older version of the script.

The definition is now hoisted above its first use. A correct run prints:

```
weak symbols supported: False
skipping (not emitted into patches.elf, likely #if 0): bgDebPrintROOMID, ... (13 names)
weakened 29 patched functions across N files
```

Note the doc set says *fourteen* `#if 0` patches; the filter now reports
**thirteen**. The old count predates the filter ever running. Trust the script.

## RESOLVED â€” `./N64Recomp patches.toml` works on Windows

`02-windows-build-notes.md` listed as unproven risk #3 that CMake invokes
`./N64Recomp patches.toml` with a Unix-style path that might not resolve. **It
resolves.** PowerShell accepts `./N64Recomp` and finds `N64Recomp.exe`. No manual
workaround is needed. Delete that risk.

## GOTCHA 4 â€” `--target` skips CMake regeneration, silently

**Added a source file, or edited `CMakeLists.txt`?** The one-liner will build
happily and ignore your change completely.

```powershell
cmake --build build --target GoldenRecomp --config Release --parallel
```

MSBuild only re-runs CMake as part of the `ZERO_CHECK` target, and naming a
specific target excludes it. The build then reuses stale project files and
**succeeds** - which is the worst available failure. Symptom: the new `.cpp` has
no object file anywhere under `build\`, new libraries are not linked, and any
`add_custom_command(POST_BUILD ...)` never fires.

It cost one round in step 3f-1, where a whole new OpenXR translation unit was
silently omitted and the resulting exe ran fine with none of the new code in it.

Reconfigure explicitly first. It reuses the cache, takes about a second, and
changes no configuration:

```powershell
cmake -S . -B build
cmake --build build --target GoldenRecomp --config Release --parallel
```

Editing existing source files does **not** need this, which is why it took until
the twelfth build of the project to appear.

## When you must do more than the one-liner

**Added a new `RECOMP_PATCH` *name*** (not just new code inside an existing
patched function): you must re-run the rename script, and the order matters,
because the script filters against what N64Recomp actually emitted:

```powershell
cd patches; make CC=clang LD=ld.lld; cd ..
.\N64Recomp.exe patches.toml
py tools_weaken_patched.py
cmake --build build --target GoldenRecomp --config Release --parallel
```

Re-running the script is safe and idempotent: it rewrites
`RECOMP_FUNC void NAME(` to `RECOMP_FUNC void NAME__recomp_orig(`, which no longer
matches once renamed. Interpolation slice 6 changed exactly one file for that
reason â€” the other 28 names were already done.

It does **not** create the `.bakweak` backups â€” those were made by hand â€” so there
is nothing to clobber.

**First build in a clean tree:** the ordering trap in `06-replicate.md` applies â€”
the script filters against `RecompiledPatches/patches.c`, which does not exist
yet. Run the script, build once, run it again.

## Checkpoints, for comparison

```
patches.toml  -> Function count: 347   (before Phase 1 step 1)
              -> Function count: 382   (after step 1)
              -> Function count: 385   (after interpolation slice 6)
```

If the count does not move after you edited a patch, `make` failed and you are
recompiling a stale `patches.elf` â€” check for GOTCHA 2. `N64Recomp` will happily
succeed against the old elf and report the old count. This is how a broken build
disguises itself as a working one.

A patch-only rebuild should touch `patches/patches.elf`,
`RecompiledPatches/patches.c` and `build\Release\GoldenRecomp.exe`, in that order,
within seconds of each other. If `GoldenRecomp.exe` is older than `patches.elf`,
the link did not pick up the change.

## Verifying a new patch actually bound

```powershell
Select-String -Path RecompiledFuncs\funcs_*.c -Pattern 'yourFunctionName'
```

You want to see two things: the definition renamed to
`yourFunctionName__recomp_orig` in one file, and an unrenamed *call* to
`yourFunctionName` in another. The call site resolving to the unrenamed symbol is
what makes the link pick the patch rather than the original.

For slice 6 that was `funcs_32.c` (definition, renamed) and `funcs_38.c` (the
recompiled `bg.c`, calling through). If you see the rename but no call site, the
function is dead code and your patch will never run.

## Compiling one patch TU alone, for a fast syntax check

Faster than a build when you only want to know whether it parses:

```powershell
cd C:\Users\<USER>\Desktop\GoldenEye64Recomp\patches
& 'C:\Program Files\LLVM\bin\clang.exe' -target mips -mips2 -mabi=32 -O2 -G0 `
  -mno-abicalls -mno-odd-spreg -mno-check-zero-division -fomit-frame-pointer `
  -ffast-math -fno-unsafe-math-optimizations -fno-builtin-memset `
  -Wall -Wextra -Wno-incompatible-library-redeclaration -Wno-unused-parameter `
  -Wno-unknown-pragmas -Wno-unused-variable -Wno-unused-but-set-variable `
  -Wno-missing-braces -Wno-unsupported-floating-point-opt -Wno-switch `
  -fno-strict-aliasing -nostdinc -DVERSION_US -DLANG_US -DREFRESH_NTSC `
  -DTARGET_N64 -D_LANGUAGE_C -DMIPS -DLEFTOVERDEBUG `
  -I ../lib/ge/include -I ../lib/ge/include/PR -I ../lib/ge/include/libc `
  -I ../lib/rt64/include yourfile.c -c -o yourfile.o
```

**Three warnings are expected and pre-existing** â€” a `-Wvisibility` on
`sndPlaySfx` in `externs.h:245`, and `MIN`/`MAX` redefined between
`lib/ge/include/math.h` and `PR/gbi.h`. They come from the headers, not from your
file. Anything else is yours.

## GOTCHA 4 â€” how you LAUNCH it decides whether it runs at all

Found 2026-08-22, after half an hour spent suspecting the patch code.

`GoldenRecomp.exe` **crashes with an access violation (`0xC0000005`) if the
working directory is not the repo root.** Correct:

```powershell
cd C:\Users\<USER>\Desktop\GoldenEye64Recomp
build\Release\GoldenRecomp.exe
```

**Double-clicking the exe in Explorer crashes it**, because Explorer sets the
working directory to the exe's own folder.

The cause is `gamecontrollerdb.txt`. `CMakeLists.txt:162` downloads it to the
**repo root**, not next to the exe, and SDL resolves it relative to the working
directory. When it is missing you get one line on stderr â€”

```
Failed to load controller mappings: Invalid RWops
```

â€” and then, shortly after, a null dereference. A missing *optional* controller
database should be a warning, not a crash; it is an upstream bug, and worth fixing
properly if input ever misbehaves. For now, just launch from the right directory.

### Why this is worth its own section

The failure mode is maximally misleading. The exe dies in under ten seconds with
no window, the Application event log names the faulting module as
`GoldenRecomp.exe` itself (not a DLL), and the fault offset is stable across runs
â€” all of which reads like freshly broken recompiled code. It is not. If you have
just changed a patch and the exe starts crashing, **check the working directory
before you bisect your patch.**

Also note the Release build ships **no PDB**, so `llvm-symbolizer` cannot resolve
that fault offset to a function name. If you genuinely need a symbolized stack,
build `--config RelWithDebInfo` and reproduce there.

### Bisecting patches: make sure you actually disabled the thing

A cautionary note from the same session. Disabling interpolation slice 6 via
`GE_INTERP_BULLET_IMPACTS=0` does **not** remove the patch â€” the `#else` branch
still replaces `explosionCallRenderBulletImpactOnProp` and still calls across into
game code. Likewise `GE_VR_MODE_OFF` still patches both projection setters; it
only skips the maths.

Those flags are behaviour switches, not build-out switches. To truly remove a
patch from the link you must delete the `RECOMP_PATCH` function and re-run
`tools_weaken_patched.py` so the original stops being renamed. A bisect that
forgets this proves less than it appears to.
