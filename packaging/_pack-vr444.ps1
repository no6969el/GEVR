# Assemble GEVR Beta vr444 staging folder (BYO-ROM) - same layout as vr442 ship pack.
# After -Vr: pack from getv\build-windows into out\vr444-staging (+ zip).
# Retagged from planned vr443.2 - major modem-scrap glitch cut warrants a full tag.

[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [string]$BuildDir,

    [string]$OutDir = "",
    [string]$PackagingRoot = "",
    [string]$Tag = "vr444",
    [switch]$SkipSmoke,
    [string]$CombinedBin = ""
)

$ErrorActionPreference = "Stop"
if (-not $PackagingRoot) { $PackagingRoot = $PSScriptRoot }
if (-not $OutDir) { $OutDir = Join-Path $PackagingRoot ("out\{0}-staging" -f $Tag) }

$templates = Join-Path $PackagingRoot "templates"
$romStarter = Join-Path $PackagingRoot "rom-starter"

$requiredDlls = @(
    "glew32.dll", "SDL2.dll", "openxr_loader.dll",
    "libwinpthread-1.dll", "libgcc_s_seh-1.dll", "libstdc++-6.dll"
)

function Copy-IfExists([string]$src, [string]$destDir) {
    if (-not (Test-Path -LiteralPath $src)) { throw "Missing required file: $src" }
    Copy-Item -LiteralPath $src -Destination $destDir -Force
}

if (Test-Path -LiteralPath $OutDir) { Remove-Item -LiteralPath $OutDir -Recurse -Force }
New-Item -ItemType Directory -Path $OutDir | Out-Null

Copy-IfExists (Join-Path $BuildDir "goldeneye.exe") $OutDir
foreach ($dll in $requiredDlls) {
    Copy-IfExists (Join-Path $BuildDir $dll) $OutDir
}
Get-ChildItem -LiteralPath $BuildDir -Filter "*.dll" | ForEach-Object {
    $dest = Join-Path $OutDir $_.Name
    if (-not (Test-Path -LiteralPath $dest)) {
        Copy-Item -LiteralPath $_.FullName -Destination $OutDir -Force
    }
}

Copy-IfExists (Join-Path $romStarter "GevrRomStarter.exe") $OutDir
Copy-IfExists (Join-Path $romStarter "gevr_prepare.exe") $OutDir
Copy-IfExists (Join-Path $romStarter "EXPECTED-ROM.txt") $OutDir
$filelistRepo = Join-Path $romStarter "filelist.gevr-images.csv"
if (Test-Path $filelistRepo) { Copy-IfExists $filelistRepo $OutDir }
elseif (Test-Path (Join-Path $BuildDir "filelist.gevr-images.csv")) {
    Copy-IfExists (Join-Path $BuildDir "filelist.gevr-images.csv") $OutDir
}

# Ship layout: Start-GEVR.bat + tag boot + RELEASE-NOTES.txt (same as vr442 pack)
Copy-Item -LiteralPath (Join-Path $templates "Start-GEVR-vr444.bat") -Destination (Join-Path $OutDir "Start-GEVR.bat") -Force
Copy-Item -LiteralPath (Join-Path $templates "gevr-vr444-boot.cmd") -Destination (Join-Path $OutDir "gevr-vr444-boot.cmd") -Force
Copy-Item -LiteralPath (Join-Path $templates "RELEASE-NOTES-vr444.txt") -Destination (Join-Path $OutDir "RELEASE-NOTES.txt") -Force
if (Test-Path (Join-Path $templates "Clear-GEVR-cache.bat")) {
    Copy-Item (Join-Path $templates "Clear-GEVR-cache.bat") $OutDir -Force
}
if (Test-Path (Join-Path $templates "Play-on-monitor.bat")) {
    Copy-Item (Join-Path $templates "Play-on-monitor.bat") $OutDir -Force
}

$zipPath = Join-Path (Split-Path -Parent $OutDir) ("GEVR-Beta-{0}-win64.zip" -f $Tag)
if (Test-Path $zipPath) { Remove-Item $zipPath -Force }
Compress-Archive -Path (Join-Path $OutDir "*") -DestinationPath $zipPath -CompressionLevel Optimal

Write-Host "[pack] Staging: $OutDir"
Write-Host "[pack] Zip: $zipPath"

if (-not $SkipSmoke) {
    if (-not $CombinedBin) {
        $guess = Join-Path (Split-Path (Split-Path $BuildDir -Parent) -Parent) "assets\images\combined\combined.bin"
        if (Test-Path -LiteralPath $guess) { $CombinedBin = $guess }
        if (-not $CombinedBin -or -not (Test-Path -LiteralPath $CombinedBin)) {
            $alt = "F:\Projects\GEVR\GoldenEyeVR\goldeneye-native\vendor\ge-decomp\assets\images\combined\combined.bin"
            if (Test-Path -LiteralPath $alt) { $CombinedBin = $alt }
        }
    }
    $smoke = Join-Path $PackagingRoot "_smoke-ship-zip.ps1"
    if ((Test-Path $smoke) -and $CombinedBin -and (Test-Path $CombinedBin)) {
        & $smoke -StagingDir $OutDir -CombinedBin $CombinedBin -ShipTag $Tag
        & $smoke -ZipPath $zipPath -CombinedBin $CombinedBin -ShipTag $Tag
    } else {
        Write-Host "[pack] Smoke skipped (no _smoke-ship-zip.ps1 or CombinedBin)"
    }
}

Write-Host "[pack] PASS pack path for $Tag"
