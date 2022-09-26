cmake_minimum_required (VERSION 3.8)

# test app
add_executable (example "ayaya_gui.cpp" "ayaya_gui.h")
set_target_properties(example
  PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON
  )

target_include_directories(example PRIVATE ../ayaya_gui/include)
target_link_libraries(example ayaya_gui)