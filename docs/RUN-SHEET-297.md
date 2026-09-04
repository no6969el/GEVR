# RUN-SHEET-297 — ARM 3. **THE CHARACTERS AND THE PROPS, IN BOTH EYES.**

**READ `297` §0, §3, §4 AND §5 FIRST.** Every block below is complete and self-contained — no block
delegates to another sheet (`296` §11 defect 1). Run them **in order**. The order is not a
convenience: **R1 is the negative arm and it runs before the positive one** (`279` §7, rule `15`).

**THE GATE THIS SHEET IS FOR, IN ONE SENTENCE:** *the people, the characters and the props are
present and stable in BOTH eyes.* Not a disparity number. **S3 does not run until that is true** —
a separation measured on an eye with no world is a number about nothing.

---

## §1 — THE OFFLINE GATES, ON THE MAIN PC. **BEFORE THE BUILD.**

They were worn on the bridge under `gcc 11.4.0`; the main PC has a different compiler and the
harness invokes bare `gcc`. Strong evidence, different event.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
bash getv/tools/stereo_harness.sh
py getv\tools\stereo_disparity.py --selftest
```

**GATE §1 — three things:**

1. **`63 passed, 0 failed` / `VERDICT PASS`.**
2. **The real-header syntax gate reads `PASS 0 errors` for all NINE files** — `stereo.c`, `lv.c`,
   `fr.c`, `bondview2.c`, `dyn.c`, `model.c`, `propobj.c`, and **`chr.c` and `chrprop.c`, which are
   new to the gate because ARM 3 edits them.** A FAIL here is a compile error found in one second
   instead of a link failure found in ten minutes (`292`, `00-STATE` §6).
3. **The three-arm pairing falsifier still reads `pairmono 0 / pairoff 2 / pairon 0`** — the
   **middle arm must still fire.** A harness whose falsifier has gone quiet is not a harness.
4. `stereo_disparity.py --selftest` recovers the injected `-37`.

---

## §2 — THE BUILD

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv
.\build_windows.ps1 *> F:\Projects\GEVR\GoldenEyeVR\build_297_arm3.log 2>&1
Select-String -Path F:\Projects\GEVR\GoldenEyeVR\build_297_arm3.log -Pattern 'first failure|conflicting types|error|Build succeeded|goldeneye.exe' | Select-Object -First 20
Get-Item F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
```

**►► READ THE FIRST FAILURE LINE, NOT THE LAST ERROR** (`00-STATE` §6). A conflicting declaration is
a hard error that survives `-w`, kills one object file, and buries itself under a wall of
`undefined reference` that reads like *"the new file was never added to the build"*.
**`297` adds three prototypes to `ge_port_decls.h` and nowhere else, precisely so this cannot
happen — but the `Select-Object -First 20` stays deliberate.**

**GATE §2: the exe's `LastWriteTime` moves.** If it still reads `2026-09-02 01:29`, nothing was
built and every block below is scoring the previous binary.

---

## §3 — GATE B1. **IS ARM 3 ACTUALLY IN THE BINARY?**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
$strings = '[getv][stereo] ON','ARM 1 view-pair restore','ARM 3 per-eye render rebuild','pairguard] ON','pairguard] SUMMARY','pairguard] MISMATCH','rebuild] SUMMARY','rebuild] GATE','forced-read-after-lvlRender','PREDICTION frame=','1/D LAW','pools scaled x'
# Select-String -Encoding Byte was REMOVED in PowerShell 7 (`297`): it throws "'Byte' is not a
# supported encoding name", and with -ErrorAction SilentlyContinue every probe then prints
# MISSING on a binary that may well contain all of them. A NULL RESULT PRODUCED BY A CMDLET THAT
# NEVER RAN IS NOT A NULL RESULT. Read the bytes. Latin1 is the only decoder that maps all 256
# byte values one-to-one, so nothing is lost or folded before the search.
$bytes = [System.IO.File]::ReadAllBytes((Resolve-Path .\goldeneye.exe))
$blob  = [System.Text.Encoding]::Latin1.GetString($bytes)
foreach ($s in $strings) {
  "{0,-36} {1}" -f $s, ($(if ($blob.Contains($s)) {'FOUND'} else {'MISSING'}))
}
Remove-Variable blob, bytes
```

**GATE B1: all TWELVE read FOUND.** A knob that is not in the binary reads as a clean null result
(`133`, `268` §4). **`rebuild] SUMMARY` and `rebuild] GATE` are new and are ARM 3's own census —
if those two are MISSING, `chrprop.c` did not make it into the build and nothing below means
anything.**

---

## §4 — R0. **THE SHIPPING PATH IS UNCHANGED. AND IT RUNS FIRST.**

> **►►►►►►►► R0 IS GREEN AS OF 2026-09-02. `297` §11.5. THIS BLOCK IS DONE — GO TO §5. ◄◄◄◄◄◄◄◄**
> `[MEASURED]`: a full session, shooting characters, walking and returning, **no crash**, 39 MB of
> log against the 2.2 MB truncated ones the bug produced.
>
> **§10's `objBuildRenderState + 199` IS RETRACTED IN FULL — that function is not on the R0 stack
> at all**, and the symbol came from a load base derived by assuming it was (`297` §11.1). **The
> real cause was `chr.c:3305`: `if (headSwitchVisible)` written TWICE**, so the `else` bound to the
> inner `if` and an off-screen chr never cleared `PROPFLAG_ONSCREEN` while its `field_20` joint
> list had already been nulled. Fixed.
>
> **►► IF YOU RE-RUN THIS BLOCK: DO NOT SHOOT A MINE.** That crash is real, **pre-existing, and not
> ARM 3's** — `297` §12, proven against the saved pre-ARM-3 binary. It will fire in R1 and R2 too.
>
> **►► THE TWO DIAGNOSTIC KNOBS ARE WORTH LEAVING ON: `GETV_CHR_DEBUG=1` and `GETV_HIT_DEBUG=1`.**
> They had been in the tree unused, and `rej(off=0)` is what named the bug above.

`48` allows exactly one behaviour change per knob, and ARM 3 touched `objTick` and `chrTick` — the
two functions the entire game runs through. **Before anything stereo is looked at, the mono game has
to be the mono game.**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
$env:GETV_SLOTFREE              = "1"
$env:GETV_VSYNC                 = "1"
$env:GETV_FPS                   = "panel"
$env:GETV_SIMHZ                 = "query"
$env:GETV_SIMDIV                = "1"
$env:GETV_WIDESCREEN            = "0"
$env:GETV_ROOMSCISSOR           = "1"
$env:GETV_WINDOW                = "2560x1369"
$env:GETV_STAGE                 = "29"
$env:GETV_DIFFICULTY            = "0"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_297_R0_mono_shipping.log 2>&1
Select-String -Path run_297_R0_mono_shipping.log -Pattern 'GETV_FPS=panel'
Select-String -Path run_297_R0_mono_shipping.log -Pattern 'getv\]\[stereo\]|getv\]\[rebuild\]'
Select-String -Path run_297_R0_mono_shipping.log -Pattern 'props interpolated|simulation held to|ours: x=|game_exit requested'
```

**PLAY IT, AND SHOOT FIRST.** Two or three minutes: **fire the gun immediately**, then walk, shoot a guard, watch him flinch and drop, break glass, open
a door, take the tank if you pass it.**

**GATE R0 — and every one of these is a thing ARM 3 could have broken:**

1. **NOT ONE `[getv][stereo]` OR `[getv][rebuild]` LINE IN THE LOG.** Every knob is off; every entry
   point must be silent (`48`).
2. **GUARDS FLINCH NORMALLY WHEN SHOT.** `chr.c:2893`'s `flinchcnt` now sits behind a `simOwner`
   parameter, and `chrTick` passes 1. **If flinch recovery looks fast, slow, or stuck, the guard is
   wrong and nothing else in this sheet matters** (`293` §3c.1).
3. **CHARACTER COLOURS DO NOT POP OR LAG WHEN THEY MOVE BETWEEN LIT AND DARK ROOMS.**
   `update_color_shading` took the same parameter (`295` §3).
4. **DOORS MAKE THEIR NOISE ONCE.** The iris-door SFX edge is behind `isSimOwner` inside the
   extracted build (`293` §3b.1).
5. **`props interpolated 0`, zero `simulation held to`, log ends `game_exit requested`.**
6. `GETV_FPS=panel -> <n> Hz` and `ours: x=367.333`.

**►► IF R0 FAILS, STOP.** The extraction broke the shipping game and no stereo arm can be read over
that.

---

## §5 — R1. **THE NEGATIVE ARM. STEREO ON, REBUILD OFF — THE BROKEN PICTURE, ON PURPOSE.**

This is the frame everyone already knows is wrong, and it runs **before** the fix so the fix has
something to be compared against. `279` §7: an instrument tuned on the positive frame passes its
own contract until it meets the negative one.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
$env:GETV_SLOTFREE              = "1"
$env:GETV_VSYNC                 = "1"
$env:GETV_FPS                   = "panel"
$env:GETV_SIMHZ                 = "query"
$env:GETV_SIMDIV                = "1"
$env:GETV_WIDESCREEN            = "0"
$env:GETV_ROOMSCISSOR           = "1"
$env:GETV_WINDOW                = "2560x1369"
$env:GETV_STAGE                 = "29"
$env:GETV_DIFFICULTY            = "0"
$env:GETV_STEREO                = "1"
$env:GETV_STEREO_OFFSET         = "0"
$env:GETV_STEREO_MODE           = "1"
$env:GETV_STEREO_VIEWRESTORE    = "1"
$env:GETV_STEREO_PAIRGUARD      = "0"
$env:GETV_STEREO_REBUILD        = "0"
$env:GETV_STEREO_REBUILD_REPORT = "600"
$env:GETV_DLGRAB_AT             = "5400"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_297_R1_rebuild_off.log 2>&1
Select-String -Path run_297_R1_rebuild_off.log -Pattern 'GETV_FPS=panel'
Select-String -Path run_297_R1_rebuild_off.log -Pattern 'getv\]\[stereo\]|dlgrab_'
Select-String -Path run_297_R1_rebuild_off.log -Pattern 'rebuild\] SUMMARY'
Select-String -Path run_297_R1_rebuild_off.log -Pattern 'props interpolated|simulation held to|game_exit requested'
```

**WALK UNTIL YOU CAN SEE A GUARD, THEN PRESS F9 TWICE with him on screen.** `GETV_DLGRAB_AT=5400`
takes one automatically — at `panel` on a 180 Hz display that is ~30 s in, deliberately far past the
level-load fade (`295`'s S2 grab at frame 900 was ~5 s and came back BLACK, and the gate scored the
resulting refusal as a PASS).

**GATE R1 — the negative arm passes by being WRONG in the way it is supposed to be:**

1. **The banner reads `ARM 3 per-eye render rebuild off`.**
2. **`rebuild] SUMMARY ... eyes-rebuilt=0 chr=0 obj=0`.** The census is zero **by construction**, and
   that is what every build from `292` to `296` did.
3. **ON SCREEN: the characters and props are missing from one half, exactly as reported.** Look at
   it and say which half. **This is the "before" picture and it is evidence, not a formality.**
4. `props interpolated 0`, zero `simulation held to`, `game_exit requested`.

---

## §6 — R2. **THE ARM. STEREO ON, REBUILD ON, ZERO SEPARATION.**

**Identical to §5 with one character changed.** That is the point: one knob, one behaviour change
(`48`), and the difference between the two pictures is the whole finding.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
$env:GETV_SLOTFREE              = "1"
$env:GETV_VSYNC                 = "1"
$env:GETV_FPS                   = "panel"
$env:GETV_SIMHZ                 = "query"
$env:GETV_SIMDIV                = "1"
$env:GETV_WIDESCREEN            = "0"
$env:GETV_ROOMSCISSOR           = "1"
$env:GETV_WINDOW                = "2560x1369"
$env:GETV_STAGE                 = "29"
$env:GETV_DIFFICULTY            = "0"
$env:GETV_STEREO                = "1"
$env:GETV_STEREO_OFFSET         = "0"
$env:GETV_STEREO_MODE           = "1"
$env:GETV_STEREO_VIEWRESTORE    = "1"
$env:GETV_STEREO_PAIRGUARD      = "0"
$env:GETV_STEREO_REBUILD        = "1"
$env:GETV_STEREO_REBUILD_REPORT = "600"
$env:GETV_DLGRAB_AT             = "5400"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_297_R2_rebuild_on.log 2>&1
Select-String -Path run_297_R2_rebuild_on.log -Pattern 'GETV_FPS=panel'
Select-String -Path run_297_R2_rebuild_on.log -Pattern 'getv\]\[stereo\]|dlgrab_'
Select-String -Path run_297_R2_rebuild_on.log -Pattern 'rebuild\] SUMMARY'
Select-String -Path run_297_R2_rebuild_on.log -Pattern 'props interpolated|simulation held to|game_exit requested'
```

**SAME ROUTE AS R1. Get a guard on screen and press F9 twice.** Then, identifying the BMP by the
log's **own** `dlgrab_` announcement and never by timestamp (`00-STATE` §6, `279` §2):

```
py F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\tools\stereo_disparity.py F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows\dlgrab_<N>.bmp
```

### GATE R2 — SIX THINGS, AND EACH CAN FAIL ON ITS OWN

1. **►►►► THE CHARACTERS AND THE PROPS ARE IN BOTH HALVES. ◄◄◄◄** Guards, their weapons, crates,
   doors, the tank. **This is the gate. Everything else on this sheet is support for it.**
2. **NOTHING WARPS.** Watch a guard walk across both halves. A character that is present but
   stretched, twisted or anchored to the wrong place means the build ran but under the wrong view —
   a different fault from absence, and a worse one.
3. **`rebuild] SUMMARY ... eyes-rebuilt=1` and `chr` + `obj` both > 0.** With the world drawn,
   `chr` should track the guards on screen and `obj` the props. **`chr=0` in a room with a guard in
   it means the driver ran and admitted nothing — read `skipped=`.**
4. **IT DOES NOT CRASH, and the log ends `game_exit requested`.** **A CRASH HERE IS THE ARENA, NOT
   THE EYE LOOP.** `292` §1 doubled both pools for exactly this moment and **until now the second
   eye allocated nothing, so the x2 has never actually been spent.** Overflow is silent: the writer
   stops appending with no terminator and `gfx_run_dl` walks off the end into vertex data. **If it
   crashes, that is the finding — re-run with `$env:GETV_GFXPOOL = "0"` removed and the pool
   raised, report the banner's `gfx=`/`vtx=` numbers, and stop.**
5. **`props interpolated 0` and zero `simulation held to`.** The sim did not tick twice.
6. **THE TWO HALVES ARE PIXEL-IDENTICAL — and the script must now REFUSE for the right reason.**
   At zero separation there is nothing to find. **`stereo_disparity.py` prints its `content` line
   FIRST**: if it says `CANNOT ANSWER: THIS IS A BLANK OR FADING FRAME`, the grab was too early and
   **that is not a pass** — take another. The pass is
   `CANNOT ANSWER — the two halves match no better shifted than unshifted` **on a frame whose
   texture energy cleared 0.15.** (`295`'s S2 could not tell those two apart. Now it can.)

**►► AND THE COMPARISON THAT IS THE POINT: put R1's picture beside R2's.** If they look the same,
ARM 3 did nothing and the census in item 3 is where to look first.

---

## §7 — R3. **THE PAIRING GUARD WITH ARM 3 ON — AND ITS ZERO NOW MEANS SOMETHING ELSE.**

Same block as §6 with `$env:GETV_STEREO_PAIRGUARD = "600"`.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
$env:GETV_SLOTFREE              = "1"
$env:GETV_VSYNC                 = "1"
$env:GETV_FPS                   = "panel"
$env:GETV_SIMHZ                 = "query"
$env:GETV_SIMDIV                = "1"
$env:GETV_WIDESCREEN            = "0"
$env:GETV_ROOMSCISSOR           = "1"
$env:GETV_WINDOW                = "2560x1369"
$env:GETV_STAGE                 = "29"
$env:GETV_DIFFICULTY            = "0"
$env:GETV_STEREO                = "1"
$env:GETV_STEREO_OFFSET         = "0"
$env:GETV_STEREO_MODE           = "1"
$env:GETV_STEREO_VIEWRESTORE    = "1"
$env:GETV_STEREO_PAIRGUARD      = "600"
$env:GETV_STEREO_REBUILD        = "1"
$env:GETV_STEREO_REBUILD_REPORT = "600"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_297_R3_guard_rebuild.log 2>&1
Select-String -Path run_297_R3_guard_rebuild.log -Pattern 'pairguard\] SUMMARY|pairguard\] MISMATCH|rebuild\] SUMMARY|game_exit requested'
```

**GATE R3: `checks > 0` AND `mismatch = 0` in every window.**

**►► AND READ THE NEXT SENTENCE BEFORE CELEBRATING IT.** With ARM 3 on, the arena's owner is the
LAST eye by construction, so **this zero is not evidence that ARM 1 works — it is evidence that the
fault can no longer occur.** That is why ARM 2 had to be worn on a build without ARM 3 (`295` §5),
and it is already done: `295` §10. **A non-zero `mismatch` here would be the interesting result** —
it would mean something is reading a pair the rebuild did not reinstall, and that is a new class.

---

## §8 — R4. **S3, THE SEPARATION GATE. ONLY IF R2 PASSED.**

**S3 HAS STILL NEVER RUN.** Use **`RUN-SHEET-295` §10.2 exactly as written**, adding these two lines
to its block:

```powershell
$env:GETV_STEREO_REBUILD        = "1"
$env:GETV_STEREO_REBUILD_REPORT = "600"
```

**and changing `$env:GETV_DLGRAB_AT` from `900` to `5400`** — frame 900 is inside the level-load
fade at `panel` on this display, which is what made `295`'s S2 gate unreadable.

**Its gates are unchanged**, plus one this sheet adds: **the 1/D law is measured on a frame where
the characters and props are present in both eyes.** A disparity measured on an eye with no world in
it is a number about nothing.

**►► YES, THIS SECTION DELEGATES, AND IT IS THE ONE PLACE THIS SHEET DOES.** `296` §11 defect 1 says
a block assembled from two documents is not a supplied command. **The reason it stands here: R4 must
not be run at all unless R2 passed, and reproducing it would invite running it anyway.** If R2
passes, say so and the block will be spliced in full before R4 is attempted.

---

## §9 — R5. **THE COST. `P5` — AND ARM 3 IS A SECOND FULL MODEL BUILD PER FRAME.**

`297` §7 calls the cost `[INFERRED]` affordable, and `P5` says that is not a claim. Three runs, on
Cradle (STAGE 41), against `272` §5.2's `0.890 ms` mean / `2.504 ms` worst:

| run | knobs | what it measures |
|---|---|---|
| R5a | `GETV_STEREO=1`, `REBUILD=0` | stereo as it was |
| R5b | `GETV_STEREO=1`, `REBUILD=1` | **ARM 3's own cost, and it is the number that matters** |
| R5c | no `GETV_STEREO` | mono baseline |

Use `RUN-SHEET-295` §10.4's block three times with `$env:GETV_STEREO_REBUILD` set to `0`, `1` and
the whole stereo group removed. **R5b − R5a is ARM 3's cost. It does not have to be zero. It has to
be KNOWN.**

---

## §10 — WHAT WOULD FALSIFY ARM 3, STATED BEFORE IT IS RUN (rule `15`)

- **R1's census reads anything other than `chr=0 obj=0`.** The knob does not gate what it claims to.
- **R2's picture is unchanged from R1's.** The driver runs and rebuilds nothing that reaches the
  screen — look at `skipped=` and at whether `bgLevelRender` is even downstream of the call.
- **R2 crashes.** The arena. §6 item 4.
- **R0 shows a changed flinch, a changed colour lerp, or a doubled door SFX.** A guard is in the
  wrong place, and the extraction — not the stereo work — is what is broken.
- **R2 shows characters present but WARPING.** The build ran under a view that is not that eye's:
  look at `geStereoNoteArenaBuild()`'s placement and at whether `gePropsRebuildRenderPass()` is
  really inside the eye loop.
- **R3 reports `mismatch > 0`.** Something reads a pair the rebuild did not reinstall. New class.
