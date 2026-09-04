# 39 — the task board

**Live status, updated 2026-08-23 after `50` was built and measured.** The numbered docs are the
*record*; this is the *state*. If they disagree, a doc is right about what
happened and this is right about what is open.

**Rule: a row moves to DONE only when something was OBSERVED.**
**Second rule: verify the instrument before trusting a test.**
**Third rule, earned in `49`: five hypotheses were falsified in one session, each
plausible, each from reasoning about a mechanism instead of measuring it.**

---

## BLOCKING

> # ►►►► `126` IS THE PLAN. ROUTE B, LABELLED TASKS. RB-00 DONE, RB-01 NEXT. ◄◄◄◄
>
> **This board records STATE. `126` records the PLAN and its task states.
> Where they disagree, `126` wins for Route B tasks.**
>
> | # | | |
> |---|---|---|
> | **O107** | **THE VIEW PATH IS DONE AND IT WAS NOT ENOUGH** | `125`. R3 (`poseChg` 0 -> 91) and the previous-pose fix both landed and both were worn. *"Tighter, but still absolutely happening."* |
> | **O108** | **T7's EXONERATION OF INTERPOLATION IS VOID** | `125` §2. `rr_option "Original"` dropped submits to 60 into a 90 Hz panel, so the compositor repeated frames — doubling by a second mechanism. **The run proved nothing.** Rule 10 |
> | **O109** | **`dupSrc` 30/90, CONSTANT THROUGH EVERY BUILD TODAY** | Thirty frames a second are not real. Untouched by six fixes because none addressed it. **This is the Route B argument** |
> | **O110** | **`rt64_projection_processor.cpp:165` USED ONE POSE FOR CURRENT AND PREVIOUS VIEW** | **FIXED — `126` build.** Velocity and motion vectors saw zero camera motion from head rotation. Its own comment had named the fix and deferred it |
>

> # ►► CORRECTED 2026-08-24. THIS BLOCK IS THE CURRENT STATE. ◄◄
>
> **Everything below this block is older. Where they disagree, this wins.**
>
> **THE TWO SHIP BLOCKERS ARE UNCHANGED AND NOBODY HAS WORKED ON THEM:**
> **B3** (the machine bugchecks when a VR session closes, `0x139` arg1=3, costs
> a reboot per test) and **B4** (a tester will close with the X). **They outrank
> everything in the judder line and have done since `75`.** They are not being
> worked on because comfort was ranked above them by the owner in `92`; that is
> a decision, not an oversight, and it should be re-taken deliberately rather
> than by default.
>
> | **O99** | **R4 DONE — PERFECT DARK DOES NOT DO PER-PASS POSES, AND NEVER NEEDED TO** | **CLOSED, no machine.** One sim tick per XR frame, paced by `xrWaitFrame`, no interpolator. **P1 is re-framed as a workaround for our interpolator, not prior art to catch up to** | `117`,`114` §3.2 |
> | **O100** | **THE TIMEBASE DIFFERENCE IS ONE ACCUMULATOR** | **READ, NOT COSTED.** PD carries a remainder (`lvupdate240rem`) and exposes a float timestep (`lvupdate60f`) while keeping integer 60ths for legacy constants. GoldenEye's `updateFrameCounters` truncates. **`92`'s "90 is unreachable" is true of a truncating timebase and false of an accumulating one** | `117` §3 |
> | **O101** | **`99` §4's HEADLINE COST MAY BE AN OVERESTIMATE** | **OPEN.** It named the hundreds of "N sixtieths" duration constants as the main expense; **PD shows those do not change.** Re-cost from the four named `g_ClockTimer` comparisons plus an accumulator. **`117` §6.1 has the read, no machine** | `117` §4.2, `99` |
>
> | **O102** | **ROUTE B COSTED FROM THE TREE — IT IS A SLICE, NOT A PROJECT** | **READ DONE, NOT BUILT.** We already have BOTH halves of PD's design: `g_ClockTimer` (integer 60ths, 152 refs, 5 writes all in `lv.c`) and `g_GlobalTimerDelta` (float, **217 refs**, `lv.c:979`). **The only gap is the remainder accumulator.** `92`'s "structurally unavailable" is one integer divide at `frametiming.c:82`. **The unit never changes, so `99` §4's headline cost evaporates** | `118`,`117` |
> | **O103** | **T1-S0, THE TIMEBASE INSTRUMENT — BUILT, NOT RUN** | **`119`. No behaviour change, NOT gated on VR, short build.** **G-119-1: at `-NoXr` 90, PREDICT delta/clk/gdelta all FLAT with min==max. NOT FLAT kills `118` before it is built.** Statics keyed on a **magic sentinel**, not zero — `100`'s trap, first reusable answer to it | `119`,`118`,`100` |
> | **O104** | **`92`'s AIM-FEEL OBJECTION TO ROUTE B IS DEFUSED** | **It becomes a CHOICE.** Leave `crosshair_x_pos` on the integer tick and weapon feel is bit-identical to today; move it to the float only if smooth aim is wanted. `92` treated it as a forced consequence | `118` §4 |
> | **O105** | **THE WHOLE FIRST ROUTE-B SLICE IS TESTABLE AT `-NoXr`** | **THE DE-RISKER.** No headset, no B3 reboot risk, no wearer time. **Nothing else in this project has had this property** | `118` §5 |
> | **O98** | **NEW STRUCT MEMBERS MOVED TO THE END OF `SharedQueueResources`** | **DONE — `120` §2.** Second layer behind `build.ps1`'s header guard: a stale object now degrades to "new field reads garbage" instead of "whole struct misaligned" | `120`,`115` |
> | **O106** | **`commit-session.ps1` WOULD HAVE LOST TODAY'S WORK** | **FIXED — `120` §1.** It staged a hardcoded file list from the `86`-`96` era and committed under a hardcoded message. **Three existing commits already carry the identical subject line.** Now `git add -A`, mandatory `-Message`, lock clearing, and a clean-tree check after | `120` |
>
> ## THE JUDDER LINE, `103` THROUGH `117`
>
> | # | Task | State | Doc |
> |---|---|---|---|
> | **O93** | **THE STALL IS FIXED AND THE JUDDER IS NOT** | **MEASURED AND WORN.** 60 fps / 90 submits / `interpUsed=90` under `-EyeInterp`, against 16 fps / 13 submits in `103`-`105`. **`dupSrc=30/90` — one submission in three still repeats, unchanged from before `103`. The wearer felt no difference** | `113`,`111`,`107` |
> | **O94** | **THREE FACTS THAT DO NOT RECONCILE — THE LIVE QUESTION** | **OPEN.** `eye0=90` rendered, `interpUsed=90` consumed, `dupSrc=30/90` repeat. **NO MECHANISM PROPOSED ON PURPOSE — `106` §2.** Next: log the `(set, pass)` pair every present consumes for one second. ~10 lines, no headset. **Each outcome names a different file** | `113` §4.1 |
> | **O95** | **`dupSrc` IS BLIND WHERE BUFFERS ARE REUSED IN PLACE** | **KNOWN LIMIT, CORRECTED IN `112`.** Knob-off reads `90/90` on a build that is not duplicating, because the same two `RenderTarget` objects are rewritten every frame. **Knob-off readings are VOID; only knob-on is informative** | `113` §2 |
> | **O96** | **`ds_option 2` — THE ONE SHIPPABLE WIN OF THE DAY** | **CONFIRMED FREE AND EFFECTIVE.** 60 fps, 90 eye passes, LATE 12% (better than baseline's 17%). Kills the distant shimmer (`108` §3). **RECOMMEND AS DEFAULT.** `msaa_option` stays `"None"` | `111` §4, `108` |

>
> | # | Task | State | Doc |
> |---|---|---|---|
> | **O81** | **ROUTE D — PUBLISH THE INTERPOLATED EYE PASSES.** RT64 renders 90 eye passes/s and publishes 60; `rt64_workload_queue.cpp` gated the publish on `frame == 0`. **`submits=90 renders=60 reused=30` is a publish guard, not a GPU limit** | **THREE ATTEMPTS, THREE STALLS: 16.3 / 25.7 / 16.3 fps against 60.** `reused` goes to 0 in all three — the mechanism is real — but `submits` collapses to 13/s and `xrWaitFrame` goes 9 ms -> 75 ms | `103`,`104`,`105`,`106` |
> | **O82** | **`105`'s DOUBLE BUFFER WAS NEVER A DOUBLE BUFFER — `107` §2** | **FIXED, NOT COMPILED, NOT WORN.** The set stride was `displayFrames * 2`, and `displayFrames` alternates 1/2 at 60 into 90, so set 1's base moved onto set 0's targets on every other workload. **Fixed stride, costs nothing — `RenderTarget`'s constructor allocates no GPU memory.** `GE_VR_EYE_INTERP=0` still an exact identity | `107`,`105` |
> | **O83** | **`105`'s RESULT IS VOID, AND `106` §2 RESTS ON IT** | **`48` rule 4.** "Option A did not move the number, therefore the handover is not the cause" is not evidence, because the dependency was never removed. **`106` §2's "the handover is not the problem" is UNSUPPORTED until G-107-2 runs** | `107` |
> | **O84** | **`106` §6 MOVE 2 IS DONE AND ITS SUSPECT IS ELIMINATED — `107` §1** | **CLOSED, no launch.** The resolve and downsample are genuine no-ops (MSAA off, `ds_option 1`); the descriptor set rebuilds only on a SAMPLER change; `setSRV` and the heap copy run unconditionally every present. **Nothing in the sampling path is conditional on `params.texture` having changed** | `107` |
> | **O85** | **`106` §6 MOVE 1 IS STILL OWED AFTER FOUR ATTEMPTS.** Change ONLY the sampled-texture variable | **`56`'s method, still unapplied. O84 makes it MORE worth running, not less** — it now has no candidate mechanism, so a stall would be genuinely surprising and a clean pass closes the question | `106`,`56` |
> | **O74** | **THE PACING INSTRUMENT — `max` AND A LATE-COUNT beside `72`'s means** | **BUILT — `109`. NOT COMPILED, NOT WORN.** Four maxima plus a late count against the runtime's OWN display period, printed beside `72`'s means because the comparison is the instrument. `LATE` prints `n/a` not `0` when the period is unknown. **Pure diagnostic, short build.** `107` §3 says where the follow-on probes go | `109`,`107`,`73`,`72` |
> | **O85** | **`106` §6 MOVE 1 — CHANGE ONLY THE SAMPLED-TEXTURE VARIABLE** | **BUILT — `110`. NOT COMPILED, NOT WORN.** `-EyeSampleTest`: pass 0, a REAL frame, alternating between the two sets on consecutive presents. No extra passes, nothing extra rendered. Alternates on the PRESENT ORDINAL, not `i` — using `i` would do nothing on a `displayFrames == 1` workload, which is what broke `105`. **PREDICTION, written before the run: it does NOT stall** (`107` §1 found no mechanism). A stall would be the most interesting result in the sequence | `110`,`106`,`107`,`56` |
> | **O86** | **THE PRESENT THREAD'S STRUCTURE, WRITTEN DOWN AT LAST — `107` §3** | **`submitFrame()` RUNS ON RT64's PRESENT THREAD.** And `workloadGraphicsWorker` / `presentGraphicsWorker` are **two independent `ID3D12CommandQueue`s with NO cross-queue GPU synchronisation anywhere** — they share only the CPU-side `interpolatedMutex`. `D3D12Texture::resourceStates` is a plain non-atomic member mutated from both | `107` |
> | **O87** | **A NAMED HAZARD, NOT A GUARD — rule 13.** With the interp knob on, a failed pass lookup falls back to the legacy `vrEyeZeroTarget`/`vrEyeOneTarget` pair, which points into **the set being written right now** | **NO GUARD BUILT. The instrument already exists:** `interpUsed` below `submits`/3 means it fired. `42` is why a guard was not added | `107`,`103` |
> | **O88** | **LAST NIGHT'S TESTING — RECOVERED AND WRITTEN UP** | **CLOSED — `108`.** Reconstructed from the owner's transcript of a session that hit a budget limit. Two results were nearly lost, and one of them falsifies a line written the next morning | `108` |
> | **`106` §7.2** | **THE GUARD WALK WAS RUN, KNOB OFF: *"The characters are ok."*** | **CLOSED — `108` §1. THE DEFAULT BUILD IS CLEAN.** The misplacement is OURS, fires only under `GE_VR_EYE_INTERP=1`, and lives in the eye target MODIFIER change `104`/`105` made. **`107` §2 is likely its cause; G-107-2 tests both at once** | `108`,`106` |
> | **O90** | **NO ANTIALIASING AT ALL UNDER VR — A NAMED, SEPARATE FAULT.** Not judder, not stereo | **CAUSE KNOWN, LEVER CONFIRMED, COST UNMEASURED.** MSAA is forced off by `43`, so supersampling is the only AA available. `ds_option 2`, worn: *"It just smooths out the distance."* **The shimmer WAS aliasing** | `108` §2.2, §3 |
> | **O89** | **READ THE FPS LINE AT `ds_option 2`, AND TRY `4`** | **OPEN.** The AA lever was judged by FEEL — the bridge dropped before the log could be read. **`49`'s O22 (8x fewer pixels ran 4x SLOWER) lives in exactly this territory; if `4` is slower than `2` that is O22 reproducing on demand** | `108` §3.1, `49` |
> | **O91** | **`interpolation.c`'s transient-draw flicker** — a short-lived draw has no previous-frame partner, so RT64 drops it on in-between frames, *"reads as flicker rather than ghosting"* | **OPEN.** The other half of the head-glitch report, and **NOT fixed by supersampling**. `23`'s family | `108` §2.2 |
> | **O92** | **`ds_option` IS `2` ON DISK AND EVERY `103`-`106` NUMBER WAS TAKEN AT `1`** | **CONFOUND, ACTIVE.** `107` §1's downsample elimination was FALSE for this reason and is corrected at source. **Pin `ds_option 1` for G-107-2's like-for-like run** (`graphics.json.bak-preDS2`), and re-check after any in-game menu visit — the menu rewrites the file | `108` §4, `48` item E, `43` |
>
> ## THE JUDDER FINDINGS THAT SURVIVE
>
> **`106` §3 IS RETRACTED BY ITS OWN §7.** Interpolated frames are NOT visually
> wrong: `-NoXr` presents the same frames at 90 on the monitor and characters
> are correct. **Route D is a sound goal, `23` is back to promoted-not-
> prerequisite, and the character misplacement seen on the `105` build is OURS,
> in the eye-target modifier change.** One knob-OFF launch and a guard walk
> settles which — `106` §7.2, and it batches with G-107-4.
>
> **`105` §3 SURVIVES AND IS THE MOST USEFUL THING IN IT.** Not the GPU (work
> down, time up). Not the CPU (`record 0.02 ms`, `waitForGpu 0.00`, 9950X3D on
> the V-cache die).
>
> **`97`'s TIMEWARP IS RETIRED BY OWNER DECISION AND STAYS RETIRED** — *"I want a
> pure smooth experience, not an emulator type feel."* `-Timewarp` /
> `-TimewarpYaw` remain as diagnostics only. **Do not relitigate.**
>
> **AND THE ONE FACT THAT SURVIVES EVERY DESCRIPTION:** stick turn is clean,
> head turn is not, at comparable angular speeds. **Route D addresses the STICK
> half only** — `104` §2 — and is a prerequisite for the head half rather than a
> fix for it.
>
> ## PROCESS CHANGE, 2026-08-24, OWNER DECISION
>
> **Rules 5 and 11 are no longer standing rules; they are invoked by request.**
> Numbers kept and not reused — eighteen citations across fourteen documents.
> `00-START-HERE`'s rules section carries the full note. **A reader of THIS BOARD
> can no longer assume DONE means worn**, so every row above says which it means
> in its own words.
>
> ## STILL OWED FROM THE FLOOR
>
> **O73 — COMMIT BOTH REPOS. NOW FAILED FOUR SESSIONS.** `48` says run git from a
> shell that can delete, which is Windows and not the Linux bridge. **This
> session edited `rt64_workload_queue.cpp` and wrote `107`, so the debt grew.**
>
> ---
>

> # ►► CORRECTED 2026-08-23, END OF THE READS SESSION. THIS BLOCK IS THE CURRENT STATE. ◄◄
>
> **Everything below this block is older. Where they disagree, this wins.**
>
> ## WHAT CHANGED THIS SESSION: NOTHING WAS WORN, AND THAT IS THE POINT
>
> **`86` §8 owed six reads before any 6DoF code. They are all done — plus five
> more the doing of them opened. `87`, `88`, `89`, `90`. Then slice S0 was
> written — `91`. No launches, no builds, no headset, no bugchecks.**
>
> ## AND THEN THE PRIORITY CHANGED: COMFORT OUTRANKS FEATURES — `92`
>
> **`90 Hz` is structurally unavailable: the sim quantum is an integer 1/60 s
> tick. The sim is ALREADY holding 60 (142 of 149 samples), so `73`'s VI-clock
> halving is real but RARE and cannot be a constant judder.** New favourites:
> the **2:3 cadence** and **partial interpolation**. **O74, O75, O76 below, and
> `23` is promoted.** **`86`'s slices continue AFTER the judder has an answer** —
> a slice built into a build that makes the wearer sick cannot be judged by the
> wearer, and the wearer is this project's best instrument.
>
> | # | Task | State | Doc |
> |---|---|---|---|
> | **O68** | **THE READS `86` §8 OWED — ALL ELEVEN.** Six asked for, five more opened by doing them | **DONE. Reads only, no code.** `87` (1-6), `88` (7, 8, and `86` A1's owed read 1), `89` (9, 10, 11 and the stats-table trap) | `87`,`88`,`89` |
> | **O69** | **SLICE S0, THE 6DoF INSTRUMENT. WRITTEN.** Two halves: host (`rt64_render_context.cpp`) and game (inside the already-patched `viSetFovY`). **NO new `RECOMP_PATCH` name — short build** | **NOT COMPILED, NOT WORN. Rule 11.** Build with `.\build.ps1`, then wear. **Six gates, two of which are falsifiers that decide other slices** | `91`,`86` |
> | **O70** | **THE TWO FALSIFIERS S0 CARRIES.** `muzzleExt` **must be > 0**; `A40` **must be < 0** | **UNRESOLVED AND CONSEQUENTIAL.** If either fails, `88` §5.1's aim-axis reasoning inverts and **slices G2 and A1 both change shape.** Neither is answerable from the tree — the weapon stats are ROM data | `90`,`91`,`88` |
> | **O64** | **A WORLD-SPACE AIM DOT — PROMOTED. NO LONGER OPTIONAL** | **`90`: `crosshair_angle` IS the bullet and it is CLAMPED, so there is NO unclamped shot path in GoldenEye.** Past the clamp the gun model points where you aimed while the bullet does not follow — **the gun becomes an actively misleading indicator, and a world dot is the only honest one** | `90`,`86` |
> | **O71** | **H2 OPTION B IS TWO WRITES, NOT ONE** | `eyeheight` (or `headpos.f[1]`) buys the view and the ceiling; **the AI reads the CROUCH STATE** (`chrprop.c:1413`), so `crouchpos` must be written too or gate G-H2-3 cannot pass. **`87`'s "smaller than it looked" was half right** | `89` |
> | **O72** | **`eyeheight` IS ABSENT FROM `patches/structs.h`** | Blocks H2 option B's patch. **S0 says so in its own log line** rather than omitting it, because a missing field looks exactly like a field reading zero | `91`,`89` |
> | **O80** | **►► `96` IS THE JUDDER PLAN. START THERE. ◄◄ COMFORT BLOCKS `86`.** | **Phase 0 free (close one eye / stop mid-turn / mirror), Phase 1 = O79, Phase 2 = the build already written, Phase 3 = a DECISION TABLE, nothing pre-committed** | `96` |
> | **O79** | **DOES PIMAX OPENXR 0.1.0 REPROJECT AT ALL?** Unchecked, and it could decide the whole thing | **A READ and a settings check, not an experiment. The FIX CHANGES depending on the answer** — if nothing acts on the pose label, labelling it honestly buys little and the answer is to reduce staleness instead | `95`,`94` |
> | **THE FINDING** | **STICK TURN IS CLEAN, HEAD TURN IS NOT — at comparable angular speeds** | **The one thing that survives dropping every adjective. It localises the fault to the HEAD POSE PATH.** Arrived unprompted, which is why it is worth more than the first description | `95` |
> | **O78** | **TEST `93` BEFORE ACTING ON IT — `94`.** The owner stopped a route change made on the strength of three sentences of description | **T1 the mirror recording (NO CODE, NO BUILD — `47`'s method, decisive between image fault and pose fault). T2/T3 the numbers. T4 `GE_VR_POSE_LAG=N` — `56`'s method, and NO CHANGE AT N=4 KILLS `93` whatever anybody felt.** Also unchecked: **does the Pimax runtime reproject anyway?** | `94`,`47`,`56` |
> | **O77** | **A POSE/IMAGE MISMATCH — CANDIDATE 4, NOT A CONCLUSION. `93`, corrected by `94`.** We submit whatever RT64 last rendered with **this present tick's fresh pose** (`ge_vr_xr.cpp:1258` / `:1518` / `:1533`). **That tells the compositor no reprojection is needed, so it applies none** — and ~1 submission in 3 reuses an unchanged image at a NEWER pose | **INSTRUMENT FIRST: G93-1** (angular difference rendered-vs-submitted; **PREDICT non-zero, growing with head speed**) and **G93-2** (reused-image count; **PREDICT ~1 in 3**). **Then carry the render pose through to the submit** — rule 8, one pose not two. **No-code falsifier: `47`'s mirror recording** | `93`,`47`,`28` |
> | **O74** | **THE PACING INSTRUMENT — `max` AND A LATE-COUNT beside `72`'s means** | **`73` asked for it and it has been outstanding since. TWO LINES.** `72` exonerated the submit loop on MEANS, and a mean cannot see a hitch — **so it is cleared of being SLOW and not of being IRREGULAR.** Do it WITH S0: diagnostics batch freely | `92`,`73`,`72` |
> | **O75** | **THE THREE WEARER QUESTIONS — one launch, no code** | **(1)** stand still at a wall: judder? **(2)** turn your head: does the GUN step against a smooth world, or together? **(3)** constant or worse when busy? **They separate all three judder candidates and cost nothing** | `92` |
> | **O76** | **90 Hz IS STRUCTURALLY UNAVAILABLE, and that is now understood rather than assumed** | **The sim quantum is an INTEGER 1/60 s tick** (`frametiming.c:75`). 60/30/20/15 only. **Route A — keep 60, fix the interpolation — is the only route compatible with `86`**, because changing the quantum changes the aim feel of every weapon | `92` |
> | **`23`** | **PROMOTED, DEMOTED, AND NOW BACK TO OPEN AND UNRANKED — `94`.** "Explosion effects stick to the view when turning" | `92` promoted it on one theory, `93` demoted it on another, **neither time from a number.** **It is a known real defect either way.** Leave it ranked when something measures it | `94`,`93`,`92`,`23` |
> | **O73** | **THE FLOOR'S ITEM 1 — COMMIT BOTH REPOS — IS OWED AND WAS NOT DONE** | **NOT skipped: this session drives the machine through the Linux bridge, and `48` says run git on WINDOWS.** `git status` over the mount TIMED OUT. **No stale `.lock` files exist** (checked), so it is not the `48` lock fault. **The next session must commit before anything else** | `48` |
>
> ## RETRACTED THIS SESSION — rule 10, and two of them were mine
>
> | Claim | Was | Now |
> |---|---|---|
> | *"`field_FFC` is `crosspos2`/`bgunSetAimPos`, exactly"* | `86` §3.8 | **FALSE.** `field_FFC` never reaches a bullet — it points the gun model and the muzzle flash | `90` |
> | *"`gun_azimuth_angle` drives the BULLET"* | **`87`**, mine | **FALSE.** `crosshair_x_pos` does. The two-integrator finding survives; the labels swapped | `90` |
> | *"A1 and G1-G3 collide over `field_FFC`"* | **`87`**, mine | **Overstated.** `gunfire.c:568` aims the gun at the aim point **by design** — it is the coupling A1 wanted | `88` |
> | *"47 unique patch names across 48 sites"* | **`87`**, mine | **45 across 46.** The regex matched **comment prose about `RECOMP_PATCH` naming** — an instrument counting itself | `91` |
> | *"the near plane is ~10 units"* | `83` | **Under the VR gate `znear` is clamped to 2.0**, so slice G3's trim range is wider | `87` |
>
> ---
>
> ## CORRECTED 2026-08-23, LATE. READ THIS BEFORE THE TABLE BELOW.
>
> **The table below is the state as of `50`, and B1 is no longer true.**
>
> | | Now | Doc |
> |---|---|---|
> | **B1 — the eyes will not fuse** | **DONE. FIXED, MEASURED AND WORN.** Root cause: the two present draws bound the SAME descriptor heap slot in one command list; D3D12 reads heaps at EXECUTION time, so both halves sampled eye 1's texture. Fix: per-eye descriptor sets in `VIRenderer`, both the SBS and XR paths. Gate required -113 px ±5, **measured -117 px** at corr 0.9768; `mean\|L-R\|` 0.0006 -> 16.52. **Worn: depth present, images fuse, ONE gun.** Commit `825ab8a` | `69`,`70`,`71` |
> | **B2 — worn, dark stale frame** | **Worked around, not fixed.** `-Sbs` is the default and the headset is live and correct; `-NoSbs` reproduces the freeze on demand | `65` |
>
> **Everything B1 blocked is now judgeable for the first time** — O2, O8, O20 in
> the table below all said "not judgeable until B1".
>
> **New, and both are consequences of the fix rather than of the bug:**
>
> | # | Task | State | Doc |
> |---|---|---|---|
> | **O53** | **SCALE IS WRONG.** "My arms and my perspective are comically large." `16`'s units/metre derivation, never measured, now looked at through working stereo. **Two separable faults: world scale, and the viewmodel's ratio to the world — no units/metre value can fix a ratio** | **The sweep, worn, no code: `-UnitsPerMetre 150 / 200 / 50`, read `eye sep` at each, settle it with `16`'s doorway test. RECORD EVERY VALUE, not just the winner** (`MODS-IDEAS`) | `71`,`16` |
> | **O54** | **JUDDER.** `26` predicted it; `00` carried "it has not appeared" and that is now false | **The submit loop is EXONERATED — `72`. 516 samples, one over budget, ~87% of every frame blocked in `xrWaitFrame`. But those are MEANS and a mean cannot see a hitch.** Next: `max` + late-count beside the mean, two lines | `72`,`71` |
> | **O55** | **`EYETGT: *** DIVERGED ***` prints for essentially the whole of a worn session in which stereo WORKED.** `65` built that line as a whole hypothesis | A red banner on a healthy session is the next thing to mislead somebody. Not diagnosed | `72`,`65` |
> | **O56** | **The `sameSlot` instrument `70` asked to ship WITH the fix was not built.** The fix landed; the probe that would catch its regression did not | Two lines in the present path. Nothing currently detects a return of B1 | `70` |
> | **O57** | **`-NoXr` regression check after the B1 fix** | **DONE — PASS, OBSERVED. `73`.** A level was played, 123 s, clean teardown, no crash, no error. `eye1=0` under `-NoXr` is the correct reading. **`50`'s and `61`'s menu-only scoring was NOT repeated** | `73`,`71` |
> | **O58** | **The GAME's VI clock halves to 30 in heavy scenes while the renderer holds 90** — measured under `-NoXr`, so it is not the VR path. **The interpolator's input rate is 30, not 60, exactly when judder is reported** | **A candidate for O54 that predicts WHEN it judders.** Falsifier, no code: if it judders equally when standing still doing nothing, this is wrong | `73` |
> | **B4** | **THE GAME MUST CLOSE GRACEFULLY. A tester closes with the X.** The force-kill is a session workaround for the people who know about it — it is not a shippable exit, and B3 means the normal one takes the machine down | **This is the ship-blocking half of B3.** O21 is the fix: honour the fence wait's result, and make `teardown: present thread drained` true or delete it (`64`) | `75`,`64` |
> | **B3** | **THE MACHINE BUGCHECKS WHEN A VR SESSION CLOSES.** `0x139` arg1=3, five times, never under `-NoXr`. Two of three XR logs stop mid-line with no teardown output at all | **BLOCKING, and it costs the user a reboot per test.** Workaround NOW: kill the process, never the X. That is also the experiment — a force-kill runs none of our shutdown code. Then fix **O21** | `75`,`64` |
> | **ACTIVE** | **SLICE 2 — the gun follows the hand. BUILT, WORN, NOT WORKING.** Three corrections in one session, all diagnosed by the wearer: rotation-only is not "free"; the composition was a MIRROR not a rotation; and the engine's own turn-sway was still rotating the gun underneath the hand | **`GE_VR_HAND_ABSOLUTE` defaults OFF — the shipped default is the delta path, which tracks but pulls. NEITHER IS VALIDATED.** Next: `81`, then the `-HandAbsolute` "far away" bug (suspect: `R0` captured from the wrong hand model) | `79`,`81` |
> | **O67** | **THE SEAM WORKS — `85`. CONFIRMED WORN: *"it moves where my hand goes when in front of me"*.** Position tracks left, right and depth; solid, single, stable. Two faults killed by measurement: a **feedback loop** (the delta was measured against the rendered position, which already held last frame's delta) and an **inverted Z** that is correctly opposite the render path's | **UNTESTED: the hand at the side, low, or behind the shoulder — the qualifier was deliberate.** Then drop `-SeamNoRot` and sweep `-HandAxisX/Y/Z` one at a time.** Then slice 3, the bullet. `.\vr.ps1 -UnitsPerMetre 50 -SeamNoRot -HandPosZ 1` | `85` |
> | **O66** | **THE SEAM IS BUILT AND FIRES — `84`.** `gunSetHorizontalOffset` is patched, writes `field_92C`/`field_8EC`, and **the gun moves**: those fields ARE GoldenEye's hand override, observed not argued. But the placement is wrong — two guns, one on the floor, one ghosting over the shoulder | **Three faults, not one** (interpolation pairing, the `gunofs` space, and a rotation that pre-multiplies about the model's own origin). **Open with the known-constant experiment in `84`** | `84`,`83` |
> | **O65** | **THE SEAM AND THE HOOK ARE FOUND — `83`.** `field_92C`/`field_8EC` are the engine's own hand override (= PD's `useposrot`/`posrotmtx`), and `gunSetHorizontalOffset` (`gun.c:1230`, ten lines) is the one patchable function between the tick's clear and the placement's read | **Owed before it compiles: two externs and the `WeaponStats` struct, which is not in `patches/structs.h`.** Bounded. This is where the hand work belongs | `83`,`82` |
> | **O63** | **PRIOR ART FOUND, AND IT IS MIT.** Perfect Dark — the SAME ENGINE — has a shipping PCVR + Quest port with motion-control aiming (`Alex-LeTux/perfect_dark_VR`). MIT means it may influence **anywhere**, including the upstreamable half | **Read before designing slice 3.** VR code may not be in the public tree yet — **so play the released build; it runs on this rig** | `81` |
> | **O64** | **A WORLD-SPACE AIM DOT.** Asked for directly: *"aim where I'm aiming the gun, and have a dot or crosshair in the distance"* | **Not decoration.** `38`'s clamp means the gun and the bullet WILL disagree past ~±30°, and a dot on the fired ray is the only honest way to show where the shot goes | `79`,`61`,`38` |
> | **SLICE 1** | **THE VIEWMODEL'S SIZE AND DISTANCE — BUILT AND PASSED ITS GATES.** `-ViewmodelScale` / `-ViewmodelPush`, identity by default. Patched on `bondviewTransformManyPosToViewMatrix`, identified by POINTER IDENTITY against the player's own hand models | Monitor gates G2, G3, G4, G6 all observed. **Worn tuning not finished** — the gun still read too large at scale 0.5 | `78` |
> | **PLAN** | **THE VR HAND AND GUN — `76`, four slices.** Slice 1: push the viewmodel out and size it (knobs, no tracking). Slice 2: the gun follows the hand, visually only. Slice 3: the bullet follows the hand (`38` has the inversion). Slice 4: auto-aim and damping | **Plan written and agreed. Slice 1 next.** The constraint everything else bends around: `38`'s hard clamp, ~±30° off body centre | `76`,`38`,`36` |
> | **O53** | **SCALE — ANSWERED. `77`.** Provisional **~50 u/m**, measured worn from a correct eye height. `16` corrected at source; its derivation was out by ~2x | **The "big head" was O60, the recentre, NOT scale.** Owed: the doorway test at 50 vs 65, ten minutes | `77`,`16` |
> | **O8** | **The viewmodel is a SEPARATE fault, now observed** — oversized at 25/35/50/100, shrank only at 400 when everything did. `36` measured it at ~15-25 cm apparent | **Slice 1 of `76`.** And it is not cosmetic: the user has to close one eye to look at the world, which destroys the stereo B1 just bought | `77`,`76`,`36` |
> | **O62** | **Scale DOES respond to `-UnitsPerMetre` — 400 was unmissable** (world small, player tall, **and the gun scaled too**). 100 vs 50 felt identical, so the step was too small, not the axis wrong | **`71` had the DIRECTION backwards: 400 made it worse, so the correction is DOWN.** And the viewmodel moving with the knob means arm and world may be ONE fault, not two | `75`,`74` |
> | **O60** | **Recentre fires at PROCESS START, which is the wrong moment.** The headset is still on the desk when the game reaches the first menu, so the captured origin is wrong for every test that follows | **Should fire at LEVEL START, or on demand.** `F9` already works and composes correctly with the existing origin — the default moment is what is wrong, not the mechanism | worn, 2026-08-23 |
> | **O61** | **A quad layer for flat content** — a screen in front of you before the level, and the honest fix for the zoomed menus (`25`'s blit bug). One mechanism, two problems | Parked in `MODS-IDEAS` with the detail. **Not while `75` is open** | `MODS-IDEAS` |
> | **O59** | **`STEREO IS OFF` fires under `-NoXr`**, where stereo is off by design, and names `msaa_option` as first suspect — pointing the reader at a setting that is not wrong. **O17, and worse than recorded: a whole mode, not just menus** | Gate it on VR being enabled. One condition | `73` |
>

| # | Task | State | Next action | Doc |
|---|---|---|---|---|
| **B2** | **WORN, AND THE HEADSET SHOWS A DARK STALE FRAME** | **`63`. ~1% brightness, head and controller motion change nothing, but it is NOT frozen** - the image drifts and the save-select screen flickered through correctly once. Every instrument reports healthy: 90 passes/eye/sec, distinct targets, 90 Hz cadence, both hands tracked | **THE BISECT, in order: `-NoXr` play a level, then `-Flat` play a level, then worn. Whichever first shows it names the layer.** Then `rr_option: "Original"` worn | `63` |
| B1 | **The eyes will not fuse** | **`50` BUILT AND MEASURED. G2/G3 pass, G1 FAILED at 0 px.** Second defect found: one `viewProjTransformsBuffer` for both eyes | **ANSWERED — `57`. BOTH HALVES CARRY EYE 1's IMAGE** (both-pass vs eye1-alone: mean diff 0.31, 4.1%). Not a cancellation. Interpolation ELIMINATED | **MECHANISM ESTABLISHED, `58`, on a build whose instruments are all verified.** Eye 0's pass gets the correct distinct view (dx=1000.000), renders into its own target (stamped), and that target holds **eye 0's correct image when eye 1's pass is absent** (`-SkipEye 1`, 28.47% from eye 1's) and **eye 1's image when it is present** (4.32%, identical). **Something in eye 1's pass writes eye 0's texture.** Next: **census the WRITES — a per-target write counter tagged with the rendering eye.** Plan written, NOT built | `58` |

**What it is.** The workload has **2 framebuffer pairs**; `setOverride()`
redirects **one**. Pair 0 is shared between the eye passes. Eye 0 also has **no
override target at all at frame 0**. So eye 0's finished image sits in the shared
default target and eye 1's pass draws over it.

**The two eyes have been rendering the same image.** Measured: `0.14%` of pixels
differ across the seam, 0 px disparity at every depth, against a predicted 113 px.

**The fix** (`49`): give eye 0 its own scratch target too — size
`eyeColorTargets` as `displayFrames * 2`, publish both, and have present sample
the published target for each half.

**The gate**: `-Flat`, stand still, screenshot, cross-correlate → **113 px ± 5,
right eye further LEFT**. No headset. Regression: `-NoXr` unchanged.
**Falsification: `-Offset 0` → ~0 px, `-Offset 1.6` → ~56 px. NOT `-ForceEye`
— see O24.** `50` has the edits, the risks and the ordering against O21.

---

## OPEN

| # | Task | State | Doc |
|---|---|---|---|
| O32 | **Knob now ANNOUNCES itself** (edit 1 of `58`); A-G0's negative half passes. The run itself is **superseded** — the `target stamp` answered its question without it | Optional now | `58` |
| O33 | **BUILT AND FIRED.** `view FINAL` prints both passes' view translation at the consumption point; dx=1000.000 sustained | Done | `58` |
| O34 | **`fb census` now reports 1 pair, not the 2 `49` built its root cause on.** Either `49` measured a MENU (O28) or the count is workload-dependent | Log only | `58` |
| O35 | **The census verdict names a stale next action** — "Look at the shared transform buffer", which `51` closed | Not fixed | `58` |
| O41 | **`-SkipEye 0`'s black half NEVER meant "eye 1's pass leaves eye 0's target alone".** The target was never written at all (stamp `-1`). `56` and `57` both rested on that reading | **Corrected at source in `56`, `57`** | `58` |
| O42 | **The stamp records only a pass's OVERRIDE target.** Writes through `otherColorTargetKey` (`workload_queue.cpp:751,790`) and `fbManager.recordOperations` (`:862`) are invisible to it | The next slice | `58` |
| O36 | **THREE numbers for one gate.** `PREDICTION:` says -94.2 px per **668**-px half-frame; the capture's half is **800**; `00` says -113 px ± 5. **Must be fixed BEFORE the first non-zero disparity is measured** | Not fixed | `58` |
| O37 | Stray lines, two at a time, seen crossing the image during the run. Not measured, possibly a cursor artefact | Untriaged | `58` |
| O38 | **`rt64_state.cpp:1080` uploads the game's RAW viewProj into the SAME `BufferPair` eye 0's processor writes.** Eye 1 has its own; eye 0 shares with the game's path. Rule 6's shape, sixth time | Candidate, does not fit alone | `58` |
| O24 | **FIXED, not observed.** `-ForceEye` was announced but not connected under `-Flat`.** `g_forceEye` lives only in `ge_vr_xr.cpp`, which `-Flat` never starts; `vr.ps1` still prints `FORCE EYE n - depth MUST collapse` | Found while verifying `50`. Fix is edit 5 of `50`. Rule 6's shape, like `32`'s `-Sign` | `50` |
| O27 | **CLOSED as stated.** The resolve hypothesis died to source; the "eye 0 draws eye 1's view" statement died to measurement — dx=1000.000. **Ninth falsification** | Replaced by the bounded span: everything before `viewProjMatrix` is correct and distinct, everything after the pixels is correct and distinct | `58` |
| O31 | **CLOSED.** `rr_option` restored to `"Manual"`/90 and verified after the game closed. Backup kept at `graphics.json.bak-pre57` | Done | `57` |
| O29 | **`-Flat` has NO crash diagnostics.** The exception filter and every `shutdown:` line are gated behind `GE_VR_XR`; `-Flat` is now the main harness | Not built | `57` |
| O30 | **`render passes:` over-reports under `-SkipEye`** — counter increments before the skip | Known, not fixed | `57` |
| O28 | **The `fb eye` probe latches on the first workload — likely a MENU.** Same defect `52`'s census had in run 1. `49`'s "2 pairs" may be a menu measurement | Needs the census's latch condition | `52` |
| O25 | **CLOSED, not the cause.** Two `dst` addresses now, image unchanged. One `viewProjTransformsBuffer` for both eye passes was real and was not it |
| O25b | superseded — original text: **One `viewProjTransformsBuffer` for both eye passes.** Distinct hashes, one `dst`; both passes render whichever frustum wrote it last | **Plan written, NOT built. Blocked on `52`'s census** — a no-op if the world is in the shared pair | `51`, `52` |
| O21 | **Teardown can free GPU resources mid-use.** `WaitForSingleObject(...,1000)` result discarded; `shutdown: gpu idle` logged unconditionally | Fix designed, not built | `49` |
| O22 | **`-ResScale` makes it SLOWER.** 8x fewer pixels → 4x slower (60 → 16 fps). Unexplained, and it owns O7 | Open. Instrument built (`stage ms:`) | `49` |
| O23 | Two full GPU drains per frame (`execute(); wait();` per eye) plus one in the XR loop | Noted, not chased | `49` |
| O2 | Gate 6 — `-NoHeadTranslate` must KEEP stereo | Not judgeable until B1 | `34` |
| O5 | Hand aim: drive `crosshair_x_pos`/`_y_pos`, never `crosshair_angle` | Concept + firing path read | `37`, `38` |
| O6 | Legibility — "hard to see" | Untriaged | `33`, `47` |
| O7 | ~~60 fps not 90~~ | **VOID AS STATED — `60`.** That counter is incremented in `update_screen(vi_origin)`, the emulated N64 VI update: it measures the CONSOLE video clock, reads 60.0 across workloads differing 2x in cost, and never reported the PC framerate at all. `render passes: 90` says the renderer IS at 90. **The real present rate has never been measured** | `60` |
| O44 | **Add a real present counter** (draw hook) beside the VI line, and rename the VI line. Gate: `-NoXr` on a 180 Hz monitor must not read 60.0 | Not built | `60` |
| O46 | **`43`'s MSAA force-off is gated on `GE_VR_XR`, which `-Flat` never sets.** The harness every measurement since `49` came from is unprotected: open the graphics menu once and stereo dies silently. **O29's shape, second instance in two days** | Slice 1 of `62`, two lines | `62` |
| O47 | **"Changing a setting mid-session breaks execution"** — crash, hang, black or wrong render? Never written down; the four have different causes. RT64 HAS a live-reconfigure path, so the candidate is our eye targets not surviving it | Slice 2 of `62`, reads before experiments | `62` |
| O52 | **FIVE CITED DOCUMENTS NEVER EXISTED** — `41`,`42`,`43`,`45`,`46`, cited **37 times**, none ever on disk or in git history. `43` (the MSAA rule) alone is cited 24 times | **Stubs written** that point at the surviving source comments. Nothing invented, nothing removed | `00` |
| O49 | **THE XR PATH HAS NOT BEEN WORN SINCE `36`.** `43`,`47`,`49`,`50`,`51`,`52`,`54`,`56`,`57`,`58`,`61` were ALL measured in `-Flat`, which never sets `GE_VR_XR`. Eleven documents of change, never seen through the headset | **`-Flat` is not a substitute for wearing it, only for MEASURING it.** Belongs in `48` | `63` |
| O50 | **G4 was never fully run.** `-NoXr` reached the menu and was called a pass; a level was never played on the `61` build | Step 1 of the bisect | `63`, `61` |
| O4  | **BUILT AND PARTLY OBSERVED — `61`.** Profile bound (**oculus/touch_controller**, NOT Index); both hands tracked; `move`,`turn`,`fire`,`use`,`weapon_prev` all FIRED. G1,G2 pass, G3 partial | **Blocked on B2** — G5 needs a visible image. Remaining buttons unverified | `61`, `63` |
| O51 | **`view FINAL` logged EVERY FRAME in a headset** - 3 lines x 90 Hz, 20k lines in two minutes, synchronous I/O on the present thread. Gate tuned on `-Flat`, where the camera is still. **An instrument that changes what it measures** | **FIXED** - now behind `GE_VR_LOG_VIEW`, default off | `61`, `63` |
| O48 | **`vr.json`, hot-reloaded** — VR preferences as config with env vars as diagnostic overrides, each value logging its SOURCE. Delivers tuning WHILE WORN, which turns a wear test into a comparison. Part of `61` | Plan written, NOT built | `61` |
| O43 | **Scan lines: display-side, not ours.** Reproduce under `-NoXr`; absent from six captures; vanish when the window is not foreground (composited flip). Cosmetic | Low. Re-test after the memory/EXPO instability is settled | `59` |
| O45 | **Quit-to-menu goes BLACK under `-Flat`.** Does NOT reproduce under `-NoXr`, so it is on the VR path. Three candidates read OUT of the source; mechanism not identified | Step 2 of `59`: capture the black | `59` |
| O8 | Viewmodel at ~15-25 cm apparent | Not judgeable until B1 | `36` |
| O10 | Aim mode locks crosshair to head | Deferred by choice | `36` |
| O11 | Scope needs a scope RENDER, not a view zoom | Concept only | `37` |
| O12 | Auto-aim: **`37`'s "it will fight a tracked hand" is a PREDICTION, untested** — and there is currently no crosshair in VR at all, so auto-aim may be doing the job the missing crosshair would. **Runtime knob, default ON, decided by a wear test.** A world-space aim dot along the fired ray is feasible and is the option that changes the answer | `61` amendment | `61`, `37` |
| O13 | Aim cone clamped to ~original FOV | Undecided | `38` |
| O14 | `git add --renormalize .` | Deferred | `203b753` |
| O17 | `STEREO IS OFF` false-positives in menus | Needs gating on `inLevel` | `43` |
| O18 | Exit safety: is the X as safe as taskbar-close? | Unconfirmed | `42` |
| O20 | Re-run `-NoRecentreYaw` validly | **Blocked on B1** — void until stereo is real | `47` |

---

## DONE — observed, with evidence

| Task | Evidence | Doc |
|---|---|---|
| **B1 root cause identified** | `fb verdict: 2 framebuffer pairs but only pair 1 is redirected` | `49` |
| **The eyes render one image** | 0.14% pixels differ, 0 px disparity at all depths vs 113 predicted | `49` |
| **O16 `-Sbs` fixed** | `-Flat` splits the window; every measurement in `49` came from it | `49` |
| **O19 mirror measurement made a gate** | `PREDICTION:` line computes expected px before anyone looks | `49` |
| `viewOffset` symmetry (`47`'s next action) | pure x translation, worst rot term 0.000000 | `49` |
| Per-eye frustums mirrored | `m20 = ∓0.14106` | `49` |
| Clip-w convention | `m23 = -1.00000`, negative as assumed | `49` |
| Upload path correct and distinct per eye | hashes differ, ordered, serialised | `49` |
| Render responds to eye matrices | `-Offset 50` vs `0`: 81% of pixels differ | `49` |
| Both eyes render into distinct targets | `eye0=90 eye1=90 distinctTargets=90` | `43` |
| Present samples distinct textures | pointer comparison | `49` |
| Eye separation correct | 6.32 units at 100 u/m vs 63.5 mm | `47` |
| Eye-sign question closed | knob's consumer deleted by `30` | `32`, `36` |
| Recentre works | origin captured, y near zero | `36` |
| Hip-fire aim decoupled from head | Worn and confirmed | `36` |
| MSAA can no longer break stereo | Forced off under VR | `43` |
| Startup crash, teardown crash | | `27`, `29` |
| **Full shutdown with a LIVE session** | **`begin` / `session ended` / `gpu idle` / `xr session destroyed` / `complete, clean` - in order, TWICE.** The first two had never executed in this project's life | `63` |
| **The headset's real cadence** | `DISPLAY PERIOD: 11111128 ns = 90.0 Hz`, read for the first time | `63` |
| `build.ps1` | Clean builds, no lingering workers, stale-log warning | `49` |

---

## Corrections made by `49`

**A wrong doc that nobody flags costs more than a bug.**

| Claim | Where | Now |
|---|---|---|
| "`-ForceEye 0` — falsification, depth MUST collapse" | `00` step 4 | **False under `-Flat`.** Knob has no consumer there — O24. Corrected by `50` |
| "Find the seam by minimising `mean\|L-R\|`" | `49`, `00`, `48` | **Only valid on a BROKEN build.** With real stereo the halves differ everywhere. Cost 4 px (−117 vs −113) on a synthetic test. Seam now comes from client width — `50` |
| "`49`: THE root cause / the fix needs only building" | `49`, `39`, `00` | **Incomplete.** It was *a* root cause. `50` built it, G1 still measured 0 px — `50` AS BUILT |
| "`-SwapEyes` moves the fault to the other eye — needs a new explanation" | `47`, `49` | **Explained.** It changes which frustum the LAST pass carries, and the last pass owns the only buffer — `51` M1 |
| "44 px in the wrong direction" | `47` | **Void** — identical images cannot have disparity |
| "The unexplained residual" | `47` | **Void** — no signal to have a residual |
| "One rendered image is wrong; the eyes are asymmetric" | `47` | Wrong shape — there is one image |
| "Stereo validated" | `10`, 3e, 3f-3 | **Suspect** — nothing ever measured TWO images |
| "The headset's 90 Hz is queried and logged" | `00` | **False** — never queried at all |
| "`ds_option: 4`" | `00` | It is `1` |
| "Exit taking the machine down — fixed" | `00` | **Incomplete** — O21 |
| "`-Sbs` does not split the window" | `39` O16 | Launcher bug, fixed |

### ~~Not our bug~~ — **RETRACTED 2026-08-23. IT IS OUR BUG. See `75`.**

**Five `0x139 KERNEL_SECURITY_CHECK_FAILURE` bugchecks, arg1=3 (LIST_ENTRY
corrupt), every one within a minute of a VR session ending — and a `-NoXr`
session that played a level and exited clean.** `GoldenRecomp.exe` is
access-violating inside `nvwgf2umx.dll` and `D3D12Core.dll`. **The owner of this
machine lowered his RAM speed on the strength of the paragraph below and it
crashed three more times.** The original text is kept as the record of the
error:

The machine crash on 2026-08-23 (`-Flat` session, affinity pinned to the X3D CCD
on a 9950X3D) ended with the **BIOS losing its memory settings and requiring a
DIMM to be physically removed to boot.** No user-mode process can do that.
Memory-training / EXPO instability at firmware level. Re-test memory stability
before attributing any future machine-level fault to this project.
