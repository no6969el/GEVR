# Ship-blocker smoke gates for GEVR Beta zips (BYO-ROM, file-backed images).
#
# 2026-09-16: this file was a SINGLE LINE with no newlines, so PowerShell read the
# whole thing as one comment. It ran, did nothing, and gated nothing -- which is how
# the vr440 short boot template reached the public zip. Rewritten with real line
# endings, and the boot-content gate below is the one that would have caught it.
[CmdletBinding()]
param(
    [string]$ZipPath = "",
    [string]$StagingDir = "",
    [Parameter(Mandatory = $true)]
    [string]$CombinedBin,
    [string]$ShipTag = "vr441"
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
    "filelist.gevr-images.csv",
    "EXPECTED-ROM.txt",
    "Start-GEVR.bat",
    "Play-on-monitor.bat",
    "RELEASE-NOTES.txt"
)

# The live KEEP + PLAY0 allowlist. Every one of these must be assigned, with this
# value, in gevr-*-boot.cmd. A stub or picture-only boot fails here.
$requiredBootKnobs = [ordered]@{
    # chair features vr440 never turned on
    "GETV_VR_CORPSEKEEP"        = "1"
    "GETV_VR_CORPSEKEEP_MAX"    = "48"
    "GETV_VR_CORPSEKEEP_CEIL"   = "440"
    "GETV_VR_TEXINVAL"          = "1"
    "GETV_VR_TEXDLRETAG"        = "1"
    "GETV_VR_VFXTMEM"           = "1"
    "GETV_VR_VFXSHIFT"          = "1"
    "GETV_TEX16BE"              = "1"
    "GETV_RGBA16BE"             = "0"
    "GETV_TEX32BE"              = "1"
    # PLAY0 arm
    "GETV_VR_VTXGUARD"          = "64"
    "GETV_VR_ADSSIGHT"          = "1"
    "GETV_VR_HITSNAP"           = "2"
    "GETV_VR_SIGHTPX"           = "6"
    "GETV_VR_ADSCULL"           = "1"
    # aim / hands / gun / playspace
    "GETV_VR_HEADYAW"           = "1"
    "GETV_VR_HEADFRAME"         = "2"
    "GETV_VR_HANDYAW"           = "2"
    "GETV_VR_LEVELYAW"          = "1"
    "GETV_VR_GUNAIM"            = "1"
    "GETV_VR_GUNMOUNT"          = "1"
    "GETV_VR_GUNARM"            = "1"
    "GETV_VR_PLAYSPACE"         = "1"
    "GETV_VR_BODY_NOARMS"       = "1"
    "GETV_XR_FLOOR_M"           = "-0.200"
    "GETV_VR_HANDCUBES"         = "1"
    "GETV_VR_CASINGS"           = "1"
    "GETV_VR_RETICLE"           = "1"
    "GETV_VR_TOUCHUSE"          = "1"
    "GETV_VR_HANDMELEE"         = "1"
    # #75 swing pose KEEP
    "GETV_VR_SWINGHIT"          = "1"
    "GETV_VR_SWINGPOSE"         = "1"
    "GETV_VR_GUNREBASE"         = "1"
    # picture KEEP
    "GETV_SUPERSAMPLE"          = "3"
    "GETV_XR_PLAY_SRCFBO"       = "1"
    "GETV_XR_PLAY_EYERECT"      = "1"
    # #72 Dam jump-strip: cloud remesh OFF (was 1). SKYPIN KEEP covers look-up.
    "GETV_VR_SKYMESH"           = "0"
    "GETV_VR_SKYSCISSOR"        = "1"
    # Dam SKYWORLD KEEP (retire SKYINF while SKYWORLD on)
    "GETV_VR_SKYWORLD"          = "1"
    "GETV_VR_SKYINF"            = "0"
    # vr444 KEEP (throwables / hand cube / modem scrap)
    "GETV_VR_THROWGRIP"         = "2"
    "GETV_VR_HANDCUBE_HIDEARMED"= "1"
    "GETV_VR_MODEMDROP"         = "3"
    "GETV_VR_HANDCUBE_MM"       = "45"
    "GETV_BIND_WEAPON_PREV"     = "x"
    # vr445.2 KEEP
    "GETV_VR_JANUSSPAWN"        = "1"
    "GETV_VR_GUNORIGIN"         = "1"
    "GETV_AI_ANIMFRAMES"        = "1"
    # vr450 KEEP (#80 water RECT + #90 grip doors)
    "GETV_VR_SKYWATERRECT"      = "1"
    "GETV_VR_GRIPUSE"           = "1"
    # core VR (#49: GETV_FPS must stay unset so EXE 421/422 follow HMD)
    "GETV_VR"                   = "1"
    "GETV_SIMDIV"               = "1"
    "GETV_SIMHZ"                = "query"
    "GETV_STEREO_SRC"           = "xr"
    "GE_VR_XR"                  = "1"
}

# Knobs that must NOT be armed in a public boot.
$forbiddenBootKnobs = @(
    "GETV_FPS",
    "GETV_XR_FOVMATCH",
    "GETV_VR_WALLCENSUS",
    "GETV_VR_ROOMLOADWHY",
    "GETV_FIREDUMP",
    "GETV_STAGE",
    "GETV_CHR_DEBUG",
    "GETV_INPUT_DEBUG",
    "GETV_FRONTTRACE",
    "GETV_CINETRACE",
    "GETV_LOGFLUSH",
    "GETV_SKYTRACE",
    "GETV_ROOMTRACE",
    "GETV_CULLWHY",
    "GETV_XR_SHARPLOG",
    "GETV_VR_SKYWATERLERP",
    "GETV_VR_SKYWATERLAYER",
    "GETV_VR_SKYWATERUV",
    "GETV_VR_TEXGUARD",
    "GETV_VR_SCRAPDROP",
    "GETV_VR_EMBEDEYE",
    "GETV_VR_FALSEDOOR",
    "GETV_VR_CHRPASS",
    "GETV_VR_FRIGWHY",
    "GETV_VR_DOORLOS",
    "GETV_VR_FRIGMUTE",
    "GETV_VR_FRIGDOORROOM",
    "GETV_VR_FRIGOPEN",
    "GETV_STEREO_MTXGUARD"
)

# Names that are not knobs in goldeneye.exe. Setting them is a silent no-op and has
# shipped before (vr440 set both). Fail rather than let a typo look like a feature.
$deadBootKnobs = @(
    "GETV_SRCFBO",
    "GETV_MSGSCALE"
)

# Legacy names that are also no-ops but are deliberately kept. GE_VR_XR appears in no
# getv source and in no binary string; the VR arm is gated on GETV_VR (gevr_xr.c
# geVrXrEnabled -- unset means off). Play-on-monitor.bat's gate still requires
# GE_VR_XR=0, so the name stays and is excepted here rather than failing the build.
$knownNoOpKnobs = @(
    "GE_VR_XR"
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

    return $ascii
}

function Get-BootCmd([string]$root) {
    $boot = Get-ChildItem -LiteralPath $root -Filter "gevr-*-boot.cmd" | Select-Object -First 1
    if (-not $boot) {
        Fail "Missing gevr-*-boot.cmd (must set GEVR_SHIP_TAG and the KEEP allowlist)"
    }
    return $boot
}

function Test-BootCmdShipTag($boot, [string]$expectedTag) {
    $text = Get-Content -LiteralPath $boot.FullName -Raw
    $pattern = '(?im)^\s*set\s+GEVR_SHIP_TAG\s*=\s*' + [regex]::Escape($expectedTag) + '\s*$'
    if ($text -notmatch $pattern) {
        Fail "$($boot.Name) must set GEVR_SHIP_TAG=$expectedTag"
    }
    Pass "$($boot.Name) sets GEVR_SHIP_TAG=$expectedTag"
}

# THE GATE THAT WOULD HAVE CAUGHT vr440. A boot cmd that does not arm the live KEEP
# and PLAY0 set is a stub, however well-formed it looks.
function Test-BootCmdAllowlist($boot, [string]$exeAscii) {
    $text = Get-Content -LiteralPath $boot.FullName -Raw

    # A flattened file (no newlines) passes regexes by accident; refuse it outright.
    if ($text -notmatch "`n") {
        Fail "$($boot.Name) has no line breaks - the file is one line and cmd cannot read it"
    }

    $missing = @()
    foreach ($name in $requiredBootKnobs.Keys) {
        $want = $requiredBootKnobs[$name]
        $pattern = '(?im)^\s*set\s+' + [regex]::Escape($name) + '\s*=\s*' + [regex]::Escape($want) + '\s*$'
        if ($text -notmatch $pattern) {
            $missing += ("{0}={1}" -f $name, $want)
        }
    }
    if ($missing.Count -gt 0) {
        Fail ("$($boot.Name) is not the live KEEP boot - {0} knob(s) missing or wrong: {1}" -f $missing.Count, ($missing -join ", "))
    }
    Pass ("$($boot.Name) arms all {0} KEEP + PLAY0 knobs" -f $requiredBootKnobs.Count)

    $armed = @()
    foreach ($name in $forbiddenBootKnobs) {
        # Armed means assigned a value that is neither empty nor 0, ON THE SAME LINE.
        # "set X=" (the clear) and "set X=0" (pinned off) are both fine and expected.
        # \s on the value side would cross the newline and match the next line, so the
        # capture is [^\r\n] only.
        $pattern = '(?im)^[ \t]*set[ \t]+' + [regex]::Escape($name) + '[ \t]*=([^\r\n]*)'
        foreach ($m in [regex]::Matches($text, $pattern)) {
            $val = $m.Groups[1].Value.Trim()
            if ($val -ne '' -and $val -ne '0') {
                $armed += ("{0}={1}" -f $name, $val)
            }
        }
    }
    if ($armed.Count -gt 0) {
        Fail ("$($boot.Name) arms falsifier/instrument knob(s) in a public boot: {0}" -f (($armed | Sort-Object -Unique) -join ", "))
    }
    Pass "$($boot.Name) arms no falsifier or instrument knobs"

    $dead = @()
    foreach ($name in $deadBootKnobs) {
        $pattern = '(?im)^[ \t]*set[ \t]+' + [regex]::Escape($name) + '[ \t]*=[ \t]*[^\s]'
        if ($text -match $pattern) {
            $dead += $name
        }
    }
    if ($dead.Count -gt 0) {
        Fail ("$($boot.Name) sets name(s) that are not knobs in this goldeneye.exe (silent no-op): {0}" -f ($dead -join ", "))
    }
    Pass "$($boot.Name) sets no dead knob names"

    # Every GETV_/GEVR_ name the boot ARMS must actually exist in the binary.
    $unknown = @()
    foreach ($m in [regex]::Matches($text, '(?im)^[ \t]*set[ \t]+((?:GETV|GEVR|GE_VR)_[A-Z0-9_]+)[ \t]*=[ \t]*[^\s]')) {
        $name = $m.Groups[1].Value
        if ($name -eq "GEVR_SHIP_TAG") { continue }
        if ($knownNoOpKnobs -contains $name) { continue }
        if ($exeAscii.IndexOf($name) -lt 0) {
            $unknown += $name
        }
    }
    if ($unknown.Count -gt 0) {
        Fail ("$($boot.Name) arms name(s) absent from goldeneye.exe: {0}" -f (($unknown | Sort-Object -Unique) -join ", "))
    }
    Pass "every knob the boot arms exists in goldeneye.exe"
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

function Test-StartBat([string]$batPath, $boot) {
    if (-not (Test-Path -LiteralPath $batPath)) {
        Fail "Missing Start-GEVR.bat"
    }
    $lines = Get-Content -LiteralPath $batPath
    $nonRem = @($lines | Where-Object { $_ -notmatch '^\s*rem\b' -and $_ -notmatch '^\s*REM\b' -and $_.Trim() -ne '' })
    $text = $nonRem -join "`n"
    if ($text -notmatch '(?i)GevrRomStarter\.exe') {
        Fail "Start-GEVR.bat must launch GevrRomStarter.exe"
    }
    # It must call THIS zip's boot cmd, not a stale tag's.
    if ($text -notmatch [regex]::Escape($boot.Name)) {
        Fail "Start-GEVR.bat must call $($boot.Name)"
    }
    foreach ($line in $nonRem) {
        if ($line -match '(?i)goldeneye\.exe') {
            Fail "Start-GEVR.bat must not invoke goldeneye.exe directly"
        }
    }
    Pass "Start-GEVR.bat calls $($boot.Name) then GevrRomStarter.exe"
}

function Test-MonitorBat([string]$batPath) {
    if (-not (Test-Path -LiteralPath $batPath)) {
        Fail "Missing Play-on-monitor.bat"
    }
    $lines = Get-Content -LiteralPath $batPath
    $nonRem = @($lines | Where-Object { $_ -notmatch '^\s*rem\b' -and $_ -notmatch '^\s*REM\b' -and $_.Trim() -ne '' })
    $text = $nonRem -join "`n"
    if ($text -notmatch '(?im)^\s*set\s+GE_VR_XR\s*=\s*0\s*$') {
        Fail "Play-on-monitor.bat must set GE_VR_XR=0"
    }
    if ($text -notmatch '(?im)^\s*set\s+GETV_STEREO\s*=\s*0\s*$') {
        Fail "Play-on-monitor.bat must set GETV_STEREO=0"
    }
    if ($text -notmatch '(?im)^\s*set\s+GETV_AUDIO_CLOCK\s*=\s*device\s*$') {
        Fail "Play-on-monitor.bat must set GETV_AUDIO_CLOCK=device (#48 audio sync)"
    }
    if ($text -notmatch '(?im)^\s*set\s+GETV_AUDIO_QUEUE_MS\s*=\s*33\s*$') {
        Fail "Play-on-monitor.bat must set GETV_AUDIO_QUEUE_MS=33 (#48 audio sync)"
    }
    if ($text -match '(?i)gevr-vr\d+-boot\.cmd') {
        Fail "Play-on-monitor.bat must not call any gevr-*-boot.cmd"
    }
    if ($text -notmatch '(?i)GevrRomStarter\.exe') {
        Fail "Play-on-monitor.bat must launch GevrRomStarter.exe"
    }
    foreach ($line in $nonRem) {
        if ($line -match '(?i)goldeneye\.exe') {
            Fail "Play-on-monitor.bat must not invoke goldeneye.exe directly"
        }
    }
    Pass "Play-on-monitor.bat is flat (GE_VR_XR=0, GETV_STEREO=0, no boot cmd)"
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
    $exeAscii = Test-ExeGates $exe $script:CombinedHead

    $boot = Get-BootCmd $root
    Test-BootCmdShipTag $boot $ShipTag
    Test-BootCmdAllowlist $boot $exeAscii

    Test-StartBat (Join-Path $root "Start-GEVR.bat") $boot
    Test-MonitorBat (Join-Path $root "Play-on-monitor.bat")
    Test-ReleaseNotesShipStamp (Join-Path $root "RELEASE-NOTES.txt")
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
