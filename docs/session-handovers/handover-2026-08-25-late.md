# Handover — 2026-08-25 LATE. Aim chain built, FOV fixed, upgrade catalogue opened.

Repo docs are authoritative. Read `162` → `163` → `166` → `167`, then `161` (the plan)
and **`169` (the new standing upgrade sheet)**.

## New standing file: `169-THE-UPGRADE-SHEET.md`

`161` is the PLAN — what is being built now, with gates. **`169` is the CATALOGUE** —
everything found that would be an upgrade, whether or not anyone intends to build it.
Items live in `169` from the moment they're found and move to `161` when someone
decides to build them. Nothing is ever deleted; a rejected idea with its reason stops
the next session re-finding it. Every entry carries ID / WHAT / EVIDENCE / COST /
BLOCKERS / VERDICT. **Next ID: U-18.**

## What was built this session (all UNWORN — the owner can no longer test)

- `163` — P1-2/P1-3: the aim projects through GoldenEye's own projector instead of a
  gain constant. Five knobs dead, zero free parameters.
- `164` — the shot leaves the **barrel**, not the eye. Plus a SHOT instrument that
  reports muzzle + direction so accuracy is computable from the log alone.
- `165` — the crosshair, which had never been drawn in the entire project.
- `167` — the FOV fix: the aim divided by the *game's* frustum while the frame is
  *drawn* with the headset's.

## The findings that matter most

**The aim projected through a frustum nobody is looking through.** `c_scalex/c_scaley`
come from `c_perspfovy=106`; the frame is rendered from the headset's ~88°. Vertical
gap 1.374, horizontal 1.540 — **two ratios**, which is why it read as two bugs
("worse going up" and "off differently at the sides"). `163` §1's claim that the FOV
read was no longer owed is **retracted**.

**The crosshair had two separate faults.** It was never drawn at all —
`gunsightmode=2` is `GUNSIGHTREASON_NOTAIMING`, set from the aim button nobody presses
in VR. Once drawn, it appeared **doubled, one place per eye**: the frustums are
mirrored and asymmetric, so no single pixel is correct for both. PD's fix is U-01.

**World scale was compensating for the FOV.** At `WorldUnitsPerMetre 12` Bond is
14.6 m tall and the gun is 1.7 m long — that's the "giant arm". The correct value is
100. `159`'s sweep to 12 was cancelling the FOV error and breaking the geometry to
do it.

**The PD port rule, learned three times:** the constants and designs transfer; the
subsystems do not. Every failure (`155`'s post-rotation, `163` §7's muzzle model part,
`166`'s laser) was a call *into* a PD feature GoldenEye doesn't have. Before costing
anything that touches game code, grep `patches/externs.h` and `patches/structs.h` for
every symbol it needs — `157` withdrew a slice for want of eight, `166` stopped one
for want of five.

## Next, in order

1. **U-01 per-eye HUD shift** — fixes the doubled crosshair, nothing blocks it. PD's
   canting term evaluates to −0.1867 for our eye 0, which is exactly the `m20=-0.18669`
   already in our own projection log. Our 3D scene is canted; the HUD isn't.
2. **Wear-test `167`** with world scale back to 100.
3. `166` §4's **17° yaw error** is still open and is *not* a PD problem. Leading
   candidate: the wearer aims by the drawn gun, whose orientation is the seam matrix
   `158` §3 already proved is not the barrel.
4. **U-14** (per-weapon muzzle from `MuzzleFlashExtension`) and **U-16** (clamp split)
   are cheap GoldenEye-native wins found while reading.

## Folder layout

`local-only` and `repo` are siblings under `GoldenEyeVR`. The live build tree is a
**separate** directory: `C:\Users\<USER>\Desktop\GoldenEye64Recomp`.
