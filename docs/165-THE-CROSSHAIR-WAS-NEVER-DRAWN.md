# 165 — THE CROSSHAIR WAS NEVER DRAWN. FOR THE ENTIRE PROJECT.

**2026-08-25. BUILT. Written up retroactively at session close; the code has
referenced this number since it was built.**

> ## THE WEARER: ***"Oh there is no crosshair."***
>
> ## AND THE INSTRUMENT ANSWERED IT IN ONE RUN, WITH NO INVESTIGATION:
>
> ```
> [gevr] 6dof-game: SIGHT gunsightmode=2 mpmenuon=0
>                   -> crosshair SUPPRESSED BY THE GAME (not an aim fault)
> ```

---

## 1. WHAT `2` IS

`gunDrawSight` (`gunfire.c:6210`) draws **only** when `gunsightmode == 0` **and**
`mpmenuon == FALSE`. And `2` is **`GUNSIGHTREASON_NOTAIMING`**
(`patches/structs.h:169`), set every tick at `bondview2.c:5471`:

```c
gunSetSightVisible(GUNSIGHTREASON_NOTAIMING, moveData.aiming);
```

**`moveData.aiming` is the AIM BUTTON.**

> ## **IN VR NOBODY EVER PRESSES R, SO THE BIT NEVER CLEARED AND THE CROSSHAIR HAS
> ## BEEN HIDDEN SINCE THE PROJECT BEGAN.**
>
> **It was never drawn off-screen. It was never a stereo fault. The game was told
> we are not aiming, and it believed us.**

**AND THE OWNER ALREADY SETTLED THE DESIGN QUESTION**, in `101`: *"you're in the
shooting position now."* In VR the gun is in your hand and pointed. **`NOTAIMING`
is meaningless here.**

## 2. WHY `gunSetSightVisible` AND NOT `gunDrawSight`

`gunDrawSight` needs `crosshairimage` and `display_image_at_position`, and
**neither is in `patches/externs.h`** — `115`'s cross-boundary hazard, which
already made `157` withdraw a slice. **`gunSetSightVisible` is four lines and both
its symbols are reachable.**

**ONLY THE `NOTAIMING` BIT IS IGNORED.** `NOCONTROL` (cutscenes, AI-driven
sequences) and `DAMAGE` still suppress the sight, **because those are states where
a crosshair would be wrong in VR too.** `48` rule 5: one bit, one reason.

## 3. THE GENERAL LESSON, WHICH IS WORTH MORE THAN THE FIX

> **GOLDENEYE HAS OTHER BUTTON-GATED STATES THAT VR WILL NEVER ENTER.**
>
> **ANYTHING THAT "DOES NOT APPEAR IN VR" SHOULD BE CHECKED AGAINST A GAME-SIDE
> GATE BEFORE IT IS INVESTIGATED AS A RENDERING FAULT.**

This is recorded as `169` U-17 for exactly that reason. **The cost of not knowing
it here was months of the crosshair simply being absent while the aim chain was
debugged blind.**

## 4. AND IT IMMEDIATELY EXPOSED THE NEXT FAULT

With the crosshair finally drawn, the wearer reported it **doubled — one place per
eye.** That is `166` §1 and `170`: the HUD is orthographic and was excluded from
every per-eye transform. **Two separate faults, and the first had to be fixed
before the second could even be seen.**

## 5. GATES

- **G-165-1** — the crosshair is visible in normal play without touching the aim
  button.
- **G-165-2** — it still disappears in cutscenes and on death (`NOCONTROL`,
  `DAMAGE` unaffected).
- **G-165-3** — `-NoXr` untouched: the patch is gated on `GE_VR_AIM_FROM_HAND`.
