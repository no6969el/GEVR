# 111 — IT WORKS. AND `reused` NEVER MEASURED WHAT WE THOUGHT.

**2026-08-24. Built, compiled, run, four logs kept. `107` + `109` + `110` in one
build. THE STALL IS FIXED — and the instrument that judged all four previous
attempts was reading its own failure as a success.**

---

## §1 — THE RESULT

| | knob OFF (run 1) | **`-EyeInterp` (run 2)** | `103` | `104` | `105` |
|---|---|---|---|---|---|
| **fps** | 60.0 | **60.0** | 16.3 | 25.7 | 16.3 |
| **submits/s** | 90 | **90** | 13 | 13 | 13 |
| **eye passes/s** | 90 | **90** | — | 39 | 31-34 |
| **`xrWaitFrame`** | 9.11 ms | **9.27 ms** | 75.40 | 73.64 | 75.35 |
| **`interpUsed`** | 0 | **90** | n/a | 13 | 11-12 |

> ## **G-107-1 PASS. G-107-2 PASS ON FPS AND SUBMITS. THE PIPELINE DOES NOT COLLAPSE, AND EVERY INTERPOLATED EYE PASS IS BEING PRESENTED.**

**`105` WAS RIGHT AND ONLY ITS ARITHMETIC WAS WRONG.** The double buffer was the
correct fix; its set stride was derived from `displayFrames`, which alternates
1/2 at 60 into 90, so the two sets overlapped and the dependency it was built to
remove was never removed — `107` §2. **With a fixed stride it works.**

**AND `106` §2 IS NOW POSITIVELY FALSIFIED**, not merely unsupported: *"the
handover between the threads is not the problem"* was wrong. **It was exactly
the problem.**

**G-107-4 PASS:** run 1 is 60 fps / 90 submits / `interpUsed=0` / `sampleAlt=0`,
identical to before. The identity claim holds.

---

## §2 — AND THE FINDING THAT MATTERS MORE THAN THE FIX

**`reused` did not go to 0. It reads 30, exactly as it did with the knob off.**
That looks like a failure. **It is not — the instrument cannot do anything else,
and it never could.**

```cpp
renders = g_renderCount;                                    /* ge_vr_xr.cpp:2416 */
reused  = (submits > newRenders) ? (submits - newRenders) : 0;      /* :2160 */
```

**`g_renderCount` is incremented in `publish_render_pose`, which is called from
`rt64_render_context.cpp:1609` — ON THE GAME THREAD, ONCE PER GAME FRAME.**

> ## **SO `renders` IS THE GAME'S FRAME RATE, NOT A COUNT OF RENDERED IMAGES, AND `reused` IS JUST `submits − game frames`.**

**At a 60 sim submitting at 90 it is pinned to 30 BY ARITHMETIC, no matter what
the images are doing.** It cannot reach zero unless submits falls to 60 or below.

### §2.1 — WHICH MEANS ALL THREE PREVIOUS "SUCCESSES" WERE THE STALL ITSELF

**`103`, `104` and `105` each reported `reused` 30 -> 0 and read it as *"the
mechanism is real."*** `106` §4 lists it as one of four things that are "still
solid."

**IT WAS THE CLAMP.** Their submits collapsed to **13**, which is below
`renders = 60`, so `(submits > newRenders) ? ... : 0` returned **0**.

> ## **THEY WERE READING THEIR OWN STALL AS THE SUCCESS SIGNAL. THREE TIMES, ACROSS THREE DOCUMENTS.**

**`106` §4 item 3 is RETRACTED.** So is every "the duplicate submissions
disappear" claim in `103`, `104` and `105`.

### §2.2 — AND `93`'s G93-2 WAS NEVER BUILT

**`93` §5 asked for:** *"count submissions reusing an unchanged image. PREDICT
~1 in 3."* **That counter does not exist.** What exists compares submits against
game frames and produces 30 — **which matches the prediction by coincidence of
arithmetic and has been quoted as confirming it ever since.**

**This is `49`'s "TWO INSTRUMENTS IN THIS TREE CANNOT FAIL" for the third
time**, after the upload verdict and the `VIEWPROJ GPU` line. **Rule 4, and
`00`'s standing warning: before trusting an instrument, ask what it would print
on a working build — and then on a build that fails the way you care about.**
**This one prints 30 on both.**

### §2.3 — SO: IS THE DUPLICATE FRAME GONE? WE STILL DO NOT KNOW.

**Honest answer: the stall is fixed and the duplicate-frame question is
UNMEASURED**, because the instrument that was supposed to answer it never did.

**`interpUsed=90` is the best evidence we have** — the present thread took a
distinct interpolated pass target on all ninety presents, where before it took
one in three. **But that is the SAMPLING side, not the submitted side.**

> **OWED: a real duplicate-image counter.** Compare `vrPresentSource[eye]`
> against its previous value at submit time and count matches. **That is G93-2
> as originally specified, and it is a handful of lines.** Until it exists,
> nobody should say the duplicate frame is fixed.

---

## §3 — `109` EARNED ITSELF ON ITS FIRST RUN

**Baseline, steady state:**

```
frame budget: runtime display period 11.11 ms (90.0 Hz) | our frame 10.27 ms (97.4 Hz)
stage ms:     waitFrame 9.11 | locate 0.89 | waitForGpu 0.00 | record 0.01 | execute 0.02 | endFrame 0.24
stage MAX ms: waitFrame 10.70 | record 0.02 | endFrame 1.18 | frame 11.81 | LATE 16/91 (18%)
```

**The mean says 10.27 ms against an 11.11 ms budget — comfortable. The max says
11.81-12.30 ms and LATE 15-16 out of 90.**

> ## **ROUGHLY ONE FRAME IN SIX MISSES THE DISPLAY DEADLINE ON THE BUILD THE WEARER ACTUALLY PLAYS, AND `72`'s MEANS COULD NEVER HAVE SHOWN IT.**

**`73` predicted exactly this and it took fourteen documents to measure.**

**AND IT IS NOT CONSTANT** — earlier samples in the same run read `LATE 0/60
(0%)`, and a load-time sample read `LATE 3/11 (27%)` with `endFrame` max
19.12 ms. **Lateness comes and goes. That is a HITCH pattern, not a throttle**,
and it is the first direct evidence of the shape of the thing.

**The interp build is NOT worse on pacing:** `LATE 14-15/90 (16%)`, marginally
better than baseline.

---

## §4 — O89 ANSWERED: SUPERSAMPLING IS FREE ON THIS RIG

**Run 4, `ds_option 2`, knob off:**

```
60.0 fps | render passes: eye0=90 eye1=90 distinctTargets=90
stage MAX ms: waitFrame 10.34 | record 0.02 | endFrame 0.29 | frame 12.36 | LATE 11/91 (12%)
```

**60 fps, 90 eye passes, and LATE 12% — BETTER than the baseline's 17-18%.**

> ## **`ds_option 2` COSTS NOTHING MEASURABLE. `49`'s O22 DID NOT REPRODUCE.**

**`108` §3 confirmed by feel that it kills the distant shimmer; this measures
that it is free.** Combined, **the antialiasing fault (O90) has a confirmed
diagnosis, a confirmed lever, and a measured zero cost.**

**RECOMMENDATION: `ds_option 2` becomes the default**, and `4` is worth one run
to see whether the curve bends. **`msaa_option` stays `"None"` — `43`.**

---

## §5 — A NUMBER NOT TO OVER-READ

**`posecheck MAX delta`: 0.09-0.12 deg baseline, 0.23-0.48 deg interp,
0.65-0.78 deg at `ds_option 2`.**

**DO NOT read that as a regression.** It is a MAX over whatever the wearer did
during that run, and it scales with how much the head moved. **Three runs with
three different amounts of head movement are not comparable.** To mean anything
it needs the motionless `-TimewarpYaw` test (`98`) or a fixed movement.

**Naming it because a rising number in a log is exactly the kind of thing that
becomes a hypothesis by tomorrow.** Rule 3.

---

## §6 — WHERE THIS LEAVES THE PROJECT

| | |
|---|---|
| **Route D** | **ALIVE AND WORKING.** The stall is gone, every interpolated eye pass is presented, and the timebase work (`99` §4, Route B) is **NOT needed for this** |
| **`106` §2** | **FALSIFIED.** The handover WAS the problem |
| **`106` §4 item 3** | **RETRACTED.** `reused` 30 -> 0 was the clamp, not a fix |
| **O85 / `110`** | **BUILT AND NOT NEEDED.** `-EyeSampleTest` was gated on run 2 stalling. It did not. **Keep it — it is a clean isolating diagnostic and cost nothing** |
| **G93-2** | **OWED, AND NEVER BUILT.** A real duplicate-image counter |
| **O74 / `109`** | **DELIVERED. ~1 frame in 6 is late, intermittently** |
| **O89 / O90** | **ANSWERED. Supersampling is free; make it the default** |
| **THE HEAD-TURN HALF** | **STILL OPEN AND UNADDRESSED.** `104` §2: the head pose is still sampled once per game frame. **What `107` bought is the PREREQUISITE — there is now a published per-pass render to put a fresh pose into. That is the next slice** |

**AND THE WEARER HAS NOT WORN IT.** Every number here is from a log. **The
question that decides whether any of this mattered — does the stick turn feel
smooth now — has not been asked.**
