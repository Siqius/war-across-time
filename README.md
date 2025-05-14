# About
An age of war inspired game made in C++ using [Raylib](https://www.raylib.com/)

# Supported platforms
* Windows
  * [Msys2](https://github.com/msys2/msys2-installer/releases/download/2025-02-21/msys2-x86_64-20250221.exe) is needed to compile the game
    * Open MSYS2 MINGW64
    * Run `pacman -S git mingw-w64-x86_64-raylib mingw-w64-x86_64-gcc` to install dependencies
* Linux/MacOS
  * Install `raylib`, `g++` and `make` using a package manager (apt, brew, etc.)

# Dependencies
* Raylib
* make
* g++

# Installation
Clone the repository: <br>
`git clone https://github.com/Siqius/war-across-time.git` <br> <br>
Go into the directory: <br>
`cd war-across-time` <br> <br>
Compile the game: <br>
`make`

After compiling, you can find the executable in `\build\WarAcrossTime`, <br>
or `C:\msys64\home\{user}\war-across-time\target\build\WarAcrossTime.exe` if you're on windows
