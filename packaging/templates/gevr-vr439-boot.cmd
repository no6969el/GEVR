@echo off
rem GEVR Beta vr439 boot. Same KEEP stack as the vr434 quality zip, then ROM starter.
rem Chair KEEP: SS3 + SrcFbo (425b), loco@90 (424b), playspace, sky/eye isolation, MSGSCALE 434.
rem Falsifiers stay off. No -Log. FOVMATCH stays off.

rem Cache stamp - bump each public Beta tag.
set GEVR_SHIP_TAG=vr439

rem --- Do not inherit dev / wrong-runtime knobs ---
set GETV_XR_FOVMATCH=
set GETV_GUN_AIM=
set GETV_REALCLOCK=
set GETV_VR_WATERTILE=
set GETV_VR_OCCLSKIP=
set GETV_VR_FOGSKIP=
set GETV_VR_DISTSKIP=

rem --- Core VR + pacing ---
set GETV_VR=1
set GETV_FPS=90
set GETV_SIMDIV=1
set GETV_SIMHZ=query
set GETV_BUDGET=120
set GETV_XR_PLAY=1
set GETV_XR_PLAY_AT=300
set GETV_XR_PLAY_STEREO=1
set GETV_XR_PLAY_SCREEN=2
set GETV_STEREO=1
set GETV_STEREO_SRC=xr
set GETV_STEREO_REBUILD=1
set GETV_STEREO_VIEWRESTORE=1
set GETV_STEREO_HUDGATE=1
set GETV_STEREO_AIMRECT=1
set GETV_STEREO_GUNOFS=1
set GETV_XR_UNITS_PER_M=100
set GETV_XR_FOVSYM=1
set GETV_XR_HEAD_TRANSLATE=1
set GETV_XR_PLAY_AUTORECENTER=1
set GETV_XR_PLAY_AUTOSCREEN=1
set GETV_XR_PLAY_FOVSCALE_CINEMA=85
set GETV_XR_PLAY_SRCRECT=full
set GETV_XR_PLAY_EYERECT=1

rem --- Sharpness KEEP (SS3 + SrcFbo). Never SS>1 without SrcFbo. ---
set GETV_SUPERSAMPLE=3
set GETV_XR_PLAY_SRCFBO=1
set GETV_SRCFBO=1
set GETV_MSGSCALE=434

rem --- Recenter + input ---
set GETV_XR_ACTIONS=1
set GETV_XR_HANDS=1
set GETV_XR_INPUT=1
set GETV_XR_RECENTER_CHORD=1
set GETV_XR_RECENTER_YAWONLY=1
set GETV_XR_TURN=1
set GETV_XR_TURN_SCALE=60
set GETV_XR_TURN_DEAD=20
set GETV_XR_BUTTONS=1

rem --- Aim / hands / playspace ---
set GETV_VR_HEADYAW=1
set GETV_VR_HEADYAW_IPD=1
set GETV_VR_HEADFRAME=2
set GETV_VR_HANDYAW=2
set GETV_VR_GUNAIM=1
set GETV_VR_PLAYSPACE=1
set GETV_VR_BODY=0
set GETV_VR_BODY_NOARMS=1
set GETV_TEX16BE=1

rem --- Sky / eye isolation ---
set GETV_VR_SKYMESH=1
set GETV_VR_SKYSCISSOR=1

set GE_VR_XR=1
