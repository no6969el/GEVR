# 77 — SCALE, MEASURED. The centring was the fault. The viewmodel is a separate one.

**2026-08-23, ~16:30. Six worn launches in one session, every judgement made by
the person wearing it, every eye separation confirmed in the log at the
consumption point.** This closes `16`'s open question and `71` O1.

---

## THE RUNS

| u/m | live `eyeDelta` | Centred | The world | Player vs guards | The gun |
|---|---|---|---|---|---|
| 100 | -6.392 | **no** — headset on the desk at launch | *"people look small, I'm a big head"* | **wrong, above them** | big |
| 50 | -3.196 | **no** | *"looks the same"* | wrong | big |
| 400 | -25.512 | **no** | much too small, *"I was a tall big person"* | tall | **small** |
| 25 | — | **yes, F9** | ***"everything is in perspective"*** | **same height** | big |
| 100 | — | **yes** | *"everything feels smaller"* | **same height** | big |
| 50 | — | **yes** | ***"this one feels better"*** | **same height** | big |
| 35 | — | **yes** | (bracketing; 50 preferred) | same height | big |

---

## FINDING 1 — THE "BIG HEAD" WAS THE RECENTRE, NOT THE SCALE

**The origin was captured at process start, with the headset still on the desk.**
Putting it on then placed the head roughly a metre above that origin — **and that
metre is added on top of Bond's 175-unit eye height.** The player spent every
early session looking down on guards from about half a metre too high.

**Pressing `F9` once while wearing it removed the symptom completely, at every
units/metre value tried.** The player has been eye-to-eye with the guards ever
since.

**And the decomp says that is correct:** `chr.c:1717` `chrheight = 185.0f`,
`bondview.c:1507` eye height `175.0f`. **A guard is exactly Bond's height.**
There was never anything wrong with the character geometry, and no scale value
could have fixed a viewpoint that was simply too high.

**This is O60**: the mechanism is fine, the *moment* is wrong. Recentre belongs at
level start or on demand, not at process start.

## FINDING 2 — SCALE RESPONDS, AND `71` HAD THE DIRECTION BACKWARDS

`71` read the first report as "the world is too large, sweep units/metre UP".
**Wrong on both halves.** 400 made everything smaller and the player taller —
worse, not better — so the correction is **DOWN**, and the world reads right
around **50**.

**The near-miss worth recording:** 100 vs 50 was reported as *"it looks the
same"* even though the live `eyeDelta` genuinely halved. **That nearly closed the
whole line of enquiry as a non-response.** It took a 4x step to produce a signal
the wearer could not miss.

> **The rule, and `56` already earned it once:** when a human is the instrument,
> **use a step nobody could miss.** A 2x change in a direction the tester is
> unsure of reads as noise, and "no change" from a human is not the same
> measurement as "no change" from a number.

## FINDING 3 — THE VIEWMODEL IS A SEPARATE FAULT, ESTABLISHED BY OBSERVATION

**The gun read oversized at 25, 35, 50 and 100.** It only shrank at 400, when the
entire world shrank with it.

**An object that keeps its apparent size across a 16x sweep of world scale is not
a world-scale problem.** `71` O1 proposed this split as a possibility; it is now
observed.

**`36` already measured the mechanism: the viewmodel sits at ~15-25 cm apparent
(O8).** A gun 20 cm from your face is enormous whatever the world does.

**And it is not a cosmetic complaint.** The wearer's own words:

> *"It's making this hard, because I have to close one eye to not see it — and
> then it removes depth."*

**A fault that forces the user to shut one eye destroys the thing this project
spent a day and a half fixing.** That is why `76` puts it first.

---

## WHAT GOES INTO `16`

**Provisional: ~50 units per metre**, from a wear judgement, bracketed by 35 and
100 and preferred over both.

**It is not yet `16`'s doorway measurement**, and it should not be written up as
one. What it is: the first value ever chosen by looking at the world through
working stereo from the correct eye height. **`16`'s derivation of ~100 is
therefore out by about a factor of two**, which is well outside the "maybe 10%"
that document claimed for itself.

**What would settle it properly:** stand in a doorway, at 50 and at 65, and pick.
Ten minutes, when the gun is no longer making the world hard to look at.

## THE PROTOCOL ITEM THIS SESSION EARNED

**Every VR session was ended with `taskkill /F`, not the X, and the machine
survived all four.** See `75` — the bugcheck is ours, and until O21 is fixed the
force-kill is the exit.
