# 293 — THE SECOND EYE DOES NOT LOSE ROOMS. IT LOSES MODELS. AND THE PASS THAT BUILDS THEM IS THE ONE `292` GATED OFF.

**Currency: 2026-09-01, session `293`, FIRST PASS. NOTHING HAS BEEN BUILT OR RUN THIS SESSION.**
Everything below is `[MEASURED]` from artefacts already on disk (18 `dlgrab_*.txt` dumps from
`292`'s S2/S2b/S2c/S2d/S2e arms) plus source reads. **No knob was changed, no binary was made.**

---

## §0 — THE HEADLINE, AND IT RETRACTS THE FRAMING IN `NEXT-SESSION-PROMPT-293`

`NEXT-SESSION-PROMPT-293` names the first job as:

> **THE TWO EYES ADMIT DIFFERENT GEOMETRY** … The only thing that differs is the **viewport
> rectangle**, and something in room admission or the portal traversal reads it.

**That is wrong on all three counts, and the dumps that were already sitting in
`getv\build-windows` say so.**

1. **ROOM ADMISSION DOES NOT DIVERGE.** `gSPSegment(SPSEGMENT_BG_VTX)` is written once per room
   by `bgRenderRoomPrimary`/`Secondary`. It is **equal in both eyes in every one of the eighteen
   dumps** — 2/2, 3/3, 4/4, 5/5, 6/6, 9/9, 10/10, 11/11, 12/12, 13/13, 15/15, 23/23.
   `SPSEGMENT_BG_DL` is 1/1 everywhere. **The portal traversal, `bgDetermineVisibleRooms` and
   `bgIsRoomOnScreen` are exonerated by measurement, not by argument.**
2. **WHAT DIVERGES IS THE chr/prop MODEL PASS, AND ONLY THAT.** `SPSEGMENT_MODEL_MTX` and
   `SPSEGMENT_MODEL_VTX` — written once per model draw — collapse in the second eye in every
   dump. `dlgrab_5249`: **MODEL_MTX 39 -> 1, MODEL_VTX 17 -> 0, BG_VTX 3 -> 3.**
3. **IT IS NOT A DIVERGENCE. IT IS A ONE-DIRECTIONAL LOSS.** Eye 1's set of `DL CALL` targets is a
   **strict subset** of eye 0's in **all eighteen dumps** — `only-in-eye1 = 0`, every time.
   **Nothing is ever admitted in the second eye that the first eye did not have.** A two-way
   divergence and a one-way loss are different bugs and want different repairs.

4. **AND THE SECOND EYE ALLOCATES NOTHING.** The `gSPSegment` **pointer values** — `dynAllocate`
   is a bump allocator, so they are a direct read on who allocated — show `MODEL_VTX` **`fresh=0`**
   in every dump that draws any model at all: **every model eye 1 draws comes out of a block eye 0's
   tick allocated.** Its one fresh allocation per frame is the viewmodel. §2.1.

**AND FAULT 3 IS NOT DOWNSTREAM OF THIS. IT IS THE SAME BUG SEEN FROM THE OTHER END** — see §3.
`292` §5a's *"Fault 3 is a consequence of that divergence, not its cause"* is **retracted**:
there is no upstream divergence to be a consequence of.

---

## §1 — THE MEASUREMENT

`getv/tools/dlgrab_eyecensus.py` (new, committed with this doc). It splits a `GETV_DLGRAB` dump at
its **viewport loads** — `gSPViewport` is `G_MOVEMEM` index `0x80`, and `292` FAULT 1 made those
per-eye copies, so they are the eye boundary — and censuses each half separately.

**IT REPRODUCES `292` §5a's OWN NUMBERS BEFORE IT IS BELIEVED** (`133`): on `dlgrab_5249.txt` it
finds the two viewport loads at **`521470A8`** and **`52147958`** — the exact pair `292` §5a
quotes from the display list — and **1060 / 622 triangle commands, 1940 / 1355 vertices.**
Same dump, same split, same numbers. It is measuring what the session measured.

**WHY THE SEGMENT COUNTS AND NOT THE TRIANGLE COUNT.** "1060 vs 622" says the eyes differ; it
cannot say **what** differs, because rooms and models both make triangles. The `gSPSegment` writes
can: seg 14/15 are written by the **room** path, seg 3/4/5 by the **model** path, in the same
dump. That is the whole trick, and it needed no build and no run.

**IT HAS A FALSIFIER** (rule `15`, `49`, `279` §7). `--selftest` builds a synthetic two-eye dump
whose eye 1 carries a draw eye 0 never had and **fails if the subset test does not fire**; it also
fails if the viewport splitter does not find two eyes. **`SELFTEST PASS`.**

### 1.1 — THE TABLE. **EIGHTEEN DUMPS, FIVE ARMS, ONE PATTERN.**

```
        dump | BG_VTX e0/e1  BG_DL e0/e1 | MODEL_MTX e0/e1  MODEL_VTX e0/e1  MODEL_COL1 e0/e1 |  tri e0/e1
 dlgrab_900  |         2/2          1/1  |            38/0            16/0             19/0   |   832/85
 dlgrab_2361 |         9/9          1/1  |           159/7           85/17            115/35   | 3100/1976
 dlgrab_2537 |       11/11          1/1  |           159/7           85/17            115/35   | 3147/2023
 dlgrab_2705 |       15/15          1/1  |           138/5           83/15            113/33   | 3457/2021
 dlgrab_2892 |       23/23          1/1  |           214/5          117/15            153/33   | 4382/2382
 dlgrab_2893 |       11/11          1/1  |            79/3           44/10             68/28   | 1989/1429
 dlgrab_3000 |         6/6          1/1  |           117/1            51/0             79/18   | 1935/1006
 dlgrab_3393 |         4/4          1/1  |            43/5           32/15             53/33   | 1661/1383
 dlgrab_3445 |         5/5          1/1  |            81/5           49/15             73/33   | 1999/1439
 dlgrab_3917 |       13/13          1/1  |           142/9           83/15            117/37   | 3025/1901
 dlgrab_4133 |       11/11          1/1  |            77/1            34/0             58/18   | 1753/1189
 dlgrab_5215 |         3/3          1/1  |            39/1            17/0             38/18   |  1061/623
 dlgrab_5249 |         3/3          1/1  |            39/1            17/0             38/18   |  1060/622
 dlgrab_5287 |       10/10          1/1  |           115/1            51/0             78/18   |  1751/905
 dlgrab_5543 |         9/9          1/1  |           195/5          100/15            133/33   | 3087/1681
 dlgrab_5595 |       12/12          1/1  |           154/2            69/1             99/19   | 2253/1125
```

**READ THE `BG_VTX` COLUMN FIRST. IT NEVER MOVES.** Rooms are admitted identically in both eyes at
every scene complexity from 2 rooms to 23. **`dlgrab_5595` is from S2e — the `MTXGUARD=2` arm —
and it is 12/12 on rooms and 69/1 on models, so the guard did not touch this.**

### 1.2 — AND THE PER-ROOM SCISSORS PAIR ONE FOR ONE

`dlgrab_5249`: **17 `SETSCISSOR` in each eye**, in the same order, same shapes, the second eye's
in the right half. That is an independent check on the same conclusion — the room list, its order
and its rectangles are the same in both eyes. **It is also the check that the eye split itself is
sound**: a split that leaked one eye's commands into the other could not pair 17 with 17.

**ONE THING IN THAT LIST IS NOT EXPLAINED AND IS NOT CLAIMED.** Of the six genuine per-room
rectangles, two translate by exactly `+640` between the eyes (`(8,120)-(484,628)` ->
`(648,120)-(1124,628)`) and four look like **one absolute box clamped into each half**
(`(4,120)-(640,840)` / `(640,120)-(1276,840)` reads as a single `[4..1276]` box cut in two).
**Whether the second shape means a room bbox that is NOT recomputed per eye is an open question,
not a finding.** It removes nothing today — the room geometry is identical either way.

---

## §2 — WHERE THE MODELS GO. **`propsTick()` IS NOT A SIMULATION TICK.**

`[MEASURED]` from source. `propsTick()` (`chrprop.c:2538`) walks the active prop list and calls
`chrTick()` / `objTick()`. Inside `objTick()` (`propobj.c:4294`), at **`propobj.c:5980-5992`**:

```c
var_v1_5 = ... posIsOnScreen(prop, &obj->runtime_pos, getinstsize(model), applyFogCull) ...;
if (var_v1_5 != 0)
{
    ...
    prop->flags |= PROPFLAG_ONSCREEN;
    mtxs = dynAllocate(model->obj->numMatrices << 6);
    model->render_pos = (RenderPosView *) mtxs;
    ...
    matrix_4x4_multiply_homogeneous_in_place(camGetWorldToScreenMtxf(), mtxs);
```

**So the "tick" does four things that are RENDER work, not simulation work:**

1. it runs the **on-screen admission test** (`posIsOnScreen`) — the one that reads the player's
   view rectangle and the per-room 2D box;
2. it sets **`PROPFLAG_ONSCREEN`**;
3. it **allocates `model->render_pos` from the per-frame arena**; and
4. it **fills it from `camGetWorldToScreenMtxf()` — the CURRENT VIEW MATRIX.**

`chraiUpdateOnscreenPropCount()` (`chrprop.c:219`) then builds **`g_OnScreenPropList`** from those
flags, and `chrpropsRenderPass()` (`chrprop.c:500`) — the render — iterates **that list only** and
emits `gSPMatrix(model->render_pos)` + `gSPSegment(SPSEGMENT_MODEL_MTX/VTX)` per prop.

**AND ALL FOUR OF THOSE, PLUS `chraiUpdateOnscreenPropCount()`, SIT INSIDE THE BLOCK `292` GATED
TO EYE 0** (`lv.c`, `if (geStereoIsFirstEye() && gePortSimShouldTick())`).

**The gate is not wrong — props must not tick twice.** What is wrong is that the block it guards
is **two jobs welded together**: a simulation tick that must run once per frame, and a **per-VIEW
model build that must run once per EYE.** `258` STAGE 6 gated both because there is one gate.

**So the second eye renders models from eye 0's list, admitted against eye 0's rectangle, through
eye 0's view matrix — and every model whose admission or matrices eye 0 did not leave behind in a
usable state simply is not drawn.** That is the 39 -> 1.

### 2.1 — **AND THE ARENA POINTERS PROVE IT, WITHOUT A BUILD AND WITHOUT A GATE READ.**

`dynAllocate()` is a **bump allocator with no bounds check at all** (`dyn.c:155-186`; that is why
running off the end segfaults instead of failing, `00-STATE` §7). So every block handed out in one
frame is a strictly rising address in the per-frame arena, and the `gSPSegment` **pointer VALUES**
— not just their count — say **who allocated in which eye**. `dlgrab_eyecensus.py --arena`:

```
dlgrab_5249   MODEL_MTX(3) eye0: n=39 range=52147258..521477D8
              MODEL_MTX(3) eye1: n=1  range=52147B08..52147B08
                eye1 reused-from-eye0=0  fresh=1  above-eye0-high-water=1
              MODEL_VTX(4) eye0: n=17 range=5229129C..522A6CCC
              MODEL_VTX(4) eye1: (none emitted)

dlgrab_2361   MODEL_MTX(3) eye0: n=159 range=52147258..52148B18
              MODEL_MTX(3) eye1: n=7   distinct=4 reused=3 fresh=1 above-high-water=1
              MODEL_VTX(4) eye0: n=85  range=52269744..522AC00C
              MODEL_VTX(4) eye1: n=17  distinct=10 reused=10 **fresh=0**
                -> EYE 1 ALLOCATED NOTHING. It is replaying eye 0's arena.

dlgrab_3393   MODEL_VTX(4) eye1: distinct=9 reused=9 **fresh=0**   (same)
```

**READ `fresh=0` ON `MODEL_VTX`. THAT IS THE FINDING.** Every model the second eye still draws is
drawn out of a vertex block **allocated during eye 0's tick**. The second eye builds **no model
geometry of its own, in any dump.**

**AND THE ONE EXCEPTION NAMES ITSELF.** Eye 1 emits exactly **one** fresh `MODEL_MTX` per frame,
and it is always **above eye 0's high-water mark** — so the arena bump pointer does carry on
across the eye boundary (`52147B08` sits just past eye 1's own view copies `52147AA8`/`52147AB8`).
In `dlgrab_5249` it appears at `seq=005639`, **after the last room scissor at `seq=005586`** —
i.e. in the post-room-loop block, which is the **viewmodel** (`bondviewRemoved7F08BCB8`,
`PROP_TYPE_VIEWER`), the one prop whose matrix is built in the RENDER path rather than the tick.
**That is why the second eye still shows the gun and the HUD and almost nothing else.**

**THIS IS ALSO THE FALSIFIER FAILING TO FIRE, WHICH IS THE POINT** (rule `15`). If the model build
ran per eye, eye 1's values would be **all fresh and all above eye 0's maximum**. They are the
opposite. `--arena` prints both numbers every time so the wrong answer is visible.

**AND HERE IS THE SENTENCE THIS SESSION EXISTS TO WRITE:**
> **`292` §1 doubled BOTH memory pools so that two eyes could each allocate — and then gated away
> the only code that allocates.** The pools are correctly sized for a build that never happens.

### 2.2 — WHICH MAKES THE DROP-SITE QUESTION SECONDARY, NOT OPEN

`chrpropsRenderPass` iterates the same `g_OnScreenPropList` in both eyes, and its
`getROOMID_isRendered` filter reads room flags that are **identical** (§1). `chrpropRender`
(`chrprop.c:446`) has no gate of its own. The per-prop returns are in `chrobjRenderProp`
(`propobj.c:7511`): `fogGetPropDistColor(...) == 0`, then `objAlpha <= 0`, then
`sub_GAME_7F04AC20`'s own `if (prop->flags & PROPFLAG_ONSCREEN)` (`propobj.c:7287`).
**Which of those three fires on which prop is NOT measured and is NOT claimed here** (§5).

**But it no longer blocks the repair**, and that is the useful part: whichever gate fires, `--arena`
says there was **nothing per-eye for it to have drawn**. A build that rebuilds `render_pos` per eye
changes the input to all three gates at once. **Naming the gate would refine the story; it cannot
change the cut.**

---

## §3 — WHY THIS IS ALSO FAULT 3, AND WHY `MTXGUARD` WAS ALWAYS THE WRONG PLACE

`00-STATE` §7 (new in `292`): `bondviewTransformManyPosToViewMatrix` converts `render_pos` from
`f32` to 16.16 **in place**, on the ALPHA pass (`chr.c:3538`), and `render_pos` is per-frame arena
state rebuilt on the OPAQUE pass. **One rebuild, one conversion.**

The rebuild is `propobj.c:5991` — **inside the tick.** The conversion is in the render — **inside
the eye loop.** With the tick gated to eye 0 and the render run twice, the pairing is
**one rebuild and two conversions**, by construction. Fault 3 is not a second bug that the
divergence happens to trigger; **it is the same missing per-eye rebuild, observed on the models
that DO still reach the alpha pass instead of on the ones that vanish.**

**This is why `GETV_STEREO_MTXGUARD=2` "showed better" and must still never ship.** Skipping the
second conversion removes the saturated matrices; it cannot restore a per-eye matrix that was
never built. `292` was right to call it a falsifier.

**AND IT ANSWERS THE DESIGN QUESTION `NEXT-SESSION-PROMPT-293` SAYS HAS NOT BEEN MADE** — *"who
owns `model->render_pos` per eye"*. **Nobody can, while the only thing that writes it is gated to
eye 0.** The question is not who owns the pointer; it is **where the model build lives**. The
shape that follows is: **split the gated block into `sim-once` and `build-models-per-eye`**, with
`posIsOnScreen` + `PROPFLAG_ONSCREEN` + the `dynAllocate` + the `camGetWorldToScreenMtxf()`
multiply + `chraiUpdateOnscreenPropCount()` on the per-eye side, and everything that advances the
world (`chrTick`'s AI and animation, `propsTickPlayer`, the horde tick, the autoaim and reload
work) on the once-per-frame side.

---

## §3a — THE CUT. **AND THE OBVIOUS ONE IS ILLEGAL.**

The obvious repair is *"move the model build out of the tick gate"* or *"run the gated block twice"*.
**Both are wrong, and the source says why.** `[MEASURED]` from `propobj.c:5900-6395` and
`chr.c:2840-3255`:

**THE ADMISSION TEST DOES NOT ONLY SELECT A MODEL BUILD — IT SELECTS BETWEEN TWO SIMULATION PATHS.**
In `objTick`, `var_v1_5` (the `posIsOnScreen` result) chooses between a branch that allocates
`render_pos` and one that clears `PROPFLAG_ONSCREEN` — **and each branch walks the prop's children
through a DIFFERENT function** (`sub_GAME_7F0442DC` vs `sub_GAME_7F04424C`), and each calls
`chrobjWeaponTick(prop)`. `chrTick` has the same shape: the `headSwitchVisible` branch rebuilds
**`chr->field_20`, the joint list** (torn down at `chr.c:2846-2851`, rebuilt at `:3222-3223`) and the
other branch clears the flag on both held weapons and the hat and latches `shadecol = nextcol`.

**So running either function twice per frame double-ticks weapons, children and colour lerps.**
And the ~40 lines immediately UPSTREAM of the admission test mutate the **portal table** —
`doorActivatePortal` / `doorDeactivatePortal` / `bgToggleDataPortalsContrlBytes1Bit1`
(`propobj.c:5922-5967`) — which is the graph `bgRoomVisibilityRelated` walks. **Running that per eye
would change the portal graph between the two eyes' traversals.** That the room sets still came out
identical (§1) says the hazard did not fire in these dumps; it does not say it is safe.

**THE ONE SHAPE LEFT STANDING** is therefore **not** a split of `objTick`/`chrTick` and **not** a
second tick. It is a **new render-only pass, per eye, over the props already admitted**: for each
entry of `g_OnScreenPropList`, re-`dynAllocate` `render_pos`, rebuild the matrices from
`camGetWorldToScreenMtxf()`, re-run `modelUpdateRelationsQuick` and re-derive `prop->zDepth` —
**and touch nothing else.** Admission, the child walks, `chrobjWeaponTick`, `update_color_shading`,
the portal toggles and `chr->field_20` all stay exactly where they are, once per frame.

**WHAT THAT SHAPE COSTS, STATED UP FRONT:** the second eye's prop ADMISSION is still eye 0's. At
zero separation that is exact; at a real IPD it is a sub-pixel difference in a test that already
admits by room, and §1 measured the room set identical. **It is a limitation to write down, not a
defect to discover later** — and it is the reason this shape is cheap.

**IT IS STILL NOT A PLAN.** The build block is ~400 lines and **has not been classified line by
line into "pure render build" and "mutates the world".** The candidates that must NOT re-run are
already named above; the ones that look idempotent (the tank/door `Switch.visible` writes,
`sub_GAME_7F03F540`'s collision rect) **look** idempotent and have not been proven so.
**That classification is the next piece of work and it is a source read, not a build.**

---

## §3b — THE CLASSIFICATION, DONE. **THE ENGINE ALREADY HAS THE GUARD, AND THERE IS EXACTLY ONE BLOCKER.**

`[MEASURED]` from source, `objTick`'s build block, `propobj.c:5983-6375`, read line by line. §3a said
this was owed before anyone writes code. It is now done, and it changes the shape twice.

### 3b.1 — EVERY ACCUMULATOR IN THE BLOCK IS ALREADY BEHIND THE ENGINE'S OWN "THIS PASS OWNS THE WORLD" FLAG

| line | mutation | guard |
|---|---|---|
| `:5985` | `update_color_shading(&obj->shadecol, &obj->nextcol)` — colour lerp | **`isSimOwner`** |
| `:6022`, `:6030` | iris-door `METAL_SLIDE_OPEN_SFX` / `CLOSE_SFX`, on an edge in `previousOpenPosition` | **`isSimOwner`** |
| `:6179` | `vehicle->wheelxrot += var_f0_3` — wheel spin | **`isSimOwner`** |
| `:6190` | `vehicle->wheelxrot += var_f0_3` **again, UNGUARDED** | **inert** — `var_f0_3` is initialised `0.0f` and assigned only inside the `isSimOwner` branch |
| `:6253` | `aircraft->rotoryrot += rotaryspeed` — rotor spin | **`(g_ClockTimer > 0) && isSimOwner`** |

**That is the complete accumulator list for the block, and there are no unguarded ones.**
`:6190` is called out because it **reads** unguarded and is not; anyone auditing this will stop there.

**AND THE FLAG IS THE RIGHT ONE ALREADY.**
`isSimOwner = get_player_position_in_shuffled(get_cur_playernum()) == 0` (`propobj.c:4548`) — the
engine's own *"this pass owns the world"* bit, and it is **`TRUE` in single player, always.** It is
the same idea as `geStereoIsFirstEye()` one level down, computed from the player index and blind to
eyes. **A per-eye build pass wants `isSimOwner && geStereoIsFirstEye()` and needs no new guards of
its own for anything in the table above.**

**THIS IS NOT "RE-RUN `objTick` WITH `isSimOwner` FALSE".** That would still run the child walks,
`chrobjWeaponTick`, and the whole `if (isSimOwner)` block at `:6395` onward. The point is narrower
and better: **the extracted build function inherits a codebase that already separates these.**

### 3b.2 — WRITES THAT ARE IDEMPOTENT, SO THEY MAY RE-RUN

`vehicle->wheelyrot = atan2f(...)` (`:6222`, unguarded but a pure function of `turnrot60`, `speed`
and switch data); `modelGetNodeRwData(...)->Gunfire.visible = tank->is_firing_tank` and
`Switch.visible = 0` (`:6351`, `:6357`). **Re-deriving them per eye writes the same values.**

### 3b.3 — AND THE ONE BLOCKER, WHICH IS REAL

```c
propobj.c:6347   sub_GAME_7F03F540(sp158, &sp16C, &tank_render->rect, &tank_render->collision);
```
`sp16C` is built from **`currentPlayerGetViewToWorldMtxf()`**. So this is a **VIEW-DEPENDENT WRITE
INTO WORLD STATE** — and that state is read by **`bondview2.c:2970`**,
`chrpropTestPointInPolygon(&g_CurrentPlayer->field_488.collision_position, &tank->rect, …)`:
**the test for whether the player can board the tank.**

Re-run per eye it takes the **last** eye's view. At the S3 gate's deliberately absurd
`GETV_STEREO_OFFSET=500` that is a **250-unit offset on the boarding test**; at ~6 cm it is
negligible. **It is a correctness question, not a rendering one, and it must be answered before the
build pass is written, not after.** It is also the only one of its kind found in the block.

**`00-STATE` §5 CARRIES AN OPEN "THE TANK IS UNENTERABLE" ITEM (`278` §5). THAT IS A MONO SYMPTOM AND
THIS IS A STEREO HAZARD. THEY ARE NOT THE SAME QUESTION AND MUST NOT BE MERGED** (`263` §1). This
doc claims only that the two touch the same struct.

### 3b.4 — AND A SECOND STORE OF PER-VIEW MATRICES THAT IS NOT THE ARENA

`modelFindNodeMtx(model, model->obj->Switches[n], 0)` (`:6114`, `:6122`, `:6132`, `:6290`, `:6299`)
returns a pointer into the **MODEL's node rwdata**, and the per-view matrices for autogun and
aircraft sub-parts are written **there**, not into the `dynAllocate`d block. That storage is **per
MODEL, not per eye**, so under a per-eye build the **last eye wins** for anything that reads it
outside the eye loop. **Doubling the arena does not cover this.** Whether anything outside the loop
reads it is **unread** and is the next item after §3b.3.

### 3b.5 — SO THE SHAPE, NOW WITH ITS EDGES

**Per eye:** `dynAllocate` + `model->render_pos`; every
`matrix_4x4_multiply_homogeneous*(camGetWorldToScreenMtxf(), …)`; `subcalcmatrices` with
`basemtx = camGetWorldToScreenMtxf()` (aircraft, `:6270`); `modelUpdateRelationsQuick`;
`prop->zDepth`.
**Once per frame:** admission and `PROPFLAG_ONSCREEN`; everything in 3b.1; `sub_GAME_7F03F540`
(3b.3); `chrobjWeaponTick`; both child walks; the portal toggles upstream (§3a); everything from
`:6395`.
**Undecided:** the rwdata matrices of 3b.4.

**`chrTick` IS CLASSIFIED IN §3c, AND IT DOES NOT MATCH `objTick`** — its one accumulator
(`flinchcnt`) is behind **no guard at all**, and the rest of its build is **cleaner** than
`objTick`'s. Read §3c before acting on §3b.

---

## §3c — `chrTick`, CLASSIFIED. **IT IS MORE SEPARABLE THAN `objTick` — AND IT HAS THE ONE THAT WOULD HAVE SHIPPED.**

`[MEASURED]` from source, `chr.c:2855-3230`. §3b left this owed. It is now read.

### 3c.1 — THE UNGUARDED ACCUMULATOR

```c
chr.c:2888   renderdata.basemtx = camGetWorldToScreenMtxf();
chr.c:2889   renderdata.mtxlist = dynAllocate(model->obj->numMatrices * sizeof(Mtxf));
chr.c:2891   if (g_CurModelChr->flinchcnt >= 0)
chr.c:2893       g_CurModelChr->flinchcnt += g_ClockTimer;      /* <-- NO isSimOwner. NO guard at all. */
chr.c:2898       if (g_CurModelChr->flinchcnt >= 30)  /* 24 on EU */
```

**`flinchcnt` is the flinch timer, it is advanced by `g_ClockTimer` INSIDE the build block, and it
is behind NO guard of any kind.** Run the build twice per frame and **every character recovers from
being shot in half the time.** That is not a rendering artefact — it is the test in the mission's
own point `3`: *would a 1997 player notice this as the game behaving differently?* **Yes.**

**SO §3b.1's RESULT DOES NOT GENERALISE.** *"Every accumulator is already behind `isSimOwner`"* is
true of `objTick` and **FALSE of `chrTick`.** Anyone who reads §3b and skips §3c ships a
half-length flinch. **The extracted build pass must hoist this one out explicitly.**

**Also unguarded, but debug-only:** the held-weapon position nudges at `chr.c:3071-3101`
(`entry->x/y/zoffset += 0.02f` under `!get_debug_render_raster()` and L-trigger chords) — the
developer's tuner. It would double-step per eye. **Named for completeness, not a shipping concern.**

### 3c.2 — AND THE REST OF `chrTick`'s BUILD IS BETTER SHAPED THAN `objTick`'s

**The joint list is rebuilt FROM NULL every pass** — `chr->field_20 = sub_GAME_7F06B120(NULL, model)`
(`:2914`), appended to by `chrRenderHeldWeapon` for both hands (`:3018-3019`) and by the hat
(`:3171`), then finalised by `sub_GAME_7F06B29C` / `sub_GAME_7F06BB28` (`:3222-3223`); the previous
one is torn down at `:2846-2851`. **It carries nothing across passes.** Both matrix lists
(`:2889` and the hat's at `:3033`) come from a fresh `dynAllocate` with
`basemtx = camGetWorldToScreenMtxf()`. `chr->chrflags |= CHRFLAG_HAS_BEEN_ON_SCREEN` (`:2858`) is a
sticky idempotent flag.

**So once `flinchcnt` is hoisted out, `chrTick`'s build re-runs cleanly** — which is the opposite of
what §3a's caution predicted, and it is the good news of this section.

### 3c.3 — THE INVARIANT THAT FALLS OUT, AND IT IS FAULT 3 AGAIN

```c
chr.c:3160   matrix_4x4_multiply_homogeneous((Mtxf *)hatmodel->render_pos, &mtx, &tmp);
chr.c:3161   matrix_4x4_copy(&tmp, (Mtxf *)hatmodel->render_pos);
```
**An IN-PLACE transform of `render_pos`** — the same family as `bondviewTransformManyPosToViewMatrix`
(`00-STATE` §7). It is safe today **only because `render_pos` was freshly allocated a few lines
earlier in the same pass.** So:

> **THE BUILD MUST RE-RUN AS A WHOLE PER EYE. A PARTIAL RE-RUN RE-TRANSFORMS.**
> Every in-place operator in this code is correct exactly once per fresh allocation, and `292`'s
> fault 3 is what a mismatched pairing looks like on screen.

**That invariant is the thing to write into the eye-loop design, and it is the reason a "just
rebuild the matrices" patch that reuses the existing block is more dangerous than it looks.**

---

## §4 — WHAT THIS RETRACTS

- **`292` §5a: *"Fault 3 is a consequence of that divergence, not its cause. Whatever makes a
  half-width viewport admit a different room set is the next question."*** **RETRACTED.** A
  half-width viewport admits the **same** room set — measured, eighteen dumps.
- **`NEXT-SESSION-PROMPT-293`'s first job as written** — "something in room admission or the
  portal traversal reads [the viewport rectangle]" — **is looking in a subsystem the evidence
  clears.** `00-STATE` §5's *"do not reopen room ADMISSION"* (from `278`) held after all, one
  question over.
- **Nothing else.** `292`'s FAULT 1 and FAULT 2 stand; S1 stands; the pool sizing stands.

## §5 — NOT CLAIMED

- **WHETHER ANYTHING OUTSIDE THE EYE LOOP READS THE rwdata MATRICES OF §3b.4 IS UNREAD.**
- **NOTHING WAS BUILT OR RUN.** No claim that the split in §3 compiles, is affordable, or is even
  the right cut.
- **THE EXACT PER-PROP GATE THAT DROPS THE REMAINING MODELS IS NOT IDENTIFIED** — see §2.2. It is
  one of `fogGetPropDistColor == 0`, `objAlpha <= 0`, or the `PROPFLAG_ONSCREEN` test in
  `sub_GAME_7F04AC20`, and **which one fires on which prop has not been measured.**
  **`GETV_CHR_DEBUG` already carries counters for those gates and is already in the binary**
  (`chr.c:45-67`, `ge_chr_dbg_on()`), but **they are not tagged by eye**, so as they stand they
  cannot separate the two passes. Tagging them is a build. **It is worth doing for the record and
  it is NOT on the critical path** (§2.2).
- **`fogGetPropDistColor` IS ONE OF THE TWO UNTESTED CANDIDATES `289` §4 LEFT STANDING FOR THE
  VANISHING PROPS** (`fog` = 12,257, never tested). **That these two questions now touch the same
  function is a COINCIDENCE OF LOCATION, NOT A LINK, and must not be merged** (`263` §1).
- **S3 HAS STILL NEVER RUN.** No separation has ever been applied. Nothing here changes the gate
  in `RUN-SHEET-292` §5, and it must not be run until S2 is clean at zero separation.
- **The scissor shape in §1.2 is an observation, not a mechanism.**

## §6 — STILL OWED, CARRIED FORWARD (UNCHANGED)

All of `277` §9 · `278` §6's INFERRED hoist-1 read · `279` §5's amount arm · `280` §7.3's
black-wall dump · `274` §7's CONTAMINATED gate · `287` ARM 6 the wear pass, **STILL NEVER RUN** ·
`289` R2's missing `dlgrab` · `GETV_ROOMSCISSOR=0` as a default, still unjustified because ARM 6
has never run. **`293` opened none of these and closed none of them.**
