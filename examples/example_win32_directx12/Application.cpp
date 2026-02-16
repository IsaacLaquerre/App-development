#include "Application.h"
#include "Popups.h"

#include "imgui.h"
#include "windef.h"
#include "WinUser.h"

#include <cstdio>
#include <cmath>
#include <ctime>
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
    ImVec2 window_size = ImVec2(1280, 800);
    ImVec2 window_pos = ImVec2(100, 100);

    bool fullscreen = false;
    bool vsync = true;
    bool showFps = true;

    extern bool open_settings = false;
    extern bool exit = false;

    static void TextCentered(std::string text) {
        auto windowWidth = ImGui::GetWindowSize().x;
        auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

        ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
        ImGui::Text(text.c_str());
    }

    struct Theme {
        char* type;
        ImVec4 background_color;
        ImVec4 foreground_color;
        ImVec4 font_color;
    };

    Theme themes[2]{
        { "Dark",
            RGBA::ToVec4(53.0f, 53.0f, 62.0f, 1.0f),
            RGBA::ToVec4(0.0f, 122.0f, 204.0f, 1.0f),
            RGBA::ToVec4(255.0f, 255.0f, 255.0f, 1.0f)
        },
        { "Light",
            RGBA::ToVec4(250.0f, 250.0f, 250.0f, 1.0f),
            RGBA::ToVec4(147.0f, 148.0f, 165.0f, 1.0f),
            RGBA::ToVec4(0.0f, 0.0f, 0.0f, 1.0f)
        }
    };

    ImVec4 background_color;
    ImVec4 foreground_color;
    ImVec4 font_color;

    enum class ThemeIndices {
        Dark = 0,
        Light = 1
    };
    int themeIndex = 0;
    ThemeIndices theme = static_cast<ThemeIndices>(themeIndex);

    void RenderApp()
    {
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigViewportsNoAutoMerge = false;
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        window_size = viewport->Size;

        static ImFontConfig small_size_cfg;
        small_size_cfg.SizePixels = 15.0f;
        static ImFontConfig large_size_cfg;
        large_size_cfg.SizePixels = 24.0f;

        static ImFont* font_small = io.Fonts->AddFontDefault(&small_size_cfg);
        static ImFont* DroidSans_small = io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", small_size_cfg.SizePixels);
        static ImFont* font_large = io.Fonts->AddFontDefault(&large_size_cfg);
        static ImFont* DroidSans_large = io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", large_size_cfg.SizePixels);

        background_color = themes[static_cast<int>(MyApp::GetTheme())].background_color;
        foreground_color = themes[static_cast<int>(MyApp::GetTheme())].foreground_color;
        font_color = themes[static_cast<int>(MyApp::GetTheme())].font_color;

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
        style.Colors[ImGuiCol_Button] = foreground_color;
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(foreground_color.x, foreground_color.y, foreground_color.z, foreground_color.w - 0.25f);
        style.Colors[ImGuiCol_ButtonActive] = ImVec4(foreground_color.x, foreground_color.y, foreground_color.z, foreground_color.w - 0.5f);
        style.Colors[ImGuiCol_MenuBarBg] = background_color;
        style.Colors[ImGuiCol_Header] = foreground_color;
        style.Colors[ImGuiCol_HeaderHovered] = ImVec4(foreground_color.x, foreground_color.y, foreground_color.z, foreground_color.w - 0.25f);
        style.Colors[ImGuiCol_HeaderActive] = ImVec4(foreground_color.x, foreground_color.y, foreground_color.z, foreground_color.w - 0.5f);
        style.Colors[ImGuiCol_MenuBarBg] = background_color;
        style.Colors[ImGuiCol_WindowBg] = background_color;
        style.Colors[ImGuiCol_PopupBg] = ImVec4(background_color.x, background_color.y, background_color.z, background_color.w - 0.05f);
        style.Colors[ImGuiCol_TitleBg] = background_color;
        style.Colors[ImGuiCol_TitleBgActive] = ImVec4(background_color.x, background_color.y, background_color.z, background_color.w);
        style.Colors[ImGuiCol_TitleBgCollapsed] = background_color;
        style.Colors[ImGuiCol_InputTextCursor] = font_color;
        style.Colors[ImGuiCol_SliderGrab] = foreground_color;
        style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(foreground_color.x, foreground_color.y, foreground_color.z, foreground_color.w - 0.25f);
        style.Colors[ImGuiCol_Text] = font_color;
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

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Options"))
            {
                if (ImGui::MenuItem("Settings"))
                {
                    open_settings = true;
                }
                if (ImGui::IsItemHovered()) ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);

                if (ImGui::MenuItem("Exit"))
                {
                    exit = true;
                }
                if (ImGui::IsItemHovered()) ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
                ImGui::EndMenu();
            }
            if (ImGui::IsItemHovered()) ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);

            if (ImGui::BeginMenu("Credits"))
            {
                ImGui::Text("Made by Isaac Laquerre");
                std::time_t t = std::time(nullptr);
                std::tm *const pTInfo = std::localtime(&t);
                int currYear = 1900 + pTInfo->tm_year;
                std::string currYearVerbose = "Copyright © ";
                currYearVerbose += std::to_string(currYear);
                ImGui::Text(currYearVerbose.c_str());
                ImGui::EndMenu();
            }
            if (ImGui::IsItemHovered()) ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
            ImGui::EndMainMenuBar();
        }

        RenderPopups();

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
        ImDrawList* viewport_background_draw_list = ImGui::GetBackgroundDrawList();

        // Foreground (viewport) draw list
        ImDrawList* viewport_foreground_draw_list = ImGui::GetForegroundDrawList();
        if (MyApp::GetShowFps())
        {

            // Draw FPS
            std::string fps_text_string = "FPS: " + std::to_string((int)std::floor(io.Framerate));
            const char* fps_text = fps_text_string.c_str();
            ImVec2 fps_text_size = ImGui::CalcTextSize(fps_text);
            ImVec2 fps_text_pos = ImVec2(mainViewportSize.x - 70, 3.0f);
            ImU32 fps_color = static_cast<int>(MyApp::GetTheme()) == 0 ? IM_COL32(255, 255, 0, 255) : IM_COL32(255, 0, 0, 255);
            //ImGui::PushClipRect(window_pos, ImVec2(fps_text_pos.x + fps_text_size.x, fps_text_pos.y + fps_text_size.y), true);
            viewport_foreground_draw_list->AddText(fps_text_pos, fps_color, fps_text);
            //ImGui::PopClipRect();
        }

        // Window module draw list
        ImDrawList* draw_list = ImGui::GetWindowDrawList();


        ImGui::End();

        // Show imgui_demo.cpp render
        //ImGui::ShowDemoWindow();
    }

    ImVec4 GetBackgroundColor()
    {
        return background_color;
    }

    ImVec4 GetFontColor()
    {
        return font_color;
    }

    // Handle fullscreen/windowed logic
    extern void ToggleFullscreen()
    {
        fullscreen = !fullscreen;
    }

    bool GetFullscreen()
    {
        return fullscreen;
    }

    // Handle theme toggle logic
    extern void ToggleTheme()
    {
        themeIndex++;
        if (themeIndex > 1) themeIndex = 0;
        theme = static_cast<ThemeIndices>(themeIndex);
    }

    ThemeIndices GetTheme()
    {
        return theme;
    }

    // Handle vsync toggle logic
    extern void ToggleVsync()
    {
        vsync = !vsync;
    }

    // Handle fps toggle logic
    extern void ToggleShowFps()
    {
        showFps = !showFps;
    }

    bool GetVsync()
    {
        return vsync;
    }

    bool GetShowFps()
    {
        return showFps;
    }
}
