# 27 — the XR startup crash: a clobbered render hook, and a typeless swapchain image

**2026-08-22.** `00-START-HERE` left one open problem: with `GE_VR_XR=1` the game
crashes before reaching its own ROM picker. This is the cause, and it is not in
the OpenXR code at all.

## What the session started from

Three things were true before any diagnosis, and two of them were already
answered by evidence sitting on disk:

| Claim in `00-START-HERE` | Actual state |
|---|---|
| "The fix was never compiled" | It was. `rt64_render_context.cpp` 13:54, `GoldenRecomp.exe` 13:56. A rebuild is a no-op |
| "Check the game still launches" | `gevr.log` 13:56:46 — a clean XR-off run, 60 fps, ~180 passes/s |
| "XR crashes before writing a line of `gevr.log`" | **Still true.** Exit code `0xC0000005` |

So the build is green and the baseline is healthy. Only the XR path is broken.

## The diagnostic that moved it

Run with `GE_VR_XR=1`, 25 seconds, read the log:

```
[gevr-xr] GE_VR_XR is set - OpenXR will start once RT64 is up.
```

One line, then an access violation. **That single line relocates the crash.** It
is written from the `RT64Context` constructor immediately after `SetRenderHooks`,
so the crash is not before the log — it is after hook registration and before
anything the XR frame loop does. `g_ge_vr_app_ready` was never the problem, and
the prime suspect in `00-START-HERE` — the present thread reaching a
half-constructed `Application` — is wrong.

## The cause

RT64's render hooks are **three global function pointers, not a list**
(`lib/rt64/src/rhi/rt64_render_hooks.cpp`). `SetRenderHooks` assigns all three
unconditionally.

`RT64Context`'s constructor calls `recompui::set_render_hooks()` at its very top,
which installs the launcher UI's `init_hook` / `draw_hook` / `deinit_hook`. One
hundred lines later, ours does:

```c
RT64::SetRenderHooks(nullptr, ge_vr_render_hook_draw, nullptr);
```

That **erases all three of recompui's hooks.** `init_hook` is what constructs
`ui_context` — the RmlUi context, the render interface, the launcher and config
menus. It never runs, `ui_context` stays a null `unique_ptr`, and the first
`recompui::` call on the main thread dereferences it.

The symptom reads exactly right once you know: *the game never reaches its own
ROM picker*, because the ROM picker is the thing that was deleted.

## Why this hid so well

It presented as an OpenXR bug and was investigated as one for two rounds — a
frame loop moved between threads, a `SYNCHRONIZED` gate, a release-before-submit
ordering fix. All three of those were real bugs and all three are still fixed.
None of them was this one.

The tell that was available all along: **XR being off by default made the game
work.** That was read as "the XR code is dangerous", which is true but incidental.
The sharper reading is that the *only other thing* the opt-in switch gates is the
`SetRenderHooks` call, and that call touches nothing OpenXR-shaped.

Third time this project has been bitten by the same shape, after `21` and the
zoom leak in `26`: **a change that is correct in its own terms writes over state
someone else owns.** The rule from `26` was "when a patch changes a value the game
stores, check who reads it back." The generalisation is now unavoidable — *check
who else writes it.* A global setter with no chaining is a value the game stores.

## The fix — chain, do not replace

RT64 already exports the getters. Capture what is installed, install wrappers,
forward.

```c
static RT64::RenderHookInit   *g_prev_init   = nullptr;
static RT64::RenderHookDraw   *g_prev_draw   = nullptr;
static RT64::RenderHookDeinit *g_prev_deinit = nullptr;
```

Each wrapper calls the previous hook **first**, then does our work. Order is not
cosmetic: recompui's `draw_hook` renders the UI into the swap-chain framebuffer,
and calling it first leaves the existing frame identical to what it is today,
with our XR work appended rather than interleaved.

The `g_ge_vr_app_ready` guard stays. It was written against a hazard that is real
even though it was not this crash, it costs one relaxed atomic load per present,
and removing it now would be removing a guard because it failed to catch a bug it
was never aimed at.

## Gates

Written to the standard from `00-START-HERE` — *what would this build have to do
differently for each of these to fail?*

| # | Check | Pass | What failure would mean |
|---|---|---|---|
| 1 | `GE_VR_XR=1`, launch | Process **does not exit** with `0xC0000005`; reaches the ROM picker | Still clobbering, or a second independent crash behind this one |
| 2 | `GE_VR_XR=1`, `gevr.log` | Lines **past** the `GE_VR_XR is set` line — runtime name, system name, LUID, session created | The hook is chained but our own path never runs |
| 3 | `GE_VR_XR=1`, the UI | Launcher menu appears and is interactive | `init_hook` restored but `draw_hook` not, or the order is wrong |
| 4 | `GE_VR_XR` unset | 60 fps, unchanged from the 13:56:46 log | The chaining broke the default path — the one that must never break |

Gate 4 is the one that matters most and is the easiest to skip.

**Not in scope, and expected to still be wrong:** anything in the headset. The
3f-2 gate — left eye red, right eye blue — is the *next* step, and reaching it
requires this crash gone first. `27` claims only that the game survives XR being
switched on.

---

# Result — both gates cleared, and a second bug behind the first

## The hook clobber was real, and it was not the whole story

Chaining the hooks moved the crash a long way. Same command, same 30 seconds:

```
[gevr-xr] render hooks chained (prev init=...6900 draw=...5450 deinit=...5380)
[gevr-xr] runtime: SteamVR/OpenXR 2.16.7
[gevr-xr] adapter LUID match: yes
[gevr-xr] eye 0 swapchain: 4140x3292, 3 images
[gevr-xr] xrBeginSession ok - frames start submitting now.
[gevr-xr]   frame 0: ... executed ... released images
[gevr-xr] first layer submitted - left eye red, right eye blue.
[gevr-xr]   frame 0: endFrame returned
<access violation>
```

The entire 3f-2 path ran. A layer was submitted. Then it died before frame 1.

## Making the crash describe itself

Rather than a fourth round of inference, an unhandled-exception filter went in
(`ge_vr_crash_filter`, installed only under `GE_VR_XR`). It logs the exception
code, the faulting address, and every stack frame as `module+RVA`. Relinking
with `/MAP` — one CMake flag, no recompile — turns those into names:

```
access violation READING address 0x0
fault at  GoldenRecomp.exe+0x517692  ->  RT64::D3D12SwapChain::resize + 0xD2
  frame 8 GoldenRecomp.exe+0x4FA2CE  ->  RT64::PresentQueue::threadLoop + 0x2DE
```

Two runs, from "somewhere after the XR frame loop" to a function and an offset.
**This is the tooling the project should have had four crashes ago**, and it now
costs nothing to keep.

## What `resize + 0xD2` actually is

```c
bool D3D12SwapChain::resize() {
    ...
    for (uint32_t i = 0; i < textureCount; i++) {
        textures[i].releaseTargetHeap();
        textures[i].d3d->Release();          // <-- +0xD2, null on the second call
        textures[i].d3d = nullptr;
    }
    if (FAILED(d3d->ResizeBuffers(...))) {
        fprintf(stderr, "ResizeBuffers failed ...");   // no console. invisible.
        return false;
    }
    setTextures();
    return true;
}
```

and its only caller:

```c
swapChainValid = ext.swapChain->resize();
... const bool needsResize = ext.swapChain->needsResize() || !swapChainValid;
```

**A failed `ResizeBuffers` leaves every texture released and null, returns false,
and the loop calls `resize()` straight back — into the nulls it just wrote.** The
crash is always the *second* call. The first one is the real event, and RT64
reports it to a stream that a `/SUBSYSTEM:WINDOWS` process does not have.

So the crash location was a red herring twice over: not our code, and not even
the failure.

## The actual bug: a typeless swapchain image

`GetDeviceRemovedReason()` — one call, added at end of frame — answered it:

```
[gevr-xr] *** D3D12 DEVICE REMOVED at end of frame: 0x887A0001 ***
```

`DXGI_ERROR_INVALID_CALL`. The device was removed because *we* issued an invalid
call, and the confirming log line is unambiguous:

```
[gevr-xr] swapchain image: format 27 (chose 29), 4140x3292, flags 0x1
```

**27 is `R8G8B8A8_TYPELESS`. 29 is the `R8G8B8A8_UNORM_SRGB` we asked for.**
SteamVR allocates the images typeless so the application can take either an sRGB
or a linear view of them — and we called:

```c
g_device->CreateRenderTargetView(resource, nullptr, rtv);
```

A null `pDesc` means *infer the format from the resource*. A typeless resource
has no format to infer. D3D12 does not return an error for this; it removes the
device, one frame later, on a different thread, inside somebody else's code.

Fixed with an explicit `D3D12_RENDER_TARGET_VIEW_DESC` carrying the format we
chose — which is what `hello_xr` does, for exactly this reason.

## Gates

| # | Check | Result |
|---|---|---|
| 1 | `GE_VR_XR=1` survives launch | **Pass.** 30 s, no exit |
| 2 | `gevr.log` past the opt-in line | **Pass.** Runtime, system, LUID match, both swapchains, session begun |
| 3 | The UI | **Pass.** Reaches the game, `[gevr]` fps lines flowing |
| 4 | `GE_VR_XR` unset | **Pass.** 60 fps, unchanged |

Session state reached `VISIBLE` and frames submit continuously:

```
[gevr-xr] session state -> SYNCHRONIZED -> VISIBLE
[gevr]    60.0 fps | render passes: eye0=132 eye1=0 distinctTargets=0
```

**Frame pacing is clean.** `26` risk 4 predicted judder from `xrWaitFrame` owning
the cadence and said not to chase it. On the present thread, at 60 fps, it did
not appear. The interlock is still Phase 2's job; it is simply not urgent.

## The 3f-2 gate itself — left red, right blue — is a human observation

Everything a program can check about it passes. Whether the headset actually
shows the tint is the one thing the machine cannot report.

## New knob: `GE_VR_XR_LEVEL`

The bisect ladder from `00-START-HERE` is now a runtime switch instead of a code
edit, so its three rungs are three launches rather than three builds.

```
GE_VR_XR_LEVEL=0   session and event loop only (this is 3f-1)
GE_VR_XR_LEVEL=1   frame loop, layerCount = 0, no D3D12 work at all
GE_VR_XR_LEVEL=2   full 3f-2 (default)
```

## Three rules this cost, all the same shape

1. **`21`:** a patch changed a value the game inspects.
2. **`26`:** a patch changed a value the game *reads back and compares*.
3. **`27`:** we changed a global the *host* owns — and then made an invalid call
   whose only report was a device removal on another thread.

The common factor is not arithmetic. It is **writing into something you do not
own, and the owner having no way to tell you.** Both fixes are the same fix:
chain instead of replace, and state explicitly instead of letting something be
inferred.

And the meta-lesson, which is now paid for: **when a crash cannot be reproduced
in a debugger, the fix is not more inference — it is making the program report
its own failure.** The exception filter and `/MAP` cost one build. They resolved
in two runs what four rounds of reasoning had not.

## Files changed

| File | Change |
|---|---|
| `src/main/rt64_render_context.cpp` | Chain render hooks; `ge_vr_crash_filter` |
| `src/main/ge_vr_xr.cpp` | Explicit RTV desc; `checkDeviceRemoved`; `GE_VR_XR_LEVEL` |
| `build` config | `CMAKE_EXE_LINKER_FLAGS_RELEASE="/INCREMENTAL:NO /MAP"` |

No new `RECOMP_PATCH` names, so the short build applies. Still **31** renamed.

Resolving an address from a future crash:

```
python  # against build\Release\GoldenRecomp.map, preferred base 0x140000000
```

## Next

**3f-3** — copy RT64's two eye targets into the swapchain images instead of
clearing them, and settle `GE_VR_EYE_SIGN` by observation. The tint test comes
first, before any judgement of the picture, per `10`.

The floor calibration in `10` is now on the critical path: `26` said it was not
needed for 3f-1 or 3f-2, and 3f-3 is where that stops being true.

---

# 3f-2 gate: PASSED, 2026-08-22

**Reported from the headset: red and blue, one colour per eye, filling the view.
The game continues to run and is playable on the monitor.**

That is 3f-2 exactly as `26` specified it. Both swapchains are being written,
both are reaching the compositor, and the layer is accepted — "both eyes the same
colour" (a single-eye submission) and "still in the loading area" (a rejected
layer) are both excluded by observation rather than by inference.

With the headset awake the session also reaches **`FOCUSED`**, which it never did
while the headset was asleep. It oscillates `VISIBLE` <-> `FOCUSED` as window
focus moves between the game and the SteamVR compositor; frames submit in both
states, so this is not a fault.

**The game not appearing in the headset is correct for this slice.** 3f-2 submits
flat colour and deliberately does not touch RT64's eye targets. Putting the
game's own images there is 3f-3.

## Phase 2 status after 3f-2

| Slice | State |
|---|---|
| 3f-1 session on RT64's device | Done, `26` |
| 3f-2 swapchains, frame loop, layer submission | **Done and confirmed in the headset** |
| 3f-3 the game's eyes, and the tint test | Next |
| 3f-4 live pose and FOV | After 3f-3 |

Everything between the game's rendered eye images and the compositor is now
proven end to end. What remains in 3f-3 is a copy.
