> # ######## 2026-08-31b — CODE WRITTEN, NOTHING BUILT, NOTHING RUN. `287`. ########
>
> **THIS SESSION MADE NO MEASUREMENT. It read source, found three errors in `286`, wrote two
> instruments and a run sheet, and stopped at the owner's instruction: "plan first, stop before
> building."** Binary in play is still `286`'s — **`2026-08-31 01:07`, 18,021,956 bytes.**
>
> **►►►► `286` §1's SITE LIST IS WRONG IN BOTH DIRECTIONS. `287` §1. ◄◄◄◄**
> **`explosion.c:1486` (SMOKE) is a fifth scissor site and `286` MISSED IT** — a build following
> `286` verbatim leaves smoke clipped and reads the surviving artifact as "the extension took."
> **`chr.c:186` IS NOT A SITE**: `ge_chr_dbg_vis_breakdown`, a read-only debug counter gated on
> `ge_chr_dbg_on()` that sets no scissor. **`propobj.c:14007` is a DIFFERENT CLASS — a CULL, not a
> clip**: a too-tight rect there REMOVES a prop, which makes it the first candidate mechanism the
> **BLACK-WALL** symptom has ever had (`279` §6, `280` §7.3, owed four sessions). It gets its own
> knob. **AND `chraction.c:10770` reads the rectangle DIRECTLY and is AI/SPAWN LOGIC — which is why
> the knob MUST NOT live in `bgGet2dBboxByRoomId`.** The tidy chokepoint would have silently
> changed what characters do.
> **THE ERROR'S SHAPE: `286` grepped for the ONE HELPER, not for the RECTANGLE. Fifth instance in
> five sessions of a grep standing in for a read** (`275` §1, `277` §6.2, `278` §7.2).
>
> **►►►► NO CODE IN THIS PORT HAS EVER ASKED THE DISPLAY WHAT IT IS. `287` §3. ◄◄◄◄**
> `285` §2 said no LOG records the panel. `[MEASURED]` it is worse: a grep of `getv\port` for
> `GetCurrentDisplayMode`/`GetDesktopDisplayMode`/`refresh_rate` returns **ZERO hits.** So
> **"the panel is 120 Hz" is `[REPORTED]`**, and `GETV_FPS=<panel Hz>` — the whole of the
> smoothness fix — has been set against a number the binary has never seen. **`GETV_PACEHIST` now
> prints SDL's own answer. IF IT SAYS 60, S1's "super smooth" needs re-reading.**
>
> **►► `285` §1.4 IS A RETRACTION CANDIDATE, FROM SOURCE. `287` §2.** The TURN **is** delta-scaled,
> unlike the walk — `bondview2.c:7366`, and **every** term of all four branches of
> `bondviewCurrentPlayerUpdateSpeedTheta` (`:4573-4630`). **And mouse and pad travel the SAME
> path** (`port_input.c` accumulates `ge_mouse_pend_x` into the stick), so `285` §2's mouse-vs-pad
> question needs no arm. **SOURCE READ, NOT A MEASUREMENT. Its falsifier is free and unrun.**
>
> **►► THE COST ARM NEEDS A THIRD RECIPE AND IT IS IN NO DOC. `287` §4.** `WORK_OVER=` needs a CAP
> (or there is no budget and no sleep) **and vsync OFF** (`port_render.c:1010` says so in its own
> source: the vblank block is inside `work`). **`VSYNC=0` + `FPS=120`.** At `VSYNC=1` it prints
> `slept=0` and declares itself void — **that is the prediction, and it is the check that it is
> `271`'s instrument.** **And the 90 Hz budget is not the 120 Hz budget: `1.722` ms was measured
> against `11.111`; at 120 Hz it is `8.333`, and neither term has ever been taken at 120 Hz.**
>
> **►►►► AND A TRAP THAT IS LIVE RIGHT NOW: `gfx_sdl2.c` IS GITIGNORED AND REGENERATED, EXACTLY
> LIKE `gfx_pc.c`, AND `00-STATE` §6 NAMED ONLY `gfx_pc.c`. `287` §5. ◄◄◄◄**
> `GETV_PACEHIST` lives in it. **`tools/fetch-thirdparty.sh verify` WILL FAIL until the patch is
> regenerated — that is correct — and a regen run BEFORE that DELETES the instrument**, which is
> `271` §7's `GETV_DLGRAB` exactly. **`regen` then `verify`, GIT BASH, MAIN PC, AFTER the arms.**
>
> **WHAT IS WRITTEN AND UNBUILT:** `GETV_ROOMSCISSOR` at six sites + per-site take counters ·
> `GETV_PROPCULLBOX` · `GETV_PACEHIST`. **All default OFF, all self-announcing.** Seven files,
> six tracked, one gitignored (§5 above).
>
> **FIRST RUN OF THE NEXT SESSION: `RUN-SHEET-287.md` §1 (build gate), then ARM 4A.**
> **`285` OUTRANKS THE HOLES. Do not start PART TWO before PART ONE has a log.**
>
> **STILL OWED AND STILL UNTOUCHED — FIVE SESSIONS NOW:** all of `277` §9 (the two hoist sites
> driven, the two intro-skip audio falsifiers, the `MoveBond` executions-per-second counter), plus
> `278` §6's `[INFERRED]` hoist-1 read · the same-spot two-resolution amount arm (`279` §5) · the
> black-wall dump (`280` §7.3) · `GETV_REALCLOCK`'s `CONTAMINATED` gate (`274` §7).

> # ######## 2026-08-30o — THE WIDESCREEN HOLES ARE THE PORT'S FILL, NOT THE CULLING. `278`. ########
>
> **NO BUILD. Every arm ran on `277`'s binary (`20:05:55`, 18,017,350 bytes), verified per block.**
>
> **THE SESSION WAS ASKED FOR THREE THINGS — drive the two hoist sites, run `277` §8's two audio
> falsifiers, design the `MoveBond` counter — AND DELIVERED NONE OF THEM.** The tank could not be
> entered in four arms, the audio arms were never reached, and the counter is designed but
> unwritten. **What it found instead was found because the owner reported it unprompted.**
>
> **►►►► `[MEASURED]` THE MISSING WALLS AT WIDESCREEN ARE NOT THE ROOM-VISIBILITY PASS. ◄◄◄◄**
> W1 vs W2, **200 stationary frames each, same spot and facing, the artifact on screen in the 16:9
> arm** — and the `GETV_CULLSTAT` census is **BYTE-IDENTICAL**: `curroom=9 drawn=2
> rooms(front=1 straddle=1 BEHIND=0) vtx(total=609 front=244 straddle=365)`. A widened view would
> admit MORE rooms. **A positive result, not a null.**
>
> **THE CAUSE IS A PORT KNOB THAT IS ON BY DEFAULT.** `configWidescreen = 1`
> (`port_support.c:203`), and `ge_effective_native_width()` (`gfx_pc.c:423`) redefines the
> content's native width as `gfx_native_height * (window width / window height)` — **the REAL
> window's aspect** — while the comment right above it says it deliberately does **not** write that
> back into the game's own scissor-tracked canvas. **`[MEASURED]` maximised at 2560x1369: effective
> native width `1795.2`, game canvas `1280x960` in every `SETSCISSOR` of every dump. 515 columns,
> 28.7%, are space the game never drew into.** That is the slab.
> **`[REPORTED]` `GETV_WIDESCREEN=0` restores pillarbox and removes MOST of it — NOT ALL. There is
> more than one contributor and this is NOT closed.**
>
> **►► IT IS `P3`, AND UNLIKE `268`'s ARTIFACT IT IS IN STEREO'S PATH.** Two notions of view width,
> one of which does not know about the window; `258` STAGE 6's off-centre per-eye frustum is a
> harder case of the same requirement. **NEXT: the per-room portal `SETSCISSOR` rects
> (`bg.c:622-677`), correlated to ONE artifact frame's hole.** No dump has yet been identified as
> carrying the artifact. **And two symptoms — a BLACK wall standing still, SEE-THROUGH slabs
> walking — are NOT established as one fault (`263` §1).**
>
> **THREE RETRACTIONS, ALL MINE.** The clip-box account I wrote was measured false in the very arm
> I wrote it for; *"the tank is entered by standing on top"* is false and **the owner's memory of
> side-entry was right** (detection is armed by being BLOCKED, `bondview2.c:2540-2571`) — the
> FOURTH read-stopped-too-early of this shape in four sessions; and I read `dlgrab_2700`, **a dump
> from a previous session at a different window size**, and reported it as this run's result.
>
> **AND A NEW `[INFERRED]` RETRACTION CANDIDATE FOR `275` §4's HOIST 1** — `g_TankTurretTurn` is
> rebuilt every frame as `g_GlobalTimerDelta * turnspeed`, so retail's divide CANCELLED, and the
> hoist may make the term 2/3 rather than fix it. **Source read only, unmeasured, and it
> contradicts a doc the owner signed off. Do not act on it.** `278` §6.
>
> **TRAPS PAID FOR:** the port layer has knobs a game-side grep cannot see (`gfx_pc.c` is
> gitignored — four wrong turns); **a `GETV_STAGE` boot silently inherits folder 1's SCREEN/RATIO
> options and silently runs AGENT**; `dlgrab_*` accumulates across sessions; the N64 `B` is `E`/`F`
> on the keyboard.

> # ######## 2026-08-30n — THE GATE IS MET, AND `RB-04` IS TWO FAULTS. `277`. ########
>
> **`276`'s SHAPE 3 WAS BUILT AND RUN FOR THE FIRST TIME. Seven arms, one binary
> (`20:05:55`, `GETV_SIMHZ` verified in the exe).** `276` §5 said the `239` gate was not met;
> **it is met now, for the term it was written about.**
>
> **►► `[MEASURED]` 90 Hz, term on: `fps 90` · `speedgraph 60/s` · `g_GlobalTimer 60/s` ·
> `simhz on delta 0.6667`** — with `props interpolated 0` and zero `simulation held to` in every
> arm, so `268`'s divider ran in none of them. **NO FALSIFIER FIRED.** Arm C proves the term is
> invisible when unset (no banner, `simhz OFF`, full `speedgraph 90/s`) and both refusals fire
> and name themselves (rule `17`).
>
> **►►►► AND THE SAME RUNS PROVED THE FIX IS HALF OF `RB-04`. ◄◄◄◄**
> `[MEASURED]` on the Dam route: **60 Hz `20.94 s` · 90 Hz `14.32 s` = `1.463`** — and the term
> changes it by **nothing** (`14.32` on vs `14.24` off). **Bond's walk is not delta-scaled**
> (`145` §2: an exponential approach advanced once per FRAME, `sp240` is a collision ratio, not a
> time), and **shape 3 changes the DELTA, not the TICK COUNT.** `145` §2 TRANSFERS to the native
> port — measured here for the first time.
>
> **SO AT 90 Hz THE WORLD IS NOW CORRECT AND BOND IS 1.46x FAST — a mismatch that did NOT exist
> with the term off, where both were ~1.5x and therefore consistent.** `[REPORTED]` the owner did
> not perceive it (*"everything was fine"*), and called 60 Hz *"everything seemed in sync"*.
> **A measured, unperceived mismatch, written down so it cannot resurface as "something feels
> off" in a headset three weeks from now.** The fix for the second half is a timestep inside
> `MoveBond` — 1,307 lines, **changes movement feel**, `118` §4 — and is **the owner's call**.
>
> **TWO RETRACTIONS, BOTH MINE.** `275` §7 / `RUN-SHEET-276` §0's prediction 4 had its two
> figures **inverted** (27.04 is the CORRECT one, 18.18 the fast one), and it was handed to the
> owner a third time this session. Worse: **the walking route could never have measured this fix
> at all** — I quoted `145`'s numbers without reading `145`'s mechanism. **The instrument that
> worked was the owner's own: watch the truck.**
>
> **`[REPORTED]` SKIPPING THE INTRO KILLS THE AUDIO** — the first normal-boot repro of `269`'s
> silence. Named candidate (`[INFERRED]`): `fileValidateSaves()`'s non-title call site is the
> **last line of the legal-screen init** (`front.c:1461`), which a skip never reaches.
> **Two free falsifiers first, no build — `277` §8.**
>
> **THE `RB-04` ROUTE IS NOW WRITTEN DOWN** (Dam, `GETV_STAGE=33`, start to the barrels) with a
> this-binary baseline. Three sessions had been reconstructing it from memory. `277` §7.

> # ######## 2026-08-30 — SHAPE 3 IS WRITTEN. THE CARRY HAD TO BE INTEGER. `276`. ########
>
> **`258` STAGE 4's FIX, on the shape `275` §5 chose. CODE WAS WRITTEN. NOTHING WAS BUILT AND
> NOTHING WAS RUN** — the bridge is a Linux VM with no mingw toolchain. **Every claim is
> `[MEASURED]` from source or from a harness that ran; NOTHING is measured from the game, and
> `239`'s gate is NOT met.**
>
> **►► THE TERM EXISTS: `GETV_SIMHZ`.** Five files, every edit inside `#ifdef GE_PORT_NATIVE`,
> **default OFF** — with the knob unset every line reduces to the retail arithmetic on every
> version, by construction. The seam is `lv.c:1151`'s `g_GlobalTimerDelta = (f32) g_ClockTimer`,
> split three ways: **integer `g_ClockTimer`** (122 frame-counted files, 24 iteration sites),
> **fractional `g_GlobalTimerDelta`** (0.667 every frame at 90 Hz — no `259` §4 residual), and a
> new **`g_GlobalTimerFieldDelta`** for `275` §4's two hoist sites.
>
> **`258` §3.2 IS HONOURED, NOT RETROFITTED:** `GETV_SIMHZ=query` reads `ge_pace_framerate`,
> `GETV_SIMHZ=<n>` supplies it. **AND IT REFUSES (rule `17`):** `CONTAMINATED` with
> `GETV_REALCLOCK` set, queried with the cap off, or pinned against a pacer that disagrees.
> **That pays `274` §7's owed `GETV_REALCLOCK` gate from the other side.**
>
> **►►►► THE HARNESS FAILED FIRST, AND THAT IS THE POINT OF WRITING ONE. `276` §3. ◄◄◄◄**
> `[MEASURED]` the first cut carried the leftover fraction in an `f32` and **lost 0.1 of a field
> EVERY SECOND at 72 and 144 Hz** — `60/72` and `60/144` are not representable — **while 90 and
> 120 Hz PASSED.** A harness that tested only the target rate would have shipped a 0.17% slow
> clock nobody could ever have explained. **The carry counts 60ths of a field in an INTEGER**,
> exact at every rate. `getv/tools/simhz_harness.c`, ALL PASS at 60/72/90/120/144/165 and an hour
> at 90.
>
> **`275` §9's ONE OPEN CLASS IS CLOSED, NOT OVERTURNED.** A parser walked all 24 `g_ClockTimer`
> loop bodies: **exactly 2 carry a delta reference** — `275` §4's two — and the only functions
> called from any of the 24 are `sqrtf` and two `matrixmath.c` helpers, in a file with **zero**
> delta references. **The count of two is exact.**
>
> **WHAT IS OWED NEXT: THE `239` GATE. `RUN-SHEET-276.md`, written BEFORE the build** (`15`).
> Four arms — 60 Hz control, 90 Hz ON, 90 Hz OFF as the regression control, and one arm whose
> whole purpose is to make the term REFUSE. **The falsifier that voids everything: `speedgraph`
> still reading `90/s` at 90 Hz means the term is not in the binary** (`133`, `268` §4).
> **AND THE TWO HOIST SITES ARE COVERED BY NO NUMBER IN THE SHEET** — the tank turret and a
> sliding grenade must be LOOKED at, at both rates.
>
> **►►►► AND A COMMIT TRAP, FOUND WHILE PREPARING THIS ONE — IT IS NOT ABOUT THE CLOCK. ◄◄◄◄**
> `[MEASURED]` **`COMMIT-NOW.cmd` COMMITS THREE REPOS AND `vendor\ge-decomp` IS NOT ONE OF
> THEM** (`vendor/` is gitignored by `goldeneye-native`, `.gitignore:42`). **`276`'s entire fix
> lives in the decomp**, so the script alone would commit the docs, the harness, and none of the
> change. **AND `git add -A` there would sweep 2,106 CRLF-dirty files in with it** — `HEAD` is LF
> throughout, and **the history already contains one such sweep: `7a4e7bfd`, subject "fix: three
> pointer-size errors the -w build never warned about", is 736 files and 601,764 insertions.**
> **AND A STALE `index.lock` SITS IN THE DECOMP RIGHT NOW, DATED `2026-08-29 04:13`** — zero
> bytes, no git running, and the bridge cannot unlink it. **Any `git add` there fails until it
> is deleted from the main PC** (STEP A0). **Commit the decomp BY EXPLICIT PATH LIST** — the block is `RUN-SHEET-276.md` STEP A2. The
> churn itself is the owner's call and was NOT actioned. `00-STATE` §6, `276` §6.
>
> **`275` AND ITS COMMIT MESSAGE ARE STILL UNTRACKED.** `COMMIT-MESSAGE-2026-08-30e.txt` and
> `docs/275-*.md` never got committed. **Three message files are written for today, one per
> repo** (rule `17`): `-2026-08-30m.txt`, `-m-decomp.txt`, `-m-native.txt`.

> # ######## 2026-08-30 — FORTY OF FORTY-FOUR ARE GUARDED. THE SHAPE IS CHOSEN. `275`. ########
>
> **`258` STAGE 4's MEDIUM half — the shape of the fractional delta. A SOURCE READ AND A DECISION.
> NO CODE, NO BUILD, NOTHING RUN.** All 44 divide sites and all 24 iteration sites read to their
> enclosing function's guard, not to a fixed window.
>
> `[MEASURED]` **`274` §5's COST INPUT IS WRONG: 40 GUARDED, 4 NOT — not 34/10.** There are
> **three guard spellings** in the tree and `274` grepped for one: `g_ClockTimer > 0` (34),
> `g_ClockTimer >= (0 + 1)` (6, carrying `// Keep the 0 + 1 for matching`), and
> `g_GlobalTimerDelta > 0.0f` (1). **Both gunfire accusations are dead** — `5994` and `6311` sit
> under the `>= (0 + 1)` form. The real four are `front.c:8941-8943` and `propobj.c:2393`.
> **A GREP FOR A GUARD IS NOT A READ FOR A GUARD.** `275` §1.
>
> **AND THE FOUR ARE NOT EQUAL.** `front.c:8941` is a **permanent-NaN trap** armed for exactly
> one frame per cast: `8936` zeroes the y numerator, `8941` divides by the delta, `8947` takes it
> into a file-scope accumulator on the `cast_camera_reset` frame, and `8963`'s `NaN * 0.0f` is
> `NaN`. Latent today because the delta is only zero while paused. **`275` §2.1.**
>
> **SHAPE 2 IS NOT LIKE `268` — IT IS `268`, THE SAME LINES** (`frametiming.c:88-94`). It has been
> built, run and rejected. **SHAPE 1 ARMS THE TRAP ABOVE WITH PROBABILITY 1/3 PER CAST.** `275` §3.
>
> **►► THE OWNER'S CALL: SHAPE 3.** Integer `g_ClockTimer` beside a genuinely fractional
> `g_GlobalTimerDelta`. **Its "second source of truth" objection is PRICED: exactly two sites in
> the tree put the delta INSIDE a `g_ClockTimer` loop — `bondview2.c:7330` (tank turret) and
> `propobj.c:5065` (projectile friction). Both are one-line hoists.** Shape 3 is the only shape
> that never produces a zero divisor outside pause, so **the four unguarded sites need no work at
> all**, and the only one that has no `259` §4 judder residual. `275` §4, §5.
>
> **THE NUMERATOR ALREADY HAS ITS VARIABLE: `ge_pace_framerate` (`gfx_sdl2.c:106`, deliberately
> non-static, already written by `GETV_FPS` and printed in the `pace:` banner).** `258` §3.2's
> "queried by default, pinnable" costs nothing extra. **`GETV_SIMHZ` is a proposed name and is in
> NO BINARY.** `275` §6.
>
> **WHAT IS OWED NEXT — `275` §7:** gated default-off, a banner naming the numerator AND its
> source, a `CONTAMINATED` refusal per rule `17`, the two hoists, and the `git diff` against
> `origin = n64decomp/007`. **THE FALSIFIER IS WRITTEN: `speedgraph` must read `60/s` at BOTH
> caps** (today: 60 and 90) **and the `RB-04` walk must stopwatch at 18.2 s, not 27.0.**
> **`239`'s gate is met for the DECISION. It is not met for the FIX, which does not exist.**

> # ######## 2026-08-30 — THE REAL CLOCK CANNOT RUN AT NINETY. THE TIMEBASE IS SETTLED. `274`. ########
>
> **`258` STAGE 4's HIGH half — `SESSION-START` §4's named `P1`/`P9` determinism question — CLOSED.
> THREE RUNS, NO BUILD, NO CODE.** `run_clock_A_60.log`, `run_clock_B_90synth.log`,
> `run_clock_C_90real.log`. `bondview2.c` was not touched.
>
> `[MEASURED]` **`GETV_REALCLOCK=1` UNDER A FRAME CAP RENDERS AT 60, NOT 90** — `fps 60.0` across
> 29 windows with `[getv] pace: 90 fps cap on, vsync=0` in the same log. `waitForNextFrame()`
> blocks a whole real field (16.552 ms) unless `GETV_FPS=0` (`frametiming.c:322-343`,
> `port_os.c:221`), and **uncapped is the one state `273` §7.3 says locks up on Cradle.**
> **Arm B held 90 fps on the same panel minutes earlier, so the display is exonerated** — that was
> not why arm B was in the sheet, and it is why it earned its place. `274` §2, §3.
>
> **`RB-04` NOW HAS A NUMBER.** `[MEASURED]` arm B, 90 Hz synthetic: **`speedgraph 90/s` = 1.500x**,
> against the owner's stopwatch **1.487** (`27.04s / 18.18s`). **A stopwatch, a `printf` written
> months earlier and an instrument read today agree to under one per cent.** `259` §3 is confirmed
> by RUN, not by reading.
>
> **THE DECISION: the SYNTHETIC counter, MADE RATE-AWARE.** Fields per frame = `60.0f/actualHz`
> computed from the rate the program is TOLD — **queried by default, pinnable** (`258` §3.2).
> **Determinism survives because a configured term does not float under load**, so `271`/`272`/`273`
> stay comparable. `ge_config.c:388`'s `framerate=30 -> GETV_TICKFIELDS=2` is the port's own
> precedent; 90 Hz is the same mechanism with a non-integer factor. **`GETV_REALCLOCK` is rejected
> for the present path and stays reachable as the knob it is** (rule `2`).
>
> **WHAT STAGE 4 STILL OWES, AND IT IS MEDIUM:** `[MEASURED]` **44 divide-by-`g_GlobalTimerDelta`
> sites, not `259`'s 8** — that count was `132`'s, recomp-era. **34 guarded by `g_ClockTimer > 0`,
> 10 NOT.** `g_ClockTimer` is also an **iteration count** (22 loops) and must stay integer. Three
> shapes are open and **one reintroduces `268`.** `274` §5.
>
> **ONE RETRACTION, MINE:** `260` §4 and `RUN-SHEET-260` predicted *"`speedgraph ~60/s` while `fps`
> reads 90."* The `~60/s` was right for the wrong reason. **NEW TRAP: a knob's RUN CONDITION is part
> of the knob** — `GETV_REALCLOCK` and `GETV_GPUTIME` both need `GETV_FPS=0`, both were cited for
> two sessions without it, and only one of them has a refusal gate. `274` §7.

> # ######## 2026-08-30 — THE GPU HAS A NUMBER. IT CAN ONLY BE TAKEN WITH THE CAP OFF. `273`. ########
>
> **`258` STAGE 3.1's GPU half, CLOSED. TWO BUILDS, NINE RUNS.** `run_273_gpu2_*` (v2 gate),
> `run_273_h1_*` / `run_273_h2_*` (the two axis runs), `run_273_v3_*` (the refusal gate).
>
> `[MEASURED]` **GPU draw = 0.832 ms on CRADLE and 0.334 ms on FACILITY**, 1280x960, RTX 5090,
> `GETV_FPS=0`, `GETV_SIMDIV=1`. **The first GPU figure this project has ever owned**, and it is
> **scene-sensitive, 2.5x.** With `272` §5.2's CPU term, **the pre-stereo frame on the hardest
> level in the game is 0.890 ms CPU + 0.832 ms GPU against 11.111 ms.** `273` §5.
>
> **`272` §7's REPAIR WAS BUILT AS DESIGNED AND ITS DIAGNOSIS WAS WRONG — AND THAT IS MINE.**
> `glEndQuery` moved ahead of the swap and the sleep and the figure **did not move at all**:
> 11.11 before, 11.11 after, both levels. `[MEASURED]` the CPU issues the two markers **0.22 ms
> apart** while the GPU reports **11.11 ms** between them — **the GPU waits INSIDE the query
> window while the pacer sleeps.** And the capped figure is **still 11.11 at 320x240, one
> sixteenth of the pixels.** `ge_gpu_timer.c:179-189` had named the mechanism in its own source.
> **`272` §7's cap-invariance gate asked for something unobtainable: the repair was a RUN
> CONDITION, not a bracket.** `273` §4.
>
> **WHAT DID WORK:** `[MEASURED]` **the present costs nothing** — `CPU present 0.00 ms, max 0.05`,
> sleep-subtracted and cross-validated against the budget line's `wait mean` in the same window.
> **And `GETV_GPUTIME` now REFUSES a capped run** — `slept=N/120` + `CONTAMINATED`, verdict
> withheld. Rule `17`, fourth instrument in this family. `273` §2.
>
> **THREE TRAPS, ALL NEW:** `272`'s four control arms **were not reproducible from their own logs**
> — they inherited `$env:GETV_SIMDIV`, and a clean env reset makes 90 Hz engage `268`'s divider
> (**the owner named it from the screen before the log was opened**) · **`GETV_SUPERSAMPLE` is
> INERT on Windows** — accepted, exported, read by nobody · **`GETV_FPS=0` locks up on Cradle,
> 3 of 3.** `273` §7.
>
> **NOT CLAIMED: there is still no CAPPED GPU figure**, so "0.832 ms holds when the pacer sleeps"
> is an assumption and every claim that stereo fits rests on it. `273` §6.

> # ######## 2026-08-30 — THE "GPU TIMELINE" IS THE FRAME CAP. THE GPU IS STILL UNMEASURED. `272`. ########
>
> **`258` STAGE 3.1's GPU half. FOUR RUNS, NO BUILD.** `run_272_gpu_90.log`,
> `run_272_gpu_90_nodraw.log`, `run_272_gpu_cradle_90.log`, `run_272_gpu_cradle_60.log`.
>
> `[MEASURED]` **`[getv][gputime]` prints 11.11 ms against an 11.111 ms period and 16.67
> against 16.667 — and the figure is BYTE-IDENTICAL in a ventilation shaft and on CRADLE,
> while the CPU work between those two scenes differs 4.4x.** Cap-sensitive and scene-blind:
> **it is measuring the frame cap.** Both its numbers are void, and so is every verdict string
> it has ever printed. `272` §2.
>
> **PROVED FROM SOURCE, NOT INFERRED:** `gfx_end_frame` carries the pacer's `sys_sleep`
> (`gfx_sdl2.c:111`), the query and the swap bracket both wrap it — and arm A's own log has
> `wait mean=10.762` beside `CPU in swap 10.76` in the same window. **THIRD instrument with
> this identical bracket error** (`267` §1, `271` §4, now `272` §3).
>
> **►► AND THE OWNER FOUND THE THING THAT MADE IT PROVABLE, FROM THE SCREEN:** *"Are we trying
> to track performance because you loaded me in one of the easiest levels? I'm inside of a
> vent."* **`GETV_STAGE=34` is `LEVELID_FACILITY`** — inherited from `271` without anyone
> asking what level it was. **Every performance number this project owned was taken in a vent.**
> The owner also supplied the replacement: `[REPORTED]` **Cradle is the hardest**, and it is the
> strongest possible form of the test — there is no scene left to escalate to. **Rule `16`.**
>
> **RETRACTED, BOTH MINE:** the gputime brackets, and **`271` §2's 0.259 ms as a BASELINE** —
> it describes Facility only. **The honest pre-stereo CPU figure is `[MEASURED]` 0.890 ms mean,
> 2.504 ms worst frame, Cradle at 90 Hz.** `272` §4.
>
> **WHAT SURVIVED AND IT MATTERS:** **`WORK_OVER=0` in every one of 83 windows — ~9,960 frames —
> on the hardest level in the game, pacer sleeping on every frame.** `P5`'s CPU term holds up
> where it counts. `272` §5.
>
> **NOT CLAIMED: still no GPU figure of any kind.** Stage 41 direct-boots (new). The repair is
> designed, gated and **deliberately not built** — `272` §7. **NEXT SESSION BUILDS IT.**
>
> **THE METHOD NOTE WORTH KEEPING (`272` §8): when a measurement will not move, find the axis
> it is pinned to and change THAT. The scene was cheaper than the cap and arrived first.**

> # ######## 2026-08-30 — THE WORK IS 0.259 ms AT BOTH CAPS. `P5`'s CPU TERM IS CLOSED. `271`. ########
>
> **`258` STAGE 2 BUILT AND STAGE 3.1 TAKEN. The pre-stereo baseline exists.**
> `[MEASURED]` **Fast3D replay + swap = 0.259 ms at 60 Hz AND at 90 Hz — identical to three
> decimal places — against periods of 16.667 and 11.111 ms. `WORK_OVER=0` over 7,440 frames,
> and the pacer SLEPT ON EVERY ONE OF THEM.** `run_271_work_60.log`, `run_271_work_90.log`.
>
> **The falsifier was written before the run and did not fire:** `work` moved 0.000 ms across
> the cap, `wait` moved 5.507 — the whole period change. **`266` §3's `OVER=` fired on 21-39%
> of frames and meant nothing; `WORK_OVER` is 0 and means something.**
>
> **NEW AND OFF BY DEFAULT — nothing: this build changes NO behaviour.** `GETV_BUDGET` now
> prints a second line with `WORK`/`wait`/`idle_mean`/`outside`. **`gfx_sdl2.c` was touched and
> is GITIGNORED — `tools/fetch-thirdparty.sh regen` in the same commit.** `port_render.c` is tracked.
>
> **ONE RETRACTION, MINE: `headroom_mean = budget - work`** — `267` §1's error one level down.
> The bracket does not hold the game tick or the display-list CONSTRUCTION, so it assumed
> everything outside it was free. **`idle_mean`, the pacer's MEASURED sleep, replaces it.** `271` §4.
>
> **AND `267`'s TWO ARMS WERE NEVER ONE EXPERIMENT** — the 60 arm ran vsync=1, the 90 arm ran
> vsync=0 **with the simulation held to 30 Hz** (they predate `268`), and neither pinned a stage.
> Found by diffing two logs already on disk. **`268`'s method note, twice in two sessions.**
>
> ### ►► **WHAT IS NOW THE WHOLE OF `P5`: THE GPU, AND IT IS UNMEASURED.** `GETV_GPUTIME=1`
> ### exists, is untouched, and was OFF in both arms. **Stereo doubles GPU work. That is a
> ### RUN, not a build — same binary.** `271` §6. ◄◄
>
> ### ►►►► **THE THIRDPARTY PATCH IS TWO SESSIONS STALE AND THE TOOL SAID OTHERWISE.**
> ### 415,083 bytes tracked, 433,892 needed. **`GETV_DLGRAB` IS NOT IN IT — a fresh clone has
> ### no F9.** `cmd_regen`'s unchecked `mv` printed "wrote ... bytes" after failing; that is
> ### fixed in `tools/fetch-thirdparty.sh`, along with a SECOND silent fallthrough: MSYS2's bash
> ### has no `git`, so every cache probe failed and it blamed the NETWORK. **NOW RESOLVED —
> ### regen from GIT BASH gives 433,892 bytes and `15/15 files match pristine + patch`.** `271` §7 ◄◄
>
> *(Chronology note: `269` and `270` were written without banners here. Their findings are in
> `00-STATE` §3 and in the numbered docs; this is the gap, not a deletion.)*

> # ######## 2026-08-30 — THE 90 Hz FAULT IS A DIVIDER THAT TURNS ITSELF ON. `268`. ########
>
> **`[MEASURED]` `GETV_SIMDIV=auto` engages ITSELF at 90 Hz — divider 3, simulation held to
> 30 Hz, props drawn INTERPOLATED — and is a no-op at 60. No `[simdiv]` banner exists in any
> 60 Hz log; `props interpolated 0` at 60 vs `85000` at 90.**
> **`GETV_SIMDIV=1` at 90 removes the artifacts. Owner: *"Yeah. That fixed it."***
>
> **The "black triangles" were never triangles, never geometry, and never the renderer** —
> rooms clipped away by a portal scissor computed against state that only advances on ticks.
> **Same single cause as the ghost truck you can walk through, the see-through textures, and
> the walls jumping. IT IS OUT OF STEREO'S PATH; `258` is unaffected.**
>
> **OWED, and it is the owner's call: the DEFAULT.** `auto` engaging silently above 60 Hz
> while marked `EXPERIMENTAL` is what cost this. `268` §7 lists the three options.
>
> **RE-RANKED under rule `16`:** the late gun sound is present at 60 as well, so the pacer is
> exonerated for it. `port_audio.c:520` `want.samples = 512` -> `256` is one line, untried.
>
> **NEW AND OFF BY DEFAULT:** `GETV_DLCENSUS` (per-frame opcode census) and **`GETV_DLGRAB` —
> F9 dumps one frame's ENTIRE display list plus a BMP of the SAME frame** (`268` §8).
> **`gfx_sdl2.c` and `gfx_opengl.c` were touched and are GITIGNORED — `tools/fetch-thirdparty.sh
> regen` in the same commit.** `port_render.c` and `port_support.c` are tracked.
>
> **FOUR RETRACTIONS, ALL MINE — `268` §4.** The worst: the F9 hook first went into
> `keyboard_on_key_down()`, which NOTHING in this port ever registers. A whole build-and-run
> cycle produced zero data.
>
> **METHOD NOTE. The owner reframed this and the reframe is what solved it** — *"we have the
> source, ask where it stops agreeing"* — and the answer was four grep-able banner lines in
> logs already sitting on disk. **THE TWO ARMS ALREADY EXISTED. NOBODY HAD DIFFED THEM.**

# HANDOVER

> # ►►►►►► **READ `00-STATE.md` FIRST. IT IS THE ENTRY POINT.** ◄◄◄◄◄◄
> **This file is 1,000+ lines and nine stacked banners; `00-START-HERE` is 4,300.
> `00-STATE` is ~170 lines and carries the current truth with pointers.**
> **Read the top banner below for what happened most recently. Read the rest only
> when `00-STATE` sends you.** Nothing here is deleted or condensed — the banner
> stack is the chronology, and the chronology is load-bearing: `262` was only
> solvable because `242`'s three faults could be seen to have been fixed later by
> `250`/`251`.

**Last updated: 2026-08-30h. Docs run to `271`. NEXT DOC = `272`.**

> # ►►►► **`267`: THE BUDGET INSTRUMENT MEASURED THE PACER. `266` §3 RETRACTED.** ◄◄◄◄
> `[MEASURED]` **the reported frame cost CHANGED WITH THE CAP — 16.40 ms at 60, 10.93 ms
> at 90. WORK DOES NOT GET CHEAPER BECAUSE YOU ASKED FOR MORE FRAMES.** The figure tracks
> the PERIOD. `[READ]` `gfx_end_frame` -> `swap_buffers_end` -> `sync_framerate_with_timer`
> -> **`sys_sleep()`**, and the vblank wait in `SwapWindow` — **both inside my bracket.**
> **`OVER=` fails on limiter jitter, not on missed work. It cannot answer `P5`.**
> ### ►► **WHAT IS REAL: THE GAME HOLDS 90 Hz IN GAMEPLAY** — mean 10.93 ms against an
> ### 11.111 ms period over 2,400 frames, `min=9.27`. **HEADROOM REMAINS UNKNOWN and the
> ### pre-stereo baseline is NOT taken.** Fix = subtract the sleep; `267` §5. ◄◄
> **`266` §4's bench validation is NOT retracted — but a scripted clock has no pacer in it.
> VALIDATE THE NEXT INSTRUMENT AGAINST A RUN AS WELL AS A BENCH.**
>
> ### ►► **TWO `[REPORTED]` ITEMS, BOTH NEW, BOTH OUTRANKING ANY DOCUMENT (`182` §5):**
> **1. A BLACK TRIANGLE ESCAPES ITS VIEWPORT IN SPLIT-SCREEN.** Owner screenshot, three
> player: a hard-edged dark triangle over Bond's viewport AND a matching band filling the
> BLANK fourth quadrant, which nothing should draw into. **That is a per-view SCISSOR
> question, and `lvlRender`'s per-view loop is the mechanism STEREO IS BUILT ON (`258`
> §1).** `GETV_BIGTRI` already prints `scissor=` per draw. **Not yet run. Not measured.**
> **2. SAVES REPORTED LOST.** Live EEPROM is in `%APPDATA%` (`260` §1) and `GETV_SAVEDIR`
> redirects it — a run with that set makes saves LOOK gone without losing them.
> **`local-only\save-backup.ps1` now snapshots and restores it.**

> # ►►►► **`266`: THE CLOCK WAS NEVER THE PROBLEM. `257` §6.1 IS RETRACTED.** ◄◄◄◄
> `[READ]` the `SDL_GetTicks()` timing `257` costed a session against is inside
> **`if (rendered < 5)`** — the BOOT-STALL BISECTOR. It fires five times and never again,
> and a 1 ms quantum is right for it. **The steady state already timed with
> `SDL_GetPerformanceCounter()` and `CLOCK_MONOTONIC`.** A read that stopped one
> conditional too early — the same shape as `259` and `261` §2.
> ### ►► **WHAT WAS ACTUALLY MISSING IS WORSE: NOTHING TIMED THE WHOLE CPU FRAME.**
> ### `ge_prof.t_frame` brackets `gfx_run` ALONE; `gfx_start_frame` and `gfx_end_frame`
> ### — the latter carrying the SWAP — are outside it. And `[prof]` prints one frame in
> ### sixty, so there was nothing for a budget claim to FAIL against. ◄◄
> **`GETV_BUDGET=<n>`**: whole-frame bracket, budget DERIVED from `ge_pace_framerate`
> (no literal `11.1` in the file), first five frames excluded, and **`OVER=` is the term
> that can fail** — that is the whole of `P5`. Uncapped prints `budget=none | OVER=n/a`
> rather than inventing a target.
> **VALIDATED AGAINST A SCRIPTED CLOCK BEFORE SHIPPING, AND THE TEST EARNED ITS KEEP:**
> the first cut printed **`(59 fps)` for a 60 fps cap** — a truncating divide, the SAME
> ONE that made `92` declare 90 Hz unavailable (`134`). The Hz is now carried, not
> re-derived.
> **OWED: one run at 60 and one at 90 = the pre-stereo baseline (`257` §6). Then `258`.**

> # ►►►► **`265`: THE COMBINER IS EXONERATED. `263` §4 IS DEAD, KILLED BY A
> # COUNTER-EXAMPLE IN ITS OWN LOG.** ◄◄◄◄
> `[MEASURED]` `run_ccprobe.log`, 50,341 frames, terminating record present, zero
> exceptions, `miss=0`. **768 draw lines, ONE combiner across all of them.**
> ### ►► **`CheadbrosnanboilerZ` DRAWS A BLACK TEXEL WITH A BLACK PRIM AND RENDERS
> ### CORRECTLY. `CorumovZ`'s 1917 — the reported fault — has `texel=8b0000` (RED),
> ### `prim=(255,255,255)`, `shade=(167,167,167)`: THE LEAST BLACK INPUTS IN THE LOG.** ◄◄
> **`264` §4's falsification condition was written before the run and it was MET.** No
> cause is named; the search space is not the combiner.
> **TWO FAULTS IN MY OWN PROBE, both in `265` §5:** the table SATURATED (`entries=64
> overflow=16` — absence from it is NOT evidence of absence, and no Trevelyan appears),
> and `near=`/`last_delta=` are misdocumented noise — **`264` §4 row 3 is RETRACTED**.
> **NEXT: key the same pointer bridge on the MODEL, not on `1x1`** (`GETV_CCMODEL`), and
> read what the ROM intends texnum 1917 to be. `265` §6.

> # ►►►► **`264`: THE COMBINER PROBE IS BUILT. NOTHING HAS BEEN RUN.** ◄◄◄◄
> **`GETV_CCPROBE=<n>` — three parts: the 1x1 bind's identity (`tex.c`), the decoded
> texel (`gfx_pc.c` upload), and the combiner + every colour input at draw time
> (`gfx_sp_tri1`), plus a census in the 60-frame block that prints WHETHER OR NOT the
> gate is on.**
> ### ►► **IT IS KEYED ON THE PIXEL POINTER, NOT ON A "CURRENT MODEL" GLOBAL.** The bind
> ### runs in `ge_convert_gdl()`; the draw runs frames later out of the list that convert
> ### built. A model global read at draw time names WHATEVER WAS CONVERTED LAST — that is
> ### `263` §1 committed to code. `tex->data` is the one object both passes hold. ◄◄
> **THE CONTROL IS MANDATORY:** `1608`/`CheadbrosnanZ` renders CORRECTLY and is in the
> table by construction. **A run that prints only the faulty draw is not evidence.**
> **THE CAP IS PER TABLE ENTRY** — `1514` is bound by all six weapons every frame and a
> global cap would be spent on the HUD before Ourumov's one shirt draw appeared.
> **FALSIFICATION, WRITTEN BEFORE THE RUN (`264` §4):** a sane non-black prim/shade on the
> 1x1 draws KILLS `263` §4. A line identical to the control's means I CANNOT ANSWER THIS.
> `entries>0` with `draws=0` means THE KEY IS WRONG, and `last_delta=` says by how much.
> **OWNER: `fetch-thirdparty.sh regen` before the native half — parts 2/3 are in the
> gitignored `gfx_pc.c`.**

> # ►►►► **`263`: THE 1x1 TEXTURES ARE RETAIL. FOUR THEORIES DEAD. THE SEARCH IS
> # THE COLOUR COMBINER.** ◄◄◄◄
> **THE SYMPTOM LIST WAS WRONG AND IT WAS MINE.** `261` §3 claimed a "total split
> across eleven characters with no exceptions" from TWO screenshots.
> **`[REPORTED]` owner: there are TWO faults — `CorumovZ`'s SHIRT and one
> Trevelyan's FACE. Everything else renders correctly.** His correction REMOVED
> six faults I had invented. `182`.
> **AND IT IMMEDIATELY PAID:** against a list of two, `texnum=1917` stands out —
> bound by `CorumovZ` ALONE in the whole run.
> ### ►► **BUT 1x1 IS CORRECT — `imagelist.u.csv` LISTS 1514/1604/1608/1917 AS
> ### GENUINELY 12-BYTE IMAGES, AND EVERY DEGENERATE BIND IS ONE OF THEM.**
> ### A 12-byte image is a header with no pixels: a flat-colour placeholder, as
> ### Rare shipped it. **`DEGENERATE_1x1` IS NOT A FAULT INDICATOR.** ◄◄
> **A 1x1 texture is HOW THE HARDWARE PAINTS A FLAT SURFACE — one texel modulated
> by prim/shade colour. THE TEXEL IS RIGHT; THE COLOUR IS COMING OUT BLACK.** One
> mechanism, both symptoms. `[INFERRED]`, `182`, not to be built on.
> **NEXT: probe the combiner mode + prim/env/shade colour on a 1x1 draw. It must
> be able to say I CANNOT ANSWER THIS — a sane non-black prim kills the theory.**
> **DEAD, MEASURED, DO NOT REOPEN:** missing assets (`0 MISSING`) · bind misses
> (`miss=0`) · degenerate 1x1 (retail) · CI/TLUT (`ci_decodes=0`).
> **REPRO (owner):** touch nothing from boot -> cast roll plays; skip ANY intro
> video -> straight to menu; idle at menu -> loops forever; never reaches a demo
> because the RAMROM functions are `STUB:`.

> # ►►►►►► **THE INTRO CAST CRASH IS FIXED. READ `262`.** ◄◄◄◄◄◄
> **It was `GETV_SLOTFREE = 0` in `%APPDATA%\Goldeneye-Native\Goldeneye-Native\
> goldeneye.cfg` disabling a fix that WORKS.** `[MEASURED]` gate off -> release
> no-ops 21x -> every anim slot leaks -> pool exhausts (`required=155 free=0
> maxcap=420`) -> NULL -> `front.c:8636` faults at `0x28`.
> **`GETV_SLOTFREE=1`: `anim=47 model=93` freed, ZERO exceptions, full cast twice
> round, and ALL SIX standing-gate criteria PASS** — including the dropped-weapon
> pickup that `242` turned it off for. **`250`/`251` had since fixed `242`'s three
> faults as independent pointer bugs, which is what made the re-test valid.**
> ### ►► **OWNER ACTION: DELETE THE `GETV_SLOTFREE = 0` LINE FROM THAT
> ### `%APPDATA%` CFG.** It is user data, outside this session's reach. ◄◄
> **`261` §2 IS RETRACTED** — I checked three config paths and not the live one
> (search path 4, per-user). **`242` was right all along.**
> **THE OWNER'S TWO CORRECTIONS DID THE WORK:** *"it crashed on a different
> character than normal"* (a leak, not a ceiling — no sizing theory produces
> that) and *"it was slow from the beginning"* (the audio fault is present at
> BOOT, so my duration-matched A/Bs were testing the wrong shape).
> **THE AUDIO SCARE WAS MY OWN `GETV_SLOTTRACE`** — the only run carrying it was
> the only run that sounded bad; audio init is byte-identical across all runs.
> **AND: NEVER READ A LOG AS FINAL WITHOUT ITS TERMINATING RECORD** (`EXCEPTION`
> or `game_exit requested`). I reported "no crash" off a file still being
> written.

> # ►►►► **`261`: THE ELEVENTH CAST CHARACTER IS JAWS. `GETV_SLOTFREE` HAS BEEN
> # ON SINCE `234` AND `242`'s PARK NEVER TOOK EFFECT.** ◄◄◄◄
> `[MEASURED]` Mayday is #10, **Jaws is #11 and gets `model=0` -> `0x28` fault at
> `front.c:8636`. `233` reproduces exactly.** Ten slots, no reuse.
> **`242` parked `GETV_SLOTFREE=0` in a `goldeneye.cfg` that does not exist beside
> the binary and does not contain the key; `model.c:252` defaults ON.** Four
> banners have carried "parked OFF" as fact. **Rule 10.**
> **GOOD: the three faults `242` blamed it for were fixed later by `250`/`251` as
> independent pointer bugs. BAD: it is ON and the crash still happens, so `234`'s
> release does not free the slot. NEXT READ: `ge_slot_release()` (`model.c:262`).**
> **TEXTURES: `miss=0`, `0 MISSING` everywhere -- NOT missing assets.
> `deg1x1` is FALSIFIED as the mechanism (`CheadbrosnanZ` has 7 and Bond's face is
> fine). The surviving discriminator is `rec=155`/`head=-1` self-contained bodies
> vs `rec=153` + separate head -- total across 11 characters.**
> **FIXED THIS SESSION: `F2` (the save now persists -- open since bring-up) and
> `F1` (fossil EEPROM + `front.c:2452` passing `f32*` where `coord2d*` is
> required). Owner confirms folders and saves work.**

> # ►►►►►► **READ `260` FIRST. THE "BLANK EEPROM" RUN WAS NEVER BLANK, NO BUILD
> # IS NEEDED FOR ANY QUEUED RUN, AND THE INTRO IS BEING PRIORITISED.** ◄◄◄◄◄◄
> `[MEASURED]` `run_blank.log` loads **512/512 bytes** from `%APPDATA%`, not from
> `build-windows`. **`256`'s exoneration of `eeprom.bin` is UNSOUND and `237` §1
> is un-retracted.** The save is a **first-write fossil**: Windows `rename()`
> refused every replace until the `MoveFileExA` fix, which **is in the 04:36
> binary** and has never been confirmed to write.
> **`257` §7's "BUILD ONCE" IS WRONG — every queued env var is already in the
> 04:36 exe.** `RUN-SHEET-260` put the folder fix behind a build and behind four
> runs that need the game to start. **The blocker was sequenced after the things
> it blocks.**
> **`GETV_SAVEDIR` at an empty folder = a genuinely blank EEPROM, first time.**
> **`GETV_CLOCKTRACE`'s `speedgraph N/s` tests `259` as a NUMBER — no stopwatch.**
> **`GETV_VSYNC=0` is MANDATORY at 90 Hz; today's run had `vsync=1`.**
**`169` NEXT ID = `U-26`.**

> # ►►►►►► 2026-08-29h — **`RB-04` IS NOT IN `MoveBond`. IT IS AN INTEGER, AND
> # THE PORT ALREADY WARNS ABOUT IT IN A `printf`.** ◄◄◄◄◄◄
>
> ## ►► **READ `259`. `258` §4 STAGE 1 STEP 4 IS DONE AND IT RETRACTED THE
> ## DIAGNOSIS THIS PROJECT HAS CARRIED FOR SEVERAL BANNERS.** ◄◄
>
> ### **THE RETRACTION.** `HANDOVER` has said *"Bond's walk is an exponential
> ### approach to a target, advanced once per FRAME, with no timestep in the
> ### loop."* **`[MEASURED]` FROM SOURCE: FALSE. THE WALK IS ALREADY
> ### DELTA-SCALED.**
> `bondview2.c:7845-7856`, both axes, `* g_GlobalTimerDelta`. The debug-fast path
> (`7867`) and the tank path (`7665`) too. **The speed ramps
> (`bondviewUpdateSpeedForwards` `4445`, `Sideways` `4411`) also step by the
> delta** — they are a THROTTLE clamped to ±1.0, not a position integrator, and
> the analog path (`6195`, `6214`) bypasses them entirely.
> **`MoveBond` is `6943-8341` = 1,399 lines, not 1,307.**
> **WHY THE SURVEY MISSED IT:** `132` §3 counted *"all 8 divides, not one an
> integrator."* **It was looking for DIVIDES. The walk multiplies and adds.**
>
> ## ►►►► **WHERE IT ACTUALLY LIVES: THE DELTA IS AN INTEGER** ◄◄◄◄
> `updateFrameCounters(s32)` → `ge_sim_pending_fields` **`s32`** →
> `speedgraphframes` **`s32`** → `g_ClockTimer` **`s32`** → `(f32)` cast LAST.
> **`g_GlobalTimerDelta` IS AN INTEGER COUNT OF 60 Hz FIELDS. IT CANNOT
> REPRESENT TWO-THIRDS OF A FIELD** — and 122 of 135 files under `src/game` step
> by it.
>
> ### ►► **AND UPSTREAM ALREADY DOCUMENTED THE 1.5x, IN A `printf` WE NEVER
> ### READ** (`frametiming.c:232-259`) ◄◄
> *"every rendered frame counts as exactly one video field and **the game's
> wall-clock speed IS the render rate**"* · *"WARNING: `GETV_FPS=%d` with the
> synthetic clock... **the game will run at %d/60 = %.2fx speed.** Set
> **`GETV_REALCLOCK=1`**... **A divider does NOT fix this.**"*
> **AT `GETV_FPS=90` THAT PRINTS `1.50x`. THE OWNER'S STOPWATCH SAID `1.487`
> (`27.04/18.18`). A stopwatch and a `printf` written months apart agree to under
> one per cent.**
> **The off-switch already exists and is already parsed** — `ge_config.c:836`,
> `gePortRealClockOn()` at `port_os.c:214`.
> **`[INFERRED]`, `182`, needs one run: `RB-02` WAS `GETV_REALCLOCK` and already
> measured CORRECT at 27.04s — making `RB-03`'s float delta a SECOND correction
> stacked on the first, which is what a 1.5x overshoot looks like.**
>
> ## ►► **WHAT IS STILL OPEN IS NOT SPEED — IT IS QUANTISATION** ◄◄
> The real clock fixes the RATE, not the integer. At 90 Hz it hands the sim
> `0,1,1,0,1,1...` — **correct on average, uneven per frame. JUDDER-SHAPED, NOT
> SPEED-SHAPED — and the owner reported exactly that shape in `96`: *"it just
> feels not ninety hertz"*, logged SEPARATELY from the judder.** `[INFERRED]`.
> **THE `P1` FIX IS ONE SITE:** make the field count FRACTIONAL — carry the
> remainder instead of truncating — at **`ge_sim_pending_fields`
> (`frametiming.c:88`)**, which is already an accumulator and already the site
> its own comment (`frametiming.c:61`) says *"throws the remainder away."*
> **NOT surgery inside `MoveBond`.**
> ### **THE COST INPUT, NOW THAT THE SYMBOLS ARE READ:** 216 refs, **8 divide by
> it**, and a fractional delta makes those divides **amplify**. `bondview2.c:7678`
> already carries a **`VERSION_EU`-only divide-by-zero guard** on it — evidence
> Rare hit this class on the one version whose delta was not `1.0`.
> **Those 8 sites are the review list and must be re-read in the NATIVE tree
> BEFORE the change.**
>
> ## ►► **STAGE 3 GAINS THE CHEAPEST TEST IN THE PROJECT, AND IT NEEDS NO
> ## BUILD:** run the fixed route with **`GETV_REALCLOCK=1` at `GETV_FPS=90`.**
> ## It confirms or kills the whole of `259` §3 in ONE LAUNCH. ◄◄
> **Gate unchanged (`239`): TWO rates, or it is not a setting.**
>
> ## **NOTHING RUN, NOTHING BUILT, NOTHING COMMITTED.** `259` is read from
> source. **The port's own warning says `UNVERIFIED ON THIS HARDWARE` — written
> on a 60 Hz panel, harness compute-bound at ~56 fps. It reasons; it does not
> measure. So does `259`.**
>
> **Everything below is the previous banner. History and fallback. DELETE NOTHING.**

---


> # ►►►►►► 2026-08-29g — **THE ENGINE ALREADY RENDERS N VIEWS PER FRAME, AND
> # LOCAL MULTIPLAYER IS INTACT AND LINKED. THE ROUTE IS `258`.** ◄◄◄◄◄◄
>
> ## ►► **READ `258`. IT RE-ORDERS `257` §7 RATHER THAN REPLACING IT.** ◄◄
>
> ### ►►►► **`lvlRender` (`lv.c:762`) ALREADY LOOPS OVER VIEWS** ◄◄◄◄
> `for (i = 0; i < getPlayerCount(); i++)` — each iteration sets its own
> viewport, FOV, aspect, and calls **`viSetupCurrentPlayerView` (`fr.c:696`), the
> seam, which is the ONE place the projection is built.**
> **SPLIT-SCREEN IS THE EXISTENCE PROOF: 2-4 views, 2-4 projections, ONE display
> list, ONE swap — shipped, retail, compiled in our tree.**
> - **It DISSOLVES the `gfx_run()` double-swap trap** (`gfx_pc.c:5817`) instead of
>   solving it — an eye loop at `lvlRender` never calls `gfx_run` twice.
> - **It ANSWERS `256` §2's 24 pre-combined projection loads** — re-running the
>   render body per eye produces all 60 correctly by construction. A
>   `gfx_sp_matrix` substitution reaches the 36 and **cannot** reach the 24.
> - **`255` §3's A vs B was a choice about where to double the work. There is a
>   THIRD site, it is the one the engine itself uses, and it was not on the list.**
> **`[INFERRED]` that it is cheaper — `182`, MAY NOT BE BUILT ON. `258` §4 stage 3
> is the counter-example search and it costs ONE LAUNCH AND NO CODE.**
>
> ### ►►►► **THE TRAP: DO NOT SET `getPlayerCount()` TO 2 FOR STEREO.** ◄◄◄◄
> `[MEASURED]` **173 refs across 35 files**, and they are GAME LOGIC, not render:
> `alloc_window_pieces.c:14` sizes the glass buffer `200 / getPlayerCount()`;
> **`bondinv.c` gates DUAL-WIELD on `== 1` at four sites**; `bondview2.c` at
> three. **It would also spawn and tick a second Bond.**
> **The eye loop nests INSIDE the per-player body. One player, one authoritative
> position, two views — not two players.** Rule 6, in advance.
>
> ### ►► **LOCAL MULTIPLAYER SURVIVED, AND THERE IS MORE THAN EXPECTED** ◄◄
> `[MEASURED]` from source and `objects.txt`: **`mpmenu.c` (1,774 lines) and the
> MP text banks are LINKED INTO `goldeneye.exe`** · split-screen 2/3/4-way
> viewport code compiled (`fr.c:770`) · **`_Static_assert(GE_PORT_MAX_PADS == 4)`
> (`port_os.c:1046`)** with a synthetic harness for ports 1-3 already written
> (`port_input.c:800`) · **and the port layer carries `ge_net.c`,
> `ge_net_enet.c`, `ge_net_udp.c`, `ge_discovery.c` and SIX `ge_bot*.c` files,
> all linked.**
> **`[ASSUMED]` — LINKED IS NOT RUN. None of it has been exercised in any logged
> session; the net and bot layers are upstream's and their state is unknown.**
> **THE REAL LIMITER IS NOT PLAYER COUNT — IT IS THE OUTPUT SURFACE.**
> Split-screen composes every player into ONE framebuffer with viewport
> rectangles, so "one in VR, three flat" asks one buffer to be a headset
> swapchain and a desktop window at once. **A `P3`/`P4` structural question.**
>
> ## ►► **THE OWNER'S TWO DECISIONS, AND ONE HAS A DEADLINE** ◄◄
> **1. Single player outranks multiplayer.** `P9` does not promote MP into the
> build order — **it costs nothing extra if `P6` is built, and only gets expensive
> if `P6` is skipped.**
> **2. "Limit the multiplayer to everyone of the same hz" — ACCEPTED, and it
> retires the `P1`/`P9` determinism worry.** But: **the sim step must be a value
> the program can be TOLD, not only one it computes. Runtime-queried by default,
> PINNABLE.** That is one parameter at the moment the timestep is written into
> `MoveBond` — **and a rewrite if it is added afterwards. STAGE 4.**
>
> ## ►►►► **THE NEW ORDERING CLAIM: THE POSE SPINE (`P6`) COMES BEFORE
> ## STEREO.** ◄◄◄◄
> The eye **translation** lives in the VIEW matrix, not the projection (`255` §1 —
> projection-only is frustum shift, **that is `B1` again**). **Build stereo first
> and it consumes a renderer-side pose; then `P6` arrives and the eye path is
> reworked — the exact "hack later" the owner's clause forbids.** In this order
> `P6` costs nothing extra and stereo consumes it. **`194` is the receipt: one
> missing term, four faults.**
>
> ## **THE ROUTE, `258` §4:** **0** commit · **1** `257` §7's free reads +
> **`RB-04` re-grep (a `P1` dependency)** · **2 THE FRAME BUDGET — the gate on
> everything after it** (`P5`; `SDL_GetTicks()` ms against 11.1 ms through a
> `printf` that costs more than it measures) · **3 the 60 Hz baseline + TWO FREE
> READS: run 2P split-screen, and the four-pad synthetic harness** — these answer
> the owner's local-MP question for no code · **4** the clock, pinnable, + `RB-04`,
> **validated at TWO rates (`239`)** · **5 the pose spine** · **6 stereo, the eye
> loop, desktop SBS gate, no headset** · **7 aim (`P8`) — may run beside 6** ·
> **8** hands/body as one system · **9** multiplayer, deferred.
> ## **COST OF THE RE-ORDER: ONE STAGE (5 before 6).** Everything else is `257`
> §7 re-sequenced plus two free reads.
>
> ## **NOTHING WAS BUILT, RUN OR COMMITTED THIS SESSION.** Three files: `258`,
> `00-START-HERE.md` (`P6`-`P9`), this banner.
>
> **Everything below is the previous banner. History and fallback. DELETE NOTHING.**

---


> # ►►►►►► 2026-08-29f — **THE OWNER ADDED FOUR MORE STANDING REQUIREMENTS.
> # THEY ARE `P6`–`P9`, AND `P9` COLLIDES WITH `P1`.** ◄◄◄◄◄◄
>
> ## ►► **`P6`–`P9` ARE NOW IN `00-START-HERE`, BESIDE `P1`–`P5`. READ THEM
> ## BEFORE PLANNING ANYTHING.** ◄◄
> **`P6`** the SIM owns the pose — head, two hands, body proxy — and the renderer
> only consumes it · **`P7`** two hands and a body are ONE articulated system, not
> three knobs · **`P8`** aim is independent of facing, camera and locomotion ·
> **`P9`** the sim is authoritative for ballistics and position, **because
> multiplayer will read it.**
> **A plan that does not satisfy `P1`–`P9` is not finished.**
>
> ### ►► **`P6` IS `194` PROMOTED FROM BUG TO FOUNDATION.** ◄◄
> *"The head rotation reaches only the EYE VIEW MATRIX... THE GAME CAMERA NEVER
> LEARNS ABOUT THE HEAD."* `194` hung four faults on it — bullet origin, drawn
> gun orientation, bullet direction, frame recovery. **They were never four bugs.
> They are one missing term, and it recurs in ANY design that leaves the pose in
> the render layer.** `P4` agrees on cost: pose-in-the-renderer is a per-frame
> correction paid forever.
>
> ### ►► **`P8` IS ALREADY HALF-MEASURED. DO NOT RE-LITIGATE IT.** ◄◄
> `[MEASURED]` `thr*camT` is **NOT** the bug (`223` §2.2, `gunfire.c:570-574`) ·
> `[MEASURED]` the error is **camera-dependent**, ±3° within a group and jumping
> between — **the signature of an aim ray still carrying a camera term** ·
> `[MEASURED]` pitch tracks to ~5°, **the fault is yaw-only.**
> **`66`: aim and stereo are independent. `P8` does not wait on Phase 1.**
>
> ## ►►►► **THE ONE NEW OPEN QUESTION, AND IT IS TIMED** ◄◄◄◄
> **`P1` makes the sim rate `60.0f / actualHz` — a float, per frame, from the
> runtime. Two peers on different headsets then tick at different rates with
> different timesteps. Correct for single player; DIVERGENCE BY CONSTRUCTION for
> a shared authoritative sim.** The usual answer is a fixed-rate deterministic
> sim decoupled from BOTH present rate and headset rate — **a third term `P1`
> does not name.**
> **`[ASSUMED]`, unmeasured, no transport/topology/authority model chosen or
> costed — `182`, may not be built on.** It is recorded now because **the cheapest
> moment to decide whether that numerator is a literal, a query or a fixed step
> is BEFORE the timestep goes into `MoveBond` (`RB-04`), not after.**
> **This is a decision for the owner. I am not making it.**
>
> ## **NOTHING WAS BUILT, RUN OR COMMITTED FOR THIS.** Two files edited:
> `00-START-HERE.md` (`P6`–`P9` inserted after `P5`) and this banner.
> **`257` §7 steps 0-6 are UNCHANGED and still the queue.**
>
> **Everything below is the previous banner. History and fallback. DELETE NOTHING.**

---


> # ►►►►►► 2026-08-29e — **NINETY IS THE TARGET, THE OWNER SET FOUR STANDING
> # REQUIREMENTS, AND `92` HAS BEEN DEAD SINCE `134`.** ◄◄◄◄◄◄
>
> ## ►► **READ `257` BEFORE PLANNING ANYTHING.** ◄◄
>
> ### **THE OWNER'S FOUR REQUIREMENTS ARE NOW STANDING CONSTRAINTS `P1`–`P5`**
> ### **IN `00-START-HERE`.** 90 Hz in the headset · adjustable FOV · adjustable
> ### resolution per headset · **"every choice for this foundation builds on this
> ### so that we don't have to hack later on."**
> **A plan that does not satisfy `P1`–`P5` is not finished.**
>
> ## ►►►► **HOW TO COMMIT. THIS, EVERY SESSION.** ◄◄◄◄
> # **DOUBLE-CLICK `COMMIT-NOW.cmd` IN `Z:\Desktop\GoldenEyeVR`.**
> It dry-runs, shows every staged file, asks y/N, **commits BOTH repos**, then
> offers `goldeneye-native` separately. **Nothing is pushed.**
>
> ### **THERE ARE EXACTLY TWO REPOS, AND THEY ARE NOT THE TWO THE OLD
> ### `00-START-HERE` NAMED** (`257` §7.1, all verified on disk):
> - **`Z:\Desktop\GoldenEyeVR`** — **IS** a repo, no remote.
>   **`repo\` inside it has NO `.git`; all docs commit here.**
> - **`Z:\Desktop\GoldenEye64Recomp`** — origin is cblock85's.
> - **`GoldenEyeVR\goldeneye-native\` is NOT one of them** — its own repo
>   (`SegfaultEvan`), **gitignored by the parent at `.gitignore:46`**, and
>   `commit-session.ps1` does not touch it. Separate, manual commit.
>
> ### ►► **THE PATH IS `Z:\Desktop`, NOT `C:\Users\<USER>\Desktop`** (owner,
> ### 2026-08-29). Both reach the same folders and older docs use the `C:` form.
> ### **`commit-session.ps1` HAD THE `C:` FORM HARDCODED** — it would have
> ### printed "NOT FOUND" and committed **nothing**. Both scripts now resolve
> ### from `$PSScriptRoot`. **Never hardcode a drive letter here again.**
>
> ### ►►►► **AND `Z:` IS A NAS — GIT REFUSES BOTH REPOS UNTIL TOLD OTHERWISE.**
> ### `fatal: detected dubious ownership` → **`git add FAILED`, nothing staged,
> ### nothing committed.** `Z:\Desktop` maps to `\\NAS\Double 6TB\User folder
> ### Data\Desktop`, and git's CVE-2022-24765 check refuses a UNC path owned by
> ### someone else. **ONE-TIME FIX, ALREADY-RUN SESSIONS CAN SKIP:**
> ```powershell
> git config --global --add safe.directory '%(prefix)///NAS/Double 6TB/User folder Data/Desktop/GoldenEyeVR'
> git config --global --add safe.directory '%(prefix)///NAS/Double 6TB/User folder Data/Desktop/GoldenEye64Recomp'
> ```
> **`commit-now.ps1` now pre-flights this and offers to add them** (it asks —
> it is a global config change). `goldeneye-native` needs its own when first
> committed. **`257` §7.1.3.** And note `257` §7.1.4: the script reported the
> failure correctly and **still ended on its reassuring closing paragraph**,
> with the two failures scrolled off above. `49`, third time in one session.
>
> ### ►► **`-MessageFile` DOES NOT EXIST. THE `29c` BANNER WAS WRONG AND WAS
> ### COPIED FORWARD TWICE.** `commit-session.ps1` takes **`-Message`**
> ### (mandatory) and `-DryRun`, nothing else. By hand:
> ```powershell
> cd Z:\Desktop\GoldenEyeVR
> .\commit-session.ps1 -Message (Get-Content .\COMMIT-MESSAGE-2026-08-29d.txt -Raw)
> ```
> **Do NOT right-click `commit-session.ps1` → Run** — the mandatory `-Message`
> opens an interactive prompt a multi-line body cannot be pasted into.
> **`[MEASURED]` `git status` TIMES OUT ON THE BRIDGE** (twice, 120 s cap) —
> `lib/ge` recursion. `--ignore-submodules=all`, or read it at the main PC.
>
> ## ►► **DO NEXT — `257` §7, STEPS 0-6 IN ORDER.** ◄◄
> **0. COMMIT** `247`-`257` — **`COMMIT-NOW.cmd`, main PC, not the bridge**;
> **`fetch-thirdparty.sh regen` before the native half** (`gfx_pc.c` is gitignored).
> **1. RUN 1 — `GETV_SAVE_DEBUG=1`, NO BUILD.** `F1` vs `F2` in one launch.
> **2. BUILD ONCE.** **3. RUN 2 (`GETV_ALIGNPTR=0`), RUN 3 (`GETV_RECTPROBE=1`),
> AND THE ROW-3 READ** — the read that decides A vs B on feasibility.
> **4. FREE DESK WORK, NO BUILD — `RB-04` re-grepped in the NATIVE tree.**
> **5. THE FRAME-BUDGET INSTRUMENT.** **6. THE BASELINE, BEFORE ANY STEREO CODE.**
>
> ## ►► **`92` IS SUPERSEDED BY `134` AND MUST NOT BE CITED.** ◄◄
> *"90 Hz is structurally unavailable... no amount of PC moves it"* — **false.**
> `134` ran the sim at ninety: **59.3 → 87.1 fps mean, 129 samples. It was a
> truncating divide and a hardcoded `60` in a file nobody had opened.**
> **`147`, WORN:** ***"I am so happy to say it's SO MUCH better. It's totally
> playable and enjoyable."*** — `interpUsed=0`, `distinctTargets=90`,
> **`LATE 0/91 (ZERO per cent)`**. **Pacing is BETTER at ninety real frames than
> at sixty plus an interpolator** (`109` measured 18% late).
> **THE INTERPOLATOR IS DELETED AND STAYS DELETED.** `131` §1: *"The sim itself
> ticks at 90. Every frame is real; nothing is interpolated."*
>
> ## **`257` §1 IS MY RETRACTION**, and it is `182`'s pattern for the **fifth**
> time (`160`, `163`, `171` §3, `180`, now this): I offered the owner
> "60 sim + interpolation" as **proven and cheap**, citing `92` as live and
> conflating `64`'s `rr_option: "Original"` (renderer stops interpolating, sim
> still 60, repeats manufactured) with Route B (sim produces 90 real frames).
> **Opposite operations, treated as the same one.**
> **THE OWNER CAUGHT IT FROM MEMORY, AS HE DID IN `180`.** `HANDOVER` §5 holds.
> **And his objection was on the record the whole time** — `96`: *"it just feels
> **not ninety hertz**"*, logged as a fault SEPARATE from the judder.
>
> ## ►► **THE ONE REAL CON IS `RB-04`, AND IT IS ONE FUNCTION** ◄◄
> Owner's stopwatch, fixed route: stock **29.48s** · RB-02 (clock) **27.04s —
> CORRECT** · RB-03 (float delta) **18.18s**. `27.04/18.18 = 1.487 = 90/60`.
> **Bond walks exactly 1.5x too fast.** Cause: **`bondview2.c` — Bond's walk is
> an exponential approach to a target, advanced once per FRAME, with no timestep
> in the loop.** All 44 `/ g_GlobalTimerDelta` sites were listed and **none is
> Bond's walk.** **The delta consumers are NOT the risk** — `132` §3 counted
> them: 216 refs, 8 guarded, **all 8 divides, not one an integrator.**
> **WHAT CHANGED:** it was parked because fixing it means a timestep inside
> `MoveBond` (1307 lines) through a patch layer, and `118` §4 says leave feel
> alone. **In source, `bondview2.c` is directly editable and the matching decomp
> is ground truth for the original curve** — "did we change the feel" becomes a
> diff, not an opinion.
> ### **`[ASSUMED]` — EVERY `RB-04` LINE NUMBER IS RECOMP-ERA AND UNVERIFIED
> ### AGAINST THE NATIVE TREE. `257` §7 step 4 exists for this. NO COST ESTIMATE
> ### MAY PRECEDE IT** (`168` §5; `157` withdrew a slice for want of eight symbols).
>
> ## ►► **THE CORRECTION THE OWNER ACCEPTED: RATE-AGNOSTIC, NOT NINETY** ◄◄
> Do not replace a hardcoded `60` with a hardcoded `90`. **Sim rate is
> `60.0f / actualHz`, per frame, from the runtime; the `MoveBond` timestep is
> rate-agnostic.** A 72 Hz Quest or 120 Hz Index must be a config line, not a
> second port. **It costs nothing extra — the timestep goes in either way; the
> only question is whether the numerator is a literal or a query.**
>
> ## **A vs B: COST FAVOURS B, FEASIBILITY IS STILL ROW 3** (`257` §6). `P4` —
> A doubles game-side render work **every frame forever**; B's costs (split
> `gfx_run`, gitignored file) are **one-time and structural**. **This does NOT
> overturn `256` §2.2**: neither carries an eye translation, and row 3 is the read.
> ## **AND THERE IS NO FRAME BUDGET** (`257` §6.1): `port_render.c:143` times
> three stages with **`SDL_GetTicks()`, millisecond resolution, against 11.1 ms**,
> through a per-frame `printf` **that costs more than it measures.**
> `gfx_sdl2.c:403` already has `SDL_GetPerformanceCounter()`. **Requirement 4 is
> unmeasurable until this is fixed.**
>
> ## **OPEN:** `F1` folder selection · `F2` the EEPROM is never written · the
> intro scanline wipe · **`RB-04` — the Phase 1 dependency** · the frame-budget
> instrument · wrong SFX (`GETV_AUDIO_TESTSFX`, built, **never run**) · latency
> ~51 ms · `SETUP.md` §3.5 owes `229` §9's two CSV traps · **STEREO, MEASURED,
> NOT STARTED.**
> ## **NOT CLAIMED:** no architecture recommendation · **no claim `134`'s numbers
> transfer — the NATIVE port has never been run above 60** · no claim the
> `MoveBond` fix is cheap · `[INFERRED]` only that `P2`'s tangent form fixes
> `222` §2's 30% aspect · **nothing in `257` §7 has been run.**
>
> **Everything below is the previous banner. History and fallback. DELETE NOTHING.**

---


> # ►►►►►► 2026-08-29d — **ONE BUILD, THEN THREE ENV-ONLY RUNS. TWO CLOSED
> # DOCUMENTS HAVE REOPENED. NO ARCHITECTURE CHOICE IS MADE.** ◄◄◄◄◄◄
>
> ## ►► **DO NEXT, IN THIS ORDER.** ◄◄
>
> ### **1. COMMIT.** `247`-`256`, the fixes and both handover docs are untracked.
> ### **At the main PC, NOT through the bridge** (`48`, `148` item 11).
> **`getv/port/fast3d/gfx_pc.c` IS GITIGNORED** (`233` §6.1). `tools/fetch-thirdparty.sh regen`
> is **part of the commit**, not an afterthought — it regenerates
> `getv/patches/thirdparty/0001-getv-port-layer.patch`, the tracked artifact.
> **Without it a fresh clone loses every probe in this session.**
>
> ### **2. RUN 1 — `GETV_SAVE_DEBUG=1`. NO BUILD NEEDED. DO IT FIRST.**
> ```powershell
> Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
> cd C:\Users\<USER>\Desktop\GoldenEyeVR\goldeneye-native\getv\build-windows
> $env:GETV_SAVE_DEBUG = "1"
> .\goldeneye.exe *> run_save.log 2>&1
> ```
> **Reads but no writes → `file2.c` runs and declines to write. Neither → it never
> runs.** This separates `F1` from `F2` in one launch. (`256` §3.1, §5.)
>
> ### **3. BUILD ONCE, THEN RUNS 2 AND 3.** `256` §5.
> ```powershell
> cd C:\Users\<USER>\Desktop\GoldenEyeVR\goldeneye-native
> & getv\build_windows.ps1 -Target all *> build.log 2>&1
> ```
> **Run 2 — `GETV_ALIGNPTR=0`, nothing else.** All four folders selectable →
> `253`'s widening is the cause and `254` shipped a regression. Still two → it is
> excluded, at the cost of one launch.
> **Run 3 — `GETV_RECTPROBE=1`, blank EEPROM, watch the gunbarrel through.**
> Read the `BLANK` lines only.
> **The binary is behaviourally identical to tonight's** — all three changes are
> instruments or default-on gates. **`48` is satisfied by the RUNS.**
>
> ## ►► **`256` §2 — THE STEREO MEASUREMENT. `255` §4's "A SINGLE IDENTIFIABLE
> ## LOAD PER FRAME" IS FALSE BY A FACTOR OF SIXTY.** ◄◄
> `[MEASURED]` **60 `PROJECTION LOAD`s per frame: 36 `PERSP` + 24 `OTHER`, zero
> `ORTHO`**, identical across six frames. The 36 are **byte-identical** (near 5.0,
> far 15,248) and their scissor sequence is **palindromic** — the BG portal/room
> recursion re-loading the same projection at every step. The 24 `OTHER` are that
> projection **with a view already multiplied in** — seven distinct `m32` values,
> every one predicted to under 0.001.
> **NEITHER CLASS CARRIES AN EYE TRANSLATION.** A per-eye substitution at
> `gfx_sp_matrix`'s `G_MTX_PROJECTION` branch delivers the asymmetric **frustum**
> to all 36 cheaply and unambiguously — **but not the SEPARATION, which lives in
> the view. Projections alone give two images differing in shear and not in
> viewpoint. That is `B1` again.**
> **NO RECOMMENDATION IS MADE.** B is viable but is **not a one-site change**; the
> 24 pre-combined loads need a decision of their own; **A's double-tick risk is
> still unmeasured.** The deciding read is `256` §5's **row 3 whole**.
>
> ## ►► **THE FIRST STEP-1 RUN COULD NOT HAVE ANSWERED ITS QUESTION** (`256` §1) ◄◄
> A hard cap of **40** and **no `ge_probe_after_ok()` gate** — which the
> `GETV_SKINTRACE` probe ten lines below it has, and seven others in the same file
> use. The budget was spent on **frames 0–61 of 5,461**, all boot and front end.
> **`49`, second instance: an instrument that cannot be pointed at the moment in
> question is not an instrument for that question.** It printed four elements and
> no context, so it would have printed the same thing on a working build.
>
> ## ►► **TWO CLOSED DOCUMENTS REOPEN** ◄◄
> - **`237` §1 IS RETRACTED.** `236` §3.1 pre-registered both branches and **the
>   second fired**: the folder fault survived a boot the log confirms was blank.
>   **`eeprom.bin` is exonerated.** `237` closed this on one run that removed the
>   symptom and read that as proof of the cause.
> - **`231` §4's FOURTH BRANCH FIRED.** 288,000 texrects reach the RDP, so the
>   plumbing branch is dead; **40 of 73 sampled dumps are entirely zero texels** —
>   a 440-byte one-row I8 scanline wipe with `prim` stepping a grey ramp. The
>   glyphs in the same run are healthy. **The intro strips are the one genuinely
>   broken member of `231` §3's grouping.**
> - **`[MEASURED]` across all 18 run logs: `[getv][save] loaded` fires in 16,
>   `flush` in ZERO. The EEPROM has never been written, on any build, in any
>   logged run.** `port_save.c:175`'s "file2.c rewrites it correctly on first run"
>   **is false in practice. Nothing self-heals and no progress can persist.**
>
> ## ►► **THE RULE THIS SESSION BOUGHT** (`256` §3.2) ◄◄
> **A KNOB IS NOT ONLY FOR A CHANGE YOU EXPECT TO REVERT. IT IS WHAT LETS A
> SUSPECT BE EXCLUDED IN ONE LAUNCH INSTEAD OF A REBUILD.** `254` shipped
> `ALIGN64_V2_PTR` **ungated**, on `253`'s argument that *"an off-switch for that
> is a switch nobody would ever flip"*. **Nine hours later it needs flipping.**
> Correctness arguments do not decide whether a change is testable.
> **And the owner's hedge was DATA:** *"The menu issue didnt start on this build"*
> put `front.c` back in the window that had been excluded on a timeline I had
> wrong. **`HANDOVER` §5 holds again.**
>
> ## **STILL TRUE FROM `255`, AND STILL THE TRAPS:** `gfx_pc.c` is gitignored ·
> **`gfx_run()` is not re-entrant** (`gfx_pc.c:5817` — `start_frame()` at the top,
> `swap_buffers_begin()` at the bottom; calling it twice per frame swaps twice) ·
> the seam is `viSetupCurrentPlayerView` (`fr.c:696`) · `guPerspectiveF`/`guLookAtF`
> are **row-vector**, GL/OpenXR **column-vector** · engine yaw is the **negative**
> of the right-handed convention · **`guPerspective` cannot express an off-centre
> frustum** — a headset frustum must REPLACE it.
> ## **THE PHASE 1 GATE STILL NEEDS NO HEADSET:** desktop side-by-side,
> `GETV_STEREO_OFFSET=500`, halves cross-correlated, **`PREDICTION:` in pixels
> written to the log BEFORE the screenshot.**
> ## **PHASE 1 IS NOT:** OpenXR · head tracking · hand aim · the vignette/HUD
> quad/mirror · `gevr_xr.c`.
>
> ## **OPEN:** **`F1`** the folder selection — `eeprom.bin` exonerated, `GETV_ALIGNPTR`
> is Run 2 · **`F2`** the EEPROM is never written · the intro scanline wipe —
> upstream vs binding, Run 3 decides · wrong SFX (`GETV_AUDIO_TESTSFX`, built,
> **never run**) · latency ~51 ms (`port_audio.c:521`) · `SETUP.md` §3.5 owes
> `229` §9's two CSV traps · the 121 registered pointer narrowings · `GETV_SLOTFREE`
> parked OFF · **STEREO, MEASURED, NOT STARTED.**
> ## **NOT CLAIMED:** no architecture recommendation · `[ASSUMED]` the `V·P` fit is
> Z-only — four elements cannot exclude X/Y · no claim `ALIGN64_V2_PTR` causes the
> folder fault · `[INFERRED]` only that `F1` and `F2` share a cause · the 40 blank
> rects are a **SAMPLE** · **nothing in `256` §5 has been run.**
>
> **Everything below is the previous banner. History and fallback. DELETE NOTHING.**

---


> # ►►►►►► 2026-08-29c — **PHASE A IS CLOSED. PHASE 1 (STEREO) IS SCOPED AND
> # NOT STARTED. THE ONLY VR REFERENCE TREE IS NOT WIRED.** ◄◄◄◄◄◄
>
> ## ►► **DO NEXT, IN THIS ORDER.** ◄◄
>
> ### **1. COMMIT.** `247`-`255`, three fixes and both handover docs are
> ### untracked. **At the main PC, NOT through the bridge** (`48`, `148` item 11).
> ```powershell
> cd C:\Users\<USER>\Desktop\GoldenEyeVR
> .\commit-session.ps1 -MessageFile .\COMMIT-MESSAGE-2026-08-29c.txt
> ```
> **Phase 1 must not be layered on an uncommitted tree.** If a stereo experiment
> has to be backed out, `G-250` and `G-251` must already be a commit of their own
> or they go out with it. (`255` §6.)
>
> ### **2. ONE LAUNCH, NO CODE — `GETV_MTXTRACE`.** `255` §4 step 1.
> ```powershell
> Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
> cd C:\Users\<USER>\Desktop\GoldenEyeVR\goldeneye-native\getv\build-windows
> $env:GETV_MTXTRACE = "1"
> .\goldeneye.exe *> run_mtx.log 2>&1
> ```
> Load a level, look around, quit. **This decides architecture A vs B on a
> measurement instead of on which reference tree looks more finished.**
>
> ## ►► **`255` §1 — THE CORRECTION THAT MATTERS: `007-VR`'s STEREO IS NOT
> ## MERELY UNRUN, IT IS UNREACHABLE.** ◄◄
> Grepping that tree for its nine shim symbols **outside `vr/`** returns **two**
> call sites in the whole repository: `joy.c:436` and `fr.c:719`.
> - **`gevr_shim_init` is never called**, so `g_vr.active` is never set, so the
>   one live call returns `0` every frame and writes nothing.
> - **There is no eye loop.** Nothing calls `begin_eye`. The DL is built once.
> - **`gevr_shim_eye_view_n64` has NO call site at all** — and the eye
>   **translation** lives in the view matrix. Projection-only is frustum shift,
>   not separation. **That is `B1` — one image in both eyes — reachable from a
>   grep instead of from RenderDoc.**
> **This corrects my own `254` §3.1.** `58`'s lesson, third repository: **read
> the call sites before believing a reference tree works.**
>
> ### What `007-VR` IS worth — a day saved, not a line copied
> **The seam:** `viSetupCurrentPlayerView` (**our `fr.c:696`**, already carrying a
> `GE_PORT_NATIVE` block). **The convention:** `guPerspectiveF`/`guLookAtF` are
> **row-vector** (`v*M`), GL/OpenXR are **column-vector** (`M*v`) — transpose
> explicitly or `guMtxF2L` renders a scrambled frustum. **The sign:**
> `bondview2.c` rotates about Y by `(360 - vv_theta)`, so engine yaw is the
> **negative** of the right-handed convention; **pitch it refuses to assert** and
> so should we. **And `guPerspective` cannot express an off-centre frustum** — a
> headset frustum must REPLACE it, leaving `g_viPerspNorm` alone.
>
> ## ►► **TWO TRAPS, READ FROM SOURCE, BEFORE ANY STEREO CODE** ◄◄
> - **`getv/port/fast3d/gfx_pc.c` IS GITIGNORED** (`233` §6.1). Anything written
>   there reaches the repo only via `tools/fetch-thirdparty.sh regen`, **in the
>   same commit.** A fresh clone loses it otherwise.
> - **`gfx_run()` is not re-entrant.** `gfx_pc.c:5817` calls
>   `gfx_wapi->start_frame()` at the top and **`swap_buffers_begin()` at the
>   bottom.** Calling it twice per frame swaps twice.
>
> ## ►► **THE PHASE 1 GATE NEEDS NO HEADSET** (`255` §4) ◄◄
> Desktop side-by-side window, `GETV_STEREO_OFFSET=500`, halves split at the seam
> and cross-correlated, with a **`PREDICTION:` line in pixels written to the log
> BEFORE the screenshot is taken** (`70`'s shape, `65`'s harness).
> **This drops OpenXR, session lifecycle and the compositor out of the question
> being asked** — four failure sources the recomp spent days untangling from this
> one. 500 units is deliberately absurd; the real ~6 cm is tuned **after** the
> mechanism is proven (`239`: a knob validated at one value is not a setting).
>
> ## **PHASE 1 IS NOT:** OpenXR · head tracking · hand aim (`66`: aim and stereo
> are **independent**) · the vignette/HUD quad/mirror · `gevr_xr.c`.
>
> ## **CLOSED THIS SESSION:** the inventory crash and slow pickup
> (`GETV_CUFFIDX`, `G-250`) · the explosion crash (`GETV_RWSTRIDE`, `G-251`) ·
> the ammo re-pickup (fell out of `G-250`) · the loot box — **never established
> as a bug** (`252` §6) · the menu text, the folder screen, the purple explosion.
> ## **OPEN:** wrong SFX (`GETV_AUDIO_TESTSFX`, built, **never run**) · latency
> ~51 ms (`port_audio.c:521`, `want.samples 512 -> 256`) · `SETUP.md` §3.5 owes
> `229` §9's two CSV traps · the 121 registered pointer narrowings — **correct
> only because the heap is one contiguous region**, and the cost input for `247`
> Phase D · `GETV_SLOTFREE` parked OFF · **STEREO, SCOPED, NOT STARTED.**
>
> **Everything below is the previous banner. History and fallback. DELETE NOTHING.**

---


> # ►►►►►► 2026-08-29 — **PHASE 0's SYMPTOM LIST IS ALMOST EMPTY, AND THE REAL
> # FAULT CLASS IS NAMED.** ◄◄◄◄◄◄
>
> ## ►► **DO NEXT: `G-251` — BUILD, THEN THE STANDING GATE.** `251` §5. ◄◄
> ```powershell
> Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
> cd C:\Users\<USER>\Desktop\GoldenEyeVR\goldeneye-native
> & getv\build_windows.ps1 -Target all *> build.log 2>&1
> cd getv\build-windows
> $env:GETV_STAGE = "9"
> .\goldeneye.exe *> run_rw.log 2>&1
> ```
> **1** pick up a dropped weapon (still instant?) · **2 TAKE A LOOT BOX AND READ
> WHAT IT GIVES YOU — reported twice, never once measured** · **3** cycle the
> inventory twice · **4** shoot the console and let it explode — **the step under
> test** · **5** take damage and keep playing.
> **`GETV_RWSTRIDE=0` is the A/B. `GETV_SLOTFREE` stays `0` in `goldeneye.cfg`.**
>
> ## **THE STANDING GATE FOR ANY SHARED-LIFECYCLE CHANGE** (`242` §5, and it
> exists because `G-234` exercised ONE of eighteen call sites and passed):
> **weapon, ammo, cycle everything twice, a second level, the attract loop —
> WRITTEN DOWN BEFORE THE RUN, not invented after the failure.**
>
> ## ►► **THE FAULT CLASS: THE DECOMP ENCODES POINTER SIZE IN ARITHMETIC.** ◄◄
> **And `build_windows.ps1:160` is `-w` — every diagnostic off.** Four flags
> re-enabled found **56 pointer/int narrowings across half the game files**
> (`248` §4).
> - **`bondviewSelectCuff`: `switchindex << 2` over 8-byte pointers.** FIXED
>   (`GETV_CUFFIDX`), `G-250` **PASSED** — *"pick up the weapon INSTANTLY and
>   rotate through my inventory"*, **and it took the slow-pickup symptom with it.**
> - **`->datas[i]` at four sites: an 8-byte stride over a 4-byte-word pool.** The
>   correction has been in `modelGetNodeRwData` since the bring-up and was never
>   applied to the four direct indexers. FIXED (`GETV_RWSTRIDE`), **UNTESTED.**
> - **`ALIGN64_V2` casts to `(u32)`, and `front.c:8517` feeds it a POINTER.**
>   **LOCATED, NOT FIXED. It is the obvious next one.**
> **THE SWEEP IS THE PRIZE, NOT THE THREE FIXES**: every `<< 2`, `* 4`, `+= 4`
> and `(u32)` applied to a pointer or a pointer-array base. `168` §5.
>
> ## **`fault addr: ffffffffffffffff` MEANS NON-CANONICAL, NOT `-1`** (`249`).
> **#GP has no faulting address; Windows fills the field with ones.** `243` and
> `248` both misread it. **`0xAAAAAAAA_00007ff6` is two halves of two GOOD
> pointers.**
>
> ## **THE PORT NOW EMITS A LINKER MAP** (`243` §3). **Anchor the ASLR delta on
> `&g_mempPools` from `[getv] MEMP TABLE` against THAT BUILD'S map — re-read it
> every build, it moved `0x1000` and silently shifted every answer — then VERIFY
> THE PC LANDS ON AN INSTRUCTION BOUNDARY, and resolve EVERY STACK FRAME.**
>
> ## **FOUR MISTAKES OF MINE THIS SESSION, ALL RETRACTED IN PLACE:**
> `239` — promoted `GETV_RGBA16BE` to the config on a measurement taken against
> ONE explosion flare · `239` — sent the owner to `GETV_AUDIO_DEBUG`, which
> measures the MIXER when the fault is an INDEX · `240` — blamed `GETV_GIVE` on a
> gate that could not tell a keycard from a rifle · `241` — wrote into
> `Model.obj` inside the very function whose job is to clear it, **in a fix whose
> own argument was that the alias had been lost.**
> **`244`: `GETV_RGBA16BE` does not fix an endian-wrong reader — our read was
> always correct. It UNDOES a corruption already in the data, and the fault is
> per-asset PROVENANCE.**
>
> ## **CLOSED SINCE `229`:** the menu text — **NEVER A BUG** (`236`) · the folder
> screen — a stale `eeprom.bin` (`237`) · the purple explosion (`237`/`244`) ·
> the intro cast crash — **diagnosed** (`233`), **fix parked** (`242`) · the
> inventory crash and the slow pickup (`250`).
> ## **OPEN:** the loot box giving wrong items · ammo re-pickup · wrong SFX
> (`GETV_AUDIO_TESTSFX`, built, never run) · latency ~51 ms · **STEREO, NOT
> STARTED — and it is the reason `227` chose this road.**
>
> ## **FOUR OTHER PORTS ARE ON DISK** (`245`-`247`). `clone-prior-art.ps1`.
> **`007-VR` reaches `g_CurrentPlayer->vv_theta` — `194`'s root cause, confirmed
> here at `bondview.h:558`, `f32`, 27 references.** **DO NOT SWITCH BASES: it has
> never been run.** **Phase C of `247` is where the VR term gets built.**
>
> **Everything below is the pre-`230` plan. History and fallback. DELETE NOTHING.**

---

> # ►►►►►► 2026-08-27 LATE — **PHASE 0 IS PASSED. THE NATIVE PORT BOOTS AND PLAYS.** ◄◄◄◄◄◄
>
> ## `[REPORTED]` ***"It works"*** — **`goldeneye.exe`, 17.2 MB, from the owner's ROM.**
> **The gate `227` set is MET. `228`'s Phase 1 (stereo) is unblocked.**
> **READ `229` §11 FOR THE BUILD, THEN `229` §20 FOR THE PLAN.**
>
> ## ►► **ITEM 0: COMMIT. THE BUILD EXISTS ONLY AS UNTRACKED WORKING-TREE STATE.** ◄◄
> **40+ documents overdue and this session changed more real files than any before
> it** — the CRLF fix, 550 extracted `.bin`, a 20.9 MB and a 6.9 MB generated
> source, `UsetuplenZ.c`, `build_windows.ps1`, `port_audio.c`. **Full table in
> `229` §20.** `commit-session.ps1`, at the main PC, **not through the bridge**.
>
> ## **`[MEASURED]` EVERY PHASE 0 BLOCKER WAS BUILD-PIPELINE, NOT CODE.**
> Git symlinks checked out as 36-byte text · asset uniquify never run ·
> **CRLF in `filelist.u.csv` making the ROM extraction skip 812 of 812 rows AND
> EXIT 0** · one double-applied symbol prefix. **Not one line of game logic was
> wrong.** `229` §9 is the one to read: **a control was already on disk** —
> `imagelist.csv` is CRLF too and its loop does not test a flag, so images
> extracted while obseg did not.
>
> ## **THE FOUR OPEN SYMPTOMS, IN THE ORDER THAT UNBLOCKS THEM (`229` §20):**
> **1. THE MENU TEXT IS NOT DRAWN — AND IT BLOCKS EVERYTHING ELSE.**
> `[MEASURED]` the assets are innocent: every front-end text bank loads
> `NATIVE (early-out)`, both fonts convert `0/94` bad glyphs, and there is **not one
> texture fault in 100,270 log lines.** **The strings and glyphs are PRESENT and are
> not being DRAWN — it is a render question, and the next step is a READ.**
> **2. WRONG SFX** (*"back out ... makes a machine gun sound"*) — an index landing on
> the wrong record. **`GETV_AUDIO_TESTSFX=<id>` is built, cheap, and NEVER RUN.**
> **3. LATENCY ~51 ms**, halved from ~90 by `229` §13. Two terms left; take SDL's
> `want.samples 512 -> 256` first. **`ovf` is the failure signal.**
> **4. PURPLE EXPLOSION** — `[MEASURED]` **NOT a missing texture.** Needs item 1.
>
> ## ►► **THE PORT HAD NO STDOUT ON WINDOWS UNTIL THIS SESSION.** ◄◄
> `[MEASURED]` PE **subsystem 2 (GUI)** — no console, no stdout handle, so
> `*> run.log` produced a **ZERO-BYTE FILE** and every `printf` was discarded.
> `-mwindows` arrived from `pkg-config --libs sdl2`, which `build_windows.ps1`
> already filtered two OTHER flags out of. **Now stripped; `-GuiSubsystem` restores
> it.** **Treat every runtime claim about the native port made before `229` §13 as
> `[ASSUMED]`.**
>
> ## ►► **NEW RULE, AND IT COST TWO RETRACTIONS: `48` APPLIES TO ENV VARS.** ◄◄
> **AN ENVIRONMENT VARIABLE THAT RE-ROUTES THE BOOT PATH IS A BEHAVIOUR CHANGE.**
> **`229` §16 blamed the audio mixer on a `pkAll=0` that `GETV_MENU=11` had caused**
> — a shortcut introduced one section earlier. **§17 retracted it; §19 `[MEASURED]`
> `pkAll=32768` once the front end was walked normally.** **Never judge audio, or
> anything else, through `GETV_MENU`.**
> **PowerShell `$env:` PERSISTS for the life of the window** — three variables
> accumulated silently. **`Remove-Item Env:GETV_*` between runs.**
>
> ## **AND THE OWNER WAS RIGHT BOTH TIMES HE CONTRADICTED ME THIS SESSION:**
> *"That doesnt happen on this build"* (**the X-close crash is recomp-era; X is the
> CLEAN exit here and `taskkill` would LOSE the 64 KB stdout buffer**) and
> *"There was a run before this it all worked"* (**which killed §16**).
> **§5's rule held without exception.**
>
> **Everything below is the recomp-era plan and the pre-Phase-0 native plan.
> History and fallback. DELETE NOTHING.**

---

> # ►►►►►► 2026-08-27 — DIRECTION CHANGE. READ `227` FIRST. ◄◄◄◄◄◄
> ## THE PRIMARY DIRECTION IS NOW A NATIVE SOURCE PORT, NOT THE RECOMP+PATCHES BUILD.
> **Owner's decision (`227`): build GoldenEye VR FROM SOURCE — the native GoldenEye PC
> port (`SegfaultEvan/goldeneye-native`, from the 2026 100% decomp) + a VR layer ported
> from Perfect Dark VR (same engine, on disk), ROM for assets only. NO recompiler, NO TLB.**
>
> **WHY:** the cblock85 recomp reconstructs the base game from the ROM and RECOMPILES it; all
> VR work to date is `RECOMP_PATCH` hacks on that binary, not on the source. The TLB gate
> (`225` §6/§11) is a RECOMPILER limitation that DOES NOT EXIST in a native port.
>
> **WHAT CARRIES:** the 226 docs of `[MEASURED]` design knowledge (aim/`194`/`226`, scale,
> seam, frames) — the spec for the native VR layer. **WHAT DOES NOT:** the `patches/*.c`.
> **DELETE NOTHING:** the recomp build stays as a working PCVR reference/fallback.
>
> **NEXT — READ `229`. Phase 0: compiles fully AND now links-ready.** `[MEASURED]`
> goldeneye-native compiles game 165/165, assets, audio, port layer, port c++ all 100%.
> The link hit multiple-definition errors on per-stage setup data; ROOT CAUSE was the
> asset symbol-uniquify pass never having been run. **This session: PR/gbi.h include fixed,
> tvOS main dropped from the link, AND all 67 setup/stan TUs uniquified (verified).**
> **NEXT ACTION: owner just RE-RUNS the build** (`& getvuild_windows.ps1 -Target all *> build.log 2>&1`);
> assistant reads `build.log` — expect a link to goldeneye.exe. Full status + the local
> files to request at session start: `229` §4, §3 and §6.
>
> **Everything below this banner is the recomp-era plan. It is history/fallback, not the
> primary path — kept per DELETE NOTHING.**

---


## §0 — READ THIS FIRST, IN THIS ORDER

1. **`00-START-HERE.md`** — the standing rules.
2. **`182`** — evidence tiers. **MANDATORY. An `[INFERRED]` claim may not be built
   on, and it requires a stated counter-example search.**
3. **`48`** — one behaviour change per run; one source of truth; **measure, do not
   reason**; an instrument must be able to say **I CANNOT ANSWER THIS**.
4. **`168` §5** — grep `externs.h`/`structs.h` for every symbol BEFORE costing
   anything. **`157` withdrew a whole slice for want of eight symbols.**
5. **`136`** — a new `RECOMP_PATCH`-reachable symbol means **BUILD TWICE**.
6. **`224`** — **the strategic fork the owner has chosen.** Start here for
   direction.

### THE THREE OWNER POLICIES THAT ARE NOT NEGOTIABLE

> **FIX IT IN THE SOURCE — AND WE MAY CHANGE ANYTHING, PROVIDED THE GAME STAYS
> TRUE TO ITS SPIRIT.** — **ADDED 2026-08-29. Owner:** *"From now on, any change I
> want to be made from the source so that we don't hack and everything is
> wonderful. We can change anything as long as the game remains true to its
> spirit."*

**This OUTRANKS the instinct to preserve retail behaviour for its own sake.** It
is neither preservation purism nor a licence to redesign. **The line is between a
HARDWARE BUDGET and a DESIGN DECISION — and in the source both are just
constants**, so the test is asked deliberately, every time:

> ## **Would a 1997 player notice this as the game behaving DIFFERENTLY — or only
> ## as the absence of a limit the CONSOLE imposed?**

**`lib/ge` is a MATCHING decomp and the native tree is directly editable, so
*"did we change the feel"* is A DIFF, NOT AN OPINION.** That is what `227` bought.

| | scope | worked example |
|---|---|---|
| **FREE — just do it** | hardware budgets and platform faults: slot/pool counts, memory limits, resolution, refresh ceiling, 64-bit pointer arithmetic, Windows `rename()` | **`262`'s `ANIM_MODEL_SPARE_SLOTS 10`** — a 4 MB RDRAM budget, never a design choice. `F2`'s `MoveFileExA`. These RESTORE the original intent on hardware without the constraint. |
| **CAREFUL — diff it first** | anything the player FEELS: movement curves, fire rates, reload/animation timing, AI reaction, difficulty, damage, how a scene looks | **`RB-04`'s `MoveBond` timestep.** Permitted — but diffed against the decomp and WORN before it is believed. **`118` §4's "leave feel alone" now lives here as "PROVE you did not change the feel"**, which is stronger and cheaper than not touching it. |
| **ADDITIVE — inert when off** | the VR layer: stereo, 6DoF, the pose spine, adjustable FOV | **`P1`-`P9`. With VR disabled the flat game must be the game it was.** An addition that changes the base game when switched OFF has failed this policy. |
| **ASK FIRST** | the game's DESIGN: level layout, weapon balance, objectives, mission structure, music | Not ours to decide. |

**An ambiguous change is `CAREFUL`, and it is resolved by BUILDING THE DIFF OR
THE INSTRUMENT — never by arguing the category.**
**Rules `14`-`16` in `00-START-HERE` are this policy's working half:** change the
source rather than working around it; build the instrument and validate it before
believing it; a repeated owner report is a RANKING error.

### AND THE TWO THAT WERE ALREADY STANDING

> **EVERY GIT COMMIT IS THE OWNER'S.** No commits, stages, branches, merges,
> resets or tags. **Ever.** Reading git state is fine.

> **DELETE NOTHING until the project is done.** Every knob stays reachable as an
> off-switch. Mark superseded; never remove.

---

## §1 — WHERE THE PROJECT ACTUALLY IS

**The aim is the owner's stated priority:** *"getting this hand tracking right and
the bullet leaving the gun."* It is **not solved**, but this session narrowed it
sharply and **eliminated the thing we had been varying for three wear tests.**

### THE ROOT CAUSE, NAMED IN `194`, NOW WITH FOUR FAULTS ATTACHED

> **The head rotation reaches only the EYE VIEW MATRIX, composed onto the game's
> view matrix at RENDER time. THE GAME CAMERA NEVER LEARNS ABOUT THE HEAD.**

It has produced: **(1)** the bullet's origin, **(2)** the drawn gun's orientation,
**(3)** the bullet's direction, **(4)** the frame recovery itself.

### WHAT THIS SESSION SETTLED

- **`[MEASURED]` the composition is NOT the bug.** `thr*camT` is correct and is
  already the default — confirmed independently by `gunfire.c:570-574`. `217`,
  `221` and two wear tests varied the wrong thing. (`223` §2.2)
- **`[MEASURED]` the error is CAMERA-DEPENDENT** — constant to ±3° within a
  group, jumping between. **This rules out the cone clamp, the muzzle, the seam
  and the barrel offset, all camera-independent.** (`223` §2.3)
- **`[MEASURED]` pitch already tracks** (within ~5°). **The fault is yaw-only**, so
  the fix is a rotation about one axis, not a rebuild.
- **`[MEASURED]` the ASPECT is real and is 30%** — game x/y `1.000` vs render
  `1.297`. **The "skinnier" is now a number, not an impression.** (`222` §2)
- **`[MEASURED]` GoldenEye is delta-scaled, not fixed-tick** — `g_GlobalTimerDelta`,
  216 consumers, **and Rare already shipped it at 1.2 for PAL.** 90 Hz and a game
  speed control are one term. (`224` §2)
- **`[MEASURED]` `lib/ge` is a MATCHING decomp** — 313 C files, 1 non-matching,
  builds a byte-identical ROM. **It is compiled by nothing today.** (`224` §1)

### WHAT WAS WITHDRAWN

**A least-squares recovery of a single `ViewToWorld` across 11 shots. Residual
119°. THE MODEL WAS WRONG** — the owner turned mid-run, so the camera is not
constant. **Recorded in `223` §2.1 only so it is not repeated.**

---

## §2 — THE PLAN. IN ORDER.

### STEP 1 — THE OFFLINE FRAME TEST. NO WEAR TEST. NO REBUILD. DO THIS FIRST.

**The data is already in `gevr.log`.** `223` §3: for each shot compare
`v2w^T . ray` (current) against `v2w^T . (H . ray)` and `v2w^T . (H^T . ray)`,
where `H` is the head rotation from `POSEREC hq`. Whichever minimises the angle to
the observed bullet direction wins.

**THE PARSING TRAP:** `MTXREC` and `POSEREC` **share a line** — no newline between
them. A per-line state machine yields **zero** records. **Regex the whole file and
zip by index.** (This cost this session two attempts.)

**If the head term wins:** build it as one term behind a `-HeadFrame` knob, keep
the old path reachable.

### STEP 2 — PROVE THE SOURCE PIPELINE. THE OWNER CHOSE THIS.

**`224` §5, P1–P5.** The gate is **P2** (`make` unmodified reproduces sha1
`abe01e4aeb033b6c0836819f549c791b26cfde83`) and **P5** (a self-built ROM boots and
plays).

> **IF P2 FAILS, THAT ROAD DOES NOT EXIST AND `224` §3 IS A WISH LIST. That is why
> it is first, and why NO DESIGN WORK SHOULD PRECEDE IT.**

### STEP 3 — IF P5 PASSES, THE SPLIT (NOT A MIGRATION)

**Move only what is structurally impossible from patches:**

1. **the head rotation into the camera** (`bondview.c`) — `224` §3.1, the root
   cause with four faults
2. **the aspect rebuild** (`bondview.c:657` from real tangents) — `224` §3.5
3. **`g_GlobalTimerDelta`** for 90 Hz + speed — `224` §2

**Keep the patch layer for every tunable that gets worn.**

---

## §3 — THE CHECKLIST

### AIM — THE PRIORITY
- [ ] **STEP 1's offline test** (no wear test, data in hand) — `223` §3
- [ ] build the winning frame term behind a knob
- [ ] **the crosshair slice** — owner's spec: **disappear when off-screen, sit on
      the target, much smaller.** 32×32 glyph at `gunfire.c:6225` — `224` §3.6
- [ ] **U-18 never cleanly worn**
- [ ] `noPose` — **`[MEASURED]` 218 of 2023 frames (~10%) had no controller pose.**
      Not invalidating, but not zero

### SCALE & COMFORT
- [ ] **the ASPECT, 30%, now measured** — `222` §2 / `224` §3.5. **Do not let it
      muddy the aim test; it is a separate fault**
- [ ] world scale at 25 untested — judge against a guard, **both numbers together**
- [ ] **U-25 head-relative locomotion** — designed; PD `VrArmBodyFollow = 0.02`
      (`bondgun.c:10991`). Owner: *"Forward follows your head"*, *"I am in a seat
      that spins"*
- [ ] **U-24 calibration phase** — `205`, standing/empty

### STABILITY
- [ ] **menu crash** — both quick fixes blocked; `208`'s autolaunch is **inert**
      (it hooked `waitForNextFrame`, which the front end does not use — `137`).
      **Correct hook is `viSetFovY`**
- [ ] **B3/B4 X-close** — use `taskkill`. **This cost a whole session to a machine
      crash once**
- [ ] 2.4% late frames

### NATIVE PORT — THE LIVE CHECKLIST (2026-08-27 LATE, supersedes the recomp lists below for direction; `229` §20)
- [x] **PHASE 0 — the native port BOOTS AND PLAYS from the owner's ROM** (`229` §11)
- [ ] **THE COMMIT — ITEM 0, DO IT FIRST.** The working build is untracked
- [ ] **menu text not drawn** — assets proven innocent; a RENDER read. **Blocks all
      normal play, and `GETV_MENU` is not a substitute for fixing it**
- [ ] **wrong sfx** — `GETV_AUDIO_TESTSFX=<id>`, built and never run
- [ ] **audio latency ~51 ms** — SDL `want.samples 512 -> 256` next, one term per run
- [ ] **purple explosion** — not a missing texture; needs the menu fixed first
- [ ] **fold `229` §9's two traps into `SETUP.md` §3.5** (normalise the CSVs, and
      `extract` is column 4) — **without this a fresh clone repeats this whole session**
- [ ] **`uniquify_asset_symbols.py` portability bugs still UNFIXED in the vendored
      tool** (`clang -O1`; `globals_of` requires a leading `_`) — worked around only
- [ ] **THEN Phase 1 — stereo** (`228` §5)

### HOUSEKEEPING
- [ ] **THE COMMIT — 40+ DOCUMENTS OVERDUE, BOTH REPOS.** Owner-only,
      `commit-session.ps1` at the main PC, **not through the bridge**

---

## §4 — THE BUILD AND RUN

```powershell
.\build.ps1     # TWICE if any new symbol was added (docs 136)
.\build.ps1
```

**The current wear-test line:**

```powershell
.\vr.ps1 -HandSeam -HandPosZ 1 -ViRate 90 `
         -WorldUnitsPerMetre 25 -HandUnitsPerMetre 25 `
         -ViewmodelScale 0.5 -GunOffX 0 -GunOffY 0 -GunOffZ 0 `
         -AimFromHand -MuzzleOrigin -NoCrouch -HudDepth 0.2
```

**`-HudDepth 0.2` is the value that WORKED and must win over parallax** — `210`
regressed this once by letting an untested term take precedence by default.

**THE STALE-LOG TRAP (`133`):** **always check that `gevr.log` is NEWER than
`build/Release/GoldenRecomp.exe`** before reading it. The owner caught this
himself this session: *"gevr.log predates this exe. It describes the OLD binary."*

---

## §5 — METHOD, EARNED THE HARD WAY

> **`[MEASURED]` across this whole session: every RECORDING answered its question
> in ONE run (`200`, `203`, `212`, `222`'s ASPECT, `223`'s MTXREC). Every GUESS
> (`213`, `214`, `215`, `217`, `221`) had to be corrected by the next
> measurement.**

**When tempted to ship a candidate, ship an instrument instead.**

**And the owner's corrections have been right every time they conflicted with my
reading** — `195` §3, `219` §2, the barrel-length diagnosis (*"the larger gun went
further to the right"* — an error scaling with barrel length is a rotation error).
**Wear reports outrank analysis.**

**The GoldenEye source at `lib/ge/src` is a valuable source of truth — USE IT.**
It settled U-18, the 32×32 glyph, the `field_B58` two-frame trap, the composition
question, and the whole of `224`. **Search for the MECHANISM, never for Perfect
Dark's identifier (`168`).**
