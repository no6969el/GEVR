# 227 — THE PIVOT: A NATIVE SOURCE PORT, NOT A RECOMP+PATCHES HACK

**2026-08-27. STRATEGIC DIRECTION CHANGE, owner's decision. Tiers per `182`. This
supersedes the recomp-centric plan of `224`/`225` as the PRIMARY direction — but
DELETE NOTHING: the recomp build stays as a working reference and a fallback.**

---

## §0 — THE OWNER'S INTENT, IN HIS WORDS

> *"The source code was released for GoldenEye and there's a Perfect Dark VR reverse
> engineered... I want to use the source code as the main source of me building this and
> use the advantages of having the source code as the main product, so that when I release
> this it's actually special and not just another hack."*

**And the realization that forced this doc:** the owner started building believing he was
working FROM SOURCE with his own ROM. **He was not.** He was building `RECOMP_PATCH` hacks on
top of cblock85's recompiled program, which reconstructs the base game from the ROM via
`vanilla_to_tlbfree` (`225` §6). **All the VR work to date sits on someone else's recompiled
binary, not on the GoldenEye source.**

---


## §0.5 — HOW THE PROJECT GOT ROUTED TO THE RECOMP (and why that was correct THEN)

**`[READ]` `local-only/goldeneye-native/goldeneye-native` (the owner's OWN repo, `no6969el`)
is NOT a game port — it is the owner's from-scratch native-port ATTEMPT + design harness:**
a libultra shim, an RDP backend, a host layer that `[READ]` `RESUME-HERE.md` says **boots the
full intro (legal/Nintendo/Rare/gunbarrel, music, ~1,300 gfx tasks/frame) and crashes
reproducibly at frame 2520, no renderer attached.** Plus design docs (`GE007-VR-ARCHITECTURE`,
`MICROCODE-SPEC`, `VR-PLAN`, `PRIORITIES`).

**`[READ]` `PRIOR-ART.md`, surveyed 2026-08-21:** *"Every working GoldenEye-on-PC effort is
static recompilation. No fork of the decomp contains a native host layer. As of this survey,
ours is [the only one]."* **So on 2026-08-21 a COMPLETE native GoldenEye port did not exist** —
the only native path was to finish building the platform layer by hand (the frame-2520 work).
Against that, a working recomp (cblock85) existed. **The recomp pivot was correct THEN.**

**But `PRIOR-ART.md` line 6 said: *"Re-check before making architecture decisions — this space
moves fast."* IT MOVED:** the decomp hit 100% and `SegfaultEvan/goldeneye-native` finished
exactly that native host layer (all 27 stages boot). **The one obstacle that routed the
project away is gone. This pivot is the re-check the owner's own plan called for.**

**THE NAME COLLISION that caused the confusion:** `no6969el/goldeneye-native` (owner's
incomplete harness) vs `SegfaultEvan/goldeneye-native` (the complete native port). Same name,
different things.

## §1 — WHY THE CURRENT ARCHITECTURE CAN NEVER BE "FROM SOURCE"

**`[READ]` the cblock85 architecture (`225` §5-§6):**
- Base game = the owner's ROM, run-time converted to TLB-free, **statically RECOMPILED** by
  N64Recomp into `RecompiledFuncs/` (frozen), + `RECOMP_PATCH` mods.
- **The TLB requirement is a limitation of the RECOMPILER, not a design choice.** N64Recomp
  cannot recompile TLB-mapped code (its README: unimplemented). GoldenEye TLB-demand-pages
  its game segment (`225` §11). So a TLB-free ROM is mandatory FOR RECOMPILATION.
- "Reverse-engineer the TLB" (the `225` §11 step-4 paging->residency conversion) exists ONLY
  because we are recompiling a ROM.

> **So the answer to "do it ourselves or reverse-engineer the TLB" is NEITHER. There is a
> different architecture where the recompiler — and therefore TLB — does not exist at all.**

---

## §2 — THE PRIOR ART IS NOT A RECOMP. IT IS A NATIVE PORT. `[READ]`

**`[READ]` `local-only/prior-art/perfect_dark_VR` on disk:**
- Has a **`port/` layer** — `port/fast3d` (a reimplemented N64 graphics renderer), `port/vr`
  (OpenXR), `port/src`, `port/include`. A `CMakeLists.txt` builds a **native executable for
  PC and standalone Quest**.
- Its README: *"This VR build is based on the PC port of Perfect Dark"* and *"the Android
  port"*; **runs on Meta Quest Standalone**; the ROM is used **only for assets** ("place ROM
  in the data folder").
- **NO recompiler. NO TLB.** The decompiled C is compiled DIRECTLY to native code.

**This is the architecture the owner was reaching for, and GoldenEye is the same engine as
Perfect Dark — which is why PD has been the prior art all along (`168`).**

---

## §3 — WHAT NOW MAKES IT VIABLE (2026 FACTS)

- **`[REPORTED, web]` GoldenEye 007 is 100% decompiled (2026).** A complete decomp is the
  precondition for a native build.
- **`[REPORTED, web]` a native GoldenEye PC port EXISTS: `SegfaultEvan/goldeneye-native`** —
  "GoldenEye 007 as a native app for Windows, macOS and Linux. Built from the N64
  decompilation, not an emulator. Bring your own ROM." **This is the GoldenEye equivalent of
  the Perfect Dark PC port — the base the VR layer bolts onto.**

**None of this existed maturely when the project started on the recomp. The foundation for a
from-source GoldenEye VR is now real.**

---

## §4 — THE TARGET ARCHITECTURE

```
GoldenEye native PC port (SegfaultEvan, from the 100% decomp)   <- the engine, native, from source
        +  a VR layer  (OpenXR + fast3d stereo + motion aim)    <- ported from Perfect Dark VR (same engine)
        +  the owner's ROM for ASSETS only                       <- no recompilation, no TLB
        =  GoldenEye VR, built from source, Quest-standalone-capable
```

**Three assets already in hand:**
1. **The engine, native:** `SegfaultEvan/goldeneye-native` (evaluate as base).
2. **The VR reference, SAME engine:** Perfect Dark VR's `port/vr` + `port/fast3d`, on disk.
3. **The design knowledge:** 226 docs of `[MEASURED]` GoldenEye VR behaviour — aim/camera
   (`194`, `226`), scale (`159`/`205`), seam (`204`), 6DoF frames, crouch, locomotion. **This
   TRANSFERS even though the recomp CODE does not.** It is the spec for the native VR layer.

---

## §5 — WHAT CARRIES, WHAT DOES NOT (honest)

| | Carries to the native port? |
|---|---|
| The `RECOMP_PATCH` C files (`patches/*.c`) | **NO** — different codebase, different build model |
| RT64 host / OpenXR host glue | **PARTIAL as reference** — the native port uses `fast3d`, not RT64 |
| The 226 docs of measurements & design decisions | **YES — fully. This is the real accumulated value.** |
| The aim analysis (`226`: head falsified, `194` camera fault, clamp is the wall) | **YES — it is exactly the VR-aim spec for the port** |
| Scale / seam / frame conventions | **YES — as design inputs** |

**The VR work was not wasted. The owner now knows precisely how GoldenEye's aiming, camera,
scale and frames behave — which is the hard-won knowledge a native VR layer needs.**

---

## §6 — THE HONEST TRADE-OFF

- **The recomp build WORKS today** — a playable PCVR GoldenEye. The native port starts the VR
  integration fresh on a better foundation and is MORE work to get back to "running in VR".
- **The recomp is PCVR-only** (needs RT64/D3D12 on a PC). **The native port can run standalone
  on the owner's Quest 3** (as PD VR does) — a categorically better product.
- **The recomp is "hacks on a recompiled ROM". The native port is the owner's source code
  compiled into the actual product — "special, not a hack".**

**Owner's decision: pursue the native port as the primary product. Keep the recomp build as a
reference/fallback (DELETE NOTHING).**

---

## §7 — WHAT IS OWED (the plan)

1. **Evaluate `SegfaultEvan/goldeneye-native` as the base** — clone, confirm it builds, runs
   with the owner's ROM, and how its structure maps to Perfect Dark's port framework.
2. **Map Perfect Dark VR's `port/vr` + `port/fast3d` onto it** — what transfers directly
   (same engine), what needs GoldenEye-specific work.
3. **Scope the VR integration** as a phased plan, seeded by the 226 docs: stereo/eye split,
   6DoF head, motion-controlled aim (the `194` camera fix is NATURAL here — a native camera
   is editable C, no TLB gate), scale, comfort/locomotion.
4. **Confirm Quest-standalone target** vs PCVR-first.

**Do §7.1 before anything else — the base has to build with the owner's ROM before any VR
work is costed. Same discipline as `224` §5's P2: prove the foundation first.**

**NOTHING STAGED. THE COMMIT IS THE OWNER'S. The recomp tree and its docs remain; this is a
new primary direction, not a deletion.**
