# 125 — R3 AND THE PREVIOUS POSE. THE VIEW PATH IS DONE, AND IT WAS NOT ENOUGH.

**2026-08-24. Two more builds, both worn. The head-turn artifact survives a view
path that is now, as far as we can measure, correct.**

---

## §1 — WHAT WAS BUILT

### `125` — R3. THE POSE FOR THE INSTANT A PASS WILL BE SHOWN.

**`124` measured why `121`-`123` did nothing: the passes of one workload are
RENDERED back-to-back in ~2 ms but DISPLAYED 11.11 ms apart, and the host
refreshed every 11.11 ms — so every pass read the same slot.** The config was
the wrong channel: one value for passes that need different answers.

**So each pass now asks for the pose predicted at
`predictedDisplayTime + i * displayPeriod`** — via `xrLocateViews` called from
RT64's workload thread, matrices handed straight back rather than through the
config.

> **`poseChg` went from 0 to 91 after reading zero on three consecutive builds.
> `poseRefresh=183` (two eyes x 90). No XR errors — the Pimax runtime is happy
> being located from the workload thread, which R1 predicted.**

**WORN: "overall it feels better, but the same thing is happening."**

### `126` — THE PREVIOUS PASS'S POSE

**`rt64_projection_processor.cpp:165` multiplied BOTH the current view and the
PREVIOUS view by the SAME eye transform — and the comment above it said so:**

> *"The previous-frame pair feeds velocity and motion vectors. Using the same
> eye transform keeps them consistent; a future refinement is a separate
> previous head pose, which would make motion vectors correct across head
> movement too."*

**With the same pose on both, RT64's velocity and motion vectors see ZERO camera
motion from head rotation.** A stationary object has real screen-space motion
when the head turns; RT64 was told it had none.

**It could not have been fixed before `125`, because there was no per-pass pose
to put there.** Each pass now carries the previous pass's pose, cached across
workloads so pass 0 gets a real one. Gated by `hasPrevViewOffset`.

**AND THE WEARER'S ANSWER CONFIRMED THE SHAPE OF IT BEFORE THE BUILD RAN.** Asked
whether all objects have real screen-space motion under head rotation, he said
the artifact happens on everything and he only uses characters because they are
easiest to see. **A camera-motion fault must be universal. It is.**

**WORN: "it almost feels like the ghost doesn't want to show up or can't...
so much tighter now... but it's still absolutely happening."**

---

## §2 — A RETRACTION, AND IT CHANGES THE CONCLUSION

**`124` §3 recorded T7 as cleanly exonerating RT64's frame interpolation:
`rr_option "Original"`, interpolation off, ghost still present.**

> ## **THAT ELIMINATION IS VOID. THE TEST WAS CONFOUNDED.**

**With `rr_option: "Original"` the submit rate dropped to 60 into a 90 Hz panel**
(`submits=60`, measured). **So the compositor was repeating frames — which
produces doubling by a DIFFERENT mechanism.** "Ghost still present" in that run
says nothing about interpolation, because the run guaranteed a second source of
doubling.

**Rule 10, and it matters:** that false elimination is what kept the search on
the view path for the rest of the evening.

---

## §3 — WHERE THAT LEAVES IT: THE STRUCTURAL ARGUMENT

**The panel is 90 Hz and fixed. The sim is 60 Hz and structurally cannot be
otherwise — `92`, the integer tick.**

**Sixty real frames on a ninety-hertz display has EXACTLY THREE treatments:**

| | | Status |
|---|---|---|
| **1. Repeat 30** | visible doubling on motion | What T7 measured |
| **2. Interpolate 30** | approximated frames; the approximation shows on head rotation | **What we do now, and it is as good as we can make it** |
| **3. Make the sim 90** | every frame real | **Route B** |

**AND THE NUMBER THAT NEVER MOVED:**

> ## **`dupSrc` HAS READ 30/90 THROUGH EVERY BUILD TODAY** — the stride fix, the
> phase fix, the per-pass read, the 90 Hz host refresh, the display-time
> prediction, and the previous-pose fix. **Thirty frames a second are not real,
> and nothing we built could change that, because nothing we built addressed
> it.**

**The view path is now correct as far as it can be measured:** 90 distinct
images, 90 distinct poses each predicted for its own display instant, both eyes
from one instant, correct previous poses feeding motion vectors. **The residual
is the thirty frames per second that are not real game frames.**

---

## §4 — WHAT THIS IS NOT

**IT IS NOT A CLAIM THAT ROUTE B IS PROVEN NECESSARY.** It is a claim that:

1. Every view-side cause has been eliminated by measurement and by wearing it.
2. The one remaining structural fact — 30 unreal frames a second — has been
   constant all day and is untouched.
3. `119`'s gate CONFIRMED `118`'s model of the timebase (`delta=1 [1..1]`,
   `clk=1 [1..1]`, `gdelta=1000 [1000..1000]`, flat).

**The honest residual possibility: RT64's interpolation could be IMPROVED rather
than replaced.** T7 was supposed to test that and was confounded. **A clean test
is hard on this hardware** — 60 into 90 cannot be made 1:1 on a 90 Hz panel, so
any "interpolation off" run introduces repeats instead. **That is itself part of
the argument for option 3.**

---

## §5 — THE OWNER'S QUESTION, ANSWERED

He asked, before agreeing to P1: *"I can't properly judge if Route B is needed if
possibly my only issue is the head turn. Perhaps the world IS fine if my head
was."*

**The head is now as fixed as the view path can make it, and the artifact
remains.** That was the right order and it produced the evidence it was meant
to.

**Route B moves from LAST RESORT to THE PLAN — `126`.**
