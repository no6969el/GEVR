# 112 — G93-2, AS `93` ACTUALLY SPECIFIED IT

**2026-08-24. The counter `93` §5 asked for, which has never existed. Pure
diagnostic, one file, `ge_vr_xr.cpp.bak112`. Short build.**

---

## §1 — WHAT WAS WRONG

**`93` §5:** *"count submissions reusing an unchanged image. PREDICT ~1 in 3."*

**What shipped was `reused = submits − renders`, and `renders` is
`g_renderCount`, incremented in `publish_render_pose` on the GAME THREAD once
per game frame** (`rt64_render_context.cpp:1609`).

**So it was `submits − game frames`, pinned to 30 by arithmetic at a 60 sim
submitting at 90.** It produced 30, matched the prediction by coincidence, and
was quoted as confirming it for four documents. **And when `103`-`105` stalled
to 13 submits — below `renders = 60` — the clamp returned 0, and three sessions
read their own stall as the success signal.** `111` §2.

---

## §2 — WHAT IT NOW PRINTS

```
[gevr] posecheck: MAX delta ... | submits=90 renders(GAME FRAMES)=60
       submits-minus-gameframes=30 | dupSrc=N/90 (docs\112 G93-2) | POSE_LAG=0
```

**`reused` is KEPT — so `103`-`106` remain comparable — but RELABELLED to what it
actually computes.** A number that means something other than its name is worse
than no number; `32` and `50` Risk 3 are the same shape.

**`dupSrc` is the real thing:** consecutive submissions whose SOURCE eye textures
are the same objects as the previous submission, from `vrPresentSource[eye]` —
the texture the VI renderer actually sampled.

---

## §3 — WHAT IT WOULD PRINT IF IT WERE LOOKING AT THE WRONG THING

**`52`'s rule, written before the run, and the reason the last one went
unnoticed for four documents:**

**It compares POINTERS, NOT PIXELS.**

| Reading | Means |
|---|---|
| **HIGH** | **CONCLUSIVE.** The same texture submitted twice IS a duplicate frame. No interpretation needed |
| **HIGH, where buffers are REUSED IN PLACE** | **MEANINGLESS — CORRECTED BY `113` §2.** With the knob OFF the present thread samples the same two `RenderTarget` objects forever while their CONTENTS are rewritten every game frame, so the pointer never changes and this reads `90/90` on a build that is not duplicating at all. **The knob-off reading is VOID as a baseline.** This table originally omitted that and it cost a wrong prediction the same day |
| **LOW / ZERO** | **NECESSARY BUT NOT SUFFICIENT.** It cannot see an interpolator that produced two identical images into two different buffers. It says the plumbing delivers distinct buffers; it does not say the pixels differ |

**And it prints `n/a`, never `0`, before RT64 has published an eye source** —
a zero there is indistinguishable from perfection. `91`'s rule.

---

## §4 — THE GATES

```powershell
.\build.ps1
.\vr.ps1 -UnitsPerMetre 50 -SeamNoRot -HandPosZ 1              # run A, knob off
.\vr.ps1 -UnitsPerMetre 50 -SeamNoRot -HandPosZ 1 -EyeInterp   # run B, knob on
```

| Gate | **PREDICTION** |
|---|---|
| **G-112-1, knob OFF** | **`dupSrc` ~60/90.** The present thread samples the same frame-0 pair for all three presents of a game frame, so two in three are duplicates. **If it reads ~0 here the counter is not working, because we KNOW the knob-off build repeats images** |
| **G-112-2, knob ON** | **`dupSrc` ~0/90.** `111` measured `interpUsed=90` — a distinct pass target on every present. **If it is still ~60, the passes are distinct on the sampling side and identical on the submitted side, and something between them is collapsing them** |

**G-112-1 is the important one and it is deliberately a NON-ZERO prediction.**
`48` rule 2: a gate a working build would also pass is not a gate. **A counter
that reads 0 on both builds is broken, not good news** — which is exactly the
trap the old one fell into.

---

## §5 — AND IT BATCHES WITH THE WEAR TEST

**Nobody has worn the `111` build.** This is a diagnostic, so one launch answers
both questions:

- **The number:** is the duplicate frame actually gone?
- **The wearer:** does the stick turn feel smooth now?

**`95`: three separate faults in this project were diagnosed from description
alone.** The number cannot answer the second question and the wearer cannot
answer the first.
