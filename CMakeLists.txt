cmake_minimum_required(VERSION 3.31)
project(vv)

set(CMAKE_OSX_SYSROOT /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk)
set(CMAKE_CXX_STANDARD 20)
set(appName vv)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(GLM REQUIRED)
find_package(assimp REQUIRED)

include_directories("glad/include")
include_directories("imgui")
include_directories("imgui/backends")
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLFW3_INCLUDE_DIRS})
include_directories(${ASSIMP_INCLUDE_DIRS})
include_directories(${GLM_INCLUDE_DIRS})
include_directories("vendor/include")
include_directories("src")

link_directories(${OPENGL_LIBRARY_DIRS})
link_directories(${GLFW3_LIBRARY_DIRS})

set(imgui_files imgui/imgui.cpp imgui/imgui_demo.cpp imgui/imgui_draw.cpp imgui/imgui_tables.cpp imgui/imgui_widgets.cpp imgui/backends/imgui_impl_glfw.cpp imgui/backends/imgui_impl_opengl3.cpp imgui/misc/cpp/imgui_stdlib.cpp)
set(app_files
    src/main.cpp
    src/Shader.cpp
    src/Mesh.cpp
    src/Texture.cpp
        src/Camera.cpp
        src/Camera.h
        src/Model.cpp
        src/Model.h
)

add_executable(${appName} ${imgui_files} glad/src/glad.c vendor/stb_image.cpp ${app_files})

target_link_libraries(${appName} ${OPENGL_LIBRARIES} glfw dl)
