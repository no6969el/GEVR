# RELEASE-POLICY — staged open (build phase)

Status: draft for BarZ / GEVR helper. Not legal advice.
Currency: 2026-09-05 after PLAN-330 closed (`c87059e` docs tip).

## Goal

- **Later:** make the whole GEVR track available.
- **Now:** keep the *buildable product* locked so nobody can clone mid-project and own our progress.
- **Always:** leave an *ideas trail* so a serious person could start from scratch and re-derive the path (months of work), not `clone && build && play VR`.

## Two layers

| Layer | What | Now | Later |
|---|---|---|---|
| **Textbook** | Plans, measured results, falsifiers, architecture, ORIGIN notes, session writeups | Sharable (public docs repo OK) | Same |
| **Workshop** | `gevr_*`, XR call sites, instruments, working patches, complete `getv` VR tree, binaries, drop-in patch series | **Private / do not push public** | Open under chosen license |

## What we do *not* claim

- Evan King MIT GETV / `goldeneye-native` upstream (NOTICE already scopes MIT).
- Decomp / game data / ROM-derived material.
- OpenXR / SteamVR APIs.
- Perfect Dark VR (and other prior art): **map only**, lives under `local-only\prior-art`, never product commits.

Our claim is the **delta**: original VR integration, instruments, pacing/handover design, and authored docs about them. Tag with `LICENSE-GEVR` + `ORIGIN.md` when those land.

## Current remote facts (measured 2026-09-05)

- `no6969el/GEVR` — **public** docs textbook. Local tip `c87059e` (330). Public tip still ~310–313 sync. Local GoldenEyeVR folder had **no** `git remote` wired; histories diverge (local ahead a lot; public has a few commits not in local).
- `no6969el/goldeneye-native` — **public**, last push ~2026-08-22. **No `getv` / no `gevr` on public HEAD** (good).
- Local product tree is **~38 commits ahead** of `SegfaultEvan/goldeneye-native` origin and contains the frame loop (`7e4441a`, `gevr_xr.*`). **Do not push that ahead-set to any public remote** until release day.

## Build-phase rules

1. **Never publish the workshop.** No public push of local `goldeneye-native` VR commits; no zip of `build-windows` VR exes; no “here is the full patch series that lands 328–330.”
2. **Docs may narrate.** Naming what was measured (K-3 LANDS, xrWaitFrame blocks, etc.) is the textbook. Pasting entire production `.c` bodies into docs is not.
3. **Intentional incompleteness.** Public mirrors omit the glue that makes a drop-in VR GoldenEye.
4. **Prior art quarantined.** `local-only\` stays local.
5. **PII.** Keep Windows profile paths redacted in anything that ships public.
6. **Release day.** Publish workshop under chosen license; NOTICE/ORIGIN already honest; flip this policy to “open.”

## End-of-day hygiene (authorized; execute when today’s other work is done)

Default cut list (helper judgment against the goal above):

- Wire / repair `origin` → `no6969el/GEVR` for the docs tree; reconcile the 4 public-only commits before push.
- Push **docs textbook** through 330 (ideas trail), after a pass that guts or privatizes anything that is a full build cookbook if it hands the workshop over (candidates to review: `06-replicate`, `07-rebuild-after-patch-edit`, any doc that embeds full patch bodies or exact “copy these files” VR glue). Prefer *describe* over *deliver*.
- Do **not** push `repo\xr\` megabyte stdout logs; short reports/sidecars/summaries OK if they teach without shipping binaries.
- Do **not** push local product `goldeneye-native` ahead-38 to `no6969el/goldeneye-native` (or anywhere public). Consider making that public repo clearly “upstream mirror / no GEVR VR layer” or private if it confuses.
- Add `LICENSE-GEVR` + `ORIGIN.md` stubs when ready (separate small docs commit).
- Leave COMMIT-MESSAGE litter and build logs untracked / unpushed.

## Stop conditions

- If a scrub would delete history someone relies on: prefer `git filter` / new public branch / file deletion commit over force-push unless BarZ says force.
- Consequential public push still gets a one-line confirm in helper chat before `git push`.

## Next product HIGH (unchanged)

I-3 / D-X3 pacing handover (`geVrXrPaceArm`) — fresh session, §7c. This policy is side hygiene, not that HIGH.
