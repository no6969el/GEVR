# 98 — THE TIMEWARP RAN, AND MADE IT WORSE. WHAT THAT DOES AND DOES NOT MEAN.

**2026-08-24. First wear of `97`. Read `97` first.**

## §1 — THE RESULT

**Wearer: *"The fix is actually horrible. Timewarp made it even worse."***

**And the instrument says it was running correctly**, which is the only reason
that report is worth anything — `48` rule 4:

```
warp: applied=182 skipped=0 maxCorrection=0.88 deg      (tw1 log)
posecheck: MAX delta 0.87 deg | submits=91 renders=60 reused=31 | POSE_LAG=0
```

| | |
|---|---|
| `applied=182`, `skipped=0` | **182 = 2 x 91. Two eyes per submission.** Every submission was warped. G-97-3 passes |
| `maxCorrection` 0.00 -> 3.40 deg | **Tracks head speed**, and matches `posecheck`'s independently-computed delta line for line. Both halves agree |
| `POSE_LAG=0` | **The baseline `97` §5 said was missing now exists** — `gevr-logs\gevr-0823-210234-tw0-lag0.log`. The sticky-variable worry in `97` §7 is closed: it was 4 because it was set to 4 |

**So this is not a fix that failed to run. It is a fix that ran and pointed the
wrong way.**

## §2 — WHY "MUCH WORSE" IS INFORMATION AND "NO CHANGE" WOULD NOT HAVE BEEN

**`97` §6 item 3, written before the run:** *a backwards delta warps by exactly
the right amount in exactly the wrong direction, which reads as "much worse",
not as "no change".*

**A warp that does nothing useful would have been reported as UNCHANGED.** A
warp of the right magnitude aimed backwards **doubles** the angular error, and
doubling an error that is already the complaint is exactly "horrible". **The
report is consistent with the mechanism being right and the sign being wrong,
and inconsistent with the mechanism being irrelevant.**

**This is not proof.** It is the prediction that was written down first, which
is the only kind worth anything here — `48` rule 2.

## §3 — TWO SUSPECTS, AND THE SECOND ONE IS IN OUR OWN SOURCE COMMENT

**SUSPECT 1 — the delta is conjugated.** Derivation says
`d_r = (q_rendered^-1 * q_submitted) * d_submitted`, and it is what `97` built.
It is right on paper and paper has lost to this codebase repeatedly.

**SUSPECT 2 — THE POSE WE COMPARE IS NOT THE POSE THE IMAGE WAS RENDERED FROM.**
`ge_vr_xr.cpp`, at the copy itself, has said so since Phase 2:

> *"this list is executed during RT64's render hook, while RT64's own list for
> THIS frame is still open. So the eye targets we read are the ones RT64
> finished LAST frame."*

**But `publish_render_pose` is called from the frame RT64 is building NOW.** So
the image is from render N-1 and the pose we call "rendered-from" is render N.
**We are correcting from the wrong end of the interval.** That does not obviously
double the error, but it does mean the warp is aimed at an interval we never
measured — and it makes `posecheck`'s delta an underestimate of the real
image-to-display staleness, which is a correction owed to `93` and `97`. Rule 10.

**Both are cheap to settle and NEITHER requires the wearer to turn his head.**

## §4 — THE MOTIONLESS TEST. `GE_VR_TIMEWARP_YAW`

**The wearer is being made ill by the thing under test, so the test must not
require the symptom.** `48`: the wearer is the best instrument in this project —
which is a reason to spend his wearing time carefully, not freely.

`-TimewarpYaw 10` **ignores the measured delta entirely** and warps by a fixed
10 degrees of yaw. **Head still. Nothing moves.** The picture must simply sit
rotated by a known angle in a known direction.

| What he sees, holding still | Means |
|---|---|
| **Picture shifted, and STAYS still** | The warp works and the axis is yaw. **Which way it shifted gives the sign directly**, and `-TimewarpInvert` is then the fix |
| **Picture shifted the wrong way** | Suspect 1 confirmed. `-TimewarpInvert` |
| **Picture tilted or shifted VERTICALLY** | Axis convention, not sign. The shader's ray basis disagrees with the pose's |
| **Picture judders or swims while still** | **The delta is not the only thing driving it — suspect 2.** Nothing should move under a constant warp |

**`-TimewarpInvert` (`GE_VR_TIMEWARP=2`) is the other arm, one env var away, no
rebuild.**

## §5 — THE PROTOCOL ITEM THIS EARNED

**`48` says the wearer is the best instrument. It does not say what the wearer's
job IS, and this session got that wrong before he corrected it:**

> ***"I am just testing here. Seeing this judder is nauseating and I can't be
> dealing with code too."***

**The wearer reports what it LOOKED LIKE. The session reads the logs, forms the
interpretation, and hands back one instruction.** A handover that asks him to
check a counter, save a log or judge a caveat is a handover that has moved work
onto the one person who cannot do it while wearing the thing.

**Acted on, not just recorded:** `vr.ps1` now archives the previous `gevr.log`
into `gevr-logs\` on every launch, tagged with the flags that produced it. The
"copy gevr.log after anything interesting" instruction that has stood since
Phase 2 had already lost one full crash stack trace and one T4 baseline. **It
was never a discipline problem; it was a chore assigned to the wrong moment.**
