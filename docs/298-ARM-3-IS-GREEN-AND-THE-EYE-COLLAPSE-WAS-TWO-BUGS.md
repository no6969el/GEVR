# `298` — **ARM 3 IS GREEN. THE OWNER'S SENTENCE IS ANSWERED. AND THE SYMPTOM UNDERNEATH IT WAS TWO BUGS, NOT ONE.**

**`[MEASURED]` 2026-09-02.** Seven runs, no build, no source change. Every run is the owner's on the
main PC; every read below is offline, on the bridge.

Run logs, all in `getv/build-windows`:
`run_297_R1_rebuild_off.log` · `run_297_R2_rebuild_on.log` · `run_298_tex_filter0.log` ·
`run_298_tex_point.log` · `run_298_cull_A_shipping.log` · `run_298_cull_B_roomscissor_off.log` ·
`run_298_cull_C_proproomtest_off.log` · `run_298_cull_D_samealley_shipping.log` ·
`run_298_order_E.log` · `run_298_nearclamp_off_F.log`
Grabs are filed per arm: `grabs_298_A/`, `_B/`, `_C/`, `_D/`, `_E/`, `_F/`, and everything that
predates them in `grabs_pre_298cull/`.

---

## §0 — THE HEADLINE, AND IT IS THE OWNER'S SENTENCE

**`00-STATE` §3 OPEN item 0 — *"the people, the characters and the props are not in the right eye at
all, and what does draw warps"* — IS ANSWERED BY A RUN.** R2, `GETV_STEREO_REBUILD=1`, the first
frame ARM 3 has ever rendered:

**THE CHARACTERS AND THE PROPS ARE IN BOTH EYES. NOTHING WARPS. IT DOES NOT CRASH.**

Reported after `292`, `293` and `295`. Carried for three sessions as *"the eye-1 model collapse"*.
Gone.

**AND THE GATE'S OWN LIMIT, STATED HERE SO NOBODY OVERSTATES IT LATER: at `GETV_STEREO_OFFSET=0`
"each eye built its own world" and "eye 1 was handed a copy" are INDISTINGUISHABLE BY
CONSTRUCTION.** R2 proves the world reaches both halves. It does not prove per-eye construction.
**That is `RUN-SHEET-297` §8 / R4 (S3, the separation gate), and it is now unblocked and still
unrun.**

---

## §1 — R1 AND R2, AND THE NUMBERS THAT SCORE THEM

### 1.1 — The census accounts for the whole list

`[getv][stereo][rebuild] SUMMARY`, `run_297_R2_rebuild_on.log`:

| window | list | chr | obj | skipped | chr+obj vs list |
|---|---|---|---|---|---|
| 600 | 11 | 2 | 9 | 0 | **11 = 11** |
| 1200 | 1 | 0 | 0 | 1 | 1 skipped, accounted |
| 1800 | 3 | 2 | 1 | 0 | **3 = 3** |
| 2400 | 7 | 5 | 2 | 0 | **7 = 7** |
| 3000 | 7 | 5 | 2 | 0 | **7 = 7** |
| 3600 | 7 | 5 | 2 | 0 | **7 = 7** |

`eyes-rebuilt=1` in every window. **The driver is not admitting a subset — it walks
`g_OnScreenPropList` and takes all of it**, and the one `skipped` is the whole of its window's list.
`RUN-SHEET-297` §6 gate 3 asked only for `chr + obj > 0`; the balancing sum is stronger than the
gate and is recorded because it is free.

### 1.2 — THE TWO EYES CARRY THE SAME WORLD, AND THE CONTROL IS THE GOOD EYE

Per-half mean horizontal gradient (texture energy), taken on the play area either side of the seam
`stereo_disparity.py` reports at x=1279. **This instrument is this session's own; its limit is that
it measures how much is drawn, not what.**

| grab | LEFT half (eye 0) | RIGHT half (eye 1) | ratio |
|---|---|---|---|
| `2451` R1 rebuild OFF | **0.415** | 3.578 | **8.6x** |
| `2754` R1 rebuild OFF | **0.589** | 3.557 | **6.0x** |
| `2568` R2 rebuild ON | 3.631 | 3.647 | **1.00** |
| `3056` R2 rebuild ON | 3.553 | 3.631 | **1.02** |

**►► THE CONTROL THAT MAKES IT A RESULT: R2's per-eye figure (~3.6) EQUALS R1's POPULATED eye
(~3.57).** ARM 3 did not level the two halves by degrading the good one; it brought the starved one
up to it. A fix that broke both eyes equally would also read 1.00.

### 1.3 — R1 IS NEGATIVE IN THE WAY IT WAS SUPPOSED TO BE, WITH ONE DEFECT IN THE SHEET

`eyes-rebuilt=-1 chr=0 obj=0 skipped=0 | enabled=0`. **`RUN-SHEET-297` §5 gate 2 predicted
`eyes-rebuilt=0`.** `-1` is the never-assigned sentinel and is arguably the better value — it
separates *the driver did not run* from *it ran and rebuilt zero eyes* — but **the sheet's stated
string is wrong and `297` §10's falsifier ("R1's census reads anything other than `chr=0 obj=0`")
did not fire.** Recorded as a defect in a stated outcome, not a finding about the code.

### 1.4 — NO CRASH IN EITHER ARM, AND THE ARENA HELD

`grep -n "EXCEPTION"` returns nothing in R1 or R2; both end `game_exit requested`. **`292` §1 doubled
both pools for exactly this moment and until R2 the second eye allocated nothing, so the x2 had
never been spent.** It has now been spent and it did not overflow. `gfx=245760 vtx=81920`.

---

## §2 — THE DISPARITY GATE COULD NOT BE SCORED AS WRITTEN, AND R1'S `dx` WAS THE CORRELATOR'S WALL

### 2.1 — `dx` TRACKS THE SEARCH BOUND. IT IS NOT A MEASUREMENT.

`00-STATE` §6 already warns that a pegged `dx` is the correlator's boundary. **The built-in detector
never fired, because it tests `abs(dx) >= search` while `measure()`'s own `lo`/`hi` clipping
(`stereo_disparity.py:90-91`) makes the reachable bound `search - 1`.** Swept:

| `--search` | `dlgrab_2451` (R1) | `dlgrab_2568` (R2) |
|---|---|---|
| 200 | `dx=+199` `mad_best 15.217` | `dx=+1` `mad_best 0.825` |
| 300 | `dx=+229` `mad_best 14.722` | `dx=+1` `mad_best 0.825` |
| 500 | `dx=-499` `mad_best 7.346` | `dx=+1` `mad_best 0.825` |
| 800 | `dx=-799` `mad_best 0.787` | `dx=+1` `mad_best 0.825` |

**R1's `dx` is whatever the window allows and `mad_best` "improves" to 0.787 as the overlap shrinks
to nothing.** R2's answer does not move across a 4x change of window. **AN ANSWER THAT IS INVARIANT
UNDER ITS OWN INSTRUMENT'S FREE PARAMETER IS A MEASUREMENT; ONE THAT TRACKS THE PARAMETER IS THE
PARAMETER.** The off-by-one in the peg detector is a live defect in the script.

### 2.2 — GATE R2 ITEM 6 IS UNSCOREABLE AS THE SHEET WRITES IT

`stereo_disparity.py` emits a verdict only when handed `--predicted-frac` or `--predicted-px`;
`RUN-SHEET-297` §6's invocation passes neither, so it prints
`VERDICT: measured only -- no PREDICTION supplied, so this is not a gate.` **And the sheet's stated
pass string is unreachable on this frame anyway**: `mad_zero 5.182 -> mad_best 0.825` at a
**one-pixel** shift is meaningfully better, so the `CANNOT ANSWER -- the two halves match no better
shifted than unshifted` branch cannot be taken. Content was never in doubt — texture energy 3.606
and 3.570 against the 0.15 floor, so `297` §0's blank-frame trap did not bite.

**`[INFERRED]`, NOT MEASURED — the one pixel is viewport rounding.** Eye 0 is
`ours: x=367.333 w=912.667`, eye 1 `x=1280` on an integer boundary, so the halves sample on a
different sub-pixel phase. **FREE FALSIFIER: a `GETV_WINDOW` whose eye half is an exact integer
should drive `dx` to 0.** Unrun.

---

## §3 — **THE SYMPTOM UNDER THE EYE COLLAPSE WAS TWO BUGS, AND ONE FALSIFIER SEPARATED THEM.**

The owner `[REPORTED]` it in their own words, and per §7b2 that is the item:

> *"As James Bond stands there and breathes, you see the wall move, even goes above the gunshot
> decal. Whenever you get close to an edge or something is on the corners of your vision, it tends
> to disappear. You can see the building splits in the distance as well. The gun disappears on the
> floor."*
>
> *"If I move any little bit, it goes down or goes away. It seems to be in sync with exactly my
> movement."*

Four arms, all mono, all no-build. **A** shipping · **B** `GETV_ROOMSCISSOR=0` · **C**
`GETV_PROPROOMTEST=0` · **D** shipping again, at the alley B was grabbed in.
**Both falsifier banners fired, so neither arm is a silent default**; no `EXCEPTION` in any of the
four; no `[getv][stereo]` line in any of them (rule `48`).

| symptom | A / D shipping | B `ROOMSCISSOR=0` | reading |
|---|---|---|---|
| the split down the distant facade | present | **GONE** (`[REPORTED]`) | **the per-room clip RECTANGLE** |
| the wall cut with geometry showing through | present | **STILL PRESENT** | **NOT the rectangle** |

**`bg.c:445-447` wrote both branches down before either was run, and one of each fired:**
*holes GONE -> the rectangles are the cause, and a real fix has to widen them correctly* ·
*holes STAY -> the rectangles are innocent, every 0.00-px edge match is a coincidence of position,
and the cause is that no room owns those pixels at all.*

**►► THESE HAVE BEEN ONE COMPLAINT SINCE `278`. THEY ARE TWO MECHANISMS AND THEY MUST NOT BE
MERGED AGAIN.** `278` §7.1 exonerated room ADMISSION and explicitly left the per-room RECTANGLE
uncleared; `282`, `283` and `284` then killed three theories in that family. **The rectangle is now
implicated by its own falsifier for the FIRST symptom only.**

**►► AND ARM D IS WHY THE SECOND ONE IS REAL.** It was grabbed in arm B, whose documented cost
(`bg.c:448-451`) is *"rooms will overdraw each other... walls through walls, rooms visible where
they should not be"* — so it could have been the falsifier's receipt. **D re-ran the same alley at
`ROOMSCISSOR=1 PROPROOMTEST=1`, verified by the ABSENCE of both banners, and it reproduces.**
`grabs_298_D/dlgrab_3851`, `_6907`, `_7930`.

**STILL OWED FROM THIS BLOCK: ARM C's GATE WAS NEVER EXERCISED.** The knob fired, but no gun was
dropped, so *"the gun disappears on the floor"* is untested and `bg.c:583`'s
`getROOMID_isRendered(roomnum)` — *"NEITHER `GETV_ROOMSCISSOR` NOR `GETV_PROPCULLBOX` TOUCHES IT. It
has survived two arms without being tested once"* — is still a live, untested candidate.

---

## §4 — **THE SECOND BUG IS THE NEAR-PLANE DEPTH CLAMP. AND MY FIRST CANDIDATE FOR IT IS DEAD.**

### 4.1 — RETRACTED BEFORE IT WAS BELIEVED: THE DRAW-ORDER THEORY. MINE.

Proposed this session: a collapsed painter's order would track the camera and be indifferent to the
scissor. **`GETV_ORDER`'s own stated null is *"if every room lands in bucket 0 there is no ordering
at all"*. `[MEASURED]` over all 16,412 frame dumps in `run_298_order_E.log`:**

```
[0..2] 7156   [0..6] 2943   [0..4] 2260   [0..7] 1838
[0..5] 1279   [0..3]  592   [0..1]  128   [0..0]  216
```

**All 216 of the `[0..0]` frames have `rooms=1`, which is trivially ordered. Every multi-room frame
has a real bucket span.** The ordering is intact. **The theory was pre-registered and it measured
false.** It is in §4 of `00-STATE`.

### 4.2 — WHAT THE CENSUS SAYS INSTEAD

`[getv][far]`, cumulative, last line of each run:

| | `NEAR all_near(hw-DRAWS)` | `NEAR straddle` | `NEAR clamped` |
|---|---|---|---|
| **E**, clamp ON (default) | 50 | 22,635 | **22,685** |
| **F**, `GETV_NEARCLAMP=0` | 548 | **18,439** | **0** |

**In E, `clamped` equals `straddle`: every straddling triangle is clamped, 100%, not a subset.**

**►►►► AND F IS NOT A MASKED ZERO, WHICH IS THE ONLY THING THAT COULD HAVE VOIDED IT.** `289` R2's
rule: *a zero downstream of a test that rejects most of its input is a masked zero, not an
exoneration.* Here the upstream condition is `straddle`, and it reads **18,439** — the near plane
was crossed eighteen thousand times with the clamp provably off. **`[REPORTED]` by the owner on that
run: the artefact did not appear.**

### 4.3 — THE MECHANISM, IN THE CLAMP'S OWN COMMENT

`gfx_pc.c:3752`:

```c
if (nc) {
    for (int i = 0; i < 3; i++) {
        float w = v_arr[i]->w;
        if (w > 0.0f && v_arr[i]->z < -w) { v_arr[i]->z = -w; moved = 1; }
    }
    if (moved) ge_far.tri_near_clamped++;
}
```

**It moves `z` and nothing else** — `x`, `y` and `w` are untouched, deliberately, because hardware
does not move the footprint either. But `gfx_pc.c:3733` says what that costs:

> *Per-vertex, so a triangle straddling the near plane has its interpolated depth shifted within the
> first fraction of the range. The exact fix is `GL_DEPTH_CLAMP` / `ARB_depth_clamp` /
> `EXT_depth_clamp`, which clamps after interpolation and disables z clipping outright, which is
> precisely the hardware behaviour.*

Clamping per-vertex **before** interpolation tilts the depth gradient across the whole triangle, so
whether it wins or loses the depth test against its neighbours is recomputed from the camera every
frame. **That predicts all three of the owner's observations without adjustment: only near the
camera, only at edges and corners, and in exact sync with movement.** And it is vertex-level, which
is why `GETV_ROOMSCISSOR` never touched it.

**►► DO NOT CONFUSE THIS WITH A DEAD THEORY.** `00-STATE` §4 records `281`'s *"the projector DROPS
behind-camera verts instead of clipping them"* as FALSE, killed by `282` §2.1 — **that was
`sub_GAME_7F0B5528`, the portal-box projector in the GAME code.** This is `gfx_pc.c`, triangle
submission in the RENDERER. Different file, different layer. The resemblance is close enough to
mislead and is named here for that reason.

### 4.4 — **`GETV_NEARCLAMP=0` IS NOT THE FIX AND MUST NOT SHIP**

Without the clamp, GL clips `-w <= z <= w` unconditionally and **every triangle poking through the
near plane is DISCARDED** where hardware would rasterise it with depth clamped. The price is already
visible in F's own census: **`all_near(hw-DRAWS)` 50 -> 548.** The owner was not looking for missing
near geometry and would not have noticed it.

**THE FIX IS THE ONE THE SOURCE ALREADY NAMES, AND IT IS UNWRITTEN.** `[MEASURED]`:
`GL_DEPTH_CLAMP` appears in `gfx_pc.c` comments at `:3644` and `:3734` and **is not implemented
anywhere in `gfx_opengl.c`.** It is a backend change and therefore a BUILD.

### 4.5 — WHAT F DOES NOT ESTABLISH

**F took NO `dlgrab` grabs** — the log announces none — so the negative rests entirely on the
owner's eyes. Two knobs have silently failed to take in this session already (§5). **A -> B -> A is
owed: same alley, `GETV_NEARCLAMP` back to default, confirm the artefact RETURNS.** Until that runs,
this is `[REPORTED]` plus a census, not `[MEASURED]` cause.

---

## §5 — **`configFiltering` BREAKS `ge_config.c`'s OWN DOCUMENTED PRECEDENCE. ONE KEY WIDE. IT VOIDED TWO ARMS.**

`ge_config.c` states its contract at `:15-19` and again at `:1067` — **CLI > environment > config
file > defaults** — and delivers it by routing every key through `put()` -> `setenv(name, value,
over)` with `over = 0` on the file pass (`:1284`: *"Pass 2 - the file, with overwrite=0 so the
environment always wins"*).

**`key_filtering()` is the exception. It writes the global DIRECTLY, with no `over` guard:**

```c
static void key_filtering(const char *v, int over)
{
    ...
    } else if (strcmp(v, "three-point") == 0 || ... ) {
        configFiltering = 2;                      /* :428 -- unconditional */
        put("GETV_POINT_FILTER", "0", over);      /*      -- this one obeys precedence */
    }
}
```

`port_support.c:185`'s constructor reads `GETV_FILTERING` before `main()`; the config pass then
stamps `configFiltering` back. **`[MEASURED]`: `run_298_tex_filter0.log` and `run_298_tex_point.log`
both banner `filtering=2` with `GETV_FILTERING=0` set in the environment.** Two owner run cycles
spent measuring the default.

**SCOPE, SWEPT AND BOUNDED: `grep` for direct `config*` assignment in `ge_config.c` returns ONLY
those three lines inside `key_filtering`.** `configWidescreen` is never touched there, so
**`GETV_WIDESCREEN=0` was honoured in every block this session, R1's and R2's included.**

**THE FIX IS ONE LINE AND IT IS NOT WRITTEN**: guard the three `configFiltering` writes on `over`,
or have the constructor re-assert after the config pass. **This is the `GETV_SLOTFREE` shape
(`00-STATE` §3, `262` §2) — same file, same "the per-user cfg wins and the block silently gets the
default", same class of wasted cycle.**

**AND THE QUESTION IT WAS ASKED FOR IS STILL OPEN.** The blur on near surfaces — the railing at
`1346`, the brick at `12010` — measures **texture energy 0.029 against 4.467** for the street in the
same frame, a factor of 154, while the same brick renders crisply where the wall recedes in the same
crop. **Same texture, two distances, one behaving, third instance.** `[INFERRED]` magnification of a
low-resolution texture at 8x the N64's pixel count with three-point filtering; **UNTESTED**, because
the arm never took.

---

## §6 — TWO HOUSEKEEPING FINDINGS THAT COST REAL EVIDENCE

- **A RE-RUN OVERWROTE `run_297_R2_rebuild_on.log`.** The 14 MB log that announced `dlgrab_2568`
  and `_3056` was replaced by a 5.8 MB re-run announcing `1192`/`1346`. **The BMPs and §1.2's
  measurements survive; their provenance cannot be re-derived**, and `00-STATE` §6 makes a log's own
  `dlgrab` announcements the only admissible provenance. **A re-run of an arm gets a NEW log name.**
- **`dlgrab_NNNN` COLLIDES ACROSS ARMS BY CONSTRUCTION.** The name is the frame number, so two arms
  run from the same spot overwrite each other's grabs silently. 109 pairs had accumulated in
  `build-windows` told apart only by timestamp. **Every arm now moves its own grabs into
  `grabs_298_<ARM>/` as the last step of its block**, and the pre-existing pile is in
  `grabs_pre_298cull/`.

---

## §7 — WHAT THIS SESSION DELIBERATELY DID NOT DO

Nothing was built, nothing was reverted, and **no source file was changed.** Both one-line fixes
this session identified — `configFiltering`'s missing `over` guard and `GL_DEPTH_CLAMP` in the GL
backend — are named, not written. Neither should be folded into an arm.

Also untouched: `RUN-SHEET-297` §7 (R3, pairguard), §8 (R4/S3, now unblocked by R2 passing), §9
(R5, cost); `297` §12's mine crash and its two non-equivalent corrections; and the explosion
texture.

---

## §8 — FALSIFIERS FOR THE NEXT SESSION, STATED BEFORE THEY RUN (rule `15`)

1. **A -> B -> A on `GETV_NEARCLAMP` does NOT bring the artefact back.** Then the clamp is not the
   mechanism and §4 is `[REPORTED]` coincidence. This is the first thing to run.
2. **`GL_DEPTH_CLAMP` enabled in the backend does not change the artefact.** Then the depth-gradient
   reading of `gfx_pc.c:3733` is wrong even though the knob moved it.
3. **`GETV_PROPROOMTEST=0` does not keep the floor gun visible.** `getROOMID_isRendered` is
   exonerated and the disappearing props are a fourth thing.
4. **A `GETV_WINDOW` with an integer eye half does not drive R2's `dx` to 0.** Then §2.2's
   viewport-rounding reading is wrong and the 1 px is something else.
5. **R4/S3's 1/D law fails on a frame where both eyes are populated.** Then R2's green picture is
   eye 1 replaying a copy, and §0's stated limit was the real story.
