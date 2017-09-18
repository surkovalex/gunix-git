#$language = "VBScript"
#$interface = "1.0"

Sub Main
Dim Counter
For Counter = 1 To 10000	
crt.Screen.Send "top -n 1 | grep mediaserver && procmem  2613  | grep  AudioFlinger" & chr(13) 
crt.Screen.WaitForString "# "	
Next
End Sub