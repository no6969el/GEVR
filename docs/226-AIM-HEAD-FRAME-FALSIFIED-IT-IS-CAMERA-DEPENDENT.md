# 226 — THE HEAD-FRAME AIM FIX IS FALSIFIED. THE FAULT IS CAMERA-DEPENDENT.

**2026-08-27. Tiers per `182`. `[MEASURED]` offline from a fresh capture — NO wear test
wasted, NO build. This closes `223` §3's standing hypothesis.**

---

## §1 — THE CAPTURE
**Quest 3 (not Pimax). 28 MTXREC shots, gun held on a fixed target, HEAD yaw varied
19-116 deg, game camera held ~fixed.** `[MEASURED]` cam-forward spread across shots small,
confirming head-only variation.

## §2 — CONVENTION VALIDATED (so the result is not an artifact)
**`[MEASURED]` play-space `ray` vs gun-forward from `POSEREC gq`: mean 0.1 deg, max 0.2 deg.**
The aim ray IS the gun ray, and the quaternion convention (shared by `hq`->H) is correct.
Therefore the head-matrix H below is trustworthy.

## §3 — THE RESULT: `223` §3 IS FALSIFIED
**`[MEASURED]` consistency (mean pairwise angle of the world bullet dir across the head-turn
sweep; lower = head-invariant = correct):**

| candidate | spread |
|---|---|
| **current `v2w^T . ray` (NO head term)** | **6.6 deg** |
| `v2w^T . (H . ray)` | 72.4 deg |
| `v2w^T . (H^T . ray)` | 74.2 deg |

> **Adding the head rotation (either handedness) makes the aim 10x WORSE. The current
> no-head-term computation is already head-invariant to 6.6 deg. `223` §3's "the missing
> term is play->world = H" is WRONG.** `223` §4 said "if the head term wins, build it" — it
> lost, offline, at zero build/wear cost. This is `48`'s instrument-over-candidate paying off.

## §4 — THE REDIRECT (and it matches `194`)
**Head is EXONERATED — consistent with `194` (the head never reaches the game camera, so it
must not drive aim; the data confirms it does not).** `223` §2.3's big errors (+151, +179)
came from a PHYSICAL/STICK turn — the GAME CAMERA changing (`cam`/`thr`), which this capture
held fixed. **`[INFERRED]` the fault is in the camera->world mapping `v2w = thr . cam^-1`,
which moves with the VIEW, not the head. Counter-example search owed; confirm by capture.**

### THE ~6.6 deg RESIDUAL
`[MEASURED]` mildly head-correlated (worst, 8-11 deg, only at extreme 113-116 deg head yaw),
otherwise ~gun-wander. A secondary effect at best; NOT the primary fault.

## §5 — WHAT IS OWED (the decisive next capture)
**Mirror of this one: gun on a FIXED real target, vary the VIEW/BODY (stick-turn to different
compass facings) between shots, head roughly forward.** That varies `cam`/`thr`. Then measure
how `v2w^T . ray` swings with the game-camera orientation — `223` §2.3's 151/179 deg should
reappear and localise to a `cam`/`thr` term. That is where the real, camera-dependent fix is.
**No rebuild to capture; offline to analyse. The head path is closed — DELETE NOTHING, but do
not build `-HeadFrame`.**

---

## §6 — CAMERA-TURN CAPTURE + SCREEN DATA. THE AIM MATH WORKS; THE CLAMP IS THE WALL.

**`[MEASURED]` Quest 3, 42 MTXREC shots + 211 BULLET screen records: gun held ~fixed
(ray spread 11.5 deg), stick-turned the view.**

### THE DIRECTION MATH IS CORRECT
- **`[MEASURED]` aim (`v2w^T.ray`) swings ~1:1 with the stick-turn** (0->174 deg across the
  sweep). The bullet tracks in-game facing correctly. STICK-TURN IS NOT THE BUG.
- **`[MEASURED]` bullet vs SIGHT screen gap = 0px over 211 shots.** `193` holds: the bullet
  goes where the crosshair is drawn. The projection is innocent.
- Combined with §3 (head-invariant) and §2 (ray=gun 0.1 deg): the aim follows the GUN and the
  STICK correctly. The transforms are right.

### THE WALL — SCREEN-SPACE FIRING + THE FRUSTUM CLAMP
- **`[MEASURED]` sight CLAMPED on 211/211 shots (100%).** GoldenEye fires through a
  screen-space `crosshair_angle` bounded to the screen rectangle (`90`: no unclamped shot
  path exists). When the hand-aimed gun points outside the view frustum, the aim pins to the
  edge. (100% here is partly the fixed-gun/turned-view design, but it demonstrates the
  mechanism.)
- **`[MEASURED]` bullet vs GUNPOINT (`field_FFC`, drawn gun) gap = 39px mean; drawn gun stuck
  at center on 128/211.** The gun you SEE and the bullet you FIRE disagree.

### THE CONCLUSION — IT IS STRUCTURAL, NOT A KNOB
> **The aim `[INFERRED]` fault is `194` again: the game camera never follows the head/body,
> so room-scale hand-aim constantly lands outside the engine's screen-space frustum, and the
> engine cannot fire there — it clamps. The direction transforms are correct; the engine's
> screen-space bullet path conflicts with room-scale aiming.** Counter-example search owed,
> but every measured signal (aim tracks gun+stick, bullet=sight, 100% clamp) is consistent.

### THE REAL FIX ROUTES (both source-side — the `224` §3 / TLB-free gate)
1. **`194`'s fix: head rotation into the game camera (`bondview.c`)** so the view follows the
   aim and it stays inside the frustum.
2. **A world-space aim/bullet path** bypassing the screen-space crosshair (`90`'s world dot).

**`223`'s `-HeadFrame` is DEAD (§3). The aim work is now part of the source-build program,
not a standalone tuning fix. DELETE NOTHING; do not build the head term.**
