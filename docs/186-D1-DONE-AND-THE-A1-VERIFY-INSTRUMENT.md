# 186 — `D1` IS DONE, AND `A1`'s VERIFY STEP IS BUILT. NO BEHAVIOUR CHANGED.

**2026-08-25 session. Tiers per `182`. Every commit is the owner's (`00-START-HERE`).**
**`185` order followed exactly: `D1` first, then `A1`'s VERIFY, and `A1` ITSELF IS NOT WRITTEN.**

---

## §0 — WHAT IS IN THE TREE, AND WHAT IS NOT

| | | |
|---|---|---|
| **`D1`** | the log label renamed | **DONE** |
| **`A1` VERIFY** | the band instrument | **BUILT, UNRUN** |
| **`A1` THE FIX** | the cone clamp | **DELIBERATELY NOT WRITTEN** |

**TWO FILES TOUCHED, BOTH `.c`: `patches/ge_vr_aim.c` and `patches/ge_vr_bindtest.c`.**
**NO HEADER CHANGED, so `115`'s cross-boundary trap does not apply and a partial
build is legitimate this once.** `[READ]` — it is the whole diff.

**ZERO NEW SYMBOLS**, so `168` §5's mandatory grep of `patches/externs.h` and
`patches/structs.h` has nothing to fail on: everything read here is either our
own patch-side global or a call site that already existed.

---

## §1 — `D1`. THE LINE NOW NAMES THE SHOT.

`[READ]` `ge_vr_bindtest.c:889` printed `crosshair_angle` under the word
**`BULLET`**. That was TRUE when `90` wrote it and **STOPPED being true at
`172`/U-16**, which split the two. `184` §3a is the record of what the stale
label cost: an hour, and a claim that had to be retracted.

**IT NOW PRINTS THE CONSUMER'S OWN SELECTION** — the identical condition
`ge_vr_aim.c:638` uses, `geVrClampSplitActive() && g_geVrTrueAimHave` — under
`BULLET`, and the clamped field under `SIGHT`.

```
[gevr] 6dof-game: BULLET aim=(X,Y)px src=TRUEAIM | SIGHT crosshair_angle=(X,Y)px CLAMPED | GUNPOINT ...
```

> **`src=` IS NOT DECORATION.** When the split is off or nothing was published
> this frame, `BULLET` and `SIGHT` are **EQUAL BY CONSTRUCTION** — that is the
> fallback `:638` takes, and it is CORRECT behaviour, not a silent failure.
> Without `src=`, "the two are equal" would be ambiguous between the fallback and
> a broken publish. `48` rule 9.

**AND ONE TRAP AVOIDED IN THE WRITING, WORTH RECORDING BECAUSE IT IS INVISIBLE:**
`GE_VR_LIT(lit)` is `recomp_puts((lit), sizeof(lit) - 1)`. **A ternary inside it
compiles fine and prints FOUR BYTES of whichever string won**, because `sizeof`
takes the size of a POINTER the moment the argument stops being a literal. It is
written as an `if`/`else` over two literals for that reason.

---

## §2 — ►►►► `A1` VERIFY. THE LINE THAT DECIDES WHETHER `A1` IS BUILT. ◄◄◄◄

**`182`: AN `[INFERRED]` CLAIM MAY NOT BE BUILT ON.** `184` §4's cause — the
divide is unbounded between the frustum edge and the `fwd[2] < -0.05f` refusal,
so a ~37 degree band of DIFFERENT gun directions collapses onto ONE screen point
— **is `[INFERRED]`**, and `185` `A1` therefore carries a VERIFY step marked not
optional. **This is that step, and it changes no term in any expression.**

### THE CLASSIFICATION IS IN TANGENT UNITS, NOT DEGREES
That is the unit the fault lives in. **After `167`, the frustum edge IS
`|nx| == 1` by construction**, because the ray is divided by the RENDER's own
live tangents. So, read once per 90 frames, CUMULATIVE:

| term | meaning |
|---|---|
| `aimed` / `refused` | the two sides of the `fwd[2] < -0.05f` test. **`aimed` is the denominator** — a raw count of wild samples means nothing without it |
| `INSIDE` | `\|nx\| <= 1` and `\|ny\| <= 1`. On frustum, the divide is honest |
| **`BAND`** | **passed the refusal, but off frustum. `>>> THIS IS THE CLAIM UNDER TEST. <<<`** |
| `SAT` | the `162` +-2 clamp actually fired — the samples that all land on one pixel |
| `noFrus` | **the `167` frustum path was REFUSED. See §3 — this term can void the run.** |
| `maxNx` / `maxNy` | the extremes, `x1000` |
| `lastNdc` / `lastFwd` | one live sample, `x1000`, signed |

### HOW TO READ IT, WRITTEN DOWN BEFORE THE RUN SO THE ANSWER CANNOT BE FITTED
- **`BAND` large against `aimed` -> `184` §4 CONFIRMED.** Ordinary play does enter
  the region, the divide is returning legal enormous values there, and **`A1`'s
  cone clamp is the right fix.** Build it.
- **`BAND` at or near zero -> `[INFERRED]` FALSIFIED. DO NOT BUILD `A1`.** The
  quadrant behaviour then has another cause and the cone clamp would be a fix for
  nothing. **Write that up as a finding — it is a result, not a failed session.**
- **`SAT` large** -> the `162` clamp is the collapsing mechanism. `184` measured
  **290 of 1,313** at `(480,340)`.
- **`maxNx`/`maxNy` just over `1000`** -> only grazing the edge. **In the
  thousands** -> `162`'s *"twenty times off screen"* family. **Both want the same
  cure but read very differently**, which is why the extremes sit beside the
  counts.

---

## §3 — THE ONE WAY THIS INSTRUMENT COULD HAVE LIED, AND THE GUARD AGAINST IT

**`|n| == 1` IS THE FRUSTUM EDGE ONLY ON THE `167` PATH.** If `geVrAimFrustum()`
refuses — the host has not established tangents — `nx`/`ny` fall back to the
stock `transform3Dto2DCoords` pixel inversion, **whose unit is the GAME's 106
degree frustum.** Counting those together would silently mix two units and
**manufacture exactly the false `BAND` figure this instrument exists to avoid.**

**So they are counted SEPARATELY as `noFrus` and are evidence for nothing.**
**`noFrus` large -> THE RUN IS NOT EVIDENCE.** Fix that first, re-run, and read
nothing above until it is small.

**AND THE FLAG IS SET INSIDE THE `hX > 0.01f && hY > 0.01f` GUARD, NOT BESIDE THE
CALL.** Degenerate tangents leave `nx`/`ny` holding the stock inversion **even
though `geVrAimFrustum()` returned 1** — scoring those as frustum-relative is
precisely the error `noFrus` exists to prevent. The flag means *"`nx`/`ny` were
actually recomputed"*, not *"the call succeeded"*. It is cleared every frame
before it can be set (`48` rule 13).

**THE FLAG IS TAKEN FROM THE EXISTING CALL, NOT A SECOND ONE.**
`geVrAimFrustum()` WRITES `g_geVrAimFrus`, and calling it twice a frame would
work while making the instrument a participant in the thing it measures.

---

## §4 — WHAT IS OWED, IN ORDER

1. **BUILD.** Two `.c` files, no headers — `115` does not apply.
2. **ONE RUN**, the standing command from `MAIN-STATION-TASKS.md`, unchanged.
   **SWEEP THE GUN WIDE AND DWELL AT THE EXTREMES** — right, left, up, down, and
   deliberately past where the crosshair stops, a few seconds each way. The band
   is only entered if you aim into it, and **the print is once per 90 frames, so
   a fast sweep can pass THROUGH the band between two samples and score nothing.**
   **NO SHOTS ARE NEEDED.** Both instruments sit in the PER-FRAME
   `caclulate_gun_crosshair_position_rotation` and are populated by aiming alone;
   `B1` is the run where firing is the measurement. **And `BULLET` vs `SIGHT`
   diverge only while the sight is CLAMPED, so the same dwell past the stop is
   what proves `D1` too — equal ON-screen is correct, not a fault.**
3. **READ `A1-VERIFY`.** `noFrus` first, then `BAND` against `aimed`.
4. **THEN, AND ONLY THEN, `A1` + `A2` AS ONE BUILD** — or `186` §2's falsification
   branch, written up as its own doc.

**`[ASSUMED]`, AND IT IS THE ONLY ASSUMPTION IN THIS DOCUMENT:** that a wide
deliberate sweep enters the band in the same proportion ordinary play does. **If
`BAND` is large only when sweeping and near zero otherwise, that is a THIRD
answer** — real, but not the everyday fault — and it should be recorded as such
rather than forced into either branch above.
