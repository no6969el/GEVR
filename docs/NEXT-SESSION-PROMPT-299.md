Read `repo\docs\00-STATE.md` — **§3 OWNER ACTION OUTSTANDING (the top FIVE entries, all new)**, and
**§3 OPEN items 0 and 1, which are the owner's own sentences and outrank everything else in the
file**; then **§4, which retracts four things including one of this session's own**, then **§6 —
five new traps, and three of them are about how a NULL RESULT is read.** Then **`298` §3 and §4 IN
FULL** — §3 is the two-bug split, §4 is the near-plane clamp and the theory it killed. Then
**`RUN-SHEET-297` §7 onward**.

Same rules as always. Bridge reads are not free (`00-STATE` §6): `git log`, `git show` and
`git diff <path>` are safe; `git status` and `git add` are **NOT** (use
`git --no-optional-locks status`), and **a bare `git diff` in the decomp prints ~2,100 lines of CRLF
churn, so always give it a path list** — and pass `--ignore-cr-at-eol`. The build, every run and
every commit are the owner's, on the main PC — **you write and validate OFFLINE, then supply
complete copy-paste command blocks (§7a). Quote a run-sheet block, never paraphrase it.**

---

## ►►►► WHERE THINGS ACTUALLY STAND. READ THIS BEFORE RANKING ANYTHING. ◄◄◄◄

**ARM 3 IS GREEN.** `[MEASURED]` 2026-09-02, R2: the characters and the props are **in both eyes**
and nothing warps. `eyes-rebuilt=1`, `chr`+`obj` accounting for the whole `g_OnScreenPropList` in
every window, no crash, `292`'s doubled pools spent for the first time without overflowing. Per-eye
texture energy **1.00 and 1.02**, against R1's **8.6x and 6.0x** — and R2's per-eye figure equals
R1's GOOD eye, so the starved eye came up rather than the good one coming down.

**`00-STATE` §3 OPEN's three-session entry is ANSWERED.** It is kept in full per rule `2` and marked.

**►► THE ONE THING R2 DOES NOT PROVE, AND DO NOT LET IT DRIFT:** at `GETV_STEREO_OFFSET=0`,
*"each eye built its own world"* and *"eye 1 was handed a copy"* are **indistinguishable by
construction.** R2 proves the world REACHES both halves. **R4 / S3 is what proves per-eye
construction. It is now unblocked and it has never run.**

**NOTHING WAS BUILT, NOTHING WAS COMMITTED TO THE DECOMP, AND NO SOURCE FILE CHANGED IN `298`.**

---

## ►►►►►►►► WHAT TO DO FIRST, AND IT IS NOT THE RUN SHEET ◄◄◄◄◄◄◄◄

**`GETV_NEARCLAMP` A -> B -> A. ONE SHORT RUN, NO BUILD. `298` §4.5.**

Arm F (`GETV_NEARCLAMP=0`) came back clean — the owner's new #1 visible symptom did not appear —
with `NEAR straddle=18439 clamped=0`, so the condition was crossed eighteen thousand times with the
knob provably off. **That is not a masked zero.** But **arm F took NO `dlgrab` grabs**, so the
negative rests on the owner's eyes alone, and **two knobs silently failed to take in `298`**. Same
alley, clamp back to default, confirm the artefact **RETURNS**, F9 both states.

**Until that runs, `298` §4 is `[REPORTED]` plus a census, not `[MEASURED]` cause. Do not write the
fix first.**

---

## ►►►► THE OWNER'S #1 SYMPTOM IS NOW TWO BUGS. DO NOT MERGE THEM AGAIN. ◄◄◄◄

*"As James Bond stands there and breathes, you see the wall move, even goes above the gunshot decal…
whenever you get close to an edge or something is on the corners of your vision, it tends to
disappear… you can see the building splits in the distance as well."* And the sentence that named
the mechanism: **"If I move any little bit, it goes down or goes away. It seems to be in sync with
exactly my movement."**

| symptom | shipping | `ROOMSCISSOR=0` | reading |
|---|---|---|---|
| the split down the distant facade | present | **GONE** | the per-room clip RECTANGLE |
| the wall cut, geometry showing through | present | **STILL PRESENT** | the NEAR-PLANE CLAMP |

`bg.c:445-447` wrote both branches down before either ran and **one of each fired.** Every future arm
must say which of the two it is aimed at.

**THE SECOND ONE'S MECHANISM, AND THE FIX IS NAMED BY THE SOURCE ITSELF:** `gfx_pc.c:3752` clamps
`z` per-vertex **before** interpolation, which tilts the depth gradient across every straddling
triangle; `:3733` says the exact fix is `GL_DEPTH_CLAMP` / `ARB_depth_clamp` / `EXT_depth_clamp`,
*"which is precisely the hardware behaviour"*. **`[MEASURED]`: that extension is referenced in
`gfx_pc.c` comments twice and IMPLEMENTED NOWHERE in `gfx_opengl.c`.**
**►► `GETV_NEARCLAMP=0` IS NOT THE FIX AND MUST NOT SHIP** — GL then discards every triangle poking
through the near plane; F's own census shows the price starting, `all_near` **50 -> 548**.
**►► AND IT IS NOT `281`'s DEAD THEORY** — that was the game-side portal projector
(`sub_GAME_7F0B5528`), killed by `282` §2.1. This is the renderer's triangle submission.

---

## ►►►► THE TWO ONE-LINE FIXES THIS SESSION IDENTIFIED AND DELIBERATELY DID NOT WRITE ◄◄◄◄

**Both are builds. Neither belongs inside an arm. Neither should be started before the A -> B -> A.**

1. **`GL_DEPTH_CLAMP` in the GL backend**, then remove or gate the per-vertex clamp.
2. **`configFiltering`'s missing `over` guard** — `ge_config.c:421/424/428` assign the global
   directly while `put("GETV_POINT_FILTER", ..., over)` on the next line obeys precedence, so the
   per-user cfg beats the environment for that one key. **It voided two owner run cycles**
   (`run_298_tex_filter0.log`, `run_298_tex_point.log`, both bannering `filtering=2` with
   `GETV_FILTERING=0` set). Scope is swept and bounded: only those three lines;
   `configWidescreen` is untouched, so `GETV_WIDESCREEN=0` was honoured everywhere.

---

## ►►►► OWED, AND EACH IS ONE SHORT RUN ◄◄◄◄

- **`RUN-SHEET-297` §7 (R3, pairguard)** — and read its own warning before celebrating its zero:
  with ARM 3 on, the arena's owner is the last eye by construction, so a zero means the fault
  cannot occur, not that ARM 1 works.
- **§8 (R4 / S3, separation).** **Unblocked by R2 passing. The sheet says its block will be spliced
  in FULL rather than delegated once R2 passes — that splice is owed and is the assistant's job.**
  Its added gate: the 1/D law is measured on a frame where the characters and props are present in
  BOTH eyes.
- **§9 (R5, cost).** R5b − R5a is ARM 3's own cost. It does not have to be zero; it has to be known.
- **Arm C's gate.** `GETV_PROPROOMTEST=0` fired its banner but no gun was dropped, so
  *"the gun disappears on the floor"* is still untested and `bg.c:583`'s `getROOMID_isRendered` has
  now survived three arms without being tested once.
- **The filtering question.** Still open, because the arm never took. Until the source fix lands the
  only route is editing `filtering = point` in the per-user cfg, and **the gate is the banner
  reading `filtering=0`.**

**NOT STARTED AND NOT ARM 3's:** `297` §12's mine crash and its two non-equivalent corrections, and
the explosion texture.

---

## ►►►► HOUSEKEEPING THAT COST EVIDENCE IN `298` ◄◄◄◄

- **A re-run overwrote `run_297_R2_rebuild_on.log`.** The BMPs survive; their provenance does not.
  **A re-run of an arm gets a NEW log name.**
- **`dlgrab_NNNN` is named by frame number**, so two arms from the same spot overwrite each other
  silently. Grabs are now filed per arm: `grabs_298_A/` … `_F/`, everything earlier in
  `grabs_pre_298cull/`.

## RUN LOGS `298` PRODUCED

`run_297_R1_rebuild_off.log` · `run_297_R2_rebuild_on.log` (**re-run; the original was overwritten**)
· `run_298_tex_filter0.log` · `run_298_tex_point.log` (**both VOID — the knob never took**) ·
`run_298_cull_A_shipping.log` · `run_298_cull_B_roomscissor_off.log` ·
`run_298_cull_C_proproomtest_off.log` · `run_298_cull_D_samealley_shipping.log` ·
`run_298_order_E.log` · `run_298_nearclamp_off_F.log`
