# 28 — step 3f-3 plan: the game's own eyes in the headset

**2026-08-22.** 3f-2 passed: red left, blue right, confirmed in the headset, game
still playable on the monitor (`27`). Every stage between an image and the
compositor is now proven. 3f-3 replaces the flat colour with GoldenEye.

## Prior-art check

- **Upstream `rt64/rt64`**: no stereo, no OpenXR. Nothing to adopt. Re-confirmed.
- **Ours, and this is the important one — `25`'s side-by-side path**
  (`rt64_present_queue.cpp`, ~line 350). It already takes the two eye targets and
  puts both on screen, and it is **validated on a monitor with real parallax**.

That path also carries a warning written from a failure, and it is the single
most useful sentence available to 3f-3:

> Eye 1 must go through the SAME preparation as the main target, not just have
> its texture swapped in. The first attempt skipped `resolveTarget` /
> `downsampleTarget` and kept the main target's `resolutionScale` and
> `downsamplingScale` while substituting eye 1's raw dimensions. The VI shader
> maps `videoResolution` onto `textureResolution`, so a mismatched pair samples a
> small corner of the texture and blows it up — **which presented as the right
> half showing a magnified crop, and read as "stereo is broken" rather than "the
> blit is wrong".**

**So an eye target is not a picture.** It is an input to `VIRenderer` along with
a resolution scale, a downsample multiplier, an MSAA resolve, and a format. Any
3f-3 design that treats `vrEyeOneTarget` as something to copy is repeating a
mistake this project has already made and already documented.

## What the host can actually reach

Read from RT64 rather than assumed:

| Need | Path | Note |
|---|---|---|
| RT64's native command list | `D3D12CommandList::d3d` (`rt64_d3d12.h:150`) | `ID3D12GraphicsCommandList4*`, **already open, already on the present queue** |
| The swap-chain back buffer | `D3D12Framebuffer::colorTargets[0]` -> `D3D12Texture::d3d` (`:134`, `:265`) | `ID3D12Resource*` |
| Window size | `D3D12Framebuffer::width` / `height` | |
| Eye 1's target | `SharedQueueResources::vrEyeOneTarget` | eye 0 is the main colour target, not published separately |

The hook signature already hands us both: `RenderHookDraw(RenderCommandList *,
RenderFramebuffer *)`, called at `rt64_present_queue.cpp:421`, **after**
`viRenderer->render()` has drawn.

## Three designs, and why the cheap one wins this slice

**A. Render each eye through `VIRenderer` into the XR swapchain image.** Wrap the
acquired D3D12 resource as an RT64 framebuffer and let RT64 draw the eye into it
at the headset's own resolution. This is the *correct* end state — full
resolution, no dependence on the window, all the preparation logic reused in the
place it belongs. It is also the largest change, needs RT64-side work, and would
be the first thing in this project to put an externally-owned resource into
RT64's framebuffer abstraction.

**B. Blit the eye targets from the host in raw D3D12.** Requires reimplementing
the VI mapping outside RT64 — which is precisely the thing the `25` comment says
goes wrong, and it would go wrong somewhere with no error message. **Rejected.**

**C. Copy the two halves of the side-by-side framebuffer.** With `GE_VR_SBS=1`
the swap-chain framebuffer *already contains both eyes, fully prepared*, each in
one half. At hook time it is sitting there finished. Two
`CopyTextureRegion` calls with a source box each, into the two acquired XR
swapchain images. No shader, no root signature, no PSO, no format conversion, and
**every line of preparation logic is RT64's already-validated code.**

**3f-3 takes C**, on the same reasoning that shaped 3f-1 and 3f-2: get a picture
using only parts that are already proven, then improve it. A is the follow-up
slice, and this plan is not pretending otherwise — see "What C costs" below.

C also deletes the riskiest machinery in 3f-2. Recording into RT64's own open
command list means **our separate command list, allocator, fence, and the
`waitForGpu` that resets the allocator all go away**, along with the whole class
of "two submissions racing on one queue" problems.

## The sizing decision, and why it is forced

`CopyTextureRegion` does not rescale. Source and destination extents must match.

So the XR swapchains cannot be created at the runtime's recommended 4140x3292
while the source is half a window. **Create each eye's swapchain at
(windowWidth / 2, windowHeight) and let the runtime scale to the panel.**

`09` anticipated exactly this and called the recommended size "a knob, not a
requirement". This is that knob being turned for the first time.

Consequence with teeth: **the window size is not known until RT64 has a swap
chain**, so swapchain creation must move out of `startup()` and become lazy — on
the first hook call that has a framebuffer. If the window is then resized, the
swapchains are wrong and must be recreated. `27` is a standing reminder of what
RT64 does when a swap-chain resize goes wrong.

## Aspect, which is better than it sounds

Each SBS half is squeezed 2:1 horizontally — that is what `25` chose and it is
correct for a monitor. In a headset the runtime maps the image onto the FOV given
in `projView.fov` and does not preserve aspect, so a squeezed image would be
*stretched back out*. The two errors are inverses.

On a 1920x1080 window each half is 960x1080, or 8:9. A true Pimax eye frustum is
100.0 x 91.0 degrees — very nearly square. **They approximately cancel**, which is
why C is worth trying at all rather than being obviously wrong.

`GE_VR_FIT_ASPECT=0` gives the raw eye frustum instead of the undistorted
monitor preview, and is the correct setting for the headset. This slice is where
that stops being a debug flag.

## What C costs, stated plainly so it is not discovered later

1. **Resolution is capped by the window.** 960x1080 per eye against a 4140x3292
   panel. It will look soft. **This is not the bug; do not chase it.**
2. **It couples the headset path to `GE_VR_SBS`**, a flag documented as "monitor
   only, no meaning once the images go to a headset". 3f-3 makes that comment
   temporarily false. Design A un-couples it.
3. **The monitor shows the side-by-side view**, not a normal game view.

All three are removed by A, and none of them prevents the tint test — which is
the only question 3f-3 actually has to answer.

## Staging — two slices

### 3f-3a — the copy, with the tint test

Copy both halves. Then, **before any judgement of the picture**, force a tint:
left eye multiplied toward red, right toward blue, behind `GE_VR_XR_TINT=1`.

**Gate:** left eye reads red-shifted, right eye blue-shifted, and it is the
*game* underneath rather than a flat colour. `10` is unambiguous about why this
comes first:

> A monoscopic image with correct perspective looks *exactly* like working
> stereo — it fuses, it looks like a room, it survives head movement.

Without the tint, "I can see the game and it looks 3D" is worth nothing. A tint
cannot be faked by a single image reaching both eyes.

A flat multiply needs a shader, which C was chosen to avoid — so the tint is done
instead by **copying only one eye's half into both swapchains** on alternate
runs, under `GE_VR_XR_FORCE_EYE=0|1`. If both eyes show the same image and the
scene still looks like a room with depth, the depth is an illusion and the copy
is wrong. That is the same test with no shader.

### 3f-3b — depth, and the sign

Only after 3f-3a passes: is there depth, and is it the right way round?

**This is where `GE_VR_EYE_SIGN` gets settled by observation.** `25` closed 3e
with the sign resting on argument, and `27` confirmed eye 0 is genuinely the left
eye (red was reported in the left eye, and red is what eye 0 submits) — so the
indexing is trustworthy and only the displacement direction is open.

**Gate:** near objects separate more than far ones, and the world reads convex
rather than inside-out. Swapping `GE_VR_EYE_SIGN` must visibly reverse it — if it
does not, the eye offset is not reaching the render.

## Prerequisite that is now on the critical path

**The SteamVR floor calibration**, 2.4-3.2 m out (`10`). `26` said it was not
needed for 3f-1 or 3f-2. 3f-3b is a depth judgement, and `10` records this
miscalibration collapsing apparent disparity in a stereo test already. Fix it
before 3f-3b; 3f-3a does not care.

**MSAA must be off** — RT64 ignores render target overrides under MSAA, so with
it on there are no two eye targets to copy.

## Risks, in the order they are likely to bite

1. **Resource state.** The back buffer is a bound render target at hook time and
   must be transitioned to `COPY_SOURCE` and back. **A resource cannot be bound
   as an RTV while in `COPY_SOURCE`** — unbind with `OMSetRenderTargets(0, ...)`
   first. RT64 re-sets the framebuffer every frame, so leaving it unbound is safe;
   leaving it in the wrong *state* is not.
2. **Format compatibility.** The XR images are `R8G8B8A8_TYPELESS` (`27`); the
   back buffer is `R8G8B8A8_UNORM` or the HDR variant. Copies are legal within one
   typeless family and illegal across families — and `27` is the standing proof
   that D3D12 answers an illegal call by removing the device rather than by
   returning an error. **Log both formats on the first copy.**
3. **Window resize.** Swapchain extents become wrong. Detect and recreate, or the
   copy silently mismatches.
4. **`vrEyeOneTarget` is null when not in a level.** Front end, menus and
   cutscenes have no eye split. Submit `layerCount = 0` rather than copying
   garbage.
5. **Odd window widths.** `windowWidth / 2` truncates and the halves stop tiling.
   Round down and copy matching extents.

## Gates, to the standard from `00-START-HERE`

*What would this build have to do differently for each of these to fail?*

| # | Check | Pass |
|---|---|---|
| 1 | `gevr.log` | Both source and destination formats logged; extents match; no `DEVICE REMOVED` |
| 2 | Headset, `GE_VR_XR_FORCE_EYE` unset | The game, in both eyes |
| 3 | Headset, `GE_VR_XR_FORCE_EYE=0` | **Depth disappears.** If it does not, the two eyes were never different |
| 4 | 3f-3b: depth | Near separates more than far; world convex |
| 5 | 3f-3b: `GE_VR_EYE_SIGN=-1` | Visibly reverses gate 4 |
| 6 | Monitor | Still playable, side-by-side view |
| 7 | `GE_VR_XR` unset | Unchanged. 60 fps |

Gate 3 is the one that makes this slice worth anything, and it is the one that is
tempting to skip once the game appears in the headset.

## Command

```powershell
cd C:\Users\<USER>\Desktop\GoldenEye64Recomp
$env:GE_VR_XR="1"; $env:GE_VR_SBS="1"; $env:GE_VR_FRUSTUM="1"
$env:GE_VR_FIT_ASPECT="0"; $env:GE_VR_TEST_OFFSET="3.175"
build\Release\GoldenRecomp.exe
```

MSAA off. SteamVR up, headset awake.

## After 3f-3

**3f-3c / design A** — render each eye through `VIRenderer` directly into the XR
swapchain image at the headset's own resolution, and drop the SBS coupling and
the resolution cap with it. Then **3f-4**, live pose and FOV from
`xrLocateViews`, replacing the hardcoded Pimax tangents and the
`GE_VR_TEST_OFFSET` constant.

---

# Revision — design A chosen, 2026-08-22

**Decision: best quality and performance.** Design C (copying the side-by-side
window) is dropped. It capped the headset at roughly a third of its panel to save
implementation effort, and that is the wrong trade for a project whose whole
point is what the headset shows.

## A', as built — A's quality without A's coupling

Design A as written above wrapped the acquired OpenXR image as an RT64
framebuffer, which would make RT64 render into a resource it does not own. That
is the first thing of its kind in this codebase and it is not necessary.

**Built instead: RT64 renders each eye into its own offscreen target at a size
the host requests, and publishes them. The host copies those into the OpenXR
swapchain images.**

| | |
|---|---|
| Resolution | **4140x3292 per eye** — the headset's own recommendation, not the window's |
| Extra cost | one full-rate copy per eye per frame, ~20 GB/s against a 5090's ~1.8 TB/s |
| RT64 knows about OpenXR | **nothing.** "Render the two eyes into offscreen targets of this size and publish them" |
| External resources in RT64 | **none** |
| Monitor | unchanged and normal; no SBS coupling |

That last row matters beyond tidiness. `12` §7 puts RT64 changes on the MIT side,
to go upstream; the host is GPL-adjacent and stays local. A' keeps every
OpenXR-shaped line in the host and leaves RT64 with a generic feature that stands
on its own.

## Mechanism

**RT64** (`rt64_present_queue.cpp`, `rt64_shared_queue_resources.h`,
`rt64_present_queue.h`) — the host writes `vrPresentEyeWidth` / `Height`; zero is
the default and disables the whole path, so an untouched build behaves exactly as
before. When set, `threadPresent` renders each eye through `VIRenderer` into an
offscreen framebuffer, using the `viewportOverride` / `scissorOverride` that
`25` already added, and publishes the textures in `COPY_SOURCE`.

**Eye 1 goes through the same preparation as the main target** — resolve or
downsample, its own `resolutionScale`, its own format. `25` records what
happens otherwise, and it presents as "stereo is broken" rather than as a bad
blit.

**Host** (`ge_vr_xr.cpp`) — `CopyTextureRegion` into the acquired image, with
transitions `RENDER_TARGET -> COPY_DEST -> RENDER_TARGET`, since OpenXR requires
the image back in `RENDER_TARGET` at release.

## The ordering argument, which is load-bearing

The host's list is executed *during* RT64's render hook, while RT64's own list
for this frame is still open. **So the eye images read are the ones RT64 finished
last frame — one frame stale, and correct rather than racy.** Both submissions
are on the same queue, so the read is ordered before RT64's next write to the
same texture. Nothing to synchronise, no fence, no cross-queue anything.

## Falling back rather than showing something stale

When RT64 has published no eye image — front end, menus, cutscenes, the opening
frames, or any frame not in a level — the host submits the 3f-2 flat colour
instead. **Red and blue say "no image" unambiguously**; a stale frame would look
like a working one that had frozen.

## The gate, unchanged and still the whole point

`GE_VR_XR_FORCE_EYE=0|1` sends one eye's image to **both** eyes.

`10`'s warning is why this exists: a monoscopic image with correct perspective
fuses, looks like a room, and survives head movement. So "I can see the game and
it looks 3D" is worth nothing on its own. **With this set the depth must
collapse.** If it does not, the two eyes were never receiving different images.

## Status

Built clean. Session starts, `4140x3292` per eye requested and granted, 60 fps on
the monitor, no device removal. `eye0=0 eye1=0` in the log because the eye split
requires being **in a level** — `VrEyeOverride` is gated on `inLevel`, so the ROM
picker and the front end correctly have no eye targets to publish.

**Awaiting the in-level observation.**
