@echo off
setlocal
cd /d "%~dp0"

rem GEVR Beta vr438 - always launch through the ROM starter (BYO-ROM).
rem Do not run the game binary directly; cache, GEVR_SHIP_TAG, and VR boot env are set here.

call "%~dp0gevr-vr438-boot.cmd"

if not exist "%~dp0GevrRomStarter.exe" (
  echo FATAL: GevrRomStarter.exe missing. Re-download the full GEVR Beta zip.
  exit /b 1
)

"%~dp0GevrRomStarter.exe"
exit /b %ERRORLEVEL%
