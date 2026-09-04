# 260 — THE "BLANK EEPROM" RUN WAS NEVER BLANK, AND THE SAVE IS A FOSSIL.

**2026-08-29h. Read from the owner's own logs on the share. `[MEASURED]`.
The owner reported he cannot start the game — the folder fault — and said the
intro has been raised before and not acted on. Both are addressed here.**

## §1 — `256`'s RETRACTION OF `237` RESTS ON A RUN WHOSE PREMISE WAS FALSE

`256` retracted `237` §1 and **exonerated `eeprom.bin`** on the grounds that
*"the folder fault survived a boot the log confirms was blank."*

### `[MEASURED]` — `run_blank.log` (2026-08-29 04:37), line for line:
```
[getv][save] loaded 512/512 bytes from
  C:\Users\pdbar\AppData\Roaming\Goldeneye-Native\Goldeneye-Native\/eeprom.bin
```
**512 of 512 bytes loaded. THE BOOT WAS NOT BLANK.** `run_align0.log` (04:36) and
`run_clock_60.log` (today, 14:56) load the identical file.

**THE EEPROM LIVES IN `%APPDATA%`, NOT IN `build-windows`.** Whatever was cleared
to make a "blank" run was not the file the game reads. **`eeprom.bin` is NOT
exonerated. `237` §1 is un-retracted and back in the window.**
**Rule 4, and it is the second time in three sessions: verify the instrument —
an instrument that cannot be pointed at the thing in question is not an
instrument for that question.**

## §2 — WHY THE SAVE IS A FOSSIL, AND IT EXPLAINS THE 512 BYTES

`port_save.c:221` — upstream's own comment, never read into our docs:

> *"POSIX `rename()` atomically REPLACES the destination. Windows `rename()`
> REFUSES when the destination exists, with `EEXIST` — so **every flush after the
> file first appeared failed.** Measured on a 900-frame Train run: 112 attempts,
> 112 failures, 0 successes... **No save data has ever persisted on this
> platform.**"*

**THAT IS `F2`, DIAGNOSED, AND IT IS ALREADY FIXED IN SOURCE** — `MoveFileExA`
with `MOVEFILE_REPLACE_EXISTING`, `port_save.c:240`.
**`[MEASURED]` the fix IS in the current 04:36 binary** (`MoveFileExA` and the
new `replace ... failed` string both present), **and today's 14:56 run logged
zero rename/replace failures.**

### **SO THE EEPROM ON DISK IS THE FIRST-EVER WRITE, FROZEN.**
It was created once, when no destination existed and `rename()` therefore
succeeded. **Every write since failed until the `MoveFileExA` fix.** The game has
been booting against a fossil from the first run for the entire project.
**`[INFERRED]` — `182` — but it is the only account consistent with: a file that
exists, loads 512/512, and has a documented write path that could not replace
it.**

## §3 — THE UNBLOCK, AND IT NEEDS NO BUILD

**`GETV_SAVEDIR` (`port_save.c:108`) redirects the save directory.** Pointing it
at an empty folder produces **a genuinely blank EEPROM for the first time in this
project**, without deleting the owner's existing file.
**`[MEASURED]` all of `GETV_SAVEDIR`, `GETV_SAVE_DEBUG`, `GETV_ALIGNPTR`,
`GETV_RECTPROBE`, `GETV_REALCLOCK`, `GETV_FPS`, `GETV_PADS`, `GETV_PAD_SYNTH`
and `GETV_CLOCKTRACE` are present in the 04:36 binary.**

> ### **`257` §7's "BUILD ONCE, THEN RUNS 2 AND 3" IS WRONG. NO BUILD IS NEEDED
> ### FOR ANY QUEUED RUN.** `RUN-SHEET-260` sequenced the folder fix behind a
> ### build and behind four runs that all require starting the game — **the
> ### blocker was placed after the things it blocks. My error.**

## §4 — THE CLOCK INSTRUMENT IS BETTER THAN THE STOPWATCH

`[MEASURED]` from today's run, `GETV_CLOCKTRACE` emits:
```
[getv][clock] 60 fps | waitloop 60 fields/s | speedgraph 60/s |
              g_GlobalTimer 60/s | simdiv 1
```
**`speedgraph N/s` is `259`'s hypothesis as a NUMBER.** At `GETV_FPS=90`:
- **synthetic clock → expect `speedgraph 90/s`** (the sim consuming 90 fields a
  second = the 1.5x), and
- **`GETV_REALCLOCK=1` → expect `speedgraph ~60/s`** while `fps` reads 90.

**No stopwatch needed. `259` is confirmed or killed by one grep of two logs.**
Also `[MEASURED]`: today's run had **`vsync=1`**, so `GETV_VSYNC=0` is mandatory
for any 90 Hz run or the panel caps it and the run is void.

## §5 — THE INTRO. THE OWNER HAS RAISED IT TWICE AND IT HAS BEEN PARKED TWICE.
`229` §20 ranked it below the menu text. `231` §3 grouped it with faults that
were not its own. `237` closed the group. `242` parked the cast-crash fix.
**`256` established the fault is real and specific: 40 of 73 sampled dumps are
entirely zero texels — a 440-byte one-row I8 scanline wipe with `prim` stepping
a grey ramp, while the glyphs in the same run are healthy.**
**It is a live, diagnosed, unfixed render fault, and it has never been given a
session.** `GETV_RECTPROBE=1` reads it and **needs no build** (§3).
**HANDOVER §5: the owner's corrections have outranked the analysis every time
they conflicted. This is the fifth instance and it is a PRIORITY correction
rather than a factual one.**

## §6 — NOT CLAIMED
- No claim the stale EEPROM causes `F1`. §3's run is what tests it.
- `[INFERRED]` only: that the file is a first-write fossil.
- No claim `F2` is fixed in behaviour — **the `MoveFileExA` path is in the binary
  and has never been confirmed to write.** `GETV_SAVE_DEBUG=1` prints `flush #N`.
