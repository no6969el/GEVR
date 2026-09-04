# 197 — THE HAND POSITION AND THE AIM RAY USE OPPOSITE HANDEDNESS, TEN LINES APART, IN ONE FUNCTION.

**2026-08-25. Tiers per `182`. `[REPORTED]` is the wearer, verbatim, from a run
whose stereo is `[MEASURED]` GOOD — see §4.**

---

## §1 — THE REPORT, AND IT IS A TRANSPOSE, NOT A SIGN

> ***"If I turn right, even if I turn my whole body right, the gun disappears over
> my LEFT shoulder. If I turn left, it goes into my RIGHT shoulder."***
> ***"If I tilt my head sideways to the right, the gun shoots off to the left. And
> if I do it to the left, it goes to the right."***
> ***"If I walk forward, it starts to go down to the floor... it starts to go back,
> but now it's veering off to the left."***

**INVERTED IN YAW *AND* IN ROLL, AND TRANSLATION LEAKING ACROSS AXES.** A wrong
SIGN inverts one axis. **Wrong on two rotation axes at once, plus forward
becoming down, is a wrong-handed BASIS** — the vector is being mapped through a
rotation instead of its inverse.

---

## §2 — ►►►► THE READ. THEY ARE TEN LINES APART AND THEY DISAGREE. ◄◄◄◄

**`[READ]` `rt64_render_context.cpp`, inside `hand_override`:**

```c
// THE POSITION, docs\156:
handPos[i] = (dx * Rhead[i][0]) + (dy * Rhead[i][1]) + (dz * Rhead[i][2]);   // = Rhead   * d

// THE AIM RAY, docs\158 s5, TEN LINES BELOW:
g_geVrAimFwdHead[hand][i] = (Rhead[0][i] * fwdWorld[0])
                          + (Rhead[1][i] * fwdWorld[1])
                          + (Rhead[2][i] * fwdWorld[2]);                     // = Rhead^T * fwd
```

**`[READ]` `ge_vr_quat_to_basis` builds the standard basis whose COLUMNS are the
local axes in world coordinates — it maps LOCAL -> WORLD. To express a WORLD
vector in the head's frame you need its TRANSPOSE.**

**THE AIM DOES. THE POSITION DOES NOT.** The position has been counter-rotating
by the head's orientation since `156`.

> **AND IT IS INVISIBLE WHENEVER YOU FACE FORWARD**, because `Rhead` is then the
> identity and its transpose is the same matrix. **It appears only when the head
> TURNS — which is every head-turn report this project has ever recorded:**
>
> | doc | `[REPORTED]` |
> |---|---|
> | `173` | *"if I turn my head left and right, the gun will change directions in my hand automatically"* |
> | `192` | *"it seems to kinda wanna maneuver the hand"* |
> | `197` | *"turn right, the gun disappears over my LEFT shoulder"* |
>
> **THREE INDEPENDENT REPORTS OF ONE FAULT, AND THE PROJECT KEPT FILING THEM
> AGAINST THE ROTATION.**

### AND `173` FOUND THIS EXACT THING — IN THE OTHER VARIABLE

`173` §3: *"`R = Rhead * Rhand^T` is wrong; correct is `R = Rhead^T * Rhand` —
**AND THE AIM PATH HAS ALWAYS USED `Rhead^T`**."*

**IT DIAGNOSED THE HANDEDNESS, SHIPPED `-SeamCompose` FOR THE ROTATION, AND NEVER
LOOKED AT THE POSITION BESIDE IT.** Same fault, same function, same document,
other variable. **`T9` is still owed and is still about the ROTATION; this is the
POSITION half and it is independent.**

---

## §3 — THE CHANGE

```c
handPos[i] = (dx * Rhead[0][i]) + (dy * Rhead[1][i]) + (dz * Rhead[2][i]);  // Rhead^T
```

- **KNOB `-NoHandPosT`** (`GE_VR_HAND_POS_T=0`) restores the legacy handedness.
- **`194`'s ROOM TERM TAKES THE SAME KNOB AND THE SAME TRANSPOSE** — it is also a
  world displacement expressed in the head's frame. **Two terms that are ADDED
  must live in ONE frame; a knob that flipped only one would produce a state
  neither arm of the A/B could explain.**
- **HOST-SIDE ONLY. ONE BUILD.** No new symbols, no `115` header, no game symbols.

**`G-197`, AND IT NEEDS NO SHOOTING:**
1. **Turn your head and body left and right. THE GUN MUST STAY IN FRONT OF YOU.**
2. **Tilt your head. It must stay put, not lean the other way.**
3. **Walk. It must come with you, not sink to the floor or veer.**
4. **`-NoHandPosT` reproduces today's inversion on purpose.**

> **WHAT THIS DOES NOT CLAIM:** it does not explain *"it sticks to the ground"*
> **as a resting height** (`[REPORTED]` `want=(8.0, -65.0, -45.5)` is 0.65 m below
> the head centre, which is a grip/height question and belongs with `-GunOffY`),
> and it does not touch the aim ray, which `193` §1 measured as correct across 55
> shots. **It fixes where the gun IS, not where it points.**

---

## §4 — THE STEREO BANNER WAS A FALSE ALARM, AND THE WEARER CALLED IT

`[REPORTED]`: *"ignore that anyway because it was the log for the previous run."*
**HE IS RIGHT, `[MEASURED]`.** `vr.ps1`'s `Show-GeVrVerdict` runs against the
EXISTING log **at launch time** — its own comment says *"it arrives at the moment
you are deciding what to launch"* — **so the verdict shown describes the PREVIOUS
session.** The run under discussion reads
`render passes: eye0=91 eye1=91` on **139 samples**, `90.0 fps`,
`VRGATE/s ... -> stereo=90 | OK`, `layout OK`.

> **AND THE WEARER'S SECOND POINT IS THE IMPORTANT ONE:** *"this issue is gonna do
> the same thing no matter what build we're in. As long as it's VR, it's going to
> show you those problems."* **He is right about that too, and `182` says so:**
> the yaw/roll inversion is a MONOCULAR observation — where the gun sits relative
> to your view — and needs no stereo to be valid. **`179`'s voiding applies to
> DEPTH and FUSION judgements, not to every observation made in a headset.**
> **Reaching for a "the run is void" banner to set aside a report that is
> reproducible in every build would have been the worst mistake available here.**

---

## §5 — WHAT IS OWED

1. **BUILD ONCE. `G-197`** (§3) — turn, tilt, walk. Then `-NoHandPosT` for the
   before.
2. **`G-196`** (`196` §4) — the room term, now in the correct frame.
3. **`G-194`** (`195` §2) — the bullet, from a mark.
4. **`T9` / `-SeamCompose 1`** — **STILL SEPARATE AND STILL OWED.** The rotation
   half. **`197` may reduce it or may not; they are independent terms.**
5. **THE RESTING HEIGHT** (§3's caveat) — `-GunOffY`, and only with `G-197`
   passing, because a gun that counter-rotates cannot be judged for height.
6. **`B1`**, then `U-18`. **`noPose`/`U-21`/`U-22`** on any build.

**NOTHING STAGED. THE COMMIT IS THE OWNER'S**, both repos.
