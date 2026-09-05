# `320` -- **THE HALVING IS COUNTED ONCE, AND THE ARM WAS ALREADY ON DISK**

> **OFFLINE ASSISTANT. NOTHING BUILT, RUN, STAGED, BRANCHED, MERGED OR TAGGED BY THE ASSISTANT.**
> **NO GAME RUN AND NO COMPILE OF THE PRODUCT THIS SESSION.** Two pastes by the owner on the main
> PC: one `-fsyntax-only` gate and one file-reading arithmetic block. Binary UNTOUCHED, no
> gitignored file edited. `319`'s two commits are in at `328a9d3` and `3f6fd86`.
> **Wrong filed fixes: FIVE.**

---

## section 0 -- WHAT THIS SESSION ESTABLISHED, IN ONE TABLE

| | |
|---|---|
| **1** | **`[PREDICTION] X1-0c` LANDS AND THE LAST GAP IN `319` IS PAID.** `gcc exit 0`, no diagnostics, `-Wall -Wextra`, on the INERT shape the game build actually takes. `[REPORTED, OWNER PASTE]` and it can never be `[MEASURED]` -- `-fsyntax-only` writes no artefact. section 1 |
| **2** | **THE ARM `NEXT-SESSION-PROMPT-320` RANKED AS THIS SESSION'S CHEAPER TRACK NEEDED NO RUN AT ALL: ITS INPUT HAD BEEN ON DISK SINCE `314`.** `disp_314_wsOFF.txt`, 5 grabs, `GATE 4b` quiet, widescreen OFF. **`306` section 0 pays for the second time in three sessions.** section 2 |
| **3** | **`[PREDICTION] X1b-1` LANDS. `[PREDICTION] X1b-2` IS FALSIFIED.** `[MEASURED, BRIDGE]` median `k = 0.6978` against `a = 0.713021`: **`R = 0.9786`**, where `X1b-2` needed `2.0`. **The halving is counted ONCE.** section 3 |
| **4** | **SO `319` section 6's CANDIDATE SURVIVES ITS ONLY STATED OBJECTION.** `geStereoEyeAspect()` does not double-count; `gfx_adjust_x_for_aspect_ratio()` divides by the WINDOW while the 3D content lands in a viewport the window is not. section 3 |
| **5** | **THIRD INDEPENDENT ARRIVAL AT THE SAME NUMBER.** `312`: `0.987`. `313`'s control: `0.987`. This arm, stereo ON with the eye loop running: `0.9786`. **Different sessions, different grabs, one number to within `0.9%`.** |
| **6** | **THE DEPTH-DRIFT REFUSAL IS NOT LOAD-BEARING HERE** and was checked before it was leaned on (`314` section 2.2's rule): median over all five `0.6968`, over the four kept `0.6978`. **A difference of `0.001` against a fork whose arms are a factor of two apart.** section 4 |
| **7** | **NOTHING IS PATCHED AND NOTHING IS FILED.** `U-28` reserved, not filed, on the owner's instruction. `H19` open and unpatched. SHAPE A / SHAPE B still deferred. **The count of wrong filed fixes stays at FIVE.** |

---

## section 1 -- **`X1-0c`, AND WHY IT WENT INTO A DOC THE SAME MINUTE**

`[REPORTED, OWNER PASTE]` 2026-09-05:

    gcc present   True   (C:\msys64\mingw64\bin\gcc.exe)
    gevr_xr.c     True
    gevr_xr.h     True
    gcc exit 0   (0 means the INERT shape compiles clean and the game build is unharmed)

**Exit `0` AND no diagnostic line under `-Wall -Wextra`**, so the `#else` shape is clean and
warning-free. `319`'s commits had already landed, so this was owed retroactively -- exactly as
`NEXT-SESSION-PROMPT-320` allowed for.

**IT WAS WRITTEN TO `RUN-SHEET-319` section 1 AND `00-STATE` BEFORE ANYTHING ELSE WAS DONE, AND
THAT IS THE POINT.** `-fsyntax-only` leaves no artefact. A gate whose only record is a chat log
does not exist on the disk, and the next session applying the disk rule would read *"STILL OWED"*
in three places and pay it twice. **`318`'s lesson runs in this direction too: a claim that work
is DONE is also a claim about the filesystem, and the assistant is the one who has to put it
there.** `319`'s "still owed" bullets were kept verbatim and superseded in place (rule `2`).

---

## section 2 -- **THE ARM COST NO RUN, AND FINDING THAT OUT COST ONE `ls`**

**`NEXT-SESSION-PROMPT-320` described track A as *"on grabs already held"* -- which is true, and
understates it. The SCORING was already held too.**

`[MEASURED, BRIDGE]` `disp_314_wsOFF.txt`, `2026-09-04T22:31:03` to `22:31:20`, 83 lines, five
scored grabs against `run_314_wsOFF.log`. Checked against what the fork actually requires:

| requirement | why it is a requirement | reading |
|---|---|---|
| `2560x1369` | the geometry the fork is stated at | all five grabs |
| stereo ON | no disparity to measure otherwise | `[getv][stereo] ON`, one framebuffer, one DL, one swap |
| **widescreen OFF** | with it ON, `ge_effective_native_width()` makes `gfx_adjust_x_for_aspect_ratio()` the IDENTITY and there is no denominator left to test | `tanw=1.368534`, the 4:3 frustum |
| **`GATE 4b` quiet** | `H24` stretches the 2D layer to the window edge under widescreen, so the seam stops being the seam | **`0` fires**; tool read `play area x=[367..2192) width=1825`, backend printed `1825.334` |
| contrast | `307` section 2's `0.20` bar | `0.763 / 0.663 / 0.588 / 0.550 / 0.394` |

**AND THE THREE ARMS THAT LOOK LIKE CANDIDATES ARE ALL DISQUALIFIED BY THE SAME FACT:** `wide1`,
`wsON` and `wsONb` are widescreen ON. `wsON` fires `GATE 4b` five times out of five. **`H24` is
still blinding every `WS=1` arm, exactly as `315` and `317` said, and `[PREDICTION] 4a` is still
neither established nor falsified.** `wsOFF` is the only clean stereo arm at this geometry the
project owns, and it is four usable grabs after the drift refusal. **That is thin, and it is said
here rather than left for a later session to discover.**

---

## section 3 -- **THE MEASUREMENT, AND THE THREE RECTANGLES IT CHOOSES BETWEEN**

`[MEASURED, BRIDGE]` `gfx_pc.c:2362-2369` is one expression. With widescreen OFF the numerator is
exactly `4/3` (`gfx_pc.c:425-427`), so `a = (4/3) / (aspect of gfx_current_dimensions)` --
**and `gfx_current_dimensions` is the SDL WINDOW, one write site, `gfx_pc.c:6062`** (`319` `F1`).
The 3D content lands in `rdp.viewport` (`:3977-3980`), which `geStereoEyeViewport()` has halved.
**Three rectangles, and they are exactly a factor of two apart.**

`312`/`313` established that measured disparity is the game's own predicted disparity times `a`,
so `k = (measured dx) / (PREDICTED px)` reads the `a` the shipped code applied, and `R = k / a`
is `1.0` for whichever rectangle is the truth.

`[MEASURED, BRIDGE]`, and every value below was pre-registered in `RUN-SHEET-320` section 4
before the owner pasted it, to the digit:

    frame 2502   dx  -116.0   PREDICTED   -202.71   k 0.5722   depth-drift  28.3 pct
    frame 2680   dx   -64.0   PREDICTED    -97.44   k 0.6568   depth-drift   8.1 pct
    frame 2901   dx   -52.0   PREDICTED    -74.63   k 0.6968   depth-drift   2.0 pct
    frame 3129   dx   -46.0   PREDICTED    -65.83   k 0.6988   depth-drift   0.9 pct
    frame 3346   dx   -41.0   PREDICTED    -56.61   k 0.7243   depth-drift   3.6 pct

    median k   all 5 grabs                0.6968
    median k   depth-drift 15 pct or less   0.6978   (n=4, refused 1)

    a WINDOW        2560.000 x 1369   0.713021    R = 0.9786
    a PLAY AREA     1825.334 x 1369   1.000000    R = 0.6978
    a EYE VIEWPORT   912.667 x 1369   1.999999    R = 0.3489

**`R = 0.9786` AGAINST THE WINDOW MODEL. `[PREDICTION] X1b-1` LANDS** (tolerance `0.15`, actual
`0.021`) **AND `[PREDICTION] X1b-2` IS FALSIFIED, NOT NARROWLY:** it needed `2.0` and the
eye-viewport model it implies reads `0.3489`. **There is no reading of this arm in which the
halving is counted twice.**

**SO THE OBJECTION IS DEAD AND THE CANDIDATE IS NOT.** `stereo.h:89-95` says it in terms --
*"`aspect` is ALREADY THIS EYE'S aspect -- lv.c halved it once, through set_cur_player_aspect(),
so this builder halves NOTHING"* -- and the measurement agrees: the game side halves once into
the projection, Fast3D squeezes once by the window, and nothing is counted twice. **What remains
is `319` section 6's actual complaint: the squeeze uses a rectangle the content does not land in.**

---

## section 4 -- **WHAT THIS DOES NOT ESTABLISH**

- **IT DOES NOT ESTABLISH `a = 1.060225` IN THE HEADSET.** That is an inference about a path that
  does not exist. `[DISPOSAL] 9a` stands, `gfx_current_dimensions` is still the SDL window, and
  `318`'s numbers are still what they were. **This arm RANKS `H19`; it does not fix it and it does
  not measure VR.**
- **IT IS A DESKTOP WINDOW.** `318`'s correction stands -- `2560x1369` is `GETV_WINDOW`.
- **IT SAYS NOTHING ABOUT HOW ANYTHING LOOKS.** No grab was ranked. `4e` still belongs to the
  owner in the headset.
- **IT IS FOUR GRABS ON ONE SIGHTLINE FROM ONE RUN.** What carries it is that `312` and `313`
  reached the same number by other routes at other geometries -- not this arm's own weight.
- **`--max-depth-drift`'s DEFAULT IS STILL DEFERRED AND THIS ARM DOES NOT REOPEN IT.** The
  refusal was checked before it was relied on (`314` section 2.2) and it moves the median by
  `0.001`. **It orders the error -- `28.3% -> 0.572` is the furthest grab from the pack and the
  two lowest-drift grabs agree to `0.002` -- but the conclusion does not need it.**
- **`U-28` IS NOT FILED**, on the owner's explicit instruction and `301` section 0. **`H19` IS NOT
  PATCHED.** SHAPE A / SHAPE B stays exactly where `RUN-SHEET-314` section 1 left it.

---

## section 5 -- WHAT NEEDS A PERSON

- **`X2` -- SLICE 2, THE SWAPCHAIN. `HIGH`, AND A FRESH SESSION'S** (`00-STATE` section 7c).
  `xrEnumerateSwapchainFormats` -> `xrCreateSwapchain` -> the session-state event pump ->
  `xrBeginSession`. Constraints unchanged: XR state and rects in `gevr_xr.c`, the
  `glBindFramebuffer` beside `pp_fbo` in `gfx_opengl.c`, ONE display list and ONE `gfx_run`.
- **THIS SESSION'S DOCS COMMIT** -- `RUN-SHEET-320` has no commit section because there is nothing
  but docs to commit. Path list in `NEXT-SESSION-PROMPT-321`. **The 57-file username scrub is
  still nobody's.**
- **VENDORING THE OpenXR HEADERS** before the GAME build ever links `gevr_xr` -- the smoke includes
  from `GoldenEye64Recomp\lib\openxr\include`, the other line's path, `00-STATE` section 6 trap 2.
- **SHAPE A / SHAPE B** -- now ranked rather than guessed, still deferred, still `HIGH`.
- **`H25`**, **`XR_EXT_view_configuration_views_change`**, **`RUN-SHEET-317` section 2**,
  **`RUN-SHEET-316` section 3**, **`[PREDICTION] 4a`**, **`GX-0`**, **lane 3** -- all unchanged.
- **`U-27` must not be guessed from a grep. `E3` is CLOSED.**

**`169` NEXT ID = `U-28`. NEXT INSTRUMENT HOLE = `H25`.**
