# 209 — AUDIT OF TODAY'S DOCUMENTATION AGAINST `182`. ONE RULE WAS BROKEN TWENTY TIMES.

**2026-08-25. Requested by the owner: *"I know there's some rules that need to be
followed when it comes to the documentation and the labeling of it. Can you
double check that all that has been done on the work today?"***
**Scope: `186` through `208`, twenty-three documents.**

---

## §1 — WHAT PASSES

| rule | source | result |
|---|---|---|
| **Tiers on every load-bearing claim** | `182` §3 | **PASS.** All 23 carry tags. Counted: 47 `[MEASURED]`, 35 `[READ]`, 19 `[INFERRED]`, 60 `[REPORTED]`, 7 `[ASSUMED]` |
| **`[REPORTED]` verbatim** | `182` §3 | **PASS.** Every one is quoted, not paraphrased |
| **Inherited claims keep the ORIGINAL tier** | `182` §3 | **PASS** — e.g. `191` §1 kept `185` `A3`'s `[INFERRED]` and then retracted it rather than promoting it |
| **`169` append-only, NEXT ID moved** | `169` header | **PASS.** U-21..U-24 appended, NEXT ID now U-25 |
| **DELETE NOTHING** | `00-START-HERE` | **PASS.** Every off switch survives; `208`'s dead hook kept as a comment |
| **Sessions never commit** | `00-START-HERE` | **PASS.** Nothing staged in either repo |
| **`168` §5 grep before costing game-code work** | `168` | **PASS, and it paid twice** — it blocked `207`'s patch guard and it cleared `208`'s stage globals |
| **No RT64 / N64ModernRuntime file touched** | `48` rule 12 | **PASS.** `lib/rt64` and `lib/N64ModernRuntime` were READ only; all edits are `src/main`, `patches/`, `vr.ps1` |

---

## §2 — ►►►► WHAT FAILS: `[INFERRED]` WITHOUT ITS COUNTER-EXAMPLE SEARCH ◄◄◄◄

**`182` §3 requires, for `[INFERRED]`: *"the counter-example search, and its
result."* `182` §2 mechanism 2 spells out why: *"before asserting X causes Y,
SEARCH FOR A RUN WHERE X HELD AND Y DID NOT. State that you looked and what you
found."***

**`[MEASURED]`: the phrase "counter-example" appears in `182` itself and in `184`.
IT APPEARS IN NONE OF TODAY'S TWENTY-THREE DOCUMENTS. Nineteen `[INFERRED]` tags
were written and not one states a search.**

**THE TAG WAS APPLIED HONESTLY AND THE OBLIGATION BEHIND IT WAS NOT DISCHARGED.**
That is failure mode 3 in a new costume: **the tier communicated "this is
inference" while omitting the one thing that makes an inference checkable.**

### THE MITIGATION, AND IT IS PARTIAL

**Most of today's `[INFERRED]` claims were RESOLVED within hours rather than
built on**, which is the outcome the rule exists to force:

| claim | fate |
|---|---|
| `188` §3 — `A2`'s ten pixels are the screen origin | **`[MEASURED]` `origin=(0,10)` within one run** (`189` §2) |
| `191` §2 — the HUD sits at infinity | **`[REPORTED]` confirmed at `-HudDepth 0.2`** (`192` §1) |
| `196` §2 — the head-turn is the missing room term | **SUPERSEDED and falsified** by `200`'s measurement |
| `207` §2 — RB-02's cadence exposes the race | **`[MEASURED]`: 3 clean mash-runs at 60 against 2 crashes at 90** |

**ONE SURVIVES UNRESOLVED AND LOAD-BEARING** — `193` §3, that the second
weapon's spray comes from our fixed pistol muzzle. **Its counter-example search
is owed and is recorded as owed in §4.**

---

## §3 — THE SECOND FAILURE: `108`, AND IT WAS CAUGHT

**`108`'s rule is to mark a task before finishing.** `T2` and `T7` were both
**ANSWERED today** — `T2` passed on measured `MUZZLENODE` data, `T7` answered
from 55 logged shots — **and both `RESULT:` lines in `MAIN-STATION-TASKS.md` were
still rows of dots.** The findings lived only in `193`.

**FIXED IN THIS PASS.** Both now carry their result, their tier and their
evidence in the sheet the next session actually opens.

> **AND THE NEAR-MISS IS THE POINT: `108` EXISTS BECAUSE A SESSION ENDED WITHOUT
> WRITING UP AND THE NEXT ONE CONTRADICTED IT.** A result recorded only in a
> numbered document, while the checklist still says "not done", is that failure
> in slow motion.

---

## §4 — WHAT IS OWED FROM THIS AUDIT

1. **THE COUNTER-EXAMPLE SEARCH FOR `193` §3** — the per-weapon muzzle
   explanation of the spray. **Look for a run where a NON-pistol was carried and
   the aim was NOT off**, and say what was found. **Until then it stays
   `[INFERRED]` and `U-18` must not be costed as though it were settled.**
2. **NO RETRO-TAGGING OF `186`-`208`.** `182` §6 forbids it for the old corpus and
   the reasoning holds here: **guessing today what a document meant this morning
   is the same failure wearing a tidy-up.** The gap is recorded; the documents
   stand as written.
3. **FROM `210` ON: an `[INFERRED]` tag WITHOUT a stated search is a defect**, the
   same way an untiered claim has been since `183`.

---

## §5 — THE HONEST SUMMARY

**Twenty-three documents, tiered throughout, with four self-retractions caught by
reads before they cost a build** (`188`'s SAT gate, `191`'s `A3` premise, `195`
§3, the virtual-screen performance suspicion). **The tiering system worked.**

**And the one rule that was broken, was broken every single time it applied.**
**`182` §1's own lesson, turned on today: naming a failure mode in prose does not
prevent it. Only a rule that changes what gets WRITTEN does — and `[INFERRED]`'s
second half never made it into the writing.**
