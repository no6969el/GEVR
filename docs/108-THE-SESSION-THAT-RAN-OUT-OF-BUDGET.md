# 108 — THE SESSION THAT RAN OUT OF BUDGET, RECOVERED

**2026-08-24. Reconstructed from the owner's transcript of the 2026-08-23/24
session, which ended on a session limit before anything was written up.**

> **THIS IS A RECOVERED RECORD, NOT A FRESH ONE.** It is written from the
> conversation, not from `gevr.log`, and it is labelled so because `48`'s whole
> case is that an undocumented result is one the next session re-derives or
> contradicts. **Two results here were about to be lost, and one of them
> falsifies a claim written in `107` earlier today.**

---

## §1 — THE GUARD WALK WAS RUN. `106` §7.2 IS CLOSED.

**`106` §7.2 asked for one launch, knob OFF, watching a guard walk, to decide
whether the character misplacement was ours or predated `103`.**

**The owner ran it. *"The characters are ok."***

> ## **THE DEFAULT BUILD IS CLEAN. THE MISPLACEMENT IS OURS AND IT ONLY FIRES WITH `GE_VR_EYE_INTERP=1`.**

**It is in the eye target MODIFIER change** — `104` and `105` changed
`0x1000 + eyeTargetIndex`, and `105` made it alternate between two sets on
consecutive workloads. `103` never touched it. **`106` §7.2's second branch (in
the VR eye path generally, predating `103`) is eliminated.**

**And `107` §2 is very likely its cause rather than a separate fault**: the
alternating modifier was indexing into sets that overlapped, so a "set 1" write
landed on set 0's targets. **That is a wrong-content bug and a stall in one
mechanism, and G-107-2 tests both at once.**

---

## §2 — TWO WEARER REPORTS, AND THEY ARE NOT THE SAME FAULT

**The owner, unprompted, which `95` records is when his reports are worth
most:**

> *"I have been noticing even when they are good that you see random glitches
> from their head or a flicker of something but it's very minimal but it
> exists. When you move your head back and forth the characters in the distance
> double the same way as the edges of the mountain and other things do when I
> move my head. Do you think it's the upscaling/downscaling being done by the
> launching app?"*

**Two separate things, and separating them is the finding.**

### §2.1 — THE DOUBLING IS THE DUPLICATE FRAME. NOT THE UPSCALER.

**Three things rule the upscaler out, and none of them is an adjective:**

1. **It is MONOCULAR** — D1, already answered: it happens with one eye closed.
2. **It is MOTION-DEPENDENT** — appears on head movement, settles when still.
3. **The mechanism is MEASURED** — `reused=30/s`. One submission in three is a
   repeated image.

**An upscaler does not produce a second copy of an edge; it produces softness or
crawl, and it does not switch on and off with your head.**

**And there is a detail in his own description that confirms it:** mountain
edges *and* distant characters double **the same way**. A head ROTATION moves
everything across the retina by the same angle regardless of distance, so a
duplicated frame doubles near and far identically. **A resolution artefact would
not behave that uniformly.** `92`, `93`, and the `reused` counter.

### §2.2 — THE HEAD GLITCHES AND FLICKER ARE MISSING ANTIALIASING

**Here his instinct about resolution was right, and it has two documented causes
in our own tree.**

> **THERE IS NO ANTIALIASING AT ALL UNDER VR.** MSAA is forced off (`43` — RT64
> ignores render target overrides under MSAA and stereo silently breaks), and
> `ds_option` was `1`, so no supersampling either. **A 320x240-era game with
> hard-edged low-poly geometry is drawn at 5838x4498 with ZERO edge filtering.**
> Thin high-frequency detail — a head at distance, a railing, a rifle barrel —
> lands on sub-pixel coverage and pops in and out as you move.

**And their own interpolation code predicts the other half.** The comment in
`interpolation.c` says a short-lived draw that exists for one or two frames has
no previous-frame partner, so RT64 drops it on the in-between frames —
*"reads as flicker rather than ghosting."* **Written about muzzle flashes, but
anything transient on a character qualifies.**

---

## §3 — THE TEST WAS RUN AND IT PASSED

**`ds_option` set to `2` in `%LOCALAPPDATA%\GoldenRecomp\graphics.json`. Backup
at `graphics.json.bak-preDS2`. `msaa_option` left at `"None"` — not negotiable,
`43`.** That renders at 2x and downsamples, which is real supersampled AA and
**the only antialiasing available to us with MSAA off.**

**The owner launched it: *"It just smooths out the distance, I am sure my gpu
can handle all this, it's a 5090."***

> ## **SUPERSAMPLING REMOVES THE DISTANT SHIMMER, SO THE SHIMMER WAS ALIASING. §2.2 IS CONFIRMED AND WE HAVE THE LEVER.**

**The doubling did not change, and should not have** — different fault, §2.1.

### §3.1 — WHAT WAS NOT READ, AND IT MATTERS

**THE FPS LINE.** The desktop bridge dropped before the log could be read, so
**the GPU cost of `ds_option 2` is UNMEASURED.** It was judged by feel.

**That is not a complaint about the owner; it is the open half of the result.**
`49`'s **O22 is still unexplained** — 8x FEWER pixels once ran 4x SLOWER — and
resolution changes in this build have surprised us before. **Read the fps line
before trusting `ds_option 2`, and try `4`: if 4 is somehow slower than 2, that
is O22 reproducing on demand, which nobody has ever pinned down.**

---

## §4 — AND IT FALSIFIES A CLAIM IN `107`, WRITTEN EARLIER TODAY

**`107` §1 says, in the table of eliminated suspects:**

> *"**The downsample** — NO-OP, CONFIRMED. `ds_option` is `1`, so
> `downsampleMultiplier == 1` and the branch is not taken."*

**THAT IS NOW FALSE, AND IT WAS FALSE WHEN IT WAS WRITTEN** — `ds_option` had
already been changed to `2` the night before, and `107` read the value out of
`00-START-HERE`'s environment table instead of off the disk. **`48` item E
exists for exactly this: check the environment before trusting a cross-session
comparison.**

**Traced through the tree to be sure rather than assumed:** `ds_option` ->
`userConfig.downsampleMultiplier` (`rt64_user_configuration.h:91`) ->
`workloadConfig.downsampleMultiplier` (`rt64_workload_queue.cpp:218`) ->
`chosenRt->downsampleMultiplier` (`:539`). **The one thing that could cancel it
is the reference-height reduction at `:476-480`, which halves the multiplier
when `nativeColorHeight >= 360`. GoldenEye's is 240. It does not fire.**

> ## **SO AT `ds_option 2`, `prepareEyeFromTarget` TAKES THE `downsampleTarget` BRANCH: A COMPUTE DISPATCH PER EYE PER PRESENT, ON THE EXACT PATH G-107-2 MEASURES.**

**`107` §1 is corrected at source. Rule 10.** The other eliminations in that
table stand — the resolve genuinely is a no-op, the descriptor set genuinely
does not rebuild on a texture change, and `setSRV` genuinely runs
unconditionally. **Only the downsample line was wrong, and it was wrong because
it trusted a document over the disk.**

### §4.1 — WHAT IT MEANS FOR G-107-2

**G-107-2 IS NOW CONFOUNDED UNLESS `ds_option` IS PINNED.** The `103`-`106`
numbers were all taken at `ds_option 1`. **Comparing a `107` run at `2` against
them measures two changes at once.**

> **RUN G-107-2 AT `ds_option 1` FIRST, against `106` §1's table, which is the
> only like-for-like comparison available. THEN re-run at `2` if you want the
> supersampled number.** Restore from `graphics.json.bak-preDS2`.

**And re-check the file after ANY in-game menu visit** — the menu rewrites
`graphics.json`, which is `43`'s standing hazard and would silently put
`ds_option` back to 1 mid-experiment.

---

## §5 — WHAT THIS OPENS

| # | |
|---|---|
| **O89** | **READ THE FPS LINE AT `ds_option 2`, AND TRY `4`.** The AA lever is confirmed by feel and unmeasured in cost. **O22 lives in this exact territory** |
| **O90** | **ANTIALIASING IS A NAMED, SEPARATE FAULT NOW** — not judder, not stereo. Cause known (`43` forces MSAA off, so supersampling is the only route), lever known, cost unknown |
| **O91** | **`interpolation.c`'s transient-draw flicker** is the other half of §2.2 and is `23`'s family. **Not fixed by supersampling** |
| **`106` §7.2** | **CLOSED — §1** |
| **O88** | **CLOSED by this document** |

---

## §6 — THE PROCESS NOTE, WHICH IS THE POINT OF WRITING THIS AT ALL

**Two results nearly died with a session limit: a confirmed diagnosis with a
working lever (§3), and a falsification of a claim written the next morning
(§4).** `48` says write the findings doc and treat it as the most valuable
output. **This session did the work and skipped the write-up, and the next
session then wrote a document that contradicted it.**

**The cheap fix is not more discipline. It is writing the finding at the moment
it lands rather than at the end** — which is also what `100` concluded about
instrument output, for the same reason.
