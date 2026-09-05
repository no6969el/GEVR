Read `repo\docs\00-STATE.md` — the **currency line at the top** (it carries `311`'s full result,
`[MEASURED]`, written from the repo and from the four `disp_311_*.txt` files read back on the
bridge, not from a paste), then **§4 RETRACTED — THREE new** (candidate `A`, `[PREDICTION] 2c`,
and one process defect that is the ASSISTANT'S), then **§6 TRAPS**. Then
**`311-THE-SEPARATION-IS-APPLIED-THE-PIXELS-ARE-NOT` §0, §5, §6 and §7** — §0 is one table, §5 is
the `MODE=2` arm, §6 is the retraction in arithmetic, §7 is what this session got wrong. Then
**`RUN-SHEET-312`** — §0 is the gate and it is NOT `912` any more, §1 is the scorer, §2 is the job.
Then **`PRIORITY-BOARD-311`** — the current board; `310`'s and `309`'s are bannered.

Same rules as always. **You work OFFLINE. The build, every run and every commit are the owner's, on
the main PC. Supply complete copy-paste PowerShell blocks; quote a run-sheet block verbatim, never
paraphrase it. Never stage, commit, branch, merge or tag.** `git log`, `git show` and
`git diff <path>` are bridge-safe; `git status` needs `--no-optional-locks` **and a path list**.
**►►►► A PLACEHOLDER IS NOT A COMMAND: `<` is a RESERVED OPERATOR in PowerShell** (`00-STATE` §7a).
**►►►► INSTRUMENT OUTPUT IS ASCII (`H16`): the docs may carry arrows, the tools may not.**
**►►►► DO NOT EDIT A TRACKED SOURCE FILE WITH `Get-Content`/`-replace`/`Set-Content`** (`308` §1.1,
`00-STATE` §6). Hand the splice to `py` and do it in BYTES.
**►►►► A HOLE'S FILED FIX IS A DIAGNOSIS, NOT A PATCH — the count of wrong filed fixes is five
(`301` §0). MEASURE BEFORE YOU PATCH.** `311` is the case FOR that rule at its strongest: **the
last candidate standing was `A`, it had survived four sessions of elimination, and one five-minute
run killed it. Nobody had filed it, so the count did not move.**

---

## ►►►► THE FIRST COMMAND, AND IT IS NOT OPTIONAL ◄◄◄◄

`306` §0 is the standing rule: **a claim that work is owed is a claim about git.** `311` ran this
and its opening sentence was right for the second session running — but it is one command.

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR
git log --oneline -3
git --no-optional-locks status --porcelain -- repo/docs
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
git log --oneline -3
git --no-optional-locks status --porcelain -- getv/tools
```

**►►►►►►►► AND THE ANSWER WILL BE MESSY FOR A REASON THAT IS STILL NOT ANY SESSION'S: THE DOCS
TREE CARRIES A USERNAME SCRUB.** `[MEASURED]` `311` §1: **57 tracked files under `repo/docs`**,
every sampled hunk `C:\Users\<USER>\…` -> `C:\Users\<USER>\…`. `310` measured 58 and `00-STATE.md`
is the one that left the list, because `c0188a0` could not separate its scrub hunk from `310`'s own
edit without staging hunks. **The 57 are nobody's session work. Do not sweep them into a commit and
do not "tidy" them** (`307` §5, sixteen strays).

- **`311` LEFT TWO COMMITS' WORTH OF WORK.** The first is IN: **`9cabee8`** (`docs(311a)`), the
  `00-STATE` §4 retraction of `310` §8's argument, committed BEFORE the runs.
- **The second is `311`'s session commit** — the block is `311-THE-SEPARATION-IS-APPLIED-THE-PIXELS-ARE-NOT`
  §8 and the message file is `COMMIT-MESSAGE-2026-09-04h.txt`, written and correct. **Check whether
  it is in before writing any sentence about what is owed** (`305` §2a, `306` §0).

`goldeneye-native` has **two untracked scratch files from `309`** — `getv/tools/_patch309.py`
(spent) and `getv/tools/ladder_driver.py` (**keep only as a deliberate decision**). Neither belongs
in any commit. **`311` added nothing to that repo: no tool was edited and no build was made.**

---

## ►►►► WHERE THINGS ACTUALLY STAND ◄◄◄◄

**`H19` HAS BEEN NARROWED FIVE TIMES AND IT IS NOW ONE STEP WIDE.** Five candidates are dead, all
by measurement:

| candidate | how it died | where |
|---|---|---|
| the eye-width / pixel conversion | three independent ways — the log, `gfx_pc.c`'s scale arithmetic, and the tool's detected play area | `309` §6.1, `310` §0 item 6, §8.1 |
| the frustum and its 4:3 term | **identity** — the renderer and the prediction are the same four floats — and `tR` **cancels** structurally | `310` §1, §2, §0 item 5 |
| `C` — a correlator biased on multi-depth scenes | the flat wall IS single-depth and it still reads `0.705` | `310` §7 |
| `B` — a short measured depth | the ratio is FLAT over a 6.7-fold ladder; a scale error needs `c = -22.4` at `D = 76`, which reads `0.956` at `D = 509` | `310` §8, **corrected** in `00-STATE` §4 by `311` |
| **`A`** — a short APPLIED SEPARATION | **`MODE=2` reads `0.7075` while `geStereoOffsetCameraPos()` returns 0** (`stereo.c:355-357`). `0.7022 / 0.7075 = 0.992` | **`311` §5, §6** |

**►►►►►►►► WHAT IS LEFT IS THE ONE STEP THE PREDICTION DOES NOT OWN: NDC FRACTION -> PIXELS.**
The prediction is deliberately a FRACTION of the eye's width (`stereo.c:434-441`) and the measuring
tool multiplies by a half it DERIVES from the image. **`310` proved three ways that the play area
IS `1825` px and each half IS `912` px — and none of the three measured what NDC `+/-1` SPANS
inside that half.** `[MEASURED]` of the SYSTEM. **NOT a diagnosis of a line. Nothing is filed and
nothing is patched.**

**AND THE RATIO IS A PURE SCALE, MEASURED OVER A 4-FOLD SEPARATION RANGE:** medians `0.6907` /
`0.7036` / `0.6960` at `sep` `32` / `64` / `128`, ratio-of-ratios `1.019`, `0.989`, `1.008`.

### ►►►►►►►► AND ONE THING `310` SAID THAT `311` HAD TO WALK BACK ◄◄◄◄◄◄◄◄

`310` §7 called the ratio FLAT with a total spread of `0.026`. **That was six grabs on ONE
separation.** `[MEASURED]` `311` §7.1, pooled over all fifteen admissible `MODE=1` grabs:
**`D < 400` median `0.7097` against `D >= 400` median `0.6924` — a ~2.5% downward drift with
depth.** It fits `0.670 + 11.0/D` and it fits `|dx|` about as well, **and within one arm `D` and
`|dx|` are inversely related, so `311` cannot separate them.** It does not touch the headline —
`0.705` against `1.000` is a 30% effect — **but the correlator's ~2% error bar is now the same size
as an unexplained trend, and it must not be quoted as though the trend were noise.**

---

## ►►►►►►►► THE FIRST JOB: `RUN-SHEET-312` §2. **EFFORT: `LOW`.** ◄◄◄◄◄◄◄◄

> **EFFORT IS THE OWNER'S TIME, NOT THE ASSISTANT'S.**
> **`LOW`** = offline only, or a short run with no build — minutes.
> **`MEDIUM`** = a build, or a run plus real analysis — one sitting.
> **`HIGH`** = a design decision or unbounded scope, **and it must not be started at the end of a
> session.**
>
> **THIS SESSION'S RECOMMENDED SHAPE, IN ORDER:**
>
> | | job | effort | costs the owner |
> |---|---|---|---|
> | **1** | **`RUN-SHEET-312` §2 — the `GETV_WINDOW` sweep, two arms** | **`LOW`** | **two short runs on the same wall, ~5 minutes, no build** |
> | **2** | score both with §1's `Score-Arm2` and read the two medians against §2.1 | **`LOW`** | one paste |
> | **3** | file the answer, update `H19` on the board | **`LOW`** | one commit block |
> | **4** | **`H18`'s durable form** — make `stereo_disparity.py` refuse an out-of-range `--predicted-frac` itself, and re-run `--selftest A/B/C` | **`LOW`** | one paste, no build. **Do it AFTER the runs, never before** |
>
> **§2 IS FIRST BECAUSE `GETV_WINDOW` IS THE ONLY KNOB THAT MOVES THE PIXEL GEOMETRY AND NOTHING
> ELSE.** It does not touch `fovy`, the N64 `320x180` view, `tanw`, or the separation.
> **`RUN-SHEET-312` §2.1 pre-registers TWO candidate scales that fit the `2560x1369` control
> equally well and predict OPPOSITE results on the two arms** — `1600x1369` reads `0.50` under one
> and `1.00` under the other; `2560x800` reads `1.00` under one and `0.42` under the other.
> **"Neither" is the third outcome, it means the factor is geometry-independent, and it costs the
> same five minutes.**
>
> **►►►► AND THE ONE THING THAT WILL BITE IF IT IS MISSED: THE HALF IS NOT `912` ON EITHER ARM.**
> `RUN-SHEET-311` §1's scorer hard-codes `$frac * 912.0`. `RUN-SHEET-312` §0 has the table and §1's
> `Score-Arm2` takes the half as an argument: **`800.00` for `1600x1369`, `533.33` for
> `2560x800`.** The TOOL derives its own half from the image and is unaffected; only the PowerShell
> admissibility figure moves.
>
> **DO NOT START GROUP `C` / `V7` (the per-eye contents instrument) — it is `HIGH` and it is
> `PRIORITY-BOARD-311` §E item 9.** **The instrumented print that `310` and `311` kept naming as
> the third step is `MEDIUM` and `311` §6 LOWERED ITS VALUE: the applied separation is no longer
> the suspect, so an instrumented print of the NDC -> pixel step is the one worth a build, and
> only after §2 says whether the window can move it.**

---

## ►►►► THE THINGS THAT NEED A PERSON ◄◄◄◄

- **`RUN-SHEET-312` §2, both arms.** `LOW`, no build. **Same flat wall and same walk as `311` §2**,
  `D` from about `200` out to about `550`, four or five grabs each.
- **The commit**, this session's own paths only, explicit `git add --` path lists,
  `git commit -F`. **Do NOT use `COMMIT-NOW.cmd`** (`307` §5). **And leave the 57-file username
  scrub alone.**
- **`E3` (FC3/FC4) is CLOSED.** Do not re-ask.
- **THE `MODE=2` DEPTH-CONSTANCY CHECK IS STILL OWED** (`PRIORITY-BOARD-311` §E item 0e). **Put it
  in a sheet or it will not happen again.**

---

## ►►►► THE THING THIS SESSION SHOULD BE MOST CAREFUL ABOUT ◄◄◄◄

**`311` KILLED THE LAST CANDIDATE ON THE LIST AND DID NOT REPLACE IT WITH A NAMED ONE, AND THAT IS
THE HONEST POSITION.** "The horizontal NDC -> pixel response is short by `0.705`" is a
LOCATION — the same shape `310` §9's sentence had, and that sentence turned out to be false.
**`RUN-SHEET-312` §2.1's two candidate scales are `[HYPOTHESIS]`, they are NOT filed, and neither
names a line of code.** The reason they are written down at all is that they are **falsifiable in
five minutes and they disagree with each other**, which is the shape `RUN-SHEET-310` §4 used to
kill `B` and `C` in one sitting. **If both die, say so and write the next pair; do not curve-fit a
third from two data points.**

**AND ONE PROCESS DEFECT FROM `311` ITSELF, §7.2 — IT IS THE THIRD SESSION RUNNING WITH ONE, AND
THIS TIME IT IS THE ASSISTANT'S:** the `MODE=2` depth-constancy check was described **in chat and
never written into `RUN-SHEET-311`**, so all seven grabs landed at one spot and the check did not
happen. **That is `308` §0 exactly, pointed at the assistant instead of at a citation.** The
defence has not changed: **a block or a check that is written at the keyboard goes into the sheet
before the session ends, or it does not exist.**

**`169` NEXT ID = `U-26`.**
