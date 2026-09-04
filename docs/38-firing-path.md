# 38 — the firing path, read

**2026-08-23.** `37` rested on one unverified claim and this is the check.
The answer is yes, and three things found on the way change how the hand-aim
slice has to be built.

---

## The question, answered

**Does hip fire read `crosshair_angle`?** **Yes, unconditionally.**

`gunfire.c:4847`, `bullet_path_from_screen_center` — the single source of every
bullet direction in the game:

```c
crosspos.x = g_CurrentPlayer->crosshair_angle.f[0] + randfactor * scaledspread * ...
crosspos.y = g_CurrentPlayer->crosshair_angle.f[1] + randfactor * scaledspread * ...
...
transformAndNormalizeByLength2Dto3D(&crosspos, result, 1.0f);
```

**There is no aim-mode branch anywhere in it.** Eight call sites — five in
`gun.c`, two in `chrprop.c`, one in `gunfire.c` — and every shot in both modes
goes through it. `37`'s foundation stands: drive that quantity and the gun aims,
in hip fire, without ever entering aim mode.

## The full pipeline, since the names mislead

```
stick  moveData.controlStickXRaw/YRaw          bondview2.c:6077
  -> turn_x, turn_y                            a RATE, not a position
  -> crosshair_x_pos = crosshair_x_pos * guncrossdamp + turn_x
                                               leaky integrator, once per g_ClockTimer sub-tick
  -> crosshair_angle.f[0] = crosshair_x_pos * (1 - guncrossdamp) * W * 0.5 + W * 0.5
                                               SCREEN PIXELS
  -> clamp to [3, W-4], then += getPlayer_c_screenleft()
  -> bullet_path_from_screen_center adds random spread
  -> transformAndNormalizeByLength2Dto3D       unprojection to a 3D direction
```

---

## Correction 1 — `crosshair_angle` is not an angle

`37` called it "an angular offset between where the body faces and where the gun
points". **It is a screen-space pixel position.** `gunfire.c:4696` builds it from
a normalised position times `screen_width * 0.5` plus a half-screen centre, then
clamps it to the viewport in pixels.

The conclusion `37` drew from it survives — it *is* the gun-versus-body offset,
and it *is* the thing to drive — but the units are pixels and the aim is
fundamentally **screen-space**, resolved into a ray by unprojection. Anything
built on "it's an angle, just add the hand's yaw" would have been wrong in a way
that looked plausible for a while.

## Correction 2 — write the INPUT, never `crosshair_angle` itself

`crosshair_angle` is **recomputed from `crosshair_x_pos` / `crosshair_y_pos`
every frame.** Writing it directly would survive exactly until the next call to
`caclulate_gun_crosshair_position_rotation` and then vanish, intermittently,
depending on whether anything moved.

`35` predicted this shape for `vv_theta` and warned about the companions. **Here
it is confirmed in the actual code**, and it is `21`'s rule for the fifth time.

The inputs are also not free: that same function *rescales* `crosshair_x_pos`
whenever `guncrossdamp` changes — which happens on **weapon switch**, since the
damping comes from `WeaponStats`. So a hand-aim implementation that sets
`crosshair_x_pos` must expect the game to rescale it underneath, and must set it
every frame rather than once.

The relation is exactly invertible, which is the good news:

```
crosshair_x_pos = (desired_pixel_x - W * 0.5) / ((1 - guncrossdamp) * W * 0.5)
```

So the slice is: take the controller's aim direction, project it into the game's
screen space, invert that expression, write `crosshair_x_pos` / `crosshair_y_pos`
every frame, and let the game's own pipeline do the rest — spread, auto-aim, hit
detection, sway, all unchanged.

## Correction 3 — the aim cone is HARD LIMITED, and smaller than the view

```c
if (crosshair_angle.f[0] < 3.0f)               crosshair_angle.f[0] = 3.0f;
else if ((screen_width - 4.0f) < ...)          crosshair_angle.f[0] = screen_width - 4.0f;
```

**The gun can never point outside the game's viewport.** That is a hard clamp on
how far the hand may aim off the body's facing, and it is not a tuning value —
past it, the pixel simply stops moving.

Worse than it first appears: `bullet_path_from_screen_center` scales spread by
`viGetFovY()`, and `00-START-HERE` records that the patch's `viGetFovY` **divides
the widening back out** so the game believes its FOV is normal. The screen
rectangle therefore corresponds to the game's **original** field of view, not the
106 degrees the culling frustum was widened to.

**So hand aim gets roughly the original FOV's half-angle off body centre — on the
order of ±30 degrees horizontally — while the wearer can comfortably look much
further.** Point the controller past that and the gun stops following your hand.

This is a real design constraint and it is worth having before anything is built,
because it decides an interaction question: **what happens when you point past
the limit?** Options, none chosen: let the gun lag at the clamp; auto-turn the
body to follow; or fade/indicate the limit. Choosing wrongly is the difference
between "the gun is mine" and "the gun fights me".

---

## One thing that is right already

`bullet_path_from_screen_center` zeroes its origin and returns a **camera-space
direction**. So the aim is *already* expressed as an offset from the game camera,
which is exactly the decomposition `37` argued for — and it means our head
rotation, applied downstream in RT64, cannot disturb it. The architecture wanted
does not have to be created; it has to be fed.

## Where the injection goes

`bondview2.c:6072` and `:6077` — two entry points, the aim-lock path and the
stick path. That branch is almost certainly the aim-mode split, and it is where a
VR path would be added as a third case rather than by editing either.

## Still not established

- Which of `:6072` / `:6077` is aim mode, confirmed rather than assumed.
- Whether `crosshair_x_pos` has readers besides this function.
- Whether `getPlayer_c_screenwidth()` is affected by anything the patch does.

None of these block the controller slice. All of them block the hand-aim slice,
and each is a read rather than an experiment.
