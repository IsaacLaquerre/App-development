#include "imgui.h"

#include "Popups.h"
#include "Application.h"

#include <cstdio>
#include <string>
#include <windows.h>

namespace MyApp
{
    void RenderPopups()
    {
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImGuiViewport* viewport = ImGui::GetMainViewport();

        static ImFontConfig large_size_cfg;
        large_size_cfg.ExtraSizeScale = 1.25f;
        static ImFont* font_large = io.Fonts->AddFontDefault(&large_size_cfg);

        float popupWidth = 500.0f;
        float popupHeight = 250.0f;
        float popupX = viewport->Pos.x + viewport->Size.x / 2 - popupWidth / 2;
        float popupY = viewport->Pos.y + viewport->Size.y / 2 - popupHeight / 2;

        ImGui::SetNextWindowSize(ImVec2(popupWidth, popupHeight), ImGuiCond_Always);
        ImGui::SetNextWindowPos(ImVec2(popupX, popupY), ImGuiCond_Always);
        if (ImGui::BeginPopup("Settings", ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::PushFont(font_large);
            ImGui::Text("Settings");
            ImGui::PopFont();
            ImGui::SeparatorText("Graphics");
            ImGui::BeginTable("Graphics", 2);

            ImGui::TableNextColumn();
            ImGui::Text("Fullscreen: ");
            ImGui::SameLine();
            const char* fullscreenVerbose = MyApp::GetFullscreen() ? "False" : "True";
            ImGui::SetCursorScreenPos(ImVec2(popupX + 100, ImGui::GetCursorScreenPos().y));
            if (ImGui::Button(fullscreenVerbose))
            {
                ToggleFullscreen();
            }
            if (ImGui::IsItemHovered()) ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);

            ImGui::Text("Show FPS: ");
            ImGui::SameLine();
            const char* showFpsVerbose = MyApp::GetShowFps() ? "Yes" : "No";
            ImGui::SetCursorScreenPos(ImVec2(popupX + 100, ImGui::GetCursorScreenPos().y));
            if (ImGui::Button(showFpsVerbose))
            {
                MyApp::ToggleShowFps();
            }
            if (ImGui::IsItemHovered()) ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);

            ImGui::Text("VSync: ");
            ImGui::SameLine();
            const char* vsyncVerbose = MyApp::GetVsync() ? "Enabled" : "Disabled";
            ImGui::SetCursorScreenPos(ImVec2(popupX + 100, ImGui::GetCursorScreenPos().y));
            if (ImGui::Button(vsyncVerbose))
            {
                MyApp::ToggleVsync();
            }
            if (ImGui::IsItemHovered()) ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);

            ImGui::Text("Theme: ");
            ImGui::SameLine();
            const char* themeVerbose = static_cast<int>(MyApp::GetTheme()) == 0 ? "Dark" : "Light";
            ImGui::SetCursorScreenPos(ImVec2(popupX + 100, ImGui::GetCursorScreenPos().y));
            if (ImGui::Button(themeVerbose))
            {
                MyApp::ToggleTheme();
            }
            if (ImGui::IsItemHovered()) ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);

            ImGui::EndTable();

            ImGui::SetCursorScreenPos(ImVec2((popupX + popupWidth) - 57, (popupY + popupHeight) - 27));
            if (ImGui::Button("Close"))
            {
                MyApp::open_settings = false;
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::IsItemHovered()) ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
            ImGui::EndPopup();
        }

        if (MyApp::open_settings) ImGui::OpenPopup("Settings");
    }
}
