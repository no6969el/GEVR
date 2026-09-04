# 177 — FOUR READS, NO MACHINE NEEDED. THREE BLOCKERS DISSOLVE.

**2026-08-25. Reads only. Nothing built. `48` rule 1.**

> ## THE HEADLINE, AND IT CORRECTS A PREMISE THE PROJECT HAS BUILT ON
>
> ## **`camGetWorldToScreenMtxf()` IS PATCH-REACHABLE.** `patches/externs.h:63`.
>
> **`160` §2/B1 and `163` §1 both rest on the claim that PD can project a world
> ray "because `camGetWorldToScreenMtxf()` is in scope and we cannot because it is
> not". IT IS IN SCOPE. It has been declared in `externs.h` the whole time.**

---

## 1. WHAT THAT CHANGES, AND WHAT IT DOES NOT

**IT DOES NOT INVALIDATE `163`.** The projected aim we built via
`transform3Dto2DCoords` is correct, and `167` made it FOV-correct. **Nothing shipped
is wrong.**

**WHAT IT CHANGES IS WHAT IS NOW POSSIBLE:** PD's exact idiom —
**take a point in the WORLD, push it through `camGetWorldToScreenMtxf()`, get
pixels** — is available to us directly. **That is the mechanism U-06 (crosshair
parallax by target distance) and U-05 (aim at the laser dot's real hit point)
both need**, and both were costed as blocked partly on this.

**THE LESSON IS `171` §3's, AGAIN, AND THIS IS THE THIRD TIME:** a capability was
written off from a claim in a document rather than from a grep. **`160` said it,
`163` repeated it, and neither checked `externs.h`.**

## 2. U-15 / U-18 — THE FRAME BLOCKER IS GONE

`171` §4 said the muzzle node could not be used because its value is in the
MODEL's frame and *"the conversion runs through `gunmtx`, which is local to
`gunUpdateAndFire` and not published anywhere."*

**`gunmtx` IS PUBLISHED.** `gunfire.c:572`:

```c
matrix_4x4_copy(&gunmtx, &hand->gunmtx_camspace);
```

> **`hand->gunmtx_camspace` is the gun's matrix IN CAMERA SPACE — exactly the
> frame `bullet_path_from_screen_center`'s `arg0` wants — persisted per hand.**

**AND THE PATCH-SIDE SLOT EXISTS AT A VERIFIED OFFSET.** `patches/structs.h`
carries **sixteen consecutive `s32` placeholders**, `field_A98` through
`field_AD4`. That is `0xA98`-`0xAD8` = **0x40 bytes = exactly one `Mtxf`**, and
**BOTH sides anchor on `throw_item_pos_related` at `0xad8`**, which is the
independent check `115` demands.

**So this is a TRANSCRIPTION, not a reverse-engineering job.** Replace the sixteen
placeholders with `Mtxf gunmtx_camspace;` and the muzzle node becomes usable.

## 3. U-07 — MANUAL RELOAD. THE ROUTE IS ONE FIELD.

`bondview2.c:9432` is the entire gate:

```c
s32 bond_pressed_reload_activate(void) { return g_CurrentPlayer->field_D0; }
```

and `lv.c:733`:

```c
if (bond_pressed_reload_activate() && bond_interact_object()) {
    attempt_reload_item_in_hand(GUNRIGHT);
    attempt_reload_item_in_hand(GUNLEFT);
}
```

**NONE of those three functions is in `patches/externs.h`. `field_D0` IS**
(`structs.h:2005`).

> **SO NO FUNCTION NEEDS PATCHING. Write `field_D0` from the patch when the host
> reports the gesture, and the game's own reload path runs.** `172` §7's rule in a
> new place: **we own a value the unreachable function reads.**

**ONE CAVEAT, RECORDED BEFORE IT COSTS A BUILD:** the `&& bond_interact_object()`
is a second condition and **its meaning is UNREAD.** If it gates on "standing near
something usable", a gesture reload would work only sometimes — which would read
as an unreliable gesture rather than as a missing condition.

## 4. U-05 — THE LASER. DOWNGRADED, NOT CLEARED.

`166` §5.2 listed five unreachable symbols and a struct. **The struct half is
solved:**

- **`BeamRecord` IS fully defined** — `src/bondtypes.h:2305`: `unk00`, `item_id`,
  `pos`, `delta`, `unk1c` and the rest, **with offsets in the comments.**
- **The patch-side slot exists**: `ChrRecord_f180 field_A54` occupies `0xA54`, and
  `noise` at `0xA80` anchors the far end on both sides. **44 bytes, correct size.**

**And if we can fill a `BeamRecord` ourselves, `CapBeamLengthAndDecideIfRendered`
and `gunCreateBeamForHand` are not needed at all** — they are constructors for a
struct we would be constructing.

**WHAT STILL BLOCKS IT: the beam is in WORLD space** (`pos` from
`hand->field_B58`), and **`currentPlayerGetViewToWorldMtxf` is still not
reachable.** Our aim ray is camera-space.

**TWO CANDIDATE ROUTES, BOTH UNREAD:**
1. **`hand->field_B58` is already the muzzle in WORLD space**, computed by the
   game at `gunfire.c:757`. **If the beam start can be taken from it directly, only
   the DIRECTION needs converting.**
2. **`camGetWorldToScreenMtxf()` is reachable (§0) and is invertible in principle.**
   Whether that is cheaper than finding a view-to-world accessor is a judgement,
   not a read.

## 5. U-09 — SEPARATE DOCUMENT

The crouch read is `176`. **Summary: the AI's "shoot lower at a crouched player"
behaviour is ALREADY STOCK** (`chrprop.c:1413`) and has simply never been told,
because `crouchpos` only moves when a button is pressed. **`86`'s Option B is
blocked (`eyeheight` is not patch-reachable) and is not needed, because in VR the
view lowers physically.**

## 6. WHAT THESE READS DID TO THE SHEET

| entry | was | now |
|---|---|---|
| **U-05** laser | BLOCKED — 5 symbols + a struct | **struct SOLVED; blocked only on view-to-world.** Two unread routes |
| **U-07** reload | NEEDS A READ | **ROUTE FOUND** — write `field_D0`. One caveat unread |
| **U-09** crouch | DISCUSS BEFORE BUILDING | **DESIGNED, `176`.** Decisions taken |
| **U-15/U-18** muzzle | frame not established | **FRAME SOLVED** — `gunmtx_camspace`, offset-verified |

> ## **AND THE RULE THAT PRODUCED ALL FOUR:**
> **EVERY ONE OF THESE BLOCKERS DISSOLVED UNDER A GREP OF `patches/externs.h` AND
> `patches/structs.h`.** `168` §5 made that grep mandatory before COSTING work.
> **`177` extends it: run it again before believing a blocker that a previous
> document asserted.** Three of the four above were written down as impossible by
> me, in documents from earlier today.
