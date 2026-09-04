# Step 3b — the eye override fires

**2026-08-22. Written, not yet built.** Turns on the path 3a plumbed, driven from
the host, with a lateral eye offset only.

## The result that matters before any picture

**Nothing inside RT64 needed to change to turn the override on.** The host side
is one small function in `src/main/rt64_render_context.cpp` calling
`setVrConfig()` once per game frame. That was the actual test of step 3a — a
boundary drawn in the wrong place shows up as "enabling the feature required
reopening the thing that was supposed to be finished", and it did not.

One design change did come out of writing it, described next. It came from the
work, not from a picture, which is the cheaper way to find it.

## Design change: tangents, not a projection matrix

`12` §3.1 said the eye projection should "replace the game's projection
outright". Writing it exposed the flaw: **handing RT64 a finished projection
matrix means choosing a depth convention, and the game's is not D3D's.** RT64
consumes the game's own projection and understands the mapping it arrives with.
Substituting a D3D `[0,1]` matrix would have silently changed depth semantics
underneath the whole renderer, and depth bugs read as z-fighting, decal flicker
or missing geometry — none of which announce their cause.

`VrEyeParams` therefore carries **four tangents**, not a matrix, and
`processScene` rewrites only the four terms describing the frustum's *shape*:

```cpp
projMatrix[0][0] = 2 / (tanRight - tanLeft);
projMatrix[1][1] = 2 / (tanUp    - tanDown);
projMatrix[2][0] = (tanRight + tanLeft) / (tanRight - tanLeft);
projMatrix[2][1] = (tanUp    + tanDown) / (tanUp    - tanDown);
```

The depth row is left exactly as the game wrote it. No convention is chosen, and
the change is confined to what the eye actually needs to alter.

This also puts the host side in the same shape as the patch, which has always
built the frustum from tangents for a related reason — `05`: libm is not
dependably available in patch space, so trig never crosses that boundary. The
two now agree by construction rather than by comment.

**The skew belongs at `[2][0]`, not `[0][2]`.** RT64's own
`adjustProjectionMatrix()` settles the convention empirically: it scales
`[0][0]` through `[3][0]` to change horizontal field of view, so column 0 is the
x output and row 2's contribution to it is the skew. Transposing it shears the
world in a way that looks almost right, which `10` calls the worst kind of wrong.

## What 3b actually enables: the offset only

`overrideFrustum` is written, wired, and left **off**.

The patch is still building the per-eye asymmetric frustum on the MIPS side.
Enabling the host frustum now would apply it twice and produce a picture with two
possible causes. The frustum moves to the host in **3c**, at the same moment the
patch changes from "one eye's frustum" to "the cull superset" — those are one
change, not two, and splitting them would leave a build where neither side owns
the frustum cleanly.

So 3b tests exactly one thing: does a host-supplied view-space transform reach
the geometry.

## Driving it — environment variable, no rebuild to flip

```
GE_VR_TEST_OFFSET   lateral eye offset in GAME UNITS, signed. Unset or 0 = off.
```

Unset, the build behaves exactly as 3a did. Read once at startup, so changing it
needs a relaunch but never a rebuild.

Game units rather than metres, deliberately: the units-per-metre constant is real
and unmeasured, and borrowing it here would make this test depend on a number
nobody has established. A real IPD in metres arrives with the head pose.

## The gate

Build, then run three times from the repo root:

```powershell
cd C:\Users\pdbar\Desktop\GoldenEye64Recomp

$env:GE_VR_TEST_OFFSET=""     ; build\Release\GoldenRecomp.exe   # control
$env:GE_VR_TEST_OFFSET="120"  ; build\Release\GoldenRecomp.exe   # eye 0
$env:GE_VR_TEST_OFFSET="-120" ; build\Release\GoldenRecomp.exe   # mirrored
```

Pass requires all four of:

1. **Control run is identical to 3a.** If it is not, the override is firing when
   it should be disabled.
2. **`120` shifts the viewpoint sideways.** The camera slides laterally; it does
   not rotate, and it does not zoom.
3. **`-120` shifts it the other way by the same amount.** Asymmetry between the
   two means the sign is being applied somewhere it should not be.
4. **Straight edges stay straight.** A translation cannot shear. Any shear means
   the transform is not landing in view space as intended.

120 units is far larger than a real IPD — roughly a body-width rather than an
eye-width — because a 63.5 mm shift on a monitor is nearly invisible and would
make this gate unfalsifiable. It is a plumbing test, not a stereo test.

## Known limitation, stated rather than discovered later

`config.inLevel` is hardcoded true. The patch knows whether a level is loaded via
`geVrInLevel()`; the host does not yet. Perspective-only gating in
`processScene` keeps menus and the watch out of it, since those are orthographic,
but **a perspective front-end scene would still get the offset**. Acceptable for
a monitor test; a proper host import replaces it before anything reaches a
headset.

## Files

RT64 (MIT, `thirdparty-diffs\rt64\`):
`rt64_vr_eye.h` (rewritten from 3a), `rt64_projection_processor.cpp`.

Recomp host (`thirdparty-diffs\recomp-host\`):
`src/main/rt64_render_context.cpp`, backup `.bak3b`.

The licence split from `12` §7 is doing real work here for the first time: the
two halves of one feature land in two different buckets, and only one of them can
go upstream.

## Building

Host C++ and RT64 only. No patch change, so no `make`, no `N64Recomp`.

```powershell
$env:PATH = "C:\Program Files\LLVM\bin;C:\Program Files\CMake\bin;C:\Users\pdbar\AppData\Local\Microsoft\WinGet\Links;" + $env:PATH
cd C:\Users\pdbar\Desktop\GoldenEye64Recomp
cmake --build build --target GoldenRecomp --config Release --parallel
```

---

## GOTCHA — `interop` is a global namespace, not `RT64::interop`

First build of 3b failed with eleven errors from one line, headed by:

```
error C3083: 'interop': the symbol to the left of a '::' must be a type
error C2039: 'float4x4': is not a member of 'RT64'
```

`interop::float4x4` is declared in `shared/rt64_hlsl.h` at **global** scope.
Every RT64 source refers to it as plain `interop::float4x4` from *inside*
`namespace RT64`, where ordinary lookup walks out to the global namespace and
finds it. Read from outside, that looks exactly like `RT64::interop`, and it is
not.

Host code must say `interop::float4x4`. `RT64::VrConfiguration` and
`RT64::VrEyeParams` are genuinely in `RT64`; only the matrix type is not, so the
two sit side by side in the same function with different qualification. That is
ugly and correct.

The error message earns its place here because it points at the `::` rather than
at the namespace, and because the same line also produces "is not a member of
RT64", which invites the conclusion that the header was not included. It was.

**Also worth knowing:** the link failed, so `GoldenRecomp.exe` on disk was still
the *previous* successful build. Running the exe after a failed build tests the
old binary, silently. Check that the build printed
`GoldenRecomp.vcxproj -> ...GoldenRecomp.exe` before trusting any run.

---

## Result — 3b passes, 2026-08-22

Run at `GE_VR_TEST_OFFSET` of `120`, `-120`, `30`, `-30`.

| Gate | Outcome |
|---|---|
| 1. Control identical | Pass |
| 2. Viewpoint slides sideways | Pass |
| 3. Mirrored equally by sign | Pass — the first-person gun sat at the far right under one sign and the far left under the other |
| 4. Straight edges stay straight | Pass — no shear reported at any magnitude |

**The host-supplied view transform reaches the geometry, in view space, with
correct sign symmetry. The eye split works.**

### The 120 run was a scale error, not a failure

At `120` the camera sat outside the player — Bond visible from the side, aiming
one way while the camera looked from the other — and swept a wide arc when
turning.

Both symptoms were correct behaviour at a wrong magnitude. `16-game-units.md`
established afterwards that 1 unit is about 1 cm, so `120` put each eye 1.2 m
from centre and the two eyes 2.4 m apart.

**The arc is the part worth keeping.** A lateral offset in *view* space rotates
with the view, so the eye position sweeps a circle of that radius as the head
turns. That is what a real eye does, and observing it is stronger evidence that
the transform landed in view space than the sideways slide is — a translation
applied in the wrong space would still slide, but it would not orbit.

### The first-person gun is the best instrument on the monitor

At `30` — about 30 cm — the gun swung from far right to far left as the sign
flipped, while the level geometry moved comparatively little.

That is parallax behaving correctly: the gun sits roughly 30-40 cm from the eye,
so a 30 cm lateral camera move swings it through something like 50 degrees, while
a wall ten metres away moves by under two. **Near objects move most.**

It also corroborates `16` independently. Had the scale been ten times smaller,
30 units would be 3 cm and the gun would barely have twitched; ten times larger
and the camera would have been 3 m out with the player model in frame, as it was
at `120`. Neither happened. The gun is now the standing check for anything that
moves the camera.

### Caveat on the comparison method

The runs were separate launches, so the two shots were not from an identical
position. The gun's screen position is a strong enough marker to carry the
symmetry judgement on its own, but a future test that needs finer comparison
wants a runtime toggle rather than a relaunch.
