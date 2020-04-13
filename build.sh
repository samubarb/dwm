#!/usr/bin/env sh

cd ~/dwm
sudo make clean install &&
    killall dwm
