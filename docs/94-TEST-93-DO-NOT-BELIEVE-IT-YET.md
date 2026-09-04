# 94 — THE TEST FOR `93`, AND WHAT `93` OVER-CLAIMED

**2026-08-23, immediately after `93`, at the owner's insistence: *"we can't just
change routes off what I said, what if I was wrong. We should test it."***

**He is right, and this document exists because he was right rather than because
the process caught it.**

---

## 1. WHAT `93` DID WRONG

**`93` §7 says, correctly: *"That the mismatch is THE judder the wearer feels is
a HYPOTHESIS."* And then every header in the document, and every navigation doc
it edited, treated it as a finding.**

| What `93` did | Why it was too much |
|---|---|
| Titled itself **"THE JUDDER IS A POSE/IMAGE MISMATCH"** | It is a *candidate*. The title is a conclusion |
| Wrote **"the wearer's three answers ELIMINATED all three candidates"** | Three sentences of description do not eliminate anything. **`47`: "the right eye looks skewed" turned out to mean "the right eye is not being rendered."** Descriptions have been wrong in this project in exactly this way |
| **Demoted `23` on the strength of one sentence**, three hours after `92` promoted it on the strength of a different theory | Two re-rankings in one afternoon, neither from a number |
| Rewrote `00`, `39` and `HANDOVER` to lead with it | **The navigation docs now point the next session at an untested hypothesis as though it were the state** |

### AND ONE ANSWER WAS USED FOR WORK IT CANNOT DO

> **`92` question 1 — *"stand still and look at a wall: does it judder?"* — is a
> BADLY DESIGNED QUESTION and its "no" eliminates nothing.**
>
> **A static scene viewed by a static head cannot show judder under ANY
> hypothesis**, because judder is a property of motion. **Every candidate
> predicts "no" here.** `48` rule 2, turned on the question instead of the code:
> **what would this question have to answer differently for any candidate to
> fail? Nothing. It is not a gate.**
>
> **`93` used that "no" to kill the 2:3 cadence. That reasoning is withdrawn.**
>
> **What DOES bear on the cadence is answer 2 — *"if I turn slow it's fine."***
> Film-pulldown judder is classically **worst on slow, smooth pans**. "Slow is
> fine" argues against it properly. **One real argument, not three.**

**So the honest state: `92`'s candidates are RE-RANKED, not eliminated.
`93`'s mechanism is a new candidate — a strong one, and the only one with a
confirmed structural defect behind it — but it is candidate 4, not the answer.**

---

## 2. WHAT IS FACT AND WHAT IS NOT

| | |
|---|---|
| **FACT, read from source** | `projViews[eye].pose` is assigned from **this present tick's** `xrLocateViews`, while the texture beside it is **whatever RT64 last produced**. `ge_vr_xr.cpp:1258`, `:1518`, `:1533`. **Not in question** |
| **FACT** | At ~60 rendered into ~90 presented, **some submissions must reuse an unchanged image**. Arithmetic |
| **FACT** | `28` documented one-frame staleness in Phase 2 |
| **HYPOTHESIS** | That this mismatch is **what the wearer feels** |
| **UNKNOWN, AND IT MATTERS** | **Whether the runtime reprojects anyway.** Pimax OpenXR 0.1.0's behaviour is not established. **A compositor that applies its own late-stage warp regardless would blunt or erase the effect — and `93` never checked** |

> **That last row is the one that could make `93` wrong while every fact in it
> stays true**, and it is exactly the shape of `49`: *a* cause, not *the* cause.

---

## 3. THE TESTS — ranked by cost, and NONE depends on a description

**The point of every test below is that it produces a NUMBER or a
FALSIFICATION, so the wearer's report is corroboration rather than evidence.**

### T1 — THE MIRROR RECORDING. No code, no build, ~10 minutes.

**`47` built this method and it separates exactly these two worlds.**

1. Record the headset mirror while turning the head **fast**.
2. Watch the recording.

| Mirror | Lenses | Means |
|---|---|---|
| **smooth** | **judders** | **The IMAGES are right; the POSE submitted with them is wrong.** `93` survives |
| **judders too** | judders | **The images themselves are bad. `93` is WRONG** and the fault is upstream of the submit |

> **A mirror shows the submitted IMAGE and never the metadata.** That is why
> `47` works, and it is the cheapest discriminator available. **Do this first.**

### T2 — G93-1, THE NUMBER. Two lines, ships with S0's build.

**Log, per submission, the angular difference between the pose the frame was
RENDERED from and the pose it is SUBMITTED with — with a max, not a mean.**
(`72`'s means hid a hitch; `00`'s fifteenth instrument warning.)

| | |
|---|---|
| **PREDICTION** | **Non-zero, and the max grows with head angular velocity** |
| **KILLS `93` IF** | **It prints ~0.** Then the two poses already agree and there is nothing to fix |
| **What it would print if it were looking at the wrong thing** | If it compares a pose against **itself** — the same failure as `49`'s "upload verdict" comparing two adjacent struct members — **it prints 0 on every build, working or broken.** **State which two variables it reads, in the log line itself** |

### T3 — G93-2, THE REUSE COUNT. One line, same build.

**Count submissions that copy an unchanged rendered image. PREDICTION: roughly
one in three.** Zero would mean RT64 renders per submission and `93` §2.2 is
wrong.

### T4 — **THE KNOB THAT MAKES IT WORSE ON PURPOSE.** The decisive one.

**`56`'s method — the best thing in this project's toolbox: remove or alter a
thing and see whether the result changes.** `-SkipEye` cracked B1 after five
wrong predictions about which input was faulty.

> **Add `GE_VR_POSE_LAG=N`: deliberately submit a pose N present-ticks OLD
> instead of the fresh one.**
>
> | Setting | Predicted, if `93` is right | Predicted, if `93` is wrong |
> |---|---|---|
> | `N = 0` (today) | today's judder | today's judder |
> | **`N = 4`** — a large, unmissable lag | **Dramatically worse on fast turns, and ONLY on fast turns** | **No change** |
> | **`N = -1`** — submit the pose the image was ACTUALLY rendered from | **Materially better** | No change |
>
> **`00`: when a human is the instrument, use a step nobody could miss.** 100 vs
> 50 units/metre was reported as *"it looks the same"* while the log showed the
> separation genuinely halving; a 4x step answered it in one launch. **`N = 4`
> is that step.**
>
> **And this is the test that does not care whether the owner's description was
> right.** It asks a different question — *does moving this quantity move the
> symptom?* — and a "no change" at `N = 4` **kills `93` outright** no matter what
> anybody felt.

---

## 4. THE ORDER, AND WHAT IT COSTS

```
T1  mirror recording        no code, no build, ~10 min   -> image fault vs pose fault
T2  G93-1 angular delta  ─┐
T3  G93-2 reuse count     ├─ two or three lines, ONE build, ships WITH S0
T4  GE_VR_POSE_LAG       ─┘   (N=0 default: an unset build is unchanged)
```

**All three code items are diagnostics and batch freely** — `48`'s amended rule
5: they cannot regress anything. **`GE_VR_POSE_LAG` defaults to 0, which is an
exact identity, so the shipped behaviour is untouched.**

**Then ONE wear session answers T1, T4 and S0's own gates together.**

---

## 5. WHAT GETS REVERTED UNTIL THE TESTS RUN

**Rule 10 applied to `93`, hours old.**

| | |
|---|---|
| **`23`** | **Back to OPEN and UNRANKED.** `92` promoted it, `93` demoted it, neither from a number. **It is a known real defect either way** |
| **`92`'s three candidates** | **RE-RANKED, NOT ELIMINATED.** Answer 1 does no work at all; answer 2 argues against the cadence properly; answer 3 argues against `73` and is corroborated by `92`'s 142-of-149 measurement — **which is a number, and stands** |
| **`93`'s mechanism** | **Candidate 4.** The only one with a confirmed structural defect behind it, and still a candidate |
| **`00`, `39`, `HANDOVER`** | **Re-worded to say CANDIDATE, and to point at these tests rather than at a fix** |

---

## 6. THE RULE THIS EARNED, AND THE OWNER FOUND IT

> ### A WEARER'S REPORT IS A LEAD, NOT A MEASUREMENT — AND THE MOMENT IT AGREES WITH YOUR THEORY IS THE MOMENT TO DISTRUST IT.
>
> **`00` says the wearer is the best instrument in this project, and that is
> true: three faults in `79` were diagnosed from description alone.** But `47`
> is the other half of it — *"the right eye looks skewed"* meant *"the right eye
> is not being rendered"* — **and this document exists because a description
> that fitted a freshly-formed theory was promoted to a finding within the
> hour.**
>
> **The tell was availability, not evidence: three sentences arrived, one
> expression fitted all of them, and the fit felt like proof.** `48` already
> warns that five hypotheses were falsified in `49`, *"each plausible, each from
> reasoning about a mechanism instead of measuring it."* **This was the sixth,
> and it was caught by the owner rather than by the protocol.**
>
> **Proposed addition to `48`:** *"When a wearer's description CONFIRMS the
> hypothesis you are currently holding, write the test before you write the
> conclusion. A description that surprises you is evidence; a description that
> flatters you is a lead."*

**Nothing here is built. `48` rule 1.**
