# 100 — EVERY PATCH PRINT IN THIS PROJECT HAS GONE NOWHERE. FOUND, AND FIXED.

**2026-08-24. Written the moment the second explanation appeared, so this file
exists before it is cited — `00`'s "phantom documents" section is five documents
cited 37 times that were never written, and `43` alone was cited 24 times.**

## §1 — WHAT WAS RUN

**The owner did exactly what was asked: entered a mission, gun in hand, left the
game running.** The log says the run was healthy in every other respect:

```
render passes: eye0=90 eye1=90 distinctTargets=90     (stereo live, both eyes)
6dof: ctrlR viewrel=(7.5,-6.7,-11.8)u quat=(...)      (controller VALID - the
                                                       previous run's valid=0
                                                       focused=0 is gone)
60.0 fps
```

**And `6dof-game:` lines: ZERO. Again.**

## §2 — WHAT WAS ELIMINATED, FROM DISK, WITH NO GUESSING

| Checked | Result |
|---|---|
| Is S0 in the running binary? | **YES.** `strings patches\patches.elf` finds all five `6dof-game` format strings, and so does the **exe**. It is not a stale-patch problem |
| Was the patch rebuilt after the edit? | **YES.** `patches.elf` 23:16, `ge_vr_bindtest.c` 23:14 |
| Did the run reach a level? | **Everything else says yes** — both eyes rendering, controller pose valid and non-zero |

## §3 — TWO EXPLANATIONS SURVIVE AND NO LOG ON DISK SEPARATES THEM

1. **THE GATE IS FALSE.** `geVrWorldCamera()` is false when `viSetFovY` runs, so
   the block never executes.
2. **`recomp_printf` DOES NOT REACH `gevr.log`.**

**Suspect 2 is not exotic and this project has paid for its shape before.** The
build is `/SUBSYSTEM:WINDOWS` with no console; `07` note 3 already records that
RT64's own `fprintf(stderr, ...)` failure reports **"go nowhere at all"**, and
`27` lost a round to exactly that.

> **AND THERE IS NO WORKING EXAMPLE TO ARGUE FROM.** All seven `recomp_printf`
> calls in `ge_vr_bindtest.c` are either **S0 itself** or the trace at `:522`,
> which is behind `#if GE_VR_TRACE_FOV` and is **off**. Every `[gevr]` line that
> has ever appeared in `gevr.log` — including every `seam` and `hand` line — is
> a **host-side `ge_vr::log`**. **No patch print has ever been OBSERVED to
> arrive.**
>
> **`48` rule 4: verify the instrument before trusting the test. S0 was trusted
> for a session and a half without anyone checking that its output had a route.**

## §4 — THE ONE LINE THAT SETTLES IT. BUILT, NOT YET RUN

**The patch calls `recomp_ge_vr_set_world_camera(geVrWorldCamera())`
unconditionally, every frame, from inside `viSetFovY` — four lines above the S0
block.** The host has that value and **has never logged it.** Now it does, once
per transition:

```
[gevr] world camera gate -> TRUE
```

| What the next log shows | What it means |
|---|---|
| **The line never appears** | `viSetFovY` is not running at all. **Both suspects are wrong** and the question moves upstream — and the FOV widening would have to be explained too |
| **`-> false` only** | **Suspect 1.** The gate is the fault, and S0 needs a different home or a different gate |
| **`-> TRUE` and still no `6dof-game:`** | **SUSPECT 2 CONFIRMED. Every `recomp_printf` instrument in this tree is blind**, and S0's game half must be re-routed through a patch->host call like `set_world_camera` itself |

**Host-side only. Short build. Costs one in-level launch, batched with anything
else — `48` amended rule 5, diagnostics batch freely.**

## §5 — WHY THIS MATTERS BEYOND S0

**If suspect 2 is right, it is not an S0 bug — it is a rule.** Every future
game-side instrument in `86`'s slices would have been written the same way and
would have been silent the same way, and each one would have cost a launch to
discover. **`muzzleExt` and `A40` are still unread and still decide the shape of
G2 and A1.**


---

# §6 — ANSWERED, SAME SESSION. **SUSPECT 2, AND IT WAS NEVER ONLY S0.**

**The gate line was built and run. The log:**

```
[gevr] world camera gate -> false
[gevr] world camera gate -> TRUE          <- and it STAYED true
```

**46 seconds of level after that transition, and not one `6dof-game:` line.**
§4's third row, exactly: **suspect 2.**

**And then it was read at source rather than inferred — `src/game/recomp_api.cpp`:**

```c
extern "C" void recomp_puts(uint8_t* rdram, recomp_context* ctx) {
    for (u32 i = 0; i < length; i++) {
        fputc(MEM_B(i, (gpr) cur_str), stdout);      /* <- STDOUT */
    }
}
```

**`recomp_printf` lands here. The build is `/SUBSYSTEM:WINDOWS` with no console.
The characters were written and discarded.**

**`ge_vr_host.h` says so in its own header comment, four files away:**

> *"The Release build links /SUBSYSTEM:WINDOWS and has no console, so everything
> diagnostic goes to `gevr.log`."*

**That sentence was written about the HOST's logger and was never checked
against the PATCH's.** `00` already recorded that RT64's `fprintf(stderr, ...)`
goes nowhere and `27` lost a round to one — **the same fault, the third time,
in a third place.**

## THE FIX — one function, host-side, short build

**`recomp_puts` now tees into `gevr.log`, line by line.** stdout still receives
every character, so a console build or a redirected run behaves exactly as
before; `gevr.log` gets a copy. Buffered to a newline, because a partial line
interleaved with the host's logging is worse than useless. Capped at 1024 chars
so a runaway format string cannot grow it without bound.

**This fixes EVERY patch print in the tree at once** — which is why it was done
here and not by giving S0 its own patch->host export. An export would have cost
a `syms.ld` address and a new name. This cost neither.

## §7 — AND THE CHECK THAT ALMOST LIED, WHICH IS THE SAME FAULT AGAIN

**`grep -c "6dof-game" gevr.log` returned 2, and both matches were the GATE LINE
I had just written**, because its help text quotes the string `'6dof-game:'` to
tell the reader what to look for. **An instrument counting itself.**

**`91` had to recount the patch names because `87`'s regex matched COMMENT
PROSE** and answered 47/48 instead of 45/46. **Same shape, nine documents later,
in the hands of the person who had just written that up.** Caught only because
the count was 2 and five lines per tick were expected.

**The rule earned: an instrument that names its own output string will match
itself. Anchor the pattern (`^\[gevr\] 6dof-game:`) or do not put the string in
the message.**

## §8 — WHAT THIS UNBLOCKS

**`muzzleExt` and `A40` are still unread — but they are now one launch away
rather than one mystery away.** Build, enter a level with a gun, exit.

**And every game-side instrument in `86`'s nine slices would have been written
the same way and been silent the same way**, each costing a launch to discover.
That is the real value of this, and it is worth more than S0.

---

# §9 — THE BISECT ANSWERED, AND IT ANSWERED TWICE

**The tee worked. `recomp_puts` reaches `gevr.log` now. And the bisect returned
two separate faults, neither of which was the one being hunted.**

## FAULT 1 — `_Printf` CARRIES THE FIRST CALL AND THEN STOPS

```
[gevr] 6dof-game: BULLET crosshair_angle=(160,120)px CLAMPED | GUNPOINT
       field_FFC=(160,120)px unclamped | aim A38/A3C/A40=(0,0,-1000)
<CR>
<CR>            <- eight of these, where four formatted lines should be
```

**The first `recomp_printf` arrived complete and correct. The four after it
produced NOTHING BUT THEIR TRAILING NEWLINE.** The format strings are not the
problem — the first one proves that. `_Printf` is real game code
(`libultrare/libc/xprintf.c`) reached through the recomp, and **it is the link
nobody in this project had ever seen work.** Now we know why: it works once.

## FAULT 2 — **A STATIC IN A `RECOMP_PATCH` CANNOT BE ASSUMED ZERO**

**The direct-`recomp_puts` marker never printed at all**, and it was guarded by:

```c
static u32 s0Marked = 0;
if (s0Marked == 0) { ... }
```

**If patch statics were zero-initialised it would have printed once. It did
not.**

> **AND `s6dofTick` IS THE SAME SHAPE AND HAS BEEN TRUSTED SINCE `91`.** It only
> ever worked because `x++ % 90 == 0` comes true from **any** starting value
> within 90 frames. **That is luck, not design** — and any future instrument
> using a `static` flag as a one-shot latch will silently never fire. **This is
> `42`'s shape again: a guard that is never reached.**

## §10 — WHAT WAS ALREADY WON, ON THE ONE LINE THAT CARRIED

| Falsifier | Prediction | **Measured** |
|---|---|---|
| **`A40`** | **< 0**, about −1000 — against `initBondDATA.c:114`'s **+1000** | **−1000. CONFIRMED.** `88` §5.1's aim-axis reasoning stands; the runtime value wins over the initialiser |
| `muzzleExt` | > 0 | **Still unread** — it was on a line `_Printf` dropped |

**Also read, and it is a gate passing:** `crosshair_angle=(160,120)` and
`field_FFC=(160,120)` — **screen centre for a 320x240 frame, which is where a
rested crosshair belongs.** The instrument is looking at the right quantities.

## §11 — THE FIX: THE INSTRUMENT OWNS ITS OWN OUTPUT PATH

**S0's game half no longer uses `recomp_printf`, `_Printf`, or a static.**
A `GE_VR_LIT` macro plus a hand-rolled `geVrPutS32` emit every field through
`recomp_puts` — which **is** proven, because the tee carried the BULLET line
intact.

**And the falsifiers are emitted FIRST**, so a truncation costs the cheap lines
rather than the two that decide slices G2 and A1.

**The rule earned, and it outlives S0:** *an instrument must own its output path
end to end, or it is reporting on a channel nobody has ever watched succeed.*
Three sessions of "the reads are done, the instrument is written" rested on a
`printf` that had never once been observed to arrive.
