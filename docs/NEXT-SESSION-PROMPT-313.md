Read `repo\docs\00-STATE.md` — the **currency line at the top** (it carries `312`'s full result,
`[MEASURED]`, written from the repo and from the three `disp_312_*.txt` files and the three
`run_312_*.log` files read back on the bridge, not from a paste), then **§3's opening block**, then
**§4 — TWO new, both `311`'s and both the assistant's own** — then **§6 TRAPS, the top two.** Then
**`312-THE-0705-IS-THE-ASPECT-TERM` §0, §2 and §3** — §0 is one table, §2 is the answer and its
arithmetic, §3 is `H22`. Then **`RUN-SHEET-313`** — §0 is the gate and the half moves AGAIN, §1 is
the scorer with the staleness column, §2 is the job. Then **`PRIORITY-BOARD-312`** — the current
board; `311`'s and `310`'s are bannered.

Same rules as always. **You work OFFLINE. The build, every run and every commit are the owner's, on
the main PC. Supply complete copy-paste PowerShell blocks; quote a run-sheet block verbatim, never
paraphrase it. Never stage, commit, branch, merge or tag.** `git log`, `git show` and
`git diff <path>` are bridge-safe; `git status` needs `--no-optional-locks` **and a path list**.
**►►►► A PLACEHOLDER IS NOT A COMMAND: `<` is a RESERVED OPERATOR in PowerShell** (`00-STATE` §7a).
**►►►► INSTRUMENT OUTPUT IS ASCII (`H16`): the docs may carry arrows, the tools may not.**
**►►►► DO NOT EDIT A TRACKED SOURCE FILE WITH `Get-Content`/`-replace`/`Set-Content`** (`308` §1.1,
`00-STATE` §6). Hand the splice to `py` and do it in BYTES.
**►►►► A HOLE'S FILED FIX IS A DIAGNOSIS, NOT A PATCH — the count of wrong filed fixes is five
(`301` §0). MEASURE BEFORE YOU PATCH.** `312` is the case FOR that rule and the case AGAINST
relaxing it in the same session: **`H19` is LOCATED, in one line, with three geometries and twelve
grabs behind it — and it is still not patched, because `RUN-SHEET-313` §2 can kill it in eight
minutes and four of the five wrong filed fixes looked this good.**

---

## ►►►► THE FIRST COMMAND, AND IT IS NOT OPTIONAL ◄◄◄◄

`306` §0 is the standing rule: **a claim that work is owed is a claim about git.** It has now been
right three sessions running, and in `312` it caught a PROMPT that was one commit stale.

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR
git log --oneline -3
git --no-optional-locks status --porcelain -- repo/docs
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
git log --oneline -3
git --no-optional-locks status --porcelain -- getv/tools
```

**►►►►►►►► AND THE ANSWER WILL BE MESSY FOR A REASON THAT IS STILL NOT ANY SESSION'S: THE DOCS
TREE CARRIES A USERNAME SCRUB.** `[MEASURED]` `312` §1: **57 tracked files under `repo/docs`**,
`C:\Users\<USER>\...` -> `C:\Users\<USER>\...`, unchanged since `310` measured 58. **The 57 are
nobody's session work. Do not sweep them into a commit and do not "tidy" them** (`307` §5, sixteen
strays).

- **`311` LEFT NOTHING OWED** and `312` measured that before writing a sentence about it:
  `GoldenEyeVR` HEAD **`ee87a5d`** (`docs(311b)`) over `7e5b746` and `9cabee8`.
- **`312`'s OWN COMMIT** — the block is `312-THE-0705-IS-THE-ASPECT-TERM` §6 and the message file
  is `COMMIT-MESSAGE-2026-09-05.txt`. **Check whether it is in before writing any sentence about
  what is owed** (`305` §2a, `306` §0).
- `goldeneye-native` has **two untracked scratch files from `309`** — `getv/tools/_patch309.py` and
  `getv/tools/ladder_driver.py`. Neither belongs in any commit. **If `RUN-SHEET-312` §5 has been
  run there will also be `_splice312.py`, which is scratch too** — the only tracked path that
  splice touches is `getv/tools/stereo_disparity.py`.

---

## ►►►► WHERE THINGS ACTUALLY STAND ◄◄◄◄

**`H19` IS NOT NARROWED ANY MORE. IT IS LOCATED, AND IT IS ONE LINE.**

`[MEASURED, BRIDGE]` `gfx_pc.c:2362`, called on every 3D vertex at `gfx_pc.c:2476`:

```c
    return x * (ge_effective_native_width() / gfx_native_height)
             / ((float)gfx_current_dimensions.width / (float)gfx_current_dimensions.height);
```

With `GETV_WIDESCREEN=0` — which every arm of `310`, `311` and `312` ran — that is
**`x * (4/3) / (W/H)`**, and it is applied AFTER the projection and OUTSIDE the eye viewport.

| window | `a = (4/3)/(W/H)` | `[MEASURED]` median ratio | **median / `a`** |
|---|---:|---:|---:|
| `1600x1369` | `1.1408` | `1.0987` | `0.963` |
| `2560x1369` (control) | **`0.7130`** | **`0.7036`** | `0.987` |
| `2560x800` | `0.4167` | `0.3813` | `0.915` |

**AND THE ONE THAT NEEDS NO PREDICTION AND NO DEPTH, WHICH IS THE ONE TO QUOTE:** `[ARITHMETIC]`
under `MODE=2` the drawn NDC fraction is `s/tR = (128*0.5/1000)/0.684267 = 0.093531`, so the shift
must be `0.093531 * 912.667 * 0.7130 = 60.87 px`. `[MEASURED]` **`dx = -60`, on all five `312`
grabs and all seven `311` grabs. `60/60.87 = 0.986`.**

**►►►► SIX CANDIDATES DIED TO GET HERE, ALL BY MEASUREMENT** — the eye-width conversion, the
frustum and its 4:3 term, the correlator, the measured depth, the applied separation, and now `C1`
and `C2` as written. **THE EYE RECTANGLE IS CONFIRMED FOUR WAYS** (the tool, the BMP letterbox,
`311` §6.4's source read, and the backend's own `[getv] VIEWPORT n64 ... w=` line reading
`912.667` / `800` / `533.333`). **`311` §6.4's chain was sound end to end and the number was still
missing, because the term is not in that chain at all** — `00-STATE` §6 carries that as a trap.

### ►►►►►►►► AND ONE THING `311` SAID THAT `312` HAD TO WALK BACK, AND IT IS AN INSTRUMENT ◄◄◄◄◄◄◄◄

**`H22`.** `[MEASURED, BRIDGE]` the scorer takes the last `PREDICTION` line before a grab and
nothing checks how far before. In `run_311_mode2.log` **all seven grabs were scored against ONE
line, `41,502`-`150,254` log lines earlier**; in `run_312_mode2depth.log` all five against one line
`58,637` lines earlier, **taken in a different room.** `311` §7.2 read the identical `D = 1005.73`
as *"the owner stood still"* and filed a process defect against itself. **The owner walked — that
log's own eleven prints run `D = 454.67` to `2786.24` through rooms 7, 8 and 1 — and the PRINT
stopped.** The process defect stands; **its cause was an instrument defect underneath it, and no
sheet discipline would have caught it.** On `MODE=1` arms the gap is `140`-`983` lines, still
`0.0%`-`15.0%` of `D`, **and `312` §2.3 shows the two stalest grabs are the two worst-corrected
points on their arms.**

---

## ►►►►►►►► THE FIRST JOB: `RUN-SHEET-313` §2. **EFFORT: `LOW`.** ◄◄◄◄◄◄◄◄

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
> | **1** | **`RUN-SHEET-313` §2 — three arms: `GETV_WIDESCREEN=1`, a `4:3` window, an aspect-preserving resize** | **`LOW`** | **three short runs on the same wall, ~8 minutes, no build** |
> | **2** | score all three with §1's `Score-Arm3` and read them against §2.1's `3b`/`3c`/`3d` | **`LOW`** | one paste |
> | **3** | file the answer, close or re-open `H19` on the board | **`LOW`** | one commit block |
> | **4** | **`RUN-SHEET-312` §5 — `H18`'s durable form**, if it has still not been run | **`LOW`** | one paste, no build. **AFTER the runs, never before** |
>
> **§2 IS FIRST BECAUSE TWO OF ITS THREE ARMS DISAGREE ABOUT WHAT MOVES THE RATIO.** `3b` (a `4:3`
> window, `a = 1.0000`) and `3d` (`GETV_WIDESCREEN=1`, the expression becomes the identity) both
> say the under-read VANISHES; **`3c` (`1280x684`, the control's aspect at half the pixels) says it
> must NOT MOVE AT ALL.** A factor that is not the aspect cannot satisfy all three.
>
> **►►►► AND THE ONE THING THAT WILL BITE IF IT IS MISSED: ARM 1's HALF IS NOT PREDICTED IN THE
> SHEET.** `GETV_WIDESCREEN=1` changes `ge_effective_native_width()`, so it changes `ge_scale()`,
> the play area AND the pillarbox together. **`RUN-SHEET-313` §0 says to READ the half off that
> arm's own `[getv] VIEWPORT n64` line and off the tool's `eye half`, and check the two agree
> before scoring it.** The `1280.00` in §2's scoring block is a plausible placeholder and it is
> flagged as one. The tool derives its own half and is unaffected either way.
>
> **DO NOT PATCH `gfx_adjust_x_for_aspect_ratio()` THIS SESSION, AND DO NOT PATCH
> `geStereoPredict()` EITHER.** If `3b` and `3c` both land, the fix is a DESIGN decision — a knob
> that already exists, or the prediction learning the term — and that is `HIGH`. **`00-STATE` §7c:
> a `HIGH` item does not start at the end of a session.**

---

## ►►►► THE THINGS THAT NEED A PERSON ◄◄◄◄

- **`RUN-SHEET-313` §2, three arms.** `LOW`, no build. **Same flat wall and same walk as `312` §2**,
  `D` from about `200` out to about `550`, four or five grabs each — **and STATIONARY at each grab,
  which is `H22`'s only defence until the tool carries one.**
- **`RUN-SHEET-312` §5**, the `H18` splice, if not yet run. `LOW`, offline.
- **The commit**, this session's own paths only, explicit `git add --` path lists,
  `git commit -F`. **Do NOT use `COMMIT-NOW.cmd`** (`307` §5). **And leave the 57-file username
  scrub alone.**
- **`E3` (FC3/FC4) is CLOSED.** Do not re-ask.

---

## ►►►► THE THING THIS SESSION SHOULD BE MOST CAREFUL ABOUT ◄◄◄◄

**`312` DID WHAT FIVE SESSIONS COULD NOT AND THAT IS EXACTLY WHY IT IS DANGEROUS.** A located line,
three geometries, twelve grabs and a `0.986` is the most convincing thing this project has produced
about `H19` — **and `301` §0 says four of the five wrong FILED fixes were convincing too.** The
defence has not changed and it is cheap: **`RUN-SHEET-313` §2 is eight minutes and it can falsify
the whole thing.** Run it before believing it.

**AND THE SECOND ONE, WHICH IS `H22`'s REAL LESSON: `312` FOUND ITS ANSWER IN A SOURCE READ THAT
OUTCOME `2e` SENT IT TO, NOT IN THE TWO DATA POINTS.** `RUN-SHEET-312` §2.1 said *"if both die, say
so and write the next pair; do not curve-fit a third from two points."* Both did die. **A third
candidate fitted to `1.0987` and `0.3813` would have been an exponent pair with no line of code
behind it, and it would have been wrong in the same way `310` §9's sentence was.** The rule earned
its keep in the only way a rule can: **by being obeyed when it was inconvenient.**

**`169` NEXT ID = `U-26`.**
