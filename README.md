# TemplateVSCodeSDL2
A basic template of an SDL2 project, with configured tasks and a basic CMake file.


To reconfigure anything, make sure to go over ./.vscode/*.json and verify all file paths.
In the CMakeLists.txt file, make sure to adjust the project name, and libraries to your needs.

Other than that, you might encounter an issue if the signature of the entry point isn't `int main(int, char**)`,
  since SDL_main overtakes the entry point and then redirects back to it.

Setting up SDL2 was done via msys2 and it's package manager pacman, for the ucrt64 chaintool.
To search and install the SDL2 packages use the following commands:
```
  pacman -Ss mingw-w64-ucrt-x86_64-SDL2       # list all SDL2 packages for the ucrt64 toolchain
  pacman -Qs <package name>                   # list all installed packages, filtered to include <package name>
  pacman -S <package name>                    # install a specific package
```

To simply install all SDL2 packages in one go, use the following command:
```
  pacman -S mingw-w64-ucrt-x86_64-SDL2*       # will install all packages starting with "mingw-w64....-SDL2"
```
