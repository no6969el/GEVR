# 34 — step 3f-5 plan: recentre, and separating the head from the eyes

**PROPOSAL, 2026-08-22. NOTHING BUILT.** `33` diagnosed; this is what to do about
it. Read the gates before the design — if a gate here is one a *working* build
would fail, the design is wrong and the code should not be written.

Decisions taken from `33`'s menu:

| Question | Chosen |
|---|---|
| The 4.55 m origin | **Recentre and instrument in one slice** |
| `-NoHeadTranslate` | **Split — keep stereo, drop body position** |
| Automatic capture | **First frame with valid *and tracked* flags** |
| The key | Automatic on first frame, **plus a bindable manual recentre** |

---

## What is actually wrong, restated in one line

`views[eye].position` bundles two independent facts — **where the head is** and
**where that eye sits relative to the head** — and every use of it so far has
treated the pair as one quantity. `33`'s 4.55 m error lives in the first;
the correct 3.17-unit separation lives in the second. Both bugs, and one
misleading flag, come from never having separated them.

**So the slice is the separation, and the recentre falls out of it.** That
ordering matters: build the recentre alone and the same conflation is still
sitting there waiting.

---

## Design

### 1. Decompose, once, in one place

In `ge_vr_update_config`, before the per-eye loop:

```
centre[i]     = (position[0][i] + position[1][i]) * 0.5      // where the head is
eyeOffset[eye][i] = position[eye][i] - centre[i]             // ±half IPD
```

`|eyeOffset[0] - eyeOffset[1]|` is exactly the `eye sep` the log already prints,
so **the decomposition is verifiable against a number we have already measured**
rather than against an argument. That check is Gate 1.

### 2. Recentre the centre, not the eyes

```
effective[eye][i] = (centre[i] - origin[i]) + eyeOffset[eye][i]
```

Subtracting the origin from the **centre** rather than from each eye position
makes it structurally impossible for a recentre to disturb the IPD. Subtracting
it from each eye separately would give the same answer today and would be one
refactor away from not doing.

`origin` is captured once, from `centre`, on the first frame that is both valid
and tracked.

### 3. Valid is not tracked — and the difference is the whole risk

`ge_vr_xr.cpp:509` already gates publication on
`XR_VIEW_STATE_POSITION_VALID_BIT | ORIENTATION_VALID_BIT`. **Valid means the
numbers are meaningful; tracked means they are currently being measured rather
than extrapolated from a stale pose.** A capture taken on a valid-but-untracked
frame bakes a guess in for the session — and would look exactly like the bug
being fixed here, which is the worst possible failure mode for a fix.

So `HeadView` gains a `tracked` flag from
`XR_VIEW_STATE_POSITION_TRACKED_BIT | ORIENTATION_TRACKED_BIT`. **The publish
gate is not changed** — 3f-4's behaviour stays exactly as worn — the flag is
added alongside and only the capture consults it.

### 4. Recentre yaw. Do NOT recentre pitch or roll

This was not in the menu and it should have been, so it is called out rather
than buried.

`LOCAL`'s yaw origin is whatever heading SteamVR's zero pose has. The game's
forward comes from the gamepad. If the two disagree by a constant, **you are
permanently looking off-axis from where the gun points** — a second, quieter
component of "the view is broken" that a position-only recentre would leave
behind, and that nobody would connect back to calibration.

Pitch and roll are different: `LOCAL` is **gravity-aligned**, so their origins
are physically meaningful and already correct. Cancelling them would tilt the
horizon permanently and lock the tilt to wherever your head happened to be at
capture. That is worse than the disease, and it is the mistake a symmetrical
"recentre all three axes" would make without anyone noticing until they wore it.

Yaw-only recentring is therefore the design, and it gets a knob —
`GE_VR_RECENTRE_YAW=0` — because the yaw *convention* has no more evidence
behind it than the rotation convention `30` gave three sign knobs to.

### 5. What `-NoHeadTranslate` becomes

```
GE_VR_HEAD_TRANSLATE=0   ->   effective[eye] = eyeOffset[eye]
```

Centre contributes nothing; the ±IPD survives. Rotation and stereo, fixed
viewpoint. **This is a behaviour change to a flag that has been worn**, so `30`'s
description of it becomes wrong and is corrected in the same commit.

### 6. The manual key

One case beside the existing `F11` handling in `sdl_event_filter`
(`src/game/input.cpp:112`). Default **F9**, overridable by
`GE_VR_RECENTRE_KEY` as an SDL scancode, so a clash costs a relaunch and not a
rebuild.

Keyboard only. A gamepad binding has to go through the remapping UI and the
saved-config path, which is a different concern in a different file, and this
slice should not grow one.

### 7. The instrumentation — the half that pays for itself later

The existing once-a-second line gains the **raw** centre beside the corrected
one:

```
[gevr] head: y=0.4 units (raw 227.7, origin 227.3) | eye sep 3.17 units
```

Cheap, and it distinguishes three failures that are indistinguishable by feel:

- **Raw jumps, corrected holds still** → SteamVR re-zeroed mid-session. Working
  as designed; the recentre absorbed it.
- **Raw holds still, corrected drifts** → our arithmetic. Ours to fix.
- **Origin far from the first raw sample** → the capture took a bad frame, which
  is precisely what §3 exists to prevent, reporting itself.

`33` chose "recentre + instrument" so that the diagnosis of the 4.55 m falls out
of ordinary play. This line is that diagnosis.

---

## Gates, written before the code

| # | Check | Pass | What would have to be different to fail |
|---|---|---|---|
| 1 | `eye sep` after the split | **Still 3.17 at 50 u/m** | The decomposition would have to be wrong — and this compares it against a number already measured, not against reasoning |
| 2 | `y` at session start | **Within a few units of zero** | The origin is not being subtracted, or is captured from the wrong quantity |
| 3 | Crouch | `y` goes clearly negative; `raw` moves with it | Only the origin is live and the pose is not |
| 4 | Look at a wall, press F9 | Position unchanged, **yaw snaps to game-forward** | Yaw recentring inverted or not applied |
| 5 | `GE_VR_RECENTRE_YAW=0`, press F9 | Position recentres, **heading does not move** | The knob does not reach the transform |
| 6 | `-NoHeadTranslate` | Rotation works, leaning does nothing, **stereo present** | The split is not reaching the flag — this is the gate on §5, and note it is the exact opposite of `32`'s claim about this flag |
| 7 | `-NoHead` | Byte-identical to 3f-3 | The new path is running when it must not |
| 8 | `.\vr.ps1 -NoXr` | 60 fps, clean close | Input.cpp edit reached the non-VR path |

Gate 6 is the one worth staring at. `32` told you `-NoHeadTranslate` kills depth,
and after this slice **that becomes false on purpose.** A gate that contradicts
a document written two hours earlier is exactly the kind that catches a slice
that only half landed.

Gate 8 is there because this is the first slice to touch `input.cpp`, which is on
the path that must never break.

---

## Risks

1. **Yaw sign.** No more evidence than `30`'s rotation convention had. Hence
   Gate 4, Gate 5, and the knob.
2. **`input.cpp` is shared, non-VR code.** Every prior slice kept host changes in
   VR-only files. Gate 8 exists for this and the key handler returns immediately
   unless `GE_VR_XR` is set.
3. **The capture can still be wrong** if the very first tracked frame is bad.
   Not prevented, but §7's `origin` print makes it *visible*, and F9 clears it.
4. **A stale origin after SteamVR re-zeroes.** The automatic capture is one-shot
   by design. F9 is the answer, and §7's raw-vs-corrected line is how you know
   to press it.

---

## What this does not do

- **It does not decouple aim from view.** Still Phase 3, still the patch.
- **It does not clamp head translation** (`31`). Deliberately: a clamp would have
  reduced the 4.55 m to a smaller wrong number and made the cause *harder* to
  find. Clamping is right once the origin is trustworthy, and not before.
- **It does not touch the viewmodel**, or the 60-vs-90 Hz target framerate `33`
  noticed. Both are separate and neither is what makes the view unusable.

---

## Build

Existing files only, no new `RECOMP_PATCH` name, no new source file:

```powershell
cmake --build build --target GoldenRecomp --config Release --parallel
```

`07` GOTCHA 2 does not apply. Files touched: `ge_vr_xr.cpp`, `ge_vr_host.h`,
`rt64_render_context.cpp`, `input.cpp`, `vr.ps1`.

---

## Roadmap decided alongside this plan, 2026-08-22

**VR controllers.** There is **no OpenXR input code in the tree at all** — no
action sets, no suggested bindings, no `xrSyncActions`. Greenfield.

Agreed scope and order:

| | |
|---|---|
| First | Buttons and sticks onto the N64 pad. Host-side only, no MIPS patch |
| Then | Motion aim as its own **phase**, not a slice — it needs the patch and the player struct |
| Order | **3f-5 before controllers** |

The ordering argument is not a preference. Controller poses are located into
`g_appSpace` — **the same `XR_REFERENCE_SPACE_TYPE_LOCAL` that is currently
reporting the head 4.55 m in the air.** Hands inherit the identical broken
origin. Building aim on it first means calibrating hand positions against a frame
known to be wrong by metres, where a bad binding and a bad origin are
indistinguishable in a headset. **3f-5 fixes the frame both the head and the
hands sit in.**

Two things established for the controller slice while checking:

- **Bind to `/interaction_profiles/oculus/touch_controller`.** OpenXR binds to
  *interaction profiles*, not devices; SteamVR remaps whatever hardware is
  present onto them. This is not a Pimax-specific path. Add
  `/interaction_profiles/khr/simple_controller` as a fallback.
- **The injection point is `recomp::get_input_analog()` / `get_input_digital()`**
  (`input.cpp:590` / `:620`). Every game input funnels through those two, so VR
  buttons merge in there without touching the N64 controller model.
- `xrAttachSessionActionSets` is **once per session and irreversible**, so the
  action set has to be built at session creation, before the frame loop syncs.
  Same "know who destroys what you build, and when" shape as `29`.

**Also open, and possibly ahead of both:** legibility. The view is reported as
hard to see independently of the height error. Untriaged, no evidence yet — see
`35` once there is some. It has not been costed and may outrank the controllers.
