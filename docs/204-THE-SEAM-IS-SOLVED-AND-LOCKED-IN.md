# 204 — THE SEAM IS SOLVED, AND THE COORDINATES ARE LOCKED IN.

**2026-08-25. Tiers per `182`. `[REPORTED]`: *"We need to lock these coordinates
in because this is great. We can totally move on to getting the aiming to
actually work."***

---

## §1 — THE FOUR TERMS THAT MAKE UP THE ANSWER

**The gun's frame took four corrections, and NONE of them was a tuning
constant.** Each was read or measured, and each is now a default:

| # | term | how it was settled |
|---|---|---|
| **1** | **`R = Rhand`** — no head term at all | `200`: 744 poses, 83 head-only transitions. `Rhand` drifts **0.14 deg**; every form with a head term drifts **4.2-4.4** against the head's own **4.34**. The view matrix already applies the head (`194`), so a head term applied it twice. |
| **2** | **position = the RAW play-space hand** | `200` §2. `(hand - head) + (head - gameCamera)` **is** `hand`. It collapsed `194` and `197` into one line. |
| **3** | **`gun_azimuth` write OFF** | `201`. `163`'s second driver turned the model from a HEAD-RELATIVE term. Correct for a crosshair, wrong for a gun. |
| **4** | **`R` TRANSPOSED on the way out** | `203`: 734 paired samples. COLUMN **0.00 deg** from the true controller forward, ROW **54.60**. The game reads the ROW. **`158` §2's question, open for forty-five documents.** |

**AND THE FIFTH TERM IS NOT A CORRECTION AT ALL — IT IS THE MODEL:**

## §2 — ►► `-HandAxisX -1 -HandAxisZ -1` IS THE GUN MODEL'S OWN BARREL AXIS ◄◄

**`[MEASURED]`, in the project's own log since `171`:**

```
MUZZLENODE Switches[3]=(0, 56.7, 350.3)   [x100, MODEL frame]
```

**THE MUZZLE SITS AT +350 ON Z. THE MODEL'S BARREL POINTS ALONG `+Z`, NOT `-Z`**
— and `-Z` is what OpenXR means by forward, so a 180 degree turn about Y is owed.
**`diag(-1, 1, -1)` IS EXACTLY THAT TURN** (determinant `+1`: a rotation, not a
mirror).

> **SO `155`'s NUMBERS WERE RIGHT FOR A REASON NOBODY HAD FOUND.** They were
> discovered empirically, survived as "PD's basis that transferred", were
> DISCARDED in `201` §1 when the frame changed and the roll came good without
> them — **and are right again on the far side of three frame corrections,
> because they were never about the frame. They are a property of the ART.**
>
> **THAT IS WHY THEY ARE NOW A DEFAULT AND NOT A KNOB SETTING**: a term that
> describes the model belongs in the code, not in every command line.

---

## §3 — WHAT IS LOCKED IN

**HOST DEFAULTS CHANGED — `-HandAxisX -1` and `-HandAxisZ -1` are now the
built-in values**, alongside `GE_VR_SEAM_FRAME=2`, `GE_VR_SEAM_T=1` and
`GE_VR_GUN_AZIMUTH=0`. **An unset launch is now the correct one.**

**AND `vr.ps1` NOW EXPORTS THE AXIS SIGNS UNCONDITIONALLY.** It used to write
them only when they differed from `1`, which with a host default of `-1` would
have **silently swallowed an explicit `-HandAxisX 1`** — *"a knob that cannot be
turned off looks exactly like a knob that does nothing"* (`178`).

### THE STANDING COMMAND, SHORTER THAN IT HAS BEEN ALL PROJECT

```powershell
.\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
         -WorldUnitsPerMetre 100 -HandUnitsPerMetre 100 `
         -ViewmodelScale 0.5 -GunOffY 8 -GunOffZ -2 `
         -AimFromHand -MuzzleOrigin -NoCrouch -HudDepth 0.2
```

**THE OFF SWITCHES SURVIVE, ALL OF THEM:** `-SeamFrame 0|1`, `-NoSeamT`,
`-GunAzimuth`, `-HandAxisX 1 -HandAxisZ 1`, `-NoHandPosT`, `-NoRoomOrigin`,
`-NoAimCone`. **`00-START-HERE`: DELETE NOTHING.**

---

## §4 — WHAT THIS CLOSED, AND WHAT IT DID NOT

**CLOSED:** `185` `T9` · `158` §2 · `166` §4's *"the drawn gun is the liar"* — it
was, and now it is not · every head-turn report from `173` onward.

**NOT CLOSED, AND NOT TOUCHED BY ANY OF IT:**
- **`B1`/U-06, THE PARALLAX** — `193` §2 measured the muzzle at **0.19-0.61 m**
  from the eye. **This is the next thing that changes what SHOOTING feels like.**
- **`G-194`** the mark test · **`U-18`** the per-weapon muzzle (`T2` passed).
- **THE POSE KNOBS** — `-GunOffY 8 -GunOffZ -2` are `154`'s PISTOL values from the
  legacy frame, and `-ViewmodelScale 0.5` with them. **Knob-only, and now
  judgeable for the first time**, because the motion underneath them is correct.
- **THE FOV / SCALE READ** (`199` §4) — `fovy=106` against the headset's `88`.
- **The 2.4% late frames** (`196` §5b) · **B3's X close** (`187` §3) ·
  **THE COMMIT, both repos, and it is now nineteen documents overdue.**

---

## §5 — THE METHOD NOTE, BECAUSE IT IS THE REUSABLE PART

**The seam took two wear tests of hand-picked candidates and answered neither.
It took two RECORDINGS and answered completely:**

- **`200` from the INPUT side** — because the fault was in what we COMPUTED.
- **`203` from the OUTPUT side** — because the fault was in what the game
  CONSUMED, which the inputs could not see (`202` §3).

> **AND THE OWNER ASKED FOR THE RECORDER.** `48` and `158` §2 both already said to
> measure rather than reason; **the project owned the rule and did not apply it
> here until asked.** That is the lesson worth carrying, not the matrices.

**NOTHING STAGED. THE COMMIT IS THE OWNER'S.**
