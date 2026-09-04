# 223 — MTXREC: RECORD THE INPUTS, STOP GUESSING THE FORM

**2026-08-26. Tiers per `182`. BUILT, RUN, DATA CAPTURED, ANALYSIS UNFINISHED.**

---

## §1 — WHY

**`221` shipped `-BulletFrame` with two candidate compositions. BOTH WERE WORN AND
BOTH WERE WRONG.** `48`'s method finding, again: **every recording answered its
question in one run; every guess had to be corrected by the next measurement.**

**The family is larger than two.** The composition order **and** the transpose on
the final multiply are independent choices — **at least four members, one wear
test each.** So this stops guessing and records the **inputs**.

**`[MEASURED]` per shot, at fire time only** (the aim block runs per frame and
would flood the log — `133`'s stale-log trap starts as a big log):

```
[gevr] MTXREC cam=(9 floats) thr=(9 floats) ray=(3 floats)
```

`cam` = `gunmtx_camspace` rotation, `thr` = `throw_item_pos_related` rotation,
`ray` = the play-space aim ray actually fired.

**With these in the log, EVERY composition and transpose is testable OFFLINE,
forever, with no rebuild and no further wear test.**

**NEW SYMBOL `recomp_ge_vr_frame_report = 0x8F000184` — `136`, build twice.**
Wired in five places: `syms.ld`, `misc_funcs.h`, `recomp_api.cpp`,
`rt64_render_context.cpp`, `ge_vr_host.h`.

---

## §2 — WHAT THE RUN MEASURED

**`[MEASURED]` 11 MTXREC records, three groups, including a physical 180° turn.**

### 2.1 A FIT I RAN THAT WAS WRONG, AND IS WITHDRAWN

**I tried to recover ONE `ViewToWorld` across all 11 shots by least squares.
Residual `119.2 deg` mean. THE MODEL WAS WRONG:** the owner **turned** during the
run, so the camera is not constant and **no single matrix can fit.**

> **THAT FIT IS VOID AND CARRIES NO TIER. It is recorded here only so the next
> session does not repeat it.** `48`: an instrument must be able to say
> **I CANNOT ANSWER THIS** — and a 119° residual is that instrument saying so.

### 2.2 WHAT DID SURVIVE — THE COMPOSITION IS NOT THE BUG

**`[MEASURED]` ranking the 8 candidate compositions against the recovered matrix,
`thr*camT` ranks first (10.5 deg).**

**`[READ]` `gunfire.c:570-574` says exactly that in source:**
```c
throw_item_pos_related = ViewToWorld x gunmtx_camspace
  =>  ViewToWorld = thr x cam^-1  =  thr * camT
```

**THAT IS ALREADY `-BulletFrame 1`, THE DEFAULT, AND IT HAS BEEN RUNNING ALL
ALONG.** **So the composition was never the fault — and `217`, `221` and two wear
tests were spent varying the wrong thing.**

### 2.3 THE SIGNATURE, FROM `220` AND TONIGHT

**`[MEASURED]`** error **constant to ±3 deg within a group**, jumping between
groups (`+151`, `+179`, `+60`). **`[MEASURED]`** pitch tracks well
(controller `+0.6/+34.3/-6.4` vs bullet `+3.7/+29.0/-4.9`).

> **A FIXED ROTATION FOR A FIXED CAMERA THAT CHANGES WHEN THE CAMERA TURNS IS A
> CAMERA-DEPENDENT TERM.** This rules out the cone clamp, the muzzle, the seam and
> the barrel offset — **all camera-independent.** **Yaw-only, so the fix is a
> rotation about one axis, not a rebuild of the chain.**

---

## §3 — THE STANDING HYPOTHESIS, NOT YET TESTED

**`[INFERRED]`, and the counter-example search is NOT yet done, so `182` says
THIS MAY NOT BE BUILT ON:**

> **We apply a CAMERA->WORLD matrix to a PLAY-SPACE ray.** `ray` is raw play
> space; `ViewToWorld` expects a camera-space vector. **The missing term is
> play->world — which changes exactly when the owner turns and is constant when
> he does not.**

**That matches the §2.3 signature and it is `194` again.** **It is also cheap to
test: the data is already captured.**

**THE OFFLINE TEST, which needs NO wear test and NO rebuild:** for each shot
compare the current `v2w^T . ray` against `v2w^T . (H . ray)` and
`v2w^T . (H^T . ray)`, where `H` is the head rotation from `POSEREC hq`. **Whichever
minimises the angle to the observed bullet direction is the answer.**

### A PARSING TRAP THE NEXT SESSION WILL HIT

**`[MEASURED]` `MTXREC` and `POSEREC` SHARE A LINE — there is no newline between
them in `gevr.log`.** A state machine that expects one record per line silently
produces **zero** complete records. **Parse by regex over the whole file and zip by
index; do not pair by line.**

---

## §4 — WHAT IS OWED

1. **RUN §3's OFFLINE TEST. The data is in `gevr.log` already.** No wear test.
2. **If the head term wins, build it** — one term, `-HeadFrame` knob, keep the old
   path reachable (**DELETE NOTHING**).
3. **`-BulletFrame` stays** but §2.2 means form 1 is correct and the knob is no
   longer the live question. **Mark it settled, do not remove it.**

**NOTHING STAGED. THE COMMIT IS THE OWNER'S.**
