# 124 — P1: THREE BUILDS, AND THE ANSWER IS A TIMING ONE

**2026-08-24, late. The head-turn half, chased to ground. Every counter in here
was read off a live build; every elimination was worn.**

> **THE OWNER RE-STATED THE TARGET AND IT SHOULD NOT BE LOST AGAIN:**
> *"The judder happens when I turn my HEAD. The stick turn is just
> semi-satisfactory. I tried to make that clear a few times so we wouldn't just
> fall back to finding a fix for the head turn and then settle for the 60
> feeling of the world."*
>
> **`103`-`116` fixed the STICK half. That is the half he cares about least,
> and `104` §2 said so at the time.**

---

## §1 — WHAT WAS BUILT, AND WHAT EACH BUILD MEASURED

| Build | Change | `poseRefresh` | `posePP` | **`poseChg`** | Worn |
|---|---|---|---|---|---|
| `121` | Workload re-reads the pose **per pass** | — | 92 | **0** | "better but still happens" |
| `122` | Same, but **one pose per pass shared by both eyes** | — | 92 | **0** | (fixed a skew bug `121` introduced) |
| `123` | Host **refreshes the pose at 90 Hz** as well | **91** | 91 | **0** | ghost orbits the object on circular head motion |

> ## **BOTH HALVES CONFIRMED RUNNING. `poseChg` STILL ZERO. THAT IS NOT A PLUMBING FAILURE — IT IS THE ANSWER.**

---

## §2 — THE MECHANISM

**The passes of one workload are RENDERED back-to-back in a couple of
milliseconds. They are DISPLAYED 11.11 ms apart.**

The host refreshes the pose every 11.11 ms. **So every pass of a given workload
falls inside a single refresh interval and reads the identical matrix.** The
pose still only changes *between* workloads — which is 60 Hz, exactly where it
started.

**We built a faster pipe and handed it the same water.**

> ### **THE FIX IS NOT "READ THE NEWEST POSE". IT IS "POSE EACH PASS FOR THE MOMENT IT WILL BE SHOWN".**
>
> **Pass `i` needs the pose predicted for
> `predictedDisplayTime + i * displayPeriod`, located AT RENDER TIME.**

**That is `114` §3.2's READ 3 (R3), which was listed as owed and then skipped
when the per-pass plumbing looked sufficient on its own.** `48` rule 1 exists for
this: the reads come before the code, not during.

**R1 already cleared the way:** `xrLocateSpace` takes an arbitrary future
`XrTime` and is not frame-loop-ordered, which is exactly how Perfect Dark
locates its head pose (`117` §1).

### §2.1 — AND THE WEARER DESCRIBED IT BEFORE THE COUNTER DID

*"If I'm looking at someone and I move my head in a circle motion, I can see
their reprojection going around them."*

**A ghost that ORBITS the object as the head orbits is a FIXED-LAG signature** —
a constant positional offset in whatever direction the head is currently moving.
Not smoothing, not damping, not stereo. **`95` again.**

---

## §3 — WHAT TODAY ELIMINATED. ALL OF IT WORN.

| Suspect | Verdict |
|---|---|
| **RT64's frame interpolation** | **EXONERATED — T7.** `rr_option: "Original"`, interpolation genuinely off (`eye0=60`, `interpUsed=0`, `submits=60`), **and the ghost was still there.** `92` candidate 2 and `23` are not the cause of THIS |
| **Stereo / per-eye disparity** | **DEAD, re-confirmed on this build.** Visible with each eye individually. D1 answered a second time, for this specific artifact rather than an old one |
| **In-game input smoothing / camera damping** | **DEAD.** The owner's own hypothesis, and a good one. **The patch makes exactly three host->game calls — `recomp_ge_vr_hand_override`, `recomp_ge_vr_set_world_camera`, `recomp_ge_vr_viewmodel_delta` — and NONE carries head yaw or pitch.** The head pose never reaches the game, so it never touches the stick-look damping or the aim integrators. `ge_vr_head_transform` is a pure quaternion-to-matrix with sign flips: no filter, no damping, all three axes identical |
| **`ge_vr_apply_split` as a yaw threshold** | **DEAD.** It is a POSITION split, not a rotation one |
| **A recomp feature / our own additions** | **DEAD.** The owner ran with the features off and the artifact persisted, just harder to see at native resolution |

---

## §4 — A CORRECTION I OWE, ABOUT VELOCITY vs AMPLITUDE

**The owner observed: fast tight head-shakes show NOTHING; slow wide turns
separate clearly.** I concluded from that that latency was dead, because latency
error is `angular velocity x latency` and the fast case has the higher velocity.

**THAT CONCLUSION WAS TOO FAST AND IS WITHDRAWN.**

**During a slow deliberate turn the eye SMOOTH-PURSUES the object, and any
frame-to-frame position error resolves into a visible double image. During a
fast shake the eye cannot track anything and the same error simply blurs.** It
is a property of how the artifact is LOOKED AT, not of the mechanism.

**The observation is real and valuable; my inference from it was wrong.** Rule 3
- and the author of it broke it again.

---

## §5 — AND THE TIMEBASE GATE PASSED, SO ROUTE B IS STILL LIVE

**G-119-1, measured:**

```
[gevr] timebase: delta=1 [1..1] | clk=1 [1..1] | gdelta x1000=1000 [1000..1000]
```

**Flat, exactly as `118` predicted.** The tick is rigidly 1 and
`g_GlobalTimerDelta` really is just a cast of it. **`118`'s model is CONFIRMED
and Route B remains viable.**

**PARKED BY OWNER DECISION, AND FOR A GOOD REASON HE ARTICULATED:** *"I can't
properly judge if Route B is needed if possibly my only issue is the head turn.
Perhaps the world IS fine if my head was."* **Fix the dominant variable, then
re-judge.** That is the correct order and it also avoids taking on a deep change
to decompiled game timing that may turn out to be unnecessary.

**The timebase line printed ONCE rather than every 90 frames, which is still
unexplained** — `100`'s statics trap in a new costume. The VALUE is what the
gate needed and it is not worth chasing further unless Route B is taken up.

---

## §6 — WHAT R3 NEEDS

1. **A host entry point** that locates the head pose for a **given future
   `XrTime`** and builds the two eye matrices — the work
   `ge_vr_refresh_eye_pose` already does, but parameterised by time instead of
   using "whatever was last published".
2. **The pass index carried into it**, so pass `i` can compute
   `predictedDisplayTime + i * displayPeriod`.
3. **Callable from RT64's workload thread.** R1 says the OpenXR call is legal
   there; the boundary crossing is the actual work.

**GATE: `poseChg` must go strongly non-zero while the head moves.** It has read
0 on three consecutive builds and it is the number that says whether anything
changed at all.

**AND THE REAL GATE IS THE WEARER.** Every counter in `121`-`123` read healthy
while the artifact was untouched.
