#!/usr/bin/env bash


if [ "$(uname)" = "Linux" ]; then

    echo "Linux-GNU system."
    echo "Installing SDL2 onto computer ..."
    sudo apt-get install libsdl2-2.0 libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev
    clear
    # echo "Installing SDL2 development tools onto computer ..."
    # sudo apt-get install libsdl2-dev
    # clear
    # echo "Installing SDL2 image tools onto computer ..."
    # sudo apt-get install libsdl2-image-dev
    # clear
    # echo "Installing SDL2 True Type Font tools onto computer ..."
    # sudo apt-get install libsdl2-ttf-dev
    # clear
    # echo "Installing SDL2 mixer tools onto computer ..."
    # sudo apt-get install libsdl2-mixer-dev
    clear
    echo "Successfully installed all required software."

elif [ "$(uname)" = "Darwin" ]; then

    clear
    echo "MacOS system."
    echo "Installing SDL2 onto computer ..."
    brew install sdl2 sdl2_image sdl2_mixer sdl2_ttf
    clear
    echo "Successfully installed all required software."

elif [ "$(uname)" = "cygwin" ]; then

    # POSIX compatibility layer and Linux environment emulation for Windows
    echo "Cygwin system."
    echo "Installing SDL2 onto computer ..."
    echo "Installing SDL2 development tools onto computer ..."
    echo "Installing SDL2 image tools onto computer ..."
    echo "Installing SDL2 True Type Font tools onto computer ..."
    echo "Installing SDL2 mixer tools onto computer ..."

elif [ "$(uname)" = "msys" ]; then

    # Lightweight shell and GNU utilities compiled for Windows (part of MinGW)
    echo "Msys system."
    echo "Installing SDL2 onto computer ..."
    echo "Installing SDL2 development tools onto computer ..."
    echo "Installing SDL2 image tools onto computer ..."
    echo "Installing SDL2 True Type Font tools onto computer ..."
    echo "Installing SDL2 mixer tools onto computer ..."

elif [ "$(uname)" = "win32" ]; then

    echo "Win32 system."
    echo "Installing SDL2 onto computer ..."
    echo "Installing SDL2 development tools onto computer ..."
    echo "Installing SDL2 image tools onto computer ..."
    echo "Installing SDL2 True Type Font tools onto computer ..."
    echo "Installing SDL2 mixer tools onto computer ..."
fi
