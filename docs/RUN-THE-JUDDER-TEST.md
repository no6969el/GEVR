# RUN THE JUDDER TEST — `94` T1-T4, one card

**Written 2026-08-23. The code is in the tree and has NEVER been compiled.
Nothing here changes shipped behaviour: `GE_VR_POSE_LAG` defaults to 0, which
is an exact identity.**

---

## STEP 0 — BUILD

```powershell
cd C:\Users\pdbar\Desktop\GoldenEye64Recomp
.\build.ps1
```

**No new `RECOMP_PATCH` name was added, so this is the SHORT path.**
Four files changed: `include/ge_vr_host.h`, `src/main/ge_vr_xr.cpp`,
`src/main/rt64_render_context.cpp`, `vr.ps1` — **plus slice S0 from `91`, which
is in the same build and has also never been compiled.**

**If it does not compile, that is expected work.** Paste the errors.

---

## STEP 1 — T1, THE MIRROR. NO CODE NEEDED. DO THIS EVEN IF THE BUILD FAILS.

`47`'s method, and it is the cheapest discriminator in the project.

1. Start a session, record the headset mirror (e.g. "Pimax Mirror - Both").
2. **Turn your head FAST**, the speed that makes it bad.
3. Stop, exit properly, **watch the recording**.

| Mirror | Lenses | Verdict |
|---|---|---|
| **smooth** | juddered | **The IMAGES are right; the POSE submitted with them is wrong. `93` SURVIVES** |
| **juddered too** | juddered | **The images themselves are bad. `93` IS DEAD** and the fault is upstream of the submit |

**A mirror shows the submitted IMAGE and never the metadata. That is the whole
trick.**

---

## STEP 2 — T4, THE DECISIVE ONE. Three launches, A/B/A.

```powershell
.\vr.ps1 -UnitsPerMetre 50 -SeamNoRot -HandPosZ 1                 # A: today
.\vr.ps1 -UnitsPerMetre 50 -SeamNoRot -HandPosZ 1 -PoseLag 4      # B: made worse
.\vr.ps1 -UnitsPerMetre 50 -SeamNoRot -HandPosZ 1 -PoseLag 0      # A again
```

**PUT THE HEADSET ON, THEN PRESS `F9`. Exit with
`taskkill /F /IM GoldenRecomp.exe` — NEVER the X.**

**In each: turn your head FAST, then SLOW. Nothing else.**

| What you feel at `-PoseLag 4` | Means |
|---|---|
| **Much worse, and only on FAST turns** | **`93` SURVIVES.** The submitted pose is load-bearing |
| **The same as `-PoseLag 0`** | **`93` IS DEAD**, whatever the earlier description suggested. The pose we submit is not what you are feeling |
| Worse on slow turns too | Neither prediction. Say so — it is a third answer and it is informative |

> **This is the test that does not depend on your description.** It asks
> *"does moving this quantity move the symptom?"* — and a "no change" kills the
> theory no matter what anybody felt. **`56`'s method: remove or alter a thing
> and see whether the result changes. It cracked B1 after five wrong
> predictions about which input was faulty.**
>
> **The A/B/A order matters.** Going back to 0 at the end guards against
> "everything feels worse the longer I wear it", which is a real effect and
> would otherwise read as a positive result.

---

## STEP 3 — T2/T3, THE NUMBERS. Free, from the same launches.

After each session, in `gevr.log`:

```
[gevr] posecheck: MAX delta N.NN deg (rendered-from[game thread] vs
       submitted[present thread]) | submits=NN renders=NN reused=NN | POSE_LAG=N
```

| Field | **PREDICTION** | If it fails |
|---|---|---|
| **MAX delta** | **> 0, and BIGGER in the second when you turned fast** | **~0.00 always -> `93` IS DEAD.** The two poses already agree |
| **submits vs renders** | **submits ~90/s, renders ~60/s** | Equal -> RT64 renders per submission, `93` §2.2 is wrong |
| **reused** | **~30/s, about one submission in three** | 0 -> same as above |

**MAX, not mean, deliberately.** `72` exonerated the submit loop on means and
`00`'s fifteenth instrument warning is that **a mean cannot see a hitch, and
judder is nothing but hitches.**

**A `0.00` here is a REAL RESULT, not a broken instrument.** The two
orientations are read from different threads by construction and the log line
names both — this is not `49`'s "upload verdict" comparing two adjacent struct
members against each other.

---

## STEP 4 — WHILE YOU ARE IN THERE, S0's OWN GATES (`91`)

Same launches, no extra cost. In `gevr.log`:

| Check | Pass |
|---|---|
| `[gevr] 6dof:` lines appear, every field labelled with its frame | G0-1, G0-2 |
| `.\vr.ps1 -NoXr` prints **no** `6dof` line | G0-3 |
| **`muzzleExt`** | **PREDICT > 0.** If negative, `88` §5.1 inverts and slices G2/A1 change shape |
| **`A40`** | **PREDICT < 0** (about -1000) |

---

## WHAT TO SEND BACK

1. **T1: mirror smooth or juddering?**
2. **T4: is `-PoseLag 4` worse, same, or worse-in-a-different-way?**
3. **The `posecheck` lines from each log.**
4. **`muzzleExt` and `A40`.**

**Keep the logs — `gevr.log` is rewritten every launch:**

```powershell
copy gevr.log gevr-keep-poselag0.log
copy gevr.log gevr-keep-poselag4.log
```

**A full crash stack trace was lost this way once.**
