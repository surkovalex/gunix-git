#!/system/bin/sh
i=1
while [[ $i > 0 ]]
do
    echo "$i times"
    input keyevent DPAD_DOWN
    sleep 4
    input keyevent DPAD_DOWN
    sleep 4
    input keyevent DPAD_DOWN
    sleep 4
    input keyevent DPAD_UP
    sleep 5
    input keyevent DPAD_UP
    sleep 5
    input keyevent DPAD_UP
    sleep 5
    input keyevent DPAD_UP
    sleep 5
    input keyevent DPAD_UP
    sleep 2
    input keyevent DPAD_DOWN
    sleep 4
    input keyevent DPAD_DOWN
    sleep 4
    input keyevent DPAD_UP
    sleep 5
    input keyevent DPAD_DOWN
    sleep 4
    input keyevent DPAD_DOWN
    sleep 4
    input keyevent DPAD_UP
    sleep 5
    i=$(($i+1))
done