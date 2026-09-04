# 237 — THE PURPLE EXPLOSION IS DOCUMENTED UPSTREAM, WITH A MEASURED FIX

**2026-08-28. Docs run to `237`. NEXT DOC = `238`.**

> # ►►►► **`GETV_RGBA16BE=1`. IT IS IN OUR BINARY, DEFAULT OFF, AND UPSTREAM
> # MEASURED IT TURNING MAGENTA EXPLOSIONS ORANGE.** ◄◄◄◄
> **`229` §20 item 4 has been `[UNDIAGNOSED]` since it was written. It was
> diagnosed, in this repository, in a file nobody had opened: `docs/COLOUR_BUGS.md`.**

---

## §1 — THE FOLDER SCREEN IS CLOSED

`[REPORTED]` after renaming `eeprom.bin` aside: ***"all of them are now
selectable. So that's fixed. The menu looks good."***

**`236` §3.1's `[INFERRED]` is confirmed: the save file was stale**, written by an
earlier broken build, and two folders read as unusable from its contents. **The
port's file layer is exonerated — a fresh EEPROM initialises all four correctly.**

**`236` §3.2 (the line through the folder picture) is also `[REPORTED]` gone** —
"the menu looks good" — **so it travelled with the stale save and was never a
`GETV_WALLETLUT` question.** That candidate is withdrawn unpursued, which is the
cheapest possible outcome for it.

> **AND THE ANSWER TO THE OWNER'S QUESTION IS NO.** *"Did you load me right to the
> main spot?"* — **that launch was a plain boot with no environment at all.** The
> only thing that changed was the stale save moving out of the way. **§3 gives the
> line that does jump straight into a level.**

---

## §2 — THE EXPLOSION. UPSTREAM ALREADY MEASURED THIS.

`docs/COLOUR_BUGS.md` §1, **in the goldeneye-native tree, on our disk the whole
time:**

> **"Explosions render magenta instead of orange. Cause: RGBA16 texel byte order.
> `GETV_RGBA16BE=1` fixes it."**

`[READ]` upstream's own numbers, Bunker 1, frame 680, mean colour of strongly
chromatic pixels in the explosion:

| `GETV_RGBA16BE` | chromatic px | mean RGB | reads as |
|---|---|---|---|
| **0 (our default)** | 207,304 | **(153, 76, 168)** | **magenta** |
| **1** | 156,078 | **(204, 157, 66)** | **orange** |
| 2 (control: u16 swap) | 168,327 | (206, 164, 71) | orange |

**`[READ]` what upstream ruled out, each with the measurement that did it:** not
the paintball cheat (`GETV_IMPACT=1`: `paintball_cheat=0`), not a cheat-array
overrun, **not fog** (three levels, three fog colours, same magenta — if fog were
tinting it the hue would follow the fog), and not RGBA32 (`GETV_LIGHTTRACE` showed
**no RGBA32 uploads exist** in the scene, so the probe was inert).

### §2.1 — AND IT PLAUSIBLY EXPLAINS "SPARKLY" TOO, AS ONE CAUSE

`[REPORTED]` the owner's word is *"sparkly and purple"*, and **"sparkly" is new —
it is not in the corpus.** **`[INFERRED]` a byte-order error inside a 16-bit texel
scrambles adjacent texels independently, which reads as BOTH a wrong hue AND
high-frequency speckle.** **One cause, two symptoms.**
**Counter-example search: `glass2.c:645-665` documents a SEPARATE random-colour
fault — bullet sparks taking their RGBA from the raw bytes of a float after a
struct grew from `0x2c` to `0x38` — but that one is ALREADY FIXED in this tree
(the code reads `unk28..unk2B` by name, with `GETV_SPARKTRACE` as its A/B). So a
second, independent sparkle mechanism existed and has been eliminated, which is
why `[INFERRED]` and not `[ASSUMED]`.**
**If mode 1 fixes the hue and leaves the sparkle, that is the finding and the two
split apart again.**

### §2.2 — WHY IT IS NOT ALREADY THE DEFAULT, IN UPSTREAM'S WORDS

> **"The census has no coverage."** Five levels at mode 0 and mode 1 gave
> byte-identical frames — **which reads like proof of safety and is not**:
> `GETV_LIGHTTRACE` reports **zero RGBA16 uploads in those idle frames.** The only
> observed RGBA16 consumer anywhere is the explosion flare, where the count moves
> **8 -> 9** as the explosion appears.

**So what is established is "mode 1 fixes explosions" and "nothing else measured
uses RGBA16 yet". That is a knob to RUN, not a default to flip** — exactly this
project's own posture, arrived at independently.

**`[MEASURED]` corroboration from our own logs:** `[getv][tex16be]` reads
`16b_images=0 16b_texels=0 | 32b_images=6 32b_texels=5888` on every menu and
early-level frame sampled in `run_tt.log` and `run_rp.log`. **We have never had an
RGBA16 upload in any frame this project has captured** — consistent with the
explosion being the only consumer.

## §2.3 — A CENSUS ERROR OF MINE, RECORDED SO IT IS NOT REPEATED

**`235`/`236`-era env-var sweeps missed `GETV_RGBA16BE` entirely.** The grep was
`getenv("GETV_[A-Z_]*")` — **`[A-Z_]` excludes DIGITS**, so every knob with a
number in its name was invisible. **`GETV_RGBA16BE`, `GETV_RGBA32BE` and anything
else so named were never in the list I read from.**
**Use `getenv("GETV_[A-Z0-9_]*")`.**

---

## §3 — `G-237`. AN A/B ON ONE VARIABLE. NO BUILD.

**Two runs, identical except for the term under test.** `GETV_STAGE` and
`GETV_GIVE` re-route the boot path — a behaviour change by `229` §20's rule — so
they are held CONSTANT ACROSS BOTH ARMS and are not what is being judged.

**ARM A — baseline, confirm the fault with the harness in place:**
```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
cd C:\Users\<USER>\Desktop\GoldenEyeVR\goldeneye-native\getv\build-windows
$env:GETV_STAGE = "9"      # Bunker 1 -- the level upstream measured on
$env:GETV_GIVE  = "25"     # rocket launcher; GETV_GIVE_AMMO defaults to 400
.\goldeneye.exe
```

**ARM B — the one term:**
```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
$env:GETV_STAGE = "9"
$env:GETV_GIVE  = "25"
$env:GETV_RGBA16BE = "1"
.\goldeneye.exe
```

**Fire a rocket at a wall in each. Judge the DIFFERENCE BETWEEN THE ARMS**
(`195` §2's rule), on two axes separately: **HUE** (magenta -> orange) and
**SPECKLE** (sparkly -> smooth).

| outcome | meaning |
|---|---|
| hue fixed, sparkle gone | **one cause, both symptoms.** §2.1 confirmed |
| hue fixed, sparkle remains | **two faults.** The sparkle is its own investigation, and `GETV_SPARKTRACE=1` is the first read |
| neither changes | our explosion is not upstream's magenta, `COLOUR_BUGS.md` §1 does not apply, and **mode 2 is the control to try before anything else** |

**`GETV_RGBA16BE=2` is upstream's own control** (swap the two bytes of each texel,
rather than reversing each 4-byte group). **If mode 1 does something odd, mode 2 is
the next single run, not a code change.**

---

## §4 — WHAT IS NOT CLAIMED

- **Nothing has been run.** Every number in §2 is upstream's, from their tree, on
  their hardware, at mode 0 vs mode 1 — **not ours.**
- **No claim that our purple IS their magenta.** The colours were reported by eye,
  by two different people, on two different builds. **§3's ARM A exists to
  establish the baseline before the fix is judged.**
- **`236` §3.2's `GETV_WALLETLUT` line is withdrawn, not disproved.** It stopped
  mattering when the save was replaced; if the line ever returns, that candidate
  is still on file.
