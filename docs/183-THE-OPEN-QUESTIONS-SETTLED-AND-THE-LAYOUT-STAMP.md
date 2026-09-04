# 183 — CLOSING THE OPEN STATEMENTS. AND `115`'s TRAP BECOMES DETECTABLE.

**2026-08-26. First document written under `182`'s tiers.**

---

## §1 — ►► SETTLED: `build.ps1` DOES REBUILD RT64. MY HYPOTHESIS IS DEAD. ◄◄

**`[READ]` `build.ps1:110`:**

```powershell
cmake --build build --config Release --parallel -- /nodeReuse:false
```

**No `--target`. That is EVERY target, `lib\rt64` included.** And
`$headerRoots` (`build.ps1:85`) already covers `lib\rt64\src`, `src`, `patches`
and `lib\N64ModernRuntime`.

> ### **SO THE MORNING BUILD OF 2026-08-26 *WAS* A FULL REBUILD OF RT64, AND STEREO WAS STILL DEAD AFTER IT.**
> **`[MEASURED]`: `HEADER CHANGED ... newest: patches\misc_funcs.h`, `BUILD OK
> in 63.6s`, and the run that followed had `eye1=0` in all 1,712 samples.**

**MY `[INFERRED]` CLAIM — that the later rebuild fixed stereo by recompiling the
RT64 library — IS THEREFORE FALSIFIED.** The earlier build already did that.
**`182` §3 said an `[INFERRED]` claim may not be built on. This is the first
time that rule was applied, and it caught its own author within the hour.**

## §2 — SO WHAT DID FIX IT? `[ASSUMED]`, AND SAID PLAINLY.

**NOT KNOWN.** What is known:

- **`[READ]`** Nothing changed this session touches the stereo path. The
  counters count, the banner prints, `begin_shutdown` runs at exit, the screen
  PSO hoist runs in the no-eye-pair branch only.
- **`[MEASURED]`** Same flags, same source for the stereo path, opposite result,
  hours apart.
- **`[MEASURED]`** `VRGATE/s` reports ALL FOUR TERMS at 91/91. **Whatever was
  false before, nothing is false now.**

**WHAT WOULD SETTLE IT:** it is now self-answering. **If stereo dies again,
`VRGATE/s` names the term in one second** — the situation that cost three
sessions cannot recur silently. **DO NOT SPEND A SESSION ON THE HISTORICAL
CAUSE.** The instrument that would have answered it now exists; that is the
whole return.

## §3 — THE LAYOUT STAMP. `115`'s TRAP, MADE VISIBLE.

**`115` is the only mechanism ever demonstrated to break stereo silently**, and
until now it was undetectable at runtime — only inferred, after the symptoms had
been chased. **`[MEASURED]`, `115`: 60 fps -> 25.7, submits 90 -> 13, characters
out of position, a frozen trace. From one stale object file. Three sessions
(`103`-`105`) went to symptoms of that shape.**

**BUILT:** `SharedQueueResources` gains `layoutStamp` **as its FIRST member**.
RT64's side writes its own `sizeof` at the gate; the host compares against its
own and prints once:

```
[gevr] layout OK: SharedQueueResources NNNN bytes on both sides (docs\183)
```

...or a banner that says STOP, delete `build\.gevr-header-stamp`, rebuild fully,
and **do not debug gameplay until it is gone.**

> **IT IS THE FIRST MEMBER ON PURPOSE. At offset 0 it is the one field whose
> location cannot itself be shifted by the disagreement it exists to detect.**

## §4 — THE REMAINING OPEN ITEMS, EACH WITH A TIER

| item | tier | what is owed |
|---|---|---|
| **B3 / B4 closed** | `[MEASURED]` one clean X close, `[ASSUMED]` in general | **3-4 more X closes.** B3 never failed on EVERY close. Free now - just stop using `taskkill` |
| **U-18 per-weapon muzzle** | `[MEASURED]` but **n=1** | Two distinct `Switches[3]` values, but the second weapon got ONE sample. **Linger on it next run** |
| **`ds_option 4`** | `[ASSUMED]` | Never run. `2` is `[MEASURED]` free (`111` §4). **If 4 is SLOWER than 2, that is `49`'s O22 on demand** and worth more than the AA |
| **The 15 fps samples** | `[MEASURED]`, unexplained | 1,406 samples at `eye0=15` in the 08-26 flat run. **May be an artefact of the no-stereo state; recheck now stereo is back** |
| **Aim tuning constants** | `[ASSUMED]` | `-HandAxisX/Z`, `-GunOffY/Z`: **were any set or confirmed after 08-24 21:00?** If so they were tuned monocular. `154`/`155` predate it and are probably safe |
| **The head-locked screen** | `[REPORTED]` | *"stayed perfectly still and stuttered... very nauseating."* Not yet built. `179` §5 |
| **U-20 the room** | owner wants it | Queued behind the screen anchoring |

## §5 — AND ONE STATEMENT OF MINE THAT WAS SIMPLY WRONG

**I wrote "90 Hz costs stereo".** The true statement was never that.
**`[MEASURED]` today: `90.0 fps`, `interpUsed=0`, stereo in 75 of 99 samples.**
**`-ViRate 90` and full stereo coexist and always did** — `147` line 46 recorded
it on 08-24 and the owner remembered it correctly against two of my documents.

**THE 90 Hz HEAD POSE AND THE 90 Hz SIM ARE DIFFERENT LEVERS AND WERE CONFLATED
UNDER ONE NUMBER.** `-FloatDelta` is the one that speeds the game up (`144`,
`145`), and it is parked.
