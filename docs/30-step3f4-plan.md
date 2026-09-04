# 30 — step 3f-4 plan: live pose and FOV, and the world holding still

**2026-08-22.** 3f-3 put the game in the headset at full panel resolution. 3f-4
is what makes it a *place* rather than a picture.

## The thing that is actually wrong right now

The head pose from `xrLocateViews` is handed to the compositor as the projection
layer's pose, and **nowhere else**. The game's camera is driven entirely by the
gamepad.

So the image is rendered from the game's camera, then displayed at wherever your
head is. Turn your head and the whole world turns with it. **Nothing stays put.**

That is worth stating plainly because of what it does to everything else: with no
vestibular confirmation that the world is a world, judgements about separation
and scale are being made on a scene that is already wrong in a different way.
The report that closed the last session —

> too far apart, the gun was visibly two of them, also very close

— may be two faults stacked, and 3f-4 removes one of them. **It is therefore
worth doing before concluding anything about the eye sign or the scale.**

## Prior art

- `xr_stereo.cpp` (`10`) already contains a validated pose-to-view and
  tangents-to-projection pair, against this rig.
- `26` chose the mechanism in advance: *"Head rotation reaches the game's culling
  frustum via the patch's existing widening."* The frustum is already widened to
  106 degrees for exactly this. **The design decision is made; this is its
  implementation.**
- `VrEyeParams::viewOffset` is a full 4x4 composed as `v * V * E * P`, so `E`
  acts in **view space, after the game's own camera**. A head transform placed
  there rotates and translates the view without the game knowing anything
  happened. The struct was built for this from the start — `15` calls it "eye
  transform in VIEW space" and only ever used the one translation element.

## The one convention question, and why it is already answered

Handedness is normally where this kind of work goes wrong. Here it is settled by
evidence rather than by argument:

**The measured Pimax `XrFovf` tangents were fed straight into
`VrEyeParams::tanLeft/Right/Up/Down` and produced correct stereo — on the monitor
in 3e, and in the headset in 3f-3.** If RT64's view space disagreed with OpenXR's
on handedness or on which way is forward, that could not have worked.

So the frustum convention transfers. **The rotation convention is a separate
claim and does not inherit that evidence** — which is why it gets a knob and a
gate rather than a paragraph of reasoning. `25` closed with the eye sign resting
on argument and it is *still* unsettled two slices later; that mistake is not
worth repeating on a second axis.

## Staging — two slices, because they fail differently

### 3f-4a — live FOV, replacing the hardcoded tangents

Take `views[eye].fov` per frame, convert the four angles to tangents, feed them
into `VrEyeParams`. Delete the `ge_vr_eye_tangents` constant table.

No coordinate maths, no rotation, nothing that can invert depth. Pure
substitution of a measured constant by the same number arriving live.

**Gate:** the log prints per-frame tangents that match the hardcoded table to
within rounding — `-1.3760 / 1.0358 / 1.0176 / -1.0176` for the left eye. **The
picture must be visibly unchanged from 3f-3.**

That gate is the point of splitting the slice: if the numbers match and the image
changes, the plumbing is wrong and it is wrong *before* any rotation exists to
blame. If they do not match, the constants were stale and the log says by how
much.

### 3f-4b — head pose into the view

Build `E` from the head pose, in view space:

```
E = | R^T      0 |          R = head rotation, t = head position in game units
    | -t.R^T   1 |          row-vector convention, translation in row 3
```

and let the per-eye position from `xrLocateViews` supply the IPD instead of
`GE_VR_TEST_OFFSET`.

**This is where the scale question gets answered properly.** `xrLocateViews`
reports eye positions in **metres**; the game works in game units; the conversion
is one number, and that number is the thing `16` derived as ~100 units/metre and
explicitly labelled *"a derivation, not a measurement"*.

So it becomes a knob, `GE_VR_UNITS_PER_METRE`, default 100, and it drives **both**
the head translation and the eye separation — consistently, which the current
build does not: today the IPD is a hand-set constant in game units and the head
does not move at all.

Sweeping that one variable is a direct measurement of the game's scale. Whatever
value makes a doorway feel like a doorway **is** the answer `16` asked for, and it
is a physical quantity rather than a tuning fudge.

**Gates, in order:**

| # | Check | Pass |
|---|---|---|
| 1 | Turn your head | **The world stays put.** This is the whole slice |
| 2 | Lean left and right | The view translates. Parallax against near objects |
| 3 | `GE_VR_HEAD=0` | Reverts to 3f-4a exactly. Head does nothing |
| 4 | Yaw, pitch, roll each alone | Each moves the world the *correct* way |

Gate 4 is four separate observations and they are worth taking separately: an
inverted pitch is easy to mistake for an inverted roll when both are wrong at
once, and each has its own sign knob.

## Knobs, so a wrong convention costs a relaunch and not a rebuild

`GE_VR_EYE_SIGN` earned its keep — it is still the fastest way to test the
outstanding sign question. Same pattern here:

```
GE_VR_HEAD=1              head pose drives the view (0 reverts to 3f-4a)
GE_VR_HEAD_YAW_SIGN       flip yaw
GE_VR_HEAD_PITCH_SIGN     flip pitch
GE_VR_HEAD_ROLL_SIGN      flip roll
GE_VR_HEAD_TRANSLATE=0    rotation only - isolates orientation from position
GE_VR_UNITS_PER_METRE     default 100 (docs\16). Drives IPD and head translation
GE_VR_LIVE_FOV=0          fall back to the hardcoded tangent table
```

`GE_VR_HEAD_TRANSLATE=0` is there because rotation and translation fail in ways
that look alike through a headset — a world that swims when you turn and a world
that swims when you lean both read as "tracking is broken".

## Risks

1. **Rotation handedness.** The frustum evidence does not transfer to rotation.
   Hence the per-axis signs and gate 4.
2. **The culling frustum.** The patch widens to 106 degrees so head rotation has
   geometry to find. Beyond roughly half that in yaw, expect things to pop in at
   the edges. That is a known limit of the approach `26` chose, not a new bug,
   and the fix is Phase 3's decoupled camera rather than a wider frustum.
3. **The viewmodel.** It rides the game camera, so under head rotation it will
   swing with the world instead of staying in front of you. **Expect this to look
   worse before it looks better** — and it is already the subject of an open
   contradiction, since the docs predicted it would read flat and it doubles
   instead. Do not chase it in 3f-4.
4. **`LOCAL` space drift.** The origin is wherever the headset was at session
   start. A recentre is still wanted, and is still not built.
5. **One frame of latency.** The pose used is the one located during the present
   hook, and the game's frame was rendered before it. `12` §5 deferred the
   interlock deliberately; reprojection in the compositor covers most of it.

## What this does not do

**It does not decouple aim from view.** Where you look and where you shoot stay
the same thing. Turning your head turns the gun. That is Phase 3 and it needs the
patch, not the host.

3f-4 makes the world hold still. That is enough for one slice, and it is the
precondition for judging everything else.

## After 3f-4

Re-run the stereo ladder from `00-START-HERE` — **on a world that stays put.**
Sign first, then sweep `GE_VR_UNITS_PER_METRE` for scale. Both judgements get
much easier once the horizon stops following your head, and the scale sweep then
produces a real number for `16`.

---

# 3f-4 implemented, 2026-08-22 — built, not yet worn

Both slices are in. The headset was asleep for all of it, so **everything below
is verified up to the point where a person has to look through it.**

## What is verified

| Check | Result |
|---|---|
| Builds clean | Yes |
| `GE_VR_XR` unset | 60 fps, closes cleanly. **Unchanged** |
| Knobs reach the host | `head=1 translate=1 liveFov=1 unitsPerMetre=50.0 yaw=1 pitch=-1 roll=1` |
| `vr.ps1` reports its own state | Yes, and no longer prints an offset it is not using |
| Sleeping headset | Retries, as `29` |

## What is not

**Anything a person has to see.** No live pose has ever reached
`ge_vr_head_transform` — the function has never executed with real data.

## Where the transport lives

`ge_vr::HeadView` in `ge_vr_host.h`: raw OpenXR values, metres and quaternions
and FOV angles, with **no conversion applied**. Published on the present thread
immediately after a successful `xrLocateViews`, read on the game thread by
`ge_vr_update_config`.

Deliberately dumb. Every conversion this project has got wrong was got wrong in
a place that was also doing something else, so all of them — the sign flips, the
units, the matrix — now live in exactly one function, `ge_vr_head_transform`,
which does nothing else.

A mutex rather than atomics: it is a dozen floats that have to be consistent
**with each other**, and a torn read mixing one eye's pose with the other's FOV
would produce a subtly wrong frustum and no error anywhere.

## One decision worth recording: each eye uses its OWN pose

Not the head pose plus a hand-set IPD. `xrLocateViews` reports a pose per eye, so
that is what each eye's transform is built from.

Three things fall out at once:

- **The separation is the headset's real measured one**, not `docs\16`'s
  derivation times a constant.
- **Leaning works** without being written.
- **Position and frustum can no longer disagree.** `25` records the failure where
  eye 1 carried the right eye's tangents while its camera was displaced left —
  uncomfortable rather than obviously broken, and expensive to find late. Both
  now come from the same `views[eye]`, in the same frame. That class of bug is
  gone rather than guarded against.

`GE_VR_TEST_OFFSET` is consequently unused while head tracking is on, and
`vr.ps1` no longer prints it in that mode — a launcher reporting a number the
build ignores is exactly the kind of thing that costs a wrong diagnosis.

## The scale question is now a physical measurement

`GE_VR_UNITS_PER_METRE` converts both the head translation and the eye
separation, from one place. Sweeping it sweeps the game's scale coherently:

```powershell
.\vr.ps1 -UnitsPerMetre 100    # docs\16's derivation
.\vr.ps1 -UnitsPerMetre 50     # world reads twice as large
.\vr.ps1 -UnitsPerMetre 200    # half as large
```

Whatever makes a doorway feel like a doorway is the number `16` asked for, and
it is a physical quantity rather than a tuning fudge.

## The order to test in

```powershell
.\vr.ps1 -NoHead -NoLiveFov     # 1. exactly 3f-3. Confirms nothing regressed
.\vr.ps1 -NoHead                # 2. 3f-4a. Live FOV only. MUST look identical
.\vr.ps1 -NoHeadTranslate       # 3. rotation only. Does the world hold still?
.\vr.ps1                        # 4. everything, at 100 units/metre
```

Step 2 is the one that is tempting to skip and shouldn't be: if the live
tangents match the constants and the picture still changes, the plumbing is
wrong, and it is wrong *before* any rotation exists to blame it on. `gevr.log`
prints the live tangents once — the left eye should read
`-1.3760 1.0358 1.0176 -1.0176`.

If step 3 swims, work the signs one axis at a time:
`-YawSign -1`, then `-PitchSign -1`, then `-RollSign -1`.

## Expect the viewmodel to look worse

It rides the game camera, so under head rotation the gun swings with the world
instead of staying in front of you. It is already the subject of an open
contradiction — the docs predicted flat, it doubles. **Not a 3f-4 bug. Do not
chase it here.**
