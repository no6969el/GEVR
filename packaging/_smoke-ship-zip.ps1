# Ship-blocker smoke gates for GEVR Beta zips (BYO-ROM, file-backed images).

[CmdletBinding()]
param(
    [string]$ZipPath = "",
    [string]$StagingDir = "",
    [Parameter(Mandatory = $true)]
    [string]$CombinedBin,
    [string]$ShipTag = "vr439"
)

$ErrorActionPreference = "Stop"

if (-not $ZipPath -and -not $StagingDir) {
    throw "Pass -ZipPath and/or -StagingDir"
}
if ($ZipPath -and $StagingDir) {
    throw "Pass only one of -ZipPath or -StagingDir per invocation"
}

$requiredDlls = @(
    "glew32.dll",
    "SDL2.dll",
    "openxr_loader.dll",
    "libwinpthread-1.dll",
    "libgcc_s_seh-1.dll",
    "libstdc++-6.dll"
)

$requiredFiles = @(
    "goldeneye.exe",
    "GevrRomStarter.exe",
    "gevr_prepare.exe",
    "EXPECTED-ROM.txt",
    "Start-GEVR.bat",
    "Play-on-monitor.bat",
    "RELEASE-NOTES.txt",
    "filelist.gevr-images.csv"
)

$romExtensions = @(".z64", ".n64", ".v64")
$romNamePatterns = @("*eeprom*")

$fileBackedMarker = "[getv] images: file-backed"

function Fail([string]$msg) {
    Write-Error "[smoke] FAIL: $msg"
    exit 1
}

function Pass([string]$msg) {
    Write-Host "[smoke] OK: $msg"
}

function Get-CombinedHead64([string]$path) {
    if (-not (Test-Path -LiteralPath $path)) {
        Fail "CombinedBin not found: $path (needed for embedded-image gate)"
    }
    $bytes = [System.IO.File]::ReadAllBytes($path)
    if ($bytes.Length -lt 64) {
        Fail "CombinedBin shorter than 64 bytes"
    }
    return $bytes[0..63]
}

function Test-BinaryContainsBytes([byte[]]$haystack, [byte[]]$needle) {
    if ($needle.Length -eq 0 -or $haystack.Length -lt $needle.Length) {
        return $false
    }
    for ($i = 0; $i -le ($haystack.Length - $needle.Length); $i++) {
        $match = $true
        for ($j = 0; $j -lt $needle.Length; $j++) {
            if ($haystack[$i + $j] -ne $needle[$j]) {
                $match = $false
                break
            }
        }
        if ($match) { return $true }
    }
    return $false
}

function Test-ExeGates([string]$exePath, [byte[]]$combinedHead) {
    if (-not (Test-Path -LiteralPath $exePath)) {
        Fail "Missing goldeneye.exe at $exePath"
    }
    $exeBytes = [System.IO.File]::ReadAllBytes($exePath)
    if (Test-BinaryContainsBytes $exeBytes $combinedHead) {
        Fail "goldeneye.exe contains first 64 bytes of combined.bin (linked ROM-derived images)"
    }
    Pass "goldeneye.exe does not embed combined.bin head"

    $ascii = [System.Text.Encoding]::ASCII.GetString($exeBytes)
    # IndexOf: -like treats [getv] as a character class, so the marker never matches.
    if ($ascii.IndexOf($fileBackedMarker) -lt 0) {
        Fail "goldeneye.exe missing file-backed marker string: $fileBackedMarker"
    }
    Pass "goldeneye.exe reports file-backed images"
}

function Test-BootCmdShipTag([string]$root, [string]$expectedTag) {
    $bootName = "gevr-$expectedTag-boot.cmd"
    $bootPath = Join-Path $root $bootName
    if (-not (Test-Path -LiteralPath $bootPath)) {
        Fail "Missing $bootName (must set GEVR_SHIP_TAG=$expectedTag)"
    }
    $boot = Get-Item -LiteralPath $bootPath
    $text = Get-Content -LiteralPath $boot.FullName -Raw
    $pattern = '(?im)^\s*set\s+GEVR_SHIP_TAG\s*=\s*' + [regex]::Escape($expectedTag) + '\s*$'
    if ($text -notmatch $pattern) {
        Fail "$($boot.Name) must set GEVR_SHIP_TAG=$expectedTag"
    }
    Pass "$($boot.Name) sets GEVR_SHIP_TAG=$expectedTag"

    if ($text -notmatch '(?im)^\s*set\s+GETV_STEREO_SRC\s*=\s*xr\s*$') {
        Fail "$($boot.Name) must set GETV_STEREO_SRC=xr"
    }
    Pass "$($boot.Name) sets GETV_STEREO_SRC=xr"

    if ($text -notmatch '(?im)^\s*set\s+GETV_XR_PLAY_SRCFBO\s*=\s*1\s*$') {
        Fail "$($boot.Name) must set GETV_XR_PLAY_SRCFBO=1"
    }
    Pass "$($boot.Name) sets GETV_XR_PLAY_SRCFBO=1"

    if ($text -notmatch '(?im)^\s*set\s+GETV_SUPERSAMPLE\s*=\s*3\s*$') {
        Fail "$($boot.Name) must set GETV_SUPERSAMPLE=3"
    }
    Pass "$($boot.Name) sets GETV_SUPERSAMPLE=3"

    if ($text -notmatch '(?im)^\s*set\s+GETV_VR_SKYMESH\s*=\s*1\s*$') {
        Fail "$($boot.Name) must set GETV_VR_SKYMESH=1"
    }
    Pass "$($boot.Name) sets GETV_VR_SKYMESH=1"

    if ($text -notmatch '(?im)^\s*set\s+GETV_VR_PLAYSPACE\s*=\s*1\s*$') {
        Fail "$($boot.Name) must set GETV_VR_PLAYSPACE=1"
    }
    Pass "$($boot.Name) sets GETV_VR_PLAYSPACE=1"

    $lines = Get-Content -LiteralPath $boot.FullName
    $nonRem = @($lines | Where-Object { $_ -notmatch '^\s*rem\b' -and $_.Trim() -ne '' })
    foreach ($line in $nonRem) {
        if ($line -match '(?i)goldeneye\.exe') {
            Fail "$($boot.Name) must not invoke goldeneye.exe (Start-GEVR.bat launches GevrRomStarter.exe)"
        }
    }
    Pass "$($boot.Name) does not launch goldeneye.exe"
}

function Test-FilelistCsv([string]$csvPath) {
    if (-not (Test-Path -LiteralPath $csvPath)) {
        Fail "Missing filelist.gevr-images.csv (gevr_prepare exit 3 without it)"
    }
    $text = Get-Content -LiteralPath $csvPath -Raw
    if ([string]::IsNullOrWhiteSpace($text)) {
        Fail "filelist.gevr-images.csv is empty (gevr_prepare exit 3)"
    }
    if ($text -notmatch 'combined\.bin') {
        Fail "filelist.gevr-images.csv must list images/combined.bin"
    }
    Pass "filelist.gevr-images.csv present (combined.bin row)"
}

function Test-ReleaseNotesShipStamp([string]$notesPath) {
    if (-not (Test-Path -LiteralPath $notesPath)) {
        Fail "Missing RELEASE-NOTES.txt"
    }
    $text = Get-Content -LiteralPath $notesPath -Raw
    if ($text -notmatch 'ship stamp') {
        Fail "RELEASE-NOTES.txt must document ship stamp / cache rebuild on update"
    }
    Pass "RELEASE-NOTES.txt documents ship stamp"
}

function Test-StartBat([string]$batPath, [string]$expectedTag) {
    if (-not (Test-Path -LiteralPath $batPath)) {
        Fail "Missing Start-GEVR.bat"
    }
    $bootName = "gevr-$expectedTag-boot.cmd"
    $lines = Get-Content -LiteralPath $batPath
    $nonRem = @($lines | Where-Object { $_ -notmatch '^\s*rem\b' -and $_.Trim() -ne '' })
    $text = $nonRem -join "`n"
    $bootPattern = '(?i)' + [regex]::Escape($bootName)
    if ($text -notmatch $bootPattern) {
        Fail "Start-GEVR.bat must call $bootName"
    }
    if ($text -notmatch '(?i)GevrRomStarter\.exe') {
        Fail "Start-GEVR.bat must launch GevrRomStarter.exe"
    }
    foreach ($line in $nonRem) {
        if ($line -match '(?i)goldeneye\.exe') {
            Fail "Start-GEVR.bat must not invoke goldeneye.exe directly"
        }
    }
    Pass "Start-GEVR.bat calls $bootName then GevrRomStarter.exe"
}

function Test-MonitorBat([string]$batPath, [string]$expectedTag) {
    if (-not (Test-Path -LiteralPath $batPath)) {
        Fail "Missing Play-on-monitor.bat"
    }
    $lines = Get-Content -LiteralPath $batPath
    $nonRem = @($lines | Where-Object { $_ -notmatch '^\s*rem\b' -and $_.Trim() -ne '' })
    $text = $nonRem -join "`n"
    $tagPattern = '(?im)^\s*set\s+GEVR_SHIP_TAG\s*=\s*' + [regex]::Escape($expectedTag) + '\s*$'
    if ($text -notmatch $tagPattern) {
        Fail "Play-on-monitor.bat must set GEVR_SHIP_TAG=$expectedTag"
    }
    if ($text -notmatch '(?im)^\s*set\s+GE_VR_XR\s*=\s*0\s*$') {
        Fail "Play-on-monitor.bat must set GE_VR_XR=0"
    }
    if ($text -notmatch '(?im)^\s*set\s+GETV_STEREO\s*=\s*0\s*$') {
        Fail "Play-on-monitor.bat must set GETV_STEREO=0"
    }
    if ($text -match '(?i)gevr-.*-boot\.cmd') {
        Fail "Play-on-monitor.bat must not call a gevr-*-boot.cmd"
    }
    if ($text -notmatch '(?i)GevrRomStarter\.exe') {
        Fail "Play-on-monitor.bat must launch GevrRomStarter.exe"
    }
    foreach ($line in $nonRem) {
        if ($line -match '(?i)goldeneye\.exe') {
            Fail "Play-on-monitor.bat must not invoke goldeneye.exe directly"
        }
    }
    Pass "Play-on-monitor.bat is flat (GEVR_SHIP_TAG=$expectedTag, GE_VR_XR=0, GETV_STEREO=0, no boot cmd)"
}

function Test-Tree([string]$root) {
    foreach ($name in $requiredFiles) {
        $p = Join-Path $root $name
        if (-not (Test-Path -LiteralPath $p)) {
            Fail "Missing $name in ship tree"
        }
    }
    Pass "Required player files present"

    foreach ($dll in $requiredDlls) {
        $p = Join-Path $root $dll
        if (-not (Test-Path -LiteralPath $p)) {
            Fail "Missing runtime DLL: $dll"
        }
    }
    Pass "Required runtime DLLs present"

    Get-ChildItem -LiteralPath $root -Recurse -File | ForEach-Object {
        $ext = $_.Extension.ToLowerInvariant()
        if ($romExtensions -contains $ext) {
            Fail "ROM-like file in ship tree: $($_.FullName)"
        }
        foreach ($pat in $romNamePatterns) {
            if ($_.Name -like $pat) {
                Fail "EEPROM-like file in ship tree: $($_.FullName)"
            }
        }
    }
    Pass "No .z64/.n64/.v64/eeprom payloads in tree"

    $exe = Join-Path $root "goldeneye.exe"
    Test-ExeGates $exe $script:CombinedHead
    Test-StartBat (Join-Path $root "Start-GEVR.bat") $ShipTag
    Test-MonitorBat (Join-Path $root "Play-on-monitor.bat") $ShipTag
    Test-BootCmdShipTag $root $ShipTag
    Test-ReleaseNotesShipStamp (Join-Path $root "RELEASE-NOTES.txt")
    Test-FilelistCsv (Join-Path $root "filelist.gevr-images.csv")
}

$script:CombinedHead = Get-CombinedHead64 $CombinedBin

if ($StagingDir) {
    if (-not (Test-Path -LiteralPath $StagingDir)) {
        Fail "StagingDir not found: $StagingDir"
    }
    Write-Host "[smoke] Checking staging: $StagingDir"
    Test-Tree $StagingDir
}

if ($ZipPath) {
    if (-not (Test-Path -LiteralPath $ZipPath)) {
        Fail "ZipPath not found: $ZipPath"
    }
    $temp = Join-Path ([System.IO.Path]::GetTempPath()) ("gevr-smoke-" + [Guid]::NewGuid().ToString("n"))
    New-Item -ItemType Directory -Path $temp | Out-Null
    try {
        Expand-Archive -LiteralPath $ZipPath -DestinationPath $temp -Force
        Write-Host "[smoke] Checking zip: $ZipPath"
        Test-Tree $temp
    }
    finally {
        Remove-Item -LiteralPath $temp -Recurse -Force -ErrorAction SilentlyContinue
    }
}

Write-Host "[smoke] PASS all gates"
exit 0
