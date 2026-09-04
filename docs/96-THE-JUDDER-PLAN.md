# 96 — THE JUDDER PLAN. Read this, then do it in order.

**2026-08-23. THE handover document for the comfort work. `92`-`95` are the
reasoning; this is the plan. Written to be executed by a session that has read
nothing else.**

> # ►► COMFORT BLOCKS EVERYTHING. `86`'s SLICES WAIT. ◄◄
>
> **The owner's words: *"it's pointless building all this extra stuff if you're
> just gonna get sick when you're playing it."*** He is right, and `86`'s nine
> 6DoF slices are parked until this has an answer. **A slice built into a build
> the wearer cannot tolerate cannot be judged by the wearer — and the wearer is
> this project's best instrument.**

---

## THE ONE FACT THAT SURVIVES EVERY DESCRIPTION

> **STICK TURN IS CLEAN. HEAD TURN IS NOT. At comparable angular speeds.**

**Both rotate the world across the retina; only one is bad.** That localises the
fault to the **HEAD POSE PATH** and it depends on no adjective, no metaphor and
no visual. **Everything else the wearer described is context. This is the
finding.**

**Second, separate fault, do not conflate them:** *"when I turn with the
controller it doesn't judder, but it just feels not ninety hertz."* **That is
`92`** — the sim runs at 60 (measured, 142 of 149 samples) and RT64 interpolates
to ~90. **Smooth-but-not-native is the honest expected result of the current
architecture. Fixing the head-turn fault will NOT fix that, and success must not
be judged by it.**

---

## THE STATE OF THE EVIDENCE, HONESTLY

| | |
|---|---|
| **FACT, from source** | We submit whatever RT64 last rendered with **this present tick's** freshly located pose. `ge_vr_xr.cpp:1258`, `:1518`, `:1533`. **The image and the declared pose are not from the same moment** |
| **FACT** | At ~60 rendered into ~90 presented, some submissions must reuse an image. Arithmetic |
| **FACT** | `28` documented this staleness in Phase 2 and nobody connected it to comfort |
| **FACT, from source** | **We apply NO smoothing, prediction or damping to the head pose.** Checked; a useful negative |
| **HYPOTHESIS** (`93`, candidate 4) | That the mismatch is what the wearer feels |
| **UNCHECKED, AND IT COULD DECIDE EVERYTHING** | **Does Pimax OpenXR 0.1.0 reproject at all?** If it does, we are aiming its correction at the wrong target. If it does not, the mismatch shows up raw |
| **NOT ELIMINATED** | `92`'s 2:3 cadence, and a stereo fault that only appears in motion |

**Twelve plausible mechanisms have been falsified in this project. `49` killed
five in one session. Nothing below assumes `93` is right.**

---

# THE PLAN — four phases, in order, cheapest first

## PHASE 0 — FREE. NO BUILD. DO THIS FIRST.

**These can invalidate the entire framing of everything after them, and they
cost seconds of wearing.**

| # | Test | Result -> meaning |
|---|---|---|
| **D1** | **Close ONE EYE while turning your head fast.** | **Doubling GONE -> it is STEREO.** The two eyes disagree during motion — a live B1-shaped fault that every static measurement in this project would have missed. **`93` is then looking at the wrong half of the pipeline.** **Doubling REMAINS -> TEMPORAL**, and Phase 2 is the right next step |
| **D2** | **Stop dead mid-turn**, staring at a high-contrast edge. | **Clears instantly -> motion-driven.** **A static double remains -> stereo geometry**, present at rest and merely invisible until something moves |
| **T1** | **Record the headset mirror while turning fast**, then watch it. `47`'s method | **Mirror smooth, lenses bad -> the images are right and the POSE is wrong.** **Mirror bad too -> the images are bad; `93` is DEAD** |

> **A mirror shows the submitted IMAGE and never the metadata. That is why `47`
> works and why T1 is the best ten minutes available.**

## PHASE 1 — ONE READ, NO CODE. **O79.**

**Establish what Pimax OpenXR 0.1.0 actually does:** does it apply late-stage
reprojection / timewarp? Does it predict? Is there a setting for it? Check the
Pimax OpenXR documentation and its own settings UI.

User Input: "Smooth motion is what it is called, it is and has been disabled."

> **Why before the fix and not after:** if the runtime does NOT reproject, then
> carrying the correct pose through buys far less than `93` assumes, and the
> real fix is to reduce staleness rather than to label it honestly. **The fix
> changes depending on this answer, so the answer comes first.** `86` §8's rule:
> do the reads before, not during.

User Input: "The answer is that we arent using the feature so we can look at it for what it is."

## PHASE 2 — THE BUILD THAT IS ALREADY WRITTEN. ONE COMPILE.

**Already in the tree, never compiled: slice S0 (`91`), the `posecheck`
instrument, and `GE_VR_POSE_LAG` (`94` T4).** `GE_VR_POSE_LAG` defaults to 0,
an exact identity, so an unset build is unchanged.

User Input: "We did these tests but I am willing to test again"

```powershell
cd C:\Users\<USER>\Desktop\GoldenEye64Recomp
.\build.ps1                                                       # SHORT path, no new patch name
.\vr.ps1 -UnitsPerMetre 50 -SeamNoRot -HandPosZ 1                 # A: today
.\vr.ps1 -UnitsPerMetre 50 -SeamNoRot -HandPosZ 1 -PoseLag 4      # B: made worse on purpose
.\vr.ps1 -UnitsPerMetre 50 -SeamNoRot -HandPosZ 1 -PoseLag 0      # A again
# F9 WHILE WEARING IT.  Exit: taskkill /F /IM GoldenRecomp.exe  - NEVER the X
copy gevr.log gevr-keep-poselag<N>.log      # it is rewritten every launch
```

| Test | **PREDICTION** | **What kills it** |
|---|---|---|
| **T4** `-PoseLag 4` | **Much worse on HEAD turns, and NOTHING AT ALL on stick turns** | **No change -> `93` is DEAD**, whatever anyone felt. **Worse on BOTH -> it is not this mechanism** |
| **T2** `posecheck` MAX delta | **> 0, larger when you turned fast** | **~0.00 always -> `93` is DEAD**; the poses already agree |
| **T3** submits vs renders | **~90 vs ~60, reused ~30/s** | Equal -> RT64 renders per submission; `93` §2.2 wrong |

**Also free in the same launches — S0's own gates (`91`):** `6dof:` lines
appear with every field labelled by frame; **no `6dof` line at all under
`-NoXr`**; **`muzzleExt` must be > 0** and **`A40` must be < 0** (these two
decide whether `88` §5.1's aim-axis reasoning inverts, which changes slices G2
and A1).

**A/B/A ordering is deliberate** — going back to 0 at the end guards against
"everything feels worse the longer I wear it", which is real and would otherwise
read as a positive result.

## PHASE 3 — THE FIX, CHOSEN BY WHAT PHASES 0-2 SAID

User Input: "None of this reflects on the flat screen mirror or output. Only in the headset.  Turning is better by using joystick but head movement causes image to double most notibilty on edges and visable lines.  If joystick movement is being judged, even though its better than headmovement it still feels slower than you would want." 

**Do not pre-commit to one. The decision table IS the plan.**

| If | Then build |
|---|---|
| **D1 says STEREO** | **Stop. New investigation.** The two eyes disagree in motion; `93` is not it. Start from `47`'s method applied to a MOVING scene, since every B1 measurement was static |
| **T4 worse + T2 non-zero + runtime DOES reproject** | **CARRY THE RENDER POSE THROUGH TO THE SUBMIT.** RT64 already has the pose in `VrConfiguration`; publish it with the frame and put it in `projViews[eye].pose`. **Rule 8: two poses that must agree, so have ONE.** The compositor's warp then does its job |
| **T4 worse + runtime does NOT reproject** | **Reduce staleness instead.** Labelling the pose honestly buys nothing if nothing acts on the label. Look at the game-thread/present-thread handoff (`28`) and at rendering closer to submit time |
| **T4 no change** | **`93` is dead.** Return to `92`: the 2:3 cadence and the 1/60 quantum. **`92` §4 route A — keep the 60 sim, fix the interpolation — is the only route compatible with `86`** |

**Gates for whatever gets built — write them before the code, `48` rule 2:**

| | |
|---|---|
| **G-FIX-1** | **Worn: turn fast. The wearer reports it materially better.** The only gate that decides |
| **G-FIX-2** | `posecheck` MAX delta **goes to ~0** — the number that must vanish is the LIE, not the latency |
| **G-FIX-3** | **`-NoXr` untouched**, and stereo still measures **-113 px +/-5** under `-Flat`. **B1 cost this project weeks; nothing here may disturb it** |
| **G-FIX-4** | **Stick turn is no WORSE.** It is currently the clean case and it is the control |

---

## WHAT NOT TO DO

| | |
|---|---|
| **Do not change the 1/60 quantum** | `92`: it would change the aim feel of every weapon, because `crosshair_x_pos` steps once per `g_ClockTimer`. It is a project, not a slice |
| **Do not build on the wearer's imagery** | *"Just an example of the visual, let's not get caught up on that."* **The stick-vs-head asymmetry is the finding; the mountain edge is not** |
| **Do not re-ask the three `92` §6 questions** | Answered. `95` §1 records them |
| **Do not resume `86`'s slices first** | S0 excepted — it is written, it is one build, and it batches with the tests |
| **Do not trust a description that agrees with you** | `94` §6. It happened once already this session and the owner caught it, not the protocol |

---

## THE SINGLE NEXT ACTION

> **Commit both repos (owed — O73). Then PHASE 0: close one eye while turning
> fast, stop dead mid-turn, and record the mirror. Thirty seconds of wearing and
> ten minutes of video, no build, and it can invalidate everything after it.**
>
> **Then Phase 1's read, then the one build.**

**Nothing in Phase 3 is built. `48` rule 1: plan, discuss, then execute.**
