# 233 — THE CAST CRASH: TEN SLOTS, AND A FREE THAT DOES NOTHING

**2026-08-28. `GETV_MPCHR` + `GETV_RECTTRACE` run. Docs run to `233`. NEXT DOC = `234`.**

> # ►►►► **ROOT CAUSE, `[MEASURED]` THEN `[READ]` TO THE LINE.** ◄◄◄◄
> **`clear_aircraft_model_obj()` sets `Model.obj = NULL`. On the N64 that FREED the
> slot, because the free test was `unk08 == 0` and `unk08` ALIASED `Model.obj`. At
> 64-bit the alias is gone, the port replaced the test with a `ge_inuse` byte —
> AND NOTHING EVER CLEARS IT. The free became a no-op.**
>
> **Ten anim slots exist. Ten cast characters got one. The eleventh got NULL, and
> `front.c:8560` dereferenced it.**

---

## §1 — THE MEASUREMENT, AND IT FALSIFIES `232` §3.3

`[MEASURED]` `run_mp.log`, 20:16:46, `GETV_MPCHR=1 GETV_RECTTRACE=1`, both
read-only. **Every `[mpchr]` line, in order, by its `model=` pointer:**

```
1  00007ff64b73b9b0   body=5(CdjbondZ)        head=78
2  00007ff64b73bb78   body=22(CboilerbondZ)   head=74
3  00007ff64b73bd40   body=16(CnatalyaZ)      head=-1   <-- succeeded
4  00007ff64b73bf08   body=9(CboilertrevZ)    head=-1
5  00007ff64b73c0d0   body=11(CxeniaZ)        head=-1
6  00007ff64b73c298   body=7(CorumovZ)        head=-1
7  00007ff64b73c460   body=6(CborisZ)         head=-1
8  00007ff64b73c628   body=10(CvalentinZ)     head=-1
9  00007ff64b73c7f0   body=19(CgreatguardZ)   head=69
10 00007ff64b73c9b8   body=22(CboilerbondZ)   head=74
11 0000000000000000   body=16(CnatalyaZ)      head=-1   <-- NULL. CRASH.
```

### `232` §3.2 IS CONFIRMED
`model=0000000000000000 rwdatalen=-1` on the crashing line, then
`EXCEPTION 0xc0000005, fault addr 0x28, rcx=0`. **`front.c:8560`
`modelSetScale((Model *) cast_model, 0.1f)` on a NULL model, at `Model->scale`,
native offset `0x28`.** The predicted value and the observed fault agree.

### `232` §3.3 IS FALSIFIED, BY ITS OWN INSTRUMENT
**`head = -1` IS NOT THE DISCRIMINATOR.** Line 3 is **the same body 16
`CnatalyaZ` with the same `head=-1`, and it succeeded.** Five more head-less
bodies (9, 11, 7, 6, 10) succeeded too. **The counter-example search in `232` §3.3
said it was "a lead, not a mechanism"; it was tiered `[INFERRED]` and it cost
nothing to drop.**

### WHAT THE POINTERS SAY INSTEAD
**`[MEASURED]` the delta between consecutive models is `0x1c8` EVERY TIME, ten
times.** A bump allocator marching forward through a fixed array, **never
reusing a slot**. The eleventh call finds nothing.

---

## §2 — THE ARITHMETIC MATCHES EXACTLY. TEN IS NOT A COINCIDENCE.

`[READ]` `prop.c:2452-2453`, the front-end path:
```c
modelmgrAllocateModelSlots(0);
modelmgrAllocateAnimModelSlots(0);
```
`[READ]` `initunk_005520.c:81`: `g_MaxAnimModelSlots = numanimated + ANIM_MODEL_SPARE_SLOTS`,
and `#define ANIM_MODEL_SPARE_SLOTS 10`.

> **`0 + 10 = 10` SLOTS. TEN SUCCEEDED. THE ELEVENTH FAILED.**

---

## §3 — AND HERE IS WHY NOTHING IS EVER REUSED

`[READ]` `front.c:8648-8650`, the cast's own release, called for every character:
```c
if (cast_model != 0) {
    clear_aircraft_model_obj(cast_model);
}
```
`[READ]` `model.c:258`:
```c
void clear_aircraft_model_obj(Model *objinstance) { objinstance->obj = NULL; }
```

**On the N64 that IS the free.** `[READ]` `model.c:95`, the non-native predicate:
```c
#define GE_ANIMSLOT_FREE(slot) ((slot).unk08 == 0)
```
and `objecthandler.h`'s own comment: *"the N64 layout made `unk08` alias
`Model.obj` (the in-use marker)"*. **Clearing `obj` cleared `unk08` cleared the
slot. One store, two meanings, by layout.**

**At 64-bit the alias is gone** — `Model.obj` is at 0x10, `AnimModelSlot` is
padded by 256 bytes and carries its marker past the padding — so the port
substituted its own predicate, `model.c:92`:
```c
#define GE_ANIMSLOT_FREE(slot) ((slot).ge_inuse == 0)
```

### ►► `ge_inuse` IS SET IN TWO PLACES AND CLEARED IN TWO, AND NEITHER IS A FREE ◄◄

`[READ]`, every occurrence in the tree:

| site | what it does |
|---|---|
| `model.c:157` | `ge_inuse = 1` — claim a **model** slot |
| `model.c:237` | `ge_inuse = 1` — claim an **anim** slot |
| `initunk_005520.c:62` | `ge_inuse = 0` — **pool allocation**, once |
| `initunk_005520.c:96` | `ge_inuse = 0` — **pool allocation**, once |

> **THERE IS NO RELEASE PATH. `ge_inuse` IS A ONE-WAY RATCHET.**
> `clear_aircraft_model_obj` and `clear_model_obj` still clear `obj`, exactly as
> they always did — **and on this port that no longer means anything.**

**`[INFERRED]` this affects far more than the intro cast.** Counter-example
search: `clear_aircraft_model_obj` has **8 call sites** (`chr.c:2012`,
`front.c:2244`, `front.c:8649`, `propobj.c:783`, `:1117`, `title.c:567`) and
`clear_model_obj` **10 more** — every one is a free that no longer frees. **The
intro is simply the first place that recycles more than ten times in a row.**
**The one thing that would falsify a general leak is a call site whose slot IS
reused, and none was found.**

## §3.1 — THIS IS THE SAME BUG FAMILY THE TREE ALREADY DOCUMENTS, ONE LAYER DOWN

`[READ]` `initunk_005520.c`'s own header comment describes the previous instance:
> *"the spare-slot pools below were sized for the N64 totals, so
> `modelmgrInstantiateModelWithAnim()` found no slot ... returned NULL, **and the
> gun barrel intro dereferenced it (`chrModelInstance == 0x0`)**"*

**That was fixed by scaling the rwdata pools ×3 — a SIZE fix.** This one is not a
size fault: **ten slots is the correct number; they are simply never given back.**

---

## §4 — THE FIX. NOT WRITTEN, BECAUSE THE OBVIOUS ONE IS WRONG.

**The naive fix — clear `ge_inuse` inside `clear_*_model_obj` — cannot be written
directly**: both functions take a `Model *`, and `ge_inuse` sits at a **different
offset** in `ModelSlot` (past `ge_model_pad[320-40]`) than in `AnimModelSlot`
(past `ge_anim_pad[256]`). **A `Model *` does not say which pool it came from, and
writing the wrong offset corrupts the neighbouring slot** — precisely the class of
fault `objecthandler.h`'s padding exists to prevent.

**THE CANDIDATE THAT AVOIDS THE AMBIGUITY: resolve the pool by ADDRESS.** Both
pools are contiguous arrays with known bases and counts
(`g_ModelSlots`/`g_MaxModelSlots`, `g_AnimModelSlots`/`g_MaxAnimModelSlots`), so a
range test names the slot type with no aliasing and no new field:

```
ge_slot_release(Model *m):
    if m within g_AnimModelSlots[0 .. g_MaxAnimModelSlots)   -> that slot's ge_inuse = 0
    else if m within g_ModelSlots[0 .. g_MaxModelSlots)       -> that slot's ge_inuse = 0
    else                                                      -> not pooled; do nothing
```
called from both `clear_model_obj` and `clear_aircraft_model_obj`, **behind
`GETV_SLOTFREE` (default ON, `=0` reverts)** so the old behaviour stays reachable
per DELETE NOTHING.

**GATE `G-233`: the intro plays past the eleventh cast character without
crashing**, and `GETV_MPCHR` shows **model pointers REPEATING** rather than
ascending — which is the measurement, not the absence of a crash.

**NOT WRITTEN YET, and deliberately: this is one behaviour change and it should
be the only one in its run** (`48`), and it touches a free path used by 18 call
sites across the game.

---

## §5 — THE FILL RECTANGLES, RECORDED NOT CONCLUDED

`[MEASURED]` `GETV_RECTTRACE` captured its full 200-line budget, and **every
single one is the same shape**:

```
[getv][rect] #4 zclear=0 px=(0,0)-(439,329) fill=0xff000000 cyc=3
             z_cmp=0 z_upd=0 scissor=(0,0 0x0) native=440x330
```

**A FULL-SCREEN OPAQUE BLACK FILL AT EXACTLY THE MENU'S 440x330**, in
`G_CYC_FILL`, over and over. **That is the shape of the overdraw candidate `232`
§2.1 named — but this log CANNOT establish ordering against the glyph texrects,
because `GETV_RECTPROBE` was off for this run.** A per-frame clear that runs
BEFORE the text is correct and expected; the same rectangle AFTER it is the fault.

**`scissor=(0,0 0x0)` in all 200 lines is noted and not chased** — the probe's
budget is spent on early frames, before the first `SETSCISSOR`.

> **THE A/B IS ONE RUN, NO REBUILD: `GETV_NOFILLRECT=1`.** If the menu text
> appears with fill rectangles dropped, it was being covered. If it does not, fill
> overdraw is excluded and a TEXTURED rectangle drawn over it is next.
> **It is a behaviour change and travels alone.**

---

## §6 — PROVENANCE. WHOSE BUGS ARE THESE?

**The owner asked whether the upstream port has these problems. `[READ]` from the
repository itself:**

- **`origin` is `https://github.com/SegfaultEvan/goldeneye-native`, and
  `origin/main` is `d0e0569`.**
- **Our tree carries exactly ONE commit on top of it: `6665fc6` "Phase 0: native
  port links, boots and plays"** — the `-mwindows` strip, `-GuiSubsystem`, the
  materialised `PR/` headers, and `port_audio.c`'s queue depth. **`git show
  --stat` confirms it: 23 files, and 21 of them are copied-in headers.**
- **`origin/windows-bringup` is IDENTICAL to `origin/main`** — `git rev-list
  --count` is **0 in both directions. There is no better Windows branch we are
  missing.**

> ## ►► SO EVERY FAULT IN `230`-`233` IS IN UPSTREAM'S CODE, NOT IN OUR CHANGES. ◄◄
> **`ge_inuse` is upstream's. `GETV_MPCHR`, `GETV_RECTTRACE`, `GETV_LIGHTTRACE`
> and `GETV_TRIWHERE` are upstream's instruments** — the three "already built,
> never run" probes this project keeps finding were all written by him.
> **`ge_inuse` never being cleared is platform-independent C: it will bite macOS
> exactly as hard.**

### AND `[READ]` WHY IT MAY NOT HAVE BITTEN HIM YET

`docs/ROADMAP.md:40` and its division-of-labour table, in upstream's own words:

> *"**The Surface renders at roughly one frame per second.** It cannot measure
> anything at runtime"*

| machine | what it owns |
|---|---|
| **Mac** | *"anything needing a running game"* — bots, co-op, the CLI, measurement |
| **Surface** | *"anything offline"* — extraction, audits, tests, **Windows**, the launcher, netplay |

**`[INFERRED]` upstream's Windows target is BUILT and AUDITED but not PLAYED**;
runtime verification happens on the Mac. **Counter-example search: the README does
claim Windows "Builds and plays", and `origin/windows-bringup` exists — so Windows
has been run at least once. The claim here is about DEPTH of runtime exercise, not
about whether it starts.** **The control that would settle it is a macOS run of
the same intro, which this project cannot perform.**

## §6.1 — AND A HAZARD THE COMMIT POLICY HAS TO KNOW ABOUT

**`[MEASURED]` `git check-ignore -v` says `getv/port/fast3d/gfx_pc.c` is IGNORED**
(`.gitignore:156`). `[READ]` the reason is licensing, stated in `.gitignore` and
`docs/LICENSING.md` §4: **fast3d is fetched from a pinned sm64ex commit by
`tools/fetch-thirdparty.sh` and is never vendored; upstream's own changes to it
live as a patch series in `getv/patches/thirdparty/`.**

> **THEREFORE `231`'s `GETV_RECTPROBE` IS NOT COMMITTABLE AS A FILE EDIT AND
> `commit-session.ps1` WILL SILENTLY MISS IT.**
> **The mechanism that preserves it is `tools/fetch-thirdparty.sh regen`, which
> regenerates `0001-getv-port-layer.patch` from the working tree.**
> **Any fast3d change this project ever makes has to end in a `regen`, or a fresh
> clone loses it — the same shape of trap as `229` §9's CRLF, and it fails
> silently in the same way.**

---

## §7 — WHAT IS NOT CLAIMED

- **No fix is on disk.** §4 is a design, and its ambiguity is the reason it is not
  code yet.
- **Nothing about the menu text is concluded.** §5 is a rectangle, not a verdict,
  and `232` §2.1's question to the wearer is still open.
- **`[ASSUMED]` that the intro is the only place the slot leak has already bitten.**
  It is the first found, not the only one; §3's 18 call sites are the search space.

---

## §8 — TWO WEAR REPORTS, ADDED AFTER THE RUN ABOVE

**`[REPORTED]` `232` §2.1's open question is ANSWERED: THE MENU TEXT IS STILL
MISSING** on a plain launch (no `GETV_*` at all) of the 20:07:50 binary.

> **So the glyph is delivered correctly and then not seen. `232` §2 exonerated
> every field of the texrect; `233` §5 found a full-screen opaque black fill at
> exactly the menu's 440x330. OVERDRAW IS THE ONLY CANDIDATE LEFT STANDING, and
> `GETV_NOFILLRECT=1` is its one-run A/B.**

**`[REPORTED]` AND THE WRONG-SFX SYMPTOM NOW HAS A REPRODUCIBLE PATH** — *"click
the copy button on the bottom and hit B to back out ... it plays a machine gun
noise."* **`229` §20 item 2 has been `[UNDIAGNOSED]` and never run since it was
written; this is the first time it has come with an exact button sequence.**
`GETV_AUDIO_DEBUG=1` + `GETV_AUDIO_TESTSFX=<id>` is built and still never run.
**It is a behaviour change and does NOT travel with `GETV_NOFILLRECT`.**
