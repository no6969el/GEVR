# 294 — THE VIEW CANCELS, THE NODE MATRICES **ARE** THE ARENA, AND ALL THREE HAZARDS ARE ONE PAIRING INVARIANT

**Currency: 2026-09-01, session `294`, FIRST PASS. NOTHING HAS BEEN BUILT OR RUN THIS SESSION.**
Everything below is `[MEASURED]` from source reads of `vendor/ge-decomp/src`. **No knob was
changed, no binary was made. S3 has still never run.**

**THIS DOC RETRACTS TWO SECTIONS OF `293` THAT `293` WROTE AS BLOCKERS.** Both were source reads,
both were wrong, and both were wrong in the direction that makes the eye loop look harder than it
is. `293`'s §1, §2, §2.1, §3, §3a and §3c are **untouched and stand**.

---

## §0 — THE HEADLINE

`293` §3b closed with two obstacles standing between the classification and a per-eye build pass:

> **§3b.3** — the tank entry rect is a **view-dependent write into world state**; re-run per eye it
> takes the last eye's view; at `GETV_STEREO_OFFSET=500` that is a **250-unit offset on the
> boarding test**. *"It must be answered before the build pass is written."*
>
> **§3b.4** — `modelFindNodeMtx` returns a pointer into the **MODEL's node rwdata**, which is
> **per MODEL, not per eye**, so **"doubling the arena does not cover this."**

**Both premises are false, and they are false in opposite directions.**

1. **§3b.3's write is not view-dependent.** It is a **round trip**: the same expression multiplies
   by the view matrix and then by that matrix's exact inverse. The eye offset enters and leaves on
   one line. **There was never a 250-unit anything.** §1.
2. **§3b.4's storage is not the rwdata. It IS the `dynAllocate`d arena block.** Doubling the arena
   is *precisely* what covers it, and those matrices were already inside §3b.5's *per eye* bucket.
   §3b.4 named `modelFindNodeMtx` and described its neighbour `modelGetNodeRwData`. §2.
3. **AND THE ITEM `293` §5 LISTED AS UNREAD IS NOW READ.** The readers of `model->render_pos` from
   outside the build are the **shot path**, they are **view-space end to end**, and they are
   **already gated to eye 0** — so the pairing they need holds today, by construction. §3.

**What survives all three is ONE invariant, and it is the same sentence every time:**

> **`g_CurrentPlayer`'s view pair (`field_10CC` = world→view, `viewtoworldmtxf` = view→world) and
> every `model->render_pos` block in the arena are ONE coordinate system with ONE owner. Any code
> that reads either must run while that owner is installed. The eye loop's job is to keep that
> pairing intact — not to decide which eye wins.**

**There is no "which eye wins" decision anywhere in §3b. That framing is retracted.** §4.

---

## §1 — §3b.3 ANSWERED. **THE VIEW CANCELS EXACTLY.**

### 1.1 — THE CHAIN, WITH LINE NUMBERS

`[MEASURED]` `propobj.c`, `objTick`'s build block:

```
:6061   mtxs[0] = W2V ∘ (obj->mtx @ runtime_pos)     matrix_4x4_multiply_homogeneous(camGetWorldToScreenMtxf(), &tempMatrix2, mtxs)
:6337   mtxs[1] = mtxs[0] ∘ turret_local             matrix_4x4_multiply_homogeneous_in_place(&mtxs[0], &mtxs[1])
:6346   sp16C   = V2W ∘ mtxs[1]                      matrix_4x4_multiply_homogeneous(currentPlayerGetViewToWorldMtxf(), &mtxs[1], &sp16C)
:6347   sub_GAME_7F03F540(sp158, &sp16C, &tank_render->rect, &tank_render->collision)
```

So `sp16C = V2W ∘ W2V ∘ objWorld ∘ turretLocal`.

`matrix_4x4_multiply_homogeneous` (`matrixmath.c:161-180`) is plain affine composition
`result = lhs ∘ rhs` — rhs applied first, translation in row 3, last column forced to `(0,0,0,1)`.
**It is associative, so the inner pair is free to cancel.**

### 1.2 — AND THE TWO MATRICES ARE EXACT INVERSES, BUILT FIVE LINES APART FROM THE SAME NUMBERS

`[MEASURED]` `bondview2.c:9005` and `:9010`:

```c
matrix_4x4_set_lookat            ((Mtxf*) g_CurrentPlayer->field_64, cam_pos, cam_look_dir, cam_up);
matrix_4x4_set_basis_and_position((Mtxf*) g_CurrentPlayer->field_68, cam_pos, cam_look_dir, cam_up);
```

`matrixmath.c:586` and `:650` normalise the **same three vectors with character-identical code**
from **identical inputs**, then lay them down transposed relative to each other:

| | `set_lookat` → `field_64` (W2V) | `set_basis_and_position` → `field_68` (V2W) |
|---|---|---|
| basis | `m[0][0]=right_x, m[1][0]=right_y, …` | `m[0][0]=right_x, m[1][0]=up_x, …` (transpose) |
| translation | `m[3][*] = -(eye · axis)` | `m[3][*] = pos` |

**A rigid orthonormal frame, so `Rᵀ = R⁻¹` and `-(p·R)` is the matching translation. These are not
"approximately paired" — one is literally the transpose of the other.** They are installed together
by the only call site that writes either, `bondview2.c:9046-9047`, forty lines after they are built.

### 1.3 — AND `camGetWorldToScreenMtxf` IS MISNAMED. THERE IS NO PROJECTION IN IT.

`[MEASURED]` `bondview.c:832` returns `field_64` — the **bare lookat**. **No projection and no
visibility scale:**

- the projection goes into `field_10E0` via a **separate copy** `spC4` (`bondview2.c:9017-9044`);
- `bgGetLevelVisibilityScale()` is applied to **`spC4.m[0]` only** (`:9038`), never to `field_64`.

**There is nothing in `W2V` but the rigid camera frame, which is why the round trip is clean.**
A name that says "screen" over a matrix that stops at "view" is worth a `00-STATE` §6 line on its
own — it is the reason §3b.3 read as a projection-carrying, non-invertible write.

### 1.4 — SO THE NUMBER §3b.3 FEARED DOES NOT EXIST

At `GETV_STEREO_OFFSET=500`, eye 1 builds `mtxs[0]` with **eye 1's** `W2V` and un-does it with
**eye 1's** `V2W`. **The 500 enters and leaves on the same expression.** `sp16C` is the same world
matrix in both eyes to within float rounding of the round trip — relative ~1e-7 on a coordinate of
a few thousand game units, i.e. **well under a millimetre against a boarding rect.**

**`293` §3b.3's *"a 250-unit offset on the boarding test"* is RETRACTED.**

**AND THE OTHER TWO CALLERS CONFIRM IT BY CONTRAST.** `sub_GAME_7F03F540` is called three times:

| call site | matrix argument | space |
|---|---|---|
| `propobj.c:703` `chrobjCollisionRelated` | `obj->mtx` @ `runtime_pos` | **world, no view at all** |
| `propobj.c:12927` door | `door7F0526EC()` | **world, no view at all** |
| `propobj.c:6347` tank | `V2W ∘ (W2V ∘ world)` | **world, via a round trip** |

**The tank is the only one that goes through view space, and the reason is structural, not
semantic:** `mtxs[0]` is premultiplied by `W2V` *before* the turret locals are appended, so by
`:6346` the code has **no world-space copy of the turret composite to hand** and manufactures one.
**A round trip, not a view dependency.**

### 1.5 — WHAT ACTUALLY SURVIVES, AND IT IS A PAIRING, NOT A DECISION

The cancellation holds **if and only if the `W2V` that built `mtxs[0]` and the `V2W` read at `:6346`
are the same eye's pair.** Both come from `g_CurrentPlayer`, both are installed by one call site,
always together. So:

> **The per-eye build must run inside the eye's own `viSetupCurrentPlayerView` scope. A build
> hoisted out of the eye loop, or one that runs for eye 1 while the struct still carries eye 0's
> pair, takes the FULL separation as error.**

**That is the 500-unit failure `293` §3b.3 feared — it just lives at setup ordering, not at
`:6347`.** Same family as §3c.3: correct exactly once per fresh pairing.

### 1.6 — THE DECISION, AND IT IS CHEAP

`sub_GAME_7F03F540` moves from §3b.5's *once per frame* list to **"may re-run per eye, harmlessly"**.
Re-running it buys nothing, so **leave it once per frame**: fewer moving parts, provably identical
result either way. **No new guard. Nothing is owed here before the build pass.**

---

## §2 — §3b.4 ANSWERED. **THAT STORAGE IS THE ARENA.**

`[MEASURED]` `model.c:669-676`, the whole function:

```c
Mtxf *modelFindNodeMtx(struct Model *model, struct ModelNode *node, s32 arg2) {
    s32 index = modelFindNodeMtxIndex(node, arg2);
    if (index >= 0) { return &model->render_pos[index].pos; }
    return NULL;
}
```

It returns a pointer into **`model->render_pos`** — the exact block from `propobj.c:5991`
(`mtxs = dynAllocate(...); model->render_pos = mtxs;`). Only the **index** comes from rodata
(`Header.MatrixIndex` / `Group.MatrixIDs`, `model.c:631-664`) — **read-only, per-model, and never
written by anything.** `modelFindNodeMtx(model, Switches[3], 0)` is **`&mtxs[MatrixIndex]` under
another name.**

| `293` §3b.4 said | actually |
|---|---|
| "returns a pointer into the **MODEL's node rwdata**" | into the **per-frame arena**, `model->render_pos` |
| "**per MODEL, not per eye** … the last eye wins" | **per allocation** — hence per eye the moment the build allocates per eye |
| "**doubling the arena does not cover this**" | **doubling the arena is exactly what covers it** |

**All three RETRACTED.** The autogun and aircraft sub-part matrices (`:6114`, `:6122`, `:6132`,
`:6290`, `:6299`) are `dynAllocate` + `render_pos` and were **already inside §3b.5's *per eye*
bucket**. **§3b.5's *Undecided* line is now empty.**

### 2.1 — THE CONFLATION, NAMED SO IT IS NOT REPEATED

§3b.4 named `modelFindNodeMtx` and described its **neighbour** `modelGetNodeRwData`
(`model.c:734`), which indexes `Objinst->datas` — allocated once at model instantiation
(`model.c:9012`), **genuinely per-model and persistent.** That is what `:6351` and `:6357` write:

```c
modelGetNodeRwData(model, Switches[7])->Gunfire.visible = (s16) tank_render->is_firing_tank;
modelGetNodeRwData(model, Switches[8])->Switch.visible  = 0;
```

**Two `s16` visibility flags, one derived from world state and one a constant.** `293` §3b.2
already classified them correctly as idempotent. **Last eye writes the same value. No hazard.**
**The two functions sit 65 lines apart in `model.c` and differ by one word in the name.**

---

## §3 — THE READERS TRACE. **`293` §5's "UNREAD" ITEM, NOW READ.**

`293` §5 listed *"whether anything outside the eye loop reads the rwdata matrices of §3b.4"* as
unread. §2 dissolves the rwdata half of that question. **The remaining half — who reads
`model->render_pos` from outside the build — is answered here, and it is more interesting than the
question that prompted it.**

### 3.1 — ONE OF THE THREE CANDIDATES WAS NEVER OUTSIDE THE BUILD

`objecthandler.c:430-662` is the body of **`sub_GAME_7F06B29C`**, and `[MEASURED]` its only callers
are `chr.c:3201`, `:3221`, `:3225` — **inside `chrTick`'s build block**, which `293` §3c.2 already
identifies as the joint-list finaliser — plus `title.c:266`, which has no eye loop.
**Not a reader from outside. Closed.**

### 3.2 — THE REAL READER IS THE SHOT PATH, AND IT IS VIEW-SPACE END TO END

`[MEASURED]` chain:

```
chraiCheckUseHeldItems()                lv.c:932
  chraiCheckUseHeldItem()               chrprop.c:1771
    chraiDefaultWeaponFireHandler()     chrprop.c:1091
      bullet_path_from_screen_center()  gunfire.c:6092   -> shotdata.viewOrigin / viewDir
      projectileFindCollidingProp()     propobj.c:1561
        projectileTestObjectCollisionRecursive()   :1443
          projectileTestObjectCollision()          :1375   <- gated on PROPFLAG_ONSCREEN
            projectileLineTestModel()              :1183
              modelFindNextProjectileHitCandidate()   model.c:6932
                modelTestRayIntersectsNodeBBox()       model.c:6770  -> modelFindNodeMtx -> render_pos
                sub_GAME_7F074CAC()                    model.c:6781  -> modelFindNodeMtx -> render_pos
```

and in parallel `chrTestHit` (`chr.c:3953`) / `chrHandleBulletHit` (`chr.c:4161`), which read
`modelFindNodeMtx(...)->m[3][*]` and subtract `shotdata->viewOrigin` directly (`chr.c:4117-4119`,
`:4285`).

**`projectileFindCollidingProp` takes a WORLD ray and transforms it into view space with the
CURRENT view matrix, at call time** (`propobj.c:1601`, `:1607`):

```c
sp88 = *worldRayStart;  mtx4TransformVecInPlace(camGetWorldToScreenMtxf(), &sp88);
sp7c = normalised_dir;  mtx4RotateVecInPlace   (camGetWorldToScreenMtxf(), sp7c.f);
```

**So the ray's view and the geometry's view must be the same eye.** This is `§1.5`'s pairing again,
with the two halves separated by a much longer distance in the code: the matrices are written in
`objTick`, the ray is transformed in the shot path, and **nothing ties them together except
"whatever `g_CurrentPlayer->field_10CC` points at right now."**

### 3.3 — AND THE SHOT RAY PUTS THE EYE AT THE ORIGIN, LITERALLY

`[MEASURED]` `gunfire.c:6117-6119`:

```c
arg0->x = 0.0f;   arg0->y = 0.0f;   arg0->z = 0.0f;   /* viewOrigin */
```

**`shotdata.viewOrigin` is the origin of view space.** The direction comes from
`g_CurrentPlayer->crosshair_angle` through `transformAndNormalizeByLength2Dto3D`. **The entire
hitscan is defined in the current view's frame with the eye at `(0,0,0)`** and only converted out
to world where world coordinates are needed (`chrprop.c:1161`, `chr.c:4110` — the same
`V2W` round-trip idiom as `§1`).

**THIS IS THE FACT THAT MATTERS FOR VR AND IT IS BIGGER THAN THE EYE LOOP.** "Where the bullet
comes from" is not a gun position in this engine — it is **the camera**, and in stereo "the camera"
is two places. **Naming it; not solving it. It is not a `293` §3b question and must not be merged
into one** (`263` §1).

### 3.4 — AND A NEW FACT THAT STRENGTHENS `293` §3b.5 RATHER THAN THREATENING IT

`[MEASURED]` `propobj.c:1399`:

```c
if (prop->flags & PROPFLAG_ONSCREEN) {          /* precise per-node line test */
    if (projectileLineTestModel(obj, modelRayOrigin, modelRayDir, ...)) { ... }
}                                                /* else: coarse instsize sphere only */
```

**`PROPFLAG_ONSCREEN` does not only decide what is DRAWN. It decides whether a bullet gets a
precise per-node hit test or a bounding-sphere approximation.** That is a **gameplay** consequence
of a **rendering** flag.

**So `293` §3b.5's decision to keep admission and `PROPFLAG_ONSCREEN` *once per frame* now has a
second, independent reason** — run admission per eye and **a prop's hit fidelity would depend on
which eye ran last.** The mission's own point `3` test (*would a 1997 player notice?*) says yes:
shots that pass through a shoulder in one frame and clip a sphere in the next.

**AND THIS TOUCHES `00-STATE` §5's OPEN "VANISHING PROPS" ITEM ONLY BY LOCATION.** `posIsOnScreen`
being load-bearing for more than drawing is a fact about the mono engine; the vanishing props are
a mono symptom; this is a stereo design constraint. **Same function, three questions, and `263` §1
says they do not merge.**

### 3.5 — WHERE IT ALL SITS: THE PAIRING ALREADY HOLDS, AND FOR THE RIGHT REASON

`[MEASURED]` `lv.c`, `258` STAGE 6's eye loop:

```
:908    if (geStereoIsFirstEye() && gePortSimShouldTick()) {
:914        propsTick();                       <- the build + admission, eye 0 only
:932        chraiCheckUseHeldItems();          <- the shot path, eye 0 only
        }
:1035   }   /* end of the eye loop */
```

Both the build and its only outside reader are **inside the same eye-0 gate, downstream of one
`viSetupCurrentPlayerView` (`:875`)**. Within a frame the order is:

> eye 0 setup → eye 0 build → **eye 0 shot path** → eye 0 render → eye 1 setup → *(no build)* →
> eye 1 render → restore

**The ray and the matrices are always both eye 0's. The pairing holds today, by construction.**

**AND SPLIT-SCREEN IS THE EXISTENCE PROOF THAT THIS IS THE MECHANISM, NOT LUCK.** In split-screen
`set_cur_player()` moves `g_CurrentPlayer` per player, so the view pair, the `render_pos` blocks
and the shot ray all belong to the same player automatically. **`258` §1's "split-screen is the
shipped existence proof for stereo's mechanism" is true one level deeper than it was written:
it is the existence proof for the PAIRING, and the pairing is what an eye loop has to reproduce
by hand — because an eye loop keeps `getPlayerCount()` at 1 (`258` §1.5) and therefore gets none
of it for free.**

### 3.6 — THE RESIDUE, AND IT IS A LIVE MISMATCH IN THE CURRENT BUILD

`[MEASURED]` `lv.c:1035-1046`. The eye loop's exit restores the **rectangle**, the **aspect** and
the **camera scales**:

```c
geStereoBeginEye(-1);
set_cur_player_aspect(ge_af);
viSetViewSize(ge_vw, ge_vh);
viSetViewPosition(ge_vl, ge_vt);
viSetAspect(g_CurrentPlayer->aspect);
```

**It does NOT restore the view matrix pair.** `field_10CC` / `viewtoworldmtxf` are written only by
`viSetupCurrentPlayerView` → `bondview2.c:9046-9047`, which is not re-run after the loop.

> **SO WHEN `lvlRender` RETURNS, `camGetWorldToScreenMtxf()` STILL RETURNS THE LAST EYE'S MATRIX,
> WHILE EVERY `model->render_pos` IN THE ARENA HOLDS EYE 0's. THEY ARE ALREADY MISMATCHED TODAY,
> IN THE SHIPPING STEREO PATH, FOR THE WHOLE GAP BETWEEN FRAMES.**

**Whether anything reads either in that gap is NOT established here** — `[MEASURED]` there are
**69 call sites** of the two accessors across **13 files** — `camGetWorldToScreenMtxf()` 31 +
`currentPlayerGetViewToWorldMtxf()` 38 (`propobj.c` 19, `gunfire.c` 9, `gun.c` 8, `chr.c` 6,
`explosion.c` 5, `bg.c` 4, `chrprop.c` 4, `bondview2.c` 4, `chraction.c` 3, `sky.c` 3,
`glass2.c` 2, `bondhead.c` 1, `bgfog.c` 1) — and **an exhaustive
inside/outside trace of 69 sites is exactly the kind of unbounded source read this project has
been burned by** (`288` §3's *"the load-bearing claim underneath all of it is a SOURCE READ, which
is not a measurement"*). **§5 proposes the instrument that answers it by measurement instead.**

**The cheap mitigation is one line and is worth writing regardless of the answer: restore the view
pair at the end of the eye loop the same way the rectangle is restored.** It cannot be wrong, and
it removes the whole class.

---

## §4 — THE ONE INVARIANT, AND IT REPLACES THREE SEPARATE WORRIES

`293` §3b.3, `293` §3b.4 and the readers question were written as three problems. **They are one:**

> **THE VIEW PAIR AND THE ARENA ARE ONE COORDINATE SYSTEM WITH ONE OWNER.**
> `g_CurrentPlayer->field_10CC` (W2V), `g_CurrentPlayer->viewtoworldmtxf` (V2W) and every
> `model->render_pos` block written under them belong to whichever eye was installed when they were
> written. **Any read of any of them must happen while that same eye is installed.** Round trips
> through the pair (`§1`) cancel; rays transformed into the pair (`§3.2`) match; matrices allocated
> under the pair (`§2`) are per-eye for free. **Break the pairing and all three fail at once, by
> the full inter-eye separation.**

**Combined with `293` §3c.3 — *"the build must re-run as a WHOLE per eye; a partial re-run
re-transforms"* — that is the complete design constraint on the build pass.** Two sentences, both
`[MEASURED]`, and neither is a "which eye wins" choice. **There is no such choice in `293` §3b.**

**`293` §3b.5's shape, corrected:**

- **Per eye:** `dynAllocate` + `model->render_pos`; every
  `matrix_4x4_multiply_homogeneous*(camGetWorldToScreenMtxf(), …)`; `subcalcmatrices`;
  `modelUpdateRelationsQuick`; `prop->zDepth`; **and the node matrices of old §3b.4, which are the
  same arena block.**
- **Once per frame:** admission and `PROPFLAG_ONSCREEN` (**now for two reasons — §3.4**);
  everything in §3b.1; `chrobjWeaponTick`; both child walks; the portal toggles; everything from
  `:6395`; **`flinchcnt` hoisted out per §3c.1**; **the whole shot path.**
- **Free either way:** `sub_GAME_7F03F540` (§1.6) — left once per frame by choice.
- **Undecided:** *(empty)*.

---

## §5 — THE INSTRUMENT THIS WANTS, AND IT IS NOT BUILT

**Do not answer §3.6 by reading 53 call sites. Stamp the pairing and let it assert.** `[INFERRED]`
shape, not built, not costed:

1. Stamp an eye index beside the view pair when `currentPlayerSetMatrix10CC` /
   `currentPlayerSetViewToWorldMtxf` install it (`bondview.c:823`, `:856` — one `s32`).
2. Stamp the same index into each `dynAllocate`d `render_pos` block at `propobj.c:5991` and
   `chr.c:2889`. **The arena already proves allocation order** (`293` §2.1, `00-STATE` §7).
3. Under `GETV_STEREO_PAIRGUARD`, compare the two on every `modelFindNodeMtx` and on entry to
   `projectileFindCollidingProp`; log and count mismatches. **Inert when the knob is off.**

**Its falsifier is built in and must be run** (rule `15`): with stereo OFF it must report **zero**
mismatches, and with the current build plus a deliberate read after `lvlRender` it must report
**non-zero** — a guard that cannot fail on the negative frame is `279` §7 again.

**And the arithmetic falsifier for §1, when a build exists:** print `sp16C.m[3][*]` for both eyes at
`GETV_STEREO_OFFSET=500` and assert the inter-eye delta is `< 1e-2`. **If it prints ~250, the
pairing invariant of §1.5 was violated — which is exactly what that number now diagnoses.**

---

## §6 — WHAT THIS RETRACTS

- **`293` §3b.3 in full** — *"a VIEW-DEPENDENT WRITE INTO WORLD STATE"*, *"re-run per eye it takes
  the last eye's view"*, *"a 250-unit offset on the boarding test"*, and *"it is a correctness
  question … it must be answered before the build pass is written"*. **RETRACTED.** The view
  cancels; the write is view-independent; nothing is owed before the build pass. **§1.**
  **The sentence that survives is the pairing requirement of §1.5, which §3b.3 did not state.**
- **`293` §3b.4 in full** — *"returns a pointer into the MODEL's node rwdata"*, *"per MODEL, not per
  eye"*, *"the last eye wins"*, *"doubling the arena does not cover this"*, and *"whether anything
  outside the loop reads it is unread and is the next item after §3b.3"*. **RETRACTED on every
  clause.** It is the arena. **§2.**
- **`293` §3b.5's *"Undecided: the rwdata matrices of 3b.4"*.** **CLOSED — there is nothing there.**
- **`293` §5's *"whether anything outside the eye loop reads the rwdata matrices of §3b.4 is
  UNREAD"*.** **SUPERSEDED**: the rwdata half is void (§2), the `render_pos` half is traced (§3),
  and what remains is the bounded, measurable question of §3.6.
- **The "which eye wins" framing wherever it appears in `293` §3b.** There is no such decision.
- **Nothing else.** `293` §1, §2, §2.1, §2.2, §3, §3a, §3b.1, §3b.2 and all of §3c **stand
  unchanged.** `292`'s FAULT 1 and FAULT 2 stand. The pool sizing stands.

## §7 — NOT CLAIMED

- **NOTHING WAS BUILT OR RUN.** No claim that any of this compiles. **S3 has still never run**, and
  nothing here changes the gate in `RUN-SHEET-292` §5.
- **§3.6 IS NOT RESOLVED.** That the pair is left stale after the eye loop is `[MEASURED]`; that
  **something reads it in that window is NOT established** and must not be cited as if it were.
  **The 53-call-site trace was deliberately not attempted** — §5 is the reason.
- **THE FLOAT RESIDUAL OF §1.4 IS AN ESTIMATE FROM `f32` PRECISION, NOT A MEASUREMENT.** No
  build has printed it. The §5 arithmetic falsifier is what would.
- **§3.3'S VR CONSEQUENCE — that the hitscan originates at the camera, not the gun — IS NAMED, NOT
  ANALYSED.** It is not a `293` §3b question and is not merged into one (`263` §1).
- **§3.4 TOUCHES `00-STATE` §5's VANISHING PROPS AND `278` §5's UNENTERABLE TANK BY LOCATION
  ONLY.** Three questions, one function. **They do not merge** (`263` §1) — and `293` §3b.3 said
  the same thing about the tank, which remains correct even though the rest of §3b.3 does not.
- **`matrix_4x4_multiply_homogeneous`'s associativity is asserted from its source, not proved over
  floats.** Exact in ℝ; the residual is §1.4's estimate.

## §8 — STILL OWED, CARRIED FORWARD

All of `293` §6 unchanged — `277` §9 · `278` §6's INFERRED hoist-1 read · `279` §5's amount arm ·
`280` §7.3's black-wall dump · `274` §7's CONTAMINATED gate · `287` ARM 6 the wear pass, **STILL
NEVER RUN** · `289` R2's missing `dlgrab` · `GETV_ROOMSCISSOR=0` as a default. **`294` opened none
of these and closed none of them.**

**Newly owed by this doc:** §3.6's window question (instrument in §5, not built) · the one-line
view-pair restore at `lv.c:1042` (not written) · `293` §5's `GETV_CHR_DEBUG` per-eye tagging,
**still the right next measurement for the drop site and still not on the critical path.**
