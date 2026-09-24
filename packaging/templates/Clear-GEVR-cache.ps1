# Clear-GEVR-cache.ps1
# Optional PowerShell twin of Clear-GEVR-cache.bat (same folder).
# Prefer the .bat for double-click; use this from an elevated / scripted shell.
#
# Modes:
#   -CacheOnly   old behavior: delete %LOCALAPPDATA%\GEVR\cache only
#   -CleanReset  wipe junk as if new install; backup+restore saves (default if interactive)
#   -FullInstallWipe  with -CleanReset: also wipe install folder except ROM + this script/bat

[CmdletBinding()]
param(
    [switch]$CacheOnly,
    [switch]$CleanReset,
    [switch]$FullInstallWipe,
    [switch]$Yes
)

$ErrorActionPreference = "Stop"
$InstallDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$GevrLocal = Join-Path $env:LOCALAPPDATA "GEVR"
$CacheRoot = Join-Path $GevrLocal "cache"
$GeNative = Join-Path $env:APPDATA "Goldeneye-Native\Goldeneye-Native"
$BackupRoot = Join-Path $env:LOCALAPPDATA "GEVR-save-backups"
$Stamp = Get-Date -Format "yyyyMMdd-HHmmss"
$BackupDir = Join-Path $BackupRoot "gevr-saves-$Stamp"

function Write-Banner {
    Write-Host ""
    Write-Host "============================================================"
    Write-Host " GEVR clean / reset  (keeps your folder saves)"
    Write-Host "============================================================"
}

function Backup-Saves {
    New-Item -ItemType Directory -Force -Path (Join-Path $BackupDir "local-gevr") | Out-Null
    New-Item -ItemType Directory -Force -Path (Join-Path $BackupDir "appdata-goldeneye-native") | Out-Null

    $localEeprom = Join-Path $GevrLocal "eeprom.bin"
    if (Test-Path $localEeprom) {
        Copy-Item $localEeprom (Join-Path $BackupDir "local-gevr\eeprom.bin") -Force
        Write-Host "  + LOCAL eeprom.bin"
    }
    foreach ($name in @("saves", "save")) {
        $src = Join-Path $GevrLocal $name
        if (Test-Path $src) {
            Copy-Item $src (Join-Path $BackupDir "local-gevr\$name") -Recurse -Force
            Write-Host "  + LOCAL $name\"
        }
    }
    if (Test-Path $GevrLocal) {
        Get-ChildItem $GevrLocal -File -ErrorAction SilentlyContinue |
            Where-Object { $_.Name -match 'eeprom|save.*\.bin|folder' } |
            ForEach-Object {
                Copy-Item $_.FullName (Join-Path $BackupDir "local-gevr\$($_.Name)") -Force
            }
    }
    $appEeprom = Join-Path $GeNative "eeprom.bin"
    if (Test-Path $appEeprom) {
        Copy-Item $appEeprom (Join-Path $BackupDir "appdata-goldeneye-native\eeprom.bin") -Force
        Write-Host "  + APPDATA eeprom.bin"
    }
    $cfg = Join-Path $GeNative "goldeneye.cfg"
    if (Test-Path $cfg) {
        Copy-Item $cfg (Join-Path $BackupDir "appdata-goldeneye-native\goldeneye.cfg.bak") -Force
        Write-Host "  + APPDATA goldeneye.cfg (backup only, not restored)"
    }
}

function Restore-Saves {
    New-Item -ItemType Directory -Force -Path $GevrLocal | Out-Null
    $localBack = Join-Path $BackupDir "local-gevr"
    if (Test-Path (Join-Path $localBack "eeprom.bin")) {
        Copy-Item (Join-Path $localBack "eeprom.bin") (Join-Path $GevrLocal "eeprom.bin") -Force
        Write-Host "  Restored LOCAL eeprom.bin"
    }
    foreach ($name in @("saves", "save")) {
        $src = Join-Path $localBack $name
        if (Test-Path $src) {
            Copy-Item $src (Join-Path $GevrLocal $name) -Recurse -Force
            Write-Host "  Restored LOCAL $name\"
        }
    }
    Get-ChildItem $localBack -File -ErrorAction SilentlyContinue |
        Where-Object { $_.Name -ne "eeprom.bin" } |
        ForEach-Object { Copy-Item $_.FullName (Join-Path $GevrLocal $_.Name) -Force }

    New-Item -ItemType Directory -Force -Path $GeNative | Out-Null
    $appEeprom = Join-Path $BackupDir "appdata-goldeneye-native\eeprom.bin"
    if (Test-Path $appEeprom) {
        Copy-Item $appEeprom (Join-Path $GeNative "eeprom.bin") -Force
        Write-Host "  Restored APPDATA eeprom.bin"
    }
}

function Clear-InstallJunk {
    $playerLog = Join-Path $InstallDir "gevr-player-log.txt"
    if (Test-Path $playerLog) { Remove-Item $playerLog -Force }
    Get-ChildItem $InstallDir -Filter "gevr-fault-*.txt" -ErrorAction SilentlyContinue |
        Remove-Item -Force
    foreach ($f in @("GevrRomStarter.exe.new", "GEVR-finish-update.bat")) {
        $p = Join-Path $InstallDir $f
        if (Test-Path $p) { Remove-Item $p -Force }
    }
    $tempUpdate = Join-Path $env:TEMP "GEVR-update"
    if (Test-Path $tempUpdate) {
        Remove-Item $tempUpdate -Recurse -Force
        Write-Host "  Cleared %TEMP%\GEVR-update"
    }

    $keepBoot = $null
    $startBat = Join-Path $InstallDir "Start-GEVR.bat"
    if (Test-Path $startBat) {
        $line = Select-String -Path $startBat -Pattern 'gevr-.*-boot\.cmd' |
            Select-Object -First 1
        if ($line) {
            if ($line.Line -match '(gevr-[^\s"<>|]+-boot\.cmd)') {
                $keepBoot = $Matches[1]
            }
        }
    }
    $boots = @(Get-ChildItem $InstallDir -Filter "gevr-*-boot.cmd" -ErrorAction SilentlyContinue)
    if (-not $keepBoot -and $boots.Count -gt 0) {
        $keepBoot = $boots[-1].Name
    }
    if ($keepBoot) { Write-Host "  Keeping boot: $keepBoot" }
    foreach ($b in $boots) {
        if ($keepBoot -and ($b.Name -ne $keepBoot)) {
            Remove-Item $b.FullName -Force
            Write-Host "  Removed stale $($b.Name)"
        }
    }
    Get-ChildItem $InstallDir -Filter "Start-GEVR-vr*.bat" -ErrorAction SilentlyContinue |
        ForEach-Object {
            Remove-Item $_.FullName -Force
            Write-Host "  Removed $($_.Name)"
        }
    Write-Host "  Install junk cleaned."
}

function Clear-InstallExceptRomAndSelf {
    Write-Host "  FULL install wipe in: $InstallDir"
    $keepNames = @("Clear-GEVR-cache.bat", "Clear-GEVR-cache.ps1")
    $keepExt = @(".z64", ".n64", ".v64")
    Get-ChildItem $InstallDir -Force | ForEach-Object {
        if ($_.PSIsContainer) {
            Remove-Item $_.FullName -Recurse -Force -ErrorAction SilentlyContinue
        } else {
            $keep = ($keepNames -contains $_.Name) -or ($keepExt -contains $_.Extension.ToLowerInvariant())
            if (-not $keep) {
                Remove-Item $_.FullName -Force -ErrorAction SilentlyContinue
            }
        }
    }
    Write-Host "  Install folder wiped except ROM(s) and reset scripts."
    Write-Host "  Re-unzip GEVR-Beta-*-win64.zip into this folder, then Start-GEVR.bat."
}

function Invoke-CacheOnly {
    Write-Host ""
    Write-Host "Cache-only wipe:"
    Write-Host "  $CacheRoot"
    if (-not $Yes) {
        $c = Read-Host "Type YES to continue"
        if ($c -ne "YES") { Write-Host "Cancelled."; return }
    }
    if (Test-Path $CacheRoot) {
        Remove-Item $CacheRoot -Recurse -Force
        Write-Host "Deleted $CacheRoot"
        Write-Host "Run Start-GEVR.bat or Play-on-monitor.bat to prepare again."
    } else {
        Write-Host "Cache folder not found (nothing to delete)."
    }
}

function Invoke-CleanReset {
    Write-Host ""
    Write-Host "Clean reset keep-saves:"
    Write-Host "  Backup -> $BackupDir"
    if (-not $Yes) {
        $c = Read-Host "Type YES to run clean reset"
        if ($c -ne "YES") { Write-Host "Cancelled."; return }
    }

    Write-Host ""
    Write-Host "--- 1/5 Backup saves ---"
    Backup-Saves
    Write-Host "Backup folder: $BackupDir"

    Write-Host ""
    Write-Host "--- 2/5 Wipe LocalAppData\GEVR ---"
    if (Test-Path $GevrLocal) {
        Remove-Item $GevrLocal -Recurse -Force
        Write-Host "Removed $GevrLocal"
    } else {
        Write-Host "No %LOCALAPPDATA%\GEVR folder."
    }

    Write-Host ""
    Write-Host "--- 3/5 Wipe Goldeneye-Native configs (keep eeprom) ---"
    if (Test-Path $GeNative) {
        Get-ChildItem $GeNative -Force -ErrorAction SilentlyContinue | ForEach-Object {
            if ($_.Name -ieq "eeprom.bin") { return }
            Remove-Item $_.FullName -Recurse -Force -ErrorAction SilentlyContinue
        }
        Write-Host "Cleared non-eeprom files under Goldeneye-Native"
    } else {
        Write-Host "No Goldeneye-Native AppData folder."
    }

    Write-Host ""
    Write-Host "--- 4/5 Restore saves ---"
    Restore-Saves

    Write-Host ""
    Write-Host "--- 5/5 Install-folder + temp junk ---"
    Clear-InstallJunk

    $doFull = $FullInstallWipe
    if (-not $doFull -and -not $Yes) {
        $fw = Read-Host "Type FULL to wipe install folder, or Enter to skip"
        if ($fw -eq "FULL") { $doFull = $true }
    }
    if ($doFull) {
        Clear-InstallExceptRomAndSelf
    } else {
        Write-Host "Skipped install-folder wipe (exe/zip kept)."
    }

    Write-Host ""
    Write-Host "Done. Saves restored from:"
    Write-Host "  $BackupDir"
    Write-Host "Next: run Start-GEVR.bat (first launch re-prepares cache)"
}

Write-Banner
if (-not $CacheOnly -and -not $CleanReset) {
    Write-Host ""
    Write-Host " [1] Cache only"
    Write-Host " [2] Clean reset (Quest / multi-version junk; keeps saves)"
    Write-Host " [3] Cancel"
    Write-Host ""
    $choice = Read-Host "Type 1, 2, or 3 then Enter"
    if ($choice -eq "1") { $CacheOnly = $true }
    elseif ($choice -eq "2") { $CleanReset = $true }
    else { Write-Host "Cancelled."; exit 0 }
}

if ($CacheOnly) { Invoke-CacheOnly; exit 0 }
if ($CleanReset) { Invoke-CleanReset; exit 0 }
Write-Host "Cancelled."
exit 0
