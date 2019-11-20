#!/bin/bash
clear; clear; clear;
echo "#############################"
sudo su
sudo apt install build-essential git cmake libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev
git clone https://github.com/raysan5/raylib.git raylib
cd raylib/src/
make PLATFORM=PLATFORM_DESKTOP # To make the static version.
sudo make install # Static version.

