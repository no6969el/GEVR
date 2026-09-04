# 292 — THE EYE LOOP IS WRITTEN. AND BOTH DISPLAY-LIST POOLS ARE SIZED FOR ONE VIEW.

**2026-09-01, session `292`. `258` STAGE 6, `P2`/`P3` — up to the first gate and not one line
past it.** `291` left the pose spine worn green, so the eye loop may consume `gePoseCurrent()`.
This session designed the per-eye view and projection at `fr.c:696` **from source before writing
anything**, found one thing that changes the design, wrote the code, and validated the
mathematics offline.

**WRITTEN AND VALIDATED OFFLINE — NOT BUILT, NOT RUN.** Rule `1`: every build, every run and
every commit is the owner's, main PC. `RUN-SHEET-292.md` carries every block.

**`290`/`291` were NOT re-run and nothing in `00-STATE` §5 was reopened.** Confirmed on the
bridge with safe reads only (`git log`, `git show`, `git diff <path>` — never `git status`/`git
add`, §6): `GoldenEyeVR` `7c58574` (291 docs), `goldeneye-native` `868776a`, `vendor/ge-decomp`
`4014d36a` (290's three).

---

## §1 — THE FINDING. **BOTH POOLS ARE SIZED BY `getPlayerCount()`, AND AN EYE IS NOT A PLAYER.**

`[MEASURED]`, read from source this session, `vendor/ge-decomp/src/game/dyn.c:40-41, 90-96`:

```c
s32 g_GfxSizesByPlayerCount[] = {0x10000, 0x18000, 0x20000, 0x28000};
s32 g_VtxSizesByPlayerCount[] = {0x10000, 0x18000, 0x20000, 0x28000};
...
g_GfxBuffers[0] = mempAllocBytesInBank(g_GfxSizesByPlayerCount[getPlayerCount() - 1] * 2, ...);
g_VtxBuffers[0] = mempAllocBytesInBank(g_VtxSizesByPlayerCount[getPlayerCount() - 1] * 2, ...);
```

**The display-list pool AND the vertex pool are both indexed by player count, once, at level
load.** `258` §1.5 forbids raising `getPlayerCount()` — 173 refs, 35 files, game logic — so the
eye loop renders the body **twice out of the pools sized for ONE view**. Retail never meets
this: two split-screen players index `[2 - 1]` and are handed `0x18000`.

**AND `dyn.c`'s OWN `GE_PORT_NATIVE` COMMENT ALREADY RECORDS WHAT RUNNING OUT COSTS** — it was
written for a different reason (`Gfx` is 16 bytes here, 8 on hardware) and it describes this
failure exactly:

> *"When a level exceeds it, the writer simply stops appending — no terminator, no error — and
> `gfx_run_dl` walks off the end of the truncated list into whatever follows it in the pool,
> which is vertex data. On Jungle in first person (17 rooms, 15,458 triangles, the largest
> submission observed) the final prop record is cut off after 10 of its 13 commands … and the
> walk then executes `Vtx_t` structs as opcodes until a `G_VTX` with a garbage address
> segfaults."*

**A silent truncation followed by a segfault is the worst possible first failure for a stereo
gate, because it reads as "the eye loop crashed" and sends the next session into the eye loop.**
It is the same family as everything in §6 of `00-STATE`: everything reports success while the
artefact is wrong.

**THE VERTEX POOL IS THE ONE THAT WOULD HAVE BEEN MISSED.** `dynAllocateMatrix()` and
`dynAllocateLights()` both take from `g_GfxMemPos`, which starts inside `g_VtxBuffers` — so a
second eye doubles the **matrix** traffic as well as the vertices, and
`bondviewUpdateCameraMatrices()` alone allocates four matrices per eye. The existing
`GETV_GFXPOOL` block scales **only** the `Gfx` side, for a different reason, and copying its
shape without reading it would have scaled half of what needed scaling.

**The fix is the same shape as the block already there and is inert with the knob off:** scale
both tables by the eye count at `dynInit`. `[INFERRED]`, and it is the one number the run has to
check: retail gives 1.5x for two players, not 2x, so 2x is generous rather than tight — but a
pool that is generous per view and a pool that is big enough for TWO Jungle-sized views are not
the same claim, and only the run can say which.

---

## §2 — THE FOUR OTHER READS THAT CHANGED THE CODE. ALL `[MEASURED]` FROM SOURCE.

**2.1 — `propsTick()` IS INSIDE THE PER-PLAYER BODY, SO THE EYE LOOP WOULD TICK IT TWICE.**
`lv.c:839` (now `:850`): the whole simulation block — `gePortPoseProbeAtTick()`, `propsTick()`,
`gePortPropHistoryTick()`, `gePortHordeTick()`, the autoaim and reload calls and
`propsTickPlayer()` — sits **between** `bgRoomVisibilityRelated()` and `bgLevelRender()`, inside
the loop the eye loop wraps. `gePortSimShouldTick()` is a pure read of a flag
(`frametiming.c:338`), so it cannot defend itself. **The eye gate is `geStereoIsFirstEye() &&
gePortSimShouldTick()`, in that order, so the `&&` short-circuits and eye 1 never even asks.**
And `frametiming.c`'s own comment says why a counter that advanced per call would be wrong.

**2.2 — `viSetViewSize()` WRITES BACK INTO THE PLAYER STRUCT, SO THE SECOND EYE WOULD GET A
QUARTER.** `fr.c:880-884`: `viSetViewSize()` calls `currentPlayerSetScreenSize()`, which writes
`g_CurrentPlayer->viewx`; `viSetViewPosition()` calls `currentPlayerSetScreenPosition()`. The
existing line is `viSetViewSize(g_CurrentPlayer->viewx, ...)` — **it reads the value it is about
to overwrite.** Halving that inside the loop halves an already-halved width on the second
iteration. **The player's rectangle is therefore captured ONCE before the eye loop and restored
after it.** Nothing about this is visible from the eye loop's own lines; it is two hops away.

**2.3 — AND THAT SAME WRITE-BACK IS WHY THE HALVES SCISSOR FOR FREE.**
`bgScissorCurrentPlayerView()` (`bg.c:2277`) clamps every room's clip rectangle to
`g_CurrentPlayer->viewleft/viewtop/viewx/viewy` — **the player's rectangle, not the video
mode's.** Setting the eye's viewport through `viSetViewSize`/`viSetViewPosition` therefore
carries the half into the per-room scissor with no separate plumbing, and `GETV_ROOMSCISSOR=1`
(shipping) is the arm that uses it. **This is why the side-by-side needs no renderer change at
all.**

**2.4 — THE CULLING SCALES RE-DERIVE PER EYE, AND THEY ARE ASYMMETRY-BLIND.**
`viSetViewSize` also calls `currentPlayerSetCameraScale()` (`bondview.c:653`), which rebuilds
`c_scalex/c_scaley`, `c_recipscale*`, the LOD scales and `c_cameraleftnorm`/`c_cameratopnorm`
from `c_halfwidth`/`c_halfheight`/`c_perspfovy`/`c_perspaspect`. **So the eye's viewport
automatically re-derives the plane normals `posIsOnScreen` reads — self-consistent, and free.**
But those normals are built from a **symmetric** half-angle and **cannot express an off-centre
frustum.** That is a real limitation and it is named here rather than discovered later. It costs
nothing at this gate for a reason that is already `[MEASURED]`: **`289` §4 established that the
five view planes remove ZERO props in the shipping configuration.** That is a result being
*used*, not a dead theory being reopened.

---

## §3 — THE DESIGN. **ONE NEW MODULE, FOUR SEAMS, AND NOTHING UNDER `getv/port/`.**

The eye loop is nested **inside** `lvlRender`'s per-player body (`lv.c:785`), leaves
`getPlayerCount()` at 1, and emits **two viewport rectangles into ONE display list presented with
ONE swap** — which is what split-screen already does, so `gfx_run()` is never called twice
(`258` §1.2). **`gfx_pc.c` and `gfx_sdl2.c` are untouched, so `verify` stays `15/15` and NO REGEN
IS OWED** (`287` §5). `git ls-files` was checked before deciding this, not after (§6).

| site | change | why it is there |
|---|---|---|
| `src/game/stereo.c` / `.h` **NEW** | the eye model: knobs, eye count, per-eye viewport, the four-tangent frustum, the eye translation, the PREDICTION printer | one place that can be compiled and falsified on its own |
| `src/game/lv.c` | the eye loop + the sim-tick gate + `geStereoPredict()` | §2.1, §2.2 |
| `src/fr.c` `viSetupCurrentPlayerView` | the four-tangent projection, **after** `guPerspectiveF`, not instead of it | `P2`; and `g_viPerspNorm` stays exactly as `guPerspectiveF` set it (`255` §1) |
| `src/game/bondview2.c` `bondviewUpdateCameraMatrices` | the eye **translation**, into `cam_pos`, immediately after the `GETV_INTERP` swap | **`255` §1: the translation lives in the VIEW matrix** |
| `src/game/dyn.c` | both pools scaled by the eye count | §1 |

**WHY `bondviewUpdateCameraMatrices` AND NOT THE PROJECTION.** Everything the frame draws with
is built from `cam_pos` there: `field_5C`/`field_60` (the RSP geometry matrix), `field_64`
(world→screen, which `camGetWorldToScreenMtxf()` hands to twenty-odd call sites), `field_68`
(view→world), `field_10E0` (projection × view) and `bondviewUpdateFrustumPlanes()`. **Moving the
position moves all of them; moving the projection moves none of them.** That difference is `B1`,
from `43` to `71`, and it is `255` §1 point 3 in the one available reference tree, which wires
`gevr_shim_eye_projection_n64` and never calls `gevr_shim_eye_view_n64` at all.

**The offset is placed AFTER the interpolation swap** so it is never fed back into
`gePortCamInterp`'s history — that history is per **player** and must stay per player, not per
eye.

**`P6` HOLDS ON THE LIVE PATH.** The eye vector is read from `gePoseCurrent()` — the pose the sim
owns, written before the tick (`290`/`291`) — and not from a renderer-side pose. At the identity
pose it degenerates to ± half the separation along the camera's own right vector, which is all
the first gate asks for.

---

## §4 — THE MATHEMATICS IS VALIDATED, NOT ASSERTED. **`stereo_harness.sh`, 42/42, `-Wall -Wextra -Werror` CLEAN.**

It compiles the **REAL** `stereo.c` against type stubs — the file it tests IS the file that ships
— together with **verbatim** copies of `guPerspectiveF` (`libultra/gu/perspective.c`) and
`matrix_4x4_set_lookat` (`game/matrixmath.c`).

**4.1 — THE ROW-VECTOR CONVENTION IS CHECKED, NOT BELIEVED.** With the symmetric tangents the
four-tangent matrix equals `guPerspectiveF`'s own output to **`1.192e-07`** — float epsilon. A
transposed or column-vector matrix fails here, in a harness, instead of in a RenderDoc capture.
`00-STATE` §7's row-vector fact is now a passing test rather than a note.

**4.2 — THE SIGN IS INHERITED, NOT REASONED ABOUT.** `matrix_4x4_set_lookat` normalises forward
with a **negative** reciprocal (stored forward = −look) and takes `right = up × forward`. The eye
offset is computed with **those same six lines**, so whatever handedness the engine has, the
offset has it too. Engine yaw being the negative of the right-handed convention never has to be
asserted. The harness then measures, through the full matrix chain, that **the right eye's image
sits FURTHER LEFT** — which is the gate's required sign, derived rather than guessed.

**4.3 — THE 1/D LAW IS THE DISCRIMINATOR, AND THE FALSIFIER IS TUNED TO BE CONVINCING.**
A real separation moves a near object more than a far one: `disparity / eye_width = −SEPARATION /
(D · (tanR − tanL))`. A projection-only offset moves **every depth by the same amount**.
`GETV_STEREO_MODE=2` builds the projection-only version **on purpose**, and its shift is chosen so
that at D = 1000 it produces **exactly** the disparity the real thing produces — `-103.923` px
against `-103.923` px in the harness. **It would pass a single-depth eyeball check. It fails the
ratio: `1.0000` where the real thing reads `4.0000`.** That is how `B1` survived from `43` to
`71`, reproduced deliberately so the gate can be shown to fire.

**4.4 — THE PREDICTION PRINTER'S OWN ARITHMETIC IS CHECKED** against a value computed in the
harness script from the tangents the block itself printed. **An instrument nobody has tried to
break is not an instrument** (`49`, rule `15`).

**4.5 — AND THE MEASURING SCRIPT HAS ITS OWN FALSIFIER.** `stereo_disparity.py --selftest`
injects a known −37 px shift into a synthetic frame and fails loudly if the correlator does not
recover it. `279` §7: a detector tuned on the positive frame passes its own contract until it
meets the negative one.

**4.6 — AND ALL FIVE TOUCHED FILES PARSE WITH THE BUILD'S OWN FLAGS. THIS GATE IS A CORRECTION,
AND IT COST A BUILD.** The first offline pass ran `gcc -fsyntax-only` **without**
`build_windows.ps1:207`'s `-include src/ge_port_decls.h`, reported 0 errors on everything, and
**missed a local `extern` that disagreed with the real prototype**: `stereo.c` declared
`bondviewGetCurrentPlayersRoom` as returning `s32`; it returns **`u8`** (`bondview.h:2822`). A
conflicting type is an **error**, not a warning, so `build_windows.ps1:160`'s `-w` did not touch
it; the file never compiled, and the build failed at **LINK** with eight
`undefined reference to 'geStereo…'` lines that read like a missing build entry and were nothing
of the kind. **The local externs are now DELETED — `ge_port_decls.h` already declares all three —
and `stereo_harness.sh` parses `stereo.c`, `lv.c`, `fr.c`, `bondview2.c` and `dyn.c` with
`build_windows.ps1`'s own flag list: 0 errors each.** `00-STATE` §6 carries the trap.
**And it retracts a claim made earlier in this document's own history:** `bondview2.c`'s "12
pre-existing gcc errors" were the same missing force-include. With the build's flags it reports
**0**.

---

## §5 — THE GATE. **IT NEEDS NO HEADSET, AND IT IS THREE NUMBERS, NOT A PICTURE.**

`255` §4's shape, `70`'s ordering. Every block is in `RUN-SHEET-292.md`.

```
GETV_STEREO=1  GETV_STEREO_OFFSET=500  GETV_STEREO_PROBE=60

PREDICTION: printed by the build, in the log, BEFORE the picture is taken — from THAT
            BUILD's own four tangents and THAT BUILD's own offset, at the depth of
            whatever the player is looking at, measured with the engine's own ray test.
            It says CANNOT ANSWER rather than assuming a depth.
REQUIRED:   |measured - predicted| <= 5 px, and the sign must match: the RIGHT eye's
            image FURTHER LEFT. AND the log's own 1/D ratio must read 4.000, not 1.000.
TODAY:      no stereo has ever run in this port. The gate cannot pass by accident.
```

**Three failures, three different numbers** (`255` §4): zero disparity is `B1`; the wrong sign is
a swapped eye; the wrong magnitude is a units error. **And a fourth the recomp era did not have:
the right magnitude at one depth and the wrong law across three is a projection-only build, which
is the failure that looks most like success.**

**500 game units is deliberately absurd. ~6 cm is tuned AFTER the mechanism is proven, never
before — a knob validated at one value is not a setting (`239`).**

---

## §5a — IT WAS BUILT AND RUN. **S1 GREEN. S2 FOUND THREE FAULTS AND ALL THREE WERE MINE.**

**`[MEASURED]` 2026-09-01, same session.** S2 is the arm `292` §6 wrote to catch *"the render body
survives being driven twice"*. **It caught it. That `[INFERRED]` is now RETRACTED — the body does
NOT survive being driven twice, and the reason is not particles.**

**S1 (knob off) — GREEN.** Zero `[getv][stereo]` lines, `props interpolated 0`, zero `simulation
held to`, `ours: x=367.333`, clean `game_exit requested`. The shipping path is untouched.

### FAULT 1 — THE DISPLAY LIST HOLDS A **POINTER** TO A VIEWPORT SLOT THE TWO EYES SHARE.
`fr.c:707` emitted `gSPViewport(&g_CurrentPlayer->viewports[g_ViBackIndex])`. That array is indexed
by the FRAME's back-buffer index, so within one frame it is ONE struct: both eyes wrote it, both
pointed at it, the second write won, and **both halves were transformed by the last eye's
rectangle.** Eye 0's world geometry was mapped into the right half and then scissored to the left
half, so it landed nowhere and the left half kept only what does not go through the viewport
transform — the sky fill. `[MEASURED]` `dlgrab_900.bmp`: one correct image, one flat blue
rectangle. **This is `67`/`70`'s fault from the recomp era in a different renderer — two draws
sharing one slot (`255` §3) — and `258` §1.5's *"an eye is not a player"* turns out to govern
graphics resources too.** Fixed with the pattern the same function already used one line below for
the projection: a per-eye copy from the per-frame arena. **Confirmed from the DL itself:** eye 0
`MOVEMEM 521470A8`, eye 1 `52147958`, and correct per-eye scissors `(1,30)-(160,210)` /
`(160,30)-(319,210)`.

### FAULT 2 — THE ASPECT WAS HALVED IN ONLY ONE OF THE TWO PLACES THAT DESCRIBE THE CAMERA.
The first cut halved it inside `geStereoBuildFrustumF` and told the game nothing, so the RSP drew a
half-width frustum while `c_perspaspect`, the culling scales and every screen<->world mapping the
game does for aim still described a FULL-width view. **`[REPORTED]` a shot went to the right while
the gun pointed forward.** Now exactly ONE place halves it — `set_cur_player_aspect()` in `lv.c` —
so `viSetAspect`, `currentPlayerSetCameraScale()` and the projection read one number, and the
builder halves nothing.

### FAULT 3 — **`bondviewTransformManyPosToViewMatrix` IS NOT A TRANSFORM, AND IT IS NOT IDEMPOTENT.**
> **THE FINDING OF THIS SESSION, AND IT IS AN ENGINE FACT, NOT A STEREO ONE.**

Despite the name it applies no view matrix: it converts each `RenderPosView` from `f32` to the
N64's 16.16 fixed point **IN PLACE, OVER THE SAME MEMORY** (`bondview2.c`,
`matrix_4x4_f32_to_s32`). Run it twice on one array and the second pass reads fixed-point words
back as floats and **saturates every entry at +/-32768**.

**`[MEASURED]` `dlgrab_5249.txt` seq=002525, eye 0** — a 4-vertex alpha-80 ground shadow under a
character:
```
[ -32768 -32768 -32768       0 ]      every entry at the saturation limit,
[      0 -32768 -32768  -32768 ]      m[3][3] = -0.0004
[ -32768 -32768 -32768       0 ]
[      0 -32768 -32768 -0.0004 ]
```
**That is the green wedge across the left eye. `[REPORTED]` by the owner first, and it is what
named the fault:** *"whenever it glitches, it's when passing a character … the character is not
showing in front of me, and instead it's warping everywhere."*

**WHY THE EYE LOOP REACHES IT AND RETAIL DOES NOT.** `model->render_pos` is per-FRAME arena state,
re-pointed at a fresh `dynAllocate` on the OPAQUE pass; the conversion runs on the ALPHA pass
(`chr.c:3538`, guarded by `withalpha != 0`). One rebuild, one conversion. **The eye loop runs the
body twice, and `[MEASURED]` the two eyes do not draw the same thing: 1060 triangle commands and
1940 vertices in eye 0 against 622 and 1355 in eye 1, in the SAME frame, at ZERO separation, with
byte-identical projection matrices.** So a model reaches the alpha pass in one eye without the
opaque pass that rebuilt its matrices.

**THE INSTRUMENT, AND IT COULD HAVE SAID NO.** `GETV_STEREO_MTXGUARD=1` observes and changes
nothing that draws; its own report says *"already-converted=0 means the saturated matrix came from
somewhere else and this diagnosis is WRONG"*. It did not say that:

| arm | result |
|---|---|
| **S2d observe** | **`arrays=183808 already-converted=88520`** — 48%, and **every hit `eye=1`**, the second eye. Values `nan` and `-4.4e28`: fixed-point words read back as floats. |
| **S2e skip** | **`arrays=820471 already-converted=381767 skipped=381767`** — every hit skipped. **`[REPORTED]` *"both eyes showed better"*.** Both viewport lines now print — `ours: x=367.333` AND `ours: x=1280`, `w=912.667` each. Clean exit, `props interpolated 0`. |

**MODE 2 IS A FALSIFIER, NOT A FIX, AND IT MUST NOT SHIP.** It suppresses a symptom. **The repair
is a design decision that has NOT been made: who owns `render_pos` per eye.** The honest statement
of the problem is that the render body is not idempotent, and `258` §1's route assumed it was.

### WHAT IS STILL OPEN AFTER S2e
- **`[REPORTED]` a few artifacts remain**, F9'd as `dlgrab_3917.bmp` / `dlgrab_5595.bmp` — both
  **announced by the log**, so provenance is clean this time (§6, `279` §2). Not yet analysed.
- **THE 1060-vs-622 DIVERGENCE IS NOT EXPLAINED AND IS NOT FIXED.** The two eyes still admit
  different geometry. Fault 3 is a consequence of that divergence, not its cause. **Whatever makes
  a half-width viewport admit a different room set is the next question, and it is the real one.**
- **THE HUD IS DRAWN PER EYE IN FULL-SCREEN COORDINATES** — the ammo counter lands in both halves,
  the clock straddles the seam. Expected: the HUD quad is explicitly NOT in this stage.
- **S3 HAS NOT RUN.** No separation has ever been applied. The gate is untouched.

## §6 — NOT CLAIMED. **READ THIS BEFORE BELIEVING ANY OF THE ABOVE.**

- **NOTHING HAS BEEN BUILT OR RUN.** No claim that the eye loop compiles under the real build
  (`clang`, `-w`), that two views fit the scaled pools, that anything reaches the screen, or that
  the cost is affordable.
- **~~`[INFERRED]` that the render body survives being driven twice in one frame.~~ RETRACTED BY
  §5a's FAULT 3 — IT DOES NOT.** The original text is kept below because the reasoning that led to
  the arm is what caught it: Split-screen drives it up to four times, which is why the shape is credible — but
  it does so for four *players*, and `glassRenderShards`, `bullet_sparks_render_all`,
  `explosionRenderFlyingParticles` and `weaponRenderTracers` sit **outside** the sim gate and have
  not been read for state. **THE IDENTITY ARM IS THE COUNTER-EXAMPLE SEARCH:** `GETV_STEREO=1`
  with `GETV_STEREO_OFFSET=0` renders the body twice with **identical** views, so anything that
  double-advances shows up as particles or tracers running at twice the rate while the two halves
  stay pixel-identical. That arm separates *"driven twice"* from *"driven with two views"*, and it
  runs before the offset is ever applied.
- **THE HEAD QUATERNION AND Z PATHS ARE UNEXERCISED IN-GAME.** With an identity pose the rotation
  is identity and the head offset is zero, so only the harness has ever driven them. Head space is
  defined as +X right, +Y up, −Z forward (the OpenXR convention) and that choice is **not** tested
  by any run in this stage. It is written down so STAGE 7 finds a decision rather than an
  accident.
- **THE VIEW-PLANE CULLING IS ASYMMETRY-BLIND** (§2.4). Inert today on `289`'s measurement; a real
  headset frustum is a different question and belongs to whichever stage brings one.
- **NO COST ESTIMATE IS OFFERED HERE.** The report against `272`'s Cradle baseline — CPU 0.890 ms
  + GPU 0.832 ms against the 11.111 ms period — is an arm in the run sheet, not a prediction in
  this document.

---

## §7 — NOT IN THIS SESSION, AND NOT PLANNED PAST THE FIRST GATE

**Not opened:** OpenXR, head tracking, hand aim, the vignette, the HUD quad, the desktop mirror,
`gevr_xr.c` (`258` STAGE 6). **Aim is STAGE 7 (`P8`); hands and body are STAGE 8.**
**Not reopened:** `getPlayerCount()`, the vanishing props, the mouse turn, or anything in
`00-STATE` §5. **Nothing past the no-headset side-by-side is planned, on purpose.**

## §8 — STILL OWED, CARRIED FORWARD (UNCHANGED BY 292)

All of `277` §9 · `278` §6's INFERRED hoist-1 read · `279` §5's amount arm · `280` §7.3's
black-wall dump · `274` §7's CONTAMINATED gate · `287` ARM 6 the wear pass, **STILL NEVER RUN** ·
`289` R2's missing `dlgrab`. **`292` opened none of these and closed none of them.**
