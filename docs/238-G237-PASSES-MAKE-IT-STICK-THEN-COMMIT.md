# 238 — `G-237` PASSES. MAKE IT STICK, THEN COMMIT.

**2026-08-28. Docs run to `238`. NEXT DOC = `239`.**

> # ►►►► **`GETV_RGBA16BE=1` FIXES THE EXPLOSION.** ◄◄◄◄
> `[REPORTED]` **ARM A: *"it was all sparkly."* ARM B: *"it looks like it's
> working."*** **`229` §20 item 4 is closed.**
>
> ## ►► AND THAT IS THE LAST OF THE FOUR PHASE-0 SYMPTOMS EXCEPT ONE. ◄◄
> **`229` §20 listed four. Item 1 (menu text) was WITHDRAWN as not-a-bug (`236`).
> Item 4 (purple explosion) is now FIXED. Item 3 (latency) is untouched and needs
> a build. ONLY ITEM 2 — THE WRONG SFX — IS BOTH OPEN AND FREE TO TEST.**

---

## §1 — THE RESULT

| arm | `GETV_RGBA16BE` | `[REPORTED]` |
|---|---|---|
| **A** | unset (0) | ***"it was all sparkly"*** — the baseline reproduces |
| **B** | **1** | ***"I saw it right before you closed it. So it looks like it's working."*** |

**`237` §2.1's `[INFERRED]` — one cause, two symptoms — is SUPPORTED:** a
byte-order error inside a 16-bit texel scrambles adjacent texels independently,
giving both a wrong hue and high-frequency speckle. **The sparkle went with the
colour.**

> **HONEST LIMIT, `[REPORTED]` AND NOT HIDDEN: arm B was a GLIMPSE, not a
> sustained look.** **Do not spend a run confirming it** — fold a deliberate look
> at an explosion into the next level run that happens for any other reason, and
> record it then. **If the sparkle turns out to survive at a longer look, `237`
> §3's third row applies and `GETV_SPARKTRACE=1` is the first read.**

---

## §2 — MAKING IT STICK: THE CONFIG FILE, NOT A CODE DEFAULT

**Upstream deliberately did NOT promote this to a default** (`COLOUR_BUGS.md`:
*"the census has no coverage"* — five levels compared byte-identical **because
`GETV_LIGHTTRACE` reports zero RGBA16 uploads in those frames**). **That caution is
correct and we inherit it.**

**So do not edit the default. Put it in the port's own config file**, which
`ge_config.c` supports for **any** raw gate:

**`C:\Users\pdbar\AppData\Roaming\Goldeneye-Native\Goldeneye-Native\goldeneye.cfg`**
```ini
# --- raw escape hatch ---
GETV_RGBA16BE = 1   # docs 237: fixes the magenta/sparkly explosion flare
```

**Why the config file and not a source edit:**

1. **`[READ]` precedence is `command line > GETV_* environment > this file >
   defaults`.** **An explicit environment variable STILL BEATS IT**, so every
   measurement harness and every future A/B keeps working unchanged — including
   `GETV_RGBA16BE=0` to reproduce the fault on demand. **The off-switch survives,
   which is DELETE NOTHING satisfied without touching a line of code.**
2. **It does not enter our diff against upstream.** `233` §6.1: `gfx_pc.c` is
   GITIGNORED and only reaches a commit through
   `tools/fetch-thirdparty.sh regen`. **A default flipped there is a change we
   would have to carry, re-apply and defend forever, for a knob upstream is still
   deciding about.**
3. **It is one line, in a file the port writes itself, and reversible by deleting
   it.**

**THE PROMOTION QUESTION IS UPSTREAM'S AND STAYS OPEN.** What would settle it is
the census they name: frames that actually exercise RGBA16 elsewhere — *"the
wall-hole impact rows 8..15 in `s_impactimages` are RGBA/16b and are the obvious
next subject."*

---

## §3 — ►►►► NOW COMMIT. IT IS THE MOST OVERDUE IT HAS EVER BEEN. ◄◄◄◄

**Since the last commit (`44cc8c8`, Phase 0) this session has produced:**

- **NINE documents**, `230` through `238`
- **A REAL FIX THAT PASSED ITS GATE** — `234`'s slot lifecycle, three files in
  `vendor/ge-decomp`, `G-234` PASS at 33 casts on one slot
- **Two instruments** — `GETV_TEXTTRACE` (`textrelated.c`, committable normally)
  and **`GETV_RECTPROBE` (`gfx_pc.c`, WHICH IS GITIGNORED)**
- **Three faults closed and one withdrawn:** the intro crash, the folder
  selection, the explosion; the menu text withdrawn as never-a-bug

### §3.1 — THE ORDER MATTERS, AND STEP 1 IS THE ONE THAT GETS FORGOTTEN

> **`gfx_pc.c` IS GITIGNORED. `commit-session.ps1` WILL SILENTLY MISS
> `GETV_RECTPROBE` AND SAY NOTHING.** (`233` §6.1)

**1. Regenerate the third-party patch — Git Bash or MSYS2, NOT PowerShell:**
```bash
cd /c/Users/pdbar/Desktop/GoldenEyeVR/goldeneye-native
tools/fetch-thirdparty.sh regen
```
**Then confirm `getv/patches/thirdparty/0001-getv-port-layer.patch` actually
changed.** If it did not, the probe is not in the commit and re-running
`commit-session.ps1` later will not fix it.

**2. Then the commit itself, owner-only, at the main PC, not through the bridge:**
```powershell
cd C:\Users\pdbar\Desktop\GoldenEyeVR
.\commit-session.ps1
```

**Both repos.** `GoldenEyeVR` carries `230`-`238` and
`local-only\clone-prior-art.ps1`; `goldeneye-native` carries the fix, the
instruments and the regenerated patch.

---

## §4 — THE BOARD AFTER THIS

| # | item | state |
|---|---|---|
| ~~1~~ | ~~MGB64 run~~ | **DONE** (`236`) |
| ~~2~~ | ~~`G-234` slot fix~~ | **PASSED** (`236`) |
| ~~5~~ | ~~purple explosion~~ | **FIXED** (`238`) |
| ~~6~~ | ~~menu text~~ | **WITHDRAWN — not a bug** (`236`) |
| ~~6a~~ | ~~folders 2 of 4~~ | **FIXED — stale save** (`237`) |
| ~~6b~~ | ~~line through the picture~~ | **GONE with the save** (`237`) |
| **11** | **THE COMMIT + the regen** | ► **DO THIS NEXT.** §3 |
| **4** | **wrong SFX** | **the only Phase 0 symptom both open and free.** `GETV_AUDIO_DEBUG=1`, repro is copy button then B |
| 7 | audio latency ~51 ms | `want.samples 512 -> 256`, needs a build |
| 3 | `clone-prior-art.ps1` | unrun |
| 8 | `SETUP.md` §3.5 | unwritten; a fresh clone still repeats `229` |
| 10 | **Phase 1 — stereo** (`228` §5) | **unblocked, not started. THE ACTUAL PROJECT** |

> **AND THAT LAST ROW IS THE POINT.** `227` chose the native port **to get VR out
> of `RECOMP_PATCH` hacks and into source.** Phase 0 is passed, its symptom list
> is nearly empty, and **stereo has not been started.**

## §5 — WHAT IS NOT CLAIMED

- **Arm B was a glimpse** (§1). The fix is `[REPORTED]`, not `[MEASURED]`.
- **No claim RGBA16 is correct anywhere but the explosion flare.** Upstream's
  census gap is inherited whole.
- **`G-234` proves 33 cast reuses.** The other seventeen `clear_*_model_obj` call
  sites are now reachable and still untested.
