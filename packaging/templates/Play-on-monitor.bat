@echo off
setlocal
cd /d "%~dp0"

rem Flat / monitor play. No OpenXR, no stereo eyes.
rem Headset play: use Start-GEVR.bat instead.

set GEVR_SHIP_TAG=vr450.1
set GE_VR_XR=0
set GETV_STEREO=0
set GETV_STEREO_MODE=0
set GETV_FPS=60
rem Match headset boot audio pacing (gevr-vr441-boot.cmd) so flat play stays in sync.
set GETV_AUDIO_CLOCK=device
set GETV_AUDIO_QUEUE_MS=33

rem Flat QoL parity with VR ship (not XR): tank edge pull-in + stick pitch; die/continue pads; GL/rocket keepers; far-vis
set GETV_VR_TANKMOUNT=1
set GETV_VR_TANKPITCH=1
set GETV_VR_SETUPCOPY=1
set GETV_VR_ONESHOT=1
set GETV_VR_ROCKETMODEL=1
set GETV_VR_VISFAR=1
set GETV_VR_PROJSPAWN=0
set GETV_VR_TOUCHTANK=0

rem #51 flat purple explosions: same tex/VFX KEEP as VR boot sec.9 (monitor bat never called boot.cmd)
set GETV_VR_CORPSEKEEP=1
set GETV_VR_CORPSEKEEP_MAX=48
set GETV_VR_CORPSEKEEP_CEIL=440
set GETV_VR_TEXINVAL=1
set GETV_VR_TEXDLRETAG=1
set GETV_VR_VFXTMEM=1
set GETV_VR_VFXSHIFT=1
set GETV_TILE1=1
set GETV_BASETILE=1
set GETV_TMEMMAP=0
rem EXACTLY ONE 16-bit byte-order side may be on. DECODE side = TEX16BE.
set GETV_TEX16BE=1
set GETV_RGBA16BE=0
set GETV_TEX32BE=1

if not exist "%~dp0GevrRomStarter.exe" (
  echo FATAL: GevrRomStarter.exe missing. Unzip the full GEVR Beta zip.
  exit /b 1
)

"%~dp0GevrRomStarter.exe"
exit /b %ERRORLEVEL%