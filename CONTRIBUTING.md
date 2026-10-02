# Contributing

Fan testers first. Thanks for helping GEVR Beta.

## Stay on Latest (Update first)

**Before you play or file a bug:** open **GevrRomStarter** and click **Update** once if GitHub has a newer build. That keeps your saves, prefs, and ROM path while pulling **Latest** (today **vr451**). Do not hunt older tag zips unless we ask you to reproduce on a specific cut.

Fresh install? Grab **[GEVR-Beta-vr451-win64.zip](https://github.com/no6969el/GEVR/releases/latest)** from [Latest](https://github.com/no6969el/GEVR/releases/latest), then use **Update** on every later drop.

## Play the current zip

Follow [README — How to play](README.md#how-to-play).

- **Headset:** `Start-GEVR.bat`
- **No headset / monitor only:** `Play-on-monitor.bat`

Bring a **USA GoldenEye `.z64` you own**. The zip has no ROM. We will not ask you to upload one.

Older tag **pages** may still show on GitHub. **Latest is vr451.** Do not hunt older downloads as if they were Latest.

## File a bug or crash

Use the [issue forms](https://github.com/no6969el/GEVR/issues/new/choose). The forms ask for:

- Headset model
- OpenXR runtime
- SteamVR on/off
- HMD vs monitor
- `Start-GEVR.bat` yes/no (if you have no headset, use `Play-on-monitor.bat` and pick **No**)

If the game hard-crashed, look beside `goldeneye.exe` for **`gevr-fault-*.txt`** and paste the first lines.

**Do not upload ROM files** (no `.z64` / `.n64` / `.v64`, no dumps). Screenshots, a short clip, or a few log lines are enough.

## Credits, licenses, names

- [CREDITS.md](CREDITS.md) - who we actually leaned on
- [LICENSE-MAP.md](LICENSE-MAP.md) - whose license is whose
- [LICENSE](LICENSE) - MIT for this public docs/tools tree
- [PRIOR-ART.md](PRIOR-ART.md) - Perfect Dark VR influence (map, not copied code)

GoldenEye the game is Nintendo / Rareware. GEVR is a VR add-on on a from-source PC port. Not a ROM dump, not a "mod pack."

## Code from this public repo

This GitHub tree is mostly docs, issue forms, and pack templates. The playable workshop lives in the Release zip, not as a clone-and-build here.

**PR policy (after 2026-09-25 code freeze):**
- **No code PRs** to public `main` (`xr/`, `tools/`, `historical/recomp/patches/`, `packaging/rom-starter/*.c` / `*.h`, etc.). Open an [Issue](https://github.com/no6969el/GEVR/issues/new/choose) instead; new product work is private.
- **Allowed** (owner discretion): typos, README / BETA / living-status / issue-template copy, and other front-facing docs.
- Testers: Issues + zip feedback only. Do not expect to clone-and-build from this repo.

If a credit line is missing for something we really used, open an Issue titled `Credits: ...` and point at the borrow.

Stay tuned. Star the repo and [follow @no6969el](https://github.com/no6969el).
