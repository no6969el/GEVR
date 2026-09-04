# 172 — U-16. THE CLAMP SPLIT, WITHOUT TOUCHING THE DRAW SITE.

**2026-08-25. BUILT, UNWORN. `169` U-16's "BLOCKERS: none" WAS WRONG, and the
mandatory grep caught it before a line was written.**

> ## THE SPLIT, AND STOCK GOLDENEYE ALREADY SHIPS HALF OF IT
>
> | quantity | clamped? | read by |
> |---|---|---|
> | `field_FFC` | **NEVER** | the GUN's pointing |
> | `crosshair_angle` | `[3, w-4]` | **the DRAWN sight AND the BULLET** |
>
> **The clamp is right for the sight and wrong for the shot, and one field is
> doing both jobs.** PD split exactly here — `bondgun.c:8419` clamps `crosspos`,
> `:8468` leaves `crosspos2` free.

---

## 1. THE OBVIOUS ROUTE IS BLOCKED, AND `169` SAID OTHERWISE

`161` P1-5 and `169` U-16 both say: **move the `[3, w-4]` clamp into
`gunDrawSight()`.** `169` recorded **"BLOCKERS: none."**

**THE MANDATORY GREP (`168` §5) SAYS IT IS BLOCKED:**

| symbol `gunDrawSight` needs | in `patches/` ? |
|---|---|
| `crosshairimage` | **NO** |
| `display_image_at_position` | **NO** |
| `get_screen_ratio` | yes |

**That is `115`'s cross-boundary hazard, and `157` already withdrew a slice to
it.** The entry was costed by reading the game source and never by checking the
boundary — **the exact failure `168` §5 was written to prevent, committed in the
same document that prescribes the cure.**

## 2. THE ROUTE THAT COSTS NOTHING: WE ALREADY OWN BOTH ENDS

`caclulate_gun_crosshair_position_rotation` **produces** the aim.
`bullet_path_from_screen_center` **consumes** it. **Both are already
`RECOMP_PATCH`ed by this project.** So:

- **PUBLISH** the aim in pixels **before** the clamp, into `g_geVrTrueAimPx`.
- **CONSUME** it in our own `bullet_path_from_screen_center`.
- **LEAVE `crosshair_angle` EXACTLY AS STOCK**, so `gunDrawSight` — which we
  cannot reach — keeps pinning the sight at the edge **with no change at all.**

> **ZERO NEW SYMBOLS. The function we cannot patch never needed patching: it
> needed to be left alone and fed a different field.**

## 3. THE TWO THINGS THAT WOULD HAVE BEEN WRONG

**THE SCREEN ORIGIN.** `crosshair_angle` has `screenleft`/`screentop` added
**after** the clamp. The published copy takes them too. **Getting this wrong
would offset the bullet by the screen origin — small, constant, and it would read
as a sight misalignment rather than a units bug**, which is the most expensive
kind of error this project has had.

**THE STALE FRAME.** `g_geVrTrueAimHave` is cleared at the top of the function
and set only when a value is published, so **a frame that publishes nothing falls
back to the clamped field rather than firing last frame's aim.** `48` rule 13 —
a static in patch code cannot be assumed zero.

## 4. `-FreeAim` IS SUPERSEDED FOR SHIPPING

`153` unclamped `crosshair_angle` itself, which frees the bullet **and walks the
drawn crosshair off the screen.** `153` called that *"DELIBERATE — the visible
proof the lock broke"* and *"wrong as a shipping state"*, and it was right on both
counts. **This achieves the same thing for the bullet without the second half.**
`-FreeAim` is kept as the proof it always was.

## 5. THE INSTRUMENT REPORTS WHAT WAS AIMED, NOT WHAT WAS DRAWN

`164`'s SHOT line now takes the unclamped value when the split is on. **Otherwise
it would disagree with the shot precisely when the aim leaves the screen
rectangle — which is the only situation this slice exists for.**

## 6. GATES

- **G-172-1 — BOTH HALVES, or it is not the split.** Aim past the screen edge:
  **the crosshair must STOP at the edge** *and* **the shot must keep tracking the
  gun.** Either alone is a different bug.
- **G-172-2** — `-NoClampSplit` restores the caught bullet, out of the same build.
- **G-172-3** — `-NoXr` untouched.

## 7. WHAT CHANGES ON THE SHEET

**U-16 — BUILT, and its BLOCKERS field corrected from "none" to the two
unreachable symbols, with the route that avoids them.** The lesson generalises and
is worth more than the slice:

> **A GAME FUNCTION YOU CANNOT PATCH IS NOT ALWAYS A BLOCKER. IF YOU OWN THE
> PRODUCER AND THE CONSUMER, YOU CAN CHANGE WHAT FLOWS BETWEEN THEM AND LEAVE THE
> UNREACHABLE FUNCTION UNTOUCHED.** `157` withdrew a slice for want of eight
> symbols; **this one needed none, and the difference was asking what the function
> READS rather than what it DOES.**
