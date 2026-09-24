rem GEVR Beta vr443 - internal cook 453
@echo off
rem GEVR Beta vr443 boot - cook 453 ship knobs.
rem
rem vr440 shipped the picture KEEP only: the chair features (corpses, explosion
rem texture, the PLAY0 arm) are in goldeneye.exe but the boot never turned them on.
rem This file is the chair PLAY0 environment (harvest\_launch425w.ps1 -Arm PLAY0,
rem every parameter at its default) plus the ship picture KEEP stack. The binary is
rem byte-identical to vr440's - only this file changed.
rem
rem Falsifiers stay off. No -Log. FOVMATCH stays off. Read-only censuses stay off.

rem ---------------------------------------------------------------------------
rem 0. WIPE - anything the shell already exported that an arm must own.
rem    (425w Remove-Item block, verbatim, plus the dev probes.)
rem ---------------------------------------------------------------------------
set GETV_FPS=
set GETV_XR_FOVMATCH=
set GETV_REALCLOCK=
set GETV_GUN_AIM=
set GETV_FULLSCREEN=
set GETV_WINDOW=
set GETV_MSAA=
set GETV_FXAA=
set GETV_CRT=
set GETV_CRT_SCANLINE=
set GETV_CRT_MASK=
set GETV_CRT_CURVE=
set GETV_CRT_VIGNETTE=
set GETV_XR_SHARPLOG=
set GETV_FIREDUMP=
set GETV_VR_VISFAR=1
set GETV_ROOMHOLD=
set GETV_CULLWHY=
set GETV_STEREO_PROBE=
set GETV_ROOMTRACE=
set GETV_SKYTRACE=
set GETV_GRNDSKIPROOM=
set GETV_GRNDNOP=
set GETV_GRNDPAT=
set GETV_PORTALBOX=
set GETV_MUSICFADE_HZ=
set GETV_AUDIO_DEBUG=
set GETV_NO_AUDIO=
set GETV_NO_AUDIO_QUEUE=
set GETV_VR_BODY_NOARMS_TRACE=
set GETV_XR_INPUT_FIREHAND=
set GETV_XR_INPUT_WALKHAND=
set GETV_XR_TURN_HAND=
set GETV_XR_TURN_INVERT=
set GETV_XR_BUTTON_HAND=
set GETV_XR_BTN_SQUEEZE=
set GETV_XR_BTN_SQUEEZE_PCT=
set GETV_CONTROLS=
set GETV_DUALANALOG=
set GETV_CHR_DEBUG=
set GETV_FRONTTRACE=
set GETV_INPUT_DEBUG=
set GETV_CINETRACE=
set GETV_STATE=
set GETV_STAGE=
set GETV_LOGFLUSH=
set GETV_VR_WATERTILE=
set GETV_VR_OCCLSKIP=
set GETV_VR_FOGSKIP=
set GETV_VR_DISTSKIP=
set GETV_VR_TEXTBAND_PAD=
set GETV_VR_TEXTBAND_X=
set GETV_VR_AMMOHUD_PAD=
set GETV_VR_MSGSCALE=
set GETV_VR_BLOODINVAL=
set GETV_VR_TITLEBG=
set GETV_VR_HUB=
set GETV_VR_TEXGUARD=
set GETV_VR_SCRAPDROP=
set GETV_VR_SKYPIN=
set GETV_VR_SKYWORLD=
set GETV_VR_SKYINF=
set GETV_VR_SKYWATERPIN=
set GETV_VR_SKYWATERRECT=
set GETV_VR_SKYWATERLERP=
set GETV_VR_SKYWATERLAYER=
set GETV_VR_SKYWATERUV=
set GETV_VR_GRIPUSE=
set GETV_VR_FRIGMUTE=
set GETV_VR_FRIGDOORROOM=
set GETV_VR_FRIGOPEN=
set GETV_VR_MODEMDROP=
set GETV_VR_MODEMBED=
set GETV_VR_BUGZBIAS=
set GETV_VR_BUGMATX=
set GETV_VR_BUGOUT=
set GETV_VR_PROJPROP=
set GETV_VR_PROJCOOK=
set GETV_VR_PROJSOLID=
set GETV_VR_PROPWHY=
set GETV_VR_SPINWHEEL=
set GETV_VR_EMBEDEYE=
set GETV_VR_JANUSSPAWN=
set GETV_VR_GUNORIGIN=
set GETV_AI_ANIMFRAMES=
set GETV_VR_SWINGHIT=
set GETV_VR_SWINGPOSE=
set GETV_VR_GUNREBASE=
set GETV_VR_FALSEDOOR=
set GETV_VR_CHRPASS=
set GETV_VR_FRIGWHY=
set GETV_VR_DOORLOS=
set GETV_STEREO_MTXGUARD=
set GETV_BIND_WEAPON_PREV=
set GETV_VR_BONDHAND=

rem ---------------------------------------------------------------------------
rem 1. Cache ship stamp. Must match the wear exe's tag or gevr_prepare re-slices.
rem    Bump on every public tag. A changed stamp re-slices the image cache
rem    once from the player's own ROM; the ROM slice itself is unchanged here.
rem ---------------------------------------------------------------------------
set GEVR_SHIP_TAG=vr450

rem ---------------------------------------------------------------------------
rem 2. Core VR + pacing (425w standing keepers; pacing follows the headset (421); do not re-pin GETV_FPS)
rem ---------------------------------------------------------------------------
set GETV_VR=1
rem GETV_FPS unset: 421 follows headset Hertz (72/80/90/120...). Do not pin here.
rem SIMHZ=query (+ vr445 code arm) so interlock can open. Dig GETV_SIMHZ=0 for retail.
set GETV_SIMDIV=1
set GETV_SIMHZ=query
rem OPT 2026-09-21: desktop vsync before XR blit beats HMD; compositor paces.
set GETV_VSYNC=0
rem OPT: was GETV_BUDGET=120 (report+fflush tax every frame). Unset = off.
set GETV_BUDGET=
rem WINFOCUS ship OFF (AttachThreadInput jitter; click still needed). Dig =1.
set GETV_VR_WINFOCUS=0
rem FRAMELOG ship OFF ??? gate 60f/10f census+fflush (DIG-81-PRINTF-GATE). Dig =1.
set GETV_FRAMELOG=
rem #81 WEAPSTEAL ship ON ??? recycle floor modems so throws keep working.
set GETV_VR_WEAPSTEAL=1
rem vr445: monitor mirror ON while VR (NODESKTOP off). Dig =1 skips desktop resolve.
set GETV_XR_NODESKTOP=0
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
set GETV_XR_HEAD_TRANSLATE=0
set GETV_XR_PLAY_AUTORECENTER=1
set GETV_XR_PLAY_AUTOSCREEN=1
set GETV_XR_PLAY_FOVSCALE_CINEMA=85
set GETV_XR_PLAY_SRCRECT=full
set GETV_XR_PLAY_EYERECT=1

rem ---------------------------------------------------------------------------
rem 3. Sharpness KEEP (SS3 + SrcFbo). Never SS>1 without SrcFbo.
rem    GETV_SRCFBO and GETV_MSGSCALE are NOT knobs in this binary - the real
rem    names are GETV_XR_PLAY_SRCFBO and GETV_VR_MSGSCALE (default 50 = the
rem    434 chair KEEP), so MSGSCALE is left at its code default on purpose.
rem ---------------------------------------------------------------------------
set GETV_SUPERSAMPLE=3
set GETV_XR_PLAY_SRCFBO=1

rem ---------------------------------------------------------------------------
rem 4. Recenter + input (425w per-arm assigns, at PLAY0 defaults)
rem ---------------------------------------------------------------------------
set GETV_XR_ACTIONS=1
set GETV_XR_HANDS=1
set GETV_XR_INPUT=1
set GETV_XR_RECENTER_CHORD=1
set GETV_XR_RECENTER_YAWONLY=1
set GETV_XR_FLOOR_INJECT=0
set GETV_XR_FLOOR_M=-0.200
set GETV_XR_TURN=1
set GETV_XR_TURN_SCALE=60
rem Player VR Settings (#76) in AppData - survives zip update; overrides defaults.
if exist "%LOCALAPPDATA%\GEVR\gevr-player-prefs.cmd" (
  call "%LOCALAPPDATA%\GEVR\gevr-player-prefs.cmd"
)

set GETV_XR_TURN_DEAD=20
set GETV_XR_BUTTONS=1

rem #76 VR Settings glass (intro/cinema, look right). Stick U/D row, L/R change. Prefs in AppData.
rem GETV_VR_OPT_PANEL -- C-default ON in ge_vr_opt.c; =0 digs OFF. No batline.
set GETV_XR_INPUT_TRIGGER=50
set GETV_XR_INPUT_DEADZONE=20
set GETV_XR_INPUT_EVERY=0
set GETV_XR_HAPTICS=1

rem Button maps: SHIP choice, NOT chair. 425w clears BTN_A/BTN_B and runs on the
rem binary defaults. B = use (reload); pause = Menu / system button (not B/Y).
rem A = weapon (N64 A cycle). Falsifier: clear both and you are on chair.
set GETV_XR_BTN_B=use

rem --- 2026-09-19 PASS KEEPs (WATCHFAR / GUNEYE / HINGE / left-Y) ---
rem MTXGUARD=2 is Bunker-only (Dam tunnel blue flicker if global) -- use Start-GEVR-55-bunker-mtxguard2*.bat
set GETV_WATCHFAR=1
set GETV_VR_GUNEYE=1
set GETV_HINGE_SLOT=2
set GETV_VR_HUDICONAR=1
set GETV_VR_HUDSCALE=25
set GETV_VR_HUDDIGITMIN=25
set GETV_XR_BTN_LY=start
set GETV_XR_BTN_A=weapon
rem WEAPAX KEEP: A = next gun; left-controller X = previous
set GETV_BIND_WEAPON_PREV=x
set GETV_VR_SPINWHEEL=
set GETV_AUTOAIM=0

rem ---------------------------------------------------------------------------
rem 5. Aim / hands / gun / playspace (425w shared PLAY body, defaults)
rem ---------------------------------------------------------------------------
set GETV_VR_HEADYAW=1
set GETV_VR_HEADYAW_IPD=1
set GETV_VR_HEADFRAME=2
set GETV_VR_HANDYAW=2
set GETV_VR_LEVELYAW=1
set GETV_VR_GUNAIM=1
set GETV_VR_GUNMOUNT=1
set GETV_VR_GUNARM=1
set GETV_VR_GUNPITCH=0
set GETV_VR_GUNARM_TRACE=0
set GETV_VR_PLAYSPACE=1
set GETV_VR_TILTFIX=0
set GETV_VR_BODY=0
set GETV_VR_BODY_NOARMS=1
set GETV_VR_HANDCUBES=1
set GETV_VR_HANDCUBE_MM=45
rem chair: empty hand invisible with MASK=0+ghost miss; show cubes for now
set GETV_VR_HANDCUBE_MASK=1
rem chair: separate L/R triggers
set GETV_VR_DUALFIRE=1

set GETV_VR_TRACER_PERHAND=1

set GETV_VR_THROWAIM=1

set GETV_VR_HANDMESH=0

set GETV_VR_HANDMESH_CURL=1

set GETV_VR_HANDMESH_POINT=1

set GETV_VR_TANKTRACE=1
set GETV_VR_TANKGHOST=1

rem --- pack 452 (internal build) chair knobs ---
rem Internal build: 452 (public still vr441 smoke until tagged)
set GETV_VR_HANDSOLID=0
set GETV_VR_GUNZ=0
rem chair 2026-09-19: slip-in preferred over touch-enter
set GETV_VR_TOUCHTANK=0
set GETV_VR_TANKMOUNT=1
set GETV_VR_TOUCHTANK_R=80
rem chair: ghost miss ??? use HANDCUBES for empty hand
set GETV_VR_GHOSTHAND=0
set GETV_VR_GHOSTHAND_A=96
set GETV_VR_ONESHOT=1
rem chair 452: PROJSPAWN=1 spawned beside head not barrel
set GETV_VR_PROJSPAWN=0
set GETV_VR_ROCKETMODEL=1
set GETV_VR_TANKPITCH=1
set GETV_VR_SETUPCOPY=1





set GETV_VR_ROCKETAIM=1
set GETV_VR_PROJAIM=1
set GETV_VR_ROCKETONE=2
set GETV_VR_SIGHT2D=1
set GETV_VR_SIGHTTRACE=0
set GETV_VR_RETICLE=1
set GETV_VR_RETICLE_M=5.00
set GETV_VR_RETICLE_HAND=1
set GETV_VR_TOUCHUSE=1
set GETV_VR_TOUCHUSE_R=12
set GETV_VR_TOUCHUSE_TRACE=0
set GETV_VR_HANDMELEE=1
set GETV_VR_HANDMELEE_R=8
set GETV_VR_HANDMELEE_COOL=30
set GETV_VR_HANDMELEE_TRACE=0
rem #75 melee swing pose KEEP (wear PASS loosened): forward hemisphere + SWINGHIT
set GETV_VR_SWINGHIT=1
set GETV_VR_SWINGHIT_V=250
set GETV_VR_SWINGPOSE=1
set GETV_VR_SWINGPOSE_Z_M=0.15
set GETV_VR_SWINGPOSE_Y_M=0.00
rem #74 playspace / free move / hands follow -- C-default ON; explicit so shell cannot dig OFF
set GETV_VR_GUNREBASE=1
rem GETV_XR_BODY_TRANSLATE unset = C-default ON (do not set =0)

rem ---------------------------------------------------------------------------
rem 6. PLAY0 arm-only (the four knobs 425w raises on -Arm PLAY0 alone)
rem ---------------------------------------------------------------------------
rem VTXGUARD is a 64 KB poison allocation between the vertex arena and the
rem level texture pool, not an instrument: an arena overrun lands in poison
rem instead of on FIRE_n. It ships ON.
set GETV_VR_VTXGUARD=64
set GETV_VR_ADSSIGHT=1
set GETV_VR_HITSNAP=2
set GETV_VR_SIGHTPX=6
set GETV_VR_ADSCULL=1

rem ---------------------------------------------------------------------------
rem 7. Rooms / cull / portals / audio (425w shared PLAY body)
rem ---------------------------------------------------------------------------
set GETV_VR_DRAWALL=1
set GETV_VR_CULLWIDE=3.0
set GETV_VR_SCREENWIDE=3.0
set GETV_VR_ROOMBUDGET=64
set GETV_VR_LODDIST=0.25
rem last-cook: MaxVisRange vs FarFog ??? RESULT-FAR-CHR-VIS
set GETV_VR_VISFAR=1
set GETV_ROOMSCISSOR=0
set GETV_PORTALOPEN=1
set GETV_PROPCULLBOX=0
set GETV_PROPROOMTEST=0
set GETV_VR_ROOMTEST=0
set GETV_VR_PORTALWIDE=1
set GETV_VR_PORTALDEPTH=24
set GETV_VR_PORTALVISITS=64
set GETV_VR_ROOMHEAP=4096
set GETV_VR_ROOMLOADWHY=0
set GETV_AUDIO_CLOCK=device
set GETV_AUDIO_QUEUE_MS=33

rem ---------------------------------------------------------------------------
rem 8. Sky / eye isolation
rem ---------------------------------------------------------------------------
rem #72 Dam jump-strip blue PASS: cloud remesh OFF (was 1)
set GETV_VR_SKYMESH=0
rem Dam SKYWORLD KEEP (wear PASS): tiled N64 cloud UV as world geometry. Dig =0.
set GETV_VR_SKYWORLD=1
rem SKYINF retired for ship while SKYWORLD is on (chair Dig =0). Dig =1 only for A/B.
set GETV_VR_SKYINF=0
rem #80 Frigate water RECT KEEP (wear PASS): full-extent sea tile rects. Dig =0.
set GETV_VR_SKYWATERRECT=1
rem SKYWATERPIN / SKYWATERLERP / SKYWATERLAYER / SKYWATERUV stay OFF (not KEEP).
set GETV_VR_SKYWATERPIN=0
rem Dam sky pin KEEP 2026-09-20: C-default ON. Unset/empty = ON; only =0 digs OFF.
rem Chair bat optional. Do not set SKYMESH=1.
set GETV_VR_SKYPIN=
set GETV_VR_SKYSCISSOR=1
set GETV_VR_SKYFILL=1
set GETV_VR_SKYFILL2=0
set GETV_VR_SKYFILL3=1

rem ---------------------------------------------------------------------------
rem 9. Corpses / texture / VFX (the chair keepers the public boot never turned on)
rem ---------------------------------------------------------------------------
set GETV_VR_CORPSEKEEP=1
set GETV_VR_CORPSEKEEP_MAX=48
set GETV_VR_CORPSEKEEP_CEIL=440
set GETV_VR_TEXINVAL=1
set GETV_VR_TEXDLRETAG=1
rem Read-only censuses: chair runs them on, players get console spam. Off.
set GETV_VR_WALLCENSUS=0
set GETV_VR_VFXTMEM=1
set GETV_VR_VFXSHIFT=1
set GETV_TILE1=1
set GETV_BASETILE=1
set GETV_TMEMMAP=0
rem EXACTLY ONE 16-bit byte-order side may be on. DECODE side = TEX16BE.
set GETV_TEX16BE=1
set GETV_RGBA16BE=0
set GETV_TEX32BE=1

set GE_VR_XR=1
rem chair 452: gun vanish below chest ? GHOSTHAND=0 GUNZ=0 HANDSOLID=0; empty left cube
rem chair 452: MASK=1 LEFT cube (0=neither); HANDMESH=0; two-hand snap dig parallel
set GETV_VR_CASINGS=1
rem #49 Hertz: DO NOT pin GETV_FPS=90 here. Unset = follow HMD (421/422).
rem Pinning 90 makes 72/80/120 refuse the pace interlock (~frame 300 ??? desktop-looking).
rem set GETV_FPS=90
rem public ship: no GETV_UNLOCKALL (chair-only; silent fix 2026-09-19)
rem #70 Dam modem chair: HEAD_TRANSLATE=0 cuts continuous flicker (MONFRAME REJECT)

rem --- vr444.1 KEEP (explicit so shell leftovers cannot dig OFF) ---
set GETV_VR_THROWGRIP=2
set GETV_VR_HANDCUBE_HIDEARMED=1
set GETV_VR_MODEMDROP=3
rem WEAPAX: BIND_WEAPON_PREV=x + BTN_A=weapon set above.
rem Dig-only #70 paths stay OFF (PROJSOLID/PROJCOOK/PROPWHY/MODEMBED/...):
set GETV_VR_BUGMATX=
set GETV_VR_BUGZBIAS=
set GETV_VR_MODEMBED=
set GETV_VR_PROJSOLID=
set GETV_VR_PROJCOOK=
set GETV_VR_PROPWHY=
set GETV_VR_PROJPROP=
set GETV_VR_SPINWHEEL=
set GETV_VR_EMBEDEYE=

rem --- vr445.2 KEEP (wear PASS stack; cadence already in 445.1 binary) ---
rem #82 Janus: explicit ON (also follows DRAWALL when unset). Dig =0 for retail.
set GETV_VR_JANUSSPAWN=1
rem Gun origin: shot leaves from drawn gun mount (GUNAIM=1). Dig =0.
set GETV_VR_GUNORIGIN=1
rem AI ANIMFRAMES: C-default ON in binary; explicit so shell cannot dig OFF. Dig =0.
set GETV_AI_ANIMFRAMES=1
rem #84 walk/run gait: code KEEP (no knob). Cadence KEEP retained from vr445.1.

rem --- vr450 KEEP (wear PASS; new on top of 445.2) ---
rem #80 Frigate water RECT: set above with SKYWORLD (SKYWATERRECT=1). LERP/LAYER/UV OFF.
rem #90 Contextual Grip doors: squeeze near = USE toggle; clear = AIM. Dig =0.
rem Pickup / mines / modem / mission-lock are NOT a separate KEEP for this cut
rem (same knob today; release notes advertise doors only). Dig =0 turns doors off too.
set GETV_VR_GRIPUSE=1
rem Slot4 seed (007 + 24 solo cheats): C-default ON in goldeneye.exe (fileValidateSaves).
rem Seeds FOLDER4 only when empty; never touches folders 1-3. Dig OFF: GETV_SEEDFOLDER4=0.
rem Do NOT arm GETV_UNLOCKALL (that fills all four folders).
rem Do NOT arm: FALSEDOOR / CHRPASS / FRIGWHY / DOORLOS / FRIGMUTE / FRIGDOORROOM /
rem FRIGOPEN / SKYWATERLERP / SKYWATERLAYER / SKYWATERUV / TEXGUARD / SCRAPDROP / EMBEDEYE.
rem Do NOT globalize GETV_STEREO_MTXGUARD=2 onto Dam (Facility/Bunker chairs only).
