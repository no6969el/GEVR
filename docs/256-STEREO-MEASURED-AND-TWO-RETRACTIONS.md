# 256 — 60 PROJECTION LOADS A FRAME, AND TWO CLOSED DOCUMENTS REOPEN

**2026-08-29. Docs run to `256`. NEXT DOC = `257`.**

> # ►►►►►► **`255` §4 STEP 1 IS ANSWERED. AND `237` §1 IS RETRACTED — THE FOLDER
> # FAULT SURVIVED A BLANK EEPROM.** ◄◄◄◄◄◄
>
> **Three measurements, two of them retractions of documents that were closed.
> All three came from runs the owner made tonight; not one needed a new idea,
> only an instrument that could fail.**

---

## §1 — THE FIRST STEP-1 RUN COULD NOT HAVE ANSWERED ITS QUESTION

`[MEASURED]` `run_mtx.log`: all 40 `PROJECTION LOAD` lines fall between log lines
220 and 468 — **frame 0 to frame 61 of 5,461.** The probe was asleep for every
gameplay frame in the run.

`[READ]` `gfx_pc.c:2136`, as it stood:

```c
if (mt && mt_n < 40 && (parameters & G_MTX_PROJECTION)) {
```

Two properties, and between them they decide the outcome: a hard cap of **40**,
and **no `ge_probe_after_ok()` gate** — which the `GETV_SKINTRACE` probe ten lines
below it does have, and which seven other probes in the same file use. So the
budget was spent during boot and the front end.

> **`49`'s warning, restated because this is a second instance: an instrument that
> cannot be pointed at the moment in question is not an instrument for that
> question.** The old probe also printed four matrix elements and no context, so
> `255` §4's second half — *"whether the world pass is distinguishable from
> HUD/menu passes at that site"* — **could not have been answered on any build.**
> It would have printed the same thing on a working one.

**What the 40 lines do establish, and it is kept:** every one is a `LOAD`, none a
`MUL`, none `+PUSH`; all carry an identical matrix with `m23=-1, m33=0`, i.e.
`guPerspective`'s shape, solving to **near 100, far ≈ 10,007**. That is the front
end's projection, and it is not the world's (§2).

### §1.1 — THE PROBE, REBUILT

Three changes, all so the **same** probe can answer step 1:

1. `ge_probe_after_ok()` now gates it — `GETV_PROBE_AFTER` already existed.
2. The cap scales with the env value: `GETV_MTXTRACE=N` → `N*200`.
3. The line carries the frame, the viewport, the scissor, and **classifies** the
   matrix: `PERSP` (`m23=-1, m33=0`), `ORTHO` (`m23=0, m33=1`), or `OTHER`.

---

## §2 — `[MEASURED]` 60 PROJECTION LOADS PER FRAME. 36 PERSP + 24 OTHER. ZERO ORTHO.

`run_mtx2.log`, `GETV_PROBE_AFTER=3000`, cap 400 exhausted in **under 7 frames**.
Identical across six complete frames:

| frame | total | PERSP | OTHER | ORTHO |
|---|---|---|---|---|
| f3000 – f3005 | **60** | **36** | **24** | **0** |

**So `255` §4's "a single identifiable load per frame" is false by a factor of
sixty. But the loads are NOT ambiguous**, and the new scissor field is what shows
why. Within one frame the sequence is **palindromic**:

```
full → (576,420)700x500 → (772,484)124x208 → (4,40)1272x880 → (44,232)772x656
     → (400,356)416x348 → (564,400)252x236 → (576,420)240x216 → (728,452)88x184
     → (772,484)44x152 → (772,488)44x52 → … and back out in mirror order
```

**That is the BG portal/room recursion narrowing and restoring its scissor**, and
re-loading the same projection at every step. All 36 PERSP carry a **byte-identical**
matrix — `m22=-1.000656 m32=-10.003 m23=-1 m33=0`, solving to **near 5.0, far
15,248**. One value, thirty-six loads.

### §2.1 — THE 24 OTHER ARE THAT PROJECTION WITH A VIEW ALREADY IN IT

Constant within a frame, drifting between frames. Fitting `V·P` against the world
`P` in row-vector convention, with `tz = -m33` and `s = -m23`:

| measured m32 | predicted | err |
|---|---|---|
| 39.848 | 39.848 | −0.0003 |
| 40.432 | 40.431 | −0.0009 |
| 40.910 | 40.909 | −0.0006 |
| 41.184 | 41.185 | +0.0006 |
| 40.682 | 40.682 | +0.0002 |
| 39.198 | 39.198 | +0.0003 |
| 39.181 | 39.180 | −0.0008 |

**Seven distinct values, every one predicted to under 0.001.** `tz` ranges −49.1 to
−51.2 and tracks the camera. **These are combined view×projection matrices being
loaded into the PROJECTION slot** — the thing `GETV_MVCHK` was written to test,
now measured without running it.

> **`[ASSUMED]`, and stated because the probe cannot exclude it: the fit uses four
> elements, so a Z-only modification is CONSISTENT with the data and is not proven.
> An eye offset is an X translation, and X translation is invisible in
> `m22/m32/m23/m33`.** **Counter-example search: none possible from this log — the
> elements that would falsify it were not printed.** **§5 prints row 3 whole.**

### §2.2 — WHAT THIS DOES TO `255` §3's ARCHITECTURE CHOICE

**It is not the clean win for B that step 1 hoped for, and the reason is `255` §1
point 3 arriving as a property of OUR tree rather than 007-VR's.**

**Neither class carries an eye translation.** The 36 PERSP are a pure frustum; the
24 OTHER carry a Z shift only. A per-eye substitution at `gfx_sp_matrix`'s
`G_MTX_PROJECTION` branch can deliver the asymmetric **frustum** to all 36
uniformly — that part is unambiguous and cheap. **It cannot deliver the eye
SEPARATION, because that lives in the view.** Substituting projections alone gives
two images differing in shear and not in viewpoint, **which is `B1`.**

**No recommendation is made. B is viable but is not a one-site change, and the 24
pre-combined loads need a decision of their own. A's double-tick risk is still
unmeasured.** The deciding read is §5's row 3.

---

## §3 — ►► `237` §1 IS RETRACTED. THE FOLDER FAULT IS NOT THE SAVE FILE. ◄◄

`236` §3.1 pre-registered both branches:

> *"If all four become selectable, the file was stale. If two still are, **the
> fault is in the port's file layer** and `eeprom.bin` is exonerated."*

`[REPORTED]` tonight, on a boot the log confirms was blank
(`run_rect.log`: `no existing save at … -- starting blank (512 bytes)`):
***"The selection of the file also didnt work till I use one of the bottom ones."***

> ## **THE SECOND BRANCH FIRED. `eeprom.bin` IS EXONERATED AND `237` §1 IS WRONG.**

**`237` closed this on one run that removed the symptom, and read that as proof of
the cause.** It had the alternative in front of it — `236` §3.1 named *"the port
simply never initialises unused folders correctly"* — and did not keep it open.

### §3.1 — AND A SECOND, INDEPENDENT FAULT FELL OUT OF THE SAME LOOK

`[MEASURED]` across **all 18 run logs**, 2026-08-27 19:51 to tonight:
`[getv][save] loaded` fires in 16 of them and **`flush` fires in ZERO.**

`[READ]` `port_save.c:337` — `geSaveFlush()` is called from `osEepromWrite` on
every block, and prints `flush #N` on success. `[READ]` the path is otherwise
healthy: `geSaveInit` sets `ge_eeprom_enabled = 1`, `osEepromProbe` returns
`EEPROM_TYPE_4K`, and reads demonstrably work.

> **So the game never calls `osEepromWrite` at all. The EEPROM has never been
> written, on any build, in any logged run.**

**That makes `port_save.c:175`'s own comment false in practice** — *"file2.c's CRC
check then rewrites it correctly on first run."* It cannot. **Nothing self-heals,
and no progress can persist.**

**F1 and F2 are kept SEPARATE.** `[INFERRED]` they share a cause in `file2.c`
never reaching its init/rewrite path. **Counter-example search: none run — and
`GETV_SAVE_DEBUG=1` prints every block read and write, which separates "file2.c
never runs" from "file2.c runs and declines to write" in one launch and no build.
That is §5's first run.**

### §3.2 — THE OWNER'S HEDGE WAS DATA, AND IT RELOCATED THE SUSPECT

`[REPORTED]`: *"The menu issue didnt start on this build, I think it was before
this one or before that."*

**That window is exactly where `ALIGN64_V2_PTR` landed** — the 23:24 build, one
before tonight's, in **`front.c`, the file-select file**. It was excluded earlier
in the session on a timeline I had wrong, and the owner's own hedge is what put it
back. **`HANDOVER` §5 holds again, and `252` §6's "keep the wearer's hedges" paid
for itself within a day of being written.**

> **`254` shipped it UNGATED, on `253`'s argument that *"an off-switch for that is
> a switch nobody would ever flip"*. Nine hours later it needs flipping.**
> **THE RULE THAT COMES OUT OF IT: A KNOB IS NOT ONLY FOR A CHANGE YOU EXPECT TO
> REVERT. IT IS WHAT LETS A SUSPECT BE EXCLUDED IN ONE LAUNCH INSTEAD OF A
> REBUILD.** Correctness arguments do not decide whether a change is testable.
> **`GETV_ALIGNPTR` is added at the call site, default ON; the macro is untouched.**

---

## §4 — THE INTRO: `231` §4's FOURTH BRANCH FIRED

`231` §4 pre-registered four outcomes for `GETV_RECTPROBE`. It had never been run.
`[MEASURED]` `run_rect.log`:

- **288,000 texrects reached the RDP.** The *"count == 0 → DL plumbing"* branch is
  dead. They arrive.
- Of 73 sampled dumps, **40 have `probe64: min=0 max=0 nz=0` — entirely zero
  texels.** That is the fourth branch: *"a texture whose texels are all zero."*

The 40 are one clean class, and it is the owner's *"first texture that slides as
james is walking out"*:

```
px=(412,155)-(439,155)  fmt=4 siz=1 cms=2 cmt=2 line=440 lrs=1756 lrt=0
cyc=0 om_l=0x0f0a4000   prim=(118,118,118,255)  bytes=440  min=0 max=0 nz=0
```

**A 440-byte, one-row I8 strip, drawn full-width and one pixel tall, at a
different `y` each time, with `prim` stepping a grey ramp** — 118, 231, 90, 203,
133, 62, 246, 175, 104, 218, 147. A horizontal scanline wipe.

**Everything around it is correct**: `valid=1`, NDC on-screen, prim alpha 255,
sane tile descriptor, and a 440-byte load did occur — the right size for 440 I8
texels. **Only the texel data is zero.** Two combiners appear (24 × `0x30000301006000c1`,
16 × `0x3000303100600619`); all 40 are `dsdx=1024 dtdy=1024 flip=0`.

**Meanwhile the glyph class in the same run is healthy** (`max=186..219`, real
data). **So `231` §3's three-symptom grouping split apart exactly as `231`
pre-registered it would — but not in the direction it expected.** `236` had
already withdrawn the menu text; the glyphs are innocent here too; **the intro
strips are the one member that is genuinely broken.**

### §4.1 — WHAT THE PROBE STILL CANNOT SAY, AND THE ONE-LINE FIX FOR THAT

**The dump reads `loaded_texture[0] + tmem*8` — what the renderer samples AFTER
binding. It cannot distinguish:**

- **the game handed us a zeroed buffer** → the fault is upstream, in the asset or
  DL path; from
- **the data arrived and our binding points the sampler elsewhere** → the fault is
  in `gfx_pc.c`.

**These have different fixes and the log cannot choose between them.** §5 adds a
`BLANK` line that fires **only** when the sampled window is all zero and prints
`rdp.block_addr`'s own bytes beside `texture_to_load.addr`, naming the outcome:
`SOURCE ALSO ZERO (upstream)` / `SOURCE HAS DATA (binding)` / `NO BLOCK LOADED`.

---

## §5 — ON DISK NOW. ONE BUILD, THEN THREE ENV-ONLY RUNS.

**All three changes are either instruments or default-on gates, so the built
binary is behaviourally identical to tonight's.** `48` is satisfied by the RUNS,
each of which changes one thing.

| file | change | knob |
|---|---|---|
| `gfx_pc.c` | MTXTRACE gated + scaled cap + kind/frame/vp/scissor + **row 3 whole** | `GETV_MTXTRACE`, `GETV_PROBE_AFTER` |
| `gfx_pc.c` | RECTPROBE **blank-source discriminator** | `GETV_RECTPROBE` |
| `front.c` | `ALIGN64_V2_PTR` **gated, default ON** | `GETV_ALIGNPTR=0` reverts |
| `macro.h` | comment marked SUPERSEDED; **macro unchanged** | — |

**Run 1 — F1/F2, no build needed, do it first:** `GETV_SAVE_DEBUG=1`. Reads but no
writes → `file2.c` runs and declines to write. Neither → it never runs.

**Run 2 — F1's A/B:** `GETV_ALIGNPTR=0`, nothing else. All four folders selectable
→ `253`'s widening is the cause and `254` shipped a regression. Still two → it is
excluded, at the cost of one launch.

**Run 3 — the intro:** `GETV_RECTPROBE=1`, blank EEPROM, watch the gunbarrel
through. Read the `BLANK` lines only.

**`gfx_pc.c` IS GITIGNORED** (`233` §6.1). `tools/fetch-thirdparty.sh regen` is
part of the commit, not an afterthought — it regenerates
`getv/patches/thirdparty/0001-getv-port-layer.patch`, which is the tracked artifact.

---

## §6 — WHAT IS NOT CLAIMED

- **No architecture recommendation for Phase 1.** §2.2 says why, and §5's row 3 is
  the read that would support one.
- **`[ASSUMED]` the `V·P` fit is Z-only** (§2.1). Four elements cannot exclude X/Y.
- **No claim `ALIGN64_V2_PTR` causes the folder fault** — only that the owner's
  hedged window contains it, it is in the right file, and Run 2 costs one launch.
- **No claim F1 and F2 share a cause.** `[INFERRED]` only, and Run 1 tests it.
- **The 40 blank rects are a SAMPLE**, 1 in 5000 plus the first 8. **The healthy
  glyph dumps do not prove the glyphs are all healthy** — `49` again: a sample that
  happens to miss a fault prints the same thing as a build without one.
- **Nothing in §5 has been run.** It ships with the next build.
- **The black crates after an explosion remain an OBSERVATION, not a fault**
  (`252` §6). `[MEASURED]` this run: 0 `NULL texture`, 0 `could not load texture`,
  every `modeltex` line `0 MISSING`. **MGB64 with the same ROM is the free control.**
