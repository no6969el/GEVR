# 251 — THE RWDATA POOL IS INDEXED IN WORDS, AND FOUR SITES DID NOT KNOW

**2026-08-29. Phase A. Docs run to `251`. NEXT DOC = `252`.**

> # ►►►►►► **`G-250` PASSED. THE CUFF FIX WORKS.** ◄◄◄◄◄◄
> `[REPORTED]` ***"I was able to pick up the weapon INSTANTLY and rotate through
> my inventory."***
> **Three of the four gate steps passed, including the slow pickup that `248` §6
> recorded and did not explain. Step 4 — the explosion — crashed exactly as
> `250` §5 predicted it would.**

---

## §1 — WHAT `G-250` SETTLED

| gate step | `[REPORTED]` |
|---|---|
| pick up a dropped weapon | ***"INSTANTLY"*** — **and the "not as quick as the normal game" symptom is gone with it** |
| cycle the whole inventory | ***"rotate through my inventory"*** — **no crash. `250`'s fix holds** |
| shoot something explosive | ***"shot the console computer, and it blew up... and then it crashed"*** |

**So `bondviewSelectCuff` was ALSO the slow pickup.** `[INFERRED]` the cuff select
runs from `gunUpdateAndFire` every frame; a straddled `base[0]` that happened to
be non-NULL but harmless would make that path do work it should not, and the
pickup path shares it. **Counter-example search: no measurement of the pickup
timing was taken before or after, so this is the only reading offered for it and
it is not established.**

---

## §2 — THE SECOND CRASH, RESOLVED — AND A LESSON ABOUT THE MAP

`[MEASURED]` `run_cuff.log`: `objDeform + 0x167`, **the same site as `249`**,
same instruction, same rotated register (`rcx = 0x21732330_00007ff7`).

> ## ►► THE ANCHOR MUST BE RE-READ FROM EVERY NEW MAP. ◄◄
> **The first attempt resolved this crash to `process_monitor_animation_microcode
> + 0x107`, which is WRONG.** `g_mempPools` moved from `0x140f803a0` to
> `0x140f813a0` in the rebuild, and the stale anchor shifted every answer by
> `0x1000`.
> **It was caught because the resolved address did not land on an INSTRUCTION
> BOUNDARY** — `objdump` showed it inside a 7-byte `movl`. **`206`'s rule needs
> this clause: the map is rebuilt with the binary, so re-read the anchor symbol
> from the NEW map, and verify the PC disassembles cleanly before believing the
> symbol.**

---

## §3 — THE DEFECT, AND THE TREE ALREADY CARRIED THE FIX

`[READ]` `propobj.c:7750`, in `objDeform`:
```c
vtxslot = (Vertex **) (&model->datas[rodata->RwDataIndex]);
```

`[READ]` `model.c:677`, in `modelGetNodeRwData`, written during the tvOS bring-up:
> *"the rwdata pool is indexed in N64 WORDS, not in pointers. `data` is declared
> `union ModelRwData **`, so `&data[index]` strides by sizeof(pointer) — 4 bytes
> on the N64, 8 here. But the pool's length is computed by
> `modelCalculateRwDataLen()` in 4-byte words and allocated as `numRecords * 4`,
> so a doubled stride walks straight off the end."*
```c
return (union ModelRwData *)&((u32 *)data)[index];
```

> ## **THE CORRECTION HAS BEEN IN THIS TREE SINCE THE BRING-UP. IT WAS APPLIED TO
> ## ONE ACCESSOR AND NOT TO THE FOUR SITES THAT INDEX THE SAME POOL DIRECTLY.**

`[MEASURED]` `grep -rn '\->datas\['` — **exactly four, and all four stride by
eight:**

| site | what it computes |
|---|---|
| `model.c:8939` | `rwdata->RwDatas = &pmodel->datas[numRecords]` — the head's rwdata start |
| `propobj.c:7404` | `rwdataSlot = &obj->model->datas[…RwDataIndex]` |
| **`propobj.c:7750`** | **`vtxslot` — the crash** |
| `propobj.c:14943` | `new_var = &s3->datas[s0->RwDataIndex]` |

**And `[READ]` `model.c:148` confirms the pool's unit: `mempAllocBytesInBank(((header->numRecords * 4) + 0xf | 0xf) ^ 0xf, …)` — `numRecords * 4`. FOUR-BYTE WORDS.**

---

## §4 — THE FIX

**One accessor in `model.h`, used at all four sites, behind `GETV_RWSTRIDE`
(default ON, `=0` reverts):**
```c
#ifdef GE_PORT_NATIVE
#define GE_RWDATA_SLOT(datasptr, idx) \
    (geRwStride() ? (void *) &((u32 *) (datasptr))[(idx)] \
                  : (void *) &(datasptr)[(idx)])
#else
#define GE_RWDATA_SLOT(datasptr, idx) ((void *) &(datasptr)[(idx)])
#endif
```
**On the N64 both arms are the same address**, and the non-native arm is the
original expression verbatim, so `225`'s matching-ROM gate cannot move.

**`[MEASURED]` all 135 `src/game/*.c` compile clean** under the Windows build's
own flags — swept in full because `model.h` changed and reaches every consumer.

---

## §5 — `G-251`. THE SAME STANDING GATE, PLUS THE EXPLOSION.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
cd C:\Users\pdbar\Desktop\GoldenEyeVR\goldeneye-native
& getv\build_windows.ps1 -Target all *> build.log 2>&1
cd getv\build-windows
$env:GETV_STAGE = "9"
.\goldeneye.exe *> run_rw.log 2>&1
```
1. pick up a dropped weapon — **still instant?**
2. **take an ammo box / loot and READ WHAT IT GIVES YOU** — still unmeasured
3. cycle the whole inventory twice
4. **shoot the console computer and let it explode** — the step under test
5. take damage, keep playing a while

**`GETV_RWSTRIDE=0` is the A/B on the same binary. `GETV_SLOTFREE` stays 0.**
**A NEW MAP IS WRITTEN — keep it with `run_rw.log`, and §2's rule applies.**

---

## §6 — THE PATTERN, AND WHY THIS IS THE VALUABLE PART

**Three defects now, one disease, all found in one evening:**

| site | the mistake |
|---|---|
| `bondviewSelectCuff` (`250`) | `switchindex << 2` — a 4-byte stride over 8-byte pointers |
| **`->datas[i]` at four sites (`251`)** | **an 8-byte stride over a 4-byte-word pool — THE SAME ERROR INVERTED** |
| `ALIGN64_V2` at `front.c:8517` (`248` §4.1) | a pointer forced through `(u32)` |

> **THE COMMON CAUSE IS THAT THE DECOMP ENCODES POINTER SIZE IN ARITHMETIC, AND
> `-w` MEANS NOTHING EVER WARNS** (`248` §4). **Two of the three were found only
> because a crash pointed at them.**

**`247`'s Phase A is not finished until the sweep is mechanical:** every `<< 2`,
`* 4`, `+= 4` and `(u32)` cast applied to a pointer or a pointer-array base.
**`168` §5: grep the mechanism, not the instance.** **`ALIGN64_V2` is still
unfixed and is the obvious next one, because it is already located.**

## §7 — WHAT IS NOT CLAIMED

- **`G-251` has not been run.**
- **`[ASSUMED]` all four `->datas[` sites are wrong.** `[READ]` says the pool is
  word-indexed and all four stride by pointer; **only `propobj.c:7750` is
  evidenced by a crash.** `GETV_RWSTRIDE=0` exists because the other three are
  reasoned, not measured.
- **The loot-box contents and the ammo re-pickup remain unmeasured** (`243` §1).
  **Step 2 of `G-251` is the first time anyone will have READ what the box gives.**
