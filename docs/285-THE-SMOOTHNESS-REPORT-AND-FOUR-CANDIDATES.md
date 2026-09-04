# 285 — THE SMOOTHNESS REPORT. STANDING SINCE BRING-UP, NEVER DIAGNOSED, AND IT OUTRANKS THE HOLES.

**2026-08-31. NO BUILD, NO RUN YET.** Source read only. Written the moment the report was made so
it cannot be lost again — **rule `16`: a repeated owner report is a RANKING error, not noise.**

> ## THE REPORT, VERBATIM
> **`[REPORTED]`** *"When you turn real fast, I feel like it's waiting or something. It's not the
> smoothness that I want."* · ran 120 Hz to check: *"it definitely smoothed out, but it seems like
> it's still locked to something... it just feels weird. And it's always been that way since we've
> been working on the entire resolutions."*

**THIS HAS BEEN PRESENT FOR THE WHOLE PROJECT AND HAS NEVER HAD A DOC, A NUMBER OR AN ARM.**
`134`/`147` measured that 90 Hz is *achievable* and worn as "totally playable"; `277` measured that
the WORLD runs at retail speed. **Neither of those is a measurement of SMOOTHNESS**, and nothing in
`92`-`284` measures the interval between presented frames.

---

## §1 — FOUR CANDIDATES, ALL FROM SOURCE, NONE MEASURED. DO NOT ACT ON ANY OF THEM.

### 1. ►► THE PACER ASSUMES ITS OWN SLEEP WAS EXACT
`gfx_sdl2.c:580-604`, `sync_framerate_with_timer()`:
```c
sys_sleep(remain / perf_freq * 1000000.0);
...
frame_time = now + remain;   /* "Assume we slept the required amount of time" */
```
**`[INFERRED]`** `sys_sleep` on Windows overshoots — it is a scheduler wait, not a spin — and the
pacer books the sleep it ASKED for, not the one `271` already measures (`ge_pace_wait_ms`, right
there in the same function). The error accumulates into `frame_time`, so the cap alternates between
sleeping and not sleeping. **Average rate correct, individual intervals uneven.** That is the exact
shape of "the number says 60 but it does not feel like 60".
**`271` already has the honest figure two lines above. Nothing consumes it.**

### 2. ►►►► EVERY ARM THIS PROJECT HAS EVER RUN SET `GETV_VSYNC=0` ◄◄◄◄
It is in every run sheet, including the four I wrote today. It came from `273`, which NEEDED it —
an uncapped GPU sample is impossible behind a vblank wait — and it has been copied forward ever
since **into runs that are not measuring the GPU at all.**
`gfx_sdl2.c:413-421` says so in its own comment: *"Off by default is wrong for most people... this
is the escape hatch for benchmarking."* **The session lead has been playing the benchmarking
configuration for the entire project.**
**`[INFERRED]`** with the swap interval released, presented frames land at an arbitrary phase
against the panel's refresh, so some are shown twice and some once — **judder that gets smaller at
higher frame rates without ever going away**, which is precisely the `[REPORTED]` 120 Hz result.
**THIS IS THE CHEAPEST THING TO TEST IN THE WHOLE PROJECT AND IT NEEDS NO BUILD.**

### 3. THE WORLD ADVANCES PER FRAME, NOT PER SECOND
`[MEASURED]`, standing: the synthetic timebase advances exactly one field per rendered frame
(`274`, `277`; the banner reads `clock: synthetic timebase (GETV_REALCLOCK=0) -- speedgraphframes
is deterministically 1`). **Motion is therefore uniform in FRAMES, not in TIME.** If the intervals
between presented frames are uneven (§1.1, §1.2), the motion is uneven no matter how correct the
average is. `GETV_SIMHZ` (`276`, `277`) fixes the world's SPEED; **it does not make the step
proportional to the time the frame actually took.**

### 4. THE TURN ITSELF MAY HAVE NO TIMESTEP
`277` §4 `[MEASURED]` that **Bond's walk advances an exponential approach once per FRAME with no
timestep** (`bondview2.c:7237`/`:7411`) and that `GETV_SIMHZ` does not touch it. **Whether the
LOOK/TURN rate is in the same family has never been checked** — and the report is specifically
about turning. `[OPEN]`, source-read not yet done.
Adjacent and possibly the same thing: `00-STATE` §3's *"crosshair auto-centres; aiming with the
mouse fights it — it keeps putting you back"*, which is also `[REPORTED]` and also undiagnosed.

## §2 — WHAT IS NOT YET KNOWN AND MUST BE ASKED, NOT ASSUMED
- **The panel's refresh rate.** Every candidate above is about the relationship between the game's
  rate and the display's, and nothing in any log records the display. **It is not in a single one
  of the 40-odd run logs.**
- Whether the feel differs between mouse and pad. §1.4 would; §1.1 and §1.2 would not.
- Whether it is present in the front-end menus (no world simulation there) — that separates
  presentation from simulation in one look.

## §3 — THE ORDER, AND WHY
1. **Vsync on, capped at the panel's own rate.** No build. If the feel changes, §1.2 is it and the
   whole project has been mis-configured rather than broken.
2. **The same, with `GETV_SIMHZ` on**, so the world's speed is right at that rate.
3. **Only then** an instrument: the DISTRIBUTION of presented-frame intervals — not the mean, which
   `271` already has and which is exactly the statistic that hides this. **A mean of 16.67 ms is
   the same for a perfectly even run and one alternating 8 and 25.**
4. `§1.1`'s repair — book the MEASURED sleep instead of the requested one — is a two-line change and
   **must not be made before the distribution instrument exists to score it** (`P5`, rule `15`).

## §4 — RANKING
**This goes to the top of `00-STATE` §3 OPEN, above the widescreen holes.** It is worn, it is
constant, it has been there since bring-up, and **smoothness is the entire point of a VR port** —
`92`'s 90 Hz work exists for it. A hole in a wall is a blemish; judder is the thing that makes
people take the headset off.
