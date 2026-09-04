# 150 — END-OF-SESSION HAZARD SCAN

**2026-08-24. A sweep for things that will bite a future session, logged as each
one was found so a budget cut-off loses nothing. Nothing here is fixed unless it
says so.**

---

## H-1 — SIXTEEN `recomp_printf` CALLS IN PATCH CODE, AND ONLY THE FIRST OF EACH WORKS

**`100` established it: `recomp_printf` carries its FIRST call and then stops.**
**This session proved the consequence** — `workbench_theboy.c`'s
`[trace] retrace ... sgf=` line printed **once in one run and zero in another**,
and `131` §5 had named it as THE gate for RB-02 (`134`, `136`).

**Live `recomp_printf` call sites still in the tree:**

| File | Count |
|---|---|
| `widescreen.c` | **6** |
| `workbench_theboy.c` | **6** |
| `ge_vr_bindtest.c` | 3 |
| `ge_vr_route_b.c` | 3 |
| `boot.c`, `print.c` | 1 each |

> **ANY OF THESE MAY BE SILENTLY DEAD. Do not write a gate on one.** The working
> emitter is `recomp_puts` via the hand-rolled `GEVR_LIT` / `geVrPutNum` pattern
> in `ge_vr_route_b.c`, which produced 950 lines in a single run.

**RECOMMENDED:** when any of these is next relied on, convert it rather than
trust it. **Not converted now — `48` rule 5, and none is load-bearing today.**

## H-2 — `widescreen.c:11` STILL HAS THE UNGUARDED `60 / speedgraphframes`

**`131` §4 found and fixed this in `workbench_theboy.c:695`** where it is a live
divide by zero once `deltaFrames` can be 0.

**`widescreen.c:11` has the identical line** and is **inside `#if 0`, so it is
dead today.** **It is a loaded gun for whoever flips that `#if`** — the whole
block is a `dynGetMasterDisplayList` patch, and enabling it under `-ViRate 90`
would divide by zero on one frame in three.

**RECOMMENDED:** guard it in place even though it is dead, or delete the block.
**Not touched — it cannot fire as it stands.**

## H-4 — THE KNOB AUDIT IS CLEAN, WITH ONE EXCEPTION: `GE_VR_LOG_VIEW`

**Checked both directions — `48` rule 6, "a knob with no flag in `vr.ps1` is a
knob that never fires", and its converse, a knob that never gets cleared.**

**GOOD NEWS, and it is worth recording because it was not obvious:**
**every one of the 38 `GE_VR_*` variables `vr.ps1` clears IS read by the host.**
There are **no dead knobs.** (A first pass suggested 38 dead ones; that was a
grep that only looked for `getenv(` and missed the `ge_vr_env_float()` helper.
**Verified before logging** — `48` rule 4.)

> **THE EXCEPTION: `GE_VR_LOG_VIEW` is READ by the host and is NOT in `vr.ps1`'s
> clear list.** So if it is ever set in a shell, **it stays set for every
> subsequent launch from that shell** and no `vr.ps1` invocation will clear it.
> That is the exact shape of the leak the clear-list exists to prevent.

**RECOMMENDED, one word:** add `"GE_VR_LOG_VIEW"` to the `foreach` clear list in
`vr.ps1` (~line 279). **Not done — it is a behaviour change to the launcher and
this session has already been bitten once by a tidy-up (`142`).**

**Also read but not cleared, and deliberately out of scope:** `GE_LIVE_*`,
`GE_HYB_*` — the LiveGamecode / hybrid-ROM knobs. They are a different subsystem
with its own conventions and `vr.ps1` is not their launcher.

## H-5 — FOUR LAUNCHER KNOBS ARE NOW OBSOLETE, AND ONE OF THEM IS A TRAP AT 90 Hz

`vr.ps1` still offers **`-EyeInterp`, `-EyeSampleTest`, `-EyeSetPhase`,
`-PosePerPass`.** **All four exist to fix artefacts of interpolating 60 into 90**
— the duplicate frame, the eye-set phase fault, the per-pass head pose.

> **UNDER ROUTE B THERE IS NO INTERPOLATION AT ALL** — `147` measured
> `interpUsed=0` with `distinctTargets=90`. **The machinery these knobs enable
> has nothing left to do, and `126` predicted exactly this: RB-02 makes
> `121`-`126` "a no-op with one pass per frame".**

**THE TRAP:** they are still selectable, and **`-PosePerPass` and `-EyeSetPhase`
both imply `-EyeInterp`**, which allocates a second eye-target set and switches
the present thread onto the interpolated sampling path. **Combining one of them
with `-ViRate 90` would re-enable a path built for a problem that no longer
exists**, and `105`/`115`'s character-misplacement regression lives on that path.

**RECOMMENDED:** have `vr.ps1` **refuse or warn** when any of the four is
combined with `-ViRate`, the way it already refuses `-FloatDelta` without
`-ViRate`. **Not done — launcher behaviour change, `48` rule 5, and nobody is
likely to set them by accident.** **But do not delete them either:** they are the
only way back to the old path if Route B ever needs to be A/B'd against it.

## H-6 — THE FENCE-WAIT AUDIT IS OTHERWISE CLEAN

**Checked every `WaitForSingleObject` and `ID3D12CommandQueue::Signal` in
`src/main`.** `149`'s `waitForGpu()` is the **only** one, and it is now checked.
**There is no second instance of the B3 pattern hiding elsewhere.**

## H-7 — `.bak` CLUTTER IS HARMLESS

29 `.bak*` files across `patches/` and `src/main/`. **`.gitignore` covers them
with three patterns** (`*.bak`, `*.bak[0-9]`, `*.bak*`). **They cannot reach a
commit.** Left alone — several are the only record of a pre-change state.

## H-8 — NO DUPLICATE LIVE `RECOMP_PATCH` DEFINITIONS

Checked with `#if 0` blocks excluded: **no symbol is patched twice in the live
tree.** (`select_ramrom_to_play` appears twice in `workbench_theboy.c`, but one
is inside a disabled block.) **`132`'s deletion of `fps.c`'s dead
`waitForNextFrame` patch removed the one real instance.**

## H-9 — `-ViRate 90` IS NOT THE DEFAULT, AND THAT IS DELIBERATE. NOT A HAZARD.

> ### **OWNER, ON READING THIS ITEM: *"It's not default because we are still testing and apply what we need when we need it."***
>
> **CLOSED. DO NOT CHANGE THE DEFAULT.** Flags are applied per run, on purpose,
> for as long as this is a test build. **A future session that "tidies" this into
> a default is undoing a decision, not fixing a defect.**

**The reasoning below is kept because it is still true of the eventual ship
build** — when this stops being a test build, the default becomes a real
question, and this is the argument for changing it then. **It is not a question
now.**

**AND THE METHOD IS THE POINT:** every flag stays opt-in, so a launch describes
itself and an unset build is always the reference. **That is the same discipline
that made `131` safe to test and that gave `133` an accidental baseline worth
having.** It has already paid for itself twice this session.

---

### THE ORIGINAL WRITE-UP, KEPT FOR THE SHIP BUILD

**`vr.ps1` declares `[int] $ViRate = 60`.** So **every launch that does not
explicitly pass `-ViRate 90` runs the OLD 60 Hz sim with RT64 interpolating up
to the panel** — the duplicate frame, the interpolated-frame artefacts, and the
judder that `147` just closed.

> ### **THE BUILD THE OWNER CALLED *"SO MUCH better... totally playable and enjoyable"* IS NOT THE BUILD THAT LAUNCHES BY DEFAULT.**

**This was correct while RB-02 was unproven** — `131` insisted an unset build be
byte-identical, and that discipline is what made the whole slice safe to test.
**It is now the wrong default.** `147` and `148` record Route B as closed and
shipped; **the launcher does not agree with them.**

**RECOMMENDED, and it is one character:** `[int] $ViRate = 90`, with the banner
kept so a run still says what it is doing. **Then `-ViRate 60` becomes the
opt-out for A/B work, which is the right way round.**

**NOT DONE.** It is a behaviour change to every future launch, made at the end of
a long session, on a launcher that has already bitten this project once tonight
(`142`). **It belongs in its own build with a deliberate before-and-after** —
and it should be the owner's call, not mine, because it changes what "just run
it" means.

**AND IT INTERACTS WITH `148` 6D-00:** if `-ViRate 90` becomes default, **every
6DoF wear test inherits 90 Hz automatically**, which is what you want — but B3
(`149`) is unproven at 90, and the only B3 data in existence predates Route B.

## H-10 — THE SHUTDOWN CHAIN IS COHERENT, AND `42`'s EARLY STOP DOES FIRE

**Traced end to end, because `149` touched it and a wrong belief here costs a
reboot to discover.**

```
SDL_QUIT (input.cpp:194)  -> ge_vr::begin_shutdown()   drains, sets shutting_down
RT64 deinit hook          -> drain again (fast)        -> xr_shutdown(drained)
~RT64Context (safety net) -> xr_shutdown(drained)      idempotent, `done` guard
```

**All three paths are present and the guards are real:** `begin_shutdown` is
`exchange`-guarded so it runs once; `xr_shutdown` has a `static bool done`;
the drain sets `g_ge_vr_shutting_down` before taking the mutex so the draw hook
early-returns.

**The timeouts nest correctly:** drain 2000 ms, fence 1000 ms, and **a failure at
either now takes the deliberate-leak branch** rather than proceeding (`149`).
**`begin_shutdown` discards its drain result — harmless**, because the deinit
hook re-drains and that result IS honoured.

**No defect found here. Recorded because "I checked and it is fine" is worth as
much as a finding when the next session is deciding where to look.**

## H-11 — NO `TODO` / `FIXME` / `HACK` MARKERS IN ANY GoldenEyeVR-AUTHORED FILE

`ge_vr_xr.cpp`, `rt64_render_context.cpp`, `ge_vr_bindtest.c`,
`ge_vr_route_b.c`, `ge_vr_host.h` — **zero.** Unusual, and worth stating: the
open questions in this project live in numbered documents rather than in code
comments, which is why the documents matter as much as they do.

## H-3 — `widescreen.c:254` — `counterstrike++ % 20` WITHOUT AN INITIALISER CHECK

`if (counterstrike++ % 20) { ... }` — the `x++ % N` idiom `100` documented.
**Benign for a gate that only needs to come true eventually**, which is why
`s6dofTick` survived. **Recorded so it is recognised, not fixed.**
