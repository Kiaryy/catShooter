#!/bin/sh
if [ "$1" == "linux" ]; then
    tar -czvf release/linux/catShooterLinux.tar.gz assets/ -C build/ catShooter  

elif [ "$1" == "windows" ]; then
    tar -czvf release/windows/catShooterWindows.tar.gz assets/ -C build/ catShooter.exe
else
    echo "What is bro talking about"
fi