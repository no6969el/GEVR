# Step 3c — the culling frustum moves to the engine's own lever

> **Outcome, 2026-08-22:** the camera gates passed; the blue-band gate failed and
> the band turned out to be near-plane clipping rather than culling
> (`19-blue-band.md`). The work below stands — drawing and culling really were
> disagreeing by 46 degrees, and that had to be fixed before two eyes could be
> drawn from one display list. It simply does not fix the band.

**2026-08-22. Written, not yet built.** The step where the patch stops fighting
the engine, and where the two halves of the eye split finally stop overlapping.

Plan and the research behind it: `17-step3c-plan.md`.

## What changed, in one table

| Concern | Before 3c | After 3c |
|---|---|---|
| Per-eye frustum | patch, rewriting `Mtx` and `Mtxf` | **RT64** (`overrideFrustum`) |
| Culling frustum | nothing — stock 60 deg | **patch**, via `viSetFovY` |
| Per-eye view offset | RT64 | RT64, unchanged |

Both halves now sit where they can see what they need. Nothing is applied twice
and nothing is applied nowhere.

## The patch: a new mode, `GE_VR_MODE_HOSTEYE`

Now the default. `OFF`, `BINDTEST` and `STEREO` are all kept — `STEREO` is the
A/B partner for everything below, and throwing it away would make the comparison
impossible the first time something looks wrong.

In `HOSTEYE` the two projection setters become counter-only pass-throughs. The
frustum maths does not move to RT64 — RT64 has had its own copy since 3b. It is
simply switched on there and switched off here.

The new patch:

```c
RECOMP_PATCH void viSetFovY(f32 fovy) {
    g_geVrFovWidenCalls++;
    if (geVrInLevel()) {
        fovy *= GE_VR_CULL_FOVY_SCALE;      /* 106 / 60 */
        if (fovy > 170.0f) fovy = 170.0f;
    }
    g_ViBackData->fovy = fovy;
    currentPlayerSetPerspective(g_ViBackData->znear, g_ViBackData->fovy, g_ViBackData->aspect);
    currentPlayerSetCameraScale();
}
```

Three deliberate choices in nine lines:

- **Multiplicative, never an assignment.** `bondview2.c:3069` calls
  `viSetFovY(zoominfovy)` for scope zoom. Assigning a constant would pin the
  scope at one magnification.
- **Patching the setter, not calling it.** `viSetFovY` is re-called every frame
  by `lvlRender` and from eight sites in `front.c`. Setting the FOV anywhere else
  would be overwritten within a frame.
- **The 170 clamp.** At 180 the projection is singular and the frustum normals
  are meaningless. A 1.77x scale never reaches it from 60, but zoom multiplies
  too, and a scope at 3x would.

106 degrees vertical gives roughly 121 horizontal at the game's aspect, which
contains the headset's 108 degree two-eye union with margin for head rotation
between 30 Hz display lists. **The superset only has to contain the eye frustums,
not match them.** Too generous costs submitted geometry that is then clipped;
too tight costs geometry that does not exist. The asymmetry of those two costs is
why the number errs high.

## The host: the frustum override switched on

Four environment variables now, all off by default so an unset build still
behaves exactly as 3a did:

```
GE_VR_TEST_OFFSET   lateral eye offset in game units (1 unit ~ 1 cm, docs\16)
GE_VR_FRUSTUM       1 to apply the measured per-eye frustum
GE_VR_EYE           0 left, 1 right
GE_VR_FIT_ASPECT    1 (default) keeps the monitor preview undistorted
```

The tangents are the measured Pimax values from `09`, moved out of the patch and
into the host where they belong — the host is what will eventually call
`xrLocateViews`.

### The preview fit, and why it scales about zero

A true eye frustum is nearly square. Shown full-screen on a 16:9 monitor it looks
horizontally squashed, which is correct and also makes the asymmetry hard to
judge by eye. `GE_VR_FIT_ASPECT` rescales the horizontal terms so the image keeps
the game's own x/y ratio.

**It scales `[0][0]` and `[2][0]` together, about zero.** Scaling about the
frustum centre would re-centre the projection and quietly delete the
off-centre-ness that is the entire point of a stereo frustum. This is the same
trick, and the same reasoning, as `GE_VR_PREVIEW_FIT_ASPECT` in the patch — now
in the host, since that is where the frustum lives.

## Build — this one needs more than the one-liner

`viSetFovY` is a **new `RECOMP_PATCH` name**, so the rename script must be
re-run, and the order matters because it filters against what N64Recomp actually
emitted (`07`, "When you must do more than the one-liner"):

```powershell
$env:PATH = "C:\Program Files\LLVM\bin;C:\Program Files\CMake\bin;C:\Users\pdbar\AppData\Local\Microsoft\WinGet\Links;" + $env:PATH
cd C:\Users\pdbar\Desktop\GoldenEye64Recomp

cd patches; make CC=clang LD=ld.lld; cd ..
.\N64Recomp.exe patches.toml
py tools_weaken_patched.py
cmake --build build --target GoldenRecomp --config Release --parallel
```

Expect `tools_weaken_patched.py` to report **30** renamed, one more than the 29
in `01`. If it still says 29, `viSetFovY` did not reach `patches.elf` and
everything below will silently do nothing.

The renamed list in `01-state-of-play.md` gains `viSetFovY`.

## Gate 3c

Run in this order. Each step has one job.

```powershell
cd C:\Users\pdbar\Desktop\GoldenEye64Recomp

# 1 - control: everything unset
build\Release\GoldenRecomp.exe

# 2 - cull widening only, no eye frustum
$env:GE_VR_FRUSTUM="" ; build\Release\GoldenRecomp.exe

# 3 - the real thing: wide cull + measured left eye
$env:GE_VR_FRUSTUM="1" ; $env:GE_VR_EYE="0" ; build\Release\GoldenRecomp.exe

# 4 - right eye
$env:GE_VR_EYE="1" ; build\Release\GoldenRecomp.exe
```

| Run | Pass looks like |
|---|---|
| 1 | **Noticeably WIDER than before**, and undistorted. The patch's own eye frustum is gone; what remains is the 106 degree cull FOV, which is now what gets drawn as well. This is the one run whose appearance legitimately changes without the host doing anything. |
| 2 | Same as 1. `GE_VR_FRUSTUM=""` is off. |
| 3 | The asymmetric eye frustum: centre of projection pushed to one side, image undistorted, **straight edges straight**. |
| 4 | Mirrored — the centre pushed the other way by the same amount. |
| **all** | ~~**No blue background band at any screen edge while strafing along a wall.**~~ **FAILED 2026-08-22.** The camera behaved as predicted in all three runs; the band survived all of them, and only ever appears when pressed against a wall. It was never a culling problem — see `19-blue-band.md`. 3c's widening of the cull frustum is still correct and still necessary, it just does not own this symptom. |
| **all** | No geometry popping in at the edges while turning. |

Then the cost check, which matters and is easy to skip:

- **Frame time on a dense level — Surface or Streets, not the Facility.** `05`
  predicts display list overflow becomes likelier as the frustum widens, and 3c
  is the first change that genuinely enlarges the culled volume rather than just
  the drawn one. Symptoms would be flickering or missing geometry in busy scenes,
  which look nothing like a frustum bug and would be misdiagnosed as one.

## Where this can go wrong, most likely first

1. **`currentPlayerSetPerspective` / `currentPlayerSetCameraScale` may not
   resolve.** They are game functions not declared in `patches/externs.h`, so the
   patch declares them itself. The link uses `--unresolved-symbols=ignore-all`,
   so a name N64Recomp cannot resolve does **not** fail the build — it produces a
   call into nothing. Symptom: crash on the first in-level frame, or the FOV
   never widening. `g_geVrFovWidenCalls` distinguishes the two: zero means the
   patch never ran at all, non-zero with no visible change means the calls went
   nowhere.
2. **LOD shifts with FOV.** `c_lodscalez` derives from `c_scaley`, and
   `widescreen.c` already patches `getPlayer_c_lodscalez` and `getinstsize` to
   compensate for related changes. Models switching detail level at the wrong
   distance is plausible and is a behaviour change, not a bug in this step.
3. **The front end.** `front.c` calls `viSetFovY` from eight places.
   `geVrInLevel()` should keep them stock; if the title screen or file select
   looks wide or distorted, that gate is the suspect.

## The eye parameters are now in two places

The tangents exist in the host (`rt64_render_context.cpp`) and still in the patch
(`g_geVrEyeParams`, used only by `GE_VR_MODE_STEREO`). That duplication is
deliberate for now — `STEREO` has to keep working as the A/B partner — but it is
a divergence risk the moment either set is edited. When `STEREO` is finally
retired, the patch copy goes with it.
