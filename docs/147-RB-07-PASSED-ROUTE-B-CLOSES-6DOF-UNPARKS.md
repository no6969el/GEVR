# 147 — RB-07 PASSED, WORN. ROUTE B CLOSES. THE COMFORT GATE LIFTS AND 6DoF UNPARKS.

---

# >>>> HOW TO LAUNCH THE BUILD THAT WORKS. THE ONLY COMMAND. <<<<

**Added `151`, after a session spent unsure which sim was running. THIS IS THE
BUILD THE OWNER CALLED *"SO MUCH better... totally playable and enjoyable."***

```powershell
cd C:\Users\pdbar\Desktop\GoldenEye64Recomp
.\build.ps1
.\vr.ps1 -UnitsPerMetre 50 -SeamNoRot -HandPosZ 1 -ViRate 90
```

**IN `pwsh`, NOT WINDOWS POWERSHELL 5.1.** `build.ps1:159` uses `??`, which is a
PARSE ERROR in 5.1 and reads as a broken build script rather than a wrong shell.

**IT MUST BE REBUILT EVERY TIME** — owner, 2026-08-24.

### THE THREE THAT ARE NOT OPTIONAL

1. **HEADSET ON, THEN LAUNCH.** O60. **Three confounded launches already**, and
   it remains the first thing to suspect when a run looks wrong.
2. **`-ViRate 90` IS EXPLICIT AND STAYS EXPLICIT.** `vr.ps1` defaults to 60.
   Making 90 the default was tried and reverted (`151` §1): **a run whose pacing
   is implicit is a run that can be judged without knowing which sim it was.**
3. **CLOSE WITH `taskkill /F /IM GoldenRecomp.exe`. NEVER THE X.**

> ## **B4 WAS RUN ON PURPOSE, 2026-08-24, AND THE X STILL BUGCHECKS THE MACHINE — WITH `149`'s FIX COMPILED IN.**
>
> **AND THE LOG SAYS WHY: THERE IS NO `shutdown:` LINE AT ALL.** The log stops
> mid-gameplay, at `90.0 fps | LATE 0/91`. **`149` fixed `xr_shutdown`, and on
> the X path `xr_shutdown` NEVER RUNS** — `42` recorded this exact signature:
> the bugcheck lands *"BEFORE the render deinit hook logged its first line, so
> every safeguard that lived in that hook was unreachable, which is why the log
> for that run simply stops."*
>
> **SO `149` IS NOT REFUTED, IT IS INSUFFICIENT. The fix has to move EARLIER —
> to `begin_shutdown()` at the SDL_QUIT moment, `42`'s territory — and `59`
> complicates it: with a game running, SDL_QUIT does NOT exit the process.**

### WHAT A GOOD RUN LOOKS LIKE IN THE LOG

```
[gevr] 90.0 fps | render passes: eye0=90 eye1=90 distinctTargets=90 | interpUsed=0
[gevr-xr] stage MAX ms: ... | LATE 0/91 (0%)
[gevr] clock: ... -> per1000ms=60
```

**`interpUsed=0` and `per1000ms=60` are the pair that says Route B is live and
the clock is honest.** `dupSrc` is BLIND here and means nothing — `113` §2.

**AND `LATE 13/13` IS NOT A FAULT.** It is the low-frame-count window before
gameplay and **appears in the good 19:00 run eight times.** A run that ends
early will show nothing else, which is not the same as a regression.

---

**2026-08-24, 19:00. The headset, at a true 90 Hz sim.**

> ## ***"I am so happy to say it's SO MUCH better. It's totally playable and enjoyable."***

**The judder line opened at `92` and ran to here — fifty-five documents.**

---

## §1 — THE NUMBERS, AND THEY AGREE WITH THE WEARER

| | Reading |
|---|---|
| **fps** | **mean 82.7, max 90.0** (min 10.5 is the level load) |
| **`interpUsed`** | **0** |
| **`eye0` / `eye1` / `distinctTargets`** | **90 / 90 / 90** |
| **`LATE`** | **0/91 — ZERO PER CENT** |
| **`per1000ms`** | **60** (169 samples; 28 at 63) |

**G-146-1 PASSES.** **G-146-3 PASSES, and `146` §3's warning was wrong in the
good direction:** it predicted the 50% extra real rendering might blow the
11.11 ms budget at 26 Mpx an eye, because `109` measured the old 60 fps build at
**`LATE 16/91 (18%)`**. **It now reads `0/91`. The pacing is better at ninety
real frames than it was at sixty plus an interpolator.**

**G-146-4 PASSES: the clock keeps real time with XR on**, not only at `-NoXr`.

### AND THE DUPLICATE FRAME, CAREFULLY

**`dupSrc` reads 90/90 — AND THAT NUMBER IS VOID, exactly as `113` §2
established:** with `-EyeInterp` unset the present thread samples the same two
`RenderTarget` objects forever, so the pointer never changes and the counter is
blind. **Do not read it as ninety duplicates. `112` corrected this once already
and it must not be re-misread.**

> **THE MEANINGFUL PAIR IS `interpUsed=0` WITH `distinctTargets=90`.** There is
> no interpolator running and ninety distinct eye targets are presented per
> second. **The duplicate frame is not fixed — IT NO LONGER EXISTS**, because
> nothing is being manufactured. `93`'s 1-in-3 and the 30/90 that survived
> fifteen documents were both artefacts of interpolating 60 into 90.

---

## §2 — THE OWNER'S DECISION, AND IT CLOSES ROUTE B

> ***"Now I can see how updating the world from sixty hertz could improve the
> experience, but this is definitely much better. So it's good enough that if
> doing the world in ninety hertz needs to be put on the back burner so that we
> can implement the proper 6DoF and all that, I'd say let's do it."***

**That is the right call and it is precise about what is being deferred.**

**What Route B delivered:** the *view* and the *frames* at 90 Hz — ninety real,
distinct, correctly-timed frames with no interpolation and no duplicates.

**What it did not deliver:** the *world animation* still advances in 60 discrete
steps a second. That is RB-03's job, **and `145` showed it is not a small fix** —
Bond's walk is a per-frame convergence loop with no timestep, so a finer delta
makes him 1.5x faster rather than smoother, and correcting it means putting a
timestep inside `MoveBond`'s 1307 lines.

> ### **SO RB-03 IS DEFERRED AS A KNOWN FUTURE IMPROVEMENT, NOT AS A DEFECT. `-FloatDelta` stays off by default and the shipping build is correct.**

---

## §3 — AND THIS LIFTS THE GATE THAT HAS BLOCKED EVERYTHING SINCE `96`

**`96`, quoting the owner:** *"It's pointless building all this extra stuff if
you're just going to get sick when you're playing it."* **`86`'s nine 6DoF slices
have been PARKED ever since.**

> ## **COMFORT WAS THE BLOCKER. THE OWNER HAS NOW WORN IT AND CALLED IT PLAYABLE AND ENJOYABLE. THE GATE IS LIFTED AND 6DoF UNPARKS.**

**The work that was parked is not stale — it was researched while it waited:**

- **`86`** — the nine-slice 6DoF plan.
- **`102`** — **Perfect Dark's actual constants**, read at `67ea20c`, MIT,
  attribution owed. `86` copied their design and not their values; `102` has the
  numbers, so **G2 becomes a check and G3 a table to verify** rather than sweeps.
- **`102` §1's correction:** **PD clamps the drawn CROSSHAIR and leaves the
  BULLET AIM UNCLAMPED** (`bondgun.c:8419-8422` vs `:8468-8472`) — *"exactly the
  break-the-lock the owner asked for, and prior art ships it."*
- **`101`** — **aim mode is A1's entry point, found by the wearer.** Holding aim
  calls a nine-line wrapper around the exact function `86` chose, already
  fetching both per-weapon dampings. **The ARM is already unclamped; only the
  BULLET is locked.** **A1-R3 is CLOSED by the owner:** losing look-ahead in aim
  mode is not a problem — *"you're in the shooting position now."*

**A1 IS THE NEXT SLICE, and it has a design (`101` §6), prior-art values
(`102`), and a closed open question.**

**STILL UNREAD, ONE IN-LEVEL LAUNCH, BATCHES WITH ANYTHING:** `muzzleExt`
(`100`) — the only one of `90`'s five falsifiers never read, because its line is
the only one touching `get_ptr_item_statistics`. **Move it to its own line, last.**

---

## §4 — THE HEAD TURN, ASKED AND ANSWERED. `124`'s TARGET IS CLOSED.

This section originally warned that *"playable and enjoyable"* did not separate
the head half from the stick half, and that it should be asked directly.
**It was asked, and the answer is unambiguous:**

> ## ***"I shook my head fast, slow, went in circles. IT DOESN'T DO IT. It's pretty damn good."***

**Fast, slow, and circular — the three motions this project has used as its
falsifiers all evening.** `95` established that a ghost which ORBITS is a
fixed-lag signature; **the circle test is the one that would have caught a
residual, and it is clean.**

> **`146` §5's PREDICTION — *"the head-turn half may not be fixed at all"* — IS
> WRONG, AND WRONG IN THE GOOD DIRECTION.** `124`'s target, restated by the owner
> and carried as the thing not to lose, **is closed.**

**AND THE WEARER MEASURED THE RESIDUAL IN THE SAME BREATH:** *"Since I'm moving
so fluidly I can notice the sixty hertz in the world on the truck, but only when
you're running at full speed and you turn and pass it by. It's not major."*

**That is RB-03, precisely located by eye:** the world animating in 60 discrete
steps while the view runs at 90. **It only becomes visible once everything else
is smooth enough to see past** — which is itself a measure of how much Route B
fixed. **Owner decision: back burner** (`148`).

**Also open and deferred by the owner:** the menu-mash crash (`137` §4), and
**B3/B4 — the bugcheck on VR session close — which `39` has had marked BLOCKING
since `75` and which every session including this one has chosen the judder over.
With the judder closed, B3 has no competition left.**
