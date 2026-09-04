# 213 — U-18 IS WIRED: THE MUZZLE IS MEASURED, NOT TUNED. AND A SURVEY OF WHAT ELSE THE SOURCE CAN ANSWER.

**2026-08-26. Tiers per `182`. `[INFERRED]` carries its counter-example search
(`209` §4.3). BUILT, UNRUN.**

---

## §1 — WHAT CHANGED

**`muzzle_origin` used to return `handPos + fwd * GE_VR_MUZZLE_EXT`, and
`-MuzzleExt` DEFAULTS TO 0 — so the "muzzle" was the GRIP**, and
`-GunOffY 8 -GunOffZ -2` (`154`'s PISTOL constants) were carrying the barrel for
every weapon in the game. **`[REPORTED]` *"the secondary gun sprayed way off to
the right"* is what that costs when the barrel is twice as long.**

**NOW:**

```
muzzle_cam = handPos + R * (Switches[3] * 0.1)
```

| | `[MEASURED]` |
|---|---|
| pistol | `(0, 5.7, 35.0)` cm — **a 35 cm barrel** |
| the second weapon | `(0, 2.3, 70.6)` cm — **70.6 cm, twice as long** |

**`212` settled every term of this FROM SOURCE with no wear test:
`matrix_scalar_multiply` touches `[0..11]` only, `IDO_POINT_ONE = 0.1` is the
model->game conversion, and `T2` had already measured the 2:1 ratio
independently.**

### TWO DECISIONS WORTH KEEPING

**ROTATED BY `R`, NOT BY `fwd`.** `R` is `204`'s solved orientation, so the
offset lands in the frame `handPos` already lives in. **Using `fwd` would carry
only the barrel's LENGTH and throw away its lateral and vertical components —
and `[MEASURED]` `210`: the VERTICAL component is the one that dominates at
contact range.**

**AND NOT `field_B58`, WHICH IS THE OBVIOUS-LOOKING ANSWER AND A TRAP.**
`[READ]` `gunfire.c:758` writes it in CAMERA space, `:815` in WORLD space,
depending on whether the weapon has a flash node — and `[MEASURED]` the WORLD
branch fired on **518 of 1255 samples.**

**KNOB `-NoMuzzleNode`. ONE NEW SYMBOL (`0x8F000170`) — BUILD TWICE (`136`).**

> **AND `-GunOffX/Y/Z` MUST NOW RUN AT 0.** They were carrying the barrel; with
> the real one wired, **a barrel counted twice is worse than not at all.**
> `vr.ps1` says so on every launch.

**`G-213`: swap to a LONGER weapon. The shot must stay on the crosshair.**

---

## §2 — ►► THE SURVEY: WHAT ELSE THE SOURCE CAN STILL ANSWER ◄◄

**Asked by the owner: *"I wonder if there is anything else in this project that
would be optimized from the source code if it hasn't already."* Three checked in
one sitting. ONE IS ALREADY ANSWERED.**

### 1. `U-21` — THE SIGHT MARGIN. **ANSWERED. `[READ]`.**

`gunfire.c:6225`:

```c
display_image_at_position(&sp54, &xypos, &halfedxy, 0x20, 0x20, ...);
```

**`0x20 = 32`. THE CROSSHAIR GLYPH IS 32x32 PIXELS.** The stock `[3, w-4]` clamp
pins the sight's CENTRE at `316` on a 320-wide screen, **so exactly 16 px — half
the glyph — hangs off the edge.** `[REPORTED]` *"partially off on whatever corner
I left it at"*, and `190` §2 predicted the mechanism without the number.

> **`U-21`'s INSET CONSTANT IS 16, AND IT WAS NEVER A TUNING QUESTION.** It goes
> in our own copy of the clamp, **never the cone** (`190` §2: that would move the
> bullet and undo U-16).

### 2. THE `[REPORTED]` "SKINNIER" — A SPECIFIC PLACE TO LOOK. `[READ]`.

`bondview.c:657`:

```c
c_scalex = (c_scaley * c_perspaspect * c_halfheight) / c_halfwidth;
```

**The game's HORIZONTAL scale is derived from its OWN aspect**, and `167`
established `c_scalex`/`c_scaley` are never rebuilt from the headset tangents.
**"Skinny" is a horizontal-only distortion, and this is the only horizontal-only
term in the projection chain.**
**`[ASSUMED]`, and what would settle it: print `c_perspaspect`, `c_halfwidth`
and `c_halfheight` beside the render's own aspect, once.** One line, no run
dedicated to it.

### 3. `205` §5's ARM LENGTH — IT MAY EXIST. `[READ]`.

`bondview2.c:10537`: `chr->aimendrshoulder` / `aimendlshoulder`. **The engine has
shoulder aim endpoints.** Not yet read far enough to say whether a usable arm
length falls out, **but `205` §5 Q1 asked "does Bond's arm length even exist as a
number?" and the answer is no longer obviously no.**

### AND THE ONES THE SOURCE CANNOT ANSWER — SAID SO IT IS NOT RE-ASKED

**The 2.4% late frames** (`196` §5b) · **B3's X close** (`187` §3) ·
**`208`'s autolaunch hook** — all HOST-side or timing, and the game's source has
nothing to say about any of them.

---

## §3 — WHAT IS OWED

1. **BUILD TWICE. `G-213`** — swap to a longer weapon, with `-GunOff*` at 0.
2. **`U-21`, now a one-constant change** (§2.1).
3. **THEN `211`'s SOLVER**, with the measured muzzle as its input — **U-18 was
   its prerequisite and is now done.**
4. **The `c_perspaspect` print** (§2.2) rides any build.

> **THE PATTERN THE SURVEY CONFIRMS:** `212` closed `U-18` from source, `189` §2
> closed `A2` from `bondview.c:724`, and §2.1 just closed `U-21`'s constant.
> **Three questions that were queued as wear tests, answered by reading.**
> `00-START-HERE` now says so at the top.

**NOTHING STAGED. THE COMMIT IS THE OWNER'S.**
