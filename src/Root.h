//
// Created by kam on 20.7.2025.
//

#ifndef ROOT_H
#define ROOT_H

#include <vector>
#include <GLFW/glfw3.h>

#include "types.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"


class Root {
    inline static GLFWwindow* window;

public:
    inline static std::vector<Mesh> meshes;
    inline static std::vector<Shader> shaders;
    inline static std::vector<Texture> textures;
    inline static Camera camera{vec3(0.f, 0.f, 3.f), vec3(0.f, 0.f, -1.f)};

    Root();

    static auto init() -> void;
    static auto loop() -> void;
    static auto cleanup() -> void;
    static auto process_input() -> void;

private:
    static auto framebuffer_size_callback(GLFWwindow* window, int width, int height) -> void;
};



#endif //ROOT_H
