# 32 — the 3f-4 wear session: measure before arguing

**2026-08-22, after `31`.** 3f-4 has been built for two slices and worn for
none. This plan is what to do about that, and it is **not** the ladder
`00-START-HERE` currently prints — because reading the source before running it
found one of its steps to be inert.

Nothing here needs a rebuild. The launcher change is PowerShell; the binary
already reads every variable involved.

---

## The state the session opens in

| | |
|---|---|
| `goldeneye-vr` branch | 8 commits, clean (one untracked `.gitattributes`) |
| `GoldenRecomp.exe` | built 16:54 |
| `gevr.log` | written 16:32 — **older than the exe** |

So `07` GOTCHA 4 applies to the log on disk: it predates the binary and describes
a different run. That run was `unitsPerMetre=50 pitch=-1`, someone mid-sweep,
and it never got a session — `xrGetSystem failed (-35)`, headset asleep,
`eye0=0 eye1=0` for the whole run. **Nothing has been learned since `31` and
nothing has regressed since `31`.** The ledger is exactly where it was left.

---

## The finding: `GE_VR_EYE_SIGN` is dead in the head-tracked path

`rt64_render_context.cpp:889`:

```cpp
const float sign = ((eye == 0) ? 1.0f : -1.0f) * env.eyeSign;
...
if (useHead) {
    m = ge_vr_head_transform(headView, eye, env);   // sign is never read
}
else {
    m = interop::float4x4::identity();
    m[3][0] = sign * env.offset;                    // sign is read only here
}
```

`ge_vr_head_transform` does not take `eyeSign` and does not consult it. It builds
each eye's transform from `views[eye]`'s own pose, which is the whole point of
`30`'s "each eye uses its OWN pose" decision — and that decision **removed the
quantity the sign was flipping.** Nobody deleted the knob to match.

`00-START-HERE` step 4 therefore says:

```powershell
.\vr.ps1 -Sign -1              # eye sign. Never tested. See below
```

and that line does not pass `-NoHead`. It sets `GE_VR_EYE_SIGN=-1`, prints
`eyeSign=-1` in the log, renders an identical frame, and invites the conclusion
**"the eye sign is not the problem"** — drawn from a control that is not
connected to anything.

This is the fourth instance of the shape `21` named and `26` and `27` repeated:
*check who else writes what you write*. The variant here is its mirror — **check
whether anyone still reads what you write.** A knob that has lost its consumer
is worse than a knob that never existed, because it produces a confident
negative result instead of an error.

### What replaces it

`GE_VR_EYE=1` still works, and works *in the head-tracked path*, because it acts
after the transforms are built (`:949`):

```cpp
if (env.eye == 1) {
    const RT64::VrEyeParams swap = config.eyes[0];
    config.eyes[0] = config.eyes[1];
    config.eyes[1] = swap;
}
```

It swaps the complete parameter sets — pose *and* frustum together, so the two
cannot be made to disagree, which is the failure `25` records. **This is the
real "are the eyes swapped" test in 3f-4, and it is the only one.**

Two problems with relying on it as it stands:

1. **`vr.ps1` does not expose it.** It has to be set by hand, which means it will
   be set by hand *in a different shell* than the one `vr.ps1` runs in.
2. **`vr.ps1` does not clear it.** The clean-slate loop at the top lists fifteen
   variables and `GE_VR_EYE` is not among them — in a script whose own comment
   says *"A leftover variable from a previous experiment is indistinguishable
   from a code change that did not work."* A stale `GE_VR_EYE=1` would swap the
   eyes on every run of every future session and survive every `-NoXr` baseline.

Both are fixed in this slice. `-SwapEyes` sets it, the clear loop drops it, and
the existing `host: ... eye=%u` log line already reports it.

---

## What this does to the geometry question

`00-START-HERE` says **"sign before scale"**, and the argument for it is sound:
sweeping a scale cannot fix a divergence. But it was written when the sign was a
live knob, and it is not one. The order has to be re-derived.

The replacement is better, because it starts with something that is **not a
judgement.** The `31` head log already prints:

```
[gevr] head: x=.. y=.. z=.. units (0.412 m up), eye sep 6.31 units
```

`eye sep` is `|views[1].position - views[0].position| * unitsPerMetre`. At
`-UnitsPerMetre 100` and a 63.5 mm IPD it must read **≈ 6.35**.

That single number splits the question in half before anyone judges any depth:

- **If it reads ≈ 6.3**, the separation is correct *by construction* for the
  scale it was told. There is then no sign left to be backwards on the
  displacement, and what remains is what `unitsPerMetre` ought to be — a scale
  question, and only a scale question.
- **If it reads far from 6.3**, the eye positions are not being read or converted
  correctly, and no amount of sweeping the scale will help. That is the
  plumbing, and it is diagnosable from the log alone.

So: **measure, then swap, then sweep.** Not sign, then scale.

The `eye sep` line is the kind of evidence this project keeps finding it needed
earlier — a number, printed by the program, about the thing in question, read
before anyone forms an impression through a lens.

---

## The other thing nobody wrote down: `-NoHeadTranslate` kills stereo

With `env.headTranslate` false, `ge_vr_head_transform` leaves row 3 at zero. It
does that for **both eyes**. The eye separation in 3f-4 *is* the per-eye
position, so switching translation off does not merely stop leaning — it sets
the two eyes to the same viewpoint.

`30` describes `-NoHeadTranslate` as *"rotation only - isolates orientation from
position"*, and `00-START-HERE` step 2 uses it as the world-holds-still test.
Both are still correct about rotation. Neither mentions that **depth goes with
it.** The frustums stay per-eye and asymmetric, so it is a slightly-wrong mono
rather than a clean one, and it will read as flat.

Anyone running that step and reporting "all the depth vanished" would be
reporting the build working as written. Worth knowing before, not after.

It also hands us a falsification for free, which is the reason it is in the
ladder below rather than in a footnote.

---

## The ladder

Run in order. Do not skip on the grounds that a step looks boring; the boring
steps are the ones that localise a fault before there is anything interesting to
blame it on.

```powershell
cd C:\Users\<USER>\Desktop\GoldenEye64Recomp
```

### Part 1 — regressions

| | Command | Gate |
|---|---|---|
| 1.1 | `.\vr.ps1 -NoXr` | Normal 60 fps game. Closes cleanly. **The path that must never break** |
| 1.2 | `.\vr.ps1 -NoHead -NoLiveFov` | Exactly 3f-3, the last state a person confirmed |
| 1.3 | `.\vr.ps1 -NoHead` | 3f-4a. **Must look identical to 1.2** |

1.3 is `30`'s own gate and the one it predicted would be skipped. `gevr.log`
prints the live tangents once; the left eye must read
`-1.3760 1.0358 1.0176 -1.0176`. **If the numbers match and the picture changes,
the plumbing is wrong — and it is wrong before any rotation exists to blame.**

### Part 2 — the measurement, before any judgement

| | Command | Gate |
|---|---|---|
| 2.1 | `.\vr.ps1` | Read `eye sep` from `gevr.log`. **Record the number before saying anything about how it looks** |

**Gate A: `eye sep` reads 6.0–6.7 units.**

What would the build have to do differently to fail this? Misread
`xrLocateViews`' per-eye positions, or apply `unitsPerMetre` somewhere the two
eyes do not share. Both are host bugs, both are invisible to the eye, and both
make every later step meaningless.

Also confirm from the same line: crouch and `y` goes clearly negative; jump and
it spikes by roughly 40. **A `y` that never moves means the pose is not reaching
the render at all**, which is the specific failure that makes the world look
rigidly bolted to your head.

### Part 3 — the world holding still

| | Command | Gate |
|---|---|---|
| 3.1 | `.\vr.ps1 -NoHeadTranslate` | Rotation only. **Turn your head: the world stays put.** Expect depth to be gone — see above |
| 3.2 | `.\vr.ps1` | Everything. World stays put, *and* leaning gives parallax |

**Gate B: 3.1 has no depth.** Independent of anything else, and it is a
falsification, not a feature: if 3.1 *does* have depth, separation is arriving
from somewhere other than the head transform, and `GE_VR_TEST_OFFSET` leaking
back in is the first suspect.

If the world swims, one axis at a time — `-YawSign -1`, then `-PitchSign -1`,
then `-RollSign -1`, **separately**, because a wrong pitch and a wrong roll look
alike when both are wrong at once.

### Part 4 — the doubling

Only now, and only on a world that stays put.

| | Command | Gate |
|---|---|---|
| 4.1 | `.\vr.ps1 -ForceEye 0` | **Depth MUST collapse.** One eye's image to both |
| 4.2 | `.\vr.ps1 -SwapEyes` | Does the doubling get better or worse? |
| 4.3 | `.\vr.ps1 -UnitsPerMetre 50` | World reads twice as large, separation halves |
| 4.4 | `.\vr.ps1 -UnitsPerMetre 200` | World reads half as large, separation doubles |

**Gate C: 4.1 collapses depth.** With Gate B, that is two independent routes to
mono — one through the head transform, one through the swapchain copy. Both
passing pins the separation to exactly one place. Either failing names which.

**Gate D, on 4.2: swapping either fixes the doubling or makes it plainly worse.**
It cannot do nothing. If `-SwapEyes` changes nothing perceptible, the two eyes
are not actually carrying different images, and Gate C is the check that
contradicts it — the pair is only informative together.

For 4.3 and 4.4, judge by **a doorway**, not by the gun. Whichever
`-UnitsPerMetre` makes a doorway feel like a doorway is the measurement `16`
asked for, and `16` wrote its own falsification: *"If it looks like three metres
or three centimetres, the derivation is wrong."* Record the number.

### Part 5 — the shutdown that has never run

**Before any long session, and only after a live session has existed.** Close the
window; confirm all four, in order:

```
[gevr-xr] shutdown: session ended
[gevr-xr] shutdown: gpu idle
[gevr-xr] shutdown: xr session destroyed
[gevr-xr] shutdown: complete, clean
```

The first two **have never executed** — every close since `29` went through the
no-session path because the headset was asleep, including the run currently on
disk. Anything missing names the step that failed. The failure this guards
against previously took the **whole machine** down, not just the game.

---

## What this plan expects to be wrong about

Written before the session, so it can be scored afterwards.

1. **`eye sep` reads ≈ 6.3 and Gate A passes.** The code path is short and the
   number is straightforward. If so, the eye-sign hypothesis that has been open
   since `25` is closed **without ever having been testable in this build**, and
   the "too far apart" report was always a scale report.
2. **The doubling survives every scale.** The gun rides the game camera, so it
   sits at a fixed small depth and takes the full eye displacement regardless of
   what the world does. If the world reads right at some `-UnitsPerMetre` and the
   gun still doubles, it is the viewmodel's own depth and its own slice — which
   is what `00-START-HERE` already suspects.
3. **`-NoHeadTranslate` will be reported as "broken"** rather than as flat, the
   first time it is run, because "no depth" and "tracking is dead" feel similar
   through a headset. The `eye sep` line is what tells them apart.

Prediction 1 is the one worth being wrong about. If `eye sep` comes back wrong,
this session found a host bug instead of a scale, and that is the better outcome.

---

## Changed in this slice

- `vr.ps1`: `-SwapEyes` added; `GE_VR_EYE` added to the clean-slate clear list.
- `00-START-HERE.md`: step 4 corrected — `-Sign -1` removed as a live test, the
  measure-then-swap-then-sweep order put in its place.

No source change, no rebuild.
