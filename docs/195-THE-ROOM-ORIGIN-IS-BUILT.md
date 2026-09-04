# 195 — THE ROOM ORIGIN IS BUILT. ONE ADDITION, ONE KNOB, NO NEW SYMBOLS.

> **►► §3 IS RETRACTED. `196`. ◄◄**
> **It claimed "THE PICTURE WAS ALREADY CORRECT" and put the term at the single
> bullet consumer. `[REPORTED]` in one run: the gun moves OPPOSITE to the wearer,
> in BOTH arms of the knob — the picture had the same fault, from the same
> missing term.** The term now lives in `handPos`, above every consumer, and is
> NO LONGER added in `muzzle_origin` (both would double-count). **`G-196` comes
> before `G-194`.** `196` §3 has the rule that came out of it.

**2026-08-25. `194`'s slice. Tiers per `182`. BUILT, UNRUN.**

---

## §1 — WHAT CHANGED

**ONE FILE OF SUBSTANCE: `src/main/rt64_render_context.cpp`. Plus `vr.ps1`.**
**HOST-SIDE ONLY — no patch code, NO new `RECOMP_PATCH` symbols, so `136` does
not apply and ONE BUILD IS ENOUGH.** No header in `115`'s cross-boundary set.
**`168` §5's mandatory grep has nothing to fail on: zero game symbols.**

```
origin = (hand - head)        <- docs\157, what muzzle_origin returned until now
       + (head - gameCamera)  <- docs\194, the missing term
```

**The room term is computed beside the hand, inside `hand_override`, from the
SAME `headOrigin` that `ge_vr_head_transform` writes into the eye view matrix** —
`48` rule 8, one place computes it. **It is added in `muzzle_origin`, not into
the shared global. See §3.**

**THREE THINGS MATCH THE VIEW DELIBERATELY**, and each would be a silent fault
if it did not:

| | and NOT | why |
|---|---|---|
| `env.worldUnitsPerMetre` | `handUnitsPerMetre` | the view scales the head translation with the EYES' number (`156` S1). **Both are 100 today, which is exactly why it is written down — wrong here would be invisible until somebody sweeps one** |
| `env.posSign*` | `ge_vr_hand_pos_sign_*` | those belong to the hand delta; these belong to the view translation |
| `Rhead` | — | so the term lands in the head's frame, like `handPos` beside it |

**`-NoRoomOrigin` (`GE_VR_ROOM_ORIGIN=0`) reverts exactly**, and clears the term
rather than leaving it unset (`48` rule 13), so the off arm cannot fire a stale
displacement.

**AND AN UNSET ROOMSCALE SESSION IS BYTE-IDENTICAL TO BEFORE**: stand where you
started and the term is zero by construction (`131`'s rule that a new term stays
invisible until exercised).

---

## §2 — `G-194`, CORRECTED. **THE VERSION IN `194` §3 WAS WRONG.**

> ### ►► THE GATE I FIRST WROTE WAS *"step sideways WITHOUT MOVING THE GUN; the
> ### two impacts must agree."* **THAT IS GEOMETRICALLY FALSE AND WOULD HAVE
> ### FAILED A WORKING FIX.** ◄◄
> **A ray with a FIXED DIRECTION fired from an origin translated half a metre
> lands half a metre away — that is correct behaviour, not a fault.** Demanding
> the impacts agree would have demanded the bullet ignore the very translation
> this slice exists to deliver. **`189` §3 was the same class of error** (a gate
> that could not pass), and the rule from it stands: **a gate must be checked
> against the geometry before it is checked against the build.**

**THE CORRECT TEST KEEPS THE TARGET FIXED AND LETS THE DIRECTION CHANGE:**

1. From the **CENTRE** of your space, put the crosshair on a **MARK** and fire.
   Note where it lands.
2. **Step as far sideways as the space allows. RE-AIM AT THE SAME MARK.** Fire.
   **IT MUST STILL HIT** — the same as it did from the centre.
3. **Re-run with `-NoRoomOrigin`.** From off-centre it should now **MISS, by
   roughly how far you stepped.**

> **JUDGE THE DIFFERENCE BETWEEN THE TWO ARMS, NOT THE ABSOLUTE MISS.**
> `193` §2 measured a muzzle sitting **0.19-0.61 m** from the eye, and that
> parallax is present in BOTH arms and is `B1`'s job. **What `G-194` owns is the
> part that appears only when you move your feet.** **Step as far as you can** so
> the roomscale term dominates the muzzle term rather than competing with it.

> **AND THE FALSIFIER, STATED IN ADVANCE:** if the off-centre shot still misses by
> your displacement with the term ON, it is going into the wrong frame — **look at
> `Rhead` and the signs before anything else**, because a rotation error would
> apply the correction sideways rather than removing it. **If it misses by TWICE
> your displacement, the sign is inverted** — one flip, not a rethink.

---

## §3 — THE ONE TRAP IN THE SLICE, AND WHY THE TERM IS NOT IN THE SHARED GLOBAL

**`g_geVrLastHandPos` IS ALSO THE DRAWN GUN'S ANCHOR.** `157` publishes it before
the grip offset precisely so the muzzle and the picture come from one number.

**SO ADDING THE ROOM TERM THERE WOULD HAVE MOVED THE VIEWMODEL TOO** — the gun
would slide across the room as the wearer walked, **and it would have read exactly
like a broken grip offset**, which is a fault this project has already
mis-diagnosed twice (`154` §1, `157` §6.1).

**THE PICTURE WAS ALREADY CORRECT.** The view matrix carries the translation, so
the drawn gun is anchored to the wearer's head, where it belongs. **Only the
ENGINE'S BULLET FRAME was missing it.** The term is therefore added at the single
consumer that needs it — `muzzle_origin` — and nowhere else.

**`vr.ps1` SAYS SO OUT LOUD ON EVERY LAUNCH:** *"the DRAWN GUN is unaffected and
should be... A viewmodel that slides is a BUG."* **A gate that names the wrong
outcome as well as the right one is `48` rule 9.**

---

## §4 — WHAT IS OWED, IN ORDER

1. **BUILD ONCE. RUN `G-194`** (§2), both arms.
2. **`B1` / U-06 — THE PARALLAX** (`193` §2). **Judgeable once §2 passes**, and not
   before: parallax cannot be measured against an origin that moves when the
   wearer shifts his weight.
3. **`U-18` — THE PER-WEAPON MUZZLE** (`193` §3). `T2` PASSED.
4. **`T9` / `-SeamCompose 1`**, its own launch (`192` §2).
5. **`noPose`** (`190` §3), **`U-21`**, **`U-22`** — all still unbuilt, all cheap,
   none on the critical path.

**NOTHING STAGED. THE COMMIT IS THE OWNER'S**, both repos.
