# 48 — the session protocol

**How to start a session, and how to leave it.** Every item names the incident
that paid for it, so you can judge whether it still applies rather than taking it
on trust.

## How to use this

**It is tiered, and the tiers are honest.** The floor is small enough to do when
you are tired at the end of a bad session. Everything above it is genuinely
optional and says what it costs.

**Skipping is fine. Skipping silently is not.** A skip with a reason is data — it
tells the next person what state things are in, and it tells this document where
it is wrong. Write `skipped X, because Y` in the findings doc and move on. No
item here is worth more than the work it protects.

**This document is a draft.** See the last section before trusting it.

---

# THE FLOOR

Three things. If you do nothing else, do these — a session that ends here is
recoverable.

### 1. Commit both repos, clean

```powershell
git -C C:\Users\<USER>\Desktop\GoldenEye64Recomp status --short
git -C C:\Users\<USER>\Desktop\GoldenEyeVR status --short
```

Both empty. Remove scratch `.bat` / `.tmp` files. **~2 minutes.**

**This is LOCAL. It has nothing to do with GitHub.** Both repos are git on this
disk with no remote, deliberately — a remote comes when there is something worth
publishing. A commit here is a restore point, and the thing it protects against
has already happened once: a file edited across a long session with no way back
to the version that worked.

**Run git on WINDOWS, not through a mounted view of the repo.** A session
driving this machine through a file-share style mount has no git identity there
and cannot unlink, so a commit attempted that way fails halfway: it writes
partial objects, leaves `index.lock` behind, and **cannot clean up after
itself** - which is how a repo ends up locked. 2026-08-23, twice in one session,
the second time self-inflicted. Use a real shell on the machine that owns the
repo.

**If a commit fails, check for a stale lock FIRST.**

```powershell
Get-ChildItem .git -Recurse -Filter *.lock
```

**2026-08-23:** `GoldenEyeVR/.git` held three zero-length locks dated
2026-08-22 23:55, with no git process running. Every commit into that repo had
been failing since — including, presumably, the one that left them. **This item
was recorded as skipped for two sessions when it was actually blocked**, which
is a different failure with a different fix, and the scoring below was wrong
about which one it was. Remove the locks only after confirming no `git.exe` is
running.

### 1b. CHECK THAT THE DOCUMENT YOU CITED EXISTS — added 2026-08-23

```powershell
ls repo\docs\*.md          # then read the numbers, out loud, looking for gaps
```

**Five numbered documents — `41`, `42`, `43`, `45`, `46` — are cited 37 times
and have never existed**, on disk or in git history. `43` alone is cited 24
times and is the MSAA rule that silently destroys stereo.

Nobody noticed because the reasoning survives in long source comments, so every
citation *reads* as though it resolves. **A citation is not a document.**
Ten seconds, and it went unspotted across two phases.

### 2. Say what is now false

Any claim in an existing doc that today disproved, corrected **where it lives**,
not only in a new document.

`00-START-HERE` once said *"MSAA must stay off — it is already off in
`graphics.json`."* True when written, later false, trusted for hours after it
stopped being true. **A document's authority outlives its accuracy.**
**~5 minutes, and it is the highest-value five minutes in this list.**

### 3. Name the single next action

One paragraph, concrete enough to start cold in ten minutes.

> *"Log `viewOffset` for both eyes and read the two matrices side by side. If eye
> 1 differs from eye 0 by anything but the sign of the x translation, that is the
> bug. Twenty minutes."*

Not *"continue investigating the stereo problem."* **~5 minutes.**

**That is the floor. Twelve minutes.** Everything below is worth doing when there
is room, and is not worth a bad mood when there is not.

---

# STARTING A SESSION

### Read (5 min)

`00-START-HERE` → `39` (the board, authoritative for what is open) → the doc the
blocking item names. The numbered docs are a record, not a manual; do not read
them in order.

### WEAR IT BEFORE YOU BELIEVE IT — added 2026-08-23, `63`

**`-Flat` is not a substitute for wearing the headset. It is a substitute for
MEASURING.** Eleven documents — `43` through `61` — were validated entirely in
`-Flat`, which never sets `GE_VR_XR`. Eye targets were restructured, transform
buffers split, MSAA forced and a controller slice built, and **not one frame of
any of it was seen through the headset.** The first wear session after that
window found a dark, stale image that no instrument in the project reports.

**The rule:** after any change to the render or present path, run the bisect
before drawing a conclusion — **`-NoXr` play a level, `-Flat` play a level, then
worn.** Three launches. It costs less than one wrong diagnosis.

**And "it reached the menu" is not "it works."** `61`'s G4 was scored a pass on a
`-NoXr` launch that only ever reached the menu; a level was never played.

### Verify the environment (3 min — the best-value minutes here)

```powershell
cd C:\Users\<USER>\Desktop\GoldenEye64Recomp
dir /T:W gevr.log build\Release\GoldenRecomp.exe
```

1. **Log older than the exe?** It describes a different binary. `07` GOTCHA 4 —
   two rounds were once spent analysing such a log.
2. **Which runtime, at what resolution?** Top of `gevr.log`. This rig moved from
   SteamVR/OpenXR 2.16.7 at 4140x3292 to **Pimax OpenXR 0.1.0, Crystal Super,
   5838x4498** between sessions, silently, invalidating cross-session
   comparisons and changing the reported FOV. `40`.
3. **Is the instrument working?** `render passes: eye0=N eye1=N distinctTargets=N`
   — all three matching. Three hypotheses were tested while the second eye was
   not being rendered; those results were **void**, not weak. `43`, `47`.

---

# DURING — four habits, not a checklist

### Measure rather than describe

*"The right eye looks skewed"* meant *"the right eye is not being rendered."*
Every correct conclusion in this project came from a number.

**The mirror method**, which is what settled it: record the headset mirror,
`ffmpeg -i rec.mp4 -vf "select='eq(n\,60)'" -vsync 0 f%02d.jpg`, split each frame
in half, cross-correlate the halves for the (dx, dy) that aligns them, and
compare against the value predicted from the live tangents.

**A mirror shows the submitted IMAGE and never the metadata:**

| Mirror | Lenses | Means |
|---|---|---|
| wrong | wrong | the images are wrong |
| **right** | **wrong** | **the images are right; the pose/FOV submitted with them is wrong** |

That distinction separated a render bug from a pose bug twice in one day. It is
also the tool most likely to be over-applied — it answers questions about
*images*, and not every problem is one.

### One change at a time

Three settings changed in `graphics.json` at once: one necessary, one caused a
regression, and separating them cost a round.

### Ask both directions of the same question

**Who else writes what you write?** `21`, `26`, `27`, `38`.
**Who else reads it — and does anyone still?** `32` found a knob whose consumer
had been deleted, which returns a confident **false negative**.

### Keep the evidence

`gevr.log` is rewritten every launch. A full crash stack trace was lost to a
relaunch. `copy gevr.log gevr-keep-<what>.log`.

---

# TRIGGERED — not every session

These fire on a condition. Running them on a schedule is how a protocol becomes
ritual and then gets ignored.

### Before designing something new: look for prior art (20-30 min)

**Trigger: you are about to design, not debug.** If there is a concrete bug in
front of you, this is procrastination and you should skip it.

This project's own `PRIOR-ART.md` (in `no6969el/goldeneye-native`) independently
found the licence structure and recommended the architecture that was eventually
built. Known relevant:

| | |
|---|---|
| `RaYRoD-TV/StarFox64-VR` | OpenXR, per-eye stereo, motion controllers, **world-space HUD**, N64-lineage PC port. Closest to us. **Licence unestablished** |
| `DR-89/fear-vr` | Native OpenXR stereo + 6DoF |
| `VR-Stereo-Hub/bioshock-trilogy-vr` | Same shape, motion controllers |
| `fgsfdsfgs/perfect_dark` | Same engine family; only decomp-native prior art |
| `rt64/rt64` | **Upstream of our renderer.** Check if it is already fixed there |

**Establish the licence before reading the source**, because it decides where the
idea may land:

| Source licence | May influence | May NOT influence |
|---|---|---|
| MIT / BSD / Apache | anywhere | — |
| **GPL** (Dolphin VR, RetroArch, Mupen64Plus) | the recomp **host**, already GPL-3.0 | **`lib/rt64/`, `repo\`** — the MIT upstreamable half |
| Proprietary / unclear | nothing | everything |

`PUBLISH-MANIFEST.md` has the full split. The test is which project's source a
change derives from, not which folder it sits in.

### Before a non-trivial change: plan, then stop (30 min)

**Trigger: the change is more than an hour of work, or touches shared code.**

Write the plan as a numbered doc and **wait for a reply.** A doc written and
executed in the same breath is a changelog. `32` was aimed at the wrong question
and `33` had to undo it.

Write the gates **before** the code, and ask of each: *what would this build have
to do differently for this to fail?* A gate a working build would also pass is
not a gate.

---

# LEAVING — beyond the floor

Time-costed, so you can take the top of the list and stop.

| | Item | Cost |
|---|---|---|
| A | **The findings doc.** What was measured and what it eliminates; what is confirmed working so nobody re-checks it; **every wrong turn and why**; which earlier results are now **void** | 30-45 min |
| B | **The board, `39`.** State, next action and doc reference per item. DONE only for things **observed** — `33` exists because two slices were called finished on a build nobody had worn | 10 min |
| C | **`00-START-HERE`.** Status ledger true; index updated; anything that would cost a day near the top | 10 min |
| D | **Both READMEs.** Status current | 10 min |
| E | **Environment.** Runtime, headset, per-eye resolution, and any settings changed outside the repo — `graphics.json` above all, since the in-game menu rewrites it | 2 min |

**A is the one to protect.** The wrong turns are the most valuable paragraphs
this project produces; they are also the first thing lost, because writing down
what you got wrong is the least appealing task at the end of a long day. `47` is
the model.

If you only have fifteen minutes past the floor, do **A**, badly, in bullet
points. A rough record of a wrong turn beats a polished record of the outcome.

---

# This document is a draft — score it and fix it

By its own standard it is not DONE: it was written, not observed. Derived from
**one** session, from the failures that happened to be noticed. Whatever went
right that day went right for reasons nobody examined, which is exactly the gap a
checklist cannot contain. It is over-fitted to a stereo image problem and
probably under-specified everywhere else. It also rests on an impression rather
than a measurement, which is the thing rule 3 warns against.

### Predictions, written before use

Score these at the next handover, then **edit this document** rather than
inheriting it.

1. **The environment checks will be the most valuable and least skipped.** Three
   commands, two day-long faults caught.
2. **Prior art will be skipped even when triggered.** If it is skipped twice with
   the trigger met, the trigger is wrong, not the person.
3. **The floor will hold and the extended list will not.** That is the intended
   behaviour, not a failure — but if even the floor is skipped, the floor is
   still too big.
4. **The mirror method will be applied to a problem that is not an image
   problem.**
5. **Something not listed here will cost a day**, and its rule will be obvious in
   hindsight. Normal for a first draft.

**Note what you skipped and why.** The skips are the signal: either the item is
wrong or the skipping is, and which one it turns out to be is what tells you what
to change.


---

# SCORED, 2026-08-23 (late session). Do not inherit this unscored again

`48` asked to be scored at the next handover and edited rather than trusted.
This is that scoring. **The session it was scored against ran seven wrong
predictions and found three real defects**, so it is a fair test.

## The five predictions

| # | Prediction | Score |
|---|---|---|
| 1 | The environment checks will be the most valuable and least skipped | **Partly wrong.** They were skipped most sessions. What actually paid was checking the *instrument* (`eye targets`, `idx coverage`, `pass targets`) — and two instruments were found lying |
| 2 | Prior art will be skipped even when triggered | **RIGHT until this session.** Run once, in `55`. Verdict: StarFox64-VR's licence is UNCLEAR so it may influence nothing, and RT64 upstream has no stereo path. Closed permanently |
| 3 | The floor will hold; the extended list will not | **WRONG, and then wrong again.** The extended list (A: the findings doc) held every time — it is the most valuable output. The FLOOR failed: item 1, "commit both repos", was not done all session. **CORRECTED 2026-08-23: it was not skipped, it was BLOCKED** — three stale git locks from 23:55 the previous night. A checklist item that cannot succeed looks exactly like one nobody bothered with, and this document assumed the second for two sessions |
| 4 | The mirror method will be applied to a problem that is not an image problem | **Tempted, correctly declined** — `53`. `-Flat` supersedes the mirror for every image question: same information, no headset, no camera shake |
| 5 | Something not listed here will cost a day, and its rule will be obvious in hindsight | **RIGHT.** See below |

## Prediction 5, resolved: the rule this document was missing

**"One change at a time" was misread as "one DIAGNOSTIC at a time", and it cost
two round trips.**

The rule exists so a regression cannot hide inside a batch. **A read-only
diagnostic cannot cause a regression.** `50`, `51` and `52` each spent a whole
build-and-launch cycle answering one question; `54` batched four and answered
more in one launch.

> ### ►► RULES 5 AND 11 ARE NO LONGER STANDING RULES — 2026-08-24, OWNER DECISION ◄◄
>
> **Rule 5 (one change at a time) and rule 11 (nothing is DONE until it has been
> OBSERVED) are now invoked BY REQUEST, not applied by default.** *"Change one
> thing on this build"* invokes 5; *"don't call that done until I've worn it"*
> invokes 11.
>
> **Their numbers are kept and NOT reused** — between them they are cited
> eighteen times across fourteen documents, and renumbering would repoint every
> citation at a different rule while still reading as though it resolved.
> **Nothing that cites "rule 5" or "rule 11" needs editing.**
>
> **Every other rule is unchanged and still standing.** `00-START-HERE`'s rules
> section carries the full note, including what each one said and what is given
> up by not applying it automatically.

### Proposed amendment to rule 5

> **One BEHAVIOUR change at a time. Diagnostics may be batched freely** — they
> cannot regress anything, and one launch that answers four questions beats four
> launches that answer one each. The moment a diagnostic changes what a frame
> renders, it is a behaviour change again.

## The rule this session earned, and it is not in this document

**Write the "what would make this instrument useless?" branch BEFORE running it.**

`52`'s census had three outcomes written down, including *"no perspective
projection anywhere - the census is looking at the wrong thing."* It fired on a
menu workload and reported exactly that. **Had it silently picked "the pair with
the most perspective projections" from a set containing none, it would have named
pair 0 — the answer that sends the project down a route we had already
eliminated.** A wrong answer in the exact shape of the expected one.

That branch cost one line to write and saved a session.

### Proposed new rule

> **Every instrument states, before it runs, what it would report if it were
> looking at the wrong thing.** An instrument with no "I cannot answer this"
> output will invent an answer, and it will look like the one you expected.

## What actually did the work this session

Ranked, honestly:

1. **`-SkipEye`** — remove a thing and see if the result changes. The only form
   of evidence that survives a wrong mental model, and after five wrong
   predictions the model was the thing most in doubt.
2. **Predictions written down with decision rules attached.** Seven were wrong
   and each cost one launch instead of a session, because the branch was decided
   before the number arrived.
3. **The difference MAP rather than the difference FRACTION.** A 0.19% change on
   the build meant to fix it was about to be reported as partial progress; the
   map showed a mouse cursor. **When a number moves, look at WHERE.**
4. **Correcting a doc at its source, including this session's own.** `57`'s
   title and first finding are wrong and say so — an impression promoted to a
   finding two hours after the author wrote the rule against it.


---

# SCORED AGAIN, 2026-08-23 — THE READS SESSION

**`48` asks to be scored at each handover and EDITED rather than inherited.
This is the second scoring. The session it scores did eleven source reads, wrote
five documents, built one slice, and never launched the game once** — so it
tests the parts of this protocol that do not involve a headset.

## What the floor did

| Item | Result |
|---|---|
| **1. Commit both repos** | **FAILED AGAIN, and again NOT by being skipped.** This session drove the machine through the Linux bridge; `git status` over the mount **timed out at 45 s**. **No stale `.lock` files existed** — checked explicitly, so the `48` lock fault did NOT repeat. **Owed to the next session as O73** |
| **1b. Check the cited document exists** | **RAN, AND PASSED — 19 citations, 19 resolved, no phantoms.** First time this item has been exercised since the five phantom documents were found. **It cost about ten seconds** |
| **2. Say what is now false** | **RAN. Five claims retracted**, each corrected at source and listed in `HANDOVER` |
| **3. Name the single next action** | **RAN.** *"Commit, build, wear S0, read `muzzleExt` and `A40` first"* |

> **Item 1 has now failed two sessions running for two DIFFERENT reasons, and
> both were environmental rather than behavioural.** The item is not wrong and
> the person is not skipping it. **What is missing is that the floor assumes the
> session can reach a Windows shell, and twice it could not.**
>
> ### PROPOSED AMENDMENT, and it is small
>
> > **Floor item 1 gains a precondition: *can this session run git on Windows at
> > all?* If not, STOP, say so in the findings doc, and hand the commit to the
> > next session as a numbered task.** A floor item that silently cannot succeed
> > is indistinguishable from one nobody bothered with — **which is exactly what
> > this document concluded LAST time, and it still shipped an item that can
> > silently fail.**

## The rule this session earned

**AN INSTRUMENT THAT COUNTS OCCURRENCES OF A NAME WILL COUNT THE PROSE ABOUT
THAT NAME.**

`87` corrected `00`'s stale *"31 patch names renamed"* to *"47 unique across 48
sites"*. **Both numbers were wrong.** The true figure is **45 across 46** — the
`grep` matched **comment sentences discussing `RECOMP_PATCH` naming**, including
one in the very document doing the counting. **An instrument that counted
itself.**

> **This is rule 4 — verify the instrument before trusting the test — applied to
> a one-line `grep`, which is precisely where nobody applies it.** The rule was
> broken *while correcting somebody else's stale number*, which is the most
> confident anyone ever is.
>
> ### PROPOSED NEW RULE
>
> > **A count is an instrument. Before believing one, ask what ELSE matches the
> > pattern — and check that the document doing the counting is not itself in
> > the corpus.**

## What this protocol got RIGHT that is worth keeping

| | |
|---|---|
| **"Plan, discuss, then execute"** | **Held completely.** `86` was a plan; three sessions of reads followed; **not one line of code was written until the reads were done and the two architectural choices were discussed and agreed.** Slice S0 then took one pass |
| **"Do the reads before, not during"** (`86` §8) | **The single highest-value item in this project's history.** Eleven reads, no launches, no bugchecks, **five retracted claims — two of which would have been built into slice A1 and discovered by a wearer** |
| **"Write the gates before the code"** | **Held, and paid immediately.** Slice S0 prints `n/a` rather than `0` for unbuilt quantities **only because gate G0-1 had already named "a frozen number" as its failure mode** |
| **Rule 6, check who else writes what you write** | **Caught a conditional-compilation fault BEFORE the build** — declarations moved into an `#if` block that the consumer sat outside of. Sixth instance of this rule, first in that costume |

## The honest negative

**Two of the five retracted claims were written and retracted by the same
sessions, hours apart** (`87`'s bullet labelling, `87`'s patch-name count).

**That is the system working — but it also says the first pass over a body of
source produces confident wrong labels, and the second pass catches them.**
**Nothing in this document currently says "read it twice".** It should, and the
cost is small: the second pass over `gunfire.c` took minutes and moved a slice
from optional to mandatory.
