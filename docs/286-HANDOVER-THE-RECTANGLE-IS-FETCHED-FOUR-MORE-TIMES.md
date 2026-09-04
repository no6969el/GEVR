# 286 — HANDOVER. THE SWITCH WAS INCOMPLETE BY CONSTRUCTION, AND THE PLAY SETTINGS ARE NOW KNOWN.

**2026-08-31. Closing doc for the session that produced `280`, `282`, `283`, `284`, `285`.**
Binary in play: **`goldeneye.exe` 2026-08-31 01:07, 18,021,956 bytes.**

---

## §1 — WHY TWO HOLES SURVIVED `GETV_ROOMSCISSOR=0`. IT IS NOT A MYSTERY.

**`[MEASURED]`, and it answers the session lead's question directly.** The switch replaced the
per-room rectangle at the **two room draw calls only** — `bg.c:1051` (primary pass) and `:1132`
(secondary/xlu). **The rectangle is fetched and applied at FOUR other sites the switch never
touched**, all reading the *same* stored box:

| site | what it clips |
|---|---|
| `chr.c:3437` | a character's model |
| `chr.c:186` | a character, earlier test |
| `explosion.c:874` | an explosion |
| `propobj.c:7570` | a prop — **the parked car in `dlgrab_8040` is one** |

All four call `getPropCombinedRoomsBBox2D` (`propobj.c:13861`), which walks the prop's rooms and
unions `bgGet2dBboxByRoomId` — **`bg.c:751`, reading `dword_CODE_bss_8007FFA0[].bbox`. The identical
rectangle.**

**PROOF IT IS STILL LIVE, from a dump taken WITH the switch on:** `dlgrab_8040` carries
`(832,120)-(1276,840)` with **613 triangles under it**, plus `(4,120)-(280,840)` 577,
`(4,120)-(44,568)` 593, `(4,120)-(28,428)` 575 — in a run whose banner says every room got the full
view. **The switch is incomplete by construction, not by accident, and the next session should
finish it before concluding anything about what survives.**

`[MEASURED]` the surviving slab in `8040`: right edge at window x ~`1550` = game `207.3`, against
that frame's `(832,...)` rect whose `ulx` is game `208` — **the same 0-to-1 unit coincidence as the
other eight, on a rectangle nothing was supposed to be using.**

## §2 — ►► THE SETTINGS. THIS IS THE BUILD AND THE CONFIGURATION TO START FROM.

**PLAY / LOOK AT ANYTHING:**
```
GETV_VSYNC=1  GETV_FPS=120  GETV_SIMHZ=query  GETV_SIMDIV=1
GETV_WIDESCREEN=0  GETV_ROOMSCISSOR=0  GETV_WINDOW=2560x1369
```
- `VSYNC=1` + `FPS=<panel Hz>` — **`285`. The panel is 120 Hz. This is the whole smoothness fix.**
- `SIMHZ=query` — the world at retail speed at 120 (`276`, `277`). Banner: `0.500000 fields per frame`.
- `SIMDIV=1` — pins `268`'s divider off. Gate: `props interpolated 0` + zero `simulation held to`.
- `WIDESCREEN=0` — pillarbox, and the largest hole contributor off (`278` §2). Gate: `ours: x=367.333`.
- `ROOMSCISSOR=0` — most of the remaining holes off (`284`). Gate: the `roomscissor]` banner.

**MEASURING THE GPU ONLY:** `GETV_VSYNC=0` **and** `GETV_FPS=0` (`273` §8). **Nothing else.**

**THREE DEFAULTS ARE NOW OWED A DECISION, ALL THE SAME SHAPE AS `268` §7:** `configWidescreen`
(`port_support.c:203`, still `1`), `GETV_ROOMSCISSOR` (still on = retail), and the vsync line in
every run sheet in `repo\docs`. **All three are currently wrong-by-default for a human.**

## §3 — WHAT THE NEXT SESSION SHOULD DO, IN ORDER
1. **Finish the switch** — the four sites in §1, same knob, same banner. Then re-run arm A. **Only
   then is "what survives a world with no per-room rectangle" a real question.**
2. **The wear pass, which has never been run**: Facility (glass), Dam, Cradle, the front-end.
   Looking for transparency in the wrong order — `sub_GAME_7F0B3C8C`'s buckets are what the
   rectangle used to contain. **Streets at four viewpoints is not a test of that.**
3. **The cost, both ways** — `GETV_GPUTIME=1` with `GETV_FPS=0`, and `WORK_OVER=` (`271`).
   Budget: `[MEASURED]` CPU `0.890` + GPU `0.832` ms against `11.111` (`272`, `273`).
4. **Then the defaults in §2** — the session lead's call, each with a banner.
5. **Smoothness underneath the vsync fix (`285` §1)** — the frame-interval DISTRIBUTION instrument,
   and whether the TURN has a timestep at all. **`285` ranks above this whole item.**

## §4 — STILL OWED, AND HONESTLY LISTED
- The same-spot two-resolution amount arm (`279` §5) — **still no number.**
- **A black-wall dump. Run C did not get one** (`280` §7.3, measured: the walls were within 5%).
- Whether retail shows any of this (`283` §5.2). The clipping is decomp-matching code.
- **All of `277` §9, untouched through four sessions now**: the two hoist sites driven, the two
  intro-skip audio falsifiers, the `MoveBond` executions-per-second counter. Plus `278` §6's
  `[INFERRED]` hoist-1 read.
- `SETUP.md` §3.5 owes `229` §9's two CSV traps.

## §5 — WHAT THIS SESSION CHANGED IN THE SOURCE
**`vendor/ge-decomp/src/game/bg.c` ONLY.** Three knobs, all `#ifdef GE_PORT_NATIVE`, all default
off, all announcing themselves: **`GETV_PORTALBOX`** (print-only probe), **`GETV_ROOMSCISSOR`**
(falsifier), **`GETV_PORTALOPEN`** (`281` patch 2, now known dead — **kept, not deleted**, rule 2).
`gfx_pc.c` untouched, so **no regen is needed**.
New tool: `repo\tools\dlgrab_scissor_census.py` — the scissor-span list per dump. Its
uncovered-area verdict is a **self-declared null** (`280` §6.2); the span list is the useful half.
