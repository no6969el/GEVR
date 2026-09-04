# 103 — THE INTERPOLATED EYE FRAMES ALREADY EXIST. WE THROW THEM AWAY.

**2026-08-24. The O22/R2 read `99` §3 asked for, done at source with no headset
and no launch. Read `99` first for why this question decides everything.**

---

## §1 — THE ONE LINE

**`lib/rt64/src/hle/rt64_workload_queue.cpp:1352`:**

```cpp
// Step 3e, extended by docs\50: publish BOTH eyes for the
// present thread. Only the first pass of a workload, so a
// pointer changes once per game frame rather than per
// interpolated pass.
if (vrStereo && (frame == 0) && (eyeTarget != nullptr)) {
    ext.sharedResources->vrEyeZeroTarget.store(eyeTarget, ...);
    ext.sharedResources->vrEyeOneTarget.store(eyeTarget, ...);
}
```

> ## **`frame == 0`.**
>
> **RT64 renders the eyes for EVERY interpolated pass. We publish only the
> first one. The rest are rendered, completed, and discarded.**

**`:1249`** — `for (uint32_t frame = 0; frame < displayFrames; frame++)`, and the
eye loop sits **inside** it (`:1313`), with a per-frame target
`eyeColorTargets[(frame * 2) + eye]` (`:1323-1325`). **The work is being done.
Two of every three results are thrown on the floor.**

**That is `posecheck`'s `submits=90 renders=60 reused=30` explained exactly.
Not a GPU limit. Not the sim. A publish guard.**

## §2 — SO O22 IS NOT THE GATE, AND `99` §3's ORDER IS WRONG

**`99` said Route D lives or dies on what a full-resolution eye re-render costs,
and put that read first because `49`'s O22 made every cost estimate
untrustworthy.**

**The question is moot. THE RE-RENDER IS ALREADY HAPPENING AND ALREADY PAID
FOR.** Whatever O22 turns out to be, it is not standing between us and 90 Hz
eye images — the machine is producing them right now, at whatever
`rr_manual_value` is set to, and has been all along. **`99` §5's order is
corrected here.** Rule 10.

**O22 remains open and remains worth understanding** — 8x fewer pixels running
4x slower is still an unexplained result about *something*. It is no longer a
blocker.

## §3 — WHAT PUBLISHING THEM WOULD AND WOULD NOT FIX

**Be precise, because this is the point where a session gets excited and skips
the measurement — `48` rule 3.**

| | Today | With interpolated eyes published |
|---|---|---|
| **World motion** (stick turn, animation, everything the game simulates) | 60 real + 30 duplicates | **~90 distinct images.** The duplicate-frame judder goes |
| **HEAD pose** | Sampled at 60, baked into `VrEyeParams` on the game thread once per workload | **STILL 60.** Interpolation lerps the GAME's transforms; it does not know the head moved |

> **So this fixes the DUPLICATE FRAME and does not by itself fix the HEAD RATE.**
> **`99` §2's distinction survives intact and is the reason to state this
> carefully:** the complaint was head turn, not stick turn.

**But it changes the head problem from "impossible" to "plumbing".** Once a
per-interpolated-frame render is a thing we publish, **there is somewhere to put
a freshly located head pose** — build `VrEyeParams` per pass instead of per
workload. **Today there is nowhere to put it, because the pass is discarded.**

**And it may fix more of the FELT problem than the table suggests.** The wearer's
report was doubling on edges during head turns. **A head turn moves every edge
in the world across the retina, and 30 duplicated frames a second is exactly what
produces a doubled edge.** How much of that is the duplicate and how much is the
60 Hz pose is **not decidable from source** — and it does not have to be, because
publishing costs one guard.

## §4 — WHAT THIS COSTS, AND THE THREE THINGS THAT WILL BITE

**The guard is one line. Nothing else about it is one line.**

1. **LIFETIME.** `eyeColorTargets` is indexed by `frame`, and the present thread
   holds the published pointer across a frame boundary. **The
   `interpolatedMutex` / `interpolatedCondition` handshake at `:264-279` and
   `:1270-1280` exists precisely because the workload queue must not reuse a
   target the present queue is still reading.** The eye targets are **outside**
   that handshake today, and they are safe only because `frame == 0` makes the
   pointer change once per game frame. **Remove the guard and that argument
   disappears with it.** This is `29`'s shape — know who destroys what you build,
   and when — and it is the single most likely way to reproduce a `0x139`.
2. **WHICH ONE DOES THE PRESENT THREAD WANT?** Publishing a pointer per pass is
   not enough; the XR side copies whenever `xrWaitFrame` releases it, which is
   not synchronised to passes. **A ring with a sequence number, and the present
   thread taking the newest COMPLETE one, is the shape.** Naively storing the
   latest pointer races.
3. **B1 IS RIGHT THERE.** `:1319-1325` gives every eye and every pass its own
   target and modifier **specifically so the `RenderFramebufferKey`s cannot
   collide** — `50`'s fix and `69`-`71`'s root cause. **Any change to that
   indexing risks reproducing one image in both eyes, and it took weeks to find
   the first time.** G-99-4 is not a formality.

## §5 — THE GATES, AND ONE IS ALREADY IN THE TREE

| | |
|---|---|
| **G-103-1** | **`posecheck` `renders` rises toward `submits` and `reused` falls toward 0.** Already printing, already reading 90/60/30. **This is a gate we can read on the FIRST launch without asking the wearer anything** |
| **G-103-2** | **Worn: the doubling on head turns is reduced or gone.** The only gate that decides — and per §3 it may only be partly answered |
| **G-103-3** | **Stick turn is smooth**, because that is the half this directly fixes. **If stick turn does not improve, the change is not doing what this document says** |
| **G-103-4** | **`-Flat` still measures -113 px +/-5, and `-NoXr` is untouched.** B1 |
| **G-103-5** | **No new `0x139` on exit**, run five times. §4 item 1 is a lifetime change and B3 is already an open bugcheck |

## §6 — THE NEXT SESSION'S FIRST MOVE, REPLACING `99` §5

> **1. Read the `interpolatedMutex` handshake (`rt64_workload_queue.cpp:264-279`,
> `:1270-1280`) and decide how the eye targets join it.** That is the whole
> risk. No headset.
>
> **2. Then publish per pass behind a knob — `GE_VR_EYE_INTERP=0` an exact
> identity — and read `posecheck` before anyone puts the headset on.**
>
> **3. Only then wear it.**

**This is a much smaller change than `99` §4's timebase work and it does not
touch the quantum, the aim integrators, or anything in `86`.** Route B stays
where `99` left it: last resort.

**And it is not a guess. The frames exist. There is a counter in this tree that
has been printing their absence for two days.**
