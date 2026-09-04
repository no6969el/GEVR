# 232 — THE TEXRECT ARRIVES PERFECT. AND THE INTRO CRASH IS A NULL `Model`.

**2026-08-28. `231`'s probe was run and the intro crashed. Docs run to `232`. NEXT DOC = `233`.**

> # ►►►► **TWO FINDINGS, AND THE CRASH IS THE CHEAPER ONE.** ◄◄◄◄
> **1. `[MEASURED]` the glyph texture rectangles reach the RDP with EVERYTHING
> CORRECT** — right place, right format, real texels, full alpha, the standard
> XLU blender. **There is nothing left in the texrect path to blame.**
> **2. `[MEASURED]` the intro crash is `modelSetScale(NULL)` at `front.c:8560`** —
> fault address `0x28` is `Model->scale` **in the native 64-bit layout**, and the
> instrument that would confirm it is already on disk and has never been run.

---

## §1 — THE RUN

`[MEASURED]` `run_rp.log`, 225,592 bytes, **20:08:51**, against `goldeneye.exe`
of **20:07:50** — newer (`133`). `GETV_RECTPROBE=1`, nothing else.
**`[REPORTED]` the owner let the whole gun-barrel intro play — *"I never tested
it"* — and it crashed.** That is the first time the intro has been run to the end
on a build with working stdout.

---

## §2 — THE TEXRECT PROBE. EVERY FIELD IS RIGHT.

```
[getv][rp] #1 px=(59,23)-(67,35) ndc=(-0.732,0.861)-(-0.695,0.788) native=440x330
   scissor=(0,0 1280x960) | tile0 fmt=4 siz=1 cms=0 cmt=0 line=8 tmem=0 valid=1
   uls=0 ult=0 lrs=28 lrt=44 | cyc=0 combine=0x03013000000c1600 c2=1 om_l=0x005041c8
   | prim=(255,255,255,255) env=(0,0,0,0) | tex=00007ff64b667150 bytes=96
   probe64: min=0 max=205 nz=39 | uls_in=0 ult_in=0 dsdx=1024 dtdy=1024 flip=0
```

**18,000+ texrects seen. The sample above is `#1`, and `#5000`, `#10000` and
`#15000` are the same shape at other screen positions.**

| field | value | verdict |
|---|---|---|
| `px=(59,23)-(67,35)` | **identical to `231`'s glyph #1** (`x=59 drawY=23 w=8 h=12`) | the game's glyph became this rectangle. **The two instruments meet.** |
| `ndc=(-0.732,0.861)-(-0.695,0.788)` | well inside ±1, upper-left | **placement is correct.** The 440x330 path is not leaking a 320 constant |
| `native=440x330` | matches `viGetX/Y` | consistent with `231` |
| `fmt=4 siz=1` | `G_IM_FMT_I`, `G_IM_SIZ_8b` | **the format the font path asks for** |
| `line=8`/`16`, `lrs=28`/`60`, `lrt=44` | 8- and 16-wide tiles, 12 rows | matches `w=8`/`w=14`, `h=12` |
| `tmem=0 valid=1` | tile 0, a SETTILESIZE was seen | descriptor is real |
| `probe64: min=0 max=205 nz=39` | **39 of 64 sampled texels non-zero, with antialiased values** | **the glyph bitmap IS in the memory the renderer samples.** Not blank, not absent |
| `prim=(255,255,255,255)` | full white, **alpha 255** | `front.c:1537`/`:2862` pass colour `-1`. Not a zero-alpha fault |
| `cyc=0` | `G_CYC_1CYCLE` | correct |
| `om_l=0x005041c8` | `[READ]` decodes to **exactly `G_RM_AA_XLU_SURF`**: `AA_EN\|IM_RD\|CLR_ON_CVG\|CVG_DST_WRAP\|FORCE_BL\|ZMODE_OPA`, blender `(CLR_IN, A_IN, CLR_MEM, 1MA)` | **standard alpha blending, exactly what `microcode_constructor` sets** |
| `dsdx=1024 dtdy=1024 flip=0` | +1.0/+1.0, unflipped | the `RECTFLIP` fault is not on this path |

> ## ►► SO THE TEXRECT PATH IS EXONERATED END TO END. ◄◄
> **`231` §4's four named outcomes are ALL excluded**: the count is not zero, the
> texels are not blank, the prim alpha is not zero, and the NDC is not off-screen.
> **The remaining possibility inside fast3d was the combiner or blender, and the
> blender decodes correct.**

## §2.1 — WHICH RAISES A QUESTION THAT COSTS NOTHING TO ANSWER

**`[ASSUMED]`, and it has been assumed since `229` §14: that the front-end text is
still missing IN THIS BUILD.** Every measurement since says the machinery is
correct. **Two possibilities remain and the wearer settles both in one sentence:**

1. **the text now draws** — in which case a fix between `229` and here already
   cured it and the corpus is chasing a closed fault; or
2. **it still does not** — in which case the glyph is drawn correctly **and then
   covered**, because nothing else is left.

**OVERDRAW IS NOW THE LEADING CANDIDATE, and its instrument is already on disk
and has never been run:** `gfx_pc.c:5117` carries **`GETV_RECTTRACE=1`** (log
every fill rectangle: rect, fill colour, z state, scissor, native size) and
**`GETV_NOFILLRECT=1`** (drop fill rectangles entirely — the A/B).
`draw_blackbox_to_screen` and `microcode_constructor_related_to_menus`
(`textrelated.c:392`, `:404`) both emit `gDPFillRectangle` in the menu path.

**`GETV_NOFILLRECT` IS A BEHAVIOUR CHANGE AND GETS ITS OWN RUN** (`48`, and `229`
§20's env-var clause). `GETV_RECTTRACE` is read-only and does not.

---

## §3 — THE CRASH. NAMED, AND THE NUMBER PROVES IT.

```
[getv] displaycast: buf=00007ff64b668380 charidx=2
[getv] displaycast: anim=11/22 flip=1
[getv] cast body=16 'CnatalyaZ' allocSize=0x8fc0 buf=00007ff64b681380 rem=0x18160
[getv] cast head raw = 0xffffffff (signed -1)
[getv] boot-> ce:7-instance
[getv] ===== EXCEPTION 0xc0000005 =====
[getv] fault addr: 0000000000000028   <-- NULL-BASE OFFSET
[getv] FAULT PC: 00007ff64a1f3a6b
[getv]   rcx=0x0000000000000000 ... rax=0x0000000000000000
```

### §3.1 — `[MEASURED]` `0x28` IS `Model->scale` IN THE NATIVE LAYOUT

`[READ]` `bondtypes.h`'s `Model`, laid out for a 64-bit host (8-byte pointers):

| field | N64 offset (comment) | **native offset** |
|---|---|---|
| `s16 unk00`, `s16 rwdatalen` | 0x00, 0x02 | 0x00, 0x02 |
| `struct ChrRecord *chr` | 0x04 | **0x08** |
| `ModelFileHeader *obj` | 0x08 | **0x10** |
| `RenderPosView *render_pos` | 0x0c | **0x18** |
| `union ModelRwData **datas` | 0x10 | **0x20** |
| **`f32 scale`** | 0x14 | ► **0x28** ◄ |

`[READ]` `model.c:795`: `void modelSetScale(Model *objinst, f32 scale) {
objinst->scale = scale; }` — **one store, at 0x28, and `rcx` is 0.**

### §3.2 — AND THE UNGUARDED CALL SITE IS `front.c:8560`

`[READ]` there are two callers of `modelSetScale` in this path and **only one is
unguarded**:

- `chr_b.c:137` — inside `if (model != 0) { modelSetScale(model, scale); ... }` — **guarded**
- `front.c:8560` — `cast_model = setup_chr_instance(...); modelSetScale((Model *) cast_model, 0.1f);` — **no NULL check**

> **`makeonebody` returns `model` even when `modelmgrInstantiateModelWithAnim`
> gave it nothing** (its own `if (model != 0)` guard proves the author expected
> that), **and `front.c` dereferences the result immediately.**

### §3.3 — WHY THIS CAST AND NOT THE OTHERS

`[MEASURED]` the cast sequence ran repeatedly before the crash — `charidx=8`,
`charidx=1`, then `charidx=2` — and **the `[getv][sw]` probe fired for bodies 5,
22, 19 and 22**, i.e. every survivor took the *separate head model* path.
**The one that crashed is the only one with `head = -1` (`HEAD_FIXED`)**, so it
skipped `ce:6-headload` entirely. **`[INFERRED]` the head-less branch leaves the
instantiation short of something, or the pool in a different state.
Counter-example search: `title.c:518` calls `setup_chr_instance` with two real
headers and has never been reported to crash, which is consistent but is not a
head-less control — so this is a lead, not a mechanism.**

### §3.4 — THE INSTRUMENT ALREADY EXISTS AND HAS NEVER BEEN RUN

`[READ]` `chr_b.c:114`, **`GETV_MPCHR=1`**, prints per character body:

```
[getv][mpchr] body=N(file) head=N(file) hasHead=U | bodyRoot=%p rec=N tex=N
              | headRoot=%p rec=N | model=%p rwdatalen=N scale=%.4f pov=%.4f
```

**`model=(nil)` on the CnatalyaZ line closes §3.2 outright.** A non-null `model`
falsifies it and moves the fault into `modelSetScale`'s caller chain instead.
**This is the third instrument found already built and never run** — after
`GETV_AUDIO_TESTSFX` (`229` §20 item 2) and `GETV_RECTTRACE`. **Grep the port for
`getenv("GETV_` before writing a new probe.**

---

## §4 — THE NEXT RUN. READ-ONLY, TWO PROBES, NO BEHAVIOUR CHANGE.

**Both of these only print. Neither re-routes anything, so `48` permits them in
one run — unlike `GETV_NOFILLRECT`, which does not travel with them.**
**NO REBUILD IS NEEDED: both are already in `goldeneye.exe`.**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
cd C:\Users\<USER>\Desktop\GoldenEyeVR\goldeneye-native\getv\build-windows
$env:GETV_MPCHR    = "1"
$env:GETV_RECTTRACE = "1"
.\goldeneye.exe *> run_mp.log 2>&1
```

**Let the intro run to the crash.** The crash handler writes the log itself, so
nothing is lost.

**Then, and ONLY as a separate run, the overdraw A/B:**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
$env:GETV_NOFILLRECT = "1"
.\goldeneye.exe *> run_nofill.log 2>&1
```

**If the menu text appears with fill rectangles dropped, the text was being
covered and the fault is a fill rectangle, not the glyph.** If it does not appear,
overdraw by FILL rect is excluded and the next suspect is a textured rectangle
drawn over it.

---

## §5 — WHAT IS NOT CLAIMED

- **No fix is on disk.** `front.c:8560` wants a NULL check, and it is not written:
  **a guard there would hide the crash without explaining why the model was
  null**, and `GETV_MPCHR` costs one run to find out. `48`.
- **The purple explosion is untouched**, and §2 weakens `231` §3's grouping: the
  glyph texrects are perfect, so *"missing gun-barrel textures"* is no longer
  obviously the same fault. **`231` §3 said the grouping was a lead and not a
  mechanism; this is the run that started to break it up.**
- **No claim that the menu text is or is not visible in this build.** §2.1 is a
  question for the wearer, and `HANDOVER` §5 says his report outranks the analysis.
