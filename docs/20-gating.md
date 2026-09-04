# "In a level" is not the same as "playing" — 2026-08-22

> **This did not fix the reported symptoms.** They were caused by the host-side
> frustum override, left on by a stale environment variable — see
> `21-host-gate.md`. The change below is kept because it is correct on its own
> terms: `geVrInLevel()` really is too loose for in-level menus, cutscenes and
> demo playback, and gating in beats gating out. It just was not the cause.

## The two reports

After the znear fix landed and the blue band went away:

- the menus are off-centre and covered by a black border again;
- James Bond is off-centre walking in the intro, and appears to clip.

Both are the same bug, and the black border is a returning one: Phase 0 hit it at
cot scale 0.3, where "the file-select options were covered by an overlay stretched
past its scissor box". `03-phase0-result.md` recorded it and `geVrInLevel()` was
written to prevent it.

`geVrInLevel()` was not enough.

## Why

```c
static s32 geVrInLevel(void) {
    return g_StageNum != LEVELID_NONE && g_StageNum != LEVELID_TITLE;
}
```

That answers "is a level loaded". It does not answer "is the player playing",
and a great deal of GoldenEye happens with a level loaded and the player not in
control:

- the intro walk and other cinematic cameras;
- death cams, single and multiplayer;
- the swirl and fade transitions;
- the briefing, mission-complete and mission-failed menus, which sit on a loaded
  stage rather than at `LEVELID_TITLE`;
- demo playback on the title screen.

Every one of those was getting a 106 degree vertical FOV. Cinematic cameras
frame their subject for a 60 degree view, so Bond walks off-centre and into the
frustum's edge; menu overlays are sized for a 60 degree view, so they stretch
past their scissor and the unscissored remainder is black.

The patch's own comment predicted part of this and then under-scoped it: it noted
the gate "does NOT cover the in-level pause menu / watch", treated that as an
acceptable Phase 3 deferral, and did not notice that briefings, cutscenes and
demos fall through the same hole. The comment described the limitation accurately
and drew too small a conclusion from it.

## The fix — gate IN, not OUT

```c
static s32 geVrWorldCamera(void) {
    return geVrInLevel()
        && demoMode == 0
        && (g_CameraMode == CAMERAMODE_FP || g_CameraMode == CAMERAMODE_MP);
}
```

**The direction matters more than the contents.** An exclusion list is open-ended
— every camera mode added or discovered later is a new bug, found by a player.
An inclusion list is closed: `CAMERAMODE_FP` and `CAMERAMODE_MP` are the two
modes that mean "the player is looking through their own eyes and driving". Every
other mode in the enum — `NONE`, `INTRO`, `FADESWIRL`, `SWIRL`, `DEATH_CAM_SP`,
`DEATH_CAM_MP`, `POSEND`, `FP_NOINPUT`, `FADE_TO_TITLE` — renders stock, and a
mode nobody has thought of yet also renders stock.

`g_CameraMode` (`bondview.c:283`, assigned at `bondview2.c:770`) is the
authoritative current mode. `demoMode` is upstream's own flag, already
special-cased in `widescreen.c:141` for the title-screen attract loop at exactly
this kind of boundary.

Both the FOV widening and the znear clamp now use it.

### `FP_NOINPUT` is excluded on purpose

It covers first-person moments where the player has no control, which is where
in-level menus sit. The cost is an FOV change when one opens. That is worth
paying: the alternative is the overlay bug, and Phase 3 replaces those screens
with world-space panels anyway, so polish spent there is thrown away.

If a normal-play moment turns out to use `FP_NOINPUT`, the symptom will be a
brief FOV narrowing during it — visible, harmless, and easy to attribute.

## Lesson

The gate's name told the truth and its use did not. `geVrInLevel()` was called
at three sites that all wanted a different question — "is this the player's own
view of the world, right now" — and the name never made that mismatch visible.
`geVrWorldCamera()` is named for the question actually being asked.

The general form: a predicate that is *nearly* the one you want will pass every
test you think to run, because the cases where it differs are the ones you were
not thinking about.
