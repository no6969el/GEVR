# Other projects using GEVR

Public product projects that reuse **GEVR** work — name, docs, tools, design playbook, or more. This is the opposite direction of [CREDITS.md](../CREDITS.md) (what GEVR borrowed). Here we record **what others took from GEVR**.

**GEVR itself:** [README](../README.md) · Latest playable: [Releases](https://github.com/no6969el/GEVR/releases/latest) · Attribution: **BarZ / [@no6969el](https://github.com/no6969el)**

How this sheet stays honest:

1. **One project per section** — separate entries; do not blend them.
2. **Name the borrow** — brand, docs, tools, design map, or code. Soft words like “inspired by” are not enough when main pillars moved.
3. **Say what is *not* GEVR** — their own host/VR stack when that is true, so the record is not a smear.
4. **Evidence from public trees** — links and paths anyone can check. Not legal advice.

To add or correct a row, open an Issue titled `Other projects: ...` with the repo URL and what moved.

---

## Index

| Project | Platform | Their public credit for GEVR | Recorded here |
|---------|----------|------------------------------|---------------|
| [MrSco/goldeneye-vr](https://github.com/MrSco/goldeneye-vr) | Meta Quest (standalone APK) | “Inspired by” / “inspiration only” | [§ MrSco / goldeneye-vr](#mrsco--goldeneye-vr) |

---

## MrSco / goldeneye-vr

- **Repo:** https://github.com/MrSco/goldeneye-vr  
- **Release checked:** [v0.1.0](https://github.com/MrSco/goldeneye-vr/releases/tag/v0.1.0) (2026-09-23)  
- **Repo created:** 2026-09-21 (after GEVR’s public Beta wave)  
- **Their one-line credit:** README — GEVR is “the PC VR project that inspired this one.” CREDITS — “Inspiration only — no GEVR code in this tree.”

### Why “inspired by” understates it

Inspiration is a soft word. What moved from GEVR are **main pillars**: product identity, credit framing, measurement tools, and the published PC VR playbook — not a vague mood. Their own HANDOFF also says the port lived in a `GEVR-OpenGLES` folder that held the **GEVR PC repo tracked** beside this port **untracked**, then split into `MrSco/goldeneye-vr`.

### What they took from GEVR

| Area | What moved | Evidence (public) |
|------|------------|-------------------|
| **Brand / package identity** | Android package and application id **`com.gevr.port`**; native library **`libgevr.so`**; log tags and tools under the **`gevr_`** prefix (~37 `gevr_*` paths in tree) | `android/app/build.gradle` (`applicationId "com.gevr.port"`); README install path `Android/data/com.gevr.port/...`; CMake builds `libgevr.so` |
| **Credit sheet** | **CREDITS.md started as GEVR’s** (they say so), then rewritten for their tree. Same honesty rules, prior-art table rows, and phrasing survive | Their CREDITS opening paragraph; shared lines such as “We credit only real influence or reuse”, “Licence first”, “Map vs vendor”, “Game data stays with the player”, StarFox64-VR / MGB64 rows |
| **Measurement tools (byte-identical)** | **`tools/gevr_stereo.py`** and **`tools/dlgrab_scissor_census.py`** — **100% identical** to GEVR’s public copies | Diff against [GEVR `tools/gevr_stereo.py`](../tools/gevr_stereo.py) and [GEVR `tools/dlgrab_scissor_census.py`](../tools/dlgrab_scissor_census.py); their copies still cite GEVR `docs\\49` / `docs\\50` |
| **VR design playbook** | Stereo vs cinema screen gating, recenter chord, and GETV-class behaviors used as targets (VISFAR, ROOMHEAP, ROOMSCISSOR, UNITS_PER_M, etc.) | Commit: “True stereo gameplay, ported from Perfect Dark VR and **gated like GEVR PC**”; HANDOFF cites GEVR docs (`175`, `178`, `CONTROLS`, `KEEP-DEFAULTS-INVENTORY-vr441`, …) and knobs (`GETV_XR_PLAY_SCREEN`, `GETV_XR_RECENTER_CHORD`, `GETV_VR_VISFAR`, …); in-tree comments in `bondview2.c`, `bg.c`, `bgfog.c`, `propobj.c`, `boss.c`, `input.c` |
| **Workspace provenance** | Cooked beside GEVR PC before public split | HANDOFF §11.3: split out of `GEVR-OpenGLES` (“two projects in one folder, the GEVR PC repo tracked and this port entirely untracked”) |

### What is *not* claimed as GEVR product code

Their **playable Quest stack** is primarily:

- **Host:** Perfect Dark PC port under `port/` (vendored)  
- **VR layer:** [Alex-LeTux/perfect_dark_VR](https://github.com/Alex-LeTux/perfect_dark_VR) under `port/vr/` (vendored)  
- **Game:** `n64decomp/007` under `src/`  
- **Their glue:** OpenGLES / Android shim files they named `gevr_*` (not a paste of GEVR’s PC GETV / OpenXR product tree)

So: **no** claim here that they shipped GEVR’s Windows `goldeneye.exe` / GETV sources as the APK. The record is that they still took **GEVR name, GEVR docs/tools, and GEVR’s published VR scheme** while calling it inspiration.

### Fairer public framing (ours)

Closer to honest than “inspired by”:

> Quest / OpenGLES GoldenEye VR port on Perfect Dark’s host + VR stack, **following GEVR’s published PC VR design and tools**, shipping under a **GEVR-branded** package id (`com.gevr.port`).

---

## Add the next project

When another product reuses GEVR, add a new `##` section above the same pattern: index row, what they say, what they took (table), what is not GEVR code. Keep each project separate.
