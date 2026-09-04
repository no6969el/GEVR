# 264 — THE COMBINER PROBE IS BUILT. IT IS KEYED ON A POINTER, AND IT CAN FAIL.

**2026-08-29m. WRITTEN BEFORE THE RUN, on purpose (`48` rule 15).**
**No result is claimed here. `263` §4 asked for an instrument; this is the instrument,
its wiring, and every way it can come back wrong — recorded now so the numbers cannot be
read generously later.**

---

## §1 — WHAT WAS BUILT, AND WHERE

`GETV_CCPROBE=<n>` — **`n` = lines per table entry, default 12. Unset or `0` = off.**
Three parts, all `#ifdef GE_PORT_NATIVE` / diagnostic-only. **No pixel changes.**

| part | file | what it does |
|---|---|---|
| 1 | `vendor/ge-decomp/src/game/tex.c` (`ge_cctab_*`, and one call inside the existing `DEGENERATE_1x1` branch of the `GETV_TEXBIND` block) | records every 1x1 bind: **pixel pointer, texturenum, texnum asked for, model name** |
| 2 | `getv/port/fast3d/gfx_pc.c`, in `ge_upload_texture()` | records the **decoded RGBA texel** of every 1x1 upload, against the same pointer |
| 3 | `gfx_pc.c`, in `gfx_sp_tri1()` just after the `[getv][bigtri]` block | one line per draw that binds a table entry: **combiner + every colour input** |
| census | `gfx_pc.c`, `gfx_end_frame()`, the existing 60-frame block | `[getv][ccprobe]` — table state, **printed whether or not the gate is on** |

## §2 — ►► THE TRAP THE DESIGN EXISTS TO AVOID ◄◄

**The bind and the draw are DIFFERENT PASSES.** `[READ]` `objecthandler_2.c:331` sets
`ge_model_convert_name` around `ge_convert_gdl()`; `tex.c:974`'s bind runs inside that
convert. **The draw runs frames later, out of the display list the convert built.**

> **A "current model" global read at DRAW time therefore names whatever model was
> CONVERTED LAST — not the one being drawn. It would have printed confident, wrong
> attributions: `263` §1 committed to code instead of prose.**

**The one object both passes hold is the PIXEL POINTER.** `[READ]`
`texWriteLoadToTmemAddr()` emits `gDPSetTextureImage(..., tex->data)`
(`tex.c:606,622`); `gfx_pc.c` sees that same address as
`rdp.loaded_texture[tile].addr`. **That is the key, and it is the whole design.**

`[READ]` `struct tex` (`image.h:39-53`) — `u8 *data`, `u8 width`, `u8 height`.
**Model names are COPIED into the table, not aliased**: `ge_model_convert_name` points
at the loader's `name` argument, which does not outlive the convert. **A probe whose
attribution rots is worse than no probe.**

## §3 — WHY ONLY 1x1 BINDS, AND WHY THE CAP IS PER ENTRY

`263` §3: **eight texnums in the whole ROM are genuinely 12-byte images**, so the table is
tiny (64 slots, overflow counted). And it necessarily contains **the CONTROL** — `1608`,
bound by `CheadbrosnanZ`, **which renders correctly.**

**The cap is per table entry, not per run, and that is not a detail.** `1514` is bound by
all six weapons and drawn every frame. **A single global cap would be spent on the HUD
before `CorumovZ`'s one shirt draw ever appeared — and the control with it.** A cap that
can starve the two draws the probe exists for is not an instrument.

## §4 — ►►►► WHAT KILLS THE HYPOTHESIS, STATED BEFORE THE RUN ◄◄◄◄

**`263` §4 is `[INFERRED]` and may not be built on. This is what would settle it.**

- **HYPOTHESIS DEAD** if the 1x1 draws come back with **sane non-black `prim`/`env`/shade**
  and a combiner that selects one of them. Then the black is not in the combiner inputs,
  and the fault is geometry or lighting instead.
- **I CANNOT ANSWER THIS** if the line for `CorumovZ`/`1917` is **field-for-field identical**
  to the line for `CheadbrosnanZ`/`1608`. **The control is mandatory. A run that prints only
  the faulty draw is not evidence** (`182` §2 — the sample of convenience).
- **HYPOTHESIS SURVIVES** only if the faulty draw's colour inputs differ from the control's
  in a way that resolves to black. **Surviving is not confirming.**

### AND IF IT IS POINTED AT THE WRONG THING, IT SAYS SO
| output | means |
|---|---|
| `model=` the same name on every line | the pass trap in §2 fired anyway — **the attribution is worthless and so is the rest of the line** |
| `entries=0` | the game side never ran, or no 1x1 bind happened. Nothing about the combiner is being measured |
| `entries>0` but `draws=0` | **the KEY is wrong** — the address `tex.c` recorded is not the one the RDP loads from. `unkeyed=` and `last_delta=` say by how much; **a constant non-zero delta is a header offset, not a bug** |
| `valid=0` on an entry that draws | the decode never went through `ge_upload_texture` (HD-pack override, or a cache hit). **Half the question is unanswered and must be reported as unanswered** |

## §5 — THE RUN

```
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
$env:GETV_SLOTFREE="1"; $env:GETV_TEXBIND="1"; $env:GETV_CCPROBE="12"
```
**Touch nothing from boot** — `263` §6: skipping ANY intro video sends it straight to the
menu and the cast roll never runs. Let it loop twice, then quit.

**Before reading a number:** the log is NEWER than the exe (`133`); `grep -a ccprobe` finds
the format string IN the binary; and the log carries its terminating record (`262` §5).

## §6 — NOT CLAIMED
- **No result. Nothing has been run.** Every claim above is `[READ]`, from the files cited.
- No claim the two faults share a cause. `263` §7 stands.
- **No claim the Trevelyan face is a 1x1 draw at all.** If no probe line names a Trevelyan
  model, that half is untouched and must be said so rather than generalised from Ourumov.
- The probe compiles clean under `-Wall -Wextra` in isolation; **it has not been built into
  the game.** `build_windows.ps1:160` is `-w`, so a real diagnostic there would be silent.

## §7 — OWNER ACTION THIS ADDS
**`gfx_pc.c` is GITIGNORED.** Parts 2, 3 and the census live in it, so
**`tools/fetch-thirdparty.sh regen` must run before the native half is committed**, or
they are recorded nowhere. Part 1 is in the decomp repo and commits normally.
