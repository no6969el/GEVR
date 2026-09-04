# 263 — THE 1x1 TEXTURES ARE RETAIL. FOUR THEORIES DEAD. THE SEARCH SPACE IS THE COLOUR COMBINER.

**2026-08-29k. All `[MEASURED]`. No fix written — this doc exists so the next
session does not re-chase any of the four dead ends below.**

---

## §1 — THE SYMPTOM LIST WAS WRONG, AND IT WAS MINE

`261` §3 wrote: *"Every character the owner photographed as black-faced is a
`rec=155`, `head=-1` self-contained body... The split is total across eleven
characters with no exceptions."*

**`[REPORTED]`, owner, correcting it:** *"They're all not blackface. Only, I
think, one of them has a blackface, and then one of them is missing their shirt
texture. Those are the two problems."*

> ### **THERE ARE TWO FAULTS, NOT A CLASS OF EIGHT.**
> - **`CorumovZ` — the SHIRT surface is black.**
> - **One Trevelyan model — the FACE is black.** (`CtrevelyanZ` body=8 or
>   `CboilertrevZ` body=9; not yet distinguished.)
> - **Everything else in the cast renders correctly.**

**I had TWO screenshots. I found a property those two shared, checked it against
a log, and wrote up an eleven-character "total split with no exceptions" without
ever having seen the other nine.** That is an `[INFERRED]` pattern stated as
`[MEASURED]`, which is the precise failure `182` exists to prevent.
**`HANDOVER` §5 again — and note the shape: the owner's correction did not add a
fault, it REMOVED six I had invented.**

## §2 — AND THE CORRECTION IMMEDIATELY PAID

With the real symptom list, the same log that looked like noise became a signal.
`[MEASURED]` `run_texbind.log`, `GETV_TEXBIND=1`:

**`texnum=1917` is bound by exactly ONE model in the entire run — `CorumovZ` —
and resolves `1x1 gbifmt=2 depth=0`.** One unique degenerate texture, one unique
missing surface, one model. **Against a list of eight that correlation was
invisible; against a list of two it is unmissable.**

## §3 — BUT 1x1 IS **CORRECT**. THE ROM SAYS SO.

`[MEASURED]` `imagelist.u.csv` — the game's OWN image table — lists exactly
thirteen images of 20 bytes or less. The **12-byte** ones are:

```
1514  1604  1608  1671  1725  1867  1917  2057
```

`[MEASURED]` the degenerate texnums in the whole run:

```
1514 (all six weapons)   1604 (CdjbondZ)   1608 (CheadbrosnanZ, ...boiler, CjawsZ)   1917 (CorumovZ)
```

> ## **EVERY DEGENERATE BIND IS ONE OF THE ROM'S GENUINELY-12-BYTE IMAGES.**
> **The table's offsets are self-consistent (`11517288 + 12 = 11517300`), so the
> extraction followed the ROM faithfully. A 12-byte image is a header with no
> pixel data: a 1x1 flat-colour placeholder, exactly as Rare shipped it.**

### **`DEGENERATE_1x1` IS NOT A FAULT INDICATOR. DO NOT CHASE IT A FOURTH TIME.**
`CheadbrosnanZ` binds 1608 seven times and renders perfectly, which was the
counter-example available from the start.

## §4 — WHAT THIS TURNS THE PROBLEM INTO, AND IT IS BETTER

**A 1x1 texture is HOW THE HARDWARE PAINTS A FLAT-COLOURED SURFACE** — one texel,
modulated by the primitive or shade colour, filling the polygon. Ourumov's olive
shirt is drawn that way by design.

> ## **THE TEXEL IS RIGHT. THE COLOUR COMBINED WITH IT IS COMING OUT BLACK.**

**One mechanism covers both symptoms:** a flat-shaded surface rendering black
while correctly-textured hair and hands on the SAME model are fine. Alec's face
has the identical shape — hard-edged, flat, black, adjacent to correct texture.
**`[INFERRED]`, `182`, may not be built on** — but it is the first hypothesis
today that explains both faults with one cause and contradicts nothing measured.

**Supporting, already in every frame line:** `shadea_cc=6444`, and
`cvgsel cvg_sel_draws=29268 forced_opaque=29268`. The combiner is doing
non-trivial work on these draws.

### THE NEXT INSTRUMENT, AND ITS FALSIFICATION CONDITION
**For a draw that binds a 1x1 texture, report the combiner mode and the prim/env/
shade colour.** If prim comes back zero, or the combiner selects an input the
hardware would not, that is the bug and it is one fix for both characters.
**IT MUST BE ABLE TO SAY I CANNOT ANSWER THIS:** if the 1x1 draws come back with
a sane non-black prim colour, this hypothesis is dead and the fault is in
geometry or lighting instead. **State that before the run** (`48`, rule 15).

## §5 — FOUR THEORIES DEAD, ALL MEASURED. DO NOT REOPEN WITHOUT NEW DATA.
| theory | killed by |
|---|---|
| missing / unextracted assets | `miss=0` and `0 MISSING` on every `texbind`/`modeltex` line |
| texture bind misses | `ge_texbind_miss = 0` for the whole run |
| degenerate 1x1 textures | §3 — they are RETAIL; and `CboilertrevZ`/`CnatalyaZ` have ZERO degenerates while rendering wrong |
| CI / TLUT / palette | `ci_decodes=0` throughout |

## §6 — THE REPRO RECIPE, `[REPORTED]` BY THE OWNER
**Worth an entry of its own: it costs an hour to rediscover.**
- **Touch nothing from boot -> the character cast roll plays.**
- **Skip ANY intro video — even leaving the gunbarrel scene — and it goes STRAIGHT
  to the menu**, cast roll never runs.
- **From the menu, idle -> the loop restarts, and then loops forever.**
- **It never reaches a gameplay demo because `select_ramrom_to_play`,
  `get_is_ramrom_flag`, `check_ramrom_flags` and
  `clear_ramrom_block_buffer_heading_ptrs` are all `[getv] STUB:` in this port.**
  The owner's *"it's supposed to do it once and then go to the gameplay videos"*
  is correct and the cause is named. **Not started.**

## §7 — NOT CLAIMED
- No claim about WHY the combiner colour is black; §4 names the read.
- Which Trevelyan model is the black-faced one is **not yet distinguished**.
- No claim the two faults share a cause — `[INFERRED]` only, and the probe in §4
  is what would establish it.
