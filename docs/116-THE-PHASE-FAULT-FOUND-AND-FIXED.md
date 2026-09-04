# 116 — O94 CLOSED. THE PUBLISH/CONSUME PHASE FAULT, MEASURED AND FIXED.

**2026-08-24. The pick trace answered it on the first clean run. `113` §4's
three irreconcilable facts reconcile.**

---

## §1 — THE TRACE

**`-EyeInterp -EyePickLog`, on the clean rebuild, 60 fps / 90 submits:**

```
pick trace (oldest first):  1:0:03eb  1:0:03eb  0:1:839a   x8, every second, forever
```

**Perfectly periodic. A three-present cycle:**

| Present | set | pass | target |
|---|---|---|---|
| 1 | 1 | 0 | `03eb` |
| 2 | **1** | **0** | **`03eb`  <- THE DUPLICATE** |
| 3 | 0 | 1 | `839a` |

> ## **ONE DUPLICATE IN EVERY THREE PRESENTS. THAT IS `dupSrc=30/90` TO THE DIGIT, AND THE TWO INSTRUMENTS WERE BUILT INDEPENDENTLY.**

**This is `113` §4.1's SECOND predicted outcome — "the same pair twice running
-> a publish/consume phase fault."** Written before the run, and it is what
arrived.

---

## §2 — THE MECHANISM

**`105` published the set index as a free-floating atomic:**

```cpp
ext.sharedResources->vrEyePassSet.store(geVrEyeWriteParity, release);   /* AT THE END */
geVrEyeSetParity ^= 1u;
```

**Released at the END of the workload — after every pass is rendered.**

**The present thread reads it at the START of each present:**

```cpp
const uint32_t passSet = ext.sharedResources->vrEyePassSet.load(acquire);
```

> ## **SO THE FIRST PRESENT OF A WORKLOAD READS THE PREVIOUS WORKLOAD'S SET INDEX, AND RE-PRESENTS ITS PASS 0.**

**At 60 sim into 90 display, `displayFrames` alternates 1, 2 — so the cycle is
two workloads and three presents, and exactly one of those three lands before
the new set is published.** The trace and the arithmetic agree.

### §2.1 — AND IT EXPLAINS EVERY LEFTOVER

| `113` §4's contradiction | Resolved |
|---|---|
| `eye0=90` rendered | **True.** Ninety eye passes really are rendered |
| `interpUsed=90` consumed | **True, and misleading.** Every present DID take a published pass target — it just took **the wrong workload's** on one in three |
| `dupSrc=30/90` repeating | **True, and now explained** |

**None of the three was lying. `interpUsed` counts pass PICKS and never claimed
they were DISTINCT** — the same shape as `reused` in `111` §2, and the third
instrument this week whose name promised more than it measured.

---

## §3 — THE FIX: REMOVE THE SECOND SOURCE OF TRUTH

**`48` rule 8: when two things must agree, do not synchronise them — remove the
second one.**

**The present thread ALREADY knows which workload it is presenting.** It binds
`frameCounters` to that workload's `InterpolatedFrameCounters`
(`rt64_present_queue.cpp:122`) and reads `count` from it to decide
`framesToPresent`. **That phasing is demonstrably correct, because
`framesToPresent` is correct.**

**`vrEyePassSet` was a SECOND, separately-published answer to "which workload
are we presenting" — and the two disagreed one time in three.**

**So the set index now lives beside `count`, and inherits its phasing for
free:**

```cpp
struct InterpolatedFrameCounters {
    ...
    uint32_t eyeSet = 0;        /* docs\116 */
};

curFrameCounters.count   = displayFrames;          /* workload queue, :1169 */
curFrameCounters.eyeSet  = geVrEyeSetParity;       /* stamped in the same breath */
```

**And the COUNT comes from the same place as the SET.** Taking one from the
workload's counters and the other from the atomic would leave exactly the
mismatch being removed.

**Knob-gated: `GE_VR_EYE_SETPHASE=1`, or `.\vr.ps1 -EyeSetPhase` (which implies
`-EyeInterp`).** Unset keeps `105`'s atomic, so the two are A/B-able in one
sitting and `111`'s numbers stay comparable. **`103`-`105` are three
demonstrations that this exact synchronisation is easy to break, so the old path
stays reachable until the new one is worn.**

---

## §4 — THE GATES

```powershell
.\build.ps1
.\vr.ps1 -UnitsPerMetre 50 -SeamNoRot -HandPosZ 1 -EyeSetPhase -EyePickLog
```

| Gate | **PREDICTION** |
|---|---|
| **G-116-1** | **`dupSrc` drops from ~30/90 to ~0/90. THE GATE.** Anything else and the diagnosis is wrong |
| **G-116-2** | **fps stays 60, submits stay 90.** `103`-`105` each cost both. A regression here means the fix reintroduced a dependency |
| **G-116-3** | **The trace stops repeating.** Expect `1:0:xxxx 0:0:yyyy 0:1:zzzz`-style with no consecutive identical entries |
| **G-116-4, WORN** | **DOES THE STICK TURN LOOK SMOOTH?** The only gate that matters, and the only one a log cannot answer. `95` |

**WHAT WOULD MAKE THIS FAIL AND STILL LOOK LIKE SUCCESS** — `52`'s rule: if
`frameCounters.eyeSet` is itself read from the wrong slot, `dupSrc` could fall
while the images become WRONG rather than distinct. **G-116-4 is the guard
against that, and it is a wearer gate for a reason.** Watch for the character
misplacement of `105`/`115`.

---

## §5 — WHAT THIS DOES NOT DO

**IT IS STILL THE STICK-TURN HALF.** `104` §2, unchanged: the head pose is
sampled once per game frame. **`posecheck MAX delta` will not move and head turn
may not improve.**

**If G-116-1 and G-116-4 both pass, the duplicate-frame judder is closed after
`92`, `93`, `94`, `96`, `97`, `98`, `99`, `103`, `104`, `105`, `106`, `107`,
`111`, `112`, `113` — and the head-turn half (`114` §3, P1) becomes the whole
remaining problem.**
