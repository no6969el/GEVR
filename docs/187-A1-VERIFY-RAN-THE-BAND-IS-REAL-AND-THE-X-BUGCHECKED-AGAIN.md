# 187 — `A1-VERIFY` RAN. THE BAND IS REAL. `D1` PASSED. AND THE X BUGCHECKED AGAIN.

**Written 2026-08-25 after a session that ended in a machine crash before it could
write up. Tiers per `182`. Every commit is the owner's.**
**The evidence is `gevr-keep-A1VERIFY-crash.log` (preserved from `gevr.log`).**

---

## §0 — WHERE THINGS ACTUALLY STAND

| | | |
|---|---|---|
| **`D1`** the log label | **DONE, RUN, AND PASSED** | §2 |
| **`A1` VERIFY** | **RUN. `184` §4 CONFIRMED** | §1 |
| **`A1` THE FIX** the cone clamp | **STILL NOT WRITTEN — IT IS NOW THE NEXT BUILD** | §4 |
| **`B3`/`B4`** the X close | **RE-OPENED. `181`'s `[ASSUMED]` clean close did not hold** | §3 |
| **The tree** | `186`'s two `.c` edits are UNCOMMITTED in `GoldenEye64Recomp`; `186`+`187`+`MAIN-STATION-TASKS.md` uncommitted in `GoldenEyeVR` | §5 |

---

## §1 — ►►►► `A1-VERIFY`: THE BAND IS ENTERED. BUILD `A1`. ◄◄◄◄

**`[MEASURED]`, last of 318 cumulative lines, `gevr-keep-A1VERIFY-crash.log`:**

```
[gevr] A1-VERIFY: aimed=8548 refused=936 | INSIDE=5702 BAND=2846 SAT=1424 noFrus=0
       | maxNx=15376 maxNy=20575 | lastNdc=(-8027,11239) lastFwd=(567,-240,787) x1000
```

**READ IN `186` §2's OWN ORDER, WHICH WAS WRITTEN BEFORE THE RUN:**

- **`noFrus=0`.** The `167` frustum path was never refused. **The run is
  evidence** — `186` §3's one way this instrument could have lied did not happen,
  and every `nx`/`ny` below is in frustum-edge units.
- **`BAND=2846` against `aimed=8548` — THIRTY-THREE PER CENT.** `186` §2's
  criterion was *"`BAND` large against `aimed` -> `184` §4 CONFIRMED... build
  it."* **It is a third of every aimed frame. `184` §4 IS CONFIRMED AND IS NO
  LONGER `[INFERRED]`.**
- **`INSIDE=5702`** — the three counts sum to `aimed` exactly (`5702+2846=8548`),
  so nothing is being double-counted or dropped.
- **`SAT=1424`, half the band.** The `162` +-2 NDC clamp fires on **one aimed
  frame in six**, and every one of those lands on the same pixel. That is the
  collapsing mechanism, measured directly rather than inferred from `184`'s
  290-of-1,313 histogram.
- **`maxNx=15.4`, `maxNy=20.6`** (x1000 -> tangent units). **Not grazing the
  edge — twenty times outside it.** `162`'s *"twenty times off screen"* family,
  literally. `lastNdc=(-8.0, 11.2)` is one live sample of it.

> **AND THE `[ASSUMED]` FROM `186` §4 IS STILL OPEN, HONESTLY:** this was a
> deliberate wide sweep with dwells, as instructed. **It proves the band is
> reachable and enormous when entered; it does not by itself prove ordinary play
> enters it at 33%.** It does not need to — the cure is correct either way — but
> **do not quote 33% as a figure for normal play.**

---

## §2 — `D1` PASSED, AND IT PASSED THE WAY IT WAS SUPPOSED TO

**`[MEASURED]`, 318 `6dof-game: BULLET ... | SIGHT ...` lines: 99 DIFFER, 219 are
EQUAL.** `src=TRUEAIM` throughout.

**The equal ones are on-screen and the differing ones are clamped — exactly the
predicted signature** (`186` §4 / `MAIN-STATION-TASKS.md`: *"equal ON-screen is
correct, not a fault"*):

```
BULLET aim=(480,21)px   src=TRUEAIM | SIGHT crosshair_angle=(316,21)px  CLAMPED
BULLET aim=(159,-100)px src=TRUEAIM | SIGHT crosshair_angle=(159,13)px  CLAMPED
BULLET aim=(160,120)px  src=TRUEAIM | SIGHT crosshair_angle=(160,120)px CLAMPED
```

**SO U-16 IS PUBLISHING THE UNCLAMPED VALUE AND `184` §3a IS SETTLED FOR GOOD:**
the bullet does take the unclamped aim, the old `BULLET` label was the liar, and
**the instrument can now tell the two apart in one line.** `172`'s clamp split is
confirmed live, not just read.

**AND `A2` IS CONFIRMED IN THE SAME LINES, INDEPENDENTLY:** rest is
`(160,120)` against a `320x220` centre of `(160,110)` — **ten pixels low, again.**
`185` `A2` needs no new run, only the read.

---

## §3 — ►► `B3`/`B4` ARE RE-OPENED. THE X BUGCHECKED THE MACHINE. ◄◄

**`[REPORTED]` (owner, this session): the PC crashed on closing the game with the
X — the bug `181` reported closed.**
**`[MEASURED]`: `gevr-keep-A1VERIFY-crash.log` ends mid-frame on a `[trace]
submitting gfx task` line, and `grep shutdown` returns NOTHING.** No
`shutdown: complete, clean`, no partial teardown line — **the same signature `42`,
`151` and `157` recorded, and the opposite of `181`'s one good close.**

**`181` IS NOT REFUTED, IT IS INSUFFICIENT — AND IT SAID SO ITSELF:** its own
tier line was *"`[ASSUMED]`: one clean close. B3 failed five times but never on
every close — WANT THREE OR FOUR MORE X CLOSES."* **The second close was the
failure.** `begin_shutdown()` performing the teardown is necessary and is not the
whole path.

> **UNTIL THIS IS RE-DIAGNOSED, GO BACK TO `taskkill /F /IM GoldenRecomp.exe`.**
> **`MAIN-STATION-TASKS.md` and `185` `D2` both currently say CLOSE WITH THE X.
> THAT INSTRUCTION IS SUSPENDED** — it costs a reboot per wear test, which is the
> exact tax `148` 6D-00 called the highest-value thing in the project.
> **DO NOT spend deliberate crashes on it. Every wear test now yields one X-close
> data point for free — but only after its log has been COPIED ASIDE**, which is
> the lesson of this session: the run was excellent and nearly lost.

**THE OPEN QUESTION, STATED SO IT IS NOT RE-ASKED VAGUELY:** `181` closed the
path where `SDL_QUIT` is queued and the window is already being destroyed. **Was
this close the same path?** No `shutdown:` line at all means `begin_shutdown()`
either never ran or died inside its own teardown — **and those two are
distinguishable with one entry-side print**, which is cheaper than any reasoning
about it. That print is the next `D`-group task.

---

## §4 — WHAT IS OWED, IN ORDER

1. **`A1` + `A2` AS ONE BUILD.** `185` `A1`: clamp the DIRECTION into the frustum
   cone (per-axis tangent limits from the live headset tangents `167` already
   establishes) **before** the divide; knob `-NoAimCone`. `185` `A2` is a READ,
   not a launch, and rides the same build. **Gate `G-A1`: the crosshair moves
   continuously to the edge and STOPS — the two axes saturating INDEPENDENTLY,
   not to a corner. Gate `G-A2`: rest reads `(160,110)`.**
2. **A ONE-LINE ENTRY PRINT IN `begin_shutdown()`** (§3). No behaviour change.
   It can ride the same build — it is an instrument, not a behaviour.
3. **THEN `A3`**, then `C1`-`C3`, per `185`. Unchanged.
4. **`A1-VERIFY` STAYS IN.** After `A1` it becomes the regression check: **`BAND`
   should collapse toward zero and `SAT` with it.** Deleting it would throw away
   the only before-figure this project has for the fault.

---

## §5 — THE TREE, DESCRIBED. NOTHING STAGED.

**`GoldenEye64Recomp` (clean at `81280c2`, worktree modified):**
`patches/ge_vr_aim.c`, `patches/ge_vr_bindtest.c` — `186`'s `D1` label and the
`A1-VERIFY` instrument. **Verified `[READ]`: `SIGHT crosshair_angle` and
`A1-VERIFY` appear in the worktree and NOT in `HEAD`.**
New log kept: `gevr-keep-A1VERIFY-crash.log`.

**`GoldenEyeVR` (clean at `c1cead4`, worktree modified):**
`docs/MAIN-STATION-TASKS.md` (modified), `docs/186-...md` (untracked),
`docs/187-...md` (this file, untracked), plus `HANDOVER.md` and
`00-START-HERE.md` updated by this write-up.

**THE COMMIT IS THE OWNER'S**, `commit-session.ps1`, on Windows, both repos.
