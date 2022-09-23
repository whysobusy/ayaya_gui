# CMakeList.txt : CMake project for ayaya_gui, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (ayaya_gui  "main.cpp")

add_subdirectory(external/glfw)

target_include_directories(${PROJECT_NAME}
	PUBLIC external/glfw/include
)

target_link_directories(${PROJECT_NAME}
	PRIVATE external/glfw/src
)

target_link_libraries(${PROJECT_NAME} glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)