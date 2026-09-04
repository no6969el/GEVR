# 49 — the eyes were never two images. Root cause found

**2026-08-23, session following `47`/`48`.**

**Read this before `47`.** `47`'s measurements were taken on a build where both
eyes rendered the same picture, so every conclusion it drew about eye GEOMETRY
is void. Its *method* is still the best thing in this project. Its *findings*
are not.

---

## THE ROOT CAUSE, measured

```
[gevr] fb eye0: pairs=2 recorded=2 overrideSet=1 overrideFbPairIndex=1 overrideAddr=0x003DA800
[gevr] fb eye1: pairs=2 recorded=2 overrideSet=1 overrideFbPairIndex=1 overrideAddr=0x003DA800
[gevr] fb verdict: 2 framebuffer pairs but only pair 1 is redirected. The other 1
       are SHARED between the eye passes - if the world is in one of them,
       eye 1 overwrites eye 0.
```

**The workload has TWO framebuffer pairs. `setOverride()` redirects exactly ONE
`RenderTargetKey`.** Pair 0 is shared between the two eye passes.

`interpolationTargetKey` is chosen by scanning pairs from the last backwards and
taking the first early-present candidate — it picked pair 1. Everything drawn
into pair 0 goes to the *shared* target for its address, for both eyes.

Combined with the other measured asymmetry — **eye 0 has no override target at
all at frame 0**, because `overrideTarget` is only assigned when
`usingMSAA || (frame > 0)` — eye 0's finished image lives in the shared default
target, where eye 1's pass then draws over it.

**Two targets, one world.** Both halves end up showing the same eye.

---

## Why this took a whole session: everything else was correct

Each of these was in question. All are now numbers, not arguments. **Do not
re-investigate any of them.**

| | Evidence |
|---|---|
| `viewOffset` symmetry | eye1-eye0 = pure x translation `dx=-6.350 dy=0 dz=0`, **worst rotation term 0.000000**, sustained. This was `47`'s stated next action. It is clean |
| Per-eye frustums | `proj EYE 0 m20=-0.14106`, `EYE 1 m20=+0.14106`. Exactly mirrored |
| Clip-w convention | `m23 = -1.00000`. Negative, as assumed since 3c. `47`'s sign reasoning was sound |
| Override reaches the projection | `overrides=21` per eye |
| Upload happens, with distinct data | `count=22` per eye; `hash eye0=ED96E755873A6190 eye1=EC93128A61777630` |
| Upload is ordered | memcpy → record copyBufferRegion → waitForUploaders → execute → wait, **per eye** |
| Render targets distinct | `eye0=90 eye1=90 distinctTargets=90` sustained |
| Present textures distinct | `present source: eye0=...E2F0 eye1=...14D0` |
| **The render RESPONDS to the matrices** | `-Offset 50` vs `-Offset 0`: **81% of pixels differ, mean 21.0** |

And the output:

```
eye width 800:  mean|diff| = 0.025    0.14% of pixels differ
```

0 px disparity at every depth — sky, cliffs, road, gun — correlation 0.989-1.000.
**Predicted 113 px. Measured 0.**

---

## THE FIX — designed, NOT BUILT. Next session starts here

**Make eye 0 symmetric with eye 1.** Today eye 1 gets its own scratch target and
eye 0 does not; that asymmetry is the bug's home.

1. Size `eyeColorTargets` as `displayFrames * 2`, indexed `[frame*2 + eye]`.
2. Give **both** eyes a scratch target — delete the `if (eye > 0)` special case
   in the eye loop (`rt64_workload_queue.cpp` ~1160).
3. Publish both: add `vrEyeZeroTarget` alongside `vrEyeOneTarget`, cleared before
   the targets they name are destroyed (the rule already written for
   `vrPresentEyeTexture`).
4. Present samples the published target for **each** half, in both the SBS path
   and the XR eye loop — the left half must stop using `renderParams.texture`.

With both eyes composited into their own targets, eye 1 redrawing shared pair 0
no longer destroys anything eye 0 still needs: the passes are already fully
serialised by `execute(); wait();`.

### The gate — write it before the code

`.\vr.ps1 -Flat`, stand still, screenshot, split at the seam, cross-correlate.

**Distant content must sit 113 px ± 5 apart, right eye further LEFT.**

The log prints its own prediction, so this is a gate with a number in front of
it, not an impression:

```
[gevr] PREDICTION: eye1 - eye0 = -0.2821 ndc = -94.2 px per 668-px half-frame
```
(scale to the screenshot's half-width: 800 px → **-113 px**)

**What would make it fail:** today's build, which measures 0. No headset needed.

**Regression gate:** `.\vr.ps1 -NoXr` must be unchanged. It is the path that must
never break.

---

## What this VOIDS

Same shape as `43` voiding the MSAA-era results.

| Claim | Where | Now |
|---|---|---|
| "Horizontal disparity is 44 px in the WRONG DIRECTION" | `47` | **Void.** Two identical images cannot produce a geometric disparity |
| "The residual is not explained... plausibly TWO effects" | `47` | **Void.** There was no signal to have a residual |
| "`-SwapEyes` moves the fault to the other eye" | `47` | **Needs a new explanation** |
| "One of the two RENDERED IMAGES is wrong, the eyes are not symmetric" | `47` | **Wrong shape.** There is only one rendered image |
| "Stereo validated" / 3e / 3f-3 "confirmed" | `10`, `18`, `28` | **Suspect.** `overrideFrustum` works — the picture responds — but no measurement ever showed TWO images |
| "Exit taking the machine down — Fixed, `29`" | `00` | **Incomplete.** See Teardown |
| "The headset's 90 Hz is queried at startup, logged, and never used" | `00` | **False.** `ge_vr_xr.cpp` never queried the display rate at all. The project assumed 90 Hz from a sentence describing code that does not exist |
| "`ds_option: 4`" | `00` | It is `1` |
| "`-Sbs` does not split the window" | `39` O16 | **Launcher bug, FIXED.** `-Sbs` was only set inside `if (-not $NoXr)` |

---

## The wrong turns — five falsifications in one session

The pattern matters more than the individual errors. **Every one came from
reasoning about a mechanism instead of measuring it** — the exact failure `47`
documented, repeated immediately.

### 1. Desktop vsync was capping the headset
`vsyncEnabled = true`, never assigned; XR submits on the present thread.
Coherent. **Killed by the user's monitor being 180 Hz.** A 180 Hz vsync cannot
produce 60.0 fps. *I did not know the machine. One question would have saved it.*

### 2. GPU-bound on pixels
`-ResScale 0.35` → 3.2 Mpx/eye, eight times fewer. **Ran at ~16 fps instead of
60.** Eight times less work, four times slower. **Still unexplained — own slice.**

### 3. RTSS was frame-limiting
Afterburner + `RTSSHooksLoader64` resident, and an exact 60.0 looks like a
limiter. **`Limit=0`, `EnableHooking=0`.** Two minutes, and it would have been a
very convincing false lead if found later.

### 4. A shared `viewProjTransformsBuffer` race
Written up, **approved by the user, and falsified while implementing it**:
`threadRenderFrame` ends `execute(); wait();`. No upload can race. *A fix that
works for the wrong reason is worse than no fix.*

### 5. The teardown crash was the XR `waitForGpu` timeout
Wrong: **`-Flat` never sets `GE_VR_XR`**, so that path did not execute.

---

## Teardown — a real defect, but NOT tonight's crash

```cpp
WaitForSingleObject(g_fenceEvent, 1000);   // result DISCARDED
```

Shutdown then logs `shutdown: gpu idle` **unconditionally** and releases the
allocator, command list, swapchains and fence. If the GPU has not drained in one
second we free resources it is still reading, and the log says all was well.

**Fix (not built):** return the wait result; retry in 500 ms slices up to ~10 s;
if it still has not drained, **deliberately leak rather than release** and log
`GPU DID NOT DRAIN`. The process is exiting; the OS reclaims. Releasing is the
dangerous act. Never print `gpu idle` unless it is.

### Tonight's machine crash was NOT this

The user pinned the process to the X3D CCD (Process Lasso, 9950X3D) in a
**`-Flat`** session — no OpenXR, so none of the above ran. They saw an error and
powered the machine off; the Kernel-Power 41 is that manual shutdown.

**Then the BIOS lost its memory settings and would not boot until a DIMM was
physically removed.** No user-mode process can do that. That is memory training
/ EXPO instability at the firmware level.

**Conclusion: the machine-level fault is a hardware/BIOS stability issue, not
this project's code.** Minidumps exist at `C:\Windows\Minidump\082226-*.dmp` if
anyone wants to confirm. Worth re-testing memory stability before trusting any
future "it crashed the machine" report — otherwise it will be attributed here.

---

## What was BUILT and works — the durable output

### `-Flat` — stereo measurable with no headset
`.\vr.ps1 -Flat` — VR geometry, side by side, XR off. Every measurement in this
document came from it. It replaces the mirror-recording method for image
questions: no headset, no ffmpeg, no hoping the camera was still.

### The measurement method
Split at the seam, cross-correlate per depth band, compare against `PREDICTION`.
Find the seam by minimising `mean|L-R|` over candidate widths — that is what
turned "the halves look similar" into "0.14% of pixels differ".

### The instruments, all inert, all in `gevr.log`

| Line | Answers |
|---|---|
| `viewOffset eye 0/1` | `47`'s stated next action, in full |
| `eyeDelta:` (1 Hz) | Do the eyes stay a pure IPD apart **while leaning**? Prints its own verdict |
| `proj GAME` / `proj EYE` | The game's projection and both eyes', before and after override |
| `PREDICTION:` | Expected disparity in px, **before** anyone looks at a picture. This is `47`'s O19 |
| `present source:` | Did both halves sample the same texture? |
| `upload eyeN:` | overrides / count / hash / destination, per eye |
| `fb eyeN:` | **pairs / recorded / overrideSet / pair index / address — this is the line that found the bug** |
| `DISPLAY PERIOD:` | The headset's real cadence, from `XrFrameState::predictedDisplayPeriod` |
| `frame budget` + `stage ms:` | waitFrame / locate / waitForGpu / record / execute / endFrame |

### `build.ps1`
Disables MSBuild node reuse (13 lingering workers) and `vctip.exe`, filters ~200
benign warnings so a real error is visible, and **warns when `gevr.log` predates
the exe** — `07` GOTCHA 4, which has cost this project two rounds.

---

## Start here next session

1. **Build the fix above.** It is designed, gated, and needs no headset to verify.
2. **Then the teardown fix**, before long sessions.
3. `-ResScale` making things slower is unexplained and owns the 60 fps question.
4. Read `DISPLAY PERIOD` before ever calling 60 fps a performance problem again.

**Do not judge anything by wearing it until `-Flat` measures two different
images.** That is the mistake this entire document exists to record.
