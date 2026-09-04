# 33 — the first head-tracked session, and what it actually showed

**PROPOSAL — NOT EXECUTED. 2026-08-22.** Nothing in "What to do" below has been
built. This document exists to be argued with first. `32` skipped that step and
this one is not going to.

---

## Correcting `32` before anything else

`32` aimed the session at the sign-versus-scale question and treated the eye
geometry as the frontier. **It was aimed at the wrong open question**, and the
very first head-tracked log says so in its first line of head data. The ladder
was not wrong to run — it produced the number that closes one question outright —
but the thing that makes the view unusable was never in `32`'s list of
candidates.

`32` also went in as a doc and a launcher edit in the same breath, with no gap
for disagreement. That is the failure this project's method exists to prevent.

---

## What the run actually was

```
[gevr] host: frustum=1 offset=3.175 eye=0 fitAspect=0 sbs=0 (enabled=1)
[gevr] host: eyeSign=1
[gevr] host: head=1 translate=1 liveFov=1 unitsPerMetre=50.0 yaw=1 pitch=1 roll=1
```

**This is the first time `ge_vr_head_transform` has ever run with real data.**
It got a full session — `xrBeginSession ok`, state reaching `FOCUSED`, both eye
swapchains at 4140x3292, both eyes rendering, layers submitted. Everything `30`
built is alive.

`eye=0` and `eyeSign=1` — the defaults. **The launcher change in `32` is inert in
this run**: `-SwapEyes` was not passed, and `GE_VR_EYE` was already 0 before it
was added to the clear list, so clearing it removed nothing. The only flag
difference from the previous run is `pitch=1` where that run had `pitch=-1`, and
that is a flag choice, not a code change. Recorded because "what changed" has to
be settled from the log rather than from memory.

---

## Result 1 — the eye separation is correct. That question is closed

```
eye sep 3.17 units      at unitsPerMetre = 50
```

3.17 / 50 = **0.0634 m = 63.4 mm**. The measured IPD from `09` is 63.5 mm.

**Gate A passes.** `xrLocateViews`' per-eye positions are being read correctly
and converted correctly, and the two eyes share the conversion. At 100 units per
metre this same headset would read 6.34.

Three things follow, and they are worth stating separately because they have been
open for a long time:

- **The eye-sign hypothesis is dead.** Not "tested and passed" — *dead*. `30`
  removed the quantity `GE_VR_EYE_SIGN` flipped, and the separation that replaced
  it is measured, correct, and cannot be backwards, because both eyes come from
  the same `views[]` in the same frame. `25` left it resting on argument; it is
  now settled by a number, and the answer is that there was nothing there.
- **`16`'s derivation is not what is wrong.** Whatever `unitsPerMetre` should be,
  the separation tracks it exactly and consistently.
- **`32`'s prediction 1 was right, and it was the least interesting thing in the
  document.**

## Result 2 — the head pose origin is four and a half metres in the air

```
[gevr] head: x=-50.6 y=227.7 z=86.2 units (4.555 m up), eye sep 3.17 units
                     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
```

**This is the breakage.** Every sample in the run sits at `y` between 223 and
228 units, `x` around -50, `z` around +84. It varies by a few units as the
wearer moves, so **tracking is live and the pose is reaching the render** — the
failure `31`'s log line was written to detect is not the failure we have.

The problem is the origin. `LOCAL` space is supposed to be anchored at the
headset's own pose when the space is created, so `y` should start near zero and
swing by half a metre. It starts 4.55 m up and stays there.

That constant offset is fed straight into `ge_vr_head_transform`'s row 3 and
displaces the viewpoint by `(-50, +227, +84)` game units from wherever the game
put the camera. Bond's eye height is **175 units** (`16`). The camera is
therefore roughly 227 units above his eyes — comfortably through the ceiling,
and about a metre sideways and forwards out of his body as well.

**That is what "totally broken" is.** Not the eye geometry. A viewpoint teleported
out of the player.

### It falsifies a claim in `00-START-HERE`

> **The floor calibration does not affect our image** — we use `LOCAL`, not
> `STAGE`, precisely because `10` measured the floor 2.4-3.2 m out.

`10` measured the floor wrong by 2.4-3.2 m on this rig. We are now 4.55 m out in
`LOCAL`. The reasoning was that `LOCAL` is immune because it is head-anchored
rather than floor-anchored. **The observation says otherwise**, and it is the
kind of claim that should not have survived on reasoning alone once a number was
available. Whether SteamVR is deriving `LOCAL` from a broken seated zero, or the
space is being created before tracking settles, is not yet established and is the
first thing to find out.

### And it makes the recentre non-optional

`00-START-HERE` lists the recentre key under "known and not blocking":

> A key that rebuilds it at the current head pose would remove any dependence on
> SteamVR's floor calibration, which resets constantly on this rig. Offered, ~20
> lines, not built.

It is blocking. It was the fix the whole time and it was filed as a convenience.

---

## Two things seen in passing, neither a bug

**`eye1=0` at the start and end of the run.** `render passes: eye0=90 eye1=0` for
the opening stretch, both eyes through the middle, then back to `eye1=0`. That is
`config.inLevel` gating from `21` doing its job — menus are not gameplay. Do not
chase it.

**60 fps, not 90.** Every line reads 60.0. `00-START-HERE` already records that
`ultramodern::get_target_framerate` follows the monitor and that the headset's
90 Hz is queried, logged and discarded — running at 90 depended entirely on
`rr_manual_value` being 90 in `graphics.json`. Worth checking whether that file
still says what `00` says it says, but it is a separate slice and not what makes
the view unusable.

---

## What to do — options, not a decision

### Right now, with no code at all

**In SteamVR, wear the headset, hold still, and reset the seated position.** Then
relaunch. If `y` drops to near zero, the cause is SteamVR's zero pose and the
whole problem is calibration reaching us through `LOCAL` — which is a five-second
test of the paragraph above, and it either confirms or kills the explanation
before a line is written.

To get a usable view back meanwhile:

```powershell
.\vr.ps1 -NoHead            # 3f-3. Worn and confirmed. No head tracking at all
.\vr.ps1 -NoHeadTranslate   # rotation works, position offset gone
```

`-NoHeadTranslate` is the better of the two if the rotation is worth having,
with one cost that is now measurable rather than theoretical: it zeroes row 3
for **both** eyes, so the 3.17-unit separation goes with it. Rotation and a
correct position, no stereo.

### The candidates, in the order I would rank them

1. **Recentre.** Capture the head pose once, at first good frame or on a
   keypress, and subtract it from every later pose. Removes the dependence on
   SteamVR's calibration entirely instead of compensating for it. It is the fix
   already written down, it is small, and it is right regardless of what the
   seated-position test says.
2. **Find out why `LOCAL` is 4.5 m out**, rather than only cancelling it.
   Cancelling a number you do not understand is how you end up with a second
   constant nobody can justify — `16` is already one of those. But this is
   diagnosis, and it does not have to block 1.
3. **Clamp head translation** (`31`'s open item). Independent of both, and a
   clamp alone would *not* have saved this run — a 227-unit offset clamped to
   something sane is still an offset, just a smaller wrong one. **A clamp is not
   a substitute for a recentre**, and it would have hidden the symptom well
   enough to make the cause harder to find.

### The gate, whatever we build

`y` reads within a few units of zero at session start, and a crouch takes it
clearly negative. That is a number in the existing log line, not a judgement
through a lens — and this session is the argument for preferring those.

---

## Open questions for discussion, before anything is built

1. Recentre on first good frame, on a keypress, or both? Automatic is invisible
   when it goes wrong; a key needs a binding and someone to remember it.
2. Do we want to understand the 4.5 m before cancelling it, or cancel first and
   diagnose after? I lean cancel-first *only* because the recentre is correct
   independently of the answer.
3. Is `-NoHeadTranslate` losing stereo acceptable as the interim, or should it
   keep the per-eye separation and drop only the head's own position? That is a
   real behaviour change to `ge_vr_head_transform`, not a knob, and it is
   arguably what the flag should have meant all along.
