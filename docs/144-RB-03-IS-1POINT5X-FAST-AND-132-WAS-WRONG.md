# 144 — RB-03 RUNS, AND IT MAKES BOND 1.5x TOO FAST. `132` §3 IS RETRACTED.

**2026-08-24, 18:23.** The owner, on the `-FloatDelta` run: ***"felt like the
Flash lol. I'm definitely faster. It's a fun way to play but not for VR."***

---

## §1 — THE KNOB WORKS. THAT IS NOT THE PROBLEM.

```
clock: ticks=20 in 333ms -> per1000ms=60 | clk=1 gd1000=666 sgf=1 wfnf=3479
```

**`gd1000=666`. G-135-3 PASSES** — `g_GlobalTimerDelta` is the fractional delta,
two thirds of a sixtieth per frame, exactly as designed. RB-03 is plumbed
correctly and is doing what `132` specified.

**And `per1000ms=60`. THE ENGINE'S CLOCK IS STILL CORRECT.** Mission timers,
durations and every "N sixtieths" constant still keep real time.

> ### **SO THE WORLD CLOCK IS RIGHT AND THE PLAYER IS FAST. THOSE ARE DIFFERENT NUMBERS AND ONLY ONE OF THEM WAS BEING WATCHED.**

**`143` §6 named this exact outcome as the thing that would make RB-03 a fault
rather than a success, and predicted it would show as `per1000ms` moving off 60.
IT DID NOT.** The gate was watching the wrong quantity. **The wearer caught what
the instrument could not** — fourth time this project (`95`, `98`, `124`, now
this).

---

## §2 — WHY, AND IT IS `132` §3's OWN LIST

`132` §3 surveyed the 216 `g_GlobalTimerDelta` references and found **eight**
inside a `g_ClockTimer > 0` guard, **all eight divides**:

```
bondview2.c:2885   speedverta /= g_GlobalTimerDelta + g_GlobalTimerDelta
bondview2.c:6709   tank turret turn
gun.c:2335-2337    velocity += (pos - prevpos) / g_GlobalTimerDelta
gunfire.c:203-205  velocity += (pos - prevpos) / g_GlobalTimerDelta
```

**I concluded: *"a MILD fault, not a wrong rate... stale velocity for 11 ms, not
motion at two-thirds speed."* THAT IS RETRACTED.**

> **A DIVIDE BY THE DELTA SCALES INVERSELY WITH IT. `1 / 0.667 = 1.5`.**
> **The ratio the owner reported is the ratio in the arithmetic.**

**The sums were the wrong thing to check.** Every ADDITION of `k * delta` is
unchanged between the two configurations — 60 ticks x 1.0 and 90 frames x 0.667
both total 60, which is why `per1000ms` stayed at 60 and why I convinced myself
the change was safe. **Divides are not sums. They do not care that the total is
preserved; they care what the instantaneous value is**, and it changed by exactly
the factor that was felt.

**`126` RB-04 has been sitting there naming this the whole time.** It was
re-scoped to "eight named lines, do it only if RB-07 says it is visible". **RB-07
did not need to: the monitor said it.**

---

## §3 — THE STRATEGIC POINT, AND IT IS THE OWNER'S FRAMING

> ***"It's a fun way to play but not for VR."***

**RB-02 ALONE IS ALREADY THE WIN, AND IT IS UNAFFECTED BY ANY OF THIS.**

| | RB-02 | RB-02 + RB-03 |
|---|---|---|
| fps | **89.0** | 88.2 |
| `per1000ms` | **60** | 60 |
| `deltaFrames` | **0/1 alternating** | n/a |
| audio, pause, stability | **correct** | correct |
| **player speed** | **CORRECT** | **~1.5x** |
| motion smoothness within frames | stepped | smooth |

**RB-03 IS KNOB-GATED AND STAYS OFF.** `-FloatDelta` is not set by default and
nothing reaches it without being asked. **The build the owner plays is RB-02 and
it is correct**, which is exactly why `132` §1 insisted the two be separate knobs
rather than fused. **That decision paid for itself here** — a fused build would
have made the whole slice unusable and the cause unattributable.

---

## §4 — RB-04 IS NOW THE TASK, AND IT IS EIGHT LINES

**The fix is not to abandon the float delta.** It is to give those eight divides
the quantity they actually mean: **the time since the last TICK**, not the length
of one frame.

**Two shapes, and the choice needs a read before a build:**

1. **Divide by the integer `g_ClockTimer` instead**, which inside a
   `g_ClockTimer > 0` guard is 1 and restores today's behaviour exactly.
   Bit-identical to stock for those eight sites, and it keeps the smooth float
   delta everywhere else. **The conservative option and probably correct.**
2. **Accumulate the displacement across the frames since the last tick** and
   divide by the accumulated delta. More faithful, more code, and it changes feel
   in ways nobody has asked for.

**Option 1 first.** `118` §4's principle applies: leave the thing that decides
feel on the integer, and take the smoothness everywhere it is free.

**AND THE OTHER 208 REFERENCES ARE UNAFFECTED** — they are additions and they
already sum correctly. **This is genuinely eight lines.**

---

## §4.1 — CORRECTION, WRITTEN BEFORE A LINE OF RB-04 WAS BUILT

**I read where the eight lines actually live, and §2's attribution does not
survive it.** Rule 4, and caught this time before the build rather than after.

| Site | Enclosing function | Length | What it is |
|---|---|---|---|
| `bondview2.c:2885` | small pitch/clamp block | ~72 lines | **`speedverta` — vertical LOOK rate** |
| `bondview2.c:6709` | **`MoveBond`** | **1307 lines** | **tank turret turn speed** |
| `gun.c:2335-2337` | `gunFireTankShell` | 149 lines | **tank shell** muzzle velocity |
| `gunfire.c:203-205` | `gunFireTankShell` | 149 lines | **tank shell** muzzle velocity |

> ### **SIX OF THE EIGHT ARE TANK CODE. THEY CANNOT EXPLAIN BOND RUNNING FAST ON FOOT.**

**And Bond's on-foot movement is correctly scaled.** `bondview2.c:7228`,
`:7234`, `:7044` and the walk terms are all `move_offset += (...) *
g_GlobalTimerDelta` — additions, which sum to 60 units a second in **both**
configurations. **There is no unscaled per-frame movement term in the path.**

**TWO CONSEQUENCES:**

1. **"Eight lines" was wrong twice over** — six are irrelevant to the symptom and
   one of the two that might matter is inside a 1307-line function that cannot
   reasonably be `RECOMP_PATCH`ed.
2. **The remaining candidate is `speedverta` — a LOOK rate, not a walk rate.**
   `1 / 0.667 = 1.5` still applies to it exactly. **So "I'm definitely faster"
   may be describing TURN or LOOK speed rather than movement speed**, which in a
   headset is very easy to conflate.

### §4.2 — AND THE OWNER'S ANSWER RULES `speedverta` OUT AS THE CAUSE

Asked what specifically felt faster: ***"walking / running speed"*** AND
***"everything, uniformly."*** Not turning, not looking.

> **`speedverta` IS A PITCH-LOOK RATE. IT CANNOT PRODUCE "EVERYTHING, UNIFORMLY
> FASTER", AND IT CANNOT MOVE BOND ACROSS THE FLOOR.** §2's mechanism is not the
> symptom. **Two framings in a row now, `132` §3 and `144` §2, both wrong.**

### §4.3 — AND PATCHING IT IS NOT CHEAP EITHER

`bondviewUpdatePauseTransition` is 74 lines and self-contained, but the patch
headers are missing **`watch_transition_time`, `M_TAU_F`, `cosf`,
`pause_transition_time`** and the `pause_state` / `pause_target_verta` /
`pause_saved_verta` struct fields. **Porting those into `patches/structs.h` is
exactly `115`'s cross-boundary header trap** — and the function also drives the
watch pause transition, which is one of the few gates currently PASSING
(`143`: *"world stopped dead"*).

> **SO: A RISKY EDIT, TO A WORKING PATH, FOR A MECHANISM THE OWNER'S OWN
> DESCRIPTION RULES OUT.** Not written. Rule 5 and rule 4.

### §4.4 — WHAT TO DO INSTEAD, AND IT NEEDS NO BUILD AT ALL

**"Everything, uniformly faster" with a correct integer clock points at the
per-frame update rate, not at any individual rate constant.** And there is a
possibility nobody has excluded:

> ## **RB-02 MAY ALREADY BE FAST, AND NOBODY HAS CHECKED.**
>
> `143` recorded *"works good"* for the `-ViRate 90` run — **that was a
> stability judgement, not a speed comparison.** If anything in the frame path
> advances by a fixed amount per FRAME rather than per sixtieth, it is 1.5x at 90
> fps **in both configurations**, and `-FloatDelta` would only have made it
> obvious.

**THE THREE-RUN COMPARISON, SAME CORRIDOR, NO CODE:**

```powershell
.\vr.ps1 -NoXr                            # stock 60. THE REFERENCE.
.\vr.ps1 -NoXr -ViRate 90                 # RB-02
.\vr.ps1 -NoXr -ViRate 90 -FloatDelta     # RB-03
```

**Stock and RB-02 match, RB-03 fast** -> the fault is in RB-03 and the search is
for a nonlinearity that 90 delta-scaled updates produce where 60 did not.
**RB-02 ALREADY FAST vs stock** -> the fault is in RB-02, it has been there since
17:23, and it is far more serious than RB-03.

**That second outcome is the one nobody has tested for, and it is one launch.**

---

> **THE ORIGINAL §4 CONCLUSION, NOW SUPERSEDED BY §4.1-§4.4:** *Walking, turning,
> or everything?* Those point at different code and different fixes, and
> `106` §2's standing criticism of this project is building on the previous
> document's framing without checking it. **`132` §3 and `144` §2 are two such
> framings in a row. A third would be the same mistake.**

---

## §5 — WHAT TO CHECK WHEN RB-04 IS BUILT

**The instrument cannot answer this one and should not be trusted to.**
`per1000ms` stayed at 60 through a 1.5x speed fault, so a new gate is owed:

> **THE GATE IS THE PLAYER, AND IT IS A COMPARISON THE OWNER CAN MAKE IN THIRTY
> SECONDS: run the same corridor with `-ViRate 90` and with
> `-ViRate 90 -FloatDelta`. THE SAME SPEED, OR IT IS NOT FIXED.**

**And then the question RB-03 exists to answer, which has still never been
asked:** with the speed correct, **does the world look smoother with the float
delta than without it?** That is the whole reason for the task, and every run so
far has been confounded by something else.
