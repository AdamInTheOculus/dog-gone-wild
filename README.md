# Dog Gone Wild

You are a dog. Your owner has been kidnapped. Stop the kidnappers and find your owner.

## How to play

* Press WASD to run different animations. Placeholder sprites used from https://www.spriters-resource.com/snes/ff6/. Released game will contain sprites created by me.
* Press ESC to quit the application (wow!)
* More features to be added

## How to compile

### MacOS
* `sh install.sh` -- automatically installs SDL2, SDL2-dev, SDL2-image, SDL2-ttf, SDL2-mixer.
* `sh build.sh` -- automatically cleans, compiles, and executes the game.

### Linux (Debian)
* `sh install.sh`  -- automatically installs SDL2, SDL2-dev, SDL2-image, SDL2-ttf, SDL2-mixer.
* `sh build.sh` -- automatically cleans, compiles, and executes the game. 

### Windows 7 & 10
* Install MinGW http://www.mingw.org/ -- (TODO: Reason goes here)
* Modify Windows PATH to include `C:\MinGW32\bin`. You should be able to execute `gcc` in Command Prompt.

#### Now we need to put `SDL2.dll` file in both 32-bit and 64-bit system locations (Windows)
* Download/extract `SDL2-devel-2.x.x-mingw.tar.gz`
* Copy `i686-w64-mingw32bin\SDL2.dll` file into `C:\Windows\System\SysWOW64`.
* Copy `x86_64-w64-mingw32\bin\SDL2.dll` file into `C:\Windows\System\System32`.
* Traverse to root directory with PowerShell or Command Prompt.
* Compile code by typing `mingw32-make.exe` to run Makefile for Windows.
* Run game by typing `.\bin\main.exe`
* If you receive an error such as `Unable to start correctly` or `SDL2.dll not found`, try switching SDL2.dll placement.
* Review this StackOverflow thread: https://stackoverflow.com/questions/18389874/sdl2-dll-missing
