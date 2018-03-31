# Dog Gone Wild

You are a dog. Your owner has been kidnapped. Find your owner and catch the kidnappers.

## How to compile

Depending on what OS you are running, different tasks need to be completed.

### MacOS
* `brew install sdl2` -- downloads SDL2 code and places in /usr directory
* `sh start.sh` -- automatically cleans, compiles, and executes the game.

### Linux (Debian)
* `sh install.sh`  -- automatically installs SDL2 and SDL2-dev.
* `sh start.sh` -- automatically cleans, compiles, and executes the game. 

### Windows 7
* After many hours of battling I got this working by compiling via command-line. You will need to install MinGW: http://www.mingw.org/
* Modify your Windows PATH to include `C:\MinGW32\bin`
* Using Powershell, traverse to the game directory.
* Compile code by typing `mingw32-make.exe` to run Makefile for Windows.
* Run game by typing `.\bin\main.exe`

## How to play

* Press ESC to quit the application (wow!)
* More features to be added
