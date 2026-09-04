# 91 — SLICE S0, THE 6DoF INSTRUMENT, AS BUILT

**2026-08-23. `86` §5: "Slice 0 is an instrument and it ships first."
Written, not yet compiled, not yet worn. `48` rule 11: this does not move to
DONE until it has been OBSERVED.**

---

## WHAT WAS BUILT, AND WHERE

**Two halves, because the quantities live in two places and no single function
can see both.**

| Half | File | Prints |
|---|---|---|
| **Host** | `src/main/rt64_render_context.cpp`, inside the existing once-a-second `useHead` block | head position **in play space**, height above origin, **recentre yaw in degrees**, the right controller **head-relative**, its quaternion, the scale trio |
| **Game** | `patches/ge_vr_bindtest.c`, inside the **already-patched** `viSetFovY` | the bullet quantity, the gun-pointing quantity, both integrators with their damping, the **widened** camera scale, the crouch state, and the two falsifiers |

**Supporting change:** `HeadView` gains `originYawDeg` (`include/ge_vr_host.h`),
filled in `src/main/ge_vr_xr.cpp` beside the origin position it must agree with.

> ### NO NEW `RECOMP_PATCH` NAME. THIS REBUILDS ON THE SHORT PATH.
>
> **`viSetFovY` is already patched and already runs every frame** — `lvlRender`
> re-sets it, and the front end calls it from eight places. **Putting the
> game-side instrument there costs no new name**, so `07` GOTCHA 2's long build
> with `tools_weaken_patched.py` is not required. **`87` read 6 asked for the
> new names to be counted before the first build rather than after it failed
> silently. The count for S0 is zero.**

---

## THE DESIGN DECISION THAT IS NOT COSMETIC

**A quantity that is not built yet prints `n/a`, never `0.0`.**

```
recentreYaw=12.4deg bodyYaw=n/a(H3-not-built)
ctrlR viewrel=n/a quat=n/a (valid=0 focused=0 handValid=0)
```

> **Gate G0-1 is *"every field is non-zero and moves when the corresponding
> physical thing moves"*, and its stated failure mode is a FROZEN number** —
> the shape of `32`'s dead eye-sign knob and `80`'s knobs with deleted
> consumers.
>
> **A zero is indistinguishable from a frozen tracked value.** So printing
> `bodyYaw=0.0` for a quantity slice H3 has not built would manufacture a G0-1
> failure out of a feature that simply does not exist, and the next session
> would go looking for a tracking fault. **`n/a` with the reason attached
> cannot be misread.**
>
> **Same for the controller block**: with no focused session it prints
> `valid/focused/handValid` rather than stale poses, because `61` risk 2 is that
> *"no input"* and *"not focused"* are different states that look identical.

---

## WHAT IT WOULD PRINT IF IT WERE LOOKING AT THE WRONG THING

**`52`'s census cost one launch instead of a session because it said this before
it ran. Both halves say it, in the source, above the code.**

| | |
|---|---|
| **The game half cannot latch on a MENU** | It is gated on `geVrWorldCamera()` — in a level, not demo, `CAMERAMODE_FP`/`MP`. **`39` O28 is the `fb eye` probe one-shotting on a menu workload** |
| **The scale figures are the WIDENED ones, and say so** | `87` read 3: `currentPlayerSetCameraScale()` has just recomputed `c_scalex`/`c_scaley` from the **106°** fovy. `viGetFovY` divides the widening out for the *game's* readback and **not** out of these. **Anyone inverting `transformAndNormalizeByLength2Dto3D` for A1 must use these numbers** |
| **G0-3, `-NoXr` prints nothing** | The host block sits under `useHead`, false without a session; the game block under `geVrWorldCamera()`. **`59`'s shape — a VR instrument firing where VR is off** |
| **The falsifier needs no code** | **Cover the headset's sensors. Every tracked field must freeze TOGETHER.** If one keeps moving it is not reading tracking |

---

## THE TWO FALSIFIERS IT CARRIES — `90`

**Printed with their predictions inline, so the reader does not have to hold
`88` in their head. `48` rule 2: the gate before the run.**

| Field | **PREDICTION** | If it fails |
|---|---|---|
| `muzzleExt` (`MuzzleFlashExtension` ×100) | **> 0**, for every weapon | The model's barrel is local **−Z** and **`88` §5.1 is inverted** — which inverts the aim-axis reasoning under slices G2 and A1 |
| `A40` (`hands[0].field_A40`) | **< 0**, about −1000 | `initBondDATA.c:114` initialises it to **+1000**, the opposite sign. **`88` §5.1 leans on the runtime sign being negative** |

**Neither can be answered from the tree.** The weapon stats are ROM data
(`gitem_structs[item].item_weapon_stats`, `gun.c:712`), so `muzzleExt` is the
one part of read 11 that is genuinely an instrument rather than a read.

**And the line labels the bullet bluntly**, because `86` §3.8 and `87` finding 1
both had it backwards:

```
[gevr] 6dof-game: BULLET crosshair_angle=(320,120)px CLAMPED
                | GUNPOINT field_FFC=(340,118)px unclamped | aim A38/A3C/A40=(...)
```

---

## A CONDITIONAL-COMPILATION FAULT, CAUGHT BEFORE THE BUILD

The instrument needs `get_ptr_item_statistics`, `get_item_in_hand_or_watch_menu`
and `g_geVrSeamWrites`. **These were declared beside the `83` seam, which sits
at line ~995 — AFTER `viSetFovY` at ~515, and OUTSIDE the
`#if GE_VR_MODE == GE_VR_MODE_HOSTEYE` block that contains it.**

**First attempt moved them up into the HOSTEYE block. That compiles under
HOSTEYE and breaks every other mode**, because the seam outside would then
reference symbols that no longer exist.

**They now sit before the `#if`, outside all mode conditionals, with the reason
in a comment.** **This is `48` rule 6 — check who else reads what you write — in
its conditional-compilation costume, and it was caught by reading the `#if`
boundaries rather than by a failed build.** Sixth instance of that rule.

---

## AND A COUNT CORRECTED, WHICH IS EMBARRASSING IN THE RIGHT WAY

**`87` read 6 corrected `00`'s stale "31 renamed" to "47 unique names across 48
sites". That was also wrong. The true figure is 45 unique across 46 sites**,
one name duplicated (`select_ramrom_to_play`, under opposing `#if`).

> **`87`'s regex matched COMMENT PROSE** — sentences *about* `RECOMP_PATCH`
> naming, including one in `87`'s own subject matter. **An instrument that
> counted itself.**
>
> **`48` rule 4: verify the instrument before trusting the test — and this was
> a one-line `grep` written while correcting somebody else's stale number.**
> Corrected at source in `87` and `00`. **Rule 10, applied to my own document,
> which is the only version of rule 10 that means anything.**

---

## THE GATES, AND HOW TO RUN THEM

**Build — SHORT path, no new patch name:**

```powershell
cd C:\Users\<USER>\Desktop\GoldenEye64Recomp
.\build.ps1
```

**Then, worn — and `86` §5's standing preconditions apply:**

```powershell
.\vr.ps1 -UnitsPerMetre 50 -SeamNoRot -HandPosZ 1
# PUT THE HEADSET ON, THEN PRESS F9.  O60, three confounded launches already.
# EXIT:  taskkill /F /IM GoldenRecomp.exe    NEVER the X - B3/B4
```

| Gate | Pass |
|---|---|
| **G0-1** | Every tracked field is non-zero and **moves when the physical thing moves**. Crouch: head `y` clearly negative. Move the controller: `ctrlR viewrel` follows |
| **G0-2** | **Every field states its frame.** `head play=`, `ctrlR viewrel=`. Already true by construction — read the line and confirm |
| **G0-3** | **`.\vr.ps1 -NoXr` prints no `6dof` line at all** |
| **FALSIFIER** | Cover the sensors: every tracked field freezes **together** |
| **`90`-1** | `muzzleExt` **> 0** |
| **`90`-2** | `A40` **< 0** |

**A regression check that costs one launch and must not be skipped:**
`.\vr.ps1 -NoXr` must still be a normal game. **The instrument touches
`viSetFovY`, which every path calls** — including the one that must never break.

---

## WHAT IS NOT DONE

- **Not compiled.** The build runs on the Windows side; this session edits the
  tree from the Linux bridge and cannot invoke MSBuild.
- **Not worn.** `48` rule 11: **nothing moves to DONE until it has been
  OBSERVED**, and `33` exists because two slices were called finished on a build
  nobody had worn.
- **`eyeheight` is not printed** — it is absent from `patches/structs.h`. **Said
  out loud in the log line itself** (`eyeheight=absent-from-patch-struct`)
  rather than omitted silently, because a missing field looks exactly like a
  field reading zero. **H2 will need it, and read 10 named the function that
  owns it: `bondviewUpdatePlayerCollisionPositionFields`.**
- **Next slice is H1**, the recentre at level start — `86` §6. Not before S0 is
  worn.
