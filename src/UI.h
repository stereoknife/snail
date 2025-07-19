//
// Created by kam on 18.7.2025.
//

#ifndef UI_H
#define UI_H

#include "imgui.h"
#include "nfd.hpp"
#include "misc/cpp/imgui_stdlib.h"

namespace UI {
    std::string filename{"Filename"};

    auto draw_ui() -> void {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();

        ImGui::SetNextWindowPos(ImVec2(viewport->WorkPos.x, viewport->WorkPos.y), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(200, viewport->Size.y), ImGuiCond_FirstUseEver);

        ImGui::Begin("Import", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        if (ImGui::Button("Load model")) {
            //m = Mesh(filename);
            NFD::Guard nfdGuard;
            NFD::UniquePath outPath;
            if (NFD::OpenDialog(outPath) == NFD_OKAY) {
                filename.clear();
                filename.append(outPath.get());
            }
        }
        ImGui::End();
    }
}

#endif //UI_H
