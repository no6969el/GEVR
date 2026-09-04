# 136 — `static` HELPERS IN PATCH CODE ARE NOT EMITTED. THE CALL GOES NOWHERE.

**2026-08-24. The root cause of a silent instrument, and it is one word.**

---

## §1 — THE SYMPTOM, AND WHY IT WAS SO HARD TO BELIEVE

`135`'s `[gevr] tick:` line printed **zero times across three runs**, including a
run where the very first statement of the function was an **unconditional**
`recomp_puts` marker that could not be gated by anything.

**And every single link in the chain checked out:**

| Check | Result |
|---|---|
| Is the code in the binary? | **YES** — `gdSum1000` and the marker string are in `patches.bin` AND `GoldenRecomp.exe` |
| Is the function in the patch ELF? | **YES** — `geVrTickInstrument` is in `patches.map` |
| Is the patch active? | **YES** — `waitForNextFrame__recomp_orig` exists, so the original was renamed and ours is the only definition |
| Does the caller run? | **YES** — fps 59.3 -> 88.7. That needs the accumulator inside `waitForNextFrame` |
| Does `recomp_puts` work in this build? | **YES** — 426 `6dof-game` lines in the same log |

**Everything true, and nothing printed.** That is exactly where `121` gave up on
`119`'s line after two hours.

---

## §2 — THE MEASUREMENT THAT SETTLED IT IN ONE COMMAND

Compare what N64Recomp emitted into `RecompiledPatches/patches.c` against what is
in `patches.map`:

| Function | in `patches.c` | in `patches.map` | |
|---|---|---|---|
| `geVrPutS32` (**static**, `ge_vr_bindtest.c`) | **0** | **0** | **INLINED away — works** |
| `geVrTickInstrument` (**static**, `ge_vr_route_b.c`) | **0** | **1** | **NOT inlined, NOT emitted** |
| `geVrViRate` (global) | 1 | 1 | emitted, works |
| `geVrApplyFloatDelta` (global) | 1 | 1 | emitted, works |

> ## **N64Recomp EMITS GLOBAL FUNCTIONS OUT OF `patches.elf`. IT DOES NOT EMIT `static` ONES.**
>
> **A `static` helper in patch code only works if the C compiler INLINES it away
> before N64Recomp ever sees a call to it — and whether that happens is a
> compiler decision that nobody is checking.**

**`geVrPutS32` got inlined into `viSetFovY`.** That is the entire reason `119`'s
hand-rolled emitter works and 950 `6dof-game` lines come out.

**`geVrTickInstrument` did NOT get inlined** — it is large, and its caller
`waitForNextFrame` carries `__attribute__((optnone))`, which suppresses inlining
into it. **So it survived as a real call, to a function the recompiler had never
emitted. The call went nowhere, silently.**

### THE FIX IS ONE WORD

`static void geVrTickInstrument` -> `void geVrTickInstrument`. Same for
`geVrPutNum`.

> ### **RULE: HELPERS IN PATCH CODE ARE NON-STATIC.**
>
> **A `static` that happens to be inlined is a build that works by luck.** This
> is the second time luck has been the load-bearing mechanism here — `100`'s
> `s6dofTick` only ever worked because `x++ % 90 == 0` comes true from any start
> value. **Rule 13's shape, one level up: do not depend on a thing that is true
> by accident.**

---

## §3 — TEN MORE OF THEM ARE IN THE TREE RIGHT NOW

`ge_vr_bindtest.c` has **ten** `static` helpers — `geVrGetEyeParams`,
`geVrGetFixed`, `geVrSetFixed`, `geVrNonZero`, `geVrBuildProj`, `geVrInLevel`,
`geVrWorldCamera`, `geVrPutS32`, `geVrViewmodelHand`, `geVrApplyViewmodel` — plus
one in `interpolation.c`.

**They all work today, which means the compiler is currently inlining all of
them.** Nothing guarantees it keeps doing so: **a helper growing past the
inlining threshold, or a caller gaining `optnone`, silently turns one of them
into a call that goes nowhere.**

**NOT CHANGED IN THIS PASS — they work, and `126` RB-04's discipline is to fix
what actually breaks.** But this is now a named hazard with a one-command test:

```
grep -c "void NAME(" RecompiledPatches/patches.c   # 0 AND in patches.map = broken
```

**AND IT IS A LIVE CANDIDATE FOR `119`/`121`'s MYSTERY.** That block sits inside
`viSetFovY` and prints via `geVrPutS32`. If inlining decisions shifted for that
translation unit on some build, its behaviour would change with no source change
— which is very close to what `121` described and could not explain.

---

## §4 — WHAT THIS COST, AND WHAT IT DID NOT

**Four runs produced no timebase data.** RB-02's fps result stands — it never
depended on this instrument — but **RB-03 and RB-03a are still unmeasured**, and
`126` keeps them that way.

**Nothing in `131` or `132` is contradicted.** The Route B code itself has been
correct throughout; what failed was, in order: a stale binary (`133`), two gates
that could not fire (`134`), and a helper the recompiler never emitted (this).

> **THE FPS COUNTER HAS CARRIED EVERY REAL RESULT IN THIS SLICE.** It is an old,
> boring, independently-built instrument that nobody touched. **Three
> purpose-built gates have now failed in a row.** That is worth remembering the
> next time a gate is written: `48` rule 4, and the fourth instance this week.

**NEXT: rebuild and one `-NoXr -ViRate 90` run.** The marker either prints or it
does not, and after this there are no untested links left in the chain.
