# 36 — 3f-5 worn: what passed, and the bug 3f-5 introduced

**2026-08-22, immediately after 3f-5 was worn.** Three gates passed, one roadmap
item collapsed, and one new fault was introduced **by this slice** and is
diagnosed below.

---

## Passed

| Gate | Result | Evidence |
|---|---|---|
| 1 — separation survives the split | **PASS** | `eye sep 6.33 units` at 100 u/m = 63.3 mm, against 63.5 measured |
| 2 — `y` near zero at start | **PASS** | `y=-0.2 units (-0.002 m up)`, from `origin y=1.163 m` |
| 3 — crouch goes negative | **PASS** | `y=-26.0 units (-0.260 m up)`, `raw` moved 1.16 -> 0.90 with it |

The recentre works. Note the origin this session was **1.163 m**, not the 4.55 m
of `33` — so the offset is **not a fixed constant, it varies between sessions.**
That is itself the answer to `33`'s open question: this is SteamVR's zero pose,
it moves, and cancelling it per session is the correct response rather than
compensating with a constant anyone could have hard-coded.

## Phase 3 is largely already done

Reported from play:

> When I move my head the gun stays forward. I can look around and the gun is
> controllable by the controller. **It's decoupled.**

**`35`'s gate 1, outcome 1.** The composition order was right and the documents
were wrong: `E` acts in view space after the game's camera, so head rotation
never reaches `vv_theta`. `00-START-HERE` and `30` both assert "turning your head
turns the gun" and **both are hereby corrected.**

Phase 3 therefore is not a phase. What remains of it is *hand* aim — moving the
aim source from stick to controller — which is a slice on top of the controller
work, not a rewrite. The `vv_theta` companion-field warning in `35` still stands
and still has to be honoured when something does write those angles.

---

## The new fault: the layer pose disagrees with what we drew

Also reported:

> The right eye is showing the image but if I close my left eye and move my head
> the distortion is off. Also still shows two of everything.

### The mechanism

`ge_vr_xr.cpp:696`:

```cpp
projViews[eye].pose = views[eye].pose;      // the RAW located pose
```

3f-5 made the renderer draw from `yawInv * q_raw` — the pose with the captured
heading rotated out. **The layer still tells the compositor `q_raw`.**

So every frame we hand the runtime an image and a claim about the orientation it
was drawn at, and since this afternoon **the claim is wrong by a constant yaw.**
The compositor reprojects against that claim. The angular error is constant, the
warp it produces is not, and it is applied **per eye against each eye's own
pose** — which is precisely a differential, non-rigid disagreement between the
two images.

**Vertical and rotational disparity is what prevents fusion.** Horizontal
separation being correct — and `eye sep 6.33` says it is — does not help if the
two images are rotated relative to each other. That is why "two of everything"
survived a slice that measurably fixed the geometry.

Translation is **not** implicated: a constant positional offset leaves every
frame-to-frame delta unchanged, and reprojection only consumes deltas. **Rotation
is different**, because it changes what the image itself depicts.

### The falsification, one flag, no rebuild

```powershell
.\vr.ps1 -NoRecentreYaw
```

Keeps the position recentre — which gates 2 and 3 show working — and drops the
yaw rotation, restoring agreement between the layer pose and the drawn image.

**Prediction: fusion improves markedly and the right-eye distortion goes.** If it
does not, this diagnosis is wrong and the fault is elsewhere; `-NoRecentre` then
reverts the slice entirely for a clean A/B.

### The real fix, and why the current one is in the wrong place

Recentring by post-processing the pose inside the renderer was **architecturally
wrong**, and wrong in exactly the way `30` warned about: a coordinate conversion
placed somewhere that was also doing something else, where nobody downstream can
see it. `ge_vr_xr.cpp` cannot know the renderer moved the world.

OpenXR has an idiom for this and we should use it.
`XrReferenceSpaceCreateInfo::poseInReferenceSpace` defines a space **offset from
LOCAL**. Recreate `g_appSpace` with the captured origin as that offset and:

- `xrLocateViews` returns poses already recentred;
- the layer pose is that same recentred pose, because it comes from the same
  call;
- **agreement is structural rather than maintained** — the same reasoning that
  made "each eye uses its own pose" the right call in `30`;
- the quaternion maths leaves `rt64_render_context.cpp` entirely.

Recentring then becomes: capture the pose, destroy the space, create a new one
with that offset. `29`'s rule applies — know who destroys what you build — since
`g_appSpace` is referenced by the frame loop and the teardown path.

**This supersedes 3f-5's recentre implementation. The decomposition, the
tracked-bit gate, the split flag and the logging all stay; only the place the
offset is applied changes.**

---

## Two things noticed in the log, neither chased

**The live tangents are not `09`'s measurements any more.**

```
eye 0 live tangents: -1.4869 1.0190 0.9657 -0.9657      this session
                     -1.3760 1.0358 1.0176 -1.0176      docs\09, and the old constants
```

Wider horizontally, narrower vertically. Live FOV is doing its job — this is the
argument for it — but it means the headset's reported FOV **changed between
sessions**, and nobody knows why. It is also a candidate for the legibility
complaint, since a wider frustum across the same panel is fewer pixels per
degree.

**Screenshots are not available.** Confirmed from play: no in-VR capture, and a
lens photograph shows one eye. `-Sbs` remains untried and is the only route to a
side-by-side comparison; if it also fails, per-eye judgement has to be done by
alternately closing one eye, which is what produced the report above and is
evidently workable.

## Still untested

Gate 6 — `-NoHeadTranslate` must now **keep** stereo, the opposite of what `32`
claimed. Not yet run.

---

## The lens photographs — they were more useful than expected

Two through-the-lens phone photos, offered as "these won't help". They carry one
measurement and one absence.

**The viewmodel is rendering very large and very near.** The PP7 and hand fill a
large fraction of the frame in both shots. Combined with `16`'s ~100 units per
metre and the session's `unitsPerMetre=100`, a viewmodel sitting around 15-25
game units from the eye maps to **15-25 centimetres from the wearer's face.**

That is **inside the human near point.** Typical comfortable fusion stops around
40-50 cm and the absolute near point is 10-25 cm even for young eyes. **An object
at 20 cm with a real 63.5 mm IPD cannot be fused**, and it does not matter how
correct the separation is — which it now measurably is.

**So the gun doubling has a candidate cause that is not a bug at all: the
viewmodel is at a distance the eyes physically cannot converge on.** Note the
arithmetic runs the other way from intuition — distance in metres is
`units / unitsPerMetre`, so a *lower* `-UnitsPerMetre` pushes the gun *further
away*. The last session ran at 50 and this one at 100, meaning **this session
placed everything at half the apparent distance of the last one.**

`00-START-HERE`'s open note said the docs predicted the viewmodel would "read as
flat" and it doubles instead, and that the Phase 3 plan for it was therefore
aimed at the wrong problem. This is the mechanism it was missing.

Two consequences, and they are separable, which is the point:

- **World scale and viewmodel depth are different quantities and cannot share one
  knob.** Whatever `-UnitsPerMetre` makes a doorway feel right will not also put
  the gun at a fusable distance, because the game placed the viewmodel for a
  flat screen where convergence does not exist. The viewmodel needs its own
  depth scale.
- **`-UnitsPerMetre 50` should measurably reduce the doubling** as a side effect,
  by pushing everything to twice the distance. That is a test, not a fix.

**The absence: no HUD or crosshair is visible in either photo.** Not conclusive
from two frames of a dark corridor, but if the reticle is genuinely not being
drawn, `35`'s aim experiment could not have been run as written — and the fact
that the decoupling was confirmed by watching the *gun* rather than a crosshair
suggests it was not.

---

## Correction, same day: there are TWO aim modes, and only one is decoupled

From play, after the above was written:

> There is no crosshair in that game unless you hit the aim button, in which the
> crosshair comes up and **it locks to your head.**

So the "Phase 3 is already done" finding above is **half right, and the half it
gets wrong is the half that matters for shooting.**

| Mode | Crosshair | Coupling | Status |
|---|---|---|---|
| Hip / free look | none drawn | **Decoupled.** Look freely, gun stays where the stick put it | Confirmed working |
| Aim mode (aim button) | drawn | **Locked to the head** | Phase 3 work remains, and this is where it is |

That is not a contradiction of the mechanism, it is a second path through it.
Free look never reaches `vv_theta`, as the composition order predicts. Aim mode
does something else, and **finding what** is now the first task of Phase 3 rather
than the experiment in `35` — which has been run, and answered for the mode it
happened to test.

**`35` gate 1 should have specified which mode.** It says "put the crosshair on
an object", which in this game silently means "enter aim mode" — so the gate as
written could only ever have exercised the coupled path, and the answer that came
back was from the uncoupled one. A gate that does not name the mode it runs in
cannot say which mode its answer describes.

Nothing to redesign yet: hip-fire decoupling is confirmed and free, and aim mode
is deferred by explicit choice until the fusion problem is closed.
