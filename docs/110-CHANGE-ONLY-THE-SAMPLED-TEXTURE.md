# 110 — O85. CHANGE ONLY THE SAMPLED TEXTURE.

**2026-08-24. `106` §6 move 1, finally built. `56`'s method, unapplied through
four attempts. Backups: `.bak110` on all four files.**

---

## §1 — THE OMISSION THIS CLOSES

**`103`, `104` and `105` each changed TWO things at once** — which texture the
present thread samples, AND how many distinct passes it consumes — **then
reasoned about the result as though only one had moved.** `106` §2 named the
pattern and was blunt about it: each explanation was built on the previous
one's framing rather than re-derived from the numbers.

**`106` §6 asked for the obvious missing experiment and nobody built it.** This
is it.

---

## §2 — WHAT IT DOES

**`GE_VR_EYE_SAMPLE_TEST=1`, or `.\vr.ps1 -EyeSampleTest`.**

The present thread samples **pass 0 — a REAL frame, never an interpolated one —
alternating between the two eye target sets on consecutive presents.**

| Held constant | Changed |
|---|---|
| Passes published | **The sampled texture pointer, every present** |
| Passes rendered | |
| Frame content is real, never interpolated | |
| No extra GPU work of any kind | |

**Alternation is on the PRESENT ORDINAL, not on the present loop's `i`.** Using
`i` would not alternate at all on a `displayFrames == 1` workload — and
`displayFrames` alternates 1/2 at 60 into 90. **That is the exact assumption
that broke `105`** (`107` §2), and repeating it here would have produced a test
that quietly does nothing on half the frames.

### §2.1 — IT IMPLIES `-EyeInterp`, AND THE SWITCH SETS BOTH

**Without `GE_VR_EYE_INTERP` the allocation does not happen, and the workload
writes set 0's TARGETS into both parity slots — so the two "sets" are the same
two textures and alternating between them changes nothing.**

**That would be a knob announcing a state it is not in — `32`'s shape, and `39`
O24's — so `-EyeSampleTest` sets both rather than letting anyone set half of
it.** `GE_VR_EYE_SAMPLE_TEST` is also added to `vr.ps1`'s clear list: the env is
cached in a `static int` read once per process, so a leftover from a previous
run is indistinguishable from a change that did not work, which is the hazard
that list's own comment names.

---

## §3 — THE GATES

```powershell
.\build.ps1
.\vr.ps1 -UnitsPerMetre 50 -SeamNoRot -HandPosZ 1 -EyeSampleTest
```

| Gate | |
|---|---|
| **G-110-1** | **`sampleAlt=` on the `render passes:` line must be NON-ZERO.** Zero means the test is not running and **nothing measured under it means anything** — `104`'s G-104-1 lesson, and `00`'s instrument warning |
| **G-110-2** | **fps and `submits`.** **STALLS (~16 fps, submits ~13) -> the cost IS in changing the sampled texture**, and passes and lifetimes were never relevant. **DOES NOT STALL (60 fps, submits 90) -> the pass path is implicated** and `107` §2's fixed stride is where to look |
| **G-110-3** | `-EyeSampleTest` absent -> `sampleAlt=0` and the build behaves exactly as `107` left it |

**`ds_option` MUST BE PINNED — `108` §4.1.** Every `103`-`106` number was taken
at `1` and the file on disk says `2`. Restore `graphics.json.bak-preDS2` first,
and re-check after any in-game menu visit.

### §3.1 — WHICH OUTCOME IS EXPECTED, WRITTEN BEFORE THE RUN

**`107` §1 read the whole sampling path and found NO mechanism by which a
changed texture costs anything** — the resolve is a no-op, the descriptor set
does not rebuild on a texture change, and `setSRV` plus the heap copy run
unconditionally every present either way.

> **SO THE PREDICTION IS: IT DOES NOT STALL.** A stall here would contradict
> `107` §1 and would be the most interesting result in the sequence, because it
> would mean the cost is somewhere the read did not reach.

**`48` rule 2: what would this build have to do differently for the gate to
fail?** It would have to stall while consuming exactly as many distinct passes
as the 60 fps build does. Nothing in the tree predicts that. **That is what
makes it a gate and not a formality.**

---

## §4 — WHAT IT CANNOT DO

**It cannot fix anything.** It is a diagnostic and it is knob-gated; an unset
build is unchanged.

**And it does not test interpolated CONTENT.** Pass 0 of each set is a real
frame, deliberately — the point is to isolate the pointer change from
everything else. **If it does not stall, the next question is which of the two
remaining differences matters: interpolated content, or the number of distinct
passes.** Those are separable in turn, and neither is separated yet.
