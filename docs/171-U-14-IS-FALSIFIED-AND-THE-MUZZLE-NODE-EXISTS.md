# 171 — U-14 IS FALSIFIED, AND THE MUZZLE NODE EXISTS AFTER ALL. `163` §7 RETRACTED.

**2026-08-25. Two corrections found while preparing U-14. Nothing was built on a
wrong assumption, which is the only reason this is cheap.**

---

# 1. THE OFF SWITCH THAT SLICE SHIPPED WITHOUT

`167` and `170` are **two behaviour changes** and they stacked into one unbuilt
tree. `170` has `-NoHudShift`; **`167` had nothing**, so a single wear test could
not have said which of the two moved the crosshair.

**`-AimEstimate` IS NOT THE A/B** — it reverts to the old GAIN path entirely and
bypasses the projection as well, so it answers a different question.

**Added `GE_VR_AIM_FRUSTUM` / `-NoAimFrustum`**, which falls back to
`transform3Dto2DCoords` with the game's own `c_scale` — `167`'s fault,
deliberately reproduced. **`48` rule 5, restated: if two changes must share a
build, each needs its own switch.**

---

# 2. ►►►► U-14 IS FALSIFIED. `MuzzleFlashExtension` IS NOT A BARREL LENGTH. ◄◄◄◄

`169` U-14 proposed defaulting `GE_VR_MUZZLE_EXT` to the weapon's own
`MuzzleFlashExtension`, on the strength of `6D-02` measuring it at `100` flat
across 97 samples. **THE MEASUREMENT WAS RIGHT AND THE INTERPRETATION WAS WRONG.**

`gunfire.c:754`:

```c
matrix_column_3_scalar_multiply(flashext, flashmtx.m[0]);
```

and `matrixmath.c:408`:

```c
void matrix_column_3_scalar_multiply(f32 scalar, f32 *matrix) {
    matrix[8] *= scalar;  matrix[9]  *= scalar;
    matrix[10] *= scalar; matrix[11] *= scalar;
}
```

**Elements 8-11 are ROW 2 of the flat 4x4 — the matrix's Z BASIS ROW. It never
touches `m[3][*]`, which is the position.**

> ## **`MuzzleFlashExtension` STRETCHES THE MUZZLE-FLASH SPRITE ALONG ITS OWN Z.
> ## IT IS A VISUAL SCALE, NOT A DISTANCE, AND IT MOVES NOTHING.**

**Wiring it to the muzzle offset would have pushed the bullet's origin a metre
down the barrel** (100 units at 1 unit = 1 cm) **and the error would have looked
exactly like the grip offset being wrong** — which this project has already
mis-attributed once (`163` §6).

**U-14 IS DECIDED AGAINST.** Kept in `169` with this reason so it is not
re-proposed — the next reader will find `muzzleExt=100` in `6D-02` and reach for
it exactly as I did.

---

# 3. ►►►► BUT THE MUZZLE NODE EXISTS. `163` §7 IS RETRACTED. ◄◄◄◄

`163` §7 concluded:

> *"GOLDENEYE HAS NO MUZZLE MODEL PART. `MODELPART` has ZERO occurrences in the
> whole game tree. PD's per-weapon muzzle node DOES NOT TRANSFER."*

**THAT SEARCHED FOR PERFECT DARK'S NAME, NOT FOR THE THING.**

`gunfire.c:633`:

```c
flashdata = (f32 *) mdlhdr->Switches[3]->Data;
```

`gunfire.c:746`:

```c
matrix_4x4_set_position((coord3d *) flashdata, &flashmtx);
```

> ## **`Switches[3]->Data` IS A `coord3d`: THE MUZZLE POSITION IN THE GUN MODEL'S
> ## OWN FRAME, PER WEAPON. THAT IS PD's `MODELPART_GUN_MUZZLEPOS`, UNDER A
> ## DIFFERENT NAME.**

**AND IT IS ENTIRELY PATCH-REACHABLE** — the grep `168` §5 makes mandatory, which
`163` never ran for this:

| symbol | in `patches/` ? |
|---|---|
| `ModelNode` (with `Data`) | **YES** — `structs.h:1118` |
| `ModelFileHeader.Switches` | **YES** — `structs.h:1162` |
| `numSwitches` | **YES** — `structs.h:1163` |
| `copy_of_body_obj_header[2]` | **YES** — `structs.h:2522` |

**FOUR FOR FOUR. Nothing blocks reading it.**

## 3.1 SO THE PD PORT SCORECARD CHANGES

`168`'s table listed the muzzle model part as one of three PD features that
FAILED to transfer. **It is now one that transfers — we simply looked for it by
the wrong name.** The rule in `168` survives and is *sharpened*:

> **"THE CONSTANTS AND DESIGNS TRANSFER; THE SUBSYSTEMS DO NOT" — and the search
> must be for the MECHANISM, never for PD's identifier.** `MODELPART` returning
> zero was true and meant nothing.

---

# 4. WHY THIS SHIPPED AS AN INSTRUMENT AND NOT A FIX

**The value is in the MODEL's frame.** The conversion to the frame
`bullet_path_from_screen_center`'s `arg0` wants runs through `gunmtx`, which is
**local to `gunUpdateAndFire`** and not published anywhere.

**THE FRAME IS NOT ESTABLISHED, SO THIS MEASURES BEFORE ANYTHING DEFAULTS TO
IT** — and that is precisely the step whose absence produced §2. `90`'s
discipline, `115`'s, and `86` §3's "print every quantity WITH THE FRAME IT IS IN".

New line, every sample:

```
[gevr] 6dof-game: MUZZLENODE Switches[3]=(x,y,z)[x100, MODEL frame] numSwitches=N
                  | flashExt=NNN[x100] <- docs171: a SPRITE STRETCH, NOT a barrel length
```

**A missing node prints `absent`, never `0`** — `48`, because a zero here is
indistinguishable from a muzzle at the model origin.

## 4.1 WHAT THE NEXT RUN DECIDES

- **Is `Switches[3]` present on every weapon?** `numSwitches` is documented in
  `structs.h:1163` as *"Does not reflect number actually used"*, so presence must
  be measured, not assumed.
- **Does it CHANGE between weapons?** If a pistol and a rifle report the same
  vector, it is not a per-weapon muzzle and this is over.
- **What is its magnitude?** That establishes the model frame's scale against the
  game units we already know, which is the whole blocker in §4.

**IF ALL THREE PASS, `-MuzzleExt` AND ITS THREE SIGN KNOBS CAN BE DELETED and
per-weapon muzzles come for free** — the outcome `163` §7 wrote off.

---

# 5. WHAT CHANGES ON THE SHEET

- **U-14** — **DECIDED AGAINST**, §2. Kept with its reason.
- **U-15** (the game already computes a muzzle point) — **upgraded.** §3 is the
  cleaner half of it: the source node, rather than `field_B58` downstream of a
  matrix we cannot reach.
- **U-18, NEW** — read `Switches[3]` per weapon and establish its frame. **The
  instrument is built; the read happens on the next run.**
