# 97 — D1 IS ANSWERED, `93` IS RE-AIMED, AND THE FIX HAS A SHAPE

**2026-08-24. Written after the owner ran D1 and answered O79. Read `96` for the
plan this executes; this document records what Phase 0 and Phase 1 returned and
what they change.**

---

## §1 — WHAT CAME BACK

| Test | Answer | What it eliminates |
|---|---|---|
| **D1 — close one eye while turning fast** | **"It does it in both, even by themselves."** | **STEREO IS DEAD.** A fault visible in ONE eye alone is not a disagreement between two eyes. `96`'s "D1 says STEREO -> stop, new investigation" row does not fire |
| **D2 / T1 (mirror)** | *"None of this reflects on the flat screen mirror or output. Only in the headset."* | **Weaker than it looks — see §2.** It does NOT distinguish the candidates on its own |
| **O79 — does Pimax OpenXR 0.1.0 reproject?** | **"Smooth motion is what it is called, it is and has been disabled."** | **THE RUNTIME DOES NOT REPROJECT.** This is the row of `96`'s decision table that fires |
| **T2 — `posecheck` MAX delta** | **NON-ZERO, 0.06 -> 7.09 deg, largest when turning fast.** 54 samples, `gevr.log` | Matches the prediction. The poses do not agree |
| **T3 — submits vs renders** | **`submits=90 renders=60 reused=30`, every second, dead on** | Confirmed. One submission in three is a REPEATED IMAGE |

---

## §2 — THE MIRROR EVIDENCE IS WEAKER THAN `47`'s TABLE MAKES IT LOOK

**`47` row 2 — *mirror right, lenses wrong = the pose is wrong* — assumed the
only two candidates were "bad images" and "bad metadata".** A **duplicate**
image is neither. It is a perfectly correct image shown at the wrong *time*, and
a mirror recording of a 90 Hz stream watched on a 60 Hz monitor will not show it.

**Recorded so a later session does not lean on that row harder than it can
bear.** Rule 10. The evidence that carries the weight here is D1 and T3, both of
which are numbers or single-eye observations rather than comparisons of two
displays.

---

## §3 — THE MECHANISM, RESTATED. `93` WAS RIGHT ABOUT THE DEFECT AND WRONG ABOUT WHY IT HURTS

**`93` said: we hand the compositor a stale image with a fresh pose, which tells
it no correction is needed, so it applies none — we are disabling the mechanism
that would have corrected us.**

**O79 kills the second half of that sentence. There is no mechanism to disable.
Smooth Motion is off, so nothing was ever going to warp our image whatever pose
we labelled it with.**

**What is left is not a labelling error. It is the raw arithmetic of T3:**

> **Thirty times a second we display the same pixels for two consecutive
> display frames while the wearer's head keeps moving.**

At 90 Hz that is a 2-1-2-1 cadence — **`92`'s pulldown judder, arriving through
`93`'s code path.** The two candidates were never rivals; they are the same
defect described from two ends. **On a high-contrast edge during smooth motion, a
frame held for double the time and then jumped double the distance is seen as a
DOUBLED EDGE, in each eye independently.** That is D1's answer, predicted after
the fact but predicted from the measurement rather than from the description.

### Why stick turn is clean and head turn is not — the fact that survives every description

**Because they are interpolated by different things, and only one of them is
interpolated at all.**

- **Stick turn is a GAME rotation.** It happens in the 60 Hz sim, and RT64's
  interpolator exists precisely to smooth 60 Hz sim motion into 90 presented
  frames. `64` proved that interpolator is load-bearing.
- **Head turn is a POSE rotation.** It enters at eye-render time, which happens
  at the **eye-render rate — `renders=60`.** RT64's interpolator never sees it.
  **Nothing smooths head motion. There is no intermediate frame for it to be
  smoothed into.**

**This explains the asymmetry with no adjective and no metaphor, it explains why
the stick case still "feels not ninety hertz" (it is genuine 60 interpolated to
90), and it predicts that the head case is strictly worse — which is what was
reported.**

---

## §4 — THE FIX: IF THE RUNTIME WILL NOT REPROJECT, WE REPROJECT

**`96`'s decision table, the row that fires: *T4 worse + runtime does NOT
reproject -> reduce staleness instead. Labelling the pose honestly buys nothing
if nothing acts on the label.***

**Carrying the render pose through to the submit — `93`'s proposed fix — is now
known to buy NOTHING ON ITS OWN.** It is still correct and should be done, but as
the INPUT to the warp below, not as the fix.

### The proposal: rotational timewarp in our own copy step

**We already own the exact place and we already have both inputs.**

| We have | Where |
|---|---|
| The pose the image was rendered from | **`ge_vr::render_pose()`** — already called every present tick by `posecheck`, `ge_vr_xr.cpp:1613` |
| The pose we are about to submit | `views[eye].pose`, `:1258` |
| A command list open on RT64's queue, with an RTV already created for the swapchain image | `:1467` |
| The delta between them, in degrees | `posecheck` computes it today and throws it away |

**Today `:1518` is a `CopyTextureRegion` — a straight blit. The fix replaces
that blit with a full-screen draw that samples the eye texture through the
rotation between the two poses.** That is asynchronous timewarp, it is what the
compositor would have done had Smooth Motion been on, and it is roughly a
hundred lines of shader plus a constant buffer.

**Why this and not "make RT64 interpolate the eye targets":** that is the larger
and better fix and it should be costed — but it interpolates GAME motion, and
`renders=60` says the eye path is not on it today. **The head-pose half would
still not be smoothed by it**, because the head pose is not a quantity the
interpolator knows about. **A timewarp fixes the head half specifically, which is
the half the wearer reports as intolerable.**

### GATES — written before the code. `48` rule 2

| Gate | What would a WORKING build have to do differently to fail? |
|---|---|
| **G-97-1** | **Worn: turn the head fast. The wearer reports the doubling materially reduced.** The only gate that decides |
| **G-97-2** | **`posecheck` MAX delta is unchanged.** The lie is not what we are removing — the delta is the CORRECTION SIZE and it must stay non-zero. **A gate that expected it to go to zero would be a gate a broken build passes**, and `96` G-FIX-2 is corrected here on that ground |
| **G-97-3** | **A new counter: `warp: applied=N skipped=N maxCorrection=X deg`.** Applied must be ~90/s and `maxCorrection` must track head speed. **If it prints applied=0 the fix is not running and any felt improvement is imagination** |
| **G-97-4** | **`GE_VR_TIMEWARP=0` is an EXACT identity** — same code path as today, so the A/B is one env var and not one build |
| **G-97-5** | **`-NoXr` untouched, and `-Flat` still measures -113 px +/-5.** B1 cost this project weeks. Nothing here may disturb it |
| **G-97-6** | **Stick turn is no WORSE.** It is the clean control case |

### The risk that must be stated before the code, not after

**A timewarp on a 60->90 duplicate corrects ROTATION only. It cannot correct
translation, and it cannot invent geometry disoccluded at the edges of the
frame.** Expect a residual at the frame border and expect no improvement at all
on the "not ninety hertz" stick complaint — **which `96` already warns must not
be used to judge success.** If the wearer reports the stick case improved, the
instrument is wrong or the report is.

---

## §5 — WHAT IS STILL OWED, AND IT IS SMALL

1. **T4 has no control on disk.** All 54 `posecheck` lines say `POSE_LAG=4`;
   `gevr.log` is rewritten every launch and no `gevr-keep-poselag0.log` exists.
   **One `-PoseLag 0` launch, then `copy gevr.log gevr-keep-poselag0.log`.**
   Cheap, and it is the baseline every number above is implicitly compared to.
2. **THE GAME HALF OF S0 HAS NEVER PRINTED A LINE.** Zero `6dof-game:` lines in
   the log, and all eight controller samples read `valid=0 focused=0`. **That
   launch never reached a level.** The block is gated on `geVrWorldCamera()`,
   so it is doing exactly what it was written to do — **but `muzzleExt` and
   `A40` are still unread**, and they decide whether `88` §5.1 inverts and
   whether slices G2 and A1 change shape. **`52`'s menu trap in a new place.**
   Needs one launch that enters a mission with a gun in hand.
3. **`96` §Phase 3's decision table is now resolved to one row.** Recorded here
   rather than rewritten there, so the reasoning that chose it stays visible.

---

## §6 — AS BUILT. 2026-08-24. NOT COMPILED, NOT WORN — `48` RULE 11

**One file touched: `src/main/ge_vr_xr.cpp`. No new `RECOMP_PATCH` name, no new
source file, no `CMakeLists.txt` edit — so this is a SHORT build with no
regeneration step.** Backups: `ge_vr_xr.cpp.bak97`, `vr.ps1.bak97`.

| Where | What |
|---|---|
| **The knob** | `GE_VR_TIMEWARP`, **default 0**. Unset takes the original `CopyTextureRegion` path with no branch taken and no object created. **G-97-4** |
| **`vr.ps1 -Timewarp`** | Sets it, and prints what to read and what would mean it is not running |
| **The draw** | Replaces the blit at the old `:1518` with a full-screen triangle that inverse-maps each pixel: submitted-frustum ray -> delta rotation -> rendered-frustum ray -> sample |
| **The delta** | `q_delta = conj(q_rendered) * q_submitted`, from `ge_vr::render_pose()` — **the same call `posecheck` already makes**, so there is no new plumbing and no second source of truth. Rule 8 |
| **The instrument** | `warp: applied=N skipped=N maxCorrection=X deg`, once a second beside `posecheck`. **G-97-3** |

**Three decisions worth knowing before reading a wear report:**

1. **TWO SRV SLOTS, ONE PER EYE. This is B1 in one line.** `69`-`71`: both
   present draws bound the **same descriptor heap slot** in one command list and
   D3D12 resolves heaps at **execution** time, so the second binding won for
   both eyes. **Both eyes are recorded into `g_cmdList` here too.** A shared slot
   would reproduce B1 exactly and it would look like a timewarp bug.
2. **`d3dcompiler_47.dll` and `D3D12SerializeRootSignature` are reached by
   `GetProcAddress`, not by linking.** Linking means editing `CMakeLists.txt`,
   and `07` GOTCHA 4 is that a `CMakeLists` edit without `cmake -S . -B build`
   **succeeds while silently ignoring the change.** If either lookup fails the
   build logs it and falls back to the straight copy — a stated hazard rather
   than a silent one.
3. **A backwards delta warps by exactly the right amount in exactly the wrong
   direction**, which reads as *"much worse"*, not as *"no change"* — and
   `maxCorrection` prints the same either way. **If the wearer reports much
   worse, invert the delta before concluding the mechanism is wrong.**

## §7 — A KNOB THAT WAS NEVER CLEARED. `48` rule 6, again

**`vr.ps1` clears every `GE_VR_*` before setting the ones it wants — its own
comment says a leftover is indistinguishable from a change that did not work —
and `GE_VR_POSE_LAG` WAS NOT IN THE LIST.** Added, with `GE_VR_TIMEWARP`.

**This is a candidate explanation for §5 item 1**: all 54 samples in `gevr.log`
read `POSE_LAG=4` with no `-PoseLag 0` run anywhere, which is what a sticky
shell variable looks like. **Not established — the launches may simply all have
been at 4.** But the T4 baseline must now be re-run from a **fresh shell**, and
the number to check is the `POSE_LAG=` field the instrument already prints.
