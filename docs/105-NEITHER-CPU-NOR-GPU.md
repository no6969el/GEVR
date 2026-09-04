# 105 — TWO ATTEMPTS, ONE CAUSE, AND IT IS NEITHER THE CPU NOR THE GPU

**2026-08-24. Closes `103` and `104` as built. Read `103` for why the frames
exist at all. Nothing in here is built — `48` rule 1.**

---

## §1 — THE THREE RUNS, SIDE BY SIDE

| | knob OFF | `103` naive publish | `104` indexed publish |
|---|---|---|---|
| fps | **60.0** | 16.3 | 25.7 |
| `submits` /s | **90** | 13 | 13 |
| `reused` /s | 30 | **0** | **0** |
| **eye passes RENDERED /s** | **90** | — | **39** |
| `xrWaitFrame` | **9.15 ms** | 75.40 | 73.64 |
| `interpUsed` /s | n/a | n/a | **13 (running)** |

**`104` passed G-104-1 and failed G-104-2.** Indexing the passes properly and
inheriting the existing `interpolatedCondition` bought **~60% more throughput
than `103`'s naive version and did not fix the stall.**

## §2 — THE MISDIAGNOSIS, NAMED

**`103` §4 and `104` §2 both called this a LIFETIME hazard — the present thread
reading a target the workload queue was still writing, i.e. a correctness
race.** `104` fixed that properly, by the book, using the mechanism that already
existed. **The stall survived.**

> **It was never a correctness problem. It is a SCHEDULING one.** Two documents
> aimed at the wrong layer, and the second one aimed there because the first one
> said so. **Rule 10, and rule 3: the numbers below were available before either
> was written.**

## §3 — IT IS NOT THE GPU, AND THE LOG PROVES IT WITHOUT A NEW INSTRUMENT

**The discriminator is `render passes: eye0=` — the count of eye passes RENDERED
per second, which has been printing since `50`:**

```
knob off :  60.0 fps | render passes: eye0=90
EyeInterp:  25.7 fps | render passes: eye0=39
```

> **THE GPU IS DOING LESS THAN HALF THE WORK AND TAKING MORE THAN TWICE AS
> LONG.** A saturated GPU stays pinned — the work count would hold and the frame
> rate would fall. **Work went DOWN while time went UP. That is something
> WAITING, not something SATURATED.**

**And our own XR path is idle while it happens:**

```
stage ms: waitFrame 73.64 | locate 0.20 | waitForGpu 0.00 | record 0.02 | execute 0.03 | endFrame 0.24
```

**`waitForGpu` is exactly 0.00** — we never wait on our own submission. About
half a millisecond of real work, then **73 ms blocked in `xrWaitFrame`**, which
is the compositor pacing an application that cannot keep up. **`72` exonerated
this loop for being slow and this does not re-accuse it.**

**It is not the CPU either.** The machine is a 9950X3D, the process is confirmed
on the V-cache CCD, and `record` is 0.02 ms. **There is no CPU shortage to
solve, and the affinity hypothesis is closed by the owner rather than by
argument.**

## §4 — WHAT IT ACTUALLY IS: THE PIPELINE LOST ITS SLACK

**With `frame == 0`, the present thread reads a target the workload queue
finished A WHOLE GAME FRAME AGO.** That gap is not incidental — **it is what
lets the two threads overlap at all.** The present worker samples a surface
nothing is touching while the workload races ahead.

**With per-pass publishing, present iteration `i` reads pass `i` the workload has
only just finished.** The GPU must complete that write before the eye render can
sample it — **every present, both eyes.** Pipeline depth collapses from about one
frame to zero and the threads run in lockstep.

**The numbers agree:** `renders=26` against `submits=13` — the workload side
produces roughly twice what present consumes, which is a queue that has stopped
being a queue.

## §5 — AND THE THING WORTH MORE THAN EITHER FAILURE

```
60.0 fps | render passes: eye0=90     <- on the GOOD build, with the knob OFF
```

**Ninety eye passes a second were being rendered while sixty were published, on
a build that predates all of this work, at a stable 60 fps.** `103`'s central
claim, measured directly by an independent counter that has been printing since
`50`. **Thirty finished stereo pairs a second, discarded, and the frame rate was
fine while it happened.**

> **The capacity is real and already paid for. We simply cannot consume it in a
> way that removes the pipeline's slack.**

## §6 — TWO CANDIDATE FIXES, HONESTLY COSTED. DISCUSS BEFORE BUILDING.

### A — DOUBLE BUFFER THE PASS SET (one game frame of slack, the safe one)

Workload fills set B while present drains set A; flip at workload end.
**Restores exactly the gap `frame == 0` had today, and presents ~90 distinct
images instead of 60.**

**THE COST IS NOT THE POINTERS, IT IS THE TARGETS.** `eyeColorTargets` is
indexed `(frame * 2) + eye` and **reused by the next workload**, so double
buffering means **twice as many eye render targets allocated**. At VR resolution
that is a real VRAM figure and **it must be measured before it is built** — this
project has one unexplained result in exactly that area (`49` O22, where 8x
fewer pixels ran 4x slower).

### B — LAG BY ONE PASS, NOT ONE WORKLOAD (cheap, and unproven)

Within a single workload the passes are **already distinct targets** — index
`(frame * 2) + eye` differs per pass. **Only the next workload overwrites them.**
So consuming pass `i` while the workload renders pass `i + 1` gives one pass of
slack — about 11 ms — **with no extra allocation at all.**

**The unsolved end of it:** the last pass of a workload has no successor to hide
behind, and the first has no predecessor. **Whether that degenerates to today's
behaviour on those two passes or needs a one-target carry is the read this
option owes.**

**B is the one to cost first**, because it is free if it works, and A is the
fallback that is known to work and known to cost memory.

## §7 — WHAT DOES NOT CHANGE EITHER WAY

**The head pose is still sampled once per game frame.** Both options give ~90
distinct images of WORLD motion. **`posecheck`'s `MAX delta` will not go to zero
and head turn may not improve** — `103` §3, unchanged and still the thing to be
careful about promising. **Stick turn is the half this fixes.**

**`GE_VR_EYE_INTERP` stays in the tree at default 0**, which is an exact
identity. **Do not delete it: it is now the cheapest way to reproduce a
measurable pipeline stall on demand**, and `56`'s whole method is altering a
thing on purpose to see what changes.

---

# §8 — OPTION A, AS BUILT. 2026-08-24. NOT RUN.

**Chosen over B at the owner's direction. Four files, no new patch name, no
`CMakeLists` change. Backups `.bak104` / `.bak105`.**

| File | Change |
|---|---|
| `rt64_workload_queue.cpp` | `eyeTargetCount` is now **two sets**; the pass index is offset by the write parity; the set is published **after the frame loop**, not during it |
| `rt64_workload_queue.h` | `geVrEyeSetParity` — workload-thread-only, never seen by the present thread |
| `rt64_shared_queue_resources.h` | `vrEyePassTarget[set][eye][pass]` and `vrEyePassSet` |
| `rt64_present_queue.cpp` | Acquires the set, then the count, then the targets |

**THE ORDERING IS THE WHOLE CORRECTNESS ARGUMENT, in both directions:**
the writer stores **count, then set index**, both release; the reader acquires
**set index, then count**, then the targets. **A set index can therefore never be
paired with the previous set's count.**

**And the flip happens once, after every pass in the set is recorded.** That is
the entire difference from `104`: **`104` handed over a set that was still being
written; this hands over one that is finished.**

## THE GATES — the first three still need no headset

| | |
|---|---|
| **G-105-1** | **fps stays 60 and `submits` stays ~90.** `103` got 16, `104` got 25.7. **If this is not ~60 the option is wrong, not mistuned** |
| **G-105-2** | **`reused` -> ~0 and `interpUsed` ~30/s.** Both already print |
| **G-105-3** | **`render passes: eye0=` stays ~90.** It fell to 39 under `104` — **that number falling again is the stall signature and it is the fastest way to recognise it** |
| **G-105-4** | **VRAM.** Twice the eye targets now exist. Watch for an allocation failure or a paging cliff, and treat `49` O22 as unexplained territory |
| **G-105-5** | Worn: **stick turn smoother.** Head turn may not change — §7 |
| **G-105-6** | **`-Flat` still -113 px +/-5, `-NoXr` untouched, `distinctTargets` still equals the pass count.** **The two sets must not collide with each other**; a collision here is `69`-`71` again |
| **G-105-7** | **No `0x139` on exit, five closes.** B3 is open and this is a lifetime change |

**`GE_VR_EYE_INTERP=0` remains an exact identity — the legacy frame-0 pointer is
still published and still the fallback. The second target set is allocated
either way, so G-105-4 applies to BOTH arms.**
