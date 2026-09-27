# `314` — **THE TWO INSTRUMENT HOLES ARE CLOSED, `U-26` IS ANSWERED, AND SHAPE A IS NOT A CONFIG DEFAULT**

> **OFFLINE ASSISTANT. NOTHING BUILT, STAGED, BRANCHED, MERGED OR TAGGED BY THE ASSISTANT.**
> Two splices pasted by the owner on the main PC; everything else in this document is
> `[MEASURED, BRIDGE]` from the repo, the tool and the logs, read back rather than taken on a
> paste. **NO BUILD. NO RUN. THE BINARY IS UNTOUCHED.**

---

## §0 — WHAT THIS SESSION ESTABLISHED, IN ONE TABLE

| | |
|---|---|
| **1** | **`313` LEFT NOTHING OWED.** `[MEASURED, BRIDGE]` `GoldenEyeVR` HEAD `afaba05`, `goldeneye-native` HEAD `533fd3d`, `stereo_disparity.py` `18,722` bytes with `H18` in it. `RUN-SHEET-312` §5 had already landed. The username scrub is still **57** files and still nobody's |
| **2** | **►►►► `RUN-SHEET-314` §2 IS WORN. BOTH INSTRUMENT HOLES ARE SPLICED, OFFLINE, NO BUILD.** `stereo_disparity.py` `18,722 -> 22,192 -> 24,413` bytes, `CRLF=0`, zero control characters, `83 insertions(+) / 3 deletions(-)` on ONE path, **four `selftest` lines and all four `PASS`** |
| **3** | **►►►►►►►► THE CONTROL: 31 REAL GRABS ACROSS FIVE ARMS, SPLICED vs `git show HEAD:`, IDENTICAL ON ALL 31** — `eye half`, `dx`, `mad_best`, `contrast`, exit code. **Nothing this project has measured moves.** §1.2 |
| **4** | **►►►►►►►► `H23` DOES MORE THAN REFUSE: IT RECOVERS ARM 3 AT THE SHEET'S OWN `--search 500`.** `[MEASURED]` all seven `1280x684` grabs now read `-66, -47, -39, -31, -24, -22, -20` — **exactly the `--search 200` re-score** — against the committed tool's `-456 / mad 0.000 / PEGGED` on all seven. `3i` no longer depends on a hand-chosen `--search`. §1.3 |
| **5** | **►►►► AND TWO CORRECTIONS, BOTH THE ASSISTANT'S OWN, BOTH MADE THE SAME DAY THEY WERE WRITTEN.** The frame number `H22` was said to need a build **was already in the log**, four lines above the line the scorer greps; and once measured, **the frame gap does not order the error** — so §2's own stated fix would have thrown away the best grab on the arm. §2 |
| **6** | **►►►►►►►►►► `U-26` IS ANSWERED, AND `313` §5's CENSUS — NOT ONLY ITS INFERENCE — WAS WRONG.** `configWidescreen` is read in **`lv.c:868`**, in the GAME tree, through a local `extern` at `lv.c:855`, and it swaps the frustum's aspect to `gePortRealAspect()`. `[MEASURED]` the decomposition closes to **six decimals**. §3 |
| **7** | **►►►►►►►► SO SHAPE A IS NOT A CONFIG DEFAULT. `[ARITHMETIC]` IT NARROWS THE HORIZONTAL FRUSTUM BY `21.1%` AT `2560x1369`** — `tanw 1.368534 -> 1.079632` — **and that is a change to what the player SEES, not to how pixels are mapped.** It also drives `a` to **exactly `1.000000` at EVERY window**, not just at the mandated one. §4 |
| **8** | **ONE NEW UNKNOWN, `U-27`: WITH `GETV_WIDESCREEN=0` THE GAME'S FULL-VIEW ASPECT IS `2.370372`, NOT `4:3`** — constant across all four `WS=0` window shapes, and `[ARITHMETIC]` equal to `ASPECT_RATIO_SD * 16/9 = 64/27 = 2.370370` to six decimals. **`RUN-SHEET-314` §1's problem statement calls the pillarbox term *"correct ... for a mono 4:3 image"*. The image the frustum describes is not 4:3.** §5 |
| **9** | **NOTHING IS PATCHED IN THE PRODUCT. THE COUNT OF WRONG FILED FIXES STAYS AT FIVE.** Only the INSTRUMENT was changed, and only where `RUN-SHEET-314` §2 asked for it. **§1 is still the owner's and is still unpicked.** §6 |

---

## §1 — `RUN-SHEET-314` §2 IS WORN

### 1.1 — AS PASTED, READ BACK OFF THE BRIDGE

`[MEASURED, BRIDGE]` `getv/tools/stereo_disparity.py`: **`24,413` bytes, `CRLF=0`, ZERO control
characters.** `H18`, `H22` and `H23` all present by name. `--selftest` exits `0` and prints four
`PASS` lines; `A`, `B` and `C` are byte-identical to the committed tool's.
`git diff --stat` reads `1 file changed, 83 insertions(+), 3 deletions(-)` on ONE path —
`45 + 38` and `3`, exactly the two dry-runs summed. **No CRLF churn, no second file.**

### 1.2 — **THE CONTROL, AND IT IS `3h`'s SHAPE POINTED AT AN INSTRUMENT INSTEAD OF AN ARM**

`[MEASURED, BRIDGE]` the live tool against `git show HEAD:getv/tools/stereo_disparity.py`, on
**31 real grabs**: `grabs_313_w1600x1200` and `grabs_313_w1280x684` at `--search 200`,
`grabs_311_sep64`, `grabs_312_w2560h800` and `grabs_310_S3d` at `--search 500`.
**`eye half`, `dx`, `mad_best`, `contrast` and the exit code are IDENTICAL on all 31.**
A sound corpus does not care about a bound that was never binding.

### 1.3 — **`H23` RECOVERS THE ARM, IT DOES NOT ONLY REFUSE IT**

`[MEASURED, BRIDGE]` all seven `grabs_313_w1280x684` BMPs at the sheet's own `--search 500`:

| grab | committed tool | **live tool** | live tool at `--search 200` |
|---|---|---|---|
| all seven | `dx -456`, `mad_best 0.000`, `PEGGED` | **`-66, -47, -39, -31, -24, -22, -20`**, `mad_best 1.218`-`6.159`, no peg | **the same seven** |

**Every one equals its own `--search 200` re-score.** `313` §3.2 needed a hand-chosen `--search`
to recover `3i`; it no longer does.

---

## §2 — ►►►► **TWO CORRECTIONS, BOTH THE ASSISTANT'S OWN, BOTH FROM THIS SESSION** ◄◄◄◄

### 2.1 — **"THE FRAME NUMBER NEEDS A BUILD" IS FALSE. IT WAS IN THE LOG ALL ALONG.**

`[MEASURED, BRIDGE]` `stereo.c:499-500` prints a HEADER four lines above the line the scorer
greps: `[getv][stereo] ---- PREDICTION frame=2520 mode=1 ----`. **It carries `frame=`, and
`[getv][dlgrab] frame N ` carries `frame` too. The scorer greps `PREDICTION: disparity =` and
never looked up four lines.**

**AND THE TWO COUNTERS ARE THE SAME CLOCK, MEASURED.** Across **11 logs and 64 grabs** spanning
`310`, `311`, `312` and `313`: every header `frame=` is a multiple of `60` (`ge_st_probe`),
**every grab's gap to the last header before it lies in `[0, 58]`, not one of the 64 is negative,
and one is exactly `0`** — which pins any constant offset between the counters at zero.

**THE RULE, AND IT IS `313` §5 ONE STEP SIDEWAYS: A CENSUS THAT STOPS AT THE LINE YOU GREPPED
ANSWERS ABOUT THAT LINE, NOT ABOUT THE BLOCK IT SITS IN.** `313` was caught by a symbol whose
effect left the file; this was caught by a field four lines up in the same `printf` block.
**The defence in both cases is one `grep -B4`.**

### 2.2 — ►►►► **AND THE PAYOFF FALSIFIES `RUN-SHEET-314` §2's OWN STATED FIX.**

§2 asks for *"a refusal in the tool when they are more than a few frames apart"*. `[MEASURED]`,
13 grabs, both `313` arms:

| arm | frame | **frame gap** | **D drift** | ratio | verdict |
|---|---:|---:|---:|---:|---|
| `1600x1200` | `2578` | **`+58`** | `0.1%` | **`1.0028`** | `PASS` — **the arm's most accurate grab, at its LARGEST frame gap** |
| `1600x1200` | `2739` | `+39` | **`16.2%`** | **`0.8922`** | **`FAIL`** — **its only failure, at its largest drift** |
| `1600x1200` | `2882` | **`+2`** | `8.4%` | `1.0032` | `PASS` |
| `1600x1200` | `3028` | `+28` | `11.2%` | `0.9538` | `PASS` |
| `1600x1200` | `3214` | `+34` | `3.3%` | `0.9827` | `PASS` |
| `1600x1200` | `3410` | `+50` | `4.1%` | `0.9921` | `PASS` |

**A FRAME-GAP REFUSAL WOULD HAVE THROWN AWAY THE BEST GRAB AND KEPT THE ONLY FAILURE.** The frame
gap measures the PROBE'S CADENCE, not how far the world moved. **The depth drift is the term that
carries it, and §2a's splice chose it on an argument (`1/D` proportionality) rather than on this
evidence — it was right, and it was luckier than the assistant knew.** `312` §2.4's shape, twice.

**AND THE DEFAULT `--max-depth-drift 0.05` IS TOO TIGHT ON THIS EVIDENCE:** it fires on `16.2%`,
`11.2%` and `8.4%`, and two of those three PASSED — one at `1.0032`, the most accurate grab on the
arm. Every drift from `0.1%` to `11.2%` passed; the single failure is at `16.2%`. **The tightest
default the evidence supports is `0.15`.** `[OWNER, 2026-09-05]` **this rides with the next tool
commit and is NOT changed here** — the code already says out loud that the bound is chosen and not
measured, and the `pairing` line prints the drift and its px cost on every grab regardless.

---

## §3 — ►►►►►►►► **`U-26` IS ANSWERED, AND IT IS TWO LINES OF GAME CODE OLDER THAN `292b`** ◄◄◄◄◄◄◄◄

`313` §5 filed *"where the aspect arm 1 sees actually comes from"* as `U-26`, owed by nobody, on
the strength of a census that said `configWidescreen` *"appears only in `gfx_pc.c`,
`port_support.c` and the launcher"*.

**`[MEASURED, BRIDGE]` THE REAL LIST IS SIX FILES AND ONE OF THEM IS IN THE GAME TREE:**
`configfile.h`, `gfx_pc.c`, `ge_config.c`, `ge_launcher.cpp`, `port_support.c`, **`lv.c`**.

```c
/* lv.c:855-856 -- a LOCAL EXTERN, the pattern 00-STATE §6 already carries twice */
extern unsigned int configWidescreen;
extern float gePortRealAspect(void);
...
/* lv.c:868-870 */
f32 ge_a = ge_af;
if (configWidescreen && pcount == 1) {
    ge_a = gePortRealAspect();
}
```

`gePortRealAspect()` (`ge_display_api.c:15`) returns
`gfx_output_dimensions.width / gfx_output_dimensions.height`, falling back to `1.3333334f`.
**`[MEASURED, BRIDGE]` `git log -L` shows both `extern` lines as CONTEXT in the `292b` diff — they
predate `292b` and were present when `313` ran.** The census simply missed the file.

**►►►► AND THE DECOMPOSITION CLOSES TO SIX DECIMALS, FROM THE LOGS' OWN PRINTED TANGENTS.**
`geStereoBuildFrustumF()`: `tR = tU * aspect_eye`, `tanw = 2 * tU * aspect_eye`, and
`geStereoEyeAspect()` halves once (`*out = full * 0.5f`).

| arm | `[MEASURED]` `tU` | `[MEASURED]` `tR` | `aspect_eye = tR/tU` | full `= x2` |
|---|---:|---:|---:|---:|
| **every `WS=0` arm ever run** (four window shapes) | `0.577350` | `0.684267` | `1.185186` | **`2.370372`** |
| **`WS=1`, arm 1** | `0.577350` | `0.539816` | **`0.934989`** | **`1.869978`** |

**`tU` IS `0.577350` ON EVERY ARM, WIDESCREEN ON AND OFF — `tan(30 deg)`, `fovy = 60`. THE WHOLE
`tanw` MOVE IS THE ASPECT AND NOTHING ELSE.** And `[ARITHMETIC]` `gePortRealAspect()` at
`2560x1369` is `2560/1369 = 1.869978`, whose half is **`0.934989` — the measured `aspect_eye`, to
six decimals.** `U-26` is not a mystery and it is not downstream of `ge_scale()`; it is
`lv.c:869`.

---

## §4 — ►►►►►►►► **WHAT THAT DOES TO SHAPE A, AND IT IS NOT WHAT §1 ASSUMED** ◄◄◄◄◄◄◄◄

**THE GOOD NEWS FIRST, AND IT IS BETTER THAN §1 CLAIMED.** `[ARITHMETIC]` with
`configWidescreen=1`, `ge_effective_native_width() = 240 * (W/H)`, so
`a = (ge_effective_native_width()/gfx_native_height) / (W/H) = 1.000000` **identically, at EVERY
window**:

| window | `a` at `WS=0` | **`a` at `WS=1`** |
|---|---:|---:|
| `2560x1369` | `0.7130` | **`1.000000`** |
| `1600x1200` | `1.0000` | **`1.000000`** |
| `1280x684` | `0.7125` | **`1.000000`** |
| `2560x800` | `0.4167` | **`1.000000`** |
| `1600x1369` | `1.1408` | **`1.000000`** |

**The measured ratio is `a` — that is what the five-window table means. So SHAPE A predicts
`ratio = 1.000` at ANY geometry, not only at the mandated one. It is a stronger fix than SHAPE B,
which corrects the PREDICTION at whatever window it is cut against.**

**►►►►►►►► AND THE COST, WHICH §1 DID NOT STATE BECAUSE `U-26` WAS OPEN: SHAPE A NARROWS THE
HORIZONTAL FRUSTUM BY `21.1%`.** `[MEASURED]` `tanw 1.368534 -> 1.079632`, ratio `0.788897`.
**The player sees `21.1%` LESS OF THE WORLD HORIZONTALLY, undistorted, instead of more of it,
squeezed.** That is not a rendering detail and it is not the pillarbox margin `313` §0.1 already
described — it is the field of view. **`00-STATE` §7b2: the owner's eyes rank this, not this
document.**

**AND IT IS SEPARATE FROM THE THING `313` §0.1 WARNED ABOUT.** That was cosmetic — the pair goes
left-aligned with a `734.67` px black band, and the 2D layer stretches to the window edge under
`gfx_pc.c:4193`. **This is the projection. Two different costs, and only one of them was on the
table when §1 was written.**

---

## §5 — **ONE NEW UNKNOWN, AND IT SITS UNDER §1's PROBLEM STATEMENT: `U-27`**

`RUN-SHEET-314` §1 opens: *"`gfx_adjust_x_for_aspect_ratio()` is **correct** — it is retail
pillarbox behaviour for a mono 4:3 image in a wide window."*

**`[MEASURED]` THE FRUSTUM IS NOT 4:3.** With `GETV_WIDESCREEN=0` the game's full-view aspect is
**`2.370372`**, constant across all four `WS=0` window shapes ever run, and `[ARITHMETIC]` that is
`ASPECT_RATIO_SD * 16/9 = 64/27 = 2.370370` to six decimals. **Where the `16/9` comes from has
never been read, and it is not `configWidescreen` — the knob was OFF on all four arms.**

**`U-27`: WHAT SETS `g_CurrentPlayer->aspect` TO `64/27` ON A `GETV_WIDESCREEN=0` ARM.**
**IT IS NOT OWED BY ANY SHEET AND IT MUST NOT BE GUESSED FROM A GREP** (§3 is why). It matters
because **if the pillarbox term is correcting a frame that was never 4:3, then "the term is
correct and the predictor does not know it" is not the whole statement of the defect** — and §1
is a choice between two fixes to that statement. **`169` NEXT ID = `U-28`.**

---

## §6 — ►►►►►►►► **SO WHAT §1 NOW LOOKS LIKE. IT IS STILL NOT PICKED HERE.** ◄◄◄◄◄◄◄◄

| | **SHAPE A — ship `GETV_WIDESCREEN=1`** | **SHAPE B — teach `geStereoPredict()` the term** |
|---|---|---|
| **cost to build** | a config default | a source change in `stereo.c` + a rebuild, **and it changes the INSTRUMENT** |
| **what it fixes** | `[ARITHMETIC]` `a = 1.000000` at **every** window | the prediction at the window it is cut against; `239` says a term validated at one geometry is not a setting |
| **`313`'s blocker** | **GONE. `U-26` is answered (§3): the frustum move is `lv.c:869`, `gePortRealAspect()`, and it is exact to six decimals** | — |
| **the new blocker** | **`[ARITHMETIC]` it costs `21.1%` of horizontal FOV at `2560x1369`, plus `313` §0.1's left-alignment and `734.67` px black band. Both are things the owner SEES** | **the honest objection stands: it teaches the predictor to expect the squeeze rather than removing it** |
| **has it ever been measured?** | **NO. Arm 1 was VOID twice and no arm has replaced it** | **the term itself has, five windows, `0.915`-`0.992`** |
| **falsifier** | an arm at `2560x1369`, `WS=1`, ratio scored against a half READ off its own `VIEWPORT n64` line, **and `play area` checked to read `1825` and not `2560`** (`313` §0.1) | the `+/-5 px` gate at `2560x1369`, four or five grabs, `D` `200`-`550` |

**►►►► THE ONE THING THIS SESSION WOULD PRE-REGISTER BEFORE EITHER SHAPE IS BUILT, AND IT IS FREE:**
the SHAPE A arm above is `LOW` — one run, no build — **and `[PREDICTION] 4a` is now sharp enough to
be worth writing down in advance: it must read `tanR-tanL = 1.079632`, `backend_eye_w = 912.667`,
`play area x=[0..1825) width=1825`, `eye half 912`, and a median ratio of `1.000` +/- the
instrument's own `~2%`.** **If the ratio comes back at `0.7`, the play-area detection is confounded
again and the arm is VOID, not a falsification** — same disposal as `3a`, written down before it
runs.

**AND THE ORDER `301` §0 IMPLIES: THE ARM IS CHEAPER THAN THE ARGUMENT IT WOULD SETTLE.** Five
wrong filed fixes, four of them convincing. **SHAPE A is currently the only one of the two whose
central claim has never been measured, and it is one run from being measured.**

---

---
