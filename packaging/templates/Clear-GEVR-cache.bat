@echo off
setlocal EnableExtensions EnableDelayedExpansion
cd /d "%~dp0"

rem =============================================================================
rem  Clear-GEVR-cache.bat  (shipped next to Start-GEVR.bat)
rem
rem  Extended clean / reset tool. SAME filename as the old cache-only bat so
rem  existing zip docs and muscle memory keep working.
rem
rem  [1] Cache only          - old behavior (picture wrong after an update)
rem  [2] Clean reset         - wipe junk as if new install; KEEP saves
rem                            (Quest / multi-version launch weirdness)
rem  [3] Cancel
rem
rem  Option [2] always backs up saves first, then restores them.
rem  Does NOT delete goldeneye.exe / the zip unless you opt into FULL wipe.
rem  Does NOT touch your .z64 ROM path on disk (rom.path binder is cleared).
rem =============================================================================

set "GEVR_LOCAL=%LOCALAPPDATA%\GEVR"
set "CACHE_ROOT=%GEVR_LOCAL%\cache"
set "GE_NATIVE=%APPDATA%\Goldeneye-Native\Goldeneye-Native"
set "BACKUP_ROOT=%LOCALAPPDATA%\GEVR-save-backups"
set "STAMP="
for /f %%I in ('powershell -NoProfile -Command "Get-Date -Format yyyyMMdd-HHmmss" 2^>nul') do set "STAMP=%%I"
if not defined STAMP set "STAMP=%DATE:~-4%%DATE:~4,2%%DATE:~7,2%-%TIME:~0,2%%TIME:~3,2%%TIME:~6,2%"
set "STAMP=%STAMP: =0%"
set "BACKUP_DIR=%BACKUP_ROOT%\gevr-saves-%STAMP%"

echo.
echo ============================================================
echo  GEVR clean / reset  (keeps your folder saves)
echo ============================================================
echo.
echo  This bat lives in your GEVR game folder.
echo  Close goldeneye.exe / GevrRomStarter before continuing.
echo.
echo  [1] Cache only
echo      Deletes:  %%LOCALAPPDATA%%\GEVR\cache
echo      Keeps:    saves, prefs, rom binder, install folder, .z64
echo      Use when: picture looks wrong after a Beta update.
echo.
echo  [2] Clean reset (recommended after many versions / Quest weirdness)
echo      Backs up saves first, then wipes caches / configs / temp /
echo      update leftovers / stale boot junk, then restores saves.
echo      Keeps:    eeprom / folder saves, your .z64 on disk,
echo                goldeneye.exe + current zip files (by default)
echo      Use when: Quest-as-HMD / OpenXR fails to launch cleanly after
echo                stacking many Beta zips in one folder.
echo.
echo  [3] Cancel
echo.
set /p CHOICE=Type 1, 2, or 3 then Enter: 
if "%CHOICE%"=="1" goto :CACHE_ONLY
if "%CHOICE%"=="2" goto :FULL_RESET
if /i "%CHOICE%"=="YES" goto :CACHE_ONLY
echo Cancelled.
exit /b 0

rem ---------------------------------------------------------------------------
:CACHE_ONLY
echo.
echo Cache-only wipe:
echo   %CACHE_ROOT%
echo Saves under %%LOCALAPPDATA%%\GEVR and %%APPDATA%%\Goldeneye-Native are kept.
echo Your .z64 ROM is not touched.
echo.
set /p CONFIRM=Type YES to continue: 
if /i not "%CONFIRM%"=="YES" (
  echo Cancelled.
  exit /b 0
)
if exist "%CACHE_ROOT%" (
  rmdir /s /q "%CACHE_ROOT%"
  echo Deleted %CACHE_ROOT%.
  echo Run Start-GEVR.bat or Play-on-monitor.bat to prepare again.
) else (
  echo Cache folder not found ^(nothing to delete^).
)
echo.
pause
exit /b 0

rem ---------------------------------------------------------------------------
:FULL_RESET
echo.
echo Clean reset keep-saves:
echo   Backup -^>  %BACKUP_DIR%
echo   Wipe   -^>  LocalAppData\GEVR ^(except restored saves^)
echo             AppData Goldeneye-Native configs ^(eeprom kept^)
echo             install-folder logs / Update leftovers / stale boots
echo             %%TEMP%%\GEVR-update
echo   Keep   -^>  folder saves / eeprom.bin, .z64 on disk, game exe/zip
echo.
echo Optional later: wipe the INSTALL FOLDER itself ^(exe/dlls^) except
echo your ROM and this bat — only if you type FULL when asked.
echo.
set /p CONFIRM=Type YES to run clean reset: 
if /i not "%CONFIRM%"=="YES" (
  echo Cancelled.
  exit /b 0
)

echo.
echo --- 1/5 Backup saves ---
mkdir "%BACKUP_DIR%" >nul 2>&1
mkdir "%BACKUP_DIR%\local-gevr" >nul 2>&1
mkdir "%BACKUP_DIR%\appdata-goldeneye-native" >nul 2>&1
call :BackupSaves
echo Backup folder: %BACKUP_DIR%

echo.
echo --- 2/5 Wipe LocalAppData\GEVR ---
if exist "%GEVR_LOCAL%" (
  rmdir /s /q "%GEVR_LOCAL%"
  echo Removed %GEVR_LOCAL%
) else (
  echo No %%LOCALAPPDATA%%\GEVR folder.
)

echo.
echo --- 3/5 Wipe Goldeneye-Native configs ^(keep eeprom^) ---
if exist "%GE_NATIVE%" (
  if exist "%GE_NATIVE%\goldeneye.cfg" (
    del /f /q "%GE_NATIVE%\goldeneye.cfg" >nul 2>&1
    echo Deleted goldeneye.cfg
  )
  rem Wipe non-save clutter; never delete eeprom.bin here.
  for %%F in ("%GE_NATIVE%\*") do (
    if /i not "%%~nxF"=="eeprom.bin" (
      if not exist "%%~fF\" (
        del /f /q "%%~fF" >nul 2>&1
      )
    )
  )
  for /d %%D in ("%GE_NATIVE%\*") do (
    rmdir /s /q "%%~fD" >nul 2>&1
  )
) else (
  echo No Goldeneye-Native AppData folder.
)

echo.
echo --- 4/5 Restore saves ---
call :RestoreSaves

echo.
echo --- 5/5 Install-folder + temp junk ---
call :CleanInstallJunk

echo.
echo Optional FULL wipe of this install folder ^(exe/dlls/bats^),
echo keeping only your .z64/.n64/.v64 and this reset bat.
echo You would re-unzip the Beta zip afterward.
echo.
set /p FULLWIPE=Type FULL to wipe install folder, or Enter to skip: 
if /i "%FULLWIPE%"=="FULL" (
  call :WipeInstallExceptRomAndSelf
) else (
  echo Skipped install-folder wipe ^(exe/zip kept^).
)

echo.
echo ============================================================
echo  Done. Saves restored from:
echo    %BACKUP_DIR%
echo.
echo  Next: run Start-GEVR.bat  ^(first launch re-prepares cache^)
echo  Quest: set OpenXR to Virtual Desktop before launching.
echo ============================================================
echo.
pause
exit /b 0

rem =============================================================================
:BackupSaves
rem LOCALAPPDATA\GEVR save-shaped items (outside / including root)
if exist "%GEVR_LOCAL%\eeprom.bin" (
  copy /y "%GEVR_LOCAL%\eeprom.bin" "%BACKUP_DIR%\local-gevr\eeprom.bin" >nul
  echo   + LOCAL eeprom.bin
)
if exist "%GEVR_LOCAL%\saves\" (
  xcopy /e /i /y /q "%GEVR_LOCAL%\saves" "%BACKUP_DIR%\local-gevr\saves\" >nul
  echo   + LOCAL saves\
)
if exist "%GEVR_LOCAL%\save\" (
  xcopy /e /i /y /q "%GEVR_LOCAL%\save" "%BACKUP_DIR%\local-gevr\save\" >nul
  echo   + LOCAL save\
)
rem Any loose *eeprom* / *save*.bin at GEVR root (not under cache)
for %%F in ("%GEVR_LOCAL%\*eeprom*" "%GEVR_LOCAL%\*save*.bin" "%GEVR_LOCAL%\*folder*") do (
  if exist "%%~fF" if not exist "%%~fF\" (
    copy /y "%%~fF" "%BACKUP_DIR%\local-gevr\%%~nxF" >nul 2>&1
  )
)
rem APPDATA Goldeneye-Native eeprom (canonical folder saves)
if exist "%GE_NATIVE%\eeprom.bin" (
  copy /y "%GE_NATIVE%\eeprom.bin" "%BACKUP_DIR%\appdata-goldeneye-native\eeprom.bin" >nul
  echo   + APPDATA eeprom.bin
)
rem Also snapshot goldeneye.cfg into backup for forensics (not restored)
if exist "%GE_NATIVE%\goldeneye.cfg" (
  copy /y "%GE_NATIVE%\goldeneye.cfg" "%BACKUP_DIR%\appdata-goldeneye-native\goldeneye.cfg.bak" >nul
  echo   + APPDATA goldeneye.cfg ^(backup only, not restored^)
)
exit /b 0

rem =============================================================================
:RestoreSaves
mkdir "%GEVR_LOCAL%" >nul 2>&1
if exist "%BACKUP_DIR%\local-gevr\eeprom.bin" (
  copy /y "%BACKUP_DIR%\local-gevr\eeprom.bin" "%GEVR_LOCAL%\eeprom.bin" >nul
  echo   Restored LOCAL eeprom.bin
)
if exist "%BACKUP_DIR%\local-gevr\saves\" (
  xcopy /e /i /y /q "%BACKUP_DIR%\local-gevr\saves" "%GEVR_LOCAL%\saves\" >nul
  echo   Restored LOCAL saves\
)
if exist "%BACKUP_DIR%\local-gevr\save\" (
  xcopy /e /i /y /q "%BACKUP_DIR%\local-gevr\save" "%GEVR_LOCAL%\save\" >nul
  echo   Restored LOCAL save\
)
for %%F in ("%BACKUP_DIR%\local-gevr\*") do (
  if exist "%%~fF" if not exist "%%~fF\" (
    if /i not "%%~nxF"=="eeprom.bin" (
      copy /y "%%~fF" "%GEVR_LOCAL%\%%~nxF" >nul 2>&1
    )
  )
)
mkdir "%GE_NATIVE%" >nul 2>&1
if exist "%BACKUP_DIR%\appdata-goldeneye-native\eeprom.bin" (
  copy /y "%BACKUP_DIR%\appdata-goldeneye-native\eeprom.bin" "%GE_NATIVE%\eeprom.bin" >nul
  echo   Restored APPDATA eeprom.bin
)
exit /b 0

rem =============================================================================
:CleanInstallJunk
rem Logs / crash dumps beside the exe
if exist "%~dp0gevr-player-log.txt" del /f /q "%~dp0gevr-player-log.txt" >nul 2>&1
for %%F in ("%~dp0gevr-fault-*.txt") do if exist "%%~fF" del /f /q "%%~fF" >nul 2>&1
rem GevrRomStarter in-app Update leftovers
if exist "%~dp0GevrRomStarter.exe.new" del /f /q "%~dp0GevrRomStarter.exe.new" >nul 2>&1
if exist "%~dp0GEVR-finish-update.bat" del /f /q "%~dp0GEVR-finish-update.bat" >nul 2>&1
rem Temp download staging from Update
if exist "%TEMP%\GEVR-update\" (
  rmdir /s /q "%TEMP%\GEVR-update"
  echo   Cleared %%TEMP%%\GEVR-update
)
rem Stale multi-version boot cmds: keep the one Start-GEVR.bat calls
set "KEEP_BOOT="
if exist "%~dp0Start-GEVR.bat" (
  for /f "delims=" %%I in ('powershell -NoProfile -Command "$m = Select-String -Path '%~dp0Start-GEVR.bat' -Pattern 'gevr-[^\s\"<>|]+-boot\.cmd' | Select-Object -First 1; if ($m) { [IO.Path]::GetFileName($m.Matches[0].Value) }" 2^>nul') do set "KEEP_BOOT=%%I"
)
rem Fallback: last gevr-*-boot.cmd on disk if Start-GEVR.bat parse failed
if not defined KEEP_BOOT (
  for %%F in ("%~dp0gevr-*-boot.cmd") do set "KEEP_BOOT=%%~nxF"
)
if defined KEEP_BOOT echo   Keeping boot: !KEEP_BOOT!
for %%F in ("%~dp0gevr-*-boot.cmd") do (
  if exist "%%~fF" if /i not "%%~nxF"=="!KEEP_BOOT!" (
    del /f /q "%%~fF" >nul 2>&1
    echo   Removed stale %%~nxF
  )
)
rem Old versioned Start-GEVR-vr*.bat copies left by hand mixes
for %%F in ("%~dp0Start-GEVR-vr*.bat") do (
  if exist "%%~fF" (
    del /f /q "%%~fF" >nul 2>&1
    echo   Removed %%~nxF
  )
)
echo   Install junk cleaned.
exit /b 0

rem =============================================================================
:WipeInstallExceptRomAndSelf
echo   FULL install wipe in: %~dp0
for %%F in ("%~dp0*") do (
  if exist "%%~fF" if not exist "%%~fF\" (
    set "KEEP=0"
    if /i "%%~nxF"=="%~nx0" set "KEEP=1"
    if /i "%%~nxF"=="Clear-GEVR-cache.ps1" set "KEEP=1"
    if /i "%%~xF"==".z64" set "KEEP=1"
    if /i "%%~xF"==".n64" set "KEEP=1"
    if /i "%%~xF"==".v64" set "KEEP=1"
    if "!KEEP!"=="0" (
      del /f /q "%%~fF" >nul 2>&1
    )
  )
)
for /d %%D in ("%~dp0*") do (
  rmdir /s /q "%%~fD" >nul 2>&1
)
echo   Install folder wiped except ROM +(s) and this bat.
echo   Re-unzip GEVR-Beta-*-win64.zip into this folder, then Start-GEVR.bat.
exit /b 0
