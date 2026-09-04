# 114 — THE OVERHAUL PLAN. POWER, THE HEAD POSE, MODS, AND TEXTURES.

**2026-08-24. A PLAN. Nothing in it is built. Rule 1: plan, discuss, then
execute.**

**Written while O94's pick trace was building, so §3's slicing assumes the
`113` §4 contradiction is still open. If the trace resolves it, §3 gets
cheaper, not different.**

---

## §1 — "WE NEED MORE POWER" — WE ALREADY HAVE IT, AND TODAY MEASURED IT

**The owner's instinct is that headroom is the constraint. The numbers say the
opposite, and this is worth settling before any money or architecture is spent
on it.**

| Measurement | Reading | Source |
|---|---|---|
| **GPU wait** | **`waitForGpu 0.00 ms`** — we never once wait on our own GPU submission | `111` |
| **CPU record** | **`record 0.02 ms`, `execute 0.03 ms`** — about half a millisecond of real work per frame | `111` |
| **Where the frame goes** | **~87% blocked in `xrWaitFrame`** | `72`, unchanged in `111` |
| **4x THE PIXEL WORK** | **`ds_option 2` cost NOTHING.** 60 fps, 90 eye passes, and LATE went 17% -> **12%, better** | `111` §4 |
| **`105` §3's elimination** | Not the GPU (work went DOWN while time went UP). Not the CPU (9950X3D, process on the V-cache die) | `105` |

> ## **QUADRUPLING THE PIXEL WORK WAS FREE ON THIS RIG. THAT IS NOT A MACHINE THAT IS OUT OF POWER.**

**The bottleneck is ARCHITECTURAL, not hardware:**

1. **The sim quantum is an integer 1/60 s tick** (`frametiming.c:75`). 60, 30,
   20, 15 — **never 90, on any hardware.** `92`, and no PC moves it.
2. **The VIEW is sampled once per game frame**, not once per present. `99` §2 —
   *"the judder is not the game simulating at 60, it is THE VIEW being sampled
   at 60."*
3. **A duplicate submission one time in three**, still unexplained after
   `103`-`113`.

**None of those three is a throughput problem, and none is improved by a bigger
card.** **Spend nothing on hardware for the judder.**

### §1.1 — WHERE MORE POWER *WOULD* ACTUALLY BUY SOMETHING

**Textures, and only textures — §4.** A 4K texture pack at 5838x4498 per eye is
a **VRAM and streaming-bandwidth** workload, which is a genuinely different
constraint from the one above. **That is the one place the 5090 will be asked
for something it is not currently being asked for.**

---

## §2 — SO WHAT IS THE REAL BUDGET?

**`109` gave us the first honest answer today: mean frame 10.27 ms against an
11.11 ms display period — and MAX 11.81-12.30 ms, LATE 15-16 per 90.**

> **We have roughly 0.8 ms of mean headroom and we are ALREADY MISSING THE
> DEADLINE ONE FRAME IN SIX, INTERMITTENTLY.** `111` §3.

**Read that carefully before adding anything to the frame:** the headroom is not
in GPU capacity, it is in **latency against a hard 11.11 ms cadence**. A change
that adds 2 ms of GPU work costs nothing (`ds_option 2` proved it). A change
that adds a **synchronisation point** costs everything (`103`-`105` proved
that). **Those are the two categories, and they are not intuitive.**

**O97, and it is cheap: the intermittent lateness is unexplained.** Earlier
samples in the same run read `LATE 0/60`. Something periodic is costing us a
deadline six times a second and nobody knows what. **`109` can already see it;
it just needs one run with a longer window.**

---

## §3 — P1: THE PER-PASS HEAD POSE. THE ACTUAL NEXT BUILD.

**This is the head-turn half, untouched by all of `103`-`113`, and it is the
half the wearer complains about** — `95`: *stick turn is clean, head turn is
not.*

**`107` bought the PREREQUISITE and that is all it bought.** `104` §2: before
it, the interpolated passes were rendered and thrown away, so there was nowhere
to put a fresh pose. **Now there is.**

### §3.1 — WHAT IS ACTUALLY WRONG

```cpp
publish_render_pose(headView.orientation);   /* rt64_render_context.cpp:1609 — GAME THREAD, 60/s */
xrLocateViews(...views);                     /* ge_vr_xr.cpp:1258 — PRESENT THREAD, 90/s */
projViews[eye].pose = views[eye].pose;       /* :1533 — the FRESH pose on the STALE image */
```

**The image was rendered from a pose up to a whole game frame old; we submit it
labelled with the current one.** `93`, corrected by `94`.

**AND THE OWNER HAS ALREADY DECIDED THE SHAPE OF THE FIX.** `98`: the timewarp
worked and was **retired on purpose** — *"I want a pure smooth experience, not
an emulator type feel."* **So the answer is not to warp the stale image. It is
to make the image not stale.** That is what per-pass posing is.

### §3.2 — READS OWED BEFORE ANY CODE — `86` §8's discipline

**None of these is an experiment. Do them before, not during.**

| # | Read | Why it changes the design |
|---|---|---|
| **R1** | **Can the pose be located off the XR frame thread, and against what time?** `xrLocateSpace`/`xrLocateViews` need a valid `XrTime`, and the eye passes are rendered on the WORKLOAD thread. **If the answer is no, P1 must pass a pose ACROSS threads instead of sampling one, and the whole slicing changes** | Decides S1 entirely |
| **R2** | **Where does the workload thread get its eye params?** `VrEyeParams` / `ge_vr_head_transform`. **Is there a per-pass injection point, or is the transform baked once per workload?** | Decides whether S1 is a hook or a rewrite |
| **R3** | **What predicted display time does each pass correspond to?** Three passes in one workload target three different display instants ~11.11 ms apart. **Posing them all at one time buys much less than posing each at its own** | Decides S2's value |
| **R4** | **What does Perfect Dark do?** MIT, readable, same engine, at `67ea20c`. **`102` read their aim code and not their frame pacing.** They ship PCVR at 90; if they solved this, the answer is sitting in a readable tree | May collapse S1-S2 entirely |

**R4 first. It is free and it may make the other three moot** — `55` and `86`
are both cases where reading prior art beat deriving it.

### §3.3 — THE SLICES, GATES BEFORE CODE

| Slice | What | **GATE** |
|---|---|---|
| **P1-S0** | **Instrument.** Extend `posecheck` to report the pose delta **PER PASS**, not one max across the second. Also report it against a KNOWN head motion, not whatever the wearer did — `113` and `111` §5 both flag that the current max is uncomparable across runs | **G-P1-0: the per-pass delta is non-zero and GROWS with pass index.** If pass 2 is no staler than pass 0, the premise is wrong and P1 is pointless. **This gate can kill the whole slice for the cost of one instrument** |
| **P1-S1** | **One pose per pass**, sampled or passed per R1's answer, carried with the pass to submit time | **G-P1-1: `posecheck MAX delta` drops toward zero WHILE THE HEAD IS MOVING.** The motionless `-TimewarpYaw` test (`98`) gives the controlled motion. **G-P1-2: fps stays 60 and submits stay 90** — `103`-`105` are four demonstrations that a new synchronisation point costs everything |
| **P1-S2** | **Per-pass predicted display time**, so each pass is posed for the instant it will actually be shown | **G-P1-3: the wearer.** By this point the numbers cannot answer it. `95` |

**P1-S0 SHIPS FIRST AND ALONE.** It is an instrument, it can invalidate S1 and
S2 before they are written, and today produced two separate cases (`111` §2,
`113` §2) of an instrument that measured something other than its name.

### §3.4 — THE HONEST RISK

**`113` §4's contradiction is still open: 90 rendered, 90 consumed, 30
repeating.** **If one present in three is showing a repeated image, giving each
pass its own pose fixes the pose on a frame that is a duplicate anyway.**

> **SO O94 GATES P1.** Resolve the pick trace first. **This is the one ordering
> constraint in this document.**

---

## §4 — MODS AND TEXTURES

### §4.1 — THE TEXTURE PIPELINE IS ALREADY BUILT, AND IT IS UPSTREAM MIT

**Found while writing this. `lib/rt64/src/common/rt64_replacement_database.*`
and `render/rt64_texture_cache.h` already implement a complete texture
replacement system:**

| | |
|---|---|
| **Hash-keyed lookup** | `getResolvedPathFromHash(uint64_t tmemHash, ...)` — replace by TMEM hash, the standard N64 approach |
| **Packs as folders OR zips** | `ReplacementDirectory(dirOrZipPath, zipBasePath)` |
| **A versioned hash scheme** | `ReplacementConfiguration::hashVersion = 5` |
| **Per-texture operations** | `ReplacementOperation::Stream` and filters — stream vs. preload, per texture |
| **A mipmap cache** | `ReplacementMipmapCacheHeader` — precomputed mips, so packs do not pay for them at load |
| **A JSON database** | `to_json`/`from_json` on the whole config |

> ## **DO NOT BUILD A TEXTURE SYSTEM. RT64 HAS ONE. THE WORK IS AUTHORING A PACK AND WIRING THE PATH, NOT WRITING THE PIPELINE.**

**Rule 12 and the prior-art rule: RT64 is MIT and upstream of us, so this may
influence anywhere including the upstreamable half.**

**READS OWED (all free, no launches):**
- **T1: is the replacement path actually REACHED on our build?** `52`'s lesson —
  a system that exists and is never called is `42`.
- **T2: what does it do under the VR eye path specifically?** Every texture is
  sampled twice per frame, once per eye. **Streaming behaviour under a doubled
  sample rate is not something upstream will have tuned for.**
- **T3: VRAM.** A 4K pack at 5838x4498 per eye is §1.1's real constraint. **This
  is where the 5090 gets asked for something.**

### §4.2 — MODS

**`MODS-IDEAS.md` already exists and is not read into this plan.** The
infrastructure question is the same one the 6DoF work keeps hitting: **a new
`RECOMP_PATCH` name costs a long build** (`07`), and we are at **45 names across
46 sites** (`91`).

**The cheap discipline that already works: `85`'s seam.** Hook one leaf function
and write the engine's own override fields, rather than adding a name per mod.

---

## §5 — ROUTE B, THE TIMEBASE: LAST RESORT. RECORDED, NOT CHOSEN.

**Owner's decision, restated so nobody relitigates it: the timebase stays last
resort.**

**Why it is genuinely expensive**, from `99` §4's read of the tree: 39 of 43
literal `g_ClockTimer` comparisons are against zero and survive untouched; **four
are not and are named.** The real cost is **the hundreds of duration constants
meaning "N sixtieths of a second"** — `99` §4.1 has the fractional-tick variant
that avoids them. **And `92`: changing the quantum changes the aim feel of every
weapon**, because `crosshair_x_pos` steps once per `g_ClockTimer`.

### §5.1 — WHAT WOULD PROMOTE IT

**Write the trigger down now, so the decision is made on evidence and not on
frustration:**

> **Route B gets promoted if — and only if — P1-S0's gate G-P1-0 PASSES (the
> staleness is real and grows per pass) AND P1-S1 then fails to remove it
> without costing the frame rate.**
>
> **That would mean the view genuinely cannot be sampled faster than the sim
> within this architecture, which is the only thing Route B fixes and the only
> argument that justifies its cost.**

**Until that is measured, Route B stays parked.** `92`, `99` and `106` all
reached for it early; **`111` showed the cheap route was working all along and
only its arithmetic was wrong.**

---

## §6 — THE ORDER

1. **O94 — the pick trace.** Built, building. **Gates P1 (§3.4).**
2. **Commit both repos.** Five source files and eight documents outstanding, now
   failed five sessions. `48` floor item 1.
3. **`ds_option 2` as the default.** Free, measured, kills the shimmer. **The
   only shippable win available today** — `111` §4, `108` §3.
4. **R4** — read Perfect Dark's frame pacing. Free, and may collapse §3.
5. **P1-S0** — the per-pass pose instrument. **Ships alone.**
6. **T1/T2** — is the replacement path reached, and what does it do per-eye.
7. **P1-S1**, if G-P1-0 passes.
8. **Route B** — only on §5.1's trigger.

**AND THE TWO SHIP BLOCKERS ARE STILL UNTOUCHED: B3 and B4.** `39` has had them
marked BLOCKING since `75`. **Nothing in this plan addresses them, and that is a
choice being made by default rather than deliberately.**
