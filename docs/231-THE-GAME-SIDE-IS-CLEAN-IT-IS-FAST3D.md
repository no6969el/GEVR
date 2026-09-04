# 231 — THE GAME SIDE IS CLEAN. THE MENU TEXT FAULT IS IN FAST3D.

**2026-08-28. `230`'s instrument was run. Docs run to `231`. NEXT DOC = `232`.**

> # ►►►► **`[MEASURED]` 66,843 GLYPHS. EVERY SINGLE ONE EMITTED. ZERO REJECTED.** ◄◄◄◄
> **`230` §5's leading candidate — a bad `g_ViBackData` failing all three gates — is
> FALSIFIED, and so is `230` §1.3's inference that the glyphs never reach fast3d.**
> **`viGetX()/viGetY()` are `(440,330)`, the clip rect is sane, and `textRenderGlyph`
> emits a `gSPTextureRectangle` for every character the front end asks for.**
>
> **THE INSTRUMENT ANSWERED AGAINST THE HYPOTHESIS THAT BUILT IT. THAT IS WHY IT WAS
> AN INSTRUMENT AND NOT A FIX.**

---

## §1 — THE RUN

`[MEASURED]` `getv/build-windows/run_tt.log`, 141,701 bytes, **19:41:08**, against
`goldeneye.exe` of **19:40:22** — **the log is NEWER than the binary** (`133`).
`build.log`: `game 165 built 0 failed · assets 234/0 · audio 40/0 · port layer
58/0 · port c++ 2/0 · goldeneye.exe 17.2 MB`.

```
[getv][tt] glyph idx=51 w=8  h=12 base=0 px=00007ff62d407150 | x=59  drawY=23 | clip=(58,23)+440x330 | vi=(440,330) | orient=0 | stage=4
[getv][tt] glyph idx=54 w=14 h=12 base=0 px=00007ff62d4072e8 | x=68  drawY=23 | clip=(58,23)+440x330 | vi=(440,330) | orient=0 | stage=4
...
[getv][tt] render=4400 outlined=0 | glyphs=68643 | rej_vi=0 rej_clip=0 rej_edge=0 rej_ycase=0 EMITTED=68643 | quad=0
```

| reading | value | what it kills |
|---|---|---|
| `vi=(440,330)` | the hi-res menu arm ran | **`front.c:9221`'s `viSetXY(440,330)` DID execute.** `230` §2's GATE-1 candidate is dead |
| `clip=(58,23)+440x330` | sane, and `x` starts inside it | GATES 2 and 3 are dead |
| `rej_* = 0` across 68,643 glyphs | **not one rejection, ever** | the whole four-way y-case tree is dead |
| `EMITTED = glyphs` | **every glyph produced a texrect** | the game side is doing its job |
| `render=4400 outlined=0` | the front end uses **`textRender` only** | `textRenderOutlined`/`textDrawGlyphQuad` are not on this path at all |
| `w=8 h=12 base=0`, distinct `px=` per glyph | real metrics, real pointers | the font tables are good, third independent confirmation |

**`230` §1.3 said `[INFERRED]` the texrects were not reaching fast3d, on the
strength of a constant `tris submitted=520`. It stated its counter-example search
and it was WRONG: 520 was a different screen, and the frame counts move as soon as
the menu is up (`301: submitted=1020 drawn=492`). The inference was tiered
correctly, which is the only reason it cost nothing.**

---

## §2 — SO WHERE DOES A TEXRECT DIE? THE READ NARROWS IT TO SHADING.

`[READ]` `gfx_dp_texture_rectangle` -> `gfx_draw_rectangle` -> **two
`gfx_sp_tri1` calls** per rectangle. Between `ge_tri_submitted++`
(`gfx_pc.c:2710`) and `ge_tri_count++` (`:3366`) there are exactly **two** ways
out, and **neither can fire for a rectangle**:

1. **the clip reject** (`:2855`, `v1->clip_rej & v2->clip_rej & v3->clip_rej`) —
   `[READ]` `gfx_draw_rectangle` writes `x/y/z/w/u/v/vpx/vpy/vpz` into
   `rsp.loaded_vertices[MAX_VERTICES + 0..3]` and **never writes `clip_rej`**.
   Those four slots are outside the range `gfx_sp_vertex` fills, and `rsp` is
   static, so `clip_rej` is **0 for the life of the process**. The AND can never
   be non-zero. *(Latent hazard, noted not chased: it works by accident of
   zero-initialisation, and `gfx_sky_rdp_tri` sets `clip_rej = 0` explicitly on
   three of the same four slots while `gfx_draw_rectangle` sets none.)*
2. **the cull** (`:2867`) — `[READ]` `gfx_draw_rectangle` sets
   `rsp.geometry_mode = 0` around both `gfx_sp_tri1` calls, so `G_CULL_BOTH` is
   clear and the whole block is skipped.

`[READ]` **there is no other `return;` between `:2885` and `:3366`.**

> ## ►► SO THE GLYPHS ARE BEING **DRAWN**, AND DRAWN INVISIBLY. ◄◄
> **The fault is in what those two triangles SHADE — the texture, the tile
> descriptor, the combiner, the prim colour, or where they land in NDC — not in
> whether they exist.**

---

## §3 — AND THE OWNER'S TWO NEW OBSERVATIONS PUT THEM IN ONE CLASS

`[REPORTED]`, this run: **the Bond gun-barrel intro was missing some textures, and
the blood did not come down from the top.**

**`[INFERRED]` all three symptoms are 2D texture rectangles in the front end**:
the glyphs, the gun-barrel elements and the blood are drawn as texrects, while the
3D geometry around them renders. **Counter-example search, and it is not clean:**
the purple explosion (`229` §20 item 4) is in-level and is not obviously a texrect,
and the gun-barrel is a hybrid — the walking Bond is a model. **So this is a
grouping worth testing, not a mechanism, and §4's probe is pointed at the texrect
path precisely because that is the common term.** **If the probe says texrects
arrive with good state, the grouping is wrong and the three split apart again.**

---

## §4 — THE SECOND INSTRUMENT: `GETV_RECTPROBE=1`. ON DISK, COMPILES CLEAN.

**File:** `getv/port/fast3d/gfx_pc.c`, at the top of
`gfx_dp_texture_rectangle` — **before** the `G_CYC_COPY` fiddling, so the state
printed is the state that arrived. **Off by default. No behaviour change.**

**It counts every texture rectangle the RDP receives, and dumps the full state of
a sample:**

- the rect in native pixels **and the NDC it will land at**, computed with
  `gfx_draw_rectangle`'s own `kx`/`ky` rather than re-derived
- `gfx_native_width/height` and the live scissor
- the tile descriptor: `fmt siz cms cmt line tmem size_valid uls ult lrs lrt`
- cycle type, `combine_mode`, `combine_has_c2`, `other_mode_l` (blender/render mode)
- **prim and env colour** — `front.c:1294` passes colour `0xFF`, which is
  **BLACK with alpha FF**, and `:2850` passes `0xEBD879FF`
- `loaded_texture[0].addr` and size, **plus a texel probe over the first 64 bytes
  THE RENDERER WOULD SAMPLE (`addr + tmem*8`), reporting min/max/non-zero**
- the raw `uls ult dsdx dtdy flip` the game sent

**Sampling: the first 8 rects, then 8 more once the frame counter passes
`GETV_RECTPROBE_AFTER` (default 600), then every 5000th; a running count every
2000.** The second window exists because the first 8 are the legal/logo screens —
**the same gate, for the same reason, as the existing `GETV_TRIWHERE_AFTER`.**

### `[MEASURED]` IT COMPILES
`gcc -fsyntax-only` with the port flag set from `build_windows.ps1` lines 227-232
(`-DGE_PORT_NATIVE -DRAPI_GL -DWAPI_SDL2 -std=gnu17 -Werror=return-type`) -> **EXIT 0**.
Linux syntax check, not a build.

### WHAT EACH OUTCOME MEANS

| reading | conclusion |
|---|---|
| **count = 0** (or far below 68,643) | the display list carrying the glyphs is **never executed**. A DL-plumbing question; nothing in fast3d is at fault |
| **count ~= glyph count, `probe: max=0`** | the glyph's texels are **not in TMEM where the renderer samples** — a load/tmem-offset fault |
| **count OK, `prim=(...,0)`** | a zero alpha; the combiner multiplies TEXEL0 by PRIM |
| **count OK, `ndc` outside ±1** | placement — the 440x330 path leaking a 320x240 constant |
| **count OK and everything sane** | the fault is further down: the combiner translation or the blender, and `GETV_LIGHTTRACE=1`'s per-combiner histogram is the next read |

---

## §5 — HOW TO RUN IT

**A FRESH PowerShell window.**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
cd C:\Users\<USER>\Desktop\GoldenEyeVR\goldeneye-native
& getv\build_windows.ps1 -Target all *> build.log 2>&1
cd getv\build-windows
$env:GETV_RECTPROBE = "1"
.\goldeneye.exe *> run_rp.log 2>&1
```

**Sit on the front end for a few seconds with the text screen up before doing
anything else** — the second sample window fires around frame 600 and that is the
sample that matters. **Then, if you want the gun-barrel data too, let the intro
play.** Close with the **X**. `run_rp.log` must be newer than `goldeneye.exe`.

**One variable. No `GETV_MENU`. No `GETV_TEXTTRACE`** — it is still in the binary
and still costs nothing unset, but two instruments in one run is two behaviour
descriptions in one log.

---

## §6 — WHAT IS NOT CLAIMED

- **No candidate fix is on disk.** Both changes this session are instruments.
- **`230`'s `GETV_TEXTTRACE` stays** (`DELETE NOTHING`) and is the control if the
  game side ever needs re-checking.
- **The `clip_rej` observation in §2 is a READ, not a defect report.** It is
  recorded because a future change to `gfx_draw_rectangle` that starts writing
  those slots would silently arm it.
- **`outlined=0` is a fact about the FRONT END only.** The in-level HUD's use of
  `textRenderOutlined` is untested by this run.
