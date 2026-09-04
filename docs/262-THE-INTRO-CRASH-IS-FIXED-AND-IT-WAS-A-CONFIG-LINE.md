# 262 — THE INTRO CRASH IS FIXED. IT WAS A CONFIG LINE DISABLING A WORKING FIX.

**2026-08-29j. All `[MEASURED]`. The owner's fourth request for the intro; the
first one that got a session.**

---

## §1 — THE CHAIN, END TO END

```
%APPDATA%\Goldeneye-Native\Goldeneye-Native\goldeneye.cfg : GETV_SLOTFREE = 0
   -> ge_config setenv -> ge_slotfree_on() == 0            [MEASURED: "resolved to 0 (env=0)"]
   -> ge_slot_release() returns immediately, 21 times      [MEASURED: 21x GATED-OFF]
   -> every anim slot LEAKS, across attract-loop cycles
   -> pool exhausts                                        [MEASURED: required=155 free=0 maxcap=420]
   -> modelmgrInstantiateModelWithAnim returns NULL
   -> front.c:8636 modelSetScale(NULL, 0.1f)
   -> EXCEPTION 0xc0000005, fault addr 0x28
```

**`GETV_SLOTFREE=1` -> `anim=47 model=93 unpooled=3` freed, ZERO exceptions, the
full cast twice round.** `[MEASURED]` `run_on_matched.log`: 4,621 frames, no
`EXCEPTION`, no `slotfail`.

### THE OWNER'S OBSERVATION IS WHAT BROKE IT OPEN
> *"It crashed on a different character than normal."*

**A fixed ceiling crashes at the SAME character every time. A LEAK crashes
earlier each cycle.** The crash moved from `CjawsZ` (11th) to `CorumovZ` (7th)
once the attract loop had been round twice. **No sizing theory can produce that,
and it is the single fact that identified a leak rather than a limit.**
`HANDOVER` §5, again.

## §2 — `242` WAS RIGHT, AND `261` §2 IS RETRACTED

**`242`'s park DID take effect.** `261` §2 claimed three ways it had not: the
default is ON, no cfg sits beside the binary, and `getv/goldeneye.cfg` has no
such key. **All three are true and all three are irrelevant — `ge_config.c:34`
search path 4 is the PER-USER config in `%APPDATA%`, and that is the one in
use.** `[MEASURED]` `env=0` on a run whose shell had `Remove-Item Env:GETV_*`.
**I checked three paths and not the live one. Rule 10.**

**And `242` was right to park it in 2026-08-28.** Its three faults were real.
**`250` and `251` then fixed them as independent pointer bugs**
(`bondviewSelectCuff`'s `switchindex << 2`; `->datas[i]`'s 8-byte stride), which
is what makes the re-test valid NOW and would not have been valid then.

## §3 — THE STANDING GATE, WRITTEN BEFORE THE RUN, SCORED AFTER

| # | criterion | result |
|---|---|---|
| 1 | attract loop, full cast, twice round | **PASS** — no crash |
| 2 | pick up a dropped weapon | **PASS** — instant, no weapon-switch first (`242`'s fault 1, GONE) |
| 3 | cycle the whole inventory twice | **PASS** |
| 4 | ammo box contents | **PASS** — mines/grenades/knives for the weapons carried; `252` §6 already found the loot box was never established as a bug |
| 5 | die, load a second level | **PASS** |
| 6 | take damage, keep playing | **PASS** |

## §4 — THE AUDIO SCARE WAS MY OWN INSTRUMENT

`[REPORTED]` *"the sound is delayed again"* on the first `GETV_SLOTFREE=1` run.
**That run was the ONLY one carrying `GETV_SLOTTRACE=1`.** Every subsequent run
with the fix ON and the trace OFF is clean, and `[MEASURED]` the audio init is
byte-identical across all of them — `22050 Hz stereo, 736 samples/frame,
device 2`, same heap, same high-water — as are `pace:` and `clock:`.
**The instrument, not the fix.**

### AND THE OWNER CORRECTED THE MODEL OF THE FAULT
> *"There wasn't a delay. It was slow from the beginning."*

**I had been running duration-matched A/B tests for a fault that is present at
BOOT or not at all.** That made three of my runs unnecessary and one of my
conclusions unsound. **A symptom's SHAPE is a measurement too, and I assumed it.**

## §5 — MY OWN WRONG TURNS, ALL THREE RETRACTED IN PLACE
1. **`ANIM_MODEL_SPARE_SLOTS 10 -> 32`** — wrong axis. `[MEASURED]` the crash did
   not move. Reverted to retail; knob kept.
2. **"raise `GE_RWDATA_SCALE`, the slots are too small"** — falsified by the
   instrument in the same run that was built to test it: `maxcap=420` against
   `required=155`. **Capacity was never short.**
3. **I read `run_slotfail.log` WHILE IT WAS STILL BEING WRITTEN** and reported
   "no crash, instrument never fired." The owner said *"check what happened
   last"* and the file had grown. **`133`'s stale-log trap in a new form: not a
   stale file, an INCOMPLETE one. Check for the terminating record — `EXCEPTION`
   or `game_exit requested` — before reading a log as final.**

## §6 — WHAT REMAINS, AND IT IS ONE LINE OF USER DATA
**The fix is ON by default in `model.c:252` and always has been.** The only thing
holding it off is **`GETV_SLOTFREE = 0` in
`%APPDATA%\Goldeneye-Native\Goldeneye-Native\goldeneye.cfg`** — user data, not
source, and outside the folders this session can reach.
> **ACTION FOR THE OWNER: delete that one line from that file.** Then the fix is
> live with no environment variable to remember. **The knob stays reachable
> (DELETE NOTHING) — it is simply no longer set to the wrong value.**

## §7 — STILL OPEN, UNTOUCHED BY THIS
- **The attract loop repeats the CAST instead of advancing to the gameplay
  demos.** `[REPORTED]` *"it's supposed to do it once and then go to the gameplay
  videos."* The RAMROM replay path — `ramromreplay.c`. **Not investigated.**
- **The `rec=155`/`head=-1` black faces** (`261` §3). Next in order.
- **The green line across the folder art** — `[REPORTED]` *"always been there but
  not in default game."* Port-introduced.
- **Folder 3 lost its save** — probably `GETV_UNLOCKALL` writing four folders
  through a five-slot rotation. **My fixture; mine to fix.**
- **Audio latency ~51 ms** (`229`), `port_audio.c:521` `want.samples 512 -> 256`.
