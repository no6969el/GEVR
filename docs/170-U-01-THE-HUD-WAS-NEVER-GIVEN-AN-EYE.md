# 170 — U-01. THE HUD WAS NEVER GIVEN AN EYE.

**2026-08-25. BUILT, UNWORN. First entry moved off `169`'s sheet.**

> ## THE FAULT, IN ONE LINE OF SOMEONE ELSE'S CODE
>
> `rt64_projection_processor.cpp:156`
>
> ```cpp
> if (p.vrEye.enabled && (proj.type == Projection::Type::Perspective)) {
> ```
>
> **THE HUD IS ORTHOGRAPHIC. So every per-eye adjustment in this project has
> been gated away from it since stereo existed — the HUD was drawn at the SAME
> PIXEL in both eyes while the 3D scene behind it was canted per eye.**

---

## 1. WHAT THE WEARER SAW, AND WHY IT COULD NOT BE TUNED

***"the aim target was up the whole time and duplicated (two different locations
on each eye)"***

`166` §1 established there is **no single pixel that is correct for both eyes**,
because the frustums are mirrored and asymmetric:

```
[gevr-xr] eye 0 live tangents: -1.4869 1.0190 0.9657 -0.9657
[gevr-xr] eye 1 live tangents: -1.0190 1.4869 0.9657 -0.9657
```

**The optical centre of each eye is not the centre of its image.** No crosshair
position, and no amount of tuning, can satisfy both. **The HUD needed a per-eye
transform and was structurally excluded from receiving one.**

## 2. THE CORRECTION WAS ALREADY BEING COMPUTED, FOR THE OTHER PATH

The perspective branch cants the world with

```cpp
projMatrix[2][0] = (eye.tanRight + eye.tanLeft) / w;
```

For our eye 0 that is **-0.1867**. Our own projection log has printed
**`m20=-0.18669`** all along. **PD compute the identical quantity**
(`vr_openxr.cpp:1989`) and name it the optical-centre offset ratio:

```c
return (tanRight + tanLeft) / (tanRight - tanLeft);
```

> **SO THE NUMBER WAS NEVER MISSING. IT WAS APPLIED TO THE WORLD AND NOT TO THE
> THING DRAWN ON TOP OF IT.**

## 3. WHY `[3][0]` AND NOT `[2][0]` — DERIVED, NOT TUNED

The perspective path puts canting at `[2][0]`, which multiplies the depth term.
**An orthographic projection has no perspective divide — `w` is constant — so
the equivalent contribution is a CONSTANT in the translation row**, which under
RT64's row-vector convention is `[3][0]`, the same column 0 the perspective terms
write.

**And the magnitude follows from that same argument:** at the HUD's notional
depth the perspective skew contributes exactly `m20` to `x_ndc`, so adding that
quantity makes the HUD cant with the world it sits on. **There is no free
parameter in term 1.**

## 4. TWO TERMS, AND ONLY THE FIRST IS A BUG FIX

| term | knob | default | what |
|---|---|---|---|
| **canting** | `GE_VR_HUD_SHIFT` | **1 = ON** | **the fix.** Puts the HUD at INFINITY, where both eyes agree |
| **depth** | `GE_VR_HUD_DEPTH` | **0 = infinity** | optional. Puts the HUD at a finite distance in metres |

**Canting alone is the correct default.** A crosshair at infinity is comfortable
and is what most VR shooters ship; the depth term exists because some wearers
prefer a crosshair that feels "on" the gun.

**THE DEPTH SIGN, DERIVED RATHER THAN GUESSED** (`48`: five wrong signs so far):
an object at finite depth `D` directly ahead of the head centre appears **RIGHT
of centre to the LEFT eye**. The left eye has `eyeX < 0`, so the shift is
`-eyeX/D`, scaled into NDC by dividing by the half-width tangent.

## 5. WHERE WE DELIBERATELY DIFFER FROM PD

PD (`vr_openxr.cpp:2386`):

```c
parallaxOffset = localEyeX * (VrStereoCrosshair * fovTan.tanHalfWidth);
```

**That MULTIPLIES by the tangent where the geometry divides, and carries an
inverse-depth scalar rather than a depth.** It is an empirical knob that works
for them. Ours expresses the same idea so that **the knob is in METRES and the
zero case is exactly "infinity"**. **Recorded here so the difference is never
mistaken later for a porting error.**

## 6. THE IPD IS MEASURED, NOT CONFIGURED

`eyeX` comes from the runtime's own two eye positions, not a configured IPD —
**`25`'s rule that position and frustum must come from one source, applied to the
HUD as well.** Guarded to `[0.01, 0.10] m`, which is **exactly PD's guard**
(`vr_openxr.cpp:2373`); outside that range it is not an IPD and a nominal 64 mm
is used instead.

## 7. THE INSTRUMENT, AND IT CAN FAIL LOUDLY

```
[gevr] 6dof: HUD shift=1 depth=0.00m eye0=-0.1867 eye1=0.1867 ndc
```

> **THE TWO MUST DIFFER, BY ROUGHLY A SIGN FLIP. EQUAL VALUES MEAN THE SHIFT
> NEVER REACHED THE PROJECTION** — which is the failure this whole document is
> about, and it would otherwise look identical in the headset to not having built
> it. `48`.

## 8. GATES

- **G-170-1** — **the crosshair is ONE object, not two.** Close one eye, then the
  other: it must sit in the SAME place in the world both times. **This is the
  claim.**
- **G-170-2** — the log line's `eye0` and `eye1` differ by roughly a sign flip.
- **G-170-3** — `-NoHudShift` reproduces the doubling, out of the same build.
- **G-170-4** — `-NoXr` untouched. The path is inert when `vrEye.enabled` is
  false, so this holds by construction, but it is the discipline (`131`).

## 9. WHAT THIS DOES NOT FIX

**Not the aim.** `167` moved the crosshair onto the barrel; this stops it being
drawn twice. **`166` §4's 17 degrees is still open and is untouched by both.**

**And it does not make a 2D crosshair correct — it makes it CONSISTENT.** A HUD
at infinity agrees between the eyes; it still cannot show parallax against a near
target. **That is U-06, and it is blocked on the laser (U-05).**
