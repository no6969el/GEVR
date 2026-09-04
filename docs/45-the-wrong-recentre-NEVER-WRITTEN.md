# 45 — the recentre, done wrong the second time

> ## THIS DOCUMENT WAS NEVER WRITTEN. Stub added 2026-08-23 so the citations
> ## resolve. **No content invented or removed.**

## What `45` names

The **second** wrong recentre: transforming the head pose and then submitting
the *recentred* pose as the projection layer's pose.

## Where it lives — the reasoning survives verbatim

`src\main\ge_vr_xr.cpp:78`, inside the `46` block:

> 3f-5 transformed the pose inside the RENDERER, leaving this file submitting
> the RAW pose as the projection layer's. The image was drawn from one
> viewpoint and described to the compositor as another.
>
> **docs\45 "fixed" that by submitting the recentred pose - which is worse, and
> the reason is the whole lesson.** `XrCompositionLayerProjectionView::pose` is
> defined to be IN THE LAYER'S SPACE, and the layer's space was still raw
> LOCAL. Handing it recentred coordinates is not an inconsistency, **it is a
> false statement about where the head was, and the compositor believed it**:
> the view went far right and sideways and one eye went black as its frustum
> was reprojected off the panel.

Also `ge_vr_xr.cpp:1233`, `:1259`, and `rt64_render_context.cpp:855` (the
head/eye split).

**Superseded by `46`**, which removed the need to transform poses at all.
