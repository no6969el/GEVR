# 64 — the bisect run, and B2 renamed: the frame is CORRECT and FROZEN

**2026-08-23, ~12:30-12:55. Six launches, measured throughout. Read this
before `63`, which this document corrects in three places.**

---

## THE HEADLINE

**B2 is not a dark frame, not a stale target, and not a stereo fault. It is a
COMPLETE, CORRECT render of the level, frozen, at ~1% brightness, while the
game continues to run normally behind it.**

A gamma boost of the "black" capture shows the Dam in full — geometry,
textures, sky, railings, the ramp — with nothing missing and nothing displaced.
Nobody had ever boosted one of these captures. `63` measured mean 2.29/255 and
stopped at the number.

**Rule 3 has a corollary this session paid for: a number can be measured
correctly and still be the wrong number. "Mean 2.29/255" is true and says
"dark". `(image/255)**0.35` says "correct frame, frozen". The second is one
line of Python and it was never run.**

---

## THE BISECT (`63`'s first action) — RESULT

| # | Run | Game | Start menu | Quit from the watch |
|---|---|---|---|---|
| 1 | `.\vr.ps1 -NoXr` | **OK** | OK | OK |
| 2 | `.\vr.ps1 -Flat` | **plays fine, bright** | **CORRUPT** | **BLACK** |
| 3 | `.\vr.ps1` worn | **frozen at ~1%** | — | crash |

**Step 2 is where the eye path first breaks, but it breaks something else.**
The dark frozen frame appears only at step 3, behind `GE_VR_XR`. The `-Flat`
menu corruption and the quit-black are a separate fault — see "The second
fault" below.

---

## MEASURED — Run A, worn, plain `.\vr.ps1`

| | |
|---|---|
| Content | **The Dam, complete and correct**, under a gamma boost |
| Brightness | mean 1.60 then 2.32 /255, max pixel **72** |
| Against `63` | `63` had mean 2.29 and max **72**. **Identical. No regression since `63`** |
| t0 -> t1, 3 s apart | every pixel changed, by a **uniform x1.4 scale**: 2->3, 4->6, 6->8, 8->11 |
| t1 -> +107 s | **6 pixels differ**, all in a 3x3 block at the bottom-left corner. Otherwise byte-identical |

**The uniform value mapping is the point.** A scene changing does not remap
every luma value by the same factor. A fade does. The fade was still ramping at
t0, and had stopped by t1+107.

**`63`'s "the image drifts, so it is not frozen" is corrected: the drift WAS
the fade, and it stops.**

## MEASURED — Run B, `-PresentEye 1`, timed series

Seven captures at 0, 5, 10, 15, 30, 60, 90 s, standing still:

```
    t     mean   max      differs from previous
  000s    2.42   183
  005s    1.67   183      71.47% of pixels
  010s    2.42   183      71.48%
  015s    2.42   183       0.00%      <- byte-identical
  030s    2.42   183       0.00%         from here
  060s    2.42   183       0.00%         to the end
  090s    2.42   183       0.00%
```

**Frozen byte-for-byte for 80 seconds.** The 005s frame is 010s scaled by
~0.69 (010s->005s: 2->1, 4->3, 6->4, 8->5) — the same fade, one step back.
000s and 010s cross-correlate at **dx=0** with mean|diff| 0.21, so the two
bright states are the same image dithered, **not two eyes and not a shift.**

**So the freeze sets in within about ten seconds of level start, and is total.**

---

## THE GAME IS ALIVE. This is the finding that relocates the bug.

> *"I remembered the button press for the watch to quit, but I wasn't able to
> see it while I was doing it. Then it quit to the menu that says you failed
> the mission."*

**Navigated blind, and it worked.** Input, game logic, menu state and the
mission-failed transition all advanced normally while the presented image sat
frozen on a frame from level load.

**Nothing is hung.** The freeze is entirely downstream of the game. This also
retires `63`'s "Input: not confirmed reaching the game" — it is confirmed.

And it explains `63`'s save-select flicker: a moment when the present chain
picked up a current workload instead of the frozen one.

---

## FALSIFIED THIS SESSION — hypotheses 10 and 11

**10. `63` candidate 1: interpolated-frame counters against `50`'s
`frame * 2 + eye` eye targets. DEAD.**
`rr_option: "Original"`, worn. `render passes` dropped 90 -> 60, so the setting
was live and this is a real negative. Result: t0 and t1 five seconds apart were
**byte-identical, zero pixels differing**, mean 0.84/255. Frozen harder, not
less. Interpolation is exonerated in both directions: `-Flat` freezes nothing
at 90, XR freezes at both 90 and 60.

**11. The unguarded `eyeZeroTarget`. DEAD.**
`present_queue.cpp:407` guards on `eyeOneTarget != nullptr` and never checks
`eyeZeroTarget`; eye 0 can `continue` past its
`vrPresentEyeTexture[0].store(...)`, leaving the host's pointer at last frame's
value. Plausible, and `-PresentEye 1` forces both halves to `eyeOneTarget`, the
guarded one. **No effect** — Run B above froze exactly as Run A did.

**The missing guard is still a real defect. It is not this one.** Do not
"fix" it and call B2 closed — `49`'s "THE ROOT CAUSE" already made that mistake.

---

## ESTABLISHED FROM SOURCE, at zero launch cost — `58`'s method

### `-Flat` does not exercise the path the headset uses

`rt64_present_queue.cpp:398` gates the entire per-eye present block on
`wantWidth = vrPresentEyeWidth`. **That value is stored in exactly one place in
the tree: `ge_vr_xr.cpp:1019`, the XR host.** `-Flat` never sets `GE_VR_XR`, so
the host never runs, so `wantWidth` is 0, so under `-Flat` the block is skipped
entirely and the window path at line 509 reads `vrEyeZeroTarget` /
`vrEyeOneTarget` **directly**.

The headset does not. Under XR there is a whole second stage `-Flat` never
executes: a per-eye `viRenderer->render()` into separate `vrPresentEyeTextures`,
their own framebuffers, layout barriers, then the host's `CopyTextureRegion`
into the swapchain.

**So `-Flat` validates the eye RENDER and nothing downstream of it.** `-Flat`
playing fine exonerates `50`'s eye targets, `51`'s transform buffers, the index
coverage and the fb census — and says nothing at all about the stage that is
frozen.

**This is the correct form of `63`'s "eleven documents never worn".** It is not
that a regression hid in those eleven; it is that `-Flat` structurally cannot
reach the stage where the fault is.

### Every healthy instrument reads the wrong side

`ge_vr_report` — the source of `60.0 fps` and
`render passes: eye0=90 eye1=90 distinctTargets=90` — is called from
`RT64Context::update_screen(vi_origin)`, **the game's VI tick**
(`rt64_render_context.cpp:1705`). `vrEyePasses` is incremented in
`workload_queue.cpp:1306`, the **render** side.

**Not one of those numbers observes `PresentQueue::threadPresent`.** They are
all upstream of the freeze, which is why they all report healthy. This is
`63`'s "whatever is wrong is not visible to a single instrument this project
owns" — now located rather than lamented.

The two lines that DO observe the eye present path,
`[gevr-xr] RT64 published both eye images` and `[gevr-xr] eye copy: src format`,
are both **one-shot** (`g_loggedEyesArrived`, `g_loggedCopy`,
`ge_vr_xr.cpp:1187` and `1477`). They fire once at startup and then report
nothing for the rest of the session. **An instrument that latches true and
never speaks again cannot see a regression** — rule 4, in a new place.

### The present thread is alive

`rt64_render_context.cpp:1706`: *"xr_tick is deliberately NOT called here any
more. The XR frame loop runs on RT64's present thread via the render hook."*
`[gevr-xr] stage ms:` and `frame budget:` printed once a second to the last
second of every run. **So the present thread is running and submitting XR
frames at 90 Hz while its output is frozen.** Narrower than "the present thread
stopped", and not to be guessed at further.

---

## THE TEARDOWN CRASH — 100% REPRODUCIBLE, and `63` is corrected

Both worn runs ended identically. Same RVAs, same fault address, same
`access violation READING 0x2C`; only the thread id differs.

```
[gevr-xr] teardown: quit requested entered, draining present thread
[gevr-xr] teardown: present thread drained
[gevr-crash] code 0xC0000005, access violation READING address 0x2C
[gevr-crash] fault at nvwgf2umx.dll+0x490370
```

Resolved against `build\Release\GoldenRecomp.map`:

| frame | symbol |
|---|---|
| 11 | `D3D12DescriptorSet::setSRV +0x71` |
| 12 | `D3D12DescriptorSet::setTexture +0x19a` |
| 13 | `VIRenderer::render +0x10a` |
| 14 | `PresentQueue::threadPresent +0x10d3` |
| 15 | `PresentQueue::threadLoop +0x560` |

**`teardown: present thread drained` is FALSE.** The present thread is still
inside `viRenderer->render()` after that line prints, and it then touches a
destroyed texture.

**`63` recorded "the full shutdown sequence executed, cleanly, TWICE — promote
it to DONE — observed." On this build none of the four `shutdown:` lines print
at all, because the crash happens first.** `00-START-HERE`'s ledger row must be
reverted from EXECUTED, CLEAN, TWICE. Rule 11: it was promoted on two
observations that did not include reading the crash reporter's output.

This is `49` O21, worse than recorded, and it is in the **same function** as
the freeze.

---

## The second fault — the `-Flat` menu corruption and the quit-black

Separate from B2, and the bisect pairs them:

**Quit from the watch IS the `SDL_QUIT` path** — `input.cpp:180-207`, stop the
game, show the menu, keep the process alive (`59`). So "quit goes black" is the
limiting case of "the start menu is corrupt": the eye path mishandles
**menu-class workloads**, and when the game stops producing world workloads,
corrupt becomes black.

`59` treated these as two unrelated symptoms in one doc. They are one.
Supporting: `52` found the `fb eye` probe latches on a MENU; `39` O17's
starvation warning false-positives in menus. Three signs that menus are a
workload class the eye path does not handle.

**Not measured yet.** Run E, unrun at the end of this session, has the plan:
capture the corrupt menu under `-Flat`, a good level frame as control, the
black after quitting, then `-SkipEye 0` / `-SkipEye 1` on the same menu.
**`-SkipEye` has never been pointed at a menu**, and it is the knob that
cracked B1.

---

## THE PLAN — the instrument, then nothing else

**Do not fix anything yet.** Eleven hypotheses have been falsified, two of them
today, and every one of them was plausible. The present path has never been
observed. Observe it first.

### The counters, all printed once a second beside the existing line

In `PresentQueue::threadPresent`:

1. entries to `threadPresent`
2. of those, how many had `renderParams.texture != nullptr`
3. how many reached `viRenderer->render(eyeParams)`, per eye
4. how many stored `vrPresentEyeTexture[eye]`, per eye

In `ge_vr_xr.cpp` `refreshEyeSources()`, **replacing** the one-shot
`g_loggedEyesArrived`:

5. per second, how many frames found `g_eyeSource[0]` / `[1]` non-null

### What each would report if it were looking at the wrong thing

**Required before the build — `48`, and `52`'s census is the model.**

- Counter 1 at ~90/s with 4 at ~0/s: the present thread runs, the eye stores do
  not. The fault is inside the block.
- 1 and 4 both ~90/s, 5 at ~0/s: RT64 publishes, the host does not pick up. The
  fault is at the host boundary.
- All five ~90/s: **everything downstream of the game is running correctly and
  the fault is in what the workload CONTAINS** — the frozen workload theory,
  and the search moves to the workload queue.
- Counter 1 at ~0/s: the present thread has stopped, and the `stage ms` lines
  are coming from somewhere other than where I believe. That would falsify the
  reading of `rt64_render_context.cpp:1706` above.

**All four outcomes are distinguishable, and a working build produces the third
with a moving image — so "all five at 90/s" is not by itself a pass.** The gate
is the counters PLUS the frame still being frozen.

### Then, and only then

The answer names one of: the workload contents, the eye present block, the host
boundary. Each has a different next slice. **Do not write that slice now.**

---

## Housekeeping

- `graphics.json` restored to `rr_option: "Manual"` / `rr_manual_value: 90`,
  verified by reading it back. Backups: `graphics.json.bak-pre64` (this
  session), `graphics.json.bak-pre57`.
- Preserved logs in `GoldenEyeVR\ge-vr-shots\`:
  `gevr-PRESERVED-bisect-step3.log`, `gevr-A-worn-FINAL.log`, and a tagged log
  beside every capture.
- Captures: `gevr-A-worn-*`, `gevr-D-orig-*`, `gevr-B-pe1-*`,
  `gevr-B-series-*`.

## Corrections to make in `00-START-HERE`

1. **The ledger row "Full-session shutdown: EXECUTED, CLEAN, TWICE — `63`"
   must be reverted.** It crashes, reproducibly, and prints none of the four
   lines.
2. **"Do this first" must stop leading with the bisect** — it has been run, and
   its answer is in this document.
3. **The `59`/`60` index entry says only "the scan lines and the 60 fps VI
   clock".** `59` also contains symptom A, quit-to-menu black, which is half of
   the second fault. The entry undersells it and a session looking for that
   symptom would not find it.
4. **`-Flat`'s standing must be restated.** It is not "a substitute for
   measuring it" in general — it is structurally blind to the eye PRESENT
   stage, by the `vrPresentEyeWidth` gate. Say which stage it covers.

---

# THE INSTRUMENT RAN. Reading 3, and the search moves.

**2026-08-23 ~13:02. Built in 62 s, worn immediately.**

## What it says

```
[gevr] 60.0 fps | render passes: eye0=91 eye1=91 distinctTargets=91
[gevr] PRESENT: entries=61 hasTex=91 | eyeRender=91/91 eyeStore=91/91 | hostSees=91/91
```

Sustained, every second, through the freeze.

| Counter | Reads | Means |
|---|---|---|
| `entries` | **61/s** | `threadPresent` is entered once per VI frame, at the 60 Hz VI clock |
| `hasTex` | **91/s** | the inner present loop runs 90x/s — `threadPresent` loops over `framesToPresent`, so 60 entries produce 90 presents. **This is why the two numbers differ and it is not a fault** |
| `eyeRender` | **91/91** | both eye `viRenderer->render()` calls run every present |
| `eyeStore` | **91/91** | both `vrPresentEyeTexture[eye]` stores run every present. **The `continue` path is never taken** |
| `hostSees` | **91/91** | the host picks up a non-null image for both eyes, every frame |

**This is reading 3 of the four written down before the build: everything
downstream of the game runs correctly, at full rate, with nothing null,
starved, stale or skipped.**

It also settles hypothesis 11 a second way, from the other end: `eyeStore`
at 91/91 means eye 0 never `continue`s past its store. The unguarded
`eyeZeroTarget` is a real defect that never fires on this path.

## AND IT EXPOSED A HOLE IN THIS DOCUMENT'S OWN EVIDENCE

**Every capture in this document up to this point was taken while the player
was deliberately holding still.** Run A: "hold still". Run D: standing still.
Run B's 90-second series: "hands off the controller". **A static scene
photographed twice is byte-identical too**, and "frozen" had been asserted for
an hour on evidence that could not tell the two apart.

**Rule 4, broken by the author of this document, in this document.** The
instrument's own honesty check is what surfaced it: all five counters reading
full rate is what a WORKING build produces, so the reading only meant anything
if the freeze was real, and nobody had established that it was.

### The gap, closed

**The first attempt at this was itself ambiguous, and the user caught it.**
Three captures were taken (`gevr-MOVE-t0/t1/t2`) and came back byte-identical,
but the user's "I'm moving now" arrived as the last one fired — so it could not
be established that any of the three was taken during motion. **A test whose
timing cannot be confirmed is not evidence.** Recorded because the near-miss is
the same shape as the hole it was meant to close.

Re-run with motion confirmed first, four captures 3-4 s apart across
**eleven seconds** of walking and hard turning:

```
gevr-MOVE2-a-130543.png   mean 2.42  max 72
gevr-MOVE2-b-130547.png
gevr-MOVE2-c-130550.png
gevr-MOVE2-d-130554.png

all six pairwise comparisons: IDENTICAL, 0.00% of pixels differ
```

**Byte-identical across eleven seconds of confirmed motion.** The freeze is
real. The conclusion stands, and it now rests on evidence that could have
falsified it.

**One loose thread, kept because it is not yet explained:** `MOVE2-a` differs
from `MOVE-t0`, taken 90 seconds earlier, in 19.28% of pixels at mean|diff|
0.20 — the same tiny magnitude as the two dithered "bright" states in Run B's
series. So the image is not eternally pinned; it changes occasionally, and
**not in response to player motion.** Whatever advances it is not the game's
camera. That is a clue and it should not be filed away.

## WHERE THE FAULT IS NOW

Established, not argued:

- The game runs (input, logic, menus, the blind quit).
- The VI tick runs at 60 Hz and `update_screen` is called 60x/s.
- The workload is rendered 90x/s into two distinct eye targets.
- The present path runs 90x/s, both eyes, every stage.
- The host receives a fresh non-null image 90x/s.
- **And the pixels never change.**

**Every stage is running. The thing being run is the same thing every time.**
The fault is in WHAT THE WORKLOAD CONTAINS — the pipeline is faithfully
rendering and presenting a workload whose contents are pinned.

**The search moves upstream, to the workload queue**, between "the game
submits a frame" and "RT64 renders a workload". Everything downstream of that
boundary is now measured and healthy, which is a much smaller search than this
session started with.

## NEXT SLICE — plan only, do not build yet

The same treatment, one boundary upstream. In `rt64_workload_queue.cpp`, per
second:

1. workloads submitted by the game
2. workloads actually rendered
3. the rendered workload's draw-call count and its framebuffer address
4. a cheap hash or serial of the workload identity, so "the same one 90 times"
   is distinguishable from "90 different ones that happen to look alike"

**What each would say if it were looking at the wrong thing:**

- submitted ~60/s, rendered ~90/s, **identity constant** -> the queue is
  re-rendering one pinned workload and discarding new ones. Names the bug.
- submitted ~0/s -> the game is not submitting despite the VI tick running,
  and the fault is upstream of RT64 entirely, in the recomp's graphics task.
- submitted ~60/s and **identity changing** -> the workloads are fresh and
  identical in content, which would mean the game is not DRAWING, only
  flipping. Different bug again, and the search moves to the display list.

**All three are distinguishable and none is what a working build produces**,
since a working build has a changing identity AND changing pixels.

## Also still unexplained, and NOT to be folded in

**The brightness.** mean 2.42/255, max 72, on a correct frame. Whether that is
the same fault as the freeze or `63` candidate 4's separate second bug is
**unknown and must not be assumed**. A frame frozen during a fade-in would
explain it; so would a transfer-function fault. Do not attribute it until the
freeze is named.

---

# THE DEATH BURST — B1 AND B2 ARE ONE BUG

**2026-08-23 ~13:12. 22 captures, 1.5 s apart, through play, death, replay and
the mission-failed menu. One launch. This is the measurement the whole session
was for.**

## The images

```
shot   mean   max    vs previous
01     1.60    72
02     2.32    72    71.69% changed
03     1.60    72    71.69% changed
04     1.60    72    IDENTICAL
05-07  1.60    72    IDENTICAL
08     2.32    72    71.69% changed
09-11  2.32    72    IDENTICAL
12     1.60    72    71.69% changed
13     2.32    72    71.69% changed
14-17  2.32    72    IDENTICAL
------------------------------------ THE PLAYER DIES HERE
18    63.01   237    99.79% changed
19    25.70   119    99.73% changed
20    29.76   126    99.25% changed
21    59.16   237    99.51% changed
22   113.07   194    99.56% changed
```

**Shots 01-17: two states, 1.60 and 2.32, max 72, byte-identical in between.
Shots 18-22: mean up to 113, max 237, and 99%+ of pixels changing every
1.5 seconds.** Bright, live, and moving.

## The counters, at the same moments

```
shots 01-17   render passes: eye0=90 eye1=90 distinctTargets=90    <- eye split ON
shot  18      render passes: eye0=88 eye1=5  distinctTargets=5     <- the transition
shots 19-22   render passes: eye0=92 eye1=0  distinctTargets=0     <- eye split OFF
```

## THE CORRELATION IS EXACT

| Eye split | Image |
|---|---|
| `eye1=90 distinctTargets=90` — **running** | **frozen, mean 1.60-2.32, max 72** |
| `eye1=0 distinctTargets=0` — **not running** | **live, mean up to 113, max 237** |

**When the second eye pass runs, the image freezes and goes dark. When it stops,
the image is immediately correct, bright and animated — same build, same
session, same launch, seconds apart.**

**B1 and B2 are not two blockers. They are one bug, and it is the eye split
itself.** Everything downstream of it — the present path, the host copy, the
compositor, the brightness pipeline — is proven correct by shots 18-22, which
travel the same wires.

## What this retires

- **`63` candidate 4, "brightness is a separate second bug": DEAD.** The same
  pipeline produces max 237 four seconds later.
- **The whole "which instrument is lying" search: over.** Nothing was lying.
  `render passes: eye0=90 eye1=90 distinctTargets=90` was reporting the truth —
  the eye split IS running, and that is precisely the problem.
- **"The fault is in what the workload contains", written one section above
  this: WRONG, and superseded within the hour.** The workload is fine when the
  eye split is off. Left in place as the record.

## The two states, and why they matter

During the freeze the window alternates between exactly two frames, 1.60 and
2.32, related by a **uniform x1.4 brightness scale** (measured three times
today: Run A t0/t1, Run B 005s/010s, and shots 01-13 here). Not two viewpoints
— `MOVE2` cross-correlated at dx=0.

**Two eye targets, holding the same image at two different brightnesses, being
presented alternately.** `50`'s `frame * 2 + eye` indexing produces exactly that
alternation. And a x1.4 difference between two targets that should be identical
in brightness is not a stereo question at all.

## NEXT — one launch, no code, and it is already built

**`.\vr.ps1 -SkipEye 0` and `.\vr.ps1 -SkipEye 1`, WORN.**

`56` proved each pass alone is correct under `-Flat` and called `-SkipEye` the
most valuable diagnostic in the project. **It has never been run worn**, and the
correlation above makes it the direct test:

| Result | Means |
|---|---|
| Image comes **alive and bright** with one pass skipped | the second pass is what breaks it, and the search is inside the eye loop. Matches shots 19-22 exactly |
| Still **frozen and dark** with one pass alone | the eye split breaks it even single-pass, and `56`'s `-Flat` result does not carry to XR — which would also be a finding, since `-Flat` cannot reach this stage (see the `vrPresentEyeWidth` gate above) |

**A working build shows a live bright image under both, so neither outcome is
one a working build also produces.**

Run `-SkipEye 1` first: it leaves eye 0, the eye confirmed to be the left one by
`27`'s tint test.

---

# THE INTRO BURST — THE MOMENT IT STOPS, CAUGHT

**2026-08-23 ~13:21. 30 captures, 0.6 s apart, from level select through the
Dam's intro fly-through into gameplay. `-ResScale 0.25`.**

Nobody had ever captured the START of a level. Every capture before this one was
taken well after the freeze had already happened.

```
shot   mean    max     vs previous
01    42.42    242       --
02    41.57    210      6.98% changed
03    26.39    134     99.81%
04    20.78    103     98.95%
05    48.55    247     99.15%
06    47.10    200     89.01%
07    50.73    204     88.72%
08    55.94    206     92.45%
09    44.28    194     97.03%
10    43.48    204     98.37%
11    45.54    221     98.75%
12    40.51    211     98.98%
13    42.32    168     92.13%
--------------------------------- THE EYE SPLIT ENGAGES HERE
14    42.32    168     IDENTICAL
15    42.34    164     (cycles)
16    42.34    164     IDENTICAL
17    42.34    164     IDENTICAL
18    42.36    165     (cycles)
...
30    42.36    165     (cycles among 42.32 / 42.34 / 42.36 forever)
```

And the counters across the same boundary:

```
shots 01-13   render passes: eye0=90 eye1=0  distinctTargets=0    <- intro, split OFF
shot  14/15   render passes: eye0=91 eye1=90 distinctTargets=90   <- IT ENGAGES
shots 15-30   render passes: eye0=92 eye1=92 distinctTargets=92   <- split ON
```

**The intro plays perfectly — bright, 89-99% of pixels changing every 0.6 s —
right up to the frame where the eye split turns on. Then it stops, instantly and
permanently, and cycles among three fixed frames for the rest of the session.**

## CONFIRMED IN BOTH DIRECTIONS

| Transition | Split | Image |
|---|---|---|
| Intro burst, shots 13 -> 14 | OFF -> **ON** | animating -> **frozen** |
| Death burst, shots 17 -> 18 | ON -> **OFF** | frozen -> **animating** |

**Two independent transitions, in opposite directions, in separate launches,
each caught at the frame it happens.** The eye split turning on is the moment
the image stops; the eye split turning off is the moment it resumes.

## AND THE BRIGHTNESS WAS NEVER A BUG

**This run froze at mean 42.3. Every earlier run froze at mean 1.6-2.4.**

The difference is **which frame it froze on**. At full resolution the freeze
happens almost immediately, during the level's fade-in from black, so it locks
onto a nearly-black frame. At `-ResScale 0.25` the intro ran about eight seconds
first, so it locked onto a fully bright one.

**So "the image is ~1% brightness" was never a rendering fault, a transfer
function, an sRGB mismatch or a second bug.** It is a fade-in, frozen early.
`63` candidate 4 is dead, `63`'s entire "dark" framing is dead, and the x1.4
alternation measured three times today is simply two eye targets holding two
adjacent steps of that fade.

**Every hypothesis this project has entertained about darkness was aimed at
something that does not exist.**

## What `-ResScale` actually did

It was launched to test whether eye target SIZE causes the freeze. It does not
prevent it — but it **delays** it, from near-instant to about eight seconds.
**The freeze is timing- or load-dependent**, which is new, and which is the
first evidence pointing at a race rather than a logic error.

`49` O22's unexplained "8x fewer pixels ran 4x slower" is very likely the same
mechanism seen from the other side and should be re-read in this light.

## The state of the diagnosis

**One bug, not two. B1 and B2 are the same fault, and it is the eye split.**

Established by measurement, both directions, this session:

- Split off: image correct, bright, animating. Intro, death replay, menus.
- Split on: image locks within seconds and never advances.
- Everything downstream is proven good, because the working frames travel the
  same present path, host copy, swapchain and compositor.
- The game never stops: input, logic, menus and the blind quit all work
  throughout.
- Lowering eye target resolution delays the freeze but does not prevent it.

**The remaining question is what, inside the eye split, stops new workload
content reaching the eye targets — and the resolution-dependent delay says to
look for a race first.**

## Do NOT do next

- **Do not fix the unguarded `eyeZeroTarget`.** Real defect, measured not to
  fire (`eyeStore=92/92`), and fixing it now changes behaviour mid-diagnosis.
- **Do not chase brightness.** It is explained.
- **Do not trust `-SkipEye` to disable the eye split.** Measured this session:
  under XR it disables only the PRESENT-side eye render. `render passes` shows
  `eye0=92 eye1=92 distinctTargets=92` still running under `-SkipEye 1`. The
  knob does not mean what `56` says it means on this path, and a gate written
  around it returns a false answer. **`00-START-HERE` calls `-SkipEye` "the most
  valuable diagnostic in the project"; that is true under `-Flat` and wrong
  under XR.**
