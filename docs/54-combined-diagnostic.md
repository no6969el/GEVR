# 54 — the combined diagnostic. BUILT

**2026-08-23, after `51` fixed a third real defect and G1 still measured 0 px.**

**Diagnostics only. Nothing here changes how a frame is rendered** — one knob
changes what present *samples*, and it is off by default.

---

## Why this is one build instead of three

`50`, `51` and `52` each cost a build, a launch and a wear of the user's
patience, and each answered exactly one question. **"One change at a time" exists
so a regression cannot hide inside a batch** — `48` rule 5, paid for by three
`graphics.json` settings moved at once. **A read-only diagnostic cannot cause a
regression.** Batching those is not a violation of the rule; treating them as if
they were behaviour changes was a misreading of it that cost this session two
round trips.

**The gates and the docs stay.** They are what caught a mouse cursor being
reported as progress tonight.

---

## What is already eliminated, by measurement

| | Slice |
|---|---|
| Eye render targets shared | `50` — `shared=0` |
| World drawn into a shared framebuffer pair | `52` — census |
| One transform buffer for both eyes | `51` — two `dst` |
| Eye passes not serialised | Read: `execute(); wait();` per eye, `rt64_workload_queue.cpp` 852-855 |
| Matrices, frustums, `viewOffset`, clip-w, upload hashes | `49` |
| Present sampling one texture | `present source` distinct |

**Never measured: whether the two passes produce different PIXELS, and whether
the override lands on an index the draws actually use.** Both are in this build.

---

## D1 — transform-index coverage. Prints on ANY `-Flat` run

Every existing instrument reports the override as applied and the matrix as
correct. **None of them checks that the overridden transform index is one the
geometry references.** An override written to an index nothing draws with is
invisible everywhere and would produce exactly what we see.

```
[gevr] idx coverage: drawn=N overridden=N covered=N maxDrawnIndex=N
[gevr]   drawnMask=0x................ overrideMask=0x................
[gevr] idx verdict: ...
```

| Verdict | Means |
|---|---|
| `covered=0` | **The override touches no index the draws use. That is the bug**, and every matrix log in this project has been correct and irrelevant |
| `covered < drawn` | Some geometry renders with the GAME's projection — identical in both eyes. Partial stereo at best |
| `covered == drawn` | Coverage is fine. The break is downstream, and D2 locates it |

`maxDrawnIndex >= 64` prints a warning that the mask is incomplete rather than
letting a truncated number read as a finding.

## D2 — force both present halves to one eye

```powershell
.\vr.ps1 -Flat -PresentEye 0
.\vr.ps1 -Flat -PresentEye 1
```

Forces **both** halves to sample that eye's published target. Cross-run
comparison, which `51` M1 already validated as a working method.

| Result | Means | Next |
|---|---|---|
| The two runs' images **differ** | The two targets hold different pixels. The passes work; **present is collapsing them** | Instrument present's per-half selection |
| The two runs' images are **identical** | Both targets hold the same image. The passes render identical geometry | The break is upstream of present — and D1 says whether it is coverage |

**D1 and D2 together locate the break in one launch and one pair of launches, and
every combination of their answers names a different next slice.**

## What would make this build useless

If `covered == drawn` **and** the two `-PresentEye` runs are identical, then the
override reaches the right indices, the passes still render the same pixels, and
nothing in this build explains it. That outcome is not a dead end — it points
squarely at the RSP transform stage between the buffer and the vertices, which is
the only untouched link left. **Stated now, so it reads as a result rather than
a surprise.**

---

## Prediction, written before the launch

**`covered` will be less than `drawn`, or zero.**

The reasoning offered as prediction, not finding: `overrides=23 count=24` has been
in the log since `49` and has always been read as "23 of the 24 transforms were
overridden, near enough all of them". **It has never been checked against what
the geometry references.** A count of overrides is not coverage.

The last three predictions in this project were wrong. This one is written down
so it can be scored, not believed.

---

# D1 RESULT — coverage is COMPLETE. Prediction wrong

```
[gevr] idx coverage: drawn=23 overridden=23 covered=23 maxDrawnIndex=23
[gevr]   drawnMask=0x0000000000FFFFFE overrideMask=0x0000000000FFFFFE
[gevr] idx verdict: every drawn index is overridden. Coverage is not the problem.
```

**The two masks are identical** — indices 1 through 23, drawn and overridden,
exactly. `maxDrawnIndex=23`, well inside the 64-bit mask, so the numbers are
complete and not truncated.

**Coverage is eliminated.** The `overrides=23 count=24` line that has sat in the
log since `49` means what it appeared to mean after all: index 0 is the only one
untouched, and nothing draws with it.

## Prediction: WRONG. The fourth in a row

| Doc | Prediction | Outcome |
|---|---|---|
| `50` | G1 will pass at ~113 px | Wrong |
| `51` | The shared framebuffer pair will matter | Wrong |
| `52` | The world will be in the shared pair | Wrong |
| `54` | `covered` will be less than `drawn`, or zero | **Wrong** |

**Four wrong predictions, four cheap.** Each cost one launch because it was
written down as a prediction with a decision rule attached, instead of being
acted on as a finding. **That is the method working**, and it is worth more than
a run of correct guesses would have been — the three defects found along the way
are real and permanently eliminated.

**What it also says: the mental model of this pipeline is wrong somewhere
fundamental**, not off by a detail. Four targeted guesses, four misses.

## What D1 leaves

Now eliminated, all by measurement: eye targets, framebuffer pair, transform
buffer, pass serialisation, matrices, frustums, upload hashes, present textures,
**and transform-index coverage.**

And a conclusion that follows from G1 itself, without needing D2:

**G1 compares the left half (sampling eye 0's target) against the right half
(sampling eye 1's target). They are identical, and `present source` reports two
distinct textures. So the two targets hold identical pixels.** D2's cross-run
comparison would confirm this and add little — it is already implied.

**Therefore the two eye passes render identical pixels**, with correct distinct
matrices, complete override coverage, their own transform buffers, their own
targets, and full serialisation between them.

**This is the outcome `54` named in advance as "what would make this build
useless"**, and it points where that section said it would: the stage between the
transform buffer and the vertices.

## Next, and it needs no code

```powershell
.\vr.ps1 -Flat -Offset 500
```

A 1000-unit separation. If the halves are still identical at that magnitude, the
per-eye parameter differentiates **nothing** within a run, and every remaining
question about amounts, signs and scales is closed at once.
