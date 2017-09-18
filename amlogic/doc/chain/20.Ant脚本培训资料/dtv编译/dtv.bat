cd E:\workspace_java\dtv
e:
call ant release
cd bin 
copy dtv-release.apk D:\Android-sign\APK
cd D:\Android-sign
d:
java -jar SignUtil_All.jar A20 Amlogic SDMC


