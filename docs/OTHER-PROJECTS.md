# Other projects using GEVR

Public product projects that reuse **GEVR** work — name, docs, tools, design playbook, packaging, or a full-tree fork. This is the opposite direction of [CREDITS.md](../CREDITS.md) (what GEVR borrowed). Here we record **what others took from GEVR**.

**GEVR itself:** [README](../README.md) · Latest playable: [Releases](https://github.com/no6969el/GEVR/releases/latest) · Attribution: **BarZ / [@no6969el](https://github.com/no6969el)**

How this sheet stays honest:

1. **One project per section** — separate entries; do not blend them.
2. **Name the borrow** — brand, docs, tools, design map, packaging, or whole-tree fork. Soft words like “inspired by” are not enough when main pillars moved.
3. **Say what is *not* GEVR** — their own host/VR stack or installer glue when that is true, so the record is not a smear.
4. **Evidence from public trees** — links and paths anyone can check. Not legal advice.

**Scan (2026-09-24):** GitHub repo search (`goldeneye VR`, `goldeneye openxr`, `goldeneye quest`, `GEVR goldeneye`), code search (`no6969el/GEVR`, `com.gevr.port`, `GevrRomStarter`, shared CREDITS phrases), and the public [fork list](https://github.com/no6969el/GEVR/forks) for `no6969el/GEVR`. Re-run when another product ships.

To add or correct a row, open an Issue titled `Other projects: ...` with the repo URL and what moved.

---

## Index

| Project | Platform | Their public credit for GEVR | Recorded here |
|---------|----------|------------------------------|---------------|
| [MrSco/goldeneye-vr](https://github.com/MrSco/goldeneye-vr) | Meta Quest (standalone APK) | “Inspired by” / “inspiration only” | [§ MrSco / goldeneye-vr](#mrsco--goldeneye-vr) |
| [MrSco/GEVR-OpenGLES](https://github.com/MrSco/GEVR-OpenGLES) | GitHub fork of GEVR (PC docs/tools tree) | Fork of GEVR; description calls it “OpenGLES Fork” | [§ MrSco / GEVR-OpenGLES](#mrsco--gevr-opengles) |
| [Mr-Nlce/PCVR-Mods-Installer-Hub](https://github.com/Mr-Nlce/PCVR-Mods-Installer-Hub) (`Core/GoldenEye007VR`) | Windows PCVR installer hub module | Links releases; “standalone OpenXR beta … by no6969el” | [§ Mr-Nlce / PCVR-Mods-Installer-Hub](#mr-nlce--pcvr-mods-installer-hub) |
| [LiquidAzir/GEVR-Goldeneye-VR-](https://github.com/LiquidAzir/GEVR-Goldeneye-VR-) | GitHub fork of GEVR | Fork (inherits GEVR README) | [§ LiquidAzir / GEVR-Goldeneye-VR-](#liquidazir--gevr-goldeneye-vr-) |
| [cualquiercosa327/GEVR](https://github.com/cualquiercosa327/GEVR) | GitHub fork of GEVR | Fork (inherits GEVR README) | [§ cualquiercosa327 / GEVR](#cualquiercosa327--gevr) |

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

## MrSco / GEVR-OpenGLES

- **Repo:** https://github.com/MrSco/GEVR-OpenGLES  
- **Kind:** **GitHub fork** of [no6969el/GEVR](https://github.com/no6969el/GEVR)  
- **Fork created:** 2026-09-18  
- **Description on GitHub:** “OpenGLES Fork of Native from-source GoldenEye VR (OpenXR)…”  
- **Their public credit:** Fork relationship itself; README is still GEVR’s player door (checked tip still points players at GEVR releases / GevrRomStarter)

### Why this is on the sheet

This is the **named workspace** behind [MrSco/goldeneye-vr](#mrsco--goldeneye-vr). The Quest port’s HANDOFF says the Android/OpenGLES work lived **untracked** beside a tracked GEVR PC checkout in a folder called `GEVR-OpenGLES`, then split to `MrSco/goldeneye-vr`. The public fork is the GEVR side of that pair.

### What they took from GEVR

| Area | What moved | Evidence (public) |
|------|------------|-------------------|
| **Whole public GEVR tree** | Full fork of GEVR (`README`, `CREDITS`, `docs/`, `packaging/`, `tools/`, `xr/`, cover art, licence map) | GitHub shows `fork: true`, `parent: no6969el/GEVR`; root listing matches GEVR’s public layout |
| **Brand / player identity** | Ships as **GEVR** in README and box art; still tells players to grab **GEVR** zips and run **GevrRomStarter** | Fork README (tip checked ~vr443.1-era copy of upstream wording) |
| **Provenance for Quest product** | Folder / fork name **GEVR-OpenGLES** is the bridge credited in the Quest port HANDOFF | [MrSco/goldeneye-vr](https://github.com/MrSco/goldeneye-vr) HANDOFF §11.3; this fork’s `full_name` and description |

### What is *not* on this public fork (as of scan)

Compare to upstream at scan time: **0 commits ahead**, ~31 behind — a **stale mirror**, not a divergent OpenGLES product tree on GitHub. No public `android/` / Quest APK tree on this fork tip; the standalone Quest product is the separate [goldeneye-vr](#mrsco--goldeneye-vr) repo. The “OpenGLES” claim in the fork description is **not** backed by a published OpenGLES codebase on this remote.

### Fairer public framing (ours)

> Public **fork of GEVR** used as the PC/docs side of MrSco’s Quest port workspace; Quest product later published separately as `MrSco/goldeneye-vr`.

---

## Mr-Nlce / PCVR-Mods-Installer-Hub

- **Repo:** https://github.com/Mr-Nlce/PCVR-Mods-Installer-Hub  
- **Module:** `Core/GoldenEye007VR/`  
- **Kind:** Third-party **installer / redistributor** for GEVR’s GitHub releases (not a from-source fork)  
- **Their public credit:** README links [GEVR releases](https://github.com/no6969el/GEVR/releases); “Standalone OpenXR beta and ROM starter by no6969el and the contributors credited by the project.”

### What they took from GEVR

| Area | What moved | Evidence (public) |
|------|------------|-------------------|
| **Release pipeline** | Installer downloads **`no6969el/GEVR`** GitHub release zips (fallback tag/asset hard-coded to a GEVR Beta zip) | `Core/GoldenEye007VR/GoldenEye007VR-core.ps1`: `$REPO = 'no6969el/GEVR'`, `$FALLBACK_TAG` / `$FALLBACK_ASSET` / `$FALLBACK_URL` pointing at GEVR release assets |
| **Runtime file contract** | Required file list is GEVR’s ship layout (`Start-GEVR.bat`, `GevrRomStarter.exe`, `goldeneye.exe`, `gevr_prepare.exe`, `gevr-*-boot.cmd`, DLLs, `EXPECTED-ROM.txt`, …) | `$REQUIRED_RUNTIME` array in the same `.ps1` |
| **ROM identity / LocalAppData layout** | USA ROM size + SHA-256 and `%LOCALAPPDATA%\GEVR` cache/saves story taken from GEVR’s documented starter behavior | `Core/GoldenEye007VR/README_GoldenEye007VR.md` (size `12,582,912`, SHA-256 matching GEVR’s EXPECTED-ROM family) |
| **Player docs / quirks / binds** | Hub README restates GEVR Beta limitations, tested runtimes, and control map (including B = reload, dual stick recenter, vr444.1-era notes) | Same README sections “Controls”, “Tested runtimes”, “Beta limitations” |
| **Launch wrapping** | Hub writes `Start-GEVR-Hub.bat` that **calls GEVR’s versioned boot** then launches **GevrRomStarter.exe**, with Hub-side `GETV_SIMHZ=query` / `GETV_FPS` clear | `New-GoldenEyeStage` launcher template in `GoldenEye007VR-core.ps1` |

### What is *not* claimed as GEVR product code

- Hub-owned installer scripts, icon, uninstall, and `Start-GEVR-Hub.bat` wrapper are **their** glue.  
- They do **not** vendor GEVR sources into the Hub tree; they pull the **publisher zip** at install time.  
- They state the Hub never ships or downloads a ROM.

### Fairer public framing (ours)

> Third-party PCVR Hub module that **installs and launches official GEVR Beta zips**, copying GEVR’s file layout, ROM rules, and player documentation into the Hub UI.

---

## LiquidAzir / GEVR-Goldeneye-VR-

- **Repo:** https://github.com/LiquidAzir/GEVR-Goldeneye-VR-  
- **Kind:** **GitHub fork** of [no6969el/GEVR](https://github.com/no6969el/GEVR)  
- **Fork created:** 2026-09-20  
- **Their public credit:** Fork (inherits GEVR README / CREDITS / packaging)

### What they took from GEVR

| Area | What moved | Evidence (public) |
|------|------------|-------------------|
| **Whole public GEVR tree** | Complete fork of the GEVR repository | `fork: true`, `parent: no6969el/GEVR` |

### What is *not* claimed

At scan time: **0 commits ahead** of upstream, behind on `main` — **no unique product work** detected on the fork. Listed because a fork is still a full public copy of GEVR.

---

## cualquiercosa327 / GEVR

- **Repo:** https://github.com/cualquiercosa327/GEVR  
- **Kind:** **GitHub fork** of [no6969el/GEVR](https://github.com/no6969el/GEVR)  
- **Fork created:** 2026-09-22  
- **Their public credit:** Fork (inherits GEVR README / CREDITS / packaging)

### What they took from GEVR

| Area | What moved | Evidence (public) |
|------|------------|-------------------|
| **Whole public GEVR tree** | Complete fork of the GEVR repository | `fork: true`, `parent: no6969el/GEVR` |

### What is *not* claimed

At scan time: **0 commits ahead** of upstream, behind on `main` — **no unique product work** detected on the fork. Listed because a fork is still a full public copy of GEVR.

---

## Checked in the same scan — not recorded as GEVR borrowers

These showed up while hunting GoldenEye / VR ports. They are **not** listed above because public evidence did **not** show them taking GEVR name, docs, tools, or tree (sibling engines, recomps, or unrelated “GoldenEye” software).

| Project | Why seen in the scan | GEVR borrow? |
|---------|----------------------|--------------|
| [Alex-LeTux/perfect_dark_VR](https://github.com/Alex-LeTux/perfect_dark_VR) | Prior art **GEVR credits** (other direction) | **No** — we map from them |
| [jkdansereau/goldeneye-pc-port](https://github.com/jkdansereau/goldeneye-pc-port) | Sibling from-source PC port | **No GEVR cite** in scan targets |
| [mscrnt/Sightline](https://github.com/mscrnt/Sightline) | Native GE Windows port | Code search for `GEVR` / `no6969el` → **0** hits |
| [n64decomp/007](https://github.com/n64decomp/007), recomp trees, ROM tools | Shared GoldenEye ecosystem | Not GEVR-derived VR products |
| Private [no6969el/GEVR-Quest](https://github.com/no6969el/GEVR-Quest) | BarZ workshop copy for Quest study | **Ours** — not a third-party borrower |

If a project above later ships GEVR-branded code or copies GEVR tools/docs, add a full section.

---

## Add the next project

When another product reuses GEVR, add a new `##` section using the same pattern: index row, what they say, what they took (table), what is not GEVR code. Keep each project separate. Update the **Scan** date line when you re-run the hunt.
