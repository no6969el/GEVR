# 133 — A STALE BINARY, THEN A LINK ERROR THAT NAMED A GAP IN THE BUILD ITSELF.

**2026-08-24, evening. Two failures in a row, and both were worth having.**

---

## §1 — THE FIRST RUN WAS A STALE BINARY, AND IT WAS READ AS A PASS

**Both `-NoXr` launches at 17:08 and 17:09 were judged "tested working". Neither
binary contained RB-02 or RB-03.**

| | Stamped |
|---|---|
| `GoldenRecomp.exe` | **15:37** |
| `patches.elf`, `RecompiledPatches\patches.c` | **14:09** |
| the RB-02 / RB-03 source edits | **17:02-17:03** |

**`build.ps1` had never been run.** The binary predated every line of the change.

> ### **AND THE LOG SAID SO. `61.1 fps`, `timebase: delta=1 [1..1] | clk=1 [1..1] | gdelta x1000=1000 [1000..1000]`. G-131-1 AND G-132-1 BOTH FAILED.**

**A knob that is not in the binary produces a game that looks completely
normal**, which is indistinguishable from success to anyone who does not read the
gate. **`111` is the same lesson** — three documents celebrated `reused 30 -> 0`
which was a stall firing a clamp — and **`48` item E is the same shape**: state
read from the wrong place.

**IT WAS NOT WASTED.** Two unmodified sessions, minutes apart, on the machine as
it stands: **fps mean 59.2 / 59.3, max 61.6 / 61.1 over 140 samples, timebase
flat on both.** **G-131-5's identity target is now measured rather than
remembered**, and the two logs agreeing to a tenth means a real change will be
unmistakable. Recorded in `TESTS-OWED-ON-RETURN.md`.

---

## §2 — THEN THE BUILD FAILED, AND THE ERROR WAS THE INTERESTING PART

```
RecompiledFuncs.lib(funcs_5.obj)  : error LNK2005: __scHandleRetrace already defined in PatchesLib.lib
RecompiledFuncs.lib(funcs_30.obj) : error LNK2005: waitForNextFrame already defined in PatchesLib.lib
fatal error LNK1169: one or more multiply defined symbols found
```

**Exactly the two functions RB-02 newly patched, and nothing else.**

### THE MECHANISM

`tools_weaken_patched.py` renames the recompiled ORIGINAL of every
`RECOMP_PATCH`'d function to `{name}__recomp_orig`, so the strong definition in
`PatchesLib` is the only one left and every call site resolves to the patch.
**MSVC has no `__attribute__((weak))`, so on Windows the rename is the only
mechanism available.**

The evidence, read off the tree:

| | State |
|---|---|
| `bossMainloop` in `RecompiledFuncs` | **`bossMainloop__recomp_orig`** — renamed |
| `__scHandleRetrace`, `waitForNextFrame` | **still strong originals** |
| both, in `RecompiledPatches/patches.c` | **present**, regenerated 17:13 |
| `RecompiledFuncs/funcs_5.c` mtime | **2026-08-21** — three days old |
| the script's name-collecting regex, tested against `ge_vr_route_b.c` | **collects both** |

> ## **`tools_weaken_patched.py` IS NOT INVOKED BY `build.ps1` AND NOT BY CMAKE. IT IS A MANUAL STEP.**
>
> **It had been run by hand at some point in the past, so every EXISTING patch
> was already renamed and the gap was invisible.** `RecompiledFuncs` is not
> regenerated on an ordinary build — it is three days old — so the old renames
> persisted and nothing ever revealed that the step was missing.
>
> **RB-02 ADDED THE FIRST NEW `RECOMP_PATCH` IN LONG ENOUGH THAT NOBODY
> REMEMBERED, AND THE GAP SURFACED IMMEDIATELY AND PRECISELY.**

**This is `49`'s "two instruments cannot fail" turned inside out: a build step
that has silently not been running is indistinguishable from one that runs, right
up until the first input that needs it.**

---

## §3 — THE FIX, AND WHY IT HOOKS WHERE IT DOES

**`build.ps1` now detects `LNK2005`, runs `tools_weaken_patched.py`, and rebuilds
once**, stamping the header stamp only if that retry succeeds.

**It cannot simply run BEFORE the build.** On the rename path the script
intersects its collected names against `RecompiledPatches/patches.c`, to avoid
renaming the original of a patch that sits inside `#if 0` — and **that file does
not describe a brand-new patch until the build has regenerated it.** Running it
first would filter out precisely the new function that needs renaming, which is a
one-build lag that would look like a flaky build.

**So the correct hook is after a build that has already produced a fresh
`patches.c`** — which is exactly where the link error occurs. **Retry once, and
only for this specific error.**

### AND A SECOND, SEPARATE HOLE IN `build.ps1`, FOUND WHILE LOOKING

`$headerRoots` watched `lib\rt64\src`, `src` and `patches` — **not
`lib\N64ModernRuntime`.** RB-02 put `ultramodern::get_vi_rate()` in
`ultramodern.hpp`, which is in none of them. **A change touching only that header
would have taken the short build and silently kept the old VI thread** — `115`'s
trap, one directory further out. **Added.**

**This build was safe from it by luck:** `patches/misc_funcs.h` also changed, and
that forced the full build.

---

## §4 — WHAT THIS COSTS RB-02 AND RB-03

**Nothing, and no code changed.** Neither slice has been compiled yet, so
neither has been tested, and **`126` keeps both at IN PROGRESS.** The two
failures were a stale binary and a missing build step; **not one line of `131` or
`132` has been contradicted, or confirmed.**

**NEXT, AND IT IS TWO COMMANDS:**

```powershell
.\build.ps1                               # now self-heals the LNK2005 and says so
.\vr.ps1 -NoXr -ViRate 90                 # RB-02 alone. 131 section 5
.\vr.ps1 -NoXr -ViRate 90 -FloatDelta     # then RB-03. 132 section 5
```

**If the retry works, `build.ps1` prints that it ran the weaken step.** If
python is not on PATH it says so and stops rather than looping.
