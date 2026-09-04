# 246 — DO NOT SWITCH THE BASE. TAKE THE IDEAS.

**2026-08-29. Docs run to `246`. NEXT DOC = `247`.**

> # ►►►►►► **`007-VR`'s OWN README, LAST COMMIT: *"THE GAME HAS NEVER BEEN
> # RUN."*** ◄◄◄◄◄◄
>
> **Switching to it would trade a port that boots and plays 27 stages for one
> that has never once had a ROM behind it.**

---

## §1 — THE MEASUREMENT THAT DECIDES IT

`[READ]` `mattymattmattmatt/007-VR`, `port/README.md`, "What is not done",
written in the branch's most recent commit:

> **"The game has never been run.** This is the big one, and it dominates
> everything below. `ge007` links, starts, initialises RDRAM, and stops at the
> missing-ROM message — no GoldenEye ROM exists in the environment this was built
> in, so `init()` has never been called with real data behind it. Every milestone
> here was verified by unit tests, by pixel readback in `ge007-selftest`, or by
> the linker; **none of it was verified by playing the game.** Expect the first
> real boot to find bugs."

**Their own next task is the first boot. Ours passed Phase 0 on 2026-08-27.**

| | ours (`goldeneye-native`) | `007-VR` |
|---|---|---|
| boots from a ROM | **yes** | **never attempted** |
| stages that load and play | **27** | 0 |
| audio | working, ~51 ms latency | microcode written, unrun |
| front end | plays, menus navigate | unrun |
| VR layer | `RECOMP_PATCH`-era design, 226 docs of measurements | **21,524 lines, unrun** |
| test harness | **none** | **selftest + 824 lines of control tests** |

> **THE ASYMMETRY IS THE POINT.** They have the ARCHITECTURE and the TESTS and no
> evidence. We have the EVIDENCE — a working build and 245 documents of measured
> behaviour — and neither the architecture nor the tests. **Taking their tree
> would throw away the only half that has been proven.**

**AND THE RULE THIS SESSION KEEPS RE-LEARNING APPLIES TO REPOSITORIES TOO:
`[READ]` is not `[MEASURED]`.** A source tree that reads well has not been run.
**`236` measured a renderer that was correct and answering the wrong question;
this is the same trap at project scale.**

---

## §2 — WHAT WE TAKE, CHEAPEST FIRST

### ►► TIER 1 — FREE. READS, NOT CODE. ◄◄

**1. `vv_theta`. THE SYMBOL `194` NEEDED.**
`[READ]` `gevr_shim.c` includes `game/bondview.h` and drives
`g_CurrentPlayer->vv_theta`. **`194` named the root cause — the head reaches only
the eye view matrix, the game camera never learns about it — and `224` §3.1 wanted
it moved into `bondview.c`. It was never built here because the symbol was never
named. It is named now.** **This is the single most valuable thing in all four
trees, because it serves the ACTUAL project goal.**

**2. Their composition decision, as prior art.**
`[READ]` body yaw lives in play space; the head's heading is folded into it on
RECENTRE (`body_yaw = wrap_pi(body_yaw + quat_yaw_of(head))`), and *"the engine's
yaw is deliberately not used"* for play-space heading. **`197`-`204` reached the
seam answer from the input side; this is an independent answer to the same
question from the camera side. Compare before building.**

**3. `007portable`'s `cb865c0` as a grep pattern, not a patch.**
`chraiGetCollisionBounds(prop, struct rect4f **, s32 *, f32 *, f32 *)` was called
with four `f32` locals; the callee stores a POINTER through one, 8 bytes into a
4-byte slot, wrecking the local beside it. **Search OUR tree for call sites whose
argument types do not match the prototype**, in `propobj.c` first. **`168` §5's
rule: grep the mechanism.**

### ►► TIER 2 — CHEAP AND HIGH VALUE ◄◄

**4. A framebuffer-readback self-test.** `[READ]` `ge007-selftest` builds a
display list, submits it, and **reads the framebuffer back**, *"because every bug
below left the triangle and draw-call counters looking perfectly healthy."*
> **THAT IS THIS SESSION'S BLIND SPOT NAMED BY SOMEONE ELSE.** `231` §1.3 reasoned
> from `tris submitted=520 drawn=520` and was wrong. **`242` §5 concluded a gate
> must walk the lifecycle; this is how.**

**5. `dkr_ptr_plausible()` / arena bounds** (goldenballoon). A plausibility check
before following a game-supplied pointer. **`243` §2's crash is a `-1` reaching a
dereference; this turns that into a logged refusal.**

### ►► TIER 3 — THE BIG ONE, AND IT NEEDS ITS OWN DECISION ◄◄

**6. The 32-bit arena.** Both other ports confine game-visible memory so game
pointers stay 32-bit and lossless. **`[MEASURED]` ours does the opposite:
`[getv] TLB: not present; heap = 00007ff6c4423b70 .. 00007ff6c6423b70` — our game
heap is at `0x7ff6…`, so a game pointer CANNOT fit in an `s32` at all, and every
struct that holds one has to be widened by hand.** That is the origin of
`ge_anim_pad[256]`, `ge_model_pad[320-40]`, the `_Static_assert`, the
`unk10`/`Model.obj` collision, and the whole of `234`-`243`.

**COST: high. It is not a patch; it is a memory-model change under a port that
already works.** **VALUE: it retires a fault class rather than an instance.**
**NOT TONIGHT, AND NOT WITHOUT A SEPARATE DOCUMENT COSTING IT.**

### ►► NOT TAKEN ◄◄
**`goldenballoon`'s `asset_swap` memo** — elegant, but our byte-order faults are
per-asset provenance (`244`) and the font path already shows the local fix.
**Revisit only if a third asset class turns up.**

---

## §3 — THE PLAN, IN ORDER, UNCHANGED AT THE FRONT

**1. `G-243` — build for the linker map, reproduce the inventory crash, resolve
the `FAULT PC`.** Unchanged, and now with three reference trees to check the
answer against. **Nothing below starts until a crash has a function name.**

**2. Grep for Tier-1 item 3** — mismatched argument types at call sites in
`propobj.c` and the item path. Free, and it may BE the crash.

**3. The ammo re-pickup and loot-box contents** (`243` §1). Still uncharacterised.

**4. `vv_theta`** — read `bondview.c` against `gevr_shim.c` and cost the camera
term. **This is where the project actually goes.**

**5. The self-test harness** (Tier 2), before any further shared-lifecycle change.

**6. THEN Tier 3 gets its own document and the owner's decision.**

**AND THE COMMIT IS AGAIN OVERDUE** — `239`-`246`, plus `build_windows.ps1`'s
map flag and `clone-prior-art.ps1`.

## §4 — WHAT IS NOT CLAIMED

- **No claim `007-VR`'s VR layer is better than ours.** It is unrun. **Its
  ARCHITECTURE is worth reading; its RESULTS do not exist.**
- **No claim the arena approach is right for us.** §2 Tier 3 is a cost to be
  established, not a conclusion.
- **`[ASSUMED]` `vv_theta` is reachable from our tree the way it is from theirs.**
  Same decomp, so very likely — **and `168` §5 says grep `externs.h`/`structs.h`
  before costing anything.**

---

## §5 — AND `vv_theta` IS CONFIRMED PRESENT IN OUR TREE

`[READ]`, checked before costing anything (`168` §5):

```
game/bondview.h:558:  /* 0x0148 */ f32 vv_theta;
```
**27 references across `game/*.c`**, plus two derived fields documented beside it
(*"Computed value from vv_theta, used to calculate boost direction"*).

> **§4's `[ASSUMED]` is discharged: the symbol `007-VR` drives is in OUR
> `bondview.h`, at offset `0x0148`, and it is an `f32` — not a pointer, so none of
> the 64-bit hazards of `245` §4 apply to reading or writing it.**
> **The camera term `194` has wanted since 2026-08-25 is reachable today, on the
> build we already have.**
