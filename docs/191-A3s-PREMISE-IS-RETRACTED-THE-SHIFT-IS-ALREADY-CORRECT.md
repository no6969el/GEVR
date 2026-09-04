# 191 — `A3`'s PREMISE IS RETRACTED. THE HUD SHIFT IS ALREADY EXACTLY RIGHT, AND THE NEXT TEST NEEDS NO BUILD AT ALL.

**2026-08-25. Tiers per `182`. Written BEFORE any A3 code was touched.**

---

## §1 — ►►►► `185` `A3` SAYS THE SHIFT IS 32% TOO MUCH. IT IS NOT. ◄◄◄◄

**THE CLAIM UNDER TEST**, `185` `A3`, tiered `[INFERRED]`:
*"from this run's tangents (`eye0 -1.3760, 1.0358`) the cyclopean term is
`(tanR+tanL)/(tanR-tanL) = -0.1411`, **not 0.1867 — about 32% too much.**"*

**`[READ]` `rt64_render_context.cpp:1083`. THE FORMULA IN THE CODE IS ALREADY
THAT EXPRESSION**, sign-derived and documented at length in `173`:

```c
float ndc = -((tanRight + tanLeft) / (tanRight - tanLeft)) * ge_vr_hud_sign();
```

**SO THE ONLY WAY IT COULD BE 32% WRONG IS IF IT WERE FED THE WRONG TANGENTS.
IT IS NOT — AND THE SAME LOG PROVES IT.**

**`[MEASURED]`, `gevr.log`, one run, three lines, AND THE ORDER IS THE WHOLE
ANSWER:**

| line | what it says | when |
|---|---|---|
| **12** | `[gevr]   tangents -1.3760 1.0358 ... overrideFrustum=1` | **STARTUP** |
| **41** | `[gevr-xr] eye 0 live tangents: -1.4869 1.0190 ...` | the runtime replies |
| **152** | `[gevr] 6dof: HUD shift=1 ... eye0=0.1867 eye1=-0.1867` | per frame |

**DO THE ARITHMETIC ON THE LIVE PAIR:**
`(1.0190 - 1.4869) / (1.0190 + 1.4869) = -0.4679 / 2.5059 = **-0.18672**`.
**THAT IS THE PRINTED VALUE, TO FOUR DECIMAL PLACES. THE SHIFT IS DERIVED
CORRECTLY FROM THE TANGENTS THE HEADSET ACTUALLY REPORTS.**

### AND WHERE `-0.1411` CAME FROM, BECAUSE IT IS AN HONEST-LOOKING MISTAKE
**`[READ]` `rt64_render_context.cpp:2836`: the `[gevr]   tangents` line is inside
`if (!loggedFull)`. IT IS PRINTED ONCE, AT STARTUP** — at log line **12**, which
is **twenty-nine lines BEFORE the runtime delivered any live FOV at all** (line
41). **It is the CONSTANT TABLE, logged before the headset had spoken.** Once
`useLiveFov` engages, `config.eyes[].tanLeft/tanRight` are replaced by
`tan(headView.fovAngles[])` — and **the one-time print never fires again to say
so.**

> **`185` `A3` COMPUTED THE "CORRECT" VALUE FROM A STARTUP CONSTANT AND COMPARED
> IT AGAINST A LIVE MEASUREMENT.** Two different numbers, one log, no way to see
> it without checking WHEN each line was printed.
>
> **THIS IS THE FIFTH TIME (`160`, `163`, `171` §3, `180`, now this) AND THE
> SECOND IN TWO DAYS.** `189` §2 was the same shape: a number measured correctly
> and compared against the wrong reference. **`182`'s rule caught it exactly as
> intended — `A3` carried `[INFERRED]`, so it got checked before it was built.**
>
> **HAD IT BEEN BUILT, WE WOULD HAVE DIALLED A CORRECT TERM DOWN BY 32% AND THEN
> TUNED AROUND THE ERROR** — which is `-AimGain`'s entire history (`163`).

**`185` `A3`'s instruction was *"derive it, do not dial it."* IT IS ALREADY
DERIVED. THE INSTRUCTION IS SATISFIED AND THE TASK AS WRITTEN IS VOID.**

---

## §2 — SO WHAT IS THE WEARER SEEING? THE LEADING CANDIDATE IS *NOT* A BUG.

**THE OBSERVATION STANDS AND IS NOT IN DOUBT** — `[REPORTED]`: *"the left eye's
right side of the cross and the right eye's left side overlap perfectly"*, the
two crosses **one crosshair width apart.**

**`[READ]`, `rt64_render_context.cpp:981-984`, THE PROJECT'S OWN WORDS:**
*"With canting alone the HUD sits at INFINITY: both eyes agree, which is the fix,
and a crosshair at infinity is comfortable and is what most VR shooters ship."*

**`[INFERRED]`, AND STATED AS SUCH: A CROSSHAIR AT INFINITY IS DOUBLE WHEN YOU
ARE NOT VERGED AT INFINITY.** The canting term places the HUD at infinity by
construction — parallel rays, zero convergence. **But the wearer is verged on a
gun about half a metre away, or on a guard across a room.** Anything at infinity
seen by eyes converged nearer is **physiologically double**, and it separates by
an amount that grows as the vergence target comes closer. **A crosshair-width of
separation is exactly the scale that produces.**

> **AND IT EXPLAINS WHY `173` WAS RIGHT AND THE SYMPTOM SURVIVED.** `173` fixed
> the DIVERGENT case — *"divergent is BEHIND infinity, where eyes cannot fuse"* —
> and landed on parallel, which is infinity. **The wearer confirmed the
> improvement at the time** (*"much closer now in my vision"*). **Parallel was the
> destination, and parallel is still not fused if you are looking at your gun.**

---

## §3 — ►►►► AND THE TEST FOR IT IS A KNOB THAT ALREADY EXISTS. NO BUILD. ◄◄◄◄

**`[READ]` `GE_VR_HUD_DEPTH` / `-HudDepth`, built in `170`, DEFAULT 0 = infinity,
`vr.ps1:189`.** Its second term is already derived and sign-checked:

```c
if (depth > 0.01f) ndc += -(eyeX_m / depth) / halfW;
```

**`ge_vr_hud_offset_ndc` documents the sign derivation:** *"an object at finite
depth D directly ahead of the head centre appears RIGHT of centre to the LEFT
eye... so the shift must be `-eyeX/D`, scaled into NDC by dividing by the
half-width tangent."*

**SO THE ENTIRE `A3` QUESTION IS ONE LAUNCH ARGUMENT ON THE BUILD ALREADY ON
DISK.** `-HudDepth 2.0` first, then **HALVE, NEVER NUDGE** (`159`): `2.0 -> 1.0 ->
0.5`. **The gate is `G-A3` unchanged: one fused crosshair, in the same world
place with either eye closed.**

- **A depth fuses it -> `A3` CLOSES as a DEFAULT CHANGE, not a code fix**, and the
  value the wearer picks is the finding. **Record it; do not leave it as a knob**
  (`174`'s trim is the cautionary tale).
- **No depth fuses it -> the infinity hypothesis is FALSIFIED**, the residual is
  something else, and `A3` is re-opened with §1's retraction still standing.

> **AND THIS IS WHY `-HudDepth` MUST BE SWEPT BEFORE ANY `A3` CODE IS WRITTEN.**
> A build spent on a term that is already correct (§1) would have been the FOURTH
> knob this project added to cancel an error that was not there.

---

## §4 — WHAT THIS DOES TO THE ORDER, AND IT IS GOOD NEWS FOR THE OWNER'S PRIORITY

**THE OWNER'S STANDING PRIORITY IS SHOT ACCURACY** — *"getting this hand tracking
right and the bullet leaving the gun."* `A3` was the last gate in front of
`B2`/`T7`, the near-wall/far-wall test that decides parallax versus a constant
angular error.

**`A3` NO LONGER NEEDS A BUILD, SO THE NEXT SESSION IS A PURE WEAR SESSION:**

1. **`-HudDepth` sweep, `2.0 -> 1.0 -> 0.5`.** Gate `G-A3`. No build, no rebuild
   between arms — **only the launch argument changes, which is `48` rule 5
   satisfied for free.**
2. **THEN `T7`/`B2` IN THE SAME SESSION, on whatever depth fused** (or on the
   default if none did, recording that it did not). **Shoot a wall at arm's
   length, then the same spot from across the room. Miss SHRINKS -> muzzle
   parallax, `B1` is the known cure. Miss HOLDS -> a constant angular error.**
   **`189` §2 removed `B2`'s other blocker**, so this is now reachable.
3. **`noPose`** (`190` §3) and **`U-21`/`U-22`** wait for the next build. **Do not
   build them into this session** — it is worth more as a no-build session.

**NOTHING STAGED. THE COMMIT IS THE OWNER'S**, both repos.
