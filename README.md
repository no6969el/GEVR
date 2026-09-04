# GEVR — VR for GoldenEye 007, via N64 recompilation

Bringing GoldenEye 007 to PCVR as a true 6DoF port, by attaching to a
statically recompiled build of the game rather than emulating it.

**Status, 2026-08-23 (late): the game runs in a headset at 5838x4498 per eye,
with head tracking and 6DoF, from the user's own ROM.** Head translation and
rotation are live, the head-pose origin is recentred, and hip-fire aim is
decoupled from where you look.

**It is NOT yet stereo, and never has been.** Both eye halves carry the same
image â€” eye 1's. This was only discovered when it was first *measured* rather
than judged by eye; every earlier "stereo validated" claim in this repo was made
without anyone comparing two images. See `docs/49` and `docs/57`.

**Each eye pass is individually correct**: run one alone (`-Flat -SkipEye`) and
it renders its full displacement. The replacement happens only when both passes
run. The live hypothesis is that present's resolve is keyed on the framebuffer
address the two eye targets share.

**Stereo is now measurable from a screenshot with no headset** (`-Flat` plus
`tools/gevr_stereo.py`), which is what made the last several results possible.

**Start at `docs/00-START-HERE.md`, then `docs/57` for the blocker and `docs/39`
for open work.** `docs/47`'s image findings are VOID â€” its method is still the
best thing in it.

## What is here

| Path | What |
|---|---|
| `patches/ge_vr_bindtest.c` | The VR projection hook. Builds a per-eye asymmetric frustum inside the game's own projection setters. |
| `patches/interpolation.c` | Six fixes that make the game render correctly at 90/180 Hz â€” a prerequisite for comfort in a headset, not a nicety. |
| `xr/xr_probe.cpp` | OpenXR reconnaissance. Reports per-eye FOV, IPD, cant, swapchain sizes, refresh rates. |
| `xr/xr_stereo.cpp` | Standalone stereo renderer. Validates the projection maths in a headset, independently of the game. |
| `docs/` | The full record: build gotchas, the interpolation diagnosis, measured hardware facts, the plan, and every wrong turn with its evidence. |

Most of the VR rendering work lives in RT64 rather than here â€” see
`docs/12`, `docs/17` and `docs/18` for why, and the licence note below.

## This is not a standalone build

`patches/*.c` compile **only** inside a checkout of
[`cblock85/GoldenEye64Recomp`](https://github.com/cblock85/GoldenEye64Recomp),
where they `#include "patches.h"`. Drop them into that tree's `patches/` directory
and build per `docs/06-replicate.md`.

That tree links GPL-3.0 `N64ModernRuntime`. **It stays external and is never
vendored here.** This repo is MIT; keeping the two apart is deliberate.

`xr/*.cpp` are standalone and depend only on the Khronos OpenXR loader and D3D12.

## No ROM data, ever

Nothing here contains or requires distributed game data. You supply your own
retail cartridge dump. The `.gitignore` refuses ROM extensions on principle.

## Quick start for the XR tools

Fetch the OpenXR loader (URL and rationale in `docs/09-openxr-probe.md`), then
from a VS developer shell:

```powershell
cl /std:c++17 /EHsc /O2 /nologo xr\xr_stereo.cpp /I lib\openxr\include ^
   /link lib\openxr\native\x64\release\lib\openxr_loader.lib ^
         d3d12.lib dxgi.lib d3dcompiler.lib user32.lib shell32.lib
```

Run `xr_stereo.exe tint` to tint the left eye red and the right blue. That is the
only check that distinguishes real stereo from a monoscopic image with correct
perspective â€” the latter fuses, looks like a room, and survives head movement, so
parallax judgement alone will mislead you.

## Three things that will cost you a day each if unread

- **Check which OpenXR runtime you are on**, in `gevr.log`. This project's
  measurements were taken on SteamVR/OpenXR at 4140x3292 per eye and the rig
  later moved to Pimax OpenXR 0.1.0 at 5838x4498 with a different reported FOV,
  silently. `docs/40`.
- **Verify the instrument before trusting a test.** `render passes: eye0=N
  eye1=N distinctTargets=N` must all match, or the second eye is not being drawn
  and anything you conclude about it is void. `docs/43`, `docs/47`.
- **Measure, do not describe.** Record the headset mirror and cross-correlate the
  two halves; expected disparities are computable from the live FOV. `docs/47`
  has the method, and it is the only diagnostic that produced correct answers.

## Two more things that will cost you an hour each

- `docs/07` â€” `GoldenRecomp.exe` crashes with an access violation unless the
  working directory is the repo root. It reads exactly like broken recompiled code
  and is not.
- `docs/09` â€” `XR_CURRENT_API_VERSION` from the Khronos 1.1.x headers is rejected
  by SteamVR, which implements 1.0, and the loader reports it only as "chained
  CreateInstance call failed". Ask for `XR_API_VERSION_1_0`.

## Licence

MIT. See `LICENSE`.

RT64 (`github.com/rt64/rt64`) is **also MIT**, and a substantial part of this
project's rendering work is changes to it. Those belong upstream as a fork or PR
against RT64, not vendored here. Changes to the recomp host are a different
matter â€” that tree links GPL-3.0 `N64ModernRuntime` and stays external. The split
and the evidence for it are in `PUBLISH-MANIFEST.md`.
