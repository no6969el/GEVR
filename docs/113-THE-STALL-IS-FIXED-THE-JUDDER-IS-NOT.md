# 113 — THE STALL IS FIXED. THE JUDDER IS NOT. AND THREE FACTS DO NOT RECONCILE.

**2026-08-24. `112`'s counter, run on both builds, worn. The wearer: *"I ran
both, they felt the same. Both did the same thing."***

---

## §1 — THE NUMBERS

| | knob OFF (run A) | **knob ON (run B)** |
|---|---|---|
| fps | 60.1 | **60.0** |
| submits/s | 90 | **90** |
| eye passes/s | 90-92 | **90** |
| `interpUsed` | 0 | **90** |
| **`dupSrc`** | **90/90** | **30/90** |

> ## **ONE SUBMISSION IN THREE STILL CARRIES THE SAME SOURCE TEXTURE AS THE ONE BEFORE IT. THE DUPLICATE FRAME IS NOT FIXED.**

**That is exactly the 1-in-3 `93` §5 predicted, measured properly for the first
time — and it is unchanged from before `103`.**

**AND THE WEARER CONFIRMS IT.** Both builds felt the same. **`95`: the wearer is
this project's best instrument, and he is agreeing with the number.**

---

## §2 — G-112-1 FAILED ITS PREDICTION, AND THE REASON VOIDS THE BASELINE

**`112` §4 predicted `dupSrc` ~60/90 with the knob off. It read 90/90.**

**Because with the knob off the present thread samples THE SAME TWO
`RenderTarget` OBJECTS FOREVER** — `eyeColorTargets[0]` and `[1]` — and the
workload rewrites their CONTENTS every game frame. **The pointer never changes
while the content changes sixty times a second.**

> ## **SO ON THE KNOB-OFF BUILD THE COUNTER IS BLIND. `90/90` IS NOT "NINETY DUPLICATE IMAGES", IT IS "THIS COUNTER CANNOT SEE THIS BUILD".**

**`112` §3 named this exact limitation — "it compares POINTERS, not PIXELS" —
and understated it.** It said a low number was necessary-but-not-sufficient. **It
should also have said that a HIGH number is meaningless wherever the buffers are
reused in place, which is precisely the knob-off path.**

**The knob-OFF number is VOID as a baseline. Only the knob-ON number is
informative**, because there the pointers genuinely rotate.

**Corrected at source in `112`. Rule 10 — and it is the second instrument in two
documents to be caught by asking what it prints on a build that fails the way we
care about.**

---

## §3 — WHAT `107` ACTUALLY BOUGHT

| | Before `107` | After |
|---|---|---|
| **The pipeline stall** | 16 fps, 13 submits, `xrWaitFrame` 75 ms | **FIXED. 60 fps, 90 submits, 9.3 ms** |
| **The duplicate frame** | 1 in 3 | **1 in 3. UNCHANGED** |
| **What the wearer feels** | — | **UNCHANGED** |

**The stall was real and it was blocking, and `106` §2 was wrong about its
cause. That is worth having.** **It was not the judder.**

---

## §4 — AND THREE FACTS DO NOT RECONCILE. THIS IS THE OPEN QUESTION.

1. **`eye0=90`** — ninety eye passes RENDERED per second.
2. **`interpUsed=90`** — the present thread took a published pass target on
   **all ninety** presents, not one in three.
3. **`dupSrc=30/90`** — **thirty of those ninety repeat the previous pointer.**

**Ninety published, ninety consumed, thirty repeats. Those cannot all be true of
a healthy pipeline, and nothing here says which one is lying.**

> **NO MECHANISM IS PROPOSED IN THIS DOCUMENT, ON PURPOSE.** `106` §2's
> criticism of this project was that each explanation was built on the previous
> one's framing rather than re-derived from the numbers, and `103`, `104` and
> `105` are three documents of exactly that. **A fourth story would be the same
> mistake.**

### §4.1 — THE MEASUREMENT THAT SETTLES IT, AND IT NEEDS NO HEADSET

**Log the actual `(set, pass)` pair every present consumes, for one second.**
Roughly ten lines, present thread only, knob-gated.

| It prints | Means |
|---|---|
| `A0 B0 B1 A0 B0 B1 ...` — no consecutive repeats | **`dupSrc` IS WRONG and the fault is in `112`'s counter.** After today that is a live possibility and must be first on the list |
| `A0 A0 B0 ...` — the same pair twice in a row | **A PUBLISH/CONSUME PHASE FAULT.** The set index is released at the END of the workload, so the first present of a workload may still be reading the previous set |
| Ninety distinct pairs, yet `dupSrc` 30 | The pointers differ and something DOWNSTREAM collapses them — the blit or the host copy |

**Each outcome names a different file. That is what makes it a gate.**

---

## §5 — WHAT IS STILL TRUE AND WORTH KEEPING

1. **The stall fix stands.** 60 fps and 90 submits under `-EyeInterp`, where
   `103`-`105` got 16.
2. **`109`'s pacing maxima stand.** ~1 frame in 6 late, intermittently — `111`
   §3, still unexplained and still the best lead on the FEEL of the judder.
3. **`ds_option 2` is confirmed free and kills the distant shimmer** — `111`
   §4. **The one shippable improvement to come out of today, and it is
   independent of every open question above.**
4. **The head-turn half has never been addressed at all.** `104` §2. Everything
   in `103`-`113` is the stick-turn half.
