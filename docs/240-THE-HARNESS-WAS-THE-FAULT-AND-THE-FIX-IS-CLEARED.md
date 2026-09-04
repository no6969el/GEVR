# 240 — `GETV_GIVE` PERTURBS THE INVENTORY. THE SLOT FIX IS CLEARED.

**2026-08-28. Docs run to `240`. NEXT DOC = `241`.**

> # ►►►► **`GETV_GIVE` IS A BEHAVIOUR CHANGE THAT REACHES GAMEPLAY, AND IT
> # BROKE ITEM PICKUP.** ◄◄◄◄
> **`[REPORTED]` with `GETV_GIVE=8`: *"I wasn't able to pick up a gun until after
> a moment... I went over it, back over it"*, and it only worked after a kill.**
> **`[REPORTED]` with the harness removed and NOTHING ELSE CHANGED:
> *"Seemed to pick up normally."***
>
> ## **ONE VARIABLE. SAME BINARY. THE HARNESS DID IT.**

---

## §1 — AND `234`'s OWN RISK NOTE IS DISCHARGED

**`234` §5 recorded the predicted failure mode:** *"`G-234` proves the slot is
recycled and the intro survives 33 casts. It does not prove the other seventeen
`clear_*_model_obj` call sites behave; they are now reachable and untested."*

**When a prop/item symptom appeared on the very next level run, that note made the
slot fix the first suspect — correctly.** `GETV_SLOTFREE=0` was queued as arm B of
the A/B and **was never needed: arm A answered it.**

`[READ]`, taken before the run rather than after, **five of the ten
`clear_model_obj` call sites in `propobj.c` are genuine cleanup paths** —
`else { if (model) clear_model_obj(model); }` after a failed object creation, plus
the prop-destruction branch. **That is exactly what the release is for.** Five of
eighteen is not a clearance and was not treated as one; **the run is what cleared
it.**

> **THE FIX STANDS. `GETV_SLOTFREE` REMAINS THE OFF-SWITCH** and remains the first
> thing to try if any future prop, item or model symptom appears — **but it is no
> longer a suspect for this one.**

---

## §2 — WHAT `GETV_GIVE` ACTUALLY DOES, AND WHY THIS WAS PREDICTABLE

`[READ]` `ge_ruleset.c`: `GETV_GIVE=<item id>` is *"consumed by the
`INTROTYPE_ITEM` case in `bondview2.c`, which is the record a mission uses to arm
Bond at the start. Going through that path rather than writing a hand slot
directly means the weapon arrives with the game's own inventory and ammo
handling."*

**It writes the mission's own arming record. That is the inventory, at the moment
the level starts** — and `[REPORTED]` the observable consequence is that ground
pickups are refused until something else moves the state on.

> ## ►► `229` §20's ENV-VAR RULE APPLIES TO `GETV_GIVE`, AND NOBODY HAD SAID SO. ◄◄
> **"AN ENVIRONMENT VARIABLE THAT RE-ROUTES THE BOOT PATH IS A BEHAVIOUR CHANGE."**
> `229` §16/§17 cost two retractions to `GETV_MENU`. **`GETV_GIVE` is the same
> shape one layer in: it does not re-route the BOOT path, it re-routes the
> INVENTORY, and it is just as capable of producing a false finding.**
> **RULE: `GETV_GIVE` IS FOR ARMING A MEASUREMENT, NOT FOR JUDGING GAMEPLAY.**
> Anything about pickup, inventory, ammo or weapon switching must be judged on a
> run WITHOUT it.

## §2.1 — AND THE AK TEXTURE REPORT IS CONFOUNDED BY THE SAME RUN

`[REPORTED]` in the same session: *"on the gun, the texture looked a little
different... not the pistol, the secondary... either the AK or the rifle."*
**That observation was made with `GETV_GIVE=8` live.** **It is not withdrawn — it
is UNJUDGED**, and it must be repeated on a plain run with the weapon picked up
the normal way. §4.

---

## §3 — A STALE ID LIST THAT WOULD HAVE COST A RUN

`[READ]` `ge_ruleset.c`'s own comment offers: *"Useful ids: 5 PP7, 12 KF7, 13 ZMG,
15 D5K, 18 KLOBB, 22 AR33, 25 RCP90, 27 SHOTGUN."*

`[READ]` the actual `ITEM_IDS` enum in `bondconstants.h`:

| id | enum | the comment claims |
|---|---|---|
| 5 | `ITEM_WPPKSIL` | "PP7" |
| 8 | **`ITEM_AK47`** (the KF7 Soviet) | — |
| 12 | `ITEM_SPECTRE` | "KF7" |
| 13 | `ITEM_M16` (AR33) | "ZMG" |
| 14 | `ITEM_FNP90` (RC-P90) | — |
| 17 | `ITEM_SNIPERRIFLE` | — |
| 24 | `ITEM_GRENADELAUNCH` | — |
| **25** | **`ITEM_ROCKETLAUNCH`** | "RCP90" |

**The list is wrong for every entry checked.** `[READ]` it does say *"The full
list is the ITEM_IDS enum in `src/bondconstants.h`"*, and **that is the source of
truth.** **`168` §5's rule in a new costume: grep the header, do not trust the
summary beside it.**

**One thing the comment gets right by accident: `25` really is the rocket
launcher**, so `COLOUR_BUGS.md`'s explosion repro (`GETV_GIVE=25`) was correct.

---

## §4 — NEXT: THE AK TEXTURE, ON A CLEAN RUN, AS THE RGBA16 CENSUS

**`239` §3 left `GETV_RGBA16BE` commented out and per-run.** Upstream's stated
blocker for promoting it is that **the census has no coverage** — no second RGBA16
consumer was ever found to test it on. **A weapon texture that looks wrong at the
default setting is exactly that missing frame, IF it is RGBA16 at all.**

**The `[getv][tex16be] f<N> 16b_images=N 16b_texels=N` line prints every 60 frames
with NO knob set**, so a plain run answers "is this gun even an RGBA16 consumer?"
without an A/B.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
cd C:\Users\<USER>\Desktop\GoldenEyeVR\goldeneye-native\getv\build-windows
$env:GETV_STAGE = "9"
.\goldeneye.exe *> run_ak.log 2>&1
```

**NO `GETV_GIVE`.** Take the weapon off the tower guard the way the game intends,
look at it, walk with it, then X.

| `16b_images` while holding it | next |
|---|---|
| **rises above 0** | the gun IS an RGBA16 consumer. **Then the A/B — same run plus `GETV_RGBA16BE=1` — IS the census upstream asked for**, and it decides the promotion question either way |
| **stays 0** | the gun is not RGBA16, the fault is unrelated to `237`, and the switch stays a per-run knob |

## §5 — WHAT IS NOT CLAIMED

- **No mechanism for the pickup fault inside `GETV_GIVE`.** `[MEASURED]` only that
  removing it removes the symptom. The `INTROTYPE_ITEM` path is where to look if
  it ever matters; it does not matter today, because the knob is optional.
- **`239`'s two suspects are both `[REPORTED]` cleared** — *"no more sound latency
  ... the look looked alright"* — but they were unpicked TOGETHER, so which of the
  two caused which half is still `[ASSUMED]`.
- **The explosion is `[REPORTED]` still wrong** with `GETV_RGBA16BE` off, which is
  expected and consistent with `237`.

---

# ►►►►►► §6 — RETRACTION. §1 AND THE TITLE ARE WRONG. ◄◄◄◄◄◄

**Written within the hour, before anything was built on it.**

`[REPORTED]`, clarifying the plain run: ***"it doesn't let me pick up weapons. I
got confused because it let me pick up key cards and body vests, but it doesn't
let me pick up the guns."*** And of the EARLIER `GETV_GIVE` run: ***"I did [pick
one up], because I shot them with it. This time, I couldn't."***

> ## **SO THE ARROW POINTS THE OTHER WAY.**
> **WITH the harness a weapon was eventually picked up. WITHOUT it, none was.**
> **`GETV_GIVE` IS NOT THE CAUSE. §1's "the harness did it" IS WITHDRAWN, AND SO
> IS THIS DOCUMENT'S TITLE.**

## §6.1 — WHY I GOT IT WRONG, AND IT IS A GATE DEFECT

**The gate said *"walk onto the first weapon on the ground and try to pick it
up"*, and the report came back *"seemed to pick up normally"* — which was TRUE of
key cards and body armour and FALSE of weapons.** **The gate did not name what
had to be picked up, so a partial pass read as a pass.**

**`189` §3 and `195` §2 are the same lesson twice already: CHECK A GATE AGAINST
THE GEOMETRY — here, against the OBJECT CLASS — BEFORE CHECKING IT AGAINST THE
BUILD.** A gate that cannot distinguish "picked up a keycard" from "picked up a
rifle" cannot answer a question about weapon pickup.

## §6.2 — THE DISCRIMINATOR IS NOW MUCH SHARPER

`[REPORTED]` **non-weapon items pick up; WEAPONS DO NOT.** That is a far better
clue than anything in §1: **the fault is specific to the weapon pickup path, not
to pickup in general.**

**AND `234`'s SLOT FIX IS BACK AS THE FIRST SUSPECT.** `[READ]` `propobj.c:12394`
— one of the ten `clear_model_obj` call sites the fix made live — sits in the
`else` of `sub_GAME_7F051F30(weapon, self, (ModelFileHeader *)prop_header,
lastobjentry, objinst)`. **That is a weapon path.** §1 read five call sites and
called them "genuine cleanup"; **a read of five is not a clearance, which §1 said
and then ignored.**

## §6.3 — ARM B, WHICH SHOULD HAVE RUN BEFORE §1 WAS WRITTEN

**Same binary. One variable. No build.**
```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
cd C:\Users\<USER>\Desktop\GoldenEyeVR\goldeneye-native\getv\build-windows
$env:GETV_STAGE = "9"
$env:GETV_SLOTFREE = "0"
.\goldeneye.exe
```
**THE GATE, STATED PROPERLY THIS TIME: walk over a DROPPED GUN — a rifle from the
tower guard, or the AK on the floor — and press the use button. A KEYCARD OR A
BODY ARMOUR PICKUP DOES NOT COUNT AND MUST NOT BE REPORTED AS ONE.**

| result | conclusion |
|---|---|
| **the gun is picked up** | **`234`'s fix caused it.** A slot is being released while the weapon path still references it. The fix narrows to the call sites provably safe, or `ge_slot_release` gains a guard |
| **still no gun pickup** | **neither the fix nor the harness.** A pre-existing weapon-pickup fault in the port, never noticed because nobody had played far enough into a level. **MGB64 is then the control: does IT let you pick up a rifle on Bunker?** |

## §6.4 — AND `234`'s GATE WAS NEVER THIS EITHER

**`G-234` PASSED on what it measured** — 33 cast reuses, one slot, no crash — and
**`234` §5 said in as many words that the other seventeen call sites were
"reachable and still untested".** **This is that risk arriving, and the honest
position is that the fix is UNJUDGED for props and weapons, not proven.**
**`GETV_SLOTFREE=0` exists precisely so this costs one run and no rebuild.**
