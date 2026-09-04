# 71 — B1 FIXED, WORN AND CONFIRMED. And what the fix revealed underneath.

**2026-08-23, ~15:00. The fix from `70`, built, measured and worn.**

---

## THE GATE, PASSED

Written in `00-START-HERE` before any of this session's code:

```
Pass: -113 px +/- 5 in the far band, right eye further LEFT
```

Measured on `-Flat`, default offset, far band y=150-400:

```
                     BEFORE          AFTER
disparity            0 px            -117 px      <- gate: -113 +/- 5
correlation at peak  1.0000 @ dx=0   0.9768 @ dx=-117
correlation at dx=0  1.0000          0.3287
mean|L-R|            0.0006          16.5209
```

**A build that still shared the descriptor slot could not have passed this.**

## WORN — reported from the headset

| | |
|---|---|
| **Depth** | **PRESENT.** "There does seem to be depth and the images are fused" |
| **The doubling** | **GONE.** "It seems to align fairly well" |
| **The gun** | **ONE GUN.** Was visibly two since 3f-3 |

**`65` predicted all three from one cause** — two identical images submitted with
two different eye poses cannot fuse, so everything doubled. Fix the images and
the doubling goes. **It did.**

**Everything in `00-START-HERE`'s "the viewmodel contradicts the docs" section
is now closed by observation, not by argument.**

---

## WHAT THE FIX REVEALED — two new open items

Both were invisible while there was no stereo to look at.

### O1 — SCALE IS WRONG. The player and the viewmodel read enormous.

> *"My arms and my perspective are comically large."*
> *"The arm and gun size is very large in comparison to the people and
> surroundings."*

**This is `16`'s open question arriving for the first time with real stereo to
judge it by.** `16` derived ~100 units/metre from Bond's eye height and called
it, in its own words, **"a derivation, not a measurement"**, and wrote its own
falsification: *"If it looks like three metres or three centimetres, the
derivation is wrong."*

**It has now been looked at through working stereo, and it is wrong.**

**Two separable things, and they must not be conflated:**

1. **World scale** — `GE_VR_UNITS_PER_METRE` drives the IPD *and* head
   translation. A world that reads too LARGE means the in-game IPD is too SMALL
   relative to it, which means units/metre is too LOW. Sweep it UP.
2. **Viewmodel scale relative to the world** — the arm and gun being oversized
   *compared to people and surroundings* is a ratio inside the game's own
   rendering, and **no units/metre value can fix a ratio.** If the world comes
   right and the gun is still huge, it is the viewmodel's own scale and its own
   slice.

**The test, one launch each, no code — `00-START-HERE` already lists it:**

```powershell
.\vr.ps1 -UnitsPerMetre 150     # world reads SMALLER / player smaller
.\vr.ps1 -UnitsPerMetre 200
.\vr.ps1 -UnitsPerMetre 50      # world reads LARGER - the wrong direction, as a control
```

**Read `eye sep` from `gevr.log` at each.** At 100 u/m it measured 6.33 units
for a 63.3 mm IPD (`36`). That is correct *by construction* — so if the world
still reads wrong at a correct IPD, **the units/metre derivation itself is what
is wrong**, which is exactly what `16` asked someone to check.

**`16`'s own three independent settling methods still stand and are now
usable for the first time:** the `eye sep` log line, a physical crouch or jump
against a known in-game height, and **a doorway** — whichever
`-UnitsPerMetre` makes one feel like a doorway *is* the measurement `16` asked
for. **Record it in `16` when it is found.**

### O2 — JUDDER. `26` predicted it; it has now appeared.

> *"It judders and is not running as smooth as it needs to."*

**`26` predicted judder from `xrWaitFrame` owning the cadence, and
`00-START-HERE` has carried "It has not appeared" ever since.** That line is now
false and must be corrected.

**Do not guess at this.** What is already known and must be read first:

- **The VI clock is 60 and the display period is 90** — `60`, `63`. The game
  produces 60 workloads/sec; the headset wants 90. Interpolation covers the gap.
- **`rr_option: "Manual"` / `rr_manual_value: 90`** is set by hand and does NOT
  come from the headset. `49` established **the headset's rate was never
  queried** — `XrFrameState::predictedDisplayPeriod` now prints it, and it is
  90. It works only because the manual value happens to match.
- **`12` §5 deferred the frame-pacing interlock.** This is that debt arriving.
- **`-ResScale 0.25` delayed the B2 freeze by ~8 seconds** (`64`), so this
  pipeline is demonstrably load-sensitive.

**First measurements, before any theory:**

1. `[gevr-xr] frame budget: runtime display period 11.11 ms (90.0 Hz) | our
   frame N ms` — already logged every second. **Read it. If "our frame"
   exceeds 11.11 ms, we are missing the compositor's deadline** and that is the
   judder, full stop.
2. `[gevr-xr] stage ms: waitFrame | locate | waitForGpu | record | execute |
   endFrame` — also already logged. **Whichever stage is large is the answer.**
3. Only then consider `rr_option`, `-ResScale`, or the interlock.

**CORRECTED 2026-08-23, `72`. THEY HAVE NOW BEEN READ, AND STEPS 1 AND 2 ABOVE
ARE ANSWERED.** Over 516 one-second samples of the worn session: the runtime
budget is 11.11 ms, our frame time is a **median of 10.23 ms**, and **exactly
one** sample exceeded the budget. `waitFrame` is ~8.9 ms of it -- we sit
**blocked in `xrWaitFrame` for ~87% of every frame** -- while record, execute
and endFrame together cost ~0.3 ms and `waitForGpu` is **0.00**.

**So the judder is NOT a submit-stage overrun, and step 3's `rr_option` /
`-ResScale` / interlock list is not where to start either.** But `72` also
records the limit that matters: **every one of those numbers is a MEAN over ~90
frames, and a mean cannot see a hitch.** Read `72` before acting on any of it.

---

## STILL OPEN, unchanged by this fix

| | |
|---|---|
| **B2 / `-Sbs`** | The freeze is worked around, not fixed. `-NoSbs` reproduces it. `65` |
| **The teardown crash** | 100% reproducible, `threadPresent` -> `VIRenderer::render` -> `setSRV`. `64` |
| **One eye distorted / menus zoomed** | The XR-only per-eye present pass, `25`'s blit bug. `65` |
| **Decoupled hand aim** | Not started. The pose arrives and the firing path is known. `66` Track B |
| **`-NoXr` regression check** | **NOT RE-RUN since the fix.** The path that must never break. Run it |

## The one thing to do before trusting any of this

**`.\vr.ps1 -NoXr`, play a level, quit to menu.** The fix touches `VIRenderer`,
which every non-VR present also uses. `descriptorSetIndex` defaults to 0 and no
non-VR caller sets it, so the path is unchanged by construction — **but that is
an argument, and this project has been wrong thirteen times with arguments.**
