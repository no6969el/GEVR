# 254 — PHASE A IS CLOSED. NEXT IS STEREO.

**2026-08-29. Docs run to `254`. NEXT DOC = `255`.**

> # ►►►►►► **PHASE 0's SYMPTOM LIST IS EMPTY. `228` §5's ITEM 2 — STEREO — IS
> # NOW THE NEXT THING THIS PROJECT DOES.** ◄◄◄◄◄◄

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
| **A4** | ammo re-pickup, loot box | **DONE.** Re-pickup fixed (§1); the loot box is `[READ]` legitimate behaviour and needs a comparison run, not a code hunt (`252` §3) |

**THREE FIXES SHIPPED THIS SESSION, ALL GATED:** `GETV_CUFFIDX`, `GETV_RWSTRIDE`,
and `ALIGN64_V2_PTR` (ungated; a pure widening). **ONE PARKED:** `GETV_SLOTFREE`,
off by default (`242`).

---

## §3 — WHAT `228` §5 SAYS, AND WHAT HAS CHANGED SINCE IT

`[READ]` `228` §5, "OWED, IN ORDER":
> **1.** Phase 0 — the owner builds and runs his ROM. ► **PASSED 2026-08-27.**
> **2.** *"Then Phase 1 (stereo) — the first VR code, ported from PD VR's Fast3D."*
> **3.** *"Reconcile the two Fast3D versions early (the one real unknown in Phases 1-2)."*

### §3.1 — ITEM 3 IS NOW MUCH BETTER SUPPLIED THAN `228` KNEW

**`228` assumed one reference: Perfect Dark VR's Fast3D. There are now four
relevant trees on disk** (`245`, `246`, `clone-prior-art.ps1`):

| tree | what it gives Phase 1 |
|---|---|
| **`007-VR`** | **`vr/src/gevr_gl.c`, 591 lines of STEREO GL, on OUR decomp** — plus `gevr_xr.c` (1383 lines of OpenXR) and 824 lines of control tests. **UNRUN** (`246` §1) |
| `perfect_dark_VR` | `228`'s original reference. Pinned at `67ea20c`; **DO NOT RE-CLONE** (`161`) |
| `Emill/n64-fast3d-engine` | **the upstream our `gfx_pc.c` descends from** — and `gfx_pc.c` is GITIGNORED here (`233` §6.1), so this is the only way to see what our copy changed |
| `goldenballoon` | a NEWER sibling of the same Fast3D, with WebGPU and Metal backends |

> **`233` §6.1 is the constraint that shapes Phase 1: `gfx_pc.c` reaches the
> repository ONLY through `tools/fetch-thirdparty.sh regen`.** **Every line of
> stereo work in that file has to end in a regen or a fresh clone loses it.**

---

## §4 — BEFORE PHASE 1 STARTS: THE COMMIT

**`247`-`254`, three fixes, and both handover documents are uncommitted.**
`239`-`246` went in at `181a0f7`/`dd5bd6cd`; everything since is loose.

**Three repos, as `243`/`245` established:**
- **`GoldenEyeVR`** — docs `247`-`254`, `HANDOVER.md`, `00-START-HERE.md`,
  `clone-prior-art.ps1`
- **`ge-decomp`** — `bondview2.c`, `model.c`, `model.h`, `propobj.c`, `macro.h`,
  `front.c`. **BY NAME. NEVER `-A`** — that tree has 2,716 files showing as
  modified from CRLF churn (`243`)
- **`goldeneye-native`** — nothing this round unless `gfx_pc.c` is touched

## §5 — WHAT IS NOT CLAIMED

- **`[INFERRED]` the re-pickup was fixed by `250`.** Nobody A/B'd it with
  `GETV_CUFFIDX=0`, and nobody needs to.
- **No claim `007-VR`'s stereo code works** — `246` §1: *"the game has never been
  run."* **It is a design to read, not a patch to take.**
- **Phase 1 is not scoped here.** `255` should do that, and `228` §2's rule
  stands: **gates before code.**
