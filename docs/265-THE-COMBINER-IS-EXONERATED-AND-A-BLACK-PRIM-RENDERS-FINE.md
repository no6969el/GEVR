# 265 — `263` §4 IS DEAD. THE COMBINER IS EXONERATED BY A COUNTER-EXAMPLE IN THE SAME LOG.

**2026-08-29n. `run_ccprobe.log`, 6,581,956 bytes, 50,341 frames, `game_exit requested`
present, ZERO exceptions.** The probe of `264` ran and answered its question — **against
the hypothesis it was built to test.**

---

## §1 — THE RUN IS VALID. CHECKED BEFORE ANY NUMBER WAS READ.
`[MEASURED]` exe `22:42:14`, log `22:56:16`, **log newer**. `findstr` finds `ccprobe`
in the binary. **Terminating record present** (`262` §5). `miss=0 wrongnum=0` on every
`texbind` line. `CorumovZ` drew **5,745** times, so **the cast roll ran** — the `263` §6
repro held.

## §2 — ►►►► THE MEASUREMENT ◄◄◄◄

`[MEASURED]` **768 draw lines. ONE combiner across all of them: `0x0000040832000a29`,
`c2=1 cyc=1 geom=0x2205`.** The combiner does not vary between the faulty draw and every
correct one, so **it cannot be the discriminator.**

| | texel | prim | env | shade | renders |
|---|---|---|---|---|---|
| **`CorumovZ` `1917` — THE FAULT** | **`8b0000ff` dark RED** | `(255,255,255,0..42)` | `(0,0,0,255)` | `(167,167,167,255)` | owner: **BLACK** |
| `CheadbrosnanZ` `1608` — the control | `000000ff` BLACK | `(254,254,254,255)` | `(0,0,0,255)` | `(255,255,255,255)` | **correct** |
| **`CheadbrosnanboilerZ` `1608`** | **`000000ff` BLACK** | **`(0,0,0,255)` BLACK** | `(0,0,0,255)` | `(255,255,255,255)` | **correct** |

> ## **A BLACK TEXEL DRAWN WITH A BLACK PRIM RENDERS CORRECTLY. THE ONE SURFACE THE OWNER
> ## SEES AS BLACK HAS THE LEAST BLACK INPUTS OF ANY DRAW IN THE LOG.**

**`264` §4's falsification condition, verbatim: *"HYPOTHESIS DEAD if the 1x1 draws come
back with sane non-black prim/env/shade and a combiner that selects one of them."*
Every colour input on Ourumov's 1x1 draws is non-black. THE CONDITION IS MET.**

**AND THE COUNTER-EXAMPLE SEARCH `182` §2 DEMANDS WAS IN THE SAME LOG:**
`CheadbrosnanboilerZ` is the run where the proposed cause held and the effect did not.
**24 lines carry `prim=(0,0,0,*)` and six carry `shade1=(0,0,0,*)`; none of those models is
a reported fault.**

## §3 — WHAT IS NOW DEAD
| theory | killed by |
|---|---|
| **`263` §4 — the 1x1 surfaces render black because their COMBINER INPUTS are black** | §2. Non-black inputs on the fault; black inputs on a correct draw |
| the colour combiner as the search space at all | one combiner value across all 768 draws |

## §4 — AND A SECOND-ORDER READ, `[INFERRED]`, NOT TO BE BUILT ON
**A surface drawn from `texel=8b0000` × `prim=white` × `shade=grey` cannot appear black.**
So either **the 1917 draws are not the shirt**, or the shirt is not drawn by any 1x1 bind.
`263` §2's correlation — *"1917 is bound by `CorumovZ` alone"* — was a correlation between
a unique texture and a unique fault, **and it has now been tested and did not hold up.**
**The counter-example search for this one has NOT been done. It is a hypothesis, not a
finding.**

## §5 — ►► THE PROBE'S OWN FAULTS. BOTH MINE. ◄◄
1. **THE TABLE SATURATED. `entries=64 overflow=16`.** Every model carries its OWN copy of
   a 1x1 image, so the weapons alone hold ~50 of 64 slots. **16 distinct binds were
   dropped and never recorded.**
   > **ABSENCE FROM THIS TABLE IS NOT EVIDENCE OF ABSENCE.** No Trevelyan model appears in
   > it. That is CONSISTENT with `263` §5 (`CboilertrevZ` has zero degenerates) but this
   > run does not prove it, and must not be cited as if it did.
2. **`near=` AND `last_delta=` IN THE CENSUS ARE MISDOCUMENTED — `264` §4 ROW 3 IS
   RETRACTED.** `ge_cctab_find()` is called on EVERY textured draw by part 3, not only on
   1x1 uploads, so `near` counts near-misses across the whole draw stream and its delta is
   noise. **`unkeyed=12` is correct** — that counter lives only in the upload path.
   The pointer key itself is `[MEASURED]` sound: 12 unkeyed 1x1 uploads against 377,511
   keyed draws, `miss=0`, and per-MODEL attribution rather than per-texnum, which is
   better than `264` claimed.
3. **THE SAMPLE IS EARLY-FRAMES-ONLY.** 12 lines per entry, drawn from `f=1419..32167` of
   50,341, and `CorumovZ`'s twelve all fall in `f=2721..2722`. Fine for a question about a
   static bind; **it is not a survey of the run.**

## §6 — WHAT THE NEXT PROBE MUST DO, AND WHY IT IS THE SAME BRIDGE
**Stop keying on `1x1`. Key on the MODEL.** `264`'s pointer bridge already does the hard
part; it is currently filtered to degenerate binds by one `if`.
**`GETV_CCMODEL=CorumovZ` — record EVERY bind of the named model, then print one line per
draw that binds one of them.** That answers the question `263` §2's correlation was
standing in for: **what actually draws the shirt, and what does it get?**
**Its falsification condition must be written before it runs, and it must include: if the
shirt surface never appears in the model's own bind set, the draw is not a textured draw
at all and this instrument cannot see it.**

## §7 — NOT CLAIMED
- **No cause is named.** `263` §4 is dead; nothing replaces it yet.
- No claim about the Trevelyan face. **Nothing in this run touches it.**
- No claim that `8b0000` is the wrong colour for that surface — **the ROM's own intent for
  texnum 1917 has not been read.** It could be a collar tab. That read is owed.
