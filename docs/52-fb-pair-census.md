# 52 — where is the world? The framebuffer-pair census

**2026-08-23, between `51`'s plan and its build.**

**Built and compiling. Diagnostic only — it reads what is already there and
changes no behaviour.** Needs one `-Flat` launch to report.

---

## Why this exists

`51`'s M1 measured that the displayed image follows whichever eye pass ran
**last** (+116/+129 px under `-SwapEyes`, against 0 px for the alternative).
`51` then concluded its own fix was aimed correctly.

**That conclusion did not follow.** Two mechanisms predict M1's result
identically:

| | Mechanism | Fix |
|---|---|---|
| **(a)** | One `viewProjTransformsBuffer` shared by both eye passes. Last upload wins | `51` — per-eye buffer |
| **(b)** | The **world** is drawn into shared framebuffer **pair 0**, which `setOverride()` does not redirect. Each eye's scratch target only receives a copy of it | Redirect the pair the world is actually in — a different slice |

**The fix for (a) is a no-op for (b), and vice versa.** M1 does not discriminate.

This is the project's signature failure, caught this time before the code:
`25` settled the eye sign by argument, `32` found the knob it flipped had been
deleted, `49` cleared the transform buffer by arguing about a race, and `50`
called an asymmetry THE root cause on one measurement. **Four instances. The
rule that keeps being paid for is rule 3.**

## What it measures

Once per session, per framebuffer pair: colour-image address, game-call count,
**perspective vs orthographic projection count**, and the drawn colour rect —
plus which pair `interpolationTargetKey` chose to redirect.

The world is the pair with the perspective projections. The HUD is orthographic.

```
[gevr] fb census: 2 pairs, redirected pair = 1
[gevr]   pair 0: addr=0x........ calls=N persp=N ortho=N draw=WxH
[gevr]   pair 1: addr=0x........ calls=N persp=N ortho=N draw=WxH   <-- REDIRECTED
[gevr] fb census verdict: ...
```

## The decision rule, written before the measurement

| Verdict | Means | Next |
|---|---|---|
| **The world IS the redirected pair** | `50` Risk 1 is **not** the cause. The sharing is upstream, in the transforms | **Build `51`** as written |
| **The world is in the SHARED pair** | `51` is a **no-op**. The scratch targets only ever hold a copy of one shared world image | **New slice: redirect the pair the world is in**, or every pair. `51` is shelved, not built |
| **No perspective projection anywhere** | The census is measuring the wrong thing | Fix the census before trusting either branch |

**What would make this instrument useless?** If both pairs carry perspective
projections in comparable numbers, the census does not have a clean answer and
says so rather than picking the larger one silently.

## Cost

One `-Flat` launch. No headset. Nothing to undo — if the answer sends us to a
new slice, the census stays as a permanent instrument, and it is the line that
would have saved `50` from being built on a guess.

---

## RUN 1 — the census fired on the wrong workload, and said so

```
[gevr] fb census: 1 pairs, redirected pair = -1
[gevr]   pair 0: addr=0x003DA800 calls=1 persp=0 ortho=1 draw=320x240
[gevr] fb census verdict: NO perspective projection in any pair.
       The census is looking at the wrong thing.
```

One pair, one orthographic call, 320x240, and **no pair chosen for redirection
at all** (`-1`). That is a title or menu workload, not the world.

**The one-shot latched on the first VR-enabled workload it saw**, which arrives
long before anything perspective is drawn.

**This cost one launch and produced no wrong conclusion**, because the third
branch of the decision rule was written down before the measurement and the
instrument reports it in its own words. Had the census silently picked "the pair
with the most perspective projections" out of a set containing none, it would
have named pair 0 — and pair 0 is precisely the answer that sends the project
down the shared-pair route. **A wrong answer, in the exact shape of the expected
one.** The `48` habit that caught it: *what would this instrument have to see for
its verdict to be wrong?*

### The correction

Latch only on a workload that has the world in it: **at least one perspective
projection AND a redirect target already chosen** (`interpolationTargetFbPairIndex
>= 0`). Anything else leaves the probe armed for the next workload.

---

## Prediction, written before the launch

**The world will be in pair 0 — the SHARED one — and `51` will be shelved.**

Reasoning, offered as a prediction and not as a finding: `interpolationTargetKey`
scans pairs from the last backwards and takes the first *early-present*
candidate, which selects for the pair that is presented, not the pair the world
is drawn into. On a game that draws the world and then composites a HUD pass over
it, those are different pairs.

**If this prediction is right, `49`, `50` and `51` were all aimed one layer away
from the defect, and the census is the first thing that looked at where the world
actually goes.**

---

# RUN 2 — THE ANSWER. The prediction was WRONG

```
[gevr] fb census: 1 pairs, redirected pair = 0
[gevr]   pair 0: addr=0x003B5000 calls=260 persp=1 ortho=2 draw=440x330   <-- REDIRECTED
[gevr] fb census verdict: the world (pair 0, 1 perspective projections) IS the
       redirected pair. The shared pair is NOT where the world goes -
       docs\50 Risk 1 is not the cause. Look at the shared transform buffer.
```

**The world workload has ONE framebuffer pair, it holds the perspective
projection and all 260 draw calls, and it is the pair that gets redirected.**

The `fb eye` probe agrees on the address in the same run:
`overrideAddr=0x003B5000` — the world's colour image is the thing being
redirected.

| Hypothesis | Status |
|---|---|
| **(b)** the world is drawn into a shared, non-redirected pair — `50` Risk 1 | **DEAD.** Measured, not argued |
| **(a)** the shared `viewProjTransformsBuffer` | **The remaining candidate. Build `51`** |

## Scoring the prediction

**Wrong, and worth keeping.** The reasoning — *"`interpolationTargetKey` takes
the first early-present candidate, which selects the presented pair, not the pair
the world is drawn into"* — was plausible, mechanical, and untested. **It is the
same species of argument this document was written to stop trusting**, and it
went in the predictions section rather than the findings section precisely so it
could be scored instead of believed. That is the only reason it cost nothing.

## A real correction to `49`, found on the way

`49`'s central line reads:

> *"2 framebuffer pairs but only pair 1 is redirected. The other 1 are SHARED
> between the eye passes - **if the world is in one of them**, eye 1 overwrites
> eye 0."*

**That conditional was never tested until now, and the answer is no.** The line
is true about pair counts and wrong about consequence — and `50` was built on
it, as "THE ROOT CAUSE".

The `fb eye` probe also **latches one-shot on the first workload with recorded
pairs**, which in run 1 was a **title/menu** workload — `pairs=2`,
`overrideAddr=0x003DA800`, matching run 1's census of the menu exactly. In run 2,
properly in a level, it reports `overrideAddr=0x003B5000`, the world.

**So `49`'s "2 pairs, pair 1 redirected" may itself have been measured on a menu
frame.** That is the same latch defect this census had in run 1, in an
instrument the project has trusted since `49` — and it is `48` rule 4 landing on
the tool rather than the test.

**Open, and worth its own fix: give the `fb eye` probe the census's latch
condition.** Until then, treat its pair count and index as describing whatever
workload happened to arrive first, not the world.
