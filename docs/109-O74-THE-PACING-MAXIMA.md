# 109 — O74, THE PACING MAXIMA. OUTSTANDING SINCE `73`.

**2026-08-24. A pure diagnostic. No behaviour change, no new `RECOMP_PATCH`
name, short build. Backup at `ge_vr_xr.cpp.bak109`.**

---

## §1 — WHY THIS EXISTS

**`72` exonerated the XR submit loop: 516 samples, one over the 11.11 ms budget,
~87% of every frame blocked in `xrWaitFrame`.** That has been quoted ever since
as "the submit loop is not the problem."

**It measured MEANS.** `92`, `73` and `106` all make the same objection:

> ## **A MEAN CANNOT SEE A HITCH, AND JUDDER IS NOTHING BUT HITCHES.**

**So the submit loop was cleared of being SLOW. It was never cleared of being
IRREGULAR, and nothing in this tree could tell the difference.** `73` asked for
the maxima; it has been outstanding through fourteen documents.

---

## §2 — WHAT WAS ADDED

**Four maxima and a late count, printed on their own line BESIDE `72`'s means
rather than replacing them** — the comparison is the instrument:

```
[gevr-xr] stage ms:     waitFrame 9.15 | locate 0.20 | waitForGpu 0.00 | record 0.02 | execute 0.03 | endFrame 0.24
[gevr-xr] stage MAX ms: waitFrame ?.?? | record ?.?? | endFrame ?.?? | frame ?.?? | LATE ?/?? (??%)
```

| Read | Means |
|---|---|
| **max / mean near 1** | **Smooth. `72`'s exoneration holds and is now actually supported** |
| **max / mean several times over** | **HITCHING — and `72` never measured it** |
| **`LATE`** | Frames whose TOTAL exceeded **the runtime's own display period**, from `XrFrameState::predictedDisplayPeriod`. Not a threshold we chose |

**`LATE` prints `n/a`, never `0`, when the display period has not been reported
yet.** A zero there is indistinguishable from a perfect session — `91`'s rule
about unbuilt quantities, and `52`'s "state what you would report if you were
looking at the wrong thing", in a new place.

**Everything resets each second with `g_stage = StageTimes()`, so the maxima are
per-second maxima and not lifetime ones.** A lifetime max would latch on the
first level load and never move again, which is `55`'s shape.

---

## §3 — WHAT IT IS FOR, IMMEDIATELY

**`106` §1's table shows `xrWaitFrame` going 9.15 ms -> 75.40 ms under the interp
knob. That is a MEAN.** Whether it is *"every frame waits 75 ms"* or *"most
frames wait 9 ms and one in eight waits 500"* are completely different faults
with completely different fixes, and **as of today we cannot tell them apart.**

> **RUN THIS WITH G-107-2. It costs nothing and it is the difference between a
> steady throttle and a periodic stall.**

**And it applies to the knob-OFF build too**, which is the one the wearer
actually plays: `72`'s 87%-blocked figure has never had a max beside it.

---

## §4 — WHAT IT CANNOT DO

**It instruments the XR host's frame, not RT64's present iteration.** `107` §3
established that `submitFrame()` runs ON the present thread, so the two are
nested — but the eye blits, the `executeCommandLists` and the
`presentGraphicsWorker->wait()` GPU block all happen in `rt64_present_queue.cpp`
**before** `submitFrame` is entered, and they land inside no stage here. They
would show up only as time that is not accounted for between frames.

**Probing those three is the natural follow-on and is deliberately NOT in this
change** — `107` §3 names the exact call sites.
