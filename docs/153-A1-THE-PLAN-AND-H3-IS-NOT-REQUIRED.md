# 153 — A1, THE PLAN. AND H3 IS NOT REQUIRED FOR IT.

**2026-08-25. A read session — no code, no launch, no headset. Written as a plan
and STOPPED for a reply, `48`: "a doc written and executed in the same breath is
a changelog."**

---

## §1 — WHAT THE OWNER DESCRIBED IS A1, AND HIS BUILD IS ALREADY HALF OF IT

> *"It moves the hand and makes the gun change its position, but not its shot."*

**That is `90` §1 in one sentence: THE BULLET IS CLAMPED AND THERE IS NO
UNCLAMPED SHOT PATH.** Two integrators, two dampings, two destinations:

| | Feeds | Clamped? | Drives |
|---|---|---|---|
| `crosshair_x_pos` -> `crosshair_angle` | `guncrossdamp` | **YES**, `gunfire.c:4699-4715` | **THE BULLET** + the HUD crosshair |
| `gun_azimuth_angle` -> `field_FFC` | `gunaimdamp` | **NO** | **THE GUN MODEL'S POINTING**, muzzle flash, viewmodel sway |

**His hand mapping drives the unclamped one. The gun swings; the bullet does
not follow.** The 2026-08-24 log says it in one line:

```
6dof-game: BULLET crosshair_angle=(166,116)px CLAMPED | GUNPOINT field_FFC=(166,116)px unclamped
```

**`101` §6.3 already scoped this: "The gap between 'the arm is free' and 'the
bullet follows' IS slice A1. It is the only part of his description that is not
already in the build."**

---

## §2 — H3 IS NOT REQUIRED. THE DEPENDENCY IS AN ARTEFACT OF THE ROUTE `86` CHOSE.

**`86` §6 says flatly: *"H3 body yaw ► A1 cannot be written without it"*, and the
H3 slice repeats it: *"the gun's world direction needs it."* THAT IS TRUE OF
`86`'s RECIPE AND NOT OF THE PROBLEM.**

`86`'s five-step recipe goes **camera -> WORLD -> camera**:

> 1. Gun forward `{0,0,-1}` through the override matrix.
> 2. **Into world via the head quaternion, then the body yaw (slice H3).**
> 3. Back into camera space, invert `transformAndNormalizeByLength2Dto3D` -> pixel.

> ## **STEP 2 AND STEP 3 UNDO EACH OTHER. THE GUN AND THE CAMERA SHARE THE SAME BODY YAW, SO IT CANCELS ON THE ROUND TRIP.**
>
> **`86` SAW THIS ITSELF, one paragraph earlier:** *"So we do not need PD's
> world->screen route. They use `camGetWorldToScreenMtxf` because they start
> from a world point; **we can start from the gun's direction in camera space
> and invert two lines of arithmetic**."* **The shortcut is named and then the
> recipe takes the long way anyway, and the dependency comes from the long way.**

**AND THERE IS A SHORTER ROUTE STILL, WHICH DID NOT EXIST WHEN `86` WAS WRITTEN:**

> ### **`field_FFC` IS ALREADY THE GUN'S POINTING AS A SCREEN POINT, IN PIXELS, UNCLAMPED, AND ALREADY DRIVEN BY THE OWNER'S HAND MAPPING.**
> **`(166,116)px` in the log.** There is nothing to unproject, nothing to route
> through world space, and therefore **nothing for body yaw to do.**

**SO H3 (6D-04) IS NOT A BLOCKER FOR A1. It remains worth building** — G1/G2/G3
and any true world-space work still need a named body yaw, and **`86`'s rule 8
point stands: every consumer reads it, nobody re-derives it.** It is no longer
in front of the headline feature.

---

## §3 — THE CHANGE. CORRECTED BY THE READS IN §7, WHICH WERE DONE THE SAME DAY.

**MY FIRST §3 SAID: "feed the bullet integrator from the same screen point that
drives the gun's pointing." IT IS WRONG, AND THE FUNCTION SAYS SO IN 69 LINES.**

### §3.1 — BOTH INTEGRATORS ALREADY TAKE THE SAME INPUT

`gunfire.c:4666-4734`, read end to end:

```c
for (i = 0; i < g_ClockTimer; i++) {                       /* :4692 THE BULLET */
    crosshair_x_pos = (crosshair_x_pos * guncrossdamp) + turn_x;
}
crosshair_angle.f[0] = (crosshair_x_pos * (1-guncrossdamp) * w * 0.5f) + w*0.5f;
   /* :4698-4715  CLAMPED to [3, w-4] */

for (i = 0; i < g_ClockTimer; i++) {                       /* :4722 THE GUN */
    gun_azimuth_angle = (gun_azimuth_angle * gunaimdamp) + turn_x;
}
field_FFC.x = (gun_azimuth_angle * (1-gunaimdamp) * w * 0.5f) + w*0.5f;
   /* NOT CLAMPED */
```

**`turn_x` FEEDS BOTH. They differ in the damping constant and in the clamp, and
in nothing else.**

### §3.2 — AND THE DAMPING CANCELS. THE STEADY STATE IS IDENTICAL.

Solve the integrator: `x* = t / (1 - d)`. Substitute into the screen line:

```
screen = x* (1-d) (w/2) + w/2  =  t (w/2) + w/2      <- d CANCELS
```

**Checked numerically at `guncrossdamp` 0.7651, `gunaimdamp` 0.9 and 0.5: all
three land on the SAME pixel.** The damping sets only how FAST each converges.

> ## **SO THE CLAMP IS THE ONLY STEADY-STATE DIFFERENCE BETWEEN WHERE THE GUN POINTS AND WHERE THE BULLET GOES.**
>
> **AND IT EXPLAINS THE OWNER'S REPORT EXACTLY.** *"It moves the hand and makes
> the gun change its position, but not its shot."* **Push the aim past the screen
> rectangle and `crosshair_angle` PINS at `[3, w-4]` while `field_FFC` keeps
> going.** The gun tracks the hand; the bullet stops at the edge. **That is
> `gunfire.c:4698-4715` and nothing else.**

**This was G-A1-3's PREDICTION** — *"the crosshair pins and the gun keeps
tracking, so gun and bullet visibly disagree"* — **and the owner has already
observed it in the headset without either of us recognising it as that gate.**

### §3.3 — SO A1 IS THE CLAMP, AND PERFECT DARK'S ANSWER APPLIES DIRECTLY

**`102` §1: PD clamps the DRAWN CROSSHAIR and leaves the BULLET AIM UNCLAMPED.**
That is precisely the split we need, and **prior art ships it.**

**The change: compute the crosshair position ONCE, keep the UNCLAMPED value for
the bullet, and apply the `[3, w-4]` clamp only on the path that DRAWS.**

**THE READ THAT DECIDES THE SHAPE IS STILL OWED AND IS NOW THE ONLY ONE LEFT:**
`90` counted **eight readers of `crosshair_angle`** — the drawn crosshair,
auto-aim target selection, and the hit path among them. **Each must be sorted
into "wants the clamped screen position" or "wants the true aim".** `48` rule 6,
and `101` §6.2: *"a crosshair at pixel -400 is a valid ray and an invalid screen
position."*

**DO NOT SIMPLY DELETE THE SIXTEEN LINES.** Auto-aim and the HUD almost
certainly want the clamped value; the bullet does not.

## §4 — THE TIMEBASE COLLISION `101` §6.4 FLAGGED IS RESOLVED, AND IN OUR FAVOUR

```c
for (i = 0; i < g_ClockTimer; i++) {
    crosshair_x_pos = (crosshair_x_pos * guncrossdamp) + turn_x;
}
```

**`101` §6.4 warned that the aim work and the timebase work touch the same four
lines, and that whichever is built second must know what the first did.** Route
B was built first. **So this is now answerable rather than a worry:**

> **UNDER RB-02 THE LOOP RUNS 0 OR 1 TIMES PER FRAME AT 90 Hz INSTEAD OF ONCE
> PER FRAME AT 60 — BUT `waitForNextFrame`'s ACCUMULATOR EMITS EXACTLY SIXTY
> TICKS PER REAL SECOND (`per1000ms=60`, measured on every run). THE INTEGRATOR
> THEREFORE STILL GETS SIXTY ITERATIONS A SECOND AND THE AIM FEEL IS PRESERVED.**

**`92` §4's *"changing the quantum changes the aim feel of every weapon"* does
NOT fire here, because the quantum's RATE did not change — only its
distribution across frames did. **This is a PREDICTION, not a measurement:
G-A1-5 below is what would falsify it.**

---

## §5 — THE GATES. Written before the code, and each asks what a working build would have to do differently to FAIL.

| Gate | Test |
|---|---|
| **G-A1-1** | **Point off-centre and fire. The shot lands where the barrel points, not where the head looks.** `86`. **Today's build cannot pass this at all** — it is the whole slice |
| **G-A1-2** | **Switch weapons mid-burst. Aim does not jump.** `guncrossdamp` comes from `WeaponStats` and the game **rescales `crosshair_x_pos` underneath us**; a once-per-switch write fails ONLY here |
| **G-A1-3** | **Point PAST the clamp and report what happens, in the same launch — not discovered later.** PREDICTION: the crosshair pins, the gun keeps tracking, and **gun and bullet visibly disagree.** That is expected, and it is what §3 item 3 exists to decide |
| **G-A1-4** | **`-NoXr` aims with the stick exactly as before.** The patch replaces a function BOTH paths call. **No headset, no reboot risk — run this one first** |
| **G-A1-5** | **Aim feel is unchanged from today at `-ViRate 90`** — §4's prediction. If reloading or tracking feels wrong, §4 is falsified and the integrator is seeing a different iteration count than the accumulator implies |

**G-A1-4 IS FIRST AND COSTS NOTHING.** `48`/`63`: this touches a function the
monitor path also calls, so the `-NoXr` bisect runs BEFORE the headset. **That
rule cost two reboots last session by being skipped.**

---

## §6 — WHAT THIS DOES NOT DO

- **It does not touch the clamp.** §3 item 3.
- **It does not build H3.** §2.
- **It does not need the OpenXR controller path.** `handValid=0` and
  `NONE BOUND` are real (6D-14) but describe an **unused** route: the hand
  reaches the game through the owner's own mapping. **A1 rides the path that
  already works.**
- **No per-weapon table.** `86` §7: not until two weapons are measured to
  disagree.

---

## §7 — THE READS STILL OWED BEFORE THE BUILD

**`76` and `86` §8 both say do these before, not during.**

1. **Whether `crosshair_x_pos` has readers besides
   `caclulate_gun_crosshair_position_rotation`.** `86` §8 item 2, still open.
2. **`caclulate_gun_crosshair_position_rotation`'s exact length and every symbol
   it calls**, against `07`'s `RECOMP_PATCH` rules. **~85 lines is "looks
   patchable", which is not this project's standard.**
3. **Count the new `RECOMP_PATCH` names BEFORE the first build** — `07`, and
   `136`: **helpers in patch code are NON-STATIC or the recompiler never emits
   them.**

### READ 1 — CLOSED. `crosshair_x_pos` HAS NO OTHER READERS.

**Eleven sites in the whole tree, and `gunfire.c` owns every meaningful one:**

| Site | What |
|---|---|
| `bondview.h:1058-1059` | the struct fields |
| `gunfire.c:4678-4679` | **the weapon-switch rescale — G-A1-2's exact line, confirmed present** |
| `gunfire.c:4692-4693` | the integrator |
| `gunfire.c:4696-4697` | produces `crosshair_angle` |
| `initBondDATA.c:287-288`, `player.c:379-380` | zero-init |

> **`86` §8 item 2 IS ANSWERED: NO, THERE ARE NO OTHER READERS. Writing
> `crosshair_x_pos` is contained.** The exposure is entirely in
> `crosshair_angle`'s eight readers, which is a different question — §3.3.

### READ 2 — CLOSED. THE FUNCTION IS 69 LINES, NOT ~85, AND IT IS PATCHABLE.

`caclulate_gun_crosshair_position_rotation`, `gunfire.c:4666-4734`. **Two
callers**, `:4752` (auto-aim, passing `max_aim_lock_speed`) and `:4775`
(`sub_GAME_7F067FBC`, the owner's aim-mode entry point). **Calls only
`getPlayer_c_screenwidth/height/left/top`,
`transformAndNormalizeByLength2Dto3D` and `sub_GAME_7F067AB4`.**

### READ 3 — STILL OWED

**Count the new `RECOMP_PATCH` names BEFORE the first build** — `07`, and `136`:
**helpers in patch code are NON-STATIC or the recompiler never emits them.**

> **AND ONE READ IS ADDED, WHICH §3.3 CREATED AND WHICH IS NOW THE GATING ONE:
> SORT `crosshair_angle`'s EIGHT READERS INTO "WANTS THE CLAMPED SCREEN
> POSITION" AND "WANTS THE TRUE AIM". No machine needed.**

---

# §8 — THE GATING READ IS DONE. THE EIGHT READERS SORT ONE-TO-SEVEN.

**2026-08-25, same session. No machine. This is the read `§3.3` said had to
happen before a line of the clamp was touched.**

## §8.1 — EVERY SITE, CLASSIFIED

**WRITERS — three, and two of them matter more than expected:**

| Where | What it does |
|---|---|
| `gunfire.c:4696-4718` | the integrator, **then the clamp**. The function A1 patches |
| `sub_GAME_7F06802C()` `:4794` | **recentres BOTH** `crosshair_angle` **and** `field_FFC` to screen centre |
| `sub_GAME_7F0680D4()` `:4818` | projects a rotation matrix, writes `crosshair_angle`, **then copies it into `field_FFC`** |

> **NOTE WHAT THE TWO EXTRA WRITERS DO: they set `field_FFC = crosshair_angle`,
> UNCLAMPED, deliberately keeping the gun and the aim identical.** The engine
> already treats "gun points where the aim points" as the correct state.
> **`:4698-4715` is the ONLY place the two are pulled apart.**

**READERS — and the sort is not eight-way, it is ONE against the rest:**

| Reader | Callers | Wants |
|---|---|---|
| **`gunDrawSight()`** `:6214` | draws `crosshairimage` | **THE CLAMPED VALUE.** It is a texture blit; off the screen rectangle it is wrong or invisible |
| `get_bullet_angle()` `:4783` | **`chrprop.c:2322`, the auto-aim / target test** | **TRUE AIM** — §8.2 |
| `sub_GAME_7F068190()` `:4839`, `:5185` | `bondview2.c:8258`, `chraction.c:9995`, `gun.c:2326`, `gunfire.c:194` | **TRUE AIM.** It unprojects to a direction vector |
| `bullet_path_from_screen_center()` `:4865`, `:5211` | `chrprop.c:931/1423`, `gun.c:1775/1862/1961/2143` | **TRUE AIM.** The shot itself |

## §8.2 — THE AUTO-AIM READER WANTS THE TRUE AIM, AND THIS IS THE ONE THAT COULD HAVE GONE WRONG

`chrprop.c:2322` reads it into the manual-aim branch:

```c
passes_horizontal_check = screen_left_edge[0] <= crosshair_x && crosshair_x <= screen_right_edge[0];
```

**It compares the crosshair against the target's projected screen bounds — and
those bounds come from `transform3Dto2DCoords`, which is NOT clamped.** So both
sides of the comparison are already in unclamped screen space.

> **FEEDING IT THE CLAMPED VALUE IS THE BUG, NOT THE FIX. With the gun pointed
> off-screen, a clamped crosshair sits at `x = w-4` and this test reports a hit
> on whatever happens to be at the screen edge.** **The true aim is the correct
> input here and always was.**

## §8.3 — SO THE CHANGE IS SMALLER AND SAFER THAN "DELETE SIXTEEN LINES"

> ## **KEEP `crosshair_angle` UNCLAMPED — IT IS THE TRUE AIM. MOVE THE `[3, w-4]` CLAMP INTO `gunDrawSight()`, WHICH IS THE ONLY CONSUMER THAT WANTS IT.**

**That is `102` §1's Perfect Dark split — clamp the DRAWN crosshair, leave the
BULLET AIM unclamped — confirmed at the call-site level in our own tree.**

**AND IT MUST BE KNOB-GATED.** `:4698-4715` exists because stock aim genuinely
reaches the screen edge; removing it unconditionally changes stock play, and
**G-A1-4 requires `-NoXr` to aim exactly as before.** Knob off: the clamp stays
where it is and the build is an exact identity. **`48` rule 6, and `131`'s
unset-build discipline, which paid for itself in Route B.**

## §8.4 — WHAT IS NOW OWED BEFORE THE BUILD

**ONLY READ 3 REMAINS:** count the new `RECOMP_PATCH` names before the first
build (`07`), and **helpers in patch code are NON-STATIC** (`136`).

**AND ONE NEW GATE, BECAUSE §8.2 FOUND A BEHAVIOUR CHANGE NOBODY ASKED FOR:**

| Gate | Test |
|---|---|
| **G-A1-6** | **Auto-aim and target selection still behave at close range with the knob ON.** §8.2 says the true aim is more correct here, **which means A1 silently CHANGES auto-aim** — a fix, but an unrequested one. **`48` rule 6: this is a value someone else reads back, and it is the sixth instance.** Watch for enemies becoming easier or harder to hit at the screen edge |

---

# §9 — AS BUILT. WRITTEN, NOT COMPILED, NOT RUN.

**2026-08-25. Six files. One behaviour change, knob-gated, off by default.**

| File | Change | Backup |
|---|---|---|
| **`patches/ge_vr_aim.c`** | **NEW.** `RECOMP_PATCH caclulate_gun_crosshair_position_rotation` - stock line for line, with `:4699-4715`'s clamp wrapped in `if (!geVrFreeAimActive())` | n/a |
| `patches/syms.ld` | `recomp_ge_vr_free_aim = 0x8F000130` (next free) | — |
| `patches/misc_funcs.h` | `DECLARE_FUNC(s32, recomp_ge_vr_free_aim)` | — |
| `patches/externs.h` | declares `transformAndNormalizeByLength2Dto3D` and `sub_GAME_7F067AB4` - **signatures READ off `bondview.h:2801` and `gunfire.c:4645`, not guessed** | `.bak153` |
| `src/game/recomp_api.cpp` | the host side, reading `GE_VR_FREE_AIM` | `.bak153` |
| `vr.ps1` | `-FreeAim`, **AND THE NAME ADDED TO THE CLEAR LIST AT `:358`** | `.bak153` |

> **THE CLEAR-LIST LINE IS NOT OPTIONAL.** `vr.ps1` wipes every `GE_VR_*` before
> setting the ones it wants, **so a knob absent from that list is a knob that
> never fires** - `48` rule 6, and the exact shape of the dead `-Sign` knob in
> `32`. It was nearly missed here too.

**`vr.ps1` PARSES CLEAN** - checked with `[Parser]::ParseFile`, not by eye.

## §9.1 — WHY ONE PATCH AND NOT TWO

**`gunDrawSight` is NOT patched in this slice.** Wrapping it was investigated
and **rejected on evidence:** `tools_weaken_patched.py` renames the *recompiled*
original, which has the `(uint8_t* rdram, recomp_context* ctx)` signature — **so
`NAME__recomp_orig` is not callable as a plain C function from patch code.**
Reimplementing its 25 lines and 4 `#ifdef` branches is a second behaviour change
and belongs in its own build (`48` rule 5, and `142` is the fresh proof).

**CONSEQUENCE, STATED SO IT IS NOT READ AS A BUG:** with the knob on, **the HUD
crosshair follows the gun off the screen edge.** That is G-A1-3's observation and
the visible proof the lock broke. **Clamping the draw is slice A1b**, and it is
what `102` §1 says Perfect Dark does.

## §9.2 — THE BUILD, AND A TRAP FOUND WHILE READING IT

**CMake runs the whole patch chain** — `PatchesBin` (`make` in `patches/`, which
globs `*.c`, so the new file needs no CMake edit) -> `./N64Recomp patches.toml`
-> `RecompiledPatches/patches.c` -> `PatchesLib`. **`build.ps1`'s header watch
covers `patches/`, so the two header edits force a FULL rebuild** (`115`).

> ### **`CMakeLists.txt:150` CARRIES A STANDING TODO: *"modifying patches requires two builds to take."***
> **AND THIS IS A BRAND-NEW `RECOMP_PATCH` NAME**, which `07` says needs the
> rename script re-run, and `133` says `build.ps1` self-heals **once** on
> `LNK2005`. **SO: RUN `.\build.ps1` AND IF THE FIRST RUN DOES NOT PRODUCE A
> WORKING KNOB, RUN IT AGAIN BEFORE CONCLUDING ANYTHING.** A patch that silently
> never got emitted is `136`'s exact failure and it cost a whole session.

## §9.3 — THE ORDER THE GATES RUN IN

1. **`.\build.ps1`** — must report a FULL rebuild. Run twice if needed (§9.2).
2. **`.\vr.ps1 -NoXr` — G-A1-4 FIRST, KNOB OFF.** Aim with the stick must be
   exactly as today. **No headset, no reboot risk.**
3. **`.\vr.ps1 -NoXr -FreeAim`** — G-A1-1 on the monitor: point off-centre, fire,
   and see whether the shot follows the barrel. **G-A1-2** weapon switch,
   **G-A1-3** the crosshair leaving the screen, **G-A1-6** auto-aim at the edge.
4. **Only then the headset.** `48`/`63`: the render/present bisect before wearing
   anything — **the rule whose skipping cost two reboots on 2026-08-24.**
