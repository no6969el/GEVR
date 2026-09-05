Read `repo\docs\00-STATE.md` — the **currency line at the top** (it carries `310`'s full result,
`[MEASURED]`, and it was written from the repo, from the run's own log and from
`disp_310_S3d.txt` read back on the bridge, not from a paste), then **§4 RETRACTED — TWO new**
(the admissibility miss in `310`'s own sheet, and the death of candidates `B` and `C`), then
**§6 TRAPS**. Then **`310-THE-PROJECTION-AGREES-AND-H20-DIES` §0, §7, §8 and §9** — §0 is one
table, §7 is the flat-wall ladder and the error bar, §8 is how `B` died offline, §9 is the one
sentence that is left. Then **`RUN-SHEET-311`** — §0 is the gate, §2 is the first job. Then
**`PRIORITY-BOARD-310`** — still the current board; `309`'s and `308`'s are bannered.

Same rules as always. **You work OFFLINE. The build, every run and every commit are the owner's, on
the main PC. Supply complete copy-paste PowerShell blocks; quote a run-sheet block verbatim, never
paraphrase it. Never stage, commit, branch, merge or tag.** `git log`, `git show` and
`git diff <path>` are bridge-safe; `git status` needs `--no-optional-locks` **and a path list**.
**►►►► A PLACEHOLDER IS NOT A COMMAND: `<` is a RESERVED OPERATOR in PowerShell** (`00-STATE` §7a).
**►►►► INSTRUMENT OUTPUT IS ASCII (`H16`): the docs may carry arrows, the tools may not.**
**►►►► DO NOT EDIT A TRACKED SOURCE FILE WITH `Get-Content`/`-replace`/`Set-Content`** (`308` §1.1,
`00-STATE` §6). Hand the splice to `py` and do it in BYTES.
**►►►► A HOLE'S FILED FIX IS A DIAGNOSIS, NOT A PATCH — the count of wrong filed fixes is five
(`301` §0). MEASURE BEFORE YOU PATCH.** `310` is the case FOR that rule twice over: it named three
candidates, pre-registered what would kill each, and **two of them were dead within the day —
one of them without a run at all.**

---

## ►►►► THE FIRST COMMAND, AND IT IS NOT OPTIONAL ◄◄◄◄

**`310` SUPPLIED A COMMIT BLOCK AND THE SESSION ENDED WITHOUT SEEING IT RUN.** `306` §0 is the
standing rule and `310` §0 item 1 is the fourth session in a row where the opening claim about git
was wrong in one direction or the other.

```powershell
Set-Location F:\Projects\GEVR\GoldenEyeVR
git log --oneline -3
git --no-optional-locks status --porcelain -- repo/docs
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
git log --oneline -3
git --no-optional-locks status --porcelain -- getv/tools
```

**►►►►►►►► AND THE ANSWER WILL BE MESSY FOR A REASON THAT IS NOT THIS SESSION'S OR `310`'s: THE
DOCS TREE CARRIES A USERNAME SCRUB.** `[MEASURED]` `310` §0 item 2: **58 tracked files under
`repo/docs`, `182 insertions / 121 deletions`, every sampled hunk `C:\Users\<USER>\…` ->
`C:\Users\<USER>\…`.** It is nobody's session work. **`00-STATE.md` is one of the 58, so `310`'s
own edit and one scrub hunk sit in the same file and cannot be separated without staging hunks.**
- **If `310`'s docs commit is IN:** the scrub may be partly committed with it. Say which HEAD, and
  **check whether the other 57 are still dirty before writing any sentence about what is owed**
  (`305` §2a, `306` §0 — a claim that work is owed is a claim about git).
- **If it is NOT in:** the block is `310` §6 and the message file is
  `COMMIT-MESSAGE-2026-09-04e.txt`, written and correct. **Offer it; the commit is the owner's.**
- **Either way: the scrub is a SEPARATE change with a separate reason. Do not sweep it into a
  session commit, and do not "tidy" it.** `307` §5, sixteen strays.

`goldeneye-native` has **two untracked scratch files from `309`** — `getv/tools/_patch309.py`
(spent) and `getv/tools/ladder_driver.py` (**keep only as a deliberate decision — it re-runs the
`--patch` ladder**). Neither belongs in any commit.

---

## ►►►► WHERE THINGS ACTUALLY STAND ◄◄◄◄

**THE `S3b` UNDER-READ IS CORNERED IN EXACTLY ONE PLACE, AND THE BOARD HAS NEVER BEEN THIS CLOSE.**
`310` killed four candidates:

| candidate | how it died | where |
|---|---|---|
| the eye-width / pixel conversion | three independent ways — the log, `gfx_pc.c`'s own scale arithmetic, and the tool's detected play area | `309` §6.1, `310` §0 item 6, §8.1 |
| the frustum and its 4:3 term | **identity** — the renderer and the prediction are the same four floats — and `tR` **cancels** out of the ratio structurally | `310` §1, §2, §0 item 5 |
| **`C`** — a correlator biased on multi-depth scenes | **the flat wall IS single-depth and it still reads `0.705`** | `310` §7 |
| **`B`** — a short measured depth | `-dD / (camera displacement along look)` = median **`1.0053`** over 28 pairs; an additive offset would swing the ratio with depth and it is FLAT | `310` §8 |

**►►►►►►►► WHAT IS LEFT IS `A`, AND IT IS ONE SENTENCE: THE SEPARATION THAT REACHES THE DRAWN
IMAGE IS `~22.6` GAME UNITS, NOT THE `32` REQUESTED.** `[MEASURED]` of the SYSTEM. **It is NOT a
diagnosis of a line, nothing is filed, and nothing is patched.**

**AND THE INSTRUMENT NOW HAS AN ERROR BAR FOR THE FIRST TIME:** six admissible flat-wall grabs
across a 6.7-fold depth range read **`0.6921`-`0.7184`, mean `0.7051`, spread `0.026`** — most of
that spread being `dx` an integer. **The correlator is good to ~2%.** `0.750` and `0.6667` are
`0.045` and `0.038` from the mean and are therefore **both excluded by the data**, which agrees
with the algebra that excluded them first.

### ►►►►►►►► `V3` DOES NOT CLOSE, AND NOW WE KNOW WHY IN ARITHMETIC ◄◄◄◄◄◄◄◄

`[ARITHMETIC]` `310` §9.1: with a constant `0.705`, the `±5 px` gate can pass only where
**`|predicted| <= 17 px`** — which is exactly and only `S3b_5400`, the frame `309` §5.2 proved
unfalsifiable. **`V3` / `258` STAGE 6 CANNOT CLOSE UNTIL `A` IS FOUND. It is not a tuning problem,
no venue fixes it, and a sheet that claims to close it before `A` has a name is wrong on its face.**

---

## ►►►►►►►► THE FIRST JOB: `RUN-SHEET-311` §2. **EFFORT: `LOW`.** ◄◄◄◄◄◄◄◄

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
> | **1** | **`RUN-SHEET-311` §2 — the `32 / 64 / 128` separation sweep** | **`LOW`** | **three short runs at one spot, ~5 minutes total, no build** |
> | **2** | score it with §1's gated scorer and read the three medians | **`LOW`** | one paste |
> | **3** | **`RUN-SHEET-311` §3 — the `MODE=2` discriminator at `D ~= 1000`** | **`LOW`** | one short run, no build |
> | **4** | file the answer and update `H19` on the board | **`LOW`** | one commit block |
>
> **§2 IS FIRST BECAUSE IT IS THE ONE THAT CAN NAME THE CONSTANT.** `A` says the ratio is the SAME
> at every separation. **If the ratio MOVES with `sep`, it is not a scale factor at all — something
> adds, clamps or saturates — and that outranks every other item on the board.** The sweep also
> cuts the quantization error 4x at `sep 128`, which sharpens the constant itself.
>
> **§3 IS THE FALSIFIER AND IT IS CHEAP: `MODE=2` puts the shift in the PROJECTION and never
> touches the view matrix** (`stereo.c:284-295`, `:355-357`), **and it is tuned to agree with a
> real separation at `D = 1000`.** `~1.00` puts the loss in the VIEW path and confirms `A`;
> **`~0.705` puts it somewhere common to both paths and REOPENS what `310` §8.1 closed** — which
> would be the more important answer of the two.
>
> **DO NOT START GROUP `C` / `V7` (the per-eye contents instrument) — it is `HIGH` and it is
> `PRIORITY-BOARD-310` §E item 9.** **The instrumented print of the applied
> `|eye_pos - centre_pos|` is the obvious third step and it needs a BUILD, which makes it
> `MEDIUM`: do the two `LOW` runs first, because they may name the factor without one.**

---

## ►►►► THE THINGS THAT NEED A PERSON ◄◄◄◄

- **`RUN-SHEET-311` §2, then §3.** Both `LOW`, neither needs a build. Same flat wall as `310` §7
  for §2; a long sightline for §3.
- **The commit**, this session's own paths only, explicit `git add --` path lists,
  `git commit -F`. **Do NOT use `COMMIT-NOW.cmd`** (`307` §5). **And leave the username scrub
  alone.**
- **`E3` (FC3/FC4) is CLOSED.** Do not re-ask.

---

## ►►►► THE THING THIS SESSION SHOULD BE MOST CAREFUL ABOUT ◄◄◄◄

**`A` IS THE LAST CANDIDATE STANDING, AND THAT IS EXACTLY WHEN A WRONG FIX GETS FILED.** The count
is five. A last-remaining suspect feels like a conclusion and is not one: **`310` §9 states `A` as
a measurement of the SYSTEM — "the separation that reaches the image is `~22.6` units" — and
deliberately does NOT name a line of code, because the source read says the offset should be
exactly `±sep/2` along a unit right vector and the pose is identity** (`stereo.c:333-423`,
`bondview2.c:8958`, `posespine.c:76`). **The source and the image disagree, and until a run says
WHERE, "A owns it" is a location, not a mechanism.**

**AND ONE PROCESS DEFECT FROM `310` ITSELF, §7.2 — IT IS THE SECOND SESSION RUNNING WITH ONE:**
**`RUN-SHEET-310` §3 was written without carrying `RUN-SHEET-307` §2.0's admissibility gate
forward**, so a grab whose prediction the correlator could not express was scored rather than
refused, and its ratio was reported as "an outlier". **A number the instrument was never able to
give is not a data point, and calling it an outlier is a shrug with a statistic on it.**
**WHEN YOU WRITE A SCORING BLOCK, CARRY EVERY GATE ITS PREDECESSOR HAD — it costs one `grep` and
this one cost a wrong sentence in a results table.** `RUN-SHEET-311` §0 and §1 carry it.

**`169` NEXT ID = `U-26`.**
