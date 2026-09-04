# 101 — THE AIM BUTTON IS SLICE A1's ENTRY POINT, ALREADY WRITTEN AND SHIPPED

**2026-08-24. Found by the WEARER, from inside the headset, by holding the aim
button and moving the stick. Read `90` and `87` first; this changes A1's
options, not its physics.**

## §1 — WHAT HE NOTICED

> ***"If you hold the aim button then move the joystick you get direct control
> of the aiming direction of the gun."***

**He is right, and the code says so in one hop.** `bondview2.c:6039-6078`:

```c
if (moveData.canSwivelGun)      { controldef = CONTROLLER_CONFIG_HONEY; }  /* hip fire */
else if (moveData.canManualAim) { controldef = CONTROLLER_CONFIG_KISSY; }  /* AIM MODE */

if (controldef == HONEY) {                       /* autoaim, swivel, speedtheta */
    sub_GAME_7F067F58(sp70, ftemp, MAX_AIMLOCK_SPEED_DEFAULT);
}
else if (controldef == KISSY) {
    sub_GAME_7F067FBC(stickX * 0.65f / 80.0f,    /* <-- DIRECT. NO AUTOAIM. */
                      stickY * 0.65f / 80.0f);
}
```

**`canManualAim` is `insightaimmode` — the aim button.** `88` found this split
was **controller config, not auto-aim-vs-manual**, and that finding is what makes
the KISSY branch readable as an input path rather than an aiming mode.

## §2 — AND THE ENTRY POINT LANDS EXACTLY WHERE `86` ALREADY AIMED A1

`gunfire.c:4756`:

```c
void sub_GAME_7F067FBC(f32 turn_x, f32 turn_y) {
    item_stats  = get_ptr_item_statistics(getCurrentPlayerWeaponId(GUNRIGHT));
    guncrossdamp = item_stats->CrosshairSpeed;
    gunaimdamp   = item_stats->AimLockSpeed;
    caclulate_gun_crosshair_position_rotation(turn_x, turn_y, guncrossdamp, gunaimdamp);
}
```

> **It is a nine-line wrapper around the EXACT function `86` chose for A1 route
> 1** — `caclulate_gun_crosshair_position_rotation`, `gunfire.c:4666` — **and it
> already fetches the correct PER-WEAPON damping for both integrators.**

**`87` finding 1 said A1 must drive BOTH `crosshair_x_pos` (`guncrossdamp`) and
`gun_azimuth_angle` (`gunaimdamp`) or the gun and the shot disagree by
construction. This function does both, with the right constants, in shipped
code that every player has exercised.**

**It also completes `88`'s dead-code family.** `88` found `sub_GAME_7F0680D4` has
no callers and called it *"A1's whole job already written, but UNTESTED engine
code."* **`sub_GAME_7F067FBC` is the same job and it is NOT untested — it runs
every time anybody holds the aim button.**

## §3 — THE HONEST DIFFERENCE FROM PERFECT DARK'S METHOD

**They are not the same technique and the choice is real.**

| | **PD / `38` — OPEN LOOP** | **KISSY entry — CLOSED LOOP** |
|---|---|---|
| How | Invert the damping and write the absolute value: `crosspossum = x_ndc / (1 - crossdamp)` (`bondgun.c:8408`) | Feed a per-tick **delta** — `(desired - current)` — and let the engine's own damping converge |
| Needs | The damping model to be exactly right, and direct writes to internals | Only the shipped entry point |
| Behaviour | Lands in **one frame**. Exact | **Converges over frames.** Self-correcting: a wrong gain is slow, not wrong |
| Failure mode | A model error is a permanent aim offset | A gain error is lag or overshoot, **visible and tunable by the wearer** |
| Patch cost | Patch `caclulate_gun_crosshair_position_rotation` — **69 lines, and `86` costed a NEW PATCH NAME and a long build** | **Possibly no patch of that function at all.** It is called, not modified |

**`38`'s inversion is confirmed by independent prior art and is not in doubt.
This is a second route to the same place, and it trades exactness for using only
code the game already trusts.** `48` rule 8's shape: prefer the mechanism that
already exists to a second one that must agree with it.

## §4 — WHAT DOES NOT CHANGE, SO NOBODY READS THIS AS A SHORTCUT

1. **THE CLAMP IS STILL THERE.** `90`: `crosshair_angle` is clamped at
   `gunfire.c:4699-4715` and **it is the bullet**. Routing through KISSY does
   not escape it. **SLICE A2, THE WORLD-SPACE AIM DOT, IS STILL NOT OPTIONAL.**
2. **HONEY AND KISSY MUST NOT BOTH RUN.** `bondview2.c:6044` picks one per
   frame. Calling `sub_GAME_7F067FBC` ourselves while the stock code runs the
   HONEY branch means two writers to the same integrators in one frame —
   **`48` rule 6, which has caught this project five times** (`21`, `26`, `27`,
   `32`, `38`).
3. **VERSION TRAP, worth naming now.** The damping fetch is `#if`-split: US
   takes `CrosshairSpeed`/`AimLockSpeed`; **EU hardcodes `0.7651f` and shifts
   `CrosshairSpeed` into the other slot.** Anything derived from these constants
   is US-only unless it reads them the way this function does.
4. **`muzzleExt` IS STILL UNREAD.** It decides G2's shape, not A1's — but A1's
   gates are judged by looking at the gun, and `90` says the gun model can point
   somewhere the bullet does not.

## §5 — WHAT THE NEXT SESSION SHOULD DO WITH THIS

**Nothing yet. `48` rule 1: plan, discuss, then execute.** The reads owed:

| # | Read | Why |
|---|---|---|
| **A1-R1** | **What sets `insightaimmode`, and can it be held true under VR without the button?** If aim mode can simply be ON in VR, the KISSY branch drives itself and we only supply the deltas | Decides whether this is a hook or a patch |
| **A1-R2** | **What are `MAX_AIMLOCK_SPEED_DEFAULT` and the `0.65f/80.0f` scaling in real units?** The delta we feed must be in the same units as a stick | Decides the gain, and a wrong gain is `77`'s "it looks the same" all over again |
| **A1-R3** | **Does the KISSY branch disable anything else we want** — `canLookAhead`, `canNaturalTurn`, `canSwivelGun` are all forced false in aim mode (`bondview2.c:4923-4937`) | **Aim mode changes MOVEMENT too.** Free aim must not silently cost the player their turning |

**A1-R3 is the one that could kill it**, and it is the reason this is a route and
not a decision. **The wearer found the mechanism; the reads decide whether it is
usable without taking something else away.**

---

# §6 — THE OWNER'S DESIGN, AND WHERE THE "ROTATION SPHERE" ACTUALLY IS

> ***"Grab button on the controller activates the modded KISSY — kissy is
> normally stuck on a rotation sphere, we need that lock to break and allow free
> movement of the arm/gun — then the trigger to shoot."***

**`caclulate_gun_crosshair_position_rotation` read in full, `gunfire.c:4666-4734.
The design survives, and the lock is SIXTEEN LINES — but it is not on the arm.**

## §6.1 — THE ARM IS ALREADY FREE. ONLY THE BULLET IS LOCKED.

**The function computes TWO things from the same input and clamps only one:**

```c
/* THE BULLET - clamped to the screen rectangle, 3 px in from every edge */
crosshair_angle.f[0] = (crosshair_x_pos * (1 - guncrossdamp) * w * 0.5f) + w*0.5f;
if (crosshair_angle.f[0] < 3.0f)            crosshair_angle.f[0] = 3.0f;
else if (w - 4.0f < crosshair_angle.f[0])   crosshair_angle.f[0] = w - 4.0f;
   ... same for y ...

/* THE GUN MODEL - NO CLAMP. NONE. */
field_FFC.x = (gun_azimuth_angle * (1 - gunaimdamp) * w * 0.5f) + w*0.5f;
field_FFC.y = (gun_azimuth_turning * (1 - gunaimdamp) * h * 0.5f) + h*0.5f;
transformAndNormalizeByLength2Dto3D(&field_FFC, &coords, 1000.0f);
sub_GAME_7F067AB4(&coords);          /* -> hands[0].field_A38/A3C/A40 */
```

**`90` said this and now it is read end to end: `field_FFC` is unclamped and it
is what points the ARM. So "free movement of the arm/gun" needs NO lock broken
at all — `85` already moves it and the engine already aims the model at the
resulting point.** The thing that is locked is **where the bullet goes.**

**And the `1000.0f` closes a loop from this morning:** it is the length that
produces `field_A40`, which S0 measured at **−1000**. The instrument confirmed
the constant in the function the instrument was built to investigate.

## §6.2 — THE LOCK IS 16 LINES, AND REMOVING IT IS NOT OBVIOUSLY WRONG

**`76` offered three options for the clamp and said none was chosen; `86` §3.8
found PD chose none of them either and answered with a world dot.** Reading it
now adds something neither had:

**The clamp is a DESIGN choice, not a mathematical necessity.**
`transformAndNormalizeByLength2Dto3D` is a pinhole un-projection — screen point
to view ray. **It extrapolates perfectly well outside the screen rectangle.**
Deleting the clamp yields a valid ray up to the point where the tangent
diverges, near ±90 degrees off axis.

**So the honest position: the lock CAN break. What is unknown is what else
breaks with it.** `90` counted **eight call sites** reading `crosshair_angle` —
the drawn crosshair, auto-aim target selection and the hit path among them. **A
crosshair at pixel −400 is a valid ray and an invalid screen position**, and
`48` rule 6 is that this project has been bitten five times by exactly that:
a value someone else reads back.

**That is the read A1 owes before anyone deletes sixteen lines.**

## §6.3 — THE DESIGN, RESTATED IN THIS PROJECT'S TERMS

| His step | What it becomes | Cost |
|---|---|---|
| **Grip activates modded KISSY** | Force `insightaimmode` true from the VR input path instead of from the aim button. **A1-R1** already asks whether it can be held true | Small, if R1 says yes |
| **Free arm/gun** | **Already exists.** `field_FFC` is unclamped and `gunfire.c:568` aims the model at the derived point — `88`, and `85`'s `-SeamNoRot` was the wearer refusing to fight it | **Zero** |
| **The bullet follows the arm** | Feed the controller-derived screen point to BOTH integrators through `sub_GAME_7F067FBC` — §2 — and **then decide the clamp** | The slice |
| **Trigger to shoot** | Already bound. `61`, five actions firing | **Zero** |
| **Break the lock** | Delete or widen `:4699-4715` — **only after the eight-reader read** | Unknown until read |

**The gap between "the arm is free" and "the bullet follows" IS slice A1. It is
the only part of his description that is not already in the build.**

## §6.4 — AND A TIMEBASE COLLISION WORTH SEEING NOW, NOT LATER

```c
for (i = 0; i < g_ClockTimer; i++) {
    crosshair_x_pos = (crosshair_x_pos * guncrossdamp) + turn_x;
}
```

**BOTH integrators step in a loop counted by `g_ClockTimer`** — the quantum.
**This is the exact line `92` §4 meant by *"changing the quantum changes the aim
feel of every weapon"*, and `99` §4.1's fractional-tick variant cannot drive a
loop at all.**

> **So the aim work and the timebase work touch the same four lines.** Whichever
> is built second must know what the first one did to them. **Recorded here so
> the collision is found at the plan stage rather than by a wearer reporting
> that reloading feels wrong.**
