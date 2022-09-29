# Ayaya GUI

## Introduction
Ayaya GUI is a lightweight C++ GUI framework.
 - It is still in the early stage of development and a lot of things are expected to change.

## How to build
Requirements:
 - A C++17 compiler
 - Git
 - CMake
 - Vcpkg

Dependencies:
 - Skia
 - GLFW

Clone the repository
```
git clone https://github.com/whysobusy/ayaya_gui.git
```
Install the required libraries
```
vcpkg "@.\vcpkg_rf.txt"
```
Build the project
```
cd ayaya_gui
mkdir build
cd build
cmake ..//
```


## Credits
 - [elements](https://github.com/cycfi/elements)
 - [flutter engine](https://github.com/whysobusy/engine)