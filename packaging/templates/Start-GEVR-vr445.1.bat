@echo off
setlocal
cd /d "%~dp0"

rem GEVR Beta vr445.1 - ROM starter + KEEP VR boot.
call "%~dp0gevr-vr445.1-boot.cmd"

if not exist "%~dp0GevrRomStarter.exe" (
  echo FATAL: GevrRomStarter.exe missing. Re-download the full GEVR Beta zip.
  exit /b 1
)

"%~dp0GevrRomStarter.exe"
exit /b %ERRORLEVEL%
