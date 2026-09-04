# 176 — U-09. THE AI ALREADY KNOWS YOU CROUCHED. IT IS JUST NEVER TOLD.

**2026-08-25. THE READ IS DONE AND THE DESIGN IS DECIDED. Not yet built.**

> ## THE OWNER'S REQUIREMENT
>
> ***"It would be great if the AI would know that you crouched when they see you
> and shoot downwards."***
>
> ## **THAT BEHAVIOUR IS ALREADY IN STOCK GOLDENEYE, FULLY WRITTEN.**

---

## 1. THE FINDING — AND §1 AS FIRST WRITTEN CITED THE WRONG FUNCTION

> ### ►► CORRECTION, SAME DAY, BEFORE ANYTHING WAS BUILT. ◄◄
> **The first version of this section cited `chrprop.c:1413`. That is inside
> `chraiFistAttackHandler` — it is YOU PUNCHING THEM, and `hitpart` is which part
> of the GUARD your fist lands on. It is not a guard shooting you.**
> **The conclusion below survives; the mechanism is different and it matters,
> because the two are driven by DIFFERENT FIELDS.**

**THE REAL SITE IS `chraction.c:5854`, in `chrlvUpdateAimendsideback` — the
guard's aim update:**

```c
ducking_height = bondviewGetPlayerDuckingHeightRelated(g_CurrentPlayer);
...
dy -= ducking_height * (0.55f + 0.1f * random * arg4);   /* and three sibling cases */
```

and (`bondview2.c:9150`):

```c
f32 bondviewGetPlayerDuckingHeightRelated(struct player *player) {
    return player->eyeheight + player->field_88 + player->ducking_height_offset;
}
```

> ## **THE GUARD AIMS AT A FRACTION OF THE PLAYER'S ACTUAL HEIGHT. Lower the
> ## height and he aims lower — no special case, no crouch flag, it falls out of
> ## the arithmetic he already does.**

**AND THE AI NEVER READS `crouchpos` AT ALL** — grepped across `chr.c`,
`chraction.c` and `chrai*.c`: **zero hits for `GetCrouchPos` or `eyeheight`.**
It reads **height**, through that one getter. **So the thing to drive is
`ducking_height_offset`, not the crouch enum.**

**The conclusion is unchanged and is still the point: the behaviour is stock, and
has never been told, because `ducking_height_offset` only moves when `crouchpos`
moves and `crouchpos` only moves on a BUTTON PRESS.** `165`'s lesson, again.

**This is `165`'s lesson again, exactly** (*"GoldenEye has other button-gated
states that VR will never enter"*), and `169` U-17 predicted a repeat. **It is the
second one found.**

## 2. `86` OPTION B IS BLOCKED, AND WE DO NOT NEED IT

`86` framed this as *"Option A (ceiling clamp only) vs Option B (drive
`eyeheight`)"*. **Option B is blocked at the patch boundary and the mandatory grep
(`168` §5) says so before a line is written:**

| symbol | in `patches/structs.h`? |
|---|---|
| `crouchpos` | **YES** — `:1985` |
| `autocrouchpos` | **YES** — `:3795` |
| **`eyeheight`** | **NO** |

**Our own S0 instrument has been printing `eyeheight=absent-from-patch-struct` for
weeks. That was the answer to a question nobody had asked yet.**

> ## **AND IT DOES NOT MATTER, BECAUSE IN VR THE VIEW ALREADY LOWERS.**
> **You crouch and the headset descends. The picture is free.** `86`'s Option B
> existed to lower the CAMERA; roomscale does that physically. **The only thing
> missing is telling the GAME — and that is `crouchpos`, which IS reachable.**

**So the A-vs-B choice is void. The slice is: derive a crouch state from head
height and write it.**

## 3. EVERY CONSUMER, COUNTED — SIX SITES, ALL NAMED

`currentPlayerGetCrouchPos()` returns `min(crouchpos, autocrouchpos)`
(`bondview.c:1558`), so **autocrouch can only ever force you MORE crouched** and a
physical crouch composes with it correctly for free.

| site | what it does | wanted? |
|---|---|---|
| **`chrprop.c:1413`, `:1416`** | **the AI's hit part** | ►► **THE WHOLE POINT** ◄◄ |
| `bondview2.c:6380` | `speedforwards/sideways *= 0.5f` at SQUAT | **YES — owner's decision** |
| `bondview2.c:6756`, `:6760`, `:6767` | `ducking_height_offset` — SQUAT drops the camera by `FULL_CROUCH_OFFSET`, HALF by `-60.0f` | ►► **NO — MUST BE SUPPRESSED, see §4** ◄◄ |

**Six readers. Two are the feature, one is wanted, three must be suppressed.
Nothing else in the tree reads it.**

## 4. ►►►► THE DOUBLE-CROUCH, AND IT IS THE TRAP IN THIS SLICE ◄◄◄◄

`bondview2.c:6756` moves the game camera **down** when `crouchpos` says SQUAT.
**In VR the camera is already down, because your head is.**

> **LEFT ALONE, THE PLAYER WOULD CROUCH TWICE — once in reality and once in the
> engine — and end up far below where he actually is.** That would read as "the
> crouch is too strong" or "the floor is wrong", and would be blamed on scale.

**OWNER'S DECISION: suppress the engine's drop.**

> ### ►► BUT NOT BY ZEROING THE FIELD — THAT WOULD DESTROY THE FEATURE. ◄◄
> **§1's correction makes this the crux: `ducking_height_offset` is the SAME field
> the guard's aim reads. Zero it and the camera stops dropping AND the AI stops
> knowing.** The first draft of this document proposed exactly that, and it would
> have quietly removed the thing the slice exists to add.

**THE RESOLUTION: let the engine do its work, and CANCEL THE CAMERA DROP ON OUR
SIDE.**

`rt64_projection_processor.cpp:159` — `viewMatrix = mul(viewMatrix, eye.viewOffset)`
— **the game's view matrix is the BASE and our eye transform composes onto it**,
which is exactly why the engine's drop reaches the headset. **It is also why we
can undo it: the patch publishes `ducking_height_offset` to the host, and the host
adds it back into the eye transform's Y.**

| consumer | sees the crouch? | |
|---|---|---|
| the guard's aim (`chraction.c:5854`) | **YES** | the feature |
| collision / ceiling (`bondview2.c:4567`) | **YES** | wanted |
| speed penalty (`bondview2.c:6380`, via `crouchpos`) | **YES** | owner's decision |
| **the VR camera** | **NO — cancelled** | your head is the only thing that moves the view |

**AND THE ENGINE'S SMOOTHING IS PRESERVED.** `bondview2.c:6770` eases
`ducking_height_offset` toward its target with `chrobjApplySpeed`. **Zeroing the
field every frame would have fought that easing; cancelling it in the eye
transform leaves it untouched and reads the settled value.**

## 5. CALIBRATION — OWNER'S DECISION: AT LEVEL START

**PD's numbers, measured and already recorded in `102`:**

- thresholds are **FRACTIONS OF THE CONFIGURED STANDING HEIGHT**:
  **`< height/1.3` = DUCK (HALF)**, **`< height/1.6` = SQUAT**
- **a 90-sample MEDIAN** calibration (`vr_openxr.cpp:1286-1308`)
- `VR_MAX_HEAD_CM 250` glitch swallow; slider clamp **130-200 cm**

> **AND THE BUG PD ALREADY PAID FOR, WHICH WE WOULD HAVE WRITTEN**
> (`bondmove.c:2571-2578`): **a RUNNING MAX was the original standing reference,
> and a physical JUMP raised it — leaving the player spuriously ducking
> afterwards.** Fractions of a *configured* height, not of a running max.

**Take the 90-sample median at level start.** A median rather than a mean because
one bad locate cannot move it, which is the same reason `159` preferred a guard to
a doorway.

**KNOWN RISK, RECORDED NOW:** starting a level already crouched calibrates low and
everything reads too tall until recentre. **`161` P2-1 (recentre moves to level
start) is the natural companion and should land in the same slice or immediately
after.**

## 6. WHAT IS STILL OWED BEFORE BUILDING

**The ceiling probe.** `89` read 10 named
`bondviewUpdatePlayerCollisionPositionFields` (`bondview2.c:4557`) as the place a
written height must survive. **Whether writing `crouchpos` alone is enough to keep
you out of low geometry — or whether the collision fields need the PD
save/write/probe/restore dance (`102`, `bondwalk.c:1876-1901`) — is UNREAD.**

**It does not block the AI behaviour, which is §1 and needs none of it.** So this
slice can ship the requirement and leave the ceiling as its own question. `48`
rule 5.

## 7. GATES

- **G-176-1 — THE REQUIREMENT.** Let a guard see you, then physically crouch.
  **His shots must go lower.** `chrprop.c:1413` is the mechanism; the instrument
  is the wearer.
- **G-176-2** — the S0 line's `crouchpos=` changes from `2` as you crouch, and
  returns to `2` when you stand.
- **G-176-3 — NO DOUBLE CROUCH.** The view drops by exactly as much as your head
  did, and no more.
- **G-176-4** — movement slows while squatting (owner's decision), and recovers.
- **G-176-5** — `-NoXr` untouched: button crouch behaves exactly as stock.
