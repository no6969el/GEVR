# `306` — THE SWEEP CRASHED ON AN ARROW, AND THE RUN EVERYONE SAID WAS OWED WAS ALREADY ON DISK

**WRITTEN OFFLINE 2026-09-04.** No build, no game, no commit by this session. Binary untouched
and verified against `EXPECTED-EXE-303.txt` this session: `45756E5ADB5F…E7223F92`,
**18,070,774 bytes**, 21:05:38Z.

**`306` RAN NOTHING. EVERY NUMBER BELOW IS OFF THE FILESYSTEM OR OUT OF `git log`** — both
bridge-safe reads (`00-STATE` §6) — **except the two selftests, which were re-worn on the bridge
and are NOT the gate. `RUN-SHEET-306` §1 is the gate, and `H7` is why.**

---

## §0 — THE ONE THING TO READ IF YOU READ NOTHING ELSE

**THREE DOCUMENTS SAID WORK WAS OWED. THE FILESYSTEM SAYS TWO OF THE THREE WERE ALREADY DONE, AND
THE THIRD DIED IN A WAY NOBODY LOOKED FOR.**

| | |
|---|---|
| **1** | **`RUN-SHEET-305` §5 IS WORN.** `689b009` (native, `dlgrab_dlorder.py`) and `e58e1f1` (`GoldenEyeVR`, six documents) are committed and both trees are clean on every named path. **`NEXT-SESSION-PROMPT-306` opens with *"NOTHING IN `305` IS COMMITTED YET"* and that sentence was already false when it was written** |
| **2** | **►►►► `RUN-SHEET-305` §2 WAS RUN AND IT CRASHED.** `order_sweep_305.txt`, 23:45:07Z, ends in a `UnicodeEncodeError` from `cp1252` on `\u25ba` — **`►`** — raised at `dlgrab_dlorder.py:93`, the `PERMUTATION` verdict line, **the instant the sweep reached `dlgrab_2928`, the first permuted frame in the corpus.** The instrument died at exactly the finding it was written to bound |
| **3** | **►►►►►►►► `RUN-SHEET-304` §2a's `P1` ARM IS ON DISK, CLEAN, ADMISSIBLE AND UNREAD.** `run_304_P1_polygon_viewer_on.log`, `ARM=P1 START=2026-09-03T23:48:34Z`, nine grabs in `grabs_304_P1\`, **frames 1225–1391 — gameplay, which is GATE §2a's own requirement** — no `EXCEPTION`, `game_exit requested`. **Four documents carry §2a as *"the only part of `304` still owed"*.** The reading has never been taken and `P2` has not run |
| **4** | **THE CORPUS IS 265 DUMPS, NOT 256** — `grabs_304_P1`'s nine. `RUN-SHEET-305` GATE §2a pre-registers 256 and would have refused the sweep on a discrepancy that is fully explained by one folder |

**AND THE COUNT OF FILED FIXES THAT WERE WRONG IS STILL FIVE, because `306` filed no fix for the
polygon.** It fixed an instrument's output encoding, which is a different kind of thing and is
`§2` below.

---

## §1 — ►►►► THE SWEEP DIED ON A CHARACTER, AND THE GATE THAT WAS SUPPOSED TO CATCH IT IS
EXPOSED THE SAME WAY

`[MEASURED]` on disk, `order_sweep_305.txt`, 11,148 bytes, **23:45:07Z** — three minutes before
the `P1` run. It contains **30 `REFUSED` (mono) and 12 `ORDER IDENTICAL`** verdicts — 42 files —
and then, on the 43rd:

```
file        …\grabs_299_E1\dlgrab_2928.txt
DL CALLs    eye0 46   eye1 46
Traceback (most recent call last):
  File "…\getv\tools\dlgrab_dlorder.py", line 165, in main
    v = report(p, f.read())
  File "…\getv\tools\dlgrab_dlorder.py", line 93, in report
    print(f"VERDICT     \u25ba\u25ba PERMUTATION -- same {len(c0)} targets, …
  File "C:\…\Python313\Lib\encodings\cp1252.py", line 19, in encode
    return codecs.charmap_encode(input,self.errors,encoding_table)[0]
UnicodeEncodeError: 'charmap' codec can't encode characters in position 12-13
```

**THREE THINGS FOLLOW, AND ONLY THE FIRST IS OBVIOUS.**

**1. THE SWEEP PRODUCED NOTHING USABLE.** It classified 42 of 265 dumps and stopped. No
`================` summary line was ever printed, so **`RUN-SHEET-305` GATE §2a has no reading at
all** — not a pass, not a fail.

**2. `--selftest` IS EXPOSED TOO, AND IT IS `RUN-SHEET-305`'s FIRST GATE.** `dlgrab_dlorder.py:136`
prints check `B`'s header — `"B. ►► THE CHECK THAT FAILS ON A SET COMPARISON"` — **before**
`7 checks, 0 failed`. On a stdout that resolves to `cp1252`, **GATE §1a cannot pass either.**
`H7` is not an abstraction here: the bridge's `python3` writes UTF-8 by default and never saw it.

**3. ►►►► AND `stereo_disparity.py`'s PEG ALARM IS ONE OF THE THREE `►` PRINT SITES (`:261`).**
`H1` exists because that alarm **had never fired**; `301` §2 rebuilt `measure()` so that it can.
**`--selftest` does NOT cover it:** check `B` exercises the DETECTOR and prints its own ASCII
verdict (`peg detector FIRED  PASS`), while **`:261` is the REPORT path's alarm and prints only on
a real frame.** `[MEASURED]` on the bridge after the edit: `selftest A/B/C` all `PASS`, unchanged.
**So the first time the alarm fired on a redirected run against a real grab, it would have raised
the same exception** — the alarm and the crash are the same line. **Same family as `H1` itself, one
level over: an alarm that has never fired is an alarm whose PRINT has never been executed, and a
selftest that checks the decision instead of the output does not close that.**

### 1.1 — WHAT `306` CHANGED, AND WHY IT IS THE NARROW FIX AND NOT THE CLEVER ONE

**FIVE PRINT SITES, `►` → `>>`, NO LOGIC TOUCHED:**

| file | line | what it prints |
|---|---|---|
| `dlgrab_dlorder.py` | 93 | the `PERMUTATION` verdict — **the line that crashed** |
| `dlgrab_dlorder.py` | 136 | `--selftest` check `B`'s header |
| `stereo_disparity.py` | 261 | **the `H1` peg alarm** |
| `stereo_eyediff.py` | 55, 60 | the module docstring, which `:419` prints on a usage error |

**THE ALTERNATIVE WAS `py -X utf8` OR `PYTHONIOENCODING`, AND IT IS THE WORSE FIX**: it makes every
future block carry an environment flag that a copy-paste can drop, and `00-STATE` §7a says every
command the owner runs is supplied complete. **ASCII output has no dependency to forget.** The
flagged form is kept in `RUN-SHEET-306` §1e as a fallback **for diagnosis only** — if it passes
where the plain form failed, the console encoding is the fault and not the tool, and that is worth
knowing.

**`[MEASURED]` on the bridge after the edit: `dlgrab_dlorder.py --selftest` reads `7 checks,
0 failed` and `stereo_eyediff.py --selftest` reads `16 checks, 0 failed`, both unchanged.**
**THE BRIDGE IS NOT THE GATE.** `RUN-SHEET-306` §1 re-wears both under `py`, and it deliberately
uses a **plain `py`** so that the run tests the fix rather than masking it.

**AND THE CHECK COUNT DID NOT MOVE ON PURPOSE.** Adding an eighth check would have been the
natural instinct and it would have broken the pre-registered gate line `7 checks, 0 failed` that
`305`, `NEXT-SESSION-PROMPT-306` and `RUN-SHEET-306` all quote. **A gate's text is part of the
gate.**

---

## §2 — `RUN-SHEET-304` §2a's `P1` ARM: RUN, CLEAN, ADMISSIBLE, AND NEVER READ

`[MEASURED]` on disk and out of the log's own banners:

| | |
|---|---|
| log | `run_304_P1_polygon_viewer_on.log`, 10,950,073 bytes, **23:48:47Z** |
| provenance | **exactly one log**, `[getv][arm] GETV_ARM=P1`, `[getv][run] ARM=P1 START=2026-09-03T23:48:34Z` — `279` §2 satisfied, `H5` satisfied, `N2` satisfied |
| arm | `GETV_STEREO_REBUILD_VIEWER=1`, `GETV_STEREO_REBUILD=1`, `GETV_STEREO_VIEWRESTORE=1`, `GETV_STEREO_OFFSET=0`, stage 29, `GETV_FARCLAMP=1`, `GL_DEPTH_CLAMP ON` |
| grabs | **nine**, `dlgrab_P1_1225 / 1245 / 1263 / 1284 / 1305 / 1324 / 1343 / 1365 / 1391`, `.txt` + `.bmp` both present for all nine, and **nine `[getv][dlgrab] frame` announcements in the log matching them exactly** |
| health | `EXCEPTION` count **0**; `game_exit requested` present |
| venue | frames **1225–1391**, well past the ~541-frame opening — **GAMEPLAY, which is GATE §2a's stated requirement and the reason `304` wrote the gate that way** |

**WHAT IS STILL MISSING IS THE READING, NOT THE RUN.** `stereo_eyediff.py` has never been pointed
at `grabs_304_P1`. **`RUN-SHEET-306` §3 is that read and it costs seconds.** `P2` — the same walk
with `GETV_STEREO_REBUILD_VIEWER=0` — has not been run, and GATE §2a's table needs both columns.

**►► AND THE THIRD INSTANCE OF ONE TRAP IS NOW ON THE RECORD.** `305` §2a caught `304` §3 and §4
being carried as owed while they sat on disk, and wrote the rule: *a run sheet's owed list is a
claim about the filesystem.* **`306` caught the same shape twice more in one session** — `P1`, and
`305`'s own commits. **The commits are the sharper case, because `git log` answers it in one
bridge-safe command and nobody ran it.**

---

## §2a — THE SHOT-LINE LABEL, NOW AT 23 OF 23

`305` §2 measured `[getv][dlgrab] frame N` beside `[getv][shot] frame N+1` in 14 of 14 pairs and
proved from the call sites that they are **the same frame** (`port_render.c:748-759`,
`gfx_opengl.c:1495-1520`, `fno` a private counter). **`P1`'s nine pairs are `1225/1226 … 1391/1392`
— nine more, same offset, 23 of 23.** **A consistent offset in every pair is a label mismatch; a
real off-by-one is not consistent.** `RUN-SHEET-305` §3's diagnosis is unchanged and still unpatched.

---

## §3 — WHAT DID NOT CHANGE

- **`303` §2, §3, §4, §5, §6 stand. `304` §1 stands. `305` §1 and §2a stand — subject to §1's
  re-wear**, which is the same condition `305` put on itself.
- **The polygon has no new evidence and no new explanation.** `306` read no pixels.
- **The binary is untouched.** No build, no run, no stage, no commit by this session.
- **`305` §1.4's falsifier is still the open edge**, and `RUN-SHEET-306` §2 is still what bounds it.

---

## §4 — WHERE THE WORK GOES

1. **`RUN-SHEET-306` §1** — the `py` re-wear, now also the test of the ASCII fix. Seconds.
2. **§2** — the corpus sweep, split into a 256-dump reproduction and `P1`'s nine as new data.
3. **§3** — read the `P1` arm. **This is the cheapest unread evidence on the board.**
4. **§4** — `P2`, the other half of `304` §2a.
5. **§5** — the FC3/FC4 sentence, owed to `305` §4 and to nobody else.
6. **§6 — `S3`, THE SEPARATION GATE. `258` STAGE 6's EXIT GATE, NEVER RUN, AND ITS STANDING
   OBJECTION HAS LAPSED BY MEASUREMENT** — `303` §2 filled the second eye, so GATE 4.1's four
   conditions are satisfiable for the first time. **`PRIORITY-BOARD-306` GROUP `V` is the ordered
   route from here to a headset, and it is the first time this project has written one down.**
7. **The per-eye `MODEL_MTX` CONTENTS instrument** — `305` §4, unchanged, undesigned, and still
   the only level left for the polygon.

---

## §5 — FILES

| file | repo | change |
|---|---|---|
| `getv/tools/dlgrab_dlorder.py` | `goldeneye-native` | 2 print sites, `►` → `>>`. No logic |
| `getv/tools/stereo_disparity.py` | `goldeneye-native` | 1 print site (**the `H1` peg alarm**), `►` → `>>` |
| `getv/tools/stereo_eyediff.py` | `goldeneye-native` | 2 docstring lines, `►` → `>>`; `:419` prints the docstring |
| `repo/docs/306-…md` | `GoldenEyeVR` | this document |
| `repo/docs/RUN-SHEET-306.md` | `GoldenEyeVR` | **NEW.** §1 the re-wear, §2 the split sweep, §3 the `P1` read, §4 `P2`, §5 the FC sentence, §6 `S3`, §7 the commits |
| `repo/docs/PRIORITY-BOARD-306.md` | `GoldenEyeVR` | **NEW.** Supersedes `PRIORITY-BOARD-299`; adds GROUP `V` (the route to a headset) and GROUP `X` (the XR layer), and `H16` |
| `repo/docs/PRIORITY-BOARD-299.md` | `GoldenEyeVR` | SUPERSEDED banner only — rule `2` deletes nothing |
| `repo/docs/NEXT-SESSION-PROMPT-306.md` | `GoldenEyeVR` | SUPERSEDED banner only |
| `repo/docs/NEXT-SESSION-PROMPT-307.md` | `GoldenEyeVR` | **NEW** |
| `repo/docs/00-STATE.md` | `GoldenEyeVR` | currency, §3, §4, §6 |

**NOTHING WAS BUILT, RUN, STAGED, COMMITTED, BRANCHED OR TAGGED.**
