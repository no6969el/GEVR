# 119 — T1-S0. THE TIMEBASE INSTRUMENT. IT CAN KILL `118` BEFORE `118` IS BUILT.

**2026-08-24. `118` §7's first slice. An instrument, no behaviour change, no new
`RECOMP_PATCH` name. Backups `.bak119`.**

---

## §1 — WHY AN INSTRUMENT FIRST

**`118` argues Route B is a slice rather than a project, and the argument rests
on three numbers NOBODY IN THIS PROJECT HAS EVER LOOKED AT:**

| | | |
|---|---|---|
| `speedgraphframes` | `frametiming.c:53` | **The truncated quantity.** The whole of `92`'s *"90 Hz is structurally unavailable"* is the integer divide at `frametiming.c:82` that produces it |
| `g_ClockTimer` | `lv.c:974` | The engine's integer tick. 152 refs |
| `g_GlobalTimerDelta` | `lv.c:979` | **The engine's FLOAT tick. 217 refs — MORE than the integer — and currently just a cast of it** |

**`118` §1 claims the engine is already predominantly float-timestep and that
only an accumulator is missing. That is a claim about STATIC structure. This is
the runtime check of it, and it costs one launch with no headset.**

---

## §2 — WHAT IT PRINTS

```
[gevr] timebase: delta=1 [1..1] | clk=1 [1..1] | gdelta x1000=1000 [1000..1000] (docs 119, PREDICT all flat at -NoXr 90)
```

**Once every 90 frames. Instantaneous value plus min/max over the window** —
`72`'s standing warning is that a mean cannot see a hitch, and `109` made the
same choice for the same reason. **Windowed, not lifetime: a lifetime max
latches on the first level load and never moves again, which is `55`'s shape.**

**`gdelta` is x1000 because there is no float formatting in patch code.**

---

## §3 — THE GATES, AND THE FIRST ONE CAN END `118`

| Gate | **PREDICTION** | If it fails |
|---|---|---|
| **G-119-1** | **At `-NoXr`, `rr_manual_value 90`: `delta=1` flat, `clk=1` flat, `gdelta=1000` flat, `min == max` on all three** | **NOT FLAT -> the game is ALREADY receiving a variable delta, and `118`'s model of a rigid 60 Hz tick is WRONG.** Everything in `118` would need re-deriving |
| **G-119-2** | **`gdelta == clk * 1000` on every sample** | **NOT EQUAL -> `g_GlobalTimerDelta` is not simply a cast of `g_ClockTimer`, and `118` §2's two-line choke point is wrong** |
| **G-119-3** | The line appears **at all**, under `-NoXr` | Nothing appears -> the patch print path is dead again. `100` fixed it once; **rule 4 says verify the instrument, not assume it** |

**G-119-1 is deliberately a NON-TRIVIAL prediction with a real failure mode.**
`48` rule 2: a gate a working build would also pass is not a gate. **This one
would fail loudly if `118` has the engine's behaviour wrong — which is exactly
what an instrument should be able to do to the document that asked for it.**

---

## §4 — TWO DECISIONS WORTH NAMING

### §4.1 — NOT GATED ON `geVrWorldCamera()`, DELIBERATELY

**`118` §5's whole de-risker is that the timebase work is testable at `-NoXr`
with no headset.** A VR gate would make the instrument silent on exactly the
path that matters. **It runs every frame, in menus and levels, VR or not.** It is
one line per 90 frames.

### §4.2 — THE STATICS PROBLEM, AND A FIX FOR IT — `100`

**`100` established that a static in `RECOMP_PATCH` code CANNOT BE ASSUMED
ZERO**, and noted that `s6dofTick` has only ever worked because
`x++ % 90 == 0` comes true from any starting value within 90 frames — *"luck,
not design."*

> **MIN/MAX CANNOT RELY ON THAT LUCK. A garbage initial minimum would never be
> beaten and would print forever, and it would look like a real measurement.**

**So initialisation is keyed on a MAGIC SENTINEL rather than on zero:**

```c
static u32 tbMagic;
if (tbMagic != 0x7B11BA5EU) { tbMagic = 0x7B11BA5EU; /* seed min/max from the live sample */ }
```

**The odds of uninitialised memory holding that exact word are 1 in 2^32, and if
it ever does the only cost is one window of unseeded extremes.** A documented
hazard rather than an unreachable guard — **rule 13**.

**This is a reusable answer to `100`'s trap and the first time this project has
had one.** Everything before it either avoided statics or got lucky.

---

## §5 — BUILD NOTES

**NO NEW `RECOMP_PATCH` NAME.** It lives inside the already-patched `viSetFovY`,
which runs every frame — the same reasoning `91` used for S0. **Short build.**

**`patches/externs.h` gained `extern f32 g_GlobalTimerDelta;`** — and that is a
HEADER change, so `115`'s guard in `build.ps1` will now force a full rebuild.
**`patches` has been added to that guard's scan roots in this slice**: it was
missing, and `patches/externs.h` is shared by every patch translation unit,
which is `115`'s trap in a second location.

---

## §6 — WHAT IT DOES NOT DO

**It changes no behaviour whatsoever.** It reads three globals and prints them.
**If `118` is wrong, this is the cheapest possible way to find out — and if
`118` is right, these are the numbers the accumulator has to move.**

**RUN IT AT `-NoXr` FIRST.** No headset, no VR, no B3 reboot risk, and it is the
path `118` §5 says the whole first slice can be validated on.
