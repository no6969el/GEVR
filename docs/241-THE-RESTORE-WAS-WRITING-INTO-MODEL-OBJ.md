# 241 — THE RESTORE WAS WRITING INTO `Model.obj`

**2026-08-28. Docs run to `241`. NEXT DOC = `242`.**

> # ►►►► **`GETV_SLOTFREE=0` RESTORED WEAPON PICKUP. SO `234`'s FIX CAUSED IT,
> # AND THE DEFECT IS ONE LINE — MINE.** ◄◄◄◄
> `[REPORTED]` ***"That fixed it for sure."*** One variable, same binary.

---

## §1 — THE MECHANISM, `[READ]` AND EXACT

`234`'s `ge_slot_release()` did three things:
```c
slot->unk10   = slot->ge_rwdata;      /* put the rwdata pointer back */
slot->unk02   = slot->ge_rwdatacap;
slot->ge_inuse = 0;
```

**`unk10` IS AT OFFSET `0x10`. SO IS `Model.obj`.** `objecthandler.h` says it in as
many words — *"unk08 aliases Model.chr and unk10 aliases Model.obj"* — and `234`
§2 QUOTED that sentence while building a fix that writes through it.

> ## ►► `clear_model_obj()` SET `Model.obj = NULL`, AND THE NEXT LINE PUT A
> ## NON-NULL POINTER STRAIGHT BACK INTO THE SAME WORD. ◄◄
> **The model was resurrected with a garbage `obj`** — an rwdata buffer address
> reinterpreted as a `ModelFileHeader *`.

`[READ]` **nineteen sites test `->obj` to decide whether a model is alive**,
including `model.c:505`, `model.c:762`, `chr.c:2559`
(`model->obj->numRecords`), and — **the one that matters here** —
`gunfire.c:1519` on the HELD-WEAPON path:
```c
if (heldR != NULL && heldR->obj != NULL && heldR->obj->model != NULL)
```
**A dead model whose `obj` is non-NULL passes that test and is then dereferenced.**

### §1.1 — AND IT EXPLAINS THE SYMPTOM'S EXACT SHAPE

`[REPORTED]` **keycards and body armour picked up; WEAPONS DID NOT.** **The
weapon path is the one that reads `->obj` twice and then follows it.** A
non-weapon pickup does not. **That asymmetry was the clue and it is now
accounted for** — it is not a general pickup failure, and never was.

---

## §2 — THE CORRECTED FIX

**`ge_slot_release()` now clears `ge_inuse` AND NOTHING ELSE.**

The reason the restore existed at all was real (`234` §2): every reuse path reads
the slot's rwdata out of `unk10`, and `unk10` does not survive a use. **So the
readers move to the saved copy instead of the release writing back:**

| site | before | now, when `GETV_SLOTFREE` is on |
|---|---|---|
| `modelmgrCanSlotFitRwdata()` | `slot->unk10 != NULL && slot->unk02 >= n` | `slot->ge_rwdata != NULL && slot->ge_rwdatacap >= n` |
| `modelmgrInstantiateModel()` loop | `rwdata = ...unk10; rwdatalen = ...unk02` | `= ...ge_rwdata; = ...ge_rwdatacap` |
| `modelmgrInstantiateModelWithAnim()` loop + its fit test | same | same |

**Every substitution is behind `ge_slotfree_on()`, so `GETV_SLOTFREE=0` remains a
COMPLETE revert on one binary** — release, fit test and both readers all fall back
together. **A forward declaration was added because all three readers appear
earlier in the file than the definition.**

**`[MEASURED]` all 135 `src/game/*.c` compile clean** under the Windows build's own
game flags. Every added line is inside `GE_PORT_NATIVE`.

---

## §3 — THE LESSON, AND IT IS NOT "BE MORE CAREFUL"

> **`234` §2's whole argument was that the port had lost an ALIAS — that `unk10`
> and `Model.obj` are the same word. I then wrote a fix that WROTE TO THAT WORD,
> in the function whose entire job is to clear it.**
> **A document can state the hazard correctly in its analysis and still walk into
> it in its implementation. Stating an aliasing constraint is not the same as
> enforcing it.**

**AND THE GATE IS WHAT SHOULD HAVE CAUGHT IT.** `G-234` measured cast-model reuse
— 33 casts, one slot — **a path with no weapons in it.** `234` §5 said the other
seventeen call sites were "reachable and still untested" and that was true; **the
gate simply never went near them.** **A gate that exercises one caller of an
eighteen-caller change is a smoke test, not a gate.**

---

## §4 — `G-241`. ONE BUILD, TWO THINGS TO CHECK, AND BOTH MUST HOLD.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
cd C:\Users\pdbar\Desktop\GoldenEyeVR\goldeneye-native
& getv\build_windows.ps1 -Target all *> build.log 2>&1
cd getv\build-windows
$env:GETV_STAGE = "9"
.\goldeneye.exe
```

**1. WEAPON PICKUP — walk over a DROPPED GUN and press use. It must be picked up
and it must fire.** Keycards and armour do not count (`240` §6.1).

**2. THEN, WITHOUT `GETV_STAGE`, THE INTRO — it must still loop past the eleventh
cast character**, i.e. `G-234` has not regressed:
```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
$env:GETV_MPCHR = "1"
.\goldeneye.exe *> run_slot2.log 2>&1
```
**Both, or the fix is not finished.** `GETV_SLOTFREE=0` is still the revert.

## §5 — WHAT IS NOT CLAIMED

- **The corrected fix has not been run.** §2 is `[READ]` plus a syntax check.
- **`[ASSUMED]` that the `->obj` resurrection is the ONLY consequence** the restore
  had. Nineteen readers were found; what else consumed a resurrected model between
  release and reuse is unknown, and a clean `G-241` is what would retire the
  question.
- **The AK texture report (`240` §2.1) is still UNJUDGED** and now needs a run on
  this build, since the previous two were confounded by `GETV_GIVE` and by this
  defect in turn.
