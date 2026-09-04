# 106 — THREE ATTEMPTS, THREE STALLS. STOP. AND A REGRESSION THAT IS A FINDING.

**2026-08-24. Closes the `103`-`105` line as UNSOLVED. Read `105` §3 for the
evidence that survives; everything in `105` §4 and §6-A is now doubtful.**

---

## §1 — THE FOUR RUNS

| | knob OFF | `103` naive | `104` indexed | **`105` double-buffered** |
|---|---|---|---|---|
| fps | **60.0** | 16.3 | 25.7 | **16.3 - 18.8** |
| `submits` /s | **90** | 13 | 13 | **13** |
| eye passes rendered /s | **90** | — | 39 | **31 - 34** |
| `xrWaitFrame` | **9.15 ms** | 75.40 | 73.64 | **75.35** |
| `reused` /s | 30 | 0 | 0 | **0** |
| `interpUsed` /s | n/a | n/a | 13 | **11 - 12** |

**Option A is not better than `104`. It is slightly WORSE, and level with
`103`'s naive version.**

## §2 — WHAT THAT ELIMINATES, WHICH IS THE POINT OF HAVING BUILT IT

**Double buffering removes the write-while-read dependency BY CONSTRUCTION.**
The present thread reads a set the workload queue finished an entire game frame
ago and is not touching. **If `105` §4's "the pipeline lost its slack" were the
cause, this would have fixed it. It did not move.**

> **So the diagnosis in `105` §4 is WRONG, and so was `103` §4 and `104` §2
> before it. Three documents, three explanations, all aimed at the handover
> between the two threads. The handover is not the problem.**

**Rule 10, and it is worth being blunt about the pattern:** each explanation was
built on the previous one's framing rather than re-derived from the numbers.
`103` said "lifetime hazard", `104` accepted that and fixed it properly, `105`
accepted the remainder and fixed the scheduling. **Nobody went back to the
measurement and asked what all three had in common.**

**What all three have in common, and it is the only thing left:** the present
thread samples a **different eye target from one present to the next**. When it
samples the same target every present, the build runs at 60. **That, not when
the target was written, is the variable that has never been changed
independently** — `56`'s method, unapplied here for three attempts.

## §3 — THE REGRESSION IS A FINDING, AND IT MAY MATTER MORE THAN THE STALL

**The wearer, on the `105` build:** *"characters moving out of place — earlier in
the project the crates and other objects were doing it, but in this one it seems
that is off on the characters again."*

> **We are now SHOWING the interpolated frames. He is describing what they look
> like.**

**`92` candidate 2 is PARTIAL INTERPOLATION — some things interpolate, some do
not — and it was never eliminated.** `23`, *"explosion effects stick to the view
when turning"*, has been open since Phase 1 as its known worked instance. **The
crates he remembers are the same family.**

**Until now every interpolated eye pass was rendered and discarded, so nobody
had ever LOOKED at one. The first time we present them, characters are in the
wrong place.**

**THE CONSEQUENCE FOR THE WHOLE ROUTE:** even if the stall were solved tomorrow,
**presenting interpolated frames would ship visibly mis-placed characters.**
`99` §3's Route D assumed the interpolated frames were correct and only
unpublished. **They are unpublished AND wrong.** That assumption is corrected
here.

**And it re-ranks `23` a second time.** `92` promoted it; this makes it a
prerequisite rather than a nicety.

## §4 — WHAT IS STILL SOLID AFTER ALL THIS

1. **`103`'s core measurement.** `render passes: eye0=90` at a stable 60 fps
   with the knob OFF. **Ninety eye passes rendered per second, sixty published,
   on a build that predates this work.** Independent counter, unaffected by
   every failure since.
2. **`105` §3's elimination.** Not the GPU — work went down while time went up.
   Not the CPU — `record 0.02 ms`, `waitForGpu 0.00`, 9950X3D with the process
   confirmed on the V-cache die.
3. **The duplicate submissions really do disappear.** `reused` 30 -> 0 in all
   three attempts.
4. **`GE_VR_EYE_INTERP` is the cheapest reproducible pipeline stall in the
   project.** Keep it. `56`.

## §5 — THE VRAM REGRESSION I INTRODUCED, AND FIXED

**As first written, `105` allocated the second eye target set on EVERY build,
knob or not** — a VRAM cost on the default path to pay for an experiment that
does not work. **That is exactly what `48` rule 5 exists to stop, and it was
mine.** The allocation and the pass indexing are now both gated on
`GE_VR_EYE_INTERP`, so **an unset build is byte-identical to the one before
`103`.**

## §6 — WHAT THE NEXT SESSION SHOULD DO, AND IT IS NOT A FOURTH ATTEMPT

> **STOP BUILDING. The next move is one read and one experiment, and neither
> needs the headset.**

| # | Move | Why |
|---|---|---|
| **1** | **Change ONLY the variable never changed alone: make the present thread sample a DIFFERENT target every present WITHOUT publishing more passes** — e.g. alternate between two copies of the SAME finished frame-0 pair. **If that stalls, the cost is in changing the sampled texture, and nothing about passes or lifetimes was ever relevant.** If it does not stall, the pass path is implicated and lifetimes are back on the table | `56`'s method. Three attempts changed two things at once |
| **2** | **Read what the VIRenderer does when `params.texture` changes** — descriptor set rebuild, layout transition, or a barrier that forces a queue sync. `prepareEyeFromTarget`'s resolve and downsample are both no-ops here (MSAA off, `ds_option 1`), so **the cost is downstream of it and has not been read** | The only unread code in the path |
| **3** | **Then, separately, `23`** — partial interpolation. **§3 makes it a prerequisite for Route D, not an optional cleanup** | Characters in the wrong place is a ship blocker whatever the frame rate |

**And the honest option that is now on the table: Route D may not be worth it.**
`99` §2 said the target is "make the VIEW update at 90". **If interpolated frames
are visually wrong, the route that reaches 90 by presenting them inherits that
wrongness** — and `99` §4's timebase work, which `92` and `99` both called a
last resort, starts looking less like a last resort and more like the only route
that produces frames that are actually correct. **That is a judgement for the
owner, not a conclusion for this document.**

---

# §7 — §3 IS RETRACTED. THE INTERPOLATED FRAMES ARE FINE.

**`.\vr.ps1 -NoXr`, run by the owner: *"Nope it all looks good here, runs great
too."***

**`-NoXr` presents the SAME interpolated frames on the monitor at 90** —
`rr_manual_value: 90`, the interpolator running exactly as it does under VR.
**Characters are correct there and the frame rate is fine.**

> ## **SO INTERPOLATED FRAMES ARE NOT VISUALLY WRONG, AND §3 WAS WRONG TO SAY SO.**

**§3 reasoned that because the misplacement appeared the first time we presented
interpolated passes, presenting interpolated passes was the cause.** That is the
same mistake `57` is famous for here — **an appearance promoted to a finding** —
and it was made worse by being built on top of it: §3 went on to declare `23` a
prerequisite for Route D and to suggest the timebase work might be the only
route producing correct frames. **All of that rested on an untested assumption
and it is withdrawn.** Rule 10.

**What actually killed it:** the owner said the regression started *with our
changes*, not with the build. One command, no headset, no code. **The cheapest
test in the sequence was the one nobody ran.**

## §7.1 — WHAT IT LEAVES

| | |
|---|---|
| **Route D is BACK.** | Presenting interpolated frames is a sound goal. `99` §3 stands as written; `106` §6's closing paragraph is withdrawn |
| **`23` returns to where `92` had it** | Promoted and open, **not** a prerequisite |
| **The character misplacement is OURS** | It does not occur on the interpolated path itself. It occurs on **our VR eye path**, under the changes made in `103`-`105` |
| **The CHR tagging candidate is dead** | `chrpropRender` skips pos/rot/scale and interpolates verts only — that treatment is evidently correct, because `-NoXr` displays those very frames and characters are right |

## §7.2 — THE REMAINING SUSPECT, AND THE READ THAT ISOLATES IT

**`104` and `105` changed the eye target MODIFIER** — `0x1000 + eyeTargetIndex`
— and `105` made it **alternate between two sets on consecutive workloads.**
`103` did not touch it.

**So the question is exactly one launch wide:**

> **Run VR with the knob OFF and look at a guard walk.**
> ```powershell
> .\vr.ps1 -UnitsPerMetre 50 -SeamNoRot -HandPosZ 1
> ```
> **Characters correct -> the regression is ours and lives in the modifier
> change, which only fires with `GE_VR_EYE_INTERP=1`.**
> **Characters wrong with the knob OFF -> it is in the VR eye path generally and
> predates `103`**, and the `-Flat`/`-NoXr` difference becomes the next read.

**This also re-verifies the default build**, which is the thing that must be
clean regardless of how the experiment ends.
