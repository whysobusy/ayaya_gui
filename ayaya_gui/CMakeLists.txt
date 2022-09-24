# CMakeList.txt : CMake project for ayaya_gui, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (ayaya "ayaya_gui.cpp" "ayaya_gui.h")
target_compile_features(ayaya PUBLIC cxx_std_17)

find_package(OPENGL REQUIRED)
target_link_libraries(ayaya PRIVATE ${OPENGL_LIBRARIES})

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(ayaya PRIVATE glfw)

# Skia vcpkg seems to fail setting dll_export vs. dll_import flags correctly.
# SKIA_IMPLEMENTATION=1 is evaluated to __declspec(dll_export) when compiling 
# the demo but it has to be __declspec(dll_import).
# Hence we overwrite SKIA_IMPLEMENTATION=1 by SKIA_IMPLEMENTATION=0!
find_package(skia CONFIG REQUIRED)
# UNCOMMENT TO FIX LINK ERRORS
get_target_property(skia_interface_defs skia INTERFACE_COMPILE_DEFINITIONS)
string(REPLACE "SKIA_IMPLEMENTATION=1" "SKIA_IMPLMENTATION=0" skia_interface_defs_fixed "${skia_interface_defs}")
set_target_properties(skia PROPERTIES INTERFACE_COMPILE_DEFINITIONS "${skia_interface_defs_fixed}")
target_link_libraries(ayaya PRIVATE skia skia::skia)
