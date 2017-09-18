#$language = "VBScript"
#$interface = "1.0"

Sub Main
Dim Counter
For Counter = 1 To 10000	
crt.sleep 12000000
crt.Screen.Send "input keyevent  23" & chr(13) 
crt.Screen.WaitForString "# "	
Next
End Sub