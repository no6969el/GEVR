# 37 — VR aim: the concept, and the three traps in it

**CONCEPT, 2026-08-22. Not a plan, not scheduled.** Captured while the reasoning
is fresh because it changes what the controller slice should build toward. `26`
chose its mechanism one slice before it was needed and that paid; this is the
same move.

---

## The idea

In VR you never press the aim button. **The gun is the aim.** You point the
controller, the gun points there, you pull the trigger and the shot goes where
the barrel is. Hip-fire already behaves this way — `36` confirmed the shot
follows the gun, not the head — so the flat-screen aim mode, whose whole job is
to let a thumbstick do what a hand does directly, has **no role in VR at all.**

That is the right instinct and it deletes work rather than adding it.

## The game already has the quantity

`bondview.h`:

```c
/* 0x1051 */ s32     aimtype;
/* 0x1057 */ coord2d crosshair_angle;
            f32     crosshair_x_pos;
            f32     crosshair_y_pos;
            f32     gunaimdamp;
```

`crosshair_angle` is the offset between the player's facing and where the gun
points. It must be — aim mode moves the crosshair across the screen while the
camera stays put, and something has to carry that difference.

> **Corrected by `38`:** it is a **screen-space pixel position, not an angle**,
> and it is recomputed every frame from `crosshair_x_pos` / `crosshair_y_pos`, so
> it must never be written directly. `38` also confirms hip fire reads it
> unconditionally — the claim this document rested on — and finds a hard clamp
> that limits hand aim to roughly the game's original FOV. Read `38` before
> acting on anything below.

**So gun-direction-independent-of-body-direction is not a feature we add. It is a
feature the game ships, currently driven by the stick in one mode.** VR aim is
redirecting its input, which means auto-aim, sway, hit detection and anything
else downstream keeps working because we did not invent a parallel path.

Same shape as `26`: *"head rotation reaches the culling frustum via the patch's
existing widening."* Use the machinery that is there.

---

## Trap 1 — `vv_theta` is not the gun. Do not drive it from the hand

The tempting shortcut is to write the controller's yaw straight into `vv_theta`.
**It would spin the world.**

`vv_theta` is the player's **body facing**, and it drives the camera orientation,
the movement direction and the culling frustum. The world is rendered from the
game camera plus the head offset, so moving `vv_theta` moves the world. Point the
controller left and the room swings left.

The decomposition has to be:

| Quantity | Driven by | Drives |
|---|---|---|
| `vv_theta` / `vv_verta` | stick — snap or smooth turn, as now | body facing, camera, movement, culling |
| `crosshair_angle` | **the controller's aim pose, relative to the body** | where the gun points and where the shot goes |

The hand supplies an **offset**, never an absolute heading. That is also why the
recentre in `36` matters here: "relative to the body" is measured in the space
3f-5 is fixing, and a hand angle taken against a drifting origin is a hand angle
that drifts.

## Trap 2 — auto-aim stops being a feature

`autoaimx`, `autoaimy`, `autoaim_target_x/y`, `autoyaimtime60` and
`currentPlayerSetXAutoAimEnabled` are GoldenEye's aim assist. On a thumbstick it
is generous and invisible. **On a tracked hand it fights you**: the gun points
where you put it and the game quietly moves the shot somewhere else, which reads
as the weapon not being yours — the single fastest way to break presence.

It is already a runtime setter, so this is a knob rather than surgery. Expect to
want it off, or heavily reduced, and expect that to be contentious because it
also makes the game harder in a way the original never was.

`gunaimdamp` is the same problem in miniature: damping tuned to smooth stick
input will read as lag on a hand that is already smooth.

## Trap 3 — you cannot zoom a VR view

The sniper is the interesting case and the instinct — **raise the scope to your
eye and it zooms** — is exactly right as an interaction. It is also cheaply
measurable once controller poses exist: the distance between the controller's aim
pose and the head pose, both of which we will already have, in the same space.
No new plumbing, and it is a gesture rather than a binding.

**But the zoom itself cannot work the way it does on a monitor.** Narrowing the
headset's field of view is not zoom, it is a lie about the size of the room, and
it is a reliable way to make people ill. The FOV in a headset is set by the
optics and the wearer's head; it is not a free parameter.

The VR-native answer is a **scope render**: a second, narrow-FOV render of the
scene drawn onto the scope lens geometry, so the magnified image sits inside the
world at the right physical place instead of replacing it. That is how VR
shooters do it, and it is well understood.

Two consequences worth noting now rather than later:

- It is a **second view per eye**, which the eye-target machinery from `28`
  already has most of the shape for.
- It lands in **RT64**, which is MIT and upstreamable — the good half of the
  licence split in `PUBLISH-MANIFEST.md`, not the encumbered one.

Also entangled and needing separation: the game ties zoom to `insightaimmode`,
which *also* re-couples the crosshair to the head. VR wants the magnification
without the coupling, so those two have to come apart before either is useful.

---

## What this means for the work already scheduled

Nothing changes order. It changes what the controller slice should expose.

1. **Controller slice — buttons and sticks.** Unchanged, next.
   **But also surface the `aim` pose**, not only the buttons. It is a few extra
   lines at binding time and it is what everything above needs. Building the
   bindings twice because the first pass only wanted buttons would be silly.
2. **Hand aim** — drive `crosshair_angle` from that pose. Find who else reads it
   first: `21`'s rule, and `35` already flagged that `vv_theta`'s companions go
   stale if written blind. Establish whether `crosshair_angle` has companions of
   its own **before** writing to it.
3. **Auto-aim and damping** — knobs, tuned once hand aim exists and not before.
4. **The scope** — its own phase, RT64-side, after all of the above.

## The open question, recorded not answered

Does the shot ray read `crosshair_angle` in **both** modes, or only in aim mode?

`36` established the shot follows the gun in hip-fire. If hip-fire's ray ignores
`crosshair_angle` and simply uses the body facing, then driving that field does
nothing outside aim mode and the whole approach above needs re-deriving.

**That is the one fact this concept rests on, and it has not been checked.** It
is a code question, answerable by reading the firing path, and it should be
settled before the hand-aim slice is planned rather than during it.
