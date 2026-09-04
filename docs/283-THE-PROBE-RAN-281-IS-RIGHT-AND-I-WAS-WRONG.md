# 283 — THE PROBE RAN. `281`'s SYMPTOM IS CONFIRMED, `282` §2.2 IS RETRACTED, AND THE DEFECT IS ONE LINE MEETING ANOTHER.

**2026-08-31. BUILT AND RUN.** `goldeneye.exe` **2026-08-30 20:43:56, 18,020,737 bytes** — the
`GETV_PORTALBOX` build. Arm: `run_282_P1_portalbox.log`, Streets 29, `GETV_WIDESCREEN=0`,
`GETV_SIMDIV=1`, 60 Hz, `2560x1369`. **All four gates met**: probe `ARMED` banner present,
`window: 2560x1369`, `ours: x=367.333 y=171.125` (widescreen off), `game_exit requested`.
No `BUDGET SPENT`. Dumps by announcement: **`dlgrab_2299`, `dlgrab_2440`** — byte-identical, one
viewpoint, standing still.

> ## THE ONE-LINE RESULT
> **`[MEASURED]` A straddling portal does NOT reliably fail open. Its near-plane crossing points
> are projected through `bondview.c:734`'s `z == 0.0f -> inv_z = -1e20` guard, so they land at
> ~1e25 and expand only the sides their SIGN points at. `4,955` of `5,373` straddles (`92.2%`)
> left at least ONE side finite — a side then bounded solely by the verts that were in front.
> That is a too-tight edge, and in the F9 frame the hole starts exactly on one, to `0.07` game
> units.**
> **`281` PREDICTED THE SYMPTOM AND WAS RIGHT. `282` §2.2 PREDICTED THE OPPOSITE AND IS WRONG.**

---

## §1 — THE GATE: THE PROBE IS ON THE PATH THAT MADE THE RECTS

`[MEASURED]`. The F9 frames' own `SETSCISSOR` sub-rects, in game units, are **`(1,30)-(91,210)`**
and **`(233,30)-(319,210)`**. **158 frames of the standing-still period print stored boxes that
reproduce BOTH exactly** after the emitter's truncate/ceil and the view clamp. The void condition
in `RUN-SHEET-282` §4 did not fire. Representative frame, `f=1994`, three rooms:

| | box the room may paint in | from |
|---|---|---|
| room 16 (current) | `(1,30)-(319,210)` — the whole view | — |
| room 17 | **`(1,30)-(90.71,210)`** | **`port=46`** |
| room 9 | **`(233.05,30)-(319,210)`** | **`port=51`** |

## §2 — ►►►► THE RETRACTION, AND IT IS MINE ◄◄◄◄

`282` §2.2 argued: a min/max over a superset can only EXPAND an AABB, the crossings are inserted,
therefore a straddle cannot produce a tight box and must fail open. **The first half is still true.
The conclusion does not follow and is measured FALSE.**

**`port=46`, the portal that produced room 17's box, `[MEASURED]` verbatim:**

```
f=1994 port=46 npts=4 gen=12 drop=4 cross=4 kept=8
   raw=(-2045102172841887488016384.00, -12678085184508128275726336.00)-(90.71, 2586950348079568443670528.00)   HUGE
```

**Three sides at ~1e25. The fourth, `max.x`, is `90.71`.** An expansion only expands the side its
SIGN points at: a crossing that projects to a huge NEGATIVE x pushes `min.x` out and leaves `max.x`
untouched. So the huge values are useless as bounds AND harmless on three sides, while the fourth
side stays whatever the surviving front verts gave it — **too tight, exactly as `281` said, and for
a reason `281` did not name.**

**IT IS NOT A ONE-OFF. `[MEASURED]` over the whole run:**

| | count |
|---|---|
| portal boxes printed | 37,620 |
| straddles (`HUGE`) | **5,373** |
| straddles with **at least one side still finite** | **4,955 = 92.2%** |
| which side stayed finite | `max.x` 2,564 · `min.x` 2,337 · `max.y` 1,406 · `min.y` 14 |
| `drop=0 cross=0` (no straddle at all) | 13,052 |
| `FAILOPEN` branch (inverted box -> `screensize`) | **0 — it never fires**, because 1e25 keeps `max > min` |

**`282` §2.2 is RETRACTED in full**, and with it the `[INFERRED]` claim that `281`'s patch 2 is a
no-op: **the existing fail-open never runs at all.**

## §3 — AND THE HOLE STARTS ON THAT EDGE. TWO SLABS, TWO DIFFERENT STORIES, ONE FRAME.

`[MEASURED]` from `dlgrab_2299.bmp` against the same frame's rects:

| slab | measured edge | rect edge | `d` | the portal behind it |
|---|---|---|---|---|
| left | left edge at window x `886`, **207 rows** = game `90.93` | room 17's `lrx` `91` (`90.71`) | **0.07 game units** | **`port=46`: `drop=4 cross=4`, HUGE, `max.x` finite** |
| right | right edge at window x `1695`, **121 rows** = game `232.75` | room 9's `ulx` `233` (`233.05`) | **0.25 game units** | **`port=51`: `drop=0 cross=0`** — every vert in front |

**►► THE TWO HOLES IN ONE FRAME HAVE DIFFERENT CAUSES.**
- **The LEFT slab is `281`'s fault, confirmed.** The box's right edge came from a straddle that
  lost its bound.
- **The RIGHT slab is NOT.** `port=51` never straddled; its box is a clean measurement of that
  doorway and `281`'s own stop rule applies. **The question there is why nothing paints the strip
  between the white building's right edge (game `216.3`) and `233` at all** — three rooms are in
  the draw list and none of them covers it. **That is the missing-neighbour reading and it is now
  the second open thread**, `278` §3's `drawn=2` census being the standing hint.

## §4 — WHAT `281` GOT RIGHT AND WHAT IT STILL HAS WRONG

- **RIGHT, and it outranks my analysis: the symptom, the site, and "this fires when you stand close
  to a doorway."** `drop=4` on the faulting portal is that, measured.
- **STILL WRONG: the cause.** `281` says the projector *"drops verts behind the camera instead of
  clipping them."* **It clips them** — `sub_GAME_7F0B5528:2311-2325` appends the crossings, and
  `cross=4` on that very portal proves the loop ran. `282` §2.1 stands.
- **So `281`'s patch 1 ("add Sutherland-Hodgman") would be rewriting a clip that already exists.**
  The defect is not a missing clip. **It is `arg2[len].z = 0.0f;` meeting
  `transform3Dto2DWithZScaling`'s `if (in->z == 0.0f) inv_z = -1e20f;` (`bondview.c:734`).** The
  clipped point is placed exactly ON the plane the projector refuses to divide by.
- **`281`'s patch 2 is dead for a new reason**: the fail-open it proposes to add already exists in
  the source and **fired zero times in 37,620 boxes**.

## §5 — THE CANDIDATE FIX, NAMED AND NOT WRITTEN

**Give the crossing point a z the projector can divide by**, so it lands at its true screen
position and bounds the box properly — `arg2[len].z = -epsilon` rather than `0.0f`, or handle the
`z == 0` case in the projector by using the near plane. **One line either way.**
**NOT WRITTEN, AND THREE THINGS MUST BE SETTLED FIRST:**
1. **This is decomp-MATCHING code.** `00-STATE` §7: *"the decomp `lib/ge` is MATCHING — 'did we
   change the feel' is a DIFF."* Any change must sit behind `#ifdef GE_PORT_NATIVE` or the match is
   gone.
2. **►► IT IS THEREFORE RETAIL BEHAVIOUR, NOT PORT-INTRODUCED — AND THAT IS NOT ESTABLISHED EITHER
   WAY.** The same floats, the same guard, the same 1e25 on an N64. **Whether retail shows these
   holes has NOT been measured and must not be assumed in either direction.** `[OPEN]`.
3. It fixes at most the LEFT slab. §3's right slab has a different cause and would survive it, so
   *"the holes are gone"* is not an admissible gate for it. **The gate is: `port=46`'s `raw.max.x`
   stops being `90.71` and becomes a bound that contains the doorway.**

## §6 — WHAT IS OWED, UPDATED
- **`00-STATE` §3 item 2, §4 (this retraction) and the currency line.** Owed now.
- The missing-neighbour thread (§3's right slab).
- Whether retail shows this (§5.2).
- **Still untouched from `277` §9**: the two hoist sites driven, the two intro-skip audio
  falsifiers, the `MoveBond` counter. And `278` §6's hoist-1 read.
- The same-spot two-resolution amount arm (`279` §5) and a black-wall dump (`279` §6) — run C did
  not get one (`280` §7.3).
