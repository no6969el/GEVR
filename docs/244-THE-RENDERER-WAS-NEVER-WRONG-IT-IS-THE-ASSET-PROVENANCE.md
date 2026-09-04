# 244 — THE RENDERER WAS NEVER WRONG. `GETV_RGBA16BE` IS AN ASSET-PROVENANCE FAULT.

**2026-08-29. From `akratch/goldenballoon`. Docs run to `244`. NEXT DOC = `245`.**

> # ►►►► **OUR RGBA16 READ IS ALREADY CORRECT, AND IDENTICAL TO A SIBLING
> # PORT'S. SO THE TEXELS ARRIVE PRE-SCRAMBLED — AND THE SCRAMBLE HAS ALREADY
> # BEEN DIAGNOSED ONCE IN THIS TREE, FOR THE FONTS.** ◄◄◄◄

---

## §1 — THE THIRD PORT, AND WHY IT IS WORTH ANYTHING TO US

**`https://github.com/akratch/goldenballoon` — "Golden Balloon", `[READ]` a native
and browser source port of the 1997 N64 kart racer (Diddy Kong Racing).**

**A DIFFERENT GAME. Same author as MGB64, and NEWER** — WebGPU and WebAssembly
backends, three presentation modes, **91 automated test checks** covering boot,
racing, renderers, 2-4 player, audio and Adventure mode. Its own README states it
is *"unaffiliated with GoldenEye's MGB64 port but shares architectural lineage
through the sm64ex/Fast3D renderer"*.

> **THAT SHARED LINEAGE IS THE WHOLE VALUE. `getv/port/fast3d/gfx_pc.c` and
> `platform/fast3d/gfx_pc_dkr.c` DESCEND FROM THE SAME CODE**, so their texture
> importers are directly comparable, line for line — **which is a control this
> project has never had for a renderer question.**

---

## §2 — THE COMPARISON, AND IT GOES THE OPPOSITE WAY FROM `237`

**Golden Balloon, `gfx_pc_dkr.c:2275`:**
```c
/* Texels are big-endian ROM bytes (swap_texture leaves them
 * untouched by design); read the 16-bit value MSB-first. */
uint16_t c = ((uint16_t) row[x * 2] << 8) | row[x * 2 + 1];
```

**Ours, `gfx_pc.c:import_texture_rgba16`, at the DEFAULT `GETV_RGBA16BE=0`:**
```c
uint16_t col16 = (rdp.loaded_texture[tile].addr[b0] << 8)
               | rdp.loaded_texture[tile].addr[b1];
```

> ## ►► **THE SAME READ. BYTE-EXPLICIT, MSB-FIRST, ENDIAN-INDEPENDENT.
> ## OUR RENDERER IS ALREADY CORRECT AND ALWAYS WAS.** ◄◄

`[READ]` and what the knob actually does is perturb the BYTE INDICES before that
read:
- **`=1`** — `b0 = (b0 & ~3) | (3 - (b0 & 3))`, i.e. **reverse each 4-byte group**.
  Its own comment: *"undo a native u32 store"*.
- **`=2`** — swap the two bytes of each texel.

**So `237` had it backwards.** `GETV_RGBA16BE=1` does not correct a renderer that
reads endian-wrongly; **it UNDOES A CORRUPTION ALREADY PRESENT IN THE TEXEL DATA.**

---

## §3 — AND THAT CORRUPTION IS ALREADY DIAGNOSED IN THIS TREE. FOR THE FONTS.

`[READ]` `textrelated.c`, `ge_font_convert()`, written by an earlier session:

> *"The pixel data is a byte stream that merely happens to be stored as
> `u32 fontZurichBold_fontbytes[] = { ... }`. On the N64 byte 0 of each word was
> the leftmost pixel; compiled little-endian, byte 0 of that word in memory is the
> word's LAST byte, so every group of four pixels sits REVERSED. That mirrors each
> glyph in 4-pixel chunks, which is why 'b' rendered as 'd' and 'p' as 'q'."*
>
> *"So the rule needs one more clause: swap ROM blobs, never extracted C data,
> EXCEPT WHERE EXTRACTED C DATA IS REALLY A BYTE STREAM STORED IN A u32 ARRAY.
> Check what a field MEANS, not just where it came from."*

**`ge_font_convert` fixes it by reversing each 4-byte group at load time. That is
EXACTLY what `GETV_RGBA16BE=1` does at texel-read time.**

> ## ►► SAME FAULT. SAME SHAPE. SAME FIX. TWO DIFFERENT ASSET CLASSES, FOUND
> ## EIGHTEEN DOCUMENTS APART AND NEVER CONNECTED. ◄◄

**`[INFERRED]` any GoldenEye asset extracted into a `u32 ...[]` C array is
byte-reversed in 4-byte groups on a little-endian build, and the explosion's
RGBA16 flare is one of them.** **Counter-example search: assets read straight out
of the ROM blob are NOT affected — Golden Balloon says so of its own
(*"swap_texture leaves them untouched by design"*), and this tree's own font rule
says the same. So the fault is per-asset-PROVENANCE, not per-format.**

---

## §4 — WHICH EXPLAINS `239` EXACTLY, AND RETIRES THE "CENSUS" FRAMING

`239` §3 retracted `GETV_RGBA16BE=1` as a global default because *"everything
looks weird"*. **§3 above says why, and it is not that the switch is unsafe in
general:**

| the texture came from | at `=0` | at `=1` |
|---|---|---|
| **an extracted `u32[]` C array** (the explosion flare) | **wrong** — reversed in 4-byte groups | **right** |
| **the ROM blob, untouched** | **right** | **wrong** — the knob reverses correct data |

**A GLOBAL SWITCH CANNOT BE RIGHT FOR BOTH, AND UPSTREAM'S "the census has no
coverage" WAS THE SYMPTOM OF THAT, NOT A SAMPLING PROBLEM.** No amount of extra
frames would have made it safe to promote — **the correct fix is not a renderer
mode at all, it is to normalise the asset AT INGEST, once, the way
`ge_font_convert` already does for fonts.**

**`[MEASURED]` corroboration on file:** `[getv][tex16be]` reads `16b_images=0` on
every menu and early-level frame this project has captured, and upstream's own
note says the count moves **8 -> 9 only as the explosion appears**. **The one
RGBA16 consumer anyone has ever observed is the flare — the asset most likely to
have come through the extractor as C data.**

---

## §5 — TWO MORE THINGS WORTH TAKING FROM THAT TREE

**1. `platform/asset_swap.c` — a centralised byte-swap layer with a MEMO.**
`[READ]` it keeps a session-long set of already-normalised blob pointers so a
record cannot be swapped twice, guards the memo against section reload, and
**fails CLOSED on overflow**: a full table reports *"already swapped"* (skip)
rather than *"not yet swapped"* (re-swap), *"because re-swapping a record puts it
back into big-endian, which is strictly worse than leaving one un-normalized
record alone."* **That is the systematic answer to the fault class that has now
bitten this project four times** (fonts, the spark colour, `unk10`, the flare).

**2. `dkr_arena_room()` / `dkr_ptr_plausible()` — bounds checks before following a
game-supplied pointer.** `[READ]` the TLUT loader refuses rather than reading past
its arena, *"the entry count comes from the display list, the load address from the
game."* **`243` §2's crash is a `-1` reaching a dereference; a plausibility guard
is the shape of defence that turns that into a logged refusal instead of a
close.**

**NEITHER IS BUILT HERE AND NEITHER SHOULD BE TONIGHT.** Recorded as design
precedent with a working implementation to read.

---

## §6 — WHAT THIS CHANGES, AND WHAT IT DOES NOT

- **`237`'s FIX still works** — `=1` really did fix the flare, `[REPORTED]`. **Its
  EXPLANATION was wrong**, and §2 replaces it.
- **`238` §2's promotion to `goldeneye.cfg` stays WITHDRAWN** (`239`), and §4 now
  gives the principled reason rather than "the census is thin".
- **NOTHING IS BUILT.** No code changed in this document.
- **`[ASSUMED]` which GoldenEye assets came through the extractor as `u32[]` C
  data.** The font path proves at least two did. **Establishing that list is the
  real work, and `229` §9's extraction pipeline is where it lives.**
- **The inventory crash, the ammo re-pickup and the loot-box contents (`243`) are
  untouched by any of this.** `G-243` still stands and still needs the map.
