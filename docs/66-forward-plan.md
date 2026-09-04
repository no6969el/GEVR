# 66 — the forward plan. Two tracks, and they do not block each other.

**2026-08-23, ~14:00. Written as the handoff after `64` and `65`.**

**Read `65` first, then this. `64` is the evidence behind `65`.**

---

## WHERE WE ACTUALLY ARE

**The headset works.** Live, bright, correct image, at 90 Hz, with head
tracking, recentre, both hands tracked and five controller actions firing.
`.\vr.ps1` — SBS is the default now, `65` explains why.

**But it is not yet VR.** Two things are missing, and naming them separately
matters because a day and a half was lost to treating one blocker as everything:

| | What is wrong | Why it stops it being VR |
|---|---|---|
| **B1** | Both eyes carry the same image, 0 px disparity | No depth. Everything doubles. It is a large flat screen strapped to your face |
| **AIM** | The tracked controller pose does not drive aim | The Touch controllers work as a **gamepad**. Motion does nothing. You are not reaching into the world |

**These are independent.** Nothing about hand aim depends on stereo being
fixed, and nothing about stereo depends on aim. **They can be worked in either
order, or by two sessions in parallel.** That is the single most useful fact in
this document.

---

## TRACK A — B1, stereo

**State: measured worn for the first time in `65`.**

```
PREDICTION: eye1 - eye0 = -124.7 px per half-frame
MEASURED:   0 px.  corr 1.0000 at dx=0.  mean|L-R| = 0.001
```

**Twelve hypotheses have been falsified.** Do not add a thirteenth by argument.
What is known, and it is a lot:

- Each eye pass, run alone, renders its full displacement correctly (`56`).
- The two eyes render into distinct targets, `shared=0` (`50`).
- The per-eye transform buffers are distinct (`51`).
- The per-eye matrices are computed correctly and distinctly (`57`).
- Every drawn index is overridden; coverage is not the problem (`54`).
- The world IS the redirected framebuffer pair (`52`).
- Present's resolve is not it (`58`, from source).
- MSAA is forced off, so it is not that (`43`).

**The surviving statement, from `58`:** eye 0's pass renders eye 1's view
whenever eye 1's pass also runs.

### What has NEVER been done, and is now possible

**Every one of the experiments above was run in `-Flat`.** `64` established
`-Flat` is structurally blind to the eye present stage. **And until today the
headset did not work, so none of them could be re-run worn.**

**First actions, worn, no code:**

1. `.\vr.ps1 -Offset 500` — 1000-unit separation. Any per-eye response is
   enormous and unmissable. `57` ran this in `-Flat` and got zero.
2. `.\vr.ps1 -PresentEye 0` then `-PresentEye 1` — separates "the target holds
   the wrong image" from "present reads the wrong target". `58` planned this and
   it was never run worn.
3. `.\vr.ps1 -SwapEyes` — pose and frustum together.

**Gate for all three:** the halves must differ. `65`'s harness measures it —
split at the seam, cross-correlate, compare to the `PREDICTION:` line. **A
number, before anyone looks.**

**WARNING: `-SkipEye` returns a false answer under XR** (`64`). It disables only
the present-side eye render. Use it in `-Flat` only.

---

## TRACK B — decoupled hand aim. This is what makes it feel like VR.

**State: the hard parts are already built and confirmed worn.**

- **Hip fire is decoupled from the head, confirmed worn** (`36`).
- **The firing path is understood**: hip fire reads `crosshair_angle`, and `38`
  corrects `37` in three places. **Read `38` before `37`.**
- **The controllers bind and fire**: `/interaction_profiles/oculus/touch_controller`,
  both hands `aim` poses valid, five actions firing (`61`).

**So the pose is arriving and the firing path is known. What is missing is the
wire between them.** `xr input: aim L valid=1 pos=...` is logged every session
and nothing consumes it.

### The slice, and it is small

Drive `crosshair_angle` from the **right hand's aim pose** rather than from the
gamepad stick, in the same place `36` decoupled it from the head.

**Write the gates before the code — `48` rule 2:**

| Gate | What would a working build have to do differently to fail it? |
|---|---|
| Point the controller left, crosshair goes left | A build wired to the stick cannot pass this; the crosshair would not move at all |
| Hold the controller still and move the head | Crosshair must NOT follow the head. This is the whole point of "decoupled" and `36` already proved the head half |
| Fire while pointing off-centre | The shot must land where the controller points, not where the head looks. `38`'s firing path decides this |

**The trap, and it has bitten this project seven times (rule 6):** check who
else writes `crosshair_angle` before writing it. `38` found the firing path
reads it back. A value written and then overwritten by the game's own logic
returns a confident false negative.

**Aim mode is separate and still head-locked** (`36`). Do not fold it in.

---

## WHICH TO DO FIRST

**Recommendation: TRACK B.**

Not because B1 matters less — it is the headline blocker — but because:

- **Track B has never been attempted**, and its prerequisites are all built and
  confirmed worn. It is the shortest path from "an Xbox controller" to "reaching
  into the world".
- **Track A has twelve falsified hypotheses.** It needs the worn experiments in
  `65` and `58` run and measured before anyone theorises again, and that is a
  measurement session, not a building session.
- **A day and a half went into one blocker.** Shipping a visible capability
  breaks that, and the aim slice is the one that changes how it feels.

**But B1 is the one that decides whether this is VR.** Do not let Track B
become a reason to stop measuring Track A.

---

## THE OPEN DEBT — do not let these rot

| | |
|---|---|
| **B2 is NOT fixed** | `-Sbs` is a workaround. The freeze is load-dependent, so a race is still there. `-NoSbs` reproduces it on demand — that is the reproduction case, and it is cheap |
| **The teardown crash** | 100% reproducible, `PresentQueue::threadPresent` -> `VIRenderer::render` -> `setSRV`, 0x2C. `teardown: present thread drained` prints and is false. Was on the DONE list; `64` reverted it |
| **The XR-only present pass distorts** | One eye distorted worn, menus "a zoomed in version of what's on the screen" — `25`'s blit bug, in the per-eye present render. Separate from B1 |
| **`59`'s symptom A** | Quit-to-menu black under `-Flat` = the limiting case of the corrupt start menu. One fault, not two. Unmeasured |
| **`-SkipEye` under XR** | Returns a false answer. `00-START-HERE` calls it the best diagnostic in the project; true in `-Flat` only |

---

## THE ONE RULE THIS SESSION ADDED

**A number can be measured correctly and still be the wrong number.**

"Mean 2.29/255" was true for eleven documents and said "dark". `(image/255)**0.35`
said "a correct frame, frozen" — one line, never run. The brightness was a fade
caught early and there was never a brightness bug at all.

**Rule 3 says measure, do not describe. This session's corollary: look at the
picture as well as the number.**
