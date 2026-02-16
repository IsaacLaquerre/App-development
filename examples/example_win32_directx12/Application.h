#pragma once
#include <wtypes.h>

#include "imgui.h"

namespace MyApp
{
    void RenderApp();

    extern struct RGBA {
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

    struct Color {
        char* type;
        ImVec4 value;
    };

    ImVec4 GetBackgroundColor();
    ImVec4 GetFontColor();

    extern bool open_settings;
    extern bool exit;

    void ToggleFullscreen();
    bool GetFullscreen();

    enum class ThemeIndices;
    void ToggleTheme();
    ThemeIndices GetTheme();

    void ToggleVsync();
    bool GetVsync();

    void ToggleShowFps();
    bool GetShowFps();
}
