Read `repo\docs\00-STATE.md` — **§3 WORKS (the top FIVE entries, three of them new instruments)**,
**§3 OWNER ACTION OUTSTANDING**, then **§4 RETRACTED**, then **§6 TRAPS — four new ones, and two
of them are about fixes that were written down wrong on a board and would have looked like they
worked.** Then **`301` IN FULL — it is short and §0 is the whole session in a table.** Then
**`RUN-SHEET-301` §1 → §8 in order.** Then **`PRIORITY-BOARD-299`**, which is where the work goes
once these arms land.

Same rules as always. Bridge reads are not free (`00-STATE` §6): `git log`, `git show` and
`git diff <path>` are safe; `git status` and `git add` are **NOT** (use
`git --no-optional-locks status`), and **a bare `git status` in the decomp prints 2,106 CRLF-dirty
files — so always give it a path list** and pass `--ignore-cr-at-eol`. The build, every run and
every commit are the owner's, on the main PC — **you write and validate OFFLINE, then supply
complete copy-paste command blocks (§7a). Quote a run-sheet block, never paraphrase it.**

---

## ►►►► WHERE THINGS ACTUALLY STAND ◄◄◄◄

**`301` REPAIRED THE INSTRUMENTS AND BUILT NOTHING.** Every `LOW` and `MEDIUM` hole on
`PRIORITY-BOARD-299` is closed — `H1`, `H2`, `H3`, `H5`, `H6`, plus `H10` which `301` found while
verifying its own work — along with both of `299`'s unfiled candidates (`N1`, `N2`). `H4` is
surveyed but its banner work is open. `H9` was held back deliberately: it is `HIGH`.

**TEN OFFLINE GATES PASS. NOTHING IS BUILT.** `goldeneye.exe` is still **18,062,771 bytes at
`02:40`** from `299` §9.6, and **that binary does not contain any of `301`'s work.**

**THE THREE ARMS THAT HAVE NEVER RUN STILL HAVE NEVER RUN.** `RUN-SHEET-300` §4/§5/§6 —
GROUP A's A2/A3/A4 — are **SUPERSEDED** and carry a banner saying so. They live on as
`RUN-SHEET-301` §5/§6/§7, re-gated onto the repaired instruments. **Do not run them from `300`.**

---

## ►►►►►►►► THE FIRST ACTION: `RUN-SHEET-301`, FROM §1. ◄◄◄◄◄◄◄◄

**NOTHING IN IT HAS BEEN WORN.** §1 gates → §2 regen → §3 build → §3c the binary identity → §4 a
smoke read → §5/§6/§7 the arms → §8 the commits (which may be run first; see §8.5).

**§3 IS WHERE THIS SESSION'S REAL RISK LANDS.** `301` touched four C files. `chrprop.c` was fully
compiled offline by `stereo_harness.sh`'s real-header gate, and `port_render.c`, `ge_config.c` and
`gfx_pc.c` are now type-checked by the new `port_syntax_gate.sh` — **but that gate uses STUB
SDL/GL headers, so the build is still the authority.** A failure in §3 is more likely to be in
those files than anywhere else; read the FIRST error, not the last.

**IF THE OWNER HAS ALREADY RUN SOME OF IT, ASK WHICH GATES PRINTED WHAT BEFORE ASSUMING ANYTHING.**
A run sheet that is partly worn is the shape that produced `279` §7 four times.

---

## ►►►► WHAT THE NEW INSTRUMENTS SAY, AND WHY THE OLD READINGS CANNOT BE COMPARED ◄◄◄◄

**Five lines in the log are new or changed. Three of them replace something that was misreporting,
so a number from before `301` is NOT comparable to one from after.**

| line | what it replaces |
|---|---|
| `[getv][run] ARM=<n> START=<utc>` | nothing. `H5` — the log now identifies its own arm |
| `[getv][arm] GETV_ARM=<n>` | nothing. `N2` — grabs are `dlgrab_D1_5400.*`, not `dlgrab_5400.*` |
| `[getv][near] SCENE ... \|\| CLAMP ACTION ...` | the NEAR group inside `[getv][far]`. `N1` |
| `[getv][stereo][rebuild] WINDOW ...` | the SUMMARY line as the thing you score. `H2` |
| `[getv][config] ... GETV_FILTERING=<env> -> filtering=<effective>` | `filtering=<effective>` alone. `H4` |

**►► THE ONE TO READ FIRST IS `ZERO-REBUILD FRAMES` ON THE `WINDOW` LINE.** `298` §1.1 scored
ARM 3 green off six spot checks; the same run had **372 frames** in which the second eye rebuilt
nothing, and the old census could not see them because it printed one frame in `n`. **That number
has never been read on a real run. `RUN-SHEET-301` §7 is where it gets read.**

---

## ►►►► THE THING THIS SESSION SHOULD BE MOST CAREFUL ABOUT ◄◄◄◄

**A HOLE'S FILED FIX IS A DIAGNOSIS, NOT A PATCH — `301` §0.** Two of the six on the board were
wrong:

- **`H1`** said *"clamp `hi`/`lo` to `±search`"*. That **reads past the end of the row**: `hi` is
  clipped by the IMAGE EDGE, not by `search`.
- **`H3`** said *"print `ge_props_zsnap_n` beside `list=`"*. That **prints `-1` on every frame**,
  because `gePropsRestoreTickZDepth()` nulls it at `lv.c:1135` and the report runs at `lv.c:1151`.

Both took under a minute to catch by **reproducing the arithmetic and reading the call order**
rather than the declaration. The `H3` shape is the worse one: it swaps a misleading number for a
**constant**, and nothing would ever notice. **`H4`'s remaining banner work is the same kind of
task on 324 more knobs — expect at least one of them to be filed wrong too.**

---

## ►►►► AFTER THE ARMS: WHERE THE WORK GOES ◄◄◄◄

**`A4` (`RUN-SHEET-301` §7) UNBLOCKS ALL OF GROUP B**, which is the dead eye in every level's
opening — ~541 deterministic frames where the second eye receives no models, and **the first thing
a player sees, every level.** `B1` turns entirely on whether §7 reads `flag=` or `type=`, and
**both branches are live candidates: `299` refused to assert either and `301` did not change
that.** Do not inherit a guess.

Then, roughly in this order:

- **`H4`'s banners.** `MEDIUM`, and `knob_banner_survey.py --used-in repo/docs` already ranks the
  324 silent knobs by how often the docs actually set them. **The convention is settled: every
  banner prints the FULL knob name and an `=`.** Work down the list; do not sweep.
- **GROUP D**, the stereo gates that have never run — unblocked, and `D1` is `LOW`.
- **GROUP C**, the `NaN` nobody has looked at. `HIGH`, and `301` did not touch it.
- **`H9`.** `HIGH`, deliberately held: nothing answers *"is the picture right"* without the
  owner's eyes, and every visual verdict in `298`, `299` and `301` is `[REPORTED]`. **It needs a
  known-good reference frame the project does not have. Name it as accepted, or build it
  deliberately — but not at the end of a session.**

---

## ►►►► HOUSEKEEPING THAT WILL BITE IF IGNORED ◄◄◄◄

- **`gfx_pc.c` IS GITIGNORED.** Its changes exist ONLY in
  `getv/patches/thirdparty/0001-getv-port-layer.patch`. After touching any of the fifteen
  third-party files run `tools/fetch-thirdparty.sh regen`; **`verify` returning `15/15` is the
  proof.** Since `301` regen works over the bridge and the patch no longer churns — two regens
  over unchanged sources are byte-identical — **so any diff in that file is now a real change.**
- **`EXPECTED-EXE-301.txt`** is written by `§3c` and every arm throws on a mismatch. **Re-run
  `§3c` after any rebuild** and the arms need no editing.
- **PowerShell 7.** `Select-String -Encoding Byte` does not exist and throws; scan a binary with
  `[System.Text.Encoding]::Latin1.GetString([System.IO.File]::ReadAllBytes($exe))`. `00-STATE` §6
  records this and `301` nearly reintroduced it anyway.
- **`build_windows.ps1` lives in `getv\`, not the repository root**, and the binary lands in
  `getv\build-windows\`. A `Set-Location` to the wrong one fails silently into whatever directory
  the prompt was in.
- **If a new `getv/port/**` file fails `port_syntax_gate.sh`, that is the gate working.** Either
  add what it needs to `glstub/` — **checked against the real spec, never against whatever
  silences the error** — or add it to the script's EXCLUDE list WITH ITS REASON. Do not leave it
  failing and do not silence it.
