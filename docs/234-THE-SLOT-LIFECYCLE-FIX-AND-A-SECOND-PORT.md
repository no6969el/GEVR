# 234 — THE SLOT LIFECYCLE FIX, AND A SECOND PORT TO MEASURE AGAINST

**2026-08-28. Docs run to `234`. NEXT DOC = `235`.**

> # ►►►► **THE FIRST FIX THIS PROJECT HAS WRITTEN INTO THE NATIVE PORT.** ◄◄◄◄
> **Everything in `230`-`233` was an instrument. This is a behaviour change, it is
> `GETV_SLOTFREE` (default ON, `=0` reverts), and it is three files.**
>
> ## ►► AND DESIGNING IT FOUND A SECOND FAULT HIDING BEHIND THE FIRST. ◄◄
> **`233` §4's one-line version — "clear `ge_inuse` in the free" — WOULD HAVE
> TURNED A NULL-MODEL CRASH INTO MEMORY CORRUPTION.** §2 is why.

---

## §1 — WHAT `233` ESTABLISHED, IN ONE LINE

`clear_model_obj()` / `clear_aircraft_model_obj()` set `Model.obj = NULL`. On the
N64 that WAS the free, because the free test was `unk08 == 0` and **`unk08`
aliased `Model.obj`** — one store, two meanings, by layout. At 64-bit `Model.obj`
moved to `0x10`, the alias is gone, the port substituted an explicit `ge_inuse`
byte, **and nothing ever clears it.** Ten anim slots, ten cast characters, the
eleventh NULL.

---

## §2 — THE SECOND FAULT. `[READ]`, AND IT IS THE REASON THIS IS THREE FILES.

**Every reuse path reads the slot's rwdata back out of `unk10`:**

| site | code |
|---|---|
| `model.c:141` | `rwdata = g_ModelSlots[i].unk10;` |
| `model.c:226` | `rwdatas = g_AnimModelSlots[i2].unk10;` |
| `modelmgrCanSlotFitRwdata` | `slot->unk10 != NULL && slot->unk02 >= numRecords` |

`[READ]` **`unk10` is at offset `0x10`. So is `Model.obj`.** `objecthandler.h`'s
own comment says so: *"unk08 aliases Model.chr and unk10 aliases Model.obj"*.
**`modelInit()` / `animInit()` therefore overwrite the slot's rwdata pointer with
the model's file header, the first time the slot is used.**

`[READ]` on the N64 `unk10` aliased `Model.datas`, which held the rwdata — so the
pointer the slot was allocated with was still there for the next reuse. **The
aliasing that made the free work and the aliasing that made the reuse work are
the same aliasing, and the port lost both at once.**

> ## ►► NOBODY HAD EVER NOTICED, BECAUSE NO SLOT HAS EVER BEEN REUSED. ◄◄
> **`ge_inuse` being a one-way ratchet is what has been HIDING the clobber.**
> Clearing it alone would have handed a `ModelFileHeader *` to code expecting
> rwdata — **on every reuse, game-wide, silently.**
> **This is exactly the failure `48` exists to prevent, and it was found by
> designing the fix rather than by shipping it.**

---

## §3 — THE FIX AS BUILT

### §3.1 — `objecthandler.h`: a copy the first use cannot reach
Added to **both** `ModelSlot` and `AnimModelSlot`, inside `GE_PORT_NATIVE`, **past
the padding beside `ge_inuse`** where no `Model` field lands:
```c
void *ge_rwdata;
s16   ge_rwdatacap;
```

### §3.2 — `initunk_005520.c`: saved once, at pool allocation
Both `modelmgrAllocateModelSlots()` and `modelmgrAllocateAnimModelSlots()` mirror
what they just put in `unk10`/`unk02` into the new fields. **The spare-slot branch
gets the buffer and its capacity; the `i < numobjs` branch gets `NULL` and `0`.**

### §3.3 — `model.c`: `ge_slot_release()`, and the two frees that call it
```
ge_slot_release(Model *m):
    if !GETV_SLOTFREE or m == NULL      -> return
    if m is inside g_AnimModelSlots[]   -> unk10 = ge_rwdata; unk02 = ge_rwdatacap; ge_inuse = 0
    else if inside g_ModelSlots[]       -> same
    else                                -> not pooled; nothing to do
```
called at the end of **`clear_model_obj()`** and **`clear_aircraft_model_obj()`**.

**Three properties worth stating, because each is a trap avoided:**

1. **The pool is resolved by ADDRESS, not by a type the caller does not have.**
   `ge_inuse` sits at a **different offset** in `ModelSlot` than in
   `AnimModelSlot`; a `Model *` cannot say which, and writing the wrong one
   corrupts the neighbouring slot — **the exact class of fault the padding in
   `objecthandler.h` exists to prevent.** The range test also requires the
   pointer to be **slot-aligned**, so a `Model *` into the middle of a slot is
   rejected rather than half-released.
2. **A pointer in neither pool is left alone.** Both instantiate functions have a
   `mempAllocBytesInBank` fallback; those models are not pooled and have nothing
   to release. Counted as `g_geSlotFreedUnpooled`.
3. **Restoring `unk10`/`unk02` returns the slot to its exact post-allocation
   state**, so **every existing reuse test works unchanged** — no instantiate-path
   edits, which keeps the change small and keeps the N64 build byte-identical.

### §3.4 — `[MEASURED]` IT COMPILES
`gcc -fsyntax-only` with `build_windows.ps1`'s own game flag set, verbatim
(`-fms-extensions -include src/ge_port_decls.h -DGE_PORT_NATIVE -std=gnu17
-Werror=return-type` …), across **all 135 `src/game/*.c`**:

> **135 checked, 0 failures.**

A header change reaches every consumer, so the whole batch was swept rather than
the three edited files. **This is a Linux syntax check, not a build.**

### §3.5 — AND THE N64 BUILD CANNOT REGRESS
**Every added line is inside `#ifdef GE_PORT_NATIVE`.** `225`'s byte-identical-ROM
gate is untouched by construction.

---

## §4 — `G-234`. THE GATE IS A MEASUREMENT, NOT THE ABSENCE OF A CRASH.

**NO REBUILD IS OPTIONAL HERE — this is the first change that needs one.**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
cd C:\Users\<USER>\Desktop\GoldenEyeVR\goldeneye-native
& getv\build_windows.ps1 -Target all *> build.log 2>&1
cd getv\build-windows
$env:GETV_MPCHR = "1"
.\goldeneye.exe *> run_slot.log 2>&1
```

**Let the whole intro play — past the eleventh cast character, all the way round.**

| reading | verdict |
|---|---|
| **`[mpchr]` `model=` pointers REPEAT** instead of climbing by `0x1c8` | ► **PASS.** Slots are being recycled |
| the intro loops without an exception | necessary, **not sufficient** — a leak that merely got slower looks the same for longer |
| `model=0000000000000000` still appears | the release is not reaching those slots; read `g_geSlotFreedAnim` |
| **anything visibly wrong with a cast character's model** | **the clobber is real and my `unk10` restore is wrong.** `GETV_SLOTFREE=0` reverts on the same binary |

> **`GETV_SLOTFREE=0` IS THE A/B AND IT NEEDS NO SECOND BUILD.** Same binary, old
> behaviour, crash returns. **That is the control for every claim above.**

---

## §5 — THE OWNER FOUND A SECOND, INDEPENDENT PORT. IT IS A CONTROL WE DID NOT HAVE.

**`https://github.com/akratch/mgb64` — MGB64.** `[READ]` from the repository and
its releases page:

- **A native source port of GoldenEye 007 from the same `n64decomp/007`
  decompilation** — C, CMake, SDL2 + OpenGL, N64 display lists translated to the
  GPU. **The same idea as `goldeneye-native`, by a different author.**
- **It ships BINARIES.** `v0.3.2`, 6 July 2026: **`mgb64-windows-v0.3.2.zip`
  (portable, x64)**, plus macOS and Linux. Two `v0.4.0-alpha` builds after it.
- **Bring your own ROM. No assets shipped** — same terms as ours.
- **`[REPORTED]` by the project itself: DISCONTINUED, August 2026.** *"provided
  as-is; no longer maintained or supported."*
- **No VR, no Perfect Dark.** It is not a base to switch to. **It is a
  reference and a control.**

### ►► WHY THIS MATTERS MORE THAN IT LOOKS ◄◄

**`233` §6 could only answer "are these upstream's bugs?" by INFERENCE** — from
`origin/main` being one commit behind us and upstream's roadmap assigning Windows
to a machine that *"renders at roughly one frame per second"*. **MGB64 turns that
into a measurement, in about five minutes and with no build:**

> **Download `mgb64-windows-v0.3.2.zip`, point it at the same ROM, and look at the
> folder screen and the intro.**

| MGB64 shows | what it means |
|---|---|
| **folder text present, intro completes** | both faults are specific to `goldeneye-native`'s port layer, **and MGB64's source is a worked reference for both** |
| **folder text missing too** | the fault is upstream of both ports — the decomp, or the asset pipeline — and `230`-`233`'s five exclusions apply to a much narrower place |
| **its own intro crashes at a cast character** | **the model-slot lifecycle is a shared decomp-level trap**, and §3's fix is worth reading across |

**`[ASSUMED]` and stated as such: nothing about MGB64's behaviour is known yet.
The table above is a plan for reading a result, not a prediction of one.**

**AND IT IS A DIFFERENT CODEBASE.** A difference does NOT localise a fault inside
our tree by itself — **but a MATCH is a strong statement about where the fault is
NOT**, and that is the thing this project has been short of for five documents.

---

## §6 — WHAT IS NOT CLAIMED

- **`G-234` has not been run.** Nothing above is `[REPORTED]` yet.
- **No claim that the slot leak is the only cause of the intro crash** — it is the
  cause of `model == NULL` at that call site, `[MEASURED]`. Anything downstream of
  a working intro is unexplored.
- **The menu text is untouched by this document** and stands where `233` §8 left
  it: game side clean, texrect state clean, fill overdraw excluded, combiner
  decoded correct. **Five exclusions and no candidate.**
- **`[READ]` MGB64's summary came from its README and releases page, not from its
  source.** No claim is made about how it draws text or manages model slots.
