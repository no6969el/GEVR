# 254 — PHASE A IS CLOSED.

**2026-08-29. Docs run to `254`.**

---

## §1 — A4 CLOSED

`[REPORTED]` ***"Everything is fine. I reported that last time."***

**The ammo re-pickup works.** `[MEASURED]` it is fixed, and `[INFERRED]` it went
with `250`'s cuff stride — the pickup path runs through `gunUpdateAndFire`, which
is where `bondviewSelectCuff` is called from, and the same fix removed the slow
pickup (`251` §1).

> **AND THE OWNER IS RIGHT THAT HE REPORTED IT.** `G-250`'s gate step 1 was *"pick
> up a dropped weapon"* and he answered *"INSTANTLY"*; `G-251`'s step 2 asked for
> the loot box and he answered that too. **The re-pickup was inside what he
> reported and I asked for it again anyway.**
> **`252` §6 warned about flattening a wearer's report; this is the mirror error —
> failing to credit one.** **A gate is also a record: what it asked, and what came
> back, is the answer, and re-asking costs the owner a run.**

---

## §2 — PHASE A, FINAL STATE

| | item | outcome |
|---|---|---|
| **A1** | resolve the crashes | **DONE.** Two crashes, two fixes, both gated and passed (`248`-`251`) |
| **A2** | the stride/narrowing sweep | **DONE.** 122 sites found, 1 fixed, 121 triaged and registered (`253`) |
| **A3** | the `-1` enum sweep | **NOT DONE, AND NO LONGER JUSTIFIED.** `249` `[MEASURED]` the fault addresses were NON-CANONICAL, not sentinels; the evidence that motivated A3 evaporated. **Left on file as a standing hazard, not a task** |
| **A4** | ammo re-pickup, loot box | **DONE.** Re-pickup fixed (§1); the loot box is `[READ]` legitimate behaviour (`252` §3) |

**THREE FIXES SHIPPED THIS SESSION, ALL GATED:** `GETV_CUFFIDX`, `GETV_RWSTRIDE`,
and `ALIGN64_V2_PTR` (ungated; a pure widening).
