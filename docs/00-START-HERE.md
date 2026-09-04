# START HERE — GoldenEyeVR handoff

> # ►►►► **THIS FILE IS 4,300 LINES. FOR ORIENTATION, READ `00-STATE.md`.** ◄◄◄◄
> **`00-STATE` carries the current truth in ~170 lines and points back here.**
> **Come here for: THE RULES (18), `P1`-`P9`, the spirit test, prior art and the
> licence split.** Everything above "THE RULES" is dated banner history — kept
> per DELETE NOTHING, not read for orientation.

> # ►►►►►► 2026-08-29c — **THE POINTER-ARITHMETIC SWEEP PAID OFF AND PHASE A IS
> # CLOSED. STEREO IS SCOPED, NOT STARTED.** ◄◄◄◄◄◄
>
> ## **THE ONE THING TO DO NEXT: COMMIT, THEN ONE `GETV_MTXTRACE` LAUNCH.**
> **`255` §6 then §4 step 1. No code is written until that measurement exists.**
>
> ## ►► **`[MEASURED]` THE ONLY VR REFERENCE TREE ON DISK IS NOT WIRED.** ◄◄
> `007-VR`'s `vr/` is 4,450 lines with **two** call sites outside it in the whole
> repository. **`gevr_shim_init` is never called** — `g_vr.active` is never set —
> so `fr.c:719` returns `0` on every frame. **There is no eye loop**, and
> **`gevr_shim_eye_view_n64` has no call site at all.** Projection-only gives
> frustum shift, not eye separation: **that build would show one image in both
> eyes.** `255` §1. **This corrects `254` §3.1, which called it merely "unrun".**
>
> ## ►► **WHAT WE TAKE FROM IT ANYWAY** ◄◄
> The seam is `viSetupCurrentPlayerView` — **our `fr.c:696`**. `guPerspectiveF`
> is **row-vector**, GL is **column-vector**; transpose or the frustum scrambles.
> Engine yaw is the **negative** of the right-handed convention (`bondview2.c`
> rotates by `360 - vv_theta`); **the pitch sign is honestly left unasserted.**
> `guPerspective` cannot express an asymmetric frustum, so it must be **replaced**
> — and `g_viPerspNorm` left alone.
>
> ## ►► **BEFORE ANY STEREO CODE** ◄◄
> **`gfx_pc.c` is GITIGNORED** — `tools/fetch-thirdparty.sh regen` belongs in the
> same commit (`233` §6.1). **`gfx_run()` swaps buffers at the bottom**
> (`gfx_pc.c:5817`), so a per-eye replay swaps twice unless it is split.
> **The projection interception point is one site: `gfx_pc.c:2167`,
> `gfx_sp_matrix()` under `G_MTX_PROJECTION`.** The game-side alternative is
> `fr.c:696`. **`255` §3 names both and recommends neither** — `GETV_MTXTRACE`
> decides it.
>
> ## ►► **THE GATE, AND IT DOES NOT NEED A HEADSET** ◄◄
> Desktop SBS window, `GETV_STEREO_OFFSET=500`, cross-correlate the halves, with
> the **`PREDICTION:` line written to the log before anyone looks** (`70`).
> **A build that still renders one image cannot pass; a build with real per-eye
> views cannot fail.** That is the test `234` failed to apply.
>
> ## **FIXES THAT LANDED, BOTH FROM ONE FAULT CLASS — THE DECOMP ENCODES POINTER
> ## SIZE IN ARITHMETIC:** `bondviewSelectCuff`'s `switchindex << 2` over 8-byte
> pointers (`GETV_CUFFIDX`, **`G-250` PASSED** — instant pickup, full inventory
> rotation, **and it took the slow pickup and the ammo re-pickup with it**) ·
> `->datas[i]`'s 8-byte stride over a 4-byte-word pool at four sites
> (`GETV_RWSTRIDE`, **`G-251` PASSED**) · `ALIGN64_V2`'s `(u32)` cast on a
> pointer at `front.c:8517` (`ALIGN64_V2_PTR`, no knob, no known symptom).
> **`build_windows.ps1:160` is still `-w`. The sweep is the prize, not the three
> fixes.**
>
> ## **THE LOOT BOX WAS NEVER A BUG** (`252` §6, owner-prompted). A hedged
> report was flattened into a table row, inherited status from two adjacent real
> crashes, and was propped up by a register `249` had already retracted.
> **`MultiAmmoCrateRecord` took ten seconds to read.**
>
> **Everything below is the previous banner. History and fallback. DELETE NOTHING.**

---

> # ►►►►►► 2026-08-29 — **THE PORT'S REAL DISEASE IS POINTER ARITHMETIC. THREE
> # INSTANCES FOUND IN ONE NIGHT.** ◄◄◄◄◄◄
>
> ## **THE ONE THING TO DO NEXT: BUILD AND RUN `G-251`.** `251` §5.
> **`GETV_SLOTFREE = 0` stays in `goldeneye.cfg`. Keep the NEW `goldeneye.map`
> with the run's log — a map only resolves the binary it was built with.**
>
> ## ►► **`[MEASURED]` THE DECOMP ENCODES POINTER SIZE IN ARITHMETIC, AND THE
> ## BUILD COMPILES WITH `-w` SO NOTHING EVER WARNS.** ◄◄
> **`build_windows.ps1:160` is `@('-w','-Werror=return-type')`. Turning four flags
> back on gave 52 `-Wpointer-to-int-cast`, 3 `-Wint-conversion` and 1
> `-Wint-to-pointer-cast` across HALF the game files** (`248` §4). Three defects
> of that family were found this session and **two of them only because a crash
> pointed at them:**
>
> | site | the mistake | state |
> |---|---|---|
> | `bondviewSelectCuff` (`250`) | `switchindex << 2` — a **4-byte stride over 8-byte pointers** | **FIXED**, `GETV_CUFFIDX`. `G-250` PASSED |
> | `->datas[i]`, four sites (`251`) | an **8-byte stride over a 4-byte-word pool** — the same error inverted | **FIXED**, `GETV_RWSTRIDE`. **UNTESTED** |
> | `ALIGN64_V2` at `front.c:8517` (`248` §4.1) | a pointer forced through `(u32)` | **LOCATED, NOT FIXED** |
>
> ## ►► **HOW TO READ A CRASH. THE PORT NOW EMITS A LINKER MAP** (`243` §3). ◄◄
> **1.** Take `&g_mempPools` from `[getv] MEMP TABLE` in the run's log.
> **2.** Take `g_mempPools` from **THAT BUILD'S** `goldeneye.map`. **RE-READ IT
> EVERY BUILD** — it moved by `0x1000` between two builds and silently shifted
> every answer (`251` §2).
> **3.** `delta = runtime - map`; `PC(map) = FAULT PC - delta`; the containing
> symbol is the greatest `.text` symbol at or below it.
> **4. VERIFY THE PC DISASSEMBLES ON AN INSTRUCTION BOUNDARY before believing the
> symbol.** That check is what caught the stale anchor.
> **The handler also prints a full call stack — resolve every frame, not just the
> PC.** That is what named `bondviewSelectCuff`.
>
> ## **`fault addr: ffffffffffffffff` DOES NOT MEAN `-1`.** `249`.
> **It means the address was NON-CANONICAL, so the CPU raised #GP, which has no
> faulting address at all and Windows fills the field with ones.** **`243` and
> `248` both read it as a sentinel and both were wrong.** **A register holding
> `0xAAAAAAAA_00007ff6` is two halves of two good pointers, not one corrupt one.**
>
> ## **WHAT IS CLOSED SINCE `229`:** the intro cast crash's DIAGNOSIS (`233`; the
> FIX is parked, `242`) · the menu text — **NEVER A BUG**, folder strings are
> gated on save progress (`236`) · the folder screen — a stale `eeprom.bin`
> (`237`) · the purple explosion — `GETV_RGBA16BE=1`, and `244` explains WHY it is
> not a global default · the inventory crash and the slow pickup (`250`).
>
> ## **STILL OPEN:** the loot box handing out the wrong items — **REPORTED TWICE,
> NEVER READ** · ammo re-pickup · the wrong SFX (`GETV_AUDIO_TESTSFX`, built,
> never run) · audio latency ~51 ms · **PHASE 1, STEREO — NOT STARTED.**
>
> ## ►► **FOUR OTHER PORTS OF THIS DECOMP ARE NOW ON DISK** (`245`, `246`). ◄◄
> `local-only\clone-prior-art.ps1`. **The work is never on `master`** — six of nine
> forks surveyed were the decomp's own head commit untouched.
> **`mattymattmattmatt/007-VR` carries a 21,524-line OpenXR layer that reaches
> `g_CurrentPlayer->vv_theta` — the game camera `194` said never learns about the
> head, CONFIRMED in our tree at `bondview.h:558`, offset `0x148`, `f32`.**
> **DO NOT SWITCH BASES: its README says *"the game has never been run."***
> **`jeffory/007portable` names `modelGetNodeRwData` and `makeonebody` in its own
> 64-bit commits.** **Both keep game pointers 32-bit by arena placement; ours does
> not, and `247` §2 Tier 3 is where that decision gets costed.**
>
> **Everything below is the pre-`229` plan and recomp-era history. DELETE NOTHING.**

---

> # ►►►►►► 2026-08-27 LATE — **PHASE 0 IS PASSED. IT BOOTS AND PLAYS.** ◄◄◄◄◄◄
>
> ## `[REPORTED]` ***"It works."*** **`goldeneye.exe`, 17.2 MB, the owner's ROM.**
> ## **THE ONE THING TO DO NEXT: `commit-session.ps1`. THEN THE MENU TEXT.**
>
> **READ `HANDOVER.md`, THEN `229` §20 (the plan). `229` §11 is the build.**
>
> ## ►► **THE COMMIT IS ITEM 0 AND IT IS NOT OPTIONAL.** ◄◄
> **40+ documents overdue, and the working native build EXISTS ONLY AS UNTRACKED
> WORKING-TREE STATE** — a CRLF fix, 550 extracted `.bin`, a 20.9 MB and a 6.9 MB
> generated source, and four edited files. **Table in `229` §20.**
>
> ## **`[MEASURED]` ALL FOUR PHASE 0 BLOCKERS WERE BUILD-PIPELINE. NONE WERE CODE.**
> Git symlinks checked out as 36-byte text files · the asset uniquify pass never run
> · **CRLF in `filelist.u.csv`, which made the ROM extraction skip 812 of 812 rows
> AND EXIT 0** · one double-applied symbol prefix. **Not one line of game logic was
> wrong.** **`229` §9 is the model for how it was found: a CONTROL was already on
> disk** — `imagelist.csv` is CRLF too, its loop does not test a flag, and its
> images extracted fine while obseg did not. **One run of one script proved and
> disproved the hypothesis at the same time.**
>
> ## ►► **THE MENU TEXT IS THE BLOCKER, AND THE ASSETS ARE INNOCENT.** ◄◄
> `[MEASURED]` every front-end text bank loads `NATIVE (early-out)`, both fonts
> convert with **`0/94`** bad glyphs, and there is **NOT ONE texture fault in
> 100,270 log lines** (0 `NULL texture`, 0 `could not load texture`, every
> `modeltex` `0 MISSING`). **The strings and the glyphs are PRESENT. They are not
> being DRAWN.** **It is a render question and the next step is a READ, not a run.**
> **The owner cannot navigate his own game until this is fixed, and every other
> symptom is reached through that menu.**
>
> ## ►► **THE PORT HAD NO STDOUT ON WINDOWS FOR THE WHOLE PROJECT UNTIL NOW.** ◄◄
> `[MEASURED]` PE **subsystem 2 (GUI)**: no console, no stdout handle, so
> `*> run.log` wrote a **ZERO-BYTE FILE** and every `printf` was thrown away —
> **nothing broken, nothing logged.** `-mwindows` came from `pkg-config --libs
> sdl2`, which `build_windows.ps1` already stripped two other flags out of.
> **Fixed; `-GuiSubsystem` restores it. TREAT EVERY RUNTIME CLAIM ABOUT THE NATIVE
> PORT MADE BEFORE `229` §13 AS `[ASSUMED]`.**
>
> ## ►► **NEW STANDING RULE — `48` EXTENDS TO ENVIRONMENT VARIABLES.** ◄◄
> **AN ENV VAR THAT RE-ROUTES THE BOOT PATH IS A BEHAVIOUR CHANGE, AND
> `GETV_MENU` IS ONE.** **`229` §16 blamed the audio mixer on a `pkAll=0` that
> `GETV_MENU=11` itself caused** — a shortcut introduced one section earlier —
> **and §19 then `[MEASURED]` `pkAll=32768` through a normal boot.** Two retractions
> from one confound. **PowerShell `$env:` PERSISTS for the life of the window:
> `Remove-Item Env:GETV_*` between runs, or open a fresh one.**
>
> ## **X-CLOSE IS THE CLEAN EXIT ON THE NATIVE PORT.** `[REPORTED]` the recomp-era
> ## crash *"doesnt happen on this build"*, and **`taskkill /F` would LOSE the 64 KB
> ## buffered stdout** — `HANDOVER` §3's `taskkill` note is recomp-only.
>
> **Everything below is the pre-Phase-0 plan and recomp-era history. DELETE NOTHING.**
>
> ---
>
> # ►►►►►► 2026-08-27 — DIRECTION IS THE NATIVE SOURCE PORT. READ `227`, THEN `229`. ◄◄◄◄◄◄
>
> ## **THE ONE THING TO DO NEXT: FINISH THE PHASE 0 NATIVE BUILD (`229`).**
> `[MEASURED]` `goldeneye-native` compiles game/assets/audio 100%; the port layer was
> blocked on one broken-symlink include (`PR/gbi.h`). Two fixes are on disk
> (`build_windows.ps1`, see `229` §1). **NEXT: owner re-runs the build, assistant reads
> `build.log`.** Local files to request + full runbook: `229` §6 and §3. Gate = the
> native game boots and plays from the owner's ROM.
>
> **Everything below is recomp-era history/fallback (DELETE NOTHING).**
>
> ---
>
> # ►►►►►► 2026-08-26 END OF SESSION — READ `HANDOVER.md` FIRST. ◄◄◄◄◄◄
>
> ## **THE ONE THING TO DO NEXT NEEDS NO HEADSET AND NO REBUILD.**
> **`223` §3's OFFLINE FRAME TEST. The data is already in `gevr.log`.** Compare
> `v2w^T . ray` against `v2w^T . (H . ray)` and `v2w^T . (H^T . ray)`, `H` from
> `POSEREC hq`. **PARSING TRAP: `MTXREC` and `POSEREC` SHARE A LINE.** A per-line
> state machine yields ZERO records — regex the file, zip by index.
>
> ## **THEN: `224` §5 — PROVE THE SOURCE PIPELINE. THE OWNER CHOSE THIS.**
> **`[MEASURED]` `lib/ge` is a MATCHING decomp** (313 C files, 1 non-matching,
> byte-identical ROM) **that is compiled by NOTHING today.** Gate is P2 (`make`
> reproduces sha1 `abe01e4a…`) and P5 (self-built ROM boots and plays).
> **IF P2 FAILS THAT ROAD DOES NOT EXIST — so no design work precedes it.**
>
> **`[MEASURED]` GoldenEye is DELTA-SCALED, not fixed-tick** — `g_GlobalTimerDelta`,
> 216 consumers, **and Rare shipped it at `1.2f` for PAL.** **90 Hz and a game
> speed control are one term** (`224` §2). Counter-example on file:
> `bondhead.c:284` DIVIDES by it.
>
> ## **WHAT THIS SESSION KILLED: THE COMPOSITION WAS NEVER THE BUG.**
> `thr*camT` is correct, is already the default, and `gunfire.c:570-574` says so
> in source. **`217`, `221` and two wear tests varied the wrong thing** (`223`
> §2.2). **`[MEASURED]` the error is CAMERA-DEPENDENT and YAW-ONLY** — pitch
> already tracks within ~5°. That rules out the cone, muzzle, seam and barrel.
>
> ## **A FIT I RAN AND WITHDREW:** one `ViewToWorld` across 11 shots, residual
> **119°**. The owner TURNED mid-run, so the camera is not constant and the model
> was wrong. **`223` §2.1, recorded so it is not repeated.**
>
> ---
>
> ## **THE PREVIOUS ENTRY — `G-220`, NOW RUN. SUPERSEDED, KEPT PER DELETE NOTHING.**
> ```powershell
> .\build.ps1
> .\build.ps1
> .\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
>          -WorldUnitsPerMetre 25 -HandUnitsPerMetre 25 `
>          -ViewmodelScale 0.5 -GunOffX 0 -GunOffY 0 -GunOffZ 0 `
>          -AimFromHand -MuzzleOrigin -NoCrouch -HudDepth 0.2
> ```
> **YOUR AIM MUST TURN WITH YOU.** `[MEASURED]` baseline to beat: **176 degrees
> of physical rotation moved the bullet 17** (`220`).
> **Mirrored or rotated -> `-BulletFrame 2`. Nothing changes -> `-BulletFrame 0`
> is today.** Three launches, no rebuild (`221` §2).
>
> ## WHERE THE AIM STANDS — UPDATED 2026-08-26 END OF SESSION
> **THE SEAM IS SOLVED** (`204`) · **THE CROSSHAIR'S PROJECTION IS CORRECT**
> (`193` §1, and `220` §3 says why head-relative is right for it) ·
> **THE BULLET'S DIRECTION IS WRONG, CAMERA-DEPENDENT AND YAW-ONLY** (`223` §2.3);
> **the COMPOSITION is settled and was never the fault** (`223` §2.2) ·
> **THE BULLET'S ORIGIN** is a constant offset (`215`) and waits ·
> **THE ASPECT IS A SEPARATE, MEASURED 30% FAULT** — game x/y `1.000` vs render
> `1.297` (`222` §2). **Do not let it muddy the aim test.**
>
> ## **THE OWNER'S MODEL, AND IT WAS RIGHT SINCE `164`:**
> *"the aimer is fixed to a 2D plane at a fixed distance in front of me... the
> gun doesn't really matter."* **`220` §2 — a head-relative direction planted on
> a camera that never turns BEHAVES exactly like that.** It sat in the corpus,
> in his words, for fifty-six documents.
>
> ## THE CROSSHAIR SPEC, OWNER'S DECISIONS (`220` §4): **disappear off-screen,
> sit ON the target, MUCH smaller.** U-21's edge inset is superseded.

> # ►►►►►► THE GOLDENEYE SOURCE IS ON THIS DISK. READ IT FIRST, EVERY TIME. ◄◄◄◄◄◄
>
> ## **`GoldenEye64Recomp\lib\ge\src\` — 242 files in `game\`, plus `include\`.**
> ## **Perfect Dark's VR port: `GoldenEyeVR\local-only\prior-art\perfect_dark_VR`**
> ## (branch `port`, commit `67ea20c`, MIT — **DO NOT RE-CLONE**, `161`).
>
> **`[READ]` SPOT-CHECKED: `gunfire.c:633`, `bondview.c:722`, `chraction.c:5854`
> ALL RESOLVE.** Line numbers cited anywhere in this corpus can be opened.
>
> ## ►► IT HAS ANSWERED QUESTIONS THAT COST WEAR TESTS. USE IT FIRST. ◄◄
> **`212` settled U-18 ENTIRELY FROM SOURCE — a question `171` §4 had parked as
> unanswerable, and which was about to cost a run.** In one sitting it produced:
> **`matrix_scalar_multiply` touches `[0..11]` only** (the basis, never the
> position) · **`IDO_POINT_ONE = 0.1`** is the model->game scale · **`field_B58`
> is written from TWO DIFFERENT FRAMES depending on the weapon** (`:758` camera,
> `:815` world) — **a landmine that would have been wired blind.**
> **And `189` §2 closed `A2` with `bondview.c:724`**, which had said for thirty
> years that the projection's centre is `c_screentop + c_halfheight`.
>
> ## **THE TWO RULES THAT GO WITH IT:**
> **1. SEARCH FOR THE MECHANISM, NEVER FOR PERFECT DARK'S IDENTIFIER** (`168`).
> `163` §7 concluded GoldenEye had no muzzle node because `MODELPART` returned
> zero — it cost a session, and `171` found the node under another name.
> **`210` §3 is the same trap arriving from outside: five files and three
> functions that do not exist here.**
> **2. GREP `patches/externs.h` AND `patches/structs.h` BEFORE COSTING ANYTHING**
> (`168` §5). It has blocked two slices and cleared three.
>
> > **A READ COSTS MINUTES. A WEAR TEST COSTS A SESSION AND CAN ONLY ANSWER THE
> > QUESTION YOU ALREADY THOUGHT TO ASK.**

> # ►►►►►► 2026-08-26 — THE PLAN CHANGED. READ `211` FIRST. ◄◄◄◄◄◄
>
> ## **THE CROSSHAIR WILL BE DRAWN WHERE THE BULLET GOES, NOT WHERE THE EYE
> ## LOOKS.** One computation replaces five knobs. **`211` is the design; nothing
> ## is built yet.**
>
> ## THE OWNER'S DECISION, AND THE TWO ROUTES RULED OUT
> **NOT a rebuild to match Perfect Dark** — `168`'s rule, learned three times: the
> designs transfer, THE SUBSYSTEMS DO NOT. **NOT more term-by-term tuning** — five
> knobs now move the same crosshair and fight each other.
>
> ## **WHY IT IS TRACTABLE NOW:** `204` solved the frame (744 poses) and `193` §1
> measured the projection innocent (55 shots). **The unknowns are closed; what is
> left is arithmetic over measured inputs.**
>
> ## `[MEASURED]` THE FAULT, FROM `210`'s RUN
> **Muzzle at `(-3.0, -8.1, -9.7)` cm — 8 cm BELOW the eye. Miss-then-hit at
> contact range: `4.38 deg` (yaw `+3.84`, pitch `-2.23`).** The vertical offset
> subtends `4.6 deg` at 1 m and `0.11 deg` at 43 m — **same order as the miss, and
> the VERTICAL term dominates.**
> **AND `210`'s PARALLAX CANNOT CURE IT:** its distance was stale (`626 m` at
> arm's length), PD's `1.75 m` floor zeroes it at contact range, **and it corrects
> HORIZONTALLY while the fault is VERTICAL.**
>
> ## THE ORDER: **`U-18` (the per-weapon muzzle — removes the last tuned input) ->
> ## THE SOLVER (~150 lines, host-side, no new game symbols) -> `G-211-1..4`.**
> **`-NoAimSolver` reverts entirely. The first run is a straight A/B.**
>
> ## **AND THE SCALE IS A SEPARATE PROBLEM.** `[REPORTED]` the guard reads
> *"smaller and skinnier"*. **"Skinny" is an ASPECT word, not a scale word** — it
> belongs with `205`'s calibration and the FOV, not with the aim.

> # ►►►►►► 2026-08-26 — `B1` IS BUILT. THE CROSSHAIR CONVERGES. `210`. ◄◄◄◄◄◄
>
> **`193` §2 `[MEASURED]` the bullet leaving `0.19`-`0.61 m` from the eye while
> the crosshair is drawn FROM the eye — two rays, same direction, different
> origins, meeting at ONE distance.** The crosshair now converges at the **last
> impact distance** (`item_related`, reachable, no new game symbols).
>
> **PD's design taken whole, and their three guards KEPT:** a `1.75 m` floor,
> **nominal-relative** correction, and a **`+-0.02` NDC clamp**.
> ## ►► AND THE CLAMP IS A TEST, NOT A COPIED CONSTANT ◄◄
> `[REPORTED]` the wearer fused at `-HudDepth 0.2`, which this file computes as
> **`~0.128` NDC — SIX TIMES PD's maximum.** `192` §1 flagged that `0.2 m` is
> nearer than the gun. **If the parallax alone fuses it, that gap WAS the missing
> depth. IF IT DOES NOT, our depth term and PD's differ by a large factor and
> THAT IS THE FINDING — do not widen the clamp to chase it.**
>
> ## **AND `SHOTREC` PAIRS A SHOT WITH ITS POSE AT LAST**, emitted inside the fire
> path so every value is from one instant by construction. **Host-side, no new
> symbols.** From the owner's suggestion, which named this gap correctly — **while
> naming five files and three functions that do not exist in this tree** (they are
> PD's; `168`'s rule, `210` §3).
>
> ## **BUILD TWICE. TWO RUNS: `-NoParallax` for the baseline, then default.**
> Three known angles (straight, 45 up, 90 right) + a NEAR and a FAR wall in each.
> **The FIRST shot of any run uses the fallback — by design (`185` B1).**

> # ►►►►►► 2026-08-25 SESSION CLOSE — WHERE IT ACTUALLY STANDS ◄◄◄◄◄◄
>
> ## **THE SEAM IS SOLVED AND LOCKED IN (`204`). THAT IS THE HEADLINE.**
> Five terms, none of them a tuning constant, all now HOST DEFAULTS:
> `R = Rhand` (no head term, `200`) · position = the RAW play-space hand (`200`) ·
> `gun_azimuth` write OFF (`201`) · `R` TRANSPOSED on the way out (`203`) ·
> `-HandAxisX -1 -HandAxisZ -1`, **which is the MODEL's `+Z` barrel, not a fudge**
> (`204` §2). **`158` §2 and `185` `T9` are closed. AN UNSET LAUNCH IS CORRECT.**
>
> ## **THE STANDING COMMAND**
> ```powershell
> .\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
>          -WorldUnitsPerMetre 25 -HandUnitsPerMetre 25 `
>          -ViewmodelScale 0.5 -GunOffX 0 -GunOffY 0 -GunOffZ 0 `
>          -AimFromHand -MuzzleOrigin -NoCrouch -HudDepth 0.2
> ```
> **THE TWO SCALE NUMBERS MUST BE EQUAL** (`205` §4 — their ratio is an
> arm-length multiplier, `[MEASURED]` at 2x when they were 50 and 100).
> **25 is UNJUDGED**: the world `[REPORTED]` small at 50, and 25 has not been
> worn. **Judge it against a GUARD.**
>
> ## ►► WHAT IS OPEN, IN PRIORITY ORDER ◄◄
> **1. `B1`/U-06 THE PARALLAX** — `193` §2 `[MEASURED]` the muzzle at
> **0.19-0.61 m** from the eye. Two rays, same direction, different origins,
> never meet. **PD's `vrComputeCrosshairParallax`, 25 lines, NO new symbols.**
> **THIS IS THE ONE THAT CHANGES WHERE BULLETS LAND, and it has been next since
> `193`.**
> **2. THE SCALE** — see above.
> **3. THE MENU CRASH** — `206` has a SYMBOLIC STACK (model animation path,
> `sub_GAME_7F06DEC0 +0xA1`); `207` has the cadence finding (**3 mash-runs clean
> at `-ViRate 60`, 2 crashes at 90**) and found BOTH quick fixes blocked.
> **`208`'s autolaunch is BUILT BUT INERT — wrong hook, `wfnf=2`. Move it to
> `viSetFovY` (`208` §5); the mechanism itself is sound and untested.**
> **4. `U-18`** the per-weapon muzzle (`T2` PASSED) · **5. `G-194`** ·
> **6. `noPose`/`U-21`/`U-22`/`U-23`/`U-24`.**
>
> ## ►► AND THE COMMIT IS TWENTY-FOUR DOCUMENTS OVERDUE. BOTH REPOS. ◄◄
> `commit-session.ps1`, on Windows, not through the bridge (`148` item 11).
>
> ## ►► DOCUMENTATION RULE, NEW AND MANDATORY FROM `210` — `209` ◄◄
> **AN `[INFERRED]` TAG WITHOUT ITS COUNTER-EXAMPLE SEARCH IS A DEFECT**, the
> same way an untiered claim has been since `183`. **`182` §3 always required
> "the counter-example search, and its result"; `209` `[MEASURED]` that
> NINETEEN `[INFERRED]` tags were written across `186`-`208` and NOT ONE stated a
> search.** The tag was honest and the obligation behind it was not discharged.
> **`182` §6 still applies: DO NOT retro-tag `186`-`208`.**

> # ►►►► 2026-08-25 — THE MENU CRASH HAS A SYMBOLIC STACK AT LAST. `206`. ◄◄◄◄
>
> ```
> mainproc -> bossEntry -> bossMainloop -> lvlRender -> propsTick -> chrTick
>   -> subcalcmatrices -> instcalcmatrices -> modelUpdateMatrices
>   -> process_02_position -> sub_GAME_7F06DEC0 +0xA1
>        access violation READING 0x284FFEE0005
> ```
> **THE CHARACTER/MODEL MATRIX PIPELINE, following a WILD pointer** (not near
> null — corrupt or stale, not a missing check). **`inLevel=0`: the front end,
> exactly as `[REPORTED]`. 90 fps, `LATE 1/91` — it was NOT struggling.**
>
> ## **`137` §4's SUSPECT IS FALSIFIED.** It named `musicTrack1Play`'s
> `alCSPGetState` spin — **that is a HANG; this is an ACCESS VIOLATION with no
> audio frame in the stack.** Retired at no cost, because it was tiered a suspect.
>
> ## **AND NO GoldenEyeVR FRAME IS IN THE STACK** — the aim ray was all zeroes and
> the hand path was provably idle. **The obvious VR suspects are excluded for
> THIS crash.** `[ASSUMED]` whether it is ours AT ALL: **`137` §4's stock test
> (`-NoXr`, no `-ViRate`) has never been run in a hundred documents, and a
> symbolic stack now makes both outcomes actionable.**
>
> ## ►► HOW TO READ ANY FUTURE CRASH — THE HANDLER WAS ALREADY THERE ◄◄
> **`[gevr-crash]` offsets resolve against `build/Release/GoldenRecomp.map` at
> preferred base `0x140000000`.** No new instrumentation was ever needed — only
> the read. **COPY THE LOG *AND* THE MAP ASIDE TOGETHER**: the map is rebuilt with
> the binary, and a stack without its map is unreadable.
> **Kept: `gevr-keep-MENUCRASH.log` + `.map`.**

> # ►►►►►► 2026-08-25 — THE SEAM IS SOLVED AND LOCKED IN. `204`. ◄◄◄◄◄◄
>
> ## `[REPORTED]` ***"We need to lock these coordinates in because this is great.
> ## We can totally move on to getting the aiming to actually work."***
>
> ## **FIVE TERMS, NOT ONE OF THEM A TUNING CONSTANT:**
> **1.** `R = Rhand` — **no head term** (`200`: 0.14 deg vs 4.2-4.4).
> **2.** position = **the RAW play-space hand** (`200` §2 — it collapsed `194`+`197`).
> **3.** `gun_azimuth` write **OFF** (`201` — `163`'s second driver).
> **4.** `R` **TRANSPOSED** on the way out (`203`: COLUMN 0.00 deg, ROW 54.60 —
> **`158` §2 closed after forty-five documents**).
> **5.** `-HandAxisX -1 -HandAxisZ -1` — **AND IT IS THE MODEL, NOT A FUDGE:**
> `MUZZLENODE Switches[3]=(0, 56.7, 350.3)` says **the barrel points along `+Z`**,
> so a 180 deg turn about Y is owed. **`155`'s numbers were right for a reason
> nobody had found — they describe the ART, not the frame.**
>
> ## **ALL FIVE ARE NOW HOST DEFAULTS. AN UNSET LAUNCH IS THE CORRECT ONE.**
> ```powershell
> .\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
>          -WorldUnitsPerMetre 100 -HandUnitsPerMetre 100 `
>          -ViewmodelScale 0.5 -GunOffY 8 -GunOffZ -2 `
>          -AimFromHand -MuzzleOrigin -NoCrouch -HudDepth 0.2
> ```
> **EVERY OFF SWITCH SURVIVES** (`-SeamFrame 0|1`, `-NoSeamT`, `-GunAzimuth`,
> `-HandAxisX 1 -HandAxisZ 1`, `-NoHandPosT`, `-NoRoomOrigin`, `-NoAimCone`).
>
> ## ►►►► NEXT IS THE AIMING, AND IT IS `B1`/U-06 — THE PARALLAX. ◄◄◄◄
> **`193` §2 `[MEASURED]` the muzzle at `0.19`-`0.61 m` from the eye.** Two rays,
> same direction, different origins, never meet. **PD's
> `vrComputeCrosshairParallax`, 25 lines, NO new symbols, fed from
> `item_related`.** **This is the next thing that changes what SHOOTING feels
> like.** Then `G-194`, then `U-18` (per-weapon muzzle, `T2` PASSED).
>
> ## ►► AND THE COMMIT IS NINETEEN DOCUMENTS OVERDUE. BOTH REPOS. ◄◄

> # ►►►► 2026-08-25 — THE GAME READS THE **ROW**. `158` §2 IS CLOSED. `203`. ◄◄◄◄
>
> ## **`[MEASURED]`, 734 paired samples, against the raw controller forward:**
> ## **COLUMN `0.00` deg · ROW `54.60` deg.**
> The COLUMN *is* the controller's forward by construction — **and the drawn gun
> behaves like the ROW.** Bucketed by true yaw, the ROW is **mirrored in yaw
> throughout** and **diverges in pitch by up to 89 deg on the LEFT ONLY**:
> `true yaw -80, true pitch +37.5 -> ROW pitch -51.8`, while the right half stays
> close. **That is the wearer's report, in numbers.**
>
> ## **AND IT IS NOT A REFLECTION — IT IS THE INVERSE ROTATION**, which differs
> from its own mirror by more and more as you turn from the identity. **`202` §2
> closed the sign sweep because a conjugation cannot be asymmetric; the shape of
> the asymmetry CONFIRMS that reasoning rather than merely fitting it.**
>
> ## **`158` §2 PUBLISHED BOTH AXES AND SAID "ONE RUN PICKS". IT SAT OPEN FOR
> ## FORTY-FIVE DOCUMENTS. ONE RUN PICKED.**
> **FIX: transpose `R` on the way out** — its ROW becomes our COLUMN, and roll
> comes right with it because the transpose of the inverse is the rotation.
> **`-NoSeamT` reverts. ONE BUILD, host-side.**
>
> ## `G-203`: **aim top-RIGHT -> points top-RIGHT; sweep LEFT -> no lift.**
> **No regression on the three that passed:** wrist roll, head-turn independence,
> walking stability. **Then the POSE knobs — knob-only, and only after.**
>
> ## ►► METHOD, FOR THE RECORD ◄◄
> **`200` solved the composition from the INPUT side; `203` solved the consuming
> frame from the OUTPUT side.** Inputs alone were trustworthy and blind — the
> fault was in what the game CONSUMED. **The pair is what closed it.**

> # ►►►► 2026-08-25 — `G-201` PASSED. THE SIGN SWEEP IS CLOSED. `202`. ◄◄◄◄
>
> ## `[REPORTED]` ***"When you turn your head, the gun does not move."***
> **THE HEAD NO LONGER RE-AIMS THE GUN.** `163`'s `field_FFC` write was the yaw.
> **AND *"the crosshair didn't affect the direction of the gun"* IS `201`
> WORKING** — the first build where the two are independent. **Do not file it as
> a regression.** *"Going through geometry"* is `169` **U-23**, a viewmodel with
> no collision — filed, not chased.
>
> ## ►►►► THE REMAINING FAULT IS ASYMMETRIC, AND THAT IS THE FINDING ◄◄◄◄
> **Right side correct, LEFT side lifts and inverts.** `-HandAxis*` is a
> conjugation and **every conjugation is SYMMETRIC about the identity — no sign
> and no mirror can produce an asymmetry.** `[MEASURED]` the wrist covered the
> full `-179.6` to `+179.7` deg of yaw, so it is not a range artefact either.
> **THE SIGN SWEEP IS CLOSED WITHOUT RUNNING THE REST OF IT.**
> **HONEST LIMIT `[MEASURED]`: pitch hit `-83` deg and yaw/pitch correlated at
> `r = -0.34` — the wearer's own ARM couples the axes, so the log cannot say
> whether the gun coupled them or he did.**
>
> ## **SO THE RECORDER GAINS AN OUTPUT SIDE — `POSEOUT`.** `199` logs INPUTS ONLY
> by design, which is what made `200` trustworthy and is exactly why it is blind
> here: **the fault is in how the GAME CONSUMES the matrix.** The new line carries
> `R`'s third ROW and COLUMN (**`158` §2's ambiguity, live again, settled the same
> way**) and `g_geVrLastRoot`, **the placement the GAME itself produced** —
> without which our contribution cannot be separated from the game's (`85`).
> **ONE BUILD, host-side, no new symbols. Then sweep again and send the log.**

> # ►►►► 2026-08-25 — WALKING IS STABLE. ROLL FIXED. THE YAW IS A SECOND DRIVER. `201`. ◄◄◄◄
>
> ## **`[REPORTED]` *"when I walked forward and backwards... it didn't move or
> ## adjust position."* THE POSITION IS SOLVED** — `200`'s raw play-space hand
> holds under walking. Four documents (`194`-`197`) tried to fix this; the answer
> was that the head term should never have been there at all.
>
> ## **AND THE ROLL WAS THE LEGACY AXIS SIGNS, PREDICTED BEFORE THE RUN.**
> `diag(-1,1,-1)` mirrors X and Z and spares Y — **inverting ROLL and YAW and not
> PITCH, exactly the two reported and exactly the one not.**
> **NEW DEFAULTS: `-HandAxisX 1 -HandAxisZ 1`.** `155`'s `-1 -1` were measured
> against a composition that no longer exists.
>
> ## ►►►► THE REMAINING YAW IS NOT THE SEAM. `[MEASURED]` R DRIFTS 0.14 DEG. ◄◄◄◄
> **`[READ]` the gun model has TWO drivers.** `163`'s `gun_azimuth` write feeds
> `field_FFC` -> `7F067AB4` -> `hands[].field_A38/A3C/A40`, **and it is written
> from `Rhead^T * fwdWorld` — a HEAD-RELATIVE term that changes when you turn
> your head with the hand still.** **Correct for a CROSSHAIR, wrong for a GUN. One
> number was driving both.**
> **`163` was RIGHT when it added this** — the seam was cosmetic then (`157`
> §6.1). **`200` removed the reason; the write outlived it.**
> **NOW GATED, DEFAULT OFF. `-GunAzimuth` restores it. ONE NEW SYMBOL -> BUILD
> TWICE (`136`).**
> **THE CROSSHAIR AND THE BULLET ARE UNTOUCHED, both `[READ]`:** the crosshair is
> the FIRST integrator; `164`'s bullet takes the barrel ray and has never read
> `field_FFC`.
>
> ## `G-201`: **gun STILL, head turning — IT MUST NOT RE-AIM.** The crosshair
> WILL still slide across the screen and **that is correct** (`201` §2).

> # ►►►► 2026-08-25 — SOLVED. THERE IS NO HEAD TERM. `R = Rhand`. `200`. ◄◄◄◄
>
> ## **`[MEASURED]`, 744 recorded poses, 83 head-only transitions:**
> | composition | drift per head-only step |
> |---|---|
> | **`Rhand` — no head term** | **0.14 deg** |
> | `Rhead * Rhand^T` (LEGACY) | 4.35 |
> | `Rhead^T * Rhand` (`173`, `T9`) | 4.40 |
> | *the other five* | 4.18 - 4.41 |
>
> **THE HEAD MOVED 4.34 DEG PER STEP. EVERY FORM WITH A HEAD TERM DRIFTS BY
> EXACTLY THE HEAD'S OWN MOTION — the head rotation is being applied TWICE**,
> because `194` established the view matrix already applies it. **`173` and the
> legacy form are two wrong ways to spend a rotation that was already spent**,
> which is why swapping between them moved the symptom and never removed it.
> **`Rhand` over `Rhand^T` needs no run: the AIM uses `-Rhand` col 2 and `193` §1
> measured that aim correct across 55 shots.**
>
> ## **AND THE POSITION TAKES THE SAME ANSWER — IT COLLAPSES `194` + `197`:**
> `(hand - head) + (head - gameCamera)` **IS** `hand`. **The raw play-space hand
> position. The room term is SUBSUMED, not dropped — do NOT add it twice or the
> gun runs away at double walking speed.**
>
> ## **`-SeamFrame 2` IS THE NEW DEFAULT.** `1` = `173`, `0` = legacy. ONE BUILD.
> ## `G-200`, NO SHOOTING: **head turns/tilts — the gun MUST NOT re-aim. Wrist
> ## twists — it rolls IN PLACE. Walk — it comes with you, at YOUR speed.**
> **EXPECTED, NOT A FAILURE: `-HandAxis*` and `-GunOff*` were tuned against the
> legacy frame** (`185` `T9`). **JUDGE MOTION FIRST, POSE SECOND** — a gun that
> tracks right but sits at a wrong angle is those knobs, not this frame.
>
> ## ►► THE METHOD NOTE, AND IT IS THE POINT ◄◄
> **Two wear tests answered two of eight candidates and could only ever say "no".
> The recorder answered all eight at once, offline, thirty to one.** The owner
> asked for it; `48` and `158` §2 already said to. **The project had the rule and
> did not apply it here until asked.** Log kept: `gevr-keep-POSEREC.log`.

> # ►►►► 2026-08-25 — `T9` FAILED TOO. BUILD, THEN RECORD POSES. `199`. ◄◄◄◄
>
> ## **BOTH COMPOSITIONS ARE FALSIFIED IN THE HEADSET.** `173`'s
> `R = Rhead^T * Rhand` is `[REPORTED]` worse, the legacy `Rhead * Rhand^T` was
> already wrong (`198`). **THERE ARE EIGHT CANDIDATES AND WE HAVE SPENT A WEAR
> TEST ON EACH OF TWO.** Six more sessions of "no" is not a plan.
>
> ## ►►►► SO RECORD THE RAW POSES AND SOLVE IT OFFLINE. THE OWNER ASKED FOR
> ## EXACTLY THIS INSTRUMENT AND HE IS RIGHT. ◄◄◄◄
> ```
> [gevr] POSEREC hq=(x y z w) hp=(x y z)  gq=(x y z w) gp=(x y z)
> ```
> **HEAD pose and GUN-HAND pose, RAW, logged BEFORE anything transforms them —
> which is the whole design: everything else in the file is derivable from those
> twelve numbers, and a recorder that logged a DERIVED value could be wrong in
> the same way the code is wrong.** 9 Hz. `-NoPoseRec` off. **`158` §2 solved this
> shape of problem the same way: publish, then let one run pick.**
>
> ## **THE CALIBRATION SEQUENCE — ONE MOTION AT A TIME, PAUSE BETWEEN.**
> **1** stand still 5 s · **2** YAW head L/R, gun still · **3** ROLL head L/R ·
> **4** PITCH head up/down · **5** TWIST wrist CCW/CW, head still · **6** WALK
> forward/back/left/right. **Say each mark out loud. Nothing to aim, nothing to
> shoot. DROP `-SeamCompose 1` for this run.** `199` §3.
> **Steps 2-4 move the head with the hand FIXED — any composition that varies
> there is falsified. Step 5 must be a pure roll in place. Only one of the eight
> satisfies both, and both are checkable on a laptop.**
>
> ## ►► AND `166` §3's PRE-REGISTERED FINDING HAS FIRED — THE SCALE ◄◄
> Still a toy model at `100` with `167` running. **`[MEASURED]` the stereo at 100
> is geometrically EXACT** (eye offset `3.175` u = 63.5 mm IPD; Bond's eye 175 u =
> 1.75 m; ratio `0.0363` = reality's `0.0363`), **so `159`'s "too high" is NOT the
> answer and lowering it only makes Bond a giant.** **The suspect is `[READ]`
> `fovy=106` against the headset's true `88` — 106 degrees squeezed into 88 makes
> everything small, far and low. THAT IS THE NEXT READ.** `199` §4.

> # ►►►► 2026-08-25 — `G-197` PARTIAL. THE REST IS `T9`. NO BUILD NEEDED. `198`. ◄◄◄◄
>
> ## `[REPORTED]`, ONE SENTENCE CARRYING BOTH HALVES:
> ***"I tilt my head to the left, the gun will TILT TO THE RIGHT but COME TO THE
> LEFT WITH ME."***
> **POSITION: FOLLOWS — `197`'s transpose CONFIRMED by the wearer who reported the
> fault. ORIENTATION: STILL INVERTED — and `197` never claimed it** (§3: *"where
> the gun IS, not where it points"*).
>
> ## ►►►► EVERY REMAINING SYMPTOM IS ROTATIONAL, AND `T9` IS BUILT. ◄◄◄◄
> *"it's TURNING and going in that direction"* — a rotated lever sweeps its muzzle
> off-screen while the grip barely moves. **And twisting the hand sends the gun
> *"all the way to the ground before it flips... like a big letter C"* — A ROLL IN
> THE WRONG FRAME SWEEPS AN ARC; IN THE RIGHT FRAME IT SPINS IN PLACE.**
> **`173`: `R = Rhead * Rhand^T` is wrong, `R = Rhead^T * Rhand` is right — THE
> SAME HANDEDNESS `197` JUST FIXED IN THE VARIABLE NEXT DOOR.**
> **`-SeamCompose 1`. NO BUILD. Its own launch.**
>
> ## **EXPECTED IF `T9` PASSES:** `-HandAxis*` and `-GunOff*` were tuned against
> the old composition. **Re-check AFTER, never during** (`185` `T9`).
>
> ## RESIDUALS RECORDED, NOT EXPLAINED: the small upward drift when walking the
> line (*"on some sort of warp"* — much smaller than before), and the SCALE
> question (*"my hand looks five feet off the ground"*, *"my face is on the
> floor"*). **Do not chase either until `T9` is worn** — everything hanging off a
> wrong orientation inherits its error. `198` §3.

> # ►►►► 2026-08-25 — THE POSITION IS TRANSPOSED. THE AIM NEVER WAS. `197`. ◄◄◄◄
>
> ## **TEN LINES APART, IN ONE FUNCTION, `[READ]`:**
> ```
> position (docs\156):   Rhead[i][0..2] . d    = Rhead   * d     <- WRONG
> aim ray  (docs\158):   Rhead[0..2][i] . fwd  = Rhead^T * fwd   <- RIGHT
> ```
> `ge_vr_quat_to_basis` maps LOCAL -> WORLD, so a WORLD vector expressed in the
> head's frame needs the TRANSPOSE. **The aim does it. The position never has.**
>
> ## **INVISIBLE FACING FORWARD** (`Rhead` is then identity) **— IT ONLY APPEARS
> ## WHEN THE HEAD TURNS**, which is every head-turn report ever filed here:
> `173` *"the gun will change directions in my hand automatically"* · `192` *"it
> wants to maneuver the hand"* · `197` ***"turn right and the gun disappears over
> my LEFT shoulder; tilt right and it leans LEFT; walk forward and it sinks to
> the floor."*** **Yaw AND roll inverted plus axis leakage = a wrong-handed
> BASIS, not a sign.**
>
> ## ►► `173` DIAGNOSED THIS EXACT THING — AND ONLY FIXED THE ROTATION. ◄◄
> *"`R = Rhead * Rhand^T` is wrong... AND THE AIM PATH HAS ALWAYS USED `Rhead^T`."*
> **It shipped `-SeamCompose` and never looked at the POSITION beside it.**
> **`T9` IS STILL SEPARATE AND STILL OWED — this is the other half.**
>
> ## **FIX: `handPos` takes `Rhead^T`. `194`'s room term takes the SAME transpose
> ## and the SAME knob** (two terms that are ADDED must live in one frame).
> **`-NoHandPosT` reverts. ONE BUILD, host-side.**
> **`G-197`, NO SHOOTING: turn — the gun stays in front of you. Tilt — it stays
> put. Walk — it comes with you.** Then `G-196`, then `G-194`.
>
> ## ►► AND THE STEREO BANNER WAS A FALSE ALARM. THE WEARER CALLED IT. ◄◄
> `vr.ps1`'s verdict runs against the EXISTING log AT LAUNCH — **it describes the
> PREVIOUS run.** This one: `eye0=91 eye1=91` on 139 samples, `stereo=90 | OK`.
> **AND HIS SECOND POINT STANDS: a yaw/roll inversion is MONOCULAR and needs no
> stereo to be valid.** `179` voids DEPTH and FUSION judgements, not every
> observation made in a headset. **Do not reach for a void banner to set aside a
> report that reproduces in every build.**

> # ►►►► 2026-08-25 — THE GUN MOVES OPPOSITE TO YOU. `195` §3 RETRACTED. `196`. ◄◄◄◄
>
> ## `[REPORTED]` ***"If I go forward, the gun starts to come towards me. If I walk
> ## backwards, the gun goes forward."*** — **IN BOTH ARMS OF THE KNOB.**
> **`195` §3 said "THE PICTURE WAS ALREADY CORRECT". IT WAS NOT.** The drawn gun
> sits at `gameCamera + (hand - head)` while your eye sits at
> `gameCamera + roomOffset` — **so relative to your eye the gun is at
> `-roomOffset` and moves opposite to you, by exactly how far you moved.**
> **AND "no matter which version" EXONERATES THE KNOB:** `195`'s term touched only
> the BULLET path, so it could not have changed the picture either way.
>
> ## **THE FIX: the term moves INTO `handPos`, above every consumer, and is
> ## REMOVED from `muzzle_origin`.** Both would double-count — and that failure
> would have read as `195` §2's "sign inverted" branch and sent the next session
> hunting a sign that was not wrong. **ONE TERM, ONE PLACE. ONE BUILD.**
>
> ## **`G-196` FIRST, AND IT NEEDS NO SHOOTING: hold the gun still and WALK —
> ## forward, back, left, right. THE GUN MUST STAY WITH YOUR HAND.**
> Then `-NoRoomOrigin` reproduces the inversion on purpose. **THEN `G-194`.**
>
> ## ►► THE RULE THAT CAME OUT OF IT — NEW, AND IT COST ONE RUN ◄◄
> **When one published value feeds both what is DRAWN and what is SIMULATED, a
> correction belongs ABOVE the split, or it will be right in one and wrong in the
> other.** `157` §6.1 is the same lesson from the other side. **And the fault was
> found because the gate made the wearer MOVE** — a gate that puts him in an
> unusual posture finds what standing still never will.
>
> ## **AND THE ARM: the anchor is the bug, not the absence of an arm.** An IK arm
> (`169` U-11) hung off the same anchor would swing the wrong way too. **The left
> hand is a wiring job — `hand_override` already takes `hand` 0/1 and `structs.h`
> carries `hands[2]` — once the first is anchored right.** `196` §5.

> # ►►►► 2026-08-25 — THE ROOM ORIGIN IS BUILT. BUILD ONCE, THEN `G-194`. `195`. ◄◄◄◄
>
> ## **`origin = (hand - head) + (head - gameCamera)`.**
> **HOST-SIDE ONLY — no patch code, NO new `RECOMP_PATCH` symbols, so `136` does
> NOT apply and ONE BUILD IS ENOUGH.** No `115` header. Zero game symbols.
> **`-NoRoomOrigin` reverts. An unset roomscale session is byte-identical.**
>
> ## `G-194` — **CORRECTED IN `195` §2. THE FIRST WORDING WAS GEOMETRICALLY WRONG**
> ~~"step sideways without moving the gun; the impacts must agree"~~ — **a fixed
> direction fired from a translated origin LANDS TRANSLATED. That gate would have
> failed a working fix.** Second such gate this week (`189` §3): **check a gate
> against the geometry before you check it against the build.**
> **THE TEST: hit a MARK from the centre. Step as far sideways as you can, RE-AIM
> AT THE SAME MARK, fire. IT MUST STILL HIT.** `-NoRoomOrigin` is the before and
> should MISS by roughly your displacement. **JUDGE THE DIFFERENCE BETWEEN THE
> ARMS** — a miss in BOTH is the muzzle parallax and belongs to `B1`.
> **Sign check: twice your displacement = the term is inverted.**
>
> ## ►► AND THE DRAWN GUN MUST NOT MOVE. A VIEWMODEL THAT SLIDES IS A BUG. ◄◄
> The term is added at `muzzle_origin` ONLY, **not** into `g_geVrLastHandPos` —
> which is also the gun's DRAWING anchor (`157`). **The picture was already
> correct; only the engine's bullet frame was missing the translation.** Folding
> it into the shared global would have slid the viewmodel and read exactly like a
> broken grip — mis-diagnosed twice already (`154` §1, `157` §6.1). `195` §3.
>
> ## THEN: **`B1`/U-06 parallax** (judgeable only after `G-194` passes) ·
> **`U-18`** · **`T9`** · **`noPose`/`U-21`/`U-22`**.

> # ►►►► 2026-08-25 — YOUR BODY MOVES THE VIEW AND NOT THE BULLET. `194`. ◄◄◄◄
>
> ## **`193` §4's READ IS DONE, AND IT HAS AN ANSWER.**
> **`[READ]` the roomscale head translation IS written into the eye view matrix**
> (`ge_vr_head_transform`: `view.position * worldUnitsPerMetre` -> `m[3][*]`), and
> **`[READ]` it is composed onto the game's view matrix AT RENDER TIME**
> (`rt64_projection_processor.cpp:159`) — **so the ENGINE'S CAMERA NEVER LEARNS
> ABOUT IT.** Meanwhile **`[READ]` the muzzle origin is `hand MINUS head`**
> (`:1853`), deliberately invariant to where you stand.
>
> ## ►►►► **SO HOW FAR YOU HAVE STEPPED IS A PURE ERROR IN THE BULLET'S ORIGIN.**
> Centred, it is zero — *"the center shots remain ok."* **Half a metre to the side
> and the shot leaves from half a metre from where you are looking.** It is the
> only mechanism found that is switched on by MOVING YOUR BODY.
> **AND IT STACKS ON `193` §2's ALREADY-MEASURED 0.19-0.61 m MUZZLE OFFSET.**
>
> ## **THE FIX IS ONE ADDITION, HOST-SIDE, NO NEW SYMBOLS.**
> `origin = (hand - head) + (head - gameCamera)`, and **the missing term is
> already computed** in `ge_vr_head_transform`'s `m[3][*]`. **TAKE IT FROM THERE,
> DO NOT RE-DERIVE IT** — `25`'s failure was two sources disagreeing.
> **KNOB `-NoRoomOrigin`. GATE `G-194`: shoot a mark, step half a metre sideways
> WITHOUT MOVING THE GUN, shoot again. The impacts must agree.**
>
> ## ►► **IT LANDS BEFORE `B1`, NOT AFTER.** ◄◄
> `B1` converges the crosshair on the last impact DISTANCE. **Against an origin
> that moves whenever the wearer shifts his weight, its gate cannot be judged.**
> Same reason `A1` came before `A3`.
>
> ## **THE THREE ORIGIN FAULTS, ONE STORY:** the bullet leaves from the wrong place
> **relative to your head** (`193` §2 -> `B1`), **for the weapon in your hand**
> (`193` §3 -> `U-18`), **and in the room** (`194`). **THE DIRECTION WAS NEVER THE
> PROBLEM** — measured across 55 shots, `193` §1.

> # ►►►► 2026-08-25 — THE PROJECTION IS INNOCENT. IT IS THE ORIGIN. `193`. ◄◄◄◄
>
> ## **`[MEASURED]`, 55 SHOTS, NO NEW RUN: the crosshair and the bullet AGREE.**
> `tan(dir)/ndc` median **X 1.248** against the render half-tangent **1.253**, and
> **Y 0.953** against **0.966** — **and the off-centre figures do not diverge from
> the centre ones.** **`167` and `A1` are doing exactly what they claim. STOP
> LOOKING AT THE FRUSTUM.** The scatter is the game's own random spread
> (`ge_vr_aim.c:890`), which is why MEDIANS are quoted.
>
> ## ►►►► **THE BULLET STARTS UP TO 0.4 m FROM YOUR EYE.** ◄◄◄◄
> `[MEASURED]` `muzzle=` over the same shots: **X `+0.10` to `-0.31` m, Y to
> `-0.27` m, Z `0.19` to `0.61` m.** **The crosshair is drawn from the EYE; the
> bullet leaves the MUZZLE; same direction, different origin — two parallel rays
> NEVER MEET.** 0.3 m subtends **17 degrees at 1 m and under 1 degree at 20 m**,
> which is *"fine in a small central region, sprays at the sides"* from inside.
> **THAT IS `T7`'s "MISS SHRINKS" BRANCH, ANSWERED FROM THE LOG. `B1`/U-06 IS THE
> CURE AND IS NOW THE TOP OF THE LIST.**
> **`192` §1 IS THE SAME STORY:** a crosshair that had to be pulled to `0.2 m` to
> fuse, beside a bullet that starts `0.3 m` away.
>
> ## **AND `T2` PASSED ON THE WAY PAST — `U-18` PROCEEDS.**
> `[MEASURED]` `MUZZLENODE Switches[3]`: pistol `(0,56.7,350.3)` on 696 samples,
> **a second weapon `(0,23.3,705.7)` on 40 — the muzzle is TWICE as far down the
> barrel.** Our origin is a FIXED `-GunOffY 8 -GunOffZ -2`, **PD's PISTOL
> default** — **which is why the second gun sprayed.**
>
> ## ►► NOT EXPLAINED, AND DELIBERATELY NOT GUESSED AT ◄◄
> `[REPORTED]` *"if I am on the side off center in VR it shoots off to the side"* —
> **a dependence on head POSITION, which nothing above accounts for.**
> **READ FIRST, BEFORE ANY MORE AIM WORK: does the roomscale head TRANSLATION
> reach the game's camera frame, or only the rendered view?** `193` §4.

> # ►►►► 2026-08-25 — `A3` CLOSED AT `-HudDepth 0.2`. GROUP `A` IS COMPLETE. `192`. ◄◄◄◄
>
> ## **`[REPORTED]` *"0.2 is the one that actually worked."* NO BUILD WAS NEEDED.**
> `191`'s `[INFERRED]` confirmed: the HUD sat at INFINITY while the wearer verges
> nearer. **`A1` DONE · `A2` CLOSED · `A3` CLOSED — `185` GROUP `A` IS FINISHED.**
> **`[MEASURED]` CAVEAT: `0.2 m` is NEARER THAN THE GUN** (`0.128` NDC of extra
> convergence, on the scale of the canting term itself). **It is a MEASUREMENT of
> the residual, not a preference — `B1` should replace it with a computed depth.**
>
> ## ►►►► THE HEAD-TURN REPORT IS `T9`, AND `T9` IS ALREADY BUILT. ◄◄◄◄
> `[REPORTED]` *"when I turn my head left and right... it seems to kinda wanna
> maneuver the hand."* **THE SAME WEARER SAID THE SAME THING IN `173`.** Two
> independent reports of one symptom. **`R = Rhead * Rhand^T` is wrong; correct is
> `Rhead^T * Rhand`, and THE AIM HAS ALWAYS USED `Rhead^T`.**
> **`-SeamCompose 1`. BUILT, KNOB-GATED, NEVER WORN. ITS OWN LAUNCH, never folded
> into an aim run** — if it passes, `-HandAxis*` and `-GunOff*` were tuned against
> a reference that no longer exists (`185` `T9`).
> **AND IT IS COSMETIC (`157` §6.1: every `field_8EC` reader is a DRAWING site) —
> WHICH IS WHY IT MATTERS: you aim by looking at the gun.**
>
> ## STILL OWED, AND STILL THE OWNER'S PRIORITY: **`T7`. IT HAS NOT BEEN RUN.**
> Same command with `-HudDepth 0.2`, nothing else changed. **Near wall, then far
> wall. Miss SHRINKS -> parallax (`B1`). Miss HOLDS -> constant angular error.**
>
> ## AND ONE REPORT NOT YET DIAGNOSED — DO NOT GUESS AT IT
> `[REPORTED]` *"the perspective is still off, which causes the gun to go beyond
> the distance of the aimer."* **Candidates in order: `B1` (the principled cure),
> then `166` §3's unresolved toy-model question via THE GUARD TEST (`159`), and
> `-ViewmodelScale`/`-GunOffZ` LAST and only with a number.** `192` §3.

> # ►►►► 2026-08-25 — NEXT SESSION NEEDS **NO BUILD**. `-HudDepth`, THEN `T7`. `191`. ◄◄◄◄
>
> ## **`185` `A3`'s "32% TOO MUCH" IS RETRACTED — THE SHIFT WAS ALREADY RIGHT.**
> **`[MEASURED]`: `0.1867` IS `(tanR+tanL)/(tanR-tanL)` for the LIVE tangents
> `-1.4869, 1.0190`, to four decimals.** The `-0.1411` came from the
> `[gevr] tangents` line — **`loggedFull`, printed ONCE at startup, 29 lines
> BEFORE the headset reported any FOV.** Constant table, not render.
> **FIFTH TIME (`160`, `163`, `171` §3, `180`, this) AND THE SECOND IN TWO DAYS**
> (`189` §2 was the same shape). **`182` caught it because `A3` carried
> `[INFERRED]` — building it would have dialled a CORRECT term down by a third
> and then tuned around the error, which is `-AimGain`'s whole history.**
>
> ## ►► SO WHY ARE THE TWO CROSSES STILL A WIDTH APART? `[INFERRED]`: BECAUSE THE
> ## HUD IS AT INFINITY AND YOUR EYES ARE NOT. ◄◄
> The canting term places the HUD at infinity BY CONSTRUCTION — parallel rays.
> **Anything at infinity is physically double when you are verged on a gun half a
> metre away.** `173` fixed DIVERGENT and correctly landed on PARALLEL; **parallel
> is still not fused if you are looking at your gun.**
>
> ## **AND THE TEST IS A KNOB THAT ALREADY EXISTS — `-HudDepth`, NO BUILD.**
> **`2.0 -> 1.0 -> 0.5`. HALVE, NEVER NUDGE (`159`).** `G-A3` unchanged: one fused
> cross, same world place with either eye closed. **If a depth fuses it, `A3`
> closes as a DEFAULT CHANGE and the value is the finding — record it, do not
> leave it as a knob** (`174`).
>
> ## ►►►► THEN `T7`/`B2` IN THE SAME SESSION — THE OWNER'S OWN PRIORITY. ◄◄◄◄
> **Shoot a wall at arm's length, then the same spot across the room. Miss SHRINKS
> -> muzzle parallax (`B1` is the known cure). Miss HOLDS -> a constant angular
> error.** `189` §2 removed its other blocker. **`noPose`, `U-21`, `U-22` all wait
> for the next BUILD — this session is worth more with none.**

> # ►►►► 2026-08-25 — ***"THE TARGET FOLLOWED MY HAND DIRECTION."*** `G-A1` PASSED. `190`. ◄◄◄◄
>
> ## **THE QUADRANT IS GONE.** `184`'s `[REPORTED]` *"nothing is related to where
> you're pointing it... only focusing on the general quadrant"* was `[INFERRED]`
> to a mechanism, `[MEASURED]` by `187`, fixed by `188`, and is now `[REPORTED]`
> cured **by the man who first named it.** Four documents, the whole `182` chain.
>
> ## **AND THE AXES SATURATE INDEPENDENTLY** — `[REPORTED]`, on a LEVEL sweep the
> crosshair rests at the MIDDLE of the right edge. **`188` §1 called the per-axis
> form out against a radial one specifically because a radial clamp "would look
> like the very fault this removes". Confirmed in the headset.**
>
> ## ►►►► SO `185` GROUP `A`'s BLOCK IS LIFTED. **`A3` IS NEXT.** ◄◄◄◄
> *"Nothing else in aim is judgeable until this is done."* **It is done.** `A3`'s
> own blocker — *"cannot be judged while the crosshair leaves the frame"* — **is
> met, and `B2` is unblocked too** (`189` §2 removed its other dependency).
> **`A3`: derive the cyclopean term, do NOT dial it.** Applied `0.1867` vs
> `[INFERRED]` `-0.1411`, about 32% too much; the wearer sees the two crosses one
> crosshair width apart.
>
> ## THE TWO THINGS SEEN BESIDE IT — BOTH EXPLAINED, NEITHER A REGRESSION
> **1. "PARTIALLY OFF AT THE CORNER" IS THE STOCK `[3, w-4]` CLAMP.** `nx=1` maps
> to `320` on a 320-wide screen, the clamp brings it to `316`, **so the sight's
> CENTRE rests 4 px inside the frame and the glyph hangs half off.**
> **`187`'s own log printed `crosshair_angle=(316,21)` before anyone said it.**
> `169` **U-21** — and **do NOT inset the cone to fix it: that moves the BULLET
> and undoes U-16.** Change our own clamp.
> **2. THE RESET-TO-CENTRE ON A LOST CONTROLLER IS THE REFUSAL PATH DECAYING**
> (`ge_vr_aim.c:324` + `:285`), exactly as `160` §2 recorded. **A lost pose means
> "I don't know where the gun is"; gliding to centre ASSERTS it is level and
> forward. HOLD IT INSTEAD** — `169` **U-22**.
> **AND `A1-VERIFY` CANNOT SEE THOSE FRAMES AT ALL** — `aimed` and `refused` are
> both inside the pose branch, so a dropout is counted in neither. **Add `noPose`
> before anything else reads that line.** `190` §3.

> # ►►►► 2026-08-25 — `A2` IS CLOSED. `A1` ENGAGED. `G-A1` AWAITS THE WEARER. `189`. ◄◄◄◄
>
> ## **`A2` WAS NEVER A FAULT. `[MEASURED]` `origin=(0,10)`.**
> `c_screentop` is the `(240-220)/2` letterbox; `crosshair_angle` adds it after
> the `h/2` and the aim inversion subtracts it. **Rest at `(160,120)` IS dead
> centre.** The ten-pixel drop was a correct measurement against the wrong
> baseline — **the third time (`163` §7, `171` §2). PRINT THE FRAME BEFORE
> HUNTING INSIDE IT.** **And `185` `B2`'s 10 px confound does not exist**, so `B2`
> now waits only on `A1` and `A3`.
>
> ## **THE CONE CLAMP ENGAGED ON EVERY BAND FRAME** — `CONE=2455 = BAND=2455`,
> `coneOff=0`, `noFrus=0`. **`188` §2's "the fix is inert" branch is excluded.**
> **BUT `CONE == BAND` IS AN IDENTITY, NOT A RESULT** — the two count the same
> predicate. **It proves the code RAN. Whether aiming is BETTER is `G-A1`, in the
> headset, and the log cannot substitute for it.** `189` §1.
>
> ## ►► AND A GATE I WROTE WAS WRONG: `SAT` CANNOT FALL. ◄◄
> `188` re-pointed the counters at the PRE-cone values so `BAND` would survive the
> fix, **and `SAT` came with it — both are BEFORE-figures now.** `SAT=1447` is
> correct behaviour, not a failure. **The log-side gate is `CONE == BAND` with
> `coneOff=0`.** `vr.ps1` and `188` are corrected. `189` §3.
>
> ## **NEXT: the wearer's `G-A1`. Then `A3`, whose blocker is now met.**
>
> ## ►► AND WHERE THE TWO SOURCE TREES ACTUALLY ARE. WRITE IT DOWN ONCE. ◄◄
> **Every doc in this project cites "the game tree" and `gunfire.c:633` and none
> of them says WHERE.** It is on this disk and the line numbers resolve exactly:
>
> | | |
> |---|---|
> | **GoldenEye decomp** | `GoldenEye64Recomp\lib\ge\src\game\` — 242 files |
> | **Perfect Dark (prior art, MIT `67ea20c`)** | `GoldenEyeVR\local-only\prior-art\perfect_dark_VR` (`161`) |
>
> **`[READ]` SPOT-CHECKED 2026-08-25: `gunfire.c:633` is `Switches[3]->Data`
> (`171`), `bondview.c:722` is `transform3Dto2DCoords` (`163`), `chraction.c:5854`
> is `bondviewGetPlayerDuckingHeightRelated` (`176`). ALL THREE LAND.**
> **So `168` §5's mandatory grep has a second half available: read the MECHANISM
> in `lib\ge` before deciding a symbol is unreachable** — that is the read `163`
> §7 skipped when it searched for Perfect Dark's identifier instead of the thing.

> # ►►►► 2026-08-25 — `A1` IS BUILT. BUILD TWICE, THEN ONE RUN. `188`. ◄◄◄◄
>
> ## **THE DIRECTION IS NOW BOUNDED TO THE FRUSTUM CONE BEFORE THE DIVIDE.**
> `187` measured the fault (`BAND=2846` of `aimed=8548`, `SAT=1424`), so `182`'s
> bar is cleared and `185` `A1` was written. **Knob `-NoAimCone` reverts to today
> exactly. The `162` +-2 clamp is UNTOUCHED and simply unreachable now.**
>
> ## **ONE NEW SYMBOL -> BUILD TWICE (`136`). NO `115` HEADER CHANGED.**
> ```powershell
> .\build.ps1     # twice
> ```
> **Then the standing command from `MAIN-STATION-TASKS.md`, unchanged, PLUS
> `-NoCrouch`. SWEEP SLOWLY, INCLUDING DIAGONALLY, AND DWELL PAST THE STOP.
> NO SHOTS NEEDED.**
>
> ## `G-A1` — **the crosshair moves CONTINUOUSLY to the edge and STOPS**, and on a
> diagonal sweep **the two axes saturate INDEPENDENTLY, not to a corner.**
> **IN THE LOG: `CONE=` non-zero and tracking `BAND=`, with `SAT=` at zero.**
> **`BAND` large with `CONE=0` means the fix is INERT — and that reads identically
> to success without the CONE counter.** `188` §2.
>
> ## ►► AND `A2` IS PROBABLY NOT A FAULT. ONE PRINT DECIDES IT. ◄◄
> **`[READ]`: `crosshair_angle` has `c_screentop` ADDED after the `h/2`, and the
> aim inversion SUBTRACTS it — so the centre is `(screenleft + w/2,
> screentop + h/2)`, not `(w/2, h/2)`.** `[INFERRED]`: `screentop = 10` is the
> `(240-220)/2` letterbox and the "ten-pixel drop" is the screen origin.
> **The `WIDE-frustum` line now prints `origin=` and `centre-should-be=`.
> `origin=(0,10)` closes `A2` as CORRECT ALL ALONG** — and with it the confound
> `185` `B2` warned about. `188` §3.
>
> ## **AND THE `begin_shutdown()` ENTRY PRINT IS IN.** Next X-close crash says
> whether it was never called or died inside. **STILL CLOSE WITH `taskkill`** —
> the lines cost nothing; do not spend a crash to collect them. `188` §4.

> # ►►►► 2026-08-25 LATE — READ `187` FIRST, THEN `185` (THE PLAN). ◄◄◄◄
>
> **THE LAST SESSION FINISHED ITS WORK AND THE MACHINE CRASHED BEFORE IT WROTE
> UP. `187` IS THAT WRITE-UP.** The block below still says *"the order starts at
> `D1`"* — **`D1` IS DONE AND RUN. THE NEXT BUILD IS `A1`+`A2`.**
>
> ## **`A1-VERIFY` RAN. `184` §4 IS CONFIRMED AND NO LONGER `[INFERRED]`.**
> **`[MEASURED]`: `BAND=2846` of `aimed=8548` (33%), `SAT=1424`, `noFrus=0`,
> `maxNx=15.4` / `maxNy=20.6` in tangent units.** The 37-degree band IS entered,
> the divide DOES return legal enormous values there, and the `162` clamp fires
> on one aimed frame in six. **BUILD THE CONE CLAMP** (`185` `A1`, `-NoAimCone`),
> **and `185` `A2` — the ten-pixel drop, confirmed again at `(160,120)` — rides
> the same build as a READ.**
>
> ## **`D1` PASSED.** 99 of 318 `BULLET`/`SIGHT` samples differ, and only while
> the sight is clamped. **U-16 publishes the UNCLAMPED value.**
>
> ## ►► `B3`/`B4` ARE RE-OPENED — **CLOSE WITH `taskkill`, NOT THE X.** ◄◄
> **`[REPORTED]` the X bugchecked the machine again; `[MEASURED]` the log ends
> mid-frame with NO `shutdown:` line.** `181` fixed a real thing and is
> **INSUFFICIENT, not refuted** (its own tier was `[ASSUMED]`, one close).
> **Every "CLOSE WITH THE X" instruction in the docs is SUSPENDED.**
>
> ## **AND COPY `gevr.log` ASIDE BEFORE EVERY CLOSE.** `187` §3.

> # ►►►► 2026-08-26 — STOP. EVERYTHING BELOW IS BUILT AND MOSTLY UNTESTED. ◄◄◄◄
>
> # ►►►►►► THE PLAN IS `185`. START THERE. ◄◄◄◄◄◄
>
> ## **SEVEN GROUPS, EACH ONE A SESSION'S WORTH, EACH WITH ITS OWN GATES.**
> **`A` the aim geometry · `B` depth · `C` comfort · `D` instruments ·
> `E` the test script · `F` the backlog · `G` the commit.**
>
> ### THE ORDER, IN ONE LINE
> **`D1` (minutes) -> `A1`+`A2` (one build) -> `A3` -> `C1`+`C2`+`C3` (one build)
> -> `B1` -> `E` from `T3` -> `B2`/`T7` decides `B3` -> `F`. `G` AT ANY POINT.**
>
> ## **AND THE ONE FAULT THAT BLOCKS ALL AIM WORK — `184` §4, GROUP `A1`:**
> **`[READ]` the aim refuses only at `fwd[2] < -0.05f` (~87 degrees) against a
> ~50 degree frustum.** Between them the divide returns finite, legal, ENORMOUS
> values, and `162`'s +-2 NDC clamp then **collapses a 37-degree band of
> DIFFERENT gun directions onto ONE screen point.**
> **`[MEASURED]`: 290 of 1,313 samples sit on exactly `(480,340)`.**
> **`[REPORTED]`, and the wearer named it before any of this was read:**
> *"nothing is related to where you're pointing it... it's only focusing on the
> general quadrant."* **BOUND THE DIRECTION TO THE FRUSTUM CONE BEFORE THE
> DIVIDE.**
>
> **AND `MAIN-STATION-TASKS.md` `T3`-`T11` ARE ALL VOID AND MUST BE RE-RUN** —
> `179`/`180`: no run between 08-24 21:00 and 08-26 had stereo at all.

> # ►►►► 2026-08-26 — B3 AND B4 ARE CLOSED, AND STEREO IS BACK. ◄◄◄◄
>
> ## **`shutdown: complete, clean` — THE X WAS PRESSED ON PURPOSE AND THE MACHINE LIVED.** `181`
> **`39` had both marked BLOCKING since `75`. Five sessions looked at the
> TEARDOWN and found nothing wrong, because nothing was wrong with it — it was
> never CALLED.** `SDL_QUIT` is queued, and Windows has already begun destroying
> the window before the main loop pumps it. **`SDL_AddEventWatch` fires
> synchronously on the posting thread, and `begin_shutdown()` now performs the
> teardown instead of leaving it to a hook that never runs.**
> **STILL `[ASSUMED]`: one clean close. B3 failed five times but never on every
> close — WANT THREE OR FOUR MORE X CLOSES. They cost nothing now.**
>
> ## **AND `-ViRate 90` RUNS WITH FULL STEREO. `180` IS RETRACTED.**
> **`[MEASURED]`: `90.0 fps · interpUsed=0 · stereo in 75 of 99 samples ·
> VRGATE/s ... -> stereo=91 | OK`.** The owner said so from memory and the
> instrument agreed. **`interpUsed` and `interpolationTargetKey` are INDEPENDENT
> — one VRGATE line shows `interpKey=91` beside `interpUsed=0`.**
> **`[INFERRED]`, UNVERIFIED: what fixed it was most likely the first rebuild
> that recompiled the RT64 LIBRARY** (`rt64_shared_queue_resources.h` changed) —
> `115`'s cross-boundary header trap. **DO NOT BUILD ON THIS until `build.ps1`'s
> "all targets" is READ and shown to include or exclude `lib/rt64`.**

> ## ►►►► HOW TO WRITE HERE: `182`. TIERS ARE MANDATORY FROM `183` ON. ◄◄◄◄
> **Every load-bearing claim carries `[MEASURED]` (the run and the line),
> `[READ]` (file:line), `[INFERRED]` (and the counter-example search you ran),
> `[REPORTED]` (verbatim), or `[ASSUMED]` (and what would settle it).**
> **AN `[INFERRED]` CLAIM MAY NOT BE BUILT ON.** `180` was retracted hours after
> it was written for exactly that — the FOURTH time this project has promoted an
> unverified claim to an established one (`160`, `163`, `171` §3, `180`).
> **A claim inherited from another document keeps THAT document's tier.**
> **AND A `[REPORTED]` OBSERVATION THAT CONTRADICTS A DOCUMENT IS EVIDENCE
> AGAINST THE DOCUMENT** — the owner overturned three claims from memory in one
> session and was right every time.

> ## **THE ORDERED TEST SCRIPT IS `MAIN-STATION-TASKS.md`. GO THERE FIRST.**
>
> **ONE BUILD, THEN ELEVEN RUNS, EACH CHANGING EXACTLY ONE THING** — sequenced so
> no test can invalidate a test above it. **Do not test these ad hoc.**
>
> ### ►► AND `T1`-`T11` ARE NOT THE WHOLE MAIN-STATION BACKLOG. ◄◄
> **`MAIN-STATION-TASKS.md` PHASE 4** carries the rest, audited 2026-08-26 out of
> the old `TESTS-OWED-ON-RETURN.md` (**which is now HISTORY — do not work from
> it**): **`T12`** `ds_option 2` as the default (measured free, only the DECISION
> is owed), **`T13`** one read to close O97, **B3/B4**, and **THE COMMIT**.
>
> **AND ONE THING CAME OFF THAT LIST FOR GOOD: `muzzleExt` IS DEAD, NOT OWED.**
> It did print — `6D-02` measured `100` flat — and **`171` §2 falsified U-14**:
> it scales the muzzle-flash SPRITE, not a barrel length. **Wiring it in would
> have pushed the bullet origin ~1 m down the barrel and looked exactly like a
> bad grip offset.** `169` U-14 is the record that stops it being re-proposed.
>
> **B4 IS WORSE THAN THE OLD FILE SAYS:** re-run on purpose 2026-08-24 with
> `149`'s fix compiled in, and **the X still bugchecks — with no `shutdown:` line
> in the log at all.** On the X path `xr_shutdown` never runs. **`149` is
> insufficient, not refuted**; the fix has to move to `begin_shutdown()`.
>
> | | | UPDATED 2026-08-26 |
> |---|---|---|
> | **WORN AND PASSED** | `165` crosshair drawn · `175` virtual screen (`178` ungated it) · `181` **B3/B4 CLOSED** · `183` layout stamp | |
> | **PARTLY PASSED** | `170`+`173` the crosshair fuses — **`[REPORTED]` it does NOT fuse today; the two crosses sit ONE CROSSHAIR WIDTH apart.** Group `A3` | |
> | **BUILT, NEVER WORN** | `174` head anchor · `176` physical crouch · `173` seam composition | |
> | **READ, CORRECT, NOT THE FAULT** | `172` clamp split — **`184` §3a: the bullet DOES take the unclamped aim. A LOG LABEL said otherwise.** Group `D1` | |
> | **NEVER ISOLATED** | `167` the FOV fix — and it IS running (`184` §3b) | |
> | **READ DONE** | `171` MUZZLENODE — **T2 PASSED, U-18 proceeds** | |
>
> ## **BUILD TWICE.** Two new `RECOMP_PATCH` symbols (`136`), four headers changed (`115`).
>
> ## THE THREE THAT DECIDE THE MOST
> **`T7` THE DISTANCE TEST** — shoot a wall near, then far. **Miss shrinks =
> muzzle parallax (U-06, a known cure). Miss holds = a constant angular error in
> the ray.** They behave OPPOSITELY, so one wall answers it, and **everything
> after depends on which.** If only one test gets done, make it this.
>
> **`T9` THE SEAM COMPOSITION** — hand held still, head turning, **the gun must
> not re-aim.** `R = Rhead * Rhand^T` is wrong; correct is `R = Rhead^T * Rhand`,
> **and the AIM has always used `Rhead^T`** — the aim and the picture have been on
> different transforms the whole time. **SECOND-TO-LAST ON PURPOSE: if it passes,
> `-HandAxis*` and `-GunOff*` were all tuned against a reference that no longer
> exists.**
>
> **`T10` PHYSICAL CROUCH — the owner's own requirement.** *"It would be great if
> the AI would know that you crouched."* **It already does:** `chraction.c:5854`
> aims at a fraction of `bondviewGetPlayerDuckingHeightRelated()`. **The AI has
> never read `crouchpos` at all** — it reads HEIGHT. So the slice writes
> `crouchpos`, lets MoveBond lower the height, and **cancels the camera drop
> host-side** so you do not crouch twice. **Stand still for the first ~90 frames —
> that is the calibration.**
>
> ## AND NOTE `-NoCrouch` ON EVERY AIM TEST
> **Physical crouch is ON by default and MOVES THE CAMERA.** If it fires while you
> are judging aim it silently changes what you are measuring. **Disabled for the
> whole aim chain, enabled alone in `T10`.**
>
> ## TWO STANDING POLICIES, OWNER'S DECISIONS
> **DELETE NOTHING** until the project is done — a knob costs a branch, a deleted
> knob costs the next session the read that found it. **This overrides every
> "should be deleted" in the docs.**
> **EVERY GIT COMMIT IS THE OWNER'S.** Sessions never stage, commit, branch or
> merge — they leave the tree described and put the commands in
> `MAIN-STATION-TASKS.md`.

> # ►►►► 2026-08-25 LATE EVENING — THE VIRTUAL SCREEN. `175`, U-19. ◄◄◄◄
>
> **ONE BUILD PENDING and it carries THREE things: `174` (the head-centre anchor
> + the trim instrument) and `175` (the virtual screen). THREE HEADERS CHANGED —
> `build.ps1` MUST report a FULL REBUILD** (`115`).
>
> ## **THE MENUS SHOW THE GAME NOW, NOT THE RED/BLUE CLEAR — `175`**
>
> **AND THE RED/BLUE WAS NEVER A BUG.** `ge_vr_xr.cpp:1632` says so in the
> project's own words: *"Null is a normal state, not a failure: the front end,
> menus, cutscenes and the opening frames all legitimately have no eye split."*
> Left red / right blue is `docs\10`'s convention, chosen so a swapped or
> single-eye submission is obvious the instant the headset is on. **It did its
> job. It is simply hostile to navigate a menu through.**
>
> **THE OWNER'S REASON IS A TOOLING REASON:** *"I can't use the VR controllers and
> see what I'm doing, because if I switch to the desktop view it switches to
> desktop controls."* **This makes every future wear test cheaper**, which is why
> it went ahead of things on the sheet that sound more important.
>
> ## **IT IS A REAL 3D RECTANGLE, NOT A BLIT**
> Copying the flat image into both eyes reads as a **wall at infinity filling the
> whole field of view.** Instead: the same shape as the timewarp shader — a
> fullscreen triangle that reconstructs each eye's view ray **from its OWN frustum
> tangents** — intersected with a plane at `-dist`.
> **`d.z` is `-1` by construction, so the plane is hit at `t = dist`: no divide,
> and no way to hit a degenerate one.**
>
> > **AND THE STEREO IS FREE.** The ray starts at that eye's own offset from the
> > head centre, so the screen has **genuine depth and correct parallax** — and
> > **needs NONE of the per-eye HUD machinery `173` fought over, because this is
> > actual 3D rather than a 2D sprite pretending to be.** The canted asymmetric
> > frustum (`166` §1) is correct BY CONSTRUCTION for the same reason.
>
> **THE SOURCE TAKES THE SAME PATH THE EYES DO.** `prepareEyeFromTarget` turned
> out to be generic over any `RenderTarget`, so the ordinary present `colorTarget`
> goes through the identical resolve and `VIRenderer::render()`. **THERE IS NO
> SECOND ROUTE BY WHICH A FRAME CAN REACH THE HEADSET** — a constraint, not a
> convenience: `50` and `69`-`71` are both records of two present paths
> disagreeing.
>
> **THREE THINGS TAKEN FROM PAST FAILURES:** one descriptor slot **per eye**
> (`69`-`71`: D3D12 resolves heaps at EXECUTION time, and a shared slot would
> reproduce B1 exactly while looking like a screen bug); **the red/blue clear
> REMAINS the fallback**, so "flat mode" and "no image at all" never become
> ambiguous; and `g_flatSource` is dropped at teardown, because `42`'s crash was a
> stale pointer into RT64's resources outliving them.
>
> **KNOBS:** `-ScreenDist` (2.5 m) and `-ScreenSize` (2.6 m WIDTH; height follows
> the image's aspect). **Sized in METRES at a distance, so the two do not fight.**
>
> ## ►► AND U-20 IS QUEUED, WITH ITS DEPENDENCY NOW CLEARED ◄◄
> **The owner wants PD's hub ROOM, re-skinned for GoldenEye** — and it is far
> smaller than it looks. `vr_hub.cpp` is 410 lines but **the geometry is TWO QUADS
> AND TWELVE VERTICES**: `BuildFloorMesh()` is 6 verts, `BuildSkyMesh()` is 6.
> **Everything you SEE is procedural fragment shader** — grid with distance fog,
> banded sky, one logo decal. **THERE ARE NO ART ASSETS TO PORT.**
>
> **AND IT IS THE RARE PD FEATURE WHERE `168`'s RULE CUTS THE OTHER WAY: the hub
> calls into NOTHING.** No lasersight, no model parts, no game state. **The only
> real work is GLSL -> HLSL.** `175` §7 built the textured-quad-with-per-eye-
> matrices machinery it needs, so **U-20 is now "draw two more quads behind it
> with different shaders", not a from-scratch feature.**

> # ►►►► 2026-08-25 EVENING — THE CROSSHAIR FUSES. `173`, `174`. ◄◄◄◄
>
> **READ `173` and `174`, then `161` (the plan) and `169` (the upgrade sheet,
> NEXT ID `U-20`).**
>
> ## **U-01 IS WORN AND WORKING: "much closer now in my vision."**
> **AND IT TOOK THREE ATTEMPTS, TWO OF THEM MINE:**
>
> **(1) `170` PUT THE SHIFT ON THE WRONG PIPELINE STAGE.** `Projection::Type` has
> FIVE members, not two — **GoldenEye's HUD sprites are `Type::Rectangle`, which
> carries NO PROJECTION MATRIX AT ALL.** The edit to `projMatrix[3][0]` was
> structurally incapable of moving the crosshair at any sign or magnitude.
> **`166` §1's diagnosis was right; `170`'s implementation aimed at a stage the
> HUD never passes through.** `173` §2.
>
> **(2) THE SIGN WAS INVERTED.** The matrix entry's sign is NOT the sign it
> produces in NDC — **the perspective divide flips it.** Expanding with
> `m23 = -1` gives `x_ndc = 2X/w - (tanR+tanL)/w`, negative constant, and it
> checks out at both frustum edges. **THE WEARER NAMED IT BEFORE THE ALGEBRA:**
> the two crosshairs **DIVERGED**, and divergent is BEHIND infinity, where eyes
> cannot fuse. Convergent would have been a finite depth. `173` §1.
>
> **AND TWO THINGS THAT WOULD HAVE BEEN WRONG IN THE FIX:** `FixedRect` is **10.2
> FIXED POINT** — one pixel is FOUR units, so a float pixel count lands at a
> QUARTER and truncates, which reads as "sign right, magnitude off" and invites
> tuning. And the shift is **NOT applied to full-width rects** — `coversScissorWidth`
> already identifies the framebuffer blit and fades, and shifting those would
> slide the whole IMAGE sideways per eye.
>
> ## ►► THE SEAM COMPOSITION IS WRONG, AND THE WEARER FOUND IT ◄◄
> ***"if I turn my head left and right, the gun will change directions in my hand
> automatically."***
>
> The seam computes `R = Rhead * Rhand^T`. **The correct view-space orientation is
> `R = Rhead^T * Rhand`** — **AND THE AIM PATH HAS ALWAYS USED `Rhead^T`.**
> **SO THE AIM AND THE PICTURE HAVE BEEN USING TWO DIFFERENT TRANSFORMS THE
> ENTIRE TIME.** That is `166` §4's "the drawn gun is the liar" hypothesis, and
> the head-turn report is the confirmation it was waiting for. `158` §3 proved `R`
> is a DRAWING matrix; **this says why.**
> **`-SeamCompose 1`. KNOB-GATED AND UNTESTED** — `-HandAxis*` and `-GunOff*` were
> all tuned against the old composition, so the default stays legacy until worn.
>
> ## ►► THE AIM WAS ANCHORED AT THE LEFT EYE — `174` ◄◄
> ***"it seems to aim off the right eye."*** `HeadView::position[2][3]` is **PER
> EYE**, so `head.position[0]` is the **LEFT EYE** — and the hand position, the
> muzzle and the whole aim ray were measured from it, **while `167`'s frustum and
> the HUD shift are CYCLOPEAN.** A constant lateral bias of half the IPD, ~3.2
> units at 100 u/m. **Now anchored at the head centre. BUILT, UNWORN.**
>
> ## ►►►► THE ONE TEST THAT DECIDES WHAT COMES NEXT ◄◄◄◄
> The shot lands **~6 px UP and ~1 px RIGHT** of the crosshair (the wearer drew
> it — predominantly VERTICAL, which a LATERAL half-IPD error does NOT explain).
>
> **SHOOT A WALL AT ARM'S LENGTH, THEN THE SAME SPOT FROM ACROSS THE ROOM.**
> **MISS SHRINKS WITH DISTANCE -> MUZZLE PARALLAX** (U-06, PD's
> `vrComputeCrosshairParallax` — a known cure).
> **MISS STAYS THE SAME SIZE -> A CONSTANT ANGULAR ERROR** in the ray.
> **They behave OPPOSITELY, so one wall answers it, and everything after depends
> on which.**
>
> ## AND A MEASUREMENT INSTRUMENT, NOT A KNOB — `174` §5
> **`-AimTrimX` / `-AimTrimY`, NDC.** Dial until the shot sits on the crosshair
> and **REPORT THE VALUE.** **IT IS EXPECTED TO BE DELETED** — `163` deleted five
> knobs by finding the projection; this exists to FIND the next cause, not to live
> beside one. Recording that intent is what stops it becoming permanent, which is
> how `-AimGain` survived as long as it did.
>
> ## NEW ON THE SHEET: `U-19` — THE FLAT GAME IMAGE IN VR
> The red/blue in menus is **NOT a bug and NOT a diagnostic left on** —
> `ge_vr_xr.cpp:1632` says null eye sources are a normal state for the front end,
> and `:2133` clears to `docs\10`'s tint on purpose. **Replacing that clear with
> the game's flat image would let the headset stay on through menus.**
> **THE ENTIRE BLIT PIPELINE ALREADY EXISTS** (`g_twRoot`/`g_twPso`, a fullscreen
> triangle with 16 float constants — the timewarp path). **One shared slot for the
> flat present texture is the only missing piece.**
> **AND IT IS NOT A PORT: PD's `vr_hub.cpp` is a decorative OpenGL room and never
> shows the game image.** `169` U-19.

> # ►►►► 2026-08-25 CLOSE — FOUR SLICES BUILT, NONE WORN. TWO RETRACTIONS. ◄◄◄◄
>
> **THE OWNER CANNOT TEST FOR NOW. EVERYTHING BELOW IS COMPILED-READY AND UNWORN.**
> **ONE BUILD CARRIES ALL OF IT, AND EVERY BEHAVIOUR CHANGE HAS ITS OWN OFF SWITCH.**
>
> ## READ IN THIS ORDER
> **`161`** the plan (boxes ticked) — **`169`** THE UPGRADE SHEET (new, standing) —
> then `167`, `170`, `171`, `172` for this session's slices.
>
> ## **`169` IS A NEW STANDING FILE. APPEND, NEVER REWRITE. NEXT ID: `U-19`.**
> **`161` is the PLAN (being built now, with gates). `169` is the CATALOGUE
> (everything found that WOULD be an upgrade).** Items enter `169` when found and
> move to `161` when someone decides to build them. **Nothing is ever deleted** —
> a rejected idea with its reason stops the next session re-finding it (`108`).
>
> ## WHAT WAS BUILT, ALL UNWORN
>
> | doc | what | off switch |
> |---|---|---|
> | **`167`** | The aim projected through a frustum nobody looks through. Game `c_scale` is built from `fovy=106`; the frame is DRAWN at the headset's ~88. **Vertical gap 1.374, horizontal 1.540 — TWO ratios, which is why it read as two bugs.** Now divided by the RENDER's live tangents. Zero new constants. | `-NoAimFrustum` |
> | **`170`** | **U-01.** `rt64_projection_processor.cpp:156` gates every per-eye adjustment on `Type::Perspective` — **and the HUD is ORTHOGRAPHIC**, so it has been excluded since stereo existed. That is the doubled crosshair. Fixed at `[3][0]`. | `-NoHudShift` |
> | **`171`** | The MUZZLENODE instrument. No behaviour change. | n/a |
> | **`172`** | **U-16.** The clamp split: the sight PINS, the shot KEEPS GOING. | `-NoClampSplit` |
>
> ## ►► TWO RETRACTIONS. BOTH WERE MINE, BOTH FOUND BEFORE THEY COST A BUILD. ◄◄
>
> **1. `163` §7 IS WRONG — GOLDENEYE HAS A MUZZLE NODE.** It said "no muzzle model
> part" because `MODELPART` returns zero. **THAT SEARCHED FOR PERFECT DARK'S NAME,
> NOT FOR THE THING.** `gunfire.c:633` reads `mdlhdr->Switches[3]->Data` — the
> per-weapon muzzle position in the gun model's frame, PD's `MODELPART_GUN_MUZZLEPOS`
> under another name — **and all four symbols it needs ARE patch-reachable.**
> `171` §3, `169` U-18.
>
> **2. `163` §1's "the FOV read is no longer owed for aiming" IS WRONG.** `166` §2
> measured the gap. **The read was owed and `167` is the fix.**
>
> ## ►► AND ONE PROPOSAL FALSIFIED BEFORE IT WAS BUILT — `169` U-14 ◄◄
> **`MuzzleFlashExtension` IS NOT A BARREL LENGTH.** `gunfire.c:754` hands it to
> `matrix_column_3_scalar_multiply`, which scales `matrix[8..11]` — **row 2, the Z
> BASIS ROW** (`matrixmath.c:408`). **It never touches `m[3][*]`, the position. It
> stretches the flash SPRITE and moves nothing.** `6D-02`'s `muzzleExt=100` was
> measured correctly and INTERPRETED wrongly. **Wiring it in would have pushed the
> bullet origin ~1 m down the barrel and looked exactly like a bad grip offset.**
>
> ## THE TWO RULES THIS SESSION ADDED, AND BOTH CAUGHT REAL ERRORS
>
> **1. SEARCH FOR THE MECHANISM, NEVER FOR PERFECT DARK'S IDENTIFIER.** A
> name-based grep can only prove PD's name is absent. It cost `163` §7 a feature
> GoldenEye has.
>
> **2. BEFORE COSTING ANYTHING THAT TOUCHES GAME CODE, GREP `patches/externs.h`
> AND `patches/structs.h` FOR EVERY SYMBOL IT NEEDS.** `157` withdrew a slice for
> want of eight; `166` stopped one for want of five; **`169` U-16 was recorded as
> "BLOCKERS: none" and was BLOCKED** — caught by this grep before a line was
> written (`172` §1).
>
> **AND ITS COROLLARY, FROM `172` §7:** **a game function you cannot patch is not
> always a blocker. If you own the PRODUCER and the CONSUMER, change what flows
> between them and leave the unreachable function untouched.** U-16 needed ZERO new
> symbols — **the difference was asking what the function READS rather than what it
> DOES.**
>
> ## THE SCALE STORY IS CLOSED IN THEORY, UNTESTED IN PRACTICE — `166` §3
> **`-WorldUnitsPerMetre` GOES BACK TO 100.** At 12, Bond is **14.6 m tall** and the
> gun is **1.7 m long** — that is the "gun/arm is much bigger than it should be"
> report, and it is arithmetic, not perception. **`159`'s sweep to 12 was
> cancelling the FOV error `167` now fixes.** **IF IT STILL LOOKS LIKE A TOY MODEL
> AT 100, THE FOV WAS NOT THE WHOLE STORY AND THAT IS THE FINDING.**
>
> ## STILL OPEN, AND NOT ADDRESSED BY ANY OF THE ABOVE
> **`166` §4's SEVENTEEN DEGREES.** Measured from the owner's own two-shot
> experiment: same muzzle, 17 deg of yaw between "aimed to hit" and "aimed where it
> should have been". **THE ONE OBSERVATION THAT DECIDES IT, now that the crosshair
> is visible AND single: does the crosshair sit on the DRAWN GUN'S BARREL, or off
> to one side?** On it -> the ray is right and the world is being aimed at wrong.
> Off it -> **the drawn gun is the liar**, and the seam rotation must be derived
> from the same raw pose the aim uses (`158` §3 already proved the seam matrix is
> not the barrel).
>
> ## THE BUILD AND THE LAUNCHES
> ```powershell
> .\build.ps1          # MUST report a FULL REBUILD - rt64_vr_eye.h changed (115)
> .\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
>          -WorldUnitsPerMetre 100 -HandUnitsPerMetre 100 `
>          -ViewmodelScale 0.5 -GunOffY 8 -GunOffZ -2 `
>          -HandAxisX -1 -HandAxisZ -1 `
>          -AimFromHand -MuzzleOrigin
> ```
> **Then repeat with `-NoHudShift`, and again with `-NoAimFrustum`, to isolate each
> half out of the one build.**
>
> **READ THE LOG FIRST, EVERY TIME:**
> ```powershell
> Select-String -Path .\gevr.log -Pattern "HUD shift|MUZZLENODE|AIM|SHOT" | Select-Object -Last 12
> ```
> - **`HUD shift=1 ... eye0= eye1=` — THE TWO MUST DIFFER.** Equal means the shift
>   never reached the projection, **which looks identical in the headset to not
>   having built it** (`48`).
> - **`state=` must say `APPLIED`.**
> - **`MUZZLENODE Switches[3]=` — does it CHANGE between a pistol and a rifle?
>   If not, it is not a per-weapon muzzle and U-18 is over.**
>
> **HEADSET ON, THEN LAUNCH. WAKE THE CONTROLLERS FIRST** — one run had
> `handValid=0` on 91 of 99 samples. **CLOSE WITH `taskkill`, NEVER THE X.**

> # ►►►► 2026-08-25 LATEST — `169` IS THE UPGRADE SHEET. THREE NEW DOCS. ◄◄◄◄
>
> **`167` THE FOV FIX (built, UNWORN) — `168` THE PD PORT — `169` THE UPGRADE SHEET.**
>
> ## **`169` IS A NEW STANDING FILE. APPEND TO IT, NEVER REWRITE IT.**
> **`161` is the PLAN (what is being built now, with gates). `169` is the
> CATALOGUE (everything found that WOULD be an upgrade).** An item lives in `169`
> from the moment it is found and moves to `161` only when someone decides to
> build it. **Nothing is ever deleted from `169`** — a rejected idea with its
> reason stops the next session re-finding it. **NEXT ID: `U-18`.**
>
> ## THE AIM PROJECTED THROUGH A FRUSTUM NOBODY IS LOOKING THROUGH — `167`
> **`c_scalex`/`c_scaley` come from `c_perspfovy=106`; the frame is DRAWN from the
> headset's ~88.** Vertical gap **1.374**, horizontal **1.540** — **TWO RATIOS,
> which is why it read as two bugs** ("worse going up" AND "off differently at the
> sides"). Now divided by the RENDER's own live tangents. **Zero new constants.**
> **`163` §1's "the FOV read is no longer owed" is RETRACTED.**
> **THE BULLET WAS NEVER AFFECTED** — it is a raw game-space ray. This moves the
> CROSSHAIR onto the barrel and nothing else.
>
> ## THE CROSSHAIR: TWO SEPARATE FAULTS, ONE FIXED
> **(1)** It was NEVER DRAWN — `gunsightmode=2` is `GUNSIGHTREASON_NOTAIMING`, set
> from the AIM BUTTON nobody presses in VR. Hidden for the whole project. Fixed
> in `165`. **(2)** Once drawn it appeared DOUBLED, one place per eye — the
> frustums are mirrored and asymmetric, so **no single pixel is right for both.**
> **PD's fix is `U-01` and it is the top of the sheet.**
>
> ## **THE PD PORT RULE, LEARNED THREE TIMES — `168`**
> **THE CONSTANTS AND DESIGNS TRANSFER. THE SUBSYSTEMS DO NOT.** Every failure
> (`155`'s post-rotation, `163` §7's muzzle model part, `166` §8.5's laser) was a
> call INTO a PD feature GoldenEye does not have. **So the question is never "is
> this VR code portable" — it is "what does this VR code CALL INTO".**
> **AND THE CHEAPEST STEP IN THE WHOLE PROJECT: before costing anything that
> touches game code, grep `patches/externs.h` and `patches/structs.h` for every
> symbol it needs.** `157` withdrew a slice for want of eight; `166` stopped one
> for want of five.
>
> ## TIER A OF THE PORT — NOTHING BLOCKS THESE
> **`U-01` per-eye HUD shift** (PD's canting term evaluates to `-0.1867` for our
> eye 0 — **exactly the `m20=-0.18669` already in our own log**); **`U-02` host-side
> recoil** (*"100% on OpenXR side, no engine dependency"*); **`U-03` snap turn**;
> **`U-04` the settings menu.**
>
> ## AND TWO CHEAP GOLDENEYE-NATIVE WINS FOUND WHILE READING
> **`U-14`** — `MuzzleFlashExtension` (`gun.h:18`) is the per-weapon barrel length
> the game ALREADY SHIPS, already measured at 100, already at offset 0 of a struct
> we already declare. **Per-weapon muzzles for a default change.**
> **`U-16`** — **`field_FFC` is never clamped in stock GoldenEye.** The clamp split
> is already half done; prior art is not shipping something novel there.

> # ►►►► 2026-08-25 LATE — P0 IS CLOSED. THE PROJECTOR WAS IN THE GAME. ◄◄◄◄
>
> **READ `162`, THEN `163`, THEN `161` (updated — seven boxes ticked).**
>
> ## **THE AIM KNOB WAS NEVER ON. `162`.**
> **`state=NEVER-CALLED` on all 117 samples — not APPLIED, not REFUSED, a THIRD
> state. `-AimFromHand` was not passed, so `aim_screen_ndc` returned at its
> guard.** *"Still mis-aimed, UNTUNED"* was judged on a build where the aim path
> never executed.
>
> ## **AND THREE THINGS THE BOARD SAID WERE WRONG.**
> **(1) THE CONTROLLERS DID BIND** — `bound profile =
> /interaction_profiles/oculus/touch_controller`, with live pose data. The Pimax
> presents as **Oculus Touch**. `handValid=` is not in the log at all; that
> reading was from an older build. **P0-1 WAS NOT THE BLOCKER.**
> **(2) P0-3(a) WOULD HAVE BROKEN THE AIM.** `-AimFwdNeg 0` cleared the refusal
> **under basis 0**; `158` §5 changed the default to basis 2 and inverted the
> convention. `fwdHead.z < 0` on 97 of 98 samples, so **`1.0` is correct** and
> defaulting to 0 would refuse every frame. **NOT APPLIED, and the code says why.**
> **(3) P1-4(b) IS IMPOSSIBLE.** `MODELPART` has **zero** occurrences in the game
> tree. **GoldenEye has no muzzle node** — only `f32 MuzzleFlashExtension`
> (`gun.h:18`). Second PD constant to fail transfer after `155`.
>
> ## **P1-2 IS BUILT, AND IT NEEDED NO WORLD FRAME AT ALL. `163`.**
> **`transform3Dto2DCoords` (`bondview.c:722`) takes NO camera matrix, runs off
> live `g_CurrentPlayer` scales, is already called from `gunfire.c:4818`, and
> carries the game's OWN fov.** And inverting its partner shows GoldenEye's camera
> frame is **`+x` right, `+y` up, `-z` forward — OPENXR'S HEAD FRAME, AXIS FOR
> AXIS.** The ray crosses the boundary unmodified.
>
> **FIVE KNOBS ARE NOW DEAD: `-AimGain`, `-AimSignX`, `-AimSignY`, `-AimFwdAxis`,
> `-AimFwdNeg`. ZERO free parameters.** Old path kept behind **`-AimEstimate`** so
> both can be compared out of ONE build.
>
> **P1-3 IS IN THE SAME BUILD, AND ITS TRAP WAS HIT AND FIXED:** writing
> `gun_azimuth` beside the crosshair pre-load puts it ABOVE that pair's own
> integrator loop, which overwrites it the same frame — **a crosshair that tracks
> and a gun that does not, which reads as "the gun lags".**
>
> ## **NOTHING BELOW HAS BEEN COMPILED. BUILD, THEN WEAR IT ONCE.**
> ```powershell
> .\build.ps1
> .\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
>          -WorldUnitsPerMetre 12 -HandUnitsPerMetre 100 `
>          -ViewmodelScale 0.5 -GunOffY 8 -GunOffZ -2 `
>          -HandAxisX -1 -HandAxisZ -1 `
>          -AimFromHand -MuzzleOrigin
> ```
> **`build.ps1` MUST REPORT A FULL REBUILD** — three headers changed (`115`), and
> **run it TWICE**: two new `RECOMP_PATCH`-reachable symbols (`136`).
> **READ THE LOG FIRST: `state=` MUST NOW SAY `APPLIED`.**
> **CLOSE WITH `taskkill /F /IM GoldenRecomp.exe`.**

> # ►►►► 2026-08-25 — `161` IS THE PLAN NOW. `148` IS SUPERSEDED. ◄◄◄◄
>
> **READ `161` (the prioritised, tickable board), THEN `160` (the full Perfect
> Dark scan and the evidence behind the order). `148`'s `6D-xx` labels are still
> valid and are carried into `161`.**
>
> ## **PERFECT DARK'S SOURCE IS NOW ON THIS DISK AND STAYS THERE.**
> `local-only\prior-art\perfect_dark_VR` — branch `port`, commit `67ea20c`, MIT.
> **The same commit `102` was read at, so every line number in `102` resolves.**
> **DO NOT RE-CLONE IT. ATTRIBUTION IS OWED** in `PUBLISH-MANIFEST.md` and at the
> point of use.
>
> ## **WHY THE AIM IS NOT "COPY-PASTE FROM PERFECT DARK", IN ONE SENTENCE**
>
> **They edit `bgunSwivel` from inside the game, where
> `camGetWorldToScreenMtxf()` is in scope, and PROJECT a world ray through the
> game's own camera matrix — zero tuning constants. We compute our aim in
> `rt64_render_context.cpp`, where that matrix is not in scope, so we ESTIMATED
> the projection with `GE_VR_AIM_GAIN` and a pile of sign knobs.** `160` §2/B1.
>
> **AND "SOMETHING IS LOCKING THE MOVEMENT" IS THREE THINGS, NOT ONE:**
> **(1)** the controllers never bind — `handValid=0` on all 46 samples (`6D-14`,
> now `P0-1`); **(2)** the aim write is `REFUSED` every frame, so both
> integrators decay to screen centre and every shot leaves along the view axis
> (`158`, now `P0-2`/`P1-2`); **(3)** the `[3, w-4]` clamp, which is real,
> already unclamped behind `-FreeAim`, and **the smallest of the three.**
>
> **THREE MORE FINDINGS FROM THE SCAN, ALL IN `160`:**
> **we drive only ONE of the two aim integrators** where PD drives both, two
> lines apart; **`muzzle_origin` still uses the barrel axis `158` §3 FALSIFIED**
> while `aim_screen_ndc` uses the derived one — a live bug hidden only by
> `-MuzzleExt` defaulting to 0; and **PD reads the muzzle out of the gun model
> itself** (`MODELPART_GUN_MUZZLEPOS`), which would delete `-MuzzleExt` and give
> per-weapon muzzles for free.

**Updated 2026-08-24, end of session. B1 IS FIXED — IT IS VR.
THE JUDDER LINE IS CLOSED, INCLUDING THE HEAD TURN.
THE NEXT PHASE IS 6DoF, AND `161` IS THE PLAN (`148` superseded).**

> # >>>> 2026-08-25 CLOSE — SCALE, AND THE NEXT MISSION. <<<<
>
> ## **THE OWNER'S NEXT MISSION, IN HIS WORDS: "getting this hand tracking right and the bullet leaving the gun."**
>
> ## SCALE — `159`. AND BOTH RECORDED NUMBERS WERE WRONG FOR THIS JOB.
>
> **6D-12/S1's split resolved `16` vs `77` in one session. They were never in
> conflict — two quantities were sharing one number:**
>
> | | Value | Kind |
> |---|---|---|
> | **`-HandUnitsPerMetre`** | **100 — PINNED** | **A MEASUREMENT.** 1 unit = 1 cm (`16`, Bond's 175-unit eye). Hand travels 1:1 |
> | **`-WorldUnitsPerMetre`** | **~12–25, STILL TUNING** | **A PERCEPTION.** Sets stereo separation and apparent size only |
>
> **THE DIAGNOSTIC PHRASE, AND IT NAMES THE FAULT:** *"toy model level...
> characters much smaller than me size wise BUT SAME HEIGHT."* **Heights are
> GEOMETRY and invariant — `chr.c:1717`'s `chrheight 185` vs Bond's `175` puts
> you eye-to-eye with a guard at any scale. Only SIZE is stereo. Same-height-but-
> miniature IS HYPERSTEREO and it means the number is TOO HIGH.**
>
> **HALVE, NEVER NUDGE.** Finer than a factor of two is below the noise floor.
> **50 → 100 (worse, I had the optics BACKWARDS) → 25 ("better") → 12 pending.**
>
> **THE GUN-TO-GUARD RATIO IS `-ViewmodelScale` ALONE** — world scale moves both
> together and their ratio never changes. **Halve the grip offsets with it.**
>
> > **THE BEST INSTRUMENT THIS PROJECT HAS IS A GUARD.** Better than the doorway
> > `16` asked for: a doorway's true size is a guess about 1990s level authoring;
> > **a person is known by heart, and the guard is guaranteed to be your height.**
>
> **IF THE SWEEP BOTTOMS OUT IT IS NOT STEREO — AND THE FOV READ IS OWED**
> (`159` §6): S0 reports `fovy=106` from the widescreen path while the headset's
> live tangents give ~88 degrees. **It is NOT established that `widescreen.c`
> does not re-apply after our override. That is a READ, not a launch.**
>
> ## AIMING — WHERE IT ACTUALLY STANDS
>
> | | |
> |---|---|
> | **A1b** the ORIGIN | **DONE, WORN — "bullets come out of the gun"** |
> | **A1c** the DIRECTION | **`-AimFwdNeg 0` cleared the REFUSAL. Still mis-aimed, UNTUNED, no log read since** |
> | **A1** the clamp | Built, inert until A1c is right |
>
> **THE NEXT AIM RUN MUST READ THE LOG FIRST** — `Select-String -Path .\gevr.log -Pattern "AIM"`.
> **`state=` must say APPLIED**, then tune `-AimGain`, then `-AimSignX/-AimSignY`.
> **TWO GUARDS ARE STILL OWED IN CODE:** make `AIM_FWD_NEG 0` the DEFAULT (it is
> a trap as shipped), and **CLAMP the NDC** — a near-zero forward divisor threw
> `ndc=(-8.5,-17.9)` and flung the crosshair off screen, which is the "shooting
> the ground" report.

> # >>>> 2026-08-25 LATE — AIMING. THE SEAM WAS COSMETIC ALL ALONG. <<<<
>
> ## **THE FINDING OF THE SESSION, AND IT IS STRUCTURAL — `157` §6.1**
>
> **`hand_override`'s matrix lands in `hand->field_8EC`, and EVERY READER OF
> `field_8EC` IN THE GAME TREE IS A DRAWING SITE** (`gunfire.c:550-553`).
>
> > **SO FROM `83` UNTIL TODAY, MOVING THE HAND MOVED THE GUN'S PICTURE AND
> > NOTHING ELSE. `crosshair_x_pos` SAW THE STICK AND ONLY THE STICK.**
>
> **The wearer:** *"No matter where I move the gun it doesn't change unless I move
> my trigger."* **AND IT INVALIDATES `153` §3** — that proof was correct and its
> premise was not: the hand never fed `turn_x`, so A1's unclamping removed a
> limit the hand could not reach.
>
> ## WHERE AIMING STANDS
>
> | | |
> |---|---|
> | **A1b** the bullet's ORIGIN | **DONE, WORN — "bullets come out of the gun"** |
> | **A1c** the bullet's DIRECTION | **BUILT, REFUSED every frame. `158` §5 is the fix, UNRUN** |
> | **A1** the clamp | Built; inert until A1c lands |
>
> **THREE GUESSES AT THE BARREL AXIS INSIDE `R` WERE ALL WRONG, AND ONE LOG LINE
> CAUGHT IT IN ONE RUN:** `state=REFUSED fwd=-0.303`,
> `row3=(-0.45,-0.84,0.30)` — **dominated by Y; that is not a barrel.** The
> game-side line agreed: **`crosshair_angle=(160,120)px`, dead centre, unmoving.**
> **`R` IS A DRAWING MATRIX** (`Rhead*Rhand^T` plus a `diag(sgn)` conjugation)
> **and was the wrong place to look for geometry.** `158` §5 derives the ray from
> the RAW poses and is now the default.
>
> > **`48`'s "an instrument must be able to say I CANNOT ANSWER THIS" paid for
> > itself: a refused frame and a zero frame look identical in the headset.**
>
> ## ALSO THIS SESSION
>
> **6D-08 (G2) DONE** — PD's `{w,-x,y,-z}` basis is `-HandAxisX -1 -HandAxisZ -1`
> and it fixed the up/down inversion **on the first launch**. **But PD's 1.5708
> rad post-rotation is FALSIFIED for us** (`155`) — first PD constant that did not
> transfer, **and it came from the same slice as one that did.**
>
> **6D-09 (G3)** — the "anchor on the front of the gun" was `ge_vr_gun_off_*`
> defaulting to **zero**: the gun pivoted about the model's own origin. **`-GunOffY 8
> -GunOffZ -2`** (PD's pistol default, cm -> our units) fixed it. **`-SeamNoRot`,
> in every command in this project until now, was DELETING the rotation entirely.**
>
> **6D-12 (S1) BUILT** — `-WorldUnitsPerMetre` / `-HandUnitsPerMetre` split.
> **6D-02 DONE, 6D-01 G0-1/G0-2 pass, `23` CLOSED.**
> **AUTO-AIM IS OFF in the game's own options** (`157` §6.2) — record it before
> comparing runs.
>
> ## THE STANDING COMMAND
>
> ```
> .\vr.ps1 -UnitsPerMetre 50 -HandSeam -HandPosZ 1 -ViRate 90 `
>          -GunOffY 8 -GunOffZ -2 -HandAxisX -1 -HandAxisZ -1 `
>          -AimFromHand -MuzzleOrigin
> ```
>
> **B3 STILL BUGCHECKS ON THE X** and `149`'s fix is in code the X path never
> reaches. **CLOSE WITH `taskkill`.**

> # >>>> 2026-08-25 — 6DoF IS MOVING. FIVE SLICES, `153`-`157`. <<<<
>
> **CLOSED, MEASURED:** **`23`** (explosions duplicating) is GONE now that nothing
> is interpolated — open since Phase 1, `92`'s candidate 2. **6D-02** `muzzleExt`
> read at last: `100`, PREDICT >0, **`90`'s five falsifiers are five for five.**
> **6D-01** G0-1/G0-2 pass — `head play` tracks the physical headset.
> **6D-08 (G2)** — PD's `{w,-x,y,-z}` basis is **`-HandAxisX -1 -HandAxisZ -1`**
> and it **fixed the up/down inversion on the first launch.**
>
> **THE STANDING COMMAND HAS CHANGED. `-SeamNoRot` IS GONE** — it was writing
> identity over the gun's rotation (`154` §1) and had been in every command in
> this project. **`-HandSeam` replaces it:**
>
> ```
> .\vr.ps1 -UnitsPerMetre 50 -HandSeam -HandPosZ 1 -ViRate 90 `
>          -GunOffY 8 -GunOffZ -2 -HandAxisX -1 -HandAxisZ -1
> ```
>
> **AND PD IS PRIOR ART, NOT A SPEC — FIRST MEASURED PROOF (`155`):** the basis
> transferred; **their 1.5708 rad X post-rotation DID NOT** (`-HandRotXDeg 90`
> failed, `-90` was worse, 0 beat both). **Same slice, two constants, one right.**
> They were judged separately only by accident of landing in different builds.
>
> **BUILT, NOT RUN:** **`153` A1** (the bullet goes where the gun points — the
> clamp at `gunfire.c:4699-4715` is the ONLY steady-state difference between gun
> and bullet, and its eight readers sort ONE-to-seven), **`156` S1** (the scale
> knob split — world vs hand), **`157` A1b** (**shots leave the CAMERA, not the
> gun — three zeroed lines at `gunfire.c:4871-4873`**; the wearer's blocker).
>
> **B3 IS ANSWERED AND NOT FIXED: B4 was run on purpose, the X still bugchecks,
> and there is NO `shutdown:` line in the log — `149`'s fix is in `xr_shutdown`,
> which the X path never reaches** (`42`'s recorded signature). **KEEP CLOSING
> WITH `taskkill`. Do not spend a fourth reboot.**

> # >>>> `151` — THE DEFAULT WAS TRIED AND REVERTED. B3 IS COMPILED, UNWORN. <<<<
>
> **`vr.ps1` IS UNCHANGED — `$ViRate = 60`, and H-9 STAYS OPEN.** 90 was made the
> default and reverted the same evening by owner decision: **every launch names
> its own pacing.** `.\vr.ps1 -UnitsPerMetre 50 -SeamNoRot -HandPosZ 1 -ViRate 90`
>
> **6D-00: `149`'s FIX IS COMPILED** and verified in the binary rather than the
> build log (`133`). **TWO PC CRASHES WERE SPENT AND NEITHER ANSWERED B4: NO
> `shutdown:` LINE APPEARS IN EITHER LOG, so the teardown was never reached.
> B3 IS UNTESTED, NOT REFUTED.** Keep closing with `taskkill`.
>
> **AND THE REBOOTS WERE AVOIDABLE — `151` §4.** `48`'s "WEAR IT BEFORE YOU
> BELIEVE IT" (`63`) says a render/present-path change gets the `-NoXr` bisect
> BEFORE the headset. `waitForGpu` is in the frame loop and went straight to a
> headset. **`118`'s de-risker exists for exactly this.**
>
> **`151` §2 answers the 60 Hz monitor question from the code: it does NOT go
> slow.** The VI thread paces on the wall clock and the tick accumulator runs off
> real elapsed counts. The caveat is `145` — Bond's speed tracks the actual frame
> rate, so at 60 fps he is back to about stock.

> # ►►►► READ `HANDOVER.md`'s TOP BLOCK, THEN `148` (THE PLAN), THEN `147`. ◄◄◄◄
>
> **`148` REPLACES `126` AS THE STANDING PLAN.** `126` is Route B and Route B is
> closed. **Take the first `148` task not marked DONE, and mark it before you
> finish — `108` is why.**
>
> ## THE HEAD TURN IS GONE
>
> ***"I shook my head fast, slow, went in circles. IT DOESN'T DO IT. It's pretty
> damn good."*** *"SO MUCH better... totally playable and enjoyable."*
>
> **`124`'s target, the half the owner insisted must not be lost, is CLOSED** —
> `92` to `147`, fifty-five documents. Route B made the sim actually run at
> 90 Hz: fps mean **82.7**, **`interpUsed=0`**, **`distinctTargets=90`**,
> **`LATE 0/91`**, **`per1000ms=60`**. The duplicate frame that survived fifteen
> documents **no longer exists**, because nothing is manufactured.
>
> **DEFERRED BY OWNER DECISION, NOT A DEFECT:** the world still animates in 60
> steps — visible only on the truck at full speed. That is RB-03 (`145`).
>
> **THE HANDOVER'S "SUGGESTIONS AND LOOSE ENDS" BLOCK IS NOT OPTIONAL READING.**
> Nine items, including the one recommendation that outranks the plan itself:
> **B3 (the bugcheck on VR close) is now the highest-value task in the project**,
> because every 6DoF slice is judged by wearing it and every wear test risks a
> reboot.

> # ►►►► ROUTE B IS DONE. ***"SO MUCH better... totally playable and enjoyable."*** ◄◄◄◄
>
> **Worn 2026-08-24 19:00 at a true 90 Hz sim.** fps mean **82.7**,
> **`interpUsed=0`**, **`eye0 = eye1 = distinctTargets = 90`**,
> **`LATE 0/91` — zero per cent**, **`per1000ms=60`**. `147`.
>
> **The duplicate frame that survived fifteen documents is not fixed — IT NO
> LONGER EXISTS**, because nothing is being manufactured. **`dupSrc=90/90` is
> VOID** (`113` §2 — blind counter with `-EyeInterp` unset; do not re-misread it).
>
> ## THE GATE THAT BLOCKED EVERYTHING SINCE `96` IS LIFTED
>
> `96`: *"It's pointless building all this extra stuff if you're just going to
> get sick when you're playing it."* **`86`'s nine 6DoF slices unpark.**
>
> **NEXT IS A1** — design in `101` §6, prior-art values in `102`, and its one
> open question already closed by the owner (*"you're in the shooting position
> now"*). **`102` §1: PD leaves the BULLET AIM UNCLAMPED and clamps only the
> drawn crosshair — prior art ships the break-the-lock.**
>
> **DEFERRED BY OWNER DECISION, NOT A DEFECT:** the world still animates in 60
> steps while rendering at 90. That is RB-03, and `145` shows it is not small.
>
> **STILL OPEN:** the head-turn artifact was never separated from the stick half
> in the report (`146` §5) — ask sometime, no longer blocking. **B3/B4 have been
> BLOCKING since `75` and now have no competition.**

> # ►►►► READ `HANDOVER.md`'s TOP BLOCK, THEN `146`, THEN `126`. ◄◄◄◄
>
> ## WHERE IT STANDS IN FOUR LINES
>
> **1. RB-02 WORKS.** `143`: the sim runs at **90 Hz and keeps real time** —
> 89 fps, `per1000ms=60` across 138 samples, `interpUsed=0`, audio and pause
> correct, Bond's speed correct (`145`), stable. **`92`'s "90 Hz is
> structurally unavailable" is answered** — a truncating divide plus a hardcoded
> `60` in a runtime file nobody had opened (`129`).
>
> **2. RB-03 IS PARKED, STRUCTURALLY.** `145`: it makes Bond exactly 1.5x fast
> (timed: 27.04 s vs 18.18 s). **Not a bug we introduced** — `bondview2.c:7237`,
> Bond's walk is a per-FRAME convergence loop with no timestep, so more frames
> means a faster Bond. Fixing it means a timestep inside `MoveBond`'s 1307
> lines. **`-FloatDelta` is off by default; the build being played is correct.**
>
> **3. THE PATH IS NOW RB-07 — THE HEADSET. `146` IS THE PLAN.**
> `.\vr.ps1 -UnitsPerMetre 50 -SeamNoRot -HandPosZ 1 -ViRate 90`
> **Do not rebuild first (`146` §1). Read fps and `dupSrc` BEFORE judging
> anything worn (`146` §4).** **RB-02 trades an interpolator for 50% more real
> rendering at 26 Mpx an eye** — the headroom `109` measured was sized for sixty
> frames, not ninety.
>
> **4. THE PREDICTION, ON THE RECORD:** stick turn and world motion should be
> clearly better; **the HEAD TURN may not be fixed at all** (`146` §5). If it
> survives a true 90 Hz sim with no interpolation and no duplicate frames,
> **every explanation this project has is exhausted** and the cause is upstream
> of everything we have touched.
>
> **B3 still costs a reboot per VR session — close with `taskkill`, never the X.**

> ### ►►►► `126` IS THE PLAN. ROUTE B, AS LABELLED TASKS. START THERE. ◄◄◄◄
>
> **EVERY SESSION: read this file, then `126`, then take the first task that is
> not DONE. Mark it DONE / IN PROGRESS / BLOCKED before you finish, whatever
> happened.** `108` exists because a session ended without writing up and the
> next one wrote a document that contradicted it.
>
> **RB-00 — RB-01c DONE. RB-02 (`131`) AND RB-03 (`132`) ARE WRITTEN AND
> UNBUILT. RB-04 IS RE-SCOPED TO EIGHT LINES AND IS NO LONGER A BLOCKER.**
>
> > ## **►► THE VERY NEXT THING: BUILD IT AND RUN IT TWICE. `131` §5, THEN `132` §5. ◄◄**
> >
> > ```powershell
> > .\build.ps1
> > .\vr.ps1 -NoXr -ViRate 90                 # RB-02 alone. CORRECTNESS gates.
> > .\vr.ps1 -NoXr -ViRate 90 -FloatDelta     # then RB-03. THE SMOOTHNESS.
> > ```
> >
> > **ONE BUILD, TWO LAUNCHES, IN THAT ORDER.** RB-02 alone shows no benefit —
> > motion still steps until RB-03 — **but G-131-1/-3/-5 are CORRECTNESS gates
> > and RB-03 sits on them.** Fused knobs would mean a failure could not say
> > which half caused it. **G-132-1: `gdelta x1000` ~667 STEADY. G-132-3: PAUSE
> > IT, the world must stop DEAD. G-132-4 is the first gate in this whole line
> > that can answer BETTER rather than NOT BROKEN.**
> >
> > **NO HEADSET. NO B3 REBOOT RISK. NO WEARER TIME** — `118`'s de-risker, and
> > this is the slice it was for. **`build.ps1` MUST REPORT A FULL REBUILD**
> > (three headers changed — `115`).
> >
> > **G-131-1, THE GATE: `sgf=` on the `[trace] retrace` line must STOP being
> > flat 1** — a mix of 0 and 1 averaging two thirds. Still flat 1 and nothing
> > else in the run counts. **G-131-3: LISTEN TO IT** (`130`). **G-131-5: an
> > unset launch must be indistinguishable from today.**
> >
> > **`131` is nine files and one knob.** `events.cpp`'s two hardcoded `60`s
> > become a knob; the remainder accumulator and `130`'s audio divisor live in
> > the new `patches/ge_vr_route_b.c`. **NO RT64 FILE IS TOUCHED** —
> > `PUBLISH-MANIFEST.md` records the GPL side.
> >
> > **AND `131` §4 CORRECTS `127`:** `workbench_theboy.c:659`'s
> > `60 / speedgraphframes` is **a live divide by zero** once `deltaFrames` can
> > be 0 — `127` audited the game tree and not the patches. It was also feeding
> > RT64 the wrong rate, which would have re-manufactured the very frames Route B
> > deletes.
> >
> > **AND `132` §3 COLLAPSES RB-04, WHICH NOBODY HAD COUNTED:** of 216
> > `g_GlobalTimerDelta` references, **EIGHT sit inside a `g_ClockTimer > 0`
> > guard and ALL EIGHT ARE DIVIDES — not one is an integrator.**
> > `bondview2.c:2885`, `bondview2.c:6709`, `gun.c:2335-2337`,
> > `gunfire.c:203-205`. The other 208 are unguarded accumulations that sum
> > correctly from a fractional delta; **`bondview2.c` is 73 of 75 unguarded, so
> > RB-03 lands safely alone.** The eight give stale velocity for 11 ms on one
> > frame in three — **not motion at two-thirds speed.**
> >
> > **RB-03's ONE LINE:** `lvlManageMpGame` is ~500 lines, but **its only caller
> > is `bossMainloop`, which is already patched**, so the delta is overwritten
> > right after it returns. **THE SUBTLE BIT (`132` §2.2): under RB-02
> > `g_ClockTimer == 0` NO LONGER MEANS PAUSED** — it also means "no whole tick
> > this frame". The pause test is re-asked directly, and G-132-3 is there only
> > to check it.
> >
> > **STILL NOT ADDRESSED BY EITHER: THE HEAD-TURN HALF.** `124`'s target.
> > RB-02/RB-03 delete the duplicate frame, the interpolated-frame artefacts and
> > the per-pass pose machinery, **but the head pose path is judged at RB-07, in
> > the headset, and nowhere else.**
>

> > ## **`130` — THE AUDIO IS PACED BY THE RETRACE, AND 90 Hz BREAKS IT. THE FIX IS ONE DIVISOR.**
> > `sched.c:334` notifies the audio client on `(frameCount & 1) == 0` — 30
> > audio frames a second x `g_FrameSize` 735 = **exactly 22050 samples/s**. At
> > 90 that is 45 frames/s and the `osAiGetLength` servo **floors at 720, so
> > 32,400 samples/s into a 22,050 Hz DAC.** The host then **decimates by
> > `1 << skip_factor`** (`main.cpp:238`) — aliased, hashy audio, not graceful
> > latency. **`90/3 == 60/2 == 30`, so `frameCount % 3` makes the audio path
> > cadence-IDENTICAL to today.** Do NOT rescale `MAYBE_FRAME_RATE`.
> >
> > **SO RB-02's KNOB MUST SET BOTH `events.cpp`'s VI RATE AND `sched.c`'s
> > DIVISOR. EITHER ONE ALONE IS A BROKEN BUILD.**
> > **Game code, so `RECOMP_PATCH` — no licence boundary, unlike the VI edit.**
> > **WATCH NOT GUARD:** `musicFadeTick` and `g_ViShakeTimer` are per-retrace and
> > would run 1.5x fast. **NEGATIVE that removes a worry:** the ungated AI send
> > in `events.cpp:167` is dead — GE never registers `OS_EVENT_AI`.
>
> **And `129` is still the biggest finding of the Route B work.**
>
> > ## **THE 60 Hz IS HARDCODED IN THE RUNTIME'S VI THREAD, NOT IN THE GAME AT ALL.**
> > `ultramodern/src/events.cpp:123,:139` — `vi_thread_func` ticks at a literal
> > `60`. `bossMainloop` waits on those messages and `waitForNextFrame` divides
> > real time into 1/60ths, **but neither can produce more than 60 ticks a
> > second because only 60 retraces arrive.** Every earlier costing — `92`,
> > `99`, `118`, `127`, `128` — looked only at game code. The clock is upstream
> > of all of it.
>
> **`speed_multiplier` is NOT the lever** — `constexpr 1`, and it scales the VI
> rate AND `counter_per_ms` together, so raising it is a fast-forward, not a
> frame rate. **The lever is the literal `60`, decoupled from the counter.**
>
> **And it CORRECTS `128`:** `bossMainloop`'s skip gate is a HALF-frame guard
> (8.28 ms) and passes 90 Hz retraces (11.11 ms) by arithmetic. `128`'s edit (b)
> is probably unnecessary. **`demoMode`'s multiplied variant is the one to
> watch.**
>
> **LICENCE, RULE 12:** `N64ModernRuntime` is GPL-3.0. **This edit is fine for us
> and is NOT upstreamable to RT64's MIT half.** First Route B edit to touch the
> boundary — record it in `PUBLISH-MANIFEST.md` when made.
>
> **RB-01c is next and needs no machine:** the VI thread's own comment says it
> is what lets the game generate **audio and gfx** lists. **If audio is paced
> per VI, a 90 Hz VI changes audio timing** — cheaper to ask now than to lose a
> wear test to it.
>
> ### WHY — `125`
>
> **The view path is now correct as far as it can be measured, and the head-turn
> artifact survives it.** `125` built R3 (each pass posed for
> `predictedDisplayTime + i * period`, `poseChg` 0 -> 91 after three builds of
> zero) and `126`'s previous-pose fix (`rt64_projection_processor.cpp:165` was
> multiplying BOTH the current and previous view by the SAME head pose, so
> velocity and motion vectors saw ZERO camera motion from head rotation — the
> comment above it had named that exact refinement and deferred it).
>
> **Worn: "it feels better... so much tighter now... but it's still absolutely
> happening."**
>
> ### AND A RETRACTION THAT CHANGES THE CONCLUSION
>
> **`124` §3 recorded T7 as exonerating RT64's interpolation. THAT IS VOID.**
> With `rr_option "Original"` the submit rate fell to **60 into a 90 Hz panel**,
> so the compositor was repeating frames — doubling by a different mechanism.
> The run could not have told us anything about interpolation. **Rule 10, and it
> is what kept the search on the view path all evening.**
>
> ### THE STRUCTURAL ARGUMENT
>
> **Panel 90 Hz, fixed. Sim 60 Hz, structurally (`92`). Sixty real frames on a
> ninety-hertz display has EXACTLY THREE treatments: repeat 30 (visible
> doubling — what T7 measured), interpolate 30 (what we do, now as good as we
> can make it), or MAKE THE SIM 90 (Route B).**
>
> > **`dupSrc` HAS READ 30/90 THROUGH EVERY BUILD TODAY** — stride fix, phase
> > fix, per-pass read, 90 Hz host refresh, display-time prediction, previous
> > pose. **Thirty frames a second are not real, and nothing we built touched
> > it.**
>
> **`119`'s gate CONFIRMED `118`'s model** — `delta=1 [1..1]`, `clk=1 [1..1]`,
> `gdelta=1000 [1000..1000]`, flat. **The foundation is verified.**
>
> **THE HONEST RESIDUAL:** interpolation could be IMPROVED rather than replaced.
> T7 was meant to test that and was confounded, and **a clean test is hard here
> — 60 into 90 cannot be 1:1 on a 90 Hz panel, so any "interpolation off" run
> introduces repeats instead. That is itself part of the argument.**
>
> ---
>
> ### ►►►► `124` — P1: THREE BUILDS, AND THE ANSWER IS A TIMING ONE. ◄◄◄◄
>
> **THE TARGET, RE-STATED BY THE OWNER AND NOT TO BE LOST AGAIN:** *"The judder
> happens when I turn my HEAD. The stick turn is just semi-satisfactory. I tried
> to make that clear a few times so we wouldn't just fall back to fixing the head
> turn and then settle for the 60 feeling of the world."* **`103`-`116` fixed
> the STICK half — the half he cares about least.**
>
> | Build | Change | `poseRefresh` | `posePP` | **`poseChg`** |
> |---|---|---|---|---|
> | `121` | workload re-reads pose per pass | — | 92 | **0** |
> | `122` | one pose per pass, both eyes (fixes `121`'s skew bug) | — | 92 | **0** |
> | `123` | host refreshes the pose at 90 Hz too | **91** | 91 | **0** |
>
> **BOTH HALVES CONFIRMED RUNNING AND `poseChg` IS STILL ZERO — and that is the
> ANSWER, not a plumbing failure.**
>
> > **The passes of one workload are RENDERED back-to-back in ~2 ms but
> > DISPLAYED 11.11 ms apart. The host refreshes every 11.11 ms. So every pass
> > of a workload falls inside ONE refresh interval and reads the identical
> > matrix.** We built a faster pipe and handed it the same water.
>
> **THE FIX IS "POSE EACH PASS FOR THE MOMENT IT WILL BE SHOWN"** — pass `i`
> wants the pose predicted for `predictedDisplayTime + i * displayPeriod`,
> located AT RENDER TIME. **That is `114` §3.2's R3, listed as owed and then
> skipped.** R1 already cleared it: `xrLocateSpace` takes an arbitrary future
> time and is not frame-ordered — how PD does it (`117` §1).
>
> **AND THE WEARER NAMED IT FIRST:** *"if I move my head in a circle motion I
> can see their reprojection going around them."* **A ghost that ORBITS is a
> FIXED-LAG signature.** `95`.
>
> ### EVERYTHING TODAY ELIMINATED — ALL WORN
>
> **RT64 INTERPOLATION: EXONERATED.** `rr_option "Original"`, genuinely off
> (`interpUsed=0`, `submits=60`), **ghost still present.** `92` cand 2 / `23`
> are not this. **STEREO: DEAD**, visible in each eye alone, D1 re-confirmed on
> this build. **IN-GAME DAMPING: DEAD** — the patch makes three host->game calls
> and **none carries head yaw or pitch**; `ge_vr_head_transform` is a pure
> quaternion-to-matrix, no filter, all axes identical. **OUR OWN FEATURES: DEAD**
> — artifact persists with them off.
>
> ### A CORRECTION I OWE — RULE 3, BROKEN BY ITS OWN AUTHOR AGAIN
>
> Fast tight shakes show nothing; slow wide turns separate. **I concluded
> latency was dead. WITHDRAWN.** A slow turn lets the eye SMOOTH-PURSUE, which
> resolves frame-to-frame error into a visible double image; a fast shake blurs
> it. **A property of how it is LOOKED AT, not of the mechanism.**
>
> ### THE TIMEBASE GATE PASSED — ROUTE B IS LIVE AND PARKED
>
> `timebase: delta=1 [1..1] | clk=1 [1..1] | gdelta x1000=1000 [1000..1000]` —
> **flat, exactly as `118` predicted. `118`'s model is CONFIRMED.**
> **Parked by owner decision, and the reason is sound:** *"I can't properly
> judge if Route B is needed if possibly my only issue is the head turn."*
> Fix the dominant variable, then re-judge.
>
> ---
>
> ### ►►►► `118` + `119` — ROUTE B IS A SLICE, NOT A PROJECT. THE INSTRUMENT IS BUILT. ◄◄◄◄
>
> **`118` costed Route B from the tree. `92` and `99` both over-costed it,
> because nobody had looked at what we already have.**
>
> | | Perfect Dark | GoldenEye | |
> |---|---|---|---|
> | Integer tick, 60ths | `lvupdate60` | **`g_ClockTimer`** | **EXISTS.** 152 refs; **5 writes, ALL in `lv.c`**, one of which is the delta |
> | Float tick, 60ths | `lvupdate60f` | **`g_GlobalTimerDelta`** | **EXISTS. 217 refs — MORE than the integer.** `lv.c:979` |
> | Remainder accumulator | `lvupdate240rem` | **MISSING** | **THE ONLY GAP** |
> | Zero-tick frames | supported | **34 guards already in the tree** | already handled |
>
> **THE CHOKE POINT IS TWO LINES** (`lv.c:974-979`) fed by ONE integer divide
> (`frametiming.c:82`) that discards its remainder. **`currentFrameCounter` is
> contained entirely in `frametiming.c/h` — 8 refs, it does not spread.**
>
> **THE UNIT NEVER CHANGES.** `g_ClockTimer` stays integer 60ths, so all 152 refs
> and every "N sixtieths" constant keep working. **`99` §4's headline cost — the
> hundreds of duration constants — evaporates, exactly as `117` §4.2 predicted.**
>
> **AND `92`'s AIM-FEEL OBJECTION IS DEFUSED AND BECOMES A CHOICE:** leave
> `crosshair_x_pos` on the integer and weapon feel is bit-identical to today.
>
> > ### **THE DE-RISKER: THE WHOLE FIRST SLICE IS TESTABLE AT `-NoXr` ON THE MONITOR. NO HEADSET, NO B3 REBOOT RISK, NO WEARER TIME. Nothing else in this project has had that property.**
>
> **AND IT DELETES, AT ONCE:** the duplicate frame, the per-pass head pose
> problem, the pose/image mismatch, and the partial-interpolation artefacts.
>
> ### `119` — T1-S0 IS BUILT. IT CAN KILL `118` BEFORE `118` IS BUILT.
>
> **Logs `speedgraphframes`, `g_ClockTimer` and `g_GlobalTimerDelta` with
> min/max, once per 90 frames, NOT gated on VR.** No behaviour change, no new
> patch name, short build.
>
> **G-119-1: at `-NoXr` 90, PREDICT all three FLAT with min == max. NOT FLAT
> means the game already receives a variable delta and `118`'s model is
> WRONG.** **G-119-2: `gdelta == clk * 1000` always, or the choke point is not
> two lines.**
>
> **It also carries the first reusable answer to `100`'s statics trap:** min/max
> cannot rely on `s6dofTick`'s luck, so init is keyed on a **magic sentinel**
> rather than on zero. Rule 13.
>
> **FALSE LEAD RULED OUT so nobody chases it:**
> `g_speedGraphCountAccumulator` (`speed_graph.c:66`) is the ON-SCREEN DEBUG
> GRAPH's counter, **not** a timebase accumulator. The name is the only thing
> about it that is relevant.
>
> **ROUTE B REMAINS THE OWNER'S CALL AND STAYS LAST RESORT UNTIL HE MOVES IT —
> but it should now be decided on `118`, not on `92`'s "structurally
> unavailable", which describes the timebase we have and not the one that is
> reachable.**
>
> ---
>
> ### ►►►► `117` — R4. PERFECT DARK NEVER SOLVED OUR PROBLEM. IT NEVER HAD IT. ◄◄◄◄
>
> **Read at `67ea20c`, MIT, no machine needed. And it reshapes the strategic
> picture without changing the owner's decision — Route B stays last resort
> until he says otherwise.**
>
> **THEIR VR FRAME LOOP IS ONE LINE OF ARCHITECTURE** (`pdmain.c:620-687`):
> `vr_begin_frame_and_update_poses()` -> **`lvTick()`** -> `lvRender()` ->
> `vr_end_frame_and_submit()`. **One sim tick, one render, one XR frame, in
> lockstep.** Their own comment: *"xrWaitFrame is the ONLY thing pacing the
> game's tick."* **No interpolator. No duplicate submissions. One head pose per
> rendered frame.**
>
> **SO R4's ANSWER IS: THEY DO NOT DO PER-PASS HEAD POSES — THERE ARE NO PASSES
> TO POSE.** P1 is not collapsed, but it is re-framed: **per-pass posing is a
> workaround for an interpolator that exists only because our sim cannot run at
> the display rate.** `114` §3's slicing stands; it is no longer "catching up to
> prior art".
>
> ### AND THE ONE STRUCTURAL DIFFERENCE THAT EXPLAINS EVERYTHING
>
> **Perfect Dark** (`lv.c:2233-2246`) — base unit **240ths**, and:
> ```c
> lvupdate60     = lvupdate240 + lvupdate240rem;
> lvupdate240rem = lvupdate60 & 3;      /* THE REMAINDER IS CARRIED */
> lvupdate60   >>= 2;                    /* integer 60ths, legacy constants intact */
> lvupdate60f    = lvupdate240 * 0.25f;  /* AND a float timestep */
> ```
>
> **GoldenEye** (`frametiming.c:46-53`) — `updateFrameCounters(s32 deltaFrames)`,
> integer accumulation, and `waitForNextFrame` divides `osGetCount` by 775875
> and **DISCARDS the fraction. There is no remainder accumulator anywhere.**
>
> > **PD CARRIES THE REMAINDER AND EXPOSES A FLOAT TIMESTEP. GOLDENEYE
> > TRUNCATES. THAT IS THE ENTIRE REASON THEY GET NATIVE 90 Hz AND WE NEED AN
> > INTERPOLATOR.**
>
> **AND NOTE 240 DOES NOT DIVIDE INTO 90 EITHER** (240/90 = 2.667). **The
> accumulator is what makes a non-divisible rate work.** `92`'s *"90 is not 60
> over an integer, therefore unreachable"* **is true of a truncating timebase
> and false of an accumulating one.**
>
> ### WHAT THAT DOES TO ROUTE B's COST — BOTH DIRECTIONS
>
> **WORSE: there is no migration to copy.** They never did one. `114` §3.2's
> hope that their tree held the timebase work is corrected — **Route B has a
> validated DESIGN there and nothing more.**
>
> **BETTER, AND LARGER: `99` §4's headline cost may not be real.** It named
> *"the hundreds of duration constants meaning N sixtieths"* as the main
> expense. **PD shows those do not change** — `lvupdate60` stays an integer
> count of 60ths and every constant keeps working. **The change is confined to
> how that integer is DERIVED.** `99` §4's other finding is the part to re-cost:
> 39 of 43 `g_ClockTimer` comparisons survive, four do not, and those four are
> named.
>
> **IT IS A READ, NOT A COSTING. Nobody has tried it.**
>
> ### THE QUESTION FOR THE OWNER
>
> **The judder line has spent `92` through `116` — fifteen documents — making a
> 60 Hz sim look like 90. The head-turn half is the next several. The same
> engine, one game later, gets it free by carrying a remainder.**
>
> > **IS ONE ACCUMULATOR IN `updateFrameCounters` PLUS FOUR NAMED `g_ClockTimer`
> > COMPARISONS CHEAPER THAN THE REMAINING INTERPOLATOR WORK — GIVEN IT ALSO
> > DELETES THE PER-PASS POSE, THE DUPLICATE FRAME AND THE PACING PROBLEMS AT
> > ONCE?**
>
> **Open, and the owner's to answer.** `117` §6.1 has the cheap next read that
> would cost it properly — no machine, no GPU.
>
> ---
>
> ### ►►►► `116` — O94 CLOSED. THE PHASE FAULT, MEASURED AND FIXED. ◄◄◄◄
>
> **The pick trace, on the clean rebuild, at 60 fps / 90 submits:**
>
> ```
> 1:0:03eb   1:0:03eb   0:1:839a     x8, every second, forever
> ```
>
> **Two consecutive presents take the SAME set, SAME pass, SAME pointer. One
> duplicate in every three presents — `dupSrc=30/90` to the digit, from an
> independently built counter.**
>
> **THE MECHANISM:** `105` published the eye set index as a free-floating atomic
> released at the **END** of the workload. **So the FIRST present of a workload
> reads the PREVIOUS workload's set and re-shows its pass 0.** At 60 into 90,
> `displayFrames` alternates 1/2, so the cycle is two workloads and three
> presents — and exactly one of the three lands before the new set is published.
>
> **AND IT RESOLVES `113` §4's THREE IRRECONCILABLE FACTS.** None was lying:
> `eye0=90` really renders ninety, `interpUsed=90` really picks ninety — it just
> never claimed they were DISTINCT. **Third instrument this week whose name
> promised more than it measured** (`reused`, `dupSrc` knob-off, now
> `interpUsed`).
>
> **THE FIX — `48` rule 8, remove the second source of truth.** The present
> thread already binds the workload's own `InterpolatedFrameCounters` and reads
> `count` from it to decide `framesToPresent`; **that phasing is demonstrably
> correct because `framesToPresent` is correct.** So `eyeSet` now lives beside
> `count` and inherits it for free. The count comes from the same place as the
> set, or the mismatch just moves.
>
> **KNOB-GATED: `-EyeSetPhase` (implies `-EyeInterp`).** `103`-`105` are three
> demonstrations that this synchronisation is easy to break, so `105`'s path
> stays reachable until the new one is worn.
>
> ### THE GATES — `TESTS-OWED-ON-RETURN.md`, TEST 1
>
> **G-116-1: `dupSrc` ~30/90 -> ~0/90. THE GATE.**
> **G-116-2: fps stays 60, submits stay 90.**
> **G-116-3: the trace stops repeating.**
> **G-116-4, WORN: DOES THE STICK TURN LOOK SMOOTH?** The only gate a log cannot
> answer. **And watch for `105`/`115`'s character misplacement — if `dupSrc`
> falls while characters go wrong, the fix is reading the wrong slot and that is
> a failure wearing a success's numbers.**
>
> **STILL THE STICK-TURN HALF ONLY.** `104` §2: the head pose is still sampled
> once per game frame. **If G-116-1 and G-116-4 pass, the duplicate-frame judder
> closes after fifteen documents and the head-turn half (`114` §3) becomes the
> whole remaining problem.**
>
> ---
>
> ### ►►►► `113` — THE STALL IS FIXED. THE JUDDER IS NOT. ◄◄◄◄
>
> **The wearer, on both builds: *"I ran both, they felt the same. Both did the
> same thing."*** And the number agrees with him.
>
> | | knob OFF | **knob ON** |
> |---|---|---|
> | fps / submits | 60.1 / 90 | **60.0 / 90** |
> | `interpUsed` | 0 | **90** |
> | **`dupSrc`** | **90/90 (VOID — §2)** | **30/90** |
>
> > **ONE SUBMISSION IN THREE STILL CARRIES THE SAME SOURCE TEXTURE AS THE ONE
> > BEFORE IT.** Exactly the 1-in-3 `93` predicted, measured properly at last,
> > **and unchanged from before `103`.**
>
> **`107` FIXED THE PIPELINE STALL — 60 fps and 90 submits where `103`-`105` got
> 16 — AND THAT WAS NOT THE JUDDER.**
>
> **G-112-1 FAILED AND THE REASON VOIDS THE BASELINE:** with the knob off the
> present thread samples **the same two `RenderTarget` objects forever** while
> their contents are rewritten every game frame, so the pointer never changes.
> **`90/90` means "this counter is blind on this build", not "ninety
> duplicates".** Only the knob-ON number is informative. `112` corrected.
>
> ### THREE FACTS THAT DO NOT RECONCILE — AND NO STORY IS OFFERED
>
> **`eye0=90` rendered. `interpUsed=90` consumed. `dupSrc=30/90` repeat.**
> Ninety published, ninety consumed, thirty repeats. **Nothing here says which
> one is lying, and `106` §2's whole criticism of this project is that
> `103`/`104`/`105` each built a story on the last one's framing. A fourth would
> be the same mistake.**
>
> **THE MEASUREMENT THAT SETTLES IT, NO HEADSET, ~10 LINES:** log the actual
> `(set, pass)` pair every present consumes, for one second.
> **No consecutive repeats -> `dupSrc` itself is wrong**, which after today is a
> live possibility and goes first. **Same pair twice -> a publish/consume phase
> fault.** **Ninety distinct pairs yet dupSrc 30 -> something DOWNSTREAM
> collapses them.** Each outcome names a different file.
>
> ### WHAT SURVIVES
>
> **The stall fix. `109`'s ~1-in-6 late frames, intermittent, still the best
> lead on the FEEL. And `ds_option 2` — free, kills the distant shimmer, the one
> shippable win of the day and independent of everything above.**
> **The HEAD-TURN half has never been addressed at all** — `104` §2. All of
> `103`-`113` is the stick-turn half.
>
> ---
>
> ### ►►►► `111` — IT WORKS. 60 fps, 90 SUBMITS, `interpUsed=90`. ◄◄◄◄
>
> **Built, compiled, run. `107` + `109` + `110` in one build, four logs kept.**
>
> | | knob OFF | **`-EyeInterp`** | `103` | `104` | `105` |
> |---|---|---|---|---|---|
> | fps | 60.0 | **60.0** | 16.3 | 25.7 | 16.3 |
> | submits/s | 90 | **90** | 13 | 13 | 13 |
> | `xrWaitFrame` | 9.11 ms | **9.27 ms** | 75.40 | 73.64 | 75.35 |
> | `interpUsed` | 0 | **90** | n/a | 13 | 11-12 |
>
> **`105` WAS RIGHT AND ONLY ITS ARITHMETIC WAS WRONG.** The stride fix carried
> it. **`106` §2's "the handover is not the problem" is POSITIVELY FALSIFIED —
> it was exactly the problem.** G-107-4 passes: the knob-off build is unchanged.
>
> ### AND THE FINDING THAT MATTERS MORE THAN THE FIX
>
> **`reused` reads 30, not 0 — and that is not a failure, because the instrument
> never measured what four documents thought it did.**
> **`renders` is `g_renderCount`, incremented in `publish_render_pose` on the
> GAME THREAD once per game frame** (`rt64_render_context.cpp:1609`). So
> **`reused` is just `submits − game frames`, pinned to 30 by arithmetic at a 60
> sim submitting at 90.**
>
> > **SO `103`/`104`/`105`'s CELEBRATED "reused 30 -> 0, THE MECHANISM IS REAL"
> > WAS THE CLAMP FIRING BECAUSE submits COLLAPSED TO 13, BELOW renders=60.**
> > **THEY WERE READING THEIR OWN STALL AS THE SUCCESS SIGNAL, THREE TIMES.**
> > `106` §4 item 3 is RETRACTED.
>
> **And `93`'s G93-2 — "count submissions reusing an unchanged image" — WAS
> NEVER BUILT.** What exists produces 30 by coincidence and has been quoted as
> confirming the prediction ever since. **`49`'s "two instruments cannot fail",
> third instance. Rule 4.**
>
> **SO THE DUPLICATE FRAME IS UNMEASURED.** `interpUsed=90` is the best evidence
> we have and it is the SAMPLING side, not the submitted side. **A real
> duplicate-image counter is OWED — compare `vrPresentSource[eye]` against its
> previous value at submit time. Until it exists nobody should say the
> duplicate frame is fixed.**
>
> ### `109` EARNED ITSELF ON ITS FIRST RUN
>
> **Baseline: mean frame 10.27 ms under an 11.11 ms budget — comfortable. Max
> 11.81-12.30 ms, `LATE 16/91 (18%)`.** **One frame in six misses the display
> deadline on the build the wearer plays, and `72`'s means could never have
> shown it.** `73` predicted it fourteen documents ago. **And it is
> INTERMITTENT** — other samples in the same run read `LATE 0/60`. **That is a
> hitch pattern, not a throttle.** The interp build is no worse: 16%.
>
> ### O89 ANSWERED: SUPERSAMPLING IS FREE
>
> **`ds_option 2`, knob off: 60 fps, 90 eye passes, `LATE 11/91 (12%)` — BETTER
> than baseline.** **`49`'s O22 did not reproduce.** With `108` §3's confirmed
> shimmer fix, **O90 now has a diagnosis, a lever, and a measured zero cost.
> RECOMMEND `ds_option 2` AS THE DEFAULT.** `msaa_option` stays `"None"`.
>
> ### DO NOT OVER-READ `posecheck MAX delta`
>
> 0.09-0.12 baseline, 0.23-0.48 interp, 0.65-0.78 at ds2. **It is a MAX over
> whatever the wearer did and scales with head movement. Three runs with three
> different amounts of movement are NOT comparable.** Rule 3.
>
> ### WHAT IS NEXT
>
> 1. **WEAR IT. Nobody has.** Every number above is from a log, and the question
>    that decides whether any of it mattered — **does the stick turn feel smooth
>    now** — has not been asked.
> 2. **Build the real G93-2 duplicate-image counter.**
> 3. **THE HEAD-TURN HALF IS STILL OPEN.** `104` §2: the head pose is still
>    sampled once per game frame. **`107` bought the PREREQUISITE — there is now
>    a published per-pass render to put a fresh pose into. That is the slice.**
> 4. **Route B / the timebase is NOT needed for this.** `99` §4 stays parked.
>
> ---
>
> ### ►►►► `110` — O85 IS BUILT. THE TEST NOBODY RAN FOR FOUR ATTEMPTS. ◄◄◄◄
>
> **`103`/`104`/`105` each changed the sampled texture AND the pass count
> together, then reasoned as though only one had moved.** `-EyeSampleTest`
> changes **the sampled texture ALONE**: pass 0, a real frame, alternating
> between the two eye target sets on consecutive presents. No extra passes,
> nothing extra rendered.
>
> **It alternates on the PRESENT ORDINAL, not the loop index** — indexing on `i`
> would not alternate at all on a `displayFrames == 1` workload, and that is
> precisely the assumption that broke `105` (`107` §2).
>
> **It implies `-EyeInterp` and the switch sets both**, because without that
> allocation the two sets are the same two textures and there is nothing to
> alternate between — `32`'s shape otherwise.
>
> **G-110-1: `sampleAlt=` must be NON-ZERO or nothing measured counts.**
> **G-110-2: STALLS -> the cost is the texture change and passes were never
> relevant. DOES NOT STALL -> the pass path is implicated.**
>
> **PREDICTION, ON THE RECORD BEFORE THE RUN: it does NOT stall.** `107` §1
> found no mechanism by which a changed texture costs anything. **A stall would
> contradict that read and would be the most interesting result in the whole
> `103`-`110` sequence.**
>
> ---
>
> ### ►►►► `109` — O74 IS BUILT. OUTSTANDING SINCE `73`. ◄◄◄◄
>
> **`72`'s "the submit loop is exonerated" measured MEANS, and a mean cannot see
> a hitch.** The loop was cleared of being SLOW and never cleared of being
> IRREGULAR. **Four maxima and a late count now print BESIDE the means** —
> the comparison is the instrument: max/mean near 1 is smooth, max/mean several
> times over is hitching. `LATE` counts frames over **the runtime's own display
> period**, and prints `n/a` rather than `0` when the period is unknown, because
> a zero there looks exactly like a perfect session.
>
> **RUN IT WITH G-107-2.** `106` §1's `xrWaitFrame 75.40 ms` is a mean, and
> *"every frame waits 75 ms"* versus *"one frame in eight waits 500"* are
> different faults with different fixes that we currently cannot tell apart.
>
> **Pure diagnostic, no behaviour change, no new patch name, short build.**
> Backup `ge_vr_xr.cpp.bak109`.
>
> ---
>
> ### ►►►► `108` — LAST NIGHT'S SESSION, RECOVERED. IT FALSIFIES A LINE IN `107`. ◄◄◄◄
>
> **Reconstructed from the owner's transcript of a session that hit a budget
> limit before anything was written up. Two results were about to be lost.**
>
> **1. `106` §7.2 IS CLOSED. THE GUARD WALK WAS RUN, KNOB OFF: *"The characters
> are ok."*** **The default build is CLEAN and the misplacement is OURS — it
> fires only with `GE_VR_EYE_INTERP=1` and it is in the eye target MODIFIER
> change that `104` and `105` made.** `103` never touched it. **`107` §2 is
> very likely its cause rather than a separate fault, and G-107-2 tests both at
> once.**
>
> **2. TWO WEARER REPORTS, AND THEY ARE NOT THE SAME FAULT.**
> **The doubling** (distant characters and mountain edges double the same way on
> head movement) **is the duplicate frame, NOT the upscaler**: monocular (D1),
> motion-dependent, and measured — `reused=30/s`. A head rotation moves
> everything across the retina by the same angle regardless of distance, which
> is why near and far double identically; a resolution artefact would not.
> **The head glitches and flicker are a DIFFERENT and NEW fault: there is no
> antialiasing at all under VR.** MSAA is forced off (`43`) and `ds_option` was
> `1`, so a 320x240-era game is drawn at 5838x4498 with zero edge filtering.
>
> **3. AND THE TEST WAS RUN AND IT PASSED.** `ds_option 2`, `msaa_option` still
> `"None"`, backup `graphics.json.bak-preDS2`. The owner, worn: *"It just
> smooths out the distance."* **Supersampling removes the shimmer, so the
> shimmer WAS aliasing. Diagnosis confirmed, lever known.**
> **BUT THE FPS LINE WAS NEVER READ** — the bridge dropped — **so its GPU cost
> is unmeasured, and `49`'s O22 (8x fewer pixels ran 4x SLOWER) lives in exactly
> this territory. O89.**
>
> **4. IT FALSIFIES `107` §1's DOWNSAMPLE LINE, WRITTEN THE NEXT MORNING.**
> `107` said the downsample is a no-op because `ds_option` is `1`. **It read the
> value out of `00-START-HERE`'s environment table instead of off the disk —
> `48` item E exactly.** At `ds_option 2` the branch IS taken: **a compute
> dispatch per eye per present, on the path G-107-2 measures.** Corrected at
> source. **Every other elimination in `107` §1 stands.**
>
> > ### **SO PIN `ds_option` BEFORE RUNNING G-107-2.** `103`-`106` were all
> > measured at `1`. Run at `1` first for the only like-for-like comparison, then
> > at `2` if you want the supersampled number. **And re-check the file after any
> > in-game menu visit — the menu rewrites it.**
>
> ---
>
> ### ►►►► `107` — `105`'s DOUBLE BUFFER WAS NEVER A DOUBLE BUFFER. ◄◄◄◄
>
> **A read session. No launches, no headset. Two negatives and one fix.**
>
> **1. `106` §6 MOVE 2 IS DONE AND ITS SUSPECT IS ELIMINATED.** The whole
> sampling path was read. The resolve and the downsample are genuine no-ops
> (MSAA off → `resolvedTexture == nullptr` → `usesResolve()` false; `ds_option 1`
> → `downsampleMultiplier == 1`). The descriptor set is rebuilt only when the
> SAMPLER changes, never the texture. And `setSRV` → `CreateShaderResourceView`
> plus the shader-visible heap copy in `setDescriptorSet` run **unconditionally,
> every present, with no comparison against what was there before.**
> **NOTHING IN THAT PATH IS CONDITIONAL ON `params.texture` HAVING CHANGED, so
> `106` §6's "the cost is in changing the sampled texture" has no mechanism.**
>
> **2. AND THE ACTUAL DEFECT, FOUND WHILE LOOKING FOR SOMETHING ELSE:**
>
> ```cpp
> const size_t eyeTargetsPerSet = size_t(displayFrames) * 2;   /* :1263 */
> const size_t eyeTargetIndex   = (eyeWriteSet * eyeTargetsPerSet) + frame*2 + eye;
> ```
>
> **`displayFrames` IS RECOMPUTED EVERY WORKLOAD** (`:1130`) and at 60 into 90
> **it alternates 1, 2, 1, 2.** So set 1's base MOVED — index 4 on a two-frame
> workload, index **2** on a one-frame workload. **A `displayFrames == 1`
> workload writing "set 1" wrote targets 2 and 3, which are SET 0's pass-1 pair,
> the one the present thread was reading.** The double buffer was defeated on
> roughly every other frame.
>
> > **SO `105`'s NEGATIVE RESULT IS NOT EVIDENCE — `48` RULE 4 — AND `106` §2's
> > "THE HANDOVER IS NOT THE PROBLEM" RESTS ENTIRELY ON IT.**
>
> **3. THE FIX IS BUILT, NOT COMPILED.** A FIXED stride
> (`(VR_EYE_PASS_MAX + 1) * 2`), so the sets are disjoint for every
> `displayFrames`, plus a clamp so a large `displayFrames` cannot run off the end
> of its set. **It costs nothing: `RenderTarget`'s constructor allocates no GPU
> memory (`rt64_render_target.cpp:23`) — textures are lazy — so the number that
> actually ALLOCATE is unchanged.** That answers `106` §5's VRAM objection.
> **`GE_VR_EYE_INTERP=0` is still an exact identity.**
>
> **4. AND THE PRESENT THREAD'S STRUCTURE IS NOW WRITTEN DOWN** — `107` §3.
> **`submitFrame()` RUNS ON RT64's PRESENT THREAD**, so one iteration is strictly
> serial: eye blits → `executeCommandLists` → **`presentGraphicsWorker->wait()`,
> a CPU block on the GPU fence** → `xrWaitFrame` → copy → `xrEndFrame`. And
> **`workloadGraphicsWorker` and `presentGraphicsWorker` are TWO INDEPENDENT
> `ID3D12CommandQueue`s with no cross-queue GPU synchronisation anywhere** — they
> share only the CPU-side `interpolatedMutex`.
>
> ### THE GATES — TWO NEED NO HEADSET
>
> ```powershell
> .\build.ps1
> .\vr.ps1 -UnitsPerMetre 50 -SeamNoRot -HandPosZ 1 -EyeInterp
> ```
>
> **G-107-1: `interpUsed=` still reads ~1/3 of `submits`. ZERO means the pass
> path stopped and nothing else is judgeable.**
> **G-107-2: `reused` ~0 AND `submits` toward 90 AND fps toward 60. THIS IS THE
> WHOLE EXPERIMENT.** Pass → `105` was right and only its arithmetic was wrong,
> and Route D is alive. Fail → `106` §2 is finally supported by an experiment
> that actually ran, and `106` §6 move 1 is next.
> **G-107-4: a knob-OFF launch is unchanged. `106` §7.2's guard-walk check
> batches here.**
>
> **KNOW WHAT IT CANNOT DO:** the head pose is still sampled once per game frame.
> **`posecheck`'s `MAX delta` will not go to zero and head turn may not improve.**
> Stick turn is the half this addresses.
>
> **STILL OWED, IN ORDER:** `106` §6 move 1 (still unapplied after four
> attempts, and §1 above makes it MORE worth running); the per-present stage
> timer (**O74**, and `107` §3 says where the probes go); then `23`.
>
> ---
>
> ### ►►►► `104` — AND IT IS BUILT. TEST THIS ONE. ◄◄◄◄
>
> **`103`'s naive publish was RUN and it measured beautifully in one direction:**
> **`reused` 30 -> 0** (the mechanism is real) **and fps 60 -> 16, `xrWaitFrame`
> 9 ms -> 75 ms.** `103` §4 predicted the hazard and predicted the wrong symptom:
> **a stall, not a bugcheck.** No reboot was spent.
>
> **`104` fixes it by NOT inventing a rendezvous.** The present queue already
> walks the passes in lockstep under `interpolatedCondition`
> (`rt64_present_queue.cpp:270-296`), and its loop index `i` maps 1:1 onto the
> workload's `frame`. **So the eye targets are indexed the same way and inherit
> the same guarantee. `48` rule 8, and `46` fixed the recentre with this exact
> move.**
>
> **THE TEST NEEDS NO HEADSET FOR ITS FIRST TWO GATES:**
>
> ```powershell
> .\build.ps1
> .\vr.ps1 -UnitsPerMetre 50 -SeamNoRot -HandPosZ 1 -EyeInterp
> ```
>
> **G-104-1: `interpUsed=` on the `render passes:` line should read ~30/s.
> ZERO means it is not running.**
> **G-104-2: `reused` -> ~0 AND `submits` stays ~90 AND fps stays 60.** `103`
> got the first and destroyed the other two; **that gate is the whole
> difference.**
>
> **`GE_VR_EYE_INTERP=0` is an exact identity — the legacy frame-0 pointer is
> still published and still the fallback.**
>
> **AND KNOW WHAT IT CANNOT DO:** the head pose is still sampled once per game
> frame, so `posecheck`'s `MAX delta` will not go to zero and **head turn may not
> improve.** Stick turn is the half this fixes. **`104` is what makes a per-pass
> head pose possible later — before it there was nowhere to put one.**
>
>
> ---
>
> ### ►►►► AND THEN `103` LANDED. READ IT BEFORE `99`. ◄◄◄◄
>
> **`rt64_workload_queue.cpp:1352`:**
>
> ```cpp
> if (vrStereo && (frame == 0) && (eyeTarget != nullptr)) {   /* <- frame == 0 */
>     vrEyeZeroTarget.store(eyeTarget); vrEyeOneTarget.store(eyeTarget);
> }
> ```
>
> **RT64 RENDERS THE EYES FOR EVERY INTERPOLATED PASS. WE PUBLISH ONLY THE
> FIRST. The rest are rendered, completed and DISCARDED.** The eye loop sits
> inside `for (frame = 0; frame < displayFrames; frame++)` with its own
> per-pass target.
>
> **That is `submits=90 renders=60 reused=30` exactly. Not a GPU limit, not the
> sim — a publish guard.**
>
> **SO `99` §3's GATE IS MOOT AND `99` §5's ORDER IS CORRECTED.** Route D does
> not need a costing: **the re-render is already happening and already paid
> for.** O22 stays open and stays interesting; it is no longer a blocker.
>
> **BE PRECISE ABOUT WHAT IT FIXES** — `103` §3. Publishing them gives ~90
> distinct images of **world** motion, so the duplicate-frame judder goes.
> **The HEAD pose is still sampled at 60**, because interpolation lerps the
> game's transforms and does not know the head moved. **But it turns the head
> problem from impossible into plumbing: once a per-pass render is published
> there is somewhere to put a freshly located pose. Today there is nowhere,
> because the pass is thrown away.**
>
> **THE RISK IS LIFETIME, NOT RENDERING** — `103` §4. The
> `interpolatedMutex` handshake exists so the workload queue cannot reuse a
> target the present thread is still reading, and **the eye targets are outside
> it today, safe only BECAUSE of `frame == 0`.** Remove the guard and that
> argument goes with it. **`29`'s shape, and the likeliest way to make a new
> `0x139`.**
>
> **G-103-1 IS ALREADY IN THE TREE:** `posecheck` prints `renders` and `reused`.
> **The first launch can be judged from the log with the headset still on the
> desk.**
>
>
> ---
>
> # ►►►► 2026-08-24. READ `102`, THEN `99`, THEN `101`. ◄◄◄◄
>
> **Four things happened. Two are findings, one is a decision, one is a fault
> that had been silently costing this project instruments for its whole life.**
>
> ### 1. THE JUDDER IS NAMED, THE FIX WORKED, AND THE OWNER REJECTED IT — `98`
>
> `97`'s rotational timewarp ran correctly (`applied=182/s`, both eyes,
> correction tracking head speed) and **made it worse, then better once aimed
> right — and it is retired ON PURPOSE:** *"I don't even use these features in
> other VR because I notice them. I want a pure smooth experience, not an
> emulator type feel."* **A reprojected frame is a guess and the wearer can see
> guesses. Do not relitigate this.** `-Timewarp` / `-TimewarpYaw` stay as
> **diagnostics** — the motionless yaw test reads a pose convention without
> anyone turning their head.
>
> ### 2. THE REAL TARGET, RESTATED — `99`
>
> **The judder is not the game simulating at 60. It is THE VIEW being sampled at
> 60.** `renders=60` in every `posecheck` line. World animation at 60 has never
> been complained about; the head pose at 60 is the whole complaint.
> **So the target is "make the VIEW update at 90", and running the game at 90 is
> only one way to do that.**
>
> **ROUTE D, uncosted until now: render 90 REAL frames of a 60 Hz world.** Not
> warped, not blended. **It lives or dies on ONE read — what a full-resolution
> eye re-render costs, and what `49`'s O22 is.** Do that read first.
>
> **And `92` §4's route B is re-costed from the tree:** of 43 literal
> comparisons against `g_ClockTimer`, **39 are against ZERO and survive
> untouched; FOUR do not** and are named in `99` §4. **The real cost is the
> hundreds of duration constants meaning "N sixtieths of a second", which `92`
> missed** — `99` §4.1 has the fractional-tick variant that avoids them.
>
> ### 3. **EVERY PATCH PRINT IN THIS PROJECT HAS GONE NOWHERE — `100`**
>
> `recomp_printf` lands in `recomp_puts`, which `fputc`'d to **stdout** on a
> `/SUBSYSTEM:WINDOWS` build with no console. **Written and discarded, always.**
> `ge_vr_host.h` says so in its own header comment about the HOST logger; nobody
> checked the PATCH side. **Fixed: `recomp_puts` now tees into `gevr.log`.**
>
> **Two more, and they outlive S0:**
> **(a) `_Printf` carries the FIRST call and then stops** — the four after it
> emitted only their newlines. **(b) A `static` in `RECOMP_PATCH` code CANNOT be
> assumed zero.** `s6dofTick` has been trusted since `91` and only ever worked
> because `x++ % 90 == 0` comes true from any start value. **Luck, not design.**
> **S0 now emits through `recomp_puts` with a hand-rolled formatter: no varargs,
> no `_Printf`, no statics — and the falsifiers print FIRST.**
>
> **ALREADY WON: `A40 = -1000`. `90`'s falsifier 2 CONFIRMED** against
> `initBondDATA.c:114`'s +1000. **`muzzleExt` is the last one unread.**
>
> ### 4. **PERFECT DARK'S NUMBERS ARE NOW OURS — `102`**
>
> **`86` copied their DESIGN and not their VALUES**, so nine slices were
> specified to re-derive what they had already measured. **Their tree is read
> again at `67ea20c` and `102` has the constants.** MIT; attribution owed.
>
> **AND IT CONTAINS A CORRECTION THAT CHANGES A1 AND A2: `86` §3.8's "PD keeps
> the clamp" IS FALSE. They clamp the DRAWN CROSSHAIR and leave THE BULLET AIM
> UNCLAMPED** (`bondgun.c:8419-8422` vs `:8468-8472`). **That is exactly the
> "break the lock" the owner asked for, and prior art ships it.**
>
> **Also confirmed verbatim:** the `x / (1 - damp)` inversion for **both**
> integrators; `{w,-x,y,-z}` plus a **1.5708** rad X offset (its own comment
> says "1.0 rad" and is wrong); grip offsets **`(0,16,-4)` default, `(-4,16,+8)`
> rifles** — **in `bondgun.c:6286-6320`, not `vr_input.cpp`, and in an Ry180
> basis, so copying the numbers alone mirrors the gun about the grip.**
>
> **G2 becomes a CHECK instead of a sweep. G3 becomes a table to VERIFY. A2 may
> not be mandatory after all.**
>
> ### AND ONE ANSWERED BY THE OWNER, SO NOBODY RE-ASKS IT
>
> **`101` A1-R3 is CLOSED.** Aim mode disabling look-ahead, natural turn and
> swivel is **not a problem** — *"that's not a problem because you're in the
> shooting position now."* **It is a stock GoldenEye feature players already
> understand: hold to aim, release to move.**
>
> ### THE NEXT SESSION, IN ORDER
>
> 1. **O22 / R2** — what a full-res eye re-render costs. **Decides whether
>    smooth is a knob or a project.** No headset.
> 2. **One in-level launch** closes `muzzleExt` — batches with anything.
> 3. **Then A1** with `102` §1's correction and `101` §6's design.

>
> ---
>
> # ►► START HERE: `96` IS THE PLAN. COMFORT BLOCKS EVERYTHING. ◄◄
>
> **The owner: *"it's pointless building all this extra stuff if you're just gonna
> get sick when you're playing it."*** `86`'s nine 6DoF slices are PARKED.
>
> **THE ONE FACT THAT SURVIVES EVERY DESCRIPTION:**
>
> > **STICK TURN IS CLEAN. HEAD TURN IS NOT.** At comparable angular speeds.
> > Both rotate the world across the retina; only one is bad. **That localises the
> > fault to the HEAD POSE PATH and depends on no adjective and no metaphor.**
>
> **A separate, lesser fault, do not conflate:** stick turn *"feels not ninety
> hertz"* — that is `92`, the 60 sim interpolated to 90, and **fixing the head
> turn will not fix it.**
>
> **PHASE 0 IS FREE AND COMES FIRST — thirty seconds of wearing, no build:**
>
> 1. **Close ONE EYE while turning fast.** Doubling gone -> **STEREO**, and `93`
>    is looking at the wrong half of the pipeline. Remains -> temporal.
> 2. **Stop dead mid-turn.** Clears -> motion-driven. Static double -> stereo
>    geometry that every static measurement in this project would have missed.
> 3. **Record the mirror** (`47`'s method). Mirror smooth + lenses bad -> the
>    images are right and the POSE is wrong. Mirror bad too -> **`93` is DEAD**.
>
> **PHASE 1: O79 — does Pimax OpenXR 0.1.0 reproject at all?** A read, not an
> experiment. **The fix CHANGES depending on the answer, so the answer comes
> first.**
>
> **PHASE 2: the build is already written and never compiled** — S0 (`91`), the
> `posecheck` instrument, and `GE_VR_POSE_LAG` (`94` T4, defaults 0 = identity).
> **`-PoseLag 4` should be much worse on HEAD turns and do NOTHING to stick turns.
> No change KILLS `93` whatever anyone felt.**
>
> **PHASE 3: the fix is chosen by what 0-2 said. `96` has the decision table.
> Nothing is pre-committed.**
>
> **`93` is CANDIDATE 4, not the answer** — `94` walks back its over-claiming,
> which the owner caught rather than the protocol.
>
> ---
>> # ►► THE JUDDER HAS A CANDIDATE AND A TEST. READ `94`, THEN `93`. ◄◄
>
> **NOT a conclusion. `93` was written as one and `94` walks it back** — at the
> owner's insistence, and he was right: *"we can't just change routes off what I
> said, what if I was wrong."*
>
> **The wearer reported: no judder standing still; EVERYTHING judders together
> above a speed threshold; no worse when the scene is busy.** That RE-RANKS
> `92`'s three candidates. **It does not eliminate them** — and **`92` question
> 1 eliminates nothing at all**, because a static scene cannot judder under any
> hypothesis. `48` rule 2 turned on the question: **a question every candidate
> answers the same way is not a gate.**
>
> **CANDIDATE 4, and the only one with a confirmed structural defect behind
> it** — the pose we submit is not the pose the image was rendered from:
>
> ```cpp
> xrLocateViews(...views);                       /* ge_vr_xr.cpp:1258 — THIS tick */
> g_cmdList->CopyTextureRegion(...source...);    /* :1518 — whatever RT64 last made */
> projViews[eye].pose = views[eye].pose;         /* :1533 — OLD image, NEW pose */
> ```
>
> **WE TELL THE COMPOSITOR THE IMAGE WAS RENDERED FROM A POSE IT WAS NOT
> RENDERED FROM.** Reprojection exists to warp a stale image to the true display
> pose — **so by handing it the CURRENT pose we tell it no correction is needed,
> and it applies none.** We are not failing to correct the error; **we are
> disabling the mechanism that would have.**
>
> **And at 60 rendered into ~90 presented, roughly one submission in three
> reuses an unchanged image and gives it a NEWER pose** — one image, two claimed
> viewpoints. On a fast turn that is a step back then forward.
>
> **`47`'s mirror table row 2 is this fault, written down before we knew we had
> it: *mirror right, lenses wrong = the images are right; the pose submitted
> with them is wrong.*** **The no-code falsifier is one mirror recording.**
>
> **`28`'s "one-frame staleness" has been documented since Phase 2. What is new
> is that it is THE JUDDER.**
>
> **TEST IT BEFORE BELIEVING IT — `94` §3. Four tests, none of which depends on
> a description:**
>
> | | |
> |---|---|
> | **T1** | **The mirror recording. NO CODE, NO BUILD, ~10 min.** `47`'s method: a mirror shows the IMAGE and never the metadata. **Mirror smooth + lenses juddering = the pose is wrong. Mirror juddering too = `93` is DEAD** |
> | **T2** | **G93-1**, the angular delta rendered-vs-submitted, **max not mean**. PREDICT non-zero, growing with head speed. **~0 kills it** |
> | **T3** | **G93-2**, reused-image count. PREDICT ~1 in 3 |
> | **T4** | **`GE_VR_POSE_LAG=N` — THE DECISIVE ONE.** `56`'s method: alter the thing on purpose. **N=4 should be dramatically worse on fast turns only. NO CHANGE AT N=4 KILLS `93` outright, whatever anybody felt.** Defaults to 0 = exact identity |
>
> **Also unchecked and it could make `93` wrong while every fact in it stays
> true: does the Pimax runtime reproject anyway?** `49`'s shape — *a* cause, not
> *the* cause. Twelve plausible mechanisms have been falsified here; `49` killed
> five in one session.
>
> ---
>
> # ►► PRIORITY CHANGED 2026-08-23: COMFORT OUTRANKS FEATURES. `92`. ◄◄
>
> **Raised by the owner: a build that makes the wearer sick is not shippable
> however many slices it has.**
>
> **THE 90 Hz ANSWER, from source: the game's timestep is quantised to a WHOLE
> number of 1/60 s ticks** (`frametiming.c:75`, `speedgraphframes`, consumed by
> `g_ClockTimer` and every timer in the engine). **It can run at 60, 30, 20, 15
> — it CANNOT run at 90 on any hardware, because 90 is not 60 over an integer.**
> **This is not a performance limit and no amount of PC moves it.** 90 in the
> headset is 60 of GAME through an interpolator, and `64` proved the
> interpolator is load-bearing.
>
> **AND THE SIM IS ALREADY HOLDING 60.** Measured from `gevr.log`, 149 samples,
> zero cost: **142 at >=59**, 5 dipping, **1 near half**, 1 on a load.
> **So `73`'s "the VI clock halves in heavy scenes" is REAL BUT RARE — one
> sample in 149 — and cannot be a judder that is felt constantly.**
>
> **Three ranked candidates, each with a falsifier, in `92` §3.** The new
> favourite is the **2:3 cadence** (60 into 90 is film-pulldown judder) or
> **partial interpolation** — and `23`, *"explosion effects stick to the view
> when turning"*, is a KNOWN WORKED INSTANCE of the second, open since Phase 1
> and never connected to judder. **`23` is promoted.**
>
> **THE CHEAPEST THING IN THE PROJECT — `92` §6, three wearer questions, one
> launch, no code, and they separate all three candidates:**
> **(1)** stand still, look at a wall — does it judder? **(2)** turn your head:
> does the GUN step against a smooth world, or do they judder together?
> **(3)** constant, or worse when busy?
>
> **Route A — keep the 60 sim and fix the interpolation — is the only route
> compatible with `86`.** Changing the quantum to 1/90 would change the aim feel
> of every weapon, because `crosshair_x_pos` steps once per `g_ClockTimer`.
>
> ---
>
> # ►► S0 IS BUILT AND NOT YET WORN. `91`. BUILD, THEN WEAR IT. ◄◄
>
> ```powershell
> cd C:\Users\pdbar\Desktop\GoldenEye64Recomp
> .\build.ps1                                          # SHORT path - NO new patch name
> .\vr.ps1 -UnitsPerMetre 50 -SeamNoRot -HandPosZ 1     # then F9 WHILE WEARING IT
> taskkill /F /IM GoldenRecomp.exe                      # NEVER the X - B3/B4
> .\vr.ps1 -NoXr                                        # the regression that must not break
> ```
>
> **The reads `86` §8 owed are ALL DONE — `87`, `88`, `89`, `90`. S0 is written
> and compiles nowhere yet: `48` rule 11, nothing is DONE until it is WORN.**
>
> **Six gates, and two of them are falsifiers that decide other slices:**
> `muzzleExt` **must be > 0** and `A40` **must be < 0** — if either fails,
> `88` §5.1's aim-axis reasoning inverts and G2/A1 change. `90`, `91`.
>
> **Next after S0 is worn: H1**, the recentre at level start. `86` §6.
>
> # ►► THIS SESSION'S JOB IS 6DoF. READ `86` BEFORE ANYTHING ELSE. ◄◄
>
> **`86-6DOF-PLAN.md` is the plan for every 6DoF aspect in this project — head
> position, head rotation, recentre, body yaw, roomscale, scale, the hand, the
> gun, and the bullet — and it is derived from Perfect Dark's actual VR source,
> read at commit `67ea20c`, with a file and line for every claim.**
>
> **Perfect Dark is the SAME ENGINE and its VR port is MIT.** `81` said the VR
> code was not public. **That is FALSE and is corrected in `86` §0** — it is
> public, it is complete, and `86` was written against it rather than against a
> summary of it.
>
> | Read, in this order | Why |
> |---|---|
> | **`86` §2, THE FRAMES** | **Nearly every hand and head fault this project has had was a frame error wearing a different costume.** Their controller pose is located against the **VIEW space**, not the play space, which is the one structural difference between their placement and ours |
> | **`86` §4, WHAT IT CORRECTS** | **Six claims in our own docs are falsified there**, including two in `82` and one in `76`. Rule 10 |
> | **`86` §5, THE SLICES** | Gates written before the code. **Slice 0 is an instrument and it ships first** |
> | **`86` §8, THE READS OWED** | Six reads. **None is an experiment.** Do them before, not during |
>
> **The three findings that change what gets built:**
>
> 1. **`38`'s aim inversion is CONFIRMED by independent prior art.** PD writes
>    `crosspossum = x_ndc / (1 − crossdamp)` (`bondgun.c:8408`); `38` derived the
>    same expression from GoldenEye's source alone. **And our counterpart
>    function, `caclulate_gun_crosshair_position_rotation` (`gunfire.c:4666`),
>    is about 85 lines — `RECOMP_PATCH`-able**, which `78` could not say about
>    `gunUpdateAndFire`.
> 2. **The aim clamp is not escaped by anyone.** `76` offered three answers to
>    "what happens past the clamp" and said none was chosen. **PD chose none of
>    them** — they keep the clamp and answer the gap with a **world-space laser
>    dot**. **O64 is therefore the mechanism, not decoration.**
> 3. **Head height should be a GAME quantity, not a render one.** Ours is a
>    translation applied in RT64, downstream of everything the game knows —
>    which is why you go through ceilings (`31`) and why crouching does not make
>    you a smaller target. PD drives the player's own eye height and asks
>    `bwalkCanMoveUpwards` about the ceiling. **`86` slice H2 puts both options
>    in front of the wearer rather than choosing by argument.**
>
> **`86` is a PLAN. Nothing in it is built.** `48` rule 1: plan, discuss, then
> execute. Discuss it before writing code.
>
> ---
>
> ## ►► `87` — `86` §8's SIX READS ARE DONE. READ IT WITH `86`. ◄◄
>
> **No launches, no build, no headset. Three of the six came back different
> from what `86` assumed, and each one changes a slice:**
>
> 1. **THE AIM IS TWO INTEGRATORS, NOT ONE.** `crosshair_x_pos` (damped by
>    `guncrossdamp`) drives the crosshair; **`gun_azimuth_angle` (damped by
>    `gunaimdamp`) drives the BULLET** — `gunfire.c:4722-4732`. **`86` slice A1
>    writes only the first, which would steer the crosshair and leave the shot
>    where it was.** Both must be pre-loaded. `38`'s inversion is still right;
>    it has to be applied twice.
> 2. **`field_FFC` ALSO MOVES THE GUN MODEL** — `gunfire.c:512-520`, into
>    `gunofs`. **That is `79`'s "it's still attached to other parts", named at
>    source, and it is where `85`'s seam already writes.** A1 and G1-G3 collide.
>    Rule 6.
> 3. **THE FOV PATCH DOES DISTURB THE PROJECTION — but not `c_screenwidth`.**
>    `c_scalex`/`c_scaley` carry the full 106/60 = **1.7667**, under
>    `geVrWorldCamera()` only. The round trip stays self-consistent, but **the
>    crosshair pixel is a pixel in the CULLING frustum**, which is a second
>    independent reason slice A2's world dot is the mechanism.
>
> **And two came back BETTER:** the ceiling query **exists**
> (`stanTestLocusEdgeAboveY`, already called with the player's own eye height)
> and **the game already auto-crouches** under low geometry (`autocrouchpos`)
> — **so H2 option B is smaller than `86` costed it, and the A-vs-B
> recommendation should be re-discussed on those grounds.** There is no
> `GEOFLAG_BLOCK_SIGHT`; GoldenEye passes a **per-call `cdtypes` mask**
> instead, which serves R1's purpose without the flag.
>
> **`87` opened four more reads. Read 7 is DONE — `88`.**
>
> ---
>
> ## ►► `88` — READ 7. THE GUN ALREADY POINTS AT WHERE THE BULLET GOES. ◄◄
>
> **`87` asked whether `itemstats->PlayX/Y/Z` can be zeroed under VR so
> `field_FFC` stops moving the gun model. They can — three readers, all in one
> block — but they SHOULD NOT BE:**
>
> ```c
> /* gunfire.c:568 */
> matrix_4x4_align(&tmpmtx, 0.0f, gunofs.x - hand->field_A38, ...);
> ```
>
> **`field_A38/A3C/A40` IS THE AIM POINT.** The engine already orients the gun
> on the axis through the gun position and the aim point. **Write the aim and
> the gun model follows it** — no rotation write, no sign sweep. **`87`'s
> "A1 and G1-G3 collide" is RETRACTED; it is the coupling A1 wanted.** And
> **`85`'s `-SeamNoRot` was the wearer refusing to fight a rotation the engine
> was already computing.** Rule 3, and the wearer got there first again.
>
> | Also in `88` | |
> |---|---|
> | **`:6077` IS AIM MODE** | `86` §5 A1's owed read 1, closed. **And the split is CONTROLLER CONFIG (`HONEY`/`KISSY`), not auto-aim vs manual** — auto-aim is nested one level in. Explains `36`'s "hip fire decoupled, aim mode is not" |
> | **`sub_GAME_7F0680D4` HAS NO CALLERS** | Dead in the shipped game. It is still A1's whole job already written — **but it is UNTESTED engine code, a candidate and not a shortcut** |
> | **A1 MAY NEED NO NEW PATCH NAME** | `85`'s seam leaf `gunSetHorizontalOffset` is called at `gunfire.c:464`, **48 lines upstream of the `field_FFC` read at `:512`, same frame**, and `field_FFC` is a player global. **`87` read 6's "one long build for A1" may be wrong.** Two routes now open — discuss before building |
> | **DO NOT ZERO THE STATS TABLE** | `get_ptr_item_statistics` returns a pointer into shared, mutable, per-item data that `copy_item_in_hand_to_main_list` WRITES. Zeroing it is a permanent mutation. Rule 7 |
> | **`gunUpdateAndFire` IS 666 LINES** | Not patchable. `78` and `83` were right; this is a third measurement agreeing |
>
> ---
>
> ## ►► `90` — THE BULLET IS THE CLAMPED QUANTITY. `86` AND `87` BOTH HAD IT BACKWARDS. ◄◄
>
> **Found while costing the A1 build routes. One read.**
>
> | | |
> |---|---|
> | **`crosshair_x_pos` → `crosshair_angle`** | **THE BULLET.** `bullet_path_from_screen_center` (`gunfire.c:4846`) reads it, **eight call sites**, and the decomp's own comment says *"computes the angle the player's bullets are fired at"*. **It is CLAMPED** at `:4699-4715` |
> | **`gun_azimuth_angle` → `field_FFC` → `field_A38/A3C/A40`** | **The GUN MODEL'S POINTING**, the muzzle flash, and the viewmodel sway. **Five readers, none of them fires anything.** Unclamped |
>
> **So `86` §3.8's *"`field_FFC` is `crosspos2`/`bgunSetAimPos`, exactly"* is
> FALSE, and so is `87` finding 1's labelling. `87`'s TWO-INTEGRATOR finding
> survives — only the labels on its outputs swap.**
>
> **THE CONSEQUENCES:**
>
> 1. **There is NO unclamped shot path in GoldenEye. The bullet cannot leave
>    the screen rectangle.** `86` gate G-A1-3's prediction is confirmed from
>    source before it is run: the gun keeps tracking, the bullet pins.
> 2. **SLICE A2 IS NOT OPTIONAL.** Past the clamp the gun model becomes an
>    actively misleading indicator. **A world dot on the fired ray is the only
>    thing that tells the truth**, and G-A2-2's dot must pin with the BULLET.
> 3. **A1 writes BOTH integrators or the gun and the shot disagree by
>    construction.**
> 4. **`88` §5.1 is corroborated but NOT proven** — `initBondDATA.c:114`
>    initialises `field_A40` to **+1000**, the opposite sign to the runtime
>    value. **S0 prints `field_A40` as well as `MuzzleFlashExtension`**
>
> ---
>
> ## ►► `89` — EVERY OWED READ IS NOW CLOSED. BUILD AFTER DISCUSSING. ◄◄
>
> **Reads 9, 10 and 11 are done, and the stats-table trap is closed with no
> code. `86` §8 said do the reads before, not during. They are done.**
>
> | | |
> |---|---|
> | **READ 9 — and it COSTS H2 A WRITE** | `autocrouchpos` will not fight a written-in head height; `currentPlayerGetCrouchPos` returns the **MINIMUM** of it and `crouchpos`, so it is a cap that composes for free (rule 8). **But the AI reads the CROUCH STATE, not `eyeheight`** — `chrprop.c:1413` picks `HIT_CHEST`/`HIT_GENERAL`/`HIT_GENERALHALF` from it. **So driving `eyeheight` alone does NOT pass gate G-H2-3. H2 option B is TWO writes**: `eyeheight` for the view and the ceiling, **`crouchpos` for the AI**. `87`'s "smaller than it looked" was half right and is corrected in `89` |
> | **READ 10** | **`bondviewUpdatePlayerCollisionPositionFields`** — `bondview2.c:4557-4651`, **95 lines, patchable, one new name.** It derives `eyeheight` from **`headpos.f[1]`**, so there are **two injection points** (override the walk-bob, or compose with it) — a wearer question, not an argument. **And its `phi_f0 < 30.0f` clamp means gate G-H2-4 is FREE** — which is the whole case for option B in one line: **our RT64 translation is downstream of that clamp; a game-side write is upstream of it** |
> | **READ 11 — SETTLED FROM SOURCE** | **The model's barrel is local +Z, and `guAlignF` maps local +Z onto `aimpoint − gunofs` — the vector from the gun TO the target.** `88` §5 holds with the sign established. View space is −Z forward, confirmed twice (`gunfire.c:764`'s `-m[3][2]`, and `83`'s z = −33). **One falsifier for S0: `MuzzleFlashExtension` must be POSITIVE for every weapon** — the stats are ROM data, so it is the one field that cannot be read from the tree |
> | **THE TRAP — CLOSED, NO CODE** | `copy_item_in_hand_to_main_list` **has no callers**; our patch only reads `PosX`; and **`88` decided not to write the mutation in the first place.** A guard would be **`42` exactly — a safeguard in a hook nothing reaches.** It becomes **rule 13** below instead |
>
> **`86` slice changes: S0 prints `MuzzleFlashExtension`; H2 option B is two
> writes and one new patch name; G-H2-4 is free; G2's sweep is for roll and grip
> basis only, not the aim axis. A1 is unchanged — `87`'s two integrators and
> `88`'s two routes both stand.**

> # THE STATE, IN ONE SCREEN
>
> | | |
> |---|---|
> | **B1, stereo** | **FIXED, WORN, CONFIRMED.** Gate required -113 px +/-5, measured **-117 px**. Depth is real, images fuse, one gun instead of two. Root cause: **two present draws bound the SAME descriptor heap slot in one command list**, and D3D12 reads heaps at EXECUTION time. `69` `70` `71` |
> | **B3, THE MACHINE BUGCHECKS** | **NEW, BLOCKING, AND IT IS OURS.** `0x139` arg1=3, five times, always within a minute of a VR session closing, never under `-NoXr`. **`39`'s "not our bug / memory instability" is RETRACTED** — the owner lowered his RAM speed on the strength of it and it crashed three more times. `75` |
> | **B2, the SBS freeze** | Worked around, not fixed. `-Sbs` is the default; `-NoSbs` reproduces it |
> | **Scale** | **ANSWERED. ~50 units/metre**, measured worn. `16`'s derived 100 is out by ~2x. `77` |
> | **The "big head"** | **Was the RECENTRE, not the scale.** Origin was captured at process start with the headset on the desk. **Press `F9` while wearing it.** O60 |
> | **Judder** | Appeared, as `26` predicted. **The XR submit loop is exonerated** — 516 samples, one over budget, ~87% of every frame blocked in `xrWaitFrame`. `72` |
> | **ACTIVE WORK** | **6DoF — `86`. EVERY READ IT OWED IS DONE (`87` `88` `89` `90`), AND SLICE S0 IS WRITTEN (`91`).** S0 is **not compiled and not worn**. The hand work (`76` slices 1-2, `78` `79` `85`) is behind it and its position half is confirmed worn |
> | **THE HAND** | **THE GUN FOLLOWS THE HAND — `85`.** `.\vr.ps1 -UnitsPerMetre 50 -SeamNoRot -HandPosZ 1`. Position tracks; rotation is deliberately off because a wrong one HIDES the gun rather than tilting it. Next: sweep `-HandAxisX/Y/Z` |
> | **THE HAND (history)** | **Three paths, three flags, NONE validated** — `-HandAim` (default, tracks but the sway pulls), `-HandAbsolute`, `-HandSeam`. **The seam is the right architecture and it fires; its placement is wrong.** `84` has the one-launch experiment to start with |
> | **THE SAFE EXIT** | **`Close GoldenEye VR.bat` on the Desktop**, or `close-gevr.ps1` in the repo. It keeps the log first. **Never use the X** |
> | **6DoF, THE PLAN** | **`86`. THE CURRENT PHASE.** Nine slices, gates written first, from Perfect Dark's source at `67ea20c`. **The eleven reads it owed are DONE — `87` `88` `89` `90`. SLICE S0 IS WRITTEN — `91`, not compiled, not worn.** Decisions taken: **H2 uses B-i, A1 uses route 1** |
> | **PRIOR ART** | **Perfect Dark — the SAME ENGINE — has a shipping MIT VR port with motion-control aiming.** `81`. **ITS VR SOURCE IS PUBLIC AND HAS NOW BEEN READ IN FULL — `86`.** `81`'s "not yet in the public tree" is FALSE and corrected there. `82` was a first pass over it and `86` supersedes it |
> | **EVERY KNOB** | **`80`**, generated from the source. Includes which knobs are CONNECTED, which are `-Flat`-only, and the one whose consumer was deleted |
>
> ## THREE THINGS THAT WILL COST YOU IF YOU DO NOT READ THEM
>
> 1. **NEVER CLOSE A VR SESSION WITH THE X.** `taskkill /F /IM GoldenRecomp.exe`.
>    Four force-kills, zero bugchecks; every X-close today took the machine down.
>    **This is also the experiment for O21** — a force-kill runs none of our
>    teardown code.
> 2. **PUT THE HEADSET ON, THEN PRESS `F9`.** Recentring fires at process start,
>    which is the wrong moment. Everything about scale and height is wrong until
>    you do this, and it cost this project three confounded launches.
> 3. **THE WEARER IS THE BEST INSTRUMENT IN THIS PROJECT.** Three separate faults
>    in `79` were diagnosed from description alone: "rotation only is not free",
>    "turn left and I see the right side of the gun" (a MIRROR, not a rotation),
>    and "it's still attached to other parts" (the engine's own turn-sway). **Ask
>    what it looks like, not whether it works.**
> 4. **WHEN A HUMAN IS THE INSTRUMENT, USE A STEP NOBODY COULD MISS.** 100 vs 50
>    was reported as "it looks the same" while the log showed the eye separation
>    genuinely halving. A 4x step answered it in one launch. `77`
>
> ## THE INSTRUMENT WARNING, NOW WITH A FIFTEENTH ENTRY
>
> **`72`: the frame-budget and stage-ms lines report MEANS over ~90 frames.**
> A mean cannot see a hitch, and judder is nothing but hitches. **Before
> trusting any instrument in this tree, ask what it would print on a WORKING
> build — and then ask what it would print on a build that fails in the way you
> actually care about.**

> ## READ `65`, THEN `64`. RUN `.\vr.ps1` — SBS IS NOW THE DEFAULT.
>
> **`GE_VR_SBS` decides whether the headset works at all.** Measured over four
> launches: `-Sbs` worked 2/2, plain `.\vr.ps1` froze 2/2. It is documented
> everywhere as a monitor-only debug view with "no meaning once the images go
> to a headset". **That was false, and believing it cost a day and a half.**
> `vr.ps1` now sets it by default; `-NoSbs` reproduces the fault on purpose.
>
> **THE MECHANISM IS NOT ESTABLISHED.** `-Sbs` is a workaround, not a fix. The
> freeze is load-dependent (`-ResScale 0.25` delayed it ~8 s), so there is a
> race and `-Sbs` is hiding it. **Do not close B2.**
>
> ## `67`: THE UPSTREAM HALF OF B1 IS EXONERATED BY RENDERDOC
>
> **In a frame measured pixel-identical, D3D12 was given two distinct buffers
> with correctly mirrored matrices (+/-414.6 offset, -/+0.1411 skew), each with
> its own SRV, in two separately executed command lists, into two distinct
> targets each sampled by its own half.** Everything from the CPU matrices to
> the presented texture is correct and the pixels are identical.
>
> **So the fault is at or after the SHADER READ.** That is ground truth from
> outside the codebase, not a thirteenth hypothesis.
>
> **The capture is already on disk** — `ge-vr-shots\rdc\` — so the next query
> needs no launch. Open it in `qrenderdoc.exe` and resolve which descriptor
> each dispatch actually reads. `67` has the exact chain.
>
> **TWO INSTRUMENTS IN THIS TREE CANNOT FAIL.** `49`'s "upload verdict"
> compares two adjacent struct member addresses; today's `VIEWPROJ GPU` line
> compares two `BufferPair::get()` results. Both are true on every build.
> `49`'s steered `57` and `58`. Both are now labelled in place. **Before
> trusting any instrument here, ask what it would print on a WORKING build.**

> ## ~~B1 IS THE ONLY BLOCKER~~ — **CLOSED 2026-08-23. FIXED AND WORN, `71`.**
> **Kept as the record of what it looked like from inside. The measurement below
> was true and the diagnosis it implied was not: the images were identical
> because both present draws SAMPLED THE SAME DESCRIPTOR SLOT, not because
> anything upstream was wrong.**
>
> ```
> PREDICTION: eye1 - eye0 = -124.7 px per half-frame
> MEASURED:   0 px.  cross-correlation at dx=0 = 1.0000, mean|L-R| = 0.001
> ```
>
> **One image in both eyes.** `49`'s and `57`'s `-Flat` finding does carry to
> XR. This is the whole of what remains.
>
> **The doubling in the lenses IS B1** — two identical images submitted with two
> different eye poses cannot fuse, so everything doubles. `47`'s mirror table,
> second row. It is not a separate fault and gets no slice of its own. **The
> "viewmodel contradicts the docs" section below is closed by this.**
>
> ## WHAT `64` KILLED — do not re-run these
>
> - **Frame interpolation.** `rr_option: "Original"` froze it harder. Passes
>   dropped 90 -> 60, so the setting was live and the negative is real.
> - **The unguarded `eyeZeroTarget`.** Measured never to fire: `eyeStore=92/92`.
>   Still a real defect. Not this one.
> - **`RenderTarget`'s address.** It is `addressForName`, cosmetic. Falsified
>   from source at zero cost — the second time after `58`.
> - **The brightness.** There was never a brightness bug. "1% brightness" was a
>   level fade-in frozen early; at `-ResScale 0.25` it freezes bright instead.
>   Every sRGB and transfer-function theory was aimed at nothing.
>
> ## TWO INSTRUMENT TRAPS, BOTH PAID FOR TODAY
>
> **`-SkipEye` does NOT disable the eye split under XR.** It disables only the
> present-side eye render; `render passes` still shows `eye1=92
> distinctTargets=92` under `-SkipEye 1`. It is the best knob in the project
> under `-Flat` and returns a false answer in the headset.
>
> **`-Flat` is structurally blind to the eye PRESENT stage.** `vrPresentEyeWidth`
> is written only by the XR host (`ge_vr_xr.cpp:1019`), so under `-Flat` the
> whole per-eye present block is skipped. `-Flat` validates the eye RENDER and
> nothing downstream of it.

> **`39` is the live task board.** Open work, status and next actions live there.
> **`65` then `64`** are this session. `47`'s measurement METHOD is still the
> best thing in the project; its image findings are void. Every other document is indexed at the bottom; you do not need to read them in order.

---

## THE RULES — these are not suggestions

Every one of these was paid for. The incident is named so you can check it.

> **CHANGED 2026-08-24, BY OWNER DECISION. RULES 5 AND 11 ARE NO LONGER
> STANDING RULES — they are invoked BY REQUEST.** Their numbers are kept and not
> reused, because between them they are cited eighteen times across fourteen
> documents. **Every other rule is unchanged and still standing.** The two are
> written out in place below with what they said, what invokes them now, and
> what is given up — recorded rather than deleted, so this reads as a decision
> and not as an omission.

**1. Plan, discuss, then execute.** Write the plan as a numbered doc and **stop**.
A doc written and executed in the same breath is a changelog, not a plan, and it
removes the one checkpoint that catches a wrongly-aimed slice. `32` was aimed at
the wrong question; `33` had to undo it.

**2. Write the gates before the code, and ask of each: what would this build have
to do differently for this to fail?** A gate a working build would also pass is
not a gate. Five such gates have been caught before they were run.

**3. Measure. Do not describe.** *"The right eye looks skewed"* turned out to
mean *"the right eye is not being rendered."* Every correct conclusion in this
project came from a number; every wrong one came from reasoning about an
appearance. `47`.

**4. Verify the instrument before trusting a test.** `render passes: eye0=N
eye1=N distinctTargets=N` must all match. Three hypotheses were tested and acted
on while the second eye did not exist. Results from a broken instrument are not
weak evidence — they are **no** evidence, and must be marked void. `43`, `47`.

**5. ~~One change at a time.~~ — REMOVED AS A STANDING RULE 2026-08-24, BY OWNER
DECISION. NOW APPLIED ON REQUEST.**

> **The number is kept and NOT reused. Rules 5 and 11 are cited eighteen times
> across fourteen documents; renumbering would repoint every one of those
> citations at a different rule while still reading as though it resolved —
> `32`'s shape, and `41`-`46`'s. Nothing that cites "rule 5" needs editing.**

**What it said, kept because the incident is still true:** one change at a time.
Three settings were changed in `graphics.json` at once — one was necessary, one
caused a regression, and separating them cost a round. **`48` had already
amended it to "one BEHAVIOUR change at a time; diagnostics may be batched
freely."**

**What it is now:** a tool the owner asks for. *"Change one thing"* on a given
build invokes it for that build. It no longer gates a batch by default.

**What is given up, stated plainly so nobody rediscovers it as a surprise:**
when a batched build regresses, the batch has to be bisected to find out which
change did it. That cost is now accepted per-build rather than avoided
per-project.

**6. Check who else writes what you write — and who still reads it.** Five
instances: `21`, `26`, `27`, `38`, and `32`, where a knob's consumer had been
deleted and it returned a confident **false negative**.

**7. Know who destroys what you build, and when.** `29`: the object was alive and
already gutted. `42`: every safeguard lived in a hook that was never reached.

**8. When two things must agree, do not synchronise them — remove the second
one.** The recentre was wrong twice in opposite directions before it was made a
property of the shared reference space. `46`.

**9. Make the program describe its own failure rather than inferring harder.**
This applies to **appearance**, not only to crashes. When a question is asked
twice, add the log line instead of answering it again.

**10. Correct a falsified doc at its source, and record it.** Eight claims have
been falsified so far. **A wrong doc that nobody flags costs more than a bug.**

**11. ~~Nothing moves to DONE until it has been OBSERVED.~~ — REMOVED AS A
STANDING RULE 2026-08-24, BY OWNER DECISION. NOW APPLIED ON REQUEST.**

> **Number kept and not reused — see rule 5 above for why.**

**What it said, kept because the incident is still true:** nothing moves to DONE
until it has been observed — not when the code is written, not when it compiles.
`33` exists because two slices were called finished on a build nobody had worn.

**What it is now:** a tool the owner asks for. *"Don't call that done until I've
worn it"* invokes it for that item. Work may otherwise be recorded as done at
the point it is written.

**What is given up, stated plainly:** the status of an item no longer implies
anyone has seen it run. **A reader of `39` can no longer assume DONE means
worn**, so anything depending on that distinction has to say which it means in
its own words. `91` and `107` both currently rely on the old reading and say
"written, not compiled, not worn" explicitly, which is the habit that replaces
the rule.

**12. Respect the licence split before reading anyone else's source.** See "Look
for prior art" below. Reading a GPL project to solve an RT64-side problem
contaminates the only part of this work that can go upstream.

**13. Prefer a documented hazard to an unreachable guard.** **NEVER WRITE
THROUGH `get_ptr_item_statistics`** (`gun.c:708`) — it returns a pointer into
shared, per-item, ROM-loaded `WeaponStats`, not a copy, so a write is permanent,
global to the weapon type, and invisible. **The only stock writer,
`copy_item_in_hand_to_main_list`, is dead code**, so no guard was built: a guard
here would be `42` again, where every safeguard lived in a hook that was never
reached. **A hazard that is written down and never triggered costs nothing; a
guard that is built and never reached costs a patch name, a long build, and a
future session's puzzlement.** `89`.

**14. WE HAVE THE SOURCE. CHANGE IT.** — **ADDED 2026-08-29 BY OWNER DIRECTION.**
> *"Always keep in mind we have all the source files."* — owner, and he had to say
> it after a session spent working around a constant it could have edited.

`227` moved this project to source **so that fixes do not have to be hacks**, and
the owner's standing clause says every choice must build on that *"so that we
don't have to hack later on."* The habit this replaces is real and cost `262`:
faced with the cast crash, the project built a **shared-lifecycle slot-free path**
(`234`), broke pickup, inventory and weapon switching with it (`242`), turned it
off, and carried the crash as OPEN for four banners — **while
`ANIM_MODEL_SPARE_SLOTS 10` sat editable in `initunk_005520.c`, in a file whose
own header comment already described this exact NULL-model intro crash.**
**Before designing a runtime workaround, a knob, or a probe, ASK WHAT THE SOURCE
SAYS AND WHETHER THE SOURCE CAN SIMPLY BE CHANGED.** A constant sized for 4 MB of
N64 RDRAM is not a constraint we inherited. **And never ask the owner to read a
file to find something the source can print** (`262`: a config value was treated
as an oracle when three lines of C would state it).

**15. AN INSTRUMENT MUST BE BUILT WHEN ONE CAN BE — AND VALIDATED BEFORE IT IS
BELIEVED.** — **ADDED 2026-08-29 BY OWNER DIRECTION.**
> *"If a tool can be made for you to observe, then that tool should be made and
> used if proven accurate to troubleshoot."* — owner.

The first half is rule 9 restated as an obligation rather than a preference: when
a question is asked twice, **build the probe.** The second half is the owner's own
qualifier and it is the one that bites: ***if proven accurate***. `261`'s slot
trace was placed AFTER the gate it was meant to observe, so "the gate is off" and
"the function is never called" both printed nothing — **and the same paragraph
that shipped it claimed it could tell those two apart.** `256` §1 is the same
failure. **State what the instrument would print if it were pointed at the wrong
thing, BEFORE the run, and check that its silence has exactly one meaning.**
**Counters that are incremented and never printed are not an instrument at all**
— `g_geSlotFreedAnim` and its two siblings were counted from `234` to `261`
without a single line of output, so a fix nobody could observe was argued about
for four banners.

**16. AN OWNER REPORT REPEATED IS A RANKING ERROR, NOT NOISE.**
— **ADDED 2026-08-29.**
> *"I don't know why the project by now, as many times as I brought it up, has not
> made it part of the process."* — owner, on the intro.

**The intro was raised three times and parked three times** — `229` §20 ranked it
under the menu text, `231` §3 grouped it with faults that were not its own, `242`
parked its fix. **When the owner raises the same item in more than one session,
the backlog order is wrong and it is the ORDER that gets fixed, not the item's
priority argued again.** `HANDOVER` §5 already records that his corrections
outrank the analysis every time they conflict; **this extends it from facts to
PRIORITIES.** And the cost is measurable: the crash survived four banners and the
fix was a constant.

**`48` is the full protocol — the start-of-session checks and the handover
checklist. Work it top to bottom at both ends of a session.**

**17. THE SESSION'S OWN COMMIT MESSAGE IS PART OF THE SESSION'S OUTPUT — AND SO IS
EVERY OTHER ARTEFACT A TOOL WILL SILENTLY SUBSTITUTE A STALE ONE FOR.**
— **ADDED 2026-08-30 BY OWNER DIRECTION.** *"Whatever the outcome bake it into the
rules so it doesn't happen again."*

**`COMMIT-NOW.cmd` picks the NEWEST `COMMIT-MESSAGE-*.txt` by timestamp.** When a
session ends without writing one, the newest file is the PREVIOUS session's, and the
commit goes through under a message describing different work. **It did exactly that
three commits running on 2026-08-30** — `270`, `271` and the regen all landed reading
*"docs: 267 — the budget instrument measured the pacer."* Nothing failed. Nothing
warned. **The history was simply wrong, and history is what `262` was solvable from.**

**THE RULE HAS TWO HALVES, AND THE SECOND IS THE GENERAL ONE:**
1. **The assistant writes the message files — one per repo touched, dated TODAY —
   BEFORE saying the session is ready to commit.** A commit that is "ready" without
   its message is not ready. This joins the end-of-session checklist (`SESSION-START`
   §5, `00-STATE` §7c) and ranks with updating `00-STATE`.
2. **WHEREVER A TOOL FALLS BACK TO "THE NEWEST" OR "THE LAST" INSTEAD OF FAILING,
   THAT FALLBACK IS A SILENT-STALENESS BUG AND IT GETS A GATE.** This is not one
   incident: the same session found `fetch-thirdparty.sh` printing *"wrote … bytes"*
   after an `mv` that failed, the same script blaming the NETWORK when the real fault
   was a missing `git`, a thirdparty patch two sessions stale so a fresh clone had no
   `GETV_DLGRAB`, two divergent tracked copies of `SESSION-START.md`, and a stale
   `index.lock` left by the assistant that broke the owner's commit. **Every one of
   them reported success or said nothing.** `271` §7.
   **The fix is always the same shape: make the silent path FATAL and give it a gate
   that names what it checked** — `verify`'s `15/15 files match`, not a byte count.

> **RULE `3` SAYS MEASURE RATHER THAN DESCRIBE. THIS IS ITS COUNTERPART FOR TOOLS:
> A TOOL THAT CANNOT FAIL IS NOT REPORTING, IT IS REASSURING.** `15` demands an
> instrument that can fail; `17` demands the same of the plumbing.


**18. NO ATTRIBUTION TRAILERS IN COMMIT MESSAGES — AND MORE GENERALLY, A CONVENTION
THAT ARRIVES FROM THE ASSISTANT'S OWN DEFAULTS RATHER THAN FROM THIS PROJECT IS A
SILENT CHANGE AND GETS REFUSED.**
— **ADDED 2026-09-01 BY OWNER DIRECTION**, on the session that introduced one.
*"I did not ask for that. Now I have to worry about this replicating. Especially how
it was introduced."*

**THE FIRST HALF IS FLAT AND HAS NO EXCEPTIONS.** No `Co-Authored-By`, no
`Claude-Session` or any session URL, no tool footer, no "generated with" line. **The
message body is the output; a trailer is noise in it.**

**AND THE HISTORY SAYS SOMETHING STRONGER THAN "IT WAS NEVER DONE".** `[MEASURED]`
2026-09-01, 89 commits: **13 carry a `Co-Authored-By:` trailer and every one of them is
from the repo's first two days** (2026-08-22 and 2026-08-23, `d0c1b2a` through
`1f4cfa9`). **Then it stops. Sixty consecutive commits carried none** before `294` put
one back. **The trailer is not unprecedented here — it was TRIED AND ABANDONED, which is
a firmer decision than never having tried it.** Do not reintroduce it on the strength of
finding it in the first week.

**THE INCIDENT, AND IT IS RECORDED BECAUSE OF HOW IT ARRIVED, NOT BECAUSE OF WHAT IT
WAS.** `294` wrote `COMMIT-MESSAGE-2026-09-01f.txt` and appended a `Co-Authored-By`
and a session URL. **The owner never asked for them.** They came from the assistant's
own tooling defaults, which had told it those lines "replace any earlier attribution
guidance" — so the assistant treated an instruction from OUTSIDE this repo as
outranking a convention INSIDE it, mentioned it in one line as a courtesy, and
committed. **It landed in `a6dce62` before it was caught.** The damage was two lines.
**The problem is that nothing in the repo would have stopped it, and every future
session starts with the same defaults.**

**SO THE SECOND HALF IS THE GENERAL ONE, AND IT IS RULE `17`'s SHAPE APPLIED TO STYLE
INSTEAD OF TO PLUMBING:**

> **THE ASSISTANT'S DEFAULTS ARE AN UNTRACKED INPUT TO THIS REPOSITORY.** They change
> between sessions, they are invisible in every diff, and they are not this project's
> decisions. **When a default and a house convention disagree, the house wins, and the
> disagreement gets SAID — not footnoted after the fact.**

**THE CHECK IS CHEAP, AND `294` GOT IT WRONG TWICE BEFORE GETTING IT RIGHT — WHICH IS
THE PART WORTH LEARNING.** First it grepped the last **6** commits, found **0**, and
concluded the trailer had *never* been used. Then it anchored the same grep over **all**
history and got **14**, flatly contradicting what it had already told the owner. Both
numbers were real; **neither was a measurement, because neither stated its WINDOW.**

> **A CONVENTION CHECK WITHOUT A STATED WINDOW IS NOT A MEASUREMENT — IT IS A SAMPLE
> DRESSED AS A FACT.** Rule `3` says measure rather than describe; this is where a count
> that looks like a measurement still describes. **Say the window, say the count, and
> look at WHERE the hits fall.** Six commits cannot see an abandonment and all-history
> cannot see a decision — **the shape over time is the answer, not the total.**

The working form, and it must be **ANCHORED AT THE LINE START WITH THE COLON** or the
rule's own text and this very paragraph match it and the check reports a convention that
does not exist — **a test its own documentation fails is rule `4`, verify the instrument
before trusting it:**

```
git --no-optional-locks log --format='%h %ad|%B' --date=short | grep -c "^Co-Authored-By:"
git --no-optional-locks log -40 --format='%B' | grep -c "^Co-Authored-By:"   # the recent window
```

**Zero in the recent window, with any hits confined to the earliest commits, means the
thing was DROPPED. Stop — it is not "nobody got round to it".** The same test, and the
same window discipline, applies to file naming, section ordering, date formats and
message style.

**AND IF ONE GETS IN ANYWAY: SAY SO PLAINLY AND FIX IT BEFORE THE COMMIT, NOT AFTER.**
Mentioning an unrequested change in passing is not consent, and "you can delete it if
you like" puts the work on the owner. **The assistant does not get to introduce a
convention and bill the removal to whoever noticed.**


---

## THE PERFORMANCE CONSTRAINTS — `P1`–`P5`, OWNER-SET, 2026-08-29

**Entered by `257` §5 from the owner's stated requirements.** They are not a
phase and not a checklist item. **They constrain every plan written from here,
and a plan that does not satisfy them is not finished.**

> **The owner's words, and they are the source of all five:** *"I need ninety
> hertz in my headset... everything to be able to be adjustable for different
> fields of view and different headsets that have different resolutions...
> incredibly optimized and run very smoothly, which is why I'm building this on
> source. **Every choice that we make for this foundation builds on this so that
> we don't have to hack later on.**"*

**P1. SIM RATE AND PRESENT RATE ARE SEPARATE TERMS, AND NEITHER IS A LITERAL.**
The sim rate is `60.0f / actualHz`, computed per frame from the runtime — never a
hardcoded `90`. `ge_timing_probe.c` already names the property to preserve:
*"game time is counted in video fields, so a correct clock gives 60 a second
whatever the renderer is doing."* **`239`: a knob validated at one value is not a
setting. Anything rate-dependent is read at TWO rates before it is believed.**

**P2. NEVER STORE AN FOV ANGLE. STORE FOUR TANGENTS PER EYE, PER FRAME.**
`guPerspective` cannot express an off-centre frustum, so the projection is
replaced regardless (`255` §1). **`222` §2 `[MEASURED]` the aspect error at 30%**
— game x/y `1.000` against render `1.297` — **the exact fault class a stored
aspect assumption produces.** Adjustable FOV and being correct once are the same
code path.

**P3. RESOLUTION IS ONE VARIABLE, SOURCED FROM THE RUNTIME.** The seam already
exists and must be preserved: `ge_config.c:270` parses `WIDTHxHEIGHT`, and
`ge_display_api.c:12` records that the dimension *"is only ever assigned on
`gfx_current_dimensions`, never on `gfx_output_dimensions`."* **One assignment
site. No constants.**

**P4. PAY STRUCTURAL COST ONCE; NEVER PAY PER-FRAME COST FOR CONVENIENCE.**
The cheaper thing to write is often the more expensive thing to run. **This is
the axis on which `255` §3's A/B is decided for cost** (`257` §6) — and it is why
the project is on source at all.

**P5. NO PERFORMANCE CLAIM WITHOUT AN INSTRUMENT THAT CAN FAIL.** `49`. **As of
`257` §6.1 there is no frame budget in the native port** — `port_render.c:143`
times three stages with `SDL_GetTicks()`, millisecond resolution, against an
11.1 ms budget, through a per-frame `printf` that costs more than it measures.
**"Runs smoothly" is not measurable until that is fixed, and stereo's cost cannot
be reported until there is a baseline to subtract from.**

---

## THE EMBODIMENT AND SIM-AUTHORITY CONSTRAINTS — `P6`–`P9`, OWNER-SET, 2026-08-29

**Entered from the owner's stated requirements, 2026-08-29f, and they extend
`P1`–`P5` under the same clause: `"every choice for this foundation builds on
this so that we don't have to hack later on."` A plan that does not satisfy
`P6`–`P9` is not finished.**

> **The owner's words, and they are the source of all four:** *"we must have a
> very strong 6DoF system that controls two hands, possibly even a body. And I
> want movement in VR to be free, so aim is always accurate no matter which way
> you're facing or which way the camera is. We also want to make sure the game
> understands the player's position, and the game understands the physics in the
> game, like where the bullets are going, where they hit — because that's going
> to be useful when we get to the multiplayer portion of all this."*

**P6. THE SIM OWNS THE POSE. THE RENDERER IS A CONSUMER, NEVER THE HOLDER.**
Head, both hands and any body proxy are game-side state, updated before the
tick, readable by game code. **This is `194`'s root cause restated as a
foundation requirement rather than a bug:** *"the head rotation reaches only the
EYE VIEW MATRIX, composed onto the game's view matrix at RENDER time. THE GAME
CAMERA NEVER LEARNS ABOUT THE HEAD."* `194` attached four faults to it — bullet
origin, drawn gun orientation, bullet direction, frame recovery. **`P6` says
those four were never four bugs. They are one missing term, and every one of
them recurs in any design that leaves the pose in the render layer.**
**`P4` decides this on cost as well: pose-in-the-renderer is a per-frame
correction paid forever; pose-in-the-sim is structural and paid once.**

**P7. TWO HANDS AND A BODY ARE ONE ARTICULATED SYSTEM, NOT THREE KNOBS.**
`86` already made this the standing objection to the previous approach — *"6DoF
as a coherent system rather than as six separate knobs"* — and `U-25` is the
designed head-relative locomotion term (PD's `VrArmBodyFollow = 0.02`,
`bondgun.c:10991`; owner: *"Forward follows your head"*, *"I am in a seat that
spins"*). **Rule 8 governs the shape: when two things must agree, do not
synchronise them — remove the second one.** Hands, head and body agree because
they are derived from one reference space, not because three terms are kept in
step.

**P8. AIM IS INDEPENDENT OF FACING, OF THE CAMERA, AND OF LOCOMOTION.**
"Free movement" means the aim ray is a property of the hand in world space and
of nothing else. **The existing evidence already points here and must not be
re-litigated:** `[MEASURED]` the composition `thr*camT` is **not** the bug
(`223` §2.2, confirmed at `gunfire.c:570-574`); `[MEASURED]` the residual error
is **camera-dependent**, constant to ±3° within a camera group and jumping
between them (`223` §2.3) — **which is exactly the signature of an aim ray that
still carries a camera term it should not have**; `[MEASURED]` pitch already
tracks to ~5°, **so the fault is yaw-only.** `66`: aim and stereo are
independent, and `P8` does not wait on Phase 1.
**The sign trap is on the record:** `bondview2.c` rotates about Y by
`(360 - vv_theta)`, so engine yaw is the **negative** of the right-handed
convention; `guPerspectiveF`/`guLookAtF` are **row-vector**, GL/OpenXR
**column-vector**.

**P9. THE SIM IS AUTHORITATIVE FOR BALLISTICS AND FOR POSITION, BECAUSE
MULTIPLAYER WILL READ IT.** Where a bullet starts, where it goes and what it
hits must be computed and resolvable in game state, not inferred from what was
drawn. **This is the multiplayer prerequisite, and it is being entered NOW
precisely so it is not retrofitted later.**

> ### **`P9` HAS AN UNRESOLVED COLLISION WITH `P1`, AND IT IS BEING RECORDED,
> ### NOT DECIDED.** `P1` makes the sim rate `60.0f / actualHz`, a float read
> from the runtime per frame. **Two peers on different headsets therefore tick
> at different rates with different timesteps — a 90 Hz Index and a 72 Hz Quest
> do not produce the same trajectory from the same input.** For single player
> that is correct and desirable. **For a shared authoritative simulation it is
> divergence by construction.** The standard resolution is a fixed-rate
> deterministic sim decoupled from both present rate and headset rate, which is
> a *third* term `P1` does not currently name.
> **`[ASSUMED]` — nothing here is measured, and no multiplayer transport,
> topology or authority model has been chosen or costed.** `182`: this may not
> be built on. **It is written down because `P1` is about to be implemented, and
> the cheapest moment to find out whether the numerator is a literal, a query,
> or a fixed step is before the timestep goes into `MoveBond`, not after.**
> **See `RB-04`.**

---

## Look for prior art before you build

Cheap, and never done systematically. This project's own `PRIOR-ART.md` (in
`no6969el/goldeneye-native`, fetchable from GitHub) independently found the
licence structure and recommended the architecture that was eventually built.

**Search GitHub before designing anything non-trivial.** Known relevant:

| | |
|---|---|
| `RaYRoD-TV/StarFox64-VR` | OpenXR, per-eye stereo, motion controllers, **world-space HUD**, on an N64-lineage PC port. The closest thing to us. **Licence not established — establish it before reading the source** |
| `DR-89/fear-vr` | Native OpenXR stereo + 6DoF mod |
| `VR-Stereo-Hub/bioshock-trilogy-vr` | Same shape, with motion controllers |
| `fgsfdsfgs/perfect_dark` | Same engine family; the only decomp-native prior art. **MIT** |
| **`Alex-LeTux/perfect_dark_VR`, branch `port`** | **THE ONE THAT MATTERS. Same engine, shipping PCVR + Quest VR port, MIT, and its VR source is PUBLIC AND READ — `86`, at commit `67ea20c`. `81`'s "not yet in the public tree" is FALSE.** Attribution is owed on anything derived from it: `PUBLISH-MANIFEST.md` **and** the source comment |
| `rt64/rt64` | **Upstream of our renderer.** Check whether a problem is already fixed there |

**The licence decides where borrowed ideas may land:**

| Source licence | May influence | May NOT influence |
|---|---|---|
| MIT / BSD / Apache | anywhere | — |
| **GPL** (Dolphin VR, RetroArch, Mupen64Plus — most emulators) | the recomp **host**, which already links GPL-3.0 `N64ModernRuntime` | **`lib/rt64/` and `repo\`** — the MIT, upstreamable half |
| Proprietary or unclear | nothing | everything |

Establish the licence **before** reading, and say which half it may touch.
`PUBLISH-MANIFEST.md` has the full split; the test is which project's source a
change derives from, not which folder it sits in.

---

## FOUR THINGS THAT WILL COST YOU A DAY IF UNREAD

1. **Check the runtime and resolution lines in `gevr.log` before anything.**
   This rig moved from SteamVR/OpenXR 2.16.7 at 4140x3292 per eye to **Pimax
   OpenXR 0.1.0, Crystal Super, 5838x4498** between sessions, and nothing
   announced it. Every measurement before `36` was taken on the other runtime.
   `40`.

2. **Verify the instrument before trusting a test — and check WHAT WORKLOAD it
   latched on.** Two instruments were caught lying on 2026-08-23: the `fb eye`
   probe one-shots on the first workload, which is a **MENU** (`39` O28), and
   `render passes:` over-reports under `-SkipEye` (`39` O30). **Every instrument
   must state, before it runs, what it would report if it were looking at the
   wrong thing** — `52`'s census did, fired on a menu, and said so, which is the
   only reason it cost one launch instead of a session. `43`, `47`, `52`.

3. **Measure, do not describe — and when a number moves, look at WHERE.**
   Every correct conclusion came from a number; every wrong one from reasoning
   about an appearance. Two examples from one night: a 0.19% pixel difference on
   the build meant to fix it was about to be reported as progress — the
   difference **map** showed a mouse cursor. And `57`'s own title is wrong
   because a frame *looked* un-offset; measuring it showed the offset applied in
   full. **The author of rule 3 broke it two hours after writing it down.**

4. **Remove a thing and see if the result changes.** `-SkipEye` runs one eye
   pass alone. After five wrong predictions about which input was faulty, this
   was the first evidence that survived a wrong mental model — it proved each
   pass is individually correct, which no amount of input-checking could. `56`.

---

## Where the project is, in one paragraph

**CORRECTED 2026-08-23 — the paragraph below is VOID. B1 IS FIXED.** Kept as the
record of what the project looked like from inside the blocker. **The current
one-paragraph state is the first table in this file, and the current plan is
`86`.**

> GoldenEye 007 runs on Windows from the user's own ROM, recompiled, with high
> framerate interpolation, and reaches a Pimax headset at 4140x3292 per eye with
> head tracking, hip-fire aim decoupled, and a recentre. **What it does NOT do is
> stereo: both eyes have always shown one image, and that is the single blocker.**
>
> Phase 2 (OpenXR) is built through 3f-5 and was worn and confirmed at 3f-5 -
> **but every "stereo confirmed" claim before `49` was made without anyone ever
> measuring two images.** `B1` is the only thing that matters until it is fixed,
> and it is now measurable from a screenshot with **no headset** (`-Flat`).

**Where it actually is:** stereo is real and worn, the world scale is measured,
the controllers are bound, and **the gun follows the hand** (`85`). What remains
is 6DoF as a coherent system rather than as six separate knobs — **`86`** — and
above it the two ship-blockers, **B3** (the machine bugchecks when a VR session
closes) and **B4** (a tester will close with the X).

**UPDATED 2026-08-23, end of the reads session.** `86`'s eleven owed reads are
**all done** — `87`, `88`, `89`, `90` — and they retracted five claims, **two of
them written in the same session that retracted them**. **Slice S0, the 6DoF
instrument, is WRITTEN and has never been compiled** (`91`). **The next session
commits both repos, builds, wears S0, and reads `muzzleExt` and `A40` before
judging anything else.** Then H1.

---

## Do this first

### 0. WEAR IT. It works now.

```powershell
cd C:\Users\pdbar\Desktop\GoldenEye64Recomp
.\vr.ps1                      # SBS is the default now - docs\65
```

**The bisect `63` asked for has been run — `64` has the result.** Do not run it
again. `-NoXr` is intact, `-Flat` plays fine, and plain XR froze because
`GE_VR_SBS` was off.

**CORRECTED 2026-08-23 — B1 is fixed, so the "expect everything doubled" line
below is VOID.** Kept as the record.

> **Expect, worn:** a live, bright, correct image, head tracking, both hands
> tracked, five controller actions firing — **and everything doubled**, because
> both eyes carry the same image. That doubling is B1 and it is the only blocker.

**Expect now, worn, at `-UnitsPerMetre 50` with `F9` pressed while wearing it:**
depth is real, the images fuse, **one** gun, head tracking, both hands tracked,
and with `-SeamNoRot -HandPosZ 1` **the gun follows your hand** (`85`).

**`86` is the forward plan** — every 6DoF aspect, sliced, with gates. `66` was
the forward plan at the time B1 closed and is superseded by it.

### 1. The stereo harness

**No headset needed. `-Flat` measures stereo from a screenshot** - that is the
single most useful thing `49` added, and every measurement since has come from
it. `vr.ps1` and `build.ps1` live in the recomp repo root.

```powershell
cd C:\Users\pdbar\Desktop\GoldenEye64Recomp
```

### 1. The regression check

```powershell
.\vr.ps1 -NoXr                 # a normal 60/90 fps game. The path that must never break
```

### 2. The blocker, measured

```powershell
.\vr.ps1 -Flat                 # both eyes side by side in the window, XR off
.\tools_gevr_capture.ps1 -Tag whatever
```

The capture script grabs the **client area** (not the window - the seam must land
at exactly half the width) plus a tagged copy of `gevr.log`, and prints the
instrument lines. Analyse with:

```
python GoldenEyeVR\repo\tools\gevr_stereo.py <shot.png> --log <shot.log>
```

**Pass: -113 px +/- 5 in the far band, right eye further LEFT.** Today: **0**.

**Read the instrument lines BEFORE judging any picture** - `48` rule 4:

| Line | Must say |
|---|---|
| `eye targets: ... shared=` | `0`. `1` means the two eyes share a target |
| `render passes: eye0=N eye1=N distinctTargets=N` | all three equal (**over-reports under `-SkipEye`** - `39` O30) |
| `idx coverage: drawn/overridden/covered` | all equal. Currently 23/23/23 |
| `fb census: N pairs, redirected pair = N` | the world's pair IS the redirected one |
| `pass targets: eye0=.. set=N \| eye1=.. set=N` | two distinct targets, both `set=1` |
| `PREDICTION:` | the expected px, printed before anyone looks |

### 3. The knobs that did the work (stereo harness)

```powershell
.\vr.ps1 -Flat -Offset 500     # 1000-unit separation. Any per-eye response is enormous
.\vr.ps1 -Flat -SkipEye 0      # run ONE pass alone. THE knob that cracked it - docs\56
.\vr.ps1 -Flat -SkipEye 1
.\vr.ps1 -Flat -PresentEye 0   # force BOTH halves to one eye's target
```

**`-SkipEye` is the most valuable diagnostic in the project.** Running one pass
alone proved each pass is individually correct, which turned the search from
"which input is wrong" (five wrong answers) into "what replaces the output".

**`-ForceEye` is DEAD under `-Flat`** - `39` O24. Use `-Offset 0` to falsify.

### 4. Does the world hold still

```powershell
.\vr.ps1 -NoHeadTranslate      # rotation only
.\vr.ps1                       # everything
```

**Gate: turn your head and the world stays put.** That is the whole of 3f-4.

If it swims, work one axis at a time — `-YawSign -1`, then `-PitchSign -1`, then
`-RollSign -1`. Separately, because an inverted pitch and an inverted roll look
alike when both are wrong at once.

`gevr.log` now prints, once a second:

```
[gevr] head: x=.. y=.. z=.. units (0.412 m up), eye sep 6.31 units
```

**Read it before judging anything by feel.** Crouch and `y` should go clearly
negative; jump and it should spike ~40. **A `y` that never moves means the pose
is not reaching the render at all** — and that is the specific failure where the
world appears rigidly attached to your head, because the compositor is being told
the image came from a viewpoint it did not.

`eye sep` is the headset's real IPD in game units. **If it does not read close to
6.3, `16`'s 100 units/metre is wrong by that ratio** — which would explain the
"too far apart" report on its own, without the eye sign being involved at all.

### 5. Close it properly, once, and check the log

**Before any long session.** With a live session, close the window and confirm
all four lines, in order:

```
[gevr-xr] shutdown: session ended
[gevr-xr] shutdown: gpu idle
[gevr-xr] shutdown: xr session destroyed
[gevr-xr] shutdown: complete, clean
```

**CORRECTED 2026-08-23 — `63`: all four have now executed, in order, TWICE,
with a live session.** Before that, steps 1 and 2 had never run — every close
since the `29` fix went through the no-session path because the headset was
asleep. Anything missing
names the step that failed. The failure this guards against previously **took the
whole machine down**, not just the game.

### 6. Then the open question — measure, then swap, then sweep

**Read `eye sep` from `gevr.log` first.** It is a number the program prints
about the thing in question, and it costs nothing. At `-UnitsPerMetre 100` it
must read **~6.35** for a 63.5 mm IPD. If it does, the separation is correct by
construction and only the scale is left; if it does not, no scale sweep will
help and the fault is in the host.

```powershell
.\vr.ps1 -SwapEyes             # THE eye-swap test. Pose and frustum together
.\vr.ps1 -ForceEye 0           # falsification: one eye to BOTH. Depth MUST collapse
.\vr.ps1 -UnitsPerMetre 50     # scale. World reads twice as large
```

**`-ForceEye` is DEAD under `-Flat`** — corrected 2026-08-23 while verifying
`50`. `g_forceEye` is declared, parsed and applied only in
`src\main\ge_vr_xr.cpp`, and `vr.ps1` sets `GE_VR_XR` only when **not**
`-Flat`. So under `-Flat` nothing reads it, while `vr.ps1` still prints
`FORCE EYE 0 - depth MUST collapse`. **A knob announcing a state it is not in —
rule 6, and `32`'s `-Sign` in a new place.** It is valid only with the XR path
live. Under `-Flat` the falsification is **`-Offset 0`** (→ ~0 px disparity)
and **`-Offset 1.6`** (→ half). `39` O24; fixed by edit 5 of `50`.

**Do not use `-Sign -1` for this.** `ge_vr_head_transform` never reads
`GE_VR_EYE_SIGN`, so with head tracking on it changes the log line and nothing
else — a knob whose consumer was removed by `30`'s "each eye uses its OWN pose"
decision, which would return a confident false negative. `32` has the source.
`vr.ps1` now warns if you try it. It is still meaningful with `-NoHead`, which
tests the 3f-3 path that 3f-4 replaced.

**Also**: `-NoHeadTranslate` sets **both** eyes to the same viewpoint, because
in 3f-4 the separation *is* the per-eye position. It is rotation-only *and*
depth-free. That is the build working as written, not tracking failing — see
`32`.

---

## SUPERSEDED - the old "open question"

**Everything in this section is VOID.** It reasons about eye sign and scale
assuming two images exist. `-Offset 500` produced **zero** difference between
the halves (`57`), so no sign, scale, IPD or units-per-metre question can be the
blocker. Kept as the record of what was believed.

## The old open question - stereo geometry (VOID)

Reported from play, on the **3f-3** build:

> the left and right eyes were too far from each other — the gun was visibly two
> of them when I had both eyes open. Also, very close.

**Retest on 3f-4 first.** A head-locked world was one of the confounds and it is
now gone.

Two candidates remain, and the order matters:

1. **The eyes are swapped.** Images that refuse to fuse and sit as two mean the
   eyes are being asked to **diverge**, which they cannot do. Swapped eyes
   produce exactly that, worst on near objects like the gun. `25` closed 3e with
   `GE_VR_EYE_SIGN` resting on **argument rather than observation** — but `32`
   found that `30` removed the quantity it flipped, so the test is now
   `-SwapEyes` (`GE_VR_EYE`), which swaps pose and frustum as a pair and cannot
   make them disagree.
2. **The scale is wrong.** Too much separation makes the world read *miniature
   and close* — but it still fuses. `16` derived ~100 units/metre from Bond's eye
   height, called it **"a derivation, not a measurement"**, and wrote its own
   falsification: *"If it looks like three metres or three centimetres, the
   derivation is wrong."*

**Sign before scale.** Sweeping the scale first means tuning a number that cannot
fix a divergence.

Three independent ways to settle the scale, none of which depend on judging
depth — worth using, since depth judgement is exactly what is in question:

- **`eye sep` in the log.** Should read ~6.3 units for a 63.5 mm IPD.
- **A physical crouch or jump.** Head translation is the only quantity in the
  build with a known real-world size. Crouch until your view reaches something
  whose in-game height you know.
- **A doorway.** Whichever `-UnitsPerMetre` makes one feel like a doorway **is**
  the measurement `16` asked for. Record it there.

---

## CLOSED — the viewmodel "contradiction" was B1 all along (`65`)

**Everything below is explained.** The gun doubles because EVERY object doubles:
two identical images submitted with two different eye poses cannot fuse. It is
not the viewmodel's own depth and it needs no slice. Kept as the record.

### The old reasoning

The gun **doubles**. The docs predicted it would "read as flat" because it rides
the camera rather than the eye — and flat means identical in both eyes, which
fuses uncomfortably at infinity. **Doubling is the opposite failure**: full eye
displacement at a distance too near to fuse.

So the Phase 3 plan for the viewmodel is aimed at the wrong problem and should be
re-derived from observation rather than from that prediction.

Separable from scale: if at a corrected `-UnitsPerMetre` the world looks right
and the gun still doubles, it is the viewmodel's own depth, and its own slice.

---

## What is verified, and what is not

| | |
|---|---|
| XR off | Closes cleanly. **Never break this.** (It reads "60 fps" in the log; that is the **N64's VI clock**, not the framerate — `60`) |
| XR on, headset asleep | Retries rather than disabling itself; closes cleanly |
| Startup crash | Fixed — `27` |
| The two eyes | **Render the SAME IMAGE.** `49`'s root cause was *a* cause, not *the* cause — `50` |
| Exit taking the machine down | **Incomplete — `29` fixed ONE path.** Teardown can still free GPU resources mid-use: `WaitForSingleObject(...,1000)`'s result is discarded and `shutdown: gpu idle` is printed unconditionally — `49` O21 |
| Eye 0 is the left eye | Confirmed by the red/blue tint test — `27` |
| 3f-3, the game in the headset | **Worn and confirmed** |
| 3f-4, head tracking | **Worn and confirmed** — `36` |
| 3f-5, recentre | **Worn.** origin varies per session (4.55 m, then 1.16 m); corrected y ~ 0 — `36` |
| Full-session shutdown | **BROKEN. REVERTED FROM DONE — `64`.** 100% reproducible crash: `PresentQueue::threadPresent` -> `VIRenderer::render` -> `setTexture` -> `setSRV`, access violation reading 0x2C, AFTER `teardown: present thread drained` prints. That line is false. None of the four `shutdown:` lines print |
| Eye sign | **Closed** — the knob's consumer was deleted by `30`. Never anything there — `36` |
| Eye separation | **Measured correct.** 6.33 units at 100 u/m = 63.3 mm — `36` |
| Hip-fire aim vs head | **Decoupled, confirmed worn.** Aim mode is not — `36` |
| Stereo fusion | **Still broken, and now measured WORN — `65`. 0 px disparity against a predicted -124.7; halves pixel-identical, corr 1.0000 at dx=0.** THE ONLY BLOCKER |
| Frame interpolation as the cause | **ELIMINATED.** `rr_option: "Original"`, 60 passes, still identical — `57` |
| Each eye pass in isolation | **CORRECT. Measured at 1000-unit separation** — `57` |
| The world's framebuffer pair | **IS the redirected pair. Measured** — `52`. `50` Risk 1 is dead |
| Per-eye transform buffers | **Distinct. Measured** — `51`. Was not the cause |
| Whether the two passes render different pixels | **NEVER MEASURED.** The one gap left — `53` |
| Eye render targets | **Distinct and published, both eyes. Measured `shared=0`** — `50` |
| Vertical eye alignment | **0 px. Measured correct** — `47` |
| Panel cant | **0.097 deg. Parallel, not the cause** — `47` |
| MSAA breaking stereo | **Impossible now** — forced off under VR, `43` |
| Scale | Derived, never measured |
| `47`'s image conclusions | **VOID** — measured on a build with one image in both eyes — `49` |

**The ledger above is a summary. `39` is the task board and is authoritative for
what is open.**

---

## The environment, as of 2026-08-23 late — `48` item E

**Check these before trusting any cross-session comparison.**

| | |
|---|---|
| Runtime | Pimax OpenXR 0.1.0, Crystal Super, 5838x4498 per eye (changed silently once — `40`) |
| `-Flat` window | 1600x900 client area, **800-px halves**. The disparity prediction scales to the half-width |
| `graphics.json` `rr_option` | **`"Manual"` / `rr_manual_value: 90` — restored and verified 2026-08-23 late.** `57` borrowed it as `"Original"` and put it back. Backup `graphics.json.bak-pre57`. The in-game menu rewrites this file, so re-check after any menu visit |
| `graphics.json` `msaa_option` | `"None"`. Required — RT64 ignores render target overrides under MSAA (`43`) |
| `graphics.json` `ds_option` | **`2` AS OF 2026-08-24 — CHANGED, AND THE CHANGE IS A RESULT.** `108` §3: supersampling at 2x removes the distant shimmer, confirming the head-glitch/flicker fault is **missing antialiasing** (MSAA is forced off by `43`, so this is the only AA available). Backup `graphics.json.bak-preDS2`. **ITS GPU COST IS UNMEASURED — the fps line was never read (O89), and `49`'s O22 lives in this territory.** **Every number in `103`-`106` was taken at `1`, so PIN IT BEFORE ANY COMPARISON — `107` §5.** (This file long said `4`; `49` corrected it to `1`) |
| Machine stability | **Six kernel bugchecks in 10 hours**, all `0x139 (0x3)` LIST_ENTRY corruption. Consistent with `49`'s memory/EXPO instability finding, NOT this project — `-Flat` never sets `GE_VR_XR`, so O21's teardown cannot be the mechanism. Re-test at JEDEC before attributing anything here |
| Version control | Both repos are git, **local only, no remote — by choice.** A remote comes when there is a product worth publishing; until then a commit is a local restore point and needs no account. **Both repos committed clean 2026-08-23 10:30** (`GoldenEye64Recomp` 37 commits on `goldeneye-vr`, `GoldenEyeVR` 23 on `main`) |

## How to run

```powershell
cd C:\Users\pdbar\Desktop\GoldenEye64Recomp
.\vr.ps1                    # head tracking, live FOV
.\vr.ps1 -UnitsPerMetre 50   # THE MEASURED WORLD SCALE (`77`). The default of
                            # 100 is `16`'s derivation and reads ~2x too small.
                            # PUT THE HEADSET ON AND PRESS F9 BEFORE JUDGING IT
.\vr.ps1 -Flat              # NO HEADSET. Both eyes side by side in the window
.\vr.ps1 -NoXr              # baseline, no VR at all
.\build.ps1                 # build. Use this, not the raw cmake line
```

**`-Flat` is the most useful thing `49` added.** It makes stereo measurable from
a screenshot - no headset, no mirror recording, no hoping the camera was still
during a video. Screenshot it, split at the seam, cross-correlate, and compare
against the `PREDICTION:` line the log prints. A gate with a number in front of
it rather than an impression, which is what `47` O19 asked for.

**`build.ps1`** disables MSBuild's lingering node-reuse workers and the `vctip`
telemetry uploader, filters ~200 benign warnings so a real error is visible, and
warns when `gevr.log` predates the exe - `07` GOTCHA 4, which has cost two rounds.

**The working directory must be the repo root.** `gamecontrollerdb.txt` lives
there and SDL null-derefs without it — double-clicking the exe in Explorer
crashes it.

`vr.ps1` clears every `GE_VR_*` variable before setting the ones it wants. A
leftover from a previous experiment is otherwise indistinguishable from a change
that did not work, and that has already cost one wrong diagnosis.

Start SteamVR and **wake the headset** first. If it dozes, the build now retries
rather than giving up on the run, but it will sit there logging nothing useful.

### Environment variables

```
GE_VR_XR=1               enable OpenXR (off by default)
GE_VR_XR_LEVEL           0 session only, 1 frame loop no layer, 2 full (default)
GE_VR_XR_FORCE_EYE       0 or 1 — one eye's image to BOTH eyes. XR PATH ONLY (dead under -Flat, 39 O24)
GE_VR_FRUSTUM=1          per-eye frustum (needs the patch in HOSTEYE mode)
GE_VR_SBS=1              ON BY DEFAULT. NOT a debug view - the headset FREEZES
                         without it (2/2 vs 2/2). docs\65. -NoSbs to reproduce
GE_VR_FIT_ASPECT=0       raw eye frustum. Correct for the headset
GE_VR_EYE                0 left, 1 right - SWAPS the two parameter sets. The eye-swap test
GE_VR_EYE_SIGN=-1        flips the eye displacement. IGNORED when head tracking is on (32)
GE_VR_TEST_OFFSET        lateral offset in game units. IGNORED when head tracking is on
GE_VR_HEAD=0             head pose does not drive the view (reverts to 3f-3)
GE_VR_HEAD_TRANSLATE=0   rotation only, no leaning
GE_VR_LIVE_FOV=0         hardcoded Pimax tangents instead of per-frame FOV
GE_VR_HEAD_YAW_SIGN      -1 flips yaw
GE_VR_HEAD_PITCH_SIGN    -1 flips pitch
GE_VR_HEAD_ROLL_SIGN     -1 flips roll
GE_VR_UNITS_PER_METRE    default 100 (docs\16). Drives IPD *and* head translation
```

**`GE_VR_UNITS_PER_METRE` DOES THREE JOBS AND THAT IS THE PROBLEM — `86` §3.9.**
Perfect Dark needs **three independent scales**: one for the eye separation
(`vr_world_scale`), one for head height → eye height (`unitsPerCm`, and in real-
height mode it is **1 real cm = 1 game unit**, i.e. 100 u/m), and one for how far
a physical step carries you. **Ours is one knob driving all three, which is why
100 vs 50 was reported as "it looks the same" while the log showed the eye
separation genuinely halving** (`77`). **`86` slice S1 splits it, and until it is
split no scale sweep can answer anything** — `77`'s measured ~50 and PD's 100 may
not even be about the same quantity.

**MSAA must stay off** — RT64 ignores render target overrides under MSAA, so
stereo silently stops working. It is already off in `graphics.json`.

### Graphics settings that matter

`%LOCALAPPDATA%\GoldenRecomp\graphics.json`:

- `rr_option: "Manual"`, `rr_manual_value: 90` — was `"Display"`, which follows
  the **monitor** (60). Backup at `graphics.json.bak-preVR`.
- `msaa_option: "None"` — required, see above.
- `ds_option: 1`. **Correction: this file long said `4`. It is `1`** — `49`.
  And `-ResScale` makes things **slower**: 8x fewer pixels ran 4x slower (60 to 16
  fps). Do not reach for resolution as the framerate knob until `49` O22 is
  understood.

---

## Architecture, as built

| Concern | Owner |
|---|---|
| Culling frustum, 106 deg | patch, `RECOMP_PATCH viSetFovY` |
| `viGetFovY` divides the widening back out | or the game believes it is permanently zoomed |
| Per-eye frustum and eye transform | RT64 `ProjectionProcessor`, via `VrEyeParams` |
| Two eye images, offscreen, at headset resolution | RT64 `PresentQueue::threadPresent` — `28` |
| Copy into the OpenXR swapchain images | host, `ge_vr_xr.cpp` |
| Head pose and FOV | host, `ge_vr_head_transform` — `30` |
| Render hooks | **chained, never replaced** — `27` |
| Teardown | **the deinit hook, not the destructor** — `29` |

**RT64 knows nothing about OpenXR.** Its side is "render the two eyes into
offscreen targets of this size and publish them" — generic, MIT, upstreamable —
while every OpenXR line stays in the host. That split falls along the licence
boundary without being contrived to.

Two conventions, with different standing:

- **The frustum convention is known.** Measured `XrFovf` tangents were fed
  straight into `VrEyeParams` and produced correct stereo twice. That could not
  work if RT64's view space disagreed with OpenXR's.
- **The rotation convention is not.** It does not inherit that evidence, which is
  why it has per-axis sign knobs and an unfired gate.

---

## Diagnostics — use these before reasoning about a crash

Added in `27` after four rounds had been spent inferring crash locations from
where the log stopped. They have since resolved three crashes in about two runs
each. **Reach for them first.**

- **Unhandled-exception filter**, installed under `GE_VR_XR`. Writes the
  exception code, read vs write, the faulting address, and every stack frame as
  `module+RVA` into `gevr.log`.
- **`/MAP`**, already configured. Resolve an RVA against
  `build\Release\GoldenRecomp.map`, preferred base `0x140000000`:

```python
import re, bisect
syms=[]
pat=re.compile(r'^\s+\d{4}:[0-9a-f]{8}\s+(\S+)\s+([0-9a-f]{16})\s')
for line in open('build/Release/GoldenRecomp.map', errors='ignore'):
    m=pat.match(line)
    if m: syms.append((int(m.group(2),16), m.group(1)))
syms.sort(); addrs=[s[0] for s in syms]
rva = 0x517692                       # from the [gevr-crash] line
i = bisect.bisect_right(addrs, 0x140000000+rva) - 1
print(syms[i][1], hex(0x140000000+rva-syms[i][0]))
```

- **`GetDeviceRemovedReason()`** at end of frame. A removed D3D12 device is
  reported nowhere else and surfaces as somebody else's crash several steps later.
- **`GE_VR_XR_LEVEL`**, the bisect ladder as a runtime knob.
- **The head log**, once a second. See "Do this first", step 2.

- **The runtime capability block**, once per session: per-eye pose and
  orientation, panel cant, frustum aspect against the real target aspect. Both
  a portability check and the thing that killed the cant hypothesis by
  measurement. `41`.
- **The stereo starvation warning.** Shouts if eye 0 renders and eye 1 does not.
  (Currently false-positives in menus — see `39` O17.)

**When a crash cannot be reproduced under a debugger, make the program report its
own failure rather than inferring harder — and this applies to APPEARANCE, not
only to crashes.**

### The mirror measurement — the only diagnostic that settled an image question

1. Record the headset mirror (e.g. "Pimax Mirror - Both") while playing.
2. `ffmpeg -i rec.mp4 -vf "select='eq(n\,60)'" -vsync 0 f%02d.jpg`
3. Split each frame in half and cross-correlate the halves for the (dx, dy) that
   aligns them.
4. Compare against the value predicted from the live tangents — so it is a gate
   with a number, not an impression.

**Why it works: a mirror shows the submitted IMAGE and never the metadata.**

| Mirror | Lenses | Means |
|---|---|---|
| wrong | wrong | the images are wrong |
| **right** | **wrong** | **the images are right; the pose/FOV submitted with them is wrong** |

That distinction separated a render bug from a pose bug twice in one session.
`47` has the worked example.

**`gevr.log` is rewritten on every launch.** After anything interesting:
`copy gevr.log gevr-keep-<what>.log`. A full crash stack trace was lost this way.

---

## Build

```powershell
$env:PATH = "C:\Program Files\LLVM\bin;C:\Program Files\CMake\bin;C:\Users\pdbar\AppData\Local\Microsoft\WinGet\Links;" + $env:PATH
cd C:\Users\pdbar\Desktop\GoldenEye64Recomp
cmake --build build --target GoldenRecomp --config Release --parallel
```

1. **`--target` skips CMake regeneration.** Adding a source file or editing
   `CMakeLists.txt` needs `cmake -S . -B build` first, or the build succeeds
   while silently ignoring the change. `07` GOTCHA 4.
2. **A new `RECOMP_PATCH` name needs the long build** with
   `tools_weaken_patched.py`. **Currently 45 unique names across 46 sites,
   counted from source 2026-08-23 — `87` read 6, RECOUNTED in `91`. This line
   long said 31; `87` first answered 47/48 by matching COMMENT PROSE.** `07`
   has the sequence.
   Adding code to an existing patch file does not count; only a new *name* does.
3. **No console** (`/SUBSYSTEM:WINDOWS`). Everything goes to `gevr.log` in the
   repo root, rewritten each launch. **RT64's own `fprintf(stderr, ...)` failure
   reports go nowhere at all** — `27` lost a round to one of them.
4. **Check `gevr.log`'s timestamp against the exe's** before concluding anything
   from it. Two rounds were once spent analysing a log that predated the binary.

---

## ►► THE TWO REPOSITORIES — READ THIS BEFORE YOUR FIRST COMMIT ◄◄

**Rewritten `257`, 2026-08-29, from a live read of the disk and of
`commit-session.ps1`. The previous version of this section named the wrong two
repositories and pointed at a `goldeneye-native` that has since moved.**

> ## **THERE ARE EXACTLY TWO REPOSITORIES, AND `commit-session.ps1` COMMITS BOTH
> ## OF THEM IN ONE CALL, WITH ONE MESSAGE.**

| | **`GoldenEyeVR`** | **`GoldenEye64Recomp`** |
|---|---|---|
| On disk | `Z:\Desktop\GoldenEyeVR` | `Z:\Desktop\GoldenEye64Recomp` |
| Remote | **NONE. Local only.** | `github.com/cblock85/...` — **not yours** |
| Holds | **all docs**, `patches/`, `tools/`, `xr/`, the commit messages | the thing that builds and runs the recomp |
| Licence | — | mixed; links GPL-3.0 `N64ModernRuntime` |

> ### ►►►► **`Z:` IS A MAPPED NETWORK DRIVE TO A NAS, AND GIT REFUSES BOTH
> ### REPOS UNTIL GIVEN AN EXCEPTION.** ◄◄◄◄
> `Z:\Desktop` → `\\NAS\Double 6TB\User folder Data\Desktop`. Git resolves the
> mapping, sees a UNC path owned by someone other than the local user, and
> refuses: **`fatal: detected dubious ownership` → `git add FAILED` → nothing
> staged, nothing committed, in EITHER repo.** That is git's CVE-2022-24765
> mitigation working as designed, not a broken repo.
>
> **ONE-TIME FIX. Run once per machine; it persists in the global config:**
> ```powershell
> git config --global --add safe.directory '%(prefix)///NAS/Double 6TB/User folder Data/Desktop/GoldenEyeVR'
> git config --global --add safe.directory '%(prefix)///NAS/Double 6TB/User folder Data/Desktop/GoldenEye64Recomp'
> ```
> **`commit-now.ps1` pre-flights all three repos and offers to add them** — it
> asks, because this writes to the global git config. `goldeneye-native` needs
> its own entry when it is first committed. **`257` §7.1.3.**
> **Do NOT reach for `safe.directory '*'`** — it disables the check for every
> repository on the machine, forever.

> ### **THE DESKTOP IS REACHABLE BY TWO PATHS AND BOTH ARE LIVE.**
> **`Z:\Desktop\...` is the current one** (owner, 2026-08-29). Older documents —
> including `147`'s launch command and every banner before `29e` — say
> `C:\Users\pdbar\Desktop\...`. **They refer to the same folders.**
> **DO NOT HARDCODE EITHER ONE IN A SCRIPT.** `commit-session.ps1` did, on the
> `C:` form, and would have silently reported "NOT FOUND" and committed nothing.
> Both it and `commit-now.ps1` now resolve from `$PSScriptRoot`. `257` §7.1.

### THE THREE THINGS THAT LOOK LIKE A THIRD REPO AND ARE NOT

1. **`GoldenEyeVR\repo\` HAS NO `.git`.** `[MEASURED]` on the bridge. It is a
   plain subfolder of `GoldenEyeVR`. **`repo\docs\` commits with `GoldenEyeVR`
   and nothing special is needed for it.** Do not go looking for a repo there.
2. **`GoldenEyeVR\goldeneye-native\` IS its own git repo** — remote
   `github.com/SegfaultEvan/goldeneye-native`, branch `main` — **and it is
   GITIGNORED by the parent** (`GoldenEyeVR\.gitignore:46`). **It is NOT one of
   the two. `commit-session.ps1` does not touch it.** Committing the native
   port is a separate, manual act in that directory.
3. **`local-only\goldeneye-native\...` and `local-only\prior-art\`** are also
   gitignored nested repos (`.gitignore:23`, `:33`). Historical; not the live
   native tree.

> **`[MEASURED]` `git status` IN EITHER REPO TIMES OUT ON THE LINUX BRIDGE** —
> twice, at the 120 s cap, on 2026-08-29. `commit-session.ps1`'s own comment says
> why: recursing `GoldenEye64Recomp`'s `lib/ge` submodule exceeds the bridge's
> 45-second limit. **Use `--ignore-submodules=all`, or read git state at the main
> PC. This is not a hang; it is the documented behaviour.**

---

## ►► THE COMMIT COMMANDS. THESE, VERBATIM, EVERY SESSION. ◄◄

**AT THE MAIN PC, NOT THROUGH THE LINUX BRIDGE** (`48`, `148` item 11). **The
bridge cannot delete files, so every lock it creates is permanent — that wedged
`GoldenEyeVR` for two whole sessions.** `commit-now.ps1` refuses to run anywhere
else.

> # ►► **DOUBLE-CLICK `COMMIT-NOW.cmd` IN `Z:\Desktop\GoldenEyeVR`.**
> # ►► **THAT IS THE WHOLE PROCEDURE. IT DOES BOTH REPOS.** ◄◄

It finds the newest `COMMIT-MESSAGE-*.txt`, prints the subject line, **runs a
dry run and shows you every file it would stage, asks y/N, and only then
commits.** Then, separately, it offers `goldeneye-native` if that repo has
changes and a `-native` message file exists. **Nothing is pushed, ever.**

**DO NOT right-click `commit-session.ps1` → Run with PowerShell.** `-Message` is
a **mandatory** parameter, so Explorer drops you into an interactive `Message:`
prompt that a multi-line body cannot be pasted into. `COMMIT-NOW.cmd` exists to
remove that trap.

### The same thing by hand, if the wrapper is ever in the way

```powershell
cd Z:\Desktop\GoldenEyeVR
.\commit-session.ps1 -Message (Get-Content .\COMMIT-MESSAGE-<date>.txt -Raw)
```

Add `-DryRun` to stage and show without committing. And the native port, which
the script does **not** pick up:

```powershell
cd Z:\Desktop\GoldenEyeVR\goldeneye-native
git add -A
git commit -F ..\COMMIT-MESSAGE-<date>-native.txt
```

> ### **THE PARAMETER IS `-Message`, NOT `-MessageFile`.**
> **`-MessageFile` DOES NOT EXIST and the call fails.** `[READ]`
> `commit-session.ps1:37-42` — the only parameters are `-Message` (mandatory
> string) and `-DryRun`. **The `2026-08-29c` HANDOVER banner said `-MessageFile`
> and it was copied forward twice before anyone opened the script.** Hence
> `-Raw`: it reads the file into the one string the script actually wants.

**WHAT THE SCRIPT DOES, so you can trust it:** clears stale `.lock` files first,
stages with `git add -A` (both `.gitignore`s already exclude `*.bak*`,
`gevr-*.log` and build output — verified, not assumed), **prints what it staged
BEFORE committing**, then verifies the tree is clean afterwards. A commit that
succeeded and left the tree dirty missed something and looks identical to one
that did not.

**BOTH REPOS ARE LOCAL ONLY. EVERY COMMIT EXISTS ON ONE DISK.** `GoldenEyeVR`
has no remote at all; `GoldenEye64Recomp`'s origin is cblock85's. **See
`PUBLISH-MANIFEST.md` before adding a remote — `local-only/` must not go to a
public one.**

> **EVERY GIT COMMIT IS THE OWNER'S.** The assistant never commits, stages,
> branches, merges, resets or tags. **Reading git state is fine.** The
> assistant's job is to leave the message file ready and the command written out.

---

## Version control

Nothing was committed until 2026-08-22. Both repos are now under git, **locally,
with no remote of ours.**

| Repo | State |
|---|---|
| `GoldenEye64Recomp` | branch **`goldeneye-vr`**, **37 commits**, clean as of 2026-08-23 10:30 |
| `GoldenEyeVR` | branch `main`, **23 commits**, clean as of 2026-08-23 10:30 |

**If a commit fails, look for a stale lock before assuming anything else.**
`GoldenEyeVR/.git` held `index.lock`, `HEAD.lock` and `objects/maintenance.lock`
from **2026-08-22 23:55**, all zero-length, with no git process running. **The
repo had been unable to accept a commit since that moment** — which is the real
reason `48` floor item 1 stayed outstanding across two sessions. It was not
being skipped; it was failing, and nothing said so out loud.

```powershell
Get-ChildItem .git -Recurse -Filter *.lock     # then check no git.exe is running
```

**CORRECTED 2026-08-23 — the bugcheck was probably NOT the cause.**

The same two files, **`HEAD.lock` and `objects/maintenance.lock`, both
zero-length**, were recreated deliberately-by-accident in one command: running
`git commit` through a tool that **cannot delete files**. Git writes each lock,
does its work, then unlinks it — and when the unlink fails the commit still
succeeds while the locks are left behind, with no error that stops anything.
The next `git` invocation then refuses.

**The signature matches exactly**: the same two paths, both zero length, no git
process running. A bugcheck would not reliably produce that pair and nothing
else.

**The rule:** run git from a shell that can delete. In this environment that
means the Windows side, not the Linux bridge — the bridge cannot `rm`, so every
lock it creates is permanent. Recovery is one line:

```powershell
Get-ChildItem .git -Recurse -Filter *.lock | Remove-Item -Force
```

Kept because `57`'s bugcheck attribution is still *possible* and has not been
disproven — but it is no longer the leading explanation, and a session that
believes it will go looking at the wrong layer. Rule 10.

Sliced by concern, not by session: build fixes, interpolation, the VR patch and
host boundary, RT64 per-eye rendering, the OpenXR host, the handoff material,
3f-4, and the head log.

**Committing is LOCAL and needs no GitHub.** This was worth stating plainly: the
recurring "nothing is committed" line read as a demand for a remote, which is
not what it meant and not what the project needs yet.

Before adding a remote, whenever that happens:

- **`origin` in `GoldenEye64Recomp` is cblock85's.** Pushing needs your own fork
  or a fresh repo.
- **`GoldenEyeVR/local-only/` is tracked deliberately but must not go to a public
  remote.** `PUBLISH-MANIFEST.md` has the split: RT64 changes are MIT and belong
  upstream, the recomp host links GPL-3.0 and stays local.

Ignored on purpose: `*.bak*` (the same changes are captured as diffs in
`ge-vr-handoff/diffs/`), `gevr*.log`, and the two fetched third-party Windows dep
folders — the upstream rules already exclude their `.lib`/`.dll`, so tracking
them would commit headers without libraries.

---

## Roadmap

**Next, once the geometry question is settled:**

- **Phase 3, decoupled aim.** **Partly done already** — hip fire is decoupled and
  was confirmed worn (`36`). What remains is *hand* aim, and aim mode, which does
  lock the crosshair to the head. `37` has the concept, `38` the firing path.
- **The viewmodel**, re-derived from observation — see above.

**Known and not blocking:**

- **The target framerate does not come from the headset.**
  `ultramodern::get_target_framerate` chooses between Original, Manual and the
  **monitor's** rate. **CORRECTION (`49`): the headset's rate was NEVER queried
  or logged - that code does not exist.** This project assumed 90 Hz for its
  whole life from a sentence describing nothing.
  `XrFrameState::predictedDisplayPeriod` now prints it as `DISPLAY PERIOD`.
  **Read it before calling 60 fps a performance problem.** It runs at 90 only because `rr_manual_value` happens to be 90 — a
  different headset, or a 120 Hz panel, would silently stay wrong. Belongs with
  the frame-pacing interlock `12` §5 deferred.
- **Head translation is unclamped** (`31`). Stand on a chair and the viewpoint
  goes through the ceiling; crouch and it goes through the floor. Phase 4's
  head-in-geometry fade needs to consider **vertical position, not only walls**,
  and jumping reaches the problem faster than walking into a wall does.
  **CORRECTED 2026-08-23 — `86` §3.3: a fade is not needed for the vertical
  half.** Perfect Dark writes the candidate eye height into the player's crouch
  offsets, asks the game's own **`bwalkCanMoveUpwards`**, restores the fields and
  keeps the last known-good height. Fifteen lines, no fade, and the counterpart
  query in our tree is read 4 of `86` §8. **The horizontal half is a separate
  and better-answered problem — `86` slice R1: probe on sight-blocking geometry,
  not on walls, which is what lets you lean over a balcony rail.**
- **The recentre key.** `LOCAL` space is anchored wherever the headset was at
  session start. A key that rebuilds it at the current head pose would remove any
  dependence on SteamVR's floor calibration, which resets constantly on this rig.
  Offered, ~20 lines, not built. **The floor calibration does not affect our
  image** — we use `LOCAL`, not `STAGE`, precisely because `10` measured the floor
  2.4-3.2 m out.
- **Explosion effects stick to the view when turning** (`23`). Pre-existing, in
  the interpolation layer. Next slice is a `GE_IDBAND_EXPLOSION` around
  `explosionRenderPropExplosion` (`explosion.c:851`), same pattern as
  interpolation slice 6.
- **Frame pacing.** `26` predicted judder from `xrWaitFrame` owning the cadence.
  **IT HAS NOW APPEARED — this line was false and is corrected here, `71`/`72`.**
  The submit loop is NOT the cause: 516 samples, one over the 11.11 ms budget,
  ~87% of every frame blocked in `xrWaitFrame`. **But those are means, and a
  mean cannot see a hitch.** `73` adds a candidate that predicts WHEN: the
  game's own VI clock halves to 30 in heavy scenes while the renderer must still
  produce 90, so the interpolation stretch triples exactly when the scene gets
  busy. Falsifier, no code: if it judders equally standing still, that is wrong.
- **Peek** (`31`) — a bindable raised viewpoint, planned, **deliberately off the
  VR critical path.** In a headset it is already redundant: physically standing up
  does the same thing, view-only, through the same code path.

---

## The method, which is the actually valuable part

This project plans a slice, writes gates **before** the code, builds it, then
appends what the plan got wrong. The docs are that record. Three rules have been
paid for:

**Ask of every gate: what would this build have to do differently for this to
fail?** Five gates have been specified that a *working* build would have failed.

**Check who else writes what you write.** `21`: a patch changed a value the game
inspects. `26`: a value the game reads back and compares against a literal. `27`:
a global function pointer the host owns. Same shape three times.

**Know who destroys what you build, and when.** `29`: "`app` is a member, so it
is alive in the destructor" was true and irrelevant — the object was alive and
already gutted, because its teardown is a method someone else calls, not its
destructor.

And the one that pays every time: **when a crash cannot be reproduced under a
debugger, make the program describe its own failure.**

---

## The phantom documents — `41`, `42`, `43`, `45`, `46`

**Found 2026-08-23 during maintenance. Five numbered documents are cited 37
times across the docs and the source, and NONE OF THEM HAS EVER EXISTED** — not
on disk, and not anywhere in either repository's git history (`git rev-list
--all`). `44` is cited nowhere and appears never to have been intended.

**`43` alone is cited 24 times.** It is the MSAA rule — the one that silently
destroys stereo when a menu rewrites `graphics.json` — and a session told to
"read `43`" would have found nothing.

**The work is real and shipped in every case. Only the documents are missing.**
Their reasoning survives in long source comments, which is why nobody noticed:
every citation *reads* as though it resolves.

**Stub files now exist for all five**, named `*-NEVER-WRITTEN.md`. Each says
plainly that it was never written, then quotes the surviving source comment
verbatim with its file and line. **Nothing was invented and nothing was
removed.** `42`'s stub also carries `59`'s correction, since its central premise
turned out to be false.

**The lesson for the protocol:** `48` says to write the findings doc and treat
it as the most valuable output. It does not say to check that the document you
just cited exists. **Five times, over two phases, it did not.**

## Document index

Read what you need. `27` onward is this session; everything before is background.

**Start of the trail**

| | |
|---|---|
| `01` | State of play at 3e. **Superseded by this file**; kept as the Phase 1 record |
| `02` | Windows build notes — how the toolchain was got working |
| `06` | Replicating the build from scratch |
| `07` | **Rebuild after a patch edit.** Four gotchas that each disguise themselves |
| `08` | Where everything comes from. *Its "push the bundle" urgency is now stale — see The two repositories* |

**Foundations**

| | |
|---|---|
| `03` | Phase 0 — the projection hook proved attachable |
| `04` | Interpolation, six fixes, the `#if 0` path |
| `05` | Going forward — early roadmap |
| `09` | **OpenXR probe.** Measured Pimax numbers, and `XR_API_VERSION_1_0` |
| `10` | **Stereo validated.** The tint-test warning that governs every stereo judgement since |
| `16` | **Game units.** ~100 per metre, and its own falsification |

**Phase 1, the eye split**

| | |
|---|---|
| `11` | RT64 stereo seams |
| `12` | Phase 1 step 3 design. Partly superseded; §5 defers frame pacing, §7 has the licence split |
| `13`, `15`, `17`, `18` | Steps 3a, 3b, 3c plan, 3c as built |
| `14` | Near-plane clipping. Phase 4 territory |
| `19` | The blue band |
| `20`, `21` | Gating, and the host gate — *"check who reads it back"* |
| `22` | Host import plan — the patch/host boundary mechanism |
| `23` | Explosion interpolation. Open |
| `24`, `25` | Steps 3d and 3e. **`25` is where the eye sign was settled by argument** |

**Phase 2, OpenXR**

| | |
|---|---|
| `26` | The 3f plan — four slices, and the zoom-readback bug |
| `27` | **The startup crash.** Clobbered render hook, then a typeless swapchain image. Also introduces the crash reporter |
| `28` | 3f-3 — the game's eyes at full headset resolution |
| `29` | **Teardown.** The exit that took the machine down |
| `30` | **3f-4** — live pose and FOV. The current frontier |
| `31` | Peek. Off the VR path, and what physically jumping in VR does |
| `32` | **The wear session.** The dead eye-sign knob, and the ladder to run |
| `33` | The first head-tracked session. The 4.55 m origin |
| `34` | 3f-5 plan — recentre, and splitting the head from the eyes |
| `35` | Phase 3 plan. Superseded in part by `36` and `38` |
| `36` | **3f-5 worn.** Gates 1-3 pass, and the layer-pose bug 3f-5 introduced |
| `37` | VR aim concept. Read `38`'s corrections first |
| `38` | **The firing path.** Hip fire reads `crosshair_angle`; three corrections |
| `39` | **THE TASK BOARD.** Live status, open work, next actions |
| `40` | The exit crash: teardown was intact, and the RUNTIME had changed |
| `41`-`42` | Runtime capability logging, and stopping XR at SDL_QUIT |
| `43` | **MSAA forced off under VR.** The rule a menu could undo |
| `46` | Recentre by offsetting the reference space. Two wrong versions first |
| `47` | The stereo investigation. **Its METHOD is the best thing here; its image FINDINGS are void - `49`** |
| `49` | **THE ROOT CAUSE.** One image in both eyes, why, the fix, and five falsified hypotheses |
| `50` | **B1 slice 1, BUILT AND MEASURED.** Eye targets made symmetric; G1 still 0 px. Scores three of its own four predictions wrong |
| `51` | **B1 slice 2 — the shared transform buffer.** Plan only, NOT built. M1 ran; its conclusion is corrected in place |
| `52` | **THE CENSUS — where is the world?** Answered: the world IS the redirected pair. Also found the `fb eye` probe may latch on a MENU |
| `53` | The tint bisection. Plan only — superseded by `56`'s `-SkipEye`, which answered it. Records why the VR mirror is the wrong tool here |
| `54` | Combined diagnostic — index coverage (complete) and `-PresentEye` |
| `55` | **PRIOR ART, CLOSED.** StarFox64-VR licence is UNCLEAR: read nothing. RT64 upstream is MIT with no stereo path |
| `56` | **`-SkipEye`** — run one pass alone. The knob that cracked it |
| `57` | **READ THIS FIRST. Both halves carry EYE 1's image.** Its title and first finding are WRONG and corrected in place — an impression promoted to a finding. Ends with the live hypothesis: the present-time resolve is keyed on the shared framebuffer address |
| `58` | **READ FIRST.** Hypothesis 8 falsified from source at zero cost; the four-proposition contradiction it leaves, and the plan (`-PresentEye 0`, then the final view matrix per pass) |
| `63` | **READ FIRST. THE WEAR SESSION.** Dark and stale in the headset; what it is NOT, measured; four ranked candidates; and the bisect to run before anything else |
| `61` | **THE CONTROLLER SLICE, BUILT.** Bound as `oculus/touch_controller`, not Index. Both hands tracked, five actions firing |
| `62` | The settings file: the symptom named (blurry + slower), its link to O22, and the MSAA guard that misses `-Flat` |
| `59`, `60` | The scan lines (display-side, not ours) and **the "60 fps" that is the N64's VI clock** |
| `41`, `42`, `43`, `45`, `46` | **THESE WERE NEVER WRITTEN — see "The phantom documents" below.** Stubs added 2026-08-23 that point at where each one's reasoning actually survives |
| `64` | **THE FRAME IS CORRECT AND FROZEN.** The bisect result, the present-path instrument, hypotheses 10-12 falsified, and the brightness explained away |
| `67` | **READ FIRST. RENDERDOC.** The upstream half exonerated by ground truth; the two vacuous instruments; the capture kept on disk and the exact next query |
| `65` | **READ FIRST. `-Sbs` UNBLOCKS THE HEADSET.** The 2x2, B1 measured worn at 0 px, why it doubles, and why this is a workaround |
| `48` | **THE SESSION PROTOCOL.** Start-of-session checks, and the handover checklist |

**Phase 3 — the wearable build, the hand, and 6DoF**

| | |
|---|---|
| `66` | The forward plan after `65`. Two independent tracks |
| `69`, `70`, `71` | **B1 NAMED, ROOT-CAUSED AND FIXED.** Two present draws bound the same descriptor heap slot; D3D12 reads heaps at EXECUTION time. Worn and confirmed at -117 px |
| `72`, `73` | The pacing instruments (**they report MEANS, and a mean cannot see a hitch**), and the `-NoXr` regression after B1 |
| `74`, `75` | The scale-and-judder wear session, and **THE BUGCHECK IS OURS** — `39`'s "not our bug" retracted |
| `76` | **THE HAND AND GUN PLAN.** Four slices. **Its clamp design table is superseded by `86` §3.8** — Perfect Dark chose none of the three options |
| `77`, `78` | Scale measured worn (**~50 u/m**), the viewmodel isolated, and slice 1's transform |
| `79` | Slice 2 as planned. Three corrections, all diagnosed by the wearer |
| `80` | **EVERY KNOB**, generated from the source. Which are connected, which are `-Flat`-only, and the one whose consumer was deleted |
| `81` | Prior art: Perfect Dark's VR port, and the MIT verdict. **Its "the VR code is not public" caveat is FALSE — `86` §0** |
| `82` | A first pass over that repository. Three findings, all of which survive. **Superseded by `86`, which read the whole tree; `82` finding 2 is corrected there** |
| `83`, `84`, `85` | **THE SEAM.** Where the hand transform belongs (`field_92C`/`field_8EC`, hooked at `gun.c:1230`), that it fires, and that **the gun now follows the hand** — position confirmed worn |
| **`86`** | **►► THE 6DoF PLAN. READ IT FIRST. ◄◄** Every 6DoF aspect, nine slices, gates before code, derived from Perfect Dark's source with a file and line for every claim. **Plan only** |
| **`87`** | **►► `86` §8's SIX READS, DONE. READ WITH `86`. ◄◄** The aim is TWO integrators; `field_FFC` also moves the gun model; the FOV patch disturbs `c_scalex`/`c_scaley` by 1.7667. The ceiling query and an auto-crouch already exist. Eight claims corrected at source. **Four new reads opened, all cheap** |
| **`88`** | **►► READ 7, AND THE THREE READS IT CLOSED. ◄◄** **`gunfire.c:568` aims the gun at the aim point in stock code** — `87`'s "collision" retracted, and `85`'s `-SeamNoRot` explained. `:6077` is aim mode. `sub_GAME_7F0680D4` is dead code. **A1 may need no new patch name.** Seven claims corrected at source |
| **`89`** | **►► READS 9, 10, 11 AND THE TRAP. EVERY OWED READ IS CLOSED. ◄◄** The AI reads the crouch STATE, so **H2 option B is two writes**; `bondviewUpdatePlayerCollisionPositionFields` is 95 lines and G-H2-4 is free; **the barrel is local +Z and the align points it at the aim point**. The trap is closed with **no code** — rule 12 |
| **`90`** | **►► THE BULLET IS THE CLAMPED QUANTITY. READ BEFORE A1. ◄◄** `crosshair_angle` fires the shot (8 sites); `field_FFC` points the gun model and the muzzle flash. **`86` §3.8 and `87` finding 1 both had it backwards.** No unclamped shot path exists — **A2 is not optional** |
| **`91`** | **►► SLICE S0 AS BUILT. NOT COMPILED, NOT WORN. ◄◄** The 6DoF instrument, two halves, **no new patch name — short build**. Unbuilt quantities print `n/a`, never `0`. Carries `90`'s two falsifiers with their predictions inline. Also **recounts the patch names: 45 unique / 46 sites**, because `87`'s regex counted comment prose |
| **`92`** | **►► SUPERSEDED BY `134`. ITS HEADLINE IS FALSE — DO NOT CITE IT. ◄◄** It concluded *"90 Hz is structurally unavailable... not a performance limit; no amount of PC moves it."* **`134` ran the sim at 90** (59.3 → 87.1 fps mean, 129 samples): **it was a truncating divide and a hardcoded `60` in a file nobody had opened.** **`257` §1 is the retraction of a document that cited `92` as live five days after `134` answered it — the fifth instance of `182`'s pattern.** WHAT SURVIVES: the 142/149 measurement that the sim *was* holding 60, and `73` being real but rare |
| **`93`** | **A POSE/IMAGE MISMATCH — CANDIDATE 4.** We submit a stale image with a fresh pose, which would disable the compositor's reprojection. **The MISMATCH is fact; that it is the judder is a HYPOTHESIS. Its title and headers over-claimed and `94` corrects them** |
| **`97`** | **THE TIMEWARP, BUILT.** Rotational reprojection in our own copy step. **It WORKS and it is RETIRED by owner decision — `98`.** Kept as a diagnostic |
| **`98`** | **THE WARP WENT THE WRONG WAY, THEN THE RIGHT WAY.** The inverted-delta signature, predicted before the run. Adds the MOTIONLESS `-TimewarpYaw` test — reads a pose convention with nobody turning their head |
| **`99`** | **►► THE TIMEBASE PREP. THE FORWARD PLAN. ◄◄** The judder is the VIEW sampled at 60, not the SIM at 60. **Route D — 90 real frames of a 60 Hz world — costed for the first time.** `92` §4's route B re-costed from the tree: 39 of 43 literals survive, four do not |
| **`100`** | **►► EVERY PATCH PRINT IN THIS PROJECT HAS GONE NOWHERE. ◄◄** `recomp_puts` wrote to stdout on a console-less build. **Also: `_Printf` carries one call then stops, and a `static` in a `RECOMP_PATCH` is not zero.** Fixed |
| **`101`** | **AIM MODE IS A1's ENTRY POINT, ALREADY SHIPPED.** Found by the wearer. `sub_GAME_7F067FBC` is a nine-line wrapper around the exact function `86` chose, with both dampings correct. **The arm is already unclamped; only the bullet is locked** |
| **`107`** | **►►►► `105`'s DOUBLE BUFFER WAS NEVER ONE. READ FIRST. ◄◄◄◄** The set stride was `displayFrames * 2`, and `displayFrames` alternates 1/2 at 60 into 90, so set 1's base moved onto set 0's targets. **`105`'s negative result is VOID and `106` §2 rests on it.** Also: **`106` §6 move 2 is done and its suspect is eliminated** — nothing in the sampling path is conditional on the texture changing. And the present thread's real structure, written down at last |
| **`106`** | **►►►► THREE ATTEMPTS, THREE STALLS. ◄◄◄◄** `103`/`104`/`105` at 16.3 / 25.7 / 16.3 fps against 60. **§3's "the interpolated frames are wrong" is RETRACTED BY ITS OWN §7** — `-NoXr` shows the same frames correct at 90. Route D is back, `23` is not a prerequisite, and the character misplacement is OURS. **Its §2 is now unsupported — `107`** |
| **`105`** | **NEITHER THE CPU NOR THE GPU.** §3's elimination survives `107` and is the most useful thing in it: eye passes rendered fell 90/s → 31/s while time per frame more than doubled — work down, time up, which is waiting. **Its option-A double buffer did not work as written — `107` §2** |
| **`104`** | **►►►► PUBLISH THE PASSES PROPERLY. BUILT, NOT WORN. ◄◄◄◄** `103`'s naive publish drove `reused` to 0 and fps to 16. **The present queue already walks the passes in lockstep; index the eye targets the same way and inherit the same guarantee.** `interpUsed=` is the gate |
| **`103`** | **►►►► THE INTERPOLATED EYE FRAMES ALREADY EXIST AND WE DISCARD THEM. ◄◄◄◄** `rt64_workload_queue.cpp:1352` publishes only `frame == 0`. **`submits=90 renders=60 reused=30` is a publish guard, not a GPU limit.** Supersedes `99` §3's gate and `99` §5's order |
| **`102`** | **►►►► WHAT PERFECT DARK ALREADY SOLVED. THE VALUES. ◄◄◄◄** Read at `67ea20c`, MIT. Grip offsets, the quaternion basis, smoothing alphas, probe geometry, crouch thresholds, and seven traps they paid for. **CORRECTS `86` §3.8: they do NOT keep the aim clamp** |
| **`96`** | **►► THE JUDDER PLAN. Superseded by `99` on route, still correct on method. ◄◄** Four phases, cheapest first, **Phase 0 is free and can invalidate everything after it**. A decision table instead of a pre-committed fix. Gates written before the code |
| **`95`** | The wearer's second report, **scoped back at his own request** — *"just an example of the visual, let's not get caught up on that."* **The stick-vs-head asymmetry is the finding.** Adds D1/D2, and **O79: does the runtime reproject at all?** |
| **`94`** | **►► THE TEST FOR `93`. READ BEFORE `93`. ◄◄** What `93` over-claimed, **including a question of mine that could not eliminate anything and was used to kill a candidate.** Four tests, none depending on a description — **T1 the mirror (no build), T4 `GE_VR_POSE_LAG` (decisive).** `23` back to open and unranked |
