# 43 — MSAA is forced off under VR

> ## THIS DOCUMENT WAS NEVER WRITTEN — and it is **cited 24 times**, more than
> ## any other missing document. Stub added 2026-08-23 so those citations
> ## resolve. **No content invented or removed.**

## What `43` names

RT64 **ignores render target overrides when MSAA is on**, so the second eye is
never drawn — silently. `43` forced MSAA off under VR at the funnel every path
reaches, rather than documenting the rule again.

## Where it lives — the reasoning survives verbatim

`src\main\rt64_render_context.cpp:174-205`:

> **docs\43. MSAA IS FORCED OFF UNDER VR, and it is not a preference we are
> overriding lightly.**
> RT64 ignores render target overrides when MSAA is on, so the second eye is
> never drawn. There is no error, no warning, and RT64's own report goes to
> stderr, which /SUBSYSTEM:WINDOWS discards - **so the failure is entirely
> silent.** The visible result is a right eye showing a target nothing ever
> wrote to, which reads as "skewed" or "off centre" rather than as absent, and
> **two separate hypotheses were tested against that non-existent eye** before
> the render-pass counters were read.
>
> 00-START-HERE has carried "MSAA must stay off" since Phase 1. That was not
> enough, because the setting does not stay where it is put: **the in-game
> graphics menu rewrites graphics.json, and config.cpp:28 makes MSAA2X the
> default it writes. So merely opening the graphics menu silently destroys
> stereo**, and the file on disk looks like something the user chose.
>
> **A documented rule that a menu can undo is not a rule.**

The starvation warning it added is at `rt64_render_context.cpp:1661`
(`docs\43. SAY SO when the second eye is not being drawn.`) — currently
false-positives in menus, `39` O17.

## KNOWN DEFECT — `62`, O46

**The guard is gated on `std::getenv("GE_VR_XR")`, and `-Flat` never sets it.**
So the harness every measurement since `49` was taken on is **not protected**.
Open the graphics menu once and every subsequent `-Flat` stereo measurement is
void. Slice 1 of `62`, two lines, not yet built.
