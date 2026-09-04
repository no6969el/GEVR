# 73 — the `-NoXr` regression check after the B1 fix. PASS. And the game itself drops to 30.

**2026-08-23, late session. `71`'s "the one thing to do before trusting any of
this", run and read.** Evidence: `ge-vr-shots\gevr-FIX70-NOXR-regression.log`.

---

## THE VERDICT — PASS, and it was observed rather than argued

`71` said the non-VR path was unchanged **by construction** (`descriptorSetIndex`
defaults to 0, no non-VR caller sets it) and then said the right thing about it:
*"that is an argument, and this project has been wrong thirteen times with
arguments."*

**A level was played. 123 seconds, quit to menu, exit.**

| Check | Result |
|---|---|
| XR genuinely off | `host: frustum=0 offset=0.000 sbs=0 (enabled=0)`. No session, no swapchain, no XR startup block |
| Level rendered | `render passes: eye0=90..93` sustained. **`eye1=0` is CORRECT here** — one eye, one descriptor set, index 0 |
| Present healthy | `entries` tracks the VI, `hasTex` tracks the renderer, all session |
| Crash / exception / assert | **none in the log** |
| Teardown | `quit requested entered` -> `present thread drained`, clean |
| `-NoXr` played, not just menu'd | 120 of 123 samples have a level rendering. **`50` G4 and `61` were both scored on a launch that only reached the menu; this one was not** |

**And the half the log cannot give, reported by the person playing it:**

> *"Looked good and quit fine."*

**`50`'s and `61`'s failure was not repeated. G4 is now genuinely met.**

---

## WHAT THE RUN SHOWED THAT NOBODY WAS LOOKING FOR

### The GAME drops to 30 while the RENDERER stays at 90

Eight consecutive seconds, mid-level, on the monitor with XR off entirely:

```
[gevr] 30.0 fps | render passes: eye0=90    <- VI clock 30, renderer 90
[gevr] PRESENT: entries=30 hasTex=90        <- 30 VI entries, 90 textures
[gevr] 30.1 fps | render passes: eye0=93
[gevr] PRESENT: entries=31 hasTex=93
```

Framerate over the session: **median 60.0, min 30.0, 14 of 123 samples under
55.** The low block is sustained and contiguous, not a spike.

**`60` established that the `fps` line is the emulated N64 VI clock, not the PC
framerate.** So this is **the game itself halving its own tick**, which is
what GoldenEye on real hardware does in a heavy scene. **The PC is not
struggling — `render passes` holds 90 straight through it.**

### Why that matters to O54 (judder), and it is a candidate, NOT a conclusion

`72` exonerated the XR submit loop and left three candidates, the first of which
was *"interpolation quality — what the in-between images actually contain."*

**This measurement says the interpolator's INPUT rate is not 60. In a firefight
it is 30**, and it must still produce 90.

```
quiet scene    60 -> 90     1 interpolated image per 2 real ones
heavy scene    30 -> 90     2 interpolated images per 1 real one
```

**The stretch triples exactly when the scene gets busy — which is exactly when
judder is reported.** That is a coherent, cheap-to-test story and it is the
first candidate in this project that predicts *when* the judder happens rather
than just that it does.

**Falsification, and it needs no code:** if the judder is this, it is
**scene-dependent** — bad in a firefight, near-absent standing still in a
corridor. **If it judders equally when nothing is happening, this is wrong** and
`72`'s per-frame `max` becomes the next move instead.

**Do not build anything on this yet.** It is one read of one log, and the
relationship between the VI clock, the interpolator and what the headset
receives has never been traced end to end.

---

## TWO DEFECTS IN THE INSTRUMENTS, found by running the path they do not cover

### D1 — `STEREO IS OFF` fires under `-NoXr`, where stereo is off ON PURPOSE

```
*** STEREO IS OFF: eye 0 is rendering, eye 1 is NOT.    ***
*** FIRST SUSPECT: msaa_option in graphics.json must be ***
```

**On a run launched with `-NoXr`.** Stereo being off is the entire point of the
launch, and the banner names `msaa_option` as first suspect — **sending the
reader at a setting that is not wrong, on a run that is not broken.**

This is **O17** ("`STEREO IS OFF` false-positives in menus") and it is worse
than recorded: it fires on a whole *mode*, not just on menus. **Gate it on VR
being enabled at all.** One condition.

`48`'s own warning applies to it: *a document's authority outlives its
accuracy* — and a banner shouts louder than a document.

### D2 — `[gevr-xr]` teardown lines print with XR disabled

```
[gevr-xr] teardown: quit requested entered, draining present thread
[gevr-xr] teardown: present thread drained
```

Cosmetic, but `64` already established that **`teardown: present thread drained`
prints and is false**. A false line under a prefix claiming a subsystem that was
never started is two wrong things stacked. Recorded, not fixed.
