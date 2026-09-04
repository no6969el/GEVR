# 242 — `G-241` FAILS. THE SLOT FIX GOES OFF BY DEFAULT.

**2026-08-28. Docs run to `242`. NEXT DOC = `243`.**

> # ►►►► **TWO ATTEMPTS, TWO GATE FAILURES. STOP ITERATING AND REVERT THE
> # DEFAULT.** ◄◄◄◄

---

## §1 — THE RESULT, AND IT IS NOT A STALE BINARY

`[MEASURED]` `model.c` **22:21:00**, `goldeneye.exe` **22:37:29** — the binary was
built AFTER the corrected source, and `[MEASURED]` the corrected shape is in the
file: one forward declaration of `ge_slotfree_on`, **zero** `slot->unk10 =
slot->ge_rwdata` restores. `build.log`: **165/234/40/58/2 built, 0 failed.**
**`241`'s fix was really in this run.**

`[REPORTED]`, with `GETV_SLOTFREE` at its default (ON):

1. ***"I don't think it let me pick up the gun until I switched the gun in my
   hand, and then it let me pick it up."*** — **pickup still wrong, now with a
   workaround rather than a hard refusal.**
2. ***"I picked up the ammo box, and I think it gave me two different types of
   mines."*** — **an item index landing on the wrong record.**
3. ***"I kept switching through the guns, and then it just closed."*** — **a NEW
   crash, on weapon cycling, which no build before `234` has been reported to do.**

> **`241` §1 was a correct diagnosis of a real defect — the `Model.obj`
> resurrection — and fixing it did not fix the symptom. So there is at least one
> MORE fault in the same change, and possibly the whole approach is wrong.**

---

## §2 — THE DECISION: DEFAULT IT OFF, AND SAY WHY IN ONE LINE

**The crash `234` fixes is in the INTRO ATTRACT LOOP — a screen the owner skips.
The faults it causes are in PICKUP, INVENTORY and WEAPON SWITCHING, plus a crash.**

> ## **THAT TRADE IS WRONG, AND IT HAS BEEN WRONG FOR TWO BUILDS.**

**`GETV_SLOTFREE = 0` in `goldeneye.cfg`. NO BUILD.** The code stays exactly where
it is — DELETE NOTHING — and the knob simply defaults the other way until it has a
gate it can pass. **`241` §2 made `=0` a complete revert on one binary precisely
so this costs nothing.**

**AND THE INTRO CRASH RETURNS. That is accepted, knowingly**: it is reached only
by watching the attract loop past eleven cast characters, and `240`/`241` cost two
sessions of gameplay faults to avoid it.

---

## §3 — A SIGNAL TO RETIRE: `ITEM ENTRY CORRUPT` IS A FALSE ALARM ON WINDOWS

`[READ]` `port_support.c:612`, `gePortCheckItemEntries()`:
```c
uintptr_t h = (uintptr_t) c_item_entries[i].header;
if (h != 0 && (h >> 32) != 0x1) { ... "ITEM ENTRY CORRUPT" ... }
```

**The test asserts that every item-table pointer has `0x1` in its HIGH 32 BITS.**
That encodes one platform's address shape. `[MEASURED]` **Windows pointers in our
logs are `0x00007ff6…`, so `h >> 32` is `0x7ff6` and the test fires on EVERY
ENTRY, ALWAYS** — 104 hits in `run_slot.log`, 33 in `run_rp.log`.

> **IT IS NOT EVIDENCE OF AN ITEM-TABLE FAULT AND MUST NOT BE READ AS ONE.**
> **This matters right now, because `242` §1's "ammo box gave two kinds of mine"
> is an item-table symptom and the nearest-looking instrument is broken.**
> **The check needs a platform-correct predicate (or deletion) before it can say
> anything.** Recorded, not fixed — one behaviour change at a time.

---

## §4 — `G-242`. THE REVERT IS ALSO THE EXPERIMENT.

```powershell
Add-Content "$env:APPDATA\Goldeneye-Native\Goldeneye-Native\goldeneye.cfg" `
  "`nGETV_SLOTFREE = 0   # docs 242: 234's fix is UNPROVEN for props/weapons"
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
cd C:\Users\<USER>\Desktop\GoldenEyeVR\goldeneye-native\getv\build-windows
$env:GETV_STAGE = "9"
.\goldeneye.exe *> run_off.log 2>&1
```

**REDIRECT TO A LOG THIS TIME.** `241` §4's run had none, so the weapon-cycling
crash printed its handler output to a console nobody kept. **A crash without its
log is one run wasted** (`206`: the handler was always there; only the READ was
missing).

**Do all three, in order: pick up a dropped gun WITHOUT switching first; take an
ammo box and read what it gave you; then cycle every weapon repeatedly.**

| result | conclusion |
|---|---|
| **all three clean** | **all three faults are `234`'s**, and the slot work restarts from scratch with a gate that exercises weapons |
| **some persist** | those are PRE-EXISTING port faults, uncovered because this is the first session to play a level properly. **`234` is exonerated for them and they become their own items** |
| **it crashes again** | `run_off.log` carries the handler output and the crash is readable for the first time |

---

## §5 — THE METHOD FAILURE, STATED PLAINLY

**`G-234` exercised ONE of eighteen call sites and passed. `G-241` was written
after a weapon fault was known, and STILL only asked "does a gun pick up" — it did
not ask about ammo boxes, inventory contents, or repeated weapon switching, all of
which were broken.**

> **A CHANGE TO A SHARED LIFECYCLE NEEDS A GATE THAT WALKS THE LIFECYCLE, NOT ONE
> THAT SAMPLES IT.** For any third attempt the gate is fixed in advance: pick up a
> weapon, pick up ammo, switch through every weapon twice, drop into a second
> level, and watch the intro loop — **before the owner is asked to judge anything
> by feel.**

## §6 — WHAT IS NOT CLAIMED

- **No mechanism for any of §1's three symptoms.** `241` §1's defect was real and
  is fixed; what remains is unidentified.
- **`[ASSUMED]` the three symptoms share a cause.** They may not. §4 tests them
  together only because one run can.
- **`234`'s CORE FINDING STANDS** — `ge_inuse` is never cleared, the free is a
  one-way ratchet, and the intro crash is `[MEASURED]` its consequence. **What is
  withdrawn is the FIX, not the diagnosis.**
