# 41 — the runtime capability block

> ## THIS DOCUMENT WAS NEVER WRITTEN. This stub was added 2026-08-23 so the
> ## citations resolve. **No content has been invented or removed.**
>
> `41` is cited 2 times across the docs and once in the source, but no file
> `41-*.md` has ever existed — not on disk and not anywhere in git history
> (checked with `git rev-list --all`). The same is true of `42`, `43`, `45` and
> `46`. See "The phantom documents" in `00-START-HERE`.
>
> **The work is real and shipped. Only the document is missing.** What follows
> is a pointer to where its reasoning actually survives, quoted rather than
> summarised, so nothing here is a reconstruction from memory.

## What `41` names

**The runtime capability block** — printed once per session: per-eye pose and
orientation, panel cant, and the frustum aspect against the real target aspect.

## Where it lives

`src\main\ge_vr_xr.cpp:1325` — `// docs\41. The RUNTIME CAPABILITY BLOCK.`

## Why it mattered

From `00-START-HERE`, which is the surviving description:

> **The runtime capability block**, once per session: per-eye pose and
> orientation, panel cant, frustum aspect against the real target aspect. Both
> a portability check and **the thing that killed the cant hypothesis by
> measurement**.

`47` used its output to close the panel-cant question at **0.097 degrees —
parallel, not the cause.**
