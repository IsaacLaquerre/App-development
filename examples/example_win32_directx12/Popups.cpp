#include "imgui.h"

#include "Application.h"
#include "Popups.h"

#include <cstdio>
#include <string>
#include <windows.h>

namespace MyApp
{
    bool fullscreen = false;

    enum class Themes {
        Dark = 0,
        Light = 1
    };
    int themeIndex = 0;
    Themes theme = static_cast<Themes>(themeIndex);

    ImVec2 window_size = ImVec2(1280, 800);
    ImVec2 window_pos = ImVec2(100, 100);

    bool* RenderPopups(bool* menu_flags)
    {
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        window_size = viewport->Size;

        static ImFontConfig large_size_cfg;
        large_size_cfg.ExtraSizeScale = 1.25f;
        static ImFont* font_large = io.Fonts->AddFontDefault(&large_size_cfg);

        bool open_settings = menu_flags[0];

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
            /*const char* fullscreenVerbose = std::to_string(fullscreen) == "0" ? "False" : "True";
            const std::string fullscreen_button_text = "Fullscreen: " + (std::string)fullscreenVerbose;
            if (ImGui::Button(fullscreen_button_text.c_str()))
            {
                ToggleFullscreen();
            }*/
            ImGui::Text("Theme: ");
            ImGui::SameLine();
            const char* themeVerbose = theme == Themes::Dark ? "Dark" : "Light";
            if (ImGui::Button(themeVerbose))
            {
                ToggleTheme();
            }
            if (ImGui::IsItemHovered()) ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);

            ImGui::EndTable();

            if (ImGui::Button("Close"))
            {
                open_settings = false;
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::IsItemHovered()) ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
            ImGui::EndPopup();
        }

        if (open_settings) ImGui::OpenPopup("Settings");

        menu_flags[0] = open_settings;
        return menu_flags;
    }

    // Handle fullscreen/windowed logic
    static void ToggleFullscreen()
    {
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        fullscreen = !fullscreen;

        if (fullscreen)
        {
            window_pos = ImGui::GetWindowPos();
            ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
        } else {
            ImGui::SetNextWindowSize(window_size, ImGuiCond_Always);
            ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_Always);
        }
    }

    Themes GetTheme()
    {
        return theme;
    }

    // Handle theme logic
    static void ToggleTheme()
    {
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        themeIndex++;
        if (themeIndex > 1) themeIndex = 0;
        theme = static_cast<Themes>(themeIndex);
    }
}
