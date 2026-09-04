# 258 — THE ROUTE. AND THE ENGINE ALREADY RENDERS N VIEWS PER FRAME.

**2026-08-29f. Written after the owner added `P6`-`P9` and asked for the
optimised build route. `257` §7 is not replaced — it is stages 0 and 1 of this.**

**NOTHING HERE HAS BEEN BUILT OR RUN.** Rule 1: this is a plan and it stops.

---

## §1 — THE FINDING. `[MEASURED]`, READ FROM SOURCE THIS SESSION.

**`lvlRender` (`vendor/ge-decomp/src/game/lv.c:762-796`) ALREADY LOOPS OVER
VIEWS, AND EACH ITERATION CARRIES ITS OWN VIEWPORT, FOV, ASPECT AND
PROJECTION.**

```c
pcount = getPlayerCount();
gSPClipRatio(DL++, FRUSTRATIO_2);
for (i = 0; i < pcount; i++) {
    set_cur_player(get_nth_player_from_shuffled(i));
    viSetViewSize(...); viSetViewPosition(...);
    viSetFovY(g_CurrentPlayer->fovy);
    viSetAspect(g_CurrentPlayer->aspect);
    DL = viClearZBufCurrentPlayer(DL);
    DL = viSetupCurrentPlayerView(DL);      /* fr.c:696 — THE SEAM */
    ...
}
```

**Consequences, in order of how much they change the plan:**

**1.1 — SPLIT-SCREEN IS THE EXISTENCE PROOF FOR MULTI-VIEW-PER-FRAME.**
Two to four views, each with its own viewport rectangle and its own projection,
**are already emitted into ONE display list and presented with ONE swap.**
This is retail behaviour, shipped, and the code is in our tree and compiled.
**It means the "N views per frame" question is answered before we write a line.**

**1.2 — IT DISSOLVES THE `gfx_run()` RE-ENTRANCY TRAP INSTEAD OF SOLVING IT.**
`255`/`256` recorded that `gfx_pc.c:5817` calls `start_frame()` at the top and
`swap_buffers_begin()` at the bottom, **so calling `gfx_run` twice per frame
swaps twice.** An eye loop placed at `lvlRender`'s per-player body **never calls
`gfx_run` twice.** It produces one DL containing two viewport blocks and hands
it over once — **exactly what split-screen already does.**
**`255` §3's architecture A/B was framed as a choice about where to double the
work. There is a third site, it is the one the engine itself uses, and it was
not on the list.**

**1.3 — IT ANSWERS `256` §2's 24 PRE-COMBINED LOADS.** `256` `[MEASURED]` 60
projection loads per frame: 36 byte-identical `PERSP` (the BG portal recursion
re-loading) and **24 `OTHER` with a view already multiplied in.** A substitution
at `gfx_sp_matrix`'s `G_MTX_PROJECTION` branch reaches the 36 and **cannot
correctly reach the 24.** A loop at `lvlRender` re-runs the whole render body per
eye, **so all 60 are produced correctly for the eye being drawn, by
construction.** The 24 stop being a decision of their own.

**1.4 — `viSetupCurrentPlayerView` IS THE SINGLE PROJECTION BUILD SITE**, and the
port layer already annotates it as such in-tree: *"This call is the only place
the projection matrix is built."* **That is `P2`'s replacement site, named and
already carrying a `GE_PORT_NATIVE` block.**

### ►►►► `1.5` — THE TRAP, AND IT IS THE MOST IMPORTANT LINE IN THIS DOC ◄◄◄◄

> **DO NOT IMPLEMENT STEREO BY SETTING `getPlayerCount()` TO 2.**

`[MEASURED]` **173 references across 35 files.** A split-screen player is a
separate *simulated entity*, not a second eye. Raising the count changes game
logic at sites that have nothing to do with rendering — among those read this
session: `alloc_window_pieces.c:14` sizes the shattered-glass buffer
`200 / getPlayerCount()`; `bondinv.c` gates **dual-wield** on
`getPlayerCount() == 1` at four sites; `bondview2.c` branches on it at three;
`bgfog.c`, `bgroomtrans.c`, `boss.c` all read it. **It would also spawn a second
Bond and tick him.**
**The eye loop must be NESTED INSIDE the per-player body and must leave
`getPlayerCount()` alone.** `P6`/`P9` want one player with one authoritative
position and two views of him — **not two players.**
**This is rule 6 in advance: check who else reads what you are about to write.**

---

## §2 — MULTIPLAYER: WHAT IS ACTUALLY ON DISK. `[MEASURED]`.

The owner asked whether the local multiplayer system survives. **It does, and
there is more than expected.**

| Thing | State | Evidence |
|---|---|---|
| `mpmenu.c` | present, 1,774 lines | `vendor/ge-decomp/src/game/mpmenu.c` |
| MP text banks | present, E and J | `LmpmenuE/J`, `LmpweaponsE/J` |
| **All of it LINKED into `goldeneye.exe`** | **yes** | `getv/build-windows/objects.txt:103,304,351,388` |
| Split-screen viewport code | present, compiled | `fr.c:770-826` (`viSetupScreensForNumPlayers`), 2/3/4-way fills |
| Per-view render loop | present, compiled | `lv.c:762` |
| **Four independently addressable N64 pads** | **yes** | `port_os.c:1046` `_Static_assert(GE_PORT_MAX_PADS == 4)` |
| Synthetic pad harness for ports 1-3 | present | `port_input.c:800` — *"a log showing four identical ports would prove the plumbing runs but not that the ports are independently addressable"* |
| **Networking in the port layer** | **present and linked** | `ge_net.c` (528), `ge_net_enet.c` (391), `ge_net_udp.c` (470), `ge_discovery.c` (255) |
| **Bot AI in the port layer** | **present and linked** | `ge_bot{,_ai,_arbiter,_doors,_nav,_route}.c` |

### `[ASSUMED]` — AND THE HONEST CAVEAT
**Linked is not run.** Nothing above has been exercised in this port in any
logged session. `48`: presence in `objects.txt` is a **build** fact, not a
**behaviour** fact. **The networking and bot layers are upstream's, their state
is unknown to us, and no claim is made that they work.**

### THE REAL LIMITER IS NOT PLAYER COUNT — IT IS THE OUTPUT SURFACE
`[MEASURED]` split-screen composes every player into **ONE framebuffer** with
viewport **rectangles** (`fr.c:696` sets `vscale`/`vtrans`; `viSetupScreensForNumPlayers`
fills the borders). **"One in VR, three on a monitor" therefore asks one
framebuffer to be simultaneously a headset swapchain image at headset resolution
and a desktop window at window resolution.** That is a second output target, and
it is a `P3`/`P4` structural question, **not a player-count question.**
**NO CLAIM is made here about 2 vs 4 players.** The cheap read that settles the
whole area is in §4, stage 3, and it costs one launch and no code.

---

## §3 — THE OWNER'S TWO DECISIONS, RECORDED

**3.1 — SINGLE PLAYER OUTRANKS MULTIPLAYER.** Owner, this session:
*"Multiplayer is not as important as single player experience."*
**`P9` therefore does NOT promote multiplayer into the build order.** It stays
what it was: a constraint that the sim, not the renderer, owns ballistics and
position — **which single player needs anyway** (`P6`, `P8`). **`P9` costs
nothing extra if `P6` is built correctly. It becomes expensive only if `P6` is
skipped.**

**3.2 — THE `P1`/`P9` COLLISION IS RESOLVED, BY THE OWNER, IN ONE SENTENCE.**
*"It could be that we limit the multiplayer to everyone of the same hz."*
**Accepted. This is the cheap and correct answer** and it retires the
determinism worry raised in `HANDOVER` 2026-08-29f.
**But it has ONE design consequence and it must be honoured at stage 4, not
retrofitted:**

> **THE SIM STEP MUST BE A VALUE THE PROGRAM CAN BE TOLD, NOT ONLY A VALUE IT
> COMPUTES.** `P1` says the rate is `60.0f / actualHz` read per frame from the
> runtime. A session that pins every peer to a common rate needs that same term
> **supplied** rather than **queried**. So the clock is built with the source of
> the numerator as an input: **runtime-queried by default, pinnable to a fixed
> value.** *"Every choice for this foundation builds on this so that we don't
> have to hack later on."* **The pin is one parameter at the moment the timestep
> is written. It is a rewrite if it is added afterwards.**

---

## §4 — THE ROUTE

**Ordering rule used throughout: nothing that costs a build comes before a read
that could change it, and nothing that makes a performance claim comes before
the instrument that could falsify it (`P5`, `49`).**

### STAGE 0 — COMMIT. UNCHANGED FROM `257` §7 STEP 0.
`COMMIT-NOW.cmd`, **main PC, not the bridge**. `fetch-thirdparty.sh regen`
before the native half — `gfx_pc.c` is gitignored. **Owner-only.**

### STAGE 1 — THE FREE READS. NO BUILD, THEN ONE BUILD. `257` §7 STEPS 1-4.
Run 1 (`GETV_SAVE_DEBUG=1`, separates `F1` from `F2`), build once, Run 2
(`GETV_ALIGNPTR=0`), Run 3 (`GETV_RECTPROBE=1`), **and the `RB-04` re-grep in the
NATIVE tree.**
**`RB-04`'s re-grep is a `P1` DEPENDENCY and stays first** — every line number in
it is recomp-era and `[ASSUMED]` (`168` §5). **No cost estimate may precede it.**

### STAGE 2 — THE FRAME BUDGET. `P5`. THIS IS THE GATE ON EVERYTHING AFTER IT.
`257` §6.1: `port_render.c:143` times three stages with `SDL_GetTicks()`,
**millisecond resolution against an 11.1 ms budget, through a per-frame `printf`
that costs more than it measures.** `gfx_sdl2.c:403` already has
`SDL_GetPerformanceCounter()`.
**Until this exists, "runs smoothly" is not a measurable claim and stereo's cost
cannot be reported, because there is nothing to subtract from.**
**The instrument must be able to say I CANNOT ANSWER THIS** (`48`) and must state
what it would report if pointed at a menu (`52`).

### STAGE 3 — THE BASELINE, AND THE TWO FREE EXISTENCE READS. NO CODE.
1. **The 60 Hz single-player baseline**, with stage 2's instrument. Before any
   stereo code (`257` §7 step 6).
2. **RUN 2-PLAYER SPLIT-SCREEN.** One launch, no code, and it reads on §1
   directly: **if two views with two projections in one DL and one swap are
   healthy in this port, the multi-view mechanism is proven before stereo is
   written.** If it is broken, that is a fault to find now and not inside a
   stereo bring-up. **This is `56`'s move — remove a thing and see what changes —
   run in reverse.**
3. **The four-pad read**, using the synthetic harness already in
   `port_input.c:800`. Settles §2's player-count question for the cost of a run.

**These three answer the local-multiplayer feasibility question the owner
raised, and none of them costs a build or a line of code.**

### STAGE 4 — THE CLOCK. `P1`, AND `RB-04`.
Sim rate `60.0f / actualHz`, per frame, **numerator queried by default and
pinnable** (§3.2). The `MoveBond` timestep, **rate-agnostic** — `bondview2.c`'s
exponential approach to a target, advanced once per frame with no timestep, is
why Bond walks exactly `90/60 = 1.487x` too fast on the owner's stopwatch
(`27.04s` vs `18.18s`).
**In source this is a diff against the matching decomp, so "did we change the
feel" is answerable and not an opinion** — which is the whole reason the project
moved to source.
**GATE (`239`): validated at TWO rates or it is not a setting. And `134`'s
numbers are recomp-era — `[ASSUMED]` here. THE NATIVE PORT HAS NEVER BEEN RUN
ABOVE 60.**

### STAGE 5 — THE POSE SPINE. `P6`. THE FOUNDATION, AND IT COMES BEFORE STEREO.
Head, both hands and a body proxy become **game-side state, written before the
tick, readable by game code.** No hardware required to build it: feed it
identity, then a synthetic path, exactly as `port_input.c` does for pads.
**WHY IT PRECEDES STEREO, AND THIS IS THE LOAD-BEARING ORDERING CLAIM OF THIS
DOC:** stereo needs a per-eye **view**, and the eye translation lives in the view
matrix (`255` §1 — projection-only is frustum shift, **not separation; that is
`B1` again**). **Build stereo first and it consumes a renderer-side pose; then
`P6` arrives and the eye path is reworked.** That is precisely the *"hack later"*
the owner's standing clause forbids. **Built in this order, `P6` costs nothing
extra and stereo consumes it.**
**`194` is the receipt: one missing term, four faults.**

### STAGE 6 — STEREO. `P2`, `P3`. THE EYE LOOP AT `lvlRender`.
Nested inside the per-player body (**never `getPlayerCount()` — §1.5**), taking
its per-eye view from stage 5 and **replacing** the projection at
`viSetupCurrentPlayerView` with **four tangents per eye, per frame** — `P2`,
because `guPerspective` cannot express an off-centre frustum, and because a
stored aspect is what produced `222` §2's `[MEASURED]` 30% error.
**THE GATE NEEDS NO HEADSET** (`255` §4): desktop side-by-side,
`GETV_STEREO_OFFSET=500`, halves cross-correlated, **`PREDICTION:` in pixels
written to the log BEFORE the screenshot.** 500 is deliberately absurd; ~6 cm is
tuned after the mechanism is proven.
**Report the cost against stage 3's baseline.**
**NOT in this stage:** OpenXR, head tracking, hand aim, vignette, HUD quad,
mirror, `gevr_xr.c`.

### STAGE 7 — AIM. `P8`. INDEPENDENT OF STAGE 6, AND IT MAY RUN BESIDE IT.
`66`: aim and stereo are independent. Once stage 5 exists, the aim ray is a
property of the hand in world space and **carries no camera term**.
**Do not re-litigate what is already measured:** `thr*camT` is **not** the bug
(`223` §2.2, `gunfire.c:570-574`); the residual is **camera-dependent**, ±3°
within a group and jumping between — **the signature of a camera term that should
not be there**; **pitch already tracks to ~5°, so the fault is yaw-only.**
**The sign trap:** engine yaw is the **negative** of the right-handed convention
(`bondview2.c` rotates by `360 - vv_theta`); `guPerspectiveF`/`guLookAtF` are
**row-vector**, GL/OpenXR **column-vector**.
**Free movement falls out of this stage, not out of a locomotion feature** —
aim stops depending on facing because it stops reading facing.

### STAGE 8 — HANDS AND BODY AS ONE SYSTEM. `P7`.
Two hands, then the body proxy, **derived from one reference space** — rule 8:
when two things must agree, do not synchronise them, remove the second one.
`U-25` head-relative locomotion is designed (PD `VrArmBodyFollow = 0.02`,
`bondgun.c:10991`; owner: *"Forward follows your head"*, *"I am in a seat that
spins"*). `U-24` calibration.

### STAGE 9 — MULTIPLAYER. DEFERRED BY §3.1, UNBLOCKED BY §3.2 AND STAGE 3.
Nothing is designed here and nothing should be until stages 3 and 5 have run.
**What stage 3 will have already told us**, for free: whether multi-view is
healthy, whether four pads address independently, and therefore whether local
play is 2 or 4. **What stage 5 will have already given us**: a sim that owns
position and ballistics — `P9`, paid for by single player.

---

## §5 — WHAT THIS ROUTE COSTS THAT THE OLD ONE DID NOT

**One stage: stage 5 before stage 6.** Everything else is `257` §7 re-ordered,
plus two free reads added to stage 3.
**And it removes a decision:** `255` §3's A vs B, and `256` §2's 24 pre-combined
loads, are both **superseded by §1** if the `lvlRender` loop holds up — which
stage 3's split-screen run tests **before any of it is built.**

## §6 — NOT CLAIMED
- **`[MEASURED]`** covers only what was read from source and `objects.txt` this
  session: the loop, the seam, the 173 refs, the linked MP objects, the four-pad
  assert, the presence of the net and bot files.
- **NOTHING HAS BEEN RUN.** No claim that split-screen works in this port, that
  the net or bot layers function, that four pads work, or that the `lvlRender`
  eye loop is cheap.
- **`[INFERRED]`, and it may not be built on** (`182`): that nesting the eye loop
  at `lvlRender` is cheaper than architecture A or B. **Stage 3 is the
  counter-example search, and it is one launch.**
- No cost estimate for `RB-04` — stage 1 owes the re-grep first (`168` §5).
- No claim `134`'s 87.1 fps transfers; **the native port has never run above 60.**
