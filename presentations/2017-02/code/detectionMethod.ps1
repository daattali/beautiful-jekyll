$appName = 'Visual Studio Code'
$appVersion = '1.9.1'
$apps = Get-ChildItem -Path 'HKLM:\SOFTWARE\WOW6432Node\Microsoft\Windows\CurrentVersion\Uninstall', 'HKLM:\SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall' | Get-ItemProperty -Include DisplayVersion | Where-Object { $_.DisplayName -like "*$appName*" }
foreach ($app in $apps) {
    if ([System.Version]$app.DisplayVersion -ge [System.Version]$appVersion) {
        Write-Host 'Installed'
    }
}