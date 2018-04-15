# Dog Gone Wild

You are a dog. Your owner has been kidnapped. Find your owner and catch the kidnappers.

## How to compile

Depending on what OS you are running, different tasks need to be completed.

### MacOS
* `sh install.sh` -- automatically installs SDL2, SDL2-dev, SDL2-image, SDL2-ttf, SDL2-mixer.
* `sh start.sh` -- automatically cleans, compiles, and executes the game.

### Linux (Debian)
* `sh install.sh`  -- automatically installs SDL2, SDL2-dev, SDL2-image, SDL2-ttf, SDL2-mixer.
* `sh start.sh` -- automatically cleans, compiles, and executes the game. 

### Windows 7 & 10
* After many hours of battling I got this working by compiling via command-line. You will need to install MinGW: http://www.mingw.org/
* Modify your Windows PATH to include `C:\MinGW32\bin`; you should be able to execute `gcc` in Command Prompt

#### Now we need to put `SDL2.dll` file in both 32-bit and 64-bit system locations
* Download/extract `SDL2-devel-2.x.x-mingw.tar.gz`
* Copy `i686-w64-mingw32bin\SDL2.dll` file into `C:\Windows\System\SysWOW64`.
* Copy `x86_64-w64-mingw32\bin\SDL2.dll` file into `C:\Windows\System\System32`.
* Traverse to root directory with PowerShell or Command Prompt.
* Compile code by typing `mingw32-make.exe` to run Makefile for Windows.
* Run game by typing `.\bin\main.exe`
* If you receive an error such as `Unable to start correctly` or `SDL2.dll not found`, try switching SDL2.dll placement.
* Review this StackOverflow thread: https://stackoverflow.com/questions/18389874/sdl2-dll-missing

## How to play

* Press ESC to quit the application (wow!)
* More features to be added
