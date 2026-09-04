# 190 — `G-A1` PASSED. THE AIM FOLLOWS THE HAND. AND THE TWO THINGS THE WEARER SAW BESIDE IT ARE BOTH EXPLAINED.

**2026-08-25. Tiers per `182`. `[REPORTED]` throughout is the wearer, verbatim.**

---

## §1 — ►►►► `G-A1` PASSES. BOTH HALVES. ◄◄◄◄

> ### `[REPORTED]`: ***"The target followed my hand direction."***

**AGAINST THE `[REPORTED]` BASELINE THIS PROJECT HAS BEEN CARRYING SINCE `184`:**
*"nothing is related to where you're pointing it... it's only focusing on the
general quadrant."*

**THE QUADRANT IS GONE.** `184` §4's mechanism — a 37-degree band of different gun
directions collapsing onto one screen point — was `[INFERRED]`, was confirmed
`[MEASURED]` by `187`, was fixed by `188`, and is now `[REPORTED]` cured by the
person who first named it. **That is the full chain `182` asks for, in four
documents.**

**AND THE SECOND HALF OF THE GATE, WHICH IS THE ONE THAT COULD HAVE FAILED
QUIETLY:** `[REPORTED]`, on a level horizontal sweep, the crosshair comes to rest
at **the MIDDLE of the right edge** — the vertical axis stays where it was left.
**THE TWO AXES SATURATE INDEPENDENTLY.** `188` §1 called a radial clamp out
specifically because it *"would drag both to a corner together and would LOOK like
the very fault this removes"*; **the per-axis form is confirmed correct in the
headset, not just in the reasoning.**

> **`185` GROUP `A`'s CRITICAL-PATH BLOCK IS LIFTED.** *"Nothing else in aim is
> judgeable until this is done."* **It is done.** `A3` — which `185` says *"cannot
> be judged while the crosshair leaves the frame"* — **is unblocked, and so is
> `B2`** (`189` §2 removed its other dependency).

---

## §2 — THE CORNER REST IS THE STOCK CLAMP, AND THE NUMBER WAS ALREADY IN OUR LOG

> `[REPORTED]`: ***"when my controller went off screen the target is partially off
> on whatever corner I left it at."***
> `[REPORTED]`: at the limit the cross is **partly clipped but still visible.**

**THIS IS NOT `A1` MISBEHAVING. IT IS `A1` WORKING AND THEN STOCK GOLDENEYE
PINNING THE SIGHT WHERE IT HAS ALWAYS PINNED IT.** The arithmetic is four lines
of our own patch and it lands exactly on the observation:

- the cone clamp bounds `nx` to `+-1` (`188` §1);
- `ge_vr_aim.c:552`: `crosshair_angle.f[0] = nx * (w/2) + (w/2)` -> at `nx = 1`
  that is **`320` on a 320-wide screen — the frame edge exactly**;
- `:596-612`, the stock `[3, w-4]` clamp: **`320` becomes `316`**;
- `:615`: `+ screenleft`, which `189` measured as `0`.

**SO THE SIGHT'S CENTRE COMES TO REST FOUR PIXELS INSIDE THE FRAME — AND ANY
CROSSHAIR GLYPH WIDER THAN EIGHT PIXELS HANGS HALF OFF.** That is "partially
off", precisely.

> **`[MEASURED]`, AND IT WAS SITTING IN `187`'s OWN LOG UNREAD:**
> `BULLET aim=(480,21)px src=TRUEAIM | SIGHT crosshair_angle=(316,21)px CLAMPED`.
> **`316`.** The number the wearer described was printed before he described it.

**AND "WHATEVER CORNER" IS CONSISTENT WITH INDEPENDENT AXES, NOT AGAINST THEM.**
If the controller leaves the frustum diagonally, BOTH axes are out and both pin —
which is a corner, correctly. §1's level sweep is the test that separates the
two, and it says the axes are independent. **A corner reached from a diagonal
input is the right answer; a corner reached from a level input would have been
the fault.**

**IT IS ALSO NOT NEW, AND IT IS NOT OURS.** The `[3, w-4]` margin is stock — a
1997 constant sized for CRT overscan, where four pixels of inset was generous.
**A VR frame edge is a hard boundary with nothing beyond it.** Recorded as
`169` **U-21**, with the fix identified and cheap: **widen the margin in OUR OWN
clamp, which is the one place this is reachable** (`172` established that
`gunDrawSight` is not), **and leave `g_geVrTrueAimPx` untouched so the BULLET does
not move.** `188`'s cone limit must NOT be insetted instead — that would drag the
shot in with the sight and undo U-16.

---

## §3 — ►► THE RESET-TO-CENTRE ON TRACKING LOSS. BY CONSTRUCTION, AND WORTH CHANGING. ◄◄

> `[REPORTED]`: ***"If my controller snaps out of camera view the target resets in
> the center before attaching back to controller when it comes back into the
> view."***

**`[READ]`, AND IT IS THE DOCUMENTED BEHAVIOUR OF THE REFUSAL PATH.**
`ge_vr_aim.c:324`: the whole aim block sits behind `else if
(geVrAimFwdHead(...))`. **No hand pose -> the block never runs -> the stick keeps
the frame** — and with no stick input, `:285-286` is
`crosshair_x_pos * guncrossdamp + 0`, **an exponential decay to zero, which is
screen centre.** `160` §2 recorded this exact behaviour for a different cause:
*"both integrators decay to screen centre."*

**SO NOTHING IS BROKEN. BUT THE BEHAVIOUR IS A CHOICE NOBODY MADE DELIBERATELY**,
and it is the wrong one for a hand-tracked gun: **a lost pose is "I do not know
where the gun is", and gliding the sight to the centre ASSERTS something instead
— that the gun is level and forward.** `48`'s rule is that an instrument must be
able to say *"I cannot answer this"*; the aim path CAN, and then the integrator
answers anyway. **HOLD THE LAST AIM INSTEAD.** `169` **U-22**.

### AND AN INSTRUMENT GAP FOUND BY THE SAME REPORT — IT SHOULD BE CLOSED FIRST
**`[READ]`: `A1-VERIFY` CANNOT SEE THESE FRAMES AT ALL.** `aimed` and `refused`
are both incremented INSIDE the `geVrAimFwdHead()` branch, **so a frame with no
hand pose is counted in neither.** `aimed + refused` is not the frame count, and
**a tracking dropout is invisible in the one instrument that exists to measure
the aim.**

> **THAT IS THE `186` §3 MISTAKE IN ANOTHER PLACE**, and it is the reason to fix
> it now rather than later: `189` §1 read a frozen `aimed` beside a climbing
> `refused` and correctly called it idle — **but a long tracking dropout would
> look ALMOST the same** (frozen `aimed`, frozen `refused` too), and nothing in
> the line would say which. **One counter, `noPose`, beside the other two. No
> behaviour change.**

---

## §4 — WHAT IS OWED, IN ORDER

1. **`A3` — THE HUD SHIFT MAGNITUDE.** `185`: derive the cyclopean term, do not
   dial it. `[MEASURED]` applied `0.1867` against `[INFERRED]` `-0.1411` from this
   run's tangents — **about 32% too much**, and `[REPORTED]` the two crosses sit
   **one crosshair width apart.** **Its blocker is now met (§1).**
2. **`noPose` IN `A1-VERIFY`** (§3). One counter, no behaviour change. It can ride
   `A3`'s build.
3. **`U-21` THE SIGHT MARGIN** (§2) and **`U-22` HOLD-ON-LOST-POSE** (§3). Both
   small, both knob-gated, neither on the critical path — **but U-22 changes what
   a wear test LOOKS like, so it should not land in the same run as an aim
   change** (`48` rule 5).
4. **`B2`, T7 in stereo** — now blocked only by `A3`.

**NOTHING STAGED. THE COMMIT IS THE OWNER'S**, both repos.
