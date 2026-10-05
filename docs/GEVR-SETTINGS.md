# GEVR Settings - simple how-to

This page covers **GEVR Settings** in [vr454](https://github.com/no6969el/GEVR/releases/latest). For launch steps and the full control list, see the [README](../README.md) and [Controls](CONTROLS.md).

---

## Open GEVR Settings

1. Start GEVR as usual (`Start-GEVR.bat`).
2. Reach **Mission Select**.
3. Choose **GEVR Settings**. It sits next to **Select Mission**, **Multiplayer**, and **Cheat Options**.
4. Press **A** to open the page.

The row is named **GEVR Settings**. It is not named Options.

Cheat Options is the cheats row beside it. Leave that row alone unless you are using cheats.

---

## Change a setting

1. Move up or down to highlight a row.
2. Press **A** to edit that row.
3. Press **Left** or **Right** to step through the choices.
4. Press **A** again to accept, or **B** to cancel the edit.

Nothing is kept until you **Apply**.

---

## Apply (save and relaunch)

1. Highlight **Apply**.
2. Press **A**.

The game saves your choices and relaunches. That is normal. Picture size, filter, HD textures, and Visual mode need a fresh launch.

---

## Visual modes

| Mode | What you get |
|------|----------------|
| **VR** | Full headset play. |
| **XR** | A smaller screen with a black outline. |
| **Flat** | The game on the monitor. No headset. |

Change the Visual mode row, then **Apply**. Apply saves and relaunches into that mode. VR, XR, and Flat each keep the settings saved for that mode.

To come back to full VR later, set Visual mode to **VR** and Apply.

You can also start on the monitor with `Play-on-monitor.bat`.

---

## Frame rate, supersample, and filter

- **Frame rate** follows the headset unless you change it. **Fixed 90** is still available.
- **Supersample** starts at **3**.
- **Filter** starts on **bilinear**. **Point** is still available.

---

## Monitor picture

While you are in the headset, the monitor picture can be **Both**, **Left**, **Right**, or **Off**.

**Off** blanks the mirror on the desktop. You stay in the headset.

---

## HD textures on / off

**GEVR does not ship a texture pack.** The zip does not include one. Put the PNG pack in **`hdtextures\GOLDENEYE`**, next to `goldeneye.exe`. **`GOLDENEYE_HIRESTEXTURES.hts`** is the wrong file. An `.hts` file in `hdtextures` does nothing.

1. Download the PNG zip, not the `.hts` file — [GoldenEye-007-HD releases](https://github.com/GhostlyDark/GoldenEye-007-HD/releases) or [evilgames GE007 HD](https://evilgames.eu/texture-packs/ge007-hd.htm).
2. Extract it so the pictures land in **`hdtextures\GOLDENEYE`**, next to `goldeneye.exe`.
3. Turn **HD textures** **On**.
4. **Apply**.
5. The pack loads on the next boot.

**Default is Off.** Leaving it off is fine.

---

## Other rows still on the page

These rows are still there from earlier cuts:

| Row | What players usually see first |
|---|---|
| Full screen | Off |
| Window | 1280×960 |
| Game speed | Smooth 90 |
| HD textures | Off |
| Beta | None yet |
| Reset defaults | No |

**Beta** is reserved for test options later. It shows **None yet** today.

---

## Reset defaults

1. Open **GEVR Settings**.
2. Highlight **Reset defaults**.
3. Confirm **Yes**.
4. The restore follows your current Visual choice:
   - **Flat** restores monitor-friendly defaults (monitor rate, full screen, classic speed).
   - **VR** or **XR** restores headset-friendly defaults (supersample 3, follow the headset, bilinear, HD off, Visual mode VR).
5. Hit **Apply** if you want that save to relaunch now.

---

## If something looks wrong

- Did you **Apply** after changing Visual mode or HD textures?
- Flat still opening in the headset? Set Visual mode to **Flat** and Apply again.
- Picture soft after Apply? Check that **Supersample** is still **3**, or whatever you chose.
- Still stuck? Quit fully, run `Start-GEVR.bat` again, and open GEVR Settings once more.

Report bugs with headset or flat, what you changed, and what you expected. [CONTRIBUTING](../CONTRIBUTING.md).
