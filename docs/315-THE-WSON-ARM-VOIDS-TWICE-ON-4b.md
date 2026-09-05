# `315` — **THE `wsON` ARM VOIDS TWICE ON `4b`. THE CONFOUND IS THE INSTRUMENT'S, AND THIS IS AN ESCALATION, NOT A DIAGNOSIS**

**2026-09-05.** OFFLINE ASSISTANT. **NOTHING BUILT, STAGED, BRANCHED, MERGED OR TAGGED BY THE
ASSISTANT. THREE ARMS RUN BY THE OWNER ON THE MAIN PC; THE SCORER RUN BY THE OWNER; EVERYTHING
ELSE READ BACK OFF THE BRIDGE RATHER THAN TAKEN ON A PASTE.** Binary UNCHANGED — both preambles
verified `goldeneye.exe` against `EXPECTED-EXE-303.txt` and neither threw.
**NOTHING IS PATCHED IN THE PRODUCT AND NOTHING IS PATCHED IN THE INSTRUMENT. THE COUNT OF WRONG
FILED FIXES STAYS AT FIVE.**

---

## §0 — WHAT THIS SESSION ESTABLISHED, IN ONE TABLE

| | |
|---|---|
| **1** | **`RUN-SHEET-314` §5's A/B RAN. `GATE 4c` PASSED ON BOTH ARMS.** `[MEASURED]` `wsON` `tanR-tanL=1.079632`, `wsOFF` `1.368534`, **`backend_eye_w=912.667` on BOTH**. The knob took. `313` §0.1's arithmetic held — the half is `912.667` and not `1280` |
| **2** | **►►►► `GATE 4b` FAILED ON EVERY `wsON` GRAB AND PASSED ON EVERY `wsOFF` GRAB.** `[MEASURED]` `wsON` play area `x=[0..2560) width=2560`, the tool reads the half as **`1280`**; `wsOFF` `x=[367..2192) width=1825`, half **`912`**. **`4d`: with `4b` FAILED the `wsON` arm MEANS NOTHING AT ALL. It is VOID and it is NOT a falsification of `4a`** |
| **3** | **THE `wsOFF` CONTROL LANDED.** `[MEASURED]` five admissible grabs, ratios `0.572 / 0.657 / 0.697 / 0.699 / 0.724`, **median `0.697`** against the standing control `0.704` — reproduced in the same sitting on the same wall |
| **4** | **►►►►►►►► THE RE-RUN VOIDS IDENTICALLY. THAT IS TWO VOIDS AND THE RULE IS ESCALATE.** `[MEASURED, BRIDGE]` `run_315_wsONb.log`, seven fresh grabs, `tanw=1.079632`, `backend_eye_w=912.667` — and **all seven pictures return `play area x=[0..2560) width=2560`, half `1280`**, read with the committed tool's OWN `play_area()`. `RUN-SHEET-315` §0: **re-run once; if it voids twice, ESCALATE TO THE OWNER — do not diagnose** |
| **5** | **SO `[PREDICTION] 4a` IS NOT ESTABLISHED AND IS NOT FALSIFIED.** `4a` needs BOTH arms. It has `0.697` from `wsOFF` and **nothing at all** from `wsON`. **`314` §4's `a = 1.000000` at `WS=1` is still `[ARITHMETIC]` and the instrument has not been able to check it** |
| **6** | **AND THAT REACHES `314` §6a.2.** Its proposal — run `V3`'s exit gate at `GETV_WIDESCREEN=1`, where the confound is ABSENT — **rests on an arithmetic claim this instrument cannot currently measure in that configuration.** The proposal is not refuted; it is UNVERIFIED, and §6a.2 said so itself: *"if the `wsON` arm does not read `1.000`, §4's arithmetic is wrong and this section collapses with it."* **It did not read anything** |
| **7** | **`314` §2.2 IS CONFIRMED ON NEW DATA, AND IT WAS NOT ASKED TO BE.** `[MEASURED]` on the `wsOFF` arm the grab with a **`28.3%`** depth drift is the one furthest from the median (`0.572`), while the frame gaps — `42, 40, 21, 9, 46` — **order nothing**. The drift term carries the error. `RUN-SHEET-314` §2's original frame-gap refusal would still have been wrong |
| **8** | **ONE NEW INSTRUMENT HOLE, `H24`, FILED AND NOT FIXED.** §5 |
| **9** | **`V3` WAS NOT READ AND `RUN-SHEET-315` §2.1 WAS NOT RUN.** Reading the exit gate off a void arm is `295` §10.1's black-frame PASS in a different costume. **Lane 1 DID NOT CLOSE** |

---

## §1 — `GATE 4c`, AND IT IS THE HALF OF THE SHEET THAT WORKED

`[MEASURED]` from each arm's own log, not from a typed number:

| | `wsON` | `wsOFF` | `wsONb` (the re-run) |
|---|---|---|---|
| `tanR-tanL` | `1.079632` | `1.368534` | `1.079632` |
| expected by the sheet | `1.079632` | `1.368534` | `1.079632` |
| `backend_eye_w` (`ours: w=`) | `912.667` | `912.667` | `912.667` |
| left eye `x` | `0` | `367.333` | `0` |
| right eye `x` | `912.667` | `1280` | `912.667` |
| grabs / preds / dls | `5 / 64 / 5` | `5 / 42 / 5` | `7 / - / 7` |

**NO `GATE 4c FAILED` BANNER ON ANY ARM.** `GETV_WIDESCREEN=1` moves the frustum exactly as
`313` §5 measured and `314` §3 explained, and the eye rectangle is `912.667` px wide on every
arm — **the same on both sides of the knob, which is what `RUN-SHEET-314` §5 predicted and is why
this was called the cleanest A/B this project has had.**

---

## §2 — ►►►►►►►► **`GATE 4b`, AND IT FAILED THE WAY IT WAS PRE-REGISTERED TO FAIL** ◄◄◄◄◄◄◄◄

```
wsON    play area x=[0..2560)     width=2560   eye half 1280 px   seam at x=1280
wsOFF   play area x=[367..2192)   width=1825   eye half  912 px   seam at x=1279
wsONb   play area x=[0..2560)     width=2560   eye half 1280 px   (all seven grabs)
```

**THE MECHANISM WAS ALREADY WRITTEN DOWN BEFORE THE ARM RAN AND IT IS NOT NEW.** `gfx_pc.c:4193`
stretches the 2D layer to the window edge when `configWidescreen` is on; `stereo_disparity.py:58`'s
`play_area()` finds the play area from the NON-BLACK columns. **With the 2D layer covering the
window there are no black columns, so there is nothing for it to find, and it returns the whole
framebuffer.** The tool then halves `2560` and measures against a seam at `x=1280` — while the
backend's own `VIEWPORT n64` line, in the same log, prints `w=912.667`.

**►►►► AND THE WRECKAGE IS VISIBLE IN THE NUMBERS, WHICH IS WHY NONE OF THEM IS A MEASUREMENT.**
`[MEASURED]` on the void `wsON` arm the search bounds clip asymmetrically to `[-500 .. +319]`, the
five `dx` come back `-433, -500, -454, -434, -422` — **one of them pegged exactly at the `-500`
search floor** — and frame `1892` returned `VERDICT: CANNOT ANSWER -- LOW CONFIDENCE` outright.
**`RUN-SHEET-314` §5.3 step 2: if every `wsON` grab fails `4b`, SHAPE A is still UNMEASURED and
`4a` is not falsified.** That is the disposal and it was pre-registered.

---

## §3 — THE `wsOFF` CONTROL, AND IT REPRODUCED

`[MEASURED]` `4b` and `4c` both clean on all five, so these count. `ratio = dx / predicted`:

| frame | `dx` | predicted px | ratio | depth drift | frame gap |
|---:|---:|---:|---:|---:|---:|
| `2502` | `-116` | `-202.71` | `0.572` | **`28.3%`**, worth `57.38` px | `42` |
| `2680` | `-64` | `-97.44` | `0.657` | `8.1%` | `40` |
| `2901` | `-52` | `-74.63` | `0.697` | `2.0%` | `21` |
| `3129` | `-46` | `-65.83` | `0.699` | `0.9%` | `9` |
| `3346` | `-41` | `-56.61` | `0.724` | `3.6%` | `46` |

**MEDIAN `0.697`, AGAINST THE STANDING CONTROL `0.704`.** The under-read is where `309`-`313` left
it, measured again at the mandated geometry in this sitting.

**►►►► AND THE COLUMN ORDERING IS A FREE CONFIRMATION OF `314` §2.2 ON DATA THAT DID NOT EXIST
WHEN IT WAS WRITTEN.** The single grab with a large depth drift is the single grab furthest from
the median; **the frame gaps order nothing** (`9` and `46` bracket the two closest to the median).
`RUN-SHEET-314` §2's original stated fix — a refusal on frame gap — would have thrown away good
grabs here too. **The retraction stands and is now twice-measured.**

---

## §4 — THE RE-RUN, AND THE RULE IT TRIGGERS

`RUN-SHEET-315` §0's stop condition, quoted: **"If `4b` or `4c` fails, the arm is VOID: re-run it
once, and if it voids twice, ESCALATE TO THE OWNER — do not diagnose."**

`[MEASURED, BRIDGE]` `run_315_wsONb.log`, a fresh arm at the same geometry with a wall test the
owner walked deliberately: **seven grabs, seven `dlgrab` frames matching the log exactly, no stale
files in the directory, `tanw=1.079632`, `backend_eye_w=912.667`.** The arm itself is clean.

**AND ALL SEVEN PICTURES READ `play area x=[0..2560) width=2560`, half `1280`.** That was read on
the bridge by calling **the committed tool's own `play_area()`**, unmodified, on the seven BMPs —
`[MEASURED, BRIDGE]`, and **it is a read of the pictures, NOT a scorer verdict: no `dx` is claimed
from it and none should be quoted from this document.**

**TWO VOIDS. THE RULE FIRES.** Lane 1 does not close and lane 1 does not continue.

---

## §5 — `H24`, FILED AND NOT FIXED

**`H24` — THE INSTRUMENT CANNOT FIND THE EYE SEAM ON ANY ARM WHERE THE 2D LAYER REACHES THE
WINDOW EDGE.** `play_area()` infers the seam from black pillarbox columns, and `gfx_pc.c:4193`
removes them whenever `configWidescreen` is on. **Every `WS=1` arm this project ever runs will void
`4b` for this reason, at any window.** `[MEASURED]` three arms, twelve pictures, twelve identical
readings.

**AND THIS IS WHERE THIS DOCUMENT STOPS, DELIBERATELY.**

- **No fix is filed here and none is proposed here.** `301` §0: five wrong filed fixes, four of
  them convincing, and `314` §6a.1's warning is the sharper one — **a wrong INSTRUMENT patch is
  worse than a wrong product patch, because it does not look like a fix, it looks like a
  measurement.**
- **The `wsON` grabs are KEPT.** `grabs_314_wsON` (five) and `grabs_315_wsONb` (seven), plus
  `grabs_314_wsON_STALE_0202` which is quarantined and belongs to an overwritten log. **They are
  the pictures the owner ranks IN THE HEADSET** (`4e`, `314` §6a.2) and that use does not depend on
  `4b` at all.
- **`H19` is unchanged: ANSWERED, NOT PATCHED, documented, deferred to Group X by name.**

---

## §6 — THE PROCESS DEFECT OF THIS SESSION, AND IT IS THE OWNER'S TOOLING NOT THEIR JUDGEMENT

**`H5`'s GUARD WAS DEFEATED BY BEING EDITED RATHER THAN OBEYED.** The preamble throws when
`run_314_$w.log` exists; the name inside the CHECK was changed to `run_314-315_$w.log` while the
arm blocks still redirected to `run_314_$w.log`. **The guard then passed on a name nothing writes,
and the arms overwrote a `02:02` `wsON` log which is gone.**

`[MEASURED, BRIDGE]` the damage was bounded and was caught before scoring: that run's **eight**
orphan grabs (`4432, 4511, 4520, 4531, 4542, 4720, 4732, 4746`) were still sitting in
`grabs_314_wsON` with no log to be scored against. **None of their frame numbers collided with the
five real ones, so the tool's `279` §2 check would have refused each rather than mis-scoring it**
— but that was luck, not design. They were quarantined to `grabs_314_wsON_STALE_0202` before the
scorer ran.

**THE RULE: THE NAME IN THE GUARD AND THE NAME IN THE REDIRECT ARE ONE STRING. RENAME THE LOG, NOT
THE CHECK.** §6 of `00-STATE`.

---

## §7 — WHAT NEEDS A PERSON

- **►►►► THE ESCALATION ITSELF, AND IT IS THE OWNER'S.** `H24` blinds `4b` on every `WS=1` arm.
  **`HIGH`, and `00-STATE` §7c says it must not be started at the end of a session.** It is a
  fresh session's question, and it now sits beside `X1` rather than in front of it.
- **THE TWO COMMITS**, each tree's own path list, `git commit -F`. **`314`'s two are still owed and
  `315`'s docs join the docs one.** Leave the 57-file username scrub alone.
- **`X1`** — which runtime surface, and where the session lives. **`HIGH`.** Unchanged by this
  session: `314` §6a's reframing does not depend on `4a`, and four of five Perfect Dark seams are
  still in the tree.
- **`--max-depth-drift`'s default** — still deferred to the next tool commit, and §3 above is a
  second measurement in favour of `0.15` over `0.05`.
- **`U-27`** — unchanged, not owed, **and it must not be guessed from a grep.**

**`169` NEXT ID = `U-28`. NEXT INSTRUMENT HOLE = `H25`.**
