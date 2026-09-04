# Step 3a — VR eye plumbing, inert

**2026-08-22. Written, not yet built.** The first slice of the hybrid eye split
designed in `12-phase1-step3-design.md`. It adds the per-eye camera path through
RT64 and **turns none of it on**. Nothing in the game should look different.

All five edited files have `.bak3a` backups beside them. The diff and the one new
file are captured in `local-only\thirdparty-diffs\rt64\` — which, per the licence
finding in `12` §7, is the MIT half and is publishable upstream.

## What changed

| File | Change |
|---|---|
| `render/rt64_vr_eye.h` | **NEW.** `VrConfiguration` (host state, per game frame) and `VrEyeOverride` (per render pass, derived by picking an eye). |
| `render/rt64_projection_processor.h` | `VrEyeOverride vrEye` on `ProcessParams`. |
| `render/rt64_projection_processor.cpp` | The eye camera composition, guarded by `vrEye.enabled`. |
| `hle/rt64_workload_queue.h/.cpp` | `vrEye` threaded through `threadRenderFrame`; added to the `processProjections` condition; snapshotted once per workload in `renderThreadLoop`. |
| `hle/rt64_shared_queue_resources.h` | `vrConfig` plus `setVrConfig()` / `getVrConfig()`, following the existing `setUserConfig()` locking pattern. |

## Three decisions inside it worth knowing

**Two structs, not one.** `VrConfiguration` is host state updated once per game
frame; `VrEyeOverride` is the selection for a single render pass. They are
separate because the eye varies per pass while the workload is shared between
passes — which is also why the override travels on `ProcessParams` rather than on
the `Workload`, where `DebuggerCamera` lives.

**The composition point is after the interpolation lerp, not in the debugger
camera slot.** The debugger camera sits inside `!debuggerCamera.enabled` guards
that switch frame interpolation off. Copying that placement would silently
disable the interpolation work from `04` and put 30 Hz judder into a headset. The
eye transform is applied to the already-interpolated view matrix instead:

```
viewMatrix = mul(viewMatrix, viewOffset)   // v * V * E * P, row-vector convention
projMatrix = eyeProj                        // replaced outright, not adjusted
```

The projection is replaced rather than scaled because the headset defines the
frustum — the aspect-ratio adjustment and the projection lerp applied earlier in
the function are both deliberately overwritten.

**`processProjections` had to be widened.** It was
`aspectRatioAdjustment || prevFrame.matched || isDebuggerCameraEnabled()`. Without
`|| vrEye.enabled` the whole projection processor is skipped on any frame with no
interpolation match — which is the first frame of every scene, i.e. exactly the
frames you look at while debugging. This would have presented as "the override
works, except when it doesn't".

## Building it

This touches only host C++ under `lib/rt64/`. No patch changed, so no `make`, no
`N64Recomp`, no `tools_weaken_patched.py` re-run. `07`'s GOTCHA 1 still applies —
the PATH line is not optional.

```powershell
$env:PATH = "C:\Program Files\LLVM\bin;C:\Program Files\CMake\bin;C:\Users\<USER>\AppData\Local\Microsoft\WinGet\Links;" + $env:PATH
cd C:\Users\<USER>\Desktop\GoldenEye64Recomp
cmake --build build --target GoldenRecomp --config Release --parallel
```

Expect a longer build than the usual minute: `rt64_shared_queue_resources.h` is
widely included, so most of RT64 recompiles.

## The gate

```powershell
cd C:\Users\<USER>\Desktop\GoldenEye64Recomp
build\Release\GoldenRecomp.exe
```

**Pass = the game is indistinguishable from before.** Load a level, move around,
open the watch, return to the menu. Frame rate unchanged.

This is a deliberately boring gate and it is the point of the step. Every later
step changes something visible; this one proves the plumbing is inert first, so
that when 3b does change the picture there is exactly one candidate explanation.

**Any visible change is a failure**, not a bonus — most likely `vrEye.enabled`
being true when nothing set it, or the widened `processProjections` condition
running the projection processor on frames that previously skipped it. The second
is the more interesting risk: it should be a no-op, because with the override
disabled `processScene` reproduces the matrices it was already producing, but it
is new work on frames that used to do none.

## Reverting

```powershell
cd C:\Users\<USER>\Desktop\GoldenEye64Recomp\lib\rt64\src
copy /Y render\rt64_projection_processor.h.bak3a   render\rt64_projection_processor.h
copy /Y render\rt64_projection_processor.cpp.bak3a render\rt64_projection_processor.cpp
copy /Y hle\rt64_workload_queue.h.bak3a            hle\rt64_workload_queue.h
copy /Y hle\rt64_workload_queue.cpp.bak3a          hle\rt64_workload_queue.cpp
copy /Y hle\rt64_shared_queue_resources.h.bak3a    hle\rt64_shared_queue_resources.h
del render\rt64_vr_eye.h
```

## Next

3b: a host-side call to `setVrConfig()` with hardcoded left-eye constants, so the
override actually fires. Nothing in RT64 needs to change for it — that is the
test of whether 3a drew the boundary in the right place.
