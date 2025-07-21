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


namespace Root {
     inline GLFWwindow* window;
     inline std::vector<Mesh> meshes;
     inline std::vector<Shader> shaders;
     inline std::vector<Texture> textures;
     inline Camera camera{vec3(0.f, 0.f, 3.f), vec3(0.f, 0.f, -1.f)};
    
     auto init() -> void;
     auto loop() -> void;
     auto cleanup() -> void;
     auto process_input() -> void;

     auto load_shaders() -> void;
     auto framebuffer_size_callback(GLFWwindow* window, int width, int height) -> void;
}


#endif //ROOT_H
