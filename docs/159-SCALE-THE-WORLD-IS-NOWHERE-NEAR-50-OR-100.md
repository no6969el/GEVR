# 159 — SCALE. THE WORLD NUMBER IS NOWHERE NEAR 50, OR 100. AND S1 IS WHY WE KNOW.

**2026-08-25, worn, a bracketed sweep. `16` derived ~100 units/metre from the
code. `77` preferred 50 by wearing. THE WEARER'S ANSWER IS AROUND 12-25, AND
BOTH EARLIER NUMBERS ARE WRONG FOR THIS JOB.**

---

## §1 — WHAT THE SPLIT MADE VISIBLE

**6D-12 / S1 (`156`) separated `GE_VR_WORLD_UNITS_PER_METRE` from
`GE_VR_HAND_UNITS_PER_METRE`. Within one session that split resolved a conflict
that had stood since 2026-08-22.**

> **THEY WERE NEVER IN CONFLICT. THEY ARE TWO DIFFERENT QUANTITIES:**
>
> | | Number | Kind |
> |---|---|---|
> | **HAND** | **100** | **A MEASUREMENT.** One game unit is one centimetre - `16`, from Bond's 175-unit eye height and a guard's `chrheight` 185. Physical hand travel maps 1:1 |
> | **WORLD** | **~12-25, still tuning** | **A PERCEPTION.** It sets stereo eye separation and therefore apparent size. It is not a measurement of anything |

**`77`'s "50 feels better" and `16`'s "~100 from the code" were answering
different questions and neither was wrong.**

## §2 — THE SIGNATURE THAT NAMED THE FAULT

**The wearer, at 100:** *"I feel like I am on a toy model level and I am my normal
head size... looking at characters much smaller than my size wise BUT SAME
HEIGHT."*

> ## **"SAME HEIGHT BUT MINIATURE" IS HYPERSTEREO, AND IT IS DIAGNOSTIC.**
>
> **Height relationships come from GEOMETRY and are invariant** - `chr.c:1717`'s
> `chrheight = 185` against Bond's `175.0f` eye puts the player eye-to-eye with a
> guard at ANY scale. **Only APPARENT SIZE comes from stereo.** Cameras further
> apart than the world expects read as a scale model while positions stay
> correct. **That is precisely the report, and it says the number is TOO HIGH.**

**Eye separation in game units is `measured IPD x worldUnitsPerMetre`** —
`0.0639 x W`. Every halving of W is one clear perceptual step; **anything finer
than a factor of two is below the noise floor in a headset** and earlier sweeps
had been making changes smaller than that.

## §3 — THE DIRECTION, AND A CORRECTION I OWE

**I PREDICTED 100 WOULD FIX IT AND HAD THE OPTICS BACKWARDS.** More eye
separation means MORE parallax, which reads as a SMALLER, CLOSER world - so 50
-> 100 moved further into the fault, not out of it. **Withdrawn.**

**AND ONE TEST WAS CONFOUNDED BY MY OWN COMMAND LINE:** the `W=100` run omitted
`-ViewmodelScale 0.5`, so the gun reverted to full size and the wearer reported
it as *"bigger than expected"*. **`48`'s "one change at a time" broken by the
person quoting it, again.**

**MEASURED PROGRESSION:** 50 (*"shoulders will hit both sides"*) -> 100 (*"toy
model"*) -> 25 (**"better"**) -> 12 pending. **The direction is DOWN.**

## §4 — THE THIRD KNOB, AND WHY IT IS NOT WORLD SCALE

**The wearer, at 25:** *"my gun still seems a little larger than them."*

> **THE GUN AND THE GUARDS ARE BOTH GAME GEOMETRY THROUGH THE SAME STEREO, SO
> WORLD SCALE MOVES THEM TOGETHER AND THEIR RATIO NEVER CHANGES.** That ratio is
> `-ViewmodelScale` and nothing else.

**And it must move WITH the grip offsets:** the model scales about its own root,
so the grip point moves in proportionally. **Halve the scale, halve
`-GunOffY/Z`.** `0.5 -> (8, -2)`, `0.35 -> (5.6, -1.4)`, `0.25 -> (4, -1)`.

## §5 — THE BEST INSTRUMENT IN THIS PROJECT IS A GUARD

**Better than the doorway `16` asked for.** A doorway's true size is a guess about
1990s level authoring; **a person is a thing the wearer knows by heart, and
`chr.c:1717` guarantees the guard is exactly his own height.**

> **THE STANDING TEST: stand next to a guard. He must read as a real adult. THEN
> size the gun against your own hand.** Heights are invariant, so anything that
> looks wrong is a SIZE error and size is stereo.

## §6 — IF IT BOTTOMS OUT, IT IS NOT STEREO. THE FOV READ IS OWED.

**If 12 is still a toy model, no eye-separation value will fix it** and the other
classic cause of miniaturisation applies: **a rendered frustum WIDER than the
headset actually displays.**

**THERE IS A LIVE CANDIDATE AND NOBODY HAS READ IT.** S0 reports
`WIDE-frustum ... fovy=106` from the game's widescreen path, while the headset's
own live tangents (`+-0.9657` vertical) work out to about **88 degrees**.
**We override the frustum with the live tangents - but it is NOT ESTABLISHED
that `widescreen.c` does not re-apply afterwards.** `14`, and `150` already
flagged a loaded divide-by-zero behind an `#if 0` in that file.

> **THAT IS A READ, NOT A LAUNCH, AND IT IS THE NEXT THING IF THE SWEEP BOTTOMS
> OUT.**

## §7 — WHERE IT STANDS

**PINNED:** `-HandUnitsPerMetre 100`. A measurement, not a preference.
**TUNING:** `-WorldUnitsPerMetre` 25 -> 12 -> lower, halving each step.
**THEN:** `-ViewmodelScale` for the gun-to-guard ratio, offsets halved with it.

**NO FINAL NUMBER IS RECORDED YET AND ONE MUST NOT BE INVENTED.** When the wearer
lands it, it goes here and in `148` with the guard comparison as its evidence.
