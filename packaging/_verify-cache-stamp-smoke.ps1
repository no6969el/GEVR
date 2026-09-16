# Manual smoke: simulate stamp mismatch invalidation on a fake cache dir (no ROM).
# Run on Windows after integrating ship stamp in gevr_prepare / GevrRomStarter.

[CmdletBinding()]
param(
    [string]$ShipTag = "vr438",
    [string]$FakeSha = "deadbeefdeadbeefdeadbeefdeadbeefdeadbeefdeadbeefdeadbeefdeadbeef"
)

$ErrorActionPreference = "Stop"

$root = Join-Path $env:TEMP ("gevr-stamp-smoke-" + [Guid]::NewGuid().ToString("n"))
$cache = Join-Path $root "GEVR\cache\$FakeSha"
New-Item -ItemType Directory -Path $cache -Force | Out-Null

# Stale cache: ready from older cut, wrong ship.txt
New-Item -ItemType File -Path (Join-Path $cache "ready") -Force | Out-Null
Set-Content -LiteralPath (Join-Path $cache "combined.bin") -Value "stale" -NoNewline
Set-Content -LiteralPath (Join-Path $cache "ship.txt") -Value "vr437"

$env:GEVR_SHIP_TAG = $ShipTag
$env:GEVR_ROM_SHA256 = $FakeSha
$env:GEVR_CACHE_DIR = $cache
$prepare = Join-Path $PSScriptRoot "rom-starter\gevr_prepare.exe"

if (-not (Test-Path -LiteralPath $prepare)) {
    Write-Host "[stamp-smoke] SKIP: build gevr_prepare.exe on SimRig and copy here, or run after product merge."
    Write-Host "[stamp-smoke] Manual check: set GEVR_SHIP_TAG=$ShipTag, ensure ready+ship.txt=vr437, launch Start-GEVR.bat"
    Remove-Item -LiteralPath $root -Recurse -Force
    exit 0
}

& $prepare "C:\path\to\rom.z64" 2>&1 | Out-Host

if (Test-Path -LiteralPath (Join-Path $cache "ready")) {
    throw "[stamp-smoke] FAIL: ready should be removed on stamp mismatch before prepare completes"
}
Write-Host "[stamp-smoke] OK: stale ready removed on mismatch (integrate extract to finish full prepare)"

Remove-Item -LiteralPath $root -Recurse -Force
exit 0
