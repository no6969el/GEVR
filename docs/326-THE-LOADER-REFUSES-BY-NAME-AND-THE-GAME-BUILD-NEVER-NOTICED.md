# `326` -- **FORK 1 = `B` IS BUILT AND IT REFUSES BY NAME. THEN THE DEFINE AND THE LINK WENT IN, AND NOBODY HAS RUN THEM**

**2026-09-05.** Owner green-light mid-session on `PLAN-326-DX3KILL` section `2`'s fork and on
step `1` as section `3`. **THREE HELPER PASTES ON THE MAIN PC: BLOCK 0, BLOCK 1, BLOCK 2. NO GAME
WAS RUN. NOTHING STAGED, COMMITTED, BRANCHED, MERGED, TAGGED OR PUSHED.**
`[MEASURED]` `repo\xr\build_326_K1.log` and `repo\xr\build_326_K1b.log`, `16:41` and `16:42`,
**both read off the disk by the assistant, not taken on report.**

---

## 0 -- ONE TABLE

| | |
|---|---|
| `1` | **`K-1` LANDS.** Without `-Vr`, `-Target app` exits `0` and the log is **THE USUAL THREE LINES AND NOTHING ELSE** -- `libge.a 24.9 MB, 501 members`, the launcher font, `windows binary ... 17.2 MB`. **`grep -ci openxr` = `0`** |
| `2` | **`K-1b` LANDS.** With `-Vr` and no loader, exit `1`, and the refusal names the **absolute path**, the md5 `E00CB2890D93D5E33D675BCA3113B1B0` and the size `2669568` |
| `3` | **AND IT REFUSED BEFORE THE FIRST COMPILE.** `goldeneye.exe` was unchanged across `K-1b` -- same `16:41:57`, same `18,071,286` bytes. **A refusal costs one `Test-Path`, not a tree** |
| `4` | **THE GAME BUILD IS UNCHANGED AND THE SCRIPT PROVES IT RATHER THAN ASSERTING IT.** `-Vr` in this step does ONE `Test-Path`: no `-DGEVR_XR_HAVE_OPENXR`, no link argument, no DLL copied anywhere |
| `5` | **THE IGNORE LINE IS THE OTHER HALF OF FORK 1 = `B` AND IT WAS NOT IN THE PROMPT.** `[MEASURED]` `goldeneye-native\.gitignore` had **no `*.dll` rule at all** -- `git check-ignore` returned NOT IGNORED for the loader path before this session. See section `2` |
| `6` | **`K-1c` SKIPPED** on the owner's call, so the accepting half was unproven at that point. **BLOCK 5 SUPERSEDES IT** -- step `2` cannot build without placing the loader |
| `7` | ►► **STEP `2` WAS GREEN-LIT LATER IN THE SAME SESSION AND IS WRITTEN: THE DEFINE, THE LINK AND THE TWO COPIES, ALL UNDER `-Vr`. NOT ONE LINE OF IT HAS BEEN COMPILED. See section `5`** ◄◄ |
| `8` | **`K-2`, `K-3` / `D-X3-KILL` AND `I-3` ARE ALL STILL OWED, IN-GAME.** `K-2` is the owner's at the chair; the `GETV_XR_KILL` instrument is not written and `port_render.c` is untouched |

---

## 1 -- **WHAT WAS BUILT, AND WHAT DELIBERATELY WAS NOT**

**`goldeneye-native\getv\build_windows.ps1`, `+53 / -1`.** `[switch]$Vr`, defaulting OFF, in the
`param()` block beside `[switch]$GuiSubsystem` and `[switch]$Lto`; and the loader existence check,
placed **beside the existing toolchain and decomp `throw`s**, before the first compile, because it
is the same kind of statement -- a path the build cannot invent, named early. **THE `-1` IS
`[switch]$Lto` GAINING A COMMA. THERE IS NOTHING ELSE IN THAT FILE.**

**`goldeneye-native\.gitignore`, `+5 / -0`.** `getv/port/lib/openxr/`.

**THEN STEP `2`, ON A SECOND GREEN-LIGHT, TOOK IT TO `+90 / -2`.** Section `5` has the three
lines. **NOT ONE OF THEM HAS BEEN COMPILED.**

**NOT BUILT, AND ALL OF IT STILL OWED:** no `port_render.c` line, no `GETV_XR_KILL` instrument,
no patch edit, no `gfx_sdl2.c`, no handover of any kind. **`gevr_xr.c` AND `gevr_xr.h` ARE
UNTOUCHED THIS SESSION** -- `325`'s interlock bytes stand and `getv/port/src` read clean at every
gate.

### 1.1 -- **WHY THE SWITCH ARRIVED WITH THE CHECK RATHER THAN AFTER IT**

A build-time existence check with no trigger has two shapes and both are wrong: fired on every
build it breaks a build that has never needed a loader, and fired on nothing it is decoration.
**THE TRIGGER IS PART OF THE CHECK, SO IT IS IN THE SAME EDIT** -- and because `-Vr` in this step
links nothing, `K-1` can score the OFF path and `K-1b` the ON path **without the game build ever
seeing an OpenXR symbol.** That is the whole reason step `1` is separable from step `2`.

---

## 2 -- ►► **THE THING THE PROMPT DID NOT CARRY: THE NATIVE REPO DOES NOT IGNORE `*.dll`** ◄◄

`NEXT-SESSION-PROMPT-326` asked for FORK 1 = `B`'s check in `build_windows.ps1` **ONLY**.
`[MEASURED]`, before anything was edited: `GoldenEyeVR\.gitignore:3` carries a blanket `*.dll`,
**`goldeneye-native\.gitignore` carries none**, and `git check-ignore -v` on
`getv/port/lib/openxr/openxr_loader.dll` returned **NOT IGNORED**.

**SO FORK 1 = `B` HAS A SECOND HALF, AND WITHOUT IT THE FORK DEFEATS ITSELF.** `B`'s entire
purpose is that a `2.6 MB` binary does not enter git. Left un-ignored, the owner's local copy sits
in `??` in every porcelain from here on -- **one `git add -A` away from exactly the outcome
`PLAN-325-DX3` FORK 1 = `A` was refused for**, and this project's own standing hygiene rule
exists because that class of accident has happened. The ignore line is **NOT** in
`build_windows.ps1`, so the prompt's "and nothing else in that file" is intact.

`[MEASURED]` after the edit: `.gitignore:283:getv/port/lib/openxr/`.

---

## 3 -- **TWO THINGS OFF THE DISK THAT NOBODY PREDICTED. NEITHER IS FILED**

**`3.1` -- THE RELINK IS `512` BYTES LARGER.** `[ARITHMETIC]` `18,071,286` against
`goldeneye.exe.pre326`'s `18,070,774`, from the same `501` archive members and one root.
`512` bytes is one PE file-alignment block. **NO CAUSE IS OFFERED AND NONE WAS MEASURED.** The
sheet never claimed byte-identity across a relink and does not start now. **NOT FILED, NOT A
HOLE** (`301` section `0`). **WRONG FILED FIXES STAY FIVE.**

**`3.2` -- A CLAIM IN THIS SESSION'S OWN PLAN WAS WRONG AND IS CORRECTED ON DISK.**
`PLAN-326-DX3KILL` section `4` first said step `2` risked a warning storm, because the LIVE branch
of `gevr_xr.c` had only ever been compiled by the slices. `[MEASURED]` **IT CANNOT:**
`build_windows.ps1` sets `$warn = @('-w','-Werror=return-type')` -- the port batch compiles with
warnings OFF except return-type. **THE RISK RUNS THE OTHER WAY:** the game batch will say
**nothing at all** about a branch nothing has ever compiled in this flag set. Section `4` now
carries a separate `-Wall -Wextra` syntax-only compile of `gevr_xr.c` alone whose output is READ,
and names the real hazard instead of the imagined one -- **`<windows.h>` and `<GL/gl.h>` entering
a port translation unit that is already force-fed `-include ge_win_compat.h`
(`build_windows.ps1:228`), where a collision is a compile error in a file that today compiles to
nothing.**

---

## 4 -- **WHAT THIS DOES NOT CLAIM**

- **NOT that the check ACCEPTS a loader.** `K-1c` was skipped on the owner's call. **The path has
  been proved to REFUSE and has never been proved to PASS.** It is one paste (`RUN-SHEET-326`
  BLOCK 3) whenever it is wanted.
- ►► **NOT that the game links OpenXR. THE THREE LINES ARE ON DISK AND HAVE NEVER BEEN RUN.**
  No compiler has seen `-DGEVR_XR_HAVE_OPENXR` in the port batch, no linker has seen the loader
  on the link line, and **the last `goldeneye.exe` on this disk is the plain `K-1` relink.**
  Every prediction in section `5` is unscored ◄◄
- **NOT the `I-3` baseline.** `K-2` needs step `2` and a game run. **OWED.**
- **NOT that `xrWaitFrame` blocks in the game.** `D-X3-KILL` is untouched. **OWED, IN-GAME, AND
  IT NEEDS THE CHAIR.**
- **NOT a handover.** `port_render.c` is untouched and `sync_framerate_with_timer()` owns the
  clock in every binary. `H19` open. `U-28` reserved unfiled.

---

## 5 -- **STEP `2` AS WRITTEN, AND IT IS UNRUN**

**GREEN-LIT LATER IN THE SAME SESSION:** three lines, all under `-Vr`, plus the `-Wall -Wextra`
read. `build_windows.ps1` goes `+53 / -1` to **`+90 / -2`**.

| | line |
|---|---|
| `1` | `if ($Vr) { $portFlags += '-DGEVR_XR_HAVE_OPENXR' }` -- **the first thing in this project's history to define it for the GAME build.** `320`'s vendoring already put `openxr/openxr.h` on the port's existing `-I$here\port\include`, so this is a define and a link, **not a search path** |
| `2` | `if ($Vr) { $linkArgs += $xrLoader }` -- a PE DLL linked directly, no import library, **the shape every slice since `319` used.** APPENDED LAST because `gevr_xr.o`'s `xr*` calls live inside `libge.a` earlier on the line |
| `3a` | `Build-App` copies the loader beside the binary. It is not in `$Mingw\bin`, so it cannot join the four-DLL loop |
| `3b` | `Build-Dist` requires it: the list is **built rather than typed**, so a plain build's required set is unchanged |

**AND THE SECOND `-` IS AN HONESTY EDIT:** step `1`'s `Write-Output` said
`-- CHECKED, NOT LINKED`. **STEP `2` LINKS IT, SO THAT TAIL WOULD NOW BE A LIE** and it was
dropped. A build script that describes itself wrongly is worse than one that says nothing.

**`[MEASURED]` `-Target all` IS `Build-Lib; Build-App` AND NEVER CALLS `Build-Port`.**
`$portFlags` changed, so the port batch must be rebuilt explicitly -- `RUN-SHEET-326` BLOCK 5 is
`-Target port -Vr` then `-Target app -Vr`, and the decomp is not recompiled.

**FOUR PRE-REGISTERED PREDICTIONS, NONE SCORED:** `S-0` the `-Wall -Wextra` syntax-only compile
of `gevr_xr.c` alone exits `0` (its warnings are READ and **not fixed on sight** -- `301`);
`S-1` `-Target port -Vr` reports `0 failed`; `S-2` the link resolves every `xr*`;
**`S-4` `K-1` STILL LANDS AFTER STEP `2`** -- a plain build must still print no `openxr` line,
and **that is the one thing step `2` must not get wrong.**

---

## 6 -- **ARTIFACTS** (gitignored logs OK)

- `repo/xr/build_326_K1.log`, `repo/xr/build_326_K1b.log` (`16:41`, `16:42`)
- `getv/build-windows/goldeneye.exe.pre326` -- the pre-relink binary, kept beside the new one
- `repo/docs/PLAN-326-DX3KILL.md` (section `2` is the fork the owner answered; section `3.2` is
  the ignore line; section `4` carries the correction in `3.2` above)
- `repo/docs/RUN-SHEET-326.md` (BLOCK 3 is the unrun positive control)

`169` NEXT ID = `U-28`. NEXT INSTRUMENT HOLE = `H25`.
