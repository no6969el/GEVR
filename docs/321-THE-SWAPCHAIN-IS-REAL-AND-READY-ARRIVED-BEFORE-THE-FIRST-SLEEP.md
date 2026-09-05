# `321` -- **THE SWAPCHAIN IS REAL, `READY` ARRIVED BEFORE THE FIRST SLEEP, AND `GL_RGBA8` WAS NEVER ON THE MENU**

**2026-09-05. OFFLINE ASSISTANT. NOTHING BUILT, RUN, STAGED, COMMITTED, BRANCHED, MERGED OR
TAGGED BY THE ASSISTANT.** Two owner pastes on the main PC: one compile, one run. **No product
source edited; `gevr_xr.c` is byte-identical before and after (`2de74d75...`).**

---

## section 0 -- **WHAT THIS SESSION DID, IN FIVE LINES**

1. **Confirmed `320`'s two commits landed** -- `30ee9d8` (docs, 7 files, scrub back to exactly
   `57`) and `7a096e5` (native, 4 vendored headers, `getv/port/src` clean). `V-1`/`V-2` both
   `gcc exit 0` `[REPORTED, OWNER PASTE]`.
2. **Wrote ONE new file, and it is not product:** `repo\xr\gevr_xr_slice2.c`, `478` lines.
3. **Wrote `RUN-SHEET-321`** with four gates pre-registered before the run existed.
4. **The owner built it and ran it. `EXIT 0`. All four gates land.**
5. **Stopped.** `X3` is not started, `H19` is not patched, nothing is filed.

---

## section 1 -- **`X2` IS CLOSED, AND WHAT THAT MEANS EXACTLY**

`[MEASURED]` `repo\xr\gevr_xr_slice2_report.txt`, `17:56`, against `SteamVR/OpenXR v2.16.7` /
`aapvr`, `RTX 5090`, GL `4.6.0 NVIDIA 616.56`:

**`xrEnumerateSwapchainFormats` -> `xrCreateSwapchain` x2 -> `xrPollEvent` pump -> `xrBeginSession`
ALL SUCCEED, IN ORDER, IN ONE PROCESS, AGAINST THE GL CONTEXT THAT PROCESS ALREADY OWNS.**
Two swapchains at **`4140 x 3292`**, `sampleCount 1`, **three images each**, GL texture names
**`1 2 3`** and **`4 5 6`**, `PRIMARY_STEREO` committed, then ended and destroyed cleanly.

**THE SLICE-1 HALF WAS RE-RUN FROM THE TRACKED FILE, NOT FROM A COPY.** `gevr_xr_slice2.c`
`#include`s `gevr_xr.c` rather than duplicating it, so the instance/system/session path exercised
here is the bytes committed at `3f6fd86`, and the per-eye rect the swapchains were created against
came out of `gevr_xr.c`'s own statics. **One source of truth for the rect, by construction.**

**AND THE HEADSET STILL SHOWED NOTHING.** No `xrWaitFrame`, no acquire, no bind, no submit.
**`X2` is the plumbing existing, not a frame arriving.**

---

## section 2 -- **THE THREE THINGS THE RUN SAID THAT NOTHING PREDICTED**

### 2.1 -- **`GL_RGBA8` IS NOT OFFERED, AND THE PRE-REGISTERED FALLBACK WAS A FICTION**

Eight formats: `0x805B` (`GL_RGBA16`), `0x881A` (`GL_RGBA16F`), `0x881B` (`GL_RGB16F`),
`0x8C41` (`GL_SRGB8`), `0x8C43` (`GL_SRGB8_ALPHA8`), then three depth formats. **Five colour
formats and not one 8-bit linear RGBA.**

`RUN-SHEET-321` §3's rule was "`SRGB8_ALPHA8`, else `GL_RGBA8`, else refuse to guess."
**The middle clause names a format this runtime does not have.** Had `SRGB8_ALPHA8` been absent,
the smoke would have exited `4` with the list as the finding -- **which is the right behaviour,
arrived at by luck rather than by knowing the menu.** The lesson is about the RULE and not about
the runtime: **a fallback nobody has seen advertised is a guess wearing a rule's clothes.**

### 2.2 -- **THE RUNTIME RANKS `GL_RGBA16` FIRST AND `SRGB8_ALPHA8` FIFTH**

`format[0]` is the runtime's own preference and it is **16-bit-per-channel**. We took the fifth
entry because it was pre-registered, **which is a reason about the run sheet and not about the
renderer.** At `4140 x 3292 x 2` the difference between `SRGB8_ALPHA8` and `RGBA16` is roughly
**`109 MB` versus `218 MB`** of colour target before any depth or double-buffering, and Fast3D's
output is 8-bit-per-channel anyway.

**THIS IS NOT FILED AND IS NOT A HOLE.** It is a question the eye loop must answer in writing:
**take the runtime's ranking, or state why not.** `U-28` remains reserved and unfiled; this does
not become `U-29` by being interesting.

### 2.3 -- **`READY` ARRIVED WITH `0 ms` OF A `5000 ms` BUDGET SPENT**

`UNKNOWN -> IDLE -> READY`, both transitions already queued when the first `xrPollEvent` ran --
**before the pump's first `Sleep`.** SteamVR had the session ready to begin the moment it was
created, with the headset awake and no frame ever submitted.

**DO NOT GENERALISE THIS INTO A CLAIM ABOUT THE GAME LOOP.** A smoke that does nothing between
`xrCreateSession` and its first poll is the easiest possible case. **What it does establish is
that the 5-second budget was never load-bearing**, so a future sheet that sees `IDLE` persist is
looking at a real difference and not at an impatient timer.

---

## section 3 -- **WHAT IS STILL EXACTLY WHERE IT WAS**

- **`H19` OPEN AND UNPATCHED.** `a = 1.060225` in the headset is still an INFERENCE about a path
  that does not exist. `[DISPOSAL] 9a` stands; `gfx_current_dimensions` is still the SDL window
  at `gfx_pc.c:6062`. **WRONG FILED FIXES STAY AT FIVE.**
- **`U-28` RESERVED, NOT FILED**, on the owner's instruction. `169` NEXT ID = `U-28`.
  **NEXT INSTRUMENT HOLE = `H25`.**
- **`H24` STILL BLINDS EVERY `WS=1` ARM.** `[PREDICTION] 4a` neither established nor falsified.
- **THE LOADER IS STILL NOT VENDORED**, and is owed by whoever first defines
  `GEVR_XR_HAVE_OPENXR` **for the game build**. `321` did not define it for the game:
  `build_windows.ps1` is unedited and the game still compiles the inert stub.
- **THE 57-FILE USERNAME SCRUB IS STILL NOBODY'S.** Leave it alone.
- **`PUBLISH-MANIFEST.md` STILL WANTS ITS VENDORING ENTRY** -- owner's to write,
  text in `RUN-SHEET-320b` §3.

---

## section 4 -- **WHAT `321` LEAVES ON DISK**

| file | state | owed? |
|---|---|---|
| `repo/docs/RUN-SHEET-321.md` | `??` | **YES** -- it carries the pre-registration AND the result |
| `repo/docs/321-...md` (this file) | `??` | **YES** |
| `repo/docs/NEXT-SESSION-PROMPT-322.md` | `??` | **YES** |
| `repo/docs/00-STATE.md` | ` M` (deliberate) | **YES** -- currency + §3 |
| `repo/xr/gevr_xr_slice2.c` | `??` -> **FILED** | **THE OWNER CALLED IT: FILE IT.** See §4.1 |
| `repo/xr/gevr_xr_slice2.exe`, `..._report.txt`, `openxr_loader.dll` | ignored | **NO** -- build output, `repo\.gitignore` covers them |

**`-- repo/docs` WILL READ 58 ` M` AND 3 `??` BEFORE THE COMMIT:** the 57-file scrub **plus
`00-STATE.md`, which `321` edited deliberately.** **The 57 must still read ` M`, unstaged, after
any add.**


### 4.1 -- **THE HARNESS IS FILED, AND WHY THAT IS NOT A PRODUCT COMMIT**

**The owner's call, made after the result existed and not before it.** `repo\xr\gevr_xr_slice2.c`
joins `xr_probe.cpp`, `xr_ext_probe.cpp` and `xr_stereo.cpp` as **the fourth tracked instrument in
`repo\xr`** -- that directory has held tracked probe sources since `317`, so this is the existing
shape and not a new one.

**IT IS A SEPARATE COMMIT FROM `761a9e7` ON PURPOSE.** `761a9e7` was the write-up; this is the
instrument the write-up is about, and a reader who bisects should be able to take one without the
other.

**WHAT FILING IT DOES NOT DO:**
- **It does not put a line of it in the game build.** `build_windows.ps1` globs `port/src` for
  `*.c`; `repo\xr` is not on that path and never has been. **The game cannot compile this file.**
- **It does not touch `getv/port/src`, which stays clean**, and it does not change `gevr_xr.c`,
  whose md5 is still `2de74d753289fe82b2f07c863ea10c37`.
- **It does not vendor the loader** and does not define `GEVR_XR_HAVE_OPENXR` for the game.
- **It does not make the `#include "gevr_xr.c"` shape a precedent for product code.** It is a
  smoke-harness technique that exists to avoid a drifting copy (`319`'s argument), and **a
  translation unit that swallows another `.c` file has no business in `port/src`.**

**WHAT IT DOES DO, AND IT IS THE REASON:** the four `X2` gates become **re-runnable by a later
session against a tracked source**, instead of a result nobody can reproduce because the harness
that produced it was untracked build-side scratch. **`RUN-SHEET-321` §2's build block only means
something if the file it names is still there.**

**THE `.exe`, the report and `openxr_loader.dll` STAY IGNORED** -- `repo\.gitignore` covers
`*.exe`, `*.dll` and `*_report.txt`, and build output is not evidence anyone re-reads from git.

---

## section 5 -- **THE STOPPING LINE, AND IT IS §7c**

**`X3` IS NOT STARTED.** `xrWaitFrame` replacing `sync_framerate_with_timer()` is a TIMEBASE
change with its own falsifier and its own gate, and `00-STATE` §7c says a `HIGH` is not opened at
the end of a session. **`PRIORITY-BOARD-320` §C already ranks it and nothing here re-ranks it.**

**NEXT: `321`'s DOCS COMMIT, THEN `X3` AS A FRESH SESSION'S OPENER.**
