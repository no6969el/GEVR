# 182 — THE FOURTH TIME. EVERY CLAIM NOW CARRIES ITS EVIDENCE TIER.

**2026-08-26. Written after `180` was retracted hours after being written.**
**A process document. It changes how every later document is WRITTEN.**

> # ►►►► THE CORPUS CANNOT TELL A MEASUREMENT FROM A GUESS. ◄◄◄◄
>
> **180 documents, and every conclusion in all of them is in bold.** There is no
> register for "I measured this" versus "I read this in the source" versus "this
> fits the four logs I happened to open". **They are typographically identical,
> so the next reader cannot weigh them, and neither could the last four.**

---

## §1 — THE RECORD. THIS IS NOT A ONE-OFF.

| # | the claim | how it was made | what killed it |
|---|---|---|---|
| 1 | `muzzleExt` is a barrel length | `6D-02` measured `100` flat — **the measurement was right, the INTERPRETATION was asserted** | `171` §2 read `gunfire.c:754`. It scales a SPRITE |
| 2 | `camGetWorldToScreenMtxf()` is unreachable | `160` §2 asserted it | `177` grepped `externs.h:63`. **Declared the whole time** |
| 3 | ...repeated as established | `163` §1 inherited it **without re-checking** | same read |
| 4 | Route B killed stereo by removing interpolation | `180` §2, from **four archived logs and a name that looked similar** | `147` line 46, **already read that session** |

**`171` §3 CALLED THIS OUT AT #3 AND IT HAPPENED AGAIN AT #4.** Naming a
failure mode in prose does not prevent it. **Only a rule that changes what gets
WRITTEN does.**

## §2 — THE THREE MECHANISMS, NAMED SO THEY CAN BE CHECKED FOR

**1. THE SHARED PREFIX.** `interpUsed` (frames interpolated AND USED) was fused
with `interpolationTargetKey` (populated from `interpolationEnabled`) **because
the names looked alike.** No read confirmed they moved together.
> **RULE: two identifiers are the same quantity only when a READ says so. Cite
> the file and line, or do not claim it.**

**2. THE SAMPLE OF CONVENIENCE.** Four `.log` files on disk gave a unanimous
correlation. **No search was made for a run that would BREAK it** — and one
existed, in a document opened earlier the same session.
> **RULE: before asserting X causes Y, SEARCH FOR A RUN WHERE X HELD AND Y DID
> NOT.** State that you looked and what you found. **Unanimity across a sample
> you did not choose adversarially is worth nothing.**

**3. THE BORROWED TYPOGRAPHY.** `►►►►` and bold caps carry this project's
authority. **Applied to a four-minute-old hypothesis, they manufacture
confidence that was never earned.**
> **RULE: the tier tag comes FIRST, before the emphasis. See §3.**

## §3 — ►► THE TIERS. EVERY LOAD-BEARING CLAIM CARRIES ONE. ◄◄

| tag | means | required |
|---|---|---|
| **`[MEASURED]`** | a number from a log or an instrument | **the run, and the line** |
| **`[READ]`** | from the source | **file:line.** A comment is NOT a read of the code it describes |
| **`[INFERRED]`** | reasoning over `[MEASURED]`/`[READ]` facts | **the counter-example search, and its result** |
| **`[REPORTED]`** | the wearer said it | **verbatim.** Often the best evidence here — `173`'s sign, `179` §4's clamp |
| **`[ASSUMED]`** | none of the above | **and it must say what would settle it** |

**AN `[INFERRED]` CLAIM MAY NOT BE BUILT ON UNTIL IT IS `[MEASURED]` OR
`[READ]`.** `180` §5 was costing out four engineering options on an `[INFERRED]`
premise that died the same day.

**AND A CLAIM INHERITED FROM ANOTHER DOCUMENT KEEPS THAT DOCUMENT'S TIER, NOT
THE NEW DOCUMENT'S.** That is failure #3 exactly: `163` restated `160`'s
`[ASSUMED]` as though citing it had promoted it.

## §4 — THE INSTRUMENT BEATS THE ARGUMENT, EVERY TIME

**`180` reasoned for four paragraphs about which term of `vrStereo` was false.
`VRGATE/s` PRINTS IT.** One counter per term, and any term reading 0 while
`workloads > 0` IS the cause.

> ## **IF A QUESTION CAN BE ANSWERED BY AN INSTRUMENT, BUILDING THE INSTRUMENT IS CHEAPER THAN BEING RIGHT ABOUT IT — AND IT STAYS RIGHT AFTER YOU LEAVE.**

**`119` did this for the timebase. `64`'s counters did it for the eye sources.
Both cost one launch and closed questions that had survived multiple sessions of
argument.** `91`'s rule, restated: **five reads of the same silent boolean cost
more than the one instrument that answers it.**

## §5 — AND THE WEARER IS AN INSTRUMENT

**Three times in one session the owner corrected a document from memory, and was
right every time:** that the menus had not been opened recently; that MSAA was
not it; that `-ViRate 90` ran in VR with stereo and no character stutter.

**`173` already recorded this** — the wearer named the crosshair's DIVERGENCE
before any algebra, and the direction was the whole diagnosis.

> **A `[REPORTED]` observation that CONTRADICTS a document is evidence AGAINST
> THE DOCUMENT.** It outranks `[INFERRED]` outright, and the burden is on the
> document to produce a `[MEASURED]` or `[READ]` fact — not on the wearer to
> re-observe it.

## §6 — WHAT TO DO WITH THE 180 DOCUMENTS ALREADY WRITTEN

**NOTHING. DO NOT RETAG THE CORPUS** — it would be 180 documents of guesswork
about what past sessions knew, which is this failure mode wearing a tidy-up.

**FROM `183` ONWARD, TIERS ARE MANDATORY.** And when an old claim is USED, the
reader tags it as they find it: a claim with no citation is `[ASSUMED]`, whatever
typography it arrived in.
