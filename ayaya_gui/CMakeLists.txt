# CMakeList.txt : CMake project for ayaya_gui, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(ayaya_sources
    src/paint/rect.cpp
    src/paint/canvas.cpp
    src/widget/widget.cpp
    src/widget/composite.cpp
    src/widget/layer.cpp
    src/widget/basic.cpp
    src/window.cpp
    src/app.cpp
)

set(ayaya_headers
    ${CMAKE_CURRENT_SOURCE_DIR}/include/paint/canvas.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/paint/path.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/paint/color.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/paint/context.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/paint/key.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/paint/point.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/paint/rect.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/paint/utils.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/widget/composite.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/widget/basic.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/widget/widget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/widget/layer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/app.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/window.h
)

# build lib
add_library(ayaya_gui)
target_sources(ayaya_gui
    PRIVATE ${ayaya_sources}
    PUBLIC ${ayaya_headers}
)

target_include_directories(ayaya_gui
  PUBLIC
    include
  )


set_target_properties(ayaya_gui
  PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON
  )

# dependency
find_package(OPENGL REQUIRED)
target_link_libraries(ayaya_gui PUBLIC ${OPENGL_LIBRARIES})

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(ayaya_gui PUBLIC glfw)

# Skia vcpkg seems to fail setting dll_export vs. dll_import flags correctly.
# SKIA_IMPLEMENTATION=1 is evaluated to __declspec(dll_export) when compiling 
# the demo but it has to be __declspec(dll_import).
# Hence we overwrite SKIA_IMPLEMENTATION=1 by SKIA_IMPLEMENTATION=0!
find_package(skia CONFIG REQUIRED)
# UNCOMMENT TO FIX LINK ERRORS
get_target_property(skia_interface_defs skia INTERFACE_COMPILE_DEFINITIONS)
string(REPLACE "SKIA_IMPLEMENTATION=1" "SKIA_IMPLMENTATION=0" skia_interface_defs_fixed "${skia_interface_defs}")
set_target_properties(skia PROPERTIES INTERFACE_COMPILE_DEFINITIONS "${skia_interface_defs_fixed}")
target_link_libraries(ayaya_gui PUBLIC skia skia::skia)

