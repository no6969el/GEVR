# RUN SHEET 282 — the portal box probe

**Written 2026-08-31. The change is in `vendor/ge-decomp/src/game/bg.c` ONLY. It PRINTS. It
changes nothing about how the game draws.**

---

## §0 — WHAT WE ARE ASKING, IN PLAIN TERMS

The level is rooms joined by doorways. Every frame the game asks two separate questions:

1. **"Can I see into the next room from here?"** If yes, that room's walls get drawn.
2. **"While drawing that room, which rectangle of the screen am I allowed to paint in?"**
   That rectangle is meant to be the doorway, as it appears on screen.

The hole you are seeing is question 2 handing back a rectangle **smaller than the doorway
actually is**. The next room is allowed to draw, but only inside a box that stops short — and the
strip past the edge of that box never gets painted by anything, so you see straight through to the
sky. That is why the edge is dead straight and perfectly vertical: it is the edge of a rectangle,
not the edge of a wall.

We have measured that edge in **eight** different frames now and every time it lands on one of
those rectangles, to within a pixel. **What we do NOT know is why the rectangle comes out too
small.** This run answers that, and it answers it by printing numbers — nothing is changed.

**There are two competing explanations and this run separates them:**

- **`281`'s** (the doc from outside): when you stand close to a doorway, part of the doorway is
  behind your head. The game throws those corners away instead of trimming them, so the box it
  measures is only the part in front — too small.
- **Mine (`282`)**: the game already trims them, and when it does the result comes out
  **enormous**, not small — which then gets clipped back to something safe. If I am right, the
  too-small boxes are coming from doorways that were **entirely in front of you**, and `281`'s
  explanation cannot be the cause of any frame we have.

**Both of us wrote down what the run must show. One of us is going to be wrong, and that is the
point.**

---

## §1 — STEP A: BUILD

**ONE BLOCK. The last three lines are the block checking itself — if the knob is not in the
binary, every number below is a clean null (`133`, `268` §4).**

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
& getv\build_windows.ps1 -Target all *> build_282_portalbox.log 2>&1
Select-String -Path build_282_portalbox.log -Pattern 'error|Error|FAILED' | Select-Object -First 20
Get-Item F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows\goldeneye.exe |
    Select-Object FullName, LastWriteTime, Length
$exe = 'F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows\goldeneye.exe'
$txt = [Text.Encoding]::ASCII.GetString([IO.File]::ReadAllBytes($exe))
if ($txt.Contains('GETV_PORTALBOX')) { "GETV_PORTALBOX IS IN THE BINARY" }
else { "GETV_PORTALBOX IS **NOT** IN THE BINARY -- STOP, THE RUN BELOW IS A CLEAN NULL" }
```

**The timestamp must be newer than `2026-08-30 20:05:55`** (that is the binary every run from
`277` to `280` used).

---

## §2 — STEP B: THE RUN

Same place as run A. Walk until a see-through slab is on screen, **stand still**, press **F9**
twice, then quit normally so the log gets its closing line.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
$env:GETV_PORTALBOX     = "1"
$env:GETV_PORTALBOX_MAX = "600000"
$env:GETV_WIDESCREEN    = "0"
$env:GETV_SIMDIV        = "1"
$env:GETV_FPS           = "60"
$env:GETV_VSYNC         = "0"
$env:GETV_STAGE         = "29"
$env:GETV_WINDOW        = "2560x1369"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_282_P1_portalbox.log 2>&1
Select-String -Path run_282_P1_portalbox.log -Pattern 'pbox\] GETV_PORTALBOX=1|\[getv\] window:|game_exit requested|BUDGET SPENT'
Select-String -Path run_282_P1_portalbox.log -Pattern 'VIEWPORT n64' | Select-Object -First 1
(Select-String -Path run_282_P1_portalbox.log -Pattern 'dlgrab_\d+\.txt' -AllMatches).Matches.Value | Sort-Object -Unique
"log size MB: {0:N1}" -f ((Get-Item run_282_P1_portalbox.log).Length/1MB)
```

**Four things that must appear, and what it means if one does not:**

| must appear | if it is missing |
|---|---|
| `[getv][pbox] GETV_PORTALBOX=1 ... ARMED` | the knob did not take — **stop**, nothing below is valid |
| `[getv] window: 2560x1369` | wrong window; the pixel maths in the analysis will not line up |
| `ours: x=367.333 y=171.125` | **widescreen did not turn off** — with it on that number goes near 0 |
| `game_exit requested` | the log is unfinished and must not be read as "no crash" (`262` §5) |

**`BUDGET SPENT` appearing is not a failure** — it means the probe hit its line limit and stopped
printing. It says so on purpose rather than going quiet. If it appears **before** your F9, re-run
with `GETV_PORTALBOX_MAX = "2000000"`. **The log will be large — expect 30-80 MB.** That is fine
for one run and is why the knob is off by default.

---

## §3 — WHAT THE PROBE PRINTS, LINE BY LINE

Three kinds of line. All coordinates are the game's own screen units (0-320 across, 0-240 down);
the F9 dump writes the same numbers multiplied by four.

```
[getv][pbox] f=2655 port=41 npts=4 gen=6 drop=2 cross=2 raw=(...) out=(...) NORMAL
```
One doorway, measured. `npts` = corners the doorway has. `gen` = points the game ended up working
from. **`drop`** = corners that were behind you and got thrown away. **`cross`** = trim points the
game added where the doorway crosses behind you. `raw` = the box straight out of the measurement,
before any safety clamps. `out` = the box after them. `HUGE` on the end means the raw box came out
astronomically large.

```
[getv][pbox] f=2655 NEW   room=9 in=(...) roomaabb=(...) infront=5/8
```
A room being added to the draw list with the box it is allowed to paint in (`in`), next to where
that whole room actually sits on screen (`roomaabb`). **The box being smaller than the room is
normal and expected** — that is what a doorway does. It is here to show by how much.

```
[getv][pbox] f=2655 FRAME rooms=2 cachehits=17
```
End of frame. `cachehits` matters: the game remembers each doorway's box within a frame, so a
doorway answered from memory prints no line of its own. Without this count, "no line" and "nothing
happened" would look identical.

---

## §4 — WHAT EACH ANSWER MEANS. WRITTEN DOWN BEFORE THE RUN.

Find the F9 frame number, then look at the `pbox` lines with that `f=` and find the box whose `out`
matches the rectangle the hole's edge sits on.

- **`drop` is more than 0, `cross` is more than 0, and `raw` is small** →
  **`281` is right.** The doorway was partly behind you and the measurement came out too tight.
  Then we write the trim properly. This is the outcome `281` predicts.
- **`drop` is 0 on that doorway** → **`281`'s explanation does not apply**, and `281` itself says
  to stop there rather than patch anyway. The doorway was entirely in front of you and the box is
  still too small, so the question moves to *why nothing paints the strip beyond a box that is
  arguably correct* — probably a neighbouring room that never got added at all. (`278` §3 measured
  only **two** rooms being drawn at the faulted spot, which is the standing hint.)
- **Straddling doorways show `HUGE` and get clamped** → **my `282` §2 is right**, and `281`'s
  second, cheaper patch is a no-op because the game already does it.
- **`cross` is 0 everywhere** → my reading of the trim code is wrong; `282` §2.1 is retracted.
- **No printed `out` box matches any rectangle in the F9 dump** → **the probe is not watching the
  code that made those rectangles and every number it printed is void.** Stop and tell me.

---

## §5 — SEND BACK

`run_282_P1_portalbox.log`, and the `dlgrab_*.txt` + `.bmp` pair it announces. Nothing else.
I will do the matching.

---

## §6 — TWO THINGS ABOUT COMMITTING THIS, WHICH ARE TRAPS

- **The edited file lives in the decomp repo (`goldeneye-native\vendor\ge-decomp`), and
  `COMMIT-NOW.cmd` DOES NOT COVER IT.** It never has (`00-STATE` §6). A session whose only change
  is this one commits **nothing** if you just double-click that script.
- **When it is committed, commit `src/game/bg.c` BY NAME.** `git add -A` in the decomp would sweep
  in 2,106 files that differ only by line endings — that has already happened once in the history.
- `gfx_pc.c` is **not** touched by this change, so **no regen is needed**.
- Nothing here should be committed until the probe has actually told us something.
