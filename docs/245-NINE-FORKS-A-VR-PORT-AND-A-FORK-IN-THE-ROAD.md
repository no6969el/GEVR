# 245 — NINE FORKS, A REAL VR PORT, AND A FORK IN THE ROAD

**2026-08-29. Docs run to `245`. NEXT DOC = `246`.**

> # ►►►►►► **TWO INDEPENDENT PORTS OF THIS DECOMP KEEP THE GAME'S POINTERS
> # 32-BIT ON PURPOSE. EVERY BUG THIS SESSION FOUGHT IS THE TAX ON NOT DOING
> # THAT.** ◄◄◄◄◄◄
>
> **AND ONE OF THEM IS A VR PORT — 21,524 lines, OpenXR, on the same decomp,
> reaching `g_CurrentPlayer->vv_theta`: the game camera `194` said never learns
> about the head.**

---

## §1 — THE CENSUS. SIX OF NINE ARE EMPTY.

`[MEASURED]` all nine cloned and their branches listed:

| repo | default branch | verdict |
|---|---|---|
| `w0lfheart/007-Performance-Recomp` | `master` only, at `c435646` | **unmodified fork** |
| `ricjpg/ge007` | `master`, one CI edit | **effectively a fork** |
| `cmcasanova/007blargg` | `master` only, `c435646` | **unmodified fork** |
| `RyanTM899213/LaserBeam_Vita` | `master` only, `c435646` | **unmodified fork** |
| `jansenmccloud/GE007N64` | + `hack_N64FishingRod_controlStyle` | a controller hack |
| `AXDOOMER/ge007-digital-controls` | + `digital-controls` | digital control mod, real commits |
| `jakzo/goldeneye-practice-rom` | own tree | speedrun practice ROM; **`ares`, `libdragon`, `tests/`, `test_rom.sh`** |
| **`mattymattmattmatt/007-VR`** | **+ `claude/goldeneye-007-vr-port-06libw`** | ► **A REAL VR PORT.** §2 |
| **`jeffory/007portable`** | **+ `pc-port`** | ► **A REAL PC PORT.** §3 |

> **`c435646 "james bond will return."` IS THE DECOMP'S OWN HEAD COMMIT.** Six
> repos sit on it untouched. **A fork with a promising NAME is not a project** —
> `007-VR`'s master has no VR code in it at all; the work is on a branch, and
> **checking `git ls-remote --heads` before judging a repo cost one command and
> would have written off the single most valuable find here.**

---

## §2 — `mattymattmattmatt/007-VR`. AN INDEPENDENT VR PORT ON OUR DECOMP.

`[MEASURED]` branch `claude/goldeneye-007-vr-port-06libw`, **117 files, 21,524
insertions** over the fork point. A complete `vr/` layer:

| file | lines | what |
|---|---|---|
| `vr/src/gevr_xr.c` | **1383** | the OpenXR runtime |
| `vr/src/gevr_gl.c` | 591 | stereo GL |
| `vr/src/gevr_controls.c` | 471 | hands, aim, locomotion |
| `vr/shim/gevr_shim.c` | 343 | **the bridge into the game** |
| `vr/src/gevr_config.c` + `config/gevr.ini` | 272 + 86 | a tuned config file |
| `vr/src/gevr_math.c` + header | 199 + 238 | quaternion/matrix maths |
| `vr/src/gevr_camera.c` | 143 | **the camera** |
| **`vr/tests/test_controls.c`** | **824** | **UNIT TESTS FOR THE CONTROL LAYER** |
| `vr/tools/gevr_calibrate.c` | 308 | a calibration tool |

**Its prefix is `gevr_`. Ours is `ge_vr_`. Convergent, not shared.**

### §2.1 — IT REACHES THE GAME CAMERA. THAT IS `194`'s ROOT CAUSE.

`[READ]` `vr/shim/gevr_shim.c` includes **`game/bondview.h`** and both reads and
drives the player's own yaw:
```c
game->yaw    = gevr_engine_yaw_to_vr(g_CurrentPlayer->vv_theta);
params.yaw   = gevr_engine_yaw_to_vr(g_CurrentPlayer->vv_theta);
gevr_camera_recenter(&g_vr.cam, &g_vr.input.head, g_vr.controls.body_yaw);
```

> **`194`: *"The head rotation reaches only the EYE VIEW MATRIX... THE GAME CAMERA
> NEVER LEARNS ABOUT THE HEAD."* `224` §3.1 wanted exactly this moved into
> `bondview.c` and it was never built. THEY BUILT IT, AND `vv_theta` IS THE
> SYMBOL.**

`[READ]` their design decision, in their own comment: **body yaw is kept in
play space and the head's heading is FOLDED INTO IT ON RECENTRE** —
`cam->body_yaw = wrap_pi(body_yaw + quat_yaw_of(head->orientation))` — and
*"the engine's yaw is deliberately not used"* for play-space heading. **That is a
composition question this corpus spent `197`-`204` on from the other side.**

---

## §3 — `jeffory/007portable`, `pc-port`. ITS COMMIT LOG IS OUR BUG LIST.

`[MEASURED]` 585 files, 25,976 insertions. **Three commit subjects, verbatim:**

- **`029ec75 64-bit: keep the game's pointers under 2GB, and stop the cursor climbing`**
- **`11bf6d4 64-bit: one-shot pools must outlive the stage that allocated them`**
- **`cb865c0 propobj: a pointer out-param declared f32 shot the local next to it`**

### §3.1 — AND ONE OF THEM NAMES OUR FUNCTIONS

`[READ]` `029ec75`'s message:
> *"the game's data model is 32-bit, and a pointer that round-trips through an
> s32 comes back sign-extended once bit 31 is set.*
> *  `modelGetNodeRwData` (cast screen)  node = `0xffffffff800b0000`*
> *  `makeonebody -> modelAttachHead`    node = `0xffffffff80060c20`"*

**`makeonebody`. `modelAttachHead`. `modelGetNodeRwData`. The cast screen. The
attract sequence reloading stages forever.** `[READ]` *"x86-64 never saw either:
`MAP_32BIT` handed out the first 2GB, so bit 31 was always clear and every such
round-trip was accidentally lossless."*

**`234`, `241` and `243` were all in that neighbourhood, on x86-64, where the
disease is masked and only its side-effects show.**

### §3.2 — `cb865c0` IS OUR FAULT CLASS, IN OUR FILE

`[READ]`: `chraiGetCollisionBounds(prop, struct rect4f **polygon, s32 *edges,
f32 *, f32 *)` was being called **with four `f32` locals**. The callee writes a
POINTER through the second out-param — *"4 bytes on the N64, where an f32 slot
absorbed it exactly, but 8 bytes on a 64-bit host, so the store ran off the end of
the f32 and into the next local"*, leaving an adjacent `mStan` NULL.

**A pointer stored through a 4-byte slot, silently wrecking the variable beside
it. `243` §2's crash has `rdx = 0x0be1be88_00007ff6` — a pointer with its halves
misplaced — and `fault addr = -1`.** **Not the same bug. Unmistakably the same
disease.**

---

## §4 — ►► THE FORK IN THE ROAD, STATED PLAINLY ◄◄

**The decomp's data model is 32-bit. Its structs hold pointers in `s32` fields and
its code relies on those widths.** Three ports, three answers:

| port | approach | consequence |
|---|---|---|
| **`goldeneye-native` (ours)** | keep 64-bit pointers, **widen and pad each struct as it breaks** | `ge_anim_pad[256]`, `ge_model_pad[320-40]`, a `_Static_assert`, `unk10`/`Model.obj` aliasing, the spark colour at `0x28` vs `0x30`, `unka0` truncation — **and every fault of `234`-`243`** |
| **`007portable`, `007-VR`** | **confine game-visible memory to the low 2GB / an 8 MB arena so game pointers stay 32-bit and lossless** | the class does not arise |
| Perfect Dark's port | build the whole thing i686 | rejected by `007-VR` to keep the OpenXR loader 64-bit |

`[READ]` `007-VR`'s reasoning: *"keeps the renderer, the OpenXR loader and the port
itself 64-bit, and instead places everything the game can see inside the 8 MB
arena... Game pointers then fit in a u32 naturally... If the arena cannot be placed
where it belongs, the port refuses to start rather than corrupt display lists."*
**`osVirtualToPhysical` PANICS instead of truncating.**

> ## **THIS IS NOT A RECOMMENDATION TO SWITCH TONIGHT, AND IT IS NOT A DECISION
> ## THIS DOCUMENT MAKES.**
> **It is the observation that our base chose the approach that generates an
> unbounded stream of these bugs, and that two other ports of the same decomp —
> one of them a VR port — chose one that does not.** **`227` chose the road; this
> is a map of the other lanes on it, and the owner picks.**

---

## §5 — AND A TEST HARNESS, WHICH THIS PROJECT HAS NEVER HAD

**`007-VR`: `ge007-selftest`** — `[READ]` *"builds a display list in the RDRAM
arena, submits it through the SP task interception, and **reads the framebuffer
back**. That last part is what made it useful. **Every bug below left the triangle
and draw-call counters looking perfectly healthy.**"*

> **THAT IS EXACTLY THIS SESSION'S BLIND SPOT.** `231` §1.3 reasoned from
> `tris submitted=520 drawn=520` and was wrong; `236` measured a renderer drawing
> text the game never asked for. **A counter says a draw happened. A framebuffer
> read says what it looked like.**

**`007portable`: `port/tests/run_android.sh`** drives the front end into a mission
over `adb` with no human, and **`run_arm64.sh` plus "both golden sets bit-exact"**
— golden-image regression. **`jakzo`'s practice ROM carries `tests/`,
`test_rom.sh`, `ares` and `libdragon` too.**

**`242` §5 concluded that a change to a shared lifecycle needs a gate that walks
the lifecycle. Three of these repos already automate exactly that.**

## §6 — WHAT IS NOT CLAIMED

- **Nothing here has been built or run.** All `[READ]`, from cloned sources.
- **No claim either port WORKS better than ours.** `007-VR`'s own README records
  what is unfinished; neither was executed here.
- **`[ASSUMED]` the arena approach would have prevented our specific faults.** It
  addresses their CLASS; `241`'s `Model.obj` write was my own logic error and no
  memory layout would have stopped it.
- **`clone-prior-art.ps1` now carries `goldenballoon`, `007-VR` and `007portable`,
  with their branches noted.** The six empty forks are deliberately NOT listed.
