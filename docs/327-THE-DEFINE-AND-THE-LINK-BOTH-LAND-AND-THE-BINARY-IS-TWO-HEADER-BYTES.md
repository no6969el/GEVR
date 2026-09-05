# `327` -- **STEP `2` COMPILES AND LINKS AND BOTH ARE CLEAN. THE BINARY IT PRODUCES DIFFERS FROM A PLAIN ONE BY TWO HEADER BYTES, AND `gevr_xr.o` IS IN NEITHER**

**2026-09-05.** `RUN-SHEET-326` BLOCKS `4`, `5` and `6` run by the helper on the main PC; `K-2`
taken by the owner at the chair. **NO PRODUCT SOURCE EDITED. NOTHING STAGED, COMMITTED, BRANCHED,
MERGED, TAGGED OR PUSHED.** `[MEASURED]` `repo\xr\syntax_326_gevr_xr.log` (`20:59`),
`repo\xr\build_326_S1.log` (`21:01`), `repo\xr\build_326_K1_after.log` (`21:04`), and the two
binaries themselves -- **all read off the disk by the assistant, none taken on report.**

---

## 0 -- ONE TABLE

| | |
|---|---|
| `1` | **`S-0` LANDS.** `-Wall -Wextra -fsyntax-only` on `gevr_xr.c` with `-DGEVR_XR_HAVE_OPENXR`: gcc exit `0` and the log is **`0` BYTES**. Not one diagnostic. The named hazard did not fire |
| `2` | **`S-1` LANDS.** `-Target port -Vr` exit `0`, `port layer: 60 built, 0 failed`, `port c++: 2 built, 0 failed` |
| `3` | **`S-2` LANDS.** `-Target app -Vr` exit `0`, links, prints `windows openxr loader: ... (2.55 MB)`. `libge.a` **`502` members** (`+1 roots`), binary `17.2 MB` |
| `4` | **`S-3` LANDS.** `openxr_loader.dll` beside `goldeneye.exe`, `2,669,568` bytes, md5 `E00CB2890D93D5E33D675BCA3113B1B0` |
| `5` | **`S-4` LANDS, AND IT WAS THE ONE STEP `2` MUST NOT GET WRONG.** A plain `port` + `app` build: both exits `0`, `grep -ci openxr` **`0`**. No line of step `2` fires without `-Vr` |
| `6` | ►► **AND THE `-Vr` BINARY IS THE PLAIN BINARY.** `[MEASURED]` `cmp -l`: **EXACTLY TWO BYTES DIFFER**, positions `137` (`0x88`, PE COFF `TimeDateStamp`) and `217` (`0xD8`, optional-header `CheckSum`). Same length. Identical import tables. **`0` `xr*` imports in either** ◄◄ |
| `7` | ►► **`gevr_xr.o` IS AN ARCHIVE MEMBER AND IS IN NEITHER BINARY.** `[MEASURED]` neither `goldeneye.exe` nor `goldeneye.exe.vr326` contains the token `gevr_xr`, the token `geVrXr`, or the stub's own diagnostic string. **The linker never extracted the member, so the loader appended last resolved nothing** ◄◄ |
| `8` | **`K-2` LANDS AS A FORMALITY AND IS RECORDED AS ONE.** Both binaries booted and played flat with normal controls, **no `[getv][vr]` lines**. **THE THREE PACING NUMBERS WERE NOT CAPTURED** and the owner waived them on the strength of item `6`. See section `4` -- **`K-2`'s stated falsifier was never exercised** |

---

## 1 -- **STEP `2` IS COMPILED, AND EVERY PRE-REGISTERED PREDICTION SCORED**

`326` left five predictions written and none scored. **ALL FIVE ARE NOW SCORED AND ALL FIVE LAND.**

**`S-0`, AND IT IS THE QUIET ONE.** `build_windows.ps1:212` is `$warn = @('-w',
'-Werror=return-type')`, so the game batch says nothing about a branch nothing had ever compiled.
BLOCK 4 is the only place that looks. `[MEASURED]` `syntax_326_gevr_xr.log` is **`0` bytes** --
gcc exit `0` with `-Wall -Wextra` and `-DGEVR_XR_HAVE_OPENXR` produced **no diagnostic of any
kind**, not an error and not a warning. **`<windows.h>` AND `<GL/gl.h>` DID NOT COLLIDE WITH THE
FORCE-INCLUDED `ge_win_compat.h`** (`build_windows.ps1:228`), which was the named candidate.

**AND `S-0` IS NARROWER THAN IT LOOKS.** `-fsyntax-only` emitted no object. It says the LIVE
branch **parses**. It says nothing about codegen, nothing about the link, and -- as section `2`
shows -- nothing about whether any of it reaches a binary.

**`S-1` / `S-2` / `S-3`.** `[MEASURED]` `build_326_S1.log`, which is **UTF-16LE** (a PowerShell
`*>` redirect) and returns nothing to a byte-wise `grep` for `openxr` unless it is decoded first.
Decoded, it carries the loader line **twice** -- once for the `port` run, once for the `app` run --
then `60 built, 0 failed`, `2 built, 0 failed`, `libge.a 24.9 MB, 502 members (+1 roots)`, and
`windows binary: ... (17.2 MB)`.

**`S-4`.** `[MEASURED]` `build_326_K1_after.log`, decoded: the usual lines, both exits `0`,
**`grep -ci openxr` = `0`**. The define, the link argument, the copy beside the binary and the
`dist` requirement are all gated on `-Vr` and none of them fires without it.

---

## 2 -- ►► **THE FINDING NOBODY PRE-REGISTERED: THE TWO BINARIES ARE THE SAME PROGRAM** ◄◄

`326`'s sheet asked whether the `-Vr` build links. It does. **IT DOES NOT ASK WHAT THE `-Vr`
BUILD PRODUCES, AND THAT IS WHERE THE RESULT IS.**

`[MEASURED]`, the `-Vr` binary preserved as `goldeneye.exe.vr326` against the plain `K-1`-after
binary at `goldeneye.exe`:

| | plain | `-Vr` |
|---|---|---|
| length | `18,071,286` | `18,071,286` |
| md5 | `78137EDAA287CBBE428435CE49C7486A` | `58FD886FD3C0587CE7249FF524A7CFCE` |
| imported DLLs | `dbghelp`, `glew32`, `KERNEL32`, `msvcrt`, `OPENGL32`, `libwinpthread-1`, `SDL2` | **the same seven** |
| `openxr_loader.dll` in the import table | **NO** | **NO** |
| `xr*` imports | `0` | `0` |
| `libge.a` members | `502` | `502` |

**`cmp -l` REPORTS EXACTLY TWO DIFFERING BYTES:** position `137` (`0x88`) and position `217`
(`0xD8`). `[ARITHMETIC]` with `e_lfanew = 0x80`, `0x88` is the COFF header's `TimeDateStamp` and
`0xD8` is the optional header's `CheckSum`. **THE TWO BUILDS DIFFER IN WHEN THEY WERE LINKED AND
IN THE CHECKSUM THAT RECORDS IT. NOTHING ELSE.**

### 2.1 -- **AND THE REASON IS ON THE DISK, NOT INFERRED**

`[MEASURED]` `ar t` names `port_F_Projects_GEVR_GoldenEyeVR_goldeneye-native_getv_port_src_gevr_xr.o`
inside `libge.a`, in both builds. `[MEASURED]` **neither binary contains the token `gevr_xr`,
neither contains the token `geVrXr`, and neither contains the stub branch's own string
`gevr_xr was compiled without GEVR_XR_HAVE_OPENXR ...`.**

**THE MEMBER IS IN THE ARCHIVE AND IN NEITHER EXECUTABLE.** A traditional linker extracts an
archive member only to satisfy an undefined symbol, and `00-STATE` has said since `325` that
**NOTHING CALLS THE INTERLOCK** -- nothing calls anything else in that file either. So `gevr_xr.o`
is never pulled, its `xr*` calls never become undefined symbols, and `$linkArgs += $xrLoader`
appended last has **nothing to resolve.** The loader is on the link line and contributes zero
bytes.

**THIS IS A RESULT, NOT A FAULT, AND NOTHING WAS CHANGED BECAUSE OF IT** (`301`). Step `2`'s three
lines are correct, correctly gated, and correctly inert. **THEY ARE ALSO, TODAY, WITHOUT EFFECT ON
THE PRODUCED BINARY.** **NOT FILED, NOT A HOLE. WRONG FILED FIXES STAY FIVE.**

### 2.2 -- **WHAT THIS DOES TO THE NEXT STEP, AND IT IS THE USEFUL PART**

**`D-X3-KILL` ASKS WHETHER `xrWaitFrame` BLOCKS INSIDE THE GAME PROCESS.** On this evidence there
is no `xrWaitFrame` inside the game process to block: **no `xr*` import exists in the binary the
chair would run.** Any `GETV_XR_KILL` instrument in `port_render.c` that expects to reach the XR
path must first cause `gevr_xr.o` to be linked at all -- a call site, not a define. **THAT IS A
DESIGN QUESTION FOR A FRESH SESSION WITH ITS OWN GREEN-LIGHT AND ITS OWN FALSIFIER, AND IT IS NOT
STARTED HERE** (`00-STATE` section `7c`).

---

## 3 -- **A GAP IN `RUN-SHEET-326`, FLAGGED BEFORE IT COST ANYTHING**

**BLOCK 6 REBUILDS PLAIN OVER `build-windows\goldeneye.exe`, WHICH IS THE `-Vr` BINARY `K-2` RUN B
NEEDS.** As written, BLOCK 6 destroys the thing the next step measures. The `-Vr` binary was
copied aside to `goldeneye.exe.vr326` **before** BLOCK 6 ran, as a separate paste, and the sheet's
BLOCK 6 was then run verbatim and unmodified. **`K2-CHAIR-CHECKLIST` ALREADY ASKED FOR BOTH
BINARIES ("note which `goldeneye.exe` is which"); THE SHEET DID NOT ARRANGE FOR THE SECOND ONE TO
STILL EXIST.**

`goldeneye.exe.pre326` (`18,070,774`, `Sep 3`) is untouched and remains the pre-`326` control.

---

## 4 -- **`K-2` AS ACTUALLY TAKEN, AND WHAT IT DID NOT EXERCISE**

**TAKEN BY THE OWNER AT THE CHAIR**, `GETV_VR` unset, SteamVR closed, Run A the plain binary
(`78137EDA...`) and Run B the `-Vr` binary (`58FD886F...`), staged by the helper.

**WHAT LANDED:** both launched, both played on the flat screen with normal controls, **no
`[getv][vr]` output on Run B**, no VR behaviour of any kind.

**WHAT DID NOT HAPPEN, AND IT IS RECORDED RATHER THAN GLOSSED:** `GETV_BUDGET`, `ge_pace_wait_ms`
and `ge_pace_sleeps` were **NOT CAPTURED** -- no visible `GETV_BUDGET` console at the chair. The
owner waived them on the strength of section `2`. **`K-2`'s STATED FALSIFIER WAS "DIFFERENT PACING
NUMBERS", AND NO PACING NUMBER WAS READ, SO THAT HALF OF `K-2` WAS NOT EXERCISED.**

`[MEASURED]`, and it belongs beside the waiver: **both binaries contain `GETV_BUDGET` (three
occurrences) and `ge_pace_wait_ms` (one).** The instrumentation is in the build. The numbers were
not surfaced at the chair, which is a console-visibility matter and **NOT A HOLE** -- `H24` already
covers the blinding of `WS=1` arms and nothing new is filed here.

**SO `K-2` IS THE HONEST BASELINE AT THE LEVEL IT WAS TAKEN:** the `-Vr` binary does not change
how the game boots, plays or behaves with `GETV_VR` unset. **IT IS NOT EVIDENCE THAT AN XR PATH IS
INERT.** It is inert because, per section `2.1`, **it is absent.**

---

## 5 -- **WHAT THIS SESSION DOES NOT CLAIM**

- **NOT that the game links OpenXR.** It links a loader that resolves nothing. `0` `xr*` imports.
- **NOT that `xrWaitFrame` blocks, or does not.** `D-X3-KILL` is untouched. **OWED, IN-GAME.**
- **NOT the `I-3` result.** `I-3` needs `GETV_VR=1` and a run. **OWED.**
- **NOT a pacing comparison.** Section `4`: no pacing number was read.
- **NOT a cause for the `512` bytes `326` measured against `.pre326`.** Still no cause offered.
- **NOT a handover.** `port_render.c` untouched, `sync_framerate_with_timer()` owns the clock in
  every binary. `H19` open. `U-28` reserved unfiled.

---

## 6 -- **ARTIFACTS** (gitignored logs OK)

- `repo/xr/syntax_326_gevr_xr.log` (`20:59`, **`0` bytes -- that is the result**)
- `repo/xr/build_326_S1.log` (`21:01`, UTF-16LE -- decode before grepping)
- `repo/xr/build_326_K1_after.log` (`21:04`, UTF-16LE)
- `repo/xr/gates_327.log` (session-opening gates)
- `getv/build-windows/goldeneye.exe.vr326` -- **the `-Vr` binary, preserved before BLOCK 6**
- `getv/build-windows/goldeneye.exe.plain326` -- the plain binary, staged aside for `K-2`
- `getv/build-windows/goldeneye.exe.pre326` -- the pre-`326` control, untouched
- `getv/port/lib/openxr/openxr_loader.dll` -- placed by BLOCK 5, **ignored** (`.gitignore:283`)

`169` NEXT ID = `U-28`. NEXT INSTRUMENT HOLE = `H25`.
