# 277 — THE `239` GATE IS MET. AND `RB-04` WAS ALWAYS TWO FAULTS, NOT ONE.

**2026-08-30n. `276`'s SHAPE 3 was BUILT and RUN for the first time — seven arms, one build,
one binary.** `[MEASURED]` from the game, not from source and not from a harness.
**`276` §5 said the `239` gate was NOT met. IT IS MET NOW, for the term it was written about.**

> ## THE ONE-LINE RESULT
> **`GETV_SIMHZ=query` at 90 Hz: `fps 90`, `speedgraph 60/s`, `delta 0.6667`. The world runs at
> retail speed while the renderer runs at ninety.** Worn and confirmed by the session lead.
> **AND THE SAME RUNS PROVED THE FIX IS ONLY HALF OF `RB-04`:** Bond's own walk is not
> delta-scaled, so it is untouched by the term and still runs **1.463x** too fast at 90 Hz.

---

## §1 — THE BUILD

`goldeneye.exe` **2026-08-30 20:05:55**, 18,017,350 bytes (previous: 14:42, 18,014,778).
`build_276_simhz.log`: **165 game objects, 234 assets, 40 audio, 58 port, 0 failed.**
**`grep -a GETV_SIMHZ goldeneye.exe` -> 2 hits.** `133`'s gate met: the term is in the binary,
so a null result would have been a result and not an absence.

**Every arm below ran on that one binary.** All seven logs are timestamped after it. Every log
carries its terminating `[getv] game_exit requested` (`262` §5), and every clock window quoted
sits after the `lvlStageLoad` boot mark at line 99 — `273` §1's tail trap does not apply.

## §2 — THE FOUR GATE ARMS, ON FACILITY (`GETV_STAGE=34`)

`[MEASURED]`, first window of each run discarded as boot transient.

| arm | banner | `fps` | `speedgraph` | `g_GlobalTimer` | `simhz` | windows |
|---|---|---|---|---|---|---|
| **A** — 60 Hz, term on | `SHAPE 3 ON ... 60 Hz (QUERIED) = 1.000000` | 60 | **60/s** | 60/s | `on delta 1.0000` | 54 |
| **B** — 90 Hz, term on | `SHAPE 3 ON ... 90 Hz (QUERIED) = 0.666667` | **90** | **60/s** | **60/s** | `on delta 0.6667` | 32 |
| **C** — 90 Hz, term off | *(none — correct)* | 90 | **90/s** | 90/s | `OFF delta 1.0000` | 51 |
| **D** — refusal, `GETV_REALCLOCK=1` | `CONTAMINATED -- GETV_REALCLOCK=1 ...` | — | — | — | term OFF | — |
| **D2** — refusal, pin 60 vs pace 90 | `SHAPE 3 ON (PINNED)` **then** `CONTAMINATED -- pinned to 60 Hz but ge_pace_framerate is 90` | 90 | 90/s | 90/s | `on delta 1.0000` | 39 |

**`273` §7.1's gate holds in all of them:** zero `simulation held to` lines, `props
interpolated 0`, `simdiv 1` in every window. **`268`'s divider did not run in any arm**, so the
arms are comparable to each other and to `274`'s.

**ARM C IS THE ONE THAT EARNS ITS PLACE.** With the knob unset the term is invisible —
no banner, `simhz OFF`, and a full `speedgraph 90/s`. **`48`'s one-behaviour-change holds and
`276`'s default-OFF claim is now measured rather than argued from `#ifdef` placement.**

**BOTH REFUSALS FIRE AND NAME THEMSELVES (rule `17`, `15`).** D proves the `GETV_REALCLOCK`
interlock; D2 proves the pin check and **honours the pin while declaring its own numbers void**,
which is the designed behaviour and not a failure. `274` §7's owed `GETV_REALCLOCK` gate is paid
from the other side.

## §3 — THE `239` PREDICTIONS, SCORED

`RUN-SHEET-276` §0, unedited, per its own instruction.

| # | prediction | result |
|---|---|---|
| 1 | `speedgraph 60/s` at both rates | **TRUE** — A 60/s, B 60/s |
| 2 | `fps` still reads 90 in the 90 Hz arm | **TRUE** — 90, min 89 |
| 3 | `g_GlobalTimer 60/s` in both | **TRUE** |
| 4 | the stopwatch reads `18.2 s`, not `27.0` | **VOID — THE PREDICTION WAS UNMEASURABLE AND ITS TWO FIGURES WERE INVERTED. §6.1** |
| 5 | `simhz on delta 0.6667` / `1.0000` | **TRUE**, verbatim |

**NO FALSIFIER FIRED.** No stray `CONTAMINATED`, no `simulation held to`, no non-zero `props
interpolated`, `fps` did not fall to 60 in arm B, and the banner is present in every arm that
should have one and absent from the one that should not.

## §4 — THE WEAR RESULT, AND IT IS THE HEADLINE

**Three further arms on DAM (`GETV_STAGE=33`), same route, same weapon, no shooting.**
`HANDOVER` §5: a wear report outranks a log.

| arm | cap | term | route time | session lead's report |
|---|---|---|---|---|
| **E** | 90 Hz | ON | **14.32 s** | *"everything was fine"* |
| **F** | 90 Hz | OFF | **14.24 s** | *"everything was moving faster except bond"* |
| **G** | 60 Hz | ON | **20.94 s** | *"not as smooth as before"*, **"everything seemed in sync"** |

> ### **E vs F: THE WORLD CHANGES SPEED AND BOND DOES NOT. THAT IS THE TERM, SEEN.**
> `speedgraph` 60/s in E against 90/s in F is the same fact in the instrument.

> ### **G vs E: `20.94 / 14.32 = 1.463`. BOND IS 1.46x TOO FAST AT 90 Hz WITH THE TERM ON.**
> Stopwatch error on a ~14 s route is about 2%; **1.463 is 90/60 within it**, and it agrees with
> the `1.487` measured on 2026-08-24 on a different build and a different route (`145`).

**E vs F is `1.006` — Bond is invariant across the term to within the stopwatch.**

## §5 — `RB-04` IS TWO FAULTS. ONE IS FIXED AND ONE IS NOT.

**THE PROJECT HAS BEEN TREATING "the game runs 1.5x fast at 90 Hz" AS ONE FAULT. IT IS TWO,
WITH DIFFERENT MECHANISMS, AND ONLY ONE OF THEM HAS A DELTA IN IT.**

1. **THE DELTA-SCALED WORLD — FIXED BY SHAPE 3.** Truck, tank, tank turret, thrown objects,
   launch velocity, shell casings, front-end cast: the 44 `/ g_GlobalTimerDelta` sites `145` §1
   enumerated. These consume `g_GlobalTimerDelta`, shape 3 makes it `0.6667` at 90 Hz, and they
   now run at retail speed. **`[MEASURED]` arm B/E, and worn in E vs F.**
2. **BOND'S WALK — UNTOUCHED, AND IT WAS NEVER IN SCOPE.** `145` §2, from source:
   `move_offset` takes the raw error term at `bondview2.c:7237` and `swayoffset` advances by
   `sp240 * error` at `:7411`, where **`sp240` is a collision ratio, not a time. There is no
   timestep in that loop.** Its convergence is counted in FRAMES. **Shape 3 changes the DELTA;
   it does not change the TICK COUNT**, and `MoveBond` runs once per rendered frame under
   `GETV_SIMDIV=1`. **So Bond scales with the render rate no matter what the delta says.**
   `[MEASURED]` here for the first time in the NATIVE port: `1.463`.

> ### **THE CONSEQUENCE, STATED PLAINLY: AT 90 Hz WITH THE TERM ON, THE WORLD IS CORRECT AND
> ### BOND IS 1.46x FAST. THAT IS AN INTERNAL MISMATCH THAT DID NOT EXIST BEFORE THE FIX.**
> With the term OFF, Bond and the world were **both** ~1.5x — wrong, but *consistent*. Turning
> the term on corrects one population and not the other. **`[REPORTED]` the session lead did not
> perceive the mismatch in arm E** — *"everything was fine"* — and reported arm G at 60 Hz as
> *"everything seemed in sync"*, which is what a run with nothing to mismatch feels like.
> **A mismatch that is measured and NOT perceived is exactly the class of fault that resurfaces
> in a headset weeks later as "something feels off" and costs a session to re-find.**
> It is recorded here so that it cannot.

### 5.1 — THE THREE OPTIONS AT 90 Hz, AND THE CHOICE IS THE OWNER'S
| | world | Bond | internally consistent? |
|---|---|---|---|
| term OFF (what shipped before) | 1.5x | 1.46x | **yes** — uniformly fast |
| **term ON (today)** | **1x** | **1.46x** | **no** |
| term ON + a timestep in `MoveBond` | 1x | 1x | yes — **NOT WRITTEN** |

**THE THIRD ROW IS `126`'s PARKED `RB-04` ITEM AND IT IS PARKED FOR A REASON:** a timestep
inside `MoveBond` is 1,307 lines and **changes movement feel**, and `118` §4 says leave the
thing that decides feel alone. **THIS IS A GAME-DESIGN DECISION UNDER `00-STATE` §1 RULE 3'S
"ASK FIRST" COLUMN — NOT A BUGFIX, AND NOT TO BE STARTED WITHOUT THE OWNER'S CALL.**

### 5.2 — `145` §3'S OPEN QUESTION NOW HAS A CANDIDATE ANSWER. `[INFERRED]`, NOT MEASURED.
`145` §3 named one fact it could not explain: *"if this loop simply runs per frame, RB-02 should
be 1.5x too — and it is not"* (RB-02 measured 27.04 s, correct). **G vs E establishes that
`MoveBond` DOES scale with the render rate in the native port.** The candidate: **RB-02 rendered
90 and ticked the simulation at 60**, so `MoveBond` ran 60 times a second there. That is the
shape of `268`'s divider. **NOT ESTABLISHED — the recomp is a different tree and nobody has
counted `MoveBond` executions in either.** `145` §3's measurement is still the one that closes
it: **one counter, `MoveBond` executions per second.** It remains unwritten.

## §6 — RETRACTIONS. BOTH MINE, BOTH THIS SESSION.

### 6.1 — `275` §7 / `RUN-SHEET-276` §0 PREDICTION 4 HAS ITS TWO FIGURES INVERTED.
`145`'s table: stock **29.48 s** (truck hesitation), RB-02 **27.04 s — CORRECT**, RB-03
**18.18 s — exactly 1.5x too fast**. **A faster Bond finishes sooner: 27.04 is the correct-speed
figure and 18.18 is the fast one**, and `126`, `257` §140-143 and `274` §2.1 all use them that
way. `275` §7 wrote *"reads `18.2 s`, not `27.0`"* — backwards — and the run sheet inherited it
verbatim. **It was then handed to the session lead a THIRD time in this session's arm-B block.**
**The prediction is not edited (the sheet forbids it); it is retracted here.**

### 6.2 — AND THE WALKING ROUTE COULD NEVER HAVE MEASURED THIS FIX AT ALL.
Worse than inverted: **unmeasurable.** The route is timed by Bond, Bond has no delta in him, and
both 90 Hz arms render 90 frames a second — so E and F were **always** going to come out equal,
whatever the term did. **I predicted the E/F ratio would be 1.5. It is 1.006.** `145` §1 and §2
already said why and I cited `145`'s numbers without reading its mechanism. **A number quoted
from a doc whose method was not read is the same error as `274` §5's grep-for-a-guard** (`275`
§1) — the third instance of this shape in three sessions.
**THE RIGHT INSTRUMENT WAS THE ONE THE SESSION LEAD USED UNPROMPTED: WATCH THE TRUCK.**

## §7 — THE ROUTE, RECORDED. IT HAS NEVER BEEN WRITTEN DOWN BEFORE.
`145` says only *"a run from the level start to the barrels"* and **names no level.** Three
sessions have since reconstructed it from memory. **From now on:**

> **THE `RB-04` ROUTE — DAM, `GETV_STAGE=33` (`LEVELID_DAM`, `bondconstants.h:1763`).**
> Level start to the barrels. Same weapon, no shooting, do not stop for the truck.
> **BASELINE, 2026-08-30n, this binary: 60 Hz `20.94 s` · 90 Hz `14.32 s`.**
> **The 2026-08-24 figures (29.48 / 27.04 / 18.18) are a DIFFERENT ROUTE ON A DIFFERENT BUILD
> and are NOT comparable in absolute terms — only their RATIO transfers.**

## §8 — `[REPORTED]` THE INTRO SKIP KILLS THE AUDIO, AND THERE IS A NAMED CANDIDATE
**Session lead, 2026-08-30n:** *"if I skip the intro it will make the sound off, but if I let
everything load its perfect."* **This is the first NORMAL-BOOT reproduction of `269`'s silence,
which until now only existed under the `GETV_MENU` harness.**

`[INFERRED]` from source, **not measured**: `fileValidateSaves()` has exactly two call sites —
`boss`'s, gated on `g_StageNum != LEVELID_TITLE` (direct-to-level only), and **`front.c:1461`,
the last line of the legal-screen init**. `00-STATE` §6 already records that **skipping any
intro video goes straight to the menu**, which would mean that init never runs. Without it
`saves[]` stays BSS zeros; `file2.c:519-530` hands a zeroed slot back for any folder; and
`fileLoadSettingsForFolder()` at **`file2.c:1413-1414`** applies `music_vol = 0` and
`sfx_vol = 0` over the correct defaults. **`269` measured exactly this under the harness:
`g_vol 32767 -> 0`, 3 runs of 3, every folder.**

**TWO FALSIFIERS, BOTH FREE, BOTH ON THE EXISTING BINARY:**
1. **A skipped-intro boot must print NO `lg:7-fileValidateSaves` boot mark.** If it prints one,
   this account is dead.
2. **THE CROSSHAIR AND AMMO COUNTER MUST BE MISSING IN THAT SAME SESSION** — they die from the
   same zeros (`initmenus.c:113-121`). **If the sound is off and the crosshair is there, STOP:
   the mechanism is something else.**

**ON THE TWO OPTIONS THE SESSION LEAD RAISED:** *"prevent the player from skipping"* is not
available — **nothing here is a race and nothing needs time to settle**, so blocking the skip
would not reliably fix it, and it fails the spirit test outright (a 1997 player notices losing
the skip; nobody notices a save-validation call happening earlier). **Fix it in the source,
rule `14`** — but **NOT before the two falsifiers above run**, because `fileValidateSaves()` is
also where `00-STATE` §3's folder-3 save loss lives (the 4-folders-through-a-5-slot rotation,
`file2.c:670`) and that must not be disturbed blind.

## §9 — WHAT IS OWED
- **`145` §3's counter: `MoveBond` executions per second.** The one measurement that closes
  both the RB-02 anomaly and the scope of §5's row 3. Still unwritten.
- **The two hoist sites have STILL never been driven** (`RUN-SHEET-276`, last section):
  the tank turret (`bondview2.c:7330`) on Runway or Streets, and a grenade or spent rocket
  sliding to rest (`propobj.c:5065`). **Neither is exercised by Dam or by a vent.** If either
  misbehaves at 90 Hz the hoist is the suspect and `g_GlobalTimerFieldDelta` is the term to print.
- **§8's two falsifiers**, before any audio fix is proposed.
- **The `239` gate is MET for the delta term and NOT MET for Bond's walk** — and the second half
  was never in `239`'s scope. It is a new item, not a failure of this one.
