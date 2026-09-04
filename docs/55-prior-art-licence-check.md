# 55 — prior art: licence check before reading. DONE

**2026-08-23. `48`'s triggered item, run for the first time in this project.**

**Result: do not read StarFox64-VR. And it would not have helped this bug.**

---

## StarFox64-VR — the closest prior art on paper

`RaYRoD-TV/StarFox64-VR`. OpenXR, per-eye stereo, motion controllers,
world-space HUD, on an N64-lineage PC port. `00` has listed it as
**"Licence not established — establish it before reading the source"** since it
was first noted.

### Licence: UNCLEAR. It may influence nothing

The repository contains a `LICENSE.md`, and **GitHub does not display a licence
badge for it** — meaning GitHub's licence detection does not recognise it as a
standard licence. The file itself was not retrievable at the usual raw paths.

Against this project's own table:

| Source licence | May influence |
|---|---|
| **Proprietary or unclear** | **nothing** |

**So: nothing. Not the host, not `lib/rt64/`, not by description.** The rule is
not "read it carefully"; it is do not read it. `00` and `48` both say so, and
the whole point of establishing the licence *first* is that this answer arrives
before any contamination.

### Its upstream is CC0-1.0 — and that does not help

It is a fork of `HarbourMasters/Starship`, which is **CC0-1.0** — a public-domain
dedication, maximally permissive, and free to influence anything. But **the VR
work is in the fork**, not in the CC0 upstream. The permissive licence covers
exactly the part we do not need.

### The architectural finding, from the README only

**StarFox64-VR is built on `libultraship`, not RT64.** Different renderer stack
entirely: an OpenXR layer over the Starship port with "VR render hooks" in a
libultraship fork.

**So even under a permissive licence its per-eye mechanism would not transfer**
to a `setOverride`/`RenderTargetKey`/`ProjectionProcessor` problem. Its value
would have been architectural — an OpenXR layer over an N64-lineage port with
the headset code kept outside the renderer — **and that is the architecture this
project already built** (`00`, "Architecture, as built").

## RT64 upstream — MIT, and no help either

`rt64/rt64` is **MIT** and is the upstream of our renderer, so it may influence
anything, including the upstreamable half. Its README documents widescreen,
frame interpolation and path tracing, and **makes no mention of stereo, VR,
per-eye rendering, or multiple render targets per frame.**

**There is no upstream stereo path to borrow, and no upstream fix for a bug we
would be re-finding.** The per-eye work in `lib/rt64/` is genuinely new, which is
consistent with `00`'s claim that it is the upstreamable part.

---

## What this exercise was worth

**`48` prediction 2 said prior art would be skipped even when triggered.** It was
skipped for the whole project until now — so the prediction scores as **right
until this session**.

The honest accounting of what it bought:

- **A firm "do not read" on the one repository this project kept listing as
  promising.** That listing has sat in `00` for many sessions as an open
  temptation with an unresolved licence. It is now resolved and closed.
- **A negative result on RT64 upstream**, which is worth as much: nobody needs
  to go looking there for a stereo path that does not exist.
- **It did not help the live bug at all**, and `48`'s trigger predicted that
  correctly: *"If there is a concrete bug in front of you, this is
  procrastination."* There was, and it was.

**Recommendation for `48`:** keep the trigger as written. Prior art is for
designing. This run was worth doing once, to close the licence question
permanently — not as a debugging step.

## Sources

- https://github.com/RaYRoD-TV/StarFox64-VR
- https://github.com/HarbourMasters/Starship
- https://github.com/rt64/rt64
