# 115 — THE CROSS-BOUNDARY HEADER TRAP. IT LOOKED LIKE A BUG FOR AN HOUR.

**2026-08-24. Not a code fault. A BUILD fault that wore a code fault's costume,
and `build.ps1` now catches it.**

---

## §1 — WHAT IT LOOKED LIKE

**`114` added O94's pick trace: 25 atomics into `SharedQueueResources`, plus a
recording block and a gated print.** Built with `.\build.ps1`, run, and:

| | run B (13:51) | **run C/D (14:23-14:28)** | run F, clean rebuild |
|---|---|---|---|
| fps | 60.0 | **25.7** | **60.0** |
| submits/s | 90 | **13** | **90** |
| `renders` (game frames) | 60 | **26** | **59-61** |
| `xrWaitFrame` | 9.3 ms | **73.6 ms** | 10.3 ms |
| pick trace | — | **`1:0:7a82` x24, constant** | — |
| **The wearer** | — | ***"slow, and the character moved around"*** | — |

**Same runtime, same 5306x4090, same LUID, same swapchain, same source.**
**A full rebuild fixed it with NO SOURCE CHANGE.**

---

## §2 — THE MECHANISM

**`lib/rt64` is a SEPARATE CMake library** — `CMakeLists.txt:38`,
`add_subdirectory(lib/rt64)`. **`rt64_shared_queue_resources.h` is included by
BOTH sides of that boundary:**

- RT64's `rt64_present_queue.cpp` and `rt64_workload_queue.cpp` -> the `rt64` lib
- The host's `ge_vr_xr.cpp` and `rt64_render_context.cpp` -> the `GoldenRecomp` target

**`build.ps1` ran `cmake --build build --target GoldenRecomp`, which did not
rebuild every RT64 translation unit that includes that header.**

**O94 inserted its members in the MIDDLE of the struct, after `vrEyeInterpUsed`
— so every member after it shifted by 100 bytes.**

> ## **THE HOST WROTE `vrPresentEyeTexture` AT ONE OFFSET AND RT64 READ IT AT ANOTHER. TWO HALVES OF ONE PROGRAM, TWO DIFFERENT MEMORY LAYOUTS.**

---

## §3 — WHY IT COST AN HOUR, AND WHY IT WILL AGAIN

**IT DOES NOT PRESENT AS A BUILD FAULT.** It presented as:

1. **A performance regression** — and one that exactly reproduced `104`'s
   numbers, 25.7 fps and 13 submits, which is a signature this project has spent
   three documents on.
2. **A gameplay bug** — *"the character moved around like they did when we did
   something before"*, which is `105`'s known regression and was therefore the
   most natural thing in the world to blame.
3. **A diagnostic reading a constant** — `1:0:7a82` twenty-four times. **Which
   read as a stunning finding about the workload never flipping sets**, and was
   in fact a pointer read from the wrong offset.

**Every one of those pointed at real, documented, previously-observed faults.
Not one pointed at the build.**

**AND THE NEAR MISS IS THE LESSON:** the reasoning had already reached *"the
workload only ever publishes set 1, pass 0"* and was one step from a document
saying `107`'s stride fix produces a pipeline that presents the same image
ninety times a second. **That document would have been entirely wrong and
entirely persuasive**, and it would have sent the next session into
`rt64_workload_queue.cpp` after a bug that does not exist.

**`48` rule 4 caught it — barely.** The instrument was verified against a build
that was itself misbehaving, and the only reason it did not become a finding is
that the FPS anomaly was noticed in the same log.

### §3.1 — WHAT SAVED IT

**`56`'s method, and the owner's report.** *"It was slow"* arrived attached to
*"and the character moved around"* — **two symptoms at once, from two different
subsystems, is not what a single code change looks like.** That is what made a
build fault worth considering at all.

**`95` again: the wearer's unprompted second symptom was the whole diagnosis.**

---

## §4 — THE FIX, IN `build.ps1`

**`build.ps1` now stamps `build\.gevr-header-stamp` on every full build and
compares it against the newest `*.h`/`*.hpp` under `lib\rt64\src` and `src`.**

| Condition | What it does |
|---|---|
| **A header is newer than the stamp** | **Builds EVERY target** (`cmake --build build` with no `--target`), says so loudly, names the header, and re-stamps |
| **No header changed** | Short build, `--target GoldenRecomp`, exactly as before |

**It costs an occasional slower build. The alternative costs a day and looks
like a real bug the entire time.**

**`07` GOTCHA 4 is the same class of trap for NEW FILES** — *"adding a source
file needs `cmake -S . -B build` first, or the build succeeds while silently
ignoring the change."* **This is its missing sibling for CHANGED HEADERS, and it
is worse, because a silently-ignored new file usually fails to link while a
stale struct layout runs.**

---

## §5 — THE RULE THIS EARNED

> **A BUILD THAT SUCCEEDS IS NOT A BUILD THAT IS CORRECT.**
>
> **When a change touches a header shared across a library boundary, the failure
> mode is not a compile error — it is two halves of one program disagreeing
> about memory, at full speed, with no diagnostic anywhere.**
>
> **And it will present as whatever fault you were already looking for.**

**Companion to rule 4.** Rule 4 says verify the instrument before trusting the
test. **This says verify the BINARY before trusting the instrument** — because
every instrument in `114`'s run was reporting faithfully about a program whose
two halves had different ideas of where its own data lived.

### §5.1 — THE CHEAP HABIT

**When a result is surprising AND touches a shared header, rebuild fully before
writing anything down.** It costs one build. **`105` and `106` are two documents
written about a stall whose cause `107` later showed was arithmetic; this would
have been a third about a stall whose cause was a stale object file.**

---

## §6 — AND THE DEFENSIVE CHANGE NOT MADE

**New members were left in the MIDDLE of `SharedQueueResources` rather than
moved to the end.**

**Appending at the end would shrink the blast radius of a future stale object —
members before the insertion point keep their offsets.** It was NOT done,
deliberately: **the clean rebuild was the single-variable test, and changing the
source at the same time would have left us unable to say which one mattered.**
That is exactly the trap `103`-`105` fell into three times.

**It is worth doing now that the cause is known — O98, cheap, and it composes
with the `build.ps1` guard rather than replacing it.**
