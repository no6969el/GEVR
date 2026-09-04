# Handover — 2026-08-25 CLOSE. The crosshair fuses; the menus show the game.

Repo docs are authoritative. **Read `161` (the plan) and `169` (THE UPGRADE
SHEET), then `173` `174` `175` for the latest slices.** `00-START-HERE.md` and
`HANDOVER.md` both carry full top blocks.

**One build pending**, carrying `174` and `175`. Three headers changed, so it must
report a full rebuild. Test list is in `MAIN-STATION-TASKS.md`.

## Standing files

- **`161`** — the PLAN. What's being built now, with gates.
- **`169`** — the CATALOGUE. Everything found that would be an upgrade. Append,
  never rewrite. **Next ID: U-21.**

## What landed today

**Morning/afternoon (`162`-`168`, `170`-`172`):** the aim chain — the projector was
in the game all along; the shot leaves the barrel not the eye; the crosshair that
had never once been drawn in the entire project; the FOV fix; the clamp split; the
PD port feasibility study.

**Evening (`173`, `174`):** U-01 worn and working — *"much closer now in my
vision."* It took three attempts, two of them mine:

- `170` put the shift on the **orthographic projection matrix**, but GoldenEye's
  HUD sprites are **`Type::Rectangle`** — a third projection type that carries no
  matrix at all. The edit was structurally incapable of moving the crosshair.
- The sign was inverted, because **the matrix entry's sign is not the sign it
  produces in NDC** — the perspective divide flips it. The wearer named it before
  the algebra did: the crosshairs *diverged*, and divergent is behind infinity,
  where eyes physically cannot fuse.

**Late evening (`175`):** U-19 — the virtual screen. Menus and the front end now
show the game on a rectangle in space instead of the red/blue clear.

## The finding that matters most, still open

**The seam composition is wrong, and the wearer found it.** *"If I turn my head
left and right, the gun will change directions in my hand automatically."*

The seam computes `R = Rhead * Rhand^T`. The correct view-space orientation is
`R = Rhead^T * Rhand` — **and the aim path has always used `Rhead^T`.** So the aim
and the picture have been on two different transforms the entire time. That's
`166` §4's "the drawn gun is the liar" hypothesis, independently confirmed.

Knob-gated (`-SeamCompose 1`), default legacy, **untested** — `-HandAxis*` and
`-GunOff*` were all tuned against the old composition.

## The one test that decides what comes next

The shot lands ~6 px **up** and ~1 px right of the crosshair (the owner drew it —
predominantly *vertical*, which a lateral half-IPD error does not explain). The
sketch is on disk at `docs/images/2026-08-25-crosshair-impact-sketch.png`.

**Shoot a wall at arm's length, then from across the room.** Miss shrinks with
distance → muzzle parallax (U-06, PD has a cure). Miss holds → constant angular
error in the ray. **They behave oppositely, so one wall answers it.**

## Rules this project now runs on

1. **Search for the MECHANISM, never for Perfect Dark's identifier.** A name-based
   grep only proves PD's name is absent — it cost `163` §7 a feature GoldenEye has.
2. **Before costing anything touching game code, grep `patches/externs.h` and
   `patches/structs.h` for every symbol.** `157` withdrew a slice for want of
   eight; `166` stopped one for want of five; `169` U-16 was recorded "BLOCKERS:
   none" and was blocked.
3. **A function you cannot patch is not always a blocker.** If you own the
   producer and the consumer, change what flows between them (`172` §7).
4. **If two changes must share a build, each needs its own off switch** (`171` §1).

## Next up, from `169`

1. **U-20** — PD's hub room, re-skinned for GoldenEye. **Owner wants this.**
   Dependency cleared by `175`. It's two quads and twelve vertices; everything you
   see is procedural shader, and there are no art assets to port. Only real work
   is GLSL -> HLSL.
2. **U-18** — the muzzle node. Blocked only on the MUZZLENODE read.
3. **U-02** — host-side recoil. PD: *"100% on OpenXR side, no engine dependency."*
4. **U-03** — snap turn.

## Folder layout

`local-only` and `repo` are siblings under `GoldenEyeVR`. The live build tree is a
**separate** directory: `C:\Users\<USER>\Desktop\GoldenEye64Recomp`.
