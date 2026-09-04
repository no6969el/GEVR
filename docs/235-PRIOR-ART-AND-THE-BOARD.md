# 235 — THE PRIOR-ART CENSUS, AND THE BOARD AS IT STANDS

**2026-08-28. Docs run to `235`. NEXT DOC = `236`.**

> **The owner's point, and it was right: these projects do not call themselves
> GoldenEye.** `[READ]` **MGB64 stands for *"Man with the Golden Build"*.** Its
> GitHub description says only *"a 1997 Nintendo 64 first-person shooter"* — the
> word GoldenEye appears nowhere in it. **A search for "goldeneye" does not find
> it, which is exactly why a census is worth keeping.**

---

## §1 — MGB64. WHAT IT ACTUALLY IS.

`[READ]`, from a shallow clone taken this session:

- **A native source port of GoldenEye from `n64decomp/007`** — the same
  decompilation `goldeneye-native` builds on. **Different author, same base.**
- **THE SAME `src/game/` LAYOUT.** `textrelated.c`, `front.c`, `model.c`,
  `objecthandler.h`, `initunk_005520.c` all exist under the same names.
  **It is diffable against our tree file for file.**
- **THE SAME RENDERER LINEAGE.** `THIRD_PARTY.md` names
  **`Emill/n64-fast3d-engine`** for `src/platform/fast3d/`, with the 2-cycle
  combiner *"additionally derived from the Perfect Dark port"*. **That is the same
  ancestry as `getv/port/fast3d/gfx_pc.c`.** Its text path is a sibling of ours,
  not a stranger.
- **Well beyond a bring-up:** a WebGPU backend (default, `wgpu-native` pinned),
  SMAA, HD texture packs via Real-ESRGAN, cgltf scene decoration, a Dear ImGui app
  shell, CMake, Docker.
- **`[REPORTED]` DISCONTINUED, August 2026**, archived read-only. Its own README:
  *"other community projects have since surpassed this one — seek those out
  instead."* **It names none of them.**
- **No VR, no Perfect Dark integration.** **A reference and a control. NOT a base
  to move to.**

### §1.1 — TWO READS TAKEN, AND ONE IS AN OPEN QUESTION WORTH FLAGGING

`[READ]` **MGB64 kept the N64's aliasing free test.** `model.c:1111`/`:1133`:
```c
if (ptr_allocation_0[i].unk08 == 0) { ... datas = ptr_allocation_0[i].unk10; ... }
```
and `clear_aircraft_model_obj()` is still the bare `objinstance->obj = NULL`.
**No `ge_inuse`, no explicit marker** — i.e. **they did not do what
`goldeneye-native` did, so they cannot have `234`'s bug in `234`'s form.**

`[READ]` and their `Model` still documents `chr` at `0x04`, `obj` at `0x08`,
`datas` at `0x10`, `scale` at `0x14` — **the N64 offsets.**

> **`[ASSUMED]` HOW THEY KEPT THOSE OFFSETS AT 64-BIT IS NOT KNOWN.** The comments
> are the decomp's own and prove nothing about the compiled layout; `objecthandler.h`
> carries `#ifdef NATIVE_PORT extern uintptr_t D_80036418;`, which says they handle
> pointer widening deliberately somewhere. **This is the single most valuable thing
> to read in that tree, because `234` §2 is entirely a consequence of losing the
> `unk08`/`Model.obj` alias — and they appear not to have lost it.**
> **DO NOT ACT ON THIS until it is read properly. It is a lead.**

---

## §2 — THE CENSUS IS INCOMPLETE, AND HERE IS WHY

**`[MEASURED]` three routes to enumerate forks and siblings were tried and two are
blocked:**

| route | result |
|---|---|
| `api.github.com/repos/n64decomp/007/forks` | **HTTP 403** — unauthenticated rate limit |
| `github.com/n64decomp/007/network/members` | **blocked by robots.txt** |
| topic + keyword search | works, but **only finds what a project chooses to say about itself** — and MGB64 deliberately says nothing |

**So the census below is a floor, not a ceiling.** The reliable route is an
authenticated GitHub token against the forks API, which this session does not have.

---

## §3 — `clone-prior-art.ps1`, AND WHY IT IS A SCRIPT AND NOT A DONE DEED

**`[MEASURED]` the assistant's bridge shell has NO GitHub access:**
```
git ls-remote https://github.com/akratch/mgb64
fatal: unable to access ...: Received HTTP code 403 from proxy after CONNECT
```
**The clones have to be made from the owner's own PowerShell.**

**`local-only\clone-prior-art.ps1`** — shallow clones into
`local-only\prior-art\`, **outside both git repos**, **skipping anything already
present** (`161`: `perfect_dark_VR` is pinned at `67ea20c` and must never be
re-fetched):

| clone | why it is on the list |
|---|---|
| `akratch/mgb64` | **the sibling port.** §1 |
| `n64decomp/007` | **a pristine control** against our `vendor/ge-decomp`, which carries the port's `GE_PORT_NATIVE` edits |
| `Emill/n64-fast3d-engine` | **the renderer both ports inherit.** `gfx_pc.c` is GITIGNORED in our tree (`233` §6.1), so this is the only way to see what our copy changed |
| `fgsfdsfgs/perfect_dark` | the PD port our VR fork descends from, and MGB64's combiner source |
| `n64decomp/perfect_dark` | the PD decomp |
| `burnsba/getools` | GE asset tooling |
| `anarqz/007-n64-export` | GE asset exporters — the pipeline `229` §9 fought |

**`Emill/n64-fast3d-engine` earns its place independently of the census.** Our
renderer is untracked, so *"what did this port change in fast3d?"* currently has
**no answer available from our disk at all**, and the menu text is a renderer
question.

---

## §4 — THE BOARD. EVERYTHING OPEN, IN ORDER.

| # | item | state | needs a build? |
|---|---|---|---|
| **1** | **MGB64 Windows release, run against the same ROM** | ready, **nothing done** | **no** — it is a download |
| **2** | **`G-234` — the slot-lifecycle fix** | **written, compiles, never run** | **YES. The only item that does** |
| **3** | **`clone-prior-art.ps1`** | written, **never run** | no |
| **4** | **the wrong SFX** — `GETV_AUDIO_DEBUG=1` + `GETV_AUDIO_TESTSFX=<id>` | built since `229`, **never run**; now has a repro path (`233` §8) | no |
| **5** | **the purple sparkly explosion** | `[UNDIAGNOSED]`. **Its blocker is gone** — the menu was never actually blocking | no |
| **6** | **the menu text** | **SHELVED with five exclusions** (§5) | no |
| **7** | **audio latency ~51 ms** | `229` §20 item 3, untouched. `want.samples 512 -> 256` | yes |
| **8** | **`SETUP.md` §3.5** — fold in `229` §9's two CSV traps | untouched, and **a fresh clone repeats the whole of `229`** without it | no |
| **9** | **`fetch-thirdparty.sh regen`** for the `GETV_RECTPROBE` edit | **REQUIRED BEFORE ANY COMMIT** — `gfx_pc.c` is gitignored (`233` §6.1) | no |
| **10** | **Phase 1 — stereo** (`228` §5) | unblocked, not started | yes |
| **11** | **THE COMMIT** — `230`-`235`, the fix, and the probes | **six docs and a fix now overdue** | no |

## §5 — THE MENU TEXT, SHELVED PROPERLY

**Not abandoned — parked with its exclusions written down, so the next attempt is
cheap:**

1. **The game emits every glyph.** 68,643, zero rejected at any of
   `textRenderGlyph`'s four gates (`231`).
2. **The texrect reaches the RDP correct in every field** — position, NDC, `fmt=4
   siz=1`, tile descriptor, and **real antialiased texels at `addr + tmem*8`**
   (`232`).
3. **Prim alpha is 255**, not zero (`232`).
4. **Fill-rectangle overdraw is excluded** — `GETV_NOFILLRECT=1`, `[REPORTED]` no
   change (`233` §8).
5. **The combiner is correct**: `[READ]` `0x03013000000c1600` decodes against
   `color_comb`'s own packing to **RGB = PRIM, alpha = TEXEL0 x PRIM** — exactly
   what `microcode_constructor` sets.

**What is left is the fragment shader or the GL state, and `Emill/n64-fast3d-engine`
plus MGB64's `src/platform/fast3d/` are the two references that would make that dig
cheap. That is the reason §3 is worth running.**

## §6 — WHAT IS NOT CLAIMED

- **Nothing about MGB64's runtime behaviour.** Not run. §1.1 is a source read.
- **The census is a floor** (§2). Other ports under other names very likely exist.
- **`[READ]` MGB64's README, `THIRD_PARTY.md`, `objecthandler.h` and `model.c`
  only.** Its renderer and its text path have not been read.
