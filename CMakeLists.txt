cmake_minimum_required(VERSION 3.28)
project(guitest)

set(CMAKE_CXX_STANDARD 17)
set(appName guitest)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

include_directories("glad/include")
include_directories("imgui")
include_directories("imgui/backends")
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLFW3_INCLUDE_DIRS})

link_directories(${OPENGL_LIBRARY_DIRS})
link_directories(${GLFW3_LIBRARY_DIRS})

set(imgui_files imgui/imgui.cpp imgui/imgui_demo.cpp imgui/imgui_draw.cpp imgui/imgui_tables.cpp imgui/imgui_widgets.cpp imgui/backends/imgui_impl_glfw.cpp imgui/backends/imgui_impl_opengl3.cpp imgui/misc/cpp/imgui_stdlib.cpp)

add_executable(${appName} ${imgui_files} glad/src/glad.c main.cpp)

target_link_libraries(${appName} ${OPENGL_LIBRARIES} glfw dl)
