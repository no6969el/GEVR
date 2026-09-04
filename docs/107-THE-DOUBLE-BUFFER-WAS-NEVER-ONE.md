# 107 — THE DOUBLE BUFFER WAS NEVER A DOUBLE BUFFER

**2026-08-24. A read session, no launches, no headset.**
**`106` §6 move 2 is DONE and its suspect is ELIMINATED. `106` §6 move 1 is
still owed. And `105`'s experiment is VOID — the set stride is derived from a
quantity that changes every workload, so the two sets overlapped.**

---

## §1 — WHAT `106` §6 MOVE 2 ASKED FOR, AND WHAT IT FOUND

> *"Read what the VIRenderer does when `params.texture` changes — descriptor set
> rebuild, layout transition, or a barrier that forces a queue sync."*

**Read in full: `rt64_vi_renderer.cpp:43-105`, `rt64_d3d12.cpp:1023`, `:1150`,
`:1187`, `:2035`, `:2047`, and `rt64_render_target.cpp:410`, `:471`, `:475`.**

| Suspect | Verdict |
|---|---|
| **The resolve** | **NO-OP, CONFIRMED.** `resolveTarget` returns immediately unless `resolvedTextureDirty && usesResolve()`, and `usesResolve()` is `resolvedTexture != nullptr`, which is only ever created for an MSAA target. MSAA is forced off under VR (`43`). `getResolvedTexture()` then returns `texture.get()` |
| **The downsample** | **~~NO-OP, CONFIRMED~~ — FALSE, AND CORRECTED BY `108` §4 ON THE DAY THIS WAS WRITTEN.** `ds_option` had already been changed to **`2`** the night before (`108` §3) and this line read the value out of `00-START-HERE`'s environment table instead of off the disk — **`48` item E exactly.** At `ds_option 2` the `downsampleTarget` branch IS taken: **a compute dispatch per eye per present, on the path G-107-2 measures.** The reference-height reduction that could cancel it (`rt64_workload_queue.cpp:476-480`) needs `nativeColorHeight >= 360`; GoldenEye's is 240, so it does not fire |
| **The descriptor rebuild** | **DOES NOT HAPPEN.** The set is rebuilt only when `descriptorSet == nullptr` or the SAMPLER changed. The texture is not part of that test |
| **The descriptor WRITE** | **HAPPENS EITHER WAY.** `setTexture` -> `setSRV` calls `CreateShaderResourceView` and marks the range host-modified **unconditionally**, with no comparison against what was there before. `setDescriptorSet` then calls `updateShaderVisibleSet`, which copies **whenever `hostModifiedCount != 0`** — which is every present, knob or no knob |
| **A layout transition** | **SAME SHAPE EITHER WAY.** The present thread barriers the sampled texture to `SHADER_READ` every present; the workload thread renders into the frame-0 eye targets every game frame and takes them back to `COLOR_WRITE`. That round trip happens with the knob OFF too |
| **A queue sync** | **NONE keyed on the texture.** There is no cross-queue fence anywhere in this path — see §3 |

> ## **SO NOTHING IN THE SAMPLING PATH IS CONDITIONAL ON `params.texture` HAVING CHANGED. `106` §6's framing — "the cost is in changing the sampled texture" — HAS NO MECHANISM BEHIND IT.**

**That is a negative, and it is the point of having done the read.** It does not
say the cost is elsewhere in the pass path; it says the one place `106` named
cannot produce it.

---

## §2 — AND THEN THE ACTUAL DEFECT, FOUND WHILE LOOKING FOR SOMETHING ELSE

**`rt64_workload_queue.cpp`, as `105` left it:**

```cpp
const size_t eyeTargetsPerSet = size_t(displayFrames) * 2;                       /* :1263 */
...
const size_t eyeWriteSet    = (geVrEyeInterpAlloc > 0) ? geVrEyeWriteParity : 0;
const size_t eyeTargetIndex = (eyeWriteSet * eyeTargetsPerSet) + (frame * 2) + eye;  /* :1376 */
```

**`displayFrames` IS NOT A CONSTANT.** It is recomputed a hundred lines above,
every workload, from `logicalTicks - displayTicks` (`:1130`) — and at a 60 sim
driven into a 90 target **it alternates 1, 2, 1, 2**, which is the whole reason
`92` exists.

**So the second set's base address MOVES:**

| Workload | `displayFrames` | parity | `eyeTargetsPerSet` | set base | targets written |
|---|---|---|---|---|---|
| N | 2 | 0 | 4 | 0 | **0, 1, 2, 3** |
| N+1 | 1 | 1 | 2 | **2** | **2, 3** |

> ## **WORKLOAD N+1, WRITING "SET 1", WRITES TARGETS 2 AND 3 — WHICH ARE SET 0's PASS-1 PAIR, THE ONE THE PRESENT THREAD IS READING.**

**The double buffer is defeated on roughly every other frame.** `105` §3's
elimination survives (it measured the CPU and the GPU, not the buffering), but
**`105`'s central claim — "the present thread reads a set the workload queue
finished an entire game frame ago and is not touching" — is FALSE as written.**

### §2.1 — WHAT THAT COSTS US

**`48` rule 4: results from a broken instrument are not weak evidence, they are
NO evidence, and must be marked void.**

| Claim | Status |
|---|---|
| `105` "option A did not move the number, therefore the write-while-read dependency is not the cause" | **VOID.** The dependency was not removed |
| `106` §2 "the handover between the threads is not the problem" | **UNSUPPORTED.** It rests entirely on `105` having worked |
| `106` §6 "the only thing left is the sampled-texture variable" | **UNSUPPORTED**, and §1 above removes its mechanism as well |
| `103`, `104` | Unaffected. Neither had a second set at all |

**And it is the same shape as `43`, `32` and `50` Risk 3, which is why it is
worth naming: a mechanism that announces a property it does not have.** `105`
printed no gate that would have caught it — `vrEyeTargetsRebuilt` reports the
COUNT of targets, which was correct, and says nothing about which INDEX each set
occupies.

---

## §3 — THE PRESENT THREAD'S REAL STRUCTURE, WHICH IS NOWHERE IN THE DOCS

Read while chasing the 75 ms. **None of this is new code; it is new to the
written record**, and every route from here depends on it.

1. **`submitFrame()` RUNS ON RT64's PRESENT THREAD** — `ge_vr_xr.cpp:2293`,
   confirmed by `ge_vr_xr.cpp`'s own comment at the head/eye transport:
   *"Written on RT64's present thread inside the XR frame loop."*
2. **So one present iteration is strictly serial:** eye blits recorded ->
   `executeCommandLists` -> **`presentGraphicsWorker->wait()`, a CPU block on
   the GPU fence** (`rt64_present_queue.cpp:677`) -> `xrWaitFrame` ->
   `CopyTextureRegion` -> `xrEndFrame`. **There is no overlap between the eye
   work and the XR frame; the same thread does both, in order.**
3. **`workloadGraphicsWorker` and `presentGraphicsWorker` are TWO INDEPENDENT
   `ID3D12CommandQueue`s with their own fences** —
   `rt64_application.cpp:259-260`, `rt64_render_worker.cpp:10-19`. **There is no
   cross-queue GPU synchronisation between them anywhere.** They share exactly
   one thing: the CPU-side `interpolatedMutex` / `interpolatedCondition`.
4. **`D3D12Texture::resourceStates` is a plain non-atomic member**
   (`rt64_d3d12.cpp:1547`) mutated from both threads. It works today because the
   CPU handshake happens to order them. **It is not guaranteed by anything.**

**That is the shape in which a source-target dependency becomes a whole-pipeline
stall rather than a small one**, and it is why a broken double buffer is a
sufficient explanation for the numbers `103`-`105` measured.

---

## §4 — THE FIX AS BUILT

**One file, `rt64_workload_queue.cpp`. Backup at `.bak107`.**

**A FIXED stride, so the two sets are disjoint for every value of
`displayFrames`:**

```cpp
static const size_t GE_VR_EYE_SET_STRIDE = (VR_EYE_PASS_MAX + 1) * 2;   /* 18 */
const size_t eyeTargetsPerSet = (geVrEyeInterpAlloc > 0)
    ? GE_VR_EYE_SET_STRIDE
    : (size_t(displayFrames) * 2);           /* knob off: exactly as before */
```

**Set 0 owns indices 0-17, set 1 owns 18-35, for every workload, forever.**

**AND IT COSTS NOTHING, WHICH IS THE ANSWER TO `106` §5's OBJECTION.**
`RenderTarget`'s constructor allocates no GPU memory —
`rt64_render_target.cpp:23` stores four fields and returns; every texture is
created lazily on first use. **A slot never rendered into is a null
`unique_ptr` and one pointer of RAM.** The number of targets that actually
ALLOCATE is unchanged: with `displayFrames` alternating 1 and 2, four in set 0
and four in set 1, exactly as before.

**Plus a clamp.** `frame` is bounded only by `displayFrames`, so an unclamped
index could run off the end of its set and into the other one — the very fault
being fixed, in a rarer costume. Frames at or beyond `VR_EYE_PASS_MAX` park in
a spare pair. **They are never published** (the `frame < VR_EYE_PASS_MAX` guard
at `:1424` predates this), so the spare pair is never sampled.

**`GE_VR_EYE_INTERP=0` remains an exact identity.** Both changes are inside the
`geVrEyeInterpAlloc > 0` test; an unset build is byte-identical to before `103`.

---

## §5 — THE GATES. TWO OF THEM NEED NO HEADSET.

```powershell
.\build.ps1
.\vr.ps1 -UnitsPerMetre 50 -SeamNoRot -HandPosZ 1 -EyeInterp
```

| Gate | **PREDICTION** | What a failure means |
|---|---|---|
| **G-107-1** | `interpUsed=` still reads roughly one third of `submits` | **ZERO means the pass path stopped running** and nothing below is judgeable. The fallback to the legacy frame-0 pointer is silent by design, and this is the line that exposes it |
| **G-107-2** | **`reused` stays ~0 AND `submits` returns toward 90 AND fps returns toward 60** | **THIS IS THE WHOLE EXPERIMENT.** Pass: `105` was right and only its arithmetic was wrong — the handover WAS the problem and Route D is alive. Fail: `106` §2's conclusion is finally supported by an experiment that actually ran, and `106` §6 move 1 is next |
| **G-107-3** | `vrEyeTargetsRebuilt` fires **once**, reporting 36 | More than once means the resize is thrashing |
| **G-107-4, worn** | `-NoXr` and a knob-off VR launch are unchanged | The identity claim in §4. **`106` §7.2's guard-walk check batches here** |

> ### ►► PIN `ds_option` BEFORE RUNNING ANY OF THESE — `108` §4.1 ◄◄
>
> **`103`-`106`'s numbers were all taken at `ds_option 1`, and the file on disk
> now says `2`.** A `107` run at `2` compared against `106` §1's table measures
> two changes at once.
>
> **RUN G-107-2 AT `ds_option 1` FIRST** — restore from
> `graphics.json.bak-preDS2` — **then re-run at `2` if you want the supersampled
> number.** And re-check the file after ANY in-game menu visit: the menu
> rewrites `graphics.json`, which is `43`'s standing hazard and would put
> `ds_option` back mid-experiment without saying so.

**WHAT THIS CANNOT DO, stated before it is run** — `104` §2's discipline. The
head pose is still sampled once per game frame. **`posecheck`'s `MAX delta`
will not go to zero and head turn may not improve. Stick turn is the half this
addresses.**

---

## §6 — WHAT IS STILL OWED, IN ORDER

1. **`106` §6 move 1 is NOT superseded** — alternate the present thread between
   two copies of the SAME finished frame-0 pair, changing only the
   sampled-texture variable. `56`'s method, still unapplied after four
   attempts. **§1 above makes it MORE worth running, not less: it now has no
   candidate mechanism, so a stall there would be genuinely surprising and a
   clean pass would close the question.**
2. **A per-present stage timer inside the present thread's VR block.** The only
   timing we have is the host's `stage ms`, and `72` and `106` both warn that a
   mean cannot see a hitch. **O74, outstanding since `73`.** §3 says where the
   probes go: around the blit, the `wait()`, and `xrWaitFrame` separately.
3. **A NAMED HAZARD, not a guard — rule 13.** With the knob on, if the pass
   lookup fails (`passCount == 0`, or the present loop wants more frames than
   the workload produced) the fallback is the legacy `vrEyeZeroTarget` /
   `vrEyeOneTarget` pair, which now points into **the set being written right
   now** — `103`'s hazard on the fallback path. **No guard was built because the
   instrument already exists: `interpUsed` below `submits`/3 means it fired.**
   `89`'s reasoning, and `42` is why.
4. **Then `23`** — partial interpolation, promoted by `92`, and **not** a
   prerequisite (`106` §7.1).

---

## §7 — WHAT THIS DOES NOT CLAIM

**It does not claim to have found the stall.** It claims that the experiment
which was supposed to eliminate the handover **did not eliminate it**, and that
the one mechanism `106` proposed in its place **does not exist**. Those are two
negatives and one fix, and the fix may simply not help.

**`106` §7 is the model here:** the cheapest test in the sequence was the one
nobody ran, and it overturned a section. **G-107-2 is that test for `105`.**
