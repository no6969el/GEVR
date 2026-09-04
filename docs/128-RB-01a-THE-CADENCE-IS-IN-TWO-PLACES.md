# 128 — RB-01a. THE CADENCE IS IN TWO PLACES, AND ONE OF THEM IS ALREADY PATCHED.

**2026-08-24. `126`'s RB-01a, DONE. A read. It corrects `127`'s file list before
a line of RB-02 was written, which is exactly what it was for.**

---

## §1 — THE QUESTION

**`127` §6 asked: `frametiming.c` is game code reached through the recompiler —
does `waitForNextFrame`'s busy-wait still pace anything, or has the recomp
replaced it?**

---

## §2 — THE ANSWER, IN THREE PARTS

### §2.1 — `waitForNextFrame` IS PATCHED, AND THE PATCH IS DISABLED

```c
/* patches/fps.c:19 */
#if 0
RECOMP_PATCH void waitForNextFrame(void) __attribute__((optnone))
...
#endif
```

**So the STOCK `frametiming.c` version is what runs. `127`'s identification of
that function was correct.**

**BUT THE DISABLED PATCH IS A READY-MADE TEMPLATE FOR RB-02** — same math, same
constants (`MAIN_LOOP_TICK_INTERVAL 0x5eb61` = 387,937, divisor
`(interval*2)+1` = 775,875, both matching `frametiming.c:82` exactly). **RB-02
does not have to invent the patch; it has to finish this one.**

### §2.2 — `waitForNextFrame2` IS LIVE BUT IS NOT THE MAIN LOOP

`patches/fps.c:35`, `#if 1`, and it differs in one line:

```c
frameDelay = speedgraphframes;   /* instead of frameDelay = 1 */
```

**Its only caller is `renderGunbarrelEyeIntroSequence`
(`workbench_theboy.c:126`) — the gunbarrel intro fps fix.** Not the game loop.
**Do not confuse the two; the name invites it.**

### §2.3 — AND THE PART THAT CORRECTS `127`

> ## **`bossMainloop` IS PATCHED (`workbench_theboy.c:476`) AND CARRIES ITS OWN FRAME-SKIP GATE, QUANTISED TO THE SAME 1/60 s.**

```c
/* workbench_theboy.c ~:634, inside case OS_SC_RETRACE_MSG */
mainTickElapsed = (u32) (osGetCount_recomp() - copy_of_osgetcount_value_1);
if ((demoMode == 1 && mainTickElapsed < (MAIN_LOOP_TICK_INTERVAL * (speedgraphframes * 2))) ||
    (demoMode != 1 && mainTickElapsed <  MAIN_LOOP_TICK_INTERVAL))
{
    break;   // Skip frame
}
else {
    ... waitForNextFrame(); ...
}
```

**THE CADENCE IS ENFORCED TWICE:**

| # | Where | Quantum |
|---|---|---|
| 1 | `bossMainloop`'s retrace-driven skip gate | `MAIN_LOOP_TICK_INTERVAL` = 1/60 s |
| 2 | `waitForNextFrame`'s busy-wait, called inside it | the same divide, 1/60 s |

> ### **PATCHING ONLY `frametiming.c` WOULD LEAVE GATE 1 STILL QUANTISING TO 60. `127` §5's "two files" IS WRONG AND IS CORRECTED HERE.**

**And the loop is driven by `OS_SC_RETRACE_MSG`** — the emulated VI retrace. **So
the true origin of the cadence is the recomp runtime's retrace delivery, not
either gate.** Both gates are filters on top of it.

---

## §3 — THE CORRECTED EDIT LIST FOR RB-02

| | File | What |
|---|---|---|
| **1** | **`patches/fps.c`** | Finish the `#if 0` `waitForNextFrame` patch — carry the remainder instead of truncating. **Enable it. It is already written against the right constants** |
| **2** | **`patches/workbench_theboy.c`, `bossMainloop`** | The skip gate must not quantise to a whole `MAIN_LOOP_TICK_INTERVAL`, or gate 1 re-imposes 60 whatever gate 2 does |
| **3** | **`lv.c:979`** | `g_GlobalTimerDelta` fractional — RB-03, unchanged from `127` |

**`frametiming.c` ITSELF MAY NOT NEED EDITING AT ALL** — patching
`waitForNextFrame` replaces it wholesale, and `updateFrameCounters` can stay as
it is if the patch hands it the right `deltaFrames`.

**AND BOTH EDITS ARE IN `patches/`, WHICH IS THE SHORT BUILD PATH** — no new
`RECOMP_PATCH` name is needed for either, since `waitForNextFrame` and
`bossMainloop` are both already patched names. **`07` GOTCHA 4 does not
apply.**

---

## §4 — WHAT ELSE THIS READ TURNED UP

**There is already trace logging in the skip gate** — `[trace] retrace#` and
`[trace] skip#`, both once per 120. **Somebody has been here before with the
same question, and those lines will print the moment RB-02 runs.** Read them
rather than adding new ones.

**`demoMode` has its OWN cadence** — `MAIN_LOOP_TICK_INTERVAL * speedgraphframes * 2`.
**RB-02 must not break demo playback, and demos are how the attract mode runs.**

---

## §5 — WHAT THIS DID NOT ESTABLISH

**Where the retrace messages come from and at what rate.** `OS_SC_RETRACE_MSG`
is delivered by the recomp runtime. **If the runtime already delivers retraces
at the TARGET rate (90) rather than the N64's 60, then gate 1 is what converts
90 retraces into 60 ticks — and RB-02 becomes simpler than §3 suggests, because
the faster clock is already arriving.**

> **THAT IS THE FIRST THING RB-02 SHOULD READ. It is a read, not an experiment,
> and it could shrink the task again.** Filed as **RB-01b**.
