# 225 — P1/P2 PASSED. THE SOURCE ROM BUILDS BYTE-IDENTICAL. THE PIPELINE IS REAL.

**2026-08-27. Tiers per `182`. `224` §5's gate is the subject; P2 and P5 were the pass
conditions. P2 PASSED. P5 NOT YET RUN.**

---

## §1 — THE RESULT

**`[MEASURED]` P1 and P2 of `224` §5 both passed, in one session, on the owner's main PC
via the shipped Docker path:**

| gate | pass condition | result |
|---|---|---|
| **P1** | asset extractor runs, no error | `[MEASURED]` `./scripts/extract_baserom.u.sh` — "Processed: 92, Errors: 0" |
| **P2** | unmodified `make` reproduces the retail sha1 | `[MEASURED]` `checksum.sh` printed **`MATCH!`** — `build/u/ge007.u.z64` == `abe01e4aeb033b6c0836819f549c791b26cfde83` |

> **`224` §5: "IF P2 FAILS, THIS ROAD DOES NOT EXIST AND §3 IS A WISH LIST." IT DID NOT
> FAIL.** The matching decomp builds byte-identical to retail on this machine. Everything
> in `224` §2–§3 is now costable.

**Environment `[MEASURED]`:** Docker (the repo's own `docker-compose.yml` / `Dockerfile`).
The IDO recomp toolchain (`tools/ido5.3_recomp/cc`) built automatically on first `make`.

---

## §2 — THE ONE THING THAT COST THE BUILD: CRLF LINE ENDINGS

**`[INFERRED]` the repo was checked out on Windows with git `core.autocrlf` enabled, so
every text file carried CRLF (`\r\n`).**
**COUNTER-EXAMPLE SEARCH per `182`:** none found — every failure symptom below is a known
CRLF signature, and stripping CR cleared each in turn. No symptom pointed elsewhere.

**`[MEASURED]` the IDO IRIX compiler (`cfe`) is intolerant of `\r`, unlike modern gcc/clang.
Three distinct failure faces, all the same cause:**

1. shell scripts — `/bin/bash^M: bad interpreter` (the shebang's trailing `\r`).
2. C sources/headers — `Unterminated string or character constant`, and
   `Cannot open the file include/PR/gbi.h` (the `#include` line ended in `\r`, so it
   searched for `gbi.h\r`).
3. `assets/images.def` — a **`Warning 513`** flood, one per line (2698 lines), caret
   sitting exactly where the trailing `\r` was, ending in "Too many errors... goodbye."

**THE FIX APPLIED THIS SESSION:** strip trailing CR from text/source files —
`*.sh`, then `*.c/.h/.s/.inc` and the Makefiles, then the `.def` files
(`images.def`, `aicommands.def`). **`.bin` asset files were DELIBERATELY LEFT UNTOUCHED**
— `grep` flags them as text but their `\r` bytes are real data; stripping them would
corrupt the assets. `.py`/`.cpp`/`.hpp`/`.md`/`.yml` were left as-is: Python and native
gcc tolerate CRLF, so they are not build blockers.

**`[READ]` line endings never reach compiled object code — and P2's `MATCH!` PROVES it:
the byte-identical ROM was produced from the CR-stripped tree.** Normalizing was required
to build at all and did not disturb the match.

### THE DURABLE FIX — NOT APPLIED, OWNER'S CALL

**A re-clone on Windows would reintroduce every `\r`.** The one-time prevention is a git
setting (`core.autocrlf=false`, or a `.gitattributes` marking these as `-text`) plus a
renormalize. **NOT DONE — it touches git, and `EVERY GIT COMMIT IS THE OWNER'S`.**
Recorded here so the next session does not re-diagnose it from scratch.

---

## §3 — STATE OF THE WORKING TREE

**`[INFERRED]` many tracked text files in `lib/ge` now differ from HEAD by line endings
only (unstaged).** This is expected and required; it is not a code change. The owner
decides whether to commit the normalization or configure autocrlf and re-checkout.
**Nothing was staged, committed, or branched — the commit remains the owner's, now 39+
documents across both repos.**

---

## §4 — WHAT IS OWED (the rest of `224` §5)

1. **P3** — change one trivial thing in `lib/ge/src`, rebuild. The checksum step recalcs
   automatically (`tools/n64cksum`); build with `make COMPARE=0` once the ROM no longer
   matches retail, so the hash-compare does not fail on purpose.
2. **P4** — feed the modified ROM to `N64Recomp` so `RecompiledFuncs/` regenerates.
   **`[ASSUMED]` — the exact wiring (which `.toml` drives it, how the regenerated funcs
   slot into `build.ps1`) HAS NOT BEEN TRACED. That read is owed before P4 is costed.**
3. **P5** — the real gate: build the VR runtime from the self-built ROM and confirm it
   **boots and is playable**. Only then is `224` §3 fully costable.
4. **Then `224` §3.1 first** — the head rotation into the camera in `bondview.c`, the
   root cause with four faults and the owner's stated priority.

**In parallel and NOT blocked by any of this: `223`'s MTXREC offline frame test — data
already captured in `gevr.log`.** (`224` §6.)

---

## §5 — P4 TRACED. THE RECOMPILE RECIPE, AND A PREREQUISITE `224` DID NOT FLAG.

**`[READ]` `06-replicate.md`, `CMakeLists.txt:53-153`, `us.toml`, `patches.toml`,
`08-where-everything-comes-from.md` §5/§7.**

### THE RECOMPILE PATH FOR GAME CODE (offline, NOT in build.ps1)

```
.\RSPRecomp.exe aspMain.us.toml     # rsp/aspMain.cpp
.\N64Recomp.exe us.toml             # RecompiledFuncs/  (checkpoint: Function count: 3150)
py tools_weaken_patched.py          # run, build once (may fail link), run again — ordering trap
.\build.ps1
```

### THE DISTINCTION THAT EXPLAINS WHY THIS NEVER CAME UP

- **`[READ]` PATCH changes recompile automatically every build** — `CMakeLists.txt:153`
  runs `./N64Recomp patches.toml` → `RecompiledPatches/patches.c`. **Every VR change to
  date lives in `patches/`, which is why the recomp layer has been invisible.**
- **`[READ]` GAME code is FROZEN.** `RecompiledFuncs/*.c` is committed and compiled as
  static source (`CMakeLists.txt:92-94`); N64Recomp is NOT run on the game during a build.
  **`224` §3.1 (`bondview.c`) is game code, so it requires the offline regen above.**

### THE PREREQUISITE `224` UNDER-COUNTED

**`[READ]` `us.toml` feeds N64Recomp a TLB-FREE ROM (`ge007.tlbfree.z64`, sha1
`e6e7bbcd…`) and a symbol map (`dump.toml`).** Neither is what the decomp `make`
produces — P2 matched the **vanilla/retail** ROM (`abe01e4a…`).
**`[READ]` `08` §5: `ge007.tlbfree.z64` = retail + `vanilla_to_tlbfree.xdelta`, a transform
derived ONCE against vanilla.**

> **So a modified `bondview.c` cannot reach the runtime until TWO things exist that are
> NOT documented in this tree: (1) a TLB-FREE build of the MODIFIED ROM/ELF, and (2) a
> `dump.toml` REGENERATED from the modified ELF (addresses shift the moment code changes).
> `224` §5 framed P4 as "feed the modified ROM to N64Recomp"; this is the hard part.**

**`[ASSUMED]` the vanilla→TLB-free xdelta MIGHT apply to a modified ROM** — only if the
edit does not touch the bytes the delta rewrites. **What would settle it:** apply
`vanilla_to_tlbfree.xdelta` to a P3 modified ROM and diff, OR determine whether the decomp
can emit a TLB-free ELF for the `us.toml` `elf_path` route (the decomp has NO TLB-free
target today — "USB" is a DEBUGMENU/USB variant, `Makefile:107`, not this).

### WHAT IS NOT BLOCKED BY THIS

- **`224` §2's 90 Hz delta** and anything expressible as a **patch** — they ride the
  automatic `patches.toml` path and never touch the TLB-free/regen loop.
- **P3** (trivial decomp change → `make COMPARE=0`) — proves the ROM side alone.

### THE NEXT READ THAT CLOSES P4 FOR GAME CODE

1. How `vanilla_to_tlbfree.xdelta` was produced (provenance is NOT in `ge-vr-handoff`),
   and whether it applies to a modified ROM.
2. Whether N64Recomp's symbol-dump mode can regenerate `dump.toml` from
   `build/u/ge007.u.elf` (the decomp DOES emit a symboled ELF).
**Until both are answered, `224` §3.1 is not costable — only patch-expressible work is.**

---

## §6 — P4 GAME-SOURCE PATH: CLOSED. TWO PARTS SOLVED, ONE GATE NAMED.

**`[READ]` `N64Recomp/src/main.cpp:279-382`, `N64Recomp/README.md`,
`docs/upstream-issues/1` line 14, `docs/upstream-issues/5` lines 60-75, `us.toml`.**

### SOLVED — symbol regeneration
**`[READ]` N64Recomp `--dump-context` (`main.cpp:279-282, 371-382`) writes `dump.toml` +
`data_dump.toml` from an `elf_path` config and returns.** So a modified decomp ELF
regenerates the symbol map in one command; addresses shifting under a code change is a
solved, built-in step, not a hand-edit.

### SOLVED — the recompile itself
Mechanical, per `06-replicate.md`: `RSPRecomp aspMain.us.toml` → `N64Recomp us.toml`
(checkpoint `Function count: 3150`) → `tools_weaken_patched.py` (twice, ordering trap) →
`build.ps1`.

### THE ONE REAL GATE — a TLB-FREE build of the modified decomp
**`[READ]` N64Recomp's README lists TLB-mapping support as a PLANNED, UNIMPLEMENTED
feature — it cannot recompile TLB-mapped code.** GoldenEye uses TLB mapping, so the recomp
is fed a **"TLBFREE build of the 100% decomp"** (`upstream-issues/1` line 14, verbatim).
**`[MEASURED]` grep of the whole tree (`*.ld/*.mk/Makefile/*.toml/*.md`) for a TLB-free
target/define/linker-variant: NONE. Only the OUTPUT is present** (`ge007.tlbfree.z64` +
`vanilla_to_tlbfree.xdelta`); `lib/ge` is plain `n64decomp/007` (US/EU/JP/DEBUG/USB only).
**The TLB-free build recipe lives UPSTREAM (cblock85 / kholdfuzion), not on this rig.**
**`[READ]` `upstream-issues/5`: stock N64Recomp mis-computes GoldenEye jump-table ROM
offsets; kholdfuzion's fork fixes it — so a re-recompile must use that fork.**

**TO UNLOCK GAME-SOURCE EDITS (`224` §3.1), THE OWNER NEEDS THE TLB-FREE DECOMP CONFIG:**
1. obtain it from the upstream GE-recomp project, OR
2. reconstruct it — relocate the TLB-mapped segment flat via the linker script (`ge007.*.ld`)
   and stub the three TLB functions `us.toml` already names (`tlbRandomGetNext`,
   `resolve_TLBaddress_for_InvalidHit`, `initTLBPrepareContext`). Bounded but specialized.

### STRATEGIC — most of `224` may NOT need this gate
**`[INFERRED]` `224` §2's 90 Hz lever is setting ONE global, `g_GlobalTimerDelta` — very
likely expressible as a `RECOMP_PATCH` hook, which rides the automatic `patches.toml`
pipeline and SIDESTEPS the TLB-free/game-recompile loop entirely.**
**COUNTER-EXAMPLE SEARCH per `182`:** `bondhead.c:284` DIVIDES by the delta (`224` §2), so a
blanket global write has at least one site that behaves as a rate — the value still needs
wear-testing, but that is a tuning question, not a pipeline one. **The pipeline claim
stands: a global write is patch-reachable.**
**So the TLB-free gate blocks only true structural game rewrites; the highest-ticket item
(90 Hz) and anything patch-expressible do not wait on it. This may reorder priorities.**

---

## §7 — THE 90 Hz SIDESTEP IS NOT HYPOTHETICAL. IT IS ALREADY A SHIPPED PATCH.

**`[MEASURED]` (read of `patches/ge_vr_route_b.c`, and `externs.h:446`): §6's `[INFERRED]`
"the 90 Hz lever is patch-expressible" is CONFIRMED and upgraded — it is already BUILT,
WORN, and is the project's current 90 Hz mechanism. No source build, no TLB-free loop.**

- **`g_GlobalTimerDelta` is patch-reachable** — `patches/externs.h:446`.
- **RB-02 (DONE, WORN):** `ge_vr_route_b.c` patches `waitForNextFrame` to accumulate real
  elapsed counts and feed `updateFrameCounters` the whole sixtieths accrued. `[MEASURED]`
  doc 147: **90 real frames/s, `per1000ms=60` (clock correct), `interpUsed=0`.** Gated on
  `-ViRate` (default 60 = stock path). This is in the standing wear command.
- **RB-03 (BUILT, PARKED):** `geVrApplyFloatDelta()` writes `g_GlobalTimerDelta` = the
  frame's real length in sixtieths (~0.667 at 90 Hz) — also `224` §2's game-speed lever.
  Gated on `-FloatDelta`, **default OFF**.

### WHY RB-03 IS PARKED — AND IT IS THE REAL SOURCE-BUILD CASE FOR THE TIMEBASE
**`[MEASURED]` doc 145: RB-03 makes Bond 1.5x fast.** Root cause `[READ]`
`bondview2.c:7237` — `MoveBond`'s walk is a per-FRAME convergence loop with **no
timestep**, so it ignores `g_GlobalTimerDelta` and speeds up with frame rate. Scaling the
global cannot reach it. Same class as `224` §2's `bondhead.c:284` divide counter-example.

> **SO THE DELTA WRITE ITSELF IS A SOLVED PATCH. The unpatchable remainder is giving
> `MoveBond` (1307 lines) and the handful of non-delta-aware sites a real timestep — game
> logic that is clean at source and awkward as a patch. THAT is `224` §2's genuine
> source-build benefit for the timebase, not the `g_GlobalTimerDelta` assignment.**

### CONSEQUENCE FOR PRIORITY
90 Hz head-tracked frames already ship as a patch. The source build is NOT on the critical
path for 90 Hz rendering — only for smooth 90 Hz WORLD SIM + correct game speed (the
`MoveBond` timestep). That, or a targeted `MoveBond` patch, is the next real decision.

---

## §8 — THE MoveBond TIMESTEP: DOC 145's MECHANISM IS `[READ]`-CONTRADICTED. RE-MEASURE.

**Target: RB-03 (smooth 90 Hz world sim + game-speed control), parked since `145` on a
`[MEASURED]` 1.5x-fast Bond. Read of `game/bondview2.c` MoveBond (def 6322).**

### WHAT THE SOURCE ACTUALLY SHOWS
- **`[READ]` bondview2.c:7220 — the PRIMARY forward walk IS delta-scaled:**
  `move_offset += (headpos·theta_transform) * g_GlobalTimerDelta`.
- **`[READ]` 3943-3961 — the stick-speed ramps (`speedgo`, `speedstrafe`) ARE delta-scaled.**
- **`[READ]` 7237/7411 — the SWAY is NOT: `move_offset += sp220` (no delta), and
  `swayoffset += sp240 * sp220` is a per-frame convergence (`sp240` is a geometric
  displacement RATIO, not a timestep).** Sway is a secondary (lean/bob) contribution.
- **`[READ]` 7218 — `bondviewMoveAnimationTick(maxspeed, speedforwards, ...)`: the head-bob
  that DRIVES `move_offset` (via `headpos`) is animation-driven; whether that animation
  advances per-frame or per-tick is UNMEASURED and is the other candidate.**

### THE FINDING (tiered, per `182`)
> **`145`'s `[MEASURED]` 1.5x STANDS. Its MECHANISM — "the walk is a per-frame convergence
> loop with no timestep" — is `[READ]`-CONTRADICTED: the primary walk has a timestep.**
> A `[READ]` does not overturn a `[MEASURED]`; it reframes WHERE to look. The 1.5x cause is
> mis-attributed and must be RE-MEASURED, not reasoned. Candidates now named: the sway
> convergence (7237/7411) and the animation-driven head-bob locomotion (7218).

### CONSEQUENCE — SMALLER, AND PATCH-EXPRESSIBLE
**The task is NOT "rewrite MoveBond's 1658 lines." The primary walk is already delta-correct;
the fix is a handful of targeted lines (delta-scale the sway convergence and/or the anim
locomotion) — reachable from patch space. RB-03/game-speed does NOT require the source build.**

### THE NEXT STEP IS AN INSTRUMENT RUN, NOT A CODE CHANGE (`48`: measure, do not reason)
The `bondPerSec` / `per1000ms` instrument already exists in `ge_vr_route_b.c` (`145`).
**Owner wear test: run `-ViRate 90 -FloatDelta` vs `-ViRate 90` alone, same corridor, same
stick, ~10 s each; read the `[gevr] clock:` lines.**
- `bondPerSec` differs ~1.5x between the two → located to the float-delta path; bisect sway
  vs anim next.
- `bondPerSec` equal, `per1000ms` ~60 both → `145`'s 1.5x was something else; RB-03 may be
  closer to correct than it was parked believing.
**NOT costable further until this runs. It needs the rig, not the source pipeline.**

---

## §9 — RB-03 A/B RUN, 2026-08-27. THE 1.5x REPRODUCES. `[MEASURED]`.

**`[MEASURED]` two wear runs this session, read off the rig, same corridor:**

| run | flags | gd1000 | per1000ms | Bond speed (mean of moving windows) |
|---|---|---|---|---|
| A | `-ViRate 90` (RB-02) | 1000 | 60 | **605** (97 windows, peak 952) |
| B | `-ViRate 90 -FloatDelta` (RB-03) | 666 | 60 | **917** (61 windows, peak 1362) |

**917 / 605 = 1.52x — doc 145's 1.5x REPRODUCES (90/60), now with a clean instrument.**
Float delta engaged correctly (0.666 = 60/90); clock correct in BOTH (`per1000ms=60`), so
it is Bond's DISTANCE that scales, not the clock. Logs kept: `gevr-keep-fd-off.log`,
`gevr-keep-fd-on.log`.

### WHAT THIS SETTLES
- **RB-02 (fd OFF) is the correct-speed 90 Hz build** — 605 is the baseline Bond speed,
  clock correct, no interpolation. **This is the shippable performance win and it is
  already the standing `-ViRate 90` command.**
- **RB-03 (fd ON) reproduces the 1.5x** and buys only smoother world-object motion (doc
  147: "visible only on the truck at full speed"). Polish, not raw performance.

### WHY THE FIX IS GATED, NOT TRIVIAL
The clean fix needs to instrument the individual `move_offset` contributors INSIDE
`MoveBond` (bondview2.c, 1658 lines) to find the non-delta-compensated term. That is a
game-SOURCE edit — the TLB-free gate of §6. A patch cannot reach inside that function to
split the terms. **So RB-03 is the first real payoff of the source pipeline once TLB-free
is solved, NOT a performance blocker today.**

### RECOMMENDATION
Ship RB-02 for 90 Hz now (correct speed, already in the standing command). Hold RB-03's
smooth world sim as source-build work, gated behind the TLB-free decomp config (§6).

---

## §10 — TLB-FREE CONFIG SCOPED. IT IS A WHOLE-ROM RELOCATION + A RUNTIME COUPLING.

**`[MEASURED]`/`[READ]` this session: retail vs `ge007.tlbfree.z64` byte diff, `ge007.ld`,
`src/init.c`, the tlb_* source files, `src/main/rom_conversion.cpp`.**

### WHAT IT IS
- **`[READ]` `ge007.ld:86`: the `game` code segment is TLB-mapped to virtual `0x7F000000`
  (`inflate` to `0x70200000`).** N64Recomp cannot recompile TLB-mapped code (README:
  unimplemented). TLB-free relocates those segments to flat physical addresses + stubs the
  TLB setup.
- **`[MEASURED]` retail (`abe01e4a`, 12,582,912 B) vs tlbfree (`e6e7bbcd`, 12,653,664 B):
  98% of bytes differ, +70,752 B.** So it is a whole-ROM relink at a different base, NOT a
  stub patch. (The 158 KB xdelta expresses it as copy-with-relocation.)

### SOURCE-SIDE FOOTPRINT (bounded, concentrated)
- **Linker script** `ge007.ld`: repoint `game` off `0x7F000000` and `inflate` off
  `0x70200000` to flat addresses (the four `game.*.ld.inc` follow).
- **TLB stubbing**: `init.c:141-158` (`initTLBPrepareContext`, miss-handler copy to
  `K0BASE`, `osUnmapTLB` loop) + `tlb_manage.c`/`tlb_hardwire.s`/`tlb_resolve.s`/
  `tlb_random.s`. ~110 TLB refs, almost all in those files.
- Gate: no checksum (tlbfree ≠ retail by design); N64Recomp accepts + recompiled game boots.

### THE RUNTIME COUPLING — THE COST DRIVER FOR BASE-CODE EDITS
**`[READ]` `src/main/rom_conversion.cpp:87` applies the stored `vanilla_to_tlbfree`
(`ge_rom_patch`) to the USER's retail ROM at load — the base game is RECONSTRUCTED from the
cartridge dump every launch, not shipped.** So a base-code source edit is NOT self-contained:
a layout-shifting change ripples into THREE coupled regenerations — `RecompiledFuncs`,
`dump.toml` symbols, AND the `vanilla_to_tlbfree` conversion patch — to keep the loaded
image consistent with the recompiled code's address assumptions.
**`[INFERRED]` (counter-example search: none found — the recompiled code is static C while
its data/addresses live in the reconstructed image, so layout shifts must couple).**

### SCOPED CONCLUSION
1. The TLB-free config is bounded but specialized (linker relocation + TLB stubbing +
   revalidation). **Cleanest: OBTAIN it from upstream (cblock85/kholdfuzion already produced
   `ge007.tlbfree` — that IS the recipe), not reconstruct blind.**
2. Even solved, base-code edits carry the multi-regeneration coupling above.
3. **`RECOMP_PATCH` stays the right path for almost everything.** Reserve source for changes
   truly impossible as patches (MoveBond internal instrumentation §8/§9, `224` §3.1's camera
   restructure), and budget the regeneration coupling.

### NEXT STEP TO UNLOCK THE SOURCE PATH
Ask the upstream GE-recomp source (cblock85 / kholdfuzion) for the TLB-free build
configuration + the N64Recomp fork used, rather than reconstructing the linker/TLB transform
from scratch. That is the single highest-leverage action for the whole `224` §3 program.

---

## §11 — THE TLB IS DEMAND-PAGING, NOT JUST MAPPING. "TLB-FREE" = RESIDENCY CONVERSION.

**`[READ]` `src/tlb_manage.c` `tlbmanageTranslateLoadRomFromTlbAddress`, with the generic
N64 TLB-free method mapped onto this tree.**

### THE KEY FINDING
**`[READ]` GoldenEye DEMAND-PAGES the game segment.** On a TLB miss it `romCopy`s an 8 KB
page (`PAGE_SIZE 0x2000`) from `_gameSegmentRomStart + maskedAddress` into a physical block
and installs a TLB entry, with RANDOM replacement across 90 segments
(`tlbRandomGetNext() % TLB_SEGMENT_COUNT`, `MAPPING_TABLE_COUNT 90`). This is Rare's
software virtual-memory scheme: a ~930 KB game segment running in 4 MB RDRAM without being
fully resident.
> **So "TLB-free" is NOT a linker tweak — it is converting a DEMAND-PAGED memory model into
> a RESIDENT one. That is the substance of the transform and the reason it is specialized.**

### THE GENERIC 5-STEP RECIPE, MAPPED TO THIS TREE
1. **Locate TLB ops** — `tlb_manage.c` (pager), `tlb_hardwire.s`, `tlb_resolve.s` (miss
   handler), `tlb_random.s`, `osMapTLB.s`/`unmaptlb.s`; installed `init.c:141-158`. ~110
   refs. `us.toml` already stubs 3 at recomp level.
2. **Stub TLB management** — `initTLBPrepareContext`, the K0BASE miss-handler copy, the
   `osUnmapTLB` loop, and the pager `tlbmanageTranslateLoadRomFromTlbAddress`.
3. **Rebase linker to KSEG0** — `ge007.ld`: `game` `0x7F000000`->`0x80xxxxxx`, `inflate`
   `0x70200000`->flat. Mechanical once residency exists.
4. **Overlays/DMA — THE SUBSTANTIAL STEP** — make `_gameSegmentRomStart.._End` fully
   RESIDENT in flat RAM at boot (one load) and delete the on-demand `romCopy` paging.
   **`[INFERRED]` residency of the whole segment needs the 8 MB expanded RAM** (Rare paged
   precisely to avoid needing it) — **free in the recompiled runtime, so a non-issue for
   this target**. Counter-example search: none — the pager exists specifically because the
   segment does not fit resident in 4 MB.
5. **Checksum** — `n64crc`/`chksum64` for IPL3 hardware/emulator boot. **Likely irrelevant
   here**: N64Recomp reads the ELF/ROM directly and the runtime does not IPL3-boot.

### RECOMMENDATION (unchanged, now with the precise reason)
Steps 1-3 and 5 are mechanical; **step 4 (paging->residency) is a memory-model conversion
and is why OBTAINING the config from upstream (cblock85/kholdfuzion) beats reconstructing.**
They already solved it — it is baked into `ge007.tlbfree.z64` + `vanilla_to_tlbfree`.

---

## §12 — THE 1.5x IS HETEROGENEOUS, NOT UNIFORM. INPUT-SCALING CANNOT FIX IT.

**`[MEASURED]` grep of `g_GlobalTimerDelta` use by subsystem, this session:**
- **delta-aware (correct under FloatDelta):** `prop*` (46), `chr*` (guards, 13), Bond's
  primary walk (bondview2.c:7220).
- **delta-BLIND (1.5x under FloatDelta):** `gunfire*` (0), `bullet*` (0), `explosion*` (0),
  `door*` (0), plus Bond's sway (7237) and animation locomotion.

### CONSEQUENCE FOR THE "LIMIT THE STICK" IDEA
**A stick/input scale touches ONLY Bond's translation. The world is a MIX of correct and
1.5x subsystems, so no single input factor makes it consistent — it would yield a
correct-speed Bond in a mis-timed world (guards/bullets/doors/explosions still 1.5x), worse
than either clean state. Rejected.** (Recorded so it is not re-proposed — `108`.)

### THE REFRAME THAT HELPS
RB-02 (`-ViRate 90`, no FloatDelta) is already 90 Hz + CORRECT speed for everything (delta
= 1.0 on 60 ticks; delta-aware and tick-driven code agree). That is the clean performance
build and it ships today.
**RB-03's smooth-world goal does NOT require the whole TLB-free source loop: the fix is to
delta-scale the NAMED blind subsystems (`gunfire`/`bullet`/`explosion`/`door` + Bond
sway/anim), several of which are small enough to reach as targeted `RECOMP_PATCH`es.**
That is the realistic path to smooth 90 Hz world motion — a patch set, measured per
subsystem, not a source rebuild.

---

## §13 — RB-03 PROPERLY SCOPED. §12 CORRECTED: THE ENGINE IS TICK-BASED.

**`[READ]` grep of the substep-loop structure + `bondviewMoveAnimationTick` dispatch. This
CORRECTS §12, which relied on a buggy per-subsystem grep.**

### THE CORRECTION
**§12's claim that `gunfire`/`bullet`/`explosion`/`door` run 1.5x is WRONG.** `[READ]` they
use `for(i=0; i<g_ClockTimer; i++)` substep loops (e.g. `gunfire.c:4690,4720`). `g_ClockTimer`
stays integer (0/1 at 90 Hz), so those loops run **60 substeps/sec = CORRECT speed** under
RB-03 — they stutter, they are not fast. A `[READ]` corrected the `[INFERRED]` (rule 10).

### THE STRUCTURE
**`[READ]` the game is TICK-BASED: 22 `g_ClockTimer` substep-loop sites across 6 subsystems**
— `bondview2` (10), `propobj` (3), `gunfire` (3), `gun` (2), `front` (2), `bondhead` (2).
`-FloatDelta` (fractional `g_GlobalTimerDelta`) only affects code that DIRECTLY integrates
the delta (Bond primary walk 7220, prop's 46 uses, doc 132's ~208 accumulations). The
tick-looped majority is untouched by it — correct, but not smoothed.

### TWO SCOPES FOR "FIX RB-03 PROPERLY"
- **Scope A — stop the 1.5x (narrow):** delta-scale the FEW per-frame non-delta terms (Bond
  sway `7237`, + a leak audit). `[MEASURED]` Bond 1.5x (§9) traces here. Achievable, but
  payoff is small: smooths Bond's walk only; the tick-looped world still steps at 60 (= RB-02).
  And the leaks live INSIDE `MoveBond` (1658 lines, not wholesale-patchable) -> source gate.
- **Scope B — smooth the whole world at 90 (the real RB-03 goal):** convert the 22 substep
  loops from integer-tick to fractional-delta integration across collision/AI/physics/gun.
  A large, cross-cutting timestep RE-ARCHITECTURE with regression risk everywhere. Cleaner
  at source, still a genuine project. NOT a patch set.

### RECOMMENDATION (measured)
**RB-02 is the correct 90 Hz stopping point** — 90 Hz frames + head tracking + correct speed,
world logic at 60 substeps. RB-03's added value (smooth in-world object motion at 90) is
Scope B: a timestep re-architecture, not a bug fix. Weigh its payoff (smoother guards/props
under an already-90 Hz head track) against that cost before committing. Scope A is cheap but
nearly pointless (barely beats RB-02) and still needs the source gate for the MoveBond leaks.
