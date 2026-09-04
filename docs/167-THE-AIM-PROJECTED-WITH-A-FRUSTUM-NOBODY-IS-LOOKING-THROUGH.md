# 167 — THE AIM PROJECTED WITH A FRUSTUM NOBODY IS LOOKING THROUGH.

**2026-08-25. BUILT, UNWORN. This is the fix `166` §7.1 called for.**

> ## THE FAULT IN ONE LINE
>
> **`c_scalex`/`c_scaley` are built from `c_perspfovy = 106`. The frame is DRAWN
> from the headset's tangents (~88 degrees). Nothing ever rebuilt the first from
> the second, so the aim projected through a frustum that is not on screen.**

---

## 1. THE TWO NUMBERS, AND THERE ARE TWO RATIOS, NOT ONE

| axis | game | render | ratio |
|---|---|---|---|
| vertical half-tangent | `tan(106/2)` = **1.327** | `tanUp` = **0.966** | **1.374** |
| horizontal half-tangent | `c_scalex * 160` = **1.930** | `(tanR-tanL)/2` = **1.253** | **1.540** |

`c_scaley = 1.327/110 = 0.012064` matches the logged `scaley=12064` **exactly**,
which is what pins the diagnosis.

> **TWO DIFFERENT RATIOS ON THE TWO AXES IS WHY IT READ AS TWO BUGS.** The wearer
> reported the error growing *"the more I go up"* AND being *"all off in a
> different way"* at the sides. **One projection, two wrong scales.**

## 2. WHY IT DIVERGED

`currentPlayerSetProjectionMatrix` (`ge_vr_bindtest.c`) rebuilds the REAL matrix
from the headset tangents via `geVrBuildProj`. **`c_scalex`/`c_scaley` are set
separately**, by `currentPlayerSetCameraScale` (`bondview.c:649`) off
`c_perspfovy`, and that path never learned about VR. `viGetFovY` even divides the
cull scale back out (`ge_vr_bindtest.c:968`) to keep the game's own view of its
FOV consistent — **so the 106 is deliberate for culling and simply wrong for
aiming.**

## 3. THE FIX, AND IT IS PERFECT DARK'S DISCIPLINE REACHED FROM THE OTHER SIDE

`166` §8.2: PD push a **world point** through `camGetWorldToScreenMtxf()` — the
render's own matrix — which is why they have no gain constant and no FOV error.

**We already have the ray in camera space, so the equivalent is to divide it by
the RENDER's tangents instead of the game's.** New host call:

```
bool ge_vr::aim_frustum(float *out4);   // {centreX, halfSpanX, centreY, halfSpanY}, TANGENTS
```

filled where `config.eyes[]` is built, from the same live `fovAngles` the
projection override uses. The patch then computes

```
nx =  (rX - centreX) / halfSpanX
ny = -(rY - centreY) / halfSpanY      /* camera +y is UP, pixels grow DOWN */
```

and falls back to `transform3Dto2DCoords` untouched when the host returns 0.
**ZERO NEW CONSTANTS** — the tangents are measured from the headset every frame.

## 4. WHY CYCLOPEAN

The eyes are mirrored and asymmetric (`166` §1), so **no single pixel is correct
for both.** Averaging the two gives centre 0 and the shared half-span — the best
a single 2D crosshair can be, and **exactly right for the quantity that actually
matters, which is the aim fed to the integrators.**

**PD SOLVE THE REMAINING HALF DIFFERENTLY AND WE SHOULD TOO — see `168` §2.1:**
they shift the HUD **per eye** by a canting term
`(tanRight+tanLeft)/(tanRight-tanLeft)`. **For our eye 0 that is -0.1867, which
is EXACTLY the `m20=-0.18669` already in our own projection log.** The 3D scene
gets canting; the HUD does not. **That is the doubled crosshair, and it is a
separate fix from this one.**

## 5. ►►►► WHAT THIS DOES NOT FIX, STATED PLAINLY ◄◄◄◄

**THE BULLET WAS NEVER AFFECTED.** The shot direction is a raw game-space ray
(`164`) and never touched `c_scale`. **This moves the CROSSHAIR onto the barrel
and nothing else.**

**So if shots are still off after this, the remaining error is `166` §4's 17
degrees**, whose tangent ratio was 2.23 — **not** this fix's 1.374 or 1.540 — and
which is therefore a genuinely separate fault. Leading candidate remains that the
wearer aims by the DRAWN GUN, whose orientation is the seam matrix `158` §3
already proved is not the barrel.

## 6. GATES

- **G-167-1** — `-AimFromHand` unset: identical. The host gate returns at the guard.
- **G-167-2** — the crosshair sits ON the barrel at every elevation, not just at
  screen centre. **This is the specific claim.**
- **G-167-3** — no knob is touched to achieve it.
- **G-167-4** — **the world scale goes back to 100 and the "toy model" perception
  is GONE.** `166` §3: at 12 u/m Bond is 14.6 m tall and the gun is 1.7 m long.
  **If it is still toy-like at 100, the FOV was not the whole story and that is
  the finding.**
