# 297 — ARM 3 IS WRITTEN. THE SECOND EYE BUILDS ITS OWN WORLD, AND THE CUT COST ZERO ESCAPING LOCALS.

**Currency: 2026-09-02, session `297`. CODE + DOCS, OFFLINE ONLY — NOTHING BUILT, NOTHING RUN,
NOTHING COMMITTED.** The offline gates are worn: `stereo_harness.sh` reads **63 passed, 0 failed /
VERDICT PASS**, with the real-header syntax gate now parsing **NINE** files instead of seven.
**Everything below that is not marked `[MEASURED]` is `[INFERRED]` and the run is what decides it.**

---

## §0 — THE HEADLINE, AND IT IS THE OWNER'S SENTENCE, NOT THE INSTRUMENT'S

> *"We're seeing the people, the characters and the props. It's warping all over, and we don't see
> them in the right eye at all. They're not there."*

**Reported after `292`. Reported after `293`. Reported again after `295`.** It has been carried
since `293` as *"the eye-1 model collapse (`MODEL_MTX 39->1`), ARM 3's job"* — a correct diagnosis
written in the instrument's vocabulary, which every later sheet then referenced instead of the
symptom. By `RUN-SHEET-295` §10.1 the project was **telling the owner to expect it and scoring the
gate met anyway.**

**A DEFECT WRITTEN ONLY IN ENGINE TERMS READS AS FILED AND STOPS BEING RANKED. That is the process
finding of this session and it is worth more than the code.** `00-STATE` §3 now carries the symptom
at the top, in the owner's words, and the rule is in §7c: **when the owner reports something they
can see, it goes in §3 in their words and stays there until it is gone; the engine-term entry is
the explanation, never the item.** And no gate ever again says *"expect this to still be there"*
about something the owner has reported.

**ARM 3 IS NOW WRITTEN.** `GETV_STEREO_REBUILD`, default OFF.

---

## §1 — WHY IT WAS UNBLOCKED, AND THE SESSION BEFORE THIS ONE COULD NOT HAVE KNOWN

`295` §5 held ARM 3 out of the build for exactly one reason, and it was a good one: ARM 3
re-`dynAllocate`s every `render_pos` under every eye, so the pair and the arena would agree in
every window and **`GETV_STEREO_PAIRGUARD` could only ever report zero.** Shipping ARM 3 beside
ARM 2's first wearing destroys the only measurement that can say whether `294` §3.6's mismatch has
a real reader.

**THE OWNER WORE IT. `295` §10 records the three arms and their numbers** — S1 `checks=8400
mismatch=0`, S2a `checks=250803 mismatch=600` (**the falsifier fires**), S2b `checks=213951
mismatch=0`. **ARM 2's one stated blocker is spent, and ARM 3 is the job.**

**AND THE ANSWER WAS THE NULL ONE** (`295` §10.1): `mismatch == frames` exactly, every printed site
is `forced-read-after-lvlRender`, and **no engine reader of the stale pair was found in 12,000
frames.** ARM 1 still stands — it closes a real class for two pointer writes — **but it was never
the fix for anything the owner can see.** This document is.

---

## §2 — THE MECHANISM, RESTATED ONCE, BECAUSE BOTH HALVES ARE ONE BUG

`[MEASURED]`, `293` §0 and §2.1, from `292`'s own eighteen dumps:

- **ABSENT.** `292` gated `propsTick()` — and therefore `objTick`'s and `chrTick`'s render builds —
  to eye 0 via `geStereoIsFirstEye()`. Those passes are the **only** code that `dynAllocate`s
  `render_pos` and builds the model matrices. Eye 1 allocated **nothing** and replayed eye 0's
  arena: `MODEL_MTX 39->1`, `MODEL_VTX 17->0`, `MODEL_VTX fresh=0`, and eye 1's DL-CALL set a
  **strict subset** of eye 0's in **every** dump.
- **WARPING.** What did survive was transformed by `render_pos` filled from **eye 0's**
  `camGetWorldToScreenMtxf()` — a coordinate system that is not eye 1's.
- **The gun and the HUD survived** because the viewmodel is eye 1's one fresh allocation per frame.

**The warp is not a second bug. It is the surviving remainder of the first.**

---

## §3 — THE CUT, AND THE MEASUREMENT THAT MADE IT LEGAL

`NEXT-SESSION-PROMPT-297`: *"Do the escaping-locals analysis before writing a line, and say how
many there are."* Done, and the answer is the reason this session produced code rather than another
design document.

### 3.1 — `objTick`: `propobj.c:6000-6378` → `objBuildRenderState(prop, isSimOwner, previousOpenPosition)`

**`[MEASURED]`: 395 lines. objTick declares 202 locals; 53 are referenced in the range.
ESCAPING LOCALS: ZERO.** Not one is both written inside the range and read after it.

- **`sp684` looks like the exception and is not.** It appears at `:6386`/`:6388` and again at
  `:6401`/`:6403` — a loop cursor, `sp684 = current->prev; current = sp684;`, in two independent
  child walks. It carries nothing across. **And the child walk stays behind anyway.**
- **`previousOpenPosition` IS a true input and the first analysis missed it**, because it is
  declared with a trailing comment (`propobj.c:4319`) and a `;\s*$` regex does not match that line.
  It is the door's start-of-tick `openPosition` snapshot, set at `:5164` and read at `:6039`/`:6047`
  for the iris-door SFX edge. **It is a parameter.** The near-miss is recorded because the class is
  general: *a declaration harvest that a compiler did not confirm is a guess.* The extraction was
  driven to zero errors by `gcc -fsyntax-only` under the build's own flags, not by the regex.
- `obj` and `model` are re-derived from `prop` in two lines and are not parameters.

**`isSimOwner` IS THE ONLY GUARD THIS FUNCTION NEEDED, AND IT WAS ALREADY THERE.** `293` §3b.1 read
the block line by line and found **every** accumulator in it already behind the engine's own "this
pass owns the world" bit — the colour lerp, both iris-door SFX edges, the wheel spin, the rotor.
`objTick` passes the real value; the per-eye driver passes 0. **No new guard was added to this
function and none is needed.** That is `293` §3b.1 being *used* rather than restated.

**WHAT STAYS AT THE CALL SITE (`293` §3b.5):** `chrobjWeaponTick(prop)` and the child walk. Once per
frame, both.

### 3.2 — `chrTick`: `chr.c:2855-3227` → `chrBuildRenderState(prop, simOwner)`

**`[MEASURED]`: 373 lines. chrTick declares six locals; the range touches four
(`renderdata`, `chr`, `model`, `headVisible`) and every one is re-derivable from `prop` in three
lines. ESCAPING LOCALS: ZERO.** `chrTick` is ~2,800 lines of AI, animation and physics before
`after_position_update` and **none of it is entangled with the build** — `293` §3c.2's result, and
the reason this cut is cheaper than `objTick`'s.

**AND THIS IS WHERE `293` §3b.1 FAILS TO GENERALISE, EXACTLY AS `295` §3 WARNED.** `chrTick` guards
nothing. **Three guards were added, all in place:**

| line | what | why it cannot run per eye |
|---|---|---|
| `chr.c:2891-2903` | `flinchcnt += g_ClockTimer` | **every character recovers from being shot in half the time.** `293` §3c.1 |
| `chr.c:2910` | `update_color_shading(&chr->shadecol, &chr->nextcol)` | an exponential-approach lerp: 23.4% of the gap per frame instead of 12.5%. **`295` §3 — and `293` §3c.1 missed it** |
| `chr.c:3058` | the L/R-trigger held-weapon tuner | developer-only, and it would double-step. Guarded rather than left as a known wart |

**►► THEY ARE GUARDED IN PLACE AND NOT HOISTED OUT, AND THAT IS A DELIBERATE DEPARTURE FROM THE
PROMPT'S WORD "HOIST".** `flinchcnt` sits **between** the `dynAllocate` and `subcalcmatrices()`, and
`subcalcmatrices` runs the joint callback; `chr.c:2161` and `:2355` read `flinchcnt` for the flinch
envelope. **Moving the statement would change the pose by one tick on the shipping path** — a silent
behaviour change made to fix a stereo bug, which is what `48` exists to forbid. **A parameter guard
changes WHO advances it, not WHEN.** The effect is the hoist; the ordering is untouched.

### 3.3 — AND THE MOVE IS A MOVE

**`[MEASURED]`, by comparison against the pre-edit files:**

- `objBuildRenderState`'s body is **byte-identical** to `propobj.c:6000-6378`, all 379 lines, dedented
  one tab.
- `chrBuildRenderState`'s body contains **every** non-blank line of `chr.c:2855-3227` verbatim,
  indentation included, with exactly **one** line changed —
  `if (!get_debug_render_raster())` → `if (simOwner && !get_debug_render_raster())` — plus the two
  bracketed guards and their comments.

**Read the diff with `--color-moved`. If any line in either body differs in substance from what the
tick had, that is a bug, and this claim is how you find it.**

---

## §4 — THE DRIVER, AND THE FOUR THINGS IT DELIBERATELY DOES NOT DO

`gePropsRebuildRenderPass()` — `chrprop.c`, beside `chraiUpdateOnscreenPropCount` and
`g_OnScreenPropList`, called from `lv.c`'s eye loop **outside** the simulation gate and **before**
`bgLevelRender(DL)`.

1. **IT DOES NOT ADMIT.** `g_OnScreenPropList` and `PROPFLAG_ONSCREEN` are built once per frame on
   the eye that ticks. `293` §3a (the admission test also selects between two *simulation* paths and
   the lines above it mutate the portal table) and `294` §3.4 (`propobj.c:1399` gates the precise
   per-node bullet hit test on that flag). **STATED COST: the second eye's prop admission is the
   first eye's.** Exact at zero separation; at a real IPD a sub-pixel difference in a test that
   admits by room, and `293` §1 measured the room set identical in both eyes in all eighteen dumps.
2. **IT DOES NOT RE-SORT — AND THAT IS `295` §6's OPEN DECISION, MADE OUT LOUD.**
   `chraiUpdateOnscreenPropCount` does not only count: it selection-sorts the list far-to-near by
   `zDepth` for the alpha pass (`chrprop.c:254-276`). **The second eye draws in the first eye's alpha
   order.** Re-sorting per eye would leave the **last** eye's ordering installed for the next frame's
   readers, and the list is read by simulation code (`chrpropUpdateAutoaimTarget`,
   `chraiCheckUseHeldItems`) as well as by the renderer. Two props can only swap if their depths
   differ by less than the parallax between the eyes, in which case they are near-coincident anyway.
   **A limitation written down, not a defect left to be discovered.**
3. **IT DOES NOT TICK.** `isSimOwner`/`simOwner` are passed 0. §3.1 and §3.2 are the whole argument.
4. **IT DOES NOT TOUCH EXPLOSIONS, SMOKE OR THE VIEWER.** Explosion and smoke compute `zDepth` from
   the player matrix in their own ticks (`explosion.c:826`, `:1453`) and have no model build here;
   the viewer is the viewmodel, already per-eye. **Those three types keep the first eye's depth in
   the second. Named, bounded, and the first thing to extend if a run says it matters.**

**AND THE DRIVER CALLS `geStereoNoteArenaBuild()` ON EVERY EYE IT REBUILDS,** so the arena's owner
becomes the **last** eye and `geStereoArenaViewPair()` correctly returns 0. That is `295` §1's
design working as written, not a regression — and `NEXT-SESSION-PROMPT-297` says in terms: do not
"fix" it.

---

## §5 — **A NEW HAZARD THAT NO EARLIER DOCUMENT NAMES: `prop->zDepth` IS NOT RENDER-ONLY.**

`293` §3a puts *"re-derive `zDepth`"* in the per-eye column, and every document since has repeated
it. **`[MEASURED]`, by grepping every reader in the tree, that instruction is incomplete:**

| reader | what it does with `zDepth` |
|---|---|
| `chr.c:4013`, `:4014`, `:4067` | **nearest-candidate selection in the shot/hit test** |
| `chr.c:4020`, `:4148` | **`maxdist` rejection in the shot/hit test** |
| `objective_status.c:670` | objective draw/render distance |
| `bgfog.c:691`, `:699` | fog alpha — **the only one that genuinely wants the per-eye value** |

**So a naive per-eye re-derivation leaves the LAST eye's view-space depth installed for the
simulation to read between frames. At the S3 gate's deliberately absurd `GETV_STEREO_OFFSET=500`
that is a 250-unit error inside a hit test.** It is the same family as `293` §3b.3's tank-rect fear
— **and unlike that one it does NOT cancel**, because `zDepth` is a raw view-space depth with no
round trip back through `V2W` (`294` §1).

**THE REPAIR IS THE SAME SHAPE AS ARM 1's AND COMPOSES WITH IT:** `gePropsSnapshotTickZDepth()`
records the tick's own values immediately after `chraiUpdateOnscreenPropCount()`, and
`gePropsRestoreTickZDepth()` puts them back after the eye loop, beside the view-pair restore. Each
eye still renders with its own depth for fog; **every simulation reader sees exactly what it sees on
the mono path.** One `f32` per onscreen prop, no allocation.

**►► THE GENERAL RULE, AND `00-STATE` §7 GETS IT:** *before moving a write into a per-eye pass, grep
its readers. "Render-only" is a claim about the whole tree, not about the line.*

---

## §6 — TWO TRAPS, ONE PREDICTED AND ONE NOT

- **`chrprop.c` WAS 4,502 OF 4,502 LINES CRLF AGAINST AN LF `HEAD`.** `295` §6 predicted exactly
  this and named the file. **Converted to LF in the same commit** (`288a`'s precedent), and the
  driver's real diff is **219 lines**, not ~4,700.
- **►► AND SO WAS `ge_port_decls.h` — 523 of 535 lines, AND NO DOCUMENT NAMED IT.** `[MEASURED]`
  this session. It is the force-included header, so **every** change that adds a prototype touches
  it, and the first diffstat of this work read **1,056 lines** for a **12-line** addition.
  **Converted in the same commit.** `295` §6 found one file by looking at the one it needed;
  the class is bigger than the instance, and **the standing rule is now: `grep -c $'\r'` any file
  you are about to touch in `vendor/ge-decomp`, before you touch it** (`00-STATE` §6).

---

## §7 — WHAT WAS VALIDATED OFFLINE, AND WHAT THAT DOES NOT MEAN

**WORN:**
- `stereo_harness.sh` — **63 passed, 0 failed, VERDICT PASS.** The three-arm pairing falsifier is
  unchanged and still reads `pairmono 0 / pairoff 2 / pairon 0` — **the middle arm still fires**,
  which is the check that the harness is still an instrument.
- **The real-header syntax gate now parses NINE files** — `chr.c` and `chrprop.c` joined it because
  this change edits them, and it is now fatal on implicit declarations as well as on return-type.
  All nine: **0 errors** under `build_windows.ps1`'s own flags.
- The extraction's byte-identity claims in §3.3, both checked mechanically.
- `ge_port_decls.h` carries the three new prototypes and **nothing declares them locally** — the
  `00-STATE` §6 trap that produced `292`'s link failure.

**NOT ESTABLISHED, AND EVERY ONE OF THESE IS THE RUN'S JOB:**
- **THAT THE CHARACTERS AND PROPS APPEAR IN THE SECOND EYE.** That is the whole point and it is
  `[INFERRED]` until a screen shows it.
- **THAT THE ARENA HOLDS.** `292` §1 doubled both pools for exactly this, but until now the second
  eye allocated nothing, so **the x2 has never actually been spent.** Overflow is silent: the writer
  stops appending with no terminator and `gfx_run_dl` walks into vertex data (`dyn.c`'s own
  comment). **A crash in S2 is the pool, not the eye loop** — and `GETV_GFXPOOL` is the lever.
- **THE COST.** A second full model build per frame. `[INFERRED]` affordable; `P5` says that is not
  a claim. S5 is in the sheet for it.
- **THAT NOTHING DOUBLE-TICKS.** The three guards are the argument; `props interpolated 0` and zero
  `simulation held to` are the measurement.
- **THE gcc CAVEAT.** All nine files parsed under the bridge's **gcc 11.4.0**, not the main PC's
  gcc 15. Strong evidence, different event. **Re-run the harness on the main PC first** — and the
  harness's own flag list was wrong until this session (`296`/`297`: it copied `$gameFlags` and
  dropped `$std`, `$abi`, `$permissive`, so it reported 7/7 FAIL on a tree the build compiles clean).

---

## §8 — WHAT THIS SESSION DELIBERATELY DID NOT DO

- **No re-sort of `g_OnScreenPropList` per eye.** §4 item 2 — decided, not deferred.
- **No per-eye admission.** Invariant 3; it is not a cost-saving, it is a correctness bar.
- **No explosion/smoke/viewer rebuild.** §4 item 4.
- **No separation tuned to a real IPD.** `239`: after the mechanism is proven, never before.
- **No `dlgrab` analysis.** The sheet takes new ones; there is nothing to analyse yet.
- **No touching of `field_10E8`/`field_10EC`** (`295` §1.2's shadow defect). Still named, still not
  measured, still not fixed.

## §9 — STILL OWED

All of `295` §9, minus the two items this session discharges (`chrprop.c`'s line endings; the
`zDepth` sort decision), plus: **`ge_port_decls.h`'s line endings are fixed but the CRLF sweep of
the rest of `vendor/ge-decomp` is not** (~2,100 files, `00-STATE` §6) · the explosion/smoke `zDepth`
gap (§4 item 4) · **and ARM 3 itself, which is written and has never been run.**

---

## §10 — **R0 CRASHED ON THE FIRST SHOT, AND THE CAUSE WAS THE ONE DEVIATION FROM "A MOVE, NOT A REWRITE".**

**`[MEASURED]` 2026-09-02 02:33, owner, `run_297_R0_mono_shipping.log`, `goldeneye.exe 02:30`:**
the MONO shipping path — every `GETV_*` off — **crashes when the gun is fired.** §7 said R0 was the
block that could fail; it failed, and the sheet's own instruction is that this stops everything.

### 10.1 — HOW IT WAS LOCATED, WITH NO DEBUGGER AND NO SECOND RUN

The port's crash handler prints a backtrace of bare addresses (`(no symbol)`), which reads as
useless and is not. `goldeneye.map` gives every symbol at the **preferred** base `0x140000000`; the
trace is at the **loaded** base. Subtracting one from the other and bisecting the map's 46,929
symbols resolves the frames:

```
7   00007ff6a8fb65f3  ->  00000001400b65f3   objBuildRenderState + 199
```

**Read the map to bound it, not just to name it:** `objBuildRenderState` runs
`0x1400b652c-0x1400b73bb`, so `+199` is inside its opening, and `objdump -d` on the shipped exe
prints exactly which lines those bytes are — `prop->flags |= PROPFLAG_ONSCREEN`,
`mtxs = dynAllocate(model->obj->numMatrices << 6)`, `model->render_pos = mtxs`, and the
`isSimOwner` branch into `update_color_shading(&obj->shadecol, &obj->nextcol)`. **Every one of them
dereferences `obj` or `model`.** The frames underneath are `gunCreateBeamForHand` and
`explosionCreateBulletImpact` — the firing path.

**A BACKTRACE OF UNRESOLVED ADDRESSES IS A FULLY RESOLVABLE BACKTRACE IF THE `.map` IS KEPT BESIDE
THE BINARY.** `00-STATE` §6 gets it: never report a native crash as *"no symbols"*.

### 10.2 — THE CAUSE

```c
void objBuildRenderState(struct PropRecord *prop, s32 isSimOwner, f32 previousOpenPosition)
{
	struct ObjectRecord *obj = prop->obj;      /* <-- THIS */
	struct Model *model = obj->model;          /* <-- AND THIS */
```

§3.1 argued these need not be parameters because `objTick` assigns them once at `propobj.c:4522`
and never again — `[MEASURED]`, and **true, and not the point.** What `objTick` holds are **cached
copies**, and there are **~1,500 lines** between that assignment and the block. A copy stays valid
across anything in between that retires the object behind `prop`; **re-reading `prop->obj` does
not.** Firing a gun is exactly that path — a projectile that hits and is removed.

**THE FIX IS TO STOP DEVIATING.** `obj` and `model` are now parameters, and the call passes
`objTick`'s own values. §3.3 claimed the body was *"a move, not a rewrite"* and it was true of all
379 lines; **the two lines that were NOT part of the move are the two that crashed.**

**AND THE SAME SHORTCUT WAS IN `chrBuildRenderState`** — `chr = prop->chr; model = chr->model;`,
200 lines downstream of `chrTick`'s own assignment, the identical class. **Fixed before it fired.**
`renderdata` and `headVisible` stay re-derived, and that is checked, not assumed: `[MEASURED]`,
nothing between `chr.c:2651`/`:2654` and the block touches either — they are initialisers, not
carried values.

### 10.3 — THE RULE, AND IT IS THE THIRD TIME THIS SESSION HAS PAID FOR THE SAME SHAPE

> **WHEN AN EXTRACTION IS JUSTIFIED AS "A MOVE", EVERY LINE THAT IS NOT MOVED IS THE SUSPECT LIST,
> AND IT SHOULD BE SHORT ENOUGH TO WRITE DOWN.** Here it was four lines out of 379 and nobody wrote
> them down, so the review effort went to the 379 that were provably identical.

Same shape as this session's other two: the harness copied three of `build_windows.ps1`'s four flag
groups and reported 7/7 FAIL; the gate's pass string and its blank-frame string were the same
sentence. **`[MEASURED]` beats `[INFERRED]`, and "equivalent" is `[INFERRED]` unless a compiler or
a run says otherwise.**

### 10.4 — WHAT THIS DOES AND DOES NOT INVALIDATE

- **The extraction still stands.** Zero escaping locals is unchanged; the 379-line body is
  unchanged and still byte-identical; the three `chrTick` guards are unchanged.
- **THE FIX IS `[INFERRED]` AND HAS NOT BEEN RUN.** It removes the only deviation the disassembly
  points at, in the function the trace names, on the path the trace's callers describe. That is
  strong and it is not a measurement. **`RUN-SHEET-297` §4 (R0) IS RE-RUN FIRST, AND FIRING THE GUN
  IS THE FIRST THING DONE IN IT.**
- **Nothing below R0 has been run at all.** R1, R2, R3 are untouched. **ARM 3 has never rendered a
  frame.**

---

## §11 — **§10 WAS WRONG. THE CRASH WAS NEVER IN `objBuildRenderState`, AND THE METHOD THAT SAID IT WAS IS THE REAL FINDING.**

**`[MEASURED]` 2026-09-02, three runs and two saved binaries.** §10 is retracted in full below.
The extraction was never the bug. **ARM 3 *was* the regression — but for a different reason, in a
different file, four hundred lines away.**

### 11.1 — THE RETRACTION, AND WHY IT SURVIVED THREE ROUNDS

§10.1 resolved the leaf by **assuming `objBuildRenderState` was the faulting function and
back-solving the load base from it**:

```
base = leaf - (0xb656c + 199)        <-- assumes the answer to compute the evidence for the answer
```

That is circular, and it is stable enough to look like a measurement: it names a real function, the
map bounds it, and `objdump -d` obligingly prints plausible lines. **Two fixes were written against
it. Neither could ever have worked**, and the second was reported as *"confirmed in the binary, not
inferred"* — the instruction bytes were read correctly and attributed to the wrong function.

**THE NON-CIRCULAR METHOD, AND IT IS CHEAP.** Every non-leaf frame in a backtrace is a RETURN
address: the byte immediately after a `call`. That constraint is base-independent, and nine frames
pin the base uniquely.

1. `objdump -d --no-show-raw-insn goldeneye.exe > dis.txt` — `.text` is ~1.2 MB, ~291k instructions,
   well under a second.
2. Collect **R** = the address following every `call`.
3. For each `r` in R, candidate `base = frame8 - (r - 0x140000000)`. Keep it only if 64 KB-aligned
   **and every other caller frame also lands in R**. **Exactly one candidate survives.**
4. **Only then** bisect the map. **Exclude the leaf from the fit** — it is not a return address; it
   is what you are solving for.

Real base was `0x7ff7ab1d0000`; §10 used `0x7ff7ab1b0000`. **Off by `0x20000`.**

**THE TELL THAT WAS VISIBLE FOR A FULL ROUND AND NOT BELIEVED:** under the wrong base the leaf
landed **mid-instruction**, and not one caller frame followed a `call`. A leaf that is not on an
instruction boundary is proof the base is wrong. Nothing else.

**AND THE LOG SAID IT ALL ALONG.** The port prints its own crash header, and nobody grepped for it:

```
[getv] ===== EXCEPTION 0xc0000005 =====
[getv] fault addr: 00000000bdccc587
[getv] FAULT PC:   00007ff6c5514646
```

`FAULT PC` is the leaf for free and cross-checks any derived base. **`fault addr` decides the shape
of the fix**: small (< 0x10000) is a NULL-plus-offset deref and a NULL guard is right; large and
unaligned is a WILD pointer and a NULL guard is worthless. **`grep -n "EXCEPTION" <run log>` IS NOW
THE FIRST ACTION ON ANY CRASH.**

**Two more artefacts of working from a wrong base, both of which wasted a step:**
- `objdump -d --start-address=<arbitrary>` **desyncs the x86 decoder and invents instructions.** It
  printed a 32-bit `lea 0xd0(%rsp),%eax` — a pointer truncation that DOES NOT EXIST; the linear
  dump has `lea ...,%rax`. **Confirm every instruction against the linear disassembly.**
- Nearest-preceding-symbol bisect on a wrong base yields plausible names at huge offsets
  (`MoveBond + 8876`) and a call chain that reads as nonsense. **A correct base gives a chain you
  can read as a sentence.** Compare:

```
WRONG  MoveBond -> bondviewFrozenCameraTick -> sub_GAME_7F0A9AB8 -> gunCreateBeamForHand
       -> bullet_spark_render -> explosionCreateBulletImpact -> objBuildRenderState+199

RIGHT  main -> SDL_main -> bossMainloop -> lvlRender+720 -> chraiCheckUseHeldItems+14
       -> chraiCheckUseHeldItem+236 -> chraiDefaultWeaponFireHandler+2843
       -> chrTestHit+490 -> sub_GAME_7F06C010+23
```

### 11.2 — THE ACTUAL CAUSE: `chr.c:3305`, AN `if` WRITTEN TWICE

```c
    if (headSwitchVisible)          /* 3305 -- the accident, no braces */
    if (headSwitchVisible)          /* 3306 -- the real one */
    {
        chrBuildRenderState(prop, chr, model, 1);
    }
    else
    {   /* clears PROPFLAG_ONSCREEN on prop, both held weapons and the hat;
           syncs shadecol to nextcol */ }
```

The `else` binds to the **inner** `if`. On the FALSE path the outer `if` skips the entire
statement **including the else**. The parent has one `if`, at `chr.c:2853`.

**THE CHAIN.** An off-screen chr never clears `PROPFLAG_ONSCREEN`, while `chrTick:3299-3303` has
already torn `chr->field_20` (the ModelHitEntry / joint list) down to NULL. `chrTestHit` passes its
ONSCREEN guard on stale evidence, loads the NULL list at `chr.c:4170`, and `sub_GAME_7F06C010`
(`objecthandler.c:1377`) walks `while (entry->next != NULL)` **with no NULL check** —
`mov 0x18(%rax),%rax` with `rax = 0`, faulting at exactly `+23`.

**Nondeterministic by construction:** it needs a chr to go off-screen *while still a hit candidate*.
Instrumented, the build survived seven traces and two kills before firing. **That also means §10's
single clean parent run was weaker evidence for "ARM 3 is the regression" than it was reported to
be** — the conclusion held, the confidence was not earned at the time.

**THE INSTRUMENT THAT NAMED IT, AND IT HAD BEEN SITTING IN THE TREE UNUSED.** `GETV_CHR_DEBUG`
(`chr.c:73`) and `GETV_HIT_DEBUG` (`chr.c:217`):
- `jl=12573` **exactly equal to** `vis=12573` — `field_20` IS populated whenever the chr is
  visible. That killed the "never populated" theory in one line.
- **`rej(off=0)` in all seven traces** — not one candidate EVER rejected for `PROPFLAG_ONSCREEN`
  clear. **That zero is the fingerprint of a flag that can no longer be cleared**, and it is what
  pointed at the else branch.

Second symptom of the same bug, cosmetic and unreported until now: **off-screen chrs never sync
`shadecol` to `nextcol`**, so their lighting is stale when they return to view.

### 11.3 — WHAT §10's INVESTIGATION GOT RIGHT, AND THE RULE IT STILL DID NOT BUY

The extraction is **faithful**, and this was checked properly rather than argued. Normalised,
comment-stripped, whole-file multiset comparison of every ARM 3 file against `57d7f55c^`:

| file | code lines lost |
|---|---|
| `chr.c` | **1** — `if (!get_debug_render_raster())`, the intended `simOwner &&` guard |
| `propobj.c` | 3 — all three are this session's own `prop->obj` -> `obj` casts |
| `chrprop.c`, `lv.c` | **0** |
| `stereo.c`, `stereo.h`, `ge_port_decls.h` | purely additive |

Both moved bodies diff clean against the parent's inline ranges (obj: 328 lines vs 328). `lv.c`'s
four new calls genuinely early-return on `!geStereoRebuildEnabled()`.

**►►►► AND THAT CHECK STILL MISSED THE BUG, WHICH IS THE RULE OF §11: A CHECK FOR WHAT WAS *LOST*
CANNOT FIND WHAT WAS *DUPLICATED*.** The extra `if` sat in the additions column, unread, while the
report said "the extraction is clean". **Diff BOTH directions, and read added control-flow lines
with the same suspicion as deleted ones.** `-w` means the compiler will not do it for you:
`-Wdangling-else` and `-Wmisleading-indentation` never fired.

### 11.4 — HYPOTHESES KILLED. DO NOT RE-RUN THEM.

- **"the `field_20` teardown was hoisted"** — NO. Parent `chr.c:2847-2850` and ARM 3 `:3299-3303`
  sit in the identical place. ARM 3's extra teardown at the top of `chrBuildRenderState`
  (`:2686-2690`) is a true no-op for chrTick's call, which nulls it first.
- **"escaping locals"** — NO. `renderdata`/`headVisible` are initialisers only; `tickamount`, which
  chrTick DOES mutate, is never referenced inside the moved range.
- **"the three `prop->obj` casts were the crash"** — NO. The parent has `prop->obj` at all three
  sites and does not crash. They are hardening. **They are kept and they are not credited.**
- **"`bondtypes.h` says `model` is at 0x001C but the code reads 0x20, so it is a wrong-field read"**
  — NO. Those comments are **N64 32-bit offsets, not the native layout.** `chrTick` compiles
  `prop->chr->model` to the same `0x8` / `0x20`. **Confirm a suspected wrong-field read against a
  known-good site before calling it a bug.**

### 11.5 — STATUS

**FIXED, BUILT AND WORN.** `[MEASURED]`: a full session — shooting characters, walking, returning —
with **no `chrTestHit` crash**, 39 MB of log against the 2.2 MB truncated ones the bug produced.
`rej(off=…)` stayed 0 in that run, but the candidate counts were 1-2 and all rejected as `dead` or
`z`, so **the falsifier never got a chance to fire; the survival is the evidence, and it is not the
falsifier.** R0 is green for ARM 3 **except for §12, which is not ARM 3's.**

---

## §12 — **THE MINE CRASH IS PRE-EXISTING. ARM 3 IS CLEARED OF IT.**

**`[MEASURED]` 2026-09-02:** shooting a mine crashes. **The saved pre-ARM-3 parent binary
(`build-windows/goldeneye_PARENT.exe`) crashes IDENTICALLY** — same symbol and offset, same call
chain, and **the same fault address to the byte (`0xbdccc587`) across two different binaries at two
different ASLR bases.** That identity is itself the proof the garbage is deterministic data rather
than heap randomness.

```
main -> SDL_main -> bossMainloop -> lvlManageMpGame
  -> sub_GAME_7F09BBBC+173   (vtxstore_tick -- "merge duplicate batches, may free memory")
  -> sub_GAME_7F09BAC4+82    <-- FAULT
```

**THE DEFECT — A TYPE TAG THAT DOES NOT MATCH ITS UNION MEMBER.** `vtxstore.c:161`:

```c
if (var_s1->type == 1) {            /* 1 == PROP_TYPE_OBJ, NOT PROP_TYPE_CHR */
    var_v0 = var_s1->chr;           /* but reads the tagged union as ChrRecord* */
    var_v1 = var_v0->model->obj;    /* ChrRecord.model is +0x20 native -- FAULT */
```

`bondconstants.h:3930`: `PROP_TYPE_NUL=0, PROP_TYPE_OBJ=1, PROP_TYPE_DOOR=2, PROP_TYPE_CHR=3`.
`PropRecord` is `u8 type` at 0x00 followed by the `{chr,obj,door,weapon,explosion,…}` union — **the
tag selects the member.** An ObjectRecord read through a `ChrRecord*` lands on a float at +0x20;
`0xbdccc577` is ≈ `-0.1f`. Every other walker in the tree pairs them correctly (`chrprop.c:2516`,
`bondview2.c:3743`).

**►► A NULL GUARD IS NOT THE FIX — the pointer is WILD, not NULL. The `fault addr` line is what
established that, and it stopped the wrong patch being written.**

**►► TWO CANDIDATE CORRECTIONS, NOT EQUIVALENT, AND THIS SESSION DELIBERATELY DID NOT CHOOSE:**
1. the filter is wrong — `type == PROP_TYPE_CHR` (3), keeping the ChrRecord cast; or
2. the cast is wrong — keep `PROP_TYPE_OBJ` and read `var_s1->obj->model`, whose `Model *` is at a
   **different offset** than `ChrRecord`'s.

Which matches the N64 original is **unresolved**. `7a4e7bfd` ("three pointer-size errors") touched
this file but **not** the `== 1` test; its `var_v0->model->obj` line is where the ChrRecord read
came from. **Guessing here trades a loud crash for a silent wrong-model bug.** Marked in the source
at `vtxstore.c`, not fixed.

**AND AN OWNER `[REPORTED]` SYMPTOM THAT MAY SHARE THIS NEIGHBOURHOOD:** *the explosion texture does
not show properly in the native port, and it does show properly on the emulator and on the TLb
build.* `vtxstore_tick` merges duplicate vertex batches and rewrites model references, and
`7a4e7bfd` records that `propobj.c:7750` — the rwdata-stride **explosion** crash site — was in this
same family. **Test whether the two share a cause before treating the texture as an asset problem.**
