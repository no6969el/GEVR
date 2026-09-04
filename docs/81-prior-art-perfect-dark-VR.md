# 81 — PRIOR ART: Perfect Dark has a shipping VR port, and it is MIT.

**2026-08-23, ~17:20. Asked by the user at exactly the right moment**, which is
`48`'s prior-art trigger firing correctly for once: we are about to DESIGN the
hand-aim slice, not debug it.

**`48` predicted this item would be skipped even when triggered.** It was run in
`55`, and it is being run again here — and this time it found something.

---

## THE FINDING

| | |
|---|---|
| **`perfect-dark-pc-port/perfect_dark`** (fgsfdsfgs) | The PC port of the Perfect Dark decomp. **MIT.** No VR |
| **`Alex-LeTux/perfect_dark_VR`** | A VR fork of it. **MIT.** PCVR **and standalone Quest**, head tracking and **motion-control aiming**, beta released ~July 2026, developed on a Vive Pro with Index controllers |
| **`Tsuey/perfect_dark_VR`** | The same lineage, `port` branch |

**Press coverage of the release is real and positive** — Time Extension quoted a
tester calling it *"the best shooter experience I've had with virtual reality."*

## WHY THIS MATTERS MORE THAN ANY OTHER PRIOR ART IN `48`'s TABLE

**Perfect Dark is the SAME ENGINE.** GoldenEye's `gunfire.c`, `bondview2.c` and
`chr.c` have direct Perfect Dark counterparts with the same structure and often
the same function shapes. **The viewmodel placement problem we spent this
session on is, in that codebase, the same problem in nearly the same code.**

**Compare with what `55` found:** StarFox64-VR's licence was UNCLEAR, so it may
influence nothing. **This one is MIT.**

## THE LICENCE VERDICT — checked BEFORE reading source, per `48`

```
MIT  ->  may influence ANYWHERE, including lib/rt64/ and repo\,
         the upstreamable half of PUBLISH-MANIFEST.md
```

**This is the good half of the split.** Nothing about it is encumbered the way
GPL prior art would be, and it may inform the MIT side of this project as well as
the GPL host.

**Attribution is still owed.** MIT requires the notice to travel with anything
derived from it. **If a line of their approach lands here, it is credited here,
in `PUBLISH-MANIFEST.md` and in the source comment.**

## WHAT TO LOOK FOR, AND IN WHAT ORDER

**Do not read it as a shortcut for this session's remaining bug.** Read it before
slice 3 is designed. The specific questions, all of which this session has been
guessing at:

1. **How is the weapon placed relative to the controller?** We are re-rooting the
   game's node matrices (`78`, `79`). **Do they replace the transform, hide the
   game's model and draw their own, or something else?**
2. **How do they stop the engine's own turn-sway rotating the weapon?** That is
   `79` correction 3 — the exact fault the user identified worn — and the same
   sway code exists in Perfect Dark.
3. **What is their world scale, and how did they arrive at it?** `77` measured
   ours at ~50 units/metre by wearing it. A second data point from the same
   engine family is worth a lot.
4. **How is aim delivered to the firing path?** `38` found GoldenEye's aim is a
   **screen-space pixel position with a hard clamp at roughly the original
   FOV**. Perfect Dark almost certainly has the same clamp. **How they handle
   pointing past it is the design question `76` could not answer** — gun lags,
   body auto-turns, or something better.
5. **Is there a world-space aim dot?** The user asked for exactly this: *"aim
   where I'm aiming the gun, and then have a dot or crosshair in the distance."*
   It is also `61`'s O12 amendment.
6. **Comfort and Quest-standalone constraints** — they ship on mobile hardware,
   so their frame-pacing answers may bear on O54.

## THE HONEST CAVEAT

**The VR fork's README says the VR code is not yet in the public tree** — "VR
support is not yet included as the code is still under development and not
stable enough for public release." **So the released binaries are ahead of the
published source, and questions 1-6 may not be answerable from the repository
today.**

**What to do about that, in order:**

1. **Re-check the repository** — this moves fast and it may have landed.
2. **Play the released build.** It runs on this rig. **Wearing someone else's
   solution to the exact problem is worth more than reading about it**, and it
   costs one download.
3. **Ask.** It is an MIT project with an active author.

**And the discipline that applies either way:** anything learned there is
recorded as prior art with attribution, not silently absorbed.
