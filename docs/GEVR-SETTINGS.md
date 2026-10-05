# GEVR Settings - simple how-to

This page covers **GEVR Settings** in [vr456.1](https://github.com/no6969el/GEVR/releases/tag/vr456.1). For launch steps, see the [README](../README.md#install). For binds, see [Controls](CONTROLS.md). How to play: [Start here](00-START-HERE.md).

Ammo digits, the hip holster, weapon pictures, and chest reload stay on without boot knobs. They are not rows on this page.

---

## Open GEVR Settings

1. Start GEVR as usual (`Start-GEVR.bat`).
2. Reach **Mission Select**.
3. Move to **GEVR Settings**. It sits next to **Select Mission**, **Multiplayer**, and **Cheat Options**.
4. Press **A** to open the page.

The page is named **GEVR Settings**. It is not named Options.

---

## Change a setting

1. Move up or down to highlight a row.
2. Press **A** to enter that row.
3. Press **Left** or **Right** to step through the choices.
4. Press **A** again to accept, or **B** to cancel the edit.

Nothing is saved until you **Apply**.

---

## Apply (save and relaunch)

1. Highlight **Apply**.
2. Press **A**.

Apply saves your choices and relaunches into that mode. Picture size, filter, HD textures, and Visual mode need a fresh launch.

---

## Visual modes

| Mode | What you get |
|------|----------------|
| **VR** | Full headset play. |
| **XR** | A smaller screen with a black outline. |
| **Flat** | The game on the monitor. |

Change the Visual mode row, then **Apply**.

To go back to full VR later: set Visual to **VR**, then **Apply**. Each mode keeps its own saved settings.

---

## Frame rate, supersample, and filter

- Frame rate follows the headset by default. **Fixed 90** is still available.
- Supersample starts at **3**.
- The texture filter starts on **bilinear**. **Point** is still available.

Use the menu. You do not type a special command.

---

## Monitor picture

While you play in VR or XR, the monitor row can be **Both**, **Left**, **Right**, or **Off**.

**Off** blanks the mirror on the monitor while you stay in the headset.

The row is greyed out in Flat. The choice is saved with the VR and XR settings.

---

## HD textures

HD textures are beta. They can stutter, including on a fast card.

The zip has no texture pack. PNG packs go in `hdtextures\GOLDENEYE` next to `goldeneye.exe`. `GOLDENEYE_HIRESTEXTURES.hts` is the wrong file. An `.hts` file in `hdtextures` does nothing.

1. Download a GLideN64 PNG zip. [GoldenEye-007-HD releases](https://github.com/GhostlyDark/GoldenEye-007-HD/releases) or [evilgames GE007 HD](https://evilgames.eu/texture-packs/ge007-hd.htm).
2. Put the pictures in `hdtextures\GOLDENEYE`, next to `goldeneye.exe`.
3. Turn **HD textures** **On**.
4. **Apply**.
5. The pack loads on the next boot.

The row starts at **Off**. Leaving it off is fine.

---

## Reset defaults

1. Open **GEVR Settings**.
2. Highlight **Reset defaults**.
3. Confirm **Yes**.
4. The restore follows your current Visual choice:
   - **Flat** restores monitor-friendly defaults.
   - Any other Visual mode restores VR-friendly defaults: supersample 3, frame rate follows the headset, bilinear filter, HD off, Visual VR.
5. Hit **Apply** if you want that save to relaunch now.

---

## If something looks wrong

- Did you **Apply** after changing Visual mode or HD textures?
- Flat still opening in VR? Set Visual to **Flat** and Apply again.
- Picture soft after Apply? Check that **Supersample** is still what you want. The start value is 3.
- Still stuck? Quit fully, run `Start-GEVR.bat` again, and open **GEVR Settings** once more.

Report bugs with the headset or flat, what you changed, and what you expected. [CONTRIBUTING](../CONTRIBUTING.md).
