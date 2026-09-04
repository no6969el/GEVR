# 230 — THE MENU TEXT: THE READ, AND THE INSTRUMENT IT PRODUCED

**2026-08-28. Follows `229` §20 item 1. Docs run to `230`. NEXT DOC = `231`.**

> ## THIS DOCUMENT SHIPS AN INSTRUMENT, NOT A FIX.
> `229` §20 item 1 said the next step was **a read, not a run**. The read is done
> and it did not produce a candidate — it produced a **partition**. One build, one
> run, and the fault is confined to one of three places that need three different
> fixes.

---

## §0 — ITEM 0 IS ALREADY DONE

`[MEASURED]` `git log` in both repos: **`44cc8c8 Phase 0 passed: the native port
boots and plays (docs 186-229)`**, working tree clean. `229` §20's ITEM 0 and
`HANDOVER` §3's HOUSEKEEPING line are **discharged**. The 550 `.bin`, the two
generated sources, the CRLF fix and the four edited files are tracked.

---

## §1 — THE READ. WHAT THE FRONT END ACTUALLY DOES WITH TEXT.

`[READ]` **There is no separate menu text path.** `front.c` draws every string
through the same three functions the in-level HUD uses:

| site | call |
|---|---|
| `front.c:980` | `textRenderOutlined(...)` |
| `front.c:996`, `:1294`, `:1337`, `:1389`, `:1537`, `:2850`, `:2862`, `:2866`, `:2877`, `:2885`, `:2908`, `:2937` | `textRender(...)` |

Both funnel into **`textRenderGlyph`** (`textrelated.c:421`), which loads the
glyph with `gDPLoadTextureBlock` and emits **one `gSPTextureRectangle` per
character**. The outlined path goes through `textRenderGlyphOutlined` ->
`textDrawGlyphQuad` (`:751`), four more texrects.

## §1.1 — AND THAT PATH IS KNOWN TO WORK IN-LEVEL ON THIS BINARY

`[READ]` `ge_font_convert`'s own comment (`textrelated.c`, the glyphbias
paragraph) records that the bias-12 fix was **verified against "the sheared ammo
readout on the Dam HUD"** — i.e. glyphs, font tables and texrects all render in a
level on the native port.

> **SO THE FAULT IS NOT THE TEXT MACHINERY. It is specific to the front end.**
> This is consistent with `229` §14 (`0/94` bad glyphs, not one texture fault in
> 100,270 lines) and it narrows that finding: the assets are innocent AND the
> renderer is innocent in the general case.

## §1.2 — FONT TABLES, CONFIRMED AGAIN FROM `run_front.log`

`[MEASURED]`, `getv/build-windows/run_front.log` lines 156-160, **a legitimate
boot — no `GETV_MENU` anywhere in the file** (`grep -o "GETV_[A-Z_]*"` returns
only `CONTROLS`, `DUALANALOG`, `FPS`, `INVERTLOOK`, `KEYBOARD`, `REALCLOCK`,
`SUBWORD`, `SW`):

```
[getv] font: converted  9392 rom bytes -> 10148 native (6460 px), glyphbias=12
[getv] font:   sample 'T' idx=51 base=2 h=8  w=7 kern=4 px=00007ff6c4523f9c; 0/94 bad
[getv] font: converted 13632 rom bytes -> 14388 native (10700 px), glyphbias=12
[getv] font:   sample 'T' idx=51 base=0 h=12 w=8 kern=4 px=00007ff6c4527110; 0/94 bad
```

**Sane widths, heights, baselines and pixel pointers in both fonts.**

## §1.3 — AND THE TRIANGLE COUNT DOES NOT MOVE

`[MEASURED]` same log: `[getv] frame N: tris submitted=520 drawn=520` at frames
**61, 121, 181, 241** — **identical**. A screen that was emitting glyph texrects
would not hold a fixed triangle count while the menu changes.
**`[INFERRED]` the glyph texrects are not reaching fast3d at all.**
**Counter-example search:** the one way this could be wrong is if fast3d counts a
texrect somewhere other than `tris`; `gfx_pc.c` turns every texture rectangle
into two triangles through `gfx_draw_rectangle`, so it would be counted.
**The instrument in §2 tests this directly rather than resting on the inference.**

---

## §2 — THE THREE GATES. WHY THIS IS A PARTITION AND NOT A GUESS.

`[READ]` `textRenderGlyph` can return **having drawn nothing, silently**, from
three independent places. None of them logs, errors, or touches a texture:

```c
/* GATE 1 — the game's own screen extent */
if (text_orientation || (*x > 0 && *x <= viGetX() && drawY + curchar->baseline <= viGetY()))
/* GATE 2 — the clip rectangle */
if (clipX + clipWidth >= *x && clipY + clipHeight >= curchar->baseline + drawY
    && *x >= clipX && curchar->baseline + drawY + curchar->height >= clipY)
/* GATE 3 — the right edge, AFTER the texture has already been loaded */
if ((*x + curchar->width) <= clipX + clipWidth)
```

**GATE 1 reads `g_ViBackData->x/y`.** `[READ]` those are written in exactly three
places in the whole tree: `front.c:9221` (`viSetXY(440, 330)`), `front.c:9231`
(`viSetXY(320, SCREEN_HEIGHT)`) and `bondview2.c:8635`. **If the front end's
`menuInit` path has not run one of them, `viGetX()` is whatever the port left
behind and EVERY glyph is dropped before a single command is emitted.**

**GATES 2 and 3 read the same numbers.** `[READ]` `textRender` passes
`savedx, savedy` as `clipX, clipY` and its own `width, height` arguments as
`clipWidth, clipHeight` — and `front.c` supplies **`viGetX()`/`viGetY()` for those
arguments** (`:2850` and friends). **One bad `g_ViBackData` therefore fails gates
1, 2 and 3 together**, which is exactly the shape of "everything is present and
nothing is drawn".

`[MEASURED]` `run_front.log`: `[getv] SCISSOR n64: (0,40)-(1280,920) => 320x230`,
so the game is describing itself in its 320-wide space — **the `viSetXY(320,
SCREEN_HEIGHT)` arm, not the 440x330 one.** That is a statement about the
SCISSOR, not about `g_ViBackData`; **they are different variables and the
instrument is what connects them.**

---

## §3 — THE INSTRUMENT. `GETV_TEXTTRACE=1`. ON DISK, COMPILES CLEAN.

**File:** `vendor/ge-decomp/src/game/textrelated.c`.
**All of it inside `#ifdef GE_PORT_NATIVE`** — the N64 matching build is
untouched, so `225`'s byte-identical-ROM gate cannot regress.
**Unset, it is `((void) 0)` and two integer increments. No behaviour change.**

It records, per glyph, the furthest stage reached:

| stage | meaning | what it would mean if this is where they stop |
|---|---|---|
| `rej_vi` | dropped by GATE 1 | **`g_ViBackData->x/y` is wrong for the front end** — a `viSetXY` that never ran, or ran with the wrong values |
| `rej_clip` | dropped by GATE 2 | the clip rect the caller passed is wrong — `front.c`'s `viGetX()/viGetY()` arguments |
| `rej_edge` | texture loaded, dropped by GATE 3 | a right-edge/width problem only |
| `rej_ycase` | past every gate, no y-case fired | the four-way vertical case tree |
| `EMITTED` | **a texture rectangle was emitted** | **the fault is downstream of this file, in fast3d** — and §1.3's inference is wrong |

Plus `render=` / `outlined=` (how many times the game asked for text at all) and
`quad=` (the outlined path's own texrects).

**AND IF `glyphs=0` WITH `render>0`, the strings are reaching `textRender` and
dying on the `' '`/`'\n'`/`< 0x80` dispatch. IF `render=0` TOO, the front end is
not calling the text path at all and none of the above applies** — that is the
fourth outcome, and it is why the entry counters are in there.

**The first 8 glyphs print in full** — `idx w h base px x drawY clip=(...) vi=(...)
orient stage` — **so the counters can be checked against the source by hand rather
than trusted.** `48`: an instrument must be able to say *I CANNOT ANSWER THIS*;
this one says it by printing `render=0`.

### `[MEASURED]` IT COMPILES

```
gcc -fsyntax-only <the build's own game flags, verbatim from build_windows.ps1
    lines 206-225, including -std=gnu17 -Werror=return-type -DGE_PORT_NATIVE>
    src/game/textrelated.c
-> CLEAN
```
**This is a syntax check on Linux with the real flag set, not a build.** The
Windows build is still the gate.

---

## §4 — HOW TO RUN IT. ONE BUILD, ONE RUN.

**A FRESH PowerShell window, per `229` §20's env-var rule.**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
cd C:\Users\pdbar\Desktop\GoldenEyeVR\goldeneye-native
& getv\build_windows.ps1 -Target all *> build.log 2>&1
cd getv\build-windows
$env:GETV_TEXTTRACE = "1"
.\goldeneye.exe *> run_tt.log 2>&1
```

**NO `GETV_MENU`. NO OTHER `GETV_*`.** `229` §16/§17 cost two retractions to a
single boot-path shortcut.
**Boot to the front end, let it sit, press a direction or two, then close with the
X** — `X IS THE CLEAN EXIT ON THIS BUILD` and `taskkill` would lose the 64 KB
buffered stdout (`00-START-HERE`).

**Then say "done".** The assistant reads `run_tt.log` over the bridge.

### THE STALE-LOG CHECK APPLIES HERE TOO (`133`)
**`run_tt.log` must be NEWER than `getv\build-windows\goldeneye.exe`.**

---

## §5 — WHAT EACH OUTCOME UNBLOCKS

- **`rej_vi` dominant** -> read `front.c:9150-9240` and find why the `viSetXY`
  arm did not run, or what reset `g_ViBackData` after it. **A one-term fix.**
- **`rej_clip` / `rej_edge` dominant** -> the caller's clip arguments; `front.c`
  passes `viGetY(), viGetX()` at `:1294` and `viGetX(), viGetY()` at `:2850`
  — **note the order differs between call sites** and that is worth checking
  against `textRender`'s signature before anything is changed.
- **`EMITTED > 0`** -> §1.3's inference is falsified, the game is doing its part,
  and the question moves to `gfx_pc.c`: the combiner
  (`microcode_constructor` sets `G_CC` to `PRIMITIVE`/`TEXEL0`), the prim colour
  (`front.c:1294` passes `0xFF` = **black, alpha FF**), or the `G_TX_RENDERTILE`
  descriptor.
- **`render=0`** -> the front end never asks for text, and the question is a
  menu-state one, not a render one. **Nothing in §5 above would have been the
  fix, which is the point of measuring first.**

---

## §6 — WHAT IS NOT CLAIMED

- **Nothing about the purple explosion, the sfx or the latency.** They wait on
  item 1 exactly as `229` §20 ordered them.
- **No claim that `viGetX()` IS wrong.** It is the leading candidate because it
  fails three gates at once; **the instrument exists precisely because that is a
  reason to measure, not a reason to build.**
- **`run_front.log`'s `bgLoad 'bg/bg_dam_all_p.seg'`** says that run reached the
  Dam, so its frame counts are not purely a front-end sample. **The new run must
  be front-end only** — do not load a level before the numbers are read.
