# Harvest / verify a file-backed VR build on SimRig (product tree).
# Does not publish anything. Copies goldeneye.exe to stageb-images for diffing.

[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [string]$ProductRoot,

    [string]$GetvDir = "",
    [switch]$SkipBuild
)

$ErrorActionPreference = "Stop"

if (-not $GetvDir) {
    $GetvDir = Join-Path $ProductRoot "goldeneye-native\getv"
}
$buildWindows = Join-Path $GetvDir "build-windows"
$buildScript = Join-Path $GetvDir "build_windows.ps1"

if (-not (Test-Path -LiteralPath $buildScript)) {
    throw "Missing build_windows.ps1 at $buildScript"
}

if (-not $SkipBuild) {
    Write-Host "[pack] Building -Vr -ImagesFileBacked ..."
    Push-Location $GetvDir
    try {
        & $buildScript -Target all -Vr -ImagesFileBacked 2>&1 | Tee-Object -FilePath (Join-Path $ProductRoot "build_vr438_filebacked.log")
        if ($LASTEXITCODE -ne 0) {
            throw "build_windows.ps1 exited $LASTEXITCODE"
        }
    }
    finally {
        Pop-Location
    }
}

$exe = Join-Path $buildWindows "goldeneye.exe"
if (-not (Test-Path -LiteralPath $exe)) {
    throw "Missing $exe after build"
}

$stageB = Join-Path $buildWindows "goldeneye.exe.stageb-images"
Copy-Item -LiteralPath $exe -Destination $stageB -Force

$len = (Get-Item -LiteralPath $exe).Length
Write-Host "[pack] goldeneye.exe bytes: $len"
Write-Host "[pack] stageb copy: $stageB"
Write-Host "[pack] Next: run _pack-vr438.ps1 -BuildDir $buildWindows"
