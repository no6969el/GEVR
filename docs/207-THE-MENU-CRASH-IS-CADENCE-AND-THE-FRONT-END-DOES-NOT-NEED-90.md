# 207 — THE MENU CRASH SURVIVES 60 Hz AND DIES AT 90. THE FRONT END DOES NOT NEED 90.

**2026-08-25. Tiers per `182`. `206`'s stack, plus one discriminating run.**

---

## §1 — THE EVIDENCE, AND ITS HONEST WEIGHT

**`[MEASURED]`, `206`: TWO crashes, IDENTICAL fault site** — `sub_GAME_7F06DEC0
+0xA1`, reading `0x284FFEE0005` and `0x27771E00005`. **Both end `0005`**: a
garbage MIPS pointer resolved against the RDRAM base, so the corruption is
GAME-SIDE DATA, not a host bug.

**`[MEASURED]` `137` §4's test, run at last:** at **`-ViRate 60`**, the same menu
navigation **did not crash.**

> ### **AND THAT IS ONE TRIAL AGAINST AN INTERMITTENT FAULT.**
> `[REPORTED]` is *"it still crashes SOMETIMES"*. **A single clean run at 60 is
> consistent with the hypothesis and does not establish it** — `133` is the
> record of this project reading one good result as a pass. **What would settle
> it: three or four more menu passes at 60, and ONE deliberate reproduction at
> 90.** The 90 arm matters more than the 60 arm: **a failure to reproduce at 90
> would falsify the whole thing.**

---

## §2 — THE MECHANISM, AND IT FITS THE OWNER'S OWN MEMORY

**`[READ]` `model.c:1447`. `sub_GAME_7F06DEC0` is the ANIMATION JOINT READER, and
`+0xA1` lands on its first dereferences:**

```c
width     = anim->unk06;                                 // the ANIMATION
bitoffset = skeleton->Joints[jointnum].mtxA * width;     // the SKELETON
```

**`anim`, `bitstream` and `skeleton` all come straight off the model**
(`model->anim`, `model->unk34`, `model->obj->Skeleton` — `model.c:1505`).
**A wild pointer at a tiny offset is one of those being STALE OR FREED while the
model is still being ticked.**

**AND RB-02 IS THE MULTIPLIER.** `chrTick` and `propsTick` run from the sim, and
`131` made the sim run at 90 instead of 60 — **50% more ticks against exactly the
same loading work.** A pre-existing race between "tick this model" and "swap this
model's data" would surface far more often, without RB-02 having introduced it.

> **`[REPORTED]` the owner recalled an earlier session blaming *"the music
> changing... trying to load the different tracks."* THAT INSTINCT IS BETTER THAN
> `137` §4's version of it.** The suspect there was a specific audio SPIN, which
> `206` §2 falsified. **But "menu transitions swap loaded data" is the right
> family, and the model animation is another member of it.**

---

## §3 — THE FIX WORTH BUILDING: THE FRONT END DOES NOT NEED 90 Hz

**90 Hz buys comfort while you are LOOKING AROUND A WORLD. The front end is a
2D menu on a virtual screen (`175`), and `[MEASURED]` it renders with
`stereo=0`, `inLevel=0`.** **There is nothing in the front end for 90 Hz to make
smoother.**

**AND THE SIGNAL ALREADY EXISTS AND IS ALREADY LOGGED:** `VRGATE/s: ...
inLevel=0 | (world_camera() gate - front end, cutscene)`.

**THE SLICE:** pace the sim at 60 in the front end and 90 in a level.

### THE HAZARDS, NAMED BEFORE ANYTHING IS WRITTEN

1. **`[READ]` `get_vi_rate()` CACHES IN A `static`** (`events.cpp:128`) — it is
   read ONCE. Making it live is the first change, and **the static is currently
   what guarantees the rate cannot change under the accumulator.**
2. **`131` §4 AND `130`:** `workbench_theboy.c:659`'s `60 / speedgraphframes` was
   **a live divide by zero** once `deltaFrames` could be 0, and the audio divisor
   is derived from the rate. **A rate that changes at runtime re-opens both.**
3. **RT64 IS TOLD THE RATE TOO** (`131` §4) — *"it was also feeding RT64 the wrong
   rate, which would have re-manufactured the very frames Route B deletes."*
4. ►► **SO SWITCH ONLY AT A LEVEL BOUNDARY, NEVER MID-FRAME.** The game is
   already re-initialising there, which is the one moment the timing state can be
   rebuilt safely. **A rate that changes while a level is running is a different,
   much riskier feature and is NOT what this proposes.**
5. **`118`'s DE-RISKER APPLIES:** this is a timing change, so it gets `-NoXr`
   FIRST. **`151` §4 is the record of a frame-loop change going straight to a
   headset and costing two reboots.**

**KNOB: `-ViRateMenu 60` (or `0` to disable and keep one rate everywhere).**
**GATE: navigate the menus twenty times at the new default. Then `T11`'s
regression check, because this touches the thing Route B was built for.**

---

## §3b — ►►►► BOTH QUICK ROUTES ARE CLOSED, AND `131` CLOSED ONE IN ADVANCE ◄◄◄◄

**§1's evidence firmed up before either was attempted. `[MEASURED]`: THREE
consecutive runs at `-ViRate 60` with the owner deliberately MASHING through the
menus — the original `137` §4 trigger — and no crash, against TWO crashes at 90
the same evening while he was *taking his time*. `[REPORTED]`: *"It should have
absolutely crashed."* The asymmetry is stronger than a formal A/B and §1's
caveat is discharged.**

### ROUTE 1 — DYNAMIC VI RATE. **BLOCKED BY `131`, IN A COMMENT WRITTEN FOR THIS.**

`[READ]` `events.cpp:153`:

> *"docs\131. Read ONCE, not per iteration: both expressions below are ABSOLUTE,
> derived from `total_vis` and `get_start()`, so **changing the divisor mid-run
> would retroactively reinterpret every VI counted so far**."*

**THE `static` IN `get_vi_rate()` IS NOT AN OVERSIGHT TO BE REMOVED. IT IS THE
GUARANTEE.** Switching the rate live would rewrite the meaning of every VI
already counted — **a fast-forward or a stall, not a pacing change.**
**So the slice §3 proposed does not exist as written.** The honest version is
**REBASE THE TIMEBASE AT THE TRANSITION** — reset `get_start()` and `total_vis`
so the new rate begins a fresh epoch — **and that touches the machinery `130`
(audio divisor) and `132` §2.2 (pause detection) were built on.** A real slice,
with real gates, not a knob.

### ROUTE 2 — GUARD THE POINTER IN A PATCH. **BLOCKED BY `168` §5's GREP.**

`[READ]`, the mandatory grep, run before a line was written:

| symbol | `externs.h` | `structs.h` |
|---|---|---|
| `process_02_position` | **0** | 0 |
| `modelAnimReadBitsAsU16Angle` | **0** | 0 |
| `ModelRoData_GroupRecord` | **0** | **0** |
| `ModelSkeleton` / `ModelAnimation` / `ModelNode` | 0 | 3 / 4 / 9 |

**The structs are mostly reachable; the FUNCTIONS are not.** Reproducing
`process_02_position` needs at least two unreachable calls. **`157` withdrew a
slice for exactly this and `168` §5 was written from it.** **THE GREP COST TWO
MINUTES AND SAVED THE SLICE.**

---

## §3c — WHAT IS ACTUALLY AVAILABLE

1. **THE WORKAROUND, AVAILABLE NOW, ZERO RISK:** **`-ViRate 60` for menu-heavy
   sessions, `90` for playing.** `151` already established the owner's policy that
   *"every launch names its own pacing"*, so this fits what exists rather than
   fighting it. **It costs the judder fix while it is on, and only while it is.**
2. **THE REAL FIX: ROUTE 1's REBASE**, designed properly, `-NoXr` first (`118`),
   gated on `130`'s audio and `132` §2.2's pause, and **only ever switching at a
   level boundary.**
3. **THE UPSTREAM QUESTION, STILL UNASKED:** is there a LOADING flag the patch
   can already see? **If `chrTick` can be skipped while a load is in flight, that
   is smaller than either route** — and it is a grep, not a build.

---

## §4 — WHAT IS OWED, IN ORDER

1. **CONFIRM §1** — three or four more menu passes at `-ViRate 60`, and **one
   deliberate reproduction at 90.** Cheap, no build, and it is the difference
   between a hypothesis and a finding.
2. **THEN THE SLICE** (§3), `-NoXr` first.
3. **THE STOCK QUESTION IS STILL OPEN AND IS NOW SECONDARY:** if it reproduces at
   `-ViRate 60` eventually, this is stock GoldenEye's own race and belongs with
   `39` — **but the front-end pacing fix would still be worth having.**

> **AND NOTE WHAT THIS DOES NOT SAY: RB-02 IS NOT AT FAULT.** `147` closed the
> judder line with it and the owner called that build *"totally playable and
> enjoyable."* **This is a race RB-02 EXPOSED, in a place that never needed the
> extra frames.**

**NOTHING STAGED. THE COMMIT IS THE OWNER'S.**
