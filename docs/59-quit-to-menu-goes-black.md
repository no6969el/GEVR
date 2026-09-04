# 59 — quit-to-menu goes black, and the scan lines

**2026-08-23. Reported from play, and NOT yet measured. Plan only.**

Two symptoms, reported together, **with no evidence yet that they are related.**
Kept in one doc because they were seen in one session; **split it the moment
either is measured.**

---

## Symptom A — quit goes to a black screen instead of the menu

**Expected:** pause → quit returns to the game's own menu. **Observed:** black.

### What the log says

`gevr.log` ends at:

```
[gevr-xr] teardown: quit requested entered, draining present thread
[gevr-xr] teardown: present thread drained
```

and then **nothing**. No `shutdown:` line follows, because under `-Flat` there
are none to follow — **O29: every `shutdown:` line and the whole
unhandled-exception filter are gated behind `GE_VR_XR`, and `-Flat` never sets
it.** This is precisely the case O29 predicted would be undiagnosable, arriving
one day after it was written down.

### What is established by reading the source

**Quit-to-menu IS the `SDL_QUIT` path.** `src/game/input.cpp:180-207`: on
`SDL_QUIT`, with a game running, the handler sets the recompui menu to `Config`
and calls `ultramodern::quit()` — **stop the game, show the menu, keep the
process alive.**

And the first thing that same handler does, unconditionally, is
`ge_vr::begin_shutdown()`.

**`docs\42`'s premise is FALSE in this codebase.** Its comment reads:

> *"This is the first moment the process knows it is exiting, and it is the last
> moment that is reliably ours."*

`SDL_QUIT` here does not mean the process is exiting. It means **the GAME is
exiting, to a menu.** `begin_shutdown()` latches
`g_ge_vr_shutting_down` through a one-shot `already` flag that **is never
reset**, so from the first quit onward the XR present tick is disabled for the
remaining life of the process. **Rule 7's shape — know who destroys what you
build, and when — and rule 10: a doc asserting something false about when it
runs.**

### But that is NOT sufficient to explain `-Flat`

`-Flat` never sets `GE_VR_XR`, so `xr_present_tick` was doing nothing there in
the first place. **Disabling it cannot blank a `-Flat` window.** Stated plainly
because the latch is the tempting answer and it does not fit.

**The candidate that does fit:** RT64's side-by-side present path continues to
split the window and sample the two eye targets after the game has stopped
producing workloads. What it then shows is whatever those targets hold — or
nothing.

**Untested. It is a candidate, and this project has falsified nine.**

---

## Symptom B — intermittent "scan lines", two at a time

New today by report; not seen the previous night.

### Measured, and this is the useful part

**All four of today's captures were checked for rows substantially darker than
their neighbours. There are none.**

```
58-baseline-100234        0 dark rows
58-offset0-retry-101736   0 (row 0 only, the top edge)
58-skip1-eye0alone        0
58-skip0-eye1alone        0
```

So either the artefact is intermittent and four captures missed it, or **it is
not in the rendered frame at all** — a present/display-side artefact such as
tearing, which a desktop composite grab need not capture.

**Do not attribute it to today's build without a test.** The honest position:
today's edits are additive logging plus two fields on `RenderTarget`, all gated
behind `vrEye.enabled` / `geVrProbe`, and none of them touch a render state —
but that is an argument, and this project has been wrong nine times with
arguments.

---

## THE PLAN — one launch, and it partitions everything

### Step 1: `-NoXr`, quit to menu

```powershell
.\vr.ps1 -NoXr
```

Start the game, play briefly, quit from the pause menu, and watch for the scan
lines while playing.

**`-NoXr` is the path that must never break, and it is also a total
falsification of my own edits**: every instrument added today is behind
`vrEye.enabled` or `geVrProbe`, both false with VR off. So:

| Result | Means |
|---|---|
| **Black screen AND/OR scan lines under `-NoXr`** | Nothing VR-side is involved, and **nothing added today is involved**. It is the recomp itself, and it is a pre-existing upstream behaviour |
| **Both clean under `-NoXr`** | Something on the VR path. Then, and only then, Step 2 |

### Step 2, only if Step 1 is clean: `-Flat`, quit, capture the black

```powershell
.\vr.ps1 -Flat
.\tools_gevr_capture.ps1 -Tag black-screen     # WHILE it is black
```

The capture now refuses to grab the wrong window, so a PNG here is trustworthy.
**A black capture proves the window is genuinely black rather than merely not
updating**, and the tagged log says what the program was doing.

### Step 3, for the scan lines: burst capture

They are intermittent, so a single shot is the wrong instrument. Capture
repeatedly during play and check every frame for dark rows — the row test above
is already written and takes one line.

---

## What must NOT be done

**Do not fix `begin_shutdown` yet.** It is a real defect with a false premise
recorded in `42`, and it is worth fixing — but it **cannot** be the `-Flat`
mechanism, and changing it now would change behaviour while two symptoms are
unmeasured. One behaviour change at a time (`48` rule 5), and not before Step 1
says which side of the fence the problem is on.

## Reassurance, stated because it was asked

- **`-NoXr` is intact by design and is the regression gate.** If Step 1 comes
  back clean, the normal game is unaffected.
- **Everything is committed as of 2026-08-23 10:30**, both repos, so any change
  from here is revertible to a build whose behaviour is known.

---

# SYMPTOM B — MEASURED, AND IT IS NOT OURS

## Step 1 result: `-NoXr` REPRODUCES the scan lines

**That is a total falsification of everything added this session**, and of the
whole VR path. Every instrument built today is behind `vrEye.enabled` or
`geVrProbe`, both false with VR off. The lines appear anyway.

## The observation that actually solved it

> **"I only see them when the screen is focused. If I put a window above it,
> they're gone."**

That is the signature of **DXGI independent flip**. A focused, unobstructed
window may bypass the desktop compositor and present directly to the display;
put any window over it and Windows falls back to composited flip, where DWM
hands the display a whole finished frame. **An artefact that disappears under
composition is a PRESENTATION artefact, not a rendered one.**

**And it explains the captures.** `CopyFromScreen` grabs the **composited**
desktop — the very path in which the artefact does not exist. Six captures
across two builds found nothing:

```
58-baseline / 58-offset0-retry / 58-skip1 / 58-skip0    0 anomalous rows
scan01 / scan02  (taken WHILE the lines were being seen) 0 anomalous rows
                                                          (row 899 = bottom edge)
```

**Those zeroes were never evidence of absence.** The instrument structurally
cannot see this class of artefact, and it would have reported "clean" forever.
**A capture tool that cannot see the thing you are looking for is an instrument
looking at the wrong thing** — `48`'s rule, in a new place, and it took the
user's own observation rather than any measurement to notice.

## The environment, recorded

```
Display: 2560x1440 @ 180 Hz, RTX 5090
Game:    60.0 fps sustained, rr_option Manual / rr_manual_value 90
Also present: "Virtual Desktop Monitor" and "Meta Virtual Monitor" (VR streaming
              virtual displays), plus Microsoft Basic Display Adapter listed at
              the same 2560x1440@180
```

## And a knob with no caller, found on the way — rule 6, seventh time

`D3D12SwapChain::setVsyncEnabled()` exists, and `present()` uses
`syncInterval = vsyncEnabled ? 1 : 0`.

**Nothing in RT64, the host or ultramodern ever calls `setVsyncEnabled`.** The
member's initialiser, `bool vsyncEnabled = true`, is therefore the only thing
that decides it — vsync is permanently ON and there is no toggle wired to
anything. Worth knowing before anyone "turns vsync off to test": there is no
switch, and the doc that eventually says there is will be wrong.

**This also weakens the simple tearing story**: at `syncInterval = 1` a plain
tear should not occur. So the mechanism is presentation-side but **not
identified**, and the candidates are driver-level — VRR/G-Sync behaviour at
60 fps on a 180 Hz panel, or one of the two VR virtual display drivers.

## VERDICT: not this project's, and not on the critical path

- **Not in the rendered image** — six captures, and the render is composited
  correctly whenever DWM handles it.
- **Not VR** — reproduces with `-NoXr`.
- **Not this session's build** — every added instrument is inert with VR off.
- **Cosmetic**: no corruption, no crash, 60.0 fps sustained throughout.

**O43, LOW priority, display/driver-side.** Do not spend a session on it while
B1 is open. If it is ever chased, chase it with a tool that can SEE it — a
capture through the render path itself, not a desktop grab. And re-test after
the memory/EXPO instability in `57` is settled, since this rig's firmware
faults are still unresolved.

---

# STEP 1, THE OTHER HALF: SYMPTOM A DOES *NOT* REPRODUCE UNDER `-NoXr`

> **"And the menus work again."**

So the two symptoms separate cleanly, and Step 1 partitioned them in a single
launch:

| Symptom | `-NoXr` | Verdict |
|---|---|---|
| Scan lines | **REPRODUCE** | Not VR, not this build, not in the rendered image. **O43, display-side, low** |
| Quit goes black instead of to the menu | **DOES NOT reproduce** | **It IS on the VR path. Ours.** |

**`-NoXr` is confirmed intact** — the path that must never break, quitting to
the menu correctly, at 60 fps. That is the regression gate passing, and it is
worth saying plainly since the question that started this was whether the game
was falling apart.

## What is now known about A, and what is still guessed

**Read from source, and it eliminates the tempting answer:**

- `WorkloadQueue::reset()` **does** clear both published eye pointers
  (`workload_queue.cpp:47-48`, added by `50`). So "present keeps sampling stale
  eye targets after the game stops" is **not** as simple as a pointer nobody
  cleared, and with both null the present eye path is skipped entirely and the
  ordinary window path runs.
- `config.sideBySide` and `config.enabled` are derived from the environment
  (`rt64_render_context.cpp:1023-1031`) and **do not depend on a game running**,
  so they stay set after the quit.
- `begin_shutdown()` latches irreversibly on `SDL_QUIT`, but under `-Flat` it
  gates only `xr_present_tick`, which does nothing there. **Still not sufficient
  as the mechanism.**

**So the mechanism is NOT identified.** Three candidates have now been read out
of the source rather than into it, which is the useful half.

## Step 2, unchanged and now justified: capture the black

```powershell
.\vr.ps1 -Flat        # play briefly, quit from the pause menu
.\tools_gevr_capture.ps1 -Tag black-screen     # WHILE it is black
```

**The capture is trustworthy for this**, unlike for the scan lines: a black
window IS black in the composited desktop, so the instrument can see this class
of artefact even though it could not see the other.

| Result | Means |
|---|---|
| PNG is **black** | The window is genuinely being presented black — something is drawing nothing, or drawing a cleared target |
| PNG shows **the menu** | The window is fine and the display is not updating — a present/flip problem, closer to the scan lines than to us |
| PNG shows **the last game frame** | Present is frozen on a stale image, not blanked |

Those are three different bugs and the picture separates them for one launch.
The tagged log says what the program believed it was doing at the same moment.
