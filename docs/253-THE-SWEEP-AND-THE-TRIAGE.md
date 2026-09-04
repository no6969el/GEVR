# 253 — THE SWEEP: 122 SITES, ONE FIX, AND A TRIAGE

**2026-08-29. Phase A2. Docs run to `253`. NEXT DOC = `254`.**

> # ►►►►►► **122 POINTER/INT NARROWINGS ACROSS 18 FILES. ONE OF THEM USES A
> # TRUNCATED POINTER AS AN ADDRESS. THAT ONE IS FIXED; THE OTHER 121 ARE
> # REGISTERED, NOT TOUCHED.** ◄◄◄◄◄◄
>
> **`242` §5 and `252` §6 were both about changing things whose correctness was
> assumed. A blind mass-edit of 122 sites would be that mistake at the largest
> scale this tree allows.**

---

## §1 — THE SWEEP

**`[MEASURED]`, all 135 `src/game/*.c`, with the build's own flags plus
`-Wpointer-to-int-cast -Wint-to-pointer-cast -Wint-conversion`** (the build's
`-w` suppresses all three — `248` §4):

| file | sites | | file | sites |
|---|---|---|---|---|
| `chraction.c` | 44 | | `lightfixture.c` | 4 |
| `objecthandler_2.c` | 25 | | `vtxstore.c`, `title.c`, `rsp.c`, `prop.c`, `indy_comms.c`, `bondview2.c` | 2 each |
| `zlib.c` | 16 | | `stan.c`, `macro.h`, `objective_status.c`, `model.c`, `bg.c` | 1 each |
| `indy_commands.c` | 6 | | | |
| `ramromreplay.c`, `propobj.c` | 5 each | | **TOTAL** | **122** |

---

## §2 — THE TRIAGE, AND WHY MOST OF THESE ARE NOT BUGS TODAY

**The question for each site is not "does it truncate" but "IS THE TRUNCATED VALUE
USED AS AN ADDRESS".**

| class | example | verdict |
|---|---|---|
| **pointer compared to pointer, both truncated** | `chraction.c:2210` `(s32)struck_anib->struck_anim == (s32)GE_ANIM_AT(…)`; `propobj.c:14944` | **works today.** `[MEASURED]` our heap is one `0x00007ff6xxxxxxxx` region, so the high halves are equal and comparing low halves is exact. **FRAGILE, NOT BROKEN** |
| **pointer difference taken as `s32`** | `stan.c:3343` `delta = (s32)newBase - origBase`; `objecthandler_2.c:229-276` | **works today** while both operands live in one region |
| **a flag read out of a pointer's low bits** | `propobj.c:3994` `!((s32)temp_v0_2->model & 0x400)` | **works** — bit 10 survives truncation |
| **a pointer used as a small index when it is small** | `propobj.c:7149` `if ((u32)screen->tconfig < 100)` then `&monitorimages[(s32)screen->tconfig]` | **works by luck**: a real pointer's low half is essentially never < 100. **A `union{T*; s32 Index}` slot, and the generated `ge_propdef_layout.inc.c` already has a category for exactly these** |
| **a diagnostic print** | `model.c:6166` `osSyncPrintf("… (0x%X)", (u32)mdl->obj)` | harmless; **prints half an address** |
| ► **A TRUNCATED POINTER USED AS AN ADDRESS** | **`front.c:8517`** | ► **BROKEN. §3** |

> **`zlib.c` (16), `indy_commands.c` (6), `indy_comms.c` (2) and
> `ramromreplay.c` (5) are OUT OF SCOPE**: a self-contained decompressor and the
> Indy dev-station comms, which `[MEASURED]` are stubbed at boot
> (`STUB: indycommInit`). **29 of the 122 are not reachable game code.**

---

## §3 — THE ONE FIX

`[READ]` `front.c:8517`, in `displaycast`, immediately after the `ce:3-zbuf` boot
mark:
```c
zbufSetBuffer(ALIGN64_V2(bufferPtr + bufferRemaining), Z_BUFFER_4_3_WIDTH, …);
```
`[READ]` `macro.h:10`: `#define ALIGN64_V2(val) ((((u32)val) + 0x3f | 0x3f) ^ 0x3f)`
`[READ]` `viewport.c:61`: `void zbufSetBuffer(uintptr_t buffer, …) { z_buffer = buffer; }`

> **The macro casts to `u32`, so the top 32 bits of a heap pointer are discarded
> and `z_buffer` is set to a wild low address.** **Five of the macro's six call
> sites pass a SIZE, where the `u32` is correct and intended; this is the only one
> that passes a POINTER.**

**FIXED with a separate macro, leaving the original untouched:**
```c
#define ALIGN64_V2_PTR(val) ((((uintptr_t)(val)) + 0x3f | 0x3f) ^ 0x3f)
```
**`uintptr_t` is 32-bit on the N64, so this is byte-identical there.** **No knob:
widening an address can only preserve bits the old form threw away, and an
off-switch for that is a switch nobody would ever flip.**

**`[MEASURED]` `front.c` now reports ZERO `-Wpointer-to-int-cast`, and all 135
game files compile clean** (`macro.h` reaches every consumer).

### §3.1 — HONEST LIMIT: THIS PROBABLY NEVER CRASHED

**`z_buffer` is handed to `zbufInit`, which puts it in a display list as the RDP's
depth-buffer address. `[INFERRED]` fast3d uses OpenGL's own depth buffer and never
dereferences it, which is why a wild address has sat there harmlessly.**
**Counter-example search: no crash in this corpus has ever resolved into
`zbufInit` or the depth path.** **So this is a CORRECTNESS fix with no known
symptom** — recorded as such rather than sold as a cure.

---

## §4 — THE REGISTER, AND WHAT WOULD MAKE IT SAFE TO ACT ON

**The 93 in-scope sites are not a to-do list.** Every one of them works because
**the game heap is a single contiguous region whose high 32 bits are constant**
(`[MEASURED]` `heap = 00007ff6c4423b70 .. 00007ff6c6423b70`).

> ## ►► THAT IS EXACTLY THE ASSUMPTION `247`'s PHASE D WOULD MAKE PERMANENT. ◄◄
> **Under the 32-bit arena that `007-VR` and `007portable` both adopt, every one
> of these 93 sites becomes CORRECT BY CONSTRUCTION rather than correct by
> accident.** **Without it they stay a standing hazard: the day an allocation
> lands in a second region, they all break at once, silently, and each one looks
> like a fresh bug.**
>
> **So the sweep's real output is not 93 edits. It is a MEASURED SIZE for the
> Phase D decision** (`247` §2, D1): *"cost it, do not start it"* — **and this is
> a large part of that cost, now counted.**

## §5 — WHAT IS NOT CLAIMED

- **No claim the 121 untouched sites are correct in general** — only that they are
  correct under the current single-region heap, which §4 says is the fragile part.
- **`[ASSUMED]` fast3d ignores the RDP z-buffer address** (§3.1). Not verified.
- **`chraction.c`'s 44 were not read individually.** They were classified from a
  sample of six, all of the same `(s32)ptr == (s32)ptr` animation-compare shape.
- **Nothing here has been run.** `front.c`'s change ships with the next build.
