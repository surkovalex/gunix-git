#$language = "VBScript"
#$interface = "1.0"

Sub Main
Dim Counter
For Counter = 1 To 10000
crt.Screen.WaitForString "# "
crt.Screen.Send "reboot recovery" & chr(13) 	
crt.sleep 240000	
Next
End Sub