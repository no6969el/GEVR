@echo off
setlocal EnableExtensions
rem ===========================================================================
rem  Drop this NEXT TO Start-GEVR.bat / gevr-vr*-boot.cmd in the GEVR folder.
rem  Same launch as Start-GEVR, but pins GETV_FPS=90 AFTER the ship boot wipe
rem  so Quest 90 Hz can open the headset window when Hertz-follow needs a pin.
rem  Dig other rates: edit the set line below (72 / 80 / 90 / 120).
rem ===========================================================================
cd /d "%~dp0"

set "GEVR_BOOT="
if exist "%~dp0gevr-vr445-boot.cmd" set "GEVR_BOOT=%~dp0gevr-vr445-boot.cmd"
if not defined GEVR_BOOT if exist "%~dp0gevr-vr444.1-boot.cmd" set "GEVR_BOOT=%~dp0gevr-vr444.1-boot.cmd"
if not defined GEVR_BOOT if exist "%~dp0gevr-vr444-boot.cmd" set "GEVR_BOOT=%~dp0gevr-vr444-boot.cmd"
if not defined GEVR_BOOT if exist "%~dp0gevr-vr443.1-boot.cmd" set "GEVR_BOOT=%~dp0gevr-vr443.1-boot.cmd"

if not defined GEVR_BOOT (
  echo FATAL: no gevr-vr*-boot.cmd in:
  echo   %~dp0
  echo Put this bat in the GEVR install folder ^(same place as Start-GEVR.bat^).
  pause
  exit /b 1
)

if not exist "%~dp0GevrRomStarter.exe" (
  echo FATAL: GevrRomStarter.exe missing in:
  echo   %~dp0
  echo Re-download the full GEVR Beta zip, or put this bat in that folder.
  pause
  exit /b 1
)

call "%GEVR_BOOT%"
if errorlevel 1 (
  echo FATAL: boot returned %ERRORLEVEL%
  pause
  exit /b 1
)

rem AFTER boot on purpose -- boot clears GETV_FPS for HMD-follow.
set GETV_FPS=90
set GETV_SIMHZ=query
set GETV_VR=1
set GETV_XR_PLAY=1

echo.
echo GEVR-Quest-Pin90: GETV_FPS=%GETV_FPS%  ^(emergency pin^)
echo Boot: %GEVR_BOOT%
echo.

"%~dp0GevrRomStarter.exe"
exit /b %ERRORLEVEL%
