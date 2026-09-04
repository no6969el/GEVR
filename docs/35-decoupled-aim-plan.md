# 35 — Phase 3 plan: decoupling aim from view

**PROPOSAL, 2026-08-22. NOTHING BUILT.** Requested alongside 3f-5. This one opens
with a contradiction in our own documents that has to be settled by observation
before any of the design below is worth writing.

---

## The contradiction, first

`00-START-HERE` and `30` both say:

> It does not decouple aim from view. Where you look and where you shoot stay the
> same thing. **Turning your head turns the gun.**

**The mechanism says that should not be true.** `ge_vr_head_transform` builds the
head rotation into `VrEyeParams::viewOffset`, which is composed as `v * V * E * P`
— `E` acts in **view space, after the game's own camera**. The game is never told.
`vv_theta` and `vv_verta` (`bondview.h:0x0148` and `0x0160`) — the player's look
angles, which are what the gun is aimed along — cannot see a matrix RT64 applied
downstream of them.

So turning your head should move the **view** and leave the **aim** exactly where
the stick put it. Which is a different problem with a different fix.

`30` risk 3 describes what probably produced the report:

> The viewmodel rides the game camera, so under head rotation it will swing with
> the world instead of staying in front of you.

Head-turn, gun visibly swings away from where you are looking. That reads as "the
gun moved with my head" and it is very nearly the opposite: the gun stayed put in
the world while your view left it.

**This must be settled before designing anything.** The two readings need
different work, and one of them means Phase 3 is substantially smaller than the
roadmap assumes.

### The experiment, which needs no code

On the 3f-5 build, in a level, standing still:

1. Put the crosshair on a distinct object using the stick only. Do not move your head.
2. **Turn your head 30 degrees and stop.** Do not touch the stick.
3. Ask one question: **is the crosshair still on that object?**

| Observation | Meaning | Consequence |
|---|---|---|
| Crosshair stayed on the object, drifted off screen centre | Aim is **already decoupled**. The docs are wrong | Phase 3 shrinks to a reticle/viewmodel problem |
| Crosshair moved with your head, still on the object | Aim genuinely follows the head | Phase 3 as scoped, and the mechanism needs re-deriving |
| No crosshair to speak of | Legibility problem first | See the note at the bottom |

**Ask of this gate what `32` failed to ask: what would the build have to do
differently for each outcome?** Outcome 1 is what the composition order predicts.
Outcome 2 would mean something reaches `vv_theta` that nobody has documented, and
finding it matters more than any design below.

---

## The design, contingent on outcome 2 — or on wanting hand aim regardless

Decoupling has two halves and they are not equally hard.

### Half 1 — view-only head rotation

**Already built.** `E` in view space is exactly this. Nothing to do.

### Half 2 — aim from somewhere other than the stick

This is the half that needs the patch, because `vv_theta` / `vv_verta` live in the
player struct on the MIPS side and nothing in the host can reach them.

Three candidate sources, in increasing order of what they demand:

| Source | What it needs | Cost |
|---|---|---|
| **Head** | Feed the head's yaw/pitch into `vv_theta`/`vv_verta` | Smallest. But it *re*-couples aim to view, which is the opposite of the request |
| **Right hand** | OpenXR `aim` pose, located into `g_appSpace`, converted to game angles | The real answer. Needs the controller slice first |
| **Hybrid** | Hand when tracked, stick otherwise | Right eventually, wrong to start with |

**The hand path is what "6DoF" means here, and it has a hard prerequisite:**
controller poses are located into `g_appSpace` — the same `LOCAL` space that
3f-5 just recentred. Hand aim built before 3f-5 would have been calibrated
against an origin 4.55 m wrong. **It is now safe to build; it was not this
morning.**

### The part that will be underestimated

`vv_theta` is not a free variable. `bondview.c:1427-1434` shows the game
maintaining `speedtheta`, `vv_verta360`, `vv_cosverta` and `vv_sinverta` as
*computed companions* of it, and `gun.h:359`'s `gunSetBondWeaponSway` takes
`speed_verta` and `speed_theta` — so weapon sway is driven by the **rate of
change** of the look angles, not their value.

Write `vv_theta` directly and the derived set goes stale: sway, boost direction,
and anything reading `vv_cosverta` all start describing a look direction that is
no longer the one in use.

**This is `21`'s rule for the fourth time — *check who else writes what you
write*, and its mirror, check who else READS it.** `21` was a patch changing a
value the game inspects; `26` a value read back and compared to a literal; `27` a
function pointer the host owned; `32` a knob whose consumer had been deleted. The
answer here is the same shape: drive the game's own setter path if there is one,
or update the companions in the same place, and never poke the field alone.

**Finding that setter is the first real task of this phase**, ahead of any OpenXR
work.

---

## Gates, written before the code

| # | Check | Pass | What would have to differ to fail |
|---|---|---|---|
| 1 | The experiment above | An unambiguous answer to one question | Nothing — it is an observation, and it is why it comes first |
| 2 | Aim source off (`GE_VR_AIM=0`) | Byte-identical to 3f-5 | The new path runs when it must not |
| 3 | Point the hand, stick untouched | Crosshair tracks the hand | Pose conversion or the angle convention |
| 4 | Sway while turning by hand | Behaves as it does on the stick | The companions went stale — the failure above, made visible |
| 5 | `-NoXr` | 60 fps, clean close | A patch change reached the non-VR path |

Gate 4 is the one that would otherwise be found by feel, three sessions later,
as "the gun feels wrong".

---

## Sequencing

1. **The experiment.** No code. Possibly ends the phase early.
2. **Find the game's own look-angle setter**, and what else reads the companions.
3. **Controllers — buttons and sticks** (already agreed as the next slice).
4. **Hand aim**, on the pose those bindings make available.

Steps 1 and 2 are both free, and 2 is the one that decides whether this phase is
a slice or a month.

---

## Note: legibility may outrank all of this

The view is reported as hard to see independently of the height error, and no
evidence has been captured yet — `-Sbs` screenshots are the ask. If the crosshair
is not legible, gate 1 above cannot even be run, which makes legibility a
**prerequisite of this phase** rather than a parallel concern. Also unexplained:
the session ran at **60 fps, not 90**, on a `ds_option: 4` multiplier over
4140x3292 per eye.
