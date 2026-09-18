@echo off
setlocal
cd /d "%~dp0"

rem Flat / monitor play. No OpenXR, no stereo eyes.
rem Headset play: use Start-GEVR.bat instead.

set GEVR_SHIP_TAG=vr441
set GE_VR_XR=0
set GETV_STEREO=0
set GETV_STEREO_MODE=0
set GETV_FPS=60
rem Match headset boot audio pacing (gevr-vr441-boot.cmd) so flat play stays in sync.
set GETV_AUDIO_CLOCK=device
set GETV_AUDIO_QUEUE_MS=33

if not exist "%~dp0GevrRomStarter.exe" (
  echo FATAL: GevrRomStarter.exe missing. Unzip the full GEVR Beta zip.
  exit /b 1
)

"%~dp0GevrRomStarter.exe"
exit /b %ERRORLEVEL%