#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include "glad/glad.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "UI.h"

struct Input {
    bool forward;
    bool backward;
    bool left;
    bool right;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window, Input &i);

int main() {
    // Init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create window and opengl context
    GLFWwindow* window = glfwCreateWindow(800, 600, "My cool windy", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Load GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
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

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    Shader sh{"../shaders/texture.vert", "../shaders/texture.frag"};
    Texture tx{"../wall.jpg"};

    //Mesh m = Mesh::quad(1.f, 1.f);
    Mesh m = Mesh::cube(1.0f);

    Camera c{vec3(0.f, 0.f, 3.f), vec3(0.f, 0.f, -1.f)};

    auto model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    auto view = c.view();

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    glEnable(GL_DEPTH_TEST);

    Input i{};

    // Render loop
    while(!glfwWindowShouldClose(window))
    {
        process_input(window, i);
        glfwSwapBuffers(window);
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Render here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        sh.enable();

        //s32 unif = sh.get_location("color");
        //glUniform4f(unif, 1.f, 0.5f, 0.9f, 1.f);

        s32 unif = sh.get_location("boundTexture");
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tx.get_id());
        glUniform1i(unif, 0);

        model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0.5f, 1.0f, 0.0f));

        s32 modelLoc = sh.get_location("model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        s32 viewLoc = sh.get_location("view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        s32 projLoc = sh.get_location("projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        m.render();

        // Render IMGUI here

        const ImGuiViewport* viewport = ImGui::GetMainViewport();

        ImGui::SetNextWindowPos(ImVec2(viewport->WorkPos.x, viewport->WorkPos.y), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(200, viewport->Size.y), ImGuiCond_FirstUseEver);

        ImGui::Begin("Import", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        if (ImGui::Button("Load model")) {
            NFD::Guard nfdGuard;
            NFD::UniquePath outPath;
            if (NFD::OpenDialog(outPath) == NFD_OKAY) {
                m = Mesh(outPath.get());
            }
        }
        ImGui::End();

        //ImGui::ShowDemoWindow();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window, Input &i) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    i.forward = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
    i.backward = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
    i.left = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
    i.right = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
}
