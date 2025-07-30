//
// Created by kam on 21.7.2025.
//

#include "UI.h"

#include "types.h"
#include "Root.h"
#include "imgui_impl_opengl3.h"

//TODO: Add frame time overlay
auto UI::draw() -> void {
    const ImGuiViewport* viewport = ImGui::GetMainViewport();

    f32 height = viewport->Size.y;
    f32 width = viewport->Size.x;

    // Menu
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Open", "Cmd+O")) {
                NFD::Guard nfdGuard;
                NFD::UniquePath outPath;
                if (NFD::OpenDialog(outPath) == NFD_OKAY) {
                    //std::cout << "loading mesh: " << outPath << std::endl;
                    Root::meshes[1] = Mesh{outPath.get()};
                }
            }
            if (ImGui::MenuItem("Quit", "Cmd+Q")) {
                glfwSetWindowShouldClose(Root::window, true);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    // Panel
    ImGui::SetNextWindowPos(ImVec2(viewport->WorkPos.x, viewport->WorkPos.y));
    ImGui::SetNextWindowSizeConstraints(ImVec2{0, height}, ImVec2{width, height});
    ImGui::SetNextWindowSize(ImVec2(200, viewport->Size.y), ImGuiCond_FirstUseEver);
    ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);

    // Camera
    f32 fov = Root::camera.get_fov();
    ImGui::SeparatorText("Camera");
    ImGui::SliderFloat("FOV", &fov, 30.f, 100.f, "%.2f");
    Root::camera.set_fov(fov);

    // Transform // Disabled for now since meshes can't be moved yet
    /*
    ImGui::SeparatorText("Position");
    static float x = 0.001f;
    static float y = 0.001f;
    static float z = 0.001f;
    ImGui::InputFloat("X", &x, 0.01f, 1.0f, "%.3f");
    ImGui::InputFloat("Y", &y, 0.01f, 1.0f, "%.3f");
    ImGui::InputFloat("Z", &z, 0.01f, 1.0f, "%.3f");
    */

    // Shader properties
    ImGui::SeparatorText("Material");
    static s32 n = 0;
    ImGui::Combo("Shader", &n, "Phong\0PBR\0IBL\0\0");
    ImGui::End();

    ImGui::ShowDemoWindow();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
