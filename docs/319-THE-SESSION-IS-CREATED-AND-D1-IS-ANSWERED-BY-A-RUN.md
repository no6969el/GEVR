# `319` — **THE SESSION IS CREATED, AND `D1` IS ANSWERED BY A RUN**

> **OFFLINE ASSISTANT. NOTHING BUILT, RUN, STAGED, BRANCHED, MERGED OR TAGGED BY THE ASSISTANT.**
> Two compiles and one run by the owner on the main PC; everything else read off the bridge.
> Binary UNTOUCHED — nothing this session goes near `goldeneye.exe`, and no gitignored file was
> edited. `318`'s docs commit is in at **`04e7d2b`**. **Wrong filed fixes: FIVE.**

---

## §0 — WHAT THIS SESSION ESTABLISHED, IN ONE TABLE

| | |
|---|---|
| **1** | **`X1` WAS ARGUED TO A WRITTEN DECISION BEFORE ANYTHING WAS BUILT**, and the owner green-lit `D1`-`D4`. `117`'s `mainTick()` was used as evidence and **not copied** — `117`'s own banner says it is *"evidence to re-decide WITH, not a decision"* |
| **2** | **►►►► FOUR FACTS WERE READ OFF THE TREE THAT NO DOCUMENT STATED, AND ONE OF THEM DECIDES `X1b`.** §2. `gfx_current_dimensions` has ONE write site; a shipped path already overwrites it; `ge_postfx.c` is the placement precedent; **ONE display list, ONE `gfx_run`, ONE swap means `a` has exactly ONE value per frame, by construction** |
| **3** | **`gevr_xr.c` / `.h` EXIST.** `24704` + `7945` bytes, tracked-shape, in `getv/port/src`. **Inert twice over**: `GEVR_XR_HAVE_OPENXR` is not defined by the game build, and `GETV_VR` is unset by default (`48`) |
| **4** | **`[PREDICTION] X1-1` LANDS.** `xrCreateInstance` succeeds **with one extension enabled** — the first instance in this project's history to enable one. `xr_ext_probe.cpp`'s enabled zero |
| **5** | **►►►►►►►► `[PREDICTION] X1-2` LANDS: `SESSION CREATED`.** `[MEASURED]` `gevr_xr_smoke_report.txt`, 2026-09-05 `16:24:36`. **`D1` IS ANSWERED BY A RUN**: OpenXR over `XR_KHR_opengl_enable`, bound to the GL context the process already owns, **no interop**. Exit `0`, session destroyed cleanly |
| **6** | **`[PREDICTION] X1-3` LANDS.** `4140 x 3292` both views, rects identical, `max 8192 x 8192`, `samples rec 1 max 1` — **unchanged across `1h 03m`** against `318`'s `15:21:07`. The file's own change-detector did not fire, which is what "unchanged" means here |
| **7** | **►►►► NEW, AND NOT PREDICTED: THE RUNTIME'S GL REQUIREMENT IS `min 4.3  max 4.6`.** That is a transfer risk for slice 2 — a plain WGL context proves nothing about SDL2's. **`[MEASURED, BRIDGE]` it is closed on evidence already on disk: the game's own context reads `GL_VERSION=4.6.0 NVIDIA 616.56` in existing run logs.** §5 |
| **8** | **`[PREDICTION] X1-0c` HAS NO ARTEFACT AND IS NOT MARKED LANDED.** The inert gate is `-fsyntax-only` and writes no file; **and the smoke does not cover it**, because the smoke compiled the LIVE branch and the game build takes the other one. §5 |
| **9** | **`X1b` IS STILL UNANSWERED**, and this session found its candidate rather than its answer. **NOT FILED** (`301` §0); `U-28` reserved. §6 |
| **10** | **NOTHING IS PATCHED IN THE PRODUCT OR THE INSTRUMENT.** `H19` open, unpatched, documented. `[DISPOSAL] 6g` unsoftened. **The count of wrong filed fixes stays at FIVE** |

---

## §1 — **THE DECISION, AS ARGUED AND AS GREEN-LIT**

`X1` is *"which runtime surface, and where does the session live?"* Its precondition was satisfied
by the owner's decision (`7b2`), not by a gate clearing at `2560x1369` — which never happened.

- **`D1` — THE SURFACE.** OpenXR over **`XR_KHR_opengl_enable`**, bound to the GL context SDL2
  already owns. `X1-0` measured `v12` present; the native line is fast3d -> `gfx_opengl.c` on
  SDL2. **`XR_KHR_D3D12_enable v11` is advertised and deliberately NOT used** — it buys a
  GL-to-D3D interop copy that `X1-0` removed from the critical path.
- **`D2` — WHERE THE SESSION LIVES.** Process lifetime, owned by `gevr_xr.c`, driven from
  `port_render.c`'s existing `gfx_start_frame`..`gfx_end_frame` bracket. **IT OWNS THE PRESENT
  BEFORE IT OWNS THE PACING**, and that ordering is written down as a **way station, not a
  destination**: PD's own comment (`vr_openxr.cpp:2093`, quoted in `117`) is that *"xrWaitFrame
  below is the ONLY thing pacing the game's tick"*, so the destination is `xrWaitFrame` replacing
  `sync_framerate_with_timer()`. **That is a TIMEBASE change**, and the timebase was settled by
  run in `274` and worn in `277`; it gets its own decision and its own gate.
- **`D3` — PLACEMENT.** `getv/port/src/gevr_xr.c` + `.h`, tracked. **The owner's call**, and the
  reason is recorded in the header: **`ge_postfx.c` is TRACKED PARAMS, and the FBO bind and
  resolve stay in `gfx_opengl.c`** (bind at `gfx_opengl_start_frame:1471`, resolve at
  `gfx_opengl_end_frame:1571`). When slice 2 grows a swapchain the XR state and the rects live in
  `gevr_xr.c` and the `glBindFramebuffer` stays beside the two FBO paths already there.
  `build_windows.ps1:341` globs `port\fast3d`, `port\src`, `port\audio` for `*.c`, **so a new
  tracked `.c` in either directory needs no build-script edit at all.**
- **`D4` — THE FIRST SLICE IS A STANDALONE SMOKE.** No `build_windows.ps1` edit, no gitignored
  file touched, `goldeneye.exe` never rebuilt.

---

## §2 — **THE FOUR FACTS, AND `F4` IS THE ONE THAT DECIDES `X1b`**

All `[MEASURED, BRIDGE]`, read from source this session. None of them is in any document before
this one.

- **`F1` — `gfx_current_dimensions` HAS EXACTLY ONE WRITE SITE, ONCE PER FRAME, AND IT IS `H19`'s
  ONLY INPUT.** `gfx_pc.c:6062`, in `gfx_start_frame()`, from `gfx_wapi->get_dimensions()`.
  Everything downstream derives from it: `ge_scale()` `:438`, `ge_offset_x()` `:443`, `RATIO_X/Y`,
  the viewport calc `:3977-3980`, and **`gfx_adjust_x_for_aspect_ratio()` at `:2369`, which is
  `H19`**.
- **`F2` — AND A SHIPPED PATH ALREADY OVERWRITES IT AFTER THE READ.** `gfx_pc.c:6069-6076`,
  supersample, with its own comment: *"Everything downstream (RATIO_X/Y, viewports, scissors) is
  derived from `gfx_current_dimensions`, so scaling it here makes the whole scene render at the
  higher resolution with no other changes."* **So "what does `gfx_pc.c:2362` see under an XR
  path" is one assignment in `gfx_start_frame`, and there is precedent for making it.**
- **`F3` — THE DESKTOP OFFSCREEN TARGET ALREADY EXISTS AND ITS OWNER IS A TRACKED FILE.**
  `gfx_opengl.c:942` says the inherited Fast3D *"has no framebuffer support at all"* — and this
  project added two anyway: `ss_fbo` (tvOS) and `pp_fbo` (desktop). **`ge_postfx.c`/`.h` is
  tracked; `gfx_opengl.c` is not.** That is `D3`'s precedent, and §1 records the split.
- **`F4` — ►►►►►►►► ONE DISPLAY LIST, ONE `gfx_run`, ONE SWAP — SO `a` HAS EXACTLY ONE VALUE PER
  FRAME, BY CONSTRUCTION.** `port_render.c:916-924` is the whole frame. The eye loop is game-side
  (`lv.c:819-1074`) and `geStereoEyeViewport()` (`stereo.c:229-234`) makes each eye a **half-width
  viewport of the ONE target**; `stereo.h` states *"gfx_run() is never called twice."*
  **Therefore per-eye targets that `gfx_pc.c:2362` sees are unavailable without running the frame
  twice, which `293`/`294`'s arena-pairing constraint forbids without a great deal more work.**
  `318` §2's two values of `a` are therefore not two designs. §6.

---

## §3 — **THE SLICE, AS BUILT**

| file | bytes | md5 |
|---|---|---|
| `goldeneye-native\getv\port\src\gevr_xr.h` | `7945` | `9fe2f69ce89659ac2c0459372997bf7a` |
| `goldeneye-native\getv\port\src\gevr_xr.c` | `24704` | `2de74d753289fe82b2f07c863ea10c37` |

`xrCreateInstance` -> `xrGetSystem` -> `xrEnumerateViewConfigurations` ->
`xrEnumerateViewConfigurationViews` -> `xrCreateSession`. **That is all.** No swapchain, no
`xrBeginSession`, no `xrWaitFrame`, no eye loop, no submit — a file that also created swapchains
would be answering `X1b` by construction before `X1b` had been argued.

- **EVERY REFUSAL IS PRINTED BY NAME** (`309` §5.2), through one funnel that prints and records.
  `xrGetSystem`'s `-35` is `XR_ERROR_FORM_FACTOR_UNAVAILABLE` and is stated in the output to be
  **a refusal and not a measurement**.
- **THE RECT IS READ, NOT ASSUMED.** The arithmetic banner is computed from **this run's** rect,
  and the file prints a `NOTE:` naming `XR_EXT_view_configuration_views_change` if the rect is not
  `318`'s `4140 x 3292`. That detector is the reason §0 row 6 can say "unchanged".
- **NO PERFECT DARK CODE IS COPIED**, and the header says what would be owed if any ever is:
  MIT, in `PUBLISH-MANIFEST.md` **and** at the point of use. `160`'s standing instruction holds —
  the checkout at `local-only\prior-art\perfect_dark_VR` is never re-cloned.
- **THE `318` §6 TRAP FIRED CORRECTLY AND COST NOTHING.** Writing this session's run sheet, the
  payload carried a non-ASCII em dash; **the encode threw and no file had been opened**, because
  the string is encoded and asserted first. Two of my own assertions also refused writes that were
  correct — a strict `putenv` check matching the word inside a comment. **Both refusals cost one
  retry and no file.** This is `00-STATE` §6's newest trap working, not a new trap.

---

## §4 — **THE RUN, AND IT WAS READ OFF THE DISK RATHER THAN TAKEN ON A PASTE**

`[MEASURED, BRIDGE]` `repo\xr\gevr_xr_smoke.exe` `271809` bytes at **`16:23:13`**;
`gevr_xr_smoke_report.txt` `1667` bytes at **`16:24:36`**. **The source `md5` is unchanged from
the byte written at `16:19`**, so the binary is that file, unedited. `-- repo/xr` reads **empty**:
the build output produced **zero `git status` noise**, as the sheet predicted.

```
[smoke] GL context current. GL_VERSION  4.6.0 NVIDIA 616.56
[getv][vr] extensions advertised: 41   XR_KHR_opengl_enable: yes
[getv][vr] runtime: SteamVR/OpenXR  v2.16.7
[getv][vr] system: SteamVR/OpenXR : aapvr  (vendor id 10462)
[getv][vr] view 0  recommended 4140 x 3292   max 8192 x 8192   samples rec 1 max 1
[getv][vr] view 1  recommended 4140 x 3292   max 8192 x 8192   samples rec 1 max 1
[getv][vr] rects identical across views: yes
[getv][vr] [ARITHMETIC] a per-eye = 1.060225   a two-eyes-one-window = 0.530113
[getv][vr] GL required: min 4.3  max 4.6   context reports: 4.6.0 NVIDIA 616.56
[getv][vr] SESSION CREATED.
[smoke] PASS. Session live, per-eye rect 4140 x 3292.
[smoke] EXIT 0.
```

**`41` EXTENSIONS IS NOW A THIRD CONSISTENT READING** across roughly twelve and a half hours —
`X1-0`'s control still holds, and it was checked before anything below it was read.

**►►►► `[DISPOSAL] 9a` — WHAT A PASS DOES NOT SAY.** There is no swapchain, no frame and no
submit. **It says the session lives where `D2` puts it. It says NOTHING about `X1b`, about `H19`,
about `a`, or about what anything looks like.** `gfx_current_dimensions` is still the SDL window
at `gfx_pc.c:6062`, and the `a` line above is the **same arithmetic on a freshly read rect** —
`312` §2.2 is the trap that quoting it as a property of a build would repeat.

---

## §5 — **ONE GAP I AM NOT CLOSING, AND ONE I CLOSED**

**THE GAP: `[PREDICTION] X1-0c` — the inert gate — HAS NO ARTEFACT.** §1 of the run sheet is
`-fsyntax-only` and writes no file, so "all runs complete" is `[REPORTED]` for it and there is
nothing on disk to check. **And the smoke does not stand in for it**: the smoke compiled the
`GEVR_XR_LIVE` branch, and the game build takes the `#else` shape, which was never compiled by
anything. **That gate is the only evidence that adding this file cannot break the game build**, so
it is worth one pasted `gcc exit N` before the commit rather than after. `306` §0 as generalised
by `318`: a claim about work being done is a claim about the disk, and this one has no disk to
claim from.

**THE ONE I CLOSED: THE CONTEXT-VERSION TRANSFER RISK.** The output added a fact nobody had:
`GL required: min 4.3  max 4.6`. **A session bound to a plain WGL context proves nothing about the
context SDL2 hands the game.** `[MEASURED, BRIDGE]` `gfx_sdl2.c:424-436`: every
`SDL_GL_CONTEXT_MAJOR_VERSION` / `PROFILE_MASK` call sits inside `#ifdef USE_GLES`, so **the
desktop path requests no version and no profile at all.** Rather than infer what the driver then
gives, this was read off **run logs already on disk** (`318`'s own rule):

> `[getv] GL_VENDOR=NVIDIA Corporation | GL_RENDERER=NVIDIA GeForce RTX 5090/PCIe/SSE2 |
> GL_VERSION=4.6.0 NVIDIA 616.56`

**The shipped game context is `4.6.0` — the same string the smoke's context reported — and it
sits inside SteamVR's `4.3`-`4.6` window. Measured on both sides, no new run. Slice 2 does not
have a context-version problem.**

---

## §6 — **`X1b`, AND THIS SESSION FOUND ITS CANDIDATE RATHER THAN ITS ANSWER**

`F4` says `a` has one value per frame, so `318` §2's table is **not** two designs:

| shape | what `gfx_start_frame` would install | `a` | `H19` residual |
|---|---|---|---|
| **`B1`** one wide target, today's eye loop untouched | `8280 x 3292` | `0.530113` | `47%` |
| **`B2`** per-eye target, frame run twice | `4140 x 3292` | `1.060225` | `6.0%` |

**`B2` costs `293`/`294`'s arena-pairing constraint and `258` §1.2's one-DL invariant. `B1` costs
47%. Neither is acceptable as stated, and I think that is because the fork is mis-stated.**

> **`[CANDIDATE, NOT FILED]`** `gfx_adjust_x_for_aspect_ratio()` divides by the **target's**
> aspect (`gfx_current_dimensions`, `:2369`) while the rectangle the 3D content actually lands in
> is the **viewport** (`rdp.viewport`, `:3977-3980`, derived from the game's own `Vp` — which
> `geStereoEyeViewport()` has already halved per eye). In a mono full-screen frame the two
> coincide, which is why nobody has seen it. **In a side-by-side stereo frame each eye's viewport
> is `4140 x 3292` under EITHER row above** — so if the denominator is the viewport, `a` is
> `1.060225` in both and `B1`'s `47%` is a bug rather than a design.
>
> **IT IS NOT PATCHED AND NOT FILED** (`301` §0; five is five). **It has an unchecked objection
> that could kill it outright:** `geStereoEyeAspect()` already scales the eye's aspect into the
> projection (`stereo.h`, `lv.c:873`), so a viewport-aspect denominator may **double-count the
> halving**. **It is scorable OFFLINE on grabs already held.**
>
> **`[PREDICTION] X1b-1`** — candidate right: a `GETV_STEREO=1` arm at `2560x1369` scored per eye
> reads a residual near `1.0`. **`[PREDICTION] X1b-2`** — objection right: it reads near `2.0`.
> **The two have opposite signs, so the arm cannot come out ambiguous.** `U-28` is reserved.

**SHAPE A / SHAPE B (`RUN-SHEET-314` §1) STAYS DEFERRED**, exactly as that sheet leaves it. `6%`
is not `29%`, and which of the two `H19` actually costs is what the arm above decides.

---

## §7 — WHAT NEEDS A PERSON

- **`[PREDICTION] X1-0c`** — one `-fsyntax-only` run, `RUN-SHEET-319` §1, **before the commit.**
- **THIS SESSION'S TWO COMMITS** — `RUN-SHEET-319` §5, explicit path lists, one message file per
  tree. **The 57-file username scrub is still nobody's. Leave it alone.**
- **SLICE 2 — `HIGH`, AND A FRESH SESSION'S WORK** (`00-STATE` §7c): swapchain, `xrBeginSession`
  and the event loop, then `xrWaitFrame`/`xrEndFrame` and the pacing handover `D2` defers.
- **`X1b`'s OFFLINE ARM** — §6, on grabs already held, `LOW`, no build. **It ranks `H19`.**
- **VENDORING THE OpenXR HEADERS.** The smoke includes from
  `GoldenEye64Recomp\lib\openxr\include` — **a path belonging to the OTHER LINE, `00-STATE` §6
  trap 2 by name.** Fine for a standalone smoke; **owed before the game build ever links this.**
- **`H25`** — still not filed; `317` §2.1's one-pixel bias is still its candidate.
- **`XR_EXT_view_configuration_views_change`** — still a candidate, still not a hole. The rect
  did not move across `1h 03m`, which is evidence about this hour and not about the extension.
- **`RUN-SHEET-317` §2, `RUN-SHEET-316` §3, `[PREDICTION] 4a`, `--max-depth-drift`, `GX-0`,
  lane 3** — all unchanged. **`U-27` must not be guessed from a grep. `E3` is CLOSED.**

**`169` NEXT ID = `U-28`. NEXT INSTRUMENT HOLE = `H25`.**
