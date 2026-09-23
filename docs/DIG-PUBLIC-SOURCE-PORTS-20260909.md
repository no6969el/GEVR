# DIG — public from-source GoldenEye ports, 2026-09-09 to 2026-09-23

**Status:** DIG ONLY. Nothing copied, nothing applied. No ROM, no patch body landed here.

**Ask:** Which public from-source GoldenEye builds moved in the last two weeks, and which of their fixes are worth checking against GEVR.

**Class:** native compile of the N64 decomp (`n64decomp/007` / `KholdFuzion/goldeneye_src`), same family as GEVR. Xbox-360 static recomp (GoldenEye Recomp and its forks) was set aside. It is a different game binary.

**Upstream decomp:** `n64decomp/007` last push **2026-08-17**. No new decomp facts in this window. The useful commits are in PC ports on top of it. Almost all of them are in [jkdansereau/goldeneye-pc-port](https://github.com/jkdansereau/goldeneye-pc-port) (about 300 commits since 2026-09-09, v0.3.0 on 2026-09-20). Their sky, clip, and `Gfx` layout are their own PC port. Treat every row as a check, not a patch to paste.

## Worth a look on the workshop

### 1. Sky coords are already S10.5 — the extra `* 32` is real

**2026-09-12** `741dfe7` (D227).

Their sky emitter treated `unk20` / `unk24` as texel counts and multiplied by 32 to make S10.5. `skyRender` already stores `worldpos * 0.1f` in RDP S10.5 units. The extra `* 32` overflowed `s16` texture coordinates. One quad then split into two different patterns (the seam), clouds tiled ~32× too often, and cloud scroll ran ~32× too fast. That sky fix stayed closed.

**Water did not.** **2026-09-13** `4806799` (D245) let the same tc-shift run on the water quad. On **Frigate** (`-level_26`) a water-fan vertex spanned about `S=-166..299317` and they tried `kS=4`, `kT=4`. The same day, `53c9a87` reopened it: live playtest still swapped two patterns as the view turned. Sky (same emitter) was fine. **2026-09-16** `7412a98` is a headless probe only. Turning the view flips `kT` 4→3, which a single-frame trace never saw. A fixed-k A/B knob exists and is **not** the default. Do not take D245 as a finished water fix.

**GEVR check:** [#80](https://github.com/no6969el/GEVR/issues/80) is the Frigate water / horizon seam. If our sky emitter still does `(S - fold) * 32`, D227 is the same unit error. The water half is still open upstream; their leftover clue is that the shift amount changes while you turn.

### 2. Large triangles vanish next to the camera

**2026-09-12** `650ac57` (D233).

`gfx_sp_tri1` trivial-reject (`clip_rej` AND of three vertices) trusts outcodes that are only valid when `w > 0`. A vertex behind the camera flips the test. The whole triangle is dropped. OpenGL would have drawn the visible part. Props in the same room still draw, because they are small. What disappears is a large wall, ceiling, or doorway polygon, replaced by sky fill. Their backface cull already special-cases `w < 0`. The reject above it did not.

**Fix they shipped:** if any vertex has `w < 0`, skip the trivial reject and let the GPU clip.

**GEVR check:** [#79](https://github.com/no6969el/GEVR/issues/79) invisible Frigate doors (still solid, still openable) was dug as a prop-admit / `CULL_BEHIND` drop, not as this clip test. Still worth one read of our `gfx_sp_tri1` reject. If doors fail the admit before a triangle is built, D233 is not that bug.

### 3. Bullet tests miss whole wall batches

**2026-09-18** `276d012` (D312 / D313), `src/game/bg.c` `bgBuildRoomVtxBounds`.

On N64, `dma.par` is the `G_VTX` params byte. Their PC `Gfx_le` packs `w0 = (cmd<<24)|(par<<16)|len`, so `dma.par` is 24 bits and `(dma.par >> 4) & 0xf` reads the length nibble. A normal 16-vertex batch becomes **1** vertex. The batch AABB shrinks to a point, `bgTestBulletHitBackground` skips it, and shots pass through those walls with no impact.

**Fix they shipped:** `numvertices = (((u32)words.w0 >> 20) & 0xf) + 1` under `PORT` only.

**GEVR check:** only if our display-list word matches that `Gfx_le` pack. If `dma.par` is still the params byte, do not take this line. Symptom if we have it: some walls take no bullet marks while others do.

### 4. Wide FOV culls the screen edge and fades guards early

**2026-09-13** `7c48f66` (D222 / D218).

`currentPlayerSetCameraScale()` built frustum-cull normals and the fog/LOD fade (`c_scalelod` / `c_lodscalez`) from the nominal `fovy`. The widened FOV used for the real projection never reached those planes. At a wide field, geometry at the edge of the lens drops, and the fog/far clip shows up too soon. A follow-up in the same commit: `c_lodscalez` is also what `propobj.c` uses to fade characters, so widening it alone made guards fade sooner. They divide that read by the draw-distance multiplier so the two stay in step.

**GEVR check:** an HMD field is wider than the N64 `fovy` those planes were built for. If our cull planes and guard fade still use the unwidened `fovy`, this is the same split. Their menu knobs (`Video.FovScale`, draw distance) are flat-screen UI. The part to read is which `fovy` feeds `currentPlayerSetCameraScale`.

### 5. 64-bit scheduler stuck the game at 30

**2026-09-13** `52477b4` (D248).

`osScAddClient()` stores “every retrace vs every other” in the next client’s `.next`. `__scHandleRetrace` read it back at a hardcoded 8-byte offset, which is correct only when `OSScClient` is 8 bytes (32-bit pointers). On their 64-bit build the struct is 16 bytes, so the read landed inside the gfx client’s own queue pointer (always non-NULL). The gfx client was forced onto the audio client’s 30 Hz path. The VI pacemaker itself was still ticking at 60. Overlay: 30 FPS before, 60 after, same scene. Fix: index `client[1].next` instead of the byte offset.

**GEVR check:** if our scheduler still uses that 8-byte offset, the HMD can be asking for a full rate while the game client is halved. This is a frame-rate bug, not a render-cost bug.

### 6. Terminal destroy crash is a 32-bit pointer pun

**2026-09-15** `7ef0395` (D255), `src/game/vtxstore.c` `vtxstore_fix_refs`.

An active object’s `Model*` was read through `((ChrRecord*)prop->chr)->chrflags`. On N64, `CHRFLAG` and a pointer are both 4 bytes, so the pun is the pointer. On 64-bit, the enum read keeps 4 bytes and zero-extends, dropping the high half. A NULL crash is what you get when those low 32 bits happen to be zero. The model was never missing. Fix: read `ObjectRecord.model` (same union, pointer-width type) at both sites. They held Facility terminal destruction and Caverns radio terminals with no crash.

**GEVR check:** only if that function still puns through `chrflags`. Symptom: a crash when a terminal or similar object is destroyed, not a missing model.

## Smaller checks, same port

| Commit | Date | What it fixed | When it applies to us |
|---|---|---|---|
| `a088bb5` D195 | 2026-09-13 | `G_TEXTURE_GEN` envmap UVs were stripped to fix the Rareware logo. Gold, chrome, and Control glass sampled one dark texel and read black. Restored, gated on `G_TEXTURE_GEN`, so the logo stays alone. | Only if our vertex path still skips envmap UVs. |
| `9b0accc` D229 | 2026-09-13 | Water image is ZLIB+CI8. Their fast3d read index bytes as RGBA16, so Frigate water was green and pulsed. An RGBA/16b tile over a CI slot now goes through the CI8 palette path. | Only if our water importer has that format disagreement. |
| `50d73c5` D217 | 2026-09-11 | Texpool bases not 8-aligned, so CI palettes sat 4 bytes early (green PP7 / watch). `texInitPool` rounds the base up to 8. | Weapon or watch tiles the wrong solid colour. |
| `dac4ae7` D228 | 2026-09-13 | IA16 palette in `palette_to_rgba32` swapped intensity and alpha (white AK-47 patches). Direct IA16 decode in the same file was already correct. | White patches on guns after D217-class green is gone. |
| `0de99b4` D284 | 2026-09-15 | `dsll32` / `dsrl32` in `random.c` were 32-bit shifts. Real MIPS64 shifts the full register by `n+32`. The stream was stable and wrong from the first draw. | Only if our `random.c` helpers still mask to 32 bits. Changes loot and AI variance. |
| `199182d` D77 | 2026-09-11 | `sub_GAME_7F0C0BF0` in `mp_music.c` calls `get_mTrack2Vol()` and does not return it. N64 left the value in `$v0`. A PC `-O2` build silences in-level music. Menu music never calls it. | Level music silent, front-end music fine. |
| `70bc9d6` D250 | 2026-09-13 | `getenv` on a hot path (including Dam) was the fps drop. Cache it. | Any `GETV_` read inside a per-frame or per-vertex loop. |
| `532092c` D266 / D271 | 2026-09-15 | IA4 decode was I3:A1 (a Perfect Dark assumption); GE is I2:A2. Portal near-plane `lim` of `1e5` forced out-of-range bounds to full screen and drew rooms the N64 culls; they widened it to `1e38`. | IA4 edges look wrong, or rooms draw that should be culled. Not the Frigate door drop. |

## Seen, not a GEVR engine fix

| Port | In the window | Why it stays out |
|---|---|---|
| [mscrnt/Sightline](https://github.com/mscrnt/Sightline) | **2026-09-23** `ee76545` | Dam reservoir HD tile is texture id `05e7`, not `0123` (`0123` is the downstream face). That is their texture-pack map, not the decomp water drawer. Our [#30](https://github.com/no6969el/GEVR/issues/30) read says Dam `IsWater=0`. Other commits in the window are docs, CI, and the public-mirror notes. |
| same | **2026-09-22** | Tick-side lift notes. Docs, no portable code change. |
| [jkdansereau/goldeneye-pc-port](https://github.com/jkdansereau/goldeneye-pc-port) | **2026-09-18** D310 `0c70085` | `AI_PRINT` records sized as 1 byte. Fixes a spin and Caverns guards who stand still. Same PC-stride family as the #84 weapon-prop misread, not the walk-vs-run leftover. |
| same | **2026-09-20** D321 `75e5902` | Facility gas-tank chain is faithful to N64 (chr 254, ~3.5 s). A map, not a fix. |
| same | **2026-09-15** `e0167c8` | They adopted some GEVR triage notes into their docs. Nothing to take back. |
| [chrissotraidis/goldenpad](https://github.com/chrissotraidis/goldenpad) | **2026-09-19** | Apple performance counters and GitHub crash reports. No OpenXR or sky/door change. |
| [Joshua-1248/GoldenEye-007-Plus](https://github.com/Joshua-1248/GoldenEye-007-Plus) | **2026-09-12** | First upload (`b33356f`, `c5fbbb1`) plus a README edit. No later fix commits. Last push on the repo is that README. |

## No movement

`n64decomp/007` did not move. `KholdFuzion/goldeneye_src`, `SegfaultEvan/goldeneye-native`, and `Gilleece/goldeneye-omniport` did not answer on GitHub from this session (404). `kylebrussell/goldeneye-3ds` last moved **2026-09-06**, outside the window.

## What to open first when the workshop is up

1. Sky emitter: is there still a `* 32` on coords that are already S10.5 (D227). Leave the water shift alone until that read is done; upstream reopened it.
2. `gfx_sp_tri1` reject when any `w < 0` (D233), after the existing #79 admit path.
3. Which `fovy` feeds the cull planes and guard fade (D222). This is the VR-shaped one.
4. Scheduler retrace flag: struct index vs an 8-byte offset (D248), if the client looks stuck at half rate.
5. `vtxstore_fix_refs` model pointer width (D255), if terminal destruction crashes.
6. `bgBuildRoomVtxBounds` vertex count (D312), only after confirming our `G_VTX` word layout.
