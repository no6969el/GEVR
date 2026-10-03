# GevrRomStarter version picker (planned)

**Status:** specification and player-facing rules only. **Not shipped** in the public **vr452.4** cut. This page is the plan for BarZ and for whoever implements the dropdown in **GevrRomStarter** (built from the product tree; sources for the ship stamp live under [`packaging/rom-starter/`](../packaging/rom-starter/README.md) in this repo).

**This is not a new main download.** The [README](../README.md) front page and GitHub **Latest** stay on **[vr452.4](https://github.com/no6969el/GEVR/releases/tag/vr452.4)** (`GEVR-Beta-vr452.4-win64.zip`) until the project deliberately moves Latest. The picker is an optional install path inside the starter, not a replacement for that link.

---

## What players get

A **dropdown** in **GevrRomStarter** lists public **GEVR Beta** Windows zip releases from [github.com/no6969el/GEVR/releases](https://github.com/no6969el/GEVR/releases). The player picks a row, then the starter downloads that tag’s asset (same family of zips as today’s manual download) and applies it like **Update** does today (saves, GEVR Settings, and the player’s USA `.z64` stay put unless they choose to wipe cache).

**Update** remains: one click to move to **GitHub Latest** (stable only). The dropdown is for choosing a specific listed cut—including **prebeta** builds—without changing what “Latest” means on GitHub.

---

## Stable vs prebeta (GitHub truth)

GitHub marks every release with **`prerelease`** (boolean). **GevrRomStarter must use that flag; do not infer stability from the tag name alone.**

| GitHub `prerelease` | Player label (suggested) | In dropdown? | Triggers “new version” alert? |
|---------------------|--------------------------|--------------|-------------------------------|
| `false`             | Stable (public release)  | Yes, if tag ≥ floor (below) | **Yes**, only when newer than the stable build the player is on |
| `true`              | Prebeta                  | Yes, if tag ≥ floor (below) | **No** — never treat a prerelease as an update notification |

**Prebeta builds** are GitHub **prereleases**. They **appear** in the dropdown so testers can opt in. They **do not** raise an update alert.

**Only a stable public release** raises an update alert. Today, GitHub **Latest** is the stable release **[vr452.4](https://github.com/no6969el/GEVR/releases/tag/vr452.4)**. The picker and the alert logic **must not** treat a prerelease (for example **[vr453](https://github.com/no6969el/GEVR/releases/tag/vr453)**) as “a newer stable update.”

### How **Update** already behaves (keep this)

The existing **Update** button follows **GitHub Latest**. GitHub’s Latest endpoint **excludes prereleases**. Say that plainly to players:

- **Update** = “install whatever GitHub considers **Latest**” = **newest non-prerelease** release only.
- A **prebeta** row in the dropdown is **not** what **Update** installs, and seeing **vr453** in the list does **not** mean **Update** will jump to **vr453** while **vr453** remains `prerelease: true`.

---

## Oldest row in the dropdown (floor tag)

The dropdown **must not** list legacy tags. **Do not** show **vr450**, **vr452**, **vr452.4**, or any older tag.

**Floor:** the **first official vr453 release**—tag **`vr453`** on the public GEVR repo. Every listed row must be **`vr453` or newer** (by the project’s `vrNNN` / `vrNNN.x` ordering used for ship tags).

Older releases may still have GitHub tag pages for history; the picker simply **omits** them.

---

## Current public state (document the empty stable slice)

As of this writing:

- **Stable (Latest):** **[vr452.4](https://github.com/no6969el/GEVR/releases/tag/vr452.4)** — `prerelease: false`, GitHub Latest.
- **vr453:** **[prerelease](https://github.com/no6969el/GEVR/releases/tag/vr453)** — prebeta only. Example asset: **`GEVR-Beta-vr453-win64.zip`**. **Not** stable; **not** Latest.

**Dropdown behavior until vr453 ships as a stable release (`prerelease: false`):**

- **Prebeta section:** may list **vr453** (and any newer prereleases ≥ floor).
- **Stable section (for pinned installs via dropdown):** **no row older than the floor**—and because the floor **is** **vr453**, there is **no stable dropdown row at all** yet. Only prebeta rows (starting with **vr453**) appear for “pick a version.” Players who want the supported stable cut still use **[README download / Latest](../README.md)** or **Update**.

When **vr453** is eventually published as a **non-prerelease**, the dropdown gains its **first stable row at vr453**. Newer stable releases add rows; prebeta rows still never drive the update alert.

Do **not** document or implement **vr453** as stable while GitHub still has `prerelease: true`.

---

## Update alert rules (summary)

1. On open (and on a sensible refresh interval), compare the player’s **installed stable identity** to **GitHub Latest** (non-prerelease only)—same as today’s **Update** check.
2. If Latest is newer → show the existing style of “update available” prompt; **Update** installs Latest.
3. **Ignore** all releases with `prerelease: true` for that alert—including **vr453** today.
4. Installing from a **prebeta** dropdown row must **not** flip the player into “you are on Latest stable” or suppress future stable alerts incorrectly. (Installed prebeta should be labeled prebeta in UI; stable alert still tracks Latest.)

---

## Populating the dropdown (implementation sketch, public repo only)

All data comes from the **public** [GEVR releases](https://github.com/no6969el/GEVR/releases) on GitHub. **No private-repo feature**—no alternate feed, no authenticated org releases, no side-channel zips.

Suggested steps for implementers:

1. **List releases** via the GitHub REST API (paginate until tags fall below the floor), or equivalent unauthenticated fetch the starter already uses for **Update**.
2. For each release:
   - Parse tag name; **drop** if tag is older than **`vr453`** (per project tag ordering).
   - Require a Windows ship asset matching the existing pattern, e.g. **`GEVR-Beta-<tag>-win64.zip`**.
   - Classify with **`prerelease`**: `true` → prebeta group; `false` → stable group.
3. Sort each group newest-first (match GitHub’s usual ordering).
4. **Stable group empty** → show copy such as: “No stable builds in the picker yet—use **Update** or download [Latest](https://github.com/no6969el/GEVR/releases/latest) (**vr452.4** today).” Prebeta rows still list if present.
5. **Install selected row:** download that release’s zip asset URL, replace/merge the install folder using the same rules as **Update** (ship stamp, re-prepare once, keep `%LOCALAPPDATA%\GEVR` saves/settings unless the player clears cache).

**API anchors (public, no auth):**

- Latest stable: `GET https://api.github.com/repos/no6969el/GEVR/releases/latest` — **never** returns a prerelease.
- Full list: `GET https://api.github.com/repos/no6969el/GEVR/releases` — includes prereleases; each object has `"prerelease": true|false`.

---

## UI notes (for BarZ)

- **Dropdown** + optional group labels: **Stable** / **Prebeta**.
- Prebeta rows should be visually distinct (badge or suffix) so players do not confuse them with Latest.
- **Update** stays visible; it always targets **Latest** (stable), not the dropdown selection.
- Do not add a “downgrade to vr452.4 via picker” path—the floor forbids listing it. Players on an old manual unzip keep using a fresh **vr452.4** zip from the README or **Update**.

---

## Out of scope (this plan)

- Changing game code, `goldeneye.exe`, or boot knobs in this docs repo.
- Publishing zips or GitHub releases from this task.
- Private or authenticated release channels.
- Moving README **Latest** / main download off **vr452.4** (separate release decision).

---

## See also

- [BETA.md](BETA.md) — **Update** on open today; link to this plan.
- [README Install](../README.md#install-vr4524) — current stable zip.
- [packaging/rom-starter/README.md](../packaging/rom-starter/README.md) — what ships beside the starter in Beta zips.
