# GEVR Settings - simple how-to

This page covers **GEVR Settings** in [vr457](https://github.com/no6969el/GEVR/releases/latest). For launch steps and controls, see the [README](../README.md) and [Controls](CONTROLS.md).

---

## Open GEVR Settings

1. Start GEVR as usual (`Start-GEVR.bat`).
2. Reach **Mission Select**.
3. Move to **GEVR Settings**. It sits next to **Select Mission**, **Multiplayer**, and **Cheat Options**.
4. Press **A** to open it.

The page is named **GEVR Settings**. It is not named Options. In VR you look at that glass on the intro hub.

The first page lists the categories: **GRAPHICS**, **VR**, **HANDS AND GUNS**, **WEATHER**, **ENEMY AI** and **BETA**, then **RESET DEFAULTS** and **APPLY**. Each category shows its current value or a short summary. Press **A** on a category to open its page; **B** goes back.

---

## Change a setting

1. Move up or down to highlight a row.
2. Press **A** to enter that row.
3. Press **Left** or **Right** to step through the choices.
4. Press **A** again to accept, or **B** to cancel the edit.

Nothing is saved until you choose **APPLY** on the first page. Apply saves your choices; rows that need it restart the game into your choice (weather rows take effect at the next level load).

---

## The pages

| Page | Row | What it does |
|---|---|---|
| **GRAPHICS** | **VR RENDER SCALE** (SUPERSAMPLE in Flat) | 50 to 150 percent of the headset's recommended picture size, in steps of 5. Above 100 is sharper and heavier; below 100 is faster and softer. Flat mode keeps Supersample 1 / 2 / 3. |
| | **WINDOW** | Window size. The headset picture does not depend on it. |
| | **FILTER** | 3-point, bilinear, or point. |
| | **FRAME RATE** | Headset follow by default. Fixed rates must match your headset. |
| | **GAME SPEED** | Monitor play only. |
| | **HD TEXTURES** | Use the HD pack in `hdtextures\GOLDENEYE` if you installed one. The zip has none. |
| **VR** | **VISUAL MODE** | VR, XR (smaller screen with a black outline), or Flat. Each mode keeps its own saved settings. |
| | **MONITOR OUTPUT** | What the desktop window shows while you play in VR: both eyes, left, right, or no picture. Grey in Flat. |
| | **TURN SPEED**, **TURN STYLE**, **SNAP SIZE** | How the right stick turns you: speed, smooth or snap, and the snap angle. |
| **HANDS AND GUNS** | **HANDS AND ARMS** | On (default) = new hands and sleeves, arms from the body, guns drawn from the jacket and over the shoulders. Off = the old hands and the hip holsters. VR and XR only; grey in Flat. |
| | **AMMO ON GRIP** | Ammo digits on the gun in VR. Always on in VR. |
| | **AUTO PICKUP** | On (default) = walking over a gun collects it. Off = walking over it leaves it; grab or pull it. |
| | **STICK WHEEL** | Stick click opens a circle of guns (default) or a column. |
| **WEATHER** | **WEATHER** | Off, Original (default, the game as it was), Enhanced, or Dynamic. |
| | **INTENSITY**, **WEATHER TYPE** | Light to Extreme; Auto (each level picks) or one named weather. |
| | **GROUND EFFECTS**, **LIGHTNING FLASHES**, **AFFECTS ENEMIES** | Splashes, prints in snow and wet floors; storm flashes (thunder stays); whether fog and storms hinder Tactical guards. |
| | **SEED** | Random, or a fixed number for the same changing weather each time. |
| **ENEMY AI** | **ENEMY AI** | Classic (default, the original guards), Tactical, or Tactical+. |
| | **AGGRESSION** | Calm, Normal, Aggressive or Ruthless. Only with Tactical or Tactical+. |
| **BETA** | **UPSCALER** | Off, DLSS Quality, Balanced, Performance, or DLAA. Needs an RTX card and NVIDIA's own files next to `goldeneye.exe` (not in the zip). Without them the game stays on plain OpenGL. |
| | **HD TEXTURE SET** | Off, GE007 HD, GEVR Curated, or Curated plus AI fills. Needs the folder on your own disk. With no folder the game keeps HD off and says so in its log. |
| (first page) | **RESET DEFAULTS** | Restores the defaults for the current Visual mode: Hands ON, Weather Original, Enemy AI Classic, Auto pickup ON, Beta rows off. |
| | **APPLY** | Saves and restarts where needed. |

**Status in vr457.** The settings pages, HANDS AND ARMS (on by default), AUTO PICKUP, WEATHER (Enhanced and Dynamic) and ENEMY AI (Tactical and Tactical+) are **New**: built and checked on the bench, not yet tested in a headset. Classic enemy AI and Original weather are the safe defaults. The VR render scale is **Passed** in a headset on an earlier test build.

---

## Visual modes

| Mode | What you get |
|------|----------------|
| **VR** | Full headset play. |
| **XR** | A smaller screen with a black outline. |
| **Flat** | The game on the monitor. |

Change the Visual mode row, then **Apply**. To go back to full VR later: set Visual to **VR**, then **Apply**.

---

## STICK WHEEL, snap-turn, comfort

These rows sit in **GEVR Settings** and under pause **VR SETTINGS** (scroll past ratio on GAME OPTIONS).

| Row | What it does |
|---|---|
| **STICK WHEEL** | **Weapon wheel** (circle, default) or **Weapon Vert** (column). Next stick-click uses the new style. No reboot. |
| **Turn style / snap size** | **Snap** uses real degrees: 15 / 22.5 / 30 / 45 / 60 / 90. The glass is click-to-edit. |
| Comfort | VR has no walk bob, landing dip, or gun-hand sway in this cut. |

Stick **click** opens the weapon wheel. Centre follows your hover. Boxes are 2x dark grey. **Both** stick clicks still **recenter**.

Red and green **aimers** sit on the shot's first hit (not a settings row; always on in this cut).

---

## HD textures on / off

**GEVR does not ship a texture pack.** The zip has no pack. If `hdtextures` only has `GOLDENEYE_HIRESTEXTURES.hts`, that is the wrong file. An `.hts` file in `hdtextures` does nothing.

1. Download a GLideN64 **PNG** zip, not the `.hts` file. [GoldenEye-007-HD releases](https://github.com/GhostlyDark/GoldenEye-007-HD/releases) or [evilgames GE007 HD](https://evilgames.eu/texture-packs/ge007-hd.htm).
2. Put the pictures in `hdtextures\GOLDENEYE`, next to `goldeneye.exe`.
3. Turn **HD textures** **On**.
4. **Apply**.
5. The pack loads on the next boot.

**Default is Off.** Leaving it off is fine.

Decoded HD pictures stay in memory (HD memo overlay, 1 GB cap) so they stutter less. `GETV_HD_MEMO_MB=0` turns that overlay off.

---

## Your saved choices win

A fresh install starts with the defaults above (hands and arms on, weather Original, enemy AI Classic, auto pickup on, upscaler off). Anything you save with Apply is kept and beats them, also after you update. **Reset defaults** and Apply puts the defaults back.

---

## If something looks wrong

- Did you **Apply** after changing a row?
- Flat still opening in VR? Set Visual to **Flat** and Apply again.
- A Beta row misbehaving? Turn it off, Apply, and report what you saw.
- Still stuck? Quit fully, run `Start-GEVR.bat` again, and open **GEVR Settings** once more.

Report bugs with the headset or flat, what you changed, and what you expected. [CONTRIBUTING](../CONTRIBUTING.md).
