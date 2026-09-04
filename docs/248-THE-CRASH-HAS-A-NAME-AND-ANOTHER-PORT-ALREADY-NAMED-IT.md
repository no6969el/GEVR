# 248 — THE CRASH HAS A NAME, AND ANOTHER PORT ALREADY NAMED IT

**2026-08-29. Phase A. Docs run to `248`. NEXT DOC = `249`.**

> # ►►►►►► **`FAULT PC` = `modelGetNodeRwData + 0x8`.** ◄◄◄◄◄◄
> **The first `FAULT PC` this project has ever resolved. `243`'s map flag paid for
> itself on its first run.**
>
> ## **AND IT IS THE EXACT FUNCTION `007portable`'s 64-BIT COMMIT NAMES.**

---

## §1 — HOW IT WAS RESOLVED, SO THE NEXT ONE TAKES A MINUTE

**ASLR moves the image, so the map cannot be read directly. The delta comes from
any static symbol whose runtime address the port already prints.**

```
&g_mempPools at run time   0x00007ff6f84103a0     ([getv] MEMP TABLE ...)
 g_mempPools in the map    0x0000000140f803a0     (goldeneye.map:54209)
ASLR delta                 0x00007ff5b7490000
FAULT PC (runtime)         0x00007ff6f75136db
FAULT PC (map space)       0x00000001400836db
containing symbol          modelGetNodeRwData  @ 0x1400836d3   (+0x8)
```

**`206`'s rule, carried across at last: keep the log and the map together, and
find a printed static symbol to anchor the delta.** `[getv] MEMP TABLE` prints
`&g_mempPools` on every boot, so **every future crash in this port is resolvable
with the arithmetic above.**

---

## §2 — WHAT `+0x8` IS

`[READ]` `model.c:612`:
```c
union ModelRwData* modelGetNodeRwData(Model *Objinst, ModelNode *root)
{
    s32 index = 0;
    union ModelRwData **data = Objinst->datas;
    switch (root->Opcode & 0xff)      <-- the first dereference of `root`
```

**`fault addr = 0xffffffffffffffff`.** That is not a stray address: **it is `-1`
in an `s32`, SIGN-EXTENDED into a 64-bit pointer.** `root` arrived as a sentinel
and was dereferenced.

---

## §3 — THE CALLER, AND THE OWNER'S REPORT NAMES IT

`[REPORTED]` ***"it crashes after doing a full inventory cycle. Right after the
watch detonator."***

`[READ]` `bondview2.c:9226-9239` — **the watch render path**:
```c
objheader = get_ptr_itemheader_in_hand(GUNLEFT);
nodepos   = (f32 *) objheader->Switches[3];
...
rwdata = modelGetNodeRwData(GE_WATCH_MODEL(), (ModelNode *) nodepos);
```

**`Switches[3]` is read out of the left-hand item's header and cast straight to a
node pointer, unchecked.** **`[INFERRED]` after a full inventory cycle the left
hand's header is absent or its `Switches[3]` is an unresolved `0xffffffff`
sentinel, which sign-extends and faults at `+0x8`.**
**Counter-example search: the same function has ten other callers
(`chr.c:1685`, `:3180`, `bondview2.c:9114`…) and none is reported to crash, so it
is not `modelGetNodeRwData` that is broken — it is what this one call site hands
it.** **`[ASSUMED]` until §5's instrument prints the value.**

### §3.1 — AND `007portable` DOCUMENTED THIS FUNCTION FIRST

`[READ]` `jeffory/007portable`, commit `029ec75` *"64-bit: keep the game's
pointers under 2GB"*:
> *"the game's data model is 32-bit, and a pointer that round-trips through an s32
> comes back sign-extended once bit 31 is set.*
> ***`modelGetNodeRwData` (cast screen) node = `0xffffffff800b0000`***
> *`makeonebody -> modelAttachHead` node = `0xffffffff80060c20`"*

**Same function. Same sign-extension. Theirs had bit 31 set; ours is the full
`-1`.** **Two independent ports, the same decomp, the same victim.**

> ## ►► THIS IS THE MEASUREMENT `247` §1.1 SAID TO WAIT FOR. ◄◄
> **The resolved crash IS a value that came through an `s32` and sign-extended
> into a pointer. That is precisely the disease the 32-bit arena retires, and the
> owner's hypothesis is supported by a measurement rather than by analogy.**
> **It does NOT follow that the arena is the right fix for this SITE** — an
> unchecked `Switches[3]` is a missing guard whatever the pointer width — **but
> the CLASS is now evidenced in our own binary, not just in someone else's commit
> message.**

---

## §4 — A2, PARTIAL: THE BUILD COMPILES WITH ALL WARNINGS OFF

**`[MEASURED]` `build_windows.ps1:160`: `$warn = @('-w','-Werror=return-type')`.**
**`-w` disables EVERY diagnostic.** Compiling 68 of the 135 game files with four
flags re-enabled:

| warning | count |
|---|---|
| `-Wincompatible-pointer-types` | 635 |
| `-Wbuiltin-declaration-mismatch` | 545 |
| **`-Wpointer-to-int-cast`** | **52** |
| `-Wimplicit-function-declaration` | 11 |
| **`-Wint-conversion`** | **3** |
| **`-Wint-to-pointer-cast`** | **1** |

**The 56 in bold are the fault class.** The rest is decomp typing noise and the
deliberate stdio shadow.

> **AN INSTRUMENT NOTE THAT NEARLY COST THE RESULT:** the first sweep passed `-w`
> BEFORE the `-W` flags and reported **zero** warnings. **`-w` suppresses
> everything and a later `-W` does not re-enable it.** It was caught by testing
> the sweep against a file with a known mismatch first. **`178`'s rule: an
> ungated instrument looks exactly like a clean result.**

### §4.1 — ONE REAL TRUNCATION FOUND

`[READ]` `macro.h:10`:
```c
#define ALIGN64_V2(val) ((((u32)val) + 0x3f | 0x3f) ^ 0x3f)
```
**It casts its argument to `u32`.** `[READ]` all six call sites: five pass SIZES
(fine). **One passes a POINTER:**
```c
front.c:8517:  zbufSetBuffer(ALIGN64_V2(bufferPtr + bufferRemaining), Z_BUFFER_4_3_WIDTH, ...)
```
**`bufferPtr` is a heap pointer, `[MEASURED]` at `0x7ff6…`. `(u32)` keeps the low
32 bits and throws the rest away.** **And this is in `displaycast` — the same
function as `232`'s cast crash, right after the `ce:3-zbuf` boot mark.**
**NOT FIXED HERE.** One change at a time, and A1's site comes first.

---

## §5 — `G-248`. THE INSTRUMENT IS ALREADY BUILT. AGAIN.

`[READ]` `bondview2.c:9230`, immediately above the faulting call:
```c
if (geWatchDbg() && wn < 3) {
    osSyncPrintf("[getv][watchmdl] render on=%d model=%p obj=%p datas=%p "
                 "render_pos=%p hdr=%p sw3=%p\n", ...);
}
```
**`hdr` is `objheader` and `sw3` is `nodepos` — the two values §3 needs, printed
at the crash site, gated on `GETV_WATCHDBG=1`, and never run.**
**That is the FOURTH already-built-never-run instrument this session**, after
`GETV_AUDIO_TESTSFX`, `GETV_RECTTRACE` and `GETV_MPCHR`.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
cd C:\Users\<USER>\Desktop\GoldenEyeVR\goldeneye-native\getv\build-windows
$env:GETV_STAGE = "9"
$env:GETV_WATCHDBG = "1"
.\goldeneye.exe *> run_watch.log 2>&1
```
**Cycle the inventory to the watch and past the detonator, exactly as before.**
**NO REBUILD** — `GETV_SLOTFREE = 0` stays in the cfg, and `goldeneye.map` from
02:47 still matches this binary.

| `sw3=` prints | conclusion |
|---|---|
| `0xffffffff` or `0xffffffffffffffff` | **§3 confirmed.** The header's `Switches[3]` is an unresolved sentinel; the fix is a guard at the call site |
| a plausible pointer, and it still crashes | the sentinel arrives later, or `GE_WATCH_MODEL()` is the bad argument instead |
| **nothing prints** | the crash happens before the debug line — **impossible as written, so that outcome means the watch path is not the one crashing** and §3 is wrong |

## §6 — ALSO REPORTED, NOT DIAGNOSED

`[REPORTED]` ***"I am able to pick up the gun, but it isn't as quick as it is in
the normal game."*** **Recorded. No mechanism, no measurement, and NOT to be
guessed at** — it may be the same missing-header path making the pickup retry, or
it may be unrelated. **It waits for `G-248`.**

## §7 — WHAT IS NOT CLAIMED

- **`[ASSUMED]` the watch path is the crashing caller.** §3's counter-example
  search supports it; §5 measures it.
- **No fix is on disk.** §4.1's truncation is recorded, not repaired.
- **The `-1` here is a SIGN-EXTENDED s32, not necessarily the `ITEM_NOTHING`
  enum trap of `243` §2.** A3 is still owed and still separate.
