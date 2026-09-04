# 270 — STAGE 3.2 PASSES. THE MULTI-VIEW MECHANISM IS NOW AN EXISTENCE PROOF, NOT A SOURCE READ.

**2026-08-30. `258` STAGE 3, runs 2 and 3. NO CODE, NO BUILD.**
**STAGE 3.1 (the 60 Hz baseline) WAS NOT RUN — it requires STAGE 2's instrument, which
`267` retracted. A baseline taken today could not fail, which `P5` forbids.**

---

## §1 — ►►►► STAGE 3.2 PASSES ◄◄◄◄
`GETV_STAGE=38 GETV_MP=2 GETV_PADS=2`, `GETV_SIMDIV=1` pinned. `run_stage3_split2.log`.
`[MEASURED]` two independent viewports in ONE display list with ONE swap:

| scissor rect | draws | view |
|---|---|---|
| `(0,40)-(1280,476)` | 5,347 | top half |
| `(0,484)-(1280,920)` | 5,843 | bottom half |

`support_fail=0`. `[REPORTED]` owner: *"launched and ran fine."* No artifacts.

**`258` §1 said `lvlRender` already loops over views with per-view viewport, FOV, aspect and
projection. THAT WAS A SOURCE READ. IT IS NOW A RUN.** The mechanism stereo is built on is
demonstrated working in the shipped code, before a line of stereo exists.
**This is `56`'s move run in reverse and it cost two launches.**

## §2 — STAGE 3.3: FOUR PLAYERS RUN, WITH A VISUAL FAULT
`GETV_MP=4 GETV_PADS=4 GETV_PAD_SYNTH=1`. All four quadrants render
(`(0,40)-(636,476)`, `(644,40)-(1280,476)`, `(0,484)-(636,920)`, `(644,484)-(1280,920)`).
**`258` §2's player-count caveat is answered: four players RUN.** `[ASSUMED]` -> ran.

**`[REPORTED]` black flickering textures that sometimes overlay the image.** Owner likened it
to the artifact `268` fixed. **`GETV_SIMDIV=1` was pinned, so `268`'s divider is NOT the cause.**

## §3 — ►► THE INSTRUMENTS DO NOT SHOW IT, AND THAT IS NOT THE SAME AS HEALTH ◄◄
Checked and **identical or clean in both runs**: `support_fail=0` · `overflow=0` everywhere
(`ccprobe`, mixer `dmem_hi=2656/4096`) · `[getv][zcmp] test_suppressed=0` · `[getv][portal]`
**24 in BOTH**. `unhandled_dl` is 847 (2p) vs 1487 (4p), **but the 2p run was CLEAN at 847, so
that counter does not separate the arms.**
**NO CAUSE IS NAMED.** `268` §4's lesson holds: a fault living between frames is in no single
frame, and an instrument that does not cover a fault reports nothing.

**ONE CANDIDATE, `[INFERRED]`, NOT INVESTIGATED:** `258` §1.5 records that `getPlayerCount()`
drives real game logic including **glass-buffer sizing**. A resource sized off player count is
the right shape for garbage that appears at 4 and not at 2. **Unverified.**

## §4 — WHY THIS DOES NOT BLOCK STEREO
**Stereo is two VIEWS, not two PLAYERS.** `258` §1.5's central warning is never to drive
stereo from `getPlayerCount()` — 173 refs, 35 files, game logic. **The path stereo uses is the
one that came back CLEAN at two views.** The 4-player fault belongs to **STAGE 9**, which
`258` §3.1 already defers.

## §5 — NOT CLAIMED
- **NO performance measurement of any kind.** Stage 2 does not exist; cost is unmeasured and
  was not inferred from how the runs looked. `P5` intact.
- No claim the 4-player fault is or is not the glass buffer.
- No claim about four-player INPUT — `GETV_PAD_SYNTH` pads are deterministic, not played.
- **Stage 3.1 is still owed** and is gated on Stage 2.
