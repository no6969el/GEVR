# 247 — THE ADOPTION PLAN, AND AN HONEST ANSWER ON THE 32-BIT ARENA

**2026-08-29. Docs run to `247`. NEXT DOC = `248`.**

---

## §1 — THE OWNER'S TWO PROPOSITIONS, ANSWERED STRAIGHT

### §1.1 — ***"I think the 32-bit one may solve our current issues"***

**PARTLY, AND THE PART IT DOES NOT SOLVE IS ONE OF TONIGHT'S THREE.**

`243` §2 captured two distinct signatures in one crash dump:

| signature | would the arena fix it? |
|---|---|
| `rdx = 0x0be1be88_00007ff6` — **a pointer with its 32-bit halves misplaced** | ► **YES.** This is the disease `007portable` names: a pointer round-tripping through an `s32`. In a low arena the round-trip is lossless and the fault cannot occur |
| `fault addr = ffffffffffffffff` — **a `-1` sentinel reaching a dereference** | ► **NO.** This is enum SIGNEDNESS, not pointer width. `ITEM_IDS` opens with `ITEM_NOTHING = -1`, which makes the compiler pick an unsigned underlying type, so `>= 0` guards go vacuously true — `front.c:8538` documents exactly this for `HEADS`. **A 32-bit arena changes nothing about it** |

**And `241`'s defect — writing into `Model.obj` — was a logic error of mine. No
memory model would have caught it.**

> **SO: the arena retires the CLASS that keeps producing new instances, and would
> likely fix one of tonight's three. It is the difference between fixing bugs and
> stopping them arriving. It is not a cure for tonight's list.**

**AND THE EVIDENCE THAT DECIDES IT IS ONE RUN AWAY.** `G-243`'s linker map
resolves the `FAULT PC` to a function. **If that function turns out to be
following a truncated pointer, the arena case is made with a measurement instead
of an argument. If it is an unsigned-enum index, the arena would not have helped
and the case rests on the class alone.** **Do not decide before that run.**

### §1.2 — ***"I think theirs worked but they don't want to say cause you need the ROM"***

**`[MEASURED]`, and the answer is the opposite — for a reason that is entirely
innocent.**

- **All 30 commits on `claude/goldeneye-007-vr-port-06libw` are authored by
  `Claude <noreply@anthropic.com>`.** The branch is literally named `claude/…`.
- **It is an agent-built port, in a sandbox with no ROM in it.** Their README:
  *"no GoldenEye ROM exists in the environment this was built in, so `init()` has
  never been called with real data behind it."*

**That is not a project hiding a working build behind a legal excuse. It is a
statement of fact about a CI-like environment, and the README is unusually candid
elsewhere too** — it lists what is unfinished, records a real EEPROM bounds bug a
compiler warning caught, and says *"expect the first real boot to find bugs."*

> **THE INSTINCT IS SOUND IN GENERAL — PEOPLE DO UNDERCLAIM.** Here the evidence
> runs the other way, and it matters: **if we assumed their VR layer works, we
> would be adopting 21,524 unrun lines on trust.** **`[READ]` is not
> `[MEASURED]`, and it does not become `[MEASURED]` because the code is
> someone else's.**

---

## §2 — THE PLAN. FOUR PHASES, ORDERED BY EVIDENCE, NOT BY APPETITE.

### ►► PHASE A — FINISH THE CRASH. NOTHING ELSE STARTS FIRST. ◄◄

**A1. `G-243`: build for the map, reproduce the inventory crash, resolve the PC.**
Already specified. **This is also the input to the Phase D decision (§1.1).**

**A2. The prototype-mismatch sweep.** `007portable`'s `cb865c0`:
`chraiGetCollisionBounds(prop, struct rect4f **, s32 *, f32 *, f32 *)` called with
four `f32` locals — a pointer stored 8 bytes into a 4-byte slot, wrecking the
local beside it. **Grep OUR tree for call sites whose argument types disagree with
the prototype**, `propobj.c` and the item path first. **Free, and it may BE A2's
answer before A1 finishes.**

**A3. The `-1` sentinel sweep.** Every enum in `bondconstants.h` carrying a
negative member makes its own type unsigned. **`ITEM_IDS` is one. Find the others
and find the `>= 0` guards that go vacuously true.** `front.c:8538`'s `(s32)` cast
is the established fix shape in this tree.

**A4. Characterise the ammo re-pickup and the loot-box contents** (`243` §1),
which are still only `[REPORTED]`.

### ►► PHASE B — THE HARNESS, BEFORE ANY MORE SHARED-LIFECYCLE WORK ◄◄

**B1. A framebuffer-readback self-test**, after `ge007-selftest`: build a display
list, submit it, **read the pixels back**. `[READ]` their reason: *"every bug
below left the triangle and draw-call counters looking perfectly healthy."*
**`231` §1.3 reasoned from `tris submitted=520 drawn=520` and was wrong.**

**B2. A scripted play-through gate**, after `007portable`'s `run_android.sh`: drive
the front end into a mission with synthetic input. **`[READ]` their hard-won
detail: `adb shell input keyevent` sends down and up in the same instant and the
port samples the keyboard once per poll, so a tap is invisible — long presses are
required. The same applies to `xdotool` on the desktop.** **That note alone saves
the first afternoon.**

**B3. THE STANDING GATE for any shared-lifecycle change** (`242` §5): pick up a
weapon, pick up ammo, cycle every weapon twice, load a second level, watch the
attract loop. **Written down in advance, not invented after a failure.**

### ►► PHASE C — THE VR TERM. THIS IS WHERE THE PROJECT ACTUALLY GOES. ◄◄

**C1. `vv_theta`.** `[READ]` `bondview.h:558`, offset `0x0148`, `f32`, 27
references, **an `f32` not a pointer** — so none of §1.1's hazards touch it.
**Read `bondview.c` against `gevr_shim.c` and cost the camera term `194` named and
`224` §3.1 wanted.**

**C2. Compare compositions before building.** Their design: body yaw lives in
play space, the head's heading is folded in **on recentre**, and the engine's yaw
is deliberately not used for play-space heading. **`197`-`204` reached the seam
answer from the INPUT side; this is an independent answer from the CAMERA side.
Where they agree, build; where they differ, that difference is the finding.**

**C3. Their `vr/tests/test_controls.c` — 824 lines — is a specification of the
control layer's expected behaviour.** Read it as a spec even if none of it is
adopted.

### ►► PHASE D — THE MEMORY MODEL. ITS OWN DOCUMENT, ITS OWN DECISION. ◄◄

**D1. Cost it, do not start it.** What `portLowAlloc` would mean here: our heap is
`[MEASURED]` at `0x7ff6c4423b70`; the arena has to sit low, and `007-VR` reserves
it at LINK time with `--defsym` because `boss.c` finds the pool from
`_bssSegmentEnd`. **Both ports also PANIC rather than truncate in
`osVirtualToPhysical`.**

**D2. The prize:** every `ge_*_pad`, the `_Static_assert`, the `unk10` collision
and the hand-widened structs stop being necessary. **The cost:** a memory-model
change under a port that boots and plays 27 stages.

**D3. THE GATE FOR EVEN STARTING IT IS PHASE A1** — see §1.1. **And Phase B must
exist first, because this is the largest-blast-radius change anyone could make to
this tree, and `242` §5 is the lesson about changing a lifecycle without a gate
that walks it.**

---

## §3 — WHAT IS EXPLICITLY NOT ADOPTED

- **`007-VR`'s tree as a base** (`246` §1) — never run.
- **`goldenballoon`'s `asset_swap` memo** — our byte-order faults are per-asset
  provenance (`244`); revisit if a third asset class appears.
- **Anything from the six empty forks** (`245` §1).

## §4 — WHAT IS NOT CLAIMED

- **No estimate of Phase D's cost.** D1 is the estimate, and it has not been done.
- **`[ASSUMED]` A2 and A3 will find something.** They are sweeps, not diagnoses.
- **`[ASSUMED]` `vv_theta` is writable as well as readable** in the way C1 needs.
  **27 references is the search space, not the answer.**
