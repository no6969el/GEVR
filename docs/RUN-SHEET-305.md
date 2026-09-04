# `RUN-SHEET-305` — RE-WEAR `305` UNDER `py`, BOUND ITS FALSIFIER, AND ONE SENTENCE ABOUT FC3/FC4

**WRITTEN OFFLINE 2026-09-03.** `RUN-SHEET-304` §1, §2, §3, §4, §5 and §5a are **ALL WORN** —
§3 and §4 were run at 22:17–22:18 UTC and never written down; `305` §2a is the account. **§2a of
`304` (dating the POLYGON with a run) is the only part of `304` still owed.**

**NOTHING HERE BUILDS.** §1, §2 and §4 need no compile and no game. §3 is a two-line source edit
and is the only thing in this sheet that would need one.

---

## §0 — WHAT `305` FOUND, IN ONE TABLE

| | |
|---|---|
| `dlgrab_eyecensus.py` compares DL call targets as a **SET** | so a pure REORDER reads `only in eye0 = 0` and passes |
| **4 of 256 dumps are permutations**, three of them the same 8-call rotation by 3 at span `[29..36]` | and two of those three are pre-`303` with clean provenance |
| **the reorder draws NOTHING** — `dlgrab_2928` and `dlgrab_2957` are **0 px, 0 blobs** | so it is not the polygon and not `4676`'s divergence |
| `C1_2336` and `V1_2732` are **order-identical** | the polygon is downstream of everything the dump records |
| `H13`'s constant SEVEN is the second eye's target clear | closed, benign, no code change |

---

## §1 — RE-WEAR EVERY `305` NUMBER UNDER THE MAIN PC's `py`. **`H7`. SECONDS.**

**NOTHING IN `305` IS QUOTABLE FORWARD UNTIL THIS PASSES.** Every figure in that document was
measured on the bridge's `python3 3.10.12`, which is not this machine's `py` — the exact gap
`H7` was opened for and `RUN-SHEET-300` §1 closed once already.

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\tools
py .\dlgrab_dlorder.py --selftest
```

**GATE §1a — the last line must read `7 checks, 0 failed`.** Check `B` is a pure reorder that a
set-based comparison scores clean; **if `B` passes on an implementation that uses `set()`, the
check is not doing its job and this file is worthless.**

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
py ..\tools\dlgrab_dlorder.py (Get-ChildItem .\grabs_303_C1\*.txt).FullName (Get-ChildItem .\grabs_303_V1\*.txt).FullName
```

**GATE §1b — exactly ONE frame must come back `PERMUTATION` and it must be `dlgrab_C1_4676`,
reading `same 46 targets, 8 positions differ, span [29..36]` and `CYCLIC ROTATION of 8 calls by
3`. The other thirteen must read `ORDER IDENTICAL`, `dlgrab_C1_2336` and `dlgrab_V1_2732`
INCLUDED.** A second permutation here means the bridge and the main PC disagree and `305` §1.5 is
withdrawn.

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
py ..\tools\dlgrab_dlorder.py (Get-ChildItem .\grabs_299_E1\dlgrab_2928.txt,.\grabs_299_E1\dlgrab_2957.txt).FullName
py ..\tools\stereo_eyediff.py (Get-ChildItem .\grabs_299_E1\dlgrab_2928.bmp,.\grabs_299_E1\dlgrab_2957.bmp).FullName
```

**GATE §1c — THIS IS THE FALSIFIER AND IT IS THE WHOLE OF `305` §1.4.** Both frames must come
back **`PERMUTATION`** from the first command and **`total 0 px   blobs 0`** from the second.
**A non-zero pixel count on either frame puts the reorder back on the board as a candidate cause,
and `305` §1.4 is retracted.** `279` §7: this is the instrument pointed at the frames it is
expected to be boring on, and the expectation is pre-registered here.

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
py ..\tools\dlgrab_eyecensus.py .\grabs_303_C1\dlgrab_C1_4676.txt --calls --arena
```

**GATE §1d — the `ARENA` block must read `MODEL_MTX(3) eye1 … fresh=3` and `MODEL_VTX(4) eye1 …
reused-from-eye0=17 fresh=0`, and the two `MOVEMEM` lines must share ONLY `0386` and `0388`
(`G_MV_L0` / `G_MV_L1`, the lights).** If `0380`, `0382` or `0384` match between the eyes, `305`
§1.1's null is wrong and the second eye is drawing with the first eye's view after all.

---

## §2 — BOUND §1.4's FALSIFIER ACROSS THE WHOLE CORPUS. **OFFLINE, ~2 MINUTES.**

**THE OPEN EDGE IN `305`:** the two frames that falsify the reorder are on the `299` binary in a
different scene from `4676`. *"The same reorder is harmless HERE"* is not *"a reorder is harmless
everywhere"*, and `305` §1.4 says so in its own bound. **This closes it, or it does not.**

**THE QUESTION, PRE-REGISTERED: is there ANY dump that `dlgrab_dlorder.py` calls `permuted` AND
`stereo_eyediff.py` calls a pixel hit?**

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
$dumps = Get-ChildItem .\grabs_*\*.txt | Select-Object -ExpandProperty FullName
py ..\tools\dlgrab_dlorder.py $dumps *> order_sweep_305.txt
Select-String -Path order_sweep_305.txt -Pattern 'PERMUTATION' -Context 1,0
Select-String -Path order_sweep_305.txt -Pattern '^================'
```

**GATE §2a — the sweep must read `equal=32  permuted=4  admission=52  refused=168`, totalling
256.** A different total means `grabs_*` has changed since `305` was written and the folder
inventory must be reconciled before anything else is read.

Then the pixels for exactly the frames the sweep named:

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
py ..\tools\stereo_eyediff.py .\grabs_299_E1\dlgrab_2928.bmp .\grabs_299_E1\dlgrab_2957.bmp .\grabs_303_C1\dlgrab_C1_4676.bmp .\grabs_pre_298cull\dlgrab_7360.bmp
```

**GATE §2b — THE READING, AND BOTH OUTCOMES ARE WRITTEN DOWN BEFORE THE RUN:**

| result | reading |
|---|---|
| `2928` and `2957` at **0 px**, `4676` a hit | **`305` §1.4 STANDS.** The reorder is real, dated to `299`, and draws nothing; `4676`'s pixels are something else and the display list is exhausted as a place to look |
| **either of `2928` / `2957` a hit** | **`305` §1.4 IS RETRACTED.** The reorder becomes a live candidate again and `305` §4's ordering of the work is wrong |
| `4676` **clean** | the frame that started all of this is not divergent under `py` and the whole of `303` §5's third frame is in question |

`dlgrab_7360` is the `VIEWRESTORE=0` falsifier arm (`298` §3) and is **inadmissible either way** —
it is in the list so that its number is on the record, not so that it can be read.

---

## §3 — THE SHOT LINE PRINTS A DIFFERENT COUNTER FROM THE DUMP LINE. **OPTIONAL. IT IS A LABEL.**

`305` §2: `[getv][dlgrab] frame 4676` and `[getv][shot] frame 4677` describe **the same frame**.
The picture and the list are paired by construction (`port_render.c:748-759` sets the request
inside the frame's render, `gfx_opengl.c:1495-1520` consumes it in that frame's `end_frame`), and
`fno` at `gfx_opengl.c:1497` is a private counter with a different origin that reads exactly one
higher in all fourteen pairs.

**IT IS STILL A TRAP, BECAUSE READING THE TWO LINES AS TWO FRAMES VOIDS `303` §5's HEADLINE**, and
this session drafted that retraction before checking the call. **The fix is to make the shot line
print the number the dump line printed**, so the log cannot be misread again. **This is a
DIAGNOSIS of a label and it is filed as one — `301` §0, the count is five, and nobody should
patch this without reading both call sites first.**

The edit, when someone takes it: `ge_shot_request_path` already carries the dump's frame number
in the filename it was given; **print the requested path's number rather than `fno` whenever the
shot was made by a `dlgrab` request**, and leave the `GETV_SHOTFRAME` path printing `fno`, which
is the counter that knob is set against. **Two counters, two lines, each labelled with which one
it is.**

---

## §4 — ►►►►►►►► THE ONE THING THIS SHEET ASKS THE OWNER FOR: **WHAT DID FC3 AND FC4 LOOK LIKE?**

**`RUN-SHEET-304` §3 WAS RUN AND ITS COUNTERS ARE NOW READ** (`305` §2a): the knob took at full
strength in **every one of 467 windows** (`clamped == straddle`), the venue was **the road** and
not the cast roll (**median 1,359 clamped/Mvtx** against the cast roll's 45,000), and the
per-window `beyond_far` spans 0–21% with a median of 3.81% (FC3) and 5.47% (FC4).

**THE COUNTERS CANNOT DECIDE THIS AND `303` §3 SAYS SO. THE VERDICT IS THE OWNER'S EYES.**

- `run_304_FC3_road_on.log` — `GETV_FARCLAMP=1`, the shipping default
- `run_304_FC4_road_off.log` — `GETV_FARCLAMP=0`

**One sentence about each, in your own words, the way `303` §3's was recorded** — *"they both
have blur in the far distance, but not as bad as the other test"*. **If the two arms looked the
same again, `RUN-SHEET-303` §0.1 is a `279` §7 null for the second time and it should be closed
rather than re-run a third time.** If FC4 looked better, `303` §0.1 is finally supported and
`GETV_FARCLAMP` becomes a real decision.

**Nothing needs re-running. The pictures are in `grabs_304_FC3\` and `grabs_304_FC4\`.**

---

## §5 — THE COMMITS. **TWO REPOS. NOTHING IS STAGED BY THIS SHEET UNTIL YOU RUN IT.**

**►► `--ignore-cr-at-eol` IS A `git diff` OPTION AND `git status` REJECTS IT** -- `error:
unknown option 'ignore-cr-at-eol'`, and the block stops there. `[MEASURED]` on the bridge's
`git` 2026-09-03. `00-STATE` §6 and every prompt since `303` say *"use `git --no-optional-locks
status` and pass `--ignore-cr-at-eol`"* in one breath; **they are two rules for two commands.**
The blocks below put the flag only where it works.

**EVERY BLOCK OPENS WITH `git rev-parse --show-toplevel` — `299` / `RUN-SHEET-300` §7: a
git-bash path in a PowerShell block fails SILENTLY INTO THE WRONG REPO and the closing
`git log --oneline -1` prints the wrong repo's HEAD.** Read that line before reading anything
else the block prints.

### 5a — `goldeneye-native`: the new instrument

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
git rev-parse --show-toplevel
git --no-optional-locks status --short -- getv/tools/dlgrab_dlorder.py
git diff --stat --ignore-cr-at-eol -- getv/tools/dlgrab_dlorder.py
git add -- getv/tools/dlgrab_dlorder.py
git commit -F F:\Projects\GEVR\GoldenEyeVR\COMMIT-MESSAGE-2026-09-03h-native.txt
git log --oneline -1
```

**GATE §5a — the first line must end in `goldeneye-native`.** `dlgrab_dlorder.py` is a NEW file,
so `status --short` reads `?? getv/tools/dlgrab_dlorder.py` and `diff --stat` prints nothing;
that is correct and is not a failure.

### 5b — `GoldenEyeVR`: the documents

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR
git rev-parse --show-toplevel
git --no-optional-locks status --short -- repo/docs/00-STATE.md repo/docs/PRIORITY-BOARD-299.md repo/docs/RUN-SHEET-305.md repo/docs/305-THE-CENSUS-COMPARES-SETS-AND-BOTH-DL-EXPLANATIONS-ARE-NOW-DEAD.md repo/docs/NEXT-SESSION-PROMPT-305.md repo/docs/NEXT-SESSION-PROMPT-306.md
git diff --stat --ignore-cr-at-eol -- repo/docs/00-STATE.md repo/docs/PRIORITY-BOARD-299.md repo/docs/NEXT-SESSION-PROMPT-305.md
git add -- repo/docs/00-STATE.md repo/docs/PRIORITY-BOARD-299.md repo/docs/RUN-SHEET-305.md repo/docs/305-THE-CENSUS-COMPARES-SETS-AND-BOTH-DL-EXPLANATIONS-ARE-NOW-DEAD.md repo/docs/NEXT-SESSION-PROMPT-305.md repo/docs/NEXT-SESSION-PROMPT-306.md
git commit -F F:\Projects\GEVR\GoldenEyeVR\COMMIT-MESSAGE-2026-09-03h.txt
git log --oneline -1
```

**GATE §5b — the first line must end in `GoldenEyeVR`, and `diff --stat` must name EXACTLY THREE
files: `00-STATE.md`, `PRIORITY-BOARD-299.md` and `NEXT-SESSION-PROMPT-305.md`** (the last is the
rule `2` SUPERSEDED banner, not a rewrite). **The three NEW documents do not appear in
`diff --stat` because they are untracked — they appear in `status --short` as `??`.** If
`diff --stat` names a fourth file, **stop and read it: this session edited exactly three tracked
files and touched no source outside `getv/tools/`.**

---

## §6 — AFTER `305`

1. **`RUN-SHEET-304` §2a** — date the POLYGON with a run. Still the only part of `304` owed, and
   `305` §1.3 dated a DIFFERENT fault, which does not answer it.
2. **The per-eye MATRIX CONTENTS instrument.** `305` §4: everything the dump records is now
   excluded for the polygon, and the dump records addresses, never values. **This is the next
   thing to build and `305` deliberately does not design it.**
3. **`H15`** — the census's set comparison, now closed by a sibling tool rather than by changing
   the census. Decide whether the order check belongs INSIDE `dlgrab_eyecensus.py`; **`304` §1.2
   is the precedent for editing an instrument, and `H8` is the argument for keeping two.**
4. **`C1a`** — `already-converted=0` is still one run and one route.
5. **`H11` / `H12` / `H14`** — `H12` was applied by hand in `305` §2a and is still not in the
   code. **A windowed accumulator for `[getv][far]` would have made §2a a `Select-String`.**
