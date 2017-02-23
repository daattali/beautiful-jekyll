break
# Include Process info as text output
[string] $string = Get-Process -Name 'Chrome'
$string

# Capture Process info as text (fixed)
[string] $string = Get-Process -Name 'Chrome' | Out-String
$string

# Differences between objects and strings
(Get-Process)[1]                        #PSObject
(Get-Process | Out-String -Stream)[1]   #String