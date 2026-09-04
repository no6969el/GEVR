# 85 — THE SEAM WORKS. Position tracks the hand. Two faults found and killed by measurement.

**2026-08-23, ~18:05. The end of the session, and the first time the gun has
followed a hand at all.**

---

> ## CONFIRMED WORN, at the end of the session
>
> > *"Yes, it moves where my hand goes when in front of me."*
>
> **This is the first time in this project that the gun has followed a hand.**
> It is an OBSERVATION, so the row moves — `39`'s rule.
>
> **And note the qualifier, because it was not idly said: "WHEN IN FRONT OF
> ME".** Nobody has checked what happens with the hand at the side, low, or
> behind the shoulder. **Do not record this as "position works" without that
> test** — the aim clamp (`38`, roughly +/-30 degrees off body centre) lives out
> there too, and the two will be easy to confuse.

## THE STATE AT THE END

**`.\vr.ps1 -UnitsPerMetre 50 -SeamNoRot -HandPosZ 1`**

| | |
|---|---|
| **The gun is solid, single, stable** | No ghost, no flicker, no floor |
| **Left / right track the hand** | Confirmed worn |
| **Depth tracks the hand** | After the Z flip below |
| **Rotation** | **Deliberately identity** (`-SeamNoRot`). Next slice |
| **The bullet** | Still from the crosshair. Slice 3, and the user asked for it directly |

## FAULT 1 — THE FEEDBACK LOOP. Found by a constant.

**The symptom was two guns**: one on the floor, one ghosting over the shoulder,
flickering fast.

**The experiment `84` demanded — a KNOWN CONSTANT, identity rotation and a fixed
translation — came back solid, single and stable.** That one launch eliminated
the interpolation, the space and the write in one go, and left only what the
constant did not have: **change**.

**The bug:**

```
delta = want - "where the game put the gun"
```

**and "where the game put the gun" was the RENDERED position, which already
contained last frame's delta.** Our own correction moved the reference, the
reference changed the next delta, and the gun oscillated between two places
every frame. **The ghost was the two ends of the oscillation.**

**The fix is one subtraction:** the host now keeps the delta it applied and
recovers the game's unmodified placement as `rendered - ourDelta`. The reference
went from drifting to rock-stable at `(10.9, -20.8, -33.4)` — the game's own
placement, exactly.

> **The rule, and this project has now paid for it twice in one evening:**
> **when a changing thing misbehaves, freeze it.** A constant cannot feed back,
> cannot mispair and cannot oscillate — so whatever survives the constant is not
> the fault.

## FAULT 2 — THE ROTATION WAS HIDING THE GUN, NOT TILTING IT

With the loop closed the position numbers were correct and stable **and the gun
was still invisible.**

**The rotation PRE-multiplies `rotmtx` (`gunfire.c:548`), so it acts in the
gun's own frame about its own origin.** A wrong rotation there does not tilt the
weapon — **it swings it out of view or turns it edge-on**, which reads as "no
gun" and looks nothing like a rotation bug.

**`-SeamNoRot` splits the two.** With identity rotation the gun came back and
tracked the hand. **So the position half is DONE and the rotation is isolated to
a convention sweep** (`-HandAxisX/Y/Z`), not a redesign.

## FAULT 3 — THE Z SIGN IS DIFFERENT FOR THE SEAM, AND THAT IS CORRECT

> *"If I bring the controller closer to me it brings the gun more in front, and
> if I bring the controller forward it brings it behind."*

**A clean inverted Z, measured in one sentence.** `-HandPosZ 1` flips it.

**Why it differs from the render path, which measured -1:** the render path
REPLACES an absolute position in camera space; the seam ADDS to `gunofs`.
**Different space, different sign. Both measurements are right.** Anyone who
"fixes" one to match the other will break the other.

---

## WHERE THE NEXT SESSION STARTS

1. **Turn the rotation back on** — drop `-SeamNoRot` — and sweep
   `-HandAxisX/Y/Z`, **one at a time**. The position is known-good underneath
   it now, which is the whole reason this order was worth the launches.
2. **Then slice 3, the bullet.** Asked for directly:
   > *"We need to have the bullet go where the gun's facing, not where we're
   > looking. It's making it hard to aim."*
   **`38` has done the reading**: the shot comes from `crosshair_x_pos` /
   `crosshair_y_pos` projected into screen space, the relation is invertible, and
   the same hand pose that places the gun can drive it. **Write the inputs, never
   `crosshair_angle`, and write them every frame.**
3. **And the clamp is real**: `38` measured the aim as hard-limited to roughly
   +/-30 degrees off body centre. **The world-space aim dot the user asked for is
   the honest answer to it** — O64.

## THE FLAGS AS THEY STAND

```powershell
.\vr.ps1 -UnitsPerMetre 50 -SeamNoRot -HandPosZ 1     # WHERE THIS SESSION ENDED
.\vr.ps1 -UnitsPerMetre 50 -HandSeam  -HandPosZ 1     # ...plus rotation, unswept
.\vr.ps1 -SeamTest 20                                 # the constant. The tool that found fault 1
```

**Everything is behind a flag and the default build is unchanged.** `80` lists
every knob; `83` explains the seam; `84` is the experiment that broke it open.
