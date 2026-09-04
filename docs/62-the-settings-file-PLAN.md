# 62 — the settings menu, and why changing a setting breaks the session

**PLAN / investigation, 2026-08-23. Nothing built.**

Two reported symptoms, one file:

1. **The in-game graphics menu rewrites `graphics.json`**, and its default turns
   MSAA back on — which silently destroys stereo (`43`).
2. **Changing a setting mid-session breaks execution.** The working procedure is
   currently: change, save, close, reopen, play. That is a workaround that has
   been in use long enough to feel normal.

---

## What is read so far

| | |
|---|---|
| `src\game\config.cpp:19` | `graphics.json` |
| `:343`, `:360` | `ultramodern::renderer::set_graphics_config(new_config)` — the live apply |
| `:346` `save_graphics_config` | writes the whole config back |
| `:494-496` | load at startup; **write a fresh default file if loading fails** |
| `:522` | save on exit |
| `rt64_render_context.cpp:174-205` | the `43` MSAA force-off |
| `rt64_shared_queue_resources.h` | `rtConfigChanged`, `userConfigChanged`, `fbConfigChanged`, `newConfigValidated` — **RT64 HAS a live-reconfigure path** |

**So a live settings change is a supported operation in RT64.** Symptom 2 is
therefore probably not "RT64 cannot do this" but **"something of ours does not
survive it"** — and the obvious candidate is this project's own eye render
targets, which are allocated once and sized from a config that just changed
underneath them. **Candidate, not finding.**

## THE ONE THAT SHOULD BE FIXED FIRST, AND IT IS SMALL

**`43`'s MSAA force-off is gated on `std::getenv("GE_VR_XR")`.**

```c
if (std::getenv("GE_VR_XR") != nullptr) {
    application->userConfig.antialiasing = ...::None;
```

**`-Flat` never sets `GE_VR_XR`.** So the protection that `43` describes as
*"the funnel every path reaches, so it is enforced here rather than written down
again"* **does not cover the harness every measurement since `49` has been taken
on.** Open the graphics menu once, and every `-Flat` stereo measurement
afterwards is void — silently, with the file on disk looking like a choice
somebody made.

**This is O29's shape exactly** — a safeguard built for the XR path that `-Flat`
inherited none of — and it is the second instance in two days. **New: O46.**

**Fix:** gate it on "VR is active in any mode" rather than on the XR env var.
Two lines. **A behaviour change, so it is its own slice and its own gate.**

## The plan, ordered cheapest first

### Slice 1 — make the MSAA guard cover `-Flat` (O46)

**Gate:** with `msaa_option` set to `MSAA2X` in `graphics.json` by hand, launch
`-Flat`; the log must print the `MSAA forced OFF` line and `render passes:` must
still show `eye0=N eye1=N distinctTargets=N` all equal. **What it reports if it
is looking at the wrong thing:** if the line prints but `distinctTargets` is 0,
the override is being applied after RT64 has already decided, and the fix is in
the wrong place.

### Slice 2 — find out what actually breaks on a live change

**Read first, do not experiment.** Three questions, all answerable from source:

1. Which settings take the `set_graphics_config` live path, and which are only
   consumed at device/swapchain creation?
2. Does anything of ours (eye targets, `vrPresentEyeWidth`, the published eye
   pointers) get invalidated or resized when `rtConfigChanged` /
   `fbConfigChanged` fires?
3. **What does "breaks execution" mean concretely** — a crash, a hang, a black
   screen, or wrong rendering? **This has never been written down**, and the four
   have different causes. `48` rule 3: the report is a description, and the first
   step is to turn it into an observation.

**Then** instrument: log every config change with what changed, and log whether
the eye machinery was rebuilt.

### Slice 3 — stop the menu writing settings VR cannot survive

Two designs, not chosen:

- **Clamp on write:** when VR is active, `save_graphics_config` refuses to write
  values that break stereo. The file then never lies.
- **Clamp on read, which is what `43` does:** the file may say anything and the
  funnel overrides it. Simpler, already exists, but leaves a file on disk that
  disagrees with the running program — and **`00-START-HERE` has been wrong about
  `ds_option` for exactly that kind of reason before** (`49`).

**Preference, weakly held: clamp on write AND keep the read-side funnel.** The
read-side guard is the one that cannot be bypassed; the write-side one is what
stops the file becoming a lie. Belt and braces is justified when the failure is
silent and costs a session.

## Not to be done

**Do not "fix" the mid-session apply by making the menu require a restart.** That
is the workaround made official, and it removes the ability to tune a VR setting
while wearing the headset — which is exactly when tuning is needed.

---

# THE SYMPTOM, NAMED — 2026-08-23

> **"It makes the view very blurry and drops performance."**

Not a crash, not a hang, not a black screen. **A rendering symptom.** That is
worth the question it took to get: the four candidates had four different causes
and this eliminates three of them.

## And it is the same shape as O22, which has been open since `49`

| | |
|---|---|
| **O22** | `-ResScale`: **8x fewer pixels ran 4x SLOWER** (60 → 16). Unexplained |
| **O47** | change a setting mid-session: **blurry AND slower** |

**Blurry means rendering at a lower internal resolution and scaling up. Slower
at a lower resolution is the paradox O22 records.** Two reports, one shape, and
until now they were separate items. **They should be chased together, and O22's
instrument (`stage ms:`) already exists.**

`49`'s warning applies to both: *"do not reach for resolution as the framerate
knob until O22 is understood."*

## One candidate, weakened by reading — which is the point of reading first

The tempting story was "our eye targets are created once and never resized, so a
resolution change leaves them stale". **Checked, and it is not that:**

- `eyeColorTargets.resize()` (`workload_queue.cpp:1217`) resizes the **vector**,
  not the textures — so far so suspicious.
- But the targets are handed to `targetManager.setOverride()`, and the render
  path then fetches them through `targetManager.get(colorTargetKey)` and calls
  `colorTarget->resize(worker, rtWidth, rtHeight)` at **`:573`** — the ordinary
  path, which the override participates in.

**So the eye targets DO follow the resolution.** The candidate is not dead — the
resize could still be mistimed relative to present — but it is no longer the
obvious answer, and an hour of building an instrument for it has been saved.

## Where to look instead

`rtWidth` / `rtHeight` at `:573` derive from the resolution scale. **What
recomputes that scale on a live config change, and what does present believe the
size is at the same moment?** A target resized on the workload thread while the
present thread still holds the old dimensions produces exactly the reported
symptom — `25`'s failure, where the VI shader maps `videoResolution` onto a
mismatched `textureResolution` and **samples a region and magnifies it.**
**Blurry is what that looks like when the mismatch is small.**

**Instrument, not a fix:** log `rtWidth x rtHeight`, the resolution scale, and
present's `textureWidth x textureHeight` whenever any of them change. If they
ever disagree, that is the bug, and the log says so on the frame it happens.

---

# HOW MUCH OF THIS CAN WE EDIT? — all of it

Asked, and worth answering plainly because it changes what is worth planning.

**Everything here is built from source on this machine. There is no black box.**

| Layer | Editable? | Constraint |
|---|---|---|
| The settings menu itself | **Yes** — recompui / RmlUi, in `src\ui\` | none technical |
| `graphics.json`'s schema, defaults, validation | **Yes** — it is serialisation of `GraphicsConfig`; fields can be added, defaults changed, values refused | none technical |
| The renderer | **Yes** — `lib\rt64\`, and this project already changes it | **MIT: keep it upstreamable** |
| The host | **Yes** — `src\main\`, `src\game\` | links GPL-3.0; stays local |
| **The game's own logic** | **Yes** — `RECOMP_PATCH`, which is how `viSetFovY` is already hooked | a new patch NAME needs the long build (`07`) |

**So the constraint is not what can be edited. It is the licence split for what
can be PUBLISHED (`PUBLISH-MANIFEST.md`), and the discipline that `-NoXr` must
never break.**

## What that unlocks, and it is the answer to the env-var workflow

Every VR knob today is an environment variable set by `vr.ps1`: units per metre,
eye offset, head signs, skip-eye, present-eye. **That is a debugging interface,
and it is why every test needs a relaunch from PowerShell.**

Since the menu is ours to edit:

- **A VR settings page** with the knobs that are actually preferences — auto-aim
  on/off, units per metre, snap vs smooth turn, comfort options — leaving the
  environment variables to be what they should be: **diagnostics.**
- **Settings that cannot break the renderer**: refuse MSAA while VR is active at
  the point of *writing*, so the file never contains a value that silently kills
  stereo (slice 3 above).
- **Tuning while wearing the headset**, which is the only time some of these can
  honestly be judged — and is impossible today, since changing a value means
  taking the headset off, editing, relaunching, and getting back to the spot.

**That last one is worth more than it sounds.** Every wear test this project has
run has been a single-shot: one configuration, one session, one impression. A
knob that can be turned while wearing it turns a wear test into a comparison.

**Not scheduled. Recorded because it changes what `61` should expose** — if a VR
settings page is coming, the controller slice's knobs should be written as
config values from the start rather than as more environment variables.
