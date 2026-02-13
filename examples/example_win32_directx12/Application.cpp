#include "Application.h"
#include "Popups.h"

#include "imgui.h"
#include "windef.h"
#include "WinUser.h"

#include <cstdio>
#include <string>

static bool show = true;

struct ImGuiDemoDockspaceArgs
{
    bool                IsFullscreen = true;
    bool                KeepWindowPadding = false; // Keep WindowPadding to help understand that DockSpace() is a widget inside the window.
    ImGuiDockNodeFlags  DockSpaceFlags = ImGuiDockNodeFlags_None;
};

namespace MyApp
{
    int appWidth = 0;
    int appHeight = 0;

    static void TextCentered(std::string text) {
        auto windowWidth = ImGui::GetWindowSize().x;
        auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

        ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
        ImGui::Text(text.c_str());
    }

    Color background_colors[2] = {
        { "Dark", RGBA::ToVec4(31.0f, 27.0f, 41.0f, 1.0f) },
        { "Light", RGBA::ToVec4(255.0f, 255.0f, 255.0f, 1.0f) }
    };
    ImVec4 background_color;

    Color font_colors[2] = {
        { "Dark", RGBA::ToVec4(255.0f, 255.0f, 255.0f, 1.0f) },
        { "Light", RGBA::ToVec4(0.0f, 0.0f, 0.0f, 1.0f) }
    };
    ImVec4 font_color;

    void RenderApp()
    {
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigViewportsNoAutoMerge = false;
        const ImGuiViewport* viewport = ImGui::GetMainViewport();

        static ImFontConfig small_size_cfg;
        small_size_cfg.SizePixels = 15.0f;
        static ImFontConfig large_size_cfg;
        large_size_cfg.SizePixels = 24.0f;

        static ImFont* font_small = io.Fonts->AddFontDefault(&small_size_cfg);
        static ImFont* DroidSans_small = io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", small_size_cfg.SizePixels);
        static ImFont* font_large = io.Fonts->AddFontDefault(&large_size_cfg);
        static ImFont* DroidSans_large = io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", large_size_cfg.SizePixels);

        background_color = background_colors[static_cast<int>(MyApp::GetTheme())].value;
        font_color = font_colors[static_cast<int>(MyApp::GetTheme())].value;

        // Make main window dockable
        //ImGui::DockSpaceOverViewport(ImGui::GetID("Test"), viewport, ImGuiDockNodeFlags_PassthruCentralNode);

        // Demo window code
        //static int opt_demo_mode = 0;
        //static bool opt_demo_mode_changed = false;
        //static ImGuiDemoDockspaceArgs args;

        //// Refocus our window to minimize perceived loss of focus when changing mode (caused by the fact that each use a different window, which would not happen in a real app)
        //if (opt_demo_mode_changed)
        //    ImGui::SetNextWindowFocus();
        //ImGui::Begin("Examples: Dockspace", nullptr, ImGuiWindowFlags_MenuBar);
        //opt_demo_mode_changed = false;
        //opt_demo_mode_changed |= ImGui::RadioButton("Basic demo mode", &opt_demo_mode, 0);
        //opt_demo_mode_changed |= ImGui::RadioButton("Advanced demo mode", &opt_demo_mode, 1);
        //ImGui::SeparatorText("Options");
        //if (opt_demo_mode == 0)
        //{
        //    args.DockSpaceFlags &= ImGuiDockNodeFlags_PassthruCentralNode; // Allowed flags
        //    ImGui::CheckboxFlags("Flag: PassthruCentralNode", &args.DockSpaceFlags, ImGuiDockNodeFlags_PassthruCentralNode);
        //}
        //else if (opt_demo_mode == 1)
        //{
        //    ImGui::Checkbox("Fullscreen", &args.IsFullscreen);
        //    ImGui::Checkbox("Keep Window Padding", &args.KeepWindowPadding);
        //    ImGui::SameLine();
        //    ImGui::BeginDisabled(args.IsFullscreen == false);
        //    ImGui::CheckboxFlags("Flag: PassthruCentralNode", &args.DockSpaceFlags, ImGuiDockNodeFlags_PassthruCentralNode);
        //    ImGui::EndDisabled();
        //    ImGui::CheckboxFlags("Flag: NoDockingOverCentralNode", &args.DockSpaceFlags, ImGuiDockNodeFlags_NoDockingOverCentralNode);
        //    ImGui::CheckboxFlags("Flag: NoDockingSplit", &args.DockSpaceFlags, ImGuiDockNodeFlags_NoDockingSplit);
        //    ImGui::CheckboxFlags("Flag: NoUndocking", &args.DockSpaceFlags, ImGuiDockNodeFlags_NoUndocking);
        //    ImGui::CheckboxFlags("Flag: NoResize", &args.DockSpaceFlags, ImGuiDockNodeFlags_NoResize);
        //    ImGui::CheckboxFlags("Flag: AutoHideTabBar", &args.DockSpaceFlags, ImGuiDockNodeFlags_AutoHideTabBar);
        //}

        //// Show demo options and help
        //if (ImGui::BeginMenuBar())
        //{
        //    if (ImGui::BeginMenu("Help"))
        //    {
        //        ImGui::TextUnformatted(
        //            "This demonstrates the use of ImGui::DockSpace() which allows you to manually\ncreate a docking node _within_ another window." "\n"
        //            "The \"Basic\" version uses the ImGui::DockSpaceOverViewport() helper. Most applications can probably use this.");
        //        ImGui::Separator();
        //        ImGui::TextUnformatted("When docking is enabled, you can ALWAYS dock MOST window into another! Try it now!" "\n"
        //            "- Drag from window title bar or their tab to dock/undock." "\n"
        //            "- Drag from window menu button (upper-left button) to undock an entire node (all windows)." "\n"
        //            "- Hold SHIFT to disable docking (if io.ConfigDockingWithShift == false, default)" "\n"
        //            "- Hold SHIFT to enable docking (if io.ConfigDockingWithShift == true)");
        //        ImGui::Separator();
        //        ImGui::TextUnformatted("More details:"); ImGui::Bullet(); ImGui::SameLine(); ImGui::TextLinkOpenURL("Docking Wiki page", "https://github.com/ocornut/imgui/wiki/Docking");
        //        ImGui::BulletText("Read comments in ShowExampleAppDockSpace()");
        //        ImGui::EndMenu();
        //    }
        //    ImGui::EndMenuBar();
        //}
        //ImGui::End();

        // Custom "window panels" rendering
        //ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_MenuBar);
        //if (ImGui::BeginMenuBar())
        //{
        //    if (ImGui::BeginMenu("Credits"))
        //    {
        //        ImGui::TextUnformatted(
        //            "This demonstrates the use of ImGui::DockSpace() which allows you to manually\ncreate a docking node _within_ another window." "\n"
        //            "The \"Basic\" version uses the ImGui::DockSpaceOverViewport() helper. Most applications can probably use this.");
        //        ImGui::Separator();
        //        ImGui::TextUnformatted("When docking is enabled, you can ALWAYS dock MOST window into another! Try it now!" "\n"
        //            "- Drag from window title bar or their tab to dock/undock." "\n"
        //            "- Drag from window menu button (upper-left button) to undock an entire node (all windows)." "\n"
        //            "- Hold SHIFT to disable docking (if io.ConfigDockingWithShift == false, default)" "\n"
        //            "- Hold SHIFT to enable docking (if io.ConfigDockingWithShift == true)");
        //        ImGui::Separator();
        //        ImGui::TextUnformatted("More details:"); ImGui::Bullet(); ImGui::SameLine(); ImGui::TextLinkOpenURL("Docking Wiki page", "https://github.com/ocornut/imgui/wiki/Docking");
        //        ImGui::BulletText("Read comments in ShowExampleAppDockSpace()");
        //        ImGui::EndMenu();
        //    }
        //    ImGui::EndMenuBar();
        //}
        //ImGui::Text("Hello World!");
        //static char* input = "";
        //static char inputBuffer[128] = "";
        //ImGui::BeginTable("Test", 2);
        //ImGui::TableNextColumn();
        //if (ImGui::InputText("Input", inputBuffer, IM_ARRAYSIZE(inputBuffer), 0)) input = inputBuffer;
        //if (input == "" || strlen(input) == 0) input = "-";
        //static float value = 0.0f;
        //ImGui::TableNextColumn();
        //ImGui::DragFloat("Value", &value);
        //ImGui::EndTable();
        //ImGui::Separator();
        //ImGui::Text("Input text: %s, input float: %f", input, value);
        //ImGui::End();

        // Custom "1 main window" rendering

        // Style handling
        ImVec2 mainViewportSize = viewport->Size;
        ImVec2 mainViewportPos = viewport->Pos;
        static float windowScale = 0.9f;
        float windowSizeX = mainViewportSize.x * windowScale;
        float windowSizeY = mainViewportSize.y * windowScale;
        float windowPosX = mainViewportPos.x + (mainViewportSize.x - windowSizeX) / 2;
        float windowPosY = mainViewportPos.y + (mainViewportSize.y - windowSizeY) / 2;

        ImGui::PushStyleColor(ImGuiCol_MenuBarBg, background_color);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, RGBA::ToVec4(0.0f, 0.0f, 0.0f, 0.05f));
        ImGui::PushStyleColor(ImGuiCol_Text, font_color);
        ImGui::SetNextWindowPos(ImVec2(windowPosX, windowPosY), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(windowSizeX, windowSizeY), ImGuiCond_Always);

        ImGuiStyle& style = ImGui::GetStyle();
        //style.TabRounding =  5.f;
        //style.FrameRounding = 5.f;
        //style.GrabRounding = 5.f;
        style.ChildRounding = 5.f;
        style.ScrollbarRounding = 5.f;
        style.TabRounding = 5.f;
        style.WindowRounding = 5.f;
        style.PopupRounding = 5.f;
        style.Colors[ImGuiCol_MenuBarBg] = background_color;
        style.Colors[ImGuiCol_WindowBg] = background_color;
        style.Colors[ImGuiCol_PopupBg] = ImVec4(background_color.x, background_color.y, background_color.z, background_color.w - 0.15f);
        style.Colors[ImGuiCol_TitleBg] = background_color;
        style.Colors[ImGuiCol_TitleBgActive] = ImVec4(background_color.x, background_color.y, background_color.z, background_color.w);
        style.Colors[ImGuiCol_Text] = font_color;
        style.Colors[ImGuiCol_TitleBgCollapsed] = background_color;
        style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.5f);

        ImGui::Begin("##Main",
            nullptr,
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoScrollbar
        );

        // Menu bar

        bool open_settings = false;

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Options"))
            {
                //ImGui::PushStyleColor(ImGuiCol_HeaderHovered, background_color);
                ImGui::PushStyleColor(ImGuiCol_Header, background_color);
                if (ImGui::MenuItem("Settings"))
                {
                    open_settings = true;
                }
                if (ImGui::IsItemHovered()) ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
                ImGui::PopStyleColor();
                ImGui::EndMenu();
            }
            if (ImGui::IsItemHovered()) ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
            ImGui::EndMainMenuBar();
        }

        bool menu_flags[1] = { open_settings };
        bool* menu_flags_resp = RenderPopups(menu_flags);
        for (int i = 0; i < sizeof(menu_flags_resp) - 7; i++)
        {
            menu_flags[i] = menu_flags_resp[i];
        }

        // Title
        ImGui::PushFont(DroidSans_large);
        TextCentered("SAMPLE_GUI_LAYOUT");
        ImGui::PopFont();
        ImGui::Separator();
        ImGui::NewLine();

        // Body
        static char* input = "";
        static char inputBuffer[128] = "";
        static float value = 0.0f;
        static float r_value = 0.0f;
        static float g_value = 0.0f;
        static float b_value = 0.0f;

        ImGui::PushFont(DroidSans_small);
        
        ImGui::Text("Hello World!");
        ImGui::NewLine();

        ImGui::BeginTable("Test", 2);

        ImGui::TableNextColumn();
        ImGui::Text("Input");
        ImGui::SameLine();
        if (ImGui::InputText("##Input", inputBuffer, IM_ARRAYSIZE(inputBuffer), 0)) input = inputBuffer;
        if (input == "" || strlen(input) == 0) input = "-";
        ImGui::Separator();
        ImGui::Text("Input text: %s", input);

        ImGui::TableNextColumn();
        ImGui::Text("Value");
        ImGui::SameLine();
        ImGui::DragFloat("##Value", &value);
        if (ImGui::IsItemHovered()) ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
        ImGui::Separator();
        ImGui::Text("Value: %f", value);

        ImGui::EndTable();
        ImGui::NewLine();

        ImGui::SeparatorText("Color picker");

        ImGui::NewLine();
        ImGui::BeginTable("Color picker", 2);

        ImGui::TableNextColumn();
        static float color_picker[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

        ImGui::ColorEdit4("Color", color_picker);

        ImGui::EndTable();

        ImGui::PopFont();

        // Externally drawn items

        // Background (viewport) draw list
        ImDrawList* viewport_draw_list = ImGui::GetBackgroundDrawList();
        ImVec2 fps_text_pos = ImVec2(5, 5);
        std::string fps_text_string = "FPS: " + std::to_string(io.Framerate) + "\n";
        const char* fps_text = fps_text_string.c_str();
        viewport_draw_list->AddText(fps_text_pos, IM_COL32(255, 255, 0, 255), fps_text);

        // Window module draw list
        ImDrawList* draw_list = ImGui::GetWindowDrawList();


        ImGui::End();
        ImGui::PopStyleColor(3);

        // Show imgui_demo.cpp render
        // ImGui::ShowDemoWindow();
    }

    ImVec4 GetBackgroundColor()
    {
        return background_color;
    }

    ImVec4 GetFontColor()
    {
        return font_color;
    }
}
