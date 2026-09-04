# 46 — the recentre, done the way OpenXR intends

> ## THIS DOCUMENT WAS NEVER WRITTEN. Stub added 2026-08-23 so the citations
> ## resolve. **No content invented or removed.**

## What `46` names

Making the recentre a property of the **reference space** everything already
shares, via `XrReferenceSpaceCreateInfo::poseInReferenceSpace`, instead of
transforming poses.

## Where it lives — the reasoning survives verbatim

`src\main\ge_vr_xr.cpp:70`:

> **docs\46. THE RECENTRE, DONE THE WAY OPENXR INTENDS.**
> Two wrong versions preceded this one, each instructive. [...]
> The right answer is **not to transform poses at all.** OpenXR lets a reference
> space be DEFINED at an offset - `XrReferenceSpaceCreateInfo::poseInReference-`
> `Space` - so the recentre becomes a property of the space everything already
> shares. `xrLocateViews` returns recentred poses because the space is
> recentred, and `layer.space` names that same space, so the pose we render
> from and the pose we submit are **not merely equal, they are the same number
> in the same frame of reference.**
>
> **The rule earned: when two things must agree, do not synchronise them.
> Remove the second one.**

That rule is `48` rule 8, and it has been applied twice since — in `61`, to
reject a second input transport, and to place the thumbstick Y negation at one
boundary rather than in the consumer.

Also `ge_vr_xr.cpp:594` (rebuild between frames only), `:1230`, `:1266`.
