# RUN SHEET 283 — the two switches that decide whether the rectangles are guilty

**2026-08-31. Both switches are in `vendor/ge-decomp/src/game/bg.c`, both behind
`#ifdef GE_PORT_NATIVE`, BOTH DEFAULT OFF.** The matching build is untouched: with neither switch
set the game does exactly what it did before, so arm A doubles as its own control.

---

## §0 — WHY THESE TWO, IN PLAIN TERMS

We have measured where the holes start: exactly on the edge of the rectangle a room is allowed to
paint inside. What we have **not** shown is that the rectangle is what *causes* them. The edge of a
rectangle and the edge of a room's paint are in the same place either way — whether the rectangle
cut something, or whether nothing was ever going to be painted there.

**`283` §3 is the reason to be careful.** The one straddling doorway we looked at had three sides
of its rectangle blow up and one side stay at `90.71`. For a doorway you are standing inside,
"runs off screen left, top and bottom, real edge on the right" is what you would *expect* — and no
repair to the trimming moves that right edge. So `281`'s fix might well change nothing.

**Switch 1 settles the whole class in one look.** Give every room the entire screen to paint in.
- **Holes gone** → the rectangles really were cutting pixels nothing else covers. A proper fix has
  to make them wider in the right way, and we go looking for how.
- **Holes still there** → the rectangles are innocent, every edge match we measured is a
  coincidence of position, and the real answer is that **no room owns those pixels at all** —
  a missing wall or a room that was never added to the list.

**Switch 2 is `281`'s cheap patch, built so it can be measured instead of argued.** A doorway that
crosses behind your head hands back its parent's rectangle instead of its own.

**Expect switch 1 to make the picture worse in other ways.** With no per-room rectangle, rooms
paint over each other — you will see walls through walls and rooms that should be hidden.
**That is expected and is not a second bug. Judge the SLABS only.** It must never ship on.

---

## §1 — BUILD

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native
& getv\build_windows.ps1 -Target all *> build_283_switches.log 2>&1
Select-String -Path build_283_switches.log -Pattern 'error|Error|FAILED' | Select-Object -First 20
Get-Item F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows\goldeneye.exe |
    Select-Object FullName, LastWriteTime, Length
$exe = 'F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows\goldeneye.exe'
$txt = [Text.Encoding]::ASCII.GetString([IO.File]::ReadAllBytes($exe))
foreach ($k in 'GETV_ROOMSCISSOR','GETV_PORTALOPEN','GETV_PORTALBOX') {
    if ($txt.Contains($k)) { "$k IS IN THE BINARY" } else { "$k IS **NOT** IN THE BINARY -- STOP" }
}
```
**All three must say IS IN.** The timestamp must be newer than `2026-08-30 20:43:56`.

## §2 — ARM A: every room gets the whole screen

Walk to the same spot as before. **Stand still, artifact on screen, F9 twice.** Then quit normally.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
$env:GETV_ROOMSCISSOR = "0"
$env:GETV_WIDESCREEN  = "0"
$env:GETV_SIMDIV      = "1"
$env:GETV_FPS         = "60"
$env:GETV_VSYNC       = "0"
$env:GETV_STAGE       = "29"
$env:GETV_WINDOW      = "2560x1369"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_283_A_roomscissor_off.log 2>&1
Select-String -Path run_283_A_roomscissor_off.log -Pattern 'roomscissor\] GETV_ROOMSCISSOR=0|\[getv\] window:|game_exit requested'
Select-String -Path run_283_A_roomscissor_off.log -Pattern 'VIEWPORT n64' | Select-Object -First 1
(Select-String -Path run_283_A_roomscissor_off.log -Pattern 'dlgrab_\d+\.txt' -AllMatches).Matches.Value | Sort-Object -Unique
```
**The `roomscissor]` banner must appear, or the switch did not take and the arm is a clean null.**
**TELL ME WHAT YOU SAW**, in your own words: are the see-through slabs gone, smaller, or the same?
Your eyes are the instrument for this one; the dump is only corroboration.

## §3 — ARM B: `281`'s patch, on its own

Same spot, same routine.

```powershell
Remove-Item Env:GETV_* -ErrorAction SilentlyContinue
Set-Location F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\getv\build-windows
Get-Item .\goldeneye.exe | Select-Object FullName, LastWriteTime, Length
$env:GETV_PORTALOPEN = "1"
$env:GETV_WIDESCREEN = "0"
$env:GETV_SIMDIV     = "1"
$env:GETV_FPS        = "60"
$env:GETV_VSYNC      = "0"
$env:GETV_STAGE      = "29"
$env:GETV_WINDOW     = "2560x1369"
Get-ChildItem Env:GETV_* | Format-Table -AutoSize
.\goldeneye.exe *> run_283_B_portalopen.log 2>&1
Select-String -Path run_283_B_portalopen.log -Pattern 'portalopen\] GETV_PORTALOPEN=1|\[getv\] window:|game_exit requested'
Select-String -Path run_283_B_portalopen.log -Pattern 'VIEWPORT n64' | Select-Object -First 1
(Select-String -Path run_283_B_portalopen.log -Pattern 'dlgrab_\d+\.txt' -AllMatches).Matches.Value | Sort-Object -Unique
```

## §4 — WHAT EACH RESULT MEANS. WRITTEN BEFORE THE RUNS.

| arm A | arm B | reading |
|---|---|---|
| slabs GONE | — | the rectangles are the cause. Next: why they come out narrow, and a real fix |
| slabs GONE | slabs GONE | **and `281` was right end to end** — the straddle is the narrowing |
| slabs GONE | slabs STAY | rectangles guilty, but NOT because of the straddle. `281` patch 2 is dead |
| slabs STAY | slabs STAY | **rectangles innocent.** Every edge match is positional coincidence. The cause is that nothing owns those pixels — a missing room or a missing wall. `280` §8.1 predicted this is the more valuable outcome |
| slabs STAY | slabs GONE | contradiction — B is a subset of A. Something is wrong with the build; stop and tell me |

## §5 — SEND BACK
Both logs, both dump pairs, and **one sentence per arm in your own words about what the screen
looked like.** For arm A, the sentence matters more than the dump.

## §6 — COMMITTING
`bg.c` lives in the decomp repo, which **`COMMIT-NOW.cmd` does not cover** (`00-STATE` §6), and it
must be added **by name** — `git add -A` there would sweep 2,106 line-ending-only files. `gfx_pc.c`
is untouched, so no regen. Nothing goes in until an arm has told us something.
