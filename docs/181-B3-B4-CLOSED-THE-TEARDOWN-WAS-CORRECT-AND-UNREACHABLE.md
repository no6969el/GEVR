# 181 — B3 AND B4 ARE CLOSED. THE TEARDOWN WAS ALWAYS CORRECT AND NEVER RAN.

**2026-08-26. Built and WORN. The X was pressed on purpose and the machine lived.**
**Tiered per `182`.**

> # ►►►► `shutdown: complete, clean` ◄◄◄◄
>
> **`[MEASURED]`, 2026-08-26, `gevr.log:42968-42983`, closed with THE X:**
>
> ```
> [gevr-xr] teardown: quit requested entered, draining present thread
> [gevr-xr] teardown: present thread drained
> [gevr-xr] shutdown: begin
> [gevr-xr] shutdown: session ended
> [gevr-xr] shutdown: gpu idle (confirmed)
> [gevr-xr] shutdown: xr session destroyed
> [gevr-xr] shutdown: complete, clean
> [gevr-xr] teardown: deinit hook entered, draining present thread
> ```
>
> **`[REPORTED]` — the owner: *"I hit it with x and it closed"*.**
>
> **NOT ONE OF THOSE LINES HAS EVER APPEARED IN ANY LOG THIS PROJECT HOLDS.**

---

## §1 — WHY FIVE SESSIONS COULD NOT FIX IT

**`[READ]` `src/main/ge_vr_xr.cpp:2937` — the ordered teardown is CORRECT.** It
was correct before this session. It drops the eye pointers before anything can
free them, ends the session before destroying what it refers to, waits on the
fence and honours the result (`149`), and takes `40`'s deliberate-leak branch
when the drain times out. **Every session that looked at B3 looked HERE, and
found nothing wrong, because there IS nothing wrong.**

> ## **THE FAULT WAS NEVER IN THE TEARDOWN. IT WAS IN WHO CALLED IT.**

**`[READ]` `src/game/input.cpp`, before this session: the only trigger was
`SDL_QUIT`**, and `begin_shutdown()` did nothing but drain — it left the session,
swapchains and instance for the deinit hook.

**`[MEASURED]` `147`: B4 was run deliberately on 2026-08-24 with `149` compiled
in, and the machine bugchecked with NO `shutdown:` line at all** — the log stops
mid-gameplay at `90.0 fps | LATE 0/91`. **`42` recorded the identical signature.**

## §2 — `SDL_QUIT` IS QUEUED. THAT IS THE WHOLE BUG.

`42` called `SDL_QUIT` *"the first moment the process knows it is exiting, and
the last moment that is reliably ours."* **The first half is false.**

**`[READ]` `input.cpp:331`: events are seen only when the main loop reaches
`SDL_PollEvent`.** Between the click on the X and that poll, Windows has already
delivered `WM_CLOSE` and begun destroying the window — **while the present
thread is still handing OpenXR frames at 90 Hz on a device whose swapchain is
going away.**

**AND THE MAIN LOOP IS THE WORST PLACE TO WAIT:** the state this fires in is
precisely one where the main loop may be blocked behind a stalled present
thread. **A fix that depends on the main loop being responsive cannot fire in
the case it exists for.**

## §3 — THE FIX. TWO CHANGES, NEITHER IN THE TEARDOWN.

**1. `SDL_AddEventWatch` — `input.cpp`.** A watcher runs **synchronously, on the
thread that POSTS the event, before it is ever queued.** That is the earliest
this process can know, and it does not depend on the main loop at all. It
catches `SDL_WINDOWEVENT_CLOSE` **and** `SDL_QUIT`; `SDL_WINDOWEVENT_CLOSE` also
now goes through the main switch as a queued-path backstop. Registered on the
first pump, so it needs no new call site and cannot run before SDL is up.

**2. `begin_shutdown()` now PERFORMS the teardown — `rt64_render_context.cpp`.**
It used to drain and stop. **`[READ]`: the D3D12 device, queue and fence are all
still alive at `WM_CLOSE` — the WINDOW is dying, not the device — which is
exactly what OpenXR requires to be destroyed rather than abandoned.**
`xr_shutdown` latches `done`, so the deinit hook re-entering on the ordinary
path is a no-op — **`[MEASURED]`: the log shows precisely that, the hook enters,
drains, and finds nothing left.**

## §4 — THE GENERAL LESSON, AND IT IS NOT ABOUT SDL

> ## **A CORRECT MECHANISM THAT IS NEVER INVOKED IS INDISTINGUISHABLE FROM A BROKEN ONE — AND IT ATTRACTS ALL THE DEBUGGING.**

**`149` improved the fence wait inside a function nothing called. `40` added a
safe branch to a function nothing called.** Both were right, both were worn, and
both changed nothing, **because the reachability question was never asked.**

**THIS IS THE SAME SHAPE AS `178`** — the virtual screen was built inside
`ge_vr_timewarp_create()`, which only runs under a knob that is off by default,
so it never ran and its diagnostic never printed. **Twice in one session.**

> **BEFORE DEBUGGING WHAT A FUNCTION DOES, GREP ITS CALL SITES AND PROVE IT RUNS.**
> **A log line INSIDE the thing you are testing is the cheapest proof there is** —
> and its ABSENCE is a finding, not a gap. `178` and this were both found by
> noticing that a line which should have printed did not.

## §4b — CONFIRMATION #2, AND IT WAS THE HARDER RUN

**`[MEASURED]` 2026-08-26, second X close, `gevr.log:207853-207876`.** Identical
clean sequence through `shutdown: complete, clean`.

**AND THIS ONE WAS NOT A CHEAP CLOSE.** The first was a short session. This was
a long in-level run at **90 fps, full stereo, `ds_option 4`** - the heaviest GPU
state this project has ever torn down, and the closest to the conditions under
which B3 originally bugchecked five times. **`[REPORTED]` the owner: *"I close
successfully with the X again"*.**

**TWO OF THE THREE-TO-FOUR CLOSES `§5` ASKS FOR ARE NOW DONE.**

## §5 — WHAT IS NOW OWED

**B3 and B4 close.** `39` has had both marked BLOCKING since `75`.

**`[ASSUMED]` — ONE RUN IS ONE RUN.** B3 bugchecked *five* times before, but
never on every close. **What would settle it: three or four more X closes across
different sessions.** They cost nothing now — just stop using `taskkill` and
watch for `shutdown: complete, clean`.

**AND `vr.ps1` NOW WAITS ON THE PROCESS** to print its exit verdict, so the X is
the natural close from here anyway.
