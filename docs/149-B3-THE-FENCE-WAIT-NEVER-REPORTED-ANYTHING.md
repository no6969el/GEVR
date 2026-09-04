# 149 — B3 / O21. THE FENCE WAIT IGNORED EVERY RESULT IT GOT.

**2026-08-24, end of session. A read and a small fix. NOT COMPILED, NOT WORN.**

`148` 6D-00 named B3 the highest-value task in the project. `39` named the fix:
*"honour the fence wait's result."* **This is that, and the code was worse than
the note suggested.**

---

## §1 — WHAT WAS THERE

```cpp
void waitForGpu() {
    const uint64_t value = ++g_fenceValue;
    g_queue->Signal(g_fence, value);                    // result ignored
    if (g_fence->GetCompletedValue() < value) {
        g_fence->SetEventOnCompletion(value, g_fenceEvent);   // result ignored
        WaitForSingleObject(g_fenceEvent, 1000);              // result ignored
    }
}
```

**Three results, none of them read.** And the caller:

```cpp
if (g_queue && g_fence && g_fenceEvent) {
    waitForGpu();
    ge_vr::log("[gevr-xr] shutdown: gpu idle\n");    // printed unconditionally
}
```

> ## **`WAIT_TIMEOUT` MEANS THE GPU IS STILL EXECUTING. THE NEXT STEPS DESTROY THE SWAPCHAINS, THE COMMAND ALLOCATOR, THE COMMAND LIST AND THE FENCE — UNDERNEATH IT.**

**That is hazard 2 in `xr_shutdown`'s own header comment**, written by whoever
built the ordered teardown: *"Our command allocator, list and fence were released
while the GPU could still be executing work that referenced them."* **The
ordering was fixed. The proof that the ordering had finished was not.**

**AND THE LOG SAID `gpu idle` ON EVERY RUN THAT TOOK THE MACHINE DOWN.** `48`
rule 4 — an instrument whose name promised more than it measured. **The fourth
instance this session** (`134`, `136`, and the print gate on a garbage global).

### THE WORSE CASE, AND IT IS NOT HYPOTHETICAL

**If `Signal` fails — which is exactly what a removed device does, and there is a
`D3D12 DEVICE REMOVED` logger twenty lines above this function — the fence can
NEVER reach the value.** The wait then times out every single time, and the
teardown proceeded anyway, on a device that had already gone. **B3 is
`0x139 arg1=3` (LIST_ENTRY corruption), five times, never under `-NoXr`.**

---

## §2 — THE FIX, AND IT REUSES A BRANCH THAT ALREADY EXISTS

**`waitForGpu()` now returns `bool`** — true only when the GPU is confirmed
idle — and checks all three results, logging which one failed.

**The caller takes the SAME deliberate-leak branch that `40` already built for an
undrained present thread:**

```
[gevr-xr] shutdown: ABANDONED - the GPU could not be confirmed idle.
[gevr-xr]   Leaking XR + D3D12 objects deliberately; the OS reclaims them.
[gevr-xr]   Releasing them now is what takes the DRIVER down. B3, docs\149.
```

**That branch is proven** — it is the one that made force-killing safe. `40`'s
reasoning applies word for word: *"The process is exiting; Windows reclaims the
handles, the device and the memory within milliseconds. Destroying a session, a
swapchain or a command list while another thread is still inside the runtime is
how a game crash becomes a MACHINE crash."* **The same is true of the GPU.**

**A missing fence is now also a refusal**, not a silent skip: if there is nothing
to wait on, nothing can be proven idle, and hazard 2 applies regardless.

**The frame-loop call site is UNCHANGED in behaviour** — `(void) waitForGpu()`.
A missed wait there costs one frame; on the shutdown path it costs the machine.
**One behaviour change per build.** `48` rule 5.

---

## §3 — WHAT THIS DOES AND DOES NOT CLAIM

**IT DOES NOT PROMISE B3 IS FIXED.** It removes one specific, verified way for
the teardown to run while the GPU is live. **B3 has five recorded instances and
this explains all of them only if the wait was timing out** — which nobody has
ever checked, **because the log printed `gpu idle` either way.**

> ### **THE FIRST RUN IS THEREFORE A DIAGNOSTIC WHETHER OR NOT IT CRASHES.**
> **`shutdown: gpu idle (confirmed)`** -> the wait was always succeeding, B3 is
> something else, and the search moves on with one hazard permanently closed.
> **`shutdown: ABANDONED - the GPU could not be confirmed idle`** -> **that was
> it**, it has been happening silently all along, and the machine should now
> survive the close.

**THE TEST IS THE ONE THING NOBODY HAS BEEN ABLE TO AFFORD: close a VR session
with the X, on purpose.** That is B4, it costs a reboot if it still bugchecks,
and **it is now worth spending one** — because for the first time the log will
say which branch ran.

**Until it is run, keep closing with `taskkill /F /IM GoldenRecomp.exe`.**
