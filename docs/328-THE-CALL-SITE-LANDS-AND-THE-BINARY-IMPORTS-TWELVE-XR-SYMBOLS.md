# `328` -- **THE CALL SITE LANDS. `openxr_loader.dll` IS IN THE IMPORT TABLE AND TWELVE `xr*` SYMBOLS ARE UNDER IT. AND IT IS STILL NOT `D-X3-KILL`**

---

## 0 -- ONE TABLE

| | |
|---|---|
| `1` | **`S-5` LANDS.** `-Wall -Wextra -fsyntax-only` on `gevr_xr.c` with `-DGEVR_XR_HAVE_OPENXR`, after the new entry point went in: gcc exit `0`, log **`0` BYTES**. Both named candidates dead -- `wglGetCurrentDC`/`wglGetCurrentContext` are declared by the `<windows.h>` already at `gevr_xr.c:36`, and `%p` against `HDC`/`HGLRC` raises nothing under `-Wextra` |
| `2` | **`S-6` LANDS.** `-Target port -Vr` and `-Target app -Vr` both exit `0`; `port layer: 60 built, 0 failed`, `port c++: 2 built, 0 failed`, `libge.a 24.9 MB, 502 members (+1 roots)`. **No `failed`, `error`, `warning` or `undefined` anywhere in the log** |
| `3` | ►► **`K-4` LANDS, AND IT IS THE SESSION.** `[MEASURED]` `objdump -p goldeneye.exe.vr328`: **EIGHT** imported DLLs -- `327`'s seven **plus `openxr_loader.dll`** -- and **`12` `xr*` IMPORT ENTRIES** under it. `327` measured `0` in both binaries ◄◄ |
| `4` | **`K-5` LANDS.** The plain build compiles and links, **no log line names `openxr`**, the plain binary has the **same seven** DLLs and **`0`** `xr*` entries. The site is gated |
| `5` | **`K-6` IS OWED.** The chair run with `GETV_XR_KILL` unset has not been taken. **THIS SESSION DOES NOT CLAIM IT** |
| `6` | **`K-3` IS UNTOUCHED AND UNCLAIMED.** There is no `xrWaitFrame` in the binary because there is none in the tree. `D-X3-KILL` is not answered by anything below |

---

## 1 -- **THE TWELVE, AND WHY THE LIST ITSELF IS THE EVIDENCE**

`[MEASURED]` `repo\xr\imports_328_vr.log`, `DLL Name: openxr_loader.dll` at line `356`:

`xrCreateInstance`, `xrCreateSession`, `xrDestroyInstance`, `xrDestroySession`,
`xrEnumerateInstanceExtensionProperties`, `xrEnumerateViewConfigurationViews`,
`xrEnumerateViewConfigurations`, `xrGetInstanceProcAddr`, `xrGetInstanceProperties`,
`xrGetSystem`, `xrGetSystemProperties`, `xrResultToString`.

**THIS IS NOT A GENERIC SET AND THAT IS THE POINT.** It is **exactly** `gevr_xr.c`'s
direct-call list, and the two absences are as informative as the twelve presences:

- **`xrGetOpenGLGraphicsRequirementsKHR` IS NOT THERE, AND MUST NOT BE.** It is an extension
  entry point reached through `xrGetInstanceProcAddr` (`gevr_xr.c:353`), which **is** there.
  Had it appeared as an import, the file would be linking against something other than what it
  is written to call.
- **`xrWaitFrame`, `xrBeginFrame` AND `xrEndFrame` ARE NOT THERE**, because `[MEASURED]` `328`
  they exist nowhere in this tree except in printed strings and comments.

**SO THE MECHANISM IS CLOSED, NOT INFERRED.** `327` section `2.1` reasoned that the linker never
extracted the member because nothing referenced it. One reference from `port_render.c` was added
and the member came in, dragging its own undefined `xr*` into a loader that was already last on
the link line (`build_windows.ps1:504`, whose own comment predicted this in `326`). **NO BUILD
SCRIPT LINE CHANGED. THE LINK LINE WAS ALREADY RIGHT.**

---

## 2 -- **THE ARITHMETIC, AND IT SEPARATES THE STUB FROM THE LIVE BRANCH**

| binary | md5 | length | vs `plain326` |
|---|---|---|---|
| `goldeneye.exe.plain326` (`327`'s control) | `78137EDAA287CBBE428435CE49C7486A` | `18,071,286` | -- |
| `goldeneye.exe.plain328` | `B449BAD55A9B25B8F0D26A6515422EDA` | `18,075,450` | **`+4,164`** |
| `goldeneye.exe.vr328` | `65ED4041C9C7818B921157BE5CC4727D` | `18,085,678` | **`+14,392`** |

`[ARITHMETIC]` **BOTH BUILDS NOW PULL `gevr_xr.o`.** The plain build takes the **inert** member
(`gevr_xr.c:541-575`) plus the instrument block: `+4,164` bytes and **`0`** `xr*` imports. The
`-Vr` build takes the **live** member: a further `+10,228` bytes and twelve imports. **THAT IS ONE
CALL SITE BEHAVING DIFFERENTLY UNDER ONE DEFINE, NOT TWO CALL SITES.**

**AND THE SIZE STILL DOES NOT SCORE ANYTHING.** `NEXT-SESSION-PROMPT-328` item `1` ruled size
insufficient before the run, and it stays insufficient now that it happens to point the right
way. `K-4` was scored on the import table and on nothing else. The `gevr_xr` (`2`) and `geVrXr`
(`18`) token counts in the image are corroboration and were pre-registered as corroboration.

---

## 3 -- **WHAT WAS TYPED, AND IT IS THREE FILES**

Green-lit by the owner 2026-09-05: `F3` only, and the new entry point.

| file | edit |
|---|---|
| `getv/port/src/gevr_xr.h` | one declaration, `int geVrXrBeginSessionCurrent(void)`, with its reasoning |
| `getv/port/src/gevr_xr.c` | the LIVE implementation inside the existing `GEVR_XR_LIVE` guard, and its one-line inert stub |
| `getv/port/src/port_render.c` | `#include "gevr_xr.h"` and the `GETV_XR_KILL` block |

**`F1` (FILE-SCOPE DUMMY) AND `F2` (`-Wl,-u,...`) WERE PROPOSED AND REFUSED BY THE OWNER, AND
NEITHER WAS WRITTEN.** `PLAN-328-CALLSITE` section `3` records why they were named at all.

**THE HANDLES ARE TAKEN ON THE CALLEE'S SIDE.** `PLAN-326` section `5` had `port_render.c`
calling `wglGetCurrentDC()`. `[MEASURED]` `ge_win_compat.h:24` refuses `<windows.h>` into that
batch **by name**, so the wrapper takes both handles inside the platform guard instead and
refuses by name when no context is current. **`port_render.c` STILL DOES NOT SEE `<windows.h>`.**

**THE PLACEMENT IS BEFORE THE `GETV_BUDGET` BRACKET** (`port_render.c:907`), for the reason the
census and `GETV_DLGRAB` already give in that file: a block that creates and destroys an XR
session must not be charged to a frame. One contaminated budget line would have been scored by
`K-6`.

**THE STANDING LINE HELD.** `[MEASURED]` neither `geVrXrPacingOwned` nor `sync_framerate` appears
in the diff. The instrument times and prints nothing else, and **THE HANDOVER IS NOT STARTED.**

---

## 4 -- ►► **WHAT THIS SESSION DOES NOT CLAIM, AND THE LIST IS THE IMPORTANT PART** ◄◄

1. **IT DOES NOT ANSWER `D-X3-KILL`.** `[MEASURED]` `328`: `xrWaitFrame`, `xrBeginFrame` and
   `xrEndFrame` do not exist in this tree. The block creates a session in the game process and
   tears it down on the same frame. **WHETHER `xrWaitFrame` BLOCKS IN THE GAME PROCESS IS
   EXACTLY AS OPEN AS IT WAS IN `322`.**
2. **IT HAS NOT RUN THE INSTRUMENT.** `K-4` and `K-5` are link facts read from `objdump`. **NO
   BINARY BUILT THIS SESSION HAS BEEN LAUNCHED**, with or without the knob, with or without a
   runtime. `GETV_XR_KILL=1` has never executed.
3. **IT DOES NOT KNOW WHETHER `xrCreateSession` SUCCEEDS ON THE GAME'S CONTEXT.** That is the
   first thing the arm would find out and nobody has taken it.
4. **`K-6` IS OWED** -- the unset-knob baseline at the chair, with a conditions sidecar.
5. `H19` open. `U-28` reserved unfiled. `H24` still blinds every `WS=1` arm. **NOTHING NEW FILED.
   WRONG FILED FIXES STAY FIVE.**

**AND `PLAN-326` SECTION `5` IS NOT RETRACTED, IT IS INCOMPLETE.** It named the kill's shape
correctly and did not audit whether the entry points it calls exist. `328` audited that before a
compile session was spent on it, which is the only reason it cost a paragraph instead of an
afternoon. **NOT FILED, NOT A HOLE.**

---

## 5 -- **ARTIFACTS** (gitignored logs OK)

`repo\xr\gates_328.log`, `syntax_328_gevr_xr.log` (`0` bytes), `build_328_vr.log`,
`imports_328_vr.log`, `build_328_plain.log`, `imports_328_plain.log`.
Binaries preserved: `goldeneye.exe.vr328`, `goldeneye.exe.plain328`; `goldeneye.exe` is the plain
binary again. `.vr326`, `.plain326` and `.pre326` untouched.

**NOTHING STAGED, COMMITTED, BRANCHED, MERGED, TAGGED OR PUSHED.**

`169` NEXT ID = `U-28`. NEXT INSTRUMENT HOLE = `H25`.
