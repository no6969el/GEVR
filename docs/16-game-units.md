# Game units per metre — derived 2026-08-22, MEASURED 2026-08-23

> ## THE DERIVATION BELOW IS OUT BY ABOUT 2x. READ `77` FIRST.
>
> **Measured worn, 2026-08-23, through working stereo from a correctly centred
> eye height — the first time any of that was possible.**
>
> ```
> derived   ~100 units/metre   (this document, from an assumed eye height)
> measured   ~50 units/metre   (provisional; 35 and 100 both read wrong, 50 preferred)
> ```
>
> **This document's own falsifier fired:** it said *"if it looks like three
> metres or three centimetres, the derivation is wrong"*, and claimed good to
> "maybe 10%". **It is out by a factor of about two.**
>
> **What the derivation got RIGHT, and it matters:** the character geometry.
> `chr.c:1717` `chrheight = 185.0f` against Bond's `175.0f` eye height means a
> guard is exactly Bond's height, and worn, he is. **The early "people look
> small" reports were a recentring fault (O60), not a scale one.**
>
> **Still owed:** the doorway test this document asked for, at 50 and 65. Ten
> minutes. Until then **50 is provisional and labelled as such.**


`12-phase1-step3-design.md` §6 left this as "use a single tunable constant for
now, Phase 4 owns the real answer". Step 3b forced the question early, because a
lateral eye offset is meaningless without it.

## The number

**Roughly 1 game unit = 1 centimetre. About 100 units per metre.**

Derived from `lib/ge/src/game/bondview.c:1507`:

```c
g_CurrentPlayer->eyeheight = ((g_playerPerm->player_perspective_height * 185.0f * (s32)1) - 10.0f);
```

At the default perspective height of 1.0 that puts Bond's eye at **175 units**.
A standing adult's eye height is about 1.6 to 1.7 m, so 175 units is about
1.65 m, giving ~106 units per metre.

`lib/ge/src/game/player.c:33` corroborates the order of magnitude with
`DEFAULT_C_HALFHEIGHT 136.0f` for the collision capsule.

**This is a derivation, not a measurement.** It rests on the decomp constant,
which is solid, and on an assumed human eye height, which is an assumption. It is
good to within maybe 10%, which is enough for every use it currently has and not
enough for Phase 4's comfort tuning.

## What it makes true

| Quantity | Game units |
|---|---|
| Measured IPD, 63.5 mm (`09`) | **6.35** |
| Per-eye offset, half of that | **3.175** |
| One metre | ~100 |
| Old `GE_VR_MIN_ZNEAR_UNITS` = 10 | 10 cm |
| Step 3b's `GE_VR_TEST_OFFSET` = 120 | **1.2 m per eye, 2.4 m apart** |

That last row is why 3b's first run put the camera outside the player and swept a
wide arc when turning. The value was chosen to be "unmistakable on a monitor"
without any idea of the scale, and it was unmistakable by a factor of about
twenty.

## Note on the environment variable's semantics

`GE_VR_TEST_OFFSET` is the offset **per eye**, applied as `-offset` to eye 0 and
`+offset` to eye 1. Eye separation is therefore twice the value. A real IPD is
`3.175`, not `6.35`.

## The correction to `14`

`14` reasoned that a 10-unit near plane was clipping characters at a noticeable
distance. At 1 unit = 1 cm that is a 10 cm near plane, which is far too close to
explain a character vanishing at arm's length by triangle clipping alone.

The mechanism was almost certainly **whole-object culling** rather than clipping:
the game culls a character by testing its origin against the frustum, so a
model whose origin crosses a 10 cm near plane vanishes entirely while its body is
still visibly in front of the player. `14` did say the `Mtxf` path culls whole
objects; the scale now says that path is the *only* plausible one, not merely the
better fit.

The fix and the observed improvement are unaffected. The reasoning is sharper.

## Confirming it

The derivation predicts that `GE_VR_TEST_OFFSET=30` moves the viewpoint about
30 cm sideways — a clear but ordinary step, roughly a foot. If it looks like
that, ~100 units per metre is confirmed to the precision anyone needs right now.
If it looks like three metres or three centimetres, the derivation is wrong and
the constant needs a real measurement rather than an assumed eye height.
