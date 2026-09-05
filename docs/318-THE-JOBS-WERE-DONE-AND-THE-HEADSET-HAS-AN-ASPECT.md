# `318` — **THE THREE JOBS WERE ALREADY DONE ON DISK, AND THE HEADSET HAS AN ASPECT AT LAST**

> **OFFLINE ASSISTANT. NOTHING BUILT, RUN, STAGED, BRANCHED, MERGED OR TAGGED BY THE ASSISTANT.**
> One compile and one run by the owner on the main PC; everything else read off the bridge.
> Binary UNTOUCHED — nothing this session goes near `goldeneye.exe`.
> `317`'s carry-over commit is in at **`b253743`**. **Wrong filed fixes: FIVE.**

---

## §0 — WHAT THIS SESSION ESTABLISHED, IN ONE TABLE

| | |
|---|---|
| **1** | **►►►►►►►► `NEXT-SESSION-PROMPT-318` RANKED THREE JOBS AS OWED AND TWO WERE ALREADY DONE.** `[MEASURED, BRIDGE]` all four `disp_317_*` scorings stamped `23:51`-`23:52` EDT, `xr_ext_probe_report.txt` `23:57:04`, against the prompt's own `23:59:32`. **`306` §0 generalises: a claim that work is owed is a claim about the DISK, not only about `git`** |
| **2** | **`[PREDICTION] 8a` LANDS AND THE GATE FIRES.** `SEAM-CHECK RAN ON 7 OF 7 GRABS; GATE 4b FIRED 7 TIMES` on `wsONb`, seven `delta_left=0 delta_width=734.666`, `tanw=1.079632`, no `4c` failure. **`317` §3's retraction is discharged** |
| **3** | **`8b` LANDS.** `6/6`, `6/6`, `7/7` on the `WS=0` arms, **`GATE 4b FIRED 0 TIMES`**, `delta_width` `0` / `0` / **`-1` on six of seven** — `317` §2.1's one-pixel wobble under a tolerance of 40 |
| **4** | **`8c` LANDS.** Every `dx` and every `VERDICT` **identical** to `316`'s scorings across all four arms (14 / 12 / 12 / 14 lines diffed). The fix touched only a branch that never executed. **So `317` §1 and §2's numbers are readable** |
| **5** | **`7a` LANDS AND `7b` IS YES.** SteamVR/OpenXR `v2.16.7`, **41 extensions**, `XR_KHR_D3D12_enable v11`, **`XR_KHR_opengl_enable v12` PRESENT.** The native line is GL and can bind directly |
| **6** | **►►►►►►►► `X1-0b`: THE RUNTIME'S RECOMMENDED RECT IS `4140 x 3292` PER EYE**, max `8192 x 8192`, `samples rec 1 max 1`, two views, **rects identical**. `9a` and `9b` both land |
| **7** | **►►►►►►►► `[ARITHMETIC]` PER-EYE `a = 1.060225`; TWO-EYES-ONE-WINDOW `a = 0.530113`.** Against `1.0000` at `1600x1200` and `0.7130` at the `2560x1369` desktop window. **`H19`'s residual in the headset is `6.0%` on a per-eye target and `47%` on the other shape** |
| **8** | **AND IT IS A RANKING INPUT, NOT A RESULT ABOUT THE SHIPPED PATH.** **Which `W/H` `gfx_pc.c:2362` reads under an XR path is a DESIGN question nobody has answered** — today it reads the SDL window. There is no shipped VR path to measure |
| **9** | **`a` IS NOT EVEN A CONSTANT.** `XR_EXT_view_configuration_views_change` is advertised: the runtime may hand back a different rect mid-run. **Candidate hole, NOT filed** (`301` §0) |
| **10** | **ONE TRUNCATION, MINE.** A bridge-side scripted edit opened the tracked source before encoding it and left it **zero bytes**. Restored byte-identical from a copy taken first. **§3, and `00-STATE` §6 has it** |
| **11** | **LANE 1 IS CLOSED BY THE OWNER'S DECISION** (`7b2`, `00-STATE` §3, in their words), **not by a gate that cleared at `2560x1369` — it never did.** `[DISPOSAL] 6g` stands unsoftened |

---

## §1 — **THE JOBS WERE DONE BEFORE THE PROMPT THAT ASKED FOR THEM WAS WRITTEN**

`NEXT-SESSION-PROMPT-318`'s table ranked, as jobs `1`, `2` and `3`: run `Score-317` and
`[PREDICTION] 8a`; the three `WS=0` re-scores; and `X1-0`, *"still owed"*. **All three had run.**

`[MEASURED, BRIDGE]`, EDT, in order:

| artefact | stamp |
|---|---|
| `disp_317_gatefire_wsONb.txt` and the three re-scores | **`23:51:27` - `23:52:45`** |
| `RUN-SHEET-317.md`'s final edit (§3's mingw rewrite) and `xr_ext_probe.cpp` | **`23:55:06`** |
| `xr_ext_probe_report.txt` | **`23:57:04`** |
| `0f617bf`, `317`'s docs commit | **`23:57:31`** |
| `NEXT-SESSION-PROMPT-318.md`, saying all three were owed | **`23:59:32`** |
| `COMMIT-MESSAGE-2026-09-05e.txt`, saying *"X1-0 has still not produced a report"* | **`23:59:09`** |

**THE OUTPUTS ARE `Score-317`'s AND IT IS CHECKED, NOT ASSUMED.** Only that function prints
`SEAM-CHECK RAN ON n OF m GRABS; GATE 4b FIRED n TIMES`, and its `>>>> GATE 4b FAILED on frame ...`
banner appears in `disp_317_gatefire_wsONb.txt` **character for character** as `RUN-SHEET-317` §1
writes it. The header line's field order matches too.

- **`8a`.** `SEAM-CHECK RAN ON 7 OF 7 GRABS; GATE 4b FIRED 7 TIMES`. Seven `seam-check` lines,
  every one `tool play area x=0 width=2560   backend says x=0 width=1825.334   delta_left=0
  delta_width=734.666`. `tanw=1.079632`, no `GATE 4c FAILED`. **The gate can be failed. `317` §3
  is discharged.**
- **`8b`.** `replay_w1600x1200` `6 OF 6`, `v3_4x3` `6 OF 6`, `v4_4x3` `7 OF 7`; **`FIRED 0 TIMES`**
  on all three. `delta_left=0` throughout; `delta_width` `0` on both `1600x1200` arms; on
  `v4_4x3`, **`-1` on six grabs and `0` on the seventh** — `317` §2.1's measured one-pixel
  play-area bias, and at a tolerance of `40` it is correctly not a `4b` failure.
- **`8c`.** Every `dx` and `VERDICT` line diffed against `disp_316_*`: **identical**, 14 / 12 / 12
  / 14 lines. `wsONb` still `-420` (`CANNOT ANSWER`) then six `FAIL`; `1600x1200` still
  `-129, -95, -67, -50, -39, -34`; `v3_4x3` still `-119, -75, -65, -55, -48, -41`, six `PASS`;
  `v4_4x3` still seven at `-74`/`-75`.

**THE PROCESS FINDING, AND IT IS THE ONE WORTH KEEPING.** `306` §0 has been right eight sessions
running about `git`. **It is the same claim about the filesystem and nobody generalised it.** A
session that writes *"still owed"* about an artefact it can name has already told you the check:
`ls` the name. `317` ran the work, wrote the prompt twenty minutes later, and did not look.

---

## §2 — **`X1-0b`, AND THE HEADSET FINALLY HAS AN ASPECT**

**WHY IT EXISTS.** The owner stopped a badly framed question — *"is that the resolution bar for
the headset or just this arbitrary resolution here? of my monitor"* — and they were right.
`2560x1369` is `GETV_WINDOW`, a desktop window standing since `286`. **`H19`'s factor is
`a = (4/3) / (W/H)` of whatever is rendered into, and nobody had ever read `W` and `H` for the
headset.** `X1-0` enumerated extensions and stopped.

`[MEASURED]` `xr_ext_probe_report.txt`, 2026-09-05 `15:21:07`, SteamVR active, headset awake:

```
system           : SteamVR/OpenXR : aapvr  (vendor id 10462)
view configs     : 1 advertised  (2)   PRIMARY_STEREO is 2
views            : 2
  view 0  recommended 4140 x 3292   max 8192 x 8192   samples rec 1 max 1
  view 1  recommended 4140 x 3292   max 8192 x 8192   samples rec 1 max 1
  rects identical across views: yes
```

- **`[PREDICTION] 9a` LANDS.** 41 extensions, `D3D12` yes, `opengl_enable` yes — **unchanged
  across two runs eleven hours apart**, which is `7a` re-run as its own control inside the same
  process. Nothing below it was read until that line was checked.
- **`[PREDICTION] 9b` LANDS.** Two views, rects identical, so `a` is ONE number and not two.
- **THE VALUE OF `a` WAS NOT PREDICTED** (`301` §0) and is the answer:

| shape | pixels | aspect | `a = (4/3)/(W/H)` | `H19`'s residual |
|---|---|---|---|---|
| **per-eye target** | `4140 x 3292` | `1.257594` | **`1.060225`** | **`6.0%`** |
| **two eyes, one window** | `8280 x 3292` | `2.515188` | **`0.530113`** | **`47.0%`** |
| `1600x1200`, where the bar cleared | | `1.333333` | `1.000000` | `0%` |
| `2560x1369`, the desktop window | | `1.870000` | `0.713000` | `29%` |

**►►►►►►►► WHAT THIS DOES AND DOES NOT SAY, AND THE SECOND HALF IS THE IMPORTANT HALF.**

- **It is a ranking input for `X1` and it is not a decision.** If the eventual design renders each
  eye into its own target and `gfx_pc.c:2362` sees that target, `H19` costs `6.0%` in the headset
  rather than the `29%` it costs on the desktop window. **That changes how urgent SHAPE A / SHAPE B
  is. It does not choose between them.**
- **WHICH `W/H` THAT CODE READS UNDER AN XR PATH IS UNANSWERED.** Today it reads the SDL window.
  **`1.060225` is what `a` BECOMES IF the per-eye target is what that code sees** — an assumption
  about a path that does not exist yet. **`312` §2.2's trap is exactly this shape:** a chain that
  reads sound end to end while the term sits outside it. **Do not quote `1.060225` as a property
  of the shipped build. There is no shipped VR path.**
- **AND `a` IS NOT A CONSTANT.** `XR_EXT_view_configuration_views_change` is advertised: the
  runtime may return a different recommended rect while the app runs — a SteamVR resolution slider
  is enough. **A stereo prediction pinned to a rect read once at start-up can go stale silently.**
  That is a candidate for the next instrument hole and **it is NOT filed** — `H25` is still owed to
  `317` §2.1, and `301` §0 says a candidate is not a hole.
- **`samples rec 1 max 1`** — the runtime offers no MSAA on the swapchain. Recorded, not acted on.
- **`max 8192 x 8192`** against a recommendation of `4140 x 3292`: there is headroom, and the
  recommendation is what SteamVR's current settings ask for, not a panel spec.

---

## §3 — **THE TRUNCATION, AND IT IS MINE**

`[MEASURED, BRIDGE]` writing `X1-0b` into the tracked `repo\xr\xr_ext_probe.cpp`, my new comment
text carried a non-ASCII `►`. `open(p, 'w', encoding='ascii')` **truncates the file on open**; the
`UnicodeEncodeError` fired afterwards. A 145-line tracked source became **zero bytes** and
`git diff --stat` read `145 deletions`.

It was restored byte-identical from a copy taken before the write — `md5` match against the
pre-edit copy, `git --no-optional-locks status -- repo/xr` clean — and rewritten ASCII-only, with
the encode asserted on the bytes **before** the file was opened.

- **THIS IS `313` §5's FAMILY ONE LEVEL UP.** There a `\b` in a Python string put a literal `0x08`
  inside a Windows path in a tracked markdown file — the CONTENT was corrupted and a scan of the
  output would have caught it. **Here the file had no content to scan.**
- **`308` §1.1 BANS A POWERSHELL ROUND-TRIP ON A TRACKED SOURCE. IT DOES NOT COVER THIS**, because
  this is the bridge-side edit's own failure mode. **`00-STATE` §6 now carries both.**
- **THE RULE: BUILD THE STRING, ENCODE IT, ASSERT ON THE BYTES, AND ONLY THEN OPEN THE FILE — and
  copy the file first.** The copy is what made this a footnote instead of a session.
- **NOTHING WRONG WAS COMMITTED AND NO PRODUCT FILE WAS EVER AT RISK.** The count of wrong filed
  fixes stays at **FIVE**: this was not a fix, it was a write.

---

## §4 — **WHERE LANE 1 STANDS, AND WHAT `X1` OPENS WITH**

**LANE 1 IS CLOSED BY THE OWNER'S DECISION AND `00-STATE` §3 CARRIES IT IN THEIR WORDS** (`7b2`).
It is not closed by a gate clearing at `2560x1369`; that never happened and `[DISPOSAL] 6g` says so
unsoftened:

> **It passes at `1600x1200`, a `4:3` window where `a = 1.0000` by accident of the window.
> IT DOES NOT PASS AT THE MANDATED `2560x1369`. `H19` stays open, unpatched,
> `a = (4/3)/(W/H)`, and DOCUMENTED rather than hunted.**

**WHAT `X1` NOW OPENS WITH THAT IT DID NOT HAVE:**

- **THE BINDING.** `XR_KHR_opengl_enable v12`. The native line is fast3d -> `gfx_opengl.c` on
  SDL2 and can bind directly. **The GL-to-D3D interop cost is NOT `X1`'s first item.**
- **THE GEOMETRY.** `4140 x 3292` per eye, and the two values of `a` that follow from it.
- **AND THE QUESTION THAT REPLACES THEM:** does the XR path render per-eye targets that
  `gfx_pc.c:2362` sees, and does `H19` get patched before or after that is decided? **`HIGH`, and
  `00-STATE` §7c keeps it out of this session.**

---

## §5 — WHAT NEEDS A PERSON

- **`318`'s DOCS COMMIT.** `RUN-SHEET-318` §4, explicit path list. **The 57-file username scrub is
  still nobody's — leave it alone.**
- **`X1` — `HIGH`, a fresh session's opening question**, now with the binding and the geometry both
  measured.
- **THE `view_configuration_views_change` CANDIDATE** — a hole or a note? Not filed here.
- **`RUN-SHEET-317` §2 — the census as `GATE 6.1`'s instrument.** Still a PROPOSAL, still needs its
  own negative arm.
- **`H24` / `RUN-SHEET-316` §3** — still a contract, still unspliced.
- **`H25`** — still not filed; `317` §2.1's one-pixel bias is still its candidate.
- **`--max-depth-drift`'s default** — evidence on both sides. **Still deferred.**
- **`U-27`**, **`GX-0`**, **lane 3** — unchanged. **`E3` is CLOSED.**

**`169` NEXT ID = `U-28`. NEXT INSTRUMENT HOLE = `H25`.**
