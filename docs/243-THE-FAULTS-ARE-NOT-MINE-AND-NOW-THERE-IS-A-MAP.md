# 243 — THE REMAINING FAULTS ARE NOT `234`'s. AND THE LINK NOW EMITS A MAP.

**2026-08-29. Docs run to `243`. NEXT DOC = `244`.**

> # ►►►► **`GETV_SLOTFREE=0` AND THE FAULTS PERSIST. `234` IS EXONERATED FOR
> # THEM — THEY ARE PRE-EXISTING, AND THIS IS THE FIRST SESSION TO PLAY FAR
> # ENOUGH INTO A LEVEL TO FIND THEM.** ◄◄◄◄

---

## §1 — `G-242`, ALL THREE ROWS ANSWERED AT ONCE

`[REPORTED]`, with the slot fix OFF:

| symptom | verdict |
|---|---|
| ***"It picked up the gun"*** | **`234`'s hard pickup refusal WAS mine** (`241` §1) and is gone with the knob off |
| ***"but won't pick up the gun again (to get ammo)"*** | **PERSISTS. NOT MINE.** |
| ***"when I get the loot box it gives me grenades and mines"*** | **PERSISTS. NOT MINE.** |
| ***"if I cycle through the inventory, it crashes"*** | **PERSISTS. NOT MINE.** |
| `[REPORTED]` ***"also sounds were delayed"*** | **`229` §20 item 3, ~51 ms, untouched all session.** Expected |

**`242` §4's middle row is the outcome: three of the four are pre-existing port
faults.** They were never seen before because **no session had played a level far
enough to pick up a second weapon, open a loot box, or cycle an inventory.**

---

## §2 — THE CRASH IS CAPTURED, AND ITS REGISTERS SAY SOMETHING

`[MEASURED]` `run_off.log`, 02:20:08:
```
===== EXCEPTION 0xc0000005 =====
fault addr: ffffffffffffffff
FAULT PC:   00007ff60a7e36db
rcx=0x00007ff60b604800  rdx=0x0be1be8800007ff6  r8=0x00007ff60b604800
rbx=0x000000000000001d  rsi=0x0000000000000074  r13=0x0000000000000003
```

**Three readings, and the second is the one to chase:**

**1. `fault addr = ffffffffffffffff` is `-1`, not a stray address.** A `-1`
sentinel reached a dereference. **`ITEM_IDS` opens with `ITEM_NOTHING = -1`** —
and `front.c:8538` already documents this exact trap for a sibling enum:
> *"enum HEADS lists `HEAD_FIXED = 0xFFFFFFFF`, so clang gives the enum an
> UNSIGNED underlying type, while IDO gave every enum plain signed int... unsigned,
> `head >= 0` is vacuously true and the sentinel is used as the index
> 4294967295. Nothing warns, because the code is valid C."*
**`[INFERRED]` the same shape, in the item path. Counter-example search: the
direct greps (`item >= 0`, `weapon >= 0`, `itemnum >= 0`) found nothing in the
item path, so if it is this it is spelled differently — which is exactly why the
next step is to RESOLVE THE PC rather than grep for a guess.**

**2. `rdx = 0x0be1be88_00007ff6` IS A POINTER WITH ITS TWO 32-BIT HALVES
SWAPPED.** Every real pointer in this dump is `0x00007ff6_xxxxxxxx`. **That is the
signature of a 64-bit pointer read as two 32-bit words in the wrong order, or a
struct field four bytes out of place** — the same family as `unk10`/`Model.obj`
(`241`), the spark colour at `0x28` vs `0x30` (`glass2.c`), and `Model.unka0`
truncation. **This port's recurring fault is field offsets, and this register says
one is wrong here too.**

**3. `rbx = 0x1d` = 29.** `[READ]` `ITEM_IDS` numbering puts **29 =
`ITEM_PROXIMITYMINE`**, with `27 = GRENADE, 28 = TIMEDMINE, 30 = REMOTEMINE`
around it. **`[REPORTED]` the loot box gave "grenades and mines".** **Consistent,
and NOT yet a claim** — a register holding 29 during an inventory walk is
suggestive, not attribution.

---

## §3 — ►► AND THE REASON NONE OF THAT CAN BE FINISHED: THERE IS NO MAP. ◄◄

**`[MEASURED]` `build_windows.ps1` emitted no linker map** — `grep -n "Map|-Wl,"`
returned nothing. **Three crashes have now been captured this session
(`232`, `241` §4, this one) and NOT ONE `FAULT PC` HAS BEEN RESOLVED TO A
FUNCTION.** Every one was diagnosed, when at all, from the surrounding log lines.

**`206` learned this in the recomp era and wrote the rule down:**
> *"`[gevr-crash]` offsets resolve against `build/Release/GoldenRecomp.map` at
> preferred base `0x140000000`. No new instrumentation was ever needed — only the
> read. COPY THE LOG AND THE MAP ASIDE TOGETHER: the map is rebuilt with the
> binary, and a stack without its map is unreadable."*

**The native port never carried that across.** Now fixed, one line in
`$linkArgs`:
```powershell
$mapPath = [System.IO.Path]::ChangeExtension($bin, '.map')
... '-lm', "-Wl,-Map=$mapPath"
```

**`-Map` IS A LINK-TIME REPORT. IT DOES NOT CHANGE A BYTE OF THE EMITTED IMAGE**,
so this is a build-system change and not a behaviour change — it does not consume
the session's one-change-per-run budget.

---

## §4 — `G-243`. BUILD ONCE, THEN REPRODUCE THE CRASH ON PURPOSE.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
cd C:\Users\<USER>\Desktop\GoldenEyeVR\goldeneye-native
& getv\build_windows.ps1 -Target all *> build.log 2>&1
cd getv\build-windows
dir goldeneye.map          # must exist, and be newer than goldeneye.exe is old
$env:GETV_STAGE = "9"
.\goldeneye.exe *> run_map.log 2>&1
```

**`GETV_SLOTFREE = 0` stays in `goldeneye.cfg` for this** — the aim is to
characterise the PRE-EXISTING faults, and the slot knob is a second variable.

**Then do the three, deliberately: pick up a gun, walk back over it for ammo, open
a loot box and read what it gives, cycle the inventory until it dies.**

**`goldeneye.map` and `run_map.log` must be kept TOGETHER** — the map is rebuilt
with every binary, and next week's map will not resolve tonight's log.

---

## §5 — WHAT IS NOT CLAIMED

- **No mechanism for any of the three faults.** §2 is three readings of a register
  dump, one of them (`rbx=29`) explicitly not attributed.
- **`[ASSUMED]` the three share a cause.** Ammo pickup, loot-box contents and
  inventory cycling all touch the item table, which makes it plausible and not
  established.
- **`234`'s DIAGNOSIS still stands** and its FIX is still off (`242`). Nothing here
  revisits either.
- **The delayed sound is `229` §20 item 3 and is untouched.** One term
  (`want.samples 512 -> 256`) and it needs its own run.
