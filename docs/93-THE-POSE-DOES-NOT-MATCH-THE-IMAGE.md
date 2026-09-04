# 93 — A POSE/IMAGE MISMATCH: CANDIDATE 4 FOR THE JUDDER

> # ►► CORRECTED BY `94`, THE SAME DAY. READ `94` FIRST. ◄◄
>
> **This document's title was "THE JUDDER IS A POSE/IMAGE MISMATCH" and every
> header below treats a hypothesis as a finding. `94` walks that back at the
> owner's insistence: *"we can't just change routes off what I said, what if I
> was wrong. We should test it."* He was right.**
>
> | What stands | What does not |
> |---|---|
> | **The MISMATCH is FACT**, read from source — `ge_vr_xr.cpp:1258`, `:1518`, `:1533` | **That it is the judder the wearer feels is a HYPOTHESIS** |
> | Some submissions must reuse an image — arithmetic | **"The three answers ELIMINATED all three candidates"** — they RE-RANKED them |
> | `28` documented the staleness in Phase 2 | **`92` question 1 eliminates NOTHING** — a static scene cannot judder under any hypothesis, so every candidate predicts "no". **§1's use of it is withdrawn** |
> | | **Whether the Pimax runtime reprojects anyway was never checked**, and that alone could make this wrong while every fact stays true |
>
> **`23` is back to OPEN and UNRANKED — promoted by `92` and demoted by `93`
> within hours, neither time from a number.**
>
> **`94` has the tests, and `94` §3 T4 is the decisive one: a knob that makes
> the mismatch deliberately WORSE. If a 4-tick lag changes nothing, this
> document is dead regardless of what anybody felt.**



**2026-08-23, immediately after `92`. Three questions, one wearer, no launch —
then two source reads. `92` ranked three candidates and the answers eliminated
ALL THREE, which is the most useful thing a diagnostic can do.**

> # ►► WE TELL THE COMPOSITOR THE IMAGE WAS RENDERED FROM A POSE IT WAS NOT RENDERED FROM. ◄◄
>
> ```cpp
> /* ge_vr_xr.cpp:1258 — this frame's fresh locate, at predictedDisplayTime */
> xrLocateViews(g_session, &vli, &viewState, 2, &got, views);
>
> /* ge_vr_xr.cpp:1518 — copy whatever RT64 last produced, however old */
> g_cmdList->CopyTextureRegion(&dst, 0, 0, 0, &src, nullptr);
>
> /* ge_vr_xr.cpp:1533 — submit the OLD image with the NEW pose */
> projViews[eye].pose = views[eye].pose;
> ```
>
> **The image in `source` was rendered by RT64 from a head pose the GAME thread
> snapshotted earlier. The pose handed to the compositor is from THIS present
> tick's locate. They are not the same pose and nothing reconciles them.**
>
> ## WHY THAT IS WORSE THAN PLAIN LATENCY
>
> **The compositor's whole job is reprojection: give it `(image, the pose the
> image was rendered from)` and it warps the image to the pose the display will
> actually have. That correction is what makes fast head motion survivable in
> every VR title.**
>
> **We hand it the CURRENT pose. So it concludes the image is already correct
> and warps it by nothing.** The stale image is presented as though it were
> fresh, and **the full render latency appears directly on the wearer's retina
> as world lag.**
>
> **We are not merely failing to correct the error. We are actively disabling
> the mechanism that would have corrected it.**

---

## 1. THE WEARER'S ANSWERS, AND WHY THEY KILL ALL THREE OF `92`'s CANDIDATES

| `92` §6 question | Answer | What it eliminates |
|---|---|---|
| **1. Stand still at a wall — does it judder?** | **"No"** | **Kills the 2:3 cadence as the primary.** A steady presentation beat does not switch off because the head stopped |
| **2. Turn your head — does the GUN step against a smooth world?** | **"All judder if I look fast. If I turn slow it's fine"** | **Kills partial interpolation.** That fault is DIFFERENTIAL — near object against far. **Everything moving together is a WHOLE-VIEW fault.** And **"fast bad, slow fine" is a VELOCITY threshold** |
| **3. Constant, or worse when busy?** | **"Once it's bad it's bad, there is no worse. It's the same judder"** | **Kills `73`'s VI-clock halving.** That is load-driven by definition, and `92` had already measured it at one sample in 149 |

### THE SIGNATURE, STATED AS A PROPERTY

**The error is a function of HEAD ANGULAR VELOCITY and of nothing else** — not
scene content, not scene load, not the object being looked at, and it is zero
when the head is still.

> **There is one quantity in a VR pipeline with exactly that dependency:
> `angular error = angular velocity x latency`.**
>
> Slow turn -> small error -> below threshold -> **"fine"**.
> Fast turn -> large error -> **"all judder"**.
> Head still -> zero error -> **"no"**.
> Busy scene -> same latency -> **"no worse"**.
>
> **Four answers, one expression. `48` rule 3 — this is what measuring rather
> than describing looks like even when the instrument is a person.**

---

## 2. THE MECHANISM, FROM SOURCE

### 2.1 THE TWO POSES COME FROM DIFFERENT PLACES, ON DIFFERENT THREADS

| | |
|---|---|
| **The pose the frame is RENDERED from** | `ge_vr::head_view()`, read on the **GAME thread** in `rt64_render_context.cpp` when it builds `VrConfiguration`. RT64's `ProjectionProcessor` applies it |
| **The pose the frame is SUBMITTED with** | `views[eye].pose` from `xrLocateViews` at `ge_vr_xr.cpp:1258`, on the **PRESENT thread**, at this tick's `predictedDisplayTime` |
| **What connects them** | **Nothing.** `publish_head_view` is a one-way snapshot. The header says so plainly: *"published once per frame by the XR frame loop on RT64's present thread and read by the host's config update on the game thread"* |

**This is `28`'s "one-frame staleness", which `00` already names** — *"the world
lagged slightly ... the one-frame staleness in docs\\28"*. **It has been in the
tree, documented, since Phase 2. What is new here is that it is the JUDDER**,
and that submitting the fresh pose with the stale image converts a bounded
latency into an uncorrected one.

### 2.2 AND THE SAME IMAGE IS SUBMITTED MORE THAN ONCE, WITH DIFFERENT POSES

**RT64 produces about 60 rendered frames per second** (`92`: the sim is locked
at 60 and `gEXSetRefreshRate` declares 60). **The present tick runs at the
headset's rate, about 90** (`92`: median 91 eye passes/second).

**So roughly one submission in three copies an image the previous submission
already used — and gives it a DIFFERENT, NEWER pose.**

> **One unchanged image, presented twice, claimed to have been rendered from two
> different viewpoints.** The compositor has been told the scene moved when the
> pixels did not. **On a fast turn that is a step backwards followed by a step
> forwards — which is precisely what judder looks like**, and precisely why it
> arrives all at once above a speed threshold rather than growing gently.
>
> **`47`'s mirror table, second row, is this fault, written down before anyone
> knew we had it:**
>
> | Mirror | Lenses | Means |
> |---|---|---|
> | **right** | **wrong** | **the images are right; the pose/FOV submitted with them is wrong** |

---

## 3. WHAT THIS EXPLAINS THAT WAS PREVIOUSLY LOOSE

| Previously | Now |
|---|---|
| **`72`: ~87% of every frame blocked in `xrWaitFrame`, submit loop EXONERATED** | **Still true and still exonerated. The submit loop is not slow — it is submitting the WRONG METADATA, which no timing instrument can see.** `72` measured duration and this is a correctness fault |
| **`26` predicted judder "from `xrWaitFrame` owning the cadence"** | **The prediction was right; the attributed cause was not.** The cadence is fine. The pose attached to it is not |
| **`00`: "the world appears rigidly attached to your head" is the failure where the compositor is told the image came from a viewpoint it did not** | **That sentence already describes this bug.** It was written about a `y` that never moves; **the same mechanism at partial strength is the judder** |
| **`92`'s three candidates** | **All eliminated by the wearer in one launch, at zero cost.** Kept in `92` as the record |

---

## 4. THE FIX, IN PRINCIPLE — and it is bounded

**Carry the pose with the image.**

1. **When RT64 renders an eye pair, record the head pose it actually used** —
   it already has it, in `VrConfiguration`.
2. **Publish that pose alongside the rendered texture**, so the present tick can
   ask *"what was this image rendered from?"* rather than *"where is the head
   now?"*
3. **Submit THAT pose in `projViews[eye].pose`.**
4. **Then the compositor's reprojection does its job**: it warps the stale image
   to the true display pose, and the residual error the wearer sees drops from
   *full render latency* to *whatever the compositor cannot warp away*.

> **This is not a new subsystem. It is a value that already exists at the render
> end and is thrown away before the submit end asks for it.**
>
> **AND IT IS RULE 8.** *"When two things must agree, do not synchronise them —
> remove the second one."* **There are currently two poses that must agree and
> do not. The fix is not to synchronise them; it is to have ONE — the pose the
> image was rendered from — and submit it.** `46` reached the same shape for
> the recentre, twice, the hard way.

**What this does NOT fix:** the image is still 60 Hz of game content. **Motion
of the WORLD is still simulated at 60** (`92`: the quantum is 1/60 and cannot be
90). **Reprojection corrects for HEAD motion, not for world motion** — so this
addresses the fault the wearer just described and leaves `92`'s cadence question
open underneath it, where it belongs.

---

## 5. THE GATES — write them before the code. `48` rule 2.

**Instrument first, per `86` slice S0's own principle. Two lines, and they
answer it before anything is changed.**

| Gate | What would a working build have to do differently to fail? |
|---|---|
| **G93-1** | **Log the angular difference between the pose the frame was RENDERED from and the pose it is SUBMITTED with, per submission.** **PREDICTION: non-zero, and it GROWS WITH HEAD ANGULAR VELOCITY.** **A build where these already agree prints ~0 always — and this whole document is then wrong** |
| **G93-2** | **Count submissions that reuse an unchanged rendered image.** **PREDICTION: roughly one in three** at 60 render into 90 present. A build that renders per submission prints zero |
| **G93-3** | After the fix: **the logged difference is unchanged** — the mismatch is still there, because the image is still stale — **but the SUBMITTED pose now equals the RENDERED pose.** **The number that must go to zero is the LIE, not the latency** |
| **G93-4, worn** | **Turn fast. The judder is materially reduced.** The wearer is the instrument, and this is the only gate that decides |
| **G93-5, regression** | **`-NoXr` untouched, and stereo still measures -113 px +/-5 under `-Flat`.** B1 cost this project weeks; nothing here may disturb it |

**THE NO-CODE FALSIFIER, and `47` already built the method:**

> **Record the headset mirror while turning fast.** A mirror shows the submitted
> IMAGE and never the metadata. **If the mirror is smooth while the lenses
> judder, the images are right and the pose submitted with them is wrong** —
> `47`'s table, row 2. **If the mirror judders too, this document is wrong and
> the fault is in the image, not the pose.**
>
> **One recording. No build. It should be done before the fix, not after.**

---

## 6. WHAT THIS DOES TO THE PLAN

| | |
|---|---|
| **This outranks `86` entirely** | Comfort is the ship blocker the owner named, and **this is a correctness fault in the frame we present, not a feature gap** |
| **S0 still ships first** | Written, one build, and **G93-1 and G93-2 are two more lines in the same instrument** — `48`'s amended rule 5: diagnostics batch freely |
| **NEW: O77** | **The pose/image mismatch. Instrument it (G93-1, G93-2), then carry the render pose through to the submit** |
| **`92` stays open underneath** | The 2:3 cadence and the 1/60 quantum are real and unaddressed. **They are simply not what the wearer is feeling right now** |
| **`23` returns to cosmetic** | `92` promoted it on the partial-interpolation theory. **Question 2's answer — everything judders together — demotes it again.** Rule 10, three hours later |

---

## 7. HOW CONFIDENT IS THIS, HONESTLY

**The mismatch is FACT, read from source: `projViews[eye].pose` is assigned from
this tick's locate, and the texture copied beside it is whatever RT64 last
produced.** That is not in question.

**That the mismatch is THE judder the wearer feels is a HYPOTHESIS.** It
explains all four properties of the report with one expression and it is the
only candidate that survives the three answers — but **this project has
falsified twelve plausible mechanisms that each explained everything, and `49`
alone killed five in one session.**

> **So: instrument before fixing. G93-1 costs two lines and either shows a
> velocity-dependent error or it does not.** **Do not let a good explanation
> skip the measurement — that sentence is why `57`'s title is wrong.**
