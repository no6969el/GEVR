> **►►►►►►►► SUPERSEDED 2026-09-03 BY `NEXT-SESSION-PROMPT-305`. KEPT BECAUSE RULE `2` DELETES
> NOTHING. ◄◄◄◄◄◄◄◄** The session this prompt launched wore `RUN-SHEET-304` §1 and §5/§5a, and
> **§1 found a false negative in `stereo_eyediff.py` itself** -- so this document's calibration
> figures ("three hits, no false positives", "a factor of ten", "88 stereo frames") are the
> nine-frame, greyscale ones and are **corrected in `304` §1.2 and §1.3.** Read `305`.

Read `repo\docs\00-STATE.md` — the **currency line at the top** (it is `303` WORN and it is the
whole handover), then **§3 OWNER ACTION OUTSTANDING — the top FOUR entries are new**, then **§4
RETRACTED — FOUR NEW ENTRIES AND TWO OF THEM ARE `303`'s OWN**, then **§6 TRAPS — FIVE NEW.** Then
**`303-THE-VIEWER-WAS-THE-DEAD-EYE-AND-THE-SECOND-EYE-IS-THE-REFERENCE-FRAME` §0**, which is the
session in one table. Then **`RUN-SHEET-304` §0 and §1.** Then **`PRIORITY-BOARD-299`**, where
GROUP `B` and `H9` are struck through and **GROUP `C` has been rewritten from the top.**

Same rules as always. **You work OFFLINE. The build, every run and every commit are the owner's,
on the main PC. Supply complete copy-paste PowerShell blocks; quote a run-sheet block verbatim,
never paraphrase it. Never stage, commit, branch, merge or tag.** Bridge reads are not free
(`00-STATE` §6): `git log`, `git show` and `git diff <path>` are safe; `git status` and `git add`
are **NOT** (use `git --no-optional-locks status`), and **a bare `git status` in the decomp prints
2,106 CRLF-dirty files — always give it a path list** and pass `--ignore-cr-at-eol`.

---

## ►►►► WHERE THINGS ACTUALLY STAND ◄◄◄◄

**`RUN-SHEET-303` IS WORN IN FULL AND ITS THREE COMMITS ARE IN** — `94cdf01c` (decomp) /
`c26c58d` (native) / `d393860` (GoldenEyeVR), all three trees clean afterwards. The binary is
**`45756E5A…3F92`, 18,070,774 bytes, 21:05**, and `EXPECTED-EXE-303.txt` is beside it. **Do not
re-run any part of `303`, §5 included.**

**THE SESSION'S TWO FIXES CAME OUT OPPOSITE WAYS, AND A THIRD THING NOBODY ASKED FOR IS WORTH MORE
THAN EITHER.**

### 1. GROUP `B` closes, completely.

`[MEASURED]` V1: eye1 `MODEL_MTX` **38** against V2's `0`, `MODEL_VTX` 16/16, `MODEL_COL1` 19/19,
**`only in eye0 = 0` AND `only in eye1 = 0` on every opening grab**, cumulative `viewer=0`,
**ZERO-REBUILD 0 of 3015, and NOT ONE FRAME WITH `skipped>0` IN THE WHOLE RUN.** `[REPORTED]`, the
owner: *"Yes it does and it loads better than before without all that texture in the left eye"* —
and asked directly, that texture is **GONE**, not reduced. **It was `299` §8.2's symptom, not a
second one.**

### 2. The far-clamp arm is a `279` §7 null, and `RUN-SHEET-303` §0.1 is NOT supported.

FC1 far `clamped=81,076` = `straddle` **exactly**, FC2 `0`, near `clamped=0` in both — **the knob
took at full strength and the owner sees the same picture in both arms.** The reason is
`[MEASURED]` and it is about the venue: **`[getv][far]` is cumulative across two scenes that
differ 15x** — the road runs **1.2–5.9% `beyond_far`**, the cast roll **40–71%** — so `302` §4's
`13.2%` is a blend and is comparable to nothing. **The far clamp fires 45,000/Mvtx in the cast
roll, which is two enormous unlit quads and the cast text, and 50–2,300/Mvtx on the road, which is
where the owner was actually looking.** The venue maximised the counter and minimised the picture.
**Unanswered, not false.**

### 3. ►►►► The `NaN` hypothesis is dead, and the symptom that replaced it is a NEW CLASS.

`C1` (`GETV_STEREO_MTXGUARD=1`, not in the sheet, no build needed) reads
**`arrays=366456 already-converted=0 skipped=0`** against `292`'s 88,520/183,808 and `299` E2's
11,902/144,716 on a comparable arm — **upstream 2.5x larger, so `298` §4.2 makes it a result and
not a masked zero** — and **the instrument printed its own pre-registered null:**

```
[getv][mtxguard] already-converted=0 means the saturated matrix came from somewhere else
                 and this diagnosis is WRONG -- do not keep it.
```

**And the live symptom is a picture: a flat slate polygon occludes wall geometry in ONE eye** in
`dlgrab_V1_2732`, `dlgrab_C1_2336` and `dlgrab_C1_4676` — **in frames whose census reads
`MODEL_MTX 39/39`, `MODEL_VTX 17/17`, `only in eye0 = 0` AND `only in eye1 = 0`.** Same commands,
different picture. `[REPORTED]`: *"bond bobs and it changes the output."* **Every eye fault this
project has chased since `292` was an ADMISSION fault. This is the first one that is not, and
neither inherited explanation survives measurement.**

---

## ►►►►►►►► THE FIRST ACTION: `RUN-SHEET-304` §1 — WEAR THE TOOL, THEN SWEEP. ◄◄◄◄◄◄◄◄

**IT NEEDS NO BUILD AND NO GAME.** §1 wears `stereo_eyediff.py` on the main PC (`H7`: `303` ran its
selftest under the bridge's `python3`, not `py`) and then sweeps every grab in the tree.

**`H9` IS CLOSED AND THE FILED FIX WAS WRONG ABOUT THE IMPOSSIBILITY, NOT ABOUT THE DEFECT.**
`H9` said a reference-frame differ *"would need a known-good frame this project does not have."*
**True of a MONO frame. False of a STEREO one:**

> At `GETV_STEREO_OFFSET=0` the two eye halves MUST be identical apart from the viewmodel.

So the known-good frame is **in the same picture** — same run, same rig, same instant, nothing to
normalise and nothing to remember. `getv/tools/stereo_eyediff.py`, **selftest 14 checks 0 failed**,
and on `303`'s nine grabs it separates by a factor of ten: **six clean frames 0–207 px against
2,196 / 4,544 / 5,947 px. Three hits, no false positives.**

**►► THE SWEEP IS NOT ABOUT THE THREE FRAMES WE ALREADY KNOW ABOUT.** `[MEASURED]`: 21 grab
folders, 238 BMPs, **88 of them stereo dumps**, at ~0.47 s each. Those 88 were taken across
`298`–`303` by an instrument that could not see this class of fault. **A hit in `298`, `299` or
`301` dates the polygon to before the viewer fix and detaches it from `303` entirely. Finding hits
only in `303`'s own grabs is also an answer, and a more uncomfortable one.**

---

## ►►►► THE THING THIS SESSION SHOULD BE MOST CAREFUL ABOUT ◄◄◄◄

**A FILED FIX IS A DIAGNOSIS, NOT A PATCH — AND THE COUNT IS NOW FIVE.** `H1`, `H3`, `298` §4.4,
`302` §3c, and now **`H9`, whose filed fix declared the thing impossible that was sitting in every
stereo BMP the project had already taken.** Four of the five were caught the same way and it was
never by re-reading the note: **follow the call, or run the arithmetic.**

**AND `303` ADDED TWO OF ITS OWN TO §4 RETRACTED**: the far clamp's causal claim, and
`RUN-SHEET-303` §4's *"on a loop there is nothing to normalise"* — true of the eyes, **false of the
counters**, which accumulate over the walk and the death as well as the loop.

**GROUP `C` MUST BE REWRITTEN BEFORE IT IS WORKED, NOT AFTER.** Its hypothesis died in `303` §4 and
the board now says so. **Do not inherit either excluded explanation for the polygon.**

---

## ►►►► AFTER §1 AND §2: WHERE THE WORK GOES ◄◄◄◄

- **`304` §2 — the polygon, `dlgrab_C1_4676` first.** It diverges BROADLY — 900 blobs, 44,252 px,
  alignment `mad` **6.409** against every other frame's 3.4–4.1 — where the other two carry one
  polygon. **Establish whether that is the same fault at amplitude or a second one, and say which.**
- **`304` §3 — FC3/FC4 at the road**, optional, and **gated per window at `302` D3's 3.9–5.9%**.
  A run that stays under 3% is another `279` §7 null however clean the arms look.
- **`304` §4 — one `Move-Item`**: four `dlgrab_D3_*` files are sitting in `grabs_303_V1\`.
- **`H11` / `H12` / `H13`** — the far line's mixed counters, the far census's cumulative blend, and
  **the constant seven commands the second eye never gets** (`cmds` 6587/6580 in every grab of
  every stereo run, and no document explains it). All `LOW`.
- **GROUP `D`** unblocked, `D1` `LOW`. **GROUP `E1`** has now survived four arms untested.

**`169` NEXT ID = `U-26`.**
