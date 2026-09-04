# 135 — RB-02c AND RB-03a. ONE INSTRUMENT, BUILT ON WHAT IS PROVEN TO WORK.

**2026-08-24. Written, not compiled.** `134` left RB-03 with no gate that could
fire and one wearer report — *"I felt like I was running faster in the second
run"* — that nothing could confirm or deny. **Both are now answerable from the
log, and RB-03a needs no stopwatch after all.**

---

## §1 — WHY A SECOND INSTRUMENT INSTEAD OF FIXING THE FIRST

`119`'s timebase line lives in `viSetFovY` (`ge_vr_bindtest.c`). On the RB-02 runs:

- **it printed ONCE**, at line 13 of a 50,974-line log;
- **its own once-only MARKER printed ZERO times in the same run.**

**Those two facts are not coherent** — the marker sits above the line that did
print. **`121` already spent two hours on that block and did not settle it.**

> ### **SO THIS DOES NOT DEBUG IT AGAIN.** `48` rule 9. Three things are PROVEN
> ### to work on the 17:23 build, and the instrument is rebuilt on those.

**1. `waitForNextFrame` RUNS EVERY GAMEPLAY FRAME.** It is called from the
patched `bossMainloop`'s main loop, and the accumulator inside it took the sim
from **59.3 to 87.1 fps**. It cannot have done that without running.

**2. FILE-SCOPE GLOBALS IN `ge_vr_route_b.c` PERSIST AND INCREMENT CORRECTLY.**
`g_geVrTickAccum` is the proof, by the same argument. **Not function statics** —
`100`'s trap, and the likeliest cause of the block above.

**3. THE HAND-ROLLED EMITTER WORKS. 950 `6dof-game` lines went out through
`recomp_puts` in one log.**

### AND THAT THIRD POINT EXPLAINS `sgf=` COMPLETELY

**`100` found that `recomp_printf` carries its FIRST call and then stops.** The
`[trace] retrace ... sgf=` line uses `recomp_printf`.

> **It printed ONE time in one run and ZERO in the other. It was never going to
> be a gate, and `131` §5 named it as THE gate.** Not a new fault — a documented
> one, five documents old, that I did not check against before writing the gate.

---

## §2 — THE LINE

```
[gevr] tick: f=90 ms=1000 | clkSum=60 gdSum1000=60000 | gd1000=667 [667..667] delta [0..1] | rate=90 fd=1
```

Emitted once per 90 frames from `waitForNextFrame`, **on the stock path too** —
so `.\vr.ps1 -NoXr` with no knob produces a control line from the same code.
**RB-03a compares three configurations, not two.**

### G-135-1 — IS THE ACCUMULATOR RUNNING? (RB-02's real gate, at last)

**`delta [0..1]`** — the tick count producing 0s *and* 1s. **Flat `[1..1]` means
it is not running.** This is what `sgf=` was supposed to say.

### G-135-3 — IS RB-03 RUNNING?

**`gd1000=667` steady** with `-FloatDelta`; **`1000` flat** without. That is the
whole of RB-03's evidence and it is a ten-second read.

### G-135-2 — IS THE GAME RUNNING AT THE RIGHT SPEED?

> ## **`clkSum` MUST BE ~60 AND `gdSum1000` MUST BE ~60000 PER 1000 ms, IN EVERY CONFIGURATION.**

**Those two are the quantities the entire engine integrates against** — 152
references to the integer, 217 to the float. Summed over a real-time window they
*are* the game's speed, and nothing else is.

- **Both hold with and without `-FloatDelta`** -> **the game speed is correct**
  and *"felt faster"* is perception. `48` rule 3, which this project has broken
  repeatedly including by its own author (`124`).
- **`gdSum1000` differs between the two runs** -> **that is the bug, and it is
  located** rather than suspected.

**This replaces `126` RB-03a's stopwatch entirely.** A stopwatch on a corridor
measures one traverse with human reaction time at both ends; this measures every
frame of the session against the CPU counter. **It is strictly better and it was
available all along.**

### EXPECT ~60.4, NOT EXACTLY 60 — AND IT IS PRE-EXISTING

`frametiming.c`'s 775875 counts per sixtieth implies **60.42 Hz**, not 60, against
the runtime's `counter_per_ms` of 46,875. **At stock the retrace pins the loop to
60 and the discrepancy never shows; under Route B the busy-wait is subordinate,
so the accumulator can deliver 60.4 ticks a second.**

**That is a real ~0.7% fast, it is inherited from the stock timebase rather than
introduced by RB-02, and it is IDENTICAL with and without `-FloatDelta` — so it
cannot explain a difference between the two runs.** Noted so nobody reads it as
the smoking gun. If it ever matters, the fix is one constant.

---

## §3 — THE ROUND OF TESTING THIS BUYS

**Three launches from one build. All `-NoXr`, no headset, no reboot risk.**

```powershell
.\build.ps1
.\vr.ps1 -NoXr                            # CONTROL. rate=60 fd=0
.\vr.ps1 -NoXr -ViRate 90                 # RB-02.   rate=90 fd=0
.\vr.ps1 -NoXr -ViRate 90 -FloatDelta     # RB-03.   rate=90 fd=1
```

**Get into a level on each** — the instrument is in the main loop, so a menu-only
run measures the menu. **Play a similar amount each time**, and if you can, walk
the same stretch, because §2's sums are the thing that answers the speed
question.

| | expect `delta` | expect `gd1000` | expect `clkSum` / `gdSum1000` per ~1000 ms |
|---|---|---|---|
| control | `[1..1]` | `1000` | **~60 / ~60000** |
| `-ViRate 90` | **`[0..1]`** | `1000` | **~60 / ~60000** |
| `+ -FloatDelta` | **`[0..1]`** | **`667`** | **~60 / ~60000** |

> **THE RIGHT-HAND COLUMN IS THE SAME IN ALL THREE ROWS, AND THAT IS THE POINT.
> If it is not, the game speed changed and that outranks everything else in
> Route B.**

**Then say done and the logs can be read directly.** `133` is why nobody should
report "working" from feel alone again, and `134` is why nobody should report it
from a gate without checking the gate can fire.
