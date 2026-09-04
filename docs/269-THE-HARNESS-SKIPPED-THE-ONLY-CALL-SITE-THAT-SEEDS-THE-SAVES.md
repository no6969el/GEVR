# 269 — `GETV_MENU` SKIPS THE ONLY CALL SITE THAT SEEDS `saves[]`. THREE SYMPTOMS, ONE CAUSE.

**2026-08-30. Session ran the three-boot A/B the owner asked for, killed two of my own
theories with it, and fixed the fault the third arm exposed.**
**Started as "the late gun sound". THE LATE GUN SOUND DID NOT REPRODUCE.**

---

## §1 — ►►►► THE FINDING ◄◄◄◄

`fileValidateSaves()` has exactly TWO call sites, and a `GETV_MENU` boot takes **NEITHER**:

| site | gate | taken on a `GETV_MENU=5` boot? |
|---|---|---|
| `boss.c:401` | `if (g_StageNum != LEVELID_TITLE)` — a `GETV_STAGE` direct-to-level boot only | **NO** — `GETV_MENU` is a TITLE boot |
| `front.c:1461` | inside the LEGAL SCREEN init | **NO** — that is the screen the override exists to skip |

`[MEASURED]` from the run logs, and this is the whole proof:

| | `lg:1-load` … `lg:8-done` | `lg:7-fileValidateSaves` | level audio |
|---|---|---|---|
| `run_audio_E` (normal boot) | all present | **present** | **works** |
| `run_audio_D` (`GETV_MENU=5`) | **none** | **absent** | **silent** |

## §2 — WHY THAT PRODUCES SILENCE, AND WHY MUSIC AND SFX DIE TOGETHER

**The consequence was already written down in this codebase, about a different field.**
`file2.c:519-530`, on the missing crosshair and ammo counter:

> *"A zeroed slot has `SAVEFLAG_DORESET` CLEAR and folder 0, so `fileGetSaveForFoldernum(0)`
> hands it back as though it were a real save whose options word is 0.
> `fileLoadSettingsForFolder()` then applies those zeros over the correct static defaults."*

Without `fileValidateSaves()`, `saves[]` stays BSS zeros and that fake save is returned
**FOR ANY FOLDER** — which is why the folder the owner picks makes no difference. Then:

```
lv.c:397   musicTrack1ApplySeqpVol(VOLUME_MAX)          <- both paths. Volume is MAX.
lv.c:454   init_watch_at_start_of_stage
             -> fileLoadSaveSettingsForSelectedFolder   (file.c:61)
             -> fileLoadSettingsForFolder               (file2.c:1404)
                  set_mTrack2Vol((save->music_vol << 7) | (save->music_vol >> 1))   <- 0
                  sub_GAME_7F0A91A0((save->sfx_vol  << 7) | (save->sfx_vol  >> 1))  <- 0
lv.c:456   sub_GAME_7F0C11FC -> set_missionstate -> musicTrack1ApplySeqpVol(get_mTrack2Vol())
```

**Music and SFX die together because `file2.c:1413` and `:1414` are adjacent lines fed by the
same fake save.** A music-only fault could never have explained the SFX silence.

**SELF-REINFORCING, AND THIS IS THE DANGEROUS PART.** `file2.c:1348` writes
`save->music_vol = get_mTrack2Vol() >> 7`. **A save written during a `GETV_MENU` run persists
the zeros.** `[INFERRED]` this is a live candidate for `00-STATE` item 6, *"the saves I had are
gone"* — writes performed while `saves[]` was garbage. **NOT established.**

## §3 — THE FIX, AND HOW THE HARNESS CAME TO BE WRONG

`initmenus.c` mirrors `boss.c`'s block — it calls `set_selected_difficulty()` and
`set_solo_and_ptr_briefing()`, which are `boss.c:404` and `:406`. **It was copied from
`boss.c:404` onwards and missed `:401`.** The omission is invisible from `initmenus.c`.

`fileValidateSaves()` now runs at the top of the `GETV_MENU` block, behind a banner.
**`GETV_MENU_NOVALIDATE=1` restores the old behaviour** for A/B on one binary.
`boss.c:403`'s `fileSetCurrentFolder(FOLDER1)` was **deliberately not copied** — on
`GETV_MENU=5` the file-select screen sets it. **Revisit for `GETV_MENU=7`.**
Diagnostic path only: the block is unreachable unless `GETV_MENU` is set.

## §4 — THE GATES, WRITTEN BEFORE THE BUILD, AND BOTH PASSED

1. **Primary:** `g_vol` holds `32767` through the level load instead of dropping to `0`.
   `[MEASURED]` it does. `nz=3117/3121` — essentially every frame non-silent over 3,000+
   frames, against Arm A's `nz` frozen at `422` for the rest of the run.
2. **Independent, and the one that mattered:** `file2.c:519-530` says the same zeros switch
   off sight-on-screen and ammo-on-screen, **so the crosshair and ammo counter must come
   back too.** `[REPORTED]` owner: they did. **Three symptoms, one cause — that is what
   separates this from having moved the symptom.**

## §5 — ►► WHAT IS RETRACTED. BOTH ARE MINE, AND BOTH WERE KILLED BY A STATED FALSIFIER ◄◄

1. **"The late gun sound is the audio queue depth — `GE_QUEUE_TARGET` is 66.8 ms in the
   code's real units and `want.samples=512` adds 23.2 ms."** **DEAD.** `[MEASURED]` `q=` runs
   1114-1436 and `n=720` in BOTH the silent arm and the working arm; the
   `queued >= GE_QUEUE_TARGET` early-out at `port_audio.c:616` **never fires in any run**.
   The queue accounting is indistinguishable between a healthy run and a totally silent one.
   **The sign was wrong too** — over-queueing produces LATENESS, and the fault was SILENCE.
2. **"The silence is the selected folder's save holding `music_vol=0`."** **DEAD, and killed
   in one run by a falsifier written in advance.** Predicted: harness + a different folder
   would have sound, normal boot + the silent folder would not. `[MEASURED]` **BOTH came out
   the opposite way.** The folder is not the variable; `saves[]` being unseeded is.

## §6 — DEAD THEORIES — DO NOT REOPEN WITHOUT NEW DATA
- **The audio silence is NOT the SDL device, the queue accounting, the synthetic clock, the
  buffer size, or `SDL_GetQueuedAudioSize`.** The mixer runs and SAVES throughout
  (`mixops` +25,000 per 120 frames, `saves` climbing, `voices=[3-8,0,0]`, `req=[m2,s110]` —
  **the game is still asking for 110 sound effects**) and emits digital zero. **It was a
  volume of zero, applied at the source.**
- **`GETV_MENU`'s silence is NOT folder-specific.** Three arms, three folders, all silent.

## §7 — WHAT IS NOT CLAIMED
- **THE LATE GUN SOUND DID NOT REPRODUCE.** `run_audio_B` mashed through to Dam with
  `rms` 3300-3600 throughout. `00-STATE` item 8 stays `[REPORTED]` and unreproduced.
  **No fix for it may be proposed on this session's evidence.**
- **A `g_vol=0` window still exists** — 10 consecutive samples at the level-load transition,
  between two healthy stretches. It now RECOVERS where Arm A never did. Not investigated.
- No claim that this explains item 6. §2's write path is `[INFERRED]`.
- **`GETV_MENU=7` is untested** and `fileSetCurrentFolder` is deliberately absent from it.

## §8 — NEW, `[REPORTED]` THIS SESSION
**The crosshair auto-centres, and aiming with the mouse fights it** — owner: *"it keeps
putting you back."* **Not diagnosed. Not established as port-introduced rather than retail.**
This is `P8` territory (aim independent of facing/camera/locomotion) and belongs to
`258` STAGE 7, not to a bugfix queue. `GETV_MOUSE_SENS` / `GETV_MOUSE` / `GETV_GUN_AIM`
exist and have not been read.

## §9 — METHOD NOTE
**The three-boot A/B was the owner's instinct, not the plan's.** The session opened with a
designed instrument for a buffer-size theory. **The owner said the fault depended on how he
loaded through the menu — and that one sentence killed the buffer theory, produced a
deterministic 30-second repro where an intermittent report had stood for days, and led
directly here.** Rule `16` again: the repeated report is a ranking error, and the reframe
outranked the analysis. **THAT IS FIVE TIMES OUT OF FIVE.**
