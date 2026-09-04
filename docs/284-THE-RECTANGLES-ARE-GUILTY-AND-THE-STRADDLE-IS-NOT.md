# 284 — THE PER-ROOM RECTANGLES ARE THE CAUSE. THE STRADDLE IS NOT. `281` IS CLOSED.

**2026-08-31. BUILT AND RUN.** `goldeneye.exe` **2026-08-31 01:07, 18,021,956 bytes**
(`GETV_ROOMSCISSOR` + `GETV_PORTALOPEN` + `GETV_PORTALBOX`). Two arms, one behaviour change each,
Streets 29, `GETV_WIDESCREEN=0`, `GETV_SIMDIV=1`, 60 Hz, `2560x1369`.

> ## THE ONE-LINE RESULT
> **`[REPORTED]`, and it is the whole finding: with every room given the FULL VIEW instead of its
> portal rectangle, the session lead reports *"much better. I do not see the issue anymore."*
> With `281`'s straddle patch instead, *"they are back and you can see the problem again."***
> **THE RECTANGLES CUT PIXELS THAT NOTHING ELSE PAINTS. THE NEAR-PLANE STRADDLE IS NOT THE
> MECHANISM. This is row 3 of `RUN-SHEET-283` §4, written before either arm ran.**

---

## §1 — THE ARMS

| arm | switch | gates | result |
|---|---|---|---|
| A | `GETV_ROOMSCISSOR=0` | banner present · `window: 2560x1369` · `ours: x=367.333` · `game_exit requested` | **`[REPORTED]` holes GONE** |
| B | `GETV_PORTALOPEN=1` | banner present · same three | **`[REPORTED]` holes BACK** |

Both arms self-verified and both carry their terminating record (`262` §5). Neither took an F9 dump;
**for arm A the screen was always going to be the instrument** and the run sheet said so in advance.

**AND A SECOND `[REPORTED]` WORTH RECORDING, BECAUSE IT WAS PREDICTED OTHERWISE:** `RUN-SHEET-283`
§0 warned arm A would make the picture *"wrong in NEW ways -- walls through walls, rooms visible
where they should not be."* **The lead did not report any of that.** *"Much better"*, unqualified.
`[OPEN]` — one viewpoint on one level is not a clean bill, but the predicted cost did not appear
where it was predicted.

## §2 — WHAT IS NOW DEAD

- **►► `281`'s "minimum shippable" patch is DEAD, killed by a run, not by an argument.** Making
  straddling portals fail open to the parent rectangle changes nothing the lead can see. `283` §5
  predicted this might happen and said why: `port=46`'s tight side came from verts that were **in
  front**, and no repair to the trimming moves it.
- **`281`'s patch 1 is dead by the same measurement** — it is a more careful version of the same
  idea, aimed at the same portals, and those portals are not the ones doing the damage.
- **`283` §3's attribution of the LEFT slab to the straddle is RETRACTED** (I flagged it as unsafe
  before this build and the build settled it). The edge match at `0.07` game units stands as a
  measurement; **the causal claim attached to it does not.**
- **`282` §2.2 stays retracted** (`283` §2) — straddles really do lose their bound. It is just not
  what makes these holes.

## §3 — WHAT IS NOW KNOWN, AND HOW LITTLE IT IS

**KNOWN:** the per-room rectangle is narrower than the pixels the picture needs, at more than one
place, on more than one edge, with and without a straddle. Removing it fixes the picture.
**NOT KNOWN: why.** No mechanism is named, and this doc names none. What we can say from `283`'s
probe, which measured it directly:
- `port=51` produced `(233.05,30)-(319,210)` with **`drop=0 cross=0`** — every vert in front, an
  ordinary measurement of that doorway — and the building it should have covered ends at game
  `216.3`. **A gap of ~17 units with nothing exotic in the arithmetic.**
- So the rectangle is not "corrupted"; it is a **faithful projection of the portal polygon**, and
  the picture needs more than the portal polygon.
- **`[INFERRED]`, and it is the next thing to test, not a conclusion:** on a level like Streets the
  "rooms" are open outdoor regions divided by invisible planes, and buildings can sit across a
  divider. Geometry belonging to room B can be physically on room A's side and still be visible.
  Clipping room B to the doorway then removes real wall, and room A has nothing there to replace
  it. **DO NOT ACT ON THIS UNTIL IT IS MEASURED.**

## §4 — ►► THE CANDIDATE THAT FITS THIS PROJECT'S OWN RULES: DROP THE PER-ROOM SCISSOR ON PC

**The per-room scissor is a FILL-RATE optimisation.** It exists so the RDP does not shade pixels
that a nearer room will cover. `00-STATE` §1 rule 3's table puts hardware budgets in the **FREE**
column: *would a 1997 player notice this as the game behaving differently, or only as the absence
of a limit the console imposed?* **A player notices the holes. Nobody notices the absence of a
fill-rate saving on an RTX 5090.**

**THE COST, NAMED HONESTLY:**
1. **Overdraw.** More pixels shaded. The budget it eats into: `[MEASURED]` CPU `0.890 ms` and GPU
   `0.832 ms` on CRADLE against `11.111 ms` at 90 Hz (`272` §5.2, `273` §5.1). **There is room.
   It must still be measured, not assumed** — `P5`, and `273` §8's run condition (`GETV_FPS=0`).
2. **Ordering.** The secondary/transparent pass is bucketed by portal depth
   (`sub_GAME_7F0B3C8C`). Without a containing rectangle, **glass, water and smoke are where a
   regression would show first** — Facility's glass, Dam, Cradle. Streets at one viewpoint is not
   a test of that.
3. **It is a real behaviour change and it must not arrive silently.** `268`'s `auto` divider and
   `GETV_WIDESCREEN`'s default-on each cost a whole session by changing what the renderer did
   without saying so. **Whatever the default becomes, it prints a banner.**

**►► AND IT IS GOOD FOR THE DESTINATION.** In stereo every room needs a portal rectangle **per
eye** — two different rectangles for the same room, and a hole that sits at a different screen x in
each eye is a depth conflict, not a flat blemish (`281`'s VR note, which is correct). **Removing the
per-room scissor removes that problem entirely rather than doubling it.** `P4`: pay the structural
cost once. `258` STAGE 6.

## §5 — WHAT MUST HAPPEN BEFORE THE DEFAULT MOVES

1. **A WEAR PASS ON MORE THAN ONE LEVEL, WITH THE TRANSPARENT PASS IN VIEW.** Facility (glass),
   Dam, Cradle, and the front-end. Looking for: things visible through walls, glass in the wrong
   order, smoke or water drawn over what should occlude it.
2. **THE COST, MEASURED BOTH WAYS.** `GETV_GPUTIME=1` with `GETV_FPS=0` (`273` §8), and the CPU
   term with `WORK_OVER=` (`271`), switch off vs on, same level, same spot.
3. **THEN the default is the session lead's call**, and either way the knob stays and says what it
   is doing.

## §6 — STILL OPEN, UNCHANGED
The amount-vs-resolution arm (`279` §5) · a black-wall dump (`279` §6, run C missed it) · whether
retail shows any of this (`283` §5.2) · and all of `277` §9: the two hoist sites, the two
intro-skip audio falsifiers, the `MoveBond` counter, plus `278` §6's hoist-1 read.
**`00-STATE` §3 item 2, §4 and the currency line are owed for `280`, `282`, `283` and this doc.**
