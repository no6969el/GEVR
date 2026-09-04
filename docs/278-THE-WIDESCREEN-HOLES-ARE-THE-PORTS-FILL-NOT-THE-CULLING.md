# 278 — THE WIDESCREEN HOLES ARE THE PORT'S FILL, NOT THE CULLING. AND `277`'s THREE OWED ITEMS ARE STILL OWED.

**2026-08-30o. NO BUILD. Every run below is `277`'s binary — `goldeneye.exe` 2026-08-30 20:05:55,
18,017,350 bytes — verified by timestamp and size at the top of every block.**

> ## THE ONE-LINE RESULT
> **`[MEASURED]` The missing walls at widescreen are NOT the room-visibility pass. Two arms,
> 200 stationary frames each, same spot, artifact on screen in one: the cull census is
> BYTE-IDENTICAL. `GETV_WIDESCREEN` — a PORT knob that is ON BY DEFAULT — redefines the
> content's native width as a function of the REAL WINDOW's aspect and deliberately does not
> tell the game. `[REPORTED]` setting it to 0 restores pillarbox and removes most of the
> artifact.**
> **AND IT IS NOT CLOSED: artifacts remain with the knob off. There is more than one contributor.**

**THE SESSION WAS ASKED FOR THREE THINGS AND DELIVERED NONE OF THEM.** The two hoist sites were
never driven, `277` §8's audio falsifiers were never run, and the `MoveBond` counter is designed
but unwritten. §7 says why, and it is not a good reason on every count.

---

## §1 — WHAT RAN

| arm | log | what it was |
|---|---|---|
| H1 | `run_278_H1_runway60_on.log` | Runway 35, 60 Hz, term on — **tank never entered** |
| H2 | `run_278_H2_runway90_on.log` | Runway 35, 90 Hz, term on — **tank never entered** |
| H1' | `run_278_H1_streets60_on.log` | Streets 29, 60 Hz, term on — **tank never entered** |
| H3' | `run_278_H3_streets90_off.log` | Streets 29, 90 Hz, term off — **tank never entered** |
| W1 | `run_278_W1_full_normal.log` | Streets 29, SCREEN FULL + RATIO NORMAL, `GETV_CULLSTAT=1` |
| W2 | `run_278_W2_boot_wide169.log` | Streets 29, SCREEN WIDE + RATIO 16:9, `GETV_CULLSTAT=1` |
| V1 | `run_278_V1_widescreen_off.log` | Streets 29, **`GETV_WIDESCREEN=0`**, window maximised, 7 F9 dumps |

All carry their terminating `game_exit requested` (`262` §5). `GETV_SIMDIV=1` was pinned in every
arm; no `simulation held to` line appears in any of them.

**F9 dumps from V1: `dlgrab_1573/1676/1693/1714` (22:55), `2356/2763/2915/3048/3667/3932/4292`
(22:57), `2290/2849/3582` (23:02).** Their BMPs are **10,513,974 bytes = 54 + 2560x1369x3**, i.e.
the maximised window. **A SECOND, OLDER SET OF `dlgrab_*` FILES SITS IN THE SAME DIRECTORY FROM
`00:25-00:30` THE SAME DAY** — BMPs of 3,686,454 bytes = 54 + 1280x960x3, a windowed run from a
PREVIOUS session. §7.3.

## §2 — ►►►► THE FINDING: `GETV_WIDESCREEN` IS ON BY DEFAULT AND THE GAME IS NEVER TOLD ◄◄◄◄

`[MEASURED]` from source, and `[REPORTED]` confirmed by a run.

**`port_support.c:203` — `unsigned int configWidescreen = 1;`** Default ON. `GETV_WIDESCREEN=0`
turns it off. **The knob is in the binary** (`grep -a` -> 2 hits).

**`gfx_pc.c:423`, `ge_effective_native_width()`:**

```c
return gfx_native_height * ((float) gfx_current_dimensions.width / (float) gfx_current_dimensions.height);
```

`ge_scale()`, `ge_offset_x()` and `gfx_adjust_x_for_aspect_ratio()` all take their notion of "the
content's native width" from that. With the knob on, it is **the real window's aspect ratio**, so
`sx == sy` by construction and the pillarbox margin collapses to zero.

**AND THE COMMENT ABOVE IT SAYS THE QUIET PART OUT LOUD** (`gfx_pc.c:418-422`):

> *"Deliberately NOT written back into `gfx_native_width` itself. That variable is the game's own
> scissor-tracked canvas size (320x240, or 440x330 in the front-end's hi-res mode) and other code
> ... needs it to stay exactly what the game actually sent, not an aspect-ratio fiction."*

### 2.1 — THE NUMBER

`[MEASURED]` from the V1 dumps: **every `SETSCISSOR` in every dump reports a canvas of
`(0,0)-(1280,960)`** — the game's own drawing space, unchanged by the window. The BMP of those
same frames is **2560x1369**.

> **`ge_effective_native_width()` = 960 x (2560 / 1369) = `1795.2`.**
> **The game draws `1280`.**
> **`515` columns of native width — `28.7%` — are space the game never drew anything into.**

That is the artifact: hard-edged vertical slabs of whatever was last in the buffer, with real
geometry beside them, and neighbouring rooms' interior faces where one is admitted. It appears
when the window stops being the aspect it launched at — which is exactly `[REPORTED]`: *"if I go
full screen it will show it... if I leave it in small mode and how you launch it, it doesn't."*

### 2.2 — IT IS `P3`, IN ONE LINE
**There are two notions of view width and only one of them knows about the window.** `P3` says
resolution is ONE runtime variable. **`258` STAGE 6 replaces `guPerspective` with an off-centre
per-eye frustum (`P2`, four tangents per eye), which is a harder case of the same requirement.
So this is IN stereo's path** — unlike `268`'s artifact, which `00-STATE` §3 item 5 correctly
records as out of it.

## §3 — WHAT IT IS **NOT**: THE ROOM-VISIBILITY PASS IS EXONERATED

`[MEASURED]`, W1 vs W2, `GETV_CULLSTAT=1`, **200 stationary frames each, same spot, same facing,
the artifact on screen in W2** (`[REPORTED]` by the session lead, asked explicitly):

```
[getv][cull] curroom=9 drawn=2 maxrooms=56 rooms(front=1 straddle=1 BEHIND=0)
             vtx(total=609 front=244 straddle=365 BEHIND=0) cur(infront=4/8 nvtx=365)
```

**Byte-identical in both arms.** Same room, same two rooms drawn, same 609 vertices split the same
way, 200 frames each.

**This is a POSITIVE result, not a null.** If the admission pass knew the view had widened it would
admit MORE rooms at the same spot. It admits exactly the same. `bgDetermineVisibleRooms()`
(`bg.c:5638`) rebuilds the clip box every frame from `viGetViewLeft/Width/Top/Height`
(`bg.c:6198`), so a stale box was never the story either.

## §4 — WHAT IS STILL OPEN, AND IT IS THE NEXT SESSION'S FIRST TASK

1. **`GETV_WIDESCREEN=0` DID NOT ELIMINATE IT.** `[REPORTED]`: bars appeared on the sides, the
   perspective was visibly different, *"there were still minor cases of the issue."*
   **THERE IS MORE THAN ONE CONTRIBUTOR AND §2 IS ONLY THE LARGEST.**
2. **THE PER-ROOM PORTAL SCISSORS ARE THE SURFACE TO SUSPECT NEXT.** `[MEASURED]` the game emits
   sub-rectangles every frame, e.g. `dlgrab_2290`: `(820,120)-(1024,500)`, `(4,120)-(152,696)`;
   `dlgrab_2763`: `(236,388)-(400,584)`, `(712,436)-(808,488)`. They come from
   **`bg.c:622-677`**, where each room's 2D bbox is outersected against `screensize` and becomes a
   `SETSCISSOR`. **Same rooms admitted; the RECTANGLE each is clipped to is a separate question
   and §3 does not answer it.**
3. **THE MEASUREMENT THAT CLOSES IT: correlate ONE artifact frame's hole to ONE `SETSCISSOR`
   rect.** The dump and its BMP are the same frame by construction (`268` §8, and `93` is the doc
   that paid for that requirement). **Nobody has yet identified which V1 dump has the artifact on
   screen** — the session lead was asked and the session ended first.
4. **TWO SYMPTOMS, NOT ESTABLISHED AS ONE FAULT.** `[REPORTED]`: standing still gives *"a big
   black texture covering the wall that is typically white"* — **not see-through**; walking gives
   *"the right side show clear see-through."* **`263` §1 is the standing warning: six black faces
   were invented by inferring one fault from two screenshots. Do not merge these without a
   measurement.**

## §5 — THE TANK WAS NEVER ENTERED, AND THE ENTRY CHAIN IS NOW WRITTEN DOWN

Four arms across Runway and Streets. **`PtankZ` is converted in both Streets logs, so a tank model
loads.** Entry never happened, so **no hoist data exists and `277` §9's first owed item is
untouched.**

**THE CHAIN, FROM SOURCE — FOUR GATES:**

| # | gate | where |
|---|---|---|
| 1 | `stanSavedColl_posData->obj->type == PROPDEF_TANK` (45) — what Bond BUMPED INTO | `bondview2.c:2563` |
| 2 | `g_WorldTankProp` set | `:2569` |
| 3 | `g_BondCanEnterTank` — the rect test | `:2969-2973` |
| 4 | `moveData.btap` and the branch B took | `:5925/:5957` |

**THERE IS NO LEVEL WHITELIST.** Any `PROPDEF_TANK` is enterable. **AND THE DETECTION IS ARMED BY
BEING BLOCKED, NOT BY STANDING ON TOP:** the tank is picked up in `bondviewTryMoveToStan`'s
`block_20` (`bondview2.c:2540-2571`), the branch taken when the move is OBSTRUCTED.
**`[REPORTED]` the session lead said side-entry from memory and was right; my "climb on top" read
was wrong.** §7.2.

**DIFFICULTY IS DEAD AS A CANDIDATE.** `prop.c:1898` does carry a per-difficulty "Don't Load" mask
(`flags = 1 << (lvlGetSelectedDifficulty() + 4)`), and a `GETV_STAGE` boot silently runs AGENT
(`lv.c:1979`, which says so in its own comment) — **but a masked object is not loaded at all, and
`[REPORTED]` the tank is visible on every difficulty.**

**NO FREE INSTRUMENT EXISTS FOR THIS.** `GETV_VEHALL` and `GETV_VEH_DEBUG` cover `PROPDEF_VEHICHLE`
and `PROPDEF_AIRCRAFT` only; **nothing in the binary prints anything about a tank.** The proposal
is `GETV_TANKWHY=1`, ~20 lines in `bondview2.c`, printing the first failing gate of the four, with
its misaim signatures written in advance. **NOT BUILT.**

## §6 — `[INFERRED]` HOIST 1 LOOKS BACKWARDS. SOURCE READ ONLY, UNMEASURED, AND IT CONTRADICTS `275` §4.

`275` §4 priced both hoists on the reading that the numerator inside each `g_ClockTimer` loop is a
per-FIELD constant. **That is true at `propobj.c:5065` and appears FALSE at `bondview2.c:7339`.**

`g_TankTurretTurn` is rebuilt **every frame** in `bondviewProcessInput` (`bondview2.c:6071-6097`)
as `g_GlobalTimerDelta * turnspeed`. It is **already delta-scaled**, so retail's divide by
`g_GlobalTimerDelta` was a CANCELLATION, not a per-field conversion:

| arm | numerator/frame | divisor | `u` per iteration | iterations/s | steady output |
|---|---|---|---|---|---|
| 60 Hz, either | `1.0*s` | 1.0 | `s` | 60 | `s` |
| 90 Hz, term OFF | `1.0*s` | 1.0 | `s` | 90 | `s` |
| **90 Hz, term ON, hoisted (shipped)** | `0.667*s` | **1.0** | **`0.667 s`** | 60 | **`0.667 s`** |
| 90 Hz, term ON, unhoisted | `0.667*s` | 0.667 | `s` | 60 | `s` |

`tank_turret_turn_speed` is a first-order filter, `s <- SCALE*s + u`; `:7346` multiplies the state
back by `(1 - SCALE)`, so its steady output IS `u`.

**AND THE RUN SHEET'S PREDICTION FOR THIS SITE IS UNMEASURABLE AT THIS SITE.** `RUN-SHEET-276`
says *"the turret must not swing 1.5x faster at 90 Hz."* **The turret's actual rotation is
`g_TankTurretAngle += g_TankTurretTurn` at `bondview2.c:7236` — OUTSIDE every loop, delta-scaled,
and correct in all arms.** The hoisted expression feeds `vv_theta` at `:7349` as a **camera lean
while turning**, `ftemp * 4.0f`. **The predicted defect is a lean at 2/3 of retail, not 3/2, and it
is a few degrees.**

**`propobj.c:5065` CHECKS OUT.** `Rocket->unk94` is the constant `0.13333333f`
(`gun.c:1859` hand grenades, `gun.c:2214` GL grenades, `chraction.c:6933` guards) and is not
delta-scaled, so one whole field per iteration is right.

**AND THE GRENADE ARM HAS NO POSITIVE CONTROL ON THIS BINARY.** `RocketCurrent += speed` and the
friction are both per-iteration, so **resting distance is invariant to the frame rate in every arm
that can be run.** Only the UNHOISTED variant slides further, and that needs a build.
**`RUN-SHEET-276`'s *"it must come to rest over the same distance at both rates"* is satisfied by
construction and therefore proves nothing.**

## §7 — RETRACTIONS. THREE, ALL MINE, ALL THIS SESSION.

### 7.1 — *"the clip box never learns about 16:9, so wide admits fewer rooms"* — **FALSE, AND MEASURED FALSE.**
It predicted fewer rooms drawn at 16:9. **`[MEASURED]` the same rooms are drawn, 200 frames, both
arms.** The account was built from a source read of `bg.c:6198` that I did not test before stating.
**The correct scope: room ADMISSION is exonerated; the per-room clip RECTANGLE is not, and §4 item 2
is where that goes.** I then over-corrected in the other direction and said "culling is
exonerated" without qualifying which half — also wrong.

### 7.2 — *"the tank is entered by standing on top of it"* — **FALSE.**
`bondviewTryMoveToStan`'s tank detection is in `block_20`, the OBSTRUCTED branch
(`bondview2.c:2540-2571`). **You walk INTO it.** `[REPORTED]` the session lead said so from memory
and I read `:2969`'s rect test as "on top" without following the branch that arms it. **Same shape
as `275` §1's grep-for-a-guard and `277` §6.2's numbers-without-mechanism: FOURTH instance in four
sessions.**

### 7.3 — *"`dlgrab_2700` is a clean frame, so tell me which BMP shows it"* — **THE WRONG ARTEFACT.**
`dlgrab_2700` is dated **`2026-08-30 00:30`** with a **1280x960** BMP: a windowed run from a
PREVIOUS session. The V1 dumps are 22:55-23:02 with **2560x1369** BMPs. **I opened a dump from
another session and another window size and reported it as this run's result.** `00-STATE` §6's
second-stale-tree and `273` §1's tail-is-not-a-sample are the same family: **the artefact was not
identified before it was read.** Nothing here is void — the V1 scissor figures in §4 are from the
correct files — but the "2700 is clean" statement is withdrawn.

## §8 — TRAPS THIS SESSION PAID FOR

- **►►►► THE PORT LAYER HAS KNOBS A GAME-SIDE GREP CANNOT SEE. ◄◄◄◄** A sweep of every
  `GETV_*` across `getv/src` and `vendor/ge-decomp/src` returned 200-odd names and **did not
  contain `GETV_WIDESCREEN`**, because it lives in `gfx_pc.c`, which is **gitignored and
  regenerated** (`00-STATE` §6). **Four wrong turns were spent inside the game while the default-on
  knob sat in the renderer.** Grep `getv/port/**` too, and `grep -a` the exe.
- **A `GETV_STAGE` DIRECT BOOT HAS TWO INVISIBLE INPUTS.** It runs `fileValidateSaves()` and
  `fileSetCurrentFolder(FOLDER1)` (`boss.c:398-403`), so it **silently inherits folder 1's saved
  SCREEN and RATIO options** (`file2.c:1535-1541`) — and it **silently runs AGENT** because the
  difficulty menu never ran (`lv.c:1979`). **Both were uncontrolled in every arm above.**
- **`dlgrab_*` FILES ACCUMULATE ACROSS SESSIONS IN `getv\build-windows`.** Two sets from two
  different days and two different window sizes now sit side by side, distinguishable only by
  timestamp and BMP byte count. §7.3.
- **THE N64 `B` BUTTON IS `E` OR `F` ON THE KEYBOARD** (`port_input.c:1303`), A is `Enter`/`R`,
  Z is `Z`, R is `X`, Start is `Tab`. On a pad it is the pad's own B.

## §9 — WHAT IS OWED

- **ALL THREE OF `277` §9's ITEMS, UNCHANGED**: the two hoist sites driven, `277` §8's two
  intro-skip audio falsifiers, and the `MoveBond` executions-per-second counter.
- **§4 items 1-4** — the residual artifact with `GETV_WIDESCREEN=0`, the per-room scissor
  rectangles, the frame-to-rect correlation, and keeping the two symptoms separate.
- **A DECISION ON `GETV_WIDESCREEN`'s DEFAULT.** Same shape as `268` §7's owed default: a knob
  that is ON by default and silently changes what the renderer fills is what cost this session.
  **`GETV_WIDESCREEN=0` is a diagnosis, not a fix** — it buys correctness by giving up the
  widescreen image. The fix is `P3`: one runtime view width that the frustum, the scissor and the
  fill all read.
- **§6's hoist-1 read either confirmed or killed.** It contradicts a doc the owner signed off and
  it is `[INFERRED]` from source only. **Do not act on it without a measurement.**
