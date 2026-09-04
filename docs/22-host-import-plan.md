# Plan — the first host import: giving the host the gate

**2026-08-22.** `21-host-gate.md` left one thing open: `config.inLevel = true` is
hardcoded in the host, so the per-eye frustum override cannot tell gameplay from
the Nintendo logo. Clearing an environment variable is a workaround. Step 3d
needs the override on permanently, so the gate has to become real first.

## Prior-art check

**Is there a better mechanism than hand-assigned addresses in `syms.ld`?**
`05-going-forward.md` describes that pattern, and Zelda64Recomp's mod system uses
a `RECOMP_IMPORT` macro, which would be cleaner if this fork had it.

It does not. `patches/patches.h` defines only `RECOMP_EXPORT` (a section
attribute), and there is no import macro anywhere in the tree. Zelda64Recomp's own
development guide confirms the dummy-address approach is the documented standard:
functions are declared at reserved addresses from `0x8F000000` in `patches/syms.ld`
and resolved by the framework. **Nothing newer to adopt.**

## Three corrections to `05`'s description of the pattern

`05` says: "declare it in `patches.h`, give it an address in `patches/syms.ld`,
and implement it in `src/game/recomp_api.cpp` following the pointer-out-arg
pattern of `recomp_get_gyro_deltas`."

1. **`recomp_get_gyro_deltas` does not exist in this fork.** It is Zelda64Recomp's.
   The analogues here are `recomp_get_aspect_ratio` (`recomp_api.cpp:128`) for a
   value returned to patch space, and `yield_self_1ms`
   (`ultramodern/src/scheduling.cpp:45`) for a plain call. Following a function
   that is not in the tree is exactly the trap `05` itself warns about two
   sections earlier, about `geVrBuildProjectionF`.

2. **`DECLARE_FUNC` is the idiomatic declaration, not a bare prototype.**
   `patches/patch_helpers.h` defines it to expand to the MIPS prototype when
   building the patch and to the `(uint8_t* rdram, recomp_context* ctx)` host
   signature otherwise — one declaration serving both sides.
   `patches/misc_funcs.h:6` declares `yield_self_1ms` this way.

3. **Resolution is at compile time, not runtime.** N64Recomp emits a direct C
   call — `RecompiledPatches/patches.c:116` literally reads
   `yield_self_1ms(rdram, ctx);`. `librecomp` also has a runtime
   `register_manual_patch_symbols` path, but nothing in this tree calls it.

Correction 3 is the good news. **A host import with no host-side definition is a
link error, not a silent no-op.** That is the opposite of the situation on the
patch side, where `--unresolved-symbols=ignore-all` turns a missing game symbol
into a call into nothing — the failure mode flagged as risk 1 in `18`. This
direction cannot fail quietly.

## The design

**Direction: patch to host.** One value, once per frame.

```c
/* patches/misc_funcs.h */
DECLARE_FUNC(void, recomp_ge_vr_set_world_camera, s32 active);
```

```
/* patches/syms.ld — next free slot, confirmed: highest in use is
   osMotorInit_recomp = 0x8F000110 */
recomp_ge_vr_set_world_camera = 0x8F000114;
```

```cpp
/* src/game/recomp_api.cpp */
extern "C" void recomp_ge_vr_set_world_camera(uint8_t* rdram, recomp_context* ctx) {
    ge_vr::set_world_camera(_arg<0, s32>(rdram, ctx) != 0);
}
```

The patch calls it from `viSetFovY`, which is where `geVrWorldCamera()` is already
computed and which runs every frame in every context — gameplay, front end,
cutscenes, demo. The host stores it and uses it for `config.inLevel`.

**Why one boolean and not a struct.** The temptation is to send the stage number
and camera mode too, for future use. Resisted: the host has one question, and
extra fields invite guessing at what they mean later. Phase 2 needs traffic in the
other direction — per-eye parameters from `xrLocateViews` into the patch — and
that is a separate import with its own shape.

**Ordering, which is better than feared.** Within a frame the game builds its
display list (calling `viSetFovY`), then `update_screen` runs and snapshots the
config, then RT64 renders. The value is therefore fresh for the frame it governs,
with no skew. State lives as an `std::atomic<bool>` anyway — cheap, and it stops
the question being asked again if threading changes.

## Build

Adding a host import is **not** a new `RECOMP_PATCH` name, so
`tools_weaken_patched.py` does not need re-running. CMake's `PatchesBin` chain
rebuilds `patches.elf` and re-runs N64Recomp automatically. The one-liner is
enough.

## Gate

1. **It links.** Per correction 3, a missing or misspelled host definition fails
   the link. Building at all is most of the test.
2. **`GE_VR_FRUSTUM=1` and the Nintendo logo is centred.** This is the whole
   point: the configuration that broke everything in `21` should now be
   harmless outside gameplay.
3. **`GE_VR_FRUSTUM=1` and gameplay still shows the asymmetric eye frustum.** The
   gate must not be so tight that it switches the feature off entirely.
4. Intro walk, briefing menus and the crosshair all correct with the override on.

Gate 2 versus gate 3 is the real test: one confirms the gate closes, the other
confirms it opens. A gate that is always false passes 2 and fails 3, and would
otherwise look like success.

## After this

Step 3d — two render targets. `11-rt64-stereo-seams.md` established the mechanism
already exists: `RenderTargetManager::setOverride`, and a `renderThreadLoop` that
already renders one workload into several targets at display rate.

---

# Implemented, 2026-08-22 — not yet built

Five files, backups `.bak3d` on the three that existed already.

| File | Change |
|---|---|
| `patches/syms.ld` | `recomp_ge_vr_set_world_camera = 0x8F000114;` |
| `patches/misc_funcs.h` | `DECLARE_FUNC(void, recomp_ge_vr_set_world_camera, s32 active);` |
| `patches/ge_vr_bindtest.c` | the call, from `viSetFovY` |
| `include/ge_vr_host.h` | **NEW.** `ge_vr::set_world_camera()` / `world_camera()` |
| `src/game/recomp_api.cpp` | the host implementation |
| `src/main/rt64_render_context.cpp` | the atomic, and `config.inLevel = ge_vr::world_camera()` |

`ge_vr_host.h` is written from scratch and is ours, so its home is the MIT repo,
at `repo\host\`. It drops into the recomp tree's `include\` to build. Everything
else here is a diff against the GPL-adjacent host tree and stays in
`local-only\thirdparty-diffs\recomp-host\`.

## One call-site decision worth recording

The call is **unconditional and every frame**, placed before the gate rather than
inside it:

```c
recomp_ge_vr_set_world_camera(geVrWorldCamera());

if (geVrWorldCamera()) {
    fovy *= GE_VR_CULL_FOVY_SCALE;
    ...
}
```

The obvious alternative — only telling the host when the answer is true — fails
in exactly the way `21` describes. **The host needs the FALSE more than the
TRUE.** False is what switches the eye frustum off for the Nintendo logo and the
intro walk. A host that only ever hears "yes" latches on at the first level load
and never releases.

`viSetFovY` runs every frame in every context, including the front end, so the
value cannot go stale.

## Build

The one-liner. No new `RECOMP_PATCH` name, so no `tools_weaken_patched.py`.

```powershell
$env:PATH = "C:\Program Files\LLVM\bin;C:\Program Files\CMake\bin;C:\Users\<USER>\AppData\Local\Microsoft\WinGet\Links;" + $env:PATH
cd C:\Users\<USER>\Desktop\GoldenEye64Recomp
cmake --build build --target GoldenRecomp --config Release --parallel
```

## Gate, with the environment variable deliberately left ON

```powershell
$env:GE_VR_FRUSTUM="1" ; $env:GE_VR_EYE="0"
build\Release\GoldenRecomp.exe
```

Startup should print `[gevr] host: frustum=1 ... (enabled=1)`.

| Check | Pass |
|---|---|
| It links | A missing or misspelled host definition is a link error here, not a silent no-op |
| Nintendo logo | **Centred**, with `frustum=1` — the configuration that broke it in `21` |
| Intro walk | Bond centred, no clipping |
| Briefing / mission menus | Centred, no black border, crosshair accurate |
| **Gameplay** | **Still shows the asymmetric eye frustum** — centre of projection pushed to one side |

The last row is the one that can be lost by being too careful. A gate stuck at
false passes every other check and looks like success.

---

## Result — passes, 2026-08-22

Nintendo logo, intro walk and menus all correct **with `GE_VR_FRUSTUM=1`**. The
configuration that produced four rounds of wrong diagnosis in `21` is now
harmless outside gameplay, and the first host import works.

### The crosshair being off in gameplay is expected, and quantifiable

Reported alongside: with the frustum on, in-game aim is off.

**This is the hybrid design showing through, not a regression.** The patch sets a
*symmetric* 106 degree FOV, and everything the game derives — `c_scalex`,
`c_scaley`, the crosshair, hit-testing — is consistent with that. RT64 then
replaces the projection with an *asymmetric* eye frustum, after the game has
finished thinking. The game has no way to know its centre of projection moved.

The size of the error is predictable rather than mysterious. For the left eye:

```
ox = (tanRight + tanLeft) / (tanRight - tanLeft)
   = (1.0358 - 1.3760) / (1.0358 + 1.3760)
   = -0.141
```

**About 7% of the screen width**, and it should flip to the other side with
`GE_VR_EYE=1`. If the observed offset is roughly that and mirrors with the eye,
the maths is behaving; if it is much larger or does not mirror, something else is
wrong and this explanation does not cover it.

It is also not worth fixing where it appears. A screen-centre crosshair is the
wrong instrument in VR regardless — Phase 3 separates head look from weapon aim,
and aiming stops being "where the middle of the screen points". Correcting the
2D crosshair for an eye frustum would be work thrown away, and it is only visible
at all because one eye is being previewed on a flat monitor.

**With `GE_VR_FRUSTUM=0`, which is the default, aim is exact** — confirmed in
`21`, and it is what says the patch's own FOV widening keeps rendering and
hit-testing in agreement.
