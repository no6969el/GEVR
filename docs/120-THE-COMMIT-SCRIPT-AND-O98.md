# 120 — THE COMMIT SCRIPT WOULD HAVE LOST TODAY'S WORK. AND O98.

**2026-08-24. Two housekeeping changes, both of the kind that costs nothing now
and a session later. No machine needed for either.**

---

## §1 — `commit-session.ps1` WAS STALE IN THE WORST POSSIBLE WAY

**The owner said he would back up and commit tonight, using this script.
It would not have worked, and it would not have SAID it did not work.**

**Two faults, and the second is worse:**

1. **It staged a HARDCODED FILE LIST.** Twenty-odd explicit paths, all of them
   from the `86`-`96` era. **Every file this session touched — eight source
   files and fourteen documents — is absent from that list.** `git add` of a
   list that no longer describes the tree succeeds silently and stages nothing
   new.
2. **It committed under a HARDCODED MESSAGE** describing docs 86-96 and slice
   S0. **So the few files that WERE on the list would have gone in labelled as
   somebody else's work.**

**AND THE EVIDENCE THAT THIS ALREADY HAPPENED IS IN THE LOG.** Three consecutive
commits, three different sets of changes, one subject line:

```
20:10  S0 the 6DoF instrument, and the judder test harness (docs 91, 94)
09:40  S0 the 6DoF instrument, and the judder test harness (docs 91, 94)
10:02  S0 the 6DoF instrument, and the judder test harness (docs 91, 94)
```

> ## **A HISTORY THAT SAYS THE SAME THING THREE TIMES IS NOT A HISTORY. AND THE ONE THING GIT IS FOR HERE IS RECOVERY — `HANDOVER.md` WAS RESTORED FROM `git show HEAD:` TWO DAYS AGO AFTER A BAD WRITE TRUNCATED IT TO ZERO.**

### §1.1 — WHAT IT DOES NOW

| | |
|---|---|
| **Stages** | `git add -A`. **Verified safe rather than assumed:** both `.gitignore`s already exclude `*.bak*`, `gevr-*.log`, `*.log` and build output, so the session's backups and logs cannot be swept in |
| **Message** | **`-Message` is now MANDATORY.** No default, because a default is how three commits ended up identical |
| **Locks** | **Cleared FIRST**, in both repos, and it **refuses to run if a `git` process is live** — clearing locks under a running git would corrupt it |
| **Before** | Prints every staged path **before** committing |
| **After** | Re-checks `git status` and **warns if the tree is not clean** — a commit that succeeded and left the tree dirty missed something, and looks identical to one that did not |
| **`--ignore-submodules=all`** | On the status/diff calls. `GoldenEye64Recomp` has `lib/ge` (n64decomp/007), and recursing it is why plain `git status` exceeds the bridge's 45-second cap |
| **`-DryRun`** | Stage and list, do not commit |

**Old version kept at `commit-session.ps1.bak120`.**

```powershell
.\commit-session.ps1 -Message "subject line

body"
```

---

## §2 — O98: THE NEW STRUCT MEMBERS MOVED TO THE END

**`115` §6 recorded this as deliberately NOT done at the time**, because the
clean rebuild was the single-variable test and changing the source in the same
step would have left us unable to say which one fixed it. **The cause is known
now, so it is done.**

**`vrEyeSampleAlt`, `vrEyePick[]` and `vrEyePickSeq` moved from the middle of
`SharedQueueResources` to the end, under a banner that says ADD NEW MEMBERS
HERE.**

**This is the SECOND layer, not the fix.** `build.ps1`'s header guard (`115` §4)
is the fix. **This one changes the failure mode if a stale object ever slips
past it:** members added at the end cannot move the offset of anything that
existed before them, so the damage degrades from *"the whole struct is
misaligned"* to *"the new field reads garbage"*.

**`115` cost an hour and presented as a performance regression AND a gameplay
bug simultaneously. That is the failure mode being defended against.**

**`InterpolatedFrameCounters::eyeSet` (`116`) was already appended at the end of
its struct and did not need moving.**

---

## §3 — WHAT IS STILL OWED ON THE BACKUP FRONT

**Neither repo has a remote of ours.** `GoldenEyeVR` has none at all;
`GoldenEye64Recomp`'s `origin` is `cblock85/GoldenEye64Recomp`, which is not the
owner's and cannot be pushed to.

**The owner's stated plan: a GitHub repo on the disk, eventually synced with the
GitHub app, backups tonight.** **`PUBLISH-MANIFEST.md` must be read before a
PUBLIC remote** — `local-only/` is tracked deliberately and must not go to one,
and the licence split puts RT64 changes (MIT, upstreamable) on a different
footing from the recomp host (links GPL-3.0). **A PRIVATE repo sidesteps the
entire question and is the obvious first move.**
