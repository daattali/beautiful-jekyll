Get-help ConvertFrom-String -ShowWindow

$klistoutput = get-content C:\personal\PSUG\CincyPowerShell.github.io\presentations\2016-09\code\klist.txt

get-content C:\personal\PSUG\CincyPowerShell.github.io\presentations\2016-09\code\template.txt

C:\personal\PSUG\CincyPowerShell.github.io\presentations\2016-09\code\template.txt

klist | ConvertFrom-String -TemplateFile C:\personal\PSUG\CincyPowerShell.github.io\presentations\2016-09\code\template.txt | Out-GridView

$klistoutput | ConvertFrom-String -TemplateFile C:\personal\PSUG\CincyPowerShell.github.io\presentations\2016-09\code\template.txt | Out-GridView

