#include "Application.h"

#include "imgui.h"

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
    struct RGBA {
        float r = 255.0f;
        float g = 255.0f;
        float b = 255.0f;
        float a = 1.0f;

        static ImVec4 RGBA::ToVec4(float r, float g, float b, float a)
        {
            return ImVec4(r * 1.0f / 255.0f, g * 1.0f / 255.0f, b * 1.0f / 255.0f, a);
        }

        static ImU32 RGBA::ToCol32(float r, float g, float b, float a)
        {
            return IM_COL32((int)r, (int)g, (int)b, (int)a);
        }

        static RGBA RGBA::Invert(float r, float g, float b, float a)
        {
            return { 255 - r, 255 - g, 255 - b, a };
        }
    };

    static void TextCentered(std::string text) {
        auto windowWidth = ImGui::GetWindowSize().x;
        auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

        ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
        ImGui::Text(text.c_str());
    }

    void RenderApp()
    {
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        static ImFontConfig small_size_cfg;
        small_size_cfg.SizePixels = 15.0f;
        static ImFontConfig large_size_cfg;
        large_size_cfg.SizePixels = 24.0f;

        static ImFont* font_small = io.Fonts->AddFontDefault(&small_size_cfg);
        static ImFont* DroidSans_small = io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", small_size_cfg.SizePixels);
        static ImFont* font_large = io.Fonts->AddFontDefault(&large_size_cfg);
        static ImFont* DroidSans_large = io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", large_size_cfg.SizePixels);

        // Make main window dockable
        //ImGui::DockSpaceOverViewport(ImGui::GetID("Test"), ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

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
        ImGui::SetNextWindowPos(ImVec2(100, 50), ImGuiCond_Appearing);
        ImGui::SetNextWindowSize(ImVec2((float)1080, 700), ImGuiCond_Appearing); //TODO: Scale depending on main window's size
        ImGui::PushStyleColor(ImGuiCol_WindowBg, RGBA::ToVec4(0.0f, 0.0f, 0.0f, 0.15f));

        ImGuiStyle& style = ImGui::GetStyle();
        //style.TabRounding =  5.f;
        //style.FrameRounding = 5.f;
        //style.GrabRounding = 5.f;
        style.WindowRounding = 5.f;
        //style.PopupRounding = 5.f;

        ImGui::Begin("##Main",
            nullptr,
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoScrollbar
        );

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
        ImGui::Separator();
        ImGui::Text("Value: %f", value);

        ImGui::EndTable();
        ImGui::NewLine();

        ImGui::SeparatorText("Color picker");

        ImGui::BeginTable("ColorPick", 2);

        ImGui::TableNextColumn();
        ImGui::NewLine();
        ImGui::NewLine();
        ImGui::Text("R");
        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_SliderGrab, RGBA::ToVec4(r_value, 0.0f, 0.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, RGBA::ToVec4(r_value, 0.0f, 0.0f, 1.0f));
        ImGui::SliderFloat("##R", &r_value, 0.0f, 255.0f);
        ImGui::PopStyleColor(2);
        ImGui::NewLine();
        ImGui::Text("G");
        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_SliderGrab, RGBA::ToVec4(0.0f, g_value, 0.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, RGBA::ToVec4(0.0f, g_value, 0.0f, 1.0f));
        ImGui::SliderFloat("##G", &g_value, 0.0f, 255.0f);
        ImGui::PopStyleColor(2);
        ImGui::NewLine();
        ImGui::Text("B");
        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_SliderGrab, RGBA::ToVec4(0.0f, 0.0f, b_value, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, RGBA::ToVec4(0.0f, 0.0f, b_value, 1.0f));
        ImGui::SliderFloat("##B", &b_value, 0.0f, 255.0f);
        ImGui::PopStyleColor(2);

        ImGui::TableNextColumn();
        ImDrawList* draw_list = ImGui::GetWindowDrawList();

        ImVec2 top_left = ImGui::GetCursorScreenPos();
        float size = 350.0f;
        ImVec2 sizeVec = ImVec2(150.0f, 150.0f);
        ImVec2 bottom_right = ImVec2(top_left.x + size, top_left.y + size);
        ImU32 color = IM_COL32(r_value, g_value, b_value, 255);
        float rounding = 0.0f;

        draw_list->AddRectFilled(top_left, bottom_right, color, rounding, ImDrawFlags_RoundCornersAll);
        ImGui::Dummy(sizeVec);

        ImGui::PushFont(DroidSans_large);
        char* sample_text = "Sample Text";
        ImVec2 text_size = ImGui::CalcTextSize(sample_text);
        ImVec2 text_pos = ImVec2(
            top_left.x + (size - text_size.x) * 0.5f,
            top_left.y + (size - text_size.y) * 0.5f
        );

        draw_list->AddText(text_pos, IM_COL32(255 - r_value, 255 - g_value, 255 - b_value, 255), sample_text);
        ImGui::PopFont();

        ImGui::EndTable();

        ImGui::PopFont();

        // UI

        ImGui::End();
        ImGui::PopStyleColor();

        // Show imgui_demo.cpp render
        // ImGui::ShowDemoWindow();
    }
}
