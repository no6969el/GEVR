# 175 — U-19. THE GAME ON A SCREEN, INSTEAD OF THE RED/BLUE CLEAR.

**2026-08-25. BUILT, UNWORN.**

> ## THE OWNER'S REASON, AND IT IS A TOOLING REASON
>
> ***"I can't use the VR controllers either and see what I'm doing while in VR
> because if I switch to the desktop view it switches to desktop controls."***
>
> **THIS IS NOT A GAME FEATURE. IT IS A TEST-LOOP FEATURE, and it makes every
> future wear test cheaper** — which is why it earned a place ahead of things on
> the sheet that sound more important.

---

## 1. THE RED/BLUE WAS NEVER A BUG

`ge_vr_xr.cpp:1632`, in the project's own words:

> *"Null is a normal state, not a failure: the front end, menus, cutscenes and the
> opening frames all legitimately have no eye split. The caller falls back to the
> 3f-2 flat colour, which says 'no image' unambiguously instead of showing a stale
> one."*

**Left red, right blue is `docs\10`'s convention, chosen so a swapped or
single-eye submission is obvious the instant the headset is on.** It did its job.
**It is simply hostile once you are trying to USE the menus while wearing it.**

## 2. THE FIX IS A REAL 3D SCREEN, NOT A BLIT

The obvious version — copy the flat image into both eyes — puts an identical
picture in both, which reads as a wall at infinity filling the entire field of
view. **This draws a rectangle in space instead.**

Same shape as the timewarp shader, and for the same reason: **a fullscreen
triangle that reconstructs the view ray from the eye's OWN frustum tangents.**

```hlsl
float3 d   = float3(lerp(tanL, tanR, uv.x), lerp(tanU, tanD, uv.y), -1.0);
float3 hit = float3(eyeX + d.x * dist, d.y * dist, -dist);   // plane at z = -dist
```

**`d.z` is `-1` by construction, so the plane is hit at `t = dist` — no divide,
and no way to hit a degenerate one.** Inside the rectangle, sample the game;
outside, the surround colour.

> ## **AND THE STEREO IS FREE.**
> The ray starts at `(eyeX, 0, 0)` — **each eye's own offset from the head
> centre** — so the screen sits at a real depth with correct parallax.
> **NOTHING here needs the per-eye HUD shift `173` fought over, because this is
> genuine 3D rather than a 2D sprite pretending to be.**

**The canted asymmetric frustum (`166` §1) is correct BY CONSTRUCTION** here, for
the same reason: each eye uses its own tangents.

## 3. THE SOURCE: THE SAME PATH THE EYES TAKE

`prepareEyeFromTarget` (`rt64_present_queue.cpp:361`) turns any `RenderTarget`
into a sampleable texture. **It is generic — nothing about it is eye-specific** —
so the ordinary present `colorTarget` goes through the **identical** resolve,
downsample and `VIRenderer::render()`, into a new `vrPresentFlatTexture`.

> **THERE IS NO SECOND ROUTE BY WHICH A FRAME CAN REACH THE HEADSET.** That was
> the design constraint, not an accident: `50` and `69`-`71` are both records of
> what happens when two present paths disagree.

**PUBLISHED ALWAYS, not only when the eye pair is missing.** The XR side decides
whether to use it. Deciding in the present queue would mean **two places knowing
when a frame is "flat"**, which is `48` rule 8's duplicated owner.

## 4. THREE THINGS TAKEN FROM PAST FAILURES

**ONE DESCRIPTOR SLOT PER EYE.** `69`-`71`: both present draws bound the SAME
heap slot in one command list, and **D3D12 resolves heaps at EXECUTION time, not
at record time**, so the second binding won for both eyes and every measurement
said "one image in both eyes" for weeks. **A shared slot here would reproduce B1
exactly and look like a screen bug.**

**THE CLEAR REMAINS THE FALLBACK.** If the PSO fails to build, or no flat texture
has arrived, red/blue still shows. **So the two states never become ambiguous:
black-with-a-screen means "flat mode", red and blue still means "no image at
all".** A feature that silently degrades into a plausible-looking wrong answer is
the thing `48` exists to prevent.

**THE POINTER IS DROPPED AT TEARDOWN.** `g_flatSource` names a texture RT64 owns,
and `42`'s teardown crash was precisely a stale pointer into RT64's resources
outliving them.

## 5. KNOBS, AND THEY ARE INDEPENDENT ON PURPOSE

| knob | default | what |
|---|---|---|
| `-ScreenDist` | **2.5 m** | how far away it sits |
| `-ScreenSize` | **2.6 m** | its WIDTH; height follows the image's own aspect |

**The screen is sized in METRES at a given distance, so changing the distance
alone does not change how big it looks.** That is what keeps the two knobs from
fighting — a single "size" knob that meant angular size would have made distance
meaningless, and one that meant physical size would have made it a zoom.

## 6. GATES

- **G-175-1** — the front end and menus show **the game**, in a rectangle, at a
  comfortable distance. Not a wall, not a tint.
- **G-175-2** — **it has DEPTH.** Close one eye, then the other: the screen should
  shift slightly against the background, like a real object at 2.5 m.
- **G-175-3** — in-level rendering is **completely unchanged**. The screen path is
  in the `else` branch and cannot execute when an eye pair exists.
- **G-175-4** — the log says `screen (docs\175 U-19): READY`. If it says
  `UNAVAILABLE`, the PSO failed to build and red/blue is expected.

## 7. WHAT THIS UNLOCKS — `169` U-20

**The owner wants PD's hub room, re-skinned for GoldenEye.** U-20 needs a textured
quad drawn with per-eye matrices in the XR layer. **That is exactly what this
built.** PD's room is only **two quads and 12 vertices** — a floor and a sky, both
procedural in the fragment shader, with no art assets at all.

**So U-20 is now "draw two more quads behind this one with different shaders",
rather than a from-scratch feature.** Recorded so it is not re-costed from zero.
