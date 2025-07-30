//
// Created by kam on 20.7.2025.
//

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "glad/glad.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "nfd.hpp"

#include "Root.h"

#include "UI.h"

auto Root::init() -> void {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    window = glfwCreateWindow(800, 600, "My cool windy", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        // return -1;
        // Throw error or something
    }
    glfwMakeContextCurrent(window);

    // Load GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        // return -1;
        // Throw error or something
    }

    // Create viewport
    glViewport(0, 0, 800 * 2, 600 * 2);
    // Set resize callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

    ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    meshes.push_back(Mesh::cube(50.f));
    meshes.push_back(Mesh::cube(1.f));
    shaders.emplace_back("../shaders/sky.vert", "../shaders/sky.frag");
    shaders.emplace_back("../shaders/texture.vert", "../shaders/texture.frag");
    shaders.emplace_back("../shaders/reflection.vert", "../shaders/reflection.frag");
    textures.push_back(Texture::Cubemap("../textures/desert", "png"));
    textures.push_back(Texture::Texture2D("../textures/wall.jpg"));

    glEnable(GL_DEPTH_TEST);
}

auto Root::loop() -> void {
    auto model = glm::mat4(1.0f);

    while(!glfwWindowShouldClose(window))
    {
        s32 w, h;
        glfwGetWindowSize(window, &w, &h);

        auto view = camera.view();
        auto projection = camera.projection();

        process_input();
        glfwSwapBuffers(window);
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Render here
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Skybox
        shaders[0].bind();
        textures[0].bind(GL_TEXTURE0);

        shaders[0].set_int("specular_map", 0);
        shaders[0].set_mat4("view", view);
        shaders[0].set_mat4("projection", projection);

        meshes[0].render();

        auto err = glGetError();
        if (err != GL_NO_ERROR) {
            //std::cout << "OpenGL Error: " << err << std::endl;
        }

        // Mesh
        model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0.5f, 1.0f, 0.0f));

        u32 sh = 2;

        shaders[sh].bind();
        textures[1].bind(GL_TEXTURE0);
        shaders[sh].set_int("specular_map", 0);
        shaders[sh].set_mat4("model", model);
        shaders[sh].set_mat4("view", view);
        shaders[sh].set_mat4("projection", projection);

        meshes[1].render();

        // Render IMGUI here
        UI::draw();
    }
}

auto Root::cleanup() -> void {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
}

auto Root::process_input() -> void {
    auto& io = ImGui::GetIO();

    double x_mouse, y_mouse;
    glfwGetCursorPos(window, &x_mouse, &y_mouse);
    static double x_prev = x_mouse, y_prev = y_mouse;
    double delta_x = x_mouse - x_prev;
    double delta_y = y_mouse - y_prev;
    x_prev = x_mouse;
    y_prev = y_mouse;

    if (!io.WantCaptureKeyboard) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

    if (!io.WantCaptureMouse) {
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
            // Capture mouse
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            camera.mouse_input(delta_x, delta_y);
        }

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
            // Release mouse
            //glfwSetCursorPosCallback(window, nullptr);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }

    /*
    i.forward = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
    i.backward = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
    i.left = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
    i.right = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
    */
}

auto Root::mouse_input(GLFWwindow* window, double x_pos, double y_pos) -> void {
    camera.mouse_input(x_pos, y_pos);
}

auto Root::load_shaders() -> void {
    shaders.emplace_back("phong");
    shaders.emplace_back("reflection");
    shaders.emplace_back("pbs");
    shaders.emplace_back("ibl-pbs");
}

auto Root::framebuffer_size_callback(GLFWwindow* window, int width, int height) -> void
{
    glViewport(0, 0, width, height);
}
