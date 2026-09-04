# 61 — the controller slice: VR controllers to the N64 pad, and the aim pose

**PLAN, 2026-08-23. Nothing built. Written to be discussed, then executed.**

Prioritised ahead of B1 by decision: **controller work does not depend on
stereo.** Hand aim drives `crosshair_x_pos` / `crosshair_y_pos`; B1 is a defect
between the view matrix and the pixels in a render target. Neither touches the
other, and a build with one image in both eyes is perfectly good for tuning
aim — it just looks monoscopic while you do it. **Treating the two as one
milestone is what has made them feel circular.**

Read `38` before this document; `37` is the concept and `38` corrects it in
three places.

---

## What exists today

**Nothing.** `src\main\ge_vr_xr.cpp` is 1369 lines and contains **no**
`XrAction`, no `xrCreateAction`, no `xrSuggestInteractionProfileBindings`, no
`xrSyncActions`. `39` O4 has said "not started" and it is accurate.

The host side is better than expected:

| | |
|---|---|
| `recomp::get_input_digital(InputField)` / `get_input_analog(...)` | `src\game\input.cpp:632-691`. **Every** button and axis the game reads passes through here, against binding tables |
| `recomp::poll_inputs()` | `:490`. Once per frame, on the game/input thread |
| The XR frame loop | on **RT64's present thread**, via the render hook — `rt64_render_context.cpp` |

**So there is a thread boundary, and it is the same one the head pose already
crosses.** Head pose is produced in the XR loop and published through shared
atomics for the render side to consume. Controller state must do exactly the
same: **read in the XR frame loop, publish a snapshot, consume in
`poll_inputs()`.** Reading OpenXR state from the input thread would be a second
mechanism for a problem already solved once — `48` rule 8, do not synchronise
two things, remove the second one.

## The two rules this slice inherits

**Chain, never replace** (`27`): the VR contribution is OR-ed into the digital
result and summed into the analog result. With no XR session the contribution is
zero and `get_input_*` behaves exactly as today. **`-NoXr` must be
bit-identical.**

**Surface the aim pose NOW, even though nothing consumes it** (`37` item 1). It
is a few lines at binding time and every later slice — hand aim, the scope
gesture, two-handed hold — needs it. Building the bindings twice because the
first pass only wanted buttons would be silly, and `37` said so before there was
any code to regret.

---

## The design

### Action set: one, `gameplay`

| Action | Type | Purpose |
|---|---|---|
| `aim_pose` | pose | **The one everything later needs.** `.../input/aim/pose`, both hands |
| `grip_pose` | pose | For the scope gesture and hand presence later |
| `move` | vec2 | left stick → N64 analog stick |
| `turn` | vec2 | right stick → body yaw (snap or smooth, host-side) |
| `fire` | bool | trigger → Z |
| `use` | bool | A / X |
| `crouch`, `reload`, `weapon_prev/next`, `menu`, `recentre` | bool | the rest of the pad |

**Interaction profiles suggested, in this order:** Oculus Touch, Valve Index,
HTC Vive, and `khr/simple_controller` as the guaranteed fallback. Suggesting
several costs nothing — the runtime picks the one that matches the hardware
present — and the fallback means the slice cannot fail closed on an unknown
controller.

### Where each piece lands, and why

| Concern | Owner | Licence |
|---|---|---|
| Action set, bindings, `xrSyncActions`, pose spaces | `ge_vr_xr.cpp` — **host** | GPL side. Fine: it is OpenXR, which never belongs in RT64 |
| The published snapshot | `ge_vr_host.h` shared state, like the head pose | host |
| OR-ing into the pad | `input.cpp`, inside `get_input_digital` / `get_input_analog` | host |
| RT64 | **untouched by this slice** | — |

**RT64 is not modified at all here**, which keeps the MIT half clean and means
this slice cannot regress B1 or the render path. That is worth having while a
render bug is open.

---

## THE GATES — written before the code

Each one asks `48`'s question: **what would a working build have to do
differently for this to fail?**

| # | Gate | A working build fails this only if... |
|---|---|---|
| **G1** | `gevr.log` prints the interaction profile the runtime actually bound, by name, once per session: `xr input: bound profile = /interaction_profiles/oculus/touch_controller` | ...bindings were suggested but none matched. **A build with no controllers connected prints "NONE BOUND" rather than staying silent** — an instrument must be able to say it cannot answer (`48`, earned by `52`) |
| **G2** | With a controller held and moved, `xr input: aim L pos=.. quat=..` changes at 90 Hz and is finite | ...the pose action exists but was never located against the reference space, which prints a plausible constant |
| **G3** | **Every** action fires: press each binding and the log names it once, on change. A button whose line never appears is a binding that silently did not attach | ...a suggested binding was accepted and mapped to nothing — the failure mode that produces "half the buttons work" |
| **G4** | **`-NoXr` is bit-identical.** Same key/pad behaviour, same log, no `xr input:` lines at all | ...the VR contribution is not actually gated on an XR session, i.e. the chain became a replace |
| **G5** | Worn: the game is playable from the VR controller alone — move, look, fire, crouch, switch weapon | the whole point |

**G3 is the gate that matters most**, and it is the one a naive implementation
passes by accident: bindings that fail to attach do not error, they just never
fire. Without the per-action line, the first symptom is a button that does
nothing in a headset, half an hour into a wear test.

## Explicitly NOT in this slice

- **Hand aim.** `38` leaves three things unread — which of `bondview2.c:6072` /
  `:6077` is aim mode, whether `crosshair_x_pos` has other readers, and whether
  `getPlayer_c_screenwidth()` is affected by the patch. **All three are reads,
  not experiments, and all three block hand aim.** They do not block this slice.
- **Auto-aim and `gunaimdamp`.** Knobs, tuned once hand aim exists (`37` trap 2).
- **The scope.** Its own phase, RT64-side (`37` trap 3).
- **The ±30 degree aim clamp** (`38` correction 3). A real design constraint, and
  the interaction question it raises — what happens when you point past the
  limit — is not answered here and should not be answered by accident.

## Risks, named before they bite

1. **Pimax OpenXR 0.1.0 is a young runtime.** Its controller support is not
   established here. G1 exists so that failure is a named line rather than a
   confusing wear test.
2. **`xrSyncActions` needs the session focused.** Unfocused sessions return no
   input, legitimately — so the log must distinguish "no input" from "not
   focused", or a normal state reads as a bug.
3. **The pad tables assume SDL device semantics.** The chain point must be
   chosen where the VR contribution cannot be clobbered by an SDL read in the
   same frame — `21`'s rule, sixth instance.

## Before any code — one question only the user can answer

**Which controllers physically exist on this rig?** Pimax Crystal Super ships
with its own; Index and Touch controllers are also commonly paired through
SteamVR. It changes which profile is expected to bind, and therefore whether G1
passing with a *fallback* profile is a success or a warning sign.

The slice does not depend on the answer — several profiles get suggested
regardless — but **reading G1's output does.**

---

# AMENDMENT — hardware answered, profiles researched

**Rig: Pimax Crystal Super's own controllers. Also a Quest 3. Both to be
supported; Pimax is the test device.**

## The profile list, and why each is in it

| Profile | For | Confidence |
|---|---|---|
| `/interaction_profiles/valve/index_controller` | **Pimax, primary** | Good, and it matches the user's own research. PimaxXR's Control Center carries an option to *"force using Windows Mixed Reality or Oculus motion controllers buttons bindings for applications without correct Vive or Index motion controller bindings"* — an option that only makes sense if **Vive/Index is what the runtime presents natively**, with WMR/Oculus as the fallback it can force |
| `/interaction_profiles/htc/vive_controller` | Pimax, secondary | Same sentence names Vive alongside Index |
| `/interaction_profiles/oculus/touch_controller` | **Quest 3** | Quest 3 through SteamVR/Link is widely reported to present as "Oculus Touch Legacy", i.e. this profile |
| `/interaction_profiles/meta/touch_controller_plus` | Quest 3, native Meta runtime | Only if the runtime advertises the extension. **Must be guarded** |
| `/interaction_profiles/khr/simple_controller` | Anything | The guaranteed floor: select + menu + pose. **The slice cannot fail closed** |

**Binding to Index for Pimax and Touch for Quest costs nothing extra** — a
runtime simply ignores suggestions for profiles it does not implement, and picks
the one matching the hardware present.

## The wrinkle, and it decides how the code is written

**`xrSuggestInteractionProfileBindings` FAILS for a profile the runtime does not
know** — `XR_ERROR_PATH_UNSUPPORTED` on `xrStringToPath`, or a rejected
suggestion. A single "suggest everything, check one result" implementation
therefore fails **entirely** on the first unknown profile, which on a young
runtime is likely.

**So each profile is suggested independently, in its own call, and a failure is
LOGGED AND SURVIVED, never fatal:**

```
xr input: profile valve/index_controller      SUGGESTED ok
xr input: profile meta/touch_controller_plus  UNSUPPORTED by this runtime (skipped)
xr input: profile khr/simple_controller       SUGGESTED ok
xr input: bound profile = /interaction_profiles/valve/index_controller
```

**That last line is G1** and it is read from `xrGetCurrentInteractionProfile`
after the session is focused — the runtime's own answer to "what is actually
attached", rather than our guess. **On this rig it should say Index. If it says
`khr/simple_controller`, the slice still works but only the floor bindings are
live, and that is a warning, not a success** — which is exactly why the user's
answer to "which controllers" was needed before reading the log, not before
writing the code.

## Auto-aim: an OPTION, not a decision — and the crosshair question underneath

The user's read is right and better than `37`'s. `37` predicted auto-aim would
"fight a tracked hand" and recommended expecting to turn it off. That prediction
is **untested**, and it interacts with something `37` did not consider:

> **In VR there is currently no crosshair at all.** On a flat screen the
> crosshair is what makes precise aim possible; auto-aim compensates for a
> thumbstick. With a tracked hand and no crosshair, auto-aim may be doing the
> job the missing crosshair would otherwise do.

So the three cases are genuinely different and only testing separates them:

1. **Aim is accurate and a dot exists** → auto-aim probably off; it will fight.
2. **Aim is accurate, no dot** → auto-aim may be what makes it usable.
3. **Aim is imprecise** → auto-aim is a crutch and the aim needs fixing first.

**Therefore: a runtime knob, defaulted ON, and no opinion baked in.**
`currentPlayerSetXAutoAimEnabled` is already a setter (`37` trap 2), so this is
a binding rather than surgery. **Decide it from a wear test, not from this
document.**

### The dot is feasible, and it is the more interesting half

A world-space aim indicator is well-trodden in VR shooters, and this project
already has most of what it needs: `bullet_path_from_screen_center` returns a
**camera-space direction** (`38`), so the ray the game will actually fire is
already available in the right space to draw. Two shapes, in increasing cost:

- **A laser or dot along the fired ray** — drawn from the gun, hitting the world
  where the shot would land. Honest by construction: it shows the game's own
  ray, not a guess at it.
- **Re-using the game's own crosshair**, projected to that point.

**Not this slice.** It needs hand aim to exist first, and it is worth its own
plan because "what the dot shows" and "what the gun does" must be the same
quantity or it is a lie that reads as bad aim. **Recorded so the auto-aim
decision is not made before the option that changes it exists.**

---

# AMENDMENT 2 — the knobs are CONFIG, not three more environment variables

**Folded in by decision, before any code.** `62` establishes that the menu and
the config system are ours to edit, and that the env-var workflow is why every
test costs a relaunch from PowerShell.

**If this slice adds `GE_VR_SNAP_TURN`, `GE_VR_AUTOAIM` and
`GE_VR_HANDEDNESS`, it makes that worse** — and it makes them worse in the place
it hurts most, because turn style and auto-aim are exactly the settings that can
only be judged while wearing the headset.

## The decision: our own `vr.json`, hot-reloaded

**Not `graphics.json`.** That file belongs to the recomp, the in-game menu
rewrites it (`43`), and its rewrite has already destroyed stereo once. Putting VR
preferences in it means sharing a file with a writer we do not control.

```
%LOCALAPPDATA%\GoldenRecomp\vr.json          ours, and nothing else writes it
```

**Re-read when its modification time changes**, checked once a second on a thread
that already ticks. That is a few lines, it needs no UI, and it delivers the
thing a settings page was wanted for:

> **Change a value while wearing the headset, and the game changes. No relaunch,
> no taking the headset off, no walking back to the spot.**

**Every wear test this project has run has been one configuration and one
impression.** A value that can be changed while worn turns a wear test into a
comparison, which is the difference between "it feels off" and a number.

## Precedence, and it is logged

```
environment variable   (DIAGNOSTIC - always wins, always announced)
  > vr.json            (PREFERENCE)
    > built-in default
```

**Each value logs where it came from, once:**

```
xr config: snapTurn = 30.0 deg      (vr.json)
xr config: autoAim  = ON            (default)
xr config: unitsPerMetre = 100.0    (ENV GE_VR_UNITS_PER_METRE - diagnostic override)
```

**This is the `32` problem solved rather than warned about.** `vr.ps1` already
clears every `GE_VR_*` variable before each run precisely because *"a leftover
from a previous experiment is otherwise indistinguishable from a change that did
not work, and that has already cost one wrong diagnosis."* Printing the SOURCE
of every value removes the ambiguity instead of managing it.

## What moves into `vr.json` in THIS slice

Only what this slice creates. **No migration of the existing diagnostic knobs** —
`-SkipEye`, `-PresentEye`, `-Offset` are diagnostics and belong exactly where
they are.

| Value | Default | Why it is a preference |
|---|---|---|
| `autoAim` | **ON** | Undecided by design — the wear test decides, and it needs to be flippable mid-session to be decided at all |
| `turnStyle` | `snap` | Comfort. Varies per person, and per person per day |
| `snapTurnDegrees` | 30 | ditto |
| `handedness` | `right` | Which hand holds the gun |
| `deadzone` | small | Stick feel |

## Two extra gates

| # | Gate | Fails only if... |
|---|---|---|
| **G6** | Edit `vr.json` while the game is running; the log prints the new value and the behaviour changes **without a relaunch** | ...the file is read once at startup, which is the thing this amendment exists to prevent |
| **G7** | Every value prints its source. Set one by env var and it must say `ENV ... diagnostic override`, not `(vr.json)` | ...precedence is wrong, or is right but silent — and a silent precedence is `32`'s wrong diagnosis waiting to happen again |

## Deliberately still deferred

**The RmlUi settings page.** Hot-reloaded JSON gets the value — tuning while
worn — for a fraction of the work, and a UI page can be added later on top of a
config system that already exists. Building the page first would be building the
expensive half of the feature for none of the benefit.

**`62`'s slices stay separate.** The MSAA guard covering `-Flat` (O46) is a
behaviour change to the render path and must not ride along with a controller
slice. One behaviour change at a time.

---

# AS BUILT — 2026-08-23 11:31. Builds clean, untested in a headset

## What was built

| File | What |
|---|---|
| `include\ge_vr_host.h` | `ControllerInput` + `publish_controller_input` / `controller_input`. Same mutex-snapshot transport as `HeadView`, across the same thread boundary |
| `src\main\ge_vr_xr.cpp` | Action set, 8 boolean + 2 float + 2 vec2 actions, aim and grip pose actions per hand, four interaction profiles suggested INDEPENDENTLY, `xrSyncActions` per frame at the views' `predictedDisplayTime`, pose location in the recentred space, and ordered teardown |
| `src\game\input.cpp` | The chain into `controller_button_state` / `controller_axis_state` |

## The decision that made this small

**VR actions publish as SDL ids**, and the chain goes into the two functions
every binding already passes through. Consequences, all of them good:

- **The user's existing bindings apply to the headset.** No new `InputType`, no
  new binding UI, no change to how settings serialise, and a rebind done for a
  gamepad is automatically a rebind for the controllers.
- **Movement, turning and firing needed no new code at all** — the game already
  maps left stick, right stick and buttons. The VR controller simply becomes a
  second gamepad.
- **`-NoXr` is bit-identical by construction**: with no session every published
  field is zero, so the OR and the sum contribute nothing.

`ge_vr_xr.cpp` writes the SDL ids as literals so it need not include SDL, and
`input.cpp` carries `static_assert`s for every one of them. **If SDL renumbers,
it fails to COMPILE rather than silently mapping fire onto crouch** — rule 6,
which has cost this project six rounds, turned into a build error.

## DEVIATION from amendment 2 — `vr.json` NOT built, and why

Amendment 2 folded a hot-reloaded `vr.json` into this slice. **It was not
built, and the reason is a consequence of the SDL-id decision above.**

**This slice creates no preferences.** Turn style, movement and firing are all
handled by bindings the recomp already has; auto-aim and hand aim belong to
later slices; the diagnostics stay environment variables by design. **`vr.json`
would have nothing to hold.**

Building an empty config system now would be building a mechanism with no
consumer — which is `32`'s defect (a knob whose consumer does not exist) created
deliberately instead of by accident. **`vr.json` moves to the first slice that
creates a real preference**, which is the auto-aim toggle. Amendment 2's design
stands as written; only its scheduling changes. **G6 and G7 move with it.**

## Gate status

| Gate | State |
|---|---|
| G1 profile named in the log | **built, untested** — needs a headset |
| G2 aim pose located and changing | **built, untested** |
| G3 every action names itself on first fire | **built, untested** |
| G4 `-NoXr` unaffected | **SMOKE PASSES.** Launched, ran to the menu, 60 Hz VI steady, **zero `xr input` lines**. Full pass needs a play session |
| G5 playable from the controllers alone | **untested** — the wear test |
| G6, G7 | **moved** with `vr.json`, above |

## What to expect in the headset, so nothing reads as a bug

- **Monoscopic.** B1 is open; both eyes still carry one image. Aim and input can
  be judged; depth cannot.
- **Do not quit from the pause menu.** O45 blanks the screen on the VR path.
  Close the window instead.
- **`bound profile =` is the first line to read.** Index expected on this rig.
  `khr/simple_controller` means only select/menu/pose attached — playable, but a
  warning, not a success.
- **A button that does nothing and never logs a line is a binding that did not
  attach**, which is exactly what G3 exists to make visible.
