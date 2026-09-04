# 155 — G2. PD's BASIS TRANSFERS. PD's 90 DEGREE OFFSET DOES NOT.

**2026-08-25, worn, three launches. Both halves of `102`'s G2 were tested
separately and they gave OPPOSITE answers.**

---

## §1 — THE BASIS: CONFIRMED. `102` WAS RIGHT AND IT WAS A CHECK, NOT A SWEEP.

**`-HandAxisX -1 -HandAxisZ -1`** — our `R[i][j] *= sgn[i]*sgn[j]` at
`rt64_render_context.cpp:1105` is conjugation by `diag(sgn)`, and
`sgn = (-1,+1,-1)` **is exactly the `{w,-x,y,-z}` conjugation by a 180 degree Y
rotation** that `102` read out of `vr_input.cpp:1219-1225`.

> **WORN: the up/down inversion WENT AWAY, and `-HandAxisY -1` was NOT needed.**
> The wearer: *"That's a lot better now."*

**`148` 6D-08 said `102` downgrades G2 "from a sweep to a check". IT WAS A CHECK,
AND IT PASSED ON THE FIRST LAUNCH.** No sign sweep was ever run.

## §2 — THE POST-ROTATION: FALSIFIED AT BOTH SIGNS.

`102` also records PD right-multiplying by **1.5708 rad about X after smoothing**
(`vr_input.cpp:1317-1327`), with their own comment saying "1.0 rad" and being
wrong. **We had no equivalent, so `155` added `-HandRotXDeg`.**

| Run | Result |
|---|---|
| `-HandRotXDeg 90` (PD's value) | **DID NOT WORK** |
| `-HandRotXDeg -90` | **WORSE** |
| **`-HandRotXDeg` UNSET (0)** | **BEST. The standing configuration.** |

> ## **SO PD's ANGULAR OFFSET IS NOT OURS TO COPY, AND THE PROBABLE REASON IS STRUCTURAL: OUR `R` IS ALREADY HEAD-RELATIVE.**
>
> `R = Rhead * Rhand^T` (`:1099`, `79` correction 2). **PD's quaternion is
> play-space and their offset corrects grip-versus-barrel in THAT frame.** Ours
> has already been through a change of basis that theirs has not.
>
> **AND THE ASYMMETRY IS DATA: `-90` was WORSE THAN `+90`, and `0` beat both.**
> That is a minimum at or near zero with a positive gradient — **so if anything
> is owed here it is a SMALL positive angle, not PD's 90.** Not worth a launch on
> its own; batch it if another G3 run happens.

**THE KNOB STAYS, DEFAULTED TO 0 AND SKIPPED ENTIRELY AT 0**, so it costs
nothing and the question can be reopened without new code.

## §3 — `102` IS PRIOR ART, NOT A SPECIFICATION. FIRST MEASURED INSTANCE.

**`148`: "PERFECT DARK IS THE REFERENCE, NOT A SOURCE TO COPY."** Until now every
PD value that was checked had transferred. **This is the first one that did not,
and it transferred by HALF** — same document, same slice, two constants, one
right and one wrong for us.

> **THE RULE THAT EARNS: A PRIOR-ART CONSTANT IS A HYPOTHESIS WITH A GOOD PRIOR,
> AND IT STILL NEEDS ITS OWN GATE.** The basis and the offset were tested
> separately only because they landed in different builds by accident. **Had they
> been applied together, the failure of one would have been read as the failure
> of both, and `102` would have been retired wholesale.** `48` rule 5's real
> value, arrived at by luck rather than design.

## §4 — THE STANDING CONFIGURATION, AS PROVEN TONIGHT

```powershell
.\vr.ps1 -UnitsPerMetre 50 -HandSeam -HandPosZ 1 -ViRate 90 `
         -GunOffY 8 -GunOffZ -2 -HandAxisX -1 -HandAxisZ -1
```

**`-SeamNoRot` IS GONE** — it wrote identity over the rotation (`154` §1) and was
in every command in this project until tonight. **`-HandSeam` replaces it.**

**WHAT IS STILL OPEN:** the wearer reports the gun *"still kinda rotates a little
weird... because it's really big."* **That is SIZE, and size is `6D-12`/S1 -
`ONE-KNOB-THREE-JOBS`, which `148` says to do BEFORE any more scale sweeps.**
`-ViewmodelScale` (`78`, `79`) resizes the MODEL about its own root and is
independent of world scale, so it can be tried at once with no build.
