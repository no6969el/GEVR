# 79 — SLICE 2 of `76`: the gun follows the hand. BUILT, WORN, NOT FINISHED.

> ## THE RESULT, AT THE TOP, BECAUSE THE PLAN BELOW IS NOW HISTORY
>
> **Built, worn, and corrected three times in one session by the person wearing
> it. It is NOT working yet, and the default build ships the LESS wrong of two
> unfinished states.**
>
> | Correction | What was wrong | Wearer's words |
> |---|---|---|
> | **1. Rotation only is not "free"** | The gun pivoted but stayed pinned in front of the face | *"I have to be able to use the gun freely. This is not a good way to play"* |
> | **2. A MIRROR, not a rotation** | Both bases were built with `ge_vr_head_transform`'s per-axis quaternion NEGATIONS. That is a reflection, and the product of two reflected rotations is a mirror — identity-ish at the centre, worse toward the edges | *"Turn left, I see the right side of the gun... in the corners my arm drifts... as I aim at the roof it curves the hand down"* |
> | **3. The engine's own turn-sway was still in there** | The delta MULTIPLIED the game's root rotation, so `gunSetHorizontalOffset`, the sway springs and the recoil jitter still rotated the gun underneath the hand | *"In this game when you turn left or right it makes the gun turn in the direction you are turning... I think it's still attached to other parts"* |
>
> **The wearer diagnosed all three.** Correction 2 in particular — "correct dead
> ahead, increasingly wrong toward the edges, yaw mirrored while pitch reads
> fine" — is a textbook description of a mirrored transform, arrived at without
> seeing a line of the code.
>
> **Where it ended:** correction 3's absolute-rotation path is right in
> principle and read *"really far away and doesn't seem to move properly"* worn.
> **So `GE_VR_HAND_ABSOLUTE` defaults OFF**, and the shipped default is the
> delta path — which tracks, but pulls. **Neither is validated. Nothing here is
> DONE and the board says so.**
>
> ### THE NEXT SESSION'S PROCEDURE, in order, before any new code
>
> 1. **Read `81` first.** Perfect Dark — the SAME ENGINE — has a shipping MIT
>    VR port with motion-control aiming. **Corrections 1-3 are all problems
>    somebody else has already solved in nearly the same source.**
> 2. **`.\vr.ps1 -UnitsPerMetre 50 -ViewmodelScale 0.5 -HandAim -HandAbsolute`**
>    and find out why it reads far away. First suspect: the neutral reference
>    `R0` is captured from **whichever hand model calls first**, which may be the
>    watch or the left hand, not the gun.
> 3. **Only then** sweep `-HandAxisX/Y/Z`, one at a time.
> 4. **`-HandRotOnly` is the isolator** — it separates a bad translation
>    convention from a bad rotation one, and it costs one launch.
>
> ### AND THE THING THE USER ASKED FOR THAT IS NOT BUILT
>
> > *"I want it to aim where I'm aiming the gun, and then have, like, a dot or
> > crosshair in the distance."*
>
> **That is slice 3 plus a world-space aim dot** (O12's amendment in `61`, and
> `81` question 5). **The dot is not decoration: `38`'s hard clamp at roughly
> ±30° means the gun and the bullet WILL disagree past that, and a dot on the
> actual fired ray is the only honest way to show where the shot goes.**

# The plan as written, before any of it was worn

**2026-08-23, ~17:00. Written before the code.** `78` shipped and passed its
monitor gates; this is the next slice and the last build of this session.

**Scope, deliberately narrow: the gun MOVES WITH YOUR HAND. The bullet does
not.** Shots keep coming from the crosshair until slice 3. That separation is
the point — it answers *"does it feel like mine"* without entangling it with
*"does the bullet go there"*, and each question gets its own wear test.

---

## THE MATHS, AND WHY IT GOES IN THE HOST

Every viewmodel node matrix is an **absolute camera-space modelview**
(`G_MTX_LOAD`, `model.c:4854`), so re-rooting the assembly is one right-multiply
by a delta:

```
G  = inverse(oldRoot) * newRoot          computed ONCE per model, in the host
M' = M * G                               applied to EVERY node, in the patch
```

**For the root that gives exactly `newRoot`, and for every child it preserves
the relative structure** — the slide, hammer and muzzle stay where they belong.
`78` G6 already proved that class of bug is real and worth designing out.

**The inverse lives in C++, not in the patch.** The root carries a uniform
model scale (`gunfire.c:643`, `IDO_POINT_ONE`), so the inverse is not a plain
transpose, and hand-written affine inversion in patch C is exactly the kind of
thing this project has been wrong about before. **The patch sends 16 floats and
receives 16 floats.** It does one 4x4 multiply per node and nothing else.

**`78`'s scale and push fold into `G` too**, so they stop being a second code
path and the patch gets simpler rather than more complex.

## WHAT `newRoot` IS

The **right controller's `aim` pose, expressed relative to the head** — which is
already the space the viewmodel lives in, so no view matrix is involved.

```
rotation      controller orientation, head-relative
translation   (aim position - head position), head-relative, x unitsPerMetre
```

**`61` already logs this pose every frame and nothing consumes it.** That line
is the whole input to this slice.

**Two knobs, because this project has never once got a convention right first
time** (`32`'s `-Sign`, `24`'s `-ForceEye`, `44`'s position signs):

| Knob | Default | Why |
|---|---|---|
| `GE_VR_HAND_AIM` | **0, OFF** | The whole slice, behind one switch. Off is the current build exactly |
| `GE_VR_HAND_POS` | 0 | Rotation only, first. **Orientation is most of the feel and half the risk** — keeping the game's own position means a wrong translation convention cannot throw the gun across the room |

## THE GATES — written before the code

| # | Gate | What would a build that did nothing have to do to pass? |
|---|---|---|
| G1 | `GE_VR_HAND_AIM` unset changes nothing at all | Nothing. Regression gate, first |
| G2 | Point the controller left, **the gun points left** | It cannot. A build wired to the stick would not move the gun at all |
| G3 | **Hold the controller still and move your head — the gun must NOT follow the head** | This is the whole meaning of "decoupled", and `36` already proved the head half |
| G4 | The gun stays in one piece | If it comes apart, `G` was applied per node incorrectly rather than uniformly |
| G5 | The world does not move | `G` is applied only to matrices that pass `78`'s pointer test |
| G6 | **The bullet still comes from the crosshair, unchanged** | Slice 3's job. **If shots start following the gun, something has reached the aim path that should not have** |

## WHAT WILL LOOK WRONG AND IS NOT A BUG

- **The gun and the crosshair disagree.** Expected. That is slice 3.
- **The arm.** GoldenEye fuses arm and gun into one model, so an arm attached to
  a hand-tracked gun may read oddly. **The hide switch is `hand->field_87F`**
  (not `hand_invisible`, which is a load-state counter with a misleading name),
  and it is a knob for later, not this slice.
- **The aim clamp does not apply yet.** `38`'s ±30-degree limit is on the
  *bullet*, not the model, so the gun will point anywhere in this slice and stop
  agreeing with the shot beyond that. **Seeing exactly where that starts to feel
  wrong is useful information for slice 3.**

## RECORDED, NOT CHASED — the judder is still there

Reported again this session, worn, at 50 u/m. **`72` exonerated the XR submit
loop and `73` named the candidate that predicts WHEN** (the game's VI clock
halves to 30 in heavy scenes while the renderer must produce 90). **Neither has
been acted on and neither should be acted on inside this slice.** It is O54, it
is written down, and it is the strongest candidate for the next session.
