# 42 — stop submitting XR frames at SDL_QUIT

> ## THIS DOCUMENT WAS NEVER WRITTEN. Stub added 2026-08-23 so the citations
> ## resolve. **No content invented or removed.** See `00-START-HERE`,
> ## "The phantom documents".

## What `42` names

`ge_vr::begin_shutdown()` — ending XR submission and draining the present
thread at the FIRST moment the process knows it is quitting, rather than in the
render deinit hook.

## Where it lives — and the reasoning survives verbatim in the source

`src\game\input.cpp:181`:

> **docs\42. STOP SUBMITTING XR FRAMES HERE.**
> This is the first moment the process knows it is exiting, and it is the last
> moment that is reliably ours. Once both eyes were really rendering at
> 5838x4498, closing the window bugchecked the machine
> (KERNEL_SECURITY_CHECK_FAILURE 0x139) **BEFORE the render deinit hook logged
> its first line** - so every safeguard that lived in that hook was
> unreachable, which is why the log for that run simply stops.

Also `src\main\rt64_render_context.cpp:401`, and the declaration comment in
`include\ge_vr_host.h`.

## CORRECTED BY `59` — its central premise is FALSE

> *"This is the first moment the process knows it is exiting."*

**`SDL_QUIT` does not mean the process is exiting.** `input.cpp:180-207` shows
that with a game running it sets the recompui menu to `Config` and calls
`ultramodern::quit()` — **stop the GAME, show the menu, keep the process
alive** — and `begin_shutdown()` latches through a one-shot flag that is never
reset. See `59` (O45) for what that does and does not explain.
