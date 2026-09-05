# `316` — **`H24` IS THREE ARMS AND ONE OF THEM PREDATES IT, THE BAR IS CLEARABLE OFF DISK, AND X1's FIRST QUESTION IS A BINDING NOBODY MEASURED**

**2026-09-05.** OFFLINE ASSISTANT. **NOTHING BUILT, RUN, STAGED, BRANCHED, MERGED OR TAGGED BY THE
ASSISTANT. NO ARM RAN. EVERYTHING HERE IS READ OFF THE BRIDGE — LOGS, PICTURES, SOURCE AND `git` —
RATHER THAN TAKEN ON A PASTE.** Binary UNTOUCHED; no preamble ran because nothing ran.
**NOTHING IS PATCHED IN THE PRODUCT AND NOTHING IS PATCHED IN THE INSTRUMENT. THE COUNT OF WRONG
FILED FIXES STAYS AT FIVE.**

---

## §0 — WHAT THIS SESSION ESTABLISHED, IN ONE TABLE

| | |
|---|---|
| **1** | **BOTH COMMITS ARE IN AND NOTHING IS OWED.** `[MEASURED, BRIDGE]` `GoldenEyeVR` HEAD **`b9a1861`** carries all eight `314`/`315` docs; `goldeneye-native` HEAD **`ae95633`** carries `getv/tools/stereo_disparity.py` alone, `83 insertions(+) / 3 deletions(-)`, **`24,413` bytes, `CRLF=0`**, path clean. `-- repo/docs` is **exactly 57** files, all ` M`, none staged. **`NEXT-SESSION-PROMPT-316`'s "NEITHER WAS IN" was true when it was written and is not true now** |
| **2** | **►►►► `H24` HAS A THIRD ARM AND IT PREDATES `H24` BY TWO SESSIONS.** `[MEASURED, BRIDGE]` `313_wide1` — six pictures, `GETV_WIDESCREEN=1` at `2560x1369`, `tanR-tanL=1.079632` — reads `x=[0..2560) width=2560 half 1280` against a log printing `912.667`. **`H24`'s corpus is 18 pictures across THREE arms, not twelve across two** |
| **3** | **AND `313` §2.3 ALREADY DIAGNOSED IT, CORRECTLY, WITH THE `368` px IN IT.** It disposed of that arm and did not generalise; `315` §5 rediscovered the same mechanism on the next two arms and named it. **The hole was never new. What was missing was the sentence "every `WS=1` arm, at any window"** |
| **4** | **►►►►►►►► THE EYE RECTANGLE IS A PER-ARM CONSTANT AND EVERY LOG PRINTS IT.** `[MEASURED, BRIDGE]` `run_314_wsON.log`, `run_314_wsOFF.log` and `run_315_wsONb.log` carry **exactly TWO** distinct `ours: x= ... w=` rectangles across **`9,234` / `7,312` / `18,908`** `VIEWPORT n64` lines. **There is no staleness question. This is NOT `H22` and must not be reasoned about like it** |
| **5** | **THE DETECTOR AGREES WITH THE BACKEND EVERYWHERE ELSE.** `[MEASURED, BRIDGE]` the **committed** tool's own `play_area()` over **94 grabs / 15 arms**: on **71 grabs across 11 `WS=0` arms at four windows** the inferred half equals the printed half, floored — `912`/`800`/`456`. **`H24` is not a general failure of the detector; it is the one configuration that removes its landmark** |
| **6** | **`GATE 4b` CAN BE FIXED WITHOUT TOUCHING THE INSTRUMENT AT ALL, AND `316`'s SHEET DOES IT.** `314` §5.2 already parses the `VIEWPORT n64` line for `GATE 4c` and already refuses an arm without one — **it reads `w=`, throws `x=` away, and compares the play area against a TYPED `1825`.** `[x, x + 2w)` is in every log on every arm. **`RUN-SHEET-316` §1.1 is a run-sheet block, not a splice** |
| **7** | **THE DESKTOP BAR MAY ALREADY BE ANSWERED ON DISK.** `313` §2.2 read `V3`'s exit gate at `1600x1200`, where `a = 1.0000` and there is no pillarbox to lose: **five of six `PASS`, sign matching, `0.35` px at a predicted `-128.65`.** What it has never had is **`V4`, the negative arm** (`49`, `299` §4.3). `RUN-SHEET-316` §2 runs it |
| **8** | **►►►►►►►► X1's FIRST QUESTION IS A GRAPHICS BINDING AND NO DOCUMENT ANSWERS IT.** `[MEASURED, BRIDGE]` `xr_probe.cpp:118-124` enumerated **41** extensions and string-compared **two** — `XR_KHR_D3D12_enable` and `XR_FB_display_refresh_rate` — printing neither the list nor `XR_KHR_opengl_enable`. **The probe was written for the RECOMP line (RT64/D3D12). The NATIVE line is fast3d -> `gfx_opengl.c` on SDL2.** §3 |
| **9** | **AND THE BOARD ALREADY ORDERED THE FORK.** `PRIORITY-BOARD-313` §GROUP X: **"Precondition: `V3` passed"**, and **"NOT WORTH DOING IF: `V3` has not passed"**. `V3` has not passed. **`H24` before `X1` is not a preference; it is the board's own line** |
| **10** | **ONE CANDIDATE FILED AS A CANDIDATE.** The half the backend prints is a per-ARM constant; the half the tool infers is a per-PICTURE estimate — `311_mode2` reads a right bound of `2191` six times and `2192` once. **`H25`'s candidate, not `H25`. No fix, no proposal** |

---

## §1 — **THE SCAN, AND IT IS A READ OF PICTURES**

`[MEASURED, BRIDGE]` 2026-09-05. `stereo_disparity.py`'s own `read_bmp()` and `play_area()`,
**imported unmodified from the committed file at `ae95633`**, run over every `dlgrab` BMP in every
arm whose log carries a `VIEWPORT n64` line, and compared against that log's own rectangle.
**No `dx` is claimed here. No scorer ran. Nothing in this section is a verdict about stereo.**

| arm | window | grabs | tool half | log half | verdict |
|---|---|---:|---:|---:|---|
| `313_wide1` **`WS=1`** | `2560x1369` | 6 | **`1280`** | `912.667` | **`367.333` px out** |
| `314_wsON` **`WS=1`** | `2560x1369` | 5 | **`1280`** | `912.667` | **`367.333` px out** |
| `315_wsONb` **`WS=1`** | `2560x1369` | 7 | **`1280`** | `912.667` | **`367.333` px out** |
| `314_wsOFF` | `2560x1369` | 5 | `912` | `912.667` | agrees |
| `306_S3` / `307_S3b` / `307_S3c` / `310_S3d` | `2560x1369` | 30 | `912` | `912.667` | agrees |
| `311_sep64` / `311_mode2` / `312_mode2depth` | `2560x1369` | 18 | `912` | `912.667` | agrees |
| `313_w1600x1200` | `1600x1200` | 6 | `800` | `800.000` | agrees |
| `312_w1600` | `1600x1369` | 5 | `800` | `800.000` | agrees |
| `313_w1280x684` | `1280x684` | 7 | `456` | `456.000` | agrees |
| `312_w2560h800` | `2560x800` | 5 | `532` / `533` | `533.333` | **one pixel, and not stable within the arm** |

**►►►► THE THIRD `WS=1` ARM IS THE FINDING.** `313_wide1` ran on 2026-09-05 at `00:36:17Z`,
before `314` and `315` existed. `313` §2.3 point 2 wrote: *"The seam it used was `368` px from the
real one and its six `dx` … are about nothing."* **That is `H24`, measured and written down, two
sessions before it was filed** — disposed of as a property of that arm rather than of the
configuration. **`315` §5's sentence "every `WS=1` arm this project ever runs will void `4b`" is
the generalisation that was missing, and this session's scan is its third independent arm.**

**AND THE SHAPE OF THE MISS IS ONE `00-STATE` §6 ALREADY CARRIES:** a correct diagnosis recorded
in the instrument's vocabulary about ONE arm stops being ranked (`7b2`, and `297` §0 is the same
failure about the owner's own words).

---

## §2 — **`GATE 4b` DOES NOT NEED THE INSTRUMENT PATCHED, AND THAT IS `316`'s WHOLE ANSWER TO `H24`**

`NEXT-SESSION-PROMPT-316` said the cheapest honest thing is probably not a patch, and named the
line. **It is cheaper than that: the scorer already parses it.**

`[MEASURED, BRIDGE]` `RUN-SHEET-314` §5.2, as committed:

- it refuses an arm whose log has no `VIEWPORT n64` line — *"THE HALF CANNOT BE READ"*;
- it takes `backend_eye_w` from the FIRST such line's `w=` and uses it for every predicted px;
- and it then tests the play area against **`[Math]::Abs($paw - 1825) -gt 40`** — a **typed**
  number, correct at exactly one window.

**THE EYE RECTANGLE IS `x` AND `w`. THE PLAY AREA IS `[x, x + 2w)`.** `RUN-SHEET-316` §1.1 captures
`x` from the same regex, computes the expectation, prints a `seam-check` line with `delta_left` and
`delta_width` on **every** grab, and banners `GATE 4b FAILED` against the derived width rather than
a constant. **Nothing tracked changes. `stereo_disparity.py` is untouched at `24,413` bytes.**

**►►►► AND THE SCORER IS CONTROLLED BEFORE IT IS BELIEVED.** `314` §6a.1: a wrong INSTRUMENT patch
does not look like a fix, it looks like a measurement — and a scorer is an instrument.
`RUN-SHEET-316` §1.2 replays it against six numbers already published in `313` §2.2
(`-129, -95, -67, -50, -39, -34`, `PASS FAIL PASS PASS PASS PASS`). **`[PREDICTION] 6a`: any
deviation and the scorer is wrong, not the arm.**

**THE TOOL PATCH IS WRITTEN AND NOT SPLICED.** `RUN-SHEET-316` §3 carries the whole contract —
one optional `--play-area LEFT RIGHT`, the detector demoted to a printed cross-check and never
silenced, and four pre-registered predictions with a corpus that is already counted: byte-identical
unset on all 94 (`6h`), a no-op on the 71 `WS=0` grabs (`6i`), at most one pixel on
`312_w2560h800`'s five (`6j`), and movement permitted **only** on the 18 `WS=1` grabs (`6k`).
**`[OWNER, 2026-09-05]`: written down, not spliced.**

---

## §3 — ►►►►►►►► **X1, AND THE FIRST QUESTION IS NOT THE ONE PERFECT DARK ANSWERS** ◄◄◄◄◄◄◄◄

`RUN-SHEET-315` §3.1 maps Perfect Dark's `mainTick()` onto this tree seam by seam and finds four
of five already built. **That mapping is about the LOOP. It says nothing about whether the runtime
will accept this renderer, and this session found that nobody has asked.**

`[MEASURED, BRIDGE]`:

| | |
|---|---|
| the only OpenXR evidence this project owns | `09-openxr-probe`, 2026-08-22: SteamVR/OpenXR `2.16.7`, **41 extensions**, **`D3D12=yes`**, `refresh_rate_ext=yes` |
| what that probe actually tested | `xr_probe.cpp:118-124` — it enumerated all 41 and **string-compared exactly two names**, then printed a summary line. **The list was in the process's memory and was discarded** |
| which line that probe was written for | the **RECOMP** line. `xr_probe.cpp:41` `#define XR_USE_GRAPHICS_API_D3D12`; `09-openxr-probe` §"Consequences" item 3 is about **RT64** landing on the runtime's adapter |
| what the **NATIVE** line renders through | **fast3d -> `gfx_opengl.c` on SDL2.** `getv/build-windows/objects.txt` links `port_..._fast3d_gfx_opengl.o` |
| **is `XR_KHR_opengl_enable` among the 41** | **UNMEASURED. It is in no document in either tree** |

**SO X1's OPENING QUESTION IS: DOES THIS RUNTIME ACCEPT THE RENDERER THIS LINE ACTUALLY HAS?**
If yes, X1 is the loop-shape argument `117` feeds. If no, X1's first item is a GL-to-D3D interop
cost or a second backend, **and PD's `mainTick()` does not speak to that at all.**
**`RUN-SHEET-316` §4 is `X1-0`: a ~40-line enumerator, no instance-graphics binding of any kind,
no session, no swapchain, whose control is the 2026-08-22 report itself (`[PREDICTION] 7a`: 41
extensions with D3D12 among them).** Source tracked at `repo\xr\xr_ext_probe.cpp`.

### 3.1 — **AND TWO CONSTRAINTS ON *WHERE THE SESSION LIVES* THAT ARE MEASURED RATHER THAN ARGUED**

1. **►►►► ALL THREE FILES AN XR PRESENTATION SEAM MUST TOUCH ARE GITIGNORED.** `[MEASURED,
   BRIDGE]` `git check-ignore -v`: `getv/port/fast3d/gfx_pc.c` (`.gitignore:156`),
   `gfx_opengl.c` (`:154`), `gfx_sdl2.c` (`:161`). **An implementation written into any of them is
   not in the repository.**
2. **AND THE TREE ALREADY ANSWERS THAT, BY PRECEDENT AND IN ITS OWN WORDS.** `ge_depthclamp.h:18`:
   *"IT LIVES IN A TRACKED FILE ON PURPOSE. `gfx_pc.c` and `gfx_opengl.c` are gitignored"* — a
   **tracked** `ge_depthclamp.c`/`.h` called from the ignored backend by a one-line hook
   (`ge_depthclamp.h:25`: *"Call ONCE from `gfx_opengl_init()`, after the GL context exists"*).
   **`258` STAGE 6's `gevr_xr.c` goes beside it, and the hooks — and only the hooks — go in the
   ignored files.** That is not a design decision; it is the shape the tree already enforces.

**THIS IS EVIDENCE TO DECIDE X1 WITH, NOT A DECISION.** `117`'s own banner, and it applies here
exactly as it applies to PD's loop.

---

## §4 — **WHAT WAS DELIBERATELY NOT DONE**

- **NO FIX WAS FILED FOR `H24`.** §2's `GATE 4b` change is a run-sheet block that prints two
  numbers and compares them; the tracked instrument is byte-for-byte the committed one.
- **NO SPLICE.** `RUN-SHEET-316` §3 is a contract with pre-registered controls and an explicit
  line saying nothing in it runs.
- **NO ARM RAN AND NO GATE WAS SCORED.** `V3` is not read in this document, `4a` is still neither
  established nor falsified, and `[ARITHMETIC]` `a = 1.000000` at `WS=1` is still unchecked.
- **`H25` WAS NOT FILED.** The one-pixel bound wobble and the `hi = min(search, w - (Ra + px1) - 1)`
  overrun are both written down in `RUN-SHEET-316` §3.3 as candidates. **`314` §2.2: check that the
  quantity a refusal refuses on ORDERS the error it is meant to catch, on grabs you already have.
  That has not been done for either.**
- **THE RECOMP TREE WAS NOT TOUCHED**, including `xr_probe.cpp:32-33`'s stale build path
  (`lib\openxr\native\x64\release\lib\...` does not exist; the real one is `lib\openxr\lib\`).
  **Recorded, not fixed.**

---

## §5 — WHAT NEEDS A PERSON

- **`RUN-SHEET-316` §1** — offline, no run. **`6a` is the gate on the scorer itself.**
- **`RUN-SHEET-316` §2** — two runs at `1600x1200`, one sitting, **only after §1 passes.**
  `[DISPOSAL] 6g` — *it passes at `1600x1200`, not at the mandated `2560x1369`* — **gets written
  down whatever the numbers say.**
- **`RUN-SHEET-316` §4, `X1-0`** — one compile, one run, SteamVR active, headset need not be worn.
- **`X1` ITSELF** — still `HIGH`, still a fresh session's opening question, and still gated on
  `V3` by `PRIORITY-BOARD-313` §GROUP X's own precondition.
- **`RUN-SHEET-316` §3** — a contract. **It is not a task and it must not be spliced because it
  looks obvious.** `313` §5 is why an obvious-looking route gets pre-registered before it is
  believed.
- **`--max-depth-drift`'s default** — `0.15`, deferred to the next tool commit.
- **`U-27`** — not owed, **must not be guessed from a grep.**
- **`E3` (FC3/FC4) is CLOSED.**

**`169` NEXT ID = `U-28`. NEXT INSTRUMENT HOLE = `H25`.**
