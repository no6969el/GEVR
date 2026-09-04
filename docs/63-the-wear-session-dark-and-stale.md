# 63 — the first wear session since `36`: dark, stale, and what it is not

**2026-08-23, ~12:00. Observed, measured, NOT diagnosed. Read this before
touching the XR path.**

---

## THE THING NOBODY NOTICED UNTIL THE HEADSET WAS ON

**The XR path has not been worn since `36`.**

`43`, `47`, `49`, `50`, `51`, `52`, `54`, `56`, `57`, `58` and `61` — **eleven
documents, every one of them measured in `-Flat`, and `-Flat` never sets
`GE_VR_XR`.** Eye targets were restructured, transform buffers split, MSAA
forced, four instruments added and a controller slice built, and not one frame
of it was ever seen through the headset.

**So a regression anywhere in that window would have been invisible, and would
look exactly like what this session found.** This belongs at the top of the
protocol: **`-Flat` is not a substitute for wearing it; it is a substitute for
MEASURING it.**

## What was observed

| | |
|---|---|
| The image | **~1% brightness.** Mean 2.29/255, max pixel 72, on the FLAT WINDOW as well as in the headset |
| Motion | **Head and controller movement do not change the image** |
| Liveness | **Not frozen.** Two captures 3 s apart differ in 3.58% of pixels, and brightness drifted 2.29 → 1.63 |
| A flicker, seen once | The screen briefly showed **the save-file select screen**, correctly, then returned to the dark stuck frame |
| Input | Not confirmed reaching the game |

**The flicker is the most informative thing in the session.** A correct, bright,
current screen appeared for an instant and was replaced by a stale dark one.
**That is not a game that is hung, and not a scene that is dark. That is the
wrong FRAME being presented, with the right one occasionally getting through.**

## What the instruments said at the same moment

```
render passes: eye0=90 eye1=90 distinctTargets=90     sustained, all equal
60.0 fps                                              the VI clock - docs\60
DISPLAY PERIOD: 11111128 ns = 90.0 Hz                 the headset's real cadence
xr input: bound profile = /interaction_profiles/oculus/touch_controller
xr input: aim L valid=1 / aim R valid=1               both hands tracked
xr input: action 'move' / 'turn' / 'fire' / 'use' / 'weapon_prev' FIRED
```

**Everything that reports, reports healthy.** The renderer is running two eye
passes into distinct targets ninety times a second while the screen shows a
stale frame. **Whatever is wrong is not visible to a single instrument this
project owns**, which is the same shape as B1 and probably not a coincidence.

## What this is NOT — measured, not argued

| Not | Because |
|---|---|
| A hang | The image changes; the game reached the save-select screen |
| A dark SCENE | The save-select screen appeared **correctly bright** in the same session |
| An sRGB/format mismatch on the XR swapchain | The **flat window** is equally dark, and under `GE_VR_XR` that window takes the ordinary present path, not the eye path |
| The `61` controller slice | Input is published and firing; nothing in it touches the render or present path, and it modifies **no** RT64 file |
| `view FINAL` log spam | Gated off and rebuilt; the symptom is unchanged with `view FINAL` count = 0 |
| Menus disabling input | No menu is visible on the flat window in the captures |

## Candidates, ranked, each with its cheap test

**1. Present is showing a STALE target.** The flicker says the correct frame
exists and is occasionally shown. `50` changed eye target indexing to
`frame * 2 + eye` sized `displayFrames * 2`; under XR at `rr_manual 90` there
are multiple display frames per workload, and the interaction between the
interpolated-frame counters and the eye targets **has never been exercised with
a live XR session.**
**Test:** `rr_option: "Original"` (one display frame, no interpolation) with the
headset on. If the image comes alive, the fault is in that interaction. One
setting, one launch, and `57` already proved the setting is safe to move.

**2. The eye target contents are stale in the same way B1's are wrong.** B1 says
something writes eye 0's texture during eye 1's pass. **A pipeline that puts the
wrong pixels in a target may also put OLD pixels in it.** These may be one bug.
**Test:** the write census in `58`, which is already planned.

**3. The XR swapchain acquire/wait/release ordering.** If an image is released
before the copy completes, the compositor shows the previous one.
**Test:** log the swapchain image index per eye per frame; a repeating or
non-advancing index names it.

**4. Brightness is a separate second bug.** Possible, and it must not be assumed
to be the same fault. The save-select screen being bright argues the pipeline can
produce a correct image, so darkness may be scene-specific — **O6, "hard to
see", has been open since `33` and was never triaged.**

## THE BISECT, and it is the first thing next session

**Three paths, three launches, in this order. Do not skip step 1.**

| # | Run | Question |
|---|---|---|
| 1 | `.\vr.ps1 -NoXr`, **play a level properly** | Is the GAME intact on this build? Today only reached the menu — **G4 was never fully run** |
| 2 | `.\vr.ps1 -Flat`, play a level properly | Does the EYE path break it, with no XR involved? |
| 3 | `.\vr.ps1`, worn | Does the XR path break it? |

**Whichever step first shows the dark stale frame names the layer.** If step 1
shows it, nothing VR-side is involved at all and the whole search moves.

**This bisect should have been run before the headset went on.** It costs three
launches and it would have cost nothing to know.

## The one unambiguous WIN of the session

**The full shutdown sequence executed, cleanly, TWICE:**

```
[gevr-xr] shutdown: begin
[gevr-xr] shutdown: session ended
[gevr-xr] shutdown: gpu idle
[gevr-xr] shutdown: xr session destroyed
[gevr-xr] shutdown: complete, clean
```

**`00-START-HERE` records that `session ended` and `gpu idle` have NEVER
executed** — every close since `29` went through the no-session path because the
headset was asleep. This is the first time the real teardown has run with a live
session, and it is the path that once took the whole machine down. **Twice, in
order, clean. Promote it to DONE — observed.**

## Also worth keeping

- **`DISPLAY PERIOD: 90.0 Hz`, read for the first time.** `49` established the
  headset's rate had never been queried. It is 90, and `render passes` sustains
  90 per eye. `60`'s finding holds in the headset.
- **The Pimax Crystal Super binds as `oculus/touch_controller`, not Index.**
  Both the user's research and `61`'s expectation said Index. **Suggesting each
  profile independently is the only reason anything bound at all** — a single
  batched suggestion built around Index would have left every control dead with
  no error anywhere.
