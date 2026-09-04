# 279 — THE HOLE'S EDGE IS A PORTAL SCISSOR'S `lrx`. NAMED TWICE, AT TWO RESOLUTIONS.

**2026-08-30p. NO BUILD.** Analysis of `278`'s dumps plus ONE new arm (`R1`), run by the session
lead on `277`'s binary. `278` §4 items 1-4 were the task; items 2 and 3 are now MET.

> ## THE ONE-LINE RESULT
> **`[MEASURED]` The artifact's hard vertical edge is the RIGHT edge (`lrx`) of a per-room portal
> `SETSCISSOR` rect, in the game's own canvas space, to `0.00` native pixels — in TWO independent
> frames, from TWO runs, at TWO window resolutions, at two different places in the level.**
> **`dlgrab_2290` (2560x1369): edge at canvas x `151.92`, rect `(4,120)-(152,696)`.**
> **`dlgrab_2913` (3840x2160): edge at canvas x `476.00`, rect `(400,120)-(476,544)`.**
> **The hole lies OUTSIDE the rect in both. `bg.c:622-677` is named. `278` §4.2 and §4.3 are MET.**
> **AND THE GATE IS NOW OPEN: a build may be proposed.**

---

## §1 — WHAT RAN

| arm | log | what it was |
|---|---|---|
| R1 | `run_279_R1_4k_widescreen_off.log` | Streets 29, **`GETV_WINDOW=3840x2160`**, `GETV_WIDESCREEN=0`, `GETV_SIMDIV=1`, 60 Hz. 2 F9 dumps |

`[MEASURED]` self-verified from its own banner, line 8: `[getv] window: 3840x2160 windowed`.
One `game_exit requested` (`262` §5). Dumps: **`dlgrab_2913`, `dlgrab_4283`**, BMPs
`24,883,254 bytes = 54 + 3840x2160x3`. Everything else below is re-analysis of `278`'s files.

## §2 — ►►►► RETRACTION FIRST: `278` §1's DUMP ATTRIBUTION IS WRONG ◄◄◄◄

`278` §1 lists eleven `dlgrab_*` files as "F9 dumps from V1". **`[MEASURED]`, from the logs' own
announcements (`grep -oh "dlgrab_[0-9]*\.txt"` over every `run_278_*.log`):**

| log | dumps it actually announces |
|---|---|
| **`run_278_V1_widescreen_off.log`** | **`2290`, `2849`, `3582` — THREE, and that is all of V1** |
| `run_278_D1_wide169_dlgrab.log` | `2356, 2763, 2915, 3048, 3667, 3932, 4292` — **the widescreen-ON arm, which `278` §1 does not list at all** |
| every other `run_278_*.log` | none |

**`dlgrab_1573/1676/1693/1714` are announced by NO log in the directory.** They are orphans of an
unlogged 22:55 run, and they are **measurably not V1**: zero pillarbox, and an all-black border of
**57 px = 40 canvas rows x 1.42604**, i.e. the game's 4:3 `(4,40)-(1276,920)` play area stretched
to the full window width — widescreen-ON behaviour. **V1's frames carry 367 px side bars and a
171 px border (`= 120 canvas rows`, the game's own 16:9 letterbox).**

**Six of the eleven cannot carry a V1 conclusion.** Same family as `278` §7.3 and `00-STATE` §6's
second-stale-tree: **the artefact was not identified before it was read.** Nothing in `278` §2-§4
is void — those figures came from `2290` and `2763`, which are real — but the ARM LABEL on six
files was wrong, and `278` §8's own trap about accumulating `dlgrab_*` files did not save it.
**A BMP's byte count and the announcing log are the only two admissible IDs. Use both.**

## §3 — STEP 0: THE MAPPING, VALIDATED BEFORE ANYTHING WAS CONCLUDED FROM IT

`gfx_pc.c:4115-4118` maps a `SETSCISSOR` to window pixels:
`x = ulx/4 * ge_scale() + ge_offset_x()`. Stated as predictions BEFORE the measurement, per rule `15`:

| | predicted | `[MEASURED]` 2560x1369 (`2290`) | `[MEASURED]` 3840x2160 (`2913`) |
|---|---|---|---|
| `ge_scale` | `min(W/1280, H/960)` | 1.42604 | 2.25000 |
| side bars | `ge_offset_x` | **367 / 368** (pred 367.35) | **480 / 480** (pred 480.0) |
| game's own 16:9 letterbox | `120 * scale` | **171 / 171** (pred 171.1) | **270 / 270** (pred 270.0) |
| the `(4,...)` play-area inset | canvas 4 | **canvas 3.96** | **canvas 4.00** |

**Four predictions, two resolutions, all met.** The mapping is not an assumption in what follows.
**What it would have printed if pointed at the wrong thing:** any frame whose bars were not
`ge_offset_x` prints `MAPFAIL` and voids its own numbers. None did.

## §4 — ►►►► THE FINDING: THE EDGE IS A RECT'S `lrx` ◄◄◄◄

`[MEASURED]`. An edge counts only where the SAME x carries an above-threshold colour step over a
long CONTIGUOUS run — real geometry drifts off-axis, a scissor edge does not.

**`dlgrab_2290`** (V1, 2560x1369, `GETV_WIDESCREEN=0`): flat `rgb(16,24,32)` sky/stale slab at
window `(584,171)-(695,908)`. Its left edge, run **550 px**:

> **window x `584` -> canvas x `151.92`. The frame's own dump carries `SETSCISSOR (4,120)-(152,696)`.**
> **Its top edge, window y `171` -> canvas y `119.9`, is that rect's `uly` (`120`).**

**`dlgrab_2913`** (R1, 3840x2160, `GETV_WIDESCREEN=0`, a different place in the level): interior
edge, run **367 px**:

> **window x `1551` -> canvas x `476.00`. The frame's own dump carries `SETSCISSOR (400,120)-(476,544)`
> and `(400,228)-(476,500)`. `d = +0.00` native px.**

**In both frames the hole lies OUTSIDE the rect, beyond its `lrx`.** Everything drawn under that
scissor stops dead at the rect's right edge and past it the buffer shows through. **Both matches
are on `lrx`; neither is on `ulx`.** The rects come from **`bg.c:622-677`**, where each room's 2D
bbox is outersected against `screensize` — **game space, with no window term in it at all.**

**`2913`'s full sweep against its own rects: nine interior edges >=250 px, ONE lands within 2 native
px of a scissor x-edge, and it lands within 0.00.** The other eight are 8-178 px away and are
geometry. **`dlgrab_4283`: seven interior edges, ZERO matches** — and `4283` shows no slab.
**The test discriminates. It is not matching everything to everything.**

## §5 — WHAT THE 4K ARM SETTLED, AND WHAT IT DID NOT

**The prediction going in** (`279` session, stated before the run): at 3840x2160 the same rect
would put the same slab's left edge at window x `822` and its top at y `270`, proving resolution
irrelevant. **THE FALSIFIER DID NOT FIRE EITHER WAY: neither 4K dump carries that rect** — the
lead was standing somewhere else — so `822` was never testable. **The prediction is withdrawn as
unrun, not as met.**

**`[REPORTED]`, and it OUTRANKS the analysis (`HANDOVER` §5):** *"only doing it on some of the
edges and definitely not as much."* **Reduced, not gone.**

- **`[MEASURED]` NOT GONE**: `2913` carries a `0.00`-px `lrx` match at 4K with the knob off.
- **`[REPORTED]` REDUCED**: severity is resolution-sensitive.
- **►► THIS CONTRADICTS THE `279` SESSION'S OWN CLAIM THAT "RESOLUTION IS NOT THE VARIABLE".**
  That claim was argued from `2290` being an undistorted uniform 4:3 blit whose hole edge sits at a
  canvas coordinate with no window term in it. **The argument still stands for EXISTENCE and is now
  measured twice. It does NOT account for AMOUNT, and the owner's report is about amount.**
  **`[OPEN]`, unexplained, and it is the next measurement.** Candidate to test, `[INFERRED]` only:
  `ge_scale` 1.426 -> 2.25 changes how many window pixels one native pixel of rect error covers, so
  the same fault could be present-but-subpixel in more places. **Do not write that down as a cause.**

## §6 — THE TWO SYMPTOMS ARE STILL TWO. `278` §4.4 HOLDS, AND IS NOW MEASURED.

`[MEASURED]` across all three genuine V1 frames and both R1 frames: **every slab found is the
SEE-THROUGH class — a flat sky/stale fill, `rgb(16,24,32)` in `2290`.**
**NOT ONE FRAME SHOWS THE BLACK-WALL-OVER-A-WHITE-WALL SYMPTOM** (`[REPORTED]`, standing still,
*"a big black texture covering the wall that is typically white"*). **No measurement joins them.
`263` §1 stands: DO NOT MERGE.** The black-wall symptom has **no dump at all** and needs its own
F9, taken while it is on screen and standing still.

**Frame census** — `[MEASURED]` by looking at every image, not inferred:

| frame | arm | verdict |
|---|---|---|
| `2290` | V1 2560x1369 | **ARTIFACT**, see-through slab, `lrx=152` match |
| `2849` | V1 | clean — the negative control |
| `3582` | V1 | no slab. **A purple smear bottom-left, unrelated shape, LOGGED AND NOT MERGED** |
| `2913` | R1 3840x2160 | **ARTIFACT**, `lrx=476` match |
| `4283` | R1 | no slab, zero rect matches |

## §7 — THE INSTRUMENT FAILED ITS OWN CONTRACT, AND IS DEMOTED ACCORDINGLY

Stated before the run: *"on a clean frame the only long straight edges are the black-border
edges."* **`[MEASURED]` FALSE.** At `THR=10, MINRUN=150` the edge finder printed 40+ long
"axis-aligned" edges on the CLEAN frame `2849` — Streets' alley walls are near-vertical over long
spans. **Contract C failed.**

**So the frame SELECTION in §6 rests on looking at the images, and the edge finder is demoted to
what it can do: measure a coordinate on a frame already identified.** Its longest clean-frame run
was 321 px against `2290`'s 550 px — one frame's margin, not a validated threshold.
**What rescues the §4 result is not the detector, it is the `0.00` px coincidence with a rect the
SAME DUMP carries, twice, and the eight-out-of-nine rejection in `2913`.**

## §8 — TRAPS THIS SESSION PAID FOR

- **►► A LOG'S OWN `dlgrab` ANNOUNCEMENTS ARE THE ONLY ADMISSIBLE PROVENANCE.** File mtime and
  BMP byte count narrow it; they do not name the arm. Six files were mislabelled in `278` on
  timestamp alone. **`grep -oh "dlgrab_[0-9]*\.txt" <log>` per arm, every time.**
- **A FULL-WIDTH FRAME AND A PILLARBOXED FRAME ARE DIFFERENT ARMS, AND THE BLACK BORDER SAYS
  WHICH.** `57 px` border = 40 canvas rows = 4:3 play area stretched = widescreen ON.
  `171 px` = 120 canvas rows = the game's own 16:9 = V1. **Read the border before the picture.**
- **A DETECTOR TUNED ON THE POSITIVE FRAME WILL PASS ITS OWN CONTRACT UNTIL IT MEETS THE
  NEGATIVE ONE.** `2849` was what broke it, and only because it was run. **Run the clean frame.**
- **`GETV_WINDOW=WxH` and `GETV_FULLSCREEN=1` ARE REAL ON WINDOWS** (`port_support.c:104-117`,
  inside `GE_PLATFORM_DESKTOP`) and the `[getv] window:` banner self-verifies the size. Use it.

## §9 — WHAT IS OWED

- **►► THE BUILD GATE IS OPEN. THE RECT IS NAMED.** `bg.c:622-677`, the per-room 2D-bbox
  outersect against `screensize`, whose `lrx` is where the fill stops. **No fix is proposed here
  and none may be inferred from this doc** — what is NOT yet established is WHY the rect is
  narrower than the geometry admitted under it, and `278` §3 proved the ADMISSION is correct, so
  the two facts have to be reconciled before a line is changed.
- **THE AMOUNT-vs-RESOLUTION CONTRADICTION IN §5.** `[REPORTED]` reduced at 4K, `[MEASURED]`
  still present. Unexplained.
- **A DUMP OF THE BLACK-WALL SYMPTOM.** It has none. §6.
- **A DECISION ON `GETV_WIDESCREEN`'s DEFAULT** — unchanged from `278` §9, same shape as `268` §7.
- **ALL THREE OF `277` §9's ITEMS, STILL UNTOUCHED**: the two hoist sites driven, `277` §8's two
  intro-skip audio falsifiers, the `MoveBond` executions-per-second counter.
- **`278` §6's hoist-1 read confirmed or killed.** Still `[INFERRED]`, source-read only.
