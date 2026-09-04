# OpenXR probe — measured facts about the rig's headset

**2026-08-22. Ran successfully against real hardware.** Source and full report in
`xrprobe/`. This replaces guesswork with numbers.

## THE HEADSET IS NOT A QUEST 3

`05-going-forward.md` says "Quest 3 over Link" and the strategy notes reason from
it. The rig actually drives a **Pimax on SteamVR**. Both runtimes are installed;
SteamVR is the active one and that is correct — do not flip it to Oculus.

This does not overturn the PCVR-first decision, which was always about targeting a
PC-fed headset rather than standalone Android. It does mean every sentence saying
"Quest 3 over Link" should read "PCVR, currently a Pimax on SteamVR, Quest 3 over
Link also viable".

## What the runtime reports

| | |
|---|---|
| Runtime | SteamVR/OpenXR 2.16.7 |
| System name | `SteamVR/OpenXR : aapvr` |
| GPU | NVIDIA GeForce RTX 5090 (runtime requested this adapter by LUID) |
| Refresh rate | 90 Hz, single option |
| Recommended per-eye target | **4140 x 3292**, 1 sample |
| Max swapchain | 8192 x 8192, 16 layers |
| Reference spaces | VIEW, LOCAL, STAGE |
| Blend modes | 1 (opaque) |
| D3D12 support | yes (`XR_KHR_D3D12_enable`) |

## Per-eye geometry — the numbers Phase 1 was guessing

```
LEFT   fov  outer -53.99 deg  inner +46.01  up +45.50  down -45.50   (H 100.0, V 91.0)
LEFT   tan  L -1.3760  R +1.0358  U +1.0176  D -1.0176
RIGHT  fov  outer +53.99 deg  inner -46.01  up +45.50  down -45.50   (H 100.0, V 91.0)
RIGHT  tan  L -1.0358  R +1.3760  U +1.0176  D -1.0176

IPD          63.5 mm
eye yaw L/R  -57.874 / -57.874 degrees   (identical — this is head yaw, not cant)
total cant   0.000 degrees
```

## The cant question, asked and answered

Pimax is known for canted panels on some models, and a canted headset cannot be
served by per-eye *projection* alone — each eye's view matrix needs its own yaw,
or the two images do not fuse. That failure presents as eye strain and a world
that will not sit still, not as an obviously broken picture, so it is expensive to
find late. The probe was written specifically to test it.

**Result: cant is 0.000 degrees. The panels are parallel.** Both eyes report the
same yaw because that is the *head's* orientation, shared by both views — the
number to look at is the difference, and it is zero.

So `ge_vr_bindtest.c`'s parallel-eye assumption holds, and Phase 1 step 2 remains
"IPD offset on the view matrix", not "IPD and cant". Hypothesis tested and
disproven, which is the cheap outcome and the reason to test it.

**This is a property of this unit at this configuration, not of Pimax generally.**
Re-run the probe if the headset changes. `geVrGetEyeParams()` querying the runtime
makes the question moot, which is the real fix.

## The stand-in constants were wrong, and wrong in a costly way

`ge_vr_bindtest.c` shipped with plausible Quest 3 tangents. Against the real
headset:

| | guessed | measured | error |
|---|---|---|---|
| Horizontal per eye | 94 deg | 100.0 deg | 6 deg narrow |
| **Vertical** | **105 deg** | **91.0 deg** | **14 deg wide** |
| Inner/outer split | 42 / 52 | 46.01 / 53.99 | mild |

The vertical error is the one that matters. A frustum 14 degrees too tall renders
a world that looks too small and too far away — and that symptom gets blamed on
world scale, or on the per-level `room_data_float2` visibility scale, long before
anyone suspects the projection. **The measured values are now in the patch and
`GoldenRecomp.exe` has been rebuilt with them.**

## Consequences for Phase 2

1. **Resolution.** The runtime wants 4140 x 3292 per eye — 27 megapixels a frame
   at 90 Hz across both eyes. Absurd for an N64 game on its face, but RT64
   upscales, so it is not automatically wasted. Expect to render well below
   recommended and let the runtime scale. A knob, not a requirement.
2. **90 Hz is the only rate offered.** The interpolation work targets exactly this
   and is therefore not optional for comfort — it is what makes 90 Hz from a
   30/25 Hz game possible at all.
3. **D3D12 binding is available and the runtime names the adapter by LUID.** RT64
   must end up on that same adapter. On this single-GPU rig it will; the probe
   checks and reports it, and that check should survive into the real integration.
4. **Request OpenXR 1.0, not 1.1** — see below.

## GOTCHA — `XR_CURRENT_API_VERSION` fails against SteamVR

The Khronos loader 1.1.62 headers define `XR_CURRENT_API_VERSION` as OpenXR
**1.1**. SteamVR implements **1.0** and rejects the instance with
`XR_ERROR_API_VERSION_UNSUPPORTED` (-4). The loader surfaces this only as:

```
Error [GENERAL | xrCreateInstance | OpenXR-Loader] :
    LoaderInstance::CreateInstance chained CreateInstance call failed
```

which names neither the version nor the runtime. Worse, extension enumeration
succeeds first — handled inside the loader, never reaching the runtime — so
everything looks healthy right up to instance creation.

**Request `XR_API_VERSION_1_0` explicitly.** Every 1.0 runtime accepts it and 1.1
runtimes stay backward compatible. This will bite again in the real integration if
someone copies a sample that uses `XR_CURRENT_API_VERSION`.

## Getting the loader

Khronos ships no plain zip for Windows. The loader is inside the NuGet package
attached to the OpenXR-SDK release — a `.nupkg` is a zip:

```
https://github.com/KhronosGroup/OpenXR-SDK/releases/download/release-1.1.62/OpenXR.Loader.1.1.62.nupkg
```

Extract; headers in `include/openxr/`, import lib and DLL in
`native/x64/release/{lib,bin}/`. The DLL must sit beside the exe.

## Building and running the probe

Working copy lives at `C:\Users\<USER>\Desktop\ge-vr-xrprobe\`. From a VS developer
shell in that directory:

```
cl /std:c++17 /EHsc /O2 /nologo xr_probe.cpp /I lib\openxr\include ^
   /link lib\openxr\native\x64\release\lib\openxr_loader.lib d3d12.lib dxgi.lib
```

Start SteamVR first. If the headset is asleep the probe says so explicitly rather
than printing garbage — poses come back flagged invalid and it reports the session
state it reached.

## Where this code belongs

`xrprobe/` here is a snapshot. The probe is host-agnostic and has no dependency on
the recomp tree, so it belongs in **`goldeneye-native`** (the MIT repo) alongside
`phase0/`, not in `GoldenEye64Recomp`. Move it there when that repo is restored
from the bundle — see `08-where-everything-comes-from.md`.
