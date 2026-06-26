Johann Naranjo

for GDENG03_X21

NOTE: I am running on a mac device, there may be some quirks that won't work on your windows device, such as reverse slashes,,, or the fact that it is using vscode (since no vs on mac)

Anyways, here's general instructions on how I ran it

1. Copy the code from the github
2. Open GDENG03 on VS Code
3. Change tasks.json to follow this:
{
  "version": "2.0.0",
  "tasks": [
    {
      "type": "cppbuild",
      "label": "C/C++: clang++ build active file",
      "command": "/usr/bin/clang++",
      "args": [
        "-std=c++17",
        "-fdiagnostics-color=always",
        "-Wall",
        "-g",

        "-I${workspaceFolder}/Dependencies/include",
        "-I${workspaceFolder}/Source/Headers",

        "${workspaceFolder}/Dependencies/include/glad/glad.c",
        "${workspaceFolder}/Source/main.cpp",
        "${workspaceFolder}/Source/quad.cpp",
        "${workspaceFolder}/Source/circle.cpp",
        "${workspaceFolder}/Source/cube.cpp",
        "${workspaceFolder}/Source/sphere.cpp",
        "${workspaceFolder}/Source/cylinder.cpp",
        "${workspaceFolder}/Source/random.cpp",
        "${workspaceFolder}/Source/transform.cpp",
        "${workspaceFolder}/Source/Managers/window_manager.cpp",
        "${workspaceFolder}/Source/Managers/input_manager.cpp",
        "${workspaceFolder}/Source/Managers/shaders_reader.cpp",
        "${workspaceFolder}/Source/Camera_Scripts/camera.cpp",
        "${workspaceFolder}/Source/Camera_Scripts/orthographic_camera.cpp",
        "${workspaceFolder}/Source/Camera_Scripts/perspective_camera.cpp",

        "${workspaceFolder}/Dependencies/include/imgui/imgui.cpp",
        "${workspaceFolder}/Dependencies/include/imgui/imgui_draw.cpp",
        "${workspaceFolder}/Dependencies/include/imgui/imgui_tables.cpp",
        "${workspaceFolder}/Dependencies/include/imgui/imgui_widgets.cpp",
        "${workspaceFolder}/Dependencies/include/imgui/imgui_demo.cpp",
        "${workspaceFolder}/Dependencies/include/imgui/imgui_impl_glfw.cpp",
        "${workspaceFolder}/Dependencies/include/imgui/imgui_impl_opengl3.cpp",

        "${workspaceFolder}/Dependencies/library/libglfw.3.4.dylib",

        "-framework",
        "OpenGL",
        "-framework",
        "Cocoa",
        "-framework",
        "IOKit",
        "-framework",
        "CoreVideo",
        "-framework",
        "CoreFoundation",

        "-o",
        "${workspaceFolder}/Builds/app",
        "-Wno-deprecated"
      ],
      "options": {
        "cwd": "${workspaceFolder}"
      },
      "problemMatcher": [
        "$gcc"
      ],
      "group": {
        "kind": "build",
        "isDefault": true
      },
      "detail": "compiler: /usr/bin/clang++"
    }
  ]
}

4. if the build button doesn't work, build with [Command+Shift+B] on Mac (Ctrl+Shift+B I guess on windows...)
5. If the button doesn't work to run it either, type in the terminal ./Builds/app