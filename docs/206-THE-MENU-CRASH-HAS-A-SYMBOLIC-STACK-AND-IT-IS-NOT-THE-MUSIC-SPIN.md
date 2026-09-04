# 206 — THE MENU CRASH FINALLY HAS A SYMBOLIC STACK. IT IS THE MODEL MATRIX PATH, NOT `137` §4's MUSIC SPIN.

**2026-08-25. Tiers per `182`. Resolved from `build/Release/GoldenRecomp.map`
against the crash handler's own frame dump.**

---

## §1 — THE STACK, RESOLVED

**`[MEASURED]` `gevr.log:6628`:**

```
code 0xC0000005 on thread 23332
access violation READING address 0x284FFEE0005
fault at GoldenRecomp.exe+0x15DA41
```

**Resolved against the linker map (preferred base `0x140000000`):**

```
mainproc  ->  bossEntry  ->  bossMainloop  ->  lvlRender  ->  propsTick
          ->  chrTick    ->  subcalcmatrices  ->  instcalcmatrices
          ->  modelUpdateMatrices  ->  process_02_position (+0x1F5)
          ->  sub_GAME_7F06DEC0 (+0xA1)     <-- FAULT
```

**IT IS THE CHARACTER/MODEL MATRIX PIPELINE**, reading a pointer that is not
memory: `0x284FFEE0005` is wild, **not near null** — so it is a CORRUPT or STALE
pointer being followed, not a missing null check.

> **AND THE CRASH HANDLER PAID FOR ITSELF.** `137` §4 recorded this crash a
> hundred documents ago as *"mashing A through the boot menus crashes it"*, with
> **no stack and a guess.** The handler was already in the build; **all that was
> missing was resolving the offsets against the map file that the linker has been
> writing all along.** No new instrumentation was needed - only the read.

---

## §2 — ►► `137` §4's SUSPECT IS FALSIFIED ◄◄

`137` §4 named *"`musicTrack1Play`'s `while (alCSPGetState(...))` spin"* as the
specific suspect.

**THAT IS A HANG. THIS IS AN ACCESS VIOLATION, ON A THREAD RUNNING THE MODEL
MATRIX PATH, WITH NO AUDIO FRAME ANYWHERE IN THE STACK.** The two cannot be the
same fault. **`137` §4's suspect is retired** — and it is worth noting it was
tiered as a suspect rather than a finding, which is why retiring it costs
nothing.

---

## §3 — WHAT THE RUN LOOKED LIKE AT THE MOMENT IT DIED

**`[MEASURED]`, the last frame of instrumentation before the fault:**

- **`VRGATE/s: ... inLevel=0 | (world_camera() gate - front end, cutscene)`** —
  **THE FRONT END, exactly as `[REPORTED]`:** *"this happens when I go through the
  menu."*
- `render passes: eye0=90 eye1=0`, `stereo=0` — **correct and expected** for the
  front end (`175` §1: a null eye split is a normal state there).
- `90.0 fps`, `LATE 1/91 (1%)`, frame budget healthy. **It was not struggling.**
- `AIM fwdHead=(0.000,0.000,0.000)`, `SHOT n/a(no-shot-path-yet)` — **the hand and
  aim paths were NOT running.**

> ### **AND NO GoldenEyeVR FRAME APPEARS IN THE STACK.**
> Every resolved symbol is stock game code. `hand_override`, `viewmodel_delta`,
> the seam, the aim and the muzzle are **absent — and were provably inactive**
> (the aim ray was all zeroes). **That is evidence, not comfort: it means the
> obvious VR suspects can be set aside for THIS crash.**

---

## §4 — WHAT IT IS NOT YET, AND THE TEST THAT DECIDES

**`[ASSUMED]` — IT IS NOT ESTABLISHED WHETHER THIS IS OURS AT ALL.**
`137` §4 already wrote the discriminating test and **nobody has run it in a
hundred documents:**

> *"The first question is whether it is ours: try it at stock, with no `-ViRate`.
> If it only happens at 90, RB-02 caused it. If it happens at stock too, it
> belongs with B3/B4 in `39`."*

**THAT TEST IS NOW WORTH MORE THAN IT WAS**, because a symbolic stack makes both
outcomes actionable: at stock we would compare the SAME stack, and a match would
place it in the game's own model pipeline for good.

**AND A SECOND, CHEAPER READ IS AVAILABLE FIRST:** `chrTick` -> `subcalcmatrices`
-> `instcalcmatrices` -> `modelUpdateMatrices` are all in `lib\ge\src\game`
(`00-START-HERE` records the tree's location). **`process_02_position +0x1F5` and
`sub_GAME_7F06DEC0 +0xA1` can be read directly** to see WHICH pointer is
dereferenced there. **That is a read, not a launch, and it costs nothing.**

---

## §5 — WHAT IS OWED

1. **THE READ** (§4): what does `sub_GAME_7F06DEC0` dereference at `+0xA1`, and
   what feeds `process_02_position`?
2. **`137` §4's STOCK TEST** — `-NoXr`, no `-ViRate`. **Does the same stack
   appear?**
3. **NEITHER IS ON TODAY'S CRITICAL PATH.** The owner's focus is the world's
   perspective and then `B1`. **This document exists so the stack is not lost** —
   it is the first hard evidence this crash has ever had.

> **AND ONE PRACTICAL NOTE FOR EVERY FUTURE CRASH:** the offsets in
> `[gevr-crash]` resolve against `build/Release/GoldenRecomp.map` with the
> preferred base `0x140000000`. **Copy the log aside before relaunching** — the
> map is rebuilt with the binary, so a stack and its map must be kept together
> or the symbols are gone.

**NOTHING STAGED. THE COMMIT IS THE OWNER'S.**
