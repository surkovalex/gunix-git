#$language = "VBScript"
#$interface = "1.0"

Sub Main
crt.Screen.Send "root" & chr(13)
crt.Screen.WaitForString "# "
crt.Screen.Send "mkdir /mnt/nfs" & chr(13)
crt.Screen.WaitForString "# "
crt.Screen.Send "mount /dev/sda1 /mnt/nfs" & chr(13)
crt.Screen.WaitForString "#"
crt.Screen.Send "cp -rf /mnt/nfs/ubi_boot/* /cust_part_1" & chr(13)
crt.Screen.WaitForString "#"
End Sub
