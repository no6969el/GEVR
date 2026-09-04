# 184 — T3 WORN IN STEREO. THE AIM SATURATES, AND `item_related` IS IMPACT-ONLY.

**2026-08-26. First aim test with two working eyes since 08-24. Tiered per `182`.**

---

## §1 — `[REPORTED]` THE WEARER, AND IT IS THE MOST USEFUL AIM REPORT THIS PROJECT HAS HAD

> *"It's only focusing on the general quadrant that you're focusing the two d
> crosshair on... I can have the gun facing all the way to the right as long as
> I have it moving the aim crosshair up on that quadrant... nothing is related to
> where you're pointing it."*

> *"Every shot lands lower than the target."*

> *"The crosshairs are in two different spaces when I open each eye. When I have
> both open, the left eye's right side of the cross outside of the circle and the
> right eye's left side of the cross are overlapping each other perfectly."*

**THAT LAST ONE IS A MEASUREMENT, NOT AN IMPRESSION** — the separation equals
exactly one crosshair width, which is a number we can solve against.

## §2 — `[MEASURED]` THE LOG SAYS THE SAME THING

| | |
|---|---|
| unclamped aim samples **saturated or off-screen** | **442 of 1,313** |
| samples at *precisely* `(316,226)` - the corner | **290** |
| samples at *precisely* `(160,120)` - rest | **377** |
| distinct values | 469 |
| screen | **320x220**, so centre is **(160,110)** |

**THE REST POSITION IS `(160,120)` AND THE CENTRE IS `(160,110)`. TEN PIXELS
LOW, CONSTANTLY.** That is the *"every shot lands lower"* report, quantified,
and it is a fixed offset - **it will NOT shrink with distance, so it is not
parallax.**

## §3 — TWO OF MY OWN CLAIMS, RETRACTED BEFORE THEY WERE BUILT ON

**(a) "THE BULLET IS READING THE CLAMPED AIM." FALSE.**
`[READ]` `ge_vr_aim.c:638`: the consumer takes `g_geVrTrueAimPx` when
`geVrClampSplitActive() && g_geVrTrueAimHave`, and `:451` publishes it BEFORE
the clamp block at `:464`. **`172`/U-16 IS CORRECT AND WORKING.**
**WHAT MISLED ME WAS A LOG LABEL.** `ge_vr_bindtest.c:889` prints
`crosshair_angle` under the word `BULLET`; that line predates U-16 and now names
the DRAWN SIGHT as though it were the shot. **RENAME IT** - it has already cost
an hour and it will cost the next reader the same.

**(b) "`-AimFromHand` ROUTES US ONTO THE OLD ESTIMATED PATH." FALSE.**
`[READ]` `ge_vr_aim.c:251`: the outer gate is `geVrAimEstimateActive()`, not
`-AimFromHand`. And `[READ]` `rt64_render_context.cpp:1524`: `aim_fwd_head` is
ALSO gated on `GE_VR_AIM_FROM_HAND`, **so the flag is REQUIRED, not a no-op.**
**The projected path (`163`) with the render frustum (`167`) IS what ran.**

## §4 — ►►►► THE CAUSE: A DIRECTION DIVIDE WITH A GUARD 37 DEGREES TOO WIDE ◄◄◄◄

`[READ]` `ge_vr_aim.c:283` and `rt64_render_context.cpp:1483`:

```c
if (g_geVrAimFwd[2] < -0.05f)   /* ~87 degrees off axis STILL PASSES */
```

**The frustum is about +-50 degrees.** Between ~50 and ~87 the divide keeps
returning finite, legal, ENORMOUS numbers. `162` P0-3(b) recorded this family
already: *"a near-edge-on gun divides by a near-zero and throws values like
ndc=(-8.5,-17.9) - twenty times off screen... the crosshair is not aimed low, it
is flung off the frame and the integrators chase it."*

**`162`'s cure was to CLAMP THE NDC to +-2. `[MEASURED]`: +-2 NDC on 320x220 IS
`(480,340)`, and 290 samples sit exactly there.**

> ## **CLAMPING AFTER A DIVIDE-BY-NEAR-ZERO IS NOT THE SAME AS BOUNDING THE ANGLE.**
> The post-divide clamp collapses a whole 37-degree band of DIFFERENT gun
> directions onto ONE screen point. **That is precisely "only the quadrant
> survives", and the wearer described it before reading any of this.**
>
> **`[INFERRED]` (counter-example search: none found in `162`, `163`, `167`):
> bound the DIRECTION to the frustum cone BEFORE projecting.** Then the edge
> behaves smoothly and monotonically instead of snapping to a corner.

## §5 — PERFECT DARK, READ AND PARTLY APPLICABLE

`[READ]` `perfect_dark_VR/port/src/../../src/game/bondgun.c:8347-8397`: PD never
divides a direction. They push **`hand->dotpos`** - the laser dot's WORLD hit
point - through `camGetWorldToScreenMtxf()`.

`[READ]` `port/vr/vr_openxr.cpp:2397`, `vrComputeCrosshairParallax` - **25 lines,
and its `100.0f` units-per-metre is already our scale.**
`[READ]` `src/game/sight.c:1864`: fed by the distance from the player to
`hand->dotpos`, defaulting to 50000 (infinity, zero parallax) when there is none.

**AND PD CONFIRMS OUR CLAMP SPLIT INDEPENDENTLY:** `bondgun.c:8473`, `crosspos2`
(the bullet aim) is *"raw position, without smoothing"* and unclamped, while the
drawn crosshair is clamped to `[3, w-4]`. **Same architecture as `172`.**

## §6 — ►► GOLDENEYE HAS THE HIT POINT. IT IS IMPACT-ONLY. ◄◄

**THE GOOD HALF, `[READ]`:**
- `patches/structs.h:1795` - `coord3d item_related` is the last member of
  `struct hand`, and `:2529` gives the patch `struct hand hands[2]`.
  **REACHABLE TODAY, NO NEW SYMBOLS.**
- `gunfire.c:1139` - `CapBeamLengthAndDecideIfRendered(..., &field_B58,
  &item_related)`, and `:1007` shows `delta = arg3 - arg2` normalised.
  **`item_related` IS the world point the shot terminates at.**
- `gunfire.c:1130` - **the game ALREADY multiplies `item_related` by
  `camGetWorldToScreenMtxf()`.** PD's idiom, in GoldenEye, already written.

> **SO `169` U-05's BLOCKER IS DISSOLVED FROM A DIRECTION NOBODY CHECKED.** It
> was recorded as *"the beam is WORLD space and `currentPlayerGetViewToWorldMtxf`
> is still unreachable"*. **We never needed view-to-world. We needed
> world-to-screen and a world point, and both are in scope.**
> **THAT IS THE FIFTH TIME (`160`, `163`, `171` §3, `180`, this). `182` §1 gains a row.**

**THE BAD HALF, AND IT LIMITS EVERYTHING ABOVE. `[READ]`** - every writer of
`item_related` is an IMPACT site:

| site | when |
|---|---|
| `chr.c:3520` | a character was hit |
| `chrprop.c:1166` | a shot terminated |
| `propobj.c:9514` | a prop was hit |

**IT IS A TRACER TARGET, NOT A CONTINUOUS LASER DOT. IT UPDATES ONLY WHEN A SHOT
LANDS.**

**AND THERE IS NO CHEAP PER-FRAME TRACE TO REPLACE IT:** `[READ]` the trace
lives inside `chraiDefaultWeaponFireHandler` (`chrprop.c:908-931`), which also
applies damage and creates explosions, and is **not in `externs.h`**.

> ### **SO THE WORLD POINT DOES NOT FIX THE SATURATION, AND I SHOULD NOT HAVE IMPLIED IT WOULD.**
> The only always-available point is `muzzle + dir * far` - **which projects
> IDENTICALLY to the direction and explodes in exactly the same way.**
> **PD KNOWS THIS**: `bondgun.c:8368` detects a stale `dotpos` and falls back to
> `muzzlepos + vrdir * 100000` with `show_laser_dot = false`.

## §7 — WHAT THIS SPLITS INTO

| | what | evidence | cost |
|---|---|---|---|
| **A** | **Bound the DIRECTION to the frustum cone before projecting** | `[INFERRED]` §4 | **SLICE. Independent of everything below, and it is the quadrant fault** |
| **B** | **The 10 px drop** | `[MEASURED]` §2 | a read - a fixed offset with a findable source |
| **C** | **The HUD shift magnitude** | `[MEASURED]` + the wearer's overlap | applied `0.1867`; `[INFERRED]` from this run's tangents the cyclopean term is `(tanR+tanL)/(tanR-tanL) = -0.1411`. **VERIFY, do not dial** |
| **D** | **U-06 parallax from the LAST IMPACT distance** | `[READ]` §6 | small, degraded but real - PD ships the staleness fallback |
| **E** | **U-05 continuous laser dot** | `[READ]` §6 - blocked | **PROJECT.** Needs a per-frame trace GoldenEye does not expose |

**DO `A` FIRST.** It is the fault the wearer actually described, it needs no
trace, and `C` cannot be judged while the crosshair is being flung off-frame.
