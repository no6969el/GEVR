# 162 — P0. THE AIM KNOB WAS OFF, THE CONTROLLERS DID BIND, AND TWO BOARD ITEMS ARE WRONG.

**2026-08-25. P0-2 done. No launch spent. `161` P0-1 and P0-3(a) are CORRECTED here.**

> ## THE ONE-LINE RESULT
>
> **`state=NEVER-CALLED` on all 117 samples. Not `APPLIED`, not `REFUSED` — a
> THIRD state the board did not anticipate, and it means `GE_VR_AIM_FROM_HAND`
> was never set. A1c has still never actually been evaluated.**

---

## 1. WHAT THE LOG SAYS

`gevr.log`, 548 KB, last written **2026-08-25 02:13**. 234 AIM lines, 117 samples.

```
[gevr] 6dof: AIM(docs158) state=NEVER-CALLED(knob off?) fwd=0.000 ndc=(0.000,0.000)
[gevr] 6dof: AIM fwdHead=(-0.831,-0.261,-0.492)
```

`state=` tally: **117 NEVER-CALLED, 0 REFUSED, 0 APPLIED.**

## 2. WHY IT IS `NEVER-CALLED` AND NOT `REFUSED` — AND THIS ACQUITS THE GEOMETRY

`rt64_render_context.cpp:1128` sets `g_geVrAimDbgState = 0` (REFUSED) **after**
its guard. A state stuck at `-1` means the guard returned. The guard has two
live clauses and one of them is ruled out by the log itself:

| clause | verdict |
|---|---|
| `!g_geVrHaveHandPos[hand]` | **RULED OUT.** `:1350` sets it true, and `g_geVrAimFwdHead` (`:1333`) is computed downstream of it and is NON-ZERO and MOVING in the log |
| `!enabled` | **THIS IS IT.** `static const bool enabled = ge_vr_env_float("GE_VR_AIM_FROM_HAND", 0.0f)`, and `vr.ps1:602` only sets that variable when `-AimFromHand` is passed |

**THE LAST RUN WAS LAUNCHED WITHOUT `-AimFromHand`.** The standing command in
`HANDOVER.md` contains it; whatever produced this log did not.

> **SO "A1c IS STILL MIS-AIMED, UNTUNED" WAS JUDGED ON A BUILD WHERE THE AIM PATH
> NEVER RAN.** Nothing about the `158` §5 derived ray has been measured yet.
> That is the whole finding, and it is why P1-2 was reordered rather than tuned.

## 3. ►►►► P0-1 IS CORRECTED. THE CONTROLLERS DID BIND. ◄◄◄◄

```
[gevr-xr] xr input: bound profile = /interaction_profiles/oculus/touch_controller
```

**NOT `NONE BOUND`.** And `ctrlR viewrel=(6.0,-56.4,-27.3)u quat=(-0.812,...)`
is live per-sample pose data that changes frame to frame.

**`161` P0-1's second hypothesis is answered from the disk, with no launch: the
Pimax Crystal Super presents as OCULUS TOUCH, not Valve Index.** The
`handValid=0` reading came from an earlier build — **the string `handValid=` does
not appear anywhere in this log.**

**P0-1 IS NOT THE BLOCKER THE BOARD SAYS IT IS.** What remains of it is a
one-line confirmation in the current build, not an investigation.

## 4. ►►►► P0-3(a) IS WRONG AND WAS NOT APPLIED. ◄◄◄◄

`161` says to make `GE_VR_AIM_FWD_NEG` default `0` because *"`-AimFwdNeg 0` is
what cleared the refusal."* **THAT EVIDENCE IS FROM BASIS 0 AND DOES NOT
TRANSFER.**

`158` §3's refusal (`fwd=-0.303`, `row3=(-0.45,-0.84,0.30)`) was measured with
`GE_VR_AIM_BASIS 0` — R's third row. **`158` §5 then made basis 2 the default and
inverted the sign convention. `161` carried the old knob advice forward anyway.**

Under basis 2, `g_geVrAimFwdHead` is in the head's frame, OpenXR looks down `-Z`,
and the file's own comment at `:1095` says *"the forward component is `-v[2]`"*.
**The log agrees decisively:**

| `fwdHead` z | samples |
|---|---|
| **negative** | **97** |
| positive | 1 |
| zero | 19 |

Range to `-0.995`. So `fwd = -z` is POSITIVE and **`GE_VR_AIM_FWD_NEG 1.0` — the
shipped default — IS CORRECT.**

> **APPLYING P0-3(a) WOULD HAVE MADE `fwd` NEGATIVE AND TRIPPED THE `fwd < 0.05f`
> REFUSAL ON EVERY FRAME — RE-CREATING THE EXACT FAULT P0-2 WAS MEANT TO
> DIAGNOSE.** Left at `1.0` deliberately, with the reasoning in the code.

## 5. P0-3(b) IS APPLIED — THE NDC CLAMP

`rt64_render_context.cpp`, `aim_screen_ndc`. `fwd` is only tested against
`0.05f`, so a near-edge-on gun divides by a near-zero and throws
`ndc=(-8.5,-17.9)`. **That is the "it shoots the ground" report: the crosshair is
not aimed low, it is flung twenty screens off the frame and the integrators chase
it.** Clamped to `±2` — NDC is `[-1,1]` by definition and `±2` leaves a full
screen of overshoot for the clamp split (P1-5) to work against.

**GATE: unset build is character-for-character identical** — the whole function
is behind `GE_VR_AIM_FROM_HAND` and returns at the guard when it is off.

## 6. WHAT IS NOT A BUG, RECORDED SO IT IS NOT RE-FOUND

`enabled` is a **function-level `static const`**, latched on first call. That is
correct as long as the environment is set before process start, which `vr.ps1`
does. **It only becomes a problem at P2-5 (`vr.json`, hot reload)** — hot-reloading
the aim knobs will need this latch removed. Not a defect today.

## 7. WHAT THIS CHANGES ON THE BOARD

- **P0-1** — rewrite, do not tick. The profile question is ANSWERED. What is left
  is a confirmation, not a blocker.
- **P0-2** — **TICK. This document.**
- **P0-3** — (a) **REFUSED WITH CAUSE**, see §4. (b) **APPLIED.**
- **P1-2** — **promoted.** With the estimator never having run, there is nothing
  to tune and no reason to try. Go straight to the projection. See `163`.
