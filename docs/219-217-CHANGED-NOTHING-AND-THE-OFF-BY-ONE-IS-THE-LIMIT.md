# 219 — `217` CHANGED NOTHING MEASURABLE. AND MY OWN INSTRUMENT IS NOW THE LIMITING FACTOR.

**2026-08-26. Tiers per `182`. `[MEASURED]` from two runs, `-BulletDir` default
and `-NoBulletDir`.**

---

## §1 — THE A/B, AND IT IS A NULL RESULT

**`[MEASURED]`, the two arms side by side, boundary pairs discarded:**

| | default (`217` on) | `-NoBulletDir` (`217` off) |
|---|---|---|
| gun `+37` | bullet `-145` | bullet `-145` |
| gun `+87` / `+103` | bullet `-136` / `-100` | bullet `-100` |
| gun `-142` (physically turned) | bullet `-147`, err `-3.7` | bullet `-140`, err `+0.3` |

**THE TWO ARMS ARE INDISTINGUISHABLE. `217` HAD NO MEASURABLE EFFECT ON THE
BULLET.**

> **AND THAT IS A RESULT, NOT A WASTED BUILD.** `217` was `[INFERRED]` from a
> frame argument and is now falsified as a *sufficient* cause. **The frame
> mismatch it describes may still be real — `194`, `200` and `217` all found the
> same class of error — but it is NOT what is steering the bullet.**

---

## §2 — WHAT THE DATA DOES SAY, AND WHAT IT REFUSES TO

**`[MEASURED]` the relationship is PARTIAL, which excludes both simple stories:**

| gun yaw | bullet yaw |
|---|---|
| `+38` | `-145` |
| `+87` | `-136` |
| `+103` | `-100` |
| `-143` | `-147` |

- **NOT "the gun is ignored"** — 65 degrees of gun moved the bullet 45.
- **NOT one clean frame error** — no fixed rotation maps all four rows.
- **AND THE PHYSICALLY-TURNED GROUP IS NEAR-PERFECT IN BOTH RUNS** (`0.3` and
  `3.7` degrees), which says the aim is correct **exactly when the wearer's real
  body faces the way his character does.**

**I WILL NOT FIT A MECHANISM TO FOUR NOISY ROWS.** `182` §2's rule about the
sample of convenience applies to my own analysis, and `209` §2 already recorded
that nineteen `[INFERRED]` tags were written this month without their
counter-example search. **The honest position is that the data is not clean
enough, and the reason is mine.**

---

## §3 — ►►►► THE OFF-BY-ONE HAS MUDDIED THREE ANALYSES. IT IS FIXED NOW. ◄◄◄◄

**`item_related` updates only when a round LANDS** (`185` `B1`), so the value
read at fire time is **the PREVIOUS shot's.** `216`, `217` and `218` each had to
reason around it, boundary pairs had to be discarded by hand, and **`218` §5 only
became readable once the owner mentioned which test was a physical turn.**

**THE FIX: publish the impact POINT every frame, and let the HOST log the moment
it CHANGES.**

```
[gevr] IMPACTNEW at=(x,y,z) dist=Nu
```

**That line is emitted at the instant the point moves — which is the instant the
CURRENT shot landed — and it appears in the log AFTER that shot's `SHOTREC` and
`SHOTWORLD`. Pairing becomes ADJACENCY. No assumption, no discarded rows, no
dependence on the wearer remembering the order.**

**SAME SYMBOL, WIDER PAYLOAD** (`f32 units` -> `f32* in4`), **so no new address
and `136`'s double build does NOT apply. ONE BUILD.**

**AND THE 1-UNIT THRESHOLD IS NOT COSMETIC:** `gunSetTracerTarget` is shared, so
**every impact in the world writes this field, including other characters'
shots.** A jitter below one centimetre is not a new shot.

---

## §4 — THE RUN, AND IT IS SHORTER THAN THE LAST THREE

**Nine shots. No walking, no wall-hunting.**

| # | do this |
|---|---|
| **1** | **THREE shots FORWARD**, level, pausing between each |
| **2** | **THREE shots UP AND RIGHT** |
| **3** | **PHYSICALLY TURN 180 (chair and all), then THREE shots forward** |

**PAUSE ~2 SECONDS BETWEEN SHOTS.** The pairing is now by adjacency, and a pause
guarantees the `IMPACTNEW` line lands between two shots rather than beside one.

**THEN `Copy-Item .\gevr.log .\gevr-keep-IMPACTNEW.log` and send it.**

---

## §5 — WHAT IS OWED

1. **BUILD ONCE. RUN §4.** Every shot then has ITS OWN impact.
2. **RE-DERIVE THE GUN-VS-BULLET RELATION** with clean pairs. **If it is a fixed
   rotation, that rotation IS the fault and it is one matrix.** If it is still
   partial, the bullet has more than one input and the next question is which.
3. **`217` STAYS IN, DEFAULT ON.** `[MEASURED]` it changes nothing, so it costs
   nothing — **and `00-START-HERE`'s standing policy is DELETE NOTHING.** It is
   marked as falsified-as-sufficient, not removed.
4. **`218`'s TORSO YAW IS UNAFFECTED BY ANY OF THIS** and is still worth
   building for locomotion, which is a separate want.

> **AND THE PATTERN THIS DOCUMENT EXISTS TO BREAK:** `213`, `214`, `215` and
> `217` were four builds in a row, each a reasoned fix that the next measurement
> corrected. **`200` and `203` were two recordings that each answered a question
> completely.** The difference is not luck — **it is whether the instrument could
> pair cause with effect.** This one finally can.

**NOTHING STAGED. THE COMMIT IS THE OWNER'S.**
