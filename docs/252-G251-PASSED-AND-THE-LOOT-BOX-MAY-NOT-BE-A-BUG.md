# 252 — `G-251` PASSED. AND THE LOOT BOX MAY NOT BE A BUG.

**2026-08-29. Phase A. Docs run to `252`. NEXT DOC = `253`.**

> # ►►►►►► **THE EXPLOSION CRASH IS FIXED.** ◄◄◄◄◄◄
> `[REPORTED]` ***"Done, it didn't crash."*** — after shooting the console
> computer and letting it explode, the step that killed every previous build.

---

## §1 — PHASE A's CRASHES ARE BOTH CLOSED

| crash | site | fix | state |
|---|---|---|---|
| inventory cycle | `bondviewSelectCuff` -> `modelGetNodeRwData+0x8` | `GETV_CUFFIDX` — `&switches[i]` instead of a 4-byte stride | **`G-250` PASSED** |
| explosion | `objDeform+0x167` | `GETV_RWSTRIDE` — the word-indexed rwdata pool at four sites | **`G-251` PASSED** |

**And the slow pickup went with the first one** (`251` §1): *"pick up the weapon
INSTANTLY"*.

> **Two crashes, two strides, both in the same disease: THE DECOMP ENCODES POINTER
> SIZE IN ARITHMETIC** (`251` §6). **`ALIGN64_V2` at `front.c:8517` is the third
> instance, located and still unfixed.**

---

## §2 — THE PURPLE EXPLOSION IS EXPECTED, NOT A REGRESSION

`[REPORTED]` ***"Explosions still purple/sparkly colors."***

**`GETV_RGBA16BE` has been COMMENTED OUT of `goldeneye.cfg` since `239` §3**, and
`237` `[MEASURED]` that `=1` is what fixes the flare. **This is the configuration
behaving as set.** `244` explains why it is not a global default: the fault is
per-asset PROVENANCE — an extracted `u32[]` C array is byte-reversed in 4-byte
groups, a texture read straight from the ROM is not, **and no single renderer mode
can be right for both.**

**Nothing to do here until the asset side is normalised at ingest** (`244` §4).
**Turning the knob back on is a per-run choice when an explosion is the subject.**

---

## §3 — ►► THE LOOT BOX. READ THE CODE FIRST. `236` COST SIX DOCUMENTS. ◄◄

`[REPORTED]` ***"The box gave me grenades, mines, two different sets of mines,
and throwing knives."***

`[READ]` `bondtypes.h:3443`:
```c
struct multiammocrateslot { u16 modelnum; u16 quantity; };

typedef struct MultiAmmoCrateRecord {
    inherits ObjectRecord;
    struct multiammocrateslot slots[AMMOTYPE_GLOBAL_MAX];
} MultiAmmoCrateRecord;
```
`[READ]` `propobj.c:11233`, `PROPDEF_AMMO`: it walks **every slot** and hands over
each one whose `quantity > 0`.

`[READ]` `bondconstants.h:4115`, the ammo types themselves:
```
AMMO_NONE, …, AMMO_RIFLE, AMMO_SHOTGUN, AMMO_GRENADE, AMMO_ROCKETS,
AMMO_REMOTEMINE, AMMO_PROXMINE, AMMO_TIMEDMINE, AMMO_KNIFE,
AMMO_GRENADEROUND, AMMO_MAGNUM, AMMO_GGUN
```

> ## **GRENADES, THREE SEPARATE MINE TYPES AND THROWING KNIVES ARE ALL LEGITIMATE
> ## AMMO TYPES, AND A MULTI-AMMO CRATE IS BUILT TO DISPENSE SEVERAL AT ONCE.**
> **"Two different sets of mines" is `AMMO_REMOTEMINE` and `AMMO_PROXMINE`, or
> either with `AMMO_TIMEDMINE`. THAT IS WHAT THE RECORD IS FOR.**

**`[ASSUMED]` — and deliberately not investigated — that this crate is wrong.**
**Nothing read so far says it is.** The propdef layout for this record
(`ge_propdef_layout.inc.c`: `{0,0,16}, {24,32,80}, {112,128,68}`) is GENERATED and
its header states it was checked three ways; **no evidence contradicts it.**

### §3.1 — THE CHECK IS FREE AND IT IS NOT A CODE HUNT

> **`236` is the precedent: six documents of correct measurements answered the
> wrong question, because nobody read the code that decides whether to produce the
> output. The rule from it applies here exactly.**

**Open the same crate in the real game and see what it gives.** The owner has
**MGB64 with the same ROM** (`235`), which is a second implementation and a free
control. **Only if the sets differ is there anything to chase.**

**AND STATE WHAT "WRONG" WOULD MEAN BEFORE LOOKING:** a crate handing out ammo for
weapons that do not exist in the level, or quantities of zero, or the SAME type
twice — **not merely "more kinds than I expected".**

---

## §4 — WHERE PHASE A STANDS

| item | state |
|---|---|
| **A1** resolve the crash | **DONE** — both of them (`248`, `249`, `250`, `251`) |
| **A2** prototype/stride sweep | **STARTED.** Three instances found; **`ALIGN64_V2` unfixed; the mechanical sweep of `<< 2` / `* 4` / `+= 4` / `(u32)` over pointers IS NOT DONE** |
| **A3** the `-1` enum sweep | **NOT STARTED**, and `249` removed its supporting evidence — the fault addresses were non-canonical, not sentinels. **Still worth doing on its own merits; no longer urgent** |
| **A4** ammo re-pickup, loot box | **loot box: §3 says verify before investigating.** Ammo re-pickup still unmeasured |

**THE COMMIT IS DUE AGAIN** — `247`-`252`, both fixes, `HANDOVER.md` and
`00-START-HERE.md`.

## §5 — WHAT IS NOT CLAIMED

- **`GETV_RWSTRIDE`'s other three sites are still reasoned, not measured**
  (`251` §7). Only `propobj.c:7750` had a crash behind it.
- **No claim the loot box is correct** — only that nothing read so far says it is
  wrong, and that §3.1 is cheaper than any code hunt.
- **`[REPORTED]` the ammo re-pickup fault has not been re-tested since `243`.**
  It may already be fixed by `250` or `251` and nobody has looked.

---

## §6 — HOW THE LOOT BOX BECAME A BUG. IT WAS NEVER ESTABLISHED AS ONE.

**The owner asked where the belief came from. Traced, with the documents:**

**1. THE ORIGINAL REPORT WAS HEDGED, AND I STRIPPED THE HEDGE.**
`[REPORTED]`, after `G-241`: ***"I picked up the ammo box, and I THINK it gave me
two different types of mines."***
`243` §1 records it as a flat table row — ***"when I get the loot box it gives me
grenades and mines"* | PERSISTS. NOT MINE.** — **an uncertain observation promoted
to a confirmed fault by being put in a table with two real crashes.**

**2. IT INHERITED THE STATUS OF ITS NEIGHBOURS.**
It arrived in the same sentence as a failed weapon pickup and a crash, in a run
where everything the owner touched was broken. **I never once asked what an ammo
crate is SUPPOSED to give.** `243` §1 then generalised all three into
*"pre-existing port faults, uncovered because this is the first session to play
far enough into a level"* — **which is true of the two crashes and assumed of the
third.**

**3. THEN I FOUND A COINCIDENCE AND USED IT AS CORROBORATION.**
`243` §2 noted `rbx = 0x1d` = 29 = `ITEM_PROXIMITYMINE` and called it
*"consistent"* with the report. **A register happening to hold 29 during an
inventory walk is not evidence of anything**, and `249` later `[MEASURED]` that
crash to be a non-canonical pointer with no sentinel in it at all. **The
corroboration was retracted by a later document and the belief it propped up was
not.**

**4. AND THE READ THAT SETTLED IT TOOK TEN SECONDS** (§3): one struct definition
and one enum. **It was available from the first minute and nobody asked for it.**

> ## ►► THE RULE, AND IT IS `236` §2.2 AGAIN, EIGHT DOCUMENTS LATER. ◄◄
> **`236`: *"BEFORE INSTRUMENTING A MISSING OUTPUT, READ THE CODE THAT DECIDES
> WHETHER TO PRODUCE IT."* That was written about the menu text after six
> documents were spent on a non-bug. THE SAME ERROR WAS REPEATED HERE ON THE
> SAME DAY.**
>
> **SO THE RULE NEEDS THE HALF THAT WAS MISSING:**
> **AN OBSERVATION REPORTED ALONGSIDE A GENUINE FAULT IS NOT ITSELF A FAULT.**
> **Write down what CORRECT would look like before calling anything a symptom** —
> §3.1 does that for the crate, and doing it in `243` would have cost one sentence
> and closed the item on the spot.
>
> **AND KEEP THE WEARER'S HEDGES.** *"I think"* is data. `182` tiers claims by
> evidence; **a report's own uncertainty deserves the same treatment, and flattening
> it into a table is how a maybe becomes a fact.**
