# The off-centre everything — it was the host, and a stale shell

**2026-08-22. Resolved.**

## Symptoms

After 3c's znear fix removed the blue band, four reports in quick succession:

- menus off-centre and covered by a black border, a Phase 0 bug returning;
- James Bond off-centre and clipping while walking in the intro;
- the Nintendo logo not centred;
- the menu crosshair selecting somewhere other than where it points.

## Cause

**The host-side per-eye frustum override was on**, left enabled by a
`GE_VR_FRUSTUM=1` still live in a reused PowerShell window from the 3c gate runs.
Environment variables persist for the life of a shell.

`15-step3b.md` recorded the hole in advance and it was not connected to the
symptoms for four rounds:

> `config.inLevel` is hardcoded true. The patch knows whether a level is loaded
> via `geVrInLevel()`; the host does not yet. Perspective-only gating in
> `processScene` keeps menus and the watch out of it, since those are
> orthographic, but **a perspective front-end scene would still get the offset**.

The Nintendo logo, the intro walk and the front-end menu backgrounds are all
perspective scenes. The host pushed the centre of projection off to one side in
every one of them. The crosshair followed: the cursor is *drawn* through the
displaced projection while its hit test uses unmodified screen coordinates, so
the visible crosshair and the thing it selects drift apart.

Clearing the variable fixed all four at once.

## The diagnosis that failed, and why

`20-gating.md` attributed this to the patch's gate being too loose, replaced
`geVrInLevel()` with `geVrWorldCamera()`, and changed nothing observable. The
patch was never the cause.

**The tell was the Nintendo logo, and it arrived third.** It renders before any
level is loaded, so `geVrInLevel()` is false and the patch is provably not
touching it. One symptom that the patch cannot explain outweighs three that it
can, and the first two reports were compatible with both explanations, which is
why two rounds went by without the question being separated.

`20`'s change is kept. Gating in on `CAMERAMODE_FP` / `CAMERAMODE_MP` rather than
out on a list of exceptions is correct on its own terms, and the in-level menu
and cutscene cases it covers are real. It is simply not what fixed this.

## Two process changes, both already in

1. **The host announces itself.** One line at startup, in the same console as the
   patch trace:

   ```
   [gevr] host: frustum=0 offset=0.000 eye=0 fitAspect=1 (enabled=0)
   ```

   Environment-variable state is now observable rather than remembered. This
   would have ended the investigation at the first report.

2. **The patch trace is off by default** (`GE_VR_TRACE_FOV`), available with
   `-DGE_VR_TRACE_FOV=1`. It was written for this and never needed to run,
   because the host line answered it first.

## The unexpected confirmation of 3c

With the host override off and the patch's 106 degree cull FOV active, the
report was that it "aims perfect".

**That is a stronger result than it sounds.** GoldenEye's aim and hit-testing go
through `c_scalex` / `c_scaley`, the same values that build the culling frustum
— all derived from `c_perspfovy`. Widening the field of view by rewriting the
projection matrix, which is what `GE_VR_MODE_STEREO` did, would have left those
at 60 degrees and put the crosshair out of agreement with the world by a wide
margin.

Routing the change through `viSetFovY` keeps rendering, culling, aim and
hit-testing consistent because the engine re-derives all of them from one value.
Aim being correct at 106 degrees is evidence that 3c attached to the right lever,
independent of the blue band it was originally aimed at and failed to fix.

## What is still open

**The host has no gate.** `config.inLevel = true` is still hardcoded. Clearing an
environment variable is a workaround, not a fix — the moment the frustum override
is genuinely needed, which is step 3d, the front end breaks again.

The fix is the seam `05` designated long ago: a host import the patch calls each
frame with the answer to `geVrWorldCamera()`. Declared in `patches.h`, given an
address in `patches/syms.ld` (**next free slot `0x8F000114`**), implemented in
`src/game/recomp_api.cpp` following the pointer-out-arg pattern of
`recomp_get_gyro_deltas`.

That is not a detour. Phase 2 needs traffic in the other direction anyway — the
host must hand per-eye parameters to the patch — and this establishes the channel
with a single boolean before anything depends on it.

## Lesson

A symptom the suspect cannot possibly cause is worth more than three it can. The
Nintendo logo was decisive the moment it was mentioned, and it was mentioned
third, after two rounds of reasoning had already committed to the patch.

Ask early: **is there anything in this list the current theory cannot explain?**
