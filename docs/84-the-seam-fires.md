# 84 — THE SEAM FIRES. The engine accepts the write, and the placement is wrong.

**2026-08-23, ~17:56. Built from `83`, worn, one launch.** `-HandSeam`.

---

## WHAT WAS BUILT

**`gunSetHorizontalOffset` (`gun.c:1230`) is now a `RECOMP_PATCH`**, and it
writes the engine's own hand override before returning the value it always
returned:

```c
if (recomp_ge_vr_hand_override(m, hand) != 0) {
    h->field_8EC = m;      /* = Perfect Dark's posrotmtx */
    h->field_92C = 1;      /* = useposrot */
}
```

**The `WeaponStats` chase `83` warned about was two fields deep** — only
`PosX` is needed, so a two-member head struct and two externs were enough.
**The hook works and the patch attaches.**

## WHAT IT DID — worn, in the wearer's words

> *"The gun is stuck to the floor. It's kind of transparent, flickering, very
> fast... and over my shoulder is the gun again, very transparent, like a ghost
> up there, and it moves along with the gun as well."*

**And the instrument agrees the write is real and the engine is reading it:**

```
[gevr] hand seam: want=(1.5 -20.5 14.4) game=(9.2 -39.3 -25.1) delta=(-7.8 18.8 39.6)
```

36 samples, sustained. **The gun MOVED, so `field_92C` / `field_8EC` genuinely
are the engine's hand override in GoldenEye, exactly as `82`'s struct alignment
predicted.** That much is now observed rather than argued, and it is the finding
worth keeping.

## WHAT IS WRONG, AND THEY ARE THREE SEPARATE THINGS

**Do not treat this as one bug. It is at least three, and `83`'s successor
should attack them in this order:**

### 1. TWO GUNS — one on the floor, one over the shoulder

**A single transform cannot draw two guns.** So either two transforms are alive
in the same frame, or one is being interpolated against the other.

**First suspect: RT64's frame interpolation.** `00-START-HERE`'s own vocabulary
says *"swimming means RT64 matched the wrong pair, ghosting means it inherited
an id it does not own, flicker means it could not pair at all."* **The wearer
reported flicker AND a ghost, which is that vocabulary's description of a matrix
group RT64 cannot pair frame to frame** — and our write changes the gun's
transform out from under it every tick.

**The check, and it needs no headset:** `-Flat`, and watch whether the second
gun survives. If it does, it is not interpolation.

### 2. THE PLACEMENT SPACE IS WRONG — "stuck to the floor"

`gunfire.c:548` **adds** our translation to `gunofs`, and `gunofs` is then
consumed by `matrix_4x4_align(&tmpmtx, 0, gunofs.x - field_A38, ...)` at
`gunfire.c:568` — **not by a plain assignment.** So a delta that is correct
against the FINAL rendered position is not necessarily correct against `gunofs`
at the point it is added.

**We cached the final rendered root translation and treated it as `gunofs`.
Those are related, not equal.**

**The measurement that would settle it:** log `gunofs` itself from inside the
patched hook — it is a local in `gunUpdateAndFire` and not reachable, **so the
honest route is to write a KNOWN constant into `field_8EC`'s translation** (say
`(0, 0, -20)`), see exactly how far the gun moves, and derive the space from the
result. **One launch, one number, no theory.**

### 3. THE ROTATION PRE-MULTIPLIES, so it rotates about the gun's OWN origin

`rotmtx = field_8EC * rotmtx` acts in the gun's local frame. **If the model's
geometry sits away from its local origin, a rotation there swings the gun
through a wide arc rather than turning it in place** — which is a good candidate
for "over my shoulder".

**Perfect Dark does not hit this because they REPLACE the placement rather than
adding to it** (`82`). We cannot replace it, so this is the cost of the seam and
it has to be measured rather than assumed.

## STATE AS SHIPPED

**`GE_VR_HAND_SEAM` defaults OFF.** Unset, `gunSetHorizontalOffset` is the
original function and nothing about the game changes. **Three hand paths now
exist behind three flags, and none is validated:**

| Flag | What it does | Worn verdict |
|---|---|---|
| *(default)* `-HandAim` | Render-time delta on the node matrices | Tracks, but the engine's turn-sway pulls it |
| `-HandAbsolute` | Adds an absolute rotation against a neutral reference | *"Really far away"* — and `82` later found the Z sign was inverted, so **this deserves a re-test now that the sign is fixed** |
| `-HandSeam` | The engine's own override, from inside the placement | This document |

**That is not a good place to leave it and this document says so plainly.**
**But the seam is the right architecture** — it is where Perfect Dark works, it
is upstream of the sway, and it is now proven to be live in GoldenEye. The next
session should fix its placement rather than start a fourth path.

## THE ONE-LAUNCH EXPERIMENT TO OPEN WITH

```
Write field_8EC translation = (0, 0, -20), rotation = identity, and nothing else.
```

**Predicted if the space is what we assume:** the gun moves 20 units further
away and nothing else changes — no ghost, no flicker, no floor.

**Whatever actually happens tells you which of the three faults above is real**,
and it costs one launch. **That is the first thing to do, before any more
matrices are written.**
