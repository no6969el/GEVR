# 193 — THE PROJECTION IS INNOCENT. 55 SHOTS SAY SO. THE FAULT IS THE ORIGIN, AND `T2` PASSED ON THE WAY PAST.

**2026-08-25. Tiers per `182`. Computed from `gevr.log` (3.2 MB, 401 `SHOT
reported` lines, 55 distinct). NO NEW RUN WAS NEEDED FOR ANY OF THIS.**

---

## §0 — THE THREE ANSWERS

| | |
|---|---|
| **The aim projection** | **INNOCENT. `[MEASURED]` across 55 shots** | §1 |
| **The bullet's ORIGIN** | **UP TO ~0.4 m FROM THE EYE, AND IT VARIES SHOT TO SHOT** | §2 |
| **The second weapon** | **`T2` PASSES — per-weapon muzzles differ 2:1. `U-18` PROCEEDS** | §3 |
| **"off-centre in VR"** | **NOT EXPLAINED. NOT GUESSED AT.** | §4 |

---

## §1 — ►►►► THE CROSSHAIR AND THE BULLET AGREE. THE PROJECTION IS NOT THE FAULT. ◄◄◄◄

**THE HYPOTHESIS THIS KILLS** (mine, formed from the wearer's *"fine in a small
central region, sprays at the sides"* and abandoned before it cost a build): that
the crosshair is projected through one frustum and the bullet reconstructed
through another, giving an error of zero at the centre growing toward the edges.

**IT IS TESTABLE WITHOUT THE HEADSET, BECAUSE `164`'s INSTRUMENT ALREADY LOGS
BOTH SIDES:** `SHOT reported ... ndc=(x,y) ... dir=(x,y,z)`. **`ndc` is where the
crosshair is; `dir` is where the bullet went.** If they are related by a constant
half-tangent, one mapping is being used consistently. If the ratio grows with
eccentricity, they are not.

**`[MEASURED]`, 55 distinct shots, ratio = `tan(dir) / ndc`:**

| axis | median | expected | near centre | off centre |
|---|---|---|---|---|
| **X** | **1.248** | **1.253** = cyclopean render half-tangent | 1.183 | 1.317 |
| **Y** | **0.953** | **0.966** = `tanUp` | 1.047 | 0.965 |

**THE MEDIANS LAND ON THE RENDER FRUSTUM'S OWN TANGENTS TO WITHIN HALF A PER
CENT, AND THE OFF-CENTRE FIGURES DO NOT DIVERGE FROM THE NEAR-CENTRE ONES.**
**`167` IS DOING EXACTLY WHAT IT CLAIMS, AND SO IS `A1`.**

> **AND THE SCATTER IS EXPLAINED, NOT IGNORED** (sd 0.23 on X): `ndc` is the
> CLEAN pixel while `dir` carries the game's own random spread —
> `ge_vr_aim.c:890`, `randfactor * scaledspread`. **Two quantities that are
> deliberately not equal on any single shot.** The median across 55 is the
> statistic that survives it, which is why the medians are quoted and the means
> are not.

**SO: THE GUN, THE CROSSHAIR AND THE BULLET'S DIRECTION ARE ALL ON ONE
MAPPING.** Whatever the wearer is fighting, **it is not the projection**, and no
further frustum work is justified by this evidence.

---

## §2 — ►► THE BULLET DOES NOT COME OUT NEAR YOUR EYE, AND THAT IS THE PARALLAX ◄◄

> `[REPORTED]`, and it is the right question: ***"It almost doesn't even care
> about the aim tool or a combination of them both?"***

**THAT IS CORRECT, AND IT IS BY DESIGN SINCE `164`.** The bullet does **not** fly
through the crosshair. `[READ]` `ge_vr_aim.c:982`: the direction is
`fwd/(-fwd.z)` — **the raw barrel ray** — with the pixel used only to carry the
spread. **The crosshair is a SECOND, INDEPENDENT rendering of the same
direction.** §1 proves the two directions agree.

**TWO RAYS WITH THE SAME DIRECTION AND DIFFERENT ORIGINS NEVER MEET.**

**`[MEASURED]`, the `muzzle=` field across the same 55 shots, game units at
100 u/m:**

| | range | in metres |
|---|---|---|
| **X** | `+10.5` to `-31.3` | **0.10 m right to 0.31 m LEFT** |
| **Y** | `-0.5` to `-26.5` | up to **0.27 m below** |
| **Z** | `-18.9` to `-60.7` | **0.19 m to 0.61 m** in front |

**THE SHOT LEAVES A POINT THAT WANDERS OVER ROUGHLY 40 cm, WHILE THE CROSSHAIR IS
DRAWN FROM THE EYE.** A fixed lateral offset of 0.3 m subtends **17 degrees at
1 m and under 1 degree at 20 m.**

> **THAT IS THE `T7` ANSWER, AND IT WAS ALREADY IN THE LOG:** an origin offset
> produces a miss that **SHRINKS WITH DISTANCE** — `185` `B2`'s "miss shrinks"
> branch. **`B1`/U-06 IS THE NAMED, PRIOR-ART CURE**
> (`vrComputeCrosshairParallax`, 25 lines, no new symbols, `185` `B1`).
> **`[INFERRED]` — the wall test still decides it**, because §4 is unexplained and
> could contribute. **But the origin offset is `[MEASURED]` and is large enough to
> dominate anything else at room distances.**

**AND IT EXPLAINS THE SHAPE OF THE COMPLAINT.** Near the centre of the view, gun
and eye lines are nearly parallel to the sight line and the offset barely reads.
**Off to the side, that same 0.3 m sits ACROSS the aim line rather than along it,
and its angular cost is at its worst.** *"Fine in a small central region"* is what
a fixed origin offset looks like from inside.

**`192` §1 IS THE SAME FINDING FROM THE OTHER SIDE:** the crosshair had to be
pulled to **0.2 m** to fuse — nearer than the gun. **A crosshair that must sit at
20 cm to look right, and a bullet that starts 30 cm away, are one story.**

---

## §3 — `T2` PASSES. THE MUZZLE IS PER-WEAPON, AND OURS IS PISTOL-SHAPED.

**`MAIN-STATION-TASKS` `T2` asked one question: *"does `Switches[3]` CHANGE
between a pistol and a rifle? If not, it is not a per-weapon muzzle and U-18 is
over."* `[MEASURED]`, this run, `MUZZLENODE`:**

| `Switches[3]` `[x100, MODEL frame]` | samples | reading |
|---|---|---|
| `(0, 5671, 35025)` | 696 | the pistol |
| `(0, 2327, 70573)` | 40 | **a SECOND weapon — the muzzle is TWICE as far down the barrel** |
| `absent` | 518 | no gun model this frame (menus, fists) |
| `(-25715, 129, 0)`, `numSwitches=7` | **1** | **a different model entirely. ONE sample — evidence of nothing yet** |

**`U-18` PROCEEDS.** And it bears directly on the wearer's last sentence:

> `[REPORTED]`: ***"the secondary gun that came up when I ran out of the pistol
> bullets sprayed way off to the right when I was aiming forward."***

**`[INFERRED]`, and it follows from §2 rather than standing alone:** our muzzle
origin is a FIXED offset — `-GunOffY 8 -GunOffZ -2`, which `154`/`157` record as
**PD's PISTOL default in centimetres.** A weapon whose real muzzle is twice as far
down the barrel is fired from a point that is wrong **by the difference**, in a
direction that rotates with the gun. **A constant, weapon-dependent lateral
error is exactly what that produces.**

**SO `U-18` AND `B1` ARE THE SAME REPAIR SEEN TWICE: STOP GUESSING WHERE THE
BULLET LEAVES FROM.** `171` already proved all four symbols are patch-reachable.

---

## §4 — WHAT IS NOT EXPLAINED, AND IS NOT GOING TO BE GUESSED AT

> `[REPORTED]`: ***"if I am on the side off center in VR it shoots off to the
> side."***

**THAT IS A DEPENDENCE ON HEAD *POSITION*, NOT DIRECTION, AND NOTHING IN §1-§3
ACCOUNTS FOR IT.** The aim ray is built from the gun's ORIENTATION; stepping
sideways in the play space should not change it.

**IT IS WRITTEN DOWN HERE UNSOLVED ON PURPOSE.** `184` §3a, `180` and `189` §2 are
all records of what happens when an unexplained observation is folded into a
nearby explanation because the explanation was available. **The candidate worth
reading FIRST — and it is a read, not a launch — is whether the roomscale head
TRANSLATION reaches the game's camera at all, or only the rendered view.** If the
view moves and the game's shooting frame does not, every step sideways puts the
two out of register. **`[ASSUMED]`, and one read of `ge_vr_head_transform`'s
consumers settles it.**

---

## §5 — WHAT IS OWED, IN ORDER

1. **`B1` / U-06 — THE PARALLAX.** `185` `B1`, PD's `vrComputeCrosshairParallax`,
   fed from `item_related` (the last impact point), fallback 50000 = infinity.
   **§2 is the measured case for it and it is now the top of the list.**
2. **`U-18` — THE PER-WEAPON MUZZLE** (§3). `T2` has passed; the remaining work is
   the MODEL-frame to camera-frame conversion `171` §4 named as unestablished.
3. **THE §4 READ** — does roomscale translation reach the game's frame? **Before
   any more aim tuning.**
4. **`T9` / `-SeamCompose 1`** still owed from `192` §2, still its own launch.
5. **`noPose`, `U-21`, `U-22`** ride the next build.

> **AND ONE THING TO STOP DOING:** `[REPORTED]` *"this is impossible"* came after a
> session of aim work in which **the aim mathematics was never the fault.** §1 is
> the evidence that closes that line. **Everything left is about WHERE THE BULLET
> STARTS, not where it points.**

**NOTHING STAGED. THE COMMIT IS THE OWNER'S**, both repos.
