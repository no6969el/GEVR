# 259 — `RB-04` IS NOT IN `MoveBond`. IT IS AN INTEGER, AND THE PORT ALREADY WARNS ABOUT IT.

**2026-08-29g. `258` §4 stage 1, step 4 — the `RB-04` re-grep in the NATIVE tree.
Desk work, no build, no run. This is the step that existed because every `RB-04`
line number was `[ASSUMED]` recomp-era. It was worth doing: the diagnosis was
wrong, and the fix is already in the tree.**

---

## §1 — THE RETRACTION

**`HANDOVER` has said this, carried forward across several banners:**

> *"Cause: `bondview2.c` — Bond's walk is an exponential approach to a target,
> advanced once per FRAME, with no timestep in the loop."*
> *"it was parked because fixing it means a timestep inside `MoveBond`
> (1307 lines) through a patch layer."*

### **`[MEASURED]` FROM SOURCE. IT IS FALSE. THE WALK IS ALREADY DELTA-SCALED.**

`MoveBond` is at **`bondview2.c:6943`** and runs to **`8341` — 1,399 lines**, not
1,307. The on-foot position advance is **`bondview2.c:7845-7856`**:

```c
move_offset.f[0] += ((headpos_z * theta_transform.f[0])
                   - (headpos_x * theta_transform.f[2])) * g_GlobalTimerDelta;
move_offset.f[2] += ((headpos_z * theta_transform.f[2])
                   + (headpos_x * theta_transform.f[0])) * g_GlobalTimerDelta;
```

**`* g_GlobalTimerDelta`, on both axes.** The debug-fast-bond variant
(`7867-7878`) has it too, and so does the tank path (`7665-7666`).

**And the "exponential approach with no timestep" does not exist either.** The
speed ramps are `bondviewUpdateSpeedForwards` (`4445`) and
`bondviewUpdateSpeedSideways` (`4411`), and **both step by `g_GlobalTimerDelta`**
— `speedgo = speedgo + g_GlobalTimerDelta`, clamped to `±1.0`. They are a
**throttle**, not a position integrator, and the analog path
(`6195`, `6214`) bypasses them entirely with a direct
`analogWalk / 70.0f` assignment.

**WHY THE ORIGINAL SURVEY MISSED IT:** `132` §3 counted *"216 refs, 8 guarded,
all 8 divides, not one an integrator."* **It was looking for divides.** The walk
and the ramps use **multiplication and addition**. `168` §5's rule held and the
survey still missed the site, because the survey's own filter excluded it.

---

## §2 — WHERE `RB-04` ACTUALLY LIVES: THE DELTA IS AN INTEGER

`[MEASURED]` — the whole chain, read end to end this session:

| Site | Symbol | Type |
|---|---|---|
| `frametiming.c:373` | `updateFrameCounters(nextFrameTime)` | `s32` |
| `frametiming.c:88` | `ge_sim_pending_fields += deltaFrames` | **`s32`** |
| `frametiming.c:90` | `speedgraphframes = ge_sim_pending_fields` | **`s32`** |
| `lv.c:1146` | `g_ClockTimer = speedgraphframes` | **`s32`** |
| `lv.c:1151` | `g_GlobalTimerDelta = (f32) g_ClockTimer` | cast to `f32` **after** |

> ### **`g_GlobalTimerDelta` IS AN INTEGER COUNT OF 60 Hz VIDEO FIELDS, CAST TO
> ### FLOAT AT THE END. IT CANNOT REPRESENT TWO-THIRDS OF A FIELD.**

**Every per-frame system in the game steps by it, and 122 of the 135 files under
`src/game` are per-frame** (the port's own note, `frametiming.c:350`).

## §3 — AND THE PORT ALREADY DOCUMENTED THE 1.5x. IN A `printf`.

`frametiming.c:232-259`, written by upstream, never read into our docs:

> *"With the default SYNTHETIC counter, `osGetCount()` advances a fixed amount
> per call, so **every rendered frame counts as exactly one video field and the
> game's wall-clock speed IS the render rate** — at 120Hz the world runs at
> double speed. `GETV_SIMDIV` does not rescue that... **`GETV_REALCLOCK=1` makes
> a field a unit of REAL time, which is what decouples game speed from render
> rate.**"*

And it emits this, at `frametiming.c:253`:

> *"WARNING: `GETV_FPS=%d` with the synthetic clock. Every rendered frame counts
> as one video field, so **the game will run at %d/60 = %.2fx speed.** Set
> `GETV_REALCLOCK=1`... **A divider does NOT fix this.**"*

### **AT `GETV_FPS=90` THAT PRINTS `1.50x`. THE OWNER'S STOPWATCH SAID `1.487`.**
`27.04s / 18.18s = 1.487`. **A stopwatch, a fixed route, and a `printf` written
months apart agree to under one per cent.**

**`RB-04` is not an unfixed bug in a 1,399-line function reached through a patch
layer. It is the documented, expected behaviour of the default clock, it has a
named off-switch, and that off-switch is already parsed** —
`ge_config.c:836`, `key_bool_gate("GETV_REALCLOCK", ...)`, with
`gePortRealClockOn()` at `port_os.c:214`.

**This is consistent with the owner's own numbers:** `HANDOVER` records
**RB-02 (clock) 27.04s — CORRECT.** `[INFERRED]`, and it needs one run to
confirm: **`RB-02` WAS `GETV_REALCLOCK`, and it already measured correct.**
**`RB-03` (float delta, 18.18s) was then a SECOND correction applied on top of
the first — which is what a 1.5x overshoot looks like.** `182`: not to be built
on until run.

---

## §4 — WHAT IS STILL GENUINELY OPEN, AND IT IS NOT SPEED

**The real clock fixes the RATE. It does not remove the QUANTISATION.**
`speedgraphframes` stays an `s32`. At 90 Hz a rendered frame is two-thirds of a
field, so the real clock hands the sim `0, 1, 1, 0, 1, 1, ...` — **correct on
average, uneven per frame.** Mean speed is right; individual frames advance by a
whole field or by nothing.

> **THAT IS JUDDER-SHAPED, NOT SPEED-SHAPED — and the owner has already reported
> exactly that shape, twice: `96`'s *"it just feels **not ninety hertz**"*,
> logged as a fault SEPARATE from the judder.** `[INFERRED]`, `182`, **may not
> be built on.** It is written down because it predicts a specific symptom that
> a specific run can falsify.

**The `P1` fix is therefore ONE change at ONE site, not a timestep threaded
through `MoveBond`:** make the field count **fractional** — carry the remainder
instead of truncating it — so `g_GlobalTimerDelta` becomes `60.0f / actualHz`
as `P1` requires. **`ge_sim_pending_fields` is already an accumulator
(`frametiming.c:88`); it is the right place, and it is already the site that
"throws the remainder away" by its own comment at `frametiming.c:61`.**

### THE COST INPUT `168` §5 DEMANDS, NOW THAT THE SYMBOLS ARE READ
**216 refs to `g_GlobalTimerDelta`; 8 divide by it.** A fractional delta makes
every divide a divide by a number that can be **< 1**, which **amplifies**.
`bondview2.c:7678` already carries a **`VERSION_EU`-only divide-by-zero guard**
on it — evidence Rare hit this class on the one version whose delta was not 1.0.
**Those 8 sites are the review list. They are named in `132` §3 and must be
re-read in the NATIVE tree before the change, not after.**

---

## §5 — WHAT THIS DOES TO `258`

- **Stage 1 step 4 is COMPLETE.** This doc is its output.
- **Stage 4 (the clock) gets cheaper and better-defined:** it is the fractional
  accumulator at `frametiming.c:88`, plus the 8 divide sites, plus `P1`'s
  pinnable numerator (`258` §3.2) — **not surgery inside `MoveBond`.**
- **Stage 3 gains a fourth free read, and it is now the cheapest test in the
  project:** **run the fixed route with `GETV_REALCLOCK=1` at `GETV_FPS=90`.**
  No build. It confirms or kills §3 in one launch.
- **`258` §4 stage 4's gate is unchanged and now matters more:** `239` — **two
  rates, or it is not a setting.**

## §6 — NOT CLAIMED
- **NOTHING HAS BEEN RUN.** Every line here is read from source.
- `[INFERRED]` only: that `RB-02` was `GETV_REALCLOCK`; that the residual
  quantisation is what `96` reported. **Neither may be built on.**
- No claim the fractional delta is cheap — **the 8 divide sites are unread in the
  native tree.**
- The port's own warning says **`UNVERIFIED ON THIS HARDWARE`**: it was written
  on a 60 Hz panel with a harness compute-bound at ~56 fps. **It reasons; it does
  not measure.** So does this document.
