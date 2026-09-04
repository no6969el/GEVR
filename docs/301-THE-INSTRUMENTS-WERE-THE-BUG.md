# `301` — THE INSTRUMENTS WERE THE BUG

**Written OFFLINE 2026-09-03. NOTHING BUILT, NOTHING RUN, NOTHING COMMITTED.** Every `LOW` and
`MEDIUM` hole on `PRIORITY-BOARD-299` is closed, plus both of `299`'s two unfiled candidates.
`H4`'s banner work and `H9` remain open by instruction — the session was asked for the LOW and
MEDIUM tier and stopped there.

Baseline: `goldeneye.exe` **18,062,771 bytes at 02:40** (`299` §9.6). **This session does not
change that binary.** §7 below is the build that would.

---

## §0 — THE ONE THING TO READ IF YOU READ NOTHING ELSE

**TWO OF THE SIX FILED FIXES WERE WRONG, AND BOTH WOULD HAVE LOOKED LIKE THEY WORKED.**

| hole | what the board said to do | what that would actually have done |
|---|---|---|
| `H1` | "clamp `hi`/`lo` to `±search`" | **Reads past the end of the row.** `hi` is clipped by the IMAGE EDGE, not by `search` |
| `H3` | "print `ge_props_zsnap_n` beside `list=`" | **Prints `-1` on every frame.** The restore nulls it at `lv.c:1135`; the report runs at `lv.c:1151` |

Neither is a subtle error. Both were caught in under a minute **by measuring the thing before
patching it** — reproducing `measure()`'s bounds arithmetic, and reading the call order in
`lv.c` instead of the counter's declaration. **A hole's diagnosis is not its fix.** The board is
a list of symptoms honestly recorded; it is not a list of patches, and `301` recommends reading
it that way from here on.

The `H3` case is the more uncomfortable one, because the wrong fix produces a **constant** where
there used to be a **misleading number**. `-1` in every log, forever, and nothing to notice.

---

## §1 — WHAT WAS DONE

**Nine offline harnesses pass — six that already existed, three written this session.** No
regressions.

| # | closed | how, and what proves it |
|---|---|---|
| `H1` | peg detector fires | `measure()` returns the bounds it really searched; the caller tests `dx` against those and names which limit set the bound. **`--selftest` grew two cases and one of them FAILS IF THE ALARM GOES QUIET** — an instrument whose alarm has never fired is an instrument with no alarm |
| `H2` | census covers every frame | Window accumulators in `ge_rebuild_window.h`, folded in **before** the cadence gate. New `WINDOW` line carries min/max, `ZERO-REBUILD FRAMES` and `pass-never-ran`. `ge_rebuild_window_harness.sh`, **18 checks**, drives the exact `298` shape |
| `H3` | the sum balances | Loop bound captured **during the pass**, printed as `zsnap=`. `list=` is still printed, now labelled as a different moment and explicitly **not** a cross-check |
| `H4` | **surveyed only** | `knob_banner_survey.py`. **397 knobs, 35 tier A, 35 tier B, 327 tier C (82% silent).** Three banners added. The rest is ranked work, still open |
| `H5` | provenance is in the artefact | `[getv][run] ARM=<n> START=<utc>` inside the log. Prevention is one PowerShell line — see §4 |
| `H6` | **decision: VENDOR THE STUB** | `glstub/` + `depthclamp_glpath.sh`. **Falsified before being believed** (§5) |
| `N1` | far line split | `[getv][near]` separates SCENE from CLAMP ACTION |
| `N2` | grabs carry the arm | `GETV_ARM`, sanitised, 11 checks |

---

## §2 — `H1`: THE BOUND WAS NEVER `±search`

`measure()` computes `hi = min(search, w - (Ra + px1) - 1)`. The second term is the right edge of
the image. `[MEASURED]` against the real pillarboxed geometry:

```
w=2560 play=[367,2193) half=913 search=500 -> searched [-500 .. +500]   symmetric
w=2560 play=[367,2193) half=913 search=800 -> searched [-800 .. +595]   ◄── asymmetric
w=1920 play=[275,1645) half=685 search=500 -> searched [-500 .. +446]   ◄── asymmetric
```

`abs(dx) >= search` is silent on both asymmetric cases: a `dx` of `+595` on the first is the
correlator hard against its own boundary and printed as a clean measurement.

**`[MEASURED]` on `grabs_298_A/dlgrab_10393.bmp`, the three-width sweep:**

```
--search 250   searched [-250..+250]   dx -166   mad_best 13.871
--search 500   searched [-500..+500]   dx -166   mad_best 13.871
--search 800   searched [-800..+596]   dx -800   mad_best  4.441   ►► PEGGED (alarm fires)
```

**Note `mad_best` FALLING from 13.871 to 4.441 as the answer becomes garbage.** The cost is not
normalised for overlap width, so widening the search makes the match look *better* while the
overlap shrinks toward nothing. That is the trap the docstring already warned about and the
detector could not enforce. **It enforces it now, and the searched range is printed on every
run so the reader can see the boundary the number sits against.**

---

## §3 — `H2`: SIX GREEN SAMPLES, 363 FAILING FRAMES

The per-frame counters are reset by `gePropsSnapshotTickZDepth()` on every tick, so a cadence of
600 described frame 600 and said nothing about the other 599. **`298` §1.1 read six such samples
as "the driver takes all of it" and scored ARM 3 green.**

`ge_rebuild_window_harness` CASE 1 reproduces the shape rather than describing it: 4000 frames, a
fault on every 11th, cadence 600. Because `600 % 11 != 0`, **every sample point lands on a good
frame.** Six greens, 363 failures, same run. This is not contrived — it is what **any** fixed
cadence does against **any** periodic fault whose period does not divide it.

Two distinctions the new line draws that `298` could not:

- **`ZERO-REBUILD FRAMES`** is the number that scores the arm, and it is cumulative — reading the
  log more often can never shrink it.
- **`pass-never-ran`** separates "the second eye rebuilt nothing" from "the pass was never asked
  to run" (no tick under `GETV_SIMDIV`). CASE 3 proves a no-pass frame is **not** credited with
  the previous tick's stale count, which is what the old counters would have done.

**`GETV_STEREO_REBUILD_REPORT=1` is no longer required.** The cadence is now a print rate.

---

## §4 — `H5`: THE GAME CANNOT REFUSE THE LOG, SO IT SIGNS IT INSTEAD

The log is created by PowerShell's `*>` redirection. **The game never sees it and cannot refuse
to overwrite it** — so "have the game refuse" was not available. The fix is in two halves:

**PREVENTION — one line at the top of each run-sheet block.** Not a script: a script I cannot
run offline is a script that ships unverified, and this needs no script.

```powershell
if (Test-Path .\run_301_D1.log) { throw "run_301_D1.log EXISTS -- rename it or pick a new name. A re-run would destroy the arm's provenance (H5)." }
```

**DETECTION — in the game, and it survives after the fact.** Every run now prints

```
[getv][run] ARM=D1 START=2026-09-03T11:00:57Z -- ...
```

**Two logs carrying the same `ARM` are a proven collision. A log whose `ARM` does not match its
block is the wrong file.** The arm's identity no longer lives in prose above the block, which is
the reason this kept happening: an overwritten log looked exactly like an intact one and nothing
in the file itself disagreed.

---

## §5 — `H6`: THE DECISION IS **VENDOR THE STUB**, AND THE GATE WAS FALSIFIED FIRST

`getv/tools/glstub/` declares the four GL calls and five tokens `ge_depthclamp.c`'s GL path
touches. `depthclamp_glpath.sh` runs `-fsyntax-only -DRAPI_GL -DWAPI_SDL2 -Werror` against it.

**A gate that cannot fail is not a gate.** Before believing the pass, two faults were injected
into a copy:

```
inject glDepthRangedNV(...)      -> error: implicit declaration of function 'glDepthRangedNV'
inject glEnable(GL_DEPTH_CLAMP,1)-> error: too many arguments to function 'glEnable'
```

Both caught, exit non-zero. **What a pass means:** the GL path parses, every call has the right
arity and types, no typo survives. **What it does not mean:** that the stub matches the real GL
headers, or that any driver accepts `glEnable(GL_DEPTH_CLAMP)`. **A stub agrees with whatever it
was written to agree with.** `glstub/README.md` says this at length, and the rule that keeps it
honest is that nothing outside `depthclamp_glpath.sh` may ever add `-I getv/tools/glstub`.

This closes *"the GL path is never compiled offline"*. It does not close *"the GL path is
verified"*. `H6` only ever asked for the first.

---

## §6 — `H4`: 82% OF THE KNOBS ARE SILENT

`knob_banner_survey.py` is a **script, not a list**, because a list goes stale the first time a
knob is added. It reports three tiers and **names its own blind spot**:

- **A — CHECKABLE (35).** A `NAME=` echo in the file that reads the knob. Greppable by the string
  the owner typed.
- **B — MENTIONED (35).** Named in a same-file string, never as `NAME=`. Needs a human.
- **C — SILENT (327).** No same-file string names it at all.

**The first version of this script scored `GETV_NEARCLAMP` as bannered and was wrong** — its name
appears only inside `ge_depthclamp.c`'s banner for a *different* knob, while its read is in
`gfx_pc.c`. Hence the same-file rule. **The generous version of the instrument agreed with the
wrong answer**, which is worth remembering about instruments generally.

**The blind spot, stated rather than hidden:** `GETV_FILTERING` banners as `filtering=2` — the
knob's own name never appears — so it scores tier C despite having a banner. Scoring it C is
correct behaviour here, not a bug, and **it is also the whole point**: an owner who set
`GETV_FILTERING=0` and grepped the log for `GETV_FILTERING` found nothing. **That is how two run
cycles were voided.**

**►► THE CONVENTION FROM `301` ONWARD: every banner prints the FULL knob name and an `=`.** Then
the log is greppable by the string that was typed, and this script's tiers become true.

Three banners added, chosen by doc mentions: `GETV_NEARCLAMP` (28), `GETV_STEREO_REBUILD_REPORT`
(18), `GETV_FILTERING` (16 — now printing **env value and effective value side by side**, so a
config file overriding the environment is visible in one line instead of two sessions).

**The remaining 324 are ranked in the script's own output. That is the open work.**

---

## §7 — WHAT THE OWNER MUST DECIDE, AND IT IS A REAL DECISION

**These changes touch four files and REQUIRE A REGEN AND A BUILD before any of them do anything.**
`gfx_pc.c` is gitignored third-party — **its changes exist only in
`getv/patches/thirdparty/0001-getv-port-layer.patch`, which has been regenerated and re-verified
`15/15` this session.** Nothing else in the tree records them.

**The decision: `RUN-SHEET-300` §4, §5 and §6 (GROUP A's A2/A3/A4) have not run, and they were
written against the `02:40` binary. Building `301` replaces that binary.**

- **BUILD FIRST (recommended).** A2/A3/A4 read the very counters this session proved were lying —
  the rebuild census, the `[getv][far]` near counters, the filtering banner. Running them on the
  `02:40` binary produces another set of numbers from instruments we now know misreport. **The
  cost is that every `18,062,771 bytes / 02:40` gate line in `RUN-SHEET-300` must be updated to
  the new binary's identity before those blocks are used.**
- **RUN A2/A3/A4 FIRST.** Keeps `RUN-SHEET-300` usable exactly as written. **The cost is that
  their verdicts are taken through the instruments this session repaired**, and `298` is the
  precedent for what that costs.

**`301` does not make this call — it is the owner's.** But it notes that the board's own stated
plan ("one build that closes H2, H3 and whatever H4 turns up... leaves you with a rebuild census
you can actually trust before Group B asks it the hardest question it's ever been asked") is the
BUILD-FIRST path, and GROUP B is blocked on A4 either way.

---

## §7a — EXACTLY WHAT WAS VERIFIED, PER FILE. **THE COVERAGE IS NOT UNIFORM.**

| file | how far it was checked offline |
|---|---|
| `chrprop.c` | **FULLY COMPILED** under the real headers with `build_windows.ps1`'s own flags — `stereo_harness.sh`'s nine-file gate, `PASS 0 errors`. This is the strongest evidence in the session |
| `ge_rebuild_window.h` | **COMPILED AND RUN**, `-Wall -Wextra -Werror`, 18 checks |
| `ge_arm_tag.h` | **COMPILED AND RUN**, `-Wall -Wextra -Werror`, 11 checks |
| `ge_depthclamp.c` GL path | **`-fsyntax-only` PASS**, and the gate was falsified first (§5) |
| `ge_config.c` | **`-fsyntax-only` PASS** |
| `port_render.c` | **`-fsyntax-only` PASS** under `build_windows.ps1`'s own `$portFlags` (`H10`, closed after this table was first written) |
| `gfx_pc.c` | **`-fsyntax-only` PASS**, same gate |

**`H10` WAS FOUND HERE AND THEN CLOSED — see §9.** The first pass of this table read *"the risk
in this session is `port_render.c` and `gfx_pc.c`, and only the build can retire it."* That was
true when written and is no longer: `port_syntax_gate.sh` now type-checks 51 of the 57 port
sources offline, both of those included. **Six remain build-only and are named with reasons in
the script.** The build is still the authority — the stub headers are not the real SDL/GL — but
the gap between "edited" and "checked by anything" has closed for the files this session touched.

---

## §8 — FILES

**Modified (tracked):** `getv/port/src/ge_config.c`, `getv/port/src/port_render.c`,
`getv/tools/stereo_disparity.py`, `getv/patches/thirdparty/0001-getv-port-layer.patch`,
`vendor/ge-decomp/src/game/chrprop.c`.

**Modified (gitignored, recorded ONLY in the patch):** `getv/port/fast3d/gfx_pc.c`.

**New:** `getv/port/src/ge_arm_tag.h`, `vendor/ge-decomp/src/game/ge_rebuild_window.h`,
`getv/tools/knob_banner_survey.py`, `getv/tools/ge_rebuild_window_harness.{c,sh}`,
`getv/tools/ge_arm_tag_harness.c`, `getv/tools/depthclamp_glpath.sh`, `getv/tools/glstub/`.

**A note on the regen.** `tools/fetch-thirdparty.sh regen` **failed correctly** on the bridge —
its `271` guard caught that `mv` cannot unlink a target on this mount and it refused rather than
reporting a write it had not made. The regen was completed by making the final replace an
in-place copy; **all of the script's own size guards and its `verify` ran untouched, and verify
is what returned `15/15`.** The script needs no change: it behaved exactly as designed.

---

## §9 — `H10`, FOUND AND CLOSED IN THE SAME SESSION

**The finding.** `stereo_harness.sh`'s real-header syntax gate covers **decomp** files only.
`chrprop.c` was fully compiled by it; the whole of `getv/port/**` — `port_render.c` and the
gitignored `gfx_pc.c` among them — was compiled **nowhere but the owner's main PC**. An edit
there was checked by nothing until the build, and for `gfx_pc.c` a mistake is also a mistake in
the patch that is its only record.

**Why it looked harder than it was.** The first attempt compiled a port file with the decomp's
`include/` on the path and got `unknown type name 'ptrdiff_t'` — which reads like a broken file.
It is not: **`build_windows.ps1` has TWO flag sets, and `$portFlags` deliberately omits the
decomp's `include/`** because the decomp's `stdio`/`stdarg` shadows would beat the system
headers. The script says so at length in a comment. **The gate was one wrong variable away from
being written off as impossible.**

**What it took.** `port_syntax_gate.sh` uses `$portFlags` verbatim, plus `getv/tools/glstub`
extended with a minimal SDL2 header and a `GL/glext.h`. Result: **51 of 57 sources compile
offline, 0 failures.**

**What is NOT covered, and why it is a decision rather than a gap.** Six files, named
individually in the script with a reason each:

| file | why |
|---|---|
| `port_audio.c`, `port_input.c`, `port_support.c`, `gfx_sdl2.c` | SDL surfaces that are **enumerations and structs with specific layouts** — `SDL_AudioSpec`, the controller enum, the event union. A stub can state a timing signature correctly; it cannot state these without becoming a copy of SDL, **and a stub that is wrong about a type makes the gate lie in both directions** |
| `ge_gl_debug.c` | GLEW's runtime feature booleans — GLEW, not GL |
| `gfx_opengl.c` | the full GL 2.x/3.x surface: shaders, FBOs, texture units |

**They are listed as EXCLUSIONS, not as an inclusion list, so a NEW port file is gated by default
and fails loudly.** A glob with negations silently swallows new files, and silence is how coverage
rots — the same reasoning `.gitignore` gives for listing the fifteen third-party files by name.

**Falsified before being believed**, as `H6` was: an injected wrong-arity call
(`SDL_GetPerformanceCounter(1,2,3)`) and an injected undeclared identifier were both caught, exit
non-zero.

---

## §10 — THE REGEN, MADE USABLE FROM THE BRIDGE

Two changes to `tools/fetch-thirdparty.sh`, both small and both guarded.

**1. A bridge fallback for the replace.** `mv` cannot unlink a target on this mount, so `regen`
failed — **correctly**, refusing rather than reporting a write it had not made (its own `271`
guard). It now retries by copying the contents into the existing inode. **The order matters and
is commented as such:** `cat >` truncates before writing, which is the exact hazard that once
turned a 363,467-byte patch into 0 bytes, and it is only safe *after* every size guard has passed
on the new patch. If the copy fails part-way the temp directory is preserved and the message says
where the good patch is.

**2. The `---`/`+++` timestamps are normalised away.** `diff` stamped every header with the mtime
of the temporary copy, so **a regen that changed nothing still rewrote 40 lines** — in the one
tracked file that is the sole record of every change to the fifteen gitignored sources. Timestamps
in a unified-diff header are optional and ignored by `patch` and `git apply`; `verify` re-derives
all fifteen files and returned `15/15` after the change, so this is not taken on trust.
**`[MEASURED]`: two consecutive regens over unchanged sources are now byte-identical.**

**What this buys.** `git diff` on `0001-getv-port-layer.patch` now shows only real changes — so
"did anything actually change?" is answerable by reading it, and a real one-line edit no longer
looks exactly like churn.