param(
    [string]$Exe,
    [string]$Config,
    [string]$OutPrefix,
    [string]$AtMsCsv
)
$times = @($AtMsCsv.Split(',') | ForEach-Object { [int]$_ })
$argsForDosBox = "-conf `"$Config`""
& (Join-Path $PSScriptRoot 'capture_window.ps1') `
    -Exe $Exe `
    -ArgList $argsForDosBox `
    -OutPrefix $OutPrefix `
    -AtMs $times
