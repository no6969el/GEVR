@echo off
setlocal EnableExtensions
cd /d "%~dp0"

rem GEVR player log - put this next to Start-GEVR.bat, then double-click.

set "LOG=%~dp0gevr-player-log.txt"
set "GEVR_LOCAL=%LOCALAPPDATA%\GEVR"

echo.
echo ============================================================
echo  GEVR - make a log for headset problems
echo ============================================================
echo.

if not exist "%~dp0goldeneye.exe" (
  echo This file is in the wrong folder.
  echo.
  echo 1. Open your GEVR game folder ^(the one with Start-GEVR.bat^).
  echo 2. Copy this file into that folder.
  echo 3. Double-click it there.
  echo.
  pause
  exit /b 1
)

set "BOOT="
if exist "%~dp0gevr-vr445-boot.cmd" set "BOOT=%~dp0gevr-vr445-boot.cmd"
if not defined BOOT if exist "%~dp0gevr-vr444.1-boot.cmd" set "BOOT=%~dp0gevr-vr444.1-boot.cmd"
if not defined BOOT if exist "%~dp0gevr-vr444-boot.cmd" set "BOOT=%~dp0gevr-vr444-boot.cmd"
if not defined BOOT (
  for %%F in ("%~dp0gevr-*-boot.cmd") do if not defined BOOT set "BOOT=%%~fF"
)
if not defined BOOT (
  echo Something is missing from your GEVR folder.
  echo Re-download the game zip from GitHub, then try again.
  pause
  exit /b 1
)

if exist "%GEVR_LOCAL%\game.path" del /f /q "%GEVR_LOCAL%\game.path" >nul 2>&1

call "%BOOT%"
ver >nul

rem Re-assert VR after boot (some shells drop env; desktop-only runs look like "headset broken").
set GETV_VR=1
set GE_VR_XR=1
set GETV_XR_PLAY=1
set GETV_STEREO=1
set GETV_VSYNC=0
set GETV_SIMHZ=query
set GETV_ARM=PLAYER-LOG

echo === GEVR player log === > "%LOG%"
echo DATE=%DATE% TIME=%TIME%>> "%LOG%"
echo DIR=%CD%>> "%LOG%"
echo BOOT=%BOOT%>> "%LOG%"
echo GEVR_SHIP_TAG=%GEVR_SHIP_TAG%>> "%LOG%"
echo GETV_VR=%GETV_VR% GETV_XR_PLAY=%GETV_XR_PLAY% GETV_VSYNC=%GETV_VSYNC% GETV_FPS=[%GETV_FPS%] GETV_SIMHZ=[%GETV_SIMHZ%]>> "%LOG%"
echo ARM=%GETV_ARM%>> "%LOG%"
echo.>> "%LOG%"

set "GEVR_ROM_PATH="
set "GEVR_ROM_SHA256="
if exist "%GEVR_LOCAL%\rom.path" for /f "usebackq delims=" %%I in ("%GEVR_LOCAL%\rom.path") do set "GEVR_ROM_PATH=%%I"
if exist "%GEVR_LOCAL%\rom.sha256" for /f "usebackq delims=" %%I in ("%GEVR_LOCAL%\rom.sha256") do set "GEVR_ROM_SHA256=%%I"
if defined GEVR_ROM_PATH set "GEVR_CACHE_DIR=%GEVR_LOCAL%\cache"

if defined GEVR_ROM_PATH if exist "%GEVR_ROM_PATH%" if exist "%~dp0gevr_prepare.exe" (
  echo Getting your game files ready...
  echo --- prepare --->> "%LOG%"
  "%~dp0gevr_prepare.exe" "%GEVR_ROM_PATH%" >> "%LOG%" 2>&1
  echo prepare_exit=%ERRORLEVEL%>> "%LOG%"
  echo.>> "%LOG%"
  ver >nul
)

echo.
echo Before you continue:
echo   - Put your headset on / start your usual PC VR app
echo     ^(for Quest that is usually Virtual Desktop^)
echo   - In Virtual Desktop, OpenXR runtime = Virtual Desktop
echo   - Make sure the headset is connected to the PC
echo.
echo Press any key to start the game.
echo When the problem happens ^(or if VR never starts^), quit the game.
echo.
pause

echo --- game --->> "%LOG%"
"%~dp0goldeneye.exe" >> "%LOG%" 2>&1
set "RC=%ERRORLEVEL%"
echo.>> "%LOG%"
echo exit_code=%RC%>> "%LOG%"

echo.
echo ============================================================
echo  Done.
echo.
echo  Send this file to BarZ on Discord:
echo    gevr-player-log.txt
echo  ^(it is in your GEVR folder - we opened it for you^)
echo.
echo  Do NOT send your Nintendo ROM file.
echo ============================================================
echo.
explorer /select,"%LOG%"
pause
exit /b %RC%