# 261 — THE ELEVENTH IS JAWS, `GETV_SLOTFREE` WAS NEVER PARKED, AND THE BLACK FACES ARE NOT MISSING TEXTURES

**2026-08-29i. All `[MEASURED]` from `run_intro_crash.log` (16:45) and the owner's
screenshots. The intro was given a session, as the owner asked twice.**

---

## §1 — THE CRASH IS `233`, UNCHANGED, AND THE ELEVENTH CHARACTER IS JAWS

`[MEASURED]` the cast roll, in order, by `model=`:

| # | body | head | model |
|---|---|---|---|
| 1 | `CdjbondZ` | 78 `CheadbrosnanZ` | ok |
| 2 | `CboilerbondZ` | 74 | ok |
| 3 | `CnatalyaZ` | **-1** | ok |
| 4 | `CboilertrevZ` | **-1** | ok |
| 5 | `CxeniaZ` | **-1** | ok |
| 6 | `CorumovZ` | **-1** | ok |
| 7 | `CborisZ` | **-1** | ok |
| 8 | `CvalentinZ` | **-1** | ok |
| 9 | `CgreatguardZ` | 69 | ok |
| 10 | **`CmaydayZ`** | **-1** | ok |
| 11 | **`CjawsZ`** | **-1** | **`model=0000000000000000 rwdatalen=-1`** |

**`EXCEPTION 0xc0000005, fault addr 0x28, rcx=0`** at `front.c:8636`
`modelSetScale((Model *) cast_model, 0.1f)`.
**The owner's *"it crashes after Mayday"* is exact: Mayday is the tenth, Jaws is
the eleventh.** Ten slots (`ANIM_MODEL_SPARE_SLOTS 10`), ten succeed, the
eleventh is NULL. **`233` §1 and §2 reproduce line for line.**

## §2 — AND `GETV_SLOTFREE` WAS ON THE WHOLE TIME

`242` §2 parked it: *"`GETV_SLOTFREE = 0` in `goldeneye.cfg`. NO BUILD."*
**`[MEASURED]`, three ways, that this never took effect:**
1. `model.c:252` — `on = !(e && *e == '0')`. **Unset means ON.**
2. **There is no `goldeneye.cfg` beside the binary.** `ge_config.c:33` searches
   `<dir of argv[0]>/goldeneye.cfg`; `build-windows/` has none. The only cfg in
   the tree is `getv/goldeneye.cfg`.
3. **That file contains no `GETV_SLOTFREE` line anyway.**

> ### **SO THE SLOT FIX HAS BEEN ON IN EVERY RUN SINCE `234`, WHILE `HANDOVER`
> ### CARRIED "`GETV_SLOTFREE` PARKED OFF" AS A STANDING FACT ACROSS FOUR
> ### BANNERS.** Rule 10. **And rule 4 in its widest form: the configuration a
> ### run believes it has is part of the instrument.**

**Two consequences, opposite in sign:**
- **GOOD:** `242` turned it off for three gameplay faults — pickup needing a
  weapon-switch, an ammo box giving wrong items, a weapon-cycle crash. **`250`
  and `251` later fixed exactly those as independent pointer bugs**
  (`bondviewSelectCuff`'s `switchindex << 2`; `->datas[i]`'s 8-byte stride).
  `242` §1 suspected *"at least one MORE fault in the same change"* — **there
  was, and it was not in the change.** The slot fix was blamed for other bugs.
- **BAD, AND IT IS THE LIVE ONE: THE SLOT FIX IS ON AND THE CRASH STILL
  HAPPENS.** `233`'s release still is not returning slots to the pool.
  **`234`'s fix does not do what `233` said was needed.** That is the next read:
  `ge_slot_release()` (`model.c:262`) — does it run for the cast path at all, and
  does clearing `ge_inuse` actually make `GE_ANIMSLOT_FREE` true again?

## §3 — THE TEXTURES: **NOT** MISSING, AND `deg1x1` IS **NOT** THE ANSWER EITHER

`[MEASURED]` across the whole cast roll: **`miss=0` on every `texbind` line, and
`0 MISSING` on every `modeltex` line.** Every texture is resident in the pool and
every bind succeeds. **The black faces and the black shirt are NOT missing
assets, and `229` §12's finding holds: the assets are innocent.**

**`deg1x1` (degenerate 1x1 textures) climbs by roughly one per affected
character** — `CboilertrevZ` 12, `CxeniaZ` 13, `CorumovZ` 14, `CvalentinZ` 15,
`CmaydayZ` 17, `CjawsZ` 19 — **and it is tempting. IT IS ALSO FALSIFIED BY ITS
OWN DATA:** `run.log` shows **`CheadbrosnanZ` at `deg1x1=9`, seven of them its
own, and Bond's face renders correctly** in the owner's gunbarrel screenshot.
**A 1x1 texture is therefore not sufficient to produce a black face.**
`[INFERRED]` at best; **`182`; may not be built on.** Recorded so it is not
re-proposed as a mechanism without a counter-example search.

### THE DISCRIMINATOR THAT DOES SURVIVE, AND IT IS CLEAN
| renders correctly | renders black |
|---|---|
| `CdjbondZ`, `CboilerbondZ`, `CgreatguardZ` | `CboilertrevZ`, `CorumovZ`, `CxeniaZ`, `CnatalyaZ`, `CborisZ`, `CvalentinZ`, `CmaydayZ`, `CjawsZ` |
| `head=` a real model, `hasHead=0` | **`head=-1((none))`, `hasHead=1`, `headRoot=0000000000000000`** |
| `bodyRoot rec=153` | **`rec=155`** |

**Every character the owner photographed as black-faced is a `rec=155`,
`head=-1` self-contained body; every character that renders correctly is a
`rec=153` body with a SEPARATE head model.** The split is total across eleven
characters with no exceptions.

> **`232` §3.3 raised `head=-1`, `233` §1 correctly FALSIFIED it as the CRASH
> discriminator — and it was then dropped entirely. It is not the crash
> discriminator. It appears to be the TEXTURE one, and nobody tested it against
> that question.** `[INFERRED]`, one run from being settled.

**Also `[REPORTED]` and unexplained:** the gunbarrel's blood sits ON TOP of the
frame rather than inside it, and a black-and-grey fuzzy band runs across the top
of the window above Bond. **The band is consistent with `256`'s 440-byte one-row
I8 scanline wipe stepping a grey ramp** — the intro strips, `231` §4's fourth
branch. **Same screen, and probably the same fault. `GETV_RECTPROBE=1` reads it
and needs no build.**

## §4 — WHAT ELSE THIS SESSION SETTLED
- **`F2` IS FIXED.** `[MEASURED]` an empty `GETV_SAVEDIR` was written and read
  back at 512/512. `port_save.c`'s `MoveFileExA` replaces the failing POSIX
  `rename()`. **Open since the port began; the save now persists.**
- **`F1` IS FIXED, TWO CAUSES.** A fossil EEPROM (`260`), and `front.c:2452`
  passing two loose `f32*` where `projectRectCornersTo2D` requires `coord2d*`, so
  one edge of every folder's hit box was an adjacent stack local (`GETV_FOLDERBOX`).
  **`[REPORTED]` by the owner: folders and saves now work.**
- **`GETV_UNLOCKALL` V1 crashed the boot; V2 works.** Both causes in `file2.c`'s
  comment: passing `DIFFICULTY_007` to a function whose storage rejects it while
  its own bounds check accepts it, and calling slot-rotating wrappers ~400 times
  from inside `fileValidateSaves`. **`241`'s mistake, by me.**
- **AND I BROKE RULE 5**: the folder fix and the unlock fixture shipped in one
  build, so the black screen could not be attributed without the log.

## §5 — NOT CLAIMED
- No claim about WHY `234`'s slot release fails; §2 names the read, nothing more.
- **`deg1x1` is explicitly NOT claimed as the texture mechanism** — falsified by
  `CheadbrosnanZ`.
- `[INFERRED]` only: `rec=155`/`head=-1` as the texture discriminator; the top
  band as `256`'s scanline wipe.
