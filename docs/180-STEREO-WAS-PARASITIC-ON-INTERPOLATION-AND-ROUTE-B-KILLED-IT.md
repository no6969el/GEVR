# 180 — [RETRACTED] STEREO HUNG OFF THE INTERPOLATION MACHINERY, AND ROUTE B REMOVED IT

> # ►►►► RETRACTED THE SAME DAY IT WAS WRITTEN, 2026-08-26. ◄◄◄◄
>
> ## **§2's MECHANISM IS FALSE. `147` LINE 46 REFUTES IT, AND `147` WAS ALREADY READ THIS SESSION:**
>
> ```
> [gevr] 90.0 fps | render passes: eye0=90 eye1=90 distinctTargets=90 | interpUsed=0
> ```
>
> **`-ViRate 90`, `interpUsed=0`, AND BOTH EYES RENDERING.** Everything below
> claiming that Route B killed stereo by removing interpolation is WRONG.
>
> **THE OWNER CAUGHT IT FROM MEMORY** — *"I was able to run virate 90 in VR and
> the characters DID NOT stutter"* — against a document that asserted the
> opposite in bold.
>
> ## WHAT WAS ACTUALLY WRONG WITH IT
>
> **1. TWO QUANTITIES WERE FUSED BECAUSE THEY SHARE A PREFIX.** `interpUsed` is
> a count of frames interpolated AND USED. `interpolationTargetKey` is populated
> from `interpolationFb->interpolationEnabled`. **`interpUsed=0` does NOT imply
> an empty key**, and nothing was ever read to check.
>
> **2. THE SAMPLE WAS THE FILES LYING NEAREST TO HAND.** Four archived `.log`
> files, one clean correlation, and NO SEARCH FOR A RUN THAT WOULD BREAK IT.
> Unanimity across a biased sample is worth nothing.
>
> **3. IT WAS WRITTEN IN THE TYPOGRAPHY OF A FINDING.** `►►►►` and bold caps on
> a hypothesis four minutes old, indistinguishable from `171` §2, which was
> derived from source. **The next session would have built on it.**
>
> ## WHAT SURVIVES
>
> **§1's TIMELINE IS DATA AND STANDS** — stereo was alive at T6 (19:32) and
> dead by T10 (21:53), and dead in every run since. **The window is `149`,
> `150`, `151` — and `151` is titled "the default tried and reverted".**
>
> **§4's THREE INSTRUMENTS ARE BUILT AND ARE THE RIGHT ANSWER**, because they
> replace inference with a reading: `VRGATE/s` names the false term outright.
>
> **§6 STANDS AND IS UNAFFECTED** — the aim findings were still made without
> stereo, whatever the cause turns out to be.
>
> **AND SEE `182`**, written because this is the FOURTH time this project has
> promoted an unverified claim to an established one (`160`, `163`, `171` §3).


**2026-08-26. A read, three instruments, and the cause of `179`'s dead eye.**

> ## **`-ViRate 90` AND STEREO ARE MUTUALLY EXCLUSIVE IN THE CURRENT TREE.**
>
> **NOT A SETTING. NOT MSAA. NOT `175`.** The second eye's render target is
> BUILT FROM the interpolation target, so when Route B made interpolation
> unnecessary it took the eye targets with it. **Route B succeeded and broke
> stereo by succeeding.**

---

## §1 — THE EVIDENCE, AND IT IS ONE COLUMN

| run | when | `interpUsed` | `render passes` |
|---|---|---|---|
| T6 posepush | 08-24 **19:32** | **90** (27 samples) | **`eye0=91 eye1=91`** |
| T10 prevpose | 08-24 **21:53** | **0** (all 40) | `eye0=91 eye1=0` |
| T13 wfnf | 08-24 22:08 | 0 | `eye1=0` |
| 08-26 | today | **0** (all 2,603) | `eye1=0` (1,712 samples) |

**INTERPOLATION AND STEREO GO DARK IN THE SAME RUN AND NEVER RECOVER.**
`131` §1 states the mechanism as a FEATURE: *"The sim itself ticks at 90. Every
frame is real; nothing is interpolated."*

## §2 — [FALSE — SEE THE RETRACTION ABOVE] THE COUPLING, IN FOUR LINES

`rt64_workload_queue.cpp`:

```
1051  if (!interpolationCandidate || !interpolationTargetKey.isEmpty()) continue;
1053  if (interpolationFb->interpolationEnabled) { interpolationTargetKey = ...; }
1246  vrStereo = enabled && inLevel && !interpolationTargetKey.isEmpty() && !usingMSAA;
1361  eyeColorTargets[i] = make_unique<RenderTarget>(interpolationTargetKey.address, ...);
```

> **`1361` IS THE REAL DEPENDENCY AND `1246` IS ONLY ITS GUARD.** The eye targets
> are ALLOCATED AT THE INTERPOLATION TARGET'S ADDRESS. **Stereo was never
> merely gated on interpolation; it was built out of it.** `1246` is honest -
> without a key there is no address to build the second eye at.

**SO THE GUARD IS CORRECT AND THE ARCHITECTURE IS WRONG.** Removing the term
would produce a second eye pointed at address 0.

## §3 — WHY NOBODY SAW IT FOR THREE SESSIONS

**`147` MADE `-ViRate 90` STANDING PRACTICE** the moment RB-07 passed worn -
*"so much better... totally playable and enjoyable."* **That judgement was made
on the flat-mode gates** (`fps`, `dupSrc`, `LATE`), all of which improved, and
none of which can see a missing eye.

**AND EVERY DOWNSTREAM INSTRUMENT READS THE SAME UNDER BOTH CAUSES:**
`eye1=0`, `hostSees=0/0`, `dupSrc=n/a`, `EYETGT builtAt=0 current=0` - identical
whether stereo is off because no level is loaded or because the key is empty.
**`STEREO IS OFF` printed in all of them, INCLUDING the runs where stereo
worked**, because it latched once and the front end trips it legitimately.

## §4 — THE THREE INSTRUMENTS, BUILT THIS SESSION

1. **`VRGATE/s`** - `shared_queue_resources.h` gains five counters, incremented
   term by term at `:1246`. **Any term reading 0 while `workloads > 0` IS the
   cause.** No inference.
2. **The banner repeats** - every 30 starved seconds, carrying the count, so
   "menus" and "five minutes into a level" are distinguishable. **The MSAA text
   is REMOVED**: `rt64_render_context.cpp:195` has forced antialiasing to None
   on every `GE_VR_XR` launch since before the failure, and `MSAA forced OFF for
   VR` has NEVER printed in any log held. **It sent this investigation down a
   dead end for two exchanges.**
3. **`vr.ps1` reports the verdict at exit** - waits on the process, then says in
   red whether stereo ever engaged. **The numbers always existed and were always
   right. Nobody was ever told.**

## §5 — [MOOT — THE PREMISE IS RETRACTED] THE FOUR WAYS OUT

| | approach | cost | keeps 90 Hz |
|---|---|---|---|
| **A** | **Give the eye targets their own key** - derive from the presented colour image directly rather than the interpolation candidate | **SLICE. The principled fix** | **YES** |
| **B** | Keep `interpolationEnabled` true at 90 so the key is populated even when no frame is interpolated | small, but resurrects machinery Route B exists to retire | YES |
| **C** | Run stereo at 60 (`-ViRate` unset) | zero | **NO - gives back RB-07** |
| **D** | Do nothing, test at 60, keep 90 for flat | zero | partial |

**C IS THE IMMEDIATE UNBLOCK AND IT COSTS THE THING THE OWNER LIKED MOST.**
Drop `-ViRate 90` from the standing command and stereo should return on the
existing binary - **and that is also the falsification test for this whole
document.**

> ### **RUN THAT FIRST. ONE LAUNCH, NO REBUILD, AND IT EITHER CONFIRMS §2 OR KILLS IT.**

## §6 — AND IT RE-DATES EVERY AIM FINDING

`179` §3 said today's aim observations were made without stereo. **It is worse
than that: so were `T10`'s and `T13`'s.** Every aim conclusion recorded since
08-24 21:00 - `154`-`159`'s grip and axis tuning included, if any of it was
re-checked in that window - was measured through a monocular image.

**`166` §4's 17 degrees, the ~6 px up / ~1 px right sketch, `-HandAxisX -1`,
`-HandAxisZ -1`, `-GunOffY 8`, `-GunOffZ -2`: CHECK WHICH OF THESE WERE SET OR
CONFIRMED AFTER 08-24 21:00 BEFORE TRUSTING ANY OF THEM.**
