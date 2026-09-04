# 250 — A FOUR-BYTE STRIDE OVER EIGHT-BYTE POINTERS

**2026-08-29. Phase A. Docs run to `250`. NEXT DOC = `251`.**

> # ►►►►►► **`bondviewSelectCuff` INDEXES A `ModelNode **` BY FOUR BYTES.** ◄◄◄◄◄◄
> **At 64-bit the entries are eight, so `base[0]` loads eight bytes STRADDLING TWO
> ENTRIES — the low half of one pointer and the high half of its neighbour.**
> **THAT IS THE ROTATED POINTER `249` §3 could only describe as a shape.**
>
> ## **AND THE OWNER CALLED IT: *"something with the ordering or, like, the
> ## numbers when it has to reset it and something's not matching."***

---

## §1 — THE FULL CALL CHAIN, RESOLVED

`[MEASURED]` `run_watch.log` 02:59, the crash reproduced deliberately with no
explosion in the run. Every frame resolved against `goldeneye.map`:

```
main -> SDL_main -> bossMainloop -> lvlRender -> maybe_mp_interface
     -> gunUpdateAndFireBothHands -> gunUpdateAndFire
     -> bondviewSelectCuff +0x40
     -> modelGetNodeRwData  +0x8      <-- FAULT
```

`[MEASURED]` the registers at the fault, Win64 ABI (`rcx` = arg1, `rdx` = arg2):
```
rcx = 0x00007ff6f8334800    Objinst -- a good Model pointer (== rbp)
rdx = 0xf8b9b52800007ff6    root    -- 0x00007ff6f8b9b528 WITH ITS HALVES SWAPPED
```
**`modelGetNodeRwData+0x8` is `switch (root->Opcode & 0xff)`, the first
dereference of `root`.**

**AND `[MEASURED]` ZERO `[getv][watchmdl]` LINES in a run that DID reach the
crash** — so `248` §3's watch hypothesis is now properly **FALSIFIED**, not merely
untested as in `249` §4. **The watch render never executes; the cuff does.**

---

## §2 — THE DEFECT, IN ONE LINE

`[READ]` `bondview2.c:9105`:
```c
ModelNode **switches = header->Switches;
offset = switchindex << 2;                                  /* switchindex * 4 */

// byte-indexed on purpose: offset = switchindex * 4. &switches[i] won't match.
base = (ModelNode **) (((u8 *) switches) + offset);
```

**On the N64 a `ModelNode *` is FOUR bytes, so `switches + switchindex*4 bytes`
IS `&switches[switchindex]`, exactly. The comment is right — for the N64.**

> ## ►► NATIVELY THE ENTRIES ARE EIGHT BYTES, SO A FOUR-BYTE STRIDE LANDS HALF
> ## WAY INTO ONE. ◄◄
> `base[0]` then reads **the top four bytes of entry `k` followed by the bottom
> four bytes of entry `k+1`** — which for two neighbouring heap pointers
> `0x00007ff6_xxxxxxxx` produces exactly `0xxxxxxxxx_00007ff6`.

**`0xf8b9b528_00007ff6` is not a corrupted pointer. It is TWO HALVES OF TWO
DIFFERENT, PERFECTLY GOOD POINTERS.** And `base[0] != NULL` passes, because that
value is not zero.

### §2.1 — AND IT EXPLAINS EVERY OBSERVATION

| `[REPORTED]` | explained |
|---|---|
| *"it doesn't do it when I just have one gun"* | `switchindex` is small; a straddle at index 0 still reads entry 0's low half plus entry 1's — **it depends on which switches exist** |
| *"only when I pick up the loot and not the guns"* | picking items up changes `switchindex` and the switch table |
| *"I had to switch a few times"* | the cuff is selected from `gunUpdateAndFire` — **it runs on the weapon path, every frame, for whatever is in hand** |
| `249`'s `objDeform` rotation | **a SECOND site of the same family** — see §5 |

---

## §3 — THE FIX

`[READ]` the same function recomputes `base` **six times**, after each refresh of
`switches = header->Switches`. All six now go through one macro:

```c
#ifdef GE_PORT_NATIVE
#define GE_CUFF_BASE(sw, idx, off) \
    (geCuffIdx() ? &(sw)[(idx)] : (ModelNode **) (((u8 *) (sw)) + (off)))
#else
#define GE_CUFF_BASE(sw, idx, off) ((ModelNode **) (((u8 *) (sw)) + (off)))
#endif
```

**`&switches[switchindex]` is byte-identical to the old expression on the N64 and
correct on both**, so `225`'s matching-ROM gate cannot move — and the non-native
arm keeps the original text verbatim so the decomp still reads as it did.

**`GETV_CUFFIDX=0` reverts all six sites on one binary.**

**`[MEASURED]` `bondview2.c` compiles clean under the Windows build's own game
flags.** *(The N64-only compile fails on `GE_ANIMOFF_ANIM_DATA_bond_watch` at
line 3589 — a pre-existing symbol that only exists under `GE_PORT_NATIVE`, at a
line this change does not touch.)*

---

## §4 — `G-250`. ONE BUILD, AND THE GATE IS THE ONE `242` §5 WROTE IN ADVANCE.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
cd C:\Users\<USER>\Desktop\GoldenEyeVR\goldeneye-native
& getv\build_windows.ps1 -Target all *> build.log 2>&1
cd getv\build-windows
$env:GETV_STAGE = "9"
.\goldeneye.exe *> run_cuff.log 2>&1
```

**THE STANDING GATE, unchanged from `242` §5 and stated before the run:**
1. **pick up a dropped weapon** — and note whether it is quicker than before
2. **pick up an ammo box / loot** — and **read what it actually gives you**
3. **cycle every weapon twice, all the way round, past the detonator**
4. **shoot something explosive** — `249`'s `objDeform` crash
5. **`GETV_SLOTFREE` stays 0** in the cfg; one change per run

**`GETV_CUFFIDX=0` on the same binary is the A/B if anything looks worse.**
**A NEW `goldeneye.map` IS WRITTEN BY THIS BUILD — keep it with `run_cuff.log`**
(`206`), and the old map no longer resolves anything.

---

## §5 — WHAT THIS DOES *NOT* FIX, AND WHY IT MATTERS

**`249`'s `objDeform + 0x167` crash is a DIFFERENT SITE.** Its rotated value came
from `mov (%rsi),%rcx` — a pointer loaded out of a structure, not out of a
mis-strided array. **`[INFERRED]` it is the same FAMILY — a 4-byte stride or a
32-bit field where a 64-bit pointer now lives — but it has not been located, and
step 4 of `G-250` is what tells us whether it survives.**

> ## ►► AND THE REAL PRIZE IS THE SWEEP, NOT THIS FIX. ◄◄
> **`<< 2` over a pointer array is a MECHANICAL PATTERN.** `248` §4 already showed
> the build compiles with `-w`, so nothing has ever warned about any of it.
> **`251` should grep the tree for every `<< 2`, `* 4` and `+= 4` applied to a
> pointer-array base, exactly as `168` §5 says to grep the mechanism rather than
> the instance.** **`244`'s `ALIGN64_V2` truncation and this stride are the same
> disease at two different sites, and neither was found by looking for it.**

## §6 — WHAT IS NOT CLAIMED

- **`G-250` has not been run.** §2 is `[READ]` plus a register dump; the fix is
  `[READ]` plus a syntax check.
- **No claim this fixes the ammo re-pickup, the loot-box contents, or the slow
  pickup.** They are separate `[REPORTED]` symptoms and step 2 of the gate is
  what measures them.
- **`[ASSUMED]` the six sites are the only mis-strided ones in this function.**
  The sweep in §5 is what would establish it tree-wide.
