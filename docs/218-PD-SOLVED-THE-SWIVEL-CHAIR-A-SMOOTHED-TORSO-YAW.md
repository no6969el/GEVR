# 218 — PERFECT DARK ALREADY SOLVED THE SWIVEL CHAIR. A SMOOTHED TORSO YAW, AND WE SHOULD TAKE IT.

**2026-08-26. Tiers per `182`. `[READ]` from the prior-art tree on disk. NOTHING
BUILT — this is a design decision awaiting the owner.**

---

## §1 — THE QUESTION, AND WHY THE ANSWER WAS NOT A WEB SEARCH

`[REPORTED]`, three decisions in one message:

> ***"Forward follows your head (offhand control should be an option in the future
> mod menu)... For the head yaw can we investigate a good medium from other
> published games?... mainly the direction I was facing since I AM IN A SEAT THAT
> SPINS — my direction may change and that messes up the shot."***

**PERFECT DARK'S VR PORT IS ON THIS DISK, IT SHIPPED, AND IT IS THE SAME ENGINE
FAMILY.** `168`'s rule says the DESIGNS transfer even when the subsystems do
not — and this is a design, not a subsystem. **It is better evidence than a
survey of games we cannot read.**

---

## §2 — ►►►► WHAT THEY BUILT, AND THEIR COMMENT NAMES THE OWNER'S PROBLEM ◄◄◄◄

**`[READ]` `port/vr/vr_settings.h:47`:**

```c
extern float VrArmBodyFollow;   // how fast the smoothed torso yaw chases the head (SPIN COMFORT)
extern bool  VrSeatedMode;
```

**`[READ]` `src/game/bondgun.c:10991-11005`, once per tick, right hand only:**

```c
f32 w = gRawHeadQ.w, y = gRawHeadQ.y;          // YAW ONLY - w and y components
f32 n = sqrtf(w*w + y*y);
w /= n; y /= n;
if (w < 0.0f) { w = -w; y = -y; }              // hemisphere fix
f32 hy = 2.0f * atan2f(y, w);                  // the head's yaw
f32 d  = hy - VrBodyYaw;
while (d >  M_PI) d -= 2*M_PI;                 // SHORTEST ANGLE
while (d < -M_PI) d += 2*M_PI;
VrBodyYaw += d * VrArmBodyFollow;              // 0.02 per tick
```

**IT IS AN EXPONENTIAL CHASE, NOT A DEADZONE.** `VrArmBodyFollow = 0.02` gives a
time constant of about **0.8 s at 60 Hz, 0.55 s at 90**.

| what you do | what the torso does |
|---|---|
| **glance** left and right | **barely moves** — your body does not turn when you look |
| **hold** a turn, or **spin the chair** | **catches up within about a second** |

> **AND THEIR OWN COMMENT SAYS WHY THE SHORTEST-ANGLE FORM MATTERS:** *"so a full
> 360 physical spin tracks correctly instead of unwinding."* **THAT IS THE SWIVEL
> CHAIR, SOLVED, IN A SHIPPED PORT.**

**`[READ]` `bondgun.c:912-931` — the second consumer, and it is the deeper
lesson:** the arm anchor is counter-rotated by *"the head yaw RELATIVE to the
smoothed torso, so it is body-stable without coming unstuck when you physically
turn"*. **They hit the identical problem we hit in `194`/`200`/`217` — a value
expressed in a head-rotating frame dragging something that should be
body-stable — and `VrBodyYaw` is their answer to it.**

---

## §3 — WHAT WE SHOULD TAKE, AND WHAT WE SHOULD NOT

`[REPORTED]`: *"anything that is already made by them in the VR area I want to
consider taking if it works."*

| take | why |
|---|---|
| **`VrBodyYaw`, the smoothed torso yaw** | **pure maths on a quaternion. No PD subsystem is called.** `168`'s rule is satisfied outright |
| **`ArmBodyFollow = 0.02` as the starting value** | a shipped default, and `155` is the precedent that PD's CONSTANTS often transfer |
| **the shortest-angle wrap and hemisphere fix** | **both are correctness, not taste** — without them a 360 spin unwinds |
| **`VrSeatedMode` as a concept** | the owner is seated and spinning; it belongs in the options `169` U-04 already plans |

**WHAT WE MUST NOT ASSUME TRANSFERS:** their `0.02` was tuned at PD's tick rate
and for the ARM. **We would use it for LOCOMOTION as well, which is a different
job** — `155` is also the precedent that a PD constant can fail to transfer
(their 1.5708 rad post-rotation did). **So it is a knob from day one, defaulted to
theirs.**

---

## §4 — WHAT IT WOULD FIX HERE, AND IT IS MORE THAN LOCOMOTION

**1. FORWARD FOLLOWS THE BODY, NOT THE GLANCE.** `[REPORTED]` the owner asked for
head-relative forward — **the smoothed torso IS the usable version of that.** A
raw head-relative forward would steer him every time he looked at something.

**2. THE SWIVEL CHAIR STOPS CORRUPTING THE SHOT.** `[REPORTED]` *"I am in a seat
that spins, my direction may change and that messes up the shot."* **A torso yaw
that tracks sustained rotation gives every hand-relative quantity a stable body
frame to be expressed in** — which is exactly what `194`, `200` and `217` were
each missing.

**3. AND IT MAY BE THE FRAME `217` STILL NEEDS.** `[REPORTED]` after `217`:
*"it points better, which way I am facing changes the output... often off due to
positioning."* **`[INFERRED]`** — and the counter-example search is stated in §5 —
**that the residual is the chair: the play space rotates under him while the game
frame does not.**

---

## §5 — WHAT IS OWED, AND THE MEASUREMENT COMES FIRST

1. **RE-RUN `216`'s FIVE GROUPS ON THE `217` BUILD.** **This is still the next
   thing, and it now has a second question to answer:** does the residual rotate
   with the wearer's PHYSICAL facing?
   > **COUNTER-EXAMPLE SEARCH (`182` §2, `209` §4.3):** if the chair is the
   > cause, **two groups shot from the same physical facing must agree, and two
   > from different facings must differ.** `216`'s group 5 (turn 180) is already
   > that test — **but it was run before `217`, so it must be repeated.** If the
   > residual is the same whatever the facing, the chair is NOT the cause and
   > this document does not apply to the aim.
   >
   > ### ►► AND `[REPORTED]` CLARIFIES THE OLD DATA: GROUP 5 WAS A *PHYSICAL*
   > ### TURN. *"On that one test I had physically turned 180 and shot."* ◄◄
   > **THAT MAKES `216`'s TABLE SHARPER THAN IT LOOKED.** `[MEASURED]`:
   >
   > | | group 1 | group 5 (physically turned 180) |
   > |---|---|---|
   > | **GUN** world yaw | `+37.9` | `-143.4` — **it moved with his body** |
   > | **BULLET** world yaw | `-145` | `-147` — **IT DID NOT MOVE AT ALL** |
   >
   > **THE BULLET'S WORLD DIRECTION WAS INVARIANT TO A 180 DEGREE PHYSICAL
   > ROTATION.** The gun followed his body because the controller does; the
   > bullet stayed locked to the GAME's frame, which his chair cannot turn.
   > **Group 5's apparent 7-degree "success" was the two frames crossing, not
   > agreeing.**
   >
   > **THAT IS `217`'s DIAGNOSIS CONFIRMED FROM THE OTHER SIDE, AND IT WAS
   > ALREADY IN THE FIRST RECORDING** — it only became legible once the owner
   > said the turn was physical. **`[REPORTED]` detail about HOW a test was
   > performed changed what the numbers meant; the numbers alone could not.**
2. **THEN THE LOCOMOTION SLICE** — `VrBodyYaw` plus `speedforwards`/`speedstrafe`
   (`structs.h:2110-2112`, reachable). **Knob-gated, `-BodyFollow`.**
3. **`169` U-25: OFF-HAND FORWARD AS AN OPTION**, per the owner, for the settings
   menu U-04 already plans.

**NOTHING STAGED. THE COMMIT IS THE OWNER'S.**
