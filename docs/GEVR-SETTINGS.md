# GEVR Settings - simple how-to

This page covers **GEVR Settings** in [vr452.3](https://github.com/no6969el/GEVR/releases/latest). For launch steps and controls, see the [README](../README.md) and [Controls](CONTROLS.md).

---

## Open GEVR Settings

1. Start GEVR as usual (`Start-GEVR.bat`).
2. Load your save and reach **Mode Select** (Mission / Multiplayer screen).
3. Move to **GEVR Settings** (under Select Mission and Multiplayer).
4. Press **A** (or your confirm button) to open the page.

**Tip:** Cheat Options is a separate row when cheats are unlocked - leave that alone unless you are using cheats.

---

## Change a setting

1. Move up / down to highlight a row.
2. Press **A** to enter that row (the value lights up).
3. Press **Left / Right** to step through choices.
4. Press **A** again to accept, or **B** to cancel the edit.

Nothing is permanent until you **Apply**.

---

## Apply (save and relaunch)

1. Highlight **Apply**.
2. Press **A**.

The game **saves your choices and restarts**. That is normal - picture size, filter, HD, and Visual mode need a fresh launch.

After the restart you should see the new values stick (including supersample).

---

## Visual modes

| Mode | Best for | What happens |
|------|----------|----------------|
| **VR** | Everyday headset play | Full immersive VR. |
| **XR** | A framed / cinema feel | Headset view with a clean square outline. |
| **Flat** | Desk / couch on a monitor | No headset - full-screen monitor play. |

Pick the mode -> **Apply** -> wait for the relaunch.

To go back to full VR later: set Visual to **VR** -> **Apply**.

---

## HD textures on / off

**GEVR does not ship a texture pack.** Download the **GLideN64 PNG** zip (**not** `.hts`) from [GoldenEye-007-HD releases](https://github.com/GhostlyDark/GoldenEye-007-HD/releases) or [evilgames GE007 HD](https://evilgames.eu/texture-packs/ge007-hd.htm). Extract so the **`GOLDENEYE`** folders sit inside **`hdtextures`** next to `goldeneye.exe`. Do not rename files.

1. Open **GEVR Settings**.
2. Find **HD textures** and set **On**.
3. **Apply**, then play on the **next boot**.

**Default is Off.** Leaving it off is fine — the game looks good without a pack.

---

## Reset defaults

Want a clean starting point?

1. Open **GEVR Settings**.
2. Highlight **Reset defaults**.
3. Confirm **Yes** (Are you sure?).
4. The restore follows your **current Visual choice**:
   - **Flat** Visual -> Flat-friendly defaults (monitor rate, full screen, classic speed).
   - **Anything else** -> VR-friendly defaults (supersample 3, follow headset, bilinear, HD off, Visual VR).
5. Hit **Apply** if you want that save to relaunch now.

---

## Frame rate and game speed (short)

- **Headset play:** prefer following the headset so the game matches your display.
- **Flat / monitor:** you can follow the monitor rate and pick Original 60 or Smooth 90 for game speed.
- Use the menu - no special scripts required.

---

## If something looks wrong

- Did you **Apply** after changing Visual or HD?
- Flat still opening in VR? Set Visual to **Flat** and Apply again.
- Picture soft after Apply? Check **Supersample** is still what you want (default 3).
- Still stuck? Quit fully, run `Start-GEVR.bat` again, and open Settings once more.

Report bugs with: headset or flat, what you changed, and what you expected. [CONTRIBUTING](../CONTRIBUTING.md).
