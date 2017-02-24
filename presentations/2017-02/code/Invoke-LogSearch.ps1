
cls

#	Pops out an input box for desired string to be found. 
[System.Reflection.Assembly]::LoadWithPartialName('Microsoft.VisualBasic') | Out-Null
[string]$SearchTerm = [Microsoft.VisualBasic.Interaction]::InputBox("Enter the desired search string.
(Beware of trailing spaces!)", "Log Search", "")
# First is text of box, then Title Bar of box, then default value. In this case, blank.


[System.Reflection.Assembly]::LoadWithPartialName('Microsoft.VisualBasic') | Out-Null
[int]$ErrorMonth = [Microsoft.VisualBasic.Interaction]::InputBox("Search what month?", "Log Search", "$(Get-Date -Uformat %m)")
# First is text of box, then Title Bar of box, then default value. In this box, today's month.
$date = get-date

[System.Reflection.Assembly]::LoadWithPartialName('Microsoft.VisualBasic') | Out-Null
[int]$ErrorDay = [Microsoft.VisualBasic.Interaction]::InputBox("Search what day?", "Log Search",  "$(Get-Date -Uformat %d)")
# First is text of box, then Title Bar of box, then default value. In this box, today's day.

break
$searchTerm = $SearchTerm.Trim()
$errormonth = (get-date).month
## Could use VisualBasic Calendar control for the date field.


# Start the loop of web servers, sequentially numbered 51-55
For ($Server=51; $Server -le 55; $Server++)
{
cd "\\COMPANY-WEB$($Server)\c$\logs"
 Get-ChildItem -filter *-2017*$ErrorMonth*$ErrorDay* | Select-String $($SearchTerm) | Select-Object -Unique path
 # Pulls the full path for the file where the string has been found.
 
 Write-Host " "
  Get-ChildItem -filter *-2017*$ErrorMonth*$ErrorDay* | Select-String $($SearchTerm) | %{$_.Line.Split("|")}
 # Pull the error, and inserts line breaks to replace each pipe.
 
  
# Use the next line instead if you want to be able to search further in the results
# Get-ChildItem -filter *-2017*$ErrorMonth*$ErrorDay* | Select-String $($SearchTerm) | Out-GridView

# Use the next line instead if you want no date used (longer search times)
# Get-ChildItem | Select-String $($SearchTerm) | %{$_.Line.Split("|")}
}


# Start the loop of app servers, sequentially numbered 61-64
For ($Server=61; $Server -le 64; $Server++)
{
cd "\\COMPANY-APP$($Server)\c$\logs"
 Get-ChildItem -filter *-2017*$ErrorMonth*$ErrorDay* | Select-String $($SearchTerm) | Select-Object -Unique path
 # Pulls the full path for the file where the string has been found.
 
 Write-Host " "
  Get-ChildItem -filter *-2017*$ErrorMonth*$ErrorDay* | Select-String $($SearchTerm) | %{$_.Line.Split("|")}
# Pull the error, and inserts line breaks to replace each pipe.
  
  
# Use the next line instead if you want to be able to search further in the results
# Get-ChildItem -filter *-2017*$ErrorMonth*$ErrorDay* | Select-String $($SearchTerm) | Out-GridView

# Use the next line instead if you want no date used (longer search times)
# Get-ChildItem | Select-String $($SearchTerm) | %{$_.Line.Split("|")}
}