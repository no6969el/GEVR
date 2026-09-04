# 275 — FORTY OF FORTY-FOUR ARE GUARDED. THE SHAPE IS CHOSEN, AND ITS PRICE IS TWO LINES.

**2026-08-30l. Docs run to `275`. NEXT DOC = `276`.**
**`258` STAGE 4's MEDIUM half — the shape of the fractional delta. A SOURCE READ AND A
DECISION. NO CODE WAS WRITTEN, NO BUILD HAPPENED, NOTHING WAS RUN.** Every claim below is
`[MEASURED]` **from source** — each of the 44 divide sites read to its enclosing function's
guard, not to a fixed window.

> # ►►►► `274` §5's COST INPUT IS WRONG. IT IS **40 GUARDED, 4 NOT** — NOT 34/10. ◄◄◄◄
> # AND THE FOUR ARE NOT EQUAL: ONE OF THEM IS A PERMANENT-NaN TRAP THAT **SHAPE 1 ARMS.**
>
> **THE OWNER'S CALL, THIS SESSION: SHAPE 3.** Integer `g_ClockTimer`, fractional
> `g_GlobalTimerDelta`. **Its "second source of truth" objection is now PRICED: exactly two
> sites in the whole tree, both one-line hoists.**

---

## §1 — THE RETRACTION FIRST. THERE ARE THREE GUARD SPELLINGS AND `274` GREPPED FOR ONE.

`274` §5 said its guard status was *"a 25-line-window first cut... It must be read properly
before the change, not after."* **This is that read.** All 44 sites, each traced up to its
enclosing function's opening brace.

`[MEASURED]` **the tree guards this divisor in three different ways:**

| guard form | sites | example | why `274` missed it |
|---|---|---|---|
| `if (g_ClockTimer > 0)` | **34** | `gun.c:1820`, `gunfire.c:6044` | — |
| `if (g_ClockTimer >= (0 + 1))` | **6** | `gunfire.c:5992`, `gunfire.c:6309` | the literal grep. The source even says why the form exists: `// Keep the 0 + 1 for matching.` |
| `if (g_GlobalTimerDelta > 0.0f)` | **1** | `propobj.c:5698` | guards the DIVISOR itself, not the tick count |
| **UNGUARDED** | **4** | `front.c:8941-8943`, `propobj.c:2393` | — |

**BOTH OF `274`'s GUNFIRE ACCUSATIONS ARE DEAD.** `gunfire.c:5994-5996` sits under `5992`'s
`>= (0 + 1)` and `gunfire.c:6311-6313` under `6309`'s. **All 24 `gunfire.c` sites are covered.
All 12 `gun.c` sites are covered. All 3 `bondview2.c` sites are covered** — `7327`, `7670`,
and EU's explicit `if (g_GlobalTimerDelta == 0)` at `7678`, a **fourth** spelling that happens
to sit inside an already-guarded block. `propobj.c:5700` is covered by the `> 0.0f` form.

**`274` §5's other count stands:** `[MEASURED]` 24 iteration sites — 22 `for (i < g_ClockTimer)`
plus 2 `while` (`chr.c:1722`, `gunfire.c:937`). `g_ClockTimer` must stay integer.

> **THE SHAPE OF THIS ERROR IS THE ONE `00-STATE` §4 KEEPS RECORDING.** `259`, `261` §2 and
> `266` §1 were all **a read that stopped one conditional too early**. This one is a read that
> stopped at one *spelling*. **A grep for a guard is not a read for a guard**, and a codebase
> that carries `// Keep the 0 + 1 for matching` will have more than one way to write `> 0`.

## §2 — THE FOUR THAT REMAIN, READ IN FULL

### 2.1 `front.c:8941-8943` — `constructor_menu18_displaycast`. **THIS IS THE TRAP.**

No guard exists anywhere in the function. The block is a divide-then-integrate-then-multiply,
and the delta cancels — **so its ARITHMETIC is indifferent to the delta's value. Its
FAILURE is not.**

```c
8936   if (cast_camera_reset) cast_rootpos_smoothed.y = suboffset.y;      // y's numerator is now EXACTLY 0
8941   vec.f[0] = (suboffset.x - cast_rootpos_smoothed.x) / g_GlobalTimerDelta;   //  x -> ±inf
8942   vec.f[1] = (suboffset.y - cast_rootpos_smoothed.y) / g_GlobalTimerDelta;   //  y -> 0/0 = NaN
8943   vec.f[2] = (suboffset.z - cast_rootpos_smoothed.z) / g_GlobalTimerDelta;   //  z -> ±inf
8945   if (cast_camera_reset)
8947       cast_rootvel_accumulator = vec / CAST_DAMP_COMP;               // NaN ENTERS THE ACCUMULATOR
8952   for (i = 0; i < g_ClockTimer; i++) { ... }                         // runs 0 times -- NOT the path
8959   cast_rootvel_smoothed = cast_rootvel_accumulator * CAST_DAMP_COMP; // still NaN
8963   cast_rootpos_smoothed += cast_rootvel_smoothed * g_GlobalTimerDelta;  // NaN * 0 = NaN. IT STICKS.
```

**`8936` is what makes it NaN rather than merely infinite**, and `8963`'s multiply by zero does
not rescue it — `NaN * 0.0f` is `NaN`. `cast_rootpos_smoothed` is a file-scope accumulator, so
**it stays NaN for the remainder of the cast** and the camera position, the look-at target and
the smoothed root all go with it. The same pattern repeats at `8973-8979` for
`cast_target_accumulator`.

**THE WINDOW IS EXACTLY ONE FRAME PER CAST.** `cast_camera_reset` is set `TRUE` once at
`front.c:8716` and cleared at `8975` on the first render pass. Outside that frame the `8945`
and `8973` branches are not taken and the poison has no way in.

`[MEASURED]` **today `g_GlobalTimerDelta` is zero only while controls are locked or the game
is paused** (`lv.c:1136-1142`), so this frame is never delta-0 and **the trap is latent.
It has presumably been latent since 1997.**

> **AND THAT IS THE WHOLE ARGUMENT AGAINST SHAPE 1.** Shape 1 makes the delta `0,1,1` at
> 90 Hz, so **one frame in three is delta-0** and the reset frame lands on one with
> **probability 1/3, every cast.** A latent retail trap becomes a coin-flip.

### 2.2 `propobj.c:2393` — `objSettle`, the throwing-knife spin rate. **UNGUARDED, AND IT DEGRADES GRACEFULLY.**

No guard in `objSettle` (`propobj.c:2263`), and none upstream: the call chain is
`chrprop.c:2558 -> objTick (propobj.c:4294) -> objSettle (propobj.c:4923, 4929)` and **no
`g_ClockTimer` gate appears anywhere along it.**

```c
2393   tmp = tmp / g_GlobalTimerDelta;
2396   projectile->unk64 = tmp / angle;
2402   if (unk64 < 0.0f)     unk64 = -unk64;          // ±inf -> +inf
2406   if (unk64 < 0.03f)    unk64 = 0.03f;
2408   else if (0.15f < unk64) unk64 = 0.15f;         // +inf -> 0.15. CLAMPED.
```

**`inf` is caught by the clamp.** The only NaN path is `acosf()` at `2387` returning exactly
`0.0f` — a perfectly aligned knife — at the same instant as delta-0, and `NaN` fails all three
comparisons and survives. **Cost when it happens: one projectile's spin rate. Not the camera,
not the state.** Both remaining sites are the same three lines' worth of risk as `front.c`,
one order of magnitude less severe.

## §3 — SHAPE 2 IS NOT *LIKE* `268`. IT **IS** `268`, THE SAME LINES.

`274` §5 warned shape 2 *"reintroduces `268`"* by analogy. `[MEASURED]` from source, it is not
an analogy — **the code already exists and is the thing that was rejected.**

```c
frametiming.c:88    ge_sim_pending_fields += deltaFrames;
frametiming.c:89    if (gePortSimShouldTick()) { speedgraphframes = ge_sim_pending_fields;
frametiming.c:91                                 ge_sim_pending_fields = 0; }
frametiming.c:93    else                       { speedgraphframes = 0; }
```

**"Tick only when a whole field has accumulated, delta always 1" is a verbatim description of
`GETV_SIMDIV`.** It has been built, shipped, run at 90 Hz, and produced `268`'s clipped rooms —
owner, on turning it off: *"Yeah. That fixed it."* **Shape 2 is ruled out from source rather
than from reasoning, and it does not need re-testing to be ruled out.**

## §4 — SHAPE 3'S "SECOND SOURCE OF TRUTH" IS PRICED. **IT IS TWO SITES.**

`274` §5 called shape 3 *"arguably the right split... and arguably a second source of truth.
**Unread.**"* This is that read.

Under shape 3 the two variables mean different things and both are correct on their own terms
at 90 Hz:

| | value at 90 Hz | per real second | consumers |
|---|---|---|---|
| `g_ClockTimer` | `0,1,1` (whole fields) | **60** | 122 frame-counted files; 24 iteration sites; `g_GlobalTimer += g_ClockTimer` |
| `g_GlobalTimerDelta` | `0.667` constant | **60** | 13 delta-scaled files — animation, recoil, sway, camera |

**They disagree only where ONE EXPRESSION USES BOTH.** The dangerous form is a
`g_GlobalTimerDelta` reference **inside** a `g_ClockTimer` loop body: the loop runs 60 times a
second and each pass applies `0.667`, so the term lands at **two thirds** of its intended rate.

`[MEASURED]` **every one of the 24 iteration sites was scanned for a delta reference inside its
loop body. There are exactly two:**

| site | expression | effect under shape 3, unfixed |
|---|---|---|
| **`bondview2.c:7328-7331`** | `for (i<g_ClockTimer) { turret = SCALE*turret + (g_TankTurretTurn / g_GlobalTimerDelta); }` | tank turret turns **1.5x too fast** (the divide inverts the sign of the error) |
| **`propobj.c:5057-5083`**, at `5065` | `for (sp548<g_ClockTimer) { ... (Rocket->unk94 * g_GlobalTimerDelta) / sqrtf(...) }` | projectile ground friction applied at **2/3** strength — grenades and rockets slide further |

**Both are one-line hoists** — take the delta term out of the loop, or divide it by
`g_ClockTimer` inside it. Nothing else in the tree combines the two classes.

**Everything `front.c:8941` does is the SAFE combined form** and is worth naming so it is not
"fixed" by mistake: the divide is **outside** the loop at `8941`, the loop at `8952` uses only
`g_ClockTimer`, and the multiply at `8963` is **outside** again. Divide-by-`d` then
multiply-by-`d` cancels for any non-zero `d`. **Leave it alone.**

## §5 — THE DECISION, AND WHAT IT BUYS

> **►►►► SHAPE 3. INTEGER `g_ClockTimer` BESIDE A GENUINELY FRACTIONAL `g_GlobalTimerDelta`.
> THE OWNER'S CALL, 2026-08-30, ON §2 AND §4. ◄◄◄◄**

| | shape 1 | **shape 3** | shape 2 |
|---|---|---|---|
| `268` can return | no | **no** | **YES — it IS `268`** |
| delta ever 0 outside pause | **YES, 1 frame in 3** | **no** | no |
| arms `front.c:8941` (§2.1) | **YES, p=1/3 per cast** | **no** | no |
| the 4 unguarded sites need work | **yes** | **no — none** | no |
| frame-counted cadence (122 files) | unchanged, 60/s | **unchanged, 60/s** | unchanged |
| `259` §4's judder residual | **present by construction** | **absent** | present |
| sites needing repair | 4 (§2) + review | **2 (§4)** | n/a |

**Shape 3 is the only shape that leaves the 4 unguarded sites untouched, because it never
produces a zero divisor outside pause — which is exactly retail behaviour.** Its price is §4's
two hoists, and both are visible, enumerated, and one line each.

**AND IT IS THE ONLY SHAPE THAT ANSWERS `259` §4.** Shapes 1 and 2 both hand the simulation
`0,1,1` — correct on average, uneven per frame, **judder-shaped, not speed-shaped**, which is
what `96`'s *"it just feels not ninety hertz"* would look like. **Shape 3 hands it `0.667`
every frame and has no residual to observe.**

## §6 — THE NUMERATOR ALREADY HAS ITS VARIABLE. `258` §3.2 COSTS NOTHING EXTRA.

`258` §3.2 requires the sim step be **"a value the program can be TOLD, not only a value it
computes"** — queried by default, pinnable — and says *"it is a rewrite if it is added
afterwards."*

`[MEASURED]` **the variable exists and is already the single runtime home of the present rate:**

- **`gfx_sdl2.c:106` — `int ge_pace_framerate`, DELIBERATELY NON-STATIC.** Its own comment says
  why: *"`nm <binary> | grep ge_pace_framerate` is a..."* — the same discipline that made
  `ge_pace_wait_ms` reachable for `271`.
- Written by `GETV_FPS` at `gfx_sdl2.c:402`, clamped there, and printed in the
  `[getv] pace: %d fps cap %s (GETV_FPS), vsync=%d` banner at `gfx_sdl2.c:435`.
- **So `fields_per_frame = 60.0f / (f32) ge_pace_framerate` is the queried form, and it reads
  the rate the program was TOLD — not a rate it measured, which is what keeps a configured term
  from floating under load** (`274`'s determinism argument).
- **The pin is `GETV_SIMHZ=<n>`**, overriding the numerator source for `258` §3.2's
  common-rate multiplayer session. **`GETV_SIMHZ` IS IN NO BINARY. It is a proposed name for
  an unwritten term** (`274` §9 said this first; it is still true).
- **The seam is `updateFrameCounters()` (`frametiming.c:56`)**, which already carries a
  remainder-carrying precedent in its own free-run path at `frametiming.c:337-343` — and the
  comment there names the exact failure mode of getting it wrong: *"the leftover fraction is
  discarded every time and the clock never advances at all: measured 121 frames and 0 fields
  in a second."*
- **`ge_config.c:388`'s `framerate=30 -> GETV_TICKFIELDS=2` is the port's own precedent** for
  this mechanism at an integer factor, with a printed rationale.

**`P3`'s shape is honoured for free: one runtime variable, one banner, one place to pin.**

## §7 — WHAT THE BUILD MUST DO WHEN IT IS WRITTEN. NOT YET BUILT.

1. **Gated, default OFF.** `48`'s one-behaviour-change; `2`'s every-knob-stays-reachable.
2. **A banner that prints the numerator, ITS SOURCE (queried vs pinned), and the resulting
   fields-per-frame.** `[getv][simhz]`. **A knob that is not in the binary reads as a clean
   null result** — `133`, `268` §4.
3. **A REFUSAL, per rule `17` and `274` §7.** `GETV_SIMHZ` must print `CONTAMINATED` and
   withhold its verdict when asked to run at a rate `ge_pace_framerate` does not agree with,
   rather than silently substituting one. **`GETV_REALCLOCK` is still owed the same gate and
   still does not have it.**
4. **The two §4 hoists in the same change**, each commented with this doc's number.
5. **The diff `258` STAGE 4 asks for.** `vendor/ge-decomp` has `origin =
   https://github.com/n64decomp/007`, so *"did we change the feel"* is
   `git diff <import-base> -- src/game/bondview2.c src/game/propobj.c`, offline, against the
   matching decomp. **It is a diff, not an opinion** — `00-STATE` §7.

**THE `239` GATE, AND ITS FALSIFIER, WRITTEN BEFORE THE RUN** (`15`): re-run `274`'s three-arm
sheet with `GETV_BUDGET=120` added per `274` §3.1 and `GETV_SIMDIV=1` pinned, gated on
`props interpolated 0` **plus** zero `simulation held to` lines (`273` §7.1).

> **PREDICTION, TO BE WRITTEN INTO THE RUN SHEET BEFORE THE BUILD:**
> **`speedgraph` reads `60/s` at BOTH 60 Hz and 90 Hz** — today it reads 60 and **90**
> (`274` §2). **And the owner's stopwatch on the `RB-04` walk reads `18.2 s`, not `27.0`.**
> **If `speedgraph` still reads 90/s at 90 Hz, the term is not in the binary and every other
> number from that run is void.**

## §8 — WHAT THIS DOES TO `00-STATE` AND `258`

- **`00-STATE` §3 item 4's cost input is corrected**: 40 guarded, 4 not; the shape is chosen.
- **`00-STATE` §4 gains one retraction** — `274` §5's 34/10.
- **STAGE 4 remains OPEN and remains MEDIUM.** A decision is not a fix. **`239`'s gate is met
  for the timebase (`274`) and for the shape (this doc); it is NOT met for the fix, which does
  not exist.**
- **STAGE 5 (the pose spine) still precedes STAGE 6 (stereo).** Nothing here touches either.

## §9 — NOT CLAIMED
- **No code was written. No build happened. Nothing was run. No log was produced.**
  `frametiming.c`, `lv.c`, `bondview2.c`, `propobj.c` and `front.c` were **read only**.
- **§2.1's NaN is traced from source, NOT observed.** `[MEASURED]` from source that the branch
  exists, that `8936` zeroes the numerator, and that `NaN * 0.0f` is `NaN`. **Nothing has run a
  cast intro with a zero delta on the reset frame.** It is a prediction and it is falsifiable:
  force `g_GlobalTimerDelta = 0` for one frame at `8941` and the cast camera should die.
- **§4's two-site count is the whole tree's `.c` files under `vendor/ge-decomp/src`**, loop body
  by loop body. It does not cover a delta reference reached through a FUNCTION CALL made inside
  a `g_ClockTimer` loop. **That class is unread and is the one way the count of two could be
  low.**
- **`GETV_SIMHZ` is a proposed name for an unwritten term. It is in no binary.**
- **No CPU or GPU figure was taken.** `272` and `273` own those and neither was re-run.
- **The `objSettle` call chain was traced for a `g_ClockTimer` gate and none was found**, but
  `chrprop.c:2558`'s own callers were not walked to `lvlRender`. If a gate exists further up,
  `propobj.c:2393` is guarded and the unguarded count is 3, not 4. **This does not change the
  decision** — shape 3 makes all four moot.
