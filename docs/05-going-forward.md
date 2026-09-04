# Going forward

## Where the VR work actually stands

Phase 0 is done and passed. **Phase 1 step 1 is now written, compiled and linked
into a fresh `GoldenRecomp.exe` (2026-08-22) but has not yet been run.** Nothing
after it has started. Everything built so far still runs flat on a monitor;
there is no stereo, no OpenXR, no head tracking.

The interpolation work was not in the original plan. It became necessary because
flat play tolerates 30 Hz and a headset does not — a stepped image in VR is not a
cosmetic problem, it is a nausea problem. That work is now far enough along that
it no longer blocks anything.

## CORRECTION to the previous version of this doc — read this, it is a trap

The earlier text said `geVrBuildProjectionF` in `src/ge_vr_bridge.cpp` "already
exists", with no path qualifier. **It does exist — in the other repo.**
`geVrBuildProjectionF` and the original `GE_VR_MIN_ZNEAR_UNITS` live in
`no6969el/goldeneye-native`, the MIT design repo, which is **not checked out on
the rig**; see `08-where-everything-comes-from.md` and the bundle in
`goldeneye-native/`.

Two repos, one sentence, no path qualifier. A session reading that line would
search `C:\Users\pdbar\Desktop\GoldenEye64Recomp` for a file that is not there and
conclude it had been lost. Always name the repo.

The projection maths for the recomp tree has now been written separately — in the
patch, not in a host bridge, and for the reason given below. Patch space cannot
see the host repo, so `ge_vr_bindtest.c` defines its own copy of the znear
constant deliberately. The two are expected to agree; if they ever diverge,
`goldeneye-native` is the spec and the patch is the implementation.

## Phase 1 — stereo rendering

Render the world twice per frame with per-eye projections, into two targets.

The hook is proven and the site is known: `viSetupCurrentPlayerView` (`fr.c:716`)
is the **single** caller of both projection setters. One chokepoint governs the
entire world projection.

### Step 1 — per-eye projection maths — DONE (built, not yet run)

Lives in `patches/ge_vr_bindtest.c`, which is now the real hook rather than a
test. Previous version backed up as `ge_vr_bindtest.c.bak`. The copy in this
folder under `patches/` is byte-identical to what is live in the tree.

It replaces the frustum-describing parts of the game's symmetric matrix with a
per-eye asymmetric one, in both the fixed-point `Mtx` (what the RSP transforms
with) and the float `Mtxf` (what the CPU culls with). Both must agree or geometry
is culled against a frustum it is not drawn in.

Three things worth knowing before touching it:

- **The maths lives on the MIPS side, not in a host bridge.** The setters run in
  the game's address space; reaching out to native code once per frame to fetch
  four floats buys nothing and adds a call across the recomp boundary. What the
  host will eventually own is the *numbers*, not the matrix build.
- **Tangents, never angles.** libm is not dependably available in patch space.
  OpenXR hands out `XrFovf` in radians; the host bridge calls `tanf` natively and
  passes tangents across. Nothing in the patch needs trig. Sign convention
  follows `XrFovf`: left and down negative, right and up positive.
- **The skew terms go in row 2, not column 2.** `guPerspectiveF` is row-vector
  convention. Transposing them produces a sheared world that looks *almost*
  right, which is the worst kind of wrong.

`GE_VR_MIN_ZNEAR_UNITS` (10) is enforced there. `n` cancels out of the x/y scale
terms, so clamping znear costs no field of view — it only spends depth precision
better than the game's per-level 2..30 does.

**The seam for Phase 2** is the single function `geVrGetEyeParams()`. It returns
the stand-in Quest-3 constants today. Replacing it with a host import is the only
change that file should need: declare it in `patches.h`, give it an address in
`patches/syms.ld` (**next free slot is `0x8F000114`**), and implement it in
`src/game/recomp_api.cpp` following the pointer-out-arg pattern of
`recomp_get_gyro_deltas`.

**To test without a headset:** run a level. Expect a slightly wider view with the
centre of projection pushed off to one side; flip `g_geVrEye` (0 left, 1 right)
and it should move the other way by the same amount. Straight edges must stay
straight. The file's closing comment lists each wrong picture and what it means.
`GE_VR_PREVIEW_FIT_ASPECT` is on by default so the monitor image is not
horizontally stretched; set it to 0 to see the raw eye frustum.

### Step 2 — IPD on the view matrix — NOT STARTED

The projection hook never sees the view matrix, so the eye offset has to attach
elsewhere. Invisible with one eye on a monitor, so it was correctly skipped in
step 1, but it is required before anything reaches a headset.

### Step 3 — two render targets — NOT STARTED, NOT DESIGNED

Two render targets in RT64, and a way to ask the game to submit its display list
twice. **This is the hard part and it remains the genuinely unsolved piece of
Phase 1.** Decide where the eye split lives: replaying the display list per eye
is cheaper to build; running the game's render path twice is more correct.

**Known obstacle already discovered:** the front end and the world share
`viSetupCurrentPlayerView`, so any per-eye change hits menus too. The patch
already gates on `g_StageNum != LEVELID_NONE && != LEVELID_TITLE` via
`geVrInLevel()`; reuse that.

## Phase 2 — OpenXR frame loop

Session, swapchains, `xrWaitFrame` / `xrBeginFrame` / `xrEndFrame`, and pose
prediction.

**Reconnaissance is DONE — read `09-openxr-probe.md` before writing any XR code.**
A standalone probe created a real D3D12 session against the rig's headset and
came back with the actual numbers: SteamVR/OpenXR 2.16.7 driving a **Pimax**, not
a Quest 3; 90 Hz only; 4140 x 3292 recommended per eye; IPD 63.5 mm; per-eye FOV
100 x 91 degrees with a 54/46 inner-outer split; **cant 0.000 degrees, so the
panels are parallel** and step 2 stays "IPD", not "IPD and cant". The measured
tangents are now in `ge_vr_bindtest.c`, replacing Quest 3 guesses that were 14
degrees too tall vertically.

The probe also found the trap that will bite the real integration: the Khronos
1.1.x headers' `XR_CURRENT_API_VERSION` is rejected by SteamVR with an error the
loader reports only as "chained CreateInstance call failed". Ask for
`XR_API_VERSION_1_0`.

The game's main loop is driven from `workbench_theboy.c`; the frame pacing there
(`waitForNextFrame2`, `InitFrameRateControl`) is where the XR loop has to
interlock. Expect this to be fiddly — the game was never designed to have its
frame timing owned by something else.

## Phase 3 — decoupled aim, and the UI

- Head look and weapon aim must separate. GoldenEye couples them.
- The watch becomes a world-space panel rather than a screen overlay. This is why
  flat-mode watch polish is deliberately skipped — it would be thrown away.
- The HUD generally wants re-siting into the world.

## Phase 4 — comfort

Snap turn, vignette, seated recentre, adjustable scale. The per-level visibility
scale (`room_data_float2`) matters here: the game's world units are not consistent
between levels, so "one metre" is level-dependent.

## Open engineering items, not phase-gated

| Item | Size | Notes |
|---|---|---|
| First-person weapon interpolation | Medium | 112-line function. Always on screen — highest-value polish left. |
| ~~Bullet impact ids~~ | **DONE** | Interpolation slice 6, 2026-08-22. Built, unverified. |
| Scorch mark ids | Small | `explosionRenderScorchBuffer`, 48 lines. Now a small job — copy slice 6's id-band pattern with a `GE_IDBAND_SCORCH`. |
| Glass / particles / blood ids | Small each | 43 / 41 / 10 lines. Same pattern. |
| **Push `goldeneye-native`** | **Tiny, urgent** | The bundle in `goldeneye-native/` is the only copy of 1,116 insertions. It was written in a destroyed cloud container. See `08`. |
| Display list overflow | Unknown | Each tag costs 2 Gfx slots; props cost 4. Untested on Surface/Streets. A wider stereo FOV pulls MORE geometry into view, so step 1 makes this likelier, not less likely. |
| SDL2 version skew | Latent | RT64 links 2.26.3, FetchContent ships 2.30.3's DLL. Suspect on odd input/audio behaviour. |
| `LNK4098 LIBCMT conflict` | Latent | Benign so far. First suspect if the exe misbehaves at startup. |
| Splitting `ge_vr` into its own repo | Deferred | Was always "once the hook model is proven". It now is — so this is genuinely actionable. When it happens, rename `ge_vr_bindtest.c`; the name is only kept for continuity with these diffs. |

## Decisions already made — do not relitigate without reason

- **Windows native, PCVR first.** Not standalone Android. A standalone port would
  compete with existing Quest GoldenEye ports on their turf and lose; PCVR plays
  to RT64's strengths. The decision stands; only the headset named in it has
  changed — the rig runs a **Pimax on SteamVR**, measured 2026-08-22 (`09`).
  Earlier docs say "Quest 3 over Link"; that remains viable, it is just not what
  is plugged in. Do not switch the active OpenXR runtime to Oculus.
- **cblock85's fork as the base**, not a fresh N64Recomp setup.
- **The recomp host stays external and GPL-3.0.** Never vendored into the MIT repo.
- **The watch is not fixed for flat mode.** Phase 3 replaces it.

## The single most useful next step

**Run the build and look at it.** Two changes are compiled and linked and neither
has put a pixel on screen: the per-eye frustum and interpolation slice 6.
Everything downstream assumes the frustum is right.

Then push the `goldeneye-native` bundle, because it is the only copy.

After that, Phase 1 step 3 — the two-render-target problem — is the next real
piece of design work, and it is the one with no answer yet.
