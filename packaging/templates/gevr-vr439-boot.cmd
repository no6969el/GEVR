@echo off
rem VR KEEP boot knobs for vr439. Same quality stack as public vr434 Start-GEVR.bat.
rem Applied before GevrRomStarter runs goldeneye.exe. Do not launch the exe from here.

rem Cache generation stamp - bump each public Beta tag so LocalAppData image cache rebuilds once.
set GEVR_SHIP_TAG=vr439

set GETV_FPS=90
set GETV_MSGSCALE=434
set GETV_SUPERSAMPLE=3

rem XR play / stereo. Binary reads GETV_XR_PLAY_SRCFBO, not GETV_SRCFBO.
set GE_VR_XR=1
set GETV_STEREO=1
set GETV_STEREO_MODE=1
set GETV_STEREO_OFFSET=32
set GETV_STEREO_SRC=xr
set GETV_STEREO_VIEWRESTORE=1
set GETV_STEREO_PAIRGUARD=0
set GETV_STEREO_REBUILD=1
set GETV_STEREO_REBUILD_REPORT=1
set GETV_STEREO_REBUILD_VIEWER=1
set GETV_STEREO_HUDGATE=1
set GETV_STEREO_AIMRECT=1
set GETV_STEREO_GUNOFS=1

set GETV_XR_PLAY=1
set GETV_XR_PLAY_STEREO=1
set GETV_XR_PLAY_SCREEN=2
set GETV_XR_PLAY_SRCFBO=1
set GETV_XR_PLAY_AUTORECENTER=1
set GETV_XR_RECENTER_CHORD=1
set GETV_XR_HEAD_TRANSLATE=1
set GETV_XR_ACTIONS=1
set GETV_XR_HANDS=1
set GETV_XR_BUTTONS=1
rem B/Y = Start/pause so in-game options work in headset. GETV_XR_BTN_B=weapon restores weapon-on-B.
set GETV_XR_BTN_B=start
rem Auto-Aim OFF once goldeneye.exe honors GETV_AUTOAIM (next product rebuild). Harmless if unset in current exe.
set GETV_AUTOAIM=0

set GETV_VR_SKYMESH=1
set GETV_VR_SKYSCISSOR=1
set GETV_VR_PLAYSPACE=1
set GETV_VR_HEADYAW=1

rem Falsifiers stay unset: GETV_XR_FOVMATCH, GETV_VR_WATERTILE, GETV_VR_OCCLSKIP, GETV_VR_FOGSKIP, GETV_VR_DISTSKIP.
rem Do not set GETV_STEREO_PROBE. Do not launch goldeneye.exe from this file.
