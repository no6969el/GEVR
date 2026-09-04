# MODS — ideas parked as they come up

**A running list. Not a plan, not a commitment, and deliberately NOT on the
critical path.** Anything here is something to build once VR itself is solid.

**How to use this file:** when an idea comes up mid-session, it lands here with
enough context to be actionable later, and the session carries on. Nothing here
should ever be built while a blocker is open.

---

## The vision: a mods menu

An in-game menu exposing the knobs this project has already built as **player
options** rather than command-line flags. Most of the plumbing exists — the
`GE_VR_*` environment variables are read once at startup and would need to
become live-adjustable, which is the real work.

**Candidates already built and already knob-driven:**

| Knob | Today | As a mod option |
|---|---|---|
| `GE_VR_UNITS_PER_METRE` | env var, startup only | **world / player scale slider** |
| `GE_VR_TEST_OFFSET` | env var | eye separation, for comfort tuning |
| `GE_VR_EYE` (`-SwapEyes`) | env var | an accessibility / troubleshooting toggle |
| `GE_VR_HEAD_TRANSLATE` | env var | "seated / no lean" comfort mode |
| `GE_VR_RES_SCALE` | env var | render resolution, a performance slider |

---

## "BIG JAMES" MODE

**Requested 2026-08-23, the moment stereo first worked.**

When B1 was fixed and the headset showed real depth for the first time, the
immediate report was:

> *"My arms and my perspective are comically large."*
> *"The arm and gun size is very large in comparison to the people and
> surroundings."*

**That is a bug — `71` O1, the scale question `16` left open since Phase 1 —
and it is going to be fixed.** But the effect itself was funny and worth
keeping as a deliberate option once the correct value is known.

**Big James mode = drive the world/player scale AWAY from the correct value on
purpose, in the direction that makes Bond enormous.**

### What to record when O1 is settled — THIS IS THE ACTIONABLE PART

**Do not lose the numbers while fixing the bug.** When `71` O1 sweeps
`-UnitsPerMetre`, write down:

1. **The CORRECT value** — whichever makes a doorway feel like a doorway
   (`16`'s own test). This is the default and belongs in `16`.
2. **The value in use on 2026-08-23 when "Big James" was observed: 100 u/m**
   (`16`'s derivation). **That is Big James mode's setting**, and it is already
   known.
3. **The relationship** — how many units/metre correspond to roughly what
   apparent height, so a slider can be labelled in something a player
   understands rather than in engine units.

> **ANSWERED 2026-08-23 (`77`). The corrected default is LOWER, ~50, not higher.**
> **So Big James is the HIGH end, not 100.** The sweep numbers, all of them:
>
> | u/m | worn verdict |
> |---|---|
> | 25 | world in perspective, slightly large |
> | **50** | **best — the provisional default** |
> | 35 | close, between the two |
> | 100 | world reads noticeably small |
> | **400** | ***"everything really small, I was a tall big person"* — THIS IS BIG JAMES** |
>
> **Big James = `-UnitsPerMetre 400`.** And note the bonus the caveats predicted:
> at 400 **the gun shrank too**, so Big James is a big person holding a tiny gun,
> which is funnier than the bug was.

**So: Big James = `-UnitsPerMetre 100`, if the corrected default turns out to be
higher.** If the correct value turns out to be *lower* than 100, then 100 is not
Big James and the mode needs the opposite end of the sweep — **which is exactly
why the sweep numbers must be recorded rather than just the winner.**

### Caveats worth knowing before building it

- **`GE_VR_UNITS_PER_METRE` drives the IPD *and* head translation together.**
  Changing it changes how far you physically move in the world as well as how
  big things look. Big James should probably feel like *long strides* too, and
  that is a feature, not a bug.
- **Comfort.** A wrong scale is a known VR sickness trigger. Any mode that
  deliberately mis-scales the world needs a clear label and an easy way out.
- **The viewmodel is a separate ratio** (`71` O1). If the arm/gun size relative
  to the world is its own fault, Big James may need a second knob, and the
  *funny* part of the effect may live in that one rather than in units/metre.

---

## A FLAT SCREEN IN FRONT OF YOU — the pre-level and menu display

**Requested 2026-08-23, worn, while the headset showed the startup blue/red
band (`19`) with nothing to look at.**

> *"It'd be nice to output the video so we can see it before it goes to the
> game. Maybe output to a screen in front of us."*

**The mechanism is an OpenXR QUAD LAYER** — `XrCompositionLayerQuad`, a flat
rectangle placed in space, submitted alongside (or instead of) the projection
layer. It is the standard way every VR title shows 2D content, and we already
build and submit a projection layer every frame, so the frame loop, the
swapchain and the space are all in place.

**Why it is worth more than comfort:** the same mechanism is the honest fix for
**the menus**, which currently render into the projection layer and read as *"a
zoomed in version of what's on the screen"* (`66`, `25`'s blit bug). A menu is
flat content and wants a flat layer. **One mechanism, two problems.**

**Where it belongs:** not on the critical path, and NOT while stereo scale
(`75`) is open. But when it is built, build it for menus first and the startup
screen falls out of it for free.

## Parked, no detail yet

- **Peek** (`31`) — a bindable raised viewpoint. Already designed, deliberately
  off the VR critical path, and redundant in a headset where standing up does
  the same thing. **Would make a good mod option rather than a core feature.**
- **Seated / standing presets** — bundle `-NoHeadTranslate` and a height offset.

---

## Rules for this file

1. **Nothing here is built while a blocker is open.** B1 is fixed; B2, the
   teardown crash, the eye distortion and judder are not.
2. **An idea gets recorded with the NUMBERS it depends on**, or it is not
   actionable later — see Big James above.
3. **Bugs that are also funny are still bugs.** Fix them first, then offer the
   broken behaviour deliberately if it is worth offering.
