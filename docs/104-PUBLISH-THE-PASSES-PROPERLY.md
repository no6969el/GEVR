# 104 — PUBLISH THE PASSES PROPERLY. THE PRESENT QUEUE ALREADY KNEW HOW.

**2026-08-24. Follows `103` directly. `103`'s mechanism was right and its first
implementation was wrong in a way that measured beautifully.**

---

## §1 — WHAT `103`'s NAIVE VERSION PROVED, AND WHAT IT COST

**`-EyeInterp`, one launch, in a level, read from the log with the headset on
the desk:**

| | Before | `-EyeInterp` (naive) |
|---|---|---|
| **`reused`** | **30 /s** | **0** |
| `submits` | 90 | **13** |
| fps | 60.0 | **16.3** |
| `xrWaitFrame` | 9.15 ms | **75.40 ms** |

> **`reused` went to ZERO. The mechanism in `103` is REAL: those interpolated
> eye images exist and publishing them removes every duplicate submission.**
>
> **And the frame rate collapsed to a sixth.**

**`103` §4 predicted the hazard and predicted the wrong symptom.** It said the
lifetime problem would most likely show up as a `0x139` bugcheck. **It showed up
as a stall** — the present thread reading a target the workload queue was still
writing, and the implicit GPU synchronisation serialising a pipeline that is
supposed to overlap. **`xrWaitFrame` at 75 ms is the compositor pacing an
application that can no longer keep up, not a stall in our submit loop —
`72` exonerated that loop and this does not re-accuse it.**

**Worth stating plainly: taking the risk was right.** The alternative was a
session spent reading the handshake to answer a question one launch answered,
and the cost was a wasted launch rather than the reboot that was on the table.

## §2 — THE FIX IS NOT A NEW HANDSHAKE. IT IS THE ONE THAT EXISTS.

**The naive version invented a rendezvous: publish the newest pointer and hope
the reader is not mid-copy. The present queue does not need to be told which
pass is ready — IT IS ALREADY WALKING THEM IN LOCKSTEP.**

`rt64_present_queue.cpp:270-296`:

```cpp
for (int32_t i = 0; i < framesToPresent; i++) {
    if ((framesToPresent > 1) && (usingMSAA || (i > 0))) {
        std::unique_lock<std::mutex> interpolatedLock(...interpolatedMutex);
        ...interpolatedCondition.wait(interpolatedLock, [&]() {
            return (frameCounters.available > targetIndex) || ...;
        });
        colorTarget = ...interpolatedColorTargets[targetIndex].get();   /* <- pass i */
    }
```

**`i` maps 1:1 onto the workload queue's `frame`** — `i == 0` is the real frame,
`i > 0` are the interpolated passes, which is the same mapping already used to
pick `interpolatedColorTargets[i - 1]`.

> **So the eye targets are indexed the same way and inherit the same guarantee.
> `48` rule 8: when two things must agree, do not synchronise them — remove the
> second one.** The recentre was fixed by exactly this move in `46`.

## §3 — AS BUILT

**Four files. No new patch name. No `CMakeLists` change.** Backups `.bak104`.

| File | Change |
|---|---|
| `rt64_shared_queue_resources.h` | `vrEyePassTarget[2][VR_EYE_PASS_MAX=8]`, `vrEyePassCount`, and the `vrEyeInterpUsed` counter |
| `rt64_workload_queue.cpp` | Publishes **every** pass at its own index. **The legacy `vrEyeZeroTarget`/`vrEyeOneTarget` are still published at `frame == 0` and are untouched** |
| `rt64_present_queue.cpp` | At the eye block, takes `vrEyePassTarget[eye][i]` when the knob is on, the index is in range, the count covers it, and **both eyes are non-null** |
| `rt64_render_context.cpp` | `interpUsed=` on the once-a-second `render passes:` line |

**Three decisions worth knowing before reading a result:**

1. **PUBLISH ORDER IS DELIBERATE.** The targets are stored, *then* the count.
   The reader loads the count, *then* the targets. **A pass is never visible
   before the pointer that names it.**
2. **BOTH EYES OR NEITHER.** If either pass pointer is null the pair is skipped
   and the legacy frame-0 pair is used. **Step 3d's rule: dropping one eye is a
   fusion failure and far worse than presenting an older pair** — and `50` and
   `69`-`71` are what happens when the two eyes disagree.
3. **`GE_VR_EYE_INTERP=0` IS AN EXACT IDENTITY.** The legacy pointer is still
   published and still the fallback, so an unset build takes precisely the path
   this file took before `104` existed.

## §4 — THE GATES, AND THE FIRST TWO NEED NO HEADSET

| | |
|---|---|
| **G-104-1** | **`interpUsed` is ~30/s with the knob on.** **Zero means the change is NOT running** and anything felt is imagination. `00`'s instrument warning |
| **G-104-2** | **`reused` -> ~0 AND `submits` stays ~90 AND fps stays 60.** `103`'s naive version got the first and destroyed the other two. **This gate is the whole difference between `103` and `104`** |
| **G-104-3** | Worn: **stick turn is smoother.** That is the half this directly fixes |
| **G-104-4** | Worn: head turn — **may improve, may not.** `103` §3: interpolation lerps the GAME's transforms and does not know the head moved. **Do not judge the change by this** |
| **G-104-5** | **`-Flat` still -113 px +/-5, `-NoXr` untouched, both eyes still distinct.** B1 |
| **G-104-6** | **No `0x139` on exit, five closes.** The lifetime change is smaller than `103`'s but it is still a lifetime change, and B3 is open |

## §5 — WHAT IS STILL TRUE AFTER THIS, HOWEVER WELL IT GOES

**The head pose is still sampled once per game frame.** `publish_render_pose` is
called from the game thread per workload; interpolated passes reuse it. **So
`posecheck`'s `MAX delta` will not go to zero and should not.**

**The next step after this, if it holds:** build `VrEyeParams` per pass with a
freshly located pose rather than once per workload. **`104` is what makes that
possible — there is now a per-pass render that survives to be presented. Before
it, there was nowhere to put a fresher pose.**

**And it remains true that none of this touches the quantum, the aim
integrators, or any slice in `86`.** `99` §4's route B stays where it was: last
resort.
