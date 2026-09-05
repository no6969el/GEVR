# `312` — **THE `0.705` IS AN ASPECT TERM APPLIED TO EVERY 3D VERTEX, AND IT IS `gfx_pc.c:2362`**

> **OFFLINE ASSISTANT. NOTHING BUILT, STAGED, BRANCHED OR TAGGED BY THE ASSISTANT. THREE ARMS RUN
> BY THE OWNER ON THE MAIN PC**, binary unchanged (`EXPECTED-EXE-303.txt` verified by each arm's
> own preamble). **NOTHING IS PATCHED. The count of wrong filed fixes stays at FIVE.**
>
> **`RUN-SHEET-312` §2 IS WORN AND IT ANSWERED.** `[PREDICTION] 2d` DOES NOT FIRE: the factor is
> **NOT** geometry-independent. **`C1` IS DEAD** — it predicted the wrong DIRECTION on both arms.
> **`C2` HAS THE RIGHT DIRECTION AND IS OFF BY `+9.9%` / `-8.3%`**, which is `2e`, and `2e` says
> file a hole and do not curve-fit — **so the fit was not what located this. A source read was.**

---

## §0 — WHAT THIS SESSION ESTABLISHED, IN ONE TABLE

| | |
|---|---|
| **1** | **`311`'s WORK IS ALL IN AND NOTHING WAS OWED.** `[MEASURED, BRIDGE]` `GoldenEyeVR` HEAD **`ee87a5d`** (`docs(311b)`) over `7e5b746` (`docs(311)`) and `9cabee8` (`docs(311a)`); `goldeneye-native` HEAD **`5b741b3`**, `getv/tools` carrying only `309`'s two untracked scratch files. **`NEXT-SESSION-PROMPT-312` was written before `311b` landed and is one commit stale; the tree is not.** The username scrub is still 57 tracked files under `repo/docs` and still nobody's |
| **2** | **►►►►►►►► THE RATIO MOVES WITH THE WINDOW, AND IT MOVES A LOT.** `[MEASURED]` medians **`1.0987`** at `1600x1369` and **`0.3813`** at `2560x800`, against the control's **`0.7036`** at `2560x1369`. **`2d` DOES NOT FIRE. The factor is geometry-DEPENDENT and `GETV_WINDOW` reaches it** |
| **3** | **`C1` — an eye-width scale — IS DEAD, AND NOT NARROWLY.** It predicted `0.500` / `1.000`; the arms read `1.099` / `0.381`. **It has the direction backwards on both** |
| **4** | **`C2` — a width-derived scale — SURVIVES IN DIRECTION AND FAILS IN MAGNITUDE.** Predicted `1.0000` / `0.4167`, measured `1.0987` / `0.3813`: **`+9.9%` and `-8.3%`, both outside the ~2% error bar.** That is outcome `2e` |
| **5** | **►►►►►►►► AND THE ANSWER WAS NOT FITTED FROM THOSE TWO POINTS. IT WAS READ.** `[MEASURED, BRIDGE]` **`gfx_pc.c:2362`, `gfx_adjust_x_for_aspect_ratio()`, applied to EVERY 3D vertex at `gfx_pc.c:2476`:** `x * (ge_effective_native_width() / gfx_native_height) / (window width / window height)` — **with `GETV_WIDESCREEN=0` that is exactly `x * (4/3) / (W/H)`.** §2 |
| **6** | **►►►►►►►► THAT FACTOR IS `0.7130` AT THE MANDATED `2560x1369`. THE MEASURED CONTROL IS `0.7036`.** `[ARITHMETIC]` `(4/3) / (2560/1369) = 0.7130`. **`H19` HAS BEEN A `~0.705` SINCE `308` AND THIS IS A `0.713` SITTING IN ONE LINE OF THE BACKEND** |
| **7** | **►►►►►►►► AND IT ACCOUNTS FOR BOTH NEW ARMS, WHICH THE CONTROL ALONE COULD NOT DO.** `[ARITHMETIC]` `a = (4/3)/(W/H)` is **`1.1408`** at `1600x1369` and **`0.4167`** at `2560x800`. **Divide each arm by its own `a` and the three medians go from `1.0987` / `0.7036` / `0.3813` to `0.963` / `0.987` / `0.915`** |
| **8** | **►►►►►►►► THE CLEANEST NUMBER IN THE SESSION NEEDS NO PREDICTION AND NO DEPTH: THE `MODE=2` ARM READS `0.986` ONCE `a` IS IN.** `[ARITHMETIC]` under `MODE=2` the true NDC fraction is `s/tR = (128*0.5/1000)/0.684267 = 0.093531`, so the drawn shift must be `0.093531 * 912.667 * 0.7130 = 60.87 px`. **`[MEASURED]` `dx = -60` on all five `312` grabs and on all seven `311` grabs. `60 / 60.87 = 0.986`** |
| **9** | **►► AND A SECOND DEFECT, THE INSTRUMENT'S, WHICH `311` MIS-DIAGNOSED AS THE OWNER STANDING STILL.** `[MEASURED, BRIDGE]` in `run_311_mode2.log` **all seven grabs were scored against ONE `PREDICTION` line, 41,502 to 150,254 log lines earlier**; in `run_312_mode2depth.log` all five were scored against one line **58,637 lines earlier, taken in a different room.** `311` §7.2 said the identical `D` meant the owner did not walk. **The log says the owner walked from `D = 454` to `D = 2786` and the PRINT stopped.** `H22` is new. §3 |
| **10** | **THE `MODE=1` PAIRING IS SOUND BUT NOT FREE, AND IT IS NOW QUANTIFIED.** `[MEASURED]` the gap between the prediction used and the next one printed moves `D` by `0.0%`-`15.0%`, and **the two grabs with the largest drift are the two worst-corrected points on their arms** (`0.9196` at `10.3%`, `0.8330` at `15.0%`). **The residual after `a` is drift, not physics** |
| **11** | **GATE `2a` PASSES ON BOTH ARMS AND IT MATTERS: `tanR-tanL = 1.368534`, UNCHANGED.** `[MEASURED]` identical tangents `L=-0.684267 R=0.684267` on both windows. **`tanw` does not move with `GETV_WINDOW`** — so the movement in §0 item 2 is not the frustum |
| **12** | **`[PREDICTION] 2b` LANDS EXACTLY, ON THE BMPs AND IN THE BACKEND'S OWN LINE.** `[MEASURED]` the tool detects play areas `1600x900` and `1065x600`, and `[getv] VIEWPORT n64` prints `w=800`, `w=533.333`, `w=912.667` on the three arms. **The eye rectangle is right on every arm. The under-read is NOT in it** — `311` §6.4 extended to the backend |
| **13** | **NOTHING IS PATCHED AND NOTHING IS FILED AS A FIX. `RUN-SHEET-313` §2 PRE-REGISTERS TWO ARMS THAT KILL THIS IF IT IS WRONG**, one of which is a knob that already exists and needs no build |

---

## §1 — THE ENTRY STATE, MEASURED BEFORE ANY SENTENCE WAS WRITTEN ABOUT IT

`306` §0's standing rule, run first. `[MEASURED, BRIDGE]` 2026-09-04:

- `GoldenEyeVR` HEAD **`ee87a5d`** `docs(311b)`, over `7e5b746` `docs(311)` and `9cabee8` `docs(311a)`.
  **`311` left nothing owed.** `NEXT-SESSION-PROMPT-312` says "the second is `311`'s session commit —
  check whether it is in"; it is, **and so is a `311b` the prompt does not know about.**
- `git --no-optional-locks status --porcelain -- repo/docs` -> **57 modified tracked files**, the
  `<USER>` -> `<USER>` scrub, unchanged from `310` and `311`. **Not swept, not tidied.**
- `goldeneye-native` HEAD **`5b741b3`**, `-- getv/tools` -> the two untracked `309` scratch files
  and nothing else.

---

## §2 — **`RUN-SHEET-312` §2 IS WORN. THE RATIO TRACKS THE WINDOW.**

### 2.1 — THE THREE ARMS, EACH SCORED ON ITS OWN HALF

`RUN-SHEET-312` §0's table is confirmed by the BMPs and by the backend's own print, so the halves
the scorer was given are the right ones:

| arm | window | tool's play area | `[getv] VIEWPORT n64` `w=` | half used |
|---|---|---|---|---:|
| control (`311` §2 `sep64`) | `2560x1369` | `1824x1027` | **`912.667`** | `912.67` |
| **arm 1** | `1600x1369` | **`1600x900`** | **`800`** | `800.00` |
| **arm 2** | `2560x800` | **`1065x600`** | **`533.333`** | `533.33` |

**`[MEASURED]` the letterbox proves the scale rather than assuming it:** arm 1's play area is
`1600x900` — `320x180` at `ge_scale = 5.000`, width-limited, with `234` px bars top and bottom —
and arm 2's is `1065x600`, `320x180` at `3.3333`, height-limited, pillarboxed `747`/`748`.
**`[PREDICTION] 2b` lands on both.**

**`[MEASURED]` gate `2a` passes on both arms:** `separation=64.000 game units FULL`, `mode=1`, and
`tangents L=-0.684267 R=0.684267 ... tanR-tanL=1.368534` — **byte-identical to the control's.**
The window does not touch the frustum, which is what made this arm worth running.

| arm | grabs | median ratio | `C1` said | `C2` said |
|---|---:|---:|---:|---:|
| control `2560x1369` | 6 (`311` §2) | **`0.7036`** | `0.7012` | `0.7130` |
| **arm 1 `1600x1369`** | 5 | **`1.0987`** | **`0.5000`** | **`1.0000`** |
| **arm 2 `2560x800`** | 5 | **`0.3813`** | **`1.0000`** | **`0.4167`** |

**`C1` IS DEAD.** It said arm 1 halves and arm 2 goes clean; arm 1 went UP by 56% and arm 2 went
DOWN to 0.38. **It is wrong in direction, on both arms, by more than a factor of two.**

**`C2` IS NOT THE LAW EITHER.** Right direction on both, `+9.9%` on arm 1 and `-8.3%` on arm 2 —
`2e`. **`RUN-SHEET-312` §2.1 said to file that as a hole and NOT to curve-fit a third candidate
from two points, and this section obeys that.** What follows is not a fit.

### 2.2 — ►►►►►►►► **THE LINE**

`[MEASURED, BRIDGE]` `getv/port/fast3d/gfx_pc.c:2362`:

```c
static float gfx_adjust_x_for_aspect_ratio(float x) {
    return x * (ge_effective_native_width() / gfx_native_height)
             / ((float)gfx_current_dimensions.width / (float)gfx_current_dimensions.height);
}
```

and `gfx_pc.c:2476`, inside `gfx_sp_vertex()`, on **every 3D vertex the game draws**:

```c
        x = gfx_adjust_x_for_aspect_ratio(x);
```

**`[ARITHMETIC]` with `GETV_WIDESCREEN=0` — which every arm of `310`, `311` and `312` ran —
`ge_effective_native_width()` is `320` and `gfx_native_height` is `240`, so the factor is**

```
   a  =  (4/3) / (W/H)
```

| window | `a` | measured median | **median / `a`** |
|---|---:|---:|---:|
| `2560x1369` (control) | **`0.7130`** | `0.7036` | **`0.987`** |
| `1600x1369` (arm 1) | **`1.1408`** | `1.0987` | **`0.963`** |
| `2560x800` (arm 2) | **`0.4167`** | `0.3813` | **`0.915`** |

**THE `~0.705` THAT HAS BEEN THE SUBJECT OF FIVE SESSIONS IS `0.7130` AT THE MANDATED GEOMETRY, AND
IT IS THIS EXPRESSION.** It is applied AFTER the projection and INDEPENDENTLY of the eye viewport,
which is why `311` §6.4's chain read sound end to end and the number was still missing: **the eye
rectangle is correct, `vscale[0]` is correct, the N64 arithmetic is correct, and then every vertex's
`x` is multiplied by a ratio that has nothing to do with either eye.**

### 2.3 — THE PER-GRAB TABLE, AND THE RESIDUAL IS DRIFT

`[MEASURED]`, `a`-corrected, with the staleness of each grab's prediction beside it (§3):

| arm | frame | `D` | `D` drift to next print | ratio | **`/a`** |
|---|---:|---:|---:|---:|---:|
| arm 1 | `3849` | `301.19` | **`0.0%`** | `1.1432` | **`1.0021`** |
| arm 1 | `4086` | `418.55` | `2.9%` | `1.1299` | **`0.9904`** |
| arm 1 | `4244` | `472.89` | **`10.3%`** | `1.0491` | `0.9196` |
| arm 1 | `4422` | `602.81` | `4.6%` | `1.0957` | `0.9604` |
| arm 1 | `4594` | `696.71` | `4.9%` | `1.0987` | `0.9631` |
| arm 2 | `3414` | `142.55` | **`0.0%`** | `0.4058` | **`0.9739`** |
| arm 2 | `3683` | `226.45` | `6.2%` | `0.3813` | `0.9152` |
| arm 2 | `3908` | `320.70` | `6.3%` | `0.3986` | `0.9566` |
| arm 2 | `4135` | `376.38` | **`15.0%`** | `0.3471` | `0.8330` |
| arm 2 | `4421` | `474.71` | `1.7%` | `0.3807` | `0.9136` |

**THE TWO GRABS WHOSE PREDICTION IS FRESHEST READ `1.0021` AND `0.9739`. THE TWO WORST-CORRECTED
GRABS ARE THE TWO WITH THE STALEST PREDICTIONS.** The shortfall is in the same direction staleness
produces — the owner walks BACKWARD, `D` grows, the stale prediction is too LARGE, and the ratio
reads LOW. **This is a statement about `H22`, and `RUN-SHEET-313` §2 is designed so it cannot
matter at all.**

### 2.4 — AND THE ONE ARM WHERE NEITHER DEPTH NOR THE PREDICTION CAN GET IN

`[ARITHMETIC]` under `MODE=2` the frustum slides by `s = -(sep * 0.5) / 1000` in TANGENT units and
the drawn NDC fraction is `s/tR`, **with no `D` in it at all**:

```
   frac_true = (128 * 0.5 / 1000) / 0.684267 = 0.093531
   px_true   = 0.093531 * 912.667 * a(2560x1369)
             = 0.093531 * 912.667 * 0.7130
             = 60.87 px
```

**`[MEASURED]` `dx = -60`. On all five `312` grabs, and on all seven `311` §5 grabs.
`60 / 60.87 = 0.986`.** No prediction line is used, no depth is used, and the answer does not
depend on where the owner was standing. **THAT IS THE MEASUREMENT THIS FINDING RESTS ON.**

**AND IT KEEPS `A` RETRACTED, ON BETTER ARITHMETIC THAN `311` §6.1 HAD.** `311` divided the two
arms and got `0.7022 / 0.7075 = 0.992`; the `MODE=2` term in that division was a ratio against a
STALE prediction that happened to be taken near `D = 1000`, where the prediction is right by
construction. **Recomputed against the depth-free constant it is `0.7022 / 0.7029 = 0.999`.**
The conclusion does not move — **the separation is applied in full** — but the number it rested on
was luckier than `311` knew, and `00-STATE` §4 now says so.

---

## §3 — ►►►►►►►► **`H22` IS NEW: THE SCORER PAIRS A GRAB WITH A PREDICTION THAT CAN BE MINUTES OLD**

`RUN-SHEET-311` §1's scorer and `RUN-SHEET-312` §1's take **the last `PREDICTION` line before the
grab's `dlgrab` line.** Nothing checks how far before.

`[MEASURED, BRIDGE]` `run_312_mode2depth.log`, 272,043 lines: **eleven `PREDICTION` lines, the last
at line 86,277. The five grabs are at lines 144,914 to 246,631.** Every one was scored against that
same line — the nearest by **58,637 lines**, the furthest by **160,354** — and that line was taken
in `room 1` while the grabs were somewhere else.

`[MEASURED, BRIDGE]` `run_311_mode2.log`: **twenty-one `PREDICTION` lines, the last at 149,090; the
seven grabs at 190,592 to 299,344.** All seven scored against one line, **41,502 to 150,254 lines
stale**.

**►►►► SO `311` §7.2's DIAGNOSIS IS WRONG, AND IT IS WRONG IN THE ASSISTANT'S FAVOUR.** It read the
seven identical `D = 1005.73` values as *"the owner stood still"* and filed a PROCESS defect against
itself. **The owner did not stand still.** `[MEASURED]` `run_312_mode2depth.log`'s eleven prints
walk `D` across `454.67`, `465.02`, `732.42`, `1005.71`, `1205.70`, `1482.31`, `1879.85`, `1932.28`,
`1932.48`, `2378.65`, `2786.24`, through rooms 7, 8 and 1. **The instrument stopped printing and the
scorer did not notice.** The process defect was real and is still filed; **the CAUSE was an
instrument defect underneath it, and a sheet could not have fixed it.**

**WHY IT DOES NOT DAMAGE THE `MODE=1` RESULTS:** `[MEASURED]` those arms print 65 and 66 times,
spread through the run, and every grab's prediction is 140-983 log lines old — `8` to `56` rendered
frames. §2.3 quantifies what that is worth: `0.0%` to `15.0%` of `D`, and it moves the corrected
ratio by up to `0.09`. **It is a real error bar and it was invisible until this session.**

**`H22`, AS A HOLE:** *the disparity scorer pairs a grab with the last prediction printed before it
and cannot see how stale that is; on a `MODE=2` arm the prediction stops entirely and every grab in
the run is scored against one line from a different room.* **The durable fix is the tool's, not a
sheet's** — the prediction and the grab must carry a frame number and the scorer must refuse a pair
that is more than a few frames apart. **NOT DONE THIS SESSION. NOT FILED AS A FIX.**

---

## §4 — WHAT `H19` NOW SAYS

> **`H19` (RESTATED, `312`): the drawn image's horizontal response is short by
> `a = (4/3) / (window aspect)`, because `gfx_pc.c:2362`'s `gfx_adjust_x_for_aspect_ratio()`
> multiplies every 3D vertex's `x` by that ratio at `gfx_pc.c:2476`, on top of an eye viewport that
> is already correct. At the mandated `2560x1369` that factor is `0.7130`, and the measured
> under-read is `0.7036`. Corrected for it, three windows spanning `0.38` to `1.10` read
> `0.987` / `0.963` / `0.915`, and the depth-free `MODE=2` arm reads `0.986`.**

**IT IS A DIAGNOSIS AND IT IS NOT A PATCH.** `301` §0: the count of wrong FILED fixes is five, and
four of the five looked at least this good. **What separates this one from those is that it makes
three predictions that can kill it in five minutes with no build, and `RUN-SHEET-313` §2 carries
them:**

1. **`GETV_WIDESCREEN=1` at `2560x1369` makes the expression the IDENTITY by its own comment.**
   The ratio must go to `~1.00`. **If it does not, this is wrong.**
2. **A `4:3` window (`1600x1200`) makes `a = 1.0000` with widescreen still off.** The ratio must go
   to `~1.00`. **If it does not, this is wrong.**
3. **An aspect-PRESERVING resize (`1280x684`, the control's `1.870` at half the pixels) leaves `a`
   unchanged at `0.7130`.** The ratio must NOT move. **If it moves, the factor is not the aspect.**

**`1` and `2` disagree with `3` about what changes it, and all three run on the same wall in one
sitting.**

---

## §5 — WHAT THIS SESSION DID NOT DO

- **It did not patch `gfx_adjust_x_for_aspect_ratio()`.** The comment at `gfx_pc.c:410-423` says
  `GETV_WIDESCREEN=1` already makes it the identity, so **there may be nothing to patch at all —
  there may be a knob to set** — and `RUN-SHEET-313` §2 arm 1 is exactly that question. **`239`: a
  knob validated at one geometry is not a setting, and this whole session is what that costs.**
- **It did not fix `H22`.** The scorer's staleness is measured, not repaired.
- **It did not run `RUN-SHEET-312` §5**, the `H18` durable-form splice, which is still owed and is
  still `LOW`.
- **It did not touch the 57-file username scrub.**

## §6 — WHAT NEEDS A PERSON

- **`RUN-SHEET-313` §2, three arms.** `LOW`, no build, ~8 minutes, same flat wall.
- **`RUN-SHEET-312` §5**, the `H18` splice, `LOW`, offline, one paste.
- **The commit**, this session's own paths only, explicit `git add --` path lists, `git commit -F`.
  **Do NOT use `COMMIT-NOW.cmd`** (`307` §5).

## §7 — THE STANDING ONE

**`V3` / `258` STAGE 6 STILL CANNOT CLOSE.** `310` §9.1: a constant `0.705` lets the `+/-5 px` gate
pass only where `|predicted| <= 17` px. **If `RUN-SHEET-313` §2 confirms the aspect term, `V3`'s
gate becomes passable for the first time — either by setting `GETV_WIDESCREEN=1` or by folding `a`
into `geStereoPredict()`'s printed fraction — and that is the first time in eight sessions that
STAGE 6's exit gate has had a route through it.** **It is not confirmed yet.**
