# 156 — S1 / 6D-12. ONE KNOB WAS DOING THREE JOBS. IT IS NOW TWO.

**2026-08-25. Prompted by the wearer, unprompted by the plan:** *"they separate
their IPD and their world size, but we only have one — did we program that yet?"*
**No. `148` 6D-12 has said DO IT BEFORE ANY MORE SCALE SWEEPS since it was
written, and S0's own log line has said `ONE-KNOB-THREE-JOBS,S1` since `91`.**

---

## §1 — WHAT THE ONE KNOB WAS DOING

`GE_VR_UNITS_PER_METRE`, measured:

| Site | Job |
|---|---|
| `:1618-1620` the eye positions | **HOW BIG THE WORLD LOOKS.** Eye separation in game units is the measured IPD times this |
| `:1176`, `:1330-1332` hand position | **HOW FAR YOUR ARM REACHES** in game units |
| telemetry | reported one number for both |

**`86` §3.9: Perfect Dark keep THREE — world scale, a per-frame measured IPD
(clamped 1-10 cm, default 64 mm), and `unitsPerCm` for height.**

> ### THE CONFLICT THIS EXISTS TO SETTLE
> **`77` measured ~50 u/m BY WEARING IT. PD's height mapping is 100 u/m
> outright** — *"Joanna's eye sitting at 159 units for 1.59 m."* **`86` says the
> two cannot be reconciled by argument.** They were never in conflict: **they are
> two different jobs that had been sharing one number**, and splitting it is what
> lets each be measured.

## §2 — AS BUILT

**`GE_VR_WORLD_UNITS_PER_METRE`** -> the eyes. **`GE_VR_HAND_UNITS_PER_METRE`**
-> the hand. **Both default to `GE_VR_UNITS_PER_METRE`, so an unset build is an
exact identity** and `-UnitsPerMetre 50` behaves exactly as it always has.

**AND S0 NO LONGER LIES.** Its line was `scale u/m=%.1f(ONE-KNOB-THREE-JOBS,S1)`
— a single number for two jobs, which after the split would have been an
instrument reporting a quantity that no longer exists. It now reads:

```
[gevr] 6dof: scale world=50.0 hand=50.0 u/m (docs156 S1: SPLIT) ipd=0.0639m eyeSep=3.20u
```

**`48` rule 4. The instrument was corrected in the same build as the thing it
measures, not the one after.**

**HEIGHT IS NOT SPLIT OUT.** PD's third number is `unitsPerCm` and it belongs
with **H2 / 6D-10**, which `148` says needs a decision before a build. **Two of
three, and the third is named.**

## §3 — THE GATES

| Gate | Run |
|---|---|
| **G-S1-1** | Unset. **Identical to today** — the whole point of the fallback |
| **G-S1-2** | `-WorldUnitsPerMetre 100` alone. **The world should look HALF SIZE and the hand should not move differently** |
| **G-S1-3** | `-HandUnitsPerMetre 100` alone. **The gun should travel twice as far for the same arm movement; the world unchanged** |
| **G-S1-4** | Read the `scale world=.. hand=..` line and confirm it matches what was passed |

> **WHAT WOULD MAKE THIS USELESS:** if G-S1-2 changes hand travel or G-S1-3
> changes world size, the split did not take and the two are still coupled
> somewhere unread. **Say so rather than sweeping numbers.**
