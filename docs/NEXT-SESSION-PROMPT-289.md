# NEXT SESSION PROMPT — `289`

**EFFORT LEVEL: HIGH.** Source changes in two separate areas, one build, and arms on both.
Not a read-only session and not a one-knob session.

---

## PASTE THIS

Read `repo\docs\00-STATE.md` and `repo\docs\288-THE-JITTER-STATISTIC-ANSWERS-AND-THE-ROOM-TEST-IS-THE-CANDIDATE.md`, then write `RUN-SHEET-289.md` and execute it. Same rules as always. See the "Operation not permitted" warning in §6 — reads from the bridge are not free; `git log`, `git show` and `git diff <path>` are safe, `git status` and `git add` are NOT.

THERE IS A GOOD BINARY: `2026-08-31 17:09:32`, `18,035,038` bytes, ten strings. `288` ran all six of its arms on it and nothing is owed against it. **DO NOT REBUILD UNTIL THE NEW INSTRUMENTS ARE WRITTEN** — `289` gets ONE binary like `288` did.

**THE RANKED WORK IS THE VANISHING PROPS, AND `288` NARROWED IT TO ONE TEST AND ONE COUNTING BUG.** `getROOMID_isRendered(roomnum)` at `propobj.c:14087` is the standing candidate. **IT IS NOT ESTABLISHED AND MUST NOT BE TREATED AS ESTABLISHED.** `dist` is dead by measurement (0 in both runs). The box is eliminated (ARM 7, and `box=0` in 8b with the symptom still reproducing). The five view planes are measured and not incriminating — and left/right dominance is NOT evidence, because props sit on a ground plane and any level would produce it.

**THE FIRST JOB IS TO PUT `room` ON THE SAME DENOMINATOR AS EVERYTHING ELSE, BECAUSE RIGHT NOW IT CANNOT BE COMPARED AT ALL.** `propobj.c:14081` is a `while` loop over the prop's room list and `:14085` increments `room` **once per unrendered ENTRY**, then continues; every other counter is reached at most once per call, after the `break`. So `room=1,134,409` is ENTRIES TRAVERSED, not props rejected, and "29x bigger than `box`" is not a reading the report can support. **ADD A PER-PROP COUNTER — a prop whose ENTIRE room list is unrendered, counted ONCE — and print it beside the existing one, not instead of it (rule `2`).** Also fix the report line so the two denominators are not printed as one accounting. **The plane counters multi-count as well (`:14130` sets every rejecting bit); say so on the line or split props from plane-hits.**

**THE SECOND JOB IS THE ARM THAT TESTS THE ROOM CANDIDATE, AND IT NEEDS A KNOB THAT DOES NOT EXIST.** Neither `GETV_ROOMSCISSOR` nor `GETV_PROPCULLBOX` touches `getROOMID_isRendered`. **Write the falsifier the same way `287` wrote `GETV_PROPCULLBOX`: opt-in, inert when unset, a banner that says it took, and it must never ship on.** Write what it prints if pointed at the wrong thing BEFORE the run (rule `15`, `P5`). **Do not propose a fix. Name the site and measure it.** If props still vanish with the room test neutralised, that is a real result and the next arm goes elsewhere — do not re-run it hoping (`§8b`'s outcome #2, which is exactly how ARM 7 ended).

**THE SECOND RANKED ITEM IS SMOOTHNESS, AND `288` LEFT IT WITH ONE CANDIDATE.** J1 vs J2 came back equal — settled `jdp` 8.29% vs 7.70%, overlapping ranges, `vsync=0` marginally LOWER — so **`vsync` is cleared at the presented-frame resolution and the carrier is the SIM: `GETV_SIMHZ`.** `285` S1's "super smooth" ran WITH it; most of this project ran WITHOUT it. **That comparison has never been run as an arm.** It is free — no build — and it is the whole of the original complaint.

**EVERY COMMAND BLOCK CARRIES ALL OF THESE, because a block that omits a knob silently restores its default:**
`GETV_SLOTFREE=1 GETV_VSYNC=<per arm> GETV_FPS=<per arm> GETV_SIMHZ=<per arm> GETV_SIMDIV=1 GETV_WIDESCREEN=0 GETV_ROOMSCISSOR=0 GETV_WINDOW=2560x1369`

**`GETV_FPS=panel` NOW WORKS AND IS THE RIGHT SPELLING FOR ANY LOOK-AT-IT ARM** — it queried 120 Hz from SDL and the `pace:` banner carried it, on both J arms. Use it instead of a hardcoded 120; the session lead also runs a 180 Hz desk.

**THE FIRST LINE OF ANY PACEHIST LOG IS `PANEL REPORTED BY SDL: <n> Hz` AND YOU READ IT BEFORE ANYTHING ELSE.** Every bin prediction is panel/cap and every simhz gate is 60/cap — ratios, never bare numbers.

**A JITTER THRESHOLD IS SCORED ON SETTLED WINDOWS. THE BOOT WINDOW IS REPORTED, NEVER SCORED.** `288` learned this by writing `jdp < 10%` per-window and having its own boot window read 32.8%. And **do not reuse `jdm > 20%`** — hardware falsified it at 14.5% against the harness's 40.9%. **Score arms against EACH OTHER on the matched metric, not against an absolute number carried from a synthetic stream.**

**EXPECT THE FRONT-END MENU TEXT TO BE MISALIGNED IN EVERY ARM. IT IS NOT A REGRESSION AND IT WAS NEVER FIXED.** Gate 2 is `ours: x=367.333` and the fault condition is `ge_offset_x() != 0` — **the same number**. A run that passes gate 2 has broken menu text by construction. **DO NOT "FIX" IT BY MOVING TO `1825x1369`**: that prints `ours: x=0`, which is also what `WIDESCREEN=1` prints, so gate 2 would silently stop discriminating (rule `17`). It is OPEN item 2 and it is a diagnosis, not a fix.

**`GETV_ROOMSCISSOR=0` MAKES ROOMS OVERDRAW EACH OTHER — dropping side textures and blue walls are the knob's own banner text, not an old build.** Judge the slabs, not the picture.

**DEAD, DO NOT REOPEN:** the `32000` radius (`dist=0`, MEASURED, both `288` cull arms) · the per-room rectangle as the vanishing mechanism (ARM 7 `[REPORTED]`, and `box=0` in 8b) · `vsync` as the smoothness carrier (`287` 4E and `288` J1/J2, two resolutions) · ARM 4E, ARM 5, ARM 7 · everything in §5 of `00-STATE`.

**STILL OWED, NOW EIGHT SESSIONS:** all of `277` §9 · `278` §6's INFERRED hoist-1 read · `279` §5's amount arm · `280` §7.3's black-wall dump · `274` §7's CONTAMINATED gate · **`287` ARM 6, the wear pass, STILL NEVER RUN.**

**CHECK BEFORE YOU START, because `288` found both and neither may be done:** whether the regen ran (`verify` must say `15/15`, not `DIFFERS gfx_sdl2.c`), and whether `vendor/ge-decomp` still has 468 uncommitted insertions across seven files. **If the decomp is still uncommitted, say so first — `"[getv][slot] GETV_SLOTFREE resolved to"` is absent from HEAD and it is gate 4 of every run block.**

Start by reading the two docs. Do not plan past the first instrument.

---

## WHY HIGH EFFORT

- **Two separate source areas**, both needing written-then-built instruments: the `room`
  per-prop counter and report fix in `propobj.c`, and a new opt-in knob for
  `getROOMID_isRendered` that does not exist yet.
- **One binary, ten-plus string gate**, same discipline as `288`.
- **Arms on both tracks** — the room falsifier (needs the symptom reproduced on purpose, so it
  is a hands-on run) and the `GETV_SIMHZ` on/off comparison for smoothness.
- **A regen and two commits sit around it**, in a fixed order, with a known trap on each.
- `288` was HIGH and ran six arms; `289` writes new code as well as running it.
