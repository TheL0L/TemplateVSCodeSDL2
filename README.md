# TemplateVSCodeSDL2
A basic template of an SDL2 project, with configured tasks and a basic CMake file.


To reconfigure anything, make sure to go over ./.vscode/*.json and verify all file paths.
In the CMakeLists.txt file, make sure to adjust the project name, and libraries to your needs.

Other than that, you might encounter an issue if the signature of the entry point isn't `int main(int, char**)`,
  since SDL_main overtakes the entry point and then redirects back to it.
