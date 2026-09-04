# 236 — `G-234` PASSES, AND THE FOLDER TEXT WAS NEVER A BUG

**2026-08-28. Docs run to `236`. NEXT DOC = `237`.**

> # ►►►► **`G-234` PASSED. THE SLOT LEAK IS FIXED.** ◄◄◄◄
> # ►►►► **AND `229` §20 ITEM 1 IS WITHDRAWN: THE FOLDER TEXT IS NOT DRAWN
> # BECAUSE THE SAVE FILE IS EMPTY. IT IS WORKING AS WRITTEN.** ◄◄◄◄
>
> **Six documents of instruments — `230` through `235` — measured a renderer that
> was correct the whole time, drawing text the game had correctly decided not to
> draw. The exclusions were all true. THE QUESTION WAS WRONG.**

---

## §1 — `G-234`: PASS, ON BOTH HALVES OF THE GATE

`[REPORTED]` ***"it just kept doing that intro over and over and over again. Like,
it was going through all the people multiple times."***

**That IS the pass.** Before the fix the intro died at the eleventh cast
character; now the attract loop runs indefinitely, as it is meant to.

`[MEASURED]` `run_slot.log`, 21:24:23, against a `goldeneye.exe` of 21:22:13
(newer — `133`), `GETV_MPCHR=1`:

| reading | value |
|---|---|
| cast characters built | **33** |
| distinct `model=` pointers | **ONE.** `00007ff7d26ebbb0`, all 33 times |
| `model=0000000000000000` | **0** |
| `EXCEPTION` | **0** |

**`234` §4's gate was "pointers REPEAT instead of climbing by `0x1c8`". They do not
merely repeat — every cast takes the SAME slot**, which is exactly right: one cast
model is alive at a time, it is released, and the next takes the slot back.
**Before: ten ascending pointers then NULL. After: one pointer, thirty-three
times, no end.**

**AND THE `unk10` RESTORE HELD.** `234` §2 predicted that clearing `ge_inuse`
alone would hand a `ModelFileHeader *` to code expecting rwdata on every reuse.
**Thirty-three reuses, no corruption, no visible model fault `[REPORTED]`.** That
is the first evidence the second half of the fix was needed and correct.

---

## §2 — THE FOLDER TEXT. `[READ]`, AND IT IS ONE `if`.

`front.c:2889`, in the file-select render, per folder:

```c
fileGetHighestStageDifficultyCompletedForFolder(foldernum, &higheststage, &highestdifficulty);

if ((higheststage >= SP_LEVEL_DAM) && (highestdifficulty >= DIFFICULTY_AGENT))
{
    /* the difficulty name  */  textRender(... difficultytext ...)
    /* and "Mission <n>.<m>" */ textRender(... missiontext ...)
}
```

> ## ►► THE TEXT ON A FOLDER IS THAT SAVE FILE'S PROGRESS. ◄◄
> **A folder with nothing completed draws NOTHING, and there is no `else`.**
> Not a colour, not a clip, not a combiner. **The game decides not to emit it.**

### §2.1 — AND THE SECOND PORT SAYS THE SAME THING, INDEPENDENTLY

`[REPORTED]`, the owner, running **MGB64** (`235` §1) against the same ROM:
***"there actually is no text on the files. Just the picture."***

**A DIFFERENT PORT, A DIFFERENT AUTHOR, THE SAME ABSENCE.** `235` §5 said a match
would be "the strongest statement about where the fault is NOT" that this project
has had. **It arrived on the first run.**

### §2.2 — WHY SIX DOCUMENTS OF CORRECT MEASUREMENTS DID NOT CATCH IT

**Every exclusion in `230`-`233` was TRUE and none of them was the question:**

1. the game emits every glyph — **of the text it decided to draw** (`231`)
2. the texrect arrives correct in every field (`232`)
3. prim alpha is 255 (`232`)
4. fill overdraw excluded (`233` §8)
5. the combiner decodes correct (`235` §5)

**`231`'s 68,643 glyphs were real. They were other strings, on other screens.**
The instrument counted glyphs the game asked for; **it could not count a string
the game never asked for, and nothing in the chain was ever asked "should this
text exist at all?"**

> ## ►► THE METHOD LESSON, AND IT IS NEW ◄◄
> **`48` says measure, do not reason. `182` tiers the claims. NEITHER CATCHES A
> WELL-MEASURED ANSWER TO THE WRONG QUESTION.**
> **The missing step was cheap and never taken: BEFORE INSTRUMENTING A MISSING
> OUTPUT, READ THE CODE THAT DECIDES WHETHER TO PRODUCE IT.** One `if` in
> `front.c`, findable in the first ten minutes of `230`.
> **And the thing that finally broke it was the owner describing the screen
> precisely — *"the one that's written on the folders"* — plus a second
> implementation to compare against. `HANDOVER` §5 again: the wear report
> outranks the analysis.**

---

## §3 — SO WHAT IS ACTUALLY WRONG ON THAT SCREEN

`[REPORTED]`, ours versus MGB64, same ROM:

| observation | ours | MGB64 |
|---|---|---|
| text on folders | none | **none** — *not a fault* |
| folders selectable | **only the lower two** | **all four** |
| the picture on the folder | **has a line through it** | no line |

### §3.1 — THE SELECTABLE-FOLDER FAULT HAS A TEN-SECOND TEST

`[MEASURED]` `run_slot.log:351`:
```
[getv][save] loaded 512/512 bytes from C:\Users\pdbar\AppData\Roaming\Goldeneye-Native\Goldeneye-Native\/eeprom.bin
```

**A 512-byte EEPROM image EXISTS on disk and loads clean.** MGB64 was run for the
first time and had **no save at all** — which is the one difference between the
two runs that is not code.

> **`[INFERRED]`: our `eeprom.bin` was written by an earlier, broken build and
> carries half-initialised folder state, so two folders read as unusable.**
> **Counter-example search: a 512/512 read is a successful read, so the file is
> not truncated — the content, not the I/O, would be at fault. And it is possible
> the port simply never initialises unused folders correctly, in which case a
> fresh file reproduces the same two-of-four.**
> **THAT IS THE TEST: move `eeprom.bin` aside and relaunch. NO BUILD.**
> **If all four become selectable, the file was stale. If two still are, the fault
> is in the port's file layer and `eeprom.bin` is exonerated.**

### §3.2 — THE LINE THROUGH THE PICTURE: A CANDIDATE, NOT A DIAGNOSIS

`[READ]` the folder art is a Bond picture chosen per folder —
`select_load_bond_picture(walletinst[n], fileGetBondForFolder(n))` (`front.c`,
file-select tick) — and its display list is patched by
`bgApplyDynamicCCRMLUT(..., CCRMLUT_WALLETBOND)`, gated by **`GETV_WALLETLUT`**
(`front.c:2182-2226`).

**That knob has a documented history of BOTH failure modes:** with the terminator
bug it scanned 200,001 commands with no `G_ENDDL`, wrote as it went, and wedged
the file-select screen; with `bgapply.c` fixed it stops at command 158 and patches
*"exactly the three commands DL_LUT_WALLETBOND is for"*. **The default is now ON.**

**`[MEASURED]` and unexplained: `run_slot.log` contains NO `[getv][ui] walletlut:`
line at all**, though the code prints one unconditionally on that path. **So
either the file-select screen was never reached in that run, or that path did not
execute.** **Establish which before touching the knob** — `GETV_WALLETLUT=0` is
the A/B and it needs no build.

### §3.3 — AND MGB64 IS NOT A VISUAL GOLD REFERENCE

`[REPORTED]` on MGB64 with the same ROM: ***"missing a lot of textures, and things
were just different."*** **It renders our ROM worse in places than we do.** Its
value is as a CONTROL for specific questions — §2.1 is exactly that — **not as a
target to match.**

`[REPORTED]` **the explosion displayed correctly on MGB64.** **So `229` §20 item 4
— the purple sparkly explosion — is OURS and is not shared**, which makes MGB64's
combiner and texture path a worthwhile read when that item comes up.

---

## §4 — THE BOARD, UPDATED

| # | item | change since `235` |
|---|---|---|
| **1** | MGB64 run | **DONE.** §2.1, §3, §3.3 |
| **2** | `G-234` slot fix | **PASSED.** §1 |
| **3** | `clone-prior-art.ps1` | still unrun |
| **4** | wrong SFX | unchanged; `GETV_AUDIO_DEBUG=1` next |
| **5** | purple explosion | **`[REPORTED]` NOT shared with MGB64 — it is ours** |
| **6** | ~~menu text~~ | ► **WITHDRAWN. NOT A BUG.** §2 |
| **6a** | **folders: two of four selectable** | **NEW.** §3.1, and it has a no-build test |
| **6b** | **the line through the folder picture** | **NEW.** §3.2, `GETV_WALLETLUT` |
| 7-11 | latency, `SETUP.md`, `regen`, stereo, **the commit** | unchanged; **the commit is now seven docs and a working fix overdue** |

## §5 — WHAT IS NOT CLAIMED

- **`G-234` proves the slot is recycled and the intro survives 33 casts.** It does
  not prove the other seventeen `clear_*_model_obj` call sites behave; they are
  now reachable and untested.
- **§3.1 and §3.2 are untested.** Both are one run each, neither needs a build.
- **No claim that MGB64's file layer is correct** — only that it offered four
  folders on a fresh save.
