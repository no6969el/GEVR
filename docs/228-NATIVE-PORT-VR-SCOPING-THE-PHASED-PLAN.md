# 228 — NATIVE-PORT VR: THE SCOPING AND PHASED PLAN

**2026-08-27. Follows `227` (the pivot). Tiers: `[READ]` = read on disk this session,
`[REPORTED, web]` = from the GE-native repo/README. STRATEGY + PLAN, nothing built.**

---

## §1 — THE TWO FOUNDATIONS ARE ARCHITECTURALLY PARALLEL

**`[REPORTED, web]` `SegfaultEvan/goldeneye-native`** — GoldenEye from `n64decomp/007`, built
native with **SDL2 + OpenGL + a Fast3D display-list renderer**. Win/mac/Linux (+ iOS/tvOS
Metal bring-up). **All 27 stages boot.** MIT. **`GETV_SIMDIV`/`GETV_INTERP` already decouple
sim from render and interpolate the camera — the 90 Hz/judder problem this project fought
(RB-02/RB-03) is ALREADY SOLVED in this port.** Layout: `getv/port/src` (platform/main),
`getv/port/fast3d` (renderer, GE-specific additions; core Fast3D fetched not vendored).

**`[READ]` `perfect_dark_VR` (on disk)** — the SAME engine family, native, with a VR layer:
- `port/vr/vr_openxr.cpp` (98 KB) — OpenXR session/swapchain/frame-loop/stereo/pose.
- `port/vr/vr_input.cpp` (59 KB) — motion-controller aim mapping.
- `port/vr/vr_settings.cpp`, `vr_hub.cpp`, `vr_android_jni.cpp` (Quest standalone), imgui UI.
- **Stereo lives in a VENDORED Fast3D** (`port/fast3d/gfx_opengl.cpp`, `gfx_pc.cpp`,
  `gfx_sdl2.cpp` modified for per-eye).
- **Frame hook is 3 calls** (`port/src/pdmain.c:631-683`):
  `vr_begin_frame_and_update_poses()` -> `lvTick()` -> `vr_end_frame_and_submit()`.
- **MIT, (c) 2022 Ryan Dwyer.**

> **Both descend from the same Fast3D PC-port lineage (Emill). Same renderer, same SDL2/GL
> stack, same engine. Adding VR to GE-native = porting PD VR's `port/vr` + its stereo Fast3D
> onto GE-native's `port/src` + `port/fast3d`.**

---

## §2 — THE PHASED PLAN (gates before code, per `48`)

### PHASE 0 — PROVE THE BASE (owner action; the P2 of this road)
Clone `goldeneye-native`, build it (`getv/build_windows.ps1` / `build.sh`), run with the
owner's ROM. **GATE: native GoldenEye boots and plays on the owner's machine. NO VR work is
costed until this passes** — same discipline as `224` §5 P2.

### PHASE 1 — STEREO IN THE RENDERER
Reconcile PD VR's vendored stereo Fast3D against GE-native's Fast3D version, and port the
per-eye split (`gfx_opengl.cpp`/`gfx_pc.cpp`). **GATE: two eye images render on the desktop
(side-by-side), correct per-eye frustums.** `[READ]` PD's `10`-era stereo validation method
transfers.

### PHASE 2 — OPENXR + 6DoF HEAD
Port `vr_openxr.cpp`; wrap GE-native's tick loop with the 3-call structure (§1). **GATE:
headset shows the game in stereo, head-tracked, stable frame pacing** — and GE-native's
`GETV_SIMDIV`/`GETV_INTERP` already gives the 90 Hz decoupling for free.

### PHASE 3 — MOTION-CONTROLLED AIM (the owner's priority)
Port `vr_input.cpp`; map it to GoldenEye's aim system. **THIS is where the 226 docs are the
spec** — GE's aim entry points, the `field_A38` aim point, `gunfire.c`, and above all the
**`194` camera fix (head rotation into the game camera in `bondview.c`) — now ordinary
editable C, NO TLB gate, NO recompiler.** `226` proved the aim bug is the camera never
learning the head; native source fixes it directly. **GATE: hand-aimed shooting; the bullet
follows the gun and stays correct when you turn.**

### PHASE 4 — SCALE / COMFORT / LOCOMOTION
Seed from the docs: scale (~25, `159`/`205`), seam (`204`), physical crouch (`176`),
head-relative locomotion (U-25). **GATE: worn, comfortable, correctly scaled against a guard.**

### PHASE 5 (STRETCH) — STANDALONE QUEST
GE-native has iOS/tvOS Metal but not Android/Quest; PD VR has `vr_android_jni.cpp` + an
Android build. Standalone Quest = a NEW platform target for GE-native — significant.
**PCVR-first; Quest-standalone as a stretch goal.**

---

## §3 — LICENSE / RELEASE (why this ships clean)
**`[READ]` GE-native MIT + PD VR MIT ((c) Ryan Dwyer) = an MIT product.** Fast3D is
"fetched, not vendored, licence unresolved" in BOTH upstreams — handle identically.
**Attribution owed:** PD VR (Ryan Dwyer), GE-native (SegfaultEvan), Fast3D (Emill/sm64ex),
the `n64decomp/007` decomp. **This is a clean, releasable, from-source product — the opposite
of the recomp+patches situation.**

## §4 — WHAT THE 226 DOCS BECOME
Not code that ports, but the **design spec** for Phases 3-4: the aim analysis (`194`/`226`),
scale, seam, frame conventions, comfort findings. The measurement work is the reason Phase 3
can move fast.

## §5 — OWED, IN ORDER
1. **PHASE 0 — owner builds `goldeneye-native` and runs his ROM.** Everything gates on this.
2. Then Phase 1 (stereo) — the first VR code, ported from PD VR's Fast3D.
3. Reconcile the two Fast3D versions early (the one real unknown in Phases 1-2).

**NOTHING STAGED. THE COMMIT IS THE OWNER'S. This is a NEW tree (a fork of goldeneye-native),
not the recomp repo — the recomp stays as reference (DELETE NOTHING).**

---

## §6 — PHASE 0 RUNBOOK (concrete; owner action)

**`[REPORTED, web]` `SegfaultEvan/goldeneye-native` `wiki/Setup.md`. The owner already holds
the two hardest inputs:**
- **The ROM:** needs US, **sha1 `abe01e4aeb033b6c0836819f549c791b26cfde83`** — the SAME clean
  ROM the recomp P2 build matched today. Already in hand.
- **The decomp:** clones `n64decomp/007` — the owner already has it as `lib/ge`.

**Steps:**
1. `git clone https://github.com/SegfaultEvan/goldeneye-native`
2. `tools/fetch-thirdparty.sh fetch` — 15 port-layer files (Fast3D + audio mixer, sm64ex).
3. `git clone https://github.com/n64decomp/007 vendor/ge-decomp`
4. apply `getv/patches/0001-source.patch`, place the ROM, generate asset sources (reads the
   ROM; ~746 generated TUs), apply `getv/patches/0002-assets.patch`.
5. supply `deps/SDL2-2.30.9`.
6. build+run: WSL/Linux `sudo apt install build-essential pkg-config libsdl2-dev libgl1-mesa-dev`
   then `./getv/build_linux.sh all`; or native Windows `getv/build_windows.ps1` (mingw-w64).

**GATE (the P2 of this road): native GoldenEye boots and plays with the owner's ROM. No VR
work is costed until this passes.** Once it does, Phase 1 (stereo, from PD VR's Fast3D) begins.

**NOTE:** asset generation is a multi-pass sequence (`docs/SETUP.md` §2.4/§3) — do not shorten
it; a skipped pass fails to compile or misbehaves quietly.
