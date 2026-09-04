# 249 — `fault addr: ffffffffffffffff` MEANS NON-CANONICAL, NOT `-1`

**2026-08-29. Phase A. Docs run to `249`. NEXT DOC = `250`.**

> # ►►►►►► **BOTH CRASHES ARE ONE DISEASE: A STORED 64-BIT POINTER WITH ITS
> # TWO 32-BIT HALVES SWAPPED.** ◄◄◄◄◄◄
>
> **AND `243` §2 AND `248` §2 BOTH READ THE FAULT ADDRESS AS A `-1` SENTINEL.
> THAT IS RETRACTED. THE DISASSEMBLY SAYS OTHERWISE.**

---

## §1 — THE SECOND CRASH, RESOLVED

`[REPORTED]` ***"something exploded and my health bar came up and it crashed."***

`[MEASURED]` `run_watch.log`, delta anchored on `&g_mempPools` exactly as `248` §1:
```
FAULT PC (runtime) 0x00007ff6f753ae4a
FAULT PC (map)     0x00000001400aae4a
containing symbol  objDeform @ 0x1400aace3  (+0x167)
```
`[READ]` `propobj.c:7700`: *"objDeform - Deform an object due to it being
destroyed"*, called from `:8485` and `:8513` on explosion and gunfire. **The
symptom and the symbol agree.**

---

## §2 — ►► THE FAULTING INSTRUCTION, AND IT CHANGES THE DIAGNOSIS ◄◄

`objdump` at the fault PC:
```asm
1400aae47:  48 8b 0e             mov    (%rsi),%rcx            ; rcx = *rsi
1400aae4a:  48 8b 5c 01 08       mov    0x8(%rcx,%rax,1),%rbx  ; <-- FAULTS
```
with, from the register dump:
```
rsi = 0x00007ff6f8a117f8      <- a perfectly good address
rcx = 0xf8a1133000007ff6      <- what was LOADED FROM IT
rax = 0
```

> ## **`0xf8a11330_00007ff6` IS `0x00007ff6_f8a11330` WITH ITS TWO 32-BIT HALVES
> ## SWAPPED.** `rbp` is `0x00007ff6f8a11160`, a few hundred bytes away — **the
> ## correct pointer was in the right neighbourhood and arrived rotated.**

**The container is fine. The POINTER STORED INSIDE IT is wrong**, written as two
32-bit words in the wrong order.

### §2.1 — AND THAT IS WHY WINDOWS SAID `ffffffffffffffff`

`rcx + 8` is `0xf8a11330_00007ffe`. **Bits 63:48 are `0xf8a1`, which is not a sign
extension of bit 47 — the address is NON-CANONICAL.** On x86-64 a non-canonical
dereference raises **#GP, not #PF**, and there is no faulting address to report,
so Windows fills `ExceptionInformation[1]` with **all ones**.

> ## ►► `fault addr: ffffffffffffffff` IS NOT A VALUE THE PROGRAM COMPUTED. ◄◄
> **It is "there is no address", i.e. THE POINTER WAS GARBAGE IN THE HIGH BITS.**

**`243` §2 read it as a `-1` sentinel and reached for `ITEM_NOTHING = -1` and the
unsigned-enum trap. `248` §2 repeated that reading for
`modelGetNodeRwData + 0x8`. BOTH ARE WITHDRAWN.** The enum trap is real and still
worth sweeping (`247` A3) — **it is simply not what these two crashes are.**

**How it was caught: by disassembling instead of reasoning from the dump.** `48`
again, and the same shape as `189` §2 — **print the frame before hunting inside
it.**

---

## §3 — THE SAME SIGNATURE, NOW TWICE, IN TWO DIFFERENT SUBSYSTEMS

| crash | PC | the rotated register |
|---|---|---|
| inventory cycle (`243`, `248`) | `modelGetNodeRwData + 0x8` | `rdx = 0x0be1be88_00007ff6` |
| explosion (`249`) | `objDeform + 0x167` | `rcx = 0xf8a11330_00007ff6` |

**Two subsystems, two runs, the same malformation: `0x00007ff6xxxxxxxx` stored
with its halves exchanged.** **`[INFERRED]` a single mechanism is writing 64-bit
pointers into game structures as two 32-bit words in the wrong order.**

**Counter-example search, and it is not clean:** the port byte-swaps a great deal
of asset data on purpose (`244`; `vtxswap`, `texrow`, `ge_font_convert`), and any
of those passes could be walking a structure that — after the 64-bit port —
contains a REAL POINTER where the N64 had a 32-bit offset. **`244`'s rule in a new
costume: swap what is data, never what has become a pointer.** **But no specific
swapper has been identified, and until one is, this is a shape and not a
mechanism.**

---

## §4 — WHAT THE WATCH RUN DID *NOT* SHOW, STATED CAREFULLY

`[MEASURED]` **zero `[getv][watchmdl]` lines in `run_watch.log`.**

**`248` §5's table said that outcome would mean the watch path is not the crashing
one. THAT INFERENCE DOES NOT APPLY HERE, because this run crashed somewhere
else entirely** — `objDeform`, on an explosion — and `[REPORTED]` the owner
*"not sure if I made it all the way around the inventory"*. **The watch render was
never reached, so the instrument had nothing to print.**

> **`248` §3's watch hypothesis is NEITHER confirmed NOR falsified. It is
> UNTESTED, and `GETV_WATCHDBG=1` is still the way to test it — on a run that
> actually completes the inventory cycle without blowing anything up.**

---

## §5 — `G-249`. TWO RUNS, AND NEITHER NEEDS A BUILD.

**A — the inventory crash, cleanly, with the watch instrument still on:**
```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
cd C:\Users\<USER>\Desktop\GoldenEyeVR\goldeneye-native\getv\build-windows
$env:GETV_STAGE = "9"
$env:GETV_WATCHDBG = "1"
.\goldeneye.exe *> run_watch2.log 2>&1
```
**Do not fire at anything. Do not let anything explode.** Stand still, cycle the
whole inventory, past the detonator, until it dies. **The point is to reach the
watch crash without `objDeform` getting there first.**

**B — the explosion crash, on purpose:**
```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
$env:GETV_STAGE = "9"
.\goldeneye.exe *> run_boom.log 2>&1
```
**Shoot something that explodes, immediately, and nothing else.** **If it dies in
`objDeform` again, that crash is reproducible on demand** and becomes the cheapest
one to work on — **which matters, because §3's shape needs a site where the
rotated pointer can be traced back to whoever wrote it.**

**The map is still valid** — `goldeneye.map` and `goldeneye.exe` are both 02:47,
and nothing has been rebuilt since. **Keep them together** (`206`).

## §6 — WHAT IS NOT CLAIMED

- **No mechanism for the rotation** (§3). Two instances of a shape.
- **The `-1`/`ITEM_NOTHING` reading is WITHDRAWN for these two crashes only.**
  `247` A3's enum sweep stands on its own and is still owed.
- **`[ASSUMED]` both crashes share one cause.** Two rotated pointers in two
  subsystems is suggestive; it is not proof of a single writer.
- **`248` §4.1's `ALIGN64_V2` pointer truncation is still on disk, unfixed, and
  is a THIRD instance of the same family** — a pointer forced through 32 bits.
