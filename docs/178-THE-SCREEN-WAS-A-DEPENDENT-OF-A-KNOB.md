# 178 — T1 FAILED, AND THE VIRTUAL SCREEN WAS GATED ON A KNOB THAT IS OFF BY DEFAULT

**2026-08-26. First wear test of the `T1`-`T11` script. One-line fix, source only.**

> ## **THE MENUS WERE STILL RED AND BLUE — AND THE LOG SAID NEITHER `READY` NOR `UNAVAILABLE`.**
>
> **That absence IS the finding.** `175` §4 designed the fallback so the two
> states could never be confused: `READY` means the screen draws, `UNAVAILABLE`
> means the shader failed and you get the `docs\10` clear. **A THIRD STATE — the
> line not printing at all — was not anticipated, and it is the one that happened.**

---

## §1 — WHAT WAS WRONG

`ge_vr_xr.cpp:1031`: the screen PSO is built at the **BOTTOM of
`ge_vr_timewarp_create()`**, after `timewarp: READY`.

`ge_vr_xr.cpp:2128` is that function's **ONLY** caller:

```cpp
if (g_twEnabled > 0 && ge_vr_timewarp_create()) {   // 1 = delta, 2 = delta INVERTED
```

**`GE_VR_TIMEWARP` DEFAULTS TO 0.** The run's own log, line 16840:

```
[gevr-xr] timewarp: GE_VR_TIMEWARP=0 (docs\97)
```

So `ge_vr_timewarp_create()` never ran, `g_screenReady` was never set, `:2263`
fell through, and the menus cleared red/blue exactly as before.

**AND THE PRINT LIVES PAST THE EARLY RETURN**, which is why the log was silent
rather than reporting a failure. **A feature that is merely ungated looks
identical, in both the headset AND the log, to a feature that was never built.**

## §2 — THE FILE SAID SO, 1300 LINES EARLIER

`ge_vr_xr.cpp:739`, written for `97`:

> *"GE_VR_TIMEWARP=0 (the default) never reaches this code at all"*

**The warning was accurate, in the file, and above the code that then relied on
the opposite.** `171` §3's lesson for the third and fourth time: a claim in a
comment is not a substitute for following the call site.

## §3 — WHAT `175` GOT RIGHT, AND THE ONE THING IT DID NOT

**Sharing `g_twRoot` WAS correct** — same 16 root constants, same single SRV,
same static sampler, so only the shaders differ, and the root signature has to
exist either way. **Sharing the CALL SITE was not.** Creation and use are
separate concerns and this collapsed them.

## §4 — THE FIX

At `:2288`, in the no-eye-pair branch, immediately before the screen draw:

```cpp
if (!g_screenReady && !g_twTried) { (void)ge_vr_timewarp_create(); }
```

**IT DOES NOT TURN THE WARP ON.** The warp is gated independently at `:2128` on
`g_twEnabled`; this only builds PSOs. **`g_twTried` is set at the top of
`create()`, so this is a no-op after the first attempt — INCLUDING A FAILED
ONE**, and there is no per-frame retry of a shader compile.

**KNOWN AND ACCEPTED:** the first menu frame now pays a `LoadLibraryA` +
two `D3DCompile` calls inline. **One frame, in the front end, once per session.**

## §5 — WHY `GE_VR_TIMEWARP=1` WAS NOT THE WORKAROUND

It would have produced the screen — and **resampled every eye image through the
pose delta at the same time.** A real picture change riding under a test of
something else. `48` rule 5.

## §6 — AND `T2` PASSED IN THE SAME RUN

`Switches[3]` takes **TWO distinct values** across 301 samples:
`(0,5671,35025)` with `numSwitches=36` (300x) and `(-25715,129,0)` with
`numSwitches=7` (1x). **The switch COUNT differs too, so it is a different
weapon model and not noise.**

**U-18 PROCEEDS: per-weapon muzzles are free, and `-MuzzleExt` with its three
sign knobs becomes unnecessary.**

**One sample is thin.** Linger on the second weapon next run so it is twenty.

**And `flashExt=100` printed with `171`'s warning attached, exactly as intended
— `169` U-14 doing the job it exists for.**
